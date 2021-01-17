/*
 * Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 * Copyright (c) 2013 Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <linux/netfilter/nf_tables.h>
#include <arpa/inet.h>
#include <linux/netfilter/nf_nat.h>
#include <linux/netfilter.h>
#include <net/ethernet.h>
#include <netlink.h>
#include <rule.h>
#include <statement.h>
#include <expression.h>
#include <gmputil.h>
#include <utils.h>
#include <erec.h>
#include <sys/socket.h>
#include <libnftnl/udata.h>
#include <cache.h>
#include <xt.h>

static int netlink_parse_expr(const struct nftnl_expr *nle,
			      struct netlink_parse_ctx *ctx);

static void __fmtstring(3, 4) netlink_error(struct netlink_parse_ctx *ctx,
					    const struct location *loc,
					    const char *fmt, ...)
{
	struct error_record *erec;
	va_list ap;

	va_start(ap, fmt);
	erec = erec_vcreate(EREC_ERROR, loc, fmt, ap);
	va_end(ap);
	erec_queue(erec, ctx->msgs);
}

static unsigned int netlink_parse_register(const struct nftnl_expr *nle,
					   unsigned int attr)
{
	unsigned int reg;

	reg = nftnl_expr_get_u32(nle, attr);
	/* Translate 128bit registers to corresponding 32bit registers */
	if (reg >= NFT_REG_1 && reg <= NFT_REG_4)
		reg = 1 + (reg - NFT_REG_1) * (NFT_REG_SIZE / NFT_REG32_SIZE);
	else if (reg >= NFT_REG32_00)
		reg = 1 + reg - NFT_REG32_00;

	return reg;
}

static void netlink_set_register(struct netlink_parse_ctx *ctx,
				 enum nft_registers reg,
				 struct expr *expr)
{
	if (reg == NFT_REG_VERDICT || reg > MAX_REGS) {
		netlink_error(ctx, &expr->location,
			      "Invalid destination register %u", reg);
		expr_free(expr);
		return;
	}

	if (ctx->registers[reg] != NULL)
		expr_free(ctx->registers[reg]);

	ctx->registers[reg] = expr;
}

static struct expr *netlink_get_register(struct netlink_parse_ctx *ctx,
					 const struct location *loc,
					 enum nft_registers reg)
{
	struct expr *expr;

	if (reg == NFT_REG_VERDICT || reg > MAX_REGS) {
		netlink_error(ctx, loc, "Invalid source register %u", reg);
		return NULL;
	}

	expr = ctx->registers[reg];
	if (expr != NULL)
		expr = expr_clone(expr);

	return expr;
}

static void netlink_release_registers(struct netlink_parse_ctx *ctx)
{
	int i;

	for (i = 0; i < MAX_REGS; i++)
		expr_free(ctx->registers[i]);
}

static struct expr *netlink_parse_concat_expr(struct netlink_parse_ctx *ctx,
					      const struct location *loc,
					      unsigned int reg,
					      unsigned int len)
{
	struct expr *concat, *expr;
	unsigned int consumed;

	concat = concat_expr_alloc(loc);
	while (len > 0) {
		expr = netlink_get_register(ctx, loc, reg);
		if (expr == NULL) {
			netlink_error(ctx, loc,
				      "Relational expression size mismatch");
			goto err;
		}
		compound_expr_add(concat, expr);

		consumed = netlink_padded_len(expr->len);
		assert(consumed > 0);
		len -= consumed;
		reg += netlink_register_space(expr->len);
	}
	return concat;

err:
	expr_free(concat);
	return NULL;
}

static struct expr *netlink_parse_concat_data(struct netlink_parse_ctx *ctx,
					      const struct location *loc,
					      unsigned int reg,
					      unsigned int len,
					      struct expr *data)
{
	struct expr *concat, *expr, *i;

	concat = concat_expr_alloc(loc);
	while (len > 0) {
		expr = netlink_get_register(ctx, loc, reg);
		if (expr == NULL) {
			netlink_error(ctx, loc,
				      "Relational expression size mismatch");
			goto err;
		}
		i = constant_expr_splice(data, expr->len);
		data->len -= netlink_padding_len(expr->len);
		compound_expr_add(concat, i);

		len -= netlink_padded_len(expr->len);
		reg += netlink_register_space(expr->len);
	}
	return concat;

err:
	expr_free(concat);
	return NULL;
}

static void netlink_parse_chain_verdict(struct netlink_parse_ctx *ctx,
					const struct location *loc,
					struct expr *expr,
					enum nft_verdicts verdict)
{
	char chain_name[NFT_CHAIN_MAXNAMELEN] = {};
	struct chain *chain;

	expr_chain_export(expr->chain, chain_name);
	chain = chain_binding_lookup(ctx->table, chain_name);
	if (chain) {
		ctx->stmt = chain_stmt_alloc(loc, chain, verdict);
		expr_free(expr);
	} else {
		ctx->stmt = verdict_stmt_alloc(loc, expr);
	}
}

static void netlink_parse_immediate(struct netlink_parse_ctx *ctx,
				    const struct location *loc,
				    const struct nftnl_expr *nle)
{
	struct nft_data_delinearize nld;
	enum nft_registers dreg;
	struct expr *expr;

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_IMM_VERDICT)) {
		nld.verdict = nftnl_expr_get_u32(nle, NFTNL_EXPR_IMM_VERDICT);
		if  (nftnl_expr_is_set(nle, NFTNL_EXPR_IMM_CHAIN)) {
			nld.chain = nftnl_expr_get(nle, NFTNL_EXPR_IMM_CHAIN,
						   &nld.len);
		}
	} else if (nftnl_expr_is_set(nle, NFTNL_EXPR_IMM_DATA)) {
		nld.value = nftnl_expr_get(nle, NFTNL_EXPR_IMM_DATA, &nld.len);
	}

	dreg = netlink_parse_register(nle, NFTNL_EXPR_IMM_DREG);
	expr = netlink_alloc_data(loc, &nld, dreg);

	if (dreg == NFT_REG_VERDICT) {
		switch (expr->verdict) {
		case NFT_JUMP:
			netlink_parse_chain_verdict(ctx, loc, expr, NFT_JUMP);
			break;
		case NFT_GOTO:
			netlink_parse_chain_verdict(ctx, loc, expr, NFT_GOTO);
			break;
		default:
			ctx->stmt = verdict_stmt_alloc(loc, expr);
			break;
		}
	} else {
		netlink_set_register(ctx, dreg, expr);
	}
}

static void netlink_parse_xfrm(struct netlink_parse_ctx *ctx,
			       const struct location *loc,
			       const struct nftnl_expr *nle)
{
	enum nft_registers dreg;
	enum nft_xfrm_keys key;
	struct expr *expr;
	uint32_t spnum;
	uint8_t dir;

	key = nftnl_expr_get_u32(nle, NFTNL_EXPR_XFRM_KEY);
	dir = nftnl_expr_get_u8(nle, NFTNL_EXPR_XFRM_DIR);
	spnum = nftnl_expr_get_u32(nle, NFTNL_EXPR_XFRM_SPNUM);
	expr = xfrm_expr_alloc(loc, dir, spnum, key);

	dreg = netlink_parse_register(nle, NFTNL_EXPR_XFRM_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static enum ops netlink_parse_range_op(const struct nftnl_expr *nle)
{
	switch (nftnl_expr_get_u32(nle, NFTNL_EXPR_RANGE_OP)) {
	case NFT_RANGE_EQ:
		return OP_EQ;
	case NFT_RANGE_NEQ:
		return OP_NEQ;
	default:
		return OP_INVALID;
	}
}

static void netlink_parse_range(struct netlink_parse_ctx *ctx,
				const struct location *loc,
				const struct nftnl_expr *nle)
{
	struct expr *expr, *left, *right, *from, *to;
	struct nft_data_delinearize nld;
	enum nft_registers sreg;
	enum ops op;

	sreg = netlink_parse_register(nle, NFTNL_EXPR_RANGE_SREG);
	left = netlink_get_register(ctx, loc, sreg);
	if (left == NULL)
		return netlink_error(ctx, loc,
				     "Relational expression has no left hand side");

	op = netlink_parse_range_op(nle);

	nld.value = nftnl_expr_get(nle, NFTNL_EXPR_RANGE_FROM_DATA, &nld.len);
	from = netlink_alloc_value(loc, &nld);

	nld.value = nftnl_expr_get(nle, NFTNL_EXPR_RANGE_TO_DATA, &nld.len);
	to = netlink_alloc_value(loc, &nld);

	right = range_expr_alloc(loc, from, to);
	expr = relational_expr_alloc(loc, op, left, right);
	ctx->stmt = expr_stmt_alloc(loc, expr);
}

static enum ops netlink_parse_cmp_op(const struct nftnl_expr *nle)
{
	switch (nftnl_expr_get_u32(nle, NFTNL_EXPR_CMP_OP)) {
	case NFT_CMP_EQ:
		return OP_EQ;
	case NFT_CMP_NEQ:
		return OP_NEQ;
	case NFT_CMP_LT:
		return OP_LT;
	case NFT_CMP_LTE:
		return OP_LTE;
	case NFT_CMP_GT:
		return OP_GT;
	case NFT_CMP_GTE:
		return OP_GTE;
	default:
		return OP_INVALID;
	}
}

static void netlink_parse_cmp(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	struct nft_data_delinearize nld;
	enum nft_registers sreg;
	struct expr *expr, *left, *right, *tmp;
	enum ops op;

	sreg = netlink_parse_register(nle, NFTNL_EXPR_CMP_SREG);
	left = netlink_get_register(ctx, loc, sreg);
	if (left == NULL)
		return netlink_error(ctx, loc,
				     "Relational expression has no left "
				     "hand side");

	op = netlink_parse_cmp_op(nle);

	nld.value = nftnl_expr_get(nle, NFTNL_EXPR_CMP_DATA, &nld.len);
	right = netlink_alloc_value(loc, &nld);

	if (left->len > right->len &&
	    expr_basetype(left) != &string_type) {
		mpz_lshift_ui(right->value, left->len - right->len);
		right = prefix_expr_alloc(loc, right, right->len);
		right->prefix->len = left->len;
	} else if (left->len > 0 && left->len < right->len) {
		expr_free(left);
		left = netlink_parse_concat_expr(ctx, loc, sreg, right->len);
		if (left == NULL)
			goto err_free;
		tmp = netlink_parse_concat_data(ctx, loc, sreg, right->len, right);
		if (tmp == NULL)
			goto err_free;
		expr_free(right);
		right = tmp;
	}

	expr = relational_expr_alloc(loc, op, left, right);
	ctx->stmt = expr_stmt_alloc(loc, expr);
	return;
err_free:
	expr_free(left);
	expr_free(right);
}

static void netlink_parse_lookup(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *nle)
{
	enum nft_registers sreg, dreg;
	const char *name;
	struct expr *expr, *left, *right;
	struct set *set;
	uint32_t flag;

	name = nftnl_expr_get_str(nle, NFTNL_EXPR_LOOKUP_SET);
	set  = set_lookup(ctx->table, name);
	if (set == NULL)
		return netlink_error(ctx, loc,
				     "Unknown set '%s' in lookup expression",
				     name);

	sreg = netlink_parse_register(nle, NFTNL_EXPR_LOOKUP_SREG);
	left = netlink_get_register(ctx, loc, sreg);
	if (left == NULL)
		return netlink_error(ctx, loc,
				     "Lookup expression has no left hand side");

	if (left->len < set->key->len) {
		expr_free(left);
		left = netlink_parse_concat_expr(ctx, loc, sreg, set->key->len);
		if (left == NULL)
			return;
	}

	right = set_ref_expr_alloc(loc, set);

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_LOOKUP_DREG)) {
		dreg = netlink_parse_register(nle, NFTNL_EXPR_LOOKUP_DREG);
		expr = map_expr_alloc(loc, left, right);
		if (dreg != NFT_REG_VERDICT)
			return netlink_set_register(ctx, dreg, expr);
	} else {
		expr = relational_expr_alloc(loc, OP_EQ, left, right);
	}

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_LOOKUP_FLAGS)) {
		flag = nftnl_expr_get_u32(nle, NFTNL_EXPR_LOOKUP_FLAGS);
		if (flag & NFT_LOOKUP_F_INV)
			expr->op = OP_NEQ;
	}

	ctx->stmt = expr_stmt_alloc(loc, expr);
}

static struct expr *netlink_parse_bitwise_bool(struct netlink_parse_ctx *ctx,
					       const struct location *loc,
					       const struct nftnl_expr *nle,
					       enum nft_registers sreg,
					       struct expr *left)

