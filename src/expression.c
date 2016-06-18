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
#include <limits.h>

#include <expression.h>
#include <statement.h>
#include <datatype.h>
#include <rule.h>
#include <gmputil.h>
#include <utils.h>
#include <list.h>
#include <erec.h>

struct expr *expr_alloc(const struct location *loc, const struct expr_ops *ops,
			const struct datatype *dtype, enum byteorder byteorder,
			unsigned int len)
{
	struct expr *expr;

	expr = xzalloc(sizeof(*expr));
	expr->location  = *loc;
	expr->ops	= ops;
	expr->dtype	= dtype;
	expr->byteorder	= byteorder;
	expr->len	= len;
	expr->refcnt	= 1;
	init_list_head(&expr->list);
	return expr;
}

struct expr *expr_clone(const struct expr *expr)
{
	struct expr *new;

	new = expr_alloc(&expr->location, expr->ops, expr->dtype,
			 expr->byteorder, expr->len);
	new->flags = expr->flags;
	new->op    = expr->op;
	expr->ops->clone(new, expr);
	return new;
}

struct expr *expr_get(struct expr *expr)
{
	expr->refcnt++;
	return expr;
}

void expr_free(struct expr *expr)
{
	if (expr == NULL)
		return;
	if (--expr->refcnt > 0)
		return;
	if (expr->ops->destroy)
		expr->ops->destroy(expr);
	xfree(expr);
}

void expr_print(const struct expr *expr)
{
	expr->ops->print(expr);
}

bool expr_cmp(const struct expr *e1, const struct expr *e2)
{
	assert(e1->flags & EXPR_F_SINGLETON);
	assert(e2->flags & EXPR_F_SINGLETON);

	if (e1->ops->type != e2->ops->type)
		return false;

	return e1->ops->cmp(e1, e2);
}

void expr_describe(const struct expr *expr)
{
	const struct datatype *dtype = expr->dtype;
	const char *delim = "";

	printf("%s expression, datatype %s (%s)",
		expr->ops->name, dtype->name, dtype->desc);
	if (dtype->basetype != NULL) {
		printf(" (basetype ");
		for (dtype = dtype->basetype; dtype != NULL;
		     dtype = dtype->basetype) {
			printf("%s%s", delim, dtype->desc);
			delim = ", ";
		}
		printf(")");
	}

	if (expr_basetype(expr)->type == TYPE_STRING) {
		if (expr->len)
			printf(", %u characters", expr->len / BITS_PER_BYTE);
		else
			printf(", dynamic length");
	} else
		printf(", %u bits", expr->len);

	printf("\n");

	if (expr->dtype->sym_tbl != NULL) {
		printf("\npre-defined symbolic constants:\n");
		symbol_table_print(expr->dtype->sym_tbl, expr->dtype);
	}
}

void expr_set_type(struct expr *expr, const struct datatype *dtype,
		   enum byteorder byteorder)
{
	if (expr->ops->set_type)
		expr->ops->set_type(expr, dtype, byteorder);
	else {
		expr->dtype	= dtype;
		expr->byteorder	= byteorder;
	}
}

const struct datatype *expr_basetype(const struct expr *expr)
{
	const struct datatype *type = expr->dtype;

	while (type->basetype != NULL)
		type = type->basetype;
	return type;
}

int __fmtstring(4, 5) expr_binary_error(struct list_head *msgs,
					const struct expr *e1, const struct expr *e2,
					const char *fmt, ...)
{
	struct error_record *erec;
	va_list ap;

	va_start(ap, fmt);
	erec = erec_vcreate(EREC_ERROR, &e1->location, fmt, ap);
	if (e2 != NULL)
		erec_add_location(erec, &e2->location);
	va_end(ap);
	erec_queue(erec, msgs);
	return -1;
}

static void verdict_expr_print(const struct expr *expr)
{
	datatype_print(expr);
}

