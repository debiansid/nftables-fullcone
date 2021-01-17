/*
 * Copyright (c) 2008-2012 Patrick McHardy <kaber@trash.net>
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
#include <inttypes.h>
#include <errno.h>

#include <statement.h>
#include <rule.h>
#include <utils.h>
#include <netdb.h>
#include <netlink.h>
#include <mnl.h>
#include <misspell.h>
#include <json.h>
#include <cache.h>

#include <libnftnl/common.h>
#include <libnftnl/ruleset.h>
#include <netinet/ip.h>
#include <linux/netfilter.h>
#include <linux/netfilter_arp.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter/nf_synproxy.h>
#include <net/if.h>
#include <linux/netfilter_bridge.h>

static const char *const tcp_state_to_name[] = {
	[NFTNL_CTTIMEOUT_TCP_SYN_SENT]		= "syn_sent",
	[NFTNL_CTTIMEOUT_TCP_SYN_RECV]		= "syn_recv",
	[NFTNL_CTTIMEOUT_TCP_ESTABLISHED]	= "established",
	[NFTNL_CTTIMEOUT_TCP_FIN_WAIT]		= "fin_wait",
	[NFTNL_CTTIMEOUT_TCP_CLOSE_WAIT]	= "close_wait",
	[NFTNL_CTTIMEOUT_TCP_LAST_ACK]		= "last_ack",
	[NFTNL_CTTIMEOUT_TCP_TIME_WAIT]		= "time_wait",
	[NFTNL_CTTIMEOUT_TCP_CLOSE]		= "close",
	[NFTNL_CTTIMEOUT_TCP_SYN_SENT2]		= "syn_sent2",
	[NFTNL_CTTIMEOUT_TCP_RETRANS]		= "retrans",
	[NFTNL_CTTIMEOUT_TCP_UNACK]		= "unack",
};

static const char *const udp_state_to_name[] = {
	[NFTNL_CTTIMEOUT_UDP_UNREPLIED]		= "unreplied",
	[NFTNL_CTTIMEOUT_UDP_REPLIED]		= "replied",
};

static uint32_t tcp_dflt_timeout[] = {
	[NFTNL_CTTIMEOUT_TCP_SYN_SENT]		= 120,
	[NFTNL_CTTIMEOUT_TCP_SYN_RECV]		= 60,
	[NFTNL_CTTIMEOUT_TCP_ESTABLISHED]	= 432000,
	[NFTNL_CTTIMEOUT_TCP_FIN_WAIT]		= 120,
	[NFTNL_CTTIMEOUT_TCP_CLOSE_WAIT]	= 60,
	[NFTNL_CTTIMEOUT_TCP_LAST_ACK]		= 30,
	[NFTNL_CTTIMEOUT_TCP_TIME_WAIT]		= 120,
	[NFTNL_CTTIMEOUT_TCP_CLOSE]		= 10,
	[NFTNL_CTTIMEOUT_TCP_SYN_SENT2]		= 120,
	[NFTNL_CTTIMEOUT_TCP_RETRANS]		= 300,
	[NFTNL_CTTIMEOUT_TCP_UNACK]		= 300,
};

static uint32_t udp_dflt_timeout[] = {
	[NFTNL_CTTIMEOUT_UDP_UNREPLIED]		= 30,
	[NFTNL_CTTIMEOUT_UDP_REPLIED]		= 180,
};

struct timeout_protocol timeout_protocol[IPPROTO_MAX] = {
	[IPPROTO_TCP]	= {
		.array_size	= NFTNL_CTTIMEOUT_TCP_MAX,
		.state_to_name	= tcp_state_to_name,
		.dflt_timeout	= tcp_dflt_timeout,
	},
	[IPPROTO_UDP]	= {
		.array_size	= NFTNL_CTTIMEOUT_UDP_MAX,
		.state_to_name	= udp_state_to_name,
		.dflt_timeout	= udp_dflt_timeout,
	},
};

int timeout_str2num(uint16_t l4proto, struct timeout_state *ts)
{
	unsigned int i;

	for (i = 0; i < timeout_protocol[l4proto].array_size; i++) {
		if (!strcmp(timeout_protocol[l4proto].state_to_name[i], ts->timeout_str)) {
			ts->timeout_index = i;
			return 0;
		}
	}
	return -1;
}

void handle_free(struct handle *h)
{
	xfree(h->table.name);
	xfree(h->chain.name);
	xfree(h->set.name);
	xfree(h->flowtable.name);
	xfree(h->obj.name);
}

void handle_merge(struct handle *dst, const struct handle *src)
{
	if (dst->family == 0)
		dst->family = src->family;
	if (dst->table.name == NULL && src->table.name != NULL) {
		dst->table.name = xstrdup(src->table.name);
		dst->table.location = src->table.location;
	}
	if (dst->chain.name == NULL && src->chain.name != NULL) {
		dst->chain.name = xstrdup(src->chain.name);
		dst->chain.location = src->chain.location;
	}
	if (dst->set.name == NULL && src->set.name != NULL) {
		dst->set.name = xstrdup(src->set.name);
		dst->set.location = src->set.location;
	}
	if (dst->flowtable.name == NULL && src->flowtable.name != NULL)
		dst->flowtable.name = xstrdup(src->flowtable.name);
	if (dst->obj.name == NULL && src->obj.name != NULL)
		dst->obj.name = xstrdup(src->obj.name);
	if (dst->handle.id == 0)
		dst->handle = src->handle;
	if (dst->position.id == 0)
		dst->position = src->position;
	if (dst->index.id == 0)
		dst->index = src->index;
}

static int cache_init_tables(struct netlink_ctx *ctx, struct handle *h,
			     struct nft_cache *cache)
{
	int ret;

	ret = netlink_list_tables(ctx, h);
	if (ret < 0)
		return -1;

	list_splice_tail_init(&ctx->list, &cache->list);
	return 0;
}

static int cache_init_objects(struct netlink_ctx *ctx, unsigned int flags)
{
	struct nftnl_chain_list *chain_list = NULL;
	struct rule *rule, *nrule;
	struct table *table;
	struct chain *chain;
	struct set *set;
	int ret = 0;

	if (flags & NFT_CACHE_CHAIN_BIT) {
		chain_list = chain_cache_dump(ctx, &ret);
		if (!chain_list)
			return ret;
	}

	list_for_each_entry(table, &ctx->nft->cache.list, list) {
		if (flags & NFT_CACHE_SET_BIT) {
			ret = netlink_list_sets(ctx, &table->handle);
			list_splice_tail_init(&ctx->list, &table->sets);
			if (ret < 0)
				return -1;
		}
		if (flags & NFT_CACHE_SETELEM_BIT) {
			list_for_each_entry(set, &table->sets, list) {
				ret = netlink_list_setelems(ctx, &set->handle,
							    set);
				if (ret < 0)
					return -1;
			}
		}
		if (flags & NFT_CACHE_CHAIN_BIT) {
			ret = chain_cache_init(ctx, table, chain_list);
			if (ret < 0)
				return -1;
		}
		if (flags & NFT_CACHE_FLOWTABLE_BIT) {
			ret = netlink_list_flowtables(ctx, &table->handle);
			if (ret < 0)
				return -1;
			list_splice_tail_init(&ctx->list, &table->flowtables);
		}
		if (flags & NFT_CACHE_OBJECT_BIT) {
			ret = netlink_list_objs(ctx, &table->handle);
			if (ret < 0)
				return -1;
			list_splice_tail_init(&ctx->list, &table->objs);
		}

		if (flags & NFT_CACHE_RULE_BIT) {
			ret = netlink_list_rules(ctx, &table->handle);
			list_for_each_entry_safe(rule, nrule, &ctx->list, list) {
				chain = chain_cache_find(table, &rule->handle);
				if (!chain)
					chain = chain_binding_lookup(table,
							rule->handle.chain.name);
				list_move_tail(&rule->list, &chain->rules);
			}
			if (ret < 0)
				return -1;
		}
	}

	if (flags & NFT_CACHE_CHAIN_BIT)
		nftnl_chain_list_free(chain_list);

	return 0;
}

static int cache_init(struct netlink_ctx *ctx, unsigned int flags)
{
	struct handle handle = {
		.family = NFPROTO_UNSPEC,
	};
	int ret;

	if (flags == NFT_CACHE_EMPTY)
		return 0;

	/* assume NFT_CACHE_TABLE is always set. */
	ret = cache_init_tables(ctx, &handle, &ctx->nft->cache);
	if (ret < 0)
		return ret;
	ret = cache_init_objects(ctx, flags);
	if (ret < 0)
		return ret;

	return 0;
}

static bool cache_is_complete(struct nft_cache *cache, unsigned int flags)
{
	return (cache->flags & flags) == flags;
}

static bool cache_needs_refresh(struct nft_cache *cache)
{
	return cache->flags & NFT_CACHE_REFRESH;
}

static bool cache_is_updated(struct nft_cache *cache, uint16_t genid)
{
	return genid && genid == cache->genid;
}

bool cache_needs_update(struct nft_cache *cache)
{
	return cache->flags & NFT_CACHE_UPDATE;
}

int cache_update(struct nft_ctx *nft, unsigned int flags, struct list_head *msgs)
{
	struct netlink_ctx ctx = {
		.list		= LIST_HEAD_INIT(ctx.list),
		.nft		= nft,
		.msgs		= msgs,
	};
	struct nft_cache *cache = &nft->cache;
	uint32_t genid, genid_stop, oldflags;
	int ret;
replay:
	ctx.seqnum = cache->seqnum++;
	genid = mnl_genid_get(&ctx);
	if (!cache_needs_refresh(cache) &&
	    cache_is_complete(cache, flags) &&
	    cache_is_updated(cache, genid))
		return 0;

	if (cache->genid)
		cache_release(cache);

	if (flags & NFT_CACHE_FLUSHED) {
		oldflags = flags;
		flags = NFT_CACHE_EMPTY;
		if (oldflags & NFT_CACHE_UPDATE)
			flags |= NFT_CACHE_UPDATE;
		goto skip;
	}

	ret = cache_init(&ctx, flags);
	if (ret < 0) {
		cache_release(cache);
		if (errno == EINTR) {
			nft->nf_sock = nft_mnl_socket_reopen(nft->nf_sock);
			goto replay;
		}
		return -1;
	}

	genid_stop = mnl_genid_get(&ctx);
	if (genid != genid_stop) {
		cache_release(cache);
		goto replay;
	}
skip:
	cache->genid = genid;
	cache->flags = flags;
	return 0;
}

static void __cache_flush(struct list_head *table_list)
{
	struct table *table, *next;

	list_for_each_entry_safe(table, next, table_list, list) {
		list_del(&table->list);
		table_free(table);
	}
}

void cache_release(struct nft_cache *cache)
{
	__cache_flush(&cache->list);
	cache->genid = 0;
	cache->flags = NFT_CACHE_EMPTY;
}

/* internal ID to uniquely identify a set in the batch */
static uint32_t set_id;

struct set *set_alloc(const struct location *loc)
{
	struct set *set;

	set = xzalloc(sizeof(*set));
	set->refcnt = 1;
	set->handle.set_id = ++set_id;
	if (loc != NULL)
		set->location = *loc;

	init_list_head(&set->stmt_list);

	return set;
}

struct set *set_clone(const struct set *set)
{
	struct set *new_set;

	new_set			= set_alloc(NULL);
	handle_merge(&new_set->handle, &set->handle);
	new_set->flags		= set->flags;
	new_set->gc_int		= set->gc_int;
	new_set->timeout	= set->timeout;
	new_set->key		= expr_clone(set->key);
	if (set->data)
		new_set->data	= expr_clone(set->data);
	new_set->objtype	= set->objtype;
	new_set->policy		= set->policy;
	new_set->automerge	= set->automerge;
	new_set->desc		= set->desc;
	init_list_head(&new_set->stmt_list);

