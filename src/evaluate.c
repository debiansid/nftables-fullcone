/*
 * Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/netfilter.h>
#include <linux/netfilter_arp.h>
#include <linux/netfilter/nf_tables.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <net/ethernet.h>

#include <expression.h>
#include <statement.h>
#include <rule.h>
#include <erec.h>
#include <gmputil.h>
#include <utils.h>

static int expr_evaluate(struct eval_ctx *ctx, struct expr **expr);

static const char *byteorder_names[] = {
	[BYTEORDER_INVALID]		= "invalid",
	[BYTEORDER_HOST_ENDIAN]		= "host endian",
	[BYTEORDER_BIG_ENDIAN]		= "big endian",
};

static int __fmtstring(4, 5) __stmt_binary_error(struct eval_ctx *ctx,
						 const struct location *l1,
						 const struct location *l2,
						 const char *fmt, ...)
{
	struct error_record *erec;
	va_list ap;

	va_start(ap, fmt);
	erec = erec_vcreate(EREC_ERROR, l1, fmt, ap);
	if (l2 != NULL)
		erec_add_location(erec, l2);
	va_end(ap);
	erec_queue(erec, ctx->msgs);
	return -1;

}

#define stmt_error(ctx, s1, fmt, args...) \
	__stmt_binary_error(ctx, &(s1)->location, NULL, fmt, ## args)
#define stmt_binary_error(ctx, s1, s2, fmt, args...) \
	__stmt_binary_error(ctx, &(s1)->location, &(s2)->location, fmt, ## args)
#define chain_error(ctx, s1, fmt, args...) \
	__stmt_binary_error(ctx, &(s1)->location, NULL, fmt, ## args)
#define monitor_error(ctx, s1, fmt, args...) \
	__stmt_binary_error(ctx, &(s1)->location, NULL, fmt, ## args)

static int __fmtstring(3, 4) set_error(struct eval_ctx *ctx,
				       const struct set *set,
				       const char *fmt, ...)
{
	struct error_record *erec;
	va_list ap;

	va_start(ap, fmt);
	erec = erec_vcreate(EREC_ERROR, &set->location, fmt, ap);
	va_end(ap);
	erec_queue(erec, ctx->msgs);
	return -1;
}

static struct expr *implicit_set_declaration(struct eval_ctx *ctx,
					     const struct datatype *keytype,
					     unsigned int keylen,
					     struct expr *expr)
{
	struct cmd *cmd;
	struct set *set;
	struct handle h;

	set = set_alloc(&expr->location);
	set->flags	= SET_F_CONSTANT | SET_F_ANONYMOUS | expr->set_flags;
	set->handle.set = xstrdup(set->flags & SET_F_MAP ? "map%d" : "set%d");
	set->keytype 	= keytype;
	set->keylen	= keylen;
	set->init	= expr;

	if (ctx->table != NULL)
		list_add_tail(&set->list, &ctx->table->sets);
	else {
		handle_merge(&set->handle, &ctx->cmd->handle);
		memset(&h, 0, sizeof(h));
		handle_merge(&h, &set->handle);
		cmd = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &h, &expr->location, set);
		cmd->location = set->location;
		list_add_tail(&cmd->list, &ctx->cmd->list);
	}

	return set_ref_expr_alloc(&expr->location, set);
}

// FIXME
#include <netlink.h>
static struct set *get_set(struct eval_ctx *ctx, const struct handle *h,
			   const char *identifier)
{
	struct netlink_ctx nctx = {
		.msgs = ctx->msgs,
	};
	struct handle handle;
	struct set *set;
	int err;

	if (ctx->table != NULL) {
		set = set_lookup(ctx->table, identifier);
		if (set != NULL)
			return set;
	}

	init_list_head(&nctx.list);

	memset(&handle, 0, sizeof(handle));
	handle_merge(&handle, h);
	handle.set = xstrdup(identifier);
	err = netlink_get_set(&nctx, &handle, &internal_location);
	handle_free(&handle);

	if (err < 0)
		return NULL;
	return list_first_entry(&nctx.list, struct set, list);
}

static enum ops byteorder_conversion_op(struct expr *expr,
					enum byteorder byteorder)
{
	switch (expr->byteorder) {
	case BYTEORDER_HOST_ENDIAN:
		if (byteorder == BYTEORDER_BIG_ENDIAN)
			return OP_HTON;
		break;
	case BYTEORDER_BIG_ENDIAN:
		if (byteorder == BYTEORDER_HOST_ENDIAN)
			return OP_NTOH;
		break;
	default:
		break;
	}
	BUG("invalid byte order conversion %u => %u\n",
	    expr->byteorder, byteorder);
}

static int byteorder_conversion(struct eval_ctx *ctx, struct expr **expr,
				enum byteorder byteorder)
{
	enum ops op;

	assert(!expr_is_constant(*expr) || expr_is_singleton(*expr));

	if ((*expr)->byteorder == byteorder)
		return 0;
	if (expr_basetype(*expr)->type != TYPE_INTEGER)
		return expr_error(ctx->msgs, *expr,
			 	  "Byteorder mismatch: expected %s, got %s",
				  byteorder_names[byteorder],
				  byteorder_names[(*expr)->byteorder]);

	if (expr_is_constant(*expr))
		(*expr)->byteorder = byteorder;
	else {
		op = byteorder_conversion_op(*expr, byteorder);
		*expr = unary_expr_alloc(&(*expr)->location, op, *expr);
		if (expr_evaluate(ctx, expr) < 0)
			return -1;
	}
	return 0;
}

/*
 * Symbol expression: parse symbol and evaluate resulting expression.
 */
static int expr_evaluate_symbol(struct eval_ctx *ctx, struct expr **expr)
{
	struct error_record *erec;
	struct symbol *sym;
	struct set *set;
	struct expr *new;

	switch ((*expr)->symtype) {
	case SYMBOL_VALUE:
		(*expr)->dtype = ctx->ectx.dtype;
		erec = symbol_parse(*expr, &new);
		if (erec != NULL) {
			erec_queue(erec, ctx->msgs);
			return -1;
		}
		break;
	case SYMBOL_DEFINE:
		sym = symbol_lookup((*expr)->scope, (*expr)->identifier);
		if (sym == NULL)
			return expr_error(ctx->msgs, *expr,
					  "undefined identifier '%s'",
					  (*expr)->identifier);
		new = expr_clone(sym->expr);
		break;
	case SYMBOL_SET:
		set = get_set(ctx, &ctx->cmd->handle, (*expr)->identifier);
		if (set == NULL)
			return -1;
		new = set_ref_expr_alloc(&(*expr)->location, set);
		break;
	}

	expr_free(*expr);
	*expr = new;

	return expr_evaluate(ctx, expr);
}

static int expr_evaluate_value(struct eval_ctx *ctx, struct expr **expr)
{
	mpz_t mask;

	switch (expr_basetype(*expr)->type) {
	case TYPE_INTEGER:
		mpz_init_bitmask(mask, ctx->ectx.len);
		if (mpz_cmp((*expr)->value, mask) > 0) {
			expr_error(ctx->msgs, *expr,
				   "Value %Zu exceeds valid range 0-%Zu",
				   (*expr)->value, mask);
			mpz_clear(mask);
			return -1;
		}
		(*expr)->byteorder = ctx->ectx.byteorder;
		(*expr)->len = ctx->ectx.len;
		mpz_clear(mask);
		break;
	case TYPE_STRING:
		if (ctx->ectx.len > 0) {
			if ((*expr)->len > ctx->ectx.len)
				return expr_error(ctx->msgs, *expr,
						  "String exceeds maximum length of %u",
						  ctx->ectx.len / BITS_PER_BYTE);
			(*expr)->len = ctx->ectx.len;
		}
		break;
	default:
		BUG("invalid basetype %s\n", expr_basetype(*expr)->name);
	}
	return 0;
}

/*
 * Primary expressions determine the datatype context.
 */
static int expr_evaluate_primary(struct eval_ctx *ctx, struct expr **expr)
{
	__expr_set_context(&ctx->ectx, (*expr)->dtype, (*expr)->byteorder,
			   (*expr)->len);
	return 0;
}

