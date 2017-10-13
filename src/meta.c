/*
 * Meta expression/statement related definition and types.
 *
 * Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <pwd.h>
#include <grp.h>
#include <arpa/inet.h>
#include <linux/netfilter.h>
#include <linux/pkt_sched.h>
#include <linux/if_packet.h>

#include <nftables.h>
#include <expression.h>
#include <statement.h>
#include <datatype.h>
#include <meta.h>
#include <gmputil.h>
#include <utils.h>
#include <erec.h>
#include <iface.h>

static struct symbol_table *realm_tbl;
void realm_table_meta_init(void)
{
	realm_tbl = rt_symbol_table_init("/etc/iproute2/rt_realms");
}

void realm_table_meta_exit(void)
{
	rt_symbol_table_free(realm_tbl);
}

static void tchandle_type_print(const struct expr *expr,
				struct output_ctx *octx)
{
	uint32_t handle = mpz_get_uint32(expr->value);

	switch(handle) {
	case TC_H_ROOT:
		nft_print(octx, "root");
		break;
	case TC_H_UNSPEC:
		nft_print(octx, "none");
		break;
	default:
		nft_print(octx, "%0x:%0x",
			  TC_H_MAJ(handle) >> 16,
			  TC_H_MIN(handle));
		break;
	}
}

static struct error_record *tchandle_type_parse(const struct expr *sym,
						struct expr **res)
{
	uint32_t handle;
	char *str = NULL;

	if (strcmp(sym->identifier, "root") == 0)
		handle = TC_H_ROOT;
	else if (strcmp(sym->identifier, "none") == 0)
		handle = TC_H_UNSPEC;
	else if (strchr(sym->identifier, ':')) {
		uint16_t tmp;
		char *colon;

		str = xstrdup(sym->identifier);

		colon = strchr(str, ':');
		if (!colon)
			goto err;

		*colon = '\0';

		errno = 0;
		tmp = strtoull(str, NULL, 16);
		if (errno != 0)
			goto err;

		handle = (tmp << 16);
		if (str[strlen(str) - 1] == ':')
			goto out;

		errno = 0;
		tmp = strtoull(colon + 1, NULL, 16);
		if (errno != 0)
			goto err;

		handle |= tmp;
	} else {
		handle = strtoull(sym->identifier, NULL, 0);
	}
out:
	xfree(str);
	*res = constant_expr_alloc(&sym->location, sym->dtype,
				   BYTEORDER_HOST_ENDIAN,
				   sizeof(handle) * BITS_PER_BYTE, &handle);
	return NULL;
err:
	xfree(str);
	return error(&sym->location, "Could not parse %s", sym->dtype->desc);
}

const struct datatype tchandle_type = {
	.type		= TYPE_CLASSID,
	.name		= "classid",
	.desc		= "TC classid",
	.byteorder	= BYTEORDER_HOST_ENDIAN,
	.size		= 4 * BITS_PER_BYTE,
	.basetype	= &integer_type,
	.print		= tchandle_type_print,
	.parse		= tchandle_type_parse,
};

static void ifindex_type_print(const struct expr *expr, struct output_ctx *octx)
{
	char name[IFNAMSIZ];
	int ifindex;

	ifindex = mpz_get_uint32(expr->value);
	if (nft_if_indextoname(ifindex, name))
		nft_print(octx, "\"%s\"", name);
	else
		nft_print(octx, "%d", ifindex);
}

static struct error_record *ifindex_type_parse(const struct expr *sym,
					       struct expr **res)
{
	int ifindex;

	ifindex = nft_if_nametoindex(sym->identifier);
	if (ifindex == 0) {
		char *end;
		long res;

		errno = 0;
		res = strtol(sym->identifier, &end, 10);

		if (res < 0 || res > INT_MAX || *end || errno)
			return error(&sym->location, "Interface does not exist");

		ifindex = (int)res;
	}

	*res = constant_expr_alloc(&sym->location, sym->dtype,
				   BYTEORDER_HOST_ENDIAN,
				   sizeof(ifindex) * BITS_PER_BYTE, &ifindex);
	return NULL;
}

const struct datatype ifindex_type = {
	.type		= TYPE_IFINDEX,
	.name		= "iface_index",
	.desc		= "network interface index",
	.byteorder	= BYTEORDER_HOST_ENDIAN,
	.size		= 4 * BITS_PER_BYTE,
	.basetype	= &integer_type,
	.print		= ifindex_type_print,
	.parse		= ifindex_type_parse,
};

static const struct symbol_table arphrd_tbl = {
	.base		= BASE_HEXADECIMAL,
	.symbols	= {
		SYMBOL("ether",		ARPHRD_ETHER),
		SYMBOL("ppp",		ARPHRD_PPP),
		/* dummy types */
		SYMBOL("ipip",		ARPHRD_TUNNEL),
		SYMBOL("ipip6",		ARPHRD_TUNNEL6),
		SYMBOL("loopback",	ARPHRD_LOOPBACK),
		SYMBOL("sit",		ARPHRD_SIT),
		SYMBOL("ipgre",		ARPHRD_IPGRE),
		SYMBOL_LIST_END,
	},
};

