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
#include <inttypes.h>

#include <libnftnl/table.h>
#include <libnftnl/trace.h>
#include <libnftnl/chain.h>
#include <libnftnl/expr.h>
#include <libnftnl/object.h>
#include <libnftnl/set.h>
#include <libnftnl/flowtable.h>
#include <libnftnl/udata.h>
#include <libnftnl/ruleset.h>
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

	if (fcntl(mnl_socket_get_fd(nf_sock), F_SETFL, O_NONBLOCK))
		netlink_init_error();

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

uint16_t netlink_genid_get(struct netlink_ctx *ctx)
{
	return mnl_genid_get(ctx);
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
	if (h->table.name != NULL)
		nftnl_table_set(nlt, NFTNL_TABLE_NAME, h->table.name);
	if (h->handle.id)
		nftnl_table_set_u64(nlt, NFTNL_TABLE_HANDLE, h->handle.id);

	return nlt;
}

struct nftnl_chain *alloc_nftnl_chain(const struct handle *h)
{
	struct nftnl_chain *nlc;

	nlc = nftnl_chain_alloc();
	if (nlc == NULL)
		memory_allocation_error();

	nftnl_chain_set_u32(nlc, NFTNL_CHAIN_FAMILY, h->family);
	nftnl_chain_set_str(nlc, NFTNL_CHAIN_TABLE, h->table.name);
	if (h->handle.id)
		nftnl_chain_set_u64(nlc, NFTNL_CHAIN_HANDLE, h->handle.id);
	if (h->chain.name != NULL)
		nftnl_chain_set_str(nlc, NFTNL_CHAIN_NAME, h->chain.name);

	return nlc;
}

struct nftnl_rule *alloc_nftnl_rule(const struct handle *h)
{
	struct nftnl_rule *nlr;

	nlr = nftnl_rule_alloc();
	if (nlr == NULL)
		memory_allocation_error();

	nftnl_rule_set_u32(nlr, NFTNL_RULE_FAMILY, h->family);
	nftnl_rule_set_str(nlr, NFTNL_RULE_TABLE, h->table.name);
	if (h->chain.name != NULL)
		nftnl_rule_set_str(nlr, NFTNL_RULE_CHAIN, h->chain.name);
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
	nftnl_set_set_str(nls, NFTNL_SET_TABLE, h->table.name);
	if (h->set.name != NULL)
		nftnl_set_set_str(nls, NFTNL_SET_NAME, h->set.name);
	if (h->set_id)
		nftnl_set_set_u32(nls, NFTNL_SET_ID, h->set_id);
	if (h->handle.id)
		nftnl_set_set_u64(nls, NFTNL_SET_HANDLE, h->handle.id);

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
	if (set->set_flags & NFT_SET_OBJECT && data != NULL) {
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
	nftnl_obj_set_str(nlo, NFTNL_OBJ_TABLE, h->table.name);
	if (h->obj.name != NULL)
		nftnl_obj_set_str(nlo, NFTNL_OBJ_NAME, h->obj.name);

	nftnl_obj_set_u32(nlo, NFTNL_OBJ_TYPE, type);
	if (h->handle.id)
		nftnl_obj_set_u64(nlo, NFTNL_OBJ_HANDLE, h->handle.id);

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
					div_round_up(i->len, BITS_PER_BYTE));
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
		snprintf(data->chain, NFT_CHAIN_MAXNAMELEN, "%s", expr->chain);
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

int netlink_add_rule_batch(struct netlink_ctx *ctx, const struct cmd *cmd,
		           uint32_t flags)
{
	struct rule *rule = cmd->rule;
	struct nftnl_rule *nlr;
	int err;

	nlr = alloc_nftnl_rule(&rule->handle);
	netlink_linearize_rule(ctx, nlr, rule);
	err = mnl_nft_rule_batch_add(nlr, ctx->batch, flags | NLM_F_EXCL,
				     ctx->seqnum);
	nftnl_rule_free(nlr);

	return err;
}

int netlink_replace_rule_batch(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	struct rule *rule = cmd->rule;
	struct nftnl_rule *nlr;
	int err, flags = 0;

	if (ctx->octx->echo) {
		err = cache_update(ctx->nf_sock, ctx->cache,
				   CMD_INVALID, ctx->msgs,
				   ctx->debug_mask, ctx->octx);
		if (err < 0)
			return err;

		flags |= NLM_F_ECHO;
	}

	nlr = alloc_nftnl_rule(&rule->handle);
	netlink_linearize_rule(ctx, nlr, rule);
	err = mnl_nft_rule_batch_replace(nlr, ctx->batch, flags, ctx->seqnum);
	nftnl_rule_free(nlr);

	return err;
}

int netlink_del_rule_batch(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	struct nftnl_rule *nlr;
	int err;

	nlr = alloc_nftnl_rule(&cmd->handle);
	err = mnl_nft_rule_batch_del(nlr, ctx->batch, 0, ctx->seqnum);
	nftnl_rule_free(nlr);

	return err;
}

void netlink_dump_rule(const struct nftnl_rule *nlr, struct netlink_ctx *ctx)
{
	FILE *fp = ctx->octx->output_fp;

	if (!(ctx->debug_mask & NFT_DEBUG_NETLINK) || !fp)
		return;

	nftnl_rule_fprintf(fp, nlr, 0, 0);
	fprintf(fp, "\n");
}

void netlink_dump_expr(const struct nftnl_expr *nle,
		       FILE *fp, unsigned int debug_mask)
{
	if (!(debug_mask & NFT_DEBUG_NETLINK))
		return;

	nftnl_expr_fprintf(fp, nle, 0, 0);
	fprintf(fp, "\n");
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
	    strcmp(table, h->table.name) != 0 ||
	    (h->chain.name && strcmp(chain, h->chain.name) != 0))
		return 0;