/*
 * Payload expression: check whether dependencies are fulfilled, otherwise
 * generate the necessary relational expression and prepend it to the current
 * statement.
 */
static int expr_evaluate_payload(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *payload = *expr;
	enum proto_bases base = payload->payload.base;
	struct stmt *nstmt;

	if (ctx->pctx.protocol[base].desc == NULL) {
		if (payload_gen_dependency(ctx, payload, &nstmt) < 0)
			return -1;
		list_add_tail(&nstmt->list, &ctx->stmt->list);
	} else if (ctx->pctx.protocol[base].desc != payload->payload.desc)
		return expr_error(ctx->msgs, payload,
				  "conflicting protocols specified: %s vs. %s",
				  ctx->pctx.protocol[base].desc->name,
				  payload->payload.desc->name);

	return expr_evaluate_primary(ctx, expr);
}

/*
 * CT expression: update the protocol dependant types bases on the protocol
 * context.
 */
static int expr_evaluate_ct(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *ct = *expr;

	ct_expr_update_type(&ctx->pctx, ct);

	return expr_evaluate_primary(ctx, expr);
}

/*
 * Prefix expression: the argument must be a constant value of integer base
 * type; the prefix length must be less than or equal to the type width.
 */
static int expr_evaluate_prefix(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *prefix = *expr, *base, *and, *mask;

	if (expr_evaluate(ctx, &prefix->prefix) < 0)
		return -1;
	base = prefix->prefix;

	if (!expr_is_constant(base))
		return expr_error(ctx->msgs, prefix,
				  "Prefix expression is undefined for "
				  "non-constant expressions");

	if (expr_basetype(base)->type != TYPE_INTEGER)
		return expr_error(ctx->msgs, prefix,
				  "Prefix expression is undefined for "
				  "%s types", base->dtype->desc);

	if (prefix->prefix_len > base->len)
		return expr_error(ctx->msgs, prefix,
				  "Prefix length %u is invalid for type "
				  "of %u bits width",
				  prefix->prefix_len, base->len);

	/* Clear the uncovered bits of the base value */
	mask = constant_expr_alloc(&prefix->location, &integer_type,
				   BYTEORDER_HOST_ENDIAN, base->len, NULL);
	mpz_prefixmask(mask->value, base->len, prefix->prefix_len);
	and  = binop_expr_alloc(&prefix->location, OP_AND, base, mask);

	prefix->prefix = and;
	if (expr_evaluate(ctx, &prefix->prefix) < 0)
		return -1;
	base = prefix->prefix;
	assert(expr_is_constant(base));

	prefix->dtype	  = base->dtype;
	prefix->byteorder = base->byteorder;
	prefix->len	  = base->len;
	prefix->flags	 |= EXPR_F_CONSTANT;
	return 0;
}

/*
 * Range expression: both sides must be constants of integer base type.
 */
static int expr_evaluate_range_expr(struct eval_ctx *ctx,
				    const struct expr *range,
				    struct expr **expr)
{
	if (expr_evaluate(ctx, expr) < 0)
		return -1;

	if (expr_basetype(*expr)->type != TYPE_INTEGER)
		return expr_binary_error(ctx->msgs, *expr, range,
					 "Range expression is undefined for "
					 "%s types", (*expr)->dtype->desc);
	if (!expr_is_constant(*expr))
		return expr_binary_error(ctx->msgs, *expr, range,
					 "Range is not constant");
	return 0;
}

static int expr_evaluate_range(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *range = *expr, *left, *right;

	if (expr_evaluate_range_expr(ctx, range, &range->left) < 0)
		return -1;
	left = range->left;

	if (expr_evaluate_range_expr(ctx, range, &range->right) < 0)
		return -1;
	right = range->right;

	if (mpz_cmp(left->value, right->value) >= 0)
		return expr_error(ctx->msgs, range,
				  "Range has zero or negative size");

	range->dtype = left->dtype;
	range->flags |= EXPR_F_CONSTANT;
	return 0;
}

/*
 * Unary expressions: unary expressions are only generated internally for
 * byteorder conversion of non-constant numerical expressions.
 */
static int expr_evaluate_unary(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *unary = *expr, *arg;
	enum byteorder byteorder;

	if (expr_evaluate(ctx, &unary->arg) < 0)
		return -1;
	arg = unary->arg;

	assert(!expr_is_constant(arg));
	assert(expr_basetype(arg)->type == TYPE_INTEGER);
	assert(arg->ops->type != EXPR_UNARY);

	switch (unary->op) {
	case OP_HTON:
		assert(arg->byteorder == BYTEORDER_HOST_ENDIAN);
		byteorder = BYTEORDER_BIG_ENDIAN;
		break;
	case OP_NTOH:
		assert(arg->byteorder == BYTEORDER_BIG_ENDIAN);
		byteorder = BYTEORDER_HOST_ENDIAN;
		break;
	default:
		BUG("invalid unary operation %u\n", unary->op);
	}

	unary->dtype	 = arg->dtype;
	unary->byteorder = byteorder;
	unary->len	 = arg->len;
	return 0;
}

/*
 * Binops
 */
static int constant_binop_simplify(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *op = *expr, *left = (*expr)->left, *right = (*expr)->right;
	struct expr *new;
	mpz_t val, mask;

	assert(left->ops->type == EXPR_VALUE);
	assert(right->ops->type == EXPR_VALUE);
	assert(left->byteorder == right->byteorder);

	mpz_init2(val, op->len);
	mpz_init_bitmask(mask, op->len);

	switch (op->op) {
	case OP_AND:
		mpz_and(val, left->value, right->value);
		mpz_and(val, val, mask);
		break;
	case OP_XOR:
		mpz_xor(val, left->value, right->value);
		mpz_and(val, val, mask);
		break;
	case OP_OR:
		mpz_ior(val, left->value, right->value);
		mpz_and(val, val, mask);
		break;
	case OP_LSHIFT:
		assert(left->byteorder == BYTEORDER_HOST_ENDIAN);
		mpz_lshift_ui(val, mpz_get_uint32(right->value));
		mpz_and(val, val, mask);
		break;
	case OP_RSHIFT:
		assert(left->byteorder == BYTEORDER_HOST_ENDIAN);
		mpz_set(val, left->value);
		mpz_and(val, val, mask);
		mpz_rshift_ui(val, mpz_get_uint32(right->value));
		break;
	default:
		BUG("invalid binary operation %u\n", op->op);
	}

	new = constant_expr_alloc(&op->location, op->dtype, op->byteorder,
				  op->len, NULL);
	mpz_set(new->value, val);

	expr_free(*expr);
	*expr = new;

	mpz_clear(mask);
	mpz_clear(val);

	return expr_evaluate(ctx, expr);
}

static int expr_evaluate_shift(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *op = *expr, *left = op->left, *right = op->right;

	if (mpz_get_uint32(right->value) >= left->len)
		return expr_binary_error(ctx->msgs, right, left,
					 "%s shift of %u bits is undefined "
					 "for type of %u bits width",
					 op->op == OP_LSHIFT ? "Left" : "Right",
					 mpz_get_uint32(right->value),
					 left->len);

	/* Both sides need to be in host byte order */
	if (byteorder_conversion(ctx, &op->left, BYTEORDER_HOST_ENDIAN) < 0)
		return -1;
	left = op->left;
	if (byteorder_conversion(ctx, &op->right, BYTEORDER_HOST_ENDIAN) < 0)
		return -1;

	op->dtype     = &integer_type;
	op->byteorder = BYTEORDER_HOST_ENDIAN;
	op->len       = left->len;

	if (expr_is_constant(left))
		return constant_binop_simplify(ctx, expr);
	return 0;
}

static int expr_evaluate_bitwise(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *op = *expr, *left = op->left;

	if (byteorder_conversion(ctx, &op->right, left->byteorder) < 0)
		return -1;

	op->dtype     = left->dtype;
	op->byteorder = left->byteorder;
	op->len	      = left->len;

	if (expr_is_constant(left))
		return constant_binop_simplify(ctx, expr);
	return 0;
}