	return new_set;
}

struct set *set_get(struct set *set)
{
	set->refcnt++;
	return set;
}

void set_free(struct set *set)
{
	struct stmt *stmt, *next;

	if (--set->refcnt > 0)
		return;
	if (set->init != NULL)
		expr_free(set->init);
	if (set->comment)
		xfree(set->comment);
	handle_free(&set->handle);
	list_for_each_entry_safe(stmt, next, &set->stmt_list, list)
		stmt_free(stmt);
	expr_free(set->key);
	expr_free(set->data);
	xfree(set);
}

void set_add_hash(struct set *set, struct table *table)
{
	list_add_tail(&set->list, &table->sets);
}

struct set *set_lookup(const struct table *table, const char *name)
{
	struct set *set;

	list_for_each_entry(set, &table->sets, list) {
		if (!strcmp(set->handle.set.name, name))
			return set;
	}
	return NULL;
}

struct set *set_lookup_fuzzy(const char *set_name,
			     const struct nft_cache *cache,
			     const struct table **t)
{
	struct string_misspell_state st;
	struct table *table;
	struct set *set;

	string_misspell_init(&st);

	list_for_each_entry(table, &cache->list, list) {
		list_for_each_entry(set, &table->sets, list) {
			if (set_is_anonymous(set->flags))
				continue;
			if (!strcmp(set->handle.set.name, set_name)) {
				*t = table;
				return set;
			}
			if (string_misspell_update(set->handle.set.name,
						   set_name, set, &st))
				*t = table;
		}
	}
	return st.obj;
}

struct set *set_lookup_global(uint32_t family, const char *table,
			      const char *name, struct nft_cache *cache)
{
	struct handle h;
	struct table *t;

	h.family = family;
	h.table.name = table;

	t = table_lookup(&h, cache);
	if (t == NULL)
		return NULL;

	return set_lookup(t, name);
}

struct print_fmt_options {
	const char	*tab;
	const char	*nl;
	const char	*table;
	const char	*family;
	const char	*stmt_separator;
};

const char *set_policy2str(uint32_t policy)
{
	switch (policy) {
	case NFT_SET_POL_PERFORMANCE:
		return "performance";
	case NFT_SET_POL_MEMORY:
		return "memory";
	default:
		return "unknown";
	}
}

static void set_print_key(const struct expr *expr, struct output_ctx *octx)
{
	const struct datatype *dtype = expr->dtype;

	if (dtype->size || dtype->type == TYPE_VERDICT)
		nft_print(octx, "%s", dtype->name);
	else
		expr_print(expr, octx);
}

static void set_print_key_and_data(const struct set *set, struct output_ctx *octx)
{
	bool use_typeof = set->key_typeof_valid;

	nft_print(octx, "%s ", use_typeof ? "typeof" : "type");

	if (use_typeof)
		expr_print(set->key, octx);
	else
		set_print_key(set->key, octx);

	if (set_is_datamap(set->flags)) {
		nft_print(octx, " : ");
		if (set->data->flags & EXPR_F_INTERVAL)
			nft_print(octx, "interval ");

		if (use_typeof)
			expr_print(set->data, octx);
		else
			set_print_key(set->data, octx);
	} else if (set_is_objmap(set->flags)) {
		nft_print(octx, " : %s", obj_type_name(set->objtype));
	}
}

static void set_print_declaration(const struct set *set,
				  struct print_fmt_options *opts,
				  struct output_ctx *octx)
{
	const char *delim = "";
	struct stmt *stmt;
	const char *type;
	uint32_t flags;

	if (set_is_meter(set->flags))
		type = "meter";
	else if (set_is_map(set->flags))
		type = "map";
	else
		type = "set";

	nft_print(octx, "%s%s", opts->tab, type);

	if (opts->family != NULL)
		nft_print(octx, " %s", opts->family);

	if (opts->table != NULL)
		nft_print(octx, " %s", opts->table);

	nft_print(octx, " %s {", set->handle.set.name);

	if (nft_output_handle(octx))
		nft_print(octx, " # handle %" PRIu64, set->handle.handle.id);
	nft_print(octx, "%s%s%s", opts->nl, opts->tab, opts->tab);

	set_print_key_and_data(set, octx);

	nft_print(octx, "%s", opts->stmt_separator);

	if (!(set->flags & (NFT_SET_CONSTANT))) {
		if (set->policy != NFT_SET_POL_PERFORMANCE) {
			nft_print(octx, "%s%spolicy %s%s",
				  opts->tab, opts->tab,
				  set_policy2str(set->policy),
				  opts->stmt_separator);
		}

		if (set->desc.size > 0) {
			nft_print(octx, "%s%ssize %u%s",
				  opts->tab, opts->tab,
				  set->desc.size,
				  opts->stmt_separator);
		}
	}

	flags = set->flags;
	/* "timeout" flag is redundant if a default timeout exists */
	if (set->timeout)
		flags &= ~NFT_SET_TIMEOUT;

	if (flags & (NFT_SET_CONSTANT | NFT_SET_INTERVAL | NFT_SET_TIMEOUT | NFT_SET_EVAL)) {
		nft_print(octx, "%s%sflags ", opts->tab, opts->tab);
		if (set->flags & NFT_SET_CONSTANT) {
			nft_print(octx, "%sconstant", delim);
			delim = ",";
		}
		if (set->flags & NFT_SET_EVAL) {
			nft_print(octx, "%sdynamic", delim);
			delim = ",";
		}
		if (set->flags & NFT_SET_INTERVAL) {
			nft_print(octx, "%sinterval", delim);
			delim = ",";
		}
		if (set->flags & NFT_SET_TIMEOUT) {
			nft_print(octx, "%stimeout", delim);
			delim = ",";
		}
		nft_print(octx, "%s", opts->stmt_separator);
	}

	if (!list_empty(&set->stmt_list))
		nft_print(octx, "%s%s", opts->tab, opts->tab);

	if (!list_empty(&set->stmt_list)) {
		octx->flags |= NFT_CTX_OUTPUT_STATELESS;
		list_for_each_entry(stmt, &set->stmt_list, list) {
			stmt_print(stmt, octx);
			if (!list_is_last(&stmt->list, &set->stmt_list))
				nft_print(octx, " ");
		}
		octx->flags &= ~NFT_CTX_OUTPUT_STATELESS;
	}

	if (!list_empty(&set->stmt_list))
		nft_print(octx, "%s", opts->stmt_separator);

	if (set->automerge)
		nft_print(octx, "%s%sauto-merge%s", opts->tab, opts->tab,
			  opts->stmt_separator);

	if (set->timeout) {
		nft_print(octx, "%s%stimeout ", opts->tab, opts->tab);
		time_print(set->timeout, octx);
		nft_print(octx, "%s", opts->stmt_separator);
	}
	if (set->gc_int) {
		nft_print(octx, "%s%sgc-interval ", opts->tab, opts->tab);
		time_print(set->gc_int, octx);
		nft_print(octx, "%s", opts->stmt_separator);
	}

	if (set->comment) {
		nft_print(octx, "%s%scomment \"%s\"%s",
			  opts->tab, opts->tab,
			  set->comment,
			  opts->stmt_separator);
	}
}

static void do_set_print(const struct set *set, struct print_fmt_options *opts,
			 struct output_ctx *octx)
{
	set_print_declaration(set, opts, octx);

	if ((set_is_meter(set->flags) && nft_output_stateless(octx)) ||
	    nft_output_terse(octx)) {
		nft_print(octx, "%s}%s", opts->tab, opts->nl);
		return;
	}

	if (set->init != NULL && set->init->size > 0) {
		nft_print(octx, "%s%selements = ", opts->tab, opts->tab);
		expr_print(set->init, octx);
		nft_print(octx, "%s", opts->nl);
	}
	nft_print(octx, "%s}%s", opts->tab, opts->nl);
}

void set_print(const struct set *s, struct output_ctx *octx)
{
	struct print_fmt_options opts = {
		.tab		= "\t",
		.nl		= "\n",
		.stmt_separator	= "\n",
	};

	do_set_print(s, &opts, octx);
}

void set_print_plain(const struct set *s, struct output_ctx *octx)
{
	struct print_fmt_options opts = {
		.tab		= "",
		.nl		= " ",
		.table		= s->handle.table.name,
		.family		= family2str(s->handle.family),
		.stmt_separator	= "; ",
	};

	do_set_print(s, &opts, octx);
}

struct rule *rule_alloc(const struct location *loc, const struct handle *h)
{
	struct rule *rule;

	rule = xzalloc(sizeof(*rule));
	rule->location = *loc;
	init_list_head(&rule->list);
	init_list_head(&rule->stmts);
	rule->refcnt = 1;
	if (h != NULL)
		rule->handle = *h;

	return rule;
}

struct rule *rule_get(struct rule *rule)
{
	rule->refcnt++;
	return rule;
}

void rule_free(struct rule *rule)
{
	if (--rule->refcnt > 0)
		return;
	stmt_list_free(&rule->stmts);
	handle_free(&rule->handle);
	xfree(rule->comment);
	xfree(rule);
}

void rule_print(const struct rule *rule, struct output_ctx *octx)
{
	const struct stmt *stmt;

	list_for_each_entry(stmt, &rule->stmts, list) {
		stmt->ops->print(stmt, octx);
		if (!list_is_last(&stmt->list, &rule->stmts))
			nft_print(octx, " ");
	}

	if (rule->comment)
		nft_print(octx, " comment \"%s\"", rule->comment);

	if (nft_output_handle(octx))
		nft_print(octx, " # handle %" PRIu64, rule->handle.handle.id);
}

struct rule *rule_lookup(const struct chain *chain, uint64_t handle)
{
	struct rule *rule;

	list_for_each_entry(rule, &chain->rules, list) {
		if (rule->handle.handle.id == handle)
			return rule;
	}
	return NULL;
}

struct rule *rule_lookup_by_index(const struct chain *chain, uint64_t index)
{
	struct rule *rule;

	list_for_each_entry(rule, &chain->rules, list) {
		if (!--index)
			return rule;
	}
	return NULL;
}

void rule_stmt_append(struct rule *rule, struct stmt *stmt)
{
	list_add_tail(&stmt->list, &rule->stmts);
	rule->num_stmts++;
}

void rule_stmt_insert_at(struct rule *rule, struct stmt *nstmt,
			 struct stmt *stmt)
{
	list_add_tail(&nstmt->list, &stmt->list);
	rule->num_stmts++;
}

struct scope *scope_alloc(void)
{
	struct scope *scope = xzalloc(sizeof(struct scope));

	init_list_head(&scope->symbols);

	return scope;
}

struct scope *scope_init(struct scope *scope, const struct scope *parent)
{
	scope->parent = parent;
	return scope;
}

void scope_release(const struct scope *scope)
{
	struct symbol *sym, *next;

	list_for_each_entry_safe(sym, next, &scope->symbols, list) {
		assert(sym->refcnt == 1);
		list_del(&sym->list);
		xfree(sym->identifier);
		expr_free(sym->expr);
		xfree(sym);
	}
}

void scope_free(struct scope *scope)
{
	scope_release(scope);
	xfree(scope);
}

void symbol_bind(struct scope *scope, const char *identifier, struct expr *expr)
{
	struct symbol *sym;

	sym = xzalloc(sizeof(*sym));
	sym->identifier = xstrdup(identifier);
	sym->expr = expr;
	sym->refcnt = 1;

	list_add(&sym->list, &scope->symbols);
}

