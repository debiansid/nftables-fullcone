/*
 * Copyright (c) 2008-2012 Patrick McHardy <kaber@trash.net>
 * Copyright (c) 2013 Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <libmnl/libmnl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include <libnftnl/table.h>
#include <libnftnl/trace.h>
#include <libnftnl/chain.h>
#include <libnftnl/expr.h>
#include <libnftnl/object.h>
#include <libnftnl/set.h>
#include <libnftnl/udata.h>
#include <libnftnl/common.h>
#include <linux/netfilter/nfnetlink.h>
#include <linux/netfilter/nf_tables.h>
#include <linux/netfilter.h>

#include <nftables.h>
#include <netlink.h>
#include <mnl.h>
#include <expression.h>
#include <statement.h>
#include <gmputil.h>
#include <utils.h>
#include <erec.h>
#include <iface.h>

#define nft_mon_print(monh, ...) nft_print(monh->ctx->octx, __VA_ARGS__)

const struct input_descriptor indesc_netlink = {
	.name	= "netlink",
	.type	= INDESC_NETLINK,
};

const struct location netlink_location = {
	.indesc	= &indesc_netlink,
};

struct mnl_socket *netlink_open_sock(void)
{
	struct mnl_socket *nf_sock;

	nf_sock = mnl_socket_open(NETLINK_NETFILTER);
	if (nf_sock == NULL)
		netlink_init_error();

	fcntl(mnl_socket_get_fd(nf_sock), F_SETFL, O_NONBLOCK);

	return nf_sock;
}

void netlink_close_sock(struct mnl_socket *nf_sock)
{
	if (nf_sock)
		mnl_socket_close(nf_sock);
}

void netlink_restart(struct mnl_socket *nf_sock)
{
	netlink_close_sock(nf_sock);
	nf_sock = netlink_open_sock();
}

void netlink_genid_get(struct mnl_socket *nf_sock, uint32_t seqnum)
{
	mnl_genid_get(nf_sock, seqnum);
}

void __noreturn __netlink_abi_error(const char *file, int line,
				    const char *reason)
{
	fprintf(stderr, "E: Contact urgently your Linux kernel vendor. "
		"Netlink ABI is broken: %s:%d %s\n", file, line, reason);
	exit(NFT_EXIT_FAILURE);
}

int netlink_io_error(struct netlink_ctx *ctx, const struct location *loc,
		     const char *fmt, ...)
{
	struct error_record *erec;
	va_list ap;

	if (loc == NULL)
		loc = &netlink_location;

	va_start(ap, fmt);
	erec = erec_vcreate(EREC_ERROR, loc, fmt, ap);
	va_end(ap);
	erec_queue(erec, ctx->msgs);
	return -1;
}

void __noreturn __netlink_init_error(const char *filename, int line,
				     const char *reason)
{
	fprintf(stderr, "%s:%d: Unable to initialize Netlink socket: %s\n",
		filename, line, reason);
	exit(NFT_EXIT_NONL);
}

struct nftnl_table *alloc_nftnl_table(const struct handle *h)
{
	struct nftnl_table *nlt;

	nlt = nftnl_table_alloc();
	if (nlt == NULL)
		memory_allocation_error();

	nftnl_table_set_u32(nlt, NFTNL_TABLE_FAMILY, h->family);
	if (h->table != NULL)
		nftnl_table_set(nlt, NFTNL_TABLE_NAME, h->table);

	return nlt;
}

struct nftnl_chain *alloc_nftnl_chain(const struct handle *h)
{
	struct nftnl_chain *nlc;

	nlc = nftnl_chain_alloc();
	if (nlc == NULL)
		memory_allocation_error();

	nftnl_chain_set_u32(nlc, NFTNL_CHAIN_FAMILY, h->family);
	nftnl_chain_set_str(nlc, NFTNL_CHAIN_TABLE, h->table);
	if (h->handle.id != 0)
		nftnl_chain_set_u64(nlc, NFTNL_CHAIN_HANDLE, h->handle.id);
	if (h->chain != NULL)
		nftnl_chain_set_str(nlc, NFTNL_CHAIN_NAME, h->chain);

	return nlc;
}

struct nftnl_rule *alloc_nftnl_rule(const struct handle *h)
{
	struct nftnl_rule *nlr;

	nlr = nftnl_rule_alloc();
	if (nlr == NULL)
		memory_allocation_error();

	nftnl_rule_set_u32(nlr, NFTNL_RULE_FAMILY, h->family);
	nftnl_rule_set_str(nlr, NFTNL_RULE_TABLE, h->table);
	if (h->chain != NULL)
		nftnl_rule_set_str(nlr, NFTNL_RULE_CHAIN, h->chain);
	if (h->handle.id)
		nftnl_rule_set_u64(nlr, NFTNL_RULE_HANDLE, h->handle.id);
	if (h->position.id)
		nftnl_rule_set_u64(nlr, NFTNL_RULE_POSITION, h->position.id);

	return nlr;
}

struct nftnl_expr *alloc_nft_expr(const char *name)
{
	struct nftnl_expr *nle;

	nle = nftnl_expr_alloc(name);
	if (nle == NULL)
		memory_allocation_error();

	return nle;
}

struct nftnl_set *alloc_nftnl_set(const struct handle *h)
{
	struct nftnl_set *nls;

	nls = nftnl_set_alloc();
	if (nls == NULL)
		memory_allocation_error();

	nftnl_set_set_u32(nls, NFTNL_SET_FAMILY, h->family);
	nftnl_set_set_str(nls, NFTNL_SET_TABLE, h->table);
	if (h->set != NULL)
		nftnl_set_set_str(nls, NFTNL_SET_NAME, h->set);
	if (h->set_id)
		nftnl_set_set_u32(nls, NFTNL_SET_ID, h->set_id);

	return nls;
}

static struct nftnl_set_elem *alloc_nftnl_setelem(const struct expr *set,
						  const struct expr *expr)
{
	const struct expr *elem, *key, *data;
	struct nftnl_set_elem *nlse;
	struct nft_data_linearize nld;
	struct nftnl_udata_buf *udbuf = NULL;

	nlse = nftnl_set_elem_alloc();
	if (nlse == NULL)
		memory_allocation_error();

	data = NULL;
	if (expr->ops->type == EXPR_MAPPING) {
		elem = expr->left;
		if (!(expr->flags & EXPR_F_INTERVAL_END))
			data = expr->right;
	} else {
		elem = expr;
	}
	key = elem->key;

	netlink_gen_data(key, &nld);
	nftnl_set_elem_set(nlse, NFTNL_SET_ELEM_KEY, &nld.value, nld.len);
	if (elem->timeout)
		nftnl_set_elem_set_u64(nlse, NFTNL_SET_ELEM_TIMEOUT,
				       elem->timeout);
	if (elem->comment || expr->elem_flags) {
		udbuf = nftnl_udata_buf_alloc(NFT_USERDATA_MAXLEN);
		if (!udbuf)
			memory_allocation_error();
	}
	if (elem->comment) {
		if (!nftnl_udata_put_strz(udbuf, UDATA_SET_ELEM_COMMENT,
					  elem->comment))
			memory_allocation_error();
	}
	if (expr->elem_flags) {
		if (!nftnl_udata_put_u32(udbuf, UDATA_SET_ELEM_FLAGS,
					 expr->elem_flags))
			memory_allocation_error();
	}
	if (udbuf) {
		nftnl_set_elem_set(nlse, NFTNL_SET_ELEM_USERDATA,
				   nftnl_udata_buf_data(udbuf),
				   nftnl_udata_buf_len(udbuf));
		nftnl_udata_buf_free(udbuf);
	}
	if (set->set_flags & NFT_SET_MAP && data != NULL) {
		netlink_gen_data(data, &nld);
		switch (data->ops->type) {
		case EXPR_VERDICT:
			nftnl_set_elem_set_u32(nlse, NFTNL_SET_ELEM_VERDICT,
					       data->verdict);
			if (data->chain != NULL)
				nftnl_set_elem_set(nlse, NFTNL_SET_ELEM_CHAIN,
						   nld.chain, strlen(nld.chain));
			break;
		case EXPR_VALUE:
			nftnl_set_elem_set(nlse, NFTNL_SET_ELEM_DATA,
					   nld.value, nld.len);
			break;
		default:
			BUG("unexpected set element expression\n");
			break;
		}
	}
	if (set->set_flags & NFT_SET_OBJECT) {
		netlink_gen_data(data, &nld);
		nftnl_set_elem_set(nlse, NFTNL_SET_ELEM_OBJREF,
				   nld.value, nld.len);
	}

	if (expr->flags & EXPR_F_INTERVAL_END)
		nftnl_set_elem_set_u32(nlse, NFTNL_SET_ELEM_FLAGS,
				       NFT_SET_ELEM_INTERVAL_END);

	return nlse;
}

static struct nftnl_obj *
__alloc_nftnl_obj(const struct handle *h, uint32_t type)
{
	struct nftnl_obj *nlo;

	nlo = nftnl_obj_alloc();
	if (nlo == NULL)
		memory_allocation_error();

	nftnl_obj_set_u32(nlo, NFTNL_OBJ_FAMILY, h->family);
	nftnl_obj_set_str(nlo, NFTNL_OBJ_TABLE, h->table);
	if (h->obj != NULL)
		nftnl_obj_set_str(nlo, NFTNL_OBJ_NAME, h->obj);

	nftnl_obj_set_u32(nlo, NFTNL_OBJ_TYPE, type);

	return nlo;
}

static struct nftnl_obj *
alloc_nftnl_obj(const struct handle *h, struct obj *obj)
{
	struct nftnl_obj *nlo;

	nlo = __alloc_nftnl_obj(h, obj->type);

	switch (obj->type) {
	case NFT_OBJECT_COUNTER:
		nftnl_obj_set_u64(nlo, NFTNL_OBJ_CTR_PKTS,
				  obj->counter.packets);
		nftnl_obj_set_u64(nlo, NFTNL_OBJ_CTR_BYTES,
				  obj->counter.bytes);
		break;
	case NFT_OBJECT_QUOTA:
		nftnl_obj_set_u64(nlo, NFTNL_OBJ_QUOTA_BYTES,
				  obj->quota.bytes);
		nftnl_obj_set_u64(nlo, NFTNL_OBJ_QUOTA_CONSUMED,
				  obj->quota.used);
		nftnl_obj_set_u32(nlo, NFTNL_OBJ_QUOTA_FLAGS,
				  obj->quota.flags);
		break;
	case NFT_OBJECT_CT_HELPER:
		nftnl_obj_set_str(nlo, NFTNL_OBJ_CT_HELPER_NAME,
				  obj->ct_helper.name);
		nftnl_obj_set_u8(nlo, NFTNL_OBJ_CT_HELPER_L4PROTO,
				  obj->ct_helper.l4proto);
		if (obj->ct_helper.l3proto)
			nftnl_obj_set_u16(nlo, NFTNL_OBJ_CT_HELPER_L3PROTO,
					  obj->ct_helper.l3proto);
		break;
	case NFT_OBJECT_LIMIT:
		nftnl_obj_set_u64(nlo, NFTNL_OBJ_LIMIT_RATE, obj->limit.rate);
		nftnl_obj_set_u64(nlo, NFTNL_OBJ_LIMIT_UNIT, obj->limit.unit);
		nftnl_obj_set_u32(nlo, NFTNL_OBJ_LIMIT_BURST, obj->limit.burst);
		nftnl_obj_set_u32(nlo, NFTNL_OBJ_LIMIT_TYPE, obj->limit.type);
		nftnl_obj_set_u32(nlo, NFTNL_OBJ_LIMIT_FLAGS, obj->limit.flags);
		break;
	default:
		BUG("Unknown type %d\n", obj->type);
		break;
	}
	return nlo;
}

void netlink_gen_raw_data(const mpz_t value, enum byteorder byteorder,
			  unsigned int len, struct nft_data_linearize *data)
{
	assert(len > 0);
	mpz_export_data(data->value, value, byteorder, len);
	data->len = len;
}

static void netlink_gen_concat_data(const struct expr *expr,
				    struct nft_data_linearize *nld)
{
	const struct expr *i;
	unsigned int len, offset;

	len = expr->len / BITS_PER_BYTE;
	if (1) {
		unsigned char data[len];

		memset(data, 0, sizeof(data));
		offset = 0;
		list_for_each_entry(i, &expr->expressions, list) {
			assert(i->ops->type == EXPR_VALUE);
			mpz_export_data(data + offset, i->value, i->byteorder,
					i->len / BITS_PER_BYTE);
			offset += netlink_padded_len(i->len) / BITS_PER_BYTE;
		}

		memcpy(nld->value, data, len);
		nld->len = len;
	}
}

static void netlink_gen_constant_data(const struct expr *expr,
				      struct nft_data_linearize *data)
{
	assert(expr->ops->type == EXPR_VALUE);
	netlink_gen_raw_data(expr->value, expr->byteorder,
			     div_round_up(expr->len, BITS_PER_BYTE), data);
}

static void netlink_gen_verdict(const struct expr *expr,
				struct nft_data_linearize *data)
{
	data->verdict = expr->verdict;

	switch (expr->verdict) {
	case NFT_JUMP:
	case NFT_GOTO:
		strncpy(data->chain, expr->chain, NFT_CHAIN_MAXNAMELEN);
		data->chain[NFT_CHAIN_MAXNAMELEN-1] = '\0';
		break;
	}
}

void netlink_gen_data(const struct expr *expr, struct nft_data_linearize *data)
{
	switch (expr->ops->type) {
	case EXPR_VALUE:
		return netlink_gen_constant_data(expr, data);
	case EXPR_CONCAT:
		return netlink_gen_concat_data(expr, data);
	case EXPR_VERDICT:
		return netlink_gen_verdict(expr, data);
	default:
		BUG("invalid data expression type %s\n", expr->ops->name);
	}
}

struct expr *netlink_alloc_value(const struct location *loc,
				 const struct nft_data_delinearize *nld)
{
	return constant_expr_alloc(loc, &invalid_type, BYTEORDER_INVALID,
				   nld->len * BITS_PER_BYTE, nld->value);
}

static struct expr *netlink_alloc_verdict(const struct location *loc,
					  const struct nft_data_delinearize *nld)
{
	char *chain;

	switch (nld->verdict) {
	case NFT_JUMP:
	case NFT_GOTO:
		chain = xstrdup(nld->chain);
		break;
	default:
		chain = NULL;
		break;
	}

	return verdict_expr_alloc(loc, nld->verdict, chain);
}

struct expr *netlink_alloc_data(const struct location *loc,
				const struct nft_data_delinearize *nld,
				enum nft_registers dreg)
{
	switch (dreg) {
	case NFT_REG_VERDICT:
		return netlink_alloc_verdict(loc, nld);
	default:
		return netlink_alloc_value(loc, nld);
	}
}

int netlink_add_rule_batch(struct netlink_ctx *ctx,
			   const struct handle *h,
		           const struct rule *rule, uint32_t flags)
{
	struct nftnl_rule *nlr;
	int err;

	nlr = alloc_nftnl_rule(&rule->handle);
	netlink_linearize_rule(ctx, nlr, rule);
	err = mnl_nft_rule_batch_add(nlr, ctx->batch, flags | NLM_F_EXCL,
				     ctx->seqnum);
	nftnl_rule_free(nlr);
	if (err < 0)
		netlink_io_error(ctx, &rule->location,
				 "Could not add rule to batch: %s",
				 strerror(errno));
	return err;
}

int netlink_replace_rule_batch(struct netlink_ctx *ctx, const struct handle *h,
			       const struct rule *rule,
			       const struct location *loc)
{
	struct nftnl_rule *nlr;
	int err, flags = 0;

	if (ctx->octx->echo) {
		err = cache_update(ctx->nf_sock, ctx->cache,
				   CMD_INVALID, ctx->msgs,
				   ctx->debug_mask & DEBUG_NETLINK, ctx->octx);
		if (err < 0)
			return err;

		flags |= NLM_F_ECHO;
	}

	nlr = alloc_nftnl_rule(&rule->handle);
	netlink_linearize_rule(ctx, nlr, rule);
	err = mnl_nft_rule_batch_replace(nlr, ctx->batch, flags, ctx->seqnum);
	nftnl_rule_free(nlr);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not replace rule to batch: %s",
				 strerror(errno));
	return err;
}

int netlink_del_rule_batch(struct netlink_ctx *ctx, const struct handle *h,
			   const struct location *loc)
{
	struct nftnl_rule *nlr;
	int err;

	nlr = alloc_nftnl_rule(h);
	err = mnl_nft_rule_batch_del(nlr, ctx->batch, 0, ctx->seqnum);
	nftnl_rule_free(nlr);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not delete rule to batch: %s",
				 strerror(errno));
	return err;
}

void netlink_dump_rule(const struct nftnl_rule *nlr, struct netlink_ctx *ctx)
{
	FILE *fp = ctx->octx->output_fp;

	if (!(ctx->debug_mask & DEBUG_NETLINK) || !fp)
		return;

	nftnl_rule_fprintf(fp, nlr, 0, 0);
	fprintf(fp, "\n");
}

void netlink_dump_expr(const struct nftnl_expr *nle,
		       FILE *fp, unsigned int debug_mask)
{
	char buf[4096];

	if (!(debug_mask & DEBUG_NETLINK))
		return;

	nftnl_expr_snprintf(buf, sizeof(buf), nle, 0, 0);
	fprintf(fp, "%s\n", buf);
}

static int list_rule_cb(struct nftnl_rule *nlr, void *arg)
{
	struct netlink_ctx *ctx = arg;
	const struct handle *h = ctx->data;
	struct rule *rule;
	const char *table, *chain;
	uint32_t family;

	family = nftnl_rule_get_u32(nlr, NFTNL_RULE_FAMILY);
	table  = nftnl_rule_get_str(nlr, NFTNL_RULE_TABLE);
	chain  = nftnl_rule_get_str(nlr, NFTNL_RULE_CHAIN);

	if (h->family != family ||
	    strcmp(table, h->table) != 0 ||
	    (h->chain && strcmp(chain, h->chain) != 0))
		return 0;

	netlink_dump_rule(nlr, ctx);
	rule = netlink_delinearize_rule(ctx, nlr);
	list_add_tail(&rule->list, &ctx->list);

	return 0;
}

static int netlink_list_rules(struct netlink_ctx *ctx, const struct handle *h,
			      const struct location *loc)
{
	struct nftnl_rule_list *rule_cache;

	rule_cache = mnl_nft_rule_dump(ctx->nf_sock, h->family, ctx->seqnum);
	if (rule_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return 0;
	}

	ctx->data = h;
	nftnl_rule_list_foreach(rule_cache, list_rule_cb, ctx);
	nftnl_rule_list_free(rule_cache);
	return 0;
}

static int netlink_flush_rules(struct netlink_ctx *ctx, const struct handle *h,
			       const struct location *loc)
{
	return netlink_del_rule_batch(ctx, h, loc);
}

void netlink_dump_chain(const struct nftnl_chain *nlc, struct netlink_ctx *ctx)
{
	FILE *fp = ctx->octx->output_fp;

	if (!(ctx->debug_mask & DEBUG_NETLINK) || !fp)
		return;

	nftnl_chain_fprintf(fp, nlc, 0, 0);
	fprintf(fp, "\n");
}

static int netlink_add_chain_compat(struct netlink_ctx *ctx,
				    const struct handle *h,
				    const struct location *loc,
				    const struct chain *chain, uint32_t flags)
{
	struct nftnl_chain *nlc;
	int err;

	nlc = alloc_nftnl_chain(h);
	if (chain != NULL) {
		if (chain->flags & CHAIN_F_BASECHAIN) {
			nftnl_chain_set_u32(nlc, NFTNL_CHAIN_HOOKNUM,
					    chain->hooknum);
			nftnl_chain_set_s32(nlc, NFTNL_CHAIN_PRIO,
					    chain->priority);
			nftnl_chain_set_str(nlc, NFTNL_CHAIN_TYPE,
					    chain->type);
		}
		if (chain->policy != -1)
			nftnl_chain_set_u32(nlc, NFTNL_CHAIN_POLICY,
					    chain->policy);
	}

	netlink_dump_chain(nlc, ctx);
	err = mnl_nft_chain_add(ctx->nf_sock, nlc, flags, ctx->seqnum);
	nftnl_chain_free(nlc);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not add chain: %s",
				 strerror(errno));
	return err;
}

static int netlink_add_chain_batch(struct netlink_ctx *ctx,
				   const struct handle *h,
				   const struct location *loc,
				   const struct chain *chain, uint32_t flags)
{
	struct nftnl_chain *nlc;
	int err;

	nlc = alloc_nftnl_chain(h);
	if (chain != NULL) {
		if (chain->flags & CHAIN_F_BASECHAIN) {
			nftnl_chain_set_u32(nlc, NFTNL_CHAIN_HOOKNUM,
					    chain->hooknum);
			nftnl_chain_set_s32(nlc, NFTNL_CHAIN_PRIO,
					    chain->priority);
			nftnl_chain_set_str(nlc, NFTNL_CHAIN_TYPE,
					    chain->type);
		}
		if (chain->policy != -1)
			nftnl_chain_set_u32(nlc, NFTNL_CHAIN_POLICY,
					    chain->policy);
		if (chain->dev != NULL)
			nftnl_chain_set_str(nlc, NFTNL_CHAIN_DEV,
					    chain->dev);
	}

	netlink_dump_chain(nlc, ctx);
	err = mnl_nft_chain_batch_add(nlc, ctx->batch, flags, ctx->seqnum);
	nftnl_chain_free(nlc);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not add chain: %s",
				 strerror(errno));
	return err;
}

int netlink_add_chain(struct netlink_ctx *ctx, const struct handle *h,
		      const struct location *loc, const struct chain *chain,
		      uint32_t flags)
{
	if (ctx->batch_supported)
		return netlink_add_chain_batch(ctx, h, loc, chain, flags);
	else
		return netlink_add_chain_compat(ctx, h, loc, chain, flags);
}

static int netlink_rename_chain_compat(struct netlink_ctx *ctx,
				       const struct handle *h,
				       const struct location *loc,
				       const char *name)
{
	struct nftnl_chain *nlc;
	int err;

	nlc = alloc_nftnl_chain(h);
	nftnl_chain_set_str(nlc, NFTNL_CHAIN_NAME, name);
	netlink_dump_chain(nlc, ctx);
	err = mnl_nft_chain_add(ctx->nf_sock, nlc, 0, ctx->seqnum);
	nftnl_chain_free(nlc);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not rename chain: %s",
				 strerror(errno));
	return err;
}

static int netlink_rename_chain_batch(struct netlink_ctx *ctx,
				      const struct handle *h,
				      const struct location *loc,
				      const char *name)
{
	struct nftnl_chain *nlc;
	int err;

	nlc = alloc_nftnl_chain(h);
	nftnl_chain_set_str(nlc, NFTNL_CHAIN_NAME, name);
	netlink_dump_chain(nlc, ctx);
	err = mnl_nft_chain_batch_add(nlc, ctx->batch, 0, ctx->seqnum);
	nftnl_chain_free(nlc);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not rename chain: %s",
				 strerror(errno));
	return err;
}

int netlink_rename_chain(struct netlink_ctx *ctx, const struct handle *h,
			 const struct location *loc, const char *name)
{
	if (ctx->batch_supported)
		return netlink_rename_chain_batch(ctx, h, loc, name);
	else
		return netlink_rename_chain_compat(ctx, h, loc, name);
}

static int netlink_del_chain_compat(struct netlink_ctx *ctx,
				    const struct handle *h,
				    const struct location *loc)
{
	struct nftnl_chain *nlc;
	int err;

	nlc = alloc_nftnl_chain(h);
	netlink_dump_chain(nlc, ctx);
	err = mnl_nft_chain_delete(ctx->nf_sock, nlc, 0, ctx->seqnum);
	nftnl_chain_free(nlc);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not delete chain: %s",
				 strerror(errno));
	return err;
}

static int netlink_del_chain_batch(struct netlink_ctx *ctx,
				   const struct handle *h,
				   const struct location *loc)
{
	struct nftnl_chain *nlc;
	int err;

	nlc = alloc_nftnl_chain(h);
	netlink_dump_chain(nlc, ctx);
	err = mnl_nft_chain_batch_del(nlc, ctx->batch, 0, ctx->seqnum);
	nftnl_chain_free(nlc);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not delete chain: %s",
				 strerror(errno));
	return err;
}

int netlink_delete_chain(struct netlink_ctx *ctx, const struct handle *h,
			 const struct location *loc)
{
	if (ctx->batch_supported)
		return netlink_del_chain_batch(ctx, h, loc);
	else
		return netlink_del_chain_compat(ctx, h, loc);
}

static struct chain *netlink_delinearize_chain(struct netlink_ctx *ctx,
					       const struct nftnl_chain *nlc)
{
	struct chain *chain;

	chain = chain_alloc(nftnl_chain_get_str(nlc, NFTNL_CHAIN_NAME));
	chain->handle.family =
		nftnl_chain_get_u32(nlc, NFTNL_CHAIN_FAMILY);
	chain->handle.table  =
		xstrdup(nftnl_chain_get_str(nlc, NFTNL_CHAIN_TABLE));
	chain->handle.handle.id =
		nftnl_chain_get_u64(nlc, NFTNL_CHAIN_HANDLE);

	if (nftnl_chain_is_set(nlc, NFTNL_CHAIN_HOOKNUM) &&
	    nftnl_chain_is_set(nlc, NFTNL_CHAIN_PRIO) &&
	    nftnl_chain_is_set(nlc, NFTNL_CHAIN_TYPE) &&
	    nftnl_chain_is_set(nlc, NFTNL_CHAIN_POLICY)) {
		chain->hooknum       =
			nftnl_chain_get_u32(nlc, NFTNL_CHAIN_HOOKNUM);
		chain->hookstr       =
			hooknum2str(chain->handle.family, chain->hooknum);
		chain->priority      =
			nftnl_chain_get_s32(nlc, NFTNL_CHAIN_PRIO);
		chain->type          =
			xstrdup(nftnl_chain_get_str(nlc, NFTNL_CHAIN_TYPE));
		chain->policy          =
			nftnl_chain_get_u32(nlc, NFTNL_CHAIN_POLICY);
		if (nftnl_chain_is_set(nlc, NFTNL_CHAIN_DEV)) {
			chain->dev	=
				xstrdup(nftnl_chain_get_str(nlc, NFTNL_CHAIN_DEV));
		}
		chain->flags        |= CHAIN_F_BASECHAIN;
	}

	return chain;
}

static int list_chain_cb(struct nftnl_chain *nlc, void *arg)
{
	struct netlink_ctx *ctx = arg;
	const struct handle *h = ctx->data;
	const char *table;
	const char *name;
	struct chain *chain;
	uint32_t family;

	table  = nftnl_chain_get_str(nlc, NFTNL_CHAIN_TABLE);
	name   = nftnl_chain_get_str(nlc, NFTNL_CHAIN_NAME);
	family = nftnl_chain_get_u32(nlc, NFTNL_CHAIN_FAMILY);

	if (h->family != family || strcmp(table, h->table) != 0)
		return 0;
	if (h->chain && strcmp(name, h->chain) != 0)
		return 0;

	chain = netlink_delinearize_chain(ctx, nlc);
	list_add_tail(&chain->list, &ctx->list);

	return 0;
}

int netlink_list_chains(struct netlink_ctx *ctx, const struct handle *h,
			const struct location *loc)
{
	struct nftnl_chain_list *chain_cache;
	struct chain *chain;

	chain_cache = mnl_nft_chain_dump(ctx->nf_sock, h->family, ctx->seqnum);
	if (chain_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return 0;
	}

	ctx->data = h;
	nftnl_chain_list_foreach(chain_cache, list_chain_cb, ctx);
	nftnl_chain_list_free(chain_cache);

	/* Caller wants all existing chains */
	if (h->chain == NULL)
		return 0;

	/* Check if this chain exists, otherwise return an error */
	list_for_each_entry(chain, &ctx->list, list) {
		if (strcmp(chain->handle.chain, h->chain) == 0)
			return 0;
	}

	return netlink_io_error(ctx, NULL,
				"Could not find chain `%s' in table `%s': %s",
				h->chain, h->table,
				strerror(ENOENT));
}