/*
 * Binop expression: both sides must be of integer base type. The left
 * hand side may be either constant or non-constant; in case its constant
 * it must be a singleton. The ride hand side must always be a constant
 * singleton.
 */
static int expr_evaluate_binop(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *op = *expr, *left, *right;
	const char *sym = expr_op_symbols[op->op];

	if (expr_evaluate(ctx, &op->left) < 0)
		return -1;
	left = op->left;

	if (op->op == OP_LSHIFT || op->op == OP_RSHIFT)
		expr_set_context(&ctx->ectx, &integer_type, ctx->ectx.len);
	if (expr_evaluate(ctx, &op->right) < 0)
		return -1;
	right = op->right;

	if (expr_basetype(left)->type != TYPE_INTEGER)
		return expr_binary_error(ctx->msgs, left, op,
					 "Binary operation (%s) is undefined "
					 "for %s types",
					 sym, left->dtype->desc);

	if (expr_is_constant(left) && !expr_is_singleton(left))
		return expr_binary_error(ctx->msgs, left, op,
					 "Binary operation (%s) is undefined "
					 "for %s expressions",
					 sym, left->ops->name);

	if (!expr_is_constant(right))
		return expr_binary_error(ctx->msgs, right, op,
					 "Right hand side of binary operation "
					 "(%s) must be constant", sym);

	if (!expr_is_singleton(right))
		return expr_binary_error(ctx->msgs, left, op,
					 "Binary operation (%s) is undefined "
					 "for %s expressions",
					 sym, right->ops->name);

	/* The grammar guarantees this */
	assert(expr_basetype(left) == expr_basetype(right));

	switch (op->op) {
	case OP_LSHIFT:
	case OP_RSHIFT:
		return expr_evaluate_shift(ctx, expr);
	case OP_AND:
	case OP_XOR:
	case OP_OR:
		return expr_evaluate_bitwise(ctx, expr);
	default:
		BUG("invalid binary operation %u\n", op->op);
	}
}

static int list_member_evaluate(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *next = list_entry((*expr)->list.next, struct expr, list);
	int err;

	assert(*expr != next);
	list_del(&(*expr)->list);
	err = expr_evaluate(ctx, expr);
	list_add_tail(&(*expr)->list, &next->list);
	return err;
}

static int expr_evaluate_concat(struct eval_ctx *ctx, struct expr **expr)
{
	const struct datatype *dtype = ctx->ectx.dtype, *tmp;
	unsigned int type = dtype ? dtype->type : 0;
	int off = dtype ? dtype->size: 0;
	unsigned int flags = EXPR_F_CONSTANT | EXPR_F_SINGLETON;
	struct expr *i, *next;
	unsigned int n;

	n = 1;
	list_for_each_entry_safe(i, next, &(*expr)->expressions, list) {
		if (dtype && off == 0)
			return expr_binary_error(ctx->msgs, i, *expr,
						 "unexpected concat component, "
						 "expecting %s",
						 dtype->desc);
		tmp = datatype_lookup((type >> 8 * --off) & 0xff);
		expr_set_context(&ctx->ectx, tmp, tmp->size);

		if (list_member_evaluate(ctx, &i) < 0)
			return -1;
		flags &= i->flags;

		n++;
	}

	(*expr)->flags |= flags;
	(*expr)->dtype = concat_type_alloc(*expr);

	if (off > 0)
		return expr_error(ctx->msgs, *expr,
				  "datatype mismatch, expected %s, "
				  "expression has type %s",
				  dtype->desc, (*expr)->dtype->desc);

	expr_set_context(&ctx->ectx, (*expr)->dtype, (*expr)->len);

	return 0;
}

static int expr_evaluate_list(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *list = *expr, *new, *i, *next;
	mpz_t val;

	mpz_init_set_ui(val, 0);
	list_for_each_entry_safe(i, next, &list->expressions, list) {
		if (list_member_evaluate(ctx, &i) < 0)
			return -1;
		if (i->ops->type != EXPR_VALUE)
			return expr_error(ctx->msgs, i,
					  "List member must be a constant "
					  "value");
		if (i->dtype->basetype->type != TYPE_BITMASK)
			return expr_error(ctx->msgs, i,
					  "Basetype of type %s is not bitmask",
					  i->dtype->desc);
		mpz_ior(val, val, i->value);
	}

	new = constant_expr_alloc(&list->location, ctx->ectx.dtype,
				  BYTEORDER_HOST_ENDIAN, ctx->ectx.len, NULL);
	mpz_set(new->value, val);
	mpz_clear(val);

	expr_free(*expr);
	*expr = new;
	return 0;
}

static int expr_evaluate_set(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *set = *expr, *i, *next;

	list_for_each_entry_safe(i, next, &set->expressions, list) {
		if (list_member_evaluate(ctx, &i) < 0)
			return -1;

		if (!expr_is_constant(i))
			return expr_error(ctx->msgs, i,
					  "Set member is not constant");

		if (i->ops->type == EXPR_SET) {
			/* Merge recursive set definitions */
			list_splice_tail_init(&i->expressions, &i->list);
			list_del(&i->list);
			set->size      += i->size;
			set->set_flags |= i->set_flags;
			expr_free(i);
		} else if (!expr_is_singleton(i))
			set->set_flags |= SET_F_INTERVAL;
	}

	set->dtype = ctx->ectx.dtype;
	set->len   = ctx->ectx.len;
	set->flags |= EXPR_F_CONSTANT;
	return 0;
}

static int expr_evaluate_map(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr_ctx ectx = ctx->ectx;
	struct expr *map = *expr, *mappings;

	expr_set_context(&ctx->ectx, NULL, 0);
	if (expr_evaluate(ctx, &map->map) < 0)
		return -1;
	if (expr_is_constant(map->map))
		return expr_error(ctx->msgs, map->map,
				  "Map expression can not be constant");

	mappings = map->mappings;
	mappings->set_flags |= SET_F_MAP;

	switch (map->mappings->ops->type) {
	case EXPR_SET:
		mappings = implicit_set_declaration(ctx, ctx->ectx.dtype,
						    ctx->ectx.len, mappings);
		mappings->set->datatype = ectx.dtype;
		mappings->set->datalen  = ectx.len;

		map->mappings = mappings;

		ctx->set = mappings->set;
		if (expr_evaluate(ctx, &map->mappings->set->init) < 0)
			return -1;
		ctx->set = NULL;

		map->mappings->set->flags |= map->mappings->set->init->set_flags;
		break;
	case EXPR_SYMBOL:
		if (expr_evaluate(ctx, &map->mappings) < 0)
			return -1;
		if (map->mappings->ops->type != EXPR_SET_REF)
			return expr_error(ctx->msgs, map->mappings,
					  "Expression is not a map");
		break;
	default:
		BUG("invalid mapping expression %s\n",
		    map->mappings->ops->name);
	}

	map->dtype = ctx->ectx.dtype;
	map->flags |= EXPR_F_CONSTANT;

	/* Data for range lookups needs to be in big endian order */
	if (map->mappings->set->flags & SET_F_INTERVAL &&
	    byteorder_conversion(ctx, &map->map, BYTEORDER_BIG_ENDIAN) < 0)
		return -1;

	return 0;
}

static int expr_evaluate_mapping(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *mapping = *expr;
	struct set *set = ctx->set;

	if (set == NULL)
		return expr_error(ctx->msgs, mapping,
				  "mapping outside of map context");
	if (!(set->flags & SET_F_MAP))
		return set_error(ctx, set, "set is not a map");

	expr_set_context(&ctx->ectx, set->keytype, set->keylen);
	if (expr_evaluate(ctx, &mapping->left) < 0)
		return -1;
	if (!expr_is_constant(mapping->left))
		return expr_error(ctx->msgs, mapping->left,
				  "Key must be a constant");
	mapping->flags |= mapping->left->flags & EXPR_F_SINGLETON;

	expr_set_context(&ctx->ectx, set->datatype, set->datalen);
	if (expr_evaluate(ctx, &mapping->right) < 0)
		return -1;
	if (!expr_is_constant(mapping->right))
		return expr_error(ctx->msgs, mapping->right,
				  "Value must be a constant");
	if (!expr_is_singleton(mapping->right))
		return expr_error(ctx->msgs, mapping->right,
				  "Value must be a singleton");

	mapping->flags |= EXPR_F_CONSTANT;
	return 0;
}