{
	struct nft_data_delinearize nld;
	struct expr *expr, *mask, *xor, *or;
	mpz_t m, x, o;

	expr = left;

	nld.value = nftnl_expr_get(nle, NFTNL_EXPR_BITWISE_MASK, &nld.len);
	mask = netlink_alloc_value(loc, &nld);
	mpz_init_set(m, mask->value);

	nld.value = nftnl_expr_get(nle, NFTNL_EXPR_BITWISE_XOR, &nld.len);
	xor  = netlink_alloc_value(loc, &nld);
	mpz_init_set(x, xor->value);

	mpz_init_set_ui(o, 0);
	if (mpz_scan0(m, 0) != mask->len || mpz_cmp_ui(x, 0)) {
		/* o = (m & x) ^ x */
		mpz_and(o, m, x);
		mpz_xor(o, o, x);
		/* x &= m */
		mpz_and(x, x, m);
		/* m |= o */
		mpz_ior(m, m, o);
	}

	if (left->len > 0 && mpz_scan0(m, 0) == left->len) {
		/* mask encompasses the entire value */
		expr_free(mask);
	} else {
		mpz_set(mask->value, m);
		expr = binop_expr_alloc(loc, OP_AND, expr, mask);
		expr->len = left->len;
	}

	if (mpz_cmp_ui(x, 0)) {
		mpz_set(xor->value, x);
		expr = binop_expr_alloc(loc, OP_XOR, expr, xor);
		expr->len = left->len;
	} else
		expr_free(xor);

	if (mpz_cmp_ui(o, 0)) {
		nld.value = nftnl_expr_get(nle, NFTNL_EXPR_BITWISE_XOR,
					   &nld.len);

		or = netlink_alloc_value(loc, &nld);
		mpz_set(or->value, o);
		expr = binop_expr_alloc(loc, OP_OR, expr, or);
		expr->len = left->len;
	}

	mpz_clear(m);
	mpz_clear(x);
	mpz_clear(o);

	return expr;
}

static struct expr *netlink_parse_bitwise_shift(struct netlink_parse_ctx *ctx,
						const struct location *loc,
						const struct nftnl_expr *nle,
						enum ops op,
						enum nft_registers sreg,
						struct expr *left)
{
	struct nft_data_delinearize nld;
	struct expr *expr, *right;

	nld.value = nftnl_expr_get(nle, NFTNL_EXPR_BITWISE_DATA, &nld.len);
	right = netlink_alloc_value(loc, &nld);
	right->byteorder = BYTEORDER_HOST_ENDIAN;

	expr = binop_expr_alloc(loc, op, left, right);
	expr->len = left->len;

	return expr;
}