int netlink_flush_chain(struct netlink_ctx *ctx, const struct handle *h,
			const struct location *loc)
{
	return netlink_del_rule_batch(ctx, h, loc);
}

static int netlink_add_table_compat(struct netlink_ctx *ctx,
				    const struct handle *h,
				    const struct location *loc,
				    const struct table *table, uint32_t flags)
{
	struct nftnl_table *nlt;
	int err;

	nlt = alloc_nftnl_table(h);
	err = mnl_nft_table_add(ctx->nf_sock, nlt, flags, ctx->seqnum);
	nftnl_table_free(nlt);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not add table: %s",
				 strerror(errno));
	return err;
}

static int netlink_add_table_batch(struct netlink_ctx *ctx,
				   const struct handle *h,
				   const struct location *loc,
				   const struct table *table, uint32_t flags)
{
	struct nftnl_table *nlt;
	int err;

	nlt = alloc_nftnl_table(h);
	if (table != NULL)
		nftnl_table_set_u32(nlt, NFTNL_TABLE_FLAGS, table->flags);
	else
		nftnl_table_set_u32(nlt, NFTNL_TABLE_FLAGS, 0);

	err = mnl_nft_table_batch_add(nlt, ctx->batch, flags, ctx->seqnum);
	nftnl_table_free(nlt);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not add table: %s",
				 strerror(errno));
	return err;
}

