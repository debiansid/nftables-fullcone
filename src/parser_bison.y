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
#include <netinet/if_ether.h>
#include <linux/netfilter.h>
#include <linux/netfilter/nf_tables.h>
#include <linux/netfilter/nf_conntrack_tuple_common.h>
#include <linux/netfilter/nf_nat.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <libnftnl/common.h>
#include <libnftnl/set.h>

#include <rule.h>
#include <statement.h>
#include <expression.h>
#include <utils.h>
#include <parser.h>
#include <erec.h>

#include "parser_bison.h"

void parser_init(struct parser_state *state, struct list_head *msgs)
{
	memset(state, 0, sizeof(*state));
	init_list_head(&state->cmds);
	init_list_head(&state->top_scope.symbols);
	state->msgs = msgs;
	state->scopes[0] = scope_init(&state->top_scope, NULL);
	state->ectx.msgs = msgs;
}

static void yyerror(struct location *loc, void *scanner,
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

#define YYLLOC_DEFAULT(Current, Rhs, N)	location_update(&Current, Rhs, N)

%}

/* Declaration section */

%name-prefix "nft_"
%debug
%pure-parser
%parse-param		{ void *scanner }
%parse-param		{ struct parser_state *state }
%lex-param		{ scanner }
%error-verbose
%locations

