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
    MPTCP = 433,                   /* "mptcp"  */
    NOP = 434,                     /* "nop"  */
    SACK = 435,                    /* "sack"  */
    SACK0 = 436,                   /* "sack0"  */
    SACK1 = 437,                   /* "sack1"  */
    SACK2 = 438,                   /* "sack2"  */
    SACK3 = 439,                   /* "sack3"  */
    SACK_PERM = 440,               /* "sack-permitted"  */
    FASTOPEN = 441,                /* "fastopen"  */
    MD5SIG = 442,                  /* "md5sig"  */
    TIMESTAMP = 443,               /* "timestamp"  */
    COUNT = 444,                   /* "count"  */
    LEFT = 445,                    /* "left"  */
    RIGHT = 446,                   /* "right"  */
    TSVAL = 447,                   /* "tsval"  */
    TSECR = 448,                   /* "tsecr"  */
    SUBTYPE = 449,                 /* "subtype"  */
    DCCP = 450,                    /* "dccp"  */
    SCTP = 451,                    /* "sctp"  */
    CHUNK = 452,                   /* "chunk"  */
    DATA = 453,                    /* "data"  */
    INIT = 454,                    /* "init"  */
    INIT_ACK = 455,                /* "init-ack"  */
    HEARTBEAT = 456,               /* "heartbeat"  */
    HEARTBEAT_ACK = 457,           /* "heartbeat-ack"  */
    ABORT = 458,                   /* "abort"  */
    SHUTDOWN = 459,                /* "shutdown"  */
    SHUTDOWN_ACK = 460,            /* "shutdown-ack"  */
    ERROR = 461,                   /* "error"  */
    COOKIE_ECHO = 462,             /* "cookie-echo"  */
    COOKIE_ACK = 463,              /* "cookie-ack"  */
    ECNE = 464,                    /* "ecne"  */
    CWR = 465,                     /* "cwr"  */
    SHUTDOWN_COMPLETE = 466,       /* "shutdown-complete"  */
    ASCONF_ACK = 467,              /* "asconf-ack"  */
    FORWARD_TSN = 468,             /* "forward-tsn"  */
    ASCONF = 469,                  /* "asconf"  */
    TSN = 470,                     /* "tsn"  */
    STREAM = 471,                  /* "stream"  */
    SSN = 472,                     /* "ssn"  */
    PPID = 473,                    /* "ppid"  */
    INIT_TAG = 474,                /* "init-tag"  */
    A_RWND = 475,                  /* "a-rwnd"  */
    NUM_OSTREAMS = 476,            /* "num-outbound-streams"  */
    NUM_ISTREAMS = 477,            /* "num-inbound-streams"  */
    INIT_TSN = 478,                /* "initial-tsn"  */
    CUM_TSN_ACK = 479,             /* "cum-tsn-ack"  */
    NUM_GACK_BLOCKS = 480,         /* "num-gap-ack-blocks"  */
    NUM_DUP_TSNS = 481,            /* "num-dup-tsns"  */
    LOWEST_TSN = 482,              /* "lowest-tsn"  */
    SEQNO = 483,                   /* "seqno"  */
    NEW_CUM_TSN = 484,             /* "new-cum-tsn"  */
    VTAG = 485,                    /* "vtag"  */
    RT = 486,                      /* "rt"  */
    RT0 = 487,                     /* "rt0"  */
    RT2 = 488,                     /* "rt2"  */
    RT4 = 489,                     /* "srh"  */
    SEG_LEFT = 490,                /* "seg-left"  */
    ADDR = 491,                    /* "addr"  */
    LAST_ENT = 492,                /* "last-entry"  */
    TAG = 493,                     /* "tag"  */
    SID = 494,                     /* "sid"  */
    HBH = 495,                     /* "hbh"  */
    FRAG = 496,                    /* "frag"  */
    RESERVED2 = 497,               /* "reserved2"  */
    MORE_FRAGMENTS = 498,          /* "more-fragments"  */
    DST = 499,                     /* "dst"  */
    MH = 500,                      /* "mh"  */
    META = 501,                    /* "meta"  */
    MARK = 502,                    /* "mark"  */
    IIF = 503,                     /* "iif"  */
    IIFNAME = 504,                 /* "iifname"  */
    IIFTYPE = 505,                 /* "iiftype"  */
    OIF = 506,                     /* "oif"  */
    OIFNAME = 507,                 /* "oifname"  */
    OIFTYPE = 508,                 /* "oiftype"  */
    SKUID = 509,                   /* "skuid"  */
    SKGID = 510,                   /* "skgid"  */
    NFTRACE = 511,                 /* "nftrace"  */
    RTCLASSID = 512,               /* "rtclassid"  */
    IBRIPORT = 513,                /* "ibriport"  */
    OBRIPORT = 514,                /* "obriport"  */
    IBRIDGENAME = 515,             /* "ibrname"  */
    OBRIDGENAME = 516,             /* "obrname"  */
    PKTTYPE = 517,                 /* "pkttype"  */
    CPU = 518,                     /* "cpu"  */
    IIFGROUP = 519,                /* "iifgroup"  */
    OIFGROUP = 520,                /* "oifgroup"  */
    CGROUP = 521,                  /* "cgroup"  */
    TIME = 522,                    /* "time"  */
    CLASSID = 523,                 /* "classid"  */
    NEXTHOP = 524,                 /* "nexthop"  */
    CT = 525,                      /* "ct"  */
    L3PROTOCOL = 526,              /* "l3proto"  */
    PROTO_SRC = 527,               /* "proto-src"  */
    PROTO_DST = 528,               /* "proto-dst"  */
    ZONE = 529,                    /* "zone"  */
    DIRECTION = 530,               /* "direction"  */
    EVENT = 531,                   /* "event"  */
    EXPECTATION = 532,             /* "expectation"  */
    EXPIRATION = 533,              /* "expiration"  */
    HELPER = 534,                  /* "helper"  */
    LABEL = 535,                   /* "label"  */
    STATE = 536,                   /* "state"  */
    STATUS = 537,                  /* "status"  */
    ORIGINAL = 538,                /* "original"  */
    REPLY = 539,                   /* "reply"  */
    COUNTER = 540,                 /* "counter"  */
    NAME = 541,                    /* "name"  */
    PACKETS = 542,                 /* "packets"  */
    BYTES = 543,                   /* "bytes"  */
    AVGPKT = 544,                  /* "avgpkt"  */
    COUNTERS = 545,                /* "counters"  */
    QUOTAS = 546,                  /* "quotas"  */
    LIMITS = 547,                  /* "limits"  */
    SYNPROXYS = 548,               /* "synproxys"  */
    HELPERS = 549,                 /* "helpers"  */
    LOG = 550,                     /* "log"  */
    PREFIX = 551,                  /* "prefix"  */
    GROUP = 552,                   /* "group"  */
    SNAPLEN = 553,                 /* "snaplen"  */
    QUEUE_THRESHOLD = 554,         /* "queue-threshold"  */
    LEVEL = 555,                   /* "level"  */
    LIMIT = 556,                   /* "limit"  */
    RATE = 557,                    /* "rate"  */
    BURST = 558,                   /* "burst"  */
    OVER = 559,                    /* "over"  */
    UNTIL = 560,                   /* "until"  */
    QUOTA = 561,                   /* "quota"  */
    USED = 562,                    /* "used"  */
    SECMARK = 563,                 /* "secmark"  */
    SECMARKS = 564,                /* "secmarks"  */
    SECOND = 565,                  /* "second"  */
    MINUTE = 566,                  /* "minute"  */
    HOUR = 567,                    /* "hour"  */
    DAY = 568,                     /* "day"  */
    WEEK = 569,                    /* "week"  */
    _REJECT = 570,                 /* "reject"  */
    WITH = 571,                    /* "with"  */
    ICMPX = 572,                   /* "icmpx"  */
    SNAT = 573,                    /* "snat"  */
    DNAT = 574,                    /* "dnat"  */
    MASQUERADE = 575,              /* "masquerade"  */
    REDIRECT = 576,                /* "redirect"  */
    RANDOM = 577,                  /* "random"  */
    FULLY_RANDOM = 578,            /* "fully-random"  */
    PERSISTENT = 579,              /* "persistent"  */
    QUEUE = 580,                   /* "queue"  */
    QUEUENUM = 581,                /* "num"  */
    BYPASS = 582,                  /* "bypass"  */
    FANOUT = 583,                  /* "fanout"  */
    DUP = 584,                     /* "dup"  */
    FWD = 585,                     /* "fwd"  */
    NUMGEN = 586,                  /* "numgen"  */
    INC = 587,                     /* "inc"  */
    MOD = 588,                     /* "mod"  */
    OFFSET = 589,                  /* "offset"  */
    JHASH = 590,                   /* "jhash"  */
    SYMHASH = 591,                 /* "symhash"  */
    SEED = 592,                    /* "seed"  */
    POSITION = 593,                /* "position"  */
    INDEX = 594,                   /* "index"  */
    COMMENT = 595,                 /* "comment"  */
    XML = 596,                     /* "xml"  */
    JSON = 597,                    /* "json"  */
    VM = 598,                      /* "vm"  */
    NOTRACK = 599,                 /* "notrack"  */
    EXISTS = 600,                  /* "exists"  */
    MISSING = 601,                 /* "missing"  */
    EXTHDR = 602,                  /* "exthdr"  */
    IPSEC = 603,                   /* "ipsec"  */
    REQID = 604,                   /* "reqid"  */
    SPNUM = 605,                   /* "spnum"  */
    IN = 606,                      /* "in"  */
    OUT = 607                      /* "out"  */
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
#define MPTCP 433
#define NOP 434
#define SACK 435
#define SACK0 436
#define SACK1 437
#define SACK2 438
#define SACK3 439
#define SACK_PERM 440
#define FASTOPEN 441
#define MD5SIG 442
#define TIMESTAMP 443
#define COUNT 444
#define LEFT 445
#define RIGHT 446
#define TSVAL 447
#define TSECR 448
#define SUBTYPE 449
#define DCCP 450
#define SCTP 451
#define CHUNK 452
#define DATA 453
#define INIT 454
#define INIT_ACK 455
#define HEARTBEAT 456
#define HEARTBEAT_ACK 457
#define ABORT 458
#define SHUTDOWN 459
#define SHUTDOWN_ACK 460
#define ERROR 461
#define COOKIE_ECHO 462
#define COOKIE_ACK 463
#define ECNE 464
#define CWR 465
#define SHUTDOWN_COMPLETE 466
#define ASCONF_ACK 467
#define FORWARD_TSN 468
#define ASCONF 469
#define TSN 470
#define STREAM 471
#define SSN 472
#define PPID 473
#define INIT_TAG 474
#define A_RWND 475
#define NUM_OSTREAMS 476
#define NUM_ISTREAMS 477
#define INIT_TSN 478
#define CUM_TSN_ACK 479
#define NUM_GACK_BLOCKS 480
#define NUM_DUP_TSNS 481
#define LOWEST_TSN 482
#define SEQNO 483
#define NEW_CUM_TSN 484
#define VTAG 485
#define RT 486
#define RT0 487
#define RT2 488
#define RT4 489
#define SEG_LEFT 490
#define ADDR 491
#define LAST_ENT 492
#define TAG 493
#define SID 494
#define HBH 495
#define FRAG 496
#define RESERVED2 497
#define MORE_FRAGMENTS 498
#define DST 499
#define MH 500
#define META 501
#define MARK 502
#define IIF 503
#define IIFNAME 504
#define IIFTYPE 505
#define OIF 506
#define OIFNAME 507
#define OIFTYPE 508
#define SKUID 509
#define SKGID 510
#define NFTRACE 511
#define RTCLASSID 512
#define IBRIPORT 513
#define OBRIPORT 514
#define IBRIDGENAME 515
#define OBRIDGENAME 516
#define PKTTYPE 517
#define CPU 518
#define IIFGROUP 519
#define OIFGROUP 520
#define CGROUP 521
#define TIME 522
#define CLASSID 523
#define NEXTHOP 524
#define CT 525
#define L3PROTOCOL 526
#define PROTO_SRC 527
#define PROTO_DST 528
#define ZONE 529
#define DIRECTION 530
#define EVENT 531
#define EXPECTATION 532
#define EXPIRATION 533
#define HELPER 534
#define LABEL 535
#define STATE 536
#define STATUS 537
#define ORIGINAL 538
#define REPLY 539
#define COUNTER 540
#define NAME 541
#define PACKETS 542
#define BYTES 543
#define AVGPKT 544
#define COUNTERS 545
#define QUOTAS 546
#define LIMITS 547
#define SYNPROXYS 548
#define HELPERS 549
#define LOG 550
#define PREFIX 551
#define GROUP 552
#define SNAPLEN 553
#define QUEUE_THRESHOLD 554
#define LEVEL 555
#define LIMIT 556
#define RATE 557
#define BURST 558
#define OVER 559
#define UNTIL 560
#define QUOTA 561
#define USED 562
#define SECMARK 563
#define SECMARKS 564
#define SECOND 565
#define MINUTE 566
#define HOUR 567
#define DAY 568
#define WEEK 569
#define _REJECT 570
#define WITH 571
#define ICMPX 572
#define SNAT 573
#define DNAT 574
#define MASQUERADE 575
#define REDIRECT 576
#define RANDOM 577
#define FULLY_RANDOM 578
#define PERSISTENT 579
#define QUEUE 580
#define QUEUENUM 581
#define BYPASS 582
#define FANOUT 583
#define DUP 584
#define FWD 585
#define NUMGEN 586
#define INC 587
#define MOD 588
#define OFFSET 589
#define JHASH 590
#define SYMHASH 591
#define SEED 592
#define POSITION 593
#define INDEX 594
#define COMMENT 595
#define XML 596
#define JSON 597
#define VM 598
#define NOTRACK 599
#define EXISTS 600
#define MISSING 601
#define EXTHDR 602
#define IPSEC 603
#define REQID 604
#define SPNUM 605
#define IN 606
#define OUT 607

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
	struct tcp_kind_field {
		uint16_t kind; /* must allow > 255 for SACK1, 2.. hack */
		uint8_t field;
	} tcp_kind_field;

#line 998 "parser_bison.c"

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
  YYSYMBOL_MPTCP = 178,                    /* "mptcp"  */
  YYSYMBOL_NOP = 179,                      /* "nop"  */
  YYSYMBOL_SACK = 180,                     /* "sack"  */
  YYSYMBOL_SACK0 = 181,                    /* "sack0"  */
  YYSYMBOL_SACK1 = 182,                    /* "sack1"  */
  YYSYMBOL_SACK2 = 183,                    /* "sack2"  */
  YYSYMBOL_SACK3 = 184,                    /* "sack3"  */
  YYSYMBOL_SACK_PERM = 185,                /* "sack-permitted"  */
  YYSYMBOL_FASTOPEN = 186,                 /* "fastopen"  */
  YYSYMBOL_MD5SIG = 187,                   /* "md5sig"  */
  YYSYMBOL_TIMESTAMP = 188,                /* "timestamp"  */
  YYSYMBOL_COUNT = 189,                    /* "count"  */
  YYSYMBOL_LEFT = 190,                     /* "left"  */
  YYSYMBOL_RIGHT = 191,                    /* "right"  */
  YYSYMBOL_TSVAL = 192,                    /* "tsval"  */
  YYSYMBOL_TSECR = 193,                    /* "tsecr"  */
  YYSYMBOL_SUBTYPE = 194,                  /* "subtype"  */
  YYSYMBOL_DCCP = 195,                     /* "dccp"  */
  YYSYMBOL_SCTP = 196,                     /* "sctp"  */
  YYSYMBOL_CHUNK = 197,                    /* "chunk"  */
  YYSYMBOL_DATA = 198,                     /* "data"  */
  YYSYMBOL_INIT = 199,                     /* "init"  */
  YYSYMBOL_INIT_ACK = 200,                 /* "init-ack"  */
  YYSYMBOL_HEARTBEAT = 201,                /* "heartbeat"  */
  YYSYMBOL_HEARTBEAT_ACK = 202,            /* "heartbeat-ack"  */
  YYSYMBOL_ABORT = 203,                    /* "abort"  */
  YYSYMBOL_SHUTDOWN = 204,                 /* "shutdown"  */
  YYSYMBOL_SHUTDOWN_ACK = 205,             /* "shutdown-ack"  */
  YYSYMBOL_ERROR = 206,                    /* "error"  */
  YYSYMBOL_COOKIE_ECHO = 207,              /* "cookie-echo"  */
  YYSYMBOL_COOKIE_ACK = 208,               /* "cookie-ack"  */
  YYSYMBOL_ECNE = 209,                     /* "ecne"  */
  YYSYMBOL_CWR = 210,                      /* "cwr"  */
  YYSYMBOL_SHUTDOWN_COMPLETE = 211,        /* "shutdown-complete"  */
  YYSYMBOL_ASCONF_ACK = 212,               /* "asconf-ack"  */
  YYSYMBOL_FORWARD_TSN = 213,              /* "forward-tsn"  */
  YYSYMBOL_ASCONF = 214,                   /* "asconf"  */
  YYSYMBOL_TSN = 215,                      /* "tsn"  */
  YYSYMBOL_STREAM = 216,                   /* "stream"  */
  YYSYMBOL_SSN = 217,                      /* "ssn"  */
  YYSYMBOL_PPID = 218,                     /* "ppid"  */
  YYSYMBOL_INIT_TAG = 219,                 /* "init-tag"  */
  YYSYMBOL_A_RWND = 220,                   /* "a-rwnd"  */
  YYSYMBOL_NUM_OSTREAMS = 221,             /* "num-outbound-streams"  */
  YYSYMBOL_NUM_ISTREAMS = 222,             /* "num-inbound-streams"  */
  YYSYMBOL_INIT_TSN = 223,                 /* "initial-tsn"  */
  YYSYMBOL_CUM_TSN_ACK = 224,              /* "cum-tsn-ack"  */
  YYSYMBOL_NUM_GACK_BLOCKS = 225,          /* "num-gap-ack-blocks"  */
  YYSYMBOL_NUM_DUP_TSNS = 226,             /* "num-dup-tsns"  */
  YYSYMBOL_LOWEST_TSN = 227,               /* "lowest-tsn"  */
  YYSYMBOL_SEQNO = 228,                    /* "seqno"  */
  YYSYMBOL_NEW_CUM_TSN = 229,              /* "new-cum-tsn"  */
  YYSYMBOL_VTAG = 230,                     /* "vtag"  */
  YYSYMBOL_RT = 231,                       /* "rt"  */
  YYSYMBOL_RT0 = 232,                      /* "rt0"  */
  YYSYMBOL_RT2 = 233,                      /* "rt2"  */
  YYSYMBOL_RT4 = 234,                      /* "srh"  */
  YYSYMBOL_SEG_LEFT = 235,                 /* "seg-left"  */
  YYSYMBOL_ADDR = 236,                     /* "addr"  */
  YYSYMBOL_LAST_ENT = 237,                 /* "last-entry"  */
  YYSYMBOL_TAG = 238,                      /* "tag"  */
  YYSYMBOL_SID = 239,                      /* "sid"  */
  YYSYMBOL_HBH = 240,                      /* "hbh"  */
  YYSYMBOL_FRAG = 241,                     /* "frag"  */
  YYSYMBOL_RESERVED2 = 242,                /* "reserved2"  */
  YYSYMBOL_MORE_FRAGMENTS = 243,           /* "more-fragments"  */
  YYSYMBOL_DST = 244,                      /* "dst"  */
  YYSYMBOL_MH = 245,                       /* "mh"  */
  YYSYMBOL_META = 246,                     /* "meta"  */
  YYSYMBOL_MARK = 247,                     /* "mark"  */
  YYSYMBOL_IIF = 248,                      /* "iif"  */
  YYSYMBOL_IIFNAME = 249,                  /* "iifname"  */
  YYSYMBOL_IIFTYPE = 250,                  /* "iiftype"  */
  YYSYMBOL_OIF = 251,                      /* "oif"  */
  YYSYMBOL_OIFNAME = 252,                  /* "oifname"  */
  YYSYMBOL_OIFTYPE = 253,                  /* "oiftype"  */
  YYSYMBOL_SKUID = 254,                    /* "skuid"  */
  YYSYMBOL_SKGID = 255,                    /* "skgid"  */
  YYSYMBOL_NFTRACE = 256,                  /* "nftrace"  */
  YYSYMBOL_RTCLASSID = 257,                /* "rtclassid"  */
  YYSYMBOL_IBRIPORT = 258,                 /* "ibriport"  */
  YYSYMBOL_OBRIPORT = 259,                 /* "obriport"  */
  YYSYMBOL_IBRIDGENAME = 260,              /* "ibrname"  */
  YYSYMBOL_OBRIDGENAME = 261,              /* "obrname"  */
  YYSYMBOL_PKTTYPE = 262,                  /* "pkttype"  */
  YYSYMBOL_CPU = 263,                      /* "cpu"  */
  YYSYMBOL_IIFGROUP = 264,                 /* "iifgroup"  */
  YYSYMBOL_OIFGROUP = 265,                 /* "oifgroup"  */
  YYSYMBOL_CGROUP = 266,                   /* "cgroup"  */
  YYSYMBOL_TIME = 267,                     /* "time"  */
  YYSYMBOL_CLASSID = 268,                  /* "classid"  */
  YYSYMBOL_NEXTHOP = 269,                  /* "nexthop"  */
  YYSYMBOL_CT = 270,                       /* "ct"  */
  YYSYMBOL_L3PROTOCOL = 271,               /* "l3proto"  */
  YYSYMBOL_PROTO_SRC = 272,                /* "proto-src"  */
  YYSYMBOL_PROTO_DST = 273,                /* "proto-dst"  */
  YYSYMBOL_ZONE = 274,                     /* "zone"  */
  YYSYMBOL_DIRECTION = 275,                /* "direction"  */
  YYSYMBOL_EVENT = 276,                    /* "event"  */
  YYSYMBOL_EXPECTATION = 277,              /* "expectation"  */
  YYSYMBOL_EXPIRATION = 278,               /* "expiration"  */
  YYSYMBOL_HELPER = 279,                   /* "helper"  */
  YYSYMBOL_LABEL = 280,                    /* "label"  */
  YYSYMBOL_STATE = 281,                    /* "state"  */
  YYSYMBOL_STATUS = 282,                   /* "status"  */
  YYSYMBOL_ORIGINAL = 283,                 /* "original"  */
  YYSYMBOL_REPLY = 284,                    /* "reply"  */
  YYSYMBOL_COUNTER = 285,                  /* "counter"  */
  YYSYMBOL_NAME = 286,                     /* "name"  */
  YYSYMBOL_PACKETS = 287,                  /* "packets"  */
  YYSYMBOL_BYTES = 288,                    /* "bytes"  */
  YYSYMBOL_AVGPKT = 289,                   /* "avgpkt"  */
  YYSYMBOL_COUNTERS = 290,                 /* "counters"  */
  YYSYMBOL_QUOTAS = 291,                   /* "quotas"  */
  YYSYMBOL_LIMITS = 292,                   /* "limits"  */
  YYSYMBOL_SYNPROXYS = 293,                /* "synproxys"  */
  YYSYMBOL_HELPERS = 294,                  /* "helpers"  */
  YYSYMBOL_LOG = 295,                      /* "log"  */
  YYSYMBOL_PREFIX = 296,                   /* "prefix"  */
  YYSYMBOL_GROUP = 297,                    /* "group"  */
  YYSYMBOL_SNAPLEN = 298,                  /* "snaplen"  */
  YYSYMBOL_QUEUE_THRESHOLD = 299,          /* "queue-threshold"  */
  YYSYMBOL_LEVEL = 300,                    /* "level"  */
  YYSYMBOL_LIMIT = 301,                    /* "limit"  */
  YYSYMBOL_RATE = 302,                     /* "rate"  */
  YYSYMBOL_BURST = 303,                    /* "burst"  */
  YYSYMBOL_OVER = 304,                     /* "over"  */
  YYSYMBOL_UNTIL = 305,                    /* "until"  */
  YYSYMBOL_QUOTA = 306,                    /* "quota"  */
  YYSYMBOL_USED = 307,                     /* "used"  */
  YYSYMBOL_SECMARK = 308,                  /* "secmark"  */
  YYSYMBOL_SECMARKS = 309,                 /* "secmarks"  */
  YYSYMBOL_SECOND = 310,                   /* "second"  */
  YYSYMBOL_MINUTE = 311,                   /* "minute"  */
  YYSYMBOL_HOUR = 312,                     /* "hour"  */
  YYSYMBOL_DAY = 313,                      /* "day"  */
  YYSYMBOL_WEEK = 314,                     /* "week"  */
  YYSYMBOL__REJECT = 315,                  /* "reject"  */
  YYSYMBOL_WITH = 316,                     /* "with"  */
  YYSYMBOL_ICMPX = 317,                    /* "icmpx"  */
  YYSYMBOL_SNAT = 318,                     /* "snat"  */
  YYSYMBOL_DNAT = 319,                     /* "dnat"  */
  YYSYMBOL_MASQUERADE = 320,               /* "masquerade"  */
  YYSYMBOL_REDIRECT = 321,                 /* "redirect"  */
  YYSYMBOL_RANDOM = 322,                   /* "random"  */
  YYSYMBOL_FULLY_RANDOM = 323,             /* "fully-random"  */
  YYSYMBOL_PERSISTENT = 324,               /* "persistent"  */
  YYSYMBOL_QUEUE = 325,                    /* "queue"  */
  YYSYMBOL_QUEUENUM = 326,                 /* "num"  */
  YYSYMBOL_BYPASS = 327,                   /* "bypass"  */
  YYSYMBOL_FANOUT = 328,                   /* "fanout"  */
  YYSYMBOL_DUP = 329,                      /* "dup"  */
  YYSYMBOL_FWD = 330,                      /* "fwd"  */
  YYSYMBOL_NUMGEN = 331,                   /* "numgen"  */
  YYSYMBOL_INC = 332,                      /* "inc"  */
  YYSYMBOL_MOD = 333,                      /* "mod"  */
  YYSYMBOL_OFFSET = 334,                   /* "offset"  */
  YYSYMBOL_JHASH = 335,                    /* "jhash"  */
  YYSYMBOL_SYMHASH = 336,                  /* "symhash"  */
  YYSYMBOL_SEED = 337,                     /* "seed"  */
  YYSYMBOL_POSITION = 338,                 /* "position"  */
  YYSYMBOL_INDEX = 339,                    /* "index"  */
  YYSYMBOL_COMMENT = 340,                  /* "comment"  */
  YYSYMBOL_XML = 341,                      /* "xml"  */
  YYSYMBOL_JSON = 342,                     /* "json"  */
  YYSYMBOL_VM = 343,                       /* "vm"  */
  YYSYMBOL_NOTRACK = 344,                  /* "notrack"  */
  YYSYMBOL_EXISTS = 345,                   /* "exists"  */
  YYSYMBOL_MISSING = 346,                  /* "missing"  */
  YYSYMBOL_EXTHDR = 347,                   /* "exthdr"  */
  YYSYMBOL_IPSEC = 348,                    /* "ipsec"  */
  YYSYMBOL_REQID = 349,                    /* "reqid"  */
  YYSYMBOL_SPNUM = 350,                    /* "spnum"  */
  YYSYMBOL_IN = 351,                       /* "in"  */
  YYSYMBOL_OUT = 352,                      /* "out"  */
  YYSYMBOL_353_ = 353,                     /* '='  */
  YYSYMBOL_354_ = 354,                     /* '{'  */
  YYSYMBOL_355_ = 355,                     /* '}'  */
  YYSYMBOL_356_ = 356,                     /* '('  */
  YYSYMBOL_357_ = 357,                     /* ')'  */
  YYSYMBOL_358_ = 358,                     /* '|'  */
  YYSYMBOL_359_ = 359,                     /* '$'  */
  YYSYMBOL_360_ = 360,                     /* '['  */
  YYSYMBOL_361_ = 361,                     /* ']'  */
  YYSYMBOL_YYACCEPT = 362,                 /* $accept  */
  YYSYMBOL_input = 363,                    /* input  */
  YYSYMBOL_stmt_separator = 364,           /* stmt_separator  */
  YYSYMBOL_opt_newline = 365,              /* opt_newline  */
  YYSYMBOL_close_scope_ah = 366,           /* close_scope_ah  */
  YYSYMBOL_close_scope_arp = 367,          /* close_scope_arp  */
  YYSYMBOL_close_scope_at = 368,           /* close_scope_at  */
  YYSYMBOL_close_scope_comp = 369,         /* close_scope_comp  */
  YYSYMBOL_close_scope_ct = 370,           /* close_scope_ct  */
  YYSYMBOL_close_scope_counter = 371,      /* close_scope_counter  */
  YYSYMBOL_close_scope_dccp = 372,         /* close_scope_dccp  */
  YYSYMBOL_close_scope_dst = 373,          /* close_scope_dst  */
  YYSYMBOL_close_scope_dup = 374,          /* close_scope_dup  */
  YYSYMBOL_close_scope_esp = 375,          /* close_scope_esp  */
  YYSYMBOL_close_scope_eth = 376,          /* close_scope_eth  */
  YYSYMBOL_close_scope_export = 377,       /* close_scope_export  */
  YYSYMBOL_close_scope_fib = 378,          /* close_scope_fib  */
  YYSYMBOL_close_scope_frag = 379,         /* close_scope_frag  */
  YYSYMBOL_close_scope_fwd = 380,          /* close_scope_fwd  */
  YYSYMBOL_close_scope_hash = 381,         /* close_scope_hash  */
  YYSYMBOL_close_scope_hbh = 382,          /* close_scope_hbh  */
  YYSYMBOL_close_scope_ip = 383,           /* close_scope_ip  */
  YYSYMBOL_close_scope_ip6 = 384,          /* close_scope_ip6  */
  YYSYMBOL_close_scope_vlan = 385,         /* close_scope_vlan  */
  YYSYMBOL_close_scope_icmp = 386,         /* close_scope_icmp  */
  YYSYMBOL_close_scope_igmp = 387,         /* close_scope_igmp  */
  YYSYMBOL_close_scope_import = 388,       /* close_scope_import  */
  YYSYMBOL_close_scope_ipsec = 389,        /* close_scope_ipsec  */
  YYSYMBOL_close_scope_list = 390,         /* close_scope_list  */
  YYSYMBOL_close_scope_limit = 391,        /* close_scope_limit  */
  YYSYMBOL_close_scope_meta = 392,         /* close_scope_meta  */
  YYSYMBOL_close_scope_mh = 393,           /* close_scope_mh  */
  YYSYMBOL_close_scope_monitor = 394,      /* close_scope_monitor  */
  YYSYMBOL_close_scope_nat = 395,          /* close_scope_nat  */
  YYSYMBOL_close_scope_numgen = 396,       /* close_scope_numgen  */
  YYSYMBOL_close_scope_osf = 397,          /* close_scope_osf  */
  YYSYMBOL_close_scope_policy = 398,       /* close_scope_policy  */
  YYSYMBOL_close_scope_quota = 399,        /* close_scope_quota  */
  YYSYMBOL_close_scope_queue = 400,        /* close_scope_queue  */
  YYSYMBOL_close_scope_reject = 401,       /* close_scope_reject  */
  YYSYMBOL_close_scope_reset = 402,        /* close_scope_reset  */
  YYSYMBOL_close_scope_rt = 403,           /* close_scope_rt  */
  YYSYMBOL_close_scope_sctp = 404,         /* close_scope_sctp  */
  YYSYMBOL_close_scope_sctp_chunk = 405,   /* close_scope_sctp_chunk  */
  YYSYMBOL_close_scope_secmark = 406,      /* close_scope_secmark  */
  YYSYMBOL_close_scope_socket = 407,       /* close_scope_socket  */
  YYSYMBOL_close_scope_tcp = 408,          /* close_scope_tcp  */
  YYSYMBOL_close_scope_tproxy = 409,       /* close_scope_tproxy  */
  YYSYMBOL_close_scope_type = 410,         /* close_scope_type  */
  YYSYMBOL_close_scope_th = 411,           /* close_scope_th  */
  YYSYMBOL_close_scope_udp = 412,          /* close_scope_udp  */
  YYSYMBOL_close_scope_udplite = 413,      /* close_scope_udplite  */
  YYSYMBOL_close_scope_log = 414,          /* close_scope_log  */
  YYSYMBOL_close_scope_synproxy = 415,     /* close_scope_synproxy  */
  YYSYMBOL_common_block = 416,             /* common_block  */
  YYSYMBOL_line = 417,                     /* line  */
  YYSYMBOL_base_cmd = 418,                 /* base_cmd  */
  YYSYMBOL_add_cmd = 419,                  /* add_cmd  */
  YYSYMBOL_replace_cmd = 420,              /* replace_cmd  */
  YYSYMBOL_create_cmd = 421,               /* create_cmd  */
  YYSYMBOL_insert_cmd = 422,               /* insert_cmd  */
  YYSYMBOL_table_or_id_spec = 423,         /* table_or_id_spec  */
  YYSYMBOL_chain_or_id_spec = 424,         /* chain_or_id_spec  */
  YYSYMBOL_set_or_id_spec = 425,           /* set_or_id_spec  */
  YYSYMBOL_obj_or_id_spec = 426,           /* obj_or_id_spec  */
  YYSYMBOL_delete_cmd = 427,               /* delete_cmd  */
  YYSYMBOL_get_cmd = 428,                  /* get_cmd  */
  YYSYMBOL_list_cmd = 429,                 /* list_cmd  */
  YYSYMBOL_basehook_device_name = 430,     /* basehook_device_name  */
  YYSYMBOL_basehook_spec = 431,            /* basehook_spec  */
  YYSYMBOL_reset_cmd = 432,                /* reset_cmd  */
  YYSYMBOL_flush_cmd = 433,                /* flush_cmd  */
  YYSYMBOL_rename_cmd = 434,               /* rename_cmd  */
  YYSYMBOL_import_cmd = 435,               /* import_cmd  */
  YYSYMBOL_export_cmd = 436,               /* export_cmd  */
  YYSYMBOL_monitor_cmd = 437,              /* monitor_cmd  */
  YYSYMBOL_monitor_event = 438,            /* monitor_event  */
  YYSYMBOL_monitor_object = 439,           /* monitor_object  */
  YYSYMBOL_monitor_format = 440,           /* monitor_format  */
  YYSYMBOL_markup_format = 441,            /* markup_format  */
  YYSYMBOL_describe_cmd = 442,             /* describe_cmd  */
  YYSYMBOL_table_block_alloc = 443,        /* table_block_alloc  */
  YYSYMBOL_table_options = 444,            /* table_options  */
  YYSYMBOL_table_block = 445,              /* table_block  */
  YYSYMBOL_chain_block_alloc = 446,        /* chain_block_alloc  */
  YYSYMBOL_chain_block = 447,              /* chain_block  */
  YYSYMBOL_subchain_block = 448,           /* subchain_block  */
  YYSYMBOL_typeof_data_expr = 449,         /* typeof_data_expr  */
  YYSYMBOL_typeof_expr = 450,              /* typeof_expr  */
  YYSYMBOL_set_block_alloc = 451,          /* set_block_alloc  */
  YYSYMBOL_set_block = 452,                /* set_block  */
  YYSYMBOL_set_block_expr = 453,           /* set_block_expr  */
  YYSYMBOL_set_flag_list = 454,            /* set_flag_list  */
  YYSYMBOL_set_flag = 455,                 /* set_flag  */
  YYSYMBOL_map_block_alloc = 456,          /* map_block_alloc  */
  YYSYMBOL_map_block_obj_type = 457,       /* map_block_obj_type  */
  YYSYMBOL_map_block = 458,                /* map_block  */
  YYSYMBOL_set_mechanism = 459,            /* set_mechanism  */
  YYSYMBOL_set_policy_spec = 460,          /* set_policy_spec  */
  YYSYMBOL_flowtable_block_alloc = 461,    /* flowtable_block_alloc  */
  YYSYMBOL_flowtable_block = 462,          /* flowtable_block  */
  YYSYMBOL_flowtable_expr = 463,           /* flowtable_expr  */
  YYSYMBOL_flowtable_list_expr = 464,      /* flowtable_list_expr  */
  YYSYMBOL_flowtable_expr_member = 465,    /* flowtable_expr_member  */
  YYSYMBOL_data_type_atom_expr = 466,      /* data_type_atom_expr  */
  YYSYMBOL_data_type_expr = 467,           /* data_type_expr  */
  YYSYMBOL_obj_block_alloc = 468,          /* obj_block_alloc  */
  YYSYMBOL_counter_block = 469,            /* counter_block  */
  YYSYMBOL_quota_block = 470,              /* quota_block  */
  YYSYMBOL_ct_helper_block = 471,          /* ct_helper_block  */
  YYSYMBOL_ct_timeout_block = 472,         /* ct_timeout_block  */
  YYSYMBOL_ct_expect_block = 473,          /* ct_expect_block  */
  YYSYMBOL_limit_block = 474,              /* limit_block  */
  YYSYMBOL_secmark_block = 475,            /* secmark_block  */
  YYSYMBOL_synproxy_block = 476,           /* synproxy_block  */
  YYSYMBOL_type_identifier = 477,          /* type_identifier  */
  YYSYMBOL_hook_spec = 478,                /* hook_spec  */
  YYSYMBOL_prio_spec = 479,                /* prio_spec  */
  YYSYMBOL_extended_prio_name = 480,       /* extended_prio_name  */
  YYSYMBOL_extended_prio_spec = 481,       /* extended_prio_spec  */
  YYSYMBOL_int_num = 482,                  /* int_num  */
  YYSYMBOL_dev_spec = 483,                 /* dev_spec  */
  YYSYMBOL_flags_spec = 484,               /* flags_spec  */
  YYSYMBOL_policy_spec = 485,              /* policy_spec  */
  YYSYMBOL_policy_expr = 486,              /* policy_expr  */
  YYSYMBOL_chain_policy = 487,             /* chain_policy  */
  YYSYMBOL_identifier = 488,               /* identifier  */
  YYSYMBOL_string = 489,                   /* string  */
  YYSYMBOL_time_spec = 490,                /* time_spec  */
  YYSYMBOL_family_spec = 491,              /* family_spec  */
  YYSYMBOL_family_spec_explicit = 492,     /* family_spec_explicit  */
  YYSYMBOL_table_spec = 493,               /* table_spec  */
  YYSYMBOL_tableid_spec = 494,             /* tableid_spec  */
  YYSYMBOL_chain_spec = 495,               /* chain_spec  */
  YYSYMBOL_chainid_spec = 496,             /* chainid_spec  */
  YYSYMBOL_chain_identifier = 497,         /* chain_identifier  */
  YYSYMBOL_set_spec = 498,                 /* set_spec  */
  YYSYMBOL_setid_spec = 499,               /* setid_spec  */
  YYSYMBOL_set_identifier = 500,           /* set_identifier  */
  YYSYMBOL_flowtable_spec = 501,           /* flowtable_spec  */
  YYSYMBOL_flowtableid_spec = 502,         /* flowtableid_spec  */
  YYSYMBOL_flowtable_identifier = 503,     /* flowtable_identifier  */
  YYSYMBOL_obj_spec = 504,                 /* obj_spec  */
  YYSYMBOL_objid_spec = 505,               /* objid_spec  */
  YYSYMBOL_obj_identifier = 506,           /* obj_identifier  */
  YYSYMBOL_handle_spec = 507,              /* handle_spec  */
  YYSYMBOL_position_spec = 508,            /* position_spec  */
  YYSYMBOL_index_spec = 509,               /* index_spec  */
  YYSYMBOL_rule_position = 510,            /* rule_position  */
  YYSYMBOL_ruleid_spec = 511,              /* ruleid_spec  */
  YYSYMBOL_comment_spec = 512,             /* comment_spec  */
  YYSYMBOL_ruleset_spec = 513,             /* ruleset_spec  */
  YYSYMBOL_rule = 514,                     /* rule  */
  YYSYMBOL_rule_alloc = 515,               /* rule_alloc  */
  YYSYMBOL_stmt_list = 516,                /* stmt_list  */
  YYSYMBOL_stateful_stmt_list = 517,       /* stateful_stmt_list  */
  YYSYMBOL_stateful_stmt = 518,            /* stateful_stmt  */
  YYSYMBOL_stmt = 519,                     /* stmt  */
  YYSYMBOL_chain_stmt_type = 520,          /* chain_stmt_type  */
  YYSYMBOL_chain_stmt = 521,               /* chain_stmt  */
  YYSYMBOL_verdict_stmt = 522,             /* verdict_stmt  */
  YYSYMBOL_verdict_map_stmt = 523,         /* verdict_map_stmt  */
  YYSYMBOL_verdict_map_expr = 524,         /* verdict_map_expr  */
  YYSYMBOL_verdict_map_list_expr = 525,    /* verdict_map_list_expr  */
  YYSYMBOL_verdict_map_list_member_expr = 526, /* verdict_map_list_member_expr  */
  YYSYMBOL_connlimit_stmt = 527,           /* connlimit_stmt  */
  YYSYMBOL_counter_stmt = 528,             /* counter_stmt  */
  YYSYMBOL_counter_stmt_alloc = 529,       /* counter_stmt_alloc  */
  YYSYMBOL_counter_args = 530,             /* counter_args  */
  YYSYMBOL_counter_arg = 531,              /* counter_arg  */
  YYSYMBOL_log_stmt = 532,                 /* log_stmt  */
  YYSYMBOL_log_stmt_alloc = 533,           /* log_stmt_alloc  */
  YYSYMBOL_log_args = 534,                 /* log_args  */
  YYSYMBOL_log_arg = 535,                  /* log_arg  */
  YYSYMBOL_level_type = 536,               /* level_type  */
  YYSYMBOL_log_flags = 537,                /* log_flags  */
  YYSYMBOL_log_flags_tcp = 538,            /* log_flags_tcp  */
  YYSYMBOL_log_flag_tcp = 539,             /* log_flag_tcp  */
  YYSYMBOL_limit_stmt = 540,               /* limit_stmt  */
  YYSYMBOL_quota_mode = 541,               /* quota_mode  */
  YYSYMBOL_quota_unit = 542,               /* quota_unit  */
  YYSYMBOL_quota_used = 543,               /* quota_used  */
  YYSYMBOL_quota_stmt = 544,               /* quota_stmt  */
  YYSYMBOL_limit_mode = 545,               /* limit_mode  */
  YYSYMBOL_limit_burst_pkts = 546,         /* limit_burst_pkts  */
  YYSYMBOL_limit_rate_pkts = 547,          /* limit_rate_pkts  */
  YYSYMBOL_limit_burst_bytes = 548,        /* limit_burst_bytes  */
  YYSYMBOL_limit_rate_bytes = 549,         /* limit_rate_bytes  */
  YYSYMBOL_limit_bytes = 550,              /* limit_bytes  */
  YYSYMBOL_time_unit = 551,                /* time_unit  */
  YYSYMBOL_reject_stmt = 552,              /* reject_stmt  */
  YYSYMBOL_reject_stmt_alloc = 553,        /* reject_stmt_alloc  */
  YYSYMBOL_reject_with_expr = 554,         /* reject_with_expr  */
  YYSYMBOL_reject_opts = 555,              /* reject_opts  */
  YYSYMBOL_nat_stmt = 556,                 /* nat_stmt  */
  YYSYMBOL_nat_stmt_alloc = 557,           /* nat_stmt_alloc  */
  YYSYMBOL_tproxy_stmt = 558,              /* tproxy_stmt  */
  YYSYMBOL_synproxy_stmt = 559,            /* synproxy_stmt  */
  YYSYMBOL_synproxy_stmt_alloc = 560,      /* synproxy_stmt_alloc  */
  YYSYMBOL_synproxy_args = 561,            /* synproxy_args  */
  YYSYMBOL_synproxy_arg = 562,             /* synproxy_arg  */
  YYSYMBOL_synproxy_config = 563,          /* synproxy_config  */
  YYSYMBOL_synproxy_obj = 564,             /* synproxy_obj  */
  YYSYMBOL_synproxy_ts = 565,              /* synproxy_ts  */
  YYSYMBOL_synproxy_sack = 566,            /* synproxy_sack  */
  YYSYMBOL_primary_stmt_expr = 567,        /* primary_stmt_expr  */
  YYSYMBOL_shift_stmt_expr = 568,          /* shift_stmt_expr  */
  YYSYMBOL_and_stmt_expr = 569,            /* and_stmt_expr  */
  YYSYMBOL_exclusive_or_stmt_expr = 570,   /* exclusive_or_stmt_expr  */
  YYSYMBOL_inclusive_or_stmt_expr = 571,   /* inclusive_or_stmt_expr  */
  YYSYMBOL_basic_stmt_expr = 572,          /* basic_stmt_expr  */
  YYSYMBOL_concat_stmt_expr = 573,         /* concat_stmt_expr  */
  YYSYMBOL_map_stmt_expr_set = 574,        /* map_stmt_expr_set  */
  YYSYMBOL_map_stmt_expr = 575,            /* map_stmt_expr  */
  YYSYMBOL_prefix_stmt_expr = 576,         /* prefix_stmt_expr  */
  YYSYMBOL_range_stmt_expr = 577,          /* range_stmt_expr  */
  YYSYMBOL_multiton_stmt_expr = 578,       /* multiton_stmt_expr  */
  YYSYMBOL_stmt_expr = 579,                /* stmt_expr  */
  YYSYMBOL_nat_stmt_args = 580,            /* nat_stmt_args  */
  YYSYMBOL_masq_stmt = 581,                /* masq_stmt  */
  YYSYMBOL_masq_stmt_alloc = 582,          /* masq_stmt_alloc  */
  YYSYMBOL_masq_stmt_args = 583,           /* masq_stmt_args  */
  YYSYMBOL_redir_stmt = 584,               /* redir_stmt  */
  YYSYMBOL_redir_stmt_alloc = 585,         /* redir_stmt_alloc  */
  YYSYMBOL_redir_stmt_arg = 586,           /* redir_stmt_arg  */
  YYSYMBOL_dup_stmt = 587,                 /* dup_stmt  */
  YYSYMBOL_fwd_stmt = 588,                 /* fwd_stmt  */
  YYSYMBOL_nf_nat_flags = 589,             /* nf_nat_flags  */
  YYSYMBOL_nf_nat_flag = 590,              /* nf_nat_flag  */
  YYSYMBOL_queue_stmt = 591,               /* queue_stmt  */
  YYSYMBOL_queue_stmt_compat = 592,        /* queue_stmt_compat  */
  YYSYMBOL_queue_stmt_alloc = 593,         /* queue_stmt_alloc  */
  YYSYMBOL_queue_stmt_args = 594,          /* queue_stmt_args  */
  YYSYMBOL_queue_stmt_arg = 595,           /* queue_stmt_arg  */
  YYSYMBOL_queue_expr = 596,               /* queue_expr  */
  YYSYMBOL_queue_stmt_expr_simple = 597,   /* queue_stmt_expr_simple  */
  YYSYMBOL_queue_stmt_expr = 598,          /* queue_stmt_expr  */
  YYSYMBOL_queue_stmt_flags = 599,         /* queue_stmt_flags  */
  YYSYMBOL_queue_stmt_flag = 600,          /* queue_stmt_flag  */
  YYSYMBOL_set_elem_expr_stmt = 601,       /* set_elem_expr_stmt  */
  YYSYMBOL_set_elem_expr_stmt_alloc = 602, /* set_elem_expr_stmt_alloc  */
  YYSYMBOL_set_stmt = 603,                 /* set_stmt  */
  YYSYMBOL_set_stmt_op = 604,              /* set_stmt_op  */
  YYSYMBOL_map_stmt = 605,                 /* map_stmt  */
  YYSYMBOL_meter_stmt = 606,               /* meter_stmt  */
  YYSYMBOL_flow_stmt_legacy_alloc = 607,   /* flow_stmt_legacy_alloc  */
  YYSYMBOL_flow_stmt_opts = 608,           /* flow_stmt_opts  */
  YYSYMBOL_flow_stmt_opt = 609,            /* flow_stmt_opt  */
  YYSYMBOL_meter_stmt_alloc = 610,         /* meter_stmt_alloc  */
  YYSYMBOL_match_stmt = 611,               /* match_stmt  */
  YYSYMBOL_variable_expr = 612,            /* variable_expr  */
  YYSYMBOL_symbol_expr = 613,              /* symbol_expr  */
  YYSYMBOL_set_ref_expr = 614,             /* set_ref_expr  */
  YYSYMBOL_set_ref_symbol_expr = 615,      /* set_ref_symbol_expr  */
  YYSYMBOL_integer_expr = 616,             /* integer_expr  */
  YYSYMBOL_primary_expr = 617,             /* primary_expr  */
  YYSYMBOL_fib_expr = 618,                 /* fib_expr  */
  YYSYMBOL_fib_result = 619,               /* fib_result  */
  YYSYMBOL_fib_flag = 620,                 /* fib_flag  */
  YYSYMBOL_fib_tuple = 621,                /* fib_tuple  */
  YYSYMBOL_osf_expr = 622,                 /* osf_expr  */
  YYSYMBOL_osf_ttl = 623,                  /* osf_ttl  */
  YYSYMBOL_shift_expr = 624,               /* shift_expr  */
  YYSYMBOL_and_expr = 625,                 /* and_expr  */
  YYSYMBOL_exclusive_or_expr = 626,        /* exclusive_or_expr  */
  YYSYMBOL_inclusive_or_expr = 627,        /* inclusive_or_expr  */
  YYSYMBOL_basic_expr = 628,               /* basic_expr  */
  YYSYMBOL_concat_expr = 629,              /* concat_expr  */
  YYSYMBOL_prefix_rhs_expr = 630,          /* prefix_rhs_expr  */
  YYSYMBOL_range_rhs_expr = 631,           /* range_rhs_expr  */
  YYSYMBOL_multiton_rhs_expr = 632,        /* multiton_rhs_expr  */
  YYSYMBOL_map_expr = 633,                 /* map_expr  */
  YYSYMBOL_expr = 634,                     /* expr  */
  YYSYMBOL_set_expr = 635,                 /* set_expr  */
  YYSYMBOL_set_list_expr = 636,            /* set_list_expr  */
  YYSYMBOL_set_list_member_expr = 637,     /* set_list_member_expr  */
  YYSYMBOL_meter_key_expr = 638,           /* meter_key_expr  */
  YYSYMBOL_meter_key_expr_alloc = 639,     /* meter_key_expr_alloc  */
  YYSYMBOL_set_elem_expr = 640,            /* set_elem_expr  */
  YYSYMBOL_set_elem_key_expr = 641,        /* set_elem_key_expr  */
  YYSYMBOL_set_elem_expr_alloc = 642,      /* set_elem_expr_alloc  */
  YYSYMBOL_set_elem_options = 643,         /* set_elem_options  */
  YYSYMBOL_set_elem_option = 644,          /* set_elem_option  */
  YYSYMBOL_set_elem_expr_options = 645,    /* set_elem_expr_options  */
  YYSYMBOL_set_elem_stmt_list = 646,       /* set_elem_stmt_list  */
  YYSYMBOL_set_elem_stmt = 647,            /* set_elem_stmt  */
  YYSYMBOL_set_elem_expr_option = 648,     /* set_elem_expr_option  */
  YYSYMBOL_set_lhs_expr = 649,             /* set_lhs_expr  */
  YYSYMBOL_set_rhs_expr = 650,             /* set_rhs_expr  */
  YYSYMBOL_initializer_expr = 651,         /* initializer_expr  */
  YYSYMBOL_counter_config = 652,           /* counter_config  */
  YYSYMBOL_counter_obj = 653,              /* counter_obj  */
  YYSYMBOL_quota_config = 654,             /* quota_config  */
  YYSYMBOL_quota_obj = 655,                /* quota_obj  */
  YYSYMBOL_secmark_config = 656,           /* secmark_config  */
  YYSYMBOL_secmark_obj = 657,              /* secmark_obj  */
  YYSYMBOL_ct_obj_type = 658,              /* ct_obj_type  */
  YYSYMBOL_ct_cmd_type = 659,              /* ct_cmd_type  */
  YYSYMBOL_ct_l4protoname = 660,           /* ct_l4protoname  */
  YYSYMBOL_ct_helper_config = 661,         /* ct_helper_config  */
  YYSYMBOL_timeout_states = 662,           /* timeout_states  */
  YYSYMBOL_timeout_state = 663,            /* timeout_state  */
  YYSYMBOL_ct_timeout_config = 664,        /* ct_timeout_config  */
  YYSYMBOL_ct_expect_config = 665,         /* ct_expect_config  */
  YYSYMBOL_ct_obj_alloc = 666,             /* ct_obj_alloc  */
  YYSYMBOL_limit_config = 667,             /* limit_config  */
  YYSYMBOL_limit_obj = 668,                /* limit_obj  */
  YYSYMBOL_relational_expr = 669,          /* relational_expr  */
  YYSYMBOL_list_rhs_expr = 670,            /* list_rhs_expr  */
  YYSYMBOL_rhs_expr = 671,                 /* rhs_expr  */
  YYSYMBOL_shift_rhs_expr = 672,           /* shift_rhs_expr  */
  YYSYMBOL_and_rhs_expr = 673,             /* and_rhs_expr  */
  YYSYMBOL_exclusive_or_rhs_expr = 674,    /* exclusive_or_rhs_expr  */
  YYSYMBOL_inclusive_or_rhs_expr = 675,    /* inclusive_or_rhs_expr  */
  YYSYMBOL_basic_rhs_expr = 676,           /* basic_rhs_expr  */
  YYSYMBOL_concat_rhs_expr = 677,          /* concat_rhs_expr  */
  YYSYMBOL_boolean_keys = 678,             /* boolean_keys  */
  YYSYMBOL_boolean_expr = 679,             /* boolean_expr  */
  YYSYMBOL_keyword_expr = 680,             /* keyword_expr  */
  YYSYMBOL_primary_rhs_expr = 681,         /* primary_rhs_expr  */
  YYSYMBOL_relational_op = 682,            /* relational_op  */
  YYSYMBOL_verdict_expr = 683,             /* verdict_expr  */
  YYSYMBOL_chain_expr = 684,               /* chain_expr  */
  YYSYMBOL_meta_expr = 685,                /* meta_expr  */
  YYSYMBOL_meta_key = 686,                 /* meta_key  */
  YYSYMBOL_meta_key_qualified = 687,       /* meta_key_qualified  */
  YYSYMBOL_meta_key_unqualified = 688,     /* meta_key_unqualified  */
  YYSYMBOL_meta_stmt = 689,                /* meta_stmt  */
  YYSYMBOL_socket_expr = 690,              /* socket_expr  */
  YYSYMBOL_socket_key = 691,               /* socket_key  */
  YYSYMBOL_offset_opt = 692,               /* offset_opt  */
  YYSYMBOL_numgen_type = 693,              /* numgen_type  */
  YYSYMBOL_numgen_expr = 694,              /* numgen_expr  */
  YYSYMBOL_xfrm_spnum = 695,               /* xfrm_spnum  */
  YYSYMBOL_xfrm_dir = 696,                 /* xfrm_dir  */
  YYSYMBOL_xfrm_state_key = 697,           /* xfrm_state_key  */
  YYSYMBOL_xfrm_state_proto_key = 698,     /* xfrm_state_proto_key  */
  YYSYMBOL_xfrm_expr = 699,                /* xfrm_expr  */
  YYSYMBOL_hash_expr = 700,                /* hash_expr  */
  YYSYMBOL_nf_key_proto = 701,             /* nf_key_proto  */
  YYSYMBOL_rt_expr = 702,                  /* rt_expr  */
  YYSYMBOL_rt_key = 703,                   /* rt_key  */
  YYSYMBOL_ct_expr = 704,                  /* ct_expr  */
  YYSYMBOL_ct_dir = 705,                   /* ct_dir  */
  YYSYMBOL_ct_key = 706,                   /* ct_key  */
  YYSYMBOL_ct_key_dir = 707,               /* ct_key_dir  */
  YYSYMBOL_ct_key_proto_field = 708,       /* ct_key_proto_field  */
  YYSYMBOL_ct_key_dir_optional = 709,      /* ct_key_dir_optional  */
  YYSYMBOL_symbol_stmt_expr = 710,         /* symbol_stmt_expr  */
  YYSYMBOL_list_stmt_expr = 711,           /* list_stmt_expr  */
  YYSYMBOL_ct_stmt = 712,                  /* ct_stmt  */
  YYSYMBOL_payload_stmt = 713,             /* payload_stmt  */
  YYSYMBOL_payload_expr = 714,             /* payload_expr  */
  YYSYMBOL_payload_raw_expr = 715,         /* payload_raw_expr  */
  YYSYMBOL_payload_base_spec = 716,        /* payload_base_spec  */
  YYSYMBOL_eth_hdr_expr = 717,             /* eth_hdr_expr  */
  YYSYMBOL_eth_hdr_field = 718,            /* eth_hdr_field  */
  YYSYMBOL_vlan_hdr_expr = 719,            /* vlan_hdr_expr  */
  YYSYMBOL_vlan_hdr_field = 720,           /* vlan_hdr_field  */
  YYSYMBOL_arp_hdr_expr = 721,             /* arp_hdr_expr  */
  YYSYMBOL_arp_hdr_field = 722,            /* arp_hdr_field  */
  YYSYMBOL_ip_hdr_expr = 723,              /* ip_hdr_expr  */
  YYSYMBOL_ip_hdr_field = 724,             /* ip_hdr_field  */
  YYSYMBOL_ip_option_type = 725,           /* ip_option_type  */
  YYSYMBOL_ip_option_field = 726,          /* ip_option_field  */
  YYSYMBOL_icmp_hdr_expr = 727,            /* icmp_hdr_expr  */
  YYSYMBOL_icmp_hdr_field = 728,           /* icmp_hdr_field  */
  YYSYMBOL_igmp_hdr_expr = 729,            /* igmp_hdr_expr  */
  YYSYMBOL_igmp_hdr_field = 730,           /* igmp_hdr_field  */
  YYSYMBOL_ip6_hdr_expr = 731,             /* ip6_hdr_expr  */
  YYSYMBOL_ip6_hdr_field = 732,            /* ip6_hdr_field  */
  YYSYMBOL_icmp6_hdr_expr = 733,           /* icmp6_hdr_expr  */
  YYSYMBOL_icmp6_hdr_field = 734,          /* icmp6_hdr_field  */
  YYSYMBOL_auth_hdr_expr = 735,            /* auth_hdr_expr  */
  YYSYMBOL_auth_hdr_field = 736,           /* auth_hdr_field  */
  YYSYMBOL_esp_hdr_expr = 737,             /* esp_hdr_expr  */
  YYSYMBOL_esp_hdr_field = 738,            /* esp_hdr_field  */
  YYSYMBOL_comp_hdr_expr = 739,            /* comp_hdr_expr  */
  YYSYMBOL_comp_hdr_field = 740,           /* comp_hdr_field  */
  YYSYMBOL_udp_hdr_expr = 741,             /* udp_hdr_expr  */
  YYSYMBOL_udp_hdr_field = 742,            /* udp_hdr_field  */
  YYSYMBOL_udplite_hdr_expr = 743,         /* udplite_hdr_expr  */
  YYSYMBOL_udplite_hdr_field = 744,        /* udplite_hdr_field  */
  YYSYMBOL_tcp_hdr_expr = 745,             /* tcp_hdr_expr  */
  YYSYMBOL_optstrip_stmt = 746,            /* optstrip_stmt  */
  YYSYMBOL_tcp_hdr_field = 747,            /* tcp_hdr_field  */
  YYSYMBOL_tcp_hdr_option_kind_and_field = 748, /* tcp_hdr_option_kind_and_field  */
  YYSYMBOL_tcp_hdr_option_sack = 749,      /* tcp_hdr_option_sack  */
  YYSYMBOL_tcp_hdr_option_type = 750,      /* tcp_hdr_option_type  */
  YYSYMBOL_tcpopt_field_sack = 751,        /* tcpopt_field_sack  */
  YYSYMBOL_tcpopt_field_window = 752,      /* tcpopt_field_window  */
  YYSYMBOL_tcpopt_field_tsopt = 753,       /* tcpopt_field_tsopt  */
  YYSYMBOL_tcpopt_field_maxseg = 754,      /* tcpopt_field_maxseg  */
  YYSYMBOL_tcpopt_field_mptcp = 755,       /* tcpopt_field_mptcp  */
  YYSYMBOL_dccp_hdr_expr = 756,            /* dccp_hdr_expr  */
  YYSYMBOL_dccp_hdr_field = 757,           /* dccp_hdr_field  */
  YYSYMBOL_sctp_chunk_type = 758,          /* sctp_chunk_type  */
  YYSYMBOL_sctp_chunk_common_field = 759,  /* sctp_chunk_common_field  */
  YYSYMBOL_sctp_chunk_data_field = 760,    /* sctp_chunk_data_field  */
  YYSYMBOL_sctp_chunk_init_field = 761,    /* sctp_chunk_init_field  */
  YYSYMBOL_sctp_chunk_sack_field = 762,    /* sctp_chunk_sack_field  */
  YYSYMBOL_sctp_chunk_alloc = 763,         /* sctp_chunk_alloc  */
  YYSYMBOL_sctp_hdr_expr = 764,            /* sctp_hdr_expr  */
  YYSYMBOL_sctp_hdr_field = 765,           /* sctp_hdr_field  */
  YYSYMBOL_th_hdr_expr = 766,              /* th_hdr_expr  */
  YYSYMBOL_th_hdr_field = 767,             /* th_hdr_field  */
  YYSYMBOL_exthdr_expr = 768,              /* exthdr_expr  */
  YYSYMBOL_hbh_hdr_expr = 769,             /* hbh_hdr_expr  */
  YYSYMBOL_hbh_hdr_field = 770,            /* hbh_hdr_field  */
  YYSYMBOL_rt_hdr_expr = 771,              /* rt_hdr_expr  */
  YYSYMBOL_rt_hdr_field = 772,             /* rt_hdr_field  */
  YYSYMBOL_rt0_hdr_expr = 773,             /* rt0_hdr_expr  */
  YYSYMBOL_rt0_hdr_field = 774,            /* rt0_hdr_field  */
  YYSYMBOL_rt2_hdr_expr = 775,             /* rt2_hdr_expr  */
  YYSYMBOL_rt2_hdr_field = 776,            /* rt2_hdr_field  */
  YYSYMBOL_rt4_hdr_expr = 777,             /* rt4_hdr_expr  */
  YYSYMBOL_rt4_hdr_field = 778,            /* rt4_hdr_field  */
  YYSYMBOL_frag_hdr_expr = 779,            /* frag_hdr_expr  */
  YYSYMBOL_frag_hdr_field = 780,           /* frag_hdr_field  */
  YYSYMBOL_dst_hdr_expr = 781,             /* dst_hdr_expr  */
  YYSYMBOL_dst_hdr_field = 782,            /* dst_hdr_field  */
  YYSYMBOL_mh_hdr_expr = 783,              /* mh_hdr_expr  */
  YYSYMBOL_mh_hdr_field = 784,             /* mh_hdr_field  */
  YYSYMBOL_exthdr_exists_expr = 785,       /* exthdr_exists_expr  */
  YYSYMBOL_exthdr_key = 786                /* exthdr_key  */
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
#define YYLAST   7911

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  362
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  425
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1278
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2198

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   607


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
       2,     2,     2,     2,     2,     2,   359,     2,     2,     2,
     356,   357,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   353,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   360,     2,   361,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   354,   358,   355,     2,     2,     2,     2,
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
     345,   346,   347,   348,   349,   350,   351,   352
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   914,   914,   915,   924,   925,   928,   929,   932,   933,
     934,   935,   936,   937,   938,   939,   940,   941,   942,   943,
     944,   945,   946,   947,   948,   949,   950,   951,   952,   953,
     954,   955,   956,   957,   958,   959,   960,   961,   962,   963,
     964,   965,   966,   967,   968,   969,   970,   971,   972,   973,
     974,   975,   976,   977,   978,   979,   981,   982,   984,   992,
    1007,  1014,  1026,  1034,  1035,  1036,  1037,  1057,  1058,  1059,
    1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,  1068,  1069,
    1070,  1071,  1074,  1078,  1085,  1089,  1097,  1101,  1105,  1112,
    1119,  1123,  1130,  1139,  1143,  1147,  1151,  1155,  1159,  1163,
    1167,  1171,  1175,  1179,  1183,  1187,  1193,  1199,  1203,  1210,
    1214,  1222,  1229,  1236,  1240,  1247,  1256,  1260,  1264,  1268,
    1272,  1276,  1280,  1284,  1290,  1296,  1297,  1300,  1301,  1304,
    1305,  1308,  1309,  1312,  1316,  1320,  1324,  1328,  1332,  1336,
    1340,  1344,  1351,  1355,  1359,  1365,  1369,  1373,  1379,  1385,
    1389,  1393,  1397,  1401,  1405,  1409,  1413,  1417,  1421,  1425,
    1429,  1433,  1437,  1441,  1445,  1449,  1453,  1457,  1461,  1465,
    1469,  1473,  1477,  1481,  1485,  1489,  1493,  1497,  1501,  1505,
    1509,  1513,  1517,  1523,  1529,  1533,  1543,  1547,  1551,  1555,
    1559,  1563,  1569,  1573,  1577,  1581,  1585,  1589,  1593,  1599,
    1606,  1612,  1620,  1626,  1634,  1643,  1644,  1647,  1648,  1649,
    1650,  1651,  1652,  1653,  1654,  1657,  1658,  1661,  1662,  1663,
    1666,  1675,  1681,  1696,  1706,  1707,  1708,  1709,  1710,  1721,
    1731,  1742,  1752,  1763,  1774,  1783,  1792,  1801,  1812,  1823,
    1837,  1843,  1844,  1845,  1846,  1847,  1848,  1849,  1854,  1864,
    1865,  1866,  1873,  1894,  1905,  1916,  1929,  1934,  1935,  1936,
    1937,  1942,  1948,  1953,  1958,  1963,  1969,  1974,  1979,  1980,
    1991,  1992,  1995,  1999,  2002,  2003,  2004,  2005,  2009,  2014,
    2015,  2016,  2017,  2018,  2021,  2022,  2023,  2024,  2029,  2039,
    2050,  2061,  2073,  2082,  2087,  2093,  2098,  2107,  2110,  2114,
    2120,  2121,  2125,  2130,  2131,  2132,  2133,  2147,  2151,  2155,
    2161,  2166,  2173,  2178,  2183,  2186,  2193,  2200,  2207,  2220,
    2227,  2228,  2240,  2245,  2246,  2247,  2248,  2252,  2262,  2263,
    2264,  2265,  2269,  2279,  2280,  2281,  2282,  2286,  2297,  2301,
    2302,  2303,  2307,  2317,  2318,  2319,  2320,  2324,  2334,  2335,
    2336,  2337,  2341,  2351,  2352,  2353,  2354,  2358,  2368,  2369,
    2370,  2371,  2375,  2385,  2386,  2387,  2388,  2389,  2392,  2423,
    2430,  2434,  2437,  2447,  2454,  2465,  2478,  2493,  2494,  2497,
    2509,  2515,  2519,  2522,  2528,  2541,  2546,  2555,  2556,  2559,
    2562,  2563,  2564,  2567,  2582,  2583,  2586,  2587,  2588,  2589,
    2590,  2591,  2594,  2603,  2612,  2620,  2628,  2636,  2644,  2652,
    2660,  2668,  2676,  2684,  2692,  2700,  2708,  2716,  2724,  2732,
    2736,  2741,  2749,  2756,  2763,  2777,  2781,  2788,  2792,  2798,
    2810,  2816,  2823,  2829,  2836,  2837,  2838,  2839,  2842,  2843,
    2844,  2845,  2846,  2847,  2848,  2849,  2850,  2851,  2852,  2853,
    2854,  2855,  2856,  2857,  2858,  2859,  2860,  2861,  2862,  2865,
    2866,  2869,  2878,  2882,  2888,  2894,  2899,  2902,  2907,  2912,
    2915,  2921,  2926,  2934,  2935,  2937,  2941,  2949,  2953,  2956,
    2960,  2966,  2967,  2970,  2976,  2980,  2983,  3108,  3113,  3118,
    3123,  3128,  3134,  3164,  3168,  3172,  3176,  3180,  3186,  3190,
    3193,  3197,  3203,  3217,  3231,  3239,  3240,  3241,  3244,  3245,
    3248,  3249,  3264,  3280,  3288,  3289,  3290,  3293,  3294,  3297,
    3304,  3305,  3308,  3322,  3329,  3330,  3345,  3346,  3347,  3348,
    3349,  3352,  3355,  3361,  3367,  3371,  3375,  3382,  3389,  3396,
    3403,  3409,  3415,  3421,  3424,  3425,  3428,  3434,  3440,  3446,
    3453,  3460,  3468,  3469,  3472,  3476,  3484,  3488,  3491,  3496,
    3501,  3505,  3511,  3527,  3546,  3552,  3553,  3559,  3560,  3566,
    3567,  3568,  3569,  3570,  3571,  3572,  3573,  3574,  3575,  3576,
    3577,  3578,  3581,  3582,  3586,  3592,  3593,  3599,  3600,  3606,
    3607,  3613,  3616,  3617,  3628,  3629,  3632,  3636,  3639,  3645,
    3651,  3652,  3655,  3656,  3657,  3660,  3664,  3668,  3673,  3678,
    3683,  3689,  3693,  3697,  3701,  3707,  3712,  3716,  3724,  3733,
    3734,  3737,  3740,  3744,  3749,  3755,  3756,  3759,  3762,  3766,
    3770,  3774,  3779,  3786,  3791,  3799,  3804,  3813,  3814,  3820,
    3821,  3822,  3825,  3826,  3830,  3834,  3840,  3841,  3844,  3850,
    3854,  3857,  3862,  3868,  3869,  3872,  3873,  3874,  3880,  3881,
    3882,  3883,  3886,  3887,  3893,  3894,  3897,  3898,  3901,  3907,
    3914,  3921,  3932,  3933,  3934,  3937,  3945,  3957,  3964,  3967,
    3973,  3977,  3980,  3986,  3995,  4006,  4012,  4038,  4039,  4048,
    4049,  4052,  4061,  4072,  4073,  4074,  4075,  4076,  4077,  4078,
    4079,  4080,  4081,  4082,  4083,  4084,  4085,  4086,  4089,  4112,
    4113,  4114,  4117,  4118,  4119,  4120,  4121,  4124,  4128,  4131,
    4135,  4142,  4145,  4161,  4162,  4166,  4172,  4173,  4179,  4180,
    4186,  4187,  4193,  4196,  4197,  4208,  4214,  4220,  4221,  4224,
    4230,  4231,  4232,  4235,  4242,  4247,  4252,  4255,  4259,  4263,
    4269,  4270,  4277,  4283,  4284,  4287,  4288,  4291,  4297,  4303,
    4307,  4310,  4314,  4318,  4328,  4332,  4335,  4341,  4348,  4352,
    4358,  4372,  4386,  4391,  4399,  4403,  4407,  4417,  4420,  4421,
    4424,  4425,  4426,  4427,  4438,  4449,  4455,  4476,  4482,  4499,
    4505,  4506,  4507,  4510,  4511,  4512,  4515,  4516,  4519,  4535,
    4541,  4547,  4554,  4568,  4576,  4584,  4590,  4594,  4598,  4602,
    4606,  4613,  4618,  4629,  4643,  4649,  4653,  4657,  4661,  4665,
    4669,  4673,  4677,  4683,  4689,  4697,  4698,  4699,  4702,  4703,
    4707,  4713,  4714,  4720,  4721,  4727,  4728,  4734,  4737,  4738,
    4739,  4748,  4759,  4760,  4763,  4771,  4772,  4773,  4774,  4775,
    4776,  4777,  4778,  4779,  4780,  4781,  4782,  4785,  4786,  4787,
    4788,  4789,  4796,  4803,  4810,  4817,  4824,  4831,  4838,  4845,
    4852,  4859,  4866,  4873,  4876,  4877,  4878,  4879,  4880,  4881,
    4882,  4885,  4889,  4893,  4897,  4901,  4905,  4911,  4912,  4922,
    4926,  4930,  4946,  4947,  4950,  4951,  4952,  4953,  4954,  4957,
    4958,  4959,  4960,  4961,  4962,  4963,  4964,  4965,  4966,  4967,
    4968,  4969,  4970,  4971,  4972,  4973,  4974,  4975,  4976,  4977,
    4978,  4979,  4980,  4983,  5003,  5007,  5021,  5025,  5029,  5035,
    5039,  5045,  5046,  5047,  5050,  5051,  5054,  5055,  5058,  5064,
    5065,  5068,  5069,  5072,  5073,  5076,  5077,  5080,  5088,  5115,
    5120,  5125,  5131,  5132,  5135,  5139,  5159,  5160,  5161,  5162,
    5165,  5169,  5173,  5179,  5180,  5183,  5184,  5185,  5186,  5187,
    5188,  5189,  5190,  5191,  5192,  5193,  5194,  5195,  5196,  5197,
    5198,  5199,  5202,  5203,  5204,  5205,  5206,  5207,  5208,  5211,
    5212,  5213,  5214,  5217,  5218,  5219,  5220,  5223,  5224,  5227,
    5233,  5241,  5254,  5261,  5267,  5273,  5282,  5283,  5284,  5285,
    5286,  5287,  5288,  5289,  5290,  5291,  5292,  5293,  5294,  5295,
    5296,  5297,  5298,  5299,  5302,  5311,  5312,  5313,  5314,  5327,
    5333,  5334,  5335,  5338,  5344,  5345,  5346,  5347,  5348,  5351,
    5357,  5358,  5359,  5360,  5361,  5362,  5363,  5364,  5365,  5368,
    5372,  5380,  5387,  5388,  5389,  5390,  5391,  5392,  5393,  5394,
    5395,  5396,  5397,  5398,  5401,  5402,  5403,  5404,  5407,  5408,
    5409,  5410,  5411,  5414,  5420,  5421,  5422,  5423,  5424,  5425,
    5426,  5429,  5435,  5436,  5437,  5438,  5441,  5447,  5448,  5449,
    5450,  5451,  5452,  5453,  5454,  5455,  5457,  5463,  5464,  5465,
    5466,  5467,  5468,  5469,  5470,  5473,  5479,  5480,  5481,  5482,
    5483,  5486,  5492,  5493,  5496,  5502,  5503,  5504,  5507,  5513,
    5514,  5515,  5516,  5519,  5525,  5526,  5527,  5528,  5531,  5535,
    5540,  5544,  5551,  5558,  5559,  5560,  5561,  5562,  5563,  5564,
    5565,  5566,  5567,  5570,  5575,  5580,  5585,  5590,  5595,  5602,
    5603,  5604,  5605,  5606,  5609,  5610,  5611,  5612,  5613,  5614,
    5615,  5616,  5617,  5618,  5619,  5620,  5629,  5630,  5633,  5636,
    5637,  5640,  5643,  5646,  5652,  5653,  5654,  5657,  5658,  5659,
    5660,  5661,  5662,  5663,  5664,  5665,  5666,  5667,  5668,  5669,
    5670,  5671,  5672,  5673,  5674,  5677,  5678,  5679,  5682,  5683,
    5684,  5685,  5688,  5689,  5690,  5691,  5692,  5695,  5696,  5697,
    5698,  5701,  5706,  5710,  5714,  5718,  5722,  5726,  5731,  5736,
    5741,  5746,  5751,  5758,  5762,  5768,  5769,  5770,  5771,  5774,
    5782,  5783,  5786,  5787,  5788,  5789,  5790,  5791,  5792,  5793,
    5796,  5802,  5803,  5806,  5812,  5813,  5814,  5815,  5818,  5824,
    5830,  5836,  5839,  5845,  5846,  5847,  5848,  5854,  5860,  5861,
    5862,  5863,  5864,  5865,  5868,  5874,  5875,  5878,  5884,  5885,
    5886,  5887,  5888,  5891,  5905,  5906,  5907,  5908,  5909
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
  "\"eol\"", "\"mptcp\"", "\"nop\"", "\"sack\"", "\"sack0\"", "\"sack1\"",
  "\"sack2\"", "\"sack3\"", "\"sack-permitted\"", "\"fastopen\"",
  "\"md5sig\"", "\"timestamp\"", "\"count\"", "\"left\"", "\"right\"",
  "\"tsval\"", "\"tsecr\"", "\"subtype\"", "\"dccp\"", "\"sctp\"",
  "\"chunk\"", "\"data\"", "\"init\"", "\"init-ack\"", "\"heartbeat\"",
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
  "\"counters\"", "\"quotas\"", "\"limits\"", "\"synproxys\"",
  "\"helpers\"", "\"log\"", "\"prefix\"", "\"group\"", "\"snaplen\"",
  "\"queue-threshold\"", "\"level\"", "\"limit\"", "\"rate\"", "\"burst\"",
  "\"over\"", "\"until\"", "\"quota\"", "\"used\"", "\"secmark\"",
  "\"secmarks\"", "\"second\"", "\"minute\"", "\"hour\"", "\"day\"",
  "\"week\"", "\"reject\"", "\"with\"", "\"icmpx\"", "\"snat\"",
  "\"dnat\"", "\"masquerade\"", "\"redirect\"", "\"random\"",
  "\"fully-random\"", "\"persistent\"", "\"queue\"", "\"num\"",
  "\"bypass\"", "\"fanout\"", "\"dup\"", "\"fwd\"", "\"numgen\"",
  "\"inc\"", "\"mod\"", "\"offset\"", "\"jhash\"", "\"symhash\"",
  "\"seed\"", "\"position\"", "\"index\"", "\"comment\"", "\"xml\"",
  "\"json\"", "\"vm\"", "\"notrack\"", "\"exists\"", "\"missing\"",
  "\"exthdr\"", "\"ipsec\"", "\"reqid\"", "\"spnum\"", "\"in\"", "\"out\"",
  "'='", "'{'", "'}'", "'('", "')'", "'|'", "'$'", "'['", "']'", "$accept",
  "input", "stmt_separator", "opt_newline", "close_scope_ah",
  "close_scope_arp", "close_scope_at", "close_scope_comp",
  "close_scope_ct", "close_scope_counter", "close_scope_dccp",
  "close_scope_dst", "close_scope_dup", "close_scope_esp",
  "close_scope_eth", "close_scope_export", "close_scope_fib",
  "close_scope_frag", "close_scope_fwd", "close_scope_hash",
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
  "close_scope_synproxy", "common_block", "line", "base_cmd", "add_cmd",
  "replace_cmd", "create_cmd", "insert_cmd", "table_or_id_spec",
  "chain_or_id_spec", "set_or_id_spec", "obj_or_id_spec", "delete_cmd",
  "get_cmd", "list_cmd", "basehook_device_name", "basehook_spec",
  "reset_cmd", "flush_cmd", "rename_cmd", "import_cmd", "export_cmd",
  "monitor_cmd", "monitor_event", "monitor_object", "monitor_format",
  "markup_format", "describe_cmd", "table_block_alloc", "table_options",
  "table_block", "chain_block_alloc", "chain_block", "subchain_block",
  "typeof_data_expr", "typeof_expr", "set_block_alloc", "set_block",
  "set_block_expr", "set_flag_list", "set_flag", "map_block_alloc",
  "map_block_obj_type", "map_block", "set_mechanism", "set_policy_spec",
  "flowtable_block_alloc", "flowtable_block", "flowtable_expr",
  "flowtable_list_expr", "flowtable_expr_member", "data_type_atom_expr",
  "data_type_expr", "obj_block_alloc", "counter_block", "quota_block",
  "ct_helper_block", "ct_timeout_block", "ct_expect_block", "limit_block",
  "secmark_block", "synproxy_block", "type_identifier", "hook_spec",
  "prio_spec", "extended_prio_name", "extended_prio_spec", "int_num",
  "dev_spec", "flags_spec", "policy_spec", "policy_expr", "chain_policy",
  "identifier", "string", "time_spec", "family_spec",
  "family_spec_explicit", "table_spec", "tableid_spec", "chain_spec",
  "chainid_spec", "chain_identifier", "set_spec", "setid_spec",
  "set_identifier", "flowtable_spec", "flowtableid_spec",
  "flowtable_identifier", "obj_spec", "objid_spec", "obj_identifier",
  "handle_spec", "position_spec", "index_spec", "rule_position",
  "ruleid_spec", "comment_spec", "ruleset_spec", "rule", "rule_alloc",
  "stmt_list", "stateful_stmt_list", "stateful_stmt", "stmt",
  "chain_stmt_type", "chain_stmt", "verdict_stmt", "verdict_map_stmt",
  "verdict_map_expr", "verdict_map_list_expr",
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
  "optstrip_stmt", "tcp_hdr_field", "tcp_hdr_option_kind_and_field",
  "tcp_hdr_option_sack", "tcp_hdr_option_type", "tcpopt_field_sack",
  "tcpopt_field_window", "tcpopt_field_tsopt", "tcpopt_field_maxseg",
  "tcpopt_field_mptcp", "dccp_hdr_expr", "dccp_hdr_field",
  "sctp_chunk_type", "sctp_chunk_common_field", "sctp_chunk_data_field",
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
     605,   606,   607,    61,   123,   125,    40,    41,   124,    36,
      91,    93
};
#endif

#define YYPACT_NINF (-1711)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-999)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1711,  7341, -1711,   369, -1711, -1711,    79,    91,    91,    91,
    1193,  1193,  1193,  1193,  1193,  1193,  1193,  1193, -1711, -1711,
    3929,   156,  1935,   219,  2779,   238,  4004,   667,   786,   256,
    6808,   257,   277,   210, -1711, -1711, -1711, -1711,   302,  1193,
    1193,  1193,  1193, -1711, -1711, -1711,   894, -1711,    91, -1711,
      91,    98,  6189, -1711,   369, -1711,    11,    46,   369,    91,
   -1711,   -18,    78,  6189,    91, -1711,   -77, -1711,    91, -1711,
   -1711,  1193, -1711,  1193,  1193,  1193,  1193,  1193,  1193,  1193,
     346,  1193,  1193,  1193,  1193, -1711,  1193, -1711,  1193,  1193,
    1193,  1193,  1193,  1193,  1193,  1193,   433,  1193,  1193,  1193,
    1193, -1711,  1193, -1711,  1193,  1193,  1193,  1193,  1193,  1193,
    1161,  1193,  1193,  1193,  1193,  1193,   474,  1193,  1193,  1193,
     414,  1193,  1836,  1881,  2158,  2375,  1193,  1193,  1193,  2552,
   -1711,  1193,  2669,  2720,  1193, -1711,  1193,  1193,  1193,  1193,
    1193,   372,  1193, -1711,  1193, -1711,  1432,   776,   212,   308,
   -1711, -1711, -1711, -1711,   826,   857,  1308,  1256,  3221,  1409,
     606,  1622,  1073,   819,    74,   634,   817,   851,  2781,   157,
      86,   633,   215,   255,    81,   404,   824,   624,   877,  4068,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711,  4609, -1711, -1711,   -95,  6447,   221,   870,   439,  6808,
      91, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711,   867, -1711, -1711,   201,
   -1711, -1711,   867, -1711, -1711, -1711, -1711,  1475, -1711, -1711,
   -1711,  1193,  1193,  1193,     5, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711,   473,   483,   545, -1711, -1711, -1711,   189,   379,
    1055, -1711, -1711, -1711,   488, -1711, -1711, -1711,    63,    63,
   -1711,   200,    91,  4403,  3663,   398, -1711,   225,   566, -1711,
   -1711, -1711, -1711, -1711,   134,   604,   555, -1711,   688, -1711,
     392,  6189, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
     609, -1711,   859, -1711, -1711, -1711,   409, -1711,  4709, -1711,
   -1711,   756, -1711,   101, -1711,   310, -1711, -1711, -1711, -1711,
     866, -1711,   121, -1711, -1711,   720, -1711, -1711, -1711,   993,
     781,   755,   447, -1711,   329, -1711,  5714, -1711, -1711, -1711,
     762, -1711, -1711, -1711,   862, -1711, -1711,  6053,  6053, -1711,
   -1711,    95,   594,   612, -1711, -1711,   632, -1711, -1711, -1711,
     668, -1711,   679,   854,  6189, -1711,   -18,    78, -1711,   -77,
   -1711, -1711,  1193,  1193,  1193,   673, -1711, -1711, -1711,  6189,
   -1711,   502, -1711, -1711, -1711,   552, -1711, -1711, -1711,   558,
   -1711, -1711, -1711, -1711,   573, -1711, -1711,   -77, -1711,   596,
     707, -1711, -1711, -1711, -1711,  1193, -1711, -1711, -1711, -1711,
     -77, -1711, -1711, -1711,  1012, -1711, -1711, -1711, -1711,  1193,
   -1711, -1711, -1711, -1711, -1711, -1711,  1193,  1193, -1711, -1711,
   -1711,  1030,  1033, -1711,  1193,  1057, -1711,  1193, -1711,  1193,
   -1711,  1193, -1711,  1193, -1711, -1711, -1711, -1711,  1193, -1711,
   -1711, -1711,  1193, -1711,  1193, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711,  1193, -1711,    91, -1711, -1711, -1711, -1711,
    1105, -1711, -1711, -1711, -1711, -1711,  1119,   529, -1711, -1711,
     837, -1711, -1711,  1046,    80, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,   259,   268,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,  1408, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711,  3713, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711,  4415, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711,   467, -1711, -1711,
     791, -1711, -1711, -1711, -1711, -1711, -1711,   793, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
    2315, -1711, -1711, -1711, -1711,   836,   670,   847,  1082, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,   873,   860,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711,   867, -1711, -1711, -1711, -1711,
      22,    60,   465,   224, -1711, -1711, -1711,  4910,  1146,  6977,
    6808,  1061, -1711, -1711, -1711, -1711,  1218,  1239,    62,  1231,
    1236,  1259,    61,  1261,  2315,  1263,  6977,  6977,   741,  6977,
   -1711, -1711,  1206,  6808,   742,  6977,  6977,  1232, -1711,  5783,
     116, -1711,  1122, -1711, -1711,   967, -1711,  1222,  1226,   609,
   -1711, -1711,   711,  1122,  1234,  1235,  1238,  1122,   859, -1711,
   -1711,   505, -1711, -1711,  6977, -1711,  5111,  1249,   857,  1308,
    1256,  3221, -1711,  1622,   503, -1711, -1711, -1711,  1250, -1711,
   -1711, -1711, -1711,  6977, -1711,  1078,  1324,  1325,   986,  1059,
     705, -1711, -1711, -1711, -1711,  1346,   944,  1345, -1711, -1711,
   -1711, -1711,  1353, -1711, -1711, -1711, -1711,   479, -1711, -1711,
    1354,  1355, -1711, -1711, -1711,  1262,  1267, -1711, -1711,   756,
   -1711, -1711,  1367, -1711, -1711, -1711, -1711,  1377, -1711, -1711,
    5312, -1711,  1377, -1711, -1711, -1711,    59, -1711, -1711,   866,
   -1711,  1380, -1711,    91, -1711,  1034, -1711,    91,    93, -1711,
    7448,  7448,  7448,  7448,  7448,  6808,   153,  7178, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711,  7448, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
     434, -1711,  1114,  1374,  1375,  1036,   897,  1391, -1711, -1711,
   -1711,  7178,  6977,  6977,  1298,   126,   369,  1394, -1711,  1018,
     369,  1302, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711,  1368,  1053,  1058,  1066, -1711,  1074,  1077, -1711, -1711,
   -1711, -1711,  1128,  1107,   835,  1122, -1711, -1711,  1332,  1333,
    1335,  1338, -1711,  1339,  1089, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711,  1343, -1711, -1711, -1711, -1711, -1711,  1193, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711,  1347,   776, -1711, -1711, -1711,
   -1711,  1349, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
     165, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711,  1331, -1711,  1265, -1711, -1711,
    1272, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
     954, -1711,   970,  1326, -1711, -1711,   900,  1386,  1275,  1275,
   -1711, -1711, -1711,  1243, -1711, -1711, -1711, -1711,  1242,  1246,
   -1711,  1247,  1257,  1274,   730, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711,  1383, -1711, -1711,  1387, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
    1052, -1711,  1091, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
    1398,  1405,  1143, -1711, -1711, -1711, -1711, -1711,  1415,   388,
   -1711, -1711, -1711,  1156,  1157,  1164,  1417, -1711, -1711,   741,
   -1711, -1711, -1711,  1426, -1711, -1711, -1711, -1711,  6977,  3221,
    1622,  1524,  5513, -1711,   121,   112,  1529,  3050,  1122,  1122,
    1430,  6808,  6977,  6977,  6977, -1711,  1448,  6977,  1504,  6977,
   -1711, -1711, -1711, -1711,  1455, -1711,   125,  1536, -1711, -1711,
     194,   243,   670, -1711,   271,   394,   138,  1520, -1711,  6977,
   -1711,   688,  1162,   746,   158, -1711,  1086,  1391,   688, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711,  1420,   341, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,   861,   950,
   -1711,   955, -1711, -1711,  6977,  1564,  6977, -1711, -1711, -1711,
     557,   603,  6977, -1711, -1711,  1214, -1711, -1711,  6977,  6977,
    6977,  6977,  6977,  1471,  6977,  6977,   176,  6977,  1377,  6977,
    1490,  1567,  1495,  2415,  2415, -1711, -1711, -1711,  6977,   944,
    6977,   944, -1711,  1560,  1561, -1711,   742, -1711,  6808, -1711,
    6808, -1711, -1711, -1711,  1114,  1374,  1375, -1711,   688, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711,  1258,  7448,  7448,  7448,  7448,
    7448,  7448,  7448,  7448,  7552,  7448,  7448,   675, -1711,  1042,
   -1711, -1711, -1711, -1711, -1711,  1489, -1711,   658,  1652, -1711,
    1144,  3425,  2545,  2885,   145, -1711, -1711, -1711, -1711, -1711,
   -1711,  1245,  1253,  1270, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,  1581, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711,  3050, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,  1252,
    1255, -1711, -1711, -1711, -1711, -1711, -1711,  1143,   230,  1491,
   -1711, -1711, -1711, -1711, -1711,  1102, -1711, -1711, -1711,  1304,
    2066, -1711,  1455,  1477, -1711,   701,   125, -1711,   228, -1711,
   -1711,  6977,  6977,  1591, -1711,  1514,  1514, -1711,   112, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,  1271,  1529,
    6189,   112, -1711, -1711, -1711, -1711, -1711, -1711,  6977, -1711,
   -1711,   173,  1316,  1318,  1610, -1711, -1711, -1711,  1328,    59,
   -1711,  6808,    59,  6977,  1589, -1711,  7400, -1711,  1444,  1350,
    1334,   746, -1711,  1514,  1514, -1711,   158, -1711,  5783, -1711,
    4442, -1711, -1711, -1711, -1711,  1637, -1711, -1711,  1117, -1711,
   -1711,  1117, -1711,  1575,  1117, -1711, -1711,  6977, -1711, -1711,
   -1711, -1711, -1711,  1078,  1324,  1325, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711,  1642,  6977,  1493,  6977, -1711, -1711, -1711,
   -1711,   944, -1711,   944,  1377, -1711, -1711,   198,  6189,  5831,
     117, -1711, -1711, -1711,  1394,  1648, -1711, -1711,  1114,  1374,
    1375, -1711,   152,  1394, -1711, -1711,  1086,  7448,  7552, -1711,
    1557,  1623, -1711, -1711, -1711, -1711, -1711,    91,    91,    91,
      91,    91,  1562,   547,    91,    91,    91,    91, -1711, -1711,
   -1711,   369, -1711,    99, -1711,  1565, -1711, -1711, -1711,   369,
     369,   369,   369,   369,  6808, -1711,  1514,  1514,  1313,  1150,
    1582,   804,  1090,  1488, -1711, -1711, -1711,   369,   369,   232,
   -1711,  6808,  1514,  1336,   804,  1090, -1711, -1711, -1711,   369,
     369,   232,  1588,  1341,  1598, -1711, -1711, -1711, -1711, -1711,
    3288,  3762,  2555,  3033,   449, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711,  1369, -1711, -1711,  1595, -1711, -1711, -1711,  1695,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,  1599,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711,  1694,   773,  1558,
    1601, -1711, -1711, -1711, -1711, -1711,  1316,  1318, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,  1328, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711,  6977, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711,  6808,  1364,   112, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711,  1362,  1688, -1711,  1607, -1711,  1615,
   -1711,  1362,  1626, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
    6977,    63,    63,   688,  1391, -1711,   124,  1627, -1711,   741,
   -1711, -1711, -1711, -1711, -1711, -1711,   369, -1711,   341, -1711,
   -1711, -1711, -1711, -1711, -1711,  6977, -1711,  1641, -1711,  1377,
    1377,  6808, -1711,   301,  1376,  1727,   688, -1711,  1394,  1394,
    1547,  1635, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711,    91,    91,    91, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711,  1636, -1711, -1711, -1711,
   -1711, -1711, -1711,   587, -1711,   369,   369,   -77, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,   855,
   -1711, -1711, -1711, -1711, -1711,   916, -1711, -1711, -1711, -1711,
   -1711,   698,   369,   -77,   808,   916, -1711, -1711, -1711,  1593,
     385,   369, -1711, -1711, -1711, -1711, -1711, -1711,  2057,   783,
    1807, -1711, -1711,  1639, -1711,  1143, -1711, -1711,  1385,   869,
    1193, -1711, -1711, -1711, -1711, -1711,  1514,  1643,   869,  1645,
    1193, -1711, -1711, -1711, -1711, -1711,  1640,  1193, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711,  6189, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711,  1462, -1711,   218, -1711, -1711, -1711,   125, -1711, -1711,
   -1711, -1711, -1711, -1711,  1653,  1466,  1455, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711,  6977,  1401,  6808, -1711, -1711,  1195,
    5831, -1711, -1711,  1573,   369,  1407,  1412,  1422,  1423,  1427,
   -1711, -1711, -1711,  1428,  1431,  1434,  1435, -1711,  1722,  6808,
   -1711, -1711, -1711, -1711, -1711,   804, -1711,  1090, -1711,  6639,
   -1711, -1711,  2407, -1711,   245,   369,   104,   369, -1711, -1711,
   -1711, -1711, -1711, -1711,  1773, -1711,  1436, -1711, -1711,   369,
     369, -1711,   369,   369,   369,   369,   369, -1711,  1651,   369,
   -1711,  1437, -1711, -1711, -1711, -1711, -1711,  1691,  1316,  1318,
   -1711, -1711, -1711, -1711,  1441,   688, -1711, -1711,  1547, -1711,
   -1711, -1711, -1711, -1711,  1445,  1446,  1449, -1711, -1711, -1711,
   -1711,  1709, -1711, -1711, -1711, -1711,  6808,   369,  1790,  1806,
   -1711,   804, -1711, -1711, -1711, -1711,   369,   855,  1713, -1711,
   -1711, -1711,   805, -1711, -1711, -1711, -1711, -1711, -1711,   132,
   -1711, -1711, -1711, -1711, -1711, -1711,  1714, -1711,  1715, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,   869, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711,  1573,  2297,  4107,
    2783,  3271,  1486, -1711, -1711, -1711,  2236,  2351,   828,   909,
    1207,   587, -1711,  6808, -1711,   855, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711,  1717,  1718,   127, -1711, -1711,  1818,   133,
   -1711,   369, -1711, -1711, -1711, -1711,   369,   369,   369,   369,
     369,  2225,  1115,  2014,   369,   369,   369,   369,   285,  1473,
    1593, -1711,  1820, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
    1728,  1715,   369, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,   385, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711,   369,   369,   369, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     394,   394,   394,   394,   394,   394,   394,   394,   398,   401,
     394,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   205,   400,     9,    25,    26,     0,   394,
     394,   394,   394,    64,    63,     3,     0,    67,     0,   395,
       0,   419,     0,    62,     0,   389,     0,     0,     0,     0,
     564,    82,    84,     0,     0,   256,     0,   278,     0,   302,
      68,   394,    69,   394,   394,   394,   394,   394,   394,   394,
       0,   394,   394,   394,   394,    70,   394,    71,   394,   394,
     394,   394,   394,   394,   394,   394,     0,   394,   394,   394,
     394,    72,   394,    73,   394,   425,   394,   425,   394,   425,
     425,   394,   394,   425,   394,   425,     0,   394,   425,   425,
       0,   394,   425,   425,   425,   425,   394,   394,   394,   425,
      32,   394,   425,   425,   394,    44,   394,   394,   394,   394,
     425,     0,   394,    76,   394,    77,     0,     0,     0,   721,
     692,   390,   391,   392,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     899,   900,   901,   902,   903,   904,   905,   906,   907,   908,
     909,   910,   911,   912,   913,   914,   915,   916,   917,   918,
     920,     0,   922,   921,     0,     0,     0,     0,    31,     0,
       0,    81,   688,   687,   693,   694,   220,   704,   705,   698,
     890,   699,   702,   706,   703,   700,   701,   695,  1006,  1007,
    1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,
    1018,  1019,    50,  1021,  1022,  1023,   696,  1232,  1233,  1234,
    1235,  1236,  1237,  1238,  1239,   697,     0,   217,   218,     0,
      30,   201,     0,    19,   203,   206,    36,   207,   399,   396,
     397,   394,   394,   394,    13,   814,   787,   789,    66,    65,
     402,   404,     0,     0,     0,   421,   420,   422,     0,   554,
       0,   672,   673,   674,     0,   881,   882,   883,   459,   460,
     886,   679,     0,     0,     0,   475,   483,     0,   507,   532,
     544,   545,   621,   627,   648,     0,     0,   926,     7,    87,
     427,   429,   442,   430,   240,   457,   438,   463,   437,    13,
     473,    56,   481,   435,   436,    43,   535,    37,     0,    51,
      57,   552,    37,   620,    37,   626,    16,    22,   448,    42,
     646,   454,     0,   455,   440,     0,   678,   439,   723,   726,
     728,   730,   732,   733,   740,   742,     0,   741,   685,   462,
     890,   443,   449,   441,   695,   458,    58,     0,     0,    61,
     413,     0,     0,     0,    86,   407,     0,    90,   271,   270,
       0,   410,     0,     0,     0,   564,   107,   109,   256,     0,
     278,   302,   394,   394,   394,    13,   814,   787,   789,     0,
      57,     0,   131,   132,   133,     0,   125,   126,   134,     0,
     127,   128,   135,   136,     0,   129,   130,     0,   137,     0,
     139,   140,   791,   792,   790,   394,    13,    33,    41,    48,
       0,    57,   182,   426,   184,   149,   150,   151,   152,   394,
     153,   155,   179,   178,   177,   171,   394,   425,   175,   174,
     176,   791,   792,   793,   394,     0,    13,   394,   156,   394,
     159,   394,   162,   394,   168,    33,    41,    48,   394,   165,
      74,    13,   394,   186,   394,   189,    41,    75,   192,   193,
     194,   195,   198,   394,   197,     0,  1028,  1025,  1026,    53,
       0,   712,   713,   714,   715,   716,   718,     0,   931,   933,
       0,   932,    49,     0,     0,  1230,  1231,    53,  1030,  1031,
      52,    18,    52,  1034,  1035,  1036,  1037,    27,     0,     0,
    1040,  1041,  1042,  1043,  1044,     9,  1062,  1063,  1057,  1052,
    1053,  1054,  1055,  1056,  1058,  1059,  1060,  1061,     0,    25,
      52,  1077,  1076,  1075,  1078,  1079,  1080,    28,    52,  1083,
    1084,  1085,    29,  1094,  1095,  1087,  1088,  1089,  1091,  1090,
    1092,  1093,    26,    52,  1102,  1099,  1098,  1103,  1101,  1100,
    1104,    28,  1107,  1110,  1106,  1108,  1109,     8,  1113,  1112,
      17,  1115,  1116,  1117,    11,  1121,  1122,  1119,  1120,    54,
    1127,  1124,  1125,  1126,    55,  1141,  1135,  1138,  1139,  1133,
    1134,  1136,  1137,  1140,  1142,     0,  1128,    52,  1174,  1175,
      14,  1228,  1225,  1226,     0,  1227,    46,    52,    25,  1245,
     958,    26,  1244,  1247,   956,   957,    31,     0,    45,    45,
       0,    45,  1251,    45,  1254,  1253,  1255,     0,    45,  1242,
    1241,    24,  1263,  1260,  1258,  1259,  1261,  1262,    21,  1266,
    1265,    15,    52,  1269,  1272,  1268,  1271,    35,    34,   894,
     895,   896,    48,   897,    31,    34,   892,   893,   973,   974,
     980,   966,   967,   965,   975,   976,   996,   969,   978,   971,
     972,   977,   968,   970,   963,   964,   994,   993,   995,    48,
       0,    12,   981,   937,   936,     0,   740,     0,     0,    45,
      24,    21,    15,    35,  1273,   941,   942,   919,   940,     0,
     686,  1020,   200,   219,    78,   202,    79,    80,   208,   209,
     211,   210,   213,   214,   212,   215,   811,   811,   811,    92,
       0,     0,   507,     0,   416,   417,   418,     0,     0,     0,
       0,     0,   888,   887,   884,   885,     0,     0,     0,    34,
      34,     0,     0,     0,     0,    12,     0,     0,   516,     0,
     505,   506,     0,     0,     0,     0,     0,     0,     6,     0,
       0,   744,     0,   428,   431,     0,   434,     0,     0,   474,
     477,   444,     0,     0,     0,     0,     0,     0,   482,   484,
     445,     0,   531,   446,     0,    44,     0,     0,    18,    27,
       9,    25,   852,    26,     0,   856,   854,   855,     0,    37,
      37,   842,   843,     0,   582,   585,   587,   589,   591,   592,
     597,   602,   600,   601,   603,   605,   543,   569,   570,   580,
     844,   571,   578,   572,   579,   575,   576,     0,   573,   574,
       0,   604,   577,   447,   456,     0,     0,   561,   560,   553,
     556,   450,     0,   639,   640,   641,   619,   624,   637,   451,
       0,   625,   630,   452,   453,   642,     0,   664,   665,   647,
     649,   652,   662,     0,   690,     0,   689,     0,     0,   680,
       0,     0,     0,     0,     0,     0,     0,     0,   874,   875,
     876,   877,   878,   879,   880,    18,    27,     9,    25,    28,
     867,    26,    28,     8,    17,    11,    54,    55,    50,    14,
      46,    37,     0,   857,   827,   858,   737,   738,   839,   826,
     816,   815,   831,   833,   835,   837,   838,   825,   859,   860,
     828,     0,     0,     0,     0,     7,     0,   781,   780,   838,
       0,     0,   358,    57,   224,   241,   257,   284,   303,   423,
     106,     0,     0,     0,     0,   113,     0,     0,   811,   811,
     811,   115,     0,     0,   507,     0,   124,   147,     0,     0,
       0,     0,   138,     0,     0,   811,   142,   145,   143,   146,
     148,   170,     0,   185,   154,   173,   172,    12,   394,   158,
     157,   160,   163,   169,   164,   161,   167,   166,   188,   187,
     190,   191,   196,   199,  1027,     0,     0,    52,   709,   710,
      20,     0,   929,   722,    39,    39,  1229,  1032,  1029,  1038,
    1033,    18,    25,    18,    25,  1039,  1064,  1065,  1066,  1067,
      25,  1049,  1074,  1073,  1082,  1081,  1086,  1097,  1096,  1105,
    1111,  1114,  1118,  1123,    10,  1159,  1165,  1163,  1154,  1155,
    1158,  1160,  1149,  1150,  1151,  1152,  1153,  1161,  1156,  1157,
    1162,  1130,  1164,  1129,  1176,  1173,  1180,  1177,  1178,  1179,
    1181,  1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,
    1191,  1192,  1193,  1194,  1211,    47,  1223,  1246,   952,   953,
     959,    45,   954,  1243,     0,  1248,  1250,     0,  1252,  1240,
    1257,  1264,  1270,  1267,   891,   898,   889,   979,   982,   983,
       0,   985,     0,   984,   986,   987,    12,    12,   988,   960,
       0,     0,   934,  1275,  1274,  1276,  1277,  1278,     0,     0,
     707,   204,   216,     0,     0,     0,     0,   323,    13,   516,
     348,    33,   328,     0,    41,   353,   788,    48,     0,    25,
      26,   546,     0,   555,     0,   666,   668,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     0,   988,     0,
     476,    33,   514,   515,     0,    41,     0,     0,   661,    42,
     656,   655,     0,   660,   658,   659,     0,   633,   635,     0,
     756,     7,     7,   758,   753,   755,   838,   777,     7,   743,
     424,   249,   479,   480,   478,   497,    18,     0,     0,   495,
     491,   486,   487,   488,   489,   492,   490,   485,     0,     0,
      50,     0,   611,   853,     0,   606,     0,   845,   848,   849,
     846,   847,     0,   851,   850,     0,   569,   578,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   613,     0,
       0,     0,     0,     0,     0,   558,   559,   557,     0,     0,
       0,   628,   651,   656,   655,   650,     0,    10,     0,   682,
       0,   681,   724,   725,   727,   729,   731,   734,     7,   464,
     466,   739,   846,   866,   847,   868,   865,   864,   869,   862,
     863,   861,   870,   871,   872,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   822,   821,   838,
     924,  1005,   783,   782,    59,     0,    60,     0,     0,   104,
       0,     0,     0,     0,     0,    57,   224,   241,   257,   284,
     303,     0,     0,     0,    13,    33,    41,    48,   414,   403,
     405,   408,   411,   303,    12,   183,   180,    12,     0,   717,
     711,   708,    49,   719,   720,  1045,  1047,  1046,  1048,    52,
    1069,  1071,  1070,  1072,  1051,    25,     0,  1171,  1143,  1168,
    1145,  1172,  1148,  1169,  1170,  1146,  1166,  1167,  1144,  1147,
    1208,  1207,  1209,  1210,  1216,  1198,  1199,  1200,  1201,  1213,
    1202,  1203,  1204,  1205,  1206,  1214,  1215,  1217,  1218,  1219,
    1220,  1221,  1222,    52,  1197,  1196,  1212,    46,   955,     0,
       0,    25,    25,    26,    26,   961,   962,   934,   934,     0,
      23,   939,   943,   944,    31,     0,   338,   343,   333,     0,
       0,    93,     0,     0,   100,     0,     0,    95,     0,   102,
     548,     0,     0,   547,   669,     0,     0,   763,   667,   759,
    1159,  1163,  1158,  1162,  1164,    50,    10,    10,     0,   752,
       0,   750,    34,    34,    12,   471,    12,    12,     0,    12,
     504,     0,   517,   520,     0,   513,   509,   508,   510,     0,
     643,     0,     0,     0,     0,   747,     0,   748,     0,    13,
       0,   757,   766,     0,     0,   776,   754,   764,   746,   745,
       0,   496,    25,   500,   501,    50,   499,   533,     0,   537,
     534,     0,   539,     0,     0,   541,   612,     0,   616,   618,
     581,   583,   584,   586,   588,   590,   598,   599,   593,   596,
     595,   594,   608,   607,     0,     0,     0,   997,   998,   999,
    1000,   622,   638,   629,   631,   663,   691,     0,     0,     0,
       0,   467,   873,   824,   818,     0,   829,   830,   832,   834,
     836,   823,   735,   817,   736,   840,   841,     0,     0,   735,
       0,     0,    57,   360,   359,   362,   361,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    83,   226,
     225,     0,   223,     0,    52,     0,    85,   243,   242,     0,
       0,     0,     0,     0,     0,   267,     0,     0,     0,     0,
       0,     0,     0,     0,    88,   259,   258,     0,     0,     0,
     432,     0,     0,     0,     0,     0,    89,   286,   285,     0,
       0,     0,     0,     0,     0,    13,    91,   305,   304,   123,
       0,     0,     0,     0,     0,   338,   343,   333,   116,   121,
     117,   122,     0,   144,   181,     0,   930,  1068,  1050,     0,
    1195,  1224,  1249,  1256,   989,   990,   991,   992,    38,     0,
      23,   935,   951,   947,   946,   945,    31,     0,     0,     0,
       0,    13,   325,   324,   327,   326,   517,   520,    33,   350,
     349,   352,   351,    41,   330,   329,   332,   331,   510,    48,
     355,   354,   357,   356,   549,   551,     0,   393,   761,   762,
     760,  1132,   928,   927,     0,     0,   751,   925,   923,  1002,
     472,  1003,    12,  1001,     0,   522,   524,     0,    33,     0,
      33,     0,     0,    41,   657,   653,   654,    42,    42,   634,
       0,     0,     0,     7,   778,   779,     0,     0,   768,   516,
     767,   774,   775,   765,   461,   250,     0,   494,     0,   493,
      52,    52,    44,    52,   609,     0,   615,     0,   617,   623,
     632,     0,   670,     0,     0,     0,     7,   465,   820,   819,
     565,     0,   105,   415,   322,   406,   240,   409,   256,   278,
     412,   302,   222,     0,     0,     0,   322,   322,   322,   322,
     227,   387,   388,    40,   386,   385,     0,   383,   244,   246,
     245,   248,   247,     0,   254,     0,     0,     0,   301,   300,
      40,   299,   363,   365,   366,   364,   319,   367,   320,     0,
     318,   274,   275,   277,   276,     0,   273,   268,   269,   265,
     433,     0,     0,     0,     0,     0,   297,   296,   294,     0,
       0,     0,   308,   108,   110,   111,   112,   114,     0,     0,
       0,   141,    10,     0,   938,   934,   950,   948,     0,     0,
       0,    12,   340,   339,   342,   341,     0,     0,     0,     0,
       0,    12,   345,   344,   347,   346,     0,     0,    12,   335,
     334,   337,   336,   784,    94,   812,   813,   101,    96,   786,
     103,   550,     0,   683,  1004,   526,   527,   528,   529,   530,
     519,     0,   502,     0,   521,   503,   523,     0,   512,   644,
     645,   636,   749,    12,     0,     0,     0,   251,   498,    28,
      28,   542,   540,   610,     0,     0,     0,   671,   677,     0,
     469,   468,   566,   567,     0,     0,     0,     0,     0,     0,
     322,   322,   322,     0,     0,     0,     0,   384,     0,     0,
     261,   263,   264,   266,   298,     0,    52,     0,   262,     0,
     287,   295,     0,   293,     0,     0,     0,     0,   311,   309,
      12,    12,    12,  1024,     0,    23,     0,    54,    50,     0,
       0,    98,     0,     0,     0,     0,     0,    99,     0,     0,
      97,     0,   518,   525,   511,   772,    12,     0,   517,   520,
     536,   538,   614,   675,     0,     7,   568,   562,   565,   358,
     241,   257,   284,   303,     0,     0,     0,   323,   348,   328,
     353,     0,   255,   321,   260,   272,     0,     0,     0,   252,
      57,     0,    13,    33,    41,    48,     0,     0,     0,   377,
     371,   370,   374,   369,   372,   373,   306,   316,   315,     0,
     312,   317,   307,   119,   120,   118,     0,   949,     0,   797,
     796,   803,   805,   808,   809,   806,   807,   810,     0,   799,
     684,   773,    13,    33,    33,   676,   470,   567,     0,     0,
       0,     0,     0,   338,   343,   333,     0,     0,     0,     0,
     382,     0,   290,     0,   283,     0,   279,   281,   280,   282,
      52,    52,   378,     0,     0,     7,   310,  1131,     0,     0,
     800,     0,   769,   770,   771,   563,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   291,   253,    52,   292,   288,   376,   375,   314,   313,
       0,     0,     0,    52,    57,   228,   229,   230,   231,    12,
      12,    12,    13,    33,    41,    48,   379,   380,     0,   368,
     289,   802,   801,    40,   798,   239,     0,     0,     0,   232,
     237,   233,   238,   381,   804,   235,   236,   234
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1711, -1711,    -1, -1136,   918,    55, -1195,   922,  1038,  -325,
     920,  1130, -1711,   926,  -473, -1711, -1711,  1132, -1711, -1500,
    1136,    -4,   -21,  1321,  -558, -1711, -1711,  -609, -1711,  -433,
    -631,  1139, -1711,  -258, -1711,   830, -1710,  -464, -1110, -1711,
    -781,  -544,  -833, -1711,  -457,   487,  -889, -1711,   -88,  1342,
    -890,   936, -1711,  -404,    17, -1711, -1711,  1841, -1711, -1711,
   -1711, -1711, -1711, -1711,  1614, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,     7,
   -1711,  1467, -1711,   526,  -316, -1269, -1711, -1711, -1512,  -379,
   -1268,  -389,   229,  -112,  -391, -1711, -1266, -1273, -1711,  -390,
   -1278,  -302, -1711,  -247,   -96, -1525,  -959,  -157,  -155, -1561,
   -1555, -1554,  -156,  -148,  -140, -1711, -1711,  -256, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711,   216,  -726, -1306,  1810,
       3,  3168, -1711,  1248, -1711, -1711,   327, -1711,   314,   839,
   -1711, -1711,  2334, -1711,  -669,  1512, -1711, -1711,   222,  1816,
    1035,  2870,   -38, -1711, -1711, -1283, -1255,  -318, -1711, -1711,
   -1711, -1711, -1711, -1711,   122, -1711, -1711, -1711, -1711,  1120,
   -1711, -1711, -1711,  1112, -1711, -1711, -1711,   143, -1711,  1604,
   -1355,   207, -1711, -1080, -1562, -1366, -1537, -1354,   177,   178,
   -1711, -1711,  -798, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
    1063,  -307,  1522,  -104,  -169,  -151,   680,   681,   682, -1711,
    -722, -1711, -1711, -1711, -1711, -1711, -1711,  -585, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711,  -296,   666, -1711,
   -1711, -1711, -1711,  1060,   451,  -821,   445,  1172,   671, -1215,
   -1711, -1711,  1658, -1711, -1711, -1711, -1711,  1062, -1711, -1711,
     -59,   -17,  -782,  -300,   980,   -25, -1711, -1711, -1711,   933,
      -9, -1711, -1711, -1711, -1711, -1711,  -145,  -204, -1711, -1711,
     640,  -737,  1752,   -32, -1711,   750, -1188, -1711, -1442, -1711,
   -1711,   492, -1311, -1711, -1711,   458,   463, -1711, -1711,  1596,
    -565,  1566,  -547,  1568,  -530,  1569,  1853, -1711, -1709, -1711,
   -1711,  -185, -1711, -1711,    30,  -527,  1572, -1711,  -335,  -281,
    -794,  -790,  -787, -1711,  -319,  -751, -1711,  -224,  1850,  -785,
   -1711, -1407,  -284,    85,  1676, -1711,   -22, -1711,   287, -1711,
   -1334, -1711,   292, -1711, -1711, -1711, -1711, -1711,   300,  -255,
     686,  1344,   891,  1679,  1689, -1711, -1711,  -459,    40, -1711,
   -1711, -1711,   996, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711,  1379,  -980, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,   917,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711, -1711,
   -1711, -1711, -1711, -1711, -1711
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,  1647,   779,  1049,  1239,  1376,  1051,  1129,   739,
    1075,  1111,   873,  1050,  1237,   726,  1361,  1110,   874,  1682,
    1109,  1292,  1294,  1238,  1043,  1045,   724,   717,   480,   987,
    1114,  1113,   727,   803,  1874,  1363,  1967,   988,   875,   800,
     487,  1102,  1096,  1417,   989,  1022,   721,   853,  1027,  1014,
    1052,  1053,   791,   854,  1648,    45,    46,    47,    72,    85,
      87,   414,   418,   423,   410,   101,   103,   130,   993,   442,
     135,   143,   145,   260,   263,   266,   267,   735,  1141,   261,
     211,   382,  1601,  1330,   383,  1331,  1510,  2047,  1823,   386,
    1332,   387,  1845,  1846,   390,  2056,  1333,  1627,  1830,   392,
    1334,  1987,  2069,  2070,  1838,  1839,  1955,  1440,  1445,  1689,
    1687,  1688,  1443,  1448,  1328,  1840,  1609,  1985,  2062,  2063,
    2064,  2150,  1610,  1611,  1813,  1814,  1793,   212,  1718,    48,
      49,    59,   417,    51,   421,  1796,    65,   426,  1798,    69,
     431,  1801,   412,   413,  1794,   285,   286,   287,    52,   394,
    1457,   444,  1613,   320,   321,  1629,   322,   323,   324,   325,
     326,   327,  1289,  1560,  1561,   328,   329,   330,   789,   790,
     331,   332,   798,   799,  1226,  1220,  1515,  1516,   333,  1153,
    1488,  1743,   334,  1184,  1738,  1482,  1740,  1483,  1484,  1920,
     335,   336,  1519,   802,   337,   338,   339,   340,   341,   859,
     860,  1586,   381,  1953,  2027,   824,   825,   826,   827,   828,
     829,   830,  1539,   831,   832,   833,   834,   835,   836,   342,
     343,   866,   344,   345,   871,   346,   347,   867,   868,   348,
     349,   350,   879,   880,  1187,  1188,  1189,   881,   882,  1164,
    1165,   351,   352,   353,   354,   355,   888,   889,   356,   357,
     213,   837,   885,   924,   838,   358,   217,  1020,   506,   507,
     839,   514,   359,   360,   361,   362,   363,   364,   926,   927,
     928,   365,   366,   367,   780,   781,  1470,  1471,  1202,  1203,
    1204,  1458,  1459,  1506,  1501,  1502,  1507,  1205,  1753,   946,
    1695,   740,  1707,   742,  1713,   743,   435,   465,  1999,  1902,
    2129,  2130,  1885,  1895,  1143,  1702,   741,   368,   947,   948,
     932,   933,   934,   935,  1206,   937,   840,   841,   842,   940,
     941,   369,   754,   843,   675,   676,   220,   371,   844,   512,
    1430,   705,   845,  1139,   718,  1434,  1686,   223,   846,   637,
     848,   638,   849,   700,   701,  1126,  1127,   702,   850,   851,
     372,   373,   852,   228,   500,   229,   521,   230,   527,   231,
     535,   232,   549,  1040,  1375,   233,   557,   234,   562,   235,
     572,   236,   581,   237,   587,   238,   590,   239,   594,   240,
     599,   241,   604,   242,   375,   616,  1071,  1464,  1073,  1388,
    1380,  1385,  1378,  1382,   243,   620,  1094,  1416,  1399,  1405,
    1394,  1095,   244,   626,   245,   517,   246,   247,   651,   248,
     639,   249,   641,   250,   643,   251,   648,   252,   658,   253,
     661,   254,   667,   255,   714
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   706,    53,   784,   786,   216,   977,   388,   785,   966,
     965,   967,  1005,   214,   319,   755,   270,  1156,    44,   964,
    1006,   218,  1011,  1048,  1233,   384,  1299,  1100,  1207,  1301,
     370,   930,   269,   748,   389,   214,  1193,   991,   982,   264,
     984,   370,  1004,   218,  1116,   279,   214,   936,  1028,   872,
    1641,   990,   886,   376,   218,  1272,  1210,   379,   949,   949,
    1639,   777,  1654,  1557,   719,  1495,  1497,  1221,  1651,  1442,
    1652,  1225,  1508,  1653,   953,  1662,  1696,  1630,  1630,  1490,
     971,   963,  1556,   847,   861,   931,   869,  1303,  1697,  1755,
     268,  1708,  1558,  1678,  1680,  1103,  1870,  1105,  1284,  1106,
    1868,  1245,  1869,  1285,  1108,  1282,  1283,  1286,   443,  1854,
     443,   986,   443,   443,  1290,   219,   443,  1785,   443,  1851,
    1974,   443,   443,  1208,  1786,   443,   443,   443,   443,  1116,
     778,   778,   443,   951,  1905,   443,   443,   219,   887,  2125,
    2161,   999,   938,   443,   883,  1276,     3,  1720,   219,     4,
    1719,     5,  1559,   938,   938,   282,  1008,   677,  1170,  -692,
    1906,   150,  1161,  1175,  1163,  1133,    55,  -692,  -692,  -692,
    -692,     6,     7,     8,     9,  1148,   883,  1811,  1812,  2004,
    1876,  1180,  1181,    54,  1185,   862,  1642,  1465,   214,  1643,
    1197,  1198,   214,  1734,    55,  1154,   218,  1761,  1762,   883,
     218,  1455,  -687,  1781,  1456,    71,  1024,  2067,  2068,  -687,
    -687,  -687,  -687,  1157,  1151,  1115,  -653,   588,   773,  1232,
     621,  1235,  1491,    56,    57,    58,  1933,   703,  1486,     3,
    2067,  2068,     4,   589,     5,    63,     4,   704,     5,   753,
     753,  1128,  1117,   644,   508,   509,   510,  1503,  -687,  1156,
    1504,  -694,   622,   623,     6,     7,     8,     9,  -694,  -694,
    -694,  -694,   756,   722,   280,  -654,   281,  2058,    86,   725,
     617,  1722,  1723,   747,  1783,   380,  1735,   318,  1369,  -702,
     385,   677,   210,   624,   391,  1271,  -702,  -702,  -702,  -702,
     219,   102,  -785,   884,   219,  1370,   774,  -694,   757,   370,
    1371,  1372,  1630,   144,   214,  1178,  1946,  1644,   409,  1146,
    1825,  1826,   218,   265,   628,   256,   625,   221,   645,   646,
     647,  2013,   222,   618,   619,  -702,  1852,   151,   152,   153,
     224,   151,   152,   153,   929,   262,  -221,   895,   631,   221,
     388,  1523,    66,    67,   222,   929,   929,  2059,  2060,   923,
     221,  1293,   224,   896,  1295,   222,   960,  1320,  1321,  -785,
     923,   923,  1149,   224,   377,  1176,  1025,   389,   388,  1031,
    1641,   976,   370,     4,  1850,     5,  1147,   214,  1033,  2131,
    1639,   388,  1454,   897,  1032,   218,  1850,   370,   151,   152,
     153,   271,   214,  1034,   870,   389,  1669,  1630,  1630,   378,
     218,  1373,  -703,   398,   399,   400,   219,  1344,   389,  -703,
    -703,  -703,  -703,  1487,  1150,  1720,  1171,   493,   210,   425,
     427,   428,   210,   863,   864,   865,   720,  1346,  1934,   440,
    1645,  1522,  -240,  1525,  1029,   402,   283,   284,   451,   452,
     513,  1306,  1466,  1467,   458,  1347,  1345,  1280,  -703,   952,
       3,   640,   782,     4,  1307,     5,  2093,  2057,   210,   511,
     443,  1736,  1042,   210,  1492,   490,   491,  2048,  1623,   494,
    1044,  1209,  1787,  2194,  1540,     6,     7,     8,     9,   219,
     210,  1323,  2094,   305,  1513,  1047,   210,  2126,  2162,  1514,
    1642,   642,   221,  1643,   219,  2077,   221,   222,   782,   307,
    1646,   222,  1623,   461,   308,   224,  1736,  1288,  1785,   224,
    -692,   767,   210,   628,   752,   752,  1568,   305,   758,   456,
     457,  1569,   432,  1566,  1567,  1570,  2115,   768,  1850,  1074,
     318,   649,  1537,   307,  2111,   210,  1912,   631,   308,  1097,
    1258,  1995,  2025,   723,  2143,  1041,  1166,  1432,  2141,  1329,
    2142,  1046,  -687,  1782,   708,   938,   650,  1418,  1365,   978,
    1367,  1243,  1244,  1259,  1429,  1260,  1945,  1679,   782,  1192,
    2018,  1623,  2014,  1450,  1112,   744,  1721,  1453,  1155,   272,
    2002,   273,  2019,  1709,  1671,   745,   305,  1472,  1473,  1474,
    1035,     4,  1477,     5,  1479,  1969,   886,  2061,   257,   258,
     259,  -694,   307,  1305,   210,    55,  1317,   308,   221,   979,
    1099,  1644,   630,   222,  1494,   980,  1291,  1932,   257,   258,
     259,   224,  1319,   403,  1098,   404,  1769,   380,   628,  -702,
     981,   280,   863,   864,   865,   281,  1803,  1929,  1930,   776,
     385,  -952,  1017,  -952,   210,   391,  1228,   746,   630,  1526,
    1950,  1528,   631,   983,  1335,    55,  1947,  1529,   751,  1229,
    1318,    55,     4,  1304,     5,   749,   938,   938,   938,   938,
     938,  1748,  1542,   938,  1543,  1230,    55,  1993,   895,  1936,
     628,   221,  1306,  1551,   766,  1553,   222,  -953,   775,  -953,
    1447,   462,   778,   434,   224,  1577,   221,  1580,   938,    55,
    1449,   222,     3,  1979,   631,     4,  1969,     5,   463,   224,
     433,  1013,   434,  1255,  1190,  1261,   225,   938,  1444,   558,
    1770,  1485,  1156,  1771,   897,   801,  1773,     6,     7,     8,
       9,  2024,   782,   214,  1645,   634,   635,  1433,   225,  1986,
     559,   218,  1142,  1511,   210,  1754,   627,  1201,  1480,   225,
    1287,   659,  -703,   560,  1193,  2102,   214,  1207,   628,  1256,
     629,  2099,   923,  2100,   218,   887,  2101,  1144,  1145,   770,
     771,   634,   635,   893,     3,  1262,   660,     4,   630,     5,
    1018,  1019,   631,   995,     3,   632,   591,     4,  1215,     5,
     715,   716,  1241,  -952,   855,   856,   592,   593,   892,     6,
       7,     8,     9,  -507,  1867,   894,  1246,  1240,  1207,     6,
       7,     8,     9,  1982,   942,   636,  1975,  1273,  1641,  1152,
    1012,  1216,  1231,  1441,  1804,  1683,  1805,  2123,  1639,     3,
    2124,   136,     4,   137,     5,   219,  1217,   884,   138,  -953,
     139,  1727,  1728,  1413,   140,  1630,  1630,  1963,  1964,  1965,
    1966,   636,   769,  -952,     6,     7,     8,     9,   219,     4,
    1414,     5,  1886,  1975,   886,   929,  1714,  1715,   633,  1887,
     770,   771,  1886,   923,   923,   923,   923,   923,   214,  1887,
     923,  1218,  1660,   141,  1435,   142,   218,   501,   502,  2096,
    1661,   225,  1415,  1732,   278,   225,   787,   788,     4,  -953,
       5,   634,   635,   561,  1313,   923,  1888,  1832,  1749,   929,
       3,   282,  1659,     4,   943,     5,  1888,  1314,   401,  1315,
       4,   226,     5,  1977,   923,  1806,  1807,  1808,  1809,  1360,
    -507,  1649,  1833,  1834,   430,     6,     7,     8,     9,   652,
    1889,   857,  1774,   226,   858,  1324,   582,   595,   954,  1326,
    1889,   596,   131,   454,   226,   653,   886,   132,   133,  1776,
    -785,  1778,   583,   150,  1517,  1219,   955,  1469,   518,   519,
     520,   584,  1564,   134,  1518,  1554,   654,   585,   586,  1573,
     219,   636,   655,   597,   598,   600,   956,  1563,  1565,  2158,
     662,  1941,   515,   516,  1571,  1565,  1574,  1576,  1341,  1342,
    1343,  2034,  2035,  2036,   663,   770,   771,   225,   890,   891,
     215,   664,   151,   152,   153,  1354,  1498,   601,   602,  1658,
     603,   792,   957,   503,   504,  1313,   227,   505,  1366,   665,
    1368,  1499,   215,   958,  1997,   666,  1374,   221,  1325,  1998,
    1315,   782,   222,   215,  1890,  1182,  1183,  1500,   374,  1313,
     224,  1835,   150,  1517,  1890,   992,  1703,   150,  1517,   374,
     221,  -302,  1578,  1521,  1315,  1194,   656,   657,  1524,   877,
     878,  1836,  1837,  1195,  1166,  -794,  1469,  1877,  -795,  1253,
     225,  1254,   938,   938,   938,   938,   938,   938,   938,   938,
     938,   938,   938,  1248,  1249,   225,   226,  1531,  1532,  1277,
     226,   709,   998,  1279,  1538,   884,  1325,  2079,  1315,  2080,
     710,   711,  1015,   782,   712,   713,     3,   291,   292,     4,
    1390,     5,   293,   782,  1391,  1392,  1393,  1016,  1891,  1308,
    1309,  1911,   770,   771,  1960,  1961,  1962,  1021,  1991,   770,
     771,     6,     7,     8,     9,     3,  1383,  1384,     4,  1023,
       5,  1104,  1725,  1107,   214,   793,   794,   795,   796,   797,
    1386,  1387,   218,  1421,  1422,  1931,   778,  1496,   782,  1130,
       6,     7,     8,     9,  1758,  1841,  1842,  1843,  1792,  1844,
    1131,  1587,   221,  2146,  1132,   215,   573,   222,   574,   215,
    1943,  1588,   876,   877,   878,   224,  1589,   884,  1590,  1207,
    1591,   227,  1423,  1424,  1886,   227,   449,   575,   257,   258,
     259,  1887,   226,  1684,  1685,   576,   577,  1140,   578,   150,
    1517,    18,    19,  1138,  1541,   151,   152,   153,   579,   580,
    1162,  1246,  1246,  1246,  1246,  1246,  1167,  1246,  1246,  1908,
    1784,  1168,  1788,  1789,  1828,  1829,  1547,  1547,  1888,   782,
    2148,  2149,  1910,    18,    19,  1779,   219,  1780,  1565,  1565,
      62,   214,  1169,   214,  2147,  1907,   863,   864,   865,   218,
      34,   218,   938,   295,   296,   297,  1751,  1752,   300,  1928,
      35,  1667,  1889,  1172,   938,   226,    36,  1192,  1173,   923,
     923,   923,   923,   923,   923,   923,   923,   923,   923,   923,
     226,   215,    34,  1549,  1550,  1922,  1592,  1925,  1186,   370,
      37,  1174,    35,  1177,   214,  1179,  1199,   374,    36,   393,
    1862,  1211,   218,   397,  1212,  1670,  1581,  1583,  1213,  1599,
    1607,  1625,  1637,  1236,  1242,   938,  1222,  1223,   420,   393,
    1224,  1250,    37,  1251,  1252,  1584,   925,  1600,  1608,  1626,
    1638,  1257,  -997,   938,   938,   783,   447,   925,   925,  2022,
    -998,  1263,  1264,   219,  1265,   219,  1904,   528,   529,  1266,
       3,  1668,  1268,     4,   215,     5,   530,   531,   532,   533,
     534,  2020,  2021,  1156,  1269,   489,  1890,  1276,  1278,   215,
     374,  1310,   495,  1311,  1312,     6,     7,     8,     9,  1316,
    1322,  1306,  1676,  1677,  1327,   374,   951,  1336,  1958,  1149,
    1642,  1959,  1337,  1643,  1593,  1146,   219,  1674,  1675,  1957,
    1338,   522,  2176,   523,   524,   525,   526,  1377,  1339,  1594,
    1745,  1340,  1190,  1273,  1348,  1349,   225,  1350,  1973,  1692,
    1351,  1352,  1699,  1353,  1704,  1595,  1355,  1710,   370,  1358,
    1596,  1362,  1597,   214,  1379,   782,  1389,  1693,   221,   225,
    1700,   218,  1705,   222,  1981,  1711,  1381,  1407,   755,  1408,
    2170,   224,  1766,  1409,   214,  1410,  1201,  1429,     3,   923,
    1956,     4,   218,     5,   782,  1419,  1411,     3,   370,  1420,
       4,   923,     5,   214,  1400,  1401,  1402,  1403,  1404,  1598,
    1427,   218,  1412,     6,     7,     8,     9,  1428,  1767,  1765,
    1436,  1437,     6,     7,     8,     9,  1816,  1431,  1438,  1439,
    1469,   728,   550,   729,   551,   730,   731,  1642,  1446,  1451,
    1643,  1644,  1468,   732,   733,   496,   370,   895,   497,   498,
     499,   214,   923,   552,  1815,  1036,  1037,  1038,  1039,   218,
    1476,   553,   554,   555,   556,   219,  1478,  1481,  1489,     3,
     923,   923,     4,  1493,     5,   221,   734,   221,  1512,  1527,
     222,  1530,   222,  1536,  1544,  1545,   219,  1166,   224,  1546,
     224,   225,  -653,  -654,     6,     7,     8,     9,  1665,  1824,
    2118,  1579,  1690,  1681,  2011,   219,  1716,   214,  2119,  1655,
    1810,  1395,  1396,  1397,  1398,   218,  1824,  1656,  1818,  1819,
    1820,  1821,  1822,  1672,   214,  1562,  1673,  1717,   221,  1737,
    2117,  1739,   218,   222,  1657,  1724,  1847,  1848,  1849,   370,
    1741,   224,  1750,  1756,   214,  1742,  1759,  1757,  1856,  1857,
    1858,   226,   218,   219,  1768,  1772,  2114,  1775,  1644,  1599,
    1607,  1625,  1637,     3,  1645,  1313,     4,  1777,     5,  1790,
    2133,  2134,  1791,  1817,   226,  1802,  1827,  1600,  1608,  1626,
    1638,  1896,  1915,  1916,  1917,  1918,  1919,   762,     6,     7,
       8,     9,  1939,  1940,  1831,  1942,  1882,  1892,  1899,  1853,
     951,  1859,   753,   753,  1860,     3,  1861,  1872,     4,   219,
       5,  1875,  1873,  1903,  1883,  1893,  1900,   214,  -525,  1921,
    2191,   436,   437,   438,   439,   218,   219,  1923,  2192,  1913,
       6,     7,     8,     9,  1871,  1944,   938,  2116,  1927,  1935,
     215,  1948,  1949,   563,   564,  1952,   219,  1954,  1996,  1968,
    2190,  1994,  1166,  1984,  2008,  2003,   227,  2005,   565,  2012,
     566,   567,   568,  1191,  2017,  2016,  2023,   221,  2026,   925,
    2185,  2029,   222,  2041,   214,  1937,  2030,  2132,   388,   227,
     224,  1645,   218,   569,   570,   571,  2031,  2032,   221,  1149,
    2076,  2033,  2037,  1194,  2088,  2038,   226,  1878,  2039,  2040,
    2078,  1195,  2090,  2092,   388,   389,  2095,   221,  2113,  2103,
    2104,  1988,   222,  2105,  1795,  1797,  1797,  1800,     3,   219,
     224,     4,  2110,     5,  -254,  2122,  2127,   782,  2128,  2156,
    2157,   389,  1970,  2160,  1971,  1972,  2178,  1879,  -255,  1897,
    2181,  1296,  1698,     6,     7,     8,     9,  1298,  1976,  1302,
    1297,  2140,  1136,  1135,  1978,   221,  1134,  2189,  1030,  1666,
     222,  1980,  1137,  1300,  1983,  1364,  1274,   225,   224,  1026,
    1989,    70,  1650,   962,  1855,  2045,   219,  1882,  1892,  1899,
     925,   925,   925,   925,   925,   215,  2193,   925,  2159,  2043,
    2106,   467,  2107,  2000,  2108,  1883,  1893,  1900,  2044,  2098,
     370,   227,  2109,  2006,  2179,   214,    18,    19,   782,   415,
    2009,   221,   925,   218,  1799,   959,   222,   422,  1951,  1214,
    1227,  1938,   772,  1898,   224,  1909,  1924,   961,   221,  1926,
    1896,   925,  1267,   222,  2097,  2065,   469,  2071,  2135,   214,
    1533,   224,  1534,   923,  1535,  1552,  1747,   218,   221,  1275,
    1744,    18,    19,   222,  2042,    34,  1196,  1555,   750,  1359,
    1281,   224,   214,  2028,  2049,    35,  1575,   707,  1509,  1760,
     218,    36,   214,  1726,   225,  1880,   225,   752,   752,  1763,
     218,   972,    73,   464,   950,   974,  2182,   975,   973,   760,
      74,  1101,    75,   764,  2066,    37,  2072,    76,    77,    78,
      34,    79,   782,   765,  1072,     0,  1406,   219,  2081,  2082,
      35,  2083,  2084,  2085,  2086,  2087,    36,  1582,  2089,     0,
       0,   221,     0,     0,     0,     3,   222,   225,     4,     0,
       5,  1824,     0,     0,   224,     0,     0,     0,     0,   214,
      37,   219,  2154,  2155,   782,  1356,     0,   218,     0,     0,
       6,     7,     8,     9,     0,     0,  2112,     0,     0,  1881,
       0,     0,     0,     0,   219,  2120,  2121,     0,     3,     0,
       0,     4,   226,     5,   219,  2180,  2071,     3,   221,     0,
       4,     0,     5,   222,     0,  2184,     0,   370,  1897,     0,
       0,   224,   214,     6,     7,     8,     9,     0,  2152,  2177,
     218,     0,     6,     7,     8,     9,   214,  1583,  1607,  1625,
    1637,     0,     0,     0,   218,  1692,  1699,  1704,  1710,     0,
    2151,     0,     0,     0,  2153,  1584,  1608,  1626,  1638,  1988,
       0,     0,     0,  1693,  1700,  1705,  1711,  1896,     0,     0,
    2163,   219,     0,     0,     0,  2164,  2165,  2166,  2167,  2168,
    1882,  1892,  1899,  2172,  2173,  2174,  2175,   782,     0,     0,
    1878,   215,     0,     0,     0,     0,   225,     0,  1883,  1893,
    1900,  2183,  1992,     0,  1425,  1426,     0,   227,     0,   226,
       0,   226,     0,     0,     0,     0,     0,   225,     0,     0,
       0,     0,     0,     0,   219,  2195,  2196,  2197,     0,     0,
    1879,     0,     0,     0,     0,     0,   225,     0,   219,   221,
       0,     0,     0,   471,   222,    80,     0,     0,  1520,  1520,
       0,  1520,   224,  1475,     0,     0,   939,     0,    18,    19,
      81,     0,   226,     0,     0,     0,     3,   939,   939,     4,
       0,     5,     0,   221,     0,     0,    82,     3,   222,  1505,
       4,    83,     5,    84,   225,     0,   224,     0,     0,     0,
       0,     6,     7,     8,     9,     0,   221,     0,   215,     0,
     215,   222,     6,     7,     8,     9,   221,    34,     0,   224,
       0,   222,     0,     0,   227,     0,   227,    35,     0,   224,
       0,     0,     0,    36,     0,  1897,   925,   925,   925,   925,
     925,   925,   925,   925,   925,   925,   925,     0,     3,     0,
     225,     4,     0,     5,     0,     0,     0,    37,     0,     0,
       0,   215,     0,     0,     0,     0,     0,   225,  1878,     0,
       0,     0,     0,     6,     7,     8,     9,   374,  1880,     0,
       0,     0,     0,   221,     0,   951,     0,   225,   222,     0,
       0,     0,     0,     0,    60,     0,   224,     0,     0,     0,
       0,     0,     3,  1146,   782,     4,     0,     5,  1879,     0,
       0,   226,     0,  1585,     0,  1602,  1612,  1628,  1640,  2171,
       0,     0,     0,   274,   275,   276,   277,     6,     7,     8,
       9,     0,   226,     0,     0,     0,   221,     0,     0,     0,
       0,   222,  1663,     0,     0,  1664,     0,   782,     0,   224,
     221,   226,     0,     0,     0,   222,   782,   395,     0,     0,
     225,     0,  1990,   224,     0,   405,   406,   407,   408,     0,
     473,  1691,     0,     0,     0,     0,  1118,  1119,     0,     0,
       0,     0,     0,     0,     0,    18,    19,     0,   441,     0,
    1120,     0,     0,     0,  2050,     0,     0,     0,  1121,   226,
     215,     0,     0,     0,     0,   466,     0,     0,     0,     0,
     475,   476,   477,     0,  1122,   481,   374,   225,   486,  1746,
       0,  1191,  1274,     0,     0,  1694,   925,     0,  1701,     0,
    1706,     0,     0,  1712,    34,   805,     0,   227,   925,     0,
     215,     0,     0,  2051,    35,     0,  1880,     0,  1520,     0,
      36,  1520,     0,     0,  1520,   226,   374,     0,     0,     0,
    1832,     0,  1729,     0,  1730,  1731,     0,  1733,   151,   152,
     153,     0,   226,  1146,    37,   905,     0,     0,     0,   906,
       0,     0,     0,     0,   907,  1833,  1834,     0,   215,   925,
     908,  1505,   226,     0,   812,     0,     3,     0,     0,     4,
       0,     5,     0,     0,   374,     0,     3,   925,   925,     4,
       0,     5,     0,     0,   911,   782,     0,     0,     0,     0,
       0,     6,     7,     8,     9,     0,   782,     0,     0,     0,
    2169,     6,     7,     8,     9,  1614,  1123,  1124,  1125,   686,
       0,  2144,     0,     0,   215,  1614,     0,   478,   225,     0,
       0,     0,   696,   697,   698,   736,   737,   738,     0,     0,
     227,   215,    18,    19,     0,   226,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   227,     0,   939,
       0,   215,   225,  1615,  1616,  1617,  1618,   782,  1619,     0,
       0,  1620,     0,  1615,  1616,  1617,  1618,   374,  1619,     0,
       0,  1620,  2136,  1149,  1835,   225,     0,     0,  1621,     0,
       0,    34,     0,     0,     0,   225,     0,     0,  1621,     0,
       0,    35,   226,  1247,  1836,  1837,     0,    36,     0,     0,
       0,     0,     0,     0,     0,  1602,  1612,  1628,  1640,     0,
       0,   782,  2052,     0,     0,   815,     0,     0,   816,   817,
       0,    37,     0,     0,   215,     0,  2145,  1622,  2053,     0,
       0,     0,     0,  2054,   482,  2055,     0,  1622,     0,     0,
     227,     0,  1884,  1894,  1901,     0,     0,     0,     0,    18,
      19,     0,   225,   819,   820,     0,   968,   969,   970,     0,
     939,   939,   939,   939,   939,     0,     0,   939,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,     0,     0,   484,     0,     0,     0,   985,
    1914,     0,   939,     0,   210,     0,     0,   227,    34,     0,
      18,    19,     0,     0,     3,   225,     0,     4,    35,     5,
       0,   939,     0,     0,    36,     0,     0,     0,   997,   225,
       0,     0,     0,   226,     0,     0,     0,     0,     0,     6,
       7,     8,     9,     0,     0,  1623,    88,     0,    37,     0,
       0,     0,     0,  1614,    89,  1623,    90,     0,    91,    34,
     305,    92,    93,    94,     0,    95,     0,   226,     0,    35,
     305,     0,     0,     0,     0,    36,   307,     0,     0,     0,
       0,   308,     0,     0,     0,     0,   307,     0,     0,     0,
     226,   308,     0,     0,     0,     0,     0,     0,     0,    37,
     226,  1615,  1616,  1617,  1618,     0,  1619,     0,     0,  1620,
       0,     0,     0,     0,     0,   782,     3,     0,     0,     4,
       0,     5,   215,     0,     0,   782,  1621,     0,     0,     0,
    1624,     0,     0,  1884,  1894,  1901,     0,     0,   374,     0,
    1865,     6,     7,     8,     9,   605,     0,     0,     0,  2001,
       0,     0,     0,     0,   606,  1631,   215,     0,     0,  2007,
     925,     0,     0,     0,     0,     0,  2010,   226,     0,   607,
       0,     0,   227,   608,     0,  1622,     0,   609,   610,   215,
       0,     0,   611,   612,   613,   614,   615,     0,     0,   215,
       0,     0,     0,     0,     0,   227,     0,     0,     0,     0,
       0,  2015,     0,     0,  1632,   227,  1633,   446,  1619,   448,
     450,  1620,     0,   453,     0,   455,     0,     0,   459,   460,
     226,     0,   468,   470,   472,   474,     0,     0,  1634,   479,
       0,     0,   483,   485,   226,     0,     0,     0,     0,     0,
     492,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   215,     0,  2073,  2074,
    2075,     0,     0,     0,     3,     0,     0,     4,     0,     5,
       0,     0,   227,     0,     0,     0,     0,  1635,     0,    96,
       0,     0,     0,  1623,  2091,     0,     0,     0,     0,     6,
       7,     8,     9,     0,    97,     0,     0,     0,   305,     0,
       0,     0,     0,  1631,     0,     0,     0,     0,     0,   215,
      98,     0,     0,     0,   307,    99,     0,   100,  1460,   308,
       0,     0,     0,   215,     0,   374,     0,     0,  1247,  1247,
    1247,  1247,  1247,     0,  1247,  1247,     0,     0,     0,   227,
       0,     0,     0,  1548,  1548,     0,     0,     0,     0,     0,
       0,     0,  1632,   782,  1633,     0,  1619,     0,     0,  1620,
       0,     0,     0,  1585,  1612,  1628,  1640,     0,  2138,     0,
       0,  1694,  1701,  1706,  1712,     0,  1634,     0,     0,     0,
       0,     0,  1056,     0,     0,  1623,   939,   939,   939,   939,
     939,   939,   939,   939,   939,   939,   939,     0,     0,    50,
     305,     0,     0,     0,     0,     0,  1884,  1894,  1901,    61,
      50,    50,    64,    64,    64,    68,   307,     0,    50,     0,
       0,   308,     0,     0,     0,  1635,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2186,  2187,  2188,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1461,     0,   782,  1058,  1059,  1462,  1061,
    1062,  1063,  1064,  1065,  1066,  1067,  1068,  1069,  1463,    50,
    1636,     0,   396,    50,    64,    64,    64,    68,     0,     0,
       0,     0,     0,     0,    50,     0,   411,   416,   419,    50,
     424,    64,    64,   429,     0,   411,   411,   411,   411,     0,
      64,     0,     3,     0,   445,     4,    50,     5,     0,    64,
      64,     0,    68,     0,     0,    64,     0,     0,     0,     3,
       0,     0,     4,     0,     5,     0,     0,     6,     7,     8,
       9,     0,     0,  1623,   488,    50,    64,    64,     0,     0,
      64,  1631,    50,     0,     6,     7,     8,     9,   305,     0,
       0,     0,     0,     0,     0,  1587,     0,   996,     0,     0,
       0,     0,   536,   537,   307,  1588,   538,     0,     0,   308,
    1589,     0,  1590,     0,  1591,     0,   939,   539,   540,   541,
     542,   543,   544,   545,   546,   547,     0,     0,   939,     0,
    1632,     0,  1633,     0,  1619,     0,     0,  1620,     0,     0,
       0,     0,     0,   782,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1634,     0,     0,     0,  1866,     0,
       0,     0,     0,     0,     0,     0,   548,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   939,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,   939,   939,     4,
       0,     5,     0,  1635,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   146,     0,
    1592,     6,     7,     8,     9,   147,   148,     0,     0,     0,
     288,   149,   289,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   290,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   291,   292,     0,
       0,     0,   293,     0,     0,   294,     0,     0,     0,     0,
       0,     0,     0,   295,   296,   297,   298,   299,   300,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1603,     0,
       0,     0,   301,     0,   302,     0,     0,   150,   151,   152,
     153,     0,     0,   154,     0,   155,     0,     0,  1604,   156,
       0,  1623,     0,     0,   157,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,     0,   305,     0,  1593,     0,
       0,     0,     0,     0,     0,     0,   159,     0,     0,     0,
       0,   160,   307,  1594,   161,     0,     0,   308,     0,   162,
       0,     0,   163,     0,     0,   164,   165,  1605,     0,  1595,
     166,     0,     0,   167,  1596,   168,  1597,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   782,     0,     0,     0,     0,     0,   994,     0,     0,
     169,   170,     0,     0,    64,     0,  2139,     0,   782,     0,
       0,     0,     0,     0,     0,  1000,     0,  1001,     0,  1002,
       0,  1003,     0,  1863,     0,     0,  1007,     0,     0,     0,
    1009,     0,  1010,     0,     0,     0,   171,   172,   173,   174,
       0,    64,     0,     0,     0,   175,   176,     0,     0,   177,
     178,   303,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,     0,     0,   304,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     305,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     306,     0,     0,     0,     0,     0,   307,     0,     0,     0,
       0,   308,     0,     0,     0,     0,  1054,   202,   203,     0,
     309,     0,     0,   310,   311,   312,   313,     0,     0,     0,
     314,  1055,   761,     0,   315,   316,   204,     0,     0,     0,
     205,   206,     0,     3,     0,   782,     4,     0,     5,   317,
       0,     0,   207,   208,   678,   679,     0,     0,   680,   318,
    1606,   209,     0,     0,   210,   146,     0,     0,     6,     7,
       8,     9,   147,   148,     0,     0,   681,   288,   149,   289,
     939,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   290,  1056,     0,     0,     0,     0,
       0,     0,     0,     0,   291,   292,     0,     0,     0,   293,
       0,     0,   294,     0,     0,     0,     0,     0,     0,     0,
     295,   296,   297,   298,   299,   300,     0,     0,     0,     0,
       0,     0,   762,     0,     0,  1603,     0,     0,     0,   301,
       0,   302,     0,     0,   150,   151,   152,   153,     0,     0,
     154,     0,   155,     0,     0,  1604,   156,     0,     0,     0,
       0,   157,     0,     0,     0,     0,  1057,   158,     0,  1058,
    1059,  1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,  1068,
    1069,  1070,     0,   159,     0,     0,     0,     0,   160,     0,
     682,   161,     0,     0,     0,     0,   162,     0,     0,   163,
       0,     0,   164,   165,  1605,     0,     0,   166,     0,     0,
     167,     0,   168,     0,   683,   684,   685,   686,   687,   688,
     763,   689,   690,   691,   692,   693,   694,   695,     0,     0,
     696,   697,   698,     0,     0,     0,     0,   169,   170,     0,
       0,     0,     0,     0,     0,     0,    10,     0,     0,     0,
       0,   699,     0,     0,    11,     0,    12,     0,    13,     0,
       0,    14,    15,    16,     0,    17,     0,     0,     0,    18,
      19,     0,     0,   171,   172,   173,   174,     0,     0,     0,
       0,     0,   175,   176,     0,     0,   177,   178,   303,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
       0,     0,   304,     0,     0,     0,     0,     0,    34,     0,
       0,   104,     0,     0,     0,     0,   105,   305,    35,   106,
     107,   108,   109,     0,    36,   110,   111,   306,   112,   113,
     114,     0,   115,   307,     0,     0,     0,     0,   308,     0,
       0,     0,     0,     0,   202,   203,     0,   309,    37,     0,
     310,   311,   312,   313,     0,     0,     0,   314,     0,     0,
       0,   315,   316,   204,     0,     0,     0,   205,   206,     0,
       0,   116,   782,   117,   118,   119,   317,     0,     3,   207,
     208,     4,     0,     5,     0,     0,   318,  1864,   209,     0,
       0,   210,     0,     0,     0,     0,     0,     0,     0,     0,
     146,     0,     0,     6,     7,     8,     9,   147,   148,     0,
       0,     0,   288,   149,   289,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   290,
       0,     0,     0,     0,     0,     0,  1357,     0,     0,   291,
     292,   668,     0,     0,   293,     0,     0,   294,     0,     0,
       0,     0,     0,     0,     0,   295,   296,   297,   298,   299,
     300,     0,     0,     0,     0,     0,     0,     0,   669,    38,
    1603,   670,     0,     0,   301,     0,   302,     0,     0,   150,
     151,   152,   153,     0,    39,   154,     0,   155,   671,     0,
    1604,   156,     0,     0,     0,     0,   157,     0,     0,     0,
      40,     0,   158,     0,     0,    41,     0,    42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,     0,
       0,     0,     0,   160,     0,     0,   161,     0,     0,     0,
       0,   162,     0,     0,   163,     0,     0,   164,   165,  1605,
       0,     0,   166,     0,   120,   167,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   121,
       0,     0,     0,     0,   122,   123,   124,   125,     0,     0,
       0,     0,   169,   170,     0,   126,     0,     0,     0,     0,
     127,     0,   128,   129,     0,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     0,     0,   171,   172,
     173,   174,     0,     0,     0,     0,     0,   175,   176,     0,
       0,   177,   178,   303,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,     0,   672,   304,     0,     0,
     202,   203,     0,     0,     0,     0,     0,     0,     0,     0,
     673,     0,   305,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   306,     0,     0,     0,     0,     0,   307,     0,
       0,     0,     0,   308,     0,     0,   674,     0,     0,   202,
     203,     0,   309,     0,     0,   310,   311,   312,   313,     0,
       0,     0,   314,     0,     0,     0,   315,   316,   204,     0,
       0,     0,   205,   206,     0,     0,     4,   782,     5,     0,
       0,   317,     0,     0,   207,   208,     0,     0,     0,     0,
       0,   318,  2137,   209,     0,   146,   210,     0,     0,     0,
       0,     0,   147,   148,     0,     0,     0,   288,   149,   289,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   290,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   291,   292,   759,     0,     0,   293,
       0,     0,   294,     0,     0,     0,     0,     0,     0,     0,
     295,   296,   297,   298,   299,   300,     0,     0,     0,     0,
       0,     0,     0,   669,     0,     0,   670,     0,     0,   301,
       0,   302,     0,     0,   150,   151,   152,   153,     0,     0,
     154,     0,   155,   671,     0,     0,   156,     0,     0,     0,
       0,   157,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,     0,     0,     0,     0,   160,     0,
       0,   161,     0,     0,     0,  1076,   162,     0,     0,   163,
       0,     0,   164,   165,     0,     0,     0,   166,     0,     0,
     167,     0,   168,  1077,  1078,  1079,  1080,  1081,  1082,  1083,
    1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,  1093,
       0,     0,     0,     0,     0,     0,     0,   169,   170,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,     0,     0,   171,   172,   173,   174,     0,     0,     0,
       0,     0,   175,   176,     0,     0,   177,   178,   303,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
       0,   672,   304,     0,   804,   202,   203,     0,     0,     0,
     678,   679,     0,     0,   680,   673,     0,   305,     0,     0,
       0,     0,   146,     0,     0,     0,     0,   306,     0,     0,
     148,     0,   681,   307,     0,   149,     0,     0,   308,     0,
       0,   674,     0,     0,   202,   203,     0,   309,     0,     0,
     310,   311,   312,   313,     0,     0,     0,   314,     0,     0,
       0,   315,   316,   204,     0,     0,     0,   205,   206,   805,
       0,     0,     0,     0,     0,     0,   317,     0,     0,   207,
     208,     0,     0,   806,     0,   807,   318,  1764,   209,     0,
       0,   210,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   150,   151,   152,   153,     0,     0,   154,     0,   808,
       0,     0,     0,   809,     0,     0,     0,     0,   810,     0,
       0,     0,     0,     0,   811,     0,     0,     0,   812,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     159,     0,     0,     0,     0,   160,   682,     0,   813,     0,
       0,     0,     0,   162,     0,     0,   163,     0,     0,   164,
     165,     0,     0,     0,   166,     0,     0,   167,     0,   168,
     683,   684,   685,   686,   687,   688,     0,   689,   690,   691,
     692,   693,   694,   695,     0,     0,   696,   697,   698,     0,
       0,     0,     0,     0,   169,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1158,     0,   699,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   146,     0,     0,     0,     0,     0,     0,
     814,   148,     0,     0,     0,     0,   149,     0,     0,     0,
       0,     0,     0,     0,     0,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,     0,     0,   201,
     805,     0,     0,     0,     0,     0,     0,     0,     0,   815,
       0,     0,   816,   817,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   818,     0,     0,     0,     0,
       0,     0,   150,   151,   152,   153,     0,     0,   154,     0,
     808,   202,   203,     0,   809,     0,     0,   819,   820,   810,
       0,     0,     0,     0,     0,  1159,     0,     0,     0,   812,
     204,     0,     0,     0,   205,   206,     0,     0,     0,     0,
       0,   159,     0,     0,   821,   822,   160,   674,     0,  1160,
       0,     0,     0,     0,   162,   823,     0,   163,   210,     0,
     164,   165,     0,     0,     0,   166,     0,     0,   167,     0,
     168,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   169,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1234,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   146,     0,     0,     0,     0,     0,
       0,   814,   148,     0,     0,     0,     0,   149,     0,     0,
       0,     0,     0,     0,     0,     0,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,     0,
     201,   805,     0,     0,     0,     0,     0,     0,     0,     0,
     815,     0,     0,   816,   817,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   151,   152,   153,     0,     0,   154,
       0,   808,   202,   203,     0,   809,     0,     0,   819,   820,
     810,     0,     0,     0,     0,     0,  1159,     0,     0,     0,
     812,   204,     0,     0,     0,   205,   206,     0,     0,     0,
       0,     0,   159,     0,     0,   821,   822,   160,   674,     0,
    1160,     0,     0,     0,     0,   162,   823,     0,   163,   210,
       0,   164,   165,     0,     0,     0,   166,     0,     0,   167,
       0,   168,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   169,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1270,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   146,     0,     0,     0,     0,
       0,     0,   814,   148,     0,     0,     0,     0,   149,     0,
       0,     0,     0,     0,     0,     0,     0,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,     0,
       0,   201,   805,     0,     0,     0,     0,     0,     0,     0,
       0,   815,     0,     0,   816,   817,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150,   151,   152,   153,     0,     0,
     154,     0,   808,   202,   203,     0,   809,     0,     0,   819,
     820,   810,     0,     0,     0,     0,     0,  1159,     0,     0,
       0,   812,   204,     0,     0,     0,   205,   206,     0,     0,
       0,     0,     0,   159,     0,     0,   821,   822,   160,   674,
       0,  1160,     0,     0,     0,     0,   162,   823,     0,   163,
     210,     0,   164,   165,     0,     0,     0,   166,     0,     0,
     167,     0,   168,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   169,   170,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1452,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   146,     0,     0,     0,
       0,     0,     0,   814,   148,     0,     0,     0,     0,   149,
       0,     0,     0,     0,     0,     0,     0,     0,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
       0,     0,   201,   805,     0,     0,     0,     0,     0,     0,
       0,     0,   815,     0,     0,   816,   817,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,   151,   152,   153,     0,
       0,   154,     0,   808,   202,   203,     0,   809,     0,     0,
     819,   820,   810,     0,     0,     0,     0,     0,  1159,     0,
       0,     0,   812,   204,     0,     0,     0,   205,   206,     0,
       0,     0,     0,     0,   159,     0,     0,   821,   822,   160,
     674,     0,  1160,     0,     0,     0,     0,   162,   823,     0,
     163,   210,     0,   164,   165,     0,     0,     0,   166,     0,
       0,   167,     0,   168,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   169,   170,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   898,   899,   900,   901,   902,   903,     0,
       0,     0,     0,   904,     0,     0,     0,   883,     0,     0,
       0,     0,     0,     0,   814,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,     0,     0,   201,   805,     0,     0,     0,     0,     0,
       0,     0,     0,   815,     0,     0,   816,   817,     0,     0,
       0,     0,     0,     0,  1200,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   150,   151,   152,   153,
       0,     0,     0,     0,   905,   202,   203,     0,   906,     0,
       0,   819,   820,   907,     0,     0,     0,     0,     0,   908,
       0,     0,     0,   812,   204,     0,     0,     0,   205,   206,
       0,     0,  1200,   805,     0,   909,     0,     0,   821,   822,
     910,   674,     0,   911,     0,     0,     0,     0,   912,   823,
       0,   913,   210,     0,   914,   915,     0,     0,     0,   916,
       0,     0,   917,     0,   918,   150,   151,   152,   153,     0,
       0,     0,     0,   905,     0,     0,     0,   906,     0,     0,
       0,   805,   907,     0,     0,     0,     0,     0,   908,   919,
     920,     0,   812,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   909,     0,     0,     0,     0,   910,
       0,     0,   911,   150,   151,   152,   153,   912,     0,     0,
     913,   905,     0,   914,   915,   906,     0,     0,   916,     0,
     907,   917,     0,   918,     0,     0,   908,     0,     0,     0,
     812,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   909,     0,     0,     0,     0,   910,   919,   920,
     911,     0,     0,     0,     0,   912,     0,     0,   913,     0,
       0,   914,   915,     0,   815,     0,   916,   816,   817,   917,
       0,   918,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   919,   920,     0,     0,
       0,     0,   819,   820,     0,   921,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   821,
     822,     0,     0,   815,     0,     0,   816,   817,   318,     0,
     922,     0,     0,   210,     0,   944,   883,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   819,   820,     0,   921,     0,     0,     0,     0,     0,
       0,   815,     0,     0,   816,   817,     0,     0,     0,     0,
       0,     0,     0,   805,     0,     0,     0,     0,   821,   822,
       0,     0,     0,     0,     0,     0,     0,   318,     0,   922,
       0,     0,   210,     0,     0,     0,     0,     0,     0,   819,
     820,     0,   921,     0,     0,   150,   151,   152,   153,     0,
       0,     0,     0,   905,     0,     0,     0,   906,     0,     0,
       0,     0,   907,     0,     0,     0,   821,   822,   908,     0,
       0,     0,   812,     0,     0,     0,     0,   922,     0,     0,
     210,     0,     0,     0,   909,     0,     0,     0,     0,   910,
       0,     0,   911,     0,     0,     0,     0,   912,     0,     0,
     913,     0,   146,   914,   915,     0,     0,     0,   916,   147,
     148,   917,     0,   918,   288,   149,   289,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   290,     0,     0,     0,     0,     0,     0,   919,   920,
       0,   291,   292,     0,     0,     0,   293,     0,     0,   294,
       0,     0,     0,     0,     0,     0,     0,   295,   296,   297,
     298,   299,   300,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   301,     0,   302,     0,
       0,   150,   151,   152,   153,     0,     0,   154,     0,   155,
       0,     0,     0,   156,     0,     0,     0,     0,   157,     0,
       0,     0,     0,     0,   158,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     159,     0,     0,   815,     0,   160,   816,   817,   161,     0,
       0,     0,     0,   162,     0,     0,   163,     0,     0,   164,
     165,     0,     0,     0,   166,     0,     0,   167,     0,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   819,   820,     0,   921,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   169,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   821,   822,
       0,     0,     0,     0,     0,     0,     0,   945,     0,   922,
       0,     0,   210,     0,     0,     0,     0,     0,     0,     0,
     171,   172,   173,   174,     0,     0,     0,     0,     0,   175,
     176,     0,     0,   177,   178,   303,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,     0,     0,   304,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,     0,     0,     0,   305,     0,     0,   147,   148,     0,
       0,     0,     0,   149,   306,     0,     0,     0,     0,     0,
     307,     0,     0,     0,     0,   308,     0,     0,     0,     0,
       0,   202,   203,     0,   309,     0,     0,   310,   311,   312,
     313,     0,     0,     0,   314,     0,     0,     0,   315,   316,
     204,     0,     0,     0,   205,   206,     0,     0,     0,     0,
       0,     0,     0,   317,     0,     0,   207,   208,     0,     0,
       0,     0,     0,   318,     0,   209,     0,     0,   210,   150,
     151,   152,   153,     0,     0,   154,     0,   155,     0,     0,
       0,   156,     0,     0,     0,     0,   157,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,     0,
       0,     0,     0,   160,     0,     0,   161,     0,     0,     0,
       0,   162,     0,     0,   163,     0,     0,   164,   165,     0,
       0,     0,   166,     0,     0,   167,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   169,   170,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   146,     0,     0,     0,     0,     0,     0,   147,
     148,     0,     0,     0,     0,   149,     0,     0,   171,   172,
     173,   174,     0,     0,     0,     0,     0,   175,   176,     0,
       0,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,     0,     0,   201,     0,     0,
       0,     0,     0,     0,     0,  2046,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   150,   151,   152,   153,     0,     0,   154,     0,   155,
       0,     0,     0,   156,     0,     0,     0,     0,   157,   202,
     203,     0,     0,     0,   158,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   204,     0,
     159,     0,   205,   206,     0,   160,     0,     0,   161,     0,
       0,     0,     0,   162,   207,   208,   163,     0,     0,   164,
     165,   318,     0,   209,   166,     0,   210,   167,     0,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   146,     0,     0,   169,   170,     0,     0,   147,   148,
       0,     0,     0,     0,   149,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     171,   172,   173,   174,     0,     0,     0,     0,     0,   175,
     176,     0,     0,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,     0,     0,   201,
     150,   151,   152,   153,     0,     0,   154,     0,   155,     0,
       0,     0,   156,     0,     0,     0,     0,   157,     0,     0,
       0,     0,     0,   158,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   159,
       0,   202,   203,     0,   160,     0,     0,   161,     0,     0,
       0,     0,   162,     0,     0,   163,     0,     0,   164,   165,
     204,     0,     0,   166,   205,   206,   167,     0,   168,     0,
       0,     0,     0,     0,     0,     0,   207,   208,     0,     0,
       0,     0,     0,     0,     0,   209,     0,     0,   210,     0,
     146,     0,     0,   169,   170,     0,     0,     0,   148,     0,
       0,     0,     0,   149,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   171,
     172,   173,   174,     0,     0,     0,     0,   805,   175,   176,
       0,     0,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     0,     0,   201,   150,
     151,   152,   153,     0,     0,   154,     0,   808,     0,     0,
       0,   809,     0,     0,     0,     0,   810,     0,     0,     0,
       0,     0,  1159,     0,     0,     0,   812,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,     0,
     202,   203,     0,   160,     0,     0,  1160,     0,     0,     0,
       0,   162,     0,     0,   163,     0,     0,   164,   165,   204,
       0,     0,   166,   205,   206,   167,     0,   168,     0,     0,
       0,     0,     0,     0,     0,   207,   208,     0,     0,     0,
       0,     0,     0,     0,   209,     0,     0,   210,     0,     0,
       0,     0,   169,   170,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   883,     0,     0,     0,     0,     0,     0,   814,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,     0,     0,   201,   805,     0,
       0,     0,     0,     0,     0,     0,     0,   815,     0,     0,
     816,   817,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     150,   151,   152,   153,     0,     0,     0,     0,   905,   202,
     203,     0,   906,     0,     0,   819,   820,   907,     0,     0,
       0,     0,     0,   908,     0,     0,     0,   812,   204,     0,
       0,     0,   205,   206,     0,     0,     0,     0,     0,   909,
       0,     0,   821,   822,   910,   674,     0,   911,     0,     0,
       0,     0,   912,   823,     0,   913,   210,     0,   914,   915,
       0,     2,     3,   916,     0,     4,   917,     5,   918,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     7,     8,
       9,     0,     0,   919,   920,     0,     0,     0,    10,     0,
       0,     0,     0,     0,     0,     0,    11,     0,    12,     0,
      13,     0,     0,    14,    15,    16,     0,    17,     0,     0,
       0,    18,    19,    20,     0,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -394,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,   815,     0,
      35,   816,   817,     0,     0,     0,    36,     0,     0,     0,
     805,     0,     0,     0,     0,     0,     0,     0,   295,   296,
     297,  1751,  1752,   300,     0,     0,     0,     0,     0,     0,
      37,     0,     0,     0,     0,     0,   819,   820,     0,   921,
       0,     0,   150,   151,   152,   153,     0,     0,     0,     0,
     905,     0,     0,     0,   906,     0,     0,     0,   805,   907,
       0,     0,     0,   821,   822,   908,     0,     0,     0,   812,
       0,     0,   318,     0,   922,     0,     0,   210,     0,     0,
       0,   909,     0,     0,     0,     0,   910,     0,     0,   911,
     150,   151,   152,   153,   912,     0,     0,   913,   905,     0,
     914,   915,   906,     0,     0,   916,     0,   907,   917,     0,
     918,     0,     0,   908,     0,     0,     0,   812,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   909,
       0,     0,     0,     0,   910,   919,   920,   911,     0,     0,
       0,     0,   912,     0,     0,   913,     0,     0,   914,   915,
       0,    38,     0,   916,     0,     0,   917,     0,   918,     0,
       0,     0,   805,     0,     0,     0,    39,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    40,   919,   920,     0,     0,    41,     0,    42,
       0,     0,     0,     0,  1572,   151,   152,   153,     0,     0,
       0,     0,   905,     0,     0,     0,   906,     0,     0,     0,
       0,   907,     0,     0,     0,     0,     0,   908,     0,     0,
     815,   812,     0,   816,   817,     0,     0,     0,     0,     0,
       0,     0,     0,   909,     0,     0,     0,     0,   910,     0,
       0,   911,     0,     0,     0,     0,   912,     0,     0,   913,
       0,     0,   914,   915,     0,     0,     0,   916,   819,   820,
     917,   921,   918,     0,     0,     0,     0,     0,   815,     0,
       0,   816,   817,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   821,   822,   919,   920,     0,
       0,     0,     0,     0,     0,     0,   922,     0,     0,   210,
       0,     0,     0,     0,     0,     0,   819,   820,     0,   921,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   821,   822,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   922,     0,     0,   210,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   815,     0,     0,   816,   817,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     819,   820,     0,   921,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   821,   822,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   922,     0,
       0,   210
};

static const yytype_int16 yycheck[] =
{
       1,   205,     3,   321,   329,    30,   410,    66,   324,   400,
     399,   401,   476,    30,    52,   299,    37,   743,     1,   398,
     477,    30,   486,   581,   805,    63,   916,   636,   779,   918,
      52,   366,    36,   288,    66,    52,   773,   441,   427,    32,
     430,    63,   475,    52,   675,    46,    63,   366,   521,   345,
    1333,   440,   352,    54,    63,   876,   782,    58,   377,   378,
    1333,   316,  1340,  1278,   209,  1201,  1202,   793,  1337,  1149,
    1338,   797,  1208,  1339,   381,  1353,  1442,  1332,  1333,  1189,
     405,   397,  1277,   338,   342,   366,   344,   920,  1442,  1496,
      35,  1446,  1280,  1427,  1428,   639,  1657,   641,   892,   643,
    1655,   823,  1656,   893,   648,   890,   891,   894,   105,  1634,
     107,   436,   109,   110,   896,    30,   113,  1559,   115,  1631,
    1830,   118,   119,     7,     7,   122,   123,   124,   125,   760,
       4,     4,   129,    38,  1696,   132,   133,    52,    45,     7,
       7,   466,   366,   140,    23,     7,     1,  1458,    63,     4,
    1456,     6,  1288,   377,   378,    57,   481,   179,    96,     7,
    1697,   102,   747,   102,   749,   709,   103,    15,    16,    17,
      18,    26,    27,    28,    29,   740,    23,    78,    79,  1888,
    1680,   766,   767,   104,   769,    84,    41,  1167,   205,    44,
     775,   776,   209,    20,   103,   742,   205,  1503,  1504,    23,
     209,    89,     8,     5,    92,    49,   126,   103,   104,    15,
      16,    17,    18,   743,   741,   672,    22,   143,    84,   804,
     134,   806,    84,     7,     8,     9,   102,   322,   103,     1,
     103,   104,     4,   159,     6,    13,     4,   332,     6,   298,
     299,   700,   699,   162,    32,    33,    34,    89,    54,   975,
      92,     8,   166,   167,    26,    27,    28,    29,    15,    16,
      17,    18,    62,   256,    48,    22,    50,    22,    49,   262,
     113,  1466,  1467,    84,  1557,    59,   103,   354,   113,     8,
      64,   303,   359,   197,    68,   870,    15,    16,    17,    18,
     205,    53,   287,   352,   209,   130,   162,    54,    98,   321,
     135,   136,  1557,    47,   321,   764,     5,   162,    86,   287,
    1616,  1617,   321,   103,   125,    58,   230,    30,   237,   238,
     239,   103,    30,   166,   167,    54,  1632,   103,   104,   105,
      30,   103,   104,   105,   366,    58,   354,     8,   149,    52,
     399,  1230,    15,    16,    52,   377,   378,   102,   103,   366,
      63,   909,    52,    24,   912,    63,   394,   942,   943,   354,
     377,   378,   302,    63,   353,   304,   286,   399,   427,   110,
    1653,   409,   394,     4,  1629,     6,   354,   394,   110,  2088,
    1653,   440,  1164,    54,   125,   394,  1641,   409,   103,   104,
     105,    89,   409,   125,    84,   427,  1376,  1652,  1653,   353,
     409,   236,     8,    76,    77,    78,   321,   972,   440,    15,
      16,    17,    18,   288,   354,  1726,   354,    45,   359,    92,
      93,    94,   359,   322,   323,   324,   210,   974,   304,   102,
     285,  1229,   354,  1231,   522,    89,   338,   339,   111,   112,
     132,     7,  1168,  1169,   117,   975,   973,   354,    54,   354,
       1,   236,   340,     4,    20,     6,  2018,  1982,   359,   247,
     457,   288,   550,   359,   326,   138,   139,  1979,   270,   142,
     558,   355,   355,  2183,  1256,    26,    27,    28,    29,   394,
     359,   355,  2019,   285,   143,   573,   359,   355,   355,   148,
      41,   236,   205,    44,   409,  1995,   209,   205,   340,   301,
     355,   209,   270,    89,   306,   205,   288,   354,  1950,   209,
     358,   286,   359,   125,   298,   299,  1310,   285,   302,    45,
      46,  1311,    89,  1308,  1309,  1312,  2051,   302,  1783,   617,
     354,   127,  1254,   301,  2046,   359,  1724,   149,   306,   627,
     836,  1875,  1949,   342,  2105,   549,   750,   159,  2103,   953,
    2104,   572,   358,   355,   333,   779,   152,  1101,  1031,    57,
    1033,   819,   820,    84,   334,    86,  1781,   337,   340,   773,
    1936,   270,  1927,  1158,   662,   102,  1465,  1162,   354,   277,
    1886,   279,  1936,   355,  1417,   102,   285,  1172,  1173,  1174,
     535,     4,  1177,     6,  1179,     8,   896,   352,   341,   342,
     343,   358,   301,   922,   359,   103,   941,   306,   321,    57,
     631,   162,   145,   321,  1199,    57,   897,  1753,   341,   342,
     343,   321,   941,   277,   628,   279,  1515,   411,   125,   358,
      57,   415,   322,   323,   324,   419,    89,  1747,  1748,    84,
     424,    84,   113,    86,   359,   429,   141,   102,   145,  1234,
    1786,  1236,   149,    57,   961,   103,   355,  1242,   170,   154,
     941,   103,     4,   921,     6,   286,   890,   891,   892,   893,
     894,  1492,  1257,   897,  1259,   170,   103,  1872,     8,  1759,
     125,   394,     7,  1268,   286,  1270,   394,    84,    84,    86,
    1154,   277,     4,   279,   394,    20,   409,    39,   922,   103,
    1157,   409,     1,     5,   149,     4,     8,     6,   294,   409,
     277,   495,   279,     8,   773,   236,    30,   941,  1151,   113,
    1518,  1185,  1448,  1521,    54,   316,  1524,    26,    27,    28,
      29,  1946,   340,   750,   285,   268,   269,   349,    52,   354,
     134,   750,   735,  1216,   359,  1496,   113,   779,  1181,    63,
     895,   127,   358,   147,  1491,  2033,   773,  1508,   125,    54,
     127,  2030,   779,  2031,   773,    45,  2032,   737,   738,   304,
     305,   268,   269,    18,     1,   296,   152,     4,   145,     6,
     251,   252,   149,   456,     1,   152,   152,     4,    77,     6,
     351,   352,   813,   236,    38,    39,   162,   163,    17,    26,
      27,    28,    29,   102,   355,   358,   823,   811,  1559,    26,
      27,    28,    29,     5,    52,   348,     8,   876,  2101,   354,
     493,   110,   317,  1148,   277,  1434,   279,    22,  2101,     1,
      25,    45,     4,    47,     6,   750,   125,   896,    52,   236,
      54,  1472,  1473,   113,    58,  2100,  2101,  1806,  1807,  1808,
    1809,   348,   286,   296,    26,    27,    28,    29,   773,     4,
     130,     6,    89,     8,  1164,   897,  1451,  1452,   235,    96,
     304,   305,    89,   890,   891,   892,   893,   894,   895,    96,
     897,   170,  1346,    97,  1139,    99,   895,   111,   112,  2025,
    1347,   205,   162,  1478,     0,   209,   287,   288,     4,   296,
       6,   268,   269,   297,     7,   922,   133,   103,  1493,   941,
       1,    57,  1345,     4,    52,     6,   133,    20,    79,    22,
       4,    30,     6,     7,   941,  1594,  1595,  1596,  1597,  1017,
     102,  1335,   128,   129,    95,    26,    27,    28,    29,   115,
     167,   185,  1527,    52,   188,   946,   127,   130,   354,   950,
     167,   134,   285,   114,    63,   131,  1256,   290,   291,  1544,
     287,  1546,   143,   102,   103,   254,   354,  1171,   111,   112,
     113,   152,  1307,   306,   113,  1271,   152,   158,   159,  1314,
     895,   348,   158,   166,   167,   134,   354,  1306,  1307,  2125,
     113,  1772,   166,   167,  1313,  1314,  1315,  1316,   968,   969,
     970,  1960,  1961,  1962,   127,   304,   305,   321,    15,    16,
      30,   134,   103,   104,   105,   985,   270,   166,   167,  1344,
     169,   162,   354,   247,   248,     7,    30,   251,  1032,   152,
    1034,   285,    52,   354,   165,   158,  1040,   750,    20,   170,
      22,   340,   750,    63,   271,   304,   305,   301,    52,     7,
     750,   247,   102,   103,   271,    43,   355,   102,   103,    63,
     773,   354,    20,   113,    22,   773,   242,   243,   113,   327,
     328,   267,   268,   773,  1278,    45,  1280,  1686,    45,    20,
     394,    22,  1306,  1307,  1308,  1309,  1310,  1311,  1312,  1313,
    1314,  1315,  1316,    15,    16,   409,   205,  1248,  1249,   883,
     209,   231,    45,   887,  1255,  1164,    20,  1997,    22,  1998,
     240,   241,     7,   340,   244,   245,     1,    62,    63,     4,
     220,     6,    67,   340,   224,   225,   226,     8,   355,    15,
      16,  1716,   304,   305,  1803,  1804,  1805,   300,   355,   304,
     305,    26,    27,    28,    29,     1,   192,   193,     4,   103,
       6,   360,  1470,   360,  1171,   296,   297,   298,   299,   300,
     190,   191,  1171,   111,   112,  1750,     4,     5,   340,   333,
      26,    27,    28,    29,  1499,    85,    86,    87,  1582,    89,
     333,    37,   895,   355,   102,   205,   113,   895,   115,   209,
    1775,    47,   326,   327,   328,   895,    52,  1256,    54,  1950,
      56,   205,   111,   112,    89,   209,    45,   134,   341,   342,
     343,    96,   321,   111,   112,   142,   143,   357,   145,   102,
     103,    60,    61,   350,  1256,   103,   104,   105,   155,   156,
      84,  1248,  1249,  1250,  1251,  1252,   175,  1254,  1255,  1703,
    1558,    23,  1577,  1578,    94,    95,  1263,  1264,   133,   340,
      43,    44,  1709,    60,    61,  1551,  1171,  1553,  1577,  1578,
      12,  1278,    23,  1280,   355,  1698,   322,   323,   324,  1278,
     109,  1280,  1496,    78,    79,    80,    81,    82,    83,  1743,
     119,  1369,   167,    52,  1508,   394,   125,  1491,    52,  1306,
    1307,  1308,  1309,  1310,  1311,  1312,  1313,  1314,  1315,  1316,
     409,   321,   109,  1263,  1264,  1738,   162,  1740,   102,  1331,
     149,    52,   119,    52,  1331,    52,    84,   321,   125,    71,
    1645,   354,  1331,    75,   102,  1413,  1327,  1328,   102,  1330,
    1331,  1332,  1333,    84,    84,  1559,   102,   102,    90,    91,
     102,    17,   149,    18,   358,  1328,   366,  1330,  1331,  1332,
    1333,     5,     7,  1577,  1578,   320,   108,   377,   378,  1944,
       7,     7,     7,  1278,   102,  1280,  1691,   111,   112,   102,
       1,  1375,     5,     4,   394,     6,   120,   121,   122,   123,
     124,  1939,  1940,  2109,     7,   137,   271,     7,   354,   409,
     394,    17,   144,    18,   358,    26,    27,    28,    29,     8,
     102,     7,  1423,  1424,   102,   409,    38,   354,  1799,   302,
      41,  1801,   354,    44,   270,   287,  1331,  1421,  1422,  1798,
     354,   113,  2148,   115,   116,   117,   118,    96,   354,   285,
    1489,   354,  1491,  1492,   102,   102,   750,   102,  1827,  1440,
     102,   102,  1443,   354,  1445,   301,   103,  1448,  1470,   102,
     306,   102,   308,  1470,   189,   340,   130,  1440,  1171,   773,
    1443,  1470,  1445,  1171,  1853,  1448,   194,   224,  1752,   227,
     355,  1171,  1510,   227,  1491,   228,  1508,   334,     1,  1496,
    1796,     4,  1491,     6,   340,   102,   229,     1,  1510,   102,
       4,  1508,     6,  1510,   219,   220,   221,   222,   223,   355,
     102,  1510,   228,    26,    27,    28,    29,   102,  1512,  1510,
     354,   354,    26,    27,    28,    29,  1604,   102,   354,   102,
    1724,    46,   113,    48,   115,    50,    51,    41,   102,     5,
      44,   162,   102,    58,    59,   103,  1558,     8,   106,   107,
     108,  1558,  1559,   134,  1603,   137,   138,   139,   140,  1558,
     102,   142,   143,   144,   145,  1470,    52,   102,    22,     1,
    1577,  1578,     4,    43,     6,  1278,    91,  1280,   148,     5,
    1278,   357,  1280,   102,    84,     8,  1491,  1781,  1278,    84,
    1280,   895,    22,    22,    26,    27,    28,    29,     7,  1614,
    2054,   102,   288,   102,  1912,  1510,     5,  1614,  2055,   354,
    1601,   215,   216,   217,   218,  1614,  1631,   354,  1609,  1610,
    1611,  1612,  1613,   361,  1631,   357,   361,   103,  1331,   303,
    2053,   303,  1631,  1331,   354,   354,  1627,  1628,  1629,  1651,
      20,  1331,    43,   189,  1651,   307,   302,   287,  1639,  1640,
    1641,   750,  1651,  1558,     7,    70,  2050,     5,   162,  1650,
    1651,  1652,  1653,     1,   285,     7,     4,   164,     6,   102,
    2093,  2094,    39,    98,   773,   103,   353,  1650,  1651,  1652,
    1653,   113,   310,   311,   312,   313,   314,   189,    26,    27,
      28,    29,  1770,  1771,   102,  1773,  1687,  1688,  1689,   353,
      38,   103,  1751,  1752,   353,     1,    98,   102,     4,  1614,
       6,   102,     7,   102,  1687,  1688,  1689,  1724,    20,   102,
    2174,    97,    98,    99,   100,  1724,  1631,   102,  2175,   355,
      26,    27,    28,    29,   355,    84,  1950,  2052,   102,   102,
     750,   355,     5,   111,   112,   188,  1651,   102,   353,   103,
    2173,   102,  1946,   150,   104,   102,   750,   102,   126,   287,
     128,   129,   130,   773,   288,   102,   355,  1470,   185,   779,
    2164,   354,  1470,    41,  1781,  1766,   354,  2092,  1827,   773,
    1470,   285,  1781,   151,   152,   153,   354,   354,  1491,   302,
       7,   354,   354,  1491,   133,   354,   895,    93,   354,   354,
     354,  1491,   355,   102,  1853,  1827,   355,  1510,     8,   354,
     354,  1860,  1510,   354,  1588,  1589,  1590,  1591,     1,  1724,
    1510,     4,   103,     6,     8,   102,   102,   340,   103,   102,
     102,  1853,  1823,     5,  1825,  1826,   353,   133,     8,   271,
     102,   913,   355,    26,    27,    28,    29,   915,  1839,   919,
     914,   355,   712,   711,  1845,  1558,   710,  2172,   527,  1362,
    1558,  1852,   713,   917,  1855,  1025,   876,  1171,  1558,   517,
    1861,    20,  1336,   396,  1635,  1977,  1781,  1868,  1869,  1870,
     890,   891,   892,   893,   894,   895,  2178,   897,  2125,  1975,
    2037,    45,  2038,  1880,  2039,  1868,  1869,  1870,  1976,  2029,
    1912,   895,  2040,  1890,  2150,  1912,    60,    61,   340,    89,
    1897,  1614,   922,  1912,  1590,   393,  1614,    91,  1786,   789,
     798,  1768,   308,   355,  1614,  1708,  1739,   395,  1631,  1741,
     113,   941,   859,  1631,  2028,  1984,    45,  1986,  2097,  1946,
    1250,  1631,  1251,  1950,  1252,  1269,  1491,  1946,  1651,   879,
    1489,    60,    61,  1651,  1969,   109,   774,  1276,   290,  1016,
     888,  1651,  1969,  1954,  1979,   119,  1316,   205,  1208,  1501,
    1969,   125,  1979,  1471,  1278,   271,  1280,  1751,  1752,  1506,
    1979,   405,    37,   120,   378,   407,  2161,   408,   406,   303,
      45,   637,    47,   304,  1985,   149,  1987,    52,    53,    54,
     109,    56,   340,   304,   615,    -1,  1079,  1912,  1999,  2000,
     119,  2002,  2003,  2004,  2005,  2006,   125,   355,  2009,    -1,
      -1,  1724,    -1,    -1,    -1,     1,  1724,  1331,     4,    -1,
       6,  2046,    -1,    -1,  1724,    -1,    -1,    -1,    -1,  2046,
     149,  1946,  2120,  2121,   340,   997,    -1,  2046,    -1,    -1,
      26,    27,    28,    29,    -1,    -1,  2047,    -1,    -1,   355,
      -1,    -1,    -1,    -1,  1969,  2056,  2057,    -1,     1,    -1,
      -1,     4,  1171,     6,  1979,  2153,  2125,     1,  1781,    -1,
       4,    -1,     6,  1781,    -1,  2163,    -1,  2099,   271,    -1,
      -1,  1781,  2099,    26,    27,    28,    29,    -1,  2113,  2148,
    2099,    -1,    26,    27,    28,    29,  2113,  2098,  2099,  2100,
    2101,    -1,    -1,    -1,  2113,  2106,  2107,  2108,  2109,    -1,
    2111,    -1,    -1,    -1,  2115,  2098,  2099,  2100,  2101,  2178,
      -1,    -1,    -1,  2106,  2107,  2108,  2109,   113,    -1,    -1,
    2131,  2046,    -1,    -1,    -1,  2136,  2137,  2138,  2139,  2140,
    2141,  2142,  2143,  2144,  2145,  2146,  2147,   340,    -1,    -1,
      93,  1171,    -1,    -1,    -1,    -1,  1470,    -1,  2141,  2142,
    2143,  2162,   355,    -1,  1126,  1127,    -1,  1171,    -1,  1278,
      -1,  1280,    -1,    -1,    -1,    -1,    -1,  1491,    -1,    -1,
      -1,    -1,    -1,    -1,  2099,  2186,  2187,  2188,    -1,    -1,
     133,    -1,    -1,    -1,    -1,    -1,  1510,    -1,  2113,  1912,
      -1,    -1,    -1,    45,  1912,   270,    -1,    -1,  1228,  1229,
      -1,  1231,  1912,  1175,    -1,    -1,   366,    -1,    60,    61,
     285,    -1,  1331,    -1,    -1,    -1,     1,   377,   378,     4,
      -1,     6,    -1,  1946,    -1,    -1,   301,     1,  1946,  1204,
       4,   306,     6,   308,  1558,    -1,  1946,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    -1,  1969,    -1,  1278,    -1,
    1280,  1969,    26,    27,    28,    29,  1979,   109,    -1,  1969,
      -1,  1979,    -1,    -1,  1278,    -1,  1280,   119,    -1,  1979,
      -1,    -1,    -1,   125,    -1,   271,  1306,  1307,  1308,  1309,
    1310,  1311,  1312,  1313,  1314,  1315,  1316,    -1,     1,    -1,
    1614,     4,    -1,     6,    -1,    -1,    -1,   149,    -1,    -1,
      -1,  1331,    -1,    -1,    -1,    -1,    -1,  1631,    93,    -1,
      -1,    -1,    -1,    26,    27,    28,    29,  1331,   271,    -1,
      -1,    -1,    -1,  2046,    -1,    38,    -1,  1651,  2046,    -1,
      -1,    -1,    -1,    -1,    10,    -1,  2046,    -1,    -1,    -1,
      -1,    -1,     1,   287,   340,     4,    -1,     6,   133,    -1,
      -1,  1470,    -1,  1328,    -1,  1330,  1331,  1332,  1333,   355,
      -1,    -1,    -1,    39,    40,    41,    42,    26,    27,    28,
      29,    -1,  1491,    -1,    -1,    -1,  2099,    -1,    -1,    -1,
      -1,  2099,  1354,    -1,    -1,  1357,    -1,   340,    -1,  2099,
    2113,  1510,    -1,    -1,    -1,  2113,   340,    73,    -1,    -1,
    1724,    -1,   355,  2113,    -1,    81,    82,    83,    84,    -1,
      45,   355,    -1,    -1,    -1,    -1,   111,   112,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,   104,    -1,
     125,    -1,    -1,    -1,    37,    -1,    -1,    -1,   133,  1558,
    1470,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,
     126,   127,   128,    -1,   149,   131,  1470,  1781,   134,  1489,
      -1,  1491,  1492,    -1,    -1,  1440,  1496,    -1,  1443,    -1,
    1445,    -1,    -1,  1448,   109,    70,    -1,  1491,  1508,    -1,
    1510,    -1,    -1,    86,   119,    -1,   271,    -1,  1518,    -1,
     125,  1521,    -1,    -1,  1524,  1614,  1510,    -1,    -1,    -1,
     103,    -1,  1474,    -1,  1476,  1477,    -1,  1479,   103,   104,
     105,    -1,  1631,   287,   149,   110,    -1,    -1,    -1,   114,
      -1,    -1,    -1,    -1,   119,   128,   129,    -1,  1558,  1559,
     125,  1506,  1651,    -1,   129,    -1,     1,    -1,    -1,     4,
      -1,     6,    -1,    -1,  1558,    -1,     1,  1577,  1578,     4,
      -1,     6,    -1,    -1,   149,   340,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    -1,   340,    -1,    -1,    -1,
     355,    26,    27,    28,    29,    40,   271,   272,   273,   274,
      -1,   355,    -1,    -1,  1614,    40,    -1,    45,  1912,    -1,
      -1,    -1,   287,   288,   289,   271,   272,   273,    -1,    -1,
    1614,  1631,    60,    61,    -1,  1724,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1631,    -1,   779,
      -1,  1651,  1946,    88,    89,    90,    91,   340,    93,    -1,
      -1,    96,    -1,    88,    89,    90,    91,  1651,    93,    -1,
      -1,    96,   355,   302,   247,  1969,    -1,    -1,   113,    -1,
      -1,   109,    -1,    -1,    -1,  1979,    -1,    -1,   113,    -1,
      -1,   119,  1781,   823,   267,   268,    -1,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1650,  1651,  1652,  1653,    -1,
      -1,   340,   285,    -1,    -1,   280,    -1,    -1,   283,   284,
      -1,   149,    -1,    -1,  1724,    -1,   355,   162,   301,    -1,
      -1,    -1,    -1,   306,    45,   308,    -1,   162,    -1,    -1,
    1724,    -1,  1687,  1688,  1689,    -1,    -1,    -1,    -1,    60,
      61,    -1,  2046,   318,   319,    -1,   402,   403,   404,    -1,
     890,   891,   892,   893,   894,    -1,    -1,   897,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1781,    -1,    -1,    -1,    45,    -1,    -1,    -1,   435,
    1732,    -1,   922,    -1,   359,    -1,    -1,  1781,   109,    -1,
      60,    61,    -1,    -1,     1,  2099,    -1,     4,   119,     6,
      -1,   941,    -1,    -1,   125,    -1,    -1,    -1,   464,  2113,
      -1,    -1,    -1,  1912,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    -1,    -1,   270,    37,    -1,   149,    -1,
      -1,    -1,    -1,    40,    45,   270,    47,    -1,    49,   109,
     285,    52,    53,    54,    -1,    56,    -1,  1946,    -1,   119,
     285,    -1,    -1,    -1,    -1,   125,   301,    -1,    -1,    -1,
      -1,   306,    -1,    -1,    -1,    -1,   301,    -1,    -1,    -1,
    1969,   306,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
    1979,    88,    89,    90,    91,    -1,    93,    -1,    -1,    96,
      -1,    -1,    -1,    -1,    -1,   340,     1,    -1,    -1,     4,
      -1,     6,  1912,    -1,    -1,   340,   113,    -1,    -1,    -1,
     355,    -1,    -1,  1868,  1869,  1870,    -1,    -1,  1912,    -1,
     355,    26,    27,    28,    29,   134,    -1,    -1,    -1,  1881,
      -1,    -1,    -1,    -1,   143,    40,  1946,    -1,    -1,  1891,
    1950,    -1,    -1,    -1,    -1,    -1,  1898,  2046,    -1,   158,
      -1,    -1,  1946,   162,    -1,   162,    -1,   166,   167,  1969,
      -1,    -1,   171,   172,   173,   174,   175,    -1,    -1,  1979,
      -1,    -1,    -1,    -1,    -1,  1969,    -1,    -1,    -1,    -1,
      -1,  1933,    -1,    -1,    89,  1979,    91,   107,    93,   109,
     110,    96,    -1,   113,    -1,   115,    -1,    -1,   118,   119,
    2099,    -1,   122,   123,   124,   125,    -1,    -1,   113,   129,
      -1,    -1,   132,   133,  2113,    -1,    -1,    -1,    -1,    -1,
     140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2046,    -1,  1990,  1991,
    1992,    -1,    -1,    -1,     1,    -1,    -1,     4,    -1,     6,
      -1,    -1,  2046,    -1,    -1,    -1,    -1,   162,    -1,   270,
      -1,    -1,    -1,   270,  2016,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    -1,   285,    -1,    -1,    -1,   285,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,  2099,
     301,    -1,    -1,    -1,   301,   306,    -1,   308,    38,   306,
      -1,    -1,    -1,  2113,    -1,  2099,    -1,    -1,  1248,  1249,
    1250,  1251,  1252,    -1,  1254,  1255,    -1,    -1,    -1,  2113,
      -1,    -1,    -1,  1263,  1264,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,   340,    91,    -1,    93,    -1,    -1,    96,
      -1,    -1,    -1,  2098,  2099,  2100,  2101,    -1,   355,    -1,
      -1,  2106,  2107,  2108,  2109,    -1,   113,    -1,    -1,    -1,
      -1,    -1,   102,    -1,    -1,   270,  1306,  1307,  1308,  1309,
    1310,  1311,  1312,  1313,  1314,  1315,  1316,    -1,    -1,     1,
     285,    -1,    -1,    -1,    -1,    -1,  2141,  2142,  2143,    11,
      12,    13,    14,    15,    16,    17,   301,    -1,    20,    -1,
      -1,   306,    -1,    -1,    -1,   162,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2169,  2170,  2171,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   173,    -1,   340,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,    71,
     355,    -1,    74,    75,    76,    77,    78,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    -1,    97,    98,    99,   100,    -1,
     102,    -1,     1,    -1,   106,     4,   108,     6,    -1,   111,
     112,    -1,   114,    -1,    -1,   117,    -1,    -1,    -1,     1,
      -1,    -1,     4,    -1,     6,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,   270,   136,   137,   138,   139,    -1,    -1,
     142,    40,   144,    -1,    26,    27,    28,    29,   285,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    -1,   457,    -1,    -1,
      -1,    -1,   111,   112,   301,    47,   115,    -1,    -1,   306,
      52,    -1,    54,    -1,    56,    -1,  1496,   126,   127,   128,
     129,   130,   131,   132,   133,   134,    -1,    -1,  1508,    -1,
      89,    -1,    91,    -1,    93,    -1,    -1,    96,    -1,    -1,
      -1,    -1,    -1,   340,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,   355,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   175,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1559,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,  1577,  1578,     4,
      -1,     6,    -1,   162,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,
     162,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,
      -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    -1,    97,    -1,    99,    -1,    -1,   102,   103,   104,
     105,    -1,    -1,   108,    -1,   110,    -1,    -1,   113,   114,
      -1,   270,    -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,
     125,    -1,    -1,    -1,    -1,    -1,   285,    -1,   270,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,    -1,    -1,
      -1,   146,   301,   285,   149,    -1,    -1,   306,    -1,   154,
      -1,    -1,   157,    -1,    -1,   160,   161,   162,    -1,   301,
     165,    -1,    -1,   168,   306,   170,   308,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   340,    -1,    -1,    -1,    -1,    -1,   449,    -1,    -1,
     195,   196,    -1,    -1,   456,    -1,   355,    -1,   340,    -1,
      -1,    -1,    -1,    -1,    -1,   467,    -1,   469,    -1,   471,
      -1,   473,    -1,   355,    -1,    -1,   478,    -1,    -1,    -1,
     482,    -1,   484,    -1,    -1,    -1,   231,   232,   233,   234,
      -1,   493,    -1,    -1,    -1,   240,   241,    -1,    -1,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,    -1,    -1,   270,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     285,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     295,    -1,    -1,    -1,    -1,    -1,   301,    -1,    -1,    -1,
      -1,   306,    -1,    -1,    -1,    -1,    23,   312,   313,    -1,
     315,    -1,    -1,   318,   319,   320,   321,    -1,    -1,    -1,
     325,    38,    89,    -1,   329,   330,   331,    -1,    -1,    -1,
     335,   336,    -1,     1,    -1,   340,     4,    -1,     6,   344,
      -1,    -1,   347,   348,   111,   112,    -1,    -1,   115,   354,
     355,   356,    -1,    -1,   359,    23,    -1,    -1,    26,    27,
      28,    29,    30,    31,    -1,    -1,   133,    35,    36,    37,
    1950,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,
      -1,    -1,   189,    -1,    -1,    93,    -1,    -1,    -1,    97,
      -1,    99,    -1,    -1,   102,   103,   104,   105,    -1,    -1,
     108,    -1,   110,    -1,    -1,   113,   114,    -1,    -1,    -1,
      -1,   119,    -1,    -1,    -1,    -1,   173,   125,    -1,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,    -1,   141,    -1,    -1,    -1,    -1,   146,    -1,
     247,   149,    -1,    -1,    -1,    -1,   154,    -1,    -1,   157,
      -1,    -1,   160,   161,   162,    -1,    -1,   165,    -1,    -1,
     168,    -1,   170,    -1,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,    -1,    -1,
     287,   288,   289,    -1,    -1,    -1,    -1,   195,   196,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      -1,   308,    -1,    -1,    45,    -1,    47,    -1,    49,    -1,
      -1,    52,    53,    54,    -1,    56,    -1,    -1,    -1,    60,
      61,    -1,    -1,   231,   232,   233,   234,    -1,    -1,    -1,
      -1,    -1,   240,   241,    -1,    -1,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
      -1,    -1,   270,    -1,    -1,    -1,    -1,    -1,   109,    -1,
      -1,    37,    -1,    -1,    -1,    -1,    42,   285,   119,    45,
      46,    47,    48,    -1,   125,    51,    52,   295,    54,    55,
      56,    -1,    58,   301,    -1,    -1,    -1,    -1,   306,    -1,
      -1,    -1,    -1,    -1,   312,   313,    -1,   315,   149,    -1,
     318,   319,   320,   321,    -1,    -1,    -1,   325,    -1,    -1,
      -1,   329,   330,   331,    -1,    -1,    -1,   335,   336,    -1,
      -1,    97,   340,    99,   100,   101,   344,    -1,     1,   347,
     348,     4,    -1,     6,    -1,    -1,   354,   355,   356,    -1,
      -1,   359,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    -1,   998,    -1,    -1,    62,
      63,   103,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,   270,
      93,   133,    -1,    -1,    97,    -1,    99,    -1,    -1,   102,
     103,   104,   105,    -1,   285,   108,    -1,   110,   150,    -1,
     113,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,
     301,    -1,   125,    -1,    -1,   306,    -1,   308,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,
      -1,    -1,    -1,   146,    -1,    -1,   149,    -1,    -1,    -1,
      -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,   162,
      -1,    -1,   165,    -1,   270,   168,    -1,   170,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   285,
      -1,    -1,    -1,    -1,   290,   291,   292,   293,    -1,    -1,
      -1,    -1,   195,   196,    -1,   301,    -1,    -1,    -1,    -1,
     306,    -1,   308,   309,    -1,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,    -1,    -1,   231,   232,
     233,   234,    -1,    -1,    -1,    -1,    -1,   240,   241,    -1,
      -1,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,    -1,   308,   270,    -1,    -1,
     312,   313,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     322,    -1,   285,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   295,    -1,    -1,    -1,    -1,    -1,   301,    -1,
      -1,    -1,    -1,   306,    -1,    -1,   348,    -1,    -1,   312,
     313,    -1,   315,    -1,    -1,   318,   319,   320,   321,    -1,
      -1,    -1,   325,    -1,    -1,    -1,   329,   330,   331,    -1,
      -1,    -1,   335,   336,    -1,    -1,     4,   340,     6,    -1,
      -1,   344,    -1,    -1,   347,   348,    -1,    -1,    -1,    -1,
      -1,   354,   355,   356,    -1,    23,   359,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,   103,    -1,    -1,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   130,    -1,    -1,   133,    -1,    -1,    97,
      -1,    99,    -1,    -1,   102,   103,   104,   105,    -1,    -1,
     108,    -1,   110,   150,    -1,    -1,   114,    -1,    -1,    -1,
      -1,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,    -1,
      -1,   149,    -1,    -1,    -1,   180,   154,    -1,    -1,   157,
      -1,    -1,   160,   161,    -1,    -1,    -1,   165,    -1,    -1,
     168,    -1,   170,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   195,   196,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,    -1,    -1,   231,   232,   233,   234,    -1,    -1,    -1,
      -1,    -1,   240,   241,    -1,    -1,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
      -1,   308,   270,    -1,     5,   312,   313,    -1,    -1,    -1,
     111,   112,    -1,    -1,   115,   322,    -1,   285,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,   295,    -1,    -1,
      31,    -1,   133,   301,    -1,    36,    -1,    -1,   306,    -1,
      -1,   348,    -1,    -1,   312,   313,    -1,   315,    -1,    -1,
     318,   319,   320,   321,    -1,    -1,    -1,   325,    -1,    -1,
      -1,   329,   330,   331,    -1,    -1,    -1,   335,   336,    70,
      -1,    -1,    -1,    -1,    -1,    -1,   344,    -1,    -1,   347,
     348,    -1,    -1,    84,    -1,    86,   354,   355,   356,    -1,
      -1,   359,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,    -1,    -1,   108,    -1,   110,
      -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,   119,    -1,
      -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,   129,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     141,    -1,    -1,    -1,    -1,   146,   247,    -1,   149,    -1,
      -1,    -1,    -1,   154,    -1,    -1,   157,    -1,    -1,   160,
     161,    -1,    -1,    -1,   165,    -1,    -1,   168,    -1,   170,
     271,   272,   273,   274,   275,   276,    -1,   278,   279,   280,
     281,   282,   283,   284,    -1,    -1,   287,   288,   289,    -1,
      -1,    -1,    -1,    -1,   195,   196,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,   308,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
     231,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,    -1,    -1,   270,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   280,
      -1,    -1,   283,   284,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,    -1,    -1,   108,    -1,
     110,   312,   313,    -1,   114,    -1,    -1,   318,   319,   119,
      -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,   129,
     331,    -1,    -1,    -1,   335,   336,    -1,    -1,    -1,    -1,
      -1,   141,    -1,    -1,   345,   346,   146,   348,    -1,   149,
      -1,    -1,    -1,    -1,   154,   356,    -1,   157,   359,    -1,
     160,   161,    -1,    -1,    -1,   165,    -1,    -1,   168,    -1,
     170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   195,   196,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,   231,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,    -1,    -1,
     270,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,    -1,    -1,   108,
      -1,   110,   312,   313,    -1,   114,    -1,    -1,   318,   319,
     119,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,
     129,   331,    -1,    -1,    -1,   335,   336,    -1,    -1,    -1,
      -1,    -1,   141,    -1,    -1,   345,   346,   146,   348,    -1,
     149,    -1,    -1,    -1,    -1,   154,   356,    -1,   157,   359,
      -1,   160,   161,    -1,    -1,    -1,   165,    -1,    -1,   168,
      -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   195,   196,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,   231,    31,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,    -1,
      -1,   270,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   280,    -1,    -1,   283,   284,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,    -1,    -1,
     108,    -1,   110,   312,   313,    -1,   114,    -1,    -1,   318,
     319,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,
      -1,   129,   331,    -1,    -1,    -1,   335,   336,    -1,    -1,
      -1,    -1,    -1,   141,    -1,    -1,   345,   346,   146,   348,
      -1,   149,    -1,    -1,    -1,    -1,   154,   356,    -1,   157,
     359,    -1,   160,   161,    -1,    -1,    -1,   165,    -1,    -1,
     168,    -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   195,   196,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,   231,    31,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
      -1,    -1,   270,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   280,    -1,    -1,   283,   284,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,    -1,
      -1,   108,    -1,   110,   312,   313,    -1,   114,    -1,    -1,
     318,   319,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,    -1,   129,   331,    -1,    -1,    -1,   335,   336,    -1,
      -1,    -1,    -1,    -1,   141,    -1,    -1,   345,   346,   146,
     348,    -1,   149,    -1,    -1,    -1,    -1,   154,   356,    -1,
     157,   359,    -1,   160,   161,    -1,    -1,    -1,   165,    -1,
      -1,   168,    -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   195,   196,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,   231,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,    -1,    -1,   270,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
      -1,    -1,    -1,    -1,   110,   312,   313,    -1,   114,    -1,
      -1,   318,   319,   119,    -1,    -1,    -1,    -1,    -1,   125,
      -1,    -1,    -1,   129,   331,    -1,    -1,    -1,   335,   336,
      -1,    -1,    21,    70,    -1,   141,    -1,    -1,   345,   346,
     146,   348,    -1,   149,    -1,    -1,    -1,    -1,   154,   356,
      -1,   157,   359,    -1,   160,   161,    -1,    -1,    -1,   165,
      -1,    -1,   168,    -1,   170,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,
      -1,    70,   119,    -1,    -1,    -1,    -1,    -1,   125,   195,
     196,    -1,   129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,
      -1,    -1,   149,   102,   103,   104,   105,   154,    -1,    -1,
     157,   110,    -1,   160,   161,   114,    -1,    -1,   165,    -1,
     119,   168,    -1,   170,    -1,    -1,   125,    -1,    -1,    -1,
     129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   141,    -1,    -1,    -1,    -1,   146,   195,   196,
     149,    -1,    -1,    -1,    -1,   154,    -1,    -1,   157,    -1,
      -1,   160,   161,    -1,   280,    -1,   165,   283,   284,   168,
      -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   195,   196,    -1,    -1,
      -1,    -1,   318,   319,    -1,   321,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   345,
     346,    -1,    -1,   280,    -1,    -1,   283,   284,   354,    -1,
     356,    -1,    -1,   359,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   318,   319,    -1,   321,    -1,    -1,    -1,    -1,    -1,
      -1,   280,    -1,    -1,   283,   284,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,   345,   346,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   354,    -1,   356,
      -1,    -1,   359,    -1,    -1,    -1,    -1,    -1,    -1,   318,
     319,    -1,   321,    -1,    -1,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,
      -1,    -1,   119,    -1,    -1,    -1,   345,   346,   125,    -1,
      -1,    -1,   129,    -1,    -1,    -1,    -1,   356,    -1,    -1,
     359,    -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,
      -1,    -1,   149,    -1,    -1,    -1,    -1,   154,    -1,    -1,
     157,    -1,    23,   160,   161,    -1,    -1,    -1,   165,    30,
      31,   168,    -1,   170,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,   195,   196,
      -1,    62,    63,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,    99,    -1,
      -1,   102,   103,   104,   105,    -1,    -1,   108,    -1,   110,
      -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,   119,    -1,
      -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     141,    -1,    -1,   280,    -1,   146,   283,   284,   149,    -1,
      -1,    -1,    -1,   154,    -1,    -1,   157,    -1,    -1,   160,
     161,    -1,    -1,    -1,   165,    -1,    -1,   168,    -1,   170,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   318,   319,    -1,   321,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   195,   196,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   345,   346,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   354,    -1,   356,
      -1,    -1,   359,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     231,   232,   233,   234,    -1,    -1,    -1,    -1,    -1,   240,
     241,    -1,    -1,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,    -1,    -1,   270,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,   285,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    36,   295,    -1,    -1,    -1,    -1,    -1,
     301,    -1,    -1,    -1,    -1,   306,    -1,    -1,    -1,    -1,
      -1,   312,   313,    -1,   315,    -1,    -1,   318,   319,   320,
     321,    -1,    -1,    -1,   325,    -1,    -1,    -1,   329,   330,
     331,    -1,    -1,    -1,   335,   336,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   344,    -1,    -1,   347,   348,    -1,    -1,
      -1,    -1,    -1,   354,    -1,   356,    -1,    -1,   359,   102,
     103,   104,   105,    -1,    -1,   108,    -1,   110,    -1,    -1,
      -1,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,
      -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,
      -1,    -1,    -1,   146,    -1,    -1,   149,    -1,    -1,    -1,
      -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,    -1,
      -1,    -1,   165,    -1,    -1,   168,    -1,   170,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   195,   196,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    -1,    -1,    -1,    36,    -1,    -1,   231,   232,
     233,   234,    -1,    -1,    -1,    -1,    -1,   240,   241,    -1,
      -1,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,    -1,    -1,   270,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,    -1,    -1,   108,    -1,   110,
      -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,   119,   312,
     313,    -1,    -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   331,    -1,
     141,    -1,   335,   336,    -1,   146,    -1,    -1,   149,    -1,
      -1,    -1,    -1,   154,   347,   348,   157,    -1,    -1,   160,
     161,   354,    -1,   356,   165,    -1,   359,   168,    -1,   170,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,   195,   196,    -1,    -1,    30,    31,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     231,   232,   233,   234,    -1,    -1,    -1,    -1,    -1,   240,
     241,    -1,    -1,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,    -1,    -1,   270,
     102,   103,   104,   105,    -1,    -1,   108,    -1,   110,    -1,
      -1,    -1,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,
      -1,    -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
      -1,   312,   313,    -1,   146,    -1,    -1,   149,    -1,    -1,
      -1,    -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,
     331,    -1,    -1,   165,   335,   336,   168,    -1,   170,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   347,   348,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   356,    -1,    -1,   359,    -1,
      23,    -1,    -1,   195,   196,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,
     232,   233,   234,    -1,    -1,    -1,    -1,    70,   240,   241,
      -1,    -1,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,    -1,    -1,   270,   102,
     103,   104,   105,    -1,    -1,   108,    -1,   110,    -1,    -1,
      -1,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,
      -1,    -1,   125,    -1,    -1,    -1,   129,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,
     312,   313,    -1,   146,    -1,    -1,   149,    -1,    -1,    -1,
      -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,   331,
      -1,    -1,   165,   335,   336,   168,    -1,   170,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   347,   348,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   356,    -1,    -1,   359,    -1,    -1,
      -1,    -1,   195,   196,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,   231,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,    -1,    -1,   270,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   280,    -1,    -1,
     283,   284,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,    -1,    -1,    -1,    -1,   110,   312,
     313,    -1,   114,    -1,    -1,   318,   319,   119,    -1,    -1,
      -1,    -1,    -1,   125,    -1,    -1,    -1,   129,   331,    -1,
      -1,    -1,   335,   336,    -1,    -1,    -1,    -1,    -1,   141,
      -1,    -1,   345,   346,   146,   348,    -1,   149,    -1,    -1,
      -1,    -1,   154,   356,    -1,   157,   359,    -1,   160,   161,
      -1,     0,     1,   165,    -1,     4,   168,     6,   170,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,   195,   196,    -1,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,
      49,    -1,    -1,    52,    53,    54,    -1,    56,    -1,    -1,
      -1,    60,    61,    62,    -1,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   280,    -1,
     119,   283,   284,    -1,    -1,    -1,   125,    -1,    -1,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,    -1,
     149,    -1,    -1,    -1,    -1,    -1,   318,   319,    -1,   321,
      -1,    -1,   102,   103,   104,   105,    -1,    -1,    -1,    -1,
     110,    -1,    -1,    -1,   114,    -1,    -1,    -1,    70,   119,
      -1,    -1,    -1,   345,   346,   125,    -1,    -1,    -1,   129,
      -1,    -1,   354,    -1,   356,    -1,    -1,   359,    -1,    -1,
      -1,   141,    -1,    -1,    -1,    -1,   146,    -1,    -1,   149,
     102,   103,   104,   105,   154,    -1,    -1,   157,   110,    -1,
     160,   161,   114,    -1,    -1,   165,    -1,   119,   168,    -1,
     170,    -1,    -1,   125,    -1,    -1,    -1,   129,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
      -1,    -1,    -1,    -1,   146,   195,   196,   149,    -1,    -1,
      -1,    -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,
      -1,   270,    -1,   165,    -1,    -1,   168,    -1,   170,    -1,
      -1,    -1,    70,    -1,    -1,    -1,   285,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   301,   195,   196,    -1,    -1,   306,    -1,   308,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,
     280,   129,    -1,   283,   284,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,    -1,
      -1,   149,    -1,    -1,    -1,    -1,   154,    -1,    -1,   157,
      -1,    -1,   160,   161,    -1,    -1,    -1,   165,   318,   319,
     168,   321,   170,    -1,    -1,    -1,    -1,    -1,   280,    -1,
      -1,   283,   284,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   345,   346,   195,   196,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,    -1,   359,
      -1,    -1,    -1,    -1,    -1,    -1,   318,   319,    -1,   321,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   345,   346,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   356,    -1,    -1,   359,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   280,    -1,    -1,   283,   284,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     318,   319,    -1,   321,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   345,   346,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,
      -1,   359
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   363,     0,     1,     4,     6,    26,    27,    28,    29,
      37,    45,    47,    49,    52,    53,    54,    56,    60,    61,
      62,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,   109,   119,   125,   149,   270,   285,
     301,   306,   308,   364,   416,   417,   418,   419,   491,   492,
     493,   495,   510,   364,   104,   103,   488,   488,   488,   493,
     504,   493,   495,   510,   493,   498,   498,   498,   493,   501,
     419,    49,   420,    37,    45,    47,    52,    53,    54,    56,
     270,   285,   301,   306,   308,   421,    49,   422,    37,    45,
      47,    49,    52,    53,    54,    56,   270,   285,   301,   306,
     308,   427,    53,   428,    37,    42,    45,    46,    47,    48,
      51,    52,    54,    55,    56,    58,    97,    99,   100,   101,
     270,   285,   290,   291,   292,   293,   301,   306,   308,   309,
     429,   285,   290,   291,   306,   432,    45,    47,    52,    54,
      58,    97,    99,   433,    47,   434,    23,    30,    31,    36,
     102,   103,   104,   105,   108,   110,   114,   119,   125,   141,
     146,   149,   154,   157,   160,   161,   165,   168,   170,   195,
     196,   231,   232,   233,   234,   240,   241,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   270,   312,   313,   331,   335,   336,   347,   348,   356,
     359,   442,   489,   612,   613,   616,   617,   618,   622,   685,
     688,   690,   694,   699,   700,   702,   704,   714,   715,   717,
     719,   721,   723,   727,   729,   731,   733,   735,   737,   739,
     741,   743,   745,   756,   764,   766,   768,   769,   771,   773,
     775,   777,   779,   781,   783,   785,    58,   341,   342,   343,
     435,   441,    58,   436,   441,   103,   437,   438,   367,   383,
     384,    89,   277,   279,   504,   504,   504,   504,     0,   364,
     488,   488,    57,   338,   339,   507,   508,   509,    35,    37,
      52,    62,    63,    67,    70,    78,    79,    80,    81,    82,
      83,    97,    99,   246,   270,   285,   295,   301,   306,   315,
     318,   319,   320,   321,   325,   329,   330,   344,   354,   514,
     515,   516,   518,   519,   520,   521,   522,   523,   527,   528,
     529,   532,   533,   540,   544,   552,   553,   556,   557,   558,
     559,   560,   581,   582,   584,   585,   587,   588,   591,   592,
     593,   603,   604,   605,   606,   607,   610,   611,   617,   624,
     625,   626,   627,   628,   629,   633,   634,   635,   669,   683,
     688,   689,   712,   713,   714,   746,   364,   353,   353,   364,
     488,   564,   443,   446,   514,   488,   451,   453,   612,   635,
     456,   488,   461,   495,   511,   504,   493,   495,   498,   498,
     498,   501,    89,   277,   279,   504,   504,   504,   504,   510,
     426,   493,   504,   505,   423,   491,   493,   494,   424,   493,
     495,   496,   511,   425,   493,   498,   499,   498,   498,   493,
     501,   502,    89,   277,   279,   658,   426,   426,   426,   426,
     498,   504,   431,   492,   513,   493,   513,   495,   513,    45,
     513,   498,   498,   513,   501,   513,    45,    46,   498,   513,
     513,    89,   277,   294,   658,   659,   504,    45,   513,    45,
     513,    45,   513,    45,   513,   504,   504,   504,    45,   513,
     390,   504,    45,   513,    45,   513,   504,   402,   493,   495,
     498,   498,   513,    45,   498,   495,   103,   106,   107,   108,
     716,   111,   112,   247,   248,   251,   620,   621,    32,    33,
      34,   247,   691,   132,   623,   166,   167,   767,   111,   112,
     113,   718,   113,   115,   116,   117,   118,   720,   111,   112,
     120,   121,   122,   123,   124,   722,   111,   112,   115,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   175,   724,
     113,   115,   134,   142,   143,   144,   145,   728,   113,   134,
     147,   297,   730,   111,   112,   126,   128,   129,   130,   151,
     152,   153,   732,   113,   115,   134,   142,   143,   145,   155,
     156,   734,   127,   143,   152,   158,   159,   736,   143,   159,
     738,   152,   162,   163,   740,   130,   134,   166,   167,   742,
     134,   166,   167,   169,   744,   134,   143,   158,   162,   166,
     167,   171,   172,   173,   174,   175,   747,   113,   166,   167,
     757,   134,   166,   167,   197,   230,   765,   113,   125,   127,
     145,   149,   152,   235,   268,   269,   348,   701,   703,   772,
     236,   774,   236,   776,   162,   237,   238,   239,   778,   127,
     152,   770,   115,   131,   152,   158,   242,   243,   780,   127,
     152,   782,   113,   127,   134,   152,   158,   784,   103,   130,
     133,   150,   308,   322,   348,   686,   687,   688,   111,   112,
     115,   133,   247,   271,   272,   273,   274,   275,   276,   278,
     279,   280,   281,   282,   283,   284,   287,   288,   289,   308,
     705,   706,   709,   322,   332,   693,   629,   634,   333,   231,
     240,   241,   244,   245,   786,   351,   352,   389,   696,   628,
     488,   408,   441,   342,   388,   441,   377,   394,    46,    48,
      50,    51,    58,    59,    91,   439,   504,   504,   504,   371,
     653,   668,   655,   657,   102,   102,   102,    84,   701,   286,
     604,   170,   488,   612,   684,   684,    62,    98,   488,   103,
     686,    89,   189,   277,   705,   706,   286,   286,   302,   286,
     304,   305,   541,    84,   162,    84,    84,   701,     4,   365,
     636,   637,   340,   512,   519,   446,   371,   287,   288,   530,
     531,   414,   162,   296,   297,   298,   299,   300,   534,   535,
     401,   316,   555,   395,     5,    70,    84,    86,   110,   114,
     119,   125,   129,   149,   231,   280,   283,   284,   296,   318,
     319,   345,   346,   356,   567,   568,   569,   570,   571,   572,
     573,   575,   576,   577,   578,   579,   580,   613,   616,   622,
     678,   679,   680,   685,   690,   694,   700,   701,   702,   704,
     710,   711,   714,   409,   415,    38,    39,   185,   188,   561,
     562,   395,    84,   322,   323,   324,   583,   589,   590,   395,
      84,   586,   589,   374,   380,   400,   326,   327,   328,   594,
     595,   599,   600,    23,   612,   614,   615,    45,   608,   609,
      15,    16,    17,    18,   358,     8,    24,    54,     9,    10,
      11,    12,    13,    14,    19,   110,   114,   119,   125,   141,
     146,   149,   154,   157,   160,   161,   165,   168,   170,   195,
     196,   321,   356,   613,   615,   616,   630,   631,   632,   635,
     670,   671,   672,   673,   674,   675,   676,   677,   679,   680,
     681,   682,    52,    52,    22,   354,   651,   670,   671,   676,
     651,    38,   354,   563,   354,   354,   354,   354,   354,   507,
     514,   564,   443,   446,   451,   453,   456,   461,   504,   504,
     504,   371,   653,   668,   655,   657,   514,   415,    57,    57,
      57,    57,   453,    57,   461,   504,   371,   391,   399,   406,
     453,   415,    43,   430,   493,   498,   513,   504,    45,   371,
     493,   493,   493,   493,   391,   399,   406,   493,   371,   493,
     493,   399,   498,   488,   411,     7,     8,   113,   251,   252,
     619,   300,   407,   103,   126,   286,   411,   410,   376,   410,
     385,   110,   125,   110,   125,   367,   137,   138,   139,   140,
     725,   383,   410,   386,   410,   387,   384,   410,   386,   366,
     375,   369,   412,   413,    23,    38,   102,   173,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   748,   749,   750,   410,   372,   180,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   758,   763,   404,   410,   383,   384,
     389,   703,   403,   403,   360,   403,   403,   360,   403,   382,
     379,   373,   410,   393,   392,   406,   392,   406,   111,   112,
     125,   133,   149,   271,   272,   273,   707,   708,   709,   370,
     333,   333,   102,   403,   382,   379,   373,   393,   350,   695,
     357,   440,   441,   666,   666,   666,   287,   354,   652,   302,
     354,   667,   354,   541,   654,   354,   489,   656,     5,   125,
     149,   579,    84,   579,   601,   602,   629,   175,    23,    23,
      96,   354,    52,    52,    52,   102,   304,    52,   709,    52,
     579,   579,   304,   305,   545,   579,   102,   596,   597,   598,
     612,   616,   629,   633,   694,   700,   599,   579,   579,    84,
      21,   635,   640,   641,   642,   649,   676,   677,     7,   355,
     489,   354,   102,   102,   531,    77,   110,   125,   170,   254,
     537,   489,   102,   102,   102,   489,   536,   535,   141,   154,
     170,   317,   579,   402,     5,   579,    84,   376,   385,   367,
     383,   384,    84,   395,   395,   572,   613,   680,    15,    16,
      17,    18,   358,    20,    22,     8,    54,     5,   589,    84,
      86,   236,   296,     7,     7,   102,   102,   562,     5,     7,
       5,   579,   597,   612,   616,   595,     7,   488,   354,   488,
     354,   609,   681,   681,   672,   673,   674,   628,   354,   524,
     614,   671,   383,   386,   384,   386,   366,   375,   369,   412,
     413,   408,   372,   404,   395,   676,     7,    20,    15,    16,
      17,    18,   358,     7,    20,    22,     8,   670,   671,   676,
     579,   579,   102,   355,   364,    20,   364,   102,   476,   415,
     445,   447,   452,   458,   462,   563,   354,   354,   354,   354,
     354,   666,   666,   666,   652,   667,   654,   656,   102,   102,
     102,   102,   102,   354,   666,   103,   370,   493,   102,   621,
     410,   378,   102,   397,   397,   376,   383,   376,   383,   113,
     130,   135,   136,   236,   383,   726,   368,    96,   754,   189,
     752,   194,   755,   192,   193,   753,   190,   191,   751,   130,
     220,   224,   225,   226,   762,   215,   216,   217,   218,   760,
     219,   220,   221,   222,   223,   761,   761,   224,   227,   227,
     228,   229,   228,   113,   130,   162,   759,   405,   403,   102,
     102,   111,   112,   111,   112,   370,   370,   102,   102,   334,
     692,   102,   159,   349,   697,   701,   354,   354,   354,   102,
     469,   371,   545,   474,   391,   470,   102,   399,   475,   406,
     579,     5,     5,   579,   614,    89,    92,   512,   643,   644,
      38,   173,   178,   188,   749,   750,   489,   489,   102,   629,
     638,   639,   579,   579,   579,   370,   102,   579,    52,   579,
     391,   102,   547,   549,   550,   399,   103,   288,   542,    22,
     400,    84,   326,    43,   579,   365,     5,   365,   270,   285,
     301,   646,   647,    89,    92,   512,   645,   648,   365,   637,
     448,   376,   148,   143,   148,   538,   539,   103,   113,   554,
     616,   113,   554,   408,   113,   554,   579,     5,   579,   579,
     357,   567,   567,   568,   569,   570,   102,   572,   567,   574,
     614,   635,   579,   579,    84,     8,    84,   613,   680,   710,
     710,   579,   590,   579,   589,   600,   368,   601,   638,   365,
     525,   526,   357,   676,   670,   676,   681,   681,   672,   673,
     674,   676,   102,   670,   676,   632,   676,    20,    20,   102,
      39,   364,   355,   364,   416,   512,   563,    37,    47,    52,
      54,    56,   162,   270,   285,   301,   306,   308,   355,   364,
     416,   444,   512,    93,   113,   162,   355,   364,   416,   478,
     484,   485,   512,   514,    40,    88,    89,    90,    91,    93,
      96,   113,   162,   270,   355,   364,   416,   459,   512,   517,
     518,    40,    89,    91,   113,   162,   355,   364,   416,   459,
     512,   517,    41,    44,   162,   285,   355,   364,   416,   415,
     445,   447,   452,   458,   462,   354,   354,   354,   371,   391,
     399,   406,   462,   370,   370,     7,   407,   410,   383,   750,
     410,   404,   361,   361,   383,   383,   384,   384,   692,   337,
     692,   102,   381,   389,   111,   112,   698,   472,   473,   471,
     288,   355,   364,   416,   512,   652,   547,   549,   355,   364,
     416,   512,   667,   355,   364,   416,   512,   654,   542,   355,
     364,   416,   512,   656,   579,   579,     5,   103,   490,   490,
     644,   408,   368,   368,   354,   519,   643,   392,   392,   370,
     370,   370,   579,   370,    20,   103,   288,   303,   546,   303,
     548,    20,   307,   543,   596,   612,   616,   598,   597,   579,
      43,    81,    82,   650,   677,   683,   189,   287,   371,   302,
     647,   490,   490,   648,   355,   364,   514,   383,     7,   408,
     554,   554,    70,   554,   579,     5,   579,   164,   579,   589,
     589,     5,   355,   517,   519,   640,     7,   355,   670,   670,
     102,    39,   415,   488,   506,   488,   497,   488,   500,   500,
     488,   503,   103,    89,   277,   279,   506,   506,   506,   506,
     364,    78,    79,   486,   487,   612,   410,    98,   364,   364,
     364,   364,   364,   450,   617,   490,   490,   353,    94,    95,
     460,   102,   103,   128,   129,   247,   267,   268,   466,   467,
     477,    85,    86,    87,    89,   454,   455,   364,   364,   364,
     518,   450,   490,   353,   467,   454,   364,   364,   364,   103,
     353,    98,   371,   355,   355,   355,   355,   355,   472,   473,
     471,   355,   102,     7,   396,   102,   381,   389,    93,   133,
     271,   355,   364,   416,   512,   664,    89,    96,   133,   167,
     271,   355,   364,   416,   512,   665,   113,   271,   355,   364,
     416,   512,   661,   102,   371,   546,   548,   391,   399,   543,
     406,   579,   638,   355,   370,   310,   311,   312,   313,   314,
     551,   102,   391,   102,   550,   391,   551,   102,   399,   400,
     400,   579,   365,   102,   304,   102,   545,   364,   539,   410,
     410,   402,   410,   579,    84,   601,     5,   355,   355,     5,
     365,   526,   188,   565,   102,   468,   446,   451,   456,   461,
     506,   506,   506,   468,   468,   468,   468,   398,   103,     8,
     364,   364,   364,   453,   398,     8,   364,     7,   364,     5,
     364,   453,     5,   364,   150,   479,   354,   463,   612,   364,
     355,   355,   355,   368,   102,   692,   353,   165,   170,   660,
     492,   370,   490,   102,   660,   102,   492,   370,   104,   492,
     370,   519,   287,   103,   542,   370,   102,   288,   547,   549,
     386,   386,   579,   355,   601,   683,   185,   566,   364,   354,
     354,   354,   354,   354,   468,   468,   468,   354,   354,   354,
     354,    41,   617,   466,   410,   455,    86,   449,   450,   617,
      37,    86,   285,   301,   306,   308,   457,   467,    22,   102,
     103,   352,   480,   481,   482,   612,   364,   103,   104,   464,
     465,   612,   364,   370,   370,   370,     7,   381,   354,   412,
     408,   364,   364,   364,   364,   364,   364,   364,   133,   364,
     355,   370,   102,   546,   548,   355,   365,   565,   476,   447,
     452,   458,   462,   354,   354,   354,   469,   474,   470,   475,
     103,   450,   364,     8,   415,   467,   371,   391,   399,   406,
     364,   364,   102,    22,    25,     7,   355,   102,   103,   662,
     663,   660,   371,   391,   391,   566,   355,   355,   355,   355,
     355,   472,   473,   471,   355,   355,   355,   355,    43,    44,
     483,   364,   617,   364,   410,   410,   102,   102,   365,   465,
       5,     7,   355,   364,   364,   364,   364,   364,   364,   355,
     355,   355,   364,   364,   364,   364,   489,   612,   353,   479,
     410,   102,   663,   364,   410,   415,   370,   370,   370,   371,
     391,   399,   406,   463,   398,   364,   364,   364
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   362,   363,   363,   364,   364,   365,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   416,
     416,   416,   416,   417,   417,   417,   417,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   420,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   422,   423,   423,   424,   424,   425,
     425,   426,   426,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   427,   427,   427,   427,   427,   428,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   430,   431,   431,   432,   432,   432,   432,
     432,   432,   433,   433,   433,   433,   433,   433,   433,   434,
     435,   435,   436,   436,   437,   438,   438,   439,   439,   439,
     439,   439,   439,   439,   439,   440,   440,   441,   441,   441,
     442,   443,   444,   444,   445,   445,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     446,   447,   447,   447,   447,   447,   447,   447,   447,   448,
     448,   448,   449,   449,   450,   450,   451,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     453,   453,   454,   454,   455,   455,   455,   455,   456,   457,
     457,   457,   457,   457,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   459,   459,
     460,   460,   461,   462,   462,   462,   462,   462,   462,   462,
     463,   463,   464,   464,   464,   465,   465,   465,   466,   466,
     467,   467,   468,   469,   469,   469,   469,   469,   470,   470,
     470,   470,   470,   471,   471,   471,   471,   471,   472,   472,
     472,   472,   472,   473,   473,   473,   473,   473,   474,   474,
     474,   474,   474,   475,   475,   475,   475,   475,   476,   476,
     476,   476,   476,   477,   477,   477,   477,   477,   478,   479,
     480,   480,   481,   481,   481,   481,   481,   482,   482,   483,
     483,   483,   483,   484,   485,   486,   486,   487,   487,   488,
     489,   489,   489,   490,   491,   491,   492,   492,   492,   492,
     492,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     510,   510,   510,   511,   512,   513,   513,   514,   514,   515,
     516,   516,   517,   517,   518,   518,   518,   518,   519,   519,
     519,   519,   519,   519,   519,   519,   519,   519,   519,   519,
     519,   519,   519,   519,   519,   519,   519,   519,   519,   520,
     520,   521,   522,   522,   523,   524,   524,   525,   525,   525,
     526,   527,   527,   528,   528,   529,   529,   530,   530,   531,
     531,   532,   532,   533,   534,   534,   535,   535,   535,   535,
     535,   535,   536,   537,   537,   537,   537,   537,   538,   538,
     539,   539,   540,   540,   540,   541,   541,   541,   542,   542,
     543,   543,   544,   544,   545,   545,   545,   546,   546,   547,
     548,   548,   549,   549,   550,   550,   551,   551,   551,   551,
     551,   552,   553,   554,   554,   555,   555,   555,   555,   555,
     555,   555,   555,   556,   557,   557,   558,   558,   558,   558,
     558,   558,   559,   559,   560,   560,   561,   561,   562,   562,
     562,   562,   563,   563,   564,   565,   565,   566,   566,   567,
     567,   567,   567,   567,   567,   567,   567,   567,   567,   567,
     567,   567,   568,   568,   568,   569,   569,   570,   570,   571,
     571,   572,   573,   573,   574,   574,   575,   575,   576,   577,
     578,   578,   579,   579,   579,   580,   580,   580,   580,   580,
     580,   580,   580,   580,   580,   580,   580,   580,   580,   581,
     581,   582,   583,   583,   583,   584,   584,   585,   586,   586,
     586,   586,   586,   587,   587,   588,   588,   589,   589,   590,
     590,   590,   591,   591,   591,   591,   592,   592,   593,   594,
     594,   595,   595,   596,   596,   597,   597,   597,   598,   598,
     598,   598,   599,   599,   600,   600,   601,   601,   602,   603,
     603,   603,   604,   604,   604,   605,   605,   606,   606,   607,
     608,   608,   609,   610,   610,   611,   612,   613,   613,   614,
     614,   615,   616,   617,   617,   617,   617,   617,   617,   617,
     617,   617,   617,   617,   617,   617,   617,   617,   618,   619,
     619,   619,   620,   620,   620,   620,   620,   621,   621,   622,
     622,   623,   623,   624,   624,   624,   625,   625,   626,   626,
     627,   627,   628,   629,   629,   630,   631,   632,   632,   633,
     634,   634,   634,   635,   636,   636,   636,   637,   637,   637,
     638,   638,   639,   640,   640,   641,   641,   642,   642,   643,
     643,   644,   644,   644,   645,   645,   646,   646,   647,   647,
     647,   647,   647,   647,   648,   648,   648,   649,   650,   650,
     651,   651,   651,   651,   652,   653,   654,   655,   656,   657,
     658,   658,   658,   659,   659,   659,   660,   660,   661,   661,
     662,   662,   663,   664,   664,   664,   665,   665,   665,   665,
     665,   666,   667,   667,   668,   669,   669,   669,   669,   669,
     669,   669,   669,   670,   670,   671,   671,   671,   672,   672,
     672,   673,   673,   674,   674,   675,   675,   676,   677,   677,
     677,   677,   678,   678,   679,   680,   680,   680,   680,   680,
     680,   680,   680,   680,   680,   680,   680,   681,   681,   681,
     681,   681,   681,   681,   681,   681,   681,   681,   681,   681,
     681,   681,   681,   681,   682,   682,   682,   682,   682,   682,
     682,   683,   683,   683,   683,   683,   683,   684,   684,   685,
     685,   685,   686,   686,   687,   687,   687,   687,   687,   688,
     688,   688,   688,   688,   688,   688,   688,   688,   688,   688,
     688,   688,   688,   688,   688,   688,   688,   688,   688,   688,
     688,   688,   688,   689,   689,   689,   689,   689,   689,   690,
     690,   691,   691,   691,   692,   692,   693,   693,   694,   695,
     695,   696,   696,   697,   697,   698,   698,   699,   699,   700,
     700,   700,   701,   701,   702,   702,   703,   703,   703,   703,
     704,   704,   704,   705,   705,   706,   706,   706,   706,   706,
     706,   706,   706,   706,   706,   706,   706,   706,   706,   706,
     706,   706,   707,   707,   707,   707,   707,   707,   707,   708,
     708,   708,   708,   709,   709,   709,   709,   710,   710,   711,
     711,   712,   712,   712,   712,   713,   714,   714,   714,   714,
     714,   714,   714,   714,   714,   714,   714,   714,   714,   714,
     714,   714,   714,   714,   715,   716,   716,   716,   716,   717,
     718,   718,   718,   719,   720,   720,   720,   720,   720,   721,
     722,   722,   722,   722,   722,   722,   722,   722,   722,   723,
     723,   723,   724,   724,   724,   724,   724,   724,   724,   724,
     724,   724,   724,   724,   725,   725,   725,   725,   726,   726,
     726,   726,   726,   727,   728,   728,   728,   728,   728,   728,
     728,   729,   730,   730,   730,   730,   731,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   733,   734,   734,   734,
     734,   734,   734,   734,   734,   735,   736,   736,   736,   736,
     736,   737,   738,   738,   739,   740,   740,   740,   741,   742,
     742,   742,   742,   743,   744,   744,   744,   744,   745,   745,
     745,   745,   746,   747,   747,   747,   747,   747,   747,   747,
     747,   747,   747,   748,   748,   748,   748,   748,   748,   749,
     749,   749,   749,   749,   750,   750,   750,   750,   750,   750,
     750,   750,   750,   750,   750,   750,   751,   751,   752,   753,
     753,   754,   755,   756,   757,   757,   757,   758,   758,   758,
     758,   758,   758,   758,   758,   758,   758,   758,   758,   758,
     758,   758,   758,   758,   758,   759,   759,   759,   760,   760,
     760,   760,   761,   761,   761,   761,   761,   762,   762,   762,
     762,   763,   763,   763,   763,   763,   763,   763,   763,   763,
     763,   763,   763,   764,   764,   765,   765,   765,   765,   766,
     767,   767,   768,   768,   768,   768,   768,   768,   768,   768,
     769,   770,   770,   771,   772,   772,   772,   772,   773,   774,
     775,   776,   777,   778,   778,   778,   778,   779,   780,   780,
     780,   780,   780,   780,   781,   782,   782,   783,   784,   784,
     784,   784,   784,   785,   786,   786,   786,   786,   786
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     5,
       5,     3,     2,     1,     1,     2,     2,     1,     2,     2,
       2,     2,     2,     2,     3,     3,     2,     2,     3,     3,
       3,     2,     2,     6,     2,     6,     3,     2,     6,     6,
       3,     6,     3,     5,     7,     5,     7,     8,     8,     8,
       5,     7,     5,     7,     5,     7,     3,     2,     6,     2,
       6,     6,     6,     3,     6,     3,     5,     5,     8,     8,
       8,     5,     5,     5,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     3,     2,
       2,     6,     3,     3,     5,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     3,     2,     2,     3,     3,     2,
       3,     3,     2,     3,     3,     2,     3,     3,     2,     3,
       3,     2,     3,     3,     2,     2,     2,     2,     2,     2,
       4,     5,     2,     2,     1,     2,     2,     3,     3,     2,
       3,     3,     2,     2,     2,     2,     3,     2,     2,     3,
       2,     1,     2,     1,     3,     0,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     2,
       1,     0,     2,     1,     0,     2,     2,     3,     8,     8,
       8,     8,     9,     9,    10,    10,    10,     9,     9,     9,
       0,     0,     2,     2,     3,     3,     3,     3,     3,     0,
       2,     3,     1,     3,     1,     3,     0,     0,     2,     2,
       5,     4,     4,     4,     4,     3,     4,     2,     3,     3,
       1,     1,     3,     1,     1,     1,     1,     1,     0,     2,
       2,     2,     2,     2,     0,     2,     2,     4,     7,     8,
       6,     7,     7,     4,     3,     4,     3,     3,     3,     2,
       1,     1,     0,     0,     2,     2,     5,     5,     3,     4,
       3,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     3,     0,     0,     2,     2,     2,     2,     0,     2,
       2,     2,     2,     0,     2,     2,     2,     2,     0,     2,
       2,     2,     2,     0,     2,     2,     2,     2,     0,     2,
       2,     2,     2,     0,     2,     2,     2,     2,     0,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     7,     2,
       1,     1,     1,     1,     1,     3,     3,     1,     2,     2,
       2,     3,     0,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     2,     2,     1,     2,
       1,     1,     2,     3,     2,     3,     1,     2,     3,     1,
       2,     3,     1,     2,     3,     1,     2,     2,     2,     1,
       2,     2,     2,     2,     2,     0,     1,     1,     2,     1,
       1,     2,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     1,     1,
       2,     2,     2,     2,     1,     1,     2,     1,     1,     1,
       1,     5,     1,     1,     3,     3,     1,     1,     3,     3,
       5,     4,     5,     1,     2,     1,     3,     1,     2,     2,
       2,     1,     2,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     1,     3,     3,     1,     2,     1,     3,     1,
       1,     1,     6,     6,     4,     1,     1,     0,     1,     1,
       0,     3,     6,     4,     1,     1,     0,     0,     3,     3,
       0,     2,     2,     3,     2,     2,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     0,     6,     3,     6,     3,
       5,     3,     5,     2,     1,     1,     3,     4,     4,     5,
       6,     5,     1,     2,     1,     3,     1,     2,     2,     2,
       1,     1,     6,     8,     0,     0,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     3,     1,     1,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     2,     3,     3,     4,
       5,     2,     3,     2,     6,     4,     3,     4,     3,     2,
       1,     1,     3,     4,     1,     2,     1,     1,     2,     3,
       1,     3,     4,     3,     5,     3,     6,     1,     3,     1,
       1,     1,     2,     4,     6,     6,     1,     2,     1,     1,
       2,     2,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     2,     1,     4,
       5,     6,     1,     1,     1,     7,     8,     6,     1,     1,
       1,     2,     2,     6,     8,     1,     2,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     4,     1,
       1,     2,     1,     1,     1,     1,     1,     3,     1,     4,
       4,     0,     2,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     3,     3,     1,     1,     3,
       1,     1,     1,     3,     1,     3,     3,     3,     3,     5,
       1,     2,     1,     1,     2,     1,     1,     2,     1,     1,
       2,     2,     2,     1,     1,     2,     1,     2,     2,     6,
       6,     6,     4,     5,     2,     2,     1,     1,     1,     1,
       1,     1,     2,     2,     4,     0,     4,     0,     1,     0,
       1,     1,     1,     1,     1,     1,     2,     2,     6,     3,
       1,     3,     3,     3,     7,     3,     3,     3,     3,     3,
       3,     0,     4,     4,     0,     2,     2,     4,     4,     5,
       5,     3,     3,     3,     3,     1,     1,     1,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     1,
       3,     3,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     1,     2,     2,
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
       2,     1,     1,     1,     7,     1,     1,     2,     1,     3,
       1,     1,     2,     3,     1,     1,     1,     1,     2,     3,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       5,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     2,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     3,     1,     1,     3,     1,     1,     1,     3,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     2,     3,
       3,     9,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     2,     1,     1,     1,
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
#line 320 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5816 "parser_bison.c"
        break;

    case YYSYMBOL_QUOTED_STRING: /* "quoted string"  */
#line 320 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5822 "parser_bison.c"
        break;

    case YYSYMBOL_ASTERISK_STRING: /* "string with a trailing asterisk"  */
#line 320 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5828 "parser_bison.c"
        break;

    case YYSYMBOL_line: /* line  */
#line 630 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5834 "parser_bison.c"
        break;

    case YYSYMBOL_base_cmd: /* base_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5840 "parser_bison.c"
        break;

    case YYSYMBOL_add_cmd: /* add_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5846 "parser_bison.c"
        break;

    case YYSYMBOL_replace_cmd: /* replace_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5852 "parser_bison.c"
        break;

    case YYSYMBOL_create_cmd: /* create_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5858 "parser_bison.c"
        break;

    case YYSYMBOL_insert_cmd: /* insert_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5864 "parser_bison.c"
        break;

    case YYSYMBOL_table_or_id_spec: /* table_or_id_spec  */
#line 636 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5870 "parser_bison.c"
        break;

    case YYSYMBOL_chain_or_id_spec: /* chain_or_id_spec  */
#line 638 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5876 "parser_bison.c"
        break;

    case YYSYMBOL_set_or_id_spec: /* set_or_id_spec  */
#line 643 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5882 "parser_bison.c"
        break;

    case YYSYMBOL_obj_or_id_spec: /* obj_or_id_spec  */
#line 645 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5888 "parser_bison.c"
        break;

    case YYSYMBOL_delete_cmd: /* delete_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5894 "parser_bison.c"
        break;

    case YYSYMBOL_get_cmd: /* get_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5900 "parser_bison.c"
        break;

    case YYSYMBOL_list_cmd: /* list_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5906 "parser_bison.c"
        break;

    case YYSYMBOL_basehook_device_name: /* basehook_device_name  */
#line 657 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5912 "parser_bison.c"
        break;

    case YYSYMBOL_basehook_spec: /* basehook_spec  */
#line 651 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 5918 "parser_bison.c"
        break;

    case YYSYMBOL_reset_cmd: /* reset_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5924 "parser_bison.c"
        break;

    case YYSYMBOL_flush_cmd: /* flush_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5930 "parser_bison.c"
        break;

    case YYSYMBOL_rename_cmd: /* rename_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5936 "parser_bison.c"
        break;

    case YYSYMBOL_import_cmd: /* import_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5942 "parser_bison.c"
        break;

    case YYSYMBOL_export_cmd: /* export_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5948 "parser_bison.c"
        break;

    case YYSYMBOL_monitor_cmd: /* monitor_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5954 "parser_bison.c"
        break;

    case YYSYMBOL_monitor_event: /* monitor_event  */
#line 876 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 5960 "parser_bison.c"
        break;

    case YYSYMBOL_describe_cmd: /* describe_cmd  */
#line 633 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 5966 "parser_bison.c"
        break;

    case YYSYMBOL_table_block_alloc: /* table_block_alloc  */
#line 663 "parser_bison.y"
            { close_scope(state); table_free(((*yyvaluep).table)); }
#line 5972 "parser_bison.c"
        break;

    case YYSYMBOL_chain_block_alloc: /* chain_block_alloc  */
#line 665 "parser_bison.y"
            { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 5978 "parser_bison.c"
        break;

    case YYSYMBOL_typeof_data_expr: /* typeof_data_expr  */
#line 737 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5984 "parser_bison.c"
        break;

    case YYSYMBOL_typeof_expr: /* typeof_expr  */
#line 737 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 5990 "parser_bison.c"
        break;

    case YYSYMBOL_set_block_alloc: /* set_block_alloc  */
#line 674 "parser_bison.y"
            { set_free(((*yyvaluep).set)); }
#line 5996 "parser_bison.c"
        break;

    case YYSYMBOL_set_block_expr: /* set_block_expr  */
#line 778 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6002 "parser_bison.c"
        break;

    case YYSYMBOL_map_block_alloc: /* map_block_alloc  */
#line 677 "parser_bison.y"
            { set_free(((*yyvaluep).set)); }
#line 6008 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_block_alloc: /* flowtable_block_alloc  */
#line 681 "parser_bison.y"
            { flowtable_free(((*yyvaluep).flowtable)); }
#line 6014 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_expr: /* flowtable_expr  */
#line 778 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6020 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_list_expr: /* flowtable_list_expr  */
#line 778 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6026 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_expr_member: /* flowtable_expr_member  */
#line 778 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6032 "parser_bison.c"
        break;

    case YYSYMBOL_data_type_atom_expr: /* data_type_atom_expr  */
#line 627 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6038 "parser_bison.c"
        break;

    case YYSYMBOL_data_type_expr: /* data_type_expr  */
#line 627 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6044 "parser_bison.c"
        break;

    case YYSYMBOL_obj_block_alloc: /* obj_block_alloc  */
#line 684 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6050 "parser_bison.c"
        break;

    case YYSYMBOL_type_identifier: /* type_identifier  */
#line 622 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6056 "parser_bison.c"
        break;

    case YYSYMBOL_extended_prio_name: /* extended_prio_name  */
#line 657 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6062 "parser_bison.c"
        break;

    case YYSYMBOL_dev_spec: /* dev_spec  */
#line 660 "parser_bison.y"
            { xfree(((*yyvaluep).expr)); }
#line 6068 "parser_bison.c"
        break;

    case YYSYMBOL_policy_expr: /* policy_expr  */
#line 735 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6074 "parser_bison.c"
        break;

    case YYSYMBOL_identifier: /* identifier  */
#line 622 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6080 "parser_bison.c"
        break;

    case YYSYMBOL_string: /* string  */
#line 622 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6086 "parser_bison.c"
        break;

    case YYSYMBOL_table_spec: /* table_spec  */
#line 636 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6092 "parser_bison.c"
        break;

    case YYSYMBOL_tableid_spec: /* tableid_spec  */
#line 636 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6098 "parser_bison.c"
        break;

    case YYSYMBOL_chain_spec: /* chain_spec  */
#line 638 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6104 "parser_bison.c"
        break;

    case YYSYMBOL_chainid_spec: /* chainid_spec  */
#line 638 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6110 "parser_bison.c"
        break;

    case YYSYMBOL_chain_identifier: /* chain_identifier  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6116 "parser_bison.c"
        break;

    case YYSYMBOL_set_spec: /* set_spec  */
#line 643 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6122 "parser_bison.c"
        break;

    case YYSYMBOL_setid_spec: /* setid_spec  */
#line 643 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6128 "parser_bison.c"
        break;

    case YYSYMBOL_set_identifier: /* set_identifier  */
#line 648 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6134 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_spec: /* flowtable_spec  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6140 "parser_bison.c"
        break;

    case YYSYMBOL_flowtableid_spec: /* flowtableid_spec  */
#line 648 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6146 "parser_bison.c"
        break;

    case YYSYMBOL_obj_spec: /* obj_spec  */
#line 645 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6152 "parser_bison.c"
        break;

    case YYSYMBOL_objid_spec: /* objid_spec  */
#line 645 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6158 "parser_bison.c"
        break;

    case YYSYMBOL_obj_identifier: /* obj_identifier  */
#line 648 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6164 "parser_bison.c"
        break;

    case YYSYMBOL_handle_spec: /* handle_spec  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6170 "parser_bison.c"
        break;

    case YYSYMBOL_position_spec: /* position_spec  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6176 "parser_bison.c"
        break;

    case YYSYMBOL_index_spec: /* index_spec  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6182 "parser_bison.c"
        break;

    case YYSYMBOL_rule_position: /* rule_position  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6188 "parser_bison.c"
        break;

    case YYSYMBOL_ruleid_spec: /* ruleid_spec  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6194 "parser_bison.c"
        break;

    case YYSYMBOL_comment_spec: /* comment_spec  */
#line 622 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6200 "parser_bison.c"
        break;

    case YYSYMBOL_ruleset_spec: /* ruleset_spec  */
#line 641 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6206 "parser_bison.c"
        break;

    case YYSYMBOL_rule: /* rule  */
#line 667 "parser_bison.y"
            { rule_free(((*yyvaluep).rule)); }
#line 6212 "parser_bison.c"
        break;

    case YYSYMBOL_stmt_list: /* stmt_list  */
#line 687 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6218 "parser_bison.c"
        break;

    case YYSYMBOL_stateful_stmt_list: /* stateful_stmt_list  */
#line 687 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6224 "parser_bison.c"
        break;

    case YYSYMBOL_stateful_stmt: /* stateful_stmt  */
#line 691 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6230 "parser_bison.c"
        break;

    case YYSYMBOL_stmt: /* stmt  */
#line 689 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6236 "parser_bison.c"
        break;

    case YYSYMBOL_chain_stmt: /* chain_stmt  */
#line 714 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6242 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_stmt: /* verdict_stmt  */
#line 689 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6248 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_stmt: /* verdict_map_stmt  */
#line 772 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6254 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_expr: /* verdict_map_expr  */
#line 775 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6260 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_list_expr: /* verdict_map_list_expr  */
#line 775 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6266 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_list_member_expr: /* verdict_map_list_member_expr  */
#line 775 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6272 "parser_bison.c"
        break;

    case YYSYMBOL_connlimit_stmt: /* connlimit_stmt  */
#line 702 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6278 "parser_bison.c"
        break;

    case YYSYMBOL_counter_stmt: /* counter_stmt  */
#line 691 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6284 "parser_bison.c"
        break;

    case YYSYMBOL_counter_stmt_alloc: /* counter_stmt_alloc  */
#line 691 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6290 "parser_bison.c"
        break;

    case YYSYMBOL_log_stmt: /* log_stmt  */
#line 699 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6296 "parser_bison.c"
        break;

    case YYSYMBOL_log_stmt_alloc: /* log_stmt_alloc  */
#line 699 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6302 "parser_bison.c"
        break;

    case YYSYMBOL_limit_stmt: /* limit_stmt  */
#line 702 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6308 "parser_bison.c"
        break;

    case YYSYMBOL_quota_unit: /* quota_unit  */
#line 657 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6314 "parser_bison.c"
        break;

    case YYSYMBOL_quota_stmt: /* quota_stmt  */
#line 702 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6320 "parser_bison.c"
        break;

    case YYSYMBOL_reject_stmt: /* reject_stmt  */
#line 705 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6326 "parser_bison.c"
        break;

    case YYSYMBOL_reject_stmt_alloc: /* reject_stmt_alloc  */
#line 705 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6332 "parser_bison.c"
        break;

    case YYSYMBOL_reject_with_expr: /* reject_with_expr  */
#line 720 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6338 "parser_bison.c"
        break;

    case YYSYMBOL_nat_stmt: /* nat_stmt  */
#line 707 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6344 "parser_bison.c"
        break;

    case YYSYMBOL_nat_stmt_alloc: /* nat_stmt_alloc  */
#line 707 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6350 "parser_bison.c"
        break;

    case YYSYMBOL_tproxy_stmt: /* tproxy_stmt  */
#line 710 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6356 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_stmt: /* synproxy_stmt  */
#line 712 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6362 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_stmt_alloc: /* synproxy_stmt_alloc  */
#line 712 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6368 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_obj: /* synproxy_obj  */
#line 798 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6374 "parser_bison.c"
        break;

    case YYSYMBOL_primary_stmt_expr: /* primary_stmt_expr  */
#line 759 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6380 "parser_bison.c"
        break;

    case YYSYMBOL_shift_stmt_expr: /* shift_stmt_expr  */
#line 761 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6386 "parser_bison.c"
        break;

    case YYSYMBOL_and_stmt_expr: /* and_stmt_expr  */
#line 763 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6392 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_stmt_expr: /* exclusive_or_stmt_expr  */
#line 763 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6398 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_stmt_expr: /* inclusive_or_stmt_expr  */
#line 763 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6404 "parser_bison.c"
        break;

    case YYSYMBOL_basic_stmt_expr: /* basic_stmt_expr  */
#line 759 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6410 "parser_bison.c"
        break;

    case YYSYMBOL_concat_stmt_expr: /* concat_stmt_expr  */
#line 751 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6416 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt_expr_set: /* map_stmt_expr_set  */
#line 751 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6422 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt_expr: /* map_stmt_expr  */
#line 751 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6428 "parser_bison.c"
        break;

    case YYSYMBOL_prefix_stmt_expr: /* prefix_stmt_expr  */
#line 756 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6434 "parser_bison.c"
        break;

    case YYSYMBOL_range_stmt_expr: /* range_stmt_expr  */
#line 756 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6440 "parser_bison.c"
        break;

    case YYSYMBOL_multiton_stmt_expr: /* multiton_stmt_expr  */
#line 754 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6446 "parser_bison.c"
        break;

    case YYSYMBOL_stmt_expr: /* stmt_expr  */
#line 751 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6452 "parser_bison.c"
        break;

    case YYSYMBOL_masq_stmt: /* masq_stmt  */
#line 707 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6458 "parser_bison.c"
        break;

    case YYSYMBOL_masq_stmt_alloc: /* masq_stmt_alloc  */
#line 707 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6464 "parser_bison.c"
        break;

    case YYSYMBOL_redir_stmt: /* redir_stmt  */
#line 707 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6470 "parser_bison.c"
        break;

    case YYSYMBOL_redir_stmt_alloc: /* redir_stmt_alloc  */
#line 707 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6476 "parser_bison.c"
        break;

    case YYSYMBOL_dup_stmt: /* dup_stmt  */
#line 723 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6482 "parser_bison.c"
        break;

    case YYSYMBOL_fwd_stmt: /* fwd_stmt  */
#line 725 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6488 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt: /* queue_stmt  */
#line 718 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6494 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_compat: /* queue_stmt_compat  */
#line 718 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6500 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_alloc: /* queue_stmt_alloc  */
#line 718 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6506 "parser_bison.c"
        break;

    case YYSYMBOL_queue_expr: /* queue_expr  */
#line 720 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6512 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_expr_simple: /* queue_stmt_expr_simple  */
#line 720 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6518 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_expr: /* queue_stmt_expr  */
#line 720 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6524 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_stmt: /* set_elem_expr_stmt  */
#line 782 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6530 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_stmt_alloc: /* set_elem_expr_stmt_alloc  */
#line 782 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6536 "parser_bison.c"
        break;

    case YYSYMBOL_set_stmt: /* set_stmt  */
#line 727 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6542 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt: /* map_stmt  */
#line 730 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6548 "parser_bison.c"
        break;

    case YYSYMBOL_meter_stmt: /* meter_stmt  */
#line 732 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6554 "parser_bison.c"
        break;

    case YYSYMBOL_flow_stmt_legacy_alloc: /* flow_stmt_legacy_alloc  */
#line 732 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6560 "parser_bison.c"
        break;

    case YYSYMBOL_meter_stmt_alloc: /* meter_stmt_alloc  */
#line 732 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6566 "parser_bison.c"
        break;

    case YYSYMBOL_match_stmt: /* match_stmt  */
#line 689 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6572 "parser_bison.c"
        break;

    case YYSYMBOL_variable_expr: /* variable_expr  */
#line 735 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6578 "parser_bison.c"
        break;

    case YYSYMBOL_symbol_expr: /* symbol_expr  */
#line 735 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6584 "parser_bison.c"
        break;

    case YYSYMBOL_set_ref_expr: /* set_ref_expr  */
#line 743 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6590 "parser_bison.c"
        break;

    case YYSYMBOL_set_ref_symbol_expr: /* set_ref_symbol_expr  */
#line 743 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6596 "parser_bison.c"
        break;

    case YYSYMBOL_integer_expr: /* integer_expr  */
#line 735 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6602 "parser_bison.c"
        break;

    case YYSYMBOL_primary_expr: /* primary_expr  */
#line 737 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6608 "parser_bison.c"
        break;

    case YYSYMBOL_fib_expr: /* fib_expr  */
#line 867 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6614 "parser_bison.c"
        break;

    case YYSYMBOL_osf_expr: /* osf_expr  */
#line 872 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6620 "parser_bison.c"
        break;

    case YYSYMBOL_shift_expr: /* shift_expr  */
#line 737 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6626 "parser_bison.c"
        break;

    case YYSYMBOL_and_expr: /* and_expr  */
#line 737 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6632 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_expr: /* exclusive_or_expr  */
#line 739 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6638 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_expr: /* inclusive_or_expr  */
#line 739 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6644 "parser_bison.c"
        break;

    case YYSYMBOL_basic_expr: /* basic_expr  */
#line 741 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6650 "parser_bison.c"
        break;

    case YYSYMBOL_concat_expr: /* concat_expr  */
#line 766 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6656 "parser_bison.c"
        break;

    case YYSYMBOL_prefix_rhs_expr: /* prefix_rhs_expr  */
#line 748 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6662 "parser_bison.c"
        break;

    case YYSYMBOL_range_rhs_expr: /* range_rhs_expr  */
#line 748 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6668 "parser_bison.c"
        break;

    case YYSYMBOL_multiton_rhs_expr: /* multiton_rhs_expr  */
#line 746 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6674 "parser_bison.c"
        break;

    case YYSYMBOL_map_expr: /* map_expr  */
#line 769 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6680 "parser_bison.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 788 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6686 "parser_bison.c"
        break;

    case YYSYMBOL_set_expr: /* set_expr  */
#line 778 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6692 "parser_bison.c"
        break;

    case YYSYMBOL_set_list_expr: /* set_list_expr  */
#line 778 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6698 "parser_bison.c"
        break;

    case YYSYMBOL_set_list_member_expr: /* set_list_member_expr  */
#line 778 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6704 "parser_bison.c"
        break;

    case YYSYMBOL_meter_key_expr: /* meter_key_expr  */
#line 785 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6710 "parser_bison.c"
        break;

    case YYSYMBOL_meter_key_expr_alloc: /* meter_key_expr_alloc  */
#line 785 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6716 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr: /* set_elem_expr  */
#line 780 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6722 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_key_expr: /* set_elem_key_expr  */
#line 910 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6728 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_alloc: /* set_elem_expr_alloc  */
#line 780 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6734 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_stmt_list: /* set_elem_stmt_list  */
#line 687 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6740 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_stmt: /* set_elem_stmt  */
#line 689 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6746 "parser_bison.c"
        break;

    case YYSYMBOL_set_lhs_expr: /* set_lhs_expr  */
#line 780 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6752 "parser_bison.c"
        break;

    case YYSYMBOL_set_rhs_expr: /* set_rhs_expr  */
#line 780 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6758 "parser_bison.c"
        break;

    case YYSYMBOL_initializer_expr: /* initializer_expr  */
#line 788 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6764 "parser_bison.c"
        break;

    case YYSYMBOL_counter_obj: /* counter_obj  */
#line 798 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6770 "parser_bison.c"
        break;

    case YYSYMBOL_quota_obj: /* quota_obj  */
#line 798 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6776 "parser_bison.c"
        break;

    case YYSYMBOL_secmark_obj: /* secmark_obj  */
#line 798 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6782 "parser_bison.c"
        break;

    case YYSYMBOL_timeout_states: /* timeout_states  */
#line 903 "parser_bison.y"
            { xfree(((*yyvaluep).list)); }
#line 6788 "parser_bison.c"
        break;

    case YYSYMBOL_timeout_state: /* timeout_state  */
#line 903 "parser_bison.y"
            { xfree(((*yyvaluep).list)); }
#line 6794 "parser_bison.c"
        break;

    case YYSYMBOL_ct_obj_alloc: /* ct_obj_alloc  */
#line 798 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6800 "parser_bison.c"
        break;

    case YYSYMBOL_limit_obj: /* limit_obj  */
#line 798 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6806 "parser_bison.c"
        break;

    case YYSYMBOL_relational_expr: /* relational_expr  */
#line 801 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6812 "parser_bison.c"
        break;

    case YYSYMBOL_list_rhs_expr: /* list_rhs_expr  */
#line 793 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6818 "parser_bison.c"
        break;

    case YYSYMBOL_rhs_expr: /* rhs_expr  */
#line 791 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6824 "parser_bison.c"
        break;

    case YYSYMBOL_shift_rhs_expr: /* shift_rhs_expr  */
#line 793 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6830 "parser_bison.c"
        break;

    case YYSYMBOL_and_rhs_expr: /* and_rhs_expr  */
#line 795 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6836 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_rhs_expr: /* exclusive_or_rhs_expr  */
#line 795 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6842 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_rhs_expr: /* inclusive_or_rhs_expr  */
#line 795 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6848 "parser_bison.c"
        break;

    case YYSYMBOL_basic_rhs_expr: /* basic_rhs_expr  */
#line 791 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6854 "parser_bison.c"
        break;

    case YYSYMBOL_concat_rhs_expr: /* concat_rhs_expr  */
#line 791 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6860 "parser_bison.c"
        break;

    case YYSYMBOL_boolean_expr: /* boolean_expr  */
#line 893 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6866 "parser_bison.c"
        break;

    case YYSYMBOL_keyword_expr: /* keyword_expr  */
#line 788 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6872 "parser_bison.c"
        break;

    case YYSYMBOL_primary_rhs_expr: /* primary_rhs_expr  */
#line 793 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6878 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_expr: /* verdict_expr  */
#line 735 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6884 "parser_bison.c"
        break;

    case YYSYMBOL_chain_expr: /* chain_expr  */
#line 735 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6890 "parser_bison.c"
        break;

    case YYSYMBOL_meta_expr: /* meta_expr  */
#line 849 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6896 "parser_bison.c"
        break;

    case YYSYMBOL_meta_stmt: /* meta_stmt  */
#line 697 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6902 "parser_bison.c"
        break;

    case YYSYMBOL_socket_expr: /* socket_expr  */
#line 853 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6908 "parser_bison.c"
        break;

    case YYSYMBOL_numgen_expr: /* numgen_expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6914 "parser_bison.c"
        break;

    case YYSYMBOL_xfrm_expr: /* xfrm_expr  */
#line 907 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6920 "parser_bison.c"
        break;

    case YYSYMBOL_hash_expr: /* hash_expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6926 "parser_bison.c"
        break;

    case YYSYMBOL_rt_expr: /* rt_expr  */
#line 859 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6932 "parser_bison.c"
        break;

    case YYSYMBOL_ct_expr: /* ct_expr  */
#line 863 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6938 "parser_bison.c"
        break;

    case YYSYMBOL_symbol_stmt_expr: /* symbol_stmt_expr  */
#line 793 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6944 "parser_bison.c"
        break;

    case YYSYMBOL_list_stmt_expr: /* list_stmt_expr  */
#line 761 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6950 "parser_bison.c"
        break;

    case YYSYMBOL_ct_stmt: /* ct_stmt  */
#line 695 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6956 "parser_bison.c"
        break;

    case YYSYMBOL_payload_stmt: /* payload_stmt  */
#line 693 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6962 "parser_bison.c"
        break;

    case YYSYMBOL_payload_expr: /* payload_expr  */
#line 805 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6968 "parser_bison.c"
        break;

    case YYSYMBOL_payload_raw_expr: /* payload_raw_expr  */
#line 805 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6974 "parser_bison.c"
        break;

    case YYSYMBOL_eth_hdr_expr: /* eth_hdr_expr  */
#line 808 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6980 "parser_bison.c"
        break;

    case YYSYMBOL_vlan_hdr_expr: /* vlan_hdr_expr  */
#line 808 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6986 "parser_bison.c"
        break;

    case YYSYMBOL_arp_hdr_expr: /* arp_hdr_expr  */
#line 811 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6992 "parser_bison.c"
        break;

    case YYSYMBOL_ip_hdr_expr: /* ip_hdr_expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6998 "parser_bison.c"
        break;

    case YYSYMBOL_icmp_hdr_expr: /* icmp_hdr_expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7004 "parser_bison.c"
        break;

    case YYSYMBOL_igmp_hdr_expr: /* igmp_hdr_expr  */
#line 814 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7010 "parser_bison.c"
        break;

    case YYSYMBOL_ip6_hdr_expr: /* ip6_hdr_expr  */
#line 818 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7016 "parser_bison.c"
        break;

    case YYSYMBOL_icmp6_hdr_expr: /* icmp6_hdr_expr  */
#line 818 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7022 "parser_bison.c"
        break;

    case YYSYMBOL_auth_hdr_expr: /* auth_hdr_expr  */
#line 821 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7028 "parser_bison.c"
        break;

    case YYSYMBOL_esp_hdr_expr: /* esp_hdr_expr  */
#line 821 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7034 "parser_bison.c"
        break;

    case YYSYMBOL_comp_hdr_expr: /* comp_hdr_expr  */
#line 821 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7040 "parser_bison.c"
        break;

    case YYSYMBOL_udp_hdr_expr: /* udp_hdr_expr  */
#line 824 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7046 "parser_bison.c"
        break;

    case YYSYMBOL_udplite_hdr_expr: /* udplite_hdr_expr  */
#line 824 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7052 "parser_bison.c"
        break;

    case YYSYMBOL_tcp_hdr_expr: /* tcp_hdr_expr  */
#line 882 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7058 "parser_bison.c"
        break;

    case YYSYMBOL_optstrip_stmt: /* optstrip_stmt  */
#line 890 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7064 "parser_bison.c"
        break;

    case YYSYMBOL_dccp_hdr_expr: /* dccp_hdr_expr  */
#line 827 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7070 "parser_bison.c"
        break;

    case YYSYMBOL_sctp_chunk_alloc: /* sctp_chunk_alloc  */
#line 827 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7076 "parser_bison.c"
        break;

    case YYSYMBOL_sctp_hdr_expr: /* sctp_hdr_expr  */
#line 827 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7082 "parser_bison.c"
        break;

    case YYSYMBOL_th_hdr_expr: /* th_hdr_expr  */
#line 833 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7088 "parser_bison.c"
        break;

    case YYSYMBOL_exthdr_expr: /* exthdr_expr  */
#line 837 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7094 "parser_bison.c"
        break;

    case YYSYMBOL_hbh_hdr_expr: /* hbh_hdr_expr  */
#line 839 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7100 "parser_bison.c"
        break;

    case YYSYMBOL_rt_hdr_expr: /* rt_hdr_expr  */
#line 842 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7106 "parser_bison.c"
        break;

    case YYSYMBOL_rt0_hdr_expr: /* rt0_hdr_expr  */
#line 842 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7112 "parser_bison.c"
        break;

    case YYSYMBOL_rt2_hdr_expr: /* rt2_hdr_expr  */
#line 842 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7118 "parser_bison.c"
        break;

    case YYSYMBOL_rt4_hdr_expr: /* rt4_hdr_expr  */
#line 842 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7124 "parser_bison.c"
        break;

    case YYSYMBOL_frag_hdr_expr: /* frag_hdr_expr  */
#line 839 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7130 "parser_bison.c"
        break;

    case YYSYMBOL_dst_hdr_expr: /* dst_hdr_expr  */
#line 839 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7136 "parser_bison.c"
        break;

    case YYSYMBOL_mh_hdr_expr: /* mh_hdr_expr  */
#line 845 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7142 "parser_bison.c"
        break;

    case YYSYMBOL_exthdr_exists_expr: /* exthdr_exists_expr  */
#line 897 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7148 "parser_bison.c"
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

#line 7253 "parser_bison.c"

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
#line 916 "parser_bison.y"
                        {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 7470 "parser_bison.c"
    break;

  case 8: /* close_scope_ah: %empty  */
#line 932 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_AH); }
#line 7476 "parser_bison.c"
    break;

  case 9: /* close_scope_arp: %empty  */
#line 933 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ARP); }
#line 7482 "parser_bison.c"
    break;

  case 10: /* close_scope_at: %empty  */
#line 934 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_AT); }
#line 7488 "parser_bison.c"
    break;

  case 11: /* close_scope_comp: %empty  */
#line 935 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_COMP); }
#line 7494 "parser_bison.c"
    break;

  case 12: /* close_scope_ct: %empty  */
#line 936 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CT); }
#line 7500 "parser_bison.c"
    break;

  case 13: /* close_scope_counter: %empty  */
#line 937 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_COUNTER); }
#line 7506 "parser_bison.c"
    break;

  case 14: /* close_scope_dccp: %empty  */
#line 938 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_DCCP); }
#line 7512 "parser_bison.c"
    break;

  case 15: /* close_scope_dst: %empty  */
#line 939 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_DST); }
#line 7518 "parser_bison.c"
    break;

  case 16: /* close_scope_dup: %empty  */
#line 940 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_DUP); }
#line 7524 "parser_bison.c"
    break;

  case 17: /* close_scope_esp: %empty  */
#line 941 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_ESP); }
#line 7530 "parser_bison.c"
    break;

  case 18: /* close_scope_eth: %empty  */
#line 942 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ETH); }
#line 7536 "parser_bison.c"
    break;

  case 19: /* close_scope_export: %empty  */
#line 943 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_EXPORT); }
#line 7542 "parser_bison.c"
    break;

  case 20: /* close_scope_fib: %empty  */
#line 944 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FIB); }
#line 7548 "parser_bison.c"
    break;

  case 21: /* close_scope_frag: %empty  */
#line 945 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FRAG); }
#line 7554 "parser_bison.c"
    break;

  case 22: /* close_scope_fwd: %empty  */
#line 946 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_FWD); }
#line 7560 "parser_bison.c"
    break;

  case 23: /* close_scope_hash: %empty  */
#line 947 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HASH); }
#line 7566 "parser_bison.c"
    break;

  case 24: /* close_scope_hbh: %empty  */
#line 948 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HBH); }
#line 7572 "parser_bison.c"
    break;

  case 25: /* close_scope_ip: %empty  */
#line 949 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP); }
#line 7578 "parser_bison.c"
    break;

  case 26: /* close_scope_ip6: %empty  */
#line 950 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP6); }
#line 7584 "parser_bison.c"
    break;

  case 27: /* close_scope_vlan: %empty  */
#line 951 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_VLAN); }
#line 7590 "parser_bison.c"
    break;

  case 28: /* close_scope_icmp: %empty  */
#line 952 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ICMP); }
#line 7596 "parser_bison.c"
    break;

  case 29: /* close_scope_igmp: %empty  */
#line 953 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IGMP); }
#line 7602 "parser_bison.c"
    break;

  case 30: /* close_scope_import: %empty  */
#line 954 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_IMPORT); }
#line 7608 "parser_bison.c"
    break;

  case 31: /* close_scope_ipsec: %empty  */
#line 955 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_IPSEC); }
#line 7614 "parser_bison.c"
    break;

  case 32: /* close_scope_list: %empty  */
#line 956 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_LIST); }
#line 7620 "parser_bison.c"
    break;

  case 33: /* close_scope_limit: %empty  */
#line 957 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_LIMIT); }
#line 7626 "parser_bison.c"
    break;

  case 34: /* close_scope_meta: %empty  */
#line 958 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_META); }
#line 7632 "parser_bison.c"
    break;

  case 35: /* close_scope_mh: %empty  */
#line 959 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_MH); }
#line 7638 "parser_bison.c"
    break;

  case 36: /* close_scope_monitor: %empty  */
#line 960 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_MONITOR); }
#line 7644 "parser_bison.c"
    break;

  case 37: /* close_scope_nat: %empty  */
#line 961 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_NAT); }
#line 7650 "parser_bison.c"
    break;

  case 38: /* close_scope_numgen: %empty  */
#line 962 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_NUMGEN); }
#line 7656 "parser_bison.c"
    break;

  case 39: /* close_scope_osf: %empty  */
#line 963 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_OSF); }
#line 7662 "parser_bison.c"
    break;

  case 40: /* close_scope_policy: %empty  */
#line 964 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_POLICY); }
#line 7668 "parser_bison.c"
    break;

  case 41: /* close_scope_quota: %empty  */
#line 965 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_QUOTA); }
#line 7674 "parser_bison.c"
    break;

  case 42: /* close_scope_queue: %empty  */
#line 966 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_QUEUE); }
#line 7680 "parser_bison.c"
    break;

  case 43: /* close_scope_reject: %empty  */
#line 967 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_REJECT); }
#line 7686 "parser_bison.c"
    break;

  case 44: /* close_scope_reset: %empty  */
#line 968 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_RESET); }
#line 7692 "parser_bison.c"
    break;

  case 45: /* close_scope_rt: %empty  */
#line 969 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_RT); }
#line 7698 "parser_bison.c"
    break;

  case 46: /* close_scope_sctp: %empty  */
#line 970 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_SCTP); }
#line 7704 "parser_bison.c"
    break;

  case 47: /* close_scope_sctp_chunk: %empty  */
#line 971 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SCTP_CHUNK); }
#line 7710 "parser_bison.c"
    break;

  case 48: /* close_scope_secmark: %empty  */
#line 972 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_SECMARK); }
#line 7716 "parser_bison.c"
    break;

  case 49: /* close_scope_socket: %empty  */
#line 973 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SOCKET); }
#line 7722 "parser_bison.c"
    break;

  case 50: /* close_scope_tcp: %empty  */
#line 974 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_TCP); }
#line 7728 "parser_bison.c"
    break;

  case 51: /* close_scope_tproxy: %empty  */
#line 975 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_TPROXY); }
#line 7734 "parser_bison.c"
    break;

  case 52: /* close_scope_type: %empty  */
#line 976 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_TYPE); }
#line 7740 "parser_bison.c"
    break;

  case 53: /* close_scope_th: %empty  */
#line 977 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_TH); }
#line 7746 "parser_bison.c"
    break;

  case 54: /* close_scope_udp: %empty  */
#line 978 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_UDP); }
#line 7752 "parser_bison.c"
    break;

  case 55: /* close_scope_udplite: %empty  */
#line 979 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_UDPLITE); }
#line 7758 "parser_bison.c"
    break;

  case 56: /* close_scope_log: %empty  */
#line 981 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_LOG); }
#line 7764 "parser_bison.c"
    break;

  case 57: /* close_scope_synproxy: %empty  */
#line 982 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_SYNPROXY); }
#line 7770 "parser_bison.c"
    break;

  case 58: /* common_block: "include" "quoted string" stmt_separator  */
#line 985 "parser_bison.y"
                        {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 7782 "parser_bison.c"
    break;

  case 59: /* common_block: "define" identifier '=' initializer_expr stmt_separator  */
#line 993 "parser_bison.y"
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
#line 7801 "parser_bison.c"
    break;

  case 60: /* common_block: "redefine" identifier '=' initializer_expr stmt_separator  */
#line 1008 "parser_bison.y"
                        {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 7812 "parser_bison.c"
    break;

  case 61: /* common_block: "undefine" identifier stmt_separator  */
#line 1015 "parser_bison.y"
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
#line 7828 "parser_bison.c"
    break;

  case 62: /* common_block: error stmt_separator  */
#line 1027 "parser_bison.y"
                        {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 7838 "parser_bison.c"
    break;

  case 63: /* line: common_block  */
#line 1034 "parser_bison.y"
                                                                { (yyval.cmd) = NULL; }
#line 7844 "parser_bison.c"
    break;

  case 64: /* line: stmt_separator  */
#line 1035 "parser_bison.y"
                                                                { (yyval.cmd) = NULL; }
#line 7850 "parser_bison.c"
    break;

  case 65: /* line: base_cmd stmt_separator  */
#line 1036 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 7856 "parser_bison.c"
    break;

  case 66: /* line: base_cmd "end of file"  */
#line 1038 "parser_bison.y"
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
#line 7878 "parser_bison.c"
    break;

  case 67: /* base_cmd: add_cmd  */
#line 1057 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7884 "parser_bison.c"
    break;

  case 68: /* base_cmd: "add" add_cmd  */
#line 1058 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7890 "parser_bison.c"
    break;

  case 69: /* base_cmd: "replace" replace_cmd  */
#line 1059 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7896 "parser_bison.c"
    break;

  case 70: /* base_cmd: "create" create_cmd  */
#line 1060 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7902 "parser_bison.c"
    break;

  case 71: /* base_cmd: "insert" insert_cmd  */
#line 1061 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7908 "parser_bison.c"
    break;

  case 72: /* base_cmd: "delete" delete_cmd  */
#line 1062 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7914 "parser_bison.c"
    break;

  case 73: /* base_cmd: "get" get_cmd  */
#line 1063 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7920 "parser_bison.c"
    break;

  case 74: /* base_cmd: "list" list_cmd close_scope_list  */
#line 1064 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 7926 "parser_bison.c"
    break;

  case 75: /* base_cmd: "reset" reset_cmd close_scope_reset  */
#line 1065 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 7932 "parser_bison.c"
    break;

  case 76: /* base_cmd: "flush" flush_cmd  */
#line 1066 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7938 "parser_bison.c"
    break;

  case 77: /* base_cmd: "rename" rename_cmd  */
#line 1067 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7944 "parser_bison.c"
    break;

  case 78: /* base_cmd: "import" import_cmd close_scope_import  */
#line 1068 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 7950 "parser_bison.c"
    break;

  case 79: /* base_cmd: "export" export_cmd close_scope_export  */
#line 1069 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 7956 "parser_bison.c"
    break;

  case 80: /* base_cmd: "monitor" monitor_cmd close_scope_monitor  */
#line 1070 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 7962 "parser_bison.c"
    break;

  case 81: /* base_cmd: "describe" describe_cmd  */
#line 1071 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 7968 "parser_bison.c"
    break;

  case 82: /* add_cmd: "table" table_spec  */
#line 1075 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7976 "parser_bison.c"
    break;

  case 83: /* add_cmd: "table" table_spec table_block_alloc '{' table_block '}'  */
#line 1080 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 7986 "parser_bison.c"
    break;

  case 84: /* add_cmd: "chain" chain_spec  */
#line 1086 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7994 "parser_bison.c"
    break;

  case 85: /* add_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1091 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 8005 "parser_bison.c"
    break;

  case 86: /* add_cmd: "rule" rule_position rule  */
#line 1098 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8013 "parser_bison.c"
    break;

  case 87: /* add_cmd: rule_position rule  */
#line 1102 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8021 "parser_bison.c"
    break;

  case 88: /* add_cmd: "set" set_spec set_block_alloc '{' set_block '}'  */
#line 1107 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8031 "parser_bison.c"
    break;

  case 89: /* add_cmd: "map" set_spec map_block_alloc '{' map_block '}'  */
#line 1114 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8041 "parser_bison.c"
    break;

  case 90: /* add_cmd: "element" set_spec set_block_expr  */
#line 1120 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8049 "parser_bison.c"
    break;

  case 91: /* add_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1125 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8059 "parser_bison.c"
    break;

  case 92: /* add_cmd: "counter" obj_spec close_scope_counter  */
#line 1131 "parser_bison.y"
                        {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 8072 "parser_bison.c"
    break;

  case 93: /* add_cmd: "counter" obj_spec counter_obj counter_config close_scope_counter  */
#line 1140 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8080 "parser_bison.c"
    break;

  case 94: /* add_cmd: "counter" obj_spec counter_obj '{' counter_block '}' close_scope_counter  */
#line 1144 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8088 "parser_bison.c"
    break;

  case 95: /* add_cmd: "quota" obj_spec quota_obj quota_config close_scope_quota  */
#line 1148 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8096 "parser_bison.c"
    break;

  case 96: /* add_cmd: "quota" obj_spec quota_obj '{' quota_block '}' close_scope_quota  */
#line 1152 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8104 "parser_bison.c"
    break;

  case 97: /* add_cmd: "ct" "helper" obj_spec ct_obj_alloc '{' ct_helper_block '}' close_scope_ct  */
#line 1156 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8112 "parser_bison.c"
    break;

  case 98: /* add_cmd: "ct" "timeout" obj_spec ct_obj_alloc '{' ct_timeout_block '}' close_scope_ct  */
#line 1160 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8120 "parser_bison.c"
    break;

  case 99: /* add_cmd: "ct" "expectation" obj_spec ct_obj_alloc '{' ct_expect_block '}' close_scope_ct  */
#line 1164 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8128 "parser_bison.c"
    break;

  case 100: /* add_cmd: "limit" obj_spec limit_obj limit_config close_scope_limit  */
#line 1168 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8136 "parser_bison.c"
    break;

  case 101: /* add_cmd: "limit" obj_spec limit_obj '{' limit_block '}' close_scope_limit  */
#line 1172 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8144 "parser_bison.c"
    break;

  case 102: /* add_cmd: "secmark" obj_spec secmark_obj secmark_config close_scope_secmark  */
#line 1176 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8152 "parser_bison.c"
    break;

  case 103: /* add_cmd: "secmark" obj_spec secmark_obj '{' secmark_block '}' close_scope_secmark  */
#line 1180 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8160 "parser_bison.c"
    break;

  case 104: /* add_cmd: "synproxy" obj_spec synproxy_obj synproxy_config close_scope_synproxy  */
#line 1184 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8168 "parser_bison.c"
    break;

  case 105: /* add_cmd: "synproxy" obj_spec synproxy_obj '{' synproxy_block '}' close_scope_synproxy  */
#line 1188 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8176 "parser_bison.c"
    break;

  case 106: /* replace_cmd: "rule" ruleid_spec rule  */
#line 1194 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8184 "parser_bison.c"
    break;

  case 107: /* create_cmd: "table" table_spec  */
#line 1200 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8192 "parser_bison.c"
    break;

  case 108: /* create_cmd: "table" table_spec table_block_alloc '{' table_block '}'  */
#line 1205 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 8202 "parser_bison.c"
    break;

  case 109: /* create_cmd: "chain" chain_spec  */
#line 1211 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8210 "parser_bison.c"
    break;

  case 110: /* create_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1216 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 8221 "parser_bison.c"
    break;

  case 111: /* create_cmd: "set" set_spec set_block_alloc '{' set_block '}'  */
#line 1224 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8231 "parser_bison.c"
    break;

  case 112: /* create_cmd: "map" set_spec map_block_alloc '{' map_block '}'  */
#line 1231 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8241 "parser_bison.c"
    break;

  case 113: /* create_cmd: "element" set_spec set_block_expr  */
#line 1237 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8249 "parser_bison.c"
    break;

  case 114: /* create_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1242 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8259 "parser_bison.c"
    break;

  case 115: /* create_cmd: "counter" obj_spec close_scope_counter  */
#line 1248 "parser_bison.y"
                        {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 8272 "parser_bison.c"
    break;

  case 116: /* create_cmd: "counter" obj_spec counter_obj counter_config close_scope_counter  */
#line 1257 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8280 "parser_bison.c"
    break;

  case 117: /* create_cmd: "quota" obj_spec quota_obj quota_config close_scope_quota  */
#line 1261 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8288 "parser_bison.c"
    break;

  case 118: /* create_cmd: "ct" "helper" obj_spec ct_obj_alloc '{' ct_helper_block '}' close_scope_ct  */
#line 1265 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8296 "parser_bison.c"
    break;

  case 119: /* create_cmd: "ct" "timeout" obj_spec ct_obj_alloc '{' ct_timeout_block '}' close_scope_ct  */
#line 1269 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8304 "parser_bison.c"
    break;

  case 120: /* create_cmd: "ct" "expectation" obj_spec ct_obj_alloc '{' ct_expect_block '}' close_scope_ct  */
#line 1273 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8312 "parser_bison.c"
    break;

  case 121: /* create_cmd: "limit" obj_spec limit_obj limit_config close_scope_limit  */
#line 1277 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8320 "parser_bison.c"
    break;

  case 122: /* create_cmd: "secmark" obj_spec secmark_obj secmark_config close_scope_secmark  */
#line 1281 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8328 "parser_bison.c"
    break;

  case 123: /* create_cmd: "synproxy" obj_spec synproxy_obj synproxy_config close_scope_synproxy  */
#line 1285 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8336 "parser_bison.c"
    break;

  case 124: /* insert_cmd: "rule" rule_position rule  */
#line 1291 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8344 "parser_bison.c"
    break;

  case 133: /* delete_cmd: "table" table_or_id_spec  */
#line 1313 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8352 "parser_bison.c"
    break;

  case 134: /* delete_cmd: "chain" chain_or_id_spec  */
#line 1317 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8360 "parser_bison.c"
    break;

  case 135: /* delete_cmd: "rule" ruleid_spec  */
#line 1321 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8368 "parser_bison.c"
    break;

  case 136: /* delete_cmd: "set" set_or_id_spec  */
#line 1325 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8376 "parser_bison.c"
    break;

  case 137: /* delete_cmd: "map" set_spec  */
#line 1329 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8384 "parser_bison.c"
    break;

  case 138: /* delete_cmd: "element" set_spec set_block_expr  */
#line 1333 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8392 "parser_bison.c"
    break;

  case 139: /* delete_cmd: "flowtable" flowtable_spec  */
#line 1337 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8400 "parser_bison.c"
    break;

  case 140: /* delete_cmd: "flowtable" flowtableid_spec  */
#line 1341 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8408 "parser_bison.c"
    break;

  case 141: /* delete_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1346 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8418 "parser_bison.c"
    break;

  case 142: /* delete_cmd: "counter" obj_or_id_spec close_scope_counter  */
#line 1352 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8426 "parser_bison.c"
    break;

  case 143: /* delete_cmd: "quota" obj_or_id_spec close_scope_quota  */
#line 1356 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8434 "parser_bison.c"
    break;

  case 144: /* delete_cmd: "ct" ct_obj_type obj_spec ct_obj_alloc close_scope_ct  */
#line 1360 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-3].val), &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
				if ((yyvsp[-3].val) == NFT_OBJECT_CT_TIMEOUT)
					init_list_head(&(yyvsp[-1].obj)->ct_timeout.timeout_list);
			}
#line 8444 "parser_bison.c"
    break;

  case 145: /* delete_cmd: "limit" obj_or_id_spec close_scope_limit  */
#line 1366 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8452 "parser_bison.c"
    break;

  case 146: /* delete_cmd: "secmark" obj_or_id_spec close_scope_secmark  */
#line 1370 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8460 "parser_bison.c"
    break;

  case 147: /* delete_cmd: "synproxy" obj_or_id_spec close_scope_synproxy  */
#line 1374 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8468 "parser_bison.c"
    break;

  case 148: /* get_cmd: "element" set_spec set_block_expr  */
#line 1380 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8476 "parser_bison.c"
    break;

  case 149: /* list_cmd: "table" table_spec  */
#line 1386 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8484 "parser_bison.c"
    break;

  case 150: /* list_cmd: "tables" ruleset_spec  */
#line 1390 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8492 "parser_bison.c"
    break;

  case 151: /* list_cmd: "chain" chain_spec  */
#line 1394 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8500 "parser_bison.c"
    break;

  case 152: /* list_cmd: "chains" ruleset_spec  */
#line 1398 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8508 "parser_bison.c"
    break;

  case 153: /* list_cmd: "sets" ruleset_spec  */
#line 1402 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8516 "parser_bison.c"
    break;

  case 154: /* list_cmd: "sets" "table" table_spec  */
#line 1406 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8524 "parser_bison.c"
    break;

  case 155: /* list_cmd: "set" set_spec  */
#line 1410 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8532 "parser_bison.c"
    break;

  case 156: /* list_cmd: "counters" ruleset_spec  */
#line 1414 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8540 "parser_bison.c"
    break;

  case 157: /* list_cmd: "counters" "table" table_spec  */
#line 1418 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8548 "parser_bison.c"
    break;

  case 158: /* list_cmd: "counter" obj_spec close_scope_counter  */
#line 1422 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8556 "parser_bison.c"
    break;

  case 159: /* list_cmd: "quotas" ruleset_spec  */
#line 1426 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8564 "parser_bison.c"
    break;

  case 160: /* list_cmd: "quotas" "table" table_spec  */
#line 1430 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8572 "parser_bison.c"
    break;

  case 161: /* list_cmd: "quota" obj_spec close_scope_quota  */
#line 1434 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8580 "parser_bison.c"
    break;

  case 162: /* list_cmd: "limits" ruleset_spec  */
#line 1438 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8588 "parser_bison.c"
    break;

  case 163: /* list_cmd: "limits" "table" table_spec  */
#line 1442 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8596 "parser_bison.c"
    break;

  case 164: /* list_cmd: "limit" obj_spec close_scope_limit  */
#line 1446 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8604 "parser_bison.c"
    break;

  case 165: /* list_cmd: "secmarks" ruleset_spec  */
#line 1450 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8612 "parser_bison.c"
    break;

  case 166: /* list_cmd: "secmarks" "table" table_spec  */
#line 1454 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8620 "parser_bison.c"
    break;

  case 167: /* list_cmd: "secmark" obj_spec close_scope_secmark  */
#line 1458 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8628 "parser_bison.c"
    break;

  case 168: /* list_cmd: "synproxys" ruleset_spec  */
#line 1462 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8636 "parser_bison.c"
    break;

  case 169: /* list_cmd: "synproxys" "table" table_spec  */
#line 1466 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8644 "parser_bison.c"
    break;

  case 170: /* list_cmd: "synproxy" obj_spec close_scope_synproxy  */
#line 1470 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8652 "parser_bison.c"
    break;

  case 171: /* list_cmd: "ruleset" ruleset_spec  */
#line 1474 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8660 "parser_bison.c"
    break;

  case 172: /* list_cmd: "flow" "tables" ruleset_spec  */
#line 1478 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8668 "parser_bison.c"
    break;

  case 173: /* list_cmd: "flow" "table" set_spec  */
#line 1482 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8676 "parser_bison.c"
    break;

  case 174: /* list_cmd: "meters" ruleset_spec  */
#line 1486 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8684 "parser_bison.c"
    break;

  case 175: /* list_cmd: "meter" set_spec  */
#line 1490 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8692 "parser_bison.c"
    break;

  case 176: /* list_cmd: "flowtables" ruleset_spec  */
#line 1494 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8700 "parser_bison.c"
    break;

  case 177: /* list_cmd: "flowtable" flowtable_spec  */
#line 1498 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8708 "parser_bison.c"
    break;

  case 178: /* list_cmd: "maps" ruleset_spec  */
#line 1502 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8716 "parser_bison.c"
    break;

  case 179: /* list_cmd: "map" set_spec  */
#line 1506 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8724 "parser_bison.c"
    break;

  case 180: /* list_cmd: "ct" ct_obj_type obj_spec close_scope_ct  */
#line 1510 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8732 "parser_bison.c"
    break;

  case 181: /* list_cmd: "ct" ct_cmd_type "table" table_spec close_scope_ct  */
#line 1514 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, (yyvsp[-3].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8740 "parser_bison.c"
    break;

  case 182: /* list_cmd: "hooks" basehook_spec  */
#line 1518 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_HOOKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8748 "parser_bison.c"
    break;

  case 183: /* basehook_device_name: "device" "string"  */
#line 1524 "parser_bison.y"
                        {
				(yyval.string) = (yyvsp[0].string);
			}
#line 8756 "parser_bison.c"
    break;

  case 184: /* basehook_spec: ruleset_spec  */
#line 1530 "parser_bison.y"
                        {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 8764 "parser_bison.c"
    break;

  case 185: /* basehook_spec: ruleset_spec basehook_device_name  */
#line 1534 "parser_bison.y"
                        {
				if ((yyvsp[0].string)) {
					(yyvsp[-1].handle).obj.name = (yyvsp[0].string);
					(yyvsp[-1].handle).obj.location = (yylsp[0]);
				}
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8776 "parser_bison.c"
    break;

  case 186: /* reset_cmd: "counters" ruleset_spec  */
#line 1544 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8784 "parser_bison.c"
    break;

  case 187: /* reset_cmd: "counters" "table" table_spec  */
#line 1548 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8792 "parser_bison.c"
    break;

  case 188: /* reset_cmd: "counter" obj_spec close_scope_counter  */
#line 1552 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[-1].handle),&(yyloc), NULL);
			}
#line 8800 "parser_bison.c"
    break;

  case 189: /* reset_cmd: "quotas" ruleset_spec  */
#line 1556 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8808 "parser_bison.c"
    break;

  case 190: /* reset_cmd: "quotas" "table" table_spec  */
#line 1560 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8816 "parser_bison.c"
    break;

  case 191: /* reset_cmd: "quota" obj_spec close_scope_quota  */
#line 1564 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8824 "parser_bison.c"
    break;

  case 192: /* flush_cmd: "table" table_spec  */
#line 1570 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8832 "parser_bison.c"
    break;

  case 193: /* flush_cmd: "chain" chain_spec  */
#line 1574 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8840 "parser_bison.c"
    break;

  case 194: /* flush_cmd: "set" set_spec  */
#line 1578 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8848 "parser_bison.c"
    break;

  case 195: /* flush_cmd: "map" set_spec  */
#line 1582 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8856 "parser_bison.c"
    break;

  case 196: /* flush_cmd: "flow" "table" set_spec  */
#line 1586 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8864 "parser_bison.c"
    break;

  case 197: /* flush_cmd: "meter" set_spec  */
#line 1590 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8872 "parser_bison.c"
    break;

  case 198: /* flush_cmd: "ruleset" ruleset_spec  */
#line 1594 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8880 "parser_bison.c"
    break;

  case 199: /* rename_cmd: "chain" chain_spec identifier  */
#line 1600 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 8889 "parser_bison.c"
    break;

  case 200: /* import_cmd: "ruleset" markup_format  */
#line 1607 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 8899 "parser_bison.c"
    break;

  case 201: /* import_cmd: markup_format  */
#line 1613 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 8909 "parser_bison.c"
    break;

  case 202: /* export_cmd: "ruleset" markup_format  */
#line 1621 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 8919 "parser_bison.c"
    break;

  case 203: /* export_cmd: markup_format  */
#line 1627 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 8929 "parser_bison.c"
    break;

  case 204: /* monitor_cmd: monitor_event monitor_object monitor_format  */
#line 1635 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 8940 "parser_bison.c"
    break;

  case 205: /* monitor_event: %empty  */
#line 1643 "parser_bison.y"
                                                { (yyval.string) = NULL; }
#line 8946 "parser_bison.c"
    break;

  case 206: /* monitor_event: "string"  */
#line 1644 "parser_bison.y"
                                                { (yyval.string) = (yyvsp[0].string); }
#line 8952 "parser_bison.c"
    break;

  case 207: /* monitor_object: %empty  */
#line 1647 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 8958 "parser_bison.c"
    break;

  case 208: /* monitor_object: "tables"  */
#line 1648 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 8964 "parser_bison.c"
    break;

  case 209: /* monitor_object: "chains"  */
#line 1649 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 8970 "parser_bison.c"
    break;

  case 210: /* monitor_object: "sets"  */
#line 1650 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 8976 "parser_bison.c"
    break;

  case 211: /* monitor_object: "rules"  */
#line 1651 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 8982 "parser_bison.c"
    break;

  case 212: /* monitor_object: "elements"  */
#line 1652 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 8988 "parser_bison.c"
    break;

  case 213: /* monitor_object: "ruleset"  */
#line 1653 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 8994 "parser_bison.c"
    break;

  case 214: /* monitor_object: "trace"  */
#line 1654 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 9000 "parser_bison.c"
    break;

  case 215: /* monitor_format: %empty  */
#line 1657 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 9006 "parser_bison.c"
    break;

  case 217: /* markup_format: "xml"  */
#line 1661 "parser_bison.y"
                                                { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 9012 "parser_bison.c"
    break;

  case 218: /* markup_format: "json"  */
#line 1662 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 9018 "parser_bison.c"
    break;

  case 219: /* markup_format: "vm" "json"  */
#line 1663 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 9024 "parser_bison.c"
    break;

  case 220: /* describe_cmd: primary_expr  */
#line 1667 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 9034 "parser_bison.c"
    break;

  case 221: /* table_block_alloc: %empty  */
#line 1675 "parser_bison.y"
                        {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 9043 "parser_bison.c"
    break;

  case 222: /* table_options: "flags" "string"  */
#line 1682 "parser_bison.y"
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
#line 9062 "parser_bison.c"
    break;

  case 223: /* table_options: comment_spec  */
#line 1697 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].table)->comment, &(yyloc), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].table)->comment = (yyvsp[0].string);
			}
#line 9074 "parser_bison.c"
    break;

  case 224: /* table_block: %empty  */
#line 1706 "parser_bison.y"
                                                { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 9080 "parser_bison.c"
    break;

  case 228: /* table_block: table_block "chain" chain_identifier chain_block_alloc '{' chain_block '}' stmt_separator  */
#line 1713 "parser_bison.y"
                        {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9093 "parser_bison.c"
    break;

  case 229: /* table_block: table_block "set" set_identifier set_block_alloc '{' set_block '}' stmt_separator  */
#line 1724 "parser_bison.y"
                        {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9105 "parser_bison.c"
    break;

  case 230: /* table_block: table_block "map" set_identifier map_block_alloc '{' map_block '}' stmt_separator  */
#line 1734 "parser_bison.y"
                        {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9117 "parser_bison.c"
    break;

  case 231: /* table_block: table_block "flowtable" flowtable_identifier flowtable_block_alloc '{' flowtable_block '}' stmt_separator  */
#line 1745 "parser_bison.y"
                        {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9129 "parser_bison.c"
    break;

  case 232: /* table_block: table_block "counter" obj_identifier obj_block_alloc '{' counter_block '}' stmt_separator close_scope_counter  */
#line 1755 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9142 "parser_bison.c"
    break;

  case 233: /* table_block: table_block "quota" obj_identifier obj_block_alloc '{' quota_block '}' stmt_separator close_scope_quota  */
#line 1766 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9155 "parser_bison.c"
    break;

  case 234: /* table_block: table_block "ct" "helper" obj_identifier obj_block_alloc '{' ct_helper_block '}' close_scope_ct stmt_separator  */
#line 1775 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9168 "parser_bison.c"
    break;

  case 235: /* table_block: table_block "ct" "timeout" obj_identifier obj_block_alloc '{' ct_timeout_block '}' close_scope_ct stmt_separator  */
#line 1784 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9181 "parser_bison.c"
    break;

  case 236: /* table_block: table_block "ct" "expectation" obj_identifier obj_block_alloc '{' ct_expect_block '}' close_scope_ct stmt_separator  */
#line 1793 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9194 "parser_bison.c"
    break;

  case 237: /* table_block: table_block "limit" obj_identifier obj_block_alloc '{' limit_block '}' stmt_separator close_scope_limit  */
#line 1804 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9207 "parser_bison.c"
    break;

  case 238: /* table_block: table_block "secmark" obj_identifier obj_block_alloc '{' secmark_block '}' stmt_separator close_scope_secmark  */
#line 1815 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9220 "parser_bison.c"
    break;

  case 239: /* table_block: table_block "synproxy" obj_identifier obj_block_alloc '{' synproxy_block '}' stmt_separator close_scope_synproxy  */
#line 1826 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9233 "parser_bison.c"
    break;

  case 240: /* chain_block_alloc: %empty  */
#line 1837 "parser_bison.y"
                        {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 9242 "parser_bison.c"
    break;

  case 241: /* chain_block: %empty  */
#line 1843 "parser_bison.y"
                                                { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 9248 "parser_bison.c"
    break;

  case 247: /* chain_block: chain_block rule stmt_separator  */
#line 1850 "parser_bison.y"
                        {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 9257 "parser_bison.c"
    break;

  case 248: /* chain_block: chain_block comment_spec stmt_separator  */
#line 1855 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].chain)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].chain)->comment = (yyvsp[-1].string);
			}
#line 9269 "parser_bison.c"
    break;

  case 249: /* subchain_block: %empty  */
#line 1864 "parser_bison.y"
                                                { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 9275 "parser_bison.c"
    break;

  case 251: /* subchain_block: subchain_block rule stmt_separator  */
#line 1867 "parser_bison.y"
                        {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 9284 "parser_bison.c"
    break;

  case 252: /* typeof_data_expr: primary_expr  */
#line 1874 "parser_bison.y"
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
#line 9309 "parser_bison.c"
    break;

  case 253: /* typeof_data_expr: typeof_expr "." primary_expr  */
#line 1895 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 9322 "parser_bison.c"
    break;

  case 254: /* typeof_expr: primary_expr  */
#line 1906 "parser_bison.y"
                        {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 9337 "parser_bison.c"
    break;

  case 255: /* typeof_expr: typeof_expr "." primary_expr  */
#line 1917 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 9350 "parser_bison.c"
    break;

  case 256: /* set_block_alloc: %empty  */
#line 1929 "parser_bison.y"
                        {
				(yyval.set) = set_alloc(NULL);
			}
#line 9358 "parser_bison.c"
    break;

  case 257: /* set_block: %empty  */
#line 1934 "parser_bison.y"
                                                { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 9364 "parser_bison.c"
    break;

  case 260: /* set_block: set_block "type" data_type_expr stmt_separator close_scope_type  */
#line 1938 "parser_bison.y"
                        {
				(yyvsp[-4].set)->key = (yyvsp[-2].expr);
				(yyval.set) = (yyvsp[-4].set);
			}
#line 9373 "parser_bison.c"
    break;

  case 261: /* set_block: set_block "typeof" typeof_expr stmt_separator  */
#line 1943 "parser_bison.y"
                        {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9383 "parser_bison.c"
    break;

  case 262: /* set_block: set_block "flags" set_flag_list stmt_separator  */
#line 1949 "parser_bison.y"
                        {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9392 "parser_bison.c"
    break;

  case 263: /* set_block: set_block "timeout" time_spec stmt_separator  */
#line 1954 "parser_bison.y"
                        {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9401 "parser_bison.c"
    break;

  case 264: /* set_block: set_block "gc-interval" time_spec stmt_separator  */
#line 1959 "parser_bison.y"
                        {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9410 "parser_bison.c"
    break;

  case 265: /* set_block: set_block stateful_stmt_list stmt_separator  */
#line 1964 "parser_bison.y"
                        {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 9420 "parser_bison.c"
    break;

  case 266: /* set_block: set_block "elements" '=' set_block_expr  */
#line 1970 "parser_bison.y"
                        {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9429 "parser_bison.c"
    break;

  case 267: /* set_block: set_block "auto-merge"  */
#line 1975 "parser_bison.y"
                        {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 9438 "parser_bison.c"
    break;

  case 269: /* set_block: set_block comment_spec stmt_separator  */
#line 1981 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 9451 "parser_bison.c"
    break;

  case 272: /* set_flag_list: set_flag_list "comma" set_flag  */
#line 1996 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9459 "parser_bison.c"
    break;

  case 274: /* set_flag: "constant"  */
#line 2002 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_CONSTANT; }
#line 9465 "parser_bison.c"
    break;

  case 275: /* set_flag: "interval"  */
#line 2003 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_INTERVAL; }
#line 9471 "parser_bison.c"
    break;

  case 276: /* set_flag: "timeout"  */
#line 2004 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_TIMEOUT; }
#line 9477 "parser_bison.c"
    break;

  case 277: /* set_flag: "dynamic"  */
#line 2005 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_EVAL; }
#line 9483 "parser_bison.c"
    break;

  case 278: /* map_block_alloc: %empty  */
#line 2009 "parser_bison.y"
                        {
				(yyval.set) = set_alloc(NULL);
			}
#line 9491 "parser_bison.c"
    break;

  case 279: /* map_block_obj_type: "counter" close_scope_counter  */
#line 2014 "parser_bison.y"
                                                            { (yyval.val) = NFT_OBJECT_COUNTER; }
#line 9497 "parser_bison.c"
    break;

  case 280: /* map_block_obj_type: "quota" close_scope_quota  */
#line 2015 "parser_bison.y"
                                                          { (yyval.val) = NFT_OBJECT_QUOTA; }
#line 9503 "parser_bison.c"
    break;

  case 281: /* map_block_obj_type: "limit" close_scope_limit  */
#line 2016 "parser_bison.y"
                                                          { (yyval.val) = NFT_OBJECT_LIMIT; }
#line 9509 "parser_bison.c"
    break;

  case 282: /* map_block_obj_type: "secmark" close_scope_secmark  */
#line 2017 "parser_bison.y"
                                                            { (yyval.val) = NFT_OBJECT_SECMARK; }
#line 9515 "parser_bison.c"
    break;

  case 283: /* map_block_obj_type: "synproxy" close_scope_synproxy  */
#line 2018 "parser_bison.y"
                                                              { (yyval.val) = NFT_OBJECT_SYNPROXY; }
#line 9521 "parser_bison.c"
    break;

  case 284: /* map_block: %empty  */
#line 2021 "parser_bison.y"
                                                { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 9527 "parser_bison.c"
    break;

  case 287: /* map_block: map_block "timeout" time_spec stmt_separator  */
#line 2025 "parser_bison.y"
                        {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9536 "parser_bison.c"
    break;

  case 288: /* map_block: map_block "type" data_type_expr "colon" data_type_expr stmt_separator close_scope_type  */
#line 2032 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->data = (yyvsp[-2].expr);

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 9548 "parser_bison.c"
    break;

  case 289: /* map_block: map_block "type" data_type_expr "colon" "interval" data_type_expr stmt_separator close_scope_type  */
#line 2042 "parser_bison.y"
                        {
				(yyvsp[-7].set)->key = (yyvsp[-5].expr);
				(yyvsp[-7].set)->data = (yyvsp[-2].expr);
				(yyvsp[-7].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-7].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-7].set);
			}
#line 9561 "parser_bison.c"
    break;

  case 290: /* map_block: map_block "typeof" typeof_expr "colon" typeof_data_expr stmt_separator  */
#line 2053 "parser_bison.y"
                        {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 9574 "parser_bison.c"
    break;

  case 291: /* map_block: map_block "typeof" typeof_expr "colon" "interval" typeof_expr stmt_separator  */
#line 2064 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				datatype_set((yyvsp[-6].set)->key, (yyvsp[-4].expr)->dtype);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 9588 "parser_bison.c"
    break;

  case 292: /* map_block: map_block "type" data_type_expr "colon" map_block_obj_type stmt_separator close_scope_type  */
#line 2076 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->objtype = (yyvsp[-2].val);
				(yyvsp[-6].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 9599 "parser_bison.c"
    break;

  case 293: /* map_block: map_block "flags" set_flag_list stmt_separator  */
#line 2083 "parser_bison.y"
                        {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9608 "parser_bison.c"
    break;

  case 294: /* map_block: map_block stateful_stmt_list stmt_separator  */
#line 2088 "parser_bison.y"
                        {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 9618 "parser_bison.c"
    break;

  case 295: /* map_block: map_block "elements" '=' set_block_expr  */
#line 2094 "parser_bison.y"
                        {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 9627 "parser_bison.c"
    break;

  case 296: /* map_block: map_block comment_spec stmt_separator  */
#line 2099 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 9640 "parser_bison.c"
    break;

  case 298: /* set_mechanism: "policy" set_policy_spec close_scope_policy  */
#line 2111 "parser_bison.y"
                        {
				(yyvsp[-3].set)->policy = (yyvsp[-1].val);
			}
#line 9648 "parser_bison.c"
    break;

  case 299: /* set_mechanism: "size" "number"  */
#line 2115 "parser_bison.y"
                        {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 9656 "parser_bison.c"
    break;

  case 300: /* set_policy_spec: "performance"  */
#line 2120 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 9662 "parser_bison.c"
    break;

  case 301: /* set_policy_spec: "memory"  */
#line 2121 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 9668 "parser_bison.c"
    break;

  case 302: /* flowtable_block_alloc: %empty  */
#line 2125 "parser_bison.y"
                        {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 9676 "parser_bison.c"
    break;

  case 303: /* flowtable_block: %empty  */
#line 2130 "parser_bison.y"
                                                { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 9682 "parser_bison.c"
    break;

  case 306: /* flowtable_block: flowtable_block "hook" "string" prio_spec stmt_separator  */
#line 2134 "parser_bison.y"
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
#line 9700 "parser_bison.c"
    break;

  case 307: /* flowtable_block: flowtable_block "devices" '=' flowtable_expr stmt_separator  */
#line 2148 "parser_bison.y"
                        {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 9708 "parser_bison.c"
    break;

  case 308: /* flowtable_block: flowtable_block "counter" close_scope_counter  */
#line 2152 "parser_bison.y"
                        {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 9716 "parser_bison.c"
    break;

  case 309: /* flowtable_block: flowtable_block "flags" "offload" stmt_separator  */
#line 2156 "parser_bison.y"
                        {
				(yyval.flowtable)->flags |= FLOWTABLE_F_HW_OFFLOAD;
			}
#line 9724 "parser_bison.c"
    break;

  case 310: /* flowtable_expr: '{' flowtable_list_expr '}'  */
#line 2162 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9733 "parser_bison.c"
    break;

  case 311: /* flowtable_expr: variable_expr  */
#line 2167 "parser_bison.y"
                        {
				(yyvsp[0].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 9742 "parser_bison.c"
    break;

  case 312: /* flowtable_list_expr: flowtable_expr_member  */
#line 2174 "parser_bison.y"
                        {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9751 "parser_bison.c"
    break;

  case 313: /* flowtable_list_expr: flowtable_list_expr "comma" flowtable_expr_member  */
#line 2179 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9760 "parser_bison.c"
    break;

  case 315: /* flowtable_expr_member: "quoted string"  */
#line 2187 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9771 "parser_bison.c"
    break;

  case 316: /* flowtable_expr_member: "string"  */
#line 2194 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9782 "parser_bison.c"
    break;

  case 317: /* flowtable_expr_member: variable_expr  */
#line 2201 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 9791 "parser_bison.c"
    break;

  case 318: /* data_type_atom_expr: type_identifier  */
#line 2208 "parser_bison.y"
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
#line 9808 "parser_bison.c"
    break;

  case 319: /* data_type_atom_expr: "time"  */
#line 2221 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 9817 "parser_bison.c"
    break;

  case 321: /* data_type_expr: data_type_expr "." data_type_atom_expr  */
#line 2229 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 9830 "parser_bison.c"
    break;

  case 322: /* obj_block_alloc: %empty  */
#line 2240 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 9838 "parser_bison.c"
    break;

  case 323: /* counter_block: %empty  */
#line 2245 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9844 "parser_bison.c"
    break;

  case 326: /* counter_block: counter_block counter_config  */
#line 2249 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9852 "parser_bison.c"
    break;

  case 327: /* counter_block: counter_block comment_spec  */
#line 2253 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9864 "parser_bison.c"
    break;

  case 328: /* quota_block: %empty  */
#line 2262 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9870 "parser_bison.c"
    break;

  case 331: /* quota_block: quota_block quota_config  */
#line 2266 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9878 "parser_bison.c"
    break;

  case 332: /* quota_block: quota_block comment_spec  */
#line 2270 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9890 "parser_bison.c"
    break;

  case 333: /* ct_helper_block: %empty  */
#line 2279 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9896 "parser_bison.c"
    break;

  case 336: /* ct_helper_block: ct_helper_block ct_helper_config  */
#line 2283 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9904 "parser_bison.c"
    break;

  case 337: /* ct_helper_block: ct_helper_block comment_spec  */
#line 2287 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9916 "parser_bison.c"
    break;

  case 338: /* ct_timeout_block: %empty  */
#line 2297 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[(-1) - (0)].obj);
				init_list_head(&(yyval.obj)->ct_timeout.timeout_list);
			}
#line 9925 "parser_bison.c"
    break;

  case 341: /* ct_timeout_block: ct_timeout_block ct_timeout_config  */
#line 2304 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9933 "parser_bison.c"
    break;

  case 342: /* ct_timeout_block: ct_timeout_block comment_spec  */
#line 2308 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9945 "parser_bison.c"
    break;

  case 343: /* ct_expect_block: %empty  */
#line 2317 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9951 "parser_bison.c"
    break;

  case 346: /* ct_expect_block: ct_expect_block ct_expect_config  */
#line 2321 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9959 "parser_bison.c"
    break;

  case 347: /* ct_expect_block: ct_expect_block comment_spec  */
#line 2325 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9971 "parser_bison.c"
    break;

  case 348: /* limit_block: %empty  */
#line 2334 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 9977 "parser_bison.c"
    break;

  case 351: /* limit_block: limit_block limit_config  */
#line 2338 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 9985 "parser_bison.c"
    break;

  case 352: /* limit_block: limit_block comment_spec  */
#line 2342 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 9997 "parser_bison.c"
    break;

  case 353: /* secmark_block: %empty  */
#line 2351 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10003 "parser_bison.c"
    break;

  case 356: /* secmark_block: secmark_block secmark_config  */
#line 2355 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10011 "parser_bison.c"
    break;

  case 357: /* secmark_block: secmark_block comment_spec  */
#line 2359 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10023 "parser_bison.c"
    break;

  case 358: /* synproxy_block: %empty  */
#line 2368 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10029 "parser_bison.c"
    break;

  case 361: /* synproxy_block: synproxy_block synproxy_config  */
#line 2372 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10037 "parser_bison.c"
    break;

  case 362: /* synproxy_block: synproxy_block comment_spec  */
#line 2376 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10049 "parser_bison.c"
    break;

  case 363: /* type_identifier: "string"  */
#line 2385 "parser_bison.y"
                                        { (yyval.string) = (yyvsp[0].string); }
#line 10055 "parser_bison.c"
    break;

  case 364: /* type_identifier: "mark"  */
#line 2386 "parser_bison.y"
                                        { (yyval.string) = xstrdup("mark"); }
#line 10061 "parser_bison.c"
    break;

  case 365: /* type_identifier: "dscp"  */
#line 2387 "parser_bison.y"
                                        { (yyval.string) = xstrdup("dscp"); }
#line 10067 "parser_bison.c"
    break;

  case 366: /* type_identifier: "ecn"  */
#line 2388 "parser_bison.y"
                                        { (yyval.string) = xstrdup("ecn"); }
#line 10073 "parser_bison.c"
    break;

  case 367: /* type_identifier: "classid"  */
#line 2389 "parser_bison.y"
                                        { (yyval.string) = xstrdup("classid"); }
#line 10079 "parser_bison.c"
    break;

  case 368: /* hook_spec: "type" close_scope_type "string" "hook" "string" dev_spec prio_spec  */
#line 2393 "parser_bison.y"
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
#line 10112 "parser_bison.c"
    break;

  case 369: /* prio_spec: "priority" extended_prio_spec  */
#line 2424 "parser_bison.y"
                        {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 10121 "parser_bison.c"
    break;

  case 370: /* extended_prio_name: "out"  */
#line 2431 "parser_bison.y"
                        {
				(yyval.string) = strdup("out");
			}
#line 10129 "parser_bison.c"
    break;

  case 372: /* extended_prio_spec: int_num  */
#line 2438 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 10143 "parser_bison.c"
    break;

  case 373: /* extended_prio_spec: variable_expr  */
#line 2448 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 10154 "parser_bison.c"
    break;

  case 374: /* extended_prio_spec: extended_prio_name  */
#line 2455 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 10169 "parser_bison.c"
    break;

  case 375: /* extended_prio_spec: extended_prio_name "+" "number"  */
#line 2466 "parser_bison.y"
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
#line 10186 "parser_bison.c"
    break;

  case 376: /* extended_prio_spec: extended_prio_name "-" "number"  */
#line 2479 "parser_bison.y"
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
#line 10203 "parser_bison.c"
    break;

  case 377: /* int_num: "number"  */
#line 2493 "parser_bison.y"
                                                        { (yyval.val32) = (yyvsp[0].val); }
#line 10209 "parser_bison.c"
    break;

  case 378: /* int_num: "-" "number"  */
#line 2494 "parser_bison.y"
                                                        { (yyval.val32) = -(yyvsp[0].val); }
#line 10215 "parser_bison.c"
    break;

  case 379: /* dev_spec: "device" string  */
#line 2498 "parser_bison.y"
                        {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 10231 "parser_bison.c"
    break;

  case 380: /* dev_spec: "device" variable_expr  */
#line 2510 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10241 "parser_bison.c"
    break;

  case 381: /* dev_spec: "devices" '=' flowtable_expr  */
#line 2516 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10249 "parser_bison.c"
    break;

  case 382: /* dev_spec: %empty  */
#line 2519 "parser_bison.y"
                                                        { (yyval.expr) = NULL; }
#line 10255 "parser_bison.c"
    break;

  case 383: /* flags_spec: "flags" "offload"  */
#line 2523 "parser_bison.y"
                        {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 10263 "parser_bison.c"
    break;

  case 384: /* policy_spec: "policy" policy_expr close_scope_policy  */
#line 2529 "parser_bison.y"
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
#line 10278 "parser_bison.c"
    break;

  case 385: /* policy_expr: variable_expr  */
#line 2542 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10287 "parser_bison.c"
    break;

  case 386: /* policy_expr: chain_policy  */
#line 2547 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 10298 "parser_bison.c"
    break;

  case 387: /* chain_policy: "accept"  */
#line 2555 "parser_bison.y"
                                                { (yyval.val32) = NF_ACCEPT; }
#line 10304 "parser_bison.c"
    break;

  case 388: /* chain_policy: "drop"  */
#line 2556 "parser_bison.y"
                                                { (yyval.val32) = NF_DROP;   }
#line 10310 "parser_bison.c"
    break;

  case 393: /* time_spec: "string"  */
#line 2568 "parser_bison.y"
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
#line 10327 "parser_bison.c"
    break;

  case 394: /* family_spec: %empty  */
#line 2582 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV4; }
#line 10333 "parser_bison.c"
    break;

  case 396: /* family_spec_explicit: "ip" close_scope_ip  */
#line 2586 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV4; }
#line 10339 "parser_bison.c"
    break;

  case 397: /* family_spec_explicit: "ip6" close_scope_ip6  */
#line 2587 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV6; }
#line 10345 "parser_bison.c"
    break;

  case 398: /* family_spec_explicit: "inet"  */
#line 2588 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_INET; }
#line 10351 "parser_bison.c"
    break;

  case 399: /* family_spec_explicit: "arp" close_scope_arp  */
#line 2589 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_ARP; }
#line 10357 "parser_bison.c"
    break;

  case 400: /* family_spec_explicit: "bridge"  */
#line 2590 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_BRIDGE; }
#line 10363 "parser_bison.c"
    break;

  case 401: /* family_spec_explicit: "netdev"  */
#line 2591 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_NETDEV; }
#line 10369 "parser_bison.c"
    break;

  case 402: /* table_spec: family_spec identifier  */
#line 2595 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 10380 "parser_bison.c"
    break;

  case 403: /* tableid_spec: family_spec "handle" "number"  */
#line 2604 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 10391 "parser_bison.c"
    break;

  case 404: /* chain_spec: table_spec identifier  */
#line 2613 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 10401 "parser_bison.c"
    break;

  case 405: /* chainid_spec: table_spec "handle" "number"  */
#line 2621 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 10411 "parser_bison.c"
    break;

  case 406: /* chain_identifier: identifier  */
#line 2629 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 10421 "parser_bison.c"
    break;

  case 407: /* set_spec: table_spec identifier  */
#line 2637 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 10431 "parser_bison.c"
    break;

  case 408: /* setid_spec: table_spec "handle" "number"  */
#line 2645 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 10441 "parser_bison.c"
    break;

  case 409: /* set_identifier: identifier  */
#line 2653 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 10451 "parser_bison.c"
    break;

  case 410: /* flowtable_spec: table_spec identifier  */
#line 2661 "parser_bison.y"
                        {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 10461 "parser_bison.c"
    break;

  case 411: /* flowtableid_spec: table_spec "handle" "number"  */
#line 2669 "parser_bison.y"
                        {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 10471 "parser_bison.c"
    break;

  case 412: /* flowtable_identifier: identifier  */
#line 2677 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 10481 "parser_bison.c"
    break;

  case 413: /* obj_spec: table_spec identifier  */
#line 2685 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 10491 "parser_bison.c"
    break;

  case 414: /* objid_spec: table_spec "handle" "number"  */
#line 2693 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 10501 "parser_bison.c"
    break;

  case 415: /* obj_identifier: identifier  */
#line 2701 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 10511 "parser_bison.c"
    break;

  case 416: /* handle_spec: "handle" "number"  */
#line 2709 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 10521 "parser_bison.c"
    break;

  case 417: /* position_spec: "position" "number"  */
#line 2717 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 10531 "parser_bison.c"
    break;

  case 418: /* index_spec: "index" "number"  */
#line 2725 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 10541 "parser_bison.c"
    break;

  case 419: /* rule_position: chain_spec  */
#line 2733 "parser_bison.y"
                        {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 10549 "parser_bison.c"
    break;

  case 420: /* rule_position: chain_spec position_spec  */
#line 2737 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 10558 "parser_bison.c"
    break;

  case 421: /* rule_position: chain_spec handle_spec  */
#line 2742 "parser_bison.y"
                        {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 10570 "parser_bison.c"
    break;

  case 422: /* rule_position: chain_spec index_spec  */
#line 2750 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 10579 "parser_bison.c"
    break;

  case 423: /* ruleid_spec: chain_spec handle_spec  */
#line 2757 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 10588 "parser_bison.c"
    break;

  case 424: /* comment_spec: "comment" string  */
#line 2764 "parser_bison.y"
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
#line 10603 "parser_bison.c"
    break;

  case 425: /* ruleset_spec: %empty  */
#line 2777 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 10612 "parser_bison.c"
    break;

  case 426: /* ruleset_spec: family_spec_explicit  */
#line 2782 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 10621 "parser_bison.c"
    break;

  case 427: /* rule: rule_alloc  */
#line 2789 "parser_bison.y"
                        {
				(yyval.rule)->comment = NULL;
			}
#line 10629 "parser_bison.c"
    break;

  case 428: /* rule: rule_alloc comment_spec  */
#line 2793 "parser_bison.y"
                        {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 10637 "parser_bison.c"
    break;

  case 429: /* rule_alloc: stmt_list  */
#line 2799 "parser_bison.y"
                        {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 10651 "parser_bison.c"
    break;

  case 430: /* stmt_list: stmt  */
#line 2811 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 10661 "parser_bison.c"
    break;

  case 431: /* stmt_list: stmt_list stmt  */
#line 2817 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 10670 "parser_bison.c"
    break;

  case 432: /* stateful_stmt_list: stateful_stmt  */
#line 2824 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 10680 "parser_bison.c"
    break;

  case 433: /* stateful_stmt_list: stateful_stmt_list stateful_stmt  */
#line 2830 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 10689 "parser_bison.c"
    break;

  case 459: /* chain_stmt_type: "jump"  */
#line 2865 "parser_bison.y"
                                        { (yyval.val) = NFT_JUMP; }
#line 10695 "parser_bison.c"
    break;

  case 460: /* chain_stmt_type: "goto"  */
#line 2866 "parser_bison.y"
                                        { (yyval.val) = NFT_GOTO; }
#line 10701 "parser_bison.c"
    break;

  case 461: /* chain_stmt: chain_stmt_type chain_block_alloc '{' subchain_block '}'  */
#line 2870 "parser_bison.y"
                        {
				(yyvsp[-3].chain)->location = (yylsp[-3]);
				close_scope(state);
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				(yyval.stmt) = chain_stmt_alloc(&(yyloc), (yyvsp[-1].chain), (yyvsp[-4].val));
			}
#line 10712 "parser_bison.c"
    break;

  case 462: /* verdict_stmt: verdict_expr  */
#line 2879 "parser_bison.y"
                        {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 10720 "parser_bison.c"
    break;

  case 463: /* verdict_stmt: verdict_map_stmt  */
#line 2883 "parser_bison.y"
                        {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 10728 "parser_bison.c"
    break;

  case 464: /* verdict_map_stmt: concat_expr "vmap" verdict_map_expr  */
#line 2889 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10736 "parser_bison.c"
    break;

  case 465: /* verdict_map_expr: '{' verdict_map_list_expr '}'  */
#line 2895 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10745 "parser_bison.c"
    break;

  case 467: /* verdict_map_list_expr: verdict_map_list_member_expr  */
#line 2903 "parser_bison.y"
                        {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10754 "parser_bison.c"
    break;

  case 468: /* verdict_map_list_expr: verdict_map_list_expr "comma" verdict_map_list_member_expr  */
#line 2908 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10763 "parser_bison.c"
    break;

  case 470: /* verdict_map_list_member_expr: opt_newline set_elem_expr "colon" verdict_expr opt_newline  */
#line 2916 "parser_bison.y"
                        {
				(yyval.expr) = mapping_expr_alloc(&(yylsp[-3]), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 10771 "parser_bison.c"
    break;

  case 471: /* connlimit_stmt: "ct" "count" "number" close_scope_ct  */
#line 2922 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 10780 "parser_bison.c"
    break;

  case 472: /* connlimit_stmt: "ct" "count" "over" "number" close_scope_ct  */
#line 2927 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 10790 "parser_bison.c"
    break;

  case 475: /* counter_stmt_alloc: "counter"  */
#line 2938 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 10798 "parser_bison.c"
    break;

  case 476: /* counter_stmt_alloc: "counter" "name" stmt_expr  */
#line 2942 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 10808 "parser_bison.c"
    break;

  case 477: /* counter_args: counter_arg  */
#line 2950 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10816 "parser_bison.c"
    break;

  case 479: /* counter_arg: "packets" "number"  */
#line 2957 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 10824 "parser_bison.c"
    break;

  case 480: /* counter_arg: "bytes" "number"  */
#line 2961 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 10832 "parser_bison.c"
    break;

  case 483: /* log_stmt_alloc: "log"  */
#line 2971 "parser_bison.y"
                        {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 10840 "parser_bison.c"
    break;

  case 484: /* log_args: log_arg  */
#line 2977 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10848 "parser_bison.c"
    break;

  case 486: /* log_arg: "prefix" string  */
#line 2984 "parser_bison.y"
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
#line 10977 "parser_bison.c"
    break;

  case 487: /* log_arg: "group" "number"  */
#line 3109 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 10986 "parser_bison.c"
    break;

  case 488: /* log_arg: "snaplen" "number"  */
#line 3114 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 10995 "parser_bison.c"
    break;

  case 489: /* log_arg: "queue-threshold" "number"  */
#line 3119 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 11004 "parser_bison.c"
    break;

  case 490: /* log_arg: "level" level_type  */
#line 3124 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 11013 "parser_bison.c"
    break;

  case 491: /* log_arg: "flags" log_flags  */
#line 3129 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 11021 "parser_bison.c"
    break;

  case 492: /* level_type: string  */
#line 3135 "parser_bison.y"
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
#line 11053 "parser_bison.c"
    break;

  case 493: /* log_flags: "tcp" log_flags_tcp close_scope_tcp  */
#line 3165 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-1].val);
			}
#line 11061 "parser_bison.c"
    break;

  case 494: /* log_flags: "ip" "options" close_scope_ip  */
#line 3169 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 11069 "parser_bison.c"
    break;

  case 495: /* log_flags: "skuid"  */
#line 3173 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_UID;
			}
#line 11077 "parser_bison.c"
    break;

  case 496: /* log_flags: "ether" close_scope_eth  */
#line 3177 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 11085 "parser_bison.c"
    break;

  case 497: /* log_flags: "all"  */
#line 3181 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_MASK;
			}
#line 11093 "parser_bison.c"
    break;

  case 498: /* log_flags_tcp: log_flags_tcp "comma" log_flag_tcp  */
#line 3187 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 11101 "parser_bison.c"
    break;

  case 500: /* log_flag_tcp: "seq"  */
#line 3194 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 11109 "parser_bison.c"
    break;

  case 501: /* log_flag_tcp: "options"  */
#line 3198 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 11117 "parser_bison.c"
    break;

  case 502: /* limit_stmt: "limit" "rate" limit_mode limit_rate_pkts limit_burst_pkts close_scope_limit  */
#line 3204 "parser_bison.y"
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
#line 11135 "parser_bison.c"
    break;

  case 503: /* limit_stmt: "limit" "rate" limit_mode limit_rate_bytes limit_burst_bytes close_scope_limit  */
#line 3218 "parser_bison.y"
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
#line 11153 "parser_bison.c"
    break;

  case 504: /* limit_stmt: "limit" "name" stmt_expr close_scope_limit  */
#line 3232 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 11163 "parser_bison.c"
    break;

  case 505: /* quota_mode: "over"  */
#line 3239 "parser_bison.y"
                                                { (yyval.val) = NFT_QUOTA_F_INV; }
#line 11169 "parser_bison.c"
    break;

  case 506: /* quota_mode: "until"  */
#line 3240 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11175 "parser_bison.c"
    break;

  case 507: /* quota_mode: %empty  */
#line 3241 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11181 "parser_bison.c"
    break;

  case 508: /* quota_unit: "bytes"  */
#line 3244 "parser_bison.y"
                                                { (yyval.string) = xstrdup("bytes"); }
#line 11187 "parser_bison.c"
    break;

  case 509: /* quota_unit: "string"  */
#line 3245 "parser_bison.y"
                                                { (yyval.string) = (yyvsp[0].string); }
#line 11193 "parser_bison.c"
    break;

  case 510: /* quota_used: %empty  */
#line 3248 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11199 "parser_bison.c"
    break;

  case 511: /* quota_used: "used" "number" quota_unit  */
#line 3250 "parser_bison.y"
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
#line 11216 "parser_bison.c"
    break;

  case 512: /* quota_stmt: "quota" quota_mode "number" quota_unit quota_used close_scope_quota  */
#line 3265 "parser_bison.y"
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
#line 11236 "parser_bison.c"
    break;

  case 513: /* quota_stmt: "quota" "name" stmt_expr close_scope_quota  */
#line 3281 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 11246 "parser_bison.c"
    break;

  case 514: /* limit_mode: "over"  */
#line 3288 "parser_bison.y"
                                                                { (yyval.val) = NFT_LIMIT_F_INV; }
#line 11252 "parser_bison.c"
    break;

  case 515: /* limit_mode: "until"  */
#line 3289 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 11258 "parser_bison.c"
    break;

  case 516: /* limit_mode: %empty  */
#line 3290 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 11264 "parser_bison.c"
    break;

  case 517: /* limit_burst_pkts: %empty  */
#line 3293 "parser_bison.y"
                                                                { (yyval.val) = 5; }
#line 11270 "parser_bison.c"
    break;

  case 518: /* limit_burst_pkts: "burst" "number" "packets"  */
#line 3294 "parser_bison.y"
                                                                { (yyval.val) = (yyvsp[-1].val); }
#line 11276 "parser_bison.c"
    break;

  case 519: /* limit_rate_pkts: "number" "/" time_unit  */
#line 3298 "parser_bison.y"
                        {
				(yyval.limit_rate).rate = (yyvsp[-2].val);
				(yyval.limit_rate).unit = (yyvsp[0].val);
			}
#line 11285 "parser_bison.c"
    break;

  case 520: /* limit_burst_bytes: %empty  */
#line 3304 "parser_bison.y"
                                                                { (yyval.val) = 5; }
#line 11291 "parser_bison.c"
    break;

  case 521: /* limit_burst_bytes: "burst" limit_bytes  */
#line 3305 "parser_bison.y"
                                                                { (yyval.val) = (yyvsp[0].val); }
#line 11297 "parser_bison.c"
    break;

  case 522: /* limit_rate_bytes: "number" "string"  */
#line 3309 "parser_bison.y"
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
#line 11315 "parser_bison.c"
    break;

  case 523: /* limit_rate_bytes: limit_bytes "/" time_unit  */
#line 3323 "parser_bison.y"
                        {
				(yyval.limit_rate).rate = (yyvsp[-2].val);
				(yyval.limit_rate).unit = (yyvsp[0].val);
			}
#line 11324 "parser_bison.c"
    break;

  case 524: /* limit_bytes: "number" "bytes"  */
#line 3329 "parser_bison.y"
                                                        { (yyval.val) = (yyvsp[-1].val); }
#line 11330 "parser_bison.c"
    break;

  case 525: /* limit_bytes: "number" "string"  */
#line 3331 "parser_bison.y"
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
#line 11347 "parser_bison.c"
    break;

  case 526: /* time_unit: "second"  */
#line 3345 "parser_bison.y"
                                                { (yyval.val) = 1ULL; }
#line 11353 "parser_bison.c"
    break;

  case 527: /* time_unit: "minute"  */
#line 3346 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60; }
#line 11359 "parser_bison.c"
    break;

  case 528: /* time_unit: "hour"  */
#line 3347 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60; }
#line 11365 "parser_bison.c"
    break;

  case 529: /* time_unit: "day"  */
#line 3348 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 11371 "parser_bison.c"
    break;

  case 530: /* time_unit: "week"  */
#line 3349 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 11377 "parser_bison.c"
    break;

  case 532: /* reject_stmt_alloc: "reject"  */
#line 3356 "parser_bison.y"
                        {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 11385 "parser_bison.c"
    break;

  case 533: /* reject_with_expr: "string"  */
#line 3362 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state), (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 11395 "parser_bison.c"
    break;

  case 534: /* reject_with_expr: integer_expr  */
#line 3367 "parser_bison.y"
                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11401 "parser_bison.c"
    break;

  case 535: /* reject_opts: %empty  */
#line 3371 "parser_bison.y"
                        {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 11410 "parser_bison.c"
    break;

  case 536: /* reject_opts: "with" "icmp" "type" reject_with_expr close_scope_type close_scope_icmp  */
#line 3376 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-6].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-6].stmt)->reject.expr = (yyvsp[-2].expr);
				datatype_set((yyvsp[-6].stmt)->reject.expr, &icmp_code_type);
			}
#line 11421 "parser_bison.c"
    break;

  case 537: /* reject_opts: "with" "icmp" reject_with_expr  */
#line 3383 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmp_code_type);
			}
#line 11432 "parser_bison.c"
    break;

  case 538: /* reject_opts: "with" "icmpv6" "type" reject_with_expr close_scope_type close_scope_icmp  */
#line 3390 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-6].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-6].stmt)->reject.expr = (yyvsp[-2].expr);
				datatype_set((yyvsp[-6].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 11443 "parser_bison.c"
    break;

  case 539: /* reject_opts: "with" "icmpv6" reject_with_expr  */
#line 3397 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 11454 "parser_bison.c"
    break;

  case 540: /* reject_opts: "with" "icmpx" "type" reject_with_expr close_scope_type  */
#line 3404 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-5].stmt)->reject.expr = (yyvsp[-1].expr);
				datatype_set((yyvsp[-5].stmt)->reject.expr, &icmpx_code_type);
			}
#line 11464 "parser_bison.c"
    break;

  case 541: /* reject_opts: "with" "icmpx" reject_with_expr  */
#line 3410 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpx_code_type);
			}
#line 11474 "parser_bison.c"
    break;

  case 542: /* reject_opts: "with" "tcp" close_scope_tcp "reset" close_scope_reset  */
#line 3416 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 11482 "parser_bison.c"
    break;

  case 544: /* nat_stmt_alloc: "snat"  */
#line 3424 "parser_bison.y"
                                        { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 11488 "parser_bison.c"
    break;

  case 545: /* nat_stmt_alloc: "dnat"  */
#line 3425 "parser_bison.y"
                                        { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 11494 "parser_bison.c"
    break;

  case 546: /* tproxy_stmt: "tproxy" "to" stmt_expr  */
#line 3429 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 11504 "parser_bison.c"
    break;

  case 547: /* tproxy_stmt: "tproxy" nf_key_proto "to" stmt_expr  */
#line 3435 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 11514 "parser_bison.c"
    break;

  case 548: /* tproxy_stmt: "tproxy" "to" "colon" stmt_expr  */
#line 3441 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 11524 "parser_bison.c"
    break;

  case 549: /* tproxy_stmt: "tproxy" "to" stmt_expr "colon" stmt_expr  */
#line 3447 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 11535 "parser_bison.c"
    break;

  case 550: /* tproxy_stmt: "tproxy" nf_key_proto "to" stmt_expr "colon" stmt_expr  */
#line 3454 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 11546 "parser_bison.c"
    break;

  case 551: /* tproxy_stmt: "tproxy" nf_key_proto "to" "colon" stmt_expr  */
#line 3461 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 11556 "parser_bison.c"
    break;

  case 554: /* synproxy_stmt_alloc: "synproxy"  */
#line 3473 "parser_bison.y"
                        {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 11564 "parser_bison.c"
    break;

  case 555: /* synproxy_stmt_alloc: "synproxy" "name" stmt_expr  */
#line 3477 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 11574 "parser_bison.c"
    break;

  case 556: /* synproxy_args: synproxy_arg  */
#line 3485 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 11582 "parser_bison.c"
    break;

  case 558: /* synproxy_arg: "mss" "number"  */
#line 3492 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 11591 "parser_bison.c"
    break;

  case 559: /* synproxy_arg: "wscale" "number"  */
#line 3497 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 11600 "parser_bison.c"
    break;

  case 560: /* synproxy_arg: "timestamp"  */
#line 3502 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 11608 "parser_bison.c"
    break;

  case 561: /* synproxy_arg: "sack-permitted"  */
#line 3506 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 11616 "parser_bison.c"
    break;

  case 562: /* synproxy_config: "mss" "number" "wscale" "number" synproxy_ts synproxy_sack  */
#line 3512 "parser_bison.y"
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
#line 11636 "parser_bison.c"
    break;

  case 563: /* synproxy_config: "mss" "number" stmt_separator "wscale" "number" stmt_separator synproxy_ts synproxy_sack  */
#line 3528 "parser_bison.y"
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
#line 11656 "parser_bison.c"
    break;

  case 564: /* synproxy_obj: %empty  */
#line 3546 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 11665 "parser_bison.c"
    break;

  case 565: /* synproxy_ts: %empty  */
#line 3552 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11671 "parser_bison.c"
    break;

  case 566: /* synproxy_ts: "timestamp"  */
#line 3554 "parser_bison.y"
                        {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 11679 "parser_bison.c"
    break;

  case 567: /* synproxy_sack: %empty  */
#line 3559 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11685 "parser_bison.c"
    break;

  case 568: /* synproxy_sack: "sack-permitted"  */
#line 3561 "parser_bison.y"
                        {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 11693 "parser_bison.c"
    break;

  case 569: /* primary_stmt_expr: symbol_expr  */
#line 3566 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11699 "parser_bison.c"
    break;

  case 570: /* primary_stmt_expr: integer_expr  */
#line 3567 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11705 "parser_bison.c"
    break;

  case 571: /* primary_stmt_expr: boolean_expr  */
#line 3568 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11711 "parser_bison.c"
    break;

  case 572: /* primary_stmt_expr: meta_expr  */
#line 3569 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11717 "parser_bison.c"
    break;

  case 573: /* primary_stmt_expr: rt_expr  */
#line 3570 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11723 "parser_bison.c"
    break;

  case 574: /* primary_stmt_expr: ct_expr  */
#line 3571 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11729 "parser_bison.c"
    break;

  case 575: /* primary_stmt_expr: numgen_expr  */
#line 3572 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11735 "parser_bison.c"
    break;

  case 576: /* primary_stmt_expr: hash_expr  */
#line 3573 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11741 "parser_bison.c"
    break;

  case 577: /* primary_stmt_expr: payload_expr  */
#line 3574 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11747 "parser_bison.c"
    break;

  case 578: /* primary_stmt_expr: keyword_expr  */
#line 3575 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11753 "parser_bison.c"
    break;

  case 579: /* primary_stmt_expr: socket_expr  */
#line 3576 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11759 "parser_bison.c"
    break;

  case 580: /* primary_stmt_expr: osf_expr  */
#line 3577 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 11765 "parser_bison.c"
    break;

  case 581: /* primary_stmt_expr: '(' basic_stmt_expr ')'  */
#line 3578 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 11771 "parser_bison.c"
    break;

  case 583: /* shift_stmt_expr: shift_stmt_expr "<<" primary_stmt_expr  */
#line 3583 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11779 "parser_bison.c"
    break;

  case 584: /* shift_stmt_expr: shift_stmt_expr ">>" primary_stmt_expr  */
#line 3587 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11787 "parser_bison.c"
    break;

  case 586: /* and_stmt_expr: and_stmt_expr "&" shift_stmt_expr  */
#line 3594 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11795 "parser_bison.c"
    break;

  case 588: /* exclusive_or_stmt_expr: exclusive_or_stmt_expr "^" and_stmt_expr  */
#line 3601 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11803 "parser_bison.c"
    break;

  case 590: /* inclusive_or_stmt_expr: inclusive_or_stmt_expr '|' exclusive_or_stmt_expr  */
#line 3608 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11811 "parser_bison.c"
    break;

  case 593: /* concat_stmt_expr: concat_stmt_expr "." primary_stmt_expr  */
#line 3618 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 11824 "parser_bison.c"
    break;

  case 596: /* map_stmt_expr: concat_stmt_expr "map" map_stmt_expr_set  */
#line 3633 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11832 "parser_bison.c"
    break;

  case 597: /* map_stmt_expr: concat_stmt_expr  */
#line 3636 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 11838 "parser_bison.c"
    break;

  case 598: /* prefix_stmt_expr: basic_stmt_expr "/" "number"  */
#line 3640 "parser_bison.y"
                        {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 11846 "parser_bison.c"
    break;

  case 599: /* range_stmt_expr: basic_stmt_expr "-" basic_stmt_expr  */
#line 3646 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11854 "parser_bison.c"
    break;

  case 605: /* nat_stmt_args: stmt_expr  */
#line 3661 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 11862 "parser_bison.c"
    break;

  case 606: /* nat_stmt_args: "to" stmt_expr  */
#line 3665 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 11870 "parser_bison.c"
    break;

  case 607: /* nat_stmt_args: nf_key_proto "to" stmt_expr  */
#line 3669 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 11879 "parser_bison.c"
    break;

  case 608: /* nat_stmt_args: stmt_expr "colon" stmt_expr  */
#line 3674 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11888 "parser_bison.c"
    break;

  case 609: /* nat_stmt_args: "to" stmt_expr "colon" stmt_expr  */
#line 3679 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11897 "parser_bison.c"
    break;

  case 610: /* nat_stmt_args: nf_key_proto "to" stmt_expr "colon" stmt_expr  */
#line 3684 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11907 "parser_bison.c"
    break;

  case 611: /* nat_stmt_args: "colon" stmt_expr  */
#line 3690 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11915 "parser_bison.c"
    break;

  case 612: /* nat_stmt_args: "to" "colon" stmt_expr  */
#line 3694 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11923 "parser_bison.c"
    break;

  case 613: /* nat_stmt_args: nat_stmt_args nf_nat_flags  */
#line 3698 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 11931 "parser_bison.c"
    break;

  case 614: /* nat_stmt_args: nf_key_proto "addr" "." "port" "to" stmt_expr  */
#line 3702 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.type_flags = STMT_NAT_F_CONCAT;
			}
#line 11941 "parser_bison.c"
    break;

  case 615: /* nat_stmt_args: nf_key_proto "interval" "to" stmt_expr  */
#line 3708 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 11950 "parser_bison.c"
    break;

  case 616: /* nat_stmt_args: "interval" "to" stmt_expr  */
#line 3713 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 11958 "parser_bison.c"
    break;

  case 617: /* nat_stmt_args: nf_key_proto "prefix" "to" stmt_expr  */
#line 3717 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-4].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 11970 "parser_bison.c"
    break;

  case 618: /* nat_stmt_args: "prefix" "to" stmt_expr  */
#line 3725 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-3].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 11981 "parser_bison.c"
    break;

  case 621: /* masq_stmt_alloc: "masquerade"  */
#line 3737 "parser_bison.y"
                                                { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 11987 "parser_bison.c"
    break;

  case 622: /* masq_stmt_args: "to" "colon" stmt_expr  */
#line 3741 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 11995 "parser_bison.c"
    break;

  case 623: /* masq_stmt_args: "to" "colon" stmt_expr nf_nat_flags  */
#line 3745 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12004 "parser_bison.c"
    break;

  case 624: /* masq_stmt_args: nf_nat_flags  */
#line 3750 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12012 "parser_bison.c"
    break;

  case 627: /* redir_stmt_alloc: "redirect"  */
#line 3759 "parser_bison.y"
                                                { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 12018 "parser_bison.c"
    break;

  case 628: /* redir_stmt_arg: "to" stmt_expr  */
#line 3763 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12026 "parser_bison.c"
    break;

  case 629: /* redir_stmt_arg: "to" "colon" stmt_expr  */
#line 3767 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12034 "parser_bison.c"
    break;

  case 630: /* redir_stmt_arg: nf_nat_flags  */
#line 3771 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12042 "parser_bison.c"
    break;

  case 631: /* redir_stmt_arg: "to" stmt_expr nf_nat_flags  */
#line 3775 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12051 "parser_bison.c"
    break;

  case 632: /* redir_stmt_arg: "to" "colon" stmt_expr nf_nat_flags  */
#line 3780 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12060 "parser_bison.c"
    break;

  case 633: /* dup_stmt: "dup" "to" stmt_expr  */
#line 3787 "parser_bison.y"
                        {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 12069 "parser_bison.c"
    break;

  case 634: /* dup_stmt: "dup" "to" stmt_expr "device" stmt_expr  */
#line 3792 "parser_bison.y"
                        {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 12079 "parser_bison.c"
    break;

  case 635: /* fwd_stmt: "fwd" "to" stmt_expr  */
#line 3800 "parser_bison.y"
                        {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 12088 "parser_bison.c"
    break;

  case 636: /* fwd_stmt: "fwd" nf_key_proto "to" stmt_expr "device" stmt_expr  */
#line 3805 "parser_bison.y"
                        {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 12099 "parser_bison.c"
    break;

  case 638: /* nf_nat_flags: nf_nat_flags "comma" nf_nat_flag  */
#line 3815 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 12107 "parser_bison.c"
    break;

  case 639: /* nf_nat_flag: "random"  */
#line 3820 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 12113 "parser_bison.c"
    break;

  case 640: /* nf_nat_flag: "fully-random"  */
#line 3821 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 12119 "parser_bison.c"
    break;

  case 641: /* nf_nat_flag: "persistent"  */
#line 3822 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 12125 "parser_bison.c"
    break;

  case 643: /* queue_stmt: "queue" "to" queue_stmt_expr close_scope_queue  */
#line 3827 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), 0);
			}
#line 12133 "parser_bison.c"
    break;

  case 644: /* queue_stmt: "queue" "flags" queue_stmt_flags "to" queue_stmt_expr close_scope_queue  */
#line 3831 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 12141 "parser_bison.c"
    break;

  case 645: /* queue_stmt: "queue" "flags" queue_stmt_flags "num" queue_stmt_expr_simple close_scope_queue  */
#line 3835 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 12149 "parser_bison.c"
    break;

  case 648: /* queue_stmt_alloc: "queue"  */
#line 3845 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), NULL, 0);
			}
#line 12157 "parser_bison.c"
    break;

  case 649: /* queue_stmt_args: queue_stmt_arg  */
#line 3851 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 12165 "parser_bison.c"
    break;

  case 651: /* queue_stmt_arg: "num" queue_stmt_expr_simple  */
#line 3858 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 12174 "parser_bison.c"
    break;

  case 652: /* queue_stmt_arg: queue_stmt_flags  */
#line 3863 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 12182 "parser_bison.c"
    break;

  case 657: /* queue_stmt_expr_simple: queue_expr "-" queue_expr  */
#line 3875 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12190 "parser_bison.c"
    break;

  case 663: /* queue_stmt_flags: queue_stmt_flags "comma" queue_stmt_flag  */
#line 3888 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 12198 "parser_bison.c"
    break;

  case 664: /* queue_stmt_flag: "bypass"  */
#line 3893 "parser_bison.y"
                                        { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 12204 "parser_bison.c"
    break;

  case 665: /* queue_stmt_flag: "fanout"  */
#line 3894 "parser_bison.y"
                                        { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 12210 "parser_bison.c"
    break;

  case 668: /* set_elem_expr_stmt_alloc: concat_expr  */
#line 3902 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 12218 "parser_bison.c"
    break;

  case 669: /* set_stmt: "set" set_stmt_op set_elem_expr_stmt set_ref_expr  */
#line 3908 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 12229 "parser_bison.c"
    break;

  case 670: /* set_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt '}'  */
#line 3915 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 12240 "parser_bison.c"
    break;

  case 671: /* set_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt stateful_stmt_list '}'  */
#line 3922 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				list_splice_tail((yyvsp[-1].list), &(yyval.stmt)->set.stmt_list);
				free((yyvsp[-1].list));
			}
#line 12253 "parser_bison.c"
    break;

  case 672: /* set_stmt_op: "add"  */
#line 3932 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 12259 "parser_bison.c"
    break;

  case 673: /* set_stmt_op: "update"  */
#line 3933 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 12265 "parser_bison.c"
    break;

  case 674: /* set_stmt_op: "delete"  */
#line 3934 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 12271 "parser_bison.c"
    break;

  case 675: /* map_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt "colon" set_elem_expr_stmt '}'  */
#line 3938 "parser_bison.y"
                        {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 12283 "parser_bison.c"
    break;

  case 676: /* map_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt stateful_stmt_list "colon" set_elem_expr_stmt '}'  */
#line 3946 "parser_bison.y"
                        {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
				list_splice_tail((yyvsp[-3].list), &(yyval.stmt)->map.stmt_list);
				free((yyvsp[-3].list));
			}
#line 12297 "parser_bison.c"
    break;

  case 677: /* meter_stmt: flow_stmt_legacy_alloc flow_stmt_opts '{' meter_key_expr stmt '}'  */
#line 3958 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 12308 "parser_bison.c"
    break;

  case 678: /* meter_stmt: meter_stmt_alloc  */
#line 3964 "parser_bison.y"
                                                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 12314 "parser_bison.c"
    break;

  case 679: /* flow_stmt_legacy_alloc: "flow"  */
#line 3968 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 12322 "parser_bison.c"
    break;

  case 680: /* flow_stmt_opts: flow_stmt_opt  */
#line 3974 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 12330 "parser_bison.c"
    break;

  case 682: /* flow_stmt_opt: "table" identifier  */
#line 3981 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 12338 "parser_bison.c"
    break;

  case 683: /* meter_stmt_alloc: "meter" identifier '{' meter_key_expr stmt '}'  */
#line 3987 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 12351 "parser_bison.c"
    break;

  case 684: /* meter_stmt_alloc: "meter" identifier "size" "number" '{' meter_key_expr stmt '}'  */
#line 3996 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 12364 "parser_bison.c"
    break;

  case 685: /* match_stmt: relational_expr  */
#line 4007 "parser_bison.y"
                        {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 12372 "parser_bison.c"
    break;

  case 686: /* variable_expr: '$' identifier  */
#line 4013 "parser_bison.y"
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
#line 12400 "parser_bison.c"
    break;

  case 688: /* symbol_expr: string  */
#line 4040 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 12411 "parser_bison.c"
    break;

  case 691: /* set_ref_symbol_expr: "@" identifier close_scope_at  */
#line 4053 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[-1].string));
				xfree((yyvsp[-1].string));
			}
#line 12422 "parser_bison.c"
    break;

  case 692: /* integer_expr: "number"  */
#line 4062 "parser_bison.y"
                        {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 12435 "parser_bison.c"
    break;

  case 693: /* primary_expr: symbol_expr  */
#line 4072 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12441 "parser_bison.c"
    break;

  case 694: /* primary_expr: integer_expr  */
#line 4073 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12447 "parser_bison.c"
    break;

  case 695: /* primary_expr: payload_expr  */
#line 4074 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12453 "parser_bison.c"
    break;

  case 696: /* primary_expr: exthdr_expr  */
#line 4075 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12459 "parser_bison.c"
    break;

  case 697: /* primary_expr: exthdr_exists_expr  */
#line 4076 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12465 "parser_bison.c"
    break;

  case 698: /* primary_expr: meta_expr  */
#line 4077 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12471 "parser_bison.c"
    break;

  case 699: /* primary_expr: socket_expr  */
#line 4078 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12477 "parser_bison.c"
    break;

  case 700: /* primary_expr: rt_expr  */
#line 4079 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12483 "parser_bison.c"
    break;

  case 701: /* primary_expr: ct_expr  */
#line 4080 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12489 "parser_bison.c"
    break;

  case 702: /* primary_expr: numgen_expr  */
#line 4081 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12495 "parser_bison.c"
    break;

  case 703: /* primary_expr: hash_expr  */
#line 4082 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12501 "parser_bison.c"
    break;

  case 704: /* primary_expr: fib_expr  */
#line 4083 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12507 "parser_bison.c"
    break;

  case 705: /* primary_expr: osf_expr  */
#line 4084 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12513 "parser_bison.c"
    break;

  case 706: /* primary_expr: xfrm_expr  */
#line 4085 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12519 "parser_bison.c"
    break;

  case 707: /* primary_expr: '(' basic_expr ')'  */
#line 4086 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 12525 "parser_bison.c"
    break;

  case 708: /* fib_expr: "fib" fib_tuple fib_result close_scope_fib  */
#line 4090 "parser_bison.y"
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
#line 12550 "parser_bison.c"
    break;

  case 709: /* fib_result: "oif"  */
#line 4112 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 12556 "parser_bison.c"
    break;

  case 710: /* fib_result: "oifname"  */
#line 4113 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 12562 "parser_bison.c"
    break;

  case 711: /* fib_result: "type" close_scope_type  */
#line 4114 "parser_bison.y"
                                                                { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 12568 "parser_bison.c"
    break;

  case 712: /* fib_flag: "saddr"  */
#line 4117 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 12574 "parser_bison.c"
    break;

  case 713: /* fib_flag: "daddr"  */
#line 4118 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 12580 "parser_bison.c"
    break;

  case 714: /* fib_flag: "mark"  */
#line 4119 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_MARK; }
#line 12586 "parser_bison.c"
    break;

  case 715: /* fib_flag: "iif"  */
#line 4120 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_IIF; }
#line 12592 "parser_bison.c"
    break;

  case 716: /* fib_flag: "oif"  */
#line 4121 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_OIF; }
#line 12598 "parser_bison.c"
    break;

  case 717: /* fib_tuple: fib_flag "." fib_tuple  */
#line 4125 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 12606 "parser_bison.c"
    break;

  case 719: /* osf_expr: "osf" osf_ttl "version" close_scope_osf  */
#line 4132 "parser_bison.y"
                        {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-2].val), NFT_OSF_F_VERSION);
			}
#line 12614 "parser_bison.c"
    break;

  case 720: /* osf_expr: "osf" osf_ttl "name" close_scope_osf  */
#line 4136 "parser_bison.y"
                        {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-2].val), 0);
			}
#line 12622 "parser_bison.c"
    break;

  case 721: /* osf_ttl: %empty  */
#line 4142 "parser_bison.y"
                        {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 12630 "parser_bison.c"
    break;

  case 722: /* osf_ttl: "ttl" "string"  */
#line 4146 "parser_bison.y"
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
#line 12648 "parser_bison.c"
    break;

  case 724: /* shift_expr: shift_expr "<<" primary_rhs_expr  */
#line 4163 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12656 "parser_bison.c"
    break;

  case 725: /* shift_expr: shift_expr ">>" primary_rhs_expr  */
#line 4167 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12664 "parser_bison.c"
    break;

  case 727: /* and_expr: and_expr "&" shift_rhs_expr  */
#line 4174 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12672 "parser_bison.c"
    break;

  case 729: /* exclusive_or_expr: exclusive_or_expr "^" and_rhs_expr  */
#line 4181 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12680 "parser_bison.c"
    break;

  case 731: /* inclusive_or_expr: inclusive_or_expr '|' exclusive_or_rhs_expr  */
#line 4188 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12688 "parser_bison.c"
    break;

  case 734: /* concat_expr: concat_expr "." basic_expr  */
#line 4198 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 12701 "parser_bison.c"
    break;

  case 735: /* prefix_rhs_expr: basic_rhs_expr "/" "number"  */
#line 4209 "parser_bison.y"
                        {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 12709 "parser_bison.c"
    break;

  case 736: /* range_rhs_expr: basic_rhs_expr "-" basic_rhs_expr  */
#line 4215 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12717 "parser_bison.c"
    break;

  case 739: /* map_expr: concat_expr "map" rhs_expr  */
#line 4225 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12725 "parser_bison.c"
    break;

  case 743: /* set_expr: '{' set_list_expr '}'  */
#line 4236 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 12734 "parser_bison.c"
    break;

  case 744: /* set_list_expr: set_list_member_expr  */
#line 4243 "parser_bison.y"
                        {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 12743 "parser_bison.c"
    break;

  case 745: /* set_list_expr: set_list_expr "comma" set_list_member_expr  */
#line 4248 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 12752 "parser_bison.c"
    break;

  case 747: /* set_list_member_expr: opt_newline set_expr opt_newline  */
#line 4256 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 12760 "parser_bison.c"
    break;

  case 748: /* set_list_member_expr: opt_newline set_elem_expr opt_newline  */
#line 4260 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 12768 "parser_bison.c"
    break;

  case 749: /* set_list_member_expr: opt_newline set_elem_expr "colon" set_rhs_expr opt_newline  */
#line 4264 "parser_bison.y"
                        {
				(yyval.expr) = mapping_expr_alloc(&(yylsp[-3]), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 12776 "parser_bison.c"
    break;

  case 751: /* meter_key_expr: meter_key_expr_alloc set_elem_options  */
#line 4271 "parser_bison.y"
                        {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 12785 "parser_bison.c"
    break;

  case 752: /* meter_key_expr_alloc: concat_expr  */
#line 4278 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 12793 "parser_bison.c"
    break;

  case 755: /* set_elem_key_expr: set_lhs_expr  */
#line 4287 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 12799 "parser_bison.c"
    break;

  case 756: /* set_elem_key_expr: "*"  */
#line 4288 "parser_bison.y"
                                                        { (yyval.expr) = set_elem_catchall_expr_alloc(&(yylsp[0])); }
#line 12805 "parser_bison.c"
    break;

  case 757: /* set_elem_expr_alloc: set_elem_key_expr set_elem_stmt_list  */
#line 4292 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[-1]), (yyvsp[-1].expr));
				list_splice_tail((yyvsp[0].list), &(yyval.expr)->stmt_list);
				xfree((yyvsp[0].list));
			}
#line 12815 "parser_bison.c"
    break;

  case 758: /* set_elem_expr_alloc: set_elem_key_expr  */
#line 4298 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 12823 "parser_bison.c"
    break;

  case 759: /* set_elem_options: set_elem_option  */
#line 4304 "parser_bison.y"
                        {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 12831 "parser_bison.c"
    break;

  case 761: /* set_elem_option: "timeout" time_spec  */
#line 4311 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 12839 "parser_bison.c"
    break;

  case 762: /* set_elem_option: "expires" time_spec  */
#line 4315 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 12847 "parser_bison.c"
    break;

  case 763: /* set_elem_option: comment_spec  */
#line 4319 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 12859 "parser_bison.c"
    break;

  case 764: /* set_elem_expr_options: set_elem_expr_option  */
#line 4329 "parser_bison.y"
                        {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 12867 "parser_bison.c"
    break;

  case 766: /* set_elem_stmt_list: set_elem_stmt  */
#line 4336 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 12877 "parser_bison.c"
    break;

  case 767: /* set_elem_stmt_list: set_elem_stmt_list set_elem_stmt  */
#line 4342 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 12886 "parser_bison.c"
    break;

  case 768: /* set_elem_stmt: "counter" close_scope_counter  */
#line 4349 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 12894 "parser_bison.c"
    break;

  case 769: /* set_elem_stmt: "counter" "packets" "number" "bytes" "number" close_scope_counter  */
#line 4353 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
				(yyval.stmt)->counter.packets = (yyvsp[-3].val);
				(yyval.stmt)->counter.bytes = (yyvsp[-1].val);
			}
#line 12904 "parser_bison.c"
    break;

  case 770: /* set_elem_stmt: "limit" "rate" limit_mode limit_rate_pkts limit_burst_pkts close_scope_limit  */
#line 4359 "parser_bison.y"
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
#line 12922 "parser_bison.c"
    break;

  case 771: /* set_elem_stmt: "limit" "rate" limit_mode limit_rate_bytes limit_burst_bytes close_scope_limit  */
#line 4373 "parser_bison.y"
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
#line 12940 "parser_bison.c"
    break;

  case 772: /* set_elem_stmt: "ct" "count" "number" close_scope_ct  */
#line 4387 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 12949 "parser_bison.c"
    break;

  case 773: /* set_elem_stmt: "ct" "count" "over" "number" close_scope_ct  */
#line 4392 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 12959 "parser_bison.c"
    break;

  case 774: /* set_elem_expr_option: "timeout" time_spec  */
#line 4400 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 12967 "parser_bison.c"
    break;

  case 775: /* set_elem_expr_option: "expires" time_spec  */
#line 4404 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 12975 "parser_bison.c"
    break;

  case 776: /* set_elem_expr_option: comment_spec  */
#line 4408 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 12987 "parser_bison.c"
    break;

  case 782: /* initializer_expr: '{' '}'  */
#line 4426 "parser_bison.y"
                                                { (yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_SET); }
#line 12993 "parser_bison.c"
    break;

  case 783: /* initializer_expr: "-" "number"  */
#line 4428 "parser_bison.y"
                        {
				int32_t num = -(yyvsp[0].val);

				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(num) * BITS_PER_BYTE,
							 &num);
			}
#line 13006 "parser_bison.c"
    break;

  case 784: /* counter_config: "packets" "number" "bytes" "number"  */
#line 4439 "parser_bison.y"
                        {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 13018 "parser_bison.c"
    break;

  case 785: /* counter_obj: %empty  */
#line 4449 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 13027 "parser_bison.c"
    break;

  case 786: /* quota_config: quota_mode "number" quota_unit quota_used  */
#line 4456 "parser_bison.y"
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
#line 13049 "parser_bison.c"
    break;

  case 787: /* quota_obj: %empty  */
#line 4476 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 13058 "parser_bison.c"
    break;

  case 788: /* secmark_config: string  */
#line 4483 "parser_bison.y"
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
#line 13076 "parser_bison.c"
    break;

  case 789: /* secmark_obj: %empty  */
#line 4499 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 13085 "parser_bison.c"
    break;

  case 790: /* ct_obj_type: "helper"  */
#line 4505 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 13091 "parser_bison.c"
    break;

  case 791: /* ct_obj_type: "timeout"  */
#line 4506 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 13097 "parser_bison.c"
    break;

  case 792: /* ct_obj_type: "expectation"  */
#line 4507 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 13103 "parser_bison.c"
    break;

  case 793: /* ct_cmd_type: "helpers"  */
#line 4510 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_HELPERS; }
#line 13109 "parser_bison.c"
    break;

  case 794: /* ct_cmd_type: "timeout"  */
#line 4511 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_TIMEOUT; }
#line 13115 "parser_bison.c"
    break;

  case 795: /* ct_cmd_type: "expectation"  */
#line 4512 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_EXPECT; }
#line 13121 "parser_bison.c"
    break;

  case 796: /* ct_l4protoname: "tcp" close_scope_tcp  */
#line 4515 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_TCP; }
#line 13127 "parser_bison.c"
    break;

  case 797: /* ct_l4protoname: "udp" close_scope_udp  */
#line 4516 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_UDP; }
#line 13133 "parser_bison.c"
    break;

  case 798: /* ct_helper_config: "type" "quoted string" "protocol" ct_l4protoname stmt_separator close_scope_type  */
#line 4520 "parser_bison.y"
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
#line 13153 "parser_bison.c"
    break;

  case 799: /* ct_helper_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4536 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 13161 "parser_bison.c"
    break;

  case 800: /* timeout_states: timeout_state  */
#line 4542 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 13171 "parser_bison.c"
    break;

  case 801: /* timeout_states: timeout_states "comma" timeout_state  */
#line 4548 "parser_bison.y"
                        {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 13180 "parser_bison.c"
    break;

  case 802: /* timeout_state: "string" "colon" "number"  */
#line 4556 "parser_bison.y"
                        {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 13195 "parser_bison.c"
    break;

  case 803: /* ct_timeout_config: "protocol" ct_l4protoname stmt_separator  */
#line 4569 "parser_bison.y"
                        {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 13207 "parser_bison.c"
    break;

  case 804: /* ct_timeout_config: "policy" '=' '{' timeout_states '}' stmt_separator close_scope_policy  */
#line 4577 "parser_bison.y"
                        {
				struct ct_timeout *ct;

				ct = &(yyvsp[-7].obj)->ct_timeout;
				list_splice_tail((yyvsp[-3].list), &ct->timeout_list);
				xfree((yyvsp[-3].list));
			}
#line 13219 "parser_bison.c"
    break;

  case 805: /* ct_timeout_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4585 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 13227 "parser_bison.c"
    break;

  case 806: /* ct_expect_config: "protocol" ct_l4protoname stmt_separator  */
#line 4591 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 13235 "parser_bison.c"
    break;

  case 807: /* ct_expect_config: "dport" "number" stmt_separator  */
#line 4595 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 13243 "parser_bison.c"
    break;

  case 808: /* ct_expect_config: "timeout" time_spec stmt_separator  */
#line 4599 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 13251 "parser_bison.c"
    break;

  case 809: /* ct_expect_config: "size" "number" stmt_separator  */
#line 4603 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 13259 "parser_bison.c"
    break;

  case 810: /* ct_expect_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4607 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 13267 "parser_bison.c"
    break;

  case 811: /* ct_obj_alloc: %empty  */
#line 4613 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 13275 "parser_bison.c"
    break;

  case 812: /* limit_config: "rate" limit_mode limit_rate_pkts limit_burst_pkts  */
#line 4619 "parser_bison.y"
                        {
				struct limit *limit;

				limit = &(yyvsp[-4].obj)->limit;
				limit->rate	= (yyvsp[-1].limit_rate).rate;
				limit->unit	= (yyvsp[-1].limit_rate).unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-2].val);
			}
#line 13290 "parser_bison.c"
    break;

  case 813: /* limit_config: "rate" limit_mode limit_rate_bytes limit_burst_bytes  */
#line 4630 "parser_bison.y"
                        {
				struct limit *limit;

				limit = &(yyvsp[-4].obj)->limit;
				limit->rate	= (yyvsp[-1].limit_rate).rate;
				limit->unit	= (yyvsp[-1].limit_rate).unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKT_BYTES;
				limit->flags	= (yyvsp[-2].val);
			}
#line 13305 "parser_bison.c"
    break;

  case 814: /* limit_obj: %empty  */
#line 4643 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 13314 "parser_bison.c"
    break;

  case 815: /* relational_expr: expr rhs_expr  */
#line 4650 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 13322 "parser_bison.c"
    break;

  case 816: /* relational_expr: expr list_rhs_expr  */
#line 4654 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 13330 "parser_bison.c"
    break;

  case 817: /* relational_expr: expr basic_rhs_expr "/" list_rhs_expr  */
#line 4658 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 13338 "parser_bison.c"
    break;

  case 818: /* relational_expr: expr list_rhs_expr "/" list_rhs_expr  */
#line 4662 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 13346 "parser_bison.c"
    break;

  case 819: /* relational_expr: expr relational_op basic_rhs_expr "/" list_rhs_expr  */
#line 4666 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 13354 "parser_bison.c"
    break;

  case 820: /* relational_expr: expr relational_op list_rhs_expr "/" list_rhs_expr  */
#line 4670 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 13362 "parser_bison.c"
    break;

  case 821: /* relational_expr: expr relational_op rhs_expr  */
#line 4674 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13370 "parser_bison.c"
    break;

  case 822: /* relational_expr: expr relational_op list_rhs_expr  */
#line 4678 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13378 "parser_bison.c"
    break;

  case 823: /* list_rhs_expr: basic_rhs_expr "comma" basic_rhs_expr  */
#line 4684 "parser_bison.y"
                        {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 13388 "parser_bison.c"
    break;

  case 824: /* list_rhs_expr: list_rhs_expr "comma" basic_rhs_expr  */
#line 4690 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 13398 "parser_bison.c"
    break;

  case 825: /* rhs_expr: concat_rhs_expr  */
#line 4697 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13404 "parser_bison.c"
    break;

  case 826: /* rhs_expr: set_expr  */
#line 4698 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13410 "parser_bison.c"
    break;

  case 827: /* rhs_expr: set_ref_symbol_expr  */
#line 4699 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13416 "parser_bison.c"
    break;

  case 829: /* shift_rhs_expr: shift_rhs_expr "<<" primary_rhs_expr  */
#line 4704 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13424 "parser_bison.c"
    break;

  case 830: /* shift_rhs_expr: shift_rhs_expr ">>" primary_rhs_expr  */
#line 4708 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13432 "parser_bison.c"
    break;

  case 832: /* and_rhs_expr: and_rhs_expr "&" shift_rhs_expr  */
#line 4715 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13440 "parser_bison.c"
    break;

  case 834: /* exclusive_or_rhs_expr: exclusive_or_rhs_expr "^" and_rhs_expr  */
#line 4722 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13448 "parser_bison.c"
    break;

  case 836: /* inclusive_or_rhs_expr: inclusive_or_rhs_expr '|' exclusive_or_rhs_expr  */
#line 4729 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13456 "parser_bison.c"
    break;

  case 840: /* concat_rhs_expr: concat_rhs_expr "." multiton_rhs_expr  */
#line 4740 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 13469 "parser_bison.c"
    break;

  case 841: /* concat_rhs_expr: concat_rhs_expr "." basic_rhs_expr  */
#line 4749 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 13482 "parser_bison.c"
    break;

  case 842: /* boolean_keys: "exists"  */
#line 4759 "parser_bison.y"
                                                { (yyval.val8) = true; }
#line 13488 "parser_bison.c"
    break;

  case 843: /* boolean_keys: "missing"  */
#line 4760 "parser_bison.y"
                                                { (yyval.val8) = false; }
#line 13494 "parser_bison.c"
    break;

  case 844: /* boolean_expr: boolean_keys  */
#line 4764 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 13504 "parser_bison.c"
    break;

  case 845: /* keyword_expr: "ether" close_scope_eth  */
#line 4771 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 13510 "parser_bison.c"
    break;

  case 846: /* keyword_expr: "ip" close_scope_ip  */
#line 4772 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 13516 "parser_bison.c"
    break;

  case 847: /* keyword_expr: "ip6" close_scope_ip6  */
#line 4773 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 13522 "parser_bison.c"
    break;

  case 848: /* keyword_expr: "vlan" close_scope_vlan  */
#line 4774 "parser_bison.y"
                                                         { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 13528 "parser_bison.c"
    break;

  case 849: /* keyword_expr: "arp" close_scope_arp  */
#line 4775 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 13534 "parser_bison.c"
    break;

  case 850: /* keyword_expr: "dnat" close_scope_nat  */
#line 4776 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 13540 "parser_bison.c"
    break;

  case 851: /* keyword_expr: "snat" close_scope_nat  */
#line 4777 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 13546 "parser_bison.c"
    break;

  case 852: /* keyword_expr: "ecn"  */
#line 4778 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 13552 "parser_bison.c"
    break;

  case 853: /* keyword_expr: "reset" close_scope_reset  */
#line 4779 "parser_bison.y"
                                                                { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 13558 "parser_bison.c"
    break;

  case 854: /* keyword_expr: "original"  */
#line 4780 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 13564 "parser_bison.c"
    break;

  case 855: /* keyword_expr: "reply"  */
#line 4781 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 13570 "parser_bison.c"
    break;

  case 856: /* keyword_expr: "label"  */
#line 4782 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 13576 "parser_bison.c"
    break;

  case 857: /* primary_rhs_expr: symbol_expr  */
#line 4785 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13582 "parser_bison.c"
    break;

  case 858: /* primary_rhs_expr: integer_expr  */
#line 4786 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13588 "parser_bison.c"
    break;

  case 859: /* primary_rhs_expr: boolean_expr  */
#line 4787 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13594 "parser_bison.c"
    break;

  case 860: /* primary_rhs_expr: keyword_expr  */
#line 4788 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13600 "parser_bison.c"
    break;

  case 861: /* primary_rhs_expr: "tcp" close_scope_tcp  */
#line 4790 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13611 "parser_bison.c"
    break;

  case 862: /* primary_rhs_expr: "udp" close_scope_udp  */
#line 4797 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13622 "parser_bison.c"
    break;

  case 863: /* primary_rhs_expr: "udplite" close_scope_udplite  */
#line 4804 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13633 "parser_bison.c"
    break;

  case 864: /* primary_rhs_expr: "esp" close_scope_esp  */
#line 4811 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13644 "parser_bison.c"
    break;

  case 865: /* primary_rhs_expr: "ah" close_scope_ah  */
#line 4818 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13655 "parser_bison.c"
    break;

  case 866: /* primary_rhs_expr: "icmp" close_scope_icmp  */
#line 4825 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13666 "parser_bison.c"
    break;

  case 867: /* primary_rhs_expr: "igmp"  */
#line 4832 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13677 "parser_bison.c"
    break;

  case 868: /* primary_rhs_expr: "icmpv6" close_scope_icmp  */
#line 4839 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13688 "parser_bison.c"
    break;

  case 869: /* primary_rhs_expr: "comp" close_scope_comp  */
#line 4846 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13699 "parser_bison.c"
    break;

  case 870: /* primary_rhs_expr: "dccp" close_scope_dccp  */
#line 4853 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13710 "parser_bison.c"
    break;

  case 871: /* primary_rhs_expr: "sctp" close_scope_sctp  */
#line 4860 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13721 "parser_bison.c"
    break;

  case 872: /* primary_rhs_expr: "redirect" close_scope_nat  */
#line 4867 "parser_bison.y"
                        {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 13732 "parser_bison.c"
    break;

  case 873: /* primary_rhs_expr: '(' basic_rhs_expr ')'  */
#line 4873 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 13738 "parser_bison.c"
    break;

  case 874: /* relational_op: "=="  */
#line 4876 "parser_bison.y"
                                                { (yyval.val) = OP_EQ; }
#line 13744 "parser_bison.c"
    break;

  case 875: /* relational_op: "!="  */
#line 4877 "parser_bison.y"
                                                { (yyval.val) = OP_NEQ; }
#line 13750 "parser_bison.c"
    break;

  case 876: /* relational_op: "<"  */
#line 4878 "parser_bison.y"
                                                { (yyval.val) = OP_LT; }
#line 13756 "parser_bison.c"
    break;

  case 877: /* relational_op: ">"  */
#line 4879 "parser_bison.y"
                                                { (yyval.val) = OP_GT; }
#line 13762 "parser_bison.c"
    break;

  case 878: /* relational_op: ">="  */
#line 4880 "parser_bison.y"
                                                { (yyval.val) = OP_GTE; }
#line 13768 "parser_bison.c"
    break;

  case 879: /* relational_op: "<="  */
#line 4881 "parser_bison.y"
                                                { (yyval.val) = OP_LTE; }
#line 13774 "parser_bison.c"
    break;

  case 880: /* relational_op: "!"  */
#line 4882 "parser_bison.y"
                                                { (yyval.val) = OP_NEG; }
#line 13780 "parser_bison.c"
    break;

  case 881: /* verdict_expr: "accept"  */
#line 4886 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 13788 "parser_bison.c"
    break;

  case 882: /* verdict_expr: "drop"  */
#line 4890 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 13796 "parser_bison.c"
    break;

  case 883: /* verdict_expr: "continue"  */
#line 4894 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 13804 "parser_bison.c"
    break;

  case 884: /* verdict_expr: "jump" chain_expr  */
#line 4898 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 13812 "parser_bison.c"
    break;

  case 885: /* verdict_expr: "goto" chain_expr  */
#line 4902 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 13820 "parser_bison.c"
    break;

  case 886: /* verdict_expr: "return"  */
#line 4906 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 13828 "parser_bison.c"
    break;

  case 888: /* chain_expr: identifier  */
#line 4913 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 13840 "parser_bison.c"
    break;

  case 889: /* meta_expr: "meta" meta_key close_scope_meta  */
#line 4923 "parser_bison.y"
                        {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[-1].val));
			}
#line 13848 "parser_bison.c"
    break;

  case 890: /* meta_expr: meta_key_unqualified  */
#line 4927 "parser_bison.y"
                        {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 13856 "parser_bison.c"
    break;

  case 891: /* meta_expr: "meta" "string" close_scope_meta  */
#line 4931 "parser_bison.y"
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
#line 13874 "parser_bison.c"
    break;

  case 894: /* meta_key_qualified: "length"  */
#line 4950 "parser_bison.y"
                                                { (yyval.val) = NFT_META_LEN; }
#line 13880 "parser_bison.c"
    break;

  case 895: /* meta_key_qualified: "protocol"  */
#line 4951 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PROTOCOL; }
#line 13886 "parser_bison.c"
    break;

  case 896: /* meta_key_qualified: "priority"  */
#line 4952 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PRIORITY; }
#line 13892 "parser_bison.c"
    break;

  case 897: /* meta_key_qualified: "random"  */
#line 4953 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PRANDOM; }
#line 13898 "parser_bison.c"
    break;

  case 898: /* meta_key_qualified: "secmark" close_scope_secmark  */
#line 4954 "parser_bison.y"
                                                            { (yyval.val) = NFT_META_SECMARK; }
#line 13904 "parser_bison.c"
    break;

  case 899: /* meta_key_unqualified: "mark"  */
#line 4957 "parser_bison.y"
                                                { (yyval.val) = NFT_META_MARK; }
#line 13910 "parser_bison.c"
    break;

  case 900: /* meta_key_unqualified: "iif"  */
#line 4958 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIF; }
#line 13916 "parser_bison.c"
    break;

  case 901: /* meta_key_unqualified: "iifname"  */
#line 4959 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFNAME; }
#line 13922 "parser_bison.c"
    break;

  case 902: /* meta_key_unqualified: "iiftype"  */
#line 4960 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFTYPE; }
#line 13928 "parser_bison.c"
    break;

  case 903: /* meta_key_unqualified: "oif"  */
#line 4961 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIF; }
#line 13934 "parser_bison.c"
    break;

  case 904: /* meta_key_unqualified: "oifname"  */
#line 4962 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFNAME; }
#line 13940 "parser_bison.c"
    break;

  case 905: /* meta_key_unqualified: "oiftype"  */
#line 4963 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFTYPE; }
#line 13946 "parser_bison.c"
    break;

  case 906: /* meta_key_unqualified: "skuid"  */
#line 4964 "parser_bison.y"
                                                { (yyval.val) = NFT_META_SKUID; }
#line 13952 "parser_bison.c"
    break;

  case 907: /* meta_key_unqualified: "skgid"  */
#line 4965 "parser_bison.y"
                                                { (yyval.val) = NFT_META_SKGID; }
#line 13958 "parser_bison.c"
    break;

  case 908: /* meta_key_unqualified: "nftrace"  */
#line 4966 "parser_bison.y"
                                                { (yyval.val) = NFT_META_NFTRACE; }
#line 13964 "parser_bison.c"
    break;

  case 909: /* meta_key_unqualified: "rtclassid"  */
#line 4967 "parser_bison.y"
                                                { (yyval.val) = NFT_META_RTCLASSID; }
#line 13970 "parser_bison.c"
    break;

  case 910: /* meta_key_unqualified: "ibriport"  */
#line 4968 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 13976 "parser_bison.c"
    break;

  case 911: /* meta_key_unqualified: "obriport"  */
#line 4969 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 13982 "parser_bison.c"
    break;

  case 912: /* meta_key_unqualified: "ibrname"  */
#line 4970 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 13988 "parser_bison.c"
    break;

  case 913: /* meta_key_unqualified: "obrname"  */
#line 4971 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 13994 "parser_bison.c"
    break;

  case 914: /* meta_key_unqualified: "pkttype"  */
#line 4972 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PKTTYPE; }
#line 14000 "parser_bison.c"
    break;

  case 915: /* meta_key_unqualified: "cpu"  */
#line 4973 "parser_bison.y"
                                                { (yyval.val) = NFT_META_CPU; }
#line 14006 "parser_bison.c"
    break;

  case 916: /* meta_key_unqualified: "iifgroup"  */
#line 4974 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFGROUP; }
#line 14012 "parser_bison.c"
    break;

  case 917: /* meta_key_unqualified: "oifgroup"  */
#line 4975 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFGROUP; }
#line 14018 "parser_bison.c"
    break;

  case 918: /* meta_key_unqualified: "cgroup"  */
#line 4976 "parser_bison.y"
                                                { (yyval.val) = NFT_META_CGROUP; }
#line 14024 "parser_bison.c"
    break;

  case 919: /* meta_key_unqualified: "ipsec" close_scope_ipsec  */
#line 4977 "parser_bison.y"
                                                          { (yyval.val) = NFT_META_SECPATH; }
#line 14030 "parser_bison.c"
    break;

  case 920: /* meta_key_unqualified: "time"  */
#line 4978 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_NS; }
#line 14036 "parser_bison.c"
    break;

  case 921: /* meta_key_unqualified: "day"  */
#line 4979 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_DAY; }
#line 14042 "parser_bison.c"
    break;

  case 922: /* meta_key_unqualified: "hour"  */
#line 4980 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_HOUR; }
#line 14048 "parser_bison.c"
    break;

  case 923: /* meta_stmt: "meta" meta_key "set" stmt_expr close_scope_meta  */
#line 4984 "parser_bison.y"
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
#line 14072 "parser_bison.c"
    break;

  case 924: /* meta_stmt: meta_key_unqualified "set" stmt_expr  */
#line 5004 "parser_bison.y"
                        {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 14080 "parser_bison.c"
    break;

  case 925: /* meta_stmt: "meta" "string" "set" stmt_expr close_scope_meta  */
#line 5008 "parser_bison.y"
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
#line 14098 "parser_bison.c"
    break;

  case 926: /* meta_stmt: "notrack"  */
#line 5022 "parser_bison.y"
                        {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 14106 "parser_bison.c"
    break;

  case 927: /* meta_stmt: "flow" "offload" "@" string close_scope_at  */
#line 5026 "parser_bison.y"
                        {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[-1].string));
			}
#line 14114 "parser_bison.c"
    break;

  case 928: /* meta_stmt: "flow" "add" "@" string close_scope_at  */
#line 5030 "parser_bison.y"
                        {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[-1].string));
			}
#line 14122 "parser_bison.c"
    break;

  case 929: /* socket_expr: "socket" socket_key close_scope_socket  */
#line 5036 "parser_bison.y"
                        {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 14130 "parser_bison.c"
    break;

  case 930: /* socket_expr: "socket" "cgroupv2" "level" "number" close_scope_socket  */
#line 5040 "parser_bison.y"
                        {
				(yyval.expr) = socket_expr_alloc(&(yyloc), NFT_SOCKET_CGROUPV2, (yyvsp[-1].val));
			}
#line 14138 "parser_bison.c"
    break;

  case 931: /* socket_key: "transparent"  */
#line 5045 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 14144 "parser_bison.c"
    break;

  case 932: /* socket_key: "mark"  */
#line 5046 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_MARK; }
#line 14150 "parser_bison.c"
    break;

  case 933: /* socket_key: "wildcard"  */
#line 5047 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_WILDCARD; }
#line 14156 "parser_bison.c"
    break;

  case 934: /* offset_opt: %empty  */
#line 5050 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 14162 "parser_bison.c"
    break;

  case 935: /* offset_opt: "offset" "number"  */
#line 5051 "parser_bison.y"
                                                { (yyval.val) = (yyvsp[0].val); }
#line 14168 "parser_bison.c"
    break;

  case 936: /* numgen_type: "inc"  */
#line 5054 "parser_bison.y"
                                                { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 14174 "parser_bison.c"
    break;

  case 937: /* numgen_type: "random"  */
#line 5055 "parser_bison.y"
                                                { (yyval.val) = NFT_NG_RANDOM; }
#line 14180 "parser_bison.c"
    break;

  case 938: /* numgen_expr: "numgen" numgen_type "mod" "number" offset_opt close_scope_numgen  */
#line 5059 "parser_bison.y"
                        {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 14188 "parser_bison.c"
    break;

  case 939: /* xfrm_spnum: "spnum" "number"  */
#line 5064 "parser_bison.y"
                                            { (yyval.val) = (yyvsp[0].val); }
#line 14194 "parser_bison.c"
    break;

  case 940: /* xfrm_spnum: %empty  */
#line 5065 "parser_bison.y"
                                            { (yyval.val) = 0; }
#line 14200 "parser_bison.c"
    break;

  case 941: /* xfrm_dir: "in"  */
#line 5068 "parser_bison.y"
                                        { (yyval.val) = XFRM_POLICY_IN; }
#line 14206 "parser_bison.c"
    break;

  case 942: /* xfrm_dir: "out"  */
#line 5069 "parser_bison.y"
                                        { (yyval.val) = XFRM_POLICY_OUT; }
#line 14212 "parser_bison.c"
    break;

  case 943: /* xfrm_state_key: "spi"  */
#line 5072 "parser_bison.y"
                                    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 14218 "parser_bison.c"
    break;

  case 944: /* xfrm_state_key: "reqid"  */
#line 5073 "parser_bison.y"
                                      { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 14224 "parser_bison.c"
    break;

  case 945: /* xfrm_state_proto_key: "daddr"  */
#line 5076 "parser_bison.y"
                                                { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 14230 "parser_bison.c"
    break;

  case 946: /* xfrm_state_proto_key: "saddr"  */
#line 5077 "parser_bison.y"
                                                { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 14236 "parser_bison.c"
    break;

  case 947: /* xfrm_expr: "ipsec" xfrm_dir xfrm_spnum xfrm_state_key close_scope_ipsec  */
#line 5081 "parser_bison.y"
                        {
				if ((yyvsp[-2].val) > 255) {
					erec_queue(error(&(yylsp[-2]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 14248 "parser_bison.c"
    break;

  case 948: /* xfrm_expr: "ipsec" xfrm_dir xfrm_spnum nf_key_proto xfrm_state_proto_key close_scope_ipsec  */
#line 5089 "parser_bison.y"
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
#line 14277 "parser_bison.c"
    break;

  case 949: /* hash_expr: "jhash" expr "mod" "number" "seed" "number" offset_opt close_scope_hash  */
#line 5116 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-4].val), true, (yyvsp[-2].val), (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-6].expr);
			}
#line 14286 "parser_bison.c"
    break;

  case 950: /* hash_expr: "jhash" expr "mod" "number" offset_opt close_scope_hash  */
#line 5121 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-4].expr);
			}
#line 14295 "parser_bison.c"
    break;

  case 951: /* hash_expr: "symhash" "mod" "number" offset_opt close_scope_hash  */
#line 5126 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_SYM);
			}
#line 14303 "parser_bison.c"
    break;

  case 952: /* nf_key_proto: "ip" close_scope_ip  */
#line 5131 "parser_bison.y"
                                                       { (yyval.val) = NFPROTO_IPV4; }
#line 14309 "parser_bison.c"
    break;

  case 953: /* nf_key_proto: "ip6" close_scope_ip6  */
#line 5132 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV6; }
#line 14315 "parser_bison.c"
    break;

  case 954: /* rt_expr: "rt" rt_key close_scope_rt  */
#line 5136 "parser_bison.y"
                        {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[-1].val), true);
			}
#line 14323 "parser_bison.c"
    break;

  case 955: /* rt_expr: "rt" nf_key_proto rt_key close_scope_rt  */
#line 5140 "parser_bison.y"
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
#line 14345 "parser_bison.c"
    break;

  case 956: /* rt_key: "classid"  */
#line 5159 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_CLASSID; }
#line 14351 "parser_bison.c"
    break;

  case 957: /* rt_key: "nexthop"  */
#line 5160 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 14357 "parser_bison.c"
    break;

  case 958: /* rt_key: "mtu"  */
#line 5161 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_TCPMSS; }
#line 14363 "parser_bison.c"
    break;

  case 959: /* rt_key: "ipsec" close_scope_ipsec  */
#line 5162 "parser_bison.y"
                                                          { (yyval.val) = NFT_RT_XFRM; }
#line 14369 "parser_bison.c"
    break;

  case 960: /* ct_expr: "ct" ct_key close_scope_ct  */
#line 5166 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), -1);
			}
#line 14377 "parser_bison.c"
    break;

  case 961: /* ct_expr: "ct" ct_dir ct_key_dir close_scope_ct  */
#line 5170 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 14385 "parser_bison.c"
    break;

  case 962: /* ct_expr: "ct" ct_dir ct_key_proto_field close_scope_ct  */
#line 5174 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 14393 "parser_bison.c"
    break;

  case 963: /* ct_dir: "original"  */
#line 5179 "parser_bison.y"
                                                { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 14399 "parser_bison.c"
    break;

  case 964: /* ct_dir: "reply"  */
#line 5180 "parser_bison.y"
                                                { (yyval.val) = IP_CT_DIR_REPLY; }
#line 14405 "parser_bison.c"
    break;

  case 965: /* ct_key: "l3proto"  */
#line 5183 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 14411 "parser_bison.c"
    break;

  case 966: /* ct_key: "protocol"  */
#line 5184 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTOCOL; }
#line 14417 "parser_bison.c"
    break;

  case 967: /* ct_key: "mark"  */
#line 5185 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_MARK; }
#line 14423 "parser_bison.c"
    break;

  case 968: /* ct_key: "state"  */
#line 5186 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_STATE; }
#line 14429 "parser_bison.c"
    break;

  case 969: /* ct_key: "direction"  */
#line 5187 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DIRECTION; }
#line 14435 "parser_bison.c"
    break;

  case 970: /* ct_key: "status"  */
#line 5188 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_STATUS; }
#line 14441 "parser_bison.c"
    break;

  case 971: /* ct_key: "expiration"  */
#line 5189 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_EXPIRATION; }
#line 14447 "parser_bison.c"
    break;

  case 972: /* ct_key: "helper"  */
#line 5190 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_HELPER; }
#line 14453 "parser_bison.c"
    break;

  case 973: /* ct_key: "saddr"  */
#line 5191 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_SRC; }
#line 14459 "parser_bison.c"
    break;

  case 974: /* ct_key: "daddr"  */
#line 5192 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DST; }
#line 14465 "parser_bison.c"
    break;

  case 975: /* ct_key: "proto-src"  */
#line 5193 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 14471 "parser_bison.c"
    break;

  case 976: /* ct_key: "proto-dst"  */
#line 5194 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_DST; }
#line 14477 "parser_bison.c"
    break;

  case 977: /* ct_key: "label"  */
#line 5195 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_LABELS; }
#line 14483 "parser_bison.c"
    break;

  case 978: /* ct_key: "event"  */
#line 5196 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_EVENTMASK; }
#line 14489 "parser_bison.c"
    break;

  case 979: /* ct_key: "secmark" close_scope_secmark  */
#line 5197 "parser_bison.y"
                                                            { (yyval.val) = NFT_CT_SECMARK; }
#line 14495 "parser_bison.c"
    break;

  case 980: /* ct_key: "id"  */
#line 5198 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_ID; }
#line 14501 "parser_bison.c"
    break;

  case 982: /* ct_key_dir: "saddr"  */
#line 5202 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_SRC; }
#line 14507 "parser_bison.c"
    break;

  case 983: /* ct_key_dir: "daddr"  */
#line 5203 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DST; }
#line 14513 "parser_bison.c"
    break;

  case 984: /* ct_key_dir: "l3proto"  */
#line 5204 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 14519 "parser_bison.c"
    break;

  case 985: /* ct_key_dir: "protocol"  */
#line 5205 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTOCOL; }
#line 14525 "parser_bison.c"
    break;

  case 986: /* ct_key_dir: "proto-src"  */
#line 5206 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 14531 "parser_bison.c"
    break;

  case 987: /* ct_key_dir: "proto-dst"  */
#line 5207 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_DST; }
#line 14537 "parser_bison.c"
    break;

  case 989: /* ct_key_proto_field: "ip" "saddr" close_scope_ip  */
#line 5211 "parser_bison.y"
                                                               { (yyval.val) = NFT_CT_SRC_IP; }
#line 14543 "parser_bison.c"
    break;

  case 990: /* ct_key_proto_field: "ip" "daddr" close_scope_ip  */
#line 5212 "parser_bison.y"
                                                               { (yyval.val) = NFT_CT_DST_IP; }
#line 14549 "parser_bison.c"
    break;

  case 991: /* ct_key_proto_field: "ip6" "saddr" close_scope_ip6  */
#line 5213 "parser_bison.y"
                                                                { (yyval.val) = NFT_CT_SRC_IP6; }
#line 14555 "parser_bison.c"
    break;

  case 992: /* ct_key_proto_field: "ip6" "daddr" close_scope_ip6  */
#line 5214 "parser_bison.y"
                                                                { (yyval.val) = NFT_CT_DST_IP6; }
#line 14561 "parser_bison.c"
    break;

  case 993: /* ct_key_dir_optional: "bytes"  */
#line 5217 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_BYTES; }
#line 14567 "parser_bison.c"
    break;

  case 994: /* ct_key_dir_optional: "packets"  */
#line 5218 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PKTS; }
#line 14573 "parser_bison.c"
    break;

  case 995: /* ct_key_dir_optional: "avgpkt"  */
#line 5219 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_AVGPKT; }
#line 14579 "parser_bison.c"
    break;

  case 996: /* ct_key_dir_optional: "zone"  */
#line 5220 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_ZONE; }
#line 14585 "parser_bison.c"
    break;

  case 999: /* list_stmt_expr: symbol_stmt_expr "comma" symbol_stmt_expr  */
#line 5228 "parser_bison.y"
                        {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 14595 "parser_bison.c"
    break;

  case 1000: /* list_stmt_expr: list_stmt_expr "comma" symbol_stmt_expr  */
#line 5234 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 14605 "parser_bison.c"
    break;

  case 1001: /* ct_stmt: "ct" ct_key "set" stmt_expr close_scope_ct  */
#line 5242 "parser_bison.y"
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
#line 14622 "parser_bison.c"
    break;

  case 1002: /* ct_stmt: "ct" "timeout" "set" stmt_expr close_scope_ct  */
#line 5255 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);

			}
#line 14633 "parser_bison.c"
    break;

  case 1003: /* ct_stmt: "ct" "expectation" "set" stmt_expr close_scope_ct  */
#line 5262 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 14643 "parser_bison.c"
    break;

  case 1004: /* ct_stmt: "ct" ct_dir ct_key_dir_optional "set" stmt_expr close_scope_ct  */
#line 5268 "parser_bison.y"
                        {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].val), (yyvsp[-1].expr));
			}
#line 14651 "parser_bison.c"
    break;

  case 1005: /* payload_stmt: payload_expr "set" stmt_expr  */
#line 5274 "parser_bison.y"
                        {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14662 "parser_bison.c"
    break;

  case 1024: /* payload_raw_expr: "@" payload_base_spec "comma" "number" "comma" "number" close_scope_at  */
#line 5303 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-5].val), (yyvsp[-3].val), (yyvsp[-1].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 14673 "parser_bison.c"
    break;

  case 1025: /* payload_base_spec: "ll"  */
#line 5311 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 14679 "parser_bison.c"
    break;

  case 1026: /* payload_base_spec: "nh"  */
#line 5312 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 14685 "parser_bison.c"
    break;

  case 1027: /* payload_base_spec: "th" close_scope_th  */
#line 5313 "parser_bison.y"
                                                                { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 14691 "parser_bison.c"
    break;

  case 1028: /* payload_base_spec: "string"  */
#line 5315 "parser_bison.y"
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
#line 14706 "parser_bison.c"
    break;

  case 1029: /* eth_hdr_expr: "ether" eth_hdr_field close_scope_eth  */
#line 5328 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[-1].val));
			}
#line 14714 "parser_bison.c"
    break;

  case 1030: /* eth_hdr_field: "saddr"  */
#line 5333 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_SADDR; }
#line 14720 "parser_bison.c"
    break;

  case 1031: /* eth_hdr_field: "daddr"  */
#line 5334 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_DADDR; }
#line 14726 "parser_bison.c"
    break;

  case 1032: /* eth_hdr_field: "type" close_scope_type  */
#line 5335 "parser_bison.y"
                                                                        { (yyval.val) = ETHHDR_TYPE; }
#line 14732 "parser_bison.c"
    break;

  case 1033: /* vlan_hdr_expr: "vlan" vlan_hdr_field close_scope_vlan  */
#line 5339 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[-1].val));
			}
#line 14740 "parser_bison.c"
    break;

  case 1034: /* vlan_hdr_field: "id"  */
#line 5344 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_VID; }
#line 14746 "parser_bison.c"
    break;

  case 1035: /* vlan_hdr_field: "cfi"  */
#line 5345 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_CFI; }
#line 14752 "parser_bison.c"
    break;

  case 1036: /* vlan_hdr_field: "dei"  */
#line 5346 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_DEI; }
#line 14758 "parser_bison.c"
    break;

  case 1037: /* vlan_hdr_field: "pcp"  */
#line 5347 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_PCP; }
#line 14764 "parser_bison.c"
    break;

  case 1038: /* vlan_hdr_field: "type" close_scope_type  */
#line 5348 "parser_bison.y"
                                                                        { (yyval.val) = VLANHDR_TYPE; }
#line 14770 "parser_bison.c"
    break;

  case 1039: /* arp_hdr_expr: "arp" arp_hdr_field close_scope_arp  */
#line 5352 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[-1].val));
			}
#line 14778 "parser_bison.c"
    break;

  case 1040: /* arp_hdr_field: "htype"  */
#line 5357 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_HRD; }
#line 14784 "parser_bison.c"
    break;

  case 1041: /* arp_hdr_field: "ptype"  */
#line 5358 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_PRO; }
#line 14790 "parser_bison.c"
    break;

  case 1042: /* arp_hdr_field: "hlen"  */
#line 5359 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_HLN; }
#line 14796 "parser_bison.c"
    break;

  case 1043: /* arp_hdr_field: "plen"  */
#line 5360 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_PLN; }
#line 14802 "parser_bison.c"
    break;

  case 1044: /* arp_hdr_field: "operation"  */
#line 5361 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_OP; }
#line 14808 "parser_bison.c"
    break;

  case 1045: /* arp_hdr_field: "saddr" "ether" close_scope_eth  */
#line 5362 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 14814 "parser_bison.c"
    break;

  case 1046: /* arp_hdr_field: "daddr" "ether" close_scope_eth  */
#line 5363 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 14820 "parser_bison.c"
    break;

  case 1047: /* arp_hdr_field: "saddr" "ip" close_scope_ip  */
#line 5364 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_SADDR_IP; }
#line 14826 "parser_bison.c"
    break;

  case 1048: /* arp_hdr_field: "daddr" "ip" close_scope_ip  */
#line 5365 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_DADDR_IP; }
#line 14832 "parser_bison.c"
    break;

  case 1049: /* ip_hdr_expr: "ip" ip_hdr_field close_scope_ip  */
#line 5369 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[-1].val));
			}
#line 14840 "parser_bison.c"
    break;

  case 1050: /* ip_hdr_expr: "ip" "option" ip_option_type ip_option_field close_scope_ip  */
#line 5373 "parser_bison.y"
                        {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val));
				if (!(yyval.expr)) {
					erec_queue(error(&(yylsp[-4]), "unknown ip option type/field"), state->msgs);
					YYERROR;
				}
			}
#line 14852 "parser_bison.c"
    break;

  case 1051: /* ip_hdr_expr: "ip" "option" ip_option_type close_scope_ip  */
#line 5381 "parser_bison.y"
                        {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), IPOPT_FIELD_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 14861 "parser_bison.c"
    break;

  case 1052: /* ip_hdr_field: "version"  */
#line 5387 "parser_bison.y"
                                                { (yyval.val) = IPHDR_VERSION; }
#line 14867 "parser_bison.c"
    break;

  case 1053: /* ip_hdr_field: "hdrlength"  */
#line 5388 "parser_bison.y"
                                                { (yyval.val) = IPHDR_HDRLENGTH; }
#line 14873 "parser_bison.c"
    break;

  case 1054: /* ip_hdr_field: "dscp"  */
#line 5389 "parser_bison.y"
                                                { (yyval.val) = IPHDR_DSCP; }
#line 14879 "parser_bison.c"
    break;

  case 1055: /* ip_hdr_field: "ecn"  */
#line 5390 "parser_bison.y"
                                                { (yyval.val) = IPHDR_ECN; }
#line 14885 "parser_bison.c"
    break;

  case 1056: /* ip_hdr_field: "length"  */
#line 5391 "parser_bison.y"
                                                { (yyval.val) = IPHDR_LENGTH; }
#line 14891 "parser_bison.c"
    break;

  case 1057: /* ip_hdr_field: "id"  */
#line 5392 "parser_bison.y"
                                                { (yyval.val) = IPHDR_ID; }
#line 14897 "parser_bison.c"
    break;

  case 1058: /* ip_hdr_field: "frag-off"  */
#line 5393 "parser_bison.y"
                                                { (yyval.val) = IPHDR_FRAG_OFF; }
#line 14903 "parser_bison.c"
    break;

  case 1059: /* ip_hdr_field: "ttl"  */
#line 5394 "parser_bison.y"
                                                { (yyval.val) = IPHDR_TTL; }
#line 14909 "parser_bison.c"
    break;

  case 1060: /* ip_hdr_field: "protocol"  */
#line 5395 "parser_bison.y"
                                                { (yyval.val) = IPHDR_PROTOCOL; }
#line 14915 "parser_bison.c"
    break;

  case 1061: /* ip_hdr_field: "checksum"  */
#line 5396 "parser_bison.y"
                                                { (yyval.val) = IPHDR_CHECKSUM; }
#line 14921 "parser_bison.c"
    break;

  case 1062: /* ip_hdr_field: "saddr"  */
#line 5397 "parser_bison.y"
                                                { (yyval.val) = IPHDR_SADDR; }
#line 14927 "parser_bison.c"
    break;

  case 1063: /* ip_hdr_field: "daddr"  */
#line 5398 "parser_bison.y"
                                                { (yyval.val) = IPHDR_DADDR; }
#line 14933 "parser_bison.c"
    break;

  case 1064: /* ip_option_type: "lsrr"  */
#line 5401 "parser_bison.y"
                                                { (yyval.val) = IPOPT_LSRR; }
#line 14939 "parser_bison.c"
    break;

  case 1065: /* ip_option_type: "rr"  */
#line 5402 "parser_bison.y"
                                                { (yyval.val) = IPOPT_RR; }
#line 14945 "parser_bison.c"
    break;

  case 1066: /* ip_option_type: "ssrr"  */
#line 5403 "parser_bison.y"
                                                { (yyval.val) = IPOPT_SSRR; }
#line 14951 "parser_bison.c"
    break;

  case 1067: /* ip_option_type: "ra"  */
#line 5404 "parser_bison.y"
                                                { (yyval.val) = IPOPT_RA; }
#line 14957 "parser_bison.c"
    break;

  case 1068: /* ip_option_field: "type" close_scope_type  */
#line 5407 "parser_bison.y"
                                                                        { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 14963 "parser_bison.c"
    break;

  case 1069: /* ip_option_field: "length"  */
#line 5408 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 14969 "parser_bison.c"
    break;

  case 1070: /* ip_option_field: "value"  */
#line 5409 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 14975 "parser_bison.c"
    break;

  case 1071: /* ip_option_field: "ptr"  */
#line 5410 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_PTR; }
#line 14981 "parser_bison.c"
    break;

  case 1072: /* ip_option_field: "addr"  */
#line 5411 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 14987 "parser_bison.c"
    break;

  case 1073: /* icmp_hdr_expr: "icmp" icmp_hdr_field close_scope_icmp  */
#line 5415 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[-1].val));
			}
#line 14995 "parser_bison.c"
    break;

  case 1074: /* icmp_hdr_field: "type" close_scope_type  */
#line 5420 "parser_bison.y"
                                                                        { (yyval.val) = ICMPHDR_TYPE; }
#line 15001 "parser_bison.c"
    break;

  case 1075: /* icmp_hdr_field: "code"  */
#line 5421 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_CODE; }
#line 15007 "parser_bison.c"
    break;

  case 1076: /* icmp_hdr_field: "checksum"  */
#line 5422 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 15013 "parser_bison.c"
    break;

  case 1077: /* icmp_hdr_field: "id"  */
#line 5423 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_ID; }
#line 15019 "parser_bison.c"
    break;

  case 1078: /* icmp_hdr_field: "seq"  */
#line 5424 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_SEQ; }
#line 15025 "parser_bison.c"
    break;

  case 1079: /* icmp_hdr_field: "gateway"  */
#line 5425 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_GATEWAY; }
#line 15031 "parser_bison.c"
    break;

  case 1080: /* icmp_hdr_field: "mtu"  */
#line 5426 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_MTU; }
#line 15037 "parser_bison.c"
    break;

  case 1081: /* igmp_hdr_expr: "igmp" igmp_hdr_field close_scope_igmp  */
#line 5430 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[-1].val));
			}
#line 15045 "parser_bison.c"
    break;

  case 1082: /* igmp_hdr_field: "type" close_scope_type  */
#line 5435 "parser_bison.y"
                                                                        { (yyval.val) = IGMPHDR_TYPE; }
#line 15051 "parser_bison.c"
    break;

  case 1083: /* igmp_hdr_field: "checksum"  */
#line 5436 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 15057 "parser_bison.c"
    break;

  case 1084: /* igmp_hdr_field: "mrt"  */
#line 5437 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_MRT; }
#line 15063 "parser_bison.c"
    break;

  case 1085: /* igmp_hdr_field: "group"  */
#line 5438 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_GROUP; }
#line 15069 "parser_bison.c"
    break;

  case 1086: /* ip6_hdr_expr: "ip6" ip6_hdr_field close_scope_ip6  */
#line 5442 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[-1].val));
			}
#line 15077 "parser_bison.c"
    break;

  case 1087: /* ip6_hdr_field: "version"  */
#line 5447 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_VERSION; }
#line 15083 "parser_bison.c"
    break;

  case 1088: /* ip6_hdr_field: "dscp"  */
#line 5448 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_DSCP; }
#line 15089 "parser_bison.c"
    break;

  case 1089: /* ip6_hdr_field: "ecn"  */
#line 5449 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_ECN; }
#line 15095 "parser_bison.c"
    break;

  case 1090: /* ip6_hdr_field: "flowlabel"  */
#line 5450 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 15101 "parser_bison.c"
    break;

  case 1091: /* ip6_hdr_field: "length"  */
#line 5451 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_LENGTH; }
#line 15107 "parser_bison.c"
    break;

  case 1092: /* ip6_hdr_field: "nexthdr"  */
#line 5452 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_NEXTHDR; }
#line 15113 "parser_bison.c"
    break;

  case 1093: /* ip6_hdr_field: "hoplimit"  */
#line 5453 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 15119 "parser_bison.c"
    break;

  case 1094: /* ip6_hdr_field: "saddr"  */
#line 5454 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_SADDR; }
#line 15125 "parser_bison.c"
    break;

  case 1095: /* ip6_hdr_field: "daddr"  */
#line 5455 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_DADDR; }
#line 15131 "parser_bison.c"
    break;

  case 1096: /* icmp6_hdr_expr: "icmpv6" icmp6_hdr_field close_scope_icmp  */
#line 5458 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[-1].val));
			}
#line 15139 "parser_bison.c"
    break;

  case 1097: /* icmp6_hdr_field: "type" close_scope_type  */
#line 5463 "parser_bison.y"
                                                                        { (yyval.val) = ICMP6HDR_TYPE; }
#line 15145 "parser_bison.c"
    break;

  case 1098: /* icmp6_hdr_field: "code"  */
#line 5464 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_CODE; }
#line 15151 "parser_bison.c"
    break;

  case 1099: /* icmp6_hdr_field: "checksum"  */
#line 5465 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 15157 "parser_bison.c"
    break;

  case 1100: /* icmp6_hdr_field: "param-problem"  */
#line 5466 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_PPTR; }
#line 15163 "parser_bison.c"
    break;

  case 1101: /* icmp6_hdr_field: "mtu"  */
#line 5467 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_MTU; }
#line 15169 "parser_bison.c"
    break;

  case 1102: /* icmp6_hdr_field: "id"  */
#line 5468 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_ID; }
#line 15175 "parser_bison.c"
    break;

  case 1103: /* icmp6_hdr_field: "seq"  */
#line 5469 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_SEQ; }
#line 15181 "parser_bison.c"
    break;

  case 1104: /* icmp6_hdr_field: "max-delay"  */
#line 5470 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 15187 "parser_bison.c"
    break;

  case 1105: /* auth_hdr_expr: "ah" auth_hdr_field close_scope_ah  */
#line 5474 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[-1].val));
			}
#line 15195 "parser_bison.c"
    break;

  case 1106: /* auth_hdr_field: "nexthdr"  */
#line 5479 "parser_bison.y"
                                                { (yyval.val) = AHHDR_NEXTHDR; }
#line 15201 "parser_bison.c"
    break;

  case 1107: /* auth_hdr_field: "hdrlength"  */
#line 5480 "parser_bison.y"
                                                { (yyval.val) = AHHDR_HDRLENGTH; }
#line 15207 "parser_bison.c"
    break;

  case 1108: /* auth_hdr_field: "reserved"  */
#line 5481 "parser_bison.y"
                                                { (yyval.val) = AHHDR_RESERVED; }
#line 15213 "parser_bison.c"
    break;

  case 1109: /* auth_hdr_field: "spi"  */
#line 5482 "parser_bison.y"
                                                { (yyval.val) = AHHDR_SPI; }
#line 15219 "parser_bison.c"
    break;

  case 1110: /* auth_hdr_field: "seq"  */
#line 5483 "parser_bison.y"
                                                { (yyval.val) = AHHDR_SEQUENCE; }
#line 15225 "parser_bison.c"
    break;

  case 1111: /* esp_hdr_expr: "esp" esp_hdr_field close_scope_esp  */
#line 5487 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[-1].val));
			}
#line 15233 "parser_bison.c"
    break;

  case 1112: /* esp_hdr_field: "spi"  */
#line 5492 "parser_bison.y"
                                                { (yyval.val) = ESPHDR_SPI; }
#line 15239 "parser_bison.c"
    break;

  case 1113: /* esp_hdr_field: "seq"  */
#line 5493 "parser_bison.y"
                                                { (yyval.val) = ESPHDR_SEQUENCE; }
#line 15245 "parser_bison.c"
    break;

  case 1114: /* comp_hdr_expr: "comp" comp_hdr_field close_scope_comp  */
#line 5497 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[-1].val));
			}
#line 15253 "parser_bison.c"
    break;

  case 1115: /* comp_hdr_field: "nexthdr"  */
#line 5502 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_NEXTHDR; }
#line 15259 "parser_bison.c"
    break;

  case 1116: /* comp_hdr_field: "flags"  */
#line 5503 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_FLAGS; }
#line 15265 "parser_bison.c"
    break;

  case 1117: /* comp_hdr_field: "cpi"  */
#line 5504 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_CPI; }
#line 15271 "parser_bison.c"
    break;

  case 1118: /* udp_hdr_expr: "udp" udp_hdr_field close_scope_udp  */
#line 5508 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[-1].val));
			}
#line 15279 "parser_bison.c"
    break;

  case 1119: /* udp_hdr_field: "sport"  */
#line 5513 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_SPORT; }
#line 15285 "parser_bison.c"
    break;

  case 1120: /* udp_hdr_field: "dport"  */
#line 5514 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_DPORT; }
#line 15291 "parser_bison.c"
    break;

  case 1121: /* udp_hdr_field: "length"  */
#line 5515 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_LENGTH; }
#line 15297 "parser_bison.c"
    break;

  case 1122: /* udp_hdr_field: "checksum"  */
#line 5516 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_CHECKSUM; }
#line 15303 "parser_bison.c"
    break;

  case 1123: /* udplite_hdr_expr: "udplite" udplite_hdr_field close_scope_udplite  */
#line 5520 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[-1].val));
			}
#line 15311 "parser_bison.c"
    break;

  case 1124: /* udplite_hdr_field: "sport"  */
#line 5525 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_SPORT; }
#line 15317 "parser_bison.c"
    break;

  case 1125: /* udplite_hdr_field: "dport"  */
#line 5526 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_DPORT; }
#line 15323 "parser_bison.c"
    break;

  case 1126: /* udplite_hdr_field: "csumcov"  */
#line 5527 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_LENGTH; }
#line 15329 "parser_bison.c"
    break;

  case 1127: /* udplite_hdr_field: "checksum"  */
#line 5528 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_CHECKSUM; }
#line 15335 "parser_bison.c"
    break;

  case 1128: /* tcp_hdr_expr: "tcp" tcp_hdr_field  */
#line 5532 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 15343 "parser_bison.c"
    break;

  case 1129: /* tcp_hdr_expr: "tcp" "option" tcp_hdr_option_type  */
#line 5536 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPT_COMMON_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 15352 "parser_bison.c"
    break;

  case 1130: /* tcp_hdr_expr: "tcp" "option" tcp_hdr_option_kind_and_field  */
#line 5541 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].tcp_kind_field).kind, (yyvsp[0].tcp_kind_field).field);
			}
#line 15360 "parser_bison.c"
    break;

  case 1131: /* tcp_hdr_expr: "tcp" "option" "@" close_scope_at tcp_hdr_option_type "comma" "number" "comma" "number"  */
#line 5545 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-4].val), 0);
				tcpopt_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val), 0);
			}
#line 15369 "parser_bison.c"
    break;

  case 1132: /* optstrip_stmt: "reset" "tcp" "option" tcp_hdr_option_type close_scope_tcp  */
#line 5552 "parser_bison.y"
                        {
				(yyval.stmt) = optstrip_stmt_alloc(&(yyloc), tcpopt_expr_alloc(&(yyloc),
										(yyvsp[-1].val), TCPOPT_COMMON_KIND));
			}
#line 15378 "parser_bison.c"
    break;

  case 1133: /* tcp_hdr_field: "sport"  */
#line 5558 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_SPORT; }
#line 15384 "parser_bison.c"
    break;

  case 1134: /* tcp_hdr_field: "dport"  */
#line 5559 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_DPORT; }
#line 15390 "parser_bison.c"
    break;

  case 1135: /* tcp_hdr_field: "seq"  */
#line 5560 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_SEQ; }
#line 15396 "parser_bison.c"
    break;

  case 1136: /* tcp_hdr_field: "ackseq"  */
#line 5561 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_ACKSEQ; }
#line 15402 "parser_bison.c"
    break;

  case 1137: /* tcp_hdr_field: "doff"  */
#line 5562 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_DOFF; }
#line 15408 "parser_bison.c"
    break;

  case 1138: /* tcp_hdr_field: "reserved"  */
#line 5563 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_RESERVED; }
#line 15414 "parser_bison.c"
    break;

  case 1139: /* tcp_hdr_field: "flags"  */
#line 5564 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_FLAGS; }
#line 15420 "parser_bison.c"
    break;

  case 1140: /* tcp_hdr_field: "window"  */
#line 5565 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_WINDOW; }
#line 15426 "parser_bison.c"
    break;

  case 1141: /* tcp_hdr_field: "checksum"  */
#line 5566 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_CHECKSUM; }
#line 15432 "parser_bison.c"
    break;

  case 1142: /* tcp_hdr_field: "urgptr"  */
#line 5567 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_URGPTR; }
#line 15438 "parser_bison.c"
    break;

  case 1143: /* tcp_hdr_option_kind_and_field: "mss" tcpopt_field_maxseg  */
#line 5571 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_MAXSEG, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 15447 "parser_bison.c"
    break;

  case 1144: /* tcp_hdr_option_kind_and_field: tcp_hdr_option_sack tcpopt_field_sack  */
#line 5576 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = (yyvsp[-1].val), .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 15456 "parser_bison.c"
    break;

  case 1145: /* tcp_hdr_option_kind_and_field: "window" tcpopt_field_window  */
#line 5581 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_WINDOW, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 15465 "parser_bison.c"
    break;

  case 1146: /* tcp_hdr_option_kind_and_field: "timestamp" tcpopt_field_tsopt  */
#line 5586 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_TIMESTAMP, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 15474 "parser_bison.c"
    break;

  case 1147: /* tcp_hdr_option_kind_and_field: tcp_hdr_option_type "length"  */
#line 5591 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = (yyvsp[-1].val), .field = TCPOPT_COMMON_LENGTH };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 15483 "parser_bison.c"
    break;

  case 1148: /* tcp_hdr_option_kind_and_field: "mptcp" tcpopt_field_mptcp  */
#line 5596 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_MPTCP, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 15492 "parser_bison.c"
    break;

  case 1149: /* tcp_hdr_option_sack: "sack"  */
#line 5602 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK; }
#line 15498 "parser_bison.c"
    break;

  case 1150: /* tcp_hdr_option_sack: "sack0"  */
#line 5603 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK; }
#line 15504 "parser_bison.c"
    break;

  case 1151: /* tcp_hdr_option_sack: "sack1"  */
#line 5604 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK1; }
#line 15510 "parser_bison.c"
    break;

  case 1152: /* tcp_hdr_option_sack: "sack2"  */
#line 5605 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK2; }
#line 15516 "parser_bison.c"
    break;

  case 1153: /* tcp_hdr_option_sack: "sack3"  */
#line 5606 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK3; }
#line 15522 "parser_bison.c"
    break;

  case 1154: /* tcp_hdr_option_type: "echo"  */
#line 5609 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_ECHO; }
#line 15528 "parser_bison.c"
    break;

  case 1155: /* tcp_hdr_option_type: "eol"  */
#line 5610 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_EOL; }
#line 15534 "parser_bison.c"
    break;

  case 1156: /* tcp_hdr_option_type: "fastopen"  */
#line 5611 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_FASTOPEN; }
#line 15540 "parser_bison.c"
    break;

  case 1157: /* tcp_hdr_option_type: "md5sig"  */
#line 5612 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MD5SIG; }
#line 15546 "parser_bison.c"
    break;

  case 1158: /* tcp_hdr_option_type: "mptcp"  */
#line 5613 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MPTCP; }
#line 15552 "parser_bison.c"
    break;

  case 1159: /* tcp_hdr_option_type: "mss"  */
#line 5614 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MAXSEG; }
#line 15558 "parser_bison.c"
    break;

  case 1160: /* tcp_hdr_option_type: "nop"  */
#line 5615 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_NOP; }
#line 15564 "parser_bison.c"
    break;

  case 1161: /* tcp_hdr_option_type: "sack-permitted"  */
#line 5616 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_SACK_PERMITTED; }
#line 15570 "parser_bison.c"
    break;

  case 1162: /* tcp_hdr_option_type: "timestamp"  */
#line 5617 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_TIMESTAMP; }
#line 15576 "parser_bison.c"
    break;

  case 1163: /* tcp_hdr_option_type: "window"  */
#line 5618 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_WINDOW; }
#line 15582 "parser_bison.c"
    break;

  case 1164: /* tcp_hdr_option_type: tcp_hdr_option_sack  */
#line 5619 "parser_bison.y"
                                                        { (yyval.val) = (yyvsp[0].val); }
#line 15588 "parser_bison.c"
    break;

  case 1165: /* tcp_hdr_option_type: "number"  */
#line 5620 "parser_bison.y"
                                                        {
				if ((yyvsp[0].val) > 255) {
					erec_queue(error(&(yylsp[0]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[0].val);
			}
#line 15600 "parser_bison.c"
    break;

  case 1166: /* tcpopt_field_sack: "left"  */
#line 5629 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_SACK_LEFT; }
#line 15606 "parser_bison.c"
    break;

  case 1167: /* tcpopt_field_sack: "right"  */
#line 5630 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_SACK_RIGHT; }
#line 15612 "parser_bison.c"
    break;

  case 1168: /* tcpopt_field_window: "count"  */
#line 5633 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_WINDOW_COUNT; }
#line 15618 "parser_bison.c"
    break;

  case 1169: /* tcpopt_field_tsopt: "tsval"  */
#line 5636 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_TS_TSVAL; }
#line 15624 "parser_bison.c"
    break;

  case 1170: /* tcpopt_field_tsopt: "tsecr"  */
#line 5637 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_TS_TSECR; }
#line 15630 "parser_bison.c"
    break;

  case 1171: /* tcpopt_field_maxseg: "size"  */
#line 5640 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_MAXSEG_SIZE; }
#line 15636 "parser_bison.c"
    break;

  case 1172: /* tcpopt_field_mptcp: "subtype"  */
#line 5643 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_MPTCP_SUBTYPE; }
#line 15642 "parser_bison.c"
    break;

  case 1173: /* dccp_hdr_expr: "dccp" dccp_hdr_field close_scope_dccp  */
#line 5647 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[-1].val));
			}
#line 15650 "parser_bison.c"
    break;

  case 1174: /* dccp_hdr_field: "sport"  */
#line 5652 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_SPORT; }
#line 15656 "parser_bison.c"
    break;

  case 1175: /* dccp_hdr_field: "dport"  */
#line 5653 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_DPORT; }
#line 15662 "parser_bison.c"
    break;

  case 1176: /* dccp_hdr_field: "type" close_scope_type  */
#line 5654 "parser_bison.y"
                                                                        { (yyval.val) = DCCPHDR_TYPE; }
#line 15668 "parser_bison.c"
    break;

  case 1177: /* sctp_chunk_type: "data"  */
#line 5657 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_DATA; }
#line 15674 "parser_bison.c"
    break;

  case 1178: /* sctp_chunk_type: "init"  */
#line 5658 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_INIT; }
#line 15680 "parser_bison.c"
    break;

  case 1179: /* sctp_chunk_type: "init-ack"  */
#line 5659 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_INIT_ACK; }
#line 15686 "parser_bison.c"
    break;

  case 1180: /* sctp_chunk_type: "sack"  */
#line 5660 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SACK; }
#line 15692 "parser_bison.c"
    break;

  case 1181: /* sctp_chunk_type: "heartbeat"  */
#line 5661 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT; }
#line 15698 "parser_bison.c"
    break;

  case 1182: /* sctp_chunk_type: "heartbeat-ack"  */
#line 5662 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT_ACK; }
#line 15704 "parser_bison.c"
    break;

  case 1183: /* sctp_chunk_type: "abort"  */
#line 5663 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ABORT; }
#line 15710 "parser_bison.c"
    break;

  case 1184: /* sctp_chunk_type: "shutdown"  */
#line 5664 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN; }
#line 15716 "parser_bison.c"
    break;

  case 1185: /* sctp_chunk_type: "shutdown-ack"  */
#line 5665 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_ACK; }
#line 15722 "parser_bison.c"
    break;

  case 1186: /* sctp_chunk_type: "error"  */
#line 5666 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ERROR; }
#line 15728 "parser_bison.c"
    break;

  case 1187: /* sctp_chunk_type: "cookie-echo"  */
#line 5667 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ECHO; }
#line 15734 "parser_bison.c"
    break;

  case 1188: /* sctp_chunk_type: "cookie-ack"  */
#line 5668 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ACK; }
#line 15740 "parser_bison.c"
    break;

  case 1189: /* sctp_chunk_type: "ecne"  */
#line 5669 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ECNE; }
#line 15746 "parser_bison.c"
    break;

  case 1190: /* sctp_chunk_type: "cwr"  */
#line 5670 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_CWR; }
#line 15752 "parser_bison.c"
    break;

  case 1191: /* sctp_chunk_type: "shutdown-complete"  */
#line 5671 "parser_bison.y"
                                                  { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_COMPLETE; }
#line 15758 "parser_bison.c"
    break;

  case 1192: /* sctp_chunk_type: "asconf-ack"  */
#line 5672 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF_ACK; }
#line 15764 "parser_bison.c"
    break;

  case 1193: /* sctp_chunk_type: "forward-tsn"  */
#line 5673 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_FORWARD_TSN; }
#line 15770 "parser_bison.c"
    break;

  case 1194: /* sctp_chunk_type: "asconf"  */
#line 5674 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF; }
#line 15776 "parser_bison.c"
    break;

  case 1195: /* sctp_chunk_common_field: "type" close_scope_type  */
#line 5677 "parser_bison.y"
                                                                { (yyval.val) = SCTP_CHUNK_COMMON_TYPE; }
#line 15782 "parser_bison.c"
    break;

  case 1196: /* sctp_chunk_common_field: "flags"  */
#line 5678 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_FLAGS; }
#line 15788 "parser_bison.c"
    break;

  case 1197: /* sctp_chunk_common_field: "length"  */
#line 5679 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_LENGTH; }
#line 15794 "parser_bison.c"
    break;

  case 1198: /* sctp_chunk_data_field: "tsn"  */
#line 5682 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_TSN; }
#line 15800 "parser_bison.c"
    break;

  case 1199: /* sctp_chunk_data_field: "stream"  */
#line 5683 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_STREAM; }
#line 15806 "parser_bison.c"
    break;

  case 1200: /* sctp_chunk_data_field: "ssn"  */
#line 5684 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_SSN; }
#line 15812 "parser_bison.c"
    break;

  case 1201: /* sctp_chunk_data_field: "ppid"  */
#line 5685 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_PPID; }
#line 15818 "parser_bison.c"
    break;

  case 1202: /* sctp_chunk_init_field: "init-tag"  */
#line 5688 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_TAG; }
#line 15824 "parser_bison.c"
    break;

  case 1203: /* sctp_chunk_init_field: "a-rwnd"  */
#line 5689 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_RWND; }
#line 15830 "parser_bison.c"
    break;

  case 1204: /* sctp_chunk_init_field: "num-outbound-streams"  */
#line 5690 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_OSTREAMS; }
#line 15836 "parser_bison.c"
    break;

  case 1205: /* sctp_chunk_init_field: "num-inbound-streams"  */
#line 5691 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_ISTREAMS; }
#line 15842 "parser_bison.c"
    break;

  case 1206: /* sctp_chunk_init_field: "initial-tsn"  */
#line 5692 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_TSN; }
#line 15848 "parser_bison.c"
    break;

  case 1207: /* sctp_chunk_sack_field: "cum-tsn-ack"  */
#line 5695 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_CTSN_ACK; }
#line 15854 "parser_bison.c"
    break;

  case 1208: /* sctp_chunk_sack_field: "a-rwnd"  */
#line 5696 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_RWND; }
#line 15860 "parser_bison.c"
    break;

  case 1209: /* sctp_chunk_sack_field: "num-gap-ack-blocks"  */
#line 5697 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_GACK_BLOCKS; }
#line 15866 "parser_bison.c"
    break;

  case 1210: /* sctp_chunk_sack_field: "num-dup-tsns"  */
#line 5698 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_DUP_TSNS; }
#line 15872 "parser_bison.c"
    break;

  case 1211: /* sctp_chunk_alloc: sctp_chunk_type  */
#line 5702 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[0].val), SCTP_CHUNK_COMMON_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 15881 "parser_bison.c"
    break;

  case 1212: /* sctp_chunk_alloc: sctp_chunk_type sctp_chunk_common_field  */
#line 5707 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 15889 "parser_bison.c"
    break;

  case 1213: /* sctp_chunk_alloc: "data" sctp_chunk_data_field  */
#line 5711 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_DATA, (yyvsp[0].val));
			}
#line 15897 "parser_bison.c"
    break;

  case 1214: /* sctp_chunk_alloc: "init" sctp_chunk_init_field  */
#line 5715 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT, (yyvsp[0].val));
			}
#line 15905 "parser_bison.c"
    break;

  case 1215: /* sctp_chunk_alloc: "init-ack" sctp_chunk_init_field  */
#line 5719 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT_ACK, (yyvsp[0].val));
			}
#line 15913 "parser_bison.c"
    break;

  case 1216: /* sctp_chunk_alloc: "sack" sctp_chunk_sack_field  */
#line 5723 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SACK, (yyvsp[0].val));
			}
#line 15921 "parser_bison.c"
    break;

  case 1217: /* sctp_chunk_alloc: "shutdown" "cum-tsn-ack"  */
#line 5727 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SHUTDOWN,
							   SCTP_CHUNK_SHUTDOWN_CTSN_ACK);
			}
#line 15930 "parser_bison.c"
    break;

  case 1218: /* sctp_chunk_alloc: "ecne" "lowest-tsn"  */
#line 5732 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ECNE,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 15939 "parser_bison.c"
    break;

  case 1219: /* sctp_chunk_alloc: "cwr" "lowest-tsn"  */
#line 5737 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_CWR,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 15948 "parser_bison.c"
    break;

  case 1220: /* sctp_chunk_alloc: "asconf-ack" "seqno"  */
#line 5742 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF_ACK,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 15957 "parser_bison.c"
    break;

  case 1221: /* sctp_chunk_alloc: "forward-tsn" "new-cum-tsn"  */
#line 5747 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_FORWARD_TSN,
							   SCTP_CHUNK_FORWARD_TSN_NCTSN);
			}
#line 15966 "parser_bison.c"
    break;

  case 1222: /* sctp_chunk_alloc: "asconf" "seqno"  */
#line 5752 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 15975 "parser_bison.c"
    break;

  case 1223: /* sctp_hdr_expr: "sctp" sctp_hdr_field close_scope_sctp  */
#line 5759 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[-1].val));
			}
#line 15983 "parser_bison.c"
    break;

  case 1224: /* sctp_hdr_expr: "sctp" "chunk" sctp_chunk_alloc close_scope_sctp_chunk close_scope_sctp  */
#line 5763 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 15991 "parser_bison.c"
    break;

  case 1225: /* sctp_hdr_field: "sport"  */
#line 5768 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_SPORT; }
#line 15997 "parser_bison.c"
    break;

  case 1226: /* sctp_hdr_field: "dport"  */
#line 5769 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_DPORT; }
#line 16003 "parser_bison.c"
    break;

  case 1227: /* sctp_hdr_field: "vtag"  */
#line 5770 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_VTAG; }
#line 16009 "parser_bison.c"
    break;

  case 1228: /* sctp_hdr_field: "checksum"  */
#line 5771 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 16015 "parser_bison.c"
    break;

  case 1229: /* th_hdr_expr: "th" th_hdr_field close_scope_th  */
#line 5775 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[-1].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 16025 "parser_bison.c"
    break;

  case 1230: /* th_hdr_field: "sport"  */
#line 5782 "parser_bison.y"
                                                { (yyval.val) = THDR_SPORT; }
#line 16031 "parser_bison.c"
    break;

  case 1231: /* th_hdr_field: "dport"  */
#line 5783 "parser_bison.y"
                                                { (yyval.val) = THDR_DPORT; }
#line 16037 "parser_bison.c"
    break;

  case 1240: /* hbh_hdr_expr: "hbh" hbh_hdr_field close_scope_hbh  */
#line 5797 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[-1].val));
			}
#line 16045 "parser_bison.c"
    break;

  case 1241: /* hbh_hdr_field: "nexthdr"  */
#line 5802 "parser_bison.y"
                                                { (yyval.val) = HBHHDR_NEXTHDR; }
#line 16051 "parser_bison.c"
    break;

  case 1242: /* hbh_hdr_field: "hdrlength"  */
#line 5803 "parser_bison.y"
                                                { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 16057 "parser_bison.c"
    break;

  case 1243: /* rt_hdr_expr: "rt" rt_hdr_field close_scope_rt  */
#line 5807 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[-1].val));
			}
#line 16065 "parser_bison.c"
    break;

  case 1244: /* rt_hdr_field: "nexthdr"  */
#line 5812 "parser_bison.y"
                                                { (yyval.val) = RTHDR_NEXTHDR; }
#line 16071 "parser_bison.c"
    break;

  case 1245: /* rt_hdr_field: "hdrlength"  */
#line 5813 "parser_bison.y"
                                                { (yyval.val) = RTHDR_HDRLENGTH; }
#line 16077 "parser_bison.c"
    break;

  case 1246: /* rt_hdr_field: "type" close_scope_type  */
#line 5814 "parser_bison.y"
                                                                        { (yyval.val) = RTHDR_TYPE; }
#line 16083 "parser_bison.c"
    break;

  case 1247: /* rt_hdr_field: "seg-left"  */
#line 5815 "parser_bison.y"
                                                { (yyval.val) = RTHDR_SEG_LEFT; }
#line 16089 "parser_bison.c"
    break;

  case 1248: /* rt0_hdr_expr: "rt0" rt0_hdr_field close_scope_rt  */
#line 5819 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[-1].val));
			}
#line 16097 "parser_bison.c"
    break;

  case 1249: /* rt0_hdr_field: "addr" '[' "number" ']'  */
#line 5825 "parser_bison.y"
                        {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 16105 "parser_bison.c"
    break;

  case 1250: /* rt2_hdr_expr: "rt2" rt2_hdr_field close_scope_rt  */
#line 5831 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[-1].val));
			}
#line 16113 "parser_bison.c"
    break;

  case 1251: /* rt2_hdr_field: "addr"  */
#line 5836 "parser_bison.y"
                                                { (yyval.val) = RT2HDR_ADDR; }
#line 16119 "parser_bison.c"
    break;

  case 1252: /* rt4_hdr_expr: "srh" rt4_hdr_field close_scope_rt  */
#line 5840 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[-1].val));
			}
#line 16127 "parser_bison.c"
    break;

  case 1253: /* rt4_hdr_field: "last-entry"  */
#line 5845 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_LASTENT; }
#line 16133 "parser_bison.c"
    break;

  case 1254: /* rt4_hdr_field: "flags"  */
#line 5846 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_FLAGS; }
#line 16139 "parser_bison.c"
    break;

  case 1255: /* rt4_hdr_field: "tag"  */
#line 5847 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_TAG; }
#line 16145 "parser_bison.c"
    break;

  case 1256: /* rt4_hdr_field: "sid" '[' "number" ']'  */
#line 5849 "parser_bison.y"
                        {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 16153 "parser_bison.c"
    break;

  case 1257: /* frag_hdr_expr: "frag" frag_hdr_field close_scope_frag  */
#line 5855 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[-1].val));
			}
#line 16161 "parser_bison.c"
    break;

  case 1258: /* frag_hdr_field: "nexthdr"  */
#line 5860 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 16167 "parser_bison.c"
    break;

  case 1259: /* frag_hdr_field: "reserved"  */
#line 5861 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_RESERVED; }
#line 16173 "parser_bison.c"
    break;

  case 1260: /* frag_hdr_field: "frag-off"  */
#line 5862 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 16179 "parser_bison.c"
    break;

  case 1261: /* frag_hdr_field: "reserved2"  */
#line 5863 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_RESERVED2; }
#line 16185 "parser_bison.c"
    break;

  case 1262: /* frag_hdr_field: "more-fragments"  */
#line 5864 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_MFRAGS; }
#line 16191 "parser_bison.c"
    break;

  case 1263: /* frag_hdr_field: "id"  */
#line 5865 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_ID; }
#line 16197 "parser_bison.c"
    break;

  case 1264: /* dst_hdr_expr: "dst" dst_hdr_field close_scope_dst  */
#line 5869 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[-1].val));
			}
#line 16205 "parser_bison.c"
    break;

  case 1265: /* dst_hdr_field: "nexthdr"  */
#line 5874 "parser_bison.y"
                                                { (yyval.val) = DSTHDR_NEXTHDR; }
#line 16211 "parser_bison.c"
    break;

  case 1266: /* dst_hdr_field: "hdrlength"  */
#line 5875 "parser_bison.y"
                                                { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 16217 "parser_bison.c"
    break;

  case 1267: /* mh_hdr_expr: "mh" mh_hdr_field close_scope_mh  */
#line 5879 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[-1].val));
			}
#line 16225 "parser_bison.c"
    break;

  case 1268: /* mh_hdr_field: "nexthdr"  */
#line 5884 "parser_bison.y"
                                                { (yyval.val) = MHHDR_NEXTHDR; }
#line 16231 "parser_bison.c"
    break;

  case 1269: /* mh_hdr_field: "hdrlength"  */
#line 5885 "parser_bison.y"
                                                { (yyval.val) = MHHDR_HDRLENGTH; }
#line 16237 "parser_bison.c"
    break;

  case 1270: /* mh_hdr_field: "type" close_scope_type  */
#line 5886 "parser_bison.y"
                                                                        { (yyval.val) = MHHDR_TYPE; }
#line 16243 "parser_bison.c"
    break;

  case 1271: /* mh_hdr_field: "reserved"  */
#line 5887 "parser_bison.y"
                                                { (yyval.val) = MHHDR_RESERVED; }
#line 16249 "parser_bison.c"
    break;

  case 1272: /* mh_hdr_field: "checksum"  */
#line 5888 "parser_bison.y"
                                                { (yyval.val) = MHHDR_CHECKSUM; }
#line 16255 "parser_bison.c"
    break;

  case 1273: /* exthdr_exists_expr: "exthdr" exthdr_key  */
#line 5892 "parser_bison.y"
                        {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 16271 "parser_bison.c"
    break;

  case 1274: /* exthdr_key: "hbh" close_scope_hbh  */
#line 5905 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_HOPOPTS; }
#line 16277 "parser_bison.c"
    break;

  case 1275: /* exthdr_key: "rt" close_scope_rt  */
#line 5906 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_ROUTING; }
#line 16283 "parser_bison.c"
    break;

  case 1276: /* exthdr_key: "frag" close_scope_frag  */
#line 5907 "parser_bison.y"
                                                                { (yyval.val) = IPPROTO_FRAGMENT; }
#line 16289 "parser_bison.c"
    break;

  case 1277: /* exthdr_key: "dst" close_scope_dst  */
#line 5908 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_DSTOPTS; }
#line 16295 "parser_bison.c"
    break;

  case 1278: /* exthdr_key: "mh" close_scope_mh  */
#line 5909 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_MH; }
#line 16301 "parser_bison.c"
    break;


#line 16305 "parser_bison.c"

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

#line 5912 "parser_bison.y"