static void netlink_parse_bitwise(struct netlink_parse_ctx *ctx,
				  const struct location *loc,
				  const struct nftnl_expr *nle)
{
	enum nft_registers sreg, dreg;
	struct expr *expr, *left;
	enum nft_bitwise_ops op;

	sreg = netlink_parse_register(nle, NFTNL_EXPR_BITWISE_SREG);
	left = netlink_get_register(ctx, loc, sreg);
	if (left == NULL)
		return netlink_error(ctx, loc,
				     "Bitwise expression has no left "
				     "hand side");

	op = nftnl_expr_get_u32(nle, NFTNL_EXPR_BITWISE_OP);

	switch (op) {
	case NFT_BITWISE_BOOL:
		expr = netlink_parse_bitwise_bool(ctx, loc, nle, sreg,
						  left);
		break;
	case NFT_BITWISE_LSHIFT:
		expr = netlink_parse_bitwise_shift(ctx, loc, nle, OP_LSHIFT,
						   sreg, left);
		break;
	case NFT_BITWISE_RSHIFT:
		expr = netlink_parse_bitwise_shift(ctx, loc, nle, OP_RSHIFT,
						   sreg, left);
		break;
	default:
		BUG("invalid bitwise operation %u\n", op);
	}

	dreg = netlink_parse_register(nle, NFTNL_EXPR_BITWISE_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static void netlink_parse_byteorder(struct netlink_parse_ctx *ctx,
				    const struct location *loc,
				    const struct nftnl_expr *nle)
{
	enum nft_registers sreg, dreg;
	struct expr *expr, *arg;
	enum ops op;

	sreg = netlink_parse_register(nle, NFTNL_EXPR_BYTEORDER_SREG);
	arg = netlink_get_register(ctx, loc, sreg);
	if (arg == NULL)
		return netlink_error(ctx, loc,
				     "Byteorder expression has no left "
				     "hand side");

	switch (nftnl_expr_get_u32(nle, NFTNL_EXPR_BYTEORDER_OP)) {
	case NFT_BYTEORDER_NTOH:
		op = OP_NTOH;
		break;
	case NFT_BYTEORDER_HTON:
		op = OP_HTON;
		break;
	default:
		BUG("invalid byteorder operation %u\n",
		    nftnl_expr_get_u32(nle, NFTNL_EXPR_BYTEORDER_OP));
	}

	expr = unary_expr_alloc(loc, op, arg);
	expr->len = arg->len;

	dreg = netlink_parse_register(nle, NFTNL_EXPR_BYTEORDER_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static void netlink_parse_payload_expr(struct netlink_parse_ctx *ctx,
				       const struct location *loc,
				       const struct nftnl_expr *nle)
{
	enum nft_registers dreg;
	uint32_t base, offset, len;
	struct expr *expr;

	base   = nftnl_expr_get_u32(nle, NFTNL_EXPR_PAYLOAD_BASE) + 1;
	offset = nftnl_expr_get_u32(nle, NFTNL_EXPR_PAYLOAD_OFFSET) * BITS_PER_BYTE;
	len    = nftnl_expr_get_u32(nle, NFTNL_EXPR_PAYLOAD_LEN) * BITS_PER_BYTE;

	expr = payload_expr_alloc(loc, NULL, 0);
	payload_init_raw(expr, base, offset, len);

	dreg = netlink_parse_register(nle, NFTNL_EXPR_PAYLOAD_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static void netlink_parse_payload_stmt(struct netlink_parse_ctx *ctx,
				       const struct location *loc,
				       const struct nftnl_expr *nle)
{
	enum nft_registers sreg;
	uint32_t base, offset, len;
	struct expr *expr, *val;
	struct stmt *stmt;

	base   = nftnl_expr_get_u32(nle, NFTNL_EXPR_PAYLOAD_BASE) + 1;
	offset = nftnl_expr_get_u32(nle, NFTNL_EXPR_PAYLOAD_OFFSET) * BITS_PER_BYTE;
	len    = nftnl_expr_get_u32(nle, NFTNL_EXPR_PAYLOAD_LEN) * BITS_PER_BYTE;

	sreg = netlink_parse_register(nle, NFTNL_EXPR_PAYLOAD_SREG);
	val  = netlink_get_register(ctx, loc, sreg);
	if (val == NULL)
		return netlink_error(ctx, loc,
				     "payload statement has no expression");

	expr = payload_expr_alloc(loc, NULL, 0);
	payload_init_raw(expr, base, offset, len);

	stmt = payload_stmt_alloc(loc, expr, val);
	rule_stmt_append(ctx->rule, stmt);
}

static void netlink_parse_payload(struct netlink_parse_ctx *ctx,
				  const struct location *loc,
				  const struct nftnl_expr *nle)
{
	if (nftnl_expr_is_set(nle, NFTNL_EXPR_PAYLOAD_DREG))
		netlink_parse_payload_expr(ctx, loc, nle);
	else
		netlink_parse_payload_stmt(ctx, loc, nle);
}

static void netlink_parse_exthdr(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *nle)
{
	uint32_t offset, len, flags;
	enum nft_registers dreg;
	enum nft_exthdr_op op;
	uint8_t type;
	struct expr *expr;

	type   = nftnl_expr_get_u8(nle, NFTNL_EXPR_EXTHDR_TYPE);
	offset = nftnl_expr_get_u32(nle, NFTNL_EXPR_EXTHDR_OFFSET) * BITS_PER_BYTE;
	len    = nftnl_expr_get_u32(nle, NFTNL_EXPR_EXTHDR_LEN) * BITS_PER_BYTE;
	op     = nftnl_expr_get_u32(nle, NFTNL_EXPR_EXTHDR_OP);
	flags  = nftnl_expr_get_u32(nle, NFTNL_EXPR_EXTHDR_FLAGS);

	expr = exthdr_expr_alloc(loc, NULL, 0);
	exthdr_init_raw(expr, type, offset, len, op, flags);

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_EXTHDR_DREG)) {
		dreg = netlink_parse_register(nle, NFTNL_EXPR_EXTHDR_DREG);
		netlink_set_register(ctx, dreg, expr);
	} else if (nftnl_expr_is_set(nle, NFTNL_EXPR_EXTHDR_SREG)) {
		enum nft_registers sreg;
		struct stmt *stmt;
		struct expr *val;

		sreg = netlink_parse_register(nle, NFTNL_EXPR_EXTHDR_SREG);
		val = netlink_get_register(ctx, loc, sreg);
		if (val == NULL) {
			xfree(expr);
			return netlink_error(ctx, loc,
					     "exthdr statement has no expression");
		}

		expr_set_type(val, expr->dtype, expr->byteorder);

		stmt = exthdr_stmt_alloc(loc, expr, val);
		rule_stmt_append(ctx->rule, stmt);
	}
}

static void netlink_parse_hash(struct netlink_parse_ctx *ctx,
			       const struct location *loc,
			       const struct nftnl_expr *nle)
{
	enum nft_registers sreg, dreg;
	struct expr *expr, *hexpr;
	uint32_t mod, seed, len, offset;
	enum nft_hash_types type;
	bool seed_set;

	type = nftnl_expr_get_u32(nle, NFTNL_EXPR_HASH_TYPE);
	offset = nftnl_expr_get_u32(nle, NFTNL_EXPR_HASH_OFFSET);
	seed_set = nftnl_expr_is_set(nle, NFTNL_EXPR_HASH_SEED);
	seed = nftnl_expr_get_u32(nle, NFTNL_EXPR_HASH_SEED);
	mod  = nftnl_expr_get_u32(nle, NFTNL_EXPR_HASH_MODULUS);

	expr = hash_expr_alloc(loc, mod, seed_set, seed, offset, type);

	if (type != NFT_HASH_SYM) {
		sreg = netlink_parse_register(nle, NFTNL_EXPR_HASH_SREG);
		hexpr = netlink_get_register(ctx, loc, sreg);

		if (hexpr == NULL) {
			netlink_error(ctx, loc,
				      "hash statement has no expression");
			goto out_err;
		}
		len = nftnl_expr_get_u32(nle,
					 NFTNL_EXPR_HASH_LEN) * BITS_PER_BYTE;
		if (hexpr->len < len) {
			xfree(hexpr);
			hexpr = netlink_parse_concat_expr(ctx, loc, sreg, len);
			if (hexpr == NULL)
				goto out_err;
		}
		expr->hash.expr = hexpr;
	}

	dreg = netlink_parse_register(nle, NFTNL_EXPR_HASH_DREG);
	netlink_set_register(ctx, dreg, expr);
	return;
out_err:
	xfree(expr);
}

static void netlink_parse_fib(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	enum nft_registers dreg;
	struct expr *expr;
	uint32_t flags, result;

	flags = nftnl_expr_get_u32(nle, NFTNL_EXPR_FIB_FLAGS);
	result = nftnl_expr_get_u32(nle, NFTNL_EXPR_FIB_RESULT);

	expr = fib_expr_alloc(loc, flags, result);

	dreg = netlink_parse_register(nle, NFTNL_EXPR_FIB_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static void netlink_parse_meta_expr(struct netlink_parse_ctx *ctx,
				    const struct location *loc,
				    const struct nftnl_expr *nle)
{
	enum nft_registers dreg;
	uint32_t key;
	struct expr *expr;

	key  = nftnl_expr_get_u32(nle, NFTNL_EXPR_META_KEY);
	expr = meta_expr_alloc(loc, key);

	dreg = netlink_parse_register(nle, NFTNL_EXPR_META_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static void netlink_parse_socket(struct netlink_parse_ctx *ctx,
				      const struct location *loc,
				      const struct nftnl_expr *nle)
{
	enum nft_registers dreg;
	uint32_t key;
	struct expr * expr;

	key = nftnl_expr_get_u32(nle, NFTNL_EXPR_SOCKET_KEY);
	expr = socket_expr_alloc(loc, key);

	dreg = netlink_parse_register(nle, NFTNL_EXPR_SOCKET_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static void netlink_parse_osf(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	enum nft_registers dreg;
	struct expr *expr;
	uint32_t flags;
	uint8_t ttl;

	ttl = nftnl_expr_get_u8(nle, NFTNL_EXPR_OSF_TTL);
	flags = nftnl_expr_get_u32(nle, NFTNL_EXPR_OSF_FLAGS);
	expr = osf_expr_alloc(loc, ttl, flags);

	dreg = netlink_parse_register(nle, NFTNL_EXPR_OSF_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static void netlink_parse_meta_stmt(struct netlink_parse_ctx *ctx,
				    const struct location *loc,
				    const struct nftnl_expr *nle)
{
	enum nft_registers sreg;
	uint32_t key;
	struct stmt *stmt;
	struct expr *expr;

	sreg = netlink_parse_register(nle, NFTNL_EXPR_META_SREG);
	expr = netlink_get_register(ctx, loc, sreg);
	if (expr == NULL)
		return netlink_error(ctx, loc,
				     "meta statement has no expression");

	key  = nftnl_expr_get_u32(nle, NFTNL_EXPR_META_KEY);
	stmt = meta_stmt_alloc(loc, key, expr);
	expr_set_type(expr, stmt->meta.tmpl->dtype, stmt->meta.tmpl->byteorder);

	ctx->stmt = stmt;
}

static void netlink_parse_meta(struct netlink_parse_ctx *ctx,
			       const struct location *loc,
			       const struct nftnl_expr *nle)
{
	if (nftnl_expr_is_set(nle, NFTNL_EXPR_META_DREG))
		netlink_parse_meta_expr(ctx, loc, nle);
	else
		netlink_parse_meta_stmt(ctx, loc, nle);
}

static void netlink_parse_rt(struct netlink_parse_ctx *ctx,
			     const struct location *loc,
			     const struct nftnl_expr *nle)
{
	enum nft_registers dreg;
	uint32_t key;
	struct expr *expr;

	key  = nftnl_expr_get_u32(nle, NFTNL_EXPR_RT_KEY);
	expr = rt_expr_alloc(loc, key, false);

	dreg = netlink_parse_register(nle, NFTNL_EXPR_RT_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static void netlink_parse_numgen(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *nle)
{
	uint32_t type, until, offset;
	enum nft_registers dreg;
	struct expr *expr;

	type  = nftnl_expr_get_u32(nle, NFTNL_EXPR_NG_TYPE);
	until = nftnl_expr_get_u32(nle, NFTNL_EXPR_NG_MODULUS);
	offset = nftnl_expr_get_u32(nle, NFTNL_EXPR_NG_OFFSET);

	expr = numgen_expr_alloc(loc, type, until, offset);
	dreg = netlink_parse_register(nle, NFTNL_EXPR_NG_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static void netlink_parse_notrack(struct netlink_parse_ctx *ctx,
				  const struct location *loc,
				  const struct nftnl_expr *nle)
{
	ctx->stmt = notrack_stmt_alloc(loc);
}

static void netlink_parse_flow_offload(struct netlink_parse_ctx *ctx,
				       const struct location *loc,
				       const struct nftnl_expr *nle)
{
	const char *table_name;

	table_name = xstrdup(nftnl_expr_get_str(nle, NFTNL_EXPR_FLOW_TABLE_NAME));
	ctx->stmt = flow_offload_stmt_alloc(loc, table_name);
}

static void netlink_parse_ct_stmt(struct netlink_parse_ctx *ctx,
				  const struct location *loc,
				  const struct nftnl_expr *nle)
{
	enum nft_registers sreg;
	uint32_t key;
	struct stmt *stmt;
	struct expr *expr;
	int8_t dir = -1;

	sreg = netlink_parse_register(nle, NFTNL_EXPR_CT_SREG);
	expr = netlink_get_register(ctx, loc, sreg);
	if (expr == NULL)
		return netlink_error(ctx, loc,
				     "ct statement has no expression");

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_CT_DIR))
		dir = nftnl_expr_get_u8(nle, NFTNL_EXPR_CT_DIR);

	key  = nftnl_expr_get_u32(nle, NFTNL_EXPR_CT_KEY);
	stmt = ct_stmt_alloc(loc, key, dir, expr);
	expr_set_type(expr, stmt->ct.tmpl->dtype, stmt->ct.tmpl->byteorder);

	ctx->stmt = stmt;
}

static void netlink_parse_ct_expr(struct netlink_parse_ctx *ctx,
				  const struct location *loc,
				  const struct nftnl_expr *nle)
{
	struct expr *expr = NULL;
	enum nft_registers dreg;
	int8_t dir = -1;
	uint32_t key;

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_CT_DIR))
		dir = nftnl_expr_get_u8(nle, NFTNL_EXPR_CT_DIR);

	key  = nftnl_expr_get_u32(nle, NFTNL_EXPR_CT_KEY);
	expr = ct_expr_alloc(loc, key, dir);

	dreg = netlink_parse_register(nle, NFTNL_EXPR_CT_DREG);
	netlink_set_register(ctx, dreg, expr);
}

static void netlink_parse_ct(struct netlink_parse_ctx *ctx,
			     const struct location *loc,
			     const struct nftnl_expr *nle)
{
	if (nftnl_expr_is_set(nle, NFTNL_EXPR_CT_DREG))
		netlink_parse_ct_expr(ctx, loc, nle);
	else
		netlink_parse_ct_stmt(ctx, loc, nle);
}

static void netlink_parse_connlimit(struct netlink_parse_ctx *ctx,
				    const struct location *loc,
				    const struct nftnl_expr *nle)
{
	struct stmt *stmt;

	stmt = connlimit_stmt_alloc(loc);
	stmt->connlimit.count =
		nftnl_expr_get_u32(nle, NFTNL_EXPR_CONNLIMIT_COUNT);
	stmt->connlimit.flags =
		nftnl_expr_get_u32(nle, NFTNL_EXPR_CONNLIMIT_FLAGS);

	ctx->stmt = stmt;
}

static void netlink_parse_counter(struct netlink_parse_ctx *ctx,
				  const struct location *loc,
				  const struct nftnl_expr *nle)
{
	struct stmt *stmt;

	stmt = counter_stmt_alloc(loc);
	stmt->counter.packets = nftnl_expr_get_u64(nle, NFTNL_EXPR_CTR_PACKETS);
	stmt->counter.bytes   = nftnl_expr_get_u64(nle, NFTNL_EXPR_CTR_BYTES);

	ctx->stmt = stmt;
}

static void netlink_parse_log(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	struct stmt *stmt;
	const char *prefix;

	stmt = log_stmt_alloc(loc);
	prefix = nftnl_expr_get_str(nle, NFTNL_EXPR_LOG_PREFIX);
	if (nftnl_expr_is_set(nle, NFTNL_EXPR_LOG_PREFIX)) {
		stmt->log.prefix = constant_expr_alloc(&internal_location,
						       &string_type,
						       BYTEORDER_HOST_ENDIAN,
						       (strlen(prefix) + 1) * BITS_PER_BYTE,
						       prefix);
		stmt->log.flags |= STMT_LOG_PREFIX;
	}
	if (nftnl_expr_is_set(nle, NFTNL_EXPR_LOG_GROUP)) {
		stmt->log.group = nftnl_expr_get_u16(nle, NFTNL_EXPR_LOG_GROUP);
		stmt->log.flags |= STMT_LOG_GROUP;
	}
	if (nftnl_expr_is_set(nle, NFTNL_EXPR_LOG_SNAPLEN)) {
		stmt->log.snaplen =
			nftnl_expr_get_u32(nle, NFTNL_EXPR_LOG_SNAPLEN);
		stmt->log.flags |= STMT_LOG_SNAPLEN;
	}
	if (nftnl_expr_is_set(nle, NFTNL_EXPR_LOG_QTHRESHOLD)) {
		stmt->log.qthreshold =
			nftnl_expr_get_u16(nle, NFTNL_EXPR_LOG_QTHRESHOLD);
		stmt->log.flags |= STMT_LOG_QTHRESHOLD;
	}
	if (nftnl_expr_is_set(nle, NFTNL_EXPR_LOG_LEVEL)) {
		stmt->log.level =
			nftnl_expr_get_u32(nle, NFTNL_EXPR_LOG_LEVEL);
		stmt->log.flags |= STMT_LOG_LEVEL;
	}
	if (nftnl_expr_is_set(nle, NFTNL_EXPR_LOG_FLAGS)) {
		stmt->log.logflags =
			nftnl_expr_get_u32(nle, NFTNL_EXPR_LOG_FLAGS);
	}

	ctx->stmt = stmt;
}

static void netlink_parse_limit(struct netlink_parse_ctx *ctx,
				const struct location *loc,
				const struct nftnl_expr *nle)
{
	struct stmt *stmt;

	stmt = limit_stmt_alloc(loc);
	stmt->limit.rate = nftnl_expr_get_u64(nle, NFTNL_EXPR_LIMIT_RATE);
	stmt->limit.unit = nftnl_expr_get_u64(nle, NFTNL_EXPR_LIMIT_UNIT);
	stmt->limit.type = nftnl_expr_get_u32(nle, NFTNL_EXPR_LIMIT_TYPE);
	stmt->limit.burst = nftnl_expr_get_u32(nle, NFTNL_EXPR_LIMIT_BURST);
	stmt->limit.flags = nftnl_expr_get_u32(nle, NFTNL_EXPR_LIMIT_FLAGS);

	ctx->stmt = stmt;
}

static void netlink_parse_quota(struct netlink_parse_ctx *ctx,
				const struct location *loc,
				const struct nftnl_expr *nle)
{
	struct stmt *stmt;

	stmt = quota_stmt_alloc(loc);
	stmt->quota.bytes = nftnl_expr_get_u64(nle, NFTNL_EXPR_QUOTA_BYTES);
	stmt->quota.used =
		nftnl_expr_get_u64(nle, NFTNL_EXPR_QUOTA_CONSUMED);
	stmt->quota.flags = nftnl_expr_get_u32(nle, NFTNL_EXPR_QUOTA_FLAGS);

	ctx->stmt = stmt;
}

static void netlink_parse_reject(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *expr)
{
	struct stmt *stmt;
	uint8_t icmp_code;

	stmt = reject_stmt_alloc(loc);
	stmt->reject.type = nftnl_expr_get_u32(expr, NFTNL_EXPR_REJECT_TYPE);
	icmp_code = nftnl_expr_get_u8(expr, NFTNL_EXPR_REJECT_CODE);
	stmt->reject.icmp_code = icmp_code;
	stmt->reject.expr = constant_expr_alloc(loc, &integer_type,
						BYTEORDER_HOST_ENDIAN, 8,
						&icmp_code);
	ctx->stmt = stmt;
}

static bool is_nat_addr_map(const struct expr *addr, uint8_t family)
{
	const struct expr *mappings, *data;
	const struct set *set;

	if (!addr ||
	    expr_ops(addr)->type != EXPR_MAP)
		return false;

	mappings = addr->right;
	if (expr_ops(mappings)->type != EXPR_SET_REF)
		return false;

	set = mappings->set;
	data = set->data;

	if (!(data->flags & EXPR_F_INTERVAL))
		return false;

	/* if we're dealing with an address:address map,
	 * the length will be bit_sizeof(addr) + 32 (one register).
	 */
	switch (family) {
	case NFPROTO_IPV4:
		return data->len == 32 + 32;
	case NFPROTO_IPV6:
		return data->len == 128 + 128;
	}

	return false;
}

static bool is_nat_proto_map(const struct expr *addr, uint8_t family)
{
	const struct expr *mappings, *data;
	const struct set *set;

	if (!addr ||
	    expr_ops(addr)->type != EXPR_MAP)
		return false;

	mappings = addr->right;
	if (expr_ops(mappings)->type != EXPR_SET_REF)
		return false;

	set = mappings->set;
	data = set->data;

	/* if we're dealing with an address:inet_service map,
	 * the length will be bit_sizeof(addr) + 32 (one register).
	 */
	switch (family) {
	case NFPROTO_IPV4:
		return data->len == 32 + 32;
	case NFPROTO_IPV6:
		return data->len == 128 + 32;
	}

	return false;
}

static void netlink_parse_nat(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	struct stmt *stmt;
	struct expr *addr, *proto;
	enum nft_registers reg1, reg2;
	int family;

	stmt = nat_stmt_alloc(loc,
			      nftnl_expr_get_u32(nle, NFTNL_EXPR_NAT_TYPE));

	family = nftnl_expr_get_u32(nle, NFTNL_EXPR_NAT_FAMILY);

	if (ctx->table->handle.family == NFPROTO_INET)
		stmt->nat.family = family;

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_NAT_FLAGS))
		stmt->nat.flags = nftnl_expr_get_u32(nle, NFTNL_EXPR_NAT_FLAGS);

	if (stmt->nat.flags & NF_NAT_RANGE_NETMAP)
		stmt->nat.type_flags |= STMT_NAT_F_PREFIX;

	addr = NULL;
	reg1 = netlink_parse_register(nle, NFTNL_EXPR_NAT_REG_ADDR_MIN);
	if (reg1) {
		addr = netlink_get_register(ctx, loc, reg1);
		if (addr == NULL) {
			netlink_error(ctx, loc,
				      "NAT statement has no address expression");
			goto out_err;
		}

		if (family == NFPROTO_IPV4)
			expr_set_type(addr, &ipaddr_type, BYTEORDER_BIG_ENDIAN);
		else
			expr_set_type(addr, &ip6addr_type,
				      BYTEORDER_BIG_ENDIAN);
		stmt->nat.addr = addr;
	}

	if (is_nat_addr_map(addr, family)) {
		stmt->nat.family = family;
		stmt->nat.type_flags |= STMT_NAT_F_INTERVAL;
		ctx->stmt = stmt;
		return;
	}

	reg2 = netlink_parse_register(nle, NFTNL_EXPR_NAT_REG_ADDR_MAX);
	if (reg2 && reg2 != reg1) {
		addr = netlink_get_register(ctx, loc, reg2);
		if (addr == NULL) {
			netlink_error(ctx, loc,
				      "NAT statement has no address expression");
			goto out_err;
		}

		if (family == NFPROTO_IPV4)
			expr_set_type(addr, &ipaddr_type, BYTEORDER_BIG_ENDIAN);
		else
			expr_set_type(addr, &ip6addr_type,
				      BYTEORDER_BIG_ENDIAN);
		if (stmt->nat.addr != NULL) {
			addr = range_expr_alloc(loc, stmt->nat.addr, addr);
			addr = range_expr_to_prefix(addr);
		}
		stmt->nat.addr = addr;
	}

	if (is_nat_proto_map(addr, family)) {
		stmt->nat.family = family;
		stmt->nat.type_flags |= STMT_NAT_F_CONCAT;
		ctx->stmt = stmt;
		return;
	}

	reg1 = netlink_parse_register(nle, NFTNL_EXPR_NAT_REG_PROTO_MIN);
	if (reg1) {
		proto = netlink_get_register(ctx, loc, reg1);
		if (proto == NULL) {
			netlink_error(ctx, loc,
				      "NAT statement has no proto expression");
			goto out_err;
		}

		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		stmt->nat.proto = proto;
	}

	reg2 = netlink_parse_register(nle, NFTNL_EXPR_NAT_REG_PROTO_MAX);
	if (reg2 && reg2 != reg1) {
		proto = netlink_get_register(ctx, loc, reg2);
		if (proto == NULL) {
			netlink_error(ctx, loc,
				      "NAT statement has no proto expression");
			goto out_err;
		}

		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		if (stmt->nat.proto != NULL)
			proto = range_expr_alloc(loc, stmt->nat.proto, proto);
		stmt->nat.proto = proto;
	}

	ctx->stmt = stmt;
	return;
out_err:
	xfree(stmt);
}

static void netlink_parse_synproxy(struct netlink_parse_ctx *ctx,
				   const struct location *loc,
				   const struct nftnl_expr *nle)
{
	struct stmt *stmt;

	stmt = synproxy_stmt_alloc(loc);
	stmt->synproxy.mss = nftnl_expr_get_u16(nle, NFTNL_EXPR_SYNPROXY_MSS);
	stmt->synproxy.wscale = nftnl_expr_get_u8(nle,
						  NFTNL_EXPR_SYNPROXY_WSCALE);
	stmt->synproxy.flags = nftnl_expr_get_u32(nle,
						  NFTNL_EXPR_SYNPROXY_FLAGS);

	ctx->stmt = stmt;
}

static void netlink_parse_tproxy(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	struct stmt *stmt;
	struct expr *addr, *port;
	enum nft_registers reg;

	stmt = tproxy_stmt_alloc(loc);
	stmt->tproxy.family = nftnl_expr_get_u32(nle, NFTNL_EXPR_TPROXY_FAMILY);
	stmt->tproxy.table_family = ctx->table->handle.family;

	reg = netlink_parse_register(nle, NFTNL_EXPR_TPROXY_REG_ADDR);
	if (reg) {
		addr = netlink_get_register(ctx, loc, reg);
		if (addr == NULL)
			goto err;

		switch (stmt->tproxy.family) {
		case NFPROTO_IPV4:
			expr_set_type(addr, &ipaddr_type, BYTEORDER_BIG_ENDIAN);
			break;
		case NFPROTO_IPV6:
			expr_set_type(addr, &ip6addr_type, BYTEORDER_BIG_ENDIAN);
			break;
		default:
			netlink_error(ctx, loc,
				      "tproxy address must be IPv4 or IPv6");
			goto err;
		}
		stmt->tproxy.addr = addr;
	}

	reg = netlink_parse_register(nle, NFTNL_EXPR_TPROXY_REG_PORT);
	if (reg) {
		port = netlink_get_register(ctx, loc, reg);
		if (port == NULL)
			goto err;
		expr_set_type(port, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		stmt->tproxy.port = port;
	}

	ctx->stmt = stmt;
	return;
err:
	xfree(stmt);
}

static void netlink_parse_masq(struct netlink_parse_ctx *ctx,
			       const struct location *loc,
			       const struct nftnl_expr *nle)
{
	enum nft_registers reg1, reg2;
	struct expr *proto;
	struct stmt *stmt;
	uint32_t flags = 0;

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_MASQ_FLAGS))
		flags = nftnl_expr_get_u32(nle, NFTNL_EXPR_MASQ_FLAGS);

	stmt = nat_stmt_alloc(loc, NFT_NAT_MASQ);
	stmt->nat.flags = flags;

	reg1 = netlink_parse_register(nle, NFTNL_EXPR_MASQ_REG_PROTO_MIN);
	if (reg1) {
		proto = netlink_get_register(ctx, loc, reg1);
		if (proto == NULL) {
			netlink_error(ctx, loc,
				      "MASQUERADE statement has no proto expression");
			goto out_err;
		}
		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		stmt->nat.proto = proto;
	}

	reg2 = netlink_parse_register(nle, NFTNL_EXPR_MASQ_REG_PROTO_MAX);
	if (reg2 && reg2 != reg1) {
		proto = netlink_get_register(ctx, loc, reg2);
		if (proto == NULL) {
			netlink_error(ctx, loc,
				      "MASQUERADE statement has no proto expression");
			goto out_err;
		}
		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		if (stmt->nat.proto != NULL)
			proto = range_expr_alloc(loc, stmt->nat.proto, proto);
		stmt->nat.proto = proto;
	}

	ctx->stmt = stmt;
	return;
out_err:
	xfree(stmt);
}

static void netlink_parse_redir(struct netlink_parse_ctx *ctx,
				const struct location *loc,
				const struct nftnl_expr *nle)
{
	struct stmt *stmt;
	struct expr *proto;
	enum nft_registers reg1, reg2;
	uint32_t flags;

	stmt = nat_stmt_alloc(loc, NFT_NAT_REDIR);

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_REDIR_FLAGS)) {
		flags = nftnl_expr_get_u32(nle, NFTNL_EXPR_REDIR_FLAGS);
		stmt->nat.flags = flags;
	}

	reg1 = netlink_parse_register(nle, NFTNL_EXPR_REDIR_REG_PROTO_MIN);
	if (reg1) {
		proto = netlink_get_register(ctx, loc, reg1);
		if (proto == NULL) {
			netlink_error(ctx, loc,
				      "redirect statement has no proto expression");
			goto out_err;
		}

		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		stmt->nat.proto = proto;
	}

	reg2 = netlink_parse_register(nle, NFTNL_EXPR_REDIR_REG_PROTO_MAX);
	if (reg2 && reg2 != reg1) {
		proto = netlink_get_register(ctx, loc, reg2);
		if (proto == NULL) {
			netlink_error(ctx, loc,
				      "redirect statement has no proto expression");
			goto out_err;
		}

		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		if (stmt->nat.proto != NULL)
			proto = range_expr_alloc(loc, stmt->nat.proto,
						 proto);
		stmt->nat.proto = proto;
	}

	ctx->stmt = stmt;
	return;
out_err:
	xfree(stmt);
}

static void netlink_parse_dup(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	enum nft_registers reg1, reg2;
	struct expr *addr, *dev;
	struct stmt *stmt;

	stmt = dup_stmt_alloc(loc);

	reg1 = netlink_parse_register(nle, NFTNL_EXPR_DUP_SREG_ADDR);
	if (reg1) {
		addr = netlink_get_register(ctx, loc, reg1);
		if (addr == NULL) {
			netlink_error(ctx, loc,
				      "DUP statement has no destination expression");
			goto out_err;
		}

		switch (ctx->table->handle.family) {
		case NFPROTO_IPV4:
			expr_set_type(addr, &ipaddr_type, BYTEORDER_BIG_ENDIAN);
			break;
		case NFPROTO_IPV6:
			expr_set_type(addr, &ip6addr_type,
				      BYTEORDER_BIG_ENDIAN);
			break;
		}
		stmt->dup.to = addr;
	}

	reg2 = netlink_parse_register(nle, NFTNL_EXPR_DUP_SREG_DEV);
	if (reg2) {
		dev = netlink_get_register(ctx, loc, reg2);
		if (dev == NULL) {
			netlink_error(ctx, loc,
				      "DUP statement has no output expression");
			goto out_err;
		}

		expr_set_type(dev, &ifindex_type, BYTEORDER_HOST_ENDIAN);
		if (stmt->dup.to == NULL)
			stmt->dup.to = dev;
		else
			stmt->dup.dev = dev;
	}

	ctx->stmt = stmt;
	return;
out_err:
	xfree(stmt);
}

static void netlink_parse_fwd(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	enum nft_registers reg1, reg2;
	struct expr *dev, *addr;
	struct stmt *stmt;

	stmt = fwd_stmt_alloc(loc);

	reg1 = netlink_parse_register(nle, NFTNL_EXPR_FWD_SREG_DEV);
	if (reg1) {
		dev = netlink_get_register(ctx, loc, reg1);
		if (dev == NULL) {
			netlink_error(ctx, loc,
				      "fwd statement has no output expression");
			goto out_err;
		}

		expr_set_type(dev, &ifindex_type, BYTEORDER_HOST_ENDIAN);
		stmt->fwd.dev = dev;
	}

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_FWD_NFPROTO)) {
		stmt->fwd.family =
			nftnl_expr_get_u32(nle, NFTNL_EXPR_FWD_NFPROTO);
	}

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_FWD_SREG_ADDR)) {
		reg2 = netlink_parse_register(nle, NFTNL_EXPR_FWD_SREG_ADDR);
		if (reg2) {
			addr = netlink_get_register(ctx, loc, reg2);
			if (addr == NULL) {
				netlink_error(ctx, loc,
					      "fwd statement has no output expression");
				goto out_err;
			}

			switch (stmt->fwd.family) {
			case AF_INET:
				expr_set_type(addr, &ipaddr_type,
					      BYTEORDER_BIG_ENDIAN);
				break;
			case AF_INET6:
				expr_set_type(addr, &ip6addr_type,
					      BYTEORDER_BIG_ENDIAN);
				break;
			default:
				netlink_error(ctx, loc,
					      "fwd statement has no family");
				goto out_err;
			}
			stmt->fwd.addr = addr;
		}
	}

	ctx->stmt = stmt;
	return;
out_err:
	xfree(stmt);
}

static void netlink_parse_queue(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	struct expr *expr, *high;
	struct stmt *stmt;
	uint16_t num, total;

	num   = nftnl_expr_get_u16(nle, NFTNL_EXPR_QUEUE_NUM);
	total = nftnl_expr_get_u16(nle, NFTNL_EXPR_QUEUE_TOTAL);

	expr = constant_expr_alloc(loc, &integer_type,
				   BYTEORDER_HOST_ENDIAN, 16, &num);
	if (total > 1) {
		total += num - 1;
		high = constant_expr_alloc(loc, &integer_type,
					   BYTEORDER_HOST_ENDIAN, 16, &total);
		expr = range_expr_alloc(loc, expr, high);
	}

	stmt = queue_stmt_alloc(loc);
	stmt->queue.queue = expr;
	stmt->queue.flags = nftnl_expr_get_u16(nle, NFTNL_EXPR_QUEUE_FLAGS);

	ctx->stmt = stmt;
}

struct dynset_parse_ctx {
	struct netlink_parse_ctx	*nlctx;
	const struct location		*loc;
	struct list_head		stmt_list;
};

static int dynset_parse_expressions(struct nftnl_expr *e, void *data)
{
	struct dynset_parse_ctx *dynset_parse_ctx = data;
	struct netlink_parse_ctx *ctx = dynset_parse_ctx->nlctx;
	const struct location *loc = dynset_parse_ctx->loc;
	struct stmt *stmt;

	if (netlink_parse_expr(e, ctx) < 0 || !ctx->stmt) {
		netlink_error(ctx, loc, "Could not parse dynset stmt");
		return -1;
	}
	stmt = ctx->stmt;

	list_add_tail(&stmt->list, &dynset_parse_ctx->stmt_list);

	return 0;
}

static void netlink_parse_dynset(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *nle)
{
	struct dynset_parse_ctx dynset_parse_ctx = {
		.nlctx	= ctx,
		.loc	= loc,
	};
	struct expr *expr, *expr_data = NULL;
	enum nft_registers sreg, sreg_data;
	struct stmt *stmt, *dstmt, *next;
	const struct nftnl_expr *dnle;
	struct set *set;
	const char *name;

	init_list_head(&dynset_parse_ctx.stmt_list);

	name = nftnl_expr_get_str(nle, NFTNL_EXPR_DYNSET_SET_NAME);
	set  = set_lookup(ctx->table, name);
	if (set == NULL)
		return netlink_error(ctx, loc,
				     "Unknown set '%s' in dynset statement",
				     name);

	sreg = netlink_parse_register(nle, NFTNL_EXPR_DYNSET_SREG_KEY);
	expr = netlink_get_register(ctx, loc, sreg);
	if (expr == NULL)
		return netlink_error(ctx, loc,
				     "Dynset statement has no key expression");

	if (expr->len < set->key->len) {
		expr_free(expr);
		expr = netlink_parse_concat_expr(ctx, loc, sreg, set->key->len);
		if (expr == NULL)
			return;
	}

	expr = set_elem_expr_alloc(&expr->location, expr);
	expr->timeout = nftnl_expr_get_u64(nle, NFTNL_EXPR_DYNSET_TIMEOUT);

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_DYNSET_EXPR)) {
		dstmt = NULL;
		dnle = nftnl_expr_get(nle, NFTNL_EXPR_DYNSET_EXPR, NULL);
		if (dnle != NULL) {
			if (netlink_parse_expr(dnle, ctx) < 0)
				goto out_err;
			if (ctx->stmt == NULL) {
				netlink_error(ctx, loc,
					      "Could not parse dynset stmt");
				goto out_err;
			}
			dstmt = ctx->stmt;
			list_add_tail(&dstmt->list,
				      &dynset_parse_ctx.stmt_list);
		}
	} else if (nftnl_expr_is_set(nle, NFTNL_EXPR_DYNSET_EXPRESSIONS)) {
		if (nftnl_expr_expr_foreach(nle, dynset_parse_expressions,
					    &dynset_parse_ctx) < 0)
			goto out_err;
	}

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_DYNSET_SREG_DATA)) {
		sreg_data = netlink_parse_register(nle, NFTNL_EXPR_DYNSET_SREG_DATA);
		expr_data = netlink_get_register(ctx, loc, sreg_data);
	}

	if (expr_data != NULL) {
		expr_set_type(expr_data, set->data->dtype, set->data->byteorder);
		stmt = map_stmt_alloc(loc);
		stmt->map.set	= set_ref_expr_alloc(loc, set);
		stmt->map.key	= expr;
		stmt->map.data	= expr_data;
		stmt->map.op	= nftnl_expr_get_u32(nle, NFTNL_EXPR_DYNSET_OP);
		list_splice_tail(&dynset_parse_ctx.stmt_list,
				 &stmt->map.stmt_list);
	} else {
		if (!list_empty(&dynset_parse_ctx.stmt_list) &&
		    set->flags & NFT_SET_ANONYMOUS) {
			stmt = meter_stmt_alloc(loc);
			stmt->meter.set  = set_ref_expr_alloc(loc, set);
			stmt->meter.key  = expr;
			stmt->meter.stmt = list_first_entry(&dynset_parse_ctx.stmt_list,
							    struct stmt, list);
			stmt->meter.size = set->desc.size;
		} else {
			stmt = set_stmt_alloc(loc);
			stmt->set.set   = set_ref_expr_alloc(loc, set);
			stmt->set.op    = nftnl_expr_get_u32(nle, NFTNL_EXPR_DYNSET_OP);
			stmt->set.key   = expr;
			list_splice_tail(&dynset_parse_ctx.stmt_list,
					 &stmt->set.stmt_list);
		}
	}

	ctx->stmt = stmt;
	return;
