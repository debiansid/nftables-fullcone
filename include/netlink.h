#ifndef NFTABLES_NETLINK_H
#define NFTABLES_NETLINK_H

#include <libnftnl/table.h>
#include <libnftnl/chain.h>
#include <libnftnl/rule.h>
#include <libnftnl/expr.h>
#include <libnftnl/set.h>
#include <libnftnl/object.h>
#include <libnftnl/flowtable.h>

#include <linux/netlink.h>
#include <linux/netfilter/nf_tables.h>

#include <rule.h>

struct netlink_parse_ctx {
	struct list_head	*msgs;
	struct table		*table;
	struct rule		*rule;
	struct stmt		*stmt;
	struct expr		*registers[1 + NFT_REG32_15 - NFT_REG32_00 + 1];
	unsigned int		debug_mask;
};

struct rule_pp_ctx {
	struct proto_ctx	pctx;
	struct payload_dep_ctx	pdctx;
	struct stmt		*stmt;
};

extern const struct input_descriptor indesc_netlink;
extern const struct location netlink_location;

/** 
 * struct netlink_ctx
 *
 * @msgs:	message queue
 * @list:	list of parsed rules/chains/tables
 * @set:	current set
 * @data:	pointer to pass data to callback
 * @seqnum:	sequence number
 * @octx:	output context
 * @debug_mask:	display debugging information
 * @cache:	cache context
 */
struct netlink_ctx {
	struct mnl_socket	*nf_sock;
	struct list_head	*msgs;
	struct list_head	list;
	struct set		*set;
	const void		*data;
	uint32_t		seqnum;
	struct nftnl_batch	*batch;
	unsigned int		debug_mask;
	struct output_ctx	*octx;
	struct nft_cache	*cache;
};

extern struct nftnl_table *alloc_nftnl_table(const struct handle *h);
extern struct nftnl_chain *alloc_nftnl_chain(const struct handle *h);
extern struct nftnl_rule *alloc_nftnl_rule(const struct handle *h);
extern struct nftnl_expr *alloc_nft_expr(const char *name);
extern struct nftnl_set *alloc_nftnl_set(const struct handle *h);

struct nft_data_linearize {
	uint32_t	len;
	uint32_t	value[4];
	char		chain[NFT_CHAIN_MAXNAMELEN];
	int		verdict;
};

struct nft_data_delinearize {
	uint32_t	len;
	const uint32_t	*value;
	const char	*chain;
	int		verdict;
};

static inline unsigned int netlink_register_space(unsigned int size)
{
	return div_round_up(size, NFT_REG32_SIZE * BITS_PER_BYTE);
}

static inline unsigned int netlink_padded_len(unsigned int size)
{
	return netlink_register_space(size) * NFT_REG32_SIZE * BITS_PER_BYTE;
}

static inline unsigned int netlink_padding_len(unsigned int size)
{
	return netlink_padded_len(size) - size;
}

extern void netlink_gen_data(const struct expr *expr,
			     struct nft_data_linearize *data);
extern void netlink_gen_raw_data(const mpz_t value, enum byteorder byteorder,
				 unsigned int len,
				 struct nft_data_linearize *data);

extern struct expr *netlink_alloc_value(const struct location *loc,
				        const struct nft_data_delinearize *nld);
extern struct expr *netlink_alloc_data(const struct location *loc,
				       const struct nft_data_delinearize *nld,
				       enum nft_registers dreg);

extern void netlink_linearize_rule(struct netlink_ctx *ctx,
				   struct nftnl_rule *nlr,
				   const struct rule *rule);
extern struct rule *netlink_delinearize_rule(struct netlink_ctx *ctx,
					     struct nftnl_rule *r);

extern int netlink_add_rule_batch(struct netlink_ctx *ctx,
				  const struct cmd *cmd,
				  uint32_t flags);
extern int netlink_del_rule_batch(struct netlink_ctx *ctx,
				  const struct cmd *cmd);
extern int netlink_replace_rule_batch(struct netlink_ctx *ctx,
				      const struct cmd *cmd);

extern int netlink_add_chain_batch(struct netlink_ctx *ctx,
				   const struct cmd *cmd, uint32_t flags);
extern int netlink_rename_chain_batch(struct netlink_ctx *ctx,
				      const struct handle *h,
				      const struct cmd *cmd);
extern int netlink_delete_chain_batch(struct netlink_ctx *ctx,
				      const struct cmd *cmd);
extern int netlink_list_chains(struct netlink_ctx *ctx, const struct handle *h);
extern int netlink_flush_chain(struct netlink_ctx *ctx, const struct cmd *cmd);
extern struct chain *netlink_delinearize_chain(struct netlink_ctx *ctx,
					       const struct nftnl_chain *nlc);

extern int netlink_add_table_batch(struct netlink_ctx *ctx,
				   const struct cmd *cmd, uint32_t flags);
extern int netlink_delete_table_batch(struct netlink_ctx *ctx,
				      const struct cmd *cmd);