%initial-action {
	location_init(scanner, state, &yylloc);
#ifdef DEBUG
	if (debug_level & DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (debug_level & DEBUG_PARSER)
		yydebug = 1;
#endif
}

%union {
	uint64_t		val;
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

%token INCLUDE			"include"
%token DEFINE			"define"

%token HOOK			"hook"
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
%token HANDLE			"handle"
%token RULESET			"ruleset"

%token INET			"inet"

%token ADD			"add"
%token CREATE			"create"
%token INSERT			"insert"
%token DELETE			"delete"
%token LIST			"list"
%token FLUSH			"flush"
%token RENAME			"rename"
%token DESCRIBE			"describe"
%token EXPORT			"export"
%token MONITOR			"monitor"

%token ACCEPT			"accept"
%token DROP			"drop"
%token CONTINUE			"continue"
%token JUMP			"jump"
%token GOTO			"goto"
%token RETURN			"return"
%token TO			"to"

%token CONSTANT			"constant"
%token INTERVAL			"interval"
%token ELEMENTS			"elements"

%token POLICY			"policy"
%token MEMORY			"memory"
%token PERFORMANCE		"performance"
%token SIZE			"size"

%token <val> NUM		"number"
%token <string> STRING		"string"
%token <string> QUOTED_STRING
%token <string> ERROR		"error"
%destructor { xfree($$); }	STRING QUOTED_STRING ERROR

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
%token VERSION			"version"
%token HDRLENGTH		"hdrlength"
%token TOS			"tos"
%token LENGTH			"length"
%token FRAG_OFF			"frag-off"
%token TTL			"ttl"
%token PROTOCOL			"protocol"
%token CHECKSUM			"checksum"

%token ICMP			"icmp"
%token CODE			"code"
%token SEQUENCE			"seq"
%token GATEWAY			"gateway"
%token MTU			"mtu"

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

%token DCCP			"dccp"

%token SCTP			"sctp"
%token VTAG			"vtag"

%token RT			"rt"
%token RT0			"rt0"
%token RT2			"rt2"
%token SEG_LEFT			"seg-left"
%token ADDR			"addr"

%token HBH			"hbh"

%token FRAG			"frag"
%token RESERVED2		"reserved2"
%token MORE_FRAGMENTS		"more-fragments"

%token DST			"dst"

%token MH			"mh"

%token META			"meta"
%token NFPROTO			"nfproto"
%token L4PROTO			"l4proto"
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
%token PKTTYPE			"pkttype"
%token CPU			"cpu"
%token IIFGROUP			"iifgroup"
%token OIFGROUP			"oifgroup"
%token CGROUP			"cgroup"

%token CT			"ct"
%token DIRECTION		"direction"
%token STATE			"state"
%token STATUS			"status"
%token EXPIRATION		"expiration"
%token HELPER			"helper"
%token L3PROTOCOL		"l3proto"
%token PROTO_SRC		"proto-src"
%token PROTO_DST		"proto-dst"
%token LABEL			"label"

%token COUNTER			"counter"
%token PACKETS			"packets"
%token BYTES			"bytes"

%token LOG			"log"
%token PREFIX			"prefix"
%token GROUP			"group"
%token SNAPLEN			"snaplen"
%token QUEUE_THRESHOLD		"queue-threshold"
%token LEVEL			"level"
%token LEVEL_EMERG		"emerg"
%token LEVEL_ALERT		"alert"
%token LEVEL_CRIT		"crit"
%token LEVEL_ERR		"err"
%token LEVEL_WARN		"warn"
%token LEVEL_NOTICE		"notice"
%token LEVEL_INFO		"info"
%token LEVEL_DEBUG		"debug"

%token LIMIT			"limit"
%token RATE			"rate"

%token NANOSECOND		"nanosecond"
%token MICROSECOND		"microsecond"
%token MILLISECOND		"millisecond"
%token SECOND			"second"
%token MINUTE			"minute"
%token HOUR			"hour"
%token DAY			"day"
%token WEEK			"week"

%token _REJECT			"reject"
%token RESET			"reset"
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

%token POSITION			"position"
%token COMMENT			"comment"

%token XML			"xml"
%token JSON			"json"

%type <string>			identifier string comment_spec
%destructor { xfree($$); }	identifier string comment_spec

%type <cmd>			line
%destructor { cmd_free($$); }	line

%type <cmd>			base_cmd add_cmd create_cmd insert_cmd delete_cmd list_cmd flush_cmd rename_cmd export_cmd monitor_cmd describe_cmd
%destructor { cmd_free($$); }	base_cmd add_cmd create_cmd insert_cmd delete_cmd list_cmd flush_cmd rename_cmd export_cmd monitor_cmd describe_cmd

%type <handle>			table_spec tables_spec chain_spec chain_identifier ruleid_spec ruleset_spec
%destructor { handle_free(&$$); } table_spec tables_spec chain_spec chain_identifier ruleid_spec ruleset_spec
%type <handle>			set_spec set_identifier
%destructor { handle_free(&$$); } set_spec set_identifier
%type <val>			handle_spec family_spec family_spec_explicit position_spec

%type <table>			table_block_alloc table_block
%destructor { close_scope(state); table_free($$); }	table_block_alloc
%type <chain>			chain_block_alloc chain_block
%destructor { close_scope(state); chain_free($$); }	chain_block_alloc
%type <rule>			rule
%destructor { rule_free($$); }	rule

%type <val>			set_flag_list	set_flag

%type <val>			set_policy_spec

%type <set>			set_block_alloc set_block
%destructor { set_free($$); }	set_block_alloc

%type <set>			map_block_alloc map_block
%destructor { set_free($$); }	map_block_alloc

%type <list>			stmt_list
%destructor { stmt_list_free($$); xfree($$); } stmt_list
%type <stmt>			stmt match_stmt verdict_stmt
%destructor { stmt_free($$); }	stmt match_stmt verdict_stmt
%type <stmt>			counter_stmt counter_stmt_alloc
%destructor { stmt_free($$); }	counter_stmt counter_stmt_alloc
%type <stmt>			ct_stmt
%destructor { stmt_free($$); }	ct_stmt
%type <stmt>			meta_stmt
%destructor { stmt_free($$); }	meta_stmt
%type <stmt>			log_stmt log_stmt_alloc
%destructor { stmt_free($$); }	log_stmt log_stmt_alloc
%type <val>			level_type
%type <stmt>			limit_stmt
%destructor { stmt_free($$); }	limit_stmt
%type <val>			time_unit
%type <stmt>			reject_stmt reject_stmt_alloc
%destructor { stmt_free($$); }	reject_stmt reject_stmt_alloc
%type <stmt>			nat_stmt nat_stmt_alloc masq_stmt masq_stmt_alloc redir_stmt redir_stmt_alloc
%destructor { stmt_free($$); }	nat_stmt nat_stmt_alloc masq_stmt masq_stmt_alloc redir_stmt redir_stmt_alloc
%type <val>			nf_nat_flags nf_nat_flag
%type <stmt>			queue_stmt queue_stmt_alloc
%destructor { stmt_free($$); }	queue_stmt queue_stmt_alloc
%type <val>			queue_stmt_flags queue_stmt_flag

%type <expr>			symbol_expr verdict_expr integer_expr
%destructor { expr_free($$); }	symbol_expr verdict_expr integer_expr
%type <expr>			primary_expr shift_expr and_expr
%destructor { expr_free($$); }	primary_expr shift_expr and_expr
%type <expr>			exclusive_or_expr inclusive_or_expr
%destructor { expr_free($$); }	exclusive_or_expr inclusive_or_expr
%type <expr>			basic_expr
%destructor { expr_free($$); }	basic_expr

%type <expr>			multiton_expr
%destructor { expr_free($$); }	multiton_expr
%type <expr>			prefix_expr range_expr wildcard_expr
%destructor { expr_free($$); }	prefix_expr range_expr wildcard_expr
%type <expr>			list_expr
%destructor { expr_free($$); }	list_expr
%type <expr>			concat_expr map_lhs_expr
%destructor { expr_free($$); }	concat_expr map_lhs_expr
%type <expr>			error_expr
%destructor { expr_free($$); }	error_expr

%type <expr>			map_expr
%destructor { expr_free($$); }	map_expr

%type <expr>			verdict_map_stmt
%destructor { expr_free($$); }	verdict_map_stmt

%type <expr>			verdict_map_expr verdict_map_list_expr verdict_map_list_member_expr
%destructor { expr_free($$); }	verdict_map_expr verdict_map_list_expr verdict_map_list_member_expr

%type <expr>			set_expr set_list_expr set_list_member_expr
%destructor { expr_free($$); }	set_expr set_list_expr set_list_member_expr

%type <expr>			expr initializer_expr
%destructor { expr_free($$); }	expr initializer_expr

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
%type <expr>			ip_hdr_expr	icmp_hdr_expr
%destructor { expr_free($$); }	ip_hdr_expr	icmp_hdr_expr
%type <val>			ip_hdr_field	icmp_hdr_field
%type <expr>			ip6_hdr_expr    icmp6_hdr_expr
%destructor { expr_free($$); }	ip6_hdr_expr	icmp6_hdr_expr
%type <val>			ip6_hdr_field   icmp6_hdr_field
%type <expr>			auth_hdr_expr	esp_hdr_expr		comp_hdr_expr
%destructor { expr_free($$); }	auth_hdr_expr	esp_hdr_expr		comp_hdr_expr
%type <val>			auth_hdr_field	esp_hdr_field		comp_hdr_field
%type <expr>			udp_hdr_expr	udplite_hdr_expr	tcp_hdr_expr
%destructor { expr_free($$); }	udp_hdr_expr	udplite_hdr_expr	tcp_hdr_expr
%type <val>			udp_hdr_field	udplite_hdr_field	tcp_hdr_field
%type <expr>			dccp_hdr_expr	sctp_hdr_expr
%destructor { expr_free($$); }	dccp_hdr_expr	sctp_hdr_expr
%type <val>			dccp_hdr_field	sctp_hdr_field

%type <expr>			exthdr_expr
%destructor { expr_free($$); }	exthdr_expr
%type <expr>			hbh_hdr_expr	frag_hdr_expr		dst_hdr_expr
%destructor { expr_free($$); }	hbh_hdr_expr	frag_hdr_expr		dst_hdr_expr
%type <val>			hbh_hdr_field	frag_hdr_field		dst_hdr_field
%type <expr>			rt_hdr_expr	rt0_hdr_expr		rt2_hdr_expr
%destructor { expr_free($$); }	rt_hdr_expr	rt0_hdr_expr		rt2_hdr_expr
%type <val>			rt_hdr_field	rt0_hdr_field		rt2_hdr_field
%type <expr>			mh_hdr_expr
%destructor { expr_free($$); }	mh_hdr_expr
%type <val>			mh_hdr_field

%type <expr>			meta_expr
%destructor { expr_free($$); }	meta_expr
%type <val>			meta_key	meta_key_qualified	meta_key_unqualified

%type <expr>			ct_expr
%destructor { expr_free($$); }	ct_expr
%type <val>			ct_key

%type <val>			export_format
%type <string>			monitor_event
%destructor { xfree($$); }	monitor_event
%type <val>			monitor_object	monitor_format

%%

input			:	/* empty */
			|	input		line
			{
				if ($2 != NULL) {
					LIST_HEAD(list);

					$2->location = @2;

					list_add_tail(&$2->list, &list);
					if (cmd_evaluate(&state->ectx, $2) < 0) {
						if (++state->nerrs == max_errors)
							YYABORT;
					} else
						list_splice_tail(&list, &state->cmds);
				}
			}
			;

stmt_seperator		:	NEWLINE
			|	SEMICOLON
			;

opt_newline		:	NEWLINE
		 	|	/* empty */
			;

common_block		:	INCLUDE		QUOTED_STRING	stmt_seperator
			{
				if (scanner_include_file(scanner, $2, &@$) < 0) {
					xfree($2);
					YYERROR;
				}
				xfree($2);
			}
			|	DEFINE		identifier	'='	initializer_expr	stmt_seperator
			{
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, $2) != NULL) {
					erec_queue(error(&@2, "redfinition of symbol '%s'", $2),
						   state->msgs);
					YYERROR;
				}

				symbol_bind(scope, $2, $4);
				xfree($2);
			}
			|	error		stmt_seperator
			{
				if (++state->nerrs == max_errors)
					YYABORT;
				yyerrok;
			}
			;