static bool verdict_expr_cmp(const struct expr *e1, const struct expr *e2)
{
	if (e1->verdict != e2->verdict)
		return false;

	if ((e1->verdict == NFT_JUMP ||
	     e1->verdict == NFT_GOTO) &&
	    strcmp(e1->chain, e2->chain))
		return false;

	return true;
}

static void verdict_expr_clone(struct expr *new, const struct expr *expr)
{
	new->verdict = expr->verdict;
	if (expr->chain != NULL)
		new->chain = xstrdup(expr->chain);
}

static void verdict_expr_destroy(struct expr *expr)
{
	xfree(expr->chain);
}

static const struct expr_ops verdict_expr_ops = {
	.type		= EXPR_VERDICT,
	.name		= "verdict",
	.print		= verdict_expr_print,
	.cmp		= verdict_expr_cmp,
	.clone		= verdict_expr_clone,
	.destroy	= verdict_expr_destroy,
};

struct expr *verdict_expr_alloc(const struct location *loc,
				int verdict, const char *chain)
{
	struct expr *expr;

	expr = expr_alloc(loc, &verdict_expr_ops, &verdict_type,
			  BYTEORDER_INVALID, 0);
	expr->verdict = verdict;
	if (chain != NULL)
		expr->chain = chain;
	expr->flags = EXPR_F_CONSTANT | EXPR_F_SINGLETON;
	return expr;
}

static void symbol_expr_print(const struct expr *expr)
{
	printf("%s%s", expr->scope != NULL ? "$" : "", expr->identifier);
}

static void symbol_expr_clone(struct expr *new, const struct expr *expr)
{
	new->symtype	= expr->symtype;
	new->scope      = expr->scope;
	new->identifier = xstrdup(expr->identifier);
}

static void symbol_expr_destroy(struct expr *expr)
{
	xfree(expr->identifier);
}

static const struct expr_ops symbol_expr_ops = {
	.type		= EXPR_SYMBOL,
	.name		= "symbol",
	.print		= symbol_expr_print,
	.clone		= symbol_expr_clone,
	.destroy	= symbol_expr_destroy,
};

struct expr *symbol_expr_alloc(const struct location *loc,
			       enum symbol_types type, struct scope *scope,
			       const char *identifier)
{
	struct expr *expr;

	expr = expr_alloc(loc, &symbol_expr_ops, &invalid_type,
			  BYTEORDER_INVALID, 0);
	expr->symtype	 = type;
	expr->scope	 = scope;
	expr->identifier = xstrdup(identifier);
	return expr;
}

static void constant_expr_print(const struct expr *expr)
{
	datatype_print(expr);
}

static bool constant_expr_cmp(const struct expr *e1, const struct expr *e2)
{
	return expr_basetype(e1) == expr_basetype(e2) &&
	       !mpz_cmp(e1->value, e2->value);
}

static void constant_expr_clone(struct expr *new, const struct expr *expr)
{
	mpz_init_set(new->value, expr->value);
}

static void constant_expr_destroy(struct expr *expr)
{
	mpz_clear(expr->value);
}

static const struct expr_ops constant_expr_ops = {
	.type		= EXPR_VALUE,
	.name		= "value",
	.print		= constant_expr_print,
	.cmp		= constant_expr_cmp,
	.clone		= constant_expr_clone,
	.destroy	= constant_expr_destroy,
};

struct expr *constant_expr_alloc(const struct location *loc,
				 const struct datatype *dtype,
				 enum byteorder byteorder,
				 unsigned int len, const void *data)
{
	struct expr *expr;

	expr = expr_alloc(loc, &constant_expr_ops, dtype, byteorder, len);
	expr->flags = EXPR_F_CONSTANT | EXPR_F_SINGLETON;

	mpz_init2(expr->value, len);
	if (data != NULL)
		mpz_import_data(expr->value, data, byteorder,
				div_round_up(len, BITS_PER_BYTE));

	return expr;
}