	netlink_dump_rule(nlr, ctx);
	rule = netlink_delinearize_rule(ctx, nlr);
	list_add_tail(&rule->list, &ctx->list);

	return 0;
}

static int netlink_list_rules(struct netlink_ctx *ctx, const struct handle *h)
{
	struct nftnl_rule_list *rule_cache;

	rule_cache = mnl_nft_rule_dump(ctx, h->family);
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

static int netlink_flush_rules(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	return netlink_del_rule_batch(ctx, cmd);
}

void netlink_dump_chain(const struct nftnl_chain *nlc, struct netlink_ctx *ctx)
{
	FILE *fp = ctx->octx->output_fp;

	if (!(ctx->debug_mask & NFT_DEBUG_NETLINK) || !fp)
		return;

	nftnl_chain_fprintf(fp, nlc, 0, 0);
	fprintf(fp, "\n");
}

int netlink_add_chain_batch(struct netlink_ctx *ctx, const struct cmd *cmd,
			    uint32_t flags)
{
	struct chain *chain = cmd->chain;
	struct nftnl_chain *nlc;
	int err;

	nlc = alloc_nftnl_chain(&cmd->handle);
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

	return err;
}

int netlink_rename_chain_batch(struct netlink_ctx *ctx, const struct handle *h,
			       const struct cmd *cmd)
{
	const char *name = cmd->arg;
	struct nftnl_chain *nlc;
	int err;

	nlc = alloc_nftnl_chain(h);
	nftnl_chain_set_str(nlc, NFTNL_CHAIN_NAME, name);
	netlink_dump_chain(nlc, ctx);
	err = mnl_nft_chain_batch_add(nlc, ctx->batch, 0, ctx->seqnum);
	nftnl_chain_free(nlc);

	return err;
}

int netlink_delete_chain_batch(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	struct nftnl_chain *nlc;
	int err;

	nlc = alloc_nftnl_chain(&cmd->handle);
	netlink_dump_chain(nlc, ctx);
	err = mnl_nft_chain_batch_del(nlc, ctx->batch, 0, ctx->seqnum);
	nftnl_chain_free(nlc);

	return err;
}

struct chain *netlink_delinearize_chain(struct netlink_ctx *ctx,
					const struct nftnl_chain *nlc)
{
	struct chain *chain;

	chain = chain_alloc(nftnl_chain_get_str(nlc, NFTNL_CHAIN_NAME));
	chain->handle.family =
		nftnl_chain_get_u32(nlc, NFTNL_CHAIN_FAMILY);
	chain->handle.table.name  =
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

	if (h->family != family || strcmp(table, h->table.name) != 0)
		return 0;
	if (h->chain.name && strcmp(name, h->chain.name) != 0)
		return 0;

	chain = netlink_delinearize_chain(ctx, nlc);
	list_add_tail(&chain->list, &ctx->list);

	return 0;
}

int netlink_list_chains(struct netlink_ctx *ctx, const struct handle *h)
{
	struct nftnl_chain_list *chain_cache;

	chain_cache = mnl_nft_chain_dump(ctx, h->family);
	if (chain_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return 0;
	}

	ctx->data = h;
	nftnl_chain_list_foreach(chain_cache, list_chain_cb, ctx);
	nftnl_chain_list_free(chain_cache);

	return 0;
}

int netlink_flush_chain(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	return netlink_del_rule_batch(ctx, cmd);
}

int netlink_add_table_batch(struct netlink_ctx *ctx, const struct cmd *cmd,
			    uint32_t flags)
{
	struct nftnl_table *nlt;
	int err;

	nlt = alloc_nftnl_table(&cmd->handle);
	if (cmd->table != NULL)
		nftnl_table_set_u32(nlt, NFTNL_TABLE_FLAGS, cmd->table->flags);
	else
		nftnl_table_set_u32(nlt, NFTNL_TABLE_FLAGS, 0);

	err = mnl_nft_table_batch_add(nlt, ctx->batch, flags, ctx->seqnum);
	nftnl_table_free(nlt);

	return err;
}

int netlink_delete_table_batch(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	struct nftnl_table *nlt;
	int err;

	nlt = alloc_nftnl_table(&cmd->handle);
	err = mnl_nft_table_batch_del(nlt, ctx->batch, 0, ctx->seqnum);
	nftnl_table_free(nlt);

	return err;
}

struct table *netlink_delinearize_table(struct netlink_ctx *ctx,
					const struct nftnl_table *nlt)
{
	struct table *table;

	table = table_alloc();
	table->handle.family = nftnl_table_get_u32(nlt, NFTNL_TABLE_FAMILY);
	table->handle.table.name = xstrdup(nftnl_table_get_str(nlt, NFTNL_TABLE_NAME));
	table->flags	     = nftnl_table_get_u32(nlt, NFTNL_TABLE_FLAGS);
	table->handle.handle.id = nftnl_table_get_u64(nlt, NFTNL_TABLE_HANDLE);

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

int netlink_list_tables(struct netlink_ctx *ctx, const struct handle *h)
{
	struct nftnl_table_list *table_cache;

	table_cache = mnl_nft_table_dump(ctx, h->family);
	if (table_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return 0;
	}

	ctx->data = h;
	nftnl_table_list_foreach(table_cache, list_table_cb, ctx);
	nftnl_table_list_free(table_cache);
	return 0;
}

int netlink_list_table(struct netlink_ctx *ctx, const struct handle *h)
{
	return netlink_list_rules(ctx, h);
}

int netlink_flush_table(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	return netlink_flush_rules(ctx, cmd);
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

	if (!(ctx->debug_mask & NFT_DEBUG_NETLINK) || !fp)
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
	case UDATA_SET_MERGE_ELEMENTS:
		if (len != sizeof(uint32_t))
			return -1;
		break;
	default:
		return 0;
	}
	tb[type] = attr;
	return 0;
}

struct set *netlink_delinearize_set(struct netlink_ctx *ctx,
				    const struct nftnl_set *nls)
{
	const struct nftnl_udata *ud[UDATA_SET_MAX + 1] = {};
	uint32_t flags, key, data, data_len, objtype = 0;
	enum byteorder keybyteorder = BYTEORDER_INVALID;
	enum byteorder databyteorder = BYTEORDER_INVALID;
	const struct datatype *keytype, *datatype;
	bool automerge = false;
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
		if (ud[UDATA_SET_MERGE_ELEMENTS])
			automerge =
				nftnl_udata_get_u32(ud[UDATA_SET_MERGE_ELEMENTS]);
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
	set->handle.table.name = xstrdup(nftnl_set_get_str(nls, NFTNL_SET_TABLE));
	set->handle.set.name = xstrdup(nftnl_set_get_str(nls, NFTNL_SET_NAME));
	set->automerge	   = automerge;

	set->key     = constant_expr_alloc(&netlink_location,
					   set_datatype_alloc(keytype, keybyteorder),
					   keybyteorder,
					   nftnl_set_get_u32(nls, NFTNL_SET_KEY_LEN) * BITS_PER_BYTE,
					   NULL);
	set->flags   = nftnl_set_get_u32(nls, NFTNL_SET_FLAGS);
	set->handle.handle.id = nftnl_set_get_u64(nls, NFTNL_SET_HANDLE);

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

int netlink_add_set_batch(struct netlink_ctx *ctx, const struct cmd *cmd,
			  uint32_t flags)
{
	struct nftnl_udata_buf *udbuf;
	struct set *set = cmd->set;
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(&cmd->handle);
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

	if (set->automerge &&
	    !nftnl_udata_put_u32(udbuf, UDATA_SET_MERGE_ELEMENTS,
				 set->automerge))
		memory_allocation_error();

	nftnl_set_set_data(nls, NFTNL_SET_USERDATA, nftnl_udata_buf_data(udbuf),
			   nftnl_udata_buf_len(udbuf));
	nftnl_udata_buf_free(udbuf);

	netlink_dump_set(nls, ctx);

	err = mnl_nft_set_batch_add(nls, ctx->batch, flags, ctx->seqnum);
	nftnl_set_free(nls);

	return err;
}

int netlink_delete_set_batch(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(&cmd->handle);
	err = mnl_nft_set_batch_del(nls, ctx->batch, 0, ctx->seqnum);
	nftnl_set_free(nls);

	return err;
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

int netlink_list_sets(struct netlink_ctx *ctx, const struct handle *h)
{
	struct nftnl_set_list *set_cache;
	int err;

	set_cache = mnl_nft_set_dump(ctx, h->family, h->table.name);
	if (set_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return 0;
	}

	ctx->data = h;
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

int netlink_add_setelems_batch(struct netlink_ctx *ctx, const struct handle *h,
			       const struct expr *expr, uint32_t flags)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);
	alloc_setelem_cache(expr, nls);
	netlink_dump_set(nls, ctx);

	err = mnl_nft_setelem_batch_add(nls, ctx->batch, flags, ctx->seqnum);
	nftnl_set_free(nls);

	return err;
}

int netlink_delete_setelems_batch(struct netlink_ctx *ctx,
				  const struct cmd *cmd)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(&cmd->handle);
	if (cmd->expr)
		alloc_setelem_cache(cmd->expr, nls);
	netlink_dump_set(nls, ctx);

	err = mnl_nft_setelem_batch_del(nls, ctx->batch, 0, ctx->seqnum);
	nftnl_set_free(nls);

	return err;
}

int netlink_flush_setelems(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(&cmd->handle);
	netlink_dump_set(nls, ctx);

	err = mnl_nft_setelem_batch_flush(nls, ctx->batch, 0, ctx->seqnum);
	nftnl_set_free(nls);

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

int netlink_delinearize_setelem(struct nftnl_set_elem *nlse,
				const struct set *set, struct nft_cache *cache)
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
		if (nftnl_set_elem_is_set(nlse, NFTNL_SET_ELEM_OBJREF)) {
			nld.value = nftnl_set_elem_get(nlse,
						       NFTNL_SET_ELEM_OBJREF,
						       &nld.len);
		} else
			goto out;

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

static int list_setelem_cb(struct nftnl_set_elem *nlse, void *arg)
{
	struct netlink_ctx *ctx = arg;
	return netlink_delinearize_setelem(nlse, ctx->set, ctx->cache);
}

int netlink_list_setelems(struct netlink_ctx *ctx, const struct handle *h,
			  struct set *set)
{
	struct nftnl_set *nls;
	int err;

	nls = alloc_nftnl_set(h);

	err = mnl_nft_setelem_get(ctx, nls);
	if (err < 0) {
		nftnl_set_free(nls);
		if (errno == EINTR)
			return -1;

		return 0;
	}

	ctx->set = set;
	set->init = set_expr_alloc(&internal_location, set);
	nftnl_set_elem_foreach(nls, list_setelem_cb, ctx);

	if (!(set->flags & NFT_SET_INTERVAL))
		list_expr_sort(&ctx->set->init->expressions);

	nftnl_set_free(nls);
	ctx->set = NULL;

	if (set->flags & NFT_SET_INTERVAL)
		interval_map_decompose(set->init);

	return 0;
}

int netlink_get_setelem(struct netlink_ctx *ctx, const struct handle *h,
			const struct location *loc, struct table *table,
			struct set *set, struct expr *init)
{
	struct nftnl_set *nls, *nls_out = NULL;

	nls = alloc_nftnl_set(h);
	alloc_setelem_cache(init, nls);

	netlink_dump_set(nls, ctx);

	nls_out = mnl_nft_setelem_get_one(ctx, nls);
	if (!nls_out)
		return -1;

	ctx->set = set;
	set->init = set_expr_alloc(loc, set);
	nftnl_set_elem_foreach(nls_out, list_setelem_cb, ctx);

	if (!(set->flags & NFT_SET_INTERVAL))
		list_expr_sort(&ctx->set->init->expressions);

	nftnl_set_free(nls);
	nftnl_set_free(nls_out);
	ctx->set = NULL;

	if (set->flags & NFT_SET_INTERVAL)
		get_set_decompose(table, set);

	return 0;
}

void netlink_dump_obj(struct nftnl_obj *nln, struct netlink_ctx *ctx)
{
	FILE *fp = ctx->octx->output_fp;

	if (!(ctx->debug_mask & NFT_DEBUG_NETLINK) || !fp)
		return;

	nftnl_obj_fprintf(fp, nln, 0, 0);
	fprintf(fp, "\n");
}

int netlink_add_obj(struct netlink_ctx *ctx, const struct cmd *cmd,
		    uint32_t flags)
{
	struct nftnl_obj *nlo;
	int err;

	nlo = alloc_nftnl_obj(&cmd->handle, cmd->object);
	netlink_dump_obj(nlo, ctx);

	err = mnl_nft_obj_batch_add(nlo, ctx->batch, flags, ctx->seqnum);
	nftnl_obj_free(nlo);

	return err;
}

int netlink_delete_obj(struct netlink_ctx *ctx, const struct cmd *cmd,
		       uint32_t type)
{
	struct nftnl_obj *nlo;
	int err;

	nlo = __alloc_nftnl_obj(&cmd->handle, type);
	netlink_dump_obj(nlo, ctx);

	err = mnl_nft_obj_batch_del(nlo, ctx->batch, 0, ctx->seqnum);
	nftnl_obj_free(nlo);

	return err;
}

struct obj *netlink_delinearize_obj(struct netlink_ctx *ctx,
				    struct nftnl_obj *nlo)
{
	struct obj *obj;
	uint32_t type;

	obj = obj_alloc(&netlink_location);
	obj->handle.family = nftnl_obj_get_u32(nlo, NFTNL_OBJ_FAMILY);
	obj->handle.table.name =
		xstrdup(nftnl_obj_get_str(nlo, NFTNL_OBJ_TABLE));
	obj->handle.obj.name =
		xstrdup(nftnl_obj_get_str(nlo, NFTNL_OBJ_NAME));
	obj->handle.handle.id =
		nftnl_obj_get_u64(nlo, NFTNL_OBJ_HANDLE);

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

static struct nftnl_flowtable *alloc_nftnl_flowtable(const struct handle *h,
						     const struct flowtable *ft)
{
	struct nftnl_flowtable *flo;

	flo = nftnl_flowtable_alloc();
	if (flo == NULL)
		memory_allocation_error();

	nftnl_flowtable_set_u32(flo, NFTNL_FLOWTABLE_FAMILY, h->family);
	nftnl_flowtable_set_str(flo, NFTNL_FLOWTABLE_TABLE, h->table.name);
	if (h->flowtable != NULL)
		nftnl_flowtable_set_str(flo, NFTNL_FLOWTABLE_NAME, h->flowtable);

	return flo;
}

static void netlink_dump_flowtable(struct nftnl_flowtable *flo,
				   struct netlink_ctx *ctx)
{
	FILE *fp = ctx->octx->output_fp;

	if (!(ctx->debug_mask & NFT_DEBUG_NETLINK) || !fp)
		return;

	nftnl_flowtable_fprintf(fp, flo, 0, 0);
	fprintf(fp, "\n");
}

int netlink_add_flowtable(struct netlink_ctx *ctx, const struct cmd *cmd,
			  uint32_t flags)
{
	struct flowtable *ft = cmd->flowtable;
	struct nftnl_flowtable *flo;
	const char *dev_array[8];
	struct expr *expr;
	int i = 0, err;

	flo = alloc_nftnl_flowtable(&cmd->handle, ft);
	nftnl_flowtable_set_u32(flo, NFTNL_FLOWTABLE_HOOKNUM, ft->hooknum);
	nftnl_flowtable_set_u32(flo, NFTNL_FLOWTABLE_PRIO, ft->priority);

	list_for_each_entry(expr, &ft->dev_expr->expressions, list)
		dev_array[i++] = expr->identifier;

	dev_array[i] = NULL;
	nftnl_flowtable_set(flo, NFTNL_FLOWTABLE_DEVICES, dev_array);

	netlink_dump_flowtable(flo, ctx);

	err = mnl_nft_flowtable_batch_add(flo, ctx->batch, flags, ctx->seqnum);
	nftnl_flowtable_free(flo);

	return err;
}

int netlink_delete_flowtable(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	struct nftnl_flowtable *flo;
	int err;

	flo = alloc_nftnl_flowtable(&cmd->handle, NULL);
	netlink_dump_flowtable(flo, ctx);

	err = mnl_nft_flowtable_batch_del(flo, ctx->batch, 0, ctx->seqnum);
	nftnl_flowtable_free(flo);

	return err;
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

int netlink_list_objs(struct netlink_ctx *ctx, const struct handle *h)
{
	struct nftnl_obj_list *obj_cache;
	int err;

	obj_cache = mnl_nft_obj_dump(ctx, h->family,
				     h->table.name, NULL, 0, true, false);
	if (obj_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return 0;
	}

	err = nftnl_obj_list_foreach(obj_cache, list_obj_cb, ctx);
	nftnl_obj_list_free(obj_cache);
	return err;
}

int netlink_reset_objs(struct netlink_ctx *ctx, const struct cmd *cmd,
		       uint32_t type, bool dump)
{
	const struct handle *h = &cmd->handle;
	struct nftnl_obj_list *obj_cache;
	int err;

	obj_cache = mnl_nft_obj_dump(ctx, h->family,
				     h->table.name, h->obj.name, type, dump, true);
	if (obj_cache == NULL)
		return -1;

	err = nftnl_obj_list_foreach(obj_cache, list_obj_cb, ctx);
	nftnl_obj_list_free(obj_cache);
	return err;
}

static struct flowtable *
netlink_delinearize_flowtable(struct netlink_ctx *ctx,
			      struct nftnl_flowtable *nlo)
{
	struct flowtable *flowtable;
	const char * const *dev_array;
	int len = 0, i;

	flowtable = flowtable_alloc(&netlink_location);
	flowtable->handle.family =
		nftnl_flowtable_get_u32(nlo, NFTNL_FLOWTABLE_FAMILY);
	flowtable->handle.table.name =
		xstrdup(nftnl_flowtable_get_str(nlo, NFTNL_FLOWTABLE_TABLE));
	flowtable->handle.flowtable =
		xstrdup(nftnl_flowtable_get_str(nlo, NFTNL_FLOWTABLE_NAME));
	dev_array = nftnl_flowtable_get(nlo, NFTNL_FLOWTABLE_DEVICES);
	while (dev_array[len])
		len++;

	flowtable->dev_array = calloc(1, len * sizeof(char *));
	for (i = 0; i < len; i++)
		flowtable->dev_array[i] = xstrdup(dev_array[i]);

	flowtable->dev_array_len = len;

	flowtable->priority =
		nftnl_flowtable_get_u32(nlo, NFTNL_FLOWTABLE_PRIO);
	flowtable->hooknum =
		nftnl_flowtable_get_u32(nlo, NFTNL_FLOWTABLE_HOOKNUM);

	return flowtable;
}

static int list_flowtable_cb(struct nftnl_flowtable *nls, void *arg)
{
	struct netlink_ctx *ctx = arg;
	struct flowtable *flowtable;

	flowtable = netlink_delinearize_flowtable(ctx, nls);
	if (flowtable == NULL)
		return -1;
	list_add_tail(&flowtable->list, &ctx->list);
	return 0;
}

int netlink_list_flowtables(struct netlink_ctx *ctx, const struct handle *h)
{
	struct nftnl_flowtable_list *flowtable_cache;
	int err;

	flowtable_cache = mnl_nft_flowtable_dump(ctx, h->family, h->table.name);
	if (flowtable_cache == NULL) {
		if (errno == EINTR)
			return -1;

		return 0;
	}

	err = nftnl_flowtable_list_foreach(flowtable_cache, list_flowtable_cb, ctx);
	nftnl_flowtable_list_free(flowtable_cache);
	return err;
}

int netlink_batch_send(struct netlink_ctx *ctx, struct list_head *err_list)
{
	return mnl_batch_talk(ctx, err_list);
}

int netlink_flush_ruleset(struct netlink_ctx *ctx, const struct cmd *cmd)
{
	struct nftnl_table *nlt;
	int err;

	nlt = alloc_nftnl_table(&cmd->handle);
	err = mnl_nft_table_batch_del(nlt, ctx->batch, 0, ctx->seqnum);
	nftnl_table_free(nlt);

	return err;
}

struct nftnl_ruleset *netlink_dump_ruleset(struct netlink_ctx *ctx,
					 const struct handle *h,
					 const struct location *loc)
{
	return mnl_nft_ruleset_dump(ctx, h->family);
}

static void trace_print_hdr(const struct nftnl_trace *nlt,
			    struct output_ctx *octx)
{
	nft_print(octx, "trace id %08x %s ",
		  nftnl_trace_get_u32(nlt, NFTNL_TRACE_ID),
		  family2str(nftnl_trace_get_u32(nlt, NFTNL_TRACE_FAMILY)));
	if (nftnl_trace_is_set(nlt, NFTNL_TRACE_TABLE))
		nft_print(octx, "%s ",
			  nftnl_trace_get_str(nlt, NFTNL_TRACE_TABLE));
	if (nftnl_trace_is_set(nlt, NFTNL_TRACE_CHAIN))
		nft_print(octx, "%s ",
			  nftnl_trace_get_str(nlt, NFTNL_TRACE_CHAIN));
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
	nft_print(octx, " ");
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
	h.table.name  = nftnl_trace_get_str(nlt, NFTNL_TRACE_TABLE);
	h.chain.name  = nftnl_trace_get_str(nlt, NFTNL_TRACE_CHAIN);

	if (!h.table.name)
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

	trace_print_hdr(nlt, octx);
	nft_print(octx, "rule ");
	rule_print(rule, octx);
	nft_print(octx, " (");
	trace_print_verdict(nlt, octx);
	nft_print(octx, ")\n");
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
		relational_expr_pctx_update(ctx, rel);
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
			payload_dependency_kill(pctx, lhs, ctx->family);
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

	trace_print_hdr(nlt, octx);

	nft_print(octx, "packet: ");
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
		nft_print(octx, " ");
		stmt_free(stmt);
	}
	nft_print(octx, "\n");
}

int netlink_events_trace_cb(const struct nlmsghdr *nlh, int type,
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
		trace_print_hdr(nlt, monh->ctx->octx);

		if (nftnl_trace_is_set(nlt, NFTNL_TRACE_VERDICT)) {
			trace_print_verdict(nlt, monh->ctx->octx);
			nft_mon_print(monh, " ");
		}

		if (nftnl_trace_is_set(nlt, NFTNL_TRACE_MARK))
			trace_print_expr(nlt, NFTNL_TRACE_MARK,
					 meta_expr_alloc(&netlink_location,
							 NFT_META_MARK),
					 monh->ctx->octx);
		nft_mon_print(monh, "\n");
		break;
	}

	nftnl_trace_free(nlt);
	return MNL_CB_OK;
}

static int netlink_markup_setelems(const struct nftnl_parse_ctx *ctx)
{
	const struct ruleset_parse *rp;
	struct nftnl_set *set;
	uint32_t cmd;
	int ret = -1;

	set = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_SET);
	rp = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_DATA);

	cmd = nftnl_ruleset_ctx_get_u32(ctx, NFTNL_RULESET_CTX_CMD);
	switch (cmd) {
	case NFTNL_CMD_ADD:
		ret = mnl_nft_setelem_batch_add(set, rp->nl_ctx->batch,
						0, rp->nl_ctx->seqnum);
		break;
	case NFTNL_CMD_DELETE:
		ret = mnl_nft_setelem_batch_del(set, rp->nl_ctx->batch,
						0, rp->nl_ctx->seqnum);
		break;
	default:
		errno = EOPNOTSUPP;
		break;
	}

	return ret;
}