struct symbol *symbol_get(const struct scope *scope, const char *identifier)
{
	struct symbol *sym;

	sym = symbol_lookup(scope, identifier);
	if (!sym)
		return NULL;

	sym->refcnt++;

	return sym;
}

static void symbol_put(struct symbol *sym)
{
	if (--sym->refcnt == 0) {
		xfree(sym->identifier);
		expr_free(sym->expr);
		xfree(sym);
	}
}

static void symbol_remove(struct symbol *sym)
{
	list_del(&sym->list);
	symbol_put(sym);
}

int symbol_unbind(const struct scope *scope, const char *identifier)
{
	struct symbol *sym, *next;

	list_for_each_entry_safe(sym, next, &scope->symbols, list) {
		if (!strcmp(sym->identifier, identifier))
			symbol_remove(sym);
	}

	return 0;
}

struct symbol *symbol_lookup(const struct scope *scope, const char *identifier)
{
	struct symbol *sym;

	while (scope != NULL) {
		list_for_each_entry(sym, &scope->symbols, list) {
			if (!strcmp(sym->identifier, identifier))
				return sym;
		}
		scope = scope->parent;
	}
	return NULL;
}

struct symbol *symbol_lookup_fuzzy(const struct scope *scope,
				   const char *identifier)
{
	struct string_misspell_state st;
	struct symbol *sym;

	string_misspell_init(&st);

	while (scope != NULL) {
		list_for_each_entry(sym, &scope->symbols, list)
			string_misspell_update(sym->identifier, identifier,
					       sym, &st);

		scope = scope->parent;
	}
	return st.obj;
}

static const char * const chain_type_str_array[] = {
	"filter",
	"nat",
	"route",
	NULL,
};

const char *chain_type_name_lookup(const char *name)
{
	int i;

	for (i = 0; chain_type_str_array[i]; i++) {
		if (!strcmp(name, chain_type_str_array[i]))
			return chain_type_str_array[i];
	}

	return NULL;
}

static const char * const chain_hookname_str_array[] = {
	"prerouting",
	"input",
	"forward",
	"postrouting",
	"output",
	"ingress",
	NULL,
};

const char *chain_hookname_lookup(const char *name)
{
	int i;

	for (i = 0; chain_hookname_str_array[i]; i++) {
		if (!strcmp(name, chain_hookname_str_array[i]))
			return chain_hookname_str_array[i];
	}

	return NULL;
}

/* internal ID to uniquely identify a set in the batch */
static uint32_t chain_id;

struct chain *chain_alloc(const char *name)
{
	struct chain *chain;

	chain = xzalloc(sizeof(*chain));
	chain->refcnt = 1;
	chain->handle.chain_id = ++chain_id;
	init_list_head(&chain->rules);
	init_list_head(&chain->scope.symbols);
	if (name != NULL)
		chain->handle.chain.name = xstrdup(name);

	chain->policy = NULL;
	return chain;
}

struct chain *chain_get(struct chain *chain)
{
	chain->refcnt++;
	return chain;
}

void chain_free(struct chain *chain)
{
	struct rule *rule, *next;
	int i;

	if (--chain->refcnt > 0)
		return;
	list_for_each_entry_safe(rule, next, &chain->rules, list)
		rule_free(rule);
	handle_free(&chain->handle);
	scope_release(&chain->scope);
	xfree(chain->type);
	expr_free(chain->dev_expr);
	for (i = 0; i < chain->dev_array_len; i++)
		xfree(chain->dev_array[i]);
	xfree(chain->dev_array);
	expr_free(chain->priority.expr);
	expr_free(chain->policy);
	xfree(chain->comment);
	xfree(chain);
}

struct chain *chain_lookup(const struct table *table, const struct handle *h)
{
	struct chain *chain;

	list_for_each_entry(chain, &table->chains, list) {
		if (!strcmp(chain->handle.chain.name, h->chain.name))
			return chain;
	}
	return NULL;
}

struct chain *chain_binding_lookup(const struct table *table,
				   const char *chain_name)
{
	struct chain *chain;

	list_for_each_entry(chain, &table->chain_bindings, list) {
		if (!strcmp(chain->handle.chain.name, chain_name))
			return chain;
	}
	return NULL;
}

struct chain *chain_lookup_fuzzy(const struct handle *h,
				 const struct nft_cache *cache,
				 const struct table **t)
{
	struct string_misspell_state st;
	struct table *table;
	struct chain *chain;

	string_misspell_init(&st);

	list_for_each_entry(table, &cache->list, list) {
		list_for_each_entry(chain, &table->chains, list) {
			if (!strcmp(chain->handle.chain.name, h->chain.name)) {
				*t = table;
				return chain;
			}
			if (string_misspell_update(chain->handle.chain.name,
						   h->chain.name, chain, &st))
				*t = table;
		}
	}
	return st.obj;
}

const char *family2str(unsigned int family)
{
	switch (family) {
		case NFPROTO_IPV4:
			return "ip";
		case NFPROTO_IPV6:
			return "ip6";
		case NFPROTO_INET:
			return "inet";
		case NFPROTO_NETDEV:
			return "netdev";
		case NFPROTO_ARP:
			return "arp";
		case NFPROTO_BRIDGE:
			return "bridge";
		default:
			break;
	}
	return "unknown";
}

const char *hooknum2str(unsigned int family, unsigned int hooknum)
{
	switch (family) {
	case NFPROTO_IPV4:
	case NFPROTO_BRIDGE:
	case NFPROTO_IPV6:
	case NFPROTO_INET:
		switch (hooknum) {
		case NF_INET_PRE_ROUTING:
			return "prerouting";
		case NF_INET_LOCAL_IN:
			return "input";
		case NF_INET_FORWARD:
			return "forward";
		case NF_INET_POST_ROUTING:
			return "postrouting";
		case NF_INET_LOCAL_OUT:
			return "output";
		case NF_INET_INGRESS:
			return "ingress";
		default:
			break;
		};
		break;
	case NFPROTO_ARP:
		switch (hooknum) {
		case NF_ARP_IN:
			return "input";
		case NF_ARP_FORWARD:
			return "forward";
		case NF_ARP_OUT:
			return "output";
		default:
			break;
		}
		break;
	case NFPROTO_NETDEV:
		switch (hooknum) {
		case NF_NETDEV_INGRESS:
			return "ingress";
		}
		break;
	default:
		break;
	};

	return "unknown";
}

const char *chain_policy2str(uint32_t policy)
{
	switch (policy) {
	case NF_DROP:
		return "drop";
	case NF_ACCEPT:
		return "accept";
	}
	return "unknown";
}

struct prio_tag {
	int val;
	const char *str;
};

const static struct prio_tag std_prios[] = {
	{ NF_IP_PRI_RAW,      "raw" },
	{ NF_IP_PRI_MANGLE,   "mangle" },
	{ NF_IP_PRI_NAT_DST,  "dstnat" },
	{ NF_IP_PRI_FILTER,   "filter" },
	{ NF_IP_PRI_SECURITY, "security" },
	{ NF_IP_PRI_NAT_SRC,  "srcnat" },
};

const static struct prio_tag bridge_std_prios[] = {
	{ NF_BR_PRI_NAT_DST_BRIDGED,  "dstnat" },
	{ NF_BR_PRI_FILTER_BRIDGED,   "filter" },
	{ NF_BR_PRI_NAT_DST_OTHER,    "out" },
	{ NF_BR_PRI_NAT_SRC,          "srcnat" },
};

static bool std_prio_family_hook_compat(int prio, int family, int hook)
{
	/* bridge family has different values */
	if (family == NFPROTO_BRIDGE) {
		switch (prio) {
		case NF_BR_PRI_NAT_DST_BRIDGED:
			if (hook == NF_BR_PRE_ROUTING)
				return true;
			break;
		case NF_BR_PRI_FILTER_BRIDGED:
			return true;
		case NF_BR_PRI_NAT_DST_OTHER:
			if (hook == NF_BR_LOCAL_OUT)
				return true;
			break;
		case NF_BR_PRI_NAT_SRC:
			if (hook == NF_BR_POST_ROUTING)
				return true;
		}
		return false;
	}
	switch(prio) {
	case NF_IP_PRI_FILTER:
		switch (family) {
		case NFPROTO_INET:
		case NFPROTO_IPV4:
		case NFPROTO_IPV6:
		case NFPROTO_ARP:
		case NFPROTO_NETDEV:
			return true;
		}
		break;
	case NF_IP_PRI_RAW:
	case NF_IP_PRI_MANGLE:
	case NF_IP_PRI_SECURITY:
		switch (family) {
		case NFPROTO_INET:
		case NFPROTO_IPV4:
		case NFPROTO_IPV6:
			return true;
		}
		break;
	case NF_IP_PRI_NAT_DST:
		switch(family) {
		case NFPROTO_INET:
		case NFPROTO_IPV4:
		case NFPROTO_IPV6:
			if (hook == NF_INET_PRE_ROUTING)
				return true;
		}
		break;
	case NF_IP_PRI_NAT_SRC:
		switch(family) {
		case NFPROTO_INET:
		case NFPROTO_IPV4:
		case NFPROTO_IPV6:
			if (hook == NF_INET_POST_ROUTING)
				return true;
		}
	}
	return false;
}

int std_prio_lookup(const char *std_prio_name, int family, int hook)
{
	const struct prio_tag *prio_arr;
	size_t i, arr_size;

	if (family == NFPROTO_BRIDGE) {
		prio_arr = bridge_std_prios;
		arr_size = array_size(bridge_std_prios);
	} else {
		prio_arr = std_prios;
		arr_size = array_size(std_prios);
	}

	for (i = 0; i < arr_size; ++i) {
		if (strcmp(prio_arr[i].str, std_prio_name) == 0 &&
		    std_prio_family_hook_compat(prio_arr[i].val, family, hook))
			return prio_arr[i].val;
	}
	return NF_IP_PRI_LAST;
}

static const char *prio2str(const struct output_ctx *octx,
			    char *buf, size_t bufsize, int family, int hook,
			    const struct expr *expr)
{
	const struct prio_tag *prio_arr;
	int std_prio, offset, prio;
	const char *std_prio_str;
	const int reach = 10;
	size_t i, arr_size;

	mpz_export_data(&prio, expr->value, BYTEORDER_HOST_ENDIAN, sizeof(int));
	if (family == NFPROTO_BRIDGE) {
		prio_arr = bridge_std_prios;
		arr_size = array_size(bridge_std_prios);
	} else {
		prio_arr = std_prios;
		arr_size = array_size(std_prios);
	}

	if (!nft_output_numeric_prio(octx)) {
		for (i = 0; i < arr_size; ++i) {
			std_prio = prio_arr[i].val;
			std_prio_str = prio_arr[i].str;
			if (abs(prio - std_prio) <= reach) {
				if (!std_prio_family_hook_compat(std_prio,
								 family, hook))
					break;
				offset = prio - std_prio;
				strncpy(buf, std_prio_str, bufsize);
				if (offset > 0)
					snprintf(buf + strlen(buf),
						 bufsize - strlen(buf), " + %d",
						 offset);
				else if (offset < 0)
					snprintf(buf + strlen(buf),
						 bufsize - strlen(buf), " - %d",
						 -offset);
				return buf;
			}
		}
	}
	snprintf(buf, bufsize, "%d", prio);
	return buf;
}

static void chain_print_declaration(const struct chain *chain,
				    struct output_ctx *octx)
{
	char priobuf[STD_PRIO_BUFSIZE];
	int policy, i;

