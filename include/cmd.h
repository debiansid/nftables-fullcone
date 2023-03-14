#ifndef _NFT_CMD_H_
#define _NFT_CMD_H_

void cmd_add_loc(struct cmd *cmd, uint16_t offset, const struct location *loc);
void nft_cmd_error(struct netlink_ctx *ctx, struct cmd *cmd,
		   struct mnl_err *err);

void nft_cmd_expand(struct cmd *cmd);
void nft_cmd_post_expand(struct cmd *cmd);
bool nft_cmd_collapse(struct list_head *cmds);
void nft_cmd_uncollapse(struct list_head *cmds);

#endif