struct expr *constant_expr_join(const struct expr *e1, const struct expr *e2)
{
	unsigned int len = (e1->len + e2->len) / BITS_PER_BYTE, tmp;
	unsigned char data[len];

	assert(e1->ops->type == EXPR_VALUE);
	assert(e2->ops->type == EXPR_VALUE);

	tmp = e1->len / BITS_PER_BYTE;
	mpz_export_data(data, e1->value, e1->byteorder, tmp);
	mpz_export_data(data + tmp, e2->value, e2->byteorder,
			e2->len / BITS_PER_BYTE);

	return constant_expr_alloc(&e1->location, &invalid_type,
				   BYTEORDER_INVALID, len * BITS_PER_BYTE,
				   data);
}

struct expr *constant_expr_splice(struct expr *expr, unsigned int len)
{
	struct expr *slice;
	mpz_t mask;

	assert(expr->ops->type == EXPR_VALUE);
	assert(len <= expr->len);

	slice = constant_expr_alloc(&expr->location, &invalid_type,
				    BYTEORDER_INVALID, len, NULL);
	mpz_init2(mask, len);
	mpz_bitmask(mask, len);
	mpz_lshift_ui(mask, expr->len - len);

	mpz_set(slice->value, expr->value);
	mpz_and(slice->value, slice->value, mask);
	mpz_rshift_ui(slice->value, expr->len - len);
	mpz_clear(mask);

	expr->len -= len;
	return slice;
}

/*
 * Allocate a constant expression with a single bit set at position n.
 */
struct expr *flag_expr_alloc(const struct location *loc,
			     const struct datatype *dtype,
			     enum byteorder byteorder,
			     unsigned int len, unsigned long n)
{
	struct expr *expr;

	assert(n < len);

	expr = constant_expr_alloc(loc, dtype, byteorder, len, NULL);
	mpz_set_ui(expr->value, 1);
	mpz_lshift_ui(expr->value, n);

	return expr;
}

/*
 * Convert an expression of basetype TYPE_BITMASK into a series of inclusive
 * OR binop expressions of the individual flag values.
 */
struct expr *bitmask_expr_to_binops(struct expr *expr)
{
	struct expr *binop, *flag;
	unsigned long n;

	assert(expr->ops->type == EXPR_VALUE);
	assert(expr->dtype->basetype->type == TYPE_BITMASK);

	n = mpz_popcount(expr->value);
	if (n == 0 || n == 1)
		return expr;

	binop = NULL;
	n = 0;
	while ((n = mpz_scan1(expr->value, n)) != ULONG_MAX) {
		flag = flag_expr_alloc(&expr->location, expr->dtype,
				       expr->byteorder, expr->len, n);
		if (binop != NULL)
			binop = binop_expr_alloc(&expr->location,
						 OP_OR, binop, flag);
		else
			binop = flag;

		n++;
	}

	expr_free(expr);
	return binop;
}

static void prefix_expr_print(const struct expr *expr)
{
	expr_print(expr->prefix);
	printf("/%u", expr->prefix_len);
}

static void prefix_expr_set_type(const struct expr *expr,
				 const struct datatype *type,
				 enum byteorder byteorder)
{
	expr_set_type(expr->prefix, type, byteorder);
}

static void prefix_expr_clone(struct expr *new, const struct expr *expr)
{
	new->prefix     = expr_clone(expr->prefix);
	new->prefix_len = expr->prefix_len;
}

static void prefix_expr_destroy(struct expr *expr)
{
	expr_free(expr->prefix);
}

static const struct expr_ops prefix_expr_ops = {
	.type		= EXPR_PREFIX,
	.name		= "prefix",
	.print		= prefix_expr_print,
	.set_type	= prefix_expr_set_type,
	.clone		= prefix_expr_clone,
	.destroy	= prefix_expr_destroy,
};

struct expr *prefix_expr_alloc(const struct location *loc,
			       struct expr *expr, unsigned int prefix_len)
{
	struct expr *prefix;