/*
 * Transfer the invertible binops to the constant side of an equality
 * expression. A left shift is only invertible if the low n bits are
 * zero.
 */
static int binop_can_transfer(struct eval_ctx *ctx,
			      struct expr *left, struct expr *right)
{
	switch (left->op) {
	case OP_LSHIFT:
		if (mpz_scan1(right->value, 0) < mpz_get_uint32(left->right->value))
			return expr_binary_error(ctx->msgs, right, left,
						 "Comparison is always false");
		return 1;
	case OP_XOR:
		return 1;
	default:
		return 0;
	}
}

static int binop_transfer_one(struct eval_ctx *ctx,
			      const struct expr *left, struct expr **right)
{
	expr_get(*right);

	switch (left->op) {
	case OP_LSHIFT:
		(*right) = binop_expr_alloc(&(*right)->location, OP_RSHIFT,
					    *right, expr_get(left->right));
		break;
	case OP_XOR:
		(*right) = binop_expr_alloc(&(*right)->location, OP_XOR,
					    *right, expr_get(left->right));
		break;
	default:
		BUG("invalid binary operation %u\n", left->op);
	}

	return expr_evaluate(ctx, right);
}

static int binop_transfer(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *left = (*expr)->left, *i, *next;
	int err;

	if (left->ops->type != EXPR_BINOP)
		return 0;

	switch ((*expr)->right->ops->type) {
	case EXPR_VALUE:
		err = binop_can_transfer(ctx, left, (*expr)->right);
		if (err <= 0)
			return err;
		if (binop_transfer_one(ctx, left, &(*expr)->right) < 0)
			return -1;
		break;
	case EXPR_SET:
		list_for_each_entry(i, &(*expr)->right->expressions, list) {
			err = binop_can_transfer(ctx, left, i);
			if (err <= 0)
				return err;
		}
		list_for_each_entry_safe(i, next, &(*expr)->right->expressions,
					 list) {
			list_del(&i->list);
			if (binop_transfer_one(ctx, left, &i) < 0)
				return -1;
			list_add_tail(&i->list, &next->list);
		}
		break;
	default:
		return 0;
	}

	left = expr_get((*expr)->left->left);
	left->dtype = (*expr)->left->dtype;
	expr_free((*expr)->left);
	(*expr)->left = left;
	return 0;
}

static int expr_evaluate_relational(struct eval_ctx *ctx, struct expr **expr)
{
	struct expr *rel = *expr, *left, *right;

	if (expr_evaluate(ctx, &rel->left) < 0)
		return -1;
	left = rel->left;

	if (expr_evaluate(ctx, &rel->right) < 0)
		return -1;
	right = rel->right;

	if (rel->op == OP_IMPLICIT) {
		switch (right->ops->type) {
		case EXPR_RANGE:
			rel->op = OP_RANGE;
			break;
		case EXPR_SET:
		case EXPR_SET_REF:
			rel->op = OP_LOOKUP;
			break;
		case EXPR_LIST:
			rel->op = OP_FLAGCMP;
			break;
		default:
			if (right->dtype->basetype != NULL &&
			    right->dtype->basetype->type == TYPE_BITMASK)
				rel->op = OP_FLAGCMP;
			else
				rel->op = OP_EQ;
			break;
		}
	}

	if (!expr_is_constant(right))
		return expr_binary_error(ctx->msgs, right, rel,
					 "Right hand side of relational "
					 "expression (%s) must be constant",
					 expr_op_symbols[rel->op]);
	if (expr_is_constant(left))
		return expr_binary_error(ctx->msgs, left, right,
					 "Relational expression (%s) has "
					 "constant value",
					 expr_op_symbols[rel->op]);

	switch (rel->op) {
	case OP_LOOKUP:
		/* A literal set expression implicitly declares the set */
		if (right->ops->type == EXPR_SET)
			right = rel->right =
				implicit_set_declaration(ctx, left->dtype, left->len, right);
		else if (!datatype_equal(left->dtype, right->dtype))
			return expr_binary_error(ctx->msgs, right, left,
						 "datatype mismatch, expected %s, "
						 "set has type %s",
						 left->dtype->desc,
						 right->dtype->desc);

		/* Data for range lookups needs to be in big endian order */
		if (right->set->flags & SET_F_INTERVAL &&
		    byteorder_conversion(ctx, &rel->left,
					 BYTEORDER_BIG_ENDIAN) < 0)
			return -1;
		left = rel->left;
		break;
	case OP_EQ:
		if (!datatype_equal(left->dtype, right->dtype))
			return expr_binary_error(ctx->msgs, right, left,
						 "datatype mismatch, expected %s, "
						 "expression has type %s",
						 left->dtype->desc,
						 right->dtype->desc);
		/*
		 * Update protocol context for payload and meta iiftype
		 * equality expressions.
		 */
		if (left->flags & EXPR_F_PROTOCOL &&
		    left->ops->pctx_update)
			left->ops->pctx_update(&ctx->pctx, rel);

		if (left->ops->type == EXPR_CONCAT)
			return 0;

		/* fall through */
	case OP_NEQ:
	case OP_FLAGCMP:
		if (!datatype_equal(left->dtype, right->dtype))
			return expr_binary_error(ctx->msgs, right, left,
						 "datatype mismatch, expected %s, "
						 "expression has type %s",
						 left->dtype->desc,
						 right->dtype->desc);

		switch (right->ops->type) {
		case EXPR_RANGE:
			goto range;
		case EXPR_PREFIX:
			if (byteorder_conversion(ctx, &right->prefix, left->byteorder) < 0)
				return -1;
			break;
		case EXPR_VALUE:
			if (byteorder_conversion(ctx, &rel->right, left->byteorder) < 0)
				return -1;
			break;
		default:
			BUG("invalid expression type %s\n", right->ops->name);
		}
		break;
	case OP_LT:
	case OP_GT:
	case OP_LTE:
	case OP_GTE:
		if (!datatype_equal(left->dtype, right->dtype))
			return expr_binary_error(ctx->msgs, right, left,
						 "datatype mismatch, expected %s, "
						 "expression has type %s",
						 left->dtype->desc,
						 right->dtype->desc);

		switch (left->ops->type) {
		case EXPR_CONCAT:
			return expr_binary_error(ctx->msgs, left, rel,
					"Relational expression (%s) is undefined "
				        "for %s expressions",
					expr_op_symbols[rel->op],
					left->ops->name);
		default:
			break;
		}

		if (!expr_is_singleton(right))
			return expr_binary_error(ctx->msgs, right, rel,
					"Relational expression (%s) is undefined "
				        "for %s expressions",
					expr_op_symbols[rel->op],
					right->ops->name);

		if (byteorder_conversion(ctx, &rel->left, BYTEORDER_BIG_ENDIAN) < 0)
			return -1;
		if (byteorder_conversion(ctx, &rel->right, BYTEORDER_BIG_ENDIAN) < 0)
			return -1;
		break;
	case OP_RANGE:
		if (!datatype_equal(left->dtype, right->dtype))
			return expr_binary_error(ctx->msgs, right, left,
						 "datatype mismatch, expected %s, "
						 "expression has type %s",
						 left->dtype->desc,
						 right->dtype->desc);

range:
		switch (left->ops->type) {
		case EXPR_CONCAT:
			return expr_binary_error(ctx->msgs, left, rel,
					"Relational expression (%s) is undefined"
				        "for %s expressions",
					expr_op_symbols[rel->op],
					left->ops->name);
		default:
			break;
		}

		if (byteorder_conversion(ctx, &rel->left, BYTEORDER_BIG_ENDIAN) < 0)
			return -1;
		if (byteorder_conversion(ctx, &right->left, BYTEORDER_BIG_ENDIAN) < 0)
			return -1;
		if (byteorder_conversion(ctx, &right->right, BYTEORDER_BIG_ENDIAN) < 0)
			return -1;
		break;
	default:
		BUG("invalid relational operation %u\n", rel->op);
	}

	if (binop_transfer(ctx, expr) < 0)
		return -1;

	return 0;
}