static int netlink_markup_set(const struct nftnl_parse_ctx *ctx)
{
	const struct ruleset_parse *rp;
	struct nftnl_set *set;
	uint32_t cmd;
	int ret = -1;

	set = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_SET);
	rp = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_DATA);

	cmd = nftnl_ruleset_ctx_get_u32(ctx, NFTNL_RULESET_CTX_CMD);
	switch (cmd) {
	case NFTNL_CMD_ADD:
		ret = mnl_nft_set_batch_add(set, rp->nl_ctx->batch, NLM_F_EXCL,
					    rp->nl_ctx->seqnum);
		break;
	case NFTNL_CMD_DELETE:
		ret = mnl_nft_set_batch_del(set, rp->nl_ctx->batch,
					    0, rp->nl_ctx->seqnum);
		break;
	default:
		errno = EOPNOTSUPP;
		break;
	}

	if (ret < 0)
		return ret;

	return netlink_markup_setelems(ctx);
}

static int netlink_markup_build_rule(const struct nftnl_parse_ctx *ctx,
				      uint32_t cmd, struct nftnl_rule *rule)
{
	const struct ruleset_parse *rp;
	uint32_t nl_flags;
	int ret = -1;

	rp = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_DATA);

	switch (cmd) {
	case NFTNL_CMD_ADD:
		nl_flags = NLM_F_APPEND | NLM_F_CREATE;
		nftnl_rule_unset(rule, NFTNL_RULE_HANDLE);
		ret = mnl_nft_rule_batch_add(rule, rp->nl_ctx->batch, nl_flags,
					     rp->nl_ctx->seqnum);
		break;
	case NFTNL_CMD_DELETE:
		ret = mnl_nft_rule_batch_del(rule, rp->nl_ctx->batch,
					     0, rp->nl_ctx->seqnum);
		break;
	case NFTNL_CMD_REPLACE:
		nl_flags = NLM_F_REPLACE;
		ret = mnl_nft_rule_batch_add(rule, rp->nl_ctx->batch, nl_flags,
					     rp->nl_ctx->seqnum);
		break;
	case NFTNL_CMD_INSERT:
		nl_flags = NLM_F_CREATE;
		nftnl_rule_unset(rule, NFTNL_RULE_HANDLE);
		ret = mnl_nft_rule_batch_add(rule, rp->nl_ctx->batch, nl_flags,
					     rp->nl_ctx->seqnum);
		break;
	default:
		errno = EOPNOTSUPP;
		break;
	}

	return ret;

}

