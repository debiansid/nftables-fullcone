#ifndef NFTABLES_NFTABLES_H
#define NFTABLES_NFTABLES_H

#include <stdbool.h>
#include <stdarg.h>
#include <utils.h>

enum numeric_level {
	NUMERIC_NONE,
	NUMERIC_ADDR,
	NUMERIC_PORT,
	NUMERIC_ALL,
};

enum debug_level {
	DEBUG_SCANNER		= 0x1,
	DEBUG_PARSER		= 0x2,
	DEBUG_EVALUATION	= 0x4,
	DEBUG_NETLINK		= 0x8,
	DEBUG_MNL		= 0x10,
	DEBUG_PROTO_CTX		= 0x20,
	DEBUG_SEGTREE		= 0x40,
};

#define INCLUDE_PATHS_MAX	16

struct output_ctx {
	unsigned int numeric;
	unsigned int stateless;
	unsigned int ip2name;
	unsigned int handle;
	unsigned int echo;
	FILE *output_fp;
};

struct nft_cache {
	bool			initialized;
	struct list_head	list;
	uint32_t		seqnum;
};

struct mnl_socket;

struct nft_ctx {
	struct mnl_socket	*nf_sock;
	const char		*include_paths[INCLUDE_PATHS_MAX];
	unsigned int		num_include_paths;
	unsigned int		parser_max_errors;
	unsigned int		debug_mask;
	struct output_ctx	output;
	bool			check;
	struct nft_cache	cache;
	uint32_t		flags;
};

#define NFT_CTX_DEFAULT		0

enum nftables_exit_codes {
	NFT_EXIT_SUCCESS	= 0,
	NFT_EXIT_FAILURE	= 1,
	NFT_EXIT_NOMEM		= 2,
	NFT_EXIT_NONL		= 3,
};

struct input_descriptor;
struct location {
	const struct input_descriptor		*indesc;
	union {
		struct {
			off_t			token_offset;
			off_t			line_offset;

			unsigned int		first_line;
			unsigned int		last_line;
			unsigned int		first_column;
			unsigned int		last_column;
		};
		struct {
			const void		*nle;
		};
	};
};

extern const struct location internal_location;

/**
 * enum input_descriptor_types
 *
 * @INDESC_INVALID:	invalid
 * @INDESC_INTERNAL:	dummy type for internally generated messages
 * @INDESC_BUFFER:	buffer (command line arguments)
 * @INDESC_FILE:	file
 * @INDESC_CLI:		command line interface
 * @INDESC_NETLINK:	received from netlink
 */
enum input_descriptor_types {
	INDESC_INVALID,
	INDESC_INTERNAL,
	INDESC_BUFFER,
	INDESC_FILE,
	INDESC_CLI,
	INDESC_NETLINK,
};

/**
 * struct input_descriptor
 *
 * @location:		location, used for include statements
 * @type:		input descriptor type
 * @name:		name describing the input
 * @union:		buffer or file descriptor, depending on type
 * @lineno:		current line number in the input
 * @column:		current column in the input
 * @token_offset:	offset of the current token to the beginning
 * @line_offset:	offset of the current line to the beginning
 */
struct input_descriptor {
	struct location			location;
	enum input_descriptor_types	type;
	const char			*name;
	union {
		const char		*data;
		FILE			*fp;
	};
	unsigned int			lineno;
	unsigned int			column;
	off_t				token_offset;
	off_t				line_offset;
};

struct parser_state;
struct mnl_socket;

int nft_run(struct nft_ctx *nft, struct mnl_socket *nf_sock,
	    void *scanner, struct parser_state *state,
	    struct list_head *msgs);

void ct_label_table_init(void);
void mark_table_init(void);
void gmp_init(void);
void realm_table_rt_init(void);
void devgroup_table_init(void);
void realm_table_meta_init(void);
void xt_init(void);

void ct_label_table_exit(void);
void mark_table_exit(void);
void realm_table_meta_exit(void);
void devgroup_table_exit(void);
void realm_table_rt_exit(void);

int nft_print(struct output_ctx *octx, const char *fmt, ...)
	__attribute__((format(printf, 2, 3)));
int nft_gmp_print(struct output_ctx *octx, const char *fmt, ...)
	__attribute__((format(printf, 2, 0)));

#endif /* NFTABLES_NFTABLES_H */