static int expr_evaluate(struct eval_ctx *ctx, struct expr **expr)
{
#ifdef DEBUG
	if (debug_level & DEBUG_EVALUATION) {
		struct error_record *erec;
		erec = erec_create(EREC_INFORMATIONAL, &(*expr)->location, "Evaluate");
		erec_print(stdout, erec); expr_print(*expr); printf("\n\n");
	}
#endif

	switch ((*expr)->ops->type) {
	case EXPR_SYMBOL:
		return expr_evaluate_symbol(ctx, expr);
	case EXPR_SET_REF:
		return 0;
	case EXPR_VALUE:
		return expr_evaluate_value(ctx, expr);
	case EXPR_VERDICT:
	case EXPR_EXTHDR:
	case EXPR_META:
		return expr_evaluate_primary(ctx, expr);
	case EXPR_PAYLOAD:
		return expr_evaluate_payload(ctx, expr);
	case EXPR_CT:
		return expr_evaluate_ct(ctx, expr);
	case EXPR_PREFIX:
		return expr_evaluate_prefix(ctx, expr);
	case EXPR_RANGE:
		return expr_evaluate_range(ctx, expr);
	case EXPR_UNARY:
		return expr_evaluate_unary(ctx, expr);
	case EXPR_BINOP:
		return expr_evaluate_binop(ctx, expr);
	case EXPR_CONCAT:
		return expr_evaluate_concat(ctx, expr);
	case EXPR_LIST:
		return expr_evaluate_list(ctx, expr);
	case EXPR_SET:
		return expr_evaluate_set(ctx, expr);
	case EXPR_MAP:
		return expr_evaluate_map(ctx, expr);
	case EXPR_MAPPING:
		return expr_evaluate_mapping(ctx, expr);
	case EXPR_RELATIONAL:
		return expr_evaluate_relational(ctx, expr);
	default:
		BUG("unknown expression type %s\n", (*expr)->ops->name);
	}
}

static int stmt_evaluate_expr(struct eval_ctx *ctx, struct stmt *stmt)
{
	memset(&ctx->ectx, 0, sizeof(ctx->ectx));
	return expr_evaluate(ctx, &stmt->expr);
}

static int stmt_evaluate_verdict(struct eval_ctx *ctx, struct stmt *stmt)
{
	expr_set_context(&ctx->ectx, &verdict_type, 0);
	if (expr_evaluate(ctx, &stmt->expr) < 0)
		return -1;

	switch (stmt->expr->ops->type) {
	case EXPR_VERDICT:
		if (stmt->expr->verdict != NFT_CONTINUE)
			stmt->flags |= STMT_F_TERMINAL;
		break;
	case EXPR_MAP:
		break;
	default:
		BUG("invalid verdict expression %s\n", stmt->expr->ops->name);
	}
	return 0;
}

static int stmt_evaluate_meta(struct eval_ctx *ctx, struct stmt *stmt)
{
	expr_set_context(&ctx->ectx, stmt->meta.tmpl->dtype,
			 stmt->meta.tmpl->len);
	if (expr_evaluate(ctx, &stmt->meta.expr) < 0)
		return -1;
	return 0;
}

static int reject_payload_gen_dependency_tcp(struct eval_ctx *ctx,
					     struct stmt *stmt,
					     struct expr **payload)
{
	const struct proto_desc *desc;

	desc = ctx->pctx.protocol[PROTO_BASE_TRANSPORT_HDR].desc;
	if (desc != NULL)
		return 0;
	*payload = payload_expr_alloc(&stmt->location, &proto_tcp,
				      TCPHDR_UNSPEC);
	return 1;
}

static int reject_payload_gen_dependency_family(struct eval_ctx *ctx,
						struct stmt *stmt,
						struct expr **payload)
{
	const struct proto_desc *base;

	base = ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR].desc;
	if (base != NULL)
		return 0;

	if (stmt->reject.icmp_code < 0)
		return stmt_error(ctx, stmt, "missing icmp error type");

	/* Generate a network dependency */
	switch (stmt->reject.family) {
	case NFPROTO_IPV4:
		*payload = payload_expr_alloc(&stmt->location, &proto_ip,
					     IPHDR_PROTOCOL);
		break;
	case NFPROTO_IPV6:
		*payload = payload_expr_alloc(&stmt->location, &proto_ip6,
					     IP6HDR_NEXTHDR);
		break;
	default:
		BUG("unknown reject family");
	}
	return 1;
}

static int stmt_reject_gen_dependency(struct eval_ctx *ctx, struct stmt *stmt,
				      struct expr *expr)
{
	struct expr *payload = NULL;
	struct stmt *nstmt;
	int ret;

	switch (stmt->reject.type) {
	case NFT_REJECT_TCP_RST:
		ret = reject_payload_gen_dependency_tcp(ctx, stmt, &payload);
		break;
	case NFT_REJECT_ICMP_UNREACH:
		ret = reject_payload_gen_dependency_family(ctx, stmt, &payload);
		break;
	default:
		BUG("cannot generate reject dependency for type %d",
		    stmt->reject.type);
	}
	if (ret <= 0)
		return ret;

	if (payload_gen_dependency(ctx, payload, &nstmt) < 0)
		return -1;

	list_add(&nstmt->list, &ctx->cmd->rule->stmts);
	return 0;
}

static int stmt_evaluate_reject_inet_family(struct eval_ctx *ctx,
					    struct stmt *stmt,
					    const struct proto_desc *desc)
{
	const struct proto_desc *base;
	int protocol;

	switch (stmt->reject.type) {
	case NFT_REJECT_TCP_RST:
		break;
	case NFT_REJECT_ICMPX_UNREACH:
		return stmt_binary_error(ctx, stmt->reject.expr,
				    &ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR],
				    "conflicting network protocol specified");
	case NFT_REJECT_ICMP_UNREACH:
		base = ctx->pctx.protocol[PROTO_BASE_LL_HDR].desc;
		protocol = proto_find_num(base, desc);
		switch (protocol) {
		case NFPROTO_IPV4:
			if (stmt->reject.family == NFPROTO_IPV4)
				break;
			return stmt_binary_error(ctx, stmt->reject.expr,
				  &ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR],
				  "conflicting protocols specified: ip vs ip6");
		case NFPROTO_IPV6:
			if (stmt->reject.family == NFPROTO_IPV6)
				break;
			return stmt_binary_error(ctx, stmt->reject.expr,
				  &ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR],
				  "conflicting protocols specified: ip vs ip6");
		default:
			BUG("unsupported family");
		}
		break;
	}

	return 0;
}

static int stmt_evaluate_reject_inet(struct eval_ctx *ctx, struct stmt *stmt,
				     struct expr *expr)
{
	const struct proto_desc *desc;

	desc = ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR].desc;
	if (desc != NULL &&
	    stmt_evaluate_reject_inet_family(ctx, stmt, desc) < 0)
		return -1;
	if (stmt->reject.type == NFT_REJECT_ICMPX_UNREACH)
		return 0;
	if (stmt_reject_gen_dependency(ctx, stmt, expr) < 0)
		return -1;
	return 0;
}