int netlink_add_table(struct netlink_ctx *ctx, const struct handle *h,
		      const struct location *loc,
		      const struct table *table, uint32_t flags)
{
	if (ctx->batch_supported)
		return netlink_add_table_batch(ctx, h, loc, table, flags);
	else
		return netlink_add_table_compat(ctx, h, loc, table, flags);
}

static int netlink_del_table_compat(struct netlink_ctx *ctx,
				    const struct handle *h,
				    const struct location *loc)
{
	struct nftnl_table *nlt;
	int err;

	nlt = alloc_nftnl_table(h);
	err = mnl_nft_table_delete(ctx->nf_sock, nlt, 0, ctx->seqnum);
	nftnl_table_free(nlt);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not delete table: %s",
				 strerror(errno));
	return err;
}

static int netlink_del_table_batch(struct netlink_ctx *ctx,
				   const struct handle *h,
				   const struct location *loc)
{
	struct nftnl_table *nlt;
	int err;

	nlt = alloc_nftnl_table(h);
	err = mnl_nft_table_batch_del(nlt, ctx->batch, 0, ctx->seqnum);
	nftnl_table_free(nlt);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not delete table: %s",
				 strerror(errno));
	return err;
}

int netlink_delete_table(struct netlink_ctx *ctx, const struct handle *h,
			 const struct location *loc)
{
	if (ctx->batch_supported)
		return netlink_del_table_batch(ctx, h, loc);
	else
		return netlink_del_table_compat(ctx, h, loc);
}

static struct table *netlink_delinearize_table(struct netlink_ctx *ctx,
					       const struct nftnl_table *nlt)
{
	struct table *table;

	table = table_alloc();
	table->handle.family = nftnl_table_get_u32(nlt, NFTNL_TABLE_FAMILY);
	table->handle.table  = xstrdup(nftnl_table_get_str(nlt, NFTNL_TABLE_NAME));
	table->flags	     = nftnl_table_get_u32(nlt, NFTNL_TABLE_FLAGS);

	return table;
}

static int list_table_cb(struct nftnl_table *nlt, void *arg)
{
	struct netlink_ctx *ctx = arg;
	struct table *table;

	table = netlink_delinearize_table(ctx, nlt);
	list_add_tail(&table->list, &ctx->list);

	return 0;
}

int netlink_list_tables(struct netlink_ctx *ctx, const struct handle *h,
			const struct location *loc)
{
	struct nftnl_table_list *table_cache;

	table_cache = mnl_nft_table_dump(ctx->nf_sock, h->family, ctx->seqnum);
	if (table_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return 0;
	}

	nftnl_table_list_foreach(table_cache, list_table_cb, ctx);
	nftnl_table_list_free(table_cache);
	return 0;
}

int netlink_list_table(struct netlink_ctx *ctx, const struct handle *h,
		       const struct location *loc)
{
	return netlink_list_rules(ctx, h, loc);
}

int netlink_flush_table(struct netlink_ctx *ctx, const struct handle *h,
			const struct location *loc)
{
	return netlink_flush_rules(ctx, h, loc);
}

static enum nft_data_types dtype_map_to_kernel(const struct datatype *dtype)
{
	switch (dtype->type) {
	case TYPE_VERDICT:
		return NFT_DATA_VERDICT;
	default:
		return dtype->type;
	}
}

static const struct datatype *dtype_map_from_kernel(enum nft_data_types type)
{
	switch (type) {
	case NFT_DATA_VERDICT:
		return &verdict_type;
	default:
		if (type & ~TYPE_MASK)
			return concat_type_alloc(type);
		return datatype_lookup(type);
	}
}

void netlink_dump_set(const struct nftnl_set *nls, struct netlink_ctx *ctx)
{
	FILE *fp = ctx->octx->output_fp;

	if (!(ctx->debug_mask & DEBUG_NETLINK) || !fp)
		return;

	nftnl_set_fprintf(fp, nls, 0, 0);
	fprintf(fp, "\n");
}

static int set_parse_udata_cb(const struct nftnl_udata *attr, void *data)
{
	const struct nftnl_udata **tb = data;
	uint8_t type = nftnl_udata_type(attr);
	uint8_t len = nftnl_udata_len(attr);

	switch (type) {
	case UDATA_SET_KEYBYTEORDER:
	case UDATA_SET_DATABYTEORDER:
		if (len != sizeof(uint32_t))
			return -1;
		break;
	default:
		return 0;
	}
	tb[type] = attr;
	return 0;
}

static struct set *netlink_delinearize_set(struct netlink_ctx *ctx,
					   const struct nftnl_set *nls)
{
	const struct nftnl_udata *ud[UDATA_SET_MAX + 1] = {};
	uint32_t flags, key, data, data_len, objtype = 0;
	enum byteorder keybyteorder = BYTEORDER_INVALID;
	enum byteorder databyteorder = BYTEORDER_INVALID;
	const struct datatype *keytype, *datatype;
	const char *udata;
	struct set *set;
	uint32_t ulen;

	if (nftnl_set_is_set(nls, NFTNL_SET_USERDATA)) {
		udata = nftnl_set_get_data(nls, NFTNL_SET_USERDATA, &ulen);
		if (nftnl_udata_parse(udata, ulen, set_parse_udata_cb, ud) < 0) {
			netlink_io_error(ctx, NULL, "Cannot parse userdata");
			return NULL;
		}

		if (ud[UDATA_SET_KEYBYTEORDER])
			keybyteorder =
				nftnl_udata_get_u32(ud[UDATA_SET_KEYBYTEORDER]);
		if (ud[UDATA_SET_DATABYTEORDER])
			databyteorder =
				nftnl_udata_get_u32(ud[UDATA_SET_DATABYTEORDER]);
	}

	key = nftnl_set_get_u32(nls, NFTNL_SET_KEY_TYPE);
	keytype = dtype_map_from_kernel(key);
	if (keytype == NULL) {
		netlink_io_error(ctx, NULL, "Unknown data type in set key %u",
				 key);
		return NULL;
	}

	flags = nftnl_set_get_u32(nls, NFTNL_SET_FLAGS);
	if (flags & NFT_SET_MAP) {
		data = nftnl_set_get_u32(nls, NFTNL_SET_DATA_TYPE);
		datatype = dtype_map_from_kernel(data);
		if (datatype == NULL) {
			netlink_io_error(ctx, NULL,
					 "Unknown data type in set key %u",
					 data);
			return NULL;
		}
	} else
		datatype = NULL;

	if (flags & NFT_SET_OBJECT) {
		objtype = nftnl_set_get_u32(nls, NFTNL_SET_OBJ_TYPE);
		datatype = &string_type;
	}

	set = set_alloc(&netlink_location);
	set->handle.family = nftnl_set_get_u32(nls, NFTNL_SET_FAMILY);
	set->handle.table  = xstrdup(nftnl_set_get_str(nls, NFTNL_SET_TABLE));
	set->handle.set    = xstrdup(nftnl_set_get_str(nls, NFTNL_SET_NAME));

	set->key     = constant_expr_alloc(&netlink_location,
					   set_datatype_alloc(keytype, keybyteorder),
					   keybyteorder,
					   nftnl_set_get_u32(nls, NFTNL_SET_KEY_LEN) * BITS_PER_BYTE,
					   NULL);
	set->flags   = nftnl_set_get_u32(nls, NFTNL_SET_FLAGS);

	set->objtype = objtype;

	if (datatype)
		set->datatype = set_datatype_alloc(datatype, databyteorder);
	else
		set->datatype = NULL;

	if (nftnl_set_is_set(nls, NFTNL_SET_DATA_LEN)) {
		data_len = nftnl_set_get_u32(nls, NFTNL_SET_DATA_LEN);
		set->datalen = data_len * BITS_PER_BYTE;
	}

	if (nftnl_set_is_set(nls, NFTNL_SET_TIMEOUT))
		set->timeout = nftnl_set_get_u64(nls, NFTNL_SET_TIMEOUT);
	if (nftnl_set_is_set(nls, NFTNL_SET_GC_INTERVAL))
		set->gc_int  = nftnl_set_get_u32(nls, NFTNL_SET_GC_INTERVAL);

	if (nftnl_set_is_set(nls, NFTNL_SET_POLICY))
		set->policy = nftnl_set_get_u32(nls, NFTNL_SET_POLICY);

	if (nftnl_set_is_set(nls, NFTNL_SET_DESC_SIZE))
		set->desc.size = nftnl_set_get_u32(nls, NFTNL_SET_DESC_SIZE);

	return set;
}

static int netlink_add_set_compat(struct netlink_ctx *ctx,
				  const struct handle *h, struct set *set,
				  uint32_t flags)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);
	nftnl_set_set_u32(nls, NFTNL_SET_FLAGS, set->flags);
	nftnl_set_set_u32(nls, NFTNL_SET_KEY_TYPE,
			  dtype_map_to_kernel(set->key->dtype));
	nftnl_set_set_u32(nls, NFTNL_SET_KEY_LEN,
			  div_round_up(set->key->len, BITS_PER_BYTE));
	if (set->flags & NFT_SET_MAP) {
		nftnl_set_set_u32(nls, NFTNL_SET_DATA_TYPE,
				  dtype_map_to_kernel(set->datatype));
		nftnl_set_set_u32(nls, NFTNL_SET_DATA_LEN,
				  set->datalen / BITS_PER_BYTE);
	}
	netlink_dump_set(nls, ctx);

	err = mnl_nft_set_add(ctx->nf_sock, nls, NLM_F_ECHO | flags,
			      ctx->seqnum);
	if (err < 0)
		netlink_io_error(ctx, &set->location, "Could not add set: %s",
				 strerror(errno));

	set->handle.set = xstrdup(nftnl_set_get_str(nls, NFTNL_SET_NAME));
	nftnl_set_free(nls);

	return err;
}