line			:	common_block			{ $$ = NULL; }
			|	stmt_seperator			{ $$ = NULL; }
			|	base_cmd	stmt_seperator	{ $$ = $1; }
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
					LIST_HEAD(list);

					$1->location = @1;

					list_add_tail(&$1->list, &list);
					if (cmd_evaluate(&state->ectx, $1) < 0) {
						if (++state->nerrs == max_errors)
							YYABORT;
					} else
						list_splice_tail(&list, &state->cmds);
				}
				$$ = NULL;

				YYACCEPT;
			}
			;

base_cmd		:	/* empty */	add_cmd		{ $$ = $1; }
	  		|	ADD		add_cmd		{ $$ = $2; }
			|	CREATE		create_cmd	{ $$ = $2; }
			|	INSERT		insert_cmd	{ $$ = $2; }
			|	DELETE		delete_cmd	{ $$ = $2; }
			|	LIST		list_cmd	{ $$ = $2; }
			|	FLUSH		flush_cmd	{ $$ = $2; }
			|	RENAME		rename_cmd	{ $$ = $2; }
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
			|	RULE		ruleid_spec	rule
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &$2, &@$, $3);
			}
			|	/* empty */	ruleid_spec	rule
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
			|	ELEMENT		set_spec	set_expr
			{
				$$ = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &$2, &@$, $3);
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
			;

insert_cmd		:	RULE		ruleid_spec	rule
			{
				$$ = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &$2, &@$, $3);
			}
			;