out_err:
	list_for_each_entry_safe(dstmt, next, &dynset_parse_ctx.stmt_list, list)
		stmt_free(dstmt);

	xfree(expr);
}

static void netlink_parse_objref(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *nle)
{
	uint32_t type = nftnl_expr_get_u32(nle, NFTNL_EXPR_OBJREF_IMM_TYPE);
	struct expr *expr;
	struct stmt *stmt;

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_OBJREF_IMM_NAME)) {
		struct nft_data_delinearize nld;

		type = nftnl_expr_get_u32(nle, NFTNL_EXPR_OBJREF_IMM_TYPE);
		nld.value = nftnl_expr_get(nle, NFTNL_EXPR_OBJREF_IMM_NAME,
					   &nld.len);
		expr = netlink_alloc_value(&netlink_location, &nld);
		datatype_set(expr, &string_type);
		expr->byteorder = BYTEORDER_HOST_ENDIAN;
	} else if (nftnl_expr_is_set(nle, NFTNL_EXPR_OBJREF_SET_SREG)) {
		struct expr *left, *right;
		enum nft_registers sreg;
		const char *name;
		struct set *set;

		name = nftnl_expr_get_str(nle, NFTNL_EXPR_OBJREF_SET_NAME);
		set  = set_lookup(ctx->table, name);
		if (set == NULL)
			return netlink_error(ctx, loc,
					     "Unknown set '%s' in objref expression",
					     name);

		sreg = netlink_parse_register(nle, NFTNL_EXPR_OBJREF_SET_SREG);
		left = netlink_get_register(ctx, loc, sreg);
		if (left == NULL)
			return netlink_error(ctx, loc,
					     "objref expression has no left hand side");

		if (left->len < set->key->len) {
			expr_free(left);
			left = netlink_parse_concat_expr(ctx, loc, sreg, set->key->len);
			if (left == NULL)
				return;
		}

		right = set_ref_expr_alloc(loc, set);
		expr = map_expr_alloc(loc, left, right);
		expr_set_type(expr, &string_type, BYTEORDER_HOST_ENDIAN);
		type = set->objtype;
	} else {
		netlink_error(ctx, loc, "unknown objref expression type %u",
			      type);
		return;
	}

	stmt = objref_stmt_alloc(loc);
	stmt->objref.type = type;
	stmt->objref.expr = expr;
	ctx->stmt = stmt;
}