static int netlink_add_set_batch(struct netlink_ctx *ctx,
				 const struct handle *h, struct set *set,
				 uint32_t flags)
{
	struct nftnl_udata_buf *udbuf;
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);
	nftnl_set_set_u32(nls, NFTNL_SET_FLAGS, set->flags);
	nftnl_set_set_u32(nls, NFTNL_SET_KEY_TYPE,
			  dtype_map_to_kernel(set->key->dtype));
	nftnl_set_set_u32(nls, NFTNL_SET_KEY_LEN,
			  div_round_up(set->key->len, BITS_PER_BYTE));
	if (set->flags & NFT_SET_MAP) {
		nftnl_set_set_u32(nls, NFTNL_SET_DATA_TYPE,
				  dtype_map_to_kernel(set->datatype));
		nftnl_set_set_u32(nls, NFTNL_SET_DATA_LEN,
				  set->datalen / BITS_PER_BYTE);
	}
	if (set->flags & NFT_SET_OBJECT)
		nftnl_set_set_u32(nls, NFTNL_SET_OBJ_TYPE, set->objtype);

	if (set->timeout)
		nftnl_set_set_u64(nls, NFTNL_SET_TIMEOUT, set->timeout);
	if (set->gc_int)
		nftnl_set_set_u32(nls, NFTNL_SET_GC_INTERVAL, set->gc_int);

	nftnl_set_set_u32(nls, NFTNL_SET_ID, set->handle.set_id);

	if (!(set->flags & NFT_SET_CONSTANT)) {
		if (set->policy != NFT_SET_POL_PERFORMANCE)
			nftnl_set_set_u32(nls, NFTNL_SET_POLICY, set->policy);

		if (set->desc.size != 0)
			nftnl_set_set_u32(nls, NFTNL_SET_DESC_SIZE,
					  set->desc.size);
	} else if (set->init) {
		nftnl_set_set_u32(nls, NFTNL_SET_DESC_SIZE, set->init->size);
	}

	udbuf = nftnl_udata_buf_alloc(NFT_USERDATA_MAXLEN);
	if (!udbuf)
		memory_allocation_error();
	if (!nftnl_udata_put_u32(udbuf, UDATA_SET_KEYBYTEORDER,
				 set->key->byteorder))
		memory_allocation_error();

	if (set->flags & NFT_SET_MAP &&
	    !nftnl_udata_put_u32(udbuf, UDATA_SET_DATABYTEORDER,
				 set->datatype->byteorder))
		memory_allocation_error();

	nftnl_set_set_data(nls, NFTNL_SET_USERDATA, nftnl_udata_buf_data(udbuf),
			   nftnl_udata_buf_len(udbuf));
	nftnl_udata_buf_free(udbuf);

	netlink_dump_set(nls, ctx);

	err = mnl_nft_set_batch_add(nls, ctx->batch, flags, ctx->seqnum);
	if (err < 0)
		netlink_io_error(ctx, &set->location, "Could not add set: %s",
				 strerror(errno));
	nftnl_set_free(nls);

	return err;
}

int netlink_add_set(struct netlink_ctx *ctx, const struct handle *h,
		    struct set *set, uint32_t flags)
{
	if (ctx->batch_supported)
		return netlink_add_set_batch(ctx, h, set, flags);
	else
		return netlink_add_set_compat(ctx, h, set, flags);
}

static int netlink_del_set_compat(struct netlink_ctx *ctx,
				  const struct handle *h,
				  const struct location *loc)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);
	err = mnl_nft_set_delete(ctx->nf_sock, nls, 0, ctx->seqnum);
	nftnl_set_free(nls);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not delete set: %s",
				 strerror(errno));
	return err;
}

static int netlink_del_set_batch(struct netlink_ctx *ctx,
				 const struct handle *h,
				 const struct location *loc)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);
	err = mnl_nft_set_batch_del(nls, ctx->batch, 0, ctx->seqnum);
	nftnl_set_free(nls);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not delete set: %s",
				 strerror(errno));
	return err;
}

int netlink_delete_set(struct netlink_ctx *ctx, const struct handle *h,
		       const struct location *loc)
{
	if (ctx->batch_supported)
		return netlink_del_set_batch(ctx, h, loc);
	else
		return netlink_del_set_compat(ctx, h, loc);
}

static int list_set_cb(struct nftnl_set *nls, void *arg)
{
	struct netlink_ctx *ctx = arg;
	struct set *set;

	set = netlink_delinearize_set(ctx, nls);
	if (set == NULL)
		return -1;
	list_add_tail(&set->list, &ctx->list);
	return 0;
}

int netlink_list_sets(struct netlink_ctx *ctx, const struct handle *h,
		      const struct location *loc)
{
	struct nftnl_set_list *set_cache;
	int err;

	set_cache = mnl_nft_set_dump(ctx->nf_sock, h->family, h->table,
				     ctx->seqnum);
	if (set_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return 0;
	}

	err = nftnl_set_list_foreach(set_cache, list_set_cb, ctx);
	nftnl_set_list_free(set_cache);
	return err;
}

static void alloc_setelem_cache(const struct expr *set, struct nftnl_set *nls)
{
	struct nftnl_set_elem *nlse;
	const struct expr *expr;

	list_for_each_entry(expr, &set->expressions, list) {
		nlse = alloc_nftnl_setelem(set, expr);
		nftnl_set_elem_add(nls, nlse);
	}
}

static int netlink_add_setelems_batch(struct netlink_ctx *ctx,
				      const struct handle *h,
				      const struct expr *expr, uint32_t flags)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);
	alloc_setelem_cache(expr, nls);
	netlink_dump_set(nls, ctx);

	err = mnl_nft_setelem_batch_add(nls, ctx->batch, flags, ctx->seqnum);
	nftnl_set_free(nls);
	if (err < 0)
		netlink_io_error(ctx, &expr->location,
				 "Could not add set elements: %s",
				 strerror(errno));
	return err;
}

static int netlink_add_setelems_compat(struct netlink_ctx *ctx,
				       const struct handle *h,
				       const struct expr *expr, uint32_t flags)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);
	alloc_setelem_cache(expr, nls);
	netlink_dump_set(nls, ctx);

	err = mnl_nft_setelem_add(ctx->nf_sock, nls, flags, ctx->seqnum);
	nftnl_set_free(nls);
	if (err < 0)
		netlink_io_error(ctx, &expr->location,
				 "Could not add set elements: %s",
				 strerror(errno));
	return err;
}

int netlink_add_setelems(struct netlink_ctx *ctx, const struct handle *h,
			 const struct expr *expr, uint32_t flags)
{
	if (ctx->batch_supported)
		return netlink_add_setelems_batch(ctx, h, expr, flags);
	else
		return netlink_add_setelems_compat(ctx, h, expr, flags);
}

static int netlink_del_setelems_batch(struct netlink_ctx *ctx,
				      const struct handle *h,
				      const struct expr *expr)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);
	if (expr)
		alloc_setelem_cache(expr, nls);
	netlink_dump_set(nls, ctx);

	err = mnl_nft_setelem_batch_del(nls, ctx->batch, 0, ctx->seqnum);
	nftnl_set_free(nls);
	if (err < 0)
		netlink_io_error(ctx, &expr->location,
				 "Could not delete set elements: %s",
				 strerror(errno));
	return err;
}

static int netlink_del_setelems_compat(struct netlink_ctx *ctx,
				       const struct handle *h,
				       const struct expr *expr)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);
	alloc_setelem_cache(expr, nls);
	netlink_dump_set(nls, ctx);

	err = mnl_nft_setelem_delete(ctx->nf_sock, nls, 0, ctx->seqnum);
	nftnl_set_free(nls);
	if (err < 0)
		netlink_io_error(ctx, &expr->location,
				 "Could not delete set elements: %s",
				 strerror(errno));
	return err;
}

int netlink_flush_setelems(struct netlink_ctx *ctx, const struct handle *h,
			   const struct location *loc)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);
	netlink_dump_set(nls, ctx);

	err = mnl_nft_setelem_batch_flush(nls, ctx->batch, 0, ctx->seqnum);
	nftnl_set_free(nls);
	if (err < 0)
		netlink_io_error(ctx, loc,
				 "Could not flush set elements: %s",
				 strerror(errno));
	return err;
}

static struct expr *netlink_parse_concat_elem(const struct datatype *dtype,
					      struct expr *data)
{
	const struct datatype *subtype;
	struct expr *concat, *expr;
	int off = dtype->subtypes;

	concat = concat_expr_alloc(&data->location);
	while (off > 0) {
		subtype = concat_subtype_lookup(dtype->type, --off);

		expr		= constant_expr_splice(data, subtype->size);
		expr->dtype     = subtype;
		expr->byteorder = subtype->byteorder;

		if (expr->byteorder == BYTEORDER_HOST_ENDIAN)
			mpz_switch_byteorder(expr->value, expr->len / BITS_PER_BYTE);

		if (expr->dtype->basetype != NULL &&
		    expr->dtype->basetype->type == TYPE_BITMASK)
			expr = bitmask_expr_to_binops(expr);

		compound_expr_add(concat, expr);
		data->len -= netlink_padding_len(expr->len);
	}
	expr_free(data);

	return concat;
}

static int set_elem_parse_udata_cb(const struct nftnl_udata *attr, void *data)
{
	const struct nftnl_udata **tb = data;
	unsigned char *value = nftnl_udata_get(attr);
	uint8_t type = nftnl_udata_type(attr);
	uint8_t len = nftnl_udata_len(attr);

	switch (type) {
	case UDATA_SET_ELEM_COMMENT:
		if (value[len - 1] != '\0')
			return -1;
		break;
	case UDATA_SET_ELEM_FLAGS:
		if (len != sizeof(uint32_t))
			return -1;
		break;
	default:
		return 0;
	}
	tb[type] = attr;
	return 0;
}

static void set_elem_parse_udata(struct nftnl_set_elem *nlse,
				 struct expr *expr)
{
	const struct nftnl_udata *ud[UDATA_SET_ELEM_MAX + 1] = {};
	const void *data;
	uint32_t len;

	data = nftnl_set_elem_get(nlse, NFTNL_SET_ELEM_USERDATA, &len);
	if (nftnl_udata_parse(data, len, set_elem_parse_udata_cb, ud))
		return;

	if (ud[UDATA_SET_ELEM_COMMENT])
		expr->comment =
			xstrdup(nftnl_udata_get(ud[UDATA_SET_ELEM_COMMENT]));
	if (ud[UDATA_SET_ELEM_FLAGS])
		expr->elem_flags = nftnl_udata_get_u32(ud[UDATA_SET_ELEM_FLAGS]);
}

static int netlink_delinearize_setelem(struct nftnl_set_elem *nlse,
				       const struct set *set,
				       struct nft_cache *cache)
{
	struct nft_data_delinearize nld;
	struct expr *expr, *key, *data;
	uint32_t flags = 0;

	nld.value =
		nftnl_set_elem_get(nlse, NFTNL_SET_ELEM_KEY, &nld.len);
	if (nftnl_set_elem_is_set(nlse, NFTNL_SET_ELEM_FLAGS))
		flags = nftnl_set_elem_get_u32(nlse, NFTNL_SET_ELEM_FLAGS);

	key = netlink_alloc_value(&netlink_location, &nld);
	key->dtype	= set->key->dtype;
	key->byteorder	= set->key->byteorder;
	if (set->key->dtype->subtypes)
		key = netlink_parse_concat_elem(set->key->dtype, key);

	if (!(set->flags & NFT_SET_INTERVAL) &&
	    key->byteorder == BYTEORDER_HOST_ENDIAN)
		mpz_switch_byteorder(key->value, key->len / BITS_PER_BYTE);

	if (key->dtype->basetype != NULL &&
	    key->dtype->basetype->type == TYPE_BITMASK)
		key = bitmask_expr_to_binops(key);

	expr = set_elem_expr_alloc(&netlink_location, key);
	if (nftnl_set_elem_is_set(nlse, NFTNL_SET_ELEM_TIMEOUT))
		expr->timeout	 = nftnl_set_elem_get_u64(nlse, NFTNL_SET_ELEM_TIMEOUT);
	if (nftnl_set_elem_is_set(nlse, NFTNL_SET_ELEM_EXPIRATION))
		expr->expiration = nftnl_set_elem_get_u64(nlse, NFTNL_SET_ELEM_EXPIRATION);
	if (nftnl_set_elem_is_set(nlse, NFTNL_SET_ELEM_USERDATA))
		set_elem_parse_udata(nlse, expr);
	if (nftnl_set_elem_is_set(nlse, NFTNL_SET_ELEM_EXPR)) {
		const struct nftnl_expr *nle;

		nle = nftnl_set_elem_get(nlse, NFTNL_SET_ELEM_EXPR, NULL);
		expr->stmt = netlink_parse_set_expr(set, cache, nle);
	}
	if (flags & NFT_SET_ELEM_INTERVAL_END)
		expr->flags |= EXPR_F_INTERVAL_END;