static int stmt_evaluate_reject_bridge_family(struct eval_ctx *ctx,
					      struct stmt *stmt,
					      const struct proto_desc *desc)
{
	const struct proto_desc *base;
	int protocol;

	switch (stmt->reject.type) {
	case NFT_REJECT_ICMPX_UNREACH:
		return stmt_binary_error(ctx, stmt->reject.expr,
				    &ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR],
				    "conflicting network protocol specified");
	case NFT_REJECT_TCP_RST:
		base = ctx->pctx.protocol[PROTO_BASE_LL_HDR].desc;
		protocol = proto_find_num(base, desc);
		switch (protocol) {
		case __constant_htons(ETH_P_IP):
		case __constant_htons(ETH_P_IPV6):
			break;
		default:
			return stmt_binary_error(ctx, stmt,
				    &ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR],
				    "cannot reject this ether type");
		}
		break;
	case NFT_REJECT_ICMP_UNREACH:
		base = ctx->pctx.protocol[PROTO_BASE_LL_HDR].desc;
		protocol = proto_find_num(base, desc);
		switch (protocol) {
		case __constant_htons(ETH_P_IP):
			if (NFPROTO_IPV4 == stmt->reject.family)
				break;
			return stmt_binary_error(ctx, stmt->reject.expr,
				  &ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR],
				  "conflicting protocols specified: ip vs ip6");
		case __constant_htons(ETH_P_IPV6):
			if (NFPROTO_IPV6 == stmt->reject.family)
				break;
			return stmt_binary_error(ctx, stmt->reject.expr,
				  &ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR],
				  "conflicting protocols specified: ip vs ip6");
		default:
			return stmt_binary_error(ctx, stmt,
				    &ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR],
				    "cannot reject this ether type");
		}
		break;
	}

	return 0;
}

static int stmt_evaluate_reject_bridge(struct eval_ctx *ctx, struct stmt *stmt,
				       struct expr *expr)
{
	const struct proto_desc *desc;

	desc = ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR].desc;
	if (desc != NULL &&
	    stmt_evaluate_reject_bridge_family(ctx, stmt, desc) < 0)
		return -1;
	if (stmt->reject.type == NFT_REJECT_ICMPX_UNREACH)
		return 0;
	if (stmt_reject_gen_dependency(ctx, stmt, expr) < 0)
		return -1;
	return 0;
}

static int stmt_evaluate_reject_family(struct eval_ctx *ctx, struct stmt *stmt,
				       struct expr *expr)
{
	switch (ctx->pctx.family) {
	case NFPROTO_ARP:
		return stmt_error(ctx, stmt, "cannot use reject with arp");
	case NFPROTO_IPV4:
	case NFPROTO_IPV6:
		switch (stmt->reject.type) {
		case NFT_REJECT_TCP_RST:
			if (stmt_reject_gen_dependency(ctx, stmt, expr) < 0)
				return -1;
			break;
		case NFT_REJECT_ICMPX_UNREACH:
			return stmt_binary_error(ctx, stmt->reject.expr, stmt,
				   "abstracted ICMP unreachable not supported");
		case NFT_REJECT_ICMP_UNREACH:
			if (stmt->reject.family == ctx->pctx.family)
				break;
			return stmt_binary_error(ctx, stmt->reject.expr, stmt,
				  "conflicting protocols specified: ip vs ip6");
		}
		break;
	case NFPROTO_BRIDGE:
		if (stmt_evaluate_reject_bridge(ctx, stmt, expr) < 0)
			return -1;
		break;
	case NFPROTO_INET:
		if (stmt_evaluate_reject_inet(ctx, stmt, expr) < 0)
			return -1;
		break;
	}

	stmt->flags |= STMT_F_TERMINAL;
	return 0;
}

static int stmt_evaluate_reject_default(struct eval_ctx *ctx,
					  struct stmt *stmt)
{
	int protocol;
	const struct proto_desc *desc, *base;

	switch (ctx->pctx.family) {
	case NFPROTO_IPV4:
	case NFPROTO_IPV6:
		stmt->reject.type = NFT_REJECT_ICMP_UNREACH;
		stmt->reject.family = ctx->pctx.family;
		if (ctx->pctx.family == NFPROTO_IPV4)
			stmt->reject.icmp_code = ICMP_PORT_UNREACH;
		else
			stmt->reject.icmp_code = ICMP6_DST_UNREACH_NOPORT;
		break;
	case NFPROTO_INET:
		desc = ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR].desc;
		if (desc == NULL) {
			stmt->reject.type = NFT_REJECT_ICMPX_UNREACH;
			stmt->reject.icmp_code = NFT_REJECT_ICMPX_PORT_UNREACH;
			break;
		}
		stmt->reject.type = NFT_REJECT_ICMP_UNREACH;
		base = ctx->pctx.protocol[PROTO_BASE_LL_HDR].desc;
		protocol = proto_find_num(base, desc);
		switch (protocol) {
		case NFPROTO_IPV4:
			stmt->reject.family = NFPROTO_IPV4;
			stmt->reject.icmp_code = ICMP_PORT_UNREACH;
			break;
		case NFPROTO_IPV6:
			stmt->reject.family = NFPROTO_IPV6;
			stmt->reject.icmp_code = ICMP6_DST_UNREACH_NOPORT;
			break;
		}
		break;
	case NFPROTO_BRIDGE:
		desc = ctx->pctx.protocol[PROTO_BASE_NETWORK_HDR].desc;
		if (desc == NULL) {
			stmt->reject.type = NFT_REJECT_ICMPX_UNREACH;
			stmt->reject.icmp_code = NFT_REJECT_ICMPX_PORT_UNREACH;
			break;
		}
		stmt->reject.type = NFT_REJECT_ICMP_UNREACH;
		base = ctx->pctx.protocol[PROTO_BASE_LL_HDR].desc;
		protocol = proto_find_num(base, desc);
		switch (protocol) {
		case __constant_htons(ETH_P_IP):
			stmt->reject.family = NFPROTO_IPV4;
			stmt->reject.icmp_code = ICMP_PORT_UNREACH;
			break;
		case __constant_htons(ETH_P_IPV6):
			stmt->reject.family = NFPROTO_IPV6;
			stmt->reject.icmp_code = ICMP6_DST_UNREACH_NOPORT;
			break;
		}
		break;
	}
	return 0;
}

static int stmt_evaluate_reject_icmp(struct eval_ctx *ctx, struct stmt *stmt)
{
	struct error_record *erec;
	struct expr *code;

	erec = symbol_parse(stmt->reject.expr, &code);
	if (erec != NULL) {
		erec_queue(erec, ctx->msgs);
		return -1;
	}
	stmt->reject.icmp_code = mpz_get_uint8(code->value);
	return 0;
}

static int stmt_evaluate_reset(struct eval_ctx *ctx, struct stmt *stmt)
{
	int protonum;
	const struct proto_desc *desc, *base;
	struct proto_ctx *pctx = &ctx->pctx;

	desc = pctx->protocol[PROTO_BASE_TRANSPORT_HDR].desc;
	if (desc == NULL)
		return 0;

	base = pctx->protocol[PROTO_BASE_NETWORK_HDR].desc;
	if (base == NULL &&
	    (ctx->pctx.family == NFPROTO_INET ||
	     ctx->pctx.family == NFPROTO_BRIDGE))
		base = &proto_inet_service;

	protonum = proto_find_num(base, desc);
	switch (protonum) {
	case IPPROTO_TCP:
		break;
	default:
		if (stmt->reject.type == NFT_REJECT_TCP_RST) {
			return stmt_binary_error(ctx, stmt,
				 &ctx->pctx.protocol[PROTO_BASE_TRANSPORT_HDR],
				 "you cannot use tcp reset with this protocol");
		}
		break;
	}
	return 0;
}

static int stmt_evaluate_reject(struct eval_ctx *ctx, struct stmt *stmt)
{
	struct expr *expr = ctx->cmd->expr;

	if (stmt->reject.icmp_code < 0) {
		if (stmt_evaluate_reject_default(ctx, stmt) < 0)
			return -1;
	} else if (stmt->reject.expr != NULL) {
		if (stmt_evaluate_reject_icmp(ctx, stmt) < 0)
			return -1;
	} else {
		if (stmt_evaluate_reset(ctx, stmt) < 0)
			return -1;
	}

	return stmt_evaluate_reject_family(ctx, stmt, expr);
}