	if (chain->flags & CHAIN_F_BINDING)
		return;

	nft_print(octx, "\tchain %s {", chain->handle.chain.name);
	if (nft_output_handle(octx))
		nft_print(octx, " # handle %" PRIu64, chain->handle.handle.id);
	if (chain->comment)
		nft_print(octx, "\n\t\tcomment \"%s\"", chain->comment);
	nft_print(octx, "\n");
	if (chain->flags & CHAIN_F_BASECHAIN) {
		nft_print(octx, "\t\ttype %s hook %s", chain->type,
			  hooknum2str(chain->handle.family, chain->hook.num));
		if (chain->dev_array_len == 1) {
			nft_print(octx, " device \"%s\"", chain->dev_array[0]);
		} else if (chain->dev_array_len > 1) {
			nft_print(octx, " devices = { ");
			for (i = 0; i < chain->dev_array_len; i++) {
				nft_print(octx, "%s", chain->dev_array[i]);
					if (i + 1 != chain->dev_array_len)
						nft_print(octx, ", ");
			}
			nft_print(octx, " }");
		}
		nft_print(octx, " priority %s;",
			  prio2str(octx, priobuf, sizeof(priobuf),
				   chain->handle.family, chain->hook.num,
				   chain->priority.expr));
		if (chain->policy) {
			mpz_export_data(&policy, chain->policy->value,
					BYTEORDER_HOST_ENDIAN, sizeof(int));
			nft_print(octx, " policy %s;",
				  chain_policy2str(policy));
		}
		if (chain->flags & CHAIN_F_HW_OFFLOAD)
			nft_print(octx, " flags offload;");

		nft_print(octx, "\n");
	}
}

void chain_rules_print(const struct chain *chain, struct output_ctx *octx,
		       const char *indent)
{
	struct rule *rule;

	list_for_each_entry(rule, &chain->rules, list) {
		nft_print(octx, "\t\t%s", indent ? : "");
		rule_print(rule, octx);
		nft_print(octx, "\n");
	}
}

static void chain_print(const struct chain *chain, struct output_ctx *octx)
{
	chain_print_declaration(chain, octx);
	chain_rules_print(chain, octx, NULL);
	nft_print(octx, "\t}\n");
}

void chain_print_plain(const struct chain *chain, struct output_ctx *octx)
{
	char priobuf[STD_PRIO_BUFSIZE];
	int policy;

	nft_print(octx, "chain %s %s %s", family2str(chain->handle.family),
		  chain->handle.table.name, chain->handle.chain.name);

	if (chain->flags & CHAIN_F_BASECHAIN) {
		mpz_export_data(&policy, chain->policy->value,
				BYTEORDER_HOST_ENDIAN, sizeof(int));
		nft_print(octx, " { type %s hook %s priority %s; policy %s; }",
			  chain->type, chain->hook.name,
			  prio2str(octx, priobuf, sizeof(priobuf),
				   chain->handle.family, chain->hook.num,
				   chain->priority.expr),
			  chain_policy2str(policy));
	}
	if (nft_output_handle(octx))
		nft_print(octx, " # handle %" PRIu64, chain->handle.handle.id);
}

struct table *table_alloc(void)
{
	struct table *table;
	int i;

	table = xzalloc(sizeof(*table));
	init_list_head(&table->chains);
	init_list_head(&table->sets);
	init_list_head(&table->objs);
	init_list_head(&table->flowtables);
	init_list_head(&table->chain_bindings);
	init_list_head(&table->scope.symbols);
	table->refcnt = 1;

	table->chain_htable =
		xmalloc(sizeof(struct list_head) * NFT_CACHE_HSIZE);
	for (i = 0; i < NFT_CACHE_HSIZE; i++)
		init_list_head(&table->chain_htable[i]);

	return table;
}

void table_free(struct table *table)
{
	struct chain *chain, *next;
	struct flowtable *ft, *nft;
	struct set *set, *nset;
	struct obj *obj, *nobj;

	if (--table->refcnt > 0)
		return;
	if (table->comment)
		xfree(table->comment);
	list_for_each_entry_safe(chain, next, &table->chains, list)
		chain_free(chain);
	list_for_each_entry_safe(chain, next, &table->chain_bindings, list)
		chain_free(chain);
	list_for_each_entry_safe(set, nset, &table->sets, list)
		set_free(set);
	list_for_each_entry_safe(ft, nft, &table->flowtables, list)
		flowtable_free(ft);
	list_for_each_entry_safe(obj, nobj, &table->objs, list)
		obj_free(obj);
	handle_free(&table->handle);
	scope_release(&table->scope);
	xfree(table->chain_htable);
	xfree(table);
}

struct table *table_get(struct table *table)
{
	table->refcnt++;
	return table;
}

void table_add_hash(struct table *table, struct nft_cache *cache)
{
	list_add_tail(&table->list, &cache->list);
}

struct table *table_lookup(const struct handle *h,
			   const struct nft_cache *cache)
{
	struct table *table;

	list_for_each_entry(table, &cache->list, list) {
		if (table->handle.family == h->family &&
		    !strcmp(table->handle.table.name, h->table.name))
			return table;
	}
	return NULL;
}

struct table *table_lookup_fuzzy(const struct handle *h,
				 const struct nft_cache *cache)
{
	struct string_misspell_state st;
	struct table *table;

	string_misspell_init(&st);

	list_for_each_entry(table, &cache->list, list) {
		if (!strcmp(table->handle.table.name, h->table.name))
			return table;

		string_misspell_update(table->handle.table.name,
				       h->table.name, table, &st);
	}
	return st.obj;
}

const char *table_flags_name[TABLE_FLAGS_MAX] = {
	"dormant",
};

static void table_print_options(const struct table *table, const char **delim,
				struct output_ctx *octx)
{
	uint32_t flags = table->flags;
	int i;

	if (flags) {
		nft_print(octx, "\tflags ");

		for (i = 0; i < TABLE_FLAGS_MAX; i++) {
			if (flags & 0x1)
				nft_print(octx, "%s", table_flags_name[i]);
			flags >>= 1;
			if (flags)
				nft_print(octx, ",");
		}
		nft_print(octx, "\n");
		*delim = "\n";
	}
}

static void table_print(const struct table *table, struct output_ctx *octx)
{
	struct flowtable *flowtable;
	struct chain *chain;
	struct obj *obj;
	struct set *set;
	const char *delim = "";
	const char *family = family2str(table->handle.family);

	nft_print(octx, "table %s %s {", family, table->handle.table.name);
	if (nft_output_handle(octx))
		nft_print(octx, " # handle %" PRIu64, table->handle.handle.id);
	nft_print(octx, "\n");
	table_print_options(table, &delim, octx);

	if (table->comment)
		nft_print(octx, "\tcomment \"%s\"\n", table->comment);

	list_for_each_entry(obj, &table->objs, list) {
		nft_print(octx, "%s", delim);
		obj_print(obj, octx);
		delim = "\n";
	}
	list_for_each_entry(set, &table->sets, list) {
		if (set_is_anonymous(set->flags))
			continue;
		nft_print(octx, "%s", delim);
		set_print(set, octx);
		delim = "\n";
	}
	list_for_each_entry(flowtable, &table->flowtables, list) {
		nft_print(octx, "%s", delim);
		flowtable_print(flowtable, octx);
		delim = "\n";
	}
	list_for_each_entry(chain, &table->chains, list) {
		nft_print(octx, "%s", delim);
		chain_print(chain, octx);
		delim = "\n";
	}
	nft_print(octx, "}\n");
}

struct cmd *cmd_alloc(enum cmd_ops op, enum cmd_obj obj,
		      const struct handle *h, const struct location *loc,
		      void *data)
{
	struct cmd *cmd;

	cmd = xzalloc(sizeof(*cmd));
	init_list_head(&cmd->list);
	cmd->op       = op;
	cmd->obj      = obj;
	cmd->handle   = *h;
	cmd->location = *loc;
	cmd->data     = data;
	return cmd;
}

void cmd_add_loc(struct cmd *cmd, uint16_t offset, const struct location *loc)
{
	if (cmd->num_attrs > NFT_NLATTR_LOC_MAX)
		return;

	cmd->attr[cmd->num_attrs].offset = offset;
	cmd->attr[cmd->num_attrs].location = loc;
	cmd->num_attrs++;
}

void nft_cmd_expand(struct cmd *cmd)
{
	struct list_head new_cmds;
	struct set *set, *newset;
	struct flowtable *ft;
	struct table *table;
	struct chain *chain;
	struct rule *rule;
	struct obj *obj;
	struct cmd *new;
	struct handle h;

	init_list_head(&new_cmds);

	switch (cmd->obj) {
	case CMD_OBJ_TABLE:
		table = cmd->table;
		if (!table)
			return;

		list_for_each_entry(chain, &table->chains, list) {
			memset(&h, 0, sizeof(h));
			handle_merge(&h, &chain->handle);
			h.chain_id = chain->handle.chain_id;
			new = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &h,
					&chain->location, chain_get(chain));
			list_add_tail(&new->list, &new_cmds);
		}
		list_for_each_entry(obj, &table->objs, list) {
			handle_merge(&obj->handle, &table->handle);
			memset(&h, 0, sizeof(h));
			handle_merge(&h, &obj->handle);
			new = cmd_alloc(CMD_ADD, obj_type_to_cmd(obj->type), &h,
					&obj->location, obj_get(obj));
			list_add_tail(&new->list, &new_cmds);
		}
		list_for_each_entry(set, &table->sets, list) {
			handle_merge(&set->handle, &table->handle);
			memset(&h, 0, sizeof(h));
			handle_merge(&h, &set->handle);
			new = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &h,
					&set->location, set_get(set));
			list_add_tail(&new->list, &new_cmds);
		}
		list_for_each_entry(ft, &table->flowtables, list) {
			handle_merge(&ft->handle, &table->handle);
			memset(&h, 0, sizeof(h));
			handle_merge(&h, &ft->handle);
			new = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &h,
					&ft->location, flowtable_get(ft));
			list_add_tail(&new->list, &new_cmds);
		}
		list_for_each_entry(chain, &table->chains, list) {
			list_for_each_entry(rule, &chain->rules, list) {
				memset(&h, 0, sizeof(h));
				handle_merge(&h, &rule->handle);
				if (chain->flags & CHAIN_F_BINDING) {
					rule->handle.chain_id =
						chain->handle.chain_id;
					rule->handle.chain.location =
						chain->location;
				}
				new = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &h,
						&rule->location,
						rule_get(rule));
				list_add_tail(&new->list, &new_cmds);
			}
		}
		list_splice(&new_cmds, &cmd->list);
		break;
	case CMD_OBJ_SET:
	case CMD_OBJ_MAP:
		set = cmd->set;
		memset(&h, 0, sizeof(h));
		handle_merge(&h, &set->handle);
		newset = set_clone(set);
		newset->handle.set_id = set->handle.set_id;
		newset->init = set->init;
		set->init = NULL;
		new = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEMS, &h,
				&set->location, newset);
		list_add(&new->list, &cmd->list);
		break;
	default:
		break;
	}
}

struct markup *markup_alloc(uint32_t format)
{
	struct markup *markup;

	markup = xmalloc(sizeof(struct markup));
	markup->format = format;

	return markup;
}

void markup_free(struct markup *m)
{
	xfree(m);
}

struct monitor *monitor_alloc(uint32_t format, uint32_t type, const char *event)
{
	struct monitor *mon;

	mon = xmalloc(sizeof(struct monitor));
	mon->format = format;
	mon->type = type;
	mon->event = event;
	mon->flags = 0;

	return mon;
}