struct expr_handler {
	const char	*name;
	void		(*parse)(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *nle);
};

static const struct expr_handler netlink_parsers[] = {
	{ .name = "immediate",	.parse = netlink_parse_immediate },
	{ .name = "cmp",	.parse = netlink_parse_cmp },
	{ .name = "lookup",	.parse = netlink_parse_lookup },
	{ .name = "bitwise",	.parse = netlink_parse_bitwise },
	{ .name = "byteorder",	.parse = netlink_parse_byteorder },
	{ .name = "payload",	.parse = netlink_parse_payload },
	{ .name = "exthdr",	.parse = netlink_parse_exthdr },
	{ .name = "meta",	.parse = netlink_parse_meta },
	{ .name = "socket",	.parse = netlink_parse_socket },
	{ .name = "osf",	.parse = netlink_parse_osf },
	{ .name = "rt",		.parse = netlink_parse_rt },
	{ .name = "ct",		.parse = netlink_parse_ct },
	{ .name = "connlimit",	.parse = netlink_parse_connlimit },
	{ .name = "counter",	.parse = netlink_parse_counter },
	{ .name = "log",	.parse = netlink_parse_log },
	{ .name = "limit",	.parse = netlink_parse_limit },
	{ .name = "range",	.parse = netlink_parse_range },
	{ .name = "reject",	.parse = netlink_parse_reject },
	{ .name = "nat",	.parse = netlink_parse_nat },
	{ .name = "tproxy",	.parse = netlink_parse_tproxy },
	{ .name = "notrack",	.parse = netlink_parse_notrack },
	{ .name = "masq",	.parse = netlink_parse_masq },
	{ .name = "redir",	.parse = netlink_parse_redir },
	{ .name = "dup",	.parse = netlink_parse_dup },
	{ .name = "queue",	.parse = netlink_parse_queue },
	{ .name = "dynset",	.parse = netlink_parse_dynset },
	{ .name = "fwd",	.parse = netlink_parse_fwd },
	{ .name = "target",	.parse = netlink_parse_target },
	{ .name = "match",	.parse = netlink_parse_match },
	{ .name = "objref",	.parse = netlink_parse_objref },
	{ .name = "quota",	.parse = netlink_parse_quota },
	{ .name = "numgen",	.parse = netlink_parse_numgen },
	{ .name = "hash",	.parse = netlink_parse_hash },
	{ .name = "fib",	.parse = netlink_parse_fib },
	{ .name = "tcpopt",	.parse = netlink_parse_exthdr },
	{ .name = "flow_offload", .parse = netlink_parse_flow_offload },
	{ .name = "xfrm",	.parse = netlink_parse_xfrm },
	{ .name = "synproxy",	.parse = netlink_parse_synproxy },
};

static const struct expr_handler **expr_handle_ht;

#define NFT_EXPR_HSIZE	4096

void expr_handler_init(void)
{
	unsigned int i;
	uint32_t hash;

	expr_handle_ht = calloc(NFT_EXPR_HSIZE, sizeof(expr_handle_ht));
	if (!expr_handle_ht)
		memory_allocation_error();

	for (i = 0; i < array_size(netlink_parsers); i++) {
		hash = djb_hash(netlink_parsers[i].name) % NFT_EXPR_HSIZE;
		assert(expr_handle_ht[hash] == NULL);
		expr_handle_ht[hash] = &netlink_parsers[i];
	}
}

void expr_handler_exit(void)
{
	xfree(expr_handle_ht);
}

static int netlink_parse_expr(const struct nftnl_expr *nle,
			      struct netlink_parse_ctx *ctx)
{
	const char *type = nftnl_expr_get_str(nle, NFTNL_EXPR_NAME);
	struct location loc;
	uint32_t hash;

	memset(&loc, 0, sizeof(loc));
	loc.indesc = &indesc_netlink;
	loc.nle = nle;

	hash = djb_hash(type) % NFT_EXPR_HSIZE;
	if (expr_handle_ht[hash])
		expr_handle_ht[hash]->parse(ctx, &loc, nle);
	else
		netlink_error(ctx, &loc, "unknown expression type '%s'", type);

	return 0;
}

static int netlink_parse_rule_expr(struct nftnl_expr *nle, void *arg)
{
	struct netlink_parse_ctx *ctx = arg;
	int err;

	err = netlink_parse_expr(nle, ctx);
	if (err < 0)
		return err;
	if (ctx->stmt != NULL) {
		rule_stmt_append(ctx->rule, ctx->stmt);
		ctx->stmt = NULL;
	}
	return 0;
}

struct stmt *netlink_parse_set_expr(const struct set *set,
				    const struct nft_cache *cache,
				    const struct nftnl_expr *nle)
{
	struct netlink_parse_ctx ctx, *pctx = &ctx;
	struct handle h = {};

	handle_merge(&h, &set->handle);
	pctx->rule = rule_alloc(&netlink_location, &h);
	pctx->table = table_lookup(&set->handle, cache);
	assert(pctx->table != NULL);

	if (netlink_parse_expr(nle, pctx) < 0)
		return NULL;

	init_list_head(&pctx->rule->stmts);
	rule_free(pctx->rule);

	return pctx->stmt;
}

static void expr_postprocess(struct rule_pp_ctx *ctx, struct expr **exprp);