static int stmt_evaluate_nat(struct eval_ctx *ctx, struct stmt *stmt)
{
	struct proto_ctx *pctx = &ctx->pctx;
	int err;

	if (stmt->nat.addr != NULL) {
		if (pctx && (pctx->family == AF_INET))
			expr_set_context(&ctx->ectx, &ipaddr_type,
					4 * BITS_PER_BYTE);
		else
			expr_set_context(&ctx->ectx, &ip6addr_type,
					 16 * BITS_PER_BYTE);
		err = expr_evaluate(ctx, &stmt->nat.addr);
		if (err < 0)
			return err;
	}

	if (stmt->nat.proto != NULL) {
		if (pctx->protocol[PROTO_BASE_TRANSPORT_HDR].desc == NULL)
			return stmt_binary_error(ctx, stmt->nat.proto, stmt,
						 "transport protocol mapping is only "
						 "valid after transport protocol match");

		expr_set_context(&ctx->ectx, &inet_service_type,
				 2 * BITS_PER_BYTE);
		err = expr_evaluate(ctx, &stmt->nat.proto);
		if (err < 0)
			return err;
	}

	stmt->flags |= STMT_F_TERMINAL;
	return 0;
}

static int stmt_evaluate_masq(struct eval_ctx *ctx, struct stmt *stmt)
{
	struct proto_ctx *pctx = &ctx->pctx;

	if (!pctx)
		goto out;

	switch (pctx->family) {
	case AF_INET:
		expr_set_context(&ctx->ectx, &ipaddr_type,
				4 * BITS_PER_BYTE);
		break;
	case AF_INET6:
		expr_set_context(&ctx->ectx, &ip6addr_type,
				 16 * BITS_PER_BYTE);
		break;
	default:
		return stmt_error(ctx, stmt, "ip and ip6 support only");
	}

out:
	stmt->flags |= STMT_F_TERMINAL;
	return 0;
}

static int stmt_evaluate_redir(struct eval_ctx *ctx, struct stmt *stmt)
{
	int err;
	struct proto_ctx *pctx = &ctx->pctx;

	if (!pctx)
		goto out;

	switch (pctx->family) {
	case AF_INET:
		expr_set_context(&ctx->ectx, &ipaddr_type,
				4 * BITS_PER_BYTE);
		break;
	case AF_INET6:
		expr_set_context(&ctx->ectx, &ip6addr_type,
				 16 * BITS_PER_BYTE);
		break;
	default:
		return stmt_error(ctx, stmt, "ip and ip6 support only");
	}

	if (stmt->redir.proto != NULL) {
		if (pctx->protocol[PROTO_BASE_TRANSPORT_HDR].desc == NULL)
			return stmt_binary_error(ctx, stmt->redir.proto, stmt,
						 "missing transport protocol match");

		expr_set_context(&ctx->ectx, &inet_service_type,
				 2 * BITS_PER_BYTE);
		err = expr_evaluate(ctx, &stmt->redir.proto);
		if (err < 0)
			return err;
	}

out:
	stmt->flags |= STMT_F_TERMINAL;
	return 0;
}

static int stmt_evaluate_ct(struct eval_ctx *ctx, struct stmt *stmt)
{
	expr_set_context(&ctx->ectx, stmt->ct.tmpl->dtype,
			 stmt->ct.tmpl->len);
	if (expr_evaluate(ctx, &stmt->ct.expr) < 0)
		return -1;
	return 0;
}

static int stmt_evaluate_queue(struct eval_ctx *ctx, struct stmt *stmt)
{
	if (stmt->queue.queue != NULL) {
		expr_set_context(&ctx->ectx, &integer_type, 16);
		if (expr_evaluate(ctx, &stmt->queue.queue) < 0)
			return -1;
		if (!expr_is_constant(stmt->queue.queue))
			return expr_error(ctx->msgs, stmt->queue.queue,
					  "queue number is not constant");
	}
	return 0;
}

static int stmt_evaluate_log(struct eval_ctx *ctx, struct stmt *stmt)
{
	if (stmt->log.flags & STMT_LOG_LEVEL &&
	    (stmt->log.flags & STMT_LOG_GROUP	||
	     stmt->log.flags & STMT_LOG_SNAPLEN	||
	     stmt->log.flags & STMT_LOG_QTHRESHOLD)) {
		return stmt_error(ctx, stmt,
				  "level and group are mutually exclusive");
	}
	return 0;
}

int stmt_evaluate(struct eval_ctx *ctx, struct stmt *stmt)
{
#ifdef DEBUG
	if (debug_level & DEBUG_EVALUATION) {
		struct error_record *erec;
		erec = erec_create(EREC_INFORMATIONAL, &stmt->location, "Evaluate");
		erec_print(stdout, erec); stmt_print(stmt); printf("\n\n");
	}
#endif

	switch (stmt->ops->type) {
	case STMT_COUNTER:
	case STMT_LIMIT:
		return 0;
	case STMT_EXPRESSION:
		return stmt_evaluate_expr(ctx, stmt);
	case STMT_VERDICT:
		return stmt_evaluate_verdict(ctx, stmt);
	case STMT_META:
		return stmt_evaluate_meta(ctx, stmt);
	case STMT_LOG:
		return stmt_evaluate_log(ctx, stmt);
	case STMT_REJECT:
		return stmt_evaluate_reject(ctx, stmt);
	case STMT_NAT:
		return stmt_evaluate_nat(ctx, stmt);
	case STMT_MASQ:
		return stmt_evaluate_masq(ctx, stmt);
	case STMT_REDIR:
		return stmt_evaluate_redir(ctx, stmt);
	case STMT_QUEUE:
		return stmt_evaluate_queue(ctx, stmt);
	case STMT_CT:
		return stmt_evaluate_ct(ctx, stmt);
	default:
		BUG("unknown statement type %s\n", stmt->ops->name);
	}
}

static int setelem_evaluate(struct eval_ctx *ctx, struct expr **expr)
{
	struct set *set;

	set = get_set(ctx, &ctx->cmd->handle, ctx->cmd->handle.set);
	if (set == NULL)
		return -1;

	ctx->set = set;
	expr_set_context(&ctx->ectx, set->keytype, set->keylen);
	if (expr_evaluate(ctx, expr) < 0)
		return -1;
	ctx->set = NULL;
	return 0;
}

static int set_evaluate(struct eval_ctx *ctx, struct set *set)
{
	const char *type;

	type = set->flags & SET_F_MAP ? "map" : "set";

	if (set->keytype == NULL)
		return set_error(ctx, set, "%s definition does not specify "
				 "key data type", type);

	set->keylen = set->keytype->size;
	if (set->keylen == 0)
		return set_error(ctx, set, "unqualified key data type "
				 "specified in %s definition", type);

	if (set->init != NULL) {
		expr_set_context(&ctx->ectx, set->keytype, set->keylen);
		if (expr_evaluate(ctx, &set->init) < 0)
			return -1;
	}

	if (!(set->flags & SET_F_MAP))
		return 0;

	if (set->datatype == NULL)
		return set_error(ctx, set, "map definition does not specify "
				 "mapping data type");

	set->datalen = set->datatype->size;
	if (set->datalen == 0 && set->datatype->type != TYPE_VERDICT)
		return set_error(ctx, set, "unqualified mapping data type "
				 "specified in map definition");

	return 0;
}

static int rule_evaluate(struct eval_ctx *ctx, struct rule *rule)
{
	struct stmt *stmt, *tstmt = NULL;
	struct error_record *erec;

	proto_ctx_init(&ctx->pctx, rule->handle.family);
	memset(&ctx->ectx, 0, sizeof(ctx->ectx));

	list_for_each_entry(stmt, &rule->stmts, list) {
		if (tstmt != NULL)
			return stmt_binary_error(ctx, stmt, tstmt,
						 "Statement after terminal "
						 "statement has no effect");

		ctx->stmt = stmt;
		if (stmt_evaluate(ctx, stmt) < 0)
			return -1;
		if (stmt->flags & STMT_F_TERMINAL)
			tstmt = stmt;
	}

	erec = rule_postprocess(rule);
	if (erec != NULL) {
		erec_queue(erec, ctx->msgs);
		return -1;
	}

	return 0;
}