void monitor_free(struct monitor *m)
{
	xfree(m->event);
	xfree(m);
}

void cmd_free(struct cmd *cmd)
{
	handle_free(&cmd->handle);
	if (cmd->data != NULL) {
		switch (cmd->obj) {
		case CMD_OBJ_ELEMENTS:
			expr_free(cmd->expr);
			if (cmd->elem.set)
				set_free(cmd->elem.set);
			break;
		case CMD_OBJ_SET:
		case CMD_OBJ_SETELEMS:
			set_free(cmd->set);
			break;
		case CMD_OBJ_RULE:
			rule_free(cmd->rule);
			break;
		case CMD_OBJ_CHAIN:
			chain_free(cmd->chain);
			break;
		case CMD_OBJ_TABLE:
			table_free(cmd->table);
			break;
		case CMD_OBJ_EXPR:
			expr_free(cmd->expr);
			break;
		case CMD_OBJ_MONITOR:
			monitor_free(cmd->monitor);
			break;
		case CMD_OBJ_MARKUP:
			markup_free(cmd->markup);
			break;
		case CMD_OBJ_COUNTER:
		case CMD_OBJ_QUOTA:
		case CMD_OBJ_CT_HELPER:
		case CMD_OBJ_CT_TIMEOUT:
		case CMD_OBJ_CT_EXPECT:
		case CMD_OBJ_LIMIT:
		case CMD_OBJ_SECMARK:
		case CMD_OBJ_SYNPROXY:
			obj_free(cmd->object);
			break;
		case CMD_OBJ_FLOWTABLE:
			flowtable_free(cmd->flowtable);
			break;
		default:
			BUG("invalid command object type %u\n", cmd->obj);
		}
	}
	xfree(cmd->arg);
	xfree(cmd);
}

#include <netlink.h>
#include <mnl.h>

static int __do_add_setelems(struct netlink_ctx *ctx, struct set *set,
			     struct expr *expr, uint32_t flags)
{
	expr->set_flags |= set->flags;
	if (mnl_nft_setelem_add(ctx, set, expr, flags) < 0)
		return -1;

	if (!set_is_anonymous(set->flags) &&
	    set->init != NULL && set->init != expr &&
	    set->flags & NFT_SET_INTERVAL &&
	    set->desc.field_count <= 1) {
		interval_map_decompose(expr);
		list_splice_tail_init(&expr->expressions, &set->init->expressions);
		set->init->size += expr->size;
		expr->size = 0;
	}

	return 0;
}

static int do_add_setelems(struct netlink_ctx *ctx, struct cmd *cmd,
			   uint32_t flags)
{
	struct expr *init = cmd->expr;
	struct set *set = cmd->elem.set;

	if (set_is_non_concat_range(set) &&
	    set_to_intervals(ctx->msgs, set, init, true,
			     ctx->nft->debug_mask, set->automerge,
			     &ctx->nft->output) < 0)
		return -1;

	return __do_add_setelems(ctx, set, init, flags);
}

static int do_add_set(struct netlink_ctx *ctx, struct cmd *cmd,
		      uint32_t flags, bool add)
{
	struct set *set = cmd->set;

	if (set->init != NULL) {
		if (set_is_non_concat_range(set) &&
		    set_to_intervals(ctx->msgs, set, set->init, true,
				     ctx->nft->debug_mask, set->automerge,
				     &ctx->nft->output) < 0)
			return -1;
	}
	if (add && mnl_nft_set_add(ctx, cmd, flags) < 0)
		return -1;
	if (set->init != NULL) {
		return __do_add_setelems(ctx, set, set->init, flags);
	}
	return 0;
}

static int do_command_add(struct netlink_ctx *ctx, struct cmd *cmd, bool excl)
{
	uint32_t flags = excl ? NLM_F_EXCL : 0;

	if (nft_output_echo(&ctx->nft->output))
		flags |= NLM_F_ECHO;

	switch (cmd->obj) {
	case CMD_OBJ_TABLE:
		return mnl_nft_table_add(ctx, cmd, flags);
	case CMD_OBJ_CHAIN:
		return mnl_nft_chain_add(ctx, cmd, flags);
	case CMD_OBJ_RULE:
		return mnl_nft_rule_add(ctx, cmd, flags | NLM_F_APPEND);
	case CMD_OBJ_SET:
		return do_add_set(ctx, cmd, flags, true);
	case CMD_OBJ_SETELEMS:
		return do_add_set(ctx, cmd, flags, false);
	case CMD_OBJ_ELEMENTS:
		return do_add_setelems(ctx, cmd, flags);
	case CMD_OBJ_COUNTER:
	case CMD_OBJ_QUOTA:
	case CMD_OBJ_CT_HELPER:
	case CMD_OBJ_CT_TIMEOUT:
	case CMD_OBJ_CT_EXPECT:
	case CMD_OBJ_LIMIT:
	case CMD_OBJ_SECMARK:
	case CMD_OBJ_SYNPROXY:
		return mnl_nft_obj_add(ctx, cmd, flags);
	case CMD_OBJ_FLOWTABLE:
		return mnl_nft_flowtable_add(ctx, cmd, flags);
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}
	return 0;
}

static int do_command_replace(struct netlink_ctx *ctx, struct cmd *cmd)
{
	switch (cmd->obj) {
	case CMD_OBJ_RULE:
		return mnl_nft_rule_replace(ctx, cmd);
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}
	return 0;
}

static int do_command_insert(struct netlink_ctx *ctx, struct cmd *cmd)
{
	uint32_t flags = 0;

	if (nft_output_echo(&ctx->nft->output))
		flags |= NLM_F_ECHO;

	switch (cmd->obj) {
	case CMD_OBJ_RULE:
		return mnl_nft_rule_add(ctx, cmd, flags);
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}
	return 0;
}

static int do_delete_setelems(struct netlink_ctx *ctx, struct cmd *cmd)
{
	struct expr *expr = cmd->elem.expr;
	struct set *set = cmd->elem.set;

	if (set_is_non_concat_range(set) &&
	    set_to_intervals(ctx->msgs, set, expr, false,
			     ctx->nft->debug_mask, set->automerge,
			     &ctx->nft->output) < 0)
		return -1;

	if (mnl_nft_setelem_del(ctx, cmd) < 0)
		return -1;

	return 0;
}

static int do_command_delete(struct netlink_ctx *ctx, struct cmd *cmd)
{
	switch (cmd->obj) {
	case CMD_OBJ_TABLE:
		return mnl_nft_table_del(ctx, cmd);
	case CMD_OBJ_CHAIN:
		return mnl_nft_chain_del(ctx, cmd);
	case CMD_OBJ_RULE:
		return mnl_nft_rule_del(ctx, cmd);
	case CMD_OBJ_SET:
		return mnl_nft_set_del(ctx, cmd);
	case CMD_OBJ_ELEMENTS:
		return do_delete_setelems(ctx, cmd);
	case CMD_OBJ_COUNTER:
		return mnl_nft_obj_del(ctx, cmd, NFT_OBJECT_COUNTER);
	case CMD_OBJ_QUOTA:
		return mnl_nft_obj_del(ctx, cmd, NFT_OBJECT_QUOTA);
	case CMD_OBJ_CT_HELPER:
		return mnl_nft_obj_del(ctx, cmd, NFT_OBJECT_CT_HELPER);
	case CMD_OBJ_CT_TIMEOUT:
		return mnl_nft_obj_del(ctx, cmd, NFT_OBJECT_CT_TIMEOUT);
	case CMD_OBJ_CT_EXPECT:
		return mnl_nft_obj_del(ctx, cmd, NFT_OBJECT_CT_EXPECT);
	case CMD_OBJ_LIMIT:
		return mnl_nft_obj_del(ctx, cmd, NFT_OBJECT_LIMIT);
	case CMD_OBJ_SECMARK:
		return mnl_nft_obj_del(ctx, cmd, NFT_OBJECT_SECMARK);
	case CMD_OBJ_SYNPROXY:
		return mnl_nft_obj_del(ctx, cmd, NFT_OBJECT_SYNPROXY);
	case CMD_OBJ_FLOWTABLE:
		return mnl_nft_flowtable_del(ctx, cmd);
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}
}

static int do_list_table(struct netlink_ctx *ctx, struct cmd *cmd,
			 struct table *table)
{
	table_print(table, &ctx->nft->output);
	return 0;
}

static int do_list_sets(struct netlink_ctx *ctx, struct cmd *cmd)
{
	struct print_fmt_options opts = {
		.tab		= "\t",
		.nl		= "\n",
		.stmt_separator	= "\n",
	};
	struct table *table;
	struct set *set;

	list_for_each_entry(table, &ctx->nft->cache.list, list) {
		if (cmd->handle.family != NFPROTO_UNSPEC &&
		    cmd->handle.family != table->handle.family)
			continue;

		nft_print(&ctx->nft->output, "table %s %s {\n",
			  family2str(table->handle.family),
			  table->handle.table.name);

		list_for_each_entry(set, &table->sets, list) {
			if (cmd->obj == CMD_OBJ_SETS &&
			    !set_is_literal(set->flags))
				continue;
			if (cmd->obj == CMD_OBJ_METERS &&
			    !set_is_meter(set->flags))
				continue;
			if (cmd->obj == CMD_OBJ_MAPS &&
			    !map_is_literal(set->flags))
				continue;
			set_print_declaration(set, &opts, &ctx->nft->output);
			nft_print(&ctx->nft->output, "%s}%s", opts.tab, opts.nl);
		}

		nft_print(&ctx->nft->output, "}\n");
	}
	return 0;
}

struct obj *obj_alloc(const struct location *loc)
{
	struct obj *obj;

	obj = xzalloc(sizeof(*obj));
	if (loc != NULL)
		obj->location = *loc;

	obj->refcnt = 1;
	return obj;
}

struct obj *obj_get(struct obj *obj)
{
	obj->refcnt++;
	return obj;
}

void obj_free(struct obj *obj)
{
	if (--obj->refcnt > 0)
		return;
	xfree(obj->comment);
	handle_free(&obj->handle);
	xfree(obj);
}

void obj_add_hash(struct obj *obj, struct table *table)
{
	list_add_tail(&obj->list, &table->objs);
}

struct obj *obj_lookup(const struct table *table, const char *name,
		       uint32_t type)
{
	struct obj *obj;

	list_for_each_entry(obj, &table->objs, list) {
		if (!strcmp(obj->handle.obj.name, name) &&
		    obj->type == type)
			return obj;
	}
	return NULL;
}

struct obj *obj_lookup_fuzzy(const char *obj_name,
			     const struct nft_cache *cache,
			     const struct table **t)
{
	struct string_misspell_state st;
	struct table *table;
	struct obj *obj;

	string_misspell_init(&st);

	list_for_each_entry(table, &cache->list, list) {
		list_for_each_entry(obj, &table->objs, list) {
			if (!strcmp(obj->handle.obj.name, obj_name)) {
				*t = table;
				return obj;
			}
			if (string_misspell_update(obj->handle.obj.name,
						   obj_name, obj, &st))
				*t = table;
		}
	}
	return st.obj;
}

static void print_proto_name_proto(uint8_t l4, struct output_ctx *octx)
{
	const struct protoent *p = getprotobynumber(l4);

	if (p)
		nft_print(octx, "%s", p->p_name);
	else
		nft_print(octx, "%d", l4);
}

static void print_proto_timeout_policy(uint8_t l4, const uint32_t *timeout,
				       struct print_fmt_options *opts,
				       struct output_ctx *octx)
{
	bool comma = false;
	unsigned int i;

