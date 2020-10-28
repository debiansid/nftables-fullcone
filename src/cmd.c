#include <erec.h>
#include <mnl.h>
#include <cmd.h>
#include <parser.h>
#include <utils.h>
#include <iface.h>
#include <errno.h>
#include <stdlib.h>
#include <cache.h>
#include <string.h>

static int nft_cmd_enoent_table(struct netlink_ctx *ctx, const struct cmd *cmd,
				const struct location *loc)
{
	struct table *table;

	table = table_lookup_fuzzy(&cmd->handle, &ctx->nft->cache);
	if (!table)
		return 0;

	netlink_io_error(ctx, loc, "%s; did you mean table ‘%s’ in family %s?",
			 strerror(ENOENT), table->handle.table.name,
			 family2str(table->handle.family));
	return 1;
}

static int nft_cmd_enoent_chain(struct netlink_ctx *ctx, const struct cmd *cmd,
				const struct location *loc)
{
	const struct table *table;
	struct chain *chain;

	chain = chain_lookup_fuzzy(&cmd->handle, &ctx->nft->cache, &table);
	if (!chain)
		return 0;

	netlink_io_error(ctx, loc, "%s; did you mean table ‘%s’ in family %s?",
			 strerror(ENOENT), chain->handle.chain.name,
			 family2str(table->handle.family),
			 table->handle.table.name);
	return 1;
}

static int nft_cmd_enoent_rule(struct netlink_ctx *ctx, const struct cmd *cmd,
			       const struct location *loc)
{
	unsigned int flags = NFT_CACHE_TABLE |
			     NFT_CACHE_CHAIN;
	const struct table *table;
	struct chain *chain;

	if (cache_update(ctx->nft, flags, ctx->msgs) < 0)
		return 0;

	table = table_lookup_fuzzy(&cmd->handle, &ctx->nft->cache);
	if (table && strcmp(cmd->handle.table.name, table->handle.table.name)) {
		netlink_io_error(ctx, loc, "%s; did you mean table ‘%s’ in family %s?",
				 strerror(ENOENT), table->handle.table.name,
				 family2str(table->handle.family));
		return 1;
	} else if (!table) {
		return 0;
	}

	chain = chain_lookup_fuzzy(&cmd->handle, &ctx->nft->cache, &table);
	if (chain && strcmp(cmd->handle.chain.name, chain->handle.chain.name)) {
		netlink_io_error(ctx, loc, "%s; did you mean chain ‘%s’ in table %s ‘%s’?",
				 strerror(ENOENT),
				 chain->handle.chain.name,
				 family2str(table->handle.family),
				 table->handle.table.name);
		return 1;
	}

	return 0;
}

static int nft_cmd_enoent_set(struct netlink_ctx *ctx, const struct cmd *cmd,
			      const struct location *loc)
{
	const struct table *table;
	struct set *set;

	set = set_lookup_fuzzy(cmd->handle.set.name, &ctx->nft->cache, &table);
	if (!set)
		return 0;

	netlink_io_error(ctx, loc, "%s; did you mean %s ‘%s’ in table %s ‘%s’?",
			 strerror(ENOENT),
			 set_is_map(set->flags) ? "map" : "set",
			 set->handle.set.name,
			 family2str(set->handle.family),
			 table->handle.table.name);
	return 1;
}

static int nft_cmd_enoent_obj(struct netlink_ctx *ctx, const struct cmd *cmd,
			      const struct location *loc)
{
	const struct table *table;
	struct obj *obj;

	obj = obj_lookup_fuzzy(cmd->handle.obj.name, &ctx->nft->cache, &table);
	if (!obj)
		return 0;

	netlink_io_error(ctx, loc, "%s; did you mean obj ‘%s’ in table %s ‘%s’?",
			 strerror(ENOENT), obj->handle.obj.name,
			 family2str(obj->handle.family),
			 table->handle.table.name);
	return 1;
}

static int nft_cmd_enoent_flowtable(struct netlink_ctx *ctx,
				    const struct cmd *cmd,
				    const struct location *loc)
{
	const struct table *table;
	struct flowtable *ft;

	ft = flowtable_lookup_fuzzy(cmd->handle.flowtable.name,
				    &ctx->nft->cache, &table);
	if (!ft)
		return 0;

	netlink_io_error(ctx, loc, "%s; did you mean flowtable ‘%s’ in table %s ‘%s’?",
			 strerror(ENOENT), ft->handle.flowtable.name,
			 family2str(ft->handle.family),
			 table->handle.table.name);
	return 1;
}

static void nft_cmd_enoent(struct netlink_ctx *ctx, const struct cmd *cmd,
			   const struct location *loc, int err)
{
	int ret = 0;

	switch (cmd->obj) {
	case CMD_OBJ_TABLE:
		ret = nft_cmd_enoent_table(ctx, cmd, loc);
		break;
	case CMD_OBJ_CHAIN:
		ret = nft_cmd_enoent_chain(ctx, cmd, loc);
		break;
	case CMD_OBJ_SET:
		ret = nft_cmd_enoent_set(ctx, cmd, loc);
		break;
	case CMD_OBJ_RULE:
		ret = nft_cmd_enoent_rule(ctx, cmd, loc);
		break;
	case CMD_OBJ_COUNTER:
	case CMD_OBJ_QUOTA:
	case CMD_OBJ_CT_HELPER:
	case CMD_OBJ_CT_TIMEOUT:
	case CMD_OBJ_LIMIT:
	case CMD_OBJ_SECMARK:
	case CMD_OBJ_CT_EXPECT:
	case CMD_OBJ_SYNPROXY:
		ret = nft_cmd_enoent_obj(ctx, cmd, loc);
		break;
	case CMD_OBJ_FLOWTABLE:
		ret = nft_cmd_enoent_flowtable(ctx, cmd, loc);
		break;
	default:
		break;
	}

	if (ret)
		return;

	netlink_io_error(ctx, loc, "Could not process rule: %s", strerror(err));
}

void nft_cmd_error(struct netlink_ctx *ctx, struct cmd *cmd,
		   struct mnl_err *err)
{
	const struct location *loc = NULL;
	int i;

	for (i = 0; i < cmd->num_attrs; i++) {
		if (!cmd->attr[i].offset)
			break;
		if (cmd->attr[i].offset == err->offset)
			loc = cmd->attr[i].location;
	}

	if (loc) {
		if (err->err == ENOENT) {
			nft_cmd_enoent(ctx, cmd, loc, err->err);
			return;
		}
	} else {
		loc = &cmd->location;
	}

	netlink_io_error(ctx, loc, "Could not process rule: %s",
			 strerror(err->err));
}