const struct datatype arphrd_type = {
	.type		= TYPE_ARPHRD,
	.name		= "iface_type",
	.desc		= "network interface type",
	.byteorder	= BYTEORDER_HOST_ENDIAN,
	.size		= 2 * BITS_PER_BYTE,
	.basetype	= &integer_type,
	.sym_tbl	= &arphrd_tbl,
};

static void uid_type_print(const struct expr *expr, struct output_ctx *octx)
{
	struct passwd *pw;

	if (octx->numeric < NUMERIC_ALL) {
		uint32_t uid = mpz_get_uint32(expr->value);

		pw = getpwuid(uid);
		if (pw != NULL)
			nft_print(octx, "\"%s\"", pw->pw_name);
		else
			nft_print(octx, "%d", uid);
		return;
	}
	expr_basetype(expr)->print(expr, octx);
}

static struct error_record *uid_type_parse(const struct expr *sym,
					   struct expr **res)
{
	struct passwd *pw;
	uint64_t uid;
	char *endptr = NULL;

	pw = getpwnam(sym->identifier);
	if (pw != NULL)
		uid = pw->pw_uid;
	else {
		uid = strtoull(sym->identifier, &endptr, 10);
		if (uid > UINT32_MAX)
			return error(&sym->location, "Value too large");
		else if (*endptr)
			return error(&sym->location, "User does not exist");
	}

	*res = constant_expr_alloc(&sym->location, sym->dtype,
				   BYTEORDER_HOST_ENDIAN,
				   sizeof(pw->pw_uid) * BITS_PER_BYTE, &uid);
	return NULL;
}

const struct datatype uid_type = {
	.type		= TYPE_UID,
	.name		= "uid",
	.desc		= "user ID",
	.byteorder	= BYTEORDER_HOST_ENDIAN,
	.size		= sizeof(uid_t) * BITS_PER_BYTE,
	.basetype	= &integer_type,
	.print		= uid_type_print,
	.parse		= uid_type_parse,
};

static void gid_type_print(const struct expr *expr, struct output_ctx *octx)
{
	struct group *gr;

	if (octx->numeric < NUMERIC_ALL) {
		uint32_t gid = mpz_get_uint32(expr->value);

		gr = getgrgid(gid);
		if (gr != NULL)
			nft_print(octx, "\"%s\"", gr->gr_name);
		else
			nft_print(octx, "%u", gid);
		return;
	}
	expr_basetype(expr)->print(expr, octx);
}

static struct error_record *gid_type_parse(const struct expr *sym,
					   struct expr **res)
{
	struct group *gr;
	uint64_t gid;
	char *endptr = NULL;

	gr = getgrnam(sym->identifier);
	if (gr != NULL)
		gid = gr->gr_gid;
	else {
		gid = strtoull(sym->identifier, &endptr, 0);
		if (gid > UINT32_MAX)
			return error(&sym->location, "Value too large");
		else if (*endptr)
			return error(&sym->location, "Group does not exist");
	}

	*res = constant_expr_alloc(&sym->location, sym->dtype,
				   BYTEORDER_HOST_ENDIAN,
				   sizeof(gr->gr_gid) * BITS_PER_BYTE, &gid);
	return NULL;
}

const struct datatype gid_type = {
	.type		= TYPE_GID,
	.name		= "gid",
	.desc		= "group ID",
	.byteorder	= BYTEORDER_HOST_ENDIAN,
	.size		= sizeof(gid_t) * BITS_PER_BYTE,
	.basetype	= &integer_type,
	.print		= gid_type_print,
	.parse		= gid_type_parse,
};

