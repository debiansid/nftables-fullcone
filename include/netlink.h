#ifndef NFTABLES_NETLINK_H
#define NFTABLES_NETLINK_H

#include <libnftnl/table.h>
#include <libnftnl/chain.h>
#include <libnftnl/rule.h>
#include <libnftnl/expr.h>
#include <libnftnl/set.h>

#include <linux/netlink.h>
#include <linux/netfilter/nf_tables.h>

#include <rule.h>

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
 */
struct netlink_ctx {
	struct list_head	*msgs;
	struct list_head	list;
	struct set		*set;
	const void		*data;
	uint32_t		seqnum;
	bool			batch_supported;
};

extern struct nft_table *alloc_nft_table(const struct handle *h);
extern struct nft_chain *alloc_nft_chain(const struct handle *h);
extern struct nft_rule *alloc_nft_rule(const struct handle *h);
extern struct nft_rule_expr *alloc_nft_expr(const char *name);
extern struct nft_set *alloc_nft_set(const struct handle *h);

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
				   struct nft_rule *nlr,
				   const struct rule *rule);
extern struct rule *netlink_delinearize_rule(struct netlink_ctx *ctx,
					     const struct nft_rule *r);

extern int netlink_add_rule(struct netlink_ctx *ctx, const struct handle *h,
			    const struct rule *rule, uint32_t flags);
extern int netlink_delete_rule(struct netlink_ctx *ctx, const struct handle *h,
			       const struct location *loc);
extern int netlink_add_rule_list(struct netlink_ctx *ctx, const struct handle *h,
				 struct list_head *rule_list);
extern int netlink_add_rule_batch(struct netlink_ctx *ctx,
				  const struct handle *h,
				  const struct rule *rule, uint32_t flags);
extern int netlink_del_rule_batch(struct netlink_ctx *ctx,
				  const struct handle *h,
				  const struct location *loc);

extern int netlink_add_chain(struct netlink_ctx *ctx, const struct handle *h,
			     const struct location *loc,
			     const struct chain *chain, bool excl);
extern int netlink_rename_chain(struct netlink_ctx *ctx, const struct handle *h,
				const struct location *loc, const char *name);
extern int netlink_delete_chain(struct netlink_ctx *ctx, const struct handle *h,
				const struct location *loc);
extern int netlink_list_chains(struct netlink_ctx *ctx, const struct handle *h,
			       const struct location *loc);
extern int netlink_get_chain(struct netlink_ctx *ctx, const struct handle *h,
			     const struct location *loc);
extern int netlink_list_chain(struct netlink_ctx *ctx, const struct handle *h,
			      const struct location *loc);
extern int netlink_flush_chain(struct netlink_ctx *ctx, const struct handle *h,
			       const struct location *loc);

extern int netlink_add_table(struct netlink_ctx *ctx, const struct handle *h,
			     const struct location *loc,
			     const struct table *table, bool excl);
extern int netlink_delete_table(struct netlink_ctx *ctx, const struct handle *h,
				const struct location *loc);
extern int netlink_list_tables(struct netlink_ctx *ctx, const struct handle *h,
			       const struct location *loc);
extern int netlink_get_table(struct netlink_ctx *ctx, const struct handle *h,
			     const struct location *loc);
extern int netlink_list_table(struct netlink_ctx *ctx, const struct handle *h,
			      const struct location *loc);
extern int netlink_flush_table(struct netlink_ctx *ctx, const struct handle *h,
			       const struct location *loc);

extern int netlink_add_set(struct netlink_ctx *ctx, const struct handle *h,
			   struct set *set);
extern int netlink_delete_set(struct netlink_ctx *ctx, const struct handle *h,
			      const struct location *loc);
extern int netlink_list_sets(struct netlink_ctx *ctx, const struct handle *h,
			     const struct location *loc);
extern int netlink_get_set(struct netlink_ctx *ctx, const struct handle *h,
			   const struct location *loc);

extern int netlink_add_setelems(struct netlink_ctx *ctx, const struct handle *h,
				const struct expr *expr);
extern int netlink_delete_setelems(struct netlink_ctx *ctx, const struct handle *h,
				   const struct expr *expr);
extern int netlink_get_setelems(struct netlink_ctx *ctx, const struct handle *h,
				const struct location *loc, struct set *set);

extern void netlink_dump_table(struct nft_table *nlt);
extern void netlink_dump_chain(struct nft_chain *nlc);
extern void netlink_dump_rule(struct nft_rule *nlr);
extern void netlink_dump_expr(struct nft_rule_expr *nle);
extern void netlink_dump_set(struct nft_set *nls);

extern int netlink_batch_send(struct list_head *err_list);

extern void netlink_genid_get(void);
extern void netlink_restart(void);
#define netlink_abi_error()	\
	__netlink_abi_error(__FILE__, __LINE__, strerror(errno));
extern void __noreturn __netlink_abi_error(const char *file, int line, const char *reason);
extern int netlink_io_error(struct netlink_ctx *ctx,
			    const struct location *loc, const char *fmt, ...);
extern void netlink_open_error(void) __noreturn;

extern int netlink_flush_ruleset(struct netlink_ctx *ctx,
				 const struct handle *h,
				 const struct location *loc);

extern struct nft_ruleset *netlink_dump_ruleset(struct netlink_ctx *ctx,
						const struct handle *h,
						const struct location *loc);
struct netlink_mon_handler {
	uint32_t		monitor_flags;
	uint32_t		format;
	struct netlink_ctx	*ctx;
	const struct location	*loc;
	bool			cache_needed;
};

extern int netlink_monitor(struct netlink_mon_handler *monhandler);
bool netlink_batch_supported(void);

#endif /* NFTABLES_NETLINK_H */