	if (set->flags & NFT_SET_MAP) {
		if (nftnl_set_elem_is_set(nlse, NFTNL_SET_ELEM_DATA)) {
			nld.value = nftnl_set_elem_get(nlse, NFTNL_SET_ELEM_DATA,
						       &nld.len);
		} else if (nftnl_set_elem_is_set(nlse, NFTNL_SET_ELEM_CHAIN)) {
			nld.chain = nftnl_set_elem_get_str(nlse, NFTNL_SET_ELEM_CHAIN);
			nld.verdict = nftnl_set_elem_get_u32(nlse, NFTNL_SET_ELEM_VERDICT);
		} else if (nftnl_set_elem_is_set(nlse, NFTNL_SET_ELEM_VERDICT)) {
			nld.verdict = nftnl_set_elem_get_u32(nlse, NFTNL_SET_ELEM_VERDICT);
		} else
			goto out;

		data = netlink_alloc_data(&netlink_location, &nld,
					  set->datatype->type == TYPE_VERDICT ?
					  NFT_REG_VERDICT : NFT_REG_1);
		data->dtype = set->datatype;
		data->byteorder = set->datatype->byteorder;
		if (data->byteorder == BYTEORDER_HOST_ENDIAN)
			mpz_switch_byteorder(data->value, data->len / BITS_PER_BYTE);

		expr = mapping_expr_alloc(&netlink_location, expr, data);
	}
	if (set->flags & NFT_SET_OBJECT) {
		nld.value = nftnl_set_elem_get(nlse, NFTNL_SET_ELEM_OBJREF,
					       &nld.len);
		data = netlink_alloc_value(&netlink_location, &nld);
		data->dtype = &string_type;
		data->byteorder = BYTEORDER_HOST_ENDIAN;
		mpz_switch_byteorder(data->value, data->len / BITS_PER_BYTE);
		expr = mapping_expr_alloc(&netlink_location, expr, data);
	}
out:
	compound_expr_add(set->init, expr);
	return 0;
}

int netlink_delete_setelems(struct netlink_ctx *ctx, const struct handle *h,
			    const struct expr *expr)
{
	if (ctx->batch_supported)
		return netlink_del_setelems_batch(ctx, h, expr);
	else
		return netlink_del_setelems_compat(ctx, h, expr);
}

static int list_setelem_cb(struct nftnl_set_elem *nlse, void *arg)
{
	struct netlink_ctx *ctx = arg;
	return netlink_delinearize_setelem(nlse, ctx->set, ctx->cache);
}

int netlink_get_setelems(struct netlink_ctx *ctx, const struct handle *h,
			 const struct location *loc, struct set *set)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);

	err = mnl_nft_setelem_get(ctx->nf_sock, nls, ctx->seqnum);
	if (err < 0) {
		nftnl_set_free(nls);
		if (errno == EINTR)
			return -1;

		goto out;
	}

	ctx->set = set;
	set->init = set_expr_alloc(loc, set);
	nftnl_set_elem_foreach(nls, list_setelem_cb, ctx);

	if (!(set->flags & NFT_SET_INTERVAL))
		list_expr_sort(&ctx->set->init->expressions);

	nftnl_set_free(nls);
	ctx->set = NULL;

	if (set->flags & NFT_SET_INTERVAL)
		interval_map_decompose(set->init);
out:
	if (err < 0)
		netlink_io_error(ctx, loc, "Could not receive set elements: %s",
				 strerror(errno));
	return err;
}

void netlink_dump_obj(struct nftnl_obj *nln, struct netlink_ctx *ctx)
{
	FILE *fp = ctx->octx->output_fp;

	if (!(ctx->debug_mask & DEBUG_NETLINK) || !fp)
		return;

	nftnl_obj_fprintf(fp, nln, 0, 0);
	fprintf(fp, "\n");
}

int netlink_add_obj(struct netlink_ctx *ctx, const struct handle *h,
		    struct obj *obj, uint32_t flags)
{
	struct nftnl_obj *nlo;
	int err;

	nlo = alloc_nftnl_obj(h, obj);
	netlink_dump_obj(nlo, ctx);

	err = mnl_nft_obj_batch_add(nlo, ctx->batch, flags, ctx->seqnum);
	if (err < 0)
		netlink_io_error(ctx, &obj->location, "Could not add %s: %s",
				 obj_type_name(obj->type), strerror(errno));
	nftnl_obj_free(nlo);

	return err;
}

int netlink_delete_obj(struct netlink_ctx *ctx, const struct handle *h,
		       struct location *loc, uint32_t type)
{
	struct nftnl_obj *nlo;
	int err;

	nlo = __alloc_nftnl_obj(h, type);
	netlink_dump_obj(nlo, ctx);

	err = mnl_nft_obj_batch_del(nlo, ctx->batch, 0, ctx->seqnum);
	if (err < 0)
		netlink_io_error(ctx, loc, "Could not delete %s: %s",
				 obj_type_name(type), strerror(errno));
	nftnl_obj_free(nlo);

	return err;
}

static struct obj *netlink_delinearize_obj(struct netlink_ctx *ctx,
					   struct nftnl_obj *nlo)
{
	struct obj *obj;
	uint32_t type;

	obj = obj_alloc(&netlink_location);
	obj->handle.family = nftnl_obj_get_u32(nlo, NFTNL_OBJ_FAMILY);
	obj->handle.table =
		xstrdup(nftnl_obj_get_str(nlo, NFTNL_OBJ_TABLE));
	obj->handle.obj =
		xstrdup(nftnl_obj_get_str(nlo, NFTNL_OBJ_NAME));

	type = nftnl_obj_get_u32(nlo, NFTNL_OBJ_TYPE);
	switch (type) {
	case NFT_OBJECT_COUNTER:
		obj->counter.packets =
			nftnl_obj_get_u64(nlo, NFTNL_OBJ_CTR_PKTS);
		obj->counter.bytes =
			nftnl_obj_get_u64(nlo, NFTNL_OBJ_CTR_BYTES);
		break;
	case NFT_OBJECT_QUOTA:
		obj->quota.bytes =
			nftnl_obj_get_u64(nlo, NFTNL_OBJ_QUOTA_BYTES);
		obj->quota.used =
			nftnl_obj_get_u64(nlo, NFTNL_OBJ_QUOTA_CONSUMED);
		obj->quota.flags =
			nftnl_obj_get_u32(nlo, NFTNL_OBJ_QUOTA_FLAGS);
		break;
	case NFT_OBJECT_CT_HELPER:
		snprintf(obj->ct_helper.name, sizeof(obj->ct_helper.name), "%s",
			 nftnl_obj_get_str(nlo, NFTNL_OBJ_CT_HELPER_NAME));
		obj->ct_helper.l3proto = nftnl_obj_get_u16(nlo, NFTNL_OBJ_CT_HELPER_L3PROTO);
		obj->ct_helper.l4proto = nftnl_obj_get_u8(nlo, NFTNL_OBJ_CT_HELPER_L4PROTO);
		break;
	case NFT_OBJECT_LIMIT:
		obj->limit.rate =
			nftnl_obj_get_u64(nlo, NFTNL_OBJ_LIMIT_RATE);
		obj->limit.unit =
			nftnl_obj_get_u64(nlo, NFTNL_OBJ_LIMIT_UNIT);
		obj->limit.burst =
			nftnl_obj_get_u32(nlo, NFTNL_OBJ_LIMIT_BURST);
		obj->limit.type =
			nftnl_obj_get_u32(nlo, NFTNL_OBJ_LIMIT_TYPE);
		obj->limit.flags =
			nftnl_obj_get_u32(nlo, NFTNL_OBJ_LIMIT_FLAGS);
		break;
	}
	obj->type = type;

	return obj;
}

static int list_obj_cb(struct nftnl_obj *nls, void *arg)
{
	struct netlink_ctx *ctx = arg;
	struct obj *obj;

	obj = netlink_delinearize_obj(ctx, nls);
	if (obj == NULL)
		return -1;
	list_add_tail(&obj->list, &ctx->list);
	return 0;
}

int netlink_list_objs(struct netlink_ctx *ctx, const struct handle *h,
		      const struct location *loc)
{
	struct nftnl_obj_list *obj_cache;
	int err;

	obj_cache = mnl_nft_obj_dump(ctx->nf_sock, h->family, ctx->seqnum,
				     h->table, NULL, 0, true, false);
	if (obj_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return 0;
	}

	err = nftnl_obj_list_foreach(obj_cache, list_obj_cb, ctx);
	nftnl_obj_list_free(obj_cache);
	return err;
}

int netlink_reset_objs(struct netlink_ctx *ctx, const struct handle *h,
		       const struct location *loc, uint32_t type, bool dump)
{
	struct nftnl_obj_list *obj_cache;
	int err;

	obj_cache = mnl_nft_obj_dump(ctx->nf_sock, h->family, ctx->seqnum,
				     h->table, h->obj, type, dump, true);
	if (obj_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return netlink_io_error(ctx, loc,
					"Could not receive stateful object from kernel: %s",
					strerror(errno));
	}

	err = nftnl_obj_list_foreach(obj_cache, list_obj_cb, ctx);
	nftnl_obj_list_free(obj_cache);
	return err;
}

int netlink_batch_send(struct netlink_ctx *ctx, struct list_head *err_list)
{
	return mnl_batch_talk(ctx, err_list);
}

int netlink_flush_ruleset(struct netlink_ctx *ctx, const struct handle *h,
			  const struct location *loc)
{
	struct nftnl_table *nlt;
	int err;

	if (!ctx->batch_supported)
		return netlink_io_error(ctx, loc, "Operation not supported");

	nlt = alloc_nftnl_table(h);
	err = mnl_nft_table_batch_del(nlt, ctx->batch, 0, ctx->seqnum);
	nftnl_table_free(nlt);

	if (err < 0)
		netlink_io_error(ctx, loc, "Could not flush the ruleset: %s",
				 strerror(errno));
	return err;
}

struct nftnl_ruleset *netlink_dump_ruleset(struct netlink_ctx *ctx,
					 const struct handle *h,
					 const struct location *loc)
{
	struct nftnl_ruleset *rs;

	rs = mnl_nft_ruleset_dump(ctx->nf_sock, h->family, ctx->seqnum);
	if (rs == NULL) {
		if (errno == EINTR)
			return NULL;

		netlink_io_error(ctx, loc, "Could not receive ruleset: %s",
				 strerror(errno));
	}

	return rs;
}

static struct nftnl_table *netlink_table_alloc(const struct nlmsghdr *nlh)
{
	struct nftnl_table *nlt;

	nlt = nftnl_table_alloc();
	if (nlt == NULL)
		memory_allocation_error();
	if (nftnl_table_nlmsg_parse(nlh, nlt) < 0)
		netlink_abi_error();

	return nlt;
}

static struct nftnl_chain *netlink_chain_alloc(const struct nlmsghdr *nlh)
{
	struct nftnl_chain *nlc;

	nlc = nftnl_chain_alloc();
	if (nlc == NULL)
		memory_allocation_error();
	if (nftnl_chain_nlmsg_parse(nlh, nlc) < 0)
		netlink_abi_error();

	return nlc;
}

static struct nftnl_set *netlink_set_alloc(const struct nlmsghdr *nlh)
{
	struct nftnl_set *nls;

	nls = nftnl_set_alloc();
	if (nls == NULL)
		memory_allocation_error();
	if (nftnl_set_nlmsg_parse(nlh, nls) < 0)
		netlink_abi_error();

	return nls;
}

static struct nftnl_set *netlink_setelem_alloc(const struct nlmsghdr *nlh)
{
	struct nftnl_set *nls;

	nls = nftnl_set_alloc();
	if (nls == NULL)
		memory_allocation_error();
	if (nftnl_set_elems_nlmsg_parse(nlh, nls) < 0)
		netlink_abi_error();

	return nls;
}

static struct nftnl_rule *netlink_rule_alloc(const struct nlmsghdr *nlh)
{
	struct nftnl_rule *nlr;

	nlr = nftnl_rule_alloc();
	if (nlr == NULL)
		memory_allocation_error();
	if (nftnl_rule_nlmsg_parse(nlh, nlr) < 0)
		netlink_abi_error();

	return nlr;
}

static struct nftnl_obj *netlink_obj_alloc(const struct nlmsghdr *nlh)
{
	struct nftnl_obj *nlo;

	nlo = nftnl_obj_alloc();
	if (nlo == NULL)
		memory_allocation_error();
	if (nftnl_obj_nlmsg_parse(nlh, nlo) < 0)
		netlink_abi_error();

	return nlo;
}