static const struct symbol_table pkttype_type_tbl = {
	.base		= BASE_DECIMAL,
	.symbols	= {
		SYMBOL("host", PACKET_HOST),
		SYMBOL("unicast", PACKET_HOST), /* backwards compat */
		SYMBOL("broadcast", PACKET_BROADCAST),
		SYMBOL("multicast", PACKET_MULTICAST),
		SYMBOL("other", PACKET_OTHERHOST),
		SYMBOL_LIST_END,
	},
};

static void pkttype_type_print(const struct expr *expr, struct output_ctx *octx)
{
	return symbolic_constant_print(&pkttype_type_tbl, expr, false, octx);
}

const struct datatype pkttype_type = {
	.type		= TYPE_PKTTYPE,
	.name		= "pkt_type",
	.desc		= "packet type",
	.byteorder	= BYTEORDER_HOST_ENDIAN,
	.size		= BITS_PER_BYTE,
	.basetype	= &integer_type,
	.print		= pkttype_type_print,
	.sym_tbl	= &pkttype_type_tbl,
};

static struct symbol_table *devgroup_tbl;
void devgroup_table_init(void)
{
	devgroup_tbl = rt_symbol_table_init("/etc/iproute2/group");
}

void devgroup_table_exit(void)
{
	rt_symbol_table_free(devgroup_tbl);
}

static void devgroup_type_print(const struct expr *expr,
				 struct output_ctx *octx)
{
	return symbolic_constant_print(devgroup_tbl, expr, true, octx);
}

static struct error_record *devgroup_type_parse(const struct expr *sym,
						struct expr **res)
{
	return symbolic_constant_parse(sym, devgroup_tbl, res);
}

const struct datatype devgroup_type = {
	.type		= TYPE_DEVGROUP,
	.name		= "devgroup",
	.desc		= "devgroup name",
	.byteorder	= BYTEORDER_HOST_ENDIAN,
	.size		= 4 * BITS_PER_BYTE,
	.basetype	= &integer_type,
	.print		= devgroup_type_print,
	.parse		= devgroup_type_parse,
	.flags		= DTYPE_F_PREFIX,
};

static const struct meta_template meta_templates[] = {
	[NFT_META_LEN]		= META_TEMPLATE("length",    &integer_type,
						4 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_PROTOCOL]	= META_TEMPLATE("protocol",  &ethertype_type,
						2 * 8, BYTEORDER_BIG_ENDIAN),
	[NFT_META_NFPROTO]	= META_TEMPLATE("nfproto",   &nfproto_type,
						1 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_L4PROTO]	= META_TEMPLATE("l4proto",   &inet_protocol_type,
						1 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_PRIORITY]	= META_TEMPLATE("priority",  &tchandle_type,
						4 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_MARK]		= META_TEMPLATE("mark",      &mark_type,
						4 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_IIF]		= META_TEMPLATE("iif",       &ifindex_type,
						4 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_IIFNAME]	= META_TEMPLATE("iifname",   &string_type,
						IFNAMSIZ * BITS_PER_BYTE,
						BYTEORDER_HOST_ENDIAN),
	[NFT_META_IIFTYPE]	= META_TEMPLATE("iiftype",   &arphrd_type,
						2 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_OIF]		= META_TEMPLATE("oif",	     &ifindex_type,
						4 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_OIFNAME]	= META_TEMPLATE("oifname",   &string_type,
						IFNAMSIZ * BITS_PER_BYTE,
						BYTEORDER_HOST_ENDIAN),
	[NFT_META_OIFTYPE]	= META_TEMPLATE("oiftype",   &arphrd_type,
						2 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_SKUID]	= META_TEMPLATE("skuid",     &uid_type,
						4 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_SKGID]	= META_TEMPLATE("skgid",     &gid_type,
						4 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_NFTRACE]	= META_TEMPLATE("nftrace",   &integer_type,
						1    , BYTEORDER_HOST_ENDIAN),
	[NFT_META_RTCLASSID]	= META_TEMPLATE("rtclassid", &realm_type,
						4 * 8, BYTEORDER_HOST_ENDIAN),
	[NFT_META_BRI_IIFNAME]	= META_TEMPLATE("ibriport",  &string_type,
						IFNAMSIZ * BITS_PER_BYTE,
						BYTEORDER_HOST_ENDIAN),
	[NFT_META_BRI_OIFNAME]	= META_TEMPLATE("obriport",  &string_type,
						IFNAMSIZ * BITS_PER_BYTE,
						BYTEORDER_HOST_ENDIAN),
	[NFT_META_PKTTYPE]	= META_TEMPLATE("pkttype",   &pkttype_type,
						BITS_PER_BYTE,
						BYTEORDER_HOST_ENDIAN),
	[NFT_META_CPU]		= META_TEMPLATE("cpu",	     &integer_type,
						4 * BITS_PER_BYTE,
						BYTEORDER_HOST_ENDIAN),
	[NFT_META_IIFGROUP]	= META_TEMPLATE("iifgroup",  &devgroup_type,
						4 * BITS_PER_BYTE,
						BYTEORDER_HOST_ENDIAN),
	[NFT_META_OIFGROUP]	= META_TEMPLATE("oifgroup",  &devgroup_type,
						4 * BITS_PER_BYTE,
						BYTEORDER_HOST_ENDIAN),
	[NFT_META_CGROUP]	= META_TEMPLATE("cgroup",    &integer_type,
						4 * BITS_PER_BYTE,
						BYTEORDER_HOST_ENDIAN),
	[NFT_META_PRANDOM]	= META_TEMPLATE("random",    &integer_type,
						4 * BITS_PER_BYTE,
						BYTEORDER_BIG_ENDIAN), /* avoid conversion; doesn't have endianess */
};

