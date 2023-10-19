/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         nft_parse
#define yylex           nft_lex
#define yyerror         nft_error
#define yydebug         nft_debug
#define yynerrs         nft_nerrs

/* First part of user prologue.  */
#line 11 "parser_bison.y"

#include <nft.h>

#include <ctype.h>
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
#include <sctp_chunk.h>

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

static int open_scope(struct parser_state *state, struct scope *scope)
{
	if (state->scope >= array_size(state->scopes) - 1) {
		state->scope_err = true;
		return -1;
	}

	scope_init(scope, current_scope(state));
	state->scopes[++state->scope] = scope;

	return 0;
}

static void close_scope(struct parser_state *state)
{
	if (state->scope_err || state->scope == 0) {
		state->scope_err = false;
		return;
	}

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

static struct expr *ifname_expr_alloc(const struct location *location,
				      struct list_head *queue,
				      const char *name)
{
	unsigned int length = strlen(name);
	struct expr *expr;

	if (length == 0) {
		xfree(name);
		erec_queue(error(location, "empty interface name"), queue);
		return NULL;
	}

	if (length > 16) {
		xfree(name);
		erec_queue(error(location, "interface name too long"), queue);
		return NULL;
	}

	expr = constant_expr_alloc(location, &ifname_type, BYTEORDER_HOST_ENDIAN,
				   length * BITS_PER_BYTE, name);

	xfree(name);

	return expr;
}

#define YYLLOC_DEFAULT(Current, Rhs, N)	location_update(&Current, Rhs, N)

#define symbol_value(loc, str) \
	symbol_expr_alloc(loc, SYMBOL_VALUE, current_scope(state), str)

/* Declare those here to avoid compiler warnings */
void nft_set_debug(int, void *);
int nft_lex(void *, void *, void *);

#line 250 "parser_bison.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_NFT_PARSER_BISON_H_INCLUDED
# define YY_NFT_PARSER_BISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int nft_debug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    TOKEN_EOF = 0,                 /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    JUNK = 258,                    /* "junk"  */
    NEWLINE = 259,                 /* "newline"  */
    COLON = 260,                   /* "colon"  */
    SEMICOLON = 261,               /* "semicolon"  */
    COMMA = 262,                   /* "comma"  */
    DOT = 263,                     /* "."  */
    EQ = 264,                      /* "=="  */
    NEQ = 265,                     /* "!="  */
    LT = 266,                      /* "<"  */
    GT = 267,                      /* ">"  */
    GTE = 268,                     /* ">="  */
    LTE = 269,                     /* "<="  */
    LSHIFT = 270,                  /* "<<"  */
    RSHIFT = 271,                  /* ">>"  */
    AMPERSAND = 272,               /* "&"  */
    CARET = 273,                   /* "^"  */
    NOT = 274,                     /* "!"  */
    SLASH = 275,                   /* "/"  */
    ASTERISK = 276,                /* "*"  */
    DASH = 277,                    /* "-"  */
    AT = 278,                      /* "@"  */
    VMAP = 279,                    /* "vmap"  */
    PLUS = 280,                    /* "+"  */
    INCLUDE = 281,                 /* "include"  */
    DEFINE = 282,                  /* "define"  */
    REDEFINE = 283,                /* "redefine"  */
    UNDEFINE = 284,                /* "undefine"  */
    FIB = 285,                     /* "fib"  */
    SOCKET = 286,                  /* "socket"  */
    TRANSPARENT = 287,             /* "transparent"  */
    WILDCARD = 288,                /* "wildcard"  */
    CGROUPV2 = 289,                /* "cgroupv2"  */
    TPROXY = 290,                  /* "tproxy"  */
    OSF = 291,                     /* "osf"  */
    SYNPROXY = 292,                /* "synproxy"  */
    MSS = 293,                     /* "mss"  */
    WSCALE = 294,                  /* "wscale"  */
    TYPEOF = 295,                  /* "typeof"  */
    HOOK = 296,                    /* "hook"  */
    HOOKS = 297,                   /* "hooks"  */
    DEVICE = 298,                  /* "device"  */
    DEVICES = 299,                 /* "devices"  */
    TABLE = 300,                   /* "table"  */
    TABLES = 301,                  /* "tables"  */
    CHAIN = 302,                   /* "chain"  */
    CHAINS = 303,                  /* "chains"  */
    RULE = 304,                    /* "rule"  */
    RULES = 305,                   /* "rules"  */
    SETS = 306,                    /* "sets"  */
    SET = 307,                     /* "set"  */
    ELEMENT = 308,                 /* "element"  */
    MAP = 309,                     /* "map"  */
    MAPS = 310,                    /* "maps"  */
    FLOWTABLE = 311,               /* "flowtable"  */
    HANDLE = 312,                  /* "handle"  */
    RULESET = 313,                 /* "ruleset"  */
    TRACE = 314,                   /* "trace"  */
    INET = 315,                    /* "inet"  */
    NETDEV = 316,                  /* "netdev"  */
    ADD = 317,                     /* "add"  */
    UPDATE = 318,                  /* "update"  */
    REPLACE = 319,                 /* "replace"  */
    CREATE = 320,                  /* "create"  */
    INSERT = 321,                  /* "insert"  */
    DELETE = 322,                  /* "delete"  */
    GET = 323,                     /* "get"  */
    LIST = 324,                    /* "list"  */
    RESET = 325,                   /* "reset"  */
    FLUSH = 326,                   /* "flush"  */
    RENAME = 327,                  /* "rename"  */
    DESCRIBE = 328,                /* "describe"  */
    IMPORT = 329,                  /* "import"  */
    EXPORT = 330,                  /* "export"  */
    DESTROY = 331,                 /* "destroy"  */
    MONITOR = 332,                 /* "monitor"  */
    ALL = 333,                     /* "all"  */
    ACCEPT = 334,                  /* "accept"  */
    DROP = 335,                    /* "drop"  */
    CONTINUE = 336,                /* "continue"  */
    JUMP = 337,                    /* "jump"  */
    GOTO = 338,                    /* "goto"  */
    RETURN = 339,                  /* "return"  */
    TO = 340,                      /* "to"  */
    CONSTANT = 341,                /* "constant"  */
    INTERVAL = 342,                /* "interval"  */
    DYNAMIC = 343,                 /* "dynamic"  */
    AUTOMERGE = 344,               /* "auto-merge"  */
    TIMEOUT = 345,                 /* "timeout"  */
    GC_INTERVAL = 346,             /* "gc-interval"  */
    ELEMENTS = 347,                /* "elements"  */
    EXPIRES = 348,                 /* "expires"  */
    POLICY = 349,                  /* "policy"  */
    MEMORY = 350,                  /* "memory"  */
    PERFORMANCE = 351,             /* "performance"  */
    SIZE = 352,                    /* "size"  */
    FLOW = 353,                    /* "flow"  */
    OFFLOAD = 354,                 /* "offload"  */
    METER = 355,                   /* "meter"  */
    METERS = 356,                  /* "meters"  */
    FLOWTABLES = 357,              /* "flowtables"  */
    NUM = 358,                     /* "number"  */
    STRING = 359,                  /* "string"  */
    QUOTED_STRING = 360,           /* "quoted string"  */
    ASTERISK_STRING = 361,         /* "string with a trailing asterisk"  */
    LL_HDR = 362,                  /* "ll"  */
    NETWORK_HDR = 363,             /* "nh"  */
    TRANSPORT_HDR = 364,           /* "th"  */
    BRIDGE = 365,                  /* "bridge"  */
    ETHER = 366,                   /* "ether"  */
    SADDR = 367,                   /* "saddr"  */
    DADDR = 368,                   /* "daddr"  */
    TYPE = 369,                    /* "type"  */
    VLAN = 370,                    /* "vlan"  */
    ID = 371,                      /* "id"  */
    CFI = 372,                     /* "cfi"  */
    DEI = 373,                     /* "dei"  */
    PCP = 374,                     /* "pcp"  */
    ARP = 375,                     /* "arp"  */
    HTYPE = 376,                   /* "htype"  */
    PTYPE = 377,                   /* "ptype"  */
    HLEN = 378,                    /* "hlen"  */
    PLEN = 379,                    /* "plen"  */
    OPERATION = 380,               /* "operation"  */
    IP = 381,                      /* "ip"  */
    HDRVERSION = 382,              /* "version"  */
    HDRLENGTH = 383,               /* "hdrlength"  */
    DSCP = 384,                    /* "dscp"  */
    ECN = 385,                     /* "ecn"  */
    LENGTH = 386,                  /* "length"  */
    FRAG_OFF = 387,                /* "frag-off"  */
    TTL = 388,                     /* "ttl"  */
    PROTOCOL = 389,                /* "protocol"  */
    CHECKSUM = 390,                /* "checksum"  */
    PTR = 391,                     /* "ptr"  */
    VALUE = 392,                   /* "value"  */
    LSRR = 393,                    /* "lsrr"  */
    RR = 394,                      /* "rr"  */
    SSRR = 395,                    /* "ssrr"  */
    RA = 396,                      /* "ra"  */
    ICMP = 397,                    /* "icmp"  */
    CODE = 398,                    /* "code"  */
    SEQUENCE = 399,                /* "seq"  */
    GATEWAY = 400,                 /* "gateway"  */
    MTU = 401,                     /* "mtu"  */
    IGMP = 402,                    /* "igmp"  */
    MRT = 403,                     /* "mrt"  */
    OPTIONS = 404,                 /* "options"  */
    IP6 = 405,                     /* "ip6"  */
    PRIORITY = 406,                /* "priority"  */
    FLOWLABEL = 407,               /* "flowlabel"  */
    NEXTHDR = 408,                 /* "nexthdr"  */
    HOPLIMIT = 409,                /* "hoplimit"  */
    ICMP6 = 410,                   /* "icmpv6"  */
    PPTR = 411,                    /* "param-problem"  */
    MAXDELAY = 412,                /* "max-delay"  */
    TADDR = 413,                   /* "taddr"  */
    AH = 414,                      /* "ah"  */
    RESERVED = 415,                /* "reserved"  */
    SPI = 416,                     /* "spi"  */
    ESP = 417,                     /* "esp"  */
    COMP = 418,                    /* "comp"  */
    FLAGS = 419,                   /* "flags"  */
    CPI = 420,                     /* "cpi"  */
    PORT = 421,                    /* "port"  */
    UDP = 422,                     /* "udp"  */
    SPORT = 423,                   /* "sport"  */
    DPORT = 424,                   /* "dport"  */
    UDPLITE = 425,                 /* "udplite"  */
    CSUMCOV = 426,                 /* "csumcov"  */
    TCP = 427,                     /* "tcp"  */
    ACKSEQ = 428,                  /* "ackseq"  */
    DOFF = 429,                    /* "doff"  */
    WINDOW = 430,                  /* "window"  */
    URGPTR = 431,                  /* "urgptr"  */
    OPTION = 432,                  /* "option"  */
    ECHO = 433,                    /* "echo"  */
    EOL = 434,                     /* "eol"  */
    MPTCP = 435,                   /* "mptcp"  */
    NOP = 436,                     /* "nop"  */
    SACK = 437,                    /* "sack"  */
    SACK0 = 438,                   /* "sack0"  */
    SACK1 = 439,                   /* "sack1"  */
    SACK2 = 440,                   /* "sack2"  */
    SACK3 = 441,                   /* "sack3"  */
    SACK_PERM = 442,               /* "sack-permitted"  */
    FASTOPEN = 443,                /* "fastopen"  */
    MD5SIG = 444,                  /* "md5sig"  */
    TIMESTAMP = 445,               /* "timestamp"  */
    COUNT = 446,                   /* "count"  */
    LEFT = 447,                    /* "left"  */
    RIGHT = 448,                   /* "right"  */
    TSVAL = 449,                   /* "tsval"  */
    TSECR = 450,                   /* "tsecr"  */
    SUBTYPE = 451,                 /* "subtype"  */
    DCCP = 452,                    /* "dccp"  */
    VXLAN = 453,                   /* "vxlan"  */
    VNI = 454,                     /* "vni"  */
    GRE = 455,                     /* "gre"  */
    GRETAP = 456,                  /* "gretap"  */
    GENEVE = 457,                  /* "geneve"  */
    SCTP = 458,                    /* "sctp"  */
    CHUNK = 459,                   /* "chunk"  */
    DATA = 460,                    /* "data"  */
    INIT = 461,                    /* "init"  */
    INIT_ACK = 462,                /* "init-ack"  */
    HEARTBEAT = 463,               /* "heartbeat"  */
    HEARTBEAT_ACK = 464,           /* "heartbeat-ack"  */
    ABORT = 465,                   /* "abort"  */
    SHUTDOWN = 466,                /* "shutdown"  */
    SHUTDOWN_ACK = 467,            /* "shutdown-ack"  */
    ERROR = 468,                   /* "error"  */
    COOKIE_ECHO = 469,             /* "cookie-echo"  */
    COOKIE_ACK = 470,              /* "cookie-ack"  */
    ECNE = 471,                    /* "ecne"  */
    CWR = 472,                     /* "cwr"  */
    SHUTDOWN_COMPLETE = 473,       /* "shutdown-complete"  */
    ASCONF_ACK = 474,              /* "asconf-ack"  */
    FORWARD_TSN = 475,             /* "forward-tsn"  */
    ASCONF = 476,                  /* "asconf"  */
    TSN = 477,                     /* "tsn"  */
    STREAM = 478,                  /* "stream"  */
    SSN = 479,                     /* "ssn"  */
    PPID = 480,                    /* "ppid"  */
    INIT_TAG = 481,                /* "init-tag"  */
    A_RWND = 482,                  /* "a-rwnd"  */
    NUM_OSTREAMS = 483,            /* "num-outbound-streams"  */
    NUM_ISTREAMS = 484,            /* "num-inbound-streams"  */
    INIT_TSN = 485,                /* "initial-tsn"  */
    CUM_TSN_ACK = 486,             /* "cum-tsn-ack"  */
    NUM_GACK_BLOCKS = 487,         /* "num-gap-ack-blocks"  */
    NUM_DUP_TSNS = 488,            /* "num-dup-tsns"  */
    LOWEST_TSN = 489,              /* "lowest-tsn"  */
    SEQNO = 490,                   /* "seqno"  */
    NEW_CUM_TSN = 491,             /* "new-cum-tsn"  */
    VTAG = 492,                    /* "vtag"  */
    RT = 493,                      /* "rt"  */
    RT0 = 494,                     /* "rt0"  */
    RT2 = 495,                     /* "rt2"  */
    RT4 = 496,                     /* "srh"  */
    SEG_LEFT = 497,                /* "seg-left"  */
    ADDR = 498,                    /* "addr"  */
    LAST_ENT = 499,                /* "last-entry"  */
    TAG = 500,                     /* "tag"  */
    SID = 501,                     /* "sid"  */
    HBH = 502,                     /* "hbh"  */
    FRAG = 503,                    /* "frag"  */
    RESERVED2 = 504,               /* "reserved2"  */
    MORE_FRAGMENTS = 505,          /* "more-fragments"  */
    DST = 506,                     /* "dst"  */
    MH = 507,                      /* "mh"  */
    META = 508,                    /* "meta"  */
    MARK = 509,                    /* "mark"  */
    IIF = 510,                     /* "iif"  */
    IIFNAME = 511,                 /* "iifname"  */
    IIFTYPE = 512,                 /* "iiftype"  */
    OIF = 513,                     /* "oif"  */
    OIFNAME = 514,                 /* "oifname"  */
    OIFTYPE = 515,                 /* "oiftype"  */
    SKUID = 516,                   /* "skuid"  */
    SKGID = 517,                   /* "skgid"  */
    NFTRACE = 518,                 /* "nftrace"  */
    RTCLASSID = 519,               /* "rtclassid"  */
    IBRIPORT = 520,                /* "ibriport"  */
    OBRIPORT = 521,                /* "obriport"  */
    IBRIDGENAME = 522,             /* "ibrname"  */
    OBRIDGENAME = 523,             /* "obrname"  */
    PKTTYPE = 524,                 /* "pkttype"  */
    CPU = 525,                     /* "cpu"  */
    IIFGROUP = 526,                /* "iifgroup"  */
    OIFGROUP = 527,                /* "oifgroup"  */
    CGROUP = 528,                  /* "cgroup"  */
    TIME = 529,                    /* "time"  */
    CLASSID = 530,                 /* "classid"  */
    NEXTHOP = 531,                 /* "nexthop"  */
    CT = 532,                      /* "ct"  */
    L3PROTOCOL = 533,              /* "l3proto"  */
    PROTO_SRC = 534,               /* "proto-src"  */
    PROTO_DST = 535,               /* "proto-dst"  */
    ZONE = 536,                    /* "zone"  */
    DIRECTION = 537,               /* "direction"  */
    EVENT = 538,                   /* "event"  */
    EXPECTATION = 539,             /* "expectation"  */
    EXPIRATION = 540,              /* "expiration"  */
    HELPER = 541,                  /* "helper"  */
    LABEL = 542,                   /* "label"  */
    STATE = 543,                   /* "state"  */
    STATUS = 544,                  /* "status"  */
    ORIGINAL = 545,                /* "original"  */
    REPLY = 546,                   /* "reply"  */
    COUNTER = 547,                 /* "counter"  */
    NAME = 548,                    /* "name"  */
    PACKETS = 549,                 /* "packets"  */
    BYTES = 550,                   /* "bytes"  */
    AVGPKT = 551,                  /* "avgpkt"  */
    LAST = 552,                    /* "last"  */
    NEVER = 553,                   /* "never"  */
    COUNTERS = 554,                /* "counters"  */
    QUOTAS = 555,                  /* "quotas"  */
    LIMITS = 556,                  /* "limits"  */
    SYNPROXYS = 557,               /* "synproxys"  */
    HELPERS = 558,                 /* "helpers"  */
    LOG = 559,                     /* "log"  */
    PREFIX = 560,                  /* "prefix"  */
    GROUP = 561,                   /* "group"  */
    SNAPLEN = 562,                 /* "snaplen"  */
    QUEUE_THRESHOLD = 563,         /* "queue-threshold"  */
    LEVEL = 564,                   /* "level"  */
    LIMIT = 565,                   /* "limit"  */
    RATE = 566,                    /* "rate"  */
    BURST = 567,                   /* "burst"  */
    OVER = 568,                    /* "over"  */
    UNTIL = 569,                   /* "until"  */
    QUOTA = 570,                   /* "quota"  */
    USED = 571,                    /* "used"  */
    SECMARK = 572,                 /* "secmark"  */
    SECMARKS = 573,                /* "secmarks"  */
    SECOND = 574,                  /* "second"  */
    MINUTE = 575,                  /* "minute"  */
    HOUR = 576,                    /* "hour"  */
    DAY = 577,                     /* "day"  */
    WEEK = 578,                    /* "week"  */
    _REJECT = 579,                 /* "reject"  */
    WITH = 580,                    /* "with"  */
    ICMPX = 581,                   /* "icmpx"  */
    SNAT = 582,                    /* "snat"  */
    DNAT = 583,                    /* "dnat"  */
    MASQUERADE = 584,              /* "masquerade"  */
    REDIRECT = 585,                /* "redirect"  */
    RANDOM = 586,                  /* "random"  */
    FULLY_RANDOM = 587,            /* "fully-random"  */
    PERSISTENT = 588,              /* "persistent"  */
    QUEUE = 589,                   /* "queue"  */
    QUEUENUM = 590,                /* "num"  */
    BYPASS = 591,                  /* "bypass"  */
    FANOUT = 592,                  /* "fanout"  */
    DUP = 593,                     /* "dup"  */
    FWD = 594,                     /* "fwd"  */
    NUMGEN = 595,                  /* "numgen"  */
    INC = 596,                     /* "inc"  */
    MOD = 597,                     /* "mod"  */
    OFFSET = 598,                  /* "offset"  */
    JHASH = 599,                   /* "jhash"  */
    SYMHASH = 600,                 /* "symhash"  */
    SEED = 601,                    /* "seed"  */
    POSITION = 602,                /* "position"  */
    INDEX = 603,                   /* "index"  */
    COMMENT = 604,                 /* "comment"  */
    XML = 605,                     /* "xml"  */
    JSON = 606,                    /* "json"  */
    VM = 607,                      /* "vm"  */
    NOTRACK = 608,                 /* "notrack"  */
    EXISTS = 609,                  /* "exists"  */
    MISSING = 610,                 /* "missing"  */
    EXTHDR = 611,                  /* "exthdr"  */
    IPSEC = 612,                   /* "ipsec"  */
    REQID = 613,                   /* "reqid"  */
    SPNUM = 614,                   /* "spnum"  */
    IN = 615,                      /* "in"  */
    OUT = 616,                     /* "out"  */
    XT = 617                       /* "xt"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define TOKEN_EOF 0
#define YYerror 256
#define YYUNDEF 257
#define JUNK 258
#define NEWLINE 259
#define COLON 260
#define SEMICOLON 261
#define COMMA 262
#define DOT 263
#define EQ 264
#define NEQ 265
#define LT 266
#define GT 267
#define GTE 268
#define LTE 269
#define LSHIFT 270
#define RSHIFT 271
#define AMPERSAND 272
#define CARET 273
#define NOT 274
#define SLASH 275
#define ASTERISK 276
#define DASH 277
#define AT 278
#define VMAP 279
#define PLUS 280
#define INCLUDE 281
#define DEFINE 282
#define REDEFINE 283
#define UNDEFINE 284
#define FIB 285
#define SOCKET 286
#define TRANSPARENT 287
#define WILDCARD 288
#define CGROUPV2 289
#define TPROXY 290
#define OSF 291
#define SYNPROXY 292
#define MSS 293
#define WSCALE 294
#define TYPEOF 295
#define HOOK 296
#define HOOKS 297
#define DEVICE 298
#define DEVICES 299
#define TABLE 300
#define TABLES 301
#define CHAIN 302
#define CHAINS 303
#define RULE 304
#define RULES 305
#define SETS 306
#define SET 307
#define ELEMENT 308
#define MAP 309
#define MAPS 310
#define FLOWTABLE 311
#define HANDLE 312
#define RULESET 313
#define TRACE 314
#define INET 315
#define NETDEV 316
#define ADD 317
#define UPDATE 318
#define REPLACE 319
#define CREATE 320
#define INSERT 321
#define DELETE 322
#define GET 323
#define LIST 324
#define RESET 325
#define FLUSH 326
#define RENAME 327
#define DESCRIBE 328
#define IMPORT 329
#define EXPORT 330
#define DESTROY 331
#define MONITOR 332
#define ALL 333
#define ACCEPT 334
#define DROP 335
#define CONTINUE 336
#define JUMP 337
#define GOTO 338
#define RETURN 339
#define TO 340
#define CONSTANT 341
#define INTERVAL 342
#define DYNAMIC 343
#define AUTOMERGE 344
#define TIMEOUT 345
#define GC_INTERVAL 346
#define ELEMENTS 347
#define EXPIRES 348
#define POLICY 349
#define MEMORY 350
#define PERFORMANCE 351
#define SIZE 352
#define FLOW 353
#define OFFLOAD 354
#define METER 355
#define METERS 356
#define FLOWTABLES 357
#define NUM 358
#define STRING 359
#define QUOTED_STRING 360
#define ASTERISK_STRING 361
#define LL_HDR 362
#define NETWORK_HDR 363
#define TRANSPORT_HDR 364
#define BRIDGE 365
#define ETHER 366
#define SADDR 367
#define DADDR 368
#define TYPE 369
#define VLAN 370
#define ID 371
#define CFI 372
#define DEI 373
#define PCP 374
#define ARP 375
#define HTYPE 376
#define PTYPE 377
#define HLEN 378
#define PLEN 379
#define OPERATION 380
#define IP 381
#define HDRVERSION 382
#define HDRLENGTH 383
#define DSCP 384
#define ECN 385
#define LENGTH 386
#define FRAG_OFF 387
#define TTL 388
#define PROTOCOL 389
#define CHECKSUM 390
#define PTR 391
#define VALUE 392
#define LSRR 393
#define RR 394
#define SSRR 395
#define RA 396
#define ICMP 397
#define CODE 398
#define SEQUENCE 399
#define GATEWAY 400
#define MTU 401
#define IGMP 402
#define MRT 403
#define OPTIONS 404
#define IP6 405
#define PRIORITY 406
#define FLOWLABEL 407
#define NEXTHDR 408
#define HOPLIMIT 409
#define ICMP6 410
#define PPTR 411
#define MAXDELAY 412
#define TADDR 413
#define AH 414
#define RESERVED 415
#define SPI 416
#define ESP 417
#define COMP 418
#define FLAGS 419
#define CPI 420
#define PORT 421
#define UDP 422
#define SPORT 423
#define DPORT 424
#define UDPLITE 425
#define CSUMCOV 426
#define TCP 427
#define ACKSEQ 428
#define DOFF 429
#define WINDOW 430
#define URGPTR 431
#define OPTION 432
#define ECHO 433
#define EOL 434
#define MPTCP 435
#define NOP 436
#define SACK 437
#define SACK0 438
#define SACK1 439
#define SACK2 440
#define SACK3 441
#define SACK_PERM 442
#define FASTOPEN 443
#define MD5SIG 444
#define TIMESTAMP 445
#define COUNT 446
#define LEFT 447
#define RIGHT 448
#define TSVAL 449
#define TSECR 450
#define SUBTYPE 451
#define DCCP 452
#define VXLAN 453
#define VNI 454
#define GRE 455
#define GRETAP 456
#define GENEVE 457
#define SCTP 458
#define CHUNK 459
#define DATA 460
#define INIT 461
#define INIT_ACK 462
#define HEARTBEAT 463
#define HEARTBEAT_ACK 464
#define ABORT 465
#define SHUTDOWN 466
#define SHUTDOWN_ACK 467
#define ERROR 468
#define COOKIE_ECHO 469
#define COOKIE_ACK 470
#define ECNE 471
#define CWR 472
#define SHUTDOWN_COMPLETE 473
#define ASCONF_ACK 474
#define FORWARD_TSN 475
#define ASCONF 476
#define TSN 477
#define STREAM 478
#define SSN 479
#define PPID 480
#define INIT_TAG 481
#define A_RWND 482
#define NUM_OSTREAMS 483
#define NUM_ISTREAMS 484
#define INIT_TSN 485
#define CUM_TSN_ACK 486
#define NUM_GACK_BLOCKS 487
#define NUM_DUP_TSNS 488
#define LOWEST_TSN 489
#define SEQNO 490
#define NEW_CUM_TSN 491
#define VTAG 492
#define RT 493
#define RT0 494
#define RT2 495
#define RT4 496
#define SEG_LEFT 497
#define ADDR 498
#define LAST_ENT 499
#define TAG 500
#define SID 501
#define HBH 502
#define FRAG 503
#define RESERVED2 504
#define MORE_FRAGMENTS 505
#define DST 506
#define MH 507
#define META 508
#define MARK 509
#define IIF 510
#define IIFNAME 511
#define IIFTYPE 512
#define OIF 513
#define OIFNAME 514
#define OIFTYPE 515
#define SKUID 516
#define SKGID 517
#define NFTRACE 518
#define RTCLASSID 519
#define IBRIPORT 520
#define OBRIPORT 521
#define IBRIDGENAME 522
#define OBRIDGENAME 523
#define PKTTYPE 524
#define CPU 525
#define IIFGROUP 526
#define OIFGROUP 527
#define CGROUP 528
#define TIME 529
#define CLASSID 530
#define NEXTHOP 531
#define CT 532
#define L3PROTOCOL 533
#define PROTO_SRC 534
#define PROTO_DST 535
#define ZONE 536
#define DIRECTION 537
#define EVENT 538
#define EXPECTATION 539
#define EXPIRATION 540
#define HELPER 541
#define LABEL 542
#define STATE 543
#define STATUS 544
#define ORIGINAL 545
#define REPLY 546
#define COUNTER 547
#define NAME 548
#define PACKETS 549
#define BYTES 550
#define AVGPKT 551
#define LAST 552
#define NEVER 553
#define COUNTERS 554
#define QUOTAS 555
#define LIMITS 556
#define SYNPROXYS 557
#define HELPERS 558
#define LOG 559
#define PREFIX 560
#define GROUP 561
#define SNAPLEN 562
#define QUEUE_THRESHOLD 563
#define LEVEL 564
#define LIMIT 565
#define RATE 566
#define BURST 567
#define OVER 568
#define UNTIL 569
#define QUOTA 570
#define USED 571
#define SECMARK 572
#define SECMARKS 573
#define SECOND 574
#define MINUTE 575
#define HOUR 576
#define DAY 577
#define WEEK 578
#define _REJECT 579
#define WITH 580
#define ICMPX 581
#define SNAT 582
#define DNAT 583
#define MASQUERADE 584
#define REDIRECT 585
#define RANDOM 586
#define FULLY_RANDOM 587
#define PERSISTENT 588
#define QUEUE 589
#define QUEUENUM 590
#define BYPASS 591
#define FANOUT 592
#define DUP 593
#define FWD 594
#define NUMGEN 595
#define INC 596
#define MOD 597
#define OFFSET 598
#define JHASH 599
#define SYMHASH 600
#define SEED 601
#define POSITION 602
#define INDEX 603
#define COMMENT 604
#define XML 605
#define JSON 606
#define VM 607
#define NOTRACK 608
#define EXISTS 609
#define MISSING 610
#define EXTHDR 611
#define IPSEC 612
#define REQID 613
#define SPNUM 614
#define IN 615
#define OUT 616
#define XT 617

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 205 "parser_bison.y"

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
	struct limit_rate	limit_rate;
	struct tcp_kind_field {
		uint16_t kind; /* must allow > 255 for SACK1, 2.. hack */
		uint8_t field;
	} tcp_kind_field;

#line 1056 "parser_bison.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int nft_parse (struct nft_ctx *nft, void *scanner, struct parser_state *state);

#endif /* !YY_NFT_PARSER_BISON_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_JUNK = 3,                       /* "junk"  */
  YYSYMBOL_NEWLINE = 4,                    /* "newline"  */
  YYSYMBOL_COLON = 5,                      /* "colon"  */
  YYSYMBOL_SEMICOLON = 6,                  /* "semicolon"  */
  YYSYMBOL_COMMA = 7,                      /* "comma"  */
  YYSYMBOL_DOT = 8,                        /* "."  */
  YYSYMBOL_EQ = 9,                         /* "=="  */
  YYSYMBOL_NEQ = 10,                       /* "!="  */
  YYSYMBOL_LT = 11,                        /* "<"  */
  YYSYMBOL_GT = 12,                        /* ">"  */
  YYSYMBOL_GTE = 13,                       /* ">="  */
  YYSYMBOL_LTE = 14,                       /* "<="  */
  YYSYMBOL_LSHIFT = 15,                    /* "<<"  */
  YYSYMBOL_RSHIFT = 16,                    /* ">>"  */
  YYSYMBOL_AMPERSAND = 17,                 /* "&"  */
  YYSYMBOL_CARET = 18,                     /* "^"  */
  YYSYMBOL_NOT = 19,                       /* "!"  */
  YYSYMBOL_SLASH = 20,                     /* "/"  */
  YYSYMBOL_ASTERISK = 21,                  /* "*"  */
  YYSYMBOL_DASH = 22,                      /* "-"  */
  YYSYMBOL_AT = 23,                        /* "@"  */
  YYSYMBOL_VMAP = 24,                      /* "vmap"  */
  YYSYMBOL_PLUS = 25,                      /* "+"  */
  YYSYMBOL_INCLUDE = 26,                   /* "include"  */
  YYSYMBOL_DEFINE = 27,                    /* "define"  */
  YYSYMBOL_REDEFINE = 28,                  /* "redefine"  */
  YYSYMBOL_UNDEFINE = 29,                  /* "undefine"  */
  YYSYMBOL_FIB = 30,                       /* "fib"  */
  YYSYMBOL_SOCKET = 31,                    /* "socket"  */
  YYSYMBOL_TRANSPARENT = 32,               /* "transparent"  */
  YYSYMBOL_WILDCARD = 33,                  /* "wildcard"  */
  YYSYMBOL_CGROUPV2 = 34,                  /* "cgroupv2"  */
  YYSYMBOL_TPROXY = 35,                    /* "tproxy"  */
  YYSYMBOL_OSF = 36,                       /* "osf"  */
  YYSYMBOL_SYNPROXY = 37,                  /* "synproxy"  */
  YYSYMBOL_MSS = 38,                       /* "mss"  */
  YYSYMBOL_WSCALE = 39,                    /* "wscale"  */
  YYSYMBOL_TYPEOF = 40,                    /* "typeof"  */
  YYSYMBOL_HOOK = 41,                      /* "hook"  */
  YYSYMBOL_HOOKS = 42,                     /* "hooks"  */
  YYSYMBOL_DEVICE = 43,                    /* "device"  */
  YYSYMBOL_DEVICES = 44,                   /* "devices"  */
  YYSYMBOL_TABLE = 45,                     /* "table"  */
  YYSYMBOL_TABLES = 46,                    /* "tables"  */
  YYSYMBOL_CHAIN = 47,                     /* "chain"  */
  YYSYMBOL_CHAINS = 48,                    /* "chains"  */
  YYSYMBOL_RULE = 49,                      /* "rule"  */
  YYSYMBOL_RULES = 50,                     /* "rules"  */
  YYSYMBOL_SETS = 51,                      /* "sets"  */
  YYSYMBOL_SET = 52,                       /* "set"  */
  YYSYMBOL_ELEMENT = 53,                   /* "element"  */
  YYSYMBOL_MAP = 54,                       /* "map"  */
  YYSYMBOL_MAPS = 55,                      /* "maps"  */
  YYSYMBOL_FLOWTABLE = 56,                 /* "flowtable"  */
  YYSYMBOL_HANDLE = 57,                    /* "handle"  */
  YYSYMBOL_RULESET = 58,                   /* "ruleset"  */
  YYSYMBOL_TRACE = 59,                     /* "trace"  */
  YYSYMBOL_INET = 60,                      /* "inet"  */
  YYSYMBOL_NETDEV = 61,                    /* "netdev"  */
  YYSYMBOL_ADD = 62,                       /* "add"  */
  YYSYMBOL_UPDATE = 63,                    /* "update"  */
  YYSYMBOL_REPLACE = 64,                   /* "replace"  */
  YYSYMBOL_CREATE = 65,                    /* "create"  */
  YYSYMBOL_INSERT = 66,                    /* "insert"  */
  YYSYMBOL_DELETE = 67,                    /* "delete"  */
  YYSYMBOL_GET = 68,                       /* "get"  */
  YYSYMBOL_LIST = 69,                      /* "list"  */
  YYSYMBOL_RESET = 70,                     /* "reset"  */
  YYSYMBOL_FLUSH = 71,                     /* "flush"  */
  YYSYMBOL_RENAME = 72,                    /* "rename"  */
  YYSYMBOL_DESCRIBE = 73,                  /* "describe"  */
  YYSYMBOL_IMPORT = 74,                    /* "import"  */
  YYSYMBOL_EXPORT = 75,                    /* "export"  */
  YYSYMBOL_DESTROY = 76,                   /* "destroy"  */
  YYSYMBOL_MONITOR = 77,                   /* "monitor"  */
  YYSYMBOL_ALL = 78,                       /* "all"  */
  YYSYMBOL_ACCEPT = 79,                    /* "accept"  */
  YYSYMBOL_DROP = 80,                      /* "drop"  */
  YYSYMBOL_CONTINUE = 81,                  /* "continue"  */
  YYSYMBOL_JUMP = 82,                      /* "jump"  */
  YYSYMBOL_GOTO = 83,                      /* "goto"  */
  YYSYMBOL_RETURN = 84,                    /* "return"  */
  YYSYMBOL_TO = 85,                        /* "to"  */
  YYSYMBOL_CONSTANT = 86,                  /* "constant"  */
  YYSYMBOL_INTERVAL = 87,                  /* "interval"  */
  YYSYMBOL_DYNAMIC = 88,                   /* "dynamic"  */
  YYSYMBOL_AUTOMERGE = 89,                 /* "auto-merge"  */
  YYSYMBOL_TIMEOUT = 90,                   /* "timeout"  */
  YYSYMBOL_GC_INTERVAL = 91,               /* "gc-interval"  */
  YYSYMBOL_ELEMENTS = 92,                  /* "elements"  */
  YYSYMBOL_EXPIRES = 93,                   /* "expires"  */
  YYSYMBOL_POLICY = 94,                    /* "policy"  */
  YYSYMBOL_MEMORY = 95,                    /* "memory"  */
  YYSYMBOL_PERFORMANCE = 96,               /* "performance"  */
  YYSYMBOL_SIZE = 97,                      /* "size"  */
  YYSYMBOL_FLOW = 98,                      /* "flow"  */
  YYSYMBOL_OFFLOAD = 99,                   /* "offload"  */
  YYSYMBOL_METER = 100,                    /* "meter"  */
  YYSYMBOL_METERS = 101,                   /* "meters"  */
  YYSYMBOL_FLOWTABLES = 102,               /* "flowtables"  */
  YYSYMBOL_NUM = 103,                      /* "number"  */
  YYSYMBOL_STRING = 104,                   /* "string"  */
  YYSYMBOL_QUOTED_STRING = 105,            /* "quoted string"  */
  YYSYMBOL_ASTERISK_STRING = 106,          /* "string with a trailing asterisk"  */
  YYSYMBOL_LL_HDR = 107,                   /* "ll"  */
  YYSYMBOL_NETWORK_HDR = 108,              /* "nh"  */
  YYSYMBOL_TRANSPORT_HDR = 109,            /* "th"  */
  YYSYMBOL_BRIDGE = 110,                   /* "bridge"  */
  YYSYMBOL_ETHER = 111,                    /* "ether"  */
  YYSYMBOL_SADDR = 112,                    /* "saddr"  */
  YYSYMBOL_DADDR = 113,                    /* "daddr"  */
  YYSYMBOL_TYPE = 114,                     /* "type"  */
  YYSYMBOL_VLAN = 115,                     /* "vlan"  */
  YYSYMBOL_ID = 116,                       /* "id"  */
  YYSYMBOL_CFI = 117,                      /* "cfi"  */
  YYSYMBOL_DEI = 118,                      /* "dei"  */
  YYSYMBOL_PCP = 119,                      /* "pcp"  */
  YYSYMBOL_ARP = 120,                      /* "arp"  */
  YYSYMBOL_HTYPE = 121,                    /* "htype"  */
  YYSYMBOL_PTYPE = 122,                    /* "ptype"  */
  YYSYMBOL_HLEN = 123,                     /* "hlen"  */
  YYSYMBOL_PLEN = 124,                     /* "plen"  */
  YYSYMBOL_OPERATION = 125,                /* "operation"  */
  YYSYMBOL_IP = 126,                       /* "ip"  */
  YYSYMBOL_HDRVERSION = 127,               /* "version"  */
  YYSYMBOL_HDRLENGTH = 128,                /* "hdrlength"  */
  YYSYMBOL_DSCP = 129,                     /* "dscp"  */
  YYSYMBOL_ECN = 130,                      /* "ecn"  */
  YYSYMBOL_LENGTH = 131,                   /* "length"  */
  YYSYMBOL_FRAG_OFF = 132,                 /* "frag-off"  */
  YYSYMBOL_TTL = 133,                      /* "ttl"  */
  YYSYMBOL_PROTOCOL = 134,                 /* "protocol"  */
  YYSYMBOL_CHECKSUM = 135,                 /* "checksum"  */
  YYSYMBOL_PTR = 136,                      /* "ptr"  */
  YYSYMBOL_VALUE = 137,                    /* "value"  */
  YYSYMBOL_LSRR = 138,                     /* "lsrr"  */
  YYSYMBOL_RR = 139,                       /* "rr"  */
  YYSYMBOL_SSRR = 140,                     /* "ssrr"  */
  YYSYMBOL_RA = 141,                       /* "ra"  */
  YYSYMBOL_ICMP = 142,                     /* "icmp"  */
  YYSYMBOL_CODE = 143,                     /* "code"  */
  YYSYMBOL_SEQUENCE = 144,                 /* "seq"  */
  YYSYMBOL_GATEWAY = 145,                  /* "gateway"  */
  YYSYMBOL_MTU = 146,                      /* "mtu"  */
  YYSYMBOL_IGMP = 147,                     /* "igmp"  */
  YYSYMBOL_MRT = 148,                      /* "mrt"  */
  YYSYMBOL_OPTIONS = 149,                  /* "options"  */
  YYSYMBOL_IP6 = 150,                      /* "ip6"  */
  YYSYMBOL_PRIORITY = 151,                 /* "priority"  */
  YYSYMBOL_FLOWLABEL = 152,                /* "flowlabel"  */
  YYSYMBOL_NEXTHDR = 153,                  /* "nexthdr"  */
  YYSYMBOL_HOPLIMIT = 154,                 /* "hoplimit"  */
  YYSYMBOL_ICMP6 = 155,                    /* "icmpv6"  */
  YYSYMBOL_PPTR = 156,                     /* "param-problem"  */
  YYSYMBOL_MAXDELAY = 157,                 /* "max-delay"  */
  YYSYMBOL_TADDR = 158,                    /* "taddr"  */
  YYSYMBOL_AH = 159,                       /* "ah"  */
  YYSYMBOL_RESERVED = 160,                 /* "reserved"  */
  YYSYMBOL_SPI = 161,                      /* "spi"  */
  YYSYMBOL_ESP = 162,                      /* "esp"  */
  YYSYMBOL_COMP = 163,                     /* "comp"  */
  YYSYMBOL_FLAGS = 164,                    /* "flags"  */
  YYSYMBOL_CPI = 165,                      /* "cpi"  */
  YYSYMBOL_PORT = 166,                     /* "port"  */
  YYSYMBOL_UDP = 167,                      /* "udp"  */
  YYSYMBOL_SPORT = 168,                    /* "sport"  */
  YYSYMBOL_DPORT = 169,                    /* "dport"  */
  YYSYMBOL_UDPLITE = 170,                  /* "udplite"  */
  YYSYMBOL_CSUMCOV = 171,                  /* "csumcov"  */
  YYSYMBOL_TCP = 172,                      /* "tcp"  */
  YYSYMBOL_ACKSEQ = 173,                   /* "ackseq"  */
  YYSYMBOL_DOFF = 174,                     /* "doff"  */
  YYSYMBOL_WINDOW = 175,                   /* "window"  */
  YYSYMBOL_URGPTR = 176,                   /* "urgptr"  */
  YYSYMBOL_OPTION = 177,                   /* "option"  */
  YYSYMBOL_ECHO = 178,                     /* "echo"  */
  YYSYMBOL_EOL = 179,                      /* "eol"  */
  YYSYMBOL_MPTCP = 180,                    /* "mptcp"  */
  YYSYMBOL_NOP = 181,                      /* "nop"  */
  YYSYMBOL_SACK = 182,                     /* "sack"  */
  YYSYMBOL_SACK0 = 183,                    /* "sack0"  */
  YYSYMBOL_SACK1 = 184,                    /* "sack1"  */
  YYSYMBOL_SACK2 = 185,                    /* "sack2"  */
  YYSYMBOL_SACK3 = 186,                    /* "sack3"  */
  YYSYMBOL_SACK_PERM = 187,                /* "sack-permitted"  */
  YYSYMBOL_FASTOPEN = 188,                 /* "fastopen"  */
  YYSYMBOL_MD5SIG = 189,                   /* "md5sig"  */
  YYSYMBOL_TIMESTAMP = 190,                /* "timestamp"  */
  YYSYMBOL_COUNT = 191,                    /* "count"  */
  YYSYMBOL_LEFT = 192,                     /* "left"  */
  YYSYMBOL_RIGHT = 193,                    /* "right"  */
  YYSYMBOL_TSVAL = 194,                    /* "tsval"  */
  YYSYMBOL_TSECR = 195,                    /* "tsecr"  */
  YYSYMBOL_SUBTYPE = 196,                  /* "subtype"  */
  YYSYMBOL_DCCP = 197,                     /* "dccp"  */
  YYSYMBOL_VXLAN = 198,                    /* "vxlan"  */
  YYSYMBOL_VNI = 199,                      /* "vni"  */
  YYSYMBOL_GRE = 200,                      /* "gre"  */
  YYSYMBOL_GRETAP = 201,                   /* "gretap"  */
  YYSYMBOL_GENEVE = 202,                   /* "geneve"  */
  YYSYMBOL_SCTP = 203,                     /* "sctp"  */
  YYSYMBOL_CHUNK = 204,                    /* "chunk"  */
  YYSYMBOL_DATA = 205,                     /* "data"  */
  YYSYMBOL_INIT = 206,                     /* "init"  */
  YYSYMBOL_INIT_ACK = 207,                 /* "init-ack"  */
  YYSYMBOL_HEARTBEAT = 208,                /* "heartbeat"  */
  YYSYMBOL_HEARTBEAT_ACK = 209,            /* "heartbeat-ack"  */
  YYSYMBOL_ABORT = 210,                    /* "abort"  */
  YYSYMBOL_SHUTDOWN = 211,                 /* "shutdown"  */
  YYSYMBOL_SHUTDOWN_ACK = 212,             /* "shutdown-ack"  */
  YYSYMBOL_ERROR = 213,                    /* "error"  */
  YYSYMBOL_COOKIE_ECHO = 214,              /* "cookie-echo"  */
  YYSYMBOL_COOKIE_ACK = 215,               /* "cookie-ack"  */
  YYSYMBOL_ECNE = 216,                     /* "ecne"  */
  YYSYMBOL_CWR = 217,                      /* "cwr"  */
  YYSYMBOL_SHUTDOWN_COMPLETE = 218,        /* "shutdown-complete"  */
  YYSYMBOL_ASCONF_ACK = 219,               /* "asconf-ack"  */
  YYSYMBOL_FORWARD_TSN = 220,              /* "forward-tsn"  */
  YYSYMBOL_ASCONF = 221,                   /* "asconf"  */
  YYSYMBOL_TSN = 222,                      /* "tsn"  */
  YYSYMBOL_STREAM = 223,                   /* "stream"  */
  YYSYMBOL_SSN = 224,                      /* "ssn"  */
  YYSYMBOL_PPID = 225,                     /* "ppid"  */
  YYSYMBOL_INIT_TAG = 226,                 /* "init-tag"  */
  YYSYMBOL_A_RWND = 227,                   /* "a-rwnd"  */
  YYSYMBOL_NUM_OSTREAMS = 228,             /* "num-outbound-streams"  */
  YYSYMBOL_NUM_ISTREAMS = 229,             /* "num-inbound-streams"  */
  YYSYMBOL_INIT_TSN = 230,                 /* "initial-tsn"  */
  YYSYMBOL_CUM_TSN_ACK = 231,              /* "cum-tsn-ack"  */
  YYSYMBOL_NUM_GACK_BLOCKS = 232,          /* "num-gap-ack-blocks"  */
  YYSYMBOL_NUM_DUP_TSNS = 233,             /* "num-dup-tsns"  */
  YYSYMBOL_LOWEST_TSN = 234,               /* "lowest-tsn"  */
  YYSYMBOL_SEQNO = 235,                    /* "seqno"  */
  YYSYMBOL_NEW_CUM_TSN = 236,              /* "new-cum-tsn"  */
  YYSYMBOL_VTAG = 237,                     /* "vtag"  */
  YYSYMBOL_RT = 238,                       /* "rt"  */
  YYSYMBOL_RT0 = 239,                      /* "rt0"  */
  YYSYMBOL_RT2 = 240,                      /* "rt2"  */
  YYSYMBOL_RT4 = 241,                      /* "srh"  */
  YYSYMBOL_SEG_LEFT = 242,                 /* "seg-left"  */
  YYSYMBOL_ADDR = 243,                     /* "addr"  */
  YYSYMBOL_LAST_ENT = 244,                 /* "last-entry"  */
  YYSYMBOL_TAG = 245,                      /* "tag"  */
  YYSYMBOL_SID = 246,                      /* "sid"  */
  YYSYMBOL_HBH = 247,                      /* "hbh"  */
  YYSYMBOL_FRAG = 248,                     /* "frag"  */
  YYSYMBOL_RESERVED2 = 249,                /* "reserved2"  */
  YYSYMBOL_MORE_FRAGMENTS = 250,           /* "more-fragments"  */
  YYSYMBOL_DST = 251,                      /* "dst"  */
  YYSYMBOL_MH = 252,                       /* "mh"  */
  YYSYMBOL_META = 253,                     /* "meta"  */
  YYSYMBOL_MARK = 254,                     /* "mark"  */
  YYSYMBOL_IIF = 255,                      /* "iif"  */
  YYSYMBOL_IIFNAME = 256,                  /* "iifname"  */
  YYSYMBOL_IIFTYPE = 257,                  /* "iiftype"  */
  YYSYMBOL_OIF = 258,                      /* "oif"  */
  YYSYMBOL_OIFNAME = 259,                  /* "oifname"  */
  YYSYMBOL_OIFTYPE = 260,                  /* "oiftype"  */
  YYSYMBOL_SKUID = 261,                    /* "skuid"  */
  YYSYMBOL_SKGID = 262,                    /* "skgid"  */
  YYSYMBOL_NFTRACE = 263,                  /* "nftrace"  */
  YYSYMBOL_RTCLASSID = 264,                /* "rtclassid"  */
  YYSYMBOL_IBRIPORT = 265,                 /* "ibriport"  */
  YYSYMBOL_OBRIPORT = 266,                 /* "obriport"  */
  YYSYMBOL_IBRIDGENAME = 267,              /* "ibrname"  */
  YYSYMBOL_OBRIDGENAME = 268,              /* "obrname"  */
  YYSYMBOL_PKTTYPE = 269,                  /* "pkttype"  */
  YYSYMBOL_CPU = 270,                      /* "cpu"  */
  YYSYMBOL_IIFGROUP = 271,                 /* "iifgroup"  */
  YYSYMBOL_OIFGROUP = 272,                 /* "oifgroup"  */
  YYSYMBOL_CGROUP = 273,                   /* "cgroup"  */
  YYSYMBOL_TIME = 274,                     /* "time"  */
  YYSYMBOL_CLASSID = 275,                  /* "classid"  */
  YYSYMBOL_NEXTHOP = 276,                  /* "nexthop"  */
  YYSYMBOL_CT = 277,                       /* "ct"  */
  YYSYMBOL_L3PROTOCOL = 278,               /* "l3proto"  */
  YYSYMBOL_PROTO_SRC = 279,                /* "proto-src"  */
  YYSYMBOL_PROTO_DST = 280,                /* "proto-dst"  */
  YYSYMBOL_ZONE = 281,                     /* "zone"  */
  YYSYMBOL_DIRECTION = 282,                /* "direction"  */
  YYSYMBOL_EVENT = 283,                    /* "event"  */
  YYSYMBOL_EXPECTATION = 284,              /* "expectation"  */
  YYSYMBOL_EXPIRATION = 285,               /* "expiration"  */
  YYSYMBOL_HELPER = 286,                   /* "helper"  */
  YYSYMBOL_LABEL = 287,                    /* "label"  */
  YYSYMBOL_STATE = 288,                    /* "state"  */
  YYSYMBOL_STATUS = 289,                   /* "status"  */
  YYSYMBOL_ORIGINAL = 290,                 /* "original"  */
  YYSYMBOL_REPLY = 291,                    /* "reply"  */
  YYSYMBOL_COUNTER = 292,                  /* "counter"  */
  YYSYMBOL_NAME = 293,                     /* "name"  */
  YYSYMBOL_PACKETS = 294,                  /* "packets"  */
  YYSYMBOL_BYTES = 295,                    /* "bytes"  */
  YYSYMBOL_AVGPKT = 296,                   /* "avgpkt"  */
  YYSYMBOL_LAST = 297,                     /* "last"  */
  YYSYMBOL_NEVER = 298,                    /* "never"  */
  YYSYMBOL_COUNTERS = 299,                 /* "counters"  */
  YYSYMBOL_QUOTAS = 300,                   /* "quotas"  */
  YYSYMBOL_LIMITS = 301,                   /* "limits"  */
  YYSYMBOL_SYNPROXYS = 302,                /* "synproxys"  */
  YYSYMBOL_HELPERS = 303,                  /* "helpers"  */
  YYSYMBOL_LOG = 304,                      /* "log"  */
  YYSYMBOL_PREFIX = 305,                   /* "prefix"  */
  YYSYMBOL_GROUP = 306,                    /* "group"  */
  YYSYMBOL_SNAPLEN = 307,                  /* "snaplen"  */
  YYSYMBOL_QUEUE_THRESHOLD = 308,          /* "queue-threshold"  */
  YYSYMBOL_LEVEL = 309,                    /* "level"  */
  YYSYMBOL_LIMIT = 310,                    /* "limit"  */
  YYSYMBOL_RATE = 311,                     /* "rate"  */
  YYSYMBOL_BURST = 312,                    /* "burst"  */
  YYSYMBOL_OVER = 313,                     /* "over"  */
  YYSYMBOL_UNTIL = 314,                    /* "until"  */
  YYSYMBOL_QUOTA = 315,                    /* "quota"  */
  YYSYMBOL_USED = 316,                     /* "used"  */
  YYSYMBOL_SECMARK = 317,                  /* "secmark"  */
  YYSYMBOL_SECMARKS = 318,                 /* "secmarks"  */
  YYSYMBOL_SECOND = 319,                   /* "second"  */
  YYSYMBOL_MINUTE = 320,                   /* "minute"  */
  YYSYMBOL_HOUR = 321,                     /* "hour"  */
  YYSYMBOL_DAY = 322,                      /* "day"  */
  YYSYMBOL_WEEK = 323,                     /* "week"  */
  YYSYMBOL__REJECT = 324,                  /* "reject"  */
  YYSYMBOL_WITH = 325,                     /* "with"  */
  YYSYMBOL_ICMPX = 326,                    /* "icmpx"  */
  YYSYMBOL_SNAT = 327,                     /* "snat"  */
  YYSYMBOL_DNAT = 328,                     /* "dnat"  */
  YYSYMBOL_MASQUERADE = 329,               /* "masquerade"  */
  YYSYMBOL_REDIRECT = 330,                 /* "redirect"  */
  YYSYMBOL_RANDOM = 331,                   /* "random"  */
  YYSYMBOL_FULLY_RANDOM = 332,             /* "fully-random"  */
  YYSYMBOL_PERSISTENT = 333,               /* "persistent"  */
  YYSYMBOL_QUEUE = 334,                    /* "queue"  */
  YYSYMBOL_QUEUENUM = 335,                 /* "num"  */
  YYSYMBOL_BYPASS = 336,                   /* "bypass"  */
  YYSYMBOL_FANOUT = 337,                   /* "fanout"  */
  YYSYMBOL_DUP = 338,                      /* "dup"  */
  YYSYMBOL_FWD = 339,                      /* "fwd"  */
  YYSYMBOL_NUMGEN = 340,                   /* "numgen"  */
  YYSYMBOL_INC = 341,                      /* "inc"  */
  YYSYMBOL_MOD = 342,                      /* "mod"  */
  YYSYMBOL_OFFSET = 343,                   /* "offset"  */
  YYSYMBOL_JHASH = 344,                    /* "jhash"  */
  YYSYMBOL_SYMHASH = 345,                  /* "symhash"  */
  YYSYMBOL_SEED = 346,                     /* "seed"  */
  YYSYMBOL_POSITION = 347,                 /* "position"  */
  YYSYMBOL_INDEX = 348,                    /* "index"  */
  YYSYMBOL_COMMENT = 349,                  /* "comment"  */
  YYSYMBOL_XML = 350,                      /* "xml"  */
  YYSYMBOL_JSON = 351,                     /* "json"  */
  YYSYMBOL_VM = 352,                       /* "vm"  */
  YYSYMBOL_NOTRACK = 353,                  /* "notrack"  */
  YYSYMBOL_EXISTS = 354,                   /* "exists"  */
  YYSYMBOL_MISSING = 355,                  /* "missing"  */
  YYSYMBOL_EXTHDR = 356,                   /* "exthdr"  */
  YYSYMBOL_IPSEC = 357,                    /* "ipsec"  */
  YYSYMBOL_REQID = 358,                    /* "reqid"  */
  YYSYMBOL_SPNUM = 359,                    /* "spnum"  */
  YYSYMBOL_IN = 360,                       /* "in"  */
  YYSYMBOL_OUT = 361,                      /* "out"  */
  YYSYMBOL_XT = 362,                       /* "xt"  */
  YYSYMBOL_363_ = 363,                     /* '='  */
  YYSYMBOL_364_ = 364,                     /* '{'  */
  YYSYMBOL_365_ = 365,                     /* '}'  */
  YYSYMBOL_366_ = 366,                     /* '('  */
  YYSYMBOL_367_ = 367,                     /* ')'  */
  YYSYMBOL_368_ = 368,                     /* '|'  */
  YYSYMBOL_369_ = 369,                     /* '$'  */
  YYSYMBOL_370_ = 370,                     /* '['  */
  YYSYMBOL_371_ = 371,                     /* ']'  */
  YYSYMBOL_YYACCEPT = 372,                 /* $accept  */
  YYSYMBOL_input = 373,                    /* input  */
  YYSYMBOL_stmt_separator = 374,           /* stmt_separator  */
  YYSYMBOL_opt_newline = 375,              /* opt_newline  */
  YYSYMBOL_close_scope_ah = 376,           /* close_scope_ah  */
  YYSYMBOL_close_scope_arp = 377,          /* close_scope_arp  */
  YYSYMBOL_close_scope_at = 378,           /* close_scope_at  */
  YYSYMBOL_close_scope_comp = 379,         /* close_scope_comp  */
  YYSYMBOL_close_scope_ct = 380,           /* close_scope_ct  */
  YYSYMBOL_close_scope_counter = 381,      /* close_scope_counter  */
  YYSYMBOL_close_scope_last = 382,         /* close_scope_last  */
  YYSYMBOL_close_scope_dccp = 383,         /* close_scope_dccp  */
  YYSYMBOL_close_scope_destroy = 384,      /* close_scope_destroy  */
  YYSYMBOL_close_scope_dst = 385,          /* close_scope_dst  */
  YYSYMBOL_close_scope_dup = 386,          /* close_scope_dup  */
  YYSYMBOL_close_scope_esp = 387,          /* close_scope_esp  */
  YYSYMBOL_close_scope_eth = 388,          /* close_scope_eth  */
  YYSYMBOL_close_scope_export = 389,       /* close_scope_export  */
  YYSYMBOL_close_scope_fib = 390,          /* close_scope_fib  */
  YYSYMBOL_close_scope_frag = 391,         /* close_scope_frag  */
  YYSYMBOL_close_scope_fwd = 392,          /* close_scope_fwd  */
  YYSYMBOL_close_scope_gre = 393,          /* close_scope_gre  */
  YYSYMBOL_close_scope_hash = 394,         /* close_scope_hash  */
  YYSYMBOL_close_scope_hbh = 395,          /* close_scope_hbh  */
  YYSYMBOL_close_scope_ip = 396,           /* close_scope_ip  */
  YYSYMBOL_close_scope_ip6 = 397,          /* close_scope_ip6  */
  YYSYMBOL_close_scope_vlan = 398,         /* close_scope_vlan  */
  YYSYMBOL_close_scope_icmp = 399,         /* close_scope_icmp  */
  YYSYMBOL_close_scope_igmp = 400,         /* close_scope_igmp  */
  YYSYMBOL_close_scope_import = 401,       /* close_scope_import  */
  YYSYMBOL_close_scope_ipsec = 402,        /* close_scope_ipsec  */
  YYSYMBOL_close_scope_list = 403,         /* close_scope_list  */
  YYSYMBOL_close_scope_limit = 404,        /* close_scope_limit  */
  YYSYMBOL_close_scope_meta = 405,         /* close_scope_meta  */
  YYSYMBOL_close_scope_mh = 406,           /* close_scope_mh  */
  YYSYMBOL_close_scope_monitor = 407,      /* close_scope_monitor  */
  YYSYMBOL_close_scope_nat = 408,          /* close_scope_nat  */
  YYSYMBOL_close_scope_numgen = 409,       /* close_scope_numgen  */
  YYSYMBOL_close_scope_osf = 410,          /* close_scope_osf  */
  YYSYMBOL_close_scope_policy = 411,       /* close_scope_policy  */
  YYSYMBOL_close_scope_quota = 412,        /* close_scope_quota  */
  YYSYMBOL_close_scope_queue = 413,        /* close_scope_queue  */
  YYSYMBOL_close_scope_reject = 414,       /* close_scope_reject  */
  YYSYMBOL_close_scope_reset = 415,        /* close_scope_reset  */
  YYSYMBOL_close_scope_rt = 416,           /* close_scope_rt  */
  YYSYMBOL_close_scope_sctp = 417,         /* close_scope_sctp  */
  YYSYMBOL_close_scope_sctp_chunk = 418,   /* close_scope_sctp_chunk  */
  YYSYMBOL_close_scope_secmark = 419,      /* close_scope_secmark  */
  YYSYMBOL_close_scope_socket = 420,       /* close_scope_socket  */
  YYSYMBOL_close_scope_tcp = 421,          /* close_scope_tcp  */
  YYSYMBOL_close_scope_tproxy = 422,       /* close_scope_tproxy  */
  YYSYMBOL_close_scope_type = 423,         /* close_scope_type  */
  YYSYMBOL_close_scope_th = 424,           /* close_scope_th  */
  YYSYMBOL_close_scope_udp = 425,          /* close_scope_udp  */
  YYSYMBOL_close_scope_udplite = 426,      /* close_scope_udplite  */
  YYSYMBOL_close_scope_log = 427,          /* close_scope_log  */
  YYSYMBOL_close_scope_synproxy = 428,     /* close_scope_synproxy  */
  YYSYMBOL_close_scope_xt = 429,           /* close_scope_xt  */
  YYSYMBOL_common_block = 430,             /* common_block  */
  YYSYMBOL_line = 431,                     /* line  */
  YYSYMBOL_base_cmd = 432,                 /* base_cmd  */
  YYSYMBOL_add_cmd = 433,                  /* add_cmd  */
  YYSYMBOL_replace_cmd = 434,              /* replace_cmd  */
  YYSYMBOL_create_cmd = 435,               /* create_cmd  */
  YYSYMBOL_insert_cmd = 436,               /* insert_cmd  */
  YYSYMBOL_table_or_id_spec = 437,         /* table_or_id_spec  */
  YYSYMBOL_chain_or_id_spec = 438,         /* chain_or_id_spec  */
  YYSYMBOL_set_or_id_spec = 439,           /* set_or_id_spec  */
  YYSYMBOL_obj_or_id_spec = 440,           /* obj_or_id_spec  */
  YYSYMBOL_delete_cmd = 441,               /* delete_cmd  */
  YYSYMBOL_destroy_cmd = 442,              /* destroy_cmd  */
  YYSYMBOL_get_cmd = 443,                  /* get_cmd  */
  YYSYMBOL_list_cmd = 444,                 /* list_cmd  */
  YYSYMBOL_basehook_device_name = 445,     /* basehook_device_name  */
  YYSYMBOL_basehook_spec = 446,            /* basehook_spec  */
  YYSYMBOL_reset_cmd = 447,                /* reset_cmd  */
  YYSYMBOL_flush_cmd = 448,                /* flush_cmd  */
  YYSYMBOL_rename_cmd = 449,               /* rename_cmd  */
  YYSYMBOL_import_cmd = 450,               /* import_cmd  */
  YYSYMBOL_export_cmd = 451,               /* export_cmd  */
  YYSYMBOL_monitor_cmd = 452,              /* monitor_cmd  */
  YYSYMBOL_monitor_event = 453,            /* monitor_event  */
  YYSYMBOL_monitor_object = 454,           /* monitor_object  */
  YYSYMBOL_monitor_format = 455,           /* monitor_format  */
  YYSYMBOL_markup_format = 456,            /* markup_format  */
  YYSYMBOL_describe_cmd = 457,             /* describe_cmd  */
  YYSYMBOL_table_block_alloc = 458,        /* table_block_alloc  */
  YYSYMBOL_table_options = 459,            /* table_options  */
  YYSYMBOL_table_block = 460,              /* table_block  */
  YYSYMBOL_chain_block_alloc = 461,        /* chain_block_alloc  */
  YYSYMBOL_chain_block = 462,              /* chain_block  */
  YYSYMBOL_subchain_block = 463,           /* subchain_block  */
  YYSYMBOL_typeof_data_expr = 464,         /* typeof_data_expr  */
  YYSYMBOL_typeof_expr = 465,              /* typeof_expr  */
  YYSYMBOL_set_block_alloc = 466,          /* set_block_alloc  */
  YYSYMBOL_set_block = 467,                /* set_block  */
  YYSYMBOL_set_block_expr = 468,           /* set_block_expr  */
  YYSYMBOL_set_flag_list = 469,            /* set_flag_list  */
  YYSYMBOL_set_flag = 470,                 /* set_flag  */
  YYSYMBOL_map_block_alloc = 471,          /* map_block_alloc  */
  YYSYMBOL_map_block_obj_type = 472,       /* map_block_obj_type  */
  YYSYMBOL_map_block_data_interval = 473,  /* map_block_data_interval  */
  YYSYMBOL_map_block = 474,                /* map_block  */
  YYSYMBOL_set_mechanism = 475,            /* set_mechanism  */
  YYSYMBOL_set_policy_spec = 476,          /* set_policy_spec  */
  YYSYMBOL_flowtable_block_alloc = 477,    /* flowtable_block_alloc  */
  YYSYMBOL_flowtable_block = 478,          /* flowtable_block  */
  YYSYMBOL_flowtable_expr = 479,           /* flowtable_expr  */
  YYSYMBOL_flowtable_list_expr = 480,      /* flowtable_list_expr  */
  YYSYMBOL_flowtable_expr_member = 481,    /* flowtable_expr_member  */
  YYSYMBOL_data_type_atom_expr = 482,      /* data_type_atom_expr  */
  YYSYMBOL_data_type_expr = 483,           /* data_type_expr  */
  YYSYMBOL_obj_block_alloc = 484,          /* obj_block_alloc  */
  YYSYMBOL_counter_block = 485,            /* counter_block  */
  YYSYMBOL_quota_block = 486,              /* quota_block  */
  YYSYMBOL_ct_helper_block = 487,          /* ct_helper_block  */
  YYSYMBOL_ct_timeout_block = 488,         /* ct_timeout_block  */
  YYSYMBOL_ct_expect_block = 489,          /* ct_expect_block  */
  YYSYMBOL_limit_block = 490,              /* limit_block  */
  YYSYMBOL_secmark_block = 491,            /* secmark_block  */
  YYSYMBOL_synproxy_block = 492,           /* synproxy_block  */
  YYSYMBOL_type_identifier = 493,          /* type_identifier  */
  YYSYMBOL_hook_spec = 494,                /* hook_spec  */
  YYSYMBOL_prio_spec = 495,                /* prio_spec  */
  YYSYMBOL_extended_prio_name = 496,       /* extended_prio_name  */
  YYSYMBOL_extended_prio_spec = 497,       /* extended_prio_spec  */
  YYSYMBOL_int_num = 498,                  /* int_num  */
  YYSYMBOL_dev_spec = 499,                 /* dev_spec  */
  YYSYMBOL_flags_spec = 500,               /* flags_spec  */
  YYSYMBOL_policy_spec = 501,              /* policy_spec  */
  YYSYMBOL_policy_expr = 502,              /* policy_expr  */
  YYSYMBOL_chain_policy = 503,             /* chain_policy  */
  YYSYMBOL_identifier = 504,               /* identifier  */
  YYSYMBOL_string = 505,                   /* string  */
  YYSYMBOL_time_spec = 506,                /* time_spec  */
  YYSYMBOL_time_spec_or_num_s = 507,       /* time_spec_or_num_s  */
  YYSYMBOL_family_spec = 508,              /* family_spec  */
  YYSYMBOL_family_spec_explicit = 509,     /* family_spec_explicit  */
  YYSYMBOL_table_spec = 510,               /* table_spec  */
  YYSYMBOL_tableid_spec = 511,             /* tableid_spec  */
  YYSYMBOL_chain_spec = 512,               /* chain_spec  */
  YYSYMBOL_chainid_spec = 513,             /* chainid_spec  */
  YYSYMBOL_chain_identifier = 514,         /* chain_identifier  */
  YYSYMBOL_set_spec = 515,                 /* set_spec  */
  YYSYMBOL_setid_spec = 516,               /* setid_spec  */
  YYSYMBOL_set_identifier = 517,           /* set_identifier  */
  YYSYMBOL_flowtable_spec = 518,           /* flowtable_spec  */
  YYSYMBOL_flowtableid_spec = 519,         /* flowtableid_spec  */
  YYSYMBOL_flowtable_identifier = 520,     /* flowtable_identifier  */
  YYSYMBOL_obj_spec = 521,                 /* obj_spec  */
  YYSYMBOL_objid_spec = 522,               /* objid_spec  */
  YYSYMBOL_obj_identifier = 523,           /* obj_identifier  */
  YYSYMBOL_handle_spec = 524,              /* handle_spec  */
  YYSYMBOL_position_spec = 525,            /* position_spec  */
  YYSYMBOL_index_spec = 526,               /* index_spec  */
  YYSYMBOL_rule_position = 527,            /* rule_position  */
  YYSYMBOL_ruleid_spec = 528,              /* ruleid_spec  */
  YYSYMBOL_comment_spec = 529,             /* comment_spec  */
  YYSYMBOL_ruleset_spec = 530,             /* ruleset_spec  */
  YYSYMBOL_rule = 531,                     /* rule  */
  YYSYMBOL_rule_alloc = 532,               /* rule_alloc  */
  YYSYMBOL_stmt_list = 533,                /* stmt_list  */
  YYSYMBOL_stateful_stmt_list = 534,       /* stateful_stmt_list  */
  YYSYMBOL_stateful_stmt = 535,            /* stateful_stmt  */
  YYSYMBOL_stmt = 536,                     /* stmt  */
  YYSYMBOL_xt_stmt = 537,                  /* xt_stmt  */
  YYSYMBOL_chain_stmt_type = 538,          /* chain_stmt_type  */
  YYSYMBOL_chain_stmt = 539,               /* chain_stmt  */
  YYSYMBOL_verdict_stmt = 540,             /* verdict_stmt  */
  YYSYMBOL_verdict_map_stmt = 541,         /* verdict_map_stmt  */
  YYSYMBOL_verdict_map_expr = 542,         /* verdict_map_expr  */
  YYSYMBOL_verdict_map_list_expr = 543,    /* verdict_map_list_expr  */
  YYSYMBOL_verdict_map_list_member_expr = 544, /* verdict_map_list_member_expr  */
  YYSYMBOL_connlimit_stmt = 545,           /* connlimit_stmt  */
  YYSYMBOL_counter_stmt = 546,             /* counter_stmt  */
  YYSYMBOL_counter_stmt_alloc = 547,       /* counter_stmt_alloc  */
  YYSYMBOL_counter_args = 548,             /* counter_args  */
  YYSYMBOL_counter_arg = 549,              /* counter_arg  */
  YYSYMBOL_last_stmt = 550,                /* last_stmt  */
  YYSYMBOL_log_stmt = 551,                 /* log_stmt  */
  YYSYMBOL_log_stmt_alloc = 552,           /* log_stmt_alloc  */
  YYSYMBOL_log_args = 553,                 /* log_args  */
  YYSYMBOL_log_arg = 554,                  /* log_arg  */
  YYSYMBOL_level_type = 555,               /* level_type  */
  YYSYMBOL_log_flags = 556,                /* log_flags  */
  YYSYMBOL_log_flags_tcp = 557,            /* log_flags_tcp  */
  YYSYMBOL_log_flag_tcp = 558,             /* log_flag_tcp  */
  YYSYMBOL_limit_stmt = 559,               /* limit_stmt  */
  YYSYMBOL_quota_mode = 560,               /* quota_mode  */
  YYSYMBOL_quota_unit = 561,               /* quota_unit  */
  YYSYMBOL_quota_used = 562,               /* quota_used  */
  YYSYMBOL_quota_stmt = 563,               /* quota_stmt  */
  YYSYMBOL_limit_mode = 564,               /* limit_mode  */
  YYSYMBOL_limit_burst_pkts = 565,         /* limit_burst_pkts  */
  YYSYMBOL_limit_rate_pkts = 566,          /* limit_rate_pkts  */
  YYSYMBOL_limit_burst_bytes = 567,        /* limit_burst_bytes  */
  YYSYMBOL_limit_rate_bytes = 568,         /* limit_rate_bytes  */
  YYSYMBOL_limit_bytes = 569,              /* limit_bytes  */
  YYSYMBOL_time_unit = 570,                /* time_unit  */
  YYSYMBOL_reject_stmt = 571,              /* reject_stmt  */
  YYSYMBOL_reject_stmt_alloc = 572,        /* reject_stmt_alloc  */
  YYSYMBOL_reject_with_expr = 573,         /* reject_with_expr  */
  YYSYMBOL_reject_opts = 574,              /* reject_opts  */
  YYSYMBOL_nat_stmt = 575,                 /* nat_stmt  */
  YYSYMBOL_nat_stmt_alloc = 576,           /* nat_stmt_alloc  */
  YYSYMBOL_tproxy_stmt = 577,              /* tproxy_stmt  */
  YYSYMBOL_synproxy_stmt = 578,            /* synproxy_stmt  */
  YYSYMBOL_synproxy_stmt_alloc = 579,      /* synproxy_stmt_alloc  */
  YYSYMBOL_synproxy_args = 580,            /* synproxy_args  */
  YYSYMBOL_synproxy_arg = 581,             /* synproxy_arg  */
  YYSYMBOL_synproxy_config = 582,          /* synproxy_config  */
  YYSYMBOL_synproxy_obj = 583,             /* synproxy_obj  */
  YYSYMBOL_synproxy_ts = 584,              /* synproxy_ts  */
  YYSYMBOL_synproxy_sack = 585,            /* synproxy_sack  */
  YYSYMBOL_primary_stmt_expr = 586,        /* primary_stmt_expr  */
  YYSYMBOL_shift_stmt_expr = 587,          /* shift_stmt_expr  */
  YYSYMBOL_and_stmt_expr = 588,            /* and_stmt_expr  */
  YYSYMBOL_exclusive_or_stmt_expr = 589,   /* exclusive_or_stmt_expr  */
  YYSYMBOL_inclusive_or_stmt_expr = 590,   /* inclusive_or_stmt_expr  */
  YYSYMBOL_basic_stmt_expr = 591,          /* basic_stmt_expr  */
  YYSYMBOL_concat_stmt_expr = 592,         /* concat_stmt_expr  */
  YYSYMBOL_map_stmt_expr_set = 593,        /* map_stmt_expr_set  */
  YYSYMBOL_map_stmt_expr = 594,            /* map_stmt_expr  */
  YYSYMBOL_prefix_stmt_expr = 595,         /* prefix_stmt_expr  */
  YYSYMBOL_range_stmt_expr = 596,          /* range_stmt_expr  */
  YYSYMBOL_multiton_stmt_expr = 597,       /* multiton_stmt_expr  */
  YYSYMBOL_stmt_expr = 598,                /* stmt_expr  */
  YYSYMBOL_nat_stmt_args = 599,            /* nat_stmt_args  */
  YYSYMBOL_masq_stmt = 600,                /* masq_stmt  */
  YYSYMBOL_masq_stmt_alloc = 601,          /* masq_stmt_alloc  */
  YYSYMBOL_masq_stmt_args = 602,           /* masq_stmt_args  */
  YYSYMBOL_redir_stmt = 603,               /* redir_stmt  */
  YYSYMBOL_redir_stmt_alloc = 604,         /* redir_stmt_alloc  */
  YYSYMBOL_redir_stmt_arg = 605,           /* redir_stmt_arg  */
  YYSYMBOL_dup_stmt = 606,                 /* dup_stmt  */
  YYSYMBOL_fwd_stmt = 607,                 /* fwd_stmt  */
  YYSYMBOL_nf_nat_flags = 608,             /* nf_nat_flags  */
  YYSYMBOL_nf_nat_flag = 609,              /* nf_nat_flag  */
  YYSYMBOL_queue_stmt = 610,               /* queue_stmt  */
  YYSYMBOL_queue_stmt_compat = 611,        /* queue_stmt_compat  */
  YYSYMBOL_queue_stmt_alloc = 612,         /* queue_stmt_alloc  */
  YYSYMBOL_queue_stmt_args = 613,          /* queue_stmt_args  */
  YYSYMBOL_queue_stmt_arg = 614,           /* queue_stmt_arg  */
  YYSYMBOL_queue_expr = 615,               /* queue_expr  */
  YYSYMBOL_queue_stmt_expr_simple = 616,   /* queue_stmt_expr_simple  */
  YYSYMBOL_queue_stmt_expr = 617,          /* queue_stmt_expr  */
  YYSYMBOL_queue_stmt_flags = 618,         /* queue_stmt_flags  */
  YYSYMBOL_queue_stmt_flag = 619,          /* queue_stmt_flag  */
  YYSYMBOL_set_elem_expr_stmt = 620,       /* set_elem_expr_stmt  */
  YYSYMBOL_set_elem_expr_stmt_alloc = 621, /* set_elem_expr_stmt_alloc  */
  YYSYMBOL_set_stmt = 622,                 /* set_stmt  */
  YYSYMBOL_set_stmt_op = 623,              /* set_stmt_op  */
  YYSYMBOL_map_stmt = 624,                 /* map_stmt  */
  YYSYMBOL_meter_stmt = 625,               /* meter_stmt  */
  YYSYMBOL_flow_stmt_legacy_alloc = 626,   /* flow_stmt_legacy_alloc  */
  YYSYMBOL_flow_stmt_opts = 627,           /* flow_stmt_opts  */
  YYSYMBOL_flow_stmt_opt = 628,            /* flow_stmt_opt  */
  YYSYMBOL_meter_stmt_alloc = 629,         /* meter_stmt_alloc  */
  YYSYMBOL_match_stmt = 630,               /* match_stmt  */
  YYSYMBOL_variable_expr = 631,            /* variable_expr  */
  YYSYMBOL_symbol_expr = 632,              /* symbol_expr  */
  YYSYMBOL_set_ref_expr = 633,             /* set_ref_expr  */
  YYSYMBOL_set_ref_symbol_expr = 634,      /* set_ref_symbol_expr  */
  YYSYMBOL_integer_expr = 635,             /* integer_expr  */
  YYSYMBOL_primary_expr = 636,             /* primary_expr  */
  YYSYMBOL_fib_expr = 637,                 /* fib_expr  */
  YYSYMBOL_fib_result = 638,               /* fib_result  */
  YYSYMBOL_fib_flag = 639,                 /* fib_flag  */
  YYSYMBOL_fib_tuple = 640,                /* fib_tuple  */
  YYSYMBOL_osf_expr = 641,                 /* osf_expr  */
  YYSYMBOL_osf_ttl = 642,                  /* osf_ttl  */
  YYSYMBOL_shift_expr = 643,               /* shift_expr  */
  YYSYMBOL_and_expr = 644,                 /* and_expr  */
  YYSYMBOL_exclusive_or_expr = 645,        /* exclusive_or_expr  */
  YYSYMBOL_inclusive_or_expr = 646,        /* inclusive_or_expr  */
  YYSYMBOL_basic_expr = 647,               /* basic_expr  */
  YYSYMBOL_concat_expr = 648,              /* concat_expr  */
  YYSYMBOL_prefix_rhs_expr = 649,          /* prefix_rhs_expr  */
  YYSYMBOL_range_rhs_expr = 650,           /* range_rhs_expr  */
  YYSYMBOL_multiton_rhs_expr = 651,        /* multiton_rhs_expr  */
  YYSYMBOL_map_expr = 652,                 /* map_expr  */
  YYSYMBOL_expr = 653,                     /* expr  */
  YYSYMBOL_set_expr = 654,                 /* set_expr  */
  YYSYMBOL_set_list_expr = 655,            /* set_list_expr  */
  YYSYMBOL_set_list_member_expr = 656,     /* set_list_member_expr  */
  YYSYMBOL_meter_key_expr = 657,           /* meter_key_expr  */
  YYSYMBOL_meter_key_expr_alloc = 658,     /* meter_key_expr_alloc  */
  YYSYMBOL_set_elem_expr = 659,            /* set_elem_expr  */
  YYSYMBOL_set_elem_key_expr = 660,        /* set_elem_key_expr  */
  YYSYMBOL_set_elem_expr_alloc = 661,      /* set_elem_expr_alloc  */
  YYSYMBOL_set_elem_options = 662,         /* set_elem_options  */
  YYSYMBOL_set_elem_option = 663,          /* set_elem_option  */
  YYSYMBOL_set_elem_expr_options = 664,    /* set_elem_expr_options  */
  YYSYMBOL_set_elem_stmt_list = 665,       /* set_elem_stmt_list  */
  YYSYMBOL_set_elem_stmt = 666,            /* set_elem_stmt  */
  YYSYMBOL_set_elem_expr_option = 667,     /* set_elem_expr_option  */
  YYSYMBOL_set_lhs_expr = 668,             /* set_lhs_expr  */
  YYSYMBOL_set_rhs_expr = 669,             /* set_rhs_expr  */
  YYSYMBOL_initializer_expr = 670,         /* initializer_expr  */
  YYSYMBOL_counter_config = 671,           /* counter_config  */
  YYSYMBOL_counter_obj = 672,              /* counter_obj  */
  YYSYMBOL_quota_config = 673,             /* quota_config  */
  YYSYMBOL_quota_obj = 674,                /* quota_obj  */
  YYSYMBOL_secmark_config = 675,           /* secmark_config  */
  YYSYMBOL_secmark_obj = 676,              /* secmark_obj  */
  YYSYMBOL_ct_obj_type = 677,              /* ct_obj_type  */
  YYSYMBOL_ct_cmd_type = 678,              /* ct_cmd_type  */
  YYSYMBOL_ct_l4protoname = 679,           /* ct_l4protoname  */
  YYSYMBOL_ct_helper_config = 680,         /* ct_helper_config  */
  YYSYMBOL_timeout_states = 681,           /* timeout_states  */
  YYSYMBOL_timeout_state = 682,            /* timeout_state  */
  YYSYMBOL_ct_timeout_config = 683,        /* ct_timeout_config  */
  YYSYMBOL_ct_expect_config = 684,         /* ct_expect_config  */
  YYSYMBOL_ct_obj_alloc = 685,             /* ct_obj_alloc  */
  YYSYMBOL_limit_config = 686,             /* limit_config  */
  YYSYMBOL_limit_obj = 687,                /* limit_obj  */
  YYSYMBOL_relational_expr = 688,          /* relational_expr  */
  YYSYMBOL_list_rhs_expr = 689,            /* list_rhs_expr  */
  YYSYMBOL_rhs_expr = 690,                 /* rhs_expr  */
  YYSYMBOL_shift_rhs_expr = 691,           /* shift_rhs_expr  */
  YYSYMBOL_and_rhs_expr = 692,             /* and_rhs_expr  */
  YYSYMBOL_exclusive_or_rhs_expr = 693,    /* exclusive_or_rhs_expr  */
  YYSYMBOL_inclusive_or_rhs_expr = 694,    /* inclusive_or_rhs_expr  */
  YYSYMBOL_basic_rhs_expr = 695,           /* basic_rhs_expr  */
  YYSYMBOL_concat_rhs_expr = 696,          /* concat_rhs_expr  */
  YYSYMBOL_boolean_keys = 697,             /* boolean_keys  */
  YYSYMBOL_boolean_expr = 698,             /* boolean_expr  */
  YYSYMBOL_keyword_expr = 699,             /* keyword_expr  */
  YYSYMBOL_primary_rhs_expr = 700,         /* primary_rhs_expr  */
  YYSYMBOL_relational_op = 701,            /* relational_op  */
  YYSYMBOL_verdict_expr = 702,             /* verdict_expr  */
  YYSYMBOL_chain_expr = 703,               /* chain_expr  */
  YYSYMBOL_meta_expr = 704,                /* meta_expr  */
  YYSYMBOL_meta_key = 705,                 /* meta_key  */
  YYSYMBOL_meta_key_qualified = 706,       /* meta_key_qualified  */
  YYSYMBOL_meta_key_unqualified = 707,     /* meta_key_unqualified  */
  YYSYMBOL_meta_stmt = 708,                /* meta_stmt  */
  YYSYMBOL_socket_expr = 709,              /* socket_expr  */
  YYSYMBOL_socket_key = 710,               /* socket_key  */
  YYSYMBOL_offset_opt = 711,               /* offset_opt  */
  YYSYMBOL_numgen_type = 712,              /* numgen_type  */
  YYSYMBOL_numgen_expr = 713,              /* numgen_expr  */
  YYSYMBOL_xfrm_spnum = 714,               /* xfrm_spnum  */
  YYSYMBOL_xfrm_dir = 715,                 /* xfrm_dir  */
  YYSYMBOL_xfrm_state_key = 716,           /* xfrm_state_key  */
  YYSYMBOL_xfrm_state_proto_key = 717,     /* xfrm_state_proto_key  */
  YYSYMBOL_xfrm_expr = 718,                /* xfrm_expr  */
  YYSYMBOL_hash_expr = 719,                /* hash_expr  */
  YYSYMBOL_nf_key_proto = 720,             /* nf_key_proto  */
  YYSYMBOL_rt_expr = 721,                  /* rt_expr  */
  YYSYMBOL_rt_key = 722,                   /* rt_key  */
  YYSYMBOL_ct_expr = 723,                  /* ct_expr  */
  YYSYMBOL_ct_dir = 724,                   /* ct_dir  */
  YYSYMBOL_ct_key = 725,                   /* ct_key  */
  YYSYMBOL_ct_key_dir = 726,               /* ct_key_dir  */
  YYSYMBOL_ct_key_proto_field = 727,       /* ct_key_proto_field  */
  YYSYMBOL_ct_key_dir_optional = 728,      /* ct_key_dir_optional  */
  YYSYMBOL_symbol_stmt_expr = 729,         /* symbol_stmt_expr  */
  YYSYMBOL_list_stmt_expr = 730,           /* list_stmt_expr  */
  YYSYMBOL_ct_stmt = 731,                  /* ct_stmt  */
  YYSYMBOL_payload_stmt = 732,             /* payload_stmt  */
  YYSYMBOL_payload_expr = 733,             /* payload_expr  */
  YYSYMBOL_payload_raw_expr = 734,         /* payload_raw_expr  */
  YYSYMBOL_payload_base_spec = 735,        /* payload_base_spec  */
  YYSYMBOL_eth_hdr_expr = 736,             /* eth_hdr_expr  */
  YYSYMBOL_eth_hdr_field = 737,            /* eth_hdr_field  */
  YYSYMBOL_vlan_hdr_expr = 738,            /* vlan_hdr_expr  */
  YYSYMBOL_vlan_hdr_field = 739,           /* vlan_hdr_field  */
  YYSYMBOL_arp_hdr_expr = 740,             /* arp_hdr_expr  */
  YYSYMBOL_arp_hdr_field = 741,            /* arp_hdr_field  */
  YYSYMBOL_ip_hdr_expr = 742,              /* ip_hdr_expr  */
  YYSYMBOL_ip_hdr_field = 743,             /* ip_hdr_field  */
  YYSYMBOL_ip_option_type = 744,           /* ip_option_type  */
  YYSYMBOL_ip_option_field = 745,          /* ip_option_field  */
  YYSYMBOL_icmp_hdr_expr = 746,            /* icmp_hdr_expr  */
  YYSYMBOL_icmp_hdr_field = 747,           /* icmp_hdr_field  */
  YYSYMBOL_igmp_hdr_expr = 748,            /* igmp_hdr_expr  */
  YYSYMBOL_igmp_hdr_field = 749,           /* igmp_hdr_field  */
  YYSYMBOL_ip6_hdr_expr = 750,             /* ip6_hdr_expr  */
  YYSYMBOL_ip6_hdr_field = 751,            /* ip6_hdr_field  */
  YYSYMBOL_icmp6_hdr_expr = 752,           /* icmp6_hdr_expr  */
  YYSYMBOL_icmp6_hdr_field = 753,          /* icmp6_hdr_field  */
  YYSYMBOL_auth_hdr_expr = 754,            /* auth_hdr_expr  */
  YYSYMBOL_auth_hdr_field = 755,           /* auth_hdr_field  */
  YYSYMBOL_esp_hdr_expr = 756,             /* esp_hdr_expr  */
  YYSYMBOL_esp_hdr_field = 757,            /* esp_hdr_field  */
  YYSYMBOL_comp_hdr_expr = 758,            /* comp_hdr_expr  */
  YYSYMBOL_comp_hdr_field = 759,           /* comp_hdr_field  */
  YYSYMBOL_udp_hdr_expr = 760,             /* udp_hdr_expr  */
  YYSYMBOL_udp_hdr_field = 761,            /* udp_hdr_field  */
  YYSYMBOL_udplite_hdr_expr = 762,         /* udplite_hdr_expr  */
  YYSYMBOL_udplite_hdr_field = 763,        /* udplite_hdr_field  */
  YYSYMBOL_tcp_hdr_expr = 764,             /* tcp_hdr_expr  */
  YYSYMBOL_inner_inet_expr = 765,          /* inner_inet_expr  */
  YYSYMBOL_inner_eth_expr = 766,           /* inner_eth_expr  */
  YYSYMBOL_inner_expr = 767,               /* inner_expr  */
  YYSYMBOL_vxlan_hdr_expr = 768,           /* vxlan_hdr_expr  */
  YYSYMBOL_vxlan_hdr_field = 769,          /* vxlan_hdr_field  */
  YYSYMBOL_geneve_hdr_expr = 770,          /* geneve_hdr_expr  */
  YYSYMBOL_geneve_hdr_field = 771,         /* geneve_hdr_field  */
  YYSYMBOL_gre_hdr_expr = 772,             /* gre_hdr_expr  */
  YYSYMBOL_gre_hdr_field = 773,            /* gre_hdr_field  */
  YYSYMBOL_gretap_hdr_expr = 774,          /* gretap_hdr_expr  */
  YYSYMBOL_optstrip_stmt = 775,            /* optstrip_stmt  */
  YYSYMBOL_tcp_hdr_field = 776,            /* tcp_hdr_field  */
  YYSYMBOL_tcp_hdr_option_kind_and_field = 777, /* tcp_hdr_option_kind_and_field  */
  YYSYMBOL_tcp_hdr_option_sack = 778,      /* tcp_hdr_option_sack  */
  YYSYMBOL_tcp_hdr_option_type = 779,      /* tcp_hdr_option_type  */
  YYSYMBOL_tcpopt_field_sack = 780,        /* tcpopt_field_sack  */
  YYSYMBOL_tcpopt_field_window = 781,      /* tcpopt_field_window  */
  YYSYMBOL_tcpopt_field_tsopt = 782,       /* tcpopt_field_tsopt  */
  YYSYMBOL_tcpopt_field_maxseg = 783,      /* tcpopt_field_maxseg  */
  YYSYMBOL_tcpopt_field_mptcp = 784,       /* tcpopt_field_mptcp  */
  YYSYMBOL_dccp_hdr_expr = 785,            /* dccp_hdr_expr  */
  YYSYMBOL_dccp_hdr_field = 786,           /* dccp_hdr_field  */
  YYSYMBOL_sctp_chunk_type = 787,          /* sctp_chunk_type  */
  YYSYMBOL_sctp_chunk_common_field = 788,  /* sctp_chunk_common_field  */
  YYSYMBOL_sctp_chunk_data_field = 789,    /* sctp_chunk_data_field  */
  YYSYMBOL_sctp_chunk_init_field = 790,    /* sctp_chunk_init_field  */
  YYSYMBOL_sctp_chunk_sack_field = 791,    /* sctp_chunk_sack_field  */
  YYSYMBOL_sctp_chunk_alloc = 792,         /* sctp_chunk_alloc  */
  YYSYMBOL_sctp_hdr_expr = 793,            /* sctp_hdr_expr  */
  YYSYMBOL_sctp_hdr_field = 794,           /* sctp_hdr_field  */
  YYSYMBOL_th_hdr_expr = 795,              /* th_hdr_expr  */
  YYSYMBOL_th_hdr_field = 796,             /* th_hdr_field  */
  YYSYMBOL_exthdr_expr = 797,              /* exthdr_expr  */
  YYSYMBOL_hbh_hdr_expr = 798,             /* hbh_hdr_expr  */
  YYSYMBOL_hbh_hdr_field = 799,            /* hbh_hdr_field  */
  YYSYMBOL_rt_hdr_expr = 800,              /* rt_hdr_expr  */
  YYSYMBOL_rt_hdr_field = 801,             /* rt_hdr_field  */
  YYSYMBOL_rt0_hdr_expr = 802,             /* rt0_hdr_expr  */
  YYSYMBOL_rt0_hdr_field = 803,            /* rt0_hdr_field  */
  YYSYMBOL_rt2_hdr_expr = 804,             /* rt2_hdr_expr  */
  YYSYMBOL_rt2_hdr_field = 805,            /* rt2_hdr_field  */
  YYSYMBOL_rt4_hdr_expr = 806,             /* rt4_hdr_expr  */
  YYSYMBOL_rt4_hdr_field = 807,            /* rt4_hdr_field  */
  YYSYMBOL_frag_hdr_expr = 808,            /* frag_hdr_expr  */
  YYSYMBOL_frag_hdr_field = 809,           /* frag_hdr_field  */
  YYSYMBOL_dst_hdr_expr = 810,             /* dst_hdr_expr  */
  YYSYMBOL_dst_hdr_field = 811,            /* dst_hdr_field  */
  YYSYMBOL_mh_hdr_expr = 812,              /* mh_hdr_expr  */
  YYSYMBOL_mh_hdr_field = 813,             /* mh_hdr_field  */
  YYSYMBOL_exthdr_exists_expr = 814,       /* exthdr_exists_expr  */
  YYSYMBOL_exthdr_key = 815                /* exthdr_key  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   8857

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  372
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  444
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1368
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2353

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   617


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   369,     2,     2,     2,
     366,   367,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   363,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   370,     2,   371,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   364,   368,   365,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   978,   978,   979,   988,   989,   992,   993,   996,   997,
     998,   999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,
    1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,
    1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,
    1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,
    1038,  1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1048,
    1049,  1050,  1052,  1060,  1075,  1082,  1094,  1102,  1103,  1104,
    1105,  1125,  1126,  1127,  1128,  1129,  1130,  1131,  1132,  1133,
    1134,  1135,  1136,  1137,  1138,  1139,  1140,  1143,  1147,  1154,
    1158,  1166,  1170,  1174,  1181,  1188,  1192,  1199,  1208,  1212,
    1216,  1220,  1224,  1228,  1232,  1236,  1240,  1244,  1248,  1252,
    1256,  1262,  1268,  1272,  1279,  1283,  1291,  1298,  1305,  1309,
    1316,  1325,  1329,  1333,  1337,  1341,  1345,  1349,  1353,  1359,
    1365,  1366,  1369,  1370,  1373,  1374,  1377,  1378,  1381,  1385,
    1389,  1396,  1400,  1404,  1408,  1412,  1416,  1420,  1427,  1431,
    1435,  1441,  1445,  1449,  1455,  1459,  1463,  1467,  1471,  1475,
    1479,  1483,  1487,  1494,  1498,  1502,  1508,  1512,  1516,  1523,
    1529,  1533,  1537,  1541,  1545,  1549,  1553,  1557,  1561,  1565,
    1569,  1573,  1577,  1581,  1585,  1589,  1593,  1597,  1601,  1605,
    1609,  1613,  1617,  1621,  1625,  1629,  1633,  1637,  1641,  1645,
    1649,  1653,  1657,  1661,  1667,  1673,  1677,  1687,  1691,  1695,
    1700,  1704,  1708,  1712,  1717,  1721,  1725,  1729,  1734,  1738,
    1743,  1747,  1751,  1755,  1761,  1765,  1769,  1773,  1777,  1781,
    1785,  1791,  1798,  1804,  1812,  1818,  1826,  1835,  1836,  1839,
    1840,  1841,  1842,  1843,  1844,  1845,  1846,  1849,  1850,  1853,
    1854,  1855,  1858,  1867,  1877,  1892,  1902,  1903,  1904,  1905,
    1906,  1917,  1927,  1938,  1948,  1959,  1970,  1979,  1988,  1997,
    2008,  2019,  2033,  2043,  2044,  2045,  2046,  2047,  2048,  2049,
    2054,  2063,  2073,  2074,  2075,  2082,  2103,  2114,  2125,  2138,
    2143,  2144,  2145,  2146,  2151,  2157,  2162,  2167,  2172,  2178,
    2183,  2188,  2189,  2200,  2201,  2204,  2208,  2211,  2212,  2213,
    2214,  2218,  2223,  2224,  2225,  2226,  2227,  2230,  2231,  2234,
    2235,  2236,  2237,  2242,  2247,  2258,  2269,  2281,  2290,  2295,
    2301,  2306,  2315,  2318,  2322,  2328,  2329,  2333,  2338,  2339,
    2340,  2341,  2355,  2359,  2363,  2369,  2374,  2381,  2386,  2391,
    2394,  2403,  2412,  2419,  2432,  2439,  2440,  2452,  2457,  2458,
    2459,  2460,  2464,  2474,  2475,  2476,  2477,  2481,  2491,  2492,
    2493,  2494,  2498,  2509,  2513,  2514,  2515,  2519,  2529,  2530,
    2531,  2532,  2536,  2546,  2547,  2548,  2549,  2553,  2563,  2564,
    2565,  2566,  2570,  2580,  2581,  2582,  2583,  2587,  2597,  2598,
    2599,  2600,  2601,  2604,  2635,  2642,  2646,  2649,  2659,  2666,
    2677,  2690,  2705,  2706,  2709,  2720,  2726,  2730,  2733,  2739,
    2752,  2757,  2766,  2767,  2770,  2771,  2774,  2775,  2776,  2779,
    2795,  2796,  2799,  2800,  2803,  2804,  2805,  2806,  2807,  2808,
    2811,  2820,  2829,  2837,  2845,  2853,  2861,  2869,  2877,  2885,
    2893,  2901,  2909,  2917,  2925,  2933,  2941,  2949,  2953,  2958,
    2966,  2973,  2980,  2994,  2998,  3005,  3009,  3015,  3027,  3033,
    3040,  3046,  3053,  3054,  3055,  3056,  3057,  3060,  3061,  3062,
    3063,  3064,  3065,  3066,  3067,  3068,  3069,  3070,  3071,  3072,
    3073,  3074,  3075,  3076,  3077,  3078,  3079,  3080,  3081,  3084,
    3095,  3096,  3099,  3108,  3112,  3118,  3124,  3129,  3132,  3137,
    3142,  3145,  3151,  3156,  3164,  3165,  3167,  3171,  3179,  3183,
    3186,  3190,  3196,  3200,  3204,  3212,  3213,  3216,  3222,  3226,
    3229,  3354,  3359,  3364,  3369,  3374,  3380,  3410,  3414,  3418,
    3422,  3426,  3432,  3436,  3439,  3443,  3449,  3463,  3472,  3480,
    3481,  3482,  3485,  3486,  3489,  3490,  3505,  3521,  3529,  3530,
    3531,  3534,  3535,  3538,  3545,  3546,  3549,  3563,  3570,  3571,
    3586,  3587,  3588,  3589,  3590,  3593,  3596,  3602,  3608,  3612,
    3616,  3623,  3630,  3637,  3644,  3650,  3656,  3662,  3665,  3666,
    3669,  3675,  3681,  3687,  3694,  3701,  3709,  3710,  3713,  3717,
    3725,  3729,  3732,  3737,  3742,  3746,  3752,  3768,  3787,  3793,
    3794,  3800,  3801,  3807,  3808,  3809,  3810,  3811,  3812,  3813,
    3814,  3815,  3816,  3817,  3818,  3819,  3822,  3823,  3827,  3833,
    3834,  3840,  3841,  3847,  3848,  3854,  3857,  3858,  3869,  3870,
    3873,  3877,  3880,  3886,  3892,  3893,  3896,  3897,  3898,  3901,
    3905,  3909,  3914,  3919,  3924,  3930,  3934,  3938,  3942,  3948,
    3953,  3957,  3965,  3974,  3975,  3978,  3981,  3985,  3990,  3996,
    3997,  4000,  4003,  4007,  4011,  4015,  4020,  4027,  4032,  4040,
    4045,  4054,  4055,  4061,  4062,  4063,  4066,  4067,  4071,  4075,
    4081,  4082,  4085,  4091,  4095,  4098,  4103,  4109,  4110,  4113,
    4114,  4115,  4121,  4122,  4123,  4124,  4127,  4128,  4134,  4135,
    4138,  4139,  4142,  4148,  4155,  4162,  4173,  4174,  4175,  4178,
    4186,  4198,  4205,  4208,  4214,  4218,  4221,  4227,  4236,  4247,
    4253,  4279,  4280,  4289,  4290,  4293,  4302,  4313,  4314,  4315,
    4316,  4317,  4318,  4319,  4320,  4321,  4322,  4323,  4324,  4325,
    4326,  4327,  4330,  4353,  4354,  4355,  4358,  4359,  4360,  4361,
    4362,  4365,  4369,  4372,  4376,  4383,  4386,  4402,  4403,  4407,
    4413,  4414,  4420,  4421,  4427,  4428,  4434,  4437,  4438,  4449,
    4455,  4461,  4462,  4465,  4471,  4472,  4473,  4476,  4483,  4488,
    4493,  4496,  4500,  4504,  4510,  4511,  4518,  4524,  4525,  4528,
    4529,  4532,  4538,  4544,  4548,  4551,  4555,  4559,  4569,  4573,
    4576,  4582,  4589,  4593,  4599,  4613,  4627,  4632,  4638,  4654,
    4658,  4666,  4670,  4674,  4684,  4687,  4688,  4691,  4692,  4693,
    4694,  4705,  4716,  4722,  4743,  4749,  4766,  4772,  4773,  4774,
    4777,  4778,  4779,  4782,  4783,  4786,  4802,  4808,  4814,  4821,
    4834,  4842,  4850,  4856,  4860,  4864,  4868,  4872,  4879,  4884,
    4895,  4909,  4915,  4919,  4923,  4927,  4931,  4935,  4939,  4943,
    4949,  4955,  4963,  4964,  4965,  4968,  4969,  4973,  4979,  4980,
    4986,  4987,  4993,  4994,  5000,  5003,  5004,  5005,  5014,  5025,
    5026,  5029,  5037,  5038,  5039,  5040,  5041,  5042,  5043,  5044,
    5045,  5046,  5047,  5048,  5049,  5050,  5053,  5054,  5055,  5056,
    5057,  5064,  5071,  5078,  5085,  5092,  5099,  5106,  5113,  5120,
    5127,  5134,  5141,  5148,  5151,  5152,  5153,  5154,  5155,  5156,
    5157,  5160,  5164,  5168,  5172,  5176,  5180,  5186,  5187,  5197,
    5201,  5205,  5221,  5222,  5225,  5226,  5227,  5228,  5229,  5232,
    5233,  5234,  5235,  5236,  5237,  5238,  5239,  5240,  5241,  5242,
    5243,  5244,  5245,  5246,  5247,  5248,  5249,  5250,  5251,  5252,
    5253,  5254,  5255,  5258,  5278,  5282,  5296,  5300,  5304,  5310,
    5314,  5320,  5321,  5322,  5325,  5326,  5329,  5330,  5333,  5339,
    5340,  5343,  5344,  5347,  5348,  5351,  5352,  5355,  5363,  5390,
    5395,  5400,  5406,  5407,  5410,  5414,  5434,  5435,  5436,  5437,
    5440,  5444,  5448,  5454,  5455,  5458,  5459,  5460,  5461,  5462,
    5463,  5464,  5465,  5466,  5467,  5468,  5469,  5470,  5471,  5472,
    5473,  5474,  5477,  5478,  5479,  5480,  5481,  5482,  5483,  5486,
    5487,  5488,  5489,  5492,  5493,  5494,  5495,  5498,  5499,  5502,
    5508,  5516,  5529,  5536,  5542,  5548,  5557,  5558,  5559,  5560,
    5561,  5562,  5563,  5564,  5565,  5566,  5567,  5568,  5569,  5570,
    5571,  5572,  5573,  5574,  5575,  5576,  5577,  5578,  5581,  5590,
    5591,  5592,  5593,  5606,  5612,  5613,  5614,  5617,  5623,  5624,
    5625,  5626,  5627,  5630,  5636,  5637,  5638,  5639,  5640,  5641,
    5642,  5643,  5644,  5647,  5651,  5659,  5666,  5667,  5668,  5669,
    5670,  5671,  5672,  5673,  5674,  5675,  5676,  5677,  5680,  5681,
    5682,  5683,  5686,  5687,  5688,  5689,  5690,  5693,  5699,  5700,
    5701,  5702,  5703,  5704,  5705,  5708,  5714,  5715,  5716,  5717,
    5720,  5726,  5727,  5728,  5729,  5730,  5731,  5732,  5733,  5734,
    5736,  5742,  5743,  5744,  5745,  5746,  5747,  5748,  5749,  5750,
    5751,  5754,  5760,  5761,  5762,  5763,  5764,  5767,  5773,  5774,
    5777,  5783,  5784,  5785,  5788,  5794,  5795,  5796,  5797,  5800,
    5806,  5807,  5808,  5809,  5812,  5816,  5821,  5825,  5832,  5833,
    5834,  5835,  5836,  5837,  5838,  5839,  5840,  5841,  5842,  5843,
    5844,  5845,  5848,  5849,  5850,  5853,  5854,  5857,  5865,  5873,
    5874,  5877,  5885,  5893,  5894,  5897,  5901,  5908,  5909,  5910,
    5913,  5920,  5927,  5928,  5929,  5930,  5931,  5932,  5933,  5934,
    5935,  5936,  5939,  5944,  5949,  5954,  5959,  5964,  5971,  5972,
    5973,  5974,  5975,  5978,  5979,  5980,  5981,  5982,  5983,  5984,
    5985,  5986,  5987,  5988,  5989,  5998,  5999,  6002,  6005,  6006,
    6009,  6012,  6015,  6019,  6030,  6031,  6032,  6035,  6036,  6037,
    6038,  6039,  6040,  6041,  6042,  6043,  6044,  6045,  6046,  6047,
    6048,  6049,  6050,  6051,  6052,  6055,  6056,  6057,  6060,  6061,
    6062,  6063,  6066,  6067,  6068,  6069,  6070,  6073,  6074,  6075,
    6076,  6079,  6084,  6088,  6092,  6096,  6100,  6104,  6109,  6114,
    6119,  6124,  6129,  6136,  6140,  6146,  6147,  6148,  6149,  6152,
    6160,  6161,  6164,  6165,  6166,  6167,  6168,  6169,  6170,  6171,
    6174,  6180,  6181,  6184,  6190,  6191,  6192,  6193,  6196,  6202,
    6208,  6214,  6217,  6223,  6224,  6225,  6226,  6232,  6238,  6239,
    6240,  6241,  6242,  6243,  6246,  6252,  6253,  6256,  6262,  6263,
    6264,  6265,  6266,  6269,  6283,  6284,  6285,  6286,  6287
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"junk\"",
  "\"newline\"", "\"colon\"", "\"semicolon\"", "\"comma\"", "\".\"",
  "\"==\"", "\"!=\"", "\"<\"", "\">\"", "\">=\"", "\"<=\"", "\"<<\"",
  "\">>\"", "\"&\"", "\"^\"", "\"!\"", "\"/\"", "\"*\"", "\"-\"", "\"@\"",
  "\"vmap\"", "\"+\"", "\"include\"", "\"define\"", "\"redefine\"",
  "\"undefine\"", "\"fib\"", "\"socket\"", "\"transparent\"",
  "\"wildcard\"", "\"cgroupv2\"", "\"tproxy\"", "\"osf\"", "\"synproxy\"",
  "\"mss\"", "\"wscale\"", "\"typeof\"", "\"hook\"", "\"hooks\"",
  "\"device\"", "\"devices\"", "\"table\"", "\"tables\"", "\"chain\"",
  "\"chains\"", "\"rule\"", "\"rules\"", "\"sets\"", "\"set\"",
  "\"element\"", "\"map\"", "\"maps\"", "\"flowtable\"", "\"handle\"",
  "\"ruleset\"", "\"trace\"", "\"inet\"", "\"netdev\"", "\"add\"",
  "\"update\"", "\"replace\"", "\"create\"", "\"insert\"", "\"delete\"",
  "\"get\"", "\"list\"", "\"reset\"", "\"flush\"", "\"rename\"",
  "\"describe\"", "\"import\"", "\"export\"", "\"destroy\"", "\"monitor\"",
  "\"all\"", "\"accept\"", "\"drop\"", "\"continue\"", "\"jump\"",
  "\"goto\"", "\"return\"", "\"to\"", "\"constant\"", "\"interval\"",
  "\"dynamic\"", "\"auto-merge\"", "\"timeout\"", "\"gc-interval\"",
  "\"elements\"", "\"expires\"", "\"policy\"", "\"memory\"",
  "\"performance\"", "\"size\"", "\"flow\"", "\"offload\"", "\"meter\"",
  "\"meters\"", "\"flowtables\"", "\"number\"", "\"string\"",
  "\"quoted string\"", "\"string with a trailing asterisk\"", "\"ll\"",
  "\"nh\"", "\"th\"", "\"bridge\"", "\"ether\"", "\"saddr\"", "\"daddr\"",
  "\"type\"", "\"vlan\"", "\"id\"", "\"cfi\"", "\"dei\"", "\"pcp\"",
  "\"arp\"", "\"htype\"", "\"ptype\"", "\"hlen\"", "\"plen\"",
  "\"operation\"", "\"ip\"", "\"version\"", "\"hdrlength\"", "\"dscp\"",
  "\"ecn\"", "\"length\"", "\"frag-off\"", "\"ttl\"", "\"protocol\"",
  "\"checksum\"", "\"ptr\"", "\"value\"", "\"lsrr\"", "\"rr\"", "\"ssrr\"",
  "\"ra\"", "\"icmp\"", "\"code\"", "\"seq\"", "\"gateway\"", "\"mtu\"",
  "\"igmp\"", "\"mrt\"", "\"options\"", "\"ip6\"", "\"priority\"",
  "\"flowlabel\"", "\"nexthdr\"", "\"hoplimit\"", "\"icmpv6\"",
  "\"param-problem\"", "\"max-delay\"", "\"taddr\"", "\"ah\"",
  "\"reserved\"", "\"spi\"", "\"esp\"", "\"comp\"", "\"flags\"", "\"cpi\"",
  "\"port\"", "\"udp\"", "\"sport\"", "\"dport\"", "\"udplite\"",
  "\"csumcov\"", "\"tcp\"", "\"ackseq\"", "\"doff\"", "\"window\"",
  "\"urgptr\"", "\"option\"", "\"echo\"", "\"eol\"", "\"mptcp\"",
  "\"nop\"", "\"sack\"", "\"sack0\"", "\"sack1\"", "\"sack2\"",
  "\"sack3\"", "\"sack-permitted\"", "\"fastopen\"", "\"md5sig\"",
  "\"timestamp\"", "\"count\"", "\"left\"", "\"right\"", "\"tsval\"",
  "\"tsecr\"", "\"subtype\"", "\"dccp\"", "\"vxlan\"", "\"vni\"",
  "\"gre\"", "\"gretap\"", "\"geneve\"", "\"sctp\"", "\"chunk\"",
  "\"data\"", "\"init\"", "\"init-ack\"", "\"heartbeat\"",
  "\"heartbeat-ack\"", "\"abort\"", "\"shutdown\"", "\"shutdown-ack\"",
  "\"error\"", "\"cookie-echo\"", "\"cookie-ack\"", "\"ecne\"", "\"cwr\"",
  "\"shutdown-complete\"", "\"asconf-ack\"", "\"forward-tsn\"",
  "\"asconf\"", "\"tsn\"", "\"stream\"", "\"ssn\"", "\"ppid\"",
  "\"init-tag\"", "\"a-rwnd\"", "\"num-outbound-streams\"",
  "\"num-inbound-streams\"", "\"initial-tsn\"", "\"cum-tsn-ack\"",
  "\"num-gap-ack-blocks\"", "\"num-dup-tsns\"", "\"lowest-tsn\"",
  "\"seqno\"", "\"new-cum-tsn\"", "\"vtag\"", "\"rt\"", "\"rt0\"",
  "\"rt2\"", "\"srh\"", "\"seg-left\"", "\"addr\"", "\"last-entry\"",
  "\"tag\"", "\"sid\"", "\"hbh\"", "\"frag\"", "\"reserved2\"",
  "\"more-fragments\"", "\"dst\"", "\"mh\"", "\"meta\"", "\"mark\"",
  "\"iif\"", "\"iifname\"", "\"iiftype\"", "\"oif\"", "\"oifname\"",
  "\"oiftype\"", "\"skuid\"", "\"skgid\"", "\"nftrace\"", "\"rtclassid\"",
  "\"ibriport\"", "\"obriport\"", "\"ibrname\"", "\"obrname\"",
  "\"pkttype\"", "\"cpu\"", "\"iifgroup\"", "\"oifgroup\"", "\"cgroup\"",
  "\"time\"", "\"classid\"", "\"nexthop\"", "\"ct\"", "\"l3proto\"",
  "\"proto-src\"", "\"proto-dst\"", "\"zone\"", "\"direction\"",
  "\"event\"", "\"expectation\"", "\"expiration\"", "\"helper\"",
  "\"label\"", "\"state\"", "\"status\"", "\"original\"", "\"reply\"",
  "\"counter\"", "\"name\"", "\"packets\"", "\"bytes\"", "\"avgpkt\"",
  "\"last\"", "\"never\"", "\"counters\"", "\"quotas\"", "\"limits\"",
  "\"synproxys\"", "\"helpers\"", "\"log\"", "\"prefix\"", "\"group\"",
  "\"snaplen\"", "\"queue-threshold\"", "\"level\"", "\"limit\"",
  "\"rate\"", "\"burst\"", "\"over\"", "\"until\"", "\"quota\"",
  "\"used\"", "\"secmark\"", "\"secmarks\"", "\"second\"", "\"minute\"",
  "\"hour\"", "\"day\"", "\"week\"", "\"reject\"", "\"with\"", "\"icmpx\"",
  "\"snat\"", "\"dnat\"", "\"masquerade\"", "\"redirect\"", "\"random\"",
  "\"fully-random\"", "\"persistent\"", "\"queue\"", "\"num\"",
  "\"bypass\"", "\"fanout\"", "\"dup\"", "\"fwd\"", "\"numgen\"",
  "\"inc\"", "\"mod\"", "\"offset\"", "\"jhash\"", "\"symhash\"",
  "\"seed\"", "\"position\"", "\"index\"", "\"comment\"", "\"xml\"",
  "\"json\"", "\"vm\"", "\"notrack\"", "\"exists\"", "\"missing\"",
  "\"exthdr\"", "\"ipsec\"", "\"reqid\"", "\"spnum\"", "\"in\"", "\"out\"",
  "\"xt\"", "'='", "'{'", "'}'", "'('", "')'", "'|'", "'$'", "'['", "']'",
  "$accept", "input", "stmt_separator", "opt_newline", "close_scope_ah",
  "close_scope_arp", "close_scope_at", "close_scope_comp",
  "close_scope_ct", "close_scope_counter", "close_scope_last",
  "close_scope_dccp", "close_scope_destroy", "close_scope_dst",
  "close_scope_dup", "close_scope_esp", "close_scope_eth",
  "close_scope_export", "close_scope_fib", "close_scope_frag",
  "close_scope_fwd", "close_scope_gre", "close_scope_hash",
  "close_scope_hbh", "close_scope_ip", "close_scope_ip6",
  "close_scope_vlan", "close_scope_icmp", "close_scope_igmp",
  "close_scope_import", "close_scope_ipsec", "close_scope_list",
  "close_scope_limit", "close_scope_meta", "close_scope_mh",
  "close_scope_monitor", "close_scope_nat", "close_scope_numgen",
  "close_scope_osf", "close_scope_policy", "close_scope_quota",
  "close_scope_queue", "close_scope_reject", "close_scope_reset",
  "close_scope_rt", "close_scope_sctp", "close_scope_sctp_chunk",
  "close_scope_secmark", "close_scope_socket", "close_scope_tcp",
  "close_scope_tproxy", "close_scope_type", "close_scope_th",
  "close_scope_udp", "close_scope_udplite", "close_scope_log",
  "close_scope_synproxy", "close_scope_xt", "common_block", "line",
  "base_cmd", "add_cmd", "replace_cmd", "create_cmd", "insert_cmd",
  "table_or_id_spec", "chain_or_id_spec", "set_or_id_spec",
  "obj_or_id_spec", "delete_cmd", "destroy_cmd", "get_cmd", "list_cmd",
  "basehook_device_name", "basehook_spec", "reset_cmd", "flush_cmd",
  "rename_cmd", "import_cmd", "export_cmd", "monitor_cmd", "monitor_event",
  "monitor_object", "monitor_format", "markup_format", "describe_cmd",
  "table_block_alloc", "table_options", "table_block", "chain_block_alloc",
  "chain_block", "subchain_block", "typeof_data_expr", "typeof_expr",
  "set_block_alloc", "set_block", "set_block_expr", "set_flag_list",
  "set_flag", "map_block_alloc", "map_block_obj_type",
  "map_block_data_interval", "map_block", "set_mechanism",
  "set_policy_spec", "flowtable_block_alloc", "flowtable_block",
  "flowtable_expr", "flowtable_list_expr", "flowtable_expr_member",
  "data_type_atom_expr", "data_type_expr", "obj_block_alloc",
  "counter_block", "quota_block", "ct_helper_block", "ct_timeout_block",
  "ct_expect_block", "limit_block", "secmark_block", "synproxy_block",
  "type_identifier", "hook_spec", "prio_spec", "extended_prio_name",
  "extended_prio_spec", "int_num", "dev_spec", "flags_spec", "policy_spec",
  "policy_expr", "chain_policy", "identifier", "string", "time_spec",
  "time_spec_or_num_s", "family_spec", "family_spec_explicit",
  "table_spec", "tableid_spec", "chain_spec", "chainid_spec",
  "chain_identifier", "set_spec", "setid_spec", "set_identifier",
  "flowtable_spec", "flowtableid_spec", "flowtable_identifier", "obj_spec",
  "objid_spec", "obj_identifier", "handle_spec", "position_spec",
  "index_spec", "rule_position", "ruleid_spec", "comment_spec",
  "ruleset_spec", "rule", "rule_alloc", "stmt_list", "stateful_stmt_list",
  "stateful_stmt", "stmt", "xt_stmt", "chain_stmt_type", "chain_stmt",
  "verdict_stmt", "verdict_map_stmt", "verdict_map_expr",
  "verdict_map_list_expr", "verdict_map_list_member_expr",
  "connlimit_stmt", "counter_stmt", "counter_stmt_alloc", "counter_args",
  "counter_arg", "last_stmt", "log_stmt", "log_stmt_alloc", "log_args",
  "log_arg", "level_type", "log_flags", "log_flags_tcp", "log_flag_tcp",
  "limit_stmt", "quota_mode", "quota_unit", "quota_used", "quota_stmt",
  "limit_mode", "limit_burst_pkts", "limit_rate_pkts", "limit_burst_bytes",
  "limit_rate_bytes", "limit_bytes", "time_unit", "reject_stmt",
  "reject_stmt_alloc", "reject_with_expr", "reject_opts", "nat_stmt",
  "nat_stmt_alloc", "tproxy_stmt", "synproxy_stmt", "synproxy_stmt_alloc",
  "synproxy_args", "synproxy_arg", "synproxy_config", "synproxy_obj",
  "synproxy_ts", "synproxy_sack", "primary_stmt_expr", "shift_stmt_expr",
  "and_stmt_expr", "exclusive_or_stmt_expr", "inclusive_or_stmt_expr",
  "basic_stmt_expr", "concat_stmt_expr", "map_stmt_expr_set",
  "map_stmt_expr", "prefix_stmt_expr", "range_stmt_expr",
  "multiton_stmt_expr", "stmt_expr", "nat_stmt_args", "masq_stmt",
  "masq_stmt_alloc", "masq_stmt_args", "redir_stmt", "redir_stmt_alloc",
  "redir_stmt_arg", "dup_stmt", "fwd_stmt", "nf_nat_flags", "nf_nat_flag",
  "queue_stmt", "queue_stmt_compat", "queue_stmt_alloc", "queue_stmt_args",
  "queue_stmt_arg", "queue_expr", "queue_stmt_expr_simple",
  "queue_stmt_expr", "queue_stmt_flags", "queue_stmt_flag",
  "set_elem_expr_stmt", "set_elem_expr_stmt_alloc", "set_stmt",
  "set_stmt_op", "map_stmt", "meter_stmt", "flow_stmt_legacy_alloc",
  "flow_stmt_opts", "flow_stmt_opt", "meter_stmt_alloc", "match_stmt",
  "variable_expr", "symbol_expr", "set_ref_expr", "set_ref_symbol_expr",
  "integer_expr", "primary_expr", "fib_expr", "fib_result", "fib_flag",
  "fib_tuple", "osf_expr", "osf_ttl", "shift_expr", "and_expr",
  "exclusive_or_expr", "inclusive_or_expr", "basic_expr", "concat_expr",
  "prefix_rhs_expr", "range_rhs_expr", "multiton_rhs_expr", "map_expr",
  "expr", "set_expr", "set_list_expr", "set_list_member_expr",
  "meter_key_expr", "meter_key_expr_alloc", "set_elem_expr",
  "set_elem_key_expr", "set_elem_expr_alloc", "set_elem_options",
  "set_elem_option", "set_elem_expr_options", "set_elem_stmt_list",
  "set_elem_stmt", "set_elem_expr_option", "set_lhs_expr", "set_rhs_expr",
  "initializer_expr", "counter_config", "counter_obj", "quota_config",
  "quota_obj", "secmark_config", "secmark_obj", "ct_obj_type",
  "ct_cmd_type", "ct_l4protoname", "ct_helper_config", "timeout_states",
  "timeout_state", "ct_timeout_config", "ct_expect_config", "ct_obj_alloc",
  "limit_config", "limit_obj", "relational_expr", "list_rhs_expr",
  "rhs_expr", "shift_rhs_expr", "and_rhs_expr", "exclusive_or_rhs_expr",
  "inclusive_or_rhs_expr", "basic_rhs_expr", "concat_rhs_expr",
  "boolean_keys", "boolean_expr", "keyword_expr", "primary_rhs_expr",
  "relational_op", "verdict_expr", "chain_expr", "meta_expr", "meta_key",
  "meta_key_qualified", "meta_key_unqualified", "meta_stmt", "socket_expr",
  "socket_key", "offset_opt", "numgen_type", "numgen_expr", "xfrm_spnum",
  "xfrm_dir", "xfrm_state_key", "xfrm_state_proto_key", "xfrm_expr",
  "hash_expr", "nf_key_proto", "rt_expr", "rt_key", "ct_expr", "ct_dir",
  "ct_key", "ct_key_dir", "ct_key_proto_field", "ct_key_dir_optional",
  "symbol_stmt_expr", "list_stmt_expr", "ct_stmt", "payload_stmt",
  "payload_expr", "payload_raw_expr", "payload_base_spec", "eth_hdr_expr",
  "eth_hdr_field", "vlan_hdr_expr", "vlan_hdr_field", "arp_hdr_expr",
  "arp_hdr_field", "ip_hdr_expr", "ip_hdr_field", "ip_option_type",
  "ip_option_field", "icmp_hdr_expr", "icmp_hdr_field", "igmp_hdr_expr",
  "igmp_hdr_field", "ip6_hdr_expr", "ip6_hdr_field", "icmp6_hdr_expr",
  "icmp6_hdr_field", "auth_hdr_expr", "auth_hdr_field", "esp_hdr_expr",
  "esp_hdr_field", "comp_hdr_expr", "comp_hdr_field", "udp_hdr_expr",
  "udp_hdr_field", "udplite_hdr_expr", "udplite_hdr_field", "tcp_hdr_expr",
  "inner_inet_expr", "inner_eth_expr", "inner_expr", "vxlan_hdr_expr",
  "vxlan_hdr_field", "geneve_hdr_expr", "geneve_hdr_field", "gre_hdr_expr",
  "gre_hdr_field", "gretap_hdr_expr", "optstrip_stmt", "tcp_hdr_field",
  "tcp_hdr_option_kind_and_field", "tcp_hdr_option_sack",
  "tcp_hdr_option_type", "tcpopt_field_sack", "tcpopt_field_window",
  "tcpopt_field_tsopt", "tcpopt_field_maxseg", "tcpopt_field_mptcp",
  "dccp_hdr_expr", "dccp_hdr_field", "sctp_chunk_type",
  "sctp_chunk_common_field", "sctp_chunk_data_field",
  "sctp_chunk_init_field", "sctp_chunk_sack_field", "sctp_chunk_alloc",
  "sctp_hdr_expr", "sctp_hdr_field", "th_hdr_expr", "th_hdr_field",
  "exthdr_expr", "hbh_hdr_expr", "hbh_hdr_field", "rt_hdr_expr",
  "rt_hdr_field", "rt0_hdr_expr", "rt0_hdr_field", "rt2_hdr_expr",
  "rt2_hdr_field", "rt4_hdr_expr", "rt4_hdr_field", "frag_hdr_expr",
  "frag_hdr_field", "dst_hdr_expr", "dst_hdr_field", "mh_hdr_expr",
  "mh_hdr_field", "exthdr_exists_expr", "exthdr_key", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,    61,   123,   125,    40,    41,   124,    36,
      91,    93
};
#endif

#define YYPACT_NINF (-1837)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1049)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1837,  8167, -1837,   370, -1837, -1837,   120,   257,   257,   257,
    1315,  1315,  1315,  1315,  1315,  1315,  1315,  1315, -1837, -1837,
    2577,   296,  2378,   319,  1563,   227,  2797,   881,  1594,   348,
    7783,   199,   208,  2365,   325, -1837, -1837, -1837, -1837,   577,
    1315,  1315,  1315,  1315, -1837, -1837, -1837,  1024, -1837,   257,
   -1837,   257,   134,  6943, -1837,   370, -1837, -1837,   275,   281,
     370,   257, -1837,   122,   250,  6943,   257, -1837,   323, -1837,
     257, -1837, -1837,  1315, -1837,  1315,  1315,  1315,  1315,  1315,
    1315,  1315,   578,  1315,  1315,  1315,  1315, -1837,  1315, -1837,
    1315,  1315,  1315,  1315,  1315,  1315,  1315,  1315,   612,  1315,
    1315,  1315,  1315, -1837,  1315, -1837,  1315,  1315,  1315,  1315,
    1315,  1315,  1372,  1315,  1315,  1315,  1315,  1315,   532,  1315,
    1315,  1315,   113,  1315,  2325,  2443,  2452,  2534,  1315,  1315,
    1315,  2661, -1837,  1315,   728,  1315,  1315,  1315,  1315,  1228,
    1237,  1315, -1837,  1315,  1315,  1315,  1315,  1315,   493,  1315,
   -1837,  1315, -1837,  1559,   632,   785,   528, -1837, -1837, -1837,
   -1837,   788,  1034,  1590,  2270,  2686,  1131,   657,  2079,  2810,
    1668,   123,   924,   939,  1151,  3220,   913,  3634,   773, -1837,
    5759,   818,   977,   432,   438,   800,   235,  1149,   295,  1722,
    5013, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837,  5435, -1837, -1837,     5,  7419,   357,  1272,   606,
    7783,   257, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837,  1088, -1837, -1837,   367, -1837, -1837,  1088, -1837, -1837,
    1315,  1315,  1315,  1315,  1315,  1315,  1315,  1315,   612,  1315,
    1315,  1315,  1315, -1837, -1837, -1837,  1611, -1837, -1837, -1837,
    1315,  1315,  1315,   -44, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837,   636,   665,   679, -1837, -1837, -1837,   821,   466,  1005,
   -1837, -1837, -1837,   655, -1837, -1837, -1837,   127,   127, -1837,
     355,   257,  8446,  3291,   547,   550, -1837,    96,   749, -1837,
   -1837, -1837, -1837, -1837,   174,   770,   897, -1837,   768,   893,
   -1837,   570,  6943, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837,   757, -1837, -1837,   919, -1837, -1837, -1837,   596,
   -1837,  5327, -1837, -1837,   853, -1837,   241, -1837,   424, -1837,
   -1837, -1837, -1837,  1391, -1837,   146, -1837, -1837,   858, -1837,
   -1837, -1837,  1095,   911,   923,   582, -1837,   752, -1837,  6457,
   -1837, -1837, -1837,   936, -1837, -1837, -1837,   940, -1837, -1837,
    6797,  6797, -1837, -1837,   156,   677,   707, -1837, -1837,   711,
   -1837, -1837, -1837,   716, -1837,   721,   963,  6943, -1837,   122,
     250, -1837,   323, -1837, -1837,  1315,  1315,  1315,   682, -1837,
   -1837, -1837,  6943, -1837,   274, -1837, -1837, -1837,   383, -1837,
   -1837, -1837,   440,   250, -1837, -1837, -1837,   500, -1837, -1837,
     323, -1837,   506,   733, -1837, -1837, -1837, -1837,  1315, -1837,
   -1837, -1837, -1837,   323, -1837, -1837, -1837,  1063, -1837, -1837,
   -1837, -1837,  1315, -1837, -1837, -1837, -1837, -1837, -1837,  1315,
    1315, -1837, -1837, -1837,  1086,  1090, -1837,  1315,  1093, -1837,
    1315, -1837,  1315, -1837,  1315, -1837,  1315, -1837, -1837, -1837,
   -1837,  1315, -1837, -1837, -1837,  1315,  1315,   328,   257, -1837,
   -1837, -1837,   323, -1837, -1837,  1315, -1837, -1837,  1315, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1315, -1837,
     257, -1837, -1837, -1837, -1837,  1145, -1837, -1837, -1837, -1837,
   -1837,  1171,   656, -1837, -1837,   875, -1837, -1837,  1087,    49,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837,   673,   698, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837,  1312, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837,  2809, -1837, -1837, -1837, -1837,  1092, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837,  3029, -1837,  5968, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837,  3975, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,   554, -1837,
   -1837,   840, -1837, -1837, -1837, -1837, -1837, -1837,   850, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837,  2175, -1837, -1837, -1837, -1837,   908,   262,   912,  1157,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,   921,
     929, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837,   323, -1837,   733, -1837,  1315, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837,  1088, -1837, -1837, -1837, -1837,    39,    13,   690,
     111, -1837, -1837, -1837,  5536,  1216,  7210,  7783,  1126, -1837,
   -1837, -1837, -1837,  1283,  1285,    82,  1259,  1263,  1269,   126,
    1271,  2175,  1276,  7210,   114,  7210,   842,  7210, -1837, -1837,
    1227,  7783,   866,  7210,  7210,  1248,  1644, -1837,  6475,   163,
   -1837,  1644, -1837, -1837, -1837,   972, -1837,  1242,  1249,   757,
   -1837, -1837, -1837,   884,  1644,  1253,  1267,  1303,  1644,   919,
   -1837, -1837,   130, -1837, -1837,  7210, -1837, -1837,  5745,  1277,
    1034,  1590,  2270,  2686, -1837,  2079,   664, -1837, -1837, -1837,
   -1837,  1281, -1837, -1837, -1837, -1837,  7210, -1837,  1255,  1392,
    1398,  1062,   441,   327, -1837, -1837, -1837, -1837,  1429,  1484,
    1438, -1837, -1837, -1837, -1837,  1449, -1837, -1837, -1837, -1837,
     622, -1837, -1837,  1456,  1460, -1837, -1837, -1837,  1370,  1381,
   -1837, -1837,   853, -1837, -1837,  1474, -1837, -1837, -1837, -1837,
    1480, -1837, -1837,  5954, -1837,  1480, -1837, -1837, -1837,   102,
   -1837, -1837,  1391, -1837,  1486, -1837,   257, -1837,  1125, -1837,
     257,   157, -1837,  8299,  8299,  8299,  8299,  8299,  7783,   121,
    7988, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837,  8299, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837,   703, -1837,  1357,  1489,  1495,  1147,
     902,  1513, -1837, -1837, -1837,  7988,  7210,  7210,  1452,   159,
     370,  1525, -1837,  1168,   370,  1464, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837,  1503,  1195,  1206,  1209, -1837,
    1225,  1239, -1837, -1837, -1837, -1837,  1298,  1290,  1099,  1644,
   -1837, -1837,  1508,  1510,  1515,  1256,  1530, -1837,  1532,  1278,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1536, -1837, -1837,
   -1837, -1837, -1837,  1315, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837,  1541,   632, -1837, -1837, -1837, -1837,  1546,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1176, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837,  1548, -1837,  1459, -1837, -1837,  1462, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1306, -1837,
    1311,  1524, -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1163,
    1689,  1777,  1777, -1837, -1837, -1837,  1425, -1837, -1837, -1837,
   -1837,  1430,  1439, -1837,  1440,  1436,  1443,   572, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1588, -1837, -1837,
    1593, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837,  1396, -1837,  1405, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837,  1595,  1608,  1350, -1837, -1837, -1837, -1837,
   -1837,  1612,   272, -1837, -1837, -1837,  1353, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837,  1355,  1356,  1367,  1632, -1837, -1837,
     842, -1837, -1837, -1837,  1635, -1837, -1837, -1837, -1837,  7210,
    2686,  2079,  1735,  6163, -1837,   146,   260,  1734,  3115,  1644,
    1644,  1653,  7783,  7210,  7210,  7210, -1837,  1662,  7210,  1715,
    7210, -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1665, -1837,
     154,  1749, -1837, -1837,   247,   297,   262, -1837,   410,   476,
     183,  1730, -1837,  7210, -1837, -1837,   893,  1542,  1134,   277,
   -1837,   829,  1513,   893, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837,  1628,   591, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837,  1073,  1164, -1837,  1265, -1837, -1837, -1837,
    7210,  1774,  7210, -1837, -1837, -1837,   667,   726, -1837,  7210,
   -1837, -1837,  1417, -1837, -1837,  7210,  7210,  7210,  7210,  7210,
    1686,  7210,  7210,   177,  7210,  1480,  7210,  1707,  1787,  1713,
    2495,  2495, -1837, -1837, -1837,  7210,  1484,  7210,  1484, -1837,
    1778,  1784, -1837,   866, -1837,  7783, -1837,  7783, -1837, -1837,
   -1837,  1357,  1489,  1495, -1837,   893, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837,  1441,  8299,  8299,  8299,  8299,  8299,  8299,
    8299,  8299,  8488,  8299,  8299,   795, -1837,  1178, -1837, -1837,
   -1837, -1837, -1837,  1708, -1837,   304,   409, -1837,  2905,  3652,
    3251,  4477,   841, -1837, -1837, -1837, -1837, -1837, -1837,  1446,
    1468,  1471, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1806, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837,  3115, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1453,
    1470, -1837, -1837, -1837, -1837, -1837, -1837,  1350,   668,  1742,
   -1837, -1837, -1837, -1837, -1837,  1437, -1837, -1837, -1837, -1837,
   -1837,  1554,  1203, -1837,  1665,  1673, -1837,   539,   154, -1837,
     990, -1837, -1837,  7210,  7210,  1841, -1837,  1747,  1747, -1837,
     260, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
    1500,  1734,  6943,   260, -1837, -1837, -1837, -1837, -1837, -1837,
    7210, -1837, -1837,   253,  1555,  1560,  1856, -1837, -1837, -1837,
    1567,   102, -1837,  7783,   102,  7210,  1836, -1837,  8218, -1837,
    1696,  1597,  1573,  1581,  1099,  1134, -1837,  1747,  1747, -1837,
     277, -1837,  6475, -1837,  5051, -1837, -1837, -1837, -1837,  1888,
   -1837, -1837,  1461, -1837, -1837,  1461, -1837,  1826,  1461, -1837,
   -1837,  7210, -1837, -1837, -1837, -1837, -1837,  1255,  1392,  1398,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1897,  7210,  1737,
    7210, -1837, -1837, -1837, -1837,  1484, -1837,  1484,  1480, -1837,
   -1837,   237,  6943,  6579,   166, -1837, -1837, -1837,  1525,  1900,
   -1837, -1837,  1357,  1489,  1495, -1837,   231,  1525, -1837, -1837,
     829,  8299,  8488, -1837,  1805,  1878, -1837, -1837, -1837, -1837,
   -1837,   257,   257,   257,   257,   257,  1815,   658,   257,   257,
     257,   257, -1837, -1837, -1837,   370, -1837,  1562,   108, -1837,
    1821, -1837, -1837, -1837,   370,   370,   370,   370,   370,  7783,
   -1837,  1747,  1747,  1566,  1482,  1820,   983,  1766,  1741, -1837,
   -1837, -1837,   370,   370,   531, -1837,  7783,  1747,  1747,  1570,
     983,  1766, -1837, -1837, -1837,   370,   370,   531,  1830,  1577,
    1837, -1837, -1837, -1837, -1837, -1837,  5203,  4006,  3513,  4831,
    1207, -1837, -1837, -1837, -1837, -1837, -1837, -1837,  4360,  1501,
   -1837, -1837,  1838, -1837, -1837, -1837,  1937, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837,  1843, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837,  2014, -1837,   737,   472,  1072,  1844,
   -1837, -1837, -1837, -1837, -1837,  1555,  1560, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1567, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837,  7210, -1837, -1837, -1837, -1837,
   -1837, -1837,  7783,  1585,   260, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837,  1731,  1934, -1837,  1857, -1837,  1858, -1837,  1731,
    1861, -1837, -1837, -1837, -1837, -1837, -1837, -1837,  7210,   127,
     127,   893,  1513, -1837,   251,  1866, -1837,   185,   842,  1867,
   -1837, -1837, -1837, -1837, -1837, -1837,   370, -1837,   591, -1837,
   -1837, -1837, -1837, -1837, -1837,  7210, -1837,  1874, -1837,  1480,
    1480,  7783, -1837,   436,  1606,  1967,   893, -1837,  1525,  1525,
    1785,  1871, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837,   257,   257,   257, -1837, -1837, -1837, -1837,
   -1837,   416, -1837, -1837, -1837, -1837, -1837,  1873, -1837, -1837,
   -1837, -1837, -1837, -1837,  1279, -1837,   370,   370,   323, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
    1380, -1837, -1837, -1837, -1837, -1837,  1336, -1837, -1837, -1837,
   -1837, -1837,  1027,   370,   370,   323,  1110,  1336, -1837, -1837,
   -1837,  1831,   416,   370, -1837, -1837, -1837, -1837, -1837, -1837,
    1603,  1032,  1754, -1837, -1837, -1837,  1880, -1837,  1350, -1837,
   -1837, -1837,  1618,   812,  1315, -1837, -1837, -1837, -1837, -1837,
    1747,  1883,   812,  1884,  1315, -1837, -1837, -1837, -1837, -1837,
    1889,  1315, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837,  6943, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837,  1694, -1837,   288, -1837, -1837,
   -1837,   154, -1837, -1837, -1837, -1837, -1837, -1837,  1886,  1702,
   -1837, -1837,  1665,   154, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837,  7210,  1633,  7783, -1837, -1837,  2106,  6579, -1837, -1837,
    1813,   370,  1649,  1650,  1652,  1655,  1657, -1837, -1837, -1837,
    1659,  1660,  1661,  1667,   139,   370, -1837, -1837,  1988,  7783,
   -1837, -1837, -1837, -1837, -1837,   983, -1837,  1766, -1837,  7607,
   -1837, -1837, -1837,   603, -1837,   301,   370,   370, -1837, -1837,
   -1837, -1837, -1837,  2027, -1837,  1671, -1837, -1837,   370,   370,
   -1837,   370,   370,   370,   370,   370, -1837,  1902,   370, -1837,
    1674, -1837, -1837, -1837, -1837, -1837,  1942, -1837, -1837,  1555,
    1560,  1567, -1837, -1837, -1837, -1837,  1681,   893, -1837, -1837,
    1785, -1837, -1837, -1837, -1837, -1837,  1684,  1693,  1697, -1837,
   -1837, -1837, -1837, -1837, -1837,   168, -1837, -1837, -1837,  1956,
   -1837, -1837, -1837, -1837,  7783,   370,  2054,  2058, -1837, -1837,
   -1837, -1837, -1837, -1837,   370,   983,  1964, -1837, -1837, -1837,
    1103, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1966,
   -1837,  1968, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837,   812, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837,  1813,  1376,  4714,  4123,  6351,  2117, -1837, -1837, -1837,
    1442,  2345,  1557,  1188,   135, -1837,  1551,  1279, -1837,  7783,
   -1837, -1837, -1837, -1837, -1837, -1837,  1380, -1837,  1971,  1972,
   -1837,  2065,   171, -1837,   370, -1837, -1837, -1837, -1837, -1837,
     370,   370,   370,   370,   370,  1833,  1115,  2111,   370,   370,
     370,   370, -1837, -1837,   224,  1720,  1831, -1837,  2063, -1837,
   -1837, -1837, -1837,  1478,  1968,   370, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837,   416, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837,   370,   370,   370, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     432,   432,   432,   432,   432,   432,   432,   432,   436,   439,
     432,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   237,   438,     9,    28,    29,     0,
     432,   432,   432,   432,    68,    67,     3,     0,    71,     0,
     433,     0,   457,     0,    66,     0,   424,   425,     0,     0,
       0,     0,   608,    87,    89,     0,     0,   289,     0,   311,
       0,   337,    72,   432,    73,   432,   432,   432,   432,   432,
     432,   432,     0,   432,   432,   432,   432,    74,   432,    75,
     432,   432,   432,   432,   432,   432,   432,   432,     0,   432,
     432,   432,   432,    76,   432,    77,   432,   463,   432,   463,
     432,   463,   463,   432,   432,   463,   432,   463,     0,   432,
     463,   463,     0,   432,   463,   463,   463,   463,   432,   432,
     432,   463,    35,   432,   463,   432,   432,   432,   432,   463,
     463,   432,    47,   432,   432,   432,   432,   463,     0,   432,
      80,   432,    81,     0,     0,     0,   765,   736,   426,   427,
     428,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    25,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   949,   950,   951,   952,   953,   954,   955,   956,   957,
     958,   959,   960,   961,   962,   963,   964,   965,   966,   967,
     968,   970,     0,   972,   971,     0,     0,     0,     0,    34,
       0,     0,    85,   732,   731,   737,   738,   252,   748,   749,
     742,   940,   743,   746,   750,   747,   744,   745,   739,  1056,
    1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,  1065,  1066,
    1067,  1068,  1069,    53,  1074,  1075,  1076,  1077,  1071,  1072,
    1073,   740,  1322,  1323,  1324,  1325,  1326,  1327,  1328,  1329,
     741,     0,   249,   250,     0,    33,   233,     0,    21,   235,
     432,   432,   432,   432,   432,   432,   432,   432,     0,   432,
     432,   432,   432,    16,   238,    39,   239,   437,   434,   435,
     432,   432,   432,    13,   861,   834,   836,    70,    69,   440,
     442,     0,     0,     0,   459,   458,   460,     0,   598,     0,
     716,   717,   718,     0,   931,   932,   933,   500,   501,   936,
     723,     0,     0,     0,   516,   522,   527,     0,   551,   576,
     588,   589,   665,   671,   692,     0,     0,   976,     0,     7,
      92,   465,   467,   481,   468,    61,   272,   496,   477,   504,
     475,    13,   514,    14,    59,   525,   473,   474,    46,   579,
      40,     0,    54,    60,   596,    40,   664,    40,   670,    18,
      24,   487,    45,   690,   493,     0,   494,   479,     0,   722,
     478,   767,   770,   772,   774,   776,   777,   784,   786,     0,
     785,   729,   503,   940,   482,   488,   480,   739,   497,    62,
       0,     0,    65,   451,     0,     0,     0,    91,   445,     0,
      95,   304,   303,     0,   448,     0,     0,     0,   608,   112,
     114,   289,     0,   311,   337,   432,   432,   432,    13,   861,
     834,   836,     0,    60,     0,   136,   137,   138,     0,   130,
     131,   139,     0,   132,   133,   141,   142,     0,   134,   135,
       0,   143,     0,   145,   146,   838,   839,   837,   432,    13,
      36,    44,    51,     0,    60,   203,   464,   205,   170,   171,
     172,   173,   432,   174,   176,   200,   199,   198,   192,   432,
     463,   196,   195,   197,   838,   839,   840,   432,     0,    13,
     432,   177,   432,   180,   432,   183,   432,   189,    36,    44,
      51,   432,   186,    78,   220,   432,   432,   464,   216,   218,
     215,   222,     0,   223,    13,   432,   208,   207,   432,   213,
     211,    44,    79,   224,   225,   226,   227,   230,   432,   229,
       0,  1082,  1079,  1080,    56,     0,   756,   757,   758,   759,
     760,   762,     0,   981,   983,     0,   982,    52,     0,     0,
    1320,  1321,    56,  1084,  1085,    55,    20,    55,  1088,  1089,
    1090,  1091,    30,     0,     0,  1094,  1095,  1096,  1097,  1098,
       9,  1116,  1117,  1111,  1106,  1107,  1108,  1109,  1110,  1112,
    1113,  1114,  1115,     0,    28,    55,  1131,  1130,  1129,  1132,
    1133,  1134,    31,    55,  1137,  1138,  1139,    32,  1148,  1149,
    1141,  1142,  1143,  1145,  1144,  1146,  1147,    29,  1160,    55,
    1156,  1153,  1152,  1157,  1155,  1154,  1158,  1159,    31,  1163,
    1166,  1162,  1164,  1165,     8,  1169,  1168,    19,  1171,  1172,
    1173,    11,  1177,  1178,  1175,  1176,    57,  1183,  1180,  1181,
    1182,    58,  1230,  1224,  1227,  1228,  1222,  1223,  1225,  1226,
    1229,  1231,     0,  1184,    55,  1264,  1265,     0,    15,  1210,
    1209,  1202,  1203,  1204,  1188,  1189,  1190,  1191,  1192,  1193,
    1194,  1195,  1196,  1197,    53,  1206,  1205,  1208,  1207,  1199,
    1200,  1201,  1217,  1219,  1218,     0,    25,     0,  1214,  1213,
    1212,  1211,  1318,  1315,  1316,     0,  1317,    49,    55,    28,
    1335,  1008,    29,  1334,  1337,  1006,  1007,    34,     0,    48,
      48,     0,    48,  1341,    48,  1344,  1343,  1345,     0,    48,
    1332,  1331,    27,  1353,  1350,  1348,  1349,  1351,  1352,    23,
    1356,  1355,    17,    55,  1359,  1362,  1358,  1361,    38,    37,
     944,   945,   946,    51,   947,    34,    37,   942,   943,  1023,
    1024,  1030,  1016,  1017,  1015,  1025,  1026,  1046,  1019,  1028,
    1021,  1022,  1027,  1018,  1020,  1013,  1014,  1044,  1043,  1045,
      51,     0,    12,  1031,   987,   986,     0,   784,     0,     0,
      48,    27,    23,    17,    38,  1363,   991,   992,   969,   990,
       0,   730,  1070,   232,   251,    82,   234,    83,    60,   154,
     155,   132,   156,   157,     0,   158,   160,   161,   432,    13,
      36,    44,    51,    86,    84,   240,   241,   243,   242,   245,
     246,   244,   247,   858,   858,   858,    97,     0,     0,   551,
       0,   454,   455,   456,     0,     0,     0,     0,     0,   938,
     937,   934,   935,     0,     0,     0,    37,    37,     0,     0,
       0,     0,    12,     0,     0,     0,   560,     0,   549,   550,
       0,     0,     0,     0,     0,     0,     0,     6,     0,     0,
     788,     0,   466,   469,   498,     0,   472,     0,     0,   515,
     518,   476,   483,     0,     0,     0,     0,     0,     0,   526,
     528,   484,     0,   575,   485,     0,    47,    16,     0,     0,
      20,    30,     9,    28,   899,    29,     0,   904,   902,   903,
      14,     0,    40,    40,   889,   890,     0,   626,   629,   631,
     633,   635,   636,   641,   646,   644,   645,   647,   649,   587,
     613,   614,   624,   891,   615,   622,   616,   623,   619,   620,
       0,   617,   618,     0,   648,   621,   486,   495,     0,     0,
     605,   604,   597,   600,   489,     0,   683,   684,   685,   663,
     668,   681,   490,     0,   669,   674,   491,   492,   686,     0,
     708,   709,   691,   693,   696,   706,     0,   734,     0,   733,
       0,     0,   724,     0,     0,     0,     0,     0,     0,     0,
       0,   924,   925,   926,   927,   928,   929,   930,    20,    30,
       9,    28,    31,   916,    29,    31,     8,    19,    11,    57,
      58,    53,    15,    25,    49,    40,     0,   906,   874,   907,
     781,   782,   886,   873,   863,   862,   878,   880,   882,   884,
     885,   872,   908,   909,   875,     0,     0,     0,     0,     7,
       0,   828,   827,   885,     0,     0,   393,    60,   256,   273,
     290,   319,   338,   461,   111,     0,     0,     0,     0,   118,
       0,     0,   858,   858,   858,   120,     0,     0,   551,     0,
     129,   153,     0,     0,     0,     0,     0,   144,     0,     0,
     858,   148,   151,   149,   152,   169,   191,     0,   206,   175,
     194,   193,    12,   432,   179,   178,   181,   184,   190,   185,
     182,   188,   187,   217,   219,   221,   210,   209,   212,   214,
     228,   231,  1081,     0,     0,    55,   753,   754,    22,     0,
     979,   766,    42,    42,  1319,  1086,  1083,  1092,  1087,    20,
      28,    20,    28,  1093,  1118,  1119,  1120,  1121,    28,  1103,
    1128,  1127,  1136,  1135,  1140,  1151,  1150,  1161,  1167,  1170,
    1174,  1179,    10,  1248,  1254,  1252,  1243,  1244,  1247,  1249,
    1238,  1239,  1240,  1241,  1242,  1250,  1245,  1246,  1251,  1186,
    1253,  1185,  1266,    15,  1262,  1198,  1216,  1215,  1220,  1270,
    1267,  1268,  1269,  1271,  1272,  1273,  1274,  1275,  1276,  1277,
    1278,  1279,  1280,  1281,  1282,  1283,  1284,  1301,    50,  1313,
    1336,  1002,  1003,  1009,    48,  1004,  1333,     0,  1338,  1340,
       0,  1342,  1330,  1347,  1354,  1360,  1357,   941,   948,   939,
    1029,  1032,  1033,     0,  1035,     0,  1034,  1036,  1037,    12,
      12,  1038,  1010,     0,     0,   984,  1365,  1364,  1366,  1367,
    1368,     0,     0,   751,   168,   159,     0,   858,   163,   166,
     164,   167,   236,   248,     0,     0,     0,     0,   358,    13,
     560,   383,    36,   363,     0,    44,   388,   835,    51,     0,
      28,    29,   590,     0,   599,     0,   710,   712,     0,     0,
       0,     0,     0,     0,     0,     0,    12,     0,     0,  1038,
       0,   517,   429,   523,   524,    36,   558,   559,     0,    44,
       0,     0,   705,    45,   700,   699,     0,   704,   702,   703,
       0,   677,   679,     0,   499,   800,     7,     7,   802,   797,
     799,   885,   824,     7,   787,   462,   282,   520,   521,   519,
     541,    20,     0,     0,   539,   535,   530,   531,   532,   533,
     536,   534,   529,     0,     0,    53,     0,   655,   900,   901,
       0,   650,     0,   892,   895,   896,   893,   894,   905,     0,
     898,   897,     0,   613,   622,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   657,     0,     0,     0,     0,
       0,     0,   602,   603,   601,     0,     0,     0,   672,   695,
     700,   699,   694,     0,    10,     0,   726,     0,   725,   768,
     769,   771,   773,   775,   778,     7,   505,   507,   783,   893,
     915,   894,   917,   914,   913,   919,   911,   912,   910,   920,
     918,   921,   922,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   869,   868,   885,   974,  1055,
     830,   829,    63,     0,    64,     0,     0,   109,     0,     0,
       0,     0,     0,    60,   256,   273,   290,   319,   338,     0,
       0,     0,    13,    36,    44,    51,   452,   441,   443,   273,
     446,   449,   338,    12,   204,   201,    12,     0,   761,   755,
     752,    52,   763,   764,  1099,  1101,  1100,  1102,    55,  1123,
    1125,  1124,  1126,  1105,    28,     0,  1260,  1232,  1257,  1234,
    1261,  1237,  1258,  1259,  1235,  1255,  1256,  1233,  1236,  1263,
    1298,  1297,  1299,  1300,  1306,  1288,  1289,  1290,  1291,  1303,
    1292,  1293,  1294,  1295,  1296,  1304,  1305,  1307,  1308,  1309,
    1310,  1311,  1312,    55,  1287,  1286,  1302,    49,  1005,     0,
       0,    28,    28,    29,    29,  1011,  1012,   984,   984,     0,
      26,   989,   993,   994,    34,     0,   338,    12,   373,   378,
     368,     0,     0,    98,     0,     0,   105,     0,     0,   100,
       0,   107,   592,     0,     0,   591,   713,     0,     0,   807,
     711,   803,  1248,  1252,  1247,  1251,  1253,    53,    10,    10,
       0,   796,     0,   794,    37,    37,    12,   512,    12,    12,
       0,    12,   548,     0,   561,   564,     0,   557,   553,   552,
     554,     0,   687,     0,     0,     0,     0,   791,     0,   792,
       0,    13,     0,     0,   551,   801,   810,     0,     0,   823,
     798,   808,   790,   789,     0,   540,    28,   544,   545,    53,
     543,   577,     0,   581,   578,     0,   583,     0,     0,   585,
     656,     0,   660,   662,   625,   627,   628,   630,   632,   634,
     642,   643,   637,   640,   639,   638,   652,   651,     0,     0,
       0,  1047,  1048,  1049,  1050,   666,   682,   673,   675,   707,
     735,     0,     0,     0,     0,   508,   923,   871,   865,     0,
     876,   877,   879,   881,   883,   870,   779,   864,   780,   887,
     888,     0,     0,   779,     0,     0,    60,   395,   394,   397,
     396,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    88,   258,   257,     0,   255,     0,     0,    55,
       0,    90,   275,   274,     0,     0,     0,     0,     0,     0,
     300,     0,     0,     0,     0,     0,     0,     0,     0,    93,
     292,   291,     0,     0,     0,   470,     0,     0,     0,     0,
       0,     0,    94,   321,   320,     0,     0,     0,     0,     0,
       0,    13,    96,   340,   339,   128,     0,     0,     0,     0,
       0,   373,   378,   368,   121,   126,   122,   127,     0,     0,
     150,   202,     0,   980,  1122,  1104,     0,  1285,  1314,  1339,
    1346,  1039,  1040,  1041,  1042,    41,     0,    26,   985,  1001,
     997,   996,   995,    34,     0,   165,     0,     0,     0,     0,
      13,   360,   359,   362,   361,   561,   564,    36,   385,   384,
     387,   386,    44,   365,   364,   367,   366,   554,    51,   390,
     389,   392,   391,   593,   595,     0,   805,   806,   804,  1221,
     978,   977,     0,     0,   795,   975,   973,  1052,   513,  1053,
      12,  1051,     0,   566,   568,     0,    36,     0,    36,     0,
       0,    44,   701,   697,   698,    45,    45,   678,     0,     0,
       0,     7,   825,   826,     0,     0,   812,     0,   560,     0,
     811,   821,   822,   809,   502,   283,     0,   538,     0,   537,
      55,    55,    47,    55,   653,     0,   659,     0,   661,   667,
     676,     0,   714,     0,     0,     0,     7,   506,   867,   866,
     609,     0,   110,   453,   357,   444,   272,   447,   289,   311,
     450,   337,   254,     0,     0,     0,   357,   357,   357,   357,
     259,     0,   422,   423,    43,   421,   420,     0,   418,   276,
     278,   277,   281,   279,     0,   287,     0,     0,     0,   336,
     335,    43,   334,   398,   400,   401,   399,   354,   402,   355,
       0,   353,   307,   308,   310,   309,     0,   306,   301,   302,
     298,   471,     0,     0,     0,     0,     0,     0,   332,   331,
     329,     0,     0,     0,   343,   113,   115,   116,   117,   119,
       0,     0,     0,   140,   147,    10,     0,   988,   984,  1000,
     998,   162,     0,     0,     0,    12,   375,   374,   377,   376,
       0,     0,     0,     0,     0,    12,   380,   379,   382,   381,
       0,     0,    12,   370,   369,   372,   371,   831,    99,   859,
     860,   106,   101,   833,   108,   594,     0,   727,  1054,   570,
     571,   572,   573,   574,   563,     0,   546,     0,   565,   547,
     567,     0,   556,   688,   689,   680,   793,    12,     0,     0,
      14,    14,     0,     0,   284,   542,    31,    31,   586,   584,
     654,     0,     0,     0,   715,   721,     0,   510,   509,   610,
     611,     0,     0,     0,     0,     0,     0,   357,   357,   357,
       0,     0,     0,     0,     0,     0,   346,   419,     0,     0,
     294,   296,   297,   299,   333,     0,    55,     0,   295,     0,
     322,   323,   330,   318,   328,     0,     0,     0,   344,    12,
      12,    12,  1078,     0,    26,     0,    57,    53,     0,     0,
     103,     0,     0,     0,     0,     0,   104,     0,     0,   102,
       0,   562,   569,   555,   816,    12,     0,   819,   820,   561,
     564,   554,   580,   582,   658,   719,     0,     7,   612,   606,
     609,   393,   273,   290,   319,   338,     0,     0,     0,   358,
     383,   363,   388,   351,   350,     0,   347,   352,   280,     0,
     288,   356,   293,   305,     0,     0,     0,   285,    60,   317,
      13,    36,    44,    51,     0,     0,     0,   412,   406,   405,
     409,   404,   407,   408,   341,   342,   124,   125,   123,     0,
     999,     0,   844,   843,   850,   852,   855,   856,   853,   854,
     857,     0,   846,   728,   817,    13,    36,    36,    44,   720,
     511,   611,     0,     0,     0,     0,     0,   373,   378,   368,
       0,     0,     0,     0,     7,   345,   417,     0,   325,     0,
     316,   312,   314,   313,   315,    55,     0,   413,     0,     0,
    1187,     0,     0,   847,     0,   813,   814,   815,   818,   607,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   349,   348,     0,     0,     0,   326,   286,   327,
      55,   411,   410,     0,     0,     0,    55,    60,   260,   261,
     262,   263,    12,    12,    12,    13,    36,    44,    51,   414,
     415,     0,   403,   324,   430,   431,   849,   848,    43,   845,
     271,     0,     0,     0,   264,   269,   265,   270,   416,   851,
     267,   268,   266
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1837, -1837,    -1, -1275,  1070,    54, -1321,  1067,  1068,  -352,
    -898,  -718,  1182,  1297, -1837,  1074,  -519, -1837, -1837,  1301,
   -1837,  -140, -1625,  1304,    -8,   -14,  1526,  -601, -1837, -1837,
    -687, -1837,  -493,  -724,  1305, -1837,  -305, -1837,   964, -1828,
    -489, -1233, -1837,  -875,  -492,  -919, -1837,  -497,   610,  -659,
   -1837,  -546,  1544,  -982,  1089, -1837,  -399, -1837,    16, -1837,
   -1837,  2084, -1837, -1837, -1837,  1832,  1834,   595,  1069, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837,    11, -1837,  1691, -1837,   660,  -330,
   -1384, -1837, -1837, -1624,  -424, -1406,  -420,   354,     1,  -423,
   -1837, -1837, -1417, -1416, -1837,  -429, -1413, -1836, -1837,  -138,
       2, -1639,  -685,   -59,   -60, -1671, -1667, -1664,   -57,   -58,
     -40, -1837, -1837,  -164, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837,   175,  -773, -1477, -1837,   340,   -33,  3359, -1837,
     309, -1837, -1837,   780, -1837,   425,   792,  1868, -1837,   211,
   -1837,  -722,  1733, -1837, -1837,   268,   700,   758,   834,   -42,
   -1837, -1837, -1420, -1398,  -346, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837,   230, -1837, -1837, -1837, -1837,  1273, -1837, -1837,
   -1837, -1837,  1261, -1837, -1837, -1837,   255, -1837,  -320, -1428,
   -1649, -1837, -1193, -1690, -1475, -1681, -1470,   287,   286, -1837,
   -1837, -1047, -1837, -1837, -1837, -1837, -1837, -1837, -1837,  1204,
    -353,  1740,    -9,   -79,    25,   797,   798,   796, -1837,  -806,
   -1837, -1837, -1837, -1837, -1837, -1837,  1744, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837,  -350,   783, -1837, -1837,
   -1837, -1837,  1198,   560,  -913,   573,  1321,   799, -1340, -1837,
   -1837,  1864, -1837, -1837, -1837, -1837,  1208, -1837, -1837,   -67,
     246,  -851,  -349,  1084,   -27, -1837, -1837, -1837,  1071,     3,
   -1837, -1837, -1837, -1837, -1837,  -182,  -208, -1837, -1837,   759,
    -823,  1985,   -52, -1837,   872, -1277, -1837, -1555, -1837, -1837,
     609, -1395, -1837, -1837,   585,   583, -1837, -1837,  1811,  -604,
    1786,  -552,  1789,  -540,  1793,   170, -1837, -1753, -1837, -1837,
     -88, -1837, -1837,  -622,  -516,  1788, -1837,  -385,  -328,  -854,
    -844,  -840, -1837,  -284,  -859, -1837,  1322,  1538,  -759, -1837,
   -1509,  -324,   128,  1898, -1837,    32, -1837,   155, -1837, -1422,
   -1837,   307, -1837, -1837, -1837, -1837, -1837,   571,  -282,   947,
    1517,  1039,  1903,  1905, -1837, -1837,  -478,   207, -1837, -1837,
   -1837,  1109, -1837, -1837,   -68, -1837,   -48, -1837,   -43, -1837,
     -64, -1837, -1837, -1837,   -31, -1837,   -26, -1837,   -21, -1837,
     -13, -1837,   -12, -1837,    -6, -1837,     0, -1837,     9, -1837,
      19, -1837,    24,  1545, -1837,   -84, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837,  1579, -1061, -1837, -1837,
   -1837, -1837, -1837,    29, -1837, -1837, -1837, -1837,  1051, -1837,
   -1837,    30, -1837,    34, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837, -1837,
   -1837, -1837, -1837, -1837
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,  1783,   878,  1157,  1365,  1505,  1159,  1242,   836,
     891,  1184,   823,  1224,   976,  1158,  1363,   807,  1490,  1223,
     977,   695,  1819,  1222,  1419,  1421,  1364,  1151,  1153,   805,
     798,   513,  1092,  1227,  1226,   824,   904,  2017,  1492,  2117,
    1093,   978,   901,   532,  1215,  1209,  1547,  1094,  1130,   802,
     956,  1135,  1122,  1160,  1161,   892,   957,   884,  1784,    46,
      47,    48,    74,    87,    89,   447,   451,   456,   443,   103,
     293,   105,   132,  1098,   475,   142,   150,   152,   275,   278,
     295,   296,   832,  1262,   276,   222,   415,  1735,  1458,   416,
    1459,  1644,  2205,  1964,   419,  1460,   420,  1986,  1987,   423,
    2214,  2215,  1461,  1762,  1971,   425,  1462,  2115,  2195,  2196,
    1979,  1980,  2102,  1572,  1577,  1828,  1826,  1827,  1575,  1580,
    1456,  1981,  1744,  2136,  2220,  2221,  2222,  2306,  1745,  1746,
    1954,  1955,  1933,   223,  1304,  2336,    49,    50,    61,   450,
      52,   454,  1936,   458,   459,  1938,    71,   464,  1941,   445,
     446,  1934,   314,   315,   316,    53,   427,  1589,   477,  1748,
     351,   352,  1764,   353,   354,   355,   356,   357,   358,   359,
    1416,  1694,  1695,   360,   361,   362,   889,   890,   363,   364,
     365,   899,   900,  1351,  1345,  1649,  1650,   366,  1274,  1620,
    1881,   367,  1308,  1876,  1614,  1878,  1615,  1616,  2064,   368,
     369,  1653,   903,   370,   371,   372,   373,   374,   962,   963,
    1720,   414,  2100,  2179,   927,   928,   929,   930,   931,   932,
     933,  1673,   934,   935,   936,   937,   938,   939,   375,   376,
     969,   377,   378,   974,   379,   380,   970,   971,   381,   382,
     383,   982,   983,  1311,  1312,  1313,   984,   985,  1285,  1286,
     384,   385,   386,   387,   388,   991,   992,   389,   390,   224,
     940,   988,  1028,   941,   391,   228,  1128,   551,   552,   942,
     559,   392,   393,   394,   395,   396,   397,  1030,  1031,  1032,
     398,   399,   400,   879,   880,  1602,  1603,  1327,  1328,  1329,
    1590,  1591,  1640,  1635,  1636,  1641,  1330,  1891,  1050,  1834,
     837,  1846,   839,  1852,   840,   468,   498,  2148,  2046,  2282,
    2283,  2029,  2039,  1264,  1841,   838,   401,  1051,  1052,  1036,
    1037,  1038,  1039,  1331,  1041,   943,   944,   945,  1044,  1045,
     402,   851,   946,   756,   757,   231,   404,   947,   557,  1560,
     786,   948,  1252,   799,  1564,  1823,   234,   949,   718,   951,
     719,   952,   781,   782,  1239,  1240,   783,   953,   954,   405,
     406,   955,   239,   545,   240,   566,   241,   572,   242,   580,
     243,   594,  1148,  1504,   244,   602,   245,   607,   246,   617,
     247,   628,   248,   634,   249,   637,   250,   641,   251,   646,
     252,   651,   253,   685,   686,   687,   254,   688,   255,   701,
     256,   696,   257,   408,   663,  1179,  1596,  1181,  1517,  1509,
    1514,  1507,  1511,   258,   668,  1207,  1546,  1529,  1535,  1524,
    1208,   259,   707,   260,   562,   261,   262,   732,   263,   720,
     264,   722,   265,   724,   266,   729,   267,   739,   268,   742,
     269,   748,   270,   795
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,   421,    54,   227,   852,  1071,   883,  1068,   787,   886,
    1070,   350,  1069,  1111,  1034,  1109,   422,    45,   870,  1332,
    1110,  1137,  1368,   417,   299,  1185,   885,  1156,   975,   298,
    1213,  1358,  1229,   229,  1089,   845,   989,  1426,   800,   697,
    1087,  1777,  1119,   279,  1081,  1775,   308,  1136,  1317,  1150,
    1789,  1627,  1629,  1095,   409,  1790,   229,  1152,  1642,   412,
    1788,  1057,  1765,  1765,   875,  1691,  1399,  1277,   229,  1799,
     964,  1035,   972,  1155,   476,  1096,   476,  1574,   476,   476,
    1622,  1787,   476,  1690,   476,   403,  1075,   476,   476,   950,
     297,   476,   476,   476,   476,  1798,   700,   403,   476,  1835,
    1067,   517,  1115,  1324,  1836,  1431,   517,   517,  1335,   671,
    1856,  1857,   671,   674,   476,  1040,   674,  1091,  1182,  1893,
    1372,  1346,  2012,  1085,  2010,  1350,  1053,  1053,  2011,   672,
    1692,  1996,   672,  1229,   673,  1815,  1817,   673,  1925,   877,
    1693,  1411,  1992,  2124,   986,  2049,   675,  1104,  1417,   675,
    1847,   676,  1412,  1824,   676,  2050,   677,  1413,   230,   677,
    1901,  1902,  1210,   877,   678,   679,  2137,   678,   679,   986,
    1333,   680,  1116,  1926,   680,  2264,  1132,   681,  2314,  1291,
     681,   230,    58,    59,    60,   232,   682,  1952,  1953,   682,
    1403,   311,  2019,   230,  1055,  1858,   683,  1225,  2053,   683,
     986,   684,   990,   494,   684,   157,   689,   690,   232,   689,
     690,   691,  1265,  1266,   691,   158,   159,   160,  1302,   229,
     232,    62,   758,   229,   309,    55,   310,  1597,  1216,  1296,
    1218,    56,  1219,  1269,  1409,  1410,   413,  1221,  -736,  2193,
    2194,   418,  1921,  2193,  2194,   424,  -736,  -736,  -736,  -736,
    -832,   303,   304,   305,   306,  -731,  1228,   271,  1618,   871,
     850,   850,  -731,  -731,  -731,  -731,   277,   635,  1623,  -697,
     998,  1923,  1353,  1872,  1966,  1967,   225,  1860,  1861,  2153,
     104,    65,   803,  1230,   636,  1354,   428,  1275,   806,  1302,
    1993,  1994,   497,  1765,   438,   439,   440,   441,  1246,   225,
    1278,  -731,  1355,  1241,  1429,  -738,  1277,  1656,     4,  1659,
       5,   225,  -738,  -738,  -738,  -738,  1000,   474,   987,  -698,
    -832,    64,  1272,  2216,  1270,  1261,   965,  1259,   158,   159,
     160,  1082,  1260,  1267,   499,  1382,   784,   233,   872,   508,
     509,   510,  1133,  1714,   230,    73,   785,  1033,   230,   524,
    1587,  -738,   531,  1588,  2077,   229,   442,  1873,  1033,  1033,
     233,    56,  1428,   730,   758,   421,  1991,  1637,    88,  1777,
    1638,   232,   233,  1775,     4,   232,     5,  1271,    56,  1991,
     422,  1383,   426,  1299,   403,  1064,   430,  1256,   731,   865,
    1765,  1765,  2162,   421,  1255,   151,   801,   495,   709,   467,
    1080,   453,   426,  1268,  2217,  2218,   421,   866,   422,  1254,
       3,  1420,  1303,     4,  1422,     5,   496,   853,  -746,   480,
    2081,   422,   712,   740,    57,  -746,  -746,  -746,  -746,   294,
     229,   448,  -433,  1562,  1586,     6,     7,     8,     9,  1297,
    1083,  2093,   426,   519,  1806,   229,  1292,  1055,   741,  1619,
    1469,  1470,  1471,   534,   854,   421,  1356,   476,   818,   403,
     540,  1380,   225,  1381,  -746,  1519,   225,  1258,  1483,  1858,
     422,   221,  1472,     3,   403,  1276,     4,   221,     5,  2246,
     230,   312,   313,  2080,  -747,  1415,  -253,    56,  2284,  2247,
     221,  -747,  -747,  -747,  -747,  2348,   221,  1084,     6,     7,
       8,     9,   849,   849,   221,  2206,   855,   232,   221,   973,
    2349,   833,   834,   835,  1758,   221,  1598,  1599,  1624,  2230,
    1056,  1407,  2248,   233,  1451,  1991,  1474,   233,  1334,   334,
    -747,  1927,  1674,  2265,   335,     4,  2315,     5,   538,  1475,
       3,   349,  1925,     4,    56,     5,   221,   337,  1874,   272,
     273,   274,   338,  2151,    57,   230,  1187,  1086,   272,   273,
     274,  1473,  2030,  1088,  2078,     6,     7,     8,     9,  2031,
     230,    57,   966,   967,   968,  1671,  2276,   489,   490,  1489,
    2267,  2092,   232,  1874,  1702,  2056,  1149,  2177,  2297,  1385,
    2295,   811,   426,   221,  2296,  1703,  2144,   232,   225,  -736,
    1704,   235,  1922,  1154,    56,  1910,  2032,  2169,  1911,   881,
      56,  1913,  2170,  1188,  -272,  -731,  2076,  1370,  1371,   413,
    1494,   448,  1496,   309,   235,  -433,   881,   310,  1808,   671,
    1563,   674,   418,   674,  1143,  1567,   235,   424,   410,  1287,
    2208,  2033,  -551,  2163,   411,  1027,  1072,  1073,  1074,   672,
     989,  2097,  2073,  2074,   673,  2171,  1027,  1027,  1457,   233,
    1445,   558,  2219,  1316,   675,  -738,   675,   300,   435,   676,
     221,   676,  1418,   225,   677,   721,   677,  1700,  1701,  1090,
      57,   723,   678,   679,   678,   679,  1543,   349,   225,   680,
    2209,   680,   221,   310,  2142,   681,  1657,   681,  1212,   789,
     711,  1211,   465,  1544,   682,  2082,   682,  1386,  1102,  1387,
    1434,  1886,  1463,  1758,   683,  1121,   683,  1446,   804,   684,
    1432,   684,  1548,  1435,   689,   690,   689,   690,   334,   691,
     521,   691,   523,   335,   233,  1647,  1545,    57,     3,   841,
    1648,     4,  1433,     5,   546,   547,   337,   421,  1943,   233,
    2034,   338, -1002,  2176, -1002,   966,   967,   968,   881,   846,
     998,  1447,   422,     6,     7,     8,     9,  2255,   842,  1892,
    1125,   603,  2256,   515,  1716,   516,   999,  2254,  -746,  1576,
    2114,  1581,   843,  1332,  1139,   221,  1579,   235,    18,    19,
     709,   235,   604,   455,    67,    68,    69,    57,  2253,  1140,
    1317,  2094,  1434,    57,  1314,   605,  1000,  1277,  1758,  1141,
     711, -1003,  1612, -1003,   712,  1711,  1414,   553,   554,   555,
    1617,   881,  1645,   334,  1142,  1114,  1326,   848,   335,   715,
     716,  2022,  -432,   514,  1332,  1777,  2335,  2035,    35,  1775,
     863,   337,     3,  1263,  -747,     4,   338,     5,    36,  1453,
     229,  1443,   868,   869,    37,   873,  1765,  1765,   431,   432,
     433,   301,   436,   302,   437,  1388,   864,     6,     7,     8,
       9,  2023,   876,   434,   229,   460,   461,  1820,    38,   813,
    1865,  1866,  1778,  1430,   473,  1779,   548,   549,   881,   463,
     550,   958,   959,   484,   485,  2210,   466,   877,   467,   491,
     692,  1367,  2250,   990,  1842,  1366,   844,   693,   487,  1441,
   -1002,   717,  1400,  2211,  1126,  1127,   522,  1573,  2212,   881,
    2213,   902,  1442,   235,  1443,   535,   536,  1389,   995,   539,
     133,   134,   987,   135,   136,   137,   989,   694,  1859,   715,
     716,   996,  1944,   479,  1945,   481,   483,   709,  1033,   486,
     997,   488,  1804,   702,   492,   493,   560,   561,   501,   503,
     505,   507,  1340,   606,   725,   512,   796,   797,   520, -1003,
    1565,   712, -1002,   527,   530,   230,  -832,   236,  1797,  2146,
    1795,   537,   874,   812,  2147,  1796,   703,   704,  1046,  2302,
    1909,     3,  1047,  1033,     4,  1341,     5,  1807,   235,   230,
     236,   229,   232,   868,   869,  1780,  1946,  1947,  1948,  1949,
    1342,  1559,   236,   235,  1816,  2024,     6,     7,     8,     9,
     311,   717,   705,   709,   307,  -432,   232,   664,     4,  1257,
       5, -1003,  2129,     3,   989,  2119,     4,  2088,     5,   556,
     960,  1058,   867,   961,   726,   727,   728,   712,  1688,  1452,
    1698,   887,   888,  1454,  1273,   706,  1343,  1707,     6,     7,
       8,     9,   868,   869,  1785,   814,   815,   320,   321,   237,
     642,  1059,   322,     3,   643,  1060,     4,   638,     5,   816,
    1061,   665,   666,   893,  1601,  1062,   881,  1973,   639,   640,
     667,   708,   237,   225,   158,   159,   160,  -337,     6,     7,
       8,     9,  2025,   709,   237,   710,  1097,   644,   645,   882,
     993,   994,  1974,  1975,   226,  2133,     3,   225,  2125,     4,
    1794,     5,  2030,   711,  1027,  2278,   230,   712,  2279,  2031,
     713,  -841,  1495,  1781,  1497,  -842,  2020,   226,  1103,   238,
    1503,     6,     7,     8,     9,  1344,   563,   564,   565,   226,
    1697,  1699,  1123,   232,   233,  1306,  1307,  1705,  1699,  1708,
    1710,  1404,   407,   236,  2232,  1406,  2032,   236,   469,   470,
     471,   472,  1373,   138,   407,  1441,   157,  1651,  1318,  1124,
     139,   140,  2167,  2168,  1129,  1441,  2040,  1652,  1453,     3,
    1443,  1131,     4,  1957,     5,  1183,   141,  1287,  1712,  1601,
    1443,  2033,   980,   981,     3,  2030,  1782,     4,     3,     5,
    1217,     4,  2031,     5,     6,     7,     8,     9,   987,   714,
    1220,  2107,  2108,  2109,   894,   895,   896,   897,   898,     6,
       7,     8,     9,     6,     7,     8,     9,  1976,  1332,  1027,
    1027,  1027,  1027,  1027,   225,   595,  1027,   596,  1778,  2032,
    1243,  1779,   715,   716,  1244,   237,  1863,  1977,  1978,   237,
    1245,  2110,  2111,  2112,  2113,   733,   597,   157,  1651,  1100,
    1375,  1376,  1027,   525,   598,   599,   600,   601,  1655,  1896,
    1251,   734,   528,     4,  2033,     5,   647,  2119,    18,    19,
    1498,  1027,   158,   159,   160,   229,  1253,    18,    19,   236,
     226,  1283,   735,  1288,   226,   233,  1289,  1499,  1290,   736,
    2034,  1293,  1500,  1501,  1899,  1294,   987,  1932,  1120,   648,
     649,  1295,   650,  1298,  1101,   238,  1928,  1929,  1300,   238,
    1310,  1675,  -432,  1323,   717,  1919,  1336,  1920,    35,   881,
       4,  -432,     5,  2127,  2051,  1337,  1924,    35,    36,   808,
    2041,  2054,  1338,  2052,    37,  1848,  1347,    36,   819,   820,
     821,   822,  1362,    37,  2086,  2087,  1369,  2089,   157,  1651,
    1348,  1780,  1436,  1437,   236,    18,    19,     3,    38,  1658,
       4,   881,     5,  2066,     4,  2069,     5,    38,  2125,   236,
    1520,   237,  2072,  2034,  1521,  1522,  1523,  2140,   737,   738,
    1665,  1666,     6,     7,     8,     9,  1349,  1672,   229,  1377,
     229,  1630,   868,   869,  1055,  1316,  1378,   482,   235,  1502,
     230,   881,  2186,  2187,  2188,    35,  1631,  1699,  1699,  2004,
    1379,  1632,    18,    19,  1384,    36,   226,  2042,   272,   273,
     274,    37,  1319,     3,  1633, -1047,     4,   232,     5,  1634,
    1144,  1145,  1146,  1147,  1715,  1717, -1048,  1733,  1742,  1760,
    1773,   407,   229,  1390,   881,    38,   237,  1391,     6,     7,
       8,     9,  1718,  1392,  1734,  1743,  1761,  1774,  2048,  1395,
    2323,   237,    35,  1029,  1393,  2172,  2173,  1396,  2233,  1405,
    1277,   403,    36,  1403,  1029,  1029,  1805,  1267,    37,  1781,
    1512,  1513,     3,  1515,  1516,     4,  1438,     5,  1551,  1552,
     790,   226,  2106,  1439,  2104,  1440,  2105,  1553,  1554,   791,
     792,  1444,    38,   793,   794,  -432,   226,     6,     7,     8,
       9,  2329,  1434,   230,  -432,   230,   407,   881,   225,  1813,
    1814,  1055,  1778,  1811,  1812,  1779,   877,  1628,  2123,  1821,
    1822,   407,   881,  2301,  1883,  1450,  1314,  1400,     3,  1464,
     232,     4,   232,     5,   157,  1651,   852,  1455,  1830,   235,
    1465,  1831,  2009,  1466,  1838,  2132,  1843,  1969,  1970,  1849,
    2202,  2334,  1302,     6,     7,     8,     9,   230,  1832,  1467,
    1326,  1839,  1267,  1844,  2304,  2305,  1850,  1683,  1684,   233,
      90,  1270,  1906,  1468,     3,   229,  2103,     4,    91,     5,
      92,  1476,    93,  1477,   232,    94,    95,    96,  1478,    97,
    1479,  1373,  1373,  1373,  1373,  1373,   229,  1373,  1373,     6,
       7,     8,     9,  1480,   403,  1481,  1681,  1681,  1907,   143,
    1484,   144,  1482,  1905,  1487,  1506,   145,   229,   146,  1491,
    1508,   225,   147,   225,  1601,  1518,  1537,   825,  1510,   826,
    -551,   827,   828,   541,  1538,  1780,   542,   543,   544,   829,
     830,  1956,  1541,  1539,     3,  1540,   403,     4,  1542,     5,
    1027,  1027,  1027,  1027,  1027,  1027,  1027,  1027,  1027,  1027,
    1027,  1549,   148,  1559,   149,   229,  1550,  2022,  1557,     6,
       7,     8,     9,   831,   567,   225,   568,   569,   570,   571,
    2160,  1558,   233,  1287,   233,  1561,  2274,  1566,  2272,  1568,
    1569,  1042,  1965,  2273,   403,   881,   979,   980,   981,  2309,
     230,  1570,  1042,  1042,  1950,  1571,  1267,  2023,  1578,  1965,
    1583,  2290,   998,  1959,  1960,  1961,  1962,  1963,   158,   159,
     160,   230,   229,  2286,  2287,     3,  1600,   232,     4,  2288,
       5,  1988,  1989,  1990,  2333,  1608,   233,  1610,  1613,   229,
    2339,  1621,   230,  1625,  1998,  1999,  2000,  1646,   232,  1661,
       6,     7,     8,     9,  1664,  1733,  1742,  1760,  1773,  1670,
     229,   881,  1678,  1781,   236,  1679,   629,  1742,  1680,   232,
    -697,   229,  1734,  1743,  1761,  1774,  -698,  2298,  1696,  2270,
    1791,  1713,   630,  1802,  1743,   966,   967,   968,   236,   403,
     230,   631,   850,   850,  1809,  2026,  2036,  2043,   632,   633,
     403,  2347,  1792,  2345,     3,  1793,   743,     4,  2346,     5,
      98,  1810,  2027,  2037,  2044,  1818,  1855,   232,   225,  1829,
     744,  1302,  1982,  1983,  1984,    99,  1985,   745,  2271,     6,
       7,     8,     9,   235,  1862,   229,  2014,  1875,  2040,   225,
     868,   869,  1877,   100,  1027,   746,  1879,   230,   101,  1888,
     102,  2024,   747,  1880,  2116,  1287,   237,  1894,  1027,  1897,
     225,  1895,  1898,  2285,   230,  1908,  1912,  1935,  1937,  1937,
    1940,   421,  1915,  1917,   232,  2084,   881,  1441,  1930,   233,
     237,  1525,  1526,  1527,  1528,   230,   422,  1931,  2340,  1942,
    1958,   232,  2300,  1972,   229,  1951,   230,  2022,   421,  1968,
    1318,   226,   859,  1995,  2001,  2116,  2003,  1043,   225,  1027,
    2002,  2015,   232,   422,  2016,   236,  2018,  2047,  1043,  1043,
    2057,   233,   881,   232,  -569,  1315,   238,  1027,  1027,  2091,
    2065,  2067,  1029,  2120,  2071,  2121,  2122,  2023,  2139,  2079,
    2083,  2095,  2096,  2344,  2101,  2099,   235,  2118,   235,  2126,
     238,  2145,  2135,  2143,  1270,  2128,  2152,  2154,  2161,  2165,
     230,  2149,  2130,  2131,  2157,   225,  2134,  2166,  2175,   233,
    2178,  2155,  2138,  1530,  1531,  1532,  1533,  1534,  2158,  2026,
    2036,  2043,   225,  2181,  2182,     3,  2183,   232,     4,  2184,
       5,  2185,   881,  2189,  2190,  2191,  2027,  2037,  2044,  2199,
     235,  2192,  2041,   225,  2229,  2231,  2241,   237,  1837,  2243,
       6,     7,     8,     9,   225,  2245,  2249,  2197,  2257,   230,
    2059,  2060,  2061,  2062,  2063,  1778,   233,  2258,  1779,   229,
    2266,  2259,  2269,  1401,   849,   849,  -287,  2277,  2223,  2280,
    2313,  -288,  2281,   233,  2311,  2312,   232,  1029,  1029,  1029,
    1029,  1029,   226,  2331,  1029,  1425,  1423,  1639,   403,  1359,
    1249,  1424,  2200,  1248,   233,  1247,   229,  1493,  1138,  1250,
    2180,  1803,  2207,   881,    72,   233,  1134,   238,   225,  1427,
    1029,  2024,     3,   809,  2198,     4,   810,     5,     3,  2141,
    1066,     4,   229,     5,  1786,  1997,  2303,  2201,  2203,  1029,
    2260,  2262,   229,  2261,  2263,  2224,  2225,     6,     7,     8,
       9,  2252,  2332,     6,     7,     8,     9,  2234,  2235,  1939,
    2236,  2237,  2238,  2239,  2240,   817,  2098,  2242,  1778,  1063,
    1352,  1779,  1339,  2085,  2068,  2070,  1394,   225,  1065,   233,
    1485,  2251,  2289,   235,  1667,  1669,  1668,  1965,  1780,  1686,
    1402,  1882,   881,   847,   230,   324,   325,   326,  1889,  1890,
     329,   608,   609,  1320,  1319,  1488,  1885,  2197,  2322,  1408,
    1042,   788,  1689,  1709,  2268,  1643,   610,   229,   611,   612,
     613,   232,  1864,  2275,  1719,   235,  1736,  1747,  1763,  1776,
    1900,   230,  1054,  1903,  1076,  2040,  2337,  1077,   233,  1078,
     857,   614,   615,   616,  1079,  1214,   861,  2330,   862,   236,
    1186,  1180,  2308,  1536,     0,     0,     0,   230,   232,     0,
       0,  1717,  1742,  1760,  1773,     0,   229,   230,     0,  1831,
    1838,  1843,  1849,   235,  2116,     0,  2307,     0,  1718,  1743,
    1761,  1774,   229,     0,   232,  2310,  1832,  1839,  1844,  1850,
       0,  1780,     0,  2316,   232,   403,     0,  1231,  1232,  2317,
    2318,  2319,  2320,  2321,  2026,  2036,  2043,  2325,  2326,  2327,
    2328,  1233,   225,     0,     0,     0,  1781,  1555,  1556,  1234,
       0,  2027,  2037,  2044,  2338,  1042,  1042,  1042,  1042,  1042,
     235,     0,  1042,     0,     0,  1235,     0,     0,     0,     0,
    1833,   237,   230,  1840,     0,  1845,     0,   235,  1851,   225,
    2350,  2351,  2352,  1027,     0,     0,     3,     0,  1042,     4,
       0,     5,   236,     0,   236,     0,     0,     0,   235,   232,
       0,     0,     0,   233,  1607,   225,     0,  1042,     0,   235,
     500,     6,     7,     8,     9,   225,   226,     0,     0,  2021,
       0,   230,   573,   574,     0,    18,    19,     0,     0,  2041,
       0,   575,   576,   577,   578,   579,     0,   230,  1639,     0,
     233,   238,   280,     0,     0,     0,   236,     0,   232,  1781,
     281,     0,   282,     0,   283,    75,  1043,   284,   285,   286,
       0,   287,     0,    76,   232,    77,   233,     0,     0,     0,
      78,    79,    80,   235,    81,    35,   233,  1654,  1654,     0,
    1654,     0,     0,     0,   237,    36,   237,     0,     0,     0,
     225,    37,     0,  1236,  1237,  1238,   767,     0,     0,     0,
     881,     0,     0,     0,  1374,     0,     0,     0,     0,   777,
     778,   779,     0,     0,     0,    38,  2324,     0,     0,     0,
       0,     0,  2294,     0,     0,     0,     0,     0,   502,   226,
       0,   226,   235,     0,     0,     0,     0,   504,   237,   225,
       0,     0,     0,    18,    19,     0,     0,     0,     0,     0,
       0,   233,    18,    19,   238,   225,   238,     0,  1029,  1029,
    1029,  1029,  1029,  1029,  1029,  1029,  1029,  1029,  1029,     0,
       0,  1043,  1043,  1043,  1043,  1043,     0,     0,  1043,     0,
       0,     0,     0,   226,  1736,  1747,  1763,  1776,     0,   236,
       0,  1800,     0,    35,  1801,     0,  1747,     0,     0,     0,
     233,     0,    35,    36,  1043,   906,     0,     0,   407,    37,
     236,   907,    36,     0,     0,     0,   233,     0,    37,   506,
       0,     0,     0,  1043,  2028,  2038,  2045,     0,  1282,     0,
    1284,   236,     0,    38,    18,    19,     0,     0,     0,   158,
     159,   160,    38,     0,     0,     0,  1008,  1301,     0,  1305,
    1009,  1309,     0,     0,    10,  1010,     0,  1321,  1322,     0,
       0,  1011,    11,     0,    12,   914,    13,   235,     0,    14,
      15,    16,     0,    17,     0,  1825,     0,    18,    19,   236,
       0,   237,   288,     0,    35,  1014,     0,     0,     0,  1357,
       0,     0,  1361,     0,    36,    82,  1270,   289,     0,     0,
      37,     0,   237,     0,   235,     0,     0,     0,     0,     0,
      83,     0,     0,     0,  1867,   290,  1868,  1869,     0,  1871,
     291,     0,   292,   237,    38,     0,   226,    35,    84,     0,
     235,     0,     0,    85,   881,    86,   236,    36,     0,     0,
     235,     0,     0,    37,     0,  1884,   511,  1315,  1401,     0,
    2299,   407,  1029,   236,     0,     0,     0,  1398,     0,     0,
       0,    18,    19,     0,     0,     0,  1029,    38,   226,     0,
       0,   237,   238,     0,   236,     0,  1654,     0,     0,  1654,
       0,     0,  1654,     0,     0,   236,     0,     0,     0,     0,
       0,     0,     0,   407,     0,     0,  1042,  1042,  1042,  1042,
    1042,  1042,  1042,  1042,  1042,  1042,  1042,     0,  2028,  2038,
    2045,    35,     0,     0,     0,   235,   226,  1029,     0,     0,
       0,    36,   917,     0,     0,   918,   919,    37,   237,     0,
    1448,  1449,   920,     0,     0,  1029,  1029,     0,   581,   582,
       0,   407,   583,     0,     0,   237,     0,     0,     0,   236,
       0,    38,     0,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   922,   923,   235,     0,   237,     0,     0,     0,
       0,     0,  1162,   226,   106,     0,     0,   237,     0,   107,
     235,     0,   108,   109,   110,   111,     0,  1163,   112,   113,
     226,   114,   115,   116,    39,   117,     0,     0,   238,     0,
       0,     0,     0,   593,   221,     0,     0,     0,   236,    40,
       0,   226,     0,     0,     0,   238,     0,     0,     0,     0,
       0,     0,   226,     0,     0,     0,     0,    41,     0,     0,
       0,     0,    42,     0,    43,   118,   407,   119,   120,   121,
       0,   237,     0,     0,     0,     0,     3,   407,     0,     4,
       0,     5,  1164,  1374,  1374,  1374,  1374,  1374,     0,  1374,
    1374,     0,     0,   618,   619,     0,   620,     0,  1682,  1682,
       0,     6,     7,     8,     9,     0,     0,     0,  2058,     0,
       0,     0,  1721,     0,     0,   621,   226,     0,     0,     0,
    1042,     0,  1722,   622,   623,     0,   624,  1723,     0,  1724,
     237,  1725,     0,     0,  1042,     0,   625,   626,   627,     0,
       0,   238,  1043,  1043,  1043,  1043,  1043,  1043,  1043,  1043,
    1043,  1043,  1043,     0,  1165,     0,     0,  1166,  1167,  1168,
    1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,
       0,     0,     0,   236,     0,   226,     0,     0,     0,     0,
    1719,  1747,  1763,  1776,     0,  1042,     0,     0,  1833,  1840,
    1845,  1851,     0,  1582,     0,     0,     0,  1585,     0,     0,
     238,     0,     0,  1042,  1042,     0,     0,  1604,  1605,  1606,
     236,     0,  1609,     0,  1611,     0,     0,     0,     0,     0,
       0,     0,     0,  2028,  2038,  2045,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,  1626,     0,  1726,
       0,     0,     0,     0,   122,     0,   236,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   123,
       0,     0,     0,  2150,     0,   237,   124,   125,   126,   127,
       0,     0,     0,  2156,  1660,     0,  1662,   128,     0,     0,
    2159,     0,   129,  1663,   130,   131,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1676,     0,
    1677,     0,   237,     0,     0,     0,     0,     0,   161,  1685,
     226,  1687,     0,     0,     0,  2164,     0,     0,     0,     0,
       0,   236,     0,  1592,     0,   165,     0,     0,   237,     0,
       0,     0,     0,     0,     0,   407,  1043,     0,   237,     0,
       0,   166,     0,     0,     0,     0,   167,   226,     0,   168,
    1043,  1029,  1727,     0,   169,     0,     0,     0,   170,     0,
       0,   171,   172,     0,     0,     0,   173,  1728,     0,   174,
     236,   175,   238,   226,     0,     0,     0,  2226,  2227,  2228,
       0,     0,     0,   226,     0,  1729,   236,     0,  1164,     0,
    1730,     0,  1731,     0,     0,     0,   176,     0,   238,     0,
       0,  1043,   181,  2244,     0,     0,     0,     0,   238,     0,
       0,     0,     0,   237,     0,     0,     0,     0,     0,  1043,
    1043,     0,     3,     0,   881,     4,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1732,     0,     0,     0,     0,     0,     0,     6,     7,     8,
       9,     0,     0,     0,     0,     0,     0,     0,   226,     0,
    1593,  1749,   237,  1166,  1167,  1594,  1169,  1170,  1171,  1172,
    1173,  1174,  1175,  1176,  1177,  1595,     0,     0,   237,     0,
       0,     0,     0,   238,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1853,  1854,     0,
       0,     0,     0,     0,     0,     0,     0,   226,     0,     0,
    1750,  1751,  1752,  1753,     0,  1754,     0,     0,  1755,     0,
       0,     0,     0,   226,  1870,   652,     0,     0,     0,     0,
      51,     0,   407,     0,   653,  1756,     0,     0,     0,  1887,
      63,    51,    51,    66,    66,    66,    70,     0,   238,    51,
     654,   858,     0,     0,   655,     0,     0,     0,   656,   657,
    2341,  2342,  2343,   658,   659,   660,   661,   662,     0,     0,
       0,     0,     0,   759,   760,  1914,     0,   761,     0,     0,
       0,     0,     0,     0,     0,  1757,     0,     0,     0,  1042,
       0,     0,  1916,     0,  1918,   762,     0,     0,     0,     0,
       0,     0,    51,     0,     0,   429,    51,    66,    66,    66,
      70,     0,     0,     0,     0,     0,     0,    51,     0,   444,
     449,   452,    51,   457,    66,    66,   462,     0,   444,   444,
     444,   444,     0,    66,     0,     0,     0,   478,     0,    51,
       0,     0,    66,    66,     0,    70,     0,     0,    66,     0,
       0,     0,   859,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,   518,   457,    66,   457,     0,   526,   529,
       0,     0,   533,    51,    66,    66,     0,     0,    66,     0,
      51,     0,     0,     0,     3,     0,     0,     4,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,  1758,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       7,     8,     9,   334,     0,   763,     0,     0,   335,     0,
       0,     0,     0,  1749,     0,     0,     0,     0,     0,     0,
       0,   337,     0,     0,     0,     0,   338,     0,     0,   764,
     765,   766,   767,   768,   769,   860,   770,   771,   772,   773,
     774,   775,   776,     0,     0,   777,   778,   779,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2055,
     881,     0,  1750,  1751,  1752,  1753,     0,  1754,   780,     0,
    1755,     0,     0,     0,     0,     0,  1759,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1756,     0,     0,
       0,     0,  2075,     0,     0,  1043,     0,     0,     0,   444,
     449,   452,    51,   457,    66,    66,   462,     0,   444,   444,
     444,   444,     0,     3,     0,     0,     4,     0,     5,  2090,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,     0,  1757,     6,     7,
       8,     9,   154,   155,     0,     0,     0,   317,   156,   318,
       0,     0,     0,     0,     0,     0,  1737,     0,     0,     0,
       0,     0,     0,     0,   319,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   320,   321,     0,     0,     0,   322,
       0,     0,   323,     0,     0,     0,     0,     0,     0,     0,
       0,   324,   325,   326,   327,   328,   329,     0,     0,     0,
       0,     0,     0,   161,     0,   162,  1738,     0,     0,   163,
     330,     0,   331,     0,   164,   157,   158,   159,   160,     0,
     165,   161,     0,   162,     0,     0,  1739,   163,     0,     0,
       0,     0,   164,     0,     0,     0,   166,     0,   165,     0,
       0,   167,     0,     0,   168,     0,     0,     0,     0,   169,
    1758,     0,     0,   170,   166,     0,   171,   172,   669,   167,
       0,   173,   168,     0,   174,   334,   175,   169,     0,     0,
     335,   170,     0,     0,   171,   172,  1740,     0,     0,   173,
       0,     0,   174,   337,   175,     0,     0,     0,   338,     0,
       0,   176,     0,   670,     0,  2174,     0,   181,     0,     0,
       0,  1099,     0,     0,     0,     0,     0,     0,    66,   176,
     177,     0,   178,   179,   180,   181,     0,     0,     0,  1105,
       0,  1106,   881,  1107,     0,  1108,     0,     0,     0,     0,
    1112,     0,     0,     0,  1113,    51,     0,     0,  2007,     0,
       0,     0,     0,     0,  1117,     0,     0,  1118,     0,     0,
     182,   183,   184,   185,     0,     0,     0,    66,     0,   186,
     187,     0,     0,   188,   189,   332,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,     0,     0,   333,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   334,     0,     0,     0,     0,   335,
       0,     0,     0,     0,     0,     0,   336,     0,     0,     0,
       0,     0,   337,     0,     0,     0,     0,   338,     0,     0,
       0,     0,     0,   213,   214,     0,   339,     0,     0,   340,
     341,   342,   343,     0,     0,     0,   344,     0,     0,     0,
     345,   346,   215,     0,     0,     0,   216,   217,     0,     0,
       0,   881,     0,     0,     0,   347,     0,     3,   218,   219,
       4,     0,     5,     0,   348,     0,   349,  1741,   220,     0,
       0,   221,     0,     0,     0,     0,     0,     0,     0,   153,
       0,     0,     6,     7,     8,     9,   154,   155,     0,     0,
       0,   317,   156,   318,     0,     0,     0,     0,     0,     0,
    1737,     0,     0,     0,     0,     0,     0,     0,   319,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   320,   321,
       0,     0,     0,   322,     0,     0,   323,     0,     0,     0,
       0,     0,     0,     0,     0,   324,   325,   326,   327,   328,
     329,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1738,     0,     0,     0,   330,     0,   331,     0,     0,   157,
     158,   159,   160,     0,     0,   161,     0,   162,     0,     0,
    1739,   163,     0,     0,     3,     0,   164,     4,     0,     5,
       0,     0,   165,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,     6,
       7,     8,     9,   167,     0,     0,   168,  1189,     0,     0,
       0,   169,     0,  1749,     0,   170,     0,     0,   171,   172,
    1740,     0,     0,   173,     0,     0,   174,     0,   175,     0,
    1190,  1191,  1192,  1193,  1194,  1195,  1196,  1197,  1198,  1199,
    1200,  1201,  1202,  1203,  1204,  1205,  1206,     0,     0,     0,
       0,     0,     0,   176,   177,     0,   178,   179,   180,   181,
       0,     0,  1750,  1751,  1752,  1753,     0,  1754,     0,     0,
    1755,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1756,     0,     0,
       0,     0,     0,     0,   182,   183,   184,   185,     0,     0,
       0,     0,     0,   186,   187,     0,     0,   188,   189,   332,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,     0,     0,   333,     0,     0,     0,  1757,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   334,     0,
       0,     0,     0,   335,     0,     0,     0,     0,     0,     0,
     336,     0,     0,     0,     0,     0,   337,     0,     0,     0,
       0,   338,     0,     0,     0,     0,     0,   213,   214,     0,
     339,     0,     0,   340,   341,   342,   343,     0,     0,     0,
     344,     0,     0,     0,   345,   346,   215,     0,     0,     0,
     216,   217,     0,     0,     0,   881,     0,     0,     0,   347,
       0,     3,   218,   219,     4,     0,     5,     0,   348,     0,
     349,  2006,   220,     0,     0,   221,     0,     0,     0,     0,
       0,     0,     0,   153,     0,     0,     6,     7,     8,     9,
     154,   155,     0,     0,     0,   317,   156,   318,     0,     0,
    1758,     0,     0,     0,  1737,     0,     0,     0,     0,     0,
       0,     0,   319,     0,     0,   334,     0,     0,     0,     0,
     335,     0,   320,   321,     0,     0,     0,   322,     0,     0,
     323,     0,     0,   337,     0,     0,     0,     0,   338,   324,
     325,   326,   327,   328,   329,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1738,     0,     0,     0,   330,     0,
     331,     0,  1486,   157,   158,   159,   160,     0,     0,   161,
       0,   162,   881,     0,  1739,   163,     0,     0,     3,     0,
     164,     4,     0,     5,     0,     0,   165,     0,  2292,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   166,     6,     7,     8,     9,   167,     0,     0,
     168,     0,     0,     0,     0,   169,     0,  1766,     0,   170,
       0,     0,   171,   172,  1740,     0,     0,   173,     0,     0,
     174,     0,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   176,   177,     0,
     178,   179,   180,   181,     0,     0,     0,  1767,  1768,  1769,
       0,  1754,     0,     0,  1755,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1770,     0,     0,     0,     0,     0,     0,   182,   183,
     184,   185,     0,     0,     0,     0,     0,   186,   187,     0,
       0,   188,   189,   332,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,     0,     0,   333,     0,     0,
       0,  1771,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   334,     0,     0,     0,     0,   335,     0,     0,
       0,     0,     0,     0,   336,     0,     0,     0,     0,     0,
     337,     0,     0,     0,     0,   338,     0,     0,     0,     0,
       0,   213,   214,     0,   339,     0,     0,   340,   341,   342,
     343,     0,     0,     0,   344,     0,     0,     0,   345,   346,
     215,     0,     0,     0,   216,   217,     0,     0,     0,   881,
       0,     0,     0,   347,     0,     3,   218,   219,     4,     0,
       5,     0,   348,     0,   349,  2013,   220,     0,     0,   221,
       0,     0,     0,     0,     0,     0,     0,   153,     0,     0,
       6,     7,     8,     9,   154,   155,     0,     0,     0,   317,
     156,   318,     0,     0,  1758,     0,     0,     0,  1737,     0,
       0,     0,     0,     0,     0,     0,   319,     0,     0,   334,
       0,     0,     0,     0,   335,     0,   320,   321,     0,     0,
       0,   322,     0,     0,   323,     0,     0,   337,     0,     0,
       0,     0,   338,   324,   325,   326,   327,   328,   329,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1738,     0,
       0,     0,   330,     0,   331,     0,     0,   157,   158,   159,
     160,     0,     0,   161,     0,   162,   881,     0,  1739,   163,
       0,     0,     3,     0,   164,     4,     0,     5,     0,     0,
     165,     0,  1772,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   166,     6,     7,     8,
       9,   167,     0,     0,   168,     0,     0,     0,     0,   169,
       0,  1766,     0,   170,     0,     0,   171,   172,  1740,     0,
       0,   173,     0,     0,   174,     0,   175,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   176,   177,     0,   178,   179,   180,   181,     0,     0,
       0,  1767,  1768,  1769,     0,  1754,     0,     0,  1755,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1770,     0,     0,     0,     0,
       0,     0,   182,   183,   184,   185,     0,     0,     0,     0,
       0,   186,   187,     0,     0,   188,   189,   332,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,     0,
       0,   333,     0,     0,     0,  1771,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   334,     0,     0,     0,
       0,   335,     0,     0,     0,     0,     0,     0,   336,     0,
       0,     0,     0,     0,   337,     0,     0,     0,     0,   338,
       0,     0,     0,     0,     0,   213,   214,     0,   339,     0,
       0,   340,   341,   342,   343,     0,     0,     0,   344,     0,
       0,     0,   345,   346,   215,     4,     0,     5,   216,   217,
       0,     0,     0,   881,     0,     0,     0,   347,     0,     0,
     218,   219,     0,     0,   153,     0,   348,     0,   349,  2291,
     220,   154,   155,   221,     0,     0,   317,   156,   318,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   319,     0,     0,     0,     0,  1758,     0,
       0,     0,     0,   320,   321,     0,     0,   749,   322,     0,
       0,   323,     0,   334,     0,     0,     0,     0,   335,     0,
     324,   325,   326,   327,   328,   329,     0,     0,     0,     0,
       0,   337,     0,     0,   750,     0,   338,   751,     0,   330,
       0,   331,     0,     0,   157,   158,   159,   160,     0,     0,
     161,     0,   162,     0,   752,     0,   163,     0,     0,     0,
       0,   164,     0,     0,     0,     0,     0,   165,     0,     0,
     881,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   166,     0,     0,  2008,     0,   167,     0,
       0,   168,     0,     0,     3,     0,   169,     4,     0,     5,
     170,     0,     0,   171,   172,     0,     0,     0,   173,     0,
       0,   174,     0,   175,     0,     0,     0,     0,     0,     6,
       7,     8,     9,     0,     0,     0,     0,     0,     0,     0,
    1721,     0,     0,     0,     0,     0,     0,     0,   176,   177,
    1722,   178,   179,   180,   181,  1723,     0,  1724,     0,  1725,
       0,     0,     0,     0,     0,     0,     0,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,     0,   182,
     183,   184,   185,     0,     0,     0,     0,     0,   186,   187,
       0,     0,   188,   189,   332,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,     0,     0,   333,     0,
     753,     0,   905,     0,   213,   214,     0,     0,     0,     0,
       0,     0,     0,   334,   754,     0,     0,     0,   335,     0,
     153,     0,     0,     0,     0,   336,     0,     0,   155,     0,
       0,   337,     0,   156,     0,     0,   338,  1726,     0,     0,
     755,     0,   213,   214,     0,   339,     0,     0,   340,   341,
     342,   343,     0,     0,     0,   344,     0,     0,     0,   345,
     346,   215,     0,     0,     0,   216,   217,   906,     0,     0,
       0,     0,     0,   907,   347,     0,     0,   218,   219,     0,
       0,     0,   908,   348,   909,   349,  1904,   220,     0,     0,
     221,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,   158,   159,   160,     0,     0,   161,     0,   910,     0,
       0,     0,   911,     0,     0,     0,     0,   912,     0,     0,
       0,     0,     0,   913,     0,     0,     0,   914,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   166,
       0,     0,     0,     0,   167,     0,     0,   915,     0,     0,
    1727,     0,   169,     0,     0,     0,   170,     0,     0,   171,
     172,     0,     0,     0,   173,  1728,     0,   174,     0,   175,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1729,     0,     0,     0,     0,  1730,     0,
    1731,     0,     0,     0,   176,   177,     0,   178,   179,   180,
     181,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1279,     0,     0,     0,     0,     0,   759,   760,     0,
       0,   761,   881,     0,     0,     0,     0,     0,     0,   153,
       0,     0,     0,     0,     0,   916,     0,   155,  2005,   762,
       0,     0,   156,     0,     0,     0,     0,     0,     0,     0,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,     0,     0,   212,     0,   906,     0,     0,     0,
       0,     0,   907,     0,   917,     0,     0,   918,   919,     0,
       0,     0,     0,     0,   920,     0,     0,     0,     0,     0,
       0,     0,   921,     0,     0,     0,     0,     0,     0,   157,
     158,   159,   160,     0,     0,   161,     0,   910,   213,   214,
       0,   911,     0,     0,   922,   923,   912,     0,     0,     0,
       0,     0,  1280,     0,     0,     0,   914,   215,     0,     0,
       0,   216,   217,     0,     0,     0,     0,     0,   166,     0,
       0,   924,   925,   167,   755,     0,  1281,     0,     0,   763,
       0,   169,     0,   926,     0,   170,   221,     0,   171,   172,
       0,     0,     0,   173,     0,     0,   174,     0,   175,     0,
       0,     0,     0,   764,   765,   766,   767,   768,   769,     0,
     770,   771,   772,   773,   774,   775,   776,     0,     0,   777,
     778,   779,     0,   176,   177,     0,   178,   179,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1360,     0,   780,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   153,     0,
       0,     0,     0,     0,   916,     0,   155,     0,     0,     0,
       0,   156,     0,     0,     0,     0,     0,     0,     0,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,     0,     0,   212,     0,   906,     0,     0,     0,     0,
       0,   907,     0,   917,     0,     0,   918,   919,     0,     0,
       0,     0,     0,   920,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,   158,
     159,   160,     0,     0,   161,     0,   910,   213,   214,     0,
     911,     0,     0,   922,   923,   912,     0,     0,   161,     0,
     162,  1280,     0,   698,   163,   914,   215,     0,     0,   164,
     216,   217,     0,     0,     0,   165,     0,   166,     0,     0,
     924,   925,   167,   755,     0,  1281,     0,     0,     0,     0,
     169,   166,   926,     0,   170,   221,   167,   171,   172,   168,
       0,     0,   173,     0,   169,   174,     0,   175,   170,     0,
       0,   171,   172,     0,     0,     0,   173,     0,     0,   174,
       0,   175,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,   177,     0,   178,   179,   180,   181,     0,
       0,     0,     0,     0,     0,     0,   176,     0,   699,  1397,
       0,     0,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   153,     0,     0,
       0,     0,     0,   916,     0,   155,     0,     0,     0,     0,
     156,     0,     0,     0,     0,     0,     0,     0,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
       0,     0,   212,     0,   906,     0,     0,     0,     0,     0,
     907,     0,   917,     0,     0,   918,   919,     0,     0,     0,
       0,     0,   920,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,   158,   159,
     160,     0,     0,   161,     0,   910,   213,   214,     0,   911,
       0,     0,   922,   923,   912,     0,     0,   161,     0,   162,
    1280,     0,     0,   163,   914,   215,     0,     0,   164,   216,
     217,     0,     0,     0,   165,     0,   166,     0,     0,   924,
     925,   167,   755,     0,  1281,     0,     0,     0,     0,   169,
     166,   926,     0,   170,   221,   167,   171,   172,   168,     0,
       0,   173,     0,   169,   174,     0,   175,   170,     0,     0,
     171,   172,     0,     0,     0,   173,     0,     0,   174,     0,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   176,   177,     0,   178,   179,   180,   181,     0,     0,
       0,     0,     0,     0,     0,   176,     0,     0,  1584,     0,
       0,   181,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   153,     0,     0,     0,
       0,     0,   916,     0,   155,     0,     0,     0,     0,   156,
       0,     0,     0,     0,     0,     0,     0,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,     0,
       0,   212,     0,   906,     0,     0,     0,     0,     0,   907,
       0,   917,     0,     0,   918,   919,     0,     0,     0,     0,
       0,   920,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,   158,   159,   160,
       0,     0,   161,     0,   910,   213,   214,     0,   911,     0,
       0,   922,   923,   912,     0,     0,     0,     0,     0,  1280,
       0,     0,     0,   914,   215,     0,     0,     0,   216,   217,
       0,     0,     0,     0,     0,   166,     0,     0,   924,   925,
     167,   755,     0,  1281,     0,     0,     0,     0,   169,     0,
     926,     0,   170,   221,     0,   171,   172,     0,     0,     0,
     173,     0,     0,   174,     0,   175,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     4,     0,     5,     0,     0,
     176,   177,     0,   178,   179,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     7,     8,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1766,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   916,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,     0,     0,
     212,  1767,  1768,  1769,     0,  1754,     0,     0,  1755,     0,
     917,     0,     0,   918,   919,     0,     0,     0,     0,     0,
     920,     0,     0,     0,     0,  1770,  1001,  1002,  1003,  1004,
    1005,  1006,     0,     0,     0,     0,  1007,     0,     0,     0,
     986,     0,     0,     0,   213,   214,     0,     0,     0,     0,
     922,   923,     0,     0,     0,     0,  1325,     0,     0,     0,
       0,     0,     0,   215,     0,     0,     0,   216,   217,     0,
       0,     0,     0,     0,     0,  1771,     0,   924,   925,     0,
     755,     0,     0,     0,     0,     0,     0,   906,     0,   926,
       0,     0,   221,   907,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   906,     0,     0,     0,     0,
       0,   907,     0,     0,     0,     0,     0,     0,     0,     0,
     157,   158,   159,   160,     0,     0,     0,     0,  1008,     0,
       0,     0,  1009,     0,     0,     0,     0,  1010,   157,   158,
     159,   160,     0,  1011,     0,     0,  1008,   914,     0,     0,
    1009,     0,     0,     0,     0,  1010,     0,     0,     0,  1012,
    1325,  1011,     0,     0,  1013,   914,     0,  1014,     0,     0,
       0,     0,  1015,     0,     0,     0,  1016,  1012,     0,  1017,
    1018,     0,  1013,     0,  1019,  1014,     0,  1020,  1758,  1021,
    1015,     0,     0,     0,  1016,     0,     0,  1017,  1018,     0,
       0,     0,  1019,   334,     0,  1020,     0,  1021,   335,   906,
       0,     0,     0,     0,  1022,   907,     0,  1023,     0,     0,
    1024,   337,     0,     0,     0,     0,   338,     0,     0,     0,
       0,     0,  1022,     0,     0,  1023,     0,     0,  1024,     0,
       0,     0,   157,   158,   159,   160,     0,     0,     0,     0,
    1008,     0,     0,     0,  1009,     0,     0,     0,     0,  1010,
     881,     0,     0,     0,     0,  1011,     0,     0,     0,   914,
       0,     0,     0,     0,     0,     0,  2293,     0,     0,     0,
       0,  1012,     0,     0,     0,     0,  1013,     0,     0,  1014,
       0,     0,     0,     0,  1015,     0,     0,     0,  1016,     0,
       0,  1017,  1018,     0,   917,     0,  1019,   918,   919,  1020,
       0,  1021,     0,     0,   920,     0,     0,     0,     0,     0,
       0,     0,   917,     0,     0,   918,   919,     0,     0,     0,
       0,     0,   920,     0,     0,     0,  1022,     0,     0,  1023,
       0,     0,  1024,     0,   922,   923,     0,  1025,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   922,   923,     0,  1025,     0,     0,     0,     0,
       0,   924,   925,     0,     0,     0,     0,     0,     0,  1048,
     986,   349,     0,  1026,     0,     0,   221,     0,     0,   924,
     925,     0,     0,     0,     0,     0,     0,     0,     0,   349,
       0,  1026,     0,     0,   221,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   917,   906,     0,   918,
     919,     0,     0,   907,     0,     0,   920,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,   158,   159,   160,     0,     0,   922,   923,  1008,  1025,
       0,     0,  1009,     0,     0,     0,     0,  1010,     0,     0,
       0,     0,     0,  1011,     0,     0,     0,   914,     0,     0,
       0,     0,     0,   924,   925,     0,     0,     0,     0,  1012,
       0,     0,     0,     0,  1013,  1026,     0,  1014,   221,     0,
       0,     0,  1015,     0,     0,     0,  1016,     0,     0,  1017,
    1018,     0,     0,     0,  1019,     0,   153,  1020,     0,  1021,
       0,     0,     0,   154,   155,     0,     0,     0,   317,   156,
     318,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1022,   319,     0,  1023,     0,     0,
    1024,     0,     0,     0,     0,   320,   321,     0,     0,     0,
     322,     0,     0,   323,     0,     0,     0,     0,     0,     0,
       0,     0,   324,   325,   326,   327,   328,   329,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   330,     0,   331,     0,     0,   157,   158,   159,   160,
       0,     0,   161,     0,   162,     0,     0,     0,   163,     0,
       0,     0,     0,   164,     0,     0,     0,     0,     0,   165,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   917,   166,     0,   918,   919,     0,
     167,     0,     0,   168,   920,     0,     0,     0,   169,     0,
       0,     0,   170,     0,     0,   171,   172,     0,     0,     0,
     173,     0,     0,   174,     0,   175,     0,     0,     0,     0,
       0,     0,     0,     0,   922,   923,     0,  1025,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,     0,   178,   179,   180,   181,     0,     0,     0,
       0,   924,   925,     0,     0,     0,     0,     0,     0,     0,
       0,  1049,     0,  1026,     0,     0,   221,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   183,   184,   185,     0,     0,     0,     0,     0,
     186,   187,     0,     0,   188,   189,   332,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,     0,     0,
     333,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   153,     0,   334,     0,     0,     0,     0,
     335,   155,     0,     0,     0,     0,   156,   336,     0,     0,
       0,     0,     0,   337,     0,     0,     0,     0,   338,     0,
       0,     0,     0,     0,   213,   214,     0,   339,     0,     0,
     340,   341,   342,   343,     0,     0,     0,   344,     0,     0,
     906,   345,   346,   215,     0,     0,   907,   216,   217,     0,
       0,     0,     0,     0,     0,     0,   347,     0,     0,   218,
     219,     0,     0,     0,     0,   348,     0,   349,     0,   220,
       0,     0,   221,   157,   158,   159,   160,     0,     0,   161,
       0,   910,     0,     0,     0,   911,     0,     0,     0,     0,
     912,     0,     0,     0,     0,     0,  1280,     0,     0,     0,
     914,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   166,     0,     0,     0,     0,   167,     0,     0,
    1281,     0,     0,     0,     0,   169,     0,     0,     0,   170,
       0,     0,   171,   172,     0,     0,     0,   173,     0,     0,
     174,     0,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   176,   177,     0,
     178,   179,   180,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,     0,     0,     0,     0,     0,   916,   154,
     155,     0,     0,     0,     0,   156,     0,     0,     0,     0,
       0,     0,     0,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,     0,     0,   212,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   917,     0,     0,
     918,   919,     0,     0,     0,     0,     0,   920,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   157,   158,   159,   160,     0,     0,   161,     0,
     162,   213,   214,     0,   163,     0,     0,   922,   923,   164,
       0,     0,     0,     0,     0,   165,     0,     0,     0,     0,
     215,     0,     0,     0,   216,   217,     0,     0,     0,     0,
       0,   166,     0,     0,   924,   925,   167,   755,     0,   168,
       0,     0,     0,     0,   169,     0,   926,     0,   170,   221,
       0,   171,   172,     0,     0,     0,   173,     0,     0,   174,
       0,   175,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   177,     0,   178,
     179,   180,   181,     0,     0,     0,     0,     0,     0,     0,
     153,     0,     0,     0,     0,     0,     0,   154,   155,     0,
       0,     0,     0,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   182,   183,   184,
     185,     0,     0,     0,     0,     0,   186,   187,     0,     0,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,  2204,     0,   212,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,   158,   159,   160,     0,     0,   161,     0,   162,     0,
       0,     0,   163,     0,     0,     0,     0,   164,     0,     0,
       0,     0,     0,   165,     0,     0,     0,     0,     0,     0,
     213,   214,     0,     0,     0,     0,     0,     0,     0,   166,
       0,     0,     0,     0,   167,     0,     0,   168,     0,   215,
       0,     0,   169,   216,   217,     0,   170,     0,     0,   171,
     172,     0,     0,     0,   173,   218,   219,   174,     0,   175,
       0,     0,     0,   349,     0,   220,     0,     0,   221,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,   177,   153,   178,   179,   180,
     181,     0,     0,   154,   155,     0,     0,     0,     0,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,     0,
       0,     0,     0,     0,   186,   187,     0,     0,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,     0,     0,   212,     0,   157,   158,   159,   160,
       0,     0,   161,     0,   162,     0,     0,     0,   163,     0,
       0,     0,     0,   164,     0,     0,     0,     0,     0,   165,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   166,     0,     0,   213,   214,
     167,     0,     0,   168,     0,     0,     0,     0,   169,     0,
       0,     0,   170,     0,     0,   171,   172,   215,     0,     0,
     173,   216,   217,   174,     0,   175,     0,     0,     0,     0,
       0,     0,     0,   218,   219,     0,     0,     0,     0,     0,
       0,     0,     0,   220,     0,     0,   221,     0,     0,     0,
     176,   177,     0,   178,   179,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   986,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   183,   184,   185,     0,     0,     0,     0,     0,
     186,   187,     0,     0,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   906,     0,
     212,     0,     0,     0,   907,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   157,   158,   159,   160,     0,     0,     0,     0,  1008,
       0,     0,     0,  1009,   213,   214,     0,     0,  1010,     0,
       0,     0,     0,     0,  1011,     0,     0,     0,   914,     0,
       0,     0,     0,   215,     0,     0,     0,   216,   217,     0,
    1012,     0,     0,     0,     0,  1013,     0,     0,  1014,   218,
     219,     0,     0,  1015,     0,     0,     0,  1016,     0,   220,
    1017,  1018,   221,     0,     0,  1019,     0,     0,  1020,     0,
    1021,     0,     0,     0,     0,     0,     0,     2,     3,     0,
       0,     4,     0,     5,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1022,     0,     0,  1023,     0,
       0,  1024,     0,     6,     7,     8,     9,     0,     0,     0,
       0,     0,     0,     0,    10,     0,     0,     0,     0,     0,
       0,     0,    11,     0,    12,     0,    13,     0,     0,    14,
      15,    16,     0,    17,     0,     0,     0,    18,    19,    20,
       0,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -432,     0,     0,     0,   917,     0,    35,   918,   919,
       0,     0,     0,     0,     0,   920,     0,    36,   906,     0,
       0,     0,     0,    37,   907,     0,     0,   324,   325,   326,
    1889,  1890,   329,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   922,   923,    38,  1025,     0,
       0,   157,   158,   159,   160,     0,     0,     0,     0,  1008,
       0,     0,     0,  1009,     0,     0,     0,     0,  1010,     0,
       0,     0,   924,   925,  1011,     0,     0,     0,   914,     0,
       0,     0,   349,     0,  1026,     0,     0,   221,     0,     0,
    1012,     0,     0,     0,     0,  1013,     0,     0,  1014,   906,
       0,     0,     0,  1015,     0,   907,     0,  1016,     0,     0,
    1017,  1018,     0,     0,     0,  1019,     0,     0,  1020,     0,
    1021,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   157,   158,   159,   160,     0,     0,     0,     0,
    1008,     0,     0,     0,  1009,  1022,     0,     0,  1023,  1010,
       0,  1024,     0,     0,     0,  1011,     0,     0,     0,   914,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1012,     0,     0,    39,     0,  1013,     0,     0,  1014,
       0,     0,     0,     0,  1015,     0,     0,     0,  1016,    40,
       0,  1017,  1018,     0,  -432,     0,  1019,     0,     0,  1020,
       0,  1021,     0,     0,     0,     0,     0,    41,     0,     0,
       0,     0,    42,     0,    43,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1022,     0,     0,  1023,
       0,     0,  1024,     0,     0,   917,     0,     0,   918,   919,
       0,     0,     0,     0,     0,   920,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   922,   923,     0,  1025,     0,
     856,     0,     0,     0,     0,     0,     0,     0,   906,     0,
       0,     0,     0,     0,   907,     0,     0,     0,     0,     0,
       0,     0,   924,   925,     0,     0,     0,   750,     0,     0,
     751,     0,     0,     0,  1026,     0,   917,   221,     0,   918,
     919,  1706,   158,   159,   160,     0,   920,   752,     0,  1008,
       0,     0,     0,  1009,     0,     0,     0,     0,  1010,     0,
       0,     0,     0,     0,  1011,     0,     0,     0,   914,     0,
       0,     0,     0,     0,     0,     0,   922,   923,     0,  1025,
    1012,     0,     0,     0,     0,  1013,     0,     0,  1014,     0,
       0,     0,     0,  1015,     0,     0,     0,  1016,     0,     0,
    1017,  1018,     0,   924,   925,  1019,     0,     0,  1020,     0,
    1021,     0,     0,     0,     0,  1026,     0,     0,   221,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1022,     0,     0,  1023,     0,
       0,  1024,     0,     0,     0,     0,     0,     0,     0,     0,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   753,     0,     0,     0,   213,   214,     0,
       0,     0,     0,     0,     0,   917,     0,   754,   918,   919,
       0,     0,     0,     0,     0,   920,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   755,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   922,   923,     0,  1025,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   924,   925,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1026,     0,     0,   221
};

static const yytype_int16 yycheck[] =
{
       1,    68,     3,    30,   328,   434,   352,   431,   216,   361,
     433,    53,   432,   510,   399,   508,    68,     1,   338,   878,
     509,   567,   920,    65,    38,   684,   356,   628,   378,    37,
     717,   906,   756,    30,   463,   317,   385,  1019,   220,   179,
     460,  1461,   531,    32,   443,  1461,    47,   566,   871,   595,
    1467,  1326,  1327,   473,    55,  1468,    53,   603,  1333,    60,
    1466,   414,  1460,  1461,   346,  1405,   979,   840,    65,  1482,
     375,   399,   377,   619,   107,   474,   109,  1270,   111,   112,
    1313,  1465,   115,  1404,   117,    53,   438,   120,   121,   371,
      36,   124,   125,   126,   127,  1479,   180,    65,   131,  1574,
     430,   134,   522,   876,  1574,  1024,   139,   140,   881,   177,
    1587,  1588,   180,   177,   147,   399,   180,   469,   664,  1628,
     926,   894,  1793,   453,  1791,   898,   410,   411,  1792,   177,
    1407,  1770,   180,   857,   177,  1557,  1558,   180,  1693,     4,
    1415,   995,  1766,  1971,    23,  1835,   177,   499,   999,   180,
    1578,   177,   996,  1566,   180,  1836,   177,   997,    30,   180,
    1637,  1638,   708,     4,   177,   177,  2002,   180,   180,    23,
       7,   177,   524,     7,   180,     7,   127,   177,     7,    97,
     180,    53,     7,     8,     9,    30,   177,    79,    80,   180,
       7,    57,  1817,    65,    38,  1590,   177,   743,  1847,   180,
      23,   177,    45,    90,   180,   103,   177,   177,    53,   180,
     180,   177,   834,   835,   180,   104,   105,   106,   104,   216,
      65,    10,   190,   220,    49,   105,    51,  1288,   720,   103,
     722,   104,   724,   837,   993,   994,    61,   729,     7,   104,
     105,    66,     5,   104,   105,    70,    15,    16,    17,    18,
     294,    40,    41,    42,    43,     8,   753,    58,   104,    85,
     327,   328,    15,    16,    17,    18,    58,   144,    85,    22,
       8,  1691,   142,    20,  1751,  1752,    30,  1598,  1599,  2032,
      53,    13,   271,   780,   161,   155,    75,   839,   277,   104,
    1767,  1768,   122,  1691,    83,    84,    85,    86,   790,    53,
     840,    54,   172,   781,  1022,     8,  1079,  1354,     4,  1356,
       6,    65,    15,    16,    17,    18,    54,   106,   385,    22,
     364,    12,   838,    22,   311,   822,    85,   820,   104,   105,
     106,    57,   821,   294,   123,     8,   331,    30,   164,   128,
     129,   130,   293,    39,   216,    49,   341,   399,   220,   138,
      90,    54,   141,    93,   103,   352,    88,   104,   410,   411,
      53,   104,  1021,   128,   332,   432,  1764,    90,    49,  1789,
      93,   216,    65,  1789,     4,   220,     6,   364,   104,  1777,
     432,    54,    73,   861,   352,   427,    77,   816,   153,   293,
    1788,  1789,   104,   460,   814,    47,   221,   284,   126,   286,
     442,    92,    93,   364,   103,   104,   473,   311,   460,   808,
       1,  1012,   298,     4,  1015,     6,   303,    62,     8,   110,
    1897,   473,   150,   128,   297,    15,    16,    17,    18,   104,
     427,    91,   104,   161,  1285,    26,    27,    28,    29,   313,
      57,     5,   133,   134,  1505,   442,   364,    38,   153,   295,
    1072,  1073,  1074,   144,    99,   522,   326,   490,   288,   427,
     151,    20,   216,    22,    54,  1183,   220,   819,  1090,  1864,
     522,   369,  1076,     1,   442,   364,     4,   369,     6,  2169,
     352,   347,   348,   298,     8,   364,   364,   104,  2241,  2170,
     369,    15,    16,    17,    18,  2331,   369,    57,    26,    27,
      28,    29,   327,   328,   369,  2129,   331,   352,   369,    85,
    2338,   300,   301,   302,   277,   369,  1289,  1290,   335,  2144,
     364,   364,  2171,   216,   365,  1923,  1078,   220,   365,   292,
      54,   365,  1383,   365,   297,     4,   365,     6,    45,  1079,
       1,   364,  2097,     4,   104,     6,   369,   310,   295,   350,
     351,   352,   315,  2030,   297,   427,   696,    57,   350,   351,
     352,  1077,    90,    57,   313,    26,    27,    28,    29,    97,
     442,   297,   331,   332,   333,  1381,  2215,    45,    46,  1125,
    2204,  1921,   427,   295,  1438,  1862,   594,  2096,  2259,   939,
    2257,   282,   283,   369,  2258,  1439,  2018,   442,   352,   368,
    1440,    30,   365,   617,   104,  1652,   134,  2082,  1655,   349,
     104,  1658,  2082,   697,   364,   368,  1891,   922,   923,   444,
    1139,   281,  1141,   448,    53,   297,   349,   452,  1547,   697,
     358,   695,   457,   697,   580,  1257,    65,   462,   363,   847,
      37,   169,   103,  2071,   363,   399,   435,   436,   437,   697,
     999,  1926,  1885,  1886,   697,  2083,   410,   411,  1057,   352,
    1045,   133,   361,   871,   695,   368,   697,    90,    90,   695,
     369,   697,  1000,   427,   695,   243,   697,  1436,  1437,   468,
     297,   243,   695,   695,   697,   697,   114,   364,   442,   695,
      87,   697,   369,   518,  2015,   695,  1355,   697,   712,   342,
     146,   709,    90,   131,   695,  1898,   697,    85,   497,    87,
       7,  1624,  1065,   277,   695,   540,   697,  1045,   351,   695,
    1025,   697,  1214,    20,   695,   695,   697,   697,   292,   695,
     135,   697,   137,   297,   427,   144,   164,   297,     1,   103,
     149,     4,  1026,     6,   112,   113,   310,   814,    90,   442,
     278,   315,    85,  2093,    87,   331,   332,   333,   349,   293,
       8,  1045,   814,    26,    27,    28,    29,  2184,   103,  1628,
     114,   114,  2185,    45,   365,    47,    24,  2183,   368,  1272,
     364,  1278,   103,  1642,   111,   369,  1275,   216,    60,    61,
     126,   220,   135,    93,    14,    15,    16,   297,  2182,   126,
    1623,   365,     7,   297,   871,   148,    54,  1580,   277,   111,
     146,    85,  1305,    87,   150,    20,   998,    32,    33,    34,
    1309,   349,  1341,   292,   126,   516,   878,   172,   297,   275,
     276,    94,   104,   133,  1693,  2255,  2313,   365,   110,  2255,
     293,   310,     1,   832,   368,     4,   315,     6,   120,    20,
     847,    22,   313,   314,   126,    85,  2254,  2255,    78,    79,
      80,   284,   284,   286,   286,   243,   316,    26,    27,    28,
      29,   134,   104,    81,   871,    95,    96,  1564,   150,   284,
    1604,  1605,    41,  1023,   104,    44,   254,   255,   349,    97,
     258,    38,    39,   113,   114,   292,   284,     4,   286,   119,
     127,   915,  2177,    45,   365,   913,    85,   134,   116,     7,
     243,   357,   979,   310,   258,   259,   136,  1269,   315,   349,
     317,   325,    20,   352,    22,   145,   146,   305,    17,   149,
      49,    50,   999,    52,    53,    54,  1285,   164,  1597,   275,
     276,    18,   284,   109,   286,   111,   112,   126,  1000,   115,
     368,   117,  1498,   135,   120,   121,   168,   169,   124,   125,
     126,   127,    78,   306,   164,   131,   360,   361,   134,   243,
    1252,   150,   305,   139,   140,   847,   294,    30,  1475,   167,
    1473,   147,    85,   283,   172,  1474,   168,   169,    52,  2264,
    1649,     1,    52,  1045,     4,   111,     6,  1543,   427,   871,
      53,   998,   847,   313,   314,   164,  1728,  1729,  1730,  1731,
     126,   343,    65,   442,   346,   278,    26,    27,    28,    29,
      57,   357,   204,   126,     0,   297,   871,   114,     4,   818,
       6,   305,     5,     1,  1383,     8,     4,  1912,     6,   254,
     187,   364,   293,   190,   244,   245,   246,   150,  1398,  1050,
    1435,   294,   295,  1054,   364,   237,   172,  1442,    26,    27,
      28,    29,   313,   314,  1463,   285,   286,    62,    63,    30,
     131,   364,    67,     1,   135,   364,     4,   153,     6,   287,
     364,   168,   169,   164,  1292,   364,   349,   104,   164,   165,
     177,   114,    53,   847,   104,   105,   106,   364,    26,    27,
      28,    29,   365,   126,    65,   128,    43,   168,   169,   351,
      15,    16,   129,   130,    30,     5,     1,   871,     8,     4,
    1472,     6,    90,   146,   878,    22,   998,   150,    25,    97,
     153,    45,  1140,   292,  1142,    45,  1823,    53,    45,    30,
    1148,    26,    27,    28,    29,   261,   112,   113,   114,    65,
    1434,  1435,     7,   998,   847,   313,   314,  1441,  1442,  1443,
    1444,   986,    53,   216,  2146,   990,   134,   220,    99,   100,
     101,   102,   926,   292,    65,     7,   103,   104,   871,     8,
     299,   300,  2080,  2081,   309,     7,   114,   114,    20,     1,
      22,   104,     4,  1739,     6,   103,   315,  1405,    20,  1407,
      22,   169,   336,   337,     1,    90,   365,     4,     1,     6,
     370,     4,    97,     6,    26,    27,    28,    29,  1285,   242,
     370,  1943,  1944,  1945,   305,   306,   307,   308,   309,    26,
      27,    28,    29,    26,    27,    28,    29,   254,  2097,   993,
     994,   995,   996,   997,   998,   114,  1000,   116,    41,   134,
     342,    44,   275,   276,   342,   216,  1602,   274,   275,   220,
     103,  1946,  1947,  1948,  1949,   116,   135,   103,   104,   489,
      15,    16,  1026,    45,   143,   144,   145,   146,   114,  1631,
     359,   132,    45,     4,   169,     6,   135,     8,    60,    61,
     114,  1045,   104,   105,   106,  1292,   367,    60,    61,   352,
     216,    85,   153,   177,   220,   998,    23,   131,    23,   160,
     278,    52,   136,   137,  1634,    52,  1383,  1716,   538,   168,
     169,    52,   171,    52,   490,   216,  1711,  1712,    52,   220,
     103,  1383,   104,    85,   357,  1685,   364,  1687,   110,   349,
       4,   104,     6,     7,  1837,   103,  1692,   110,   120,   280,
     278,  1848,   103,  1842,   126,   365,   103,   120,   289,   290,
     291,   292,    85,   126,  1910,  1911,    85,  1913,   103,   104,
     103,   164,    15,    16,   427,    60,    61,     1,   150,   114,
       4,   349,     6,  1876,     4,  1878,     6,   150,     8,   442,
     227,   352,  1881,   278,   231,   232,   233,   365,   249,   250,
    1375,  1376,    26,    27,    28,    29,   103,  1382,  1405,    17,
    1407,   277,   313,   314,    38,  1623,    18,    45,   847,   243,
    1292,   349,  2107,  2108,  2109,   110,   292,  1711,  1712,  1781,
     368,   297,    60,    61,     5,   120,   352,   365,   350,   351,
     352,   126,   871,     1,   310,     7,     4,  1292,     6,   315,
     138,   139,   140,   141,  1455,  1456,     7,  1458,  1459,  1460,
    1461,   352,  1459,     7,   349,   150,   427,     7,    26,    27,
      28,    29,  1456,   103,  1458,  1459,  1460,  1461,  1830,     5,
     365,   442,   110,   399,   103,  2086,  2087,     7,  2147,   364,
    2263,  1459,   120,     7,   410,   411,  1504,   294,   126,   292,
     194,   195,     1,   192,   193,     4,    17,     6,   112,   113,
     238,   427,  1941,    18,  1938,   368,  1939,   112,   113,   247,
     248,     8,   150,   251,   252,   297,   442,    26,    27,    28,
      29,  2304,     7,  1405,   297,  1407,   427,   349,  1292,  1553,
    1554,    38,    41,  1551,  1552,    44,     4,     5,  1968,   112,
     113,   442,   349,   365,  1621,   103,  1623,  1624,     1,   364,
    1405,     4,  1407,     6,   103,   104,  1890,   103,   365,   998,
     364,  1572,   365,   364,  1575,  1995,  1577,    95,    96,  1580,
    2126,   103,   104,    26,    27,    28,    29,  1459,  1572,   364,
    1642,  1575,   294,  1577,    43,    44,  1580,  1390,  1391,  1292,
      37,   311,  1644,   364,     1,  1602,  1936,     4,    45,     6,
      47,   103,    49,   103,  1459,    52,    53,    54,   103,    56,
     364,  1375,  1376,  1377,  1378,  1379,  1623,  1381,  1382,    26,
      27,    28,    29,   103,  1602,   103,  1390,  1391,  1646,    45,
     104,    47,   364,  1644,   103,    97,    52,  1644,    54,   103,
     191,  1405,    58,  1407,  1862,   131,   231,    46,   196,    48,
     103,    50,    51,   104,   234,   164,   107,   108,   109,    58,
      59,  1738,   236,   234,     1,   235,  1644,     4,   235,     6,
    1434,  1435,  1436,  1437,  1438,  1439,  1440,  1441,  1442,  1443,
    1444,   103,    98,   343,   100,  1692,   103,    94,   103,    26,
      27,    28,    29,    92,   114,  1459,   116,   117,   118,   119,
    2056,   103,  1405,  1921,  1407,   103,  2213,   364,  2211,   364,
     364,   399,  1749,  2212,  1692,   349,   335,   336,   337,  2275,
    1602,   364,   410,   411,  1735,   103,   294,   134,   103,  1766,
       5,   365,     8,  1744,  1745,  1746,  1747,  1748,   104,   105,
     106,  1623,  1749,  2246,  2247,     1,   103,  1602,     4,  2248,
       6,  1762,  1763,  1764,  2310,   103,  1459,    52,   103,  1766,
    2316,    22,  1644,    43,  1775,  1776,  1777,   149,  1623,     5,
      26,    27,    28,    29,   367,  1786,  1787,  1788,  1789,   103,
    1787,   349,    85,   292,   847,     8,   128,  1798,    85,  1644,
      22,  1798,  1786,  1787,  1788,  1789,    22,   365,   367,  2208,
     364,   103,   144,     7,  1798,   331,   332,   333,   871,  1787,
    1692,   153,  1889,  1890,   371,  1826,  1827,  1828,   160,   161,
    1798,  2328,   364,  2326,     1,   364,   114,     4,  2327,     6,
     277,   371,  1826,  1827,  1828,   103,     5,  1692,  1602,   295,
     128,   104,    86,    87,    88,   292,    90,   135,  2210,    26,
      27,    28,    29,  1292,   364,  1862,   365,   312,   114,  1623,
     313,   314,   312,   310,  1628,   153,    20,  1749,   315,    43,
     317,   278,   160,   316,  1951,  2093,   847,   191,  1642,   316,
    1644,   294,   311,  2245,  1766,     7,    70,  1722,  1723,  1724,
    1725,  1968,     5,   166,  1749,  1906,   349,     7,   103,  1602,
     871,   222,   223,   224,   225,  1787,  1968,    39,  2317,   104,
      99,  1766,   365,   103,  1921,   363,  1798,    94,  1995,   363,
    1623,   847,   191,   363,   104,  2002,    99,   399,  1692,  1693,
     363,   103,  1787,  1995,     7,   998,   103,   103,   410,   411,
     365,  1644,   349,  1798,    20,   871,   847,  1711,  1712,    85,
     103,   103,   878,  1964,   103,  1966,  1967,   134,   365,   103,
     103,   365,     5,  2325,   103,   190,  1405,   104,  1407,  1980,
     871,   363,   151,   103,   311,  1986,   103,   103,   294,   103,
    1862,  2024,  1993,  1994,   105,  1749,  1997,   295,   365,  1692,
     187,  2034,  2003,   226,   227,   228,   229,   230,  2041,  2010,
    2011,  2012,  1766,   364,   364,     1,   364,  1862,     4,   364,
       6,   364,   349,   364,   364,   364,  2010,  2011,  2012,    41,
    1459,   364,   278,  1787,     7,   364,   134,   998,   365,   365,
      26,    27,    28,    29,  1798,   103,   365,  2114,   364,  1921,
     319,   320,   321,   322,   323,    41,  1749,   364,    44,  2056,
     104,   364,     8,   979,  1889,  1890,     8,   103,  2135,   103,
       5,     8,   104,  1766,   103,   103,  1921,   993,   994,   995,
     996,   997,   998,   363,  1000,  1018,  1016,  1329,  2056,   907,
     793,  1017,  2119,   792,  1787,   791,  2093,  1133,   572,   794,
    2101,  1491,  2129,   349,    20,  1798,   562,   998,  1862,  1020,
    1026,   278,     1,   281,  2115,     4,   282,     6,     1,   365,
     429,     4,  2119,     6,  1464,  1771,  2264,  2125,  2127,  1045,
    2189,  2191,  2129,  2190,  2192,  2136,  2137,    26,    27,    28,
      29,  2181,  2306,    26,    27,    28,    29,  2148,  2149,  1724,
    2151,  2152,  2153,  2154,  2155,   287,  1926,  2158,    41,   426,
     899,    44,   889,  1908,  1877,  1879,   962,  1921,   428,  1862,
    1102,  2180,  2251,  1602,  1377,  1379,  1378,  2204,   164,  1396,
     982,  1621,   349,   319,  2056,    79,    80,    81,    82,    83,
      84,   112,   113,   872,  1623,  1124,  1623,  2264,   365,   991,
     878,   216,  1403,  1444,  2205,  1333,   127,  2204,   129,   130,
     131,  2056,  1603,  2214,  1456,  1644,  1458,  1459,  1460,  1461,
    1635,  2093,   411,  1640,   438,   114,  2314,   439,  1921,   440,
     332,   152,   153,   154,   441,   718,   333,  2304,   333,  1292,
     695,   662,  2269,  1192,    -1,    -1,    -1,  2119,  2093,    -1,
      -1,  2252,  2253,  2254,  2255,    -1,  2253,  2129,    -1,  2260,
    2261,  2262,  2263,  1692,  2331,    -1,  2267,    -1,  2252,  2253,
    2254,  2255,  2269,    -1,  2119,  2276,  2260,  2261,  2262,  2263,
      -1,   164,    -1,  2284,  2129,  2253,    -1,   112,   113,  2290,
    2291,  2292,  2293,  2294,  2295,  2296,  2297,  2298,  2299,  2300,
    2301,   126,  2056,    -1,    -1,    -1,   292,  1239,  1240,   134,
      -1,  2295,  2296,  2297,  2315,   993,   994,   995,   996,   997,
    1749,    -1,  1000,    -1,    -1,   150,    -1,    -1,    -1,    -1,
    1572,  1292,  2204,  1575,    -1,  1577,    -1,  1766,  1580,  2093,
    2341,  2342,  2343,  2097,    -1,    -1,     1,    -1,  1026,     4,
      -1,     6,  1405,    -1,  1407,    -1,    -1,    -1,  1787,  2204,
      -1,    -1,    -1,  2056,  1296,  2119,    -1,  1045,    -1,  1798,
      45,    26,    27,    28,    29,  2129,  1292,    -1,    -1,   365,
      -1,  2253,   112,   113,    -1,    60,    61,    -1,    -1,   278,
      -1,   121,   122,   123,   124,   125,    -1,  2269,  1640,    -1,
    2093,  1292,    37,    -1,    -1,    -1,  1459,    -1,  2253,   292,
      45,    -1,    47,    -1,    49,    37,   878,    52,    53,    54,
      -1,    56,    -1,    45,  2269,    47,  2119,    -1,    -1,    -1,
      52,    53,    54,  1862,    56,   110,  2129,  1353,  1354,    -1,
    1356,    -1,    -1,    -1,  1405,   120,  1407,    -1,    -1,    -1,
    2204,   126,    -1,   278,   279,   280,   281,    -1,    -1,    -1,
     349,    -1,    -1,    -1,   926,    -1,    -1,    -1,    -1,   294,
     295,   296,    -1,    -1,    -1,   150,   365,    -1,    -1,    -1,
      -1,    -1,   365,    -1,    -1,    -1,    -1,    -1,    45,  1405,
      -1,  1407,  1921,    -1,    -1,    -1,    -1,    45,  1459,  2253,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,  2204,    60,    61,  1405,  2269,  1407,    -1,  1434,  1435,
    1436,  1437,  1438,  1439,  1440,  1441,  1442,  1443,  1444,    -1,
      -1,   993,   994,   995,   996,   997,    -1,    -1,  1000,    -1,
      -1,    -1,    -1,  1459,  1786,  1787,  1788,  1789,    -1,  1602,
      -1,  1483,    -1,   110,  1486,    -1,  1798,    -1,    -1,    -1,
    2253,    -1,   110,   120,  1026,    70,    -1,    -1,  1459,   126,
    1623,    76,   120,    -1,    -1,    -1,  2269,    -1,   126,    45,
      -1,    -1,    -1,  1045,  1826,  1827,  1828,    -1,   844,    -1,
     846,  1644,    -1,   150,    60,    61,    -1,    -1,    -1,   104,
     105,   106,   150,    -1,    -1,    -1,   111,   863,    -1,   865,
     115,   867,    -1,    -1,    37,   120,    -1,   873,   874,    -1,
      -1,   126,    45,    -1,    47,   130,    49,  2056,    -1,    52,
      53,    54,    -1,    56,    -1,  1567,    -1,    60,    61,  1692,
      -1,  1602,   277,    -1,   110,   150,    -1,    -1,    -1,   905,
      -1,    -1,   908,    -1,   120,   277,   311,   292,    -1,    -1,
     126,    -1,  1623,    -1,  2093,    -1,    -1,    -1,    -1,    -1,
     292,    -1,    -1,    -1,  1606,   310,  1608,  1609,    -1,  1611,
     315,    -1,   317,  1644,   150,    -1,  1602,   110,   310,    -1,
    2119,    -1,    -1,   315,   349,   317,  1749,   120,    -1,    -1,
    2129,    -1,    -1,   126,    -1,  1621,    45,  1623,  1624,    -1,
     365,  1602,  1628,  1766,    -1,    -1,    -1,   973,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,  1642,   150,  1644,    -1,
      -1,  1692,  1623,    -1,  1787,    -1,  1652,    -1,    -1,  1655,
      -1,    -1,  1658,    -1,    -1,  1798,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1644,    -1,    -1,  1434,  1435,  1436,  1437,
    1438,  1439,  1440,  1441,  1442,  1443,  1444,    -1,  2010,  2011,
    2012,   110,    -1,    -1,    -1,  2204,  1692,  1693,    -1,    -1,
      -1,   120,   287,    -1,    -1,   290,   291,   126,  1749,    -1,
    1046,  1047,   297,    -1,    -1,  1711,  1712,    -1,   112,   113,
      -1,  1692,   116,    -1,    -1,  1766,    -1,    -1,    -1,  1862,
      -1,   150,    -1,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   327,   328,  2253,    -1,  1787,    -1,    -1,    -1,
      -1,    -1,    23,  1749,    37,    -1,    -1,  1798,    -1,    42,
    2269,    -1,    45,    46,    47,    48,    -1,    38,    51,    52,
    1766,    54,    55,    56,   277,    58,    -1,    -1,  1749,    -1,
      -1,    -1,    -1,   177,   369,    -1,    -1,    -1,  1921,   292,
      -1,  1787,    -1,    -1,    -1,  1766,    -1,    -1,    -1,    -1,
      -1,    -1,  1798,    -1,    -1,    -1,    -1,   310,    -1,    -1,
      -1,    -1,   315,    -1,   317,    98,  1787,   100,   101,   102,
      -1,  1862,    -1,    -1,    -1,    -1,     1,  1798,    -1,     4,
      -1,     6,   103,  1375,  1376,  1377,  1378,  1379,    -1,  1381,
    1382,    -1,    -1,   113,   114,    -1,   116,    -1,  1390,  1391,
      -1,    26,    27,    28,    29,    -1,    -1,    -1,  1870,    -1,
      -1,    -1,    37,    -1,    -1,   135,  1862,    -1,    -1,    -1,
    1628,    -1,    47,   143,   144,    -1,   146,    52,    -1,    54,
    1921,    56,    -1,    -1,  1642,    -1,   156,   157,   158,    -1,
      -1,  1862,  1434,  1435,  1436,  1437,  1438,  1439,  1440,  1441,
    1442,  1443,  1444,    -1,   175,    -1,    -1,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
      -1,    -1,    -1,  2056,    -1,  1921,    -1,    -1,    -1,    -1,
    2252,  2253,  2254,  2255,    -1,  1693,    -1,    -1,  2260,  2261,
    2262,  2263,    -1,  1279,    -1,    -1,    -1,  1283,    -1,    -1,
    1921,    -1,    -1,  1711,  1712,    -1,    -1,  1293,  1294,  1295,
    2093,    -1,  1298,    -1,  1300,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2295,  2296,  2297,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2119,  1323,    -1,   164,
      -1,    -1,    -1,    -1,   277,    -1,  2129,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   292,
      -1,    -1,    -1,  2025,    -1,  2056,   299,   300,   301,   302,
      -1,    -1,    -1,  2035,  1360,    -1,  1362,   310,    -1,    -1,
    2042,    -1,   315,  1369,   317,   318,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1384,    -1,
    1386,    -1,  2093,    -1,    -1,    -1,    -1,    -1,   109,  1395,
    2056,  1397,    -1,    -1,    -1,  2077,    -1,    -1,    -1,    -1,
      -1,  2204,    -1,    38,    -1,   126,    -1,    -1,  2119,    -1,
      -1,    -1,    -1,    -1,    -1,  2056,  1628,    -1,  2129,    -1,
      -1,   142,    -1,    -1,    -1,    -1,   147,  2093,    -1,   150,
    1642,  2097,   277,    -1,   155,    -1,    -1,    -1,   159,    -1,
      -1,   162,   163,    -1,    -1,    -1,   167,   292,    -1,   170,
    2253,   172,  2093,  2119,    -1,    -1,    -1,  2139,  2140,  2141,
      -1,    -1,    -1,  2129,    -1,   310,  2269,    -1,   103,    -1,
     315,    -1,   317,    -1,    -1,    -1,   197,    -1,  2119,    -1,
      -1,  1693,   203,  2165,    -1,    -1,    -1,    -1,  2129,    -1,
      -1,    -1,    -1,  2204,    -1,    -1,    -1,    -1,    -1,  1711,
    1712,    -1,     1,    -1,   349,     4,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     365,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2204,    -1,
     175,    40,  2253,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,    -1,    -1,  2269,    -1,
      -1,    -1,    -1,  2204,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1583,  1584,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2253,    -1,    -1,
      89,    90,    91,    92,    -1,    94,    -1,    -1,    97,    -1,
      -1,    -1,    -1,  2269,  1610,   135,    -1,    -1,    -1,    -1,
       1,    -1,  2253,    -1,   144,   114,    -1,    -1,    -1,  1625,
      11,    12,    13,    14,    15,    16,    17,    -1,  2269,    20,
     160,    90,    -1,    -1,   164,    -1,    -1,    -1,   168,   169,
    2322,  2323,  2324,   173,   174,   175,   176,   177,    -1,    -1,
      -1,    -1,    -1,   112,   113,  1661,    -1,   116,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   164,    -1,    -1,    -1,  2097,
      -1,    -1,  1678,    -1,  1680,   134,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    -1,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    94,    95,    96,    97,    -1,    99,   100,
     101,   102,    -1,   104,    -1,    -1,    -1,   108,    -1,   110,
      -1,    -1,   113,   114,    -1,   116,    -1,    -1,   119,    -1,
      -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   133,   134,   135,   136,   137,    -1,   139,   140,
      -1,    -1,   143,   144,   145,   146,    -1,    -1,   149,    -1,
     151,    -1,    -1,    -1,     1,    -1,    -1,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,   292,    -1,   254,    -1,    -1,   297,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   310,    -1,    -1,    -1,    -1,   315,    -1,    -1,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,    -1,    -1,   294,   295,   296,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1855,
     349,    -1,    89,    90,    91,    92,    -1,    94,   317,    -1,
      97,    -1,    -1,    -1,    -1,    -1,   365,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,
      -1,    -1,  1888,    -1,    -1,  2097,    -1,    -1,    -1,   280,
     281,   282,   283,   284,   285,   286,   287,    -1,   289,   290,
     291,   292,    -1,     1,    -1,    -1,     4,    -1,     6,  1915,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,   164,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    80,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    -1,    -1,   109,    -1,   111,    94,    -1,    -1,   115,
      98,    -1,   100,    -1,   120,   103,   104,   105,   106,    -1,
     126,   109,    -1,   111,    -1,    -1,   114,   115,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,   142,    -1,   126,    -1,
      -1,   147,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,
     277,    -1,    -1,   159,   142,    -1,   162,   163,   164,   147,
      -1,   167,   150,    -1,   170,   292,   172,   155,    -1,    -1,
     297,   159,    -1,    -1,   162,   163,   164,    -1,    -1,   167,
      -1,    -1,   170,   310,   172,    -1,    -1,    -1,   315,    -1,
      -1,   197,    -1,   199,    -1,  2091,    -1,   203,    -1,    -1,
      -1,   482,    -1,    -1,    -1,    -1,    -1,    -1,   489,   197,
     198,    -1,   200,   201,   202,   203,    -1,    -1,    -1,   500,
      -1,   502,   349,   504,    -1,   506,    -1,    -1,    -1,    -1,
     511,    -1,    -1,    -1,   515,   516,    -1,    -1,   365,    -1,
      -1,    -1,    -1,    -1,   525,    -1,    -1,   528,    -1,    -1,
     238,   239,   240,   241,    -1,    -1,    -1,   538,    -1,   247,
     248,    -1,    -1,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,    -1,    -1,   277,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   292,    -1,    -1,    -1,    -1,   297,
      -1,    -1,    -1,    -1,    -1,    -1,   304,    -1,    -1,    -1,
      -1,    -1,   310,    -1,    -1,    -1,    -1,   315,    -1,    -1,
      -1,    -1,    -1,   321,   322,    -1,   324,    -1,    -1,   327,
     328,   329,   330,    -1,    -1,    -1,   334,    -1,    -1,    -1,
     338,   339,   340,    -1,    -1,    -1,   344,   345,    -1,    -1,
      -1,   349,    -1,    -1,    -1,   353,    -1,     1,   356,   357,
       4,    -1,     6,    -1,   362,    -1,   364,   365,   366,    -1,
      -1,   369,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    80,    81,    82,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,   103,
     104,   105,   106,    -1,    -1,   109,    -1,   111,    -1,    -1,
     114,   115,    -1,    -1,     1,    -1,   120,     4,    -1,     6,
      -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,    26,
      27,    28,    29,   147,    -1,    -1,   150,   182,    -1,    -1,
      -1,   155,    -1,    40,    -1,   159,    -1,    -1,   162,   163,
     164,    -1,    -1,   167,    -1,    -1,   170,    -1,   172,    -1,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,    -1,    -1,    -1,
      -1,    -1,    -1,   197,   198,    -1,   200,   201,   202,   203,
      -1,    -1,    89,    90,    91,    92,    -1,    94,    -1,    -1,
      97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,
      -1,    -1,    -1,    -1,   238,   239,   240,   241,    -1,    -1,
      -1,    -1,    -1,   247,   248,    -1,    -1,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,    -1,    -1,   277,    -1,    -1,    -1,   164,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   292,    -1,
      -1,    -1,    -1,   297,    -1,    -1,    -1,    -1,    -1,    -1,
     304,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,
      -1,   315,    -1,    -1,    -1,    -1,    -1,   321,   322,    -1,
     324,    -1,    -1,   327,   328,   329,   330,    -1,    -1,    -1,
     334,    -1,    -1,    -1,   338,   339,   340,    -1,    -1,    -1,
     344,   345,    -1,    -1,    -1,   349,    -1,    -1,    -1,   353,
      -1,     1,   356,   357,     4,    -1,     6,    -1,   362,    -1,
     364,   365,   366,    -1,    -1,   369,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,
     277,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,   292,    -1,    -1,    -1,    -1,
     297,    -1,    62,    63,    -1,    -1,    -1,    67,    -1,    -1,
      70,    -1,    -1,   310,    -1,    -1,    -1,    -1,   315,    79,
      80,    81,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,    98,    -1,
     100,    -1,  1103,   103,   104,   105,   106,    -1,    -1,   109,
      -1,   111,   349,    -1,   114,   115,    -1,    -1,     1,    -1,
     120,     4,    -1,     6,    -1,    -1,   126,    -1,   365,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   142,    26,    27,    28,    29,   147,    -1,    -1,
     150,    -1,    -1,    -1,    -1,   155,    -1,    40,    -1,   159,
      -1,    -1,   162,   163,   164,    -1,    -1,   167,    -1,    -1,
     170,    -1,   172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   197,   198,    -1,
     200,   201,   202,   203,    -1,    -1,    -1,    90,    91,    92,
      -1,    94,    -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,   238,   239,
     240,   241,    -1,    -1,    -1,    -1,    -1,   247,   248,    -1,
      -1,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,    -1,    -1,   277,    -1,    -1,
      -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   292,    -1,    -1,    -1,    -1,   297,    -1,    -1,
      -1,    -1,    -1,    -1,   304,    -1,    -1,    -1,    -1,    -1,
     310,    -1,    -1,    -1,    -1,   315,    -1,    -1,    -1,    -1,
      -1,   321,   322,    -1,   324,    -1,    -1,   327,   328,   329,
     330,    -1,    -1,    -1,   334,    -1,    -1,    -1,   338,   339,
     340,    -1,    -1,    -1,   344,   345,    -1,    -1,    -1,   349,
      -1,    -1,    -1,   353,    -1,     1,   356,   357,     4,    -1,
       6,    -1,   362,    -1,   364,   365,   366,    -1,    -1,   369,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    35,
      36,    37,    -1,    -1,   277,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,   292,
      -1,    -1,    -1,    -1,   297,    -1,    62,    63,    -1,    -1,
      -1,    67,    -1,    -1,    70,    -1,    -1,   310,    -1,    -1,
      -1,    -1,   315,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,
      -1,    -1,    98,    -1,   100,    -1,    -1,   103,   104,   105,
     106,    -1,    -1,   109,    -1,   111,   349,    -1,   114,   115,
      -1,    -1,     1,    -1,   120,     4,    -1,     6,    -1,    -1,
     126,    -1,   365,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   142,    26,    27,    28,
      29,   147,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,
      -1,    40,    -1,   159,    -1,    -1,   162,   163,   164,    -1,
      -1,   167,    -1,    -1,   170,    -1,   172,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   197,   198,    -1,   200,   201,   202,   203,    -1,    -1,
      -1,    90,    91,    92,    -1,    94,    -1,    -1,    97,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,
      -1,    -1,   238,   239,   240,   241,    -1,    -1,    -1,    -1,
      -1,   247,   248,    -1,    -1,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,    -1,
      -1,   277,    -1,    -1,    -1,   164,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   292,    -1,    -1,    -1,
      -1,   297,    -1,    -1,    -1,    -1,    -1,    -1,   304,    -1,
      -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,   315,
      -1,    -1,    -1,    -1,    -1,   321,   322,    -1,   324,    -1,
      -1,   327,   328,   329,   330,    -1,    -1,    -1,   334,    -1,
      -1,    -1,   338,   339,   340,     4,    -1,     6,   344,   345,
      -1,    -1,    -1,   349,    -1,    -1,    -1,   353,    -1,    -1,
     356,   357,    -1,    -1,    23,    -1,   362,    -1,   364,   365,
     366,    30,    31,   369,    -1,    -1,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,   277,    -1,
      -1,    -1,    -1,    62,    63,    -1,    -1,   104,    67,    -1,
      -1,    70,    -1,   292,    -1,    -1,    -1,    -1,   297,    -1,
      79,    80,    81,    82,    83,    84,    -1,    -1,    -1,    -1,
      -1,   310,    -1,    -1,   131,    -1,   315,   134,    -1,    98,
      -1,   100,    -1,    -1,   103,   104,   105,   106,    -1,    -1,
     109,    -1,   111,    -1,   151,    -1,   115,    -1,    -1,    -1,
      -1,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,
     349,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    -1,   365,    -1,   147,    -1,
      -1,   150,    -1,    -1,     1,    -1,   155,     4,    -1,     6,
     159,    -1,    -1,   162,   163,    -1,    -1,    -1,   167,    -1,
      -1,   170,    -1,   172,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   197,   198,
      47,   200,   201,   202,   203,    52,    -1,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,    -1,   238,
     239,   240,   241,    -1,    -1,    -1,    -1,    -1,   247,   248,
      -1,    -1,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,    -1,    -1,   277,    -1,
     317,    -1,     5,    -1,   321,   322,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   292,   331,    -1,    -1,    -1,   297,    -1,
      23,    -1,    -1,    -1,    -1,   304,    -1,    -1,    31,    -1,
      -1,   310,    -1,    36,    -1,    -1,   315,   164,    -1,    -1,
     357,    -1,   321,   322,    -1,   324,    -1,    -1,   327,   328,
     329,   330,    -1,    -1,    -1,   334,    -1,    -1,    -1,   338,
     339,   340,    -1,    -1,    -1,   344,   345,    70,    -1,    -1,
      -1,    -1,    -1,    76,   353,    -1,    -1,   356,   357,    -1,
      -1,    -1,    85,   362,    87,   364,   365,   366,    -1,    -1,
     369,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,   104,   105,   106,    -1,    -1,   109,    -1,   111,    -1,
      -1,    -1,   115,    -1,    -1,    -1,    -1,   120,    -1,    -1,
      -1,    -1,    -1,   126,    -1,    -1,    -1,   130,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,
      -1,    -1,    -1,    -1,   147,    -1,    -1,   150,    -1,    -1,
     277,    -1,   155,    -1,    -1,    -1,   159,    -1,    -1,   162,
     163,    -1,    -1,    -1,   167,   292,    -1,   170,    -1,   172,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,   315,    -1,
     317,    -1,    -1,    -1,   197,   198,    -1,   200,   201,   202,
     203,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,    -1,    -1,   112,   113,    -1,
      -1,   116,   349,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,   238,    -1,    31,   365,   134,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,    -1,    -1,   277,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    76,    -1,   287,    -1,    -1,   290,   291,    -1,
      -1,    -1,    -1,    -1,   297,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   305,    -1,    -1,    -1,    -1,    -1,    -1,   103,
     104,   105,   106,    -1,    -1,   109,    -1,   111,   321,   322,
      -1,   115,    -1,    -1,   327,   328,   120,    -1,    -1,    -1,
      -1,    -1,   126,    -1,    -1,    -1,   130,   340,    -1,    -1,
      -1,   344,   345,    -1,    -1,    -1,    -1,    -1,   142,    -1,
      -1,   354,   355,   147,   357,    -1,   150,    -1,    -1,   254,
      -1,   155,    -1,   366,    -1,   159,   369,    -1,   162,   163,
      -1,    -1,    -1,   167,    -1,    -1,   170,    -1,   172,    -1,
      -1,    -1,    -1,   278,   279,   280,   281,   282,   283,    -1,
     285,   286,   287,   288,   289,   290,   291,    -1,    -1,   294,
     295,   296,    -1,   197,   198,    -1,   200,   201,   202,   203,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,    -1,   317,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,   238,    -1,    31,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,    -1,    -1,   277,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    76,    -1,   287,    -1,    -1,   290,   291,    -1,    -1,
      -1,    -1,    -1,   297,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,    -1,    -1,   109,    -1,   111,   321,   322,    -1,
     115,    -1,    -1,   327,   328,   120,    -1,    -1,   109,    -1,
     111,   126,    -1,   114,   115,   130,   340,    -1,    -1,   120,
     344,   345,    -1,    -1,    -1,   126,    -1,   142,    -1,    -1,
     354,   355,   147,   357,    -1,   150,    -1,    -1,    -1,    -1,
     155,   142,   366,    -1,   159,   369,   147,   162,   163,   150,
      -1,    -1,   167,    -1,   155,   170,    -1,   172,   159,    -1,
      -1,   162,   163,    -1,    -1,    -1,   167,    -1,    -1,   170,
      -1,   172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   197,   198,    -1,   200,   201,   202,   203,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,   199,     5,
      -1,    -1,   203,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,   238,    -1,    31,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      -1,    -1,   277,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      76,    -1,   287,    -1,    -1,   290,   291,    -1,    -1,    -1,
      -1,    -1,   297,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,
     106,    -1,    -1,   109,    -1,   111,   321,   322,    -1,   115,
      -1,    -1,   327,   328,   120,    -1,    -1,   109,    -1,   111,
     126,    -1,    -1,   115,   130,   340,    -1,    -1,   120,   344,
     345,    -1,    -1,    -1,   126,    -1,   142,    -1,    -1,   354,
     355,   147,   357,    -1,   150,    -1,    -1,    -1,    -1,   155,
     142,   366,    -1,   159,   369,   147,   162,   163,   150,    -1,
      -1,   167,    -1,   155,   170,    -1,   172,   159,    -1,    -1,
     162,   163,    -1,    -1,    -1,   167,    -1,    -1,   170,    -1,
     172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   197,   198,    -1,   200,   201,   202,   203,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,     5,    -1,
      -1,   203,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,   238,    -1,    31,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,    -1,
      -1,   277,    -1,    70,    -1,    -1,    -1,    -1,    -1,    76,
      -1,   287,    -1,    -1,   290,   291,    -1,    -1,    -1,    -1,
      -1,   297,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,
      -1,    -1,   109,    -1,   111,   321,   322,    -1,   115,    -1,
      -1,   327,   328,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,   130,   340,    -1,    -1,    -1,   344,   345,
      -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,   354,   355,
     147,   357,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,
     366,    -1,   159,   369,    -1,   162,   163,    -1,    -1,    -1,
     167,    -1,    -1,   170,    -1,   172,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,     4,    -1,     6,    -1,    -1,
     197,   198,    -1,   200,   201,   202,   203,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   238,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,    -1,    -1,
     277,    90,    91,    92,    -1,    94,    -1,    -1,    97,    -1,
     287,    -1,    -1,   290,   291,    -1,    -1,    -1,    -1,    -1,
     297,    -1,    -1,    -1,    -1,   114,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      23,    -1,    -1,    -1,   321,   322,    -1,    -1,    -1,    -1,
     327,   328,    -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,   340,    -1,    -1,    -1,   344,   345,    -1,
      -1,    -1,    -1,    -1,    -1,   164,    -1,   354,   355,    -1,
     357,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,   366,
      -1,    -1,   369,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,   104,   105,   106,    -1,    -1,    -1,    -1,   111,    -1,
      -1,    -1,   115,    -1,    -1,    -1,    -1,   120,   103,   104,
     105,   106,    -1,   126,    -1,    -1,   111,   130,    -1,    -1,
     115,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,   142,
      21,   126,    -1,    -1,   147,   130,    -1,   150,    -1,    -1,
      -1,    -1,   155,    -1,    -1,    -1,   159,   142,    -1,   162,
     163,    -1,   147,    -1,   167,   150,    -1,   170,   277,   172,
     155,    -1,    -1,    -1,   159,    -1,    -1,   162,   163,    -1,
      -1,    -1,   167,   292,    -1,   170,    -1,   172,   297,    70,
      -1,    -1,    -1,    -1,   197,    76,    -1,   200,    -1,    -1,
     203,   310,    -1,    -1,    -1,    -1,   315,    -1,    -1,    -1,
      -1,    -1,   197,    -1,    -1,   200,    -1,    -1,   203,    -1,
      -1,    -1,   103,   104,   105,   106,    -1,    -1,    -1,    -1,
     111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,   120,
     349,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,   130,
      -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,    -1,    -1,
      -1,   142,    -1,    -1,    -1,    -1,   147,    -1,    -1,   150,
      -1,    -1,    -1,    -1,   155,    -1,    -1,    -1,   159,    -1,
      -1,   162,   163,    -1,   287,    -1,   167,   290,   291,   170,
      -1,   172,    -1,    -1,   297,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   287,    -1,    -1,   290,   291,    -1,    -1,    -1,
      -1,    -1,   297,    -1,    -1,    -1,   197,    -1,    -1,   200,
      -1,    -1,   203,    -1,   327,   328,    -1,   330,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   327,   328,    -1,   330,    -1,    -1,    -1,    -1,
      -1,   354,   355,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,   364,    -1,   366,    -1,    -1,   369,    -1,    -1,   354,
     355,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   364,
      -1,   366,    -1,    -1,   369,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   287,    70,    -1,   290,
     291,    -1,    -1,    76,    -1,    -1,   297,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,   104,   105,   106,    -1,    -1,   327,   328,   111,   330,
      -1,    -1,   115,    -1,    -1,    -1,    -1,   120,    -1,    -1,
      -1,    -1,    -1,   126,    -1,    -1,    -1,   130,    -1,    -1,
      -1,    -1,    -1,   354,   355,    -1,    -1,    -1,    -1,   142,
      -1,    -1,    -1,    -1,   147,   366,    -1,   150,   369,    -1,
      -1,    -1,   155,    -1,    -1,    -1,   159,    -1,    -1,   162,
     163,    -1,    -1,    -1,   167,    -1,    23,   170,    -1,   172,
      -1,    -1,    -1,    30,    31,    -1,    -1,    -1,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   197,    52,    -1,   200,    -1,    -1,
     203,    -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    81,    82,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,   100,    -1,    -1,   103,   104,   105,   106,
      -1,    -1,   109,    -1,   111,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   287,   142,    -1,   290,   291,    -1,
     147,    -1,    -1,   150,   297,    -1,    -1,    -1,   155,    -1,
      -1,    -1,   159,    -1,    -1,   162,   163,    -1,    -1,    -1,
     167,    -1,    -1,   170,    -1,   172,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   327,   328,    -1,   330,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     197,   198,    -1,   200,   201,   202,   203,    -1,    -1,    -1,
      -1,   354,   355,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   364,    -1,   366,    -1,    -1,   369,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,
     247,   248,    -1,    -1,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,    -1,    -1,
     277,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,   292,    -1,    -1,    -1,    -1,
     297,    31,    -1,    -1,    -1,    -1,    36,   304,    -1,    -1,
      -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,   315,    -1,
      -1,    -1,    -1,    -1,   321,   322,    -1,   324,    -1,    -1,
     327,   328,   329,   330,    -1,    -1,    -1,   334,    -1,    -1,
      70,   338,   339,   340,    -1,    -1,    76,   344,   345,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   353,    -1,    -1,   356,
     357,    -1,    -1,    -1,    -1,   362,    -1,   364,    -1,   366,
      -1,    -1,   369,   103,   104,   105,   106,    -1,    -1,   109,
      -1,   111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,
     120,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,
     130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   142,    -1,    -1,    -1,    -1,   147,    -1,    -1,
     150,    -1,    -1,    -1,    -1,   155,    -1,    -1,    -1,   159,
      -1,    -1,   162,   163,    -1,    -1,    -1,   167,    -1,    -1,
     170,    -1,   172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   197,   198,    -1,
     200,   201,   202,   203,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,   238,    30,
      31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,    -1,    -1,   277,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   287,    -1,    -1,
     290,   291,    -1,    -1,    -1,    -1,    -1,   297,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   104,   105,   106,    -1,    -1,   109,    -1,
     111,   321,   322,    -1,   115,    -1,    -1,   327,   328,   120,
      -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,
     340,    -1,    -1,    -1,   344,   345,    -1,    -1,    -1,    -1,
      -1,   142,    -1,    -1,   354,   355,   147,   357,    -1,   150,
      -1,    -1,    -1,    -1,   155,    -1,   366,    -1,   159,   369,
      -1,   162,   163,    -1,    -1,    -1,   167,    -1,    -1,   170,
      -1,   172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   197,   198,    -1,   200,
     201,   202,   203,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   238,   239,   240,
     241,    -1,    -1,    -1,    -1,    -1,   247,   248,    -1,    -1,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,    87,    -1,   277,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,   104,   105,   106,    -1,    -1,   109,    -1,   111,    -1,
      -1,    -1,   115,    -1,    -1,    -1,    -1,   120,    -1,    -1,
      -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,
     321,   322,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,
      -1,    -1,    -1,    -1,   147,    -1,    -1,   150,    -1,   340,
      -1,    -1,   155,   344,   345,    -1,   159,    -1,    -1,   162,
     163,    -1,    -1,    -1,   167,   356,   357,   170,    -1,   172,
      -1,    -1,    -1,   364,    -1,   366,    -1,    -1,   369,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   197,   198,    23,   200,   201,   202,
     203,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   238,   239,   240,   241,    -1,
      -1,    -1,    -1,    -1,   247,   248,    -1,    -1,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,    -1,    -1,   277,    -1,   103,   104,   105,   106,
      -1,    -1,   109,    -1,   111,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,   321,   322,
     147,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,
      -1,    -1,   159,    -1,    -1,   162,   163,   340,    -1,    -1,
     167,   344,   345,   170,    -1,   172,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   356,   357,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   366,    -1,    -1,   369,    -1,    -1,    -1,
     197,   198,    -1,   200,   201,   202,   203,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,
     247,   248,    -1,    -1,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,    70,    -1,
     277,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,    -1,    -1,    -1,    -1,   111,
      -1,    -1,    -1,   115,   321,   322,    -1,    -1,   120,    -1,
      -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,   130,    -1,
      -1,    -1,    -1,   340,    -1,    -1,    -1,   344,   345,    -1,
     142,    -1,    -1,    -1,    -1,   147,    -1,    -1,   150,   356,
     357,    -1,    -1,   155,    -1,    -1,    -1,   159,    -1,   366,
     162,   163,   369,    -1,    -1,   167,    -1,    -1,   170,    -1,
     172,    -1,    -1,    -1,    -1,    -1,    -1,     0,     1,    -1,
      -1,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,   200,    -1,
      -1,   203,    -1,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,    52,
      53,    54,    -1,    56,    -1,    -1,    -1,    60,    61,    62,
      -1,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,    -1,    -1,   287,    -1,   110,   290,   291,
      -1,    -1,    -1,    -1,    -1,   297,    -1,   120,    70,    -1,
      -1,    -1,    -1,   126,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   327,   328,   150,   330,    -1,
      -1,   103,   104,   105,   106,    -1,    -1,    -1,    -1,   111,
      -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,   120,    -1,
      -1,    -1,   354,   355,   126,    -1,    -1,    -1,   130,    -1,
      -1,    -1,   364,    -1,   366,    -1,    -1,   369,    -1,    -1,
     142,    -1,    -1,    -1,    -1,   147,    -1,    -1,   150,    70,
      -1,    -1,    -1,   155,    -1,    76,    -1,   159,    -1,    -1,
     162,   163,    -1,    -1,    -1,   167,    -1,    -1,   170,    -1,
     172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   104,   105,   106,    -1,    -1,    -1,    -1,
     111,    -1,    -1,    -1,   115,   197,    -1,    -1,   200,   120,
      -1,   203,    -1,    -1,    -1,   126,    -1,    -1,    -1,   130,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,    -1,    -1,   277,    -1,   147,    -1,    -1,   150,
      -1,    -1,    -1,    -1,   155,    -1,    -1,    -1,   159,   292,
      -1,   162,   163,    -1,   297,    -1,   167,    -1,    -1,   170,
      -1,   172,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,
      -1,    -1,   315,    -1,   317,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,   200,
      -1,    -1,   203,    -1,    -1,   287,    -1,    -1,   290,   291,
      -1,    -1,    -1,    -1,    -1,   297,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   327,   328,    -1,   330,    -1,
     104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   354,   355,    -1,    -1,    -1,   131,    -1,    -1,
     134,    -1,    -1,    -1,   366,    -1,   287,   369,    -1,   290,
     291,   103,   104,   105,   106,    -1,   297,   151,    -1,   111,
      -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,   120,    -1,
      -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,   130,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   327,   328,    -1,   330,
     142,    -1,    -1,    -1,    -1,   147,    -1,    -1,   150,    -1,
      -1,    -1,    -1,   155,    -1,    -1,    -1,   159,    -1,    -1,
     162,   163,    -1,   354,   355,   167,    -1,    -1,   170,    -1,
     172,    -1,    -1,    -1,    -1,   366,    -1,    -1,   369,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,   200,    -1,
      -1,   203,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   317,    -1,    -1,    -1,   321,   322,    -1,
      -1,    -1,    -1,    -1,    -1,   287,    -1,   331,   290,   291,
      -1,    -1,    -1,    -1,    -1,   297,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   357,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   327,   328,    -1,   330,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   354,   355,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   366,    -1,    -1,   369
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   373,     0,     1,     4,     6,    26,    27,    28,    29,
      37,    45,    47,    49,    52,    53,    54,    56,    60,    61,
      62,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,   110,   120,   126,   150,   277,
     292,   310,   315,   317,   374,   430,   431,   432,   433,   508,
     509,   510,   512,   527,   374,   105,   104,   297,   504,   504,
     504,   510,   521,   510,   512,   527,   510,   515,   515,   515,
     510,   518,   433,    49,   434,    37,    45,    47,    52,    53,
      54,    56,   277,   292,   310,   315,   317,   435,    49,   436,
      37,    45,    47,    49,    52,    53,    54,    56,   277,   292,
     310,   315,   317,   441,    53,   443,    37,    42,    45,    46,
      47,    48,    51,    52,    54,    55,    56,    58,    98,   100,
     101,   102,   277,   292,   299,   300,   301,   302,   310,   315,
     317,   318,   444,    49,    50,    52,    53,    54,   292,   299,
     300,   315,   447,    45,    47,    52,    54,    58,    98,   100,
     448,    47,   449,    23,    30,    31,    36,   103,   104,   105,
     106,   109,   111,   115,   120,   126,   142,   147,   150,   155,
     159,   162,   163,   167,   170,   172,   197,   198,   200,   201,
     202,   203,   238,   239,   240,   241,   247,   248,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   277,   321,   322,   340,   344,   345,   356,   357,
     366,   369,   457,   505,   631,   632,   635,   636,   637,   641,
     704,   707,   709,   713,   718,   719,   721,   723,   733,   734,
     736,   738,   740,   742,   746,   748,   750,   752,   754,   756,
     758,   760,   762,   764,   768,   770,   772,   774,   785,   793,
     795,   797,   798,   800,   802,   804,   806,   808,   810,   812,
     814,    58,   350,   351,   352,   450,   456,    58,   451,   456,
      37,    45,    47,    49,    52,    53,    54,    56,   277,   292,
     310,   315,   317,   442,   104,   452,   453,   377,   396,   397,
      90,   284,   286,   521,   521,   521,   521,     0,   374,   504,
     504,    57,   347,   348,   524,   525,   526,    35,    37,    52,
      62,    63,    67,    70,    79,    80,    81,    82,    83,    84,
      98,   100,   253,   277,   292,   297,   304,   310,   315,   324,
     327,   328,   329,   330,   334,   338,   339,   353,   362,   364,
     531,   532,   533,   535,   536,   537,   538,   539,   540,   541,
     545,   546,   547,   550,   551,   552,   559,   563,   571,   572,
     575,   576,   577,   578,   579,   600,   601,   603,   604,   606,
     607,   610,   611,   612,   622,   623,   624,   625,   626,   629,
     630,   636,   643,   644,   645,   646,   647,   648,   652,   653,
     654,   688,   702,   707,   708,   731,   732,   733,   775,   374,
     363,   363,   374,   504,   583,   458,   461,   531,   504,   466,
     468,   631,   654,   471,   504,   477,   512,   528,   521,   510,
     512,   515,   515,   515,   518,    90,   284,   286,   521,   521,
     521,   521,   527,   440,   510,   521,   522,   437,   508,   510,
     511,   438,   510,   512,   513,   528,   439,   510,   515,   516,
     515,   515,   510,   518,   519,    90,   284,   286,   677,   440,
     440,   440,   440,   515,   521,   446,   509,   530,   510,   530,
     512,   530,    45,   530,   515,   515,   530,   518,   530,    45,
      46,   515,   530,   530,    90,   284,   303,   677,   678,   521,
      45,   530,    45,   530,    45,   530,    45,   530,   521,   521,
     521,    45,   530,   403,   528,    45,    47,   509,   510,   512,
     530,   439,   515,   439,   521,    45,   510,   530,    45,   510,
     530,   521,   415,   510,   512,   515,   515,   530,    45,   515,
     512,   104,   107,   108,   109,   735,   112,   113,   254,   255,
     258,   639,   640,    32,    33,    34,   254,   710,   133,   642,
     168,   169,   796,   112,   113,   114,   737,   114,   116,   117,
     118,   119,   739,   112,   113,   121,   122,   123,   124,   125,
     741,   112,   113,   116,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   177,   743,   114,   116,   135,   143,   144,
     145,   146,   747,   114,   135,   148,   306,   749,   112,   113,
     127,   129,   130,   131,   152,   153,   154,   751,   113,   114,
     116,   135,   143,   144,   146,   156,   157,   158,   753,   128,
     144,   153,   160,   161,   755,   144,   161,   757,   153,   164,
     165,   759,   131,   135,   168,   169,   761,   135,   168,   169,
     171,   763,   135,   144,   160,   164,   168,   169,   173,   174,
     175,   176,   177,   776,   114,   168,   169,   177,   786,   164,
     199,   736,   738,   740,   742,   746,   748,   750,   752,   754,
     756,   758,   760,   762,   764,   765,   766,   767,   769,   785,
     793,   795,   127,   134,   164,   393,   773,   393,   114,   199,
     767,   771,   135,   168,   169,   204,   237,   794,   114,   126,
     128,   146,   150,   153,   242,   275,   276,   357,   720,   722,
     801,   243,   803,   243,   805,   164,   244,   245,   246,   807,
     128,   153,   799,   116,   132,   153,   160,   249,   250,   809,
     128,   153,   811,   114,   128,   135,   153,   160,   813,   104,
     131,   134,   151,   317,   331,   357,   705,   706,   707,   112,
     113,   116,   134,   254,   278,   279,   280,   281,   282,   283,
     285,   286,   287,   288,   289,   290,   291,   294,   295,   296,
     317,   724,   725,   728,   331,   341,   712,   648,   653,   342,
     238,   247,   248,   251,   252,   815,   360,   361,   402,   715,
     647,   504,   421,   456,   351,   401,   456,   389,   440,   437,
     438,   512,   528,   439,   515,   515,   518,   519,   677,   440,
     440,   440,   440,   384,   407,    46,    48,    50,    51,    58,
      59,    92,   454,   521,   521,   521,   381,   672,   687,   674,
     676,   103,   103,   103,    85,   720,   293,   623,   172,   504,
     631,   703,   703,    62,    99,   504,   104,   705,    90,   191,
     284,   724,   725,   293,   316,   293,   311,   293,   313,   314,
     560,    85,   164,    85,    85,   720,   104,     4,   375,   655,
     656,   349,   529,   536,   429,   461,   381,   294,   295,   548,
     549,   382,   427,   164,   305,   306,   307,   308,   309,   553,
     554,   414,   325,   574,   408,     5,    70,    76,    85,    87,
     111,   115,   120,   126,   130,   150,   238,   287,   290,   291,
     297,   305,   327,   328,   354,   355,   366,   586,   587,   588,
     589,   590,   591,   592,   594,   595,   596,   597,   598,   599,
     632,   635,   641,   697,   698,   699,   704,   709,   713,   719,
     720,   721,   723,   729,   730,   733,   422,   428,    38,    39,
     187,   190,   580,   581,   408,    85,   331,   332,   333,   602,
     608,   609,   408,    85,   605,   608,   386,   392,   413,   335,
     336,   337,   613,   614,   618,   619,    23,   631,   633,   634,
      45,   627,   628,    15,    16,    17,    18,   368,     8,    24,
      54,     9,    10,    11,    12,    13,    14,    19,   111,   115,
     120,   126,   142,   147,   150,   155,   159,   162,   163,   167,
     170,   172,   197,   200,   203,   330,   366,   632,   634,   635,
     649,   650,   651,   654,   689,   690,   691,   692,   693,   694,
     695,   696,   698,   699,   700,   701,    52,    52,    22,   364,
     670,   689,   690,   695,   670,    38,   364,   582,   364,   364,
     364,   364,   364,   524,   531,   583,   458,   461,   466,   468,
     471,   477,   521,   521,   521,   381,   672,   687,   674,   676,
     531,   428,    57,    57,    57,   461,    57,   468,    57,   477,
     521,   381,   404,   412,   419,   468,   428,    43,   445,   510,
     515,   530,   521,    45,   381,   510,   510,   510,   510,   404,
     412,   419,   510,   510,   512,   468,   381,   510,   510,   412,
     515,   504,   424,     7,     8,   114,   258,   259,   638,   309,
     420,   104,   127,   293,   424,   423,   388,   423,   398,   111,
     126,   111,   126,   377,   138,   139,   140,   141,   744,   396,
     423,   399,   423,   400,   397,   423,   399,   376,   387,   379,
     425,   426,    23,    38,   103,   175,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   777,
     778,   779,   423,   103,   383,   421,   765,   393,   767,   182,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   787,   792,   417,
     423,   396,   397,   402,   722,   416,   416,   370,   416,   416,
     370,   416,   395,   391,   385,   423,   406,   405,   419,   405,
     419,   112,   113,   126,   134,   150,   278,   279,   280,   726,
     727,   728,   380,   342,   342,   103,   416,   395,   391,   385,
     406,   359,   714,   367,   428,   468,   477,   521,   381,   404,
     412,   419,   455,   456,   685,   685,   685,   294,   364,   671,
     311,   364,   686,   364,   560,   673,   364,   505,   675,     5,
     126,   150,   598,    85,   598,   620,   621,   648,   177,    23,
      23,    97,   364,    52,    52,    52,   103,   313,    52,   728,
      52,   598,   104,   298,   506,   598,   313,   314,   564,   598,
     103,   615,   616,   617,   631,   635,   648,   652,   713,   719,
     618,   598,   598,    85,   505,    21,   654,   659,   660,   661,
     668,   695,   696,     7,   365,   505,   364,   103,   103,   549,
      78,   111,   126,   172,   261,   556,   505,   103,   103,   103,
     505,   555,   554,   142,   155,   172,   326,   598,   415,   384,
       5,   598,    85,   388,   398,   377,   396,   397,   382,    85,
     408,   408,   591,   632,   699,    15,    16,    17,    18,   368,
      20,    22,     8,    54,     5,   608,    85,    87,   243,   305,
       7,     7,   103,   103,   581,     5,     7,     5,   598,   616,
     631,   635,   614,     7,   504,   364,   504,   364,   628,   700,
     700,   691,   692,   693,   647,   364,   542,   633,   690,   396,
     399,   397,   399,   376,   387,   379,   425,   426,   421,   383,
     393,   417,   408,   695,     7,    20,    15,    16,    17,    18,
     368,     7,    20,    22,     8,   689,   690,   695,   598,   598,
     103,   365,   374,    20,   374,   103,   492,   428,   460,   462,
     467,   474,   478,   582,   364,   364,   364,   364,   364,   685,
     685,   685,   671,   686,   673,   675,   103,   103,   103,   364,
     103,   103,   364,   685,   104,   380,   510,   103,   640,   423,
     390,   103,   410,   410,   388,   396,   388,   396,   114,   131,
     136,   137,   243,   396,   745,   378,    97,   783,   191,   781,
     196,   784,   194,   195,   782,   192,   193,   780,   131,   383,
     227,   231,   232,   233,   791,   222,   223,   224,   225,   789,
     226,   227,   228,   229,   230,   790,   790,   231,   234,   234,
     235,   236,   235,   114,   131,   164,   788,   418,   416,   103,
     103,   112,   113,   112,   113,   380,   380,   103,   103,   343,
     711,   103,   161,   358,   716,   720,   364,   685,   364,   364,
     364,   103,   485,   381,   564,   490,   404,   486,   103,   412,
     491,   419,   598,     5,     5,   598,   633,    90,    93,   529,
     662,   663,    38,   175,   180,   190,   778,   779,   505,   505,
     103,   648,   657,   658,   598,   598,   598,   380,   103,   598,
      52,   598,   404,   103,   566,   568,   569,   412,   104,   295,
     561,    22,   413,    85,   335,    43,   598,   375,     5,   375,
     277,   292,   297,   310,   315,   665,   666,    90,    93,   529,
     664,   667,   375,   656,   463,   388,   149,   144,   149,   557,
     558,   104,   114,   573,   635,   114,   573,   421,   114,   573,
     598,     5,   598,   598,   367,   586,   586,   587,   588,   589,
     103,   591,   586,   593,   633,   654,   598,   598,    85,     8,
      85,   632,   699,   729,   729,   598,   609,   598,   608,   619,
     378,   620,   657,   375,   543,   544,   367,   695,   689,   695,
     700,   700,   691,   692,   693,   695,   103,   689,   695,   651,
     695,    20,    20,   103,    39,   374,   365,   374,   430,   529,
     582,    37,    47,    52,    54,    56,   164,   277,   292,   310,
     315,   317,   365,   374,   430,   459,   529,    44,    94,   114,
     164,   365,   374,   430,   494,   500,   501,   529,   531,    40,
      89,    90,    91,    92,    94,    97,   114,   164,   277,   365,
     374,   430,   475,   529,   534,   535,    40,    90,    91,    92,
     114,   164,   365,   374,   430,   475,   529,   534,    41,    44,
     164,   292,   365,   374,   430,   428,   460,   462,   467,   474,
     478,   364,   364,   364,   381,   404,   412,   419,   462,   478,
     380,   380,     7,   420,   423,   396,   779,   423,   417,   371,
     371,   396,   396,   397,   397,   711,   346,   711,   103,   394,
     402,   112,   113,   717,   478,   380,   488,   489,   487,   295,
     365,   374,   430,   529,   671,   566,   568,   365,   374,   430,
     529,   686,   365,   374,   430,   529,   673,   561,   365,   374,
     430,   529,   675,   598,   598,     5,   506,   506,   663,   421,
     378,   378,   364,   536,   662,   405,   405,   380,   380,   380,
     598,   380,    20,   104,   295,   312,   565,   312,   567,    20,
     316,   562,   615,   631,   635,   617,   616,   598,    43,    82,
      83,   669,   696,   702,   191,   294,   381,   316,   311,   560,
     666,   506,   506,   667,   365,   374,   531,   396,     7,   421,
     573,   573,    70,   573,   598,     5,   598,   166,   598,   608,
     608,     5,   365,   534,   536,   659,     7,   365,   689,   689,
     103,    39,   428,   504,   523,   504,   514,   504,   517,   517,
     504,   520,   104,    90,   284,   286,   523,   523,   523,   523,
     374,   363,    79,    80,   502,   503,   631,   423,    99,   374,
     374,   374,   374,   374,   465,   636,   506,   506,   363,    95,
      96,   476,   103,   104,   129,   130,   254,   274,   275,   482,
     483,   493,    86,    87,    88,    90,   469,   470,   374,   374,
     374,   535,   465,   506,   506,   363,   483,   469,   374,   374,
     374,   104,   363,    99,   381,   365,   365,   365,   365,   365,
     488,   489,   487,   365,   365,   103,     7,   409,   103,   394,
     402,   365,    94,   134,   278,   365,   374,   430,   529,   683,
      90,    97,   134,   169,   278,   365,   374,   430,   529,   684,
     114,   278,   365,   374,   430,   529,   680,   103,   381,   565,
     567,   404,   412,   562,   419,   598,   657,   365,   380,   319,
     320,   321,   322,   323,   570,   103,   404,   103,   569,   404,
     570,   103,   412,   413,   413,   598,   375,   103,   313,   103,
     298,   506,   564,   103,   374,   558,   423,   423,   415,   423,
     598,    85,   620,     5,   365,   365,     5,   375,   544,   190,
     584,   103,   484,   461,   466,   471,   477,   523,   523,   523,
     484,   484,   484,   484,   364,   479,   631,   411,   104,     8,
     374,   374,   374,   468,   411,     8,   374,     7,   374,     5,
     374,   374,   468,     5,   374,   151,   495,   479,   374,   365,
     365,   365,   378,   103,   711,   363,   167,   172,   679,   509,
     380,   506,   103,   679,   103,   509,   380,   105,   509,   380,
     536,   294,   104,   561,   380,   103,   295,   382,   382,   566,
     568,   561,   399,   399,   598,   365,   620,   702,   187,   585,
     374,   364,   364,   364,   364,   364,   484,   484,   484,   364,
     364,   364,   364,   104,   105,   480,   481,   631,   374,    41,
     636,   482,   423,   470,    87,   464,   465,   636,    37,    87,
     292,   310,   315,   317,   472,   473,    22,   103,   104,   361,
     496,   497,   498,   631,   374,   374,   380,   380,   380,     7,
     394,   364,   425,   421,   374,   374,   374,   374,   374,   374,
     374,   134,   374,   365,   380,   103,   565,   567,   562,   365,
     375,   584,   492,   462,   467,   474,   478,   364,   364,   364,
     485,   490,   486,   491,     7,   365,   104,   465,   374,     8,
     428,   381,   404,   412,   419,   374,   483,   103,    22,    25,
     103,   104,   681,   682,   679,   381,   404,   404,   412,   585,
     365,   365,   365,   365,   365,   488,   489,   487,   365,   365,
     365,   365,   375,   481,    43,    44,   499,   374,   636,   423,
     374,   103,   103,     5,     7,   365,   374,   374,   374,   374,
     374,   374,   365,   365,   365,   374,   374,   374,   374,   505,
     631,   363,   495,   423,   103,   506,   507,   682,   374,   423,
     428,   380,   380,   380,   381,   404,   412,   419,   479,   411,
     374,   374,   374
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   372,   373,   373,   374,   374,   375,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   430,   430,   430,   430,   431,   431,   431,
     431,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   434,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   436,
     437,   437,   438,   438,   439,   439,   440,   440,   441,   441,
     441,   441,   441,   441,   441,   441,   441,   441,   441,   441,
     441,   441,   441,   441,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   443,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   445,   446,   446,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   448,   448,   448,   448,   448,   448,
     448,   449,   450,   450,   451,   451,   452,   453,   453,   454,
     454,   454,   454,   454,   454,   454,   454,   455,   455,   456,
     456,   456,   457,   458,   459,   459,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   461,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   463,   463,   463,   464,   464,   465,   465,   466,
     467,   467,   467,   467,   467,   467,   467,   467,   467,   467,
     467,   467,   467,   468,   468,   469,   469,   470,   470,   470,
     470,   471,   472,   472,   472,   472,   472,   473,   473,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   474,   474,   475,   475,   476,   476,   477,   478,   478,
     478,   478,   478,   478,   478,   479,   479,   480,   480,   480,
     481,   481,   481,   482,   482,   483,   483,   484,   485,   485,
     485,   485,   485,   486,   486,   486,   486,   486,   487,   487,
     487,   487,   487,   488,   488,   488,   488,   488,   489,   489,
     489,   489,   489,   490,   490,   490,   490,   490,   491,   491,
     491,   491,   491,   492,   492,   492,   492,   492,   493,   493,
     493,   493,   493,   494,   495,   496,   496,   497,   497,   497,
     497,   497,   498,   498,   499,   499,   499,   499,   500,   501,
     502,   502,   503,   503,   504,   504,   505,   505,   505,   506,
     507,   507,   508,   508,   509,   509,   509,   509,   509,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   527,   527,   527,
     527,   528,   529,   530,   530,   531,   531,   532,   533,   533,
     534,   534,   535,   535,   535,   535,   535,   536,   536,   536,
     536,   536,   536,   536,   536,   536,   536,   536,   536,   536,
     536,   536,   536,   536,   536,   536,   536,   536,   536,   537,
     538,   538,   539,   540,   540,   541,   542,   542,   543,   543,
     543,   544,   545,   545,   546,   546,   547,   547,   548,   548,
     549,   549,   550,   550,   550,   551,   551,   552,   553,   553,
     554,   554,   554,   554,   554,   554,   555,   556,   556,   556,
     556,   556,   557,   557,   558,   558,   559,   559,   559,   560,
     560,   560,   561,   561,   562,   562,   563,   563,   564,   564,
     564,   565,   565,   566,   567,   567,   568,   568,   569,   569,
     570,   570,   570,   570,   570,   571,   572,   573,   573,   574,
     574,   574,   574,   574,   574,   574,   574,   575,   576,   576,
     577,   577,   577,   577,   577,   577,   578,   578,   579,   579,
     580,   580,   581,   581,   581,   581,   582,   582,   583,   584,
     584,   585,   585,   586,   586,   586,   586,   586,   586,   586,
     586,   586,   586,   586,   586,   586,   587,   587,   587,   588,
     588,   589,   589,   590,   590,   591,   592,   592,   593,   593,
     594,   594,   595,   596,   597,   597,   598,   598,   598,   599,
     599,   599,   599,   599,   599,   599,   599,   599,   599,   599,
     599,   599,   599,   600,   600,   601,   602,   602,   602,   603,
     603,   604,   605,   605,   605,   605,   605,   606,   606,   607,
     607,   608,   608,   609,   609,   609,   610,   610,   610,   610,
     611,   611,   612,   613,   613,   614,   614,   615,   615,   616,
     616,   616,   617,   617,   617,   617,   618,   618,   619,   619,
     620,   620,   621,   622,   622,   622,   623,   623,   623,   624,
     624,   625,   625,   626,   627,   627,   628,   629,   629,   630,
     631,   632,   632,   633,   633,   634,   635,   636,   636,   636,
     636,   636,   636,   636,   636,   636,   636,   636,   636,   636,
     636,   636,   637,   638,   638,   638,   639,   639,   639,   639,
     639,   640,   640,   641,   641,   642,   642,   643,   643,   643,
     644,   644,   645,   645,   646,   646,   647,   648,   648,   649,
     650,   651,   651,   652,   653,   653,   653,   654,   655,   655,
     655,   656,   656,   656,   657,   657,   658,   659,   659,   660,
     660,   661,   661,   662,   662,   663,   663,   663,   664,   664,
     665,   665,   666,   666,   666,   666,   666,   666,   666,   666,
     666,   667,   667,   667,   668,   669,   669,   670,   670,   670,
     670,   671,   672,   673,   674,   675,   676,   677,   677,   677,
     678,   678,   678,   679,   679,   680,   680,   681,   681,   682,
     683,   683,   683,   684,   684,   684,   684,   684,   685,   686,
     686,   687,   688,   688,   688,   688,   688,   688,   688,   688,
     689,   689,   690,   690,   690,   691,   691,   691,   692,   692,
     693,   693,   694,   694,   695,   696,   696,   696,   696,   697,
     697,   698,   699,   699,   699,   699,   699,   699,   699,   699,
     699,   699,   699,   699,   699,   699,   700,   700,   700,   700,
     700,   700,   700,   700,   700,   700,   700,   700,   700,   700,
     700,   700,   700,   700,   701,   701,   701,   701,   701,   701,
     701,   702,   702,   702,   702,   702,   702,   703,   703,   704,
     704,   704,   705,   705,   706,   706,   706,   706,   706,   707,
     707,   707,   707,   707,   707,   707,   707,   707,   707,   707,
     707,   707,   707,   707,   707,   707,   707,   707,   707,   707,
     707,   707,   707,   708,   708,   708,   708,   708,   708,   709,
     709,   710,   710,   710,   711,   711,   712,   712,   713,   714,
     714,   715,   715,   716,   716,   717,   717,   718,   718,   719,
     719,   719,   720,   720,   721,   721,   722,   722,   722,   722,
     723,   723,   723,   724,   724,   725,   725,   725,   725,   725,
     725,   725,   725,   725,   725,   725,   725,   725,   725,   725,
     725,   725,   726,   726,   726,   726,   726,   726,   726,   727,
     727,   727,   727,   728,   728,   728,   728,   729,   729,   730,
     730,   731,   731,   731,   731,   732,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   734,   735,
     735,   735,   735,   736,   737,   737,   737,   738,   739,   739,
     739,   739,   739,   740,   741,   741,   741,   741,   741,   741,
     741,   741,   741,   742,   742,   742,   743,   743,   743,   743,
     743,   743,   743,   743,   743,   743,   743,   743,   744,   744,
     744,   744,   745,   745,   745,   745,   745,   746,   747,   747,
     747,   747,   747,   747,   747,   748,   749,   749,   749,   749,
     750,   751,   751,   751,   751,   751,   751,   751,   751,   751,
     752,   753,   753,   753,   753,   753,   753,   753,   753,   753,
     753,   754,   755,   755,   755,   755,   755,   756,   757,   757,
     758,   759,   759,   759,   760,   761,   761,   761,   761,   762,
     763,   763,   763,   763,   764,   764,   764,   764,   765,   765,
     765,   765,   765,   765,   765,   765,   765,   765,   765,   765,
     765,   765,   766,   766,   766,   767,   767,   768,   768,   769,
     769,   770,   770,   771,   771,   772,   772,   773,   773,   773,
     774,   775,   776,   776,   776,   776,   776,   776,   776,   776,
     776,   776,   777,   777,   777,   777,   777,   777,   778,   778,
     778,   778,   778,   779,   779,   779,   779,   779,   779,   779,
     779,   779,   779,   779,   779,   780,   780,   781,   782,   782,
     783,   784,   785,   785,   786,   786,   786,   787,   787,   787,
     787,   787,   787,   787,   787,   787,   787,   787,   787,   787,
     787,   787,   787,   787,   787,   788,   788,   788,   789,   789,
     789,   789,   790,   790,   790,   790,   790,   791,   791,   791,
     791,   792,   792,   792,   792,   792,   792,   792,   792,   792,
     792,   792,   792,   793,   793,   794,   794,   794,   794,   795,
     796,   796,   797,   797,   797,   797,   797,   797,   797,   797,
     798,   799,   799,   800,   801,   801,   801,   801,   802,   803,
     804,   805,   806,   807,   807,   807,   807,   808,   809,   809,
     809,   809,   809,   809,   810,   811,   811,   812,   813,   813,
     813,   813,   813,   814,   815,   815,   815,   815,   815
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     5,     5,     3,     2,     1,     1,     2,
       2,     1,     2,     2,     2,     2,     2,     2,     3,     3,
       2,     2,     3,     3,     3,     2,     3,     2,     6,     2,
       6,     3,     2,     6,     6,     3,     6,     3,     5,     7,
       5,     7,     8,     8,     8,     5,     7,     5,     7,     5,
       7,     3,     2,     6,     2,     6,     6,     6,     3,     6,
       3,     5,     5,     8,     8,     8,     5,     5,     5,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       6,     2,     2,     2,     3,     2,     2,     6,     3,     3,
       5,     3,     3,     3,     2,     2,     2,     2,     2,     3,
       2,     2,     6,     3,     3,     5,     3,     3,     3,     3,
       2,     2,     2,     2,     2,     3,     2,     2,     3,     3,
       2,     3,     3,     2,     3,     3,     2,     3,     3,     2,
       3,     3,     2,     3,     3,     2,     2,     2,     2,     2,
       2,     4,     5,     2,     2,     1,     2,     2,     2,     3,
       3,     2,     3,     2,     3,     2,     2,     3,     2,     3,
       2,     3,     2,     2,     2,     2,     2,     2,     3,     2,
       2,     3,     2,     1,     2,     1,     3,     0,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       1,     2,     1,     0,     2,     1,     0,     2,     2,     3,
       8,     8,     8,     8,     9,     9,    10,    10,    10,     9,
       9,     9,     0,     0,     2,     2,     3,     3,     3,     3,
       5,     3,     0,     2,     3,     1,     3,     1,     3,     0,
       0,     2,     2,     5,     4,     4,     4,     4,     3,     4,
       2,     3,     3,     1,     1,     3,     1,     1,     1,     1,
       1,     0,     2,     2,     2,     2,     2,     1,     0,     0,
       2,     2,     4,     4,     8,     6,     7,     7,     4,     3,
       4,     3,     3,     3,     2,     1,     1,     0,     0,     2,
       2,     5,     5,     3,     4,     3,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     3,     0,     0,     2,
       2,     2,     2,     0,     2,     2,     2,     2,     0,     2,
       2,     2,     2,     0,     2,     2,     2,     2,     0,     2,
       2,     2,     2,     0,     2,     2,     2,     2,     0,     2,
       2,     2,     2,     0,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     7,     2,     1,     1,     1,     1,     1,
       3,     3,     1,     2,     2,     2,     3,     0,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     2,     2,     1,     2,     1,     1,
       2,     3,     2,     3,     1,     2,     3,     1,     2,     3,
       1,     2,     3,     1,     2,     2,     2,     1,     2,     2,
       2,     2,     2,     0,     1,     1,     2,     1,     1,     2,
       1,     2,     2,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     1,     1,     2,
       2,     2,     2,     1,     1,     2,     1,     1,     2,     3,
       1,     1,     5,     1,     1,     3,     3,     1,     1,     3,
       3,     5,     4,     5,     1,     2,     1,     3,     1,     2,
       2,     2,     1,     3,     3,     1,     2,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     3,     1,
       2,     1,     3,     1,     1,     1,     6,     6,     4,     1,
       1,     0,     1,     1,     0,     3,     6,     4,     1,     1,
       0,     0,     3,     3,     0,     2,     2,     3,     2,     2,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     0,
       6,     3,     6,     3,     5,     3,     5,     2,     1,     1,
       3,     4,     4,     5,     6,     5,     1,     2,     1,     3,
       1,     2,     2,     2,     1,     1,     6,     8,     0,     0,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     3,     1,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       2,     3,     3,     4,     5,     2,     3,     2,     6,     4,
       3,     4,     3,     2,     1,     1,     3,     4,     1,     2,
       1,     1,     2,     3,     1,     3,     4,     3,     5,     3,
       6,     1,     3,     1,     1,     1,     2,     4,     6,     6,
       1,     2,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     2,     1,     4,     5,     6,     1,     1,     1,     7,
       8,     6,     1,     1,     1,     2,     2,     6,     8,     1,
       2,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     1,     1,     2,     1,     1,     1,     1,
       1,     3,     1,     4,     4,     0,     2,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     1,     3,     3,
       3,     1,     1,     3,     1,     1,     1,     3,     1,     3,
       3,     3,     3,     5,     1,     2,     1,     1,     2,     1,
       1,     2,     1,     1,     2,     2,     2,     1,     1,     2,
       1,     2,     2,     6,     6,     6,     4,     5,     6,     4,
       4,     2,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     4,     0,     4,     0,     1,     0,     1,     1,     1,
       1,     1,     1,     2,     2,     6,     3,     1,     3,     3,
       3,     7,     3,     3,     3,     3,     3,     3,     0,     4,
       4,     0,     2,     2,     4,     4,     5,     5,     3,     3,
       3,     3,     1,     1,     1,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     1,     3,     3,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     1,
       2,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     1,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     5,     3,     5,     1,     5,     5,     3,
       5,     1,     1,     1,     0,     2,     1,     1,     6,     2,
       0,     1,     1,     1,     1,     1,     1,     5,     6,     8,
       6,     5,     2,     2,     3,     4,     1,     1,     1,     2,
       3,     4,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     5,     5,     5,     6,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     7,     1,
       1,     2,     1,     3,     1,     1,     2,     3,     1,     1,
       1,     1,     2,     3,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     5,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     2,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     2,     3,     3,     9,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       1,     2,     2,     1,     1,     3,     3,     1,     1,     1,
       3,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     4,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     5,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     3,     1,     1,     2,     1,     3,     4,
       3,     1,     3,     1,     1,     1,     4,     3,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     3,     1,     1,
       2,     1,     1,     2,     2,     2,     2,     2,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, nft, scanner, state, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, nft, scanner, state); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (nft);
  YY_USE (scanner);
  YY_USE (state);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, nft, scanner, state);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), nft, scanner, state);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, nft, scanner, state); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (nft);
  YY_USE (scanner);
  YY_USE (state);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_STRING: /* "string"  */
#line 360 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6179 "parser_bison.c"
        break;

    case YYSYMBOL_QUOTED_STRING: /* "quoted string"  */
#line 360 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6185 "parser_bison.c"
        break;

    case YYSYMBOL_ASTERISK_STRING: /* "string with a trailing asterisk"  */
#line 360 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6191 "parser_bison.c"
        break;

    case YYSYMBOL_line: /* line  */
#line 684 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6197 "parser_bison.c"
        break;

    case YYSYMBOL_base_cmd: /* base_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6203 "parser_bison.c"
        break;

    case YYSYMBOL_add_cmd: /* add_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6209 "parser_bison.c"
        break;

    case YYSYMBOL_replace_cmd: /* replace_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6215 "parser_bison.c"
        break;

    case YYSYMBOL_create_cmd: /* create_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6221 "parser_bison.c"
        break;

    case YYSYMBOL_insert_cmd: /* insert_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6227 "parser_bison.c"
        break;

    case YYSYMBOL_table_or_id_spec: /* table_or_id_spec  */
#line 690 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6233 "parser_bison.c"
        break;

    case YYSYMBOL_chain_or_id_spec: /* chain_or_id_spec  */
#line 692 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6239 "parser_bison.c"
        break;

    case YYSYMBOL_set_or_id_spec: /* set_or_id_spec  */
#line 697 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6245 "parser_bison.c"
        break;

    case YYSYMBOL_obj_or_id_spec: /* obj_or_id_spec  */
#line 699 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6251 "parser_bison.c"
        break;

    case YYSYMBOL_delete_cmd: /* delete_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6257 "parser_bison.c"
        break;

    case YYSYMBOL_destroy_cmd: /* destroy_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6263 "parser_bison.c"
        break;

    case YYSYMBOL_get_cmd: /* get_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6269 "parser_bison.c"
        break;

    case YYSYMBOL_list_cmd: /* list_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6275 "parser_bison.c"
        break;

    case YYSYMBOL_basehook_device_name: /* basehook_device_name  */
#line 711 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6281 "parser_bison.c"
        break;

    case YYSYMBOL_basehook_spec: /* basehook_spec  */
#line 705 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6287 "parser_bison.c"
        break;

    case YYSYMBOL_reset_cmd: /* reset_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6293 "parser_bison.c"
        break;

    case YYSYMBOL_flush_cmd: /* flush_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6299 "parser_bison.c"
        break;

    case YYSYMBOL_rename_cmd: /* rename_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6305 "parser_bison.c"
        break;

    case YYSYMBOL_import_cmd: /* import_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6311 "parser_bison.c"
        break;

    case YYSYMBOL_export_cmd: /* export_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6317 "parser_bison.c"
        break;

    case YYSYMBOL_monitor_cmd: /* monitor_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6323 "parser_bison.c"
        break;

    case YYSYMBOL_monitor_event: /* monitor_event  */
#line 930 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6329 "parser_bison.c"
        break;

    case YYSYMBOL_describe_cmd: /* describe_cmd  */
#line 687 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6335 "parser_bison.c"
        break;

    case YYSYMBOL_table_block_alloc: /* table_block_alloc  */
#line 717 "parser_bison.y"
            { close_scope(state); table_free(((*yyvaluep).table)); }
#line 6341 "parser_bison.c"
        break;

    case YYSYMBOL_chain_block_alloc: /* chain_block_alloc  */
#line 719 "parser_bison.y"
            { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 6347 "parser_bison.c"
        break;

    case YYSYMBOL_typeof_data_expr: /* typeof_data_expr  */
#line 791 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6353 "parser_bison.c"
        break;

    case YYSYMBOL_typeof_expr: /* typeof_expr  */
#line 791 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6359 "parser_bison.c"
        break;

    case YYSYMBOL_set_block_alloc: /* set_block_alloc  */
#line 728 "parser_bison.y"
            { set_free(((*yyvaluep).set)); }
#line 6365 "parser_bison.c"
        break;

    case YYSYMBOL_set_block_expr: /* set_block_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6371 "parser_bison.c"
        break;

    case YYSYMBOL_map_block_alloc: /* map_block_alloc  */
#line 731 "parser_bison.y"
            { set_free(((*yyvaluep).set)); }
#line 6377 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_block_alloc: /* flowtable_block_alloc  */
#line 735 "parser_bison.y"
            { flowtable_free(((*yyvaluep).flowtable)); }
#line 6383 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_expr: /* flowtable_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6389 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_list_expr: /* flowtable_list_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6395 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_expr_member: /* flowtable_expr_member  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6401 "parser_bison.c"
        break;

    case YYSYMBOL_data_type_atom_expr: /* data_type_atom_expr  */
#line 681 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6407 "parser_bison.c"
        break;

    case YYSYMBOL_data_type_expr: /* data_type_expr  */
#line 681 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6413 "parser_bison.c"
        break;

    case YYSYMBOL_obj_block_alloc: /* obj_block_alloc  */
#line 738 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6419 "parser_bison.c"
        break;

    case YYSYMBOL_type_identifier: /* type_identifier  */
#line 676 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6425 "parser_bison.c"
        break;

    case YYSYMBOL_extended_prio_name: /* extended_prio_name  */
#line 711 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6431 "parser_bison.c"
        break;

    case YYSYMBOL_dev_spec: /* dev_spec  */
#line 714 "parser_bison.y"
            { xfree(((*yyvaluep).expr)); }
#line 6437 "parser_bison.c"
        break;

    case YYSYMBOL_policy_expr: /* policy_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6443 "parser_bison.c"
        break;

    case YYSYMBOL_identifier: /* identifier  */
#line 676 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6449 "parser_bison.c"
        break;

    case YYSYMBOL_string: /* string  */
#line 676 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6455 "parser_bison.c"
        break;

    case YYSYMBOL_table_spec: /* table_spec  */
#line 690 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6461 "parser_bison.c"
        break;

    case YYSYMBOL_tableid_spec: /* tableid_spec  */
#line 690 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6467 "parser_bison.c"
        break;

    case YYSYMBOL_chain_spec: /* chain_spec  */
#line 692 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6473 "parser_bison.c"
        break;

    case YYSYMBOL_chainid_spec: /* chainid_spec  */
#line 692 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6479 "parser_bison.c"
        break;

    case YYSYMBOL_chain_identifier: /* chain_identifier  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6485 "parser_bison.c"
        break;

    case YYSYMBOL_set_spec: /* set_spec  */
#line 697 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6491 "parser_bison.c"
        break;

    case YYSYMBOL_setid_spec: /* setid_spec  */
#line 697 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6497 "parser_bison.c"
        break;

    case YYSYMBOL_set_identifier: /* set_identifier  */
#line 702 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6503 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_spec: /* flowtable_spec  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6509 "parser_bison.c"
        break;

    case YYSYMBOL_flowtableid_spec: /* flowtableid_spec  */
#line 702 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6515 "parser_bison.c"
        break;

    case YYSYMBOL_obj_spec: /* obj_spec  */
#line 699 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6521 "parser_bison.c"
        break;

    case YYSYMBOL_objid_spec: /* objid_spec  */
#line 699 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6527 "parser_bison.c"
        break;

    case YYSYMBOL_obj_identifier: /* obj_identifier  */
#line 702 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6533 "parser_bison.c"
        break;

    case YYSYMBOL_handle_spec: /* handle_spec  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6539 "parser_bison.c"
        break;

    case YYSYMBOL_position_spec: /* position_spec  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6545 "parser_bison.c"
        break;

    case YYSYMBOL_index_spec: /* index_spec  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6551 "parser_bison.c"
        break;

    case YYSYMBOL_rule_position: /* rule_position  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6557 "parser_bison.c"
        break;

    case YYSYMBOL_ruleid_spec: /* ruleid_spec  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6563 "parser_bison.c"
        break;

    case YYSYMBOL_comment_spec: /* comment_spec  */
#line 676 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6569 "parser_bison.c"
        break;

    case YYSYMBOL_ruleset_spec: /* ruleset_spec  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6575 "parser_bison.c"
        break;

    case YYSYMBOL_rule: /* rule  */
#line 721 "parser_bison.y"
            { rule_free(((*yyvaluep).rule)); }
#line 6581 "parser_bison.c"
        break;

    case YYSYMBOL_stmt_list: /* stmt_list  */
#line 741 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6587 "parser_bison.c"
        break;

    case YYSYMBOL_stateful_stmt_list: /* stateful_stmt_list  */
#line 741 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6593 "parser_bison.c"
        break;

    case YYSYMBOL_stateful_stmt: /* stateful_stmt  */
#line 745 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6599 "parser_bison.c"
        break;

    case YYSYMBOL_stmt: /* stmt  */
#line 743 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6605 "parser_bison.c"
        break;

    case YYSYMBOL_xt_stmt: /* xt_stmt  */
#line 954 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6611 "parser_bison.c"
        break;

    case YYSYMBOL_chain_stmt: /* chain_stmt  */
#line 768 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6617 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_stmt: /* verdict_stmt  */
#line 743 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6623 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_stmt: /* verdict_map_stmt  */
#line 826 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6629 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_expr: /* verdict_map_expr  */
#line 829 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6635 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_list_expr: /* verdict_map_list_expr  */
#line 829 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6641 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_list_member_expr: /* verdict_map_list_member_expr  */
#line 829 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6647 "parser_bison.c"
        break;

    case YYSYMBOL_connlimit_stmt: /* connlimit_stmt  */
#line 756 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6653 "parser_bison.c"
        break;

    case YYSYMBOL_counter_stmt: /* counter_stmt  */
#line 745 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6659 "parser_bison.c"
        break;

    case YYSYMBOL_counter_stmt_alloc: /* counter_stmt_alloc  */
#line 745 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6665 "parser_bison.c"
        break;

    case YYSYMBOL_last_stmt: /* last_stmt  */
#line 745 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6671 "parser_bison.c"
        break;

    case YYSYMBOL_log_stmt: /* log_stmt  */
#line 753 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6677 "parser_bison.c"
        break;

    case YYSYMBOL_log_stmt_alloc: /* log_stmt_alloc  */
#line 753 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6683 "parser_bison.c"
        break;

    case YYSYMBOL_limit_stmt: /* limit_stmt  */
#line 756 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6689 "parser_bison.c"
        break;

    case YYSYMBOL_quota_unit: /* quota_unit  */
#line 711 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6695 "parser_bison.c"
        break;

    case YYSYMBOL_quota_stmt: /* quota_stmt  */
#line 756 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6701 "parser_bison.c"
        break;

    case YYSYMBOL_reject_stmt: /* reject_stmt  */
#line 759 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6707 "parser_bison.c"
        break;

    case YYSYMBOL_reject_stmt_alloc: /* reject_stmt_alloc  */
#line 759 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6713 "parser_bison.c"
        break;

    case YYSYMBOL_reject_with_expr: /* reject_with_expr  */
#line 774 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6719 "parser_bison.c"
        break;

    case YYSYMBOL_nat_stmt: /* nat_stmt  */
#line 761 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6725 "parser_bison.c"
        break;

    case YYSYMBOL_nat_stmt_alloc: /* nat_stmt_alloc  */
#line 761 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6731 "parser_bison.c"
        break;

    case YYSYMBOL_tproxy_stmt: /* tproxy_stmt  */
#line 764 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6737 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_stmt: /* synproxy_stmt  */
#line 766 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6743 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_stmt_alloc: /* synproxy_stmt_alloc  */
#line 766 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6749 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_obj: /* synproxy_obj  */
#line 852 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6755 "parser_bison.c"
        break;

    case YYSYMBOL_primary_stmt_expr: /* primary_stmt_expr  */
#line 813 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6761 "parser_bison.c"
        break;

    case YYSYMBOL_shift_stmt_expr: /* shift_stmt_expr  */
#line 815 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6767 "parser_bison.c"
        break;

    case YYSYMBOL_and_stmt_expr: /* and_stmt_expr  */
#line 817 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6773 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_stmt_expr: /* exclusive_or_stmt_expr  */
#line 817 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6779 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_stmt_expr: /* inclusive_or_stmt_expr  */
#line 817 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6785 "parser_bison.c"
        break;

    case YYSYMBOL_basic_stmt_expr: /* basic_stmt_expr  */
#line 813 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6791 "parser_bison.c"
        break;

    case YYSYMBOL_concat_stmt_expr: /* concat_stmt_expr  */
#line 805 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6797 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt_expr_set: /* map_stmt_expr_set  */
#line 805 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6803 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt_expr: /* map_stmt_expr  */
#line 805 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6809 "parser_bison.c"
        break;

    case YYSYMBOL_prefix_stmt_expr: /* prefix_stmt_expr  */
#line 810 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6815 "parser_bison.c"
        break;

    case YYSYMBOL_range_stmt_expr: /* range_stmt_expr  */
#line 810 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6821 "parser_bison.c"
        break;

    case YYSYMBOL_multiton_stmt_expr: /* multiton_stmt_expr  */
#line 808 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6827 "parser_bison.c"
        break;

    case YYSYMBOL_stmt_expr: /* stmt_expr  */
#line 805 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6833 "parser_bison.c"
        break;

    case YYSYMBOL_masq_stmt: /* masq_stmt  */
#line 761 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6839 "parser_bison.c"
        break;

    case YYSYMBOL_masq_stmt_alloc: /* masq_stmt_alloc  */
#line 761 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6845 "parser_bison.c"
        break;

    case YYSYMBOL_redir_stmt: /* redir_stmt  */
#line 761 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6851 "parser_bison.c"
        break;

    case YYSYMBOL_redir_stmt_alloc: /* redir_stmt_alloc  */
#line 761 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6857 "parser_bison.c"
        break;

    case YYSYMBOL_dup_stmt: /* dup_stmt  */
#line 777 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6863 "parser_bison.c"
        break;

    case YYSYMBOL_fwd_stmt: /* fwd_stmt  */
#line 779 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6869 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt: /* queue_stmt  */
#line 772 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6875 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_compat: /* queue_stmt_compat  */
#line 772 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6881 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_alloc: /* queue_stmt_alloc  */
#line 772 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6887 "parser_bison.c"
        break;

    case YYSYMBOL_queue_expr: /* queue_expr  */
#line 774 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6893 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_expr_simple: /* queue_stmt_expr_simple  */
#line 774 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6899 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_expr: /* queue_stmt_expr  */
#line 774 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6905 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_stmt: /* set_elem_expr_stmt  */
#line 836 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6911 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_stmt_alloc: /* set_elem_expr_stmt_alloc  */
#line 836 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6917 "parser_bison.c"
        break;

    case YYSYMBOL_set_stmt: /* set_stmt  */
#line 781 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6923 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt: /* map_stmt  */
#line 784 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6929 "parser_bison.c"
        break;

    case YYSYMBOL_meter_stmt: /* meter_stmt  */
#line 786 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6935 "parser_bison.c"
        break;

    case YYSYMBOL_flow_stmt_legacy_alloc: /* flow_stmt_legacy_alloc  */
#line 786 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6941 "parser_bison.c"
        break;

    case YYSYMBOL_meter_stmt_alloc: /* meter_stmt_alloc  */
#line 786 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6947 "parser_bison.c"
        break;

    case YYSYMBOL_match_stmt: /* match_stmt  */
#line 743 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6953 "parser_bison.c"
        break;

    case YYSYMBOL_variable_expr: /* variable_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6959 "parser_bison.c"
        break;

    case YYSYMBOL_symbol_expr: /* symbol_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6965 "parser_bison.c"
        break;

    case YYSYMBOL_set_ref_expr: /* set_ref_expr  */
#line 797 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6971 "parser_bison.c"
        break;

    case YYSYMBOL_set_ref_symbol_expr: /* set_ref_symbol_expr  */
#line 797 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6977 "parser_bison.c"
        break;

    case YYSYMBOL_integer_expr: /* integer_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6983 "parser_bison.c"
        break;

    case YYSYMBOL_primary_expr: /* primary_expr  */
#line 791 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6989 "parser_bison.c"
        break;

    case YYSYMBOL_fib_expr: /* fib_expr  */
#line 921 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6995 "parser_bison.c"
        break;

    case YYSYMBOL_osf_expr: /* osf_expr  */
#line 926 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7001 "parser_bison.c"
        break;

    case YYSYMBOL_shift_expr: /* shift_expr  */
#line 791 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7007 "parser_bison.c"
        break;

    case YYSYMBOL_and_expr: /* and_expr  */
#line 791 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7013 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_expr: /* exclusive_or_expr  */
#line 793 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7019 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_expr: /* inclusive_or_expr  */
#line 793 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7025 "parser_bison.c"
        break;

    case YYSYMBOL_basic_expr: /* basic_expr  */
#line 795 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7031 "parser_bison.c"
        break;

    case YYSYMBOL_concat_expr: /* concat_expr  */
#line 820 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7037 "parser_bison.c"
        break;

    case YYSYMBOL_prefix_rhs_expr: /* prefix_rhs_expr  */
#line 802 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7043 "parser_bison.c"
        break;

    case YYSYMBOL_range_rhs_expr: /* range_rhs_expr  */
#line 802 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7049 "parser_bison.c"
        break;

    case YYSYMBOL_multiton_rhs_expr: /* multiton_rhs_expr  */
#line 800 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7055 "parser_bison.c"
        break;

    case YYSYMBOL_map_expr: /* map_expr  */
#line 823 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7061 "parser_bison.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 842 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7067 "parser_bison.c"
        break;

    case YYSYMBOL_set_expr: /* set_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7073 "parser_bison.c"
        break;

    case YYSYMBOL_set_list_expr: /* set_list_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7079 "parser_bison.c"
        break;

    case YYSYMBOL_set_list_member_expr: /* set_list_member_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7085 "parser_bison.c"
        break;

    case YYSYMBOL_meter_key_expr: /* meter_key_expr  */
#line 839 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7091 "parser_bison.c"
        break;

    case YYSYMBOL_meter_key_expr_alloc: /* meter_key_expr_alloc  */
#line 839 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7097 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr: /* set_elem_expr  */
#line 834 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7103 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_key_expr: /* set_elem_key_expr  */
#line 974 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7109 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_alloc: /* set_elem_expr_alloc  */
#line 834 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7115 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_stmt_list: /* set_elem_stmt_list  */
#line 741 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 7121 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_stmt: /* set_elem_stmt  */
#line 743 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7127 "parser_bison.c"
        break;

    case YYSYMBOL_set_lhs_expr: /* set_lhs_expr  */
#line 834 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7133 "parser_bison.c"
        break;

    case YYSYMBOL_set_rhs_expr: /* set_rhs_expr  */
#line 834 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7139 "parser_bison.c"
        break;

    case YYSYMBOL_initializer_expr: /* initializer_expr  */
#line 842 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7145 "parser_bison.c"
        break;

    case YYSYMBOL_counter_obj: /* counter_obj  */
#line 852 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7151 "parser_bison.c"
        break;

    case YYSYMBOL_quota_obj: /* quota_obj  */
#line 852 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7157 "parser_bison.c"
        break;

    case YYSYMBOL_secmark_obj: /* secmark_obj  */
#line 852 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7163 "parser_bison.c"
        break;

    case YYSYMBOL_timeout_states: /* timeout_states  */
#line 967 "parser_bison.y"
            { xfree(((*yyvaluep).list)); }
#line 7169 "parser_bison.c"
        break;

    case YYSYMBOL_timeout_state: /* timeout_state  */
#line 967 "parser_bison.y"
            { xfree(((*yyvaluep).list)); }
#line 7175 "parser_bison.c"
        break;

    case YYSYMBOL_ct_obj_alloc: /* ct_obj_alloc  */
#line 852 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7181 "parser_bison.c"
        break;

    case YYSYMBOL_limit_obj: /* limit_obj  */
#line 852 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7187 "parser_bison.c"
        break;

    case YYSYMBOL_relational_expr: /* relational_expr  */
#line 855 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7193 "parser_bison.c"
        break;

    case YYSYMBOL_list_rhs_expr: /* list_rhs_expr  */
#line 847 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7199 "parser_bison.c"
        break;

    case YYSYMBOL_rhs_expr: /* rhs_expr  */
#line 845 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7205 "parser_bison.c"
        break;

    case YYSYMBOL_shift_rhs_expr: /* shift_rhs_expr  */
#line 847 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7211 "parser_bison.c"
        break;

    case YYSYMBOL_and_rhs_expr: /* and_rhs_expr  */
#line 849 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7217 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_rhs_expr: /* exclusive_or_rhs_expr  */
#line 849 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7223 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_rhs_expr: /* inclusive_or_rhs_expr  */
#line 849 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7229 "parser_bison.c"
        break;

    case YYSYMBOL_basic_rhs_expr: /* basic_rhs_expr  */
#line 845 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7235 "parser_bison.c"
        break;

    case YYSYMBOL_concat_rhs_expr: /* concat_rhs_expr  */
#line 845 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7241 "parser_bison.c"
        break;

    case YYSYMBOL_boolean_expr: /* boolean_expr  */
#line 957 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7247 "parser_bison.c"
        break;

    case YYSYMBOL_keyword_expr: /* keyword_expr  */
#line 842 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7253 "parser_bison.c"
        break;

    case YYSYMBOL_primary_rhs_expr: /* primary_rhs_expr  */
#line 847 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7259 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_expr: /* verdict_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7265 "parser_bison.c"
        break;

    case YYSYMBOL_chain_expr: /* chain_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7271 "parser_bison.c"
        break;

    case YYSYMBOL_meta_expr: /* meta_expr  */
#line 903 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7277 "parser_bison.c"
        break;

    case YYSYMBOL_meta_stmt: /* meta_stmt  */
#line 751 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7283 "parser_bison.c"
        break;

    case YYSYMBOL_socket_expr: /* socket_expr  */
#line 907 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7289 "parser_bison.c"
        break;

    case YYSYMBOL_numgen_expr: /* numgen_expr  */
#line 868 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7295 "parser_bison.c"
        break;

    case YYSYMBOL_xfrm_expr: /* xfrm_expr  */
#line 971 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7301 "parser_bison.c"
        break;

    case YYSYMBOL_hash_expr: /* hash_expr  */
#line 868 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7307 "parser_bison.c"
        break;

    case YYSYMBOL_rt_expr: /* rt_expr  */
#line 913 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7313 "parser_bison.c"
        break;

    case YYSYMBOL_ct_expr: /* ct_expr  */
#line 917 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7319 "parser_bison.c"
        break;

    case YYSYMBOL_symbol_stmt_expr: /* symbol_stmt_expr  */
#line 847 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7325 "parser_bison.c"
        break;

    case YYSYMBOL_list_stmt_expr: /* list_stmt_expr  */
#line 815 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7331 "parser_bison.c"
        break;

    case YYSYMBOL_ct_stmt: /* ct_stmt  */
#line 749 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7337 "parser_bison.c"
        break;

    case YYSYMBOL_payload_stmt: /* payload_stmt  */
#line 747 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7343 "parser_bison.c"
        break;

    case YYSYMBOL_payload_expr: /* payload_expr  */
#line 859 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7349 "parser_bison.c"
        break;

    case YYSYMBOL_payload_raw_expr: /* payload_raw_expr  */
#line 859 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7355 "parser_bison.c"
        break;

    case YYSYMBOL_eth_hdr_expr: /* eth_hdr_expr  */
#line 862 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7361 "parser_bison.c"
        break;

    case YYSYMBOL_vlan_hdr_expr: /* vlan_hdr_expr  */
#line 862 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7367 "parser_bison.c"
        break;

    case YYSYMBOL_arp_hdr_expr: /* arp_hdr_expr  */
#line 865 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7373 "parser_bison.c"
        break;

    case YYSYMBOL_ip_hdr_expr: /* ip_hdr_expr  */
#line 868 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7379 "parser_bison.c"
        break;

    case YYSYMBOL_icmp_hdr_expr: /* icmp_hdr_expr  */
#line 868 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7385 "parser_bison.c"
        break;

    case YYSYMBOL_igmp_hdr_expr: /* igmp_hdr_expr  */
#line 868 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7391 "parser_bison.c"
        break;

    case YYSYMBOL_ip6_hdr_expr: /* ip6_hdr_expr  */
#line 872 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7397 "parser_bison.c"
        break;

    case YYSYMBOL_icmp6_hdr_expr: /* icmp6_hdr_expr  */
#line 872 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7403 "parser_bison.c"
        break;

    case YYSYMBOL_auth_hdr_expr: /* auth_hdr_expr  */
#line 875 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7409 "parser_bison.c"
        break;

    case YYSYMBOL_esp_hdr_expr: /* esp_hdr_expr  */
#line 875 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7415 "parser_bison.c"
        break;

    case YYSYMBOL_comp_hdr_expr: /* comp_hdr_expr  */
#line 875 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7421 "parser_bison.c"
        break;

    case YYSYMBOL_udp_hdr_expr: /* udp_hdr_expr  */
#line 878 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7427 "parser_bison.c"
        break;

    case YYSYMBOL_udplite_hdr_expr: /* udplite_hdr_expr  */
#line 878 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7433 "parser_bison.c"
        break;

    case YYSYMBOL_tcp_hdr_expr: /* tcp_hdr_expr  */
#line 936 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7439 "parser_bison.c"
        break;

    case YYSYMBOL_inner_inet_expr: /* inner_inet_expr  */
#line 944 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7445 "parser_bison.c"
        break;

    case YYSYMBOL_inner_eth_expr: /* inner_eth_expr  */
#line 944 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7451 "parser_bison.c"
        break;

    case YYSYMBOL_inner_expr: /* inner_expr  */
#line 944 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7457 "parser_bison.c"
        break;

    case YYSYMBOL_vxlan_hdr_expr: /* vxlan_hdr_expr  */
#line 947 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7463 "parser_bison.c"
        break;

    case YYSYMBOL_geneve_hdr_expr: /* geneve_hdr_expr  */
#line 947 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7469 "parser_bison.c"
        break;

    case YYSYMBOL_gre_hdr_expr: /* gre_hdr_expr  */
#line 947 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7475 "parser_bison.c"
        break;

    case YYSYMBOL_gretap_hdr_expr: /* gretap_hdr_expr  */
#line 947 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7481 "parser_bison.c"
        break;

    case YYSYMBOL_optstrip_stmt: /* optstrip_stmt  */
#line 951 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7487 "parser_bison.c"
        break;

    case YYSYMBOL_dccp_hdr_expr: /* dccp_hdr_expr  */
#line 881 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7493 "parser_bison.c"
        break;

    case YYSYMBOL_sctp_chunk_alloc: /* sctp_chunk_alloc  */
#line 881 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7499 "parser_bison.c"
        break;

    case YYSYMBOL_sctp_hdr_expr: /* sctp_hdr_expr  */
#line 881 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7505 "parser_bison.c"
        break;

    case YYSYMBOL_th_hdr_expr: /* th_hdr_expr  */
#line 887 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7511 "parser_bison.c"
        break;

    case YYSYMBOL_exthdr_expr: /* exthdr_expr  */
#line 891 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7517 "parser_bison.c"
        break;

    case YYSYMBOL_hbh_hdr_expr: /* hbh_hdr_expr  */
#line 893 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7523 "parser_bison.c"
        break;

    case YYSYMBOL_rt_hdr_expr: /* rt_hdr_expr  */
#line 896 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7529 "parser_bison.c"
        break;

    case YYSYMBOL_rt0_hdr_expr: /* rt0_hdr_expr  */
#line 896 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7535 "parser_bison.c"
        break;

    case YYSYMBOL_rt2_hdr_expr: /* rt2_hdr_expr  */
#line 896 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7541 "parser_bison.c"
        break;

    case YYSYMBOL_rt4_hdr_expr: /* rt4_hdr_expr  */
#line 896 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7547 "parser_bison.c"
        break;

    case YYSYMBOL_frag_hdr_expr: /* frag_hdr_expr  */
#line 893 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7553 "parser_bison.c"
        break;

    case YYSYMBOL_dst_hdr_expr: /* dst_hdr_expr  */
#line 893 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7559 "parser_bison.c"
        break;

    case YYSYMBOL_mh_hdr_expr: /* mh_hdr_expr  */
#line 899 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7565 "parser_bison.c"
        break;

    case YYSYMBOL_exthdr_exists_expr: /* exthdr_exists_expr  */
#line 961 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7571 "parser_bison.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
#line 197 "parser_bison.y"
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 7676 "parser_bison.c"

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= TOKEN_EOF)
    {
      yychar = TOKEN_EOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* input: input line  */
#line 980 "parser_bison.y"
                        {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 7893 "parser_bison.c"
    break;

  case 8: /* close_scope_ah: %empty  */
#line 996 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_AH); }
#line 7899 "parser_bison.c"
    break;

  case 9: /* close_scope_arp: %empty  */
#line 997 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ARP); }
#line 7905 "parser_bison.c"
    break;

  case 10: /* close_scope_at: %empty  */
#line 998 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_AT); }
#line 7911 "parser_bison.c"
    break;

  case 11: /* close_scope_comp: %empty  */
#line 999 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_COMP); }
#line 7917 "parser_bison.c"
    break;

  case 12: /* close_scope_ct: %empty  */
#line 1000 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CT); }
#line 7923 "parser_bison.c"
    break;

  case 13: /* close_scope_counter: %empty  */
#line 1001 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_COUNTER); }
#line 7929 "parser_bison.c"
    break;

  case 14: /* close_scope_last: %empty  */
#line 1002 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_LAST); }
#line 7935 "parser_bison.c"
    break;

  case 15: /* close_scope_dccp: %empty  */
#line 1003 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_DCCP); }
#line 7941 "parser_bison.c"
    break;

  case 16: /* close_scope_destroy: %empty  */
#line 1004 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_DESTROY); }
#line 7947 "parser_bison.c"
    break;

  case 17: /* close_scope_dst: %empty  */
#line 1005 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_DST); }
#line 7953 "parser_bison.c"
    break;

  case 18: /* close_scope_dup: %empty  */
#line 1006 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_DUP); }
#line 7959 "parser_bison.c"
    break;

  case 19: /* close_scope_esp: %empty  */
#line 1007 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_ESP); }
#line 7965 "parser_bison.c"
    break;

  case 20: /* close_scope_eth: %empty  */
#line 1008 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ETH); }
#line 7971 "parser_bison.c"
    break;

  case 21: /* close_scope_export: %empty  */
#line 1009 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_EXPORT); }
#line 7977 "parser_bison.c"
    break;

  case 22: /* close_scope_fib: %empty  */
#line 1010 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FIB); }
#line 7983 "parser_bison.c"
    break;

  case 23: /* close_scope_frag: %empty  */
#line 1011 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FRAG); }
#line 7989 "parser_bison.c"
    break;

  case 24: /* close_scope_fwd: %empty  */
#line 1012 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_FWD); }
#line 7995 "parser_bison.c"
    break;

  case 25: /* close_scope_gre: %empty  */
#line 1013 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_GRE); }
#line 8001 "parser_bison.c"
    break;

  case 26: /* close_scope_hash: %empty  */
#line 1014 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HASH); }
#line 8007 "parser_bison.c"
    break;

  case 27: /* close_scope_hbh: %empty  */
#line 1015 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HBH); }
#line 8013 "parser_bison.c"
    break;

  case 28: /* close_scope_ip: %empty  */
#line 1016 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP); }
#line 8019 "parser_bison.c"
    break;

  case 29: /* close_scope_ip6: %empty  */
#line 1017 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP6); }
#line 8025 "parser_bison.c"
    break;

  case 30: /* close_scope_vlan: %empty  */
#line 1018 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_VLAN); }
#line 8031 "parser_bison.c"
    break;

  case 31: /* close_scope_icmp: %empty  */
#line 1019 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ICMP); }
#line 8037 "parser_bison.c"
    break;

  case 32: /* close_scope_igmp: %empty  */
#line 1020 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IGMP); }
#line 8043 "parser_bison.c"
    break;

  case 33: /* close_scope_import: %empty  */
#line 1021 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_IMPORT); }
#line 8049 "parser_bison.c"
    break;

  case 34: /* close_scope_ipsec: %empty  */
#line 1022 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_IPSEC); }
#line 8055 "parser_bison.c"
    break;

  case 35: /* close_scope_list: %empty  */
#line 1023 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_LIST); }
#line 8061 "parser_bison.c"
    break;

  case 36: /* close_scope_limit: %empty  */
#line 1024 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_LIMIT); }
#line 8067 "parser_bison.c"
    break;

  case 37: /* close_scope_meta: %empty  */
#line 1025 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_META); }
#line 8073 "parser_bison.c"
    break;

  case 38: /* close_scope_mh: %empty  */
#line 1026 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_MH); }
#line 8079 "parser_bison.c"
    break;

  case 39: /* close_scope_monitor: %empty  */
#line 1027 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_MONITOR); }
#line 8085 "parser_bison.c"
    break;

  case 40: /* close_scope_nat: %empty  */
#line 1028 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_NAT); }
#line 8091 "parser_bison.c"
    break;

  case 41: /* close_scope_numgen: %empty  */
#line 1029 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_NUMGEN); }
#line 8097 "parser_bison.c"
    break;

  case 42: /* close_scope_osf: %empty  */
#line 1030 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_OSF); }
#line 8103 "parser_bison.c"
    break;

  case 43: /* close_scope_policy: %empty  */
#line 1031 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_POLICY); }
#line 8109 "parser_bison.c"
    break;

  case 44: /* close_scope_quota: %empty  */
#line 1032 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_QUOTA); }
#line 8115 "parser_bison.c"
    break;

  case 45: /* close_scope_queue: %empty  */
#line 1033 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_QUEUE); }
#line 8121 "parser_bison.c"
    break;

  case 46: /* close_scope_reject: %empty  */
#line 1034 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_REJECT); }
#line 8127 "parser_bison.c"
    break;

  case 47: /* close_scope_reset: %empty  */
#line 1035 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_RESET); }
#line 8133 "parser_bison.c"
    break;

  case 48: /* close_scope_rt: %empty  */
#line 1036 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_RT); }
#line 8139 "parser_bison.c"
    break;

  case 49: /* close_scope_sctp: %empty  */
#line 1037 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_SCTP); }
#line 8145 "parser_bison.c"
    break;

  case 50: /* close_scope_sctp_chunk: %empty  */
#line 1038 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SCTP_CHUNK); }
#line 8151 "parser_bison.c"
    break;

  case 51: /* close_scope_secmark: %empty  */
#line 1039 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_SECMARK); }
#line 8157 "parser_bison.c"
    break;

  case 52: /* close_scope_socket: %empty  */
#line 1040 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SOCKET); }
#line 8163 "parser_bison.c"
    break;

  case 53: /* close_scope_tcp: %empty  */
#line 1041 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_TCP); }
#line 8169 "parser_bison.c"
    break;

  case 54: /* close_scope_tproxy: %empty  */
#line 1042 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_TPROXY); }
#line 8175 "parser_bison.c"
    break;

  case 55: /* close_scope_type: %empty  */
#line 1043 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_TYPE); }
#line 8181 "parser_bison.c"
    break;

  case 56: /* close_scope_th: %empty  */
#line 1044 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_TH); }
#line 8187 "parser_bison.c"
    break;

  case 57: /* close_scope_udp: %empty  */
#line 1045 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_UDP); }
#line 8193 "parser_bison.c"
    break;

  case 58: /* close_scope_udplite: %empty  */
#line 1046 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_UDPLITE); }
#line 8199 "parser_bison.c"
    break;

  case 59: /* close_scope_log: %empty  */
#line 1048 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_LOG); }
#line 8205 "parser_bison.c"
    break;

  case 60: /* close_scope_synproxy: %empty  */
#line 1049 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_SYNPROXY); }
#line 8211 "parser_bison.c"
    break;

  case 61: /* close_scope_xt: %empty  */
#line 1050 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_XT); }
#line 8217 "parser_bison.c"
    break;

  case 62: /* common_block: "include" "quoted string" stmt_separator  */
#line 1053 "parser_bison.y"
                        {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 8229 "parser_bison.c"
    break;

  case 63: /* common_block: "define" identifier '=' initializer_expr stmt_separator  */
#line 1061 "parser_bison.y"
                        {
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, (yyvsp[-3].string)) != NULL) {
					erec_queue(error(&(yylsp[-3]), "redefinition of symbol '%s'", (yyvsp[-3].string)),
						   state->msgs);
					expr_free((yyvsp[-1].expr));
					xfree((yyvsp[-3].string));
					YYERROR;
				}

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 8248 "parser_bison.c"
    break;

  case 64: /* common_block: "redefine" identifier '=' initializer_expr stmt_separator  */
#line 1076 "parser_bison.y"
                        {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 8259 "parser_bison.c"
    break;

  case 65: /* common_block: "undefine" identifier stmt_separator  */
#line 1083 "parser_bison.y"
                        {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 8275 "parser_bison.c"
    break;

  case 66: /* common_block: error stmt_separator  */
#line 1095 "parser_bison.y"
                        {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 8285 "parser_bison.c"
    break;

  case 67: /* line: common_block  */
#line 1102 "parser_bison.y"
                                                                { (yyval.cmd) = NULL; }
#line 8291 "parser_bison.c"
    break;

  case 68: /* line: stmt_separator  */
#line 1103 "parser_bison.y"
                                                                { (yyval.cmd) = NULL; }
#line 8297 "parser_bison.c"
    break;

  case 69: /* line: base_cmd stmt_separator  */
#line 1104 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8303 "parser_bison.c"
    break;

  case 70: /* line: base_cmd "end of file"  */
#line 1106 "parser_bison.y"
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
				if ((yyvsp[-1].cmd) != NULL) {
					(yyvsp[-1].cmd)->location = (yylsp[-1]);
					list_add_tail(&(yyvsp[-1].cmd)->list, state->cmds);
				}
				(yyval.cmd) = NULL;
				YYACCEPT;
			}
#line 8325 "parser_bison.c"
    break;

  case 71: /* base_cmd: add_cmd  */
#line 1125 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8331 "parser_bison.c"
    break;

  case 72: /* base_cmd: "add" add_cmd  */
#line 1126 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8337 "parser_bison.c"
    break;

  case 73: /* base_cmd: "replace" replace_cmd  */
#line 1127 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8343 "parser_bison.c"
    break;

  case 74: /* base_cmd: "create" create_cmd  */
#line 1128 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8349 "parser_bison.c"
    break;

  case 75: /* base_cmd: "insert" insert_cmd  */
#line 1129 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8355 "parser_bison.c"
    break;

  case 76: /* base_cmd: "delete" delete_cmd  */
#line 1130 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8361 "parser_bison.c"
    break;

  case 77: /* base_cmd: "get" get_cmd  */
#line 1131 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8367 "parser_bison.c"
    break;

  case 78: /* base_cmd: "list" list_cmd close_scope_list  */
#line 1132 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8373 "parser_bison.c"
    break;

  case 79: /* base_cmd: "reset" reset_cmd close_scope_reset  */
#line 1133 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8379 "parser_bison.c"
    break;

  case 80: /* base_cmd: "flush" flush_cmd  */
#line 1134 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8385 "parser_bison.c"
    break;

  case 81: /* base_cmd: "rename" rename_cmd  */
#line 1135 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8391 "parser_bison.c"
    break;

  case 82: /* base_cmd: "import" import_cmd close_scope_import  */
#line 1136 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8397 "parser_bison.c"
    break;

  case 83: /* base_cmd: "export" export_cmd close_scope_export  */
#line 1137 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8403 "parser_bison.c"
    break;

  case 84: /* base_cmd: "monitor" monitor_cmd close_scope_monitor  */
#line 1138 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8409 "parser_bison.c"
    break;

  case 85: /* base_cmd: "describe" describe_cmd  */
#line 1139 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8415 "parser_bison.c"
    break;

  case 86: /* base_cmd: "destroy" destroy_cmd close_scope_destroy  */
#line 1140 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8421 "parser_bison.c"
    break;

  case 87: /* add_cmd: "table" table_spec  */
#line 1144 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8429 "parser_bison.c"
    break;

  case 88: /* add_cmd: "table" table_spec table_block_alloc '{' table_block '}'  */
#line 1149 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 8439 "parser_bison.c"
    break;

  case 89: /* add_cmd: "chain" chain_spec  */
#line 1155 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8447 "parser_bison.c"
    break;

  case 90: /* add_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1160 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 8458 "parser_bison.c"
    break;

  case 91: /* add_cmd: "rule" rule_position rule  */
#line 1167 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8466 "parser_bison.c"
    break;

  case 92: /* add_cmd: rule_position rule  */
#line 1171 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8474 "parser_bison.c"
    break;

  case 93: /* add_cmd: "set" set_spec set_block_alloc '{' set_block '}'  */
#line 1176 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8484 "parser_bison.c"
    break;

  case 94: /* add_cmd: "map" set_spec map_block_alloc '{' map_block '}'  */
#line 1183 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8494 "parser_bison.c"
    break;

  case 95: /* add_cmd: "element" set_spec set_block_expr  */
#line 1189 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8502 "parser_bison.c"
    break;

  case 96: /* add_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1194 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8512 "parser_bison.c"
    break;

  case 97: /* add_cmd: "counter" obj_spec close_scope_counter  */
#line 1200 "parser_bison.y"
                        {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 8525 "parser_bison.c"
    break;

  case 98: /* add_cmd: "counter" obj_spec counter_obj counter_config close_scope_counter  */
#line 1209 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8533 "parser_bison.c"
    break;

  case 99: /* add_cmd: "counter" obj_spec counter_obj '{' counter_block '}' close_scope_counter  */
#line 1213 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8541 "parser_bison.c"
    break;

  case 100: /* add_cmd: "quota" obj_spec quota_obj quota_config close_scope_quota  */
#line 1217 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8549 "parser_bison.c"
    break;

  case 101: /* add_cmd: "quota" obj_spec quota_obj '{' quota_block '}' close_scope_quota  */
#line 1221 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8557 "parser_bison.c"
    break;

  case 102: /* add_cmd: "ct" "helper" obj_spec ct_obj_alloc '{' ct_helper_block '}' close_scope_ct  */
#line 1225 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8565 "parser_bison.c"
    break;

  case 103: /* add_cmd: "ct" "timeout" obj_spec ct_obj_alloc '{' ct_timeout_block '}' close_scope_ct  */
#line 1229 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8573 "parser_bison.c"
    break;

  case 104: /* add_cmd: "ct" "expectation" obj_spec ct_obj_alloc '{' ct_expect_block '}' close_scope_ct  */
#line 1233 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8581 "parser_bison.c"
    break;

  case 105: /* add_cmd: "limit" obj_spec limit_obj limit_config close_scope_limit  */
#line 1237 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8589 "parser_bison.c"
    break;

  case 106: /* add_cmd: "limit" obj_spec limit_obj '{' limit_block '}' close_scope_limit  */
#line 1241 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8597 "parser_bison.c"
    break;

  case 107: /* add_cmd: "secmark" obj_spec secmark_obj secmark_config close_scope_secmark  */
#line 1245 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8605 "parser_bison.c"
    break;

  case 108: /* add_cmd: "secmark" obj_spec secmark_obj '{' secmark_block '}' close_scope_secmark  */
#line 1249 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8613 "parser_bison.c"
    break;

  case 109: /* add_cmd: "synproxy" obj_spec synproxy_obj synproxy_config close_scope_synproxy  */
#line 1253 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8621 "parser_bison.c"
    break;

  case 110: /* add_cmd: "synproxy" obj_spec synproxy_obj '{' synproxy_block '}' close_scope_synproxy  */
#line 1257 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8629 "parser_bison.c"
    break;

  case 111: /* replace_cmd: "rule" ruleid_spec rule  */
#line 1263 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8637 "parser_bison.c"
    break;

  case 112: /* create_cmd: "table" table_spec  */
#line 1269 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8645 "parser_bison.c"
    break;

  case 113: /* create_cmd: "table" table_spec table_block_alloc '{' table_block '}'  */
#line 1274 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 8655 "parser_bison.c"
    break;

  case 114: /* create_cmd: "chain" chain_spec  */
#line 1280 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8663 "parser_bison.c"
    break;

  case 115: /* create_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1285 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 8674 "parser_bison.c"
    break;

  case 116: /* create_cmd: "set" set_spec set_block_alloc '{' set_block '}'  */
#line 1293 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8684 "parser_bison.c"
    break;

  case 117: /* create_cmd: "map" set_spec map_block_alloc '{' map_block '}'  */
#line 1300 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8694 "parser_bison.c"
    break;

  case 118: /* create_cmd: "element" set_spec set_block_expr  */
#line 1306 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8702 "parser_bison.c"
    break;

  case 119: /* create_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1311 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8712 "parser_bison.c"
    break;

  case 120: /* create_cmd: "counter" obj_spec close_scope_counter  */
#line 1317 "parser_bison.y"
                        {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 8725 "parser_bison.c"
    break;

  case 121: /* create_cmd: "counter" obj_spec counter_obj counter_config close_scope_counter  */
#line 1326 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8733 "parser_bison.c"
    break;

  case 122: /* create_cmd: "quota" obj_spec quota_obj quota_config close_scope_quota  */
#line 1330 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8741 "parser_bison.c"
    break;

  case 123: /* create_cmd: "ct" "helper" obj_spec ct_obj_alloc '{' ct_helper_block '}' close_scope_ct  */
#line 1334 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8749 "parser_bison.c"
    break;

  case 124: /* create_cmd: "ct" "timeout" obj_spec ct_obj_alloc '{' ct_timeout_block '}' close_scope_ct  */
#line 1338 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8757 "parser_bison.c"
    break;

  case 125: /* create_cmd: "ct" "expectation" obj_spec ct_obj_alloc '{' ct_expect_block '}' close_scope_ct  */
#line 1342 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8765 "parser_bison.c"
    break;

  case 126: /* create_cmd: "limit" obj_spec limit_obj limit_config close_scope_limit  */
#line 1346 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8773 "parser_bison.c"
    break;

  case 127: /* create_cmd: "secmark" obj_spec secmark_obj secmark_config close_scope_secmark  */
#line 1350 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8781 "parser_bison.c"
    break;

  case 128: /* create_cmd: "synproxy" obj_spec synproxy_obj synproxy_config close_scope_synproxy  */
#line 1354 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8789 "parser_bison.c"
    break;

  case 129: /* insert_cmd: "rule" rule_position rule  */
#line 1360 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8797 "parser_bison.c"
    break;

  case 138: /* delete_cmd: "table" table_or_id_spec  */
#line 1382 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8805 "parser_bison.c"
    break;

  case 139: /* delete_cmd: "chain" chain_or_id_spec  */
#line 1386 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8813 "parser_bison.c"
    break;

  case 140: /* delete_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1391 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 8823 "parser_bison.c"
    break;

  case 141: /* delete_cmd: "rule" ruleid_spec  */
#line 1397 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8831 "parser_bison.c"
    break;

  case 142: /* delete_cmd: "set" set_or_id_spec  */
#line 1401 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8839 "parser_bison.c"
    break;

  case 143: /* delete_cmd: "map" set_spec  */
#line 1405 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8847 "parser_bison.c"
    break;

  case 144: /* delete_cmd: "element" set_spec set_block_expr  */
#line 1409 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8855 "parser_bison.c"
    break;

  case 145: /* delete_cmd: "flowtable" flowtable_spec  */
#line 1413 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8863 "parser_bison.c"
    break;

  case 146: /* delete_cmd: "flowtable" flowtableid_spec  */
#line 1417 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8871 "parser_bison.c"
    break;

  case 147: /* delete_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1422 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8881 "parser_bison.c"
    break;

  case 148: /* delete_cmd: "counter" obj_or_id_spec close_scope_counter  */
#line 1428 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8889 "parser_bison.c"
    break;

  case 149: /* delete_cmd: "quota" obj_or_id_spec close_scope_quota  */
#line 1432 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8897 "parser_bison.c"
    break;

  case 150: /* delete_cmd: "ct" ct_obj_type obj_spec ct_obj_alloc close_scope_ct  */
#line 1436 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-3].val), &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
				if ((yyvsp[-3].val) == NFT_OBJECT_CT_TIMEOUT)
					init_list_head(&(yyvsp[-1].obj)->ct_timeout.timeout_list);
			}
#line 8907 "parser_bison.c"
    break;

  case 151: /* delete_cmd: "limit" obj_or_id_spec close_scope_limit  */
#line 1442 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8915 "parser_bison.c"
    break;

  case 152: /* delete_cmd: "secmark" obj_or_id_spec close_scope_secmark  */
#line 1446 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8923 "parser_bison.c"
    break;

  case 153: /* delete_cmd: "synproxy" obj_or_id_spec close_scope_synproxy  */
#line 1450 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8931 "parser_bison.c"
    break;

  case 154: /* destroy_cmd: "table" table_or_id_spec  */
#line 1456 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8939 "parser_bison.c"
    break;

  case 155: /* destroy_cmd: "chain" chain_or_id_spec  */
#line 1460 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8947 "parser_bison.c"
    break;

  case 156: /* destroy_cmd: "rule" ruleid_spec  */
#line 1464 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8955 "parser_bison.c"
    break;

  case 157: /* destroy_cmd: "set" set_or_id_spec  */
#line 1468 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8963 "parser_bison.c"
    break;

  case 158: /* destroy_cmd: "map" set_spec  */
#line 1472 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8971 "parser_bison.c"
    break;

  case 159: /* destroy_cmd: "element" set_spec set_block_expr  */
#line 1476 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8979 "parser_bison.c"
    break;

  case 160: /* destroy_cmd: "flowtable" flowtable_spec  */
#line 1480 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8987 "parser_bison.c"
    break;

  case 161: /* destroy_cmd: "flowtable" flowtableid_spec  */
#line 1484 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8995 "parser_bison.c"
    break;

  case 162: /* destroy_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1489 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 9005 "parser_bison.c"
    break;

  case 163: /* destroy_cmd: "counter" obj_or_id_spec close_scope_counter  */
#line 1495 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9013 "parser_bison.c"
    break;

  case 164: /* destroy_cmd: "quota" obj_or_id_spec close_scope_quota  */
#line 1499 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9021 "parser_bison.c"
    break;

  case 165: /* destroy_cmd: "ct" ct_obj_type obj_spec ct_obj_alloc close_scope_ct  */
#line 1503 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DESTROY, (yyvsp[-3].val), &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
				if ((yyvsp[-3].val) == NFT_OBJECT_CT_TIMEOUT)
					init_list_head(&(yyvsp[-1].obj)->ct_timeout.timeout_list);
			}
#line 9031 "parser_bison.c"
    break;

  case 166: /* destroy_cmd: "limit" obj_or_id_spec close_scope_limit  */
#line 1509 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9039 "parser_bison.c"
    break;

  case 167: /* destroy_cmd: "secmark" obj_or_id_spec close_scope_secmark  */
#line 1513 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9047 "parser_bison.c"
    break;

  case 168: /* destroy_cmd: "synproxy" obj_or_id_spec close_scope_synproxy  */
#line 1517 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9055 "parser_bison.c"
    break;

  case 169: /* get_cmd: "element" set_spec set_block_expr  */
#line 1524 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 9063 "parser_bison.c"
    break;

  case 170: /* list_cmd: "table" table_spec  */
#line 1530 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9071 "parser_bison.c"
    break;

  case 171: /* list_cmd: "tables" ruleset_spec  */
#line 1534 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9079 "parser_bison.c"
    break;

  case 172: /* list_cmd: "chain" chain_spec  */
#line 1538 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9087 "parser_bison.c"
    break;

  case 173: /* list_cmd: "chains" ruleset_spec  */
#line 1542 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9095 "parser_bison.c"
    break;

  case 174: /* list_cmd: "sets" ruleset_spec  */
#line 1546 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9103 "parser_bison.c"
    break;

  case 175: /* list_cmd: "sets" "table" table_spec  */
#line 1550 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9111 "parser_bison.c"
    break;

  case 176: /* list_cmd: "set" set_spec  */
#line 1554 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9119 "parser_bison.c"
    break;

  case 177: /* list_cmd: "counters" ruleset_spec  */
#line 1558 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9127 "parser_bison.c"
    break;

  case 178: /* list_cmd: "counters" "table" table_spec  */
#line 1562 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9135 "parser_bison.c"
    break;

  case 179: /* list_cmd: "counter" obj_spec close_scope_counter  */
#line 1566 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9143 "parser_bison.c"
    break;

  case 180: /* list_cmd: "quotas" ruleset_spec  */
#line 1570 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9151 "parser_bison.c"
    break;

  case 181: /* list_cmd: "quotas" "table" table_spec  */
#line 1574 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9159 "parser_bison.c"
    break;

  case 182: /* list_cmd: "quota" obj_spec close_scope_quota  */
#line 1578 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9167 "parser_bison.c"
    break;

  case 183: /* list_cmd: "limits" ruleset_spec  */
#line 1582 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9175 "parser_bison.c"
    break;

  case 184: /* list_cmd: "limits" "table" table_spec  */
#line 1586 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9183 "parser_bison.c"
    break;

  case 185: /* list_cmd: "limit" obj_spec close_scope_limit  */
#line 1590 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9191 "parser_bison.c"
    break;

  case 186: /* list_cmd: "secmarks" ruleset_spec  */
#line 1594 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9199 "parser_bison.c"
    break;

  case 187: /* list_cmd: "secmarks" "table" table_spec  */
#line 1598 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9207 "parser_bison.c"
    break;

  case 188: /* list_cmd: "secmark" obj_spec close_scope_secmark  */
#line 1602 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9215 "parser_bison.c"
    break;

  case 189: /* list_cmd: "synproxys" ruleset_spec  */
#line 1606 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9223 "parser_bison.c"
    break;

  case 190: /* list_cmd: "synproxys" "table" table_spec  */
#line 1610 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9231 "parser_bison.c"
    break;

  case 191: /* list_cmd: "synproxy" obj_spec close_scope_synproxy  */
#line 1614 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9239 "parser_bison.c"
    break;

  case 192: /* list_cmd: "ruleset" ruleset_spec  */
#line 1618 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9247 "parser_bison.c"
    break;

  case 193: /* list_cmd: "flow" "tables" ruleset_spec  */
#line 1622 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9255 "parser_bison.c"
    break;

  case 194: /* list_cmd: "flow" "table" set_spec  */
#line 1626 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9263 "parser_bison.c"
    break;

  case 195: /* list_cmd: "meters" ruleset_spec  */
#line 1630 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9271 "parser_bison.c"
    break;

  case 196: /* list_cmd: "meter" set_spec  */
#line 1634 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9279 "parser_bison.c"
    break;

  case 197: /* list_cmd: "flowtables" ruleset_spec  */
#line 1638 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9287 "parser_bison.c"
    break;

  case 198: /* list_cmd: "flowtable" flowtable_spec  */
#line 1642 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9295 "parser_bison.c"
    break;

  case 199: /* list_cmd: "maps" ruleset_spec  */
#line 1646 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9303 "parser_bison.c"
    break;

  case 200: /* list_cmd: "map" set_spec  */
#line 1650 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9311 "parser_bison.c"
    break;

  case 201: /* list_cmd: "ct" ct_obj_type obj_spec close_scope_ct  */
#line 1654 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9319 "parser_bison.c"
    break;

  case 202: /* list_cmd: "ct" ct_cmd_type "table" table_spec close_scope_ct  */
#line 1658 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, (yyvsp[-3].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9327 "parser_bison.c"
    break;

  case 203: /* list_cmd: "hooks" basehook_spec  */
#line 1662 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_HOOKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9335 "parser_bison.c"
    break;

  case 204: /* basehook_device_name: "device" "string"  */
#line 1668 "parser_bison.y"
                        {
				(yyval.string) = (yyvsp[0].string);
			}
#line 9343 "parser_bison.c"
    break;

  case 205: /* basehook_spec: ruleset_spec  */
#line 1674 "parser_bison.y"
                        {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 9351 "parser_bison.c"
    break;

  case 206: /* basehook_spec: ruleset_spec basehook_device_name  */
#line 1678 "parser_bison.y"
                        {
				if ((yyvsp[0].string)) {
					(yyvsp[-1].handle).obj.name = (yyvsp[0].string);
					(yyvsp[-1].handle).obj.location = (yylsp[0]);
				}
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9363 "parser_bison.c"
    break;

  case 207: /* reset_cmd: "counters" ruleset_spec  */
#line 1688 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9371 "parser_bison.c"
    break;

  case 208: /* reset_cmd: "counters" table_spec  */
#line 1692 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9379 "parser_bison.c"
    break;

  case 209: /* reset_cmd: "counters" "table" table_spec  */
#line 1696 "parser_bison.y"
                        {
				/* alias of previous rule. */
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9388 "parser_bison.c"
    break;

  case 210: /* reset_cmd: "counter" obj_spec close_scope_counter  */
#line 1701 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[-1].handle),&(yyloc), NULL);
			}
#line 9396 "parser_bison.c"
    break;

  case 211: /* reset_cmd: "quotas" ruleset_spec  */
#line 1705 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9404 "parser_bison.c"
    break;

  case 212: /* reset_cmd: "quotas" "table" table_spec  */
#line 1709 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9412 "parser_bison.c"
    break;

  case 213: /* reset_cmd: "quotas" table_spec  */
#line 1713 "parser_bison.y"
                        {
				/* alias of previous rule. */
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9421 "parser_bison.c"
    break;

  case 214: /* reset_cmd: "quota" obj_spec close_scope_quota  */
#line 1718 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9429 "parser_bison.c"
    break;

  case 215: /* reset_cmd: "rules" ruleset_spec  */
#line 1722 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9437 "parser_bison.c"
    break;

  case 216: /* reset_cmd: "rules" table_spec  */
#line 1726 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9445 "parser_bison.c"
    break;

  case 217: /* reset_cmd: "rules" "table" table_spec  */
#line 1730 "parser_bison.y"
                        {
				/* alias of previous rule. */
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9454 "parser_bison.c"
    break;

  case 218: /* reset_cmd: "rules" chain_spec  */
#line 1735 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9462 "parser_bison.c"
    break;

  case 219: /* reset_cmd: "rules" "chain" chain_spec  */
#line 1739 "parser_bison.y"
                        {
				/* alias of previous rule. */
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9471 "parser_bison.c"
    break;

  case 220: /* reset_cmd: "rule" ruleid_spec  */
#line 1744 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9479 "parser_bison.c"
    break;

  case 221: /* reset_cmd: "element" set_spec set_block_expr  */
#line 1748 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 9487 "parser_bison.c"
    break;

  case 222: /* reset_cmd: "set" set_or_id_spec  */
#line 1752 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9495 "parser_bison.c"
    break;

  case 223: /* reset_cmd: "map" set_or_id_spec  */
#line 1756 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9503 "parser_bison.c"
    break;

  case 224: /* flush_cmd: "table" table_spec  */
#line 1762 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9511 "parser_bison.c"
    break;

  case 225: /* flush_cmd: "chain" chain_spec  */
#line 1766 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9519 "parser_bison.c"
    break;

  case 226: /* flush_cmd: "set" set_spec  */
#line 1770 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9527 "parser_bison.c"
    break;

  case 227: /* flush_cmd: "map" set_spec  */
#line 1774 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9535 "parser_bison.c"
    break;

  case 228: /* flush_cmd: "flow" "table" set_spec  */
#line 1778 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9543 "parser_bison.c"
    break;

  case 229: /* flush_cmd: "meter" set_spec  */
#line 1782 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9551 "parser_bison.c"
    break;

  case 230: /* flush_cmd: "ruleset" ruleset_spec  */
#line 1786 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9559 "parser_bison.c"
    break;

  case 231: /* rename_cmd: "chain" chain_spec identifier  */
#line 1792 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 9568 "parser_bison.c"
    break;

  case 232: /* import_cmd: "ruleset" markup_format  */
#line 1799 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9578 "parser_bison.c"
    break;

  case 233: /* import_cmd: markup_format  */
#line 1805 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9588 "parser_bison.c"
    break;

  case 234: /* export_cmd: "ruleset" markup_format  */
#line 1813 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9598 "parser_bison.c"
    break;

  case 235: /* export_cmd: markup_format  */
#line 1819 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9608 "parser_bison.c"
    break;

  case 236: /* monitor_cmd: monitor_event monitor_object monitor_format  */
#line 1827 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 9619 "parser_bison.c"
    break;

  case 237: /* monitor_event: %empty  */
#line 1835 "parser_bison.y"
                                                { (yyval.string) = NULL; }
#line 9625 "parser_bison.c"
    break;

  case 238: /* monitor_event: "string"  */
#line 1836 "parser_bison.y"
                                                { (yyval.string) = (yyvsp[0].string); }
#line 9631 "parser_bison.c"
    break;

  case 239: /* monitor_object: %empty  */
#line 1839 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 9637 "parser_bison.c"
    break;

  case 240: /* monitor_object: "tables"  */
#line 1840 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 9643 "parser_bison.c"
    break;

  case 241: /* monitor_object: "chains"  */
#line 1841 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 9649 "parser_bison.c"
    break;

  case 242: /* monitor_object: "sets"  */
#line 1842 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 9655 "parser_bison.c"
    break;

  case 243: /* monitor_object: "rules"  */
#line 1843 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 9661 "parser_bison.c"
    break;

  case 244: /* monitor_object: "elements"  */
#line 1844 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 9667 "parser_bison.c"
    break;

  case 245: /* monitor_object: "ruleset"  */
#line 1845 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 9673 "parser_bison.c"
    break;

  case 246: /* monitor_object: "trace"  */
#line 1846 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 9679 "parser_bison.c"
    break;

  case 247: /* monitor_format: %empty  */
#line 1849 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 9685 "parser_bison.c"
    break;

  case 249: /* markup_format: "xml"  */
#line 1853 "parser_bison.y"
                                                { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 9691 "parser_bison.c"
    break;

  case 250: /* markup_format: "json"  */
#line 1854 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 9697 "parser_bison.c"
    break;

  case 251: /* markup_format: "vm" "json"  */
#line 1855 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 9703 "parser_bison.c"
    break;

  case 252: /* describe_cmd: primary_expr  */
#line 1859 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 9713 "parser_bison.c"
    break;

  case 253: /* table_block_alloc: %empty  */
#line 1867 "parser_bison.y"
                        {
				(yyval.table) = table_alloc();
				if (open_scope(state, &(yyval.table)->scope) < 0) {
					erec_queue(error(&(yyloc), "too many levels of nesting"),
						   state->msgs);
					state->nerrs++;
				}
			}
#line 9726 "parser_bison.c"
    break;

  case 254: /* table_options: "flags" "string"  */
#line 1878 "parser_bison.y"
                        {
				if (strcmp((yyvsp[0].string), "dormant") == 0) {
					(yyvsp[-2].table)->flags |= TABLE_F_DORMANT;
					xfree((yyvsp[0].string));
				} else if (strcmp((yyvsp[0].string), "owner") == 0) {
					(yyvsp[-2].table)->flags |= TABLE_F_OWNER;
					xfree((yyvsp[0].string));
				} else {
					erec_queue(error(&(yylsp[0]), "unknown table option %s", (yyvsp[0].string)),
						   state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}
			}
#line 9745 "parser_bison.c"
    break;

  case 255: /* table_options: comment_spec  */
#line 1893 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].table)->comment, &(yyloc), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].table)->comment = (yyvsp[0].string);
			}
#line 9757 "parser_bison.c"
    break;

  case 256: /* table_block: %empty  */
#line 1902 "parser_bison.y"
                                                { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 9763 "parser_bison.c"
    break;

  case 260: /* table_block: table_block "chain" chain_identifier chain_block_alloc '{' chain_block '}' stmt_separator  */
#line 1909 "parser_bison.y"
                        {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9776 "parser_bison.c"
    break;

  case 261: /* table_block: table_block "set" set_identifier set_block_alloc '{' set_block '}' stmt_separator  */
#line 1920 "parser_bison.y"
                        {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9788 "parser_bison.c"
    break;

  case 262: /* table_block: table_block "map" set_identifier map_block_alloc '{' map_block '}' stmt_separator  */
#line 1930 "parser_bison.y"
                        {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9800 "parser_bison.c"
    break;

  case 263: /* table_block: table_block "flowtable" flowtable_identifier flowtable_block_alloc '{' flowtable_block '}' stmt_separator  */
#line 1941 "parser_bison.y"
                        {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9812 "parser_bison.c"
    break;

  case 264: /* table_block: table_block "counter" obj_identifier obj_block_alloc '{' counter_block '}' stmt_separator close_scope_counter  */
#line 1951 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9825 "parser_bison.c"
    break;

  case 265: /* table_block: table_block "quota" obj_identifier obj_block_alloc '{' quota_block '}' stmt_separator close_scope_quota  */
#line 1962 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9838 "parser_bison.c"
    break;

  case 266: /* table_block: table_block "ct" "helper" obj_identifier obj_block_alloc '{' ct_helper_block '}' close_scope_ct stmt_separator  */
#line 1971 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9851 "parser_bison.c"
    break;

  case 267: /* table_block: table_block "ct" "timeout" obj_identifier obj_block_alloc '{' ct_timeout_block '}' close_scope_ct stmt_separator  */
#line 1980 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9864 "parser_bison.c"
    break;

  case 268: /* table_block: table_block "ct" "expectation" obj_identifier obj_block_alloc '{' ct_expect_block '}' close_scope_ct stmt_separator  */
#line 1989 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9877 "parser_bison.c"
    break;

  case 269: /* table_block: table_block "limit" obj_identifier obj_block_alloc '{' limit_block '}' stmt_separator close_scope_limit  */
#line 2000 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9890 "parser_bison.c"
    break;

  case 270: /* table_block: table_block "secmark" obj_identifier obj_block_alloc '{' secmark_block '}' stmt_separator close_scope_secmark  */
#line 2011 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9903 "parser_bison.c"
    break;

  case 271: /* table_block: table_block "synproxy" obj_identifier obj_block_alloc '{' synproxy_block '}' stmt_separator close_scope_synproxy  */
#line 2022 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9916 "parser_bison.c"
    break;

  case 272: /* chain_block_alloc: %empty  */
#line 2033 "parser_bison.y"
                        {
				(yyval.chain) = chain_alloc();
				if (open_scope(state, &(yyval.chain)->scope) < 0) {
					erec_queue(error(&(yyloc), "too many levels of nesting"),
						   state->msgs);
					state->nerrs++;
				}
			}
#line 9929 "parser_bison.c"
    break;

  case 273: /* chain_block: %empty  */
#line 2043 "parser_bison.y"
                                                { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 9935 "parser_bison.c"
    break;

  case 279: /* chain_block: chain_block rule stmt_separator  */
#line 2050 "parser_bison.y"
                        {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 9944 "parser_bison.c"
    break;

  case 280: /* chain_block: chain_block "devices" '=' flowtable_expr stmt_separator  */
#line 2055 "parser_bison.y"
                        {
				if ((yyval.chain)->dev_expr) {
					list_splice_init(&(yyvsp[-1].expr)->expressions, &(yyval.chain)->dev_expr->expressions);
					expr_free((yyvsp[-1].expr));
					break;
				}
				(yyval.chain)->dev_expr = (yyvsp[-1].expr);
			}
#line 9957 "parser_bison.c"
    break;

  case 281: /* chain_block: chain_block comment_spec stmt_separator  */
#line 2064 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].chain)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].chain)->comment = (yyvsp[-1].string);
			}
#line 9969 "parser_bison.c"
    break;

  case 282: /* subchain_block: %empty  */
#line 2073 "parser_bison.y"
                                                { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 9975 "parser_bison.c"
    break;

  case 284: /* subchain_block: subchain_block rule stmt_separator  */
#line 2076 "parser_bison.y"
                        {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 9984 "parser_bison.c"
    break;

  case 285: /* typeof_data_expr: primary_expr  */
#line 2083 "parser_bison.y"
                        {
				struct expr *e = (yyvsp[0].expr);

				if (e->etype == EXPR_SYMBOL &&
				    strcmp("verdict", e->identifier) == 0) {
					struct expr *v = verdict_expr_alloc(&(yylsp[0]), NF_ACCEPT, NULL);

					expr_free(e);
					v->flags &= ~EXPR_F_CONSTANT;
					e = v;
				}

				if (expr_ops(e)->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "map data type '%s' lacks typeof serialization", expr_ops(e)->name),
						   state->msgs);
					expr_free(e);
					YYERROR;
				}
				(yyval.expr) = e;
			}
#line 10009 "parser_bison.c"
    break;

  case 286: /* typeof_data_expr: typeof_expr "." primary_expr  */
#line 2104 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10022 "parser_bison.c"
    break;

  case 287: /* typeof_expr: primary_expr  */
#line 2115 "parser_bison.y"
                        {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10037 "parser_bison.c"
    break;

  case 288: /* typeof_expr: typeof_expr "." primary_expr  */
#line 2126 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10050 "parser_bison.c"
    break;

  case 289: /* set_block_alloc: %empty  */
#line 2138 "parser_bison.y"
                        {
				(yyval.set) = set_alloc(&internal_location);
			}
#line 10058 "parser_bison.c"
    break;

  case 290: /* set_block: %empty  */
#line 2143 "parser_bison.y"
                                                { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 10064 "parser_bison.c"
    break;

  case 293: /* set_block: set_block "type" data_type_expr stmt_separator close_scope_type  */
#line 2147 "parser_bison.y"
                        {
				(yyvsp[-4].set)->key = (yyvsp[-2].expr);
				(yyval.set) = (yyvsp[-4].set);
			}
#line 10073 "parser_bison.c"
    break;

  case 294: /* set_block: set_block "typeof" typeof_expr stmt_separator  */
#line 2152 "parser_bison.y"
                        {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10083 "parser_bison.c"
    break;

  case 295: /* set_block: set_block "flags" set_flag_list stmt_separator  */
#line 2158 "parser_bison.y"
                        {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10092 "parser_bison.c"
    break;

  case 296: /* set_block: set_block "timeout" time_spec stmt_separator  */
#line 2163 "parser_bison.y"
                        {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10101 "parser_bison.c"
    break;

  case 297: /* set_block: set_block "gc-interval" time_spec stmt_separator  */
#line 2168 "parser_bison.y"
                        {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10110 "parser_bison.c"
    break;

  case 298: /* set_block: set_block stateful_stmt_list stmt_separator  */
#line 2173 "parser_bison.y"
                        {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 10120 "parser_bison.c"
    break;

  case 299: /* set_block: set_block "elements" '=' set_block_expr  */
#line 2179 "parser_bison.y"
                        {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10129 "parser_bison.c"
    break;

  case 300: /* set_block: set_block "auto-merge"  */
#line 2184 "parser_bison.y"
                        {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 10138 "parser_bison.c"
    break;

  case 302: /* set_block: set_block comment_spec stmt_separator  */
#line 2190 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 10151 "parser_bison.c"
    break;

  case 305: /* set_flag_list: set_flag_list "comma" set_flag  */
#line 2205 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10159 "parser_bison.c"
    break;

  case 307: /* set_flag: "constant"  */
#line 2211 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_CONSTANT; }
#line 10165 "parser_bison.c"
    break;

  case 308: /* set_flag: "interval"  */
#line 2212 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_INTERVAL; }
#line 10171 "parser_bison.c"
    break;

  case 309: /* set_flag: "timeout"  */
#line 2213 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_TIMEOUT; }
#line 10177 "parser_bison.c"
    break;

  case 310: /* set_flag: "dynamic"  */
#line 2214 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_EVAL; }
#line 10183 "parser_bison.c"
    break;

  case 311: /* map_block_alloc: %empty  */
#line 2218 "parser_bison.y"
                        {
				(yyval.set) = set_alloc(&internal_location);
			}
#line 10191 "parser_bison.c"
    break;

  case 312: /* map_block_obj_type: "counter" close_scope_counter  */
#line 2223 "parser_bison.y"
                                                            { (yyval.val) = NFT_OBJECT_COUNTER; }
#line 10197 "parser_bison.c"
    break;

  case 313: /* map_block_obj_type: "quota" close_scope_quota  */
#line 2224 "parser_bison.y"
                                                          { (yyval.val) = NFT_OBJECT_QUOTA; }
#line 10203 "parser_bison.c"
    break;

  case 314: /* map_block_obj_type: "limit" close_scope_limit  */
#line 2225 "parser_bison.y"
                                                          { (yyval.val) = NFT_OBJECT_LIMIT; }
#line 10209 "parser_bison.c"
    break;

  case 315: /* map_block_obj_type: "secmark" close_scope_secmark  */
#line 2226 "parser_bison.y"
                                                            { (yyval.val) = NFT_OBJECT_SECMARK; }
#line 10215 "parser_bison.c"
    break;

  case 316: /* map_block_obj_type: "synproxy" close_scope_synproxy  */
#line 2227 "parser_bison.y"
                                                              { (yyval.val) = NFT_OBJECT_SYNPROXY; }
#line 10221 "parser_bison.c"
    break;

  case 317: /* map_block_data_interval: "interval"  */
#line 2230 "parser_bison.y"
                                         { (yyval.val) = EXPR_F_INTERVAL; }
#line 10227 "parser_bison.c"
    break;

  case 318: /* map_block_data_interval: %empty  */
#line 2231 "parser_bison.y"
                                { (yyval.val) = 0; }
#line 10233 "parser_bison.c"
    break;

  case 319: /* map_block: %empty  */
#line 2234 "parser_bison.y"
                                                { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 10239 "parser_bison.c"
    break;

  case 322: /* map_block: map_block "timeout" time_spec stmt_separator  */
#line 2238 "parser_bison.y"
                        {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10248 "parser_bison.c"
    break;

  case 323: /* map_block: map_block "gc-interval" time_spec stmt_separator  */
#line 2243 "parser_bison.y"
                        {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10257 "parser_bison.c"
    break;

  case 324: /* map_block: map_block "type" data_type_expr "colon" map_block_data_interval data_type_expr stmt_separator close_scope_type  */
#line 2250 "parser_bison.y"
                        {
				(yyvsp[-7].set)->key = (yyvsp[-5].expr);
				(yyvsp[-7].set)->data = (yyvsp[-2].expr);
				(yyvsp[-7].set)->data->flags |= (yyvsp[-3].val);

				(yyvsp[-7].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-7].set);
			}
#line 10270 "parser_bison.c"
    break;

  case 325: /* map_block: map_block "typeof" typeof_expr "colon" typeof_data_expr stmt_separator  */
#line 2261 "parser_bison.y"
                        {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 10283 "parser_bison.c"
    break;

  case 326: /* map_block: map_block "typeof" typeof_expr "colon" "interval" typeof_expr stmt_separator  */
#line 2272 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				datatype_set((yyvsp[-6].set)->key, (yyvsp[-4].expr)->dtype);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 10297 "parser_bison.c"
    break;

  case 327: /* map_block: map_block "type" data_type_expr "colon" map_block_obj_type stmt_separator close_scope_type  */
#line 2284 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->objtype = (yyvsp[-2].val);
				(yyvsp[-6].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 10308 "parser_bison.c"
    break;

  case 328: /* map_block: map_block "flags" set_flag_list stmt_separator  */
#line 2291 "parser_bison.y"
                        {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10317 "parser_bison.c"
    break;

  case 329: /* map_block: map_block stateful_stmt_list stmt_separator  */
#line 2296 "parser_bison.y"
                        {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 10327 "parser_bison.c"
    break;

  case 330: /* map_block: map_block "elements" '=' set_block_expr  */
#line 2302 "parser_bison.y"
                        {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10336 "parser_bison.c"
    break;

  case 331: /* map_block: map_block comment_spec stmt_separator  */
#line 2307 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 10349 "parser_bison.c"
    break;

  case 333: /* set_mechanism: "policy" set_policy_spec close_scope_policy  */
#line 2319 "parser_bison.y"
                        {
				(yyvsp[-3].set)->policy = (yyvsp[-1].val);
			}
#line 10357 "parser_bison.c"
    break;

  case 334: /* set_mechanism: "size" "number"  */
#line 2323 "parser_bison.y"
                        {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 10365 "parser_bison.c"
    break;

  case 335: /* set_policy_spec: "performance"  */
#line 2328 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 10371 "parser_bison.c"
    break;

  case 336: /* set_policy_spec: "memory"  */
#line 2329 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 10377 "parser_bison.c"
    break;

  case 337: /* flowtable_block_alloc: %empty  */
#line 2333 "parser_bison.y"
                        {
				(yyval.flowtable) = flowtable_alloc(&internal_location);
			}
#line 10385 "parser_bison.c"
    break;

  case 338: /* flowtable_block: %empty  */
#line 2338 "parser_bison.y"
                                                { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 10391 "parser_bison.c"
    break;

  case 341: /* flowtable_block: flowtable_block "hook" "string" prio_spec stmt_separator  */
#line 2342 "parser_bison.y"
                        {
				(yyval.flowtable)->hook.loc = (yylsp[-2]);
				(yyval.flowtable)->hook.name = chain_hookname_lookup((yyvsp[-2].string));
				if ((yyval.flowtable)->hook.name == NULL) {
					erec_queue(error(&(yylsp[-2]), "unknown chain hook"),
						   state->msgs);
					xfree((yyvsp[-2].string));
					YYERROR;
				}
				xfree((yyvsp[-2].string));

				(yyval.flowtable)->priority = (yyvsp[-1].prio_spec);
			}
#line 10409 "parser_bison.c"
    break;

  case 342: /* flowtable_block: flowtable_block "devices" '=' flowtable_expr stmt_separator  */
#line 2356 "parser_bison.y"
                        {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 10417 "parser_bison.c"
    break;

  case 343: /* flowtable_block: flowtable_block "counter" close_scope_counter  */
#line 2360 "parser_bison.y"
                        {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 10425 "parser_bison.c"
    break;

  case 344: /* flowtable_block: flowtable_block "flags" "offload" stmt_separator  */
#line 2364 "parser_bison.y"
                        {
				(yyval.flowtable)->flags |= FLOWTABLE_F_HW_OFFLOAD;
			}
#line 10433 "parser_bison.c"
    break;

  case 345: /* flowtable_expr: '{' flowtable_list_expr '}'  */
#line 2370 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10442 "parser_bison.c"
    break;

  case 346: /* flowtable_expr: variable_expr  */
#line 2375 "parser_bison.y"
                        {
				(yyvsp[0].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10451 "parser_bison.c"
    break;

  case 347: /* flowtable_list_expr: flowtable_expr_member  */
#line 2382 "parser_bison.y"
                        {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10460 "parser_bison.c"
    break;

  case 348: /* flowtable_list_expr: flowtable_list_expr "comma" flowtable_expr_member  */
#line 2387 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10469 "parser_bison.c"
    break;

  case 350: /* flowtable_expr_member: "quoted string"  */
#line 2395 "parser_bison.y"
                        {
				struct expr *expr = ifname_expr_alloc(&(yyloc), state->msgs, (yyvsp[0].string));

				if (!expr)
					YYERROR;

				(yyval.expr) = expr;
			}
#line 10482 "parser_bison.c"
    break;

  case 351: /* flowtable_expr_member: "string"  */
#line 2404 "parser_bison.y"
                        {
				struct expr *expr = ifname_expr_alloc(&(yyloc), state->msgs, (yyvsp[0].string));

				if (!expr)
					YYERROR;

				(yyval.expr) = expr;
			}
#line 10495 "parser_bison.c"
    break;

  case 352: /* flowtable_expr_member: variable_expr  */
#line 2413 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10504 "parser_bison.c"
    break;

  case 353: /* data_type_atom_expr: type_identifier  */
#line 2420 "parser_bison.y"
                        {
				const struct datatype *dtype = datatype_lookup_byname((yyvsp[0].string));
				if (dtype == NULL) {
					erec_queue(error(&(yylsp[0]), "unknown datatype %s", (yyvsp[0].string)),
						   state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), dtype, dtype->byteorder,
							 dtype->size, NULL);
				xfree((yyvsp[0].string));
			}
#line 10521 "parser_bison.c"
    break;

  case 354: /* data_type_atom_expr: "time"  */
#line 2433 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 10530 "parser_bison.c"
    break;

  case 356: /* data_type_expr: data_type_expr "." data_type_atom_expr  */
#line 2441 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10543 "parser_bison.c"
    break;

  case 357: /* obj_block_alloc: %empty  */
#line 2452 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&internal_location);
			}
#line 10551 "parser_bison.c"
    break;

  case 358: /* counter_block: %empty  */
#line 2457 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10557 "parser_bison.c"
    break;

  case 361: /* counter_block: counter_block counter_config  */
#line 2461 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10565 "parser_bison.c"
    break;

  case 362: /* counter_block: counter_block comment_spec  */
#line 2465 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10577 "parser_bison.c"
    break;

  case 363: /* quota_block: %empty  */
#line 2474 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10583 "parser_bison.c"
    break;

  case 366: /* quota_block: quota_block quota_config  */
#line 2478 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10591 "parser_bison.c"
    break;

  case 367: /* quota_block: quota_block comment_spec  */
#line 2482 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10603 "parser_bison.c"
    break;

  case 368: /* ct_helper_block: %empty  */
#line 2491 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10609 "parser_bison.c"
    break;

  case 371: /* ct_helper_block: ct_helper_block ct_helper_config  */
#line 2495 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10617 "parser_bison.c"
    break;

  case 372: /* ct_helper_block: ct_helper_block comment_spec  */
#line 2499 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10629 "parser_bison.c"
    break;

  case 373: /* ct_timeout_block: %empty  */
#line 2509 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[(-1) - (0)].obj);
				init_list_head(&(yyval.obj)->ct_timeout.timeout_list);
			}
#line 10638 "parser_bison.c"
    break;

  case 376: /* ct_timeout_block: ct_timeout_block ct_timeout_config  */
#line 2516 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10646 "parser_bison.c"
    break;

  case 377: /* ct_timeout_block: ct_timeout_block comment_spec  */
#line 2520 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10658 "parser_bison.c"
    break;

  case 378: /* ct_expect_block: %empty  */
#line 2529 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10664 "parser_bison.c"
    break;

  case 381: /* ct_expect_block: ct_expect_block ct_expect_config  */
#line 2533 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10672 "parser_bison.c"
    break;

  case 382: /* ct_expect_block: ct_expect_block comment_spec  */
#line 2537 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10684 "parser_bison.c"
    break;

  case 383: /* limit_block: %empty  */
#line 2546 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10690 "parser_bison.c"
    break;

  case 386: /* limit_block: limit_block limit_config  */
#line 2550 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10698 "parser_bison.c"
    break;

  case 387: /* limit_block: limit_block comment_spec  */
#line 2554 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10710 "parser_bison.c"
    break;

  case 388: /* secmark_block: %empty  */
#line 2563 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10716 "parser_bison.c"
    break;

  case 391: /* secmark_block: secmark_block secmark_config  */
#line 2567 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10724 "parser_bison.c"
    break;

  case 392: /* secmark_block: secmark_block comment_spec  */
#line 2571 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10736 "parser_bison.c"
    break;

  case 393: /* synproxy_block: %empty  */
#line 2580 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10742 "parser_bison.c"
    break;

  case 396: /* synproxy_block: synproxy_block synproxy_config  */
#line 2584 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10750 "parser_bison.c"
    break;

  case 397: /* synproxy_block: synproxy_block comment_spec  */
#line 2588 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10762 "parser_bison.c"
    break;

  case 398: /* type_identifier: "string"  */
#line 2597 "parser_bison.y"
                                        { (yyval.string) = (yyvsp[0].string); }
#line 10768 "parser_bison.c"
    break;

  case 399: /* type_identifier: "mark"  */
#line 2598 "parser_bison.y"
                                        { (yyval.string) = xstrdup("mark"); }
#line 10774 "parser_bison.c"
    break;

  case 400: /* type_identifier: "dscp"  */
#line 2599 "parser_bison.y"
                                        { (yyval.string) = xstrdup("dscp"); }
#line 10780 "parser_bison.c"
    break;

  case 401: /* type_identifier: "ecn"  */
#line 2600 "parser_bison.y"
                                        { (yyval.string) = xstrdup("ecn"); }
#line 10786 "parser_bison.c"
    break;

  case 402: /* type_identifier: "classid"  */
#line 2601 "parser_bison.y"
                                        { (yyval.string) = xstrdup("classid"); }
#line 10792 "parser_bison.c"
    break;

  case 403: /* hook_spec: "type" close_scope_type "string" "hook" "string" dev_spec prio_spec  */
#line 2605 "parser_bison.y"
                        {
				const char *chain_type = chain_type_name_lookup((yyvsp[-4].string));

				if (chain_type == NULL) {
					erec_queue(error(&(yylsp[-4]), "unknown chain type"),
						   state->msgs);
					xfree((yyvsp[-4].string));
					YYERROR;
				}
				(yyvsp[-7].chain)->type.loc = (yylsp[-4]);
				(yyvsp[-7].chain)->type.str = xstrdup(chain_type);
				xfree((yyvsp[-4].string));

				(yyvsp[-7].chain)->loc = (yyloc);
				(yyvsp[-7].chain)->hook.loc = (yylsp[-2]);
				(yyvsp[-7].chain)->hook.name = chain_hookname_lookup((yyvsp[-2].string));
				if ((yyvsp[-7].chain)->hook.name == NULL) {
					erec_queue(error(&(yylsp[-2]), "unknown chain hook"),
						   state->msgs);
					xfree((yyvsp[-2].string));
					YYERROR;
				}
				xfree((yyvsp[-2].string));

				(yyvsp[-7].chain)->dev_expr	= (yyvsp[-1].expr);
				(yyvsp[-7].chain)->priority	= (yyvsp[0].prio_spec);
				(yyvsp[-7].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
#line 10825 "parser_bison.c"
    break;

  case 404: /* prio_spec: "priority" extended_prio_spec  */
#line 2636 "parser_bison.y"
                        {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 10834 "parser_bison.c"
    break;

  case 405: /* extended_prio_name: "out"  */
#line 2643 "parser_bison.y"
                        {
				(yyval.string) = strdup("out");
			}
#line 10842 "parser_bison.c"
    break;

  case 407: /* extended_prio_spec: int_num  */
#line 2650 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 10856 "parser_bison.c"
    break;

  case 408: /* extended_prio_spec: variable_expr  */
#line 2660 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 10867 "parser_bison.c"
    break;

  case 409: /* extended_prio_spec: extended_prio_name  */
#line 2667 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 10882 "parser_bison.c"
    break;

  case 410: /* extended_prio_spec: extended_prio_name "+" "number"  */
#line 2678 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				char str[NFT_NAME_MAXLEN];
				snprintf(str, sizeof(str), "%s + %" PRIu64, (yyvsp[-2].string), (yyvsp[0].val));
				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen(str) * BITS_PER_BYTE,
								str);
				xfree((yyvsp[-2].string));
				(yyval.prio_spec) = spec;
			}
#line 10899 "parser_bison.c"
    break;

  case 411: /* extended_prio_spec: extended_prio_name "-" "number"  */
#line 2691 "parser_bison.y"
                        {
				struct prio_spec spec = {0};
				char str[NFT_NAME_MAXLEN];

				snprintf(str, sizeof(str), "%s - %" PRIu64, (yyvsp[-2].string), (yyvsp[0].val));
				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen(str) * BITS_PER_BYTE,
								str);
				xfree((yyvsp[-2].string));
				(yyval.prio_spec) = spec;
			}
#line 10916 "parser_bison.c"
    break;

  case 412: /* int_num: "number"  */
#line 2705 "parser_bison.y"
                                                        { (yyval.val32) = (yyvsp[0].val); }
#line 10922 "parser_bison.c"
    break;

  case 413: /* int_num: "-" "number"  */
#line 2706 "parser_bison.y"
                                                        { (yyval.val32) = -(yyvsp[0].val); }
#line 10928 "parser_bison.c"
    break;

  case 414: /* dev_spec: "device" string  */
#line 2710 "parser_bison.y"
                        {
				struct expr *expr = ifname_expr_alloc(&(yyloc), state->msgs, (yyvsp[0].string));

				if (!expr)
					YYERROR;

				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 10943 "parser_bison.c"
    break;

  case 415: /* dev_spec: "device" variable_expr  */
#line 2721 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10953 "parser_bison.c"
    break;

  case 416: /* dev_spec: "devices" '=' flowtable_expr  */
#line 2727 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10961 "parser_bison.c"
    break;

  case 417: /* dev_spec: %empty  */
#line 2730 "parser_bison.y"
                                                        { (yyval.expr) = NULL; }
#line 10967 "parser_bison.c"
    break;

  case 418: /* flags_spec: "flags" "offload"  */
#line 2734 "parser_bison.y"
                        {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 10975 "parser_bison.c"
    break;

  case 419: /* policy_spec: "policy" policy_expr close_scope_policy  */
#line 2740 "parser_bison.y"
                        {
				if ((yyvsp[-3].chain)->policy) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					expr_free((yyvsp[-1].expr));
					YYERROR;
				}
				(yyvsp[-3].chain)->policy		= (yyvsp[-1].expr);
				(yyvsp[-3].chain)->policy->location	= (yyloc);
			}
#line 10990 "parser_bison.c"
    break;

  case 420: /* policy_expr: variable_expr  */
#line 2753 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10999 "parser_bison.c"
    break;

  case 421: /* policy_expr: chain_policy  */
#line 2758 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 11010 "parser_bison.c"
    break;

  case 422: /* chain_policy: "accept"  */
#line 2766 "parser_bison.y"
                                                { (yyval.val32) = NF_ACCEPT; }
#line 11016 "parser_bison.c"
    break;

  case 423: /* chain_policy: "drop"  */
#line 2767 "parser_bison.y"
                                                { (yyval.val32) = NF_DROP;   }
#line 11022 "parser_bison.c"
    break;

  case 425: /* identifier: "last"  */
#line 2771 "parser_bison.y"
                                                { (yyval.string) = xstrdup("last"); }
#line 11028 "parser_bison.c"
    break;

  case 429: /* time_spec: "string"  */
#line 2780 "parser_bison.y"
                        {
				struct error_record *erec;
				uint64_t res;

				erec = time_parse(&(yylsp[0]), (yyvsp[0].string), &res);
				xfree((yyvsp[0].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.val) = res;
			}
#line 11045 "parser_bison.c"
    break;

  case 431: /* time_spec_or_num_s: time_spec  */
#line 2796 "parser_bison.y"
                                          { (yyval.val) = (yyvsp[0].val) / 1000u; }
#line 11051 "parser_bison.c"
    break;

  case 432: /* family_spec: %empty  */
#line 2799 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV4; }
#line 11057 "parser_bison.c"
    break;

  case 434: /* family_spec_explicit: "ip" close_scope_ip  */
#line 2803 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV4; }
#line 11063 "parser_bison.c"
    break;

  case 435: /* family_spec_explicit: "ip6" close_scope_ip6  */
#line 2804 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV6; }
#line 11069 "parser_bison.c"
    break;

  case 436: /* family_spec_explicit: "inet"  */
#line 2805 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_INET; }
#line 11075 "parser_bison.c"
    break;

  case 437: /* family_spec_explicit: "arp" close_scope_arp  */
#line 2806 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_ARP; }
#line 11081 "parser_bison.c"
    break;

  case 438: /* family_spec_explicit: "bridge"  */
#line 2807 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_BRIDGE; }
#line 11087 "parser_bison.c"
    break;

  case 439: /* family_spec_explicit: "netdev"  */
#line 2808 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_NETDEV; }
#line 11093 "parser_bison.c"
    break;

  case 440: /* table_spec: family_spec identifier  */
#line 2812 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 11104 "parser_bison.c"
    break;

  case 441: /* tableid_spec: family_spec "handle" "number"  */
#line 2821 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 11115 "parser_bison.c"
    break;

  case 442: /* chain_spec: table_spec identifier  */
#line 2830 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 11125 "parser_bison.c"
    break;

  case 443: /* chainid_spec: table_spec "handle" "number"  */
#line 2838 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 11135 "parser_bison.c"
    break;

  case 444: /* chain_identifier: identifier  */
#line 2846 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 11145 "parser_bison.c"
    break;

  case 445: /* set_spec: table_spec identifier  */
#line 2854 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 11155 "parser_bison.c"
    break;

  case 446: /* setid_spec: table_spec "handle" "number"  */
#line 2862 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 11165 "parser_bison.c"
    break;

  case 447: /* set_identifier: identifier  */
#line 2870 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 11175 "parser_bison.c"
    break;

  case 448: /* flowtable_spec: table_spec identifier  */
#line 2878 "parser_bison.y"
                        {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 11185 "parser_bison.c"
    break;

  case 449: /* flowtableid_spec: table_spec "handle" "number"  */
#line 2886 "parser_bison.y"
                        {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 11195 "parser_bison.c"
    break;

  case 450: /* flowtable_identifier: identifier  */
#line 2894 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 11205 "parser_bison.c"
    break;

  case 451: /* obj_spec: table_spec identifier  */
#line 2902 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 11215 "parser_bison.c"
    break;

  case 452: /* objid_spec: table_spec "handle" "number"  */
#line 2910 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 11225 "parser_bison.c"
    break;

  case 453: /* obj_identifier: identifier  */
#line 2918 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 11235 "parser_bison.c"
    break;

  case 454: /* handle_spec: "handle" "number"  */
#line 2926 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 11245 "parser_bison.c"
    break;

  case 455: /* position_spec: "position" "number"  */
#line 2934 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 11255 "parser_bison.c"
    break;

  case 456: /* index_spec: "index" "number"  */
#line 2942 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 11265 "parser_bison.c"
    break;

  case 457: /* rule_position: chain_spec  */
#line 2950 "parser_bison.y"
                        {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 11273 "parser_bison.c"
    break;

  case 458: /* rule_position: chain_spec position_spec  */
#line 2954 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11282 "parser_bison.c"
    break;

  case 459: /* rule_position: chain_spec handle_spec  */
#line 2959 "parser_bison.y"
                        {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11294 "parser_bison.c"
    break;

  case 460: /* rule_position: chain_spec index_spec  */
#line 2967 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11303 "parser_bison.c"
    break;

  case 461: /* ruleid_spec: chain_spec handle_spec  */
#line 2974 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11312 "parser_bison.c"
    break;

  case 462: /* comment_spec: "comment" string  */
#line 2981 "parser_bison.y"
                        {
				if (strlen((yyvsp[0].string)) > NFTNL_UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed",
							 NFTNL_UDATA_COMMENT_MAXLEN),
						   state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 11327 "parser_bison.c"
    break;

  case 463: /* ruleset_spec: %empty  */
#line 2994 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 11336 "parser_bison.c"
    break;

  case 464: /* ruleset_spec: family_spec_explicit  */
#line 2999 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 11345 "parser_bison.c"
    break;

  case 465: /* rule: rule_alloc  */
#line 3006 "parser_bison.y"
                        {
				(yyval.rule)->comment = NULL;
			}
#line 11353 "parser_bison.c"
    break;

  case 466: /* rule: rule_alloc comment_spec  */
#line 3010 "parser_bison.y"
                        {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 11361 "parser_bison.c"
    break;

  case 467: /* rule_alloc: stmt_list  */
#line 3016 "parser_bison.y"
                        {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 11375 "parser_bison.c"
    break;

  case 468: /* stmt_list: stmt  */
#line 3028 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 11385 "parser_bison.c"
    break;

  case 469: /* stmt_list: stmt_list stmt  */
#line 3034 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 11394 "parser_bison.c"
    break;

  case 470: /* stateful_stmt_list: stateful_stmt  */
#line 3041 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 11404 "parser_bison.c"
    break;

  case 471: /* stateful_stmt_list: stateful_stmt_list stateful_stmt  */
#line 3047 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 11413 "parser_bison.c"
    break;

  case 499: /* xt_stmt: "xt" "string" string  */
#line 3085 "parser_bison.y"
                        {
				(yyval.stmt) = NULL;
				xfree((yyvsp[-1].string));
				xfree((yyvsp[0].string));
				erec_queue(error(&(yyloc), "unsupported xtables compat expression, use iptables-nft with this ruleset"),
					   state->msgs);
				YYERROR;
			}
#line 11426 "parser_bison.c"
    break;

  case 500: /* chain_stmt_type: "jump"  */
#line 3095 "parser_bison.y"
                                        { (yyval.val) = NFT_JUMP; }
#line 11432 "parser_bison.c"
    break;

  case 501: /* chain_stmt_type: "goto"  */
#line 3096 "parser_bison.y"
                                        { (yyval.val) = NFT_GOTO; }
#line 11438 "parser_bison.c"
    break;

  case 502: /* chain_stmt: chain_stmt_type chain_block_alloc '{' subchain_block '}'  */
#line 3100 "parser_bison.y"
                        {
				(yyvsp[-3].chain)->location = (yylsp[-3]);
				close_scope(state);
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				(yyval.stmt) = chain_stmt_alloc(&(yyloc), (yyvsp[-1].chain), (yyvsp[-4].val));
			}
#line 11449 "parser_bison.c"
    break;

  case 503: /* verdict_stmt: verdict_expr  */
#line 3109 "parser_bison.y"
                        {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 11457 "parser_bison.c"
    break;

  case 504: /* verdict_stmt: verdict_map_stmt  */
#line 3113 "parser_bison.y"
                        {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 11465 "parser_bison.c"
    break;

  case 505: /* verdict_map_stmt: concat_expr "vmap" verdict_map_expr  */
#line 3119 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11473 "parser_bison.c"
    break;

  case 506: /* verdict_map_expr: '{' verdict_map_list_expr '}'  */
#line 3125 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11482 "parser_bison.c"
    break;

  case 508: /* verdict_map_list_expr: verdict_map_list_member_expr  */
#line 3133 "parser_bison.y"
                        {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11491 "parser_bison.c"
    break;

  case 509: /* verdict_map_list_expr: verdict_map_list_expr "comma" verdict_map_list_member_expr  */
#line 3138 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11500 "parser_bison.c"
    break;

  case 511: /* verdict_map_list_member_expr: opt_newline set_elem_expr "colon" verdict_expr opt_newline  */
#line 3146 "parser_bison.y"
                        {
				(yyval.expr) = mapping_expr_alloc(&(yylsp[-3]), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 11508 "parser_bison.c"
    break;

  case 512: /* connlimit_stmt: "ct" "count" "number" close_scope_ct  */
#line 3152 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 11517 "parser_bison.c"
    break;

  case 513: /* connlimit_stmt: "ct" "count" "over" "number" close_scope_ct  */
#line 3157 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 11527 "parser_bison.c"
    break;

  case 516: /* counter_stmt_alloc: "counter"  */
#line 3168 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 11535 "parser_bison.c"
    break;

  case 517: /* counter_stmt_alloc: "counter" "name" stmt_expr  */
#line 3172 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 11545 "parser_bison.c"
    break;

  case 518: /* counter_args: counter_arg  */
#line 3180 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 11553 "parser_bison.c"
    break;

  case 520: /* counter_arg: "packets" "number"  */
#line 3187 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 11561 "parser_bison.c"
    break;

  case 521: /* counter_arg: "bytes" "number"  */
#line 3191 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 11569 "parser_bison.c"
    break;

  case 522: /* last_stmt: "last"  */
#line 3197 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
			}
#line 11577 "parser_bison.c"
    break;

  case 523: /* last_stmt: "last" "used" "never"  */
#line 3201 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
			}
#line 11585 "parser_bison.c"
    break;

  case 524: /* last_stmt: "last" "used" time_spec  */
#line 3205 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
				(yyval.stmt)->last.used = (yyvsp[0].val);
				(yyval.stmt)->last.set = true;
			}
#line 11595 "parser_bison.c"
    break;

  case 527: /* log_stmt_alloc: "log"  */
#line 3217 "parser_bison.y"
                        {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 11603 "parser_bison.c"
    break;

  case 528: /* log_args: log_arg  */
#line 3223 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 11611 "parser_bison.c"
    break;

  case 530: /* log_arg: "prefix" string  */
#line 3230 "parser_bison.y"
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
				if (!strchr((yyvsp[0].string), '$')) {
					expr = constant_expr_alloc(&(yyloc), &string_type,
								   BYTEORDER_HOST_ENDIAN,
								   (strlen((yyvsp[0].string)) + 1) * BITS_PER_BYTE, (yyvsp[0].string));
					xfree((yyvsp[0].string));
					(yyvsp[-2].stmt)->log.prefix = expr;
					(yyvsp[-2].stmt)->log.flags |= STMT_LOG_PREFIX;
					break;
				}

				/* Parse variables in log prefix string using a
				 * state machine parser with two states. This
				 * parser creates list of expressions composed
				 * of constant and variable expressions.
				 */
				expr = compound_expr_alloc(&(yyloc), EXPR_LIST);

				start = (char *)(yyvsp[0].string);

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
						item = constant_expr_alloc(&(yyloc), &string_type,
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
								erec_queue(error(&(yylsp[0]), "unknown identifier '%s'; "
										 "did you mean identifier ‘%s’?",
										 start, sym->identifier),
									   state->msgs);
							} else {
								erec_queue(error(&(yylsp[0]), "unknown identifier '%s'",
										 start),
									   state->msgs);
							}
							expr_free(expr);
							xfree((yyvsp[0].string));
							YYERROR;
						}
						item = variable_expr_alloc(&(yyloc), scope, sym);
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

				xfree((yyvsp[0].string));
				(yyvsp[-2].stmt)->log.prefix	 = expr;
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 11740 "parser_bison.c"
    break;

  case 531: /* log_arg: "group" "number"  */
#line 3355 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 11749 "parser_bison.c"
    break;

  case 532: /* log_arg: "snaplen" "number"  */
#line 3360 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 11758 "parser_bison.c"
    break;

  case 533: /* log_arg: "queue-threshold" "number"  */
#line 3365 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 11767 "parser_bison.c"
    break;

  case 534: /* log_arg: "level" level_type  */
#line 3370 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 11776 "parser_bison.c"
    break;

  case 535: /* log_arg: "flags" log_flags  */
#line 3375 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 11784 "parser_bison.c"
    break;

  case 536: /* level_type: string  */
#line 3381 "parser_bison.y"
                        {
				if (!strcmp("emerg", (yyvsp[0].string)))
					(yyval.val) = NFT_LOGLEVEL_EMERG;
				else if (!strcmp("alert", (yyvsp[0].string)))
					(yyval.val) = NFT_LOGLEVEL_ALERT;
				else if (!strcmp("crit", (yyvsp[0].string)))
					(yyval.val) = NFT_LOGLEVEL_CRIT;
				else if (!strcmp("err", (yyvsp[0].string)))
					(yyval.val) = NFT_LOGLEVEL_ERR;
				else if (!strcmp("warn", (yyvsp[0].string)))
					(yyval.val) = NFT_LOGLEVEL_WARNING;
				else if (!strcmp("notice", (yyvsp[0].string)))
					(yyval.val) = NFT_LOGLEVEL_NOTICE;
				else if (!strcmp("info", (yyvsp[0].string)))
					(yyval.val) = NFT_LOGLEVEL_INFO;
				else if (!strcmp("debug", (yyvsp[0].string)))
					(yyval.val) = NFT_LOGLEVEL_DEBUG;
				else if (!strcmp("audit", (yyvsp[0].string)))
					(yyval.val) = NFT_LOGLEVEL_AUDIT;
				else {
					erec_queue(error(&(yylsp[0]), "invalid log level"),
						   state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}
				xfree((yyvsp[0].string));
			}
#line 11816 "parser_bison.c"
    break;

  case 537: /* log_flags: "tcp" log_flags_tcp close_scope_tcp  */
#line 3411 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-1].val);
			}
#line 11824 "parser_bison.c"
    break;

  case 538: /* log_flags: "ip" "options" close_scope_ip  */
#line 3415 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 11832 "parser_bison.c"
    break;

  case 539: /* log_flags: "skuid"  */
#line 3419 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_UID;
			}
#line 11840 "parser_bison.c"
    break;

  case 540: /* log_flags: "ether" close_scope_eth  */
#line 3423 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 11848 "parser_bison.c"
    break;

  case 541: /* log_flags: "all"  */
#line 3427 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_MASK;
			}
#line 11856 "parser_bison.c"
    break;

  case 542: /* log_flags_tcp: log_flags_tcp "comma" log_flag_tcp  */
#line 3433 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 11864 "parser_bison.c"
    break;

  case 544: /* log_flag_tcp: "seq"  */
#line 3440 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 11872 "parser_bison.c"
    break;

  case 545: /* log_flag_tcp: "options"  */
#line 3444 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 11880 "parser_bison.c"
    break;

  case 546: /* limit_stmt: "limit" "rate" limit_mode limit_rate_pkts limit_burst_pkts close_scope_limit  */
#line 3450 "parser_bison.y"
                        {
				if ((yyvsp[-1].val) == 0) {
					erec_queue(error(&(yylsp[-1]), "packet limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-2].limit_rate).rate;
				(yyval.stmt)->limit.unit	= (yyvsp[-2].limit_rate).unit;
				(yyval.stmt)->limit.burst	= (yyvsp[-1].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-3].val);
			}
#line 11898 "parser_bison.c"
    break;

  case 547: /* limit_stmt: "limit" "rate" limit_mode limit_rate_bytes limit_burst_bytes close_scope_limit  */
#line 3464 "parser_bison.y"
                        {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-2].limit_rate).rate;
				(yyval.stmt)->limit.unit	= (yyvsp[-2].limit_rate).unit;
				(yyval.stmt)->limit.burst	= (yyvsp[-1].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKT_BYTES;
				(yyval.stmt)->limit.flags = (yyvsp[-3].val);
			}
#line 11911 "parser_bison.c"
    break;

  case 548: /* limit_stmt: "limit" "name" stmt_expr close_scope_limit  */
#line 3473 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 11921 "parser_bison.c"
    break;

  case 549: /* quota_mode: "over"  */
#line 3480 "parser_bison.y"
                                                { (yyval.val) = NFT_QUOTA_F_INV; }
#line 11927 "parser_bison.c"
    break;

  case 550: /* quota_mode: "until"  */
#line 3481 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11933 "parser_bison.c"
    break;

  case 551: /* quota_mode: %empty  */
#line 3482 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11939 "parser_bison.c"
    break;

  case 552: /* quota_unit: "bytes"  */
#line 3485 "parser_bison.y"
                                                { (yyval.string) = xstrdup("bytes"); }
#line 11945 "parser_bison.c"
    break;

  case 553: /* quota_unit: "string"  */
#line 3486 "parser_bison.y"
                                                { (yyval.string) = (yyvsp[0].string); }
#line 11951 "parser_bison.c"
    break;

  case 554: /* quota_used: %empty  */
#line 3489 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11957 "parser_bison.c"
    break;

  case 555: /* quota_used: "used" "number" quota_unit  */
#line 3491 "parser_bison.y"
                        {
				struct error_record *erec;
				uint64_t rate;

				erec = data_unit_parse(&(yyloc), (yyvsp[0].string), &rate);
				xfree((yyvsp[0].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[-1].val) * rate;
			}
#line 11974 "parser_bison.c"
    break;

  case 556: /* quota_stmt: "quota" quota_mode "number" quota_unit quota_used close_scope_quota  */
#line 3506 "parser_bison.y"
                        {
				struct error_record *erec;
				uint64_t rate;

				erec = data_unit_parse(&(yyloc), (yyvsp[-2].string), &rate);
				xfree((yyvsp[-2].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.stmt) = quota_stmt_alloc(&(yyloc));
				(yyval.stmt)->quota.bytes	= (yyvsp[-3].val) * rate;
				(yyval.stmt)->quota.used = (yyvsp[-1].val);
				(yyval.stmt)->quota.flags	= (yyvsp[-4].val);
			}
#line 11994 "parser_bison.c"
    break;

  case 557: /* quota_stmt: "quota" "name" stmt_expr close_scope_quota  */
#line 3522 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 12004 "parser_bison.c"
    break;

  case 558: /* limit_mode: "over"  */
#line 3529 "parser_bison.y"
                                                                { (yyval.val) = NFT_LIMIT_F_INV; }
#line 12010 "parser_bison.c"
    break;

  case 559: /* limit_mode: "until"  */
#line 3530 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 12016 "parser_bison.c"
    break;

  case 560: /* limit_mode: %empty  */
#line 3531 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 12022 "parser_bison.c"
    break;

  case 561: /* limit_burst_pkts: %empty  */
#line 3534 "parser_bison.y"
                                                                { (yyval.val) = 5; }
#line 12028 "parser_bison.c"
    break;

  case 562: /* limit_burst_pkts: "burst" "number" "packets"  */
#line 3535 "parser_bison.y"
                                                                { (yyval.val) = (yyvsp[-1].val); }
#line 12034 "parser_bison.c"
    break;

  case 563: /* limit_rate_pkts: "number" "/" time_unit  */
#line 3539 "parser_bison.y"
                        {
				(yyval.limit_rate).rate = (yyvsp[-2].val);
				(yyval.limit_rate).unit = (yyvsp[0].val);
			}
#line 12043 "parser_bison.c"
    break;

  case 564: /* limit_burst_bytes: %empty  */
#line 3545 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 12049 "parser_bison.c"
    break;

  case 565: /* limit_burst_bytes: "burst" limit_bytes  */
#line 3546 "parser_bison.y"
                                                                { (yyval.val) = (yyvsp[0].val); }
#line 12055 "parser_bison.c"
    break;

  case 566: /* limit_rate_bytes: "number" "string"  */
#line 3550 "parser_bison.y"
                        {
				struct error_record *erec;
				uint64_t rate, unit;

				erec = rate_parse(&(yyloc), (yyvsp[0].string), &rate, &unit);
				xfree((yyvsp[0].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.limit_rate).rate = rate * (yyvsp[-1].val);
				(yyval.limit_rate).unit = unit;
			}
#line 12073 "parser_bison.c"
    break;

  case 567: /* limit_rate_bytes: limit_bytes "/" time_unit  */
#line 3564 "parser_bison.y"
                        {
				(yyval.limit_rate).rate = (yyvsp[-2].val);
				(yyval.limit_rate).unit = (yyvsp[0].val);
			}
#line 12082 "parser_bison.c"
    break;

  case 568: /* limit_bytes: "number" "bytes"  */
#line 3570 "parser_bison.y"
                                                        { (yyval.val) = (yyvsp[-1].val); }
#line 12088 "parser_bison.c"
    break;

  case 569: /* limit_bytes: "number" "string"  */
#line 3572 "parser_bison.y"
                        {
				struct error_record *erec;
				uint64_t rate;

				erec = data_unit_parse(&(yyloc), (yyvsp[0].string), &rate);
				xfree((yyvsp[0].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[-1].val) * rate;
			}
#line 12105 "parser_bison.c"
    break;

  case 570: /* time_unit: "second"  */
#line 3586 "parser_bison.y"
                                                { (yyval.val) = 1ULL; }
#line 12111 "parser_bison.c"
    break;

  case 571: /* time_unit: "minute"  */
#line 3587 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60; }
#line 12117 "parser_bison.c"
    break;

  case 572: /* time_unit: "hour"  */
#line 3588 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60; }
#line 12123 "parser_bison.c"
    break;

  case 573: /* time_unit: "day"  */
#line 3589 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 12129 "parser_bison.c"
    break;

  case 574: /* time_unit: "week"  */
#line 3590 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 12135 "parser_bison.c"
    break;

  case 576: /* reject_stmt_alloc: "reject"  */
#line 3597 "parser_bison.y"
                        {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 12143 "parser_bison.c"
    break;

  case 577: /* reject_with_expr: "string"  */
#line 3603 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state), (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 12153 "parser_bison.c"
    break;

  case 578: /* reject_with_expr: integer_expr  */
#line 3608 "parser_bison.y"
                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12159 "parser_bison.c"
    break;

  case 579: /* reject_opts: %empty  */
#line 3612 "parser_bison.y"
                        {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 12168 "parser_bison.c"
    break;

  case 580: /* reject_opts: "with" "icmp" "type" reject_with_expr close_scope_type close_scope_icmp  */
#line 3617 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-6].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-6].stmt)->reject.expr = (yyvsp[-2].expr);
				datatype_set((yyvsp[-6].stmt)->reject.expr, &icmp_code_type);
			}
#line 12179 "parser_bison.c"
    break;

  case 581: /* reject_opts: "with" "icmp" reject_with_expr  */
#line 3624 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmp_code_type);
			}
#line 12190 "parser_bison.c"
    break;

  case 582: /* reject_opts: "with" "icmpv6" "type" reject_with_expr close_scope_type close_scope_icmp  */
#line 3631 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-6].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-6].stmt)->reject.expr = (yyvsp[-2].expr);
				datatype_set((yyvsp[-6].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 12201 "parser_bison.c"
    break;

  case 583: /* reject_opts: "with" "icmpv6" reject_with_expr  */
#line 3638 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 12212 "parser_bison.c"
    break;

  case 584: /* reject_opts: "with" "icmpx" "type" reject_with_expr close_scope_type  */
#line 3645 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-5].stmt)->reject.expr = (yyvsp[-1].expr);
				datatype_set((yyvsp[-5].stmt)->reject.expr, &icmpx_code_type);
			}
#line 12222 "parser_bison.c"
    break;

  case 585: /* reject_opts: "with" "icmpx" reject_with_expr  */
#line 3651 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpx_code_type);
			}
#line 12232 "parser_bison.c"
    break;

  case 586: /* reject_opts: "with" "tcp" close_scope_tcp "reset" close_scope_reset  */
#line 3657 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 12240 "parser_bison.c"
    break;

  case 588: /* nat_stmt_alloc: "snat"  */
#line 3665 "parser_bison.y"
                                        { (yyval.stmt) = nat_stmt_alloc(&(yyloc), __NFT_NAT_SNAT); }
#line 12246 "parser_bison.c"
    break;

  case 589: /* nat_stmt_alloc: "dnat"  */
#line 3666 "parser_bison.y"
                                        { (yyval.stmt) = nat_stmt_alloc(&(yyloc), __NFT_NAT_DNAT); }
#line 12252 "parser_bison.c"
    break;

  case 590: /* tproxy_stmt: "tproxy" "to" stmt_expr  */
#line 3670 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 12262 "parser_bison.c"
    break;

  case 591: /* tproxy_stmt: "tproxy" nf_key_proto "to" stmt_expr  */
#line 3676 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 12272 "parser_bison.c"
    break;

  case 592: /* tproxy_stmt: "tproxy" "to" "colon" stmt_expr  */
#line 3682 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12282 "parser_bison.c"
    break;

  case 593: /* tproxy_stmt: "tproxy" "to" stmt_expr "colon" stmt_expr  */
#line 3688 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12293 "parser_bison.c"
    break;

  case 594: /* tproxy_stmt: "tproxy" nf_key_proto "to" stmt_expr "colon" stmt_expr  */
#line 3695 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12304 "parser_bison.c"
    break;

  case 595: /* tproxy_stmt: "tproxy" nf_key_proto "to" "colon" stmt_expr  */
#line 3702 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12314 "parser_bison.c"
    break;

  case 598: /* synproxy_stmt_alloc: "synproxy"  */
#line 3714 "parser_bison.y"
                        {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 12322 "parser_bison.c"
    break;

  case 599: /* synproxy_stmt_alloc: "synproxy" "name" stmt_expr  */
#line 3718 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 12332 "parser_bison.c"
    break;

  case 600: /* synproxy_args: synproxy_arg  */
#line 3726 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 12340 "parser_bison.c"
    break;

  case 602: /* synproxy_arg: "mss" "number"  */
#line 3733 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 12349 "parser_bison.c"
    break;

  case 603: /* synproxy_arg: "wscale" "number"  */
#line 3738 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 12358 "parser_bison.c"
    break;

  case 604: /* synproxy_arg: "timestamp"  */
#line 3743 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 12366 "parser_bison.c"
    break;

  case 605: /* synproxy_arg: "sack-permitted"  */
#line 3747 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 12374 "parser_bison.c"
    break;

  case 606: /* synproxy_config: "mss" "number" "wscale" "number" synproxy_ts synproxy_sack  */
#line 3753 "parser_bison.y"
                        {
				struct synproxy *synproxy;
				uint32_t flags = 0;

				synproxy = &(yyvsp[-6].obj)->synproxy;
				synproxy->mss = (yyvsp[-4].val);
				flags |= NF_SYNPROXY_OPT_MSS;
				synproxy->wscale = (yyvsp[-2].val);
				flags |= NF_SYNPROXY_OPT_WSCALE;
				if ((yyvsp[-1].val))
					flags |= (yyvsp[-1].val);
				if ((yyvsp[0].val))
					flags |= (yyvsp[0].val);
				synproxy->flags = flags;
			}
#line 12394 "parser_bison.c"
    break;

  case 607: /* synproxy_config: "mss" "number" stmt_separator "wscale" "number" stmt_separator synproxy_ts synproxy_sack  */
#line 3769 "parser_bison.y"
                        {
				struct synproxy *synproxy;
				uint32_t flags = 0;

				synproxy = &(yyvsp[-8].obj)->synproxy;
				synproxy->mss = (yyvsp[-6].val);
				flags |= NF_SYNPROXY_OPT_MSS;
				synproxy->wscale = (yyvsp[-3].val);
				flags |= NF_SYNPROXY_OPT_WSCALE;
				if ((yyvsp[-1].val))
					flags |= (yyvsp[-1].val);
				if ((yyvsp[0].val))
					flags |= (yyvsp[0].val);
				synproxy->flags = flags;
			}
#line 12414 "parser_bison.c"
    break;

  case 608: /* synproxy_obj: %empty  */
#line 3787 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 12423 "parser_bison.c"
    break;

  case 609: /* synproxy_ts: %empty  */
#line 3793 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 12429 "parser_bison.c"
    break;

  case 610: /* synproxy_ts: "timestamp"  */
#line 3795 "parser_bison.y"
                        {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 12437 "parser_bison.c"
    break;

  case 611: /* synproxy_sack: %empty  */
#line 3800 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 12443 "parser_bison.c"
    break;

  case 612: /* synproxy_sack: "sack-permitted"  */
#line 3802 "parser_bison.y"
                        {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 12451 "parser_bison.c"
    break;

  case 613: /* primary_stmt_expr: symbol_expr  */
#line 3807 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12457 "parser_bison.c"
    break;

  case 614: /* primary_stmt_expr: integer_expr  */
#line 3808 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12463 "parser_bison.c"
    break;

  case 615: /* primary_stmt_expr: boolean_expr  */
#line 3809 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12469 "parser_bison.c"
    break;

  case 616: /* primary_stmt_expr: meta_expr  */
#line 3810 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12475 "parser_bison.c"
    break;

  case 617: /* primary_stmt_expr: rt_expr  */
#line 3811 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12481 "parser_bison.c"
    break;

  case 618: /* primary_stmt_expr: ct_expr  */
#line 3812 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12487 "parser_bison.c"
    break;

  case 619: /* primary_stmt_expr: numgen_expr  */
#line 3813 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12493 "parser_bison.c"
    break;

  case 620: /* primary_stmt_expr: hash_expr  */
#line 3814 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12499 "parser_bison.c"
    break;

  case 621: /* primary_stmt_expr: payload_expr  */
#line 3815 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12505 "parser_bison.c"
    break;

  case 622: /* primary_stmt_expr: keyword_expr  */
#line 3816 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12511 "parser_bison.c"
    break;

  case 623: /* primary_stmt_expr: socket_expr  */
#line 3817 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12517 "parser_bison.c"
    break;

  case 624: /* primary_stmt_expr: osf_expr  */
#line 3818 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12523 "parser_bison.c"
    break;

  case 625: /* primary_stmt_expr: '(' basic_stmt_expr ')'  */
#line 3819 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 12529 "parser_bison.c"
    break;

  case 627: /* shift_stmt_expr: shift_stmt_expr "<<" primary_stmt_expr  */
#line 3824 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12537 "parser_bison.c"
    break;

  case 628: /* shift_stmt_expr: shift_stmt_expr ">>" primary_stmt_expr  */
#line 3828 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12545 "parser_bison.c"
    break;

  case 630: /* and_stmt_expr: and_stmt_expr "&" shift_stmt_expr  */
#line 3835 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12553 "parser_bison.c"
    break;

  case 632: /* exclusive_or_stmt_expr: exclusive_or_stmt_expr "^" and_stmt_expr  */
#line 3842 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12561 "parser_bison.c"
    break;

  case 634: /* inclusive_or_stmt_expr: inclusive_or_stmt_expr '|' exclusive_or_stmt_expr  */
#line 3849 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12569 "parser_bison.c"
    break;

  case 637: /* concat_stmt_expr: concat_stmt_expr "." primary_stmt_expr  */
#line 3859 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 12582 "parser_bison.c"
    break;

  case 640: /* map_stmt_expr: concat_stmt_expr "map" map_stmt_expr_set  */
#line 3874 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12590 "parser_bison.c"
    break;

  case 641: /* map_stmt_expr: concat_stmt_expr  */
#line 3877 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 12596 "parser_bison.c"
    break;

  case 642: /* prefix_stmt_expr: basic_stmt_expr "/" "number"  */
#line 3881 "parser_bison.y"
                        {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 12604 "parser_bison.c"
    break;

  case 643: /* range_stmt_expr: basic_stmt_expr "-" basic_stmt_expr  */
#line 3887 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12612 "parser_bison.c"
    break;

  case 649: /* nat_stmt_args: stmt_expr  */
#line 3902 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12620 "parser_bison.c"
    break;

  case 650: /* nat_stmt_args: "to" stmt_expr  */
#line 3906 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12628 "parser_bison.c"
    break;

  case 651: /* nat_stmt_args: nf_key_proto "to" stmt_expr  */
#line 3910 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12637 "parser_bison.c"
    break;

  case 652: /* nat_stmt_args: stmt_expr "colon" stmt_expr  */
#line 3915 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12646 "parser_bison.c"
    break;

  case 653: /* nat_stmt_args: "to" stmt_expr "colon" stmt_expr  */
#line 3920 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12655 "parser_bison.c"
    break;

  case 654: /* nat_stmt_args: nf_key_proto "to" stmt_expr "colon" stmt_expr  */
#line 3925 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12665 "parser_bison.c"
    break;

  case 655: /* nat_stmt_args: "colon" stmt_expr  */
#line 3931 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12673 "parser_bison.c"
    break;

  case 656: /* nat_stmt_args: "to" "colon" stmt_expr  */
#line 3935 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12681 "parser_bison.c"
    break;

  case 657: /* nat_stmt_args: nat_stmt_args nf_nat_flags  */
#line 3939 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12689 "parser_bison.c"
    break;

  case 658: /* nat_stmt_args: nf_key_proto "addr" "." "port" "to" stmt_expr  */
#line 3943 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.type_flags = STMT_NAT_F_CONCAT;
			}
#line 12699 "parser_bison.c"
    break;

  case 659: /* nat_stmt_args: nf_key_proto "interval" "to" stmt_expr  */
#line 3949 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12708 "parser_bison.c"
    break;

  case 660: /* nat_stmt_args: "interval" "to" stmt_expr  */
#line 3954 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12716 "parser_bison.c"
    break;

  case 661: /* nat_stmt_args: nf_key_proto "prefix" "to" stmt_expr  */
#line 3958 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-4].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 12728 "parser_bison.c"
    break;

  case 662: /* nat_stmt_args: "prefix" "to" stmt_expr  */
#line 3966 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-3].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 12739 "parser_bison.c"
    break;

  case 665: /* masq_stmt_alloc: "masquerade"  */
#line 3978 "parser_bison.y"
                                                { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 12745 "parser_bison.c"
    break;

  case 666: /* masq_stmt_args: "to" "colon" stmt_expr  */
#line 3982 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12753 "parser_bison.c"
    break;

  case 667: /* masq_stmt_args: "to" "colon" stmt_expr nf_nat_flags  */
#line 3986 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12762 "parser_bison.c"
    break;

  case 668: /* masq_stmt_args: nf_nat_flags  */
#line 3991 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12770 "parser_bison.c"
    break;

  case 671: /* redir_stmt_alloc: "redirect"  */
#line 4000 "parser_bison.y"
                                                { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 12776 "parser_bison.c"
    break;

  case 672: /* redir_stmt_arg: "to" stmt_expr  */
#line 4004 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12784 "parser_bison.c"
    break;

  case 673: /* redir_stmt_arg: "to" "colon" stmt_expr  */
#line 4008 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12792 "parser_bison.c"
    break;

  case 674: /* redir_stmt_arg: nf_nat_flags  */
#line 4012 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12800 "parser_bison.c"
    break;

  case 675: /* redir_stmt_arg: "to" stmt_expr nf_nat_flags  */
#line 4016 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12809 "parser_bison.c"
    break;

  case 676: /* redir_stmt_arg: "to" "colon" stmt_expr nf_nat_flags  */
#line 4021 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12818 "parser_bison.c"
    break;

  case 677: /* dup_stmt: "dup" "to" stmt_expr  */
#line 4028 "parser_bison.y"
                        {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 12827 "parser_bison.c"
    break;

  case 678: /* dup_stmt: "dup" "to" stmt_expr "device" stmt_expr  */
#line 4033 "parser_bison.y"
                        {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 12837 "parser_bison.c"
    break;

  case 679: /* fwd_stmt: "fwd" "to" stmt_expr  */
#line 4041 "parser_bison.y"
                        {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 12846 "parser_bison.c"
    break;

  case 680: /* fwd_stmt: "fwd" nf_key_proto "to" stmt_expr "device" stmt_expr  */
#line 4046 "parser_bison.y"
                        {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 12857 "parser_bison.c"
    break;

  case 682: /* nf_nat_flags: nf_nat_flags "comma" nf_nat_flag  */
#line 4056 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 12865 "parser_bison.c"
    break;

  case 683: /* nf_nat_flag: "random"  */
#line 4061 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 12871 "parser_bison.c"
    break;

  case 684: /* nf_nat_flag: "fully-random"  */
#line 4062 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 12877 "parser_bison.c"
    break;

  case 685: /* nf_nat_flag: "persistent"  */
#line 4063 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 12883 "parser_bison.c"
    break;

  case 687: /* queue_stmt: "queue" "to" queue_stmt_expr close_scope_queue  */
#line 4068 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), 0);
			}
#line 12891 "parser_bison.c"
    break;

  case 688: /* queue_stmt: "queue" "flags" queue_stmt_flags "to" queue_stmt_expr close_scope_queue  */
#line 4072 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 12899 "parser_bison.c"
    break;

  case 689: /* queue_stmt: "queue" "flags" queue_stmt_flags "num" queue_stmt_expr_simple close_scope_queue  */
#line 4076 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 12907 "parser_bison.c"
    break;

  case 692: /* queue_stmt_alloc: "queue"  */
#line 4086 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), NULL, 0);
			}
#line 12915 "parser_bison.c"
    break;

  case 693: /* queue_stmt_args: queue_stmt_arg  */
#line 4092 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 12923 "parser_bison.c"
    break;

  case 695: /* queue_stmt_arg: "num" queue_stmt_expr_simple  */
#line 4099 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 12932 "parser_bison.c"
    break;

  case 696: /* queue_stmt_arg: queue_stmt_flags  */
#line 4104 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 12940 "parser_bison.c"
    break;

  case 701: /* queue_stmt_expr_simple: queue_expr "-" queue_expr  */
#line 4116 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12948 "parser_bison.c"
    break;

  case 707: /* queue_stmt_flags: queue_stmt_flags "comma" queue_stmt_flag  */
#line 4129 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 12956 "parser_bison.c"
    break;

  case 708: /* queue_stmt_flag: "bypass"  */
#line 4134 "parser_bison.y"
                                        { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 12962 "parser_bison.c"
    break;

  case 709: /* queue_stmt_flag: "fanout"  */
#line 4135 "parser_bison.y"
                                        { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 12968 "parser_bison.c"
    break;

  case 712: /* set_elem_expr_stmt_alloc: concat_expr  */
#line 4143 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 12976 "parser_bison.c"
    break;

  case 713: /* set_stmt: "set" set_stmt_op set_elem_expr_stmt set_ref_expr  */
#line 4149 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 12987 "parser_bison.c"
    break;

  case 714: /* set_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt '}'  */
#line 4156 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 12998 "parser_bison.c"
    break;

  case 715: /* set_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt stateful_stmt_list '}'  */
#line 4163 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				list_splice_tail((yyvsp[-1].list), &(yyval.stmt)->set.stmt_list);
				free((yyvsp[-1].list));
			}
#line 13011 "parser_bison.c"
    break;

  case 716: /* set_stmt_op: "add"  */
#line 4173 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 13017 "parser_bison.c"
    break;

  case 717: /* set_stmt_op: "update"  */
#line 4174 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 13023 "parser_bison.c"
    break;

  case 718: /* set_stmt_op: "delete"  */
#line 4175 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 13029 "parser_bison.c"
    break;

  case 719: /* map_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt "colon" set_elem_expr_stmt '}'  */
#line 4179 "parser_bison.y"
                        {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 13041 "parser_bison.c"
    break;

  case 720: /* map_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt stateful_stmt_list "colon" set_elem_expr_stmt '}'  */
#line 4187 "parser_bison.y"
                        {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
				list_splice_tail((yyvsp[-3].list), &(yyval.stmt)->map.stmt_list);
				free((yyvsp[-3].list));
			}
#line 13055 "parser_bison.c"
    break;

  case 721: /* meter_stmt: flow_stmt_legacy_alloc flow_stmt_opts '{' meter_key_expr stmt '}'  */
#line 4199 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 13066 "parser_bison.c"
    break;

  case 722: /* meter_stmt: meter_stmt_alloc  */
#line 4205 "parser_bison.y"
                                                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 13072 "parser_bison.c"
    break;

  case 723: /* flow_stmt_legacy_alloc: "flow"  */
#line 4209 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 13080 "parser_bison.c"
    break;

  case 724: /* flow_stmt_opts: flow_stmt_opt  */
#line 4215 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 13088 "parser_bison.c"
    break;

  case 726: /* flow_stmt_opt: "table" identifier  */
#line 4222 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 13096 "parser_bison.c"
    break;

  case 727: /* meter_stmt_alloc: "meter" identifier '{' meter_key_expr stmt '}'  */
#line 4228 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 13109 "parser_bison.c"
    break;

  case 728: /* meter_stmt_alloc: "meter" identifier "size" "number" '{' meter_key_expr stmt '}'  */
#line 4237 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 13122 "parser_bison.c"
    break;

  case 729: /* match_stmt: relational_expr  */
#line 4248 "parser_bison.y"
                        {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 13130 "parser_bison.c"
    break;

  case 730: /* variable_expr: '$' identifier  */
#line 4254 "parser_bison.y"
                        {
				struct scope *scope = current_scope(state);
				struct symbol *sym;

				sym = symbol_get(scope, (yyvsp[0].string));
				if (!sym) {
					sym = symbol_lookup_fuzzy(scope, (yyvsp[0].string));
					if (sym) {
						erec_queue(error(&(yylsp[0]), "unknown identifier '%s'; "
								      "did you mean identifier ‘%s’?",
								      (yyvsp[0].string), sym->identifier),
							   state->msgs);
					} else {
						erec_queue(error(&(yylsp[0]), "unknown identifier '%s'", (yyvsp[0].string)),
							   state->msgs);
					}
					xfree((yyvsp[0].string));
					YYERROR;
				}

				(yyval.expr) = variable_expr_alloc(&(yyloc), scope, sym);
				xfree((yyvsp[0].string));
			}
#line 13158 "parser_bison.c"
    break;

  case 732: /* symbol_expr: string  */
#line 4281 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 13169 "parser_bison.c"
    break;

  case 735: /* set_ref_symbol_expr: "@" identifier close_scope_at  */
#line 4294 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[-1].string));
				xfree((yyvsp[-1].string));
			}
#line 13180 "parser_bison.c"
    break;

  case 736: /* integer_expr: "number"  */
#line 4303 "parser_bison.y"
                        {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 13193 "parser_bison.c"
    break;

  case 737: /* primary_expr: symbol_expr  */
#line 4313 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13199 "parser_bison.c"
    break;

  case 738: /* primary_expr: integer_expr  */
#line 4314 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13205 "parser_bison.c"
    break;

  case 739: /* primary_expr: payload_expr  */
#line 4315 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13211 "parser_bison.c"
    break;

  case 740: /* primary_expr: exthdr_expr  */
#line 4316 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13217 "parser_bison.c"
    break;

  case 741: /* primary_expr: exthdr_exists_expr  */
#line 4317 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13223 "parser_bison.c"
    break;

  case 742: /* primary_expr: meta_expr  */
#line 4318 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13229 "parser_bison.c"
    break;

  case 743: /* primary_expr: socket_expr  */
#line 4319 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13235 "parser_bison.c"
    break;

  case 744: /* primary_expr: rt_expr  */
#line 4320 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13241 "parser_bison.c"
    break;

  case 745: /* primary_expr: ct_expr  */
#line 4321 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13247 "parser_bison.c"
    break;

  case 746: /* primary_expr: numgen_expr  */
#line 4322 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13253 "parser_bison.c"
    break;

  case 747: /* primary_expr: hash_expr  */
#line 4323 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13259 "parser_bison.c"
    break;

  case 748: /* primary_expr: fib_expr  */
#line 4324 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13265 "parser_bison.c"
    break;

  case 749: /* primary_expr: osf_expr  */
#line 4325 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13271 "parser_bison.c"
    break;

  case 750: /* primary_expr: xfrm_expr  */
#line 4326 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13277 "parser_bison.c"
    break;

  case 751: /* primary_expr: '(' basic_expr ')'  */
#line 4327 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 13283 "parser_bison.c"
    break;

  case 752: /* fib_expr: "fib" fib_tuple fib_result close_scope_fib  */
#line 4331 "parser_bison.y"
                        {
				if (((yyvsp[-2].val) & (NFTA_FIB_F_SADDR|NFTA_FIB_F_DADDR)) == 0) {
					erec_queue(error(&(yylsp[-2]), "fib: need either saddr or daddr"), state->msgs);
					YYERROR;
				}

				if (((yyvsp[-2].val) & (NFTA_FIB_F_SADDR|NFTA_FIB_F_DADDR)) ==
					  (NFTA_FIB_F_SADDR|NFTA_FIB_F_DADDR)) {
					erec_queue(error(&(yylsp[-2]), "fib: saddr and daddr are mutually exclusive"), state->msgs);
					YYERROR;
				}

				if (((yyvsp[-2].val) & (NFTA_FIB_F_IIF|NFTA_FIB_F_OIF)) ==
					  (NFTA_FIB_F_IIF|NFTA_FIB_F_OIF)) {
					erec_queue(error(&(yylsp[-2]), "fib: iif and oif are mutually exclusive"), state->msgs);
					YYERROR;
				}

				(yyval.expr) = fib_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 13308 "parser_bison.c"
    break;

  case 753: /* fib_result: "oif"  */
#line 4353 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 13314 "parser_bison.c"
    break;

  case 754: /* fib_result: "oifname"  */
#line 4354 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 13320 "parser_bison.c"
    break;

  case 755: /* fib_result: "type" close_scope_type  */
#line 4355 "parser_bison.y"
                                                                { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 13326 "parser_bison.c"
    break;

  case 756: /* fib_flag: "saddr"  */
#line 4358 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 13332 "parser_bison.c"
    break;

  case 757: /* fib_flag: "daddr"  */
#line 4359 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 13338 "parser_bison.c"
    break;

  case 758: /* fib_flag: "mark"  */
#line 4360 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_MARK; }
#line 13344 "parser_bison.c"
    break;

  case 759: /* fib_flag: "iif"  */
#line 4361 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_IIF; }
#line 13350 "parser_bison.c"
    break;

  case 760: /* fib_flag: "oif"  */
#line 4362 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_OIF; }
#line 13356 "parser_bison.c"
    break;

  case 761: /* fib_tuple: fib_flag "." fib_tuple  */
#line 4366 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 13364 "parser_bison.c"
    break;

  case 763: /* osf_expr: "osf" osf_ttl "version" close_scope_osf  */
#line 4373 "parser_bison.y"
                        {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-2].val), NFT_OSF_F_VERSION);
			}
#line 13372 "parser_bison.c"
    break;

  case 764: /* osf_expr: "osf" osf_ttl "name" close_scope_osf  */
#line 4377 "parser_bison.y"
                        {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-2].val), 0);
			}
#line 13380 "parser_bison.c"
    break;

  case 765: /* osf_ttl: %empty  */
#line 4383 "parser_bison.y"
                        {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 13388 "parser_bison.c"
    break;

  case 766: /* osf_ttl: "ttl" "string"  */
#line 4387 "parser_bison.y"
                        {
				if (!strcmp((yyvsp[0].string), "loose"))
					(yyval.val) = NF_OSF_TTL_LESS;
				else if (!strcmp((yyvsp[0].string), "skip"))
					(yyval.val) = NF_OSF_TTL_NOCHECK;
				else {
					erec_queue(error(&(yylsp[0]), "invalid ttl option"),
						   state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}
				xfree((yyvsp[0].string));
			}
#line 13406 "parser_bison.c"
    break;

  case 768: /* shift_expr: shift_expr "<<" primary_rhs_expr  */
#line 4404 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13414 "parser_bison.c"
    break;

  case 769: /* shift_expr: shift_expr ">>" primary_rhs_expr  */
#line 4408 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13422 "parser_bison.c"
    break;

  case 771: /* and_expr: and_expr "&" shift_rhs_expr  */
#line 4415 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13430 "parser_bison.c"
    break;

  case 773: /* exclusive_or_expr: exclusive_or_expr "^" and_rhs_expr  */
#line 4422 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13438 "parser_bison.c"
    break;

  case 775: /* inclusive_or_expr: inclusive_or_expr '|' exclusive_or_rhs_expr  */
#line 4429 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13446 "parser_bison.c"
    break;

  case 778: /* concat_expr: concat_expr "." basic_expr  */
#line 4439 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 13459 "parser_bison.c"
    break;

  case 779: /* prefix_rhs_expr: basic_rhs_expr "/" "number"  */
#line 4450 "parser_bison.y"
                        {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 13467 "parser_bison.c"
    break;

  case 780: /* range_rhs_expr: basic_rhs_expr "-" basic_rhs_expr  */
#line 4456 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13475 "parser_bison.c"
    break;

  case 783: /* map_expr: concat_expr "map" rhs_expr  */
#line 4466 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13483 "parser_bison.c"
    break;

  case 787: /* set_expr: '{' set_list_expr '}'  */
#line 4477 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13492 "parser_bison.c"
    break;

  case 788: /* set_list_expr: set_list_member_expr  */
#line 4484 "parser_bison.y"
                        {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 13501 "parser_bison.c"
    break;

  case 789: /* set_list_expr: set_list_expr "comma" set_list_member_expr  */
#line 4489 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 13510 "parser_bison.c"
    break;

  case 791: /* set_list_member_expr: opt_newline set_expr opt_newline  */
#line 4497 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13518 "parser_bison.c"
    break;

  case 792: /* set_list_member_expr: opt_newline set_elem_expr opt_newline  */
#line 4501 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13526 "parser_bison.c"
    break;

  case 793: /* set_list_member_expr: opt_newline set_elem_expr "colon" set_rhs_expr opt_newline  */
#line 4505 "parser_bison.y"
                        {
				(yyval.expr) = mapping_expr_alloc(&(yylsp[-3]), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 13534 "parser_bison.c"
    break;

  case 795: /* meter_key_expr: meter_key_expr_alloc set_elem_options  */
#line 4512 "parser_bison.y"
                        {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13543 "parser_bison.c"
    break;

  case 796: /* meter_key_expr_alloc: concat_expr  */
#line 4519 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 13551 "parser_bison.c"
    break;

  case 799: /* set_elem_key_expr: set_lhs_expr  */
#line 4528 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13557 "parser_bison.c"
    break;

  case 800: /* set_elem_key_expr: "*"  */
#line 4529 "parser_bison.y"
                                                        { (yyval.expr) = set_elem_catchall_expr_alloc(&(yylsp[0])); }
#line 13563 "parser_bison.c"
    break;

  case 801: /* set_elem_expr_alloc: set_elem_key_expr set_elem_stmt_list  */
#line 4533 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[-1]), (yyvsp[-1].expr));
				list_splice_tail((yyvsp[0].list), &(yyval.expr)->stmt_list);
				xfree((yyvsp[0].list));
			}
#line 13573 "parser_bison.c"
    break;

  case 802: /* set_elem_expr_alloc: set_elem_key_expr  */
#line 4539 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 13581 "parser_bison.c"
    break;

  case 803: /* set_elem_options: set_elem_option  */
#line 4545 "parser_bison.y"
                        {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 13589 "parser_bison.c"
    break;

  case 805: /* set_elem_option: "timeout" time_spec  */
#line 4552 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 13597 "parser_bison.c"
    break;

  case 806: /* set_elem_option: "expires" time_spec  */
#line 4556 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 13605 "parser_bison.c"
    break;

  case 807: /* set_elem_option: comment_spec  */
#line 4560 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 13617 "parser_bison.c"
    break;

  case 808: /* set_elem_expr_options: set_elem_expr_option  */
#line 4570 "parser_bison.y"
                        {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 13625 "parser_bison.c"
    break;

  case 810: /* set_elem_stmt_list: set_elem_stmt  */
#line 4577 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 13635 "parser_bison.c"
    break;

  case 811: /* set_elem_stmt_list: set_elem_stmt_list set_elem_stmt  */
#line 4583 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 13644 "parser_bison.c"
    break;

  case 812: /* set_elem_stmt: "counter" close_scope_counter  */
#line 4590 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 13652 "parser_bison.c"
    break;

  case 813: /* set_elem_stmt: "counter" "packets" "number" "bytes" "number" close_scope_counter  */
#line 4594 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
				(yyval.stmt)->counter.packets = (yyvsp[-3].val);
				(yyval.stmt)->counter.bytes = (yyvsp[-1].val);
			}
#line 13662 "parser_bison.c"
    break;

  case 814: /* set_elem_stmt: "limit" "rate" limit_mode limit_rate_pkts limit_burst_pkts close_scope_limit  */
#line 4600 "parser_bison.y"
                        {
				if ((yyvsp[-1].val) == 0) {
					erec_queue(error(&(yylsp[-1]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate  = (yyvsp[-2].limit_rate).rate;
				(yyval.stmt)->limit.unit  = (yyvsp[-2].limit_rate).unit;
				(yyval.stmt)->limit.burst = (yyvsp[-1].val);
				(yyval.stmt)->limit.type  = NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-3].val);
			}
#line 13680 "parser_bison.c"
    break;

  case 815: /* set_elem_stmt: "limit" "rate" limit_mode limit_rate_bytes limit_burst_bytes close_scope_limit  */
#line 4614 "parser_bison.y"
                        {
				if ((yyvsp[-1].val) == 0) {
					erec_queue(error(&(yylsp[0]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate  = (yyvsp[-2].limit_rate).rate;
				(yyval.stmt)->limit.unit  = (yyvsp[-2].limit_rate).unit;
				(yyval.stmt)->limit.burst = (yyvsp[-1].val);
				(yyval.stmt)->limit.type  = NFT_LIMIT_PKT_BYTES;
				(yyval.stmt)->limit.flags = (yyvsp[-3].val);
			}
#line 13698 "parser_bison.c"
    break;

  case 816: /* set_elem_stmt: "ct" "count" "number" close_scope_ct  */
#line 4628 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 13707 "parser_bison.c"
    break;

  case 817: /* set_elem_stmt: "ct" "count" "over" "number" close_scope_ct  */
#line 4633 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 13717 "parser_bison.c"
    break;

  case 818: /* set_elem_stmt: "quota" quota_mode "number" quota_unit quota_used close_scope_quota  */
#line 4639 "parser_bison.y"
                        {
				struct error_record *erec;
				uint64_t rate;

				erec = data_unit_parse(&(yyloc), (yyvsp[-2].string), &rate);
				xfree((yyvsp[-2].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.stmt) = quota_stmt_alloc(&(yyloc));
				(yyval.stmt)->quota.bytes	= (yyvsp[-3].val) * rate;
				(yyval.stmt)->quota.used = (yyvsp[-1].val);
				(yyval.stmt)->quota.flags	= (yyvsp[-4].val);
			}
#line 13737 "parser_bison.c"
    break;

  case 819: /* set_elem_stmt: "last" "used" "never" close_scope_last  */
#line 4655 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
			}
#line 13745 "parser_bison.c"
    break;

  case 820: /* set_elem_stmt: "last" "used" time_spec close_scope_last  */
#line 4659 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
				(yyval.stmt)->last.used = (yyvsp[-1].val);
				(yyval.stmt)->last.set = true;
			}
#line 13755 "parser_bison.c"
    break;

  case 821: /* set_elem_expr_option: "timeout" time_spec  */
#line 4667 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 13763 "parser_bison.c"
    break;

  case 822: /* set_elem_expr_option: "expires" time_spec  */
#line 4671 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 13771 "parser_bison.c"
    break;

  case 823: /* set_elem_expr_option: comment_spec  */
#line 4675 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 13783 "parser_bison.c"
    break;

  case 829: /* initializer_expr: '{' '}'  */
#line 4693 "parser_bison.y"
                                                { (yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_SET); }
#line 13789 "parser_bison.c"
    break;

  case 830: /* initializer_expr: "-" "number"  */
#line 4695 "parser_bison.y"
                        {
				int32_t num = -(yyvsp[0].val);

				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(num) * BITS_PER_BYTE,
							 &num);
			}
#line 13802 "parser_bison.c"
    break;

  case 831: /* counter_config: "packets" "number" "bytes" "number"  */
#line 4706 "parser_bison.y"
                        {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 13814 "parser_bison.c"
    break;

  case 832: /* counter_obj: %empty  */
#line 4716 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 13823 "parser_bison.c"
    break;

  case 833: /* quota_config: quota_mode "number" quota_unit quota_used  */
#line 4723 "parser_bison.y"
                        {
				struct error_record *erec;
				struct quota *quota;
				uint64_t rate;

				erec = data_unit_parse(&(yyloc), (yyvsp[-1].string), &rate);
				xfree((yyvsp[-1].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				quota = &(yyvsp[-4].obj)->quota;
				quota->bytes	= (yyvsp[-2].val) * rate;
				quota->used	= (yyvsp[0].val);
				quota->flags	= (yyvsp[-3].val);
			}
#line 13845 "parser_bison.c"
    break;

  case 834: /* quota_obj: %empty  */
#line 4743 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 13854 "parser_bison.c"
    break;

  case 835: /* secmark_config: string  */
#line 4750 "parser_bison.y"
                        {
				int ret;
				struct secmark *secmark;

				secmark = &(yyvsp[-1].obj)->secmark;
				ret = snprintf(secmark->ctx, sizeof(secmark->ctx), "%s", (yyvsp[0].string));
				if (ret <= 0 || ret >= (int)sizeof(secmark->ctx)) {
					erec_queue(error(&(yylsp[0]), "invalid context '%s', max length is %u\n", (yyvsp[0].string), (int)sizeof(secmark->ctx)), state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}
				xfree((yyvsp[0].string));
			}
#line 13872 "parser_bison.c"
    break;

  case 836: /* secmark_obj: %empty  */
#line 4766 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 13881 "parser_bison.c"
    break;

  case 837: /* ct_obj_type: "helper"  */
#line 4772 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 13887 "parser_bison.c"
    break;

  case 838: /* ct_obj_type: "timeout"  */
#line 4773 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 13893 "parser_bison.c"
    break;

  case 839: /* ct_obj_type: "expectation"  */
#line 4774 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 13899 "parser_bison.c"
    break;

  case 840: /* ct_cmd_type: "helpers"  */
#line 4777 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_HELPERS; }
#line 13905 "parser_bison.c"
    break;

  case 841: /* ct_cmd_type: "timeout"  */
#line 4778 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_TIMEOUTS; }
#line 13911 "parser_bison.c"
    break;

  case 842: /* ct_cmd_type: "expectation"  */
#line 4779 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_EXPECTATIONS; }
#line 13917 "parser_bison.c"
    break;

  case 843: /* ct_l4protoname: "tcp" close_scope_tcp  */
#line 4782 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_TCP; }
#line 13923 "parser_bison.c"
    break;

  case 844: /* ct_l4protoname: "udp" close_scope_udp  */
#line 4783 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_UDP; }
#line 13929 "parser_bison.c"
    break;

  case 845: /* ct_helper_config: "type" "quoted string" "protocol" ct_l4protoname stmt_separator close_scope_type  */
#line 4787 "parser_bison.y"
                        {
				struct ct_helper *ct;
				int ret;

				ct = &(yyvsp[-6].obj)->ct_helper;

				ret = snprintf(ct->name, sizeof(ct->name), "%s", (yyvsp[-4].string));
				if (ret <= 0 || ret >= (int)sizeof(ct->name)) {
					erec_queue(error(&(yylsp[-4]), "invalid name '%s', max length is %u\n", (yyvsp[-4].string), (int)sizeof(ct->name)), state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-4].string));

				ct->l4proto = (yyvsp[-2].val);
			}
#line 13949 "parser_bison.c"
    break;

  case 846: /* ct_helper_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4803 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 13957 "parser_bison.c"
    break;

  case 847: /* timeout_states: timeout_state  */
#line 4809 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 13967 "parser_bison.c"
    break;

  case 848: /* timeout_states: timeout_states "comma" timeout_state  */
#line 4815 "parser_bison.y"
                        {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 13976 "parser_bison.c"
    break;

  case 849: /* timeout_state: "string" "colon" time_spec_or_num_s  */
#line 4822 "parser_bison.y"
                        {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 13991 "parser_bison.c"
    break;

  case 850: /* ct_timeout_config: "protocol" ct_l4protoname stmt_separator  */
#line 4835 "parser_bison.y"
                        {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 14003 "parser_bison.c"
    break;

  case 851: /* ct_timeout_config: "policy" '=' '{' timeout_states '}' stmt_separator close_scope_policy  */
#line 4843 "parser_bison.y"
                        {
				struct ct_timeout *ct;

				ct = &(yyvsp[-7].obj)->ct_timeout;
				list_splice_tail((yyvsp[-3].list), &ct->timeout_list);
				xfree((yyvsp[-3].list));
			}
#line 14015 "parser_bison.c"
    break;

  case 852: /* ct_timeout_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4851 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 14023 "parser_bison.c"
    break;

  case 853: /* ct_expect_config: "protocol" ct_l4protoname stmt_separator  */
#line 4857 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 14031 "parser_bison.c"
    break;

  case 854: /* ct_expect_config: "dport" "number" stmt_separator  */
#line 4861 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 14039 "parser_bison.c"
    break;

  case 855: /* ct_expect_config: "timeout" time_spec stmt_separator  */
#line 4865 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 14047 "parser_bison.c"
    break;

  case 856: /* ct_expect_config: "size" "number" stmt_separator  */
#line 4869 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 14055 "parser_bison.c"
    break;

  case 857: /* ct_expect_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4873 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 14063 "parser_bison.c"
    break;

  case 858: /* ct_obj_alloc: %empty  */
#line 4879 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 14071 "parser_bison.c"
    break;

  case 859: /* limit_config: "rate" limit_mode limit_rate_pkts limit_burst_pkts  */
#line 4885 "parser_bison.y"
                        {
				struct limit *limit;

				limit = &(yyvsp[-4].obj)->limit;
				limit->rate	= (yyvsp[-1].limit_rate).rate;
				limit->unit	= (yyvsp[-1].limit_rate).unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-2].val);
			}
#line 14086 "parser_bison.c"
    break;

  case 860: /* limit_config: "rate" limit_mode limit_rate_bytes limit_burst_bytes  */
#line 4896 "parser_bison.y"
                        {
				struct limit *limit;

				limit = &(yyvsp[-4].obj)->limit;
				limit->rate	= (yyvsp[-1].limit_rate).rate;
				limit->unit	= (yyvsp[-1].limit_rate).unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKT_BYTES;
				limit->flags	= (yyvsp[-2].val);
			}
#line 14101 "parser_bison.c"
    break;

  case 861: /* limit_obj: %empty  */
#line 4909 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 14110 "parser_bison.c"
    break;

  case 862: /* relational_expr: expr rhs_expr  */
#line 4916 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 14118 "parser_bison.c"
    break;

  case 863: /* relational_expr: expr list_rhs_expr  */
#line 4920 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 14126 "parser_bison.c"
    break;

  case 864: /* relational_expr: expr basic_rhs_expr "/" list_rhs_expr  */
#line 4924 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 14134 "parser_bison.c"
    break;

  case 865: /* relational_expr: expr list_rhs_expr "/" list_rhs_expr  */
#line 4928 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 14142 "parser_bison.c"
    break;

  case 866: /* relational_expr: expr relational_op basic_rhs_expr "/" list_rhs_expr  */
#line 4932 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 14150 "parser_bison.c"
    break;

  case 867: /* relational_expr: expr relational_op list_rhs_expr "/" list_rhs_expr  */
#line 4936 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 14158 "parser_bison.c"
    break;

  case 868: /* relational_expr: expr relational_op rhs_expr  */
#line 4940 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14166 "parser_bison.c"
    break;

  case 869: /* relational_expr: expr relational_op list_rhs_expr  */
#line 4944 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14174 "parser_bison.c"
    break;

  case 870: /* list_rhs_expr: basic_rhs_expr "comma" basic_rhs_expr  */
#line 4950 "parser_bison.y"
                        {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 14184 "parser_bison.c"
    break;

  case 871: /* list_rhs_expr: list_rhs_expr "comma" basic_rhs_expr  */
#line 4956 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 14194 "parser_bison.c"
    break;

  case 872: /* rhs_expr: concat_rhs_expr  */
#line 4963 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14200 "parser_bison.c"
    break;

  case 873: /* rhs_expr: set_expr  */
#line 4964 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14206 "parser_bison.c"
    break;

  case 874: /* rhs_expr: set_ref_symbol_expr  */
#line 4965 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14212 "parser_bison.c"
    break;

  case 876: /* shift_rhs_expr: shift_rhs_expr "<<" primary_rhs_expr  */
#line 4970 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14220 "parser_bison.c"
    break;

  case 877: /* shift_rhs_expr: shift_rhs_expr ">>" primary_rhs_expr  */
#line 4974 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14228 "parser_bison.c"
    break;

  case 879: /* and_rhs_expr: and_rhs_expr "&" shift_rhs_expr  */
#line 4981 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14236 "parser_bison.c"
    break;

  case 881: /* exclusive_or_rhs_expr: exclusive_or_rhs_expr "^" and_rhs_expr  */
#line 4988 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14244 "parser_bison.c"
    break;

  case 883: /* inclusive_or_rhs_expr: inclusive_or_rhs_expr '|' exclusive_or_rhs_expr  */
#line 4995 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14252 "parser_bison.c"
    break;

  case 887: /* concat_rhs_expr: concat_rhs_expr "." multiton_rhs_expr  */
#line 5006 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 14265 "parser_bison.c"
    break;

  case 888: /* concat_rhs_expr: concat_rhs_expr "." basic_rhs_expr  */
#line 5015 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 14278 "parser_bison.c"
    break;

  case 889: /* boolean_keys: "exists"  */
#line 5025 "parser_bison.y"
                                                { (yyval.val8) = true; }
#line 14284 "parser_bison.c"
    break;

  case 890: /* boolean_keys: "missing"  */
#line 5026 "parser_bison.y"
                                                { (yyval.val8) = false; }
#line 14290 "parser_bison.c"
    break;

  case 891: /* boolean_expr: boolean_keys  */
#line 5030 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 14300 "parser_bison.c"
    break;

  case 892: /* keyword_expr: "ether" close_scope_eth  */
#line 5037 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 14306 "parser_bison.c"
    break;

  case 893: /* keyword_expr: "ip" close_scope_ip  */
#line 5038 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 14312 "parser_bison.c"
    break;

  case 894: /* keyword_expr: "ip6" close_scope_ip6  */
#line 5039 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 14318 "parser_bison.c"
    break;

  case 895: /* keyword_expr: "vlan" close_scope_vlan  */
#line 5040 "parser_bison.y"
                                                         { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 14324 "parser_bison.c"
    break;

  case 896: /* keyword_expr: "arp" close_scope_arp  */
#line 5041 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 14330 "parser_bison.c"
    break;

  case 897: /* keyword_expr: "dnat" close_scope_nat  */
#line 5042 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 14336 "parser_bison.c"
    break;

  case 898: /* keyword_expr: "snat" close_scope_nat  */
#line 5043 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 14342 "parser_bison.c"
    break;

  case 899: /* keyword_expr: "ecn"  */
#line 5044 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 14348 "parser_bison.c"
    break;

  case 900: /* keyword_expr: "reset" close_scope_reset  */
#line 5045 "parser_bison.y"
                                                                { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 14354 "parser_bison.c"
    break;

  case 901: /* keyword_expr: "destroy" close_scope_destroy  */
#line 5046 "parser_bison.y"
                                                                { (yyval.expr) = symbol_value(&(yyloc), "destroy"); }
#line 14360 "parser_bison.c"
    break;

  case 902: /* keyword_expr: "original"  */
#line 5047 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 14366 "parser_bison.c"
    break;

  case 903: /* keyword_expr: "reply"  */
#line 5048 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 14372 "parser_bison.c"
    break;

  case 904: /* keyword_expr: "label"  */
#line 5049 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 14378 "parser_bison.c"
    break;

  case 905: /* keyword_expr: "last" close_scope_last  */
#line 5050 "parser_bison.y"
                                                                { (yyval.expr) = symbol_value(&(yyloc), "last"); }
#line 14384 "parser_bison.c"
    break;

  case 906: /* primary_rhs_expr: symbol_expr  */
#line 5053 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14390 "parser_bison.c"
    break;

  case 907: /* primary_rhs_expr: integer_expr  */
#line 5054 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14396 "parser_bison.c"
    break;

  case 908: /* primary_rhs_expr: boolean_expr  */
#line 5055 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14402 "parser_bison.c"
    break;

  case 909: /* primary_rhs_expr: keyword_expr  */
#line 5056 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14408 "parser_bison.c"
    break;

  case 910: /* primary_rhs_expr: "tcp" close_scope_tcp  */
#line 5058 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14419 "parser_bison.c"
    break;

  case 911: /* primary_rhs_expr: "udp" close_scope_udp  */
#line 5065 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14430 "parser_bison.c"
    break;

  case 912: /* primary_rhs_expr: "udplite" close_scope_udplite  */
#line 5072 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14441 "parser_bison.c"
    break;

  case 913: /* primary_rhs_expr: "esp" close_scope_esp  */
#line 5079 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14452 "parser_bison.c"
    break;

  case 914: /* primary_rhs_expr: "ah" close_scope_ah  */
#line 5086 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14463 "parser_bison.c"
    break;

  case 915: /* primary_rhs_expr: "icmp" close_scope_icmp  */
#line 5093 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14474 "parser_bison.c"
    break;

  case 916: /* primary_rhs_expr: "igmp"  */
#line 5100 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14485 "parser_bison.c"
    break;

  case 917: /* primary_rhs_expr: "icmpv6" close_scope_icmp  */
#line 5107 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14496 "parser_bison.c"
    break;

  case 918: /* primary_rhs_expr: "gre" close_scope_gre  */
#line 5114 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_GRE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14507 "parser_bison.c"
    break;

  case 919: /* primary_rhs_expr: "comp" close_scope_comp  */
#line 5121 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14518 "parser_bison.c"
    break;

  case 920: /* primary_rhs_expr: "dccp" close_scope_dccp  */
#line 5128 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14529 "parser_bison.c"
    break;

  case 921: /* primary_rhs_expr: "sctp" close_scope_sctp  */
#line 5135 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14540 "parser_bison.c"
    break;

  case 922: /* primary_rhs_expr: "redirect" close_scope_nat  */
#line 5142 "parser_bison.y"
                        {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14551 "parser_bison.c"
    break;

  case 923: /* primary_rhs_expr: '(' basic_rhs_expr ')'  */
#line 5148 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 14557 "parser_bison.c"
    break;

  case 924: /* relational_op: "=="  */
#line 5151 "parser_bison.y"
                                                { (yyval.val) = OP_EQ; }
#line 14563 "parser_bison.c"
    break;

  case 925: /* relational_op: "!="  */
#line 5152 "parser_bison.y"
                                                { (yyval.val) = OP_NEQ; }
#line 14569 "parser_bison.c"
    break;

  case 926: /* relational_op: "<"  */
#line 5153 "parser_bison.y"
                                                { (yyval.val) = OP_LT; }
#line 14575 "parser_bison.c"
    break;

  case 927: /* relational_op: ">"  */
#line 5154 "parser_bison.y"
                                                { (yyval.val) = OP_GT; }
#line 14581 "parser_bison.c"
    break;

  case 928: /* relational_op: ">="  */
#line 5155 "parser_bison.y"
                                                { (yyval.val) = OP_GTE; }
#line 14587 "parser_bison.c"
    break;

  case 929: /* relational_op: "<="  */
#line 5156 "parser_bison.y"
                                                { (yyval.val) = OP_LTE; }
#line 14593 "parser_bison.c"
    break;

  case 930: /* relational_op: "!"  */
#line 5157 "parser_bison.y"
                                                { (yyval.val) = OP_NEG; }
#line 14599 "parser_bison.c"
    break;

  case 931: /* verdict_expr: "accept"  */
#line 5161 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 14607 "parser_bison.c"
    break;

  case 932: /* verdict_expr: "drop"  */
#line 5165 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 14615 "parser_bison.c"
    break;

  case 933: /* verdict_expr: "continue"  */
#line 5169 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 14623 "parser_bison.c"
    break;

  case 934: /* verdict_expr: "jump" chain_expr  */
#line 5173 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 14631 "parser_bison.c"
    break;

  case 935: /* verdict_expr: "goto" chain_expr  */
#line 5177 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 14639 "parser_bison.c"
    break;

  case 936: /* verdict_expr: "return"  */
#line 5181 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 14647 "parser_bison.c"
    break;

  case 938: /* chain_expr: identifier  */
#line 5188 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 14659 "parser_bison.c"
    break;

  case 939: /* meta_expr: "meta" meta_key close_scope_meta  */
#line 5198 "parser_bison.y"
                        {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[-1].val));
			}
#line 14667 "parser_bison.c"
    break;

  case 940: /* meta_expr: meta_key_unqualified  */
#line 5202 "parser_bison.y"
                        {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 14675 "parser_bison.c"
    break;

  case 941: /* meta_expr: "meta" "string" close_scope_meta  */
#line 5206 "parser_bison.y"
                        {
				struct error_record *erec;
				unsigned int key;

				erec = meta_key_parse(&(yyloc), (yyvsp[-1].string), &key);
				xfree((yyvsp[-1].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.expr) = meta_expr_alloc(&(yyloc), key);
			}
#line 14693 "parser_bison.c"
    break;

  case 944: /* meta_key_qualified: "length"  */
#line 5225 "parser_bison.y"
                                                { (yyval.val) = NFT_META_LEN; }
#line 14699 "parser_bison.c"
    break;

  case 945: /* meta_key_qualified: "protocol"  */
#line 5226 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PROTOCOL; }
#line 14705 "parser_bison.c"
    break;

  case 946: /* meta_key_qualified: "priority"  */
#line 5227 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PRIORITY; }
#line 14711 "parser_bison.c"
    break;

  case 947: /* meta_key_qualified: "random"  */
#line 5228 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PRANDOM; }
#line 14717 "parser_bison.c"
    break;

  case 948: /* meta_key_qualified: "secmark" close_scope_secmark  */
#line 5229 "parser_bison.y"
                                                            { (yyval.val) = NFT_META_SECMARK; }
#line 14723 "parser_bison.c"
    break;

  case 949: /* meta_key_unqualified: "mark"  */
#line 5232 "parser_bison.y"
                                                { (yyval.val) = NFT_META_MARK; }
#line 14729 "parser_bison.c"
    break;

  case 950: /* meta_key_unqualified: "iif"  */
#line 5233 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIF; }
#line 14735 "parser_bison.c"
    break;

  case 951: /* meta_key_unqualified: "iifname"  */
#line 5234 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFNAME; }
#line 14741 "parser_bison.c"
    break;

  case 952: /* meta_key_unqualified: "iiftype"  */
#line 5235 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFTYPE; }
#line 14747 "parser_bison.c"
    break;

  case 953: /* meta_key_unqualified: "oif"  */
#line 5236 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIF; }
#line 14753 "parser_bison.c"
    break;

  case 954: /* meta_key_unqualified: "oifname"  */
#line 5237 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFNAME; }
#line 14759 "parser_bison.c"
    break;

  case 955: /* meta_key_unqualified: "oiftype"  */
#line 5238 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFTYPE; }
#line 14765 "parser_bison.c"
    break;

  case 956: /* meta_key_unqualified: "skuid"  */
#line 5239 "parser_bison.y"
                                                { (yyval.val) = NFT_META_SKUID; }
#line 14771 "parser_bison.c"
    break;

  case 957: /* meta_key_unqualified: "skgid"  */
#line 5240 "parser_bison.y"
                                                { (yyval.val) = NFT_META_SKGID; }
#line 14777 "parser_bison.c"
    break;

  case 958: /* meta_key_unqualified: "nftrace"  */
#line 5241 "parser_bison.y"
                                                { (yyval.val) = NFT_META_NFTRACE; }
#line 14783 "parser_bison.c"
    break;

  case 959: /* meta_key_unqualified: "rtclassid"  */
#line 5242 "parser_bison.y"
                                                { (yyval.val) = NFT_META_RTCLASSID; }
#line 14789 "parser_bison.c"
    break;

  case 960: /* meta_key_unqualified: "ibriport"  */
#line 5243 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 14795 "parser_bison.c"
    break;

  case 961: /* meta_key_unqualified: "obriport"  */
#line 5244 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 14801 "parser_bison.c"
    break;

  case 962: /* meta_key_unqualified: "ibrname"  */
#line 5245 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 14807 "parser_bison.c"
    break;

  case 963: /* meta_key_unqualified: "obrname"  */
#line 5246 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 14813 "parser_bison.c"
    break;

  case 964: /* meta_key_unqualified: "pkttype"  */
#line 5247 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PKTTYPE; }
#line 14819 "parser_bison.c"
    break;

  case 965: /* meta_key_unqualified: "cpu"  */
#line 5248 "parser_bison.y"
                                                { (yyval.val) = NFT_META_CPU; }
#line 14825 "parser_bison.c"
    break;

  case 966: /* meta_key_unqualified: "iifgroup"  */
#line 5249 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFGROUP; }
#line 14831 "parser_bison.c"
    break;

  case 967: /* meta_key_unqualified: "oifgroup"  */
#line 5250 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFGROUP; }
#line 14837 "parser_bison.c"
    break;

  case 968: /* meta_key_unqualified: "cgroup"  */
#line 5251 "parser_bison.y"
                                                { (yyval.val) = NFT_META_CGROUP; }
#line 14843 "parser_bison.c"
    break;

  case 969: /* meta_key_unqualified: "ipsec" close_scope_ipsec  */
#line 5252 "parser_bison.y"
                                                          { (yyval.val) = NFT_META_SECPATH; }
#line 14849 "parser_bison.c"
    break;

  case 970: /* meta_key_unqualified: "time"  */
#line 5253 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_NS; }
#line 14855 "parser_bison.c"
    break;

  case 971: /* meta_key_unqualified: "day"  */
#line 5254 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_DAY; }
#line 14861 "parser_bison.c"
    break;

  case 972: /* meta_key_unqualified: "hour"  */
#line 5255 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_HOUR; }
#line 14867 "parser_bison.c"
    break;

  case 973: /* meta_stmt: "meta" meta_key "set" stmt_expr close_scope_meta  */
#line 5259 "parser_bison.y"
                        {
				switch ((yyvsp[-3].val)) {
				case NFT_META_SECMARK:
					switch ((yyvsp[-1].expr)->etype) {
					case EXPR_CT:
						(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].expr));
						break;
					default:
						(yyval.stmt) = objref_stmt_alloc(&(yyloc));
						(yyval.stmt)->objref.type = NFT_OBJECT_SECMARK;
						(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
						break;
					}
					break;
				default:
					(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].expr));
					break;
				}
			}
#line 14891 "parser_bison.c"
    break;

  case 974: /* meta_stmt: meta_key_unqualified "set" stmt_expr  */
#line 5279 "parser_bison.y"
                        {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 14899 "parser_bison.c"
    break;

  case 975: /* meta_stmt: "meta" "string" "set" stmt_expr close_scope_meta  */
#line 5283 "parser_bison.y"
                        {
				struct error_record *erec;
				unsigned int key;

				erec = meta_key_parse(&(yyloc), (yyvsp[-3].string), &key);
				xfree((yyvsp[-3].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.stmt) = meta_stmt_alloc(&(yyloc), key, (yyvsp[-1].expr));
			}
#line 14917 "parser_bison.c"
    break;

  case 976: /* meta_stmt: "notrack"  */
#line 5297 "parser_bison.y"
                        {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 14925 "parser_bison.c"
    break;

  case 977: /* meta_stmt: "flow" "offload" "@" string close_scope_at  */
#line 5301 "parser_bison.y"
                        {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[-1].string));
			}
#line 14933 "parser_bison.c"
    break;

  case 978: /* meta_stmt: "flow" "add" "@" string close_scope_at  */
#line 5305 "parser_bison.y"
                        {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[-1].string));
			}
#line 14941 "parser_bison.c"
    break;

  case 979: /* socket_expr: "socket" socket_key close_scope_socket  */
#line 5311 "parser_bison.y"
                        {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 14949 "parser_bison.c"
    break;

  case 980: /* socket_expr: "socket" "cgroupv2" "level" "number" close_scope_socket  */
#line 5315 "parser_bison.y"
                        {
				(yyval.expr) = socket_expr_alloc(&(yyloc), NFT_SOCKET_CGROUPV2, (yyvsp[-1].val));
			}
#line 14957 "parser_bison.c"
    break;

  case 981: /* socket_key: "transparent"  */
#line 5320 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 14963 "parser_bison.c"
    break;

  case 982: /* socket_key: "mark"  */
#line 5321 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_MARK; }
#line 14969 "parser_bison.c"
    break;

  case 983: /* socket_key: "wildcard"  */
#line 5322 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_WILDCARD; }
#line 14975 "parser_bison.c"
    break;

  case 984: /* offset_opt: %empty  */
#line 5325 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 14981 "parser_bison.c"
    break;

  case 985: /* offset_opt: "offset" "number"  */
#line 5326 "parser_bison.y"
                                                { (yyval.val) = (yyvsp[0].val); }
#line 14987 "parser_bison.c"
    break;

  case 986: /* numgen_type: "inc"  */
#line 5329 "parser_bison.y"
                                                { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 14993 "parser_bison.c"
    break;

  case 987: /* numgen_type: "random"  */
#line 5330 "parser_bison.y"
                                                { (yyval.val) = NFT_NG_RANDOM; }
#line 14999 "parser_bison.c"
    break;

  case 988: /* numgen_expr: "numgen" numgen_type "mod" "number" offset_opt close_scope_numgen  */
#line 5334 "parser_bison.y"
                        {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 15007 "parser_bison.c"
    break;

  case 989: /* xfrm_spnum: "spnum" "number"  */
#line 5339 "parser_bison.y"
                                            { (yyval.val) = (yyvsp[0].val); }
#line 15013 "parser_bison.c"
    break;

  case 990: /* xfrm_spnum: %empty  */
#line 5340 "parser_bison.y"
                                            { (yyval.val) = 0; }
#line 15019 "parser_bison.c"
    break;

  case 991: /* xfrm_dir: "in"  */
#line 5343 "parser_bison.y"
                                        { (yyval.val) = XFRM_POLICY_IN; }
#line 15025 "parser_bison.c"
    break;

  case 992: /* xfrm_dir: "out"  */
#line 5344 "parser_bison.y"
                                        { (yyval.val) = XFRM_POLICY_OUT; }
#line 15031 "parser_bison.c"
    break;

  case 993: /* xfrm_state_key: "spi"  */
#line 5347 "parser_bison.y"
                                    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 15037 "parser_bison.c"
    break;

  case 994: /* xfrm_state_key: "reqid"  */
#line 5348 "parser_bison.y"
                                      { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 15043 "parser_bison.c"
    break;

  case 995: /* xfrm_state_proto_key: "daddr"  */
#line 5351 "parser_bison.y"
                                                { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 15049 "parser_bison.c"
    break;

  case 996: /* xfrm_state_proto_key: "saddr"  */
#line 5352 "parser_bison.y"
                                                { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 15055 "parser_bison.c"
    break;

  case 997: /* xfrm_expr: "ipsec" xfrm_dir xfrm_spnum xfrm_state_key close_scope_ipsec  */
#line 5356 "parser_bison.y"
                        {
				if ((yyvsp[-2].val) > 255) {
					erec_queue(error(&(yylsp[-2]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 15067 "parser_bison.c"
    break;

  case 998: /* xfrm_expr: "ipsec" xfrm_dir xfrm_spnum nf_key_proto xfrm_state_proto_key close_scope_ipsec  */
#line 5364 "parser_bison.y"
                        {
				enum nft_xfrm_keys xfrmk = (yyvsp[-1].val);

				switch ((yyvsp[-2].val)) {
				case NFPROTO_IPV4:
					break;
				case NFPROTO_IPV6:
					if ((yyvsp[-1].val) == NFT_XFRM_KEY_SADDR_IP4)
						xfrmk = NFT_XFRM_KEY_SADDR_IP6;
					else if ((yyvsp[-1].val) == NFT_XFRM_KEY_DADDR_IP4)
						xfrmk = NFT_XFRM_KEY_DADDR_IP6;
					break;
				default:
					YYERROR;
					break;
				}

				if ((yyvsp[-3].val) > 255) {
					erec_queue(error(&(yylsp[-3]), "value too large"), state->msgs);
					YYERROR;
				}

				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-4].val), (yyvsp[-3].val), xfrmk);
			}
#line 15096 "parser_bison.c"
    break;

  case 999: /* hash_expr: "jhash" expr "mod" "number" "seed" "number" offset_opt close_scope_hash  */
#line 5391 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-4].val), true, (yyvsp[-2].val), (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-6].expr);
			}
#line 15105 "parser_bison.c"
    break;

  case 1000: /* hash_expr: "jhash" expr "mod" "number" offset_opt close_scope_hash  */
#line 5396 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-4].expr);
			}
#line 15114 "parser_bison.c"
    break;

  case 1001: /* hash_expr: "symhash" "mod" "number" offset_opt close_scope_hash  */
#line 5401 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_SYM);
			}
#line 15122 "parser_bison.c"
    break;

  case 1002: /* nf_key_proto: "ip" close_scope_ip  */
#line 5406 "parser_bison.y"
                                                       { (yyval.val) = NFPROTO_IPV4; }
#line 15128 "parser_bison.c"
    break;

  case 1003: /* nf_key_proto: "ip6" close_scope_ip6  */
#line 5407 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV6; }
#line 15134 "parser_bison.c"
    break;

  case 1004: /* rt_expr: "rt" rt_key close_scope_rt  */
#line 5411 "parser_bison.y"
                        {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[-1].val), true);
			}
#line 15142 "parser_bison.c"
    break;

  case 1005: /* rt_expr: "rt" nf_key_proto rt_key close_scope_rt  */
#line 5415 "parser_bison.y"
                        {
				enum nft_rt_keys rtk = (yyvsp[-1].val);

				switch ((yyvsp[-2].val)) {
				case NFPROTO_IPV4:
					break;
				case NFPROTO_IPV6:
					if ((yyvsp[-1].val) == NFT_RT_NEXTHOP4)
						rtk = NFT_RT_NEXTHOP6;
					break;
				default:
					YYERROR;
					break;
				}

				(yyval.expr) = rt_expr_alloc(&(yyloc), rtk, false);
			}
#line 15164 "parser_bison.c"
    break;

  case 1006: /* rt_key: "classid"  */
#line 5434 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_CLASSID; }
#line 15170 "parser_bison.c"
    break;

  case 1007: /* rt_key: "nexthop"  */
#line 5435 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 15176 "parser_bison.c"
    break;

  case 1008: /* rt_key: "mtu"  */
#line 5436 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_TCPMSS; }
#line 15182 "parser_bison.c"
    break;

  case 1009: /* rt_key: "ipsec" close_scope_ipsec  */
#line 5437 "parser_bison.y"
                                                          { (yyval.val) = NFT_RT_XFRM; }
#line 15188 "parser_bison.c"
    break;

  case 1010: /* ct_expr: "ct" ct_key close_scope_ct  */
#line 5441 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), -1);
			}
#line 15196 "parser_bison.c"
    break;

  case 1011: /* ct_expr: "ct" ct_dir ct_key_dir close_scope_ct  */
#line 5445 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 15204 "parser_bison.c"
    break;

  case 1012: /* ct_expr: "ct" ct_dir ct_key_proto_field close_scope_ct  */
#line 5449 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 15212 "parser_bison.c"
    break;

  case 1013: /* ct_dir: "original"  */
#line 5454 "parser_bison.y"
                                                { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 15218 "parser_bison.c"
    break;

  case 1014: /* ct_dir: "reply"  */
#line 5455 "parser_bison.y"
                                                { (yyval.val) = IP_CT_DIR_REPLY; }
#line 15224 "parser_bison.c"
    break;

  case 1015: /* ct_key: "l3proto"  */
#line 5458 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 15230 "parser_bison.c"
    break;

  case 1016: /* ct_key: "protocol"  */
#line 5459 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTOCOL; }
#line 15236 "parser_bison.c"
    break;

  case 1017: /* ct_key: "mark"  */
#line 5460 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_MARK; }
#line 15242 "parser_bison.c"
    break;

  case 1018: /* ct_key: "state"  */
#line 5461 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_STATE; }
#line 15248 "parser_bison.c"
    break;

  case 1019: /* ct_key: "direction"  */
#line 5462 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DIRECTION; }
#line 15254 "parser_bison.c"
    break;

  case 1020: /* ct_key: "status"  */
#line 5463 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_STATUS; }
#line 15260 "parser_bison.c"
    break;

  case 1021: /* ct_key: "expiration"  */
#line 5464 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_EXPIRATION; }
#line 15266 "parser_bison.c"
    break;

  case 1022: /* ct_key: "helper"  */
#line 5465 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_HELPER; }
#line 15272 "parser_bison.c"
    break;

  case 1023: /* ct_key: "saddr"  */
#line 5466 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_SRC; }
#line 15278 "parser_bison.c"
    break;

  case 1024: /* ct_key: "daddr"  */
#line 5467 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DST; }
#line 15284 "parser_bison.c"
    break;

  case 1025: /* ct_key: "proto-src"  */
#line 5468 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 15290 "parser_bison.c"
    break;

  case 1026: /* ct_key: "proto-dst"  */
#line 5469 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_DST; }
#line 15296 "parser_bison.c"
    break;

  case 1027: /* ct_key: "label"  */
#line 5470 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_LABELS; }
#line 15302 "parser_bison.c"
    break;

  case 1028: /* ct_key: "event"  */
#line 5471 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_EVENTMASK; }
#line 15308 "parser_bison.c"
    break;

  case 1029: /* ct_key: "secmark" close_scope_secmark  */
#line 5472 "parser_bison.y"
                                                            { (yyval.val) = NFT_CT_SECMARK; }
#line 15314 "parser_bison.c"
    break;

  case 1030: /* ct_key: "id"  */
#line 5473 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_ID; }
#line 15320 "parser_bison.c"
    break;

  case 1032: /* ct_key_dir: "saddr"  */
#line 5477 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_SRC; }
#line 15326 "parser_bison.c"
    break;

  case 1033: /* ct_key_dir: "daddr"  */
#line 5478 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DST; }
#line 15332 "parser_bison.c"
    break;

  case 1034: /* ct_key_dir: "l3proto"  */
#line 5479 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 15338 "parser_bison.c"
    break;

  case 1035: /* ct_key_dir: "protocol"  */
#line 5480 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTOCOL; }
#line 15344 "parser_bison.c"
    break;

  case 1036: /* ct_key_dir: "proto-src"  */
#line 5481 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 15350 "parser_bison.c"
    break;

  case 1037: /* ct_key_dir: "proto-dst"  */
#line 5482 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_DST; }
#line 15356 "parser_bison.c"
    break;

  case 1039: /* ct_key_proto_field: "ip" "saddr" close_scope_ip  */
#line 5486 "parser_bison.y"
                                                               { (yyval.val) = NFT_CT_SRC_IP; }
#line 15362 "parser_bison.c"
    break;

  case 1040: /* ct_key_proto_field: "ip" "daddr" close_scope_ip  */
#line 5487 "parser_bison.y"
                                                               { (yyval.val) = NFT_CT_DST_IP; }
#line 15368 "parser_bison.c"
    break;

  case 1041: /* ct_key_proto_field: "ip6" "saddr" close_scope_ip6  */
#line 5488 "parser_bison.y"
                                                                { (yyval.val) = NFT_CT_SRC_IP6; }
#line 15374 "parser_bison.c"
    break;

  case 1042: /* ct_key_proto_field: "ip6" "daddr" close_scope_ip6  */
#line 5489 "parser_bison.y"
                                                                { (yyval.val) = NFT_CT_DST_IP6; }
#line 15380 "parser_bison.c"
    break;

  case 1043: /* ct_key_dir_optional: "bytes"  */
#line 5492 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_BYTES; }
#line 15386 "parser_bison.c"
    break;

  case 1044: /* ct_key_dir_optional: "packets"  */
#line 5493 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PKTS; }
#line 15392 "parser_bison.c"
    break;

  case 1045: /* ct_key_dir_optional: "avgpkt"  */
#line 5494 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_AVGPKT; }
#line 15398 "parser_bison.c"
    break;

  case 1046: /* ct_key_dir_optional: "zone"  */
#line 5495 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_ZONE; }
#line 15404 "parser_bison.c"
    break;

  case 1049: /* list_stmt_expr: symbol_stmt_expr "comma" symbol_stmt_expr  */
#line 5503 "parser_bison.y"
                        {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 15414 "parser_bison.c"
    break;

  case 1050: /* list_stmt_expr: list_stmt_expr "comma" symbol_stmt_expr  */
#line 5509 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 15424 "parser_bison.c"
    break;

  case 1051: /* ct_stmt: "ct" ct_key "set" stmt_expr close_scope_ct  */
#line 5517 "parser_bison.y"
                        {
				switch ((yyvsp[-3].val)) {
				case NFT_CT_HELPER:
					(yyval.stmt) = objref_stmt_alloc(&(yyloc));
					(yyval.stmt)->objref.type = NFT_OBJECT_CT_HELPER;
					(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
					break;
				default:
					(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-3].val), -1, (yyvsp[-1].expr));
					break;
				}
			}
#line 15441 "parser_bison.c"
    break;

  case 1052: /* ct_stmt: "ct" "timeout" "set" stmt_expr close_scope_ct  */
#line 5530 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);

			}
#line 15452 "parser_bison.c"
    break;

  case 1053: /* ct_stmt: "ct" "expectation" "set" stmt_expr close_scope_ct  */
#line 5537 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 15462 "parser_bison.c"
    break;

  case 1054: /* ct_stmt: "ct" ct_dir ct_key_dir_optional "set" stmt_expr close_scope_ct  */
#line 5543 "parser_bison.y"
                        {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].val), (yyvsp[-1].expr));
			}
#line 15470 "parser_bison.c"
    break;

  case 1055: /* payload_stmt: payload_expr "set" stmt_expr  */
#line 5549 "parser_bison.y"
                        {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 15481 "parser_bison.c"
    break;

  case 1078: /* payload_raw_expr: "@" payload_base_spec "comma" "number" "comma" "number" close_scope_at  */
#line 5582 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-5].val), (yyvsp[-3].val), (yyvsp[-1].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 15492 "parser_bison.c"
    break;

  case 1079: /* payload_base_spec: "ll"  */
#line 5590 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 15498 "parser_bison.c"
    break;

  case 1080: /* payload_base_spec: "nh"  */
#line 5591 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 15504 "parser_bison.c"
    break;

  case 1081: /* payload_base_spec: "th" close_scope_th  */
#line 5592 "parser_bison.y"
                                                                { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 15510 "parser_bison.c"
    break;

  case 1082: /* payload_base_spec: "string"  */
#line 5594 "parser_bison.y"
                        {
				if (!strcmp((yyvsp[0].string), "ih")) {
					(yyval.val) = PROTO_BASE_INNER_HDR;
				} else {
					erec_queue(error(&(yylsp[0]), "unknown raw payload base"), state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}
				xfree((yyvsp[0].string));
			}
#line 15525 "parser_bison.c"
    break;

  case 1083: /* eth_hdr_expr: "ether" eth_hdr_field close_scope_eth  */
#line 5607 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[-1].val));
			}
#line 15533 "parser_bison.c"
    break;

  case 1084: /* eth_hdr_field: "saddr"  */
#line 5612 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_SADDR; }
#line 15539 "parser_bison.c"
    break;

  case 1085: /* eth_hdr_field: "daddr"  */
#line 5613 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_DADDR; }
#line 15545 "parser_bison.c"
    break;

  case 1086: /* eth_hdr_field: "type" close_scope_type  */
#line 5614 "parser_bison.y"
                                                                        { (yyval.val) = ETHHDR_TYPE; }
#line 15551 "parser_bison.c"
    break;

  case 1087: /* vlan_hdr_expr: "vlan" vlan_hdr_field close_scope_vlan  */
#line 5618 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[-1].val));
			}
#line 15559 "parser_bison.c"
    break;

  case 1088: /* vlan_hdr_field: "id"  */
#line 5623 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_VID; }
#line 15565 "parser_bison.c"
    break;

  case 1089: /* vlan_hdr_field: "cfi"  */
#line 5624 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_CFI; }
#line 15571 "parser_bison.c"
    break;

  case 1090: /* vlan_hdr_field: "dei"  */
#line 5625 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_DEI; }
#line 15577 "parser_bison.c"
    break;

  case 1091: /* vlan_hdr_field: "pcp"  */
#line 5626 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_PCP; }
#line 15583 "parser_bison.c"
    break;

  case 1092: /* vlan_hdr_field: "type" close_scope_type  */
#line 5627 "parser_bison.y"
                                                                        { (yyval.val) = VLANHDR_TYPE; }
#line 15589 "parser_bison.c"
    break;

  case 1093: /* arp_hdr_expr: "arp" arp_hdr_field close_scope_arp  */
#line 5631 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[-1].val));
			}
#line 15597 "parser_bison.c"
    break;

  case 1094: /* arp_hdr_field: "htype"  */
#line 5636 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_HRD; }
#line 15603 "parser_bison.c"
    break;

  case 1095: /* arp_hdr_field: "ptype"  */
#line 5637 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_PRO; }
#line 15609 "parser_bison.c"
    break;

  case 1096: /* arp_hdr_field: "hlen"  */
#line 5638 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_HLN; }
#line 15615 "parser_bison.c"
    break;

  case 1097: /* arp_hdr_field: "plen"  */
#line 5639 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_PLN; }
#line 15621 "parser_bison.c"
    break;

  case 1098: /* arp_hdr_field: "operation"  */
#line 5640 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_OP; }
#line 15627 "parser_bison.c"
    break;

  case 1099: /* arp_hdr_field: "saddr" "ether" close_scope_eth  */
#line 5641 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 15633 "parser_bison.c"
    break;

  case 1100: /* arp_hdr_field: "daddr" "ether" close_scope_eth  */
#line 5642 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 15639 "parser_bison.c"
    break;

  case 1101: /* arp_hdr_field: "saddr" "ip" close_scope_ip  */
#line 5643 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_SADDR_IP; }
#line 15645 "parser_bison.c"
    break;

  case 1102: /* arp_hdr_field: "daddr" "ip" close_scope_ip  */
#line 5644 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_DADDR_IP; }
#line 15651 "parser_bison.c"
    break;

  case 1103: /* ip_hdr_expr: "ip" ip_hdr_field close_scope_ip  */
#line 5648 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[-1].val));
			}
#line 15659 "parser_bison.c"
    break;

  case 1104: /* ip_hdr_expr: "ip" "option" ip_option_type ip_option_field close_scope_ip  */
#line 5652 "parser_bison.y"
                        {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val));
				if (!(yyval.expr)) {
					erec_queue(error(&(yylsp[-4]), "unknown ip option type/field"), state->msgs);
					YYERROR;
				}
			}
#line 15671 "parser_bison.c"
    break;

  case 1105: /* ip_hdr_expr: "ip" "option" ip_option_type close_scope_ip  */
#line 5660 "parser_bison.y"
                        {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), IPOPT_FIELD_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 15680 "parser_bison.c"
    break;

  case 1106: /* ip_hdr_field: "version"  */
#line 5666 "parser_bison.y"
                                                { (yyval.val) = IPHDR_VERSION; }
#line 15686 "parser_bison.c"
    break;

  case 1107: /* ip_hdr_field: "hdrlength"  */
#line 5667 "parser_bison.y"
                                                { (yyval.val) = IPHDR_HDRLENGTH; }
#line 15692 "parser_bison.c"
    break;

  case 1108: /* ip_hdr_field: "dscp"  */
#line 5668 "parser_bison.y"
                                                { (yyval.val) = IPHDR_DSCP; }
#line 15698 "parser_bison.c"
    break;

  case 1109: /* ip_hdr_field: "ecn"  */
#line 5669 "parser_bison.y"
                                                { (yyval.val) = IPHDR_ECN; }
#line 15704 "parser_bison.c"
    break;

  case 1110: /* ip_hdr_field: "length"  */
#line 5670 "parser_bison.y"
                                                { (yyval.val) = IPHDR_LENGTH; }
#line 15710 "parser_bison.c"
    break;

  case 1111: /* ip_hdr_field: "id"  */
#line 5671 "parser_bison.y"
                                                { (yyval.val) = IPHDR_ID; }
#line 15716 "parser_bison.c"
    break;

  case 1112: /* ip_hdr_field: "frag-off"  */
#line 5672 "parser_bison.y"
                                                { (yyval.val) = IPHDR_FRAG_OFF; }
#line 15722 "parser_bison.c"
    break;

  case 1113: /* ip_hdr_field: "ttl"  */
#line 5673 "parser_bison.y"
                                                { (yyval.val) = IPHDR_TTL; }
#line 15728 "parser_bison.c"
    break;

  case 1114: /* ip_hdr_field: "protocol"  */
#line 5674 "parser_bison.y"
                                                { (yyval.val) = IPHDR_PROTOCOL; }
#line 15734 "parser_bison.c"
    break;

  case 1115: /* ip_hdr_field: "checksum"  */
#line 5675 "parser_bison.y"
                                                { (yyval.val) = IPHDR_CHECKSUM; }
#line 15740 "parser_bison.c"
    break;

  case 1116: /* ip_hdr_field: "saddr"  */
#line 5676 "parser_bison.y"
                                                { (yyval.val) = IPHDR_SADDR; }
#line 15746 "parser_bison.c"
    break;

  case 1117: /* ip_hdr_field: "daddr"  */
#line 5677 "parser_bison.y"
                                                { (yyval.val) = IPHDR_DADDR; }
#line 15752 "parser_bison.c"
    break;

  case 1118: /* ip_option_type: "lsrr"  */
#line 5680 "parser_bison.y"
                                                { (yyval.val) = IPOPT_LSRR; }
#line 15758 "parser_bison.c"
    break;

  case 1119: /* ip_option_type: "rr"  */
#line 5681 "parser_bison.y"
                                                { (yyval.val) = IPOPT_RR; }
#line 15764 "parser_bison.c"
    break;

  case 1120: /* ip_option_type: "ssrr"  */
#line 5682 "parser_bison.y"
                                                { (yyval.val) = IPOPT_SSRR; }
#line 15770 "parser_bison.c"
    break;

  case 1121: /* ip_option_type: "ra"  */
#line 5683 "parser_bison.y"
                                                { (yyval.val) = IPOPT_RA; }
#line 15776 "parser_bison.c"
    break;

  case 1122: /* ip_option_field: "type" close_scope_type  */
#line 5686 "parser_bison.y"
                                                                        { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 15782 "parser_bison.c"
    break;

  case 1123: /* ip_option_field: "length"  */
#line 5687 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 15788 "parser_bison.c"
    break;

  case 1124: /* ip_option_field: "value"  */
#line 5688 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 15794 "parser_bison.c"
    break;

  case 1125: /* ip_option_field: "ptr"  */
#line 5689 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_PTR; }
#line 15800 "parser_bison.c"
    break;

  case 1126: /* ip_option_field: "addr"  */
#line 5690 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 15806 "parser_bison.c"
    break;

  case 1127: /* icmp_hdr_expr: "icmp" icmp_hdr_field close_scope_icmp  */
#line 5694 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[-1].val));
			}
#line 15814 "parser_bison.c"
    break;

  case 1128: /* icmp_hdr_field: "type" close_scope_type  */
#line 5699 "parser_bison.y"
                                                                        { (yyval.val) = ICMPHDR_TYPE; }
#line 15820 "parser_bison.c"
    break;

  case 1129: /* icmp_hdr_field: "code"  */
#line 5700 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_CODE; }
#line 15826 "parser_bison.c"
    break;

  case 1130: /* icmp_hdr_field: "checksum"  */
#line 5701 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 15832 "parser_bison.c"
    break;

  case 1131: /* icmp_hdr_field: "id"  */
#line 5702 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_ID; }
#line 15838 "parser_bison.c"
    break;

  case 1132: /* icmp_hdr_field: "seq"  */
#line 5703 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_SEQ; }
#line 15844 "parser_bison.c"
    break;

  case 1133: /* icmp_hdr_field: "gateway"  */
#line 5704 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_GATEWAY; }
#line 15850 "parser_bison.c"
    break;

  case 1134: /* icmp_hdr_field: "mtu"  */
#line 5705 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_MTU; }
#line 15856 "parser_bison.c"
    break;

  case 1135: /* igmp_hdr_expr: "igmp" igmp_hdr_field close_scope_igmp  */
#line 5709 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[-1].val));
			}
#line 15864 "parser_bison.c"
    break;

  case 1136: /* igmp_hdr_field: "type" close_scope_type  */
#line 5714 "parser_bison.y"
                                                                        { (yyval.val) = IGMPHDR_TYPE; }
#line 15870 "parser_bison.c"
    break;

  case 1137: /* igmp_hdr_field: "checksum"  */
#line 5715 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 15876 "parser_bison.c"
    break;

  case 1138: /* igmp_hdr_field: "mrt"  */
#line 5716 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_MRT; }
#line 15882 "parser_bison.c"
    break;

  case 1139: /* igmp_hdr_field: "group"  */
#line 5717 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_GROUP; }
#line 15888 "parser_bison.c"
    break;

  case 1140: /* ip6_hdr_expr: "ip6" ip6_hdr_field close_scope_ip6  */
#line 5721 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[-1].val));
			}
#line 15896 "parser_bison.c"
    break;

  case 1141: /* ip6_hdr_field: "version"  */
#line 5726 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_VERSION; }
#line 15902 "parser_bison.c"
    break;

  case 1142: /* ip6_hdr_field: "dscp"  */
#line 5727 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_DSCP; }
#line 15908 "parser_bison.c"
    break;

  case 1143: /* ip6_hdr_field: "ecn"  */
#line 5728 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_ECN; }
#line 15914 "parser_bison.c"
    break;

  case 1144: /* ip6_hdr_field: "flowlabel"  */
#line 5729 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 15920 "parser_bison.c"
    break;

  case 1145: /* ip6_hdr_field: "length"  */
#line 5730 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_LENGTH; }
#line 15926 "parser_bison.c"
    break;

  case 1146: /* ip6_hdr_field: "nexthdr"  */
#line 5731 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_NEXTHDR; }
#line 15932 "parser_bison.c"
    break;

  case 1147: /* ip6_hdr_field: "hoplimit"  */
#line 5732 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 15938 "parser_bison.c"
    break;

  case 1148: /* ip6_hdr_field: "saddr"  */
#line 5733 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_SADDR; }
#line 15944 "parser_bison.c"
    break;

  case 1149: /* ip6_hdr_field: "daddr"  */
#line 5734 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_DADDR; }
#line 15950 "parser_bison.c"
    break;

  case 1150: /* icmp6_hdr_expr: "icmpv6" icmp6_hdr_field close_scope_icmp  */
#line 5737 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[-1].val));
			}
#line 15958 "parser_bison.c"
    break;

  case 1151: /* icmp6_hdr_field: "type" close_scope_type  */
#line 5742 "parser_bison.y"
                                                                        { (yyval.val) = ICMP6HDR_TYPE; }
#line 15964 "parser_bison.c"
    break;

  case 1152: /* icmp6_hdr_field: "code"  */
#line 5743 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_CODE; }
#line 15970 "parser_bison.c"
    break;

  case 1153: /* icmp6_hdr_field: "checksum"  */
#line 5744 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 15976 "parser_bison.c"
    break;

  case 1154: /* icmp6_hdr_field: "param-problem"  */
#line 5745 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_PPTR; }
#line 15982 "parser_bison.c"
    break;

  case 1155: /* icmp6_hdr_field: "mtu"  */
#line 5746 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_MTU; }
#line 15988 "parser_bison.c"
    break;

  case 1156: /* icmp6_hdr_field: "id"  */
#line 5747 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_ID; }
#line 15994 "parser_bison.c"
    break;

  case 1157: /* icmp6_hdr_field: "seq"  */
#line 5748 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_SEQ; }
#line 16000 "parser_bison.c"
    break;

  case 1158: /* icmp6_hdr_field: "max-delay"  */
#line 5749 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 16006 "parser_bison.c"
    break;

  case 1159: /* icmp6_hdr_field: "taddr"  */
#line 5750 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_TADDR; }
#line 16012 "parser_bison.c"
    break;

  case 1160: /* icmp6_hdr_field: "daddr"  */
#line 5751 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_DADDR; }
#line 16018 "parser_bison.c"
    break;

  case 1161: /* auth_hdr_expr: "ah" auth_hdr_field close_scope_ah  */
#line 5755 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[-1].val));
			}
#line 16026 "parser_bison.c"
    break;

  case 1162: /* auth_hdr_field: "nexthdr"  */
#line 5760 "parser_bison.y"
                                                { (yyval.val) = AHHDR_NEXTHDR; }
#line 16032 "parser_bison.c"
    break;

  case 1163: /* auth_hdr_field: "hdrlength"  */
#line 5761 "parser_bison.y"
                                                { (yyval.val) = AHHDR_HDRLENGTH; }
#line 16038 "parser_bison.c"
    break;

  case 1164: /* auth_hdr_field: "reserved"  */
#line 5762 "parser_bison.y"
                                                { (yyval.val) = AHHDR_RESERVED; }
#line 16044 "parser_bison.c"
    break;

  case 1165: /* auth_hdr_field: "spi"  */
#line 5763 "parser_bison.y"
                                                { (yyval.val) = AHHDR_SPI; }
#line 16050 "parser_bison.c"
    break;

  case 1166: /* auth_hdr_field: "seq"  */
#line 5764 "parser_bison.y"
                                                { (yyval.val) = AHHDR_SEQUENCE; }
#line 16056 "parser_bison.c"
    break;

  case 1167: /* esp_hdr_expr: "esp" esp_hdr_field close_scope_esp  */
#line 5768 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[-1].val));
			}
#line 16064 "parser_bison.c"
    break;

  case 1168: /* esp_hdr_field: "spi"  */
#line 5773 "parser_bison.y"
                                                { (yyval.val) = ESPHDR_SPI; }
#line 16070 "parser_bison.c"
    break;

  case 1169: /* esp_hdr_field: "seq"  */
#line 5774 "parser_bison.y"
                                                { (yyval.val) = ESPHDR_SEQUENCE; }
#line 16076 "parser_bison.c"
    break;

  case 1170: /* comp_hdr_expr: "comp" comp_hdr_field close_scope_comp  */
#line 5778 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[-1].val));
			}
#line 16084 "parser_bison.c"
    break;

  case 1171: /* comp_hdr_field: "nexthdr"  */
#line 5783 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_NEXTHDR; }
#line 16090 "parser_bison.c"
    break;

  case 1172: /* comp_hdr_field: "flags"  */
#line 5784 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_FLAGS; }
#line 16096 "parser_bison.c"
    break;

  case 1173: /* comp_hdr_field: "cpi"  */
#line 5785 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_CPI; }
#line 16102 "parser_bison.c"
    break;

  case 1174: /* udp_hdr_expr: "udp" udp_hdr_field close_scope_udp  */
#line 5789 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[-1].val));
			}
#line 16110 "parser_bison.c"
    break;

  case 1175: /* udp_hdr_field: "sport"  */
#line 5794 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_SPORT; }
#line 16116 "parser_bison.c"
    break;

  case 1176: /* udp_hdr_field: "dport"  */
#line 5795 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_DPORT; }
#line 16122 "parser_bison.c"
    break;

  case 1177: /* udp_hdr_field: "length"  */
#line 5796 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_LENGTH; }
#line 16128 "parser_bison.c"
    break;

  case 1178: /* udp_hdr_field: "checksum"  */
#line 5797 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_CHECKSUM; }
#line 16134 "parser_bison.c"
    break;

  case 1179: /* udplite_hdr_expr: "udplite" udplite_hdr_field close_scope_udplite  */
#line 5801 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[-1].val));
			}
#line 16142 "parser_bison.c"
    break;

  case 1180: /* udplite_hdr_field: "sport"  */
#line 5806 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_SPORT; }
#line 16148 "parser_bison.c"
    break;

  case 1181: /* udplite_hdr_field: "dport"  */
#line 5807 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_DPORT; }
#line 16154 "parser_bison.c"
    break;

  case 1182: /* udplite_hdr_field: "csumcov"  */
#line 5808 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_LENGTH; }
#line 16160 "parser_bison.c"
    break;

  case 1183: /* udplite_hdr_field: "checksum"  */
#line 5809 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_CHECKSUM; }
#line 16166 "parser_bison.c"
    break;

  case 1184: /* tcp_hdr_expr: "tcp" tcp_hdr_field  */
#line 5813 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 16174 "parser_bison.c"
    break;

  case 1185: /* tcp_hdr_expr: "tcp" "option" tcp_hdr_option_type  */
#line 5817 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPT_COMMON_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 16183 "parser_bison.c"
    break;

  case 1186: /* tcp_hdr_expr: "tcp" "option" tcp_hdr_option_kind_and_field  */
#line 5822 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].tcp_kind_field).kind, (yyvsp[0].tcp_kind_field).field);
			}
#line 16191 "parser_bison.c"
    break;

  case 1187: /* tcp_hdr_expr: "tcp" "option" "@" close_scope_at tcp_hdr_option_type "comma" "number" "comma" "number"  */
#line 5826 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-4].val), 0);
				tcpopt_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val), 0);
			}
#line 16200 "parser_bison.c"
    break;

  case 1207: /* vxlan_hdr_expr: "vxlan" vxlan_hdr_field  */
#line 5858 "parser_bison.y"
                        {
				struct expr *expr;

				expr = payload_expr_alloc(&(yyloc), &proto_vxlan, (yyvsp[0].val));
				expr->payload.inner_desc = &proto_vxlan;
				(yyval.expr) = expr;
			}
#line 16212 "parser_bison.c"
    break;

  case 1208: /* vxlan_hdr_expr: "vxlan" inner_expr  */
#line 5866 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->location = (yyloc);
				(yyval.expr)->payload.inner_desc = &proto_vxlan;
			}
#line 16222 "parser_bison.c"
    break;

  case 1209: /* vxlan_hdr_field: "vni"  */
#line 5873 "parser_bison.y"
                                                        { (yyval.val) = VXLANHDR_VNI; }
#line 16228 "parser_bison.c"
    break;

  case 1210: /* vxlan_hdr_field: "flags"  */
#line 5874 "parser_bison.y"
                                                        { (yyval.val) = VXLANHDR_FLAGS; }
#line 16234 "parser_bison.c"
    break;

  case 1211: /* geneve_hdr_expr: "geneve" geneve_hdr_field  */
#line 5878 "parser_bison.y"
                        {
				struct expr *expr;

				expr = payload_expr_alloc(&(yyloc), &proto_geneve, (yyvsp[0].val));
				expr->payload.inner_desc = &proto_geneve;
				(yyval.expr) = expr;
			}
#line 16246 "parser_bison.c"
    break;

  case 1212: /* geneve_hdr_expr: "geneve" inner_expr  */
#line 5886 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->location = (yyloc);
				(yyval.expr)->payload.inner_desc = &proto_geneve;
			}
#line 16256 "parser_bison.c"
    break;

  case 1213: /* geneve_hdr_field: "vni"  */
#line 5893 "parser_bison.y"
                                                        { (yyval.val) = GNVHDR_VNI; }
#line 16262 "parser_bison.c"
    break;

  case 1214: /* geneve_hdr_field: "type"  */
#line 5894 "parser_bison.y"
                                                        { (yyval.val) = GNVHDR_TYPE; }
#line 16268 "parser_bison.c"
    break;

  case 1215: /* gre_hdr_expr: "gre" gre_hdr_field close_scope_gre  */
#line 5898 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_gre, (yyvsp[-1].val));
			}
#line 16276 "parser_bison.c"
    break;

  case 1216: /* gre_hdr_expr: "gre" close_scope_gre inner_inet_expr  */
#line 5902 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->payload.inner_desc = &proto_gre;
			}
#line 16285 "parser_bison.c"
    break;

  case 1217: /* gre_hdr_field: "version"  */
#line 5908 "parser_bison.y"
                                                        { (yyval.val) = GREHDR_VERSION;	}
#line 16291 "parser_bison.c"
    break;

  case 1218: /* gre_hdr_field: "flags"  */
#line 5909 "parser_bison.y"
                                                        { (yyval.val) = GREHDR_FLAGS; }
#line 16297 "parser_bison.c"
    break;

  case 1219: /* gre_hdr_field: "protocol"  */
#line 5910 "parser_bison.y"
                                                        { (yyval.val) = GREHDR_PROTOCOL; }
#line 16303 "parser_bison.c"
    break;

  case 1220: /* gretap_hdr_expr: "gretap" close_scope_gre inner_expr  */
#line 5914 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->payload.inner_desc = &proto_gretap;
			}
#line 16312 "parser_bison.c"
    break;

  case 1221: /* optstrip_stmt: "reset" "tcp" "option" tcp_hdr_option_type close_scope_tcp  */
#line 5921 "parser_bison.y"
                        {
				(yyval.stmt) = optstrip_stmt_alloc(&(yyloc), tcpopt_expr_alloc(&(yyloc),
										(yyvsp[-1].val), TCPOPT_COMMON_KIND));
			}
#line 16321 "parser_bison.c"
    break;

  case 1222: /* tcp_hdr_field: "sport"  */
#line 5927 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_SPORT; }
#line 16327 "parser_bison.c"
    break;

  case 1223: /* tcp_hdr_field: "dport"  */
#line 5928 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_DPORT; }
#line 16333 "parser_bison.c"
    break;

  case 1224: /* tcp_hdr_field: "seq"  */
#line 5929 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_SEQ; }
#line 16339 "parser_bison.c"
    break;

  case 1225: /* tcp_hdr_field: "ackseq"  */
#line 5930 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_ACKSEQ; }
#line 16345 "parser_bison.c"
    break;

  case 1226: /* tcp_hdr_field: "doff"  */
#line 5931 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_DOFF; }
#line 16351 "parser_bison.c"
    break;

  case 1227: /* tcp_hdr_field: "reserved"  */
#line 5932 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_RESERVED; }
#line 16357 "parser_bison.c"
    break;

  case 1228: /* tcp_hdr_field: "flags"  */
#line 5933 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_FLAGS; }
#line 16363 "parser_bison.c"
    break;

  case 1229: /* tcp_hdr_field: "window"  */
#line 5934 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_WINDOW; }
#line 16369 "parser_bison.c"
    break;

  case 1230: /* tcp_hdr_field: "checksum"  */
#line 5935 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_CHECKSUM; }
#line 16375 "parser_bison.c"
    break;

  case 1231: /* tcp_hdr_field: "urgptr"  */
#line 5936 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_URGPTR; }
#line 16381 "parser_bison.c"
    break;

  case 1232: /* tcp_hdr_option_kind_and_field: "mss" tcpopt_field_maxseg  */
#line 5940 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_MAXSEG, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16390 "parser_bison.c"
    break;

  case 1233: /* tcp_hdr_option_kind_and_field: tcp_hdr_option_sack tcpopt_field_sack  */
#line 5945 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = (yyvsp[-1].val), .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16399 "parser_bison.c"
    break;

  case 1234: /* tcp_hdr_option_kind_and_field: "window" tcpopt_field_window  */
#line 5950 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_WINDOW, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16408 "parser_bison.c"
    break;

  case 1235: /* tcp_hdr_option_kind_and_field: "timestamp" tcpopt_field_tsopt  */
#line 5955 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_TIMESTAMP, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16417 "parser_bison.c"
    break;

  case 1236: /* tcp_hdr_option_kind_and_field: tcp_hdr_option_type "length"  */
#line 5960 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = (yyvsp[-1].val), .field = TCPOPT_COMMON_LENGTH };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16426 "parser_bison.c"
    break;

  case 1237: /* tcp_hdr_option_kind_and_field: "mptcp" tcpopt_field_mptcp  */
#line 5965 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_MPTCP, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16435 "parser_bison.c"
    break;

  case 1238: /* tcp_hdr_option_sack: "sack"  */
#line 5971 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK; }
#line 16441 "parser_bison.c"
    break;

  case 1239: /* tcp_hdr_option_sack: "sack0"  */
#line 5972 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK; }
#line 16447 "parser_bison.c"
    break;

  case 1240: /* tcp_hdr_option_sack: "sack1"  */
#line 5973 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK1; }
#line 16453 "parser_bison.c"
    break;

  case 1241: /* tcp_hdr_option_sack: "sack2"  */
#line 5974 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK2; }
#line 16459 "parser_bison.c"
    break;

  case 1242: /* tcp_hdr_option_sack: "sack3"  */
#line 5975 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK3; }
#line 16465 "parser_bison.c"
    break;

  case 1243: /* tcp_hdr_option_type: "echo"  */
#line 5978 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_ECHO; }
#line 16471 "parser_bison.c"
    break;

  case 1244: /* tcp_hdr_option_type: "eol"  */
#line 5979 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_EOL; }
#line 16477 "parser_bison.c"
    break;

  case 1245: /* tcp_hdr_option_type: "fastopen"  */
#line 5980 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_FASTOPEN; }
#line 16483 "parser_bison.c"
    break;

  case 1246: /* tcp_hdr_option_type: "md5sig"  */
#line 5981 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MD5SIG; }
#line 16489 "parser_bison.c"
    break;

  case 1247: /* tcp_hdr_option_type: "mptcp"  */
#line 5982 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MPTCP; }
#line 16495 "parser_bison.c"
    break;

  case 1248: /* tcp_hdr_option_type: "mss"  */
#line 5983 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MAXSEG; }
#line 16501 "parser_bison.c"
    break;

  case 1249: /* tcp_hdr_option_type: "nop"  */
#line 5984 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_NOP; }
#line 16507 "parser_bison.c"
    break;

  case 1250: /* tcp_hdr_option_type: "sack-permitted"  */
#line 5985 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_SACK_PERMITTED; }
#line 16513 "parser_bison.c"
    break;

  case 1251: /* tcp_hdr_option_type: "timestamp"  */
#line 5986 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_TIMESTAMP; }
#line 16519 "parser_bison.c"
    break;

  case 1252: /* tcp_hdr_option_type: "window"  */
#line 5987 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_WINDOW; }
#line 16525 "parser_bison.c"
    break;

  case 1253: /* tcp_hdr_option_type: tcp_hdr_option_sack  */
#line 5988 "parser_bison.y"
                                                        { (yyval.val) = (yyvsp[0].val); }
#line 16531 "parser_bison.c"
    break;

  case 1254: /* tcp_hdr_option_type: "number"  */
#line 5989 "parser_bison.y"
                                                        {
				if ((yyvsp[0].val) > 255) {
					erec_queue(error(&(yylsp[0]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[0].val);
			}
#line 16543 "parser_bison.c"
    break;

  case 1255: /* tcpopt_field_sack: "left"  */
#line 5998 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_SACK_LEFT; }
#line 16549 "parser_bison.c"
    break;

  case 1256: /* tcpopt_field_sack: "right"  */
#line 5999 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_SACK_RIGHT; }
#line 16555 "parser_bison.c"
    break;

  case 1257: /* tcpopt_field_window: "count"  */
#line 6002 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_WINDOW_COUNT; }
#line 16561 "parser_bison.c"
    break;

  case 1258: /* tcpopt_field_tsopt: "tsval"  */
#line 6005 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_TS_TSVAL; }
#line 16567 "parser_bison.c"
    break;

  case 1259: /* tcpopt_field_tsopt: "tsecr"  */
#line 6006 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_TS_TSECR; }
#line 16573 "parser_bison.c"
    break;

  case 1260: /* tcpopt_field_maxseg: "size"  */
#line 6009 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_MAXSEG_SIZE; }
#line 16579 "parser_bison.c"
    break;

  case 1261: /* tcpopt_field_mptcp: "subtype"  */
#line 6012 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_MPTCP_SUBTYPE; }
#line 16585 "parser_bison.c"
    break;

  case 1262: /* dccp_hdr_expr: "dccp" dccp_hdr_field close_scope_dccp  */
#line 6016 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[-1].val));
			}
#line 16593 "parser_bison.c"
    break;

  case 1263: /* dccp_hdr_expr: "dccp" "option" "number" close_scope_dccp  */
#line 6020 "parser_bison.y"
                        {
				if ((yyvsp[-1].val) > DCCPOPT_TYPE_MAX) {
					erec_queue(error(&(yylsp[-3]), "value too large"),
						   state->msgs);
					YYERROR;
				}
				(yyval.expr) = dccpopt_expr_alloc(&(yyloc), (yyvsp[-1].val));
			}
#line 16606 "parser_bison.c"
    break;

  case 1264: /* dccp_hdr_field: "sport"  */
#line 6030 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_SPORT; }
#line 16612 "parser_bison.c"
    break;

  case 1265: /* dccp_hdr_field: "dport"  */
#line 6031 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_DPORT; }
#line 16618 "parser_bison.c"
    break;

  case 1266: /* dccp_hdr_field: "type" close_scope_type  */
#line 6032 "parser_bison.y"
                                                                        { (yyval.val) = DCCPHDR_TYPE; }
#line 16624 "parser_bison.c"
    break;

  case 1267: /* sctp_chunk_type: "data"  */
#line 6035 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_DATA; }
#line 16630 "parser_bison.c"
    break;

  case 1268: /* sctp_chunk_type: "init"  */
#line 6036 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_INIT; }
#line 16636 "parser_bison.c"
    break;

  case 1269: /* sctp_chunk_type: "init-ack"  */
#line 6037 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_INIT_ACK; }
#line 16642 "parser_bison.c"
    break;

  case 1270: /* sctp_chunk_type: "sack"  */
#line 6038 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SACK; }
#line 16648 "parser_bison.c"
    break;

  case 1271: /* sctp_chunk_type: "heartbeat"  */
#line 6039 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT; }
#line 16654 "parser_bison.c"
    break;

  case 1272: /* sctp_chunk_type: "heartbeat-ack"  */
#line 6040 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT_ACK; }
#line 16660 "parser_bison.c"
    break;

  case 1273: /* sctp_chunk_type: "abort"  */
#line 6041 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ABORT; }
#line 16666 "parser_bison.c"
    break;

  case 1274: /* sctp_chunk_type: "shutdown"  */
#line 6042 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN; }
#line 16672 "parser_bison.c"
    break;

  case 1275: /* sctp_chunk_type: "shutdown-ack"  */
#line 6043 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_ACK; }
#line 16678 "parser_bison.c"
    break;

  case 1276: /* sctp_chunk_type: "error"  */
#line 6044 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ERROR; }
#line 16684 "parser_bison.c"
    break;

  case 1277: /* sctp_chunk_type: "cookie-echo"  */
#line 6045 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ECHO; }
#line 16690 "parser_bison.c"
    break;

  case 1278: /* sctp_chunk_type: "cookie-ack"  */
#line 6046 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ACK; }
#line 16696 "parser_bison.c"
    break;

  case 1279: /* sctp_chunk_type: "ecne"  */
#line 6047 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ECNE; }
#line 16702 "parser_bison.c"
    break;

  case 1280: /* sctp_chunk_type: "cwr"  */
#line 6048 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_CWR; }
#line 16708 "parser_bison.c"
    break;

  case 1281: /* sctp_chunk_type: "shutdown-complete"  */
#line 6049 "parser_bison.y"
                                                  { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_COMPLETE; }
#line 16714 "parser_bison.c"
    break;

  case 1282: /* sctp_chunk_type: "asconf-ack"  */
#line 6050 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF_ACK; }
#line 16720 "parser_bison.c"
    break;

  case 1283: /* sctp_chunk_type: "forward-tsn"  */
#line 6051 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_FORWARD_TSN; }
#line 16726 "parser_bison.c"
    break;

  case 1284: /* sctp_chunk_type: "asconf"  */
#line 6052 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF; }
#line 16732 "parser_bison.c"
    break;

  case 1285: /* sctp_chunk_common_field: "type" close_scope_type  */
#line 6055 "parser_bison.y"
                                                                { (yyval.val) = SCTP_CHUNK_COMMON_TYPE; }
#line 16738 "parser_bison.c"
    break;

  case 1286: /* sctp_chunk_common_field: "flags"  */
#line 6056 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_FLAGS; }
#line 16744 "parser_bison.c"
    break;

  case 1287: /* sctp_chunk_common_field: "length"  */
#line 6057 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_LENGTH; }
#line 16750 "parser_bison.c"
    break;

  case 1288: /* sctp_chunk_data_field: "tsn"  */
#line 6060 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_TSN; }
#line 16756 "parser_bison.c"
    break;

  case 1289: /* sctp_chunk_data_field: "stream"  */
#line 6061 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_STREAM; }
#line 16762 "parser_bison.c"
    break;

  case 1290: /* sctp_chunk_data_field: "ssn"  */
#line 6062 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_SSN; }
#line 16768 "parser_bison.c"
    break;

  case 1291: /* sctp_chunk_data_field: "ppid"  */
#line 6063 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_PPID; }
#line 16774 "parser_bison.c"
    break;

  case 1292: /* sctp_chunk_init_field: "init-tag"  */
#line 6066 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_TAG; }
#line 16780 "parser_bison.c"
    break;

  case 1293: /* sctp_chunk_init_field: "a-rwnd"  */
#line 6067 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_RWND; }
#line 16786 "parser_bison.c"
    break;

  case 1294: /* sctp_chunk_init_field: "num-outbound-streams"  */
#line 6068 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_OSTREAMS; }
#line 16792 "parser_bison.c"
    break;

  case 1295: /* sctp_chunk_init_field: "num-inbound-streams"  */
#line 6069 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_ISTREAMS; }
#line 16798 "parser_bison.c"
    break;

  case 1296: /* sctp_chunk_init_field: "initial-tsn"  */
#line 6070 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_TSN; }
#line 16804 "parser_bison.c"
    break;

  case 1297: /* sctp_chunk_sack_field: "cum-tsn-ack"  */
#line 6073 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_CTSN_ACK; }
#line 16810 "parser_bison.c"
    break;

  case 1298: /* sctp_chunk_sack_field: "a-rwnd"  */
#line 6074 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_RWND; }
#line 16816 "parser_bison.c"
    break;

  case 1299: /* sctp_chunk_sack_field: "num-gap-ack-blocks"  */
#line 6075 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_GACK_BLOCKS; }
#line 16822 "parser_bison.c"
    break;

  case 1300: /* sctp_chunk_sack_field: "num-dup-tsns"  */
#line 6076 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_DUP_TSNS; }
#line 16828 "parser_bison.c"
    break;

  case 1301: /* sctp_chunk_alloc: sctp_chunk_type  */
#line 6080 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[0].val), SCTP_CHUNK_COMMON_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 16837 "parser_bison.c"
    break;

  case 1302: /* sctp_chunk_alloc: sctp_chunk_type sctp_chunk_common_field  */
#line 6085 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 16845 "parser_bison.c"
    break;

  case 1303: /* sctp_chunk_alloc: "data" sctp_chunk_data_field  */
#line 6089 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_DATA, (yyvsp[0].val));
			}
#line 16853 "parser_bison.c"
    break;

  case 1304: /* sctp_chunk_alloc: "init" sctp_chunk_init_field  */
#line 6093 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT, (yyvsp[0].val));
			}
#line 16861 "parser_bison.c"
    break;

  case 1305: /* sctp_chunk_alloc: "init-ack" sctp_chunk_init_field  */
#line 6097 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT_ACK, (yyvsp[0].val));
			}
#line 16869 "parser_bison.c"
    break;

  case 1306: /* sctp_chunk_alloc: "sack" sctp_chunk_sack_field  */
#line 6101 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SACK, (yyvsp[0].val));
			}
#line 16877 "parser_bison.c"
    break;

  case 1307: /* sctp_chunk_alloc: "shutdown" "cum-tsn-ack"  */
#line 6105 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SHUTDOWN,
							   SCTP_CHUNK_SHUTDOWN_CTSN_ACK);
			}
#line 16886 "parser_bison.c"
    break;

  case 1308: /* sctp_chunk_alloc: "ecne" "lowest-tsn"  */
#line 6110 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ECNE,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 16895 "parser_bison.c"
    break;

  case 1309: /* sctp_chunk_alloc: "cwr" "lowest-tsn"  */
#line 6115 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_CWR,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 16904 "parser_bison.c"
    break;

  case 1310: /* sctp_chunk_alloc: "asconf-ack" "seqno"  */
#line 6120 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF_ACK,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 16913 "parser_bison.c"
    break;

  case 1311: /* sctp_chunk_alloc: "forward-tsn" "new-cum-tsn"  */
#line 6125 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_FORWARD_TSN,
							   SCTP_CHUNK_FORWARD_TSN_NCTSN);
			}
#line 16922 "parser_bison.c"
    break;

  case 1312: /* sctp_chunk_alloc: "asconf" "seqno"  */
#line 6130 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 16931 "parser_bison.c"
    break;

  case 1313: /* sctp_hdr_expr: "sctp" sctp_hdr_field close_scope_sctp  */
#line 6137 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[-1].val));
			}
#line 16939 "parser_bison.c"
    break;

  case 1314: /* sctp_hdr_expr: "sctp" "chunk" sctp_chunk_alloc close_scope_sctp_chunk close_scope_sctp  */
#line 6141 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 16947 "parser_bison.c"
    break;

  case 1315: /* sctp_hdr_field: "sport"  */
#line 6146 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_SPORT; }
#line 16953 "parser_bison.c"
    break;

  case 1316: /* sctp_hdr_field: "dport"  */
#line 6147 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_DPORT; }
#line 16959 "parser_bison.c"
    break;

  case 1317: /* sctp_hdr_field: "vtag"  */
#line 6148 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_VTAG; }
#line 16965 "parser_bison.c"
    break;

  case 1318: /* sctp_hdr_field: "checksum"  */
#line 6149 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 16971 "parser_bison.c"
    break;

  case 1319: /* th_hdr_expr: "th" th_hdr_field close_scope_th  */
#line 6153 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[-1].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 16981 "parser_bison.c"
    break;

  case 1320: /* th_hdr_field: "sport"  */
#line 6160 "parser_bison.y"
                                                { (yyval.val) = THDR_SPORT; }
#line 16987 "parser_bison.c"
    break;

  case 1321: /* th_hdr_field: "dport"  */
#line 6161 "parser_bison.y"
                                                { (yyval.val) = THDR_DPORT; }
#line 16993 "parser_bison.c"
    break;

  case 1330: /* hbh_hdr_expr: "hbh" hbh_hdr_field close_scope_hbh  */
#line 6175 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[-1].val));
			}
#line 17001 "parser_bison.c"
    break;

  case 1331: /* hbh_hdr_field: "nexthdr"  */
#line 6180 "parser_bison.y"
                                                { (yyval.val) = HBHHDR_NEXTHDR; }
#line 17007 "parser_bison.c"
    break;

  case 1332: /* hbh_hdr_field: "hdrlength"  */
#line 6181 "parser_bison.y"
                                                { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 17013 "parser_bison.c"
    break;

  case 1333: /* rt_hdr_expr: "rt" rt_hdr_field close_scope_rt  */
#line 6185 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[-1].val));
			}
#line 17021 "parser_bison.c"
    break;

  case 1334: /* rt_hdr_field: "nexthdr"  */
#line 6190 "parser_bison.y"
                                                { (yyval.val) = RTHDR_NEXTHDR; }
#line 17027 "parser_bison.c"
    break;

  case 1335: /* rt_hdr_field: "hdrlength"  */
#line 6191 "parser_bison.y"
                                                { (yyval.val) = RTHDR_HDRLENGTH; }
#line 17033 "parser_bison.c"
    break;

  case 1336: /* rt_hdr_field: "type" close_scope_type  */
#line 6192 "parser_bison.y"
                                                                        { (yyval.val) = RTHDR_TYPE; }
#line 17039 "parser_bison.c"
    break;

  case 1337: /* rt_hdr_field: "seg-left"  */
#line 6193 "parser_bison.y"
                                                { (yyval.val) = RTHDR_SEG_LEFT; }
#line 17045 "parser_bison.c"
    break;

  case 1338: /* rt0_hdr_expr: "rt0" rt0_hdr_field close_scope_rt  */
#line 6197 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[-1].val));
			}
#line 17053 "parser_bison.c"
    break;

  case 1339: /* rt0_hdr_field: "addr" '[' "number" ']'  */
#line 6203 "parser_bison.y"
                        {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 17061 "parser_bison.c"
    break;

  case 1340: /* rt2_hdr_expr: "rt2" rt2_hdr_field close_scope_rt  */
#line 6209 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[-1].val));
			}
#line 17069 "parser_bison.c"
    break;

  case 1341: /* rt2_hdr_field: "addr"  */
#line 6214 "parser_bison.y"
                                                { (yyval.val) = RT2HDR_ADDR; }
#line 17075 "parser_bison.c"
    break;

  case 1342: /* rt4_hdr_expr: "srh" rt4_hdr_field close_scope_rt  */
#line 6218 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[-1].val));
			}
#line 17083 "parser_bison.c"
    break;

  case 1343: /* rt4_hdr_field: "last-entry"  */
#line 6223 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_LASTENT; }
#line 17089 "parser_bison.c"
    break;

  case 1344: /* rt4_hdr_field: "flags"  */
#line 6224 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_FLAGS; }
#line 17095 "parser_bison.c"
    break;

  case 1345: /* rt4_hdr_field: "tag"  */
#line 6225 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_TAG; }
#line 17101 "parser_bison.c"
    break;

  case 1346: /* rt4_hdr_field: "sid" '[' "number" ']'  */
#line 6227 "parser_bison.y"
                        {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 17109 "parser_bison.c"
    break;

  case 1347: /* frag_hdr_expr: "frag" frag_hdr_field close_scope_frag  */
#line 6233 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[-1].val));
			}
#line 17117 "parser_bison.c"
    break;

  case 1348: /* frag_hdr_field: "nexthdr"  */
#line 6238 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 17123 "parser_bison.c"
    break;

  case 1349: /* frag_hdr_field: "reserved"  */
#line 6239 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_RESERVED; }
#line 17129 "parser_bison.c"
    break;

  case 1350: /* frag_hdr_field: "frag-off"  */
#line 6240 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 17135 "parser_bison.c"
    break;

  case 1351: /* frag_hdr_field: "reserved2"  */
#line 6241 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_RESERVED2; }
#line 17141 "parser_bison.c"
    break;

  case 1352: /* frag_hdr_field: "more-fragments"  */
#line 6242 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_MFRAGS; }
#line 17147 "parser_bison.c"
    break;

  case 1353: /* frag_hdr_field: "id"  */
#line 6243 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_ID; }
#line 17153 "parser_bison.c"
    break;

  case 1354: /* dst_hdr_expr: "dst" dst_hdr_field close_scope_dst  */
#line 6247 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[-1].val));
			}
#line 17161 "parser_bison.c"
    break;

  case 1355: /* dst_hdr_field: "nexthdr"  */
#line 6252 "parser_bison.y"
                                                { (yyval.val) = DSTHDR_NEXTHDR; }
#line 17167 "parser_bison.c"
    break;

  case 1356: /* dst_hdr_field: "hdrlength"  */
#line 6253 "parser_bison.y"
                                                { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 17173 "parser_bison.c"
    break;

  case 1357: /* mh_hdr_expr: "mh" mh_hdr_field close_scope_mh  */
#line 6257 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[-1].val));
			}
#line 17181 "parser_bison.c"
    break;

  case 1358: /* mh_hdr_field: "nexthdr"  */
#line 6262 "parser_bison.y"
                                                { (yyval.val) = MHHDR_NEXTHDR; }
#line 17187 "parser_bison.c"
    break;

  case 1359: /* mh_hdr_field: "hdrlength"  */
#line 6263 "parser_bison.y"
                                                { (yyval.val) = MHHDR_HDRLENGTH; }
#line 17193 "parser_bison.c"
    break;

  case 1360: /* mh_hdr_field: "type" close_scope_type  */
#line 6264 "parser_bison.y"
                                                                        { (yyval.val) = MHHDR_TYPE; }
#line 17199 "parser_bison.c"
    break;

  case 1361: /* mh_hdr_field: "reserved"  */
#line 6265 "parser_bison.y"
                                                { (yyval.val) = MHHDR_RESERVED; }
#line 17205 "parser_bison.c"
    break;

  case 1362: /* mh_hdr_field: "checksum"  */
#line 6266 "parser_bison.y"
                                                { (yyval.val) = MHHDR_CHECKSUM; }
#line 17211 "parser_bison.c"
    break;

  case 1363: /* exthdr_exists_expr: "exthdr" exthdr_key  */
#line 6270 "parser_bison.y"
                        {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the first one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 17227 "parser_bison.c"
    break;

  case 1364: /* exthdr_key: "hbh" close_scope_hbh  */
#line 6283 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_HOPOPTS; }
#line 17233 "parser_bison.c"
    break;

  case 1365: /* exthdr_key: "rt" close_scope_rt  */
#line 6284 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_ROUTING; }
#line 17239 "parser_bison.c"
    break;

  case 1366: /* exthdr_key: "frag" close_scope_frag  */
#line 6285 "parser_bison.y"
                                                                { (yyval.val) = IPPROTO_FRAGMENT; }
#line 17245 "parser_bison.c"
    break;

  case 1367: /* exthdr_key: "dst" close_scope_dst  */
#line 6286 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_DSTOPTS; }
#line 17251 "parser_bison.c"
    break;

  case 1368: /* exthdr_key: "mh" close_scope_mh  */
#line 6287 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_MH; }
#line 17257 "parser_bison.c"
    break;


#line 17261 "parser_bison.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, nft, scanner, state, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= TOKEN_EOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == TOKEN_EOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, nft, scanner, state);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, nft, scanner, state);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, nft, scanner, state, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, nft, scanner, state);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, nft, scanner, state);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 6290 "parser_bison.y"