static uint32_t netlink_msg2nftnl_of(uint32_t msg)
{
	switch (msg) {
	case NFT_MSG_NEWTABLE:
	case NFT_MSG_NEWCHAIN:
	case NFT_MSG_NEWSET:
	case NFT_MSG_NEWSETELEM:
	case NFT_MSG_NEWRULE:
		return NFTNL_OF_EVENT_NEW;
	case NFT_MSG_DELTABLE:
	case NFT_MSG_DELCHAIN:
	case NFT_MSG_DELSET:
	case NFT_MSG_DELSETELEM:
	case NFT_MSG_DELRULE:
		return NFTNL_OF_EVENT_DEL;
	}

	return 0;
}

static void nlr_for_each_set(struct nftnl_rule *nlr,
			     void (*cb)(struct set *s, void *data),
			     void *data, struct nft_cache *cache)
{
	struct nftnl_expr_iter *nlrei;
	struct nftnl_expr *nlre;
	const char *set_name, *table;
	const char *name;
	struct set *s;
	uint32_t family;

	nlrei = nftnl_expr_iter_create(nlr);
	if (nlrei == NULL)
		memory_allocation_error();

	family = nftnl_rule_get_u32(nlr, NFTNL_RULE_FAMILY);
	table = nftnl_rule_get_str(nlr, NFTNL_RULE_TABLE);

	nlre = nftnl_expr_iter_next(nlrei);
	while (nlre != NULL) {
		name = nftnl_expr_get_str(nlre, NFTNL_EXPR_NAME);
		if (strcmp(name, "lookup") != 0)
			goto next;

		set_name = nftnl_expr_get_str(nlre, NFTNL_EXPR_LOOKUP_SET);
		s = set_lookup_global(family, table, set_name, cache);
		if (s == NULL)
			goto next;

		cb(s, data);
next:
		nlre = nftnl_expr_iter_next(nlrei);
	}
	nftnl_expr_iter_destroy(nlrei);
}

static int netlink_events_table_cb(const struct nlmsghdr *nlh, int type,
				   struct netlink_mon_handler *monh)
{
	struct nftnl_table *nlt;
	uint32_t family;

	nlt = netlink_table_alloc(nlh);

	switch (monh->format) {
	case NFTNL_OUTPUT_DEFAULT:
		if (type == NFT_MSG_NEWTABLE) {
			if (nlh->nlmsg_flags & NLM_F_EXCL)
				nft_mon_print(monh, "update table ");
			else
				nft_mon_print(monh, "add table ");
		} else {
			nft_mon_print(monh, "delete table ");
		}

		family = nftnl_table_get_u32(nlt, NFTNL_TABLE_FAMILY);

		nft_mon_print(monh, "%s %s\n", family2str(family),
		       nftnl_table_get_str(nlt, NFTNL_TABLE_NAME));
		break;
	case NFTNL_OUTPUT_XML:
	case NFTNL_OUTPUT_JSON:
		nftnl_table_fprintf(stdout, nlt, monh->format,
				    netlink_msg2nftnl_of(type));
		fprintf(stdout, "\n");
		break;
	}

	nftnl_table_free(nlt);
	return MNL_CB_OK;
}

static int netlink_events_chain_cb(const struct nlmsghdr *nlh, int type,
				   struct netlink_mon_handler *monh)
{
	struct nftnl_chain *nlc;
	struct chain *c;
	uint32_t family;

	nlc = netlink_chain_alloc(nlh);

	switch (monh->format) {
	case NFTNL_OUTPUT_DEFAULT:
		switch (type) {
		case NFT_MSG_NEWCHAIN:
			if (nlh->nlmsg_flags & NLM_F_EXCL)
				nft_mon_print(monh, "update ");
			else
				nft_mon_print(monh, "add ");

			c = netlink_delinearize_chain(monh->ctx, nlc);
			chain_print_plain(c, monh->ctx->octx);
			chain_free(c);
			break;
		case NFT_MSG_DELCHAIN:
			family = nftnl_chain_get_u32(nlc, NFTNL_CHAIN_FAMILY);
			nft_mon_print(monh, "delete chain %s %s %s\n", family2str(family),
			       nftnl_chain_get_str(nlc, NFTNL_CHAIN_TABLE),
			       nftnl_chain_get_str(nlc, NFTNL_CHAIN_NAME));
			break;
		}
		break;
	case NFTNL_OUTPUT_XML:
	case NFTNL_OUTPUT_JSON:
		nftnl_chain_fprintf(stdout, nlc, monh->format,
				    netlink_msg2nftnl_of(type));
		fprintf(stdout, "\n");
		break;
	}

	nftnl_chain_free(nlc);
	return MNL_CB_OK;
}

static int netlink_events_set_cb(const struct nlmsghdr *nlh, int type,
				 struct netlink_mon_handler *monh)
{
	struct nftnl_set *nls;
	struct set *set;
	uint32_t family, flags;

	nls = netlink_set_alloc(nlh);
	flags = nftnl_set_get_u32(nls, NFTNL_SET_FLAGS);
	if (flags & NFT_SET_ANONYMOUS)
		goto out;

	switch (monh->format) {
	case NFTNL_OUTPUT_DEFAULT:
		switch (type) {
		case NFT_MSG_NEWSET:
			nft_mon_print(monh, "add ");
			set = netlink_delinearize_set(monh->ctx, nls);
			if (set == NULL) {
				nftnl_set_free(nls);
				return MNL_CB_ERROR;
			}
			set_print_plain(set, monh->ctx->octx);
			set_free(set);
			nft_mon_print(monh, "\n");
			break;
		case NFT_MSG_DELSET:
			family = nftnl_set_get_u32(nls, NFTNL_SET_FAMILY);
			nft_mon_print(monh, "delete set %s %s %s\n",
			       family2str(family),
			       nftnl_set_get_str(nls, NFTNL_SET_TABLE),
			       nftnl_set_get_str(nls, NFTNL_SET_NAME));
			break;
		}
		break;
	case NFTNL_OUTPUT_XML:
	case NFTNL_OUTPUT_JSON:
		nftnl_set_fprintf(stdout, nls, monh->format,
				netlink_msg2nftnl_of(type));
		fprintf(stdout, "\n");
		break;
	}
out:
	nftnl_set_free(nls);
	return MNL_CB_OK;
}

/* returns true if the event should be ignored (i.e. null element) */
static bool netlink_event_ignore_range_event(struct nftnl_set_elem *nlse)
{
        uint32_t flags = 0;

	if (nftnl_set_elem_is_set(nlse, NFTNL_SET_ELEM_FLAGS))
		flags = nftnl_set_elem_get_u32(nlse, NFTNL_SET_ELEM_FLAGS);
	if (!(flags & NFT_SET_ELEM_INTERVAL_END))
		return false;

	if (nftnl_set_elem_get_u32(nlse, NFTNL_SET_ELEM_KEY) != 0)
		return false;

	return true;
}

static bool set_elem_is_open_interval(struct expr *elem)
{
	switch (elem->ops->type) {
	case EXPR_SET_ELEM:
		return elem->elem_flags & SET_ELEM_F_INTERVAL_OPEN;
	case EXPR_MAPPING:
		return set_elem_is_open_interval(elem->left);
	default:
		return false;
	}
}

/* returns true if the we cached the range element */
static bool netlink_event_range_cache(struct set *cached_set,
				      struct set *dummyset)
{
	struct expr *elem;

	/* not an interval ? */
	if (!(cached_set->flags & NFT_SET_INTERVAL))
		return false;

	/* if cache exists, dummyset must contain the other end of the range */
	if (cached_set->rg_cache) {
		compound_expr_add(dummyset->init, cached_set->rg_cache);
		cached_set->rg_cache = NULL;
		goto out_decompose;
	}

	/* don't cache half-open range elements */
	elem = list_entry(dummyset->init->expressions.prev, struct expr, list);
	if (!set_elem_is_open_interval(elem)) {
		cached_set->rg_cache = expr_clone(elem);
		return true;
	}

out_decompose:
	interval_map_decompose(dummyset->init);
	return false;
}

static int netlink_events_setelem_cb(const struct nlmsghdr *nlh, int type,
				     struct netlink_mon_handler *monh)
{
	struct nftnl_set_elems_iter *nlsei;
	struct nftnl_set_elem *nlse;
	struct nftnl_set *nls;
	struct set *dummyset;
	struct set *set;
	const char *setname, *table;
	uint32_t family;

	nls = netlink_setelem_alloc(nlh);
	table = nftnl_set_get_str(nls, NFTNL_SET_TABLE);
	setname = nftnl_set_get_str(nls, NFTNL_SET_NAME);
	family = nftnl_set_get_u32(nls, NFTNL_SET_FAMILY);

	set = set_lookup_global(family, table, setname, monh->cache);
	if (set == NULL) {
		fprintf(stderr, "W: Received event for an unknown set.");
		goto out;
	}

	switch (monh->format) {
	case NFTNL_OUTPUT_DEFAULT:
		if (set->flags & NFT_SET_ANONYMOUS)
			goto out;

		/* we want to 'delinearize' the set_elem, but don't
		 * modify the original cached set. This path is only
		 * used by named sets, so use a dummy set.
		 */
		dummyset = set_alloc(monh->loc);
		dummyset->key = expr_clone(set->key);
		dummyset->datatype = set->datatype;
		dummyset->flags = set->flags;
		dummyset->init = set_expr_alloc(monh->loc, set);

		nlsei = nftnl_set_elems_iter_create(nls);
		if (nlsei == NULL)
			memory_allocation_error();

		nlse = nftnl_set_elems_iter_next(nlsei);
		while (nlse != NULL) {
			if (netlink_event_ignore_range_event(nlse)) {
				set_free(dummyset);
				nftnl_set_elems_iter_destroy(nlsei);
				goto out;
			}
			if (netlink_delinearize_setelem(nlse, dummyset,
							monh->cache) < 0) {
				set_free(dummyset);
				nftnl_set_elems_iter_destroy(nlsei);
				goto out;
			}
			nlse = nftnl_set_elems_iter_next(nlsei);
		}
		nftnl_set_elems_iter_destroy(nlsei);

		if (netlink_event_range_cache(set, dummyset)) {
			set_free(dummyset);
			goto out;
		}

		switch (type) {
		case NFT_MSG_NEWSETELEM:
			nft_mon_print(monh, "add ");
			break;
		case NFT_MSG_DELSETELEM:
			nft_mon_print(monh, "delete ");
			break;
		default:
			set_free(dummyset);
			goto out;
		}
		nft_mon_print(monh, "element %s %s %s ", family2str(family), table, setname);
		expr_print(dummyset->init, monh->ctx->octx);
		nft_mon_print(monh, "\n");

		set_free(dummyset);
		break;
	case NFTNL_OUTPUT_XML:
	case NFTNL_OUTPUT_JSON:
		nftnl_set_fprintf(stdout, nls, monh->format,
				  netlink_msg2nftnl_of(type));
		fprintf(stdout, "\n");
		break;
	}
out:
	nftnl_set_free(nls);
	return MNL_CB_OK;
}

static int netlink_events_obj_cb(const struct nlmsghdr *nlh, int type,
				 struct netlink_mon_handler *monh)
{
	struct nftnl_obj *nlo;
	uint32_t family;
	struct obj *obj;

	nlo = netlink_obj_alloc(nlh);

	switch (monh->format) {
	case NFTNL_OUTPUT_DEFAULT:
		switch (type) {
		case NFT_MSG_NEWOBJ:
			nft_mon_print(monh, "add ");
			obj = netlink_delinearize_obj(monh->ctx, nlo);
			if (obj == NULL) {
				nftnl_obj_free(nlo);
				return MNL_CB_ERROR;
			}
			obj_print_plain(obj, monh->ctx->octx);
			obj_free(obj);
			nft_mon_print(monh, "\n");
			break;
		case NFT_MSG_DELOBJ:
			family = nftnl_obj_get_u32(nlo, NFTNL_OBJ_FAMILY);
			nft_mon_print(monh, "delete %s %s %s %s\n",
			       obj_type_name(nftnl_obj_get_u32(nlo, NFTNL_OBJ_TYPE)),
			       family2str(family),
			       nftnl_obj_get_str(nlo, NFTNL_OBJ_TABLE),
			       nftnl_obj_get_str(nlo, NFTNL_OBJ_NAME));
			break;
		}
		break;
	case NFTNL_OUTPUT_XML:
	case NFTNL_OUTPUT_JSON:
		nftnl_obj_fprintf(stdout, nlo, monh->format,
				  netlink_msg2nftnl_of(type));
		fprintf(stdout, "\n");
		break;
	}

	nftnl_obj_free(nlo);
	return MNL_CB_OK;
}

static void rule_map_decompose_cb(struct set *s, void *data)
{
	if (s->flags & NFT_SET_INTERVAL)
		interval_map_decompose(s->init);
}

static int netlink_events_rule_cb(const struct nlmsghdr *nlh, int type,
				  struct netlink_mon_handler *monh)
{
	struct nftnl_rule *nlr;
	const char *family;
	const char *table;
	const char *chain;
	struct rule *r;
	uint64_t handle;
	uint32_t fam;