	nft_print(octx, "%s%spolicy = { ", opts->tab, opts->tab);
	for (i = 0; i < timeout_protocol[l4].array_size; i++) {
		if (timeout[i] != timeout_protocol[l4].dflt_timeout[i]) {
			if (comma)
				nft_print(octx, ", ");
			nft_print(octx, "%s : %u",
				  timeout_protocol[l4].state_to_name[i],
				  timeout[i]);
			comma = true;
		}
	}
	nft_print(octx, " }%s", opts->stmt_separator);
}

static const char *synproxy_sack_to_str(const uint32_t flags)
{
        if (flags & NF_SYNPROXY_OPT_SACK_PERM)
                return "sack-perm";

        return "";
}

static const char *synproxy_timestamp_to_str(const uint32_t flags)
{
        if (flags & NF_SYNPROXY_OPT_TIMESTAMP)
                return "timestamp";

        return "";
}

static void obj_print_comment(const struct obj *obj,
			      struct print_fmt_options *opts,
			      struct output_ctx *octx)
{
	if (obj->comment)
		nft_print(octx, "%s%s%scomment \"%s\"",
			  opts->nl, opts->tab, opts->tab,
			  obj->comment);
}

static void obj_print_data(const struct obj *obj,
			   struct print_fmt_options *opts,
			   struct output_ctx *octx)
{
	switch (obj->type) {
	case NFT_OBJECT_COUNTER:
		nft_print(octx, " %s {", obj->handle.obj.name);
		if (nft_output_handle(octx))
			nft_print(octx, " # handle %" PRIu64, obj->handle.handle.id);

		obj_print_comment(obj, opts, octx);
		nft_print(octx, "%s%s%s", opts->nl, opts->tab, opts->tab);
		if (nft_output_stateless(octx)) {
			nft_print(octx, "packets 0 bytes 0");
			break;
		}
		nft_print(octx, "packets %" PRIu64 " bytes %" PRIu64 "%s",
			  obj->counter.packets, obj->counter.bytes, opts->nl);
		break;
	case NFT_OBJECT_QUOTA: {
		const char *data_unit;
		uint64_t bytes;

		nft_print(octx, " %s {", obj->handle.obj.name);
		if (nft_output_handle(octx))
			nft_print(octx, " # handle %" PRIu64, obj->handle.handle.id);

		obj_print_comment(obj, opts, octx);
		nft_print(octx, "%s%s%s", opts->nl, opts->tab, opts->tab);
		data_unit = get_rate(obj->quota.bytes, &bytes);
		nft_print(octx, "%s%" PRIu64 " %s",
			  obj->quota.flags & NFT_QUOTA_F_INV ? "over " : "",
			  bytes, data_unit);
		if (!nft_output_stateless(octx) && obj->quota.used) {
			data_unit = get_rate(obj->quota.used, &bytes);
			nft_print(octx, " used %" PRIu64 " %s",
				  bytes, data_unit);
		}
		nft_print(octx, "%s", opts->nl);
		}
		break;
	case NFT_OBJECT_SECMARK:
		nft_print(octx, " %s {", obj->handle.obj.name);
		if (nft_output_handle(octx))
			nft_print(octx, " # handle %" PRIu64, obj->handle.handle.id);

		obj_print_comment(obj, opts, octx);
		nft_print(octx, "%s%s%s", opts->nl, opts->tab, opts->tab);
		nft_print(octx, "\"%s\"%s", obj->secmark.ctx, opts->nl);
		break;
	case NFT_OBJECT_CT_HELPER:
		nft_print(octx, " %s {", obj->handle.obj.name);
		if (nft_output_handle(octx))
			nft_print(octx, " # handle %" PRIu64, obj->handle.handle.id);

		obj_print_comment(obj, opts, octx);
		nft_print(octx, "%s", opts->nl);
		nft_print(octx, "%s%stype \"%s\" protocol ",
			  opts->tab, opts->tab, obj->ct_helper.name);
		print_proto_name_proto(obj->ct_helper.l4proto, octx);
		nft_print(octx, "%s", opts->stmt_separator);
		nft_print(octx, "%s%sl3proto %s%s",
			  opts->tab, opts->tab,
			  family2str(obj->ct_helper.l3proto),
			  opts->stmt_separator);
		break;
	case NFT_OBJECT_CT_TIMEOUT:
		nft_print(octx, " %s {", obj->handle.obj.name);
		if (nft_output_handle(octx))
			nft_print(octx, " # handle %" PRIu64, obj->handle.handle.id);

		obj_print_comment(obj, opts, octx);
		nft_print(octx, "%s", opts->nl);
		nft_print(octx, "%s%sprotocol ", opts->tab, opts->tab);
		print_proto_name_proto(obj->ct_timeout.l4proto, octx);
		nft_print(octx, "%s", opts->stmt_separator);
		nft_print(octx, "%s%sl3proto %s%s",
			  opts->tab, opts->tab,
			  family2str(obj->ct_timeout.l3proto),
			  opts->stmt_separator);
		print_proto_timeout_policy(obj->ct_timeout.l4proto,
					   obj->ct_timeout.timeout, opts, octx);
		break;
	case NFT_OBJECT_CT_EXPECT:
		nft_print(octx, " %s {", obj->handle.obj.name);
		if (nft_output_handle(octx))
			nft_print(octx, " # handle %" PRIu64, obj->handle.handle.id);

		obj_print_comment(obj, opts, octx);
		nft_print(octx, "%s", opts->nl);
		nft_print(octx, "%s%sprotocol ", opts->tab, opts->tab);
		print_proto_name_proto(obj->ct_expect.l4proto, octx);
		nft_print(octx, "%s", opts->stmt_separator);
		nft_print(octx, "%s%sdport %d%s",
			  opts->tab, opts->tab,
			  obj->ct_expect.dport,
			  opts->stmt_separator);
		nft_print(octx, "%s%stimeout ", opts->tab, opts->tab);
		time_print(obj->ct_expect.timeout, octx);
		nft_print(octx, "%s", opts->stmt_separator);
		nft_print(octx, "%s%ssize %d%s",
			  opts->tab, opts->tab,
			  obj->ct_expect.size,
			  opts->stmt_separator);
		nft_print(octx, "%s%sl3proto %s%s",
			  opts->tab, opts->tab,
			  family2str(obj->ct_expect.l3proto),
			  opts->stmt_separator);
		break;
	case NFT_OBJECT_LIMIT: {
		bool inv = obj->limit.flags & NFT_LIMIT_F_INV;
		const char *data_unit;
		uint64_t rate;

		nft_print(octx, " %s {", obj->handle.obj.name);
		if (nft_output_handle(octx))
			nft_print(octx, " # handle %" PRIu64, obj->handle.handle.id);

		obj_print_comment(obj, opts, octx);
		nft_print(octx, "%s%s%s", opts->nl, opts->tab, opts->tab);
		switch (obj->limit.type) {
		case NFT_LIMIT_PKTS:
			nft_print(octx, "rate %s%" PRIu64 "/%s",
				  inv ? "over " : "", obj->limit.rate,
				  get_unit(obj->limit.unit));
			if (obj->limit.burst > 0 && obj->limit.burst != 5)
				nft_print(octx, " burst %u packets",
					  obj->limit.burst);
			break;
		case NFT_LIMIT_PKT_BYTES:
			data_unit = get_rate(obj->limit.rate, &rate);

			nft_print(octx, "rate %s%" PRIu64 " %s/%s",
				  inv ? "over " : "", rate, data_unit,
				  get_unit(obj->limit.unit));
			if (obj->limit.burst > 0) {
				uint64_t burst;

				data_unit = get_rate(obj->limit.burst, &burst);
				nft_print(octx, " burst %"PRIu64" %s",
					  burst, data_unit);
			}
			break;
		}
		nft_print(octx, "%s", opts->nl);
		}
		break;
	case NFT_OBJECT_SYNPROXY: {
		uint32_t flags = obj->synproxy.flags;
		const char *sack_str = synproxy_sack_to_str(flags);
		const char *ts_str = synproxy_timestamp_to_str(flags);

		nft_print(octx, " %s {", obj->handle.obj.name);
		if (nft_output_handle(octx))
			nft_print(octx, " # handle %" PRIu64, obj->handle.handle.id);

		obj_print_comment(obj, opts, octx);

		if (flags & NF_SYNPROXY_OPT_MSS) {
			nft_print(octx, "%s%s%s", opts->nl, opts->tab, opts->tab);
			nft_print(octx, "mss %u", obj->synproxy.mss);
		}
		if (flags & NF_SYNPROXY_OPT_WSCALE) {
			nft_print(octx, "%s%s%s", opts->nl, opts->tab, opts->tab);
			nft_print(octx, "wscale %u", obj->synproxy.wscale);
		}
		if (flags & (NF_SYNPROXY_OPT_TIMESTAMP | NF_SYNPROXY_OPT_SACK_PERM)) {
			nft_print(octx, "%s%s%s", opts->nl, opts->tab, opts->tab);
			nft_print(octx, "%s %s", ts_str, sack_str);
		}
		nft_print(octx, "%s", opts->stmt_separator);
		}
		break;
	default:
		nft_print(octx, " unknown {%s", opts->nl);
		break;
	}
}

static const char * const obj_type_name_array[] = {
	[NFT_OBJECT_COUNTER]	= "counter",
	[NFT_OBJECT_QUOTA]	= "quota",
	[NFT_OBJECT_CT_HELPER]	= "ct helper",
	[NFT_OBJECT_LIMIT]	= "limit",
	[NFT_OBJECT_CT_TIMEOUT] = "ct timeout",
	[NFT_OBJECT_SECMARK]	= "secmark",
	[NFT_OBJECT_SYNPROXY]	= "synproxy",
	[NFT_OBJECT_CT_EXPECT]	= "ct expectation",
};

const char *obj_type_name(enum stmt_types type)
{
	assert(type <= NFT_OBJECT_MAX && obj_type_name_array[type]);

	return obj_type_name_array[type];
}

static uint32_t obj_type_cmd_array[NFT_OBJECT_MAX + 1] = {
	[NFT_OBJECT_COUNTER]	= CMD_OBJ_COUNTER,
	[NFT_OBJECT_QUOTA]	= CMD_OBJ_QUOTA,
	[NFT_OBJECT_CT_HELPER]	= CMD_OBJ_CT_HELPER,
	[NFT_OBJECT_LIMIT]	= CMD_OBJ_LIMIT,
	[NFT_OBJECT_CT_TIMEOUT] = CMD_OBJ_CT_TIMEOUT,
	[NFT_OBJECT_SECMARK]	= CMD_OBJ_SECMARK,
	[NFT_OBJECT_SYNPROXY]	= CMD_OBJ_SYNPROXY,
	[NFT_OBJECT_CT_EXPECT]	= CMD_OBJ_CT_EXPECT,
};

uint32_t obj_type_to_cmd(uint32_t type)
{
	assert(type <= NFT_OBJECT_MAX && obj_type_cmd_array[type]);

	return obj_type_cmd_array[type];
}

static void obj_print_declaration(const struct obj *obj,
				  struct print_fmt_options *opts,
				  struct output_ctx *octx)
{
	nft_print(octx, "%s%s", opts->tab, obj_type_name(obj->type));

	if (opts->family != NULL)
		nft_print(octx, " %s", opts->family);

	if (opts->table != NULL)
		nft_print(octx, " %s", opts->table);

	obj_print_data(obj, opts, octx);

	nft_print(octx, "%s}%s", opts->tab, opts->nl);
}

void obj_print(const struct obj *obj, struct output_ctx *octx)
{
	struct print_fmt_options opts = {
		.tab		= "\t",
		.nl		= "\n",
		.stmt_separator	= "\n",
	};

	obj_print_declaration(obj, &opts, octx);
}

