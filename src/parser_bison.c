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

#line 212 "parser_bison.c"

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
    MONITOR = 331,                 /* "monitor"  */
    ALL = 332,                     /* "all"  */
    ACCEPT = 333,                  /* "accept"  */
    DROP = 334,                    /* "drop"  */
    CONTINUE = 335,                /* "continue"  */
    JUMP = 336,                    /* "jump"  */
    GOTO = 337,                    /* "goto"  */
    RETURN = 338,                  /* "return"  */
    TO = 339,                      /* "to"  */
    CONSTANT = 340,                /* "constant"  */
    INTERVAL = 341,                /* "interval"  */
    DYNAMIC = 342,                 /* "dynamic"  */
    AUTOMERGE = 343,               /* "auto-merge"  */
    TIMEOUT = 344,                 /* "timeout"  */
    GC_INTERVAL = 345,             /* "gc-interval"  */
    ELEMENTS = 346,                /* "elements"  */
    EXPIRES = 347,                 /* "expires"  */
    POLICY = 348,                  /* "policy"  */
    MEMORY = 349,                  /* "memory"  */
    PERFORMANCE = 350,             /* "performance"  */
    SIZE = 351,                    /* "size"  */
    FLOW = 352,                    /* "flow"  */
    OFFLOAD = 353,                 /* "offload"  */
    METER = 354,                   /* "meter"  */
    METERS = 355,                  /* "meters"  */
    FLOWTABLES = 356,              /* "flowtables"  */
    NUM = 357,                     /* "number"  */
    STRING = 358,                  /* "string"  */
    QUOTED_STRING = 359,           /* "quoted string"  */
    ASTERISK_STRING = 360,         /* "string with a trailing asterisk"  */
    LL_HDR = 361,                  /* "ll"  */
    NETWORK_HDR = 362,             /* "nh"  */
    TRANSPORT_HDR = 363,           /* "th"  */
    BRIDGE = 364,                  /* "bridge"  */
    ETHER = 365,                   /* "ether"  */
    SADDR = 366,                   /* "saddr"  */
    DADDR = 367,                   /* "daddr"  */
    TYPE = 368,                    /* "type"  */
    VLAN = 369,                    /* "vlan"  */
    ID = 370,                      /* "id"  */
    CFI = 371,                     /* "cfi"  */
    DEI = 372,                     /* "dei"  */
    PCP = 373,                     /* "pcp"  */
    ARP = 374,                     /* "arp"  */
    HTYPE = 375,                   /* "htype"  */
    PTYPE = 376,                   /* "ptype"  */
    HLEN = 377,                    /* "hlen"  */
    PLEN = 378,                    /* "plen"  */
    OPERATION = 379,               /* "operation"  */
    IP = 380,                      /* "ip"  */
    HDRVERSION = 381,              /* "version"  */
    HDRLENGTH = 382,               /* "hdrlength"  */
    DSCP = 383,                    /* "dscp"  */
    ECN = 384,                     /* "ecn"  */
    LENGTH = 385,                  /* "length"  */
    FRAG_OFF = 386,                /* "frag-off"  */
    TTL = 387,                     /* "ttl"  */
    PROTOCOL = 388,                /* "protocol"  */
    CHECKSUM = 389,                /* "checksum"  */
    PTR = 390,                     /* "ptr"  */
    VALUE = 391,                   /* "value"  */
    LSRR = 392,                    /* "lsrr"  */
    RR = 393,                      /* "rr"  */
    SSRR = 394,                    /* "ssrr"  */
    RA = 395,                      /* "ra"  */
    ICMP = 396,                    /* "icmp"  */
    CODE = 397,                    /* "code"  */
    SEQUENCE = 398,                /* "seq"  */
    GATEWAY = 399,                 /* "gateway"  */
    MTU = 400,                     /* "mtu"  */
    IGMP = 401,                    /* "igmp"  */
    MRT = 402,                     /* "mrt"  */
    OPTIONS = 403,                 /* "options"  */
    IP6 = 404,                     /* "ip6"  */
    PRIORITY = 405,                /* "priority"  */
    FLOWLABEL = 406,               /* "flowlabel"  */
    NEXTHDR = 407,                 /* "nexthdr"  */
    HOPLIMIT = 408,                /* "hoplimit"  */
    ICMP6 = 409,                   /* "icmpv6"  */
    PPTR = 410,                    /* "param-problem"  */
    MAXDELAY = 411,                /* "max-delay"  */
    AH = 412,                      /* "ah"  */
    RESERVED = 413,                /* "reserved"  */
    SPI = 414,                     /* "spi"  */
    ESP = 415,                     /* "esp"  */
    COMP = 416,                    /* "comp"  */
    FLAGS = 417,                   /* "flags"  */
    CPI = 418,                     /* "cpi"  */
    PORT = 419,                    /* "port"  */
    UDP = 420,                     /* "udp"  */
    SPORT = 421,                   /* "sport"  */
    DPORT = 422,                   /* "dport"  */
    UDPLITE = 423,                 /* "udplite"  */
    CSUMCOV = 424,                 /* "csumcov"  */
    TCP = 425,                     /* "tcp"  */
    ACKSEQ = 426,                  /* "ackseq"  */
    DOFF = 427,                    /* "doff"  */
    WINDOW = 428,                  /* "window"  */
    URGPTR = 429,                  /* "urgptr"  */
    OPTION = 430,                  /* "option"  */
    ECHO = 431,                    /* "echo"  */
    EOL = 432,                     /* "eol"  */
    NOP = 433,                     /* "nop"  */
    SACK = 434,                    /* "sack"  */
    SACK0 = 435,                   /* "sack0"  */
    SACK1 = 436,                   /* "sack1"  */
    SACK2 = 437,                   /* "sack2"  */
    SACK3 = 438,                   /* "sack3"  */
    SACK_PERM = 439,               /* "sack-permitted"  */
    TIMESTAMP = 440,               /* "timestamp"  */
    KIND = 441,                    /* "kind"  */
    COUNT = 442,                   /* "count"  */
    LEFT = 443,                    /* "left"  */
    RIGHT = 444,                   /* "right"  */
    TSVAL = 445,                   /* "tsval"  */
    TSECR = 446,                   /* "tsecr"  */
    DCCP = 447,                    /* "dccp"  */
    SCTP = 448,                    /* "sctp"  */
    CHUNK = 449,                   /* "chunk"  */
    DATA = 450,                    /* "data"  */
    INIT = 451,                    /* "init"  */
    INIT_ACK = 452,                /* "init-ack"  */
    HEARTBEAT = 453,               /* "heartbeat"  */
    HEARTBEAT_ACK = 454,           /* "heartbeat-ack"  */
    ABORT = 455,                   /* "abort"  */
    SHUTDOWN = 456,                /* "shutdown"  */
    SHUTDOWN_ACK = 457,            /* "shutdown-ack"  */
    ERROR = 458,                   /* "error"  */
    COOKIE_ECHO = 459,             /* "cookie-echo"  */
    COOKIE_ACK = 460,              /* "cookie-ack"  */
    ECNE = 461,                    /* "ecne"  */
    CWR = 462,                     /* "cwr"  */
    SHUTDOWN_COMPLETE = 463,       /* "shutdown-complete"  */
    ASCONF_ACK = 464,              /* "asconf-ack"  */
    FORWARD_TSN = 465,             /* "forward-tsn"  */
    ASCONF = 466,                  /* "asconf"  */
    TSN = 467,                     /* "tsn"  */
    STREAM = 468,                  /* "stream"  */
    SSN = 469,                     /* "ssn"  */
    PPID = 470,                    /* "ppid"  */
    INIT_TAG = 471,                /* "init-tag"  */
    A_RWND = 472,                  /* "a-rwnd"  */
    NUM_OSTREAMS = 473,            /* "num-outbound-streams"  */
    NUM_ISTREAMS = 474,            /* "num-inbound-streams"  */
    INIT_TSN = 475,                /* "initial-tsn"  */
    CUM_TSN_ACK = 476,             /* "cum-tsn-ack"  */
    NUM_GACK_BLOCKS = 477,         /* "num-gap-ack-blocks"  */
    NUM_DUP_TSNS = 478,            /* "num-dup-tsns"  */
    LOWEST_TSN = 479,              /* "lowest-tsn"  */
    SEQNO = 480,                   /* "seqno"  */
    NEW_CUM_TSN = 481,             /* "new-cum-tsn"  */
    VTAG = 482,                    /* "vtag"  */
    RT = 483,                      /* "rt"  */
    RT0 = 484,                     /* "rt0"  */
    RT2 = 485,                     /* "rt2"  */
    RT4 = 486,                     /* "srh"  */
    SEG_LEFT = 487,                /* "seg-left"  */
    ADDR = 488,                    /* "addr"  */
    LAST_ENT = 489,                /* "last-entry"  */
    TAG = 490,                     /* "tag"  */
    SID = 491,                     /* "sid"  */
    HBH = 492,                     /* "hbh"  */
    FRAG = 493,                    /* "frag"  */
    RESERVED2 = 494,               /* "reserved2"  */
    MORE_FRAGMENTS = 495,          /* "more-fragments"  */
    DST = 496,                     /* "dst"  */
    MH = 497,                      /* "mh"  */
    META = 498,                    /* "meta"  */
    MARK = 499,                    /* "mark"  */
    IIF = 500,                     /* "iif"  */
    IIFNAME = 501,                 /* "iifname"  */
    IIFTYPE = 502,                 /* "iiftype"  */
    OIF = 503,                     /* "oif"  */
    OIFNAME = 504,                 /* "oifname"  */
    OIFTYPE = 505,                 /* "oiftype"  */
    SKUID = 506,                   /* "skuid"  */
    SKGID = 507,                   /* "skgid"  */
    NFTRACE = 508,                 /* "nftrace"  */
    RTCLASSID = 509,               /* "rtclassid"  */
    IBRIPORT = 510,                /* "ibriport"  */
    OBRIPORT = 511,                /* "obriport"  */
    IBRIDGENAME = 512,             /* "ibrname"  */
    OBRIDGENAME = 513,             /* "obrname"  */
    PKTTYPE = 514,                 /* "pkttype"  */
    CPU = 515,                     /* "cpu"  */
    IIFGROUP = 516,                /* "iifgroup"  */
    OIFGROUP = 517,                /* "oifgroup"  */
    CGROUP = 518,                  /* "cgroup"  */
    TIME = 519,                    /* "time"  */
    CLASSID = 520,                 /* "classid"  */
    NEXTHOP = 521,                 /* "nexthop"  */
    CT = 522,                      /* "ct"  */
    L3PROTOCOL = 523,              /* "l3proto"  */
    PROTO_SRC = 524,               /* "proto-src"  */
    PROTO_DST = 525,               /* "proto-dst"  */
    ZONE = 526,                    /* "zone"  */
    DIRECTION = 527,               /* "direction"  */
    EVENT = 528,                   /* "event"  */
    EXPECTATION = 529,             /* "expectation"  */
    EXPIRATION = 530,              /* "expiration"  */
    HELPER = 531,                  /* "helper"  */
    LABEL = 532,                   /* "label"  */
    STATE = 533,                   /* "state"  */
    STATUS = 534,                  /* "status"  */
    ORIGINAL = 535,                /* "original"  */
    REPLY = 536,                   /* "reply"  */
    COUNTER = 537,                 /* "counter"  */
    NAME = 538,                    /* "name"  */
    PACKETS = 539,                 /* "packets"  */
    BYTES = 540,                   /* "bytes"  */
    AVGPKT = 541,                  /* "avgpkt"  */
    COUNTERS = 542,                /* "counters"  */
    QUOTAS = 543,                  /* "quotas"  */
    LIMITS = 544,                  /* "limits"  */
    SYNPROXYS = 545,               /* "synproxys"  */
    HELPERS = 546,                 /* "helpers"  */
    LOG = 547,                     /* "log"  */
    PREFIX = 548,                  /* "prefix"  */
    GROUP = 549,                   /* "group"  */
    SNAPLEN = 550,                 /* "snaplen"  */
    QUEUE_THRESHOLD = 551,         /* "queue-threshold"  */
    LEVEL = 552,                   /* "level"  */
    LIMIT = 553,                   /* "limit"  */
    RATE = 554,                    /* "rate"  */
    BURST = 555,                   /* "burst"  */
    OVER = 556,                    /* "over"  */
    UNTIL = 557,                   /* "until"  */
    QUOTA = 558,                   /* "quota"  */
    USED = 559,                    /* "used"  */
    SECMARK = 560,                 /* "secmark"  */
    SECMARKS = 561,                /* "secmarks"  */
    SECOND = 562,                  /* "second"  */
    MINUTE = 563,                  /* "minute"  */
    HOUR = 564,                    /* "hour"  */
    DAY = 565,                     /* "day"  */
    WEEK = 566,                    /* "week"  */
    _REJECT = 567,                 /* "reject"  */
    WITH = 568,                    /* "with"  */
    ICMPX = 569,                   /* "icmpx"  */
    SNAT = 570,                    /* "snat"  */
    DNAT = 571,                    /* "dnat"  */
    MASQUERADE = 572,              /* "masquerade"  */
    REDIRECT = 573,                /* "redirect"  */
    RANDOM = 574,                  /* "random"  */
    FULLY_RANDOM = 575,            /* "fully-random"  */
    PERSISTENT = 576,              /* "persistent"  */
    QUEUE = 577,                   /* "queue"  */
    QUEUENUM = 578,                /* "num"  */
    BYPASS = 579,                  /* "bypass"  */
    FANOUT = 580,                  /* "fanout"  */
    DUP = 581,                     /* "dup"  */
    FWD = 582,                     /* "fwd"  */
    NUMGEN = 583,                  /* "numgen"  */
    INC = 584,                     /* "inc"  */
    MOD = 585,                     /* "mod"  */
    OFFSET = 586,                  /* "offset"  */
    JHASH = 587,                   /* "jhash"  */
    SYMHASH = 588,                 /* "symhash"  */
    SEED = 589,                    /* "seed"  */
    POSITION = 590,                /* "position"  */
    INDEX = 591,                   /* "index"  */
    COMMENT = 592,                 /* "comment"  */
    XML = 593,                     /* "xml"  */
    JSON = 594,                    /* "json"  */
    VM = 595,                      /* "vm"  */
    NOTRACK = 596,                 /* "notrack"  */
    EXISTS = 597,                  /* "exists"  */
    MISSING = 598,                 /* "missing"  */
    EXTHDR = 599,                  /* "exthdr"  */
    IPSEC = 600,                   /* "ipsec"  */
    REQID = 601,                   /* "reqid"  */
    SPNUM = 602,                   /* "spnum"  */
    IN = 603,                      /* "in"  */
    OUT = 604                      /* "out"  */
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
#define MONITOR 331
#define ALL 332
#define ACCEPT 333
#define DROP 334
#define CONTINUE 335
#define JUMP 336
#define GOTO 337
#define RETURN 338
#define TO 339
#define CONSTANT 340
#define INTERVAL 341
#define DYNAMIC 342
#define AUTOMERGE 343
#define TIMEOUT 344
#define GC_INTERVAL 345
#define ELEMENTS 346
#define EXPIRES 347
#define POLICY 348
#define MEMORY 349
#define PERFORMANCE 350
#define SIZE 351
#define FLOW 352
#define OFFLOAD 353
#define METER 354
#define METERS 355
#define FLOWTABLES 356
#define NUM 357
#define STRING 358
#define QUOTED_STRING 359
#define ASTERISK_STRING 360
#define LL_HDR 361
#define NETWORK_HDR 362
#define TRANSPORT_HDR 363
#define BRIDGE 364
#define ETHER 365
#define SADDR 366
#define DADDR 367
#define TYPE 368
#define VLAN 369
#define ID 370
#define CFI 371
#define DEI 372
#define PCP 373
#define ARP 374
#define HTYPE 375
#define PTYPE 376
#define HLEN 377
#define PLEN 378
#define OPERATION 379
#define IP 380
#define HDRVERSION 381
#define HDRLENGTH 382
#define DSCP 383
#define ECN 384
#define LENGTH 385
#define FRAG_OFF 386
#define TTL 387
#define PROTOCOL 388
#define CHECKSUM 389
#define PTR 390
#define VALUE 391
#define LSRR 392
#define RR 393
#define SSRR 394
#define RA 395
#define ICMP 396
#define CODE 397
#define SEQUENCE 398
#define GATEWAY 399
#define MTU 400
#define IGMP 401
#define MRT 402
#define OPTIONS 403
#define IP6 404
#define PRIORITY 405
#define FLOWLABEL 406
#define NEXTHDR 407
#define HOPLIMIT 408
#define ICMP6 409
#define PPTR 410
#define MAXDELAY 411
#define AH 412
#define RESERVED 413
#define SPI 414
#define ESP 415
#define COMP 416
#define FLAGS 417
#define CPI 418
#define PORT 419
#define UDP 420
#define SPORT 421
#define DPORT 422
#define UDPLITE 423
#define CSUMCOV 424
#define TCP 425
#define ACKSEQ 426
#define DOFF 427
#define WINDOW 428
#define URGPTR 429
#define OPTION 430
#define ECHO 431
#define EOL 432
#define NOP 433
#define SACK 434
#define SACK0 435
#define SACK1 436
#define SACK2 437
#define SACK3 438
#define SACK_PERM 439
#define TIMESTAMP 440
#define KIND 441
#define COUNT 442
#define LEFT 443
#define RIGHT 444
#define TSVAL 445
#define TSECR 446
#define DCCP 447
#define SCTP 448
#define CHUNK 449
#define DATA 450
#define INIT 451
#define INIT_ACK 452
#define HEARTBEAT 453
#define HEARTBEAT_ACK 454
#define ABORT 455
#define SHUTDOWN 456
#define SHUTDOWN_ACK 457
#define ERROR 458
#define COOKIE_ECHO 459
#define COOKIE_ACK 460
#define ECNE 461
#define CWR 462
#define SHUTDOWN_COMPLETE 463
#define ASCONF_ACK 464
#define FORWARD_TSN 465
#define ASCONF 466
#define TSN 467
#define STREAM 468
#define SSN 469
#define PPID 470
#define INIT_TAG 471
#define A_RWND 472
#define NUM_OSTREAMS 473
#define NUM_ISTREAMS 474
#define INIT_TSN 475
#define CUM_TSN_ACK 476
#define NUM_GACK_BLOCKS 477
#define NUM_DUP_TSNS 478
#define LOWEST_TSN 479
#define SEQNO 480
#define NEW_CUM_TSN 481
#define VTAG 482
#define RT 483
#define RT0 484
#define RT2 485
#define RT4 486
#define SEG_LEFT 487
#define ADDR 488
#define LAST_ENT 489
#define TAG 490
#define SID 491
#define HBH 492
#define FRAG 493
#define RESERVED2 494
#define MORE_FRAGMENTS 495
#define DST 496
#define MH 497
#define META 498
#define MARK 499
#define IIF 500
#define IIFNAME 501
#define IIFTYPE 502
#define OIF 503
#define OIFNAME 504
#define OIFTYPE 505
#define SKUID 506
#define SKGID 507
#define NFTRACE 508
#define RTCLASSID 509
#define IBRIPORT 510
#define OBRIPORT 511
#define IBRIDGENAME 512
#define OBRIDGENAME 513
#define PKTTYPE 514
#define CPU 515
#define IIFGROUP 516
#define OIFGROUP 517
#define CGROUP 518
#define TIME 519
#define CLASSID 520
#define NEXTHOP 521
#define CT 522
#define L3PROTOCOL 523
#define PROTO_SRC 524
#define PROTO_DST 525
#define ZONE 526
#define DIRECTION 527
#define EVENT 528
#define EXPECTATION 529
#define EXPIRATION 530
#define HELPER 531
#define LABEL 532
#define STATE 533
#define STATUS 534
#define ORIGINAL 535
#define REPLY 536
#define COUNTER 537
#define NAME 538
#define PACKETS 539
#define BYTES 540
#define AVGPKT 541
#define COUNTERS 542
#define QUOTAS 543
#define LIMITS 544
#define SYNPROXYS 545
#define HELPERS 546
#define LOG 547
#define PREFIX 548
#define GROUP 549
#define SNAPLEN 550
#define QUEUE_THRESHOLD 551
#define LEVEL 552
#define LIMIT 553
#define RATE 554
#define BURST 555
#define OVER 556
#define UNTIL 557
#define QUOTA 558
#define USED 559
#define SECMARK 560
#define SECMARKS 561
#define SECOND 562
#define MINUTE 563
#define HOUR 564
#define DAY 565
#define WEEK 566
#define _REJECT 567
#define WITH 568
#define ICMPX 569
#define SNAT 570
#define DNAT 571
#define MASQUERADE 572
#define REDIRECT 573
#define RANDOM 574
#define FULLY_RANDOM 575
#define PERSISTENT 576
#define QUEUE 577
#define QUEUENUM 578
#define BYPASS 579
#define FANOUT 580
#define DUP 581
#define FWD 582
#define NUMGEN 583
#define INC 584
#define MOD 585
#define OFFSET 586
#define JHASH 587
#define SYMHASH 588
#define SEED 589
#define POSITION 590
#define INDEX 591
#define COMMENT 592
#define XML 593
#define JSON 594
#define VM 595
#define NOTRACK 596
#define EXISTS 597
#define MISSING 598
#define EXTHDR 599
#define IPSEC 600
#define REQID 601
#define SPNUM 602
#define IN 603
#define OUT 604

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 167 "parser_bison.y"

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

#line 988 "parser_bison.c"

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
  YYSYMBOL_MONITOR = 76,                   /* "monitor"  */
  YYSYMBOL_ALL = 77,                       /* "all"  */
  YYSYMBOL_ACCEPT = 78,                    /* "accept"  */
  YYSYMBOL_DROP = 79,                      /* "drop"  */
  YYSYMBOL_CONTINUE = 80,                  /* "continue"  */
  YYSYMBOL_JUMP = 81,                      /* "jump"  */
  YYSYMBOL_GOTO = 82,                      /* "goto"  */
  YYSYMBOL_RETURN = 83,                    /* "return"  */
  YYSYMBOL_TO = 84,                        /* "to"  */
  YYSYMBOL_CONSTANT = 85,                  /* "constant"  */
  YYSYMBOL_INTERVAL = 86,                  /* "interval"  */
  YYSYMBOL_DYNAMIC = 87,                   /* "dynamic"  */
  YYSYMBOL_AUTOMERGE = 88,                 /* "auto-merge"  */
  YYSYMBOL_TIMEOUT = 89,                   /* "timeout"  */
  YYSYMBOL_GC_INTERVAL = 90,               /* "gc-interval"  */
  YYSYMBOL_ELEMENTS = 91,                  /* "elements"  */
  YYSYMBOL_EXPIRES = 92,                   /* "expires"  */
  YYSYMBOL_POLICY = 93,                    /* "policy"  */
  YYSYMBOL_MEMORY = 94,                    /* "memory"  */
  YYSYMBOL_PERFORMANCE = 95,               /* "performance"  */
  YYSYMBOL_SIZE = 96,                      /* "size"  */
  YYSYMBOL_FLOW = 97,                      /* "flow"  */
  YYSYMBOL_OFFLOAD = 98,                   /* "offload"  */
  YYSYMBOL_METER = 99,                     /* "meter"  */
  YYSYMBOL_METERS = 100,                   /* "meters"  */
  YYSYMBOL_FLOWTABLES = 101,               /* "flowtables"  */
  YYSYMBOL_NUM = 102,                      /* "number"  */
  YYSYMBOL_STRING = 103,                   /* "string"  */
  YYSYMBOL_QUOTED_STRING = 104,            /* "quoted string"  */
  YYSYMBOL_ASTERISK_STRING = 105,          /* "string with a trailing asterisk"  */
  YYSYMBOL_LL_HDR = 106,                   /* "ll"  */
  YYSYMBOL_NETWORK_HDR = 107,              /* "nh"  */
  YYSYMBOL_TRANSPORT_HDR = 108,            /* "th"  */
  YYSYMBOL_BRIDGE = 109,                   /* "bridge"  */
  YYSYMBOL_ETHER = 110,                    /* "ether"  */
  YYSYMBOL_SADDR = 111,                    /* "saddr"  */
  YYSYMBOL_DADDR = 112,                    /* "daddr"  */
  YYSYMBOL_TYPE = 113,                     /* "type"  */
  YYSYMBOL_VLAN = 114,                     /* "vlan"  */
  YYSYMBOL_ID = 115,                       /* "id"  */
  YYSYMBOL_CFI = 116,                      /* "cfi"  */
  YYSYMBOL_DEI = 117,                      /* "dei"  */
  YYSYMBOL_PCP = 118,                      /* "pcp"  */
  YYSYMBOL_ARP = 119,                      /* "arp"  */
  YYSYMBOL_HTYPE = 120,                    /* "htype"  */
  YYSYMBOL_PTYPE = 121,                    /* "ptype"  */
  YYSYMBOL_HLEN = 122,                     /* "hlen"  */
  YYSYMBOL_PLEN = 123,                     /* "plen"  */
  YYSYMBOL_OPERATION = 124,                /* "operation"  */
  YYSYMBOL_IP = 125,                       /* "ip"  */
  YYSYMBOL_HDRVERSION = 126,               /* "version"  */
  YYSYMBOL_HDRLENGTH = 127,                /* "hdrlength"  */
  YYSYMBOL_DSCP = 128,                     /* "dscp"  */
  YYSYMBOL_ECN = 129,                      /* "ecn"  */
  YYSYMBOL_LENGTH = 130,                   /* "length"  */
  YYSYMBOL_FRAG_OFF = 131,                 /* "frag-off"  */
  YYSYMBOL_TTL = 132,                      /* "ttl"  */
  YYSYMBOL_PROTOCOL = 133,                 /* "protocol"  */
  YYSYMBOL_CHECKSUM = 134,                 /* "checksum"  */
  YYSYMBOL_PTR = 135,                      /* "ptr"  */
  YYSYMBOL_VALUE = 136,                    /* "value"  */
  YYSYMBOL_LSRR = 137,                     /* "lsrr"  */
  YYSYMBOL_RR = 138,                       /* "rr"  */
  YYSYMBOL_SSRR = 139,                     /* "ssrr"  */
  YYSYMBOL_RA = 140,                       /* "ra"  */
  YYSYMBOL_ICMP = 141,                     /* "icmp"  */
  YYSYMBOL_CODE = 142,                     /* "code"  */
  YYSYMBOL_SEQUENCE = 143,                 /* "seq"  */
  YYSYMBOL_GATEWAY = 144,                  /* "gateway"  */
  YYSYMBOL_MTU = 145,                      /* "mtu"  */
  YYSYMBOL_IGMP = 146,                     /* "igmp"  */
  YYSYMBOL_MRT = 147,                      /* "mrt"  */
  YYSYMBOL_OPTIONS = 148,                  /* "options"  */
  YYSYMBOL_IP6 = 149,                      /* "ip6"  */
  YYSYMBOL_PRIORITY = 150,                 /* "priority"  */
  YYSYMBOL_FLOWLABEL = 151,                /* "flowlabel"  */
  YYSYMBOL_NEXTHDR = 152,                  /* "nexthdr"  */
  YYSYMBOL_HOPLIMIT = 153,                 /* "hoplimit"  */
  YYSYMBOL_ICMP6 = 154,                    /* "icmpv6"  */
  YYSYMBOL_PPTR = 155,                     /* "param-problem"  */
  YYSYMBOL_MAXDELAY = 156,                 /* "max-delay"  */
  YYSYMBOL_AH = 157,                       /* "ah"  */
  YYSYMBOL_RESERVED = 158,                 /* "reserved"  */
  YYSYMBOL_SPI = 159,                      /* "spi"  */
  YYSYMBOL_ESP = 160,                      /* "esp"  */
  YYSYMBOL_COMP = 161,                     /* "comp"  */
  YYSYMBOL_FLAGS = 162,                    /* "flags"  */
  YYSYMBOL_CPI = 163,                      /* "cpi"  */
  YYSYMBOL_PORT = 164,                     /* "port"  */
  YYSYMBOL_UDP = 165,                      /* "udp"  */
  YYSYMBOL_SPORT = 166,                    /* "sport"  */
  YYSYMBOL_DPORT = 167,                    /* "dport"  */
  YYSYMBOL_UDPLITE = 168,                  /* "udplite"  */
  YYSYMBOL_CSUMCOV = 169,                  /* "csumcov"  */
  YYSYMBOL_TCP = 170,                      /* "tcp"  */
  YYSYMBOL_ACKSEQ = 171,                   /* "ackseq"  */
  YYSYMBOL_DOFF = 172,                     /* "doff"  */
  YYSYMBOL_WINDOW = 173,                   /* "window"  */
  YYSYMBOL_URGPTR = 174,                   /* "urgptr"  */
  YYSYMBOL_OPTION = 175,                   /* "option"  */
  YYSYMBOL_ECHO = 176,                     /* "echo"  */
  YYSYMBOL_EOL = 177,                      /* "eol"  */
  YYSYMBOL_NOP = 178,                      /* "nop"  */
  YYSYMBOL_SACK = 179,                     /* "sack"  */
  YYSYMBOL_SACK0 = 180,                    /* "sack0"  */
  YYSYMBOL_SACK1 = 181,                    /* "sack1"  */
  YYSYMBOL_SACK2 = 182,                    /* "sack2"  */
  YYSYMBOL_SACK3 = 183,                    /* "sack3"  */
  YYSYMBOL_SACK_PERM = 184,                /* "sack-permitted"  */
  YYSYMBOL_TIMESTAMP = 185,                /* "timestamp"  */
  YYSYMBOL_KIND = 186,                     /* "kind"  */
  YYSYMBOL_COUNT = 187,                    /* "count"  */
  YYSYMBOL_LEFT = 188,                     /* "left"  */
  YYSYMBOL_RIGHT = 189,                    /* "right"  */
  YYSYMBOL_TSVAL = 190,                    /* "tsval"  */
  YYSYMBOL_TSECR = 191,                    /* "tsecr"  */
  YYSYMBOL_DCCP = 192,                     /* "dccp"  */
  YYSYMBOL_SCTP = 193,                     /* "sctp"  */
  YYSYMBOL_CHUNK = 194,                    /* "chunk"  */
  YYSYMBOL_DATA = 195,                     /* "data"  */
  YYSYMBOL_INIT = 196,                     /* "init"  */
  YYSYMBOL_INIT_ACK = 197,                 /* "init-ack"  */
  YYSYMBOL_HEARTBEAT = 198,                /* "heartbeat"  */
  YYSYMBOL_HEARTBEAT_ACK = 199,            /* "heartbeat-ack"  */
  YYSYMBOL_ABORT = 200,                    /* "abort"  */
  YYSYMBOL_SHUTDOWN = 201,                 /* "shutdown"  */
  YYSYMBOL_SHUTDOWN_ACK = 202,             /* "shutdown-ack"  */
  YYSYMBOL_ERROR = 203,                    /* "error"  */
  YYSYMBOL_COOKIE_ECHO = 204,              /* "cookie-echo"  */
  YYSYMBOL_COOKIE_ACK = 205,               /* "cookie-ack"  */
  YYSYMBOL_ECNE = 206,                     /* "ecne"  */
  YYSYMBOL_CWR = 207,                      /* "cwr"  */
  YYSYMBOL_SHUTDOWN_COMPLETE = 208,        /* "shutdown-complete"  */
  YYSYMBOL_ASCONF_ACK = 209,               /* "asconf-ack"  */
  YYSYMBOL_FORWARD_TSN = 210,              /* "forward-tsn"  */
  YYSYMBOL_ASCONF = 211,                   /* "asconf"  */
  YYSYMBOL_TSN = 212,                      /* "tsn"  */
  YYSYMBOL_STREAM = 213,                   /* "stream"  */
  YYSYMBOL_SSN = 214,                      /* "ssn"  */
  YYSYMBOL_PPID = 215,                     /* "ppid"  */
  YYSYMBOL_INIT_TAG = 216,                 /* "init-tag"  */
  YYSYMBOL_A_RWND = 217,                   /* "a-rwnd"  */
  YYSYMBOL_NUM_OSTREAMS = 218,             /* "num-outbound-streams"  */
  YYSYMBOL_NUM_ISTREAMS = 219,             /* "num-inbound-streams"  */
  YYSYMBOL_INIT_TSN = 220,                 /* "initial-tsn"  */
  YYSYMBOL_CUM_TSN_ACK = 221,              /* "cum-tsn-ack"  */
  YYSYMBOL_NUM_GACK_BLOCKS = 222,          /* "num-gap-ack-blocks"  */
  YYSYMBOL_NUM_DUP_TSNS = 223,             /* "num-dup-tsns"  */
  YYSYMBOL_LOWEST_TSN = 224,               /* "lowest-tsn"  */
  YYSYMBOL_SEQNO = 225,                    /* "seqno"  */
  YYSYMBOL_NEW_CUM_TSN = 226,              /* "new-cum-tsn"  */
  YYSYMBOL_VTAG = 227,                     /* "vtag"  */
  YYSYMBOL_RT = 228,                       /* "rt"  */
  YYSYMBOL_RT0 = 229,                      /* "rt0"  */
  YYSYMBOL_RT2 = 230,                      /* "rt2"  */
  YYSYMBOL_RT4 = 231,                      /* "srh"  */
  YYSYMBOL_SEG_LEFT = 232,                 /* "seg-left"  */
  YYSYMBOL_ADDR = 233,                     /* "addr"  */
  YYSYMBOL_LAST_ENT = 234,                 /* "last-entry"  */
  YYSYMBOL_TAG = 235,                      /* "tag"  */
  YYSYMBOL_SID = 236,                      /* "sid"  */
  YYSYMBOL_HBH = 237,                      /* "hbh"  */
  YYSYMBOL_FRAG = 238,                     /* "frag"  */
  YYSYMBOL_RESERVED2 = 239,                /* "reserved2"  */
  YYSYMBOL_MORE_FRAGMENTS = 240,           /* "more-fragments"  */
  YYSYMBOL_DST = 241,                      /* "dst"  */
  YYSYMBOL_MH = 242,                       /* "mh"  */
  YYSYMBOL_META = 243,                     /* "meta"  */
  YYSYMBOL_MARK = 244,                     /* "mark"  */
  YYSYMBOL_IIF = 245,                      /* "iif"  */
  YYSYMBOL_IIFNAME = 246,                  /* "iifname"  */
  YYSYMBOL_IIFTYPE = 247,                  /* "iiftype"  */
  YYSYMBOL_OIF = 248,                      /* "oif"  */
  YYSYMBOL_OIFNAME = 249,                  /* "oifname"  */
  YYSYMBOL_OIFTYPE = 250,                  /* "oiftype"  */
  YYSYMBOL_SKUID = 251,                    /* "skuid"  */
  YYSYMBOL_SKGID = 252,                    /* "skgid"  */
  YYSYMBOL_NFTRACE = 253,                  /* "nftrace"  */
  YYSYMBOL_RTCLASSID = 254,                /* "rtclassid"  */
  YYSYMBOL_IBRIPORT = 255,                 /* "ibriport"  */
  YYSYMBOL_OBRIPORT = 256,                 /* "obriport"  */
  YYSYMBOL_IBRIDGENAME = 257,              /* "ibrname"  */
  YYSYMBOL_OBRIDGENAME = 258,              /* "obrname"  */
  YYSYMBOL_PKTTYPE = 259,                  /* "pkttype"  */
  YYSYMBOL_CPU = 260,                      /* "cpu"  */
  YYSYMBOL_IIFGROUP = 261,                 /* "iifgroup"  */
  YYSYMBOL_OIFGROUP = 262,                 /* "oifgroup"  */
  YYSYMBOL_CGROUP = 263,                   /* "cgroup"  */
  YYSYMBOL_TIME = 264,                     /* "time"  */
  YYSYMBOL_CLASSID = 265,                  /* "classid"  */
  YYSYMBOL_NEXTHOP = 266,                  /* "nexthop"  */
  YYSYMBOL_CT = 267,                       /* "ct"  */
  YYSYMBOL_L3PROTOCOL = 268,               /* "l3proto"  */
  YYSYMBOL_PROTO_SRC = 269,                /* "proto-src"  */
  YYSYMBOL_PROTO_DST = 270,                /* "proto-dst"  */
  YYSYMBOL_ZONE = 271,                     /* "zone"  */
  YYSYMBOL_DIRECTION = 272,                /* "direction"  */
  YYSYMBOL_EVENT = 273,                    /* "event"  */
  YYSYMBOL_EXPECTATION = 274,              /* "expectation"  */
  YYSYMBOL_EXPIRATION = 275,               /* "expiration"  */
  YYSYMBOL_HELPER = 276,                   /* "helper"  */
  YYSYMBOL_LABEL = 277,                    /* "label"  */
  YYSYMBOL_STATE = 278,                    /* "state"  */
  YYSYMBOL_STATUS = 279,                   /* "status"  */
  YYSYMBOL_ORIGINAL = 280,                 /* "original"  */
  YYSYMBOL_REPLY = 281,                    /* "reply"  */
  YYSYMBOL_COUNTER = 282,                  /* "counter"  */
  YYSYMBOL_NAME = 283,                     /* "name"  */
  YYSYMBOL_PACKETS = 284,                  /* "packets"  */
  YYSYMBOL_BYTES = 285,                    /* "bytes"  */
  YYSYMBOL_AVGPKT = 286,                   /* "avgpkt"  */
  YYSYMBOL_COUNTERS = 287,                 /* "counters"  */
  YYSYMBOL_QUOTAS = 288,                   /* "quotas"  */
  YYSYMBOL_LIMITS = 289,                   /* "limits"  */
  YYSYMBOL_SYNPROXYS = 290,                /* "synproxys"  */
  YYSYMBOL_HELPERS = 291,                  /* "helpers"  */
  YYSYMBOL_LOG = 292,                      /* "log"  */
  YYSYMBOL_PREFIX = 293,                   /* "prefix"  */
  YYSYMBOL_GROUP = 294,                    /* "group"  */
  YYSYMBOL_SNAPLEN = 295,                  /* "snaplen"  */
  YYSYMBOL_QUEUE_THRESHOLD = 296,          /* "queue-threshold"  */
  YYSYMBOL_LEVEL = 297,                    /* "level"  */
  YYSYMBOL_LIMIT = 298,                    /* "limit"  */
  YYSYMBOL_RATE = 299,                     /* "rate"  */
  YYSYMBOL_BURST = 300,                    /* "burst"  */
  YYSYMBOL_OVER = 301,                     /* "over"  */
  YYSYMBOL_UNTIL = 302,                    /* "until"  */
  YYSYMBOL_QUOTA = 303,                    /* "quota"  */
  YYSYMBOL_USED = 304,                     /* "used"  */
  YYSYMBOL_SECMARK = 305,                  /* "secmark"  */
  YYSYMBOL_SECMARKS = 306,                 /* "secmarks"  */
  YYSYMBOL_SECOND = 307,                   /* "second"  */
  YYSYMBOL_MINUTE = 308,                   /* "minute"  */
  YYSYMBOL_HOUR = 309,                     /* "hour"  */
  YYSYMBOL_DAY = 310,                      /* "day"  */
  YYSYMBOL_WEEK = 311,                     /* "week"  */
  YYSYMBOL__REJECT = 312,                  /* "reject"  */
  YYSYMBOL_WITH = 313,                     /* "with"  */
  YYSYMBOL_ICMPX = 314,                    /* "icmpx"  */
  YYSYMBOL_SNAT = 315,                     /* "snat"  */
  YYSYMBOL_DNAT = 316,                     /* "dnat"  */
  YYSYMBOL_MASQUERADE = 317,               /* "masquerade"  */
  YYSYMBOL_REDIRECT = 318,                 /* "redirect"  */
  YYSYMBOL_RANDOM = 319,                   /* "random"  */
  YYSYMBOL_FULLY_RANDOM = 320,             /* "fully-random"  */
  YYSYMBOL_PERSISTENT = 321,               /* "persistent"  */
  YYSYMBOL_QUEUE = 322,                    /* "queue"  */
  YYSYMBOL_QUEUENUM = 323,                 /* "num"  */
  YYSYMBOL_BYPASS = 324,                   /* "bypass"  */
  YYSYMBOL_FANOUT = 325,                   /* "fanout"  */
  YYSYMBOL_DUP = 326,                      /* "dup"  */
  YYSYMBOL_FWD = 327,                      /* "fwd"  */
  YYSYMBOL_NUMGEN = 328,                   /* "numgen"  */
  YYSYMBOL_INC = 329,                      /* "inc"  */
  YYSYMBOL_MOD = 330,                      /* "mod"  */
  YYSYMBOL_OFFSET = 331,                   /* "offset"  */
  YYSYMBOL_JHASH = 332,                    /* "jhash"  */
  YYSYMBOL_SYMHASH = 333,                  /* "symhash"  */
  YYSYMBOL_SEED = 334,                     /* "seed"  */
  YYSYMBOL_POSITION = 335,                 /* "position"  */
  YYSYMBOL_INDEX = 336,                    /* "index"  */
  YYSYMBOL_COMMENT = 337,                  /* "comment"  */
  YYSYMBOL_XML = 338,                      /* "xml"  */
  YYSYMBOL_JSON = 339,                     /* "json"  */
  YYSYMBOL_VM = 340,                       /* "vm"  */
  YYSYMBOL_NOTRACK = 341,                  /* "notrack"  */
  YYSYMBOL_EXISTS = 342,                   /* "exists"  */
  YYSYMBOL_MISSING = 343,                  /* "missing"  */
  YYSYMBOL_EXTHDR = 344,                   /* "exthdr"  */
  YYSYMBOL_IPSEC = 345,                    /* "ipsec"  */
  YYSYMBOL_REQID = 346,                    /* "reqid"  */
  YYSYMBOL_SPNUM = 347,                    /* "spnum"  */
  YYSYMBOL_IN = 348,                       /* "in"  */
  YYSYMBOL_OUT = 349,                      /* "out"  */
  YYSYMBOL_350_ = 350,                     /* '='  */
  YYSYMBOL_351_ = 351,                     /* '{'  */
  YYSYMBOL_352_ = 352,                     /* '}'  */
  YYSYMBOL_353_ = 353,                     /* '('  */
  YYSYMBOL_354_ = 354,                     /* ')'  */
  YYSYMBOL_355_ = 355,                     /* '|'  */
  YYSYMBOL_356_ = 356,                     /* '$'  */
  YYSYMBOL_357_ = 357,                     /* '['  */
  YYSYMBOL_358_ = 358,                     /* ']'  */
  YYSYMBOL_YYACCEPT = 359,                 /* $accept  */
  YYSYMBOL_input = 360,                    /* input  */
  YYSYMBOL_stmt_separator = 361,           /* stmt_separator  */
  YYSYMBOL_opt_newline = 362,              /* opt_newline  */
  YYSYMBOL_close_scope_arp = 363,          /* close_scope_arp  */
  YYSYMBOL_close_scope_ct = 364,           /* close_scope_ct  */
  YYSYMBOL_close_scope_counter = 365,      /* close_scope_counter  */
  YYSYMBOL_close_scope_eth = 366,          /* close_scope_eth  */
  YYSYMBOL_close_scope_fib = 367,          /* close_scope_fib  */
  YYSYMBOL_close_scope_hash = 368,         /* close_scope_hash  */
  YYSYMBOL_close_scope_ip = 369,           /* close_scope_ip  */
  YYSYMBOL_close_scope_ip6 = 370,          /* close_scope_ip6  */
  YYSYMBOL_close_scope_vlan = 371,         /* close_scope_vlan  */
  YYSYMBOL_close_scope_ipsec = 372,        /* close_scope_ipsec  */
  YYSYMBOL_close_scope_list = 373,         /* close_scope_list  */
  YYSYMBOL_close_scope_limit = 374,        /* close_scope_limit  */
  YYSYMBOL_close_scope_numgen = 375,       /* close_scope_numgen  */
  YYSYMBOL_close_scope_quota = 376,        /* close_scope_quota  */
  YYSYMBOL_close_scope_queue = 377,        /* close_scope_queue  */
  YYSYMBOL_close_scope_rt = 378,           /* close_scope_rt  */
  YYSYMBOL_close_scope_sctp = 379,         /* close_scope_sctp  */
  YYSYMBOL_close_scope_sctp_chunk = 380,   /* close_scope_sctp_chunk  */
  YYSYMBOL_close_scope_secmark = 381,      /* close_scope_secmark  */
  YYSYMBOL_close_scope_socket = 382,       /* close_scope_socket  */
  YYSYMBOL_close_scope_log = 383,          /* close_scope_log  */
  YYSYMBOL_common_block = 384,             /* common_block  */
  YYSYMBOL_line = 385,                     /* line  */
  YYSYMBOL_base_cmd = 386,                 /* base_cmd  */
  YYSYMBOL_add_cmd = 387,                  /* add_cmd  */
  YYSYMBOL_replace_cmd = 388,              /* replace_cmd  */
  YYSYMBOL_create_cmd = 389,               /* create_cmd  */
  YYSYMBOL_insert_cmd = 390,               /* insert_cmd  */
  YYSYMBOL_table_or_id_spec = 391,         /* table_or_id_spec  */
  YYSYMBOL_chain_or_id_spec = 392,         /* chain_or_id_spec  */
  YYSYMBOL_set_or_id_spec = 393,           /* set_or_id_spec  */
  YYSYMBOL_obj_or_id_spec = 394,           /* obj_or_id_spec  */
  YYSYMBOL_delete_cmd = 395,               /* delete_cmd  */
  YYSYMBOL_get_cmd = 396,                  /* get_cmd  */
  YYSYMBOL_list_cmd = 397,                 /* list_cmd  */
  YYSYMBOL_basehook_device_name = 398,     /* basehook_device_name  */
  YYSYMBOL_basehook_spec = 399,            /* basehook_spec  */
  YYSYMBOL_reset_cmd = 400,                /* reset_cmd  */
  YYSYMBOL_flush_cmd = 401,                /* flush_cmd  */
  YYSYMBOL_rename_cmd = 402,               /* rename_cmd  */
  YYSYMBOL_import_cmd = 403,               /* import_cmd  */
  YYSYMBOL_export_cmd = 404,               /* export_cmd  */
  YYSYMBOL_monitor_cmd = 405,              /* monitor_cmd  */
  YYSYMBOL_monitor_event = 406,            /* monitor_event  */
  YYSYMBOL_monitor_object = 407,           /* monitor_object  */
  YYSYMBOL_monitor_format = 408,           /* monitor_format  */
  YYSYMBOL_markup_format = 409,            /* markup_format  */
  YYSYMBOL_describe_cmd = 410,             /* describe_cmd  */
  YYSYMBOL_table_block_alloc = 411,        /* table_block_alloc  */
  YYSYMBOL_table_options = 412,            /* table_options  */
  YYSYMBOL_table_block = 413,              /* table_block  */
  YYSYMBOL_chain_block_alloc = 414,        /* chain_block_alloc  */
  YYSYMBOL_chain_block = 415,              /* chain_block  */
  YYSYMBOL_subchain_block = 416,           /* subchain_block  */
  YYSYMBOL_typeof_data_expr = 417,         /* typeof_data_expr  */
  YYSYMBOL_typeof_expr = 418,              /* typeof_expr  */
  YYSYMBOL_set_block_alloc = 419,          /* set_block_alloc  */
  YYSYMBOL_set_block = 420,                /* set_block  */
  YYSYMBOL_set_block_expr = 421,           /* set_block_expr  */
  YYSYMBOL_set_flag_list = 422,            /* set_flag_list  */
  YYSYMBOL_set_flag = 423,                 /* set_flag  */
  YYSYMBOL_map_block_alloc = 424,          /* map_block_alloc  */
  YYSYMBOL_map_block_obj_type = 425,       /* map_block_obj_type  */
  YYSYMBOL_map_block = 426,                /* map_block  */
  YYSYMBOL_set_mechanism = 427,            /* set_mechanism  */
  YYSYMBOL_set_policy_spec = 428,          /* set_policy_spec  */
  YYSYMBOL_flowtable_block_alloc = 429,    /* flowtable_block_alloc  */
  YYSYMBOL_flowtable_block = 430,          /* flowtable_block  */
  YYSYMBOL_flowtable_expr = 431,           /* flowtable_expr  */
  YYSYMBOL_flowtable_list_expr = 432,      /* flowtable_list_expr  */
  YYSYMBOL_flowtable_expr_member = 433,    /* flowtable_expr_member  */
  YYSYMBOL_data_type_atom_expr = 434,      /* data_type_atom_expr  */
  YYSYMBOL_data_type_expr = 435,           /* data_type_expr  */
  YYSYMBOL_obj_block_alloc = 436,          /* obj_block_alloc  */
  YYSYMBOL_counter_block = 437,            /* counter_block  */
  YYSYMBOL_quota_block = 438,              /* quota_block  */
  YYSYMBOL_ct_helper_block = 439,          /* ct_helper_block  */
  YYSYMBOL_ct_timeout_block = 440,         /* ct_timeout_block  */
  YYSYMBOL_ct_expect_block = 441,          /* ct_expect_block  */
  YYSYMBOL_limit_block = 442,              /* limit_block  */
  YYSYMBOL_secmark_block = 443,            /* secmark_block  */
  YYSYMBOL_synproxy_block = 444,           /* synproxy_block  */
  YYSYMBOL_type_identifier = 445,          /* type_identifier  */
  YYSYMBOL_hook_spec = 446,                /* hook_spec  */
  YYSYMBOL_prio_spec = 447,                /* prio_spec  */
  YYSYMBOL_extended_prio_name = 448,       /* extended_prio_name  */
  YYSYMBOL_extended_prio_spec = 449,       /* extended_prio_spec  */
  YYSYMBOL_int_num = 450,                  /* int_num  */
  YYSYMBOL_dev_spec = 451,                 /* dev_spec  */
  YYSYMBOL_flags_spec = 452,               /* flags_spec  */
  YYSYMBOL_policy_spec = 453,              /* policy_spec  */
  YYSYMBOL_policy_expr = 454,              /* policy_expr  */
  YYSYMBOL_chain_policy = 455,             /* chain_policy  */
  YYSYMBOL_identifier = 456,               /* identifier  */
  YYSYMBOL_string = 457,                   /* string  */
  YYSYMBOL_time_spec = 458,                /* time_spec  */
  YYSYMBOL_family_spec = 459,              /* family_spec  */
  YYSYMBOL_family_spec_explicit = 460,     /* family_spec_explicit  */
  YYSYMBOL_table_spec = 461,               /* table_spec  */
  YYSYMBOL_tableid_spec = 462,             /* tableid_spec  */
  YYSYMBOL_chain_spec = 463,               /* chain_spec  */
  YYSYMBOL_chainid_spec = 464,             /* chainid_spec  */
  YYSYMBOL_chain_identifier = 465,         /* chain_identifier  */
  YYSYMBOL_set_spec = 466,                 /* set_spec  */
  YYSYMBOL_setid_spec = 467,               /* setid_spec  */
  YYSYMBOL_set_identifier = 468,           /* set_identifier  */
  YYSYMBOL_flowtable_spec = 469,           /* flowtable_spec  */
  YYSYMBOL_flowtableid_spec = 470,         /* flowtableid_spec  */
  YYSYMBOL_flowtable_identifier = 471,     /* flowtable_identifier  */
  YYSYMBOL_obj_spec = 472,                 /* obj_spec  */
  YYSYMBOL_objid_spec = 473,               /* objid_spec  */
  YYSYMBOL_obj_identifier = 474,           /* obj_identifier  */
  YYSYMBOL_handle_spec = 475,              /* handle_spec  */
  YYSYMBOL_position_spec = 476,            /* position_spec  */
  YYSYMBOL_index_spec = 477,               /* index_spec  */
  YYSYMBOL_rule_position = 478,            /* rule_position  */
  YYSYMBOL_ruleid_spec = 479,              /* ruleid_spec  */
  YYSYMBOL_comment_spec = 480,             /* comment_spec  */
  YYSYMBOL_ruleset_spec = 481,             /* ruleset_spec  */
  YYSYMBOL_rule = 482,                     /* rule  */
  YYSYMBOL_rule_alloc = 483,               /* rule_alloc  */
  YYSYMBOL_stmt_list = 484,                /* stmt_list  */
  YYSYMBOL_stateful_stmt_list = 485,       /* stateful_stmt_list  */
  YYSYMBOL_stateful_stmt = 486,            /* stateful_stmt  */
  YYSYMBOL_stmt = 487,                     /* stmt  */
  YYSYMBOL_chain_stmt_type = 488,          /* chain_stmt_type  */
  YYSYMBOL_chain_stmt = 489,               /* chain_stmt  */
  YYSYMBOL_verdict_stmt = 490,             /* verdict_stmt  */
  YYSYMBOL_verdict_map_stmt = 491,         /* verdict_map_stmt  */
  YYSYMBOL_verdict_map_expr = 492,         /* verdict_map_expr  */
  YYSYMBOL_verdict_map_list_expr = 493,    /* verdict_map_list_expr  */
  YYSYMBOL_verdict_map_list_member_expr = 494, /* verdict_map_list_member_expr  */
  YYSYMBOL_connlimit_stmt = 495,           /* connlimit_stmt  */
  YYSYMBOL_counter_stmt = 496,             /* counter_stmt  */
  YYSYMBOL_counter_stmt_alloc = 497,       /* counter_stmt_alloc  */
  YYSYMBOL_counter_args = 498,             /* counter_args  */
  YYSYMBOL_counter_arg = 499,              /* counter_arg  */
  YYSYMBOL_log_stmt = 500,                 /* log_stmt  */
  YYSYMBOL_log_stmt_alloc = 501,           /* log_stmt_alloc  */
  YYSYMBOL_log_args = 502,                 /* log_args  */
  YYSYMBOL_log_arg = 503,                  /* log_arg  */
  YYSYMBOL_level_type = 504,               /* level_type  */
  YYSYMBOL_log_flags = 505,                /* log_flags  */
  YYSYMBOL_log_flags_tcp = 506,            /* log_flags_tcp  */
  YYSYMBOL_log_flag_tcp = 507,             /* log_flag_tcp  */
  YYSYMBOL_limit_stmt = 508,               /* limit_stmt  */
  YYSYMBOL_quota_mode = 509,               /* quota_mode  */
  YYSYMBOL_quota_unit = 510,               /* quota_unit  */
  YYSYMBOL_quota_used = 511,               /* quota_used  */
  YYSYMBOL_quota_stmt = 512,               /* quota_stmt  */
  YYSYMBOL_limit_mode = 513,               /* limit_mode  */
  YYSYMBOL_limit_burst_pkts = 514,         /* limit_burst_pkts  */
  YYSYMBOL_limit_rate_pkts = 515,          /* limit_rate_pkts  */
  YYSYMBOL_limit_burst_bytes = 516,        /* limit_burst_bytes  */
  YYSYMBOL_limit_rate_bytes = 517,         /* limit_rate_bytes  */
  YYSYMBOL_limit_bytes = 518,              /* limit_bytes  */
  YYSYMBOL_time_unit = 519,                /* time_unit  */
  YYSYMBOL_reject_stmt = 520,              /* reject_stmt  */
  YYSYMBOL_reject_stmt_alloc = 521,        /* reject_stmt_alloc  */
  YYSYMBOL_reject_with_expr = 522,         /* reject_with_expr  */
  YYSYMBOL_reject_opts = 523,              /* reject_opts  */
  YYSYMBOL_nat_stmt = 524,                 /* nat_stmt  */
  YYSYMBOL_nat_stmt_alloc = 525,           /* nat_stmt_alloc  */
  YYSYMBOL_tproxy_stmt = 526,              /* tproxy_stmt  */
  YYSYMBOL_synproxy_stmt = 527,            /* synproxy_stmt  */
  YYSYMBOL_synproxy_stmt_alloc = 528,      /* synproxy_stmt_alloc  */
  YYSYMBOL_synproxy_args = 529,            /* synproxy_args  */
  YYSYMBOL_synproxy_arg = 530,             /* synproxy_arg  */
  YYSYMBOL_synproxy_config = 531,          /* synproxy_config  */
  YYSYMBOL_synproxy_obj = 532,             /* synproxy_obj  */
  YYSYMBOL_synproxy_ts = 533,              /* synproxy_ts  */
  YYSYMBOL_synproxy_sack = 534,            /* synproxy_sack  */
  YYSYMBOL_primary_stmt_expr = 535,        /* primary_stmt_expr  */
  YYSYMBOL_shift_stmt_expr = 536,          /* shift_stmt_expr  */
  YYSYMBOL_and_stmt_expr = 537,            /* and_stmt_expr  */
  YYSYMBOL_exclusive_or_stmt_expr = 538,   /* exclusive_or_stmt_expr  */
  YYSYMBOL_inclusive_or_stmt_expr = 539,   /* inclusive_or_stmt_expr  */
  YYSYMBOL_basic_stmt_expr = 540,          /* basic_stmt_expr  */
  YYSYMBOL_concat_stmt_expr = 541,         /* concat_stmt_expr  */
  YYSYMBOL_map_stmt_expr_set = 542,        /* map_stmt_expr_set  */
  YYSYMBOL_map_stmt_expr = 543,            /* map_stmt_expr  */
  YYSYMBOL_prefix_stmt_expr = 544,         /* prefix_stmt_expr  */
  YYSYMBOL_range_stmt_expr = 545,          /* range_stmt_expr  */
  YYSYMBOL_multiton_stmt_expr = 546,       /* multiton_stmt_expr  */
  YYSYMBOL_stmt_expr = 547,                /* stmt_expr  */
  YYSYMBOL_nat_stmt_args = 548,            /* nat_stmt_args  */
  YYSYMBOL_masq_stmt = 549,                /* masq_stmt  */
  YYSYMBOL_masq_stmt_alloc = 550,          /* masq_stmt_alloc  */
  YYSYMBOL_masq_stmt_args = 551,           /* masq_stmt_args  */
  YYSYMBOL_redir_stmt = 552,               /* redir_stmt  */
  YYSYMBOL_redir_stmt_alloc = 553,         /* redir_stmt_alloc  */
  YYSYMBOL_redir_stmt_arg = 554,           /* redir_stmt_arg  */
  YYSYMBOL_dup_stmt = 555,                 /* dup_stmt  */
  YYSYMBOL_fwd_stmt = 556,                 /* fwd_stmt  */
  YYSYMBOL_nf_nat_flags = 557,             /* nf_nat_flags  */
  YYSYMBOL_nf_nat_flag = 558,              /* nf_nat_flag  */
  YYSYMBOL_queue_stmt = 559,               /* queue_stmt  */
  YYSYMBOL_queue_stmt_compat = 560,        /* queue_stmt_compat  */
  YYSYMBOL_queue_stmt_alloc = 561,         /* queue_stmt_alloc  */
  YYSYMBOL_queue_stmt_args = 562,          /* queue_stmt_args  */
  YYSYMBOL_queue_stmt_arg = 563,           /* queue_stmt_arg  */
  YYSYMBOL_queue_expr = 564,               /* queue_expr  */
  YYSYMBOL_queue_stmt_expr_simple = 565,   /* queue_stmt_expr_simple  */
  YYSYMBOL_queue_stmt_expr = 566,          /* queue_stmt_expr  */
  YYSYMBOL_queue_stmt_flags = 567,         /* queue_stmt_flags  */
  YYSYMBOL_queue_stmt_flag = 568,          /* queue_stmt_flag  */
  YYSYMBOL_set_elem_expr_stmt = 569,       /* set_elem_expr_stmt  */
  YYSYMBOL_set_elem_expr_stmt_alloc = 570, /* set_elem_expr_stmt_alloc  */
  YYSYMBOL_set_stmt = 571,                 /* set_stmt  */
  YYSYMBOL_set_stmt_op = 572,              /* set_stmt_op  */
  YYSYMBOL_map_stmt = 573,                 /* map_stmt  */
  YYSYMBOL_meter_stmt = 574,               /* meter_stmt  */
  YYSYMBOL_flow_stmt_legacy_alloc = 575,   /* flow_stmt_legacy_alloc  */
  YYSYMBOL_flow_stmt_opts = 576,           /* flow_stmt_opts  */
  YYSYMBOL_flow_stmt_opt = 577,            /* flow_stmt_opt  */
  YYSYMBOL_meter_stmt_alloc = 578,         /* meter_stmt_alloc  */
  YYSYMBOL_match_stmt = 579,               /* match_stmt  */
  YYSYMBOL_variable_expr = 580,            /* variable_expr  */
  YYSYMBOL_symbol_expr = 581,              /* symbol_expr  */
  YYSYMBOL_set_ref_expr = 582,             /* set_ref_expr  */
  YYSYMBOL_set_ref_symbol_expr = 583,      /* set_ref_symbol_expr  */
  YYSYMBOL_integer_expr = 584,             /* integer_expr  */
  YYSYMBOL_primary_expr = 585,             /* primary_expr  */
  YYSYMBOL_fib_expr = 586,                 /* fib_expr  */
  YYSYMBOL_fib_result = 587,               /* fib_result  */
  YYSYMBOL_fib_flag = 588,                 /* fib_flag  */
  YYSYMBOL_fib_tuple = 589,                /* fib_tuple  */
  YYSYMBOL_osf_expr = 590,                 /* osf_expr  */
  YYSYMBOL_osf_ttl = 591,                  /* osf_ttl  */
  YYSYMBOL_shift_expr = 592,               /* shift_expr  */
  YYSYMBOL_and_expr = 593,                 /* and_expr  */
  YYSYMBOL_exclusive_or_expr = 594,        /* exclusive_or_expr  */
  YYSYMBOL_inclusive_or_expr = 595,        /* inclusive_or_expr  */
  YYSYMBOL_basic_expr = 596,               /* basic_expr  */
  YYSYMBOL_concat_expr = 597,              /* concat_expr  */
  YYSYMBOL_prefix_rhs_expr = 598,          /* prefix_rhs_expr  */
  YYSYMBOL_range_rhs_expr = 599,           /* range_rhs_expr  */
  YYSYMBOL_multiton_rhs_expr = 600,        /* multiton_rhs_expr  */
  YYSYMBOL_map_expr = 601,                 /* map_expr  */
  YYSYMBOL_expr = 602,                     /* expr  */
  YYSYMBOL_set_expr = 603,                 /* set_expr  */
  YYSYMBOL_set_list_expr = 604,            /* set_list_expr  */
  YYSYMBOL_set_list_member_expr = 605,     /* set_list_member_expr  */
  YYSYMBOL_meter_key_expr = 606,           /* meter_key_expr  */
  YYSYMBOL_meter_key_expr_alloc = 607,     /* meter_key_expr_alloc  */
  YYSYMBOL_set_elem_expr = 608,            /* set_elem_expr  */
  YYSYMBOL_set_elem_key_expr = 609,        /* set_elem_key_expr  */
  YYSYMBOL_set_elem_expr_alloc = 610,      /* set_elem_expr_alloc  */
  YYSYMBOL_set_elem_options = 611,         /* set_elem_options  */
  YYSYMBOL_set_elem_option = 612,          /* set_elem_option  */
  YYSYMBOL_set_elem_expr_options = 613,    /* set_elem_expr_options  */
  YYSYMBOL_set_elem_stmt_list = 614,       /* set_elem_stmt_list  */
  YYSYMBOL_set_elem_stmt = 615,            /* set_elem_stmt  */
  YYSYMBOL_set_elem_expr_option = 616,     /* set_elem_expr_option  */
  YYSYMBOL_set_lhs_expr = 617,             /* set_lhs_expr  */
  YYSYMBOL_set_rhs_expr = 618,             /* set_rhs_expr  */
  YYSYMBOL_initializer_expr = 619,         /* initializer_expr  */
  YYSYMBOL_counter_config = 620,           /* counter_config  */
  YYSYMBOL_counter_obj = 621,              /* counter_obj  */
  YYSYMBOL_quota_config = 622,             /* quota_config  */
  YYSYMBOL_quota_obj = 623,                /* quota_obj  */
  YYSYMBOL_secmark_config = 624,           /* secmark_config  */
  YYSYMBOL_secmark_obj = 625,              /* secmark_obj  */
  YYSYMBOL_ct_obj_type = 626,              /* ct_obj_type  */
  YYSYMBOL_ct_cmd_type = 627,              /* ct_cmd_type  */
  YYSYMBOL_ct_l4protoname = 628,           /* ct_l4protoname  */
  YYSYMBOL_ct_helper_config = 629,         /* ct_helper_config  */
  YYSYMBOL_timeout_states = 630,           /* timeout_states  */
  YYSYMBOL_timeout_state = 631,            /* timeout_state  */
  YYSYMBOL_ct_timeout_config = 632,        /* ct_timeout_config  */
  YYSYMBOL_ct_expect_config = 633,         /* ct_expect_config  */
  YYSYMBOL_ct_obj_alloc = 634,             /* ct_obj_alloc  */
  YYSYMBOL_limit_config = 635,             /* limit_config  */
  YYSYMBOL_limit_obj = 636,                /* limit_obj  */
  YYSYMBOL_relational_expr = 637,          /* relational_expr  */
  YYSYMBOL_list_rhs_expr = 638,            /* list_rhs_expr  */
  YYSYMBOL_rhs_expr = 639,                 /* rhs_expr  */
  YYSYMBOL_shift_rhs_expr = 640,           /* shift_rhs_expr  */
  YYSYMBOL_and_rhs_expr = 641,             /* and_rhs_expr  */
  YYSYMBOL_exclusive_or_rhs_expr = 642,    /* exclusive_or_rhs_expr  */
  YYSYMBOL_inclusive_or_rhs_expr = 643,    /* inclusive_or_rhs_expr  */
  YYSYMBOL_basic_rhs_expr = 644,           /* basic_rhs_expr  */
  YYSYMBOL_concat_rhs_expr = 645,          /* concat_rhs_expr  */
  YYSYMBOL_boolean_keys = 646,             /* boolean_keys  */
  YYSYMBOL_boolean_expr = 647,             /* boolean_expr  */
  YYSYMBOL_keyword_expr = 648,             /* keyword_expr  */
  YYSYMBOL_primary_rhs_expr = 649,         /* primary_rhs_expr  */
  YYSYMBOL_relational_op = 650,            /* relational_op  */
  YYSYMBOL_verdict_expr = 651,             /* verdict_expr  */
  YYSYMBOL_chain_expr = 652,               /* chain_expr  */
  YYSYMBOL_meta_expr = 653,                /* meta_expr  */
  YYSYMBOL_meta_key = 654,                 /* meta_key  */
  YYSYMBOL_meta_key_qualified = 655,       /* meta_key_qualified  */
  YYSYMBOL_meta_key_unqualified = 656,     /* meta_key_unqualified  */
  YYSYMBOL_meta_stmt = 657,                /* meta_stmt  */
  YYSYMBOL_socket_expr = 658,              /* socket_expr  */
  YYSYMBOL_socket_key = 659,               /* socket_key  */
  YYSYMBOL_offset_opt = 660,               /* offset_opt  */
  YYSYMBOL_numgen_type = 661,              /* numgen_type  */
  YYSYMBOL_numgen_expr = 662,              /* numgen_expr  */
  YYSYMBOL_xfrm_spnum = 663,               /* xfrm_spnum  */
  YYSYMBOL_xfrm_dir = 664,                 /* xfrm_dir  */
  YYSYMBOL_xfrm_state_key = 665,           /* xfrm_state_key  */
  YYSYMBOL_xfrm_state_proto_key = 666,     /* xfrm_state_proto_key  */
  YYSYMBOL_xfrm_expr = 667,                /* xfrm_expr  */
  YYSYMBOL_hash_expr = 668,                /* hash_expr  */
  YYSYMBOL_nf_key_proto = 669,             /* nf_key_proto  */
  YYSYMBOL_rt_expr = 670,                  /* rt_expr  */
  YYSYMBOL_rt_key = 671,                   /* rt_key  */
  YYSYMBOL_ct_expr = 672,                  /* ct_expr  */
  YYSYMBOL_ct_dir = 673,                   /* ct_dir  */
  YYSYMBOL_ct_key = 674,                   /* ct_key  */
  YYSYMBOL_ct_key_dir = 675,               /* ct_key_dir  */
  YYSYMBOL_ct_key_proto_field = 676,       /* ct_key_proto_field  */
  YYSYMBOL_ct_key_dir_optional = 677,      /* ct_key_dir_optional  */
  YYSYMBOL_symbol_stmt_expr = 678,         /* symbol_stmt_expr  */
  YYSYMBOL_list_stmt_expr = 679,           /* list_stmt_expr  */
  YYSYMBOL_ct_stmt = 680,                  /* ct_stmt  */
  YYSYMBOL_payload_stmt = 681,             /* payload_stmt  */
  YYSYMBOL_payload_expr = 682,             /* payload_expr  */
  YYSYMBOL_payload_raw_expr = 683,         /* payload_raw_expr  */
  YYSYMBOL_payload_base_spec = 684,        /* payload_base_spec  */
  YYSYMBOL_eth_hdr_expr = 685,             /* eth_hdr_expr  */
  YYSYMBOL_eth_hdr_field = 686,            /* eth_hdr_field  */
  YYSYMBOL_vlan_hdr_expr = 687,            /* vlan_hdr_expr  */
  YYSYMBOL_vlan_hdr_field = 688,           /* vlan_hdr_field  */
  YYSYMBOL_arp_hdr_expr = 689,             /* arp_hdr_expr  */
  YYSYMBOL_arp_hdr_field = 690,            /* arp_hdr_field  */
  YYSYMBOL_ip_hdr_expr = 691,              /* ip_hdr_expr  */
  YYSYMBOL_ip_hdr_field = 692,             /* ip_hdr_field  */
  YYSYMBOL_ip_option_type = 693,           /* ip_option_type  */
  YYSYMBOL_ip_option_field = 694,          /* ip_option_field  */
  YYSYMBOL_icmp_hdr_expr = 695,            /* icmp_hdr_expr  */
  YYSYMBOL_icmp_hdr_field = 696,           /* icmp_hdr_field  */
  YYSYMBOL_igmp_hdr_expr = 697,            /* igmp_hdr_expr  */
  YYSYMBOL_igmp_hdr_field = 698,           /* igmp_hdr_field  */
  YYSYMBOL_ip6_hdr_expr = 699,             /* ip6_hdr_expr  */
  YYSYMBOL_ip6_hdr_field = 700,            /* ip6_hdr_field  */
  YYSYMBOL_icmp6_hdr_expr = 701,           /* icmp6_hdr_expr  */
  YYSYMBOL_icmp6_hdr_field = 702,          /* icmp6_hdr_field  */
  YYSYMBOL_auth_hdr_expr = 703,            /* auth_hdr_expr  */
  YYSYMBOL_auth_hdr_field = 704,           /* auth_hdr_field  */
  YYSYMBOL_esp_hdr_expr = 705,             /* esp_hdr_expr  */
  YYSYMBOL_esp_hdr_field = 706,            /* esp_hdr_field  */
  YYSYMBOL_comp_hdr_expr = 707,            /* comp_hdr_expr  */
  YYSYMBOL_comp_hdr_field = 708,           /* comp_hdr_field  */
  YYSYMBOL_udp_hdr_expr = 709,             /* udp_hdr_expr  */
  YYSYMBOL_udp_hdr_field = 710,            /* udp_hdr_field  */
  YYSYMBOL_udplite_hdr_expr = 711,         /* udplite_hdr_expr  */
  YYSYMBOL_udplite_hdr_field = 712,        /* udplite_hdr_field  */
  YYSYMBOL_tcp_hdr_expr = 713,             /* tcp_hdr_expr  */
  YYSYMBOL_tcp_hdr_field = 714,            /* tcp_hdr_field  */
  YYSYMBOL_tcp_hdr_option_type = 715,      /* tcp_hdr_option_type  */
  YYSYMBOL_tcp_hdr_option_field = 716,     /* tcp_hdr_option_field  */
  YYSYMBOL_dccp_hdr_expr = 717,            /* dccp_hdr_expr  */
  YYSYMBOL_dccp_hdr_field = 718,           /* dccp_hdr_field  */
  YYSYMBOL_sctp_chunk_type = 719,          /* sctp_chunk_type  */
  YYSYMBOL_sctp_chunk_common_field = 720,  /* sctp_chunk_common_field  */
  YYSYMBOL_sctp_chunk_data_field = 721,    /* sctp_chunk_data_field  */
  YYSYMBOL_sctp_chunk_init_field = 722,    /* sctp_chunk_init_field  */
  YYSYMBOL_sctp_chunk_sack_field = 723,    /* sctp_chunk_sack_field  */
  YYSYMBOL_sctp_chunk_alloc = 724,         /* sctp_chunk_alloc  */
  YYSYMBOL_sctp_hdr_expr = 725,            /* sctp_hdr_expr  */
  YYSYMBOL_sctp_hdr_field = 726,           /* sctp_hdr_field  */
  YYSYMBOL_th_hdr_expr = 727,              /* th_hdr_expr  */
  YYSYMBOL_th_hdr_field = 728,             /* th_hdr_field  */
  YYSYMBOL_exthdr_expr = 729,              /* exthdr_expr  */
  YYSYMBOL_hbh_hdr_expr = 730,             /* hbh_hdr_expr  */
  YYSYMBOL_hbh_hdr_field = 731,            /* hbh_hdr_field  */
  YYSYMBOL_rt_hdr_expr = 732,              /* rt_hdr_expr  */
  YYSYMBOL_rt_hdr_field = 733,             /* rt_hdr_field  */
  YYSYMBOL_rt0_hdr_expr = 734,             /* rt0_hdr_expr  */
  YYSYMBOL_rt0_hdr_field = 735,            /* rt0_hdr_field  */
  YYSYMBOL_rt2_hdr_expr = 736,             /* rt2_hdr_expr  */
  YYSYMBOL_rt2_hdr_field = 737,            /* rt2_hdr_field  */
  YYSYMBOL_rt4_hdr_expr = 738,             /* rt4_hdr_expr  */
  YYSYMBOL_rt4_hdr_field = 739,            /* rt4_hdr_field  */
  YYSYMBOL_frag_hdr_expr = 740,            /* frag_hdr_expr  */
  YYSYMBOL_frag_hdr_field = 741,           /* frag_hdr_field  */
  YYSYMBOL_dst_hdr_expr = 742,             /* dst_hdr_expr  */
  YYSYMBOL_dst_hdr_field = 743,            /* dst_hdr_field  */
  YYSYMBOL_mh_hdr_expr = 744,              /* mh_hdr_expr  */
  YYSYMBOL_mh_hdr_field = 745,             /* mh_hdr_field  */
  YYSYMBOL_exthdr_exists_expr = 746,       /* exthdr_exists_expr  */
  YYSYMBOL_exthdr_key = 747                /* exthdr_key  */
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
#define YYLAST   7641

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  359
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  389
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1236
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2080

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   604


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
       2,     2,     2,     2,     2,     2,   356,     2,     2,     2,
     353,   354,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   350,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   357,     2,   358,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   351,   355,   352,     2,     2,     2,     2,
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
     345,   346,   347,   348,   349
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   901,   901,   902,   911,   912,   915,   916,   919,   920,
     921,   922,   923,   924,   925,   926,   927,   928,   929,   930,
     931,   932,   933,   934,   935,   936,   937,   938,   940,   942,
     950,   965,   972,   984,   992,   993,   994,   995,  1015,  1016,
    1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,
    1027,  1028,  1029,  1032,  1036,  1043,  1047,  1055,  1059,  1063,
    1070,  1077,  1081,  1088,  1097,  1101,  1105,  1109,  1113,  1117,
    1121,  1125,  1129,  1133,  1137,  1141,  1145,  1151,  1157,  1161,
    1168,  1172,  1180,  1187,  1194,  1198,  1205,  1214,  1218,  1222,
    1226,  1230,  1234,  1238,  1242,  1248,  1254,  1255,  1258,  1259,
    1262,  1263,  1266,  1267,  1270,  1274,  1278,  1282,  1286,  1290,
    1294,  1298,  1302,  1309,  1313,  1317,  1323,  1327,  1331,  1337,
    1343,  1347,  1351,  1355,  1359,  1363,  1367,  1371,  1375,  1379,
    1383,  1387,  1391,  1395,  1399,  1403,  1407,  1411,  1415,  1419,
    1423,  1427,  1431,  1435,  1439,  1443,  1447,  1451,  1455,  1459,
    1463,  1467,  1471,  1475,  1481,  1487,  1491,  1501,  1505,  1509,
    1513,  1517,  1521,  1527,  1531,  1535,  1539,  1543,  1547,  1551,
    1557,  1564,  1570,  1578,  1584,  1592,  1601,  1602,  1605,  1606,
    1607,  1608,  1609,  1610,  1611,  1612,  1615,  1616,  1619,  1620,
    1621,  1624,  1633,  1639,  1654,  1664,  1665,  1666,  1667,  1668,
    1679,  1689,  1700,  1710,  1721,  1732,  1741,  1750,  1759,  1770,
    1781,  1795,  1801,  1802,  1803,  1804,  1805,  1806,  1807,  1812,
    1822,  1823,  1824,  1831,  1852,  1863,  1874,  1887,  1892,  1893,
    1894,  1895,  1900,  1906,  1911,  1916,  1921,  1927,  1932,  1937,
    1938,  1949,  1950,  1953,  1957,  1960,  1961,  1962,  1963,  1967,
    1972,  1973,  1974,  1975,  1978,  1979,  1980,  1981,  1986,  1996,
    2007,  2018,  2030,  2039,  2044,  2050,  2055,  2064,  2067,  2071,
    2077,  2078,  2082,  2087,  2088,  2089,  2090,  2104,  2108,  2112,
    2118,  2123,  2130,  2135,  2140,  2143,  2150,  2157,  2170,  2177,
    2178,  2190,  2195,  2196,  2197,  2198,  2202,  2212,  2213,  2214,
    2215,  2219,  2229,  2230,  2231,  2232,  2236,  2247,  2251,  2252,
    2253,  2257,  2267,  2268,  2269,  2270,  2274,  2284,  2285,  2286,
    2287,  2291,  2301,  2302,  2303,  2304,  2308,  2318,  2319,  2320,
    2321,  2325,  2335,  2336,  2337,  2338,  2339,  2342,  2373,  2380,
    2384,  2387,  2397,  2404,  2415,  2428,  2443,  2444,  2447,  2459,
    2465,  2469,  2472,  2478,  2491,  2496,  2505,  2506,  2509,  2512,
    2513,  2514,  2517,  2532,  2533,  2536,  2537,  2538,  2539,  2540,
    2541,  2544,  2553,  2562,  2570,  2578,  2586,  2594,  2602,  2610,
    2618,  2626,  2634,  2642,  2650,  2658,  2666,  2674,  2682,  2686,
    2691,  2699,  2706,  2713,  2727,  2731,  2738,  2742,  2748,  2760,
    2766,  2773,  2779,  2786,  2787,  2788,  2789,  2792,  2793,  2794,
    2795,  2796,  2797,  2798,  2799,  2800,  2801,  2802,  2803,  2804,
    2805,  2806,  2807,  2808,  2809,  2810,  2811,  2814,  2815,  2818,
    2827,  2831,  2837,  2843,  2848,  2851,  2856,  2861,  2864,  2870,
    2875,  2883,  2884,  2886,  2890,  2898,  2902,  2905,  2909,  2915,
    2916,  2919,  2925,  2929,  2932,  3057,  3062,  3067,  3072,  3077,
    3083,  3113,  3117,  3121,  3125,  3129,  3135,  3139,  3142,  3146,
    3152,  3166,  3180,  3188,  3189,  3190,  3193,  3194,  3197,  3198,
    3213,  3229,  3237,  3238,  3239,  3242,  3243,  3246,  3253,  3254,
    3257,  3271,  3278,  3279,  3294,  3295,  3296,  3297,  3298,  3301,
    3304,  3310,  3316,  3320,  3324,  3331,  3338,  3345,  3352,  3358,
    3364,  3370,  3373,  3374,  3377,  3383,  3389,  3395,  3402,  3409,
    3417,  3418,  3421,  3425,  3433,  3437,  3440,  3445,  3450,  3454,
    3460,  3476,  3495,  3501,  3502,  3508,  3509,  3515,  3516,  3517,
    3518,  3519,  3520,  3521,  3522,  3523,  3524,  3525,  3526,  3527,
    3530,  3531,  3535,  3541,  3542,  3548,  3549,  3555,  3556,  3562,
    3565,  3566,  3577,  3578,  3581,  3585,  3588,  3594,  3600,  3601,
    3604,  3605,  3606,  3609,  3613,  3617,  3622,  3627,  3632,  3638,
    3642,  3646,  3650,  3656,  3661,  3665,  3673,  3682,  3683,  3686,
    3689,  3693,  3698,  3704,  3705,  3708,  3711,  3715,  3719,  3723,
    3728,  3735,  3740,  3748,  3753,  3762,  3763,  3769,  3770,  3771,
    3774,  3775,  3779,  3783,  3789,  3790,  3793,  3799,  3803,  3806,
    3811,  3817,  3818,  3821,  3822,  3823,  3829,  3830,  3831,  3832,
    3835,  3836,  3842,  3843,  3846,  3847,  3850,  3856,  3863,  3870,
    3881,  3882,  3883,  3886,  3894,  3906,  3913,  3916,  3922,  3926,
    3929,  3935,  3944,  3955,  3961,  3987,  3988,  3997,  3998,  4001,
    4010,  4021,  4022,  4023,  4024,  4025,  4026,  4027,  4028,  4029,
    4030,  4031,  4032,  4033,  4034,  4035,  4038,  4061,  4062,  4063,
    4066,  4067,  4068,  4069,  4070,  4073,  4077,  4080,  4084,  4091,
    4094,  4110,  4111,  4115,  4121,  4122,  4128,  4129,  4135,  4136,
    4142,  4145,  4146,  4157,  4163,  4169,  4170,  4173,  4179,  4180,
    4181,  4184,  4191,  4196,  4201,  4204,  4208,  4212,  4218,  4219,
    4226,  4232,  4233,  4236,  4237,  4240,  4246,  4252,  4256,  4259,
    4263,  4267,  4277,  4281,  4284,  4290,  4297,  4301,  4307,  4321,
    4335,  4340,  4348,  4352,  4356,  4366,  4369,  4370,  4373,  4374,
    4375,  4376,  4387,  4398,  4404,  4425,  4431,  4448,  4454,  4455,
    4456,  4459,  4460,  4461,  4464,  4465,  4468,  4484,  4490,  4496,
    4503,  4517,  4525,  4533,  4539,  4543,  4547,  4551,  4555,  4562,
    4567,  4578,  4592,  4598,  4602,  4606,  4610,  4614,  4618,  4622,
    4626,  4632,  4638,  4646,  4647,  4648,  4651,  4652,  4656,  4662,
    4663,  4669,  4670,  4676,  4677,  4683,  4686,  4687,  4688,  4697,
    4708,  4709,  4712,  4720,  4721,  4722,  4723,  4724,  4725,  4726,
    4727,  4728,  4729,  4730,  4731,  4734,  4735,  4736,  4737,  4738,
    4745,  4752,  4759,  4766,  4773,  4780,  4787,  4794,  4801,  4808,
    4815,  4822,  4825,  4826,  4827,  4828,  4829,  4830,  4831,  4834,
    4838,  4842,  4846,  4850,  4854,  4860,  4861,  4871,  4875,  4879,
    4895,  4896,  4899,  4900,  4901,  4902,  4903,  4906,  4907,  4908,
    4909,  4910,  4911,  4912,  4913,  4914,  4915,  4916,  4917,  4918,
    4919,  4920,  4921,  4922,  4923,  4924,  4925,  4926,  4927,  4928,
    4929,  4932,  4952,  4956,  4970,  4974,  4978,  4984,  4988,  4994,
    4995,  4996,  4999,  5000,  5003,  5004,  5007,  5013,  5014,  5017,
    5018,  5021,  5022,  5025,  5026,  5029,  5037,  5064,  5069,  5074,
    5080,  5081,  5084,  5088,  5108,  5109,  5110,  5111,  5114,  5118,
    5122,  5128,  5129,  5132,  5133,  5134,  5135,  5136,  5137,  5138,
    5139,  5140,  5141,  5142,  5143,  5144,  5145,  5146,  5147,  5148,
    5151,  5152,  5153,  5154,  5155,  5156,  5157,  5160,  5161,  5162,
    5163,  5166,  5167,  5168,  5169,  5172,  5173,  5176,  5182,  5190,
    5203,  5210,  5216,  5222,  5231,  5232,  5233,  5234,  5235,  5236,
    5237,  5238,  5239,  5240,  5241,  5242,  5243,  5244,  5245,  5246,
    5247,  5248,  5251,  5260,  5261,  5262,  5263,  5276,  5282,  5283,
    5284,  5287,  5293,  5294,  5295,  5296,  5297,  5300,  5306,  5307,
    5308,  5309,  5310,  5311,  5312,  5313,  5314,  5317,  5321,  5325,
    5332,  5333,  5334,  5335,  5336,  5337,  5338,  5339,  5340,  5341,
    5342,  5343,  5346,  5347,  5348,  5349,  5352,  5353,  5354,  5355,
    5356,  5359,  5365,  5366,  5367,  5368,  5369,  5370,  5371,  5374,
    5380,  5381,  5382,  5383,  5386,  5392,  5393,  5394,  5395,  5396,
    5397,  5398,  5399,  5400,  5402,  5408,  5409,  5410,  5411,  5412,
    5413,  5414,  5415,  5418,  5424,  5425,  5426,  5427,  5428,  5431,
    5437,  5438,  5441,  5447,  5448,  5449,  5452,  5458,  5459,  5460,
    5461,  5464,  5470,  5471,  5472,  5473,  5476,  5480,  5484,  5489,
    5496,  5497,  5498,  5499,  5500,  5501,  5502,  5503,  5504,  5505,
    5508,  5509,  5510,  5511,  5512,  5513,  5514,  5515,  5516,  5517,
    5518,  5519,  5520,  5529,  5530,  5531,  5532,  5533,  5534,  5535,
    5536,  5539,  5545,  5546,  5547,  5550,  5551,  5552,  5553,  5554,
    5555,  5556,  5557,  5558,  5559,  5560,  5561,  5562,  5563,  5564,
    5565,  5566,  5567,  5570,  5571,  5572,  5575,  5576,  5577,  5578,
    5581,  5582,  5583,  5584,  5585,  5588,  5589,  5590,  5591,  5594,
    5599,  5603,  5607,  5611,  5615,  5619,  5624,  5629,  5634,  5639,
    5644,  5651,  5655,  5661,  5662,  5663,  5664,  5667,  5675,  5676,
    5679,  5680,  5681,  5682,  5683,  5684,  5685,  5686,  5689,  5695,
    5696,  5699,  5705,  5706,  5707,  5708,  5711,  5717,  5723,  5729,
    5732,  5738,  5739,  5740,  5741,  5747,  5753,  5754,  5755,  5756,
    5757,  5758,  5761,  5767,  5768,  5771,  5777,  5778,  5779,  5780,
    5781,  5784,  5798,  5799,  5800,  5801,  5802
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
  "\"describe\"", "\"import\"", "\"export\"", "\"monitor\"", "\"all\"",
  "\"accept\"", "\"drop\"", "\"continue\"", "\"jump\"", "\"goto\"",
  "\"return\"", "\"to\"", "\"constant\"", "\"interval\"", "\"dynamic\"",
  "\"auto-merge\"", "\"timeout\"", "\"gc-interval\"", "\"elements\"",
  "\"expires\"", "\"policy\"", "\"memory\"", "\"performance\"", "\"size\"",
  "\"flow\"", "\"offload\"", "\"meter\"", "\"meters\"", "\"flowtables\"",
  "\"number\"", "\"string\"", "\"quoted string\"",
  "\"string with a trailing asterisk\"", "\"ll\"", "\"nh\"", "\"th\"",
  "\"bridge\"", "\"ether\"", "\"saddr\"", "\"daddr\"", "\"type\"",
  "\"vlan\"", "\"id\"", "\"cfi\"", "\"dei\"", "\"pcp\"", "\"arp\"",
  "\"htype\"", "\"ptype\"", "\"hlen\"", "\"plen\"", "\"operation\"",
  "\"ip\"", "\"version\"", "\"hdrlength\"", "\"dscp\"", "\"ecn\"",
  "\"length\"", "\"frag-off\"", "\"ttl\"", "\"protocol\"", "\"checksum\"",
  "\"ptr\"", "\"value\"", "\"lsrr\"", "\"rr\"", "\"ssrr\"", "\"ra\"",
  "\"icmp\"", "\"code\"", "\"seq\"", "\"gateway\"", "\"mtu\"", "\"igmp\"",
  "\"mrt\"", "\"options\"", "\"ip6\"", "\"priority\"", "\"flowlabel\"",
  "\"nexthdr\"", "\"hoplimit\"", "\"icmpv6\"", "\"param-problem\"",
  "\"max-delay\"", "\"ah\"", "\"reserved\"", "\"spi\"", "\"esp\"",
  "\"comp\"", "\"flags\"", "\"cpi\"", "\"port\"", "\"udp\"", "\"sport\"",
  "\"dport\"", "\"udplite\"", "\"csumcov\"", "\"tcp\"", "\"ackseq\"",
  "\"doff\"", "\"window\"", "\"urgptr\"", "\"option\"", "\"echo\"",
  "\"eol\"", "\"nop\"", "\"sack\"", "\"sack0\"", "\"sack1\"", "\"sack2\"",
  "\"sack3\"", "\"sack-permitted\"", "\"timestamp\"", "\"kind\"",
  "\"count\"", "\"left\"", "\"right\"", "\"tsval\"", "\"tsecr\"",
  "\"dccp\"", "\"sctp\"", "\"chunk\"", "\"data\"", "\"init\"",
  "\"init-ack\"", "\"heartbeat\"", "\"heartbeat-ack\"", "\"abort\"",
  "\"shutdown\"", "\"shutdown-ack\"", "\"error\"", "\"cookie-echo\"",
  "\"cookie-ack\"", "\"ecne\"", "\"cwr\"", "\"shutdown-complete\"",
  "\"asconf-ack\"", "\"forward-tsn\"", "\"asconf\"", "\"tsn\"",
  "\"stream\"", "\"ssn\"", "\"ppid\"", "\"init-tag\"", "\"a-rwnd\"",
  "\"num-outbound-streams\"", "\"num-inbound-streams\"", "\"initial-tsn\"",
  "\"cum-tsn-ack\"", "\"num-gap-ack-blocks\"", "\"num-dup-tsns\"",
  "\"lowest-tsn\"", "\"seqno\"", "\"new-cum-tsn\"", "\"vtag\"", "\"rt\"",
  "\"rt0\"", "\"rt2\"", "\"srh\"", "\"seg-left\"", "\"addr\"",
  "\"last-entry\"", "\"tag\"", "\"sid\"", "\"hbh\"", "\"frag\"",
  "\"reserved2\"", "\"more-fragments\"", "\"dst\"", "\"mh\"", "\"meta\"",
  "\"mark\"", "\"iif\"", "\"iifname\"", "\"iiftype\"", "\"oif\"",
  "\"oifname\"", "\"oiftype\"", "\"skuid\"", "\"skgid\"", "\"nftrace\"",
  "\"rtclassid\"", "\"ibriport\"", "\"obriport\"", "\"ibrname\"",
  "\"obrname\"", "\"pkttype\"", "\"cpu\"", "\"iifgroup\"", "\"oifgroup\"",
  "\"cgroup\"", "\"time\"", "\"classid\"", "\"nexthop\"", "\"ct\"",
  "\"l3proto\"", "\"proto-src\"", "\"proto-dst\"", "\"zone\"",
  "\"direction\"", "\"event\"", "\"expectation\"", "\"expiration\"",
  "\"helper\"", "\"label\"", "\"state\"", "\"status\"", "\"original\"",
  "\"reply\"", "\"counter\"", "\"name\"", "\"packets\"", "\"bytes\"",
  "\"avgpkt\"", "\"counters\"", "\"quotas\"", "\"limits\"",
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
  "'='", "'{'", "'}'", "'('", "')'", "'|'", "'$'", "'['", "']'", "$accept",
  "input", "stmt_separator", "opt_newline", "close_scope_arp",
  "close_scope_ct", "close_scope_counter", "close_scope_eth",
  "close_scope_fib", "close_scope_hash", "close_scope_ip",
  "close_scope_ip6", "close_scope_vlan", "close_scope_ipsec",
  "close_scope_list", "close_scope_limit", "close_scope_numgen",
  "close_scope_quota", "close_scope_queue", "close_scope_rt",
  "close_scope_sctp", "close_scope_sctp_chunk", "close_scope_secmark",
  "close_scope_socket", "close_scope_log", "common_block", "line",
  "base_cmd", "add_cmd", "replace_cmd", "create_cmd", "insert_cmd",
  "table_or_id_spec", "chain_or_id_spec", "set_or_id_spec",
  "obj_or_id_spec", "delete_cmd", "get_cmd", "list_cmd",
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
  "stateful_stmt", "stmt", "chain_stmt_type", "chain_stmt", "verdict_stmt",
  "verdict_map_stmt", "verdict_map_expr", "verdict_map_list_expr",
  "verdict_map_list_member_expr", "connlimit_stmt", "counter_stmt",
  "counter_stmt_alloc", "counter_args", "counter_arg", "log_stmt",
  "log_stmt_alloc", "log_args", "log_arg", "level_type", "log_flags",
  "log_flags_tcp", "log_flag_tcp", "limit_stmt", "quota_mode",
  "quota_unit", "quota_used", "quota_stmt", "limit_mode",
  "limit_burst_pkts", "limit_rate_pkts", "limit_burst_bytes",
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
  "tcp_hdr_field", "tcp_hdr_option_type", "tcp_hdr_option_field",
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
      61,   123,   125,    40,    41,   124,    36,    91,    93
};
#endif

#define YYPACT_NINF (-1636)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-967)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1636,  7119, -1636,   282, -1636, -1636,   110,   120,   120,   120,
     888,   888,   888,   888,   888,   888,   888,   888, -1636, -1636,
    4026,   178,  1377,   204,  1625,   194,  6657,   519,  1638,   279,
    6582,   200,   250,   245, -1636, -1636, -1636, -1636,   458,   888,
     888,   888,   888, -1636, -1636, -1636,   772, -1636,   120, -1636,
     120,   147,  5972, -1636,   282, -1636,   -89,   157,   282,   120,
   -1636,    28,   174,  5972,   120, -1636,   -59, -1636,   120, -1636,
   -1636,   888, -1636,   888,   888,   888,   888,   888,   888,   888,
     467,   888,   888,   888,   888, -1636,   888, -1636,   888,   888,
     888,   888,   888,   888,   888,   888,   484,   888,   888,   888,
     888, -1636,   888, -1636,   888,   888,   888,   888,   888,   888,
    1179,   888,   888,   888,   888,   888,   740,   888,   888,   888,
     391,   888,  1193,  1770,  2367,  2476,   888,   888,   888,  2527,
   -1636,   888,  2568,  2594,   888, -1636,   888,   888,   888,   888,
     888,   497,   888, -1636,   888, -1636,  1122,   722,   343,   451,
   -1636, -1636, -1636, -1636,   706,  1061,  1159,  1739,  2148,  1574,
     566,  2115,  1469,   933,   285,   166,   802,   824,  1959,   158,
     753,  2076,   370,   376,    10,   294,   685,   428,   851,  4244,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636,  3886, -1636, -1636,   349,  6227,   284,   780,   597,  6582,
     120, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636,   858, -1636, -1636,   299,
   -1636, -1636,   858, -1636, -1636, -1636, -1636,  1349, -1636, -1636,
   -1636,   888,   888,   888,  -103, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636,   540,   545,   591, -1636, -1636, -1636,   150,   419,
     796, -1636, -1636, -1636, -1636, -1636, -1636,    29,    29, -1636,
     151,   120,  5933,  4649,   443, -1636,   260,    82, -1636, -1636,
   -1636, -1636, -1636,    80,   646,   196, -1636,   742, -1636,   414,
    5972, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,   678,
   -1636,   609, -1636, -1636, -1636,   456, -1636,  4547, -1636, -1636,
     710, -1636,   320, -1636,   336, -1636, -1636, -1636, -1636,   880,
   -1636,    94, -1636, -1636,   719, -1636, -1636, -1636,   983,   756,
     777,   444, -1636,   622, -1636,  5537, -1636, -1636, -1636,   758,
   -1636, -1636, -1636,   763, -1636,  5804,  5804, -1636, -1636,    76,
     500,   528, -1636, -1636,   538, -1636, -1636, -1636,   547, -1636,
     562,   761,  5972, -1636,    28,   174, -1636,   -59, -1636, -1636,
     888,   888,   888,   581, -1636, -1636, -1636,  5972, -1636,   173,
   -1636, -1636, -1636,   181, -1636, -1636, -1636,   431, -1636, -1636,
   -1636, -1636,   441, -1636, -1636,   -59, -1636,   578,   570, -1636,
   -1636, -1636, -1636,   888, -1636, -1636, -1636, -1636,   -59, -1636,
   -1636, -1636,   786, -1636, -1636, -1636, -1636,   888, -1636, -1636,
   -1636, -1636, -1636, -1636,   888,   888, -1636, -1636, -1636,   883,
     886, -1636,   888,   894, -1636,   888, -1636,   888, -1636,   888,
   -1636,   888, -1636, -1636, -1636, -1636,   888, -1636, -1636, -1636,
     888, -1636,   888, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
     888, -1636,   120, -1636, -1636, -1636, -1636,   934, -1636, -1636,
   -1636, -1636, -1636,   946,    65, -1636, -1636,   660, -1636, -1636,
     862,    22, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636,   326,   534, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636,  1111, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636,  2878, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636,  3259, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636,   463, -1636, -1636,   614, -1636, -1636,
   -1636, -1636, -1636, -1636,   639, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636,  2180, -1636, -1636,
   -1636, -1636,   649,   249,   684,   914, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636,   672,   674, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,   858, -1636,
   -1636, -1636, -1636,   -82,   -79,   217,   160, -1636, -1636, -1636,
    4745,   942,  6748,  6582, -1636, -1636, -1636, -1636,  1008,  1036,
      51,   990,  1017,  1021,    85,  1023,  2180,  1028,  6748,  6748,
     748,  6748, -1636, -1636,  1001,  6582,   732,  6748,  6748,  1037,
   -1636,  5606,   108, -1636,  1160, -1636, -1636,   775, -1636,  1049,
    1054,   678, -1636, -1636,   627,  1160,  1056,  1075,  1078,  1160,
     609, -1636,   557, -1636,  6748, -1636,  4943,  1039,  1061,  1159,
    1739,  2148, -1636,  2115,   134, -1636, -1636, -1636,  1098, -1636,
   -1636, -1636, -1636,  6748, -1636,  1062,  1093,  1176,   846,   804,
     615, -1636, -1636, -1636, -1636,  1215,   989,  1224, -1636, -1636,
   -1636, -1636,  1226, -1636, -1636, -1636, -1636,   392, -1636, -1636,
    1230,  1235, -1636,  1120,  1143, -1636, -1636,   710, -1636,  1247,
   -1636, -1636, -1636, -1636,  1249, -1636,  5141, -1636,  1249, -1636,
      14, -1636, -1636,   880, -1636,  1279, -1636,   120, -1636,   927,
   -1636,   120,    78, -1636,  7215,  7215,  7215,  7215,  7215,  6582,
     146,  6946, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636,  7215, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636,   613, -1636,  1067,  1272,  1275,   959,
     696,  1309, -1636, -1636, -1636,  6946,  6748,  6748,  1220,   109,
     282,  1317, -1636,   892,   282,  1236, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636,  1305,   998,  1000,  1003, -1636,
    1004,  1009, -1636, -1636, -1636, -1636,  1080,  1074,   833,  1160,
   -1636,  1264,  1273,  1278,  1283, -1636,  1288,  1042, -1636, -1636,
   -1636, -1636, -1636, -1636,  1274, -1636, -1636, -1636, -1636, -1636,
     888, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636,  1304,   722, -1636, -1636,
   -1636, -1636,  1307, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,   462, -1636,
   -1636,  2972, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636,  1229,   812,  1271,   878,   878,
   -1636, -1636, -1636,  1191, -1636, -1636, -1636, -1636,  1157,  1189,
   -1636,  1196,  1197,  1200,   193, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636,  1326,  1330, -1636, -1636, -1636, -1636,  1006,
   -1636,  1185, -1636, -1636, -1636, -1636, -1636, -1636, -1636,  1332,
    1334,  1106, -1636,  1339,    60, -1636, -1636, -1636,  1087,  1091,
    1096,  1342, -1636, -1636,   748, -1636, -1636, -1636,  1348, -1636,
   -1636, -1636, -1636,  6748,  2148,  2115,  1447,  5339, -1636,    94,
     198,  1446,  1160,  1160,  1353,  6582,  6748,  6748,  6748, -1636,
    1354,  6748,  1414,  6748, -1636, -1636, -1636, -1636,  1386, -1636,
      54,  1457, -1636, -1636,   334,   655,   249, -1636,   408,   439,
     142,  1455, -1636,  6748, -1636,   742,  1296,   514,   212, -1636,
     816,  1309,   742, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636,  1341,   219, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636,  1012,  1027,  1429,  1030, -1636,  6748,  1497,  6748,
   -1636, -1636, -1636,   417,   542,  6748,  1153, -1636, -1636,  6748,
    6748,  6748,  6748,  6748,  1407,  6748,  6748,   161,  6748,  1249,
    6748,  1426,  1503,  1433,  3074,  3074, -1636, -1636, -1636,  6748,
     989,  6748,   989, -1636,  1501,  1507, -1636,   732, -1636,  6582,
   -1636,  6582, -1636, -1636, -1636,  1067,  1272,  1275, -1636,   742,
   -1636, -1636, -1636, -1636, -1636, -1636,  1165,  7215,  7215,  7215,
    7215,  7215,  7215,  7215,  7215,  7285,  7215,  7215,   705, -1636,
     915, -1636, -1636, -1636, -1636, -1636,  1428, -1636,   292,   162,
     776,  3283,  2342,  2453,   367, -1636, -1636, -1636, -1636, -1636,
   -1636,  1181,  1183,  1184, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,  1534, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636,  1538, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636,  1188,  1190, -1636, -1636, -1636, -1636, -1636, -1636,
    1106,   153,  1437, -1636, -1636, -1636, -1636, -1636,  1209, -1636,
   -1636, -1636,  1265,  1486, -1636,  1386,   882, -1636,   590,    54,
   -1636,   386, -1636, -1636,  6748,  6748,  1546, -1636,  1449,  1449,
   -1636,   198, -1636, -1636, -1636,  1202,  1446,  5972,   198, -1636,
   -1636, -1636, -1636, -1636, -1636,  6748, -1636, -1636,   118,  1257,
    1262,  1543, -1636, -1636, -1636,  1266,    14, -1636,  6582,    14,
    6748,  1525, -1636,  7167, -1636,  1382,  1290,  1276,   514, -1636,
    1449,  1449, -1636,   212, -1636,  5606, -1636,  4283, -1636, -1636,
   -1636, -1636,  1571, -1636, -1636,  1227, -1636, -1636,  1227, -1636,
   -1636,  1227, -1636, -1636,  6748, -1636, -1636, -1636, -1636, -1636,
    1062,  1093,  1176, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
    1575,  6748,  1415,  6748, -1636, -1636, -1636, -1636,   989, -1636,
     989,  1249, -1636,   140,  5972,  5675,   115, -1636, -1636, -1636,
    1317,  1576, -1636, -1636,  1067,  1272,  1275, -1636,   111,  1317,
   -1636, -1636,   816,  7215,  7285, -1636,  1479,  1551, -1636, -1636,
   -1636, -1636, -1636,   120,   120,   120,   120,   120,  1488,   513,
     120,   120,   120,   120, -1636, -1636, -1636,   282, -1636,    62,
    1491,  1498, -1636, -1636, -1636,   282,   282,   282,   282,   282,
    6582, -1636,  1449,  1449,  1245,  1246,  1496,    96,  1102,  1417,
   -1636, -1636, -1636,   282,   282,   233, -1636,  6582,  1449,  1252,
      96,  1102, -1636, -1636, -1636,   282,   282,   233,  1504,  1268,
    1528, -1636, -1636, -1636, -1636,  2919,  3617,  2746,  2923,  1532,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636,  2158, -1636, -1636,
    1521, -1636, -1636,  1527, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636,  1529, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
     169,   133,   306,  1531, -1636, -1636, -1636, -1636, -1636,  1257,
    1262, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636,  1266, -1636, -1636, -1636, -1636, -1636, -1636, -1636,  6748,
   -1636, -1636, -1636, -1636,  6582,  1282,   198, -1636, -1636, -1636,
   -1636, -1636,   838,  1607, -1636,  1533, -1636,  1535, -1636,   838,
    1539, -1636, -1636, -1636, -1636, -1636, -1636, -1636,  6748,    29,
      29,   742,  1309, -1636,   116,  1540, -1636,   748, -1636, -1636,
   -1636, -1636, -1636, -1636,   282, -1636,   219, -1636, -1636, -1636,
   -1636,  6748, -1636,  1556, -1636,  1249,  1249,  6582, -1636,   393,
    1293,  1642,   742, -1636,  1317,  1317,  1445,  1550, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,   120,   120,
     120, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636,  1612, -1636, -1636, -1636, -1636, -1636, -1636,   682, -1636,
     282,   282,   -59, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636,   876, -1636, -1636, -1636, -1636, -1636,
     970, -1636, -1636, -1636, -1636, -1636,   564,   282,   -59,   656,
     970, -1636, -1636, -1636,  1506,   209,   282, -1636, -1636, -1636,
   -1636, -1636, -1636,  1019,   955,  1240, -1636, -1636,  1647, -1636,
    1106, -1636, -1636,  1310,   411,   888, -1636, -1636, -1636, -1636,
   -1636,  1449,  1562,   411,  1582,   888, -1636, -1636, -1636, -1636,
   -1636,  1587,   888, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636,  5972, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636,  1409, -1636,    68, -1636,
   -1636, -1636,    54, -1636, -1636, -1636, -1636, -1636, -1636,  1593,
    1413,  1386, -1636, -1636, -1636,  6748,  1351,  6582, -1636, -1636,
    1380,  5675, -1636, -1636,  1516,   282,  1355,  1356,  1358,  1359,
    1362, -1636, -1636, -1636,  1363,  1369,  1370,  1371,  1622,  6582,
   -1636, -1636, -1636, -1636,    96, -1636,  1102, -1636,  6416, -1636,
   -1636,  1041, -1636,   214,   282,    33,   282, -1636, -1636, -1636,
   -1636, -1636,  1626, -1636,  1381, -1636, -1636,   282,   282, -1636,
     282,   282,   282,   282,   282, -1636,  1598,   282, -1636,  1389,
   -1636, -1636, -1636, -1636, -1636,  1632,  1257,  1262, -1636, -1636,
    1392,   742, -1636, -1636,  1445, -1636, -1636, -1636, -1636, -1636,
    1394,  1395,  1400, -1636, -1636, -1636, -1636,  1291, -1636, -1636,
   -1636,  6582,   282,  1744,  1745,    96, -1636, -1636, -1636, -1636,
     282,   876,  1645, -1636, -1636, -1636,   734, -1636, -1636, -1636,
   -1636, -1636,   117, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636,  1651, -1636, -1636, -1636, -1636, -1636, -1636, -1636,   411,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,  1516,  2150,
    3951,  3212,  3801,  3065, -1636, -1636, -1636,  1757,  2360,   764,
     813,   102,  1412,  1506,   682, -1636,  6582,   876, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636,  1662,  1664,   107, -1636,  1763,
     123, -1636,   282, -1636, -1636, -1636, -1636,   282,   282,   282,
     282,   282,  1026,  1035,  2059,   282,   282,   282,   282, -1636,
   -1636,   209, -1636, -1636,  1767, -1636, -1636, -1636, -1636, -1636,
    1669,  1651,   282, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
     282,   282,   282, -1636, -1636, -1636, -1636, -1636, -1636, -1636
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     363,   363,   363,   363,   363,   363,   363,   363,   367,   370,
     363,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   369,     8,    14,    15,     0,   363,
     363,   363,   363,    35,    34,     3,     0,    38,     0,   364,
       0,   388,     0,    33,     0,   358,     0,     0,     0,     0,
     532,    53,    55,     0,     0,   227,     0,   249,     0,   272,
      39,   363,    40,   363,   363,   363,   363,   363,   363,   363,
       0,   363,   363,   363,   363,    41,   363,    42,   363,   363,
     363,   363,   363,   363,   363,   363,     0,   363,   363,   363,
     363,    43,   363,    44,   363,   394,   363,   394,   363,   394,
     394,   363,   363,   394,   363,   394,     0,   363,   394,   394,
       0,   363,   394,   394,   394,   394,   363,   363,   363,   394,
      18,   363,   394,   394,   363,    46,   363,   363,   363,   363,
     394,     0,   363,    47,   363,    48,     0,     0,     0,   689,
     660,   359,   360,   361,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     867,   868,   869,   870,   871,   872,   873,   874,   875,   876,
     877,   878,   879,   880,   881,   882,   883,   884,   885,   886,
     888,     0,   890,   889,     0,     0,     0,     0,    17,     0,
       0,    52,   656,   655,   661,   662,   191,   672,   673,   666,
     858,   667,   670,   674,   671,   668,   669,   663,   974,   975,
     976,   977,   978,   979,   980,   981,   982,   983,   984,   985,
     986,   987,   988,   989,   990,   991,   664,  1190,  1191,  1192,
    1193,  1194,  1195,  1196,  1197,   665,     0,   188,   189,     0,
      49,   172,     0,    50,   174,   177,    51,   178,   368,   365,
     366,   363,   363,   363,    10,   782,   755,   757,    37,    36,
     371,   373,     0,     0,     0,   390,   389,   391,     0,   522,
       0,   640,   641,   642,   849,   850,   851,   427,   428,   854,
     647,     0,     0,     0,   443,   451,     0,   475,   500,   512,
     513,   589,   595,   616,     0,     0,   894,     7,    58,   396,
     398,   411,   399,   211,   426,   407,   431,   406,    10,   441,
      28,   449,   404,   405,   414,   503,   415,     0,   416,   425,
     520,   419,   588,   420,   594,   421,   422,   417,    22,   614,
     423,     0,   424,   409,     0,   646,   408,   691,   694,   696,
     698,   700,   701,   708,   710,     0,   709,   653,   430,   858,
     412,   418,   410,   663,    29,     0,     0,    32,   382,     0,
       0,     0,    57,   376,     0,    61,   242,   241,     0,   379,
       0,     0,     0,   532,    78,    80,   227,     0,   249,   272,
     363,   363,   363,    10,   782,   755,   757,     0,   118,     0,
     102,   103,   104,     0,    96,    97,   105,     0,    98,    99,
     106,   107,     0,   100,   101,     0,   108,     0,   110,   111,
     759,   760,   758,   363,    10,    19,    21,    26,     0,   141,
     153,   395,   155,   120,   121,   122,   123,   363,   124,   126,
     150,   149,   148,   142,   363,   394,   146,   145,   147,   759,
     760,   761,   363,     0,    10,   363,   127,   363,   130,   363,
     133,   363,   139,    19,    21,    26,   363,   136,    45,    10,
     363,   157,   363,   160,    21,   163,   164,   165,   166,   169,
     363,   168,     0,   996,   993,   994,   995,     0,   680,   681,
     682,   683,   684,   686,     0,   899,   901,     0,   900,    27,
       0,     0,  1188,  1189,  1187,   998,   999,  1000,    11,  1006,
    1002,  1003,  1004,  1005,    16,     0,     0,  1008,  1009,  1010,
    1011,  1012,     8,  1030,  1031,  1025,  1020,  1021,  1022,  1023,
    1024,  1026,  1027,  1028,  1029,     0,    14,  1042,  1045,  1044,
    1043,  1046,  1047,  1048,  1041,  1050,  1051,  1052,  1053,  1049,
    1062,  1063,  1055,  1056,  1057,  1059,  1058,  1060,  1061,    15,
    1065,  1070,  1067,  1066,  1071,  1069,  1068,  1072,  1064,  1075,
    1078,  1074,  1076,  1077,  1073,  1081,  1080,  1079,  1083,  1084,
    1085,  1082,  1089,  1090,  1087,  1088,  1086,  1095,  1092,  1093,
    1094,  1091,  1108,  1102,  1105,  1106,  1100,  1101,  1103,  1104,
    1107,  1109,     0,  1096,  1134,  1132,  1133,  1131,  1186,  1183,
    1184,     0,  1185,    24,  1204,    14,  1203,   926,    15,  1202,
    1205,   924,   925,    17,     0,    23,    23,     0,  1206,  1209,
    1208,  1212,  1211,  1213,     0,  1210,  1200,  1199,  1198,  1221,
    1218,  1216,  1217,  1219,  1220,  1215,  1224,  1223,  1222,  1228,
    1227,  1230,  1226,  1229,  1225,   859,   862,   863,   864,    26,
     865,    17,   857,   860,   861,   941,   942,   948,   934,   935,
     933,   943,   944,   964,   937,   946,   939,   940,   945,   936,
     938,   931,   932,   962,   961,   963,    26,     0,     9,   949,
     905,   904,     0,   708,     0,     0,    23,  1232,  1234,  1235,
    1236,  1231,   909,   910,   887,   908,     0,   654,   171,   190,
     173,   179,   180,   182,   181,   184,   185,   183,   186,   779,
     779,   779,    63,     0,     0,   475,     0,   385,   386,   387,
       0,     0,     0,     0,   856,   855,   852,   853,     0,     0,
       0,   859,   857,     0,     0,     0,     0,     9,     0,     0,
     484,     0,   473,   474,     0,     0,     0,     0,     0,     0,
       6,     0,     0,   712,     0,   397,   400,     0,   403,     0,
       0,   442,   445,   413,     0,     0,     0,     0,     0,     0,
     450,   452,     0,   499,     0,   821,     0,     0,    11,    16,
       8,    14,   820,    15,     0,   824,   822,   823,     0,   819,
     818,   810,   811,     0,   550,   553,   555,   557,   559,   560,
     565,   570,   568,   569,   571,   573,   511,   537,   538,   548,
     812,   539,   546,   540,   547,   543,   544,     0,   541,   542,
       0,   572,   545,     0,     0,   529,   528,   521,   524,     0,
     607,   608,   609,   587,   592,   605,     0,   593,   598,   610,
       0,   632,   633,   615,   617,   620,   630,     0,   658,     0,
     657,     0,     0,   648,     0,     0,     0,     0,     0,     0,
       0,     0,   842,   843,   844,   845,   846,   847,   848,    11,
      16,     8,    14,   834,   835,    15,   836,   833,   832,   837,
     830,   831,   829,   838,    24,   840,     0,   825,   795,   826,
     705,   706,   807,   794,   784,   783,   799,   801,   803,   805,
     806,   793,   827,   828,   796,     0,     0,     0,     0,     7,
       0,   749,   748,   806,     0,     0,   327,    75,   195,   212,
     228,   254,   273,   392,    77,     0,     0,     0,     0,    84,
       0,     0,   779,   779,   779,    86,     0,     0,   475,     0,
      95,     0,     0,     0,     0,   109,     0,     0,   779,   113,
     116,   114,   117,   119,     0,   156,   125,   144,   143,     9,
     363,   129,   128,   131,   134,   140,   135,   132,   138,   137,
     159,   158,   161,   162,   167,   170,     0,     0,   679,   677,
     678,    12,     0,   897,   690,   687,   688,   997,  1001,    11,
      14,    11,    14,  1007,  1032,  1033,  1034,  1035,    14,  1017,
    1054,     0,  1112,  1122,  1113,  1120,  1110,  1111,  1115,  1116,
    1117,  1118,  1119,  1114,  1121,  1098,  1138,  1135,  1136,  1137,
    1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,
    1149,  1150,  1151,  1152,  1169,    25,  1181,   920,   921,   927,
      23,   922,  1201,     0,     0,   866,   947,   950,   951,     0,
     953,     0,   952,   954,   955,     9,     9,   956,   928,     0,
       0,   902,  1233,     0,     0,   675,   175,   187,     0,     0,
       0,     0,   292,    10,   484,   317,    19,   297,     0,    21,
     322,   756,    26,     0,    14,    15,   514,     0,   523,     0,
     634,   636,     0,     0,     0,     0,     0,     0,     0,     9,
       0,     0,   956,     0,   444,    19,   482,   483,     0,    21,
       0,     0,   629,    22,   624,   623,     0,   628,   626,   627,
       0,   601,   603,     0,   724,     7,     7,   726,   721,   723,
     806,   745,     7,   711,   393,   220,   447,   448,   446,   465,
      11,     0,     0,   463,   459,   454,   455,   456,   457,   460,
     458,   453,     0,     0,     0,     0,   579,     0,   574,     0,
     813,   816,   817,   814,   815,     0,     0,   537,   546,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   581,
       0,     0,     0,     0,     0,     0,   526,   527,   525,     0,
       0,     0,   596,   619,   624,   623,   618,     0,   659,     0,
     650,     0,   649,   692,   693,   695,   697,   699,   702,     7,
     432,   434,   707,   814,   815,   839,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   790,   789,
     806,   892,   973,   751,   750,    30,     0,    31,     0,     0,
       0,     0,     0,     0,     0,    94,   195,   212,   228,   254,
     273,     0,     0,     0,    10,    19,    21,    26,   383,   372,
     374,   377,   380,   273,     9,   154,   151,     9,     0,   685,
     676,    27,  1013,  1015,  1014,  1016,  1036,  1037,  1039,  1038,
    1040,  1019,    14,     0,  1125,  1124,  1123,  1126,  1127,  1128,
    1129,  1130,  1097,  1166,  1165,  1167,  1168,  1174,  1156,  1157,
    1158,  1159,  1171,  1160,  1161,  1162,  1163,  1164,  1172,  1173,
    1175,  1176,  1177,  1178,  1179,  1180,  1153,  1155,  1154,  1170,
      24,   923,     0,     0,    14,    14,    15,    15,   929,   930,
     902,   902,     0,    13,   907,   911,   912,    17,     0,   307,
     312,   302,     0,     0,    64,     0,     0,    71,     0,     0,
      66,     0,    73,   516,     0,     0,   515,   637,     0,     0,
     731,   635,   727,   896,   895,     0,   720,     0,   718,   893,
     891,     9,   439,     9,     9,     0,     9,   472,     0,   485,
     488,     0,   481,   477,   476,   478,     0,   611,     0,     0,
       0,     0,   715,     0,   716,     0,    10,     0,   725,   734,
       0,     0,   744,   722,   732,   714,   713,     0,   464,    14,
     468,   469,   461,   467,   501,     0,   505,   502,     0,   507,
     510,     0,   509,   580,     0,   584,   586,   549,   551,   552,
     554,   556,   558,   566,   567,   561,   564,   563,   562,   576,
     575,     0,     0,     0,   965,   966,   967,   968,   590,   606,
     597,   599,   631,     0,     0,     0,     0,   435,   841,   792,
     786,     0,   797,   798,   800,   802,   804,   791,   703,   785,
     704,   808,   809,     0,     0,   703,     0,     0,    76,   329,
     328,   331,   330,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,   197,   196,     0,   194,     0,
       0,     0,    56,   214,   213,     0,     0,     0,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
      59,   230,   229,     0,     0,     0,   401,     0,     0,     0,
       0,     0,    60,   256,   255,     0,     0,     0,     0,     0,
       0,    10,    62,   275,   274,     0,     0,     0,     0,     0,
     307,   312,   302,    87,    92,    88,    93,     0,   115,   152,
       0,   898,  1018,     0,  1182,  1207,  1214,   957,   958,   959,
     960,    20,     0,    13,   903,   919,   915,   914,   913,    17,
       0,     0,     0,     0,    10,   294,   293,   296,   295,   485,
     488,    19,   319,   318,   321,   320,    21,   299,   298,   301,
     300,   478,    26,   324,   323,   326,   325,   517,   519,     0,
     362,   729,   730,   728,     0,     0,   719,   970,   440,   971,
       9,   969,     0,   490,   492,     0,    19,     0,    19,     0,
       0,    21,   625,   621,   622,    22,    22,   602,     0,     0,
       0,     7,   746,   747,     0,     0,   736,   484,   735,   742,
     743,   733,   429,   221,     0,   462,     0,   504,   506,   508,
     577,     0,   583,     0,   585,   591,   600,     0,   638,     0,
       0,     0,     7,   433,   788,   787,   533,     0,   384,   291,
     375,   211,   378,   227,   249,   381,   272,   193,     0,     0,
       0,   291,   291,   291,   291,   198,   356,   357,   353,   355,
     354,     0,   352,   215,   217,   216,   219,   218,     0,   225,
       0,     0,     0,   271,   270,   268,   269,   332,   334,   335,
     333,   288,   336,   289,     0,   287,   245,   246,   248,   247,
       0,   244,   239,   240,   236,   402,     0,     0,     0,     0,
       0,   267,   266,   264,     0,     0,     0,   278,    79,    81,
      82,    83,    85,     0,     0,     0,   112,   992,     0,   906,
     902,   918,   916,     0,     0,     0,     9,   309,   308,   311,
     310,     0,     0,     0,     0,     0,     9,   314,   313,   316,
     315,     0,     0,     9,   304,   303,   306,   305,   752,    65,
     780,   781,    72,    67,   754,    74,   518,     0,   651,   972,
     494,   495,   496,   497,   498,   487,     0,   470,     0,   489,
     471,   491,     0,   480,   612,   613,   604,   717,     9,     0,
       0,     0,   222,   466,   578,     0,     0,     0,   639,   645,
       0,   437,   436,   534,   535,     0,     0,     0,     0,     0,
       0,   291,   291,   291,     0,     0,     0,     0,     0,     0,
     232,   234,   235,   237,     0,   231,     0,   233,     0,   257,
     265,     0,   263,     0,     0,     0,     0,   281,   279,     9,
       9,     9,     0,    13,     0,   765,   764,     0,     0,    69,
       0,     0,     0,     0,     0,    70,     0,     0,    68,     0,
     486,   493,   479,   740,     9,     0,   485,   488,   582,   643,
       0,     7,   536,   530,   533,   327,   212,   228,   254,   273,
       0,     0,     0,   292,   317,   297,   322,   351,   226,   290,
     243,     0,     0,     0,   223,     0,    10,    19,    21,    26,
       0,     0,     0,   346,   340,   339,   343,   338,   341,   342,
     276,   285,     0,   282,   286,   277,    90,    91,    89,  1099,
     917,     0,   771,   773,   776,   777,   774,   775,   778,     0,
     767,   652,   741,    10,    19,    19,   644,   438,   535,     0,
       0,     0,     0,     0,   307,   312,   302,     0,     0,     0,
       0,     0,     0,     0,     0,   260,     0,     0,   250,   252,
     251,   253,   262,   258,   347,     0,     0,     7,   280,     0,
       0,   768,     0,   737,   738,   739,   531,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   348,
     349,     0,   337,   261,   224,   259,   345,   344,   284,   283,
       0,     0,     0,   766,   210,   199,   200,   201,   202,     9,
       9,     9,    10,    19,    21,    26,   350,   770,   769,   772,
       0,     0,     0,   203,   208,   204,   209,   206,   207,   205
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1636, -1636,    -1, -1110,    32,   759,  -314,  -463, -1636, -1462,
     -18,   -15,  1254,  -624, -1636,  -375, -1636,  -445, -1070,  -550,
    -814, -1636,  -468,   485, -1636,    20, -1636, -1636,  1759, -1636,
   -1636, -1636, -1636, -1636, -1636,  1396, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
      12, -1636,  1387, -1636,   521,  -312, -1227, -1636, -1636, -1445,
    -388, -1221,  -382,   229,   -84,  -371, -1636, -1220, -1225, -1636,
    -387, -1224,  -244, -1636,  -219,   -75, -1451,  -857,  -128,  -127,
   -1480, -1470, -1468,  -124,  -125,  -113, -1636, -1636,  -190, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636,   144,  -664, -1278,
    1727,   -45,  3026, -1636,  1967, -1636, -1636,   139, -1636,   311,
     652, -1636, -1636,  2602, -1636,  -524,  1435, -1636, -1636,   154,
    1728,   992,  2773,   -33, -1636, -1636, -1238, -1230,  -317, -1636,
   -1636, -1636, -1636, -1636, -1636,   128, -1636, -1636, -1636, -1636,
    1043, -1636, -1636, -1636,  1038, -1636, -1636, -1636,   156, -1636,
    1520, -1300,   208, -1636, -1040, -1476, -1289, -1464, -1274,   189,
     188, -1636, -1636,  -574, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636,   994,  -321,  1452,   -85,  -146,  -369,   657,   654,   663,
   -1636,  -709, -1636, -1636, -1636, -1636, -1636, -1636,  1678, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,  -331,   637,
   -1636, -1636, -1636, -1636,  1005,   464,  -794,   449,  1103,   659,
   -1167, -1636, -1636,  1581, -1636, -1636, -1636, -1636,  1002, -1636,
   -1636,   207,   -29,  -745,  -335,   230,   -25, -1636, -1636, -1636,
     875,   -26, -1636, -1636, -1636, -1636, -1636,  -178,  -181, -1636,
   -1636,   626,  -714,  1672,   -56, -1636,   728, -1125, -1636, -1370,
   -1636, -1636,   493, -1204, -1636, -1636,   469,   459, -1636, -1636,
    1512,  -559,  1487,  -553,  1493,  -525,  1485,  1784, -1636, -1635,
   -1636, -1636,  -143, -1636, -1636,   -78,  -548,  1505, -1636,  -315,
    -304,  -767,  -769,  -766, -1636,  -294,  -751, -1636,  1425,  1336,
    -768, -1636, -1328,  -292,   259,  1608, -1636,   -35, -1636,   328,
   -1636, -1257, -1636,   478, -1636, -1636, -1636, -1636, -1636,   548,
    -240,   692,  1280,   863,  1615,  1617, -1636, -1636,  -504,   143,
   -1636, -1636, -1636,  1090, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636,   900, -1636, -1636, -1636,
   -1636, -1636, -1636,   885, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636,
   -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636, -1636
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,  1563,   771,  1182,  1078,   732,  1180,  1290,  1595,
    1233,  1234,  1181,   714,   478,   970,  1779,   971,   859,  1061,
    1056,  1340,   972,  1003,   783,  1564,    45,    46,    47,    72,
      85,    87,   412,   416,   421,   408,   101,   103,   130,   975,
     440,   135,   143,   145,   260,   263,   266,   267,   728,  1086,
     261,   211,   380,  1517,  1260,   381,  1261,  1427,  1942,  1728,
     384,  1262,   385,  1750,  1751,   388,  1950,  1263,  1543,  1735,
     390,  1264,  1886,  1962,  1963,  1743,  1744,  1856,  1363,  1368,
    1602,  1600,  1601,  1366,  1371,  1259,  1745,  1525,  1884,  1956,
    1957,  1958,  2003,  1526,  1527,  1718,  1719,  1698,   212,  1631,
      48,    49,    59,   415,    51,   419,  1701,    65,   424,  1703,
      69,   429,  1706,   410,   411,  1699,   285,   286,   287,    52,
     392,  1380,   442,  1529,   319,   320,  1545,   321,   322,   323,
     324,   325,   326,  1230,  1476,  1477,   327,   328,   329,   781,
     782,   330,   331,   790,   791,  1170,  1164,  1432,  1433,   332,
    1098,  1405,  1651,   333,  1128,  1646,  1399,  1648,  1400,  1401,
    1825,   334,   335,  1436,   793,   336,   337,   338,   339,   340,
     847,   848,  1502,   379,  1854,  1923,   814,   815,   816,   817,
     818,   819,   820,  1456,   821,   822,   823,   824,   825,   826,
     341,   342,   853,   343,   344,   857,   345,   346,   854,   855,
     347,   348,   349,   863,   864,  1131,  1132,  1133,   865,   866,
    1109,  1110,   350,   351,   352,   353,   354,   872,   873,   355,
     356,   213,   827,   869,   908,   828,   357,   217,  1001,   503,
     504,   829,   511,   358,   359,   360,   361,   362,   363,   910,
     911,   912,   364,   365,   366,   772,   773,  1387,  1388,  1146,
    1147,  1148,  1381,  1382,  1423,  1418,  1419,  1424,  1149,  1661,
     930,  1608,   733,  1620,   735,  1626,   736,   433,   463,  1897,
    1807,  2020,  2021,  1790,  1800,  1088,  1615,   734,   367,   931,
     932,   916,   917,   918,   919,  1150,   921,   830,   831,   832,
     924,   925,   368,   746,   833,   672,   673,   220,   370,   834,
     509,  1353,   702,   835,  1084,   715,  1357,  1599,   223,   836,
     634,   838,   635,   839,   697,   698,  1075,  1076,   699,   840,
     841,   371,   372,   842,   228,   497,   229,   518,   230,   524,
     231,   532,   232,   546,  1018,  1302,   233,   554,   234,   559,
     235,   569,   236,   578,   237,   584,   238,   587,   239,   591,
     240,   596,   241,   601,   242,   613,  1035,  1312,   243,   617,
    1054,  1339,  1322,  1328,  1317,  1055,   244,   623,   245,   514,
     246,   247,   648,   248,   636,   249,   638,   250,   640,   251,
     645,   252,   655,   253,   658,   254,   664,   255,   711
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   214,    53,   776,   218,   216,   747,   988,   948,  1059,
     387,   777,   951,   858,   778,   949,   870,   369,   269,   318,
    1151,    44,   270,   214,   703,  1557,   218,   950,   369,   987,
     382,   716,  1546,  1546,   214,  1412,  1414,   218,  1555,   993,
    1566,   967,  1425,   965,   264,   279,  1569,  1567,   741,  1568,
     914,  1137,  1473,   374,  1365,  1007,   973,   377,   937,  1577,
     441,   915,   441,  1407,   441,   441,  1213,   268,   441,  1621,
     441,   920,  1101,   441,   441,   769,  1609,   441,   441,   441,
     441,   933,   933,   947,   441,  1663,  1062,   441,   441,   955,
    1235,  1610,  1775,  1591,  1593,   441,  1474,   837,   986,  1759,
    1773,  1632,  1756,  1774,  1186,  1691,  1223,  1224,  1226,  1225,
    1154,   770,  1227,   770,   935,  1152,   150,   867,  -660,  1475,
     969,  1165,  1692,   871,  2017,  1169,  -660,  -660,  -660,  -660,
    2051,  1781,    55,  1810,     3,  1231,  1961,     4,  1642,     5,
    1716,  1717,  1669,  1670,   674,  1687,  1811,  1114,  1005,  1217,
     981,    56,    57,    58,    66,    67,  1082,  1403,  1902,     6,
       7,     8,     9,     3,   765,   990,     4,    63,     5,   867,
       3,  1911,   641,     4,  1093,     5,   214,  1633,   998,   218,
     214,  -753,  1099,   218,   867,   625,  1096,  1119,     6,     7,
       8,     9,   280,  1077,   281,     6,     7,     8,     9,  1737,
     935,  1065,  1091,   378,   282,   151,   152,   153,   383,   628,
    1961,  1102,   389,   748,    54,   396,   397,   398,  1838,  1355,
    1094,  1643,  1791,    55,  1738,  1739,  1408,    71,  1066,  1792,
     961,   423,   425,   426,   740,  1689,  1952,     4,   962,     5,
     407,   438,   766,  1546,   642,   643,   644,   102,  -753,   749,
     449,   450,  1122,    86,  1730,  1731,   456,   879,   256,   625,
     215,   375,  1783,   151,   152,   153,  1793,   674,   718,  1092,
    1757,   614,  1095,   386,   720,   625,    55,   487,   488,   627,
     768,   491,   215,   628,    55,   369,     4,  1378,     5,   219,
    1379,   214,   317,   215,   218,  1101,     4,   210,     5,   628,
    1794,  1420,  1784,   881,  1421,  1006,  1336,     3,   262,   913,
       4,   219,     5,   999,  1000,  1755,  1953,  1954,   588,   913,
     913,   625,   219,  1337,   615,   616,   144,  1755,   589,   590,
    1557,  1496,     6,     7,     8,     9,   907,  1546,  1546,  1404,
    1740,   387,  -655,  1555,  2022,   628,   907,   907,   265,  -655,
    -655,  -655,  -655,  1644,   717,  1338,  -621,   369,   221,   944,
    1741,  1742,  1430,   214,  1377,   761,   218,  1431,     3,   387,
     210,     4,   369,     5,   960,   505,   506,   507,   214,  -192,
     221,   218,   387,   762,   763,   210,  1120,     3,  -655,   210,
       4,   221,     5,     6,     7,     8,     9,  1274,  1847,   631,
     632,  1795,  1115,  1644,   849,  1276,  1356,  1539,  1558,  1275,
     441,  1559,     6,     7,     8,     9,  -670,  1839,   210,  1801,
     856,   646,   304,  -670,  -670,  -670,  -670,   936,   585,  1221,
    1951,  1970,  1633,  1943,  1277,   215,  1009,  1785,   306,   215,
    1984,   744,   744,   307,   586,   750,   647,  -671,  1383,  1384,
     210,  1010,  1457,  1985,  -671,  -671,  -671,  -671,   210,  1755,
    1153,  1254,  -670,   210,   219,  1409,  -660,  1693,   219,  2018,
     774,  1482,  1483,  1485,  1484,  2052,  1200,  1486,  1201,   633,
     459,  1691,   283,   284,  1352,  1796,  1454,  1592,   963,   151,
     152,   153,  1688,  -671,  2007,  1199,  2004,  1229,   964,   774,
    1539,  -920,   210,  -920,   745,   745,   774,   376,   222,  1817,
    1341,  1100,   317,  1900,  1498,   304,  2034,   210,   762,   763,
    1846,  1786,  1921,  1893,  2032,  -211,  1584,  2033,  1019,  1560,
     222,   306,  1912,   221,    55,   774,   307,   221,   257,   258,
     259,   222,   490,   759,    55,   870,  1292,   271,  1294,   774,
     215,  1837,  1916,   378,  1020,   656,   400,   280,   868,   760,
    1885,   281,  1111,  1955,  1013,   210,   383,  1917,  1097,  1878,
     210,   389,  1869,   430,  1802,  1296,  1895,  1232,   224,   219,
     657,  1896,  1851,   510,  1136,  1834,  1835,   508,   257,   258,
     259,     3,  1297,   977,     4,   909,     5,  1298,  1299,  1439,
     224,  1442,  1708,   637,   386,   909,   909,  1057,   627,   639,
    1248,   224,  1236,  1058,   705,  1656,     6,     7,     8,     9,
    1237,  1249,   215,  1196,  1265,  1202,  -921,  1841,  -921,   994,
     879,  1250,   386,  1238,  1372,   966,   995,   215,   719,   850,
     851,   852,   737,   774,  1011,   386,   880,   738,   221,  1561,
    -920,   219,  1089,  1090,  1370,   850,   851,   852,  1803,  1012,
    1539,  1881,  1662,  -662,  1874,   460,   219,   432,   700,  1197,
    -662,  -662,  -662,  -662,  1151,   304,   881,  -622,   701,   555,
    1920,    55,   461,   222,  1402,  1203,     4,   222,     5,  -655,
    1869,   306,  -475,   739,  1137,  1300,   307,  1428,  1172,  1990,
     556,  1228,   742,  1244,  1159,  1993,  1991,  1101,  1992,  -662,
    -920,  1173,  1237,   557,   214,  1145,  1245,   218,  1246,  1562,
     221,  1367,   225,   774,  1151,  1493,   758,  1174,   631,   632,
     767,   399,   272,  1596,   273,   221,   214,  1160,  1622,   218,
    1087,   401,   907,   402,   225,  1848,   770,   428,   843,   844,
    1397,   774,  1161,   224,  1557,   225,  2015,   224,   431,  2016,
     432,  1546,  1546,  -670,   871,     3,   452,  1555,     4,   792,
       5,   784,   278,   876,   870,  -921,     4,     3,     5,  1364,
       4,  1415,     5,  1183,  1187,   454,   455,  1709,  1184,  1710,
       6,     7,     8,     9,  -671,   877,  1416,  1162,   222,   878,
     649,   131,     6,     7,     8,     9,   132,   133,   633,  1576,
     926,  1987,  1417,  1503,     3,   927,   650,     4,   282,     5,
    1448,  1449,   134,  1504,  1194,   913,  1195,  1455,  1505,   974,
    1506,  1575,  1507,   498,   499,  -921,  1256,   651,  1246,     6,
       7,     8,     9,   652,  1358,   907,   907,   907,   907,   907,
     214,   938,   907,   218,  1864,  1865,  1866,  1867,   291,   292,
     558,  1677,   870,   293,  1678,  -753,  -475,  1679,   224,   913,
     222,  1175,   512,   513,  1271,  1272,  1273,   907,  1163,   939,
       4,  1471,     5,     3,  1874,   222,     4,   618,     5,   940,
    1284,   762,   763,   226,   845,   846,   907,   225,   941,  1244,
    1574,   225,   785,   786,   787,   788,   789,  2048,     6,     7,
       8,     9,  1256,   942,  1246,   226,   151,   152,   153,   619,
     620,  -272,  1244,  1480,   653,   654,   226,   774,  -762,  1255,
    1489,  -763,   592,  1257,  1386,  1494,   593,  1246,  1508,   980,
     224,   996,  1616,  1479,  1481,   712,   713,   621,    18,    19,
    1487,  1481,  1490,  1492,   997,   224,     3,  1002,   597,     4,
    1573,     5,   779,   780,   659,  1004,   500,   501,   594,   595,
     502,  1063,  1134,   215,     4,  1782,     5,  1876,   660,  1079,
     622,     6,     7,     8,     9,   661,  1711,  1712,  1713,  1714,
     598,   599,  1293,   600,  1295,  1135,  1064,    34,   874,   875,
    1301,   909,   219,   662,  1930,  1931,  1932,    35,   706,   663,
    -662,  1218,   225,    36,  1080,  1220,  1081,   707,   708,  1083,
       3,   709,   710,     4,   219,     5,  1107,     3,  1085,  1313,
       4,  1112,     5,  1314,  1315,  1316,     3,    37,  1111,     4,
    1386,     5,  1116,  1509,  1791,     6,     7,     8,     9,  1126,
    1127,  1792,     6,     7,     8,     9,   861,   862,  1510,  1113,
     579,     6,     7,     8,     9,   762,   763,  1214,   226,  1117,
    1635,   221,   226,  1118,  1511,  1121,   580,  1189,  1190,  1512,
    1123,  1513,  1239,  1240,   225,   581,   214,   868,  1793,   218,
    1215,   582,   583,   221,  1323,  1324,  1325,  1326,  1327,   225,
    1151,   774,  1666,  1130,   909,   909,   909,   909,   909,   215,
    1191,   909,  1783,   774,   150,  1434,  2037,  1344,  1345,  1783,
     227,  1143,  1794,  1179,  1791,  1435,  1155,  1945,  1514,   150,
    1434,  1792,   150,  1434,   762,   763,   909,  1685,   219,  1686,
    1438,  1458,   373,  1441,  1737,  1820,  1821,  1822,  1823,  1824,
     774,  1156,  1784,   373,  1815,   909,  1157,  1690,  1166,  1784,
    1187,  1187,  1187,  1187,  1187,  2038,  1187,  1187,  1793,  1738,
    1739,  1813,   515,   516,   517,  1464,  1464,  1167,  1694,  1695,
    1168,  1094,  1185,   226,  1861,  1862,  1863,  1746,  1747,  1748,
     214,  1749,   214,   218,  1192,   218,   257,   258,   259,  1481,
    1481,  1193,  1794,   860,   861,   862,  1833,   221,   907,   907,
     907,   907,   907,   907,   907,   907,   907,   907,   907,   774,
    1198,   222,  1206,  1795,   447,   493,   369,  1136,   494,   495,
     496,  -965,   214,  -966,  1611,   218,  1812,  1204,   465,    18,
      19,     3,  1205,  1138,     4,  1207,     5,  1767,  1014,  1015,
    1016,  1017,  1209,    18,    19,   226,  1210,  1497,  1499,  1515,
    1523,  1541,  1553,   151,   152,   153,     6,     7,     8,     9,
     226,  1827,   519,  1830,   520,   521,   522,   523,  1219,  1500,
    1516,  1524,  1542,  1554,  1582,  1740,  1217,  1785,    34,  1241,
    1809,   224,   774,  1242,  1785,   227,  1346,  1347,    35,   227,
     770,  1413,    34,  1795,    36,  1741,  1742,  1890,   850,   851,
     852,   775,    35,  1139,  1243,  1858,   868,  1247,    36,  1860,
    1597,  1598,  1253,  1946,  1237,  1304,  1587,  1588,    37,   150,
    1434,  1589,  1590,  1859,  2001,  2002,  1101,  2039,  1258,  1947,
    1733,  1734,    37,   935,  1948,   215,  1949,  1466,  1467,  1266,
    1873,  1267,   369,  1801,  1268,  1269,   774,   222,   214,  1305,
    1270,   218,  1605,   774,  1091,  1612,  1278,  1617,   747,  1145,
    1623,  1889,   774,  1094,   219,  1279,  1880,  1285,  2059,   214,
    1280,  1331,   218,  1606,   907,  1281,  1613,  2060,  1618,  1857,
    1282,  1624,   369,  1283,  1674,   721,   907,   722,   214,   723,
     724,   218,  1437,  1437,   868,  1437,  1288,   725,   726,  1291,
     373,  1675,  1330,  1332,    73,  1306,  1307,  1308,  1309,  1310,
    1311,  1333,    74,  1334,    75,  1335,  1673,   224,  1342,    76,
      77,    78,  1343,    79,  1350,   225,  1351,  1352,  1359,   369,
     727,  1354,  1360,   221,  1362,   214,   907,  1361,   218,   215,
    1369,   215,  1374,  1386,   879,  1385,  1393,   225,   294,   295,
     296,  1659,  1660,   299,   907,   907,  1395,   909,   909,   909,
     909,   909,   909,   909,   909,   909,   909,   909,   219,  1406,
     219,  2011,   373,  1318,  1319,  1320,  1321,     3,  1398,  1429,
       4,   215,     5,   434,   435,   436,   437,   373,  1410,  1440,
    1909,   214,  1444,  2010,   218,  1729,  1111,  1447,  1802,  1453,
    1461,  1462,     6,     7,     8,     9,  1715,  1463,   214,  1478,
     219,   218,  1729,  -621,  1723,  1724,  1725,  1726,  1727,  -622,
    1495,   369,  1570,     3,  1571,  1572,     4,   214,     5,  1594,
     218,  1580,  1752,  1753,  1754,  1583,  1585,   221,  1586,   221,
    1603,  1629,  1630,  1634,  1761,  1762,  1763,  1645,     6,     7,
       8,     9,  1647,  1649,  1515,  1523,  1541,  1553,  1658,  1664,
    1650,   225,  2009,  1558,  1665,  1667,  1559,   774,  1676,  1683,
    1681,  1696,   570,  1244,   571,  1516,  1524,  1542,  1554,   221,
    1697,  1707,  1891,   222,  1721,  1732,  1722,  2076,  1736,  1787,
    1797,  1804,  1758,   572,   754,   214,   226,  1764,   218,  2024,
    2025,   573,   574,  1653,   575,  1134,  1214,   215,  1765,  2075,
    1788,  1798,  1805,  1777,   576,   577,  1766,  -493,   226,  1778,
    1853,  1780,  2008,  1808,  1818,  1826,  1654,  1828,  1135,  1215,
    1845,  1832,  1840,   909,    80,  1849,   219,  1850,  1700,  1702,
    1702,  1705,  1855,  1868,  1892,   909,  1883,   215,   214,    81,
    1894,   218,    88,   224,  1901,  1437,  1111,   219,  1437,  2023,
      89,  1437,    90,  1842,    91,    82,   387,    92,    93,    94,
      83,    95,    84,   136,  1903,   137,   219,   547,  2074,   548,
     138,  1906,   139,  1910,  1560,  1914,   140,   222,  1915,   222,
    1922,   923,   387,  1919,   215,   909,  1925,  1926,   549,  1927,
    1928,   923,   923,  1929,  1933,   221,   550,   551,   552,   553,
    1934,  1935,  1936,   909,   909,  1937,  1720,  1870,  1969,  1871,
    1872,  1979,  1971,   219,  1983,   141,   221,   142,  1286,   222,
    1898,  1981,   226,  1875,  1986,  1994,  1995,  2014,  2073,  1877,
    1904,  1996,  2006,  -225,  2019,   221,  1879,  1907,     3,  1882,
     215,     4,  2041,     5,  2046,  1888,  2047,   224,  2050,   224,
    1091,  2067,  1787,  1797,  1804,  -226,  1581,   215,  1008,    70,
    1760,   946,   369,     6,     7,     8,     9,  1565,   214,   219,
     922,   218,  1940,  1788,  1798,  1805,   215,  2066,  2049,  1939,
     922,   922,   221,   744,   744,  1997,   219,   225,  1999,   224,
    1998,  2000,  1989,  2042,  1561,   467,   413,  1704,   214,   420,
    1852,   218,   907,   774,  1158,   219,   943,   764,  1171,  1814,
      18,    19,  1843,   227,  1348,  1349,  1829,  1831,  1604,  1988,
     214,  1208,  2026,   218,  1938,   945,  1451,  1469,  1450,   214,
     525,   526,   218,  1944,  1924,   227,  1452,  1655,   221,   527,
     528,   529,   530,   531,   215,   222,   745,   745,  1216,  1140,
    1652,   743,  1289,  1491,  1222,   221,  1472,   704,  1392,    34,
    1426,  1636,  1671,  1960,  1772,  1965,  1138,  1668,   934,    35,
     956,   959,    96,   219,   221,    36,  1972,  1973,   958,  1974,
    1975,  1976,  1977,  1978,   462,   222,  1980,    97,  2068,   957,
     752,   225,   214,   225,  1060,   218,  1729,   215,   756,    37,
     757,  1303,     0,    98,  1329,     0,     0,     0,    99,     0,
     100,     0,     0,     0,     0,   224,     0,     0,     0,   386,
       0,  2005,     0,     0,     0,     0,   219,     0,     0,  2012,
    2013,     0,   222,   225,     0,   369,  1139,     0,     0,     0,
       0,   214,   221,     0,   218,   386,     0,     0,     0,   227,
       0,     0,  1887,     0,     0,   224,     0,   214,   226,    62,
     218,  2044,     0,     0,     0,     0,     0,     0,  1499,  1523,
    1541,  1553,     0,     0,     0,     0,  1605,  1612,  1617,  1623,
       0,     0,     0,  2043,     0,     0,  2045,     0,   222,  1500,
    1524,  1542,  1554,     0,     0,   221,     0,  1606,  1613,  1618,
    1624,  2053,   224,     0,     0,   222,  2054,  2055,  2056,  2057,
    2058,  1787,  1797,  1804,  2062,  2063,  2064,  2065,   391,     0,
       0,  1091,   395,  1578,   222,     0,  1579,   215,     0,     0,
       0,  2069,  1788,  1798,  1805,     0,     0,   418,   391,     0,
       3,     0,     0,     4,     0,     5,     0,     0,     0,  2077,
    2078,  2079,     0,     0,     0,   445,   219,   215,   224,   225,
       0,   909,   226,     0,   226,     6,     7,     8,     9,     0,
    1959,     0,  1964,   602,   774,   224,     0,     0,     0,   215,
     225,     0,   603,     0,   486,     0,   219,   923,   215,  2035,
       0,   492,   222,     0,   224,     0,     0,   604,     0,   225,
       0,   605,     0,     0,   226,   606,   607,     0,   219,     0,
     608,   609,   610,   611,   612,     0,     0,   219,     0,     0,
    1422,     0,     0,     0,     0,   221,     0,     0,     0,  1188,
    1637,     3,  1638,  1639,     4,  1641,     5,     0,     0,     3,
       0,     0,     4,     0,     5,   222,   225,     0,     0,     0,
       0,   215,  1801,     0,     0,   221,     6,     7,     8,     9,
       0,     0,   224,     0,     6,     7,     8,     9,   935,   624,
       0,     0,     0,     0,     0,     0,   922,   221,     0,  1558,
     219,   625,  1559,   626,     0,   227,   221,     0,  2040,     0,
     923,   923,   923,   923,   923,     0,     0,   923,     0,     0,
     215,   627,   225,     0,  1964,   628,   560,   561,   629,     0,
       0,     0,     0,     0,     0,   224,   215,     0,     0,   225,
       0,   562,   923,   563,   564,   565,     0,     0,  1887,   219,
     226,  1501,  1518,  1528,  1544,  1556,     0,     0,   225,   533,
     534,   923,     0,   535,     0,   219,   566,   567,   568,   221,
       0,   226,     0,     0,   536,   537,   538,   539,   540,   541,
     542,   543,   544,     0,     0,     0,     0,     0,     0,     0,
     226,  1067,  1068,     0,     0,   222,     0,     0,     0,   922,
     922,   922,   922,   922,     0,  1069,   922,     0,   630,   227,
       0,   227,     0,  1070,     0,     0,     0,     0,   221,     0,
    1560,     0,     0,   545,     0,   222,   225,  1802,     0,  1071,
       0,   922,     0,     0,   221,     0,     0,   226,     0,     0,
       0,   631,   632,     3,     0,     0,     4,   222,     5,     0,
     922,   373,     0,     0,     0,  1607,   222,     0,  1614,     0,
    1619,     3,     0,  1625,     4,   224,     5,     0,     6,     7,
       8,     9,     0,     0,     0,     0,     0,     0,     0,   225,
       0,     0,  1530,     0,     0,     0,     6,     7,     8,     9,
       0,     0,     0,   226,     0,   224,   774,     0,     0,  1819,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     226,  2061,   469,     0,     0,  1422,     0,   224,  1106,   222,
    1108,   633,     0,     0,     0,     0,   224,    18,    19,   226,
    1531,  1532,  1533,  1534,     0,  1535,  1124,  1125,  1536,  1129,
    1561,     0,     0,     0,     0,  1141,  1142,     0,  1072,  1073,
    1074,   683,     0,     0,     3,  1537,     0,     4,     0,     5,
       0,     0,     0,     0,   693,   694,   695,     0,   222,     0,
       0,     0,  1176,     0,  1178,     0,    34,   373,     0,     6,
       7,     8,     9,     0,   222,     0,    35,   774,     0,   224,
       0,     0,    36,  1547,     0,     0,     0,   226,   227,     0,
       0,     0,  2027,     0,  1538,     0,     0,     0,     0,   225,
    1776,     0,     0,     0,     0,     0,    37,   373,     0,     0,
       0,   471,     0,     0,     0,  1188,  1188,  1188,  1188,  1188,
       0,  1188,  1188,     0,  1212,     0,    18,    19,   224,   225,
    1465,  1465,  1548,     0,  1549,  1899,  1535,     0,     0,  1536,
     226,     0,     0,     0,   224,  1905,     0,  1518,  1528,  1544,
    1556,   225,  1908,     0,   373,     0,  1550,     0,     0,     0,
     225,     0,   476,   923,   923,   923,   923,   923,   923,   923,
     923,   923,   923,   923,     0,    34,     0,    18,    19,     0,
       0,     0,  1789,  1799,  1806,    35,     0,  1913,     0,     0,
       0,    36,     0,     0,  1251,  1252,     0,     0,     0,  1539,
       0,     0,    60,   480,     0,  1551,     0,     0,     0,     0,
     227,     0,     0,     0,   304,    37,     0,     0,    18,    19,
       0,     0,     0,   225,     0,     0,    34,   227,     0,   482,
     306,   274,   275,   276,   277,   307,    35,     0,  1966,  1967,
    1968,     0,    36,     0,    18,    19,   373,     0,     0,  1094,
       0,     0,   922,   922,   922,   922,   922,   922,   922,   922,
     922,   922,   922,  1982,     0,   393,    37,    34,     0,   774,
     226,     0,   225,   403,   404,   405,   406,    35,     0,     0,
       0,     0,     0,    36,  1540,     0,     0,   774,   225,     0,
       0,     0,     0,    34,     0,     0,   439,     0,     0,     0,
     226,     0,  2036,    35,     0,     0,     0,    37,     0,    36,
    1539,     0,     0,   464,   227,     0,     0,     0,   473,   474,
     475,     0,   226,   479,     0,   304,   484,     0,     0,     0,
       0,   226,     0,    37,     0,     0,     0,     3,     0,   923,
       4,   306,     5,     0,     0,     0,   307,     0,     0,     0,
       0,   923,     0,     0,     0,  1789,  1799,  1806,     0,     0,
       0,     0,     6,     7,     8,     9,     0,   227,     0,     0,
       0,  1373,     0,     0,     0,  1376,  1530,     0,     0,     0,
     774,     0,     0,     0,  1389,  1390,  1391,     0,     0,  1394,
       0,  1396,     0,     0,   226,  1552,     0,     0,     0,     0,
       0,   923,     0,     0,     0,     0,     0,     0,  2070,  2071,
    2072,  1411,     0,     0,     0,     0,     0,     0,     0,   923,
     923,     0,     0,     0,  1531,  1532,  1533,  1534,   922,  1535,
       0,     0,  1536,     0,     0,     0,     0,     0,     0,     0,
     922,     0,     0,   226,     0,  1443,     0,  1445,     0,  1537,
       0,     0,     0,  1446,     0,     0,     0,     0,     0,   226,
       0,     0,     0,   729,   730,   731,  1459,     0,  1460,     0,
     444,     0,   446,   448,     0,     0,   451,  1468,   453,  1470,
       0,   457,   458,     0,     0,   466,   468,   470,   472,     0,
     922,  1021,   477,     0,     0,   481,   483,   373,  1538,     0,
       0,     0,     0,   489,     0,     0,  1022,     0,   922,   922,
       3,     0,     0,     4,     3,     5,     0,     4,     0,     5,
       0,     0,     0,     0,     0,     0,     0,   227,     0,     0,
       0,     0,     0,     0,     0,     6,     7,     8,     9,     6,
       7,     8,     9,     0,     0,     0,  1503,     0,     0,   227,
       0,     0,     0,  1547,     0,     0,  1504,     0,   227,     0,
       0,  1505,     0,  1506,     0,  1507,     0,     0,     0,     0,
    1023,  1501,  1528,  1544,  1556,     0,     0,     0,     0,  1607,
    1614,  1619,  1625,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   952,   953,   954,     0,     0,     0,     0,     0,
    1022,     0,  1548,  1539,  1549,     0,  1535,     0,     0,  1536,
       0,     0,     0,     0,  1789,  1799,  1806,    50,   304,     0,
       0,   227,     0,     0,     0,   968,  1550,    61,    50,    50,
      64,    64,    64,    68,   306,     0,    50,     0,     0,   307,
       0,  1024,  1627,  1628,  1025,  1026,  1027,  1028,  1029,  1030,
    1031,  1032,  1033,  1034,   979,     0,     3,     0,     0,     4,
       0,     5,     0,  1640,  1023,     0,     0,     0,     0,     0,
     373,  1508,     0,   774,     0,  1551,     0,     0,  1657,     0,
       0,     6,     7,     8,     9,     0,   227,    50,  1770,     0,
     394,    50,    64,    64,    64,    68,  1558,     0,     0,  1559,
       0,     0,    50,     0,   409,   414,   417,    50,   422,    64,
      64,   427,  1680,   409,   409,   409,   409,     0,    64,     0,
       0,     0,   443,     0,    50,     0,     0,    64,    64,  1682,
      68,  1684,     0,    64,   795,  1024,     0,     0,  1025,  1026,
    1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,     0,     0,
       0,     0,   485,    50,    64,    64,     0,     0,    64,     0,
      50,     0,     0,     0,     0,     0,     0,   151,   152,   153,
       0,     0,     0,     0,   889,     0,  1509,   923,   890,     0,
    1539,     0,     0,   891,     0,     0,     0,     0,     0,   892,
       0,  1510,     0,   802,     0,   304,     0,     0,     0,     0,
       0,     0,     0,     3,     0,     0,     4,  1511,     5,     0,
       0,   306,  1512,   895,  1513,     0,   307,  1560,   978,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,     7,
       8,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1530,     0,     0,     0,   774,     0,     0,     0,
     774,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1768,     0,     0,     0,  1771,   922,     0,     0,     0,
       0,     0,     0,     0,     3,     0,     0,     4,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1531,  1532,  1533,  1534,     0,  1535,   146,  1816,  1536,     6,
       7,     8,     9,   147,   148,     0,     0,     0,   288,   149,
     289,     0,     0,     0,     0,  1537,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   290,  1836,     0,     0,     0,
       0,     0,     0,     0,     0,   291,   292,  1561,     0,     0,
     293,   805,     0,     0,   806,   807,     0,     0,     0,  1844,
       0,   294,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,  1538,     0,  1519,     0,     0,     0,
     300,     0,   301,     0,     0,   150,   151,   152,   153,   809,
     810,   154,     0,   155,     0,     0,  1520,   156,     0,     0,
       0,     0,   157,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,     0,     0,     0,     0,  2031,     0,     0,
       0,     0,     0,     0,   159,     0,     0,     0,     0,   160,
     210,     0,   161,     0,     0,     0,     0,   162,  1036,     0,
     163,     0,     0,   164,   165,  1521,     0,     0,   166,     0,
       0,   167,     0,   168,  1037,  1038,  1039,  1040,  1041,  1042,
    1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1051,  1052,
    1053,     0,     0,   976,     0,   169,   170,     0,     0,  1539,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   982,     0,   983,   304,   984,     0,   985,     0,     0,
       0,     0,   989,     0,     0,     0,   991,     0,   992,     0,
     306,   171,   172,   173,   174,   307,    64,     0,     0,     0,
     175,   176,     0,  1918,   177,   178,   302,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,   774,
     303,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2029,   304,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   305,     0,     0,     0,     0,
       0,   306,     0,     0,     0,     0,   307,     0,     0,     0,
       0,     0,   202,   203,     0,   308,     0,     0,   309,   310,
     311,   312,     0,     0,     0,   313,     0,     0,     0,   314,
     315,   204,     0,     0,     0,   205,   206,     0,     3,     0,
     774,     4,     0,     5,   316,     0,     0,   207,   208,     0,
       0,     0,     0,     0,   317,  1522,   209,     0,     0,   210,
     146,     0,     0,     6,     7,     8,     9,   147,   148,     0,
       0,     0,   288,   149,   289,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   290,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   291,
     292,     0,     0,     0,   293,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   294,   295,   296,   297,   298,
     299,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1519,     0,     0,     0,   300,     0,   301,     0,     0,   150,
     151,   152,   153,     0,     0,   154,     0,   155,     0,     0,
    1520,   156,     0,     0,     0,     0,   157,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,     0,
       0,     0,     0,   160,     0,     0,   161,     0,     0,     0,
       0,   162,     0,     0,   163,     0,     0,   164,   165,  1521,
       0,     0,   166,     0,     0,   167,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     4,     0,     5,     0,   169,
     170,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     7,     8,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1547,     0,     0,     0,   171,   172,   173,   174,     0,
       0,     0,     0,     0,   175,   176,     0,     0,   177,   178,
     302,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,     0,     0,   303,     0,     0,     0,     0,     0,
    1548,     0,  1549,     0,  1535,     0,     0,  1536,     0,   304,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   305,
       0,     0,     0,     0,  1550,   306,     0,     0,     0,     0,
     307,     0,     0,     0,     0,     0,   202,   203,     0,   308,
       0,     0,   309,   310,   311,   312,     0,     0,     0,   313,
       0,     0,     0,   314,   315,   204,     0,     0,     0,   205,
     206,     0,     3,     0,   774,     4,     0,     5,   316,     0,
       0,   207,   208,  1551,     0,     0,     0,     0,   317,  1769,
     209,     0,     0,   210,   146,     0,     0,     6,     7,     8,
       9,   147,   148,     0,     0,     0,   288,   149,   289,     0,
       0,     0,     0,     0,     0,     0,     0,   675,   676,     0,
       0,   677,     0,   290,     0,     0,  1287,     0,     0,     0,
       0,     0,     0,   291,   292,     0,     0,     0,   293,   678,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   294,
     295,   296,   297,   298,   299,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1519,     0,     0,     0,   300,     0,
     301,     0,     0,   150,   151,   152,   153,     0,     0,   154,
       0,   155,     0,    10,  1520,   156,     0,     0,  1539,     0,
     157,    11,     0,    12,     0,    13,   158,     0,    14,    15,
      16,     0,    17,   304,     0,     0,    18,    19,     0,     0,
       0,     0,   159,     0,     0,     0,     0,   160,     0,   306,
     161,     0,     0,     0,   307,   162,     0,     0,   163,     0,
       0,   164,   165,  1521,     0,     0,   166,     0,     0,   167,
       0,   168,     0,     0,     0,     0,     0,     0,     0,     0,
     679,     0,     0,     0,     0,    34,     0,     0,   774,     0,
       0,     0,     0,   169,   170,    35,     0,     0,     0,     0,
       0,    36,     0,  2030,   680,   681,   682,   683,   684,   685,
       0,   686,   687,   688,   689,   690,   691,   692,     0,     0,
     693,   694,   695,     0,     0,    37,     0,     0,     0,   171,
     172,   173,   174,     0,     0,     0,     0,     0,   175,   176,
       0,   696,   177,   178,   302,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     0,     0,   303,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   304,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   305,     0,     0,     0,     0,     0,   306,
       0,     0,     0,     0,   307,     0,     0,     0,     0,     0,
     202,   203,     0,   308,     0,     0,   309,   310,   311,   312,
       0,     0,     0,   313,     0,     0,     0,   314,   315,   204,
       0,     0,     0,   205,   206,     0,     0,     4,   774,     5,
       0,     0,   316,    38,     0,   207,   208,     0,     0,     0,
       0,     0,   317,  2028,   209,     0,   146,   210,    39,     0,
       0,     0,     0,   147,   148,     0,     0,     0,   288,   149,
     289,     0,     0,     0,    40,     0,     0,     0,     0,    41,
       0,    42,     0,     0,     0,   290,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   291,   292,   665,     0,     0,
     293,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   294,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,   666,     0,     0,   667,     0,     0,
     300,     0,   301,     0,     0,   150,   151,   152,   153,     0,
       0,   154,     0,   155,   668,     0,     0,   156,     0,     0,
       0,     0,   157,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,     0,     0,     0,     0,   160,
       0,     0,   161,     0,     0,     0,     0,   162,     0,     0,
     163,     0,     0,   164,   165,     0,     0,     0,   166,     0,
       0,   167,     0,   168,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   169,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,     0,
       0,   171,   172,   173,   174,     0,     0,     0,     0,     0,
     175,   176,     0,     0,   177,   178,   302,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,   669,
     303,     0,   794,   202,   203,     0,     0,     0,     0,     0,
       0,     0,     0,   670,     0,   304,     0,     0,     0,     0,
     146,     0,     0,     0,     0,   305,     0,     0,   148,     0,
       0,   306,     0,   149,     0,     0,   307,     0,     0,   671,
       0,     0,   202,   203,     0,   308,     0,     0,   309,   310,
     311,   312,     0,     0,     0,   313,     0,     0,     0,   314,
     315,   204,     0,     0,     0,   205,   206,   795,     0,     0,
       0,     0,     0,     0,   316,     0,     0,   207,   208,     0,
       0,   796,     0,   797,   317,  1672,   209,     0,     0,   210,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
     151,   152,   153,     0,     0,   154,     0,   798,     0,     0,
       0,   799,     0,     0,     0,     0,   800,     0,     0,     0,
       0,     0,   801,     0,     0,     0,   802,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,     0,
       0,     0,     0,   160,     0,     0,   803,     0,     0,     0,
       0,   162,     0,     0,   163,     0,     0,   164,   165,     0,
       0,     0,   166,     0,     0,   167,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   753,   169,
     170,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1103,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     675,   676,     0,     0,   677,     0,     0,     0,   146,     0,
       0,     0,     0,     0,     0,   804,   148,     0,     0,     0,
       0,   149,   678,     0,     0,     0,     0,     0,     0,     0,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,     0,     0,   201,   795,     0,     0,     0,     0,
       0,     0,     0,     0,   805,     0,     0,   806,   807,     0,
       0,     0,     0,     0,     0,     0,   754,     0,     0,     0,
     808,     0,     0,     0,     0,     0,     0,   150,   151,   152,
     153,     0,     0,   154,     0,   798,   202,   203,     0,   799,
       0,     0,   809,   810,   800,     0,     0,     0,     0,     0,
    1104,     0,     0,     0,   802,   204,     0,     0,     0,   205,
     206,     0,     0,     0,     0,     0,   159,     0,     0,   811,
     812,   160,   671,   679,  1105,     0,     0,     0,     0,   162,
     813,     0,   163,   210,     0,   164,   165,     0,     0,     0,
     166,     0,     0,   167,     0,   168,     0,   680,   681,   682,
     683,   684,   685,   755,   686,   687,   688,   689,   690,   691,
     692,     0,     0,   693,   694,   695,     0,   169,   170,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1177,     0,
       0,     0,     0,     0,   696,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   146,     0,     0,     0,
       0,     0,     0,   804,   148,     0,     0,     0,     0,   149,
       0,     0,     0,     0,     0,     0,     0,     0,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
       0,     0,   201,   795,     0,     0,     0,     0,     0,     0,
       0,     0,   805,     0,     0,   806,   807,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,   151,   152,   153,     0,
       0,   154,     0,   798,   202,   203,     0,   799,     0,     0,
     809,   810,   800,     0,     0,     0,     0,     0,  1104,     0,
       0,     0,   802,   204,     0,     0,     0,   205,   206,     0,
       0,     0,     0,     0,   159,     0,     0,   811,   812,   160,
     671,     0,  1105,     0,     0,     0,     0,   162,   813,     0,
     163,   210,     0,   164,   165,     0,     0,     0,   166,     0,
       0,   167,     0,   168,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   169,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1211,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   146,     0,     0,     0,     0,     0,
       0,   804,   148,     0,     0,     0,     0,   149,     0,     0,
       0,     0,     0,     0,     0,     0,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,     0,
     201,   795,     0,     0,     0,     0,     0,     0,     0,     0,
     805,     0,     0,   806,   807,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   151,   152,   153,     0,     0,   154,
       0,   798,   202,   203,     0,   799,     0,     0,   809,   810,
     800,     0,     0,     0,     0,     0,  1104,     0,     0,     0,
     802,   204,     0,     0,     0,   205,   206,     0,     0,     0,
       0,     0,   159,     0,     0,   811,   812,   160,   671,     0,
    1105,     0,     0,     0,     0,   162,   813,     0,   163,   210,
       0,   164,   165,     0,     0,     0,   166,     0,     0,   167,
       0,   168,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   169,   170,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1375,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   146,     0,     0,     0,     0,     0,     0,   804,
     148,     0,     0,     0,     0,   149,     0,     0,     0,     0,
       0,     0,     0,     0,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     0,     0,   201,   795,
       0,     0,     0,     0,     0,     0,     0,     0,   805,     0,
       0,   806,   807,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   150,   151,   152,   153,     0,     0,   154,     0,   798,
     202,   203,     0,   799,     0,     0,   809,   810,   800,     0,
       0,     0,     0,     0,  1104,     0,     0,     0,   802,   204,
       0,     0,     0,   205,   206,     0,     0,     0,     0,     0,
     159,     0,     0,   811,   812,   160,   671,     0,  1105,     0,
       0,     0,     0,   162,   813,     0,   163,   210,     0,   164,
     165,     0,     0,     0,   166,     0,     0,   167,     0,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   169,   170,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   882,   883,   884,   885,
     886,   887,     0,     0,     0,     0,   888,     0,     0,     0,
     867,     0,     0,     0,     0,     0,     0,   804,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,     0,     0,   201,   795,     0,     0,
       0,     0,     0,     0,     0,     0,   805,     0,     0,   806,
     807,     0,     0,     0,     0,     0,     0,  1144,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
     151,   152,   153,     0,     0,     0,     0,   889,   202,   203,
       0,   890,     0,     0,   809,   810,   891,     0,     0,     0,
       0,     0,   892,     0,     0,     0,   802,   204,     0,     0,
       0,   205,   206,     0,     0,     0,   795,     0,   893,     0,
       0,   811,   812,   894,   671,     0,   895,     0,     0,     0,
       0,   896,   813,     0,   897,   210,  1144,   898,   899,     0,
       0,     0,   900,     0,     0,   901,     0,   902,   150,   151,
     152,   153,     0,     0,     0,     0,   889,     0,     0,     0,
     890,     0,     0,     0,     0,   891,     0,     0,     0,   903,
     904,   892,     0,     0,     0,   802,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   795,     0,   893,     0,     0,
       0,     0,   894,     0,     0,   895,     0,     0,     0,     0,
     896,     0,     0,   897,     0,     0,   898,   899,     0,     0,
       0,   900,     0,     0,   901,     0,   902,   150,   151,   152,
     153,     0,     0,     0,     0,   889,     0,     0,     0,   890,
       0,     0,     0,     0,   891,     0,     0,     0,   903,   904,
     892,     0,     0,     0,   802,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   805,     0,   893,   806,   807,     0,
       0,   894,     0,     0,   895,     0,   928,   867,     0,   896,
       0,     0,   897,     0,     0,   898,   899,     0,     0,     0,
     900,     0,     0,   901,     0,   902,     0,     0,     0,     0,
       0,     0,   809,   810,     0,   905,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   903,   904,     0,
       0,     0,     0,     0,   795,     0,     0,     0,     0,   811,
     812,     0,     0,   805,     0,     0,   806,   807,   317,     0,
     906,     0,     0,   210,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   150,   151,   152,   153,
       0,     0,     0,     0,   889,     0,     0,     0,   890,     0,
       0,   809,   810,   891,   905,     0,     0,     0,     0,   892,
       0,     0,     0,   802,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   893,     0,     0,   811,   812,
     894,     0,   805,   895,     0,   806,   807,   317,   896,   906,
       0,   897,   210,     0,   898,   899,     0,     0,     0,   900,
       0,     0,   901,     0,   902,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     809,   810,     0,   905,     0,   146,   903,   904,     0,     0,
       0,     0,   147,   148,     0,     0,     0,   288,   149,   289,
       0,     0,     0,     0,     0,     0,     0,   811,   812,     0,
       0,     0,     0,     0,   290,     0,     0,     0,   906,     0,
       0,   210,     0,     0,   291,   292,   751,     0,     0,   293,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     294,   295,   296,   297,   298,   299,     0,     0,     0,     0,
       0,     0,     0,   666,     0,     0,   667,     0,     0,   300,
       0,   301,     0,     0,   150,   151,   152,   153,     0,     0,
     154,   805,   155,   668,   806,   807,   156,     0,     0,     0,
       0,   157,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,     0,     0,     0,     0,   160,   809,
     810,   161,   905,     0,     0,     0,   162,     0,     0,   163,
       0,     0,   164,   165,     0,     0,     0,   166,     0,     0,
     167,     0,   168,     0,     0,     0,   811,   812,     0,     0,
       0,     0,     0,     0,     0,   929,     0,   906,     0,     0,
     210,     0,     0,     0,   169,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,     0,
     171,   172,   173,   174,     0,     0,     0,     0,     0,   175,
     176,     0,     0,   177,   178,   302,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,     0,   669,   303,
       0,     0,   202,   203,     0,     0,     0,     0,     0,     0,
     146,     0,   670,     0,   304,     0,     0,   147,   148,     0,
       0,     0,     0,   149,   305,     0,     0,     0,     0,     0,
     306,     0,     0,     0,     0,   307,     0,     0,   671,     0,
       0,   202,   203,     0,   308,     0,     0,   309,   310,   311,
     312,     0,     0,     0,   313,     0,     0,     0,   314,   315,
     204,     0,     0,     0,   205,   206,     0,     0,     0,     0,
       0,     0,     0,   316,     0,     0,   207,   208,     0,     0,
       0,     0,     0,   317,     0,   209,     0,     0,   210,   150,
     151,   152,   153,     0,     0,   154,     0,   155,     0,     0,
       0,   156,     0,     0,     0,     0,   157,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,     0,
       0,     0,     0,   160,     0,     0,   161,     0,     0,     0,
       0,   162,     0,     0,   163,     0,     0,   164,   165,     0,
       0,     0,   166,     0,     0,   167,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   169,
     170,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   146,
       0,     0,     0,     0,     0,     0,   147,   148,     0,     0,
       0,     0,   149,     0,     0,   171,   172,   173,   174,     0,
       0,     0,     0,     0,   175,   176,     0,     0,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,     0,     0,   201,     0,     0,     0,     0,     0,
       0,     0,  1941,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,     0,     0,   154,     0,   155,     0,     0,     0,
     156,     0,     0,     0,     0,   157,   202,   203,     0,     0,
       0,   158,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   204,     0,   159,     0,   205,
     206,     0,   160,     0,     0,   161,     0,     0,     0,     0,
     162,   207,   208,   163,     0,     0,   164,   165,   317,     0,
     209,   166,     0,   210,   167,     0,   168,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   146,     0,     0,   169,   170,
       0,     0,   147,   148,     0,     0,     0,     0,   149,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   171,   172,   173,   174,     0,     0,
       0,     0,     0,   175,   176,     0,     0,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,     0,     0,   201,   150,   151,   152,   153,     0,     0,
     154,     0,   155,     0,   104,     0,   156,     0,     0,   105,
       0,   157,   106,   107,   108,   109,     0,   158,   110,   111,
       0,   112,   113,   114,     0,   115,     0,     0,     0,     0,
       0,     0,     0,   159,     0,   202,   203,     0,   160,     0,
       0,   161,     0,     0,     0,     0,   162,     0,     0,   163,
       0,     0,   164,   165,   204,     0,     0,   166,   205,   206,
     167,     0,   168,     0,   116,     0,   117,   118,   119,     0,
     207,   208,     0,     0,     0,     0,     0,     0,     0,   209,
       0,   146,   210,     0,   169,   170,     0,     0,     0,   148,
       0,     0,     0,     0,   149,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     171,   172,   173,   174,     0,     0,     0,     0,   795,   175,
     176,     0,     0,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,     0,     0,   201,
     150,   151,   152,   153,     0,     0,   154,     0,   798,     0,
       0,     0,   799,     0,     0,     0,     0,   800,     0,     0,
       0,     0,     0,  1104,     0,     0,     0,   802,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   159,
       0,   202,   203,     0,   160,     0,     0,  1105,     0,     0,
       0,     0,   162,     0,     0,   163,     0,     0,   164,   165,
     204,     0,     0,   166,   205,   206,   167,     0,   168,     0,
       0,     0,     0,     0,   120,     0,   207,   208,     0,     0,
       0,     0,     0,     0,     0,   209,     0,     0,   210,   121,
     169,   170,     0,     0,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,   126,     0,     0,     0,     0,
     127,     0,   128,   129,     0,     0,     0,     0,     0,   867,
       0,     0,     0,     0,     0,     0,   804,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,     0,     0,   201,   795,     0,     0,     0,
       0,     0,     0,     0,     0,   805,     0,     0,   806,   807,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,     0,     0,     0,     0,   889,   202,   203,     0,
     890,     0,     0,   809,   810,   891,     0,     0,     0,     0,
       0,   892,     0,     0,     0,   802,   204,     0,     0,     0,
     205,   206,     0,     0,     0,     0,     0,   893,     0,     0,
     811,   812,   894,   671,     0,   895,     0,     0,     0,     0,
     896,   813,     0,   897,   210,     0,   898,   899,     0,     0,
       0,   900,     0,     0,   901,     0,   902,     0,     0,     2,
       3,     0,     0,     4,     0,     5,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   903,   904,
       0,     0,     0,     0,     0,     6,     7,     8,     9,     0,
       0,     0,     0,     0,     0,     0,    10,     0,     0,     0,
       0,     0,     0,     0,    11,     0,    12,     0,    13,     0,
       0,    14,    15,    16,     0,    17,     0,     0,     0,    18,
      19,    20,     0,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -363,   805,     0,     0,   806,   807,    34,     0,
       0,     0,     0,     0,     0,     0,     0,   795,    35,     0,
       0,     0,     0,     0,    36,   294,   295,   296,  1659,  1660,
     299,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   809,   810,     0,   905,     0,     0,     0,    37,   150,
     151,   152,   153,     0,     0,     0,     0,   889,     0,     0,
       0,   890,     0,     0,     0,   795,   891,     0,   811,   812,
       0,     0,   892,     0,     0,     0,   802,   317,     0,   906,
       0,     0,   210,     0,     0,     0,     0,     0,   893,     0,
       0,     0,     0,   894,     0,     0,   895,   150,   151,   152,
     153,   896,     0,     0,   897,   889,     0,   898,   899,   890,
       0,     0,   900,     0,   891,   901,     0,   902,     0,     0,
     892,     0,     0,     0,   802,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   795,   893,     0,     0,   903,
     904,   894,     0,     0,   895,     0,     0,     0,     0,   896,
       0,     0,   897,     0,     0,   898,   899,     0,     0,     0,
     900,     0,     0,   901,     0,   902,    38,  1488,   151,   152,
     153,     0,     0,     0,     0,   889,     0,     0,     0,   890,
       0,    39,     0,     0,   891,     0,     0,   903,   904,     0,
     892,     0,     0,     0,   802,     0,     0,    40,     0,     0,
       0,     0,    41,     0,    42,     0,   893,     0,     0,     0,
       0,   894,     0,     0,   895,     0,     0,     0,     0,   896,
       0,     0,   897,     0,   805,   898,   899,   806,   807,     0,
     900,     0,     0,   901,     0,   902,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   903,   904,     0,
       0,     0,   809,   810,     0,   905,     0,     0,     0,     0,
       0,     0,   805,     0,     0,   806,   807,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   811,
     812,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     906,     0,     0,   210,     0,     0,     0,     0,     0,     0,
     809,   810,     0,   905,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   811,   812,     0,
       0,     0,   805,     0,     0,   806,   807,     0,   906,     0,
       0,   210,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     809,   810,     0,   905,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   811,   812,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   906,     0,
       0,   210
};

static const yytype_int16 yycheck[] =
{
       1,    30,     3,   320,    30,    30,   298,   475,   396,   633,
      66,   323,   399,   344,   328,   397,   351,    52,    36,    52,
     771,     1,    37,    52,   205,  1263,    52,   398,    63,   474,
      63,   209,  1262,  1263,    63,  1145,  1146,    63,  1263,   484,
    1267,   428,  1152,   425,    32,    46,  1270,  1268,   288,  1269,
     365,   765,  1219,    54,  1094,   518,   438,    58,   379,  1283,
     105,   365,   107,  1133,   109,   110,   860,    35,   113,  1369,
     115,   365,   736,   118,   119,   315,  1365,   122,   123,   124,
     125,   375,   376,   395,   129,  1413,   636,   132,   133,   403,
     904,  1365,  1572,  1350,  1351,   140,  1221,   337,   473,  1550,
    1570,  1379,  1547,  1571,   813,  1475,   874,   875,   877,   876,
     774,     4,   878,     4,    38,     7,   102,    23,     7,  1229,
     434,   785,     7,    45,     7,   789,    15,    16,    17,    18,
       7,  1593,   103,  1609,     1,   880,   103,     4,    20,     6,
      78,    79,  1420,  1421,   179,     5,  1610,    96,   126,     7,
     464,     7,     8,     9,    15,    16,   706,   103,  1793,    26,
      27,    28,    29,     1,    84,   479,     4,    13,     6,    23,
       1,   103,   162,     4,   733,     6,   205,  1381,   113,   205,
     209,   284,   735,   209,    23,   125,   734,   102,    26,    27,
      28,    29,    48,   697,    50,    26,    27,    28,    29,   103,
      38,   669,   284,    59,    57,   103,   104,   105,    64,   149,
     103,   736,    68,    62,   104,    76,    77,    78,   102,   159,
     299,   103,    89,   103,   128,   129,    84,    49,   696,    96,
      57,    92,    93,    94,    84,  1473,    22,     4,    57,     6,
      86,   102,   162,  1473,   234,   235,   236,    53,   351,    98,
     111,   112,   756,    49,  1532,  1533,   117,     8,    58,   125,
      30,   350,    93,   103,   104,   105,   133,   302,   256,   351,
    1548,   113,   351,    66,   262,   125,   103,   138,   139,   145,
      84,   142,    52,   149,   103,   320,     4,    89,     6,    30,
      92,   320,   351,    63,   320,   959,     4,   356,     6,   149,
     167,    89,   133,    54,    92,   283,   113,     1,    58,   365,
       4,    52,     6,   248,   249,  1545,   102,   103,   152,   375,
     376,   125,    63,   130,   166,   167,    47,  1557,   162,   163,
    1568,    39,    26,    27,    28,    29,   365,  1567,  1568,   285,
     244,   397,     8,  1568,  1979,   149,   375,   376,   103,    15,
      16,    17,    18,   285,   210,   162,    22,   392,    30,   392,
     264,   265,   143,   392,  1109,   283,   392,   148,     1,   425,
     356,     4,   407,     6,   407,    32,    33,    34,   407,   351,
      52,   407,   438,   301,   302,   356,   301,     1,    54,   356,
       4,    63,     6,    26,    27,    28,    29,   956,     5,   265,
     266,   268,   351,   285,    84,   958,   346,   267,    41,   957,
     455,    44,    26,    27,    28,    29,     8,   301,   356,   113,
      84,   127,   282,    15,    16,    17,    18,   351,   143,   351,
    1881,  1893,  1636,  1878,   959,   205,   110,   268,   298,   209,
    1916,   297,   298,   303,   159,   301,   152,     8,  1112,  1113,
     356,   125,  1197,  1917,    15,    16,    17,    18,   356,  1689,
     352,   352,    54,   356,   205,   323,   355,   352,   209,   352,
     337,  1239,  1240,  1242,  1241,   352,    84,  1243,    86,   345,
      89,  1851,   335,   336,   331,   352,  1195,   334,    57,   103,
     104,   105,   352,    54,  1945,   826,  1941,   351,    57,   337,
     267,    84,   356,    86,   297,   298,   337,   350,    30,  1634,
    1060,   351,   351,  1791,   352,   282,  1996,   356,   301,   302,
    1687,   352,  1850,  1780,  1994,   351,  1340,  1995,   546,   162,
      52,   298,  1832,   205,   103,   337,   303,   209,   338,   339,
     340,    63,    45,   283,   103,   880,  1009,    89,  1011,   337,
     320,  1661,  1841,   409,   569,   127,    89,   413,   351,   299,
     351,   417,   743,   349,   532,   356,   422,  1841,   351,     5,
     356,   427,     8,    89,   268,   113,   165,   881,    30,   320,
     152,   170,  1692,   132,   765,  1655,  1656,   244,   338,   339,
     340,     1,   130,   454,     4,   365,     6,   135,   136,  1173,
      52,  1175,    89,   233,   397,   375,   376,   625,   145,   233,
     925,    63,   906,   628,   330,  1409,    26,    27,    28,    29,
       7,   925,   392,     8,   945,   233,    84,  1667,    86,   490,
       8,   925,   425,    20,  1102,    57,   492,   407,   339,   319,
     320,   321,   102,   337,   110,   438,    24,   102,   320,   282,
     233,   392,   730,   731,  1099,   319,   320,   321,   352,   125,
     267,     5,  1413,     8,     8,   274,   407,   276,   319,    54,
      15,    16,    17,    18,  1425,   282,    54,    22,   329,   113,
    1847,   103,   291,   205,  1129,   293,     4,   209,     6,   355,
       8,   298,   102,   102,  1408,   233,   303,  1160,   141,  1926,
     134,   879,   283,     7,    77,  1929,  1927,  1371,  1928,    54,
     293,   154,     7,   147,   743,   771,    20,   743,    22,   352,
     392,  1096,    30,   337,  1475,    20,   283,   170,   265,   266,
      84,    79,   274,  1357,   276,   407,   765,   110,   352,   765,
     728,   274,   771,   276,    52,   352,     4,    95,    38,    39,
    1125,   337,   125,   205,  1992,    63,    22,   209,   274,    25,
     276,  1991,  1992,   355,    45,     1,   114,  1992,     4,   313,
       6,   162,     0,    17,  1109,   233,     4,     1,     6,  1093,
       4,   267,     6,   801,   813,    45,    46,   274,   803,   276,
      26,    27,    28,    29,   355,    18,   282,   170,   320,   355,
     115,   282,    26,    27,    28,    29,   287,   288,   345,  1277,
      52,  1921,   298,    37,     1,    52,   131,     4,    57,     6,
    1189,  1190,   303,    47,    20,   881,    22,  1196,    52,    43,
      54,  1276,    56,   111,   112,   293,    20,   152,    22,    26,
      27,    28,    29,   158,  1084,   874,   875,   876,   877,   878,
     879,   351,   881,   879,  1711,  1712,  1713,  1714,    62,    63,
     294,  1435,  1197,    67,  1438,   284,   102,  1441,   320,   925,
     392,   314,   166,   167,   952,   953,   954,   906,   251,   351,
       4,  1212,     6,     1,     8,   407,     4,   134,     6,   351,
     968,   301,   302,    30,   184,   185,   925,   205,   351,     7,
    1275,   209,   293,   294,   295,   296,   297,  2017,    26,    27,
      28,    29,    20,   351,    22,    52,   103,   104,   105,   166,
     167,   351,     7,  1238,   239,   240,    63,   337,    45,   930,
    1245,    45,   130,   934,  1115,    20,   134,    22,   162,    45,
     392,     7,   352,  1237,  1238,   348,   349,   194,    60,    61,
    1244,  1245,  1246,  1247,     8,   407,     1,   297,   134,     4,
    1274,     6,   284,   285,   113,   103,   244,   245,   166,   167,
     248,   357,   765,   743,     4,  1599,     6,     7,   127,   330,
     227,    26,    27,    28,    29,   134,  1510,  1511,  1512,  1513,
     166,   167,  1010,   169,  1012,   765,   357,   109,    15,    16,
    1018,   771,   743,   152,  1861,  1862,  1863,   119,   228,   158,
     355,   867,   320,   125,   330,   871,   102,   237,   238,   347,
       1,   241,   242,     4,   765,     6,    84,     1,   354,   217,
       4,    23,     6,   221,   222,   223,     1,   149,  1219,     4,
    1221,     6,    52,   267,    89,    26,    27,    28,    29,   301,
     302,    96,    26,    27,    28,    29,   324,   325,   282,    23,
     127,    26,    27,    28,    29,   301,   302,   860,   205,    52,
    1387,   743,   209,    52,   298,    52,   143,    15,    16,   303,
      52,   305,    15,    16,   392,   152,  1115,   880,   133,  1115,
     860,   158,   159,   765,   216,   217,   218,   219,   220,   407,
    1851,   337,  1416,   102,   874,   875,   876,   877,   878,   879,
      17,   881,    93,   337,   102,   103,   352,   111,   112,    93,
      30,    84,   167,    84,    89,   113,   351,    86,   352,   102,
     103,    96,   102,   103,   301,   302,   906,  1468,   879,  1470,
     113,  1197,    52,   113,   103,   307,   308,   309,   310,   311,
     337,   102,   133,    63,  1622,   925,   102,  1474,   102,   133,
    1189,  1190,  1191,  1192,  1193,   352,  1195,  1196,   133,   128,
     129,  1616,   111,   112,   113,  1204,  1205,   102,  1493,  1494,
     102,   299,    84,   320,  1708,  1709,  1710,    85,    86,    87,
    1219,    89,  1221,  1219,    18,  1221,   338,   339,   340,  1493,
    1494,   355,   167,   323,   324,   325,  1651,   879,  1237,  1238,
    1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,   337,
       5,   743,   102,   268,    45,   103,  1261,  1408,   106,   107,
     108,     7,  1261,     7,   352,  1261,  1611,     7,    45,    60,
      61,     1,     7,   765,     4,   102,     6,  1561,   137,   138,
     139,   140,     5,    60,    61,   392,     7,  1258,  1259,  1260,
    1261,  1262,  1263,   103,   104,   105,    26,    27,    28,    29,
     407,  1646,   113,  1648,   115,   116,   117,   118,   351,  1259,
    1260,  1261,  1262,  1263,  1302,   244,     7,   268,   109,    17,
    1604,   743,   337,    18,   268,   205,   111,   112,   119,   209,
       4,     5,   109,   268,   125,   264,   265,   352,   319,   320,
     321,   319,   119,   765,   355,  1703,  1109,     8,   125,  1706,
     111,   112,   102,   282,     7,    96,  1344,  1345,   149,   102,
     103,  1346,  1347,  1704,    43,    44,  2000,  2001,   102,   298,
      94,    95,   149,    38,   303,  1115,   305,  1204,  1205,   351,
    1732,   351,  1387,   113,   351,   351,   337,   879,  1387,   130,
     351,  1387,  1363,   337,   284,  1366,   102,  1368,  1660,  1425,
    1371,   352,   337,   299,  1115,   102,  1758,   103,   352,  1408,
     102,   224,  1408,  1363,  1413,   102,  1366,   352,  1368,  1701,
     102,  1371,  1427,   351,  1427,    46,  1425,    48,  1427,    50,
      51,  1427,  1172,  1173,  1197,  1175,   102,    58,    59,   102,
     320,  1429,   221,   224,    37,   186,   187,   188,   189,   190,
     191,   225,    45,   226,    47,   225,  1427,   879,   102,    52,
      53,    54,   102,    56,   102,   743,   102,   331,   351,  1474,
      91,   102,   351,  1115,   102,  1474,  1475,   351,  1474,  1219,
     102,  1221,     5,  1634,     8,   102,   102,   765,    78,    79,
      80,    81,    82,    83,  1493,  1494,    52,  1237,  1238,  1239,
    1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,  1219,    22,
    1221,  1949,   392,   212,   213,   214,   215,     1,   102,   148,
       4,  1261,     6,    97,    98,    99,   100,   407,    43,    70,
    1817,  1530,     5,  1948,  1530,  1530,  1687,   354,   268,   102,
      84,     8,    26,    27,    28,    29,  1517,    84,  1547,   354,
    1261,  1547,  1547,    22,  1525,  1526,  1527,  1528,  1529,    22,
     102,  1566,   351,     1,   351,   351,     4,  1566,     6,   102,
    1566,     7,  1543,  1544,  1545,     7,   358,  1219,   358,  1221,
     285,     5,   103,   351,  1555,  1556,  1557,   300,    26,    27,
      28,    29,   300,    20,  1565,  1566,  1567,  1568,    43,   187,
     304,   879,  1947,    41,   284,   299,    44,   337,     7,   164,
       5,   102,   113,     7,   115,  1565,  1566,  1567,  1568,  1261,
      39,   103,   352,  1115,   103,   350,    98,  2065,   102,  1600,
    1601,  1602,   350,   134,   187,  1634,   743,   103,  1634,  1984,
    1985,   142,   143,  1406,   145,  1408,  1409,  1387,   350,  2064,
    1600,  1601,  1602,   102,   155,   156,    98,    20,   765,   102,
     185,   102,  1946,   102,   352,   102,  1406,   102,  1408,  1409,
      84,   102,   102,  1413,   267,   352,  1387,     5,  1504,  1505,
    1506,  1507,   102,    41,     7,  1425,   150,  1427,  1687,   282,
     350,  1687,    37,  1115,   102,  1435,  1847,  1408,  1438,  1983,
      45,  1441,    47,  1674,    49,   298,  1732,    52,    53,    54,
     303,    56,   305,    45,   102,    47,  1427,   113,  2063,   115,
      52,   104,    54,   284,   162,   102,    58,  1219,   285,  1221,
     184,   365,  1758,   352,  1474,  1475,   351,   351,   134,   351,
     351,   375,   376,   351,   351,  1387,   142,   143,   144,   145,
     351,   351,   351,  1493,  1494,   103,  1519,  1728,   102,  1730,
    1731,   133,   351,  1474,   102,    97,  1408,    99,   979,  1261,
    1785,   352,   879,  1744,   352,   351,   351,   102,  2062,  1750,
    1795,   351,     8,     8,   103,  1427,  1757,  1802,     1,  1760,
    1530,     4,   350,     6,   102,  1766,   102,  1219,     5,  1221,
     284,   102,  1773,  1774,  1775,     8,  1291,  1547,   524,    20,
    1551,   394,  1817,    26,    27,    28,    29,  1266,  1817,  1530,
     365,  1817,  1876,  1773,  1774,  1775,  1566,  2041,  2017,  1874,
     375,   376,  1474,  1659,  1660,  1933,  1547,  1115,  1935,  1261,
    1934,  1936,  1925,  2003,   282,    45,    89,  1506,  1847,    91,
    1692,  1847,  1851,   337,   781,  1566,   391,   307,   790,  1621,
      60,    61,  1676,   743,  1075,  1076,  1647,  1649,   352,  1924,
    1869,   847,  1988,  1869,  1869,   393,  1192,  1210,  1191,  1878,
     111,   112,  1878,  1878,  1855,   765,  1193,  1408,  1530,   120,
     121,   122,   123,   124,  1634,  1387,  1659,  1660,   863,   766,
    1406,   290,   997,  1247,   872,  1547,  1217,   205,  1119,   109,
    1152,  1388,  1423,  1884,   352,  1886,  1408,  1418,   376,   119,
     403,   406,   267,  1634,  1566,   125,  1897,  1898,   405,  1900,
    1901,  1902,  1903,  1904,   120,  1427,  1907,   282,  2051,   404,
     302,  1219,  1941,  1221,   634,  1941,  1941,  1687,   303,   149,
     303,  1021,    -1,   298,  1039,    -1,    -1,    -1,   303,    -1,
     305,    -1,    -1,    -1,    -1,  1387,    -1,    -1,    -1,  1732,
      -1,  1942,    -1,    -1,    -1,    -1,  1687,    -1,    -1,  1950,
    1951,    -1,  1474,  1261,    -1,  1990,  1408,    -1,    -1,    -1,
      -1,  1990,  1634,    -1,  1990,  1758,    -1,    -1,    -1,   879,
      -1,    -1,  1765,    -1,    -1,  1427,    -1,  2006,  1115,    12,
    2006,  2006,    -1,    -1,    -1,    -1,    -1,    -1,  1989,  1990,
    1991,  1992,    -1,    -1,    -1,    -1,  1997,  1998,  1999,  2000,
      -1,    -1,    -1,  2004,    -1,    -1,  2007,    -1,  1530,  1989,
    1990,  1991,  1992,    -1,    -1,  1687,    -1,  1997,  1998,  1999,
    2000,  2022,  1474,    -1,    -1,  1547,  2027,  2028,  2029,  2030,
    2031,  2032,  2033,  2034,  2035,  2036,  2037,  2038,    71,    -1,
      -1,   284,    75,  1284,  1566,    -1,  1287,  1817,    -1,    -1,
      -1,  2052,  2032,  2033,  2034,    -1,    -1,    90,    91,    -1,
       1,    -1,    -1,     4,    -1,     6,    -1,    -1,    -1,  2070,
    2071,  2072,    -1,    -1,    -1,   108,  1817,  1847,  1530,  1387,
      -1,  1851,  1219,    -1,  1221,    26,    27,    28,    29,    -1,
    1883,    -1,  1885,   134,   337,  1547,    -1,    -1,    -1,  1869,
    1408,    -1,   143,    -1,   137,    -1,  1847,   771,  1878,   352,
      -1,   144,  1634,    -1,  1566,    -1,    -1,   158,    -1,  1427,
      -1,   162,    -1,    -1,  1261,   166,   167,    -1,  1869,    -1,
     171,   172,   173,   174,   175,    -1,    -1,  1878,    -1,    -1,
    1148,    -1,    -1,    -1,    -1,  1817,    -1,    -1,    -1,   813,
    1391,     1,  1393,  1394,     4,  1396,     6,    -1,    -1,     1,
      -1,    -1,     4,    -1,     6,  1687,  1474,    -1,    -1,    -1,
      -1,  1941,   113,    -1,    -1,  1847,    26,    27,    28,    29,
      -1,    -1,  1634,    -1,    26,    27,    28,    29,    38,   113,
      -1,    -1,    -1,    -1,    -1,    -1,   771,  1869,    -1,    41,
    1941,   125,    44,   127,    -1,  1115,  1878,    -1,  2001,    -1,
     874,   875,   876,   877,   878,    -1,    -1,   881,    -1,    -1,
    1990,   145,  1530,    -1,  2017,   149,   111,   112,   152,    -1,
      -1,    -1,    -1,    -1,    -1,  1687,  2006,    -1,    -1,  1547,
      -1,   126,   906,   128,   129,   130,    -1,    -1,  2041,  1990,
    1387,  1259,  1260,  1261,  1262,  1263,    -1,    -1,  1566,   111,
     112,   925,    -1,   115,    -1,  2006,   151,   152,   153,  1941,
      -1,  1408,    -1,    -1,   126,   127,   128,   129,   130,   131,
     132,   133,   134,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1427,   111,   112,    -1,    -1,  1817,    -1,    -1,    -1,   874,
     875,   876,   877,   878,    -1,   125,   881,    -1,   232,  1219,
      -1,  1221,    -1,   133,    -1,    -1,    -1,    -1,  1990,    -1,
     162,    -1,    -1,   175,    -1,  1847,  1634,   268,    -1,   149,
      -1,   906,    -1,    -1,  2006,    -1,    -1,  1474,    -1,    -1,
      -1,   265,   266,     1,    -1,    -1,     4,  1869,     6,    -1,
     925,  1261,    -1,    -1,    -1,  1363,  1878,    -1,  1366,    -1,
    1368,     1,    -1,  1371,     4,  1817,     6,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1687,
      -1,    -1,    40,    -1,    -1,    -1,    26,    27,    28,    29,
      -1,    -1,    -1,  1530,    -1,  1847,   337,    -1,    -1,  1640,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1547,   352,    45,    -1,    -1,  1423,    -1,  1869,   740,  1941,
     742,   345,    -1,    -1,    -1,    -1,  1878,    60,    61,  1566,
      88,    89,    90,    91,    -1,    93,   758,   759,    96,   761,
     282,    -1,    -1,    -1,    -1,   767,   768,    -1,   268,   269,
     270,   271,    -1,    -1,     1,   113,    -1,     4,    -1,     6,
      -1,    -1,    -1,    -1,   284,   285,   286,    -1,  1990,    -1,
      -1,    -1,   794,    -1,   796,    -1,   109,  1387,    -1,    26,
      27,    28,    29,    -1,  2006,    -1,   119,   337,    -1,  1941,
      -1,    -1,   125,    40,    -1,    -1,    -1,  1634,  1408,    -1,
      -1,    -1,   352,    -1,   162,    -1,    -1,    -1,    -1,  1817,
     352,    -1,    -1,    -1,    -1,    -1,   149,  1427,    -1,    -1,
      -1,    45,    -1,    -1,    -1,  1189,  1190,  1191,  1192,  1193,
      -1,  1195,  1196,    -1,   856,    -1,    60,    61,  1990,  1847,
    1204,  1205,    89,    -1,    91,  1786,    93,    -1,    -1,    96,
    1687,    -1,    -1,    -1,  2006,  1796,    -1,  1565,  1566,  1567,
    1568,  1869,  1803,    -1,  1474,    -1,   113,    -1,    -1,    -1,
    1878,    -1,    45,  1237,  1238,  1239,  1240,  1241,  1242,  1243,
    1244,  1245,  1246,  1247,    -1,   109,    -1,    60,    61,    -1,
      -1,    -1,  1600,  1601,  1602,   119,    -1,  1838,    -1,    -1,
      -1,   125,    -1,    -1,   926,   927,    -1,    -1,    -1,   267,
      -1,    -1,    10,    45,    -1,   162,    -1,    -1,    -1,    -1,
    1530,    -1,    -1,    -1,   282,   149,    -1,    -1,    60,    61,
      -1,    -1,    -1,  1941,    -1,    -1,   109,  1547,    -1,    45,
     298,    39,    40,    41,    42,   303,   119,    -1,  1889,  1890,
    1891,    -1,   125,    -1,    60,    61,  1566,    -1,    -1,   299,
      -1,    -1,  1237,  1238,  1239,  1240,  1241,  1242,  1243,  1244,
    1245,  1246,  1247,  1914,    -1,    73,   149,   109,    -1,   337,
    1817,    -1,  1990,    81,    82,    83,    84,   119,    -1,    -1,
      -1,    -1,    -1,   125,   352,    -1,    -1,   337,  2006,    -1,
      -1,    -1,    -1,   109,    -1,    -1,   104,    -1,    -1,    -1,
    1847,    -1,   352,   119,    -1,    -1,    -1,   149,    -1,   125,
     267,    -1,    -1,   121,  1634,    -1,    -1,    -1,   126,   127,
     128,    -1,  1869,   131,    -1,   282,   134,    -1,    -1,    -1,
      -1,  1878,    -1,   149,    -1,    -1,    -1,     1,    -1,  1413,
       4,   298,     6,    -1,    -1,    -1,   303,    -1,    -1,    -1,
      -1,  1425,    -1,    -1,    -1,  1773,  1774,  1775,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    -1,  1687,    -1,    -1,
      -1,  1103,    -1,    -1,    -1,  1107,    40,    -1,    -1,    -1,
     337,    -1,    -1,    -1,  1116,  1117,  1118,    -1,    -1,  1121,
      -1,  1123,    -1,    -1,  1941,   352,    -1,    -1,    -1,    -1,
      -1,  1475,    -1,    -1,    -1,    -1,    -1,    -1,  2059,  2060,
    2061,  1143,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1493,
    1494,    -1,    -1,    -1,    88,    89,    90,    91,  1413,    93,
      -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1425,    -1,    -1,  1990,    -1,  1177,    -1,  1179,    -1,   113,
      -1,    -1,    -1,  1185,    -1,    -1,    -1,    -1,    -1,  2006,
      -1,    -1,    -1,   271,   272,   273,  1198,    -1,  1200,    -1,
     107,    -1,   109,   110,    -1,    -1,   113,  1209,   115,  1211,
      -1,   118,   119,    -1,    -1,   122,   123,   124,   125,    -1,
    1475,    23,   129,    -1,    -1,   132,   133,  1817,   162,    -1,
      -1,    -1,    -1,   140,    -1,    -1,    38,    -1,  1493,  1494,
       1,    -1,    -1,     4,     1,     6,    -1,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1847,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    26,
      27,    28,    29,    -1,    -1,    -1,    37,    -1,    -1,  1869,
      -1,    -1,    -1,    40,    -1,    -1,    47,    -1,  1878,    -1,
      -1,    52,    -1,    54,    -1,    56,    -1,    -1,    -1,    -1,
     102,  1989,  1990,  1991,  1992,    -1,    -1,    -1,    -1,  1997,
    1998,  1999,  2000,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   400,   401,   402,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    89,   267,    91,    -1,    93,    -1,    -1,    96,
      -1,    -1,    -1,    -1,  2032,  2033,  2034,     1,   282,    -1,
      -1,  1941,    -1,    -1,    -1,   433,   113,    11,    12,    13,
      14,    15,    16,    17,   298,    -1,    20,    -1,    -1,   303,
      -1,   173,  1374,  1375,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   462,    -1,     1,    -1,    -1,     4,
      -1,     6,    -1,  1395,   102,    -1,    -1,    -1,    -1,    -1,
    1990,   162,    -1,   337,    -1,   162,    -1,    -1,  1410,    -1,
      -1,    26,    27,    28,    29,    -1,  2006,    71,   352,    -1,
      74,    75,    76,    77,    78,    79,    41,    -1,    -1,    44,
      -1,    -1,    86,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,  1444,    97,    98,    99,   100,    -1,   102,    -1,
      -1,    -1,   106,    -1,   108,    -1,    -1,   111,   112,  1461,
     114,  1463,    -1,   117,    70,   173,    -1,    -1,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,    -1,    -1,
      -1,    -1,   136,   137,   138,   139,    -1,    -1,   142,    -1,
     144,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,
      -1,    -1,    -1,    -1,   110,    -1,   267,  1851,   114,    -1,
     267,    -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,   125,
      -1,   282,    -1,   129,    -1,   282,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,     4,   298,     6,    -1,
      -1,   298,   303,   149,   305,    -1,   303,   162,   455,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,   337,    -1,    -1,    -1,
     337,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   352,    -1,    -1,    -1,   352,  1851,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    -1,    93,    23,  1629,    96,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    35,    36,
      37,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,  1658,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,   282,    -1,    -1,
      67,   277,    -1,    -1,   280,   281,    -1,    -1,    -1,  1681,
      -1,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   162,    -1,    93,    -1,    -1,    -1,
      97,    -1,    99,    -1,    -1,   102,   103,   104,   105,   315,
     316,   108,    -1,   110,    -1,    -1,   113,   114,    -1,    -1,
      -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   352,    -1,    -1,
      -1,    -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,
     356,    -1,   149,    -1,    -1,    -1,    -1,   154,   179,    -1,
     157,    -1,    -1,   160,   161,   162,    -1,    -1,   165,    -1,
      -1,   168,    -1,   170,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,    -1,    -1,   447,    -1,   192,   193,    -1,    -1,   267,
     454,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   465,    -1,   467,   282,   469,    -1,   471,    -1,    -1,
      -1,    -1,   476,    -1,    -1,    -1,   480,    -1,   482,    -1,
     298,   228,   229,   230,   231,   303,   490,    -1,    -1,    -1,
     237,   238,    -1,  1845,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,   337,
     267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   352,   282,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   292,    -1,    -1,    -1,    -1,
      -1,   298,    -1,    -1,    -1,    -1,   303,    -1,    -1,    -1,
      -1,    -1,   309,   310,    -1,   312,    -1,    -1,   315,   316,
     317,   318,    -1,    -1,    -1,   322,    -1,    -1,    -1,   326,
     327,   328,    -1,    -1,    -1,   332,   333,    -1,     1,    -1,
     337,     4,    -1,     6,   341,    -1,    -1,   344,   345,    -1,
      -1,    -1,    -1,    -1,   351,   352,   353,    -1,    -1,   356,
      23,    -1,    -1,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      93,    -1,    -1,    -1,    97,    -1,    99,    -1,    -1,   102,
     103,   104,   105,    -1,    -1,   108,    -1,   110,    -1,    -1,
     113,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,
      -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,
      -1,    -1,    -1,   146,    -1,    -1,   149,    -1,    -1,    -1,
      -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,   162,
      -1,    -1,   165,    -1,    -1,   168,    -1,   170,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,     4,    -1,     6,    -1,   192,
     193,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,   228,   229,   230,   231,    -1,
      -1,    -1,    -1,    -1,   237,   238,    -1,    -1,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,    -1,    -1,   267,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    91,    -1,    93,    -1,    -1,    96,    -1,   282,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   292,
      -1,    -1,    -1,    -1,   113,   298,    -1,    -1,    -1,    -1,
     303,    -1,    -1,    -1,    -1,    -1,   309,   310,    -1,   312,
      -1,    -1,   315,   316,   317,   318,    -1,    -1,    -1,   322,
      -1,    -1,    -1,   326,   327,   328,    -1,    -1,    -1,   332,
     333,    -1,     1,    -1,   337,     4,    -1,     6,   341,    -1,
      -1,   344,   345,   162,    -1,    -1,    -1,    -1,   351,   352,
     353,    -1,    -1,   356,    23,    -1,    -1,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,    -1,
      -1,   115,    -1,    52,    -1,    -1,   980,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,   133,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    97,    -1,
      99,    -1,    -1,   102,   103,   104,   105,    -1,    -1,   108,
      -1,   110,    -1,    37,   113,   114,    -1,    -1,   267,    -1,
     119,    45,    -1,    47,    -1,    49,   125,    -1,    52,    53,
      54,    -1,    56,   282,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,   141,    -1,    -1,    -1,    -1,   146,    -1,   298,
     149,    -1,    -1,    -1,   303,   154,    -1,    -1,   157,    -1,
      -1,   160,   161,   162,    -1,    -1,   165,    -1,    -1,   168,
      -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     244,    -1,    -1,    -1,    -1,   109,    -1,    -1,   337,    -1,
      -1,    -1,    -1,   192,   193,   119,    -1,    -1,    -1,    -1,
      -1,   125,    -1,   352,   268,   269,   270,   271,   272,   273,
      -1,   275,   276,   277,   278,   279,   280,   281,    -1,    -1,
     284,   285,   286,    -1,    -1,   149,    -1,    -1,    -1,   228,
     229,   230,   231,    -1,    -1,    -1,    -1,    -1,   237,   238,
      -1,   305,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,    -1,    -1,   267,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   282,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   292,    -1,    -1,    -1,    -1,    -1,   298,
      -1,    -1,    -1,    -1,   303,    -1,    -1,    -1,    -1,    -1,
     309,   310,    -1,   312,    -1,    -1,   315,   316,   317,   318,
      -1,    -1,    -1,   322,    -1,    -1,    -1,   326,   327,   328,
      -1,    -1,    -1,   332,   333,    -1,    -1,     4,   337,     6,
      -1,    -1,   341,   267,    -1,   344,   345,    -1,    -1,    -1,
      -1,    -1,   351,   352,   353,    -1,    23,   356,   282,    -1,
      -1,    -1,    -1,    30,    31,    -1,    -1,    -1,    35,    36,
      37,    -1,    -1,    -1,   298,    -1,    -1,    -1,    -1,   303,
      -1,   305,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,   103,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   130,    -1,    -1,   133,    -1,    -1,
      97,    -1,    99,    -1,    -1,   102,   103,   104,   105,    -1,
      -1,   108,    -1,   110,   150,    -1,    -1,   114,    -1,    -1,
      -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,
      -1,    -1,   149,    -1,    -1,    -1,    -1,   154,    -1,    -1,
     157,    -1,    -1,   160,   161,    -1,    -1,    -1,   165,    -1,
      -1,   168,    -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   192,   193,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
      -1,   228,   229,   230,   231,    -1,    -1,    -1,    -1,    -1,
     237,   238,    -1,    -1,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,   305,
     267,    -1,     5,   309,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   319,    -1,   282,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,   292,    -1,    -1,    31,    -1,
      -1,   298,    -1,    36,    -1,    -1,   303,    -1,    -1,   345,
      -1,    -1,   309,   310,    -1,   312,    -1,    -1,   315,   316,
     317,   318,    -1,    -1,    -1,   322,    -1,    -1,    -1,   326,
     327,   328,    -1,    -1,    -1,   332,   333,    70,    -1,    -1,
      -1,    -1,    -1,    -1,   341,    -1,    -1,   344,   345,    -1,
      -1,    84,    -1,    86,   351,   352,   353,    -1,    -1,   356,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,    -1,    -1,   108,    -1,   110,    -1,    -1,
      -1,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,
      -1,    -1,   125,    -1,    -1,    -1,   129,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,
      -1,    -1,    -1,   146,    -1,    -1,   149,    -1,    -1,    -1,
      -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,    -1,
      -1,    -1,   165,    -1,    -1,   168,    -1,   170,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,   192,
     193,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     111,   112,    -1,    -1,   115,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,   228,    31,    -1,    -1,    -1,
      -1,    36,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,    -1,    -1,   267,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   277,    -1,    -1,   280,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   187,    -1,    -1,    -1,
     293,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,    -1,    -1,   108,    -1,   110,   309,   310,    -1,   114,
      -1,    -1,   315,   316,   119,    -1,    -1,    -1,    -1,    -1,
     125,    -1,    -1,    -1,   129,   328,    -1,    -1,    -1,   332,
     333,    -1,    -1,    -1,    -1,    -1,   141,    -1,    -1,   342,
     343,   146,   345,   244,   149,    -1,    -1,    -1,    -1,   154,
     353,    -1,   157,   356,    -1,   160,   161,    -1,    -1,    -1,
     165,    -1,    -1,   168,    -1,   170,    -1,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,    -1,    -1,   284,   285,   286,    -1,   192,   193,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,    -1,    -1,   305,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,   228,    31,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      -1,    -1,   267,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   277,    -1,    -1,   280,   281,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,    -1,
      -1,   108,    -1,   110,   309,   310,    -1,   114,    -1,    -1,
     315,   316,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,    -1,   129,   328,    -1,    -1,    -1,   332,   333,    -1,
      -1,    -1,    -1,    -1,   141,    -1,    -1,   342,   343,   146,
     345,    -1,   149,    -1,    -1,    -1,    -1,   154,   353,    -1,
     157,   356,    -1,   160,   161,    -1,    -1,    -1,   165,    -1,
      -1,   168,    -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   192,   193,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,   228,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,    -1,
     267,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     277,    -1,    -1,   280,   281,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,    -1,    -1,   108,
      -1,   110,   309,   310,    -1,   114,    -1,    -1,   315,   316,
     119,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,
     129,   328,    -1,    -1,    -1,   332,   333,    -1,    -1,    -1,
      -1,    -1,   141,    -1,    -1,   342,   343,   146,   345,    -1,
     149,    -1,    -1,    -1,    -1,   154,   353,    -1,   157,   356,
      -1,   160,   161,    -1,    -1,    -1,   165,    -1,    -1,   168,
      -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   192,   193,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,   228,
      31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,    -1,    -1,   267,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,    -1,
      -1,   280,   281,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,    -1,    -1,   108,    -1,   110,
     309,   310,    -1,   114,    -1,    -1,   315,   316,   119,    -1,
      -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,   129,   328,
      -1,    -1,    -1,   332,   333,    -1,    -1,    -1,    -1,    -1,
     141,    -1,    -1,   342,   343,   146,   345,    -1,   149,    -1,
      -1,    -1,    -1,   154,   353,    -1,   157,   356,    -1,   160,
     161,    -1,    -1,    -1,   165,    -1,    -1,   168,    -1,   170,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   192,   193,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,    -1,    -1,   267,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   277,    -1,    -1,   280,
     281,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,   110,   309,   310,
      -1,   114,    -1,    -1,   315,   316,   119,    -1,    -1,    -1,
      -1,    -1,   125,    -1,    -1,    -1,   129,   328,    -1,    -1,
      -1,   332,   333,    -1,    -1,    -1,    70,    -1,   141,    -1,
      -1,   342,   343,   146,   345,    -1,   149,    -1,    -1,    -1,
      -1,   154,   353,    -1,   157,   356,    21,   160,   161,    -1,
      -1,    -1,   165,    -1,    -1,   168,    -1,   170,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,
     114,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,   192,
     193,   125,    -1,    -1,    -1,   129,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,   141,    -1,    -1,
      -1,    -1,   146,    -1,    -1,   149,    -1,    -1,    -1,    -1,
     154,    -1,    -1,   157,    -1,    -1,   160,   161,    -1,    -1,
      -1,   165,    -1,    -1,   168,    -1,   170,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,   114,
      -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,   192,   193,
     125,    -1,    -1,    -1,   129,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   277,    -1,   141,   280,   281,    -1,
      -1,   146,    -1,    -1,   149,    -1,    22,    23,    -1,   154,
      -1,    -1,   157,    -1,    -1,   160,   161,    -1,    -1,    -1,
     165,    -1,    -1,   168,    -1,   170,    -1,    -1,    -1,    -1,
      -1,    -1,   315,   316,    -1,   318,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,   193,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,   342,
     343,    -1,    -1,   277,    -1,    -1,   280,   281,   351,    -1,
     353,    -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
      -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,   114,    -1,
      -1,   315,   316,   119,   318,    -1,    -1,    -1,    -1,   125,
      -1,    -1,    -1,   129,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   141,    -1,    -1,   342,   343,
     146,    -1,   277,   149,    -1,   280,   281,   351,   154,   353,
      -1,   157,   356,    -1,   160,   161,    -1,    -1,    -1,   165,
      -1,    -1,   168,    -1,   170,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     315,   316,    -1,   318,    -1,    23,   192,   193,    -1,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   342,   343,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,   353,    -1,
      -1,   356,    -1,    -1,    62,    63,   103,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   130,    -1,    -1,   133,    -1,    -1,    97,
      -1,    99,    -1,    -1,   102,   103,   104,   105,    -1,    -1,
     108,   277,   110,   150,   280,   281,   114,    -1,    -1,    -1,
      -1,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,   315,
     316,   149,   318,    -1,    -1,    -1,   154,    -1,    -1,   157,
      -1,    -1,   160,   161,    -1,    -1,    -1,   165,    -1,    -1,
     168,    -1,   170,    -1,    -1,    -1,   342,   343,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   351,    -1,   353,    -1,    -1,
     356,    -1,    -1,    -1,   192,   193,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,    -1,
     228,   229,   230,   231,    -1,    -1,    -1,    -1,    -1,   237,
     238,    -1,    -1,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,    -1,   305,   267,
      -1,    -1,   309,   310,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,   319,    -1,   282,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    36,   292,    -1,    -1,    -1,    -1,    -1,
     298,    -1,    -1,    -1,    -1,   303,    -1,    -1,   345,    -1,
      -1,   309,   310,    -1,   312,    -1,    -1,   315,   316,   317,
     318,    -1,    -1,    -1,   322,    -1,    -1,    -1,   326,   327,
     328,    -1,    -1,    -1,   332,   333,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   341,    -1,    -1,   344,   345,    -1,    -1,
      -1,    -1,    -1,   351,    -1,   353,    -1,    -1,   356,   102,
     103,   104,   105,    -1,    -1,   108,    -1,   110,    -1,    -1,
      -1,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,
      -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,
      -1,    -1,    -1,   146,    -1,    -1,   149,    -1,    -1,    -1,
      -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,    -1,
      -1,    -1,   165,    -1,    -1,   168,    -1,   170,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,
     193,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,
      -1,    -1,    36,    -1,    -1,   228,   229,   230,   231,    -1,
      -1,    -1,    -1,    -1,   237,   238,    -1,    -1,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,    -1,    -1,   267,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,    -1,    -1,   108,    -1,   110,    -1,    -1,    -1,
     114,    -1,    -1,    -1,    -1,   119,   309,   310,    -1,    -1,
      -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   328,    -1,   141,    -1,   332,
     333,    -1,   146,    -1,    -1,   149,    -1,    -1,    -1,    -1,
     154,   344,   345,   157,    -1,    -1,   160,   161,   351,    -1,
     353,   165,    -1,   356,   168,    -1,   170,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,   192,   193,
      -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   228,   229,   230,   231,    -1,    -1,
      -1,    -1,    -1,   237,   238,    -1,    -1,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,    -1,    -1,   267,   102,   103,   104,   105,    -1,    -1,
     108,    -1,   110,    -1,    37,    -1,   114,    -1,    -1,    42,
      -1,   119,    45,    46,    47,    48,    -1,   125,    51,    52,
      -1,    54,    55,    56,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,    -1,   309,   310,    -1,   146,    -1,
      -1,   149,    -1,    -1,    -1,    -1,   154,    -1,    -1,   157,
      -1,    -1,   160,   161,   328,    -1,    -1,   165,   332,   333,
     168,    -1,   170,    -1,    97,    -1,    99,   100,   101,    -1,
     344,   345,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   353,
      -1,    23,   356,    -1,   192,   193,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     228,   229,   230,   231,    -1,    -1,    -1,    -1,    70,   237,
     238,    -1,    -1,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,    -1,    -1,   267,
     102,   103,   104,   105,    -1,    -1,   108,    -1,   110,    -1,
      -1,    -1,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,
      -1,    -1,    -1,   125,    -1,    -1,    -1,   129,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
      -1,   309,   310,    -1,   146,    -1,    -1,   149,    -1,    -1,
      -1,    -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,
     328,    -1,    -1,   165,   332,   333,   168,    -1,   170,    -1,
      -1,    -1,    -1,    -1,   267,    -1,   344,   345,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   353,    -1,    -1,   356,   282,
     192,   193,    -1,    -1,   287,   288,   289,   290,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   298,    -1,    -1,    -1,    -1,
     303,    -1,   305,   306,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,    -1,    -1,   267,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   277,    -1,    -1,   280,   281,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,   110,   309,   310,    -1,
     114,    -1,    -1,   315,   316,   119,    -1,    -1,    -1,    -1,
      -1,   125,    -1,    -1,    -1,   129,   328,    -1,    -1,    -1,
     332,   333,    -1,    -1,    -1,    -1,    -1,   141,    -1,    -1,
     342,   343,   146,   345,    -1,   149,    -1,    -1,    -1,    -1,
     154,   353,    -1,   157,   356,    -1,   160,   161,    -1,    -1,
      -1,   165,    -1,    -1,   168,    -1,   170,    -1,    -1,     0,
       1,    -1,    -1,     4,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,   193,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    47,    -1,    49,    -1,
      -1,    52,    53,    54,    -1,    56,    -1,    -1,    -1,    60,
      61,    62,    -1,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   277,    -1,    -1,   280,   281,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,   119,    -1,
      -1,    -1,    -1,    -1,   125,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   315,   316,    -1,   318,    -1,    -1,    -1,   149,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,   110,    -1,    -1,
      -1,   114,    -1,    -1,    -1,    70,   119,    -1,   342,   343,
      -1,    -1,   125,    -1,    -1,    -1,   129,   351,    -1,   353,
      -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,   141,    -1,
      -1,    -1,    -1,   146,    -1,    -1,   149,   102,   103,   104,
     105,   154,    -1,    -1,   157,   110,    -1,   160,   161,   114,
      -1,    -1,   165,    -1,   119,   168,    -1,   170,    -1,    -1,
     125,    -1,    -1,    -1,   129,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,   141,    -1,    -1,   192,
     193,   146,    -1,    -1,   149,    -1,    -1,    -1,    -1,   154,
      -1,    -1,   157,    -1,    -1,   160,   161,    -1,    -1,    -1,
     165,    -1,    -1,   168,    -1,   170,   267,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,   114,
      -1,   282,    -1,    -1,   119,    -1,    -1,   192,   193,    -1,
     125,    -1,    -1,    -1,   129,    -1,    -1,   298,    -1,    -1,
      -1,    -1,   303,    -1,   305,    -1,   141,    -1,    -1,    -1,
      -1,   146,    -1,    -1,   149,    -1,    -1,    -1,    -1,   154,
      -1,    -1,   157,    -1,   277,   160,   161,   280,   281,    -1,
     165,    -1,    -1,   168,    -1,   170,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,   193,    -1,
      -1,    -1,   315,   316,    -1,   318,    -1,    -1,    -1,    -1,
      -1,    -1,   277,    -1,    -1,   280,   281,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   342,
     343,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     353,    -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,
     315,   316,    -1,   318,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   342,   343,    -1,
      -1,    -1,   277,    -1,    -1,   280,   281,    -1,   353,    -1,
      -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     315,   316,    -1,   318,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   342,   343,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   353,    -1,
      -1,   356
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   360,     0,     1,     4,     6,    26,    27,    28,    29,
      37,    45,    47,    49,    52,    53,    54,    56,    60,    61,
      62,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,   109,   119,   125,   149,   267,   282,
     298,   303,   305,   361,   384,   385,   386,   387,   459,   460,
     461,   463,   478,   361,   104,   103,   456,   456,   456,   461,
     472,   461,   463,   478,   461,   466,   466,   466,   461,   469,
     387,    49,   388,    37,    45,    47,    52,    53,    54,    56,
     267,   282,   298,   303,   305,   389,    49,   390,    37,    45,
      47,    49,    52,    53,    54,    56,   267,   282,   298,   303,
     305,   395,    53,   396,    37,    42,    45,    46,    47,    48,
      51,    52,    54,    55,    56,    58,    97,    99,   100,   101,
     267,   282,   287,   288,   289,   290,   298,   303,   305,   306,
     397,   282,   287,   288,   303,   400,    45,    47,    52,    54,
      58,    97,    99,   401,    47,   402,    23,    30,    31,    36,
     102,   103,   104,   105,   108,   110,   114,   119,   125,   141,
     146,   149,   154,   157,   160,   161,   165,   168,   170,   192,
     193,   228,   229,   230,   231,   237,   238,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   267,   309,   310,   328,   332,   333,   344,   345,   353,
     356,   410,   457,   580,   581,   584,   585,   586,   590,   653,
     656,   658,   662,   667,   668,   670,   672,   682,   683,   685,
     687,   689,   691,   695,   697,   699,   701,   703,   705,   707,
     709,   711,   713,   717,   725,   727,   729,   730,   732,   734,
     736,   738,   740,   742,   744,   746,    58,   338,   339,   340,
     403,   409,    58,   404,   409,   103,   405,   406,   363,   369,
     370,    89,   274,   276,   472,   472,   472,   472,     0,   361,
     456,   456,    57,   335,   336,   475,   476,   477,    35,    37,
      52,    62,    63,    67,    78,    79,    80,    81,    82,    83,
      97,    99,   243,   267,   282,   292,   298,   303,   312,   315,
     316,   317,   318,   322,   326,   327,   341,   351,   482,   483,
     484,   486,   487,   488,   489,   490,   491,   495,   496,   497,
     500,   501,   508,   512,   520,   521,   524,   525,   526,   527,
     528,   549,   550,   552,   553,   555,   556,   559,   560,   561,
     571,   572,   573,   574,   575,   578,   579,   585,   592,   593,
     594,   595,   596,   597,   601,   602,   603,   637,   651,   656,
     657,   680,   681,   682,   361,   350,   350,   361,   456,   532,
     411,   414,   482,   456,   419,   421,   580,   603,   424,   456,
     429,   463,   479,   472,   461,   463,   466,   466,   466,   469,
      89,   274,   276,   472,   472,   472,   472,   478,   394,   461,
     472,   473,   391,   459,   461,   462,   392,   461,   463,   464,
     479,   393,   461,   466,   467,   466,   466,   461,   469,   470,
      89,   274,   276,   626,   394,   394,   394,   394,   466,   472,
     399,   460,   481,   461,   481,   463,   481,    45,   481,   466,
     466,   481,   469,   481,    45,    46,   466,   481,   481,    89,
     274,   291,   626,   627,   472,    45,   481,    45,   481,    45,
     481,    45,   481,   472,   472,   472,    45,   481,   373,   472,
      45,   481,    45,   481,   472,   461,   463,   466,   466,   481,
      45,   466,   463,   103,   106,   107,   108,   684,   111,   112,
     244,   245,   248,   588,   589,    32,    33,    34,   244,   659,
     132,   591,   166,   167,   728,   111,   112,   113,   686,   113,
     115,   116,   117,   118,   688,   111,   112,   120,   121,   122,
     123,   124,   690,   111,   112,   115,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   175,   692,   113,   115,   134,
     142,   143,   144,   145,   696,   113,   134,   147,   294,   698,
     111,   112,   126,   128,   129,   130,   151,   152,   153,   700,
     113,   115,   134,   142,   143,   145,   155,   156,   702,   127,
     143,   152,   158,   159,   704,   143,   159,   706,   152,   162,
     163,   708,   130,   134,   166,   167,   710,   134,   166,   167,
     169,   712,   134,   143,   158,   162,   166,   167,   171,   172,
     173,   174,   175,   714,   113,   166,   167,   718,   134,   166,
     167,   194,   227,   726,   113,   125,   127,   145,   149,   152,
     232,   265,   266,   345,   669,   671,   733,   233,   735,   233,
     737,   162,   234,   235,   236,   739,   127,   152,   731,   115,
     131,   152,   158,   239,   240,   741,   127,   152,   743,   113,
     127,   134,   152,   158,   745,   103,   130,   133,   150,   305,
     319,   345,   654,   655,   656,   111,   112,   115,   133,   244,
     268,   269,   270,   271,   272,   273,   275,   276,   277,   278,
     279,   280,   281,   284,   285,   286,   305,   673,   674,   677,
     319,   329,   661,   597,   602,   330,   228,   237,   238,   241,
     242,   747,   348,   349,   372,   664,   596,   456,   409,   339,
     409,    46,    48,    50,    51,    58,    59,    91,   407,   472,
     472,   472,   365,   621,   636,   623,   625,   102,   102,   102,
      84,   669,   283,   572,   456,   580,   652,   652,    62,    98,
     456,   103,   654,    89,   187,   274,   673,   674,   283,   283,
     299,   283,   301,   302,   509,    84,   162,    84,    84,   669,
       4,   362,   604,   605,   337,   480,   487,   414,   365,   284,
     285,   498,   499,   383,   162,   293,   294,   295,   296,   297,
     502,   503,   313,   523,     5,    70,    84,    86,   110,   114,
     119,   125,   129,   149,   228,   277,   280,   281,   293,   315,
     316,   342,   343,   353,   535,   536,   537,   538,   539,   540,
     541,   543,   544,   545,   546,   547,   548,   581,   584,   590,
     646,   647,   648,   653,   658,   662,   668,   669,   670,   672,
     678,   679,   682,    38,    39,   184,   185,   529,   530,    84,
     319,   320,   321,   551,   557,   558,    84,   554,   557,   377,
     323,   324,   325,   562,   563,   567,   568,    23,   580,   582,
     583,    45,   576,   577,    15,    16,    17,    18,   355,     8,
      24,    54,     9,    10,    11,    12,    13,    14,    19,   110,
     114,   119,   125,   141,   146,   149,   154,   157,   160,   161,
     165,   168,   170,   192,   193,   318,   353,   581,   583,   584,
     598,   599,   600,   603,   638,   639,   640,   641,   642,   643,
     644,   645,   647,   648,   649,   650,    52,    52,    22,   351,
     619,   638,   639,   644,   619,    38,   351,   531,   351,   351,
     351,   351,   351,   475,   482,   532,   411,   414,   419,   421,
     424,   429,   472,   472,   472,   365,   621,   636,   623,   625,
     482,    57,    57,    57,    57,   421,    57,   429,   472,   365,
     374,   376,   381,   421,    43,   398,   461,   466,   481,   472,
      45,   365,   461,   461,   461,   461,   374,   376,   381,   461,
     365,   461,   461,   376,   466,   456,     7,     8,   113,   248,
     249,   587,   297,   382,   103,   126,   283,   366,   371,   110,
     125,   110,   125,   363,   137,   138,   139,   140,   693,   369,
     370,    23,    38,   102,   173,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   715,   179,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   719,   724,   379,   369,   370,   372,
     671,   378,   378,   357,   357,   381,   381,   111,   112,   125,
     133,   149,   268,   269,   270,   675,   676,   677,   364,   330,
     330,   102,   378,   347,   663,   354,   408,   409,   634,   634,
     634,   284,   351,   620,   299,   351,   635,   351,   509,   622,
     351,   457,   624,     5,   125,   149,   547,    84,   547,   569,
     570,   597,    23,    23,    96,   351,    52,    52,    52,   102,
     301,    52,   677,    52,   547,   547,   301,   302,   513,   547,
     102,   564,   565,   566,   580,   584,   597,   601,   662,   668,
     567,   547,   547,    84,    21,   603,   608,   609,   610,   617,
     644,   645,     7,   352,   457,   351,   102,   102,   499,    77,
     110,   125,   170,   251,   505,   457,   102,   102,   102,   457,
     504,   503,   141,   154,   170,   314,   547,     5,   547,    84,
     366,   371,   363,   369,   370,    84,   540,   581,   648,    15,
      16,    17,    18,   355,    20,    22,     8,    54,     5,   557,
      84,    86,   233,   293,     7,     7,   102,   102,   530,     5,
       7,     5,   547,   565,   580,   584,   563,     7,   456,   351,
     456,   351,   577,   649,   649,   640,   641,   642,   596,   351,
     492,   582,   639,   369,   370,   379,   644,     7,    20,    15,
      16,    17,    18,   355,     7,    20,    22,     8,   638,   639,
     644,   547,   547,   102,   352,   361,    20,   361,   102,   444,
     413,   415,   420,   426,   430,   531,   351,   351,   351,   351,
     351,   634,   634,   634,   620,   635,   622,   624,   102,   102,
     102,   102,   102,   351,   634,   103,   364,   461,   102,   589,
     367,   102,   366,   369,   366,   369,   113,   130,   135,   136,
     233,   369,   694,   715,    96,   130,   186,   187,   188,   189,
     190,   191,   716,   217,   221,   222,   223,   723,   212,   213,
     214,   215,   721,   216,   217,   218,   219,   220,   722,   722,
     221,   224,   224,   225,   226,   225,   113,   130,   162,   720,
     380,   378,   102,   102,   111,   112,   111,   112,   364,   364,
     102,   102,   331,   660,   102,   159,   346,   665,   669,   351,
     351,   351,   102,   437,   365,   513,   442,   374,   438,   102,
     376,   443,   381,   547,     5,     5,   547,   582,    89,    92,
     480,   611,   612,   457,   457,   102,   597,   606,   607,   547,
     547,   547,   364,   102,   547,    52,   547,   374,   102,   515,
     517,   518,   376,   103,   285,   510,    22,   377,    84,   323,
      43,   547,   362,     5,   362,   267,   282,   298,   614,   615,
      89,    92,   480,   613,   616,   362,   605,   416,   366,   148,
     143,   148,   506,   507,   103,   113,   522,   584,   113,   522,
      70,   113,   522,   547,     5,   547,   547,   354,   535,   535,
     536,   537,   538,   102,   540,   535,   542,   582,   603,   547,
     547,    84,     8,    84,   581,   648,   678,   678,   547,   558,
     547,   557,   568,   569,   606,   362,   493,   494,   354,   644,
     638,   644,   649,   649,   640,   641,   642,   644,   102,   638,
     644,   600,   644,    20,    20,   102,    39,   361,   352,   361,
     384,   480,   531,    37,    47,    52,    54,    56,   162,   267,
     282,   298,   303,   305,   352,   361,   384,   412,   480,    93,
     113,   162,   352,   361,   384,   446,   452,   453,   480,   482,
      40,    88,    89,    90,    91,    93,    96,   113,   162,   267,
     352,   361,   384,   427,   480,   485,   486,    40,    89,    91,
     113,   162,   352,   361,   384,   427,   480,   485,    41,    44,
     162,   282,   352,   361,   384,   413,   415,   420,   426,   430,
     351,   351,   351,   365,   374,   376,   381,   430,   364,   364,
       7,   382,   369,     7,   379,   358,   358,   369,   369,   370,
     370,   660,   334,   660,   102,   368,   372,   111,   112,   666,
     440,   441,   439,   285,   352,   361,   384,   480,   620,   515,
     517,   352,   361,   384,   480,   635,   352,   361,   384,   480,
     622,   510,   352,   361,   384,   480,   624,   547,   547,     5,
     103,   458,   458,   612,   351,   487,   611,   364,   364,   364,
     547,   364,    20,   103,   285,   300,   514,   300,   516,    20,
     304,   511,   564,   580,   584,   566,   565,   547,    43,    81,
      82,   618,   645,   651,   187,   284,   365,   299,   615,   458,
     458,   616,   352,   361,   482,   369,     7,   522,   522,   522,
     547,     5,   547,   164,   547,   557,   557,     5,   352,   485,
     487,   608,     7,   352,   638,   638,   102,    39,   456,   474,
     456,   465,   456,   468,   468,   456,   471,   103,    89,   274,
     276,   474,   474,   474,   474,   361,    78,    79,   454,   455,
     580,   103,    98,   361,   361,   361,   361,   361,   418,   585,
     458,   458,   350,    94,    95,   428,   102,   103,   128,   129,
     244,   264,   265,   434,   435,   445,    85,    86,    87,    89,
     422,   423,   361,   361,   361,   486,   418,   458,   350,   435,
     422,   361,   361,   361,   103,   350,    98,   365,   352,   352,
     352,   352,   352,   440,   441,   439,   352,   102,   102,   375,
     102,   368,   372,    93,   133,   268,   352,   361,   384,   480,
     632,    89,    96,   133,   167,   268,   352,   361,   384,   480,
     633,   113,   268,   352,   361,   384,   480,   629,   102,   365,
     514,   516,   374,   376,   511,   381,   547,   606,   352,   364,
     307,   308,   309,   310,   311,   519,   102,   374,   102,   518,
     374,   519,   102,   376,   377,   377,   547,   362,   102,   301,
     102,   513,   361,   507,   547,    84,   569,     5,   352,   352,
       5,   362,   494,   185,   533,   102,   436,   414,   419,   424,
     429,   474,   474,   474,   436,   436,   436,   436,    41,     8,
     361,   361,   361,   421,     8,   361,     7,   361,     5,   361,
     421,     5,   361,   150,   447,   351,   431,   580,   361,   352,
     352,   352,     7,   660,   350,   165,   170,   628,   460,   364,
     458,   102,   628,   102,   460,   364,   104,   460,   364,   487,
     284,   103,   510,   364,   102,   285,   515,   517,   547,   352,
     569,   651,   184,   534,   361,   351,   351,   351,   351,   351,
     436,   436,   436,   351,   351,   351,   351,   103,   585,   434,
     423,    86,   417,   418,   585,    86,   282,   298,   303,   305,
     425,   435,    22,   102,   103,   349,   448,   449,   450,   580,
     361,   103,   432,   433,   580,   361,   364,   364,   364,   102,
     368,   351,   361,   361,   361,   361,   361,   361,   361,   133,
     361,   352,   364,   102,   514,   516,   352,   362,   533,   444,
     415,   420,   426,   430,   351,   351,   351,   437,   442,   438,
     443,    43,    44,   451,   418,   361,     8,   435,   365,   374,
     376,   381,   361,   361,   102,    22,    25,     7,   352,   103,
     630,   631,   628,   365,   374,   374,   534,   352,   352,   352,
     352,   352,   440,   441,   439,   352,   352,   352,   352,   457,
     580,   350,   447,   361,   585,   361,   102,   102,   362,   433,
       5,     7,   352,   361,   361,   361,   361,   361,   361,   352,
     352,   352,   361,   361,   361,   361,   431,   102,   631,   361,
     364,   364,   364,   365,   374,   376,   381,   361,   361,   361
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   359,   360,   360,   361,   361,   362,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     384,   384,   384,   384,   385,   385,   385,   385,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   388,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   390,   391,   391,   392,   392,
     393,   393,   394,   394,   395,   395,   395,   395,   395,   395,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   396,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   398,   399,   399,   400,   400,   400,
     400,   400,   400,   401,   401,   401,   401,   401,   401,   401,
     402,   403,   403,   404,   404,   405,   406,   406,   407,   407,
     407,   407,   407,   407,   407,   407,   408,   408,   409,   409,
     409,   410,   411,   412,   412,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   414,   415,   415,   415,   415,   415,   415,   415,   415,
     416,   416,   416,   417,   417,   418,   418,   419,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     420,   421,   421,   422,   422,   423,   423,   423,   423,   424,
     425,   425,   425,   425,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   427,   427,
     428,   428,   429,   430,   430,   430,   430,   430,   430,   430,
     431,   431,   432,   432,   432,   433,   433,   434,   434,   435,
     435,   436,   437,   437,   437,   437,   437,   438,   438,   438,
     438,   438,   439,   439,   439,   439,   439,   440,   440,   440,
     440,   440,   441,   441,   441,   441,   441,   442,   442,   442,
     442,   442,   443,   443,   443,   443,   443,   444,   444,   444,
     444,   444,   445,   445,   445,   445,   445,   446,   447,   448,
     448,   449,   449,   449,   449,   449,   450,   450,   451,   451,
     451,   451,   452,   453,   454,   454,   455,   455,   456,   457,
     457,   457,   458,   459,   459,   460,   460,   460,   460,   460,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   478,
     478,   478,   479,   480,   481,   481,   482,   482,   483,   484,
     484,   485,   485,   486,   486,   486,   486,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   488,   488,   489,
     490,   490,   491,   492,   492,   493,   493,   493,   494,   495,
     495,   496,   496,   497,   497,   498,   498,   499,   499,   500,
     500,   501,   502,   502,   503,   503,   503,   503,   503,   503,
     504,   505,   505,   505,   505,   505,   506,   506,   507,   507,
     508,   508,   508,   509,   509,   509,   510,   510,   511,   511,
     512,   512,   513,   513,   513,   514,   514,   515,   516,   516,
     517,   517,   518,   518,   519,   519,   519,   519,   519,   520,
     521,   522,   522,   523,   523,   523,   523,   523,   523,   523,
     523,   524,   525,   525,   526,   526,   526,   526,   526,   526,
     527,   527,   528,   528,   529,   529,   530,   530,   530,   530,
     531,   531,   532,   533,   533,   534,   534,   535,   535,   535,
     535,   535,   535,   535,   535,   535,   535,   535,   535,   535,
     536,   536,   536,   537,   537,   538,   538,   539,   539,   540,
     541,   541,   542,   542,   543,   543,   544,   545,   546,   546,
     547,   547,   547,   548,   548,   548,   548,   548,   548,   548,
     548,   548,   548,   548,   548,   548,   548,   549,   549,   550,
     551,   551,   551,   552,   552,   553,   554,   554,   554,   554,
     554,   555,   555,   556,   556,   557,   557,   558,   558,   558,
     559,   559,   559,   559,   560,   560,   561,   562,   562,   563,
     563,   564,   564,   565,   565,   565,   566,   566,   566,   566,
     567,   567,   568,   568,   569,   569,   570,   571,   571,   571,
     572,   572,   572,   573,   573,   574,   574,   575,   576,   576,
     577,   578,   578,   579,   580,   581,   581,   582,   582,   583,
     584,   585,   585,   585,   585,   585,   585,   585,   585,   585,
     585,   585,   585,   585,   585,   585,   586,   587,   587,   587,
     588,   588,   588,   588,   588,   589,   589,   590,   590,   591,
     591,   592,   592,   592,   593,   593,   594,   594,   595,   595,
     596,   597,   597,   598,   599,   600,   600,   601,   602,   602,
     602,   603,   604,   604,   604,   605,   605,   605,   606,   606,
     607,   608,   608,   609,   609,   610,   610,   611,   611,   612,
     612,   612,   613,   613,   614,   614,   615,   615,   615,   615,
     615,   615,   616,   616,   616,   617,   618,   618,   619,   619,
     619,   619,   620,   621,   622,   623,   624,   625,   626,   626,
     626,   627,   627,   627,   628,   628,   629,   629,   630,   630,
     631,   632,   632,   632,   633,   633,   633,   633,   633,   634,
     635,   635,   636,   637,   637,   637,   637,   637,   637,   637,
     637,   638,   638,   639,   639,   639,   640,   640,   640,   641,
     641,   642,   642,   643,   643,   644,   645,   645,   645,   645,
     646,   646,   647,   648,   648,   648,   648,   648,   648,   648,
     648,   648,   648,   648,   648,   649,   649,   649,   649,   649,
     649,   649,   649,   649,   649,   649,   649,   649,   649,   649,
     649,   649,   650,   650,   650,   650,   650,   650,   650,   651,
     651,   651,   651,   651,   651,   652,   652,   653,   653,   653,
     654,   654,   655,   655,   655,   655,   655,   656,   656,   656,
     656,   656,   656,   656,   656,   656,   656,   656,   656,   656,
     656,   656,   656,   656,   656,   656,   656,   656,   656,   656,
     656,   657,   657,   657,   657,   657,   657,   658,   658,   659,
     659,   659,   660,   660,   661,   661,   662,   663,   663,   664,
     664,   665,   665,   666,   666,   667,   667,   668,   668,   668,
     669,   669,   670,   670,   671,   671,   671,   671,   672,   672,
     672,   673,   673,   674,   674,   674,   674,   674,   674,   674,
     674,   674,   674,   674,   674,   674,   674,   674,   674,   674,
     675,   675,   675,   675,   675,   675,   675,   676,   676,   676,
     676,   677,   677,   677,   677,   678,   678,   679,   679,   680,
     680,   680,   680,   681,   682,   682,   682,   682,   682,   682,
     682,   682,   682,   682,   682,   682,   682,   682,   682,   682,
     682,   682,   683,   684,   684,   684,   684,   685,   686,   686,
     686,   687,   688,   688,   688,   688,   688,   689,   690,   690,
     690,   690,   690,   690,   690,   690,   690,   691,   691,   691,
     692,   692,   692,   692,   692,   692,   692,   692,   692,   692,
     692,   692,   693,   693,   693,   693,   694,   694,   694,   694,
     694,   695,   696,   696,   696,   696,   696,   696,   696,   697,
     698,   698,   698,   698,   699,   700,   700,   700,   700,   700,
     700,   700,   700,   700,   701,   702,   702,   702,   702,   702,
     702,   702,   702,   703,   704,   704,   704,   704,   704,   705,
     706,   706,   707,   708,   708,   708,   709,   710,   710,   710,
     710,   711,   712,   712,   712,   712,   713,   713,   713,   713,
     714,   714,   714,   714,   714,   714,   714,   714,   714,   714,
     715,   715,   715,   715,   715,   715,   715,   715,   715,   715,
     715,   715,   715,   716,   716,   716,   716,   716,   716,   716,
     716,   717,   718,   718,   718,   719,   719,   719,   719,   719,
     719,   719,   719,   719,   719,   719,   719,   719,   719,   719,
     719,   719,   719,   720,   720,   720,   721,   721,   721,   721,
     722,   722,   722,   722,   722,   723,   723,   723,   723,   724,
     724,   724,   724,   724,   724,   724,   724,   724,   724,   724,
     724,   725,   725,   726,   726,   726,   726,   727,   728,   728,
     729,   729,   729,   729,   729,   729,   729,   729,   730,   731,
     731,   732,   733,   733,   733,   733,   734,   735,   736,   737,
     738,   739,   739,   739,   739,   740,   741,   741,   741,   741,
     741,   741,   742,   743,   743,   744,   745,   745,   745,   745,
     745,   746,   747,   747,   747,   747,   747
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       5,     5,     3,     2,     1,     1,     2,     2,     1,     2,
       2,     2,     2,     2,     2,     3,     2,     2,     2,     2,
       2,     2,     2,     2,     6,     2,     6,     3,     2,     6,
       6,     3,     6,     3,     5,     7,     5,     7,     8,     8,
       8,     5,     7,     5,     7,     4,     6,     3,     2,     6,
       2,     6,     6,     6,     3,     6,     3,     5,     5,     8,
       8,     8,     5,     5,     4,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     3,
       2,     2,     6,     3,     3,     5,     3,     3,     2,     3,
       2,     2,     2,     2,     2,     3,     2,     2,     3,     3,
       2,     3,     3,     2,     3,     3,     2,     3,     3,     2,
       3,     2,     2,     3,     3,     2,     2,     2,     2,     2,
       2,     4,     5,     2,     2,     1,     2,     2,     3,     3,
       2,     3,     3,     2,     2,     2,     2,     3,     2,     2,
       3,     2,     1,     2,     1,     3,     0,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     1,     1,
       2,     1,     0,     2,     1,     0,     2,     2,     3,     8,
       8,     8,     8,     9,     9,    10,    10,    10,     9,     9,
       8,     0,     0,     2,     2,     3,     3,     3,     3,     3,
       0,     2,     3,     1,     3,     1,     3,     0,     0,     2,
       2,     4,     4,     4,     4,     4,     3,     4,     2,     3,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     0,
       2,     2,     2,     2,     0,     2,     2,     4,     6,     7,
       6,     7,     6,     4,     3,     4,     3,     3,     2,     2,
       1,     1,     0,     0,     2,     2,     5,     5,     3,     4,
       3,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       3,     0,     0,     2,     2,     2,     2,     0,     2,     2,
       2,     2,     0,     2,     2,     2,     2,     0,     2,     2,
       2,     2,     0,     2,     2,     2,     2,     0,     2,     2,
       2,     2,     0,     2,     2,     2,     2,     0,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     6,     2,     1,
       1,     1,     1,     1,     3,     3,     1,     2,     2,     2,
       3,     0,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     2,     2,     1,     2,     1,
       1,     2,     3,     2,     3,     1,     2,     3,     1,     2,
       3,     1,     2,     3,     1,     2,     2,     2,     1,     2,
       2,     2,     2,     2,     0,     1,     1,     2,     1,     1,
       2,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     1,     3,     3,     1,     1,     3,     3,     5,     4,
       5,     1,     2,     1,     3,     1,     2,     2,     2,     1,
       2,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       1,     2,     3,     1,     2,     1,     3,     1,     1,     1,
       6,     6,     4,     1,     1,     0,     1,     1,     0,     3,
       6,     4,     1,     1,     0,     0,     3,     3,     0,     2,
       2,     3,     2,     2,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     0,     4,     3,     4,     3,     4,     3,
       3,     2,     1,     1,     3,     4,     4,     5,     6,     5,
       1,     2,     1,     3,     1,     2,     2,     2,     1,     1,
       6,     8,     0,     0,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       1,     3,     1,     1,     3,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     2,     3,     3,     4,     5,     2,
       3,     2,     6,     4,     3,     4,     3,     2,     1,     1,
       3,     4,     1,     2,     1,     1,     2,     3,     1,     3,
       4,     3,     5,     3,     6,     1,     3,     1,     1,     1,
       2,     4,     6,     6,     1,     2,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     2,     1,     4,     5,     6,
       1,     1,     1,     7,     8,     6,     1,     1,     1,     2,
       2,     6,     8,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     3,     0,
       2,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     1,     3,     3,     3,     1,     1,     3,     1,     1,
       1,     3,     1,     3,     3,     3,     3,     5,     1,     2,
       1,     1,     2,     1,     1,     2,     1,     1,     2,     2,
       2,     1,     1,     2,     1,     2,     2,     6,     6,     6,
       4,     5,     2,     2,     1,     1,     1,     1,     1,     1,
       2,     2,     4,     0,     4,     0,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     3,     1,     3,
       3,     3,     6,     3,     3,     3,     3,     3,     3,     0,
       4,     4,     0,     2,     2,     4,     4,     5,     5,     3,
       3,     3,     3,     1,     1,     1,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     1,     3,     3,
       1,     1,     1,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     4,     3,     4,     1,     4,     4,     3,     5,     1,
       1,     1,     0,     2,     1,     1,     6,     2,     0,     1,
       1,     1,     1,     1,     1,     5,     6,     8,     6,     5,
       2,     2,     3,     4,     1,     1,     1,     2,     3,     4,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     5,
       5,     5,     6,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     6,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     5,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     1,     1,     1,     2,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     2,     4,     3,     8,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     5,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     3,     1,     1,     1,     1,     2,     4,     2,     1,
       2,     1,     1,     1,     4,     2,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     2,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     1,     1
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
#line 316 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5643 "parser_bison.c"
        break;

    case YYSYMBOL_QUOTED_STRING: /* "quoted string"  */
#line 316 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5649 "parser_bison.c"
        break;

    case YYSYMBOL_ASTERISK_STRING: /* "string with a trailing asterisk"  */
#line 316 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5655 "parser_bison.c"
        break;

    case YYSYMBOL_line: /* line  */
#line 623 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5661 "parser_bison.c"
        break;

    case YYSYMBOL_base_cmd: /* base_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5667 "parser_bison.c"
        break;

    case YYSYMBOL_add_cmd: /* add_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5673 "parser_bison.c"
        break;

    case YYSYMBOL_replace_cmd: /* replace_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5679 "parser_bison.c"
        break;

    case YYSYMBOL_create_cmd: /* create_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5685 "parser_bison.c"
        break;

    case YYSYMBOL_insert_cmd: /* insert_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5691 "parser_bison.c"
        break;

    case YYSYMBOL_table_or_id_spec: /* table_or_id_spec  */
#line 629 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5697 "parser_bison.c"
        break;

    case YYSYMBOL_chain_or_id_spec: /* chain_or_id_spec  */
#line 631 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5703 "parser_bison.c"
        break;

    case YYSYMBOL_set_or_id_spec: /* set_or_id_spec  */
#line 636 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5709 "parser_bison.c"
        break;

    case YYSYMBOL_obj_or_id_spec: /* obj_or_id_spec  */
#line 638 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5715 "parser_bison.c"
        break;

    case YYSYMBOL_delete_cmd: /* delete_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5721 "parser_bison.c"
        break;

    case YYSYMBOL_get_cmd: /* get_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5727 "parser_bison.c"
        break;

    case YYSYMBOL_list_cmd: /* list_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5733 "parser_bison.c"
        break;

    case YYSYMBOL_basehook_device_name: /* basehook_device_name  */
#line 650 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5739 "parser_bison.c"
        break;

    case YYSYMBOL_basehook_spec: /* basehook_spec  */
#line 644 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5745 "parser_bison.c"
        break;

    case YYSYMBOL_reset_cmd: /* reset_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5751 "parser_bison.c"
        break;

    case YYSYMBOL_flush_cmd: /* flush_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5757 "parser_bison.c"
        break;

    case YYSYMBOL_rename_cmd: /* rename_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5763 "parser_bison.c"
        break;

    case YYSYMBOL_import_cmd: /* import_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5769 "parser_bison.c"
        break;

    case YYSYMBOL_export_cmd: /* export_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5775 "parser_bison.c"
        break;

    case YYSYMBOL_monitor_cmd: /* monitor_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5781 "parser_bison.c"
        break;

    case YYSYMBOL_monitor_event: /* monitor_event  */
#line 869 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5787 "parser_bison.c"
        break;

    case YYSYMBOL_describe_cmd: /* describe_cmd  */
#line 626 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5793 "parser_bison.c"
        break;

    case YYSYMBOL_table_block_alloc: /* table_block_alloc  */
#line 656 "parser_bison.y"
            { close_scope(state); table_free(((*yyvaluep).table)); }
#line 5799 "parser_bison.c"
        break;

    case YYSYMBOL_chain_block_alloc: /* chain_block_alloc  */
#line 658 "parser_bison.y"
            { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 5805 "parser_bison.c"
        break;

    case YYSYMBOL_typeof_data_expr: /* typeof_data_expr  */
#line 730 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5811 "parser_bison.c"
        break;

    case YYSYMBOL_typeof_expr: /* typeof_expr  */
#line 730 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5817 "parser_bison.c"
        break;

    case YYSYMBOL_set_block_alloc: /* set_block_alloc  */
#line 667 "parser_bison.y"
            { set_free(((*yyvaluep).set)); }
#line 5823 "parser_bison.c"
        break;

    case YYSYMBOL_set_block_expr: /* set_block_expr  */
#line 771 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5829 "parser_bison.c"
        break;

    case YYSYMBOL_map_block_alloc: /* map_block_alloc  */
#line 670 "parser_bison.y"
            { set_free(((*yyvaluep).set)); }
#line 5835 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_block_alloc: /* flowtable_block_alloc  */
#line 674 "parser_bison.y"
            { flowtable_free(((*yyvaluep).flowtable)); }
#line 5841 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_expr: /* flowtable_expr  */
#line 771 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5847 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_list_expr: /* flowtable_list_expr  */
#line 771 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5853 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_expr_member: /* flowtable_expr_member  */
#line 771 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5859 "parser_bison.c"
        break;

    case YYSYMBOL_data_type_atom_expr: /* data_type_atom_expr  */
#line 620 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5865 "parser_bison.c"
        break;

    case YYSYMBOL_data_type_expr: /* data_type_expr  */
#line 620 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5871 "parser_bison.c"
        break;

    case YYSYMBOL_obj_block_alloc: /* obj_block_alloc  */
#line 677 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 5877 "parser_bison.c"
        break;

    case YYSYMBOL_type_identifier: /* type_identifier  */
#line 615 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5883 "parser_bison.c"
        break;

    case YYSYMBOL_extended_prio_name: /* extended_prio_name  */
#line 650 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5889 "parser_bison.c"
        break;

    case YYSYMBOL_dev_spec: /* dev_spec  */
#line 653 "parser_bison.y"
            { xfree(((*yyvaluep).expr)); }
#line 5895 "parser_bison.c"
        break;

    case YYSYMBOL_policy_expr: /* policy_expr  */
#line 728 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5901 "parser_bison.c"
        break;

    case YYSYMBOL_identifier: /* identifier  */
#line 615 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5907 "parser_bison.c"
        break;

    case YYSYMBOL_string: /* string  */
#line 615 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5913 "parser_bison.c"
        break;

    case YYSYMBOL_table_spec: /* table_spec  */
#line 629 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5919 "parser_bison.c"
        break;

    case YYSYMBOL_tableid_spec: /* tableid_spec  */
#line 629 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5925 "parser_bison.c"
        break;

    case YYSYMBOL_chain_spec: /* chain_spec  */
#line 631 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5931 "parser_bison.c"
        break;

    case YYSYMBOL_chainid_spec: /* chainid_spec  */
#line 631 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5937 "parser_bison.c"
        break;

    case YYSYMBOL_chain_identifier: /* chain_identifier  */
#line 634 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5943 "parser_bison.c"
        break;

    case YYSYMBOL_set_spec: /* set_spec  */
#line 636 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5949 "parser_bison.c"
        break;

    case YYSYMBOL_setid_spec: /* setid_spec  */
#line 636 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5955 "parser_bison.c"
        break;

    case YYSYMBOL_set_identifier: /* set_identifier  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5961 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_spec: /* flowtable_spec  */
#line 634 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5967 "parser_bison.c"
        break;

    case YYSYMBOL_flowtableid_spec: /* flowtableid_spec  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5973 "parser_bison.c"
        break;

    case YYSYMBOL_obj_spec: /* obj_spec  */
#line 638 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5979 "parser_bison.c"
        break;

    case YYSYMBOL_objid_spec: /* objid_spec  */
#line 638 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5985 "parser_bison.c"
        break;

    case YYSYMBOL_obj_identifier: /* obj_identifier  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5991 "parser_bison.c"
        break;

    case YYSYMBOL_handle_spec: /* handle_spec  */
#line 634 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5997 "parser_bison.c"
        break;

    case YYSYMBOL_position_spec: /* position_spec  */
#line 634 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6003 "parser_bison.c"
        break;

    case YYSYMBOL_index_spec: /* index_spec  */
#line 634 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6009 "parser_bison.c"
        break;

    case YYSYMBOL_rule_position: /* rule_position  */
#line 634 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6015 "parser_bison.c"
        break;

    case YYSYMBOL_ruleid_spec: /* ruleid_spec  */
#line 634 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6021 "parser_bison.c"
        break;

    case YYSYMBOL_comment_spec: /* comment_spec  */
#line 615 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6027 "parser_bison.c"
        break;

    case YYSYMBOL_ruleset_spec: /* ruleset_spec  */
#line 634 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6033 "parser_bison.c"
        break;

    case YYSYMBOL_rule: /* rule  */
#line 660 "parser_bison.y"
            { rule_free(((*yyvaluep).rule)); }
#line 6039 "parser_bison.c"
        break;

    case YYSYMBOL_stmt_list: /* stmt_list  */
#line 680 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6045 "parser_bison.c"
        break;

    case YYSYMBOL_stateful_stmt_list: /* stateful_stmt_list  */
#line 680 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6051 "parser_bison.c"
        break;

    case YYSYMBOL_stateful_stmt: /* stateful_stmt  */
#line 684 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6057 "parser_bison.c"
        break;

    case YYSYMBOL_stmt: /* stmt  */
#line 682 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6063 "parser_bison.c"
        break;

    case YYSYMBOL_chain_stmt: /* chain_stmt  */
#line 707 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6069 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_stmt: /* verdict_stmt  */
#line 682 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6075 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_stmt: /* verdict_map_stmt  */
#line 765 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6081 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_expr: /* verdict_map_expr  */
#line 768 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6087 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_list_expr: /* verdict_map_list_expr  */
#line 768 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6093 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_list_member_expr: /* verdict_map_list_member_expr  */
#line 768 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6099 "parser_bison.c"
        break;

    case YYSYMBOL_connlimit_stmt: /* connlimit_stmt  */
#line 695 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6105 "parser_bison.c"
        break;

    case YYSYMBOL_counter_stmt: /* counter_stmt  */
#line 684 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6111 "parser_bison.c"
        break;

    case YYSYMBOL_counter_stmt_alloc: /* counter_stmt_alloc  */
#line 684 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6117 "parser_bison.c"
        break;

    case YYSYMBOL_log_stmt: /* log_stmt  */
#line 692 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6123 "parser_bison.c"
        break;

    case YYSYMBOL_log_stmt_alloc: /* log_stmt_alloc  */
#line 692 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6129 "parser_bison.c"
        break;

    case YYSYMBOL_limit_stmt: /* limit_stmt  */
#line 695 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6135 "parser_bison.c"
        break;

    case YYSYMBOL_quota_unit: /* quota_unit  */
#line 650 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6141 "parser_bison.c"
        break;

    case YYSYMBOL_quota_stmt: /* quota_stmt  */
#line 695 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6147 "parser_bison.c"
        break;

    case YYSYMBOL_reject_stmt: /* reject_stmt  */
#line 698 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6153 "parser_bison.c"
        break;

    case YYSYMBOL_reject_stmt_alloc: /* reject_stmt_alloc  */
#line 698 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6159 "parser_bison.c"
        break;

    case YYSYMBOL_reject_with_expr: /* reject_with_expr  */
#line 713 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6165 "parser_bison.c"
        break;

    case YYSYMBOL_nat_stmt: /* nat_stmt  */
#line 700 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6171 "parser_bison.c"
        break;

    case YYSYMBOL_nat_stmt_alloc: /* nat_stmt_alloc  */
#line 700 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6177 "parser_bison.c"
        break;

    case YYSYMBOL_tproxy_stmt: /* tproxy_stmt  */
#line 703 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6183 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_stmt: /* synproxy_stmt  */
#line 705 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6189 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_stmt_alloc: /* synproxy_stmt_alloc  */
#line 705 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6195 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_obj: /* synproxy_obj  */
#line 791 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6201 "parser_bison.c"
        break;

    case YYSYMBOL_primary_stmt_expr: /* primary_stmt_expr  */
#line 752 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6207 "parser_bison.c"
        break;

    case YYSYMBOL_shift_stmt_expr: /* shift_stmt_expr  */
#line 754 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6213 "parser_bison.c"
        break;

    case YYSYMBOL_and_stmt_expr: /* and_stmt_expr  */
#line 756 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6219 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_stmt_expr: /* exclusive_or_stmt_expr  */
#line 756 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6225 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_stmt_expr: /* inclusive_or_stmt_expr  */
#line 756 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6231 "parser_bison.c"
        break;

    case YYSYMBOL_basic_stmt_expr: /* basic_stmt_expr  */
#line 752 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6237 "parser_bison.c"
        break;

    case YYSYMBOL_concat_stmt_expr: /* concat_stmt_expr  */
#line 744 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6243 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt_expr_set: /* map_stmt_expr_set  */
#line 744 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6249 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt_expr: /* map_stmt_expr  */
#line 744 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6255 "parser_bison.c"
        break;

    case YYSYMBOL_prefix_stmt_expr: /* prefix_stmt_expr  */
#line 749 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6261 "parser_bison.c"
        break;

    case YYSYMBOL_range_stmt_expr: /* range_stmt_expr  */
#line 749 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6267 "parser_bison.c"
        break;

    case YYSYMBOL_multiton_stmt_expr: /* multiton_stmt_expr  */
#line 747 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6273 "parser_bison.c"
        break;

    case YYSYMBOL_stmt_expr: /* stmt_expr  */
#line 744 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6279 "parser_bison.c"
        break;

    case YYSYMBOL_masq_stmt: /* masq_stmt  */
#line 700 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6285 "parser_bison.c"
        break;

    case YYSYMBOL_masq_stmt_alloc: /* masq_stmt_alloc  */
#line 700 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6291 "parser_bison.c"
        break;

    case YYSYMBOL_redir_stmt: /* redir_stmt  */
#line 700 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6297 "parser_bison.c"
        break;

    case YYSYMBOL_redir_stmt_alloc: /* redir_stmt_alloc  */
#line 700 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6303 "parser_bison.c"
        break;

    case YYSYMBOL_dup_stmt: /* dup_stmt  */
#line 716 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6309 "parser_bison.c"
        break;

    case YYSYMBOL_fwd_stmt: /* fwd_stmt  */
#line 718 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6315 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt: /* queue_stmt  */
#line 711 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6321 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_compat: /* queue_stmt_compat  */
#line 711 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6327 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_alloc: /* queue_stmt_alloc  */
#line 711 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6333 "parser_bison.c"
        break;

    case YYSYMBOL_queue_expr: /* queue_expr  */
#line 713 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6339 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_expr_simple: /* queue_stmt_expr_simple  */
#line 713 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6345 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_expr: /* queue_stmt_expr  */
#line 713 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6351 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_stmt: /* set_elem_expr_stmt  */
#line 775 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6357 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_stmt_alloc: /* set_elem_expr_stmt_alloc  */
#line 775 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6363 "parser_bison.c"
        break;

    case YYSYMBOL_set_stmt: /* set_stmt  */
#line 720 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6369 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt: /* map_stmt  */
#line 723 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6375 "parser_bison.c"
        break;

    case YYSYMBOL_meter_stmt: /* meter_stmt  */
#line 725 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6381 "parser_bison.c"
        break;

    case YYSYMBOL_flow_stmt_legacy_alloc: /* flow_stmt_legacy_alloc  */
#line 725 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6387 "parser_bison.c"
        break;

    case YYSYMBOL_meter_stmt_alloc: /* meter_stmt_alloc  */
#line 725 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6393 "parser_bison.c"
        break;

    case YYSYMBOL_match_stmt: /* match_stmt  */
#line 682 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6399 "parser_bison.c"
        break;

    case YYSYMBOL_variable_expr: /* variable_expr  */
#line 728 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6405 "parser_bison.c"
        break;

    case YYSYMBOL_symbol_expr: /* symbol_expr  */
#line 728 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6411 "parser_bison.c"
        break;

    case YYSYMBOL_set_ref_expr: /* set_ref_expr  */
#line 736 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6417 "parser_bison.c"
        break;

    case YYSYMBOL_set_ref_symbol_expr: /* set_ref_symbol_expr  */
#line 736 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6423 "parser_bison.c"
        break;

    case YYSYMBOL_integer_expr: /* integer_expr  */
#line 728 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6429 "parser_bison.c"
        break;

    case YYSYMBOL_primary_expr: /* primary_expr  */
#line 730 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6435 "parser_bison.c"
        break;

    case YYSYMBOL_fib_expr: /* fib_expr  */
#line 860 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6441 "parser_bison.c"
        break;

    case YYSYMBOL_osf_expr: /* osf_expr  */
#line 865 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6447 "parser_bison.c"
        break;

    case YYSYMBOL_shift_expr: /* shift_expr  */
#line 730 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6453 "parser_bison.c"
        break;

    case YYSYMBOL_and_expr: /* and_expr  */
#line 730 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6459 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_expr: /* exclusive_or_expr  */
#line 732 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6465 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_expr: /* inclusive_or_expr  */
#line 732 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6471 "parser_bison.c"
        break;

    case YYSYMBOL_basic_expr: /* basic_expr  */
#line 734 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6477 "parser_bison.c"
        break;

    case YYSYMBOL_concat_expr: /* concat_expr  */
#line 759 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6483 "parser_bison.c"
        break;

    case YYSYMBOL_prefix_rhs_expr: /* prefix_rhs_expr  */
#line 741 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6489 "parser_bison.c"
        break;

    case YYSYMBOL_range_rhs_expr: /* range_rhs_expr  */
#line 741 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6495 "parser_bison.c"
        break;

    case YYSYMBOL_multiton_rhs_expr: /* multiton_rhs_expr  */
#line 739 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6501 "parser_bison.c"
        break;

    case YYSYMBOL_map_expr: /* map_expr  */
#line 762 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6507 "parser_bison.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 781 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6513 "parser_bison.c"
        break;

    case YYSYMBOL_set_expr: /* set_expr  */
#line 771 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6519 "parser_bison.c"
        break;

    case YYSYMBOL_set_list_expr: /* set_list_expr  */
#line 771 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6525 "parser_bison.c"
        break;

    case YYSYMBOL_set_list_member_expr: /* set_list_member_expr  */
#line 771 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6531 "parser_bison.c"
        break;

    case YYSYMBOL_meter_key_expr: /* meter_key_expr  */
#line 778 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6537 "parser_bison.c"
        break;

    case YYSYMBOL_meter_key_expr_alloc: /* meter_key_expr_alloc  */
#line 778 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6543 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr: /* set_elem_expr  */
#line 773 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6549 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_key_expr: /* set_elem_key_expr  */
#line 897 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6555 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_alloc: /* set_elem_expr_alloc  */
#line 773 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6561 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_stmt_list: /* set_elem_stmt_list  */
#line 680 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6567 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_stmt: /* set_elem_stmt  */
#line 682 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6573 "parser_bison.c"
        break;

    case YYSYMBOL_set_lhs_expr: /* set_lhs_expr  */
#line 773 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6579 "parser_bison.c"
        break;

    case YYSYMBOL_set_rhs_expr: /* set_rhs_expr  */
#line 773 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6585 "parser_bison.c"
        break;

    case YYSYMBOL_initializer_expr: /* initializer_expr  */
#line 781 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6591 "parser_bison.c"
        break;

    case YYSYMBOL_counter_obj: /* counter_obj  */
#line 791 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6597 "parser_bison.c"
        break;

    case YYSYMBOL_quota_obj: /* quota_obj  */
#line 791 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6603 "parser_bison.c"
        break;

    case YYSYMBOL_secmark_obj: /* secmark_obj  */
#line 791 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6609 "parser_bison.c"
        break;

    case YYSYMBOL_timeout_states: /* timeout_states  */
#line 890 "parser_bison.y"
            { xfree(((*yyvaluep).list)); }
#line 6615 "parser_bison.c"
        break;

    case YYSYMBOL_timeout_state: /* timeout_state  */
#line 890 "parser_bison.y"
            { xfree(((*yyvaluep).list)); }
#line 6621 "parser_bison.c"
        break;

    case YYSYMBOL_ct_obj_alloc: /* ct_obj_alloc  */
#line 791 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6627 "parser_bison.c"
        break;

    case YYSYMBOL_limit_obj: /* limit_obj  */
#line 791 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6633 "parser_bison.c"
        break;

    case YYSYMBOL_relational_expr: /* relational_expr  */
#line 794 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6639 "parser_bison.c"
        break;

    case YYSYMBOL_list_rhs_expr: /* list_rhs_expr  */
#line 786 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6645 "parser_bison.c"
        break;

    case YYSYMBOL_rhs_expr: /* rhs_expr  */
#line 784 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6651 "parser_bison.c"
        break;

    case YYSYMBOL_shift_rhs_expr: /* shift_rhs_expr  */
#line 786 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6657 "parser_bison.c"
        break;

    case YYSYMBOL_and_rhs_expr: /* and_rhs_expr  */
#line 788 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6663 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_rhs_expr: /* exclusive_or_rhs_expr  */
#line 788 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6669 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_rhs_expr: /* inclusive_or_rhs_expr  */
#line 788 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6675 "parser_bison.c"
        break;

    case YYSYMBOL_basic_rhs_expr: /* basic_rhs_expr  */
#line 784 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6681 "parser_bison.c"
        break;

    case YYSYMBOL_concat_rhs_expr: /* concat_rhs_expr  */
#line 784 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6687 "parser_bison.c"
        break;

    case YYSYMBOL_boolean_expr: /* boolean_expr  */
#line 880 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6693 "parser_bison.c"
        break;

    case YYSYMBOL_keyword_expr: /* keyword_expr  */
#line 781 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6699 "parser_bison.c"
        break;

    case YYSYMBOL_primary_rhs_expr: /* primary_rhs_expr  */
#line 786 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6705 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_expr: /* verdict_expr  */
#line 728 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6711 "parser_bison.c"
        break;

    case YYSYMBOL_chain_expr: /* chain_expr  */
#line 728 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6717 "parser_bison.c"
        break;

    case YYSYMBOL_meta_expr: /* meta_expr  */
#line 842 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6723 "parser_bison.c"
        break;

    case YYSYMBOL_meta_stmt: /* meta_stmt  */
#line 690 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6729 "parser_bison.c"
        break;

    case YYSYMBOL_socket_expr: /* socket_expr  */
#line 846 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6735 "parser_bison.c"
        break;

    case YYSYMBOL_numgen_expr: /* numgen_expr  */
#line 807 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6741 "parser_bison.c"
        break;

    case YYSYMBOL_xfrm_expr: /* xfrm_expr  */
#line 894 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6747 "parser_bison.c"
        break;

    case YYSYMBOL_hash_expr: /* hash_expr  */
#line 807 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6753 "parser_bison.c"
        break;

    case YYSYMBOL_rt_expr: /* rt_expr  */
#line 852 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6759 "parser_bison.c"
        break;

    case YYSYMBOL_ct_expr: /* ct_expr  */
#line 856 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6765 "parser_bison.c"
        break;

    case YYSYMBOL_symbol_stmt_expr: /* symbol_stmt_expr  */
#line 786 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6771 "parser_bison.c"
        break;

    case YYSYMBOL_list_stmt_expr: /* list_stmt_expr  */
#line 754 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6777 "parser_bison.c"
        break;

    case YYSYMBOL_ct_stmt: /* ct_stmt  */
#line 688 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6783 "parser_bison.c"
        break;

    case YYSYMBOL_payload_stmt: /* payload_stmt  */
#line 686 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6789 "parser_bison.c"
        break;

    case YYSYMBOL_payload_expr: /* payload_expr  */
#line 798 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6795 "parser_bison.c"
        break;

    case YYSYMBOL_payload_raw_expr: /* payload_raw_expr  */
#line 798 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6801 "parser_bison.c"
        break;

    case YYSYMBOL_eth_hdr_expr: /* eth_hdr_expr  */
#line 801 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6807 "parser_bison.c"
        break;

    case YYSYMBOL_vlan_hdr_expr: /* vlan_hdr_expr  */
#line 801 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6813 "parser_bison.c"
        break;

    case YYSYMBOL_arp_hdr_expr: /* arp_hdr_expr  */
#line 804 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6819 "parser_bison.c"
        break;

    case YYSYMBOL_ip_hdr_expr: /* ip_hdr_expr  */
#line 807 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6825 "parser_bison.c"
        break;

    case YYSYMBOL_icmp_hdr_expr: /* icmp_hdr_expr  */
#line 807 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6831 "parser_bison.c"
        break;

    case YYSYMBOL_igmp_hdr_expr: /* igmp_hdr_expr  */
#line 807 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6837 "parser_bison.c"
        break;

    case YYSYMBOL_ip6_hdr_expr: /* ip6_hdr_expr  */
#line 811 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6843 "parser_bison.c"
        break;

    case YYSYMBOL_icmp6_hdr_expr: /* icmp6_hdr_expr  */
#line 811 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6849 "parser_bison.c"
        break;

    case YYSYMBOL_auth_hdr_expr: /* auth_hdr_expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6855 "parser_bison.c"
        break;

    case YYSYMBOL_esp_hdr_expr: /* esp_hdr_expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6861 "parser_bison.c"
        break;

    case YYSYMBOL_comp_hdr_expr: /* comp_hdr_expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6867 "parser_bison.c"
        break;

    case YYSYMBOL_udp_hdr_expr: /* udp_hdr_expr  */
#line 817 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6873 "parser_bison.c"
        break;

    case YYSYMBOL_udplite_hdr_expr: /* udplite_hdr_expr  */
#line 817 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6879 "parser_bison.c"
        break;

    case YYSYMBOL_tcp_hdr_expr: /* tcp_hdr_expr  */
#line 875 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6885 "parser_bison.c"
        break;

    case YYSYMBOL_dccp_hdr_expr: /* dccp_hdr_expr  */
#line 820 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6891 "parser_bison.c"
        break;

    case YYSYMBOL_sctp_chunk_alloc: /* sctp_chunk_alloc  */
#line 820 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6897 "parser_bison.c"
        break;

    case YYSYMBOL_sctp_hdr_expr: /* sctp_hdr_expr  */
#line 820 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6903 "parser_bison.c"
        break;

    case YYSYMBOL_th_hdr_expr: /* th_hdr_expr  */
#line 826 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6909 "parser_bison.c"
        break;

    case YYSYMBOL_exthdr_expr: /* exthdr_expr  */
#line 830 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6915 "parser_bison.c"
        break;

    case YYSYMBOL_hbh_hdr_expr: /* hbh_hdr_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6921 "parser_bison.c"
        break;

    case YYSYMBOL_rt_hdr_expr: /* rt_hdr_expr  */
#line 835 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6927 "parser_bison.c"
        break;

    case YYSYMBOL_rt0_hdr_expr: /* rt0_hdr_expr  */
#line 835 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6933 "parser_bison.c"
        break;

    case YYSYMBOL_rt2_hdr_expr: /* rt2_hdr_expr  */
#line 835 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6939 "parser_bison.c"
        break;

    case YYSYMBOL_rt4_hdr_expr: /* rt4_hdr_expr  */
#line 835 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6945 "parser_bison.c"
        break;

    case YYSYMBOL_frag_hdr_expr: /* frag_hdr_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6951 "parser_bison.c"
        break;

    case YYSYMBOL_dst_hdr_expr: /* dst_hdr_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6957 "parser_bison.c"
        break;

    case YYSYMBOL_mh_hdr_expr: /* mh_hdr_expr  */
#line 838 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6963 "parser_bison.c"
        break;

    case YYSYMBOL_exthdr_exists_expr: /* exthdr_exists_expr  */
#line 884 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6969 "parser_bison.c"
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
#line 159 "parser_bison.y"
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 7074 "parser_bison.c"

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
#line 903 "parser_bison.y"
                        {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 7291 "parser_bison.c"
    break;

  case 8: /* close_scope_arp: %empty  */
#line 919 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ARP); }
#line 7297 "parser_bison.c"
    break;

  case 9: /* close_scope_ct: %empty  */
#line 920 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CT); }
#line 7303 "parser_bison.c"
    break;

  case 10: /* close_scope_counter: %empty  */
#line 921 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_COUNTER); }
#line 7309 "parser_bison.c"
    break;

  case 11: /* close_scope_eth: %empty  */
#line 922 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ETH); }
#line 7315 "parser_bison.c"
    break;

  case 12: /* close_scope_fib: %empty  */
#line 923 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FIB); }
#line 7321 "parser_bison.c"
    break;

  case 13: /* close_scope_hash: %empty  */
#line 924 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HASH); }
#line 7327 "parser_bison.c"
    break;

  case 14: /* close_scope_ip: %empty  */
#line 925 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP); }
#line 7333 "parser_bison.c"
    break;

  case 15: /* close_scope_ip6: %empty  */
#line 926 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP6); }
#line 7339 "parser_bison.c"
    break;

  case 16: /* close_scope_vlan: %empty  */
#line 927 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_VLAN); }
#line 7345 "parser_bison.c"
    break;

  case 17: /* close_scope_ipsec: %empty  */
#line 928 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_IPSEC); }
#line 7351 "parser_bison.c"
    break;

  case 18: /* close_scope_list: %empty  */
#line 929 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_LIST); }
#line 7357 "parser_bison.c"
    break;

  case 19: /* close_scope_limit: %empty  */
#line 930 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_LIMIT); }
#line 7363 "parser_bison.c"
    break;

  case 20: /* close_scope_numgen: %empty  */
#line 931 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_NUMGEN); }
#line 7369 "parser_bison.c"
    break;

  case 21: /* close_scope_quota: %empty  */
#line 932 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_QUOTA); }
#line 7375 "parser_bison.c"
    break;

  case 22: /* close_scope_queue: %empty  */
#line 933 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_QUEUE); }
#line 7381 "parser_bison.c"
    break;

  case 23: /* close_scope_rt: %empty  */
#line 934 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_RT); }
#line 7387 "parser_bison.c"
    break;

  case 24: /* close_scope_sctp: %empty  */
#line 935 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_SCTP); }
#line 7393 "parser_bison.c"
    break;

  case 25: /* close_scope_sctp_chunk: %empty  */
#line 936 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SCTP_CHUNK); }
#line 7399 "parser_bison.c"
    break;

  case 26: /* close_scope_secmark: %empty  */
#line 937 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_SECMARK); }
#line 7405 "parser_bison.c"
    break;

  case 27: /* close_scope_socket: %empty  */
#line 938 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SOCKET); }
#line 7411 "parser_bison.c"
    break;

  case 28: /* close_scope_log: %empty  */
#line 940 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_LOG); }
#line 7417 "parser_bison.c"
    break;

  case 29: /* common_block: "include" "quoted string" stmt_separator  */
#line 943 "parser_bison.y"
                        {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 7429 "parser_bison.c"
    break;

  case 30: /* common_block: "define" identifier '=' initializer_expr stmt_separator  */
#line 951 "parser_bison.y"
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
#line 7448 "parser_bison.c"
    break;

  case 31: /* common_block: "redefine" identifier '=' initializer_expr stmt_separator  */
#line 966 "parser_bison.y"
                        {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 7459 "parser_bison.c"
    break;

  case 32: /* common_block: "undefine" identifier stmt_separator  */
#line 973 "parser_bison.y"
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
#line 7475 "parser_bison.c"
    break;

  case 33: /* common_block: error stmt_separator  */
#line 985 "parser_bison.y"
                        {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 7485 "parser_bison.c"
    break;

  case 34: /* line: common_block  */
#line 992 "parser_bison.y"
                                                                { (yyval.cmd) = NULL; }
#line 7491 "parser_bison.c"
    break;

  case 35: /* line: stmt_separator  */
#line 993 "parser_bison.y"
                                                                { (yyval.cmd) = NULL; }
#line 7497 "parser_bison.c"
    break;

  case 36: /* line: base_cmd stmt_separator  */
#line 994 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 7503 "parser_bison.c"
    break;

  case 37: /* line: base_cmd "end of file"  */
#line 996 "parser_bison.y"
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
#line 7525 "parser_bison.c"
    break;

  case 38: /* base_cmd: add_cmd  */
#line 1015 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7531 "parser_bison.c"
    break;

  case 39: /* base_cmd: "add" add_cmd  */
#line 1016 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7537 "parser_bison.c"
    break;

  case 40: /* base_cmd: "replace" replace_cmd  */
#line 1017 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7543 "parser_bison.c"
    break;

  case 41: /* base_cmd: "create" create_cmd  */
#line 1018 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7549 "parser_bison.c"
    break;

  case 42: /* base_cmd: "insert" insert_cmd  */
#line 1019 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7555 "parser_bison.c"
    break;

  case 43: /* base_cmd: "delete" delete_cmd  */
#line 1020 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7561 "parser_bison.c"
    break;

  case 44: /* base_cmd: "get" get_cmd  */
#line 1021 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7567 "parser_bison.c"
    break;

  case 45: /* base_cmd: "list" list_cmd close_scope_list  */
#line 1022 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 7573 "parser_bison.c"
    break;

  case 46: /* base_cmd: "reset" reset_cmd  */
#line 1023 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7579 "parser_bison.c"
    break;

  case 47: /* base_cmd: "flush" flush_cmd  */
#line 1024 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7585 "parser_bison.c"
    break;

  case 48: /* base_cmd: "rename" rename_cmd  */
#line 1025 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7591 "parser_bison.c"
    break;

  case 49: /* base_cmd: "import" import_cmd  */
#line 1026 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7597 "parser_bison.c"
    break;

  case 50: /* base_cmd: "export" export_cmd  */
#line 1027 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7603 "parser_bison.c"
    break;

  case 51: /* base_cmd: "monitor" monitor_cmd  */
#line 1028 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7609 "parser_bison.c"
    break;

  case 52: /* base_cmd: "describe" describe_cmd  */
#line 1029 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7615 "parser_bison.c"
    break;

  case 53: /* add_cmd: "table" table_spec  */
#line 1033 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7623 "parser_bison.c"
    break;

  case 54: /* add_cmd: "table" table_spec table_block_alloc '{' table_block '}'  */
#line 1038 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 7633 "parser_bison.c"
    break;

  case 55: /* add_cmd: "chain" chain_spec  */
#line 1044 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7641 "parser_bison.c"
    break;

  case 56: /* add_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1049 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 7652 "parser_bison.c"
    break;

  case 57: /* add_cmd: "rule" rule_position rule  */
#line 1056 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 7660 "parser_bison.c"
    break;

  case 58: /* add_cmd: rule_position rule  */
#line 1060 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 7668 "parser_bison.c"
    break;

  case 59: /* add_cmd: "set" set_spec set_block_alloc '{' set_block '}'  */
#line 1065 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 7678 "parser_bison.c"
    break;

  case 60: /* add_cmd: "map" set_spec map_block_alloc '{' map_block '}'  */
#line 1072 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 7688 "parser_bison.c"
    break;

  case 61: /* add_cmd: "element" set_spec set_block_expr  */
#line 1078 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 7696 "parser_bison.c"
    break;

  case 62: /* add_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1083 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 7706 "parser_bison.c"
    break;

  case 63: /* add_cmd: "counter" obj_spec close_scope_counter  */
#line 1089 "parser_bison.y"
                        {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 7719 "parser_bison.c"
    break;

  case 64: /* add_cmd: "counter" obj_spec counter_obj counter_config close_scope_counter  */
#line 1098 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7727 "parser_bison.c"
    break;

  case 65: /* add_cmd: "counter" obj_spec counter_obj '{' counter_block '}' close_scope_counter  */
#line 1102 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7735 "parser_bison.c"
    break;

  case 66: /* add_cmd: "quota" obj_spec quota_obj quota_config close_scope_quota  */
#line 1106 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7743 "parser_bison.c"
    break;

  case 67: /* add_cmd: "quota" obj_spec quota_obj '{' quota_block '}' close_scope_quota  */
#line 1110 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7751 "parser_bison.c"
    break;

  case 68: /* add_cmd: "ct" "helper" obj_spec ct_obj_alloc '{' ct_helper_block '}' close_scope_ct  */
#line 1114 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7759 "parser_bison.c"
    break;

  case 69: /* add_cmd: "ct" "timeout" obj_spec ct_obj_alloc '{' ct_timeout_block '}' close_scope_ct  */
#line 1118 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7767 "parser_bison.c"
    break;

  case 70: /* add_cmd: "ct" "expectation" obj_spec ct_obj_alloc '{' ct_expect_block '}' close_scope_ct  */
#line 1122 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7775 "parser_bison.c"
    break;

  case 71: /* add_cmd: "limit" obj_spec limit_obj limit_config close_scope_limit  */
#line 1126 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7783 "parser_bison.c"
    break;

  case 72: /* add_cmd: "limit" obj_spec limit_obj '{' limit_block '}' close_scope_limit  */
#line 1130 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7791 "parser_bison.c"
    break;

  case 73: /* add_cmd: "secmark" obj_spec secmark_obj secmark_config close_scope_secmark  */
#line 1134 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7799 "parser_bison.c"
    break;

  case 74: /* add_cmd: "secmark" obj_spec secmark_obj '{' secmark_block '}' close_scope_secmark  */
#line 1138 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7807 "parser_bison.c"
    break;

  case 75: /* add_cmd: "synproxy" obj_spec synproxy_obj synproxy_config  */
#line 1142 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 7815 "parser_bison.c"
    break;

  case 76: /* add_cmd: "synproxy" obj_spec synproxy_obj '{' synproxy_block '}'  */
#line 1146 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 7823 "parser_bison.c"
    break;

  case 77: /* replace_cmd: "rule" ruleid_spec rule  */
#line 1152 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 7831 "parser_bison.c"
    break;

  case 78: /* create_cmd: "table" table_spec  */
#line 1158 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7839 "parser_bison.c"
    break;

  case 79: /* create_cmd: "table" table_spec table_block_alloc '{' table_block '}'  */
#line 1163 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 7849 "parser_bison.c"
    break;

  case 80: /* create_cmd: "chain" chain_spec  */
#line 1169 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7857 "parser_bison.c"
    break;

  case 81: /* create_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1174 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 7868 "parser_bison.c"
    break;

  case 82: /* create_cmd: "set" set_spec set_block_alloc '{' set_block '}'  */
#line 1182 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 7878 "parser_bison.c"
    break;

  case 83: /* create_cmd: "map" set_spec map_block_alloc '{' map_block '}'  */
#line 1189 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 7888 "parser_bison.c"
    break;

  case 84: /* create_cmd: "element" set_spec set_block_expr  */
#line 1195 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 7896 "parser_bison.c"
    break;

  case 85: /* create_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1200 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 7906 "parser_bison.c"
    break;

  case 86: /* create_cmd: "counter" obj_spec close_scope_counter  */
#line 1206 "parser_bison.y"
                        {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 7919 "parser_bison.c"
    break;

  case 87: /* create_cmd: "counter" obj_spec counter_obj counter_config close_scope_counter  */
#line 1215 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7927 "parser_bison.c"
    break;

  case 88: /* create_cmd: "quota" obj_spec quota_obj quota_config close_scope_quota  */
#line 1219 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7935 "parser_bison.c"
    break;

  case 89: /* create_cmd: "ct" "helper" obj_spec ct_obj_alloc '{' ct_helper_block '}' close_scope_ct  */
#line 1223 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7943 "parser_bison.c"
    break;

  case 90: /* create_cmd: "ct" "timeout" obj_spec ct_obj_alloc '{' ct_timeout_block '}' close_scope_ct  */
#line 1227 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7951 "parser_bison.c"
    break;

  case 91: /* create_cmd: "ct" "expectation" obj_spec ct_obj_alloc '{' ct_expect_block '}' close_scope_ct  */
#line 1231 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7959 "parser_bison.c"
    break;

  case 92: /* create_cmd: "limit" obj_spec limit_obj limit_config close_scope_limit  */
#line 1235 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7967 "parser_bison.c"
    break;

  case 93: /* create_cmd: "secmark" obj_spec secmark_obj secmark_config close_scope_secmark  */
#line 1239 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7975 "parser_bison.c"
    break;

  case 94: /* create_cmd: "synproxy" obj_spec synproxy_obj synproxy_config  */
#line 1243 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 7983 "parser_bison.c"
    break;

  case 95: /* insert_cmd: "rule" rule_position rule  */
#line 1249 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 7991 "parser_bison.c"
    break;

  case 104: /* delete_cmd: "table" table_or_id_spec  */
#line 1271 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7999 "parser_bison.c"
    break;

  case 105: /* delete_cmd: "chain" chain_or_id_spec  */
#line 1275 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8007 "parser_bison.c"
    break;

  case 106: /* delete_cmd: "rule" ruleid_spec  */
#line 1279 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8015 "parser_bison.c"
    break;

  case 107: /* delete_cmd: "set" set_or_id_spec  */
#line 1283 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8023 "parser_bison.c"
    break;

  case 108: /* delete_cmd: "map" set_spec  */
#line 1287 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8031 "parser_bison.c"
    break;

  case 109: /* delete_cmd: "element" set_spec set_block_expr  */
#line 1291 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8039 "parser_bison.c"
    break;

  case 110: /* delete_cmd: "flowtable" flowtable_spec  */
#line 1295 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8047 "parser_bison.c"
    break;

  case 111: /* delete_cmd: "flowtable" flowtableid_spec  */
#line 1299 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8055 "parser_bison.c"
    break;

  case 112: /* delete_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1304 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8065 "parser_bison.c"
    break;

  case 113: /* delete_cmd: "counter" obj_or_id_spec close_scope_counter  */
#line 1310 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8073 "parser_bison.c"
    break;

  case 114: /* delete_cmd: "quota" obj_or_id_spec close_scope_quota  */
#line 1314 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8081 "parser_bison.c"
    break;

  case 115: /* delete_cmd: "ct" ct_obj_type obj_spec ct_obj_alloc close_scope_ct  */
#line 1318 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-3].val), &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
				if ((yyvsp[-3].val) == NFT_OBJECT_CT_TIMEOUT)
					init_list_head(&(yyvsp[-1].obj)->ct_timeout.timeout_list);
			}
#line 8091 "parser_bison.c"
    break;

  case 116: /* delete_cmd: "limit" obj_or_id_spec close_scope_limit  */
#line 1324 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8099 "parser_bison.c"
    break;

  case 117: /* delete_cmd: "secmark" obj_or_id_spec close_scope_secmark  */
#line 1328 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8107 "parser_bison.c"
    break;

  case 118: /* delete_cmd: "synproxy" obj_or_id_spec  */
#line 1332 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8115 "parser_bison.c"
    break;

  case 119: /* get_cmd: "element" set_spec set_block_expr  */
#line 1338 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8123 "parser_bison.c"
    break;

  case 120: /* list_cmd: "table" table_spec  */
#line 1344 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8131 "parser_bison.c"
    break;

  case 121: /* list_cmd: "tables" ruleset_spec  */
#line 1348 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8139 "parser_bison.c"
    break;

  case 122: /* list_cmd: "chain" chain_spec  */
#line 1352 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8147 "parser_bison.c"
    break;

  case 123: /* list_cmd: "chains" ruleset_spec  */
#line 1356 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8155 "parser_bison.c"
    break;

  case 124: /* list_cmd: "sets" ruleset_spec  */
#line 1360 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8163 "parser_bison.c"
    break;

  case 125: /* list_cmd: "sets" "table" table_spec  */
#line 1364 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8171 "parser_bison.c"
    break;

  case 126: /* list_cmd: "set" set_spec  */
#line 1368 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8179 "parser_bison.c"
    break;

  case 127: /* list_cmd: "counters" ruleset_spec  */
#line 1372 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8187 "parser_bison.c"
    break;

  case 128: /* list_cmd: "counters" "table" table_spec  */
#line 1376 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8195 "parser_bison.c"
    break;

  case 129: /* list_cmd: "counter" obj_spec close_scope_counter  */
#line 1380 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8203 "parser_bison.c"
    break;

  case 130: /* list_cmd: "quotas" ruleset_spec  */
#line 1384 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8211 "parser_bison.c"
    break;

  case 131: /* list_cmd: "quotas" "table" table_spec  */
#line 1388 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8219 "parser_bison.c"
    break;

  case 132: /* list_cmd: "quota" obj_spec close_scope_quota  */
#line 1392 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8227 "parser_bison.c"
    break;

  case 133: /* list_cmd: "limits" ruleset_spec  */
#line 1396 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8235 "parser_bison.c"
    break;

  case 134: /* list_cmd: "limits" "table" table_spec  */
#line 1400 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8243 "parser_bison.c"
    break;

  case 135: /* list_cmd: "limit" obj_spec close_scope_limit  */
#line 1404 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8251 "parser_bison.c"
    break;

  case 136: /* list_cmd: "secmarks" ruleset_spec  */
#line 1408 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8259 "parser_bison.c"
    break;

  case 137: /* list_cmd: "secmarks" "table" table_spec  */
#line 1412 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8267 "parser_bison.c"
    break;

  case 138: /* list_cmd: "secmark" obj_spec close_scope_secmark  */
#line 1416 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8275 "parser_bison.c"
    break;

  case 139: /* list_cmd: "synproxys" ruleset_spec  */
#line 1420 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8283 "parser_bison.c"
    break;

  case 140: /* list_cmd: "synproxys" "table" table_spec  */
#line 1424 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8291 "parser_bison.c"
    break;

  case 141: /* list_cmd: "synproxy" obj_spec  */
#line 1428 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8299 "parser_bison.c"
    break;

  case 142: /* list_cmd: "ruleset" ruleset_spec  */
#line 1432 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8307 "parser_bison.c"
    break;

  case 143: /* list_cmd: "flow" "tables" ruleset_spec  */
#line 1436 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8315 "parser_bison.c"
    break;

  case 144: /* list_cmd: "flow" "table" set_spec  */
#line 1440 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8323 "parser_bison.c"
    break;

  case 145: /* list_cmd: "meters" ruleset_spec  */
#line 1444 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8331 "parser_bison.c"
    break;

  case 146: /* list_cmd: "meter" set_spec  */
#line 1448 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8339 "parser_bison.c"
    break;

  case 147: /* list_cmd: "flowtables" ruleset_spec  */
#line 1452 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8347 "parser_bison.c"
    break;

  case 148: /* list_cmd: "flowtable" flowtable_spec  */
#line 1456 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8355 "parser_bison.c"
    break;

  case 149: /* list_cmd: "maps" ruleset_spec  */
#line 1460 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8363 "parser_bison.c"
    break;

  case 150: /* list_cmd: "map" set_spec  */
#line 1464 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8371 "parser_bison.c"
    break;

  case 151: /* list_cmd: "ct" ct_obj_type obj_spec close_scope_ct  */
#line 1468 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8379 "parser_bison.c"
    break;

  case 152: /* list_cmd: "ct" ct_cmd_type "table" table_spec close_scope_ct  */
#line 1472 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, (yyvsp[-3].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8387 "parser_bison.c"
    break;

  case 153: /* list_cmd: "hooks" basehook_spec  */
#line 1476 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_HOOKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8395 "parser_bison.c"
    break;

  case 154: /* basehook_device_name: "device" "string"  */
#line 1482 "parser_bison.y"
                        {
				(yyval.string) = (yyvsp[0].string);
			}
#line 8403 "parser_bison.c"
    break;

  case 155: /* basehook_spec: ruleset_spec  */
#line 1488 "parser_bison.y"
                        {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 8411 "parser_bison.c"
    break;

  case 156: /* basehook_spec: ruleset_spec basehook_device_name  */
#line 1492 "parser_bison.y"
                        {
				if ((yyvsp[0].string)) {
					(yyvsp[-1].handle).obj.name = (yyvsp[0].string);
					(yyvsp[-1].handle).obj.location = (yylsp[0]);
				}
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8423 "parser_bison.c"
    break;

  case 157: /* reset_cmd: "counters" ruleset_spec  */
#line 1502 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8431 "parser_bison.c"
    break;

  case 158: /* reset_cmd: "counters" "table" table_spec  */
#line 1506 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8439 "parser_bison.c"
    break;

  case 159: /* reset_cmd: "counter" obj_spec close_scope_counter  */
#line 1510 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[-1].handle),&(yyloc), NULL);
			}
#line 8447 "parser_bison.c"
    break;

  case 160: /* reset_cmd: "quotas" ruleset_spec  */
#line 1514 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8455 "parser_bison.c"
    break;

  case 161: /* reset_cmd: "quotas" "table" table_spec  */
#line 1518 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8463 "parser_bison.c"
    break;

  case 162: /* reset_cmd: "quota" obj_spec close_scope_quota  */
#line 1522 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8471 "parser_bison.c"
    break;

  case 163: /* flush_cmd: "table" table_spec  */
#line 1528 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8479 "parser_bison.c"
    break;

  case 164: /* flush_cmd: "chain" chain_spec  */
#line 1532 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8487 "parser_bison.c"
    break;

  case 165: /* flush_cmd: "set" set_spec  */
#line 1536 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8495 "parser_bison.c"
    break;

  case 166: /* flush_cmd: "map" set_spec  */
#line 1540 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8503 "parser_bison.c"
    break;

  case 167: /* flush_cmd: "flow" "table" set_spec  */
#line 1544 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8511 "parser_bison.c"
    break;

  case 168: /* flush_cmd: "meter" set_spec  */
#line 1548 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8519 "parser_bison.c"
    break;

  case 169: /* flush_cmd: "ruleset" ruleset_spec  */
#line 1552 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8527 "parser_bison.c"
    break;

  case 170: /* rename_cmd: "chain" chain_spec identifier  */
#line 1558 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 8536 "parser_bison.c"
    break;

  case 171: /* import_cmd: "ruleset" markup_format  */
#line 1565 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 8546 "parser_bison.c"
    break;

  case 172: /* import_cmd: markup_format  */
#line 1571 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 8556 "parser_bison.c"
    break;

  case 173: /* export_cmd: "ruleset" markup_format  */
#line 1579 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 8566 "parser_bison.c"
    break;

  case 174: /* export_cmd: markup_format  */
#line 1585 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 8576 "parser_bison.c"
    break;

  case 175: /* monitor_cmd: monitor_event monitor_object monitor_format  */
#line 1593 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 8587 "parser_bison.c"
    break;

  case 176: /* monitor_event: %empty  */
#line 1601 "parser_bison.y"
                                                { (yyval.string) = NULL; }
#line 8593 "parser_bison.c"
    break;

  case 177: /* monitor_event: "string"  */
#line 1602 "parser_bison.y"
                                                { (yyval.string) = (yyvsp[0].string); }
#line 8599 "parser_bison.c"
    break;

  case 178: /* monitor_object: %empty  */
#line 1605 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 8605 "parser_bison.c"
    break;

  case 179: /* monitor_object: "tables"  */
#line 1606 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 8611 "parser_bison.c"
    break;

  case 180: /* monitor_object: "chains"  */
#line 1607 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 8617 "parser_bison.c"
    break;

  case 181: /* monitor_object: "sets"  */
#line 1608 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 8623 "parser_bison.c"
    break;

  case 182: /* monitor_object: "rules"  */
#line 1609 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 8629 "parser_bison.c"
    break;

  case 183: /* monitor_object: "elements"  */
#line 1610 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 8635 "parser_bison.c"
    break;

  case 184: /* monitor_object: "ruleset"  */
#line 1611 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 8641 "parser_bison.c"
    break;

  case 185: /* monitor_object: "trace"  */
#line 1612 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 8647 "parser_bison.c"
    break;

  case 186: /* monitor_format: %empty  */
#line 1615 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 8653 "parser_bison.c"
    break;

  case 188: /* markup_format: "xml"  */
#line 1619 "parser_bison.y"
                                                { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 8659 "parser_bison.c"
    break;

  case 189: /* markup_format: "json"  */
#line 1620 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 8665 "parser_bison.c"
    break;

  case 190: /* markup_format: "vm" "json"  */
#line 1621 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 8671 "parser_bison.c"
    break;

  case 191: /* describe_cmd: primary_expr  */
#line 1625 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 8681 "parser_bison.c"
    break;

  case 192: /* table_block_alloc: %empty  */
#line 1633 "parser_bison.y"
                        {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 8690 "parser_bison.c"
    break;

  case 193: /* table_options: "flags" "string"  */
#line 1640 "parser_bison.y"
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
#line 8709 "parser_bison.c"
    break;

  case 194: /* table_options: comment_spec  */
#line 1655 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].table)->comment, &(yyloc), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].table)->comment = (yyvsp[0].string);
			}
#line 8721 "parser_bison.c"
    break;

  case 195: /* table_block: %empty  */
#line 1664 "parser_bison.y"
                                                { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 8727 "parser_bison.c"
    break;

  case 199: /* table_block: table_block "chain" chain_identifier chain_block_alloc '{' chain_block '}' stmt_separator  */
#line 1671 "parser_bison.y"
                        {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 8740 "parser_bison.c"
    break;

  case 200: /* table_block: table_block "set" set_identifier set_block_alloc '{' set_block '}' stmt_separator  */
#line 1682 "parser_bison.y"
                        {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 8752 "parser_bison.c"
    break;

  case 201: /* table_block: table_block "map" set_identifier map_block_alloc '{' map_block '}' stmt_separator  */
#line 1692 "parser_bison.y"
                        {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 8764 "parser_bison.c"
    break;

  case 202: /* table_block: table_block "flowtable" flowtable_identifier flowtable_block_alloc '{' flowtable_block '}' stmt_separator  */
#line 1703 "parser_bison.y"
                        {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 8776 "parser_bison.c"
    break;

  case 203: /* table_block: table_block "counter" obj_identifier obj_block_alloc '{' counter_block '}' stmt_separator close_scope_counter  */
#line 1713 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 8789 "parser_bison.c"
    break;

  case 204: /* table_block: table_block "quota" obj_identifier obj_block_alloc '{' quota_block '}' stmt_separator close_scope_quota  */
#line 1724 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 8802 "parser_bison.c"
    break;

  case 205: /* table_block: table_block "ct" "helper" obj_identifier obj_block_alloc '{' ct_helper_block '}' close_scope_ct stmt_separator  */
#line 1733 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 8815 "parser_bison.c"
    break;

  case 206: /* table_block: table_block "ct" "timeout" obj_identifier obj_block_alloc '{' ct_timeout_block '}' close_scope_ct stmt_separator  */
#line 1742 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 8828 "parser_bison.c"
    break;

  case 207: /* table_block: table_block "ct" "expectation" obj_identifier obj_block_alloc '{' ct_expect_block '}' close_scope_ct stmt_separator  */
#line 1751 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 8841 "parser_bison.c"
    break;

  case 208: /* table_block: table_block "limit" obj_identifier obj_block_alloc '{' limit_block '}' stmt_separator close_scope_limit  */
#line 1762 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 8854 "parser_bison.c"
    break;

  case 209: /* table_block: table_block "secmark" obj_identifier obj_block_alloc '{' secmark_block '}' stmt_separator close_scope_secmark  */
#line 1773 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 8867 "parser_bison.c"
    break;

  case 210: /* table_block: table_block "synproxy" obj_identifier obj_block_alloc '{' synproxy_block '}' stmt_separator  */
#line 1784 "parser_bison.y"
                        {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 8880 "parser_bison.c"
    break;

  case 211: /* chain_block_alloc: %empty  */
#line 1795 "parser_bison.y"
                        {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 8889 "parser_bison.c"
    break;

  case 212: /* chain_block: %empty  */
#line 1801 "parser_bison.y"
                                                { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 8895 "parser_bison.c"
    break;

  case 218: /* chain_block: chain_block rule stmt_separator  */
#line 1808 "parser_bison.y"
                        {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 8904 "parser_bison.c"
    break;

  case 219: /* chain_block: chain_block comment_spec stmt_separator  */
#line 1813 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].chain)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].chain)->comment = (yyvsp[-1].string);
			}
#line 8916 "parser_bison.c"
    break;

  case 220: /* subchain_block: %empty  */
#line 1822 "parser_bison.y"
                                                { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 8922 "parser_bison.c"
    break;

  case 222: /* subchain_block: subchain_block rule stmt_separator  */
#line 1825 "parser_bison.y"
                        {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 8931 "parser_bison.c"
    break;

  case 223: /* typeof_data_expr: primary_expr  */
#line 1832 "parser_bison.y"
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
#line 8956 "parser_bison.c"
    break;

  case 224: /* typeof_data_expr: typeof_expr "." primary_expr  */
#line 1853 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 8969 "parser_bison.c"
    break;

  case 225: /* typeof_expr: primary_expr  */
#line 1864 "parser_bison.y"
                        {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8984 "parser_bison.c"
    break;

  case 226: /* typeof_expr: typeof_expr "." primary_expr  */
#line 1875 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 8997 "parser_bison.c"
    break;

  case 227: /* set_block_alloc: %empty  */
#line 1887 "parser_bison.y"
                        {
				(yyval.set) = set_alloc(NULL);
			}
#line 9005 "parser_bison.c"
    break;

  case 228: /* set_block: %empty  */
#line 1892 "parser_bison.y"
                                                { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 9011 "parser_bison.c"
    break;

  case 231: /* set_block: set_block "type" data_type_expr stmt_separator  */
#line 1896 "parser_bison.y"
                        {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9020 "parser_bison.c"
    break;

  case 232: /* set_block: set_block "typeof" typeof_expr stmt_separator  */
#line 1901 "parser_bison.y"
                        {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9030 "parser_bison.c"
    break;

  case 233: /* set_block: set_block "flags" set_flag_list stmt_separator  */
#line 1907 "parser_bison.y"
                        {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9039 "parser_bison.c"
    break;

  case 234: /* set_block: set_block "timeout" time_spec stmt_separator  */
#line 1912 "parser_bison.y"
                        {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9048 "parser_bison.c"
    break;

  case 235: /* set_block: set_block "gc-interval" time_spec stmt_separator  */
#line 1917 "parser_bison.y"
                        {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9057 "parser_bison.c"
    break;

  case 236: /* set_block: set_block stateful_stmt_list stmt_separator  */
#line 1922 "parser_bison.y"
                        {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 9067 "parser_bison.c"
    break;

  case 237: /* set_block: set_block "elements" '=' set_block_expr  */
#line 1928 "parser_bison.y"
                        {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9076 "parser_bison.c"
    break;

  case 238: /* set_block: set_block "auto-merge"  */
#line 1933 "parser_bison.y"
                        {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 9085 "parser_bison.c"
    break;

  case 240: /* set_block: set_block comment_spec stmt_separator  */
#line 1939 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 9098 "parser_bison.c"
    break;

  case 243: /* set_flag_list: set_flag_list "comma" set_flag  */
#line 1954 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9106 "parser_bison.c"
    break;

  case 245: /* set_flag: "constant"  */
#line 1960 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_CONSTANT; }
#line 9112 "parser_bison.c"
    break;

  case 246: /* set_flag: "interval"  */
#line 1961 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_INTERVAL; }
#line 9118 "parser_bison.c"
    break;

  case 247: /* set_flag: "timeout"  */
#line 1962 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_TIMEOUT; }
#line 9124 "parser_bison.c"
    break;

  case 248: /* set_flag: "dynamic"  */
#line 1963 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_EVAL; }
#line 9130 "parser_bison.c"
    break;

  case 249: /* map_block_alloc: %empty  */
#line 1967 "parser_bison.y"
                        {
				(yyval.set) = set_alloc(NULL);
			}
#line 9138 "parser_bison.c"
    break;

  case 250: /* map_block_obj_type: "counter" close_scope_counter  */
#line 1972 "parser_bison.y"
                                                            { (yyval.val) = NFT_OBJECT_COUNTER; }
#line 9144 "parser_bison.c"
    break;

  case 251: /* map_block_obj_type: "quota" close_scope_quota  */
#line 1973 "parser_bison.y"
                                                          { (yyval.val) = NFT_OBJECT_QUOTA; }
#line 9150 "parser_bison.c"
    break;

  case 252: /* map_block_obj_type: "limit" close_scope_limit  */
#line 1974 "parser_bison.y"
                                                          { (yyval.val) = NFT_OBJECT_LIMIT; }
#line 9156 "parser_bison.c"
    break;

  case 253: /* map_block_obj_type: "secmark" close_scope_secmark  */
#line 1975 "parser_bison.y"
                                                            { (yyval.val) = NFT_OBJECT_SECMARK; }
#line 9162 "parser_bison.c"
    break;

  case 254: /* map_block: %empty  */
#line 1978 "parser_bison.y"
                                                { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 9168 "parser_bison.c"
    break;

  case 257: /* map_block: map_block "timeout" time_spec stmt_separator  */
#line 1982 "parser_bison.y"
                        {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9177 "parser_bison.c"
    break;

  case 258: /* map_block: map_block "type" data_type_expr "colon" data_type_expr stmt_separator  */
#line 1989 "parser_bison.y"
                        {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 9189 "parser_bison.c"
    break;

  case 259: /* map_block: map_block "type" data_type_expr "colon" "interval" data_type_expr stmt_separator  */
#line 1999 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 9202 "parser_bison.c"
    break;

  case 260: /* map_block: map_block "typeof" typeof_expr "colon" typeof_data_expr stmt_separator  */
#line 2010 "parser_bison.y"
                        {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 9215 "parser_bison.c"
    break;

  case 261: /* map_block: map_block "typeof" typeof_expr "colon" "interval" typeof_expr stmt_separator  */
#line 2021 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				datatype_set((yyvsp[-6].set)->key, (yyvsp[-4].expr)->dtype);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 9229 "parser_bison.c"
    break;

  case 262: /* map_block: map_block "type" data_type_expr "colon" map_block_obj_type stmt_separator  */
#line 2033 "parser_bison.y"
                        {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = (yyvsp[-1].val);
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 9240 "parser_bison.c"
    break;

  case 263: /* map_block: map_block "flags" set_flag_list stmt_separator  */
#line 2040 "parser_bison.y"
                        {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9249 "parser_bison.c"
    break;

  case 264: /* map_block: map_block stateful_stmt_list stmt_separator  */
#line 2045 "parser_bison.y"
                        {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 9259 "parser_bison.c"
    break;

  case 265: /* map_block: map_block "elements" '=' set_block_expr  */
#line 2051 "parser_bison.y"
                        {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9268 "parser_bison.c"
    break;

  case 266: /* map_block: map_block comment_spec stmt_separator  */
#line 2056 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 9281 "parser_bison.c"
    break;

  case 268: /* set_mechanism: "policy" set_policy_spec  */
#line 2068 "parser_bison.y"
                        {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 9289 "parser_bison.c"
    break;

  case 269: /* set_mechanism: "size" "number"  */
#line 2072 "parser_bison.y"
                        {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 9297 "parser_bison.c"
    break;

  case 270: /* set_policy_spec: "performance"  */
#line 2077 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 9303 "parser_bison.c"
    break;

  case 271: /* set_policy_spec: "memory"  */
#line 2078 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 9309 "parser_bison.c"
    break;

  case 272: /* flowtable_block_alloc: %empty  */
#line 2082 "parser_bison.y"
                        {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 9317 "parser_bison.c"
    break;

  case 273: /* flowtable_block: %empty  */
#line 2087 "parser_bison.y"
                                                { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 9323 "parser_bison.c"
    break;

  case 276: /* flowtable_block: flowtable_block "hook" "string" prio_spec stmt_separator  */
#line 2091 "parser_bison.y"
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
#line 9341 "parser_bison.c"
    break;

  case 277: /* flowtable_block: flowtable_block "devices" '=' flowtable_expr stmt_separator  */
#line 2105 "parser_bison.y"
                        {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 9349 "parser_bison.c"
    break;

  case 278: /* flowtable_block: flowtable_block "counter" close_scope_counter  */
#line 2109 "parser_bison.y"
                        {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 9357 "parser_bison.c"
    break;

  case 279: /* flowtable_block: flowtable_block "flags" "offload" stmt_separator  */
#line 2113 "parser_bison.y"
                        {
				(yyval.flowtable)->flags |= FLOWTABLE_F_HW_OFFLOAD;
			}
#line 9365 "parser_bison.c"
    break;

  case 280: /* flowtable_expr: '{' flowtable_list_expr '}'  */
#line 2119 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9374 "parser_bison.c"
    break;

  case 281: /* flowtable_expr: variable_expr  */
#line 2124 "parser_bison.y"
                        {
				(yyvsp[0].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 9383 "parser_bison.c"
    break;

  case 282: /* flowtable_list_expr: flowtable_expr_member  */
#line 2131 "parser_bison.y"
                        {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9392 "parser_bison.c"
    break;

  case 283: /* flowtable_list_expr: flowtable_list_expr "comma" flowtable_expr_member  */
#line 2136 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9401 "parser_bison.c"
    break;

  case 285: /* flowtable_expr_member: "string"  */
#line 2144 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9412 "parser_bison.c"
    break;

  case 286: /* flowtable_expr_member: variable_expr  */
#line 2151 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 9421 "parser_bison.c"
    break;

  case 287: /* data_type_atom_expr: type_identifier  */
#line 2158 "parser_bison.y"
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
#line 9438 "parser_bison.c"
    break;

  case 288: /* data_type_atom_expr: "time"  */
#line 2171 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 9447 "parser_bison.c"
    break;

  case 290: /* data_type_expr: data_type_expr "." data_type_atom_expr  */
#line 2179 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 9460 "parser_bison.c"
    break;

  case 291: /* obj_block_alloc: %empty  */
#line 2190 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 9468 "parser_bison.c"
    break;

  case 292: /* counter_block: %empty  */
#line 2195 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9474 "parser_bison.c"
    break;

  case 295: /* counter_block: counter_block counter_config  */
#line 2199 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9482 "parser_bison.c"
    break;

  case 296: /* counter_block: counter_block comment_spec  */
#line 2203 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9494 "parser_bison.c"
    break;

  case 297: /* quota_block: %empty  */
#line 2212 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9500 "parser_bison.c"
    break;

  case 300: /* quota_block: quota_block quota_config  */
#line 2216 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9508 "parser_bison.c"
    break;

  case 301: /* quota_block: quota_block comment_spec  */
#line 2220 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9520 "parser_bison.c"
    break;

  case 302: /* ct_helper_block: %empty  */
#line 2229 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9526 "parser_bison.c"
    break;

  case 305: /* ct_helper_block: ct_helper_block ct_helper_config  */
#line 2233 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9534 "parser_bison.c"
    break;

  case 306: /* ct_helper_block: ct_helper_block comment_spec  */
#line 2237 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9546 "parser_bison.c"
    break;

  case 307: /* ct_timeout_block: %empty  */
#line 2247 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[(-1) - (0)].obj);
				init_list_head(&(yyval.obj)->ct_timeout.timeout_list);
			}
#line 9555 "parser_bison.c"
    break;

  case 310: /* ct_timeout_block: ct_timeout_block ct_timeout_config  */
#line 2254 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9563 "parser_bison.c"
    break;

  case 311: /* ct_timeout_block: ct_timeout_block comment_spec  */
#line 2258 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9575 "parser_bison.c"
    break;

  case 312: /* ct_expect_block: %empty  */
#line 2267 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9581 "parser_bison.c"
    break;

  case 315: /* ct_expect_block: ct_expect_block ct_expect_config  */
#line 2271 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9589 "parser_bison.c"
    break;

  case 316: /* ct_expect_block: ct_expect_block comment_spec  */
#line 2275 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9601 "parser_bison.c"
    break;

  case 317: /* limit_block: %empty  */
#line 2284 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9607 "parser_bison.c"
    break;

  case 320: /* limit_block: limit_block limit_config  */
#line 2288 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9615 "parser_bison.c"
    break;

  case 321: /* limit_block: limit_block comment_spec  */
#line 2292 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9627 "parser_bison.c"
    break;

  case 322: /* secmark_block: %empty  */
#line 2301 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9633 "parser_bison.c"
    break;

  case 325: /* secmark_block: secmark_block secmark_config  */
#line 2305 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9641 "parser_bison.c"
    break;

  case 326: /* secmark_block: secmark_block comment_spec  */
#line 2309 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9653 "parser_bison.c"
    break;

  case 327: /* synproxy_block: %empty  */
#line 2318 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9659 "parser_bison.c"
    break;

  case 330: /* synproxy_block: synproxy_block synproxy_config  */
#line 2322 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9667 "parser_bison.c"
    break;

  case 331: /* synproxy_block: synproxy_block comment_spec  */
#line 2326 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9679 "parser_bison.c"
    break;

  case 332: /* type_identifier: "string"  */
#line 2335 "parser_bison.y"
                                        { (yyval.string) = (yyvsp[0].string); }
#line 9685 "parser_bison.c"
    break;

  case 333: /* type_identifier: "mark"  */
#line 2336 "parser_bison.y"
                                        { (yyval.string) = xstrdup("mark"); }
#line 9691 "parser_bison.c"
    break;

  case 334: /* type_identifier: "dscp"  */
#line 2337 "parser_bison.y"
                                        { (yyval.string) = xstrdup("dscp"); }
#line 9697 "parser_bison.c"
    break;

  case 335: /* type_identifier: "ecn"  */
#line 2338 "parser_bison.y"
                                        { (yyval.string) = xstrdup("ecn"); }
#line 9703 "parser_bison.c"
    break;

  case 336: /* type_identifier: "classid"  */
#line 2339 "parser_bison.y"
                                        { (yyval.string) = xstrdup("classid"); }
#line 9709 "parser_bison.c"
    break;

  case 337: /* hook_spec: "type" "string" "hook" "string" dev_spec prio_spec  */
#line 2343 "parser_bison.y"
                        {
				const char *chain_type = chain_type_name_lookup((yyvsp[-4].string));

				if (chain_type == NULL) {
					erec_queue(error(&(yylsp[-4]), "unknown chain type"),
						   state->msgs);
					xfree((yyvsp[-4].string));
					YYERROR;
				}
				(yyvsp[-6].chain)->type.loc = (yylsp[-4]);
				(yyvsp[-6].chain)->type.str = xstrdup(chain_type);
				xfree((yyvsp[-4].string));

				(yyvsp[-6].chain)->loc = (yyloc);
				(yyvsp[-6].chain)->hook.loc = (yylsp[-2]);
				(yyvsp[-6].chain)->hook.name = chain_hookname_lookup((yyvsp[-2].string));
				if ((yyvsp[-6].chain)->hook.name == NULL) {
					erec_queue(error(&(yylsp[-2]), "unknown chain hook"),
						   state->msgs);
					xfree((yyvsp[-2].string));
					YYERROR;
				}
				xfree((yyvsp[-2].string));

				(yyvsp[-6].chain)->dev_expr	= (yyvsp[-1].expr);
				(yyvsp[-6].chain)->priority	= (yyvsp[0].prio_spec);
				(yyvsp[-6].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
#line 9742 "parser_bison.c"
    break;

  case 338: /* prio_spec: "priority" extended_prio_spec  */
#line 2374 "parser_bison.y"
                        {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 9751 "parser_bison.c"
    break;

  case 339: /* extended_prio_name: "out"  */
#line 2381 "parser_bison.y"
                        {
				(yyval.string) = strdup("out");
			}
#line 9759 "parser_bison.c"
    break;

  case 341: /* extended_prio_spec: int_num  */
#line 2388 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 9773 "parser_bison.c"
    break;

  case 342: /* extended_prio_spec: variable_expr  */
#line 2398 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 9784 "parser_bison.c"
    break;

  case 343: /* extended_prio_spec: extended_prio_name  */
#line 2405 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 9799 "parser_bison.c"
    break;

  case 344: /* extended_prio_spec: extended_prio_name "+" "number"  */
#line 2416 "parser_bison.y"
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
#line 9816 "parser_bison.c"
    break;

  case 345: /* extended_prio_spec: extended_prio_name "-" "number"  */
#line 2429 "parser_bison.y"
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
#line 9833 "parser_bison.c"
    break;

  case 346: /* int_num: "number"  */
#line 2443 "parser_bison.y"
                                                        { (yyval.val32) = (yyvsp[0].val); }
#line 9839 "parser_bison.c"
    break;

  case 347: /* int_num: "-" "number"  */
#line 2444 "parser_bison.y"
                                                        { (yyval.val32) = -(yyvsp[0].val); }
#line 9845 "parser_bison.c"
    break;

  case 348: /* dev_spec: "device" string  */
#line 2448 "parser_bison.y"
                        {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 9861 "parser_bison.c"
    break;

  case 349: /* dev_spec: "device" variable_expr  */
#line 2460 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9871 "parser_bison.c"
    break;

  case 350: /* dev_spec: "devices" '=' flowtable_expr  */
#line 2466 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 9879 "parser_bison.c"
    break;

  case 351: /* dev_spec: %empty  */
#line 2469 "parser_bison.y"
                                                        { (yyval.expr) = NULL; }
#line 9885 "parser_bison.c"
    break;

  case 352: /* flags_spec: "flags" "offload"  */
#line 2473 "parser_bison.y"
                        {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 9893 "parser_bison.c"
    break;

  case 353: /* policy_spec: "policy" policy_expr  */
#line 2479 "parser_bison.y"
                        {
				if ((yyvsp[-2].chain)->policy) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}
				(yyvsp[-2].chain)->policy		= (yyvsp[0].expr);
				(yyvsp[-2].chain)->policy->location	= (yyloc);
			}
#line 9908 "parser_bison.c"
    break;

  case 354: /* policy_expr: variable_expr  */
#line 2492 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 9917 "parser_bison.c"
    break;

  case 355: /* policy_expr: chain_policy  */
#line 2497 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 9928 "parser_bison.c"
    break;

  case 356: /* chain_policy: "accept"  */
#line 2505 "parser_bison.y"
                                                { (yyval.val32) = NF_ACCEPT; }
#line 9934 "parser_bison.c"
    break;

  case 357: /* chain_policy: "drop"  */
#line 2506 "parser_bison.y"
                                                { (yyval.val32) = NF_DROP;   }
#line 9940 "parser_bison.c"
    break;

  case 362: /* time_spec: "string"  */
#line 2518 "parser_bison.y"
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
#line 9957 "parser_bison.c"
    break;

  case 363: /* family_spec: %empty  */
#line 2532 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV4; }
#line 9963 "parser_bison.c"
    break;

  case 365: /* family_spec_explicit: "ip" close_scope_ip  */
#line 2536 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV4; }
#line 9969 "parser_bison.c"
    break;

  case 366: /* family_spec_explicit: "ip6" close_scope_ip6  */
#line 2537 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV6; }
#line 9975 "parser_bison.c"
    break;

  case 367: /* family_spec_explicit: "inet"  */
#line 2538 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_INET; }
#line 9981 "parser_bison.c"
    break;

  case 368: /* family_spec_explicit: "arp" close_scope_arp  */
#line 2539 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_ARP; }
#line 9987 "parser_bison.c"
    break;

  case 369: /* family_spec_explicit: "bridge"  */
#line 2540 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_BRIDGE; }
#line 9993 "parser_bison.c"
    break;

  case 370: /* family_spec_explicit: "netdev"  */
#line 2541 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_NETDEV; }
#line 9999 "parser_bison.c"
    break;

  case 371: /* table_spec: family_spec identifier  */
#line 2545 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 10010 "parser_bison.c"
    break;

  case 372: /* tableid_spec: family_spec "handle" "number"  */
#line 2554 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 10021 "parser_bison.c"
    break;

  case 373: /* chain_spec: table_spec identifier  */
#line 2563 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 10031 "parser_bison.c"
    break;

  case 374: /* chainid_spec: table_spec "handle" "number"  */
#line 2571 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 10041 "parser_bison.c"
    break;

  case 375: /* chain_identifier: identifier  */
#line 2579 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 10051 "parser_bison.c"
    break;

  case 376: /* set_spec: table_spec identifier  */
#line 2587 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 10061 "parser_bison.c"
    break;

  case 377: /* setid_spec: table_spec "handle" "number"  */
#line 2595 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 10071 "parser_bison.c"
    break;

  case 378: /* set_identifier: identifier  */
#line 2603 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 10081 "parser_bison.c"
    break;

  case 379: /* flowtable_spec: table_spec identifier  */
#line 2611 "parser_bison.y"
                        {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 10091 "parser_bison.c"
    break;

  case 380: /* flowtableid_spec: table_spec "handle" "number"  */
#line 2619 "parser_bison.y"
                        {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 10101 "parser_bison.c"
    break;

  case 381: /* flowtable_identifier: identifier  */
#line 2627 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 10111 "parser_bison.c"
    break;

  case 382: /* obj_spec: table_spec identifier  */
#line 2635 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 10121 "parser_bison.c"
    break;

  case 383: /* objid_spec: table_spec "handle" "number"  */
#line 2643 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 10131 "parser_bison.c"
    break;

  case 384: /* obj_identifier: identifier  */
#line 2651 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 10141 "parser_bison.c"
    break;

  case 385: /* handle_spec: "handle" "number"  */
#line 2659 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 10151 "parser_bison.c"
    break;

  case 386: /* position_spec: "position" "number"  */
#line 2667 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 10161 "parser_bison.c"
    break;

  case 387: /* index_spec: "index" "number"  */
#line 2675 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 10171 "parser_bison.c"
    break;

  case 388: /* rule_position: chain_spec  */
#line 2683 "parser_bison.y"
                        {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 10179 "parser_bison.c"
    break;

  case 389: /* rule_position: chain_spec position_spec  */
#line 2687 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 10188 "parser_bison.c"
    break;

  case 390: /* rule_position: chain_spec handle_spec  */
#line 2692 "parser_bison.y"
                        {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 10200 "parser_bison.c"
    break;

  case 391: /* rule_position: chain_spec index_spec  */
#line 2700 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 10209 "parser_bison.c"
    break;

  case 392: /* ruleid_spec: chain_spec handle_spec  */
#line 2707 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 10218 "parser_bison.c"
    break;

  case 393: /* comment_spec: "comment" string  */
#line 2714 "parser_bison.y"
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
#line 10233 "parser_bison.c"
    break;

  case 394: /* ruleset_spec: %empty  */
#line 2727 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 10242 "parser_bison.c"
    break;

  case 395: /* ruleset_spec: family_spec_explicit  */
#line 2732 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 10251 "parser_bison.c"
    break;

  case 396: /* rule: rule_alloc  */
#line 2739 "parser_bison.y"
                        {
				(yyval.rule)->comment = NULL;
			}
#line 10259 "parser_bison.c"
    break;

  case 397: /* rule: rule_alloc comment_spec  */
#line 2743 "parser_bison.y"
                        {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 10267 "parser_bison.c"
    break;

  case 398: /* rule_alloc: stmt_list  */
#line 2749 "parser_bison.y"
                        {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 10281 "parser_bison.c"
    break;

  case 399: /* stmt_list: stmt  */
#line 2761 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 10291 "parser_bison.c"
    break;

  case 400: /* stmt_list: stmt_list stmt  */
#line 2767 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 10300 "parser_bison.c"
    break;

  case 401: /* stateful_stmt_list: stateful_stmt  */
#line 2774 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 10310 "parser_bison.c"
    break;

  case 402: /* stateful_stmt_list: stateful_stmt_list stateful_stmt  */
#line 2780 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 10319 "parser_bison.c"
    break;

  case 427: /* chain_stmt_type: "jump"  */
#line 2814 "parser_bison.y"
                                        { (yyval.val) = NFT_JUMP; }
#line 10325 "parser_bison.c"
    break;

  case 428: /* chain_stmt_type: "goto"  */
#line 2815 "parser_bison.y"
                                        { (yyval.val) = NFT_GOTO; }
#line 10331 "parser_bison.c"
    break;

  case 429: /* chain_stmt: chain_stmt_type chain_block_alloc '{' subchain_block '}'  */
#line 2819 "parser_bison.y"
                        {
				(yyvsp[-3].chain)->location = (yylsp[-3]);
				close_scope(state);
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				(yyval.stmt) = chain_stmt_alloc(&(yyloc), (yyvsp[-1].chain), (yyvsp[-4].val));
			}
#line 10342 "parser_bison.c"
    break;

  case 430: /* verdict_stmt: verdict_expr  */
#line 2828 "parser_bison.y"
                        {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 10350 "parser_bison.c"
    break;

  case 431: /* verdict_stmt: verdict_map_stmt  */
#line 2832 "parser_bison.y"
                        {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 10358 "parser_bison.c"
    break;

  case 432: /* verdict_map_stmt: concat_expr "vmap" verdict_map_expr  */
#line 2838 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10366 "parser_bison.c"
    break;

  case 433: /* verdict_map_expr: '{' verdict_map_list_expr '}'  */
#line 2844 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10375 "parser_bison.c"
    break;

  case 435: /* verdict_map_list_expr: verdict_map_list_member_expr  */
#line 2852 "parser_bison.y"
                        {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10384 "parser_bison.c"
    break;

  case 436: /* verdict_map_list_expr: verdict_map_list_expr "comma" verdict_map_list_member_expr  */
#line 2857 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10393 "parser_bison.c"
    break;

  case 438: /* verdict_map_list_member_expr: opt_newline set_elem_expr "colon" verdict_expr opt_newline  */
#line 2865 "parser_bison.y"
                        {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 10401 "parser_bison.c"
    break;

  case 439: /* connlimit_stmt: "ct" "count" "number" close_scope_ct  */
#line 2871 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 10410 "parser_bison.c"
    break;

  case 440: /* connlimit_stmt: "ct" "count" "over" "number" close_scope_ct  */
#line 2876 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 10420 "parser_bison.c"
    break;

  case 443: /* counter_stmt_alloc: "counter"  */
#line 2887 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 10428 "parser_bison.c"
    break;

  case 444: /* counter_stmt_alloc: "counter" "name" stmt_expr  */
#line 2891 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 10438 "parser_bison.c"
    break;

  case 445: /* counter_args: counter_arg  */
#line 2899 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10446 "parser_bison.c"
    break;

  case 447: /* counter_arg: "packets" "number"  */
#line 2906 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 10454 "parser_bison.c"
    break;

  case 448: /* counter_arg: "bytes" "number"  */
#line 2910 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 10462 "parser_bison.c"
    break;

  case 451: /* log_stmt_alloc: "log"  */
#line 2920 "parser_bison.y"
                        {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 10470 "parser_bison.c"
    break;

  case 452: /* log_args: log_arg  */
#line 2926 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10478 "parser_bison.c"
    break;

  case 454: /* log_arg: "prefix" string  */
#line 2933 "parser_bison.y"
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
#line 10607 "parser_bison.c"
    break;

  case 455: /* log_arg: "group" "number"  */
#line 3058 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 10616 "parser_bison.c"
    break;

  case 456: /* log_arg: "snaplen" "number"  */
#line 3063 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 10625 "parser_bison.c"
    break;

  case 457: /* log_arg: "queue-threshold" "number"  */
#line 3068 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 10634 "parser_bison.c"
    break;

  case 458: /* log_arg: "level" level_type  */
#line 3073 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 10643 "parser_bison.c"
    break;

  case 459: /* log_arg: "flags" log_flags  */
#line 3078 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 10651 "parser_bison.c"
    break;

  case 460: /* level_type: string  */
#line 3084 "parser_bison.y"
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
#line 10683 "parser_bison.c"
    break;

  case 461: /* log_flags: "tcp" log_flags_tcp  */
#line 3114 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[0].val);
			}
#line 10691 "parser_bison.c"
    break;

  case 462: /* log_flags: "ip" "options" close_scope_ip  */
#line 3118 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 10699 "parser_bison.c"
    break;

  case 463: /* log_flags: "skuid"  */
#line 3122 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_UID;
			}
#line 10707 "parser_bison.c"
    break;

  case 464: /* log_flags: "ether" close_scope_eth  */
#line 3126 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 10715 "parser_bison.c"
    break;

  case 465: /* log_flags: "all"  */
#line 3130 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_MASK;
			}
#line 10723 "parser_bison.c"
    break;

  case 466: /* log_flags_tcp: log_flags_tcp "comma" log_flag_tcp  */
#line 3136 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10731 "parser_bison.c"
    break;

  case 468: /* log_flag_tcp: "seq"  */
#line 3143 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 10739 "parser_bison.c"
    break;

  case 469: /* log_flag_tcp: "options"  */
#line 3147 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 10747 "parser_bison.c"
    break;

  case 470: /* limit_stmt: "limit" "rate" limit_mode limit_rate_pkts limit_burst_pkts close_scope_limit  */
#line 3153 "parser_bison.y"
                        {
				if ((yyvsp[-1].val) == 0) {
					erec_queue(error(&(yylsp[-1]), "limit burst must be > 0"),
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
#line 10765 "parser_bison.c"
    break;

  case 471: /* limit_stmt: "limit" "rate" limit_mode limit_rate_bytes limit_burst_bytes close_scope_limit  */
#line 3167 "parser_bison.y"
                        {
				if ((yyvsp[-1].val) == 0) {
					erec_queue(error(&(yylsp[-1]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-2].limit_rate).rate;
				(yyval.stmt)->limit.unit	= (yyvsp[-2].limit_rate).unit;
				(yyval.stmt)->limit.burst	= (yyvsp[-1].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKT_BYTES;
				(yyval.stmt)->limit.flags = (yyvsp[-3].val);
			}
#line 10783 "parser_bison.c"
    break;

  case 472: /* limit_stmt: "limit" "name" stmt_expr close_scope_limit  */
#line 3181 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 10793 "parser_bison.c"
    break;

  case 473: /* quota_mode: "over"  */
#line 3188 "parser_bison.y"
                                                { (yyval.val) = NFT_QUOTA_F_INV; }
#line 10799 "parser_bison.c"
    break;

  case 474: /* quota_mode: "until"  */
#line 3189 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 10805 "parser_bison.c"
    break;

  case 475: /* quota_mode: %empty  */
#line 3190 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 10811 "parser_bison.c"
    break;

  case 476: /* quota_unit: "bytes"  */
#line 3193 "parser_bison.y"
                                                { (yyval.string) = xstrdup("bytes"); }
#line 10817 "parser_bison.c"
    break;

  case 477: /* quota_unit: "string"  */
#line 3194 "parser_bison.y"
                                                { (yyval.string) = (yyvsp[0].string); }
#line 10823 "parser_bison.c"
    break;

  case 478: /* quota_used: %empty  */
#line 3197 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 10829 "parser_bison.c"
    break;

  case 479: /* quota_used: "used" "number" quota_unit  */
#line 3199 "parser_bison.y"
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
#line 10846 "parser_bison.c"
    break;

  case 480: /* quota_stmt: "quota" quota_mode "number" quota_unit quota_used close_scope_quota  */
#line 3214 "parser_bison.y"
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
#line 10866 "parser_bison.c"
    break;

  case 481: /* quota_stmt: "quota" "name" stmt_expr close_scope_quota  */
#line 3230 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 10876 "parser_bison.c"
    break;

  case 482: /* limit_mode: "over"  */
#line 3237 "parser_bison.y"
                                                                { (yyval.val) = NFT_LIMIT_F_INV; }
#line 10882 "parser_bison.c"
    break;

  case 483: /* limit_mode: "until"  */
#line 3238 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 10888 "parser_bison.c"
    break;

  case 484: /* limit_mode: %empty  */
#line 3239 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 10894 "parser_bison.c"
    break;

  case 485: /* limit_burst_pkts: %empty  */
#line 3242 "parser_bison.y"
                                                                { (yyval.val) = 5; }
#line 10900 "parser_bison.c"
    break;

  case 486: /* limit_burst_pkts: "burst" "number" "packets"  */
#line 3243 "parser_bison.y"
                                                                { (yyval.val) = (yyvsp[-1].val); }
#line 10906 "parser_bison.c"
    break;

  case 487: /* limit_rate_pkts: "number" "/" time_unit  */
#line 3247 "parser_bison.y"
                        {
				(yyval.limit_rate).rate = (yyvsp[-2].val);
				(yyval.limit_rate).unit = (yyvsp[0].val);
			}
#line 10915 "parser_bison.c"
    break;

  case 488: /* limit_burst_bytes: %empty  */
#line 3253 "parser_bison.y"
                                                                { (yyval.val) = 5; }
#line 10921 "parser_bison.c"
    break;

  case 489: /* limit_burst_bytes: "burst" limit_bytes  */
#line 3254 "parser_bison.y"
                                                                { (yyval.val) = (yyvsp[0].val); }
#line 10927 "parser_bison.c"
    break;

  case 490: /* limit_rate_bytes: "number" "string"  */
#line 3258 "parser_bison.y"
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
#line 10945 "parser_bison.c"
    break;

  case 491: /* limit_rate_bytes: limit_bytes "/" time_unit  */
#line 3272 "parser_bison.y"
                        {
				(yyval.limit_rate).rate = (yyvsp[-2].val);
				(yyval.limit_rate).unit = (yyvsp[0].val);
			}
#line 10954 "parser_bison.c"
    break;

  case 492: /* limit_bytes: "number" "bytes"  */
#line 3278 "parser_bison.y"
                                                        { (yyval.val) = (yyvsp[-1].val); }
#line 10960 "parser_bison.c"
    break;

  case 493: /* limit_bytes: "number" "string"  */
#line 3280 "parser_bison.y"
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
#line 10977 "parser_bison.c"
    break;

  case 494: /* time_unit: "second"  */
#line 3294 "parser_bison.y"
                                                { (yyval.val) = 1ULL; }
#line 10983 "parser_bison.c"
    break;

  case 495: /* time_unit: "minute"  */
#line 3295 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60; }
#line 10989 "parser_bison.c"
    break;

  case 496: /* time_unit: "hour"  */
#line 3296 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60; }
#line 10995 "parser_bison.c"
    break;

  case 497: /* time_unit: "day"  */
#line 3297 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 11001 "parser_bison.c"
    break;

  case 498: /* time_unit: "week"  */
#line 3298 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 11007 "parser_bison.c"
    break;

  case 500: /* reject_stmt_alloc: "reject"  */
#line 3305 "parser_bison.y"
                        {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 11015 "parser_bison.c"
    break;

  case 501: /* reject_with_expr: "string"  */
#line 3311 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state), (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 11025 "parser_bison.c"
    break;

  case 502: /* reject_with_expr: integer_expr  */
#line 3316 "parser_bison.y"
                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11031 "parser_bison.c"
    break;

  case 503: /* reject_opts: %empty  */
#line 3320 "parser_bison.y"
                        {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 11040 "parser_bison.c"
    break;

  case 504: /* reject_opts: "with" "icmp" "type" reject_with_expr  */
#line 3325 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmp_code_type);
			}
#line 11051 "parser_bison.c"
    break;

  case 505: /* reject_opts: "with" "icmp" reject_with_expr  */
#line 3332 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmp_code_type);
			}
#line 11062 "parser_bison.c"
    break;

  case 506: /* reject_opts: "with" "icmpv6" "type" reject_with_expr  */
#line 3339 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 11073 "parser_bison.c"
    break;

  case 507: /* reject_opts: "with" "icmpv6" reject_with_expr  */
#line 3346 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 11084 "parser_bison.c"
    break;

  case 508: /* reject_opts: "with" "icmpx" "type" reject_with_expr  */
#line 3353 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpx_code_type);
			}
#line 11094 "parser_bison.c"
    break;

  case 509: /* reject_opts: "with" "icmpx" reject_with_expr  */
#line 3359 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpx_code_type);
			}
#line 11104 "parser_bison.c"
    break;

  case 510: /* reject_opts: "with" "tcp" "reset"  */
#line 3365 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 11112 "parser_bison.c"
    break;

  case 512: /* nat_stmt_alloc: "snat"  */
#line 3373 "parser_bison.y"
                                        { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 11118 "parser_bison.c"
    break;

  case 513: /* nat_stmt_alloc: "dnat"  */
#line 3374 "parser_bison.y"
                                        { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 11124 "parser_bison.c"
    break;

  case 514: /* tproxy_stmt: "tproxy" "to" stmt_expr  */
#line 3378 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 11134 "parser_bison.c"
    break;

  case 515: /* tproxy_stmt: "tproxy" nf_key_proto "to" stmt_expr  */
#line 3384 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 11144 "parser_bison.c"
    break;

  case 516: /* tproxy_stmt: "tproxy" "to" "colon" stmt_expr  */
#line 3390 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 11154 "parser_bison.c"
    break;

  case 517: /* tproxy_stmt: "tproxy" "to" stmt_expr "colon" stmt_expr  */
#line 3396 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 11165 "parser_bison.c"
    break;

  case 518: /* tproxy_stmt: "tproxy" nf_key_proto "to" stmt_expr "colon" stmt_expr  */
#line 3403 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 11176 "parser_bison.c"
    break;

  case 519: /* tproxy_stmt: "tproxy" nf_key_proto "to" "colon" stmt_expr  */
#line 3410 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 11186 "parser_bison.c"
    break;

  case 522: /* synproxy_stmt_alloc: "synproxy"  */
#line 3422 "parser_bison.y"
                        {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 11194 "parser_bison.c"
    break;

  case 523: /* synproxy_stmt_alloc: "synproxy" "name" stmt_expr  */
#line 3426 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 11204 "parser_bison.c"
    break;

  case 524: /* synproxy_args: synproxy_arg  */
#line 3434 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 11212 "parser_bison.c"
    break;

  case 526: /* synproxy_arg: "mss" "number"  */
#line 3441 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 11221 "parser_bison.c"
    break;

  case 527: /* synproxy_arg: "wscale" "number"  */
#line 3446 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 11230 "parser_bison.c"
    break;

  case 528: /* synproxy_arg: "timestamp"  */
#line 3451 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 11238 "parser_bison.c"
    break;

  case 529: /* synproxy_arg: "sack-permitted"  */
#line 3455 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 11246 "parser_bison.c"
    break;

  case 530: /* synproxy_config: "mss" "number" "wscale" "number" synproxy_ts synproxy_sack  */
#line 3461 "parser_bison.y"
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
#line 11266 "parser_bison.c"
    break;

  case 531: /* synproxy_config: "mss" "number" stmt_separator "wscale" "number" stmt_separator synproxy_ts synproxy_sack  */
#line 3477 "parser_bison.y"
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
#line 11286 "parser_bison.c"
    break;

  case 532: /* synproxy_obj: %empty  */
#line 3495 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 11295 "parser_bison.c"
    break;

  case 533: /* synproxy_ts: %empty  */
#line 3501 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11301 "parser_bison.c"
    break;

  case 534: /* synproxy_ts: "timestamp"  */
#line 3503 "parser_bison.y"
                        {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 11309 "parser_bison.c"
    break;

  case 535: /* synproxy_sack: %empty  */
#line 3508 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11315 "parser_bison.c"
    break;

  case 536: /* synproxy_sack: "sack-permitted"  */
#line 3510 "parser_bison.y"
                        {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 11323 "parser_bison.c"
    break;

  case 537: /* primary_stmt_expr: symbol_expr  */
#line 3515 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11329 "parser_bison.c"
    break;

  case 538: /* primary_stmt_expr: integer_expr  */
#line 3516 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11335 "parser_bison.c"
    break;

  case 539: /* primary_stmt_expr: boolean_expr  */
#line 3517 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11341 "parser_bison.c"
    break;

  case 540: /* primary_stmt_expr: meta_expr  */
#line 3518 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11347 "parser_bison.c"
    break;

  case 541: /* primary_stmt_expr: rt_expr  */
#line 3519 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11353 "parser_bison.c"
    break;

  case 542: /* primary_stmt_expr: ct_expr  */
#line 3520 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11359 "parser_bison.c"
    break;

  case 543: /* primary_stmt_expr: numgen_expr  */
#line 3521 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11365 "parser_bison.c"
    break;

  case 544: /* primary_stmt_expr: hash_expr  */
#line 3522 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11371 "parser_bison.c"
    break;

  case 545: /* primary_stmt_expr: payload_expr  */
#line 3523 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11377 "parser_bison.c"
    break;

  case 546: /* primary_stmt_expr: keyword_expr  */
#line 3524 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11383 "parser_bison.c"
    break;

  case 547: /* primary_stmt_expr: socket_expr  */
#line 3525 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11389 "parser_bison.c"
    break;

  case 548: /* primary_stmt_expr: osf_expr  */
#line 3526 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11395 "parser_bison.c"
    break;

  case 549: /* primary_stmt_expr: '(' basic_stmt_expr ')'  */
#line 3527 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 11401 "parser_bison.c"
    break;

  case 551: /* shift_stmt_expr: shift_stmt_expr "<<" primary_stmt_expr  */
#line 3532 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11409 "parser_bison.c"
    break;

  case 552: /* shift_stmt_expr: shift_stmt_expr ">>" primary_stmt_expr  */
#line 3536 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11417 "parser_bison.c"
    break;

  case 554: /* and_stmt_expr: and_stmt_expr "&" shift_stmt_expr  */
#line 3543 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11425 "parser_bison.c"
    break;

  case 556: /* exclusive_or_stmt_expr: exclusive_or_stmt_expr "^" and_stmt_expr  */
#line 3550 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11433 "parser_bison.c"
    break;

  case 558: /* inclusive_or_stmt_expr: inclusive_or_stmt_expr '|' exclusive_or_stmt_expr  */
#line 3557 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11441 "parser_bison.c"
    break;

  case 561: /* concat_stmt_expr: concat_stmt_expr "." primary_stmt_expr  */
#line 3567 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 11454 "parser_bison.c"
    break;

  case 564: /* map_stmt_expr: concat_stmt_expr "map" map_stmt_expr_set  */
#line 3582 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11462 "parser_bison.c"
    break;

  case 565: /* map_stmt_expr: concat_stmt_expr  */
#line 3585 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 11468 "parser_bison.c"
    break;

  case 566: /* prefix_stmt_expr: basic_stmt_expr "/" "number"  */
#line 3589 "parser_bison.y"
                        {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 11476 "parser_bison.c"
    break;

  case 567: /* range_stmt_expr: basic_stmt_expr "-" basic_stmt_expr  */
#line 3595 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11484 "parser_bison.c"
    break;

  case 573: /* nat_stmt_args: stmt_expr  */
#line 3610 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 11492 "parser_bison.c"
    break;

  case 574: /* nat_stmt_args: "to" stmt_expr  */
#line 3614 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 11500 "parser_bison.c"
    break;

  case 575: /* nat_stmt_args: nf_key_proto "to" stmt_expr  */
#line 3618 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 11509 "parser_bison.c"
    break;

  case 576: /* nat_stmt_args: stmt_expr "colon" stmt_expr  */
#line 3623 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11518 "parser_bison.c"
    break;

  case 577: /* nat_stmt_args: "to" stmt_expr "colon" stmt_expr  */
#line 3628 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11527 "parser_bison.c"
    break;

  case 578: /* nat_stmt_args: nf_key_proto "to" stmt_expr "colon" stmt_expr  */
#line 3633 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11537 "parser_bison.c"
    break;

  case 579: /* nat_stmt_args: "colon" stmt_expr  */
#line 3639 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11545 "parser_bison.c"
    break;

  case 580: /* nat_stmt_args: "to" "colon" stmt_expr  */
#line 3643 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11553 "parser_bison.c"
    break;

  case 581: /* nat_stmt_args: nat_stmt_args nf_nat_flags  */
#line 3647 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 11561 "parser_bison.c"
    break;

  case 582: /* nat_stmt_args: nf_key_proto "addr" "." "port" "to" stmt_expr  */
#line 3651 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.type_flags = STMT_NAT_F_CONCAT;
			}
#line 11571 "parser_bison.c"
    break;

  case 583: /* nat_stmt_args: nf_key_proto "interval" "to" stmt_expr  */
#line 3657 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 11580 "parser_bison.c"
    break;

  case 584: /* nat_stmt_args: "interval" "to" stmt_expr  */
#line 3662 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 11588 "parser_bison.c"
    break;

  case 585: /* nat_stmt_args: nf_key_proto "prefix" "to" stmt_expr  */
#line 3666 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-4].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 11600 "parser_bison.c"
    break;

  case 586: /* nat_stmt_args: "prefix" "to" stmt_expr  */
#line 3674 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-3].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 11611 "parser_bison.c"
    break;

  case 589: /* masq_stmt_alloc: "masquerade"  */
#line 3686 "parser_bison.y"
                                                { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 11617 "parser_bison.c"
    break;

  case 590: /* masq_stmt_args: "to" "colon" stmt_expr  */
#line 3690 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11625 "parser_bison.c"
    break;

  case 591: /* masq_stmt_args: "to" "colon" stmt_expr nf_nat_flags  */
#line 3694 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 11634 "parser_bison.c"
    break;

  case 592: /* masq_stmt_args: nf_nat_flags  */
#line 3699 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 11642 "parser_bison.c"
    break;

  case 595: /* redir_stmt_alloc: "redirect"  */
#line 3708 "parser_bison.y"
                                                { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 11648 "parser_bison.c"
    break;

  case 596: /* redir_stmt_arg: "to" stmt_expr  */
#line 3712 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11656 "parser_bison.c"
    break;

  case 597: /* redir_stmt_arg: "to" "colon" stmt_expr  */
#line 3716 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11664 "parser_bison.c"
    break;

  case 598: /* redir_stmt_arg: nf_nat_flags  */
#line 3720 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 11672 "parser_bison.c"
    break;

  case 599: /* redir_stmt_arg: "to" stmt_expr nf_nat_flags  */
#line 3724 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 11681 "parser_bison.c"
    break;

  case 600: /* redir_stmt_arg: "to" "colon" stmt_expr nf_nat_flags  */
#line 3729 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 11690 "parser_bison.c"
    break;

  case 601: /* dup_stmt: "dup" "to" stmt_expr  */
#line 3736 "parser_bison.y"
                        {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 11699 "parser_bison.c"
    break;

  case 602: /* dup_stmt: "dup" "to" stmt_expr "device" stmt_expr  */
#line 3741 "parser_bison.y"
                        {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 11709 "parser_bison.c"
    break;

  case 603: /* fwd_stmt: "fwd" "to" stmt_expr  */
#line 3749 "parser_bison.y"
                        {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 11718 "parser_bison.c"
    break;

  case 604: /* fwd_stmt: "fwd" nf_key_proto "to" stmt_expr "device" stmt_expr  */
#line 3754 "parser_bison.y"
                        {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 11729 "parser_bison.c"
    break;

  case 606: /* nf_nat_flags: nf_nat_flags "comma" nf_nat_flag  */
#line 3764 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 11737 "parser_bison.c"
    break;

  case 607: /* nf_nat_flag: "random"  */
#line 3769 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 11743 "parser_bison.c"
    break;

  case 608: /* nf_nat_flag: "fully-random"  */
#line 3770 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 11749 "parser_bison.c"
    break;

  case 609: /* nf_nat_flag: "persistent"  */
#line 3771 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 11755 "parser_bison.c"
    break;

  case 611: /* queue_stmt: "queue" "to" queue_stmt_expr close_scope_queue  */
#line 3776 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), 0);
			}
#line 11763 "parser_bison.c"
    break;

  case 612: /* queue_stmt: "queue" "flags" queue_stmt_flags "to" queue_stmt_expr close_scope_queue  */
#line 3780 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 11771 "parser_bison.c"
    break;

  case 613: /* queue_stmt: "queue" "flags" queue_stmt_flags "num" queue_stmt_expr_simple close_scope_queue  */
#line 3784 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 11779 "parser_bison.c"
    break;

  case 616: /* queue_stmt_alloc: "queue"  */
#line 3794 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), NULL, 0);
			}
#line 11787 "parser_bison.c"
    break;

  case 617: /* queue_stmt_args: queue_stmt_arg  */
#line 3800 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 11795 "parser_bison.c"
    break;

  case 619: /* queue_stmt_arg: "num" queue_stmt_expr_simple  */
#line 3807 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 11804 "parser_bison.c"
    break;

  case 620: /* queue_stmt_arg: queue_stmt_flags  */
#line 3812 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 11812 "parser_bison.c"
    break;

  case 625: /* queue_stmt_expr_simple: queue_expr "-" queue_expr  */
#line 3824 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11820 "parser_bison.c"
    break;

  case 631: /* queue_stmt_flags: queue_stmt_flags "comma" queue_stmt_flag  */
#line 3837 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 11828 "parser_bison.c"
    break;

  case 632: /* queue_stmt_flag: "bypass"  */
#line 3842 "parser_bison.y"
                                        { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 11834 "parser_bison.c"
    break;

  case 633: /* queue_stmt_flag: "fanout"  */
#line 3843 "parser_bison.y"
                                        { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 11840 "parser_bison.c"
    break;

  case 636: /* set_elem_expr_stmt_alloc: concat_expr  */
#line 3851 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 11848 "parser_bison.c"
    break;

  case 637: /* set_stmt: "set" set_stmt_op set_elem_expr_stmt set_ref_expr  */
#line 3857 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 11859 "parser_bison.c"
    break;

  case 638: /* set_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt '}'  */
#line 3864 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 11870 "parser_bison.c"
    break;

  case 639: /* set_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt stateful_stmt_list '}'  */
#line 3871 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				list_splice_tail((yyvsp[-1].list), &(yyval.stmt)->set.stmt_list);
				free((yyvsp[-1].list));
			}
#line 11883 "parser_bison.c"
    break;

  case 640: /* set_stmt_op: "add"  */
#line 3881 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 11889 "parser_bison.c"
    break;

  case 641: /* set_stmt_op: "update"  */
#line 3882 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 11895 "parser_bison.c"
    break;

  case 642: /* set_stmt_op: "delete"  */
#line 3883 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 11901 "parser_bison.c"
    break;

  case 643: /* map_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt "colon" set_elem_expr_stmt '}'  */
#line 3887 "parser_bison.y"
                        {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 11913 "parser_bison.c"
    break;

  case 644: /* map_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt stateful_stmt_list "colon" set_elem_expr_stmt '}'  */
#line 3895 "parser_bison.y"
                        {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
				list_splice_tail((yyvsp[-3].list), &(yyval.stmt)->map.stmt_list);
				free((yyvsp[-3].list));
			}
#line 11927 "parser_bison.c"
    break;

  case 645: /* meter_stmt: flow_stmt_legacy_alloc flow_stmt_opts '{' meter_key_expr stmt '}'  */
#line 3907 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 11938 "parser_bison.c"
    break;

  case 646: /* meter_stmt: meter_stmt_alloc  */
#line 3913 "parser_bison.y"
                                                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 11944 "parser_bison.c"
    break;

  case 647: /* flow_stmt_legacy_alloc: "flow"  */
#line 3917 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 11952 "parser_bison.c"
    break;

  case 648: /* flow_stmt_opts: flow_stmt_opt  */
#line 3923 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 11960 "parser_bison.c"
    break;

  case 650: /* flow_stmt_opt: "table" identifier  */
#line 3930 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 11968 "parser_bison.c"
    break;

  case 651: /* meter_stmt_alloc: "meter" identifier '{' meter_key_expr stmt '}'  */
#line 3936 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 11981 "parser_bison.c"
    break;

  case 652: /* meter_stmt_alloc: "meter" identifier "size" "number" '{' meter_key_expr stmt '}'  */
#line 3945 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 11994 "parser_bison.c"
    break;

  case 653: /* match_stmt: relational_expr  */
#line 3956 "parser_bison.y"
                        {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 12002 "parser_bison.c"
    break;

  case 654: /* variable_expr: '$' identifier  */
#line 3962 "parser_bison.y"
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
#line 12030 "parser_bison.c"
    break;

  case 656: /* symbol_expr: string  */
#line 3989 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 12041 "parser_bison.c"
    break;

  case 659: /* set_ref_symbol_expr: "@" identifier  */
#line 4002 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 12052 "parser_bison.c"
    break;

  case 660: /* integer_expr: "number"  */
#line 4011 "parser_bison.y"
                        {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 12065 "parser_bison.c"
    break;

  case 661: /* primary_expr: symbol_expr  */
#line 4021 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12071 "parser_bison.c"
    break;

  case 662: /* primary_expr: integer_expr  */
#line 4022 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12077 "parser_bison.c"
    break;

  case 663: /* primary_expr: payload_expr  */
#line 4023 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12083 "parser_bison.c"
    break;

  case 664: /* primary_expr: exthdr_expr  */
#line 4024 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12089 "parser_bison.c"
    break;

  case 665: /* primary_expr: exthdr_exists_expr  */
#line 4025 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12095 "parser_bison.c"
    break;

  case 666: /* primary_expr: meta_expr  */
#line 4026 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12101 "parser_bison.c"
    break;

  case 667: /* primary_expr: socket_expr  */
#line 4027 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12107 "parser_bison.c"
    break;

  case 668: /* primary_expr: rt_expr  */
#line 4028 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12113 "parser_bison.c"
    break;

  case 669: /* primary_expr: ct_expr  */
#line 4029 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12119 "parser_bison.c"
    break;

  case 670: /* primary_expr: numgen_expr  */
#line 4030 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12125 "parser_bison.c"
    break;

  case 671: /* primary_expr: hash_expr  */
#line 4031 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12131 "parser_bison.c"
    break;

  case 672: /* primary_expr: fib_expr  */
#line 4032 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12137 "parser_bison.c"
    break;

  case 673: /* primary_expr: osf_expr  */
#line 4033 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12143 "parser_bison.c"
    break;

  case 674: /* primary_expr: xfrm_expr  */
#line 4034 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12149 "parser_bison.c"
    break;

  case 675: /* primary_expr: '(' basic_expr ')'  */
#line 4035 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 12155 "parser_bison.c"
    break;

  case 676: /* fib_expr: "fib" fib_tuple fib_result close_scope_fib  */
#line 4039 "parser_bison.y"
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
#line 12180 "parser_bison.c"
    break;

  case 677: /* fib_result: "oif"  */
#line 4061 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 12186 "parser_bison.c"
    break;

  case 678: /* fib_result: "oifname"  */
#line 4062 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 12192 "parser_bison.c"
    break;

  case 679: /* fib_result: "type"  */
#line 4063 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 12198 "parser_bison.c"
    break;

  case 680: /* fib_flag: "saddr"  */
#line 4066 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 12204 "parser_bison.c"
    break;

  case 681: /* fib_flag: "daddr"  */
#line 4067 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 12210 "parser_bison.c"
    break;

  case 682: /* fib_flag: "mark"  */
#line 4068 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_MARK; }
#line 12216 "parser_bison.c"
    break;

  case 683: /* fib_flag: "iif"  */
#line 4069 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_IIF; }
#line 12222 "parser_bison.c"
    break;

  case 684: /* fib_flag: "oif"  */
#line 4070 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_OIF; }
#line 12228 "parser_bison.c"
    break;

  case 685: /* fib_tuple: fib_flag "." fib_tuple  */
#line 4074 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 12236 "parser_bison.c"
    break;

  case 687: /* osf_expr: "osf" osf_ttl "version"  */
#line 4081 "parser_bison.y"
                        {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), NFT_OSF_F_VERSION);
			}
#line 12244 "parser_bison.c"
    break;

  case 688: /* osf_expr: "osf" osf_ttl "name"  */
#line 4085 "parser_bison.y"
                        {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 12252 "parser_bison.c"
    break;

  case 689: /* osf_ttl: %empty  */
#line 4091 "parser_bison.y"
                        {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 12260 "parser_bison.c"
    break;

  case 690: /* osf_ttl: "ttl" "string"  */
#line 4095 "parser_bison.y"
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
#line 12278 "parser_bison.c"
    break;

  case 692: /* shift_expr: shift_expr "<<" primary_rhs_expr  */
#line 4112 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12286 "parser_bison.c"
    break;

  case 693: /* shift_expr: shift_expr ">>" primary_rhs_expr  */
#line 4116 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12294 "parser_bison.c"
    break;

  case 695: /* and_expr: and_expr "&" shift_rhs_expr  */
#line 4123 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12302 "parser_bison.c"
    break;

  case 697: /* exclusive_or_expr: exclusive_or_expr "^" and_rhs_expr  */
#line 4130 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12310 "parser_bison.c"
    break;

  case 699: /* inclusive_or_expr: inclusive_or_expr '|' exclusive_or_rhs_expr  */
#line 4137 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12318 "parser_bison.c"
    break;

  case 702: /* concat_expr: concat_expr "." basic_expr  */
#line 4147 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 12331 "parser_bison.c"
    break;

  case 703: /* prefix_rhs_expr: basic_rhs_expr "/" "number"  */
#line 4158 "parser_bison.y"
                        {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 12339 "parser_bison.c"
    break;

  case 704: /* range_rhs_expr: basic_rhs_expr "-" basic_rhs_expr  */
#line 4164 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12347 "parser_bison.c"
    break;

  case 707: /* map_expr: concat_expr "map" rhs_expr  */
#line 4174 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12355 "parser_bison.c"
    break;

  case 711: /* set_expr: '{' set_list_expr '}'  */
#line 4185 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 12364 "parser_bison.c"
    break;

  case 712: /* set_list_expr: set_list_member_expr  */
#line 4192 "parser_bison.y"
                        {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 12373 "parser_bison.c"
    break;

  case 713: /* set_list_expr: set_list_expr "comma" set_list_member_expr  */
#line 4197 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 12382 "parser_bison.c"
    break;

  case 715: /* set_list_member_expr: opt_newline set_expr opt_newline  */
#line 4205 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 12390 "parser_bison.c"
    break;

  case 716: /* set_list_member_expr: opt_newline set_elem_expr opt_newline  */
#line 4209 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 12398 "parser_bison.c"
    break;

  case 717: /* set_list_member_expr: opt_newline set_elem_expr "colon" set_rhs_expr opt_newline  */
#line 4213 "parser_bison.y"
                        {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 12406 "parser_bison.c"
    break;

  case 719: /* meter_key_expr: meter_key_expr_alloc set_elem_options  */
#line 4220 "parser_bison.y"
                        {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 12415 "parser_bison.c"
    break;

  case 720: /* meter_key_expr_alloc: concat_expr  */
#line 4227 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 12423 "parser_bison.c"
    break;

  case 723: /* set_elem_key_expr: set_lhs_expr  */
#line 4236 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 12429 "parser_bison.c"
    break;

  case 724: /* set_elem_key_expr: "*"  */
#line 4237 "parser_bison.y"
                                                        { (yyval.expr) = set_elem_catchall_expr_alloc(&(yylsp[0])); }
#line 12435 "parser_bison.c"
    break;

  case 725: /* set_elem_expr_alloc: set_elem_key_expr set_elem_stmt_list  */
#line 4241 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[-1]), (yyvsp[-1].expr));
				list_splice_tail((yyvsp[0].list), &(yyval.expr)->stmt_list);
				xfree((yyvsp[0].list));
			}
#line 12445 "parser_bison.c"
    break;

  case 726: /* set_elem_expr_alloc: set_elem_key_expr  */
#line 4247 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 12453 "parser_bison.c"
    break;

  case 727: /* set_elem_options: set_elem_option  */
#line 4253 "parser_bison.y"
                        {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 12461 "parser_bison.c"
    break;

  case 729: /* set_elem_option: "timeout" time_spec  */
#line 4260 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 12469 "parser_bison.c"
    break;

  case 730: /* set_elem_option: "expires" time_spec  */
#line 4264 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 12477 "parser_bison.c"
    break;

  case 731: /* set_elem_option: comment_spec  */
#line 4268 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 12489 "parser_bison.c"
    break;

  case 732: /* set_elem_expr_options: set_elem_expr_option  */
#line 4278 "parser_bison.y"
                        {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 12497 "parser_bison.c"
    break;

  case 734: /* set_elem_stmt_list: set_elem_stmt  */
#line 4285 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 12507 "parser_bison.c"
    break;

  case 735: /* set_elem_stmt_list: set_elem_stmt_list set_elem_stmt  */
#line 4291 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 12516 "parser_bison.c"
    break;

  case 736: /* set_elem_stmt: "counter" close_scope_counter  */
#line 4298 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 12524 "parser_bison.c"
    break;

  case 737: /* set_elem_stmt: "counter" "packets" "number" "bytes" "number" close_scope_counter  */
#line 4302 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
				(yyval.stmt)->counter.packets = (yyvsp[-3].val);
				(yyval.stmt)->counter.bytes = (yyvsp[-1].val);
			}
#line 12534 "parser_bison.c"
    break;

  case 738: /* set_elem_stmt: "limit" "rate" limit_mode limit_rate_pkts limit_burst_pkts close_scope_limit  */
#line 4308 "parser_bison.y"
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
#line 12552 "parser_bison.c"
    break;

  case 739: /* set_elem_stmt: "limit" "rate" limit_mode limit_rate_bytes limit_burst_bytes close_scope_limit  */
#line 4322 "parser_bison.y"
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
#line 12570 "parser_bison.c"
    break;

  case 740: /* set_elem_stmt: "ct" "count" "number" close_scope_ct  */
#line 4336 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 12579 "parser_bison.c"
    break;

  case 741: /* set_elem_stmt: "ct" "count" "over" "number" close_scope_ct  */
#line 4341 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 12589 "parser_bison.c"
    break;

  case 742: /* set_elem_expr_option: "timeout" time_spec  */
#line 4349 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 12597 "parser_bison.c"
    break;

  case 743: /* set_elem_expr_option: "expires" time_spec  */
#line 4353 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 12605 "parser_bison.c"
    break;

  case 744: /* set_elem_expr_option: comment_spec  */
#line 4357 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 12617 "parser_bison.c"
    break;

  case 750: /* initializer_expr: '{' '}'  */
#line 4375 "parser_bison.y"
                                                { (yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_SET); }
#line 12623 "parser_bison.c"
    break;

  case 751: /* initializer_expr: "-" "number"  */
#line 4377 "parser_bison.y"
                        {
				int32_t num = -(yyvsp[0].val);

				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(num) * BITS_PER_BYTE,
							 &num);
			}
#line 12636 "parser_bison.c"
    break;

  case 752: /* counter_config: "packets" "number" "bytes" "number"  */
#line 4388 "parser_bison.y"
                        {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 12648 "parser_bison.c"
    break;

  case 753: /* counter_obj: %empty  */
#line 4398 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 12657 "parser_bison.c"
    break;

  case 754: /* quota_config: quota_mode "number" quota_unit quota_used  */
#line 4405 "parser_bison.y"
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
#line 12679 "parser_bison.c"
    break;

  case 755: /* quota_obj: %empty  */
#line 4425 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 12688 "parser_bison.c"
    break;

  case 756: /* secmark_config: string  */
#line 4432 "parser_bison.y"
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
#line 12706 "parser_bison.c"
    break;

  case 757: /* secmark_obj: %empty  */
#line 4448 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 12715 "parser_bison.c"
    break;

  case 758: /* ct_obj_type: "helper"  */
#line 4454 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 12721 "parser_bison.c"
    break;

  case 759: /* ct_obj_type: "timeout"  */
#line 4455 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 12727 "parser_bison.c"
    break;

  case 760: /* ct_obj_type: "expectation"  */
#line 4456 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 12733 "parser_bison.c"
    break;

  case 761: /* ct_cmd_type: "helpers"  */
#line 4459 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_HELPERS; }
#line 12739 "parser_bison.c"
    break;

  case 762: /* ct_cmd_type: "timeout"  */
#line 4460 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_TIMEOUT; }
#line 12745 "parser_bison.c"
    break;

  case 763: /* ct_cmd_type: "expectation"  */
#line 4461 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_EXPECT; }
#line 12751 "parser_bison.c"
    break;

  case 764: /* ct_l4protoname: "tcp"  */
#line 4464 "parser_bison.y"
                                        { (yyval.val) = IPPROTO_TCP; }
#line 12757 "parser_bison.c"
    break;

  case 765: /* ct_l4protoname: "udp"  */
#line 4465 "parser_bison.y"
                                        { (yyval.val) = IPPROTO_UDP; }
#line 12763 "parser_bison.c"
    break;

  case 766: /* ct_helper_config: "type" "quoted string" "protocol" ct_l4protoname stmt_separator  */
#line 4469 "parser_bison.y"
                        {
				struct ct_helper *ct;
				int ret;

				ct = &(yyvsp[-5].obj)->ct_helper;

				ret = snprintf(ct->name, sizeof(ct->name), "%s", (yyvsp[-3].string));
				if (ret <= 0 || ret >= (int)sizeof(ct->name)) {
					erec_queue(error(&(yylsp[-3]), "invalid name '%s', max length is %u\n", (yyvsp[-3].string), (int)sizeof(ct->name)), state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-3].string));

				ct->l4proto = (yyvsp[-1].val);
			}
#line 12783 "parser_bison.c"
    break;

  case 767: /* ct_helper_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4485 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 12791 "parser_bison.c"
    break;

  case 768: /* timeout_states: timeout_state  */
#line 4491 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 12801 "parser_bison.c"
    break;

  case 769: /* timeout_states: timeout_states "comma" timeout_state  */
#line 4497 "parser_bison.y"
                        {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 12810 "parser_bison.c"
    break;

  case 770: /* timeout_state: "string" "colon" "number"  */
#line 4505 "parser_bison.y"
                        {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 12825 "parser_bison.c"
    break;

  case 771: /* ct_timeout_config: "protocol" ct_l4protoname stmt_separator  */
#line 4518 "parser_bison.y"
                        {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 12837 "parser_bison.c"
    break;

  case 772: /* ct_timeout_config: "policy" '=' '{' timeout_states '}' stmt_separator  */
#line 4526 "parser_bison.y"
                        {
				struct ct_timeout *ct;

				ct = &(yyvsp[-6].obj)->ct_timeout;
				list_splice_tail((yyvsp[-2].list), &ct->timeout_list);
				xfree((yyvsp[-2].list));
			}
#line 12849 "parser_bison.c"
    break;

  case 773: /* ct_timeout_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4534 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 12857 "parser_bison.c"
    break;

  case 774: /* ct_expect_config: "protocol" ct_l4protoname stmt_separator  */
#line 4540 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 12865 "parser_bison.c"
    break;

  case 775: /* ct_expect_config: "dport" "number" stmt_separator  */
#line 4544 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 12873 "parser_bison.c"
    break;

  case 776: /* ct_expect_config: "timeout" time_spec stmt_separator  */
#line 4548 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 12881 "parser_bison.c"
    break;

  case 777: /* ct_expect_config: "size" "number" stmt_separator  */
#line 4552 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 12889 "parser_bison.c"
    break;

  case 778: /* ct_expect_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4556 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 12897 "parser_bison.c"
    break;

  case 779: /* ct_obj_alloc: %empty  */
#line 4562 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 12905 "parser_bison.c"
    break;

  case 780: /* limit_config: "rate" limit_mode limit_rate_pkts limit_burst_pkts  */
#line 4568 "parser_bison.y"
                        {
				struct limit *limit;

				limit = &(yyvsp[-4].obj)->limit;
				limit->rate	= (yyvsp[-1].limit_rate).rate;
				limit->unit	= (yyvsp[-1].limit_rate).unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-2].val);
			}
#line 12920 "parser_bison.c"
    break;

  case 781: /* limit_config: "rate" limit_mode limit_rate_bytes limit_burst_bytes  */
#line 4579 "parser_bison.y"
                        {
				struct limit *limit;

				limit = &(yyvsp[-4].obj)->limit;
				limit->rate	= (yyvsp[-1].limit_rate).rate;
				limit->unit	= (yyvsp[-1].limit_rate).unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKT_BYTES;
				limit->flags	= (yyvsp[-2].val);
			}
#line 12935 "parser_bison.c"
    break;

  case 782: /* limit_obj: %empty  */
#line 4592 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 12944 "parser_bison.c"
    break;

  case 783: /* relational_expr: expr rhs_expr  */
#line 4599 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 12952 "parser_bison.c"
    break;

  case 784: /* relational_expr: expr list_rhs_expr  */
#line 4603 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 12960 "parser_bison.c"
    break;

  case 785: /* relational_expr: expr basic_rhs_expr "/" list_rhs_expr  */
#line 4607 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 12968 "parser_bison.c"
    break;

  case 786: /* relational_expr: expr list_rhs_expr "/" list_rhs_expr  */
#line 4611 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 12976 "parser_bison.c"
    break;

  case 787: /* relational_expr: expr relational_op basic_rhs_expr "/" list_rhs_expr  */
#line 4615 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 12984 "parser_bison.c"
    break;

  case 788: /* relational_expr: expr relational_op list_rhs_expr "/" list_rhs_expr  */
#line 4619 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 12992 "parser_bison.c"
    break;

  case 789: /* relational_expr: expr relational_op rhs_expr  */
#line 4623 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13000 "parser_bison.c"
    break;

  case 790: /* relational_expr: expr relational_op list_rhs_expr  */
#line 4627 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13008 "parser_bison.c"
    break;

  case 791: /* list_rhs_expr: basic_rhs_expr "comma" basic_rhs_expr  */
#line 4633 "parser_bison.y"
                        {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 13018 "parser_bison.c"
    break;

  case 792: /* list_rhs_expr: list_rhs_expr "comma" basic_rhs_expr  */
#line 4639 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 13028 "parser_bison.c"
    break;

  case 793: /* rhs_expr: concat_rhs_expr  */
#line 4646 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13034 "parser_bison.c"
    break;

  case 794: /* rhs_expr: set_expr  */
#line 4647 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13040 "parser_bison.c"
    break;

  case 795: /* rhs_expr: set_ref_symbol_expr  */
#line 4648 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13046 "parser_bison.c"
    break;

  case 797: /* shift_rhs_expr: shift_rhs_expr "<<" primary_rhs_expr  */
#line 4653 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13054 "parser_bison.c"
    break;

  case 798: /* shift_rhs_expr: shift_rhs_expr ">>" primary_rhs_expr  */
#line 4657 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13062 "parser_bison.c"
    break;

  case 800: /* and_rhs_expr: and_rhs_expr "&" shift_rhs_expr  */
#line 4664 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13070 "parser_bison.c"
    break;

  case 802: /* exclusive_or_rhs_expr: exclusive_or_rhs_expr "^" and_rhs_expr  */
#line 4671 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13078 "parser_bison.c"
    break;

  case 804: /* inclusive_or_rhs_expr: inclusive_or_rhs_expr '|' exclusive_or_rhs_expr  */
#line 4678 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13086 "parser_bison.c"
    break;

  case 808: /* concat_rhs_expr: concat_rhs_expr "." multiton_rhs_expr  */
#line 4689 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 13099 "parser_bison.c"
    break;

  case 809: /* concat_rhs_expr: concat_rhs_expr "." basic_rhs_expr  */
#line 4698 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 13112 "parser_bison.c"
    break;

  case 810: /* boolean_keys: "exists"  */
#line 4708 "parser_bison.y"
                                                { (yyval.val8) = true; }
#line 13118 "parser_bison.c"
    break;

  case 811: /* boolean_keys: "missing"  */
#line 4709 "parser_bison.y"
                                                { (yyval.val8) = false; }
#line 13124 "parser_bison.c"
    break;

  case 812: /* boolean_expr: boolean_keys  */
#line 4713 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 13134 "parser_bison.c"
    break;

  case 813: /* keyword_expr: "ether" close_scope_eth  */
#line 4720 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 13140 "parser_bison.c"
    break;

  case 814: /* keyword_expr: "ip" close_scope_ip  */
#line 4721 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 13146 "parser_bison.c"
    break;

  case 815: /* keyword_expr: "ip6" close_scope_ip6  */
#line 4722 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 13152 "parser_bison.c"
    break;

  case 816: /* keyword_expr: "vlan" close_scope_vlan  */
#line 4723 "parser_bison.y"
                                                         { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 13158 "parser_bison.c"
    break;

  case 817: /* keyword_expr: "arp" close_scope_arp  */
#line 4724 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 13164 "parser_bison.c"
    break;

  case 818: /* keyword_expr: "dnat"  */
#line 4725 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 13170 "parser_bison.c"
    break;

  case 819: /* keyword_expr: "snat"  */
#line 4726 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 13176 "parser_bison.c"
    break;

  case 820: /* keyword_expr: "ecn"  */
#line 4727 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 13182 "parser_bison.c"
    break;

  case 821: /* keyword_expr: "reset"  */
#line 4728 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 13188 "parser_bison.c"
    break;

  case 822: /* keyword_expr: "original"  */
#line 4729 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 13194 "parser_bison.c"
    break;

  case 823: /* keyword_expr: "reply"  */
#line 4730 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 13200 "parser_bison.c"
    break;

  case 824: /* keyword_expr: "label"  */
#line 4731 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 13206 "parser_bison.c"
    break;

  case 825: /* primary_rhs_expr: symbol_expr  */
#line 4734 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13212 "parser_bison.c"
    break;

  case 826: /* primary_rhs_expr: integer_expr  */
#line 4735 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13218 "parser_bison.c"
    break;

  case 827: /* primary_rhs_expr: boolean_expr  */
#line 4736 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13224 "parser_bison.c"
    break;

  case 828: /* primary_rhs_expr: keyword_expr  */
#line 4737 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13230 "parser_bison.c"
    break;

  case 829: /* primary_rhs_expr: "tcp"  */
#line 4739 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13241 "parser_bison.c"
    break;

  case 830: /* primary_rhs_expr: "udp"  */
#line 4746 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13252 "parser_bison.c"
    break;

  case 831: /* primary_rhs_expr: "udplite"  */
#line 4753 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13263 "parser_bison.c"
    break;

  case 832: /* primary_rhs_expr: "esp"  */
#line 4760 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13274 "parser_bison.c"
    break;

  case 833: /* primary_rhs_expr: "ah"  */
#line 4767 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13285 "parser_bison.c"
    break;

  case 834: /* primary_rhs_expr: "icmp"  */
#line 4774 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13296 "parser_bison.c"
    break;

  case 835: /* primary_rhs_expr: "igmp"  */
#line 4781 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13307 "parser_bison.c"
    break;

  case 836: /* primary_rhs_expr: "icmpv6"  */
#line 4788 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13318 "parser_bison.c"
    break;

  case 837: /* primary_rhs_expr: "comp"  */
#line 4795 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13329 "parser_bison.c"
    break;

  case 838: /* primary_rhs_expr: "dccp"  */
#line 4802 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13340 "parser_bison.c"
    break;

  case 839: /* primary_rhs_expr: "sctp" close_scope_sctp  */
#line 4809 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13351 "parser_bison.c"
    break;

  case 840: /* primary_rhs_expr: "redirect"  */
#line 4816 "parser_bison.y"
                        {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13362 "parser_bison.c"
    break;

  case 841: /* primary_rhs_expr: '(' basic_rhs_expr ')'  */
#line 4822 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 13368 "parser_bison.c"
    break;

  case 842: /* relational_op: "=="  */
#line 4825 "parser_bison.y"
                                                { (yyval.val) = OP_EQ; }
#line 13374 "parser_bison.c"
    break;

  case 843: /* relational_op: "!="  */
#line 4826 "parser_bison.y"
                                                { (yyval.val) = OP_NEQ; }
#line 13380 "parser_bison.c"
    break;

  case 844: /* relational_op: "<"  */
#line 4827 "parser_bison.y"
                                                { (yyval.val) = OP_LT; }
#line 13386 "parser_bison.c"
    break;

  case 845: /* relational_op: ">"  */
#line 4828 "parser_bison.y"
                                                { (yyval.val) = OP_GT; }
#line 13392 "parser_bison.c"
    break;

  case 846: /* relational_op: ">="  */
#line 4829 "parser_bison.y"
                                                { (yyval.val) = OP_GTE; }
#line 13398 "parser_bison.c"
    break;

  case 847: /* relational_op: "<="  */
#line 4830 "parser_bison.y"
                                                { (yyval.val) = OP_LTE; }
#line 13404 "parser_bison.c"
    break;

  case 848: /* relational_op: "!"  */
#line 4831 "parser_bison.y"
                                                { (yyval.val) = OP_NEG; }
#line 13410 "parser_bison.c"
    break;

  case 849: /* verdict_expr: "accept"  */
#line 4835 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 13418 "parser_bison.c"
    break;

  case 850: /* verdict_expr: "drop"  */
#line 4839 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 13426 "parser_bison.c"
    break;

  case 851: /* verdict_expr: "continue"  */
#line 4843 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 13434 "parser_bison.c"
    break;

  case 852: /* verdict_expr: "jump" chain_expr  */
#line 4847 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 13442 "parser_bison.c"
    break;

  case 853: /* verdict_expr: "goto" chain_expr  */
#line 4851 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 13450 "parser_bison.c"
    break;

  case 854: /* verdict_expr: "return"  */
#line 4855 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 13458 "parser_bison.c"
    break;

  case 856: /* chain_expr: identifier  */
#line 4862 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 13470 "parser_bison.c"
    break;

  case 857: /* meta_expr: "meta" meta_key  */
#line 4872 "parser_bison.y"
                        {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 13478 "parser_bison.c"
    break;

  case 858: /* meta_expr: meta_key_unqualified  */
#line 4876 "parser_bison.y"
                        {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 13486 "parser_bison.c"
    break;

  case 859: /* meta_expr: "meta" "string"  */
#line 4880 "parser_bison.y"
                        {
				struct error_record *erec;
				unsigned int key;

				erec = meta_key_parse(&(yyloc), (yyvsp[0].string), &key);
				xfree((yyvsp[0].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.expr) = meta_expr_alloc(&(yyloc), key);
			}
#line 13504 "parser_bison.c"
    break;

  case 862: /* meta_key_qualified: "length"  */
#line 4899 "parser_bison.y"
                                                { (yyval.val) = NFT_META_LEN; }
#line 13510 "parser_bison.c"
    break;

  case 863: /* meta_key_qualified: "protocol"  */
#line 4900 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PROTOCOL; }
#line 13516 "parser_bison.c"
    break;

  case 864: /* meta_key_qualified: "priority"  */
#line 4901 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PRIORITY; }
#line 13522 "parser_bison.c"
    break;

  case 865: /* meta_key_qualified: "random"  */
#line 4902 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PRANDOM; }
#line 13528 "parser_bison.c"
    break;

  case 866: /* meta_key_qualified: "secmark" close_scope_secmark  */
#line 4903 "parser_bison.y"
                                                            { (yyval.val) = NFT_META_SECMARK; }
#line 13534 "parser_bison.c"
    break;

  case 867: /* meta_key_unqualified: "mark"  */
#line 4906 "parser_bison.y"
                                                { (yyval.val) = NFT_META_MARK; }
#line 13540 "parser_bison.c"
    break;

  case 868: /* meta_key_unqualified: "iif"  */
#line 4907 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIF; }
#line 13546 "parser_bison.c"
    break;

  case 869: /* meta_key_unqualified: "iifname"  */
#line 4908 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFNAME; }
#line 13552 "parser_bison.c"
    break;

  case 870: /* meta_key_unqualified: "iiftype"  */
#line 4909 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFTYPE; }
#line 13558 "parser_bison.c"
    break;

  case 871: /* meta_key_unqualified: "oif"  */
#line 4910 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIF; }
#line 13564 "parser_bison.c"
    break;

  case 872: /* meta_key_unqualified: "oifname"  */
#line 4911 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFNAME; }
#line 13570 "parser_bison.c"
    break;

  case 873: /* meta_key_unqualified: "oiftype"  */
#line 4912 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFTYPE; }
#line 13576 "parser_bison.c"
    break;

  case 874: /* meta_key_unqualified: "skuid"  */
#line 4913 "parser_bison.y"
                                                { (yyval.val) = NFT_META_SKUID; }
#line 13582 "parser_bison.c"
    break;

  case 875: /* meta_key_unqualified: "skgid"  */
#line 4914 "parser_bison.y"
                                                { (yyval.val) = NFT_META_SKGID; }
#line 13588 "parser_bison.c"
    break;

  case 876: /* meta_key_unqualified: "nftrace"  */
#line 4915 "parser_bison.y"
                                                { (yyval.val) = NFT_META_NFTRACE; }
#line 13594 "parser_bison.c"
    break;

  case 877: /* meta_key_unqualified: "rtclassid"  */
#line 4916 "parser_bison.y"
                                                { (yyval.val) = NFT_META_RTCLASSID; }
#line 13600 "parser_bison.c"
    break;

  case 878: /* meta_key_unqualified: "ibriport"  */
#line 4917 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 13606 "parser_bison.c"
    break;

  case 879: /* meta_key_unqualified: "obriport"  */
#line 4918 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 13612 "parser_bison.c"
    break;

  case 880: /* meta_key_unqualified: "ibrname"  */
#line 4919 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 13618 "parser_bison.c"
    break;

  case 881: /* meta_key_unqualified: "obrname"  */
#line 4920 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 13624 "parser_bison.c"
    break;

  case 882: /* meta_key_unqualified: "pkttype"  */
#line 4921 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PKTTYPE; }
#line 13630 "parser_bison.c"
    break;

  case 883: /* meta_key_unqualified: "cpu"  */
#line 4922 "parser_bison.y"
                                                { (yyval.val) = NFT_META_CPU; }
#line 13636 "parser_bison.c"
    break;

  case 884: /* meta_key_unqualified: "iifgroup"  */
#line 4923 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFGROUP; }
#line 13642 "parser_bison.c"
    break;

  case 885: /* meta_key_unqualified: "oifgroup"  */
#line 4924 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFGROUP; }
#line 13648 "parser_bison.c"
    break;

  case 886: /* meta_key_unqualified: "cgroup"  */
#line 4925 "parser_bison.y"
                                                { (yyval.val) = NFT_META_CGROUP; }
#line 13654 "parser_bison.c"
    break;

  case 887: /* meta_key_unqualified: "ipsec" close_scope_ipsec  */
#line 4926 "parser_bison.y"
                                                          { (yyval.val) = NFT_META_SECPATH; }
#line 13660 "parser_bison.c"
    break;

  case 888: /* meta_key_unqualified: "time"  */
#line 4927 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_NS; }
#line 13666 "parser_bison.c"
    break;

  case 889: /* meta_key_unqualified: "day"  */
#line 4928 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_DAY; }
#line 13672 "parser_bison.c"
    break;

  case 890: /* meta_key_unqualified: "hour"  */
#line 4929 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_HOUR; }
#line 13678 "parser_bison.c"
    break;

  case 891: /* meta_stmt: "meta" meta_key "set" stmt_expr  */
#line 4933 "parser_bison.y"
                        {
				switch ((yyvsp[-2].val)) {
				case NFT_META_SECMARK:
					switch ((yyvsp[0].expr)->etype) {
					case EXPR_CT:
						(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
						break;
					default:
						(yyval.stmt) = objref_stmt_alloc(&(yyloc));
						(yyval.stmt)->objref.type = NFT_OBJECT_SECMARK;
						(yyval.stmt)->objref.expr = (yyvsp[0].expr);
						break;
					}
					break;
				default:
					(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
					break;
				}
			}
#line 13702 "parser_bison.c"
    break;

  case 892: /* meta_stmt: meta_key_unqualified "set" stmt_expr  */
#line 4953 "parser_bison.y"
                        {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 13710 "parser_bison.c"
    break;

  case 893: /* meta_stmt: "meta" "string" "set" stmt_expr  */
#line 4957 "parser_bison.y"
                        {
				struct error_record *erec;
				unsigned int key;

				erec = meta_key_parse(&(yyloc), (yyvsp[-2].string), &key);
				xfree((yyvsp[-2].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.stmt) = meta_stmt_alloc(&(yyloc), key, (yyvsp[0].expr));
			}
#line 13728 "parser_bison.c"
    break;

  case 894: /* meta_stmt: "notrack"  */
#line 4971 "parser_bison.y"
                        {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 13736 "parser_bison.c"
    break;

  case 895: /* meta_stmt: "flow" "offload" "@" string  */
#line 4975 "parser_bison.y"
                        {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 13744 "parser_bison.c"
    break;

  case 896: /* meta_stmt: "flow" "add" "@" string  */
#line 4979 "parser_bison.y"
                        {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 13752 "parser_bison.c"
    break;

  case 897: /* socket_expr: "socket" socket_key close_scope_socket  */
#line 4985 "parser_bison.y"
                        {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 13760 "parser_bison.c"
    break;

  case 898: /* socket_expr: "socket" "cgroupv2" "level" "number" close_scope_socket  */
#line 4989 "parser_bison.y"
                        {
				(yyval.expr) = socket_expr_alloc(&(yyloc), NFT_SOCKET_CGROUPV2, (yyvsp[-1].val));
			}
#line 13768 "parser_bison.c"
    break;

  case 899: /* socket_key: "transparent"  */
#line 4994 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 13774 "parser_bison.c"
    break;

  case 900: /* socket_key: "mark"  */
#line 4995 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_MARK; }
#line 13780 "parser_bison.c"
    break;

  case 901: /* socket_key: "wildcard"  */
#line 4996 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_WILDCARD; }
#line 13786 "parser_bison.c"
    break;

  case 902: /* offset_opt: %empty  */
#line 4999 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 13792 "parser_bison.c"
    break;

  case 903: /* offset_opt: "offset" "number"  */
#line 5000 "parser_bison.y"
                                                { (yyval.val) = (yyvsp[0].val); }
#line 13798 "parser_bison.c"
    break;

  case 904: /* numgen_type: "inc"  */
#line 5003 "parser_bison.y"
                                                { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 13804 "parser_bison.c"
    break;

  case 905: /* numgen_type: "random"  */
#line 5004 "parser_bison.y"
                                                { (yyval.val) = NFT_NG_RANDOM; }
#line 13810 "parser_bison.c"
    break;

  case 906: /* numgen_expr: "numgen" numgen_type "mod" "number" offset_opt close_scope_numgen  */
#line 5008 "parser_bison.y"
                        {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 13818 "parser_bison.c"
    break;

  case 907: /* xfrm_spnum: "spnum" "number"  */
#line 5013 "parser_bison.y"
                                            { (yyval.val) = (yyvsp[0].val); }
#line 13824 "parser_bison.c"
    break;

  case 908: /* xfrm_spnum: %empty  */
#line 5014 "parser_bison.y"
                                            { (yyval.val) = 0; }
#line 13830 "parser_bison.c"
    break;

  case 909: /* xfrm_dir: "in"  */
#line 5017 "parser_bison.y"
                                        { (yyval.val) = XFRM_POLICY_IN; }
#line 13836 "parser_bison.c"
    break;

  case 910: /* xfrm_dir: "out"  */
#line 5018 "parser_bison.y"
                                        { (yyval.val) = XFRM_POLICY_OUT; }
#line 13842 "parser_bison.c"
    break;

  case 911: /* xfrm_state_key: "spi"  */
#line 5021 "parser_bison.y"
                                    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 13848 "parser_bison.c"
    break;

  case 912: /* xfrm_state_key: "reqid"  */
#line 5022 "parser_bison.y"
                                      { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 13854 "parser_bison.c"
    break;

  case 913: /* xfrm_state_proto_key: "daddr"  */
#line 5025 "parser_bison.y"
                                                { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 13860 "parser_bison.c"
    break;

  case 914: /* xfrm_state_proto_key: "saddr"  */
#line 5026 "parser_bison.y"
                                                { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 13866 "parser_bison.c"
    break;

  case 915: /* xfrm_expr: "ipsec" xfrm_dir xfrm_spnum xfrm_state_key close_scope_ipsec  */
#line 5030 "parser_bison.y"
                        {
				if ((yyvsp[-2].val) > 255) {
					erec_queue(error(&(yylsp[-2]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 13878 "parser_bison.c"
    break;

  case 916: /* xfrm_expr: "ipsec" xfrm_dir xfrm_spnum nf_key_proto xfrm_state_proto_key close_scope_ipsec  */
#line 5038 "parser_bison.y"
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
#line 13907 "parser_bison.c"
    break;

  case 917: /* hash_expr: "jhash" expr "mod" "number" "seed" "number" offset_opt close_scope_hash  */
#line 5065 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-4].val), true, (yyvsp[-2].val), (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-6].expr);
			}
#line 13916 "parser_bison.c"
    break;

  case 918: /* hash_expr: "jhash" expr "mod" "number" offset_opt close_scope_hash  */
#line 5070 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-4].expr);
			}
#line 13925 "parser_bison.c"
    break;

  case 919: /* hash_expr: "symhash" "mod" "number" offset_opt close_scope_hash  */
#line 5075 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_SYM);
			}
#line 13933 "parser_bison.c"
    break;

  case 920: /* nf_key_proto: "ip" close_scope_ip  */
#line 5080 "parser_bison.y"
                                                       { (yyval.val) = NFPROTO_IPV4; }
#line 13939 "parser_bison.c"
    break;

  case 921: /* nf_key_proto: "ip6" close_scope_ip6  */
#line 5081 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV6; }
#line 13945 "parser_bison.c"
    break;

  case 922: /* rt_expr: "rt" rt_key close_scope_rt  */
#line 5085 "parser_bison.y"
                        {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[-1].val), true);
			}
#line 13953 "parser_bison.c"
    break;

  case 923: /* rt_expr: "rt" nf_key_proto rt_key close_scope_rt  */
#line 5089 "parser_bison.y"
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
#line 13975 "parser_bison.c"
    break;

  case 924: /* rt_key: "classid"  */
#line 5108 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_CLASSID; }
#line 13981 "parser_bison.c"
    break;

  case 925: /* rt_key: "nexthop"  */
#line 5109 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 13987 "parser_bison.c"
    break;

  case 926: /* rt_key: "mtu"  */
#line 5110 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_TCPMSS; }
#line 13993 "parser_bison.c"
    break;

  case 927: /* rt_key: "ipsec" close_scope_ipsec  */
#line 5111 "parser_bison.y"
                                                          { (yyval.val) = NFT_RT_XFRM; }
#line 13999 "parser_bison.c"
    break;

  case 928: /* ct_expr: "ct" ct_key close_scope_ct  */
#line 5115 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), -1);
			}
#line 14007 "parser_bison.c"
    break;

  case 929: /* ct_expr: "ct" ct_dir ct_key_dir close_scope_ct  */
#line 5119 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 14015 "parser_bison.c"
    break;

  case 930: /* ct_expr: "ct" ct_dir ct_key_proto_field close_scope_ct  */
#line 5123 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 14023 "parser_bison.c"
    break;

  case 931: /* ct_dir: "original"  */
#line 5128 "parser_bison.y"
                                                { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 14029 "parser_bison.c"
    break;

  case 932: /* ct_dir: "reply"  */
#line 5129 "parser_bison.y"
                                                { (yyval.val) = IP_CT_DIR_REPLY; }
#line 14035 "parser_bison.c"
    break;

  case 933: /* ct_key: "l3proto"  */
#line 5132 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 14041 "parser_bison.c"
    break;

  case 934: /* ct_key: "protocol"  */
#line 5133 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTOCOL; }
#line 14047 "parser_bison.c"
    break;

  case 935: /* ct_key: "mark"  */
#line 5134 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_MARK; }
#line 14053 "parser_bison.c"
    break;

  case 936: /* ct_key: "state"  */
#line 5135 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_STATE; }
#line 14059 "parser_bison.c"
    break;

  case 937: /* ct_key: "direction"  */
#line 5136 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DIRECTION; }
#line 14065 "parser_bison.c"
    break;

  case 938: /* ct_key: "status"  */
#line 5137 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_STATUS; }
#line 14071 "parser_bison.c"
    break;

  case 939: /* ct_key: "expiration"  */
#line 5138 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_EXPIRATION; }
#line 14077 "parser_bison.c"
    break;

  case 940: /* ct_key: "helper"  */
#line 5139 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_HELPER; }
#line 14083 "parser_bison.c"
    break;

  case 941: /* ct_key: "saddr"  */
#line 5140 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_SRC; }
#line 14089 "parser_bison.c"
    break;

  case 942: /* ct_key: "daddr"  */
#line 5141 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DST; }
#line 14095 "parser_bison.c"
    break;

  case 943: /* ct_key: "proto-src"  */
#line 5142 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 14101 "parser_bison.c"
    break;

  case 944: /* ct_key: "proto-dst"  */
#line 5143 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_DST; }
#line 14107 "parser_bison.c"
    break;

  case 945: /* ct_key: "label"  */
#line 5144 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_LABELS; }
#line 14113 "parser_bison.c"
    break;

  case 946: /* ct_key: "event"  */
#line 5145 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_EVENTMASK; }
#line 14119 "parser_bison.c"
    break;

  case 947: /* ct_key: "secmark" close_scope_secmark  */
#line 5146 "parser_bison.y"
                                                            { (yyval.val) = NFT_CT_SECMARK; }
#line 14125 "parser_bison.c"
    break;

  case 948: /* ct_key: "id"  */
#line 5147 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_ID; }
#line 14131 "parser_bison.c"
    break;

  case 950: /* ct_key_dir: "saddr"  */
#line 5151 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_SRC; }
#line 14137 "parser_bison.c"
    break;

  case 951: /* ct_key_dir: "daddr"  */
#line 5152 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DST; }
#line 14143 "parser_bison.c"
    break;

  case 952: /* ct_key_dir: "l3proto"  */
#line 5153 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 14149 "parser_bison.c"
    break;

  case 953: /* ct_key_dir: "protocol"  */
#line 5154 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTOCOL; }
#line 14155 "parser_bison.c"
    break;

  case 954: /* ct_key_dir: "proto-src"  */
#line 5155 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 14161 "parser_bison.c"
    break;

  case 955: /* ct_key_dir: "proto-dst"  */
#line 5156 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_DST; }
#line 14167 "parser_bison.c"
    break;

  case 957: /* ct_key_proto_field: "ip" "saddr" close_scope_ip  */
#line 5160 "parser_bison.y"
                                                               { (yyval.val) = NFT_CT_SRC_IP; }
#line 14173 "parser_bison.c"
    break;

  case 958: /* ct_key_proto_field: "ip" "daddr" close_scope_ip  */
#line 5161 "parser_bison.y"
                                                               { (yyval.val) = NFT_CT_DST_IP; }
#line 14179 "parser_bison.c"
    break;

  case 959: /* ct_key_proto_field: "ip6" "saddr" close_scope_ip6  */
#line 5162 "parser_bison.y"
                                                                { (yyval.val) = NFT_CT_SRC_IP6; }
#line 14185 "parser_bison.c"
    break;

  case 960: /* ct_key_proto_field: "ip6" "daddr" close_scope_ip6  */
#line 5163 "parser_bison.y"
                                                                { (yyval.val) = NFT_CT_DST_IP6; }
#line 14191 "parser_bison.c"
    break;

  case 961: /* ct_key_dir_optional: "bytes"  */
#line 5166 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_BYTES; }
#line 14197 "parser_bison.c"
    break;

  case 962: /* ct_key_dir_optional: "packets"  */
#line 5167 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PKTS; }
#line 14203 "parser_bison.c"
    break;

  case 963: /* ct_key_dir_optional: "avgpkt"  */
#line 5168 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_AVGPKT; }
#line 14209 "parser_bison.c"
    break;

  case 964: /* ct_key_dir_optional: "zone"  */
#line 5169 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_ZONE; }
#line 14215 "parser_bison.c"
    break;

  case 967: /* list_stmt_expr: symbol_stmt_expr "comma" symbol_stmt_expr  */
#line 5177 "parser_bison.y"
                        {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 14225 "parser_bison.c"
    break;

  case 968: /* list_stmt_expr: list_stmt_expr "comma" symbol_stmt_expr  */
#line 5183 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 14235 "parser_bison.c"
    break;

  case 969: /* ct_stmt: "ct" ct_key "set" stmt_expr close_scope_ct  */
#line 5191 "parser_bison.y"
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
#line 14252 "parser_bison.c"
    break;

  case 970: /* ct_stmt: "ct" "timeout" "set" stmt_expr close_scope_ct  */
#line 5204 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);

			}
#line 14263 "parser_bison.c"
    break;

  case 971: /* ct_stmt: "ct" "expectation" "set" stmt_expr close_scope_ct  */
#line 5211 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 14273 "parser_bison.c"
    break;

  case 972: /* ct_stmt: "ct" ct_dir ct_key_dir_optional "set" stmt_expr close_scope_ct  */
#line 5217 "parser_bison.y"
                        {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].val), (yyvsp[-1].expr));
			}
#line 14281 "parser_bison.c"
    break;

  case 973: /* payload_stmt: payload_expr "set" stmt_expr  */
#line 5223 "parser_bison.y"
                        {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14292 "parser_bison.c"
    break;

  case 992: /* payload_raw_expr: "@" payload_base_spec "comma" "number" "comma" "number"  */
#line 5252 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 14303 "parser_bison.c"
    break;

  case 993: /* payload_base_spec: "ll"  */
#line 5260 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 14309 "parser_bison.c"
    break;

  case 994: /* payload_base_spec: "nh"  */
#line 5261 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 14315 "parser_bison.c"
    break;

  case 995: /* payload_base_spec: "th"  */
#line 5262 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 14321 "parser_bison.c"
    break;

  case 996: /* payload_base_spec: "string"  */
#line 5264 "parser_bison.y"
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
#line 14336 "parser_bison.c"
    break;

  case 997: /* eth_hdr_expr: "ether" eth_hdr_field close_scope_eth  */
#line 5277 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[-1].val));
			}
#line 14344 "parser_bison.c"
    break;

  case 998: /* eth_hdr_field: "saddr"  */
#line 5282 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_SADDR; }
#line 14350 "parser_bison.c"
    break;

  case 999: /* eth_hdr_field: "daddr"  */
#line 5283 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_DADDR; }
#line 14356 "parser_bison.c"
    break;

  case 1000: /* eth_hdr_field: "type"  */
#line 5284 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_TYPE; }
#line 14362 "parser_bison.c"
    break;

  case 1001: /* vlan_hdr_expr: "vlan" vlan_hdr_field close_scope_vlan  */
#line 5288 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[-1].val));
			}
#line 14370 "parser_bison.c"
    break;

  case 1002: /* vlan_hdr_field: "id"  */
#line 5293 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_VID; }
#line 14376 "parser_bison.c"
    break;

  case 1003: /* vlan_hdr_field: "cfi"  */
#line 5294 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_CFI; }
#line 14382 "parser_bison.c"
    break;

  case 1004: /* vlan_hdr_field: "dei"  */
#line 5295 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_DEI; }
#line 14388 "parser_bison.c"
    break;

  case 1005: /* vlan_hdr_field: "pcp"  */
#line 5296 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_PCP; }
#line 14394 "parser_bison.c"
    break;

  case 1006: /* vlan_hdr_field: "type"  */
#line 5297 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_TYPE; }
#line 14400 "parser_bison.c"
    break;

  case 1007: /* arp_hdr_expr: "arp" arp_hdr_field close_scope_arp  */
#line 5301 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[-1].val));
			}
#line 14408 "parser_bison.c"
    break;

  case 1008: /* arp_hdr_field: "htype"  */
#line 5306 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_HRD; }
#line 14414 "parser_bison.c"
    break;

  case 1009: /* arp_hdr_field: "ptype"  */
#line 5307 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_PRO; }
#line 14420 "parser_bison.c"
    break;

  case 1010: /* arp_hdr_field: "hlen"  */
#line 5308 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_HLN; }
#line 14426 "parser_bison.c"
    break;

  case 1011: /* arp_hdr_field: "plen"  */
#line 5309 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_PLN; }
#line 14432 "parser_bison.c"
    break;

  case 1012: /* arp_hdr_field: "operation"  */
#line 5310 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_OP; }
#line 14438 "parser_bison.c"
    break;

  case 1013: /* arp_hdr_field: "saddr" "ether" close_scope_eth  */
#line 5311 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 14444 "parser_bison.c"
    break;

  case 1014: /* arp_hdr_field: "daddr" "ether" close_scope_eth  */
#line 5312 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 14450 "parser_bison.c"
    break;

  case 1015: /* arp_hdr_field: "saddr" "ip" close_scope_ip  */
#line 5313 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_SADDR_IP; }
#line 14456 "parser_bison.c"
    break;

  case 1016: /* arp_hdr_field: "daddr" "ip" close_scope_ip  */
#line 5314 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_DADDR_IP; }
#line 14462 "parser_bison.c"
    break;

  case 1017: /* ip_hdr_expr: "ip" ip_hdr_field close_scope_ip  */
#line 5318 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[-1].val));
			}
#line 14470 "parser_bison.c"
    break;

  case 1018: /* ip_hdr_expr: "ip" "option" ip_option_type ip_option_field close_scope_ip  */
#line 5322 "parser_bison.y"
                        {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val), 0);
			}
#line 14478 "parser_bison.c"
    break;

  case 1019: /* ip_hdr_expr: "ip" "option" ip_option_type close_scope_ip  */
#line 5326 "parser_bison.y"
                        {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), IPOPT_FIELD_TYPE, 0);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 14487 "parser_bison.c"
    break;

  case 1020: /* ip_hdr_field: "version"  */
#line 5332 "parser_bison.y"
                                                { (yyval.val) = IPHDR_VERSION; }
#line 14493 "parser_bison.c"
    break;

  case 1021: /* ip_hdr_field: "hdrlength"  */
#line 5333 "parser_bison.y"
                                                { (yyval.val) = IPHDR_HDRLENGTH; }
#line 14499 "parser_bison.c"
    break;

  case 1022: /* ip_hdr_field: "dscp"  */
#line 5334 "parser_bison.y"
                                                { (yyval.val) = IPHDR_DSCP; }
#line 14505 "parser_bison.c"
    break;

  case 1023: /* ip_hdr_field: "ecn"  */
#line 5335 "parser_bison.y"
                                                { (yyval.val) = IPHDR_ECN; }
#line 14511 "parser_bison.c"
    break;

  case 1024: /* ip_hdr_field: "length"  */
#line 5336 "parser_bison.y"
                                                { (yyval.val) = IPHDR_LENGTH; }
#line 14517 "parser_bison.c"
    break;

  case 1025: /* ip_hdr_field: "id"  */
#line 5337 "parser_bison.y"
                                                { (yyval.val) = IPHDR_ID; }
#line 14523 "parser_bison.c"
    break;

  case 1026: /* ip_hdr_field: "frag-off"  */
#line 5338 "parser_bison.y"
                                                { (yyval.val) = IPHDR_FRAG_OFF; }
#line 14529 "parser_bison.c"
    break;

  case 1027: /* ip_hdr_field: "ttl"  */
#line 5339 "parser_bison.y"
                                                { (yyval.val) = IPHDR_TTL; }
#line 14535 "parser_bison.c"
    break;

  case 1028: /* ip_hdr_field: "protocol"  */
#line 5340 "parser_bison.y"
                                                { (yyval.val) = IPHDR_PROTOCOL; }
#line 14541 "parser_bison.c"
    break;

  case 1029: /* ip_hdr_field: "checksum"  */
#line 5341 "parser_bison.y"
                                                { (yyval.val) = IPHDR_CHECKSUM; }
#line 14547 "parser_bison.c"
    break;

  case 1030: /* ip_hdr_field: "saddr"  */
#line 5342 "parser_bison.y"
                                                { (yyval.val) = IPHDR_SADDR; }
#line 14553 "parser_bison.c"
    break;

  case 1031: /* ip_hdr_field: "daddr"  */
#line 5343 "parser_bison.y"
                                                { (yyval.val) = IPHDR_DADDR; }
#line 14559 "parser_bison.c"
    break;

  case 1032: /* ip_option_type: "lsrr"  */
#line 5346 "parser_bison.y"
                                                { (yyval.val) = IPOPT_LSRR; }
#line 14565 "parser_bison.c"
    break;

  case 1033: /* ip_option_type: "rr"  */
#line 5347 "parser_bison.y"
                                                { (yyval.val) = IPOPT_RR; }
#line 14571 "parser_bison.c"
    break;

  case 1034: /* ip_option_type: "ssrr"  */
#line 5348 "parser_bison.y"
                                                { (yyval.val) = IPOPT_SSRR; }
#line 14577 "parser_bison.c"
    break;

  case 1035: /* ip_option_type: "ra"  */
#line 5349 "parser_bison.y"
                                                { (yyval.val) = IPOPT_RA; }
#line 14583 "parser_bison.c"
    break;

  case 1036: /* ip_option_field: "type"  */
#line 5352 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 14589 "parser_bison.c"
    break;

  case 1037: /* ip_option_field: "length"  */
#line 5353 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 14595 "parser_bison.c"
    break;

  case 1038: /* ip_option_field: "value"  */
#line 5354 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 14601 "parser_bison.c"
    break;

  case 1039: /* ip_option_field: "ptr"  */
#line 5355 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_PTR; }
#line 14607 "parser_bison.c"
    break;

  case 1040: /* ip_option_field: "addr"  */
#line 5356 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 14613 "parser_bison.c"
    break;

  case 1041: /* icmp_hdr_expr: "icmp" icmp_hdr_field  */
#line 5360 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 14621 "parser_bison.c"
    break;

  case 1042: /* icmp_hdr_field: "type"  */
#line 5365 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_TYPE; }
#line 14627 "parser_bison.c"
    break;

  case 1043: /* icmp_hdr_field: "code"  */
#line 5366 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_CODE; }
#line 14633 "parser_bison.c"
    break;

  case 1044: /* icmp_hdr_field: "checksum"  */
#line 5367 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 14639 "parser_bison.c"
    break;

  case 1045: /* icmp_hdr_field: "id"  */
#line 5368 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_ID; }
#line 14645 "parser_bison.c"
    break;

  case 1046: /* icmp_hdr_field: "seq"  */
#line 5369 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_SEQ; }
#line 14651 "parser_bison.c"
    break;

  case 1047: /* icmp_hdr_field: "gateway"  */
#line 5370 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_GATEWAY; }
#line 14657 "parser_bison.c"
    break;

  case 1048: /* icmp_hdr_field: "mtu"  */
#line 5371 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_MTU; }
#line 14663 "parser_bison.c"
    break;

  case 1049: /* igmp_hdr_expr: "igmp" igmp_hdr_field  */
#line 5375 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[0].val));
			}
#line 14671 "parser_bison.c"
    break;

  case 1050: /* igmp_hdr_field: "type"  */
#line 5380 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_TYPE; }
#line 14677 "parser_bison.c"
    break;

  case 1051: /* igmp_hdr_field: "checksum"  */
#line 5381 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 14683 "parser_bison.c"
    break;

  case 1052: /* igmp_hdr_field: "mrt"  */
#line 5382 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_MRT; }
#line 14689 "parser_bison.c"
    break;

  case 1053: /* igmp_hdr_field: "group"  */
#line 5383 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_GROUP; }
#line 14695 "parser_bison.c"
    break;

  case 1054: /* ip6_hdr_expr: "ip6" ip6_hdr_field close_scope_ip6  */
#line 5387 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[-1].val));
			}
#line 14703 "parser_bison.c"
    break;

  case 1055: /* ip6_hdr_field: "version"  */
#line 5392 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_VERSION; }
#line 14709 "parser_bison.c"
    break;

  case 1056: /* ip6_hdr_field: "dscp"  */
#line 5393 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_DSCP; }
#line 14715 "parser_bison.c"
    break;

  case 1057: /* ip6_hdr_field: "ecn"  */
#line 5394 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_ECN; }
#line 14721 "parser_bison.c"
    break;

  case 1058: /* ip6_hdr_field: "flowlabel"  */
#line 5395 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 14727 "parser_bison.c"
    break;

  case 1059: /* ip6_hdr_field: "length"  */
#line 5396 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_LENGTH; }
#line 14733 "parser_bison.c"
    break;

  case 1060: /* ip6_hdr_field: "nexthdr"  */
#line 5397 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_NEXTHDR; }
#line 14739 "parser_bison.c"
    break;

  case 1061: /* ip6_hdr_field: "hoplimit"  */
#line 5398 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 14745 "parser_bison.c"
    break;

  case 1062: /* ip6_hdr_field: "saddr"  */
#line 5399 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_SADDR; }
#line 14751 "parser_bison.c"
    break;

  case 1063: /* ip6_hdr_field: "daddr"  */
#line 5400 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_DADDR; }
#line 14757 "parser_bison.c"
    break;

  case 1064: /* icmp6_hdr_expr: "icmpv6" icmp6_hdr_field  */
#line 5403 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 14765 "parser_bison.c"
    break;

  case 1065: /* icmp6_hdr_field: "type"  */
#line 5408 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_TYPE; }
#line 14771 "parser_bison.c"
    break;

  case 1066: /* icmp6_hdr_field: "code"  */
#line 5409 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_CODE; }
#line 14777 "parser_bison.c"
    break;

  case 1067: /* icmp6_hdr_field: "checksum"  */
#line 5410 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 14783 "parser_bison.c"
    break;

  case 1068: /* icmp6_hdr_field: "param-problem"  */
#line 5411 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_PPTR; }
#line 14789 "parser_bison.c"
    break;

  case 1069: /* icmp6_hdr_field: "mtu"  */
#line 5412 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_MTU; }
#line 14795 "parser_bison.c"
    break;

  case 1070: /* icmp6_hdr_field: "id"  */
#line 5413 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_ID; }
#line 14801 "parser_bison.c"
    break;

  case 1071: /* icmp6_hdr_field: "seq"  */
#line 5414 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_SEQ; }
#line 14807 "parser_bison.c"
    break;

  case 1072: /* icmp6_hdr_field: "max-delay"  */
#line 5415 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 14813 "parser_bison.c"
    break;

  case 1073: /* auth_hdr_expr: "ah" auth_hdr_field  */
#line 5419 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 14821 "parser_bison.c"
    break;

  case 1074: /* auth_hdr_field: "nexthdr"  */
#line 5424 "parser_bison.y"
                                                { (yyval.val) = AHHDR_NEXTHDR; }
#line 14827 "parser_bison.c"
    break;

  case 1075: /* auth_hdr_field: "hdrlength"  */
#line 5425 "parser_bison.y"
                                                { (yyval.val) = AHHDR_HDRLENGTH; }
#line 14833 "parser_bison.c"
    break;

  case 1076: /* auth_hdr_field: "reserved"  */
#line 5426 "parser_bison.y"
                                                { (yyval.val) = AHHDR_RESERVED; }
#line 14839 "parser_bison.c"
    break;

  case 1077: /* auth_hdr_field: "spi"  */
#line 5427 "parser_bison.y"
                                                { (yyval.val) = AHHDR_SPI; }
#line 14845 "parser_bison.c"
    break;

  case 1078: /* auth_hdr_field: "seq"  */
#line 5428 "parser_bison.y"
                                                { (yyval.val) = AHHDR_SEQUENCE; }
#line 14851 "parser_bison.c"
    break;

  case 1079: /* esp_hdr_expr: "esp" esp_hdr_field  */
#line 5432 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 14859 "parser_bison.c"
    break;

  case 1080: /* esp_hdr_field: "spi"  */
#line 5437 "parser_bison.y"
                                                { (yyval.val) = ESPHDR_SPI; }
#line 14865 "parser_bison.c"
    break;

  case 1081: /* esp_hdr_field: "seq"  */
#line 5438 "parser_bison.y"
                                                { (yyval.val) = ESPHDR_SEQUENCE; }
#line 14871 "parser_bison.c"
    break;

  case 1082: /* comp_hdr_expr: "comp" comp_hdr_field  */
#line 5442 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 14879 "parser_bison.c"
    break;

  case 1083: /* comp_hdr_field: "nexthdr"  */
#line 5447 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_NEXTHDR; }
#line 14885 "parser_bison.c"
    break;

  case 1084: /* comp_hdr_field: "flags"  */
#line 5448 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_FLAGS; }
#line 14891 "parser_bison.c"
    break;

  case 1085: /* comp_hdr_field: "cpi"  */
#line 5449 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_CPI; }
#line 14897 "parser_bison.c"
    break;

  case 1086: /* udp_hdr_expr: "udp" udp_hdr_field  */
#line 5453 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 14905 "parser_bison.c"
    break;

  case 1087: /* udp_hdr_field: "sport"  */
#line 5458 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_SPORT; }
#line 14911 "parser_bison.c"
    break;

  case 1088: /* udp_hdr_field: "dport"  */
#line 5459 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_DPORT; }
#line 14917 "parser_bison.c"
    break;

  case 1089: /* udp_hdr_field: "length"  */
#line 5460 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_LENGTH; }
#line 14923 "parser_bison.c"
    break;

  case 1090: /* udp_hdr_field: "checksum"  */
#line 5461 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_CHECKSUM; }
#line 14929 "parser_bison.c"
    break;

  case 1091: /* udplite_hdr_expr: "udplite" udplite_hdr_field  */
#line 5465 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 14937 "parser_bison.c"
    break;

  case 1092: /* udplite_hdr_field: "sport"  */
#line 5470 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_SPORT; }
#line 14943 "parser_bison.c"
    break;

  case 1093: /* udplite_hdr_field: "dport"  */
#line 5471 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_DPORT; }
#line 14949 "parser_bison.c"
    break;

  case 1094: /* udplite_hdr_field: "csumcov"  */
#line 5472 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_LENGTH; }
#line 14955 "parser_bison.c"
    break;

  case 1095: /* udplite_hdr_field: "checksum"  */
#line 5473 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_CHECKSUM; }
#line 14961 "parser_bison.c"
    break;

  case 1096: /* tcp_hdr_expr: "tcp" tcp_hdr_field  */
#line 5477 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 14969 "parser_bison.c"
    break;

  case 1097: /* tcp_hdr_expr: "tcp" "option" tcp_hdr_option_type tcp_hdr_option_field  */
#line 5481 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 14977 "parser_bison.c"
    break;

  case 1098: /* tcp_hdr_expr: "tcp" "option" tcp_hdr_option_type  */
#line 5485 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPT_COMMON_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 14986 "parser_bison.c"
    break;

  case 1099: /* tcp_hdr_expr: "tcp" "option" "@" tcp_hdr_option_type "comma" "number" "comma" "number"  */
#line 5490 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-4].val), 0);
				tcpopt_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val), 0);
			}
#line 14995 "parser_bison.c"
    break;

  case 1100: /* tcp_hdr_field: "sport"  */
#line 5496 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_SPORT; }
#line 15001 "parser_bison.c"
    break;

  case 1101: /* tcp_hdr_field: "dport"  */
#line 5497 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_DPORT; }
#line 15007 "parser_bison.c"
    break;

  case 1102: /* tcp_hdr_field: "seq"  */
#line 5498 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_SEQ; }
#line 15013 "parser_bison.c"
    break;

  case 1103: /* tcp_hdr_field: "ackseq"  */
#line 5499 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_ACKSEQ; }
#line 15019 "parser_bison.c"
    break;

  case 1104: /* tcp_hdr_field: "doff"  */
#line 5500 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_DOFF; }
#line 15025 "parser_bison.c"
    break;

  case 1105: /* tcp_hdr_field: "reserved"  */
#line 5501 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_RESERVED; }
#line 15031 "parser_bison.c"
    break;

  case 1106: /* tcp_hdr_field: "flags"  */
#line 5502 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_FLAGS; }
#line 15037 "parser_bison.c"
    break;

  case 1107: /* tcp_hdr_field: "window"  */
#line 5503 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_WINDOW; }
#line 15043 "parser_bison.c"
    break;

  case 1108: /* tcp_hdr_field: "checksum"  */
#line 5504 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_CHECKSUM; }
#line 15049 "parser_bison.c"
    break;

  case 1109: /* tcp_hdr_field: "urgptr"  */
#line 5505 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_URGPTR; }
#line 15055 "parser_bison.c"
    break;

  case 1110: /* tcp_hdr_option_type: "eol"  */
#line 5508 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_EOL; }
#line 15061 "parser_bison.c"
    break;

  case 1111: /* tcp_hdr_option_type: "nop"  */
#line 5509 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_NOP; }
#line 15067 "parser_bison.c"
    break;

  case 1112: /* tcp_hdr_option_type: "mss"  */
#line 5510 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_MAXSEG; }
#line 15073 "parser_bison.c"
    break;

  case 1113: /* tcp_hdr_option_type: "window"  */
#line 5511 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_WINDOW; }
#line 15079 "parser_bison.c"
    break;

  case 1114: /* tcp_hdr_option_type: "sack-permitted"  */
#line 5512 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK_PERMITTED; }
#line 15085 "parser_bison.c"
    break;

  case 1115: /* tcp_hdr_option_type: "sack"  */
#line 5513 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK; }
#line 15091 "parser_bison.c"
    break;

  case 1116: /* tcp_hdr_option_type: "sack0"  */
#line 5514 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK; }
#line 15097 "parser_bison.c"
    break;

  case 1117: /* tcp_hdr_option_type: "sack1"  */
#line 5515 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK1; }
#line 15103 "parser_bison.c"
    break;

  case 1118: /* tcp_hdr_option_type: "sack2"  */
#line 5516 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK2; }
#line 15109 "parser_bison.c"
    break;

  case 1119: /* tcp_hdr_option_type: "sack3"  */
#line 5517 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK3; }
#line 15115 "parser_bison.c"
    break;

  case 1120: /* tcp_hdr_option_type: "echo"  */
#line 5518 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_ECHO; }
#line 15121 "parser_bison.c"
    break;

  case 1121: /* tcp_hdr_option_type: "timestamp"  */
#line 5519 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_TIMESTAMP; }
#line 15127 "parser_bison.c"
    break;

  case 1122: /* tcp_hdr_option_type: "number"  */
#line 5520 "parser_bison.y"
                                                {
				if ((yyvsp[0].val) > 255) {
					erec_queue(error(&(yylsp[0]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[0].val);
			}
#line 15139 "parser_bison.c"
    break;

  case 1123: /* tcp_hdr_option_field: "kind"  */
#line 5529 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_COMMON_KIND; }
#line 15145 "parser_bison.c"
    break;

  case 1124: /* tcp_hdr_option_field: "length"  */
#line 5530 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_COMMON_LENGTH; }
#line 15151 "parser_bison.c"
    break;

  case 1125: /* tcp_hdr_option_field: "size"  */
#line 5531 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_MAXSEG_SIZE; }
#line 15157 "parser_bison.c"
    break;

  case 1126: /* tcp_hdr_option_field: "count"  */
#line 5532 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_WINDOW_COUNT; }
#line 15163 "parser_bison.c"
    break;

  case 1127: /* tcp_hdr_option_field: "left"  */
#line 5533 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_SACK_LEFT; }
#line 15169 "parser_bison.c"
    break;

  case 1128: /* tcp_hdr_option_field: "right"  */
#line 5534 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_SACK_RIGHT; }
#line 15175 "parser_bison.c"
    break;

  case 1129: /* tcp_hdr_option_field: "tsval"  */
#line 5535 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_TS_TSVAL; }
#line 15181 "parser_bison.c"
    break;

  case 1130: /* tcp_hdr_option_field: "tsecr"  */
#line 5536 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_TS_TSECR; }
#line 15187 "parser_bison.c"
    break;

  case 1131: /* dccp_hdr_expr: "dccp" dccp_hdr_field  */
#line 5540 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 15195 "parser_bison.c"
    break;

  case 1132: /* dccp_hdr_field: "sport"  */
#line 5545 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_SPORT; }
#line 15201 "parser_bison.c"
    break;

  case 1133: /* dccp_hdr_field: "dport"  */
#line 5546 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_DPORT; }
#line 15207 "parser_bison.c"
    break;

  case 1134: /* dccp_hdr_field: "type"  */
#line 5547 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_TYPE; }
#line 15213 "parser_bison.c"
    break;

  case 1135: /* sctp_chunk_type: "data"  */
#line 5550 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_DATA; }
#line 15219 "parser_bison.c"
    break;

  case 1136: /* sctp_chunk_type: "init"  */
#line 5551 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_INIT; }
#line 15225 "parser_bison.c"
    break;

  case 1137: /* sctp_chunk_type: "init-ack"  */
#line 5552 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_INIT_ACK; }
#line 15231 "parser_bison.c"
    break;

  case 1138: /* sctp_chunk_type: "sack"  */
#line 5553 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SACK; }
#line 15237 "parser_bison.c"
    break;

  case 1139: /* sctp_chunk_type: "heartbeat"  */
#line 5554 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT; }
#line 15243 "parser_bison.c"
    break;

  case 1140: /* sctp_chunk_type: "heartbeat-ack"  */
#line 5555 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT_ACK; }
#line 15249 "parser_bison.c"
    break;

  case 1141: /* sctp_chunk_type: "abort"  */
#line 5556 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ABORT; }
#line 15255 "parser_bison.c"
    break;

  case 1142: /* sctp_chunk_type: "shutdown"  */
#line 5557 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN; }
#line 15261 "parser_bison.c"
    break;

  case 1143: /* sctp_chunk_type: "shutdown-ack"  */
#line 5558 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_ACK; }
#line 15267 "parser_bison.c"
    break;

  case 1144: /* sctp_chunk_type: "error"  */
#line 5559 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ERROR; }
#line 15273 "parser_bison.c"
    break;

  case 1145: /* sctp_chunk_type: "cookie-echo"  */
#line 5560 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ECHO; }
#line 15279 "parser_bison.c"
    break;

  case 1146: /* sctp_chunk_type: "cookie-ack"  */
#line 5561 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ACK; }
#line 15285 "parser_bison.c"
    break;

  case 1147: /* sctp_chunk_type: "ecne"  */
#line 5562 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ECNE; }
#line 15291 "parser_bison.c"
    break;

  case 1148: /* sctp_chunk_type: "cwr"  */
#line 5563 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_CWR; }
#line 15297 "parser_bison.c"
    break;

  case 1149: /* sctp_chunk_type: "shutdown-complete"  */
#line 5564 "parser_bison.y"
                                                  { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_COMPLETE; }
#line 15303 "parser_bison.c"
    break;

  case 1150: /* sctp_chunk_type: "asconf-ack"  */
#line 5565 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF_ACK; }
#line 15309 "parser_bison.c"
    break;

  case 1151: /* sctp_chunk_type: "forward-tsn"  */
#line 5566 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_FORWARD_TSN; }
#line 15315 "parser_bison.c"
    break;

  case 1152: /* sctp_chunk_type: "asconf"  */
#line 5567 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF; }
#line 15321 "parser_bison.c"
    break;

  case 1153: /* sctp_chunk_common_field: "type"  */
#line 5570 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_TYPE; }
#line 15327 "parser_bison.c"
    break;

  case 1154: /* sctp_chunk_common_field: "flags"  */
#line 5571 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_FLAGS; }
#line 15333 "parser_bison.c"
    break;

  case 1155: /* sctp_chunk_common_field: "length"  */
#line 5572 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_LENGTH; }
#line 15339 "parser_bison.c"
    break;

  case 1156: /* sctp_chunk_data_field: "tsn"  */
#line 5575 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_TSN; }
#line 15345 "parser_bison.c"
    break;

  case 1157: /* sctp_chunk_data_field: "stream"  */
#line 5576 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_STREAM; }
#line 15351 "parser_bison.c"
    break;

  case 1158: /* sctp_chunk_data_field: "ssn"  */
#line 5577 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_SSN; }
#line 15357 "parser_bison.c"
    break;

  case 1159: /* sctp_chunk_data_field: "ppid"  */
#line 5578 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_PPID; }
#line 15363 "parser_bison.c"
    break;

  case 1160: /* sctp_chunk_init_field: "init-tag"  */
#line 5581 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_TAG; }
#line 15369 "parser_bison.c"
    break;

  case 1161: /* sctp_chunk_init_field: "a-rwnd"  */
#line 5582 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_RWND; }
#line 15375 "parser_bison.c"
    break;

  case 1162: /* sctp_chunk_init_field: "num-outbound-streams"  */
#line 5583 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_OSTREAMS; }
#line 15381 "parser_bison.c"
    break;

  case 1163: /* sctp_chunk_init_field: "num-inbound-streams"  */
#line 5584 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_ISTREAMS; }
#line 15387 "parser_bison.c"
    break;

  case 1164: /* sctp_chunk_init_field: "initial-tsn"  */
#line 5585 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_TSN; }
#line 15393 "parser_bison.c"
    break;

  case 1165: /* sctp_chunk_sack_field: "cum-tsn-ack"  */
#line 5588 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_CTSN_ACK; }
#line 15399 "parser_bison.c"
    break;

  case 1166: /* sctp_chunk_sack_field: "a-rwnd"  */
#line 5589 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_RWND; }
#line 15405 "parser_bison.c"
    break;

  case 1167: /* sctp_chunk_sack_field: "num-gap-ack-blocks"  */
#line 5590 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_GACK_BLOCKS; }
#line 15411 "parser_bison.c"
    break;

  case 1168: /* sctp_chunk_sack_field: "num-dup-tsns"  */
#line 5591 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_DUP_TSNS; }
#line 15417 "parser_bison.c"
    break;

  case 1169: /* sctp_chunk_alloc: sctp_chunk_type  */
#line 5595 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[0].val), SCTP_CHUNK_COMMON_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 15426 "parser_bison.c"
    break;

  case 1170: /* sctp_chunk_alloc: sctp_chunk_type sctp_chunk_common_field  */
#line 5600 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 15434 "parser_bison.c"
    break;

  case 1171: /* sctp_chunk_alloc: "data" sctp_chunk_data_field  */
#line 5604 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_DATA, (yyvsp[0].val));
			}
#line 15442 "parser_bison.c"
    break;

  case 1172: /* sctp_chunk_alloc: "init" sctp_chunk_init_field  */
#line 5608 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT, (yyvsp[0].val));
			}
#line 15450 "parser_bison.c"
    break;

  case 1173: /* sctp_chunk_alloc: "init-ack" sctp_chunk_init_field  */
#line 5612 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT_ACK, (yyvsp[0].val));
			}
#line 15458 "parser_bison.c"
    break;

  case 1174: /* sctp_chunk_alloc: "sack" sctp_chunk_sack_field  */
#line 5616 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SACK, (yyvsp[0].val));
			}
#line 15466 "parser_bison.c"
    break;

  case 1175: /* sctp_chunk_alloc: "shutdown" "cum-tsn-ack"  */
#line 5620 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SHUTDOWN,
							   SCTP_CHUNK_SHUTDOWN_CTSN_ACK);
			}
#line 15475 "parser_bison.c"
    break;

  case 1176: /* sctp_chunk_alloc: "ecne" "lowest-tsn"  */
#line 5625 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ECNE,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 15484 "parser_bison.c"
    break;

  case 1177: /* sctp_chunk_alloc: "cwr" "lowest-tsn"  */
#line 5630 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_CWR,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 15493 "parser_bison.c"
    break;

  case 1178: /* sctp_chunk_alloc: "asconf-ack" "seqno"  */
#line 5635 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF_ACK,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 15502 "parser_bison.c"
    break;

  case 1179: /* sctp_chunk_alloc: "forward-tsn" "new-cum-tsn"  */
#line 5640 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_FORWARD_TSN,
							   SCTP_CHUNK_FORWARD_TSN_NCTSN);
			}
#line 15511 "parser_bison.c"
    break;

  case 1180: /* sctp_chunk_alloc: "asconf" "seqno"  */
#line 5645 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 15520 "parser_bison.c"
    break;

  case 1181: /* sctp_hdr_expr: "sctp" sctp_hdr_field close_scope_sctp  */
#line 5652 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[-1].val));
			}
#line 15528 "parser_bison.c"
    break;

  case 1182: /* sctp_hdr_expr: "sctp" "chunk" sctp_chunk_alloc close_scope_sctp_chunk close_scope_sctp  */
#line 5656 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 15536 "parser_bison.c"
    break;

  case 1183: /* sctp_hdr_field: "sport"  */
#line 5661 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_SPORT; }
#line 15542 "parser_bison.c"
    break;

  case 1184: /* sctp_hdr_field: "dport"  */
#line 5662 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_DPORT; }
#line 15548 "parser_bison.c"
    break;

  case 1185: /* sctp_hdr_field: "vtag"  */
#line 5663 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_VTAG; }
#line 15554 "parser_bison.c"
    break;

  case 1186: /* sctp_hdr_field: "checksum"  */
#line 5664 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 15560 "parser_bison.c"
    break;

  case 1187: /* th_hdr_expr: "th" th_hdr_field  */
#line 5668 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[0].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 15570 "parser_bison.c"
    break;

  case 1188: /* th_hdr_field: "sport"  */
#line 5675 "parser_bison.y"
                                                { (yyval.val) = THDR_SPORT; }
#line 15576 "parser_bison.c"
    break;

  case 1189: /* th_hdr_field: "dport"  */
#line 5676 "parser_bison.y"
                                                { (yyval.val) = THDR_DPORT; }
#line 15582 "parser_bison.c"
    break;

  case 1198: /* hbh_hdr_expr: "hbh" hbh_hdr_field  */
#line 5690 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 15590 "parser_bison.c"
    break;

  case 1199: /* hbh_hdr_field: "nexthdr"  */
#line 5695 "parser_bison.y"
                                                { (yyval.val) = HBHHDR_NEXTHDR; }
#line 15596 "parser_bison.c"
    break;

  case 1200: /* hbh_hdr_field: "hdrlength"  */
#line 5696 "parser_bison.y"
                                                { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 15602 "parser_bison.c"
    break;

  case 1201: /* rt_hdr_expr: "rt" rt_hdr_field close_scope_rt  */
#line 5700 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[-1].val));
			}
#line 15610 "parser_bison.c"
    break;

  case 1202: /* rt_hdr_field: "nexthdr"  */
#line 5705 "parser_bison.y"
                                                { (yyval.val) = RTHDR_NEXTHDR; }
#line 15616 "parser_bison.c"
    break;

  case 1203: /* rt_hdr_field: "hdrlength"  */
#line 5706 "parser_bison.y"
                                                { (yyval.val) = RTHDR_HDRLENGTH; }
#line 15622 "parser_bison.c"
    break;

  case 1204: /* rt_hdr_field: "type"  */
#line 5707 "parser_bison.y"
                                                { (yyval.val) = RTHDR_TYPE; }
#line 15628 "parser_bison.c"
    break;

  case 1205: /* rt_hdr_field: "seg-left"  */
#line 5708 "parser_bison.y"
                                                { (yyval.val) = RTHDR_SEG_LEFT; }
#line 15634 "parser_bison.c"
    break;

  case 1206: /* rt0_hdr_expr: "rt0" rt0_hdr_field  */
#line 5712 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 15642 "parser_bison.c"
    break;

  case 1207: /* rt0_hdr_field: "addr" '[' "number" ']'  */
#line 5718 "parser_bison.y"
                        {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 15650 "parser_bison.c"
    break;

  case 1208: /* rt2_hdr_expr: "rt2" rt2_hdr_field  */
#line 5724 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 15658 "parser_bison.c"
    break;

  case 1209: /* rt2_hdr_field: "addr"  */
#line 5729 "parser_bison.y"
                                                { (yyval.val) = RT2HDR_ADDR; }
#line 15664 "parser_bison.c"
    break;

  case 1210: /* rt4_hdr_expr: "srh" rt4_hdr_field  */
#line 5733 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 15672 "parser_bison.c"
    break;

  case 1211: /* rt4_hdr_field: "last-entry"  */
#line 5738 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_LASTENT; }
#line 15678 "parser_bison.c"
    break;

  case 1212: /* rt4_hdr_field: "flags"  */
#line 5739 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_FLAGS; }
#line 15684 "parser_bison.c"
    break;

  case 1213: /* rt4_hdr_field: "tag"  */
#line 5740 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_TAG; }
#line 15690 "parser_bison.c"
    break;

  case 1214: /* rt4_hdr_field: "sid" '[' "number" ']'  */
#line 5742 "parser_bison.y"
                        {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 15698 "parser_bison.c"
    break;

  case 1215: /* frag_hdr_expr: "frag" frag_hdr_field  */
#line 5748 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 15706 "parser_bison.c"
    break;

  case 1216: /* frag_hdr_field: "nexthdr"  */
#line 5753 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 15712 "parser_bison.c"
    break;

  case 1217: /* frag_hdr_field: "reserved"  */
#line 5754 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_RESERVED; }
#line 15718 "parser_bison.c"
    break;

  case 1218: /* frag_hdr_field: "frag-off"  */
#line 5755 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 15724 "parser_bison.c"
    break;

  case 1219: /* frag_hdr_field: "reserved2"  */
#line 5756 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_RESERVED2; }
#line 15730 "parser_bison.c"
    break;

  case 1220: /* frag_hdr_field: "more-fragments"  */
#line 5757 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_MFRAGS; }
#line 15736 "parser_bison.c"
    break;

  case 1221: /* frag_hdr_field: "id"  */
#line 5758 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_ID; }
#line 15742 "parser_bison.c"
    break;

  case 1222: /* dst_hdr_expr: "dst" dst_hdr_field  */
#line 5762 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 15750 "parser_bison.c"
    break;

  case 1223: /* dst_hdr_field: "nexthdr"  */
#line 5767 "parser_bison.y"
                                                { (yyval.val) = DSTHDR_NEXTHDR; }
#line 15756 "parser_bison.c"
    break;

  case 1224: /* dst_hdr_field: "hdrlength"  */
#line 5768 "parser_bison.y"
                                                { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 15762 "parser_bison.c"
    break;

  case 1225: /* mh_hdr_expr: "mh" mh_hdr_field  */
#line 5772 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 15770 "parser_bison.c"
    break;

  case 1226: /* mh_hdr_field: "nexthdr"  */
#line 5777 "parser_bison.y"
                                                { (yyval.val) = MHHDR_NEXTHDR; }
#line 15776 "parser_bison.c"
    break;

  case 1227: /* mh_hdr_field: "hdrlength"  */
#line 5778 "parser_bison.y"
                                                { (yyval.val) = MHHDR_HDRLENGTH; }
#line 15782 "parser_bison.c"
    break;

  case 1228: /* mh_hdr_field: "type"  */
#line 5779 "parser_bison.y"
                                                { (yyval.val) = MHHDR_TYPE; }
#line 15788 "parser_bison.c"
    break;

  case 1229: /* mh_hdr_field: "reserved"  */
#line 5780 "parser_bison.y"
                                                { (yyval.val) = MHHDR_RESERVED; }
#line 15794 "parser_bison.c"
    break;

  case 1230: /* mh_hdr_field: "checksum"  */
#line 5781 "parser_bison.y"
                                                { (yyval.val) = MHHDR_CHECKSUM; }
#line 15800 "parser_bison.c"
    break;

  case 1231: /* exthdr_exists_expr: "exthdr" exthdr_key  */
#line 5785 "parser_bison.y"
                        {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 15816 "parser_bison.c"
    break;

  case 1232: /* exthdr_key: "hbh"  */
#line 5798 "parser_bison.y"
                                        { (yyval.val) = IPPROTO_HOPOPTS; }
#line 15822 "parser_bison.c"
    break;

  case 1233: /* exthdr_key: "rt" close_scope_rt  */
#line 5799 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_ROUTING; }
#line 15828 "parser_bison.c"
    break;

  case 1234: /* exthdr_key: "frag"  */
#line 5800 "parser_bison.y"
                                        { (yyval.val) = IPPROTO_FRAGMENT; }
#line 15834 "parser_bison.c"
    break;

  case 1235: /* exthdr_key: "dst"  */
#line 5801 "parser_bison.y"
                                        { (yyval.val) = IPPROTO_DSTOPTS; }
#line 15840 "parser_bison.c"
    break;

  case 1236: /* exthdr_key: "mh"  */
#line 5802 "parser_bison.y"
                                        { (yyval.val) = IPPROTO_MH; }
#line 15846 "parser_bison.c"
    break;


#line 15850 "parser_bison.c"

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

#line 5805 "parser_bison.y"