	prefix = expr_alloc(loc, &prefix_expr_ops, &invalid_type,
			    BYTEORDER_INVALID, 0);
	prefix->prefix     = expr;
	prefix->prefix_len = prefix_len;
	return prefix;
}

const char *expr_op_symbols[] = {
	[OP_INVALID]	= "invalid",
	[OP_HTON]	= "hton",
	[OP_NTOH]	= "ntoh",
	[OP_AND]	= "&",
	[OP_OR]		= "|",
	[OP_XOR]	= "^",
	[OP_LSHIFT]	= "<<",
	[OP_RSHIFT]	= ">>",
	[OP_EQ]		= "==",
	[OP_NEQ]	= "!=",
	[OP_LT]		= "<",
	[OP_GT]		= ">",
	[OP_LTE]	= "<=",
	[OP_GTE]	= ">=",
	[OP_RANGE]	= "within range",
	[OP_LOOKUP]	= NULL,
};

static void unary_expr_print(const struct expr *expr)
{
	if (expr_op_symbols[expr->op] != NULL)
		printf("%s(", expr_op_symbols[expr->op]);
	expr_print(expr->arg);
	printf(")");
}

static void unary_expr_clone(struct expr *new, const struct expr *expr)
{
	new->arg = expr_clone(expr->arg);
}

static void unary_expr_destroy(struct expr *expr)
{
	expr_free(expr->arg);
}

static const struct expr_ops unary_expr_ops = {
	.type		= EXPR_UNARY,
	.name		= "unary",
	.print		= unary_expr_print,
	.clone		= unary_expr_clone,
	.destroy	= unary_expr_destroy,
};

struct expr *unary_expr_alloc(const struct location *loc,
			      enum ops op, struct expr *arg)
{
	struct expr *expr;

	expr = expr_alloc(loc, &unary_expr_ops, &invalid_type,
			  BYTEORDER_INVALID, 0);
	expr->op  = op;
	expr->arg = arg;
	return expr;
}

static uint8_t expr_binop_precedence[OP_MAX + 1] = {
	[OP_LSHIFT]	= 1,
	[OP_RSHIFT]	= 1,
	[OP_AND]	= 2,
	[OP_XOR]	= 3,
	[OP_OR]		= 4,
};

static void binop_arg_print(const struct expr *op, const struct expr *arg)
{
	bool prec = false;

	if (arg->ops->type == EXPR_BINOP &&
	    expr_binop_precedence[op->op] != 0 &&
	    expr_binop_precedence[op->op] < expr_binop_precedence[arg->op])
		prec = 1;

	if (prec)
		printf("(");
	expr_print(arg);
	if (prec)
		printf(")");
}

static bool must_print_eq_op(const struct expr *expr)
{
	if (expr->right->dtype->basetype != NULL &&
	    expr->right->dtype->basetype->type == TYPE_BITMASK)
		return true;

	return expr->left->ops->type == EXPR_BINOP;
}

static void binop_expr_print(const struct expr *expr)
{
	binop_arg_print(expr, expr->left);

	if (expr_op_symbols[expr->op] &&
	    (expr->op != OP_EQ || must_print_eq_op(expr)))
		printf(" %s ", expr_op_symbols[expr->op]);
	else
		printf(" ");

	binop_arg_print(expr, expr->right);
}

static void binop_expr_clone(struct expr *new, const struct expr *expr)
{
	new->left  = expr_clone(expr->left);
	new->right = expr_clone(expr->right);
}

static void binop_expr_destroy(struct expr *expr)
{
	expr_free(expr->left);
	expr_free(expr->right);
}

static const struct expr_ops binop_expr_ops = {
	.type		= EXPR_BINOP,
	.name		= "binop",
	.print		= binop_expr_print,
	.clone		= binop_expr_clone,
	.destroy	= binop_expr_destroy,
};