void obj_print_plain(const struct obj *obj, struct output_ctx *octx)
{
	struct print_fmt_options opts = {
		.tab		= "",
		.nl		= " ",
		.table		= obj->handle.table.name,
		.family		= family2str(obj->handle.family),
		.stmt_separator = "; ",
	};

	obj_print_declaration(obj, &opts, octx);
}

static int do_list_obj(struct netlink_ctx *ctx, struct cmd *cmd, uint32_t type)
{
	struct print_fmt_options opts = {
		.tab		= "\t",
		.nl		= "\n",
		.stmt_separator	= "\n",
	};
	struct table *table;
	struct obj *obj;

	list_for_each_entry(table, &ctx->nft->cache.list, list) {
		if (cmd->handle.family != NFPROTO_UNSPEC &&
		    cmd->handle.family != table->handle.family)
			continue;

		if (cmd->handle.table.name != NULL &&
		    strcmp(cmd->handle.table.name, table->handle.table.name))
			continue;

		if (list_empty(&table->objs))
			continue;

		nft_print(&ctx->nft->output, "table %s %s {\n",
			  family2str(table->handle.family),
			  table->handle.table.name);

		list_for_each_entry(obj, &table->objs, list) {
			if (obj->type != type ||
			    (cmd->handle.obj.name != NULL &&
			     strcmp(cmd->handle.obj.name, obj->handle.obj.name)))
				continue;

			obj_print_declaration(obj, &opts, &ctx->nft->output);
		}

		nft_print(&ctx->nft->output, "}\n");
	}
	return 0;
}

struct flowtable *flowtable_alloc(const struct location *loc)
{
	struct flowtable *flowtable;

	flowtable = xzalloc(sizeof(*flowtable));
	if (loc != NULL)
		flowtable->location = *loc;

	flowtable->refcnt = 1;
	return flowtable;
}

struct flowtable *flowtable_get(struct flowtable *flowtable)
{
	flowtable->refcnt++;
	return flowtable;
}

void flowtable_free(struct flowtable *flowtable)
{
	int i;

	if (--flowtable->refcnt > 0)
		return;
	handle_free(&flowtable->handle);
	expr_free(flowtable->priority.expr);
	expr_free(flowtable->dev_expr);

	if (flowtable->dev_array != NULL) {
		for (i = 0; i < flowtable->dev_array_len; i++)
			xfree(flowtable->dev_array[i]);
		xfree(flowtable->dev_array);
	}
	xfree(flowtable);
}

void flowtable_add_hash(struct flowtable *flowtable, struct table *table)
{
	list_add_tail(&flowtable->list, &table->flowtables);
}

static void flowtable_print_declaration(const struct flowtable *flowtable,
					struct print_fmt_options *opts,
					struct output_ctx *octx)
{
	char priobuf[STD_PRIO_BUFSIZE];
	int i;

	nft_print(octx, "%sflowtable", opts->tab);

	if (opts->family != NULL)
		nft_print(octx, " %s", opts->family);

	if (opts->table != NULL)
		nft_print(octx, " %s", opts->table);

	nft_print(octx, " %s {", flowtable->handle.flowtable.name);

	if (nft_output_handle(octx))
		nft_print(octx, " # handle %" PRIu64, flowtable->handle.handle.id);
	nft_print(octx, "%s", opts->nl);
	nft_print(octx, "%s%shook %s priority %s%s",
		  opts->tab, opts->tab,
		  hooknum2str(NFPROTO_NETDEV, flowtable->hook.num),
		  prio2str(octx, priobuf, sizeof(priobuf), NFPROTO_NETDEV,
			   flowtable->hook.num, flowtable->priority.expr),
		  opts->stmt_separator);

	if (flowtable->dev_array_len > 0) {
		nft_print(octx, "%s%sdevices = { ", opts->tab, opts->tab);
		for (i = 0; i < flowtable->dev_array_len; i++) {
			nft_print(octx, "%s", flowtable->dev_array[i]);
			if (i + 1 != flowtable->dev_array_len)
				nft_print(octx, ", ");
		}
		nft_print(octx, " }%s", opts->stmt_separator);
	}

	if (flowtable->flags & NFT_FLOWTABLE_COUNTER)
		nft_print(octx, "%s%scounter%s", opts->tab, opts->tab,
			  opts->stmt_separator);
}

static void do_flowtable_print(const struct flowtable *flowtable,
			       struct print_fmt_options *opts,
			       struct output_ctx *octx)
{
	flowtable_print_declaration(flowtable, opts, octx);
	nft_print(octx, "%s}%s", opts->tab, opts->nl);
}

void flowtable_print(const struct flowtable *s, struct output_ctx *octx)
{
	struct print_fmt_options opts = {
		.tab		= "\t",
		.nl		= "\n",
		.stmt_separator	= "\n",
	};

	do_flowtable_print(s, &opts, octx);
}

struct flowtable *flowtable_lookup(const struct table *table, const char *name)
{
	struct flowtable *ft;

	list_for_each_entry(ft, &table->flowtables, list) {
		if (!strcmp(ft->handle.flowtable.name, name))
			return ft;
	}
	return NULL;
}

struct flowtable *flowtable_lookup_fuzzy(const char *ft_name,
					 const struct nft_cache *cache,
					 const struct table **t)
{
	struct string_misspell_state st;
	struct table *table;
	struct flowtable *ft;

	string_misspell_init(&st);

	list_for_each_entry(table, &cache->list, list) {
		list_for_each_entry(ft, &table->flowtables, list) {
			if (!strcmp(ft->handle.flowtable.name, ft_name)) {
				*t = table;
				return ft;
			}
			if (string_misspell_update(ft->handle.flowtable.name,
						   ft_name, ft, &st))
				*t = table;
		}
	}
	return st.obj;
}

static int do_list_flowtable(struct netlink_ctx *ctx, struct cmd *cmd,
			     struct table *table)
{
	struct flowtable *ft;

	ft = flowtable_lookup(table, cmd->handle.flowtable.name);
	if (ft == NULL)
		return -1;

	nft_print(&ctx->nft->output, "table %s %s {\n",
		  family2str(table->handle.family),
		  table->handle.table.name);

	flowtable_print(ft, &ctx->nft->output);
	nft_print(&ctx->nft->output, "}\n");

	return 0;
}

static int do_list_flowtables(struct netlink_ctx *ctx, struct cmd *cmd)
{
	struct print_fmt_options opts = {
		.tab		= "\t",
		.nl		= "\n",
		.stmt_separator	= "\n",
	};
	struct flowtable *flowtable;
	struct table *table;

	list_for_each_entry(table, &ctx->nft->cache.list, list) {
		if (cmd->handle.family != NFPROTO_UNSPEC &&
		    cmd->handle.family != table->handle.family)
			continue;

		nft_print(&ctx->nft->output, "table %s %s {\n",
			  family2str(table->handle.family),
			  table->handle.table.name);

		list_for_each_entry(flowtable, &table->flowtables, list) {
			flowtable_print_declaration(flowtable, &opts, &ctx->nft->output);
			nft_print(&ctx->nft->output, "%s}%s", opts.tab, opts.nl);
		}

		nft_print(&ctx->nft->output, "}\n");
	}
	return 0;
}

static int do_list_ruleset(struct netlink_ctx *ctx, struct cmd *cmd)
{
	unsigned int family = cmd->handle.family;
	struct table *table;

	list_for_each_entry(table, &ctx->nft->cache.list, list) {
		if (family != NFPROTO_UNSPEC &&
		    table->handle.family != family)
			continue;

		cmd->handle.family = table->handle.family;
		cmd->handle.table.name = table->handle.table.name;

		if (do_list_table(ctx, cmd, table) < 0)
			return -1;
	}

	cmd->handle.table.name = NULL;

	return 0;
}

static int do_list_tables(struct netlink_ctx *ctx, struct cmd *cmd)
{
	struct table *table;

	list_for_each_entry(table, &ctx->nft->cache.list, list) {
		if (cmd->handle.family != NFPROTO_UNSPEC &&
		    cmd->handle.family != table->handle.family)
			continue;

		nft_print(&ctx->nft->output, "table %s %s\n",
			  family2str(table->handle.family),
			  table->handle.table.name);
	}

	return 0;
}

static void table_print_declaration(struct table *table,
				    struct output_ctx *octx)
{
	nft_print(octx, "table %s %s {\n",
		  family2str(table->handle.family),
		  table->handle.table.name);
}

static int do_list_chain(struct netlink_ctx *ctx, struct cmd *cmd,
			 struct table *table)
{
	struct chain *chain;

	table_print_declaration(table, &ctx->nft->output);

	list_for_each_entry(chain, &table->chains, list) {
		if (chain->handle.family != cmd->handle.family ||
		    strcmp(cmd->handle.chain.name, chain->handle.chain.name) != 0)
			continue;

		chain_print(chain, &ctx->nft->output);
	}

	nft_print(&ctx->nft->output, "}\n");

	return 0;
}

static int do_list_chains(struct netlink_ctx *ctx, struct cmd *cmd)
{
	struct table *table;
	struct chain *chain;

	list_for_each_entry(table, &ctx->nft->cache.list, list) {
		if (cmd->handle.family != NFPROTO_UNSPEC &&
		    cmd->handle.family != table->handle.family)
			continue;

		table_print_declaration(table, &ctx->nft->output);

		list_for_each_entry(chain, &table->chains, list) {
			chain_print_declaration(chain, &ctx->nft->output);
			nft_print(&ctx->nft->output, "\t}\n");
		}
		nft_print(&ctx->nft->output, "}\n");
	}

	return 0;
}

static void __do_list_set(struct netlink_ctx *ctx, struct cmd *cmd,
			  struct set *set)
{
	struct table *table = table_alloc();

	table->handle.table.name = xstrdup(cmd->handle.table.name);
	table->handle.family = cmd->handle.family;
	table_print_declaration(table, &ctx->nft->output);
	table_free(table);

	set_print(set, &ctx->nft->output);
	nft_print(&ctx->nft->output, "}\n");
}

static int do_list_set(struct netlink_ctx *ctx, struct cmd *cmd,
		       struct table *table)
{
	struct set *set;

	set = set_lookup(table, cmd->handle.set.name);
	if (set == NULL)
		return -1;

	__do_list_set(ctx, cmd, set);

	return 0;
}

