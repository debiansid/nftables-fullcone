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
	if (state->scope_err) {
		state->scope_err = false;
		return;
	}

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

#line 223 "parser_bison.c"

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
    AH = 413,                      /* "ah"  */
    RESERVED = 414,                /* "reserved"  */
    SPI = 415,                     /* "spi"  */
    ESP = 416,                     /* "esp"  */
    COMP = 417,                    /* "comp"  */
    FLAGS = 418,                   /* "flags"  */
    CPI = 419,                     /* "cpi"  */
    PORT = 420,                    /* "port"  */
    UDP = 421,                     /* "udp"  */
    SPORT = 422,                   /* "sport"  */
    DPORT = 423,                   /* "dport"  */
    UDPLITE = 424,                 /* "udplite"  */
    CSUMCOV = 425,                 /* "csumcov"  */
    TCP = 426,                     /* "tcp"  */
    ACKSEQ = 427,                  /* "ackseq"  */
    DOFF = 428,                    /* "doff"  */
    WINDOW = 429,                  /* "window"  */
    URGPTR = 430,                  /* "urgptr"  */
    OPTION = 431,                  /* "option"  */
    ECHO = 432,                    /* "echo"  */
    EOL = 433,                     /* "eol"  */
    MPTCP = 434,                   /* "mptcp"  */
    NOP = 435,                     /* "nop"  */
    SACK = 436,                    /* "sack"  */
    SACK0 = 437,                   /* "sack0"  */
    SACK1 = 438,                   /* "sack1"  */
    SACK2 = 439,                   /* "sack2"  */
    SACK3 = 440,                   /* "sack3"  */
    SACK_PERM = 441,               /* "sack-permitted"  */
    FASTOPEN = 442,                /* "fastopen"  */
    MD5SIG = 443,                  /* "md5sig"  */
    TIMESTAMP = 444,               /* "timestamp"  */
    COUNT = 445,                   /* "count"  */
    LEFT = 446,                    /* "left"  */
    RIGHT = 447,                   /* "right"  */
    TSVAL = 448,                   /* "tsval"  */
    TSECR = 449,                   /* "tsecr"  */
    SUBTYPE = 450,                 /* "subtype"  */
    DCCP = 451,                    /* "dccp"  */
    VXLAN = 452,                   /* "vxlan"  */
    VNI = 453,                     /* "vni"  */
    GRE = 454,                     /* "gre"  */
    GRETAP = 455,                  /* "gretap"  */
    GENEVE = 456,                  /* "geneve"  */
    SCTP = 457,                    /* "sctp"  */
    CHUNK = 458,                   /* "chunk"  */
    DATA = 459,                    /* "data"  */
    INIT = 460,                    /* "init"  */
    INIT_ACK = 461,                /* "init-ack"  */
    HEARTBEAT = 462,               /* "heartbeat"  */
    HEARTBEAT_ACK = 463,           /* "heartbeat-ack"  */
    ABORT = 464,                   /* "abort"  */
    SHUTDOWN = 465,                /* "shutdown"  */
    SHUTDOWN_ACK = 466,            /* "shutdown-ack"  */
    ERROR = 467,                   /* "error"  */
    COOKIE_ECHO = 468,             /* "cookie-echo"  */
    COOKIE_ACK = 469,              /* "cookie-ack"  */
    ECNE = 470,                    /* "ecne"  */
    CWR = 471,                     /* "cwr"  */
    SHUTDOWN_COMPLETE = 472,       /* "shutdown-complete"  */
    ASCONF_ACK = 473,              /* "asconf-ack"  */
    FORWARD_TSN = 474,             /* "forward-tsn"  */
    ASCONF = 475,                  /* "asconf"  */
    TSN = 476,                     /* "tsn"  */
    STREAM = 477,                  /* "stream"  */
    SSN = 478,                     /* "ssn"  */
    PPID = 479,                    /* "ppid"  */
    INIT_TAG = 480,                /* "init-tag"  */
    A_RWND = 481,                  /* "a-rwnd"  */
    NUM_OSTREAMS = 482,            /* "num-outbound-streams"  */
    NUM_ISTREAMS = 483,            /* "num-inbound-streams"  */
    INIT_TSN = 484,                /* "initial-tsn"  */
    CUM_TSN_ACK = 485,             /* "cum-tsn-ack"  */
    NUM_GACK_BLOCKS = 486,         /* "num-gap-ack-blocks"  */
    NUM_DUP_TSNS = 487,            /* "num-dup-tsns"  */
    LOWEST_TSN = 488,              /* "lowest-tsn"  */
    SEQNO = 489,                   /* "seqno"  */
    NEW_CUM_TSN = 490,             /* "new-cum-tsn"  */
    VTAG = 491,                    /* "vtag"  */
    RT = 492,                      /* "rt"  */
    RT0 = 493,                     /* "rt0"  */
    RT2 = 494,                     /* "rt2"  */
    RT4 = 495,                     /* "srh"  */
    SEG_LEFT = 496,                /* "seg-left"  */
    ADDR = 497,                    /* "addr"  */
    LAST_ENT = 498,                /* "last-entry"  */
    TAG = 499,                     /* "tag"  */
    SID = 500,                     /* "sid"  */
    HBH = 501,                     /* "hbh"  */
    FRAG = 502,                    /* "frag"  */
    RESERVED2 = 503,               /* "reserved2"  */
    MORE_FRAGMENTS = 504,          /* "more-fragments"  */
    DST = 505,                     /* "dst"  */
    MH = 506,                      /* "mh"  */
    META = 507,                    /* "meta"  */
    MARK = 508,                    /* "mark"  */
    IIF = 509,                     /* "iif"  */
    IIFNAME = 510,                 /* "iifname"  */
    IIFTYPE = 511,                 /* "iiftype"  */
    OIF = 512,                     /* "oif"  */
    OIFNAME = 513,                 /* "oifname"  */
    OIFTYPE = 514,                 /* "oiftype"  */
    SKUID = 515,                   /* "skuid"  */
    SKGID = 516,                   /* "skgid"  */
    NFTRACE = 517,                 /* "nftrace"  */
    RTCLASSID = 518,               /* "rtclassid"  */
    IBRIPORT = 519,                /* "ibriport"  */
    OBRIPORT = 520,                /* "obriport"  */
    IBRIDGENAME = 521,             /* "ibrname"  */
    OBRIDGENAME = 522,             /* "obrname"  */
    PKTTYPE = 523,                 /* "pkttype"  */
    CPU = 524,                     /* "cpu"  */
    IIFGROUP = 525,                /* "iifgroup"  */
    OIFGROUP = 526,                /* "oifgroup"  */
    CGROUP = 527,                  /* "cgroup"  */
    TIME = 528,                    /* "time"  */
    CLASSID = 529,                 /* "classid"  */
    NEXTHOP = 530,                 /* "nexthop"  */
    CT = 531,                      /* "ct"  */
    L3PROTOCOL = 532,              /* "l3proto"  */
    PROTO_SRC = 533,               /* "proto-src"  */
    PROTO_DST = 534,               /* "proto-dst"  */
    ZONE = 535,                    /* "zone"  */
    DIRECTION = 536,               /* "direction"  */
    EVENT = 537,                   /* "event"  */
    EXPECTATION = 538,             /* "expectation"  */
    EXPIRATION = 539,              /* "expiration"  */
    HELPER = 540,                  /* "helper"  */
    LABEL = 541,                   /* "label"  */
    STATE = 542,                   /* "state"  */
    STATUS = 543,                  /* "status"  */
    ORIGINAL = 544,                /* "original"  */
    REPLY = 545,                   /* "reply"  */
    COUNTER = 546,                 /* "counter"  */
    NAME = 547,                    /* "name"  */
    PACKETS = 548,                 /* "packets"  */
    BYTES = 549,                   /* "bytes"  */
    AVGPKT = 550,                  /* "avgpkt"  */
    LAST = 551,                    /* "last"  */
    NEVER = 552,                   /* "never"  */
    COUNTERS = 553,                /* "counters"  */
    QUOTAS = 554,                  /* "quotas"  */
    LIMITS = 555,                  /* "limits"  */
    SYNPROXYS = 556,               /* "synproxys"  */
    HELPERS = 557,                 /* "helpers"  */
    LOG = 558,                     /* "log"  */
    PREFIX = 559,                  /* "prefix"  */
    GROUP = 560,                   /* "group"  */
    SNAPLEN = 561,                 /* "snaplen"  */
    QUEUE_THRESHOLD = 562,         /* "queue-threshold"  */
    LEVEL = 563,                   /* "level"  */
    LIMIT = 564,                   /* "limit"  */
    RATE = 565,                    /* "rate"  */
    BURST = 566,                   /* "burst"  */
    OVER = 567,                    /* "over"  */
    UNTIL = 568,                   /* "until"  */
    QUOTA = 569,                   /* "quota"  */
    USED = 570,                    /* "used"  */
    SECMARK = 571,                 /* "secmark"  */
    SECMARKS = 572,                /* "secmarks"  */
    SECOND = 573,                  /* "second"  */
    MINUTE = 574,                  /* "minute"  */
    HOUR = 575,                    /* "hour"  */
    DAY = 576,                     /* "day"  */
    WEEK = 577,                    /* "week"  */
    _REJECT = 578,                 /* "reject"  */
    WITH = 579,                    /* "with"  */
    ICMPX = 580,                   /* "icmpx"  */
    SNAT = 581,                    /* "snat"  */
    DNAT = 582,                    /* "dnat"  */
    MASQUERADE = 583,              /* "masquerade"  */
    REDIRECT = 584,                /* "redirect"  */
    RANDOM = 585,                  /* "random"  */
    FULLY_RANDOM = 586,            /* "fully-random"  */
    PERSISTENT = 587,              /* "persistent"  */
    QUEUE = 588,                   /* "queue"  */
    QUEUENUM = 589,                /* "num"  */
    BYPASS = 590,                  /* "bypass"  */
    FANOUT = 591,                  /* "fanout"  */
    DUP = 592,                     /* "dup"  */
    FWD = 593,                     /* "fwd"  */
    NUMGEN = 594,                  /* "numgen"  */
    INC = 595,                     /* "inc"  */
    MOD = 596,                     /* "mod"  */
    OFFSET = 597,                  /* "offset"  */
    JHASH = 598,                   /* "jhash"  */
    SYMHASH = 599,                 /* "symhash"  */
    SEED = 600,                    /* "seed"  */
    POSITION = 601,                /* "position"  */
    INDEX = 602,                   /* "index"  */
    COMMENT = 603,                 /* "comment"  */
    XML = 604,                     /* "xml"  */
    JSON = 605,                    /* "json"  */
    VM = 606,                      /* "vm"  */
    NOTRACK = 607,                 /* "notrack"  */
    EXISTS = 608,                  /* "exists"  */
    MISSING = 609,                 /* "missing"  */
    EXTHDR = 610,                  /* "exthdr"  */
    IPSEC = 611,                   /* "ipsec"  */
    REQID = 612,                   /* "reqid"  */
    SPNUM = 613,                   /* "spnum"  */
    IN = 614,                      /* "in"  */
    OUT = 615,                     /* "out"  */
    XT = 616                       /* "xt"  */
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
#define AH 413
#define RESERVED 414
#define SPI 415
#define ESP 416
#define COMP 417
#define FLAGS 418
#define CPI 419
#define PORT 420
#define UDP 421
#define SPORT 422
#define DPORT 423
#define UDPLITE 424
#define CSUMCOV 425
#define TCP 426
#define ACKSEQ 427
#define DOFF 428
#define WINDOW 429
#define URGPTR 430
#define OPTION 431
#define ECHO 432
#define EOL 433
#define MPTCP 434
#define NOP 435
#define SACK 436
#define SACK0 437
#define SACK1 438
#define SACK2 439
#define SACK3 440
#define SACK_PERM 441
#define FASTOPEN 442
#define MD5SIG 443
#define TIMESTAMP 444
#define COUNT 445
#define LEFT 446
#define RIGHT 447
#define TSVAL 448
#define TSECR 449
#define SUBTYPE 450
#define DCCP 451
#define VXLAN 452
#define VNI 453
#define GRE 454
#define GRETAP 455
#define GENEVE 456
#define SCTP 457
#define CHUNK 458
#define DATA 459
#define INIT 460
#define INIT_ACK 461
#define HEARTBEAT 462
#define HEARTBEAT_ACK 463
#define ABORT 464
#define SHUTDOWN 465
#define SHUTDOWN_ACK 466
#define ERROR 467
#define COOKIE_ECHO 468
#define COOKIE_ACK 469
#define ECNE 470
#define CWR 471
#define SHUTDOWN_COMPLETE 472
#define ASCONF_ACK 473
#define FORWARD_TSN 474
#define ASCONF 475
#define TSN 476
#define STREAM 477
#define SSN 478
#define PPID 479
#define INIT_TAG 480
#define A_RWND 481
#define NUM_OSTREAMS 482
#define NUM_ISTREAMS 483
#define INIT_TSN 484
#define CUM_TSN_ACK 485
#define NUM_GACK_BLOCKS 486
#define NUM_DUP_TSNS 487
#define LOWEST_TSN 488
#define SEQNO 489
#define NEW_CUM_TSN 490
#define VTAG 491
#define RT 492
#define RT0 493
#define RT2 494
#define RT4 495
#define SEG_LEFT 496
#define ADDR 497
#define LAST_ENT 498
#define TAG 499
#define SID 500
#define HBH 501
#define FRAG 502
#define RESERVED2 503
#define MORE_FRAGMENTS 504
#define DST 505
#define MH 506
#define META 507
#define MARK 508
#define IIF 509
#define IIFNAME 510
#define IIFTYPE 511
#define OIF 512
#define OIFNAME 513
#define OIFTYPE 514
#define SKUID 515
#define SKGID 516
#define NFTRACE 517
#define RTCLASSID 518
#define IBRIPORT 519
#define OBRIPORT 520
#define IBRIDGENAME 521
#define OBRIDGENAME 522
#define PKTTYPE 523
#define CPU 524
#define IIFGROUP 525
#define OIFGROUP 526
#define CGROUP 527
#define TIME 528
#define CLASSID 529
#define NEXTHOP 530
#define CT 531
#define L3PROTOCOL 532
#define PROTO_SRC 533
#define PROTO_DST 534
#define ZONE 535
#define DIRECTION 536
#define EVENT 537
#define EXPECTATION 538
#define EXPIRATION 539
#define HELPER 540
#define LABEL 541
#define STATE 542
#define STATUS 543
#define ORIGINAL 544
#define REPLY 545
#define COUNTER 546
#define NAME 547
#define PACKETS 548
#define BYTES 549
#define AVGPKT 550
#define LAST 551
#define NEVER 552
#define COUNTERS 553
#define QUOTAS 554
#define LIMITS 555
#define SYNPROXYS 556
#define HELPERS 557
#define LOG 558
#define PREFIX 559
#define GROUP 560
#define SNAPLEN 561
#define QUEUE_THRESHOLD 562
#define LEVEL 563
#define LIMIT 564
#define RATE 565
#define BURST 566
#define OVER 567
#define UNTIL 568
#define QUOTA 569
#define USED 570
#define SECMARK 571
#define SECMARKS 572
#define SECOND 573
#define MINUTE 574
#define HOUR 575
#define DAY 576
#define WEEK 577
#define _REJECT 578
#define WITH 579
#define ICMPX 580
#define SNAT 581
#define DNAT 582
#define MASQUERADE 583
#define REDIRECT 584
#define RANDOM 585
#define FULLY_RANDOM 586
#define PERSISTENT 587
#define QUEUE 588
#define QUEUENUM 589
#define BYPASS 590
#define FANOUT 591
#define DUP 592
#define FWD 593
#define NUMGEN 594
#define INC 595
#define MOD 596
#define OFFSET 597
#define JHASH 598
#define SYMHASH 599
#define SEED 600
#define POSITION 601
#define INDEX 602
#define COMMENT 603
#define XML 604
#define JSON 605
#define VM 606
#define NOTRACK 607
#define EXISTS 608
#define MISSING 609
#define EXTHDR 610
#define IPSEC 611
#define REQID 612
#define SPNUM 613
#define IN 614
#define OUT 615
#define XT 616

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 178 "parser_bison.y"

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

#line 1027 "parser_bison.c"

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
  YYSYMBOL_AH = 158,                       /* "ah"  */
  YYSYMBOL_RESERVED = 159,                 /* "reserved"  */
  YYSYMBOL_SPI = 160,                      /* "spi"  */
  YYSYMBOL_ESP = 161,                      /* "esp"  */
  YYSYMBOL_COMP = 162,                     /* "comp"  */
  YYSYMBOL_FLAGS = 163,                    /* "flags"  */
  YYSYMBOL_CPI = 164,                      /* "cpi"  */
  YYSYMBOL_PORT = 165,                     /* "port"  */
  YYSYMBOL_UDP = 166,                      /* "udp"  */
  YYSYMBOL_SPORT = 167,                    /* "sport"  */
  YYSYMBOL_DPORT = 168,                    /* "dport"  */
  YYSYMBOL_UDPLITE = 169,                  /* "udplite"  */
  YYSYMBOL_CSUMCOV = 170,                  /* "csumcov"  */
  YYSYMBOL_TCP = 171,                      /* "tcp"  */
  YYSYMBOL_ACKSEQ = 172,                   /* "ackseq"  */
  YYSYMBOL_DOFF = 173,                     /* "doff"  */
  YYSYMBOL_WINDOW = 174,                   /* "window"  */
  YYSYMBOL_URGPTR = 175,                   /* "urgptr"  */
  YYSYMBOL_OPTION = 176,                   /* "option"  */
  YYSYMBOL_ECHO = 177,                     /* "echo"  */
  YYSYMBOL_EOL = 178,                      /* "eol"  */
  YYSYMBOL_MPTCP = 179,                    /* "mptcp"  */
  YYSYMBOL_NOP = 180,                      /* "nop"  */
  YYSYMBOL_SACK = 181,                     /* "sack"  */
  YYSYMBOL_SACK0 = 182,                    /* "sack0"  */
  YYSYMBOL_SACK1 = 183,                    /* "sack1"  */
  YYSYMBOL_SACK2 = 184,                    /* "sack2"  */
  YYSYMBOL_SACK3 = 185,                    /* "sack3"  */
  YYSYMBOL_SACK_PERM = 186,                /* "sack-permitted"  */
  YYSYMBOL_FASTOPEN = 187,                 /* "fastopen"  */
  YYSYMBOL_MD5SIG = 188,                   /* "md5sig"  */
  YYSYMBOL_TIMESTAMP = 189,                /* "timestamp"  */
  YYSYMBOL_COUNT = 190,                    /* "count"  */
  YYSYMBOL_LEFT = 191,                     /* "left"  */
  YYSYMBOL_RIGHT = 192,                    /* "right"  */
  YYSYMBOL_TSVAL = 193,                    /* "tsval"  */
  YYSYMBOL_TSECR = 194,                    /* "tsecr"  */
  YYSYMBOL_SUBTYPE = 195,                  /* "subtype"  */
  YYSYMBOL_DCCP = 196,                     /* "dccp"  */
  YYSYMBOL_VXLAN = 197,                    /* "vxlan"  */
  YYSYMBOL_VNI = 198,                      /* "vni"  */
  YYSYMBOL_GRE = 199,                      /* "gre"  */
  YYSYMBOL_GRETAP = 200,                   /* "gretap"  */
  YYSYMBOL_GENEVE = 201,                   /* "geneve"  */
  YYSYMBOL_SCTP = 202,                     /* "sctp"  */
  YYSYMBOL_CHUNK = 203,                    /* "chunk"  */
  YYSYMBOL_DATA = 204,                     /* "data"  */
  YYSYMBOL_INIT = 205,                     /* "init"  */
  YYSYMBOL_INIT_ACK = 206,                 /* "init-ack"  */
  YYSYMBOL_HEARTBEAT = 207,                /* "heartbeat"  */
  YYSYMBOL_HEARTBEAT_ACK = 208,            /* "heartbeat-ack"  */
  YYSYMBOL_ABORT = 209,                    /* "abort"  */
  YYSYMBOL_SHUTDOWN = 210,                 /* "shutdown"  */
  YYSYMBOL_SHUTDOWN_ACK = 211,             /* "shutdown-ack"  */
  YYSYMBOL_ERROR = 212,                    /* "error"  */
  YYSYMBOL_COOKIE_ECHO = 213,              /* "cookie-echo"  */
  YYSYMBOL_COOKIE_ACK = 214,               /* "cookie-ack"  */
  YYSYMBOL_ECNE = 215,                     /* "ecne"  */
  YYSYMBOL_CWR = 216,                      /* "cwr"  */
  YYSYMBOL_SHUTDOWN_COMPLETE = 217,        /* "shutdown-complete"  */
  YYSYMBOL_ASCONF_ACK = 218,               /* "asconf-ack"  */
  YYSYMBOL_FORWARD_TSN = 219,              /* "forward-tsn"  */
  YYSYMBOL_ASCONF = 220,                   /* "asconf"  */
  YYSYMBOL_TSN = 221,                      /* "tsn"  */
  YYSYMBOL_STREAM = 222,                   /* "stream"  */
  YYSYMBOL_SSN = 223,                      /* "ssn"  */
  YYSYMBOL_PPID = 224,                     /* "ppid"  */
  YYSYMBOL_INIT_TAG = 225,                 /* "init-tag"  */
  YYSYMBOL_A_RWND = 226,                   /* "a-rwnd"  */
  YYSYMBOL_NUM_OSTREAMS = 227,             /* "num-outbound-streams"  */
  YYSYMBOL_NUM_ISTREAMS = 228,             /* "num-inbound-streams"  */
  YYSYMBOL_INIT_TSN = 229,                 /* "initial-tsn"  */
  YYSYMBOL_CUM_TSN_ACK = 230,              /* "cum-tsn-ack"  */
  YYSYMBOL_NUM_GACK_BLOCKS = 231,          /* "num-gap-ack-blocks"  */
  YYSYMBOL_NUM_DUP_TSNS = 232,             /* "num-dup-tsns"  */
  YYSYMBOL_LOWEST_TSN = 233,               /* "lowest-tsn"  */
  YYSYMBOL_SEQNO = 234,                    /* "seqno"  */
  YYSYMBOL_NEW_CUM_TSN = 235,              /* "new-cum-tsn"  */
  YYSYMBOL_VTAG = 236,                     /* "vtag"  */
  YYSYMBOL_RT = 237,                       /* "rt"  */
  YYSYMBOL_RT0 = 238,                      /* "rt0"  */
  YYSYMBOL_RT2 = 239,                      /* "rt2"  */
  YYSYMBOL_RT4 = 240,                      /* "srh"  */
  YYSYMBOL_SEG_LEFT = 241,                 /* "seg-left"  */
  YYSYMBOL_ADDR = 242,                     /* "addr"  */
  YYSYMBOL_LAST_ENT = 243,                 /* "last-entry"  */
  YYSYMBOL_TAG = 244,                      /* "tag"  */
  YYSYMBOL_SID = 245,                      /* "sid"  */
  YYSYMBOL_HBH = 246,                      /* "hbh"  */
  YYSYMBOL_FRAG = 247,                     /* "frag"  */
  YYSYMBOL_RESERVED2 = 248,                /* "reserved2"  */
  YYSYMBOL_MORE_FRAGMENTS = 249,           /* "more-fragments"  */
  YYSYMBOL_DST = 250,                      /* "dst"  */
  YYSYMBOL_MH = 251,                       /* "mh"  */
  YYSYMBOL_META = 252,                     /* "meta"  */
  YYSYMBOL_MARK = 253,                     /* "mark"  */
  YYSYMBOL_IIF = 254,                      /* "iif"  */
  YYSYMBOL_IIFNAME = 255,                  /* "iifname"  */
  YYSYMBOL_IIFTYPE = 256,                  /* "iiftype"  */
  YYSYMBOL_OIF = 257,                      /* "oif"  */
  YYSYMBOL_OIFNAME = 258,                  /* "oifname"  */
  YYSYMBOL_OIFTYPE = 259,                  /* "oiftype"  */
  YYSYMBOL_SKUID = 260,                    /* "skuid"  */
  YYSYMBOL_SKGID = 261,                    /* "skgid"  */
  YYSYMBOL_NFTRACE = 262,                  /* "nftrace"  */
  YYSYMBOL_RTCLASSID = 263,                /* "rtclassid"  */
  YYSYMBOL_IBRIPORT = 264,                 /* "ibriport"  */
  YYSYMBOL_OBRIPORT = 265,                 /* "obriport"  */
  YYSYMBOL_IBRIDGENAME = 266,              /* "ibrname"  */
  YYSYMBOL_OBRIDGENAME = 267,              /* "obrname"  */
  YYSYMBOL_PKTTYPE = 268,                  /* "pkttype"  */
  YYSYMBOL_CPU = 269,                      /* "cpu"  */
  YYSYMBOL_IIFGROUP = 270,                 /* "iifgroup"  */
  YYSYMBOL_OIFGROUP = 271,                 /* "oifgroup"  */
  YYSYMBOL_CGROUP = 272,                   /* "cgroup"  */
  YYSYMBOL_TIME = 273,                     /* "time"  */
  YYSYMBOL_CLASSID = 274,                  /* "classid"  */
  YYSYMBOL_NEXTHOP = 275,                  /* "nexthop"  */
  YYSYMBOL_CT = 276,                       /* "ct"  */
  YYSYMBOL_L3PROTOCOL = 277,               /* "l3proto"  */
  YYSYMBOL_PROTO_SRC = 278,                /* "proto-src"  */
  YYSYMBOL_PROTO_DST = 279,                /* "proto-dst"  */
  YYSYMBOL_ZONE = 280,                     /* "zone"  */
  YYSYMBOL_DIRECTION = 281,                /* "direction"  */
  YYSYMBOL_EVENT = 282,                    /* "event"  */
  YYSYMBOL_EXPECTATION = 283,              /* "expectation"  */
  YYSYMBOL_EXPIRATION = 284,               /* "expiration"  */
  YYSYMBOL_HELPER = 285,                   /* "helper"  */
  YYSYMBOL_LABEL = 286,                    /* "label"  */
  YYSYMBOL_STATE = 287,                    /* "state"  */
  YYSYMBOL_STATUS = 288,                   /* "status"  */
  YYSYMBOL_ORIGINAL = 289,                 /* "original"  */
  YYSYMBOL_REPLY = 290,                    /* "reply"  */
  YYSYMBOL_COUNTER = 291,                  /* "counter"  */
  YYSYMBOL_NAME = 292,                     /* "name"  */
  YYSYMBOL_PACKETS = 293,                  /* "packets"  */
  YYSYMBOL_BYTES = 294,                    /* "bytes"  */
  YYSYMBOL_AVGPKT = 295,                   /* "avgpkt"  */
  YYSYMBOL_LAST = 296,                     /* "last"  */
  YYSYMBOL_NEVER = 297,                    /* "never"  */
  YYSYMBOL_COUNTERS = 298,                 /* "counters"  */
  YYSYMBOL_QUOTAS = 299,                   /* "quotas"  */
  YYSYMBOL_LIMITS = 300,                   /* "limits"  */
  YYSYMBOL_SYNPROXYS = 301,                /* "synproxys"  */
  YYSYMBOL_HELPERS = 302,                  /* "helpers"  */
  YYSYMBOL_LOG = 303,                      /* "log"  */
  YYSYMBOL_PREFIX = 304,                   /* "prefix"  */
  YYSYMBOL_GROUP = 305,                    /* "group"  */
  YYSYMBOL_SNAPLEN = 306,                  /* "snaplen"  */
  YYSYMBOL_QUEUE_THRESHOLD = 307,          /* "queue-threshold"  */
  YYSYMBOL_LEVEL = 308,                    /* "level"  */
  YYSYMBOL_LIMIT = 309,                    /* "limit"  */
  YYSYMBOL_RATE = 310,                     /* "rate"  */
  YYSYMBOL_BURST = 311,                    /* "burst"  */
  YYSYMBOL_OVER = 312,                     /* "over"  */
  YYSYMBOL_UNTIL = 313,                    /* "until"  */
  YYSYMBOL_QUOTA = 314,                    /* "quota"  */
  YYSYMBOL_USED = 315,                     /* "used"  */
  YYSYMBOL_SECMARK = 316,                  /* "secmark"  */
  YYSYMBOL_SECMARKS = 317,                 /* "secmarks"  */
  YYSYMBOL_SECOND = 318,                   /* "second"  */
  YYSYMBOL_MINUTE = 319,                   /* "minute"  */
  YYSYMBOL_HOUR = 320,                     /* "hour"  */
  YYSYMBOL_DAY = 321,                      /* "day"  */
  YYSYMBOL_WEEK = 322,                     /* "week"  */
  YYSYMBOL__REJECT = 323,                  /* "reject"  */
  YYSYMBOL_WITH = 324,                     /* "with"  */
  YYSYMBOL_ICMPX = 325,                    /* "icmpx"  */
  YYSYMBOL_SNAT = 326,                     /* "snat"  */
  YYSYMBOL_DNAT = 327,                     /* "dnat"  */
  YYSYMBOL_MASQUERADE = 328,               /* "masquerade"  */
  YYSYMBOL_REDIRECT = 329,                 /* "redirect"  */
  YYSYMBOL_RANDOM = 330,                   /* "random"  */
  YYSYMBOL_FULLY_RANDOM = 331,             /* "fully-random"  */
  YYSYMBOL_PERSISTENT = 332,               /* "persistent"  */
  YYSYMBOL_QUEUE = 333,                    /* "queue"  */
  YYSYMBOL_QUEUENUM = 334,                 /* "num"  */
  YYSYMBOL_BYPASS = 335,                   /* "bypass"  */
  YYSYMBOL_FANOUT = 336,                   /* "fanout"  */
  YYSYMBOL_DUP = 337,                      /* "dup"  */
  YYSYMBOL_FWD = 338,                      /* "fwd"  */
  YYSYMBOL_NUMGEN = 339,                   /* "numgen"  */
  YYSYMBOL_INC = 340,                      /* "inc"  */
  YYSYMBOL_MOD = 341,                      /* "mod"  */
  YYSYMBOL_OFFSET = 342,                   /* "offset"  */
  YYSYMBOL_JHASH = 343,                    /* "jhash"  */
  YYSYMBOL_SYMHASH = 344,                  /* "symhash"  */
  YYSYMBOL_SEED = 345,                     /* "seed"  */
  YYSYMBOL_POSITION = 346,                 /* "position"  */
  YYSYMBOL_INDEX = 347,                    /* "index"  */
  YYSYMBOL_COMMENT = 348,                  /* "comment"  */
  YYSYMBOL_XML = 349,                      /* "xml"  */
  YYSYMBOL_JSON = 350,                     /* "json"  */
  YYSYMBOL_VM = 351,                       /* "vm"  */
  YYSYMBOL_NOTRACK = 352,                  /* "notrack"  */
  YYSYMBOL_EXISTS = 353,                   /* "exists"  */
  YYSYMBOL_MISSING = 354,                  /* "missing"  */
  YYSYMBOL_EXTHDR = 355,                   /* "exthdr"  */
  YYSYMBOL_IPSEC = 356,                    /* "ipsec"  */
  YYSYMBOL_REQID = 357,                    /* "reqid"  */
  YYSYMBOL_SPNUM = 358,                    /* "spnum"  */
  YYSYMBOL_IN = 359,                       /* "in"  */
  YYSYMBOL_OUT = 360,                      /* "out"  */
  YYSYMBOL_XT = 361,                       /* "xt"  */
  YYSYMBOL_362_ = 362,                     /* '='  */
  YYSYMBOL_363_ = 363,                     /* '{'  */
  YYSYMBOL_364_ = 364,                     /* '}'  */
  YYSYMBOL_365_ = 365,                     /* '('  */
  YYSYMBOL_366_ = 366,                     /* ')'  */
  YYSYMBOL_367_ = 367,                     /* '|'  */
  YYSYMBOL_368_ = 368,                     /* '$'  */
  YYSYMBOL_369_ = 369,                     /* '['  */
  YYSYMBOL_370_ = 370,                     /* ']'  */
  YYSYMBOL_YYACCEPT = 371,                 /* $accept  */
  YYSYMBOL_input = 372,                    /* input  */
  YYSYMBOL_stmt_separator = 373,           /* stmt_separator  */
  YYSYMBOL_opt_newline = 374,              /* opt_newline  */
  YYSYMBOL_close_scope_ah = 375,           /* close_scope_ah  */
  YYSYMBOL_close_scope_arp = 376,          /* close_scope_arp  */
  YYSYMBOL_close_scope_at = 377,           /* close_scope_at  */
  YYSYMBOL_close_scope_comp = 378,         /* close_scope_comp  */
  YYSYMBOL_close_scope_ct = 379,           /* close_scope_ct  */
  YYSYMBOL_close_scope_counter = 380,      /* close_scope_counter  */
  YYSYMBOL_close_scope_last = 381,         /* close_scope_last  */
  YYSYMBOL_close_scope_dccp = 382,         /* close_scope_dccp  */
  YYSYMBOL_close_scope_destroy = 383,      /* close_scope_destroy  */
  YYSYMBOL_close_scope_dst = 384,          /* close_scope_dst  */
  YYSYMBOL_close_scope_dup = 385,          /* close_scope_dup  */
  YYSYMBOL_close_scope_esp = 386,          /* close_scope_esp  */
  YYSYMBOL_close_scope_eth = 387,          /* close_scope_eth  */
  YYSYMBOL_close_scope_export = 388,       /* close_scope_export  */
  YYSYMBOL_close_scope_fib = 389,          /* close_scope_fib  */
  YYSYMBOL_close_scope_frag = 390,         /* close_scope_frag  */
  YYSYMBOL_close_scope_fwd = 391,          /* close_scope_fwd  */
  YYSYMBOL_close_scope_gre = 392,          /* close_scope_gre  */
  YYSYMBOL_close_scope_hash = 393,         /* close_scope_hash  */
  YYSYMBOL_close_scope_hbh = 394,          /* close_scope_hbh  */
  YYSYMBOL_close_scope_ip = 395,           /* close_scope_ip  */
  YYSYMBOL_close_scope_ip6 = 396,          /* close_scope_ip6  */
  YYSYMBOL_close_scope_vlan = 397,         /* close_scope_vlan  */
  YYSYMBOL_close_scope_icmp = 398,         /* close_scope_icmp  */
  YYSYMBOL_close_scope_igmp = 399,         /* close_scope_igmp  */
  YYSYMBOL_close_scope_import = 400,       /* close_scope_import  */
  YYSYMBOL_close_scope_ipsec = 401,        /* close_scope_ipsec  */
  YYSYMBOL_close_scope_list = 402,         /* close_scope_list  */
  YYSYMBOL_close_scope_limit = 403,        /* close_scope_limit  */
  YYSYMBOL_close_scope_meta = 404,         /* close_scope_meta  */
  YYSYMBOL_close_scope_mh = 405,           /* close_scope_mh  */
  YYSYMBOL_close_scope_monitor = 406,      /* close_scope_monitor  */
  YYSYMBOL_close_scope_nat = 407,          /* close_scope_nat  */
  YYSYMBOL_close_scope_numgen = 408,       /* close_scope_numgen  */
  YYSYMBOL_close_scope_osf = 409,          /* close_scope_osf  */
  YYSYMBOL_close_scope_policy = 410,       /* close_scope_policy  */
  YYSYMBOL_close_scope_quota = 411,        /* close_scope_quota  */
  YYSYMBOL_close_scope_queue = 412,        /* close_scope_queue  */
  YYSYMBOL_close_scope_reject = 413,       /* close_scope_reject  */
  YYSYMBOL_close_scope_reset = 414,        /* close_scope_reset  */
  YYSYMBOL_close_scope_rt = 415,           /* close_scope_rt  */
  YYSYMBOL_close_scope_sctp = 416,         /* close_scope_sctp  */
  YYSYMBOL_close_scope_sctp_chunk = 417,   /* close_scope_sctp_chunk  */
  YYSYMBOL_close_scope_secmark = 418,      /* close_scope_secmark  */
  YYSYMBOL_close_scope_socket = 419,       /* close_scope_socket  */
  YYSYMBOL_close_scope_tcp = 420,          /* close_scope_tcp  */
  YYSYMBOL_close_scope_tproxy = 421,       /* close_scope_tproxy  */
  YYSYMBOL_close_scope_type = 422,         /* close_scope_type  */
  YYSYMBOL_close_scope_th = 423,           /* close_scope_th  */
  YYSYMBOL_close_scope_udp = 424,          /* close_scope_udp  */
  YYSYMBOL_close_scope_udplite = 425,      /* close_scope_udplite  */
  YYSYMBOL_close_scope_log = 426,          /* close_scope_log  */
  YYSYMBOL_close_scope_synproxy = 427,     /* close_scope_synproxy  */
  YYSYMBOL_close_scope_xt = 428,           /* close_scope_xt  */
  YYSYMBOL_common_block = 429,             /* common_block  */
  YYSYMBOL_line = 430,                     /* line  */
  YYSYMBOL_base_cmd = 431,                 /* base_cmd  */
  YYSYMBOL_add_cmd = 432,                  /* add_cmd  */
  YYSYMBOL_replace_cmd = 433,              /* replace_cmd  */
  YYSYMBOL_create_cmd = 434,               /* create_cmd  */
  YYSYMBOL_insert_cmd = 435,               /* insert_cmd  */
  YYSYMBOL_table_or_id_spec = 436,         /* table_or_id_spec  */
  YYSYMBOL_chain_or_id_spec = 437,         /* chain_or_id_spec  */
  YYSYMBOL_set_or_id_spec = 438,           /* set_or_id_spec  */
  YYSYMBOL_obj_or_id_spec = 439,           /* obj_or_id_spec  */
  YYSYMBOL_delete_cmd = 440,               /* delete_cmd  */
  YYSYMBOL_destroy_cmd = 441,              /* destroy_cmd  */
  YYSYMBOL_get_cmd = 442,                  /* get_cmd  */
  YYSYMBOL_list_cmd = 443,                 /* list_cmd  */
  YYSYMBOL_basehook_device_name = 444,     /* basehook_device_name  */
  YYSYMBOL_basehook_spec = 445,            /* basehook_spec  */
  YYSYMBOL_reset_cmd = 446,                /* reset_cmd  */
  YYSYMBOL_flush_cmd = 447,                /* flush_cmd  */
  YYSYMBOL_rename_cmd = 448,               /* rename_cmd  */
  YYSYMBOL_import_cmd = 449,               /* import_cmd  */
  YYSYMBOL_export_cmd = 450,               /* export_cmd  */
  YYSYMBOL_monitor_cmd = 451,              /* monitor_cmd  */
  YYSYMBOL_monitor_event = 452,            /* monitor_event  */
  YYSYMBOL_monitor_object = 453,           /* monitor_object  */
  YYSYMBOL_monitor_format = 454,           /* monitor_format  */
  YYSYMBOL_markup_format = 455,            /* markup_format  */
  YYSYMBOL_describe_cmd = 456,             /* describe_cmd  */
  YYSYMBOL_table_block_alloc = 457,        /* table_block_alloc  */
  YYSYMBOL_table_options = 458,            /* table_options  */
  YYSYMBOL_table_block = 459,              /* table_block  */
  YYSYMBOL_chain_block_alloc = 460,        /* chain_block_alloc  */
  YYSYMBOL_chain_block = 461,              /* chain_block  */
  YYSYMBOL_subchain_block = 462,           /* subchain_block  */
  YYSYMBOL_typeof_data_expr = 463,         /* typeof_data_expr  */
  YYSYMBOL_typeof_expr = 464,              /* typeof_expr  */
  YYSYMBOL_set_block_alloc = 465,          /* set_block_alloc  */
  YYSYMBOL_set_block = 466,                /* set_block  */
  YYSYMBOL_set_block_expr = 467,           /* set_block_expr  */
  YYSYMBOL_set_flag_list = 468,            /* set_flag_list  */
  YYSYMBOL_set_flag = 469,                 /* set_flag  */
  YYSYMBOL_map_block_alloc = 470,          /* map_block_alloc  */
  YYSYMBOL_map_block_obj_type = 471,       /* map_block_obj_type  */
  YYSYMBOL_map_block = 472,                /* map_block  */
  YYSYMBOL_set_mechanism = 473,            /* set_mechanism  */
  YYSYMBOL_set_policy_spec = 474,          /* set_policy_spec  */
  YYSYMBOL_flowtable_block_alloc = 475,    /* flowtable_block_alloc  */
  YYSYMBOL_flowtable_block = 476,          /* flowtable_block  */
  YYSYMBOL_flowtable_expr = 477,           /* flowtable_expr  */
  YYSYMBOL_flowtable_list_expr = 478,      /* flowtable_list_expr  */
  YYSYMBOL_flowtable_expr_member = 479,    /* flowtable_expr_member  */
  YYSYMBOL_data_type_atom_expr = 480,      /* data_type_atom_expr  */
  YYSYMBOL_data_type_expr = 481,           /* data_type_expr  */
  YYSYMBOL_obj_block_alloc = 482,          /* obj_block_alloc  */
  YYSYMBOL_counter_block = 483,            /* counter_block  */
  YYSYMBOL_quota_block = 484,              /* quota_block  */
  YYSYMBOL_ct_helper_block = 485,          /* ct_helper_block  */
  YYSYMBOL_ct_timeout_block = 486,         /* ct_timeout_block  */
  YYSYMBOL_ct_expect_block = 487,          /* ct_expect_block  */
  YYSYMBOL_limit_block = 488,              /* limit_block  */
  YYSYMBOL_secmark_block = 489,            /* secmark_block  */
  YYSYMBOL_synproxy_block = 490,           /* synproxy_block  */
  YYSYMBOL_type_identifier = 491,          /* type_identifier  */
  YYSYMBOL_hook_spec = 492,                /* hook_spec  */
  YYSYMBOL_prio_spec = 493,                /* prio_spec  */
  YYSYMBOL_extended_prio_name = 494,       /* extended_prio_name  */
  YYSYMBOL_extended_prio_spec = 495,       /* extended_prio_spec  */
  YYSYMBOL_int_num = 496,                  /* int_num  */
  YYSYMBOL_dev_spec = 497,                 /* dev_spec  */
  YYSYMBOL_flags_spec = 498,               /* flags_spec  */
  YYSYMBOL_policy_spec = 499,              /* policy_spec  */
  YYSYMBOL_policy_expr = 500,              /* policy_expr  */
  YYSYMBOL_chain_policy = 501,             /* chain_policy  */
  YYSYMBOL_identifier = 502,               /* identifier  */
  YYSYMBOL_string = 503,                   /* string  */
  YYSYMBOL_time_spec = 504,                /* time_spec  */
  YYSYMBOL_family_spec = 505,              /* family_spec  */
  YYSYMBOL_family_spec_explicit = 506,     /* family_spec_explicit  */
  YYSYMBOL_table_spec = 507,               /* table_spec  */
  YYSYMBOL_tableid_spec = 508,             /* tableid_spec  */
  YYSYMBOL_chain_spec = 509,               /* chain_spec  */
  YYSYMBOL_chainid_spec = 510,             /* chainid_spec  */
  YYSYMBOL_chain_identifier = 511,         /* chain_identifier  */
  YYSYMBOL_set_spec = 512,                 /* set_spec  */
  YYSYMBOL_setid_spec = 513,               /* setid_spec  */
  YYSYMBOL_set_identifier = 514,           /* set_identifier  */
  YYSYMBOL_flowtable_spec = 515,           /* flowtable_spec  */
  YYSYMBOL_flowtableid_spec = 516,         /* flowtableid_spec  */
  YYSYMBOL_flowtable_identifier = 517,     /* flowtable_identifier  */
  YYSYMBOL_obj_spec = 518,                 /* obj_spec  */
  YYSYMBOL_objid_spec = 519,               /* objid_spec  */
  YYSYMBOL_obj_identifier = 520,           /* obj_identifier  */
  YYSYMBOL_handle_spec = 521,              /* handle_spec  */
  YYSYMBOL_position_spec = 522,            /* position_spec  */
  YYSYMBOL_index_spec = 523,               /* index_spec  */
  YYSYMBOL_rule_position = 524,            /* rule_position  */
  YYSYMBOL_ruleid_spec = 525,              /* ruleid_spec  */
  YYSYMBOL_comment_spec = 526,             /* comment_spec  */
  YYSYMBOL_ruleset_spec = 527,             /* ruleset_spec  */
  YYSYMBOL_rule = 528,                     /* rule  */
  YYSYMBOL_rule_alloc = 529,               /* rule_alloc  */
  YYSYMBOL_stmt_list = 530,                /* stmt_list  */
  YYSYMBOL_stateful_stmt_list = 531,       /* stateful_stmt_list  */
  YYSYMBOL_stateful_stmt = 532,            /* stateful_stmt  */
  YYSYMBOL_stmt = 533,                     /* stmt  */
  YYSYMBOL_xt_stmt = 534,                  /* xt_stmt  */
  YYSYMBOL_chain_stmt_type = 535,          /* chain_stmt_type  */
  YYSYMBOL_chain_stmt = 536,               /* chain_stmt  */
  YYSYMBOL_verdict_stmt = 537,             /* verdict_stmt  */
  YYSYMBOL_verdict_map_stmt = 538,         /* verdict_map_stmt  */
  YYSYMBOL_verdict_map_expr = 539,         /* verdict_map_expr  */
  YYSYMBOL_verdict_map_list_expr = 540,    /* verdict_map_list_expr  */
  YYSYMBOL_verdict_map_list_member_expr = 541, /* verdict_map_list_member_expr  */
  YYSYMBOL_connlimit_stmt = 542,           /* connlimit_stmt  */
  YYSYMBOL_counter_stmt = 543,             /* counter_stmt  */
  YYSYMBOL_counter_stmt_alloc = 544,       /* counter_stmt_alloc  */
  YYSYMBOL_counter_args = 545,             /* counter_args  */
  YYSYMBOL_counter_arg = 546,              /* counter_arg  */
  YYSYMBOL_last_stmt = 547,                /* last_stmt  */
  YYSYMBOL_log_stmt = 548,                 /* log_stmt  */
  YYSYMBOL_log_stmt_alloc = 549,           /* log_stmt_alloc  */
  YYSYMBOL_log_args = 550,                 /* log_args  */
  YYSYMBOL_log_arg = 551,                  /* log_arg  */
  YYSYMBOL_level_type = 552,               /* level_type  */
  YYSYMBOL_log_flags = 553,                /* log_flags  */
  YYSYMBOL_log_flags_tcp = 554,            /* log_flags_tcp  */
  YYSYMBOL_log_flag_tcp = 555,             /* log_flag_tcp  */
  YYSYMBOL_limit_stmt = 556,               /* limit_stmt  */
  YYSYMBOL_quota_mode = 557,               /* quota_mode  */
  YYSYMBOL_quota_unit = 558,               /* quota_unit  */
  YYSYMBOL_quota_used = 559,               /* quota_used  */
  YYSYMBOL_quota_stmt = 560,               /* quota_stmt  */
  YYSYMBOL_limit_mode = 561,               /* limit_mode  */
  YYSYMBOL_limit_burst_pkts = 562,         /* limit_burst_pkts  */
  YYSYMBOL_limit_rate_pkts = 563,          /* limit_rate_pkts  */
  YYSYMBOL_limit_burst_bytes = 564,        /* limit_burst_bytes  */
  YYSYMBOL_limit_rate_bytes = 565,         /* limit_rate_bytes  */
  YYSYMBOL_limit_bytes = 566,              /* limit_bytes  */
  YYSYMBOL_time_unit = 567,                /* time_unit  */
  YYSYMBOL_reject_stmt = 568,              /* reject_stmt  */
  YYSYMBOL_reject_stmt_alloc = 569,        /* reject_stmt_alloc  */
  YYSYMBOL_reject_with_expr = 570,         /* reject_with_expr  */
  YYSYMBOL_reject_opts = 571,              /* reject_opts  */
  YYSYMBOL_nat_stmt = 572,                 /* nat_stmt  */
  YYSYMBOL_nat_stmt_alloc = 573,           /* nat_stmt_alloc  */
  YYSYMBOL_tproxy_stmt = 574,              /* tproxy_stmt  */
  YYSYMBOL_synproxy_stmt = 575,            /* synproxy_stmt  */
  YYSYMBOL_synproxy_stmt_alloc = 576,      /* synproxy_stmt_alloc  */
  YYSYMBOL_synproxy_args = 577,            /* synproxy_args  */
  YYSYMBOL_synproxy_arg = 578,             /* synproxy_arg  */
  YYSYMBOL_synproxy_config = 579,          /* synproxy_config  */
  YYSYMBOL_synproxy_obj = 580,             /* synproxy_obj  */
  YYSYMBOL_synproxy_ts = 581,              /* synproxy_ts  */
  YYSYMBOL_synproxy_sack = 582,            /* synproxy_sack  */
  YYSYMBOL_primary_stmt_expr = 583,        /* primary_stmt_expr  */
  YYSYMBOL_shift_stmt_expr = 584,          /* shift_stmt_expr  */
  YYSYMBOL_and_stmt_expr = 585,            /* and_stmt_expr  */
  YYSYMBOL_exclusive_or_stmt_expr = 586,   /* exclusive_or_stmt_expr  */
  YYSYMBOL_inclusive_or_stmt_expr = 587,   /* inclusive_or_stmt_expr  */
  YYSYMBOL_basic_stmt_expr = 588,          /* basic_stmt_expr  */
  YYSYMBOL_concat_stmt_expr = 589,         /* concat_stmt_expr  */
  YYSYMBOL_map_stmt_expr_set = 590,        /* map_stmt_expr_set  */
  YYSYMBOL_map_stmt_expr = 591,            /* map_stmt_expr  */
  YYSYMBOL_prefix_stmt_expr = 592,         /* prefix_stmt_expr  */
  YYSYMBOL_range_stmt_expr = 593,          /* range_stmt_expr  */
  YYSYMBOL_multiton_stmt_expr = 594,       /* multiton_stmt_expr  */
  YYSYMBOL_stmt_expr = 595,                /* stmt_expr  */
  YYSYMBOL_nat_stmt_args = 596,            /* nat_stmt_args  */
  YYSYMBOL_masq_stmt = 597,                /* masq_stmt  */
  YYSYMBOL_masq_stmt_alloc = 598,          /* masq_stmt_alloc  */
  YYSYMBOL_masq_stmt_args = 599,           /* masq_stmt_args  */
  YYSYMBOL_redir_stmt = 600,               /* redir_stmt  */
  YYSYMBOL_redir_stmt_alloc = 601,         /* redir_stmt_alloc  */
  YYSYMBOL_redir_stmt_arg = 602,           /* redir_stmt_arg  */
  YYSYMBOL_dup_stmt = 603,                 /* dup_stmt  */
  YYSYMBOL_fwd_stmt = 604,                 /* fwd_stmt  */
  YYSYMBOL_nf_nat_flags = 605,             /* nf_nat_flags  */
  YYSYMBOL_nf_nat_flag = 606,              /* nf_nat_flag  */
  YYSYMBOL_queue_stmt = 607,               /* queue_stmt  */
  YYSYMBOL_queue_stmt_compat = 608,        /* queue_stmt_compat  */
  YYSYMBOL_queue_stmt_alloc = 609,         /* queue_stmt_alloc  */
  YYSYMBOL_queue_stmt_args = 610,          /* queue_stmt_args  */
  YYSYMBOL_queue_stmt_arg = 611,           /* queue_stmt_arg  */
  YYSYMBOL_queue_expr = 612,               /* queue_expr  */
  YYSYMBOL_queue_stmt_expr_simple = 613,   /* queue_stmt_expr_simple  */
  YYSYMBOL_queue_stmt_expr = 614,          /* queue_stmt_expr  */
  YYSYMBOL_queue_stmt_flags = 615,         /* queue_stmt_flags  */
  YYSYMBOL_queue_stmt_flag = 616,          /* queue_stmt_flag  */
  YYSYMBOL_set_elem_expr_stmt = 617,       /* set_elem_expr_stmt  */
  YYSYMBOL_set_elem_expr_stmt_alloc = 618, /* set_elem_expr_stmt_alloc  */
  YYSYMBOL_set_stmt = 619,                 /* set_stmt  */
  YYSYMBOL_set_stmt_op = 620,              /* set_stmt_op  */
  YYSYMBOL_map_stmt = 621,                 /* map_stmt  */
  YYSYMBOL_meter_stmt = 622,               /* meter_stmt  */
  YYSYMBOL_flow_stmt_legacy_alloc = 623,   /* flow_stmt_legacy_alloc  */
  YYSYMBOL_flow_stmt_opts = 624,           /* flow_stmt_opts  */
  YYSYMBOL_flow_stmt_opt = 625,            /* flow_stmt_opt  */
  YYSYMBOL_meter_stmt_alloc = 626,         /* meter_stmt_alloc  */
  YYSYMBOL_match_stmt = 627,               /* match_stmt  */
  YYSYMBOL_variable_expr = 628,            /* variable_expr  */
  YYSYMBOL_symbol_expr = 629,              /* symbol_expr  */
  YYSYMBOL_set_ref_expr = 630,             /* set_ref_expr  */
  YYSYMBOL_set_ref_symbol_expr = 631,      /* set_ref_symbol_expr  */
  YYSYMBOL_integer_expr = 632,             /* integer_expr  */
  YYSYMBOL_primary_expr = 633,             /* primary_expr  */
  YYSYMBOL_fib_expr = 634,                 /* fib_expr  */
  YYSYMBOL_fib_result = 635,               /* fib_result  */
  YYSYMBOL_fib_flag = 636,                 /* fib_flag  */
  YYSYMBOL_fib_tuple = 637,                /* fib_tuple  */
  YYSYMBOL_osf_expr = 638,                 /* osf_expr  */
  YYSYMBOL_osf_ttl = 639,                  /* osf_ttl  */
  YYSYMBOL_shift_expr = 640,               /* shift_expr  */
  YYSYMBOL_and_expr = 641,                 /* and_expr  */
  YYSYMBOL_exclusive_or_expr = 642,        /* exclusive_or_expr  */
  YYSYMBOL_inclusive_or_expr = 643,        /* inclusive_or_expr  */
  YYSYMBOL_basic_expr = 644,               /* basic_expr  */
  YYSYMBOL_concat_expr = 645,              /* concat_expr  */
  YYSYMBOL_prefix_rhs_expr = 646,          /* prefix_rhs_expr  */
  YYSYMBOL_range_rhs_expr = 647,           /* range_rhs_expr  */
  YYSYMBOL_multiton_rhs_expr = 648,        /* multiton_rhs_expr  */
  YYSYMBOL_map_expr = 649,                 /* map_expr  */
  YYSYMBOL_expr = 650,                     /* expr  */
  YYSYMBOL_set_expr = 651,                 /* set_expr  */
  YYSYMBOL_set_list_expr = 652,            /* set_list_expr  */
  YYSYMBOL_set_list_member_expr = 653,     /* set_list_member_expr  */
  YYSYMBOL_meter_key_expr = 654,           /* meter_key_expr  */
  YYSYMBOL_meter_key_expr_alloc = 655,     /* meter_key_expr_alloc  */
  YYSYMBOL_set_elem_expr = 656,            /* set_elem_expr  */
  YYSYMBOL_set_elem_key_expr = 657,        /* set_elem_key_expr  */
  YYSYMBOL_set_elem_expr_alloc = 658,      /* set_elem_expr_alloc  */
  YYSYMBOL_set_elem_options = 659,         /* set_elem_options  */
  YYSYMBOL_set_elem_option = 660,          /* set_elem_option  */
  YYSYMBOL_set_elem_expr_options = 661,    /* set_elem_expr_options  */
  YYSYMBOL_set_elem_stmt_list = 662,       /* set_elem_stmt_list  */
  YYSYMBOL_set_elem_stmt = 663,            /* set_elem_stmt  */
  YYSYMBOL_set_elem_expr_option = 664,     /* set_elem_expr_option  */
  YYSYMBOL_set_lhs_expr = 665,             /* set_lhs_expr  */
  YYSYMBOL_set_rhs_expr = 666,             /* set_rhs_expr  */
  YYSYMBOL_initializer_expr = 667,         /* initializer_expr  */
  YYSYMBOL_counter_config = 668,           /* counter_config  */
  YYSYMBOL_counter_obj = 669,              /* counter_obj  */
  YYSYMBOL_quota_config = 670,             /* quota_config  */
  YYSYMBOL_quota_obj = 671,                /* quota_obj  */
  YYSYMBOL_secmark_config = 672,           /* secmark_config  */
  YYSYMBOL_secmark_obj = 673,              /* secmark_obj  */
  YYSYMBOL_ct_obj_type = 674,              /* ct_obj_type  */
  YYSYMBOL_ct_cmd_type = 675,              /* ct_cmd_type  */
  YYSYMBOL_ct_l4protoname = 676,           /* ct_l4protoname  */
  YYSYMBOL_ct_helper_config = 677,         /* ct_helper_config  */
  YYSYMBOL_timeout_states = 678,           /* timeout_states  */
  YYSYMBOL_timeout_state = 679,            /* timeout_state  */
  YYSYMBOL_ct_timeout_config = 680,        /* ct_timeout_config  */
  YYSYMBOL_ct_expect_config = 681,         /* ct_expect_config  */
  YYSYMBOL_ct_obj_alloc = 682,             /* ct_obj_alloc  */
  YYSYMBOL_limit_config = 683,             /* limit_config  */
  YYSYMBOL_limit_obj = 684,                /* limit_obj  */
  YYSYMBOL_relational_expr = 685,          /* relational_expr  */
  YYSYMBOL_list_rhs_expr = 686,            /* list_rhs_expr  */
  YYSYMBOL_rhs_expr = 687,                 /* rhs_expr  */
  YYSYMBOL_shift_rhs_expr = 688,           /* shift_rhs_expr  */
  YYSYMBOL_and_rhs_expr = 689,             /* and_rhs_expr  */
  YYSYMBOL_exclusive_or_rhs_expr = 690,    /* exclusive_or_rhs_expr  */
  YYSYMBOL_inclusive_or_rhs_expr = 691,    /* inclusive_or_rhs_expr  */
  YYSYMBOL_basic_rhs_expr = 692,           /* basic_rhs_expr  */
  YYSYMBOL_concat_rhs_expr = 693,          /* concat_rhs_expr  */
  YYSYMBOL_boolean_keys = 694,             /* boolean_keys  */
  YYSYMBOL_boolean_expr = 695,             /* boolean_expr  */
  YYSYMBOL_keyword_expr = 696,             /* keyword_expr  */
  YYSYMBOL_primary_rhs_expr = 697,         /* primary_rhs_expr  */
  YYSYMBOL_relational_op = 698,            /* relational_op  */
  YYSYMBOL_verdict_expr = 699,             /* verdict_expr  */
  YYSYMBOL_chain_expr = 700,               /* chain_expr  */
  YYSYMBOL_meta_expr = 701,                /* meta_expr  */
  YYSYMBOL_meta_key = 702,                 /* meta_key  */
  YYSYMBOL_meta_key_qualified = 703,       /* meta_key_qualified  */
  YYSYMBOL_meta_key_unqualified = 704,     /* meta_key_unqualified  */
  YYSYMBOL_meta_stmt = 705,                /* meta_stmt  */
  YYSYMBOL_socket_expr = 706,              /* socket_expr  */
  YYSYMBOL_socket_key = 707,               /* socket_key  */
  YYSYMBOL_offset_opt = 708,               /* offset_opt  */
  YYSYMBOL_numgen_type = 709,              /* numgen_type  */
  YYSYMBOL_numgen_expr = 710,              /* numgen_expr  */
  YYSYMBOL_xfrm_spnum = 711,               /* xfrm_spnum  */
  YYSYMBOL_xfrm_dir = 712,                 /* xfrm_dir  */
  YYSYMBOL_xfrm_state_key = 713,           /* xfrm_state_key  */
  YYSYMBOL_xfrm_state_proto_key = 714,     /* xfrm_state_proto_key  */
  YYSYMBOL_xfrm_expr = 715,                /* xfrm_expr  */
  YYSYMBOL_hash_expr = 716,                /* hash_expr  */
  YYSYMBOL_nf_key_proto = 717,             /* nf_key_proto  */
  YYSYMBOL_rt_expr = 718,                  /* rt_expr  */
  YYSYMBOL_rt_key = 719,                   /* rt_key  */
  YYSYMBOL_ct_expr = 720,                  /* ct_expr  */
  YYSYMBOL_ct_dir = 721,                   /* ct_dir  */
  YYSYMBOL_ct_key = 722,                   /* ct_key  */
  YYSYMBOL_ct_key_dir = 723,               /* ct_key_dir  */
  YYSYMBOL_ct_key_proto_field = 724,       /* ct_key_proto_field  */
  YYSYMBOL_ct_key_dir_optional = 725,      /* ct_key_dir_optional  */
  YYSYMBOL_symbol_stmt_expr = 726,         /* symbol_stmt_expr  */
  YYSYMBOL_list_stmt_expr = 727,           /* list_stmt_expr  */
  YYSYMBOL_ct_stmt = 728,                  /* ct_stmt  */
  YYSYMBOL_payload_stmt = 729,             /* payload_stmt  */
  YYSYMBOL_payload_expr = 730,             /* payload_expr  */
  YYSYMBOL_payload_raw_expr = 731,         /* payload_raw_expr  */
  YYSYMBOL_payload_base_spec = 732,        /* payload_base_spec  */
  YYSYMBOL_eth_hdr_expr = 733,             /* eth_hdr_expr  */
  YYSYMBOL_eth_hdr_field = 734,            /* eth_hdr_field  */
  YYSYMBOL_vlan_hdr_expr = 735,            /* vlan_hdr_expr  */
  YYSYMBOL_vlan_hdr_field = 736,           /* vlan_hdr_field  */
  YYSYMBOL_arp_hdr_expr = 737,             /* arp_hdr_expr  */
  YYSYMBOL_arp_hdr_field = 738,            /* arp_hdr_field  */
  YYSYMBOL_ip_hdr_expr = 739,              /* ip_hdr_expr  */
  YYSYMBOL_ip_hdr_field = 740,             /* ip_hdr_field  */
  YYSYMBOL_ip_option_type = 741,           /* ip_option_type  */
  YYSYMBOL_ip_option_field = 742,          /* ip_option_field  */
  YYSYMBOL_icmp_hdr_expr = 743,            /* icmp_hdr_expr  */
  YYSYMBOL_icmp_hdr_field = 744,           /* icmp_hdr_field  */
  YYSYMBOL_igmp_hdr_expr = 745,            /* igmp_hdr_expr  */
  YYSYMBOL_igmp_hdr_field = 746,           /* igmp_hdr_field  */
  YYSYMBOL_ip6_hdr_expr = 747,             /* ip6_hdr_expr  */
  YYSYMBOL_ip6_hdr_field = 748,            /* ip6_hdr_field  */
  YYSYMBOL_icmp6_hdr_expr = 749,           /* icmp6_hdr_expr  */
  YYSYMBOL_icmp6_hdr_field = 750,          /* icmp6_hdr_field  */
  YYSYMBOL_auth_hdr_expr = 751,            /* auth_hdr_expr  */
  YYSYMBOL_auth_hdr_field = 752,           /* auth_hdr_field  */
  YYSYMBOL_esp_hdr_expr = 753,             /* esp_hdr_expr  */
  YYSYMBOL_esp_hdr_field = 754,            /* esp_hdr_field  */
  YYSYMBOL_comp_hdr_expr = 755,            /* comp_hdr_expr  */
  YYSYMBOL_comp_hdr_field = 756,           /* comp_hdr_field  */
  YYSYMBOL_udp_hdr_expr = 757,             /* udp_hdr_expr  */
  YYSYMBOL_udp_hdr_field = 758,            /* udp_hdr_field  */
  YYSYMBOL_udplite_hdr_expr = 759,         /* udplite_hdr_expr  */
  YYSYMBOL_udplite_hdr_field = 760,        /* udplite_hdr_field  */
  YYSYMBOL_tcp_hdr_expr = 761,             /* tcp_hdr_expr  */
  YYSYMBOL_inner_inet_expr = 762,          /* inner_inet_expr  */
  YYSYMBOL_inner_eth_expr = 763,           /* inner_eth_expr  */
  YYSYMBOL_inner_expr = 764,               /* inner_expr  */
  YYSYMBOL_vxlan_hdr_expr = 765,           /* vxlan_hdr_expr  */
  YYSYMBOL_vxlan_hdr_field = 766,          /* vxlan_hdr_field  */
  YYSYMBOL_geneve_hdr_expr = 767,          /* geneve_hdr_expr  */
  YYSYMBOL_geneve_hdr_field = 768,         /* geneve_hdr_field  */
  YYSYMBOL_gre_hdr_expr = 769,             /* gre_hdr_expr  */
  YYSYMBOL_gre_hdr_field = 770,            /* gre_hdr_field  */
  YYSYMBOL_gretap_hdr_expr = 771,          /* gretap_hdr_expr  */
  YYSYMBOL_optstrip_stmt = 772,            /* optstrip_stmt  */
  YYSYMBOL_tcp_hdr_field = 773,            /* tcp_hdr_field  */
  YYSYMBOL_tcp_hdr_option_kind_and_field = 774, /* tcp_hdr_option_kind_and_field  */
  YYSYMBOL_tcp_hdr_option_sack = 775,      /* tcp_hdr_option_sack  */
  YYSYMBOL_tcp_hdr_option_type = 776,      /* tcp_hdr_option_type  */
  YYSYMBOL_tcpopt_field_sack = 777,        /* tcpopt_field_sack  */
  YYSYMBOL_tcpopt_field_window = 778,      /* tcpopt_field_window  */
  YYSYMBOL_tcpopt_field_tsopt = 779,       /* tcpopt_field_tsopt  */
  YYSYMBOL_tcpopt_field_maxseg = 780,      /* tcpopt_field_maxseg  */
  YYSYMBOL_tcpopt_field_mptcp = 781,       /* tcpopt_field_mptcp  */
  YYSYMBOL_dccp_hdr_expr = 782,            /* dccp_hdr_expr  */
  YYSYMBOL_dccp_hdr_field = 783,           /* dccp_hdr_field  */
  YYSYMBOL_sctp_chunk_type = 784,          /* sctp_chunk_type  */
  YYSYMBOL_sctp_chunk_common_field = 785,  /* sctp_chunk_common_field  */
  YYSYMBOL_sctp_chunk_data_field = 786,    /* sctp_chunk_data_field  */
  YYSYMBOL_sctp_chunk_init_field = 787,    /* sctp_chunk_init_field  */
  YYSYMBOL_sctp_chunk_sack_field = 788,    /* sctp_chunk_sack_field  */
  YYSYMBOL_sctp_chunk_alloc = 789,         /* sctp_chunk_alloc  */
  YYSYMBOL_sctp_hdr_expr = 790,            /* sctp_hdr_expr  */
  YYSYMBOL_sctp_hdr_field = 791,           /* sctp_hdr_field  */
  YYSYMBOL_th_hdr_expr = 792,              /* th_hdr_expr  */
  YYSYMBOL_th_hdr_field = 793,             /* th_hdr_field  */
  YYSYMBOL_exthdr_expr = 794,              /* exthdr_expr  */
  YYSYMBOL_hbh_hdr_expr = 795,             /* hbh_hdr_expr  */
  YYSYMBOL_hbh_hdr_field = 796,            /* hbh_hdr_field  */
  YYSYMBOL_rt_hdr_expr = 797,              /* rt_hdr_expr  */
  YYSYMBOL_rt_hdr_field = 798,             /* rt_hdr_field  */
  YYSYMBOL_rt0_hdr_expr = 799,             /* rt0_hdr_expr  */
  YYSYMBOL_rt0_hdr_field = 800,            /* rt0_hdr_field  */
  YYSYMBOL_rt2_hdr_expr = 801,             /* rt2_hdr_expr  */
  YYSYMBOL_rt2_hdr_field = 802,            /* rt2_hdr_field  */
  YYSYMBOL_rt4_hdr_expr = 803,             /* rt4_hdr_expr  */
  YYSYMBOL_rt4_hdr_field = 804,            /* rt4_hdr_field  */
  YYSYMBOL_frag_hdr_expr = 805,            /* frag_hdr_expr  */
  YYSYMBOL_frag_hdr_field = 806,           /* frag_hdr_field  */
  YYSYMBOL_dst_hdr_expr = 807,             /* dst_hdr_expr  */
  YYSYMBOL_dst_hdr_field = 808,            /* dst_hdr_field  */
  YYSYMBOL_mh_hdr_expr = 809,              /* mh_hdr_expr  */
  YYSYMBOL_mh_hdr_field = 810,             /* mh_hdr_field  */
  YYSYMBOL_exthdr_exists_expr = 811,       /* exthdr_exists_expr  */
  YYSYMBOL_exthdr_key = 812                /* exthdr_key  */
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
#define YYLAST   8525

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  371
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  442
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1352
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2324

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   616


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
       2,     2,     2,     2,     2,     2,   368,     2,     2,     2,
     365,   366,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   362,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   369,     2,   370,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   363,   367,   364,     2,     2,     2,     2,
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
     355,   356,   357,   358,   359,   360,   361
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   950,   950,   951,   960,   961,   964,   965,   968,   969,
     970,   971,   972,   973,   974,   975,   976,   977,   978,   979,
     980,   981,   982,   983,   984,   985,   986,   987,   988,   989,
     990,   991,   992,   993,   994,   995,   996,   997,   998,   999,
    1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,  1008,  1009,
    1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,  1018,  1020,
    1021,  1022,  1024,  1032,  1047,  1054,  1066,  1074,  1075,  1076,
    1077,  1097,  1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,
    1106,  1107,  1108,  1109,  1110,  1111,  1112,  1115,  1119,  1126,
    1130,  1138,  1142,  1146,  1153,  1160,  1164,  1171,  1180,  1184,
    1188,  1192,  1196,  1200,  1204,  1208,  1212,  1216,  1220,  1224,
    1228,  1234,  1240,  1244,  1251,  1255,  1263,  1270,  1277,  1281,
    1288,  1297,  1301,  1305,  1309,  1313,  1317,  1321,  1325,  1331,
    1337,  1338,  1341,  1342,  1345,  1346,  1349,  1350,  1353,  1357,
    1361,  1365,  1369,  1373,  1377,  1381,  1385,  1392,  1396,  1400,
    1406,  1410,  1414,  1420,  1424,  1428,  1432,  1436,  1440,  1444,
    1448,  1452,  1459,  1463,  1467,  1473,  1477,  1481,  1488,  1494,
    1498,  1502,  1506,  1510,  1514,  1518,  1522,  1526,  1530,  1534,
    1538,  1542,  1546,  1550,  1554,  1558,  1562,  1566,  1570,  1574,
    1578,  1582,  1586,  1590,  1594,  1598,  1602,  1606,  1610,  1614,
    1618,  1622,  1626,  1632,  1638,  1642,  1652,  1656,  1660,  1664,
    1668,  1672,  1676,  1680,  1684,  1688,  1694,  1698,  1702,  1706,
    1710,  1714,  1718,  1724,  1731,  1737,  1745,  1751,  1759,  1768,
    1769,  1772,  1773,  1774,  1775,  1776,  1777,  1778,  1779,  1782,
    1783,  1786,  1787,  1788,  1791,  1800,  1810,  1825,  1835,  1836,
    1837,  1838,  1839,  1850,  1860,  1871,  1881,  1892,  1903,  1912,
    1921,  1930,  1941,  1952,  1966,  1976,  1977,  1978,  1979,  1980,
    1981,  1982,  1987,  1997,  1998,  1999,  2006,  2027,  2038,  2049,
    2062,  2067,  2068,  2069,  2070,  2075,  2081,  2086,  2091,  2096,
    2102,  2107,  2112,  2113,  2124,  2125,  2128,  2132,  2135,  2136,
    2137,  2138,  2142,  2147,  2148,  2149,  2150,  2151,  2154,  2155,
    2156,  2157,  2162,  2172,  2183,  2194,  2206,  2215,  2220,  2226,
    2231,  2240,  2243,  2247,  2253,  2254,  2258,  2263,  2264,  2265,
    2266,  2280,  2284,  2288,  2294,  2299,  2306,  2311,  2316,  2319,
    2326,  2333,  2340,  2353,  2360,  2361,  2373,  2378,  2379,  2380,
    2381,  2385,  2395,  2396,  2397,  2398,  2402,  2412,  2413,  2414,
    2415,  2419,  2430,  2434,  2435,  2436,  2440,  2450,  2451,  2452,
    2453,  2457,  2467,  2468,  2469,  2470,  2474,  2484,  2485,  2486,
    2487,  2491,  2501,  2502,  2503,  2504,  2508,  2518,  2519,  2520,
    2521,  2522,  2525,  2556,  2563,  2567,  2570,  2580,  2587,  2598,
    2611,  2626,  2627,  2630,  2642,  2648,  2652,  2655,  2661,  2674,
    2679,  2688,  2689,  2692,  2693,  2696,  2697,  2698,  2701,  2716,
    2717,  2720,  2721,  2722,  2723,  2724,  2725,  2728,  2737,  2746,
    2754,  2762,  2770,  2778,  2786,  2794,  2802,  2810,  2818,  2826,
    2834,  2842,  2850,  2858,  2866,  2870,  2875,  2883,  2890,  2897,
    2911,  2915,  2922,  2926,  2932,  2944,  2950,  2957,  2963,  2970,
    2971,  2972,  2973,  2974,  2977,  2978,  2979,  2980,  2981,  2982,
    2983,  2984,  2985,  2986,  2987,  2988,  2989,  2990,  2991,  2992,
    2993,  2994,  2995,  2996,  2997,  2998,  3001,  3012,  3013,  3016,
    3025,  3029,  3035,  3041,  3046,  3049,  3054,  3059,  3062,  3068,
    3073,  3081,  3082,  3084,  3088,  3096,  3100,  3103,  3107,  3113,
    3117,  3121,  3129,  3130,  3133,  3139,  3143,  3146,  3271,  3276,
    3281,  3286,  3291,  3297,  3327,  3331,  3335,  3339,  3343,  3349,
    3353,  3356,  3360,  3366,  3380,  3389,  3397,  3398,  3399,  3402,
    3403,  3406,  3407,  3422,  3438,  3446,  3447,  3448,  3451,  3452,
    3455,  3462,  3463,  3466,  3480,  3487,  3488,  3503,  3504,  3505,
    3506,  3507,  3510,  3513,  3519,  3525,  3529,  3533,  3540,  3547,
    3554,  3561,  3567,  3573,  3579,  3582,  3583,  3586,  3592,  3598,
    3604,  3611,  3618,  3626,  3627,  3630,  3634,  3642,  3646,  3649,
    3654,  3659,  3663,  3669,  3685,  3704,  3710,  3711,  3717,  3718,
    3724,  3725,  3726,  3727,  3728,  3729,  3730,  3731,  3732,  3733,
    3734,  3735,  3736,  3739,  3740,  3744,  3750,  3751,  3757,  3758,
    3764,  3765,  3771,  3774,  3775,  3786,  3787,  3790,  3794,  3797,
    3803,  3809,  3810,  3813,  3814,  3815,  3818,  3822,  3826,  3831,
    3836,  3841,  3847,  3851,  3855,  3859,  3865,  3870,  3874,  3882,
    3891,  3892,  3895,  3898,  3902,  3907,  3913,  3914,  3917,  3920,
    3924,  3928,  3932,  3937,  3944,  3949,  3957,  3962,  3971,  3972,
    3978,  3979,  3980,  3983,  3984,  3988,  3992,  3998,  3999,  4002,
    4008,  4012,  4015,  4020,  4026,  4027,  4030,  4031,  4032,  4038,
    4039,  4040,  4041,  4044,  4045,  4051,  4052,  4055,  4056,  4059,
    4065,  4072,  4079,  4090,  4091,  4092,  4095,  4103,  4115,  4122,
    4125,  4131,  4135,  4138,  4144,  4153,  4164,  4170,  4196,  4197,
    4206,  4207,  4210,  4219,  4230,  4231,  4232,  4233,  4234,  4235,
    4236,  4237,  4238,  4239,  4240,  4241,  4242,  4243,  4244,  4247,
    4270,  4271,  4272,  4275,  4276,  4277,  4278,  4279,  4282,  4286,
    4289,  4293,  4300,  4303,  4319,  4320,  4324,  4330,  4331,  4337,
    4338,  4344,  4345,  4351,  4354,  4355,  4366,  4372,  4378,  4379,
    4382,  4388,  4389,  4390,  4393,  4400,  4405,  4410,  4413,  4417,
    4421,  4427,  4428,  4435,  4441,  4442,  4445,  4446,  4449,  4455,
    4461,  4465,  4468,  4472,  4476,  4486,  4490,  4493,  4499,  4506,
    4510,  4516,  4530,  4544,  4549,  4555,  4571,  4575,  4583,  4587,
    4591,  4601,  4604,  4605,  4608,  4609,  4610,  4611,  4622,  4633,
    4639,  4660,  4666,  4683,  4689,  4690,  4691,  4694,  4695,  4696,
    4699,  4700,  4703,  4719,  4725,  4731,  4738,  4752,  4760,  4768,
    4774,  4778,  4782,  4786,  4790,  4797,  4802,  4813,  4827,  4833,
    4837,  4841,  4845,  4849,  4853,  4857,  4861,  4867,  4873,  4881,
    4882,  4883,  4886,  4887,  4891,  4897,  4898,  4904,  4905,  4911,
    4912,  4918,  4921,  4922,  4923,  4932,  4943,  4944,  4947,  4955,
    4956,  4957,  4958,  4959,  4960,  4961,  4962,  4963,  4964,  4965,
    4966,  4967,  4968,  4971,  4972,  4973,  4974,  4975,  4982,  4989,
    4996,  5003,  5010,  5017,  5024,  5031,  5038,  5045,  5052,  5059,
    5066,  5069,  5070,  5071,  5072,  5073,  5074,  5075,  5078,  5082,
    5086,  5090,  5094,  5098,  5104,  5105,  5115,  5119,  5123,  5139,
    5140,  5143,  5144,  5145,  5146,  5147,  5150,  5151,  5152,  5153,
    5154,  5155,  5156,  5157,  5158,  5159,  5160,  5161,  5162,  5163,
    5164,  5165,  5166,  5167,  5168,  5169,  5170,  5171,  5172,  5173,
    5176,  5196,  5200,  5214,  5218,  5222,  5228,  5232,  5238,  5239,
    5240,  5243,  5244,  5247,  5248,  5251,  5257,  5258,  5261,  5262,
    5265,  5266,  5269,  5270,  5273,  5281,  5308,  5313,  5318,  5324,
    5325,  5328,  5332,  5352,  5353,  5354,  5355,  5358,  5362,  5366,
    5372,  5373,  5376,  5377,  5378,  5379,  5380,  5381,  5382,  5383,
    5384,  5385,  5386,  5387,  5388,  5389,  5390,  5391,  5392,  5395,
    5396,  5397,  5398,  5399,  5400,  5401,  5404,  5405,  5406,  5407,
    5410,  5411,  5412,  5413,  5416,  5417,  5420,  5426,  5434,  5447,
    5454,  5460,  5466,  5475,  5476,  5477,  5478,  5479,  5480,  5481,
    5482,  5483,  5484,  5485,  5486,  5487,  5488,  5489,  5490,  5491,
    5492,  5493,  5494,  5495,  5496,  5499,  5508,  5509,  5510,  5511,
    5524,  5530,  5531,  5532,  5535,  5541,  5542,  5543,  5544,  5545,
    5548,  5554,  5555,  5556,  5557,  5558,  5559,  5560,  5561,  5562,
    5565,  5569,  5577,  5584,  5585,  5586,  5587,  5588,  5589,  5590,
    5591,  5592,  5593,  5594,  5595,  5598,  5599,  5600,  5601,  5604,
    5605,  5606,  5607,  5608,  5611,  5617,  5618,  5619,  5620,  5621,
    5622,  5623,  5626,  5632,  5633,  5634,  5635,  5638,  5644,  5645,
    5646,  5647,  5648,  5649,  5650,  5651,  5652,  5654,  5660,  5661,
    5662,  5663,  5664,  5665,  5666,  5667,  5670,  5676,  5677,  5678,
    5679,  5680,  5683,  5689,  5690,  5693,  5699,  5700,  5701,  5704,
    5710,  5711,  5712,  5713,  5716,  5722,  5723,  5724,  5725,  5728,
    5732,  5737,  5741,  5748,  5749,  5750,  5751,  5752,  5753,  5754,
    5755,  5756,  5757,  5758,  5759,  5760,  5761,  5764,  5765,  5766,
    5769,  5770,  5773,  5781,  5789,  5790,  5793,  5801,  5809,  5810,
    5813,  5817,  5824,  5825,  5826,  5829,  5836,  5843,  5844,  5845,
    5846,  5847,  5848,  5849,  5850,  5851,  5852,  5855,  5860,  5865,
    5870,  5875,  5880,  5887,  5888,  5889,  5890,  5891,  5894,  5895,
    5896,  5897,  5898,  5899,  5900,  5901,  5902,  5903,  5904,  5905,
    5914,  5915,  5918,  5921,  5922,  5925,  5928,  5931,  5937,  5938,
    5939,  5942,  5943,  5944,  5945,  5946,  5947,  5948,  5949,  5950,
    5951,  5952,  5953,  5954,  5955,  5956,  5957,  5958,  5959,  5962,
    5963,  5964,  5967,  5968,  5969,  5970,  5973,  5974,  5975,  5976,
    5977,  5980,  5981,  5982,  5983,  5986,  5991,  5995,  5999,  6003,
    6007,  6011,  6016,  6021,  6026,  6031,  6036,  6043,  6047,  6053,
    6054,  6055,  6056,  6059,  6067,  6068,  6071,  6072,  6073,  6074,
    6075,  6076,  6077,  6078,  6081,  6087,  6088,  6091,  6097,  6098,
    6099,  6100,  6103,  6109,  6115,  6121,  6124,  6130,  6131,  6132,
    6133,  6139,  6145,  6146,  6147,  6148,  6149,  6150,  6153,  6159,
    6160,  6163,  6169,  6170,  6171,  6172,  6173,  6176,  6190,  6191,
    6192,  6193,  6194
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
  "\"param-problem\"", "\"max-delay\"", "\"ah\"", "\"reserved\"",
  "\"spi\"", "\"esp\"", "\"comp\"", "\"flags\"", "\"cpi\"", "\"port\"",
  "\"udp\"", "\"sport\"", "\"dport\"", "\"udplite\"", "\"csumcov\"",
  "\"tcp\"", "\"ackseq\"", "\"doff\"", "\"window\"", "\"urgptr\"",
  "\"option\"", "\"echo\"", "\"eol\"", "\"mptcp\"", "\"nop\"", "\"sack\"",
  "\"sack0\"", "\"sack1\"", "\"sack2\"", "\"sack3\"", "\"sack-permitted\"",
  "\"fastopen\"", "\"md5sig\"", "\"timestamp\"", "\"count\"", "\"left\"",
  "\"right\"", "\"tsval\"", "\"tsecr\"", "\"subtype\"", "\"dccp\"",
  "\"vxlan\"", "\"vni\"", "\"gre\"", "\"gretap\"", "\"geneve\"",
  "\"sctp\"", "\"chunk\"", "\"data\"", "\"init\"", "\"init-ack\"",
  "\"heartbeat\"", "\"heartbeat-ack\"", "\"abort\"", "\"shutdown\"",
  "\"shutdown-ack\"", "\"error\"", "\"cookie-echo\"", "\"cookie-ack\"",
  "\"ecne\"", "\"cwr\"", "\"shutdown-complete\"", "\"asconf-ack\"",
  "\"forward-tsn\"", "\"asconf\"", "\"tsn\"", "\"stream\"", "\"ssn\"",
  "\"ppid\"", "\"init-tag\"", "\"a-rwnd\"", "\"num-outbound-streams\"",
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
  "set_flag", "map_block_alloc", "map_block_obj_type", "map_block",
  "set_mechanism", "set_policy_spec", "flowtable_block_alloc",
  "flowtable_block", "flowtable_expr", "flowtable_list_expr",
  "flowtable_expr_member", "data_type_atom_expr", "data_type_expr",
  "obj_block_alloc", "counter_block", "quota_block", "ct_helper_block",
  "ct_timeout_block", "ct_expect_block", "limit_block", "secmark_block",
  "synproxy_block", "type_identifier", "hook_spec", "prio_spec",
  "extended_prio_name", "extended_prio_spec", "int_num", "dev_spec",
  "flags_spec", "policy_spec", "policy_expr", "chain_policy", "identifier",
  "string", "time_spec", "family_spec", "family_spec_explicit",
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
     615,   616,    61,   123,   125,    40,    41,   124,    36,    91,
      93
};
#endif

#define YYPACT_NINF (-1807)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1036)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1807,  7898, -1807,   632, -1807, -1807,   254,   139,   139,   139,
    1107,  1107,  1107,  1107,  1107,  1107,  1107,  1107, -1807, -1807,
    4064,   201,  2701,   298,  1176,   375,  2887,   765,  1428,   385,
    7509,   243,   364,  1868,   346, -1807, -1807, -1807, -1807,   303,
    1107,  1107,  1107,  1107, -1807, -1807, -1807,  1236, -1807,   139,
   -1807,   139,   210,  6664, -1807,   632, -1807, -1807,   100,   134,
     632,   139, -1807,   107,   113,  6664,   139, -1807,   315, -1807,
     139, -1807, -1807,  1107, -1807,  1107,  1107,  1107,  1107,  1107,
    1107,  1107,   397,  1107,  1107,  1107,  1107, -1807,  1107, -1807,
    1107,  1107,  1107,  1107,  1107,  1107,  1107,  1107,   516,  1107,
    1107,  1107,  1107, -1807,  1107, -1807,  1107,  1107,  1107,  1107,
    1107,  1107,  1278,  1107,  1107,  1107,  1107,  1107,   271,  1107,
    1107,  1107,   112,  1107,  1515,  1773,  1933,  2245,  1107,  1107,
    1107,  2468, -1807,  1107,  1542,  1107,  2668,  2778,  1107, -1807,
    1107,  1107,  1107,  1107,  1107,   457,  1107, -1807,  1107, -1807,
    1258,   833,   762,   440, -1807, -1807, -1807, -1807,   828,  1187,
    1790,  1904,  2982,  1741,   711,  2917,  2746,   807,   168,   991,
     844,   906,  3007,   174,  3324,   728, -1807,  5383,   862,  2175,
     288,   343,   709,   319,   961,   688,  1310,  4295, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,  4842,
   -1807, -1807,   523,  7138,   324,   956,   401,  7509,   139, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1025, -1807,
   -1807,   294, -1807, -1807,  1025, -1807, -1807,  1107,  1107,  1107,
    1107,  1107,  1107,  1107,  1107,   516,  1107,  1107,  1107,  1107,
   -1807, -1807, -1807,  1709, -1807, -1807, -1807,  1107,  1107,  1107,
     -14, -1807, -1807, -1807, -1807, -1807, -1807, -1807,   566,   589,
     603, -1807, -1807, -1807,   470,   426,   924, -1807, -1807, -1807,
     562, -1807, -1807, -1807,    88,    88, -1807,   588,   139,  4631,
    5048,   480,   434, -1807,   280,   697, -1807, -1807, -1807, -1807,
   -1807,   129,   699,   573, -1807,   714,   818, -1807,   500,  6664,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,   890,
   -1807, -1807,   845, -1807, -1807, -1807,   532, -1807,  4944, -1807,
   -1807,   903, -1807,   341, -1807,   456, -1807, -1807, -1807, -1807,
    1087, -1807,   151, -1807, -1807,   849, -1807, -1807, -1807,  1183,
     889,   916,   557, -1807,   746, -1807,  6066, -1807, -1807, -1807,
     874, -1807, -1807, -1807,   907, -1807, -1807,  6423,  6423, -1807,
   -1807,   138,   614,   638, -1807, -1807,   642, -1807, -1807, -1807,
     661, -1807,   668,   978,  6664, -1807,   107,   113, -1807,   315,
   -1807, -1807,  1107,  1107,  1107,   753, -1807, -1807, -1807,  6664,
   -1807,   133, -1807, -1807, -1807,   152, -1807, -1807, -1807,   158,
   -1807, -1807, -1807, -1807,   307, -1807, -1807,   315, -1807,   313,
     712, -1807, -1807, -1807, -1807,  1107, -1807, -1807, -1807, -1807,
     315, -1807, -1807, -1807,  1019, -1807, -1807, -1807, -1807,  1107,
   -1807, -1807, -1807, -1807, -1807, -1807,  1107,  1107, -1807, -1807,
   -1807,  1033,  1035, -1807,  1107,  1040, -1807,  1107, -1807,  1107,
   -1807,  1107, -1807,  1107, -1807, -1807, -1807, -1807,  1107, -1807,
   -1807, -1807,  1107,  1107, -1807, -1807,  1107, -1807,  1107, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1107, -1807,   139,
   -1807, -1807, -1807, -1807,  1100, -1807, -1807, -1807, -1807, -1807,
    1117,   240, -1807, -1807,   824, -1807, -1807,  1042,   286, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807,   249,   301, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807,  1218, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,  3320,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807,  4651, -1807,  5591, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807,  3406, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807,   593, -1807, -1807,   823, -1807, -1807,
   -1807, -1807, -1807, -1807,   832, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807,  2590, -1807, -1807,
   -1807, -1807,   847,   318,   871,  1101, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807,   864,   869, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,   315,
   -1807,   712, -1807,  1107, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1025, -1807, -1807,
   -1807, -1807,    26,   -13,   340,   232, -1807, -1807, -1807,  5152,
    1152,  6930,  7509,  1065, -1807, -1807, -1807, -1807,  1238,  1243,
      86,  1211,  1241,  1256,   122,  1259,  2590,  1265,  6930,   123,
    6930,   964,  6930, -1807, -1807,  1185,  7509,   880,  6930,  6930,
    1210,  1437, -1807,  6048,   140, -1807,  1437, -1807, -1807, -1807,
     965, -1807,  1216,  1221,   890, -1807, -1807, -1807,   732,  1437,
    1227,  1269,  1280,  1437,   845, -1807, -1807,   772, -1807, -1807,
    6930, -1807, -1807,  5360,  1276,  1187,  1790,  1904,  2982, -1807,
    2917,   600, -1807, -1807, -1807, -1807,  1300, -1807, -1807, -1807,
   -1807,  6930, -1807,  1264,  1370,  1387,  1052,   782,   370, -1807,
   -1807, -1807, -1807,  1397,  1233,  1444, -1807, -1807, -1807, -1807,
    1446, -1807, -1807, -1807, -1807,   317, -1807, -1807,  1455,  1457,
   -1807, -1807, -1807,  1343,  1363, -1807, -1807,   903, -1807, -1807,
    1463, -1807, -1807, -1807, -1807,  1465, -1807, -1807,  5568, -1807,
    1465, -1807, -1807, -1807,    85, -1807, -1807,  1087, -1807,  1467,
   -1807,   139, -1807,  1118, -1807,   139,   125, -1807,  8055,  8055,
    8055,  8055,  8055,  7509,   155,  7720, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807,  8055, -1807, -1807, -1807, -1807, -1807, -1807, -1807,   691,
   -1807,  1321,  1474,  1481,  1137,   863,  1499, -1807, -1807, -1807,
    7720,  6930,  6930,  1409,   142,   632,  1507, -1807,  1000,   632,
    1414, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
    1487,  1164,  1170,  1172, -1807,  1189,  1190, -1807, -1807, -1807,
   -1807,  1246,  1245,  1057,  1437, -1807, -1807,  1454,  1458,  1468,
    1475, -1807,  1477,  1195, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807,  1464, -1807, -1807, -1807, -1807, -1807,  1107, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807,  1479,   833, -1807, -1807,
   -1807, -1807,  1485, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807,   992, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807,  1493, -1807,  1405, -1807,
   -1807,  1401, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807,  1240, -1807,  1199,  1469, -1807, -1807, -1807, -1807, -1807,
   -1807,   988,  1299,  1701,  1701, -1807, -1807, -1807,  1368, -1807,
   -1807, -1807, -1807,  1372,  1373, -1807,  1374,  1366,  1376,   776,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1509,
   -1807, -1807,  1511, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807,  1314, -1807,  1317, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807,  1513,  1517,  1279, -1807, -1807,
   -1807, -1807, -1807,  1519,   283, -1807, -1807, -1807,  1255, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807,  1261,  1270,  1273,  1523,
   -1807, -1807,   964, -1807, -1807, -1807,  1525, -1807, -1807, -1807,
   -1807,  6930,  2982,  2917,  1633,  5776, -1807,   151,   178,  1631,
    2819,  1437,  1437,  1537,  7509,  6930,  6930,  6930, -1807,  1539,
    6930,  1593,  6930, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
    1543, -1807,   143,  1625, -1807, -1807,   477,   775,   318, -1807,
     819,   914,   205,  1606, -1807,  6930, -1807, -1807,   818,  1439,
     812,   295, -1807,   858,  1499,   818, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807,  1506,   227, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807,  1001,  1076, -1807,  1156, -1807,
   -1807, -1807,  6930,  1651,  6930, -1807, -1807, -1807,   321,   658,
   -1807,  6930, -1807, -1807,  1292, -1807, -1807,  6930,  6930,  6930,
    6930,  6930,  1556,  6930,  6930,   161,  6930,  1465,  6930,  1575,
    1653,  1581,  3310,  3310, -1807, -1807, -1807,  6930,  1233,  6930,
    1233, -1807,  1645,  1649, -1807,   880, -1807,  7509, -1807,  7509,
   -1807, -1807, -1807,  1321,  1474,  1481, -1807,   818, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807,  1303,  8055,  8055,  8055,  8055,
    8055,  8055,  8055,  8055,  8157,  8055,  8055,   941, -1807,  1169,
   -1807, -1807, -1807, -1807, -1807,  1569, -1807,   540,  2347, -1807,
    2418,  3627,  2758,  3295,   507, -1807, -1807, -1807, -1807, -1807,
   -1807,  1315,  1323,  1331, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1670, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807,  2819, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1325,
    1327, -1807, -1807, -1807, -1807, -1807, -1807,  1279,   219,  1595,
   -1807, -1807, -1807, -1807, -1807,  1371, -1807, -1807, -1807, -1807,
   -1807,  1390,   747, -1807,  1543,  2563, -1807,   736,   143, -1807,
    1168, -1807, -1807,  6930,  6930,  1694, -1807,  1598,  1598, -1807,
     178, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
    1341,  1631,  6664,   178, -1807, -1807, -1807, -1807, -1807, -1807,
    6930, -1807, -1807,   180,  1394,  1396,  1690, -1807, -1807, -1807,
    1398,    85, -1807,  7509,    85,  6930,  1666, -1807,  7949, -1807,
    1522,  1423,  1402,  1410,  1057,   812, -1807,  1598,  1598, -1807,
     295, -1807,  6048, -1807,  4669, -1807, -1807, -1807, -1807,  1714,
   -1807, -1807,  1384, -1807, -1807,  1384, -1807,  1658,  1384, -1807,
   -1807,  6930, -1807, -1807, -1807, -1807, -1807,  1264,  1370,  1387,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1725,  6930,  1570,
    6930, -1807, -1807, -1807, -1807,  1233, -1807,  1233,  1465, -1807,
   -1807,   164,  6664,  6321,   146, -1807, -1807, -1807,  1507,  1727,
   -1807, -1807,  1321,  1474,  1481, -1807,   224,  1507, -1807, -1807,
     858,  8055,  8157, -1807,  1635,  1700, -1807, -1807, -1807, -1807,
   -1807,   139,   139,   139,   139,   139,  1641,   541,   139,   139,
     139,   139, -1807, -1807, -1807,   632, -1807,   114, -1807,  1650,
   -1807, -1807, -1807,   632,   632,   632,   632,   632,  7509, -1807,
    1598,  1598,  1386,  1434,  1648,   808,  1197,  1568, -1807, -1807,
   -1807,   632,   632,   723, -1807,  7509,  1598,  1399,   808,  1197,
   -1807, -1807, -1807,   632,   632,   723,  1665,  1400,  1673, -1807,
   -1807, -1807, -1807, -1807,  5942,  3980,  3128,  3814,  1134, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807,  1647, -1807, -1807,  1671,
   -1807, -1807, -1807,  1766, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807,  1675, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807,  1785, -1807,  1367,   860,  1306,  1676, -1807, -1807, -1807,
   -1807, -1807,  1394,  1396, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807,  1398, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807,  6930, -1807, -1807, -1807, -1807, -1807, -1807,  7509,
    1424,   178, -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1638,
    1767, -1807,  1687, -1807,  1691, -1807,  1638,  1693, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807,  6930,    88,    88,   818,  1499,
   -1807,   167,  1705, -1807,   128,   964,  1712, -1807, -1807, -1807,
   -1807, -1807, -1807,   632, -1807,   227, -1807, -1807, -1807, -1807,
   -1807, -1807,  6930, -1807,  1732, -1807,  1465,  1465,  7509, -1807,
     689,  1433,  1814,   818, -1807,  1507,  1507,  1642,  1721, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
     139,   139,   139, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807,  1723, -1807, -1807, -1807, -1807, -1807, -1807,
     596, -1807,   632,   632,   315, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807,  1135, -1807, -1807, -1807,
   -1807, -1807,  1106, -1807, -1807, -1807, -1807, -1807,   773,   632,
     315,   908,  1106, -1807, -1807, -1807,  1681,   389,   632, -1807,
   -1807, -1807, -1807, -1807, -1807,  1840,  1263,  2038, -1807, -1807,
    1734, -1807,  1279, -1807, -1807, -1807,  1473,   538,  1107, -1807,
   -1807, -1807, -1807, -1807,  1598,  1735,   538,  1737,  1107, -1807,
   -1807, -1807, -1807, -1807,  1738,  1107, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
    6664, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1549,
   -1807,   145, -1807, -1807, -1807,   143, -1807, -1807, -1807, -1807,
   -1807, -1807,  1742,  1554, -1807, -1807,  1543,   143, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807,  6930,  1486,  7509, -1807, -1807,
    1262,  6321, -1807, -1807,  1678,   632,  1488,  1489,  1512,  1516,
    1518, -1807, -1807, -1807,  1527,  1531,  1533,  1534, -1807,  1815,
    7509, -1807, -1807, -1807, -1807, -1807,   808, -1807,  1197, -1807,
    7329, -1807, -1807,  2646, -1807,   177,   632,   170,   632, -1807,
   -1807, -1807, -1807, -1807, -1807,  1863, -1807,  1548, -1807, -1807,
     632,   632, -1807,   632,   632,   632,   632,   632, -1807,  1744,
     632, -1807,  1508, -1807, -1807, -1807, -1807, -1807,  1797, -1807,
   -1807,  1394,  1396,  1398, -1807, -1807, -1807, -1807,  1524,   818,
   -1807, -1807,  1642, -1807, -1807, -1807, -1807, -1807,  1551,  1572,
    1574, -1807, -1807, -1807, -1807,  1798, -1807, -1807, -1807, -1807,
    7509,   632,  1911,  1923, -1807,   808, -1807, -1807, -1807, -1807,
     632,  1135,  1809, -1807, -1807, -1807,  1045, -1807, -1807, -1807,
   -1807, -1807, -1807,   148, -1807, -1807, -1807, -1807, -1807, -1807,
    1830, -1807,  1836, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807,   538, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807,  1678,  2627,  4333,  3220,  4167,  1969, -1807, -1807,
   -1807,  2136,  2608,  2084,  2497,  1504,   596, -1807,  7509, -1807,
    1135, -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1841,  1843,
     147, -1807, -1807,  1944,   150, -1807,   632, -1807, -1807, -1807,
   -1807, -1807,   632,   632,   632,   632,   632,  2545,  1603,  2532,
     632,   632,   632,   632,   199,  1588,  1681, -1807,  1945, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807,  1851,  1836,   632, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807,   389, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807,   632,   632,   632, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     419,   419,   419,   419,   419,   419,   419,   419,   423,   426,
     419,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   229,   425,     9,    28,    29,     0,
     419,   419,   419,   419,    68,    67,     3,     0,    71,     0,
     420,     0,   444,     0,    66,     0,   413,   414,     0,     0,
       0,     0,   595,    87,    89,     0,     0,   280,     0,   302,
       0,   326,    72,   419,    73,   419,   419,   419,   419,   419,
     419,   419,     0,   419,   419,   419,   419,    74,   419,    75,
     419,   419,   419,   419,   419,   419,   419,   419,     0,   419,
     419,   419,   419,    76,   419,    77,   419,   450,   419,   450,
     419,   450,   450,   419,   419,   450,   419,   450,     0,   419,
     450,   450,     0,   419,   450,   450,   450,   450,   419,   419,
     419,   450,    35,   419,   450,   419,   450,   450,   419,    47,
     419,   419,   419,   419,   450,     0,   419,    80,   419,    81,
       0,     0,     0,   752,   723,   415,   416,   417,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    25,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   936,   937,
     938,   939,   940,   941,   942,   943,   944,   945,   946,   947,
     948,   949,   950,   951,   952,   953,   954,   955,   957,     0,
     959,   958,     0,     0,     0,     0,    34,     0,     0,    85,
     719,   718,   724,   725,   244,   735,   736,   729,   927,   730,
     733,   737,   734,   731,   732,   726,  1043,  1044,  1045,  1046,
    1047,  1048,  1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,
      53,  1061,  1062,  1063,  1064,  1058,  1059,  1060,   727,  1306,
    1307,  1308,  1309,  1310,  1311,  1312,  1313,   728,     0,   241,
     242,     0,    33,   225,     0,    21,   227,   419,   419,   419,
     419,   419,   419,   419,   419,     0,   419,   419,   419,   419,
      16,   230,    39,   231,   424,   421,   422,   419,   419,   419,
      13,   848,   821,   823,    70,    69,   427,   429,     0,     0,
       0,   446,   445,   447,     0,   585,     0,   703,   704,   705,
       0,   918,   919,   920,   487,   488,   923,   710,     0,     0,
       0,   503,   509,   514,     0,   538,   563,   575,   576,   652,
     658,   679,     0,     0,   963,     0,     7,    92,   452,   454,
     468,   455,    61,   264,   483,   464,   491,   462,    13,   501,
      14,    59,   512,   460,   461,    46,   566,    40,     0,    54,
      60,   583,    40,   651,    40,   657,    18,    24,   474,    45,
     677,   480,     0,   481,   466,     0,   709,   465,   754,   757,
     759,   761,   763,   764,   771,   773,     0,   772,   716,   490,
     927,   469,   475,   467,   726,   484,    62,     0,     0,    65,
     438,     0,     0,     0,    91,   432,     0,    95,   295,   294,
       0,   435,     0,     0,     0,   595,   112,   114,   280,     0,
     302,   326,   419,   419,   419,    13,   848,   821,   823,     0,
      60,     0,   136,   137,   138,     0,   130,   131,   139,     0,
     132,   133,   140,   141,     0,   134,   135,     0,   142,     0,
     144,   145,   825,   826,   824,   419,    13,    36,    44,    51,
       0,    60,   202,   451,   204,   169,   170,   171,   172,   419,
     173,   175,   199,   198,   197,   191,   419,   450,   195,   194,
     196,   825,   826,   827,   419,     0,    13,   419,   176,   419,
     179,   419,   182,   419,   188,    36,    44,    51,   419,   185,
      78,   215,   419,   419,   212,    13,   419,   206,   419,   209,
      44,    79,   216,   217,   218,   219,   222,   419,   221,     0,
    1069,  1066,  1067,    56,     0,   743,   744,   745,   746,   747,
     749,     0,   968,   970,     0,   969,    52,     0,     0,  1304,
    1305,    56,  1071,  1072,    55,    20,    55,  1075,  1076,  1077,
    1078,    30,     0,     0,  1081,  1082,  1083,  1084,  1085,     9,
    1103,  1104,  1098,  1093,  1094,  1095,  1096,  1097,  1099,  1100,
    1101,  1102,     0,    28,    55,  1118,  1117,  1116,  1119,  1120,
    1121,    31,    55,  1124,  1125,  1126,    32,  1135,  1136,  1128,
    1129,  1130,  1132,  1131,  1133,  1134,    29,    55,  1143,  1140,
    1139,  1144,  1142,  1141,  1145,    31,  1148,  1151,  1147,  1149,
    1150,     8,  1154,  1153,    19,  1156,  1157,  1158,    11,  1162,
    1163,  1160,  1161,    57,  1168,  1165,  1166,  1167,    58,  1215,
    1209,  1212,  1213,  1207,  1208,  1210,  1211,  1214,  1216,     0,
    1169,    55,  1248,  1249,    15,  1195,  1194,  1187,  1188,  1189,
    1173,  1174,  1175,  1176,  1177,  1178,  1179,  1180,  1181,  1182,
      53,  1191,  1190,  1193,  1192,  1184,  1185,  1186,  1202,  1204,
    1203,     0,    25,     0,  1199,  1198,  1197,  1196,  1302,  1299,
    1300,     0,  1301,    49,    55,    28,  1319,   995,    29,  1318,
    1321,   993,   994,    34,     0,    48,    48,     0,    48,  1325,
      48,  1328,  1327,  1329,     0,    48,  1316,  1315,    27,  1337,
    1334,  1332,  1333,  1335,  1336,    23,  1340,  1339,    17,    55,
    1343,  1346,  1342,  1345,    38,    37,   931,   932,   933,    51,
     934,    34,    37,   929,   930,  1010,  1011,  1017,  1003,  1004,
    1002,  1012,  1013,  1033,  1006,  1015,  1008,  1009,  1014,  1005,
    1007,  1000,  1001,  1031,  1030,  1032,    51,     0,    12,  1018,
     974,   973,     0,   771,     0,     0,    48,    27,    23,    17,
      38,  1347,   978,   979,   956,   977,     0,   717,  1057,   224,
     243,    82,   226,    83,    60,   153,   154,   155,   156,     0,
     157,   159,   160,   419,    13,    36,    44,    51,    86,    84,
     232,   233,   235,   234,   237,   238,   236,   239,   845,   845,
     845,    97,     0,     0,   538,     0,   441,   442,   443,     0,
       0,     0,     0,     0,   925,   924,   921,   922,     0,     0,
       0,    37,    37,     0,     0,     0,     0,    12,     0,     0,
       0,   547,     0,   536,   537,     0,     0,     0,     0,     0,
       0,     0,     6,     0,     0,   775,     0,   453,   456,   485,
       0,   459,     0,     0,   502,   505,   463,   470,     0,     0,
       0,     0,     0,     0,   513,   515,   471,     0,   562,   472,
       0,    47,    16,     0,     0,    20,    30,     9,    28,   886,
      29,     0,   891,   889,   890,    14,     0,    40,    40,   876,
     877,     0,   613,   616,   618,   620,   622,   623,   628,   633,
     631,   632,   634,   636,   574,   600,   601,   611,   878,   602,
     609,   603,   610,   606,   607,     0,   604,   605,     0,   635,
     608,   473,   482,     0,     0,   592,   591,   584,   587,   476,
       0,   670,   671,   672,   650,   655,   668,   477,     0,   656,
     661,   478,   479,   673,     0,   695,   696,   678,   680,   683,
     693,     0,   721,     0,   720,     0,     0,   711,     0,     0,
       0,     0,     0,     0,     0,     0,   911,   912,   913,   914,
     915,   916,   917,    20,    30,     9,    28,    31,   903,    29,
      31,     8,    19,    11,    57,    58,    53,    15,    25,    49,
      40,     0,   893,   861,   894,   768,   769,   873,   860,   850,
     849,   865,   867,   869,   871,   872,   859,   895,   896,   862,
       0,     0,     0,     0,     7,     0,   815,   814,   872,     0,
       0,   382,    60,   248,   265,   281,   308,   327,   448,   111,
       0,     0,     0,     0,   118,     0,     0,   845,   845,   845,
     120,     0,     0,   538,     0,   129,   152,     0,     0,     0,
       0,   143,     0,     0,   845,   147,   150,   148,   151,   168,
     190,     0,   205,   174,   193,   192,    12,   419,   178,   177,
     180,   183,   189,   184,   181,   187,   186,   213,   214,   208,
     207,   210,   211,   220,   223,  1068,     0,     0,    55,   740,
     741,    22,     0,   966,   753,    42,    42,  1303,  1073,  1070,
    1079,  1074,    20,    28,    20,    28,  1080,  1105,  1106,  1107,
    1108,    28,  1090,  1115,  1114,  1123,  1122,  1127,  1138,  1137,
    1146,  1152,  1155,  1159,  1164,    10,  1233,  1239,  1237,  1228,
    1229,  1232,  1234,  1223,  1224,  1225,  1226,  1227,  1235,  1230,
    1231,  1236,  1171,  1238,  1170,  1250,  1247,  1183,  1201,  1200,
    1205,  1254,  1251,  1252,  1253,  1255,  1256,  1257,  1258,  1259,
    1260,  1261,  1262,  1263,  1264,  1265,  1266,  1267,  1268,  1285,
      50,  1297,  1320,   989,   990,   996,    48,   991,  1317,     0,
    1322,  1324,     0,  1326,  1314,  1331,  1338,  1344,  1341,   928,
     935,   926,  1016,  1019,  1020,     0,  1022,     0,  1021,  1023,
    1024,    12,    12,  1025,   997,     0,     0,   971,  1349,  1348,
    1350,  1351,  1352,     0,     0,   738,   167,   158,     0,   845,
     162,   165,   163,   166,   228,   240,     0,     0,     0,     0,
     347,    13,   547,   372,    36,   352,     0,    44,   377,   822,
      51,     0,    28,    29,   577,     0,   586,     0,   697,   699,
       0,     0,     0,     0,     0,     0,     0,     0,    12,     0,
       0,  1025,     0,   504,   418,   510,   511,    36,   545,   546,
       0,    44,     0,     0,   692,    45,   687,   686,     0,   691,
     689,   690,     0,   664,   666,     0,   486,   787,     7,     7,
     789,   784,   786,   872,   811,     7,   774,   449,   273,   507,
     508,   506,   528,    20,     0,     0,   526,   522,   517,   518,
     519,   520,   523,   521,   516,     0,     0,    53,     0,   642,
     887,   888,     0,   637,     0,   879,   882,   883,   880,   881,
     892,     0,   885,   884,     0,   600,   609,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   644,     0,     0,
       0,     0,     0,     0,   589,   590,   588,     0,     0,     0,
     659,   682,   687,   686,   681,     0,    10,     0,   713,     0,
     712,   755,   756,   758,   760,   762,   765,     7,   492,   494,
     770,   880,   902,   881,   904,   901,   900,   906,   898,   899,
     897,   907,   905,   908,   909,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   856,   855,   872,
     961,  1042,   817,   816,    63,     0,    64,     0,     0,   109,
       0,     0,     0,     0,     0,    60,   248,   265,   281,   308,
     327,     0,     0,     0,    13,    36,    44,    51,   439,   428,
     430,   433,   436,   327,    12,   203,   200,    12,     0,   748,
     742,   739,    52,   750,   751,  1086,  1088,  1087,  1089,    55,
    1110,  1112,  1111,  1113,  1092,    28,     0,  1245,  1217,  1242,
    1219,  1246,  1222,  1243,  1244,  1220,  1240,  1241,  1218,  1221,
    1282,  1281,  1283,  1284,  1290,  1272,  1273,  1274,  1275,  1287,
    1276,  1277,  1278,  1279,  1280,  1288,  1289,  1291,  1292,  1293,
    1294,  1295,  1296,    55,  1271,  1270,  1286,    49,   992,     0,
       0,    28,    28,    29,    29,   998,   999,   971,   971,     0,
      26,   976,   980,   981,    34,     0,   327,    12,   362,   367,
     357,     0,     0,    98,     0,     0,   105,     0,     0,   100,
       0,   107,   579,     0,     0,   578,   700,     0,     0,   794,
     698,   790,  1233,  1237,  1232,  1236,  1238,    53,    10,    10,
       0,   783,     0,   781,    37,    37,    12,   499,    12,    12,
       0,    12,   535,     0,   548,   551,     0,   544,   540,   539,
     541,     0,   674,     0,     0,     0,     0,   778,     0,   779,
       0,    13,     0,     0,   538,   788,   797,     0,     0,   810,
     785,   795,   777,   776,     0,   527,    28,   531,   532,    53,
     530,   564,     0,   568,   565,     0,   570,     0,     0,   572,
     643,     0,   647,   649,   612,   614,   615,   617,   619,   621,
     629,   630,   624,   627,   626,   625,   639,   638,     0,     0,
       0,  1034,  1035,  1036,  1037,   653,   669,   660,   662,   694,
     722,     0,     0,     0,     0,   495,   910,   858,   852,     0,
     863,   864,   866,   868,   870,   857,   766,   851,   767,   874,
     875,     0,     0,   766,     0,     0,    60,   384,   383,   386,
     385,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    88,   250,   249,     0,   247,     0,    55,     0,
      90,   267,   266,     0,     0,     0,     0,     0,     0,   291,
       0,     0,     0,     0,     0,     0,     0,     0,    93,   283,
     282,     0,     0,     0,   457,     0,     0,     0,     0,     0,
      94,   310,   309,     0,     0,     0,     0,     0,     0,    13,
      96,   329,   328,   128,     0,     0,     0,     0,     0,   362,
     367,   357,   121,   126,   122,   127,     0,   149,   201,     0,
     967,  1109,  1091,     0,  1269,  1298,  1323,  1330,  1026,  1027,
    1028,  1029,    41,     0,    26,   972,   988,   984,   983,   982,
      34,     0,   164,     0,     0,     0,     0,    13,   349,   348,
     351,   350,   548,   551,    36,   374,   373,   376,   375,    44,
     354,   353,   356,   355,   541,    51,   379,   378,   381,   380,
     580,   582,     0,   792,   793,   791,  1206,   965,   964,     0,
       0,   782,   962,   960,  1039,   500,  1040,    12,  1038,     0,
     553,   555,     0,    36,     0,    36,     0,     0,    44,   688,
     684,   685,    45,    45,   665,     0,     0,     0,     7,   812,
     813,     0,     0,   799,     0,   547,     0,   798,   808,   809,
     796,   489,   274,     0,   525,     0,   524,    55,    55,    47,
      55,   640,     0,   646,     0,   648,   654,   663,     0,   701,
       0,     0,     0,     7,   493,   854,   853,   596,     0,   110,
     440,   346,   431,   264,   434,   280,   302,   437,   326,   246,
       0,     0,     0,   346,   346,   346,   346,   251,   411,   412,
      43,   410,   409,     0,   407,   268,   270,   269,   272,   271,
       0,   278,     0,     0,     0,   325,   324,    43,   323,   387,
     389,   390,   388,   343,   391,   344,     0,   342,   298,   299,
     301,   300,     0,   297,   292,   293,   289,   458,     0,     0,
       0,     0,     0,   321,   320,   318,     0,     0,     0,   332,
     113,   115,   116,   117,   119,     0,     0,     0,   146,    10,
       0,   975,   971,   987,   985,   161,     0,     0,     0,    12,
     364,   363,   366,   365,     0,     0,     0,     0,     0,    12,
     369,   368,   371,   370,     0,     0,    12,   359,   358,   361,
     360,   818,    99,   846,   847,   106,   101,   820,   108,   581,
       0,   714,  1041,   557,   558,   559,   560,   561,   550,     0,
     533,     0,   552,   534,   554,     0,   543,   675,   676,   667,
     780,    12,     0,     0,    14,    14,     0,     0,   275,   529,
      31,    31,   573,   571,   641,     0,     0,     0,   702,   708,
       0,   497,   496,   597,   598,     0,     0,     0,     0,     0,
       0,   346,   346,   346,     0,     0,     0,     0,   408,     0,
       0,   285,   287,   288,   290,   322,     0,    55,     0,   286,
       0,   311,   319,     0,   317,     0,     0,     0,     0,   335,
     333,    12,    12,    12,  1065,     0,    26,     0,    57,    53,
       0,     0,   103,     0,     0,     0,     0,     0,   104,     0,
       0,   102,     0,   549,   556,   542,   803,    12,     0,   806,
     807,   548,   551,   541,   567,   569,   645,   706,     0,     7,
     599,   593,   596,   382,   265,   281,   308,   327,     0,     0,
       0,   347,   372,   352,   377,     0,   279,   345,   284,   296,
       0,     0,     0,   276,    60,     0,    13,    36,    44,    51,
       0,     0,     0,   401,   395,   394,   398,   393,   396,   397,
     330,   340,   339,     0,   336,   341,   331,   124,   125,   123,
       0,   986,     0,   831,   830,   837,   839,   842,   843,   840,
     841,   844,     0,   833,   715,   804,    13,    36,    36,    44,
     707,   498,   598,     0,     0,     0,     0,     0,   362,   367,
     357,     0,     0,     0,     0,   406,     0,   314,     0,   307,
       0,   303,   305,   304,   306,    55,    55,   402,     0,     0,
       7,   334,  1172,     0,     0,   834,     0,   800,   801,   802,
     805,   594,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   315,   277,    55,
     316,   312,   400,   399,   338,   337,     0,     0,     0,    55,
      60,   252,   253,   254,   255,    12,    12,    12,    13,    36,
      44,    51,   403,   404,     0,   392,   313,   836,   835,    43,
     832,   263,     0,     0,     0,   256,   261,   257,   262,   405,
     838,   259,   260,   258
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1807, -1807,    -1, -1257,   962,    65, -1292,   963,  -520,  -353,
    -873,   969,  1080,  1200, -1807,   979,  -463, -1807, -1807,  1204,
   -1807,  -129, -1576,  1206,   -29,   -24,  1426,  -590, -1807, -1807,
    -667, -1807,  -474,  -703,  1209, -1807,  -275, -1807,   875, -1806,
    -472, -1200, -1807,  -853,  -462,  -909, -1807,  -494,   518,  -641,
   -1807,  -440,  1448,  -971,   995, -1807,  -428, -1807,    17, -1807,
   -1807,  1981, -1807, -1807, -1807,  1729,  1726,  1731,  1017, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807,    25, -1807,  1582, -1807,   568,  -334,
   -1387, -1807, -1807, -1610,  -421, -1386,  -420,   266,   -80,  -410,
   -1807, -1377, -1394, -1807,  -407, -1380,  -285, -1807,  -219,   -64,
   -1617,  -767,  -127,  -128, -1654, -1648, -1646,  -126,  -123,  -108,
   -1807, -1807,  -230, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807,   156,  -729, -1285,   229,   -46,  3260, -1807,   290, -1807,
   -1807,   181, -1807,   351,   768,  1772, -1807,   223, -1807,  -666,
    1637, -1807, -1807,   242,   185,   857,   784,   -43, -1807, -1807,
   -1398, -1375,  -343, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
     165, -1807, -1807, -1807, -1807,  1196, -1807, -1807, -1807, -1807,
    1188, -1807, -1807, -1807,   184, -1807,  -318, -1410, -1643, -1807,
   -1175, -1652, -1449, -1626, -1440,   217,   221, -1807, -1807,  -894,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807,  1128,  -325,  1654,
     -68,  -140,  -193,   727,   729,   726, -1807,  -801, -1807, -1807,
   -1807, -1807, -1807, -1807,  1689, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807,  -347,   716, -1807, -1807, -1807, -1807,
    1125,   495,  -880,   494,  1244,   713, -1311, -1807, -1807,  1784,
   -1807, -1807, -1807, -1807,  1126, -1807, -1807,   -67,    -9,  -848,
    -342,  1069,   -27, -1807, -1807, -1807,   996,   108, -1807, -1807,
   -1807, -1807, -1807,  -162,  -202, -1807, -1807,   678,  -783,  1893,
     -52, -1807,   793, -1264, -1807, -1544, -1807, -1807,   526, -1350,
   -1807, -1807,   499,   496, -1807, -1807,  1707,  -603,  1683,  -594,
    1684,  -587,  1692,   299, -1807, -1796, -1807, -1807,  -160, -1807,
   -1807,  -591,  -513,  1697, -1807,  -370,  -309,  -868,  -847,  -854,
   -1807,  -366,  -840, -1807,  -173,  1789,  -820, -1807, -1499,  -321,
     126,  1799, -1807,   -38, -1807,   292, -1807, -1411, -1807,   406,
   -1807, -1807, -1807, -1807, -1807,   706,  -279,   787,  1431,   953,
    1806,  1811, -1807, -1807,  -498,   212, -1807, -1807, -1807,   960,
   -1807, -1807,   -71, -1807,   -70, -1807,   -66, -1807,   -59, -1807,
   -1807, -1807,   -55, -1807,   -54, -1807,   -44, -1807,   -32, -1807,
      -6, -1807,    -2, -1807,     3, -1807,     8, -1807,    12, -1807,
      24,  1472, -1807,   -75, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807,  1490, -1034, -1807, -1807, -1807, -1807,
   -1807,    29, -1807, -1807, -1807, -1807,   971, -1807, -1807,    39,
   -1807,    47, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807, -1807,
   -1807, -1807
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,  1761,   863,  1140,  1347,  1486,  1142,  1224,   821,
     876,  1166,   808,  1206,   961,  1141,  1345,   793,  1471,  1205,
     962,   681,  1796,  1204,  1401,  1403,  1346,  1134,  1136,   791,
     784,   510,  1076,  1209,  1208,   809,   889,  1991,  1473,  2088,
    1077,   963,   886,   521,  1197,  1191,  1527,  1078,  1113,   788,
     941,  1118,  1105,  1143,  1144,   877,   942,   869,  1762,    46,
      47,    48,    74,    87,    89,   444,   448,   453,   440,   103,
     290,   105,   132,  1082,   472,   139,   147,   149,   272,   275,
     292,   293,   817,  1244,   273,   219,   412,  1715,  1440,   413,
    1441,  1624,  2171,  1940,   416,  1442,   417,  1962,  1963,   420,
    2180,  1443,  1741,  1947,   422,  1444,  2108,  2193,  2194,  1955,
    1956,  2076,  1552,  1557,  1805,  1803,  1804,  1555,  1560,  1438,
    1957,  1723,  2106,  2186,  2187,  2188,  2276,  1724,  1725,  1930,
    1931,  1910,   220,  1286,    49,    50,    61,   447,    52,   451,
    1913,   455,   456,  1915,    71,   461,  1918,   442,   443,  1911,
     311,   312,   313,    53,   424,  1569,   474,  1727,   348,   349,
    1743,   350,   351,   352,   353,   354,   355,   356,  1398,  1674,
    1675,   357,   358,   359,   874,   875,   360,   361,   362,   884,
     885,  1333,  1327,  1629,  1630,   363,  1256,  1600,  1858,   364,
    1290,  1853,  1594,  1855,  1595,  1596,  2038,   365,   366,  1633,
     888,   367,   368,   369,   370,   371,   947,   948,  1700,   411,
    2074,  2151,   912,   913,   914,   915,   916,   917,   918,  1653,
     919,   920,   921,   922,   923,   924,   372,   373,   954,   374,
     375,   959,   376,   377,   955,   956,   378,   379,   380,   967,
     968,  1293,  1294,  1295,   969,   970,  1267,  1268,   381,   382,
     383,   384,   385,   976,   977,   386,   387,   221,   925,   973,
    1013,   926,   388,   225,  1111,   540,   541,   927,   548,   389,
     390,   391,   392,   393,   394,  1015,  1016,  1017,   395,   396,
     397,   864,   865,  1582,  1583,  1309,  1310,  1311,  1570,  1571,
    1620,  1615,  1616,  1621,  1312,  1868,  1035,  1811,   822,  1823,
     824,  1829,   825,   465,   495,  2120,  2020,  2254,  2255,  2003,
    2013,  1246,  1818,   823,   398,  1036,  1037,  1021,  1022,  1023,
    1024,  1313,  1026,   928,   929,   930,  1029,  1030,   399,   836,
     931,   742,   743,   228,   401,   932,   546,  1540,   772,   933,
    1234,   785,  1544,  1800,   231,   934,   704,   936,   705,   937,
     767,   768,  1221,  1222,   769,   938,   939,   402,   403,   940,
     236,   534,   237,   555,   238,   561,   239,   569,   240,   583,
    1131,  1485,   241,   591,   242,   596,   243,   606,   244,   615,
     245,   621,   246,   624,   247,   628,   248,   633,   249,   638,
     250,   671,   672,   673,   251,   674,   252,   687,   253,   682,
     254,   405,   650,  1162,  1576,  1164,  1498,  1490,  1495,  1488,
    1492,   255,   654,  1189,  1526,  1509,  1515,  1504,  1190,   256,
     693,   257,   551,   258,   259,   718,   260,   706,   261,   708,
     262,   710,   263,   715,   264,   725,   265,   728,   266,   734,
     267,   781
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,   418,    54,   224,   837,   871,   868,  1053,   295,  1054,
     347,   773,  1066,  1095,   296,   400,   419,   855,    45,   870,
    1055,   222,   414,  1314,  1056,  1139,  1019,   400,   960,  1167,
    1025,  1093,  1350,  1408,  1094,   830,  1195,  1071,  1340,  1211,
     974,  1038,  1038,  1080,   222,  1755,   305,   683,  1102,  1753,
    1079,  1607,  1609,  1073,   406,   786,   222,   276,  1622,   409,
    1765,   473,  1766,   473,   860,   473,   473,  1744,  1744,   473,
    1768,   473,  1767,  1299,   473,   473,  1671,  1554,   473,   473,
     473,   473,  1060,  1776,  1381,   473,  1042,  1020,   473,   935,
     473,   473,  1119,  1052,  1670,  1602,  1259,   949,   473,   957,
    1413,   294,   686,   657,   658,  1812,   657,   658,   659,  1870,
    1354,   659,  1393,  1075,  1813,   660,  1120,  1987,   660,   661,
     662,  1985,   661,   662,  1986,  1672,  1792,  1794,  1395,  1902,
     663,  1971,  1306,   663,  1394,  1968,  1399,  1317,   226,  1211,
    1673,  2095,   664,  1088,  1133,   664,   862,  1315,  1824,   744,
    1328,   862,  1135,  1903,  1332,  2250,   227,  2287,  1391,  1392,
    2023,   226,  1099,    58,    59,    60,  1801,  1138,   665,  1898,
     975,   665,   666,   226,   971,   666,  1040,   667,   971,   227,
     667,  2027,   668,  1273,   971,   668,   669,  2024,   154,   669,
    1067,   227,    56,  1928,  1929,    67,    68,    69,   670,  2182,
    1849,   670,   491,   675,   222,   306,   675,   307,   222,  1068,
    2125,  1165,  1385,   676,   856,  1069,   676,   410,  1993,  1251,
    1835,   677,   415,  1027,   677,  1278,   421,  1284,  1247,  1248,
    1257,  -723,  1284,    62,  1027,  1027,  1577,    56,  1260,  -723,
    -723,  -723,  -723,    56,  1198,  1210,  1200,  1598,  1201,  2134,
      73,  2191,  2192,  1203,  1192,    65,    56,   835,   835,   428,
     429,   430,    56,   300,   301,   302,   303,   308,  1567,  1223,
    2051,  1568,  1212,  1900,  2191,  2192,   457,   458,   452,  -819,
    2183,  2184,  1833,  1834,  1850,   470,  1837,  1838,   651,  1207,
    1603,   744,   857,   789,   481,   482,  1744,  1252,   425,   792,
     488,   268,    64,   155,   156,   157,   435,   436,   437,   438,
    1254,   400,   622,  1243,  1228,   972,   486,   487,   511,  1249,
     445,   226,   229,   524,   525,   226,   983,   528,   623,   471,
     439,  1241,  1878,  1879,  1242,  1259,   155,   156,   157,   227,
     222,   652,   653,   227,  1018,   229,   496,    88,  1281,  -819,
    1253,   505,   506,   507,  1108,  1018,  1018,   229,   515,    55,
    1122,   520,   418,   423,  1070,  1410,  1236,   427,  1967,  1755,
    1072,  1627,   985,  1753,   787,  1123,  1628,   419,  1364,  1237,
    1967,  1049,   450,   423,    57,  1617,   400,  1012,  1618,  1250,
     418,  1744,  1744,   297,  1238,   492,  1065,   464,  1012,  1012,
     477,   400,  1368,   418,  1369,   419,  -989,  1402,  -989,   695,
    1404,    56,  1124,  1115,   493,   222,  2256,    56,   419,  1566,
    1285,   494,   274,   423,  1365,  2054,   950,  1125,   104,    57,
     222,   523,   148,   698,  1279,    57,   230,  1599,   529,  1851,
    1737,   473,  1636,  1542,  1639,  1942,  1943,   716,    57,  1274,
     291,  1240,  1783,   218,    57,   331,   218,   226,  1454,   230,
     332,  1969,   407,   799,   800,   797,  1451,  1452,  1453,  1456,
    -245,   230,   717,   334,  1851,   227,  -264,  1457,   335,  2052,
     834,   834,   218,  1464,   840,  -718,  2181,   432,  1389,  2217,
    2172,  1835,  -718,  -718,  -718,  -718,   408,  1109,  1110,  -684,
    2219,  1041,   527,  2320,  1316,   229,  1433,   445,     3,   229,
    1904,     4,  2251,     5,  2288,   218,  2218,  1654,  1397,   218,
     818,   819,   820,   218,   346,  1967,   866,  1902,  1899,   218,
     707,  -718,   226,     6,     7,     8,     9,  2185,   218,  1604,
    2201,   958,  1578,  1579,     4,   218,     5,   226,  1756,  1455,
     227,  1757,  1682,  1169,  1132,   829,   309,   310,  2240,  1370,
    2236,  1539,  1651,  -989,  1793,   227,  1466,   218,  1684,   450,
     423,  2149,   850,   547,  1683,  2030,  2269,  1367,  1116,  1694,
    2267,  2116,  1137,  2268,   803,   709,   298,  2066,   299,  2055,
     851,  -723,   269,   270,   271,  1258,   695,   410,  1680,  1681,
       4,   306,     5,    57,  2090,   307,   462,  2141,  1170,    57,
     415,  2050,   657,   658,  1439,   421,  2142,   659,  1785,   230,
     698,  1371,   660,   230,   660,  -989,   661,   662,   661,   662,
    1269,  1920,  1352,  1353,  1126,  2135,     4,   663,     5,   663,
    1543,   229,   974,   866,   790,  1415,  2071,  2143,  1547,   664,
     838,   664,   853,   854,  1298,  1057,  1058,  1059,   859,  1475,
    1427,  1477,  2047,  2048,  1429,   775,  1193,  1084,  1470,   826,
    1758,   951,   952,   953,  1194,   665,  1400,   665,   346,   666,
     433,   666,   434,   218,   667,  1104,   667,   839,  1074,   668,
    1027,   668,   827,   669,  2067,   669,  1637,  2114,  1416,   695,
    2056,  1535,  1536,  1255,  2118,   670,   828,   670,  1103,  2119,
     675,  1417,   675,   269,   270,   271,   229,  1086,   831,  2123,
     676,  1428,   676,   698,  1863,  1445,   695,     4,   677,     5,
     677,   229,   418,   833,  1528,  1414,   232,     3,  1887,   697,
       4,  1888,     5,  -990,  1890,  -990,   697,   419,     3,   849,
     698,     4,  2107,     5,   983,   230,  2148,   218,  1587,   232,
     782,   783,     6,     7,     8,     9,  1561,  2224,  1869,  2225,
     984,   232,   848,     6,     7,     8,     9,  2227,  2100,  2226,
    1556,  2090,  1314,  -725,   858,  1559,   951,   952,   953,  1296,
    -725,  -725,  -725,  -725,   542,   543,   544,  -685,  1759,   463,
     985,   464,  1362,  1098,  1363,  1027,  1027,  1027,  1027,  1027,
    1322,  1308,  1027,  1592,   133,   134,   726,   233,   861,  1597,
    1299,  1396,   862,   222,  1921,   592,  1922,  -733,  1755,  -725,
     230,  1259,  1753,  1314,  -733,  -733,  -733,  -733,  1027,  -538,
     233,   727,  1245,  1323,  -718,   230,   593,   222,   866,   431,
    1744,  1744,   233,   770,  1012,   678,   887,  1027,  1324,   594,
    1625,     3,   679,   771,     4,   460,     5,   701,   702,  1348,
    1423,  1760,   711,  -733,   701,   702,  1349,  1797,  1435,  1412,
    1425,  1842,  1843,  1424,   484,  1425,     6,     7,     8,     9,
    1523,   680,  2221,   476,   975,   478,   480,  1382,  1553,   483,
    -990,   485,  1355,  1325,   489,   490,   980,  1524,   498,   500,
     502,   504,  1949,  2103,  1335,   509,  2096,   972,   514,   232,
     517,   519,  -734,   232,   982,   974,  1031,  1336,   526,  -734,
    -734,  -734,  -734,  1018,   981,   616,  1836,  1950,  1951,  1525,
     226,   943,   944,  1337,  1777,   535,   536,  1778,  1416,   703,
    2004,   617,   712,   713,   714,  1545,   703,  2005,   227,  1032,
     618,  1691,  -990,  1775,   226,  1737,   619,   620,  -734,  1012,
    1012,  1012,  1012,  1012,   222,   629,  1012,  1043,  1018,   630,
     331,  1773,   227,   234,  1774,   332,   317,   318,  1886,   852,
     235,   319,  1326,  2284,  2006,   549,   550,   688,   334,  1737,
     233,  1044,  1012,   335,   233,  1045,   234,  1423,   878,   853,
     854,   631,   632,   404,   331,   545,   595,  1763,   234,   332,
    1435,  1012,  1425,   974,  1046,   404,  1239,  1802,  2007,   689,
     690,  1047,   334,  1668,  1434,   308,  2062,   335,  1436,  1781,
    1249,   634,  1923,  1924,  1925,  1926,  -819,  1678,   853,   854,
    1677,  1679,   801,  2068,  1687,   232,   135,  1685,  1679,  1688,
    1690,  1952,  1081,   136,   137,   691,  1844,  2248,  1845,  1846,
    2249,  1848,  1581,   635,   636,  -326,   637,   719,  -828,   138,
    -829,  1953,  1954,  1784,   866,  1087,   537,   538,  1610,   945,
     539,   226,   946,   720,  1476,   866,  1478,  1338,   692,   223,
    1819,  1772,  1484,  1611,   154,  1631,  1479,  1106,  1612,   227,
       4,  1807,     5,  2098,   721,  1632,   466,   467,   468,   469,
     722,  1613,   223,  1480,   229,  1107,  1614,  1386,  1481,  1482,
     232,  1388,  1112,  1994,   223,     3,   233,  2008,     4,     4,
       5,     5,  -725,  2096,   625,   232,  1114,  2203,   229,   879,
     880,   881,   882,   883,   626,   627,  2084,  2085,  2086,  2087,
       6,     7,     8,     9,  1645,  1646,   234,    18,    19,     3,
     234,  1652,     4,   235,     5,  1756,  1423,   235,  1757,   154,
    1631,  2139,  2140,   872,   873,  1269,  -733,  1581,  1225,  1692,
    1635,  1425,  1199,   776,     6,     7,     8,     9,   978,   979,
     972,  1202,   777,   778,  1227,   867,   779,   780,   866,   723,
     724,   233,  1226,    90,  1500,   965,   966,    35,  1501,  1502,
    1503,    91,  1233,    92,  2009,    93,   233,    36,    94,    95,
      96,  1314,    97,    37,  1483,  1235,   304,  1265,   230,  1840,
       4,  1270,     5,  1027,  1027,  1027,  1027,  1027,  1027,  1027,
    1027,  1027,  1027,  1027,  2081,  2082,  2083,    38,  1873,   154,
    1631,  1271,  1300,  1275,     3,   222,  1272,     4,  1909,     5,
    1638,  1085,   155,   156,   157,   229,  1288,  1289,  1933,  1357,
    1358,  -734,   223,  1958,  1959,  1960,   223,  1961,  1292,     6,
       7,     8,     9,  1276,   794,  1305,  1876,  1758,   972,   552,
     553,   554,   234,   804,   805,   806,   807,     3,  1277,   404,
       4,  1280,     5,  1655,  2158,  2159,  2160,  1282,  1896,  1319,
    1897,  1905,  1906,   479,  1320,  1679,  1679,  2032,  1318,  1901,
    1329,  2028,     6,     7,     8,     9,  1418,  1419,    18,    19,
    2025,   321,   322,   323,  1866,  1867,   326,  2026,  1355,  1355,
    1355,  1355,  1355,  2004,  1355,  1355,  1127,  1128,  1129,  1130,
    2005,  1344,   530,  1661,  1661,   531,   532,   533,     3,   853,
     854,     4,  1330,     5,   269,   270,   271,   234,   222,  2040,
     222,  2043,   226,  1331,   404,  1351,  2046,  1359,    35,   230,
    1496,  1497,   234,     6,     7,     8,     9,  2006,    36,   404,
     227,  1298,  1366,   400,    37,  1360,  1979,  1012,  1012,  1012,
    1012,  1012,  1012,  1012,  1012,  1012,  1012,  1012,   223,  1361,
    2014,   964,   965,   966,   729,  1759,  1531,  1532,    38,  1533,
    1534,  2007,   222,  1493,  1494,  1027,  1695,  1697,   730,  1713,
    1721,  1739,  1751,   862,  1608,   731,  1374,  2060,  2061,  1027,
    2063, -1034,    98, -1035,  2022,  1698,  1782,  1714,  1722,  1740,
    1752,  1996,  1372,   732,  1373,  1014,  1375,    99,  1377,   733,
    2144,  2145,  1378,   140,  1385,   141,  1014,  1014,  2204,  2122,
     142,  1387,   143,  1798,  1799,   100,   144,   154,  1631,  2128,
     101,  1420,   102,   223,  2078,   226,  2131,   226,  1984,  1421,
    1027,  1997,  1788,  1789,  1422,  1259,  2079,  1426,   223,  1790,
    1791,  2080,  1432,   227,  1416,   227,   866,  1437,  1027,  1027,
    1505,  1506,  1507,  1508,  2094,  1040,   145,  1446,   146,  1945,
    1946,  2136,  1825,  1447,  1860,  1448,  1296,  1382,   232,  1249,
    2008,   155,   156,   157,   400,  2302,   837,  2274,  2275,   226,
    2102,  1808,  1449,  1450,  1815,  1252,  1820,  1458,  1463,  1826,
     497,  1459,  1301,   951,   952,   953,   229,   227,  1465,  1809,
    1308,  1460,  1816,   222,  1821,    18,    19,  1827,  1461,  2077,
    1462,  1883,  1468,  2015,  1663,  1664,   400,   512,  1472,   513,
    1487,  2197,  2198,  2199,   222,  1489,  1491,  1884,  1517,  1012,
    1499,  1521,    18,    19,     3,  1518,  1519,     4,  1520,     5,
    1522,   866,  1529,  1012,  1530,   222,  1537,  2215,  1546,   233,
    1538,  1539,  1541,  1882,  1548,    35,  1551,  2112,  1558,     6,
       7,     8,     9,  1549,   400,    36,  1550,  1581,  1563,   983,
    1580,    37,  1588,   233,  1998,  1590,  1593,  1601,     3,  1605,
    1932,     4,    35,     5,   866,  1626,  1641,  2168,  1644,  1650,
    1658,  1659,    36,   222,  1012,    38,  1660,  -684,    37,  1676,
    2016,  -685,  1693,     6,     7,     8,     9,  1779,  1769,   229,
     230,   229,  1012,  1012,  1806,  2244,  1770,  2132,  1756,   232,
     226,  1757,    38,  2004,  1771,  1786,  1269,  1787,  1795,  1832,
    2005,  1941,  1284,  2242,  1839,  1852,  2243,  1854,   227,  1865,
    1856,   226,  1871,  1857,  1927,   866,  1872,  1874,  1941,   222,
    1875,  1885,  1935,  1936,  1937,  1938,  1939,   400,  1889,   227,
    1892,  1999,   226,   229,  1423,  1894,   222,  2006,  1907,  1908,
    1964,  1965,  1966,  2258,  2259,  1919,  2239,  2260,  1944,  1934,
     227,  1948,  1973,  1974,  1975,   810,   222,   811,   844,   812,
     813,  1970,  1977,  1713,  1721,  1739,  1751,   814,   815,  1976,
     233,  2007,  1978,  1990,  1989,  2312,  2313,  2314,  1992,  2021,
     226,  1714,  1722,  1740,  1752,   234,     3,  -556,  2031,     4,
    2039,     5,   235,   230,  2041,   230,  2045,  2069,   227,   835,
     835,   816,  2000,  2010,  2017,  2280,  2281,  2318,  2053,   234,
    1758,     6,     7,     8,     9,  2057,   235,  2065,   499,  2070,
    2001,  2011,  2018,  2241,  2075,  2316,  1756,  2089,  2317,  1757,
     222,  2073,  2105,    18,    19,  2117,   226,  2115,  2124,  2306,
    2126,     3,  2133,  2129,     4,  2137,     5,   230,  2138,  2310,
    2147,  2153,  2154,   226,   227,   584,  2165,   585,  1912,  1914,
    1914,  1917,  2311,  2257,  2150,  1269,     6,     7,     8,     9,
    2200,   227,  2214,   226,   229,  2155,   586,   418,  2212,  2156,
    2008,  2157,  2058,    35,   587,   588,   589,   590,  2220,   222,
    2161,   227,   419,    36,  2162,   229,  2163,  2164,  1027,    37,
    2216,   223,  2235,   418,   556,   277,   557,   558,   559,   560,
    2109,  2202,  2247,   278,  2228,   279,   229,   280,   419,  2238,
     281,   282,   283,    38,   284,  1297,  1510,  1511,  1512,  1513,
    1514,  -278,  1014,  2252,  1996,  2229,   234,  2230,  1759,  2091,
    2253,  2092,  2093,   235,  2282,  2315,  2283,   226,  1758,  2286,
    2304,   866,  2121,  -279,  2307,  2097,  2033,  2034,  2035,  2036,
    2037,  2099,  2127,  1405,   229,   227,  1407,  2296,  2101,  2130,
       3,  2104,  1341,     4,  1997,     5,  1411,  2110,   501,  1231,
     232,  1406,  1230,  1229,  2000,  2010,  2017,  1121,   230,  1232,
    1780,  1474,   400,    18,    19,     6,     7,     8,     9,  1117,
    1409,    72,  2001,  2011,  2018,   796,   226,   795,  1051,  1300,
    1756,  1988,   798,  1757,  1764,  1972,   562,   563,  2169,  2319,
     229,   222,   834,   834,   227,   564,   565,   566,   567,   568,
     230,  2285,  2167,  1383,  2231,  2233,  2232,   229,  2189,     3,
    2195,  2234,     4,    35,     5,  2223,  2305,  1014,  1014,  1014,
    1014,  1014,   223,    36,  1014,  1916,   802,   229,   222,    37,
    1048,   233,  1012,  2166,     6,     7,     8,     9,  2072,  2059,
    1321,  2042,  1334,  2173,  2152,  1376,  1759,  2044,   230,  1050,
    1014,   222,  2261,    38,  2222,     3,  1647,  1649,     4,  1648,
       5,   222,  1384,   232,  1666,   232,  1859,  1862,  1669,  1014,
     832,  1302,  1390,  1469,  1689,  2190,   774,  2196,  1623,  1841,
       6,     7,     8,     9,  1877,  1039,  1880,  1998,  1061,  2205,
    2206,  1063,  2207,  2208,  2209,  2210,  2211,  2308,   842,  2213,
    1064,   229,  1758,  1062,   230,  1196,   846,     3,   226,  1163,
       4,   847,     5,  1941,   285,  1516,     0,   232,     0,  1995,
       0,   230,  2014,  1168,     0,     0,   227,     0,     0,   286,
       0,   222,     6,     7,     8,     9,     0,     0,  1619,     0,
    2237,   230,     0,     0,   233,   226,   233,   287,     0,  2245,
    2246,     0,   288,  2195,   289,  1028,   400,  -538,   866,     0,
     229,     0,     0,   227,     0,     0,  1028,  1028,   226,     0,
       0,     0,     0,     0,  2111,     0,     0,  2303,   226,     0,
       0,  2278,     0,     0,     0,   222,   227,     0,     0,     0,
       0,     0,  1697,  1721,  1739,  1751,   227,   234,   233,   222,
    1808,  1815,  1820,  1826,   235,  2277,     0,  2109,     0,  2279,
    1698,  1722,  1740,  1752,     0,   230,     0,     0,  1809,  1816,
    1821,  1827,     0,     0,     0,  2289,     0,     0,     0,     0,
    1759,  2290,  2291,  2292,  2293,  2294,  2000,  2010,  2017,  2298,
    2299,  2300,  2301,     0,     0,     0,     0,     0,   226,     0,
       0,     0,     0,     0,  2001,  2011,  2018,  2309,   232,   694,
     503,     0,     0,     0,     0,  1699,   227,  1716,  1726,  1742,
    1754,   695,     0,   696,   230,    18,    19,     0,     0,  1301,
       0,  2321,  2322,  2323,     0,  2015,     0,     0,     0,     0,
       0,   697,   229,     0,     0,   698,     0,     0,   699,     0,
     232,     0,   226,  2266,     0,     0,     0,     0,     0,     0,
     234,     0,   234,   223,     0,     0,   226,   235,     3,   235,
     227,     4,     0,     5,     0,    35,     0,     0,     0,   229,
       0,     0,     0,     0,   227,    36,     0,     0,     0,   233,
       0,    37,     0,     6,     7,     8,     9,     0,   232,     0,
       0,     0,   229,     0,     0,  1040,   866,     0,     0,     0,
     233,     0,   229,     0,   234,    38,   853,   854,     0,     0,
       0,   404,  2113,     0,  1634,  1634,     0,  1634,     0,  1810,
       0,   233,  1817,     0,  1822,     0,   700,  1828,     0,     3,
       0,     0,     4,     0,     5,     0,     0,     0,     0,  1249,
       0,     0,   866,     0,   232,     0,   230,     0,     0,     0,
       0,     0,     0,     0,     6,     7,     8,     9,  2272,   701,
     702,   232,     0,     0,     0,  1701,   223,     0,   223,   233,
       0,     0,   229,     0,     0,  1702,     0,     0,     0,     0,
    1703,   232,  1704,   230,  1705,     0,     0,  1619,     0,     0,
       0,     0,     0,     0,   866,  1014,  1014,  1014,  1014,  1014,
    1014,  1014,  1014,  1014,  1014,  1014,   230,     0,     3,     0,
    2270,     4,     0,     5,     0,     0,   230,     0,     0,     0,
     223,     0,     0,   508,     0,   233,   229,     0,  1264,     0,
    1266,     0,     0,     6,     7,     8,     9,     0,    18,    19,
     229,   703,   233,     3,     0,   234,     4,  1283,     5,  1287,
       0,  1291,   404,     0,     0,   232,     3,  1303,  1304,     4,
       0,     5,   233,     0,     0,     0,   234,     0,     6,     7,
       8,     9,     0,   235,     3,     0,     0,     4,     0,     5,
       0,     6,     7,     8,     9,     0,   230,   234,    35,  1339,
       0,  1706,  1343,     0,   404,     0,     0,     0,    36,     6,
       7,     8,     9,     0,    37,     0,     0,     0,     0,     0,
       0,   155,   156,   157,   232,     0,     0,     0,     0,     3,
       0,     0,     4,     0,     5,     0,     0,     0,    38,     0,
       0,  1716,  1726,  1742,  1754,   234,   233,     0,     3,     0,
     230,     4,   404,     5,     6,     7,     8,     9,     0,  1996,
       0,     0,     0,     0,   230,     0,  2014,  1380,     0,     0,
       0,   223,  1028,     6,     7,     8,     9,     0,     0,     0,
    2002,  2012,  2019,     0,     0,  1040,     0,     0,     0,     0,
    1861,     0,  1297,  1383,     0,     0,     0,  1014,     0,  1997,
       0,   234,     0,  2174,     0,   233,     0,     0,   235,     0,
       0,  1014,     0,   223,  1707,   866,     0,     0,   234,     0,
    1356,  1634,  1213,  1214,  1634,   235,     0,  1634,     0,  1708,
       0,  1696,     0,   516,     0,     0,  1215,     0,   234,     0,
    1430,  1431,     0,     0,  1216,   404,     0,  1709,    18,    19,
       0,     0,  1710,  2175,  1711,     0,   232,     0,    75,     0,
    1217,   223,  1014,     0,     0,     0,    76,     0,    77,     0,
    1949,     0,     0,    78,    79,    80,     0,    81,     0,     3,
    1014,  1014,     4,     0,     5,     0,   866,  1028,  1028,  1028,
    1028,  1028,     0,   232,  1028,  1950,  1951,     0,    35,     0,
       0,     0,  1712,     0,     6,     7,     8,     9,    36,     0,
       0,     0,   234,     0,    37,     0,   232,   223,  1728,   235,
    1028,     0,     0,     0,     0,     0,   232,     0,     0,  2015,
       0,     0,     0,     0,   223,     0,     0,   233,    38,  1028,
       0,     0,  1998,   518,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   223,     0,     0,     0,    18,    19,
       0,     0,  2002,  2012,  2019,   866,     0,  1729,  1730,  1731,
    1732,   234,  1733,     0,   233,  1734,     0,  1572,   235,     0,
     607,  2273,   608,     0,     0,     0,     0,  1218,  1219,  1220,
     753,     0,  1735,  1252,     0,     0,   232,   233,     0,     0,
     866,   609,     0,   763,   764,   765,     0,   233,    35,   610,
     611,     0,   612,   866,     0,     0,  2297,     0,    36,  1952,
       0,     0,   613,   614,    37,     0,     0,     0,   223,  2295,
       0,   866,     0,     0,     0,     0,     0,     0,  1252,  1953,
    1954,  1736,  1147,     0,   106,     0,     0,  1814,    38,   107,
     232,     0,   108,   109,   110,   111,     0,  2176,   112,   113,
       0,   114,   115,   116,   232,   117,     0,     0,     0,     0,
    1562,     0,     0,     0,  1565,  2177,   866,   233,     0,     0,
    2178,     0,  2179,     0,  1584,  1585,  1586,   223,     0,  1589,
       0,  1591,  2271,     0,     0,   866,     0,    82,     0,     0,
       0,     0,     0,   234,     0,   118,     0,   119,   120,   121,
     404,  2262,    83,  1573,  1606,     0,  1149,  1150,  1574,  1152,
    1153,  1154,  1155,  1156,  1157,  1158,  1159,  1160,  1575,     0,
      84,   233,     0,     0,     0,    85,     0,    86,     0,     0,
     234,     0,     0,     0,     0,   233,     0,   235,     0,   597,
     598,  1640,     0,  1642,  1737,     0,     0,     0,     0,     0,
    1643,     0,     0,   234,   599,     0,   600,   601,   602,   331,
     235,     0,     0,   234,   332,  1656,     0,  1657,     0,     0,
     235,     0,     0,     0,     0,     0,  1665,   334,  1667,   603,
     604,   605,   335,     0,     0,     0,     0,     0,     0,     0,
    1699,  1726,  1742,  1754,     0,     0,     0,     0,  1810,  1817,
    1822,  1828,     0,     0,   570,   571,     0,     0,   572,   223,
       0,     0,     0,     0,     0,     0,   866,     0,     0,   573,
     574,   575,   576,   577,   578,   579,   580,   581,     0,     0,
       0,     0,  1738,   234,  2002,  2012,  2019,     0,     0,     3,
     235,     0,     4,     0,     5,     0,   223,     0,     0,     0,
    1014,     0,   639,     0,     0,     0,  1356,  1356,  1356,  1356,
    1356,   640,  1356,  1356,     6,     7,     8,     9,   582,   223,
       0,  1662,  1662,   122,     0,     0,   641,     0,  1728,   223,
     642,     0,     0,     0,   643,   644,     0,   234,   123,   645,
     646,   647,   648,   649,   404,   124,   125,   126,   127,     0,
       0,   234,     0,     0,     0,     0,   128,     0,   235,     0,
       0,   129,     0,   130,   131,  1028,  1028,  1028,  1028,  1028,
    1028,  1028,  1028,  1028,  1028,  1028,     0,  1729,  1730,  1731,
    1732,     3,  1733,     0,     4,  1734,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   223,
       0,     0,  1735,     0,     0,     0,     6,     7,     8,     9,
       0,     0,  1830,  1831,     0,     0,     0,     0,     0,     0,
    1728,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    63,    51,    51,    66,    66,    66,    70,     0,  1847,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1736,     0,   223,  1864,     0,     3,     0,     0,     4,
       0,     5,     0,     0,     0,     0,     0,   223,     0,  1729,
    1730,  1731,  1732,     0,  1733,     0,     0,  1734,     0,     0,
       0,     6,     7,     8,     9,     0,     0,     0,     0,     0,
    1891,     0,     0,    51,  1735,  1745,   426,    51,    66,    66,
      66,    70,     0,  1145,     0,     0,     0,  1893,    51,  1895,
     441,   446,   449,    51,   454,    66,    66,   459,  1146,   441,
     441,   441,   441,     0,    66,     0,     0,     0,   475,     0,
      51,     0,     0,    66,    66,     0,    70,     0,     0,    66,
     891,     0,     0,  1736,     0,  1746,   892,  1747,     0,  1733,
       0,     0,  1734,    51,     0,     0,     0,  1028,     0,     0,
     522,    51,    66,    66,  1737,     0,    66,     0,    51,  1748,
       0,  1028,     0,     0,   155,   156,   157,     0,     0,   331,
       0,   993,     0,  1147,   332,   994,     0,     0,     0,     0,
     995,     0,     0,   158,     0,   159,   996,   334,     0,   160,
     899,     0,   335,     0,   161,     0,     0,     0,     0,     0,
     162,     0,     0,     0,     0,     0,     0,     0,  1749,     0,
     999,     0,  1028,     0,     0,     0,   163,     0,     0,     0,
       0,   164,     0,     0,   165,     0,   866,     0,     0,   166,
    1028,  1028,   167,     0,     0,   168,   169,   655,     0,     0,
     170,     0,  1982,   171,  1148,   172,  1737,  1149,  1150,  1151,
    1152,  1153,  1154,  1155,  1156,  1157,  1158,  1159,  1160,  1161,
       0,   331,     0,     0,     0,     0,   332,     0,     0,     0,
     173,  2029,   656,     0,     0,     0,   178,     0,     0,   334,
       0,     0,     0,     0,   335,     0,     0,   441,   446,   449,
      51,   454,    66,    66,   459,     0,   441,   441,   441,   441,
       0,     0,     0,     0,  2049,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   866,     0,
       0,  1737,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2064,     0,     0,  2264,     0,   331,  1171,     0,     0,
       0,   332,     0,     0,     0,     0,   902,     0,     0,   903,
     904,     0,     0,     0,   334,     0,   905,     0,     0,   335,
    1172,  1173,  1174,  1175,  1176,  1177,  1178,  1179,  1180,  1181,
    1182,  1183,  1184,  1185,  1186,  1187,  1188,     0,     3,     0,
       0,     4,     0,     5,     0,     0,   907,   908,     0,     0,
       0,     0,     0,   866,     0,     0,     0,     0,     0,     0,
     150,     0,     0,     6,     7,     8,     9,   151,   152,  1750,
       0,     0,   314,   153,   315,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   218,   316,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   317,
     318,     0,     0,     0,   319,     0,     0,   320,     0,     0,
       0,     0,     0,     0,     0,     0,   321,   322,   323,   324,
     325,   326,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1717,     0,     0,     0,   327,     0,   328,     0,     0,
     154,   155,   156,   157,     0,     0,   158,     0,   159,  1083,
       0,  1718,   160,     0,     0,     0,    66,   161,     0,     0,
       0,     0,     0,   162,  2146,     0,     0,  1089,     0,  1090,
       0,  1091,     0,  1092,     0,     0,     0,     0,  1096,   163,
       0,     0,  1097,    51,   164,     0,  1100,   165,  1101,     0,
       0,     0,   166,     0,     0,   167,     0,    66,   168,   169,
    1719,     0,     0,   170,     0,     0,   171,     0,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     0,     0,     4,     0,
       5,     0,     0,   173,   174,     0,   175,   176,   177,   178,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     7,     8,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1745,     0,     0,     0,     0,     0,
    1028,     0,     0,     0,   179,   180,   181,   182,     0,     0,
       0,     0,     0,   183,   184,     0,     0,   185,   186,   329,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,     0,     0,   330,  1746,     0,  1747,     0,  1733,     0,
       0,  1734,     0,     0,     0,     0,     0,     0,   331,     0,
       0,     0,     0,   332,     0,     0,     0,     0,  1748,     0,
     333,     0,     0,     0,     0,     0,   334,     0,     0,     0,
       0,   335,     0,     0,     0,     0,     0,   210,   211,     0,
     336,     0,     0,   337,   338,   339,   340,     0,     0,     0,
     341,     0,     0,     0,   342,   343,   212,     0,     0,     0,
     213,   214,     0,     0,     0,   866,     0,  1749,     0,   344,
       0,     3,   215,   216,     4,     0,     5,     0,   345,     0,
     346,  1720,   217,     0,     0,   218,     0,     0,     0,     0,
       0,     0,     0,   150,     0,     0,     6,     7,     8,     9,
     151,   152,     0,     0,     0,   314,   153,   315,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   316,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   317,   318,     0,     0,     0,   319,     0,     0,
     320,     0,     0,     0,     0,     0,     0,     0,     0,   321,
     322,   323,   324,   325,   326,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1717,     0,     0,     0,   327,     0,
     328,     0,     0,   154,   155,   156,   157,     0,     0,   158,
    1737,   159,     0,     0,  1718,   160,     0,     0,     0,     0,
     161,    10,     0,     0,     0,   331,   162,     0,     0,    11,
     332,    12,     0,    13,     0,     0,    14,    15,    16,     0,
      17,     0,   163,   334,    18,    19,     0,   164,   335,     0,
     165,     0,     0,     0,     0,   166,     0,     0,   167,     0,
       0,   168,   169,  1719,     0,     0,   170,     0,     0,   171,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   866,     0,     0,     0,     0,     0,     3,     0,
       0,     4,     0,     5,    35,     0,   173,   174,  1983,   175,
     176,   177,   178,     0,    36,     0,     0,     0,     0,     0,
      37,     0,     0,     6,     7,     8,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1745,     0,     0,
       0,     0,     0,     0,    38,     0,     0,   179,   180,   181,
     182,     0,     0,     0,     0,     0,   183,   184,     0,     0,
     185,   186,   329,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,     0,     0,   330,  1746,     0,  1747,
       0,  1733,     0,     0,  1734,     0,     0,     0,     0,     0,
       0,   331,     0,     0,     0,     0,   332,     0,     0,     0,
       0,  1748,     0,   333,     0,     0,     0,     0,     0,   334,
       0,     0,     0,     0,   335,     0,     0,     0,     0,     0,
     210,   211,     0,   336,     0,     0,   337,   338,   339,   340,
       0,     0,     0,   341,     0,     0,     0,   342,   343,   212,
       0,     0,     0,   213,   214,     0,     0,     0,   866,     0,
    1749,     0,   344,     0,     3,   215,   216,     4,     0,     5,
      39,   345,     0,   346,  1981,   217,     0,  1467,   218,     0,
       0,     0,     0,     0,     0,    40,   150,     0,     0,     6,
       7,     8,     9,   151,   152,     0,     0,     0,   314,   153,
     315,     0,     0,    41,     0,     0,     0,     0,    42,     0,
      43,     0,     0,     0,     0,   316,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   317,   318,     0,     0,   735,
     319,     0,     0,   320,     0,     0,     0,     0,     0,     0,
       0,     0,   321,   322,   323,   324,   325,   326,     0,     0,
       0,     0,     0,     0,     0,     0,   736,  1717,     0,   737,
       0,   327,     0,   328,     0,     0,   154,   155,   156,   157,
       0,     0,   158,  1737,   159,     0,   738,  1718,   160,     0,
       0,     0,     0,   161,     0,     0,     0,     0,   331,   162,
       0,     0,     0,   332,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   163,   334,     0,     0,     0,
     164,   335,     0,   165,     0,     0,     0,     0,   166,     0,
       0,   167,     0,     0,   168,   169,  1719,     0,     0,   170,
       0,     0,   171,     0,   172,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   866,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   173,
     174,  2265,   175,   176,   177,   178,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,     0,
     179,   180,   181,   182,     0,     0,     0,     0,     0,   183,
     184,     0,     0,   185,   186,   329,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,     0,     0,   330,
       0,   739,     0,     0,     0,   210,   211,     0,     0,     0,
       0,     0,     0,     0,   331,   740,     0,     0,     0,   332,
       0,     0,     0,     0,     0,     0,   333,     0,     0,     0,
       0,     0,   334,     0,     0,     0,     0,   335,     0,     0,
       0,   741,     0,   210,   211,     0,   336,     0,     0,   337,
     338,   339,   340,     0,     0,     0,   341,     0,     0,     0,
     342,   343,   212,     4,     0,     5,   213,   214,     0,     0,
       0,   866,     0,     0,     0,   344,     0,     0,   215,   216,
       0,     0,   150,     0,   345,     0,   346,  2263,   217,   151,
     152,   218,     0,     0,   314,   153,   315,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   316,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   317,   318,     0,     0,   841,   319,     0,     0,   320,
       0,     0,     0,     0,     0,     0,     0,     0,   321,   322,
     323,   324,   325,   326,     0,     0,     0,     0,     0,     0,
     158,     0,   736,     0,     0,   737,     0,   327,     0,   328,
       0,     0,   154,   155,   156,   157,     0,   162,   158,     0,
     159,     0,   738,     0,   160,     0,     0,     0,     0,   161,
       0,     0,     0,   163,     0,   162,     0,     0,   164,     0,
       0,   165,     0,     0,     0,     0,   166,     0,     0,   167,
       0,   163,   168,   169,     0,     0,   164,   170,     0,   165,
     171,     0,   172,     0,   166,     0,     0,   167,     0,     0,
     168,   169,     0,     0,     0,   170,     0,     0,   171,     0,
     172,     0,     0,     0,     0,     0,     0,   173,     0,     0,
       0,     0,     0,   178,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   173,   174,     0,   175,   176,
     177,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,     0,   179,   180,   181,   182,
       0,     0,     0,     0,     0,   183,   184,     0,     0,   185,
     186,   329,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,     0,     0,   330,     0,   739,     0,   890,
       0,   210,   211,     0,   745,   746,     0,     0,   747,     0,
     331,   740,     0,     0,     0,   332,     0,   150,     0,     0,
       0,     0,   333,     0,     0,   152,   748,     0,   334,     0,
     153,     0,     0,   335,     0,     0,     0,   741,     0,   210,
     211,     0,   336,     0,     0,   337,   338,   339,   340,     0,
       0,     0,   341,     0,     0,     0,   342,   343,   212,     0,
       0,     0,   213,   214,   891,     0,     0,     0,     0,     0,
     892,   344,     0,     0,   215,   216,     0,     0,     0,   893,
     345,   894,   346,  1881,   217,     0,     0,   218,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   154,   155,   156,
     157,     0,     0,   158,     0,   895,     0,     0,     0,   896,
       0,     0,     0,     0,   897,     0,     0,     0,     0,     0,
     898,     0,     0,     0,   899,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   163,     0,     0,     0,
       0,   164,     0,     0,   900,   749,     0,     0,     0,   166,
       0,     0,   167,     0,     0,   168,   169,     0,     0,     0,
     170,     0,     0,   171,     0,   172,     0,     0,     0,   750,
     751,   752,   753,   754,   755,     0,   756,   757,   758,   759,
     760,   761,   762,     0,     0,   763,   764,   765,   843,     0,
     173,   174,     0,   175,   176,   177,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1261,   766,     0,
     745,   746,     0,     0,   747,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,     0,     0,     0,     0,
       0,   901,   748,   152,     0,     0,     0,     0,   153,     0,
       0,     0,     0,     0,     0,     0,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,     0,     0,
     209,     0,   891,     0,     0,     0,     0,     0,   892,     0,
     902,     0,     0,   903,   904,     0,     0,     0,   844,     0,
     905,     0,     0,     0,     0,     0,     0,     0,   906,     0,
       0,     0,     0,     0,     0,   154,   155,   156,   157,     0,
       0,   158,     0,   895,   210,   211,     0,   896,     0,     0,
     907,   908,   897,     0,     0,     0,     0,     0,  1262,     0,
       0,     0,   899,   212,     0,     0,     0,   213,   214,     0,
       0,     0,     0,     0,   163,     0,     0,   909,   910,   164,
     741,   749,  1263,     0,     0,     0,     0,   166,     0,   911,
     167,     0,   218,   168,   169,     0,     0,     0,   170,     0,
       0,   171,     0,   172,     0,   750,   751,   752,   753,   754,
     755,   845,   756,   757,   758,   759,   760,   761,   762,     0,
       0,   763,   764,   765,     0,     0,     0,     0,   173,   174,
       0,   175,   176,   177,   178,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   766,  1342,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,     0,     0,     0,     0,     0,   901,
       0,   152,     0,     0,     0,     0,   153,     0,     0,     0,
       0,     0,     0,     0,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,     0,     0,   209,     0,
     891,     0,     0,     0,     0,     0,   892,     0,   902,     0,
       0,   903,   904,     0,     0,     0,     0,     0,   905,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   154,   155,   156,   157,     0,     0,   158,
       0,   895,   210,   211,     0,   896,     0,     0,   907,   908,
     897,     0,     0,     0,     0,     0,  1262,     0,     0,     0,
     899,   212,   158,     0,   159,   213,   214,   684,   160,     0,
       0,     0,   163,   161,     0,   909,   910,   164,   741,   162,
    1263,     0,     0,     0,     0,   166,     0,   911,   167,     0,
     218,   168,   169,     0,     0,   163,   170,     0,     0,   171,
     164,   172,     0,   165,     0,     0,     0,     0,   166,     0,
       0,   167,     0,     0,   168,   169,     0,     0,     0,   170,
       0,     0,   171,     0,   172,     0,   173,   174,     0,   175,
     176,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1379,     0,     0,     0,     0,     0,   173,
       0,   685,     0,     0,     0,   178,     0,     0,     0,     0,
       0,   150,     0,     0,     0,     0,     0,   901,     0,   152,
       0,     0,     0,     0,   153,     0,     0,     0,     0,     0,
       0,     0,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,     0,     0,   209,     0,   891,     0,
       0,     0,     0,     0,   892,     0,   902,     0,     0,   903,
     904,     0,     0,     0,     0,     0,   905,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   154,   155,   156,   157,     0,     0,   158,     0,   895,
     210,   211,     0,   896,     0,     0,   907,   908,   897,     0,
       0,     0,     0,     0,  1262,     0,     0,     0,   899,   212,
     158,     0,   159,   213,   214,     0,   160,     0,     0,     0,
     163,   161,     0,   909,   910,   164,   741,   162,  1263,     0,
       0,     0,     0,   166,     0,   911,   167,     0,   218,   168,
     169,     0,     0,   163,   170,     0,     0,   171,   164,   172,
       0,   165,     0,     0,     0,     0,   166,     0,     0,   167,
       0,     0,   168,   169,     0,     0,     0,   170,     0,     0,
     171,     0,   172,     0,   173,   174,     0,   175,   176,   177,
     178,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1564,     0,     0,     0,     0,     0,   173,     0,     0,
       0,     0,     0,   178,     0,     0,     0,     0,     0,   150,
       0,     0,     0,     0,     0,   901,     0,   152,     0,     0,
       0,     0,   153,     0,     0,     0,     0,     0,     0,     0,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,     0,     0,   209,     0,   891,     0,     0,     0,
       0,     0,   892,     0,   902,     0,     0,   903,   904,     0,
       0,     0,     0,     0,   905,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   154,
     155,   156,   157,     0,     0,   158,     0,   895,   210,   211,
       0,   896,     0,     0,   907,   908,   897,     0,     0,     0,
       0,     0,  1262,     0,     0,     0,   899,   212,     0,     0,
       0,   213,   214,     0,     0,     0,     0,     0,   163,     0,
       0,   909,   910,   164,   741,     0,  1263,     0,     0,     0,
       0,   166,     0,   911,   167,     0,   218,   168,   169,     0,
       0,     0,   170,     3,     0,   171,     4,   172,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,     7,
       8,     9,   173,   174,     0,   175,   176,   177,   178,  1701,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1702,
       0,     0,     0,     0,  1703,     0,  1704,     0,  1705,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   901,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
       0,     0,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   902,     0,     0,   903,   904,     0,     0,  1307,
       0,     0,   905,     0,     0,   986,   987,   988,   989,   990,
     991,     0,     0,     0,     0,   992,     0,     0,     0,   971,
       0,     0,     0,     0,     0,     0,   210,   211,     0,     0,
       0,     0,   907,   908,     0,  1706,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   212,     0,     0,   891,   213,
     214,     0,     0,     0,   892,     0,     0,     0,     0,   909,
     910,     0,   741,     0,     0,     0,   891,     0,     0,     0,
       0,   911,   892,     0,   218,     0,     0,     0,     0,     0,
       0,   154,   155,   156,   157,     0,     0,     0,     0,   993,
       0,     0,     0,   994,     0,     0,     0,     0,   995,   154,
     155,   156,   157,     0,   996,     0,     0,   993,   899,     0,
       0,   994,     0,     0,     0,     0,   995,     0,     0,     0,
     997,     0,   996,     0,     0,   998,   899,     0,   999,     0,
       0,     0,     0,  1000,     0,     0,  1001,     0,   997,  1002,
    1003,     0,     0,   998,  1004,     0,   999,  1005,  1707,  1006,
       0,  1000,     0,     0,  1001,     0,     0,  1002,  1003,     0,
       0,     0,  1004,  1708,     0,  1005,     0,  1006,     0,     0,
       0,     0,     0,     0,  1007,     0,     0,  1008,     0,     0,
    1009,  1709,     0,     0,     0,     0,  1710,     0,  1711,     0,
       0,     0,  1007,     0,     0,  1008,     0,     0,  1009,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     866,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1980,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   902,     0,     0,   903,   904,     0,
       0,     0,  1307,     0,   905,     0,     0,     0,     0,     0,
       0,     0,   902,     0,     0,   903,   904,     0,     0,     0,
       0,     0,   905,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   907,   908,     0,  1010,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   891,   907,   908,     0,  1010,     0,   892,     0,     0,
       0,   909,   910,     0,     0,     0,     0,     0,     0,     0,
       0,   346,     0,  1011,     0,     0,   218,     0,     0,   909,
     910,     0,     0,     0,   154,   155,   156,   157,     0,   346,
       0,  1011,   993,     0,   218,     0,   994,     0,     0,     0,
       0,   995,     0,     0,     0,  1033,   971,   996,     0,     0,
       0,   899,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   997,     0,     0,     0,     0,   998,     0,
       0,   999,     0,     0,     0,     0,  1000,     0,     0,  1001,
       0,     0,  1002,  1003,     0,     0,     0,  1004,     0,     0,
    1005,     0,  1006,   891,     0,     0,     0,     0,     0,   892,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1007,     0,     0,
    1008,     0,     0,  1009,     0,     0,   154,   155,   156,   157,
       0,     0,     0,     0,   993,     0,     0,     0,   994,     0,
       0,     0,     0,   995,     0,     0,     0,     0,     0,   996,
       0,     0,     0,   899,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   997,     0,     0,     0,     0,
     998,     0,     0,   999,     0,     0,     0,     0,  1000,     0,
       0,  1001,     0,     0,  1002,  1003,     0,     0,     0,  1004,
       0,     0,  1005,     0,  1006,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   902,     0,     0,
     903,   904,     0,     0,     0,     0,     0,   905,     0,  1007,
       0,     0,  1008,     0,     0,  1009,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   907,   908,     0,
    1010,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   909,   910,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1011,   150,     0,   218,
       0,     0,     0,     0,   151,   152,     0,     0,     0,   314,
     153,   315,     0,     0,     0,     0,     0,     0,     0,   902,
       0,     0,   903,   904,     0,     0,   316,     0,     0,   905,
       0,     0,     0,     0,     0,     0,   317,   318,     0,     0,
       0,   319,     0,     0,   320,     0,     0,     0,     0,     0,
       0,     0,     0,   321,   322,   323,   324,   325,   326,   907,
     908,     0,  1010,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   327,     0,   328,     0,     0,   154,   155,   156,
     157,     0,     0,   158,     0,   159,   909,   910,     0,   160,
       0,     0,     0,     0,   161,     0,  1034,     0,  1011,     0,
     162,   218,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   163,     0,     0,     0,
       0,   164,     0,     0,   165,     0,     0,     0,     0,   166,
       0,     0,   167,     0,     0,   168,   169,     0,     0,     0,
     170,     0,     0,   171,     0,   172,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   174,     0,   175,   176,   177,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,   180,   181,   182,     0,     0,     0,     0,     0,
     183,   184,     0,     0,   185,   186,   329,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,     0,     0,
     330,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,     0,   331,     0,     0,     0,     0,
     332,   152,     0,     0,     0,     0,   153,   333,     0,     0,
       0,     0,     0,   334,     0,     0,     0,     0,   335,     0,
       0,     0,     0,     0,   210,   211,     0,   336,     0,     0,
     337,   338,   339,   340,     0,     0,     0,   341,     0,     0,
     891,   342,   343,   212,     0,     0,   892,   213,   214,     0,
       0,     0,     0,     0,     0,     0,   344,     0,     0,   215,
     216,     0,     0,     0,     0,   345,     0,   346,     0,   217,
       0,     0,   218,   154,   155,   156,   157,     0,     0,   158,
       0,   895,     0,     0,     0,   896,     0,     0,     0,     0,
     897,     0,     0,     0,     0,     0,  1262,     0,     0,     0,
     899,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   163,     0,     0,     0,     0,   164,     0,     0,
    1263,     0,     0,     0,     0,   166,     0,     0,   167,     0,
       0,   168,   169,     0,     0,     0,   170,     0,     0,   171,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,   174,     0,   175,
     176,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   150,     0,     0,     0,     0,     0,   901,   151,   152,
       0,     0,     0,     0,   153,     0,     0,     0,     0,     0,
       0,     0,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,     0,     0,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   902,     0,     0,   903,
     904,     0,     0,     0,     0,     0,   905,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   154,   155,   156,   157,     0,     0,   158,     0,   159,
     210,   211,     0,   160,     0,     0,   907,   908,   161,     0,
       0,     0,     0,     0,   162,     0,     0,     0,     0,   212,
       0,     0,     0,   213,   214,     0,     0,     0,     0,     0,
     163,     0,     0,   909,   910,   164,   741,     0,   165,     0,
       0,     0,     0,   166,     0,   911,   167,     0,   218,   168,
     169,     0,     0,     0,   170,     0,     0,   171,     0,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,     0,   175,   176,   177,
     178,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,     0,     0,     0,     0,     0,     0,   151,
     152,     0,     0,     0,     0,   153,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,   180,   181,   182,     0,
       0,     0,     0,     0,   183,   184,     0,     0,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,     0,     0,   209,     0,  2170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   154,   155,   156,   157,     0,     0,   158,     0,
     159,     0,     0,     0,   160,     0,     0,     0,     0,   161,
       0,     0,     0,     0,     0,   162,     0,     0,   210,   211,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   163,     0,     0,     0,     0,   164,   212,     0,   165,
       0,   213,   214,     0,   166,     0,     0,   167,     0,     0,
     168,   169,     0,   215,   216,   170,     0,     0,   171,     0,
     172,   346,     0,   217,     0,     0,   218,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   173,   174,     0,   175,   176,
     177,   178,   150,     0,     0,     0,     0,     0,     0,   151,
     152,     0,     0,     0,     0,   153,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,   180,   181,   182,
       0,     0,     0,     0,     0,   183,   184,     0,     0,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,     0,     0,   209,     0,     0,     0,     0,
       0,     0,   154,   155,   156,   157,     0,     0,   158,     0,
     159,     0,     0,     0,   160,     0,     0,     0,     0,   161,
       0,     0,     0,     0,     0,   162,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   210,
     211,   163,     0,     0,     0,     0,   164,     0,     0,   165,
       0,     0,     0,     0,   166,     0,     0,   167,   212,     0,
     168,   169,   213,   214,     0,   170,     0,     0,   171,     0,
     172,     0,     0,     0,   215,   216,     0,     0,     0,     0,
       0,     0,     0,     0,   217,     0,     0,   218,     0,     0,
       0,     0,     0,     0,     0,   173,   174,     0,   175,   176,
     177,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   971,     0,     0,   179,   180,   181,   182,
       0,     0,     0,     0,     0,   183,   184,     0,     0,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,     0,     0,   209,     0,     0,     0,     0,
     891,     0,     0,     0,     0,     0,   892,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   154,   155,   156,   157,     0,     0,   210,
     211,   993,     0,     0,     0,   994,     0,     0,     0,     0,
     995,     0,     0,     0,     0,     0,   996,     0,   212,     0,
     899,     0,   213,   214,     0,     0,     0,     0,     0,     0,
       0,     0,   997,     0,   215,   216,     0,   998,     0,     0,
     999,     0,     0,     0,   217,  1000,     0,   218,  1001,     0,
       0,  1002,  1003,     0,     0,     0,  1004,     0,     0,  1005,
       0,  1006,     0,     0,     0,     0,     0,     0,     2,     3,
       0,     0,     4,     0,     5,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1007,     0,     0,  1008,
       0,     0,  1009,     0,     6,     7,     8,     9,     0,     0,
       0,     0,     0,     0,     0,    10,     0,     0,     0,     0,
       0,     0,     0,    11,     0,    12,     0,    13,     0,     0,
      14,    15,    16,     0,    17,     0,     0,     0,    18,    19,
      20,     0,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -419,     0,     0,     0,   902,     0,    35,   903,
     904,     0,     0,     0,     0,     0,   905,     0,    36,   891,
       0,     0,     0,     0,    37,   892,     0,     0,   321,   322,
     323,  1866,  1867,   326,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   907,   908,    38,  1010,
       0,     0,   154,   155,   156,   157,     0,     0,     0,     0,
     993,     0,     0,     0,   994,     0,     0,     0,     0,   995,
       0,     0,     0,   909,   910,   996,     0,     0,     0,   899,
       0,     0,     0,   346,     0,  1011,     0,     0,   218,     0,
       0,   997,     0,     0,     0,     0,   998,     0,     0,   999,
       0,     0,     0,     0,  1000,     0,     0,  1001,     0,     0,
    1002,  1003,     0,     0,     0,  1004,     0,     0,  1005,     0,
    1006,     0,     0,     0,     0,   891,     0,     0,     0,     0,
       0,   892,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1007,     0,     0,  1008,     0,
       0,  1009,     0,     0,     0,     0,     0,     0,   154,   155,
     156,   157,     0,     0,     0,     0,   993,     0,     0,     0,
     994,     0,     0,     0,    39,   995,     0,     0,     0,     0,
       0,   996,     0,     0,     0,   899,     0,     0,     0,    40,
       0,     0,     0,     0,  -419,     0,     0,   997,     0,     0,
       0,     0,   998,     0,     0,   999,     0,    41,     0,     0,
    1000,     0,    42,  1001,    43,     0,  1002,  1003,     0,     0,
       0,  1004,     0,     0,  1005,     0,  1006,   891,     0,     0,
       0,     0,     0,   892,     0,   902,     0,     0,   903,   904,
       0,     0,     0,     0,     0,   905,     0,     0,     0,     0,
       0,  1007,     0,     0,  1008,     0,     0,  1009,     0,     0,
    1686,   155,   156,   157,     0,     0,     0,     0,   993,     0,
       0,     0,   994,     0,     0,   907,   908,   995,  1010,     0,
       0,     0,     0,   996,     0,     0,     0,   899,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   997,
       0,     0,   909,   910,   998,     0,     0,   999,     0,     0,
       0,     0,  1000,     0,  1011,  1001,     0,   218,  1002,  1003,
       0,     0,     0,  1004,     0,     0,  1005,     0,  1006,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   902,     0,     0,   903,   904,     0,     0,     0,     0,
       0,   905,     0,  1007,     0,     0,  1008,     0,     0,  1009,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   907,   908,     0,  1010,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   909,   910,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1011,     0,     0,   218,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   902,     0,     0,   903,   904,     0,     0,
       0,     0,     0,   905,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   907,   908,     0,  1010,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     909,   910,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1011,     0,     0,   218
};

static const yytype_int16 yycheck[] =
{
       1,    68,     3,    30,   325,   358,   349,   428,    37,   429,
      53,   213,   440,   507,    38,    53,    68,   335,     1,   353,
     430,    30,    65,   863,   431,   615,   396,    65,   375,   670,
     396,   505,   905,  1004,   506,   314,   703,   457,   891,   742,
     382,   407,   408,   471,    53,  1443,    47,   176,   520,  1443,
     470,  1308,  1309,   460,    55,   217,    65,    32,  1315,    60,
    1447,   107,  1448,   109,   343,   111,   112,  1442,  1443,   115,
    1450,   117,  1449,   856,   120,   121,  1387,  1252,   124,   125,
     126,   127,   435,  1463,   964,   131,   411,   396,   134,   368,
     136,   137,   555,   427,  1386,  1295,   825,   372,   144,   374,
    1009,    36,   177,   174,   174,  1554,   177,   177,   174,  1608,
     911,   177,   980,   466,  1554,   174,   556,  1771,   177,   174,
     174,  1769,   177,   177,  1770,  1389,  1537,  1538,   982,  1673,
     174,  1748,   861,   177,   981,  1745,   984,   866,    30,   842,
    1397,  1947,   174,   496,   584,   177,     4,     7,  1558,   187,
     879,     4,   592,     7,   883,     7,    30,     7,   978,   979,
    1812,    53,   515,     7,     8,     9,  1546,   607,   174,     5,
      45,   177,   174,    65,    23,   177,    38,   174,    23,    53,
     177,  1824,   174,    97,    23,   177,   174,  1813,   103,   177,
      57,    65,   104,    79,    80,    14,    15,    16,   174,    22,
      20,   177,    90,   174,   213,    49,   177,    51,   217,    57,
    2006,   651,     7,   174,    85,    57,   177,    61,  1794,   822,
    1570,   174,    66,   396,   177,   103,    70,   104,   819,   820,
     824,     7,   104,    10,   407,   408,  1270,   104,   825,    15,
      16,    17,    18,   104,   706,   739,   708,   104,   710,   104,
      49,   104,   105,   715,   694,    13,   104,   324,   325,    78,
      79,    80,   104,    40,    41,    42,    43,    57,    90,   767,
     103,    93,   766,  1671,   104,   105,    95,    96,    93,   293,
     103,   104,  1567,  1568,   104,   104,  1578,  1579,   114,   729,
      85,   329,   163,   268,   113,   114,  1671,   310,    75,   274,
     119,    58,    12,   104,   105,   106,    83,    84,    85,    86,
     823,   349,   144,   807,   776,   382,    45,    46,   133,   293,
      91,   213,    30,   142,   143,   217,     8,   146,   160,   106,
      88,   805,  1617,  1618,   806,  1064,   104,   105,   106,   213,
     349,   167,   168,   217,   396,    53,   123,    49,   846,   363,
     363,   128,   129,   130,   114,   407,   408,    65,   135,   105,
     111,   138,   429,    73,    57,  1006,   794,    77,  1743,  1767,
      57,   144,    54,  1767,   218,   126,   149,   429,     8,   799,
    1755,   424,    92,    93,   296,    90,   424,   396,    93,   363,
     457,  1766,  1767,    90,   801,   283,   439,   285,   407,   408,
     110,   439,    85,   470,    87,   457,    85,   997,    87,   126,
    1000,   104,   111,   127,   302,   424,  2212,   104,   470,  1267,
     297,   122,    58,   133,    54,   297,    85,   126,    53,   296,
     439,   141,    47,   150,   312,   296,    30,   294,   148,   294,
     276,   487,  1336,   160,  1338,  1730,  1731,   128,   296,   363,
     104,   804,  1486,   368,   296,   291,   368,   349,  1061,    53,
     296,  1746,   362,   282,   283,   280,  1057,  1058,  1059,  1063,
     363,    65,   153,   309,   294,   349,   363,  1064,   314,   312,
     324,   325,   368,  1074,   328,     8,  2103,    90,   363,  2141,
    2100,  1841,    15,    16,    17,    18,   362,   257,   258,    22,
    2143,   363,    45,  2309,   364,   213,   364,   278,     1,   217,
     364,     4,   364,     6,   364,   368,  2142,  1365,   363,   368,
     297,   298,   299,   368,   363,  1900,   348,  2071,   364,   368,
     242,    54,   424,    26,    27,    28,    29,   360,   368,   334,
    2116,    85,  1271,  1272,     4,   368,     6,   439,    41,  1062,
     424,    44,  1420,   682,   583,    85,   346,   347,  2175,   242,
    2170,   342,  1363,   242,   345,   439,  1086,   368,  1422,   279,
     280,  2070,   292,   133,  1421,  1839,  2230,   924,   292,    39,
    2228,  1992,   606,  2229,   285,   242,   283,  1898,   285,  1874,
     310,   367,   349,   350,   351,   363,   126,   441,  1418,  1419,
       4,   445,     6,   296,     8,   449,    90,  2056,   683,   296,
     454,  1868,   683,   683,  1042,   459,  2056,   683,  1527,   213,
     150,   304,   681,   217,   683,   304,   681,   681,   683,   683,
     832,    90,   907,   908,   569,  2045,     4,   681,     6,   683,
     357,   349,   984,   348,   350,  1011,  1903,  2057,  1239,   681,
      62,   683,   312,   313,   856,   432,   433,   434,    85,  1122,
    1030,  1124,  1862,  1863,  1030,   341,   695,   486,  1108,   103,
     163,   330,   331,   332,   698,   681,   985,   683,   363,   681,
     283,   683,   285,   368,   681,   529,   683,    99,   465,   681,
     863,   683,   103,   681,     5,   683,  1337,  1989,     7,   126,
    1875,  1221,  1222,   363,   166,   681,   103,   683,   527,   171,
     681,    20,   683,   349,   350,   351,   424,   494,   292,  2004,
     681,  1030,   683,   150,  1604,  1050,   126,     4,   681,     6,
     683,   439,   799,   171,  1196,  1010,    30,     1,  1632,   146,
       4,  1635,     6,    85,  1638,    87,   146,   799,     1,   315,
     150,     4,   363,     6,     8,   349,  2067,   368,  1278,    53,
     359,   360,    26,    27,    28,    29,  1260,  2154,  1608,  2155,
      24,    65,   292,    26,    27,    28,    29,  2157,     5,  2156,
    1254,     8,  1622,     8,    85,  1257,   330,   331,   332,   856,
      15,    16,    17,    18,    32,    33,    34,    22,   291,   283,
      54,   285,    20,   513,    22,   978,   979,   980,   981,   982,
      78,   863,   985,  1287,    49,    50,   128,    30,   104,  1291,
    1603,   983,     4,   832,   283,   114,   285,     8,  2226,    54,
     424,  1560,  2226,  1673,    15,    16,    17,    18,  1011,   103,
      53,   153,   817,   111,   367,   439,   135,   856,   348,    81,
    2225,  2226,    65,   330,   863,   127,   324,  1030,   126,   148,
    1323,     1,   134,   340,     4,    97,     6,   274,   275,   898,
       7,   364,   163,    54,   274,   275,   900,  1544,    20,  1008,
      22,  1584,  1585,    20,   116,    22,    26,    27,    28,    29,
     114,   163,  2149,   109,    45,   111,   112,   964,  1251,   115,
     242,   117,   911,   171,   120,   121,    17,   131,   124,   125,
     126,   127,   104,     5,   142,   131,     8,   984,   134,   213,
     136,   137,     8,   217,   367,  1267,    52,   155,   144,    15,
      16,    17,    18,   985,    18,   128,  1577,   129,   130,   163,
     832,    38,    39,   171,  1464,   112,   113,  1467,     7,   356,
      90,   144,   243,   244,   245,  1234,   356,    97,   832,    52,
     153,    20,   304,  1457,   856,   276,   159,   160,    54,   978,
     979,   980,   981,   982,   983,   131,   985,   363,  1030,   135,
     291,  1455,   856,    30,  1456,   296,    62,    63,  1629,   292,
      30,    67,   260,  2250,   134,   167,   168,   135,   309,   276,
     213,   363,  1011,   314,   217,   363,    53,     7,   163,   312,
     313,   167,   168,    53,   291,   253,   305,  1445,    65,   296,
      20,  1030,    22,  1365,   363,    65,   803,  1547,   168,   167,
     168,   363,   309,  1380,  1035,    57,  1889,   314,  1039,  1479,
     293,   135,  1708,  1709,  1710,  1711,   293,  1417,   312,   313,
    1416,  1417,   284,   364,  1424,   349,   291,  1423,  1424,  1425,
    1426,   253,    43,   298,   299,   203,  1586,    22,  1588,  1589,
      25,  1591,  1274,   167,   168,   363,   170,   116,    45,   314,
      45,   273,   274,  1523,   348,    45,   253,   254,   276,   186,
     257,   983,   189,   132,  1123,   348,  1125,   325,   236,    30,
     364,  1454,  1131,   291,   103,   104,   114,     7,   296,   983,
       4,   364,     6,     7,   153,   114,    99,   100,   101,   102,
     159,   309,    53,   131,   832,     8,   314,   971,   136,   137,
     424,   975,   308,  1800,    65,     1,   349,   277,     4,     4,
       6,     6,   367,     8,   153,   439,   104,  2118,   856,   304,
     305,   306,   307,   308,   163,   164,  1923,  1924,  1925,  1926,
      26,    27,    28,    29,  1357,  1358,   213,    60,    61,     1,
     217,  1364,     4,   213,     6,    41,     7,   217,    44,   103,
     104,  2054,  2055,   293,   294,  1387,   367,  1389,   341,    20,
     114,    22,   369,   237,    26,    27,    28,    29,    15,    16,
    1267,   369,   246,   247,   103,   348,   250,   251,   348,   248,
     249,   424,   341,    37,   226,   335,   336,   110,   230,   231,
     232,    45,   358,    47,   364,    49,   439,   120,    52,    53,
      54,  2071,    56,   126,   242,   366,     0,    85,   832,  1582,
       4,   176,     6,  1416,  1417,  1418,  1419,  1420,  1421,  1422,
    1423,  1424,  1425,  1426,  1920,  1921,  1922,   150,  1611,   103,
     104,    23,   856,    52,     1,  1274,    23,     4,  1696,     6,
     114,   487,   104,   105,   106,   983,   312,   313,  1718,    15,
      16,   367,   213,    86,    87,    88,   217,    90,   103,    26,
      27,    28,    29,    52,   277,    85,  1614,   163,  1365,   112,
     113,   114,   349,   286,   287,   288,   289,     1,    52,   349,
       4,    52,     6,  1365,  2081,  2082,  2083,    52,  1665,   103,
    1667,  1691,  1692,    45,   103,  1691,  1692,  1847,   363,  1672,
     103,  1825,    26,    27,    28,    29,    15,    16,    60,    61,
    1814,    79,    80,    81,    82,    83,    84,  1819,  1357,  1358,
    1359,  1360,  1361,    90,  1363,  1364,   138,   139,   140,   141,
      97,    85,   104,  1372,  1373,   107,   108,   109,     1,   312,
     313,     4,   103,     6,   349,   350,   351,   424,  1387,  1853,
    1389,  1855,  1274,   103,   424,    85,  1858,    17,   110,   983,
     191,   192,   439,    26,    27,    28,    29,   134,   120,   439,
    1274,  1603,     5,  1441,   126,    18,  1759,  1416,  1417,  1418,
    1419,  1420,  1421,  1422,  1423,  1424,  1425,  1426,   349,   367,
     114,   334,   335,   336,   114,   291,   112,   113,   150,   112,
     113,   168,  1441,   193,   194,  1608,  1437,  1438,   128,  1440,
    1441,  1442,  1443,     4,     5,   135,   103,  1887,  1888,  1622,
    1890,     7,   276,     7,  1807,  1438,  1485,  1440,  1441,  1442,
    1443,    94,     7,   153,     7,   396,   103,   291,     5,   159,
    2060,  2061,     7,    45,     7,    47,   407,   408,  2119,  1999,
      52,   363,    54,   112,   113,   309,    58,   103,   104,  2009,
     314,    17,   316,   424,  1915,  1387,  2016,  1389,   364,    18,
    1673,   134,  1531,  1532,   367,  2234,  1916,     8,   439,  1533,
    1534,  1918,   103,  1387,     7,  1389,   348,   103,  1691,  1692,
     221,   222,   223,   224,  1944,    38,    98,   363,   100,    95,
      96,  2051,   364,   363,  1601,   363,  1603,  1604,   832,   293,
     277,   104,   105,   106,  1582,  2274,  1867,    43,    44,  1441,
    1970,  1552,   363,   363,  1555,   310,  1557,   103,   363,  1560,
      45,   103,   856,   330,   331,   332,  1274,  1441,   104,  1552,
    1622,   103,  1555,  1582,  1557,    60,    61,  1560,   103,  1913,
     103,  1624,   103,   277,  1372,  1373,  1624,    45,   103,    47,
      97,  2111,  2112,  2113,  1603,   190,   195,  1626,   230,  1608,
     131,   235,    60,    61,     1,   233,   233,     4,   234,     6,
     234,   348,   103,  1622,   103,  1624,   103,  2137,   363,   832,
     103,   342,   103,  1624,   363,   110,   103,   364,   103,    26,
      27,    28,    29,   363,  1672,   120,   363,  1839,     5,     8,
     103,   126,   103,   856,   277,    52,   103,    22,     1,    43,
    1717,     4,   110,     6,   348,   149,     5,  2097,   366,   103,
      85,     8,   120,  1672,  1673,   150,    85,    22,   126,   366,
     364,    22,   103,    26,    27,    28,    29,     7,   363,  1387,
    1274,  1389,  1691,  1692,   294,  2179,   363,  2030,    41,   983,
    1582,    44,   150,    90,   363,   370,  1898,   370,   103,     5,
      97,  1728,   104,  2177,   363,   311,  2178,   311,  1582,    43,
      20,  1603,   190,   315,  1715,   348,   293,   315,  1745,  1728,
     310,     7,  1723,  1724,  1725,  1726,  1727,  1765,    70,  1603,
       5,   364,  1624,  1441,     7,   165,  1745,   134,   103,    39,
    1741,  1742,  1743,  2217,  2218,   104,  2174,  2219,   362,    99,
    1624,   103,  1753,  1754,  1755,    46,  1765,    48,   190,    50,
      51,   362,   362,  1764,  1765,  1766,  1767,    58,    59,   104,
     983,   168,    99,     7,   103,  2295,  2296,  2297,   103,   103,
    1672,  1764,  1765,  1766,  1767,   832,     1,    20,   364,     4,
     103,     6,   832,  1387,   103,  1389,   103,   364,  1672,  1866,
    1867,    92,  1803,  1804,  1805,  2245,  2246,  2301,   103,   856,
     163,    26,    27,    28,    29,   103,   856,    85,    45,     5,
    1803,  1804,  1805,  2176,   103,  2299,    41,   104,  2300,    44,
    1839,   189,   151,    60,    61,   362,  1728,   103,   103,  2279,
     103,     1,   293,   105,     4,   103,     6,  1441,   294,  2289,
     364,   363,   363,  1745,  1728,   114,    41,   116,  1702,  1703,
    1704,  1705,  2290,  2216,   186,  2067,    26,    27,    28,    29,
       7,  1745,   364,  1765,  1582,   363,   135,  1944,   134,   363,
     277,   363,  1883,   110,   143,   144,   145,   146,   364,  1898,
     363,  1765,  1944,   120,   363,  1603,   363,   363,  2071,   126,
     103,   832,   104,  1970,   114,    37,   116,   117,   118,   119,
    1977,   363,   103,    45,   363,    47,  1624,    49,  1970,     8,
      52,    53,    54,   150,    56,   856,   225,   226,   227,   228,
     229,     8,   863,   103,    94,   363,   983,   363,   291,  1940,
     104,  1942,  1943,   983,   103,  2298,   103,  1839,   163,     5,
     362,   348,  1998,     8,   103,  1956,   318,   319,   320,   321,
     322,  1962,  2008,  1001,  1672,  1839,  1003,   364,  1969,  2015,
       1,  1972,   892,     4,   134,     6,  1007,  1978,    45,   779,
    1274,  1002,   778,   777,  1985,  1986,  1987,   561,  1582,   780,
    1472,  1116,  2030,    60,    61,    26,    27,    28,    29,   551,
    1005,    20,  1985,  1986,  1987,   279,  1898,   278,   426,  1603,
      41,   364,   281,    44,  1446,  1749,   112,   113,  2098,  2304,
    1728,  2030,  1866,  1867,  1898,   121,   122,   123,   124,   125,
    1624,  2250,  2096,   964,  2161,  2163,  2162,  1745,  2105,     1,
    2107,  2164,     4,   110,     6,  2153,  2276,   978,   979,   980,
     981,   982,   983,   120,   985,  1704,   284,  1765,  2067,   126,
     423,  1274,  2071,  2090,    26,    27,    28,    29,  1903,  1885,
     874,  1854,   884,  2100,  2075,   947,   291,  1856,  1672,   425,
    1011,  2090,  2222,   150,  2152,     1,  1359,  1361,     4,  1360,
       6,  2100,   967,  1387,  1378,  1389,  1601,  1603,  1385,  1030,
     316,   857,   976,  1107,  1426,  2106,   213,  2108,  1315,  1583,
      26,    27,    28,    29,  1615,   408,  1620,   277,   435,  2120,
    2121,   437,  2123,  2124,  2125,  2126,  2127,  2287,   329,  2130,
     438,  1839,   163,   436,  1728,   704,   330,     1,  2030,   649,
       4,   330,     6,  2170,   276,  1174,    -1,  1441,    -1,   364,
      -1,  1745,   114,   681,    -1,    -1,  2030,    -1,    -1,   291,
      -1,  2170,    26,    27,    28,    29,    -1,    -1,  1311,    -1,
    2171,  1765,    -1,    -1,  1387,  2067,  1389,   309,    -1,  2180,
    2181,    -1,   314,  2250,   316,   396,  2224,   103,   348,    -1,
    1898,    -1,    -1,  2067,    -1,    -1,   407,   408,  2090,    -1,
      -1,    -1,    -1,    -1,   364,    -1,    -1,  2274,  2100,    -1,
      -1,  2238,    -1,    -1,    -1,  2224,  2090,    -1,    -1,    -1,
      -1,    -1,  2223,  2224,  2225,  2226,  2100,  1274,  1441,  2238,
    2231,  2232,  2233,  2234,  1274,  2236,    -1,  2304,    -1,  2240,
    2223,  2224,  2225,  2226,    -1,  1839,    -1,    -1,  2231,  2232,
    2233,  2234,    -1,    -1,    -1,  2256,    -1,    -1,    -1,    -1,
     291,  2262,  2263,  2264,  2265,  2266,  2267,  2268,  2269,  2270,
    2271,  2272,  2273,    -1,    -1,    -1,    -1,    -1,  2170,    -1,
      -1,    -1,    -1,    -1,  2267,  2268,  2269,  2288,  1582,   114,
      45,    -1,    -1,    -1,    -1,  1438,  2170,  1440,  1441,  1442,
    1443,   126,    -1,   128,  1898,    60,    61,    -1,    -1,  1603,
      -1,  2312,  2313,  2314,    -1,   277,    -1,    -1,    -1,    -1,
      -1,   146,  2030,    -1,    -1,   150,    -1,    -1,   153,    -1,
    1624,    -1,  2224,   364,    -1,    -1,    -1,    -1,    -1,    -1,
    1387,    -1,  1389,  1274,    -1,    -1,  2238,  1387,     1,  1389,
    2224,     4,    -1,     6,    -1,   110,    -1,    -1,    -1,  2067,
      -1,    -1,    -1,    -1,  2238,   120,    -1,    -1,    -1,  1582,
      -1,   126,    -1,    26,    27,    28,    29,    -1,  1672,    -1,
      -1,    -1,  2090,    -1,    -1,    38,   348,    -1,    -1,    -1,
    1603,    -1,  2100,    -1,  1441,   150,   312,   313,    -1,    -1,
      -1,  1441,   364,    -1,  1335,  1336,    -1,  1338,    -1,  1552,
      -1,  1624,  1555,    -1,  1557,    -1,   241,  1560,    -1,     1,
      -1,    -1,     4,    -1,     6,    -1,    -1,    -1,    -1,   293,
      -1,    -1,   348,    -1,  1728,    -1,  2030,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    29,   364,   274,
     275,  1745,    -1,    -1,    -1,    37,  1387,    -1,  1389,  1672,
      -1,    -1,  2170,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      52,  1765,    54,  2067,    56,    -1,    -1,  1620,    -1,    -1,
      -1,    -1,    -1,    -1,   348,  1416,  1417,  1418,  1419,  1420,
    1421,  1422,  1423,  1424,  1425,  1426,  2090,    -1,     1,    -1,
     364,     4,    -1,     6,    -1,    -1,  2100,    -1,    -1,    -1,
    1441,    -1,    -1,    45,    -1,  1728,  2224,    -1,   829,    -1,
     831,    -1,    -1,    26,    27,    28,    29,    -1,    60,    61,
    2238,   356,  1745,     1,    -1,  1582,     4,   848,     6,   850,
      -1,   852,  1582,    -1,    -1,  1839,     1,   858,   859,     4,
      -1,     6,  1765,    -1,    -1,    -1,  1603,    -1,    26,    27,
      28,    29,    -1,  1603,     1,    -1,    -1,     4,    -1,     6,
      -1,    26,    27,    28,    29,    -1,  2170,  1624,   110,   890,
      -1,   163,   893,    -1,  1624,    -1,    -1,    -1,   120,    26,
      27,    28,    29,    -1,   126,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,  1898,    -1,    -1,    -1,    -1,     1,
      -1,    -1,     4,    -1,     6,    -1,    -1,    -1,   150,    -1,
      -1,  1764,  1765,  1766,  1767,  1672,  1839,    -1,     1,    -1,
    2224,     4,  1672,     6,    26,    27,    28,    29,    -1,    94,
      -1,    -1,    -1,    -1,  2238,    -1,   114,   958,    -1,    -1,
      -1,  1582,   863,    26,    27,    28,    29,    -1,    -1,    -1,
    1803,  1804,  1805,    -1,    -1,    38,    -1,    -1,    -1,    -1,
    1601,    -1,  1603,  1604,    -1,    -1,    -1,  1608,    -1,   134,
      -1,  1728,    -1,    37,    -1,  1898,    -1,    -1,  1728,    -1,
      -1,  1622,    -1,  1624,   276,   348,    -1,    -1,  1745,    -1,
     911,  1632,   112,   113,  1635,  1745,    -1,  1638,    -1,   291,
      -1,   364,    -1,    45,    -1,    -1,   126,    -1,  1765,    -1,
    1031,  1032,    -1,    -1,   134,  1765,    -1,   309,    60,    61,
      -1,    -1,   314,    87,   316,    -1,  2030,    -1,    37,    -1,
     150,  1672,  1673,    -1,    -1,    -1,    45,    -1,    47,    -1,
     104,    -1,    -1,    52,    53,    54,    -1,    56,    -1,     1,
    1691,  1692,     4,    -1,     6,    -1,   348,   978,   979,   980,
     981,   982,    -1,  2067,   985,   129,   130,    -1,   110,    -1,
      -1,    -1,   364,    -1,    26,    27,    28,    29,   120,    -1,
      -1,    -1,  1839,    -1,   126,    -1,  2090,  1728,    40,  1839,
    1011,    -1,    -1,    -1,    -1,    -1,  2100,    -1,    -1,   277,
      -1,    -1,    -1,    -1,  1745,    -1,    -1,  2030,   150,  1030,
      -1,    -1,   277,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1765,    -1,    -1,    -1,    60,    61,
      -1,    -1,  1985,  1986,  1987,   348,    -1,    89,    90,    91,
      92,  1898,    94,    -1,  2067,    97,    -1,    38,  1898,    -1,
     114,   364,   116,    -1,    -1,    -1,    -1,   277,   278,   279,
     280,    -1,   114,   310,    -1,    -1,  2170,  2090,    -1,    -1,
     348,   135,    -1,   293,   294,   295,    -1,  2100,   110,   143,
     144,    -1,   146,   348,    -1,    -1,   364,    -1,   120,   253,
      -1,    -1,   156,   157,   126,    -1,    -1,    -1,  1839,   364,
      -1,   348,    -1,    -1,    -1,    -1,    -1,    -1,   310,   273,
     274,   163,   103,    -1,    37,    -1,    -1,   364,   150,    42,
    2224,    -1,    45,    46,    47,    48,    -1,   291,    51,    52,
      -1,    54,    55,    56,  2238,    58,    -1,    -1,    -1,    -1,
    1261,    -1,    -1,    -1,  1265,   309,   348,  2170,    -1,    -1,
     314,    -1,   316,    -1,  1275,  1276,  1277,  1898,    -1,  1280,
      -1,  1282,   364,    -1,    -1,   348,    -1,   276,    -1,    -1,
      -1,    -1,    -1,  2030,    -1,    98,    -1,   100,   101,   102,
    2030,   364,   291,   174,  1305,    -1,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,    -1,
     309,  2224,    -1,    -1,    -1,   314,    -1,   316,    -1,    -1,
    2067,    -1,    -1,    -1,    -1,  2238,    -1,  2067,    -1,   112,
     113,  1342,    -1,  1344,   276,    -1,    -1,    -1,    -1,    -1,
    1351,    -1,    -1,  2090,   127,    -1,   129,   130,   131,   291,
    2090,    -1,    -1,  2100,   296,  1366,    -1,  1368,    -1,    -1,
    2100,    -1,    -1,    -1,    -1,    -1,  1377,   309,  1379,   152,
     153,   154,   314,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2223,  2224,  2225,  2226,    -1,    -1,    -1,    -1,  2231,  2232,
    2233,  2234,    -1,    -1,   112,   113,    -1,    -1,   116,  2030,
      -1,    -1,    -1,    -1,    -1,    -1,   348,    -1,    -1,   127,
     128,   129,   130,   131,   132,   133,   134,   135,    -1,    -1,
      -1,    -1,   364,  2170,  2267,  2268,  2269,    -1,    -1,     1,
    2170,    -1,     4,    -1,     6,    -1,  2067,    -1,    -1,    -1,
    2071,    -1,   135,    -1,    -1,    -1,  1357,  1358,  1359,  1360,
    1361,   144,  1363,  1364,    26,    27,    28,    29,   176,  2090,
      -1,  1372,  1373,   276,    -1,    -1,   159,    -1,    40,  2100,
     163,    -1,    -1,    -1,   167,   168,    -1,  2224,   291,   172,
     173,   174,   175,   176,  2224,   298,   299,   300,   301,    -1,
      -1,  2238,    -1,    -1,    -1,    -1,   309,    -1,  2238,    -1,
      -1,   314,    -1,   316,   317,  1416,  1417,  1418,  1419,  1420,
    1421,  1422,  1423,  1424,  1425,  1426,    -1,    89,    90,    91,
      92,     1,    94,    -1,     4,    97,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2170,
      -1,    -1,   114,    -1,    -1,    -1,    26,    27,    28,    29,
      -1,    -1,  1563,  1564,    -1,    -1,    -1,    -1,    -1,    -1,
      40,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    11,    12,    13,    14,    15,    16,    17,    -1,  1590,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   163,    -1,  2224,  1605,    -1,     1,    -1,    -1,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,  2238,    -1,    89,
      90,    91,    92,    -1,    94,    -1,    -1,    97,    -1,    -1,
      -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
    1641,    -1,    -1,    73,   114,    40,    76,    77,    78,    79,
      80,    81,    -1,    23,    -1,    -1,    -1,  1658,    88,  1660,
      90,    91,    92,    93,    94,    95,    96,    97,    38,    99,
     100,   101,   102,    -1,   104,    -1,    -1,    -1,   108,    -1,
     110,    -1,    -1,   113,   114,    -1,   116,    -1,    -1,   119,
      70,    -1,    -1,   163,    -1,    90,    76,    92,    -1,    94,
      -1,    -1,    97,   133,    -1,    -1,    -1,  1608,    -1,    -1,
     140,   141,   142,   143,   276,    -1,   146,    -1,   148,   114,
      -1,  1622,    -1,    -1,   104,   105,   106,    -1,    -1,   291,
      -1,   111,    -1,   103,   296,   115,    -1,    -1,    -1,    -1,
     120,    -1,    -1,   109,    -1,   111,   126,   309,    -1,   115,
     130,    -1,   314,    -1,   120,    -1,    -1,    -1,    -1,    -1,
     126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   163,    -1,
     150,    -1,  1673,    -1,    -1,    -1,   142,    -1,    -1,    -1,
      -1,   147,    -1,    -1,   150,    -1,   348,    -1,    -1,   155,
    1691,  1692,   158,    -1,    -1,   161,   162,   163,    -1,    -1,
     166,    -1,   364,   169,   174,   171,   276,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
      -1,   291,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,
     196,  1832,   198,    -1,    -1,    -1,   202,    -1,    -1,   309,
      -1,    -1,    -1,    -1,   314,    -1,    -1,   277,   278,   279,
     280,   281,   282,   283,   284,    -1,   286,   287,   288,   289,
      -1,    -1,    -1,    -1,  1865,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   348,    -1,
      -1,   276,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1892,    -1,    -1,   364,    -1,   291,   181,    -1,    -1,
      -1,   296,    -1,    -1,    -1,    -1,   286,    -1,    -1,   289,
     290,    -1,    -1,    -1,   309,    -1,   296,    -1,    -1,   314,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,    -1,     1,    -1,
      -1,     4,    -1,     6,    -1,    -1,   326,   327,    -1,    -1,
      -1,    -1,    -1,   348,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    26,    27,    28,    29,    30,    31,   364,
      -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   368,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    81,    82,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,
     103,   104,   105,   106,    -1,    -1,   109,    -1,   111,   479,
      -1,   114,   115,    -1,    -1,    -1,   486,   120,    -1,    -1,
      -1,    -1,    -1,   126,  2065,    -1,    -1,   497,    -1,   499,
      -1,   501,    -1,   503,    -1,    -1,    -1,    -1,   508,   142,
      -1,    -1,   512,   513,   147,    -1,   516,   150,   518,    -1,
      -1,    -1,   155,    -1,    -1,   158,    -1,   527,   161,   162,
     163,    -1,    -1,   166,    -1,    -1,   169,    -1,   171,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,     4,    -1,
       6,    -1,    -1,   196,   197,    -1,   199,   200,   201,   202,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
    2071,    -1,    -1,    -1,   237,   238,   239,   240,    -1,    -1,
      -1,    -1,    -1,   246,   247,    -1,    -1,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,    -1,    -1,   276,    90,    -1,    92,    -1,    94,    -1,
      -1,    97,    -1,    -1,    -1,    -1,    -1,    -1,   291,    -1,
      -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,   114,    -1,
     303,    -1,    -1,    -1,    -1,    -1,   309,    -1,    -1,    -1,
      -1,   314,    -1,    -1,    -1,    -1,    -1,   320,   321,    -1,
     323,    -1,    -1,   326,   327,   328,   329,    -1,    -1,    -1,
     333,    -1,    -1,    -1,   337,   338,   339,    -1,    -1,    -1,
     343,   344,    -1,    -1,    -1,   348,    -1,   163,    -1,   352,
      -1,     1,   355,   356,     4,    -1,     6,    -1,   361,    -1,
     363,   364,   365,    -1,    -1,   368,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    -1,    -1,    -1,    67,    -1,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      80,    81,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,    98,    -1,
     100,    -1,    -1,   103,   104,   105,   106,    -1,    -1,   109,
     276,   111,    -1,    -1,   114,   115,    -1,    -1,    -1,    -1,
     120,    37,    -1,    -1,    -1,   291,   126,    -1,    -1,    45,
     296,    47,    -1,    49,    -1,    -1,    52,    53,    54,    -1,
      56,    -1,   142,   309,    60,    61,    -1,   147,   314,    -1,
     150,    -1,    -1,    -1,    -1,   155,    -1,    -1,   158,    -1,
      -1,   161,   162,   163,    -1,    -1,   166,    -1,    -1,   169,
      -1,   171,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   348,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,     4,    -1,     6,   110,    -1,   196,   197,   364,   199,
     200,   201,   202,    -1,   120,    -1,    -1,    -1,    -1,    -1,
     126,    -1,    -1,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,   150,    -1,    -1,   237,   238,   239,
     240,    -1,    -1,    -1,    -1,    -1,   246,   247,    -1,    -1,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,    -1,    -1,   276,    90,    -1,    92,
      -1,    94,    -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,
      -1,   291,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,
      -1,   114,    -1,   303,    -1,    -1,    -1,    -1,    -1,   309,
      -1,    -1,    -1,    -1,   314,    -1,    -1,    -1,    -1,    -1,
     320,   321,    -1,   323,    -1,    -1,   326,   327,   328,   329,
      -1,    -1,    -1,   333,    -1,    -1,    -1,   337,   338,   339,
      -1,    -1,    -1,   343,   344,    -1,    -1,    -1,   348,    -1,
     163,    -1,   352,    -1,     1,   355,   356,     4,    -1,     6,
     276,   361,    -1,   363,   364,   365,    -1,  1087,   368,    -1,
      -1,    -1,    -1,    -1,    -1,   291,    23,    -1,    -1,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    35,    36,
      37,    -1,    -1,   309,    -1,    -1,    -1,    -1,   314,    -1,
     316,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    -1,   104,
      67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    81,    82,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   131,    94,    -1,   134,
      -1,    98,    -1,   100,    -1,    -1,   103,   104,   105,   106,
      -1,    -1,   109,   276,   111,    -1,   151,   114,   115,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,   291,   126,
      -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,   309,    -1,    -1,    -1,
     147,   314,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,
      -1,   158,    -1,    -1,   161,   162,   163,    -1,    -1,   166,
      -1,    -1,   169,    -1,   171,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   348,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,
     197,   364,   199,   200,   201,   202,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    -1,
     237,   238,   239,   240,    -1,    -1,    -1,    -1,    -1,   246,
     247,    -1,    -1,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,    -1,    -1,   276,
      -1,   316,    -1,    -1,    -1,   320,   321,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   291,   330,    -1,    -1,    -1,   296,
      -1,    -1,    -1,    -1,    -1,    -1,   303,    -1,    -1,    -1,
      -1,    -1,   309,    -1,    -1,    -1,    -1,   314,    -1,    -1,
      -1,   356,    -1,   320,   321,    -1,   323,    -1,    -1,   326,
     327,   328,   329,    -1,    -1,    -1,   333,    -1,    -1,    -1,
     337,   338,   339,     4,    -1,     6,   343,   344,    -1,    -1,
      -1,   348,    -1,    -1,    -1,   352,    -1,    -1,   355,   356,
      -1,    -1,    23,    -1,   361,    -1,   363,   364,   365,    30,
      31,   368,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    -1,    -1,   104,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,
      81,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,
     109,    -1,   131,    -1,    -1,   134,    -1,    98,    -1,   100,
      -1,    -1,   103,   104,   105,   106,    -1,   126,   109,    -1,
     111,    -1,   151,    -1,   115,    -1,    -1,    -1,    -1,   120,
      -1,    -1,    -1,   142,    -1,   126,    -1,    -1,   147,    -1,
      -1,   150,    -1,    -1,    -1,    -1,   155,    -1,    -1,   158,
      -1,   142,   161,   162,    -1,    -1,   147,   166,    -1,   150,
     169,    -1,   171,    -1,   155,    -1,    -1,   158,    -1,    -1,
     161,   162,    -1,    -1,    -1,   166,    -1,    -1,   169,    -1,
     171,    -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,
      -1,    -1,    -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,   197,    -1,   199,   200,
     201,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,    -1,   237,   238,   239,   240,
      -1,    -1,    -1,    -1,    -1,   246,   247,    -1,    -1,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,    -1,    -1,   276,    -1,   316,    -1,     5,
      -1,   320,   321,    -1,   112,   113,    -1,    -1,   116,    -1,
     291,   330,    -1,    -1,    -1,   296,    -1,    23,    -1,    -1,
      -1,    -1,   303,    -1,    -1,    31,   134,    -1,   309,    -1,
      36,    -1,    -1,   314,    -1,    -1,    -1,   356,    -1,   320,
     321,    -1,   323,    -1,    -1,   326,   327,   328,   329,    -1,
      -1,    -1,   333,    -1,    -1,    -1,   337,   338,   339,    -1,
      -1,    -1,   343,   344,    70,    -1,    -1,    -1,    -1,    -1,
      76,   352,    -1,    -1,   355,   356,    -1,    -1,    -1,    85,
     361,    87,   363,   364,   365,    -1,    -1,   368,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,
     106,    -1,    -1,   109,    -1,   111,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,
     126,    -1,    -1,    -1,   130,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,    -1,
      -1,   147,    -1,    -1,   150,   253,    -1,    -1,    -1,   155,
      -1,    -1,   158,    -1,    -1,   161,   162,    -1,    -1,    -1,
     166,    -1,    -1,   169,    -1,   171,    -1,    -1,    -1,   277,
     278,   279,   280,   281,   282,    -1,   284,   285,   286,   287,
     288,   289,   290,    -1,    -1,   293,   294,   295,    90,    -1,
     196,   197,    -1,   199,   200,   201,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,   316,    -1,
     112,   113,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,   237,   134,    31,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,    -1,    -1,
     276,    -1,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
     286,    -1,    -1,   289,   290,    -1,    -1,    -1,   190,    -1,
     296,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   304,    -1,
      -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,    -1,
      -1,   109,    -1,   111,   320,   321,    -1,   115,    -1,    -1,
     326,   327,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,
      -1,    -1,   130,   339,    -1,    -1,    -1,   343,   344,    -1,
      -1,    -1,    -1,    -1,   142,    -1,    -1,   353,   354,   147,
     356,   253,   150,    -1,    -1,    -1,    -1,   155,    -1,   365,
     158,    -1,   368,   161,   162,    -1,    -1,    -1,   166,    -1,
      -1,   169,    -1,   171,    -1,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,    -1,
      -1,   293,   294,   295,    -1,    -1,    -1,    -1,   196,   197,
      -1,   199,   200,   201,   202,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   316,     5,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,   237,
      -1,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,    -1,    -1,   276,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    76,    -1,   286,    -1,
      -1,   289,   290,    -1,    -1,    -1,    -1,    -1,   296,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,   104,   105,   106,    -1,    -1,   109,
      -1,   111,   320,   321,    -1,   115,    -1,    -1,   326,   327,
     120,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,
     130,   339,   109,    -1,   111,   343,   344,   114,   115,    -1,
      -1,    -1,   142,   120,    -1,   353,   354,   147,   356,   126,
     150,    -1,    -1,    -1,    -1,   155,    -1,   365,   158,    -1,
     368,   161,   162,    -1,    -1,   142,   166,    -1,    -1,   169,
     147,   171,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,
      -1,   158,    -1,    -1,   161,   162,    -1,    -1,    -1,   166,
      -1,    -1,   169,    -1,   171,    -1,   196,   197,    -1,   199,
     200,   201,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,   196,
      -1,   198,    -1,    -1,    -1,   202,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,   237,    -1,    31,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,    -1,    -1,   276,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    76,    -1,   286,    -1,    -1,   289,
     290,    -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,    -1,    -1,   109,    -1,   111,
     320,   321,    -1,   115,    -1,    -1,   326,   327,   120,    -1,
      -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,   130,   339,
     109,    -1,   111,   343,   344,    -1,   115,    -1,    -1,    -1,
     142,   120,    -1,   353,   354,   147,   356,   126,   150,    -1,
      -1,    -1,    -1,   155,    -1,   365,   158,    -1,   368,   161,
     162,    -1,    -1,   142,   166,    -1,    -1,   169,   147,   171,
      -1,   150,    -1,    -1,    -1,    -1,   155,    -1,    -1,   158,
      -1,    -1,   161,   162,    -1,    -1,    -1,   166,    -1,    -1,
     169,    -1,   171,    -1,   196,   197,    -1,   199,   200,   201,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,
      -1,    -1,    -1,   202,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,   237,    -1,    31,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,    -1,    -1,   276,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    76,    -1,   286,    -1,    -1,   289,   290,    -1,
      -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,
     104,   105,   106,    -1,    -1,   109,    -1,   111,   320,   321,
      -1,   115,    -1,    -1,   326,   327,   120,    -1,    -1,    -1,
      -1,    -1,   126,    -1,    -1,    -1,   130,   339,    -1,    -1,
      -1,   343,   344,    -1,    -1,    -1,    -1,    -1,   142,    -1,
      -1,   353,   354,   147,   356,    -1,   150,    -1,    -1,    -1,
      -1,   155,    -1,   365,   158,    -1,   368,   161,   162,    -1,
      -1,    -1,   166,     1,    -1,   169,     4,   171,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,   196,   197,    -1,   199,   200,   201,   202,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    52,    -1,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   237,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
      -1,    -1,   276,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   286,    -1,    -1,   289,   290,    -1,    -1,    21,
      -1,    -1,   296,    -1,    -1,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,   320,   321,    -1,    -1,
      -1,    -1,   326,   327,    -1,   163,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   339,    -1,    -1,    70,   343,
     344,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,   353,
     354,    -1,   356,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      -1,   365,    76,    -1,   368,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,    -1,    -1,    -1,    -1,   111,
      -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,   120,   103,
     104,   105,   106,    -1,   126,    -1,    -1,   111,   130,    -1,
      -1,   115,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,
     142,    -1,   126,    -1,    -1,   147,   130,    -1,   150,    -1,
      -1,    -1,    -1,   155,    -1,    -1,   158,    -1,   142,   161,
     162,    -1,    -1,   147,   166,    -1,   150,   169,   276,   171,
      -1,   155,    -1,    -1,   158,    -1,    -1,   161,   162,    -1,
      -1,    -1,   166,   291,    -1,   169,    -1,   171,    -1,    -1,
      -1,    -1,    -1,    -1,   196,    -1,    -1,   199,    -1,    -1,
     202,   309,    -1,    -1,    -1,    -1,   314,    -1,   316,    -1,
      -1,    -1,   196,    -1,    -1,   199,    -1,    -1,   202,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     348,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   364,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   286,    -1,    -1,   289,   290,    -1,
      -1,    -1,    21,    -1,   296,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   286,    -1,    -1,   289,   290,    -1,    -1,    -1,
      -1,    -1,   296,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   326,   327,    -1,   329,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,   326,   327,    -1,   329,    -1,    76,    -1,    -1,
      -1,   353,   354,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   363,    -1,   365,    -1,    -1,   368,    -1,    -1,   353,
     354,    -1,    -1,    -1,   103,   104,   105,   106,    -1,   363,
      -1,   365,   111,    -1,   368,    -1,   115,    -1,    -1,    -1,
      -1,   120,    -1,    -1,    -1,    22,    23,   126,    -1,    -1,
      -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,   147,    -1,
      -1,   150,    -1,    -1,    -1,    -1,   155,    -1,    -1,   158,
      -1,    -1,   161,   162,    -1,    -1,    -1,   166,    -1,    -1,
     169,    -1,   171,    70,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,
     199,    -1,    -1,   202,    -1,    -1,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,
     147,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,
      -1,   158,    -1,    -1,   161,   162,    -1,    -1,    -1,   166,
      -1,    -1,   169,    -1,   171,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   286,    -1,    -1,
     289,   290,    -1,    -1,    -1,    -1,    -1,   296,    -1,   196,
      -1,    -1,   199,    -1,    -1,   202,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   326,   327,    -1,
     329,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   353,   354,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   365,    23,    -1,   368,
      -1,    -1,    -1,    -1,    30,    31,    -1,    -1,    -1,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   286,
      -1,    -1,   289,   290,    -1,    -1,    52,    -1,    -1,   296,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    80,    81,    82,    83,    84,   326,
     327,    -1,   329,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,   100,    -1,    -1,   103,   104,   105,
     106,    -1,    -1,   109,    -1,   111,   353,   354,    -1,   115,
      -1,    -1,    -1,    -1,   120,    -1,   363,    -1,   365,    -1,
     126,   368,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,    -1,
      -1,   147,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,
      -1,    -1,   158,    -1,    -1,   161,   162,    -1,    -1,    -1,
     166,    -1,    -1,   169,    -1,   171,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     196,   197,    -1,   199,   200,   201,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   237,   238,   239,   240,    -1,    -1,    -1,    -1,    -1,
     246,   247,    -1,    -1,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,    -1,    -1,
     276,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,   291,    -1,    -1,    -1,    -1,
     296,    31,    -1,    -1,    -1,    -1,    36,   303,    -1,    -1,
      -1,    -1,    -1,   309,    -1,    -1,    -1,    -1,   314,    -1,
      -1,    -1,    -1,    -1,   320,   321,    -1,   323,    -1,    -1,
     326,   327,   328,   329,    -1,    -1,    -1,   333,    -1,    -1,
      70,   337,   338,   339,    -1,    -1,    76,   343,   344,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   352,    -1,    -1,   355,
     356,    -1,    -1,    -1,    -1,   361,    -1,   363,    -1,   365,
      -1,    -1,   368,   103,   104,   105,   106,    -1,    -1,   109,
      -1,   111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,
     120,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,
     130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   142,    -1,    -1,    -1,    -1,   147,    -1,    -1,
     150,    -1,    -1,    -1,    -1,   155,    -1,    -1,   158,    -1,
      -1,   161,   162,    -1,    -1,    -1,   166,    -1,    -1,   169,
      -1,   171,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   196,   197,    -1,   199,
     200,   201,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,   237,    30,    31,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,    -1,    -1,   276,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   286,    -1,    -1,   289,
     290,    -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,    -1,    -1,   109,    -1,   111,
     320,   321,    -1,   115,    -1,    -1,   326,   327,   120,    -1,
      -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,   339,
      -1,    -1,    -1,   343,   344,    -1,    -1,    -1,    -1,    -1,
     142,    -1,    -1,   353,   354,   147,   356,    -1,   150,    -1,
      -1,    -1,    -1,   155,    -1,   365,   158,    -1,   368,   161,
     162,    -1,    -1,    -1,   166,    -1,    -1,   169,    -1,   171,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   196,   197,    -1,   199,   200,   201,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   237,   238,   239,   240,    -1,
      -1,    -1,    -1,    -1,   246,   247,    -1,    -1,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,    -1,    -1,   276,    -1,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   104,   105,   106,    -1,    -1,   109,    -1,
     111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,   320,   321,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,    -1,    -1,    -1,    -1,   147,   339,    -1,   150,
      -1,   343,   344,    -1,   155,    -1,    -1,   158,    -1,    -1,
     161,   162,    -1,   355,   356,   166,    -1,    -1,   169,    -1,
     171,   363,    -1,   365,    -1,    -1,   368,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,   197,    -1,   199,   200,
     201,   202,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   237,   238,   239,   240,
      -1,    -1,    -1,    -1,    -1,   246,   247,    -1,    -1,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,    -1,    -1,   276,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   104,   105,   106,    -1,    -1,   109,    -1,
     111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   320,
     321,   142,    -1,    -1,    -1,    -1,   147,    -1,    -1,   150,
      -1,    -1,    -1,    -1,   155,    -1,    -1,   158,   339,    -1,
     161,   162,   343,   344,    -1,   166,    -1,    -1,   169,    -1,
     171,    -1,    -1,    -1,   355,   356,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   365,    -1,    -1,   368,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,   197,    -1,   199,   200,
     201,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,   237,   238,   239,   240,
      -1,    -1,    -1,    -1,    -1,   246,   247,    -1,    -1,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,    -1,    -1,   276,    -1,    -1,    -1,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,   104,   105,   106,    -1,    -1,   320,
     321,   111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,
     120,    -1,    -1,    -1,    -1,    -1,   126,    -1,   339,    -1,
     130,    -1,   343,   344,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   142,    -1,   355,   356,    -1,   147,    -1,    -1,
     150,    -1,    -1,    -1,   365,   155,    -1,   368,   158,    -1,
      -1,   161,   162,    -1,    -1,    -1,   166,    -1,    -1,   169,
      -1,   171,    -1,    -1,    -1,    -1,    -1,    -1,     0,     1,
      -1,    -1,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,   199,
      -1,    -1,   202,    -1,    26,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,
      52,    53,    54,    -1,    56,    -1,    -1,    -1,    60,    61,
      62,    -1,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,    -1,    -1,   286,    -1,   110,   289,
     290,    -1,    -1,    -1,    -1,    -1,   296,    -1,   120,    70,
      -1,    -1,    -1,    -1,   126,    76,    -1,    -1,    79,    80,
      81,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   326,   327,   150,   329,
      -1,    -1,   103,   104,   105,   106,    -1,    -1,    -1,    -1,
     111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,   120,
      -1,    -1,    -1,   353,   354,   126,    -1,    -1,    -1,   130,
      -1,    -1,    -1,   363,    -1,   365,    -1,    -1,   368,    -1,
      -1,   142,    -1,    -1,    -1,    -1,   147,    -1,    -1,   150,
      -1,    -1,    -1,    -1,   155,    -1,    -1,   158,    -1,    -1,
     161,   162,    -1,    -1,    -1,   166,    -1,    -1,   169,    -1,
     171,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,   199,    -1,
      -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,    -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,
     115,    -1,    -1,    -1,   276,   120,    -1,    -1,    -1,    -1,
      -1,   126,    -1,    -1,    -1,   130,    -1,    -1,    -1,   291,
      -1,    -1,    -1,    -1,   296,    -1,    -1,   142,    -1,    -1,
      -1,    -1,   147,    -1,    -1,   150,    -1,   309,    -1,    -1,
     155,    -1,   314,   158,   316,    -1,   161,   162,    -1,    -1,
      -1,   166,    -1,    -1,   169,    -1,   171,    70,    -1,    -1,
      -1,    -1,    -1,    76,    -1,   286,    -1,    -1,   289,   290,
      -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,
      -1,   196,    -1,    -1,   199,    -1,    -1,   202,    -1,    -1,
     103,   104,   105,   106,    -1,    -1,    -1,    -1,   111,    -1,
      -1,    -1,   115,    -1,    -1,   326,   327,   120,   329,    -1,
      -1,    -1,    -1,   126,    -1,    -1,    -1,   130,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,
      -1,    -1,   353,   354,   147,    -1,    -1,   150,    -1,    -1,
      -1,    -1,   155,    -1,   365,   158,    -1,   368,   161,   162,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,   171,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   286,    -1,    -1,   289,   290,    -1,    -1,    -1,    -1,
      -1,   296,    -1,   196,    -1,    -1,   199,    -1,    -1,   202,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   326,   327,    -1,   329,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   353,   354,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     365,    -1,    -1,   368,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   286,    -1,    -1,   289,   290,    -1,    -1,
      -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   326,   327,    -1,   329,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     353,   354,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   365,    -1,    -1,   368
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   372,     0,     1,     4,     6,    26,    27,    28,    29,
      37,    45,    47,    49,    52,    53,    54,    56,    60,    61,
      62,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,   110,   120,   126,   150,   276,
     291,   309,   314,   316,   373,   429,   430,   431,   432,   505,
     506,   507,   509,   524,   373,   105,   104,   296,   502,   502,
     502,   507,   518,   507,   509,   524,   507,   512,   512,   512,
     507,   515,   432,    49,   433,    37,    45,    47,    52,    53,
      54,    56,   276,   291,   309,   314,   316,   434,    49,   435,
      37,    45,    47,    49,    52,    53,    54,    56,   276,   291,
     309,   314,   316,   440,    53,   442,    37,    42,    45,    46,
      47,    48,    51,    52,    54,    55,    56,    58,    98,   100,
     101,   102,   276,   291,   298,   299,   300,   301,   309,   314,
     316,   317,   443,    49,    50,   291,   298,   299,   314,   446,
      45,    47,    52,    54,    58,    98,   100,   447,    47,   448,
      23,    30,    31,    36,   103,   104,   105,   106,   109,   111,
     115,   120,   126,   142,   147,   150,   155,   158,   161,   162,
     166,   169,   171,   196,   197,   199,   200,   201,   202,   237,
     238,   239,   240,   246,   247,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   276,
     320,   321,   339,   343,   344,   355,   356,   365,   368,   456,
     503,   628,   629,   632,   633,   634,   638,   701,   704,   706,
     710,   715,   716,   718,   720,   730,   731,   733,   735,   737,
     739,   743,   745,   747,   749,   751,   753,   755,   757,   759,
     761,   765,   767,   769,   771,   782,   790,   792,   794,   795,
     797,   799,   801,   803,   805,   807,   809,   811,    58,   349,
     350,   351,   449,   455,    58,   450,   455,    37,    45,    47,
      49,    52,    53,    54,    56,   276,   291,   309,   314,   316,
     441,   104,   451,   452,   376,   395,   396,    90,   283,   285,
     518,   518,   518,   518,     0,   373,   502,   502,    57,   346,
     347,   521,   522,   523,    35,    37,    52,    62,    63,    67,
      70,    79,    80,    81,    82,    83,    84,    98,   100,   252,
     276,   291,   296,   303,   309,   314,   323,   326,   327,   328,
     329,   333,   337,   338,   352,   361,   363,   528,   529,   530,
     532,   533,   534,   535,   536,   537,   538,   542,   543,   544,
     547,   548,   549,   556,   560,   568,   569,   572,   573,   574,
     575,   576,   597,   598,   600,   601,   603,   604,   607,   608,
     609,   619,   620,   621,   622,   623,   626,   627,   633,   640,
     641,   642,   643,   644,   645,   649,   650,   651,   685,   699,
     704,   705,   728,   729,   730,   772,   373,   362,   362,   373,
     502,   580,   457,   460,   528,   502,   465,   467,   628,   651,
     470,   502,   475,   509,   525,   518,   507,   509,   512,   512,
     512,   515,    90,   283,   285,   518,   518,   518,   518,   524,
     439,   507,   518,   519,   436,   505,   507,   508,   437,   507,
     509,   510,   525,   438,   507,   512,   513,   512,   512,   507,
     515,   516,    90,   283,   285,   674,   439,   439,   439,   439,
     512,   518,   445,   506,   527,   507,   527,   509,   527,    45,
     527,   512,   512,   527,   515,   527,    45,    46,   512,   527,
     527,    90,   283,   302,   674,   675,   518,    45,   527,    45,
     527,    45,   527,    45,   527,   518,   518,   518,    45,   527,
     402,   525,    45,    47,   527,   518,    45,   527,    45,   527,
     518,   414,   507,   509,   512,   512,   527,    45,   512,   509,
     104,   107,   108,   109,   732,   112,   113,   253,   254,   257,
     636,   637,    32,    33,    34,   253,   707,   133,   639,   167,
     168,   793,   112,   113,   114,   734,   114,   116,   117,   118,
     119,   736,   112,   113,   121,   122,   123,   124,   125,   738,
     112,   113,   116,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   176,   740,   114,   116,   135,   143,   144,   145,
     146,   744,   114,   135,   148,   305,   746,   112,   113,   127,
     129,   130,   131,   152,   153,   154,   748,   114,   116,   135,
     143,   144,   146,   156,   157,   750,   128,   144,   153,   159,
     160,   752,   144,   160,   754,   153,   163,   164,   756,   131,
     135,   167,   168,   758,   135,   167,   168,   170,   760,   135,
     144,   159,   163,   167,   168,   172,   173,   174,   175,   176,
     773,   114,   167,   168,   783,   163,   198,   733,   735,   737,
     739,   743,   745,   747,   749,   751,   753,   755,   757,   759,
     761,   762,   763,   764,   766,   782,   790,   792,   127,   134,
     163,   392,   770,   392,   114,   198,   764,   768,   135,   167,
     168,   203,   236,   791,   114,   126,   128,   146,   150,   153,
     241,   274,   275,   356,   717,   719,   798,   242,   800,   242,
     802,   163,   243,   244,   245,   804,   128,   153,   796,   116,
     132,   153,   159,   248,   249,   806,   128,   153,   808,   114,
     128,   135,   153,   159,   810,   104,   131,   134,   151,   316,
     330,   356,   702,   703,   704,   112,   113,   116,   134,   253,
     277,   278,   279,   280,   281,   282,   284,   285,   286,   287,
     288,   289,   290,   293,   294,   295,   316,   721,   722,   725,
     330,   340,   709,   645,   650,   341,   237,   246,   247,   250,
     251,   812,   359,   360,   401,   712,   644,   502,   420,   455,
     350,   400,   455,   388,   439,   436,   437,   525,   438,   512,
     512,   515,   516,   674,   439,   439,   439,   439,   383,   406,
      46,    48,    50,    51,    58,    59,    92,   453,   518,   518,
     518,   380,   669,   684,   671,   673,   103,   103,   103,    85,
     717,   292,   620,   171,   502,   628,   700,   700,    62,    99,
     502,   104,   702,    90,   190,   283,   721,   722,   292,   315,
     292,   310,   292,   312,   313,   557,    85,   163,    85,    85,
     717,   104,     4,   374,   652,   653,   348,   526,   533,   428,
     460,   380,   293,   294,   545,   546,   381,   426,   163,   304,
     305,   306,   307,   308,   550,   551,   413,   324,   571,   407,
       5,    70,    76,    85,    87,   111,   115,   120,   126,   130,
     150,   237,   286,   289,   290,   296,   304,   326,   327,   353,
     354,   365,   583,   584,   585,   586,   587,   588,   589,   591,
     592,   593,   594,   595,   596,   629,   632,   638,   694,   695,
     696,   701,   706,   710,   716,   717,   718,   720,   726,   727,
     730,   421,   427,    38,    39,   186,   189,   577,   578,   407,
      85,   330,   331,   332,   599,   605,   606,   407,    85,   602,
     605,   385,   391,   412,   334,   335,   336,   610,   611,   615,
     616,    23,   628,   630,   631,    45,   624,   625,    15,    16,
      17,    18,   367,     8,    24,    54,     9,    10,    11,    12,
      13,    14,    19,   111,   115,   120,   126,   142,   147,   150,
     155,   158,   161,   162,   166,   169,   171,   196,   199,   202,
     329,   365,   629,   631,   632,   646,   647,   648,   651,   686,
     687,   688,   689,   690,   691,   692,   693,   695,   696,   697,
     698,    52,    52,    22,   363,   667,   686,   687,   692,   667,
      38,   363,   579,   363,   363,   363,   363,   363,   521,   528,
     580,   457,   460,   465,   467,   470,   475,   518,   518,   518,
     380,   669,   684,   671,   673,   528,   427,    57,    57,    57,
      57,   467,    57,   475,   518,   380,   403,   411,   418,   467,
     427,    43,   444,   507,   512,   527,   518,    45,   380,   507,
     507,   507,   507,   403,   411,   418,   507,   507,   509,   380,
     507,   507,   411,   512,   502,   423,     7,     8,   114,   257,
     258,   635,   308,   419,   104,   127,   292,   423,   422,   387,
     422,   397,   111,   126,   111,   126,   376,   138,   139,   140,
     141,   741,   395,   422,   398,   422,   399,   396,   422,   398,
     375,   386,   378,   424,   425,    23,    38,   103,   174,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   774,   775,   776,   422,   382,   420,   762,   392,
     764,   181,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   784,
     789,   416,   422,   395,   396,   401,   719,   415,   415,   369,
     415,   415,   369,   415,   394,   390,   384,   422,   405,   404,
     418,   404,   418,   112,   113,   126,   134,   150,   277,   278,
     279,   723,   724,   725,   379,   341,   341,   103,   415,   394,
     390,   384,   405,   358,   711,   366,   427,   467,   475,   518,
     380,   403,   411,   418,   454,   455,   682,   682,   682,   293,
     363,   668,   310,   363,   683,   363,   557,   670,   363,   503,
     672,     5,   126,   150,   595,    85,   595,   617,   618,   645,
     176,    23,    23,    97,   363,    52,    52,    52,   103,   312,
      52,   725,    52,   595,   104,   297,   504,   595,   312,   313,
     561,   595,   103,   612,   613,   614,   628,   632,   645,   649,
     710,   716,   615,   595,   595,    85,   503,    21,   651,   656,
     657,   658,   665,   692,   693,     7,   364,   503,   363,   103,
     103,   546,    78,   111,   126,   171,   260,   553,   503,   103,
     103,   103,   503,   552,   551,   142,   155,   171,   325,   595,
     414,   383,     5,   595,    85,   387,   397,   376,   395,   396,
     381,    85,   407,   407,   588,   629,   696,    15,    16,    17,
      18,   367,    20,    22,     8,    54,     5,   605,    85,    87,
     242,   304,     7,     7,   103,   103,   578,     5,     7,     5,
     595,   613,   628,   632,   611,     7,   502,   363,   502,   363,
     625,   697,   697,   688,   689,   690,   644,   363,   539,   630,
     687,   395,   398,   396,   398,   375,   386,   378,   424,   425,
     420,   382,   392,   416,   407,   692,     7,    20,    15,    16,
      17,    18,   367,     7,    20,    22,     8,   686,   687,   692,
     595,   595,   103,   364,   373,    20,   373,   103,   490,   427,
     459,   461,   466,   472,   476,   579,   363,   363,   363,   363,
     363,   682,   682,   682,   668,   683,   670,   672,   103,   103,
     103,   103,   103,   363,   682,   104,   379,   507,   103,   637,
     422,   389,   103,   409,   409,   387,   395,   387,   395,   114,
     131,   136,   137,   242,   395,   742,   377,    97,   780,   190,
     778,   195,   781,   193,   194,   779,   191,   192,   777,   131,
     226,   230,   231,   232,   788,   221,   222,   223,   224,   786,
     225,   226,   227,   228,   229,   787,   787,   230,   233,   233,
     234,   235,   234,   114,   131,   163,   785,   417,   415,   103,
     103,   112,   113,   112,   113,   379,   379,   103,   103,   342,
     708,   103,   160,   357,   713,   717,   363,   682,   363,   363,
     363,   103,   483,   380,   561,   488,   403,   484,   103,   411,
     489,   418,   595,     5,     5,   595,   630,    90,    93,   526,
     659,   660,    38,   174,   179,   189,   775,   776,   503,   503,
     103,   645,   654,   655,   595,   595,   595,   379,   103,   595,
      52,   595,   403,   103,   563,   565,   566,   411,   104,   294,
     558,    22,   412,    85,   334,    43,   595,   374,     5,   374,
     276,   291,   296,   309,   314,   662,   663,    90,    93,   526,
     661,   664,   374,   653,   462,   387,   149,   144,   149,   554,
     555,   104,   114,   570,   632,   114,   570,   420,   114,   570,
     595,     5,   595,   595,   366,   583,   583,   584,   585,   586,
     103,   588,   583,   590,   630,   651,   595,   595,    85,     8,
      85,   629,   696,   726,   726,   595,   606,   595,   605,   616,
     377,   617,   654,   374,   540,   541,   366,   692,   686,   692,
     697,   697,   688,   689,   690,   692,   103,   686,   692,   648,
     692,    20,    20,   103,    39,   373,   364,   373,   429,   526,
     579,    37,    47,    52,    54,    56,   163,   276,   291,   309,
     314,   316,   364,   373,   429,   458,   526,    94,   114,   163,
     364,   373,   429,   492,   498,   499,   526,   528,    40,    89,
      90,    91,    92,    94,    97,   114,   163,   276,   364,   373,
     429,   473,   526,   531,   532,    40,    90,    92,   114,   163,
     364,   373,   429,   473,   526,   531,    41,    44,   163,   291,
     364,   373,   429,   427,   459,   461,   466,   472,   476,   363,
     363,   363,   380,   403,   411,   418,   476,   379,   379,     7,
     419,   422,   395,   776,   422,   416,   370,   370,   395,   395,
     396,   396,   708,   345,   708,   103,   393,   401,   112,   113,
     714,   476,   379,   486,   487,   485,   294,   364,   373,   429,
     526,   668,   563,   565,   364,   373,   429,   526,   683,   364,
     373,   429,   526,   670,   558,   364,   373,   429,   526,   672,
     595,   595,     5,   504,   504,   660,   420,   377,   377,   363,
     533,   659,   404,   404,   379,   379,   379,   595,   379,    20,
     104,   294,   311,   562,   311,   564,    20,   315,   559,   612,
     628,   632,   614,   613,   595,    43,    82,    83,   666,   693,
     699,   190,   293,   380,   315,   310,   557,   663,   504,   504,
     664,   364,   373,   528,   395,     7,   420,   570,   570,    70,
     570,   595,     5,   595,   165,   595,   605,   605,     5,   364,
     531,   533,   656,     7,   364,   686,   686,   103,    39,   427,
     502,   520,   502,   511,   502,   514,   514,   502,   517,   104,
      90,   283,   285,   520,   520,   520,   520,   373,    79,    80,
     500,   501,   628,   422,    99,   373,   373,   373,   373,   373,
     464,   633,   504,   504,   362,    95,    96,   474,   103,   104,
     129,   130,   253,   273,   274,   480,   481,   491,    86,    87,
      88,    90,   468,   469,   373,   373,   373,   532,   464,   504,
     362,   481,   468,   373,   373,   373,   104,   362,    99,   380,
     364,   364,   364,   364,   364,   486,   487,   485,   364,   103,
       7,   408,   103,   393,   401,   364,    94,   134,   277,   364,
     373,   429,   526,   680,    90,    97,   134,   168,   277,   364,
     373,   429,   526,   681,   114,   277,   364,   373,   429,   526,
     677,   103,   380,   562,   564,   403,   411,   559,   418,   595,
     654,   364,   379,   318,   319,   320,   321,   322,   567,   103,
     403,   103,   566,   403,   567,   103,   411,   412,   412,   595,
     374,   103,   312,   103,   297,   504,   561,   103,   373,   555,
     422,   422,   414,   422,   595,    85,   617,     5,   364,   364,
       5,   374,   541,   189,   581,   103,   482,   460,   465,   470,
     475,   520,   520,   520,   482,   482,   482,   482,   410,   104,
       8,   373,   373,   373,   467,   410,     8,   373,     7,   373,
       5,   373,   467,     5,   373,   151,   493,   363,   477,   628,
     373,   364,   364,   364,   377,   103,   708,   362,   166,   171,
     676,   506,   379,   504,   103,   676,   103,   506,   379,   105,
     506,   379,   533,   293,   104,   558,   379,   103,   294,   381,
     381,   563,   565,   558,   398,   398,   595,   364,   617,   699,
     186,   582,   373,   363,   363,   363,   363,   363,   482,   482,
     482,   363,   363,   363,   363,    41,   633,   480,   422,   469,
      87,   463,   464,   633,    37,    87,   291,   309,   314,   316,
     471,   481,    22,   103,   104,   360,   494,   495,   496,   628,
     373,   104,   105,   478,   479,   628,   373,   379,   379,   379,
       7,   393,   363,   424,   420,   373,   373,   373,   373,   373,
     373,   373,   134,   373,   364,   379,   103,   562,   564,   559,
     364,   374,   581,   490,   461,   466,   472,   476,   363,   363,
     363,   483,   488,   484,   489,   104,   464,   373,     8,   427,
     481,   380,   403,   411,   418,   373,   373,   103,    22,    25,
       7,   364,   103,   104,   678,   679,   676,   380,   403,   403,
     411,   582,   364,   364,   364,   364,   364,   486,   487,   485,
     364,   364,   364,   364,    43,    44,   497,   373,   633,   373,
     422,   422,   103,   103,   374,   479,     5,     7,   364,   373,
     373,   373,   373,   373,   373,   364,   364,   364,   373,   373,
     373,   373,   503,   628,   362,   493,   422,   103,   679,   373,
     422,   427,   379,   379,   379,   380,   403,   411,   418,   477,
     410,   373,   373,   373
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   371,   372,   372,   373,   373,   374,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   429,   429,   429,   429,   429,   430,   430,   430,
     430,   431,   431,   431,   431,   431,   431,   431,   431,   431,
     431,   431,   431,   431,   431,   431,   431,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   433,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   435,
     436,   436,   437,   437,   438,   438,   439,   439,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   441,   441,   441,   441,   441,   441,   441,
     441,   441,   441,   441,   441,   441,   441,   441,   442,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   444,   445,   445,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   447,   447,   447,   447,
     447,   447,   447,   448,   449,   449,   450,   450,   451,   452,
     452,   453,   453,   453,   453,   453,   453,   453,   453,   454,
     454,   455,   455,   455,   456,   457,   458,   458,   459,   459,
     459,   459,   459,   459,   459,   459,   459,   459,   459,   459,
     459,   459,   459,   459,   460,   461,   461,   461,   461,   461,
     461,   461,   461,   462,   462,   462,   463,   463,   464,   464,
     465,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   467,   467,   468,   468,   469,   469,
     469,   469,   470,   471,   471,   471,   471,   471,   472,   472,
     472,   472,   472,   472,   472,   472,   472,   472,   472,   472,
     472,   472,   473,   473,   474,   474,   475,   476,   476,   476,
     476,   476,   476,   476,   477,   477,   478,   478,   478,   479,
     479,   479,   480,   480,   481,   481,   482,   483,   483,   483,
     483,   483,   484,   484,   484,   484,   484,   485,   485,   485,
     485,   485,   486,   486,   486,   486,   486,   487,   487,   487,
     487,   487,   488,   488,   488,   488,   488,   489,   489,   489,
     489,   489,   490,   490,   490,   490,   490,   491,   491,   491,
     491,   491,   492,   493,   494,   494,   495,   495,   495,   495,
     495,   496,   496,   497,   497,   497,   497,   498,   499,   500,
     500,   501,   501,   502,   502,   503,   503,   503,   504,   505,
     505,   506,   506,   506,   506,   506,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   524,   524,   524,   525,   526,
     527,   527,   528,   528,   529,   530,   530,   531,   531,   532,
     532,   532,   532,   532,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   534,   535,   535,   536,
     537,   537,   538,   539,   539,   540,   540,   540,   541,   542,
     542,   543,   543,   544,   544,   545,   545,   546,   546,   547,
     547,   547,   548,   548,   549,   550,   550,   551,   551,   551,
     551,   551,   551,   552,   553,   553,   553,   553,   553,   554,
     554,   555,   555,   556,   556,   556,   557,   557,   557,   558,
     558,   559,   559,   560,   560,   561,   561,   561,   562,   562,
     563,   564,   564,   565,   565,   566,   566,   567,   567,   567,
     567,   567,   568,   569,   570,   570,   571,   571,   571,   571,
     571,   571,   571,   571,   572,   573,   573,   574,   574,   574,
     574,   574,   574,   575,   575,   576,   576,   577,   577,   578,
     578,   578,   578,   579,   579,   580,   581,   581,   582,   582,
     583,   583,   583,   583,   583,   583,   583,   583,   583,   583,
     583,   583,   583,   584,   584,   584,   585,   585,   586,   586,
     587,   587,   588,   589,   589,   590,   590,   591,   591,   592,
     593,   594,   594,   595,   595,   595,   596,   596,   596,   596,
     596,   596,   596,   596,   596,   596,   596,   596,   596,   596,
     597,   597,   598,   599,   599,   599,   600,   600,   601,   602,
     602,   602,   602,   602,   603,   603,   604,   604,   605,   605,
     606,   606,   606,   607,   607,   607,   607,   608,   608,   609,
     610,   610,   611,   611,   612,   612,   613,   613,   613,   614,
     614,   614,   614,   615,   615,   616,   616,   617,   617,   618,
     619,   619,   619,   620,   620,   620,   621,   621,   622,   622,
     623,   624,   624,   625,   626,   626,   627,   628,   629,   629,
     630,   630,   631,   632,   633,   633,   633,   633,   633,   633,
     633,   633,   633,   633,   633,   633,   633,   633,   633,   634,
     635,   635,   635,   636,   636,   636,   636,   636,   637,   637,
     638,   638,   639,   639,   640,   640,   640,   641,   641,   642,
     642,   643,   643,   644,   645,   645,   646,   647,   648,   648,
     649,   650,   650,   650,   651,   652,   652,   652,   653,   653,
     653,   654,   654,   655,   656,   656,   657,   657,   658,   658,
     659,   659,   660,   660,   660,   661,   661,   662,   662,   663,
     663,   663,   663,   663,   663,   663,   663,   663,   664,   664,
     664,   665,   666,   666,   667,   667,   667,   667,   668,   669,
     670,   671,   672,   673,   674,   674,   674,   675,   675,   675,
     676,   676,   677,   677,   678,   678,   679,   680,   680,   680,
     681,   681,   681,   681,   681,   682,   683,   683,   684,   685,
     685,   685,   685,   685,   685,   685,   685,   686,   686,   687,
     687,   687,   688,   688,   688,   689,   689,   690,   690,   691,
     691,   692,   693,   693,   693,   693,   694,   694,   695,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   697,   697,   697,   697,   697,   697,   697,
     697,   697,   697,   697,   697,   697,   697,   697,   697,   697,
     697,   698,   698,   698,   698,   698,   698,   698,   699,   699,
     699,   699,   699,   699,   700,   700,   701,   701,   701,   702,
     702,   703,   703,   703,   703,   703,   704,   704,   704,   704,
     704,   704,   704,   704,   704,   704,   704,   704,   704,   704,
     704,   704,   704,   704,   704,   704,   704,   704,   704,   704,
     705,   705,   705,   705,   705,   705,   706,   706,   707,   707,
     707,   708,   708,   709,   709,   710,   711,   711,   712,   712,
     713,   713,   714,   714,   715,   715,   716,   716,   716,   717,
     717,   718,   718,   719,   719,   719,   719,   720,   720,   720,
     721,   721,   722,   722,   722,   722,   722,   722,   722,   722,
     722,   722,   722,   722,   722,   722,   722,   722,   722,   723,
     723,   723,   723,   723,   723,   723,   724,   724,   724,   724,
     725,   725,   725,   725,   726,   726,   727,   727,   728,   728,
     728,   728,   729,   730,   730,   730,   730,   730,   730,   730,
     730,   730,   730,   730,   730,   730,   730,   730,   730,   730,
     730,   730,   730,   730,   730,   731,   732,   732,   732,   732,
     733,   734,   734,   734,   735,   736,   736,   736,   736,   736,
     737,   738,   738,   738,   738,   738,   738,   738,   738,   738,
     739,   739,   739,   740,   740,   740,   740,   740,   740,   740,
     740,   740,   740,   740,   740,   741,   741,   741,   741,   742,
     742,   742,   742,   742,   743,   744,   744,   744,   744,   744,
     744,   744,   745,   746,   746,   746,   746,   747,   748,   748,
     748,   748,   748,   748,   748,   748,   748,   749,   750,   750,
     750,   750,   750,   750,   750,   750,   751,   752,   752,   752,
     752,   752,   753,   754,   754,   755,   756,   756,   756,   757,
     758,   758,   758,   758,   759,   760,   760,   760,   760,   761,
     761,   761,   761,   762,   762,   762,   762,   762,   762,   762,
     762,   762,   762,   762,   762,   762,   762,   763,   763,   763,
     764,   764,   765,   765,   766,   766,   767,   767,   768,   768,
     769,   769,   770,   770,   770,   771,   772,   773,   773,   773,
     773,   773,   773,   773,   773,   773,   773,   774,   774,   774,
     774,   774,   774,   775,   775,   775,   775,   775,   776,   776,
     776,   776,   776,   776,   776,   776,   776,   776,   776,   776,
     777,   777,   778,   779,   779,   780,   781,   782,   783,   783,
     783,   784,   784,   784,   784,   784,   784,   784,   784,   784,
     784,   784,   784,   784,   784,   784,   784,   784,   784,   785,
     785,   785,   786,   786,   786,   786,   787,   787,   787,   787,
     787,   788,   788,   788,   788,   789,   789,   789,   789,   789,
     789,   789,   789,   789,   789,   789,   789,   790,   790,   791,
     791,   791,   791,   792,   793,   793,   794,   794,   794,   794,
     794,   794,   794,   794,   795,   796,   796,   797,   798,   798,
     798,   798,   799,   800,   801,   802,   803,   804,   804,   804,
     804,   805,   806,   806,   806,   806,   806,   806,   807,   808,
     808,   809,   810,   810,   810,   810,   810,   811,   812,   812,
     812,   812,   812
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
       2,     2,     2,     3,     2,     2,     6,     3,     3,     5,
       3,     3,     3,     2,     2,     2,     2,     2,     3,     2,
       2,     6,     3,     3,     5,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     3,     2,     2,     3,     3,     2,
       3,     3,     2,     3,     3,     2,     3,     3,     2,     3,
       3,     2,     3,     3,     2,     2,     2,     2,     2,     2,
       4,     5,     2,     2,     1,     2,     2,     3,     3,     2,
       3,     3,     2,     3,     3,     2,     2,     2,     2,     2,
       3,     2,     2,     3,     2,     1,     2,     1,     3,     0,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     1,     1,     2,     1,     0,     2,     1,     0,     2,
       2,     3,     8,     8,     8,     8,     9,     9,    10,    10,
      10,     9,     9,     9,     0,     0,     2,     2,     3,     3,
       3,     3,     3,     0,     2,     3,     1,     3,     1,     3,
       0,     0,     2,     2,     5,     4,     4,     4,     4,     3,
       4,     2,     3,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     0,     2,     2,     2,     2,     2,     0,     2,
       2,     4,     7,     8,     6,     7,     7,     4,     3,     4,
       3,     3,     3,     2,     1,     1,     0,     0,     2,     2,
       5,     5,     3,     4,     3,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     3,     0,     0,     2,     2,
       2,     2,     0,     2,     2,     2,     2,     0,     2,     2,
       2,     2,     0,     2,     2,     2,     2,     0,     2,     2,
       2,     2,     0,     2,     2,     2,     2,     0,     2,     2,
       2,     2,     0,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     7,     2,     1,     1,     1,     1,     1,     3,
       3,     1,     2,     2,     2,     3,     0,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     2,     2,     1,     2,     1,     1,     2,     3,     2,
       3,     1,     2,     3,     1,     2,     3,     1,     2,     3,
       1,     2,     2,     2,     1,     2,     2,     2,     2,     2,
       0,     1,     1,     2,     1,     1,     2,     1,     2,     2,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     1,     1,     2,     2,     2,     2,
       1,     1,     2,     1,     1,     2,     3,     1,     1,     5,
       1,     1,     3,     3,     1,     1,     3,     3,     5,     4,
       5,     1,     2,     1,     3,     1,     2,     2,     2,     1,
       3,     3,     1,     2,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     1,     3,     3,     1,     2,     1,     3,
       1,     1,     1,     6,     6,     4,     1,     1,     0,     1,
       1,     0,     3,     6,     4,     1,     1,     0,     0,     3,
       3,     0,     2,     2,     3,     2,     2,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     0,     6,     3,     6,
       3,     5,     3,     5,     2,     1,     1,     3,     4,     4,
       5,     6,     5,     1,     2,     1,     3,     1,     2,     2,
       2,     1,     1,     6,     8,     0,     0,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     1,     1,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     2,     3,     3,
       4,     5,     2,     3,     2,     6,     4,     3,     4,     3,
       2,     1,     1,     3,     4,     1,     2,     1,     1,     2,
       3,     1,     3,     4,     3,     5,     3,     6,     1,     3,
       1,     1,     1,     2,     4,     6,     6,     1,     2,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     2,     1,
       4,     5,     6,     1,     1,     1,     7,     8,     6,     1,
       1,     1,     2,     2,     6,     8,     1,     2,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     4,
       1,     1,     2,     1,     1,     1,     1,     1,     3,     1,
       4,     4,     0,     2,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     3,     3,     3,     1,     1,
       3,     1,     1,     1,     3,     1,     3,     3,     3,     3,
       5,     1,     2,     1,     1,     2,     1,     1,     2,     1,
       1,     2,     2,     2,     1,     1,     2,     1,     2,     2,
       6,     6,     6,     4,     5,     6,     4,     4,     2,     2,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     0,
       4,     0,     1,     0,     1,     1,     1,     1,     1,     1,
       2,     2,     6,     3,     1,     3,     3,     3,     7,     3,
       3,     3,     3,     3,     3,     0,     4,     4,     0,     2,
       2,     4,     4,     5,     5,     3,     3,     3,     3,     1,
       1,     1,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     3,     3,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     1,
       1,     1,     2,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     2,     1,     2,     2,     2,     2,     2,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       5,     3,     5,     1,     5,     5,     3,     5,     1,     1,
       1,     0,     2,     1,     1,     6,     2,     0,     1,     1,
       1,     1,     1,     1,     5,     6,     8,     6,     5,     2,
       2,     3,     4,     1,     1,     1,     2,     3,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     5,     5,
       5,     6,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     7,     1,     1,     2,     1,
       3,     1,     1,     2,     3,     1,     1,     1,     1,     2,
       3,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     5,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     2,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     2,
       3,     3,     9,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     1,     2,     2,     1,     1,
       3,     3,     1,     1,     1,     3,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     5,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     3,     1,     1,
       2,     1,     3,     4,     3,     1,     3,     1,     1,     1,
       4,     3,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     3,     1,     1,     2,     1,     1,     2,     2,     2,
       2,     2,     2
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
#line 333 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6067 "parser_bison.c"
        break;

    case YYSYMBOL_QUOTED_STRING: /* "quoted string"  */
#line 333 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6073 "parser_bison.c"
        break;

    case YYSYMBOL_ASTERISK_STRING: /* "string with a trailing asterisk"  */
#line 333 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6079 "parser_bison.c"
        break;

    case YYSYMBOL_line: /* line  */
#line 656 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6085 "parser_bison.c"
        break;

    case YYSYMBOL_base_cmd: /* base_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6091 "parser_bison.c"
        break;

    case YYSYMBOL_add_cmd: /* add_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6097 "parser_bison.c"
        break;

    case YYSYMBOL_replace_cmd: /* replace_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6103 "parser_bison.c"
        break;

    case YYSYMBOL_create_cmd: /* create_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6109 "parser_bison.c"
        break;

    case YYSYMBOL_insert_cmd: /* insert_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6115 "parser_bison.c"
        break;

    case YYSYMBOL_table_or_id_spec: /* table_or_id_spec  */
#line 662 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6121 "parser_bison.c"
        break;

    case YYSYMBOL_chain_or_id_spec: /* chain_or_id_spec  */
#line 664 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6127 "parser_bison.c"
        break;

    case YYSYMBOL_set_or_id_spec: /* set_or_id_spec  */
#line 669 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6133 "parser_bison.c"
        break;

    case YYSYMBOL_obj_or_id_spec: /* obj_or_id_spec  */
#line 671 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6139 "parser_bison.c"
        break;

    case YYSYMBOL_delete_cmd: /* delete_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6145 "parser_bison.c"
        break;

    case YYSYMBOL_destroy_cmd: /* destroy_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6151 "parser_bison.c"
        break;

    case YYSYMBOL_get_cmd: /* get_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6157 "parser_bison.c"
        break;

    case YYSYMBOL_list_cmd: /* list_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6163 "parser_bison.c"
        break;

    case YYSYMBOL_basehook_device_name: /* basehook_device_name  */
#line 683 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6169 "parser_bison.c"
        break;

    case YYSYMBOL_basehook_spec: /* basehook_spec  */
#line 677 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6175 "parser_bison.c"
        break;

    case YYSYMBOL_reset_cmd: /* reset_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6181 "parser_bison.c"
        break;

    case YYSYMBOL_flush_cmd: /* flush_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6187 "parser_bison.c"
        break;

    case YYSYMBOL_rename_cmd: /* rename_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6193 "parser_bison.c"
        break;

    case YYSYMBOL_import_cmd: /* import_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6199 "parser_bison.c"
        break;

    case YYSYMBOL_export_cmd: /* export_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6205 "parser_bison.c"
        break;

    case YYSYMBOL_monitor_cmd: /* monitor_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6211 "parser_bison.c"
        break;

    case YYSYMBOL_monitor_event: /* monitor_event  */
#line 902 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6217 "parser_bison.c"
        break;

    case YYSYMBOL_describe_cmd: /* describe_cmd  */
#line 659 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6223 "parser_bison.c"
        break;

    case YYSYMBOL_table_block_alloc: /* table_block_alloc  */
#line 689 "parser_bison.y"
            { close_scope(state); table_free(((*yyvaluep).table)); }
#line 6229 "parser_bison.c"
        break;

    case YYSYMBOL_chain_block_alloc: /* chain_block_alloc  */
#line 691 "parser_bison.y"
            { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 6235 "parser_bison.c"
        break;

    case YYSYMBOL_typeof_data_expr: /* typeof_data_expr  */
#line 763 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6241 "parser_bison.c"
        break;

    case YYSYMBOL_typeof_expr: /* typeof_expr  */
#line 763 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6247 "parser_bison.c"
        break;

    case YYSYMBOL_set_block_alloc: /* set_block_alloc  */
#line 700 "parser_bison.y"
            { set_free(((*yyvaluep).set)); }
#line 6253 "parser_bison.c"
        break;

    case YYSYMBOL_set_block_expr: /* set_block_expr  */
#line 804 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6259 "parser_bison.c"
        break;

    case YYSYMBOL_map_block_alloc: /* map_block_alloc  */
#line 703 "parser_bison.y"
            { set_free(((*yyvaluep).set)); }
#line 6265 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_block_alloc: /* flowtable_block_alloc  */
#line 707 "parser_bison.y"
            { flowtable_free(((*yyvaluep).flowtable)); }
#line 6271 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_expr: /* flowtable_expr  */
#line 804 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6277 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_list_expr: /* flowtable_list_expr  */
#line 804 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6283 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_expr_member: /* flowtable_expr_member  */
#line 804 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6289 "parser_bison.c"
        break;

    case YYSYMBOL_data_type_atom_expr: /* data_type_atom_expr  */
#line 653 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6295 "parser_bison.c"
        break;

    case YYSYMBOL_data_type_expr: /* data_type_expr  */
#line 653 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6301 "parser_bison.c"
        break;

    case YYSYMBOL_obj_block_alloc: /* obj_block_alloc  */
#line 710 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6307 "parser_bison.c"
        break;

    case YYSYMBOL_type_identifier: /* type_identifier  */
#line 648 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6313 "parser_bison.c"
        break;

    case YYSYMBOL_extended_prio_name: /* extended_prio_name  */
#line 683 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6319 "parser_bison.c"
        break;

    case YYSYMBOL_dev_spec: /* dev_spec  */
#line 686 "parser_bison.y"
            { xfree(((*yyvaluep).expr)); }
#line 6325 "parser_bison.c"
        break;

    case YYSYMBOL_policy_expr: /* policy_expr  */
#line 761 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6331 "parser_bison.c"
        break;

    case YYSYMBOL_identifier: /* identifier  */
#line 648 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6337 "parser_bison.c"
        break;

    case YYSYMBOL_string: /* string  */
#line 648 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6343 "parser_bison.c"
        break;

    case YYSYMBOL_table_spec: /* table_spec  */
#line 662 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6349 "parser_bison.c"
        break;

    case YYSYMBOL_tableid_spec: /* tableid_spec  */
#line 662 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6355 "parser_bison.c"
        break;

    case YYSYMBOL_chain_spec: /* chain_spec  */
#line 664 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6361 "parser_bison.c"
        break;

    case YYSYMBOL_chainid_spec: /* chainid_spec  */
#line 664 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6367 "parser_bison.c"
        break;

    case YYSYMBOL_chain_identifier: /* chain_identifier  */
#line 667 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6373 "parser_bison.c"
        break;

    case YYSYMBOL_set_spec: /* set_spec  */
#line 669 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6379 "parser_bison.c"
        break;

    case YYSYMBOL_setid_spec: /* setid_spec  */
#line 669 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6385 "parser_bison.c"
        break;

    case YYSYMBOL_set_identifier: /* set_identifier  */
#line 674 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6391 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_spec: /* flowtable_spec  */
#line 667 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6397 "parser_bison.c"
        break;

    case YYSYMBOL_flowtableid_spec: /* flowtableid_spec  */
#line 674 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6403 "parser_bison.c"
        break;

    case YYSYMBOL_obj_spec: /* obj_spec  */
#line 671 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6409 "parser_bison.c"
        break;

    case YYSYMBOL_objid_spec: /* objid_spec  */
#line 671 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6415 "parser_bison.c"
        break;

    case YYSYMBOL_obj_identifier: /* obj_identifier  */
#line 674 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6421 "parser_bison.c"
        break;

    case YYSYMBOL_handle_spec: /* handle_spec  */
#line 667 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6427 "parser_bison.c"
        break;

    case YYSYMBOL_position_spec: /* position_spec  */
#line 667 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6433 "parser_bison.c"
        break;

    case YYSYMBOL_index_spec: /* index_spec  */
#line 667 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6439 "parser_bison.c"
        break;

    case YYSYMBOL_rule_position: /* rule_position  */
#line 667 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6445 "parser_bison.c"
        break;

    case YYSYMBOL_ruleid_spec: /* ruleid_spec  */
#line 667 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6451 "parser_bison.c"
        break;

    case YYSYMBOL_comment_spec: /* comment_spec  */
#line 648 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6457 "parser_bison.c"
        break;

    case YYSYMBOL_ruleset_spec: /* ruleset_spec  */
#line 667 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6463 "parser_bison.c"
        break;

    case YYSYMBOL_rule: /* rule  */
#line 693 "parser_bison.y"
            { rule_free(((*yyvaluep).rule)); }
#line 6469 "parser_bison.c"
        break;

    case YYSYMBOL_stmt_list: /* stmt_list  */
#line 713 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6475 "parser_bison.c"
        break;

    case YYSYMBOL_stateful_stmt_list: /* stateful_stmt_list  */
#line 713 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6481 "parser_bison.c"
        break;

    case YYSYMBOL_stateful_stmt: /* stateful_stmt  */
#line 717 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6487 "parser_bison.c"
        break;

    case YYSYMBOL_stmt: /* stmt  */
#line 715 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6493 "parser_bison.c"
        break;

    case YYSYMBOL_xt_stmt: /* xt_stmt  */
#line 926 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6499 "parser_bison.c"
        break;

    case YYSYMBOL_chain_stmt: /* chain_stmt  */
#line 740 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6505 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_stmt: /* verdict_stmt  */
#line 715 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6511 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_stmt: /* verdict_map_stmt  */
#line 798 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6517 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_expr: /* verdict_map_expr  */
#line 801 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6523 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_list_expr: /* verdict_map_list_expr  */
#line 801 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6529 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_list_member_expr: /* verdict_map_list_member_expr  */
#line 801 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6535 "parser_bison.c"
        break;

    case YYSYMBOL_connlimit_stmt: /* connlimit_stmt  */
#line 728 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6541 "parser_bison.c"
        break;

    case YYSYMBOL_counter_stmt: /* counter_stmt  */
#line 717 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6547 "parser_bison.c"
        break;

    case YYSYMBOL_counter_stmt_alloc: /* counter_stmt_alloc  */
#line 717 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6553 "parser_bison.c"
        break;

    case YYSYMBOL_last_stmt: /* last_stmt  */
#line 717 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6559 "parser_bison.c"
        break;

    case YYSYMBOL_log_stmt: /* log_stmt  */
#line 725 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6565 "parser_bison.c"
        break;

    case YYSYMBOL_log_stmt_alloc: /* log_stmt_alloc  */
#line 725 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6571 "parser_bison.c"
        break;

    case YYSYMBOL_limit_stmt: /* limit_stmt  */
#line 728 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6577 "parser_bison.c"
        break;

    case YYSYMBOL_quota_unit: /* quota_unit  */
#line 683 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6583 "parser_bison.c"
        break;

    case YYSYMBOL_quota_stmt: /* quota_stmt  */
#line 728 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6589 "parser_bison.c"
        break;

    case YYSYMBOL_reject_stmt: /* reject_stmt  */
#line 731 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6595 "parser_bison.c"
        break;

    case YYSYMBOL_reject_stmt_alloc: /* reject_stmt_alloc  */
#line 731 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6601 "parser_bison.c"
        break;

    case YYSYMBOL_reject_with_expr: /* reject_with_expr  */
#line 746 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6607 "parser_bison.c"
        break;

    case YYSYMBOL_nat_stmt: /* nat_stmt  */
#line 733 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6613 "parser_bison.c"
        break;

    case YYSYMBOL_nat_stmt_alloc: /* nat_stmt_alloc  */
#line 733 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6619 "parser_bison.c"
        break;

    case YYSYMBOL_tproxy_stmt: /* tproxy_stmt  */
#line 736 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6625 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_stmt: /* synproxy_stmt  */
#line 738 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6631 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_stmt_alloc: /* synproxy_stmt_alloc  */
#line 738 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6637 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_obj: /* synproxy_obj  */
#line 824 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6643 "parser_bison.c"
        break;

    case YYSYMBOL_primary_stmt_expr: /* primary_stmt_expr  */
#line 785 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6649 "parser_bison.c"
        break;

    case YYSYMBOL_shift_stmt_expr: /* shift_stmt_expr  */
#line 787 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6655 "parser_bison.c"
        break;

    case YYSYMBOL_and_stmt_expr: /* and_stmt_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6661 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_stmt_expr: /* exclusive_or_stmt_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6667 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_stmt_expr: /* inclusive_or_stmt_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6673 "parser_bison.c"
        break;

    case YYSYMBOL_basic_stmt_expr: /* basic_stmt_expr  */
#line 785 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6679 "parser_bison.c"
        break;

    case YYSYMBOL_concat_stmt_expr: /* concat_stmt_expr  */
#line 777 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6685 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt_expr_set: /* map_stmt_expr_set  */
#line 777 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6691 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt_expr: /* map_stmt_expr  */
#line 777 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6697 "parser_bison.c"
        break;

    case YYSYMBOL_prefix_stmt_expr: /* prefix_stmt_expr  */
#line 782 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6703 "parser_bison.c"
        break;

    case YYSYMBOL_range_stmt_expr: /* range_stmt_expr  */
#line 782 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6709 "parser_bison.c"
        break;

    case YYSYMBOL_multiton_stmt_expr: /* multiton_stmt_expr  */
#line 780 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6715 "parser_bison.c"
        break;

    case YYSYMBOL_stmt_expr: /* stmt_expr  */
#line 777 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6721 "parser_bison.c"
        break;

    case YYSYMBOL_masq_stmt: /* masq_stmt  */
#line 733 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6727 "parser_bison.c"
        break;

    case YYSYMBOL_masq_stmt_alloc: /* masq_stmt_alloc  */
#line 733 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6733 "parser_bison.c"
        break;

    case YYSYMBOL_redir_stmt: /* redir_stmt  */
#line 733 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6739 "parser_bison.c"
        break;

    case YYSYMBOL_redir_stmt_alloc: /* redir_stmt_alloc  */
#line 733 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6745 "parser_bison.c"
        break;

    case YYSYMBOL_dup_stmt: /* dup_stmt  */
#line 749 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6751 "parser_bison.c"
        break;

    case YYSYMBOL_fwd_stmt: /* fwd_stmt  */
#line 751 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6757 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt: /* queue_stmt  */
#line 744 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6763 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_compat: /* queue_stmt_compat  */
#line 744 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6769 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_alloc: /* queue_stmt_alloc  */
#line 744 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6775 "parser_bison.c"
        break;

    case YYSYMBOL_queue_expr: /* queue_expr  */
#line 746 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6781 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_expr_simple: /* queue_stmt_expr_simple  */
#line 746 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6787 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_expr: /* queue_stmt_expr  */
#line 746 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6793 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_stmt: /* set_elem_expr_stmt  */
#line 808 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6799 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_stmt_alloc: /* set_elem_expr_stmt_alloc  */
#line 808 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6805 "parser_bison.c"
        break;

    case YYSYMBOL_set_stmt: /* set_stmt  */
#line 753 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6811 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt: /* map_stmt  */
#line 756 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6817 "parser_bison.c"
        break;

    case YYSYMBOL_meter_stmt: /* meter_stmt  */
#line 758 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6823 "parser_bison.c"
        break;

    case YYSYMBOL_flow_stmt_legacy_alloc: /* flow_stmt_legacy_alloc  */
#line 758 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6829 "parser_bison.c"
        break;

    case YYSYMBOL_meter_stmt_alloc: /* meter_stmt_alloc  */
#line 758 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6835 "parser_bison.c"
        break;

    case YYSYMBOL_match_stmt: /* match_stmt  */
#line 715 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6841 "parser_bison.c"
        break;

    case YYSYMBOL_variable_expr: /* variable_expr  */
#line 761 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6847 "parser_bison.c"
        break;

    case YYSYMBOL_symbol_expr: /* symbol_expr  */
#line 761 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6853 "parser_bison.c"
        break;

    case YYSYMBOL_set_ref_expr: /* set_ref_expr  */
#line 769 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6859 "parser_bison.c"
        break;

    case YYSYMBOL_set_ref_symbol_expr: /* set_ref_symbol_expr  */
#line 769 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6865 "parser_bison.c"
        break;

    case YYSYMBOL_integer_expr: /* integer_expr  */
#line 761 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6871 "parser_bison.c"
        break;

    case YYSYMBOL_primary_expr: /* primary_expr  */
#line 763 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6877 "parser_bison.c"
        break;

    case YYSYMBOL_fib_expr: /* fib_expr  */
#line 893 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6883 "parser_bison.c"
        break;

    case YYSYMBOL_osf_expr: /* osf_expr  */
#line 898 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6889 "parser_bison.c"
        break;

    case YYSYMBOL_shift_expr: /* shift_expr  */
#line 763 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6895 "parser_bison.c"
        break;

    case YYSYMBOL_and_expr: /* and_expr  */
#line 763 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6901 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_expr: /* exclusive_or_expr  */
#line 765 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6907 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_expr: /* inclusive_or_expr  */
#line 765 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6913 "parser_bison.c"
        break;

    case YYSYMBOL_basic_expr: /* basic_expr  */
#line 767 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6919 "parser_bison.c"
        break;

    case YYSYMBOL_concat_expr: /* concat_expr  */
#line 792 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6925 "parser_bison.c"
        break;

    case YYSYMBOL_prefix_rhs_expr: /* prefix_rhs_expr  */
#line 774 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6931 "parser_bison.c"
        break;

    case YYSYMBOL_range_rhs_expr: /* range_rhs_expr  */
#line 774 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6937 "parser_bison.c"
        break;

    case YYSYMBOL_multiton_rhs_expr: /* multiton_rhs_expr  */
#line 772 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6943 "parser_bison.c"
        break;

    case YYSYMBOL_map_expr: /* map_expr  */
#line 795 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6949 "parser_bison.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6955 "parser_bison.c"
        break;

    case YYSYMBOL_set_expr: /* set_expr  */
#line 804 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6961 "parser_bison.c"
        break;

    case YYSYMBOL_set_list_expr: /* set_list_expr  */
#line 804 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6967 "parser_bison.c"
        break;

    case YYSYMBOL_set_list_member_expr: /* set_list_member_expr  */
#line 804 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6973 "parser_bison.c"
        break;

    case YYSYMBOL_meter_key_expr: /* meter_key_expr  */
#line 811 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6979 "parser_bison.c"
        break;

    case YYSYMBOL_meter_key_expr_alloc: /* meter_key_expr_alloc  */
#line 811 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6985 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr: /* set_elem_expr  */
#line 806 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6991 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_key_expr: /* set_elem_key_expr  */
#line 946 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6997 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_alloc: /* set_elem_expr_alloc  */
#line 806 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7003 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_stmt_list: /* set_elem_stmt_list  */
#line 713 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 7009 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_stmt: /* set_elem_stmt  */
#line 715 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7015 "parser_bison.c"
        break;

    case YYSYMBOL_set_lhs_expr: /* set_lhs_expr  */
#line 806 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7021 "parser_bison.c"
        break;

    case YYSYMBOL_set_rhs_expr: /* set_rhs_expr  */
#line 806 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7027 "parser_bison.c"
        break;

    case YYSYMBOL_initializer_expr: /* initializer_expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7033 "parser_bison.c"
        break;

    case YYSYMBOL_counter_obj: /* counter_obj  */
#line 824 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7039 "parser_bison.c"
        break;

    case YYSYMBOL_quota_obj: /* quota_obj  */
#line 824 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7045 "parser_bison.c"
        break;

    case YYSYMBOL_secmark_obj: /* secmark_obj  */
#line 824 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7051 "parser_bison.c"
        break;

    case YYSYMBOL_timeout_states: /* timeout_states  */
#line 939 "parser_bison.y"
            { xfree(((*yyvaluep).list)); }
#line 7057 "parser_bison.c"
        break;

    case YYSYMBOL_timeout_state: /* timeout_state  */
#line 939 "parser_bison.y"
            { xfree(((*yyvaluep).list)); }
#line 7063 "parser_bison.c"
        break;

    case YYSYMBOL_ct_obj_alloc: /* ct_obj_alloc  */
#line 824 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7069 "parser_bison.c"
        break;

    case YYSYMBOL_limit_obj: /* limit_obj  */
#line 824 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7075 "parser_bison.c"
        break;

    case YYSYMBOL_relational_expr: /* relational_expr  */
#line 827 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7081 "parser_bison.c"
        break;

    case YYSYMBOL_list_rhs_expr: /* list_rhs_expr  */
#line 819 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7087 "parser_bison.c"
        break;

    case YYSYMBOL_rhs_expr: /* rhs_expr  */
#line 817 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7093 "parser_bison.c"
        break;

    case YYSYMBOL_shift_rhs_expr: /* shift_rhs_expr  */
#line 819 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7099 "parser_bison.c"
        break;

    case YYSYMBOL_and_rhs_expr: /* and_rhs_expr  */
#line 821 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7105 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_rhs_expr: /* exclusive_or_rhs_expr  */
#line 821 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7111 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_rhs_expr: /* inclusive_or_rhs_expr  */
#line 821 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7117 "parser_bison.c"
        break;

    case YYSYMBOL_basic_rhs_expr: /* basic_rhs_expr  */
#line 817 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7123 "parser_bison.c"
        break;

    case YYSYMBOL_concat_rhs_expr: /* concat_rhs_expr  */
#line 817 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7129 "parser_bison.c"
        break;

    case YYSYMBOL_boolean_expr: /* boolean_expr  */
#line 929 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7135 "parser_bison.c"
        break;

    case YYSYMBOL_keyword_expr: /* keyword_expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7141 "parser_bison.c"
        break;

    case YYSYMBOL_primary_rhs_expr: /* primary_rhs_expr  */
#line 819 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7147 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_expr: /* verdict_expr  */
#line 761 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7153 "parser_bison.c"
        break;

    case YYSYMBOL_chain_expr: /* chain_expr  */
#line 761 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7159 "parser_bison.c"
        break;

    case YYSYMBOL_meta_expr: /* meta_expr  */
#line 875 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7165 "parser_bison.c"
        break;

    case YYSYMBOL_meta_stmt: /* meta_stmt  */
#line 723 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7171 "parser_bison.c"
        break;

    case YYSYMBOL_socket_expr: /* socket_expr  */
#line 879 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7177 "parser_bison.c"
        break;

    case YYSYMBOL_numgen_expr: /* numgen_expr  */
#line 840 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7183 "parser_bison.c"
        break;

    case YYSYMBOL_xfrm_expr: /* xfrm_expr  */
#line 943 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7189 "parser_bison.c"
        break;

    case YYSYMBOL_hash_expr: /* hash_expr  */
#line 840 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7195 "parser_bison.c"
        break;

    case YYSYMBOL_rt_expr: /* rt_expr  */
#line 885 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7201 "parser_bison.c"
        break;

    case YYSYMBOL_ct_expr: /* ct_expr  */
#line 889 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7207 "parser_bison.c"
        break;

    case YYSYMBOL_symbol_stmt_expr: /* symbol_stmt_expr  */
#line 819 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7213 "parser_bison.c"
        break;

    case YYSYMBOL_list_stmt_expr: /* list_stmt_expr  */
#line 787 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7219 "parser_bison.c"
        break;

    case YYSYMBOL_ct_stmt: /* ct_stmt  */
#line 721 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7225 "parser_bison.c"
        break;

    case YYSYMBOL_payload_stmt: /* payload_stmt  */
#line 719 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7231 "parser_bison.c"
        break;

    case YYSYMBOL_payload_expr: /* payload_expr  */
#line 831 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7237 "parser_bison.c"
        break;

    case YYSYMBOL_payload_raw_expr: /* payload_raw_expr  */
#line 831 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7243 "parser_bison.c"
        break;

    case YYSYMBOL_eth_hdr_expr: /* eth_hdr_expr  */
#line 834 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7249 "parser_bison.c"
        break;

    case YYSYMBOL_vlan_hdr_expr: /* vlan_hdr_expr  */
#line 834 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7255 "parser_bison.c"
        break;

    case YYSYMBOL_arp_hdr_expr: /* arp_hdr_expr  */
#line 837 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7261 "parser_bison.c"
        break;

    case YYSYMBOL_ip_hdr_expr: /* ip_hdr_expr  */
#line 840 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7267 "parser_bison.c"
        break;

    case YYSYMBOL_icmp_hdr_expr: /* icmp_hdr_expr  */
#line 840 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7273 "parser_bison.c"
        break;

    case YYSYMBOL_igmp_hdr_expr: /* igmp_hdr_expr  */
#line 840 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7279 "parser_bison.c"
        break;

    case YYSYMBOL_ip6_hdr_expr: /* ip6_hdr_expr  */
#line 844 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7285 "parser_bison.c"
        break;

    case YYSYMBOL_icmp6_hdr_expr: /* icmp6_hdr_expr  */
#line 844 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7291 "parser_bison.c"
        break;

    case YYSYMBOL_auth_hdr_expr: /* auth_hdr_expr  */
#line 847 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7297 "parser_bison.c"
        break;

    case YYSYMBOL_esp_hdr_expr: /* esp_hdr_expr  */
#line 847 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7303 "parser_bison.c"
        break;

    case YYSYMBOL_comp_hdr_expr: /* comp_hdr_expr  */
#line 847 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7309 "parser_bison.c"
        break;

    case YYSYMBOL_udp_hdr_expr: /* udp_hdr_expr  */
#line 850 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7315 "parser_bison.c"
        break;

    case YYSYMBOL_udplite_hdr_expr: /* udplite_hdr_expr  */
#line 850 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7321 "parser_bison.c"
        break;

    case YYSYMBOL_tcp_hdr_expr: /* tcp_hdr_expr  */
#line 908 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7327 "parser_bison.c"
        break;

    case YYSYMBOL_inner_inet_expr: /* inner_inet_expr  */
#line 916 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7333 "parser_bison.c"
        break;

    case YYSYMBOL_inner_eth_expr: /* inner_eth_expr  */
#line 916 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7339 "parser_bison.c"
        break;

    case YYSYMBOL_inner_expr: /* inner_expr  */
#line 916 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7345 "parser_bison.c"
        break;

    case YYSYMBOL_vxlan_hdr_expr: /* vxlan_hdr_expr  */
#line 919 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7351 "parser_bison.c"
        break;

    case YYSYMBOL_geneve_hdr_expr: /* geneve_hdr_expr  */
#line 919 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7357 "parser_bison.c"
        break;

    case YYSYMBOL_gre_hdr_expr: /* gre_hdr_expr  */
#line 919 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7363 "parser_bison.c"
        break;

    case YYSYMBOL_gretap_hdr_expr: /* gretap_hdr_expr  */
#line 919 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7369 "parser_bison.c"
        break;

    case YYSYMBOL_optstrip_stmt: /* optstrip_stmt  */
#line 923 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7375 "parser_bison.c"
        break;

    case YYSYMBOL_dccp_hdr_expr: /* dccp_hdr_expr  */
#line 853 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7381 "parser_bison.c"
        break;

    case YYSYMBOL_sctp_chunk_alloc: /* sctp_chunk_alloc  */
#line 853 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7387 "parser_bison.c"
        break;

    case YYSYMBOL_sctp_hdr_expr: /* sctp_hdr_expr  */
#line 853 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7393 "parser_bison.c"
        break;

    case YYSYMBOL_th_hdr_expr: /* th_hdr_expr  */
#line 859 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7399 "parser_bison.c"
        break;

    case YYSYMBOL_exthdr_expr: /* exthdr_expr  */
#line 863 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7405 "parser_bison.c"
        break;

    case YYSYMBOL_hbh_hdr_expr: /* hbh_hdr_expr  */
#line 865 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7411 "parser_bison.c"
        break;

    case YYSYMBOL_rt_hdr_expr: /* rt_hdr_expr  */
#line 868 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7417 "parser_bison.c"
        break;

    case YYSYMBOL_rt0_hdr_expr: /* rt0_hdr_expr  */
#line 868 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7423 "parser_bison.c"
        break;

    case YYSYMBOL_rt2_hdr_expr: /* rt2_hdr_expr  */
#line 868 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7429 "parser_bison.c"
        break;

    case YYSYMBOL_rt4_hdr_expr: /* rt4_hdr_expr  */
#line 868 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7435 "parser_bison.c"
        break;

    case YYSYMBOL_frag_hdr_expr: /* frag_hdr_expr  */
#line 865 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7441 "parser_bison.c"
        break;

    case YYSYMBOL_dst_hdr_expr: /* dst_hdr_expr  */
#line 865 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7447 "parser_bison.c"
        break;

    case YYSYMBOL_mh_hdr_expr: /* mh_hdr_expr  */
#line 871 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7453 "parser_bison.c"
        break;

    case YYSYMBOL_exthdr_exists_expr: /* exthdr_exists_expr  */
#line 933 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7459 "parser_bison.c"
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
#line 170 "parser_bison.y"
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 7564 "parser_bison.c"

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
#line 952 "parser_bison.y"
                        {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 7781 "parser_bison.c"
    break;

  case 8: /* close_scope_ah: %empty  */
#line 968 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_AH); }
#line 7787 "parser_bison.c"
    break;

  case 9: /* close_scope_arp: %empty  */
#line 969 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ARP); }
#line 7793 "parser_bison.c"
    break;

  case 10: /* close_scope_at: %empty  */
#line 970 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_AT); }
#line 7799 "parser_bison.c"
    break;

  case 11: /* close_scope_comp: %empty  */
#line 971 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_COMP); }
#line 7805 "parser_bison.c"
    break;

  case 12: /* close_scope_ct: %empty  */
#line 972 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CT); }
#line 7811 "parser_bison.c"
    break;

  case 13: /* close_scope_counter: %empty  */
#line 973 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_COUNTER); }
#line 7817 "parser_bison.c"
    break;

  case 14: /* close_scope_last: %empty  */
#line 974 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_LAST); }
#line 7823 "parser_bison.c"
    break;

  case 15: /* close_scope_dccp: %empty  */
#line 975 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_DCCP); }
#line 7829 "parser_bison.c"
    break;

  case 16: /* close_scope_destroy: %empty  */
#line 976 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_DESTROY); }
#line 7835 "parser_bison.c"
    break;

  case 17: /* close_scope_dst: %empty  */
#line 977 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_DST); }
#line 7841 "parser_bison.c"
    break;

  case 18: /* close_scope_dup: %empty  */
#line 978 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_DUP); }
#line 7847 "parser_bison.c"
    break;

  case 19: /* close_scope_esp: %empty  */
#line 979 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_ESP); }
#line 7853 "parser_bison.c"
    break;

  case 20: /* close_scope_eth: %empty  */
#line 980 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ETH); }
#line 7859 "parser_bison.c"
    break;

  case 21: /* close_scope_export: %empty  */
#line 981 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_EXPORT); }
#line 7865 "parser_bison.c"
    break;

  case 22: /* close_scope_fib: %empty  */
#line 982 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FIB); }
#line 7871 "parser_bison.c"
    break;

  case 23: /* close_scope_frag: %empty  */
#line 983 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FRAG); }
#line 7877 "parser_bison.c"
    break;

  case 24: /* close_scope_fwd: %empty  */
#line 984 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_FWD); }
#line 7883 "parser_bison.c"
    break;

  case 25: /* close_scope_gre: %empty  */
#line 985 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_GRE); }
#line 7889 "parser_bison.c"
    break;

  case 26: /* close_scope_hash: %empty  */
#line 986 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HASH); }
#line 7895 "parser_bison.c"
    break;

  case 27: /* close_scope_hbh: %empty  */
#line 987 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HBH); }
#line 7901 "parser_bison.c"
    break;

  case 28: /* close_scope_ip: %empty  */
#line 988 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP); }
#line 7907 "parser_bison.c"
    break;

  case 29: /* close_scope_ip6: %empty  */
#line 989 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP6); }
#line 7913 "parser_bison.c"
    break;

  case 30: /* close_scope_vlan: %empty  */
#line 990 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_VLAN); }
#line 7919 "parser_bison.c"
    break;

  case 31: /* close_scope_icmp: %empty  */
#line 991 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ICMP); }
#line 7925 "parser_bison.c"
    break;

  case 32: /* close_scope_igmp: %empty  */
#line 992 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IGMP); }
#line 7931 "parser_bison.c"
    break;

  case 33: /* close_scope_import: %empty  */
#line 993 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_IMPORT); }
#line 7937 "parser_bison.c"
    break;

  case 34: /* close_scope_ipsec: %empty  */
#line 994 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_IPSEC); }
#line 7943 "parser_bison.c"
    break;

  case 35: /* close_scope_list: %empty  */
#line 995 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_LIST); }
#line 7949 "parser_bison.c"
    break;

  case 36: /* close_scope_limit: %empty  */
#line 996 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_LIMIT); }
#line 7955 "parser_bison.c"
    break;

  case 37: /* close_scope_meta: %empty  */
#line 997 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_META); }
#line 7961 "parser_bison.c"
    break;

  case 38: /* close_scope_mh: %empty  */
#line 998 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_MH); }
#line 7967 "parser_bison.c"
    break;

  case 39: /* close_scope_monitor: %empty  */
#line 999 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_MONITOR); }
#line 7973 "parser_bison.c"
    break;

  case 40: /* close_scope_nat: %empty  */
#line 1000 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_NAT); }
#line 7979 "parser_bison.c"
    break;

  case 41: /* close_scope_numgen: %empty  */
#line 1001 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_NUMGEN); }
#line 7985 "parser_bison.c"
    break;

  case 42: /* close_scope_osf: %empty  */
#line 1002 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_OSF); }
#line 7991 "parser_bison.c"
    break;

  case 43: /* close_scope_policy: %empty  */
#line 1003 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_POLICY); }
#line 7997 "parser_bison.c"
    break;

  case 44: /* close_scope_quota: %empty  */
#line 1004 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_QUOTA); }
#line 8003 "parser_bison.c"
    break;

  case 45: /* close_scope_queue: %empty  */
#line 1005 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_QUEUE); }
#line 8009 "parser_bison.c"
    break;

  case 46: /* close_scope_reject: %empty  */
#line 1006 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_REJECT); }
#line 8015 "parser_bison.c"
    break;

  case 47: /* close_scope_reset: %empty  */
#line 1007 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_RESET); }
#line 8021 "parser_bison.c"
    break;

  case 48: /* close_scope_rt: %empty  */
#line 1008 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_RT); }
#line 8027 "parser_bison.c"
    break;

  case 49: /* close_scope_sctp: %empty  */
#line 1009 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_SCTP); }
#line 8033 "parser_bison.c"
    break;

  case 50: /* close_scope_sctp_chunk: %empty  */
#line 1010 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SCTP_CHUNK); }
#line 8039 "parser_bison.c"
    break;

  case 51: /* close_scope_secmark: %empty  */
#line 1011 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_SECMARK); }
#line 8045 "parser_bison.c"
    break;

  case 52: /* close_scope_socket: %empty  */
#line 1012 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SOCKET); }
#line 8051 "parser_bison.c"
    break;

  case 53: /* close_scope_tcp: %empty  */
#line 1013 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_TCP); }
#line 8057 "parser_bison.c"
    break;

  case 54: /* close_scope_tproxy: %empty  */
#line 1014 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_TPROXY); }
#line 8063 "parser_bison.c"
    break;

  case 55: /* close_scope_type: %empty  */
#line 1015 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_TYPE); }
#line 8069 "parser_bison.c"
    break;

  case 56: /* close_scope_th: %empty  */
#line 1016 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_TH); }
#line 8075 "parser_bison.c"
    break;

  case 57: /* close_scope_udp: %empty  */
#line 1017 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_UDP); }
#line 8081 "parser_bison.c"
    break;

  case 58: /* close_scope_udplite: %empty  */
#line 1018 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_UDPLITE); }
#line 8087 "parser_bison.c"
    break;

  case 59: /* close_scope_log: %empty  */
#line 1020 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_LOG); }
#line 8093 "parser_bison.c"
    break;

  case 60: /* close_scope_synproxy: %empty  */
#line 1021 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_SYNPROXY); }
#line 8099 "parser_bison.c"
    break;

  case 61: /* close_scope_xt: %empty  */
#line 1022 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_XT); }
#line 8105 "parser_bison.c"
    break;

  case 62: /* common_block: "include" "quoted string" stmt_separator  */
#line 1025 "parser_bison.y"
                        {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 8117 "parser_bison.c"
    break;

  case 63: /* common_block: "define" identifier '=' initializer_expr stmt_separator  */
#line 1033 "parser_bison.y"
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
#line 8136 "parser_bison.c"
    break;

  case 64: /* common_block: "redefine" identifier '=' initializer_expr stmt_separator  */
#line 1048 "parser_bison.y"
                        {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 8147 "parser_bison.c"
    break;

  case 65: /* common_block: "undefine" identifier stmt_separator  */
#line 1055 "parser_bison.y"
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
#line 8163 "parser_bison.c"
    break;

  case 66: /* common_block: error stmt_separator  */
#line 1067 "parser_bison.y"
                        {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 8173 "parser_bison.c"
    break;

  case 67: /* line: common_block  */
#line 1074 "parser_bison.y"
                                                                { (yyval.cmd) = NULL; }
#line 8179 "parser_bison.c"
    break;

  case 68: /* line: stmt_separator  */
#line 1075 "parser_bison.y"
                                                                { (yyval.cmd) = NULL; }
#line 8185 "parser_bison.c"
    break;

  case 69: /* line: base_cmd stmt_separator  */
#line 1076 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8191 "parser_bison.c"
    break;

  case 70: /* line: base_cmd "end of file"  */
#line 1078 "parser_bison.y"
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
#line 8213 "parser_bison.c"
    break;

  case 71: /* base_cmd: add_cmd  */
#line 1097 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8219 "parser_bison.c"
    break;

  case 72: /* base_cmd: "add" add_cmd  */
#line 1098 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8225 "parser_bison.c"
    break;

  case 73: /* base_cmd: "replace" replace_cmd  */
#line 1099 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8231 "parser_bison.c"
    break;

  case 74: /* base_cmd: "create" create_cmd  */
#line 1100 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8237 "parser_bison.c"
    break;

  case 75: /* base_cmd: "insert" insert_cmd  */
#line 1101 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8243 "parser_bison.c"
    break;

  case 76: /* base_cmd: "delete" delete_cmd  */
#line 1102 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8249 "parser_bison.c"
    break;

  case 77: /* base_cmd: "get" get_cmd  */
#line 1103 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8255 "parser_bison.c"
    break;

  case 78: /* base_cmd: "list" list_cmd close_scope_list  */
#line 1104 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8261 "parser_bison.c"
    break;

  case 79: /* base_cmd: "reset" reset_cmd close_scope_reset  */
#line 1105 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8267 "parser_bison.c"
    break;

  case 80: /* base_cmd: "flush" flush_cmd  */
#line 1106 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8273 "parser_bison.c"
    break;

  case 81: /* base_cmd: "rename" rename_cmd  */
#line 1107 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8279 "parser_bison.c"
    break;

  case 82: /* base_cmd: "import" import_cmd close_scope_import  */
#line 1108 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8285 "parser_bison.c"
    break;

  case 83: /* base_cmd: "export" export_cmd close_scope_export  */
#line 1109 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8291 "parser_bison.c"
    break;

  case 84: /* base_cmd: "monitor" monitor_cmd close_scope_monitor  */
#line 1110 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8297 "parser_bison.c"
    break;

  case 85: /* base_cmd: "describe" describe_cmd  */
#line 1111 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8303 "parser_bison.c"
    break;

  case 86: /* base_cmd: "destroy" destroy_cmd close_scope_destroy  */
#line 1112 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8309 "parser_bison.c"
    break;

  case 87: /* add_cmd: "table" table_spec  */
#line 1116 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8317 "parser_bison.c"
    break;

  case 88: /* add_cmd: "table" table_spec table_block_alloc '{' table_block '}'  */
#line 1121 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 8327 "parser_bison.c"
    break;

  case 89: /* add_cmd: "chain" chain_spec  */
#line 1127 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8335 "parser_bison.c"
    break;

  case 90: /* add_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1132 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 8346 "parser_bison.c"
    break;

  case 91: /* add_cmd: "rule" rule_position rule  */
#line 1139 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8354 "parser_bison.c"
    break;

  case 92: /* add_cmd: rule_position rule  */
#line 1143 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8362 "parser_bison.c"
    break;

  case 93: /* add_cmd: "set" set_spec set_block_alloc '{' set_block '}'  */
#line 1148 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8372 "parser_bison.c"
    break;

  case 94: /* add_cmd: "map" set_spec map_block_alloc '{' map_block '}'  */
#line 1155 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8382 "parser_bison.c"
    break;

  case 95: /* add_cmd: "element" set_spec set_block_expr  */
#line 1161 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8390 "parser_bison.c"
    break;

  case 96: /* add_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1166 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8400 "parser_bison.c"
    break;

  case 97: /* add_cmd: "counter" obj_spec close_scope_counter  */
#line 1172 "parser_bison.y"
                        {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 8413 "parser_bison.c"
    break;

  case 98: /* add_cmd: "counter" obj_spec counter_obj counter_config close_scope_counter  */
#line 1181 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8421 "parser_bison.c"
    break;

  case 99: /* add_cmd: "counter" obj_spec counter_obj '{' counter_block '}' close_scope_counter  */
#line 1185 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8429 "parser_bison.c"
    break;

  case 100: /* add_cmd: "quota" obj_spec quota_obj quota_config close_scope_quota  */
#line 1189 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8437 "parser_bison.c"
    break;

  case 101: /* add_cmd: "quota" obj_spec quota_obj '{' quota_block '}' close_scope_quota  */
#line 1193 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8445 "parser_bison.c"
    break;

  case 102: /* add_cmd: "ct" "helper" obj_spec ct_obj_alloc '{' ct_helper_block '}' close_scope_ct  */
#line 1197 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8453 "parser_bison.c"
    break;

  case 103: /* add_cmd: "ct" "timeout" obj_spec ct_obj_alloc '{' ct_timeout_block '}' close_scope_ct  */
#line 1201 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8461 "parser_bison.c"
    break;

  case 104: /* add_cmd: "ct" "expectation" obj_spec ct_obj_alloc '{' ct_expect_block '}' close_scope_ct  */
#line 1205 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8469 "parser_bison.c"
    break;

  case 105: /* add_cmd: "limit" obj_spec limit_obj limit_config close_scope_limit  */
#line 1209 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8477 "parser_bison.c"
    break;

  case 106: /* add_cmd: "limit" obj_spec limit_obj '{' limit_block '}' close_scope_limit  */
#line 1213 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8485 "parser_bison.c"
    break;

  case 107: /* add_cmd: "secmark" obj_spec secmark_obj secmark_config close_scope_secmark  */
#line 1217 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8493 "parser_bison.c"
    break;

  case 108: /* add_cmd: "secmark" obj_spec secmark_obj '{' secmark_block '}' close_scope_secmark  */
#line 1221 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8501 "parser_bison.c"
    break;

  case 109: /* add_cmd: "synproxy" obj_spec synproxy_obj synproxy_config close_scope_synproxy  */
#line 1225 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8509 "parser_bison.c"
    break;

  case 110: /* add_cmd: "synproxy" obj_spec synproxy_obj '{' synproxy_block '}' close_scope_synproxy  */
#line 1229 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8517 "parser_bison.c"
    break;

  case 111: /* replace_cmd: "rule" ruleid_spec rule  */
#line 1235 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8525 "parser_bison.c"
    break;

  case 112: /* create_cmd: "table" table_spec  */
#line 1241 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8533 "parser_bison.c"
    break;

  case 113: /* create_cmd: "table" table_spec table_block_alloc '{' table_block '}'  */
#line 1246 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 8543 "parser_bison.c"
    break;

  case 114: /* create_cmd: "chain" chain_spec  */
#line 1252 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8551 "parser_bison.c"
    break;

  case 115: /* create_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1257 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 8562 "parser_bison.c"
    break;

  case 116: /* create_cmd: "set" set_spec set_block_alloc '{' set_block '}'  */
#line 1265 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8572 "parser_bison.c"
    break;

  case 117: /* create_cmd: "map" set_spec map_block_alloc '{' map_block '}'  */
#line 1272 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8582 "parser_bison.c"
    break;

  case 118: /* create_cmd: "element" set_spec set_block_expr  */
#line 1278 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8590 "parser_bison.c"
    break;

  case 119: /* create_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1283 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8600 "parser_bison.c"
    break;

  case 120: /* create_cmd: "counter" obj_spec close_scope_counter  */
#line 1289 "parser_bison.y"
                        {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 8613 "parser_bison.c"
    break;

  case 121: /* create_cmd: "counter" obj_spec counter_obj counter_config close_scope_counter  */
#line 1298 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8621 "parser_bison.c"
    break;

  case 122: /* create_cmd: "quota" obj_spec quota_obj quota_config close_scope_quota  */
#line 1302 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8629 "parser_bison.c"
    break;

  case 123: /* create_cmd: "ct" "helper" obj_spec ct_obj_alloc '{' ct_helper_block '}' close_scope_ct  */
#line 1306 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8637 "parser_bison.c"
    break;

  case 124: /* create_cmd: "ct" "timeout" obj_spec ct_obj_alloc '{' ct_timeout_block '}' close_scope_ct  */
#line 1310 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8645 "parser_bison.c"
    break;

  case 125: /* create_cmd: "ct" "expectation" obj_spec ct_obj_alloc '{' ct_expect_block '}' close_scope_ct  */
#line 1314 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8653 "parser_bison.c"
    break;

  case 126: /* create_cmd: "limit" obj_spec limit_obj limit_config close_scope_limit  */
#line 1318 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8661 "parser_bison.c"
    break;

  case 127: /* create_cmd: "secmark" obj_spec secmark_obj secmark_config close_scope_secmark  */
#line 1322 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8669 "parser_bison.c"
    break;

  case 128: /* create_cmd: "synproxy" obj_spec synproxy_obj synproxy_config close_scope_synproxy  */
#line 1326 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8677 "parser_bison.c"
    break;

  case 129: /* insert_cmd: "rule" rule_position rule  */
#line 1332 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8685 "parser_bison.c"
    break;

  case 138: /* delete_cmd: "table" table_or_id_spec  */
#line 1354 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8693 "parser_bison.c"
    break;

  case 139: /* delete_cmd: "chain" chain_or_id_spec  */
#line 1358 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8701 "parser_bison.c"
    break;

  case 140: /* delete_cmd: "rule" ruleid_spec  */
#line 1362 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8709 "parser_bison.c"
    break;

  case 141: /* delete_cmd: "set" set_or_id_spec  */
#line 1366 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8717 "parser_bison.c"
    break;

  case 142: /* delete_cmd: "map" set_spec  */
#line 1370 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8725 "parser_bison.c"
    break;

  case 143: /* delete_cmd: "element" set_spec set_block_expr  */
#line 1374 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8733 "parser_bison.c"
    break;

  case 144: /* delete_cmd: "flowtable" flowtable_spec  */
#line 1378 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8741 "parser_bison.c"
    break;

  case 145: /* delete_cmd: "flowtable" flowtableid_spec  */
#line 1382 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8749 "parser_bison.c"
    break;

  case 146: /* delete_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1387 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8759 "parser_bison.c"
    break;

  case 147: /* delete_cmd: "counter" obj_or_id_spec close_scope_counter  */
#line 1393 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8767 "parser_bison.c"
    break;

  case 148: /* delete_cmd: "quota" obj_or_id_spec close_scope_quota  */
#line 1397 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8775 "parser_bison.c"
    break;

  case 149: /* delete_cmd: "ct" ct_obj_type obj_spec ct_obj_alloc close_scope_ct  */
#line 1401 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-3].val), &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
				if ((yyvsp[-3].val) == NFT_OBJECT_CT_TIMEOUT)
					init_list_head(&(yyvsp[-1].obj)->ct_timeout.timeout_list);
			}
#line 8785 "parser_bison.c"
    break;

  case 150: /* delete_cmd: "limit" obj_or_id_spec close_scope_limit  */
#line 1407 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8793 "parser_bison.c"
    break;

  case 151: /* delete_cmd: "secmark" obj_or_id_spec close_scope_secmark  */
#line 1411 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8801 "parser_bison.c"
    break;

  case 152: /* delete_cmd: "synproxy" obj_or_id_spec close_scope_synproxy  */
#line 1415 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8809 "parser_bison.c"
    break;

  case 153: /* destroy_cmd: "table" table_or_id_spec  */
#line 1421 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8817 "parser_bison.c"
    break;

  case 154: /* destroy_cmd: "chain" chain_or_id_spec  */
#line 1425 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8825 "parser_bison.c"
    break;

  case 155: /* destroy_cmd: "rule" ruleid_spec  */
#line 1429 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8833 "parser_bison.c"
    break;

  case 156: /* destroy_cmd: "set" set_or_id_spec  */
#line 1433 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8841 "parser_bison.c"
    break;

  case 157: /* destroy_cmd: "map" set_spec  */
#line 1437 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8849 "parser_bison.c"
    break;

  case 158: /* destroy_cmd: "element" set_spec set_block_expr  */
#line 1441 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8857 "parser_bison.c"
    break;

  case 159: /* destroy_cmd: "flowtable" flowtable_spec  */
#line 1445 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8865 "parser_bison.c"
    break;

  case 160: /* destroy_cmd: "flowtable" flowtableid_spec  */
#line 1449 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8873 "parser_bison.c"
    break;

  case 161: /* destroy_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1454 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8883 "parser_bison.c"
    break;

  case 162: /* destroy_cmd: "counter" obj_or_id_spec close_scope_counter  */
#line 1460 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8891 "parser_bison.c"
    break;

  case 163: /* destroy_cmd: "quota" obj_or_id_spec close_scope_quota  */
#line 1464 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8899 "parser_bison.c"
    break;

  case 164: /* destroy_cmd: "ct" ct_obj_type obj_spec ct_obj_alloc close_scope_ct  */
#line 1468 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DESTROY, (yyvsp[-3].val), &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
				if ((yyvsp[-3].val) == NFT_OBJECT_CT_TIMEOUT)
					init_list_head(&(yyvsp[-1].obj)->ct_timeout.timeout_list);
			}
#line 8909 "parser_bison.c"
    break;

  case 165: /* destroy_cmd: "limit" obj_or_id_spec close_scope_limit  */
#line 1474 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8917 "parser_bison.c"
    break;

  case 166: /* destroy_cmd: "secmark" obj_or_id_spec close_scope_secmark  */
#line 1478 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8925 "parser_bison.c"
    break;

  case 167: /* destroy_cmd: "synproxy" obj_or_id_spec close_scope_synproxy  */
#line 1482 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8933 "parser_bison.c"
    break;

  case 168: /* get_cmd: "element" set_spec set_block_expr  */
#line 1489 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8941 "parser_bison.c"
    break;

  case 169: /* list_cmd: "table" table_spec  */
#line 1495 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8949 "parser_bison.c"
    break;

  case 170: /* list_cmd: "tables" ruleset_spec  */
#line 1499 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8957 "parser_bison.c"
    break;

  case 171: /* list_cmd: "chain" chain_spec  */
#line 1503 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8965 "parser_bison.c"
    break;

  case 172: /* list_cmd: "chains" ruleset_spec  */
#line 1507 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8973 "parser_bison.c"
    break;

  case 173: /* list_cmd: "sets" ruleset_spec  */
#line 1511 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8981 "parser_bison.c"
    break;

  case 174: /* list_cmd: "sets" "table" table_spec  */
#line 1515 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8989 "parser_bison.c"
    break;

  case 175: /* list_cmd: "set" set_spec  */
#line 1519 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8997 "parser_bison.c"
    break;

  case 176: /* list_cmd: "counters" ruleset_spec  */
#line 1523 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9005 "parser_bison.c"
    break;

  case 177: /* list_cmd: "counters" "table" table_spec  */
#line 1527 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9013 "parser_bison.c"
    break;

  case 178: /* list_cmd: "counter" obj_spec close_scope_counter  */
#line 1531 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9021 "parser_bison.c"
    break;

  case 179: /* list_cmd: "quotas" ruleset_spec  */
#line 1535 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9029 "parser_bison.c"
    break;

  case 180: /* list_cmd: "quotas" "table" table_spec  */
#line 1539 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9037 "parser_bison.c"
    break;

  case 181: /* list_cmd: "quota" obj_spec close_scope_quota  */
#line 1543 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9045 "parser_bison.c"
    break;

  case 182: /* list_cmd: "limits" ruleset_spec  */
#line 1547 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9053 "parser_bison.c"
    break;

  case 183: /* list_cmd: "limits" "table" table_spec  */
#line 1551 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9061 "parser_bison.c"
    break;

  case 184: /* list_cmd: "limit" obj_spec close_scope_limit  */
#line 1555 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9069 "parser_bison.c"
    break;

  case 185: /* list_cmd: "secmarks" ruleset_spec  */
#line 1559 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9077 "parser_bison.c"
    break;

  case 186: /* list_cmd: "secmarks" "table" table_spec  */
#line 1563 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9085 "parser_bison.c"
    break;

  case 187: /* list_cmd: "secmark" obj_spec close_scope_secmark  */
#line 1567 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9093 "parser_bison.c"
    break;

  case 188: /* list_cmd: "synproxys" ruleset_spec  */
#line 1571 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9101 "parser_bison.c"
    break;

  case 189: /* list_cmd: "synproxys" "table" table_spec  */
#line 1575 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9109 "parser_bison.c"
    break;

  case 190: /* list_cmd: "synproxy" obj_spec close_scope_synproxy  */
#line 1579 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9117 "parser_bison.c"
    break;

  case 191: /* list_cmd: "ruleset" ruleset_spec  */
#line 1583 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9125 "parser_bison.c"
    break;

  case 192: /* list_cmd: "flow" "tables" ruleset_spec  */
#line 1587 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9133 "parser_bison.c"
    break;

  case 193: /* list_cmd: "flow" "table" set_spec  */
#line 1591 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9141 "parser_bison.c"
    break;

  case 194: /* list_cmd: "meters" ruleset_spec  */
#line 1595 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9149 "parser_bison.c"
    break;

  case 195: /* list_cmd: "meter" set_spec  */
#line 1599 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9157 "parser_bison.c"
    break;

  case 196: /* list_cmd: "flowtables" ruleset_spec  */
#line 1603 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9165 "parser_bison.c"
    break;

  case 197: /* list_cmd: "flowtable" flowtable_spec  */
#line 1607 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9173 "parser_bison.c"
    break;

  case 198: /* list_cmd: "maps" ruleset_spec  */
#line 1611 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9181 "parser_bison.c"
    break;

  case 199: /* list_cmd: "map" set_spec  */
#line 1615 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9189 "parser_bison.c"
    break;

  case 200: /* list_cmd: "ct" ct_obj_type obj_spec close_scope_ct  */
#line 1619 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9197 "parser_bison.c"
    break;

  case 201: /* list_cmd: "ct" ct_cmd_type "table" table_spec close_scope_ct  */
#line 1623 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, (yyvsp[-3].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9205 "parser_bison.c"
    break;

  case 202: /* list_cmd: "hooks" basehook_spec  */
#line 1627 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_HOOKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9213 "parser_bison.c"
    break;

  case 203: /* basehook_device_name: "device" "string"  */
#line 1633 "parser_bison.y"
                        {
				(yyval.string) = (yyvsp[0].string);
			}
#line 9221 "parser_bison.c"
    break;

  case 204: /* basehook_spec: ruleset_spec  */
#line 1639 "parser_bison.y"
                        {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 9229 "parser_bison.c"
    break;

  case 205: /* basehook_spec: ruleset_spec basehook_device_name  */
#line 1643 "parser_bison.y"
                        {
				if ((yyvsp[0].string)) {
					(yyvsp[-1].handle).obj.name = (yyvsp[0].string);
					(yyvsp[-1].handle).obj.location = (yylsp[0]);
				}
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9241 "parser_bison.c"
    break;

  case 206: /* reset_cmd: "counters" ruleset_spec  */
#line 1653 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9249 "parser_bison.c"
    break;

  case 207: /* reset_cmd: "counters" "table" table_spec  */
#line 1657 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9257 "parser_bison.c"
    break;

  case 208: /* reset_cmd: "counter" obj_spec close_scope_counter  */
#line 1661 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[-1].handle),&(yyloc), NULL);
			}
#line 9265 "parser_bison.c"
    break;

  case 209: /* reset_cmd: "quotas" ruleset_spec  */
#line 1665 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9273 "parser_bison.c"
    break;

  case 210: /* reset_cmd: "quotas" "table" table_spec  */
#line 1669 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9281 "parser_bison.c"
    break;

  case 211: /* reset_cmd: "quota" obj_spec close_scope_quota  */
#line 1673 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9289 "parser_bison.c"
    break;

  case 212: /* reset_cmd: "rules" ruleset_spec  */
#line 1677 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9297 "parser_bison.c"
    break;

  case 213: /* reset_cmd: "rules" "table" table_spec  */
#line 1681 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9305 "parser_bison.c"
    break;

  case 214: /* reset_cmd: "rules" "chain" chain_spec  */
#line 1685 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9313 "parser_bison.c"
    break;

  case 215: /* reset_cmd: "rule" ruleid_spec  */
#line 1689 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9321 "parser_bison.c"
    break;

  case 216: /* flush_cmd: "table" table_spec  */
#line 1695 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9329 "parser_bison.c"
    break;

  case 217: /* flush_cmd: "chain" chain_spec  */
#line 1699 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9337 "parser_bison.c"
    break;

  case 218: /* flush_cmd: "set" set_spec  */
#line 1703 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9345 "parser_bison.c"
    break;

  case 219: /* flush_cmd: "map" set_spec  */
#line 1707 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9353 "parser_bison.c"
    break;

  case 220: /* flush_cmd: "flow" "table" set_spec  */
#line 1711 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9361 "parser_bison.c"
    break;

  case 221: /* flush_cmd: "meter" set_spec  */
#line 1715 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9369 "parser_bison.c"
    break;

  case 222: /* flush_cmd: "ruleset" ruleset_spec  */
#line 1719 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9377 "parser_bison.c"
    break;

  case 223: /* rename_cmd: "chain" chain_spec identifier  */
#line 1725 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 9386 "parser_bison.c"
    break;

  case 224: /* import_cmd: "ruleset" markup_format  */
#line 1732 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9396 "parser_bison.c"
    break;

  case 225: /* import_cmd: markup_format  */
#line 1738 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9406 "parser_bison.c"
    break;

  case 226: /* export_cmd: "ruleset" markup_format  */
#line 1746 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9416 "parser_bison.c"
    break;

  case 227: /* export_cmd: markup_format  */
#line 1752 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9426 "parser_bison.c"
    break;

  case 228: /* monitor_cmd: monitor_event monitor_object monitor_format  */
#line 1760 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 9437 "parser_bison.c"
    break;

  case 229: /* monitor_event: %empty  */
#line 1768 "parser_bison.y"
                                                { (yyval.string) = NULL; }
#line 9443 "parser_bison.c"
    break;

  case 230: /* monitor_event: "string"  */
#line 1769 "parser_bison.y"
                                                { (yyval.string) = (yyvsp[0].string); }
#line 9449 "parser_bison.c"
    break;

  case 231: /* monitor_object: %empty  */
#line 1772 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 9455 "parser_bison.c"
    break;

  case 232: /* monitor_object: "tables"  */
#line 1773 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 9461 "parser_bison.c"
    break;

  case 233: /* monitor_object: "chains"  */
#line 1774 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 9467 "parser_bison.c"
    break;

  case 234: /* monitor_object: "sets"  */
#line 1775 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 9473 "parser_bison.c"
    break;

  case 235: /* monitor_object: "rules"  */
#line 1776 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 9479 "parser_bison.c"
    break;

  case 236: /* monitor_object: "elements"  */
#line 1777 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 9485 "parser_bison.c"
    break;

  case 237: /* monitor_object: "ruleset"  */
#line 1778 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 9491 "parser_bison.c"
    break;

  case 238: /* monitor_object: "trace"  */
#line 1779 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 9497 "parser_bison.c"
    break;

  case 239: /* monitor_format: %empty  */
#line 1782 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 9503 "parser_bison.c"
    break;

  case 241: /* markup_format: "xml"  */
#line 1786 "parser_bison.y"
                                                { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 9509 "parser_bison.c"
    break;

  case 242: /* markup_format: "json"  */
#line 1787 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 9515 "parser_bison.c"
    break;

  case 243: /* markup_format: "vm" "json"  */
#line 1788 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 9521 "parser_bison.c"
    break;

  case 244: /* describe_cmd: primary_expr  */
#line 1792 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 9531 "parser_bison.c"
    break;

  case 245: /* table_block_alloc: %empty  */
#line 1800 "parser_bison.y"
                        {
				(yyval.table) = table_alloc();
				if (open_scope(state, &(yyval.table)->scope) < 0) {
					erec_queue(error(&(yyloc), "too many levels of nesting"),
						   state->msgs);
					state->nerrs++;
				}
			}
#line 9544 "parser_bison.c"
    break;

  case 246: /* table_options: "flags" "string"  */
#line 1811 "parser_bison.y"
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
#line 9563 "parser_bison.c"
    break;

  case 247: /* table_options: comment_spec  */
#line 1826 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].table)->comment, &(yyloc), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].table)->comment = (yyvsp[0].string);
			}
#line 9575 "parser_bison.c"
    break;

  case 248: /* table_block: %empty  */
#line 1835 "parser_bison.y"
                                                { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 9581 "parser_bison.c"
    break;

  case 252: /* table_block: table_block "chain" chain_identifier chain_block_alloc '{' chain_block '}' stmt_separator  */
#line 1842 "parser_bison.y"
                        {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9594 "parser_bison.c"
    break;

  case 253: /* table_block: table_block "set" set_identifier set_block_alloc '{' set_block '}' stmt_separator  */
#line 1853 "parser_bison.y"
                        {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9606 "parser_bison.c"
    break;

  case 254: /* table_block: table_block "map" set_identifier map_block_alloc '{' map_block '}' stmt_separator  */
#line 1863 "parser_bison.y"
                        {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9618 "parser_bison.c"
    break;

  case 255: /* table_block: table_block "flowtable" flowtable_identifier flowtable_block_alloc '{' flowtable_block '}' stmt_separator  */
#line 1874 "parser_bison.y"
                        {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9630 "parser_bison.c"
    break;

  case 256: /* table_block: table_block "counter" obj_identifier obj_block_alloc '{' counter_block '}' stmt_separator close_scope_counter  */
#line 1884 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9643 "parser_bison.c"
    break;

  case 257: /* table_block: table_block "quota" obj_identifier obj_block_alloc '{' quota_block '}' stmt_separator close_scope_quota  */
#line 1895 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9656 "parser_bison.c"
    break;

  case 258: /* table_block: table_block "ct" "helper" obj_identifier obj_block_alloc '{' ct_helper_block '}' close_scope_ct stmt_separator  */
#line 1904 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9669 "parser_bison.c"
    break;

  case 259: /* table_block: table_block "ct" "timeout" obj_identifier obj_block_alloc '{' ct_timeout_block '}' close_scope_ct stmt_separator  */
#line 1913 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9682 "parser_bison.c"
    break;

  case 260: /* table_block: table_block "ct" "expectation" obj_identifier obj_block_alloc '{' ct_expect_block '}' close_scope_ct stmt_separator  */
#line 1922 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9695 "parser_bison.c"
    break;

  case 261: /* table_block: table_block "limit" obj_identifier obj_block_alloc '{' limit_block '}' stmt_separator close_scope_limit  */
#line 1933 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9708 "parser_bison.c"
    break;

  case 262: /* table_block: table_block "secmark" obj_identifier obj_block_alloc '{' secmark_block '}' stmt_separator close_scope_secmark  */
#line 1944 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9721 "parser_bison.c"
    break;

  case 263: /* table_block: table_block "synproxy" obj_identifier obj_block_alloc '{' synproxy_block '}' stmt_separator close_scope_synproxy  */
#line 1955 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9734 "parser_bison.c"
    break;

  case 264: /* chain_block_alloc: %empty  */
#line 1966 "parser_bison.y"
                        {
				(yyval.chain) = chain_alloc(NULL);
				if (open_scope(state, &(yyval.chain)->scope) < 0) {
					erec_queue(error(&(yyloc), "too many levels of nesting"),
						   state->msgs);
					state->nerrs++;
				}
			}
#line 9747 "parser_bison.c"
    break;

  case 265: /* chain_block: %empty  */
#line 1976 "parser_bison.y"
                                                { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 9753 "parser_bison.c"
    break;

  case 271: /* chain_block: chain_block rule stmt_separator  */
#line 1983 "parser_bison.y"
                        {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 9762 "parser_bison.c"
    break;

  case 272: /* chain_block: chain_block comment_spec stmt_separator  */
#line 1988 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].chain)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].chain)->comment = (yyvsp[-1].string);
			}
#line 9774 "parser_bison.c"
    break;

  case 273: /* subchain_block: %empty  */
#line 1997 "parser_bison.y"
                                                { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 9780 "parser_bison.c"
    break;

  case 275: /* subchain_block: subchain_block rule stmt_separator  */
#line 2000 "parser_bison.y"
                        {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 9789 "parser_bison.c"
    break;

  case 276: /* typeof_data_expr: primary_expr  */
#line 2007 "parser_bison.y"
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
#line 9814 "parser_bison.c"
    break;

  case 277: /* typeof_data_expr: typeof_expr "." primary_expr  */
#line 2028 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 9827 "parser_bison.c"
    break;

  case 278: /* typeof_expr: primary_expr  */
#line 2039 "parser_bison.y"
                        {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 9842 "parser_bison.c"
    break;

  case 279: /* typeof_expr: typeof_expr "." primary_expr  */
#line 2050 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 9855 "parser_bison.c"
    break;

  case 280: /* set_block_alloc: %empty  */
#line 2062 "parser_bison.y"
                        {
				(yyval.set) = set_alloc(NULL);
			}
#line 9863 "parser_bison.c"
    break;

  case 281: /* set_block: %empty  */
#line 2067 "parser_bison.y"
                                                { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 9869 "parser_bison.c"
    break;

  case 284: /* set_block: set_block "type" data_type_expr stmt_separator close_scope_type  */
#line 2071 "parser_bison.y"
                        {
				(yyvsp[-4].set)->key = (yyvsp[-2].expr);
				(yyval.set) = (yyvsp[-4].set);
			}
#line 9878 "parser_bison.c"
    break;

  case 285: /* set_block: set_block "typeof" typeof_expr stmt_separator  */
#line 2076 "parser_bison.y"
                        {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9888 "parser_bison.c"
    break;

  case 286: /* set_block: set_block "flags" set_flag_list stmt_separator  */
#line 2082 "parser_bison.y"
                        {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9897 "parser_bison.c"
    break;

  case 287: /* set_block: set_block "timeout" time_spec stmt_separator  */
#line 2087 "parser_bison.y"
                        {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9906 "parser_bison.c"
    break;

  case 288: /* set_block: set_block "gc-interval" time_spec stmt_separator  */
#line 2092 "parser_bison.y"
                        {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9915 "parser_bison.c"
    break;

  case 289: /* set_block: set_block stateful_stmt_list stmt_separator  */
#line 2097 "parser_bison.y"
                        {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 9925 "parser_bison.c"
    break;

  case 290: /* set_block: set_block "elements" '=' set_block_expr  */
#line 2103 "parser_bison.y"
                        {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9934 "parser_bison.c"
    break;

  case 291: /* set_block: set_block "auto-merge"  */
#line 2108 "parser_bison.y"
                        {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 9943 "parser_bison.c"
    break;

  case 293: /* set_block: set_block comment_spec stmt_separator  */
#line 2114 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 9956 "parser_bison.c"
    break;

  case 296: /* set_flag_list: set_flag_list "comma" set_flag  */
#line 2129 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9964 "parser_bison.c"
    break;

  case 298: /* set_flag: "constant"  */
#line 2135 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_CONSTANT; }
#line 9970 "parser_bison.c"
    break;

  case 299: /* set_flag: "interval"  */
#line 2136 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_INTERVAL; }
#line 9976 "parser_bison.c"
    break;

  case 300: /* set_flag: "timeout"  */
#line 2137 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_TIMEOUT; }
#line 9982 "parser_bison.c"
    break;

  case 301: /* set_flag: "dynamic"  */
#line 2138 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_EVAL; }
#line 9988 "parser_bison.c"
    break;

  case 302: /* map_block_alloc: %empty  */
#line 2142 "parser_bison.y"
                        {
				(yyval.set) = set_alloc(NULL);
			}
#line 9996 "parser_bison.c"
    break;

  case 303: /* map_block_obj_type: "counter" close_scope_counter  */
#line 2147 "parser_bison.y"
                                                            { (yyval.val) = NFT_OBJECT_COUNTER; }
#line 10002 "parser_bison.c"
    break;

  case 304: /* map_block_obj_type: "quota" close_scope_quota  */
#line 2148 "parser_bison.y"
                                                          { (yyval.val) = NFT_OBJECT_QUOTA; }
#line 10008 "parser_bison.c"
    break;

  case 305: /* map_block_obj_type: "limit" close_scope_limit  */
#line 2149 "parser_bison.y"
                                                          { (yyval.val) = NFT_OBJECT_LIMIT; }
#line 10014 "parser_bison.c"
    break;

  case 306: /* map_block_obj_type: "secmark" close_scope_secmark  */
#line 2150 "parser_bison.y"
                                                            { (yyval.val) = NFT_OBJECT_SECMARK; }
#line 10020 "parser_bison.c"
    break;

  case 307: /* map_block_obj_type: "synproxy" close_scope_synproxy  */
#line 2151 "parser_bison.y"
                                                              { (yyval.val) = NFT_OBJECT_SYNPROXY; }
#line 10026 "parser_bison.c"
    break;

  case 308: /* map_block: %empty  */
#line 2154 "parser_bison.y"
                                                { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 10032 "parser_bison.c"
    break;

  case 311: /* map_block: map_block "timeout" time_spec stmt_separator  */
#line 2158 "parser_bison.y"
                        {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10041 "parser_bison.c"
    break;

  case 312: /* map_block: map_block "type" data_type_expr "colon" data_type_expr stmt_separator close_scope_type  */
#line 2165 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->data = (yyvsp[-2].expr);

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 10053 "parser_bison.c"
    break;

  case 313: /* map_block: map_block "type" data_type_expr "colon" "interval" data_type_expr stmt_separator close_scope_type  */
#line 2175 "parser_bison.y"
                        {
				(yyvsp[-7].set)->key = (yyvsp[-5].expr);
				(yyvsp[-7].set)->data = (yyvsp[-2].expr);
				(yyvsp[-7].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-7].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-7].set);
			}
#line 10066 "parser_bison.c"
    break;

  case 314: /* map_block: map_block "typeof" typeof_expr "colon" typeof_data_expr stmt_separator  */
#line 2186 "parser_bison.y"
                        {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 10079 "parser_bison.c"
    break;

  case 315: /* map_block: map_block "typeof" typeof_expr "colon" "interval" typeof_expr stmt_separator  */
#line 2197 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				datatype_set((yyvsp[-6].set)->key, (yyvsp[-4].expr)->dtype);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 10093 "parser_bison.c"
    break;

  case 316: /* map_block: map_block "type" data_type_expr "colon" map_block_obj_type stmt_separator close_scope_type  */
#line 2209 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->objtype = (yyvsp[-2].val);
				(yyvsp[-6].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 10104 "parser_bison.c"
    break;

  case 317: /* map_block: map_block "flags" set_flag_list stmt_separator  */
#line 2216 "parser_bison.y"
                        {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10113 "parser_bison.c"
    break;

  case 318: /* map_block: map_block stateful_stmt_list stmt_separator  */
#line 2221 "parser_bison.y"
                        {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 10123 "parser_bison.c"
    break;

  case 319: /* map_block: map_block "elements" '=' set_block_expr  */
#line 2227 "parser_bison.y"
                        {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10132 "parser_bison.c"
    break;

  case 320: /* map_block: map_block comment_spec stmt_separator  */
#line 2232 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 10145 "parser_bison.c"
    break;

  case 322: /* set_mechanism: "policy" set_policy_spec close_scope_policy  */
#line 2244 "parser_bison.y"
                        {
				(yyvsp[-3].set)->policy = (yyvsp[-1].val);
			}
#line 10153 "parser_bison.c"
    break;

  case 323: /* set_mechanism: "size" "number"  */
#line 2248 "parser_bison.y"
                        {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 10161 "parser_bison.c"
    break;

  case 324: /* set_policy_spec: "performance"  */
#line 2253 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 10167 "parser_bison.c"
    break;

  case 325: /* set_policy_spec: "memory"  */
#line 2254 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 10173 "parser_bison.c"
    break;

  case 326: /* flowtable_block_alloc: %empty  */
#line 2258 "parser_bison.y"
                        {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 10181 "parser_bison.c"
    break;

  case 327: /* flowtable_block: %empty  */
#line 2263 "parser_bison.y"
                                                { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 10187 "parser_bison.c"
    break;

  case 330: /* flowtable_block: flowtable_block "hook" "string" prio_spec stmt_separator  */
#line 2267 "parser_bison.y"
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
#line 10205 "parser_bison.c"
    break;

  case 331: /* flowtable_block: flowtable_block "devices" '=' flowtable_expr stmt_separator  */
#line 2281 "parser_bison.y"
                        {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 10213 "parser_bison.c"
    break;

  case 332: /* flowtable_block: flowtable_block "counter" close_scope_counter  */
#line 2285 "parser_bison.y"
                        {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 10221 "parser_bison.c"
    break;

  case 333: /* flowtable_block: flowtable_block "flags" "offload" stmt_separator  */
#line 2289 "parser_bison.y"
                        {
				(yyval.flowtable)->flags |= FLOWTABLE_F_HW_OFFLOAD;
			}
#line 10229 "parser_bison.c"
    break;

  case 334: /* flowtable_expr: '{' flowtable_list_expr '}'  */
#line 2295 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10238 "parser_bison.c"
    break;

  case 335: /* flowtable_expr: variable_expr  */
#line 2300 "parser_bison.y"
                        {
				(yyvsp[0].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10247 "parser_bison.c"
    break;

  case 336: /* flowtable_list_expr: flowtable_expr_member  */
#line 2307 "parser_bison.y"
                        {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10256 "parser_bison.c"
    break;

  case 337: /* flowtable_list_expr: flowtable_list_expr "comma" flowtable_expr_member  */
#line 2312 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10265 "parser_bison.c"
    break;

  case 339: /* flowtable_expr_member: "quoted string"  */
#line 2320 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10276 "parser_bison.c"
    break;

  case 340: /* flowtable_expr_member: "string"  */
#line 2327 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10287 "parser_bison.c"
    break;

  case 341: /* flowtable_expr_member: variable_expr  */
#line 2334 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10296 "parser_bison.c"
    break;

  case 342: /* data_type_atom_expr: type_identifier  */
#line 2341 "parser_bison.y"
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
#line 10313 "parser_bison.c"
    break;

  case 343: /* data_type_atom_expr: "time"  */
#line 2354 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 10322 "parser_bison.c"
    break;

  case 345: /* data_type_expr: data_type_expr "." data_type_atom_expr  */
#line 2362 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10335 "parser_bison.c"
    break;

  case 346: /* obj_block_alloc: %empty  */
#line 2373 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 10343 "parser_bison.c"
    break;

  case 347: /* counter_block: %empty  */
#line 2378 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10349 "parser_bison.c"
    break;

  case 350: /* counter_block: counter_block counter_config  */
#line 2382 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10357 "parser_bison.c"
    break;

  case 351: /* counter_block: counter_block comment_spec  */
#line 2386 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10369 "parser_bison.c"
    break;

  case 352: /* quota_block: %empty  */
#line 2395 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10375 "parser_bison.c"
    break;

  case 355: /* quota_block: quota_block quota_config  */
#line 2399 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10383 "parser_bison.c"
    break;

  case 356: /* quota_block: quota_block comment_spec  */
#line 2403 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10395 "parser_bison.c"
    break;

  case 357: /* ct_helper_block: %empty  */
#line 2412 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10401 "parser_bison.c"
    break;

  case 360: /* ct_helper_block: ct_helper_block ct_helper_config  */
#line 2416 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10409 "parser_bison.c"
    break;

  case 361: /* ct_helper_block: ct_helper_block comment_spec  */
#line 2420 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10421 "parser_bison.c"
    break;

  case 362: /* ct_timeout_block: %empty  */
#line 2430 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[(-1) - (0)].obj);
				init_list_head(&(yyval.obj)->ct_timeout.timeout_list);
			}
#line 10430 "parser_bison.c"
    break;

  case 365: /* ct_timeout_block: ct_timeout_block ct_timeout_config  */
#line 2437 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10438 "parser_bison.c"
    break;

  case 366: /* ct_timeout_block: ct_timeout_block comment_spec  */
#line 2441 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10450 "parser_bison.c"
    break;

  case 367: /* ct_expect_block: %empty  */
#line 2450 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10456 "parser_bison.c"
    break;

  case 370: /* ct_expect_block: ct_expect_block ct_expect_config  */
#line 2454 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10464 "parser_bison.c"
    break;

  case 371: /* ct_expect_block: ct_expect_block comment_spec  */
#line 2458 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10476 "parser_bison.c"
    break;

  case 372: /* limit_block: %empty  */
#line 2467 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10482 "parser_bison.c"
    break;

  case 375: /* limit_block: limit_block limit_config  */
#line 2471 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10490 "parser_bison.c"
    break;

  case 376: /* limit_block: limit_block comment_spec  */
#line 2475 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10502 "parser_bison.c"
    break;

  case 377: /* secmark_block: %empty  */
#line 2484 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10508 "parser_bison.c"
    break;

  case 380: /* secmark_block: secmark_block secmark_config  */
#line 2488 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10516 "parser_bison.c"
    break;

  case 381: /* secmark_block: secmark_block comment_spec  */
#line 2492 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10528 "parser_bison.c"
    break;

  case 382: /* synproxy_block: %empty  */
#line 2501 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10534 "parser_bison.c"
    break;

  case 385: /* synproxy_block: synproxy_block synproxy_config  */
#line 2505 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10542 "parser_bison.c"
    break;

  case 386: /* synproxy_block: synproxy_block comment_spec  */
#line 2509 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10554 "parser_bison.c"
    break;

  case 387: /* type_identifier: "string"  */
#line 2518 "parser_bison.y"
                                        { (yyval.string) = (yyvsp[0].string); }
#line 10560 "parser_bison.c"
    break;

  case 388: /* type_identifier: "mark"  */
#line 2519 "parser_bison.y"
                                        { (yyval.string) = xstrdup("mark"); }
#line 10566 "parser_bison.c"
    break;

  case 389: /* type_identifier: "dscp"  */
#line 2520 "parser_bison.y"
                                        { (yyval.string) = xstrdup("dscp"); }
#line 10572 "parser_bison.c"
    break;

  case 390: /* type_identifier: "ecn"  */
#line 2521 "parser_bison.y"
                                        { (yyval.string) = xstrdup("ecn"); }
#line 10578 "parser_bison.c"
    break;

  case 391: /* type_identifier: "classid"  */
#line 2522 "parser_bison.y"
                                        { (yyval.string) = xstrdup("classid"); }
#line 10584 "parser_bison.c"
    break;

  case 392: /* hook_spec: "type" close_scope_type "string" "hook" "string" dev_spec prio_spec  */
#line 2526 "parser_bison.y"
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
#line 10617 "parser_bison.c"
    break;

  case 393: /* prio_spec: "priority" extended_prio_spec  */
#line 2557 "parser_bison.y"
                        {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 10626 "parser_bison.c"
    break;

  case 394: /* extended_prio_name: "out"  */
#line 2564 "parser_bison.y"
                        {
				(yyval.string) = strdup("out");
			}
#line 10634 "parser_bison.c"
    break;

  case 396: /* extended_prio_spec: int_num  */
#line 2571 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 10648 "parser_bison.c"
    break;

  case 397: /* extended_prio_spec: variable_expr  */
#line 2581 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 10659 "parser_bison.c"
    break;

  case 398: /* extended_prio_spec: extended_prio_name  */
#line 2588 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 10674 "parser_bison.c"
    break;

  case 399: /* extended_prio_spec: extended_prio_name "+" "number"  */
#line 2599 "parser_bison.y"
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
#line 10691 "parser_bison.c"
    break;

  case 400: /* extended_prio_spec: extended_prio_name "-" "number"  */
#line 2612 "parser_bison.y"
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
#line 10708 "parser_bison.c"
    break;

  case 401: /* int_num: "number"  */
#line 2626 "parser_bison.y"
                                                        { (yyval.val32) = (yyvsp[0].val); }
#line 10714 "parser_bison.c"
    break;

  case 402: /* int_num: "-" "number"  */
#line 2627 "parser_bison.y"
                                                        { (yyval.val32) = -(yyvsp[0].val); }
#line 10720 "parser_bison.c"
    break;

  case 403: /* dev_spec: "device" string  */
#line 2631 "parser_bison.y"
                        {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 10736 "parser_bison.c"
    break;

  case 404: /* dev_spec: "device" variable_expr  */
#line 2643 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10746 "parser_bison.c"
    break;

  case 405: /* dev_spec: "devices" '=' flowtable_expr  */
#line 2649 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10754 "parser_bison.c"
    break;

  case 406: /* dev_spec: %empty  */
#line 2652 "parser_bison.y"
                                                        { (yyval.expr) = NULL; }
#line 10760 "parser_bison.c"
    break;

  case 407: /* flags_spec: "flags" "offload"  */
#line 2656 "parser_bison.y"
                        {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 10768 "parser_bison.c"
    break;

  case 408: /* policy_spec: "policy" policy_expr close_scope_policy  */
#line 2662 "parser_bison.y"
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
#line 10783 "parser_bison.c"
    break;

  case 409: /* policy_expr: variable_expr  */
#line 2675 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10792 "parser_bison.c"
    break;

  case 410: /* policy_expr: chain_policy  */
#line 2680 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 10803 "parser_bison.c"
    break;

  case 411: /* chain_policy: "accept"  */
#line 2688 "parser_bison.y"
                                                { (yyval.val32) = NF_ACCEPT; }
#line 10809 "parser_bison.c"
    break;

  case 412: /* chain_policy: "drop"  */
#line 2689 "parser_bison.y"
                                                { (yyval.val32) = NF_DROP;   }
#line 10815 "parser_bison.c"
    break;

  case 414: /* identifier: "last"  */
#line 2693 "parser_bison.y"
                                                { (yyval.string) = xstrdup("last"); }
#line 10821 "parser_bison.c"
    break;

  case 418: /* time_spec: "string"  */
#line 2702 "parser_bison.y"
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
#line 10838 "parser_bison.c"
    break;

  case 419: /* family_spec: %empty  */
#line 2716 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV4; }
#line 10844 "parser_bison.c"
    break;

  case 421: /* family_spec_explicit: "ip" close_scope_ip  */
#line 2720 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV4; }
#line 10850 "parser_bison.c"
    break;

  case 422: /* family_spec_explicit: "ip6" close_scope_ip6  */
#line 2721 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV6; }
#line 10856 "parser_bison.c"
    break;

  case 423: /* family_spec_explicit: "inet"  */
#line 2722 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_INET; }
#line 10862 "parser_bison.c"
    break;

  case 424: /* family_spec_explicit: "arp" close_scope_arp  */
#line 2723 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_ARP; }
#line 10868 "parser_bison.c"
    break;

  case 425: /* family_spec_explicit: "bridge"  */
#line 2724 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_BRIDGE; }
#line 10874 "parser_bison.c"
    break;

  case 426: /* family_spec_explicit: "netdev"  */
#line 2725 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_NETDEV; }
#line 10880 "parser_bison.c"
    break;

  case 427: /* table_spec: family_spec identifier  */
#line 2729 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 10891 "parser_bison.c"
    break;

  case 428: /* tableid_spec: family_spec "handle" "number"  */
#line 2738 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 10902 "parser_bison.c"
    break;

  case 429: /* chain_spec: table_spec identifier  */
#line 2747 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 10912 "parser_bison.c"
    break;

  case 430: /* chainid_spec: table_spec "handle" "number"  */
#line 2755 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 10922 "parser_bison.c"
    break;

  case 431: /* chain_identifier: identifier  */
#line 2763 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 10932 "parser_bison.c"
    break;

  case 432: /* set_spec: table_spec identifier  */
#line 2771 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 10942 "parser_bison.c"
    break;

  case 433: /* setid_spec: table_spec "handle" "number"  */
#line 2779 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 10952 "parser_bison.c"
    break;

  case 434: /* set_identifier: identifier  */
#line 2787 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 10962 "parser_bison.c"
    break;

  case 435: /* flowtable_spec: table_spec identifier  */
#line 2795 "parser_bison.y"
                        {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 10972 "parser_bison.c"
    break;

  case 436: /* flowtableid_spec: table_spec "handle" "number"  */
#line 2803 "parser_bison.y"
                        {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 10982 "parser_bison.c"
    break;

  case 437: /* flowtable_identifier: identifier  */
#line 2811 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 10992 "parser_bison.c"
    break;

  case 438: /* obj_spec: table_spec identifier  */
#line 2819 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 11002 "parser_bison.c"
    break;

  case 439: /* objid_spec: table_spec "handle" "number"  */
#line 2827 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 11012 "parser_bison.c"
    break;

  case 440: /* obj_identifier: identifier  */
#line 2835 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 11022 "parser_bison.c"
    break;

  case 441: /* handle_spec: "handle" "number"  */
#line 2843 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 11032 "parser_bison.c"
    break;

  case 442: /* position_spec: "position" "number"  */
#line 2851 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 11042 "parser_bison.c"
    break;

  case 443: /* index_spec: "index" "number"  */
#line 2859 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 11052 "parser_bison.c"
    break;

  case 444: /* rule_position: chain_spec  */
#line 2867 "parser_bison.y"
                        {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 11060 "parser_bison.c"
    break;

  case 445: /* rule_position: chain_spec position_spec  */
#line 2871 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11069 "parser_bison.c"
    break;

  case 446: /* rule_position: chain_spec handle_spec  */
#line 2876 "parser_bison.y"
                        {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11081 "parser_bison.c"
    break;

  case 447: /* rule_position: chain_spec index_spec  */
#line 2884 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11090 "parser_bison.c"
    break;

  case 448: /* ruleid_spec: chain_spec handle_spec  */
#line 2891 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11099 "parser_bison.c"
    break;

  case 449: /* comment_spec: "comment" string  */
#line 2898 "parser_bison.y"
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
#line 11114 "parser_bison.c"
    break;

  case 450: /* ruleset_spec: %empty  */
#line 2911 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 11123 "parser_bison.c"
    break;

  case 451: /* ruleset_spec: family_spec_explicit  */
#line 2916 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 11132 "parser_bison.c"
    break;

  case 452: /* rule: rule_alloc  */
#line 2923 "parser_bison.y"
                        {
				(yyval.rule)->comment = NULL;
			}
#line 11140 "parser_bison.c"
    break;

  case 453: /* rule: rule_alloc comment_spec  */
#line 2927 "parser_bison.y"
                        {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 11148 "parser_bison.c"
    break;

  case 454: /* rule_alloc: stmt_list  */
#line 2933 "parser_bison.y"
                        {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 11162 "parser_bison.c"
    break;

  case 455: /* stmt_list: stmt  */
#line 2945 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 11172 "parser_bison.c"
    break;

  case 456: /* stmt_list: stmt_list stmt  */
#line 2951 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 11181 "parser_bison.c"
    break;

  case 457: /* stateful_stmt_list: stateful_stmt  */
#line 2958 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 11191 "parser_bison.c"
    break;

  case 458: /* stateful_stmt_list: stateful_stmt_list stateful_stmt  */
#line 2964 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 11200 "parser_bison.c"
    break;

  case 486: /* xt_stmt: "xt" "string" string  */
#line 3002 "parser_bison.y"
                        {
				(yyval.stmt) = NULL;
				xfree((yyvsp[-1].string));
				xfree((yyvsp[0].string));
				erec_queue(error(&(yyloc), "unsupported xtables compat expression, use iptables-nft with this ruleset"),
					   state->msgs);
				YYERROR;
			}
#line 11213 "parser_bison.c"
    break;

  case 487: /* chain_stmt_type: "jump"  */
#line 3012 "parser_bison.y"
                                        { (yyval.val) = NFT_JUMP; }
#line 11219 "parser_bison.c"
    break;

  case 488: /* chain_stmt_type: "goto"  */
#line 3013 "parser_bison.y"
                                        { (yyval.val) = NFT_GOTO; }
#line 11225 "parser_bison.c"
    break;

  case 489: /* chain_stmt: chain_stmt_type chain_block_alloc '{' subchain_block '}'  */
#line 3017 "parser_bison.y"
                        {
				(yyvsp[-3].chain)->location = (yylsp[-3]);
				close_scope(state);
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				(yyval.stmt) = chain_stmt_alloc(&(yyloc), (yyvsp[-1].chain), (yyvsp[-4].val));
			}
#line 11236 "parser_bison.c"
    break;

  case 490: /* verdict_stmt: verdict_expr  */
#line 3026 "parser_bison.y"
                        {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 11244 "parser_bison.c"
    break;

  case 491: /* verdict_stmt: verdict_map_stmt  */
#line 3030 "parser_bison.y"
                        {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 11252 "parser_bison.c"
    break;

  case 492: /* verdict_map_stmt: concat_expr "vmap" verdict_map_expr  */
#line 3036 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11260 "parser_bison.c"
    break;

  case 493: /* verdict_map_expr: '{' verdict_map_list_expr '}'  */
#line 3042 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11269 "parser_bison.c"
    break;

  case 495: /* verdict_map_list_expr: verdict_map_list_member_expr  */
#line 3050 "parser_bison.y"
                        {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11278 "parser_bison.c"
    break;

  case 496: /* verdict_map_list_expr: verdict_map_list_expr "comma" verdict_map_list_member_expr  */
#line 3055 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11287 "parser_bison.c"
    break;

  case 498: /* verdict_map_list_member_expr: opt_newline set_elem_expr "colon" verdict_expr opt_newline  */
#line 3063 "parser_bison.y"
                        {
				(yyval.expr) = mapping_expr_alloc(&(yylsp[-3]), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 11295 "parser_bison.c"
    break;

  case 499: /* connlimit_stmt: "ct" "count" "number" close_scope_ct  */
#line 3069 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 11304 "parser_bison.c"
    break;

  case 500: /* connlimit_stmt: "ct" "count" "over" "number" close_scope_ct  */
#line 3074 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 11314 "parser_bison.c"
    break;

  case 503: /* counter_stmt_alloc: "counter"  */
#line 3085 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 11322 "parser_bison.c"
    break;

  case 504: /* counter_stmt_alloc: "counter" "name" stmt_expr  */
#line 3089 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 11332 "parser_bison.c"
    break;

  case 505: /* counter_args: counter_arg  */
#line 3097 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 11340 "parser_bison.c"
    break;

  case 507: /* counter_arg: "packets" "number"  */
#line 3104 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 11348 "parser_bison.c"
    break;

  case 508: /* counter_arg: "bytes" "number"  */
#line 3108 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 11356 "parser_bison.c"
    break;

  case 509: /* last_stmt: "last"  */
#line 3114 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
			}
#line 11364 "parser_bison.c"
    break;

  case 510: /* last_stmt: "last" "used" "never"  */
#line 3118 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
			}
#line 11372 "parser_bison.c"
    break;

  case 511: /* last_stmt: "last" "used" time_spec  */
#line 3122 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
				(yyval.stmt)->last.used = (yyvsp[0].val);
				(yyval.stmt)->last.set = true;
			}
#line 11382 "parser_bison.c"
    break;

  case 514: /* log_stmt_alloc: "log"  */
#line 3134 "parser_bison.y"
                        {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 11390 "parser_bison.c"
    break;

  case 515: /* log_args: log_arg  */
#line 3140 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 11398 "parser_bison.c"
    break;

  case 517: /* log_arg: "prefix" string  */
#line 3147 "parser_bison.y"
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
#line 11527 "parser_bison.c"
    break;

  case 518: /* log_arg: "group" "number"  */
#line 3272 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 11536 "parser_bison.c"
    break;

  case 519: /* log_arg: "snaplen" "number"  */
#line 3277 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 11545 "parser_bison.c"
    break;

  case 520: /* log_arg: "queue-threshold" "number"  */
#line 3282 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 11554 "parser_bison.c"
    break;

  case 521: /* log_arg: "level" level_type  */
#line 3287 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 11563 "parser_bison.c"
    break;

  case 522: /* log_arg: "flags" log_flags  */
#line 3292 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 11571 "parser_bison.c"
    break;

  case 523: /* level_type: string  */
#line 3298 "parser_bison.y"
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
#line 11603 "parser_bison.c"
    break;

  case 524: /* log_flags: "tcp" log_flags_tcp close_scope_tcp  */
#line 3328 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-1].val);
			}
#line 11611 "parser_bison.c"
    break;

  case 525: /* log_flags: "ip" "options" close_scope_ip  */
#line 3332 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 11619 "parser_bison.c"
    break;

  case 526: /* log_flags: "skuid"  */
#line 3336 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_UID;
			}
#line 11627 "parser_bison.c"
    break;

  case 527: /* log_flags: "ether" close_scope_eth  */
#line 3340 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 11635 "parser_bison.c"
    break;

  case 528: /* log_flags: "all"  */
#line 3344 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_MASK;
			}
#line 11643 "parser_bison.c"
    break;

  case 529: /* log_flags_tcp: log_flags_tcp "comma" log_flag_tcp  */
#line 3350 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 11651 "parser_bison.c"
    break;

  case 531: /* log_flag_tcp: "seq"  */
#line 3357 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 11659 "parser_bison.c"
    break;

  case 532: /* log_flag_tcp: "options"  */
#line 3361 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 11667 "parser_bison.c"
    break;

  case 533: /* limit_stmt: "limit" "rate" limit_mode limit_rate_pkts limit_burst_pkts close_scope_limit  */
#line 3367 "parser_bison.y"
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
#line 11685 "parser_bison.c"
    break;

  case 534: /* limit_stmt: "limit" "rate" limit_mode limit_rate_bytes limit_burst_bytes close_scope_limit  */
#line 3381 "parser_bison.y"
                        {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-2].limit_rate).rate;
				(yyval.stmt)->limit.unit	= (yyvsp[-2].limit_rate).unit;
				(yyval.stmt)->limit.burst	= (yyvsp[-1].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKT_BYTES;
				(yyval.stmt)->limit.flags = (yyvsp[-3].val);
			}
#line 11698 "parser_bison.c"
    break;

  case 535: /* limit_stmt: "limit" "name" stmt_expr close_scope_limit  */
#line 3390 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 11708 "parser_bison.c"
    break;

  case 536: /* quota_mode: "over"  */
#line 3397 "parser_bison.y"
                                                { (yyval.val) = NFT_QUOTA_F_INV; }
#line 11714 "parser_bison.c"
    break;

  case 537: /* quota_mode: "until"  */
#line 3398 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11720 "parser_bison.c"
    break;

  case 538: /* quota_mode: %empty  */
#line 3399 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11726 "parser_bison.c"
    break;

  case 539: /* quota_unit: "bytes"  */
#line 3402 "parser_bison.y"
                                                { (yyval.string) = xstrdup("bytes"); }
#line 11732 "parser_bison.c"
    break;

  case 540: /* quota_unit: "string"  */
#line 3403 "parser_bison.y"
                                                { (yyval.string) = (yyvsp[0].string); }
#line 11738 "parser_bison.c"
    break;

  case 541: /* quota_used: %empty  */
#line 3406 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11744 "parser_bison.c"
    break;

  case 542: /* quota_used: "used" "number" quota_unit  */
#line 3408 "parser_bison.y"
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
#line 11761 "parser_bison.c"
    break;

  case 543: /* quota_stmt: "quota" quota_mode "number" quota_unit quota_used close_scope_quota  */
#line 3423 "parser_bison.y"
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
#line 11781 "parser_bison.c"
    break;

  case 544: /* quota_stmt: "quota" "name" stmt_expr close_scope_quota  */
#line 3439 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 11791 "parser_bison.c"
    break;

  case 545: /* limit_mode: "over"  */
#line 3446 "parser_bison.y"
                                                                { (yyval.val) = NFT_LIMIT_F_INV; }
#line 11797 "parser_bison.c"
    break;

  case 546: /* limit_mode: "until"  */
#line 3447 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 11803 "parser_bison.c"
    break;

  case 547: /* limit_mode: %empty  */
#line 3448 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 11809 "parser_bison.c"
    break;

  case 548: /* limit_burst_pkts: %empty  */
#line 3451 "parser_bison.y"
                                                                { (yyval.val) = 5; }
#line 11815 "parser_bison.c"
    break;

  case 549: /* limit_burst_pkts: "burst" "number" "packets"  */
#line 3452 "parser_bison.y"
                                                                { (yyval.val) = (yyvsp[-1].val); }
#line 11821 "parser_bison.c"
    break;

  case 550: /* limit_rate_pkts: "number" "/" time_unit  */
#line 3456 "parser_bison.y"
                        {
				(yyval.limit_rate).rate = (yyvsp[-2].val);
				(yyval.limit_rate).unit = (yyvsp[0].val);
			}
#line 11830 "parser_bison.c"
    break;

  case 551: /* limit_burst_bytes: %empty  */
#line 3462 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 11836 "parser_bison.c"
    break;

  case 552: /* limit_burst_bytes: "burst" limit_bytes  */
#line 3463 "parser_bison.y"
                                                                { (yyval.val) = (yyvsp[0].val); }
#line 11842 "parser_bison.c"
    break;

  case 553: /* limit_rate_bytes: "number" "string"  */
#line 3467 "parser_bison.y"
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
#line 11860 "parser_bison.c"
    break;

  case 554: /* limit_rate_bytes: limit_bytes "/" time_unit  */
#line 3481 "parser_bison.y"
                        {
				(yyval.limit_rate).rate = (yyvsp[-2].val);
				(yyval.limit_rate).unit = (yyvsp[0].val);
			}
#line 11869 "parser_bison.c"
    break;

  case 555: /* limit_bytes: "number" "bytes"  */
#line 3487 "parser_bison.y"
                                                        { (yyval.val) = (yyvsp[-1].val); }
#line 11875 "parser_bison.c"
    break;

  case 556: /* limit_bytes: "number" "string"  */
#line 3489 "parser_bison.y"
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
#line 11892 "parser_bison.c"
    break;

  case 557: /* time_unit: "second"  */
#line 3503 "parser_bison.y"
                                                { (yyval.val) = 1ULL; }
#line 11898 "parser_bison.c"
    break;

  case 558: /* time_unit: "minute"  */
#line 3504 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60; }
#line 11904 "parser_bison.c"
    break;

  case 559: /* time_unit: "hour"  */
#line 3505 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60; }
#line 11910 "parser_bison.c"
    break;

  case 560: /* time_unit: "day"  */
#line 3506 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 11916 "parser_bison.c"
    break;

  case 561: /* time_unit: "week"  */
#line 3507 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 11922 "parser_bison.c"
    break;

  case 563: /* reject_stmt_alloc: "reject"  */
#line 3514 "parser_bison.y"
                        {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 11930 "parser_bison.c"
    break;

  case 564: /* reject_with_expr: "string"  */
#line 3520 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state), (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 11940 "parser_bison.c"
    break;

  case 565: /* reject_with_expr: integer_expr  */
#line 3525 "parser_bison.y"
                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11946 "parser_bison.c"
    break;

  case 566: /* reject_opts: %empty  */
#line 3529 "parser_bison.y"
                        {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 11955 "parser_bison.c"
    break;

  case 567: /* reject_opts: "with" "icmp" "type" reject_with_expr close_scope_type close_scope_icmp  */
#line 3534 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-6].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-6].stmt)->reject.expr = (yyvsp[-2].expr);
				datatype_set((yyvsp[-6].stmt)->reject.expr, &icmp_code_type);
			}
#line 11966 "parser_bison.c"
    break;

  case 568: /* reject_opts: "with" "icmp" reject_with_expr  */
#line 3541 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmp_code_type);
			}
#line 11977 "parser_bison.c"
    break;

  case 569: /* reject_opts: "with" "icmpv6" "type" reject_with_expr close_scope_type close_scope_icmp  */
#line 3548 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-6].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-6].stmt)->reject.expr = (yyvsp[-2].expr);
				datatype_set((yyvsp[-6].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 11988 "parser_bison.c"
    break;

  case 570: /* reject_opts: "with" "icmpv6" reject_with_expr  */
#line 3555 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 11999 "parser_bison.c"
    break;

  case 571: /* reject_opts: "with" "icmpx" "type" reject_with_expr close_scope_type  */
#line 3562 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-5].stmt)->reject.expr = (yyvsp[-1].expr);
				datatype_set((yyvsp[-5].stmt)->reject.expr, &icmpx_code_type);
			}
#line 12009 "parser_bison.c"
    break;

  case 572: /* reject_opts: "with" "icmpx" reject_with_expr  */
#line 3568 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpx_code_type);
			}
#line 12019 "parser_bison.c"
    break;

  case 573: /* reject_opts: "with" "tcp" close_scope_tcp "reset" close_scope_reset  */
#line 3574 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 12027 "parser_bison.c"
    break;

  case 575: /* nat_stmt_alloc: "snat"  */
#line 3582 "parser_bison.y"
                                        { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 12033 "parser_bison.c"
    break;

  case 576: /* nat_stmt_alloc: "dnat"  */
#line 3583 "parser_bison.y"
                                        { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 12039 "parser_bison.c"
    break;

  case 577: /* tproxy_stmt: "tproxy" "to" stmt_expr  */
#line 3587 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 12049 "parser_bison.c"
    break;

  case 578: /* tproxy_stmt: "tproxy" nf_key_proto "to" stmt_expr  */
#line 3593 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 12059 "parser_bison.c"
    break;

  case 579: /* tproxy_stmt: "tproxy" "to" "colon" stmt_expr  */
#line 3599 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12069 "parser_bison.c"
    break;

  case 580: /* tproxy_stmt: "tproxy" "to" stmt_expr "colon" stmt_expr  */
#line 3605 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12080 "parser_bison.c"
    break;

  case 581: /* tproxy_stmt: "tproxy" nf_key_proto "to" stmt_expr "colon" stmt_expr  */
#line 3612 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12091 "parser_bison.c"
    break;

  case 582: /* tproxy_stmt: "tproxy" nf_key_proto "to" "colon" stmt_expr  */
#line 3619 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12101 "parser_bison.c"
    break;

  case 585: /* synproxy_stmt_alloc: "synproxy"  */
#line 3631 "parser_bison.y"
                        {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 12109 "parser_bison.c"
    break;

  case 586: /* synproxy_stmt_alloc: "synproxy" "name" stmt_expr  */
#line 3635 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 12119 "parser_bison.c"
    break;

  case 587: /* synproxy_args: synproxy_arg  */
#line 3643 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 12127 "parser_bison.c"
    break;

  case 589: /* synproxy_arg: "mss" "number"  */
#line 3650 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 12136 "parser_bison.c"
    break;

  case 590: /* synproxy_arg: "wscale" "number"  */
#line 3655 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 12145 "parser_bison.c"
    break;

  case 591: /* synproxy_arg: "timestamp"  */
#line 3660 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 12153 "parser_bison.c"
    break;

  case 592: /* synproxy_arg: "sack-permitted"  */
#line 3664 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 12161 "parser_bison.c"
    break;

  case 593: /* synproxy_config: "mss" "number" "wscale" "number" synproxy_ts synproxy_sack  */
#line 3670 "parser_bison.y"
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
#line 12181 "parser_bison.c"
    break;

  case 594: /* synproxy_config: "mss" "number" stmt_separator "wscale" "number" stmt_separator synproxy_ts synproxy_sack  */
#line 3686 "parser_bison.y"
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
#line 12201 "parser_bison.c"
    break;

  case 595: /* synproxy_obj: %empty  */
#line 3704 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 12210 "parser_bison.c"
    break;

  case 596: /* synproxy_ts: %empty  */
#line 3710 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 12216 "parser_bison.c"
    break;

  case 597: /* synproxy_ts: "timestamp"  */
#line 3712 "parser_bison.y"
                        {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 12224 "parser_bison.c"
    break;

  case 598: /* synproxy_sack: %empty  */
#line 3717 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 12230 "parser_bison.c"
    break;

  case 599: /* synproxy_sack: "sack-permitted"  */
#line 3719 "parser_bison.y"
                        {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 12238 "parser_bison.c"
    break;

  case 600: /* primary_stmt_expr: symbol_expr  */
#line 3724 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12244 "parser_bison.c"
    break;

  case 601: /* primary_stmt_expr: integer_expr  */
#line 3725 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12250 "parser_bison.c"
    break;

  case 602: /* primary_stmt_expr: boolean_expr  */
#line 3726 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12256 "parser_bison.c"
    break;

  case 603: /* primary_stmt_expr: meta_expr  */
#line 3727 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12262 "parser_bison.c"
    break;

  case 604: /* primary_stmt_expr: rt_expr  */
#line 3728 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12268 "parser_bison.c"
    break;

  case 605: /* primary_stmt_expr: ct_expr  */
#line 3729 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12274 "parser_bison.c"
    break;

  case 606: /* primary_stmt_expr: numgen_expr  */
#line 3730 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12280 "parser_bison.c"
    break;

  case 607: /* primary_stmt_expr: hash_expr  */
#line 3731 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12286 "parser_bison.c"
    break;

  case 608: /* primary_stmt_expr: payload_expr  */
#line 3732 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12292 "parser_bison.c"
    break;

  case 609: /* primary_stmt_expr: keyword_expr  */
#line 3733 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12298 "parser_bison.c"
    break;

  case 610: /* primary_stmt_expr: socket_expr  */
#line 3734 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12304 "parser_bison.c"
    break;

  case 611: /* primary_stmt_expr: osf_expr  */
#line 3735 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12310 "parser_bison.c"
    break;

  case 612: /* primary_stmt_expr: '(' basic_stmt_expr ')'  */
#line 3736 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 12316 "parser_bison.c"
    break;

  case 614: /* shift_stmt_expr: shift_stmt_expr "<<" primary_stmt_expr  */
#line 3741 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12324 "parser_bison.c"
    break;

  case 615: /* shift_stmt_expr: shift_stmt_expr ">>" primary_stmt_expr  */
#line 3745 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12332 "parser_bison.c"
    break;

  case 617: /* and_stmt_expr: and_stmt_expr "&" shift_stmt_expr  */
#line 3752 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12340 "parser_bison.c"
    break;

  case 619: /* exclusive_or_stmt_expr: exclusive_or_stmt_expr "^" and_stmt_expr  */
#line 3759 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12348 "parser_bison.c"
    break;

  case 621: /* inclusive_or_stmt_expr: inclusive_or_stmt_expr '|' exclusive_or_stmt_expr  */
#line 3766 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12356 "parser_bison.c"
    break;

  case 624: /* concat_stmt_expr: concat_stmt_expr "." primary_stmt_expr  */
#line 3776 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 12369 "parser_bison.c"
    break;

  case 627: /* map_stmt_expr: concat_stmt_expr "map" map_stmt_expr_set  */
#line 3791 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12377 "parser_bison.c"
    break;

  case 628: /* map_stmt_expr: concat_stmt_expr  */
#line 3794 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 12383 "parser_bison.c"
    break;

  case 629: /* prefix_stmt_expr: basic_stmt_expr "/" "number"  */
#line 3798 "parser_bison.y"
                        {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 12391 "parser_bison.c"
    break;

  case 630: /* range_stmt_expr: basic_stmt_expr "-" basic_stmt_expr  */
#line 3804 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12399 "parser_bison.c"
    break;

  case 636: /* nat_stmt_args: stmt_expr  */
#line 3819 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12407 "parser_bison.c"
    break;

  case 637: /* nat_stmt_args: "to" stmt_expr  */
#line 3823 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12415 "parser_bison.c"
    break;

  case 638: /* nat_stmt_args: nf_key_proto "to" stmt_expr  */
#line 3827 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12424 "parser_bison.c"
    break;

  case 639: /* nat_stmt_args: stmt_expr "colon" stmt_expr  */
#line 3832 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12433 "parser_bison.c"
    break;

  case 640: /* nat_stmt_args: "to" stmt_expr "colon" stmt_expr  */
#line 3837 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12442 "parser_bison.c"
    break;

  case 641: /* nat_stmt_args: nf_key_proto "to" stmt_expr "colon" stmt_expr  */
#line 3842 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12452 "parser_bison.c"
    break;

  case 642: /* nat_stmt_args: "colon" stmt_expr  */
#line 3848 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12460 "parser_bison.c"
    break;

  case 643: /* nat_stmt_args: "to" "colon" stmt_expr  */
#line 3852 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12468 "parser_bison.c"
    break;

  case 644: /* nat_stmt_args: nat_stmt_args nf_nat_flags  */
#line 3856 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12476 "parser_bison.c"
    break;

  case 645: /* nat_stmt_args: nf_key_proto "addr" "." "port" "to" stmt_expr  */
#line 3860 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.type_flags = STMT_NAT_F_CONCAT;
			}
#line 12486 "parser_bison.c"
    break;

  case 646: /* nat_stmt_args: nf_key_proto "interval" "to" stmt_expr  */
#line 3866 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12495 "parser_bison.c"
    break;

  case 647: /* nat_stmt_args: "interval" "to" stmt_expr  */
#line 3871 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12503 "parser_bison.c"
    break;

  case 648: /* nat_stmt_args: nf_key_proto "prefix" "to" stmt_expr  */
#line 3875 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-4].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 12515 "parser_bison.c"
    break;

  case 649: /* nat_stmt_args: "prefix" "to" stmt_expr  */
#line 3883 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-3].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 12526 "parser_bison.c"
    break;

  case 652: /* masq_stmt_alloc: "masquerade"  */
#line 3895 "parser_bison.y"
                                                { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 12532 "parser_bison.c"
    break;

  case 653: /* masq_stmt_args: "to" "colon" stmt_expr  */
#line 3899 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12540 "parser_bison.c"
    break;

  case 654: /* masq_stmt_args: "to" "colon" stmt_expr nf_nat_flags  */
#line 3903 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12549 "parser_bison.c"
    break;

  case 655: /* masq_stmt_args: nf_nat_flags  */
#line 3908 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12557 "parser_bison.c"
    break;

  case 658: /* redir_stmt_alloc: "redirect"  */
#line 3917 "parser_bison.y"
                                                { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 12563 "parser_bison.c"
    break;

  case 659: /* redir_stmt_arg: "to" stmt_expr  */
#line 3921 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12571 "parser_bison.c"
    break;

  case 660: /* redir_stmt_arg: "to" "colon" stmt_expr  */
#line 3925 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12579 "parser_bison.c"
    break;

  case 661: /* redir_stmt_arg: nf_nat_flags  */
#line 3929 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12587 "parser_bison.c"
    break;

  case 662: /* redir_stmt_arg: "to" stmt_expr nf_nat_flags  */
#line 3933 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12596 "parser_bison.c"
    break;

  case 663: /* redir_stmt_arg: "to" "colon" stmt_expr nf_nat_flags  */
#line 3938 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12605 "parser_bison.c"
    break;

  case 664: /* dup_stmt: "dup" "to" stmt_expr  */
#line 3945 "parser_bison.y"
                        {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 12614 "parser_bison.c"
    break;

  case 665: /* dup_stmt: "dup" "to" stmt_expr "device" stmt_expr  */
#line 3950 "parser_bison.y"
                        {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 12624 "parser_bison.c"
    break;

  case 666: /* fwd_stmt: "fwd" "to" stmt_expr  */
#line 3958 "parser_bison.y"
                        {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 12633 "parser_bison.c"
    break;

  case 667: /* fwd_stmt: "fwd" nf_key_proto "to" stmt_expr "device" stmt_expr  */
#line 3963 "parser_bison.y"
                        {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 12644 "parser_bison.c"
    break;

  case 669: /* nf_nat_flags: nf_nat_flags "comma" nf_nat_flag  */
#line 3973 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 12652 "parser_bison.c"
    break;

  case 670: /* nf_nat_flag: "random"  */
#line 3978 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 12658 "parser_bison.c"
    break;

  case 671: /* nf_nat_flag: "fully-random"  */
#line 3979 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 12664 "parser_bison.c"
    break;

  case 672: /* nf_nat_flag: "persistent"  */
#line 3980 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 12670 "parser_bison.c"
    break;

  case 674: /* queue_stmt: "queue" "to" queue_stmt_expr close_scope_queue  */
#line 3985 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), 0);
			}
#line 12678 "parser_bison.c"
    break;

  case 675: /* queue_stmt: "queue" "flags" queue_stmt_flags "to" queue_stmt_expr close_scope_queue  */
#line 3989 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 12686 "parser_bison.c"
    break;

  case 676: /* queue_stmt: "queue" "flags" queue_stmt_flags "num" queue_stmt_expr_simple close_scope_queue  */
#line 3993 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 12694 "parser_bison.c"
    break;

  case 679: /* queue_stmt_alloc: "queue"  */
#line 4003 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), NULL, 0);
			}
#line 12702 "parser_bison.c"
    break;

  case 680: /* queue_stmt_args: queue_stmt_arg  */
#line 4009 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 12710 "parser_bison.c"
    break;

  case 682: /* queue_stmt_arg: "num" queue_stmt_expr_simple  */
#line 4016 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 12719 "parser_bison.c"
    break;

  case 683: /* queue_stmt_arg: queue_stmt_flags  */
#line 4021 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 12727 "parser_bison.c"
    break;

  case 688: /* queue_stmt_expr_simple: queue_expr "-" queue_expr  */
#line 4033 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12735 "parser_bison.c"
    break;

  case 694: /* queue_stmt_flags: queue_stmt_flags "comma" queue_stmt_flag  */
#line 4046 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 12743 "parser_bison.c"
    break;

  case 695: /* queue_stmt_flag: "bypass"  */
#line 4051 "parser_bison.y"
                                        { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 12749 "parser_bison.c"
    break;

  case 696: /* queue_stmt_flag: "fanout"  */
#line 4052 "parser_bison.y"
                                        { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 12755 "parser_bison.c"
    break;

  case 699: /* set_elem_expr_stmt_alloc: concat_expr  */
#line 4060 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 12763 "parser_bison.c"
    break;

  case 700: /* set_stmt: "set" set_stmt_op set_elem_expr_stmt set_ref_expr  */
#line 4066 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 12774 "parser_bison.c"
    break;

  case 701: /* set_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt '}'  */
#line 4073 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 12785 "parser_bison.c"
    break;

  case 702: /* set_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt stateful_stmt_list '}'  */
#line 4080 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				list_splice_tail((yyvsp[-1].list), &(yyval.stmt)->set.stmt_list);
				free((yyvsp[-1].list));
			}
#line 12798 "parser_bison.c"
    break;

  case 703: /* set_stmt_op: "add"  */
#line 4090 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 12804 "parser_bison.c"
    break;

  case 704: /* set_stmt_op: "update"  */
#line 4091 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 12810 "parser_bison.c"
    break;

  case 705: /* set_stmt_op: "delete"  */
#line 4092 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 12816 "parser_bison.c"
    break;

  case 706: /* map_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt "colon" set_elem_expr_stmt '}'  */
#line 4096 "parser_bison.y"
                        {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 12828 "parser_bison.c"
    break;

  case 707: /* map_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt stateful_stmt_list "colon" set_elem_expr_stmt '}'  */
#line 4104 "parser_bison.y"
                        {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
				list_splice_tail((yyvsp[-3].list), &(yyval.stmt)->map.stmt_list);
				free((yyvsp[-3].list));
			}
#line 12842 "parser_bison.c"
    break;

  case 708: /* meter_stmt: flow_stmt_legacy_alloc flow_stmt_opts '{' meter_key_expr stmt '}'  */
#line 4116 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 12853 "parser_bison.c"
    break;

  case 709: /* meter_stmt: meter_stmt_alloc  */
#line 4122 "parser_bison.y"
                                                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 12859 "parser_bison.c"
    break;

  case 710: /* flow_stmt_legacy_alloc: "flow"  */
#line 4126 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 12867 "parser_bison.c"
    break;

  case 711: /* flow_stmt_opts: flow_stmt_opt  */
#line 4132 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 12875 "parser_bison.c"
    break;

  case 713: /* flow_stmt_opt: "table" identifier  */
#line 4139 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 12883 "parser_bison.c"
    break;

  case 714: /* meter_stmt_alloc: "meter" identifier '{' meter_key_expr stmt '}'  */
#line 4145 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 12896 "parser_bison.c"
    break;

  case 715: /* meter_stmt_alloc: "meter" identifier "size" "number" '{' meter_key_expr stmt '}'  */
#line 4154 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 12909 "parser_bison.c"
    break;

  case 716: /* match_stmt: relational_expr  */
#line 4165 "parser_bison.y"
                        {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 12917 "parser_bison.c"
    break;

  case 717: /* variable_expr: '$' identifier  */
#line 4171 "parser_bison.y"
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
#line 12945 "parser_bison.c"
    break;

  case 719: /* symbol_expr: string  */
#line 4198 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 12956 "parser_bison.c"
    break;

  case 722: /* set_ref_symbol_expr: "@" identifier close_scope_at  */
#line 4211 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[-1].string));
				xfree((yyvsp[-1].string));
			}
#line 12967 "parser_bison.c"
    break;

  case 723: /* integer_expr: "number"  */
#line 4220 "parser_bison.y"
                        {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 12980 "parser_bison.c"
    break;

  case 724: /* primary_expr: symbol_expr  */
#line 4230 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12986 "parser_bison.c"
    break;

  case 725: /* primary_expr: integer_expr  */
#line 4231 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12992 "parser_bison.c"
    break;

  case 726: /* primary_expr: payload_expr  */
#line 4232 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12998 "parser_bison.c"
    break;

  case 727: /* primary_expr: exthdr_expr  */
#line 4233 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13004 "parser_bison.c"
    break;

  case 728: /* primary_expr: exthdr_exists_expr  */
#line 4234 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13010 "parser_bison.c"
    break;

  case 729: /* primary_expr: meta_expr  */
#line 4235 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13016 "parser_bison.c"
    break;

  case 730: /* primary_expr: socket_expr  */
#line 4236 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13022 "parser_bison.c"
    break;

  case 731: /* primary_expr: rt_expr  */
#line 4237 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13028 "parser_bison.c"
    break;

  case 732: /* primary_expr: ct_expr  */
#line 4238 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13034 "parser_bison.c"
    break;

  case 733: /* primary_expr: numgen_expr  */
#line 4239 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13040 "parser_bison.c"
    break;

  case 734: /* primary_expr: hash_expr  */
#line 4240 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13046 "parser_bison.c"
    break;

  case 735: /* primary_expr: fib_expr  */
#line 4241 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13052 "parser_bison.c"
    break;

  case 736: /* primary_expr: osf_expr  */
#line 4242 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13058 "parser_bison.c"
    break;

  case 737: /* primary_expr: xfrm_expr  */
#line 4243 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13064 "parser_bison.c"
    break;

  case 738: /* primary_expr: '(' basic_expr ')'  */
#line 4244 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 13070 "parser_bison.c"
    break;

  case 739: /* fib_expr: "fib" fib_tuple fib_result close_scope_fib  */
#line 4248 "parser_bison.y"
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
#line 13095 "parser_bison.c"
    break;

  case 740: /* fib_result: "oif"  */
#line 4270 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 13101 "parser_bison.c"
    break;

  case 741: /* fib_result: "oifname"  */
#line 4271 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 13107 "parser_bison.c"
    break;

  case 742: /* fib_result: "type" close_scope_type  */
#line 4272 "parser_bison.y"
                                                                { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 13113 "parser_bison.c"
    break;

  case 743: /* fib_flag: "saddr"  */
#line 4275 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 13119 "parser_bison.c"
    break;

  case 744: /* fib_flag: "daddr"  */
#line 4276 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 13125 "parser_bison.c"
    break;

  case 745: /* fib_flag: "mark"  */
#line 4277 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_MARK; }
#line 13131 "parser_bison.c"
    break;

  case 746: /* fib_flag: "iif"  */
#line 4278 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_IIF; }
#line 13137 "parser_bison.c"
    break;

  case 747: /* fib_flag: "oif"  */
#line 4279 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_OIF; }
#line 13143 "parser_bison.c"
    break;

  case 748: /* fib_tuple: fib_flag "." fib_tuple  */
#line 4283 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 13151 "parser_bison.c"
    break;

  case 750: /* osf_expr: "osf" osf_ttl "version" close_scope_osf  */
#line 4290 "parser_bison.y"
                        {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-2].val), NFT_OSF_F_VERSION);
			}
#line 13159 "parser_bison.c"
    break;

  case 751: /* osf_expr: "osf" osf_ttl "name" close_scope_osf  */
#line 4294 "parser_bison.y"
                        {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-2].val), 0);
			}
#line 13167 "parser_bison.c"
    break;

  case 752: /* osf_ttl: %empty  */
#line 4300 "parser_bison.y"
                        {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 13175 "parser_bison.c"
    break;

  case 753: /* osf_ttl: "ttl" "string"  */
#line 4304 "parser_bison.y"
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
#line 13193 "parser_bison.c"
    break;

  case 755: /* shift_expr: shift_expr "<<" primary_rhs_expr  */
#line 4321 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13201 "parser_bison.c"
    break;

  case 756: /* shift_expr: shift_expr ">>" primary_rhs_expr  */
#line 4325 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13209 "parser_bison.c"
    break;

  case 758: /* and_expr: and_expr "&" shift_rhs_expr  */
#line 4332 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13217 "parser_bison.c"
    break;

  case 760: /* exclusive_or_expr: exclusive_or_expr "^" and_rhs_expr  */
#line 4339 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13225 "parser_bison.c"
    break;

  case 762: /* inclusive_or_expr: inclusive_or_expr '|' exclusive_or_rhs_expr  */
#line 4346 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13233 "parser_bison.c"
    break;

  case 765: /* concat_expr: concat_expr "." basic_expr  */
#line 4356 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 13246 "parser_bison.c"
    break;

  case 766: /* prefix_rhs_expr: basic_rhs_expr "/" "number"  */
#line 4367 "parser_bison.y"
                        {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 13254 "parser_bison.c"
    break;

  case 767: /* range_rhs_expr: basic_rhs_expr "-" basic_rhs_expr  */
#line 4373 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13262 "parser_bison.c"
    break;

  case 770: /* map_expr: concat_expr "map" rhs_expr  */
#line 4383 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13270 "parser_bison.c"
    break;

  case 774: /* set_expr: '{' set_list_expr '}'  */
#line 4394 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13279 "parser_bison.c"
    break;

  case 775: /* set_list_expr: set_list_member_expr  */
#line 4401 "parser_bison.y"
                        {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 13288 "parser_bison.c"
    break;

  case 776: /* set_list_expr: set_list_expr "comma" set_list_member_expr  */
#line 4406 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 13297 "parser_bison.c"
    break;

  case 778: /* set_list_member_expr: opt_newline set_expr opt_newline  */
#line 4414 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13305 "parser_bison.c"
    break;

  case 779: /* set_list_member_expr: opt_newline set_elem_expr opt_newline  */
#line 4418 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13313 "parser_bison.c"
    break;

  case 780: /* set_list_member_expr: opt_newline set_elem_expr "colon" set_rhs_expr opt_newline  */
#line 4422 "parser_bison.y"
                        {
				(yyval.expr) = mapping_expr_alloc(&(yylsp[-3]), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 13321 "parser_bison.c"
    break;

  case 782: /* meter_key_expr: meter_key_expr_alloc set_elem_options  */
#line 4429 "parser_bison.y"
                        {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13330 "parser_bison.c"
    break;

  case 783: /* meter_key_expr_alloc: concat_expr  */
#line 4436 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 13338 "parser_bison.c"
    break;

  case 786: /* set_elem_key_expr: set_lhs_expr  */
#line 4445 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13344 "parser_bison.c"
    break;

  case 787: /* set_elem_key_expr: "*"  */
#line 4446 "parser_bison.y"
                                                        { (yyval.expr) = set_elem_catchall_expr_alloc(&(yylsp[0])); }
#line 13350 "parser_bison.c"
    break;

  case 788: /* set_elem_expr_alloc: set_elem_key_expr set_elem_stmt_list  */
#line 4450 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[-1]), (yyvsp[-1].expr));
				list_splice_tail((yyvsp[0].list), &(yyval.expr)->stmt_list);
				xfree((yyvsp[0].list));
			}
#line 13360 "parser_bison.c"
    break;

  case 789: /* set_elem_expr_alloc: set_elem_key_expr  */
#line 4456 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 13368 "parser_bison.c"
    break;

  case 790: /* set_elem_options: set_elem_option  */
#line 4462 "parser_bison.y"
                        {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 13376 "parser_bison.c"
    break;

  case 792: /* set_elem_option: "timeout" time_spec  */
#line 4469 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 13384 "parser_bison.c"
    break;

  case 793: /* set_elem_option: "expires" time_spec  */
#line 4473 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 13392 "parser_bison.c"
    break;

  case 794: /* set_elem_option: comment_spec  */
#line 4477 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 13404 "parser_bison.c"
    break;

  case 795: /* set_elem_expr_options: set_elem_expr_option  */
#line 4487 "parser_bison.y"
                        {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 13412 "parser_bison.c"
    break;

  case 797: /* set_elem_stmt_list: set_elem_stmt  */
#line 4494 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 13422 "parser_bison.c"
    break;

  case 798: /* set_elem_stmt_list: set_elem_stmt_list set_elem_stmt  */
#line 4500 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 13431 "parser_bison.c"
    break;

  case 799: /* set_elem_stmt: "counter" close_scope_counter  */
#line 4507 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 13439 "parser_bison.c"
    break;

  case 800: /* set_elem_stmt: "counter" "packets" "number" "bytes" "number" close_scope_counter  */
#line 4511 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
				(yyval.stmt)->counter.packets = (yyvsp[-3].val);
				(yyval.stmt)->counter.bytes = (yyvsp[-1].val);
			}
#line 13449 "parser_bison.c"
    break;

  case 801: /* set_elem_stmt: "limit" "rate" limit_mode limit_rate_pkts limit_burst_pkts close_scope_limit  */
#line 4517 "parser_bison.y"
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
#line 13467 "parser_bison.c"
    break;

  case 802: /* set_elem_stmt: "limit" "rate" limit_mode limit_rate_bytes limit_burst_bytes close_scope_limit  */
#line 4531 "parser_bison.y"
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
#line 13485 "parser_bison.c"
    break;

  case 803: /* set_elem_stmt: "ct" "count" "number" close_scope_ct  */
#line 4545 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 13494 "parser_bison.c"
    break;

  case 804: /* set_elem_stmt: "ct" "count" "over" "number" close_scope_ct  */
#line 4550 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 13504 "parser_bison.c"
    break;

  case 805: /* set_elem_stmt: "quota" quota_mode "number" quota_unit quota_used close_scope_quota  */
#line 4556 "parser_bison.y"
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
#line 13524 "parser_bison.c"
    break;

  case 806: /* set_elem_stmt: "last" "used" "never" close_scope_last  */
#line 4572 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
			}
#line 13532 "parser_bison.c"
    break;

  case 807: /* set_elem_stmt: "last" "used" time_spec close_scope_last  */
#line 4576 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
				(yyval.stmt)->last.used = (yyvsp[-1].val);
				(yyval.stmt)->last.set = true;
			}
#line 13542 "parser_bison.c"
    break;

  case 808: /* set_elem_expr_option: "timeout" time_spec  */
#line 4584 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 13550 "parser_bison.c"
    break;

  case 809: /* set_elem_expr_option: "expires" time_spec  */
#line 4588 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 13558 "parser_bison.c"
    break;

  case 810: /* set_elem_expr_option: comment_spec  */
#line 4592 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 13570 "parser_bison.c"
    break;

  case 816: /* initializer_expr: '{' '}'  */
#line 4610 "parser_bison.y"
                                                { (yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_SET); }
#line 13576 "parser_bison.c"
    break;

  case 817: /* initializer_expr: "-" "number"  */
#line 4612 "parser_bison.y"
                        {
				int32_t num = -(yyvsp[0].val);

				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(num) * BITS_PER_BYTE,
							 &num);
			}
#line 13589 "parser_bison.c"
    break;

  case 818: /* counter_config: "packets" "number" "bytes" "number"  */
#line 4623 "parser_bison.y"
                        {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 13601 "parser_bison.c"
    break;

  case 819: /* counter_obj: %empty  */
#line 4633 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 13610 "parser_bison.c"
    break;

  case 820: /* quota_config: quota_mode "number" quota_unit quota_used  */
#line 4640 "parser_bison.y"
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
#line 13632 "parser_bison.c"
    break;

  case 821: /* quota_obj: %empty  */
#line 4660 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 13641 "parser_bison.c"
    break;

  case 822: /* secmark_config: string  */
#line 4667 "parser_bison.y"
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
#line 13659 "parser_bison.c"
    break;

  case 823: /* secmark_obj: %empty  */
#line 4683 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 13668 "parser_bison.c"
    break;

  case 824: /* ct_obj_type: "helper"  */
#line 4689 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 13674 "parser_bison.c"
    break;

  case 825: /* ct_obj_type: "timeout"  */
#line 4690 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 13680 "parser_bison.c"
    break;

  case 826: /* ct_obj_type: "expectation"  */
#line 4691 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 13686 "parser_bison.c"
    break;

  case 827: /* ct_cmd_type: "helpers"  */
#line 4694 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_HELPERS; }
#line 13692 "parser_bison.c"
    break;

  case 828: /* ct_cmd_type: "timeout"  */
#line 4695 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_TIMEOUT; }
#line 13698 "parser_bison.c"
    break;

  case 829: /* ct_cmd_type: "expectation"  */
#line 4696 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_EXPECT; }
#line 13704 "parser_bison.c"
    break;

  case 830: /* ct_l4protoname: "tcp" close_scope_tcp  */
#line 4699 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_TCP; }
#line 13710 "parser_bison.c"
    break;

  case 831: /* ct_l4protoname: "udp" close_scope_udp  */
#line 4700 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_UDP; }
#line 13716 "parser_bison.c"
    break;

  case 832: /* ct_helper_config: "type" "quoted string" "protocol" ct_l4protoname stmt_separator close_scope_type  */
#line 4704 "parser_bison.y"
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
#line 13736 "parser_bison.c"
    break;

  case 833: /* ct_helper_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4720 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 13744 "parser_bison.c"
    break;

  case 834: /* timeout_states: timeout_state  */
#line 4726 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 13754 "parser_bison.c"
    break;

  case 835: /* timeout_states: timeout_states "comma" timeout_state  */
#line 4732 "parser_bison.y"
                        {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 13763 "parser_bison.c"
    break;

  case 836: /* timeout_state: "string" "colon" "number"  */
#line 4740 "parser_bison.y"
                        {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 13778 "parser_bison.c"
    break;

  case 837: /* ct_timeout_config: "protocol" ct_l4protoname stmt_separator  */
#line 4753 "parser_bison.y"
                        {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 13790 "parser_bison.c"
    break;

  case 838: /* ct_timeout_config: "policy" '=' '{' timeout_states '}' stmt_separator close_scope_policy  */
#line 4761 "parser_bison.y"
                        {
				struct ct_timeout *ct;

				ct = &(yyvsp[-7].obj)->ct_timeout;
				list_splice_tail((yyvsp[-3].list), &ct->timeout_list);
				xfree((yyvsp[-3].list));
			}
#line 13802 "parser_bison.c"
    break;

  case 839: /* ct_timeout_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4769 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 13810 "parser_bison.c"
    break;

  case 840: /* ct_expect_config: "protocol" ct_l4protoname stmt_separator  */
#line 4775 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 13818 "parser_bison.c"
    break;

  case 841: /* ct_expect_config: "dport" "number" stmt_separator  */
#line 4779 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 13826 "parser_bison.c"
    break;

  case 842: /* ct_expect_config: "timeout" time_spec stmt_separator  */
#line 4783 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 13834 "parser_bison.c"
    break;

  case 843: /* ct_expect_config: "size" "number" stmt_separator  */
#line 4787 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 13842 "parser_bison.c"
    break;

  case 844: /* ct_expect_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4791 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 13850 "parser_bison.c"
    break;

  case 845: /* ct_obj_alloc: %empty  */
#line 4797 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 13858 "parser_bison.c"
    break;

  case 846: /* limit_config: "rate" limit_mode limit_rate_pkts limit_burst_pkts  */
#line 4803 "parser_bison.y"
                        {
				struct limit *limit;

				limit = &(yyvsp[-4].obj)->limit;
				limit->rate	= (yyvsp[-1].limit_rate).rate;
				limit->unit	= (yyvsp[-1].limit_rate).unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-2].val);
			}
#line 13873 "parser_bison.c"
    break;

  case 847: /* limit_config: "rate" limit_mode limit_rate_bytes limit_burst_bytes  */
#line 4814 "parser_bison.y"
                        {
				struct limit *limit;

				limit = &(yyvsp[-4].obj)->limit;
				limit->rate	= (yyvsp[-1].limit_rate).rate;
				limit->unit	= (yyvsp[-1].limit_rate).unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKT_BYTES;
				limit->flags	= (yyvsp[-2].val);
			}
#line 13888 "parser_bison.c"
    break;

  case 848: /* limit_obj: %empty  */
#line 4827 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 13897 "parser_bison.c"
    break;

  case 849: /* relational_expr: expr rhs_expr  */
#line 4834 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 13905 "parser_bison.c"
    break;

  case 850: /* relational_expr: expr list_rhs_expr  */
#line 4838 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 13913 "parser_bison.c"
    break;

  case 851: /* relational_expr: expr basic_rhs_expr "/" list_rhs_expr  */
#line 4842 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 13921 "parser_bison.c"
    break;

  case 852: /* relational_expr: expr list_rhs_expr "/" list_rhs_expr  */
#line 4846 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 13929 "parser_bison.c"
    break;

  case 853: /* relational_expr: expr relational_op basic_rhs_expr "/" list_rhs_expr  */
#line 4850 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 13937 "parser_bison.c"
    break;

  case 854: /* relational_expr: expr relational_op list_rhs_expr "/" list_rhs_expr  */
#line 4854 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 13945 "parser_bison.c"
    break;

  case 855: /* relational_expr: expr relational_op rhs_expr  */
#line 4858 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13953 "parser_bison.c"
    break;

  case 856: /* relational_expr: expr relational_op list_rhs_expr  */
#line 4862 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13961 "parser_bison.c"
    break;

  case 857: /* list_rhs_expr: basic_rhs_expr "comma" basic_rhs_expr  */
#line 4868 "parser_bison.y"
                        {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 13971 "parser_bison.c"
    break;

  case 858: /* list_rhs_expr: list_rhs_expr "comma" basic_rhs_expr  */
#line 4874 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 13981 "parser_bison.c"
    break;

  case 859: /* rhs_expr: concat_rhs_expr  */
#line 4881 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13987 "parser_bison.c"
    break;

  case 860: /* rhs_expr: set_expr  */
#line 4882 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13993 "parser_bison.c"
    break;

  case 861: /* rhs_expr: set_ref_symbol_expr  */
#line 4883 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13999 "parser_bison.c"
    break;

  case 863: /* shift_rhs_expr: shift_rhs_expr "<<" primary_rhs_expr  */
#line 4888 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14007 "parser_bison.c"
    break;

  case 864: /* shift_rhs_expr: shift_rhs_expr ">>" primary_rhs_expr  */
#line 4892 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14015 "parser_bison.c"
    break;

  case 866: /* and_rhs_expr: and_rhs_expr "&" shift_rhs_expr  */
#line 4899 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14023 "parser_bison.c"
    break;

  case 868: /* exclusive_or_rhs_expr: exclusive_or_rhs_expr "^" and_rhs_expr  */
#line 4906 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14031 "parser_bison.c"
    break;

  case 870: /* inclusive_or_rhs_expr: inclusive_or_rhs_expr '|' exclusive_or_rhs_expr  */
#line 4913 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14039 "parser_bison.c"
    break;

  case 874: /* concat_rhs_expr: concat_rhs_expr "." multiton_rhs_expr  */
#line 4924 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 14052 "parser_bison.c"
    break;

  case 875: /* concat_rhs_expr: concat_rhs_expr "." basic_rhs_expr  */
#line 4933 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 14065 "parser_bison.c"
    break;

  case 876: /* boolean_keys: "exists"  */
#line 4943 "parser_bison.y"
                                                { (yyval.val8) = true; }
#line 14071 "parser_bison.c"
    break;

  case 877: /* boolean_keys: "missing"  */
#line 4944 "parser_bison.y"
                                                { (yyval.val8) = false; }
#line 14077 "parser_bison.c"
    break;

  case 878: /* boolean_expr: boolean_keys  */
#line 4948 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 14087 "parser_bison.c"
    break;

  case 879: /* keyword_expr: "ether" close_scope_eth  */
#line 4955 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 14093 "parser_bison.c"
    break;

  case 880: /* keyword_expr: "ip" close_scope_ip  */
#line 4956 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 14099 "parser_bison.c"
    break;

  case 881: /* keyword_expr: "ip6" close_scope_ip6  */
#line 4957 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 14105 "parser_bison.c"
    break;

  case 882: /* keyword_expr: "vlan" close_scope_vlan  */
#line 4958 "parser_bison.y"
                                                         { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 14111 "parser_bison.c"
    break;

  case 883: /* keyword_expr: "arp" close_scope_arp  */
#line 4959 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 14117 "parser_bison.c"
    break;

  case 884: /* keyword_expr: "dnat" close_scope_nat  */
#line 4960 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 14123 "parser_bison.c"
    break;

  case 885: /* keyword_expr: "snat" close_scope_nat  */
#line 4961 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 14129 "parser_bison.c"
    break;

  case 886: /* keyword_expr: "ecn"  */
#line 4962 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 14135 "parser_bison.c"
    break;

  case 887: /* keyword_expr: "reset" close_scope_reset  */
#line 4963 "parser_bison.y"
                                                                { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 14141 "parser_bison.c"
    break;

  case 888: /* keyword_expr: "destroy" close_scope_destroy  */
#line 4964 "parser_bison.y"
                                                                { (yyval.expr) = symbol_value(&(yyloc), "destroy"); }
#line 14147 "parser_bison.c"
    break;

  case 889: /* keyword_expr: "original"  */
#line 4965 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 14153 "parser_bison.c"
    break;

  case 890: /* keyword_expr: "reply"  */
#line 4966 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 14159 "parser_bison.c"
    break;

  case 891: /* keyword_expr: "label"  */
#line 4967 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 14165 "parser_bison.c"
    break;

  case 892: /* keyword_expr: "last" close_scope_last  */
#line 4968 "parser_bison.y"
                                                                { (yyval.expr) = symbol_value(&(yyloc), "last"); }
#line 14171 "parser_bison.c"
    break;

  case 893: /* primary_rhs_expr: symbol_expr  */
#line 4971 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14177 "parser_bison.c"
    break;

  case 894: /* primary_rhs_expr: integer_expr  */
#line 4972 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14183 "parser_bison.c"
    break;

  case 895: /* primary_rhs_expr: boolean_expr  */
#line 4973 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14189 "parser_bison.c"
    break;

  case 896: /* primary_rhs_expr: keyword_expr  */
#line 4974 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14195 "parser_bison.c"
    break;

  case 897: /* primary_rhs_expr: "tcp" close_scope_tcp  */
#line 4976 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14206 "parser_bison.c"
    break;

  case 898: /* primary_rhs_expr: "udp" close_scope_udp  */
#line 4983 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14217 "parser_bison.c"
    break;

  case 899: /* primary_rhs_expr: "udplite" close_scope_udplite  */
#line 4990 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14228 "parser_bison.c"
    break;

  case 900: /* primary_rhs_expr: "esp" close_scope_esp  */
#line 4997 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14239 "parser_bison.c"
    break;

  case 901: /* primary_rhs_expr: "ah" close_scope_ah  */
#line 5004 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14250 "parser_bison.c"
    break;

  case 902: /* primary_rhs_expr: "icmp" close_scope_icmp  */
#line 5011 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14261 "parser_bison.c"
    break;

  case 903: /* primary_rhs_expr: "igmp"  */
#line 5018 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14272 "parser_bison.c"
    break;

  case 904: /* primary_rhs_expr: "icmpv6" close_scope_icmp  */
#line 5025 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14283 "parser_bison.c"
    break;

  case 905: /* primary_rhs_expr: "gre" close_scope_gre  */
#line 5032 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_GRE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14294 "parser_bison.c"
    break;

  case 906: /* primary_rhs_expr: "comp" close_scope_comp  */
#line 5039 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14305 "parser_bison.c"
    break;

  case 907: /* primary_rhs_expr: "dccp" close_scope_dccp  */
#line 5046 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14316 "parser_bison.c"
    break;

  case 908: /* primary_rhs_expr: "sctp" close_scope_sctp  */
#line 5053 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14327 "parser_bison.c"
    break;

  case 909: /* primary_rhs_expr: "redirect" close_scope_nat  */
#line 5060 "parser_bison.y"
                        {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14338 "parser_bison.c"
    break;

  case 910: /* primary_rhs_expr: '(' basic_rhs_expr ')'  */
#line 5066 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 14344 "parser_bison.c"
    break;

  case 911: /* relational_op: "=="  */
#line 5069 "parser_bison.y"
                                                { (yyval.val) = OP_EQ; }
#line 14350 "parser_bison.c"
    break;

  case 912: /* relational_op: "!="  */
#line 5070 "parser_bison.y"
                                                { (yyval.val) = OP_NEQ; }
#line 14356 "parser_bison.c"
    break;

  case 913: /* relational_op: "<"  */
#line 5071 "parser_bison.y"
                                                { (yyval.val) = OP_LT; }
#line 14362 "parser_bison.c"
    break;

  case 914: /* relational_op: ">"  */
#line 5072 "parser_bison.y"
                                                { (yyval.val) = OP_GT; }
#line 14368 "parser_bison.c"
    break;

  case 915: /* relational_op: ">="  */
#line 5073 "parser_bison.y"
                                                { (yyval.val) = OP_GTE; }
#line 14374 "parser_bison.c"
    break;

  case 916: /* relational_op: "<="  */
#line 5074 "parser_bison.y"
                                                { (yyval.val) = OP_LTE; }
#line 14380 "parser_bison.c"
    break;

  case 917: /* relational_op: "!"  */
#line 5075 "parser_bison.y"
                                                { (yyval.val) = OP_NEG; }
#line 14386 "parser_bison.c"
    break;

  case 918: /* verdict_expr: "accept"  */
#line 5079 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 14394 "parser_bison.c"
    break;

  case 919: /* verdict_expr: "drop"  */
#line 5083 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 14402 "parser_bison.c"
    break;

  case 920: /* verdict_expr: "continue"  */
#line 5087 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 14410 "parser_bison.c"
    break;

  case 921: /* verdict_expr: "jump" chain_expr  */
#line 5091 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 14418 "parser_bison.c"
    break;

  case 922: /* verdict_expr: "goto" chain_expr  */
#line 5095 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 14426 "parser_bison.c"
    break;

  case 923: /* verdict_expr: "return"  */
#line 5099 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 14434 "parser_bison.c"
    break;

  case 925: /* chain_expr: identifier  */
#line 5106 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 14446 "parser_bison.c"
    break;

  case 926: /* meta_expr: "meta" meta_key close_scope_meta  */
#line 5116 "parser_bison.y"
                        {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[-1].val));
			}
#line 14454 "parser_bison.c"
    break;

  case 927: /* meta_expr: meta_key_unqualified  */
#line 5120 "parser_bison.y"
                        {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 14462 "parser_bison.c"
    break;

  case 928: /* meta_expr: "meta" "string" close_scope_meta  */
#line 5124 "parser_bison.y"
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
#line 14480 "parser_bison.c"
    break;

  case 931: /* meta_key_qualified: "length"  */
#line 5143 "parser_bison.y"
                                                { (yyval.val) = NFT_META_LEN; }
#line 14486 "parser_bison.c"
    break;

  case 932: /* meta_key_qualified: "protocol"  */
#line 5144 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PROTOCOL; }
#line 14492 "parser_bison.c"
    break;

  case 933: /* meta_key_qualified: "priority"  */
#line 5145 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PRIORITY; }
#line 14498 "parser_bison.c"
    break;

  case 934: /* meta_key_qualified: "random"  */
#line 5146 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PRANDOM; }
#line 14504 "parser_bison.c"
    break;

  case 935: /* meta_key_qualified: "secmark" close_scope_secmark  */
#line 5147 "parser_bison.y"
                                                            { (yyval.val) = NFT_META_SECMARK; }
#line 14510 "parser_bison.c"
    break;

  case 936: /* meta_key_unqualified: "mark"  */
#line 5150 "parser_bison.y"
                                                { (yyval.val) = NFT_META_MARK; }
#line 14516 "parser_bison.c"
    break;

  case 937: /* meta_key_unqualified: "iif"  */
#line 5151 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIF; }
#line 14522 "parser_bison.c"
    break;

  case 938: /* meta_key_unqualified: "iifname"  */
#line 5152 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFNAME; }
#line 14528 "parser_bison.c"
    break;

  case 939: /* meta_key_unqualified: "iiftype"  */
#line 5153 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFTYPE; }
#line 14534 "parser_bison.c"
    break;

  case 940: /* meta_key_unqualified: "oif"  */
#line 5154 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIF; }
#line 14540 "parser_bison.c"
    break;

  case 941: /* meta_key_unqualified: "oifname"  */
#line 5155 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFNAME; }
#line 14546 "parser_bison.c"
    break;

  case 942: /* meta_key_unqualified: "oiftype"  */
#line 5156 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFTYPE; }
#line 14552 "parser_bison.c"
    break;

  case 943: /* meta_key_unqualified: "skuid"  */
#line 5157 "parser_bison.y"
                                                { (yyval.val) = NFT_META_SKUID; }
#line 14558 "parser_bison.c"
    break;

  case 944: /* meta_key_unqualified: "skgid"  */
#line 5158 "parser_bison.y"
                                                { (yyval.val) = NFT_META_SKGID; }
#line 14564 "parser_bison.c"
    break;

  case 945: /* meta_key_unqualified: "nftrace"  */
#line 5159 "parser_bison.y"
                                                { (yyval.val) = NFT_META_NFTRACE; }
#line 14570 "parser_bison.c"
    break;

  case 946: /* meta_key_unqualified: "rtclassid"  */
#line 5160 "parser_bison.y"
                                                { (yyval.val) = NFT_META_RTCLASSID; }
#line 14576 "parser_bison.c"
    break;

  case 947: /* meta_key_unqualified: "ibriport"  */
#line 5161 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 14582 "parser_bison.c"
    break;

  case 948: /* meta_key_unqualified: "obriport"  */
#line 5162 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 14588 "parser_bison.c"
    break;

  case 949: /* meta_key_unqualified: "ibrname"  */
#line 5163 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 14594 "parser_bison.c"
    break;

  case 950: /* meta_key_unqualified: "obrname"  */
#line 5164 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 14600 "parser_bison.c"
    break;

  case 951: /* meta_key_unqualified: "pkttype"  */
#line 5165 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PKTTYPE; }
#line 14606 "parser_bison.c"
    break;

  case 952: /* meta_key_unqualified: "cpu"  */
#line 5166 "parser_bison.y"
                                                { (yyval.val) = NFT_META_CPU; }
#line 14612 "parser_bison.c"
    break;

  case 953: /* meta_key_unqualified: "iifgroup"  */
#line 5167 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFGROUP; }
#line 14618 "parser_bison.c"
    break;

  case 954: /* meta_key_unqualified: "oifgroup"  */
#line 5168 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFGROUP; }
#line 14624 "parser_bison.c"
    break;

  case 955: /* meta_key_unqualified: "cgroup"  */
#line 5169 "parser_bison.y"
                                                { (yyval.val) = NFT_META_CGROUP; }
#line 14630 "parser_bison.c"
    break;

  case 956: /* meta_key_unqualified: "ipsec" close_scope_ipsec  */
#line 5170 "parser_bison.y"
                                                          { (yyval.val) = NFT_META_SECPATH; }
#line 14636 "parser_bison.c"
    break;

  case 957: /* meta_key_unqualified: "time"  */
#line 5171 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_NS; }
#line 14642 "parser_bison.c"
    break;

  case 958: /* meta_key_unqualified: "day"  */
#line 5172 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_DAY; }
#line 14648 "parser_bison.c"
    break;

  case 959: /* meta_key_unqualified: "hour"  */
#line 5173 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_HOUR; }
#line 14654 "parser_bison.c"
    break;

  case 960: /* meta_stmt: "meta" meta_key "set" stmt_expr close_scope_meta  */
#line 5177 "parser_bison.y"
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
#line 14678 "parser_bison.c"
    break;

  case 961: /* meta_stmt: meta_key_unqualified "set" stmt_expr  */
#line 5197 "parser_bison.y"
                        {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 14686 "parser_bison.c"
    break;

  case 962: /* meta_stmt: "meta" "string" "set" stmt_expr close_scope_meta  */
#line 5201 "parser_bison.y"
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
#line 14704 "parser_bison.c"
    break;

  case 963: /* meta_stmt: "notrack"  */
#line 5215 "parser_bison.y"
                        {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 14712 "parser_bison.c"
    break;

  case 964: /* meta_stmt: "flow" "offload" "@" string close_scope_at  */
#line 5219 "parser_bison.y"
                        {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[-1].string));
			}
#line 14720 "parser_bison.c"
    break;

  case 965: /* meta_stmt: "flow" "add" "@" string close_scope_at  */
#line 5223 "parser_bison.y"
                        {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[-1].string));
			}
#line 14728 "parser_bison.c"
    break;

  case 966: /* socket_expr: "socket" socket_key close_scope_socket  */
#line 5229 "parser_bison.y"
                        {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 14736 "parser_bison.c"
    break;

  case 967: /* socket_expr: "socket" "cgroupv2" "level" "number" close_scope_socket  */
#line 5233 "parser_bison.y"
                        {
				(yyval.expr) = socket_expr_alloc(&(yyloc), NFT_SOCKET_CGROUPV2, (yyvsp[-1].val));
			}
#line 14744 "parser_bison.c"
    break;

  case 968: /* socket_key: "transparent"  */
#line 5238 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 14750 "parser_bison.c"
    break;

  case 969: /* socket_key: "mark"  */
#line 5239 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_MARK; }
#line 14756 "parser_bison.c"
    break;

  case 970: /* socket_key: "wildcard"  */
#line 5240 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_WILDCARD; }
#line 14762 "parser_bison.c"
    break;

  case 971: /* offset_opt: %empty  */
#line 5243 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 14768 "parser_bison.c"
    break;

  case 972: /* offset_opt: "offset" "number"  */
#line 5244 "parser_bison.y"
                                                { (yyval.val) = (yyvsp[0].val); }
#line 14774 "parser_bison.c"
    break;

  case 973: /* numgen_type: "inc"  */
#line 5247 "parser_bison.y"
                                                { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 14780 "parser_bison.c"
    break;

  case 974: /* numgen_type: "random"  */
#line 5248 "parser_bison.y"
                                                { (yyval.val) = NFT_NG_RANDOM; }
#line 14786 "parser_bison.c"
    break;

  case 975: /* numgen_expr: "numgen" numgen_type "mod" "number" offset_opt close_scope_numgen  */
#line 5252 "parser_bison.y"
                        {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 14794 "parser_bison.c"
    break;

  case 976: /* xfrm_spnum: "spnum" "number"  */
#line 5257 "parser_bison.y"
                                            { (yyval.val) = (yyvsp[0].val); }
#line 14800 "parser_bison.c"
    break;

  case 977: /* xfrm_spnum: %empty  */
#line 5258 "parser_bison.y"
                                            { (yyval.val) = 0; }
#line 14806 "parser_bison.c"
    break;

  case 978: /* xfrm_dir: "in"  */
#line 5261 "parser_bison.y"
                                        { (yyval.val) = XFRM_POLICY_IN; }
#line 14812 "parser_bison.c"
    break;

  case 979: /* xfrm_dir: "out"  */
#line 5262 "parser_bison.y"
                                        { (yyval.val) = XFRM_POLICY_OUT; }
#line 14818 "parser_bison.c"
    break;

  case 980: /* xfrm_state_key: "spi"  */
#line 5265 "parser_bison.y"
                                    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 14824 "parser_bison.c"
    break;

  case 981: /* xfrm_state_key: "reqid"  */
#line 5266 "parser_bison.y"
                                      { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 14830 "parser_bison.c"
    break;

  case 982: /* xfrm_state_proto_key: "daddr"  */
#line 5269 "parser_bison.y"
                                                { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 14836 "parser_bison.c"
    break;

  case 983: /* xfrm_state_proto_key: "saddr"  */
#line 5270 "parser_bison.y"
                                                { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 14842 "parser_bison.c"
    break;

  case 984: /* xfrm_expr: "ipsec" xfrm_dir xfrm_spnum xfrm_state_key close_scope_ipsec  */
#line 5274 "parser_bison.y"
                        {
				if ((yyvsp[-2].val) > 255) {
					erec_queue(error(&(yylsp[-2]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 14854 "parser_bison.c"
    break;

  case 985: /* xfrm_expr: "ipsec" xfrm_dir xfrm_spnum nf_key_proto xfrm_state_proto_key close_scope_ipsec  */
#line 5282 "parser_bison.y"
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
#line 14883 "parser_bison.c"
    break;

  case 986: /* hash_expr: "jhash" expr "mod" "number" "seed" "number" offset_opt close_scope_hash  */
#line 5309 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-4].val), true, (yyvsp[-2].val), (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-6].expr);
			}
#line 14892 "parser_bison.c"
    break;

  case 987: /* hash_expr: "jhash" expr "mod" "number" offset_opt close_scope_hash  */
#line 5314 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-4].expr);
			}
#line 14901 "parser_bison.c"
    break;

  case 988: /* hash_expr: "symhash" "mod" "number" offset_opt close_scope_hash  */
#line 5319 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_SYM);
			}
#line 14909 "parser_bison.c"
    break;

  case 989: /* nf_key_proto: "ip" close_scope_ip  */
#line 5324 "parser_bison.y"
                                                       { (yyval.val) = NFPROTO_IPV4; }
#line 14915 "parser_bison.c"
    break;

  case 990: /* nf_key_proto: "ip6" close_scope_ip6  */
#line 5325 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV6; }
#line 14921 "parser_bison.c"
    break;

  case 991: /* rt_expr: "rt" rt_key close_scope_rt  */
#line 5329 "parser_bison.y"
                        {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[-1].val), true);
			}
#line 14929 "parser_bison.c"
    break;

  case 992: /* rt_expr: "rt" nf_key_proto rt_key close_scope_rt  */
#line 5333 "parser_bison.y"
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
#line 14951 "parser_bison.c"
    break;

  case 993: /* rt_key: "classid"  */
#line 5352 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_CLASSID; }
#line 14957 "parser_bison.c"
    break;

  case 994: /* rt_key: "nexthop"  */
#line 5353 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 14963 "parser_bison.c"
    break;

  case 995: /* rt_key: "mtu"  */
#line 5354 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_TCPMSS; }
#line 14969 "parser_bison.c"
    break;

  case 996: /* rt_key: "ipsec" close_scope_ipsec  */
#line 5355 "parser_bison.y"
                                                          { (yyval.val) = NFT_RT_XFRM; }
#line 14975 "parser_bison.c"
    break;

  case 997: /* ct_expr: "ct" ct_key close_scope_ct  */
#line 5359 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), -1);
			}
#line 14983 "parser_bison.c"
    break;

  case 998: /* ct_expr: "ct" ct_dir ct_key_dir close_scope_ct  */
#line 5363 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 14991 "parser_bison.c"
    break;

  case 999: /* ct_expr: "ct" ct_dir ct_key_proto_field close_scope_ct  */
#line 5367 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 14999 "parser_bison.c"
    break;

  case 1000: /* ct_dir: "original"  */
#line 5372 "parser_bison.y"
                                                { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 15005 "parser_bison.c"
    break;

  case 1001: /* ct_dir: "reply"  */
#line 5373 "parser_bison.y"
                                                { (yyval.val) = IP_CT_DIR_REPLY; }
#line 15011 "parser_bison.c"
    break;

  case 1002: /* ct_key: "l3proto"  */
#line 5376 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 15017 "parser_bison.c"
    break;

  case 1003: /* ct_key: "protocol"  */
#line 5377 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTOCOL; }
#line 15023 "parser_bison.c"
    break;

  case 1004: /* ct_key: "mark"  */
#line 5378 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_MARK; }
#line 15029 "parser_bison.c"
    break;

  case 1005: /* ct_key: "state"  */
#line 5379 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_STATE; }
#line 15035 "parser_bison.c"
    break;

  case 1006: /* ct_key: "direction"  */
#line 5380 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DIRECTION; }
#line 15041 "parser_bison.c"
    break;

  case 1007: /* ct_key: "status"  */
#line 5381 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_STATUS; }
#line 15047 "parser_bison.c"
    break;

  case 1008: /* ct_key: "expiration"  */
#line 5382 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_EXPIRATION; }
#line 15053 "parser_bison.c"
    break;

  case 1009: /* ct_key: "helper"  */
#line 5383 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_HELPER; }
#line 15059 "parser_bison.c"
    break;

  case 1010: /* ct_key: "saddr"  */
#line 5384 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_SRC; }
#line 15065 "parser_bison.c"
    break;

  case 1011: /* ct_key: "daddr"  */
#line 5385 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DST; }
#line 15071 "parser_bison.c"
    break;

  case 1012: /* ct_key: "proto-src"  */
#line 5386 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 15077 "parser_bison.c"
    break;

  case 1013: /* ct_key: "proto-dst"  */
#line 5387 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_DST; }
#line 15083 "parser_bison.c"
    break;

  case 1014: /* ct_key: "label"  */
#line 5388 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_LABELS; }
#line 15089 "parser_bison.c"
    break;

  case 1015: /* ct_key: "event"  */
#line 5389 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_EVENTMASK; }
#line 15095 "parser_bison.c"
    break;

  case 1016: /* ct_key: "secmark" close_scope_secmark  */
#line 5390 "parser_bison.y"
                                                            { (yyval.val) = NFT_CT_SECMARK; }
#line 15101 "parser_bison.c"
    break;

  case 1017: /* ct_key: "id"  */
#line 5391 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_ID; }
#line 15107 "parser_bison.c"
    break;

  case 1019: /* ct_key_dir: "saddr"  */
#line 5395 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_SRC; }
#line 15113 "parser_bison.c"
    break;

  case 1020: /* ct_key_dir: "daddr"  */
#line 5396 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DST; }
#line 15119 "parser_bison.c"
    break;

  case 1021: /* ct_key_dir: "l3proto"  */
#line 5397 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 15125 "parser_bison.c"
    break;

  case 1022: /* ct_key_dir: "protocol"  */
#line 5398 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTOCOL; }
#line 15131 "parser_bison.c"
    break;

  case 1023: /* ct_key_dir: "proto-src"  */
#line 5399 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 15137 "parser_bison.c"
    break;

  case 1024: /* ct_key_dir: "proto-dst"  */
#line 5400 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_DST; }
#line 15143 "parser_bison.c"
    break;

  case 1026: /* ct_key_proto_field: "ip" "saddr" close_scope_ip  */
#line 5404 "parser_bison.y"
                                                               { (yyval.val) = NFT_CT_SRC_IP; }
#line 15149 "parser_bison.c"
    break;

  case 1027: /* ct_key_proto_field: "ip" "daddr" close_scope_ip  */
#line 5405 "parser_bison.y"
                                                               { (yyval.val) = NFT_CT_DST_IP; }
#line 15155 "parser_bison.c"
    break;

  case 1028: /* ct_key_proto_field: "ip6" "saddr" close_scope_ip6  */
#line 5406 "parser_bison.y"
                                                                { (yyval.val) = NFT_CT_SRC_IP6; }
#line 15161 "parser_bison.c"
    break;

  case 1029: /* ct_key_proto_field: "ip6" "daddr" close_scope_ip6  */
#line 5407 "parser_bison.y"
                                                                { (yyval.val) = NFT_CT_DST_IP6; }
#line 15167 "parser_bison.c"
    break;

  case 1030: /* ct_key_dir_optional: "bytes"  */
#line 5410 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_BYTES; }
#line 15173 "parser_bison.c"
    break;

  case 1031: /* ct_key_dir_optional: "packets"  */
#line 5411 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PKTS; }
#line 15179 "parser_bison.c"
    break;

  case 1032: /* ct_key_dir_optional: "avgpkt"  */
#line 5412 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_AVGPKT; }
#line 15185 "parser_bison.c"
    break;

  case 1033: /* ct_key_dir_optional: "zone"  */
#line 5413 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_ZONE; }
#line 15191 "parser_bison.c"
    break;

  case 1036: /* list_stmt_expr: symbol_stmt_expr "comma" symbol_stmt_expr  */
#line 5421 "parser_bison.y"
                        {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 15201 "parser_bison.c"
    break;

  case 1037: /* list_stmt_expr: list_stmt_expr "comma" symbol_stmt_expr  */
#line 5427 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 15211 "parser_bison.c"
    break;

  case 1038: /* ct_stmt: "ct" ct_key "set" stmt_expr close_scope_ct  */
#line 5435 "parser_bison.y"
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
#line 15228 "parser_bison.c"
    break;

  case 1039: /* ct_stmt: "ct" "timeout" "set" stmt_expr close_scope_ct  */
#line 5448 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);

			}
#line 15239 "parser_bison.c"
    break;

  case 1040: /* ct_stmt: "ct" "expectation" "set" stmt_expr close_scope_ct  */
#line 5455 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 15249 "parser_bison.c"
    break;

  case 1041: /* ct_stmt: "ct" ct_dir ct_key_dir_optional "set" stmt_expr close_scope_ct  */
#line 5461 "parser_bison.y"
                        {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].val), (yyvsp[-1].expr));
			}
#line 15257 "parser_bison.c"
    break;

  case 1042: /* payload_stmt: payload_expr "set" stmt_expr  */
#line 5467 "parser_bison.y"
                        {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 15268 "parser_bison.c"
    break;

  case 1065: /* payload_raw_expr: "@" payload_base_spec "comma" "number" "comma" "number" close_scope_at  */
#line 5500 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-5].val), (yyvsp[-3].val), (yyvsp[-1].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 15279 "parser_bison.c"
    break;

  case 1066: /* payload_base_spec: "ll"  */
#line 5508 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 15285 "parser_bison.c"
    break;

  case 1067: /* payload_base_spec: "nh"  */
#line 5509 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 15291 "parser_bison.c"
    break;

  case 1068: /* payload_base_spec: "th" close_scope_th  */
#line 5510 "parser_bison.y"
                                                                { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 15297 "parser_bison.c"
    break;

  case 1069: /* payload_base_spec: "string"  */
#line 5512 "parser_bison.y"
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
#line 15312 "parser_bison.c"
    break;

  case 1070: /* eth_hdr_expr: "ether" eth_hdr_field close_scope_eth  */
#line 5525 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[-1].val));
			}
#line 15320 "parser_bison.c"
    break;

  case 1071: /* eth_hdr_field: "saddr"  */
#line 5530 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_SADDR; }
#line 15326 "parser_bison.c"
    break;

  case 1072: /* eth_hdr_field: "daddr"  */
#line 5531 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_DADDR; }
#line 15332 "parser_bison.c"
    break;

  case 1073: /* eth_hdr_field: "type" close_scope_type  */
#line 5532 "parser_bison.y"
                                                                        { (yyval.val) = ETHHDR_TYPE; }
#line 15338 "parser_bison.c"
    break;

  case 1074: /* vlan_hdr_expr: "vlan" vlan_hdr_field close_scope_vlan  */
#line 5536 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[-1].val));
			}
#line 15346 "parser_bison.c"
    break;

  case 1075: /* vlan_hdr_field: "id"  */
#line 5541 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_VID; }
#line 15352 "parser_bison.c"
    break;

  case 1076: /* vlan_hdr_field: "cfi"  */
#line 5542 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_CFI; }
#line 15358 "parser_bison.c"
    break;

  case 1077: /* vlan_hdr_field: "dei"  */
#line 5543 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_DEI; }
#line 15364 "parser_bison.c"
    break;

  case 1078: /* vlan_hdr_field: "pcp"  */
#line 5544 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_PCP; }
#line 15370 "parser_bison.c"
    break;

  case 1079: /* vlan_hdr_field: "type" close_scope_type  */
#line 5545 "parser_bison.y"
                                                                        { (yyval.val) = VLANHDR_TYPE; }
#line 15376 "parser_bison.c"
    break;

  case 1080: /* arp_hdr_expr: "arp" arp_hdr_field close_scope_arp  */
#line 5549 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[-1].val));
			}
#line 15384 "parser_bison.c"
    break;

  case 1081: /* arp_hdr_field: "htype"  */
#line 5554 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_HRD; }
#line 15390 "parser_bison.c"
    break;

  case 1082: /* arp_hdr_field: "ptype"  */
#line 5555 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_PRO; }
#line 15396 "parser_bison.c"
    break;

  case 1083: /* arp_hdr_field: "hlen"  */
#line 5556 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_HLN; }
#line 15402 "parser_bison.c"
    break;

  case 1084: /* arp_hdr_field: "plen"  */
#line 5557 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_PLN; }
#line 15408 "parser_bison.c"
    break;

  case 1085: /* arp_hdr_field: "operation"  */
#line 5558 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_OP; }
#line 15414 "parser_bison.c"
    break;

  case 1086: /* arp_hdr_field: "saddr" "ether" close_scope_eth  */
#line 5559 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 15420 "parser_bison.c"
    break;

  case 1087: /* arp_hdr_field: "daddr" "ether" close_scope_eth  */
#line 5560 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 15426 "parser_bison.c"
    break;

  case 1088: /* arp_hdr_field: "saddr" "ip" close_scope_ip  */
#line 5561 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_SADDR_IP; }
#line 15432 "parser_bison.c"
    break;

  case 1089: /* arp_hdr_field: "daddr" "ip" close_scope_ip  */
#line 5562 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_DADDR_IP; }
#line 15438 "parser_bison.c"
    break;

  case 1090: /* ip_hdr_expr: "ip" ip_hdr_field close_scope_ip  */
#line 5566 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[-1].val));
			}
#line 15446 "parser_bison.c"
    break;

  case 1091: /* ip_hdr_expr: "ip" "option" ip_option_type ip_option_field close_scope_ip  */
#line 5570 "parser_bison.y"
                        {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val));
				if (!(yyval.expr)) {
					erec_queue(error(&(yylsp[-4]), "unknown ip option type/field"), state->msgs);
					YYERROR;
				}
			}
#line 15458 "parser_bison.c"
    break;

  case 1092: /* ip_hdr_expr: "ip" "option" ip_option_type close_scope_ip  */
#line 5578 "parser_bison.y"
                        {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), IPOPT_FIELD_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 15467 "parser_bison.c"
    break;

  case 1093: /* ip_hdr_field: "version"  */
#line 5584 "parser_bison.y"
                                                { (yyval.val) = IPHDR_VERSION; }
#line 15473 "parser_bison.c"
    break;

  case 1094: /* ip_hdr_field: "hdrlength"  */
#line 5585 "parser_bison.y"
                                                { (yyval.val) = IPHDR_HDRLENGTH; }
#line 15479 "parser_bison.c"
    break;

  case 1095: /* ip_hdr_field: "dscp"  */
#line 5586 "parser_bison.y"
                                                { (yyval.val) = IPHDR_DSCP; }
#line 15485 "parser_bison.c"
    break;

  case 1096: /* ip_hdr_field: "ecn"  */
#line 5587 "parser_bison.y"
                                                { (yyval.val) = IPHDR_ECN; }
#line 15491 "parser_bison.c"
    break;

  case 1097: /* ip_hdr_field: "length"  */
#line 5588 "parser_bison.y"
                                                { (yyval.val) = IPHDR_LENGTH; }
#line 15497 "parser_bison.c"
    break;

  case 1098: /* ip_hdr_field: "id"  */
#line 5589 "parser_bison.y"
                                                { (yyval.val) = IPHDR_ID; }
#line 15503 "parser_bison.c"
    break;

  case 1099: /* ip_hdr_field: "frag-off"  */
#line 5590 "parser_bison.y"
                                                { (yyval.val) = IPHDR_FRAG_OFF; }
#line 15509 "parser_bison.c"
    break;

  case 1100: /* ip_hdr_field: "ttl"  */
#line 5591 "parser_bison.y"
                                                { (yyval.val) = IPHDR_TTL; }
#line 15515 "parser_bison.c"
    break;

  case 1101: /* ip_hdr_field: "protocol"  */
#line 5592 "parser_bison.y"
                                                { (yyval.val) = IPHDR_PROTOCOL; }
#line 15521 "parser_bison.c"
    break;

  case 1102: /* ip_hdr_field: "checksum"  */
#line 5593 "parser_bison.y"
                                                { (yyval.val) = IPHDR_CHECKSUM; }
#line 15527 "parser_bison.c"
    break;

  case 1103: /* ip_hdr_field: "saddr"  */
#line 5594 "parser_bison.y"
                                                { (yyval.val) = IPHDR_SADDR; }
#line 15533 "parser_bison.c"
    break;

  case 1104: /* ip_hdr_field: "daddr"  */
#line 5595 "parser_bison.y"
                                                { (yyval.val) = IPHDR_DADDR; }
#line 15539 "parser_bison.c"
    break;

  case 1105: /* ip_option_type: "lsrr"  */
#line 5598 "parser_bison.y"
                                                { (yyval.val) = IPOPT_LSRR; }
#line 15545 "parser_bison.c"
    break;

  case 1106: /* ip_option_type: "rr"  */
#line 5599 "parser_bison.y"
                                                { (yyval.val) = IPOPT_RR; }
#line 15551 "parser_bison.c"
    break;

  case 1107: /* ip_option_type: "ssrr"  */
#line 5600 "parser_bison.y"
                                                { (yyval.val) = IPOPT_SSRR; }
#line 15557 "parser_bison.c"
    break;

  case 1108: /* ip_option_type: "ra"  */
#line 5601 "parser_bison.y"
                                                { (yyval.val) = IPOPT_RA; }
#line 15563 "parser_bison.c"
    break;

  case 1109: /* ip_option_field: "type" close_scope_type  */
#line 5604 "parser_bison.y"
                                                                        { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 15569 "parser_bison.c"
    break;

  case 1110: /* ip_option_field: "length"  */
#line 5605 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 15575 "parser_bison.c"
    break;

  case 1111: /* ip_option_field: "value"  */
#line 5606 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 15581 "parser_bison.c"
    break;

  case 1112: /* ip_option_field: "ptr"  */
#line 5607 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_PTR; }
#line 15587 "parser_bison.c"
    break;

  case 1113: /* ip_option_field: "addr"  */
#line 5608 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 15593 "parser_bison.c"
    break;

  case 1114: /* icmp_hdr_expr: "icmp" icmp_hdr_field close_scope_icmp  */
#line 5612 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[-1].val));
			}
#line 15601 "parser_bison.c"
    break;

  case 1115: /* icmp_hdr_field: "type" close_scope_type  */
#line 5617 "parser_bison.y"
                                                                        { (yyval.val) = ICMPHDR_TYPE; }
#line 15607 "parser_bison.c"
    break;

  case 1116: /* icmp_hdr_field: "code"  */
#line 5618 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_CODE; }
#line 15613 "parser_bison.c"
    break;

  case 1117: /* icmp_hdr_field: "checksum"  */
#line 5619 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 15619 "parser_bison.c"
    break;

  case 1118: /* icmp_hdr_field: "id"  */
#line 5620 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_ID; }
#line 15625 "parser_bison.c"
    break;

  case 1119: /* icmp_hdr_field: "seq"  */
#line 5621 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_SEQ; }
#line 15631 "parser_bison.c"
    break;

  case 1120: /* icmp_hdr_field: "gateway"  */
#line 5622 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_GATEWAY; }
#line 15637 "parser_bison.c"
    break;

  case 1121: /* icmp_hdr_field: "mtu"  */
#line 5623 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_MTU; }
#line 15643 "parser_bison.c"
    break;

  case 1122: /* igmp_hdr_expr: "igmp" igmp_hdr_field close_scope_igmp  */
#line 5627 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[-1].val));
			}
#line 15651 "parser_bison.c"
    break;

  case 1123: /* igmp_hdr_field: "type" close_scope_type  */
#line 5632 "parser_bison.y"
                                                                        { (yyval.val) = IGMPHDR_TYPE; }
#line 15657 "parser_bison.c"
    break;

  case 1124: /* igmp_hdr_field: "checksum"  */
#line 5633 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 15663 "parser_bison.c"
    break;

  case 1125: /* igmp_hdr_field: "mrt"  */
#line 5634 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_MRT; }
#line 15669 "parser_bison.c"
    break;

  case 1126: /* igmp_hdr_field: "group"  */
#line 5635 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_GROUP; }
#line 15675 "parser_bison.c"
    break;

  case 1127: /* ip6_hdr_expr: "ip6" ip6_hdr_field close_scope_ip6  */
#line 5639 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[-1].val));
			}
#line 15683 "parser_bison.c"
    break;

  case 1128: /* ip6_hdr_field: "version"  */
#line 5644 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_VERSION; }
#line 15689 "parser_bison.c"
    break;

  case 1129: /* ip6_hdr_field: "dscp"  */
#line 5645 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_DSCP; }
#line 15695 "parser_bison.c"
    break;

  case 1130: /* ip6_hdr_field: "ecn"  */
#line 5646 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_ECN; }
#line 15701 "parser_bison.c"
    break;

  case 1131: /* ip6_hdr_field: "flowlabel"  */
#line 5647 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 15707 "parser_bison.c"
    break;

  case 1132: /* ip6_hdr_field: "length"  */
#line 5648 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_LENGTH; }
#line 15713 "parser_bison.c"
    break;

  case 1133: /* ip6_hdr_field: "nexthdr"  */
#line 5649 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_NEXTHDR; }
#line 15719 "parser_bison.c"
    break;

  case 1134: /* ip6_hdr_field: "hoplimit"  */
#line 5650 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 15725 "parser_bison.c"
    break;

  case 1135: /* ip6_hdr_field: "saddr"  */
#line 5651 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_SADDR; }
#line 15731 "parser_bison.c"
    break;

  case 1136: /* ip6_hdr_field: "daddr"  */
#line 5652 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_DADDR; }
#line 15737 "parser_bison.c"
    break;

  case 1137: /* icmp6_hdr_expr: "icmpv6" icmp6_hdr_field close_scope_icmp  */
#line 5655 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[-1].val));
			}
#line 15745 "parser_bison.c"
    break;

  case 1138: /* icmp6_hdr_field: "type" close_scope_type  */
#line 5660 "parser_bison.y"
                                                                        { (yyval.val) = ICMP6HDR_TYPE; }
#line 15751 "parser_bison.c"
    break;

  case 1139: /* icmp6_hdr_field: "code"  */
#line 5661 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_CODE; }
#line 15757 "parser_bison.c"
    break;

  case 1140: /* icmp6_hdr_field: "checksum"  */
#line 5662 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 15763 "parser_bison.c"
    break;

  case 1141: /* icmp6_hdr_field: "param-problem"  */
#line 5663 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_PPTR; }
#line 15769 "parser_bison.c"
    break;

  case 1142: /* icmp6_hdr_field: "mtu"  */
#line 5664 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_MTU; }
#line 15775 "parser_bison.c"
    break;

  case 1143: /* icmp6_hdr_field: "id"  */
#line 5665 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_ID; }
#line 15781 "parser_bison.c"
    break;

  case 1144: /* icmp6_hdr_field: "seq"  */
#line 5666 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_SEQ; }
#line 15787 "parser_bison.c"
    break;

  case 1145: /* icmp6_hdr_field: "max-delay"  */
#line 5667 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 15793 "parser_bison.c"
    break;

  case 1146: /* auth_hdr_expr: "ah" auth_hdr_field close_scope_ah  */
#line 5671 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[-1].val));
			}
#line 15801 "parser_bison.c"
    break;

  case 1147: /* auth_hdr_field: "nexthdr"  */
#line 5676 "parser_bison.y"
                                                { (yyval.val) = AHHDR_NEXTHDR; }
#line 15807 "parser_bison.c"
    break;

  case 1148: /* auth_hdr_field: "hdrlength"  */
#line 5677 "parser_bison.y"
                                                { (yyval.val) = AHHDR_HDRLENGTH; }
#line 15813 "parser_bison.c"
    break;

  case 1149: /* auth_hdr_field: "reserved"  */
#line 5678 "parser_bison.y"
                                                { (yyval.val) = AHHDR_RESERVED; }
#line 15819 "parser_bison.c"
    break;

  case 1150: /* auth_hdr_field: "spi"  */
#line 5679 "parser_bison.y"
                                                { (yyval.val) = AHHDR_SPI; }
#line 15825 "parser_bison.c"
    break;

  case 1151: /* auth_hdr_field: "seq"  */
#line 5680 "parser_bison.y"
                                                { (yyval.val) = AHHDR_SEQUENCE; }
#line 15831 "parser_bison.c"
    break;

  case 1152: /* esp_hdr_expr: "esp" esp_hdr_field close_scope_esp  */
#line 5684 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[-1].val));
			}
#line 15839 "parser_bison.c"
    break;

  case 1153: /* esp_hdr_field: "spi"  */
#line 5689 "parser_bison.y"
                                                { (yyval.val) = ESPHDR_SPI; }
#line 15845 "parser_bison.c"
    break;

  case 1154: /* esp_hdr_field: "seq"  */
#line 5690 "parser_bison.y"
                                                { (yyval.val) = ESPHDR_SEQUENCE; }
#line 15851 "parser_bison.c"
    break;

  case 1155: /* comp_hdr_expr: "comp" comp_hdr_field close_scope_comp  */
#line 5694 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[-1].val));
			}
#line 15859 "parser_bison.c"
    break;

  case 1156: /* comp_hdr_field: "nexthdr"  */
#line 5699 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_NEXTHDR; }
#line 15865 "parser_bison.c"
    break;

  case 1157: /* comp_hdr_field: "flags"  */
#line 5700 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_FLAGS; }
#line 15871 "parser_bison.c"
    break;

  case 1158: /* comp_hdr_field: "cpi"  */
#line 5701 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_CPI; }
#line 15877 "parser_bison.c"
    break;

  case 1159: /* udp_hdr_expr: "udp" udp_hdr_field close_scope_udp  */
#line 5705 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[-1].val));
			}
#line 15885 "parser_bison.c"
    break;

  case 1160: /* udp_hdr_field: "sport"  */
#line 5710 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_SPORT; }
#line 15891 "parser_bison.c"
    break;

  case 1161: /* udp_hdr_field: "dport"  */
#line 5711 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_DPORT; }
#line 15897 "parser_bison.c"
    break;

  case 1162: /* udp_hdr_field: "length"  */
#line 5712 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_LENGTH; }
#line 15903 "parser_bison.c"
    break;

  case 1163: /* udp_hdr_field: "checksum"  */
#line 5713 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_CHECKSUM; }
#line 15909 "parser_bison.c"
    break;

  case 1164: /* udplite_hdr_expr: "udplite" udplite_hdr_field close_scope_udplite  */
#line 5717 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[-1].val));
			}
#line 15917 "parser_bison.c"
    break;

  case 1165: /* udplite_hdr_field: "sport"  */
#line 5722 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_SPORT; }
#line 15923 "parser_bison.c"
    break;

  case 1166: /* udplite_hdr_field: "dport"  */
#line 5723 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_DPORT; }
#line 15929 "parser_bison.c"
    break;

  case 1167: /* udplite_hdr_field: "csumcov"  */
#line 5724 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_LENGTH; }
#line 15935 "parser_bison.c"
    break;

  case 1168: /* udplite_hdr_field: "checksum"  */
#line 5725 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_CHECKSUM; }
#line 15941 "parser_bison.c"
    break;

  case 1169: /* tcp_hdr_expr: "tcp" tcp_hdr_field  */
#line 5729 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 15949 "parser_bison.c"
    break;

  case 1170: /* tcp_hdr_expr: "tcp" "option" tcp_hdr_option_type  */
#line 5733 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPT_COMMON_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 15958 "parser_bison.c"
    break;

  case 1171: /* tcp_hdr_expr: "tcp" "option" tcp_hdr_option_kind_and_field  */
#line 5738 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].tcp_kind_field).kind, (yyvsp[0].tcp_kind_field).field);
			}
#line 15966 "parser_bison.c"
    break;

  case 1172: /* tcp_hdr_expr: "tcp" "option" "@" close_scope_at tcp_hdr_option_type "comma" "number" "comma" "number"  */
#line 5742 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-4].val), 0);
				tcpopt_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val), 0);
			}
#line 15975 "parser_bison.c"
    break;

  case 1192: /* vxlan_hdr_expr: "vxlan" vxlan_hdr_field  */
#line 5774 "parser_bison.y"
                        {
				struct expr *expr;

				expr = payload_expr_alloc(&(yyloc), &proto_vxlan, (yyvsp[0].val));
				expr->payload.inner_desc = &proto_vxlan;
				(yyval.expr) = expr;
			}
#line 15987 "parser_bison.c"
    break;

  case 1193: /* vxlan_hdr_expr: "vxlan" inner_expr  */
#line 5782 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->location = (yyloc);
				(yyval.expr)->payload.inner_desc = &proto_vxlan;
			}
#line 15997 "parser_bison.c"
    break;

  case 1194: /* vxlan_hdr_field: "vni"  */
#line 5789 "parser_bison.y"
                                                        { (yyval.val) = VXLANHDR_VNI; }
#line 16003 "parser_bison.c"
    break;

  case 1195: /* vxlan_hdr_field: "flags"  */
#line 5790 "parser_bison.y"
                                                        { (yyval.val) = VXLANHDR_FLAGS; }
#line 16009 "parser_bison.c"
    break;

  case 1196: /* geneve_hdr_expr: "geneve" geneve_hdr_field  */
#line 5794 "parser_bison.y"
                        {
				struct expr *expr;

				expr = payload_expr_alloc(&(yyloc), &proto_geneve, (yyvsp[0].val));
				expr->payload.inner_desc = &proto_geneve;
				(yyval.expr) = expr;
			}
#line 16021 "parser_bison.c"
    break;

  case 1197: /* geneve_hdr_expr: "geneve" inner_expr  */
#line 5802 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->location = (yyloc);
				(yyval.expr)->payload.inner_desc = &proto_geneve;
			}
#line 16031 "parser_bison.c"
    break;

  case 1198: /* geneve_hdr_field: "vni"  */
#line 5809 "parser_bison.y"
                                                        { (yyval.val) = GNVHDR_VNI; }
#line 16037 "parser_bison.c"
    break;

  case 1199: /* geneve_hdr_field: "type"  */
#line 5810 "parser_bison.y"
                                                        { (yyval.val) = GNVHDR_TYPE; }
#line 16043 "parser_bison.c"
    break;

  case 1200: /* gre_hdr_expr: "gre" gre_hdr_field close_scope_gre  */
#line 5814 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_gre, (yyvsp[-1].val));
			}
#line 16051 "parser_bison.c"
    break;

  case 1201: /* gre_hdr_expr: "gre" close_scope_gre inner_inet_expr  */
#line 5818 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->payload.inner_desc = &proto_gre;
			}
#line 16060 "parser_bison.c"
    break;

  case 1202: /* gre_hdr_field: "version"  */
#line 5824 "parser_bison.y"
                                                        { (yyval.val) = GREHDR_VERSION;	}
#line 16066 "parser_bison.c"
    break;

  case 1203: /* gre_hdr_field: "flags"  */
#line 5825 "parser_bison.y"
                                                        { (yyval.val) = GREHDR_FLAGS; }
#line 16072 "parser_bison.c"
    break;

  case 1204: /* gre_hdr_field: "protocol"  */
#line 5826 "parser_bison.y"
                                                        { (yyval.val) = GREHDR_PROTOCOL; }
#line 16078 "parser_bison.c"
    break;

  case 1205: /* gretap_hdr_expr: "gretap" close_scope_gre inner_expr  */
#line 5830 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->payload.inner_desc = &proto_gretap;
			}
#line 16087 "parser_bison.c"
    break;

  case 1206: /* optstrip_stmt: "reset" "tcp" "option" tcp_hdr_option_type close_scope_tcp  */
#line 5837 "parser_bison.y"
                        {
				(yyval.stmt) = optstrip_stmt_alloc(&(yyloc), tcpopt_expr_alloc(&(yyloc),
										(yyvsp[-1].val), TCPOPT_COMMON_KIND));
			}
#line 16096 "parser_bison.c"
    break;

  case 1207: /* tcp_hdr_field: "sport"  */
#line 5843 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_SPORT; }
#line 16102 "parser_bison.c"
    break;

  case 1208: /* tcp_hdr_field: "dport"  */
#line 5844 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_DPORT; }
#line 16108 "parser_bison.c"
    break;

  case 1209: /* tcp_hdr_field: "seq"  */
#line 5845 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_SEQ; }
#line 16114 "parser_bison.c"
    break;

  case 1210: /* tcp_hdr_field: "ackseq"  */
#line 5846 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_ACKSEQ; }
#line 16120 "parser_bison.c"
    break;

  case 1211: /* tcp_hdr_field: "doff"  */
#line 5847 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_DOFF; }
#line 16126 "parser_bison.c"
    break;

  case 1212: /* tcp_hdr_field: "reserved"  */
#line 5848 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_RESERVED; }
#line 16132 "parser_bison.c"
    break;

  case 1213: /* tcp_hdr_field: "flags"  */
#line 5849 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_FLAGS; }
#line 16138 "parser_bison.c"
    break;

  case 1214: /* tcp_hdr_field: "window"  */
#line 5850 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_WINDOW; }
#line 16144 "parser_bison.c"
    break;

  case 1215: /* tcp_hdr_field: "checksum"  */
#line 5851 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_CHECKSUM; }
#line 16150 "parser_bison.c"
    break;

  case 1216: /* tcp_hdr_field: "urgptr"  */
#line 5852 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_URGPTR; }
#line 16156 "parser_bison.c"
    break;

  case 1217: /* tcp_hdr_option_kind_and_field: "mss" tcpopt_field_maxseg  */
#line 5856 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_MAXSEG, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16165 "parser_bison.c"
    break;

  case 1218: /* tcp_hdr_option_kind_and_field: tcp_hdr_option_sack tcpopt_field_sack  */
#line 5861 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = (yyvsp[-1].val), .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16174 "parser_bison.c"
    break;

  case 1219: /* tcp_hdr_option_kind_and_field: "window" tcpopt_field_window  */
#line 5866 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_WINDOW, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16183 "parser_bison.c"
    break;

  case 1220: /* tcp_hdr_option_kind_and_field: "timestamp" tcpopt_field_tsopt  */
#line 5871 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_TIMESTAMP, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16192 "parser_bison.c"
    break;

  case 1221: /* tcp_hdr_option_kind_and_field: tcp_hdr_option_type "length"  */
#line 5876 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = (yyvsp[-1].val), .field = TCPOPT_COMMON_LENGTH };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16201 "parser_bison.c"
    break;

  case 1222: /* tcp_hdr_option_kind_and_field: "mptcp" tcpopt_field_mptcp  */
#line 5881 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_MPTCP, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16210 "parser_bison.c"
    break;

  case 1223: /* tcp_hdr_option_sack: "sack"  */
#line 5887 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK; }
#line 16216 "parser_bison.c"
    break;

  case 1224: /* tcp_hdr_option_sack: "sack0"  */
#line 5888 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK; }
#line 16222 "parser_bison.c"
    break;

  case 1225: /* tcp_hdr_option_sack: "sack1"  */
#line 5889 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK1; }
#line 16228 "parser_bison.c"
    break;

  case 1226: /* tcp_hdr_option_sack: "sack2"  */
#line 5890 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK2; }
#line 16234 "parser_bison.c"
    break;

  case 1227: /* tcp_hdr_option_sack: "sack3"  */
#line 5891 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK3; }
#line 16240 "parser_bison.c"
    break;

  case 1228: /* tcp_hdr_option_type: "echo"  */
#line 5894 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_ECHO; }
#line 16246 "parser_bison.c"
    break;

  case 1229: /* tcp_hdr_option_type: "eol"  */
#line 5895 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_EOL; }
#line 16252 "parser_bison.c"
    break;

  case 1230: /* tcp_hdr_option_type: "fastopen"  */
#line 5896 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_FASTOPEN; }
#line 16258 "parser_bison.c"
    break;

  case 1231: /* tcp_hdr_option_type: "md5sig"  */
#line 5897 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MD5SIG; }
#line 16264 "parser_bison.c"
    break;

  case 1232: /* tcp_hdr_option_type: "mptcp"  */
#line 5898 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MPTCP; }
#line 16270 "parser_bison.c"
    break;

  case 1233: /* tcp_hdr_option_type: "mss"  */
#line 5899 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MAXSEG; }
#line 16276 "parser_bison.c"
    break;

  case 1234: /* tcp_hdr_option_type: "nop"  */
#line 5900 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_NOP; }
#line 16282 "parser_bison.c"
    break;

  case 1235: /* tcp_hdr_option_type: "sack-permitted"  */
#line 5901 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_SACK_PERMITTED; }
#line 16288 "parser_bison.c"
    break;

  case 1236: /* tcp_hdr_option_type: "timestamp"  */
#line 5902 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_TIMESTAMP; }
#line 16294 "parser_bison.c"
    break;

  case 1237: /* tcp_hdr_option_type: "window"  */
#line 5903 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_WINDOW; }
#line 16300 "parser_bison.c"
    break;

  case 1238: /* tcp_hdr_option_type: tcp_hdr_option_sack  */
#line 5904 "parser_bison.y"
                                                        { (yyval.val) = (yyvsp[0].val); }
#line 16306 "parser_bison.c"
    break;

  case 1239: /* tcp_hdr_option_type: "number"  */
#line 5905 "parser_bison.y"
                                                        {
				if ((yyvsp[0].val) > 255) {
					erec_queue(error(&(yylsp[0]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[0].val);
			}
#line 16318 "parser_bison.c"
    break;

  case 1240: /* tcpopt_field_sack: "left"  */
#line 5914 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_SACK_LEFT; }
#line 16324 "parser_bison.c"
    break;

  case 1241: /* tcpopt_field_sack: "right"  */
#line 5915 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_SACK_RIGHT; }
#line 16330 "parser_bison.c"
    break;

  case 1242: /* tcpopt_field_window: "count"  */
#line 5918 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_WINDOW_COUNT; }
#line 16336 "parser_bison.c"
    break;

  case 1243: /* tcpopt_field_tsopt: "tsval"  */
#line 5921 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_TS_TSVAL; }
#line 16342 "parser_bison.c"
    break;

  case 1244: /* tcpopt_field_tsopt: "tsecr"  */
#line 5922 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_TS_TSECR; }
#line 16348 "parser_bison.c"
    break;

  case 1245: /* tcpopt_field_maxseg: "size"  */
#line 5925 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_MAXSEG_SIZE; }
#line 16354 "parser_bison.c"
    break;

  case 1246: /* tcpopt_field_mptcp: "subtype"  */
#line 5928 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_MPTCP_SUBTYPE; }
#line 16360 "parser_bison.c"
    break;

  case 1247: /* dccp_hdr_expr: "dccp" dccp_hdr_field close_scope_dccp  */
#line 5932 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[-1].val));
			}
#line 16368 "parser_bison.c"
    break;

  case 1248: /* dccp_hdr_field: "sport"  */
#line 5937 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_SPORT; }
#line 16374 "parser_bison.c"
    break;

  case 1249: /* dccp_hdr_field: "dport"  */
#line 5938 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_DPORT; }
#line 16380 "parser_bison.c"
    break;

  case 1250: /* dccp_hdr_field: "type" close_scope_type  */
#line 5939 "parser_bison.y"
                                                                        { (yyval.val) = DCCPHDR_TYPE; }
#line 16386 "parser_bison.c"
    break;

  case 1251: /* sctp_chunk_type: "data"  */
#line 5942 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_DATA; }
#line 16392 "parser_bison.c"
    break;

  case 1252: /* sctp_chunk_type: "init"  */
#line 5943 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_INIT; }
#line 16398 "parser_bison.c"
    break;

  case 1253: /* sctp_chunk_type: "init-ack"  */
#line 5944 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_INIT_ACK; }
#line 16404 "parser_bison.c"
    break;

  case 1254: /* sctp_chunk_type: "sack"  */
#line 5945 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SACK; }
#line 16410 "parser_bison.c"
    break;

  case 1255: /* sctp_chunk_type: "heartbeat"  */
#line 5946 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT; }
#line 16416 "parser_bison.c"
    break;

  case 1256: /* sctp_chunk_type: "heartbeat-ack"  */
#line 5947 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT_ACK; }
#line 16422 "parser_bison.c"
    break;

  case 1257: /* sctp_chunk_type: "abort"  */
#line 5948 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ABORT; }
#line 16428 "parser_bison.c"
    break;

  case 1258: /* sctp_chunk_type: "shutdown"  */
#line 5949 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN; }
#line 16434 "parser_bison.c"
    break;

  case 1259: /* sctp_chunk_type: "shutdown-ack"  */
#line 5950 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_ACK; }
#line 16440 "parser_bison.c"
    break;

  case 1260: /* sctp_chunk_type: "error"  */
#line 5951 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ERROR; }
#line 16446 "parser_bison.c"
    break;

  case 1261: /* sctp_chunk_type: "cookie-echo"  */
#line 5952 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ECHO; }
#line 16452 "parser_bison.c"
    break;

  case 1262: /* sctp_chunk_type: "cookie-ack"  */
#line 5953 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ACK; }
#line 16458 "parser_bison.c"
    break;

  case 1263: /* sctp_chunk_type: "ecne"  */
#line 5954 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ECNE; }
#line 16464 "parser_bison.c"
    break;

  case 1264: /* sctp_chunk_type: "cwr"  */
#line 5955 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_CWR; }
#line 16470 "parser_bison.c"
    break;

  case 1265: /* sctp_chunk_type: "shutdown-complete"  */
#line 5956 "parser_bison.y"
                                                  { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_COMPLETE; }
#line 16476 "parser_bison.c"
    break;

  case 1266: /* sctp_chunk_type: "asconf-ack"  */
#line 5957 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF_ACK; }
#line 16482 "parser_bison.c"
    break;

  case 1267: /* sctp_chunk_type: "forward-tsn"  */
#line 5958 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_FORWARD_TSN; }
#line 16488 "parser_bison.c"
    break;

  case 1268: /* sctp_chunk_type: "asconf"  */
#line 5959 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF; }
#line 16494 "parser_bison.c"
    break;

  case 1269: /* sctp_chunk_common_field: "type" close_scope_type  */
#line 5962 "parser_bison.y"
                                                                { (yyval.val) = SCTP_CHUNK_COMMON_TYPE; }
#line 16500 "parser_bison.c"
    break;

  case 1270: /* sctp_chunk_common_field: "flags"  */
#line 5963 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_FLAGS; }
#line 16506 "parser_bison.c"
    break;

  case 1271: /* sctp_chunk_common_field: "length"  */
#line 5964 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_LENGTH; }
#line 16512 "parser_bison.c"
    break;

  case 1272: /* sctp_chunk_data_field: "tsn"  */
#line 5967 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_TSN; }
#line 16518 "parser_bison.c"
    break;

  case 1273: /* sctp_chunk_data_field: "stream"  */
#line 5968 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_STREAM; }
#line 16524 "parser_bison.c"
    break;

  case 1274: /* sctp_chunk_data_field: "ssn"  */
#line 5969 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_SSN; }
#line 16530 "parser_bison.c"
    break;

  case 1275: /* sctp_chunk_data_field: "ppid"  */
#line 5970 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_PPID; }
#line 16536 "parser_bison.c"
    break;

  case 1276: /* sctp_chunk_init_field: "init-tag"  */
#line 5973 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_TAG; }
#line 16542 "parser_bison.c"
    break;

  case 1277: /* sctp_chunk_init_field: "a-rwnd"  */
#line 5974 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_RWND; }
#line 16548 "parser_bison.c"
    break;

  case 1278: /* sctp_chunk_init_field: "num-outbound-streams"  */
#line 5975 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_OSTREAMS; }
#line 16554 "parser_bison.c"
    break;

  case 1279: /* sctp_chunk_init_field: "num-inbound-streams"  */
#line 5976 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_ISTREAMS; }
#line 16560 "parser_bison.c"
    break;

  case 1280: /* sctp_chunk_init_field: "initial-tsn"  */
#line 5977 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_TSN; }
#line 16566 "parser_bison.c"
    break;

  case 1281: /* sctp_chunk_sack_field: "cum-tsn-ack"  */
#line 5980 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_CTSN_ACK; }
#line 16572 "parser_bison.c"
    break;

  case 1282: /* sctp_chunk_sack_field: "a-rwnd"  */
#line 5981 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_RWND; }
#line 16578 "parser_bison.c"
    break;

  case 1283: /* sctp_chunk_sack_field: "num-gap-ack-blocks"  */
#line 5982 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_GACK_BLOCKS; }
#line 16584 "parser_bison.c"
    break;

  case 1284: /* sctp_chunk_sack_field: "num-dup-tsns"  */
#line 5983 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_DUP_TSNS; }
#line 16590 "parser_bison.c"
    break;

  case 1285: /* sctp_chunk_alloc: sctp_chunk_type  */
#line 5987 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[0].val), SCTP_CHUNK_COMMON_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 16599 "parser_bison.c"
    break;

  case 1286: /* sctp_chunk_alloc: sctp_chunk_type sctp_chunk_common_field  */
#line 5992 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 16607 "parser_bison.c"
    break;

  case 1287: /* sctp_chunk_alloc: "data" sctp_chunk_data_field  */
#line 5996 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_DATA, (yyvsp[0].val));
			}
#line 16615 "parser_bison.c"
    break;

  case 1288: /* sctp_chunk_alloc: "init" sctp_chunk_init_field  */
#line 6000 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT, (yyvsp[0].val));
			}
#line 16623 "parser_bison.c"
    break;

  case 1289: /* sctp_chunk_alloc: "init-ack" sctp_chunk_init_field  */
#line 6004 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT_ACK, (yyvsp[0].val));
			}
#line 16631 "parser_bison.c"
    break;

  case 1290: /* sctp_chunk_alloc: "sack" sctp_chunk_sack_field  */
#line 6008 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SACK, (yyvsp[0].val));
			}
#line 16639 "parser_bison.c"
    break;

  case 1291: /* sctp_chunk_alloc: "shutdown" "cum-tsn-ack"  */
#line 6012 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SHUTDOWN,
							   SCTP_CHUNK_SHUTDOWN_CTSN_ACK);
			}
#line 16648 "parser_bison.c"
    break;

  case 1292: /* sctp_chunk_alloc: "ecne" "lowest-tsn"  */
#line 6017 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ECNE,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 16657 "parser_bison.c"
    break;

  case 1293: /* sctp_chunk_alloc: "cwr" "lowest-tsn"  */
#line 6022 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_CWR,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 16666 "parser_bison.c"
    break;

  case 1294: /* sctp_chunk_alloc: "asconf-ack" "seqno"  */
#line 6027 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF_ACK,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 16675 "parser_bison.c"
    break;

  case 1295: /* sctp_chunk_alloc: "forward-tsn" "new-cum-tsn"  */
#line 6032 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_FORWARD_TSN,
							   SCTP_CHUNK_FORWARD_TSN_NCTSN);
			}
#line 16684 "parser_bison.c"
    break;

  case 1296: /* sctp_chunk_alloc: "asconf" "seqno"  */
#line 6037 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 16693 "parser_bison.c"
    break;

  case 1297: /* sctp_hdr_expr: "sctp" sctp_hdr_field close_scope_sctp  */
#line 6044 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[-1].val));
			}
#line 16701 "parser_bison.c"
    break;

  case 1298: /* sctp_hdr_expr: "sctp" "chunk" sctp_chunk_alloc close_scope_sctp_chunk close_scope_sctp  */
#line 6048 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 16709 "parser_bison.c"
    break;

  case 1299: /* sctp_hdr_field: "sport"  */
#line 6053 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_SPORT; }
#line 16715 "parser_bison.c"
    break;

  case 1300: /* sctp_hdr_field: "dport"  */
#line 6054 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_DPORT; }
#line 16721 "parser_bison.c"
    break;

  case 1301: /* sctp_hdr_field: "vtag"  */
#line 6055 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_VTAG; }
#line 16727 "parser_bison.c"
    break;

  case 1302: /* sctp_hdr_field: "checksum"  */
#line 6056 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 16733 "parser_bison.c"
    break;

  case 1303: /* th_hdr_expr: "th" th_hdr_field close_scope_th  */
#line 6060 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[-1].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 16743 "parser_bison.c"
    break;

  case 1304: /* th_hdr_field: "sport"  */
#line 6067 "parser_bison.y"
                                                { (yyval.val) = THDR_SPORT; }
#line 16749 "parser_bison.c"
    break;

  case 1305: /* th_hdr_field: "dport"  */
#line 6068 "parser_bison.y"
                                                { (yyval.val) = THDR_DPORT; }
#line 16755 "parser_bison.c"
    break;

  case 1314: /* hbh_hdr_expr: "hbh" hbh_hdr_field close_scope_hbh  */
#line 6082 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[-1].val));
			}
#line 16763 "parser_bison.c"
    break;

  case 1315: /* hbh_hdr_field: "nexthdr"  */
#line 6087 "parser_bison.y"
                                                { (yyval.val) = HBHHDR_NEXTHDR; }
#line 16769 "parser_bison.c"
    break;

  case 1316: /* hbh_hdr_field: "hdrlength"  */
#line 6088 "parser_bison.y"
                                                { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 16775 "parser_bison.c"
    break;

  case 1317: /* rt_hdr_expr: "rt" rt_hdr_field close_scope_rt  */
#line 6092 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[-1].val));
			}
#line 16783 "parser_bison.c"
    break;

  case 1318: /* rt_hdr_field: "nexthdr"  */
#line 6097 "parser_bison.y"
                                                { (yyval.val) = RTHDR_NEXTHDR; }
#line 16789 "parser_bison.c"
    break;

  case 1319: /* rt_hdr_field: "hdrlength"  */
#line 6098 "parser_bison.y"
                                                { (yyval.val) = RTHDR_HDRLENGTH; }
#line 16795 "parser_bison.c"
    break;

  case 1320: /* rt_hdr_field: "type" close_scope_type  */
#line 6099 "parser_bison.y"
                                                                        { (yyval.val) = RTHDR_TYPE; }
#line 16801 "parser_bison.c"
    break;

  case 1321: /* rt_hdr_field: "seg-left"  */
#line 6100 "parser_bison.y"
                                                { (yyval.val) = RTHDR_SEG_LEFT; }
#line 16807 "parser_bison.c"
    break;

  case 1322: /* rt0_hdr_expr: "rt0" rt0_hdr_field close_scope_rt  */
#line 6104 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[-1].val));
			}
#line 16815 "parser_bison.c"
    break;

  case 1323: /* rt0_hdr_field: "addr" '[' "number" ']'  */
#line 6110 "parser_bison.y"
                        {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 16823 "parser_bison.c"
    break;

  case 1324: /* rt2_hdr_expr: "rt2" rt2_hdr_field close_scope_rt  */
#line 6116 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[-1].val));
			}
#line 16831 "parser_bison.c"
    break;

  case 1325: /* rt2_hdr_field: "addr"  */
#line 6121 "parser_bison.y"
                                                { (yyval.val) = RT2HDR_ADDR; }
#line 16837 "parser_bison.c"
    break;

  case 1326: /* rt4_hdr_expr: "srh" rt4_hdr_field close_scope_rt  */
#line 6125 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[-1].val));
			}
#line 16845 "parser_bison.c"
    break;

  case 1327: /* rt4_hdr_field: "last-entry"  */
#line 6130 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_LASTENT; }
#line 16851 "parser_bison.c"
    break;

  case 1328: /* rt4_hdr_field: "flags"  */
#line 6131 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_FLAGS; }
#line 16857 "parser_bison.c"
    break;

  case 1329: /* rt4_hdr_field: "tag"  */
#line 6132 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_TAG; }
#line 16863 "parser_bison.c"
    break;

  case 1330: /* rt4_hdr_field: "sid" '[' "number" ']'  */
#line 6134 "parser_bison.y"
                        {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 16871 "parser_bison.c"
    break;

  case 1331: /* frag_hdr_expr: "frag" frag_hdr_field close_scope_frag  */
#line 6140 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[-1].val));
			}
#line 16879 "parser_bison.c"
    break;

  case 1332: /* frag_hdr_field: "nexthdr"  */
#line 6145 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 16885 "parser_bison.c"
    break;

  case 1333: /* frag_hdr_field: "reserved"  */
#line 6146 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_RESERVED; }
#line 16891 "parser_bison.c"
    break;

  case 1334: /* frag_hdr_field: "frag-off"  */
#line 6147 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 16897 "parser_bison.c"
    break;

  case 1335: /* frag_hdr_field: "reserved2"  */
#line 6148 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_RESERVED2; }
#line 16903 "parser_bison.c"
    break;

  case 1336: /* frag_hdr_field: "more-fragments"  */
#line 6149 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_MFRAGS; }
#line 16909 "parser_bison.c"
    break;

  case 1337: /* frag_hdr_field: "id"  */
#line 6150 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_ID; }
#line 16915 "parser_bison.c"
    break;

  case 1338: /* dst_hdr_expr: "dst" dst_hdr_field close_scope_dst  */
#line 6154 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[-1].val));
			}
#line 16923 "parser_bison.c"
    break;

  case 1339: /* dst_hdr_field: "nexthdr"  */
#line 6159 "parser_bison.y"
                                                { (yyval.val) = DSTHDR_NEXTHDR; }
#line 16929 "parser_bison.c"
    break;

  case 1340: /* dst_hdr_field: "hdrlength"  */
#line 6160 "parser_bison.y"
                                                { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 16935 "parser_bison.c"
    break;

  case 1341: /* mh_hdr_expr: "mh" mh_hdr_field close_scope_mh  */
#line 6164 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[-1].val));
			}
#line 16943 "parser_bison.c"
    break;

  case 1342: /* mh_hdr_field: "nexthdr"  */
#line 6169 "parser_bison.y"
                                                { (yyval.val) = MHHDR_NEXTHDR; }
#line 16949 "parser_bison.c"
    break;

  case 1343: /* mh_hdr_field: "hdrlength"  */
#line 6170 "parser_bison.y"
                                                { (yyval.val) = MHHDR_HDRLENGTH; }
#line 16955 "parser_bison.c"
    break;

  case 1344: /* mh_hdr_field: "type" close_scope_type  */
#line 6171 "parser_bison.y"
                                                                        { (yyval.val) = MHHDR_TYPE; }
#line 16961 "parser_bison.c"
    break;

  case 1345: /* mh_hdr_field: "reserved"  */
#line 6172 "parser_bison.y"
                                                { (yyval.val) = MHHDR_RESERVED; }
#line 16967 "parser_bison.c"
    break;

  case 1346: /* mh_hdr_field: "checksum"  */
#line 6173 "parser_bison.y"
                                                { (yyval.val) = MHHDR_CHECKSUM; }
#line 16973 "parser_bison.c"
    break;

  case 1347: /* exthdr_exists_expr: "exthdr" exthdr_key  */
#line 6177 "parser_bison.y"
                        {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the first one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 16989 "parser_bison.c"
    break;

  case 1348: /* exthdr_key: "hbh" close_scope_hbh  */
#line 6190 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_HOPOPTS; }
#line 16995 "parser_bison.c"
    break;

  case 1349: /* exthdr_key: "rt" close_scope_rt  */
#line 6191 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_ROUTING; }
#line 17001 "parser_bison.c"
    break;

  case 1350: /* exthdr_key: "frag" close_scope_frag  */
#line 6192 "parser_bison.y"
                                                                { (yyval.val) = IPPROTO_FRAGMENT; }
#line 17007 "parser_bison.c"
    break;

  case 1351: /* exthdr_key: "dst" close_scope_dst  */
#line 6193 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_DSTOPTS; }
#line 17013 "parser_bison.c"
    break;

  case 1352: /* exthdr_key: "mh" close_scope_mh  */
#line 6194 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_MH; }
#line 17019 "parser_bison.c"
    break;


#line 17023 "parser_bison.c"

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

#line 6197 "parser_bison.y"

