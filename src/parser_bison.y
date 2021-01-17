/*
 * Copyright (c) 2007-2012 Patrick McHardy <kaber@trash.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

%{

#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include <syslog.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/if_ether.h>
#include <linux/netfilter.h>
#include <linux/netfilter/nf_tables.h>
#include <linux/netfilter/nf_conntrack_tuple_common.h>
#include <linux/netfilter/nf_nat.h>
#include <linux/netfilter/nf_log.h>
#include <linux/netfilter/nfnetlink_osf.h>
#include <linux/netfilter/nf_synproxy.h>
#include <linux/xfrm.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <libnftnl/common.h>
#include <libnftnl/set.h>
#include <libnftnl/udata.h>

#include <rule.h>
#include <statement.h>
#include <expression.h>
#include <headers.h>
#include <utils.h>
#include <parser.h>
#include <erec.h>

#include "parser_bison.h"

void parser_init(struct nft_ctx *nft, struct parser_state *state,
		 struct list_head *msgs, struct list_head *cmds,
		 struct scope *top_scope)
{
	memset(state, 0, sizeof(*state));
	state->msgs = msgs;
	state->cmds = cmds;
	state->scopes[0] = scope_init(top_scope, NULL);
	init_list_head(&state->indesc_list);
}

static void yyerror(struct location *loc, struct nft_ctx *nft, void *scanner,
		    struct parser_state *state, const char *s)
{
	erec_queue(error(loc, "%s", s), state->msgs);
}

static struct scope *current_scope(const struct parser_state *state)
{
	return state->scopes[state->scope];
}

static void open_scope(struct parser_state *state, struct scope *scope)
{
	assert(state->scope < array_size(state->scopes) - 1);
	scope_init(scope, current_scope(state));
	state->scopes[++state->scope] = scope;
}

static void close_scope(struct parser_state *state)
{
	assert(state->scope > 0);
	state->scope--;
}

static void location_init(void *scanner, struct parser_state *state,
			  struct location *loc)
{
	memset(loc, 0, sizeof(*loc));
	loc->indesc = state->indesc;
}

static void location_update(struct location *loc, struct location *rhs, int n)
{
	if (n) {
		loc->indesc       = rhs[n].indesc;
		loc->token_offset = rhs[1].token_offset;
		loc->line_offset  = rhs[1].line_offset;
		loc->first_line   = rhs[1].first_line;
		loc->first_column = rhs[1].first_column;
		loc->last_line    = rhs[n].last_line;
		loc->last_column  = rhs[n].last_column;
	} else {
		loc->indesc       = rhs[0].indesc;
		loc->token_offset = rhs[0].token_offset;
		loc->line_offset  = rhs[0].line_offset;
		loc->first_line   = loc->last_line   = rhs[0].last_line;
		loc->first_column = loc->last_column = rhs[0].last_column;
	}
}

static struct expr *handle_concat_expr(const struct location *loc,
					 struct expr *expr,
					 struct expr *expr_l, struct expr *expr_r,
					 struct location loc_rhs[3])
{
	if (expr->etype != EXPR_CONCAT) {
		expr = concat_expr_alloc(loc);
		compound_expr_add(expr, expr_l);
	} else {
		location_update(&expr_r->location, loc_rhs, 2);

		expr = expr_l;
		expr->location = *loc;
	}

	compound_expr_add(expr, expr_r);
	return expr;
}

static bool already_set(const void *attr, const struct location *loc,
			struct parser_state *state)
{
	if (!attr)
		return false;

	erec_queue(error(loc, "You can only specify this once. This statement is duplicated."),
		   state->msgs);
	return true;
}

#define YYLLOC_DEFAULT(Current, Rhs, N)	location_update(&Current, Rhs, N)

#define symbol_value(loc, str) \
	symbol_expr_alloc(loc, SYMBOL_VALUE, current_scope(state), str)

/* Declare those here to avoid compiler warnings */
void nft_set_debug(int, void *);
int nft_lex(void *, void *, void *);
%}

/* Declaration section */

%name-prefix "nft_"
%debug
%define api.pure
%parse-param		{ struct nft_ctx *nft }
%parse-param		{ void *scanner }
%parse-param		{ struct parser_state *state }
%lex-param		{ scanner }
%define parse.error verbose
%locations

%initial-action {
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

%union {
	uint64_t		val;
	uint32_t		val32;
	uint8_t			val8;
	const char *		string;

	struct list_head	*list;
	struct cmd		*cmd;
	struct handle		handle;
	struct table		*table;
	struct chain		*chain;
	struct rule		*rule;
	struct stmt		*stmt;
	struct expr		*expr;
	struct set		*set;
	struct obj		*obj;
	struct flowtable	*flowtable;
	struct ct		*ct;
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;
	struct prio_spec	prio_spec;
}

%token TOKEN_EOF 0		"end of file"
%token JUNK			"junk"

%token NEWLINE			"newline"
%token COLON			"colon"
%token SEMICOLON		"semicolon"
%token COMMA			"comma"
%token DOT			"."

%token EQ			"=="
%token NEQ			"!="
%token LT			"<"
%token GT			">"
%token GTE			">="
%token LTE			"<="
%token LSHIFT			"<<"
%token RSHIFT			">>"
%token AMPERSAND		"&"
%token CARET			"^"
%token NOT			"!"
%token SLASH			"/"
%token ASTERISK			"*"
%token DASH			"-"
%token AT			"@"
%token VMAP			"vmap"

%token PLUS			"+"

%token INCLUDE			"include"
%token DEFINE			"define"
%token REDEFINE			"redefine"
%token UNDEFINE			"undefine"

%token FIB			"fib"

%token SOCKET			"socket"
%token TRANSPARENT		"transparent"
%token WILDCARD			"wildcard"

%token TPROXY			"tproxy"

%token OSF			"osf"

%token SYNPROXY			"synproxy"
%token MSS			"mss"
%token WSCALE			"wscale"

%token TYPEOF			"typeof"

%token HOOK			"hook"
%token DEVICE			"device"
%token DEVICES			"devices"
%token TABLE			"table"
%token TABLES			"tables"
%token CHAIN			"chain"
%token CHAINS			"chains"
%token RULE			"rule"
%token RULES			"rules"
%token SETS			"sets"
%token SET			"set"
%token ELEMENT			"element"
%token MAP			"map"
%token MAPS			"maps"
%token FLOWTABLE		"flowtable"
%token HANDLE			"handle"
%token RULESET			"ruleset"
%token TRACE			"trace"

%token INET			"inet"
%token NETDEV			"netdev"

%token ADD			"add"
%token UPDATE			"update"
%token REPLACE			"replace"
%token CREATE			"create"
%token INSERT			"insert"
%token DELETE			"delete"
%token GET			"get"
%token LIST			"list"
%token RESET			"reset"
%token FLUSH			"flush"
%token RENAME			"rename"
%token DESCRIBE			"describe"
%token IMPORT			"import"
%token EXPORT			"export"
%token MONITOR			"monitor"

%token ALL			"all"

%token ACCEPT			"accept"
%token DROP			"drop"
%token CONTINUE			"continue"
%token JUMP			"jump"
%token GOTO			"goto"
%token RETURN			"return"
%token TO			"to"

%token CONSTANT			"constant"
%token INTERVAL			"interval"
%token DYNAMIC			"dynamic"
%token AUTOMERGE		"auto-merge"
%token TIMEOUT			"timeout"
%token GC_INTERVAL		"gc-interval"
%token ELEMENTS			"elements"
%token EXPIRES			"expires"

%token POLICY			"policy"
%token MEMORY			"memory"
%token PERFORMANCE		"performance"
%token SIZE			"size"

%token FLOW			"flow"
%token OFFLOAD			"offload"
%token METER			"meter"
%token METERS			"meters"

%token FLOWTABLES		"flowtables"

%token <val> NUM		"number"
%token <string> STRING		"string"
%token <string> QUOTED_STRING	"quoted string"
%token <string> ASTERISK_STRING	"string with a trailing asterisk"
%destructor { xfree($$); }	STRING QUOTED_STRING ASTERISK_STRING

%token LL_HDR			"ll"
%token NETWORK_HDR		"nh"
%token TRANSPORT_HDR		"th"

%token BRIDGE			"bridge"

%token ETHER			"ether"
%token SADDR			"saddr"
%token DADDR			"daddr"
%token TYPE			"type"

%token VLAN			"vlan"
%token ID			"id"
%token CFI			"cfi"
%token PCP			"pcp"

%token ARP			"arp"
%token HTYPE			"htype"
%token PTYPE			"ptype"
%token HLEN			"hlen"
%token PLEN			"plen"
%token OPERATION		"operation"

%token IP			"ip"
%token HDRVERSION		"version"
%token HDRLENGTH		"hdrlength"
%token DSCP			"dscp"
%token ECN			"ecn"
%token LENGTH			"length"
%token FRAG_OFF			"frag-off"
%token TTL			"ttl"
%token PROTOCOL			"protocol"
%token CHECKSUM			"checksum"

%token PTR			"ptr"
%token VALUE			"value"

%token LSRR			"lsrr"
%token RR			"rr"
%token SSRR			"ssrr"
%token RA			"ra"

%token ICMP			"icmp"
%token CODE			"code"
%token SEQUENCE			"seq"
%token GATEWAY			"gateway"
%token MTU			"mtu"

%token IGMP			"igmp"
%token MRT			"mrt"

%token OPTIONS			"options"

%token IP6			"ip6"
%token PRIORITY			"priority"
%token FLOWLABEL		"flowlabel"
%token NEXTHDR			"nexthdr"
%token HOPLIMIT			"hoplimit"

%token ICMP6			"icmpv6"
%token PPTR			"param-problem"
%token MAXDELAY			"max-delay"

%token AH			"ah"
%token RESERVED			"reserved"
%token SPI			"spi"

%token ESP			"esp"

%token COMP			"comp"
%token FLAGS			"flags"
%token CPI			"cpi"

%token PORT			"port"
%token UDP			"udp"
%token SPORT			"sport"
%token DPORT			"dport"
%token UDPLITE			"udplite"
%token CSUMCOV			"csumcov"

%token TCP			"tcp"
%token ACKSEQ			"ackseq"
%token DOFF			"doff"
%token WINDOW			"window"
%token URGPTR			"urgptr"
%token OPTION			"option"
%token ECHO			"echo"
%token EOL			"eol"
%token NOP			"nop"
%token SACK			"sack"
%token SACK0			"sack0"
%token SACK1			"sack1"
%token SACK2			"sack2"
%token SACK3			"sack3"
%token SACK_PERM		"sack-permitted"
%token TIMESTAMP		"timestamp"
%token KIND			"kind"
%token COUNT			"count"
%token LEFT			"left"
%token RIGHT			"right"
%token TSVAL			"tsval"
%token TSECR			"tsecr"

%token DCCP			"dccp"

%token SCTP			"sctp"
%token VTAG			"vtag"

%token RT			"rt"
%token RT0			"rt0"
%token RT2			"rt2"
%token RT4			"srh"
%token SEG_LEFT			"seg-left"
%token ADDR			"addr"
%token LAST_ENT			"last-entry"
%token TAG			"tag"
%token SID			"sid"

%token HBH			"hbh"

%token FRAG			"frag"
%token RESERVED2		"reserved2"
%token MORE_FRAGMENTS		"more-fragments"

%token DST			"dst"

%token MH			"mh"

%token META			"meta"
%token MARK			"mark"
%token IIF			"iif"
%token IIFNAME			"iifname"
%token IIFTYPE			"iiftype"
%token OIF			"oif"
%token OIFNAME			"oifname"
%token OIFTYPE			"oiftype"
%token SKUID			"skuid"
%token SKGID			"skgid"
%token NFTRACE			"nftrace"
%token RTCLASSID		"rtclassid"
%token IBRIPORT			"ibriport"
%token OBRIPORT			"obriport"
%token IBRIDGENAME		"ibrname"
%token OBRIDGENAME		"obrname"
%token PKTTYPE			"pkttype"
%token CPU			"cpu"
%token IIFGROUP			"iifgroup"
%token OIFGROUP			"oifgroup"
%token CGROUP			"cgroup"
%token TIME			"time"

%token CLASSID			"classid"
%token NEXTHOP			"nexthop"

%token CT			"ct"
%token L3PROTOCOL		"l3proto"
%token PROTO_SRC		"proto-src"
%token PROTO_DST		"proto-dst"
%token ZONE			"zone"
%token DIRECTION		"direction"
%token EVENT			"event"
%token EXPECTATION		"expectation"
%token EXPIRATION		"expiration"
%token HELPER			"helper"
%token LABEL			"label"
%token STATE			"state"
%token STATUS			"status"
%token ORIGINAL			"original"
%token REPLY			"reply"

%token COUNTER			"counter"
%token NAME			"name"
%token PACKETS			"packets"
%token BYTES			"bytes"
%token AVGPKT			"avgpkt"

%token COUNTERS			"counters"
%token QUOTAS			"quotas"
%token LIMITS			"limits"
%token SYNPROXYS		"synproxys"
%token HELPERS			"helpers"

%token LOG			"log"
%token PREFIX			"prefix"
%token GROUP			"group"
%token SNAPLEN			"snaplen"
%token QUEUE_THRESHOLD		"queue-threshold"
%token LEVEL			"level"

%token LIMIT			"limit"
%token RATE			"rate"
%token BURST			"burst"
%token OVER			"over"
%token UNTIL			"until"

%token QUOTA			"quota"
%token USED			"used"

%token SECMARK			"secmark"
%token SECMARKS			"secmarks"

%token NANOSECOND		"nanosecond"
%token MICROSECOND		"microsecond"
%token MILLISECOND		"millisecond"
%token SECOND			"second"
%token MINUTE			"minute"
%token HOUR			"hour"
%token DAY			"day"
%token WEEK			"week"

%token _REJECT			"reject"
%token WITH			"with"
%token ICMPX			"icmpx"

%token SNAT			"snat"
%token DNAT			"dnat"
%token MASQUERADE		"masquerade"
%token REDIRECT			"redirect"
%token RANDOM			"random"
%token FULLY_RANDOM		"fully-random"
%token PERSISTENT		"persistent"

%token QUEUE			"queue"
%token QUEUENUM			"num"
%token BYPASS			"bypass"
%token FANOUT			"fanout"

%token DUP			"dup"
%token FWD			"fwd"

%token NUMGEN			"numgen"
%token INC			"inc"
%token MOD			"mod"
%token OFFSET			"offset"

%token JHASH			"jhash"
%token SYMHASH			"symhash"
%token SEED			"seed"

%token POSITION			"position"
%token INDEX			"index"
%token COMMENT			"comment"

%token XML			"xml"
%token JSON			"json"
%token VM			"vm"

%token NOTRACK			"notrack"

%token EXISTS			"exists"
%token MISSING			"missing"

%token EXTHDR			"exthdr"

%token IPSEC		"ipsec"
%token MODE			"mode"
%token REQID		"reqid"
%token SPNUM		"spnum"
%token TRANSPORT	"transport"
%token TUNNEL		"tunnel"

%token IN			"in"
%token OUT			"out"

%type <string>			identifier type_identifier string comment_spec
%destructor { xfree($$); }	identifier type_identifier string comment_spec

%type <val>			time_spec quota_used

%type <expr>			data_type_expr data_type_atom_expr
%destructor { expr_free($$); }  data_type_expr data_type_atom_expr

%type <cmd>			line
%destructor { cmd_free($$); }	line

%type <cmd>			base_cmd add_cmd replace_cmd create_cmd insert_cmd delete_cmd get_cmd list_cmd reset_cmd flush_cmd rename_cmd export_cmd monitor_cmd describe_cmd import_cmd
%destructor { cmd_free($$); }	base_cmd add_cmd replace_cmd create_cmd insert_cmd delete_cmd get_cmd list_cmd reset_cmd flush_cmd rename_cmd export_cmd monitor_cmd describe_cmd import_cmd

%type <handle>			table_spec tableid_spec chain_spec chainid_spec flowtable_spec chain_identifier ruleid_spec handle_spec position_spec rule_position ruleset_spec index_spec
%destructor { handle_free(&$$); } table_spec tableid_spec chain_spec chainid_spec flowtable_spec chain_identifier ruleid_spec handle_spec position_spec rule_position ruleset_spec index_spec
%type <handle>			set_spec setid_spec set_identifier flowtableid_spec flowtable_identifier obj_spec objid_spec obj_identifier
%destructor { handle_free(&$$); } set_spec setid_spec set_identifier flowtableid_spec obj_spec objid_spec obj_identifier
%type <val>			family_spec family_spec_explicit
%type <val32>			int_num	chain_policy
%type <prio_spec>		extended_prio_spec prio_spec
%type <string>			extended_prio_name quota_unit
%destructor { xfree($$); }	extended_prio_name quota_unit

%type <expr>			dev_spec
%destructor { xfree($$); }	dev_spec

%type <table>			table_block_alloc table_block
%destructor { close_scope(state); table_free($$); }	table_block_alloc
%type <chain>			chain_block_alloc chain_block subchain_block
%destructor { close_scope(state); chain_free($$); }	chain_block_alloc
%type <rule>			rule rule_alloc
%destructor { rule_free($$); }	rule

%type <val>			set_flag_list	set_flag

%type <val>			set_policy_spec

%type <set>			set_block_alloc set_block
%destructor { set_free($$); }	set_block_alloc

%type <set>			map_block_alloc map_block
%destructor { set_free($$); }	map_block_alloc

%type <flowtable>		flowtable_block_alloc flowtable_block
%destructor { flowtable_free($$); }	flowtable_block_alloc

%type <obj>			obj_block_alloc counter_block quota_block ct_helper_block ct_timeout_block ct_expect_block limit_block secmark_block synproxy_block
%destructor { obj_free($$); }	obj_block_alloc

%type <list>			stmt_list stateful_stmt_list set_elem_stmt_list
%destructor { stmt_list_free($$); xfree($$); } stmt_list stateful_stmt_list set_elem_stmt_list
%type <stmt>			stmt match_stmt verdict_stmt set_elem_stmt
%destructor { stmt_free($$); }	stmt match_stmt verdict_stmt set_elem_stmt
%type <stmt>			counter_stmt counter_stmt_alloc stateful_stmt
%destructor { stmt_free($$); }	counter_stmt counter_stmt_alloc stateful_stmt
%type <stmt>			payload_stmt
%destructor { stmt_free($$); }	payload_stmt
%type <stmt>			ct_stmt
%destructor { stmt_free($$); }	ct_stmt
%type <stmt>			meta_stmt
%destructor { stmt_free($$); }	meta_stmt
%type <stmt>			log_stmt log_stmt_alloc
%destructor { stmt_free($$); }	log_stmt log_stmt_alloc
%type <val>			level_type log_flags log_flags_tcp log_flag_tcp
%type <stmt>			limit_stmt quota_stmt connlimit_stmt
%destructor { stmt_free($$); }	limit_stmt quota_stmt connlimit_stmt
%type <val>			limit_burst_pkts limit_burst_bytes limit_mode time_unit quota_mode
%type <stmt>			reject_stmt reject_stmt_alloc
%destructor { stmt_free($$); }	reject_stmt reject_stmt_alloc
%type <stmt>			nat_stmt nat_stmt_alloc masq_stmt masq_stmt_alloc redir_stmt redir_stmt_alloc
%destructor { stmt_free($$); }	nat_stmt nat_stmt_alloc masq_stmt masq_stmt_alloc redir_stmt redir_stmt_alloc
%type <val>			nf_nat_flags nf_nat_flag offset_opt
%type <stmt>			tproxy_stmt
%destructor { stmt_free($$); }	tproxy_stmt
%type <stmt>			synproxy_stmt synproxy_stmt_alloc
%destructor { stmt_free($$); }	synproxy_stmt synproxy_stmt_alloc
%type <stmt>			chain_stmt
%destructor { stmt_free($$); }	chain_stmt
%type <val>			chain_stmt_type

%type <stmt>			queue_stmt queue_stmt_alloc
%destructor { stmt_free($$); }	queue_stmt queue_stmt_alloc
%type <val>			queue_stmt_flags queue_stmt_flag
%type <stmt>			dup_stmt
%destructor { stmt_free($$); }	dup_stmt
%type <stmt>			fwd_stmt
%destructor { stmt_free($$); }	fwd_stmt
%type <stmt>			set_stmt
%destructor { stmt_free($$); }	set_stmt
%type <val>			set_stmt_op
%type <stmt>			map_stmt
%destructor { stmt_free($$); }	map_stmt
%type <stmt>			meter_stmt meter_stmt_alloc flow_stmt_legacy_alloc
%destructor { stmt_free($$); }	meter_stmt meter_stmt_alloc flow_stmt_legacy_alloc

%type <expr>			symbol_expr verdict_expr integer_expr variable_expr chain_expr policy_expr
%destructor { expr_free($$); }	symbol_expr verdict_expr integer_expr variable_expr chain_expr policy_expr
%type <expr>			primary_expr shift_expr and_expr typeof_expr
%destructor { expr_free($$); }	primary_expr shift_expr and_expr typeof_expr
%type <expr>			exclusive_or_expr inclusive_or_expr
%destructor { expr_free($$); }	exclusive_or_expr inclusive_or_expr
%type <expr>			basic_expr
%destructor { expr_free($$); }	basic_expr
%type <expr>			set_ref_expr set_ref_symbol_expr
%destructor { expr_free($$); }	set_ref_expr set_ref_symbol_expr

%type <expr>			multiton_rhs_expr
%destructor { expr_free($$); }	multiton_rhs_expr
%type <expr>			prefix_rhs_expr range_rhs_expr
%destructor { expr_free($$); }	prefix_rhs_expr range_rhs_expr

%type <expr>			stmt_expr concat_stmt_expr map_stmt_expr map_stmt_expr_set
%destructor { expr_free($$); }	stmt_expr concat_stmt_expr map_stmt_expr map_stmt_expr_set

%type <expr>			multiton_stmt_expr
%destructor { expr_free($$); }	multiton_stmt_expr
%type <expr>			prefix_stmt_expr range_stmt_expr wildcard_expr
%destructor { expr_free($$); }	prefix_stmt_expr range_stmt_expr wildcard_expr

%type <expr>			primary_stmt_expr basic_stmt_expr
%destructor { expr_free($$); }	primary_stmt_expr basic_stmt_expr
%type <expr>			list_stmt_expr shift_stmt_expr
%destructor { expr_free($$); }	list_stmt_expr shift_stmt_expr
%type <expr>			and_stmt_expr exclusive_or_stmt_expr inclusive_or_stmt_expr
%destructor { expr_free($$); }	and_stmt_expr exclusive_or_stmt_expr inclusive_or_stmt_expr

%type <expr>			concat_expr
%destructor { expr_free($$); }	concat_expr

%type <expr>			map_expr
%destructor { expr_free($$); }	map_expr

%type <expr>			verdict_map_stmt
%destructor { expr_free($$); }	verdict_map_stmt

%type <expr>			verdict_map_expr verdict_map_list_expr verdict_map_list_member_expr
%destructor { expr_free($$); }	verdict_map_expr verdict_map_list_expr verdict_map_list_member_expr

%type <expr>			set_expr set_block_expr set_list_expr set_list_member_expr flowtable_expr flowtable_list_expr flowtable_expr_member
%destructor { expr_free($$); }	set_expr set_block_expr set_list_expr set_list_member_expr flowtable_expr flowtable_list_expr flowtable_expr_member
%type <expr>			set_elem_expr set_elem_expr_alloc set_lhs_expr set_rhs_expr
%destructor { expr_free($$); }	set_elem_expr set_elem_expr_alloc set_lhs_expr set_rhs_expr
%type <expr>			set_elem_expr_stmt set_elem_expr_stmt_alloc
%destructor { expr_free($$); }	set_elem_expr_stmt set_elem_expr_stmt_alloc

%type <expr>			meter_key_expr meter_key_expr_alloc
%destructor { expr_free($$); }	meter_key_expr meter_key_expr_alloc

%type <expr>			expr initializer_expr keyword_expr
%destructor { expr_free($$); }	expr initializer_expr keyword_expr

%type <expr>			rhs_expr concat_rhs_expr basic_rhs_expr
%destructor { expr_free($$); }	rhs_expr concat_rhs_expr basic_rhs_expr
%type <expr>			primary_rhs_expr list_rhs_expr shift_rhs_expr symbol_stmt_expr
%destructor { expr_free($$); }	primary_rhs_expr list_rhs_expr shift_rhs_expr symbol_stmt_expr
%type <expr>			and_rhs_expr exclusive_or_rhs_expr inclusive_or_rhs_expr
%destructor { expr_free($$); }	and_rhs_expr exclusive_or_rhs_expr inclusive_or_rhs_expr

%type <obj>			counter_obj quota_obj ct_obj_alloc limit_obj secmark_obj synproxy_obj
%destructor { obj_free($$); }	counter_obj quota_obj ct_obj_alloc limit_obj secmark_obj synproxy_obj

%type <expr>			relational_expr
%destructor { expr_free($$); }	relational_expr
%type <val>			relational_op

%type <expr>			payload_expr payload_raw_expr
%destructor { expr_free($$); }	payload_expr payload_raw_expr
%type <val>			payload_base_spec
%type <expr>			eth_hdr_expr	vlan_hdr_expr
%destructor { expr_free($$); }	eth_hdr_expr	vlan_hdr_expr
%type <val>			eth_hdr_field	vlan_hdr_field
%type <expr>			arp_hdr_expr
%destructor { expr_free($$); }	arp_hdr_expr
%type <val>			arp_hdr_field
%type <expr>			ip_hdr_expr	icmp_hdr_expr		igmp_hdr_expr numgen_expr	hash_expr
%destructor { expr_free($$); }	ip_hdr_expr	icmp_hdr_expr		igmp_hdr_expr numgen_expr	hash_expr
%type <val>			ip_hdr_field	icmp_hdr_field		igmp_hdr_field
%type <val>			ip_option_type	ip_option_field
%type <expr>			ip6_hdr_expr    icmp6_hdr_expr
%destructor { expr_free($$); }	ip6_hdr_expr	icmp6_hdr_expr
%type <val>			ip6_hdr_field   icmp6_hdr_field
%type <expr>			auth_hdr_expr	esp_hdr_expr		comp_hdr_expr
%destructor { expr_free($$); }	auth_hdr_expr	esp_hdr_expr		comp_hdr_expr
%type <val>			auth_hdr_field	esp_hdr_field		comp_hdr_field
%type <expr>			udp_hdr_expr	udplite_hdr_expr
%destructor { expr_free($$); }	udp_hdr_expr	udplite_hdr_expr
%type <val>			udp_hdr_field	udplite_hdr_field
%type <expr>			dccp_hdr_expr	sctp_hdr_expr
%destructor { expr_free($$); }	dccp_hdr_expr	sctp_hdr_expr
%type <val>			dccp_hdr_field	sctp_hdr_field
%type <expr>			th_hdr_expr
%destructor { expr_free($$); }	th_hdr_expr
%type <val>			th_hdr_field

%type <expr>			exthdr_expr
%destructor { expr_free($$); }	exthdr_expr
%type <expr>			hbh_hdr_expr	frag_hdr_expr		dst_hdr_expr
%destructor { expr_free($$); }	hbh_hdr_expr	frag_hdr_expr		dst_hdr_expr
%type <val>			hbh_hdr_field	frag_hdr_field		dst_hdr_field
%type <expr>			rt_hdr_expr	rt0_hdr_expr		rt2_hdr_expr	rt4_hdr_expr
%destructor { expr_free($$); }	rt_hdr_expr	rt0_hdr_expr		rt2_hdr_expr	rt4_hdr_expr
%type <val>			rt_hdr_field	rt0_hdr_field		rt2_hdr_field	rt4_hdr_field
%type <expr>			mh_hdr_expr
%destructor { expr_free($$); }	mh_hdr_expr
%type <val>			mh_hdr_field

%type <expr>			meta_expr
%destructor { expr_free($$); }	meta_expr
%type <val>			meta_key	meta_key_qualified	meta_key_unqualified	numgen_type

%type <expr>			socket_expr
%destructor { expr_free($$); } socket_expr
%type<val>			socket_key

%type <val>			nf_key_proto

%type <expr>			rt_expr
%destructor { expr_free($$); }	rt_expr
%type <val>			rt_key

%type <expr>			ct_expr
%destructor { expr_free($$); }	ct_expr
%type <val>			ct_key		ct_dir	ct_key_dir_optional	ct_key_dir	ct_key_proto_field

%type <expr>			fib_expr
%destructor { expr_free($$); }	fib_expr
%type <val>			fib_tuple	fib_result	fib_flag

%type <expr>			osf_expr
%type <val>			osf_ttl
%destructor { expr_free($$); }	osf_expr

%type <val>			markup_format
%type <string>			monitor_event
%destructor { xfree($$); }	monitor_event
%type <val>			monitor_object	monitor_format

%type <val>			synproxy_ts	synproxy_sack

%type <expr>			tcp_hdr_expr
%destructor { expr_free($$); }	tcp_hdr_expr
%type <val>			tcp_hdr_field
%type <val>			tcp_hdr_option_type tcp_hdr_option_field

%type <expr>			boolean_expr
%destructor { expr_free($$); }	boolean_expr
%type <val8>			boolean_keys

%type <expr>			exthdr_exists_expr
%destructor { expr_free($$); }	exthdr_exists_expr
%type <val>			exthdr_key

%type <val>			ct_l4protoname ct_obj_type

%type <list>			timeout_states timeout_state
%destructor { xfree($$); }	timeout_states timeout_state

%type <val>			xfrm_state_key	xfrm_state_proto_key xfrm_dir	xfrm_spnum
%type <expr>			xfrm_expr
%destructor { expr_free($$); }	xfrm_expr

%%

input			:	/* empty */
			|	input		line
			{
				if ($2 != NULL) {
					$2->location = @2;
					list_add_tail(&$2->list, state->cmds);
				}
			}
			;

stmt_separator		:	NEWLINE
			|	SEMICOLON
			;

opt_newline		:	NEWLINE
		 	|	/* empty */
			;

common_block		:	INCLUDE		QUOTED_STRING	stmt_separator
			{
				if (scanner_include_file(nft, scanner, $2, &@$) < 0) {
					xfree($2);
					YYERROR;
				}
				xfree($2);
			}
			|	DEFINE		identifier	'='	initializer_expr	stmt_separator
			{
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, $2) != NULL) {
					erec_queue(error(&@2, "redefinition of symbol '%s'", $2),
						   state->msgs);
					expr_free($4);
					xfree($2);
					YYERROR;
				}

				symbol_bind(scope, $2, $4);
				xfree($2);
			}
			|	REDEFINE	identifier	'='	initializer_expr	stmt_separator
			{
				struct scope *scope = current_scope(state);

				symbol_bind(scope, $2, $4);
				xfree($2);
			}
			|	UNDEFINE	identifier	stmt_separator
			{
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, $2) < 0) {
					erec_queue(error(&@2, "undefined symbol '%s'", $2),
						   state->msgs);
					YYERROR;
				}
				xfree($2);
			}
			|	error		stmt_separator
			{
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
			;

line			:	common_block			{ $$ = NULL; }
			|	stmt_separator			{ $$ = NULL; }
			|	base_cmd	stmt_separator	{ $$ = $1; }
			|	base_cmd	TOKEN_EOF
			{
				/*
				 * Very hackish workaround for bison >= 2.4: previous versions
				 * terminated parsing after EOF, 2.4+ tries to get further input
				 * in 'input' and calls the scanner again, causing a crash when
				 * the final input buffer has been popped. Terminate manually to
				 * avoid this. The correct fix should be to adjust the grammar
				 * to accept EOF in input, but for unknown reasons it does not
				 * work.
				 */
				if ($1 != NULL) {
					$1->location = @1;
					list_add_tail(&$1->list, state->cmds);
				}
				$$ = NULL;
				YYACCEPT;
			}
			;

base_cmd		:	/* empty */	add_cmd		{ $$ = $1; }
	  		|	ADD		add_cmd		{ $$ = $2; }
			|	REPLACE		replace_cmd	{ $$ = $2; }
			|	CREATE		create_cmd	{ $$ = $2; }
			|	INSERT		insert_cmd	{ $$ = $2; }
			|	DELETE		delete_cmd	{ $$ = $2; }
			|	GET		get_cmd		{ $$ = $2; }
			|	LIST		list_cmd	{ $$ = $2; }
			|	RESET		reset_cmd	{ $$ = $2; }
			|	FLUSH		flush_cmd	{ $$ = $2; }
			|	RENAME		rename_cmd	{ $$ = $2; }
			|       IMPORT          import_cmd      { $$ = $2; }
			|	EXPORT		export_cmd	{ $$ = $2; }
			|	MONITOR		monitor_cmd	{ $$ = $2; }
			|	DESCRIBE	describe_cmd	{ $$ = $2; }
			;

add_cmd			:	TABLE		table_spec
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &$2, &@$, NULL);
			}
			|	TABLE		table_spec	table_block_alloc
						'{'	table_block	'}'
			{
				handle_merge(&$3->handle, &$2);
				close_scope(state);
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &$2, &@$, $5);
			}
			|	CHAIN		chain_spec
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &$2, &@$, NULL);
			}
			|	CHAIN		chain_spec	chain_block_alloc
						'{'	chain_block	'}'
			{
				$5->location = @5;
				handle_merge(&$3->handle, &$2);
				close_scope(state);
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &$2, &@$, $5);
			}
			|	RULE		rule_position	rule
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &$2, &@$, $3);
			}
			|	/* empty */	rule_position	rule
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &$1, &@$, $2);
			}
			|	SET		set_spec	set_block_alloc
						'{'	set_block	'}'
			{
				$5->location = @5;
				handle_merge(&$3->handle, &$2);
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &$2, &@$, $5);
			}
			|	MAP		set_spec	map_block_alloc
						'{'	map_block	'}'
			{
				$5->location = @5;
				handle_merge(&$3->handle, &$2);
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &$2, &@$, $5);
			}
			|	ELEMENT		set_spec	set_block_expr
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &$2, &@$, $3);
			}
			|	FLOWTABLE	flowtable_spec	flowtable_block_alloc
						'{'	flowtable_block	'}'
			{
				$5->location = @5;
				handle_merge(&$3->handle, &$2);
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &$2, &@$, $5);
			}
			|	COUNTER		obj_spec
			{
				struct obj *obj;

				obj = obj_alloc(&@$);
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &$2);
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &$2, &@$, obj);
			}
			|	COUNTER		obj_spec	counter_obj	counter_config
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &$2, &@$, $3);
			}
			|	COUNTER		obj_spec	counter_obj	'{' counter_block '}'
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &$2, &@$, $3);
			}
			|	QUOTA		obj_spec	quota_obj	quota_config
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &$2, &@$, $3);
			}
			|	QUOTA		obj_spec	quota_obj	'{' quota_block	'}'
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &$2, &@$, $3);
			}
			|	CT	HELPER	obj_spec	ct_obj_alloc	'{' ct_helper_block '}'
			{
				$$ = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &$3, &@$, $4);
			}
			|	CT	TIMEOUT obj_spec	ct_obj_alloc	'{' ct_timeout_block '}'
			{
				$$ = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &$3, &@$, $4);
			}
			|	CT	EXPECTATION	obj_spec	ct_obj_alloc	'{' ct_expect_block '}'
			{
				$$ = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &$3, &@$, $4);
			}
			|	LIMIT		obj_spec	limit_obj	limit_config
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &$2, &@$, $3);
			}
			|	LIMIT		obj_spec	limit_obj	'{' limit_block '}'
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &$2, &@$, $3);
			}
			|	SECMARK		obj_spec	secmark_obj	secmark_config
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &$2, &@$, $3);
			}
			|	SECMARK		obj_spec	secmark_obj	'{' secmark_block '}'
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &$2, &@$, $3);
			}
			|	SYNPROXY	obj_spec	synproxy_obj	synproxy_config
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &$2, &@$, $3);
			}
			|	SYNPROXY	obj_spec	synproxy_obj	'{' synproxy_block '}'
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &$2, &@$, $3);
			}
			;