static uint32_t str2hooknum(uint32_t family, const char *hook)
{
	switch (family) {
	case NFPROTO_IPV4:
	case NFPROTO_BRIDGE:
	case NFPROTO_IPV6:
	case NFPROTO_INET:
		/* These families have overlapping values for each hook */
		if (!strcmp(hook, "prerouting"))
			return NF_INET_PRE_ROUTING;
		else if (!strcmp(hook, "input"))
			return NF_INET_LOCAL_IN;
		else if (!strcmp(hook, "forward"))
			return NF_INET_FORWARD;
		else if (!strcmp(hook, "postrouting"))
			return NF_INET_POST_ROUTING;
		else if (!strcmp(hook, "output"))
			return NF_INET_LOCAL_OUT;
	case NFPROTO_ARP:
		if (!strcmp(hook, "input"))
			return NF_ARP_IN;
		else if (!strcmp(hook, "forward"))
			return NF_ARP_FORWARD;
		else if (!strcmp(hook, "output"))
			return NF_ARP_OUT;
	default:
		break;
	}

	return NF_INET_NUMHOOKS;
}

static int chain_evaluate(struct eval_ctx *ctx, struct chain *chain)
{
	struct rule *rule;

	if (chain->flags & CHAIN_F_BASECHAIN) {
		chain->hooknum = str2hooknum(chain->handle.family,
					     chain->hookstr);
		if (chain->hooknum == NF_INET_NUMHOOKS)
			return chain_error(ctx, chain, "invalid hook %s",
					   chain->hookstr);
	}

	list_for_each_entry(rule, &chain->rules, list) {
		handle_merge(&rule->handle, &chain->handle);
		if (rule_evaluate(ctx, rule) < 0)
			return -1;
	}
	return 0;
}

static int table_evaluate(struct eval_ctx *ctx, struct table *table)
{
	struct chain *chain;
	struct set *set;

	ctx->table = table;
	list_for_each_entry(set, &table->sets, list) {
		handle_merge(&set->handle, &table->handle);
		if (set_evaluate(ctx, set) < 0)
			return -1;
	}
	list_for_each_entry(chain, &table->chains, list) {
		handle_merge(&chain->handle, &table->handle);
		if (chain_evaluate(ctx, chain) < 0)
			return -1;
	}
	ctx->table = NULL;
	return 0;
}

static int cmd_evaluate_add(struct eval_ctx *ctx, struct cmd *cmd)
{
	switch (cmd->obj) {
	case CMD_OBJ_SETELEM:
		return setelem_evaluate(ctx, &cmd->expr);
	case CMD_OBJ_SET:
		handle_merge(&cmd->set->handle, &cmd->handle);
		return set_evaluate(ctx, cmd->set);
	case CMD_OBJ_RULE:
		handle_merge(&cmd->rule->handle, &cmd->handle);
		return rule_evaluate(ctx, cmd->rule);
	case CMD_OBJ_CHAIN:
		if (cmd->data == NULL)
			return 0;
		return chain_evaluate(ctx, cmd->chain);
	case CMD_OBJ_TABLE:
		if (cmd->data == NULL)
			return 0;
		return table_evaluate(ctx, cmd->table);
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}
}

static int cmd_evaluate_delete(struct eval_ctx *ctx, struct cmd *cmd)
{
	switch (cmd->obj) {
	case CMD_OBJ_SETELEM:
		return setelem_evaluate(ctx, &cmd->expr);
	case CMD_OBJ_SET:
	case CMD_OBJ_RULE:
	case CMD_OBJ_CHAIN:
	case CMD_OBJ_TABLE:
		return 0;
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}
}

enum {
	CMD_MONITOR_EVENT_ANY,
	CMD_MONITOR_EVENT_NEW,
	CMD_MONITOR_EVENT_DEL,
	CMD_MONITOR_EVENT_MAX
};

static uint32_t monitor_flags[CMD_MONITOR_EVENT_MAX][CMD_MONITOR_OBJ_MAX] = {
	[CMD_MONITOR_EVENT_ANY] = {
		[CMD_MONITOR_OBJ_ANY]		= 0xffffffff,
		[CMD_MONITOR_OBJ_TABLES]	= (1 << NFT_MSG_NEWTABLE) |
						  (1 << NFT_MSG_DELTABLE),
		[CMD_MONITOR_OBJ_CHAINS]	= (1 << NFT_MSG_NEWCHAIN) |
						  (1 << NFT_MSG_DELCHAIN),
		[CMD_MONITOR_OBJ_RULES]		= (1 << NFT_MSG_NEWRULE) |
						  (1 << NFT_MSG_DELRULE),
		[CMD_MONITOR_OBJ_SETS]		= (1 << NFT_MSG_NEWSET) |
						  (1 << NFT_MSG_DELSET),
		[CMD_MONITOR_OBJ_ELEMS]		= (1 << NFT_MSG_NEWSETELEM) |
						  (1 << NFT_MSG_DELSETELEM),
	},
	[CMD_MONITOR_EVENT_NEW] = {
		[CMD_MONITOR_OBJ_ANY]		= (1 << NFT_MSG_NEWTABLE) |
						  (1 << NFT_MSG_NEWCHAIN) |
						  (1 << NFT_MSG_NEWRULE)  |
						  (1 << NFT_MSG_NEWSET)   |
						  (1 << NFT_MSG_NEWSETELEM),
		[CMD_MONITOR_OBJ_TABLES]	= (1 << NFT_MSG_NEWTABLE),
		[CMD_MONITOR_OBJ_CHAINS]	= (1 << NFT_MSG_NEWCHAIN),
		[CMD_MONITOR_OBJ_RULES]		= (1 << NFT_MSG_NEWRULE),
		[CMD_MONITOR_OBJ_SETS]		= (1 << NFT_MSG_NEWSET),
		[CMD_MONITOR_OBJ_ELEMS]		= (1 << NFT_MSG_NEWSETELEM),
	},
	[CMD_MONITOR_EVENT_DEL] = {
		[CMD_MONITOR_OBJ_ANY]		= (1 << NFT_MSG_DELTABLE) |
						  (1 << NFT_MSG_DELCHAIN) |
						  (1 << NFT_MSG_DELRULE)  |
						  (1 << NFT_MSG_DELSET)   |
						  (1 << NFT_MSG_DELSETELEM),
		[CMD_MONITOR_OBJ_TABLES]	= (1 << NFT_MSG_DELTABLE),
		[CMD_MONITOR_OBJ_CHAINS]	= (1 << NFT_MSG_DELCHAIN),
		[CMD_MONITOR_OBJ_RULES]		= (1 << NFT_MSG_DELRULE),
		[CMD_MONITOR_OBJ_SETS]		= (1 << NFT_MSG_DELSET),
		[CMD_MONITOR_OBJ_ELEMS]		= (1 << NFT_MSG_DELSETELEM),
	},
};

static int cmd_evaluate_monitor(struct eval_ctx *ctx, struct cmd *cmd)
{
	uint32_t event;

	if (cmd->monitor->event == NULL)
		event = CMD_MONITOR_EVENT_ANY;
	else if (strcmp(cmd->monitor->event, "new") == 0)
		event = CMD_MONITOR_EVENT_NEW;
	else if (strcmp(cmd->monitor->event, "destroy") == 0)
		event = CMD_MONITOR_EVENT_DEL;
	else {
		return monitor_error(ctx, cmd->monitor, "invalid event %s",
				     cmd->monitor->event);
	}

	cmd->monitor->flags = monitor_flags[event][cmd->monitor->type];
	return 0;
}

int cmd_evaluate(struct eval_ctx *ctx, struct cmd *cmd)
{
#ifdef DEBUG
	if (debug_level & DEBUG_EVALUATION) {
		struct error_record *erec;
		erec = erec_create(EREC_INFORMATIONAL, &cmd->location, "Evaluate");
		erec_print(stdout, erec); printf("\n\n");
	}
#endif

	ctx->cmd = cmd;
	switch (cmd->op) {
	case CMD_ADD:
	case CMD_CREATE:
	case CMD_INSERT:
		return cmd_evaluate_add(ctx, cmd);
	case CMD_DELETE:
		return cmd_evaluate_delete(ctx, cmd);
	case CMD_LIST:
	case CMD_FLUSH:
	case CMD_RENAME:
	case CMD_EXPORT:
	case CMD_DESCRIBE:
		return 0;
	case CMD_MONITOR:
		return cmd_evaluate_monitor(ctx, cmd);
	default:
		BUG("invalid command operation %u\n", cmd->op);
	};
}