static int netlink_markup_rule(const struct nftnl_parse_ctx *ctx)
{
	struct nftnl_rule *rule;
	uint32_t cmd;

	cmd = nftnl_ruleset_ctx_get_u32(ctx, NFTNL_RULESET_CTX_CMD);
	rule = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_RULE);

	return netlink_markup_build_rule(ctx, cmd, rule);
}

static int netlink_markup_build_flush(const struct nftnl_parse_ctx *ctx)
{
	struct nftnl_rule *rule;
	struct nftnl_table *table;
	struct nftnl_chain *chain;
	const char  *table_get_name, *table_get_family;
	const char *chain_get_table, *chain_get_name, *chain_get_family;
	uint32_t type;
	int ret = -1;

	rule = nftnl_rule_alloc();
	if (rule == NULL)
		return -1;

	type = nftnl_ruleset_ctx_get_u32(ctx, NFTNL_RULESET_CTX_TYPE);
	switch (type) {
	case NFTNL_RULESET_TABLE:
		table = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_TABLE);
		table_get_name = nftnl_table_get(table, NFTNL_TABLE_NAME);
		table_get_family = nftnl_table_get(table, NFTNL_TABLE_FAMILY);

		nftnl_rule_set(rule, NFTNL_RULE_TABLE, table_get_name);
		nftnl_rule_set(rule, NFTNL_RULE_FAMILY, table_get_family);
		break;
	case NFTNL_RULESET_CHAIN:
		chain = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_CHAIN);
		chain_get_table = nftnl_chain_get(chain, NFTNL_CHAIN_TABLE);
		chain_get_name = nftnl_chain_get(chain, NFTNL_CHAIN_NAME);
		chain_get_family = nftnl_chain_get(chain, NFTNL_TABLE_FAMILY);

		nftnl_rule_set(rule, NFTNL_RULE_TABLE, chain_get_table);
		nftnl_rule_set(rule, NFTNL_RULE_CHAIN, chain_get_name);
		nftnl_rule_set(rule, NFTNL_RULE_FAMILY, chain_get_family);
		break;
	default:
		errno = EOPNOTSUPP;
		goto err;
	}

	ret = netlink_markup_build_rule(ctx, NFTNL_CMD_DELETE, rule);
