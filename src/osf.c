#include <nftables.h>
#include <expression.h>
#include <utils.h>
#include <string.h>
#include <osf.h>
#include <json.h>

static const char *osf_ttl_int_to_str(const uint8_t ttl)
{
	if (ttl == 1)
		return "ttl loose ";
	else if (ttl == 2)
		return "ttl skip ";

	return "";
}

static void osf_expr_print(const struct expr *expr, struct output_ctx *octx)
{
	const char *ttl_str = osf_ttl_int_to_str(expr->osf.ttl);

	if (expr->osf.flags & NFT_OSF_F_VERSION)
		nft_print(octx, "osf %sversion", ttl_str);
	else
		nft_print(octx, "osf %sname", ttl_str);
}

static void osf_expr_clone(struct expr *new, const struct expr *expr)
{
	new->osf.ttl = expr->osf.ttl;
	new->osf.flags = expr->osf.flags;
}

static bool osf_expr_cmp(const struct expr *e1, const struct expr *e2)
{
	return (e1->osf.ttl == e2->osf.ttl) &&
	       (e1->osf.flags == e2->osf.flags);
}

const struct expr_ops osf_expr_ops = {
	.type		= EXPR_OSF,
	.name		= "osf",
	.print		= osf_expr_print,
	.clone		= osf_expr_clone,
	.cmp		= osf_expr_cmp,
	.json		= osf_expr_json,
};

struct expr *osf_expr_alloc(const struct location *loc, const uint8_t ttl,
			    const uint32_t flags)
{
	unsigned int len = NFT_OSF_MAXGENRELEN * BITS_PER_BYTE;
	const struct datatype *type = &string_type;
	struct expr *expr;

	expr = expr_alloc(loc, EXPR_OSF, type,
			  BYTEORDER_HOST_ENDIAN, len);
	expr->osf.ttl = ttl;
	expr->osf.flags = flags;

	return expr;
}