static void payload_match_expand(struct rule_pp_ctx *ctx,
				 struct expr *expr,
				 struct expr *payload)
{
	struct expr *left = payload, *right = expr->right, *tmp;
	struct list_head list = LIST_HEAD_INIT(list);
	struct stmt *nstmt;
	struct expr *nexpr = NULL;
	enum proto_bases base = left->payload.base;
	bool stacked;

	if (ctx->pdctx.icmp_type)
		ctx->pctx.th_dep.icmp.type = ctx->pdctx.icmp_type;

	payload_expr_expand(&list, left, &ctx->pctx);

	list_for_each_entry(left, &list, list) {
		tmp = constant_expr_splice(right, left->len);
		expr_set_type(tmp, left->dtype, left->byteorder);

		if (left->payload.tmpl && (left->len < left->payload.tmpl->len)) {
			mpz_lshift_ui(tmp->value, left->payload.tmpl->len - left->len);
			tmp->len = left->payload.tmpl->len;
			tmp = prefix_expr_alloc(&tmp->location, tmp, left->len);
		}

		nexpr = relational_expr_alloc(&expr->location, expr->op,
					      left, tmp);
		if (expr->op == OP_EQ)
			relational_expr_pctx_update(&ctx->pctx, nexpr);

		nstmt = expr_stmt_alloc(&ctx->stmt->location, nexpr);
		list_add_tail(&nstmt->list, &ctx->stmt->list);

		assert(left->etype == EXPR_PAYLOAD);
		assert(left->payload.base);
		assert(base == left->payload.base);

		stacked = payload_is_stacked(ctx->pctx.protocol[base].desc, nexpr);

		/* Remember the first payload protocol expression to
		 * kill it later on if made redundant by a higher layer
		 * payload expression.
		 */
		if (ctx->pdctx.pbase == PROTO_BASE_INVALID &&
		    expr->op == OP_EQ &&
		    left->flags & EXPR_F_PROTOCOL) {
			payload_dependency_store(&ctx->pdctx, nstmt, base - stacked);
		} else {
			payload_dependency_kill(&ctx->pdctx, nexpr->left,
						ctx->pctx.family);
			if (expr->op == OP_EQ && left->flags & EXPR_F_PROTOCOL)
				payload_dependency_store(&ctx->pdctx, nstmt, base - stacked);
		}
	}
	list_del(&ctx->stmt->list);
	stmt_free(ctx->stmt);
	ctx->stmt = NULL;
}

static void payload_match_postprocess(struct rule_pp_ctx *ctx,
				      struct expr *expr,
				      struct expr *payload)
{
	enum proto_bases base = payload->payload.base;

	assert(payload->payload.offset >= ctx->pctx.protocol[base].offset);
	payload->payload.offset -= ctx->pctx.protocol[base].offset;

	switch (expr->op) {
	case OP_EQ:
	case OP_NEQ:
		if (expr->right->etype == EXPR_VALUE) {
			payload_match_expand(ctx, expr, payload);
			break;
		}
		/* Fall through */
	default:
		payload_expr_complete(payload, &ctx->pctx);
		expr_set_type(expr->right, payload->dtype,
			      payload->byteorder);
		payload_dependency_kill(&ctx->pdctx, payload, ctx->pctx.family);
		break;
	}
}

/* We have seen a protocol key expression that restricts matching at the network
 * base, leave it in place since this is meaninful in bridge, inet and netdev
 * families. Exceptions are ICMP and ICMPv6 where this code assumes that can
 * only happen with IPv4 and IPv6.
 */