static bool meta_key_is_qualified(enum nft_meta_keys key)
{
	switch (key) {
	case NFT_META_LEN:
	case NFT_META_NFPROTO:
	case NFT_META_L4PROTO:
	case NFT_META_PROTOCOL:
	case NFT_META_PRIORITY:
	case NFT_META_PRANDOM:
		return true;
	default:
		return false;
	}
}

static void meta_expr_print(const struct expr *expr, struct output_ctx *octx)
{
	if (meta_key_is_qualified(expr->meta.key))
		nft_print(octx, "meta %s",
			  meta_templates[expr->meta.key].token);
	else
		nft_print(octx, "%s",
			  meta_templates[expr->meta.key].token);
}

static bool meta_expr_cmp(const struct expr *e1, const struct expr *e2)
{
	return e1->meta.key == e2->meta.key;
}

static void meta_expr_clone(struct expr *new, const struct expr *expr)
{
	new->meta.key = expr->meta.key;
	new->meta.base = expr->meta.base;
}

/**
 * meta_expr_pctx_update - update protocol context based on meta match
 *
 * @ctx:	protocol context
 * @expr:	relational meta expression
 *
 * Update LL protocol context based on IIFTYPE meta match in non-LL hooks.
 */
static void meta_expr_pctx_update(struct proto_ctx *ctx,
				  const struct expr *expr)
{
	const struct hook_proto_desc *h = &hook_proto_desc[ctx->family];
	const struct expr *left = expr->left, *right = expr->right;
	const struct proto_desc *desc;
	uint8_t protonum;

	assert(expr->op == OP_EQ);

	switch (left->meta.key) {
	case NFT_META_IIFTYPE:
		if (h->base < PROTO_BASE_NETWORK_HDR &&
		    ctx->family != NFPROTO_INET &&
		    ctx->family != NFPROTO_NETDEV)
			return;

		desc = proto_dev_desc(mpz_get_uint16(right->value));
		if (desc == NULL)
			desc = &proto_unknown;

		proto_ctx_update(ctx, PROTO_BASE_LL_HDR, &expr->location, desc);
		break;
	case NFT_META_NFPROTO:
		protonum = mpz_get_uint8(right->value);
		desc = proto_find_upper(h->desc, protonum);
		if (desc == NULL) {
			desc = &proto_unknown;

			if (protonum == ctx->family &&
			    h->base == PROTO_BASE_NETWORK_HDR)
				desc = h->desc;
		}

		proto_ctx_update(ctx, PROTO_BASE_NETWORK_HDR, &expr->location, desc);
		break;
	case NFT_META_L4PROTO:
		desc = proto_find_upper(&proto_inet_service,
					mpz_get_uint8(right->value));
		if (desc == NULL)
			desc = &proto_unknown;

		proto_ctx_update(ctx, PROTO_BASE_TRANSPORT_HDR, &expr->location, desc);
		break;
	case NFT_META_PROTOCOL:
		if (h->base < PROTO_BASE_NETWORK_HDR && ctx->family != NFPROTO_NETDEV)
			return;

		desc = proto_find_upper(h->desc, ntohs(mpz_get_uint16(right->value)));
		if (desc == NULL)
			desc = &proto_unknown;

		proto_ctx_update(ctx, PROTO_BASE_NETWORK_HDR, &expr->location, desc);
		break;
	default:
		break;
	}
}