delete_cmd		:	TABLE		table_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &$2, &@$, NULL);
			}
			|	CHAIN		chain_spec
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
			|	MAP		set_spec
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &$2, &@$, NULL);
			}
			|	ELEMENT		set_spec	set_expr
			{
				$$ = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &$2, &@$, $3);
			}
			;

list_cmd		:	TABLE		table_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &$2, &@$, NULL);
			}
			|	TABLES		tables_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &$2, &@$, NULL);
			}
			|	CHAIN		chain_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &$2, &@$, NULL);
			}
			|	SETS		tables_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &$2, &@$, NULL);
			}
			|	SET		set_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &$2, &@$, NULL);
			}
			|	RULESET		ruleset_spec
			{
				$$ = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &$2, &@$, NULL);
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

export_cmd		:	export_format
			{
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct export *export = export_alloc($1);
				$$ = cmd_alloc(CMD_EXPORT, CMD_OBJ_EXPORT, &h, &@$, export);
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
			;

monitor_format		:	/* empty */	{ $$ = NFT_OUTPUT_DEFAULT; }
			|	export_format
			;

export_format		: 	XML 		{ $$ = NFT_OUTPUT_XML; }
			|	JSON		{ $$ = NFT_OUTPUT_JSON; }
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

table_block		:	/* empty */	{ $$ = $<table>-1; }
			|	table_block	common_block
			|	table_block	stmt_seperator
			|	table_block	CHAIN		chain_identifier
					chain_block_alloc	'{' 	chain_block	'}'
					stmt_seperator
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
					stmt_seperator
			{
				$4->location = @3;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				list_add_tail(&$4->list, &$1->sets);
				$$ = $1;
			}
			|	table_block	MAP		set_identifier
					map_block_alloc		'{'	map_block	'}'
					stmt_seperator
			{
				$4->location = @3;
				handle_merge(&$4->handle, &$3);
				handle_free(&$3);
				list_add_tail(&$4->list, &$1->sets);
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
	     		|	chain_block	stmt_seperator
			|	chain_block	hook_spec	stmt_seperator
			|	chain_block	rule		stmt_seperator
			{
				list_add_tail(&$2->list, &$1->rules);
				$$ = $1;
			}
			;

set_block_alloc		:	/* empty */
			{
				$$ = set_alloc(NULL);
			}
			;

set_block		:	/* empty */	{ $$ = $<set>-1; }
			|	set_block	common_block
			|	set_block	stmt_seperator
			|	set_block	TYPE		identifier	stmt_seperator
			{
				$1->keytype = datatype_lookup_byname($3);
				if ($1->keytype == NULL) {
					erec_queue(error(&@3, "unknown datatype %s", $3),
						   state->msgs);
					YYERROR;
				}
				$$ = $1;
			}
			|	set_block	FLAGS		set_flag_list	stmt_seperator
			{
				$1->flags = $3;
				$$ = $1;
			}
			|	set_block	ELEMENTS	'='		set_expr
			{
				$1->init = $4;
				$$ = $1;
			}
			|	set_block	set_mechanism	stmt_seperator
			;

set_flag_list		:	set_flag_list	COMMA		set_flag
			{
				$$ = $1 | $3;
			}
			|	set_flag
			;

set_flag		:	CONSTANT	{ $$ = SET_F_CONSTANT; }
			|	INTERVAL	{ $$ = SET_F_INTERVAL; }
			;

map_block_alloc		:	/* empty */
			{
				$$ = set_alloc(NULL);
				$$->flags |= NFT_SET_MAP;
			}
			;

map_block		:	/* empty */	{ $$ = $<set>-1; }
			|	map_block	common_block
			|	map_block	stmt_seperator
			|	map_block	TYPE
						identifier	COLON	identifier
						stmt_seperator
			{
				$1->keytype = datatype_lookup_byname($3);
				if ($1->keytype == NULL) {
					erec_queue(error(&@3, "unknown datatype %s", $3),
						   state->msgs);
					YYERROR;
				}

				$1->datatype = datatype_lookup_byname($5);
				if ($1->datatype == NULL) {
					erec_queue(error(&@5, "unknown datatype %s", $5),
						   state->msgs);
					YYERROR;
				}

				$$ = $1;
			}
			|	map_block	FLAGS		set_flag_list	stmt_seperator
			{
				$1->flags = $3;
				$$ = $1;
			}
			|	map_block	ELEMENTS	'='		set_expr
			{
				$1->init = $4;
				$$ = $1;
			}
			|	map_block	set_mechanism	stmt_seperator
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

hook_spec		:	TYPE		STRING		HOOK		STRING		PRIORITY	NUM
			{
				$<chain>0->type		= chain_type_name_lookup($2);
				if ($<chain>0->type == NULL) {
					erec_queue(error(&@2, "unknown chain type %s", $2),
						   state->msgs);
					YYERROR;
				}
				$<chain>0->hookstr	= chain_hookname_lookup($4);
				if ($<chain>0->hookstr == NULL) {
					erec_queue(error(&@4, "unknown chain hook %s", $4),
						   state->msgs);
					YYERROR;
				}
				$<chain>0->priority	= $6;
				$<chain>0->flags	|= CHAIN_F_BASECHAIN;
			}
			|	TYPE		STRING		HOOK		STRING		PRIORITY	DASH	NUM
			{
				$<chain>0->type		= chain_type_name_lookup($2);
				if ($<chain>0->type == NULL) {
					erec_queue(error(&@2, "unknown type name %s", $2),
						   state->msgs);
					YYERROR;
				}
				$<chain>0->hookstr	= chain_hookname_lookup($4);
				if ($<chain>0->hookstr == NULL) {
					erec_queue(error(&@4, "unknown hook name %s", $4),
						   state->msgs);
					YYERROR;
				}
				$<chain>0->priority	= -$7;
				$<chain>0->flags	|= CHAIN_F_BASECHAIN;
			}
			;

identifier		:	STRING
			;

string			:	STRING
			|	QUOTED_STRING
			;

family_spec		:	/* empty */		{ $$ = NFPROTO_IPV4; }
			|	family_spec_explicit
			;

family_spec_explicit	:	IP		{ $$ = NFPROTO_IPV4; }
			|	IP6		{ $$ = NFPROTO_IPV6; }
			|	INET		{ $$ = NFPROTO_INET; }
			|	ARP		{ $$ = NFPROTO_ARP; }
			|	BRIDGE		{ $$ = NFPROTO_BRIDGE; }
			;

table_spec		:	family_spec	identifier
			{
				memset(&$$, 0, sizeof($$));
				$$.family	= $1;
				$$.table	= $2;
			}
			;

tables_spec		:	family_spec
			{
				memset(&$$, 0, sizeof($$));
				$$.family	= $1;
				$$.table	= NULL;
			}
			;

chain_spec		:	table_spec	identifier
			{
				$$		= $1;
				$$.chain	= $2;
			}
			;

chain_identifier	:	identifier
			{
				memset(&$$, 0, sizeof($$));
				$$.chain	= $1;
			}
			;

set_spec		:	table_spec	identifier
			{
				$$		= $1;
				$$.set		= $2;
			}
			;

set_identifier		:	identifier
			{
				memset(&$$, 0, sizeof($$));
				$$.set		= $1;
			}
			;

handle_spec		:	/* empty */
			{
				$$ = 0;
			}
			|	HANDLE		NUM
			{
				$$ = $2;
			}
			;

position_spec		:	/* empty */
			{
				$$ = 0;
			}
			|	POSITION	NUM
			{
				$$ = $2;
			}
			;

ruleid_spec		:	chain_spec	handle_spec	position_spec
			{
				$$		= $1;
				$$.handle	= $2;
				$$.position	= $3;
			}
			;

comment_spec		:	/* empty */
			{
				$$ = NULL;
			}
			|	COMMENT		string
			{
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

rule			:	stmt_list	comment_spec
			{
				struct stmt *i;

				$$ = rule_alloc(&@$, NULL);
				$$->handle.comment = $2;
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

stmt			:	verdict_stmt
			|	match_stmt
			|	counter_stmt
			|	meta_stmt
			|	log_stmt
			|	limit_stmt
			|	reject_stmt
			|	nat_stmt
			|	queue_stmt
			|	ct_stmt
			|	masq_stmt
			|	redir_stmt
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
			|	AT	identifier
			{
				$$ = symbol_expr_alloc(&@$, SYMBOL_SET,
						       current_scope(state),
						       $2);
				xfree($2);
			}
			;

verdict_map_list_expr	:	verdict_map_list_member_expr
			{
				$$ = set_expr_alloc(&@$);
				compound_expr_add($$, $1);
			}
			|	verdict_map_list_expr	COMMA	verdict_map_list_member_expr
			{
				compound_expr_add($1, $3);
				$$ = $1;
			}
			|	verdict_map_list_expr	COMMA	opt_newline
			;

verdict_map_list_member_expr:	opt_newline	map_lhs_expr	COLON	verdict_expr	opt_newline
			{
				$$ = mapping_expr_alloc(&@$, $2, $4);
			}
			;


counter_stmt		:	counter_stmt_alloc
			|	counter_stmt_alloc	counter_args

counter_stmt_alloc	:	COUNTER
			{
				$$ = counter_stmt_alloc(&@$);
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
				$<stmt>0->log.prefix	 = $2;
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
			;

level_type		:	LEVEL_EMERG	{ $$ = LOG_EMERG; }
			|	LEVEL_ALERT	{ $$ = LOG_ALERT; }
			|	LEVEL_CRIT	{ $$ = LOG_CRIT; }
			|	LEVEL_ERR	{ $$ = LOG_ERR; }
			|	LEVEL_WARN	{ $$ = LOG_WARNING; }
			|	LEVEL_NOTICE	{ $$ = LOG_NOTICE; }
			|	LEVEL_INFO	{ $$ = LOG_INFO; }
			|	LEVEL_DEBUG	{ $$ = LOG_DEBUG; }
			;

limit_stmt		:	LIMIT	RATE	NUM	SLASH	time_unit
	    		{
				$$ = limit_stmt_alloc(&@$);
				$$->limit.rate	= $3;
				$$->limit.unit	= $5;
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
				$<stmt>0->reject.expr->dtype = &icmp_code_type;
			}
			|	WITH	ICMP6	TYPE	STRING
			{
				$<stmt>0->reject.family = NFPROTO_IPV6;
				$<stmt>0->reject.type = NFT_REJECT_ICMP_UNREACH;
				$<stmt>0->reject.expr =
					symbol_expr_alloc(&@$, SYMBOL_VALUE,
							  current_scope(state),
							  $4);
				$<stmt>0->reject.expr->dtype = &icmpv6_code_type;
			}
			|	WITH	ICMPX	TYPE	STRING
			{
				$<stmt>0->reject.type = NFT_REJECT_ICMPX_UNREACH;
				$<stmt>0->reject.expr =
					symbol_expr_alloc(&@$, SYMBOL_VALUE,
							  current_scope(state),
							  $4);
				$<stmt>0->reject.expr->dtype = &icmpx_code_type;
			}
			|	WITH	TCP	RESET
			{
				$<stmt>0->reject.type = NFT_REJECT_TCP_RST;
			}
			;

nat_stmt		:	nat_stmt_alloc	nat_stmt_args
			;

nat_stmt_alloc		:	SNAT
			{
				$$ = nat_stmt_alloc(&@$);
				$$->nat.type = NFT_NAT_SNAT;
			}
			|	DNAT
			{
				$$ = nat_stmt_alloc(&@$);
				$$->nat.type = NFT_NAT_DNAT;
			}
			;

nat_stmt_args		:	expr
			{
				$<stmt>0->nat.addr = $1;
			}
			|	expr	COLON	expr
			{
				$<stmt>0->nat.addr = $1;
				$<stmt>0->nat.proto = $3;
			}
			|	COLON	expr
			{
				$<stmt>0->nat.proto = $2;
			}
			|	nat_stmt_args	nf_nat_flags
			{
				$<stmt>0->nat.flags = $2;
			}
			;

masq_stmt		:	masq_stmt_alloc
			|	masq_stmt_alloc	nf_nat_flags
			{
				$$ = $1;
				$$->masq.flags = $2;
			}
			;

masq_stmt_alloc		:	MASQUERADE 	{ $$ = masq_stmt_alloc(&@$); }
			;

redir_stmt		:	redir_stmt_alloc	redir_stmt_arg
			|	redir_stmt_alloc
			;

redir_stmt_alloc	:	REDIRECT	{ $$ = redir_stmt_alloc(&@$); }
			;

redir_stmt_arg		:	TO	expr
			{
				$<stmt>0->redir.proto = $2;
			}
			|	nf_nat_flags
			{
				$<stmt>0->redir.flags = $1;
			}
			|	TO	expr	nf_nat_flags
			{
				$<stmt>0->redir.proto = $2;
				$<stmt>0->redir.flags = $3;
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

queue_stmt_arg		:	QUEUENUM	expr
			{
				$<stmt>0->queue.queue = $2;
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

match_stmt		:	relational_expr
			{
				$$ = expr_stmt_alloc(&@$, $1);
			}
			;

symbol_expr		:	string
			{
				$$ = symbol_expr_alloc(&@$, SYMBOL_VALUE,
						       current_scope(state),
						       $1);
				xfree($1);
			}
			|	'$'	identifier
			{
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, $2) == NULL) {
					erec_queue(error(&@2, "unknown identifier '%s'", $2),
						   state->msgs);
					YYERROR;
				}

				$$ = symbol_expr_alloc(&@$, SYMBOL_DEFINE,
						       scope, $2);
				xfree($2);
			}
			|	AT	identifier
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
			|	meta_expr			{ $$ = $1; }
			|	ct_expr				{ $$ = $1; }
			|	'('	basic_expr	')'	{ $$ = $2; }
			;

shift_expr		:	primary_expr
			|	shift_expr		LSHIFT		primary_expr
			{
				$$ = binop_expr_alloc(&@$, OP_LSHIFT, $1, $3);
			}
			|	shift_expr		RSHIFT		primary_expr
			{
				$$ = binop_expr_alloc(&@$, OP_RSHIFT, $1, $3);
			}
			;

and_expr		:	shift_expr
			|	and_expr		AMPERSAND	shift_expr
			{
				$$ = binop_expr_alloc(&@$, OP_AND, $1, $3);
			}
			;

exclusive_or_expr	:	and_expr
			|	exclusive_or_expr	CARET		and_expr
			{
				$$ = binop_expr_alloc(&@$, OP_XOR, $1, $3);
			}
			;

inclusive_or_expr	:	exclusive_or_expr
			|	inclusive_or_expr	'|'		exclusive_or_expr
			{
				$$ = binop_expr_alloc(&@$, OP_OR, $1, $3);
			}
			;

basic_expr		:	inclusive_or_expr
			;

concat_expr		:	basic_expr
			|	concat_expr		DOT		basic_expr
			{
				if ($$->ops->type != EXPR_CONCAT) {
					$$ = concat_expr_alloc(&@$);
					compound_expr_add($$, $1);
				} else {
					struct location rhs[] = {
						[1]	= @2,
						[2]	= @3,
					};
					location_update(&$3->location, rhs, 2);

					$$ = $1;
					$$->location = @$;
				}
				compound_expr_add($$, $3);
			}
			;

list_expr		:	basic_expr		COMMA		basic_expr
			{
				$$ = list_expr_alloc(&@$);
				compound_expr_add($$, $1);
				compound_expr_add($$, $3);
			}
			|	list_expr		COMMA		basic_expr
			{
				$1->location = @$;
				compound_expr_add($1, $3);
				$$ = $1;
			}
			;

prefix_expr		:	basic_expr		SLASH	NUM
			{
				$$ = prefix_expr_alloc(&@$, $1, $3);
			}
			;

range_expr		:	basic_expr		DASH	basic_expr
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

multiton_expr		:	prefix_expr
			|	range_expr
			|	wildcard_expr
			;

map_lhs_expr		:	multiton_expr
			|	concat_expr
			;

map_expr		:	concat_expr	MAP	expr
			{
				$$ = map_expr_alloc(&@$, $1, $3);
			}
			;

expr			:	concat_expr
			|	set_expr
			|       map_expr
			|	multiton_expr
			|	error_expr
			;

error_expr		:	ERROR
			{
				$$ = NULL;
				erec_queue(error(&@1, "bad value '%s'", $1),
					   state->msgs);
				YYERROR;
			}
			;

set_expr		:	'{'	set_list_expr		'}'
			{
				$2->location = @$;
				$$ = $2;
			}
			;

set_list_expr		:	set_list_member_expr
			{
				$$ = set_expr_alloc(&@$);
				compound_expr_add($$, $1);
			}
			|	set_list_expr		COMMA	set_list_member_expr
			{
				compound_expr_add($1, $3);
				$$ = $1;
			}
			|	set_list_expr		COMMA	opt_newline
			;

set_list_member_expr	:	opt_newline	expr	opt_newline
			{
				$$ = $2;
			}
			|	opt_newline	map_lhs_expr	COLON	concat_expr	opt_newline
			{
				$$ = mapping_expr_alloc(&@$, $2, $4);
			}
			|	opt_newline	map_lhs_expr	COLON	verdict_expr	opt_newline
			{
				$$ = mapping_expr_alloc(&@$, $2, $4);
			}
			;

initializer_expr	:	expr
			|	list_expr
			;

relational_expr		:	expr	/* implicit */	expr
			{
				$$ = relational_expr_alloc(&@$, OP_IMPLICIT, $1, $2);
			}
			|	expr	/* implicit */	list_expr
			{
				$$ = relational_expr_alloc(&@$, OP_FLAGCMP, $1, $2);
			}
			|	expr	relational_op	expr
			{
				$$ = relational_expr_alloc(&@2, $2, $1, $3);
			}
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
			|	JUMP			identifier
			{
				$$ = verdict_expr_alloc(&@$, NFT_JUMP, $2);
			}
			|	GOTO			identifier
			{
				$$ = verdict_expr_alloc(&@$, NFT_GOTO, $2);
			}
			|	RETURN
			{
				$$ = verdict_expr_alloc(&@$, NFT_RETURN, NULL);
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
			;

meta_key		:	meta_key_qualified
			|	meta_key_unqualified
			;

meta_key_qualified	:	LENGTH		{ $$ = NFT_META_LEN; }
			|	NFPROTO		{ $$ = NFT_META_NFPROTO; }
			|	L4PROTO		{ $$ = NFT_META_L4PROTO; }
			|	PROTOCOL	{ $$ = NFT_META_PROTOCOL; }
			|	PRIORITY	{ $$ = NFT_META_PRIORITY; }
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
			|       PKTTYPE		{ $$ = NFT_META_PKTTYPE; }
			|       CPU		{ $$ = NFT_META_CPU; }
			|       IIFGROUP	{ $$ = NFT_META_IIFGROUP; }
			|       OIFGROUP	{ $$ = NFT_META_OIFGROUP; }
			|       CGROUP		{ $$ = NFT_META_CGROUP; }
			;

meta_stmt		:	META	meta_key	SET	expr
			{
				$$ = meta_stmt_alloc(&@$, $2, $4);
			}
			|	meta_key_unqualified	SET	expr
			{
				$$ = meta_stmt_alloc(&@$, $1, $3);
			}
			;

ct_expr			:	CT	ct_key
			{
				$$ = ct_expr_alloc(&@$, $2);
			}
			;

ct_key			:	STATE		{ $$ = NFT_CT_STATE; }
			|	DIRECTION	{ $$ = NFT_CT_DIRECTION; }
			|	STATUS		{ $$ = NFT_CT_STATUS; }
			|	MARK		{ $$ = NFT_CT_MARK; }
			|	EXPIRATION	{ $$ = NFT_CT_EXPIRATION; }
			|	HELPER		{ $$ = NFT_CT_HELPER; }
			|	L3PROTOCOL	{ $$ = NFT_CT_L3PROTOCOL; }
			|	SADDR		{ $$ = NFT_CT_SRC; }
			|	DADDR		{ $$ = NFT_CT_DST; }
			|	PROTOCOL	{ $$ = NFT_CT_PROTOCOL; }
			|	PROTO_SRC	{ $$ = NFT_CT_PROTO_SRC; }
			|	PROTO_DST	{ $$ = NFT_CT_PROTO_DST; }
			|	LABEL		{ $$ = NFT_CT_LABELS; }
			;

ct_stmt			:	CT	ct_key		SET	expr
			{
				$$ = ct_stmt_alloc(&@$, $2, $4);
			}
			;

payload_expr		:	payload_raw_expr
			|	eth_hdr_expr
			|	vlan_hdr_expr
			|	arp_hdr_expr
			|	ip_hdr_expr
			|	icmp_hdr_expr
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
			;

payload_raw_expr	:	AT	payload_base_spec	COMMA	NUM	COMMA	NUM
			{
				$$ = payload_expr_alloc(&@$, NULL, 0);
				$$->payload.base	= $2;
				$$->payload.offset	= $4;
				$$->len			= $6;
				$$->dtype		= &integer_type;
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
			|	ETHER
			{
				$$ = symbol_expr_alloc(&@$, SYMBOL_VALUE,
						       current_scope(state),
						       "ether");
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
			|	VLAN
			{
				$$ = symbol_expr_alloc(&@$, SYMBOL_VALUE,
						       current_scope(state),
						       "vlan");
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
			|	ARP
			{
				$$ = symbol_expr_alloc(&@$, SYMBOL_VALUE,
						       current_scope(state),
						       "arp");
			}
			;

arp_hdr_field		:	HTYPE		{ $$ = ARPHDR_HRD; }
			|	PTYPE		{ $$ = ARPHDR_PRO; }
			|	HLEN		{ $$ = ARPHDR_HLN; }
			|	PLEN		{ $$ = ARPHDR_PLN; }
			|	OPERATION	{ $$ = ARPHDR_OP; }
			;

ip_hdr_expr		:	IP	ip_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_ip, $2);
			}
			|	IP
			{
				$$ = symbol_expr_alloc(&@$, SYMBOL_VALUE,
						       current_scope(state),
						       "ip");
			}
			;

ip_hdr_field		:	VERSION		{ $$ = IPHDR_VERSION; }
			|	HDRLENGTH	{ $$ = IPHDR_HDRLENGTH; }
			|	TOS		{ $$ = IPHDR_TOS; }
			|	LENGTH		{ $$ = IPHDR_LENGTH; }
			|	ID		{ $$ = IPHDR_ID; }
			|	FRAG_OFF	{ $$ = IPHDR_FRAG_OFF; }
			|	TTL		{ $$ = IPHDR_TTL; }
			|	PROTOCOL	{ $$ = IPHDR_PROTOCOL; }
			|	CHECKSUM	{ $$ = IPHDR_CHECKSUM; }
			|	SADDR		{ $$ = IPHDR_SADDR; }
			|	DADDR		{ $$ = IPHDR_DADDR; }
			;

icmp_hdr_expr		:	ICMP	icmp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_icmp, $2);
			}
			|	ICMP
			{
				uint8_t data = IPPROTO_ICMP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
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

ip6_hdr_expr		:	IP6	ip6_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_ip6, $2);
			}
			|	IP6
			{
				$$ = symbol_expr_alloc(&@$, SYMBOL_VALUE,
						       current_scope(state),
						       "ip6");
			}
			;

ip6_hdr_field		:	VERSION		{ $$ = IP6HDR_VERSION; }
			|	PRIORITY	{ $$ = IP6HDR_PRIORITY; }
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
			|	ICMP6
			{
				uint8_t data = IPPROTO_ICMPV6;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
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
			|	AH
			{
				uint8_t data = IPPROTO_AH;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
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
			|	ESP
			{
				uint8_t data = IPPROTO_ESP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			;

esp_hdr_field		:	SPI		{ $$ = ESPHDR_SPI; }
			|	SEQUENCE	{ $$ = ESPHDR_SEQUENCE; }
			;

comp_hdr_expr		:	COMP	comp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_comp, $2);
			}
			|	COMP
			{
				uint8_t data = IPPROTO_COMP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
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
			|	UDP
			{
				uint8_t data = IPPROTO_UDP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
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
			|	UDPLITE
			{
				uint8_t data = IPPROTO_UDPLITE;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
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
			|	TCP
			{
				uint8_t data = IPPROTO_TCP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
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

dccp_hdr_expr		:	DCCP	dccp_hdr_field
			{
				$$ = payload_expr_alloc(&@$, &proto_dccp, $2);
			}
			|	DCCP
			{
				uint8_t data = IPPROTO_DCCP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
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
			|	SCTP
			{
				uint8_t data = IPPROTO_SCTP;
				$$ = constant_expr_alloc(&@$, &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
			;

sctp_hdr_field		:	SPORT		{ $$ = SCTPHDR_SPORT; }
			|	DPORT		{ $$ = SCTPHDR_DPORT; }
			|	VTAG		{ $$ = SCTPHDR_VTAG; }
			|	CHECKSUM	{ $$ = SCTPHDR_CHECKSUM; }
			;

exthdr_expr		:	hbh_hdr_expr
			|	rt_hdr_expr
			|	rt0_hdr_expr
			|	rt2_hdr_expr
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

%%