	nlr = netlink_rule_alloc(nlh);
	switch (monh->format) {
	case NFTNL_OUTPUT_DEFAULT:
		fam = nftnl_rule_get_u32(nlr, NFTNL_RULE_FAMILY);
		family = family2str(fam);
		table = nftnl_rule_get_str(nlr, NFTNL_RULE_TABLE);
		chain = nftnl_rule_get_str(nlr, NFTNL_RULE_CHAIN);
		handle = nftnl_rule_get_u64(nlr, NFTNL_RULE_HANDLE);

		switch (type) {
		case NFT_MSG_NEWRULE:
			r = netlink_delinearize_rule(monh->ctx, nlr);
			nlr_for_each_set(nlr, rule_map_decompose_cb, NULL,
					 monh->cache);

			nft_mon_print(monh, "add rule %s %s %s ", family, table, chain);
			rule_print(r, monh->ctx->octx);
			nft_mon_print(monh, "\n");

			rule_free(r);
			break;
		case NFT_MSG_DELRULE:
			nft_mon_print(monh, "delete rule %s %s %s handle %u\n",
			       family, table, chain, (unsigned int)handle);
			break;
		}
		break;
	case NFTNL_OUTPUT_XML:
	case NFTNL_OUTPUT_JSON:
		nftnl_rule_fprintf(stdout, nlr, monh->format,
				 netlink_msg2nftnl_of(type));
		fprintf(stdout, "\n");
		break;
	}

	nftnl_rule_free(nlr);
	return MNL_CB_OK;
}

static void netlink_events_cache_addtable(struct netlink_mon_handler *monh,
					  const struct nlmsghdr *nlh)
{
	struct nftnl_table *nlt;
	struct table *t;

	nlt = netlink_table_alloc(nlh);
	t = netlink_delinearize_table(monh->ctx, nlt);
	nftnl_table_free(nlt);

	table_add_hash(t, monh->cache);
}

static void netlink_events_cache_deltable(struct netlink_mon_handler *monh,
					  const struct nlmsghdr *nlh)
{
	struct nftnl_table *nlt;
	struct table *t;
	struct handle h;

	nlt      = netlink_table_alloc(nlh);
	h.family = nftnl_table_get_u32(nlt, NFTNL_TABLE_FAMILY);
	h.table  = nftnl_table_get_str(nlt, NFTNL_TABLE_NAME);

	t = table_lookup(&h, monh->cache);
	if (t == NULL)
		goto out;

	list_del(&t->list);
	table_free(t);
out:
	nftnl_table_free(nlt);
}

static void netlink_events_cache_addset(struct netlink_mon_handler *monh,
					const struct nlmsghdr *nlh)
{
	struct netlink_ctx set_tmpctx;
	struct nftnl_set *nls;
	struct table *t;
	struct set *s;
	LIST_HEAD(msgs);

	memset(&set_tmpctx, 0, sizeof(set_tmpctx));
	init_list_head(&set_tmpctx.list);
	init_list_head(&msgs);
	set_tmpctx.msgs = &msgs;

	nls = netlink_set_alloc(nlh);
	s = netlink_delinearize_set(&set_tmpctx, nls);
	if (s == NULL)
		goto out;
	s->init = set_expr_alloc(monh->loc, s);

	t = table_lookup(&s->handle, monh->cache);
	if (t == NULL) {
		fprintf(stderr, "W: Unable to cache set: table not found.\n");
		set_free(s);
		goto out;
	}

	set_add_hash(s, t);
out:
	nftnl_set_free(nls);
}

static void netlink_events_cache_addsetelem(struct netlink_mon_handler *monh,
					    const struct nlmsghdr *nlh)
{
	struct nftnl_set_elems_iter *nlsei;
	struct nftnl_set_elem *nlse;
	struct nftnl_set *nls;
	struct set *set;
	const char *table, *setname;
	uint32_t family;

	nls     = netlink_setelem_alloc(nlh);
	family  = nftnl_set_get_u32(nls, NFTNL_SET_FAMILY);
	table   = nftnl_set_get_str(nls, NFTNL_SET_TABLE);
	setname = nftnl_set_get_str(nls, NFTNL_SET_NAME);

	set = set_lookup_global(family, table, setname, monh->cache);
	if (set == NULL) {
		fprintf(stderr,
			"W: Unable to cache set_elem. Set not found.\n");
		goto out;
	}

	nlsei = nftnl_set_elems_iter_create(nls);
	if (nlsei == NULL)
		memory_allocation_error();

	nlse = nftnl_set_elems_iter_next(nlsei);
	while (nlse != NULL) {
		if (netlink_delinearize_setelem(nlse, set, monh->cache) < 0) {
			fprintf(stderr,
				"W: Unable to cache set_elem. "
				"Delinearize failed.\n");
			nftnl_set_elems_iter_destroy(nlsei);
			goto out;
		}
		nlse = nftnl_set_elems_iter_next(nlsei);
	}
	nftnl_set_elems_iter_destroy(nlsei);
out:
	nftnl_set_free(nls);
}

static void netlink_events_cache_delset_cb(struct set *s,
					   void *data)
{
	list_del(&s->list);
	set_free(s);
}

static void netlink_events_cache_delsets(struct netlink_mon_handler *monh,
					 const struct nlmsghdr *nlh)
{
	struct nftnl_rule *nlr = netlink_rule_alloc(nlh);

	nlr_for_each_set(nlr, netlink_events_cache_delset_cb, NULL,
			 monh->cache);
	nftnl_rule_free(nlr);
}

static void netlink_events_cache_addobj(struct netlink_mon_handler *monh,
					const struct nlmsghdr *nlh)
{
	struct netlink_ctx obj_tmpctx;
	struct nftnl_obj *nlo;
	struct table *t;
	struct obj *obj;
	LIST_HEAD(msgs);

	memset(&obj_tmpctx, 0, sizeof(obj_tmpctx));
	init_list_head(&obj_tmpctx.list);
	init_list_head(&msgs);
	obj_tmpctx.msgs = &msgs;

	nlo = netlink_obj_alloc(nlh);
	obj = netlink_delinearize_obj(&obj_tmpctx, nlo);
	if (obj == NULL)
		goto out;

	t = table_lookup(&obj->handle, monh->cache);
	if (t == NULL) {
		fprintf(stderr, "W: Unable to cache object: table not found.\n");
		obj_free(obj);
		goto out;
	}

	obj_add_hash(obj, t);
out:
	nftnl_obj_free(nlo);
}

static void netlink_events_cache_delobj(struct netlink_mon_handler *monh,
					const struct nlmsghdr *nlh)
{
	struct nftnl_obj *nlo;
	const char *name;
	struct obj *obj;
	struct handle h;
	struct table *t;
	uint32_t type;

	nlo      = netlink_obj_alloc(nlh);
	h.family = nftnl_obj_get_u32(nlo, NFTNL_OBJ_FAMILY);
	h.table  = nftnl_obj_get_str(nlo, NFTNL_OBJ_TABLE);

	name     = nftnl_obj_get_str(nlo, NFTNL_OBJ_NAME);
	type	 = nftnl_obj_get_u32(nlo, NFTNL_OBJ_TYPE);

	t = table_lookup(&h, monh->cache);
	if (t == NULL) {
		fprintf(stderr, "W: Unable to cache object: table not found.\n");
		goto out;
	}

	obj = obj_lookup(t, name, type);
	if (obj == NULL) {
		fprintf(stderr, "W: Unable to find object in cache\n");
		goto out;
	}

	list_del(&obj->list);
	obj_free(obj);
out:
	nftnl_obj_free(nlo);
}

static void netlink_events_cache_update(struct netlink_mon_handler *monh,
					const struct nlmsghdr *nlh, int type)
{
	if (!monh->cache_needed)
		return;

	switch (type) {
	case NFT_MSG_NEWTABLE:
		netlink_events_cache_addtable(monh, nlh);
		break;
	case NFT_MSG_DELTABLE:
		netlink_events_cache_deltable(monh, nlh);
		break;
	case NFT_MSG_NEWSET:
		netlink_events_cache_addset(monh, nlh);
		break;
	case NFT_MSG_NEWSETELEM:
		netlink_events_cache_addsetelem(monh, nlh);
		break;
	case NFT_MSG_DELRULE:
		/* there are no notification for anon-set deletion */
		netlink_events_cache_delsets(monh, nlh);
		break;
	case NFT_MSG_NEWOBJ:
		netlink_events_cache_addobj(monh, nlh);
		break;
	case NFT_MSG_DELOBJ:
		netlink_events_cache_delobj(monh, nlh);
		break;
	}
}

static void trace_print_hdr(const struct nftnl_trace *nlt)
{
	printf("trace id %08x ", nftnl_trace_get_u32(nlt, NFTNL_TRACE_ID));
	printf("%s ", family2str(nftnl_trace_get_u32(nlt, NFTNL_TRACE_FAMILY)));
	if (nftnl_trace_is_set(nlt, NFTNL_TRACE_TABLE))
		printf("%s ", nftnl_trace_get_str(nlt, NFTNL_TRACE_TABLE));
	if (nftnl_trace_is_set(nlt, NFTNL_TRACE_CHAIN))
		printf("%s ", nftnl_trace_get_str(nlt, NFTNL_TRACE_CHAIN));
}

static void trace_print_expr(const struct nftnl_trace *nlt, unsigned int attr,
			     struct expr *lhs, struct output_ctx *octx)
{
	struct expr *rhs, *rel;
	const void *data;
	uint32_t len;

	data = nftnl_trace_get_data(nlt, attr, &len);
	rhs  = constant_expr_alloc(&netlink_location,
				   lhs->dtype, lhs->byteorder,
				   len * BITS_PER_BYTE, data);
	rel  = relational_expr_alloc(&netlink_location, OP_EQ, lhs, rhs);

	expr_print(rel, octx);
	printf(" ");
	expr_free(rel);
}

static void trace_print_verdict(const struct nftnl_trace *nlt,
				 struct output_ctx *octx)
{
	const char *chain = NULL;
	unsigned int verdict;
	struct expr *expr;

	verdict = nftnl_trace_get_u32(nlt, NFTNL_TRACE_VERDICT);
	if (nftnl_trace_is_set(nlt, NFTNL_TRACE_JUMP_TARGET))
		chain = xstrdup(nftnl_trace_get_str(nlt, NFTNL_TRACE_JUMP_TARGET));
	expr = verdict_expr_alloc(&netlink_location, verdict, chain);

	printf("verdict ");
	expr_print(expr, octx);
	expr_free(expr);
}

static void trace_print_rule(const struct nftnl_trace *nlt,
			      struct output_ctx *octx, struct nft_cache *cache)
{
	const struct table *table;
	uint64_t rule_handle;
	struct chain *chain;
	struct rule *rule;
	struct handle h;

	h.family = nftnl_trace_get_u32(nlt, NFTNL_TRACE_FAMILY);
	h.table  = nftnl_trace_get_str(nlt, NFTNL_TRACE_TABLE);
	h.chain  = nftnl_trace_get_str(nlt, NFTNL_TRACE_CHAIN);

	if (!h.table)
		return;

	table = table_lookup(&h, cache);
	if (!table)
		return;

	chain = chain_lookup(table, &h);
	if (!chain)
		return;

	rule_handle = nftnl_trace_get_u64(nlt, NFTNL_TRACE_RULE_HANDLE);
	rule = rule_lookup(chain, rule_handle);
	if (!rule)
		return;

	trace_print_hdr(nlt);
	printf("rule ");
	rule_print(rule, octx);
	printf(" (");
	trace_print_verdict(nlt, octx);
	printf(")\n");
}

static void trace_gen_stmts(struct list_head *stmts,
			    struct proto_ctx *ctx, struct payload_dep_ctx *pctx,
			    const struct nftnl_trace *nlt, unsigned int attr,
			    enum proto_bases base)
{
	struct list_head unordered = LIST_HEAD_INIT(unordered);
	struct list_head list;
	struct expr *rel, *lhs, *rhs, *tmp, *nexpr;
	struct stmt *stmt;
	const struct proto_desc *desc;
	const void *hdr;
	uint32_t hlen;
	unsigned int n;
	bool stacked;

	if (!nftnl_trace_is_set(nlt, attr))
		return;
	hdr = nftnl_trace_get_data(nlt, attr, &hlen);

	lhs = payload_expr_alloc(&netlink_location, NULL, 0);
	payload_init_raw(lhs, base, 0, hlen * BITS_PER_BYTE);
	rhs = constant_expr_alloc(&netlink_location,
				  &invalid_type, BYTEORDER_INVALID,
				  hlen * BITS_PER_BYTE, hdr);

restart:
	init_list_head(&list);
	payload_expr_expand(&list, lhs, ctx);
	expr_free(lhs);