static int do_command_list(struct netlink_ctx *ctx, struct cmd *cmd)
{
	struct table *table = NULL;

	if (nft_output_json(&ctx->nft->output))
		return do_command_list_json(ctx, cmd);

	if (cmd->handle.table.name != NULL)
		table = table_lookup(&cmd->handle, &ctx->nft->cache);

	switch (cmd->obj) {
	case CMD_OBJ_TABLE:
		if (!cmd->handle.table.name)
			return do_list_tables(ctx, cmd);
		return do_list_table(ctx, cmd, table);
	case CMD_OBJ_CHAIN:
		return do_list_chain(ctx, cmd, table);
	case CMD_OBJ_CHAINS:
		return do_list_chains(ctx, cmd);
	case CMD_OBJ_SETS:
		return do_list_sets(ctx, cmd);
	case CMD_OBJ_SET:
		return do_list_set(ctx, cmd, table);
	case CMD_OBJ_RULESET:
		return do_list_ruleset(ctx, cmd);
	case CMD_OBJ_METERS:
		return do_list_sets(ctx, cmd);
	case CMD_OBJ_METER:
		return do_list_set(ctx, cmd, table);
	case CMD_OBJ_MAPS:
		return do_list_sets(ctx, cmd);
	case CMD_OBJ_MAP:
		return do_list_set(ctx, cmd, table);
	case CMD_OBJ_COUNTER:
	case CMD_OBJ_COUNTERS:
		return do_list_obj(ctx, cmd, NFT_OBJECT_COUNTER);
	case CMD_OBJ_QUOTA:
	case CMD_OBJ_QUOTAS:
		return do_list_obj(ctx, cmd, NFT_OBJECT_QUOTA);
	case CMD_OBJ_CT_HELPER:
	case CMD_OBJ_CT_HELPERS:
		return do_list_obj(ctx, cmd, NFT_OBJECT_CT_HELPER);
	case CMD_OBJ_CT_TIMEOUT:
		return do_list_obj(ctx, cmd, NFT_OBJECT_CT_TIMEOUT);
	case CMD_OBJ_CT_EXPECT:
		return do_list_obj(ctx, cmd, NFT_OBJECT_CT_EXPECT);
	case CMD_OBJ_LIMIT:
	case CMD_OBJ_LIMITS:
		return do_list_obj(ctx, cmd, NFT_OBJECT_LIMIT);
	case CMD_OBJ_SECMARK:
	case CMD_OBJ_SECMARKS:
		return do_list_obj(ctx, cmd, NFT_OBJECT_SECMARK);
	case CMD_OBJ_SYNPROXY:
	case CMD_OBJ_SYNPROXYS:
		return do_list_obj(ctx, cmd, NFT_OBJECT_SYNPROXY);
	case CMD_OBJ_FLOWTABLE:
		return do_list_flowtable(ctx, cmd, table);
	case CMD_OBJ_FLOWTABLES:
		return do_list_flowtables(ctx, cmd);
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}

	return 0;
}

static int do_get_setelems(struct netlink_ctx *ctx, struct cmd *cmd)
{
	struct set *set, *new_set;
	struct expr *init;
	int err;

	set = cmd->elem.set;

	/* Create a list of elements based of what we got from command line. */
	if (set_is_non_concat_range(set))
		init = get_set_intervals(set, cmd->expr);
	else
		init = cmd->expr;

	new_set = set_clone(set);

	/* Fetch from kernel the elements that have been requested .*/
	err = netlink_get_setelem(ctx, &cmd->handle, &cmd->location,
				  cmd->elem.set, new_set, init);
	if (err >= 0)
		__do_list_set(ctx, cmd, new_set);

	if (set_is_non_concat_range(set))
		expr_free(init);

	set_free(new_set);

	return err;
}

static int do_command_get(struct netlink_ctx *ctx, struct cmd *cmd)
{
	switch (cmd->obj) {
	case CMD_OBJ_ELEMENTS:
		return do_get_setelems(ctx, cmd);
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}

	return 0;
}

static int do_command_reset(struct netlink_ctx *ctx, struct cmd *cmd)
{
	struct obj *obj, *next;
	struct table *table;
	bool dump = false;
	uint32_t type;
	int ret;

	switch (cmd->obj) {
	case CMD_OBJ_COUNTERS:
		dump = true;
		/* fall through */
	case CMD_OBJ_COUNTER:
		type = NFT_OBJECT_COUNTER;
		break;
	case CMD_OBJ_QUOTAS:
		dump = true;
		/* fall through */
	case CMD_OBJ_QUOTA:
		type = NFT_OBJECT_QUOTA;
		break;
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}

	ret = netlink_reset_objs(ctx, cmd, type, dump);
	list_for_each_entry_safe(obj, next, &ctx->list, list) {
		table = table_lookup(&obj->handle, &ctx->nft->cache);
		if (!obj_lookup(table, obj->handle.obj.name, obj->type))
			list_move(&obj->list, &table->objs);
	}
	if (ret < 0)
		return ret;

	return do_command_list(ctx, cmd);
}

static int do_command_flush(struct netlink_ctx *ctx, struct cmd *cmd)
{
	switch (cmd->obj) {
	case CMD_OBJ_TABLE:
	case CMD_OBJ_CHAIN:
		return mnl_nft_rule_del(ctx, cmd);
	case CMD_OBJ_SET:
	case CMD_OBJ_MAP:
	case CMD_OBJ_METER:
		return mnl_nft_setelem_flush(ctx, cmd);
	case CMD_OBJ_RULESET:
		return mnl_nft_table_del(ctx, cmd);
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}
	return 0;
}

static int do_command_rename(struct netlink_ctx *ctx, struct cmd *cmd)
{
	struct table *table = table_lookup(&cmd->handle, &ctx->nft->cache);
	const struct chain *chain;

	switch (cmd->obj) {
	case CMD_OBJ_CHAIN:
		chain = chain_lookup(table, &cmd->handle);

		return mnl_nft_chain_rename(ctx, cmd, chain);
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}
	return 0;
}

static int do_command_monitor(struct netlink_ctx *ctx, struct cmd *cmd)
{
	struct netlink_mon_handler monhandler = {
		.monitor_flags	= cmd->monitor->flags,
		.format		= cmd->monitor->format,
		.ctx		= ctx,
		.loc		= &cmd->location,
		.cache		= &ctx->nft->cache,
		.debug_mask	= ctx->nft->debug_mask,
	};

	if (nft_output_json(&ctx->nft->output))
		monhandler.format = NFTNL_OUTPUT_JSON;

	return netlink_monitor(&monhandler, ctx->nft->nf_sock);
}

static int do_command_describe(struct netlink_ctx *ctx, struct cmd *cmd,
			       struct output_ctx *octx)
{
	expr_describe(cmd->expr, octx);
	return 0;
}

struct cmd *cmd_alloc_obj_ct(enum cmd_ops op, int type, const struct handle *h,
			     const struct location *loc, struct obj *obj)
{
	enum cmd_obj cmd_obj;

	if (obj)
		obj->type = type;

	switch (type) {
	case NFT_OBJECT_CT_HELPER:
		cmd_obj = CMD_OBJ_CT_HELPER;
		break;
	case NFT_OBJECT_CT_TIMEOUT:
		cmd_obj = CMD_OBJ_CT_TIMEOUT;
		break;
	case NFT_OBJECT_CT_EXPECT:
		cmd_obj = CMD_OBJ_CT_EXPECT;
		break;
	default:
		BUG("missing type mapping");
	}

	return cmd_alloc(op, cmd_obj, h, loc, obj);
}

int do_command(struct netlink_ctx *ctx, struct cmd *cmd)
{
	switch (cmd->op) {
	case CMD_ADD:
		return do_command_add(ctx, cmd, false);
	case CMD_CREATE:
		return do_command_add(ctx, cmd, true);
	case CMD_INSERT:
		return do_command_insert(ctx, cmd);
	case CMD_REPLACE:
		return do_command_replace(ctx, cmd);
	case CMD_DELETE:
		return do_command_delete(ctx, cmd);
	case CMD_GET:
		return do_command_get(ctx, cmd);
	case CMD_LIST:
		return do_command_list(ctx, cmd);
	case CMD_RESET:
		return do_command_reset(ctx, cmd);
	case CMD_FLUSH:
		return do_command_flush(ctx, cmd);
	case CMD_RENAME:
		return do_command_rename(ctx, cmd);
	case CMD_IMPORT:
	case CMD_EXPORT:
		errno = EOPNOTSUPP;
		return -1;
	case CMD_MONITOR:
		return do_command_monitor(ctx, cmd);
	case CMD_DESCRIBE:
		return do_command_describe(ctx, cmd, &ctx->nft->output);
	default:
		BUG("invalid command object type %u\n", cmd->obj);
	}
}

static int payload_match_stmt_cmp(const void *p1, const void *p2)
{
	const struct stmt *s1 = *(struct stmt * const *)p1;
	const struct stmt *s2 = *(struct stmt * const *)p2;
	const struct expr *e1 = s1->expr, *e2 = s2->expr;
	int d;

	d = e1->left->payload.base - e2->left->payload.base;
	if (d != 0)
		return d;
	return e1->left->payload.offset - e2->left->payload.offset;
}

static bool relational_ops_match(const struct expr *e1, const struct expr *e2)
{
	enum ops op1, op2;

	op1 = e1->op == OP_IMPLICIT ? OP_EQ : e1->op;
	op2 = e2->op == OP_IMPLICIT ? OP_EQ : e2->op;

	return op1 == op2;
}

static void payload_do_merge(struct stmt *sa[], unsigned int n)
{
	struct expr *last, *this, *expr1, *expr2;
	struct stmt *stmt;
	unsigned int i, j;

	qsort(sa, n, sizeof(sa[0]), payload_match_stmt_cmp);

	last = sa[0]->expr;
	for (j = 0, i = 1; i < n; i++) {
		stmt = sa[i];
		this = stmt->expr;

		if (!payload_can_merge(last->left, this->left) ||
		    !relational_ops_match(last, this)) {
			last = this;
			j = i;
			continue;
		}

		expr1 = payload_expr_join(last->left, this->left);
		expr2 = constant_expr_join(last->right, this->right);

		/* We can merge last into this, but we can't replace
		 * the statement associated with this if it does contain
		 * a higher level protocol.
		 *
		 * ether type ip ip saddr X ether saddr Y
		 * ... can be changed to
		 * ether type ip ether saddr Y ip saddr X
		 * ... but not
		 * ip saddr X ether type ip ether saddr Y
		 *
		 * The latter form means we perform ip saddr test before
		 * ensuring ip dependency, plus it makes decoding harder
		 * since we don't know the type of the network header
		 * right away.
		 *
		 * So, if we're about to replace a statement
		 * containing a protocol identifier, just swap this and last
		 * and replace the other one (i.e., replace 'load ether type ip'
		 * with the combined 'load both ether type and saddr') and not
		 * the other way around.
		 */
		if (this->left->flags & EXPR_F_PROTOCOL) {
			struct expr *tmp = last;

			last = this;
			this = tmp;

			expr1->flags |= EXPR_F_PROTOCOL;
			stmt = sa[j];
			assert(stmt->expr == this);
			j = i;
		}

		expr_free(last->left);
		last->left = expr1;

		expr_free(last->right);
		last->right = expr2;

		list_del(&stmt->list);
		stmt_free(stmt);
	}
}

/**
 * payload_try_merge - try to merge consecutive payload match statements
 *
 * @rule:	nftables rule
 *
 * Locate sequences of payload match statements referring to adjacent
 * header locations and merge those using only equality relations.
 *
 * As a side-effect, payload match statements are ordered in ascending
 * order according to the location of the payload.
 */
static void payload_try_merge(const struct rule *rule)
{
	struct stmt *sa[rule->num_stmts];
	struct stmt *stmt, *next;
	unsigned int idx = 0;

	list_for_each_entry_safe(stmt, next, &rule->stmts, list) {
		/* Must not merge across other statements */
		if (stmt->ops->type != STMT_EXPRESSION)
			goto do_merge;

		if (stmt->expr->etype != EXPR_RELATIONAL)
			continue;
		if (stmt->expr->left->etype != EXPR_PAYLOAD)
			continue;
		if (stmt->expr->right->etype != EXPR_VALUE)
			continue;
		switch (stmt->expr->op) {
		case OP_EQ:
		case OP_IMPLICIT:
		case OP_NEQ:
			break;
		default:
			continue;
		}

		sa[idx++] = stmt;
		continue;
do_merge:
		if (idx < 2)
			continue;
		payload_do_merge(sa, idx);
		idx = 0;
	}

	if (idx > 1)
		payload_do_merge(sa, idx);
}

struct error_record *rule_postprocess(struct rule *rule)
{
	payload_try_merge(rule);
	return NULL;
}