extern int netlink_list_tables(struct netlink_ctx *ctx, const struct handle *h);
extern int netlink_list_table(struct netlink_ctx *ctx, const struct handle *h);
extern int netlink_flush_table(struct netlink_ctx *ctx, const struct cmd *cmd);
extern struct table *netlink_delinearize_table(struct netlink_ctx *ctx,
					       const struct nftnl_table *nlt);

extern int netlink_add_set_batch(struct netlink_ctx *ctx, const struct cmd *cmd,
				 uint32_t flags);
extern int netlink_delete_set_batch(struct netlink_ctx *ctx,
				    const struct cmd *cmd);
extern int netlink_list_sets(struct netlink_ctx *ctx, const struct handle *h);
extern struct set *netlink_delinearize_set(struct netlink_ctx *ctx,
					   const struct nftnl_set *nls);

extern struct stmt *netlink_parse_set_expr(const struct set *set,
					   const struct nft_cache *cache,
					   const struct nftnl_expr *nle);

extern int netlink_add_setelems_batch(struct netlink_ctx *ctx, const struct handle *h,
				const struct expr *expr, uint32_t flags);
extern int netlink_delete_setelems_batch(struct netlink_ctx *ctx,
					 const struct cmd *cmd);
extern int netlink_list_setelems(struct netlink_ctx *ctx,
				 const struct handle *h, struct set *set);
extern int netlink_get_setelem(struct netlink_ctx *ctx, const struct handle *h,
			       const struct location *loc, struct table *table,
			       struct set *set, struct expr *init);
extern int netlink_flush_setelems(struct netlink_ctx *ctx, const struct cmd *cmd);
extern int netlink_delinearize_setelem(struct nftnl_set_elem *nlse,
				       const struct set *set,
				       struct nft_cache *cache);

extern int netlink_list_objs(struct netlink_ctx *ctx, const struct handle *h);
extern int netlink_reset_objs(struct netlink_ctx *ctx, const struct cmd *cmd,
			      uint32_t type, bool dump);
extern int netlink_add_obj(struct netlink_ctx *ctx, const struct cmd *cmd,
			   uint32_t flags);
extern int netlink_delete_obj(struct netlink_ctx *ctx, const struct cmd *cmd,
			      uint32_t type);
extern struct obj *netlink_delinearize_obj(struct netlink_ctx *ctx,
					   struct nftnl_obj *nlo);

extern int netlink_list_flowtables(struct netlink_ctx *ctx,
				   const struct handle *h);
extern int netlink_add_flowtable(struct netlink_ctx *ctx,
				 const struct cmd *cmd, uint32_t flags);
extern int netlink_delete_flowtable(struct netlink_ctx *ctx,
				    const struct cmd *cmd);

extern void netlink_dump_chain(const struct nftnl_chain *nlc,
			       struct netlink_ctx *ctx);
extern void netlink_dump_rule(const struct nftnl_rule *nlr,
			      struct netlink_ctx *ctx);
extern void netlink_dump_expr(const struct nftnl_expr *nle,
			      FILE *fp, unsigned int debug_mask);
extern void netlink_dump_set(const struct nftnl_set *nls,
			     struct netlink_ctx *ctx);
extern void netlink_dump_obj(struct nftnl_obj *nlo, struct netlink_ctx *ctx);

extern int netlink_batch_send(struct netlink_ctx *ctx, struct list_head *err_list);

extern uint16_t netlink_genid_get(struct netlink_ctx *ctx);
extern void netlink_restart(struct mnl_socket *nf_sock);
#define netlink_abi_error()	\
	__netlink_abi_error(__FILE__, __LINE__, strerror(errno));
extern void __noreturn __netlink_abi_error(const char *file, int line, const char *reason);
extern int netlink_io_error(struct netlink_ctx *ctx,
			    const struct location *loc, const char *fmt, ...);
#define netlink_init_error()	\
	__netlink_init_error(__FILE__, __LINE__, strerror(errno));
extern void __noreturn __netlink_init_error(const char *file, int line, const char *reason);

extern int netlink_flush_ruleset(struct netlink_ctx *ctx, const struct cmd *cmd);

extern struct nftnl_ruleset *netlink_dump_ruleset(struct netlink_ctx *ctx,
						const struct handle *h,
						const struct location *loc);
struct netlink_mon_handler {
	uint32_t		monitor_flags;
	uint32_t		format;
	struct netlink_ctx	*ctx;
	const struct location	*loc;
	unsigned int		debug_mask;
	bool			cache_needed;
	struct nft_cache	*cache;
};

extern int netlink_monitor(struct netlink_mon_handler *monhandler,
			    struct mnl_socket *nf_sock);
int netlink_echo_callback(const struct nlmsghdr *nlh, void *data);

struct ruleset_parse {
	struct netlink_ctx      *nl_ctx;
	struct cmd              *cmd;
};

struct nftnl_parse_ctx;

int netlink_markup_parse_cb(const struct nftnl_parse_ctx *ctx);

int netlink_events_trace_cb(const struct nlmsghdr *nlh, int type,
			    struct netlink_mon_handler *monh);

#endif /* NFTABLES_NETLINK_H */
