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

struct netlink_parse_ctx {
	struct list_head	*msgs;
	struct table		*table;
	struct rule		*rule;
	struct stmt		*stmt;
	struct expr		*registers[1 + NFT_REG32_15 - NFT_REG32_00 + 1];
};

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
	if (reg == NFT_REG_VERDICT || reg > 1 + NFT_REG32_15 - NFT_REG32_00) {
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

	if (reg == NFT_REG_VERDICT || reg > 1 + NFT_REG32_15 - NFT_REG32_00) {
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

	for (i = 0; i <= NFT_REG_MAX; i++)
		expr_free(ctx->registers[i]);
}

static struct expr *netlink_parse_concat_expr(struct netlink_parse_ctx *ctx,
					      const struct location *loc,
					      unsigned int reg,
					      unsigned int len)
{
	struct expr *concat, *expr;

	concat = concat_expr_alloc(loc);
	while (len > 0) {
		expr = netlink_get_register(ctx, loc, reg);
		if (expr == NULL) {
			netlink_error(ctx, loc,
				      "Relational expression size mismatch");
			goto err;
		}
		compound_expr_add(concat, expr);

		len -= netlink_padded_len(expr->len);
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
	if (dreg == NFT_REG_VERDICT)
		ctx->stmt = verdict_stmt_alloc(loc, expr);
	else
		netlink_set_register(ctx, dreg, expr);
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
	struct expr *expr, *left, *right;
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
	    left->dtype != &string_type) {
		return netlink_error(ctx, loc,
				     "Relational expression size mismatch");
	} else if (left->len > 0 && left->len < right->len) {
		left = netlink_parse_concat_expr(ctx, loc, sreg, right->len);
		if (left == NULL)
			return;
		right = netlink_parse_concat_data(ctx, loc, sreg, right->len, right);
		if (right == NULL)
			return;
	}

	expr = relational_expr_alloc(loc, op, left, right);
	ctx->stmt = expr_stmt_alloc(loc, expr);
}

static void netlink_parse_lookup(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *nle)
{
	enum nft_registers sreg, dreg;
	const char *name;
	struct expr *expr, *left, *right;
	struct set *set;

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

	if (left->len < set->keylen) {
		left = netlink_parse_concat_expr(ctx, loc, sreg, set->keylen);
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
		expr = relational_expr_alloc(loc, OP_LOOKUP, left, right);
	}

	ctx->stmt = expr_stmt_alloc(loc, expr);
}

static void netlink_parse_bitwise(struct netlink_parse_ctx *ctx,
				  const struct location *loc,
				  const struct nftnl_expr *nle)
{
	struct nft_data_delinearize nld;
	enum nft_registers sreg, dreg;
	struct expr *expr, *left, *mask, *xor, *or;
	mpz_t m, x, o;

	sreg = netlink_parse_register(nle, NFTNL_EXPR_BITWISE_SREG);
	left = netlink_get_register(ctx, loc, sreg);
	if (left == NULL)
		return netlink_error(ctx, loc,
				     "Bitwise expression has no left "
				     "hand side");

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

	expr = payload_expr_alloc(loc, NULL, 0);
	payload_init_raw(expr, base, offset, len);

	sreg = netlink_parse_register(nle, NFT_EXPR_PAYLOAD_SREG);
	val  = netlink_get_register(ctx, loc, sreg);
	stmt = payload_stmt_alloc(loc, expr, val);

	list_add_tail(&stmt->list, &ctx->rule->stmts);
}

static void netlink_parse_payload(struct netlink_parse_ctx *ctx,
				  const struct location *loc,
				  const struct nftnl_expr *nle)
{
	if (nftnl_expr_is_set(nle, NFT_EXPR_PAYLOAD_DREG))
		netlink_parse_payload_expr(ctx, loc, nle);
	else
		netlink_parse_payload_stmt(ctx, loc, nle);
}

static void netlink_parse_exthdr(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *nle)
{
	enum nft_registers dreg;
	uint32_t offset, len;
	uint8_t type;
	struct expr *expr;

	type   = nftnl_expr_get_u8(nle, NFTNL_EXPR_EXTHDR_TYPE);
	offset = nftnl_expr_get_u32(nle, NFTNL_EXPR_EXTHDR_OFFSET) * BITS_PER_BYTE;
	len    = nftnl_expr_get_u32(nle, NFTNL_EXPR_EXTHDR_LEN) * BITS_PER_BYTE;

	expr = exthdr_expr_alloc(loc, NULL, 0);
	exthdr_init_raw(expr, type, offset, len);

	dreg = netlink_parse_register(nle, NFTNL_EXPR_EXTHDR_DREG);
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

static void netlink_parse_ct_stmt(struct netlink_parse_ctx *ctx,
				  const struct location *loc,
				  const struct nftnl_expr *nle)
{
	enum nft_registers sreg;
	uint32_t key;
	struct stmt *stmt;
	struct expr *expr;

	sreg = netlink_parse_register(nle, NFTNL_EXPR_CT_SREG);
	expr = netlink_get_register(ctx, loc, sreg);

	key  = nftnl_expr_get_u32(nle, NFTNL_EXPR_CT_KEY);
	stmt = ct_stmt_alloc(loc, key, expr);
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
		stmt->log.prefix = xstrdup(prefix);
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

static void netlink_parse_nat(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	struct stmt *stmt;
	struct expr *addr, *proto;
	enum nft_registers reg1, reg2;
	int family;

	stmt = nat_stmt_alloc(loc);
	stmt->nat.type = nftnl_expr_get_u32(nle, NFTNL_EXPR_NAT_TYPE);

	family = nftnl_expr_get_u32(nle, NFTNL_EXPR_NAT_FAMILY);

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_NAT_FLAGS))
		stmt->nat.flags = nftnl_expr_get_u32(nle, NFTNL_EXPR_NAT_FLAGS);

	reg1 = netlink_parse_register(nle, NFTNL_EXPR_NAT_REG_ADDR_MIN);
	if (reg1) {
		addr = netlink_get_register(ctx, loc, reg1);
		if (addr == NULL)
			return netlink_error(ctx, loc,
					     "NAT statement has no address "
					     "expression");

		if (family == AF_INET)
			expr_set_type(addr, &ipaddr_type, BYTEORDER_BIG_ENDIAN);
		else
			expr_set_type(addr, &ip6addr_type,
				      BYTEORDER_BIG_ENDIAN);
		stmt->nat.addr = addr;
	}

	reg2 = netlink_parse_register(nle, NFTNL_EXPR_NAT_REG_ADDR_MAX);
	if (reg2 && reg2 != reg1) {
		addr = netlink_get_register(ctx, loc, reg2);
		if (addr == NULL)
			return netlink_error(ctx, loc,
					     "NAT statement has no address "
					     "expression");

		if (family == AF_INET)
			expr_set_type(addr, &ipaddr_type, BYTEORDER_BIG_ENDIAN);
		else
			expr_set_type(addr, &ip6addr_type,
				      BYTEORDER_BIG_ENDIAN);
		if (stmt->nat.addr != NULL)
			addr = range_expr_alloc(loc, stmt->nat.addr, addr);
		stmt->nat.addr = addr;
	}

	reg1 = netlink_parse_register(nle, NFTNL_EXPR_NAT_REG_PROTO_MIN);
	if (reg1) {
		proto = netlink_get_register(ctx, loc, reg1);
		if (proto == NULL)
			return netlink_error(ctx, loc,
					     "NAT statement has no proto "
					     "expression");

		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		stmt->nat.proto = proto;
	}

	reg2 = netlink_parse_register(nle, NFTNL_EXPR_NAT_REG_PROTO_MAX);
	if (reg2 && reg2 != reg1) {
		proto = netlink_get_register(ctx, loc, reg2);
		if (proto == NULL)
			return netlink_error(ctx, loc,
					     "NAT statement has no proto "
					     "expression");

		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		if (stmt->nat.proto != NULL)
			proto = range_expr_alloc(loc, stmt->nat.proto, proto);
		stmt->nat.proto = proto;
	}

	ctx->stmt = stmt;
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

	stmt = masq_stmt_alloc(loc);
	stmt->masq.flags = flags;

	reg1 = netlink_parse_register(nle, NFTNL_EXPR_MASQ_REG_PROTO_MIN);
	if (reg1) {
		proto = netlink_get_register(ctx, loc, reg1);
		if (proto == NULL)
			return netlink_error(ctx, loc,
					     "MASQUERADE statement"
					     "has no proto expression");
		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		stmt->masq.proto = proto;
	}

	reg2 = netlink_parse_register(nle, NFTNL_EXPR_MASQ_REG_PROTO_MAX);
	if (reg2 && reg2 != reg1) {
		proto = netlink_get_register(ctx, loc, reg2);
		if (proto == NULL)
			return netlink_error(ctx, loc,
					     "MASQUERADE statement"
					     "has no proto expression");
		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		if (stmt->masq.proto != NULL)
			proto = range_expr_alloc(loc, stmt->masq.proto, proto);
		stmt->masq.proto = proto;
	}

	ctx->stmt = stmt;
}

static void netlink_parse_redir(struct netlink_parse_ctx *ctx,
				const struct location *loc,
				const struct nftnl_expr *nle)
{
	struct stmt *stmt;
	struct expr *proto;
	enum nft_registers reg1, reg2;
	uint32_t flags;

	stmt = redir_stmt_alloc(loc);

	if (nftnl_expr_is_set(nle, NFTNL_EXPR_REDIR_FLAGS)) {
		flags = nftnl_expr_get_u32(nle, NFTNL_EXPR_REDIR_FLAGS);
		stmt->redir.flags = flags;
	}

	reg1 = netlink_parse_register(nle, NFTNL_EXPR_REDIR_REG_PROTO_MIN);
	if (reg1) {
		proto = netlink_get_register(ctx, loc, reg1);
		if (proto == NULL)
			return netlink_error(ctx, loc,
					     "redirect statement has no proto "
					     "expression");

		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		stmt->redir.proto = proto;
	}

	reg2 = netlink_parse_register(nle, NFTNL_EXPR_REDIR_REG_PROTO_MAX);
	if (reg2 && reg2 != reg1) {
		proto = netlink_get_register(ctx, loc, reg2);
		if (proto == NULL)
			return netlink_error(ctx, loc,
					     "redirect statement has no proto "
					     "expression");

		expr_set_type(proto, &inet_service_type, BYTEORDER_BIG_ENDIAN);
		if (stmt->redir.proto != NULL)
			proto = range_expr_alloc(loc, stmt->redir.proto,
						 proto);
		stmt->redir.proto = proto;
	}

	ctx->stmt = stmt;
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
		if (addr == NULL)
			return netlink_error(ctx, loc,
					     "DUP statement has no destination expression");

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
		if (dev == NULL)
			return netlink_error(ctx, loc,
					     "DUP statement has no output expression");

		expr_set_type(dev, &ifindex_type, BYTEORDER_HOST_ENDIAN);
		if (stmt->dup.to == NULL)
			stmt->dup.to = dev;
		else
			stmt->dup.dev = dev;
	}

	ctx->stmt = stmt;
}