struct expr *binop_expr_alloc(const struct location *loc, enum ops op,
			      struct expr *left, struct expr *right)
{
	struct expr *expr;

	expr = expr_alloc(loc, &binop_expr_ops, left->dtype,
			  left->byteorder, 0);
	expr->left  = left;
	expr->op    = op;
	expr->right = right;
	return expr;
}

static const struct expr_ops relational_expr_ops = {
	.type		= EXPR_RELATIONAL,
	.name		= "relational",
	.print		= binop_expr_print,
	.destroy	= binop_expr_destroy,
};

struct expr *relational_expr_alloc(const struct location *loc, enum ops op,
				   struct expr *left, struct expr *right)
{
	struct expr *expr;

	expr = expr_alloc(loc, &relational_expr_ops, &verdict_type,
			  BYTEORDER_INVALID, 0);
	expr->left  = left;
	expr->op    = op;
	expr->right = right;
	return expr;
}

static void range_expr_print(const struct expr *expr)
{
	expr_print(expr->left);
	printf("-");
	expr_print(expr->right);
}

static void range_expr_clone(struct expr *new, const struct expr *expr)
{
	new->left  = expr_clone(expr->left);
	new->right = expr_clone(expr->right);
}

static void range_expr_destroy(struct expr *expr)
{
	expr_free(expr->left);
	expr_free(expr->right);
}

static void range_expr_set_type(const struct expr *expr,
				const struct datatype *type,
				enum byteorder byteorder)
{
	expr_set_type(expr->left, type, byteorder);
	expr_set_type(expr->right, type, byteorder);
}

static const struct expr_ops range_expr_ops = {
	.type		= EXPR_RANGE,
	.name		= "range",
	.print		= range_expr_print,
	.clone		= range_expr_clone,
	.destroy	= range_expr_destroy,
	.set_type	= range_expr_set_type,
};

struct expr *range_expr_alloc(const struct location *loc,
			      struct expr *left, struct expr *right)
{
	struct expr *expr;

	expr = expr_alloc(loc, &range_expr_ops, &invalid_type,
			  BYTEORDER_INVALID, 0);
	expr->left  = left;
	expr->right = right;
	return expr;
}

static struct expr *compound_expr_alloc(const struct location *loc,
					const struct expr_ops *ops)
{
	struct expr *expr;

	expr = expr_alloc(loc, ops, &invalid_type, BYTEORDER_INVALID, 0);
	init_list_head(&expr->expressions);
	return expr;
}

static void compound_expr_clone(struct expr *new, const struct expr *expr)
{
	struct expr *i;

	init_list_head(&new->expressions);
	list_for_each_entry(i, &expr->expressions, list)
		compound_expr_add(new, expr_clone(i));
}

static void compound_expr_destroy(struct expr *expr)
{
	struct expr *i, *next;

	list_for_each_entry_safe(i, next, &expr->expressions, list)
		expr_free(i);
}

static void compound_expr_print(const struct expr *expr, const char *delim)
{
	const struct expr *i;
	const char *d = "";

	list_for_each_entry(i, &expr->expressions, list) {
		printf("%s", d);
		expr_print(i);
		d = delim;
	}
}

void compound_expr_add(struct expr *compound, struct expr *expr)
{
	list_add_tail(&expr->list, &compound->expressions);
	compound->size++;
}

void compound_expr_remove(struct expr *compound, struct expr *expr)
{
	compound->size--;
	list_del(&expr->list);
}

static void concat_expr_destroy(struct expr *expr)
{
	concat_type_destroy(expr->dtype);
	compound_expr_destroy(expr);
}

static void concat_expr_print(const struct expr *expr)
{
	compound_expr_print(expr, " . ");
}

static const struct expr_ops concat_expr_ops = {
	.type		= EXPR_CONCAT,
	.name		= "concat",
	.print		= concat_expr_print,
	.clone		= compound_expr_clone,
	.destroy	= concat_expr_destroy,
};

