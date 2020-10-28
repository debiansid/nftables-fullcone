#ifndef _NFT_CACHE_H_
#define _NFT_CACHE_H_

enum cache_level_bits {
	NFT_CACHE_TABLE_BIT	= (1 << 0),
	NFT_CACHE_CHAIN_BIT	= (1 << 1),
	NFT_CACHE_SET_BIT	= (1 << 2),
	NFT_CACHE_FLOWTABLE_BIT	= (1 << 3),
	NFT_CACHE_OBJECT_BIT	= (1 << 4),
	NFT_CACHE_SETELEM_BIT	= (1 << 5),
	NFT_CACHE_RULE_BIT	= (1 << 6),
	__NFT_CACHE_MAX_BIT	= (1 << 7),
};

enum cache_level_flags {
	NFT_CACHE_EMPTY		= 0,
	NFT_CACHE_TABLE		= NFT_CACHE_TABLE_BIT,
	NFT_CACHE_CHAIN		= NFT_CACHE_TABLE_BIT |
				  NFT_CACHE_CHAIN_BIT,
	NFT_CACHE_SET		= NFT_CACHE_TABLE_BIT |
				  NFT_CACHE_SET_BIT,
	NFT_CACHE_FLOWTABLE	= NFT_CACHE_TABLE_BIT |
				  NFT_CACHE_FLOWTABLE_BIT,
	NFT_CACHE_OBJECT	= NFT_CACHE_TABLE_BIT |
				  NFT_CACHE_OBJECT_BIT,
	NFT_CACHE_SETELEM	= NFT_CACHE_TABLE_BIT |
				  NFT_CACHE_SET_BIT |
				  NFT_CACHE_SETELEM_BIT,
	NFT_CACHE_RULE		= NFT_CACHE_TABLE_BIT |
				  NFT_CACHE_CHAIN_BIT |
				  NFT_CACHE_RULE_BIT,
	NFT_CACHE_FULL		= __NFT_CACHE_MAX_BIT - 1,
	NFT_CACHE_REFRESH	= (1 << 29),
	NFT_CACHE_UPDATE	= (1 << 30),
	NFT_CACHE_FLUSHED	= (1 << 31),
};

static inline uint32_t djb_hash(const char *key)
{
	uint32_t i, hash = 5381;

	for (i = 0; i < strlen(key); i++)
		hash = ((hash << 5) + hash) + key[i];

	return hash;
}

#define NFT_CACHE_HSIZE 8192

struct netlink_ctx;
struct table;
struct chain;
struct handle;

struct nftnl_chain_list *chain_cache_dump(struct netlink_ctx *ctx, int *err);
int chain_cache_init(struct netlink_ctx *ctx, struct table *table,
		     struct nftnl_chain_list *chain_cache);
void chain_cache_add(struct chain *chain, struct table *table);
struct chain *chain_cache_find(const struct table *table,
			       const struct handle *handle);

#endif /* _NFT_CACHE_H_ */