replace_cmd		:	RULE		ruleid_spec	rule
			{
				$$ = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &$2, &@$, $3);
			}
			;

create_cmd		:	TABLE		table_spec
			{
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &$2, &@$, NULL);
			}
			|	TABLE		table_spec	table_block_alloc
						'{'	table_block	'}'
			{
				handle_merge(&$3->handle, &$2);
				close_scope(state);
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &$2, &@$, $5);
			}
			|	CHAIN		chain_spec
			{
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &$2, &@$, NULL);
			}
			|	CHAIN		chain_spec	chain_block_alloc
						'{'	chain_block	'}'
			{
				$5->location = @5;
				handle_merge(&$3->handle, &$2);
				close_scope(state);
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &$2, &@$, $5);
			}
			|	SET		set_spec	set_block_alloc
						'{'	set_block	'}'
			{
				$5->location = @5;
				handle_merge(&$3->handle, &$2);
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &$2, &@$, $5);
			}
			|	MAP		set_spec	map_block_alloc
						'{'	map_block	'}'
			{
				$5->location = @5;
				handle_merge(&$3->handle, &$2);
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &$2, &@$, $5);
			}
			|	ELEMENT		set_spec	set_block_expr
			{
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &$2, &@$, $3);
			}
			|	FLOWTABLE	flowtable_spec	flowtable_block_alloc
						'{'	flowtable_block	'}'
			{
				$5->location = @5;
				handle_merge(&$3->handle, &$2);
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &$2, &@$, $5);
			}
			|	COUNTER		obj_spec
			{
				struct obj *obj;

				obj = obj_alloc(&@$);
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &$2);
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &$2, &@$, obj);
			}
			|	COUNTER		obj_spec	counter_obj	counter_config
			{
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &$2, &@$, $3);
			}
			|	QUOTA		obj_spec	quota_obj	quota_config
			{
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &$2, &@$, $3);
			}
			|	CT	HELPER	obj_spec	ct_obj_alloc	'{' ct_helper_block '}'
			{
				$$ = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &$3, &@$, $4);
			}
			|	CT	TIMEOUT obj_spec	ct_obj_alloc	'{' ct_timeout_block '}'
			{
				$$ = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &$3, &@$, $4);
			}
			|	CT	EXPECTATION obj_spec	ct_obj_alloc	'{' ct_expect_block '}'
			{
				$$ = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &$3, &@$, $4);
			}
			|	LIMIT		obj_spec	limit_obj	limit_config
			{
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &$2, &@$, $3);
			}
			|	SECMARK		obj_spec	secmark_obj	secmark_config
			{
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &$2, &@$, $3);
			}
			|	SYNPROXY	obj_spec	synproxy_obj	synproxy_config
			{
				$$ = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &$2, &@$, $3);
			}
			;

insert_cmd		:	RULE		rule_position	rule
			{
				$$ = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &$2, &@$, $3);
			}
			;

delete_cmd		:	TABLE		table_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &$2, &@$, NULL);
			}
			|	TABLE 		tableid_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &$2, &@$, NULL);
			}
			|	CHAIN		chain_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &$2, &@$, NULL);
			}
			| 	CHAIN 		chainid_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &$2, &@$, NULL);
			}
			|	RULE		ruleid_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &$2, &@$, NULL);
			}
			|	SET		set_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &$2, &@$, NULL);
			}
			| 	SET 		setid_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &$2, &@$, NULL);
			}
			|	MAP		set_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &$2, &@$, NULL);
			}
			|	ELEMENT		set_spec	set_block_expr
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &$2, &@$, $3);
			}
			|	FLOWTABLE	flowtable_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &$2, &@$, NULL);
			}
			|	FLOWTABLE	flowtableid_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &$2, &@$, NULL);
			}
			|	FLOWTABLE	flowtable_spec	flowtable_block_alloc
						'{'	flowtable_block	'}'
			{
				$5->location = @5;
				handle_merge(&$3->handle, &$2);
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &$2, &@$, $5);
			}
			|	COUNTER		obj_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &$2, &@$, NULL);
			}
			|  	COUNTER 	objid_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &$2, &@$, NULL);
			}
			|	QUOTA		obj_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &$2, &@$, NULL);
			}
			| 	QUOTA 		objid_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &$2, &@$, NULL);
			}
			|	CT	ct_obj_type	obj_spec	ct_obj_alloc
			{
				$$ = cmd_alloc_obj_ct(CMD_DELETE, $2, &$3, &@$, $4);
			}
			|	LIMIT		obj_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &$2, &@$, NULL);
			}
			| 	LIMIT 		objid_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &$2, &@$, NULL);
			}
			|	SECMARK		obj_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &$2, &@$, NULL);
			}
			| 	SECMARK		objid_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &$2, &@$, NULL);
			}
			|	SYNPROXY	obj_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &$2, &@$, NULL);
			}
			|	SYNPROXY	objid_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &$2, &@$, NULL);
			}
			;