err:
	nftnl_rule_free(rule);
	return ret;
}

static int netlink_markup_chain(const struct nftnl_parse_ctx *ctx)
{
	const struct ruleset_parse *rp;
	struct nftnl_chain *chain;
	uint32_t cmd;
	int ret = -1;

	chain = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_CHAIN);
	rp = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_DATA);

	nftnl_chain_unset(chain, NFTNL_CHAIN_HANDLE);

	cmd = nftnl_ruleset_ctx_get_u32(ctx, NFTNL_RULESET_CTX_CMD);
	switch (cmd) {
	case NFTNL_CMD_ADD:
		ret = mnl_nft_chain_batch_add(chain, rp->nl_ctx->batch,
					      0, rp->nl_ctx->seqnum);
		break;
	case NFTNL_CMD_DELETE:
		ret = mnl_nft_chain_batch_del(chain, rp->nl_ctx->batch,
					      0, rp->nl_ctx->seqnum);
		break;
	case NFTNL_CMD_FLUSH:
		ret = netlink_markup_build_flush(ctx);
		break;
	default:
		errno = EOPNOTSUPP;
		break;
	}

	return ret;
}


static int netlink_markup_build_table(const struct nftnl_parse_ctx *ctx,
				       uint32_t cmd, struct nftnl_table *table)
{
	struct ruleset_parse *rp;
	int ret = -1;

	rp = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_DATA);

	switch (cmd) {
	case NFTNL_CMD_ADD:
		ret = mnl_nft_table_batch_add(table, rp->nl_ctx->batch,
					      0, rp->nl_ctx->seqnum);
		break;
	case NFTNL_CMD_DELETE:
		ret = mnl_nft_table_batch_del(table, rp->nl_ctx->batch,
					      0, rp->nl_ctx->seqnum);
		break;
	case NFTNL_CMD_FLUSH:
		ret = netlink_markup_build_flush(ctx);
		break;
	default:
		errno = EOPNOTSUPP;
		break;
	}

	return ret;
}