struct expr *concat_expr_alloc(const struct location *loc)
{
	return compound_expr_alloc(loc, &concat_expr_ops);
}

static void list_expr_print(const struct expr *expr)
{
	compound_expr_print(expr, ",");
}

static const struct expr_ops list_expr_ops = {
	.type		= EXPR_LIST,
	.name		= "list",
	.print		= list_expr_print,
	.clone		= compound_expr_clone,
	.destroy	= compound_expr_destroy,
};

struct expr *list_expr_alloc(const struct location *loc)
{
	return compound_expr_alloc(loc, &list_expr_ops);
}

static void set_expr_print(const struct expr *expr)
{
	printf("{ ");
	compound_expr_print(expr, ", ");
	printf("}");
}

static void set_expr_set_type(const struct expr *expr,
			      const struct datatype *dtype,
			      enum byteorder byteorder)
{
	struct expr *i;

	list_for_each_entry(i, &expr->expressions, list)
		expr_set_type(i, dtype, byteorder);
}

static const struct expr_ops set_expr_ops = {
	.type		= EXPR_SET,
	.name		= "set",
	.print		= set_expr_print,
	.set_type	= set_expr_set_type,
	.clone		= compound_expr_clone,
	.destroy	= compound_expr_destroy,
};

struct expr *set_expr_alloc(const struct location *loc)
{
	return compound_expr_alloc(loc, &set_expr_ops);
}

static void mapping_expr_print(const struct expr *expr)
{
	expr_print(expr->left);
	printf(" : ");
	expr_print(expr->right);
}

static void mapping_expr_set_type(const struct expr *expr,
				  const struct datatype *dtype,
				  enum byteorder byteorder)
{
	expr_set_type(expr->left, dtype, byteorder);
}

static void mapping_expr_clone(struct expr *new, const struct expr *expr)
{
	new->left  = expr_clone(expr->left);
	new->right = expr_clone(expr->right);
}

static void mapping_expr_destroy(struct expr *expr)
{
	expr_free(expr->left);
	expr_free(expr->right);
}

static const struct expr_ops mapping_expr_ops = {
	.type		= EXPR_MAPPING,
	.name		= "mapping",
	.print		= mapping_expr_print,
	.set_type	= mapping_expr_set_type,
	.clone		= mapping_expr_clone,
	.destroy	= mapping_expr_destroy,
};

struct expr *mapping_expr_alloc(const struct location *loc,
				struct expr *from, struct expr *to)
{
	struct expr *expr;

	expr = expr_alloc(loc, &mapping_expr_ops, from->dtype,
			  from->byteorder, 0);
	expr->left  = from;
	expr->right = to;
	return expr;
}

static void map_expr_print(const struct expr *expr)
{
	expr_print(expr->map);
	if (expr->mappings->ops->type == EXPR_SET_REF &&
	    expr->mappings->set->datatype->type == TYPE_VERDICT)
		printf(" vmap ");
	else
		printf(" map ");
	expr_print(expr->mappings);
}

static void map_expr_clone(struct expr *new, const struct expr *expr)
{
	new->map      = expr_clone(expr->map);
	new->mappings = expr_clone(expr->mappings);
}

static void map_expr_destroy(struct expr *expr)
{
	expr_free(expr->map);
	expr_free(expr->mappings);
}

static const struct expr_ops map_expr_ops = {
	.type		= EXPR_MAP,
	.name		= "map",
	.print		= map_expr_print,
	.clone		= map_expr_clone,
	.destroy	= map_expr_destroy,
};

struct expr *map_expr_alloc(const struct location *loc, struct expr *arg,
			    struct expr *mappings)
{
	struct expr *expr;

	expr = expr_alloc(loc, &map_expr_ops, &invalid_type, BYTEORDER_INVALID, 0);
	expr->map      = arg;
	expr->mappings = mappings;
	return expr;
}