get_cmd			:	ELEMENT		set_spec	set_block_expr
			{
				$$ = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &$2, &@$, $3);
			}
			;

list_cmd		:	TABLE		table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &$2, &@$, NULL);
			}
			|	TABLES		ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &$2, &@$, NULL);
			}
			|	CHAIN		chain_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &$2, &@$, NULL);
			}
			|	CHAINS		ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &$2, &@$, NULL);
			}
			|	SETS		ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &$2, &@$, NULL);
			}
			|	SETS		TABLE	table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &$3, &@$, NULL);
			}
			|	SET		set_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &$2, &@$, NULL);
			}
			|	COUNTERS	ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &$2, &@$, NULL);
			}
			|	COUNTERS	TABLE	table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &$3, &@$, NULL);
			}
			|	COUNTER		obj_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &$2, &@$, NULL);
			}
			|	QUOTAS		ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &$2, &@$, NULL);
			}
			|	QUOTAS		TABLE	table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &$3, &@$, NULL);
			}
			|	QUOTA		obj_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &$2, &@$, NULL);
			}
			|	LIMITS		ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &$2, &@$, NULL);
			}
			|	LIMITS		TABLE	table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &$3, &@$, NULL);
			}
			|	LIMIT		obj_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &$2, &@$, NULL);
			}
			|	SECMARKS	ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &$2, &@$, NULL);
			}
			|	SECMARKS	TABLE	table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &$3, &@$, NULL);
			}
			|	SECMARK		obj_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &$2, &@$, NULL);
			}
			|	SYNPROXYS	ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &$2, &@$, NULL);
			}
			|	SYNPROXYS	TABLE	table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &$3, &@$, NULL);
			}
			|	SYNPROXY	obj_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &$2, &@$, NULL);
			}
			|	RULESET		ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &$2, &@$, NULL);
			}
			|	FLOW TABLES	ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &$3, &@$, NULL);
			}
			|	FLOW TABLE	set_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &$3, &@$, NULL);
			}
			|	METERS		ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &$2, &@$, NULL);
			}
			|	METER		set_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &$2, &@$, NULL);
			}
			|       FLOWTABLES      ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &$2, &@$, NULL);
			}
			|	FLOWTABLE	flowtable_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &$2, &@$, NULL);
			}
			|	MAPS		ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &$2, &@$, NULL);
			}
			|	MAP		set_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &$2, &@$, NULL);
			}
			|	CT		ct_obj_type	obj_spec
			{
				$$ = cmd_alloc_obj_ct(CMD_LIST, $2, &$3, &@$, NULL);
			}
			|       CT		HELPERS		TABLE   table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &$4, &@$, NULL);
			}
			|	CT		TIMEOUT		TABLE		table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_CT_TIMEOUT, &$4, &@$, NULL);
			}
			|	CT		EXPECTATION		TABLE		table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_CT_EXPECT, &$4, &@$, NULL);
			}
			;

reset_cmd		:	COUNTERS	ruleset_spec
			{
				$$ = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &$2, &@$, NULL);
			}
			|	COUNTERS	TABLE	table_spec
			{
				$$ = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &$3, &@$, NULL);
			}
			|       COUNTER         obj_spec
			{
				$$ = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &$2,&@$, NULL);
			}
			|	QUOTAS		ruleset_spec
			{
				$$ = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &$2, &@$, NULL);
			}
			|	QUOTAS		TABLE	table_spec
			{
				$$ = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &$3, &@$, NULL);
			}
			|       QUOTA           obj_spec
			{
				$$ = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &$2, &@$, NULL);
			}
			;

flush_cmd		:	TABLE		table_spec
			{
				$$ = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &$2, &@$, NULL);
			}
			|	CHAIN		chain_spec
			{
				$$ = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &$2, &@$, NULL);
			}
			|	SET		set_spec
			{
				$$ = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &$2, &@$, NULL);
			}
			|	MAP		set_spec
			{
				$$ = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &$2, &@$, NULL);
			}
			|	FLOW TABLE	set_spec
			{
				$$ = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &$3, &@$, NULL);
			}
			|	METER		set_spec
			{
				$$ = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &$2, &@$, NULL);
			}
			|	RULESET		ruleset_spec
			{
				$$ = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &$2, &@$, NULL);
			}
			;

rename_cmd		:	CHAIN		chain_spec	identifier
			{
				$$ = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &$2, &@$, NULL);
				$$->arg = $3;
			}
			;

import_cmd			:       RULESET         markup_format
			{
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc($2);
				$$ = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &@$, markup);
			}
			|	markup_format
			{
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc($1);
				$$ = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &@$, markup);
			}
			;

export_cmd		:	RULESET		markup_format
			{
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc($2);
				$$ = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &@$, markup);
			}
			|	markup_format
			{
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc($1);
				$$ = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &@$, markup);
			}
			;

monitor_cmd		:	monitor_event	monitor_object	monitor_format
			{
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc($3, $2, $1);
				m->location = @1;
				$$ = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &@$, m);
			}
			;

monitor_event		:	/* empty */	{ $$ = NULL; }
			|       STRING		{ $$ = $1; }
			;

monitor_object		:	/* empty */	{ $$ = CMD_MONITOR_OBJ_ANY; }
			| 	TABLES		{ $$ = CMD_MONITOR_OBJ_TABLES; }
			| 	CHAINS		{ $$ = CMD_MONITOR_OBJ_CHAINS; }
			| 	SETS		{ $$ = CMD_MONITOR_OBJ_SETS; }
			|	RULES		{ $$ = CMD_MONITOR_OBJ_RULES; }
			|	ELEMENTS	{ $$ = CMD_MONITOR_OBJ_ELEMS; }
			|	RULESET		{ $$ = CMD_MONITOR_OBJ_RULESET; }
			|	TRACE		{ $$ = CMD_MONITOR_OBJ_TRACE; }
			;

monitor_format		:	/* empty */	{ $$ = NFTNL_OUTPUT_DEFAULT; }
			|	markup_format
			;

markup_format		: 	XML 		{ $$ = __NFT_OUTPUT_NOTSUPP; }
			|	JSON		{ $$ = NFTNL_OUTPUT_JSON; }
			|	VM JSON		{ $$ = NFTNL_OUTPUT_JSON; }
			;

describe_cmd		:	primary_expr
			{
				struct handle h = { .family = NFPROTO_UNSPEC };
				$$ = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &@$, NULL);
				$$->expr = $1;
			}
			;

table_block_alloc	:	/* empty */
			{
				$$ = table_alloc();
				open_scope(state, &$$->scope);
			}
			;

table_options		:	FLAGS		STRING
			{
				if (strcmp($2, "dormant") == 0) {
					$<table>0->flags = TABLE_F_DORMANT;
					xfree($2);
				} else {
					erec_queue(error(&@2, "unknown table option %s", $2),
						   state->msgs);
					xfree($2);
					YYERROR;
				}
			}
			|	comment_spec
			{
				if (already_set($<table>0->comment, &@$, state)) {
					xfree($1);
					YYERROR;
				}
				$<table>0->comment = $1;
			}
			;

table_block		:	/* empty */	{ $$ = $<table>-1; }
			|	table_block	common_block
			|	table_block	stmt_separator
			|	table_block	table_options	stmt_separator
			|	table_block	CHAIN		chain_identifier
					chain_block_alloc	'{' 	chain_block	'}'
					stmt_separator
			{
				$4->location = @3;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				close_scope(state);
				list_add_tail(&$4->list, &$1->chains);
				$$ = $1;
			}
			|	table_block	SET		set_identifier
					set_block_alloc		'{'	set_block	'}'
					stmt_separator
			{
				$4->location = @3;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				list_add_tail(&$4->list, &$1->sets);
				$$ = $1;
			}
			|	table_block	MAP		set_identifier
					map_block_alloc		'{'	map_block	'}'
					stmt_separator
			{
				$4->location = @3;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				list_add_tail(&$4->list, &$1->sets);
				$$ = $1;
			}

			|	table_block	FLOWTABLE	flowtable_identifier
					flowtable_block_alloc	'{'	flowtable_block	'}'
					stmt_separator
			{
				$4->location = @3;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				list_add_tail(&$4->list, &$1->flowtables);
				$$ = $1;
			}
			|	table_block	COUNTER		obj_identifier
					obj_block_alloc	'{'	counter_block	'}'
					stmt_separator
			{
				$4->location = @3;
				$4->type = NFT_OBJECT_COUNTER;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				list_add_tail(&$4->list, &$1->objs);
				$$ = $1;
			}
			|	table_block	QUOTA		obj_identifier
					obj_block_alloc	'{'	quota_block	'}'
					stmt_separator
			{
				$4->location = @3;
				$4->type = NFT_OBJECT_QUOTA;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				list_add_tail(&$4->list, &$1->objs);
				$$ = $1;
			}
			|	table_block	CT	HELPER	obj_identifier  obj_block_alloc '{'     ct_helper_block     '}' stmt_separator
			{
				$5->location = @4;
				$5->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&$5->handle, &$4);
				handle_free(&$4);
				list_add_tail(&$5->list, &$1->objs);
				$$ = $1;
			}
			|	table_block	CT	TIMEOUT obj_identifier obj_block_alloc '{'	ct_timeout_block	'}' stmt_separator
			{
				$5->location = @4;
				$5->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&$5->handle, &$4);
				handle_free(&$4);
				list_add_tail(&$5->list, &$1->objs);
				$$ = $1;
			}
			|	table_block	CT	EXPECTATION obj_identifier obj_block_alloc '{'	ct_expect_block	'}' stmt_separator
			{
				$5->location = @4;
				$5->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&$5->handle, &$4);
				handle_free(&$4);
				list_add_tail(&$5->list, &$1->objs);
				$$ = $1;
			}
			|	table_block	LIMIT		obj_identifier
					obj_block_alloc	'{'	limit_block	'}'
					stmt_separator
			{
				$4->location = @3;
				$4->type = NFT_OBJECT_LIMIT;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				list_add_tail(&$4->list, &$1->objs);
				$$ = $1;
			}
			|	table_block	SECMARK		obj_identifier
					obj_block_alloc	'{'	secmark_block	'}'
					stmt_separator
			{
				$4->location = @3;
				$4->type = NFT_OBJECT_SECMARK;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				list_add_tail(&$4->list, &$1->objs);
				$$ = $1;
			}
			|	table_block	SYNPROXY	obj_identifier
					obj_block_alloc '{'	synproxy_block	'}'
					stmt_separator
			{
				$4->location = @3;
				$4->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				list_add_tail(&$4->list, &$1->objs);
				$$ = $1;
			}
			;

chain_block_alloc	:	/* empty */
			{
				$$ = chain_alloc(NULL);
				open_scope(state, &$$->scope);
			}
			;