static int netlink_markup_table(const struct nftnl_parse_ctx *ctx)
{
	struct nftnl_table *table;
	uint32_t cmd;

	cmd = nftnl_ruleset_ctx_get_u32(ctx, NFTNL_RULESET_CTX_CMD);
	table = nftnl_ruleset_ctx_get(ctx, NFTNL_RULESET_CTX_TABLE);

	return netlink_markup_build_table(ctx, cmd, table);
}

static int netlink_markup_flush(const struct nftnl_parse_ctx *ctx)
{
	struct nftnl_table *table;
	int ret;

	table = nftnl_table_alloc();
	if (table == NULL)
		return -1;

	ret = netlink_markup_build_table(ctx, NFTNL_CMD_DELETE, table);
	nftnl_table_free(table);

	return ret;
}

int netlink_markup_parse_cb(const struct nftnl_parse_ctx *ctx)
{
	uint32_t type;
	int ret = -1;

	type = nftnl_ruleset_ctx_get_u32(ctx, NFTNL_RULESET_CTX_TYPE);
	switch (type) {
	case NFTNL_RULESET_TABLE:
		ret = netlink_markup_table(ctx);
		break;
	case NFTNL_RULESET_CHAIN:
		ret = netlink_markup_chain(ctx);
		break;
	case NFTNL_RULESET_RULE:
		ret = netlink_markup_rule(ctx);
		break;
	case NFTNL_RULESET_SET:
		ret = netlink_markup_set(ctx);
		break;
	case NFTNL_RULESET_SET_ELEMS:
		ret = netlink_markup_setelems(ctx);
		break;
	case NFTNL_RULESET_RULESET:
		ret = netlink_markup_flush(ctx);
		break;
	default:
		errno = EOPNOTSUPP;
		break;
	}

	nftnl_ruleset_ctx_free(ctx);

	return ret;
}