static void set_ref_expr_print(const struct expr *expr)
{
	if (expr->set->flags & SET_F_ANONYMOUS) {
		if (expr->set->flags & SET_F_EVAL)
			printf("table %s", expr->set->handle.set);
		else
			expr_print(expr->set->init);
	} else {
		printf("@%s", expr->set->handle.set);
	}
}

static void set_ref_expr_clone(struct expr *new, const struct expr *expr)
{
	new->set = set_get(expr->set);
}

static void set_ref_expr_destroy(struct expr *expr)
{
	set_free(expr->set);
}

static const struct expr_ops set_ref_expr_ops = {
	.type		= EXPR_SET_REF,
	.name		= "set reference",
	.print		= set_ref_expr_print,
	.clone		= set_ref_expr_clone,
	.destroy	= set_ref_expr_destroy,
};

struct expr *set_ref_expr_alloc(const struct location *loc, struct set *set)
{
	struct expr *expr;

	expr = expr_alloc(loc, &set_ref_expr_ops, set->keytype, 0, 0);
	expr->set = set_get(set);
	expr->flags |= EXPR_F_CONSTANT;
	return expr;
}

static void set_elem_expr_print(const struct expr *expr)
{
	expr_print(expr->key);
	if (expr->timeout) {
		printf(" timeout ");
		time_print(expr->timeout / 1000);
	}
	if (expr->expiration) {
		printf(" expires ");
		time_print(expr->expiration / 1000);
	}
	if (expr->comment)
		printf(" comment \"%s\"", expr->comment);

	if (expr->stmt) {
		printf(" : ");
		stmt_print(expr->stmt);
	}
}

static void set_elem_expr_destroy(struct expr *expr)
{
	xfree(expr->comment);
	expr_free(expr->key);
}

static void set_elem_expr_clone(struct expr *new, const struct expr *expr)
{
	new->key = expr_clone(expr->key);
	new->expiration = expr->expiration;
	new->timeout = expr->timeout;
	if (expr->comment)
		new->comment = xstrdup(expr->comment);
}

static const struct expr_ops set_elem_expr_ops = {
	.type		= EXPR_SET_ELEM,
	.name		= "set element",
	.clone		= set_elem_expr_clone,
	.print		= set_elem_expr_print,
	.destroy	= set_elem_expr_destroy,
};

struct expr *set_elem_expr_alloc(const struct location *loc, struct expr *key)
{
	struct expr *expr;

	expr = expr_alloc(loc, &set_elem_expr_ops, key->dtype,
			  key->byteorder, key->len);
	expr->key = key;
	return expr;
}

void range_expr_value_low(mpz_t rop, const struct expr *expr)
{
	switch (expr->ops->type) {
	case EXPR_VALUE:
		return mpz_set(rop, expr->value);
	case EXPR_PREFIX:
		return range_expr_value_low(rop, expr->prefix);
	case EXPR_RANGE:
		return range_expr_value_low(rop, expr->left);
	case EXPR_MAPPING:
		return range_expr_value_low(rop, expr->left);
	case EXPR_SET_ELEM:
		return range_expr_value_low(rop, expr->key);
	default:
		BUG("invalid range expression type %s\n", expr->ops->name);
	}
}

void range_expr_value_high(mpz_t rop, const struct expr *expr)
{
	mpz_t tmp;

	switch (expr->ops->type) {
	case EXPR_VALUE:
		return mpz_set(rop, expr->value);
	case EXPR_PREFIX:
		range_expr_value_low(rop, expr->prefix);
		mpz_init_bitmask(tmp, expr->len - expr->prefix_len);
		mpz_add(rop, rop, tmp);
		mpz_clear(tmp);
		return;
	case EXPR_RANGE:
		return range_expr_value_high(rop, expr->right);
	case EXPR_MAPPING:
		return range_expr_value_high(rop, expr->left);
	case EXPR_SET_ELEM:
		return range_expr_value_high(rop, expr->key);
	default:
		BUG("invalid range expression type %s\n", expr->ops->name);
	}
}