	desc = NULL;
	list_for_each_entry_safe(lhs, nexpr, &list, list) {
		if (desc && desc != ctx->protocol[base].desc) {
			/* Chained protocols */
			lhs->payload.offset = 0;
			if (ctx->protocol[base].desc == NULL)
				break;
			goto restart;
		}

		tmp = constant_expr_splice(rhs, lhs->len);
		expr_set_type(tmp, lhs->dtype, lhs->byteorder);
		if (tmp->byteorder == BYTEORDER_HOST_ENDIAN)
			mpz_switch_byteorder(tmp->value, tmp->len / BITS_PER_BYTE);

		/* Skip unknown and filtered expressions */
		desc = lhs->payload.desc;
		if (lhs->dtype == &invalid_type ||
		    desc->checksum_key == payload_hdr_field(lhs) ||
		    desc->format.filter & (1 << payload_hdr_field(lhs))) {
			expr_free(lhs);
			expr_free(tmp);
			continue;
		}

		rel  = relational_expr_alloc(&lhs->location, OP_EQ, lhs, tmp);
		stmt = expr_stmt_alloc(&rel->location, rel);
		list_add_tail(&stmt->list, &unordered);

		desc = ctx->protocol[base].desc;
		lhs->ops->pctx_update(ctx, rel);
	}

	expr_free(rhs);

	n = 0;
next:
	list_for_each_entry(stmt, &unordered, list) {
		rel = stmt->expr;
		lhs = rel->left;

		/* Move statements to result list in defined order */
		desc = lhs->payload.desc;
		if (desc->format.order[n] &&
		    desc->format.order[n] != payload_hdr_field(lhs))
			continue;

		list_move_tail(&stmt->list, stmts);
		n++;

		stacked = payload_is_stacked(desc, rel);

		if (lhs->flags & EXPR_F_PROTOCOL &&
		    pctx->pbase == PROTO_BASE_INVALID) {
			payload_dependency_store(pctx, stmt, base - stacked);
		} else {
			payload_dependency_kill(pctx, lhs);
			if (lhs->flags & EXPR_F_PROTOCOL)
				payload_dependency_store(pctx, stmt, base - stacked);
		}

		goto next;
	}
}

static void trace_print_packet(const struct nftnl_trace *nlt,
			        struct output_ctx *octx)
{
	struct list_head stmts = LIST_HEAD_INIT(stmts);
	const struct proto_desc *ll_desc;
	struct payload_dep_ctx pctx = {};
	struct proto_ctx ctx;
	uint16_t dev_type;
	uint32_t nfproto;
	struct stmt *stmt, *next;

	trace_print_hdr(nlt);

	printf("packet: ");
	if (nftnl_trace_is_set(nlt, NFTNL_TRACE_IIF))
		trace_print_expr(nlt, NFTNL_TRACE_IIF,
				 meta_expr_alloc(&netlink_location,
						 NFT_META_IIF), octx);
	if (nftnl_trace_is_set(nlt, NFTNL_TRACE_OIF))
		trace_print_expr(nlt, NFTNL_TRACE_OIF,
				 meta_expr_alloc(&netlink_location,
						 NFT_META_OIF), octx);

	proto_ctx_init(&ctx, nftnl_trace_get_u32(nlt, NFTNL_TRACE_FAMILY), 0);
	ll_desc = ctx.protocol[PROTO_BASE_LL_HDR].desc;
	if ((ll_desc == &proto_inet || ll_desc  == &proto_netdev) &&
	    nftnl_trace_is_set(nlt, NFTNL_TRACE_NFPROTO)) {
		nfproto = nftnl_trace_get_u32(nlt, NFTNL_TRACE_NFPROTO);

		proto_ctx_update(&ctx, PROTO_BASE_LL_HDR, &netlink_location, NULL);
		proto_ctx_update(&ctx, PROTO_BASE_NETWORK_HDR, &netlink_location,
				 proto_find_upper(ll_desc, nfproto));
	}
	if (ctx.protocol[PROTO_BASE_LL_HDR].desc == NULL &&
	    nftnl_trace_is_set(nlt, NFTNL_TRACE_IIFTYPE)) {
		dev_type = nftnl_trace_get_u16(nlt, NFTNL_TRACE_IIFTYPE);
		proto_ctx_update(&ctx, PROTO_BASE_LL_HDR, &netlink_location,
				 proto_dev_desc(dev_type));
	}

	trace_gen_stmts(&stmts, &ctx, &pctx, nlt, NFTNL_TRACE_LL_HEADER,
			PROTO_BASE_LL_HDR);
	trace_gen_stmts(&stmts, &ctx, &pctx, nlt, NFTNL_TRACE_NETWORK_HEADER,
			PROTO_BASE_NETWORK_HDR);
	trace_gen_stmts(&stmts, &ctx, &pctx, nlt, NFTNL_TRACE_TRANSPORT_HEADER,
			PROTO_BASE_TRANSPORT_HDR);

	list_for_each_entry_safe(stmt, next, &stmts, list) {
		stmt_print(stmt, octx);
		printf(" ");
		stmt_free(stmt);
	}
	printf("\n");
}

static int netlink_events_trace_cb(const struct nlmsghdr *nlh, int type,
				   struct netlink_mon_handler *monh)
{
	struct nftnl_trace *nlt;

	assert(type == NFT_MSG_TRACE);

	nlt = nftnl_trace_alloc();
	if (!nlt)
		memory_allocation_error();

	if (nftnl_trace_nlmsg_parse(nlh, nlt) < 0)
		netlink_abi_error();

	switch (nftnl_trace_get_u32(nlt, NFTNL_TRACE_TYPE)) {
	case NFT_TRACETYPE_RULE:
		if (nftnl_trace_is_set(nlt, NFTNL_TRACE_LL_HEADER) ||
		    nftnl_trace_is_set(nlt, NFTNL_TRACE_NETWORK_HEADER))
			trace_print_packet(nlt, monh->ctx->octx);

		if (nftnl_trace_is_set(nlt, NFTNL_TRACE_RULE_HANDLE))
			trace_print_rule(nlt, monh->ctx->octx, monh->cache);
		break;
	case NFT_TRACETYPE_POLICY:
	case NFT_TRACETYPE_RETURN:
		trace_print_hdr(nlt);

		if (nftnl_trace_is_set(nlt, NFTNL_TRACE_VERDICT)) {
			trace_print_verdict(nlt, monh->ctx->octx);
			printf(" ");
		}

		if (nftnl_trace_is_set(nlt, NFTNL_TRACE_MARK))
			trace_print_expr(nlt, NFTNL_TRACE_MARK,
					 meta_expr_alloc(&netlink_location,
							 NFT_META_MARK),
					 monh->ctx->octx);
		printf("\n");
		break;
	}

	nftnl_trace_free(nlt);
	return MNL_CB_OK;
}

/* only those which could be useful listening to events */
static const char *const nftnl_msg_types[NFT_MSG_MAX] = {
	[NFT_MSG_NEWTABLE]	= "NFT_MSG_NEWTABLE",
	[NFT_MSG_DELTABLE]	= "NFT_MSG_DELTABLE",
	[NFT_MSG_NEWCHAIN]	= "NFT_MSG_NEWCHAIN",
	[NFT_MSG_DELCHAIN]	= "NFT_MSG_DELCHAIN",
	[NFT_MSG_NEWSET]	= "NFT_MSG_NEWSET",
	[NFT_MSG_DELSET]	= "NFT_MSG_DELSET",
	[NFT_MSG_NEWSETELEM]	= "NFT_MSG_NEWSETELEM",
	[NFT_MSG_DELSETELEM]	= "NFT_MSG_DELSETELEM",
	[NFT_MSG_NEWRULE]	= "NFT_MSG_NEWRULE",
	[NFT_MSG_DELRULE]	= "NFT_MSG_DELRULE",
	[NFT_MSG_TRACE]		= "NFT_MSG_TRACE",
	[NFT_MSG_NEWGEN]	= "NFT_MSG_NEWGEN",
	[NFT_MSG_NEWOBJ]	= "NFT_MSG_NEWOBJ",
	[NFT_MSG_DELOBJ]	= "NFT_MSG_DELOBJ",
};

static const char *nftnl_msgtype2str(uint16_t type)
{
	if (type >= NFT_MSG_MAX || !nftnl_msg_types[type])
		return "unknown";

	return nftnl_msg_types[type];
}

static void netlink_events_debug(uint16_t type, unsigned int debug_mask)
{
	if (!(debug_mask & DEBUG_NETLINK))
		return;

	printf("netlink event: %s\n", nftnl_msgtype2str(type));
}

static int netlink_events_newgen_cb(const struct nlmsghdr *nlh, int type,
				    struct netlink_mon_handler *monh)
{
	const struct nlattr *attr;
	char name[256] = "";
	int genid = -1, pid = -1;

	mnl_attr_for_each(attr, nlh, sizeof(struct nfgenmsg)) {
		switch (mnl_attr_get_type(attr)) {
		case NFTA_GEN_ID:
			if (mnl_attr_validate(attr, MNL_TYPE_U32) < 0)
				break;
			genid = ntohl(mnl_attr_get_u32(attr));
			break;
		case NFTA_GEN_PROC_NAME:
			if (mnl_attr_validate(attr, MNL_TYPE_NUL_STRING) < 0)
				break;
			strncpy(name, mnl_attr_get_str(attr), sizeof(name));
			break;
		case NFTA_GEN_PROC_ID:
			if (mnl_attr_validate(attr, MNL_TYPE_U32) < 0)
				break;
			pid = ntohl(mnl_attr_get_u32(attr));
			break;
		}
	}
	if (genid >= 0) {
		nft_mon_print(monh, "# new generation %d", genid);
		if (pid >= 0) {
			nft_mon_print(monh, " by process %d", pid);
			if (!monh->ctx->octx->numeric)
				nft_mon_print(monh, " (%s)", name);
		}
		nft_mon_print(monh, "\n");
	}

	return MNL_CB_OK;
}

static int netlink_events_cb(const struct nlmsghdr *nlh, void *data)
{
	int ret = MNL_CB_OK;
	uint16_t type = NFNL_MSG_TYPE(nlh->nlmsg_type);
	struct netlink_mon_handler *monh = (struct netlink_mon_handler *)data;

	netlink_events_debug(type, monh->debug_mask);
	netlink_events_cache_update(monh, nlh, type);

	if (!(monh->monitor_flags & (1 << type)))
		return ret;

	switch (type) {
	case NFT_MSG_NEWTABLE:
	case NFT_MSG_DELTABLE:
		ret = netlink_events_table_cb(nlh, type, monh);
		break;
	case NFT_MSG_NEWCHAIN:
	case NFT_MSG_DELCHAIN:
		ret = netlink_events_chain_cb(nlh, type, monh);
		break;
	case NFT_MSG_NEWSET:
	case NFT_MSG_DELSET:		/* nft {add|delete} set */
		ret = netlink_events_set_cb(nlh, type, monh);
		break;
	case NFT_MSG_NEWSETELEM:
	case NFT_MSG_DELSETELEM:	/* nft {add|delete} element */
		ret = netlink_events_setelem_cb(nlh, type, monh);
		break;
	case NFT_MSG_NEWRULE:
	case NFT_MSG_DELRULE:
		ret = netlink_events_rule_cb(nlh, type, monh);
		break;
	case NFT_MSG_TRACE:
		ret = netlink_events_trace_cb(nlh, type, monh);
		break;
	case NFT_MSG_NEWOBJ:
	case NFT_MSG_DELOBJ:
		ret = netlink_events_obj_cb(nlh, type, monh);
		break;
	case NFT_MSG_NEWGEN:
		ret = netlink_events_newgen_cb(nlh, type, monh);
		break;
	}
	fflush(stdout);

	return ret;
}

int netlink_echo_callback(const struct nlmsghdr *nlh, void *data)
{
	struct netlink_ctx *ctx = data;
	struct netlink_mon_handler echo_monh = {
		.format = NFTNL_OUTPUT_DEFAULT,
		.ctx = ctx,
		.loc = &netlink_location,
		.monitor_flags = 0xffffffff,
		.cache_needed = true,
		.cache = ctx->cache,
		.debug_mask = ctx->debug_mask,
	};

	if (!echo_monh.ctx->octx->echo)
		return MNL_CB_OK;

	return netlink_events_cb(nlh, &echo_monh);
}

int netlink_monitor(struct netlink_mon_handler *monhandler,
		    struct mnl_socket *nf_sock)
{
	struct mnl_ctx ctx = {
		.nf_sock	= nf_sock,
		.debug_mask	= monhandler->debug_mask,
	};
	int group;

	if (monhandler->monitor_flags & (1 << NFT_MSG_TRACE)) {
		group = NFNLGRP_NFTRACE;
		if (mnl_socket_setsockopt(nf_sock, NETLINK_ADD_MEMBERSHIP,
					  &group, sizeof(int)) < 0)
			return netlink_io_error(monhandler->ctx,
						monhandler->loc,
						"Could not bind to netlink socket %s",
						strerror(errno));
	}
	if (monhandler->monitor_flags & ~(1 << NFT_MSG_TRACE)) {
		group = NFNLGRP_NFTABLES;
		if (mnl_socket_setsockopt(nf_sock, NETLINK_ADD_MEMBERSHIP,
					  &group, sizeof(int)) < 0)
			return netlink_io_error(monhandler->ctx,
						monhandler->loc,
						"Could not bind to netlink socket %s",
						strerror(errno));
	}

	return mnl_nft_event_listener(&ctx, netlink_events_cb, monhandler);
}

bool netlink_batch_supported(struct mnl_socket *nf_sock, uint32_t *seqnum)
{
	return mnl_batch_supported(nf_sock, seqnum);
}