static void netlink_parse_fwd(struct netlink_parse_ctx *ctx,
			      const struct location *loc,
			      const struct nftnl_expr *nle)
{
	enum nft_registers reg1;
	struct expr *dev;
	struct stmt *stmt;

	stmt = fwd_stmt_alloc(loc);

	reg1 = netlink_parse_register(nle, NFTNL_EXPR_FWD_SREG_DEV);
	if (reg1) {
		dev = netlink_get_register(ctx, loc, reg1);
		if (dev == NULL)
			return netlink_error(ctx, loc,
					     "fwd statement has no output expression");

		expr_set_type(dev, &ifindex_type, BYTEORDER_HOST_ENDIAN);
		stmt->fwd.to = dev;
	}

	ctx->stmt = stmt;
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

static void netlink_parse_dynset(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *nle)
{
	const struct nftnl_expr *dnle;
	struct expr *expr;
	struct stmt *stmt, *dstmt;
	struct set *set;
	enum nft_registers sreg;
	const char *name;

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

	if (expr->len < set->keylen) {
		expr = netlink_parse_concat_expr(ctx, loc, sreg, set->keylen);
		if (expr == NULL)
			return;
	}

	expr = set_elem_expr_alloc(&expr->location, expr);
	expr->timeout = nftnl_expr_get_u64(nle, NFTNL_EXPR_DYNSET_TIMEOUT);

	dstmt = NULL;
	dnle = nftnl_expr_get(nle, NFTNL_EXPR_DYNSET_EXPR, NULL);
	if (dnle != NULL) {
		if (netlink_parse_expr(dnle, ctx) < 0)
			return;
		if (ctx->stmt == NULL)
			return netlink_error(ctx, loc,
					     "Could not parse dynset stmt");
		dstmt = ctx->stmt;
	}

	if (dstmt != NULL) {
		stmt = flow_stmt_alloc(loc);
		stmt->flow.set  = set_ref_expr_alloc(loc, set);
		stmt->flow.key  = expr;
		stmt->flow.stmt = dstmt;
	} else {
		stmt = set_stmt_alloc(loc);
		stmt->set.set   = set_ref_expr_alloc(loc, set);
		stmt->set.op    = nftnl_expr_get_u32(nle, NFTNL_EXPR_DYNSET_OP);
		stmt->set.key   = expr;
	}

	ctx->stmt = stmt;
}

static const struct {
	const char	*name;
	void		(*parse)(struct netlink_parse_ctx *ctx,
				 const struct location *loc,
				 const struct nftnl_expr *nle);
} netlink_parsers[] = {
	{ .name = "immediate",	.parse = netlink_parse_immediate },
	{ .name = "cmp",	.parse = netlink_parse_cmp },
	{ .name = "lookup",	.parse = netlink_parse_lookup },
	{ .name = "bitwise",	.parse = netlink_parse_bitwise },
	{ .name = "byteorder",	.parse = netlink_parse_byteorder },
	{ .name = "payload",	.parse = netlink_parse_payload },
	{ .name = "exthdr",	.parse = netlink_parse_exthdr },
	{ .name = "meta",	.parse = netlink_parse_meta },
	{ .name = "ct",		.parse = netlink_parse_ct },
	{ .name = "counter",	.parse = netlink_parse_counter },
	{ .name = "log",	.parse = netlink_parse_log },
	{ .name = "limit",	.parse = netlink_parse_limit },
	{ .name = "reject",	.parse = netlink_parse_reject },
	{ .name = "nat",	.parse = netlink_parse_nat },
	{ .name = "masq",	.parse = netlink_parse_masq },
	{ .name = "redir",	.parse = netlink_parse_redir },
	{ .name = "dup",	.parse = netlink_parse_dup },
	{ .name = "queue",	.parse = netlink_parse_queue },
	{ .name = "dynset",	.parse = netlink_parse_dynset },
	{ .name = "fwd",	.parse = netlink_parse_fwd },
};

static int netlink_parse_expr(const struct nftnl_expr *nle,
			      struct netlink_parse_ctx *ctx)
{
	const char *type = nftnl_expr_get_str(nle, NFTNL_EXPR_NAME);
	struct location loc;
	unsigned int i;

	memset(&loc, 0, sizeof(loc));
	loc.indesc = &indesc_netlink;
	loc.nle = nle;

	for (i = 0; i < array_size(netlink_parsers); i++) {
		if (strcmp(type, netlink_parsers[i].name))
			continue;
		netlink_parsers[i].parse(ctx, &loc, nle);
		return 0;
	}

	netlink_error(ctx, &loc, "unknown expression type '%s'", type);
	return -1;
}

static int netlink_parse_rule_expr(struct nftnl_expr *nle, void *arg)
{
	struct netlink_parse_ctx *ctx = arg;
	int err;

	err = netlink_parse_expr(nle, ctx);
	if (err < 0)
		return err;
	if (ctx->stmt != NULL) {
		list_add_tail(&ctx->stmt->list, &ctx->rule->stmts);
		ctx->stmt = NULL;
	}
	return 0;
}

struct stmt *netlink_parse_set_expr(const struct set *set,
				    const struct nftnl_expr *nle)
{
	struct netlink_parse_ctx ctx, *pctx = &ctx;

	pctx->rule = rule_alloc(&netlink_location, &set->handle);
	pctx->table = table_lookup(&set->handle);
	assert(pctx->table != NULL);

	if (netlink_parse_expr(nle, pctx) < 0)
		return NULL;
	return pctx->stmt;
}

struct rule_pp_ctx {
	struct proto_ctx	pctx;
	struct payload_dep_ctx	pdctx;
	struct stmt		*stmt;
};

static void expr_postprocess(struct rule_pp_ctx *ctx, struct expr **exprp);

static void integer_type_postprocess(struct expr *expr)
{
	struct expr *i;

	switch (expr->ops->type) {
	case EXPR_VALUE:
		if (expr->byteorder == BYTEORDER_HOST_ENDIAN) {
			uint32_t len = div_round_up(expr->len, BITS_PER_BYTE);

			mpz_switch_byteorder(expr->value, len);
		}
		break;
	case EXPR_SET_REF:
		list_for_each_entry(i, &expr->set->init->expressions, list) {
			expr_set_type(i, expr->dtype, expr->byteorder);
			integer_type_postprocess(i);
		}
		break;
	case EXPR_SET_ELEM:
		expr_set_type(expr->key, expr->dtype, expr->byteorder);
		integer_type_postprocess(expr->key);
		break;
	default:
		break;
	}
}

static void payload_match_expand(struct rule_pp_ctx *ctx,
				 struct expr *expr,
				 struct expr *payload)
{
	struct expr *left = payload, *right = expr->right, *tmp;
	struct list_head list = LIST_HEAD_INIT(list);
	struct stmt *nstmt;
	struct expr *nexpr = NULL;
	enum proto_bases base = left->payload.base;
	const struct expr_ops *payload_ops = left->ops;
	bool stacked;

	payload_expr_expand(&list, left, &ctx->pctx);

	list_for_each_entry(left, &list, list) {
		tmp = constant_expr_splice(right, left->len);
		expr_set_type(tmp, left->dtype, left->byteorder);
		if (tmp->byteorder == BYTEORDER_HOST_ENDIAN)
			mpz_switch_byteorder(tmp->value, tmp->len / BITS_PER_BYTE);

		nexpr = relational_expr_alloc(&expr->location, expr->op,
					      left, tmp);
		if (expr->op == OP_EQ)
			left->ops->pctx_update(&ctx->pctx, nexpr);

		nstmt = expr_stmt_alloc(&ctx->stmt->location, nexpr);
		list_add_tail(&nstmt->list, &ctx->stmt->list);

		assert(left->ops == payload_ops);
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
			payload_dependency_kill(&ctx->pdctx, nexpr->left);
			if (left->flags & EXPR_F_PROTOCOL)
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
		if (expr->right->ops->type == EXPR_VALUE) {
			payload_match_expand(ctx, expr, payload);
			break;
		}
		/* Fall through */
	default:
		payload_expr_complete(payload, &ctx->pctx);
		expr_set_type(expr->right, payload->dtype,
			      payload->byteorder);
		payload_dependency_kill(&ctx->pdctx, payload);
		break;
	}
}

static void ct_meta_common_postprocess(const struct expr *expr)
{
	const struct expr *left = expr->left;
	struct expr *right = expr->right;

	switch (expr->op) {
	case OP_LOOKUP:
		expr_set_type(right, left->dtype, left->byteorder);
		if (right->dtype == &integer_type)
			integer_type_postprocess(right);
		break;

	default:
		break;
	}
}

static void meta_match_postprocess(struct rule_pp_ctx *ctx,
				   const struct expr *expr)
{
	struct expr *left = expr->left;

	switch (expr->op) {
	case OP_EQ:
		if (expr->right->ops->type == EXPR_RANGE)
			break;

		expr->left->ops->pctx_update(&ctx->pctx, expr);

		if (ctx->pdctx.pbase == PROTO_BASE_INVALID &&
		    left->flags & EXPR_F_PROTOCOL)
			payload_dependency_store(&ctx->pdctx, ctx->stmt,
						 left->meta.base);
		break;
	default:
		ct_meta_common_postprocess(expr);
		break;
	}
}

static void ct_match_postprocess(struct rule_pp_ctx *ctx,
				 const struct expr *expr)
{
	switch (expr->op) {
	case OP_EQ:
		if (expr->right->ops->type == EXPR_RANGE)
			break;

		expr->left->ops->pctx_update(&ctx->pctx, expr);
		break;
	default:
		ct_meta_common_postprocess(expr);
		break;
	}
}

/* Convert a bitmask to a prefix length */
static unsigned int expr_mask_to_prefix(const struct expr *expr)
{
	unsigned long n;

	n = mpz_scan1(expr->value, 0);
	return mpz_scan0(expr->value, n + 1) - n;
}

/* Return true if a bitmask can be expressed as a prefix length */
static bool expr_mask_is_prefix(const struct expr *expr)
{
	unsigned long n1, n2;

	n1 = mpz_scan1(expr->value, 0);
	if (n1 == ULONG_MAX)
		return false;
	n2 = mpz_scan0(expr->value, n1 + 1);
	if (n2 < expr->len || n2 == ULONG_MAX)
		return false;
	return true;
}

/* Convert a series of inclusive OR expressions into a list */
static struct expr *binop_tree_to_list(struct expr *list, struct expr *expr)
{
	if (expr->ops->type == EXPR_BINOP && expr->op == OP_OR) {
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
	switch (left->ops->type) {
	case EXPR_PAYLOAD:
	case EXPR_EXTHDR:
		value->len = left->len;
		break;
	default:
		BUG("unknown expression type %s\n", left->ops->name);
		break;
	}
}

static void binop_adjust(struct expr *expr, unsigned int shift)
{
	const struct expr *binop = expr->left;
	struct expr *right = expr->right, *i;

	switch (right->ops->type) {
	case EXPR_VALUE:
		binop_adjust_one(binop, right, shift);
		break;
	case EXPR_SET_REF:
		list_for_each_entry(i, &right->set->init->expressions, list) {
			switch (i->key->ops->type) {
			case EXPR_VALUE:
				binop_adjust_one(binop, i->key, shift);
				break;
			case EXPR_RANGE:
				binop_adjust_one(binop, i->key->left, shift);
				binop_adjust_one(binop, i->key->right, shift);
				break;
			case EXPR_SET_ELEM:
				binop_adjust_one(binop, i->key->key, shift);
				break;
			default:
				BUG("unknown expression type %s\n", i->key->ops->name);
			}
		}
		break;
	default:
		BUG("unknown expression type %s\n", expr->ops->name);
		break;
	}
}

static void binop_postprocess(struct rule_pp_ctx *ctx, struct expr *expr)
{
	struct expr *binop = expr->left;
	struct expr *left = binop->left;
	struct expr *mask = binop->right;
	unsigned int shift;

	if ((left->ops->type == EXPR_PAYLOAD &&
	    payload_expr_trim(left, mask, &ctx->pctx, &shift)) ||
	    (left->ops->type == EXPR_EXTHDR &&
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

		assert(expr->left->ops->type == EXPR_BINOP);
		assert(binop->left == left);
		expr->left = expr_get(left);
		expr_free(binop);
		if (left->ops->type == EXPR_PAYLOAD)
			payload_match_postprocess(ctx, expr, left);
		else if (left->ops->type == EXPR_EXTHDR)
			expr_set_type(expr->right, left->dtype, left->byteorder);
	}
}

static void map_binop_postprocess(struct rule_pp_ctx *ctx, struct expr *expr)
{
	struct expr *binop = expr->left;

	if (binop->op != OP_AND)
		return;

	if (binop->left->ops->type == EXPR_PAYLOAD &&
	    binop->right->ops->type == EXPR_VALUE)
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
		 * op to OP_FLAGCMP.
		 */
		expr_free(value);

		expr->left  = expr_get(binop->left);
		expr->right = binop_tree_to_list(NULL, binop->right);
		expr->op    = OP_FLAGCMP;

		expr_free(binop);
	} else if (binop->left->dtype->flags & DTYPE_F_PREFIX &&
		   binop->op == OP_AND &&
		   expr_mask_is_prefix(binop->right)) {
		expr->left = expr_get(binop->left);
		expr->right = prefix_expr_alloc(&expr->location,
						expr_get(value),
						expr_mask_to_prefix(binop->right));
		expr_free(value);
		expr_free(binop);
	} else if (binop->op == OP_AND &&
		   binop->right->ops->type == EXPR_VALUE) {
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

	return constant_expr_alloc(loc, &string_type, BYTEORDER_HOST_ENDIAN,
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

	tmp = constant_expr_alloc(&expr->location, &string_type,
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
	expr->len = len;

	return nulterminated;
}

static struct expr *expr_postprocess_string(struct expr *expr)
{
	struct expr *mask;

	assert(expr->dtype->type == TYPE_STRING);
	if (__expr_postprocess_string(&expr))
		return expr;

	mask = constant_expr_alloc(&expr->location, &integer_type,
				   BYTEORDER_HOST_ENDIAN,
				   expr->len + BITS_PER_BYTE, NULL);
	mpz_init_bitmask(mask->value, expr->len);
	return string_wildcard_expr_alloc(&expr->location, mask, expr);
}

static void expr_postprocess(struct rule_pp_ctx *ctx, struct expr **exprp)
{
	struct expr *expr = *exprp, *i;

	//pr_debug("%s len %u\n", expr->ops->name, expr->len);

	switch (expr->ops->type) {
	case EXPR_MAP:
		switch (expr->map->ops->type) {
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
		expr->dtype = concat_type_alloc(ntype);
		break;
	}
	case EXPR_UNARY:
		expr_postprocess(ctx, &expr->arg);
		expr_set_type(expr->arg, expr->arg->dtype, !expr->arg->byteorder);

		*exprp = expr_get(expr->arg);
		expr_free(expr);
		break;
	case EXPR_BINOP:
		expr_postprocess(ctx, &expr->left);
		expr_set_type(expr->right, expr->left->dtype,
			      expr->left->byteorder);
		expr_postprocess(ctx, &expr->right);

		expr_set_type(expr, expr->left->dtype,
			      expr->left->byteorder);
		break;
	case EXPR_RELATIONAL:
		switch (expr->left->ops->type) {
		case EXPR_PAYLOAD:
			payload_match_postprocess(ctx, expr, expr->left);
			return;
		default:
			expr_postprocess(ctx, &expr->left);
			break;
		}

		expr_set_type(expr->right, expr->left->dtype, expr->left->byteorder);
		expr_postprocess(ctx, &expr->right);

		switch (expr->left->ops->type) {
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
		payload_dependency_kill(&ctx->pdctx, expr);
		break;
	case EXPR_VALUE:
		// FIXME
		if (expr->byteorder == BYTEORDER_HOST_ENDIAN)
			mpz_switch_byteorder(expr->value, expr->len / BITS_PER_BYTE);

		if (expr->dtype->type == TYPE_STRING)
			*exprp = expr_postprocess_string(expr);

		if (expr->dtype->basetype != NULL &&
		    expr->dtype->basetype->type == TYPE_BITMASK)
			*exprp = bitmask_expr_to_binops(expr);

		break;
	case EXPR_RANGE:
		expr_postprocess(ctx, &expr->left);
		expr_postprocess(ctx, &expr->right);
		break;
	case EXPR_SET_ELEM:
		expr_postprocess(ctx, &expr->key);
		break;
	case EXPR_EXTHDR:
		__payload_dependency_kill(&ctx->pdctx, PROTO_BASE_NETWORK_HDR);
		break;
	case EXPR_SET_REF:
	case EXPR_META:
	case EXPR_VERDICT:
		break;
	case EXPR_CT:
		ct_expr_update_type(&ctx->pctx, expr);
		break;
	default:
		BUG("unknown expression type %s\n", expr->ops->name);
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
		stmt->reject.expr->dtype = &icmp_code_type;
		break;
	case NFPROTO_IPV6:
		stmt->reject.family = rctx->pctx.family;
		stmt->reject.expr->dtype = &icmpv6_code_type;
		break;
	case NFPROTO_INET:
		if (stmt->reject.type == NFT_REJECT_ICMPX_UNREACH) {
			stmt->reject.expr->dtype = &icmpx_code_type;
			break;
		}
		base = rctx->pctx.protocol[PROTO_BASE_LL_HDR].desc;
		desc = rctx->pctx.protocol[PROTO_BASE_NETWORK_HDR].desc;
		protocol = proto_find_num(base, desc);
		switch (protocol) {
		case NFPROTO_IPV4:
			stmt->reject.expr->dtype = &icmp_code_type;
			break;
		case NFPROTO_IPV6:
			stmt->reject.expr->dtype = &icmpv6_code_type;
			break;
		}
		stmt->reject.family = protocol;
		break;
	case NFPROTO_BRIDGE:
		if (stmt->reject.type == NFT_REJECT_ICMPX_UNREACH) {
			stmt->reject.expr->dtype = &icmpx_code_type;
			break;
		}
		base = rctx->pctx.protocol[PROTO_BASE_LL_HDR].desc;
		desc = rctx->pctx.protocol[PROTO_BASE_NETWORK_HDR].desc;
		protocol = proto_find_num(base, desc);
		switch (protocol) {
		case __constant_htons(ETH_P_IP):
			stmt->reject.family = NFPROTO_IPV4;
			stmt->reject.expr->dtype = &icmp_code_type;
			break;
		case __constant_htons(ETH_P_IPV6):
			stmt->reject.family = NFPROTO_IPV6;
			stmt->reject.expr->dtype = &icmpv6_code_type;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

static bool expr_may_merge_range(struct expr *expr, struct expr *prev,
				 enum ops *op)
{
	struct expr *left, *prev_left;

	if (prev->ops->type == EXPR_RELATIONAL &&
	    expr->ops->type == EXPR_RELATIONAL) {
		/* ct and meta needs an unary to swap byteorder, in this case
		 * we have to explore the inner branch in this tree.
		 */
		if (expr->left->ops->type == EXPR_UNARY)
			left = expr->left->arg;
		else
			left = expr->left;

		if (prev->left->ops->type == EXPR_UNARY)
			prev_left = prev->left->arg;
		else
			prev_left = prev->left;

		if (left->ops->type == prev_left->ops->type) {
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

static void rule_parse_postprocess(struct netlink_parse_ctx *ctx, struct rule *rule)
{
	struct rule_pp_ctx rctx;
	struct stmt *stmt, *next;

	memset(&rctx, 0, sizeof(rctx));
	proto_ctx_init(&rctx.pctx, rule->handle.family);

	list_for_each_entry_safe(stmt, next, &rule->stmts, list) {
		rctx.stmt = stmt;

		switch (stmt->ops->type) {
		case STMT_EXPRESSION:
			stmt_expr_postprocess(&rctx);
			break;
		case STMT_PAYLOAD:
			expr_postprocess(&rctx, &stmt->payload.expr);
			expr_set_type(stmt->payload.val,
				      stmt->payload.expr->dtype,
				      stmt->payload.expr->byteorder);
			expr_postprocess(&rctx, &stmt->payload.val);
			break;
		case STMT_FLOW:
			expr_postprocess(&rctx, &stmt->flow.key);
			break;
		case STMT_META:
			if (stmt->meta.expr != NULL)
				expr_postprocess(&rctx, &stmt->meta.expr);
			break;
		case STMT_CT:
			if (stmt->ct.expr != NULL)
				expr_postprocess(&rctx, &stmt->ct.expr);
			break;
		case STMT_NAT:
			if (stmt->nat.addr != NULL)
				expr_postprocess(&rctx, &stmt->nat.addr);
			if (stmt->nat.proto != NULL)
				expr_postprocess(&rctx, &stmt->nat.proto);
			break;
		case STMT_REDIR:
			if (stmt->redir.proto != NULL)
				expr_postprocess(&rctx, &stmt->redir.proto);
			break;
		case STMT_REJECT:
			stmt_reject_postprocess(&rctx);
			break;
		case STMT_SET:
			expr_postprocess(&rctx, &stmt->set.key);
			break;
		case STMT_DUP:
			if (stmt->dup.to != NULL)
				expr_postprocess(&rctx, &stmt->dup.to);
			if (stmt->dup.dev != NULL)
				expr_postprocess(&rctx, &stmt->dup.dev);
			break;
		case STMT_FWD:
			if (stmt->fwd.to != NULL)
				expr_postprocess(&rctx, &stmt->fwd.to);
			break;
		default:
			break;
		}
		rctx.pdctx.prev = rctx.stmt;
	}
}

static int parse_udata_cb(const struct nftnl_udata *attr, void *data)
{
	unsigned char *value = nftnl_udata_get(attr);
	uint8_t type = nftnl_udata_type(attr);
	uint8_t len = nftnl_udata_len(attr);
	const struct nftnl_udata **tb = data;

	switch (type) {
	case UDATA_TYPE_COMMENT:
		if (value[len - 1] != '\0')
			return -1;
		break;
	default:
		return 0;
	}
	tb[type] = attr;
	return 0;
}

static char *udata_get_comment(const void *data, uint32_t data_len)
{
	const struct nftnl_udata *tb[UDATA_TYPE_MAX + 1] = {};

	if (nftnl_udata_parse(data, data_len, parse_udata_cb, tb) < 0)
		return NULL;

	if (!tb[UDATA_TYPE_COMMENT])
		return NULL;

	return xstrdup(nftnl_udata_get(tb[UDATA_TYPE_COMMENT]));
}

struct rule *netlink_delinearize_rule(struct netlink_ctx *ctx,
				      struct nftnl_rule *nlr)
{
	struct netlink_parse_ctx _ctx, *pctx = &_ctx;
	struct handle h;

	memset(&_ctx, 0, sizeof(_ctx));
	_ctx.msgs = ctx->msgs;

	memset(&h, 0, sizeof(h));
	h.family = nftnl_rule_get_u32(nlr, NFTNL_RULE_FAMILY);
	h.table  = xstrdup(nftnl_rule_get_str(nlr, NFTNL_RULE_TABLE));
	h.chain  = xstrdup(nftnl_rule_get_str(nlr, NFTNL_RULE_CHAIN));
	h.handle.id = nftnl_rule_get_u64(nlr, NFTNL_RULE_HANDLE);

	if (nftnl_rule_is_set(nlr, NFTNL_RULE_POSITION))
		h.position.id = nftnl_rule_get_u64(nlr, NFTNL_RULE_POSITION);

	pctx->rule = rule_alloc(&netlink_location, &h);
	pctx->table = table_lookup(&h);
	assert(pctx->table != NULL);

	if (nftnl_rule_is_set(nlr, NFTNL_RULE_USERDATA)) {
		const void *data;
		uint32_t len;

		data = nftnl_rule_get_data(nlr, NFTNL_RULE_USERDATA, &len);
		pctx->rule->comment = udata_get_comment(data, len);
	}

	nftnl_expr_foreach(nlr, netlink_parse_rule_expr, pctx);

	rule_parse_postprocess(pctx, pctx->rule);
	netlink_release_registers(pctx);
	return pctx->rule;
}