static const struct expr_ops meta_expr_ops = {
	.type		= EXPR_META,
	.name		= "meta",
	.print		= meta_expr_print,
	.cmp		= meta_expr_cmp,
	.clone		= meta_expr_clone,
	.pctx_update	= meta_expr_pctx_update,
};

struct expr *meta_expr_alloc(const struct location *loc, enum nft_meta_keys key)
{
	const struct meta_template *tmpl = &meta_templates[key];
	struct expr *expr;

	expr = expr_alloc(loc, &meta_expr_ops, tmpl->dtype,
			  tmpl->byteorder, tmpl->len);
	expr->meta.key = key;

	switch (key) {
	case NFT_META_IIFTYPE:
		expr->flags |= EXPR_F_PROTOCOL;
		break;
	case NFT_META_NFPROTO:
		expr->flags |= EXPR_F_PROTOCOL;
		expr->meta.base = PROTO_BASE_LL_HDR;
		break;
	case NFT_META_L4PROTO:
		expr->flags |= EXPR_F_PROTOCOL;
		expr->meta.base = PROTO_BASE_NETWORK_HDR;
		break;
	case NFT_META_PROTOCOL:
		expr->flags |= EXPR_F_PROTOCOL;
		expr->meta.base = PROTO_BASE_LL_HDR;
		break;
	default:
		break;
	}

	return expr;
}

static void meta_stmt_print(const struct stmt *stmt, struct output_ctx *octx)
{
	if (meta_key_is_qualified(stmt->meta.key))
		nft_print(octx, "meta %s set ",
			  meta_templates[stmt->meta.key].token);
	else
		nft_print(octx, "%s set ",
			  meta_templates[stmt->meta.key].token);

	expr_print(stmt->meta.expr, octx);
}

static const struct stmt_ops meta_stmt_ops = {
	.type		= STMT_META,
	.name		= "meta",
	.print		= meta_stmt_print,
};

struct stmt *meta_stmt_alloc(const struct location *loc, enum nft_meta_keys key,
			     struct expr *expr)
{
	struct stmt *stmt;

	stmt = stmt_alloc(loc, &meta_stmt_ops);
	stmt->meta.key	= key;
	stmt->meta.tmpl	= &meta_templates[key];
	stmt->meta.expr	= expr;
	return stmt;
}

/*
 * @expr:	payload expression
 * @res:	dependency expression
 *
 * Generate a NFT_META_IIFTYPE expression to check for ethernet frames.
 * Only works on input path.
 */
struct stmt *meta_stmt_meta_iiftype(const struct location *loc, uint16_t type)
{
	struct expr *dep, *left, *right;

	left = meta_expr_alloc(loc, NFT_META_IIFTYPE);
	right = constant_expr_alloc(loc, &arphrd_type,
				    BYTEORDER_HOST_ENDIAN,
				    2 * BITS_PER_BYTE, &type);

	dep = relational_expr_alloc(loc, OP_EQ, left, right);
	return expr_stmt_alloc(&dep->location, dep);
}

struct error_record *meta_key_parse(const struct location *loc,
                                    const char *str,
                                    unsigned int *value)
{
	int ret, len, offset = 0;
	const char *sep = "";
	unsigned int i;
	char buf[1024];
	size_t size;

	for (i = 0; i < array_size(meta_templates); i++) {
		if (!meta_templates[i].token || strcmp(meta_templates[i].token, str))
			continue;

		*value = i;
		return NULL;
	}

	len = (int)sizeof(buf);
	size = sizeof(buf);

	for (i = 0; i < array_size(meta_templates); i++) {
		if (!meta_templates[i].token)
			continue;

		if (offset)
			sep = ", ";

		ret = snprintf(buf+offset, len, "%s%s", sep, meta_templates[i].token);
		SNPRINTF_BUFFER_SIZE(ret, size, len, offset);
		assert(offset < (int)sizeof(buf));
	}

	return error(loc, "syntax error, unexpected %s, known keys are %s", str, buf);
}