chain_block		:	/* empty */	{ $$ = $<chain>-1; }
			|	chain_block	common_block
			|	chain_block	stmt_separator
			|	chain_block	hook_spec	stmt_separator
			|	chain_block	policy_spec	stmt_separator
			|	chain_block	flags_spec	stmt_separator
			|	chain_block	rule		stmt_separator
			{
				list_add_tail(&$2->list, &$1->rules);
				$$ = $1;
			}
			|	chain_block	comment_spec	stmt_separator
			{
				if (already_set($1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$1->comment = $2;
			}
			;

subchain_block		:	/* empty */	{ $$ = $<chain>-1; }
			|	subchain_block	stmt_separator
			|	subchain_block	rule stmt_separator
			{
				list_add_tail(&$2->list, &$1->rules);
				$$ = $1;
			}
			;

typeof_expr		:	primary_expr
			{
				if (expr_ops($1)->build_udata == NULL) {
					erec_queue(error(&@1, "primary expression type '%s' lacks typeof serialization", expr_ops($1)->name),
						   state->msgs);
					expr_free($1);
					YYERROR;
				}

				$$ = $1;
			}
			|	typeof_expr		DOT		primary_expr
			{
				struct location rhs[] = {
					[1]	= @2,
					[2]	= @3,
				};

				$$ = handle_concat_expr(&@$, $$, $1, $3, rhs);
			}
			;


set_block_alloc		:	/* empty */
			{
				$$ = set_alloc(NULL);
			}
			;

set_block		:	/* empty */	{ $$ = $<set>-1; }
			|	set_block	common_block
			|	set_block	stmt_separator
			|	set_block	TYPE		data_type_expr	stmt_separator
			{
				$1->key = $3;
				$$ = $1;
			}
			|	set_block	TYPEOF		typeof_expr	stmt_separator
			{
				$1->key = $3;
				datatype_set($1->key, $3->dtype);
				$$ = $1;
			}
			|	set_block	FLAGS		set_flag_list	stmt_separator
			{
				$1->flags = $3;
				$$ = $1;
			}
			|	set_block	TIMEOUT		time_spec	stmt_separator
			{
				$1->timeout = $3;
				$$ = $1;
			}
			|	set_block	GC_INTERVAL	time_spec	stmt_separator
			{
				$1->gc_int = $3;
				$$ = $1;
			}
			|	set_block	stateful_stmt_list		stmt_separator
			{
				list_splice_tail($2, &$1->stmt_list);
				$$ = $1;
				free($2);
			}
			|	set_block	ELEMENTS	'='		set_block_expr
			{
				$1->init = $4;
				$$ = $1;
			}
			|	set_block	AUTOMERGE
			{
				$1->automerge = true;
				$$ = $1;
			}
			|	set_block	set_mechanism	stmt_separator
			|	set_block	comment_spec	stmt_separator
			{
				if (already_set($1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$1->comment = $2;
				$$ = $1;
			}
			;

set_block_expr		:	set_expr
			|	variable_expr
			;

set_flag_list		:	set_flag_list	COMMA		set_flag
			{
				$$ = $1 | $3;
			}
			|	set_flag
			;

set_flag		:	CONSTANT	{ $$ = NFT_SET_CONSTANT; }
			|	INTERVAL	{ $$ = NFT_SET_INTERVAL; }
			|	TIMEOUT		{ $$ = NFT_SET_TIMEOUT; }
			|	DYNAMIC		{ $$ = NFT_SET_EVAL; }
			;

map_block_alloc		:	/* empty */
			{
				$$ = set_alloc(NULL);
			}
			;

map_block		:	/* empty */	{ $$ = $<set>-1; }
			|	map_block	common_block
			|	map_block	stmt_separator
			|	map_block	TIMEOUT		time_spec	stmt_separator
			{
				$1->timeout = $3;
				$$ = $1;
			}
			|	map_block	TYPE
						data_type_expr	COLON	data_type_expr
						stmt_separator
			{
				$1->key = $3;
				$1->data = $5;

				$1->flags |= NFT_SET_MAP;
				$$ = $1;
			}
			|	map_block	TYPE
						data_type_expr	COLON	INTERVAL	data_type_expr
						stmt_separator
			{
				$1->key = $3;
				$1->data = $6;
				$1->data->flags |= EXPR_F_INTERVAL;

				$1->flags |= NFT_SET_MAP;
				$$ = $1;
			}
			|	map_block	TYPEOF
						typeof_expr	COLON	typeof_expr
						stmt_separator
			{
				$1->key = $3;
				datatype_set($1->key, $3->dtype);
				$1->data = $5;

				$1->flags |= NFT_SET_MAP;
				$$ = $1;
			}
			|	map_block	TYPEOF
						typeof_expr	COLON	INTERVAL	typeof_expr
						stmt_separator
			{
				$1->key = $3;
				datatype_set($1->key, $3->dtype);
				$1->data = $6;
				$1->data->flags |= EXPR_F_INTERVAL;

				$1->flags |= NFT_SET_MAP;
				$$ = $1;
			}
			|	map_block	TYPE
						data_type_expr	COLON	COUNTER
						stmt_separator
			{
				$1->key = $3;
				$1->objtype = NFT_OBJECT_COUNTER;
				$1->flags  |= NFT_SET_OBJECT;
				$$ = $1;
			}
			|	map_block	TYPE
						data_type_expr	COLON	QUOTA
						stmt_separator
			{
				$1->key = $3;
				$1->objtype = NFT_OBJECT_QUOTA;
				$1->flags  |= NFT_SET_OBJECT;
				$$ = $1;
			}
			|	map_block	TYPE
						data_type_expr	COLON	LIMIT
						stmt_separator
			{
				$1->key = $3;
				$1->objtype = NFT_OBJECT_LIMIT;
				$1->flags  |= NFT_SET_OBJECT;
				$$ = $1;
			}
			|	map_block	TYPE
						data_type_expr	COLON	SECMARK
						stmt_separator
			{
				$1->key = $3;
				$1->objtype = NFT_OBJECT_SECMARK;
				$1->flags  |= NFT_SET_OBJECT;
				$$ = $1;
			}
			|	map_block	FLAGS		set_flag_list	stmt_separator
			{
				$1->flags |= $3;
				$$ = $1;
			}
			|	map_block	ELEMENTS	'='		set_block_expr
			{
				$1->init = $4;
				$$ = $1;
			}
			|	map_block	comment_spec	stmt_separator
			{
				if (already_set($1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$1->comment = $2;
				$$ = $1;
			}
			|	map_block	set_mechanism	stmt_separator
			;

set_mechanism		:	POLICY		set_policy_spec
			{
				$<set>0->policy = $2;
			}
			|	SIZE		NUM
			{
				$<set>0->desc.size = $2;
			}
			;

set_policy_spec		:	PERFORMANCE	{ $$ = NFT_SET_POL_PERFORMANCE; }
			|	MEMORY		{ $$ = NFT_SET_POL_MEMORY; }
			;

flowtable_block_alloc	:	/* empty */
			{
				$$ = flowtable_alloc(NULL);
			}
			;

flowtable_block		:	/* empty */	{ $$ = $<flowtable>-1; }
			|	flowtable_block	common_block
			|	flowtable_block	stmt_separator
			|	flowtable_block	HOOK		STRING	prio_spec	stmt_separator
			{
				$$->hook.loc = @3;
				$$->hook.name = chain_hookname_lookup($3);
				if ($$->hook.name == NULL) {
					erec_queue(error(&@3, "unknown chain hook"),
						   state->msgs);
					xfree($3);
					YYERROR;
				}
				xfree($3);

				$$->priority = $4;
			}
			|	flowtable_block	DEVICES		'='	flowtable_expr	stmt_separator
			{
				$$->dev_expr = $4;
			}
			|	flowtable_block COUNTER
			{
				$$->flags |= NFT_FLOWTABLE_COUNTER;
			}
			;

flowtable_expr		:	'{'	flowtable_list_expr	'}'
			{
				$2->location = @$;
				$$ = $2;
			}
			|	variable_expr
			{
				$1->location = @$;
				$$ = $1;
			}
			;

flowtable_list_expr	:	flowtable_expr_member
			{
				$$ = compound_expr_alloc(&@$, EXPR_LIST);
				compound_expr_add($$, $1);
			}
			|	flowtable_list_expr	COMMA	flowtable_expr_member
			{
				compound_expr_add($1, $3);
				$$ = $1;
			}
			|	flowtable_list_expr	COMMA	opt_newline
			;

flowtable_expr_member	:	STRING
			{
				$$ = constant_expr_alloc(&@$, &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen($1) * BITS_PER_BYTE, $1);
				xfree($1);
			}
			|	variable_expr
			{
				datatype_set($1->sym->expr, &ifname_type);
				$$ = $1;
			}
			;

data_type_atom_expr	:	type_identifier
			{
				const struct datatype *dtype = datatype_lookup_byname($1);
				if (dtype == NULL) {
					erec_queue(error(&@1, "unknown datatype %s", $1),
						   state->msgs);
					YYERROR;
				}
				$$ = constant_expr_alloc(&@1, dtype, dtype->byteorder,
							 dtype->size, NULL);
				xfree($1);
			}
			|	TIME
			{
				$$ = constant_expr_alloc(&@1, &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
			;

data_type_expr		:	data_type_atom_expr
			|	data_type_expr	DOT	data_type_atom_expr
			{
				struct location rhs[] = {
					[1]	= @2,
					[2]	= @3,
				};

				$$ = handle_concat_expr(&@$, $$, $1, $3, rhs);
			}
			;

obj_block_alloc		:       /* empty */
			{
				$$ = obj_alloc(NULL);
			}
			;

counter_block		:	/* empty */	{ $$ = $<obj>-1; }
			|       counter_block     common_block
			|       counter_block     stmt_separator
			|       counter_block     counter_config
			{
				$$ = $1;
			}
			|	counter_block	  comment_spec
			{
				if (already_set($<obj>1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$<obj>1->comment = $2;
			}
			;

quota_block		:	/* empty */	{ $$ = $<obj>-1; }
			|       quota_block     common_block
			|       quota_block     stmt_separator
			|       quota_block     quota_config
			{
				$$ = $1;
			}
			|	quota_block	comment_spec
			{
				if (already_set($<obj>1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$<obj>1->comment = $2;
			}
			;

ct_helper_block		:	/* empty */	{ $$ = $<obj>-1; }
			|       ct_helper_block     common_block
			|       ct_helper_block     stmt_separator
			|       ct_helper_block     ct_helper_config
			{
				$$ = $1;
			}
			|       ct_helper_block     comment_spec
			{
				if (already_set($<obj>1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$<obj>1->comment = $2;
			}
			;

ct_timeout_block	:	/*empty */
			{
				$$ = $<obj>-1;
				init_list_head(&$$->ct_timeout.timeout_list);
			}
			|	ct_timeout_block     common_block
			|	ct_timeout_block     stmt_separator
			|	ct_timeout_block     ct_timeout_config
			{
				$$ = $1;
			}
			|       ct_timeout_block     comment_spec
			{
				if (already_set($<obj>1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$<obj>1->comment = $2;
			}
			;

ct_expect_block		:	/*empty */	{ $$ = $<obj>-1; }
			|	ct_expect_block     common_block
			|	ct_expect_block     stmt_separator
			|	ct_expect_block     ct_expect_config
			{
				$$ = $1;
			}
			|       ct_expect_block     comment_spec
			{
				if (already_set($<obj>1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$<obj>1->comment = $2;
			}
			;

limit_block		:	/* empty */	{ $$ = $<obj>-1; }
			|       limit_block     common_block
			|       limit_block     stmt_separator
			|       limit_block     limit_config
			{
				$$ = $1;
			}
			|       limit_block     comment_spec
			{
				if (already_set($<obj>1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$<obj>1->comment = $2;
			}
			;

secmark_block		:	/* empty */	{ $$ = $<obj>-1; }
			|       secmark_block     common_block
			|       secmark_block     stmt_separator
			|       secmark_block     secmark_config
			{
				$$ = $1;
			}
			|       secmark_block     comment_spec
			{
				if (already_set($<obj>1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$<obj>1->comment = $2;
			}
			;

synproxy_block		:	/* empty */	{ $$ = $<obj>-1; }
			|	synproxy_block	common_block
			|	synproxy_block	stmt_separator
			|	synproxy_block	synproxy_config
			{
				$$ = $1;
			}
			|       synproxy_block     comment_spec
			{
				if (already_set($<obj>1->comment, &@2, state)) {
					xfree($2);
					YYERROR;
				}
				$<obj>1->comment = $2;
			}
			;

type_identifier		:	STRING	{ $$ = $1; }
			|	MARK	{ $$ = xstrdup("mark"); }
			|	DSCP	{ $$ = xstrdup("dscp"); }
			|	ECN	{ $$ = xstrdup("ecn"); }
			|	CLASSID { $$ = xstrdup("classid"); }
			;

hook_spec		:	TYPE		STRING		HOOK		STRING		dev_spec	prio_spec
			{
				const char *chain_type = chain_type_name_lookup($2);

				if (chain_type == NULL) {
					erec_queue(error(&@2, "unknown chain type"),
						   state->msgs);
					xfree($2);
					YYERROR;
				}
				$<chain>0->type		= xstrdup(chain_type);
				xfree($2);

				$<chain>0->loc = @$;
				$<chain>0->hook.loc = @4;
				$<chain>0->hook.name = chain_hookname_lookup($4);
				if ($<chain>0->hook.name == NULL) {
					erec_queue(error(&@4, "unknown chain hook"),
						   state->msgs);
					xfree($4);
					YYERROR;
				}
				xfree($4);

				$<chain>0->dev_expr	= $5;
				$<chain>0->priority	= $6;
				$<chain>0->flags	|= CHAIN_F_BASECHAIN;
			}
			;

prio_spec		:	PRIORITY extended_prio_spec
			{
				$$ = $2;
				$$.loc = @$;
			}
			;

extended_prio_name	:	OUT
			{
				$$ = strdup("out");
			}
			|	STRING
			;

extended_prio_spec	:	int_num
			{
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&@$, &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &$1);
				$$ = spec;
			}
			|	variable_expr
			{
				struct prio_spec spec = {0};

				spec.expr = $1;
				$$ = spec;
			}
			|	extended_prio_name
			{
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&@$, &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen($1) * BITS_PER_BYTE,
								$1);
				xfree($1);
				$$ = spec;
			}
			|	extended_prio_name PLUS NUM
			{
				struct prio_spec spec = {0};

				char str[NFT_NAME_MAXLEN];
				snprintf(str, sizeof(str), "%s + %" PRIu64, $1, $3);
				spec.expr = constant_expr_alloc(&@$, &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen(str) * BITS_PER_BYTE,
								str);
				xfree($1);
				$$ = spec;
			}
			|	extended_prio_name DASH NUM
			{
				struct prio_spec spec = {0};
				char str[NFT_NAME_MAXLEN];

				snprintf(str, sizeof(str), "%s - %" PRIu64, $1, $3);
				spec.expr = constant_expr_alloc(&@$, &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen(str) * BITS_PER_BYTE,
								str);
				xfree($1);
				$$ = spec;
			}
			;

int_num			:	NUM			{ $$ = $1; }
			|	DASH	NUM		{ $$ = -$2; }
			;

dev_spec		:	DEVICE	string
			{
				struct expr *expr;

				expr = constant_expr_alloc(&@$, &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen($2) * BITS_PER_BYTE, $2);
				xfree($2);
				$$ = compound_expr_alloc(&@$, EXPR_LIST);
				compound_expr_add($$, expr);

			}
			|	DEVICE	variable_expr
			{
				datatype_set($2->sym->expr, &ifname_type);
				$$ = compound_expr_alloc(&@$, EXPR_LIST);
				compound_expr_add($$, $2);
			}
			|	DEVICES		'='	flowtable_expr
			{
				$$ = $3;
			}
			|	/* empty */		{ $$ = NULL; }
			;

flags_spec		:	FLAGS		OFFLOAD
			{
				$<chain>0->flags |= CHAIN_F_HW_OFFLOAD;
			}
			;

policy_spec		:	POLICY		policy_expr
			{
				if ($<chain>0->policy) {
					erec_queue(error(&@$, "you cannot set chain policy twice"),
						   state->msgs);
					expr_free($2);
					YYERROR;
				}
				$<chain>0->policy		= $2;
				$<chain>0->policy->location	= @$;
			}
			;

policy_expr		:	variable_expr
			{
				datatype_set($1->sym->expr, &policy_type);
				$$ = $1;
			}
			|	chain_policy
			{
				$$ = constant_expr_alloc(&@$, &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &$1);
			}
			;

chain_policy		:	ACCEPT		{ $$ = NF_ACCEPT; }
			|	DROP		{ $$ = NF_DROP;   }
			;

identifier		:	STRING
			;

string			:	STRING
			|	QUOTED_STRING
			|	ASTERISK_STRING
			;

time_spec		:	STRING
			{
				struct error_record *erec;
				uint64_t res;

				erec = time_parse(&@1, $1, &res);
				xfree($1);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				$$ = res;
			}
			;

family_spec		:	/* empty */		{ $$ = NFPROTO_IPV4; }
			|	family_spec_explicit
			;

family_spec_explicit	:	IP		{ $$ = NFPROTO_IPV4; }
			|	IP6		{ $$ = NFPROTO_IPV6; }
			|	INET		{ $$ = NFPROTO_INET; }
			|	ARP		{ $$ = NFPROTO_ARP; }
			|	BRIDGE		{ $$ = NFPROTO_BRIDGE; }
			|	NETDEV		{ $$ = NFPROTO_NETDEV; }
			;

table_spec		:	family_spec	identifier
			{
				memset(&$$, 0, sizeof($$));
				$$.family	= $1;
				$$.table.location = @2;
				$$.table.name	= $2;
			}
			;

tableid_spec 		: 	family_spec 	HANDLE NUM
			{
				memset(&$$, 0, sizeof($$));
				$$.family 		= $1;
				$$.handle.id 		= $3;
				$$.handle.location	= @3;
			}
			;

chain_spec		:	table_spec	identifier
			{
				$$		= $1;
				$$.chain.name	= $2;
				$$.chain.location = @2;
			}
			;

chainid_spec 		: 	table_spec 	HANDLE NUM
			{
				$$ 			= $1;
				$$.handle.location 	= @3;
				$$.handle.id 		= $3;
			}
			;

chain_identifier	:	identifier
			{
				memset(&$$, 0, sizeof($$));
				$$.chain.name		= $1;
				$$.chain.location	= @1;
			}
			;

set_spec		:	table_spec	identifier
			{
				$$		= $1;
				$$.set.name	= $2;
				$$.set.location	= @2;
			}
			;

setid_spec 		: 	table_spec 	HANDLE NUM
			{
				$$ 			= $1;
				$$.handle.location 	= @3;
				$$.handle.id 		= $3;
			}
			;

set_identifier		:	identifier
			{
				memset(&$$, 0, sizeof($$));
				$$.set.name	= $1;
				$$.set.location	= @1;
			}
			;

flowtable_spec		:	table_spec	identifier
			{
				$$			= $1;
				$$.flowtable.name	= $2;
				$$.flowtable.location	= @2;
			}
			;

flowtableid_spec	:	table_spec	HANDLE NUM
			{
				$$			= $1;
				$$.handle.location	= @3;
				$$.handle.id		= $3;
			}
			;

flowtable_identifier	:	identifier
			{
				memset(&$$, 0, sizeof($$));
				$$.flowtable.name	= $1;
				$$.flowtable.location	= @1;
			}
			;

obj_spec		:	table_spec	identifier
			{
				$$		= $1;
				$$.obj.name	= $2;
				$$.obj.location	= @2;
			}
			;

objid_spec		:	table_spec	HANDLE NUM
			{
				$$ 			= $1;
				$$.handle.location	= @3;
				$$.handle.id		= $3;
			}
			;

obj_identifier		:	identifier
			{
				memset(&$$, 0, sizeof($$));
				$$.obj.name		= $1;
				$$.obj.location		= @1;
			}
			;

handle_spec		:	HANDLE		NUM
			{
				memset(&$$, 0, sizeof($$));
				$$.handle.location	= @2;
				$$.handle.id		= $2;
			}
			;

position_spec		:	POSITION	NUM
			{
				memset(&$$, 0, sizeof($$));
				$$.position.location	= @$;
				$$.position.id		= $2;
			}
			;

index_spec		:	INDEX		NUM
			{
				memset(&$$, 0, sizeof($$));
				$$.index.location	= @$;
				$$.index.id		= $2 + 1;
			}
			;

rule_position		:	chain_spec
			{
				$$ = $1;
			}
			|	chain_spec	position_spec
			{
				handle_merge(&$1, &$2);
				$$ = $1;
			}
			|	chain_spec	handle_spec
			{
				$2.position.location = $2.handle.location;
				$2.position.id = $2.handle.id;
				$2.handle.id = 0;
				handle_merge(&$1, &$2);
				$$ = $1;
			}
			|	chain_spec	index_spec
			{
				handle_merge(&$1, &$2);
				$$ = $1;
			}
			;

ruleid_spec		:	chain_spec	handle_spec
			{
				handle_merge(&$1, &$2);
				$$ = $1;
			}
			;

comment_spec		:	COMMENT		string
			{
				if (strlen($2) > NFTNL_UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&@2, "comment too long, %d characters maximum allowed",
							 NFTNL_UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				$$ = $2;
			}
			;

ruleset_spec		:	/* empty */
			{
				memset(&$$, 0, sizeof($$));
				$$.family	= NFPROTO_UNSPEC;
			}
			|	family_spec_explicit
			{
				memset(&$$, 0, sizeof($$));
				$$.family	= $1;
			}
			;

rule			:	rule_alloc
			{
				$$->comment = NULL;
			}
			|	rule_alloc	comment_spec
			{
				$$->comment = $2;
			}
			;

rule_alloc		:	stmt_list
			{
				struct stmt *i;

				$$ = rule_alloc(&@$, NULL);
				list_for_each_entry(i, $1, list)
					$$->num_stmts++;
				list_splice_tail($1, &$$->stmts);
				xfree($1);
			}
			;

stmt_list		:	stmt
			{
				$$ = xmalloc(sizeof(*$$));
				init_list_head($$);
				list_add_tail(&$1->list, $$);
			}
			|	stmt_list		stmt
			{
				$$ = $1;
				list_add_tail(&$2->list, $1);
			}
			;

stateful_stmt_list	:	stateful_stmt
			{
				$$ = xmalloc(sizeof(*$$));
				init_list_head($$);
				list_add_tail(&$1->list, $$);
			}
			|	stateful_stmt_list	stateful_stmt
			{
				$$ = $1;
				list_add_tail(&$2->list, $1);
			}
			;

stateful_stmt		:	counter_stmt
			|	limit_stmt
			|	quota_stmt
			|	connlimit_stmt
			;

stmt			:	verdict_stmt
			|	match_stmt
			|	meter_stmt
			|	payload_stmt
			|	stateful_stmt
			|	meta_stmt
			|	log_stmt
			|	reject_stmt
			|	nat_stmt
			|	tproxy_stmt
			|	queue_stmt
			|	ct_stmt
			|	masq_stmt
			|	redir_stmt
			|	dup_stmt
			|	fwd_stmt
			|	set_stmt
			|	map_stmt
			|	synproxy_stmt
			|	chain_stmt
			;

chain_stmt_type		:	JUMP	{ $$ = NFT_JUMP; }
			|	GOTO	{ $$ = NFT_GOTO; }
			;

chain_stmt		:	chain_stmt_type	chain_block_alloc '{'	subchain_block	'}'
			{
				$2->location = @2;
				close_scope(state);
				$4->location = @4;
				$$ = chain_stmt_alloc(&@$, $4, $1);
			}
			;

verdict_stmt		:	verdict_expr
			{
				$$ = verdict_stmt_alloc(&@$, $1);
			}
			|	verdict_map_stmt
			{
				$$ = verdict_stmt_alloc(&@$, $1);
			}
			;

verdict_map_stmt	:	concat_expr	VMAP	verdict_map_expr
			{
				$$ = map_expr_alloc(&@$, $1, $3);
			}
			;

verdict_map_expr	:	'{'	verdict_map_list_expr	'}'
			{
				$2->location = @$;
				$$ = $2;
			}
			|	set_ref_expr
			;

verdict_map_list_expr	:	verdict_map_list_member_expr
			{
				$$ = set_expr_alloc(&@$, NULL);
				compound_expr_add($$, $1);
			}
			|	verdict_map_list_expr	COMMA	verdict_map_list_member_expr
			{
				compound_expr_add($1, $3);
				$$ = $1;
			}
			|	verdict_map_list_expr	COMMA	opt_newline
			;

verdict_map_list_member_expr:	opt_newline	set_elem_expr	COLON	verdict_expr	opt_newline
			{
				$$ = mapping_expr_alloc(&@$, $2, $4);
			}
			;

connlimit_stmt		:	CT	COUNT	NUM
			{
				$$ = connlimit_stmt_alloc(&@$);
				$$->connlimit.count	= $3;
			}
			|	CT	COUNT	OVER	NUM
			{
				$$ = connlimit_stmt_alloc(&@$);
				$$->connlimit.count = $4;
				$$->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
			;

counter_stmt		:	counter_stmt_alloc
			|	counter_stmt_alloc	counter_args

counter_stmt_alloc	:	COUNTER
			{
				$$ = counter_stmt_alloc(&@$);
			}
			|	COUNTER		NAME	stmt_expr
			{
				$$ = objref_stmt_alloc(&@$);
				$$->objref.type = NFT_OBJECT_COUNTER;
				$$->objref.expr = $3;
			}
			;

counter_args		:	counter_arg
			{
				$<stmt>$	= $<stmt>0;
			}
			|	counter_args	counter_arg
			;

counter_arg		:	PACKETS			NUM
			{
				$<stmt>0->counter.packets = $2;
			}
			|	BYTES			NUM
			{
				$<stmt>0->counter.bytes	 = $2;
			}
			;

log_stmt		:	log_stmt_alloc
			|	log_stmt_alloc		log_args
			;

log_stmt_alloc		:	LOG
			{
				$$ = log_stmt_alloc(&@$);
			}
			;

log_args		:	log_arg
			{
				$<stmt>$	= $<stmt>0;
			}
			|	log_args	log_arg
			;

log_arg			:	PREFIX			string
			{
				struct scope *scope = current_scope(state);
				bool done = false, another_var = false;
				char *start, *end, scratch = '\0';
				struct expr *expr, *item;
				struct symbol *sym;
				enum {
					PARSE_TEXT,
					PARSE_VAR,
				} prefix_state;

				/* No variables in log prefix, skip. */
				if (!strchr($2, '$')) {
					expr = constant_expr_alloc(&@$, &string_type,
								   BYTEORDER_HOST_ENDIAN,
								   (strlen($2) + 1) * BITS_PER_BYTE, $2);
					xfree($2);
					$<stmt>0->log.prefix = expr;
					$<stmt>0->log.flags |= STMT_LOG_PREFIX;
					break;
				}

				/* Parse variables in log prefix string using a
				 * state machine parser with two states. This
				 * parser creates list of expressions composed
				 * of constant and variable expressions.
				 */
				expr = compound_expr_alloc(&@$, EXPR_LIST);

				start = (char *)$2;

				if (*start != '$') {
					prefix_state = PARSE_TEXT;
				} else {
					prefix_state = PARSE_VAR;
					start++;
				}
				end = start;

				/* Not nice, but works. */
				while (!done) {
					switch (prefix_state) {
					case PARSE_TEXT:
						while (*end != '\0' && *end != '$')
							end++;

						if (*end == '\0')
							done = true;

						*end = '\0';
						item = constant_expr_alloc(&@$, &string_type,
									   BYTEORDER_HOST_ENDIAN,
									   (strlen(start) + 1) * BITS_PER_BYTE,
									   start);
						compound_expr_add(expr, item);

						if (done)
							break;

						start = end + 1;
						end = start;

						/* fall through */
					case PARSE_VAR:
						while (isalnum(*end) || *end == '_')
							end++;

						if (*end == '\0')
							done = true;
						else if (*end == '$')
							another_var = true;
						else
							scratch = *end;

						*end = '\0';

						sym = symbol_get(scope, start);
						if (!sym) {
							sym = symbol_lookup_fuzzy(scope, start);
							if (sym) {
								erec_queue(error(&@2, "unknown identifier '%s'; "
										 "did you mean identifier ‘%s’?",
										 start, sym->identifier),
									   state->msgs);
							} else {
								erec_queue(error(&@2, "unknown identifier '%s'",
										 start),
									   state->msgs);
							}
							expr_free(expr);
							xfree($2);
							YYERROR;
						}
						item = variable_expr_alloc(&@$, scope, sym);
						compound_expr_add(expr, item);

						if (done)
							break;

						/* Restore original byte after
						 * symbol lookup.
						 */
						if (scratch) {
							*end = scratch;
							scratch = '\0';
						}

						start = end;
						if (another_var) {
							another_var = false;
							start++;
							prefix_state = PARSE_VAR;
						} else {
							prefix_state = PARSE_TEXT;
						}
						end = start;
						break;
					}
				}

				xfree($2);
				$<stmt>0->log.prefix	 = expr;
				$<stmt>0->log.flags 	|= STMT_LOG_PREFIX;
			}
			|	GROUP			NUM
			{
				$<stmt>0->log.group	 = $2;
				$<stmt>0->log.flags 	|= STMT_LOG_GROUP;
			}
			|	SNAPLEN			NUM
			{
				$<stmt>0->log.snaplen	 = $2;
				$<stmt>0->log.flags 	|= STMT_LOG_SNAPLEN;
			}
			|	QUEUE_THRESHOLD		NUM
			{
				$<stmt>0->log.qthreshold = $2;
				$<stmt>0->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
			|	LEVEL			level_type
			{
				$<stmt>0->log.level	= $2;
				$<stmt>0->log.flags 	|= STMT_LOG_LEVEL;
			}
			|	FLAGS			log_flags
			{
				$<stmt>0->log.logflags	|= $2;
			}
			;

level_type		:	string
			{
				if (!strcmp("emerg", $1))
					$$ = NFT_LOGLEVEL_EMERG;
				else if (!strcmp("alert", $1))
					$$ = NFT_LOGLEVEL_ALERT;
				else if (!strcmp("crit", $1))
					$$ = NFT_LOGLEVEL_CRIT;
				else if (!strcmp("err", $1))
					$$ = NFT_LOGLEVEL_ERR;
				else if (!strcmp("warn", $1))
					$$ = NFT_LOGLEVEL_WARNING;
				else if (!strcmp("notice", $1))
					$$ = NFT_LOGLEVEL_NOTICE;
				else if (!strcmp("info", $1))
					$$ = NFT_LOGLEVEL_INFO;
				else if (!strcmp("debug", $1))
					$$ = NFT_LOGLEVEL_DEBUG;
				else if (!strcmp("audit", $1))
					$$ = NFT_LOGLEVEL_AUDIT;
				else {
					erec_queue(error(&@1, "invalid log level"),
						   state->msgs);
					xfree($1);
					YYERROR;
				}
				xfree($1);
			}
			;

log_flags		:	TCP	log_flags_tcp
			{
				$$ = $2;
			}
			|	IP	OPTIONS
			{
				$$ = NF_LOG_IPOPT;
			}
			|	SKUID
			{
				$$ = NF_LOG_UID;
			}
			|	ETHER
			{
				$$ = NF_LOG_MACDECODE;
			}
			|	ALL
			{
				$$ = NF_LOG_MASK;
			}
			;

log_flags_tcp		:	log_flags_tcp	COMMA	log_flag_tcp
			{
				$$ = $1 | $3;
			}
			|	log_flag_tcp
			;

log_flag_tcp		:	SEQUENCE
			{
				$$ = NF_LOG_TCPSEQ;
			}
			|	OPTIONS
			{
				$$ = NF_LOG_TCPOPT;
			}
			;

limit_stmt		:	LIMIT	RATE	limit_mode	NUM	SLASH	time_unit	limit_burst_pkts
	    		{
				if ($7 == 0) {
					erec_queue(error(&@7, "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				$$ = limit_stmt_alloc(&@$);
				$$->limit.rate	= $4;
				$$->limit.unit	= $6;
				$$->limit.burst	= $7;
				$$->limit.type	= NFT_LIMIT_PKTS;
				$$->limit.flags = $3;
			}
			|	LIMIT	RATE	limit_mode	NUM	STRING	limit_burst_bytes
			{
				struct error_record *erec;
				uint64_t rate, unit;

				if ($6 == 0) {
					erec_queue(error(&@6, "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}

				erec = rate_parse(&@$, $5, &rate, &unit);
				xfree($5);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				$$ = limit_stmt_alloc(&@$);
				$$->limit.rate	= rate * $4;
				$$->limit.unit	= unit;
				$$->limit.burst	= $6;
				$$->limit.type	= NFT_LIMIT_PKT_BYTES;
				$$->limit.flags = $3;
			}
			|	LIMIT	NAME	stmt_expr
			{
				$$ = objref_stmt_alloc(&@$);
				$$->objref.type = NFT_OBJECT_LIMIT;
				$$->objref.expr = $3;
			}
			;

quota_mode		:	OVER		{ $$ = NFT_QUOTA_F_INV; }
			|	UNTIL		{ $$ = 0; }
			|	/* empty */	{ $$ = 0; }
			;

quota_unit		:	BYTES		{ $$ = xstrdup("bytes"); }
			|	STRING		{ $$ = $1; }
			;

quota_used		:	/* empty */	{ $$ = 0; }
			|	USED NUM quota_unit
			{
				struct error_record *erec;
				uint64_t rate;

				erec = data_unit_parse(&@$, $3, &rate);
				xfree($3);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				$$ = $2 * rate;
			}
			;

quota_stmt		:	QUOTA	quota_mode NUM quota_unit quota_used
			{
				struct error_record *erec;
				uint64_t rate;

				erec = data_unit_parse(&@$, $4, &rate);
				xfree($4);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				$$ = quota_stmt_alloc(&@$);
				$$->quota.bytes	= $3 * rate;
				$$->quota.used = $5;
				$$->quota.flags	= $2;
			}
			|	QUOTA	NAME	stmt_expr
			{
				$$ = objref_stmt_alloc(&@$);
				$$->objref.type = NFT_OBJECT_QUOTA;
				$$->objref.expr = $3;
			}
			;

limit_mode		:	OVER				{ $$ = NFT_LIMIT_F_INV; }
			|	UNTIL				{ $$ = 0; }
			|	/* empty */			{ $$ = 0; }
			;

limit_burst_pkts	:	/* empty */			{ $$ = 5; }
			|	BURST	NUM	PACKETS		{ $$ = $2; }
			;

limit_burst_bytes	:	/* empty */			{ $$ = 5; }
			|	BURST	NUM	BYTES		{ $$ = $2; }
			|	BURST	NUM	STRING
			{
				struct error_record *erec;
				uint64_t rate;

				erec = data_unit_parse(&@$, $3, &rate);
				xfree($3);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				$$ = $2 * rate;
			}
			;

time_unit		:	SECOND		{ $$ = 1ULL; }
			|	MINUTE		{ $$ = 1ULL * 60; }
			|	HOUR		{ $$ = 1ULL * 60 * 60; }
			|	DAY		{ $$ = 1ULL * 60 * 60 * 24; }
			|	WEEK		{ $$ = 1ULL * 60 * 60 * 24 * 7; }
			;

reject_stmt		:	reject_stmt_alloc	reject_opts
			;

reject_stmt_alloc	:	_REJECT
			{
				$$ = reject_stmt_alloc(&@$);
			}
			;

reject_opts		:       /* empty */
			{
				$<stmt>0->reject.type = -1;
				$<stmt>0->reject.icmp_code = -1;
			}
			|	WITH	ICMP	TYPE	STRING
			{
				$<stmt>0->reject.family = NFPROTO_IPV4;
				$<stmt>0->reject.type = NFT_REJECT_ICMP_UNREACH;
				$<stmt>0->reject.expr =
					symbol_expr_alloc(&@$, SYMBOL_VALUE,
							  current_scope(state),
							  $4);
				datatype_set($<stmt>0->reject.expr, &icmp_code_type);
				xfree($4);
			}
			|	WITH	ICMP6	TYPE	STRING
			{
				$<stmt>0->reject.family = NFPROTO_IPV6;
				$<stmt>0->reject.type = NFT_REJECT_ICMP_UNREACH;
				$<stmt>0->reject.expr =
					symbol_expr_alloc(&@$, SYMBOL_VALUE,
							  current_scope(state),
							  $4);
				datatype_set($<stmt>0->reject.expr, &icmpv6_code_type);
				xfree($4);
			}
			|	WITH	ICMPX	TYPE	STRING
			{
				$<stmt>0->reject.type = NFT_REJECT_ICMPX_UNREACH;
				$<stmt>0->reject.expr =
					symbol_expr_alloc(&@$, SYMBOL_VALUE,
							  current_scope(state),
							  $4);
				datatype_set($<stmt>0->reject.expr, &icmpx_code_type);
				xfree($4);
			}
			|	WITH	TCP	RESET
			{
				$<stmt>0->reject.type = NFT_REJECT_TCP_RST;
			}
			;

nat_stmt		:	nat_stmt_alloc	nat_stmt_args
			;

nat_stmt_alloc		:	SNAT	{ $$ = nat_stmt_alloc(&@$, NFT_NAT_SNAT); }
			|	DNAT	{ $$ = nat_stmt_alloc(&@$, NFT_NAT_DNAT); }
			;

tproxy_stmt		:	TPROXY TO stmt_expr
			{
				$$ = tproxy_stmt_alloc(&@$);
				$$->tproxy.family = NFPROTO_UNSPEC;
				$$->tproxy.addr = $3;
			}
			|	TPROXY nf_key_proto TO stmt_expr
			{
				$$ = tproxy_stmt_alloc(&@$);
				$$->tproxy.family = $2;
				$$->tproxy.addr = $4;
			}
			|	TPROXY TO COLON stmt_expr
			{
				$$ = tproxy_stmt_alloc(&@$);
				$$->tproxy.family = NFPROTO_UNSPEC;
				$$->tproxy.port = $4;
			}
			|	TPROXY TO stmt_expr COLON stmt_expr
			{
				$$ = tproxy_stmt_alloc(&@$);
				$$->tproxy.family = NFPROTO_UNSPEC;
				$$->tproxy.addr = $3;
				$$->tproxy.port = $5;
			}
			|	TPROXY nf_key_proto	TO stmt_expr COLON stmt_expr
			{
				$$ = tproxy_stmt_alloc(&@$);
				$$->tproxy.family = $2;
				$$->tproxy.addr = $4;
				$$->tproxy.port = $6;
			}
			|	TPROXY nf_key_proto	TO COLON stmt_expr
			{
				$$ = tproxy_stmt_alloc(&@$);
				$$->tproxy.family = $2;
				$$->tproxy.port = $5;
			}
			;

synproxy_stmt		:	synproxy_stmt_alloc
			|	synproxy_stmt_alloc	synproxy_args
			;

synproxy_stmt_alloc	:	SYNPROXY
			{
				$$ = synproxy_stmt_alloc(&@$);
			}
			|	SYNPROXY	NAME	stmt_expr
			{
				$$ = objref_stmt_alloc(&@$);
				$$->objref.type = NFT_OBJECT_SYNPROXY;
				$$->objref.expr = $3;
			}
			;

synproxy_args		:	synproxy_arg
			{
				$<stmt>$	= $<stmt>0;
			}
			|	synproxy_args	synproxy_arg
			;

synproxy_arg		:	MSS	NUM
			{
				$<stmt>0->synproxy.mss = $2;
				$<stmt>0->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
			|	WSCALE	NUM
			{
				$<stmt>0->synproxy.wscale = $2;
				$<stmt>0->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
			|	TIMESTAMP
			{
				$<stmt>0->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
			|	SACK_PERM
			{
				$<stmt>0->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
			;

synproxy_config		:	MSS	NUM	WSCALE	NUM	synproxy_ts	synproxy_sack
			{
				struct synproxy *synproxy;
				uint32_t flags = 0;

				synproxy = &$<obj>0->synproxy;
				synproxy->mss = $2;
				flags |= NF_SYNPROXY_OPT_MSS;
				synproxy->wscale = $4;
				flags |= NF_SYNPROXY_OPT_WSCALE;
				if ($5)
					flags |= $5;
				if ($6)
					flags |= $6;
				synproxy->flags = flags;
			}
			|	MSS	NUM	stmt_separator	WSCALE	NUM	stmt_separator	synproxy_ts	synproxy_sack
			{
				struct synproxy *synproxy;
				uint32_t flags = 0;

				synproxy = &$<obj>0->synproxy;
				synproxy->mss = $2;
				flags |= NF_SYNPROXY_OPT_MSS;
				synproxy->wscale = $5;
				flags |= NF_SYNPROXY_OPT_WSCALE;
				if ($7)
					flags |= $7;
				if ($8)
					flags |= $8;
				synproxy->flags = flags;
			}
			;

synproxy_obj		:	/* empty */
			{
				$$ = obj_alloc(&@$);
				$$->type = NFT_OBJECT_SYNPROXY;
			}
			;

synproxy_ts		:	/* empty */	{ $$ = 0; }
			|	TIMESTAMP
			{
				$$ = NF_SYNPROXY_OPT_TIMESTAMP;
			}
			;

synproxy_sack		:	/* empty */	{ $$ = 0; }
			|	SACK_PERM
			{
				$$ = NF_SYNPROXY_OPT_SACK_PERM;
			}
			;

primary_stmt_expr	:	symbol_expr			{ $$ = $1; }
			|	integer_expr			{ $$ = $1; }
			|	boolean_expr			{ $$ = $1; }
			|	meta_expr			{ $$ = $1; }
			|	rt_expr				{ $$ = $1; }
			|	ct_expr				{ $$ = $1; }
			|	numgen_expr             	{ $$ = $1; }
			|	hash_expr               	{ $$ = $1; }
			|	payload_expr			{ $$ = $1; }
			|	keyword_expr			{ $$ = $1; }
			|	socket_expr			{ $$ = $1; }
			|	osf_expr			{ $$ = $1; }
			|	'('	basic_stmt_expr	')'	{ $$ = $2; }
			;

shift_stmt_expr		:	primary_stmt_expr
			|	shift_stmt_expr		LSHIFT		primary_stmt_expr
			{
				$$ = binop_expr_alloc(&@$, OP_LSHIFT, $1, $3);
			}
			|	shift_stmt_expr		RSHIFT		primary_stmt_expr
			{
				$$ = binop_expr_alloc(&@$, OP_RSHIFT, $1, $3);
			}
			;

and_stmt_expr		:	shift_stmt_expr
			|	and_stmt_expr		AMPERSAND	shift_stmt_expr
			{
				$$ = binop_expr_alloc(&@$, OP_AND, $1, $3);
			}
			;

exclusive_or_stmt_expr	:	and_stmt_expr
			|	exclusive_or_stmt_expr	CARET		and_stmt_expr
			{
				$$ = binop_expr_alloc(&@$, OP_XOR, $1, $3);
			}
			;

inclusive_or_stmt_expr	:	exclusive_or_stmt_expr
			|	inclusive_or_stmt_expr	'|'		exclusive_or_stmt_expr
			{
				$$ = binop_expr_alloc(&@$, OP_OR, $1, $3);
			}
			;

basic_stmt_expr		:	inclusive_or_stmt_expr
			;

concat_stmt_expr	:	basic_stmt_expr
			|	concat_stmt_expr	DOT	primary_stmt_expr
			{
				struct location rhs[] = {
					[1]	= @2,
					[2]	= @3,
				};

				$$ = handle_concat_expr(&@$, $$, $1, $3, rhs);
			}
			;

map_stmt_expr_set	:	set_expr
			|	set_ref_expr
			;

map_stmt_expr		:	concat_stmt_expr	MAP	map_stmt_expr_set
			{
				$$ = map_expr_alloc(&@$, $1, $3);
			}
			|	concat_stmt_expr	{ $$ = $1; }
			;

prefix_stmt_expr	:	basic_stmt_expr	SLASH	NUM
			{
				$$ = prefix_expr_alloc(&@$, $1, $3);
			}
			;

range_stmt_expr		:	basic_stmt_expr	DASH	basic_stmt_expr
			{
				$$ = range_expr_alloc(&@$, $1, $3);
			}
			;

wildcard_expr		:	ASTERISK
			{
				struct expr *expr;

				expr = constant_expr_alloc(&@$, &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				$$ = prefix_expr_alloc(&@$, expr, 0);
			}
			;

multiton_stmt_expr	:	prefix_stmt_expr
			|	range_stmt_expr
			|	wildcard_expr
			;

stmt_expr		:	map_stmt_expr
			|	multiton_stmt_expr
			|	list_stmt_expr
			;

nat_stmt_args		:	stmt_expr
			{
				$<stmt>0->nat.addr = $1;
			}
			|	TO	stmt_expr
			{
				$<stmt>0->nat.addr = $2;
			}
			|	nf_key_proto	TO	stmt_expr
			{
				$<stmt>0->nat.family = $1;
				$<stmt>0->nat.addr = $3;
			}
			|	stmt_expr	COLON	stmt_expr
			{
				$<stmt>0->nat.addr = $1;
				$<stmt>0->nat.proto = $3;
			}
			|	TO	stmt_expr	COLON	stmt_expr
			{
				$<stmt>0->nat.addr = $2;
				$<stmt>0->nat.proto = $4;
			}
			|	nf_key_proto	TO	 stmt_expr	COLON	stmt_expr
			{
				$<stmt>0->nat.family = $1;
				$<stmt>0->nat.addr = $3;
				$<stmt>0->nat.proto = $5;
			}
			|	COLON		stmt_expr
			{
				$<stmt>0->nat.proto = $2;
			}
			|	TO	COLON		stmt_expr
			{
				$<stmt>0->nat.proto = $3;
			}
			|       nat_stmt_args   nf_nat_flags
			{
				$<stmt>0->nat.flags = $2;
			}
			|	nf_key_proto ADDR DOT	PORT	TO	stmt_expr
			{
				$<stmt>0->nat.family = $1;
				$<stmt>0->nat.addr = $6;
				$<stmt>0->nat.type_flags = STMT_NAT_F_CONCAT;
			}
			|	nf_key_proto INTERVAL TO	stmt_expr
			{
				$<stmt>0->nat.family = $1;
				$<stmt>0->nat.addr = $4;
				$<stmt>0->nat.type_flags = STMT_NAT_F_INTERVAL;
			}
			|	INTERVAL TO	stmt_expr
			{
				$<stmt>0->nat.addr = $3;
				$<stmt>0->nat.type_flags = STMT_NAT_F_INTERVAL;
			}
			|	nf_key_proto PREFIX TO	stmt_expr
			{
				$<stmt>0->nat.family = $1;
				$<stmt>0->nat.addr = $4;
				$<stmt>0->nat.type_flags =
						STMT_NAT_F_PREFIX |
						STMT_NAT_F_INTERVAL;
				$<stmt>0->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
			|	PREFIX TO	stmt_expr
			{
				$<stmt>0->nat.addr = $3;
				$<stmt>0->nat.type_flags =
						STMT_NAT_F_PREFIX |
						STMT_NAT_F_INTERVAL;
				$<stmt>0->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
			;

masq_stmt		:	masq_stmt_alloc		masq_stmt_args
			|	masq_stmt_alloc
			;

masq_stmt_alloc		:	MASQUERADE	{ $$ = nat_stmt_alloc(&@$, NFT_NAT_MASQ); }
			;

masq_stmt_args		:	TO 	COLON	stmt_expr
			{
				$<stmt>0->nat.proto = $3;
			}
			|	TO 	COLON	stmt_expr	nf_nat_flags
			{
				$<stmt>0->nat.proto = $3;
				$<stmt>0->nat.flags = $4;
			}
			|	nf_nat_flags
			{
				$<stmt>0->nat.flags = $1;
			}
			;

redir_stmt		:	redir_stmt_alloc	redir_stmt_arg
			|	redir_stmt_alloc
			;

redir_stmt_alloc	:	REDIRECT	{ $$ = nat_stmt_alloc(&@$, NFT_NAT_REDIR); }
			;

redir_stmt_arg		:	TO	stmt_expr
			{
				$<stmt>0->nat.proto = $2;
			}
			|	TO	COLON	stmt_expr
			{
				$<stmt>0->nat.proto = $3;
			}
			|	nf_nat_flags
			{
				$<stmt>0->nat.flags = $1;
			}
			|	TO	stmt_expr	nf_nat_flags
			{
				$<stmt>0->nat.proto = $2;
				$<stmt>0->nat.flags = $3;
			}
			|	TO	COLON	stmt_expr	nf_nat_flags
			{
				$<stmt>0->nat.proto = $3;
				$<stmt>0->nat.flags = $4;
			}
			;

dup_stmt		:	DUP	TO	stmt_expr
			{
				$$ = dup_stmt_alloc(&@$);
				$$->dup.to = $3;
			}
			|	DUP	TO	stmt_expr 	DEVICE	stmt_expr
			{
				$$ = dup_stmt_alloc(&@$);
				$$->dup.to = $3;
				$$->dup.dev = $5;
			}
			;

fwd_stmt		:	FWD	TO	stmt_expr
			{
				$$ = fwd_stmt_alloc(&@$);
				$$->fwd.dev = $3;
			}
			|	FWD	nf_key_proto	TO	stmt_expr	DEVICE	stmt_expr
			{
				$$ = fwd_stmt_alloc(&@$);
				$$->fwd.family = $2;
				$$->fwd.addr = $4;
				$$->fwd.dev = $6;
			}
			;

nf_nat_flags		:	nf_nat_flag
			|	nf_nat_flags	COMMA	nf_nat_flag
			{
				$$ = $1 | $3;
			}
			;

nf_nat_flag		:	RANDOM		{ $$ = NF_NAT_RANGE_PROTO_RANDOM; }
			|	FULLY_RANDOM	{ $$ = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
			|	PERSISTENT 	{ $$ = NF_NAT_RANGE_PERSISTENT; }
			;

queue_stmt		:	queue_stmt_alloc
			|	queue_stmt_alloc	queue_stmt_args
			;

queue_stmt_alloc	:	QUEUE
			{
				$$ = queue_stmt_alloc(&@$);
			}
			;

queue_stmt_args		:	queue_stmt_arg
			{
				$<stmt>$	= $<stmt>0;
			}
			|	queue_stmt_args	queue_stmt_arg
			;

queue_stmt_arg		:	QUEUENUM	stmt_expr
			{
				$<stmt>0->queue.queue = $2;
				$<stmt>0->queue.queue->location = @$;
			}
			|	queue_stmt_flags
			{
				$<stmt>0->queue.flags |= $1;
			}
			;

queue_stmt_flags	:	queue_stmt_flag
			|	queue_stmt_flags	COMMA	queue_stmt_flag
			{
				$$ = $1 | $3;
			}
			;

queue_stmt_flag		:	BYPASS	{ $$ = NFT_QUEUE_FLAG_BYPASS; }
			|	FANOUT	{ $$ = NFT_QUEUE_FLAG_CPU_FANOUT; }
			;

set_elem_expr_stmt	:	set_elem_expr_stmt_alloc
			|	set_elem_expr_stmt_alloc	set_elem_options
			;

set_elem_expr_stmt_alloc:	concat_expr
			{
				$$ = set_elem_expr_alloc(&@1, $1);
			}
			;

set_stmt		:	SET	set_stmt_op	set_elem_expr_stmt	set_ref_expr
			{
				$$ = set_stmt_alloc(&@$);
				$$->set.op  = $2;
				$$->set.key = $3;
				$$->set.set = $4;
			}
			|	set_stmt_op	set_ref_expr	'{' set_elem_expr_stmt	'}'
			{
				$$ = set_stmt_alloc(&@$);
				$$->set.op  = $1;
				$$->set.key = $4;
				$$->set.set = $2;
			}
			|	set_stmt_op	set_ref_expr '{' set_elem_expr_stmt	stateful_stmt_list	'}'
			{
				$$ = set_stmt_alloc(&@$);
				$$->set.op  = $1;
				$$->set.key = $4;
				$$->set.set = $2;
				list_splice_tail($5, &$$->set.stmt_list);
				free($5);
			}
			;

set_stmt_op		:	ADD	{ $$ = NFT_DYNSET_OP_ADD; }
			|	UPDATE	{ $$ = NFT_DYNSET_OP_UPDATE; }
			|	DELETE  { $$ = NFT_DYNSET_OP_DELETE; }
			;

map_stmt		:	set_stmt_op	set_ref_expr '{' set_elem_expr_stmt	COLON	set_elem_expr_stmt	'}'
			{
				$$ = map_stmt_alloc(&@$);
				$$->map.op  = $1;
				$$->map.key = $4;
				$$->map.data = $6;
				$$->map.set = $2;
			}
			|	set_stmt_op	set_ref_expr '{' set_elem_expr_stmt	stateful_stmt_list	COLON	set_elem_expr_stmt	'}'
			{
				$$ = map_stmt_alloc(&@$);
				$$->map.op  = $1;
				$$->map.key = $4;
				$$->map.data = $7;
				$$->map.set = $2;
				list_splice_tail($5, &$$->map.stmt_list);
				free($5);
			}
			;

meter_stmt		:	flow_stmt_legacy_alloc		flow_stmt_opts	'{' meter_key_expr stmt '}'
			{
				$1->meter.key  = $4;
				$1->meter.stmt = $5;
				$$->location  = @$;
				$$ = $1;
			}
			|	meter_stmt_alloc		{ $$ = $1; }
			;

flow_stmt_legacy_alloc	:	FLOW
			{
				$$ = meter_stmt_alloc(&@$);
			}
			;

flow_stmt_opts		:	flow_stmt_opt
			{
				$<stmt>$	= $<stmt>0;
			}
			|	flow_stmt_opts		flow_stmt_opt
			;

flow_stmt_opt		:	TABLE			identifier
			{
				$<stmt>0->meter.name = $2;
			}
			;

meter_stmt_alloc	:	METER	identifier		'{' meter_key_expr stmt '}'
			{
				$$ = meter_stmt_alloc(&@$);
				$$->meter.name = $2;
				$$->meter.size = 0;
				$$->meter.key  = $4;
				$$->meter.stmt = $5;
				$$->location  = @$;
			}
			|	METER	identifier	SIZE	NUM	'{' meter_key_expr stmt '}'
			{
				$$ = meter_stmt_alloc(&@$);
				$$->meter.name = $2;
				$$->meter.size = $4;
				$$->meter.key  = $6;
				$$->meter.stmt = $7;
				$$->location  = @$;
			}
			;

match_stmt		:	relational_expr
			{
				$$ = expr_stmt_alloc(&@$, $1);
			}
			;

variable_expr		:	'$'	identifier
			{
				struct scope *scope = current_scope(state);
				struct symbol *sym;

				sym = symbol_get(scope, $2);
				if (!sym) {
					sym = symbol_lookup_fuzzy(scope, $2);
					if (sym) {
						erec_queue(error(&@2, "unknown identifier '%s'; "
								      "did you mean identifier ‘%s’?",
								      $2, sym->identifier),
							   state->msgs);
					} else {
						erec_queue(error(&@2, "unknown identifier '%s'", $2),
							   state->msgs);
					}
					xfree($2);
					YYERROR;
				}

				$$ = variable_expr_alloc(&@$, scope, sym);
				xfree($2);
			}
			;

symbol_expr		:	variable_expr
			|	string
			{
				$$ = symbol_expr_alloc(&@$, SYMBOL_VALUE,
						       current_scope(state),
						       $1);
				xfree($1);
			}
			;

set_ref_expr		:	set_ref_symbol_expr
			|	variable_expr
			;

set_ref_symbol_expr	:	AT	identifier
			{
				$$ = symbol_expr_alloc(&@$, SYMBOL_SET,
						       current_scope(state),
						       $2);
				xfree($2);
			}
			;

integer_expr		:	NUM
			{
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, $1);
				$$ = symbol_expr_alloc(&@$, SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
			;

primary_expr		:	symbol_expr			{ $$ = $1; }
			|	integer_expr			{ $$ = $1; }
			|	payload_expr			{ $$ = $1; }
			|	exthdr_expr			{ $$ = $1; }
			|	exthdr_exists_expr		{ $$ = $1; }
			|	meta_expr			{ $$ = $1; }
			|	socket_expr			{ $$ = $1; }
			|	rt_expr				{ $$ = $1; }
			|	ct_expr				{ $$ = $1; }
			|	numgen_expr			{ $$ = $1; }
			|	hash_expr			{ $$ = $1; }
			|	fib_expr			{ $$ = $1; }
			|	osf_expr			{ $$ = $1; }
			|	xfrm_expr			{ $$ = $1; }
			|	'('	basic_expr	')'	{ $$ = $2; }
			;

fib_expr		:	FIB	fib_tuple	fib_result
			{
				if (($2 & (NFTA_FIB_F_SADDR|NFTA_FIB_F_DADDR)) == 0) {
					erec_queue(error(&@2, "fib: need either saddr or daddr"), state->msgs);
					YYERROR;
				}

				if (($2 & (NFTA_FIB_F_SADDR|NFTA_FIB_F_DADDR)) ==
					  (NFTA_FIB_F_SADDR|NFTA_FIB_F_DADDR)) {
					erec_queue(error(&@2, "fib: saddr and daddr are mutually exclusive"), state->msgs);
					YYERROR;
				}

				if (($2 & (NFTA_FIB_F_IIF|NFTA_FIB_F_OIF)) ==
					  (NFTA_FIB_F_IIF|NFTA_FIB_F_OIF)) {
					erec_queue(error(&@2, "fib: iif and oif are mutually exclusive"), state->msgs);
					YYERROR;
				}

				$$ = fib_expr_alloc(&@$, $2, $3);
			}
			;

fib_result		:	OIF	{ $$ =NFT_FIB_RESULT_OIF; }
			|	OIFNAME { $$ =NFT_FIB_RESULT_OIFNAME; }
			|	TYPE	{ $$ =NFT_FIB_RESULT_ADDRTYPE; }
			;

fib_flag		:       SADDR	{ $$ = NFTA_FIB_F_SADDR; }
			|	DADDR	{ $$ = NFTA_FIB_F_DADDR; }
			|	MARK	{ $$ = NFTA_FIB_F_MARK; }
			|	IIF	{ $$ = NFTA_FIB_F_IIF; }
			|	OIF	{ $$ = NFTA_FIB_F_OIF; }
			;

fib_tuple		:  	fib_flag	DOT	fib_tuple
			{
				$$ = $1 | $3;
			}
			|	fib_flag
			;

osf_expr		:	OSF	osf_ttl		HDRVERSION
			{
				$$ = osf_expr_alloc(&@$, $2, NFT_OSF_F_VERSION);
			}
			|	OSF	osf_ttl		NAME
			{
				$$ = osf_expr_alloc(&@$, $2, 0);
			}
			;

osf_ttl			:	/* empty */
			{
				$$ = NF_OSF_TTL_TRUE;
			}
			|	TTL	STRING
			{
				if (!strcmp($2, "loose"))
					$$ = NF_OSF_TTL_LESS;
				else if (!strcmp($2, "skip"))
					$$ = NF_OSF_TTL_NOCHECK;
				else {
					erec_queue(error(&@2, "invalid ttl option"),
						   state->msgs);
					YYERROR;
				}
			}
			;

shift_expr		:	primary_expr
			|	shift_expr		LSHIFT		primary_rhs_expr
			{
				$$ = binop_expr_alloc(&@$, OP_LSHIFT, $1, $3);
			}
			|	shift_expr		RSHIFT		primary_rhs_expr
			{
				$$ = binop_expr_alloc(&@$, OP_RSHIFT, $1, $3);
			}
			;

and_expr		:	shift_expr
			|	and_expr		AMPERSAND	shift_rhs_expr
			{
				$$ = binop_expr_alloc(&@$, OP_AND, $1, $3);
			}
			;

exclusive_or_expr	:	and_expr
			|	exclusive_or_expr	CARET		and_rhs_expr
			{
				$$ = binop_expr_alloc(&@$, OP_XOR, $1, $3);
			}
			;

inclusive_or_expr	:	exclusive_or_expr
			|	inclusive_or_expr	'|'		exclusive_or_rhs_expr
			{
				$$ = binop_expr_alloc(&@$, OP_OR, $1, $3);
			}
			;

basic_expr		:	inclusive_or_expr
			;

concat_expr		:	basic_expr
			|	concat_expr		DOT		basic_expr
			{
				struct location rhs[] = {
					[1]	= @2,
					[2]	= @3,
				};

				$$ = handle_concat_expr(&@$, $$, $1, $3, rhs);
			}
			;

prefix_rhs_expr		:	basic_rhs_expr	SLASH	NUM
			{
				$$ = prefix_expr_alloc(&@$, $1, $3);
			}
			;

range_rhs_expr		:	basic_rhs_expr	DASH	basic_rhs_expr
			{
				$$ = range_expr_alloc(&@$, $1, $3);
			}
			;

multiton_rhs_expr	:	prefix_rhs_expr
			|	range_rhs_expr
			;

map_expr		:	concat_expr	MAP	rhs_expr
			{
				$$ = map_expr_alloc(&@$, $1, $3);
			}
			;

expr			:	concat_expr
			|	set_expr
			|       map_expr
			;

set_expr		:	'{'	set_list_expr		'}'
			{
				$2->location = @$;
				$$ = $2;
			}
			;

set_list_expr		:	set_list_member_expr
			{
				$$ = set_expr_alloc(&@$, NULL);
				compound_expr_add($$, $1);
			}
			|	set_list_expr		COMMA	set_list_member_expr
			{
				compound_expr_add($1, $3);
				$$ = $1;
			}
			|	set_list_expr		COMMA	opt_newline
			;

set_list_member_expr	:	opt_newline	set_expr	opt_newline
			{
				$$ = $2;
			}
			|	opt_newline	set_elem_expr	opt_newline
			{
				$$ = $2;
			}
			|	opt_newline	set_elem_expr	COLON	set_rhs_expr	opt_newline
			{
				$$ = mapping_expr_alloc(&@$, $2, $4);
			}
			;

meter_key_expr		:	meter_key_expr_alloc
			|	meter_key_expr_alloc		set_elem_options
			{
				$$->location = @$;
				$$ = $1;
			}
			;

meter_key_expr_alloc	:	concat_expr
			{
				$$ = set_elem_expr_alloc(&@1, $1);
			}
			;

set_elem_expr		:	set_elem_expr_alloc
			|	set_elem_expr_alloc		set_elem_expr_options
			;

set_elem_expr_alloc	:	set_lhs_expr	set_elem_stmt_list
			{
				$$ = set_elem_expr_alloc(&@1, $1);
				list_splice_tail($2, &$$->stmt_list);
				xfree($2);
			}
			|	set_lhs_expr
			{
				$$ = set_elem_expr_alloc(&@1, $1);
			}
			;

set_elem_options	:	set_elem_option
			{
				$<expr>$	= $<expr>0;
			}
			|	set_elem_options	set_elem_option
			;

set_elem_option		:	TIMEOUT			time_spec
			{
				$<expr>0->timeout = $2;
			}
			|	EXPIRES		time_spec
			{
				$<expr>0->expiration = $2;
			}
			|	comment_spec
			{
				if (already_set($<expr>0->comment, &@1, state)) {
					xfree($1);
					YYERROR;
				}
				$<expr>0->comment = $1;
			}
			;

set_elem_expr_options	:	set_elem_expr_option
			{
				$<expr>$	= $<expr>0;
			}
			|	set_elem_expr_options	set_elem_expr_option
			;

set_elem_stmt_list	:	set_elem_stmt
			{
				$$ = xmalloc(sizeof(*$$));
				init_list_head($$);
				list_add_tail(&$1->list, $$);
			}
			|	set_elem_stmt_list	set_elem_stmt
			{
				$$ = $1;
				list_add_tail(&$2->list, $1);
			}
			;

set_elem_stmt		:	COUNTER
			{
				$$ = counter_stmt_alloc(&@$);
			}
			|	COUNTER	PACKETS	NUM	BYTES	NUM
			{
				$$ = counter_stmt_alloc(&@$);
				$$->counter.packets = $3;
				$$->counter.bytes = $5;
			}
			|	LIMIT   RATE    limit_mode      NUM     SLASH   time_unit       limit_burst_pkts
			{
				if ($7 == 0) {
					erec_queue(error(&@7, "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				$$ = limit_stmt_alloc(&@$);
				$$->limit.rate  = $4;
				$$->limit.unit  = $6;
				$$->limit.burst = $7;
				$$->limit.type  = NFT_LIMIT_PKTS;
				$$->limit.flags = $3;
			}
			|       LIMIT   RATE    limit_mode      NUM     STRING  limit_burst_bytes
			{
				struct error_record *erec;
				uint64_t rate, unit;

				if ($6 == 0) {
					erec_queue(error(&@6, "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				erec = rate_parse(&@$, $5, &rate, &unit);
				xfree($5);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				$$ = limit_stmt_alloc(&@$);
				$$->limit.rate  = rate * $4;
				$$->limit.unit  = unit;
				$$->limit.burst = $6;
				$$->limit.type  = NFT_LIMIT_PKT_BYTES;
				$$->limit.flags = $3;
                        }
			;

set_elem_expr_option	:	TIMEOUT			time_spec
			{
				$<expr>0->timeout = $2;
			}
			|	EXPIRES		time_spec
			{
				$<expr>0->expiration = $2;
			}
			|	comment_spec
			{
				if (already_set($<expr>0->comment, &@1, state)) {
					xfree($1);
					YYERROR;
				}
				$<expr>0->comment = $1;
			}
			;

set_lhs_expr		:	concat_rhs_expr
			|	wildcard_expr
			;

set_rhs_expr		:	concat_rhs_expr
			|	verdict_expr
			;

initializer_expr	:	rhs_expr
			|	list_rhs_expr
			|	'{' '}'		{ $$ = compound_expr_alloc(&@$, EXPR_SET); }
			|	DASH	NUM
			{
				int32_t num = -$2;

				$$ = constant_expr_alloc(&@$, &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(num) * BITS_PER_BYTE,
							 &num);
			}
			;

counter_config		:	PACKETS		NUM	BYTES	NUM
			{
				struct counter *counter;

				counter = &$<obj>0->counter;
				counter->packets = $2;
				counter->bytes = $4;
			}
			;

counter_obj		:	/* empty */
			{
				$$ = obj_alloc(&@$);
				$$->type = NFT_OBJECT_COUNTER;
			}
			;

quota_config		:	quota_mode NUM quota_unit quota_used
			{
				struct error_record *erec;
				struct quota *quota;
				uint64_t rate;

				erec = data_unit_parse(&@$, $3, &rate);
				xfree($3);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				quota = &$<obj>0->quota;
				quota->bytes	= $2 * rate;
				quota->used	= $4;
				quota->flags	= $1;
			}
			;

quota_obj		:	/* empty */
			{
				$$ = obj_alloc(&@$);
				$$->type = NFT_OBJECT_QUOTA;
			}
			;

secmark_config		:	string
			{
				int ret;
				struct secmark *secmark;

				secmark = &$<obj>0->secmark;
				ret = snprintf(secmark->ctx, sizeof(secmark->ctx), "%s", $1);
				if (ret <= 0 || ret >= (int)sizeof(secmark->ctx)) {
					erec_queue(error(&@1, "invalid context '%s', max length is %u\n", $1, (int)sizeof(secmark->ctx)), state->msgs);
					xfree($1);
					YYERROR;
				}
				xfree($1);
			}
			;

secmark_obj		:	/* empty */
			{
				$$ = obj_alloc(&@$);
				$$->type = NFT_OBJECT_SECMARK;
			}
			;

ct_obj_type		:	HELPER		{ $$ = NFT_OBJECT_CT_HELPER; }
			|	TIMEOUT		{ $$ = NFT_OBJECT_CT_TIMEOUT; }
			|	EXPECTATION	{ $$ = NFT_OBJECT_CT_EXPECT; }
			;

ct_l4protoname		:	TCP	{ $$ = IPPROTO_TCP; }
			|	UDP	{ $$ = IPPROTO_UDP; }
			;

ct_helper_config		:	TYPE	QUOTED_STRING	PROTOCOL	ct_l4protoname	stmt_separator
			{
				struct ct_helper *ct;
				int ret;

				ct = &$<obj>0->ct_helper;

				ret = snprintf(ct->name, sizeof(ct->name), "%s", $2);
				if (ret <= 0 || ret >= (int)sizeof(ct->name)) {
					erec_queue(error(&@2, "invalid name '%s', max length is %u\n", $2, (int)sizeof(ct->name)), state->msgs);
					YYERROR;
				}
				xfree($2);

				ct->l4proto = $4;
			}
			|	L3PROTOCOL	family_spec_explicit	stmt_separator
			{
				$<obj>0->ct_helper.l3proto = $2;
			}
			;

timeout_states		:	timeout_state
			{
				$$ = xmalloc(sizeof(*$$));
				init_list_head($$);
				list_add_tail($1, $$);
			}
			|	timeout_states	COMMA	timeout_state
			{
				list_add_tail($3, $1);
				$$ = $1;
			}
			;

timeout_state		:	STRING	COLON	NUM

			{
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = $1;
				ts->timeout_value = $3;
				ts->location = @1;
				init_list_head(&ts->head);
				$$ = &ts->head;
			}
			;

ct_timeout_config	:	PROTOCOL	ct_l4protoname	stmt_separator
			{
				struct ct_timeout *ct;
				int l4proto = $2;

				ct = &$<obj>0->ct_timeout;
				ct->l4proto = l4proto;
			}
			|	POLICY 	'=' 	'{' 	timeout_states 	'}'	 stmt_separator
			{
				struct ct_timeout *ct;

				ct = &$<obj>0->ct_timeout;
				list_splice_tail($4, &ct->timeout_list);
				xfree($4);
			}
			|	L3PROTOCOL	family_spec_explicit	stmt_separator
			{
				$<obj>0->ct_timeout.l3proto = $2;
			}
			;

ct_expect_config	:	PROTOCOL	ct_l4protoname	stmt_separator
			{
				$<obj>0->ct_expect.l4proto = $2;
			}
			|	DPORT	NUM	stmt_separator
			{
				$<obj>0->ct_expect.dport = $2;
			}
			|	TIMEOUT	time_spec	stmt_separator
			{
				$<obj>0->ct_expect.timeout = $2;
			}
			|	SIZE	NUM	stmt_separator
			{
				$<obj>0->ct_expect.size = $2;
			}
			|	L3PROTOCOL	family_spec_explicit	stmt_separator
			{
				$<obj>0->ct_expect.l3proto = $2;
			}
			;

ct_obj_alloc		:	/* empty */
			{
				$$ = obj_alloc(&@$);
			}
			;

limit_config		:	RATE	limit_mode	NUM	SLASH	time_unit	limit_burst_pkts
			{
				struct limit *limit;

				limit = &$<obj>0->limit;
				limit->rate	= $3;
				limit->unit	= $5;
				limit->burst	= $6;
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= $2;
			}
			|	RATE	limit_mode	NUM	STRING	limit_burst_bytes
			{
				struct limit *limit;
				struct error_record *erec;
				uint64_t rate, unit;

				erec = rate_parse(&@$, $4, &rate, &unit);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				limit = &$<obj>0->limit;
				limit->rate	= rate * $3;
				limit->unit	= unit;
				limit->burst	= $5;
				limit->type	= NFT_LIMIT_PKT_BYTES;
				limit->flags	= $2;
			}
			;

limit_obj		:	/* empty */
			{
				$$ = obj_alloc(&@$);
				$$->type = NFT_OBJECT_LIMIT;
			}
			;

relational_expr		:	expr	/* implicit */	rhs_expr
			{
				$$ = relational_expr_alloc(&@$, OP_IMPLICIT, $1, $2);
			}
			|	expr	/* implicit */	list_rhs_expr
			{
				$$ = relational_expr_alloc(&@$, OP_IMPLICIT, $1, $2);
			}
			|	expr	relational_op	rhs_expr
			{
				$$ = relational_expr_alloc(&@2, $2, $1, $3);
			}
			;

list_rhs_expr		:	basic_rhs_expr		COMMA		basic_rhs_expr
			{
				$$ = list_expr_alloc(&@$);
				compound_expr_add($$, $1);
				compound_expr_add($$, $3);
			}
			|	list_rhs_expr		COMMA		basic_rhs_expr
			{
				$1->location = @$;
				compound_expr_add($1, $3);
				$$ = $1;
			}
			;

rhs_expr		:	concat_rhs_expr		{ $$ = $1; }
			|	wildcard_expr		{ $$ = $1; }
			|	set_expr		{ $$ = $1; }
			|	set_ref_symbol_expr	{ $$ = $1; }
			;

shift_rhs_expr		:	primary_rhs_expr
			|	shift_rhs_expr		LSHIFT		primary_rhs_expr
			{
				$$ = binop_expr_alloc(&@$, OP_LSHIFT, $1, $3);
			}
			|	shift_rhs_expr		RSHIFT		primary_rhs_expr
			{
				$$ = binop_expr_alloc(&@$, OP_RSHIFT, $1, $3);
			}
			;

and_rhs_expr		:	shift_rhs_expr
			|	and_rhs_expr		AMPERSAND	shift_rhs_expr
			{
				$$ = binop_expr_alloc(&@$, OP_AND, $1, $3);
			}
			;

exclusive_or_rhs_expr	:	and_rhs_expr
			|	exclusive_or_rhs_expr	CARET		and_rhs_expr
			{
				$$ = binop_expr_alloc(&@$, OP_XOR, $1, $3);
			}
			;

inclusive_or_rhs_expr	:	exclusive_or_rhs_expr
			|	inclusive_or_rhs_expr	'|'		exclusive_or_rhs_expr
			{
				$$ = binop_expr_alloc(&@$, OP_OR, $1, $3);
			}
			;

basic_rhs_expr		:	inclusive_or_rhs_expr
			;

concat_rhs_expr		:	basic_rhs_expr
			|	multiton_rhs_expr
			|	concat_rhs_expr		DOT	multiton_rhs_expr
			{
				struct location rhs[] = {
					[1]	= @2,
					[2]	= @3,
				};

				$$ = handle_concat_expr(&@$, $$, $1, $3, rhs);
			}
			|	concat_rhs_expr		DOT	basic_rhs_expr
			{
				struct location rhs[] = {
					[1]	= @2,
					[2]	= @3,
				};

				$$ = handle_concat_expr(&@$, $$, $1, $3, rhs);
			}
			;

boolean_keys		:	EXISTS		{ $$ = true; }
			|	MISSING		{ $$ = false; }
			;

boolean_expr		:	boolean_keys
			{
				$$ = constant_expr_alloc(&@$, &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof($1) * BITS_PER_BYTE, &$1);
			}
			;

keyword_expr		:	ETHER                   { $$ = symbol_value(&@$, "ether"); }
			|	IP			{ $$ = symbol_value(&@$, "ip"); }
			|	IP6			{ $$ = symbol_value(&@$, "ip6"); }
			|	VLAN			{ $$ = symbol_value(&@$, "vlan"); }
			|	ARP			{ $$ = symbol_value(&@$, "arp"); }
			|	DNAT			{ $$ = symbol_value(&@$, "dnat"); }
			|	SNAT			{ $$ = symbol_value(&@$, "snat"); }
			|	ECN			{ $$ = symbol_value(&@$, "ecn"); }
			|	RESET			{ $$ = symbol_value(&@$, "reset"); }
			|	ORIGINAL		{ $$ = symbol_value(&@$, "original"); }
			|	REPLY			{ $$ = symbol_value(&@$, "reply"); }
			|	LABEL			{ $$ = symbol_value(&@$, "label"); }
			;

primary_rhs_expr	:	symbol_expr		{ $$ = $1; }
			|	integer_expr		{ $$ = $1; }
			|	boolean_expr		{ $$ = $1; }
			|	keyword_expr		{ $$ = $1; }
			|	TCP
			{
				uint8_t data = IPPROTO_TCP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	UDP
			{
				uint8_t data = IPPROTO_UDP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	UDPLITE
			{
				uint8_t data = IPPROTO_UDPLITE;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	ESP
			{
				uint8_t data = IPPROTO_ESP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	AH
			{
				uint8_t data = IPPROTO_AH;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	ICMP
			{
				uint8_t data = IPPROTO_ICMP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	IGMP
			{
				uint8_t data = IPPROTO_IGMP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	ICMP6
			{
				uint8_t data = IPPROTO_ICMPV6;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	COMP
			{
				uint8_t data = IPPROTO_COMP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	DCCP
			{
				uint8_t data = IPPROTO_DCCP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	SCTP
			{
				uint8_t data = IPPROTO_SCTP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	REDIRECT
			{
				uint8_t data = ICMP_REDIRECT;
				$$ = constant_expr_alloc(&@$, &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			|	'('	basic_rhs_expr	')'	{ $$ = $2; }
			;

relational_op		:	EQ		{ $$ = OP_EQ; }
			|	NEQ		{ $$ = OP_NEQ; }
			|	LT		{ $$ = OP_LT; }
			|	GT		{ $$ = OP_GT; }
			|	GTE		{ $$ = OP_GTE; }
			|	LTE		{ $$ = OP_LTE; }
			;

verdict_expr		:	ACCEPT
			{
				$$ = verdict_expr_alloc(&@$, NF_ACCEPT, NULL);
			}
			|	DROP
			{
				$$ = verdict_expr_alloc(&@$, NF_DROP, NULL);
			}
			|	CONTINUE
			{
				$$ = verdict_expr_alloc(&@$, NFT_CONTINUE, NULL);
			}
			|	JUMP			chain_expr
			{
				$$ = verdict_expr_alloc(&@$, NFT_JUMP, $2);
			}
			|	GOTO			chain_expr
			{
				$$ = verdict_expr_alloc(&@$, NFT_GOTO, $2);
			}
			|	RETURN
			{
				$$ = verdict_expr_alloc(&@$, NFT_RETURN, NULL);
			}
			;

chain_expr		:	variable_expr
			|	identifier
			{
				$$ = constant_expr_alloc(&@$, &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen($1) * BITS_PER_BYTE,
							 $1);
				xfree($1);
			}
			;

meta_expr		:	META	meta_key
			{
				$$ = meta_expr_alloc(&@$, $2);
			}
			|	meta_key_unqualified
			{
				$$ = meta_expr_alloc(&@$, $1);
			}
			|	META	STRING
			{
				struct error_record *erec;
				unsigned int key;

				erec = meta_key_parse(&@$, $2, &key);
				xfree($2);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				$$ = meta_expr_alloc(&@$, key);
			}
			;

meta_key		:	meta_key_qualified
			|	meta_key_unqualified
			;

meta_key_qualified	:	LENGTH		{ $$ = NFT_META_LEN; }
			|	PROTOCOL	{ $$ = NFT_META_PROTOCOL; }
			|	PRIORITY	{ $$ = NFT_META_PRIORITY; }
			|	RANDOM		{ $$ = NFT_META_PRANDOM; }
			|	SECMARK		{ $$ = NFT_META_SECMARK; }
			;

meta_key_unqualified	:	MARK		{ $$ = NFT_META_MARK; }
			|	IIF		{ $$ = NFT_META_IIF; }
			|	IIFNAME		{ $$ = NFT_META_IIFNAME; }
			|	IIFTYPE		{ $$ = NFT_META_IIFTYPE; }
			|	OIF		{ $$ = NFT_META_OIF; }
			|	OIFNAME		{ $$ = NFT_META_OIFNAME; }
			|	OIFTYPE		{ $$ = NFT_META_OIFTYPE; }
			|	SKUID		{ $$ = NFT_META_SKUID; }
			|	SKGID		{ $$ = NFT_META_SKGID; }
			|	NFTRACE		{ $$ = NFT_META_NFTRACE; }
			|	RTCLASSID	{ $$ = NFT_META_RTCLASSID; }
			|	IBRIPORT	{ $$ = NFT_META_BRI_IIFNAME; }
			|       OBRIPORT	{ $$ = NFT_META_BRI_OIFNAME; }
			|	IBRIDGENAME	{ $$ = NFT_META_BRI_IIFNAME; }
			|       OBRIDGENAME	{ $$ = NFT_META_BRI_OIFNAME; }
			|       PKTTYPE		{ $$ = NFT_META_PKTTYPE; }
			|       CPU		{ $$ = NFT_META_CPU; }
			|       IIFGROUP	{ $$ = NFT_META_IIFGROUP; }
			|       OIFGROUP	{ $$ = NFT_META_OIFGROUP; }
			|       CGROUP		{ $$ = NFT_META_CGROUP; }
			|       IPSEC		{ $$ = NFT_META_SECPATH; }
			|       TIME		{ $$ = NFT_META_TIME_NS; }
			|       DAY		{ $$ = NFT_META_TIME_DAY; }
			|       HOUR		{ $$ = NFT_META_TIME_HOUR; }
			;

meta_stmt		:	META	meta_key	SET	stmt_expr
			{
				switch ($2) {
				case NFT_META_SECMARK:
					switch ($4->etype) {
					case EXPR_CT:
						$$ = meta_stmt_alloc(&@$, $2, $4);
						break;
					default:
						$$ = objref_stmt_alloc(&@$);
						$$->objref.type = NFT_OBJECT_SECMARK;
						$$->objref.expr = $4;
						break;
					}
					break;
				default:
					$$ = meta_stmt_alloc(&@$, $2, $4);
					break;
				}
			}
			|	meta_key_unqualified	SET	stmt_expr
			{
				$$ = meta_stmt_alloc(&@$, $1, $3);
			}
			|	META	STRING	SET	stmt_expr
			{
				struct error_record *erec;
				unsigned int key;

				erec = meta_key_parse(&@$, $2, &key);
				xfree($2);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				$$ = meta_stmt_alloc(&@$, key, $4);
			}
			|	NOTRACK
			{
				$$ = notrack_stmt_alloc(&@$);
			}
			|	FLOW	OFFLOAD	AT string
			{
				$$ = flow_offload_stmt_alloc(&@$, $4);
			}
			|	FLOW	ADD	AT string
			{
				$$ = flow_offload_stmt_alloc(&@$, $4);
			}
			;

socket_expr		:	SOCKET	socket_key
			{
				$$ = socket_expr_alloc(&@$, $2);
			}
			;

socket_key 		: 	TRANSPARENT	{ $$ = NFT_SOCKET_TRANSPARENT; }
			|	MARK		{ $$ = NFT_SOCKET_MARK; }
			|	WILDCARD	{ $$ = NFT_SOCKET_WILDCARD; }
			;

offset_opt		:	/* empty */	{ $$ = 0; }
			|	OFFSET	NUM	{ $$ = $2; }
			;

numgen_type		:	INC		{ $$ = NFT_NG_INCREMENTAL; }
			|	RANDOM		{ $$ = NFT_NG_RANDOM; }
			;

numgen_expr		:	NUMGEN	numgen_type	MOD	NUM	offset_opt
			{
				$$ = numgen_expr_alloc(&@$, $2, $4, $5);
			}
			;

xfrm_spnum		:	SPNUM	NUM { $$ = $2; }
			|		    { $$ = 0; }
			;

xfrm_dir		:	IN	{ $$ = XFRM_POLICY_IN; }
			|	OUT	{ $$ = XFRM_POLICY_OUT; }
			;

xfrm_state_key		:	SPI { $$ = NFT_XFRM_KEY_SPI; }
			|	REQID { $$ = NFT_XFRM_KEY_REQID; }
			;

xfrm_state_proto_key	:	DADDR		{ $$ = NFT_XFRM_KEY_DADDR_IP4; }
			|	SADDR		{ $$ = NFT_XFRM_KEY_SADDR_IP4; }
			;

xfrm_expr		:	IPSEC	xfrm_dir	xfrm_spnum	xfrm_state_key
			{
				if ($3 > 255) {
					erec_queue(error(&@3, "value too large"), state->msgs);
					YYERROR;
				}
				$$ = xfrm_expr_alloc(&@$, $2, $3, $4);
			}
			|	IPSEC	xfrm_dir	xfrm_spnum	nf_key_proto	xfrm_state_proto_key
			{
				enum nft_xfrm_keys xfrmk = $5;

				switch ($4) {
				case NFPROTO_IPV4:
					break;
				case NFPROTO_IPV6:
					if ($5 == NFT_XFRM_KEY_SADDR_IP4)
						xfrmk = NFT_XFRM_KEY_SADDR_IP6;
					else if ($5 == NFT_XFRM_KEY_DADDR_IP4)
						xfrmk = NFT_XFRM_KEY_DADDR_IP6;
					break;
				default:
					YYERROR;
					break;
				}

				if ($3 > 255) {
					erec_queue(error(&@3, "value too large"), state->msgs);
					YYERROR;
				}

				$$ = xfrm_expr_alloc(&@$, $2, $3, xfrmk);
			}
			;

hash_expr		:	JHASH		expr	MOD	NUM	SEED	NUM	offset_opt
			{
				$$ = hash_expr_alloc(&@$, $4, true, $6, $7, NFT_HASH_JENKINS);
				$$->hash.expr = $2;
			}
			|	JHASH		expr	MOD	NUM	offset_opt
			{
				$$ = hash_expr_alloc(&@$, $4, false, 0, $5, NFT_HASH_JENKINS);
				$$->hash.expr = $2;
			}
			|	SYMHASH		MOD	NUM	offset_opt
			{
				$$ = hash_expr_alloc(&@$, $3, false, 0, $4, NFT_HASH_SYM);
			}
			;

nf_key_proto		:	IP		{ $$ = NFPROTO_IPV4; }
			|	IP6		{ $$ = NFPROTO_IPV6; }
			;

rt_expr			:	RT	rt_key
			{
				$$ = rt_expr_alloc(&@$, $2, true);
			}
			|	RT	nf_key_proto	rt_key
			{
				enum nft_rt_keys rtk = $3;

				switch ($2) {
				case NFPROTO_IPV4:
					break;
				case NFPROTO_IPV6:
					if ($3 == NFT_RT_NEXTHOP4)
						rtk = NFT_RT_NEXTHOP6;
					break;
				default:
					YYERROR;
					break;
				}

				$$ = rt_expr_alloc(&@$, rtk, false);
			}
			;

rt_key			:	CLASSID		{ $$ = NFT_RT_CLASSID; }
			|	NEXTHOP		{ $$ = NFT_RT_NEXTHOP4; }
			|	MTU		{ $$ = NFT_RT_TCPMSS; }
			|	IPSEC		{ $$ = NFT_RT_XFRM; }
			;

ct_expr			: 	CT	ct_key
			{
				$$ = ct_expr_alloc(&@$, $2, -1);
			}
			|	CT	ct_dir	ct_key_dir
			{
				$$ = ct_expr_alloc(&@$, $3, $2);
			}
			|	CT	ct_dir	ct_key_proto_field
			{
				$$ = ct_expr_alloc(&@$, $3, $2);
			}
			;

ct_dir			:	ORIGINAL	{ $$ = IP_CT_DIR_ORIGINAL; }
			|	REPLY		{ $$ = IP_CT_DIR_REPLY; }
			;

ct_key			:	L3PROTOCOL	{ $$ = NFT_CT_L3PROTOCOL; }
			|	PROTOCOL	{ $$ = NFT_CT_PROTOCOL; }
			|	MARK		{ $$ = NFT_CT_MARK; }
			|	STATE		{ $$ = NFT_CT_STATE; }
			|	DIRECTION	{ $$ = NFT_CT_DIRECTION; }
			|	STATUS		{ $$ = NFT_CT_STATUS; }
			|	EXPIRATION	{ $$ = NFT_CT_EXPIRATION; }
			|	HELPER		{ $$ = NFT_CT_HELPER; }
			|	SADDR		{ $$ = NFT_CT_SRC; }
			|	DADDR		{ $$ = NFT_CT_DST; }
			|	PROTO_SRC	{ $$ = NFT_CT_PROTO_SRC; }
			|	PROTO_DST	{ $$ = NFT_CT_PROTO_DST; }
			|	LABEL		{ $$ = NFT_CT_LABELS; }
			|	EVENT		{ $$ = NFT_CT_EVENTMASK; }
			|	SECMARK		{ $$ = NFT_CT_SECMARK; }
			|	ID	 	{ $$ = NFT_CT_ID; }
			|	ct_key_dir_optional
			;

ct_key_dir		:	SADDR		{ $$ = NFT_CT_SRC; }
			|	DADDR		{ $$ = NFT_CT_DST; }
			|	L3PROTOCOL	{ $$ = NFT_CT_L3PROTOCOL; }
			|	PROTOCOL	{ $$ = NFT_CT_PROTOCOL; }
			|	PROTO_SRC	{ $$ = NFT_CT_PROTO_SRC; }
			|	PROTO_DST	{ $$ = NFT_CT_PROTO_DST; }
			|	ct_key_dir_optional
			;

ct_key_proto_field	:	IP	SADDR	{ $$ = NFT_CT_SRC_IP; }
			|	IP	DADDR	{ $$ = NFT_CT_DST_IP; }
			|	IP6	SADDR	{ $$ = NFT_CT_SRC_IP6; }
			|	IP6	DADDR	{ $$ = NFT_CT_DST_IP6; }
			;

ct_key_dir_optional	:	BYTES		{ $$ = NFT_CT_BYTES; }
			|	PACKETS		{ $$ = NFT_CT_PKTS; }
			|	AVGPKT		{ $$ = NFT_CT_AVGPKT; }
			|	ZONE		{ $$ = NFT_CT_ZONE; }
			;

symbol_stmt_expr		:	symbol_expr
			|	keyword_expr
			;

list_stmt_expr		:	symbol_stmt_expr	COMMA	symbol_stmt_expr
			{
				$$ = list_expr_alloc(&@$);
				compound_expr_add($$, $1);
				compound_expr_add($$, $3);
			}
			|	list_stmt_expr	COMMA	symbol_stmt_expr
			{
				$1->location = @$;
				compound_expr_add($1, $3);
				$$ = $1;
			}
			;

ct_stmt			:	CT	ct_key		SET	stmt_expr
			{
				switch ($2) {
				case NFT_CT_HELPER:
					$$ = objref_stmt_alloc(&@$);
					$$->objref.type = NFT_OBJECT_CT_HELPER;
					$$->objref.expr = $4;
					break;
				default:
					$$ = ct_stmt_alloc(&@$, $2, -1, $4);
					break;
				}
			}
			|	CT	TIMEOUT		SET	stmt_expr
			{
				$$ = objref_stmt_alloc(&@$);
				$$->objref.type = NFT_OBJECT_CT_TIMEOUT;
				$$->objref.expr = $4;

			}
			|	CT	EXPECTATION	SET	stmt_expr
			{
				$$ = objref_stmt_alloc(&@$);
				$$->objref.type = NFT_OBJECT_CT_EXPECT;
				$$->objref.expr = $4;
			}
			|	CT	ct_dir	ct_key_dir_optional SET	stmt_expr
			{
				$$ = ct_stmt_alloc(&@$, $3, $2, $5);
			}
			;

payload_stmt		:	payload_expr		SET	stmt_expr
			{
				if ($1->etype == EXPR_EXTHDR)
					$$ = exthdr_stmt_alloc(&@$, $1, $3);
				else
					$$ = payload_stmt_alloc(&@$, $1, $3);
			}
			;

payload_expr		:	payload_raw_expr
			|	eth_hdr_expr
			|	vlan_hdr_expr
			|	arp_hdr_expr
			|	ip_hdr_expr
			|	icmp_hdr_expr
			|	igmp_hdr_expr
			|	ip6_hdr_expr
			|	icmp6_hdr_expr
			|	auth_hdr_expr
			|	esp_hdr_expr
			|	comp_hdr_expr
			|	udp_hdr_expr
			|	udplite_hdr_expr
			|	tcp_hdr_expr
			|	dccp_hdr_expr
			|	sctp_hdr_expr
			|	th_hdr_expr
			;

payload_raw_expr	:	AT	payload_base_spec	COMMA	NUM	COMMA	NUM
			{
				$$ = payload_expr_alloc(&@$, NULL, 0);
				payload_init_raw($$, $2, $4, $6);
				$$->byteorder		= BYTEORDER_BIG_ENDIAN;
				$$->payload.is_raw	= true;
			}
			;

payload_base_spec	:	LL_HDR		{ $$ = PROTO_BASE_LL_HDR; }
			|	NETWORK_HDR	{ $$ = PROTO_BASE_NETWORK_HDR; }
			|	TRANSPORT_HDR	{ $$ = PROTO_BASE_TRANSPORT_HDR; }
			;

eth_hdr_expr		:	ETHER	eth_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_eth, $2);
			}
			;

eth_hdr_field		:	SADDR		{ $$ = ETHHDR_SADDR; }
			|	DADDR		{ $$ = ETHHDR_DADDR; }
			|	TYPE		{ $$ = ETHHDR_TYPE; }
			;

vlan_hdr_expr		:	VLAN	vlan_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_vlan, $2);
			}
			;

vlan_hdr_field		:	ID		{ $$ = VLANHDR_VID; }
			|	CFI		{ $$ = VLANHDR_CFI; }
			|	PCP		{ $$ = VLANHDR_PCP; }
			|	TYPE		{ $$ = VLANHDR_TYPE; }
			;

arp_hdr_expr		:	ARP	arp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_arp, $2);
			}
			;

arp_hdr_field		:	HTYPE		{ $$ = ARPHDR_HRD; }
			|	PTYPE		{ $$ = ARPHDR_PRO; }
			|	HLEN		{ $$ = ARPHDR_HLN; }
			|	PLEN		{ $$ = ARPHDR_PLN; }
			|	OPERATION	{ $$ = ARPHDR_OP; }
			|	SADDR ETHER	{ $$ = ARPHDR_SADDR_ETHER; }
			|	DADDR ETHER	{ $$ = ARPHDR_DADDR_ETHER; }
			|	SADDR IP	{ $$ = ARPHDR_SADDR_IP; }
			|	DADDR IP	{ $$ = ARPHDR_DADDR_IP; }
			;

ip_hdr_expr		:	IP	ip_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_ip, $2);
			}
			|	IP	OPTION	ip_option_type ip_option_field
			{
				$$ = ipopt_expr_alloc(&@$, $3, $4, 0);
			}
			|	IP	OPTION	ip_option_type
			{
				$$ = ipopt_expr_alloc(&@$, $3, IPOPT_FIELD_TYPE, 0);
				$$->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
			;

ip_hdr_field		:	HDRVERSION	{ $$ = IPHDR_VERSION; }
			|	HDRLENGTH	{ $$ = IPHDR_HDRLENGTH; }
			|	DSCP		{ $$ = IPHDR_DSCP; }
			|	ECN		{ $$ = IPHDR_ECN; }
			|	LENGTH		{ $$ = IPHDR_LENGTH; }
			|	ID		{ $$ = IPHDR_ID; }
			|	FRAG_OFF	{ $$ = IPHDR_FRAG_OFF; }
			|	TTL		{ $$ = IPHDR_TTL; }
			|	PROTOCOL	{ $$ = IPHDR_PROTOCOL; }
			|	CHECKSUM	{ $$ = IPHDR_CHECKSUM; }
			|	SADDR		{ $$ = IPHDR_SADDR; }
			|	DADDR		{ $$ = IPHDR_DADDR; }
			;

ip_option_type		:	LSRR		{ $$ = IPOPT_LSRR; }
			|	RR		{ $$ = IPOPT_RR; }
			|	SSRR		{ $$ = IPOPT_SSRR; }
			|	RA		{ $$ = IPOPT_RA; }
			;

ip_option_field		:	TYPE		{ $$ = IPOPT_FIELD_TYPE; }
			|	LENGTH		{ $$ = IPOPT_FIELD_LENGTH; }
			|	VALUE		{ $$ = IPOPT_FIELD_VALUE; }
			|	PTR		{ $$ = IPOPT_FIELD_PTR; }
			|	ADDR		{ $$ = IPOPT_FIELD_ADDR_0; }
			;

icmp_hdr_expr		:	ICMP	icmp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_icmp, $2);
			}
			;

icmp_hdr_field		:	TYPE		{ $$ = ICMPHDR_TYPE; }
			|	CODE		{ $$ = ICMPHDR_CODE; }
			|	CHECKSUM	{ $$ = ICMPHDR_CHECKSUM; }
			|	ID		{ $$ = ICMPHDR_ID; }
			|	SEQUENCE	{ $$ = ICMPHDR_SEQ; }
			|	GATEWAY		{ $$ = ICMPHDR_GATEWAY; }
			|	MTU		{ $$ = ICMPHDR_MTU; }
			;

igmp_hdr_expr		:	IGMP	igmp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_igmp, $2);
			}
			;

igmp_hdr_field		:	TYPE		{ $$ = IGMPHDR_TYPE; }
			|	CHECKSUM	{ $$ = IGMPHDR_CHECKSUM; }
			|	MRT		{ $$ = IGMPHDR_MRT; }
			|	GROUP		{ $$ = IGMPHDR_GROUP; }
			;

ip6_hdr_expr		:	IP6	ip6_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_ip6, $2);
			}
			;

ip6_hdr_field		:	HDRVERSION	{ $$ = IP6HDR_VERSION; }
			|	DSCP		{ $$ = IP6HDR_DSCP; }
			|	ECN		{ $$ = IP6HDR_ECN; }
			|	FLOWLABEL	{ $$ = IP6HDR_FLOWLABEL; }
			|	LENGTH		{ $$ = IP6HDR_LENGTH; }
			|	NEXTHDR		{ $$ = IP6HDR_NEXTHDR; }
			|	HOPLIMIT	{ $$ = IP6HDR_HOPLIMIT; }
			|	SADDR		{ $$ = IP6HDR_SADDR; }
			|	DADDR		{ $$ = IP6HDR_DADDR; }
			;
icmp6_hdr_expr		:	ICMP6	icmp6_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_icmp6, $2);
			}
			;

icmp6_hdr_field		:	TYPE		{ $$ = ICMP6HDR_TYPE; }
			|	CODE		{ $$ = ICMP6HDR_CODE; }
			|	CHECKSUM	{ $$ = ICMP6HDR_CHECKSUM; }
			|	PPTR		{ $$ = ICMP6HDR_PPTR; }
			|	MTU		{ $$ = ICMP6HDR_MTU; }
			|	ID		{ $$ = ICMP6HDR_ID; }
			|	SEQUENCE	{ $$ = ICMP6HDR_SEQ; }
			|	MAXDELAY	{ $$ = ICMP6HDR_MAXDELAY; }
			;

auth_hdr_expr		:	AH	auth_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_ah, $2);
			}
			;

auth_hdr_field		:	NEXTHDR		{ $$ = AHHDR_NEXTHDR; }
			|	HDRLENGTH	{ $$ = AHHDR_HDRLENGTH; }
			|	RESERVED	{ $$ = AHHDR_RESERVED; }
			|	SPI		{ $$ = AHHDR_SPI; }
			|	SEQUENCE	{ $$ = AHHDR_SEQUENCE; }
			;

esp_hdr_expr		:	ESP	esp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_esp, $2);
			}
			;

esp_hdr_field		:	SPI		{ $$ = ESPHDR_SPI; }
			|	SEQUENCE	{ $$ = ESPHDR_SEQUENCE; }
			;

comp_hdr_expr		:	COMP	comp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_comp, $2);
			}
			;

comp_hdr_field		:	NEXTHDR		{ $$ = COMPHDR_NEXTHDR; }
			|	FLAGS		{ $$ = COMPHDR_FLAGS; }
			|	CPI		{ $$ = COMPHDR_CPI; }
			;

udp_hdr_expr		:	UDP	udp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_udp, $2);
			}
			;

udp_hdr_field		:	SPORT		{ $$ = UDPHDR_SPORT; }
			|	DPORT		{ $$ = UDPHDR_DPORT; }
			|	LENGTH		{ $$ = UDPHDR_LENGTH; }
			|	CHECKSUM	{ $$ = UDPHDR_CHECKSUM; }
			;

udplite_hdr_expr	:	UDPLITE	udplite_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_udplite, $2);
			}
			;

udplite_hdr_field	:	SPORT		{ $$ = UDPHDR_SPORT; }
			|	DPORT		{ $$ = UDPHDR_DPORT; }
			|	CSUMCOV		{ $$ = UDPHDR_LENGTH; }
			|	CHECKSUM	{ $$ = UDPHDR_CHECKSUM; }
			;

tcp_hdr_expr		:	TCP	tcp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_tcp, $2);
			}
			|	TCP	OPTION	tcp_hdr_option_type tcp_hdr_option_field
			{
				$$ = tcpopt_expr_alloc(&@$, $3, $4);
			}
			|	TCP	OPTION	tcp_hdr_option_type
			{
				$$ = tcpopt_expr_alloc(&@$, $3, TCPOPT_COMMON_KIND);
				$$->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
			|	TCP	OPTION	AT tcp_hdr_option_type	COMMA	NUM	COMMA	NUM
			{
				$$ = tcpopt_expr_alloc(&@$, $4, 0);
				tcpopt_init_raw($$, $4, $6, $8, 0);
			}
			;

tcp_hdr_field		:	SPORT		{ $$ = TCPHDR_SPORT; }
			|	DPORT		{ $$ = TCPHDR_DPORT; }
			|	SEQUENCE	{ $$ = TCPHDR_SEQ; }
			|	ACKSEQ		{ $$ = TCPHDR_ACKSEQ; }
			|	DOFF		{ $$ = TCPHDR_DOFF; }
			|	RESERVED	{ $$ = TCPHDR_RESERVED; }
			|	FLAGS		{ $$ = TCPHDR_FLAGS; }
			|	WINDOW		{ $$ = TCPHDR_WINDOW; }
			|	CHECKSUM	{ $$ = TCPHDR_CHECKSUM; }
			|	URGPTR		{ $$ = TCPHDR_URGPTR; }
			;

tcp_hdr_option_type	:	EOL		{ $$ = TCPOPT_KIND_EOL; }
			|	NOP		{ $$ = TCPOPT_KIND_NOP; }
			|	MSS  	  	{ $$ = TCPOPT_KIND_MAXSEG; }
			|	WINDOW		{ $$ = TCPOPT_KIND_WINDOW; }
			|	SACK_PERM	{ $$ = TCPOPT_KIND_SACK_PERMITTED; }
			|	SACK		{ $$ = TCPOPT_KIND_SACK; }
			|	SACK0		{ $$ = TCPOPT_KIND_SACK; }
			|	SACK1		{ $$ = TCPOPT_KIND_SACK1; }
			|	SACK2		{ $$ = TCPOPT_KIND_SACK2; }
			|	SACK3		{ $$ = TCPOPT_KIND_SACK3; }
			|	ECHO		{ $$ = TCPOPT_KIND_ECHO; }
			|	TIMESTAMP	{ $$ = TCPOPT_KIND_TIMESTAMP; }
			|	NUM		{
				if ($1 > 255) {
					erec_queue(error(&@1, "value too large"), state->msgs);
					YYERROR;
				}
				$$ = $1;
			}
			;

tcp_hdr_option_field	:	KIND		{ $$ = TCPOPT_COMMON_KIND; }
			|	LENGTH		{ $$ = TCPOPT_COMMON_LENGTH; }
			|	SIZE		{ $$ = TCPOPT_MAXSEG_SIZE; }
			|	COUNT		{ $$ = TCPOPT_WINDOW_COUNT; }
			|	LEFT		{ $$ = TCPOPT_SACK_LEFT; }
			|	RIGHT		{ $$ = TCPOPT_SACK_RIGHT; }
			|	TSVAL		{ $$ = TCPOPT_TS_TSVAL; }
			|	TSECR		{ $$ = TCPOPT_TS_TSECR; }
			;

dccp_hdr_expr		:	DCCP	dccp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_dccp, $2);
			}
			;

dccp_hdr_field		:	SPORT		{ $$ = DCCPHDR_SPORT; }
			|	DPORT		{ $$ = DCCPHDR_DPORT; }
			|	TYPE		{ $$ = DCCPHDR_TYPE; }
			;

sctp_hdr_expr		:	SCTP	sctp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_sctp, $2);
			}
			;

sctp_hdr_field		:	SPORT		{ $$ = SCTPHDR_SPORT; }
			|	DPORT		{ $$ = SCTPHDR_DPORT; }
			|	VTAG		{ $$ = SCTPHDR_VTAG; }
			|	CHECKSUM	{ $$ = SCTPHDR_CHECKSUM; }
			;

th_hdr_expr		:	TRANSPORT_HDR 	th_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_th, $2);
				if ($$)
					$$->payload.is_raw = true;
			}
			;

th_hdr_field		:	SPORT		{ $$ = THDR_SPORT; }
			|	DPORT		{ $$ = THDR_DPORT; }
			;

exthdr_expr		:	hbh_hdr_expr
			|	rt_hdr_expr
			|	rt0_hdr_expr
			|	rt2_hdr_expr
			|	rt4_hdr_expr
			|	frag_hdr_expr
			|	dst_hdr_expr
			|	mh_hdr_expr
			;

hbh_hdr_expr		:	HBH	hbh_hdr_field
			{
				$$ = exthdr_expr_alloc(&@$, &exthdr_hbh, $2);
			}
			;

hbh_hdr_field		:	NEXTHDR		{ $$ = HBHHDR_NEXTHDR; }
			|	HDRLENGTH	{ $$ = HBHHDR_HDRLENGTH; }
			;

rt_hdr_expr		:	RT	rt_hdr_field
			{
				$$ = exthdr_expr_alloc(&@$, &exthdr_rt, $2);
			}
			;

rt_hdr_field		:	NEXTHDR		{ $$ = RTHDR_NEXTHDR; }
			|	HDRLENGTH	{ $$ = RTHDR_HDRLENGTH; }
			|	TYPE		{ $$ = RTHDR_TYPE; }
			|	SEG_LEFT	{ $$ = RTHDR_SEG_LEFT; }
			;

rt0_hdr_expr		:	RT0	rt0_hdr_field
			{
				$$ = exthdr_expr_alloc(&@$, &exthdr_rt0, $2);
			}
			;

rt0_hdr_field		:	ADDR	'['	NUM	']'
			{
				$$ = RT0HDR_ADDR_1 + $3 - 1;
			}
			;

rt2_hdr_expr		:	RT2	rt2_hdr_field
			{
				$$ = exthdr_expr_alloc(&@$, &exthdr_rt2, $2);
			}
			;

rt2_hdr_field		:	ADDR		{ $$ = RT2HDR_ADDR; }
			;

rt4_hdr_expr		:	RT4	rt4_hdr_field
			{
				$$ = exthdr_expr_alloc(&@$, &exthdr_rt4, $2);
			}
			;

rt4_hdr_field		:	LAST_ENT	{ $$ = RT4HDR_LASTENT; }
			|	FLAGS		{ $$ = RT4HDR_FLAGS; }
			|	TAG		{ $$ = RT4HDR_TAG; }
			|	SID		'['	NUM	']'
			{
				$$ = RT4HDR_SID_1 + $3 - 1;
			}
			;

frag_hdr_expr		:	FRAG	frag_hdr_field
			{
				$$ = exthdr_expr_alloc(&@$, &exthdr_frag, $2);
			}
			;

frag_hdr_field		:	NEXTHDR		{ $$ = FRAGHDR_NEXTHDR; }
			|	RESERVED	{ $$ = FRAGHDR_RESERVED; }
			|	FRAG_OFF	{ $$ = FRAGHDR_FRAG_OFF; }
			|	RESERVED2	{ $$ = FRAGHDR_RESERVED2; }
			|	MORE_FRAGMENTS	{ $$ = FRAGHDR_MFRAGS; }
			|	ID		{ $$ = FRAGHDR_ID; }
			;

dst_hdr_expr		:	DST	dst_hdr_field
			{
				$$ = exthdr_expr_alloc(&@$, &exthdr_dst, $2);
			}
			;

dst_hdr_field		:	NEXTHDR		{ $$ = DSTHDR_NEXTHDR; }
			|	HDRLENGTH	{ $$ = DSTHDR_HDRLENGTH; }
			;

mh_hdr_expr		:	MH	mh_hdr_field
			{
				$$ = exthdr_expr_alloc(&@$, &exthdr_mh, $2);
			}
			;

mh_hdr_field		:	NEXTHDR		{ $$ = MHHDR_NEXTHDR; }
			|	HDRLENGTH	{ $$ = MHHDR_HDRLENGTH; }
			|	TYPE		{ $$ = MHHDR_TYPE; }
			|	RESERVED	{ $$ = MHHDR_RESERVED; }
			|	CHECKSUM	{ $$ = MHHDR_CHECKSUM; }
			;

exthdr_exists_expr	:	EXTHDR	exthdr_key
			{
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto($2);

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				$$ = exthdr_expr_alloc(&@$, desc, 1);
				$$->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
			;

exthdr_key		:	HBH	{ $$ = IPPROTO_HOPOPTS; }
			|	RT	{ $$ = IPPROTO_ROUTING; }
			|	FRAG	{ $$ = IPPROTO_FRAGMENT; }
			|	DST	{ $$ = IPPROTO_DSTOPTS; }
			|	MH	{ $$ = IPPROTO_MH; }
			;

%%