static bool meta_may_dependency_kill(struct payload_dep_ctx *ctx,
				     unsigned int family,
				     const struct expr *expr)
{
	struct expr *dep = ctx->pdep->expr;
	uint16_t l3proto;
	uint8_t l4proto;

	if (ctx->pbase != PROTO_BASE_NETWORK_HDR)
		return true;

	switch (family) {
	case NFPROTO_INET:
	case NFPROTO_NETDEV:
	case NFPROTO_BRIDGE:
		break;
	default:
		return true;
	}

	if (expr->left->meta.key != NFT_META_L4PROTO)
		return true;

	l3proto = mpz_get_uint16(dep->right->value);

	switch (dep->left->etype) {
	case EXPR_META:
		if (dep->left->meta.key != NFT_META_NFPROTO)
			return true;
		break;
	case EXPR_PAYLOAD:
		if (dep->left->payload.base != PROTO_BASE_LL_HDR)
			return true;

		switch(l3proto) {
		case ETH_P_IP:
			l3proto = NFPROTO_IPV4;
			break;
		case ETH_P_IPV6:
			l3proto = NFPROTO_IPV6;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	l4proto = mpz_get_uint8(expr->right->value);

	switch (l4proto) {
	case IPPROTO_ICMP:
	case IPPROTO_ICMPV6:
		break;
	default:
		return false;
	}

	if ((l3proto == NFPROTO_IPV4 && l4proto == IPPROTO_ICMPV6) ||
	    (l3proto == NFPROTO_IPV6 && l4proto == IPPROTO_ICMP))
		return false;

	return true;
}

static void ct_meta_common_postprocess(struct rule_pp_ctx *ctx,
				       const struct expr *expr,
				       enum proto_bases base)
{
	const struct expr *left = expr->left;
	struct expr *right = expr->right;

	if (right->etype == EXPR_SET || right->etype == EXPR_SET_REF)
		expr_set_type(right, left->dtype, left->byteorder);

	switch (expr->op) {
	case OP_EQ:
		if (expr->right->etype == EXPR_RANGE ||
		    expr->right->etype == EXPR_SET ||
		    expr->right->etype == EXPR_SET_REF)
			break;

		relational_expr_pctx_update(&ctx->pctx, expr);

		if (ctx->pdctx.pbase == PROTO_BASE_INVALID &&
		    left->flags & EXPR_F_PROTOCOL) {
			payload_dependency_store(&ctx->pdctx, ctx->stmt, base);
		} else if (ctx->pdctx.pbase < PROTO_BASE_TRANSPORT_HDR) {
			if (payload_dependency_exists(&ctx->pdctx, base) &&
			    meta_may_dependency_kill(&ctx->pdctx,
						     ctx->pctx.family, expr))
				payload_dependency_release(&ctx->pdctx);
			if (left->flags & EXPR_F_PROTOCOL)
				payload_dependency_store(&ctx->pdctx, ctx->stmt, base);
		}
		break;
	default:
		break;
	}
}

static void meta_match_postprocess(struct rule_pp_ctx *ctx,
				   const struct expr *expr)
{
	const struct expr *left = expr->left;

	ct_meta_common_postprocess(ctx, expr, left->meta.base);
}

static void ct_match_postprocess(struct rule_pp_ctx *ctx,
				 const struct expr *expr)
{
	const struct expr *left = expr->left;

	ct_meta_common_postprocess(ctx, expr, left->ct.base);
}

/* Convert a bitmask to a prefix length */
static unsigned int expr_mask_to_prefix(const struct expr *expr)
{
	unsigned long n;

	n = mpz_scan1(expr->value, 0);
	if (n == ULONG_MAX)
		return 0;
	return mpz_scan0(expr->value, n + 1) - n;
}

/* Return true if a bitmask can be expressed as a prefix length */
static bool expr_mask_is_prefix(const struct expr *expr)
{
	unsigned long n1, n2;

	n1 = mpz_scan1(expr->value, 0);
	if (n1 == ULONG_MAX)
		return true;
	n2 = mpz_scan0(expr->value, n1 + 1);
	if (n2 < expr->len || n2 == ULONG_MAX)
		return false;
	return true;
}

/* Convert a series of inclusive OR expressions into a list */
static struct expr *binop_tree_to_list(struct expr *list, struct expr *expr)
{
	if (expr->etype == EXPR_BINOP && expr->op == OP_OR) {
		if (list == NULL)
			list = list_expr_alloc(&expr->location);
		list = binop_tree_to_list(list, expr->left);
		list = binop_tree_to_list(list, expr->right);
	} else {
		if (list == NULL)
			return expr_get(expr);
		compound_expr_add(list, expr_get(expr));
	}

	return list;
}

static void binop_adjust_one(const struct expr *binop, struct expr *value,
			     unsigned int shift)
{
	struct expr *left = binop->left;

	assert(value->len >= binop->right->len);

	mpz_rshift_ui(value->value, shift);
	switch (left->etype) {
	case EXPR_PAYLOAD:
	case EXPR_EXTHDR:
		value->len = left->len;
		break;
	default:
		BUG("unknown expression type %s\n", expr_name(left));
		break;
	}
}

static void __binop_adjust(const struct expr *binop, struct expr *right,
			   unsigned int shift)
{
	struct expr *i;

	switch (right->etype) {
	case EXPR_VALUE:
		binop_adjust_one(binop, right, shift);
		break;
	case EXPR_SET_REF:
		list_for_each_entry(i, &right->set->init->expressions, list) {
			switch (i->key->etype) {
			case EXPR_VALUE:
				binop_adjust_one(binop, i->key, shift);
				break;
			case EXPR_RANGE:
				binop_adjust_one(binop, i->key->left, shift);
				binop_adjust_one(binop, i->key->right, shift);
				break;
			case EXPR_SET_ELEM:
				__binop_adjust(binop, i->key->key, shift);
				break;
			default:
				BUG("unknown expression type %s\n", expr_name(i->key));
			}
		}
		break;
	case EXPR_RANGE:
		binop_adjust_one(binop, right->left, shift);
		binop_adjust_one(binop, right->right, shift);
		break;
	default:
		BUG("unknown expression type %s\n", expr_name(right));
		break;
	}
}

static void binop_adjust(struct expr *expr, unsigned int shift)
{
	__binop_adjust(expr->left, expr->right, shift);
}

static void binop_postprocess(struct rule_pp_ctx *ctx, struct expr *expr)
{
	struct expr *binop = expr->left;
	struct expr *left = binop->left;
	struct expr *mask = binop->right;
	unsigned int shift;

	if ((left->etype == EXPR_PAYLOAD &&
	    payload_expr_trim(left, mask, &ctx->pctx, &shift)) ||
	    (left->etype == EXPR_EXTHDR &&
	     exthdr_find_template(left, mask, &shift))) {
		/* mask is implicit, binop needs to be removed.
		 *
		 * Fix all values of the expression according to the mask
		 * and then process the payload instruction using the real
		 * sizes and offsets we're interested in.
		 *
		 * Finally, convert the expression to 1) by replacing
		 * the binop with the binop payload/exthdr expression.
		 */
		binop_adjust(expr, shift);

		assert(expr->left->etype == EXPR_BINOP);
		assert(binop->left == left);
		expr->left = expr_get(left);
		expr_free(binop);
		if (left->etype == EXPR_PAYLOAD)
			payload_match_postprocess(ctx, expr, left);
		else if (left->etype == EXPR_EXTHDR)
			expr_set_type(expr->right, left->dtype, left->byteorder);
	}
}

static void map_binop_postprocess(struct rule_pp_ctx *ctx, struct expr *expr)
{
	struct expr *binop = expr->left;

	if (binop->op != OP_AND)
		return;

	if (binop->left->etype == EXPR_PAYLOAD &&
	    binop->right->etype == EXPR_VALUE)
		binop_postprocess(ctx, expr);
}

static void relational_binop_postprocess(struct rule_pp_ctx *ctx, struct expr *expr)
{
	struct expr *binop = expr->left, *value = expr->right;

	if (binop->op == OP_AND && expr->op == OP_NEQ &&
	    value->dtype->basetype &&
	    value->dtype->basetype->type == TYPE_BITMASK &&
	    !mpz_cmp_ui(value->value, 0)) {
		/* Flag comparison: data & flags != 0
		 *
		 * Split the flags into a list of flag values and convert the
		 * op to OP_EQ.
		 */
		expr_free(value);

		expr->left  = expr_get(binop->left);
		expr->right = binop_tree_to_list(NULL, binop->right);
		expr->op    = OP_IMPLICIT;

		expr_free(binop);
	} else if (binop->left->dtype->flags & DTYPE_F_PREFIX &&
		   binop->op == OP_AND && expr->right->etype == EXPR_VALUE &&
		   expr_mask_is_prefix(binop->right)) {
		expr->left = expr_get(binop->left);
		expr->right = prefix_expr_alloc(&expr->location,
						expr_get(value),
						expr_mask_to_prefix(binop->right));
		expr_free(value);
		expr_free(binop);
	} else if (binop->op == OP_AND &&
		   binop->right->etype == EXPR_VALUE) {
		/*
		 * This *might* be a payload match testing header fields that
		 * have non byte divisible offsets and/or bit lengths.
		 *
		 * Thus we need to deal with two different cases.
		 *
		 * 1 the simple version:
		 *        relation
		 * payload        value|setlookup
		 *
		 * expr: relation, left: payload, right: value, e.g.  tcp dport == 22.
		 *
		 * 2. The '&' version (this is what we're looking at now).
		 *            relation
		 *     binop          value1|setlookup
		 * payload  value2
		 *
		 * expr: relation, left: binop, right: value, e.g.
		 * ip saddr 10.0.0.0/8
		 *
		 * payload_expr_trim will figure out if the mask is needed to match
		 * templates.
		 */
		binop_postprocess(ctx, expr);
	}
}

static struct expr *string_wildcard_expr_alloc(struct location *loc,
					       const struct expr *mask,
					       const struct expr *expr)
{
	unsigned int len = div_round_up(expr->len, BITS_PER_BYTE);
	char data[len + 2];
	int pos;

	mpz_export_data(data, expr->value, BYTEORDER_HOST_ENDIAN, len);
	pos = div_round_up(expr_mask_to_prefix(mask), BITS_PER_BYTE);
	data[pos] = '*';
	data[pos + 1] = '\0';

	return constant_expr_alloc(loc, expr->dtype, BYTEORDER_HOST_ENDIAN,
				   expr->len + BITS_PER_BYTE, data);
}

static void escaped_string_wildcard_expr_alloc(struct expr **exprp,
					       unsigned int len)
{
	struct expr *expr = *exprp, *tmp;
	char data[len + 3];
	int pos;

	mpz_export_data(data, expr->value, BYTEORDER_HOST_ENDIAN, len);
	pos = div_round_up(len, BITS_PER_BYTE);
	data[pos - 1] = '\\';
	data[pos] = '*';

	tmp = constant_expr_alloc(&expr->location, expr->dtype,
				  BYTEORDER_HOST_ENDIAN,
				  expr->len + BITS_PER_BYTE, data);
	expr_free(expr);
	*exprp = tmp;
}

/* This calculates the string length and checks if it is nul-terminated, this
 * function is quite a hack :)
 */
static bool __expr_postprocess_string(struct expr **exprp)
{
	struct expr *expr = *exprp;
	unsigned int len = expr->len;
	bool nulterminated = false;
	mpz_t tmp;

	mpz_init(tmp);
	while (len >= BITS_PER_BYTE) {
		mpz_bitmask(tmp, BITS_PER_BYTE);
		mpz_lshift_ui(tmp, len - BITS_PER_BYTE);
		mpz_and(tmp, tmp, expr->value);
		if (mpz_cmp_ui(tmp, 0))
			break;
		else
			nulterminated = true;
		len -= BITS_PER_BYTE;
	}

	mpz_rshift_ui(tmp, len - BITS_PER_BYTE);

	if (nulterminated &&
	    mpz_cmp_ui(tmp, '*') == 0)
		escaped_string_wildcard_expr_alloc(exprp, len);

	mpz_clear(tmp);

	return nulterminated;
}

static struct expr *expr_postprocess_string(struct expr *expr)
{
	struct expr *mask, *out;

	assert(expr_basetype(expr)->type == TYPE_STRING);
	if (__expr_postprocess_string(&expr))
		return expr;

	mask = constant_expr_alloc(&expr->location, &integer_type,
				   BYTEORDER_HOST_ENDIAN,
				   expr->len + BITS_PER_BYTE, NULL);
	mpz_init_bitmask(mask->value, expr->len);
	out = string_wildcard_expr_alloc(&expr->location, mask, expr);
	expr_free(mask);
	return out;
}

static void expr_postprocess(struct rule_pp_ctx *ctx, struct expr **exprp)
{
	struct expr *expr = *exprp, *i;

	switch (expr->etype) {
	case EXPR_MAP:
		switch (expr->map->etype) {
		case EXPR_BINOP:
			map_binop_postprocess(ctx, expr);
			break;
		default:
			break;
		}

		expr_postprocess(ctx, &expr->map);
		expr_postprocess(ctx, &expr->mappings);
		break;
	case EXPR_MAPPING:
		expr_postprocess(ctx, &expr->left);
		expr_postprocess(ctx, &expr->right);
		break;
	case EXPR_SET:
		list_for_each_entry(i, &expr->expressions, list)
			expr_postprocess(ctx, &i);
		break;
	case EXPR_CONCAT: {
		unsigned int type = expr->dtype->type, ntype = 0;
		int off = expr->dtype->subtypes;
		const struct datatype *dtype;

		list_for_each_entry(i, &expr->expressions, list) {
			if (type) {
				dtype = concat_subtype_lookup(type, --off);
				expr_set_type(i, dtype, dtype->byteorder);
			}
			expr_postprocess(ctx, &i);

			ntype = concat_subtype_add(ntype, i->dtype->type);
		}
		datatype_set(expr, concat_type_alloc(ntype));
		break;
	}
	case EXPR_UNARY:
		expr_postprocess(ctx, &expr->arg);
		expr_set_type(expr, expr->arg->dtype, !expr->arg->byteorder);
		break;
	case EXPR_BINOP:
		expr_postprocess(ctx, &expr->left);
		switch (expr->op) {
		case OP_LSHIFT:
		case OP_RSHIFT:
			expr_set_type(expr->right, &integer_type,
				      BYTEORDER_HOST_ENDIAN);
			break;
		default:
			expr_set_type(expr->right, expr->left->dtype,
				      expr->left->byteorder);
		}
		expr_postprocess(ctx, &expr->right);

		expr_set_type(expr, expr->left->dtype,
			      expr->left->byteorder);
		break;
	case EXPR_RELATIONAL:
		switch (expr->left->etype) {
		case EXPR_PAYLOAD:
			payload_match_postprocess(ctx, expr, expr->left);
			return;
		default:
			expr_postprocess(ctx, &expr->left);
			break;
		}

		expr_set_type(expr->right, expr->left->dtype, expr->left->byteorder);
		expr_postprocess(ctx, &expr->right);

		switch (expr->left->etype) {
		case EXPR_CT:
			ct_match_postprocess(ctx, expr);
			break;
		case EXPR_META:
			meta_match_postprocess(ctx, expr);
			break;
		case EXPR_BINOP:
			relational_binop_postprocess(ctx, expr);
			break;
		default:
			break;
		}
		break;
	case EXPR_PAYLOAD:
		payload_expr_complete(expr, &ctx->pctx);
		payload_dependency_kill(&ctx->pdctx, expr, ctx->pctx.family);
		break;
	case EXPR_VALUE:
		// FIXME
		if (expr->byteorder == BYTEORDER_HOST_ENDIAN)
			mpz_switch_byteorder(expr->value, expr->len / BITS_PER_BYTE);

		if (expr_basetype(expr)->type == TYPE_STRING)
			*exprp = expr_postprocess_string(expr);

		expr = *exprp;
		if (expr->dtype->basetype != NULL &&
		    expr->dtype->basetype->type == TYPE_BITMASK)
			*exprp = bitmask_expr_to_binops(expr);

		break;
	case EXPR_RANGE:
		expr_postprocess(ctx, &expr->left);
		expr_postprocess(ctx, &expr->right);
	case EXPR_PREFIX:
		expr_postprocess(ctx, &expr->prefix);
		break;
	case EXPR_SET_ELEM:
		expr_postprocess(ctx, &expr->key);
		break;
	case EXPR_EXTHDR:
		exthdr_dependency_kill(&ctx->pdctx, expr, ctx->pctx.family);
		break;
	case EXPR_SET_REF:
	case EXPR_META:
	case EXPR_RT:
	case EXPR_VERDICT:
	case EXPR_NUMGEN:
	case EXPR_FIB:
	case EXPR_SOCKET:
	case EXPR_OSF:
	case EXPR_XFRM:
		break;
	case EXPR_HASH:
		if (expr->hash.expr)
			expr_postprocess(ctx, &expr->hash.expr);
		break;
	case EXPR_CT:
		ct_expr_update_type(&ctx->pctx, expr);
		break;
	default:
		BUG("unknown expression type %s\n", expr_name(expr));
	}
}

static void stmt_reject_postprocess(struct rule_pp_ctx *rctx)
{
	const struct proto_desc *desc, *base;
	struct stmt *stmt = rctx->stmt;
	int protocol;

	switch (rctx->pctx.family) {
	case NFPROTO_IPV4:
		stmt->reject.family = rctx->pctx.family;
		datatype_set(stmt->reject.expr, &icmp_code_type);
		if (stmt->reject.type == NFT_REJECT_TCP_RST &&
		    payload_dependency_exists(&rctx->pdctx,
					      PROTO_BASE_TRANSPORT_HDR))
			payload_dependency_release(&rctx->pdctx);
		break;
	case NFPROTO_IPV6:
		stmt->reject.family = rctx->pctx.family;
		datatype_set(stmt->reject.expr, &icmpv6_code_type);
		if (stmt->reject.type == NFT_REJECT_TCP_RST &&
		    payload_dependency_exists(&rctx->pdctx,
					      PROTO_BASE_TRANSPORT_HDR))
			payload_dependency_release(&rctx->pdctx);
		break;
	case NFPROTO_INET:
		if (stmt->reject.type == NFT_REJECT_ICMPX_UNREACH) {
			datatype_set(stmt->reject.expr, &icmpx_code_type);
			break;
		}
		base = rctx->pctx.protocol[PROTO_BASE_LL_HDR].desc;
		desc = rctx->pctx.protocol[PROTO_BASE_NETWORK_HDR].desc;
		protocol = proto_find_num(base, desc);
		switch (protocol) {
		case NFPROTO_IPV4:
			datatype_set(stmt->reject.expr, &icmp_code_type);
			break;
		case NFPROTO_IPV6:
			datatype_set(stmt->reject.expr, &icmpv6_code_type);
			break;
		}
		stmt->reject.family = protocol;
		break;
	case NFPROTO_BRIDGE:
		if (stmt->reject.type == NFT_REJECT_ICMPX_UNREACH) {
			datatype_set(stmt->reject.expr, &icmpx_code_type);
			break;
		}

		/* always print full icmp(6) name, simple 'reject' might be ambiguious
		 * because ipv4 vs. ipv6 info might be lost
		 */
		stmt->reject.verbose_print = 1;

		base = rctx->pctx.protocol[PROTO_BASE_LL_HDR].desc;
		desc = rctx->pctx.protocol[PROTO_BASE_NETWORK_HDR].desc;
		protocol = proto_find_num(base, desc);
		switch (protocol) {
		case __constant_htons(ETH_P_IP):
			stmt->reject.family = NFPROTO_IPV4;
			datatype_set(stmt->reject.expr, &icmp_code_type);
			break;
		case __constant_htons(ETH_P_IPV6):
			stmt->reject.family = NFPROTO_IPV6;
			datatype_set(stmt->reject.expr, &icmpv6_code_type);
			break;
		default:
			break;
		}

		if (payload_dependency_exists(&rctx->pdctx, PROTO_BASE_NETWORK_HDR))
			payload_dependency_release(&rctx->pdctx);

		break;
	default:
		break;
	}
}

static bool expr_may_merge_range(struct expr *expr, struct expr *prev,
				 enum ops *op)
{
	struct expr *left, *prev_left;

	if (prev->etype == EXPR_RELATIONAL &&
	    expr->etype == EXPR_RELATIONAL) {
		/* ct and meta needs an unary to swap byteorder, in this case
		 * we have to explore the inner branch in this tree.
		 */
		if (expr->left->etype == EXPR_UNARY)
			left = expr->left->arg;
		else
			left = expr->left;

		if (prev->left->etype == EXPR_UNARY)
			prev_left = prev->left->arg;
		else
			prev_left = prev->left;

		if (left->etype == prev_left->etype) {
			if (expr->op == OP_LTE && prev->op == OP_GTE) {
				*op = OP_EQ;
				return true;
			} else if (expr->op == OP_GT && prev->op == OP_LT) {
				*op = OP_NEQ;
				return true;
			}
		}
	}

	return false;
}

static void expr_postprocess_range(struct rule_pp_ctx *ctx, enum ops op)
{
	struct stmt *nstmt, *stmt = ctx->stmt;
	struct expr *nexpr, *rel;

	nexpr = range_expr_alloc(&ctx->pdctx.prev->location,
				 expr_clone(ctx->pdctx.prev->expr->right),
				 expr_clone(stmt->expr->right));
	expr_set_type(nexpr, stmt->expr->right->dtype,
		      stmt->expr->right->byteorder);

	rel = relational_expr_alloc(&ctx->pdctx.prev->location, op,
				    expr_clone(stmt->expr->left), nexpr);

	nstmt = expr_stmt_alloc(&stmt->location, rel);
	list_add_tail(&nstmt->list, &stmt->list);

	list_del(&ctx->pdctx.prev->list);
	stmt_free(ctx->pdctx.prev);

	list_del(&stmt->list);
	stmt_free(stmt);
	ctx->stmt = nstmt;
}

static void stmt_expr_postprocess(struct rule_pp_ctx *ctx)
{
	enum ops op;

	expr_postprocess(ctx, &ctx->stmt->expr);

	if (ctx->pdctx.prev && ctx->stmt &&
	    ctx->stmt->ops->type == ctx->pdctx.prev->ops->type &&
	    expr_may_merge_range(ctx->stmt->expr, ctx->pdctx.prev->expr, &op))
		expr_postprocess_range(ctx, op);
}

static void stmt_payload_binop_pp(struct rule_pp_ctx *ctx, struct expr *binop)
{
	struct expr *payload = binop->left;
	struct expr *mask = binop->right;
	unsigned int shift;

	assert(payload->etype == EXPR_PAYLOAD);
	if (payload_expr_trim(payload, mask, &ctx->pctx, &shift)) {
		__binop_adjust(binop, mask, shift);
		payload_expr_complete(payload, &ctx->pctx);
		expr_set_type(mask, payload->dtype,
			      payload->byteorder);
	}
}

/**
 * stmt_payload_binop_postprocess - decode payload set binop
 *
 * @ctx:	rule postprocessing context
 *
 * This helper has to be called if expr_postprocess() failed to
 * decode the payload operation.
 *
 * Usually a failure to decode means that userspace had to munge
 * the original payload expression because it has an odd size or
 * a non-byte divisible offset/length.
 *
 * If that was the case, the 'value' expression is not a value but
 * a binop expression with a munged payload expression on the left
 * and a mask to clear the real payload offset/length.
 *
 * So chech if we have one of the following binops:
 * I)
 *           binop (|)
 *       binop(&)   value/set
 * payload   value(mask)
 *
 * This is the normal case, the | RHS is the value the user wants
 * to set, the & RHS is the mask value that discards bits we need
 * to clear but retains everything unrelated to the set operation.
 *
 * IIa)
 *     binop (&)
 * payload   mask
 *
 * User specified a zero set value -- netlink bitwise decoding
 * discarded the redundant "| 0" part.  This is identical to I),
 * we can just set value to 0 after we inferred the real payload size.
 *
 * IIb)
 *     binop (|)
 * payload     value/set
 *
 * This happens when user wants to set all bits, netlink bitwise
 * decoding changed '(payload & mask) ^ bits_to_set' into
 * 'payload | bits_to_set', discarding the redundant "& 0xfff...".
 */
static void stmt_payload_binop_postprocess(struct rule_pp_ctx *ctx)
{
	struct expr *expr, *binop, *payload, *value, *mask;
	struct stmt *stmt = ctx->stmt;
	mpz_t bitmask;

	expr = stmt->payload.val;

	if (expr->etype != EXPR_BINOP)
		return;

	switch (expr->left->etype) {
	case EXPR_BINOP: {/* I? */
		mpz_t tmp;

		if (expr->op != OP_OR)
			return;

		value = expr->right;
		if (value->etype != EXPR_VALUE)
			return;

		binop = expr->left;
		if (binop->op != OP_AND)
			return;

		payload = binop->left;
		if (payload->etype != EXPR_PAYLOAD)
			return;

		if (!payload_expr_cmp(stmt->payload.expr, payload))
			return;

		mask = binop->right;
		if (mask->etype != EXPR_VALUE)
			return;

		mpz_init(tmp);
		mpz_set(tmp, mask->value);

		mpz_init_bitmask(bitmask, payload->len);
		mpz_xor(bitmask, bitmask, mask->value);
		mpz_xor(bitmask, bitmask, value->value);
		mpz_set(mask->value, bitmask);
		mpz_clear(bitmask);

		binop_postprocess(ctx, expr);
		if (!payload_is_known(payload)) {
			mpz_set(mask->value, tmp);
			mpz_clear(tmp);
			return;
		}

		mpz_clear(tmp);
		expr_free(stmt->payload.expr);
		stmt->payload.expr = expr_get(payload);
		stmt->payload.val = expr_get(expr->right);
		expr_free(expr);
		break;
	}
	case EXPR_PAYLOAD: /* II? */
		value = expr->right;
		if (value->etype != EXPR_VALUE)
			return;

		switch (expr->op) {
		case OP_AND: /* IIa */
			payload = expr->left;
			mpz_init_bitmask(bitmask, payload->len);
			mpz_xor(bitmask, bitmask, value->value);
			mpz_set(value->value, bitmask);
			mpz_clear(bitmask);
			break;
		case OP_OR: /* IIb */
			break;
		default: /* No idea */
			return;
		}

		stmt_payload_binop_pp(ctx, expr);
		if (!payload_is_known(expr->left))
			return;

		expr_free(stmt->payload.expr);

		switch (expr->op) {
		case OP_AND:
			/* Mask was used to match payload, i.e.
			 * user asked to set zero value.
			 */
			mpz_set_ui(value->value, 0);
			break;
		default:
			break;
		}

		stmt->payload.expr = expr_get(expr->left);
		stmt->payload.val = expr_get(expr->right);
		expr_free(expr);
		break;
	default: /* No idea */
		break;
	}
}

static void stmt_payload_postprocess(struct rule_pp_ctx *ctx)
{
	struct stmt *stmt = ctx->stmt;

	expr_postprocess(ctx, &stmt->payload.expr);

	expr_set_type(stmt->payload.val,
		      stmt->payload.expr->dtype,
		      stmt->payload.expr->byteorder);

	if (!payload_is_known(stmt->payload.expr))
		stmt_payload_binop_postprocess(ctx);

	expr_postprocess(ctx, &stmt->payload.val);
}

/*
 * We can only remove payload dependencies if they occur without
 * a statement with side effects in between.
 *
 * For instance:
 * 'ip protocol tcp tcp dport 22 counter' is same as
 * 'tcp dport 22 counter'.
 *
 * 'ip protocol tcp counter tcp dport 22' cannot be written as
 * 'counter tcp dport 22' (that would be counter ip protocol tcp, but
 * that counts every packet, not just ip/tcp).
 */
static void
rule_maybe_reset_payload_deps(struct payload_dep_ctx *pdctx, enum stmt_types t)
{
	if (t == STMT_EXPRESSION)
		return;

	payload_dependency_reset(pdctx);
}

static void rule_parse_postprocess(struct netlink_parse_ctx *ctx, struct rule *rule)
{
	struct rule_pp_ctx rctx;
	struct stmt *stmt, *next;

	memset(&rctx, 0, sizeof(rctx));
	proto_ctx_init(&rctx.pctx, rule->handle.family, ctx->debug_mask);

	list_for_each_entry_safe(stmt, next, &rule->stmts, list) {
		enum stmt_types type = stmt->ops->type;

		rctx.stmt = stmt;

		switch (type) {
		case STMT_EXPRESSION:
			stmt_expr_postprocess(&rctx);
			break;
		case STMT_PAYLOAD:
			stmt_payload_postprocess(&rctx);
			break;
		case STMT_METER:
			expr_postprocess(&rctx, &stmt->meter.key);
			break;
		case STMT_META:
			if (stmt->meta.expr != NULL)
				expr_postprocess(&rctx, &stmt->meta.expr);
			break;
		case STMT_CT:
			if (stmt->ct.expr != NULL) {
				expr_postprocess(&rctx, &stmt->ct.expr);

				if (stmt->ct.expr->etype == EXPR_BINOP &&
				    stmt->ct.key == NFT_CT_EVENTMASK)
					stmt->ct.expr = binop_tree_to_list(NULL,
									   stmt->ct.expr);
			}
			break;
		case STMT_NAT:
			if (stmt->nat.addr != NULL)
				expr_postprocess(&rctx, &stmt->nat.addr);
			if (stmt->nat.proto != NULL) {
				payload_dependency_reset(&rctx.pdctx);
				expr_postprocess(&rctx, &stmt->nat.proto);
			}
			break;
		case STMT_TPROXY:
			if (stmt->tproxy.addr)
				expr_postprocess(&rctx, &stmt->tproxy.addr);
			if (stmt->tproxy.port) {
				payload_dependency_reset(&rctx.pdctx);
				expr_postprocess(&rctx, &stmt->tproxy.port);
			}
			break;
		case STMT_REJECT:
			stmt_reject_postprocess(&rctx);
			break;
		case STMT_SET:
			expr_postprocess(&rctx, &stmt->set.key);
			break;
		case STMT_MAP:
			expr_postprocess(&rctx, &stmt->map.key);
			expr_postprocess(&rctx, &stmt->map.data);
			break;
		case STMT_DUP:
			if (stmt->dup.to != NULL)
				expr_postprocess(&rctx, &stmt->dup.to);
			if (stmt->dup.dev != NULL)
				expr_postprocess(&rctx, &stmt->dup.dev);
			break;
		case STMT_FWD:
			expr_postprocess(&rctx, &stmt->fwd.dev);
			if (stmt->fwd.addr != NULL)
				expr_postprocess(&rctx, &stmt->fwd.addr);
			break;
		case STMT_XT:
			stmt_xt_postprocess(&rctx, stmt, rule);
			break;
		case STMT_OBJREF:
			expr_postprocess(&rctx, &stmt->objref.expr);
			break;
		default:
			break;
		}

		rctx.pdctx.prev = rctx.stmt;

		rule_maybe_reset_payload_deps(&rctx.pdctx, type);
	}
}

static int parse_rule_udata_cb(const struct nftnl_udata *attr, void *data)
{
	unsigned char *value = nftnl_udata_get(attr);
	uint8_t type = nftnl_udata_type(attr);
	uint8_t len = nftnl_udata_len(attr);
	const struct nftnl_udata **tb = data;

	switch (type) {
	case NFTNL_UDATA_RULE_COMMENT:
		if (value[len - 1] != '\0')
			return -1;
		break;
	default:
		return 0;
	}
	tb[type] = attr;
	return 0;
}

static char *nftnl_rule_get_comment(const struct nftnl_rule *nlr)
{
	const struct nftnl_udata *tb[NFTNL_UDATA_RULE_MAX + 1] = {};
	const void *data;
	uint32_t len;

	if (!nftnl_rule_is_set(nlr, NFTNL_RULE_USERDATA))
		return NULL;

	data = nftnl_rule_get_data(nlr, NFTNL_RULE_USERDATA, &len);

	if (nftnl_udata_parse(data, len, parse_rule_udata_cb, tb) < 0)
		return NULL;

	if (!tb[NFTNL_UDATA_RULE_COMMENT])
		return NULL;

	return xstrdup(nftnl_udata_get(tb[NFTNL_UDATA_RULE_COMMENT]));
}

struct rule *netlink_delinearize_rule(struct netlink_ctx *ctx,
				      struct nftnl_rule *nlr)
{
	struct netlink_parse_ctx _ctx, *pctx = &_ctx;
	struct handle h;

	memset(&_ctx, 0, sizeof(_ctx));
	_ctx.msgs = ctx->msgs;
	_ctx.debug_mask = ctx->nft->debug_mask;

	memset(&h, 0, sizeof(h));
	h.family = nftnl_rule_get_u32(nlr, NFTNL_RULE_FAMILY);
	h.table.name = xstrdup(nftnl_rule_get_str(nlr, NFTNL_RULE_TABLE));
	h.chain.name = xstrdup(nftnl_rule_get_str(nlr, NFTNL_RULE_CHAIN));
	h.handle.id = nftnl_rule_get_u64(nlr, NFTNL_RULE_HANDLE);

	if (nftnl_rule_is_set(nlr, NFTNL_RULE_POSITION))
		h.position.id = nftnl_rule_get_u64(nlr, NFTNL_RULE_POSITION);

	pctx->rule = rule_alloc(&netlink_location, &h);
	pctx->table = table_lookup(&h, &ctx->nft->cache);
	assert(pctx->table != NULL);

	pctx->rule->comment = nftnl_rule_get_comment(nlr);

	nftnl_expr_foreach(nlr, netlink_parse_rule_expr, pctx);

	rule_parse_postprocess(pctx, pctx->rule);
	netlink_release_registers(pctx);
	return pctx->rule;
}
