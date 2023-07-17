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

#line 249 "parser_bison.c"

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
#line 204 "parser_bison.y"

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

#line 1053 "parser_bison.c"

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
#define YYLAST   9086

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  371
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  442
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1362
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2348

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
       0,   976,   976,   977,   986,   987,   990,   991,   994,   995,
     996,   997,   998,   999,  1000,  1001,  1002,  1003,  1004,  1005,
    1006,  1007,  1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,
    1016,  1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,
    1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,
    1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,  1046,
    1047,  1048,  1050,  1058,  1073,  1080,  1092,  1100,  1101,  1102,
    1103,  1123,  1124,  1125,  1126,  1127,  1128,  1129,  1130,  1131,
    1132,  1133,  1134,  1135,  1136,  1137,  1138,  1141,  1145,  1152,
    1156,  1164,  1168,  1172,  1179,  1186,  1190,  1197,  1206,  1210,
    1214,  1218,  1222,  1226,  1230,  1234,  1238,  1242,  1246,  1250,
    1254,  1260,  1266,  1270,  1277,  1281,  1289,  1296,  1303,  1307,
    1314,  1323,  1327,  1331,  1335,  1339,  1343,  1347,  1351,  1357,
    1363,  1364,  1367,  1368,  1371,  1372,  1375,  1376,  1379,  1383,
    1387,  1394,  1398,  1402,  1406,  1410,  1414,  1418,  1425,  1429,
    1433,  1439,  1443,  1447,  1453,  1457,  1461,  1465,  1469,  1473,
    1477,  1481,  1485,  1492,  1496,  1500,  1506,  1510,  1514,  1521,
    1527,  1531,  1535,  1539,  1543,  1547,  1551,  1555,  1559,  1563,
    1567,  1571,  1575,  1579,  1583,  1587,  1591,  1595,  1599,  1603,
    1607,  1611,  1615,  1619,  1623,  1627,  1631,  1635,  1639,  1643,
    1647,  1651,  1655,  1659,  1665,  1671,  1675,  1685,  1689,  1693,
    1698,  1702,  1706,  1710,  1715,  1719,  1723,  1727,  1732,  1736,
    1741,  1745,  1749,  1753,  1759,  1763,  1767,  1771,  1775,  1779,
    1783,  1789,  1796,  1802,  1810,  1816,  1824,  1833,  1834,  1837,
    1838,  1839,  1840,  1841,  1842,  1843,  1844,  1847,  1848,  1851,
    1852,  1853,  1856,  1865,  1875,  1890,  1900,  1901,  1902,  1903,
    1904,  1915,  1925,  1936,  1946,  1957,  1968,  1977,  1986,  1995,
    2006,  2017,  2031,  2041,  2042,  2043,  2044,  2045,  2046,  2047,
    2052,  2061,  2071,  2072,  2073,  2080,  2101,  2112,  2123,  2136,
    2141,  2142,  2143,  2144,  2149,  2155,  2160,  2165,  2170,  2176,
    2181,  2186,  2187,  2198,  2199,  2202,  2206,  2209,  2210,  2211,
    2212,  2216,  2221,  2222,  2223,  2224,  2225,  2228,  2229,  2230,
    2231,  2236,  2246,  2257,  2268,  2280,  2289,  2294,  2300,  2305,
    2314,  2317,  2321,  2327,  2328,  2332,  2337,  2338,  2339,  2340,
    2354,  2358,  2362,  2368,  2373,  2380,  2385,  2390,  2393,  2402,
    2411,  2418,  2431,  2438,  2439,  2451,  2456,  2457,  2458,  2459,
    2463,  2473,  2474,  2475,  2476,  2480,  2490,  2491,  2492,  2493,
    2497,  2508,  2512,  2513,  2514,  2518,  2528,  2529,  2530,  2531,
    2535,  2545,  2546,  2547,  2548,  2552,  2562,  2563,  2564,  2565,
    2569,  2579,  2580,  2581,  2582,  2586,  2596,  2597,  2598,  2599,
    2600,  2603,  2634,  2641,  2645,  2648,  2658,  2665,  2676,  2689,
    2704,  2705,  2708,  2719,  2725,  2729,  2732,  2738,  2751,  2756,
    2765,  2766,  2769,  2770,  2773,  2774,  2775,  2778,  2793,  2794,
    2797,  2798,  2799,  2800,  2801,  2802,  2805,  2814,  2823,  2831,
    2839,  2847,  2855,  2863,  2871,  2879,  2887,  2895,  2903,  2911,
    2919,  2927,  2935,  2943,  2947,  2952,  2960,  2967,  2974,  2988,
    2992,  2999,  3003,  3009,  3021,  3027,  3034,  3040,  3047,  3048,
    3049,  3050,  3051,  3054,  3055,  3056,  3057,  3058,  3059,  3060,
    3061,  3062,  3063,  3064,  3065,  3066,  3067,  3068,  3069,  3070,
    3071,  3072,  3073,  3074,  3075,  3078,  3089,  3090,  3093,  3102,
    3106,  3112,  3118,  3123,  3126,  3131,  3136,  3139,  3145,  3150,
    3158,  3159,  3161,  3165,  3173,  3177,  3180,  3184,  3190,  3194,
    3198,  3206,  3207,  3210,  3216,  3220,  3223,  3348,  3353,  3358,
    3363,  3368,  3374,  3404,  3408,  3412,  3416,  3420,  3426,  3430,
    3433,  3437,  3443,  3457,  3466,  3474,  3475,  3476,  3479,  3480,
    3483,  3484,  3499,  3515,  3523,  3524,  3525,  3528,  3529,  3532,
    3539,  3540,  3543,  3557,  3564,  3565,  3580,  3581,  3582,  3583,
    3584,  3587,  3590,  3596,  3602,  3606,  3610,  3617,  3624,  3631,
    3638,  3644,  3650,  3656,  3659,  3660,  3663,  3669,  3675,  3681,
    3688,  3695,  3703,  3704,  3707,  3711,  3719,  3723,  3726,  3731,
    3736,  3740,  3746,  3762,  3781,  3787,  3788,  3794,  3795,  3801,
    3802,  3803,  3804,  3805,  3806,  3807,  3808,  3809,  3810,  3811,
    3812,  3813,  3816,  3817,  3821,  3827,  3828,  3834,  3835,  3841,
    3842,  3848,  3851,  3852,  3863,  3864,  3867,  3871,  3874,  3880,
    3886,  3887,  3890,  3891,  3892,  3895,  3899,  3903,  3908,  3913,
    3918,  3924,  3928,  3932,  3936,  3942,  3947,  3951,  3959,  3968,
    3969,  3972,  3975,  3979,  3984,  3990,  3991,  3994,  3997,  4001,
    4005,  4009,  4014,  4021,  4026,  4034,  4039,  4048,  4049,  4055,
    4056,  4057,  4060,  4061,  4065,  4069,  4075,  4076,  4079,  4085,
    4089,  4092,  4097,  4103,  4104,  4107,  4108,  4109,  4115,  4116,
    4117,  4118,  4121,  4122,  4128,  4129,  4132,  4133,  4136,  4142,
    4149,  4156,  4167,  4168,  4169,  4172,  4180,  4192,  4199,  4202,
    4208,  4212,  4215,  4221,  4230,  4241,  4247,  4273,  4274,  4283,
    4284,  4287,  4296,  4307,  4308,  4309,  4310,  4311,  4312,  4313,
    4314,  4315,  4316,  4317,  4318,  4319,  4320,  4321,  4324,  4347,
    4348,  4349,  4352,  4353,  4354,  4355,  4356,  4359,  4363,  4366,
    4370,  4377,  4380,  4396,  4397,  4401,  4407,  4408,  4414,  4415,
    4421,  4422,  4428,  4431,  4432,  4443,  4449,  4455,  4456,  4459,
    4465,  4466,  4467,  4470,  4477,  4482,  4487,  4490,  4494,  4498,
    4504,  4505,  4512,  4518,  4519,  4522,  4523,  4526,  4532,  4538,
    4542,  4545,  4549,  4553,  4563,  4567,  4570,  4576,  4583,  4587,
    4593,  4607,  4621,  4626,  4632,  4648,  4652,  4660,  4664,  4668,
    4678,  4681,  4682,  4685,  4686,  4687,  4688,  4699,  4710,  4716,
    4737,  4743,  4760,  4766,  4767,  4768,  4771,  4772,  4773,  4776,
    4777,  4780,  4796,  4802,  4808,  4815,  4829,  4837,  4845,  4851,
    4855,  4859,  4863,  4867,  4874,  4879,  4890,  4904,  4910,  4914,
    4918,  4922,  4926,  4930,  4934,  4938,  4944,  4950,  4958,  4959,
    4960,  4963,  4964,  4968,  4974,  4975,  4981,  4982,  4988,  4989,
    4995,  4998,  4999,  5000,  5009,  5020,  5021,  5024,  5032,  5033,
    5034,  5035,  5036,  5037,  5038,  5039,  5040,  5041,  5042,  5043,
    5044,  5045,  5048,  5049,  5050,  5051,  5052,  5059,  5066,  5073,
    5080,  5087,  5094,  5101,  5108,  5115,  5122,  5129,  5136,  5143,
    5146,  5147,  5148,  5149,  5150,  5151,  5152,  5155,  5159,  5163,
    5167,  5171,  5175,  5181,  5182,  5192,  5196,  5200,  5216,  5217,
    5220,  5221,  5222,  5223,  5224,  5227,  5228,  5229,  5230,  5231,
    5232,  5233,  5234,  5235,  5236,  5237,  5238,  5239,  5240,  5241,
    5242,  5243,  5244,  5245,  5246,  5247,  5248,  5249,  5250,  5253,
    5273,  5277,  5291,  5295,  5299,  5305,  5309,  5315,  5316,  5317,
    5320,  5321,  5324,  5325,  5328,  5334,  5335,  5338,  5339,  5342,
    5343,  5346,  5347,  5350,  5358,  5385,  5390,  5395,  5401,  5402,
    5405,  5409,  5429,  5430,  5431,  5432,  5435,  5439,  5443,  5449,
    5450,  5453,  5454,  5455,  5456,  5457,  5458,  5459,  5460,  5461,
    5462,  5463,  5464,  5465,  5466,  5467,  5468,  5469,  5472,  5473,
    5474,  5475,  5476,  5477,  5478,  5481,  5482,  5483,  5484,  5487,
    5488,  5489,  5490,  5493,  5494,  5497,  5503,  5511,  5524,  5531,
    5537,  5543,  5552,  5553,  5554,  5555,  5556,  5557,  5558,  5559,
    5560,  5561,  5562,  5563,  5564,  5565,  5566,  5567,  5568,  5569,
    5570,  5571,  5572,  5573,  5576,  5585,  5586,  5587,  5588,  5601,
    5607,  5608,  5609,  5612,  5618,  5619,  5620,  5621,  5622,  5625,
    5631,  5632,  5633,  5634,  5635,  5636,  5637,  5638,  5639,  5642,
    5646,  5654,  5661,  5662,  5663,  5664,  5665,  5666,  5667,  5668,
    5669,  5670,  5671,  5672,  5675,  5676,  5677,  5678,  5681,  5682,
    5683,  5684,  5685,  5688,  5694,  5695,  5696,  5697,  5698,  5699,
    5700,  5703,  5709,  5710,  5711,  5712,  5715,  5721,  5722,  5723,
    5724,  5725,  5726,  5727,  5728,  5729,  5731,  5737,  5738,  5739,
    5740,  5741,  5742,  5743,  5744,  5747,  5753,  5754,  5755,  5756,
    5757,  5760,  5766,  5767,  5770,  5776,  5777,  5778,  5781,  5787,
    5788,  5789,  5790,  5793,  5799,  5800,  5801,  5802,  5805,  5809,
    5814,  5818,  5825,  5826,  5827,  5828,  5829,  5830,  5831,  5832,
    5833,  5834,  5835,  5836,  5837,  5838,  5841,  5842,  5843,  5846,
    5847,  5850,  5858,  5866,  5867,  5870,  5878,  5886,  5887,  5890,
    5894,  5901,  5902,  5903,  5906,  5913,  5920,  5921,  5922,  5923,
    5924,  5925,  5926,  5927,  5928,  5929,  5932,  5937,  5942,  5947,
    5952,  5957,  5964,  5965,  5966,  5967,  5968,  5971,  5972,  5973,
    5974,  5975,  5976,  5977,  5978,  5979,  5980,  5981,  5982,  5991,
    5992,  5995,  5998,  5999,  6002,  6005,  6008,  6012,  6023,  6024,
    6025,  6028,  6029,  6030,  6031,  6032,  6033,  6034,  6035,  6036,
    6037,  6038,  6039,  6040,  6041,  6042,  6043,  6044,  6045,  6048,
    6049,  6050,  6053,  6054,  6055,  6056,  6059,  6060,  6061,  6062,
    6063,  6066,  6067,  6068,  6069,  6072,  6077,  6081,  6085,  6089,
    6093,  6097,  6102,  6107,  6112,  6117,  6122,  6129,  6133,  6139,
    6140,  6141,  6142,  6145,  6153,  6154,  6157,  6158,  6159,  6160,
    6161,  6162,  6163,  6164,  6167,  6173,  6174,  6177,  6183,  6184,
    6185,  6186,  6189,  6195,  6201,  6207,  6210,  6216,  6217,  6218,
    6219,  6225,  6231,  6232,  6233,  6234,  6235,  6236,  6239,  6245,
    6246,  6249,  6255,  6256,  6257,  6258,  6259,  6262,  6276,  6277,
    6278,  6279,  6280
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

#define YYPACT_NINF (-1832)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1045)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1832,  8352, -1832,   344, -1832, -1832,   172,   164,   164,   164,
    1341,  1341,  1341,  1341,  1341,  1341,  1341,  1341, -1832, -1832,
    2984,   254,   911,   268,   960,   289,  8769,   892,  1271,   309,
    7963,   127,   181,  3139,   320, -1832, -1832, -1832, -1832,   156,
    1341,  1341,  1341,  1341, -1832, -1832, -1832,  1239, -1832,   164,
   -1832,   164,   188,  7118, -1832,   344, -1832, -1832,   136,   244,
     344,   164, -1832,   105,   353,  7118,   164, -1832,   589, -1832,
     164, -1832, -1832,  1341, -1832,  1341,  1341,  1341,  1341,  1341,
    1341,  1341,   522,  1341,  1341,  1341,  1341, -1832,  1341, -1832,
    1341,  1341,  1341,  1341,  1341,  1341,  1341,  1341,   605,  1341,
    1341,  1341,  1341, -1832,  1341, -1832,  1341,  1341,  1341,  1341,
    1341,  1341,  1679,  1341,  1341,  1341,  1341,  1341,   824,  1341,
    1341,  1341,   721,  1341,  2003,  2080,  2319,  2539,  1341,  1341,
    1341,  2575, -1832,  1341,  1097,  1341,  1341,  1341,  1341,  1368,
    1968,  1341, -1832,  1341,  1341,  1341,  1341,  1341,   682,  1341,
   -1832,  1341, -1832,  1475,  1043,   739,   625, -1832, -1832, -1832,
   -1832,   757,  1250,  1328,  1514,  3149,  2305,   743,  1985,  1801,
    1020,   185,   897,   695,   954,  3459,   930,  4254,   657, -1832,
    4960,   827,  2219,   519,   534,   810,   205,  1217,   282,  1422,
    3489, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832,  4033, -1832, -1832,   420,  7592,   437,  1044,   736,
    7963,   164, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,  1034, -1832, -1832,   432, -1832, -1832,  1034, -1832, -1832,
    1341,  1341,  1341,  1341,  1341,  1341,  1341,  1341,   605,  1341,
    1341,  1341,  1341, -1832, -1832, -1832,  1497, -1832, -1832, -1832,
    1341,  1341,  1341,    18, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,   703,   722,   728, -1832, -1832, -1832,   654,   562,  1222,
   -1832, -1832, -1832,   702, -1832, -1832, -1832,   161,   161, -1832,
     678,   164,  4587,  3817,   623,   639, -1832,   116,   597, -1832,
   -1832, -1832, -1832, -1832,   207,   847,   750, -1832,   836,   983,
   -1832,   633,  7118, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832,   852, -1832, -1832,   845, -1832, -1832, -1832,   667,
   -1832,  5589, -1832, -1832,   764, -1832,   310, -1832,   417, -1832,
   -1832, -1832, -1832,  1055, -1832,   124, -1832, -1832,   965, -1832,
   -1832, -1832,  1170,  1008,  1010,   673, -1832,   435, -1832,  6629,
   -1832, -1832, -1832,   994, -1832, -1832, -1832,  1014, -1832, -1832,
    6973,  6973, -1832, -1832,   178,   686,   705, -1832, -1832,   715,
   -1832, -1832, -1832,   740, -1832,   742,  1060,  7118, -1832,   105,
     353, -1832,   589, -1832, -1832,  1341,  1341,  1341,   838, -1832,
   -1832, -1832,  7118, -1832,   167, -1832, -1832, -1832,   175, -1832,
   -1832, -1832,   341,   353, -1832, -1832, -1832,   381, -1832, -1832,
     589, -1832,   576,   766, -1832, -1832, -1832, -1832,  1341, -1832,
   -1832, -1832, -1832,   589, -1832, -1832, -1832,  1092, -1832, -1832,
   -1832, -1832,  1341, -1832, -1832, -1832, -1832, -1832, -1832,  1341,
    1341, -1832, -1832, -1832,  1117,  1143, -1832,  1341,  1148, -1832,
    1341, -1832,  1341, -1832,  1341, -1832,  1341, -1832, -1832, -1832,
   -1832,  1341, -1832, -1832, -1832,  1341,  1341,   305,   164, -1832,
   -1832, -1832,   589, -1832, -1832,  1341, -1832, -1832,  1341, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,  1341, -1832,
     164, -1832, -1832, -1832, -1832,  1130, -1832, -1832, -1832, -1832,
   -1832,  1168,   617, -1832, -1832,   906, -1832, -1832,  1096,   160,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832,   265,   520, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832,  1286, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
    3591, -1832, -1832, -1832, -1832,  1113, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832,  3675, -1832,  5296, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832,  4273, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832,   380, -1832, -1832,   857,
   -1832, -1832, -1832, -1832, -1832, -1832,   868, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,  2283,
   -1832, -1832, -1832, -1832,   907,   331,   912,  1159, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832,   866,   909, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832,   589, -1832,   766, -1832,  1341, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
    1034, -1832, -1832, -1832, -1832,    56,   418,   505,   215, -1832,
   -1832, -1832,  5797,  1188,  7384,  7963,  1122, -1832, -1832, -1832,
   -1832,  1270,  1278,   117,  1267,  1280,  1283,   194,  1321,  2283,
    1323,  7384,   170,  7384,   922,  7384, -1832, -1832,  1245,  7963,
     929,  7384,  7384,  1302,  1408, -1832,  6718,   183, -1832,  1408,
   -1832, -1832, -1832,  1032, -1832,  1295,  1297,   852, -1832, -1832,
   -1832,   989,  1408,  1303,  1331,  1351,  1408,   845, -1832, -1832,
     694, -1832, -1832,  7384, -1832, -1832,  6005,  1375,  1250,  1328,
    1514,  3149, -1832,  1985,   714, -1832, -1832, -1832, -1832,  1378,
   -1832, -1832, -1832, -1832,  7384, -1832,  1252,  1451,  1455,  1108,
     823,   333, -1832, -1832, -1832, -1832,  1472,  1354,  1488, -1832,
   -1832, -1832, -1832,  1499, -1832, -1832, -1832, -1832,   635, -1832,
   -1832,  1510,  1527, -1832, -1832, -1832,  1435,  1441, -1832, -1832,
     764, -1832, -1832,  1537, -1832, -1832, -1832, -1832,  1542, -1832,
   -1832,  6213, -1832,  1542, -1832, -1832, -1832,   153, -1832, -1832,
    1055, -1832,  1544, -1832,   164, -1832,  1191, -1832,   164,   121,
   -1832,  8509,  8509,  8509,  8509,  8509,  7963,   157,  8174, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832,  8509, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832,  1004, -1832,  1263,  1545,  1548,  1201,   830,  1562,
   -1832, -1832, -1832,  8174,  7384,  7384,  1468,   149,   344,  1569,
   -1832,   872,   344,  1482, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832,  1540,  1224,  1225,  1236, -1832,  1238,  1249,
   -1832, -1832, -1832, -1832,  1320,  1308,  1015,  1408, -1832, -1832,
    1513,  1516,  1518,  1261,  1522, -1832,  1526,  1269, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832,  1529, -1832, -1832, -1832, -1832,
   -1832,  1341, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,  1564,  1043, -1832, -1832, -1832, -1832,  1566, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832,   835, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,  1543, -1832,  1480, -1832, -1832,  1450, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832,  1145, -1832,  1152,  1534,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832,  1073,  1439,  1275,
    1275, -1832, -1832, -1832,  1442, -1832, -1832, -1832, -1832,  1444,
    1454, -1832,  1456,  1453,  1457,   683, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832,  1590, -1832, -1832,  1606, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,  1291, -1832,  1296, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,  1607,  1609,  1372, -1832, -1832, -1832, -1832, -1832,  1613,
     125, -1832, -1832, -1832,  1359, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832,  1360,  1362,  1363,  1614, -1832, -1832,   922, -1832,
   -1832, -1832,  1626, -1832, -1832, -1832, -1832,  7384,  3149,  1985,
    1725,  6421, -1832,   124,   220,  1723,  4020,  1408,  1408,  1634,
    7963,  7384,  7384,  7384, -1832,  1643,  7384,  1698,  7384, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832,  1648, -1832,   249,  1730,
   -1832, -1832,   218,   351,   331, -1832,   242,   386,   206,  1710,
   -1832,  7384, -1832, -1832,   983,  1410,  1121,   328, -1832,   883,
    1562,   983, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
    1608,   545, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,   977,   980, -1832,  1068, -1832, -1832, -1832,  7384,  1751,
    7384, -1832, -1832, -1832,   681,   713, -1832,  7384, -1832, -1832,
    1396, -1832, -1832,  7384,  7384,  7384,  7384,  7384,  1660,  7384,
    7384,   189,  7384,  1542,  7384,  1680,  1759,  1683,  3098,  3098,
   -1832, -1832, -1832,  7384,  1354,  7384,  1354, -1832,  1752,  1757,
   -1832,   929, -1832,  7963, -1832,  7963, -1832, -1832, -1832,  1263,
    1545,  1548, -1832,   983, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,  1414,  8509,  8509,  8509,  8509,  8509,  8509,  8509,  8509,
    8611,  8509,  8509,  1025, -1832,   915, -1832, -1832, -1832, -1832,
   -1832,  1685, -1832,   321,   795, -1832,  2430,  3919,  2584,  3552,
    1786, -1832, -1832, -1832, -1832, -1832, -1832,  1428,  1430,  1437,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832,  1795, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832,  4020, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832,  1433,  1434, -1832,
   -1832, -1832, -1832, -1832, -1832,  1372,    75,  1703, -1832, -1832,
   -1832, -1832, -1832,  1306, -1832, -1832, -1832, -1832, -1832,  1538,
     973, -1832,  1648,  1030, -1832,   421,   249, -1832,   855, -1832,
   -1832,  7384,  7384,  1802, -1832,  1712,  1712, -1832,   220, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,  1458,  1723,
    7118,   220, -1832, -1832, -1832, -1832, -1832, -1832,  7384, -1832,
   -1832,   211,  1517,  1520,  1813, -1832, -1832, -1832,  1524,   153,
   -1832,  7963,   153,  7384,  1794, -1832,  8403, -1832,  1650,  1549,
    1531,  1541,  1015,  1121, -1832,  1712,  1712, -1832,   328, -1832,
    6718, -1832,  5314, -1832, -1832, -1832, -1832,  1837, -1832, -1832,
    1383, -1832, -1832,  1383, -1832,  1777,  1383, -1832, -1832,  7384,
   -1832, -1832, -1832, -1832, -1832,  1252,  1451,  1455, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832,  1849,  7384,  1690,  7384, -1832,
   -1832, -1832, -1832,  1354, -1832,  1354,  1542, -1832, -1832,   155,
    7118,  6736,   195, -1832, -1832, -1832,  1569,  1853, -1832, -1832,
    1263,  1545,  1548, -1832,   212,  1569, -1832, -1832,   883,  8509,
    8611, -1832,  1753,  1823, -1832, -1832, -1832, -1832, -1832,   164,
     164,   164,   164,   164,  1760,   634,   164,   164,   164,   164,
   -1832, -1832, -1832,   344, -1832,  1503,   229, -1832,  1767, -1832,
   -1832, -1832,   344,   344,   344,   344,   344,  7963, -1832,  1712,
    1712,  1509,  1394,  1770,   997,  1264,  1686, -1832, -1832, -1832,
     344,   344,   450, -1832,  7963,  1712,  1515,   997,  1264, -1832,
   -1832, -1832,   344,   344,   450,  1771,  1519,  1780, -1832, -1832,
   -1832, -1832, -1832,  3293,  4272,  2821,  3571,  1993, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832,  4625,  2462, -1832, -1832,  1783,
   -1832, -1832, -1832,  1876, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832,  1785, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,  2494, -1832,  1470,   761,  2385,  1789, -1832, -1832, -1832,
   -1832, -1832,  1517,  1520, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832,  1524, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832,  7384, -1832, -1832, -1832, -1832, -1832, -1832,  7963,
    1535,   220, -1832, -1832, -1832, -1832, -1832, -1832, -1832,  1361,
    1880, -1832,  1806, -1832,  1807, -1832,  1361,  1808, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832,  7384,   161,   161,   983,  1562,
   -1832,   286,  1809, -1832,   203,   922,  1811, -1832, -1832, -1832,
   -1832, -1832, -1832,   344, -1832,   545, -1832, -1832, -1832, -1832,
   -1832, -1832,  7384, -1832,  1833, -1832,  1542,  1542,  7963, -1832,
     279,  1557,  1917,   983, -1832,  1569,  1569,  1734,  1822, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
     164,   164,   164, -1832, -1832, -1832, -1832, -1832,   658, -1832,
   -1832, -1832, -1832, -1832,  1824, -1832, -1832, -1832, -1832, -1832,
   -1832,  1112, -1832,   344,   344,   589, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832,  1309, -1832, -1832,
   -1832, -1832, -1832,  1161, -1832, -1832, -1832, -1832, -1832,   664,
     344,   589,   707,  1161, -1832, -1832, -1832,  1778,   658,   344,
   -1832, -1832, -1832, -1832, -1832, -1832,  1707,  1084,  2590, -1832,
   -1832, -1832,  1828, -1832,  1372, -1832, -1832, -1832,  1570,   871,
    1341, -1832, -1832, -1832, -1832, -1832,  1712,  1830,   871,  1831,
    1341, -1832, -1832, -1832, -1832, -1832,  1834,  1341, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832,  7118, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,  1642, -1832,   535, -1832, -1832, -1832,   249, -1832, -1832,
   -1832, -1832, -1832, -1832,  1835,  1646, -1832, -1832,  1648,   249,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832,  7384,  1579,  7963,
   -1832, -1832,  1357,  6736, -1832, -1832,  1762,   344,  1587,  1588,
    1589,  1593,  1596, -1832, -1832, -1832,  1598,  1603,  1605,  1611,
     232,   344, -1832, -1832,  1929,  7963, -1832, -1832, -1832, -1832,
   -1832,   997, -1832,  1264, -1832,  7783, -1832, -1832,  2847, -1832,
     231,   344,   344, -1832, -1832, -1832, -1832, -1832,  1962, -1832,
    1615, -1832, -1832,   344,   344, -1832,   344,   344,   344,   344,
     344, -1832,  1843,   344, -1832,  1616, -1832, -1832, -1832, -1832,
   -1832,  1882, -1832, -1832,  1517,  1520,  1524, -1832, -1832, -1832,
   -1832,  1622,   983, -1832, -1832,  1734, -1832, -1832, -1832, -1832,
   -1832,  1624,  1625,  1627, -1832, -1832, -1832, -1832, -1832, -1832,
     202, -1832, -1832, -1832,  1867, -1832, -1832, -1832, -1832,  7963,
     344,  1983,  1987, -1832,   997, -1832, -1832, -1832, -1832,   344,
    1309,  1893, -1832, -1832, -1832,   580, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832,  1899, -1832,  1900, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832,   871, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832,  1762,  1868,  4978,  3063,
    3701,  2625, -1832, -1832, -1832,  2160,  2039,  1330,  1504,   190,
   -1832,  1477,  1112, -1832,  7963, -1832,  1309, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832,  1905,  1906, -1832,  1998,   210, -1832,
     344, -1832, -1832, -1832, -1832, -1832,   344,   344,   344,   344,
     344,  2296,  1282,  2902,   344,   344,   344,   344, -1832, -1832,
     196,  1649,  1778, -1832,  2006, -1832, -1832, -1832, -1832, -1832,
    1912,  1900,   344, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,   658, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832,   344,   344,   344, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     428,   428,   428,   428,   428,   428,   428,   428,   432,   435,
     428,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   237,   434,     9,    28,    29,     0,
     428,   428,   428,   428,    68,    67,     3,     0,    71,     0,
     429,     0,   453,     0,    66,     0,   422,   423,     0,     0,
       0,     0,   604,    87,    89,     0,     0,   289,     0,   311,
       0,   335,    72,   428,    73,   428,   428,   428,   428,   428,
     428,   428,     0,   428,   428,   428,   428,    74,   428,    75,
     428,   428,   428,   428,   428,   428,   428,   428,     0,   428,
     428,   428,   428,    76,   428,    77,   428,   459,   428,   459,
     428,   459,   459,   428,   428,   459,   428,   459,     0,   428,
     459,   459,     0,   428,   459,   459,   459,   459,   428,   428,
     428,   459,    35,   428,   459,   428,   428,   428,   428,   459,
     459,   428,    47,   428,   428,   428,   428,   459,     0,   428,
      80,   428,    81,     0,     0,     0,   761,   732,   424,   425,
     426,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    25,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   945,   946,   947,   948,   949,   950,   951,   952,   953,
     954,   955,   956,   957,   958,   959,   960,   961,   962,   963,
     964,   966,     0,   968,   967,     0,     0,     0,     0,    34,
       0,     0,    85,   728,   727,   733,   734,   252,   744,   745,
     738,   936,   739,   742,   746,   743,   740,   741,   735,  1052,
    1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,  1061,  1062,
    1063,  1064,  1065,    53,  1070,  1071,  1072,  1073,  1067,  1068,
    1069,   736,  1316,  1317,  1318,  1319,  1320,  1321,  1322,  1323,
     737,     0,   249,   250,     0,    33,   233,     0,    21,   235,
     428,   428,   428,   428,   428,   428,   428,   428,     0,   428,
     428,   428,   428,    16,   238,    39,   239,   433,   430,   431,
     428,   428,   428,    13,   857,   830,   832,    70,    69,   436,
     438,     0,     0,     0,   455,   454,   456,     0,   594,     0,
     712,   713,   714,     0,   927,   928,   929,   496,   497,   932,
     719,     0,     0,     0,   512,   518,   523,     0,   547,   572,
     584,   585,   661,   667,   688,     0,     0,   972,     0,     7,
      92,   461,   463,   477,   464,    61,   272,   492,   473,   500,
     471,    13,   510,    14,    59,   521,   469,   470,    46,   575,
      40,     0,    54,    60,   592,    40,   660,    40,   666,    18,
      24,   483,    45,   686,   489,     0,   490,   475,     0,   718,
     474,   763,   766,   768,   770,   772,   773,   780,   782,     0,
     781,   725,   499,   936,   478,   484,   476,   735,   493,    62,
       0,     0,    65,   447,     0,     0,     0,    91,   441,     0,
      95,   304,   303,     0,   444,     0,     0,     0,   604,   112,
     114,   289,     0,   311,   335,   428,   428,   428,    13,   857,
     830,   832,     0,    60,     0,   136,   137,   138,     0,   130,
     131,   139,     0,   132,   133,   141,   142,     0,   134,   135,
       0,   143,     0,   145,   146,   834,   835,   833,   428,    13,
      36,    44,    51,     0,    60,   203,   460,   205,   170,   171,
     172,   173,   428,   174,   176,   200,   199,   198,   192,   428,
     459,   196,   195,   197,   834,   835,   836,   428,     0,    13,
     428,   177,   428,   180,   428,   183,   428,   189,    36,    44,
      51,   428,   186,    78,   220,   428,   428,   460,   216,   218,
     215,   222,     0,   223,    13,   428,   208,   207,   428,   213,
     211,    44,    79,   224,   225,   226,   227,   230,   428,   229,
       0,  1078,  1075,  1076,    56,     0,   752,   753,   754,   755,
     756,   758,     0,   977,   979,     0,   978,    52,     0,     0,
    1314,  1315,    56,  1080,  1081,    55,    20,    55,  1084,  1085,
    1086,  1087,    30,     0,     0,  1090,  1091,  1092,  1093,  1094,
       9,  1112,  1113,  1107,  1102,  1103,  1104,  1105,  1106,  1108,
    1109,  1110,  1111,     0,    28,    55,  1127,  1126,  1125,  1128,
    1129,  1130,    31,    55,  1133,  1134,  1135,    32,  1144,  1145,
    1137,  1138,  1139,  1141,  1140,  1142,  1143,    29,    55,  1152,
    1149,  1148,  1153,  1151,  1150,  1154,    31,  1157,  1160,  1156,
    1158,  1159,     8,  1163,  1162,    19,  1165,  1166,  1167,    11,
    1171,  1172,  1169,  1170,    57,  1177,  1174,  1175,  1176,    58,
    1224,  1218,  1221,  1222,  1216,  1217,  1219,  1220,  1223,  1225,
       0,  1178,    55,  1258,  1259,     0,    15,  1204,  1203,  1196,
    1197,  1198,  1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,
    1190,  1191,    53,  1200,  1199,  1202,  1201,  1193,  1194,  1195,
    1211,  1213,  1212,     0,    25,     0,  1208,  1207,  1206,  1205,
    1312,  1309,  1310,     0,  1311,    49,    55,    28,  1329,  1004,
      29,  1328,  1331,  1002,  1003,    34,     0,    48,    48,     0,
      48,  1335,    48,  1338,  1337,  1339,     0,    48,  1326,  1325,
      27,  1347,  1344,  1342,  1343,  1345,  1346,    23,  1350,  1349,
      17,    55,  1353,  1356,  1352,  1355,    38,    37,   940,   941,
     942,    51,   943,    34,    37,   938,   939,  1019,  1020,  1026,
    1012,  1013,  1011,  1021,  1022,  1042,  1015,  1024,  1017,  1018,
    1023,  1014,  1016,  1009,  1010,  1040,  1039,  1041,    51,     0,
      12,  1027,   983,   982,     0,   780,     0,     0,    48,    27,
      23,    17,    38,  1357,   987,   988,   965,   986,     0,   726,
    1066,   232,   251,    82,   234,    83,    60,   154,   155,   132,
     156,   157,     0,   158,   160,   161,   428,    13,    36,    44,
      51,    86,    84,   240,   241,   243,   242,   245,   246,   244,
     247,   854,   854,   854,    97,     0,     0,   547,     0,   450,
     451,   452,     0,     0,     0,     0,     0,   934,   933,   930,
     931,     0,     0,     0,    37,    37,     0,     0,     0,     0,
      12,     0,     0,     0,   556,     0,   545,   546,     0,     0,
       0,     0,     0,     0,     0,     6,     0,     0,   784,     0,
     462,   465,   494,     0,   468,     0,     0,   511,   514,   472,
     479,     0,     0,     0,     0,     0,     0,   522,   524,   480,
       0,   571,   481,     0,    47,    16,     0,     0,    20,    30,
       9,    28,   895,    29,     0,   900,   898,   899,    14,     0,
      40,    40,   885,   886,     0,   622,   625,   627,   629,   631,
     632,   637,   642,   640,   641,   643,   645,   583,   609,   610,
     620,   887,   611,   618,   612,   619,   615,   616,     0,   613,
     614,     0,   644,   617,   482,   491,     0,     0,   601,   600,
     593,   596,   485,     0,   679,   680,   681,   659,   664,   677,
     486,     0,   665,   670,   487,   488,   682,     0,   704,   705,
     687,   689,   692,   702,     0,   730,     0,   729,     0,     0,
     720,     0,     0,     0,     0,     0,     0,     0,     0,   920,
     921,   922,   923,   924,   925,   926,    20,    30,     9,    28,
      31,   912,    29,    31,     8,    19,    11,    57,    58,    53,
      15,    25,    49,    40,     0,   902,   870,   903,   777,   778,
     882,   869,   859,   858,   874,   876,   878,   880,   881,   868,
     904,   905,   871,     0,     0,     0,     0,     7,     0,   824,
     823,   881,     0,     0,   391,    60,   256,   273,   290,   317,
     336,   457,   111,     0,     0,     0,     0,   118,     0,     0,
     854,   854,   854,   120,     0,     0,   547,     0,   129,   153,
       0,     0,     0,     0,     0,   144,     0,     0,   854,   148,
     151,   149,   152,   169,   191,     0,   206,   175,   194,   193,
      12,   428,   179,   178,   181,   184,   190,   185,   182,   188,
     187,   217,   219,   221,   210,   209,   212,   214,   228,   231,
    1077,     0,     0,    55,   749,   750,    22,     0,   975,   762,
      42,    42,  1313,  1082,  1079,  1088,  1083,    20,    28,    20,
      28,  1089,  1114,  1115,  1116,  1117,    28,  1099,  1124,  1123,
    1132,  1131,  1136,  1147,  1146,  1155,  1161,  1164,  1168,  1173,
      10,  1242,  1248,  1246,  1237,  1238,  1241,  1243,  1232,  1233,
    1234,  1235,  1236,  1244,  1239,  1240,  1245,  1180,  1247,  1179,
    1260,    15,  1256,  1192,  1210,  1209,  1214,  1264,  1261,  1262,
    1263,  1265,  1266,  1267,  1268,  1269,  1270,  1271,  1272,  1273,
    1274,  1275,  1276,  1277,  1278,  1295,    50,  1307,  1330,   998,
     999,  1005,    48,  1000,  1327,     0,  1332,  1334,     0,  1336,
    1324,  1341,  1348,  1354,  1351,   937,   944,   935,  1025,  1028,
    1029,     0,  1031,     0,  1030,  1032,  1033,    12,    12,  1034,
    1006,     0,     0,   980,  1359,  1358,  1360,  1361,  1362,     0,
       0,   747,   168,   159,     0,   854,   163,   166,   164,   167,
     236,   248,     0,     0,     0,     0,   356,    13,   556,   381,
      36,   361,     0,    44,   386,   831,    51,     0,    28,    29,
     586,     0,   595,     0,   706,   708,     0,     0,     0,     0,
       0,     0,     0,     0,    12,     0,     0,  1034,     0,   513,
     427,   519,   520,    36,   554,   555,     0,    44,     0,     0,
     701,    45,   696,   695,     0,   700,   698,   699,     0,   673,
     675,     0,   495,   796,     7,     7,   798,   793,   795,   881,
     820,     7,   783,   458,   282,   516,   517,   515,   537,    20,
       0,     0,   535,   531,   526,   527,   528,   529,   532,   530,
     525,     0,     0,    53,     0,   651,   896,   897,     0,   646,
       0,   888,   891,   892,   889,   890,   901,     0,   894,   893,
       0,   609,   618,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   653,     0,     0,     0,     0,     0,     0,
     598,   599,   597,     0,     0,     0,   668,   691,   696,   695,
     690,     0,    10,     0,   722,     0,   721,   764,   765,   767,
     769,   771,   774,     7,   501,   503,   779,   889,   911,   890,
     913,   910,   909,   915,   907,   908,   906,   916,   914,   917,
     918,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   865,   864,   881,   970,  1051,   826,   825,
      63,     0,    64,     0,     0,   109,     0,     0,     0,     0,
       0,    60,   256,   273,   290,   317,   336,     0,     0,     0,
      13,    36,    44,    51,   448,   437,   439,   273,   442,   445,
     336,    12,   204,   201,    12,     0,   757,   751,   748,    52,
     759,   760,  1095,  1097,  1096,  1098,    55,  1119,  1121,  1120,
    1122,  1101,    28,     0,  1254,  1226,  1251,  1228,  1255,  1231,
    1252,  1253,  1229,  1249,  1250,  1227,  1230,  1257,  1292,  1291,
    1293,  1294,  1300,  1282,  1283,  1284,  1285,  1297,  1286,  1287,
    1288,  1289,  1290,  1298,  1299,  1301,  1302,  1303,  1304,  1305,
    1306,    55,  1281,  1280,  1296,    49,  1001,     0,     0,    28,
      28,    29,    29,  1007,  1008,   980,   980,     0,    26,   985,
     989,   990,    34,     0,   336,    12,   371,   376,   366,     0,
       0,    98,     0,     0,   105,     0,     0,   100,     0,   107,
     588,     0,     0,   587,   709,     0,     0,   803,   707,   799,
    1242,  1246,  1241,  1245,  1247,    53,    10,    10,     0,   792,
       0,   790,    37,    37,    12,   508,    12,    12,     0,    12,
     544,     0,   557,   560,     0,   553,   549,   548,   550,     0,
     683,     0,     0,     0,     0,   787,     0,   788,     0,    13,
       0,     0,   547,   797,   806,     0,     0,   819,   794,   804,
     786,   785,     0,   536,    28,   540,   541,    53,   539,   573,
       0,   577,   574,     0,   579,     0,     0,   581,   652,     0,
     656,   658,   621,   623,   624,   626,   628,   630,   638,   639,
     633,   636,   635,   634,   648,   647,     0,     0,     0,  1043,
    1044,  1045,  1046,   662,   678,   669,   671,   703,   731,     0,
       0,     0,     0,   504,   919,   867,   861,     0,   872,   873,
     875,   877,   879,   866,   775,   860,   776,   883,   884,     0,
       0,   775,     0,     0,    60,   393,   392,   395,   394,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      88,   258,   257,     0,   255,     0,     0,    55,     0,    90,
     275,   274,     0,     0,     0,     0,     0,     0,   300,     0,
       0,     0,     0,     0,     0,     0,     0,    93,   292,   291,
       0,     0,     0,   466,     0,     0,     0,     0,     0,    94,
     319,   318,     0,     0,     0,     0,     0,     0,    13,    96,
     338,   337,   128,     0,     0,     0,     0,     0,   371,   376,
     366,   121,   126,   122,   127,     0,     0,   150,   202,     0,
     976,  1118,  1100,     0,  1279,  1308,  1333,  1340,  1035,  1036,
    1037,  1038,    41,     0,    26,   981,   997,   993,   992,   991,
      34,     0,   165,     0,     0,     0,     0,    13,   358,   357,
     360,   359,   557,   560,    36,   383,   382,   385,   384,    44,
     363,   362,   365,   364,   550,    51,   388,   387,   390,   389,
     589,   591,     0,   801,   802,   800,  1215,   974,   973,     0,
       0,   791,   971,   969,  1048,   509,  1049,    12,  1047,     0,
     562,   564,     0,    36,     0,    36,     0,     0,    44,   697,
     693,   694,    45,    45,   674,     0,     0,     0,     7,   821,
     822,     0,     0,   808,     0,   556,     0,   807,   817,   818,
     805,   498,   283,     0,   534,     0,   533,    55,    55,    47,
      55,   649,     0,   655,     0,   657,   663,   672,     0,   710,
       0,     0,     0,     7,   502,   863,   862,   605,     0,   110,
     449,   355,   440,   272,   443,   289,   311,   446,   335,   254,
       0,     0,     0,   355,   355,   355,   355,   259,     0,   420,
     421,    43,   419,   418,     0,   416,   276,   278,   277,   281,
     279,     0,   287,     0,     0,     0,   334,   333,    43,   332,
     396,   398,   399,   397,   352,   400,   353,     0,   351,   307,
     308,   310,   309,     0,   306,   301,   302,   298,   467,     0,
       0,     0,     0,     0,   330,   329,   327,     0,     0,     0,
     341,   113,   115,   116,   117,   119,     0,     0,     0,   140,
     147,    10,     0,   984,   980,   996,   994,   162,     0,     0,
       0,    12,   373,   372,   375,   374,     0,     0,     0,     0,
       0,    12,   378,   377,   380,   379,     0,     0,    12,   368,
     367,   370,   369,   827,    99,   855,   856,   106,   101,   829,
     108,   590,     0,   723,  1050,   566,   567,   568,   569,   570,
     559,     0,   542,     0,   561,   543,   563,     0,   552,   684,
     685,   676,   789,    12,     0,     0,    14,    14,     0,     0,
     284,   538,    31,    31,   582,   580,   650,     0,     0,     0,
     711,   717,     0,   506,   505,   606,   607,     0,     0,     0,
       0,     0,     0,   355,   355,   355,     0,     0,     0,     0,
       0,     0,   344,   417,     0,     0,   294,   296,   297,   299,
     331,     0,    55,     0,   295,     0,   320,   328,     0,   326,
       0,     0,     0,   342,    12,    12,    12,  1074,     0,    26,
       0,    57,    53,     0,     0,   103,     0,     0,     0,     0,
       0,   104,     0,     0,   102,     0,   558,   565,   551,   812,
      12,     0,   815,   816,   557,   560,   550,   576,   578,   654,
     715,     0,     7,   608,   602,   605,   391,   273,   290,   317,
     336,     0,     0,     0,   356,   381,   361,   386,   349,   348,
       0,   345,   350,   280,     0,   288,   354,   293,   305,     0,
       0,     0,   285,    60,     0,    13,    36,    44,    51,     0,
       0,     0,   410,   404,   403,   407,   402,   405,   406,   339,
     340,   124,   125,   123,     0,   995,     0,   840,   839,   846,
     848,   851,   852,   849,   850,   853,     0,   842,   724,   813,
      13,    36,    36,    44,   716,   507,   607,     0,     0,     0,
       0,     0,   371,   376,   366,     0,     0,     0,     0,     7,
     343,   415,     0,   323,     0,   316,     0,   312,   314,   313,
     315,    55,    55,   411,     0,     0,  1181,     0,     0,   843,
       0,   809,   810,   811,   814,   603,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   347,   346,
       0,     0,     0,   324,   286,    55,   325,   321,   409,   408,
       0,     0,     0,    55,    60,   260,   261,   262,   263,    12,
      12,    12,    13,    36,    44,    51,   412,   413,     0,   401,
     322,   845,   844,    43,   841,   271,     0,     0,     0,   264,
     269,   265,   270,   414,   847,   267,   268,   266
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1832, -1832,    -1, -1239,  1002,    43, -1333,  1001,  -939,  -347,
    -899,  -706,  1118,  1234, -1832,  1011,  -529, -1832, -1832,  1240,
   -1832,  -155, -1593,  1246,   -10,   -28,  1464,  -613, -1832, -1832,
    -682, -1832,  -487,  -716,  1247, -1832,  -260, -1832,   910, -1822,
    -479, -1235, -1832,  -876,  -577,  -926, -1832,  -490,   553,  -657,
   -1832,   566,  1484,  -994,  1026, -1832,  -434, -1832,    25, -1832,
   -1832,  2030, -1832, -1832, -1832,  1772,  1769,   243,  1131, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832,    12, -1832,  1628, -1832,   594,  -353,
   -1358, -1832, -1832, -1634,  -420, -1408,  -424,   292,   -64,  -417,
   -1832, -1404, -1402, -1832,  -422, -1385, -1831, -1832,  -198,   -51,
   -1618,  -578,  -111,  -112, -1664, -1660, -1657,  -110,  -108,   -95,
   -1832, -1832,  -218, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832,    55,  -765, -1120,   299,   -37,  3406, -1832,   213, -1832,
   -1832,   458, -1832,   363,   326,  1799, -1832,   114, -1832,  -972,
    1661, -1832, -1832,   291,   570,   756,   787,   -31, -1832, -1832,
   -1409, -1411,  -337, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
     177, -1832, -1832, -1832, -1832,  1203, -1832, -1832, -1832, -1832,
    1196, -1832, -1832, -1832,   197, -1832,  -320, -1447, -1606, -1832,
   -1197, -1674, -1461, -1671, -1460,   221,   225, -1832, -1832,  -918,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832,  1144,  -349,  1675,
     -70,  -138,  -175,   734,   735,   744, -1832,  -816, -1832, -1832,
   -1832, -1832, -1832, -1832,  1852, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832,  -361,   725, -1832, -1832, -1832, -1832,
    1140,   507,  -909,   503,  1258,   731, -1337, -1832, -1832,  1814,
   -1832, -1832, -1832, -1832,  1147, -1832, -1832,   -61,   217,  -853,
    -340,   263,   -26, -1832, -1832, -1832,  1029,     2, -1832, -1832,
   -1832, -1832, -1832,  -162,  -211, -1832, -1832,   712,  -809,  1939,
     -67, -1832,   813, -1272, -1832, -1549, -1832, -1832,   556, -1347,
   -1832, -1832,   526,   524, -1832, -1832,  1749,  -612,  1731,  -583,
    1728,  -576,  1722,   230, -1832, -1755, -1832, -1832,  -141, -1832,
   -1832,  -584,  -567,  1732, -1832,  -364,  -306,  -880,  -854,  -877,
   -1832,  -368,  -847, -1832,  1964,  1928,  -810, -1832, -1525,  -322,
     106,  1840, -1832,   -14, -1832,   677, -1832, -1392, -1832,   762,
   -1832, -1832, -1832, -1832, -1832,   802,  -264,   950,  1459,  1022,
    1841,  1844, -1832, -1832,  -498,   140, -1832, -1832, -1832,  1110,
   -1832, -1832,    26, -1832,    28, -1832,    30, -1832,   -57, -1832,
   -1832, -1832,   -43, -1832,   -42, -1832,   -29, -1832,   -12, -1832,
      -8, -1832,    -7, -1832,    -2, -1832,     6, -1832,     7, -1832,
      11,  1483, -1832,   -81, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832,  1523, -1071, -1832, -1832, -1832, -1832,
   -1832,    15, -1832, -1832, -1832, -1832,   988, -1832, -1832,    16,
   -1832,    24, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832, -1832,
   -1832, -1832
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,  1780,   876,  1155,  1363,  1503,  1157,  1240,   834,
     889,  1182,   821,  1222,   974,  1156,  1361,   805,  1488,  1221,
     975,   693,  1816,  1220,  1417,  1419,  1362,  1149,  1151,   803,
     796,   513,  1090,  1225,  1224,   822,   902,  2013,  1490,  2113,
    1091,   976,   899,   532,  1213,  1207,  1545,  1092,  1128,   800,
     954,  1133,  1120,  1158,  1159,   890,   955,   882,  1781,    46,
      47,    48,    74,    87,    89,   447,   451,   456,   443,   103,
     293,   105,   132,  1096,   475,   142,   150,   152,   275,   278,
     295,   296,   830,  1260,   276,   222,   415,  1733,  1456,   416,
    1457,  1642,  2200,  1961,   419,  1458,   420,  1983,  1984,   423,
    2209,  1459,  1760,  1968,   425,  1460,  2111,  2190,  2191,  1976,
    1977,  2098,  1570,  1575,  1825,  1823,  1824,  1573,  1578,  1454,
    1978,  1742,  2131,  2215,  2216,  2217,  2302,  1743,  1744,  1951,
    1952,  1930,   223,  1302,    49,    50,    61,   450,    52,   454,
    1933,   458,   459,  1935,    71,   464,  1938,   445,   446,  1931,
     314,   315,   316,    53,   427,  1587,   477,  1746,   351,   352,
    1762,   353,   354,   355,   356,   357,   358,   359,  1414,  1692,
    1693,   360,   361,   362,   887,   888,   363,   364,   365,   897,
     898,  1349,  1343,  1647,  1648,   366,  1272,  1618,  1878,   367,
    1306,  1873,  1612,  1875,  1613,  1614,  2060,   368,   369,  1651,
     901,   370,   371,   372,   373,   374,   960,   961,  1718,   414,
    2096,  2174,   925,   926,   927,   928,   929,   930,   931,  1671,
     932,   933,   934,   935,   936,   937,   375,   376,   967,   377,
     378,   972,   379,   380,   968,   969,   381,   382,   383,   980,
     981,  1309,  1310,  1311,   982,   983,  1283,  1284,   384,   385,
     386,   387,   388,   989,   990,   389,   390,   224,   938,   986,
    1026,   939,   391,   228,  1126,   551,   552,   940,   559,   392,
     393,   394,   395,   396,   397,  1028,  1029,  1030,   398,   399,
     400,   877,   878,  1600,  1601,  1325,  1326,  1327,  1588,  1589,
    1638,  1633,  1634,  1639,  1328,  1888,  1048,  1831,   835,  1843,
     837,  1849,   838,   468,   498,  2143,  2042,  2278,  2279,  2025,
    2035,  1262,  1838,   836,   401,  1049,  1050,  1034,  1035,  1036,
    1037,  1329,  1039,   941,   942,   943,  1042,  1043,   402,   849,
     944,   754,   755,   231,   404,   945,   557,  1558,   784,   946,
    1250,   797,  1562,  1820,   234,   947,   716,   949,   717,   950,
     779,   780,  1237,  1238,   781,   951,   952,   405,   406,   953,
     239,   545,   240,   566,   241,   572,   242,   580,   243,   594,
    1146,  1502,   244,   602,   245,   607,   246,   617,   247,   626,
     248,   632,   249,   635,   250,   639,   251,   644,   252,   649,
     253,   683,   684,   685,   254,   686,   255,   699,   256,   694,
     257,   408,   661,  1177,  1594,  1179,  1515,  1507,  1512,  1505,
    1509,   258,   666,  1205,  1544,  1527,  1533,  1522,  1206,   259,
     705,   260,   562,   261,   262,   730,   263,   718,   264,   720,
     265,   722,   266,   727,   267,   737,   268,   740,   269,   746,
     270,   793
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,   422,    54,   883,   227,   785,   850,   421,  1067,  1079,
     299,  1066,  1069,  1154,   884,   881,  1068,   973,   868,  1366,
    1109,  1107,   350,  1424,   695,  1183,    45,   298,  1356,  1330,
    1108,  1038,   229,  1211,   417,  1032,  1085,  1134,  1227,   403,
    1094,  1087,  1051,  1051,   279,   987,   308,  1763,  1763,  1093,
    1774,   403,  1117,   843,   409,   229,  1785,  1772,   798,   412,
    1315,  1786,    58,    59,    60,  1055,  1689,   229,  1397,  1688,
     476,  1572,   476,  1275,   476,   476,  1620,  1065,   476,   297,
     476,  1787,   873,   476,   476,  1625,  1627,   476,   476,   476,
     476,  1073,  1640,  1033,   476,  1796,  1429,   517,  1113,   698,
    1083,  1890,   517,   517,   309,  1784,   310,   948,  1370,  1322,
     476,  1832,  1833,  1409,  1333,   962,   413,   970,  1411,  1795,
     672,   418,  1089,   672,    62,   424,  2008,  1344,  2006,  1844,
    1989,  1348,  2007,  1690,   673,   674,   230,   673,   674,  1227,
    1410,  1214,  1922,  1216,  1415,  1217,  2120,   984,   675,  1992,
    1219,   675,  1102,   875,   303,   304,   305,   306,  2045,   230,
    1918,  1483,  2046,  1812,  1814,   676,   988,  2132,   676,   677,
     678,   230,   677,   678,  1691,   679,   756,  1114,   679,  1821,
     984,  1407,  1408,   680,   681,   271,   680,   681,   682,   428,
    1331,   682,   687,   688,   875,   687,   688,   438,   439,   440,
     441,   689,  1923,   669,   689,   670,   669,   671,   670,  2259,
     671,  1244,   984,  1401,  1289,  1595,  1053,  2311,   229,  -732,
     474,  2015,   229,  1267,  1080,    64,  -727,  -732,  -732,  -732,
    -732,  1869,  1081,  -727,  -727,  -727,  -727,   499,  2049,   277,
    -693,  1855,   508,   509,   510,   311,   300,   225,  1263,  1264,
    -742,   707,   524,  2211,  1273,   531,   157,  -742,  -742,  -742,
    -742,  1226,  1276,  1857,  1858,    56,   848,   848,    56,  1270,
     225,    56,  -727,  2148,  1300,   710,   799,    55,  1763,    56,
    1920,  1239,   225,   801,  2089,  1560,   426,  1130,  1228,   804,
     430,  1621,   869,   226,  2188,  2189,  -742,  1294,  1553,  1554,
     158,   159,   160,    73,    65,   453,   426,  1300,  1949,  1950,
    1585,  -828,  1275,  1586,  1427,  1870,   226,    88,   756,   158,
     159,   160,   230,   480,   985,     4,   230,     5,   226,   633,
    1259,  1257,  1031,   728,  2212,  2213,  2188,  2189,   403,   996,
    1258,  1380,   104,  1031,  1031,   634,   426,   519,     4,  1265,
       5,  1988,   497,  1616,   229,  1605,   151,   534,   729,  -734,
    1712,  1297,  1426,  1988,   540,   422,  -734,  -734,  -734,  -734,
     870,   421,  1252,  -694,  1763,  1763,  1137,  1774,   521,   442,
     523,  -828,   847,   847,  1772,   998,   853,  1381,  1253,  2073,
     448,  1138,  1254,   422,  -743,   963,  1062,  1418,  1082,   421,
    1420,  -743,  -743,  -743,  -743,  -734,   422,   434,   863,  -429,
     738,  1078,   421,   403,   831,   832,   833,  1557,  1635,  1266,
    1813,  1636,     3,   463,   294,     4,   864,     5,   403,   229,
    1584,  1756,  1803,   225,  1654,   739,  1657,   225,  1084,   301,
    -743,   302,   487,   996,   229,    56,   334,     6,     7,     8,
       9,   335,  1131,   476,     4,   422,     5,    57,   230,   997,
      57,   421,  1470,    57,   337,  1853,  1854,  1301,  -253,   338,
    1256,    57,    67,    68,    69,  1517,   272,   273,   274,   226,
    1290,  2280,  1561,   226,  1405,    56,  1467,  1468,  1469,   998,
    2241,  2201,   221,  1472,  2242,   809,   426,  2343,   410,   413,
    2076,  1473,   971,   309,  1481,  1871,  1295,   310,  1471,  1988,
    2210,  2344,   418,  1449,  1855,  1898,  1899,   424,   816,  1919,
    1413,   221,  1596,  1597,  -547,   221,   709,   811,  1672,   221,
     272,   273,   274,   230,   312,   313,   431,   432,   433,  1185,
    1622,  1054,  1797,  1617,  1922,  1798,  2225,  1332,   230,  1070,
    1071,  1072,   349,   460,   461,  1756,  1700,   221,   221,  1924,
    2243,  1702,   473,  1669,   221,  2262,  2260,  2172,   879,   225,
     334,   484,   485,   310,  2312,   335,  1383,   491,  1274,  -732,
     448,  2088,  1088,  1701,  1147,  -727,  2266,  2052,   337,  1152,
    2293,  2214,  2291,   338,   522,  1119,  2292,   221,  2074,   221,
     221,  -429,  2274,   535,   536,  2275,   411,   539,  1492,  -742,
    1494,  1100,   435,   814,  1186,   226,  1025,  2164,  2165,  1805,
    2158,  1455,  2139,  1141,  1698,  1699,  1822,  1025,  1025,  1963,
    1964,  1139,  2166,  1086,  1285,  1546,   672,    57,   672,  2157,
     964,   965,   966,  2090,   225,  1990,  1140,  2069,  2070,  2072,
     673,   674,   673,   674,   713,   714,  1431,   987,  1314,   225,
    1368,  1369,  1027,   455,   675,  1864,   675,  1865,  1866,  2125,
    1868,  1565,  2115,  1027,  1027,  1445,   879,    57,  2137,  1443,
      56,   676,  1210,   676,  2093,   677,   678,   677,   678,  1645,
     226,   679,  1416,   679,  1646,   465,  1655,  1209,  2078,   680,
     681,   680,   681,   514,   682,   226,   682,   232,   687,   688,
     687,   688,  2128,  1883,  1461,  2121,  -272,   689,  -734,   689,
    1384,   669,  1385,   670,  1940,   671,  1756,   538,  1268,  1112,
     232,  1123,  1907,   866,   867,  1908,   715,  1444,  1910,   842,
     851,   334,   232,   812,   813,   422,   335,   964,   965,   966,
     782,   421,  2171,  -743,  1943,  1944,  1945,  1946,   558,   337,
     783,   719,     3,  1430,   338,     4,  -998,     5,  -998,   879,
    2249,   553,   554,   555,  2077,  2250,   721,   852,   787,  1889,
     707,  1269,   802,  1574,   690,  1839,  1579,     6,     7,     8,
       9,   691,   233,  1330,  1577,  2251,     3,  1541,  -999,     4,
    -999,     5,   956,   957,   710,   436,   839,   437,  1312,  1324,
    1643,   494,  1315,  1275,  1542,   233,  1610,   866,   867,  2248,
     692,     6,     7,     8,     9,   840,   640,   233,  1615,  1871,
     641,   841,   235,  1053,  1412,   872,  1351,  1439,  1763,  1763,
     707,  1774,  1261,  1378,  1330,  1379,  1543,   229,  1772,  1352,
    1440,  2026,  1441,   810,   844,   235,     3,   603,  2027,     4,
     709,     5,   642,   643,   710,  1353,  1428,   235,  1271,   489,
     490,   229,    57,   846,  1124,  1125,   707,  1386,   604,  1439,
    1817,     6,     7,     8,     9,  1365,  1862,  1863,   466,   865,
     467,   605,  1451,   232,  1441,  2028,   479,   232,   481,   483,
     710,  1364,   486,  1451,   488,  1441,  2146,   492,   493,   866,
     867,   501,   503,   505,   507,   861,  1398,  1941,   512,  1942,
    1571,   520,  1439,  -998,   560,   561,   527,   530,  2054,  2029,
    1255,  1031,   871,  2245,   537,  1710,   985,  1441,  1856,  1387,
     874,   133,   134,   987,   135,   136,   137,  1098,    75,  1496,
     958,   230,   349,   959,   862,  -999,    76,   221,    77,   158,
     159,   160,   700,    78,    79,    80,  1497,    81,  2103,  2104,
    2105,  1498,  1499,   723,     3,   230,  1031,     4,   233,     5,
     236,   879,   233,  1794,  1792,  -998,  1563,   875,   713,   714,
    1906,   900,   556,  1793,   701,   702,  1118,    90,   229,     6,
       7,     8,     9,   236,   495,    91,   467,    92,   891,    93,
     988,  1432,    94,    95,    96,   236,    97,  -999,   235,  1354,
    2298,  2110,   235,   496,  1433,   993,   221,  1782,   994,   232,
     703,     3,  1432,  2084,     4,  1686,     5,  2141,  2030,  1402,
     995,   987,  2142,  1404,   662,  1709,  1044,  1450,   606,  1056,
     636,  1452,   237,   724,   725,   726,     6,     7,     8,     9,
     637,   638,   225,   704,  1695,  1697,  1045,  1338,  1057,  1696,
     715,  1703,  1697,  1706,  1708,   237,  1705,  1500,  1058,  1599,
     157,  1649,  2145,   157,  1649,     3,   225,   237,     4,   645,
       5,  1650,  2151,  1025,  1653,   794,   795,   663,   664,  2154,
    1339,  1970,   230,  1059,   232,  1060,   665,   880,   226,   879,
       6,     7,     8,     9,   233,  1340,     4,   311,     5,   232,
    2115,   646,   647,  1791,   648,  2031,  1971,  1972,  1493,  -335,
    1495,  -828,  1313,  1135,  2159,  1095,  1501,  1121,  2016,  1027,
     238,  1371,   515,   879,   516,   885,   886,  2227,   627,   892,
     893,   894,   895,   896,   235,   546,   547,    18,    19,  1714,
    1341,  1148,  -837,   407,   628,     4,   236,     5,  2123,  1150,
     236,   157,  1649,   629,  2026,   407,  1122,  2162,  2163,   630,
     631,  2027,  1656,   138,  1153,   991,   992,    82,  -838,   233,
     139,   140,  1285,  1101,  1599,  2221,  2222,  2223,  1663,  1664,
    1129,  -428,    83,   879,   233,  1670,   141,    35,  1025,  1025,
    1025,  1025,  1025,   225,  1127,  1025,  1181,    36,  2028,  1845,
      84,  2239,   985,    37,  1249,    85,  1215,    86,  1180,   235,
     469,   470,   471,   472,  1304,  1305,    98,  1218,   237,   307,
    1399,  1025,   237,     4,   235,     5,  1330,    38,  1241,  1342,
    1973,    99,  2029,  1242,  1027,  1027,  1027,  1027,  1027,   226,
    1025,  1027,  1243,  1860,   978,   979,  1265,  1373,  1374,   100,
    1974,  1975,  1208,  1281,   101,  1251,   102,  1099,  1434,  1435,
    1929,   788,  1893,     3,   320,   321,     4,  1027,     5,   322,
     789,   790,   229,  1287,   791,   792,   548,   549,  1286,  1518,
     550,  1288,   236,  1519,  1520,  1521,  1027,  1223,     6,     7,
       8,     9,  1896,     4,  1673,     5,   143,  2121,   144,  1291,
     985,   879,  1916,   145,  1917,   146,   238,   866,   867,   147,
     238,     3,  1292,   731,     4,  1293,     5,  1827,  1510,  1511,
    1268,  1697,  1697,  1513,  1514,  1925,  1926,  2047,  1308,   732,
    1979,  1980,  1981,  1921,  1982,  2050,     6,     7,     8,     9,
    2048,  2030,   563,   564,   565,  2106,  2107,  2108,  2109,   148,
     733,   149,  2026,  1296,   237,  1298,   734,   236,   879,  2027,
    2336,  2337,  2338,   272,   273,   274,  2062,  1321,  2065,   977,
     978,   979,   236,  -428,  1834,  1334,   230,  1628,  1335,  2068,
    1336,    18,    19,  1549,  1550,   229,  1345,   229,  1551,  1552,
    1314,   806,  1629,   525,   875,  1626,  2028,  1630,  1818,  1819,
     817,   818,   819,   820,  1142,  1143,  1144,  1145,    18,    19,
    1631,  2000,   879,  -547,  1346,  1632,   324,   325,   326,  1886,
    1887,   329,   567,   403,   568,   569,   570,   571,  2135,   237,
    2029,    35,  1713,  1715,  1347,  1731,  1740,  1758,  1770,   229,
    1360,    36,   407,  1367,   237,   735,   736,    37,  1375,  2167,
    2168,     3,  -428,  1376,     4,  1377,     5,  1382,    35,  1716,
    2044,  1732,  1741,  1759,  1771,  2228,   157,  1649,    36,  1966,
    1967,    38,  1802,  1275,    37, -1043,     6,     7,     8,     9,
    1528,  1529,  1530,  1531,  1532,     3, -1044,   225,     4,   230,
       5,   230,   158,   159,   160,  2100,  2102,  1388,    38,  2101,
    2300,  2301,   232,  1810,  1811,  2181,  2182,  2183,  1681,  1682,
       6,     7,     8,     9,  1389,  2326,   741,   407,  1390,  1808,
    1809,  2119,  1393,   823,  1391,   824,   232,   825,   826,  1394,
     742,  1401,   407,   226,  1403,   827,   828,   743,  1880,  2030,
    1312,  1398,  1436,   230,  2018,   850,  1437,  2127,  1438,  1828,
    1442,  1448,  1835,  1324,  1840,   744,  1432,  1846,  1053,   541,
    2099,   745,   542,   543,   544,  1453,   403,  1462,  1463,   829,
    1371,  1371,  1371,  1371,  1371,  1829,  1371,  1371,  1836,  1464,
    1841,  1465,   229,  1847,  2019,  1679,  1679,   233,   158,   159,
     160,  1903,  1466,  1265,  1652,  1652,  1474,  1652,  1268,  1475,
     225,  1476,   225,   229,  1477,  1478,   573,   574,   403,  1479,
     879,  1316,  1480,  1482,  1904,   575,   576,   577,   578,   579,
    1504,  1902,   866,   867,   229,  1508,  2320,   235,  1599,  1025,
    1025,  1025,  1025,  1025,  1025,  1025,  1025,  1025,  1025,  1025,
    1523,  1524,  1525,  1526,  -428,  1516,   226,  1485,   226,  1489,
    1506,  1317,  1535,   232,   225,  1953,   403,  1536,   879,  2055,
    2056,  2057,  2058,  2059,   964,   965,   966,  1537,  1539,  1487,
    1538,  1540,   229,  1547,  2296,  1027,  1027,  1027,  1027,  1027,
    1027,  1027,  1027,  1027,  1027,  1027,   230,  1285,     3,  1548,
    1555,     4,  1556,     5,  1557,  2155,  1559,  1569,  2270,  2268,
     226,  1962,  1564,  1566,   482,  1567,  1568,   230,  2269,  1576,
    1581,   996,  1947,     6,     7,     8,     9,  1598,  1962,    18,
      19,  1956,  1957,  1958,  1959,  1960,  1606,  2020,   230,   229,
    1608,  1611,  1619,  1623,  2282,  2283,  1659,  1644,   233,  1985,
    1986,  1987,  1662,  1668,  2284,  1676,   229,  1677,  1678,  2265,
     403,  1994,  1995,  1996,  -693,  1932,  1934,  1934,  1937,  -694,
    1694,   403,  1731,  1740,  1758,  1770,   229,     3,  1711,    35,
       4,  1788,     5,  1789,  1740,   236,   230,   229,   235,    36,
    1790,  2018,  1799,  1806,  1807,    37,  1815,  1852,  1732,  1741,
    1759,  1771,     6,     7,     8,     9,  1300,   225,   879,   236,
    1741,  1859,  2022,  2032,  2039,   848,   848,  1775,  1872,    38,
    1776,  1874,  1826,  1876,  2021,  2342,  2340,  1885,   225,  1877,
    1891,  2019,  1892,  1025,  1905,  2341,  1894,  1909,  2023,  2033,
    2040,  1895,   879,   230,  1912,  1914,  1927,  1025,  2267,   225,
    1439,   229,  1928,   226,  1939,  1948,  1955,   237,  2297,     3,
     230,  1965,     4,  1969,     5,  1997,   857,  1991,  1285,  1999,
    2335,  1998,  1881,  2012,  1313,  1399,  2011,  2112,  2014,  1027,
     230,   237,  2043,  2281,     6,     7,     8,     9,   422,  2053,
    -565,   230,  2080,  1027,   421,   226,  1053,   225,  1025,  2061,
    2063,  2067,  2075,  1652,  2079,   618,  1652,   619,  2087,  1652,
     229,  2091,  2092,  2095,   422,  2097,  1025,  1025,  2114,  2130,
     421,  2138,  2140,  2147,  2149,  2156,   620,  2112,  2160,  2152,
    2161,   847,   847,  2170,   621,   622,   236,   623,  2173,  1777,
    2176,  2177,  2178,   226,  1027,   238,  2179,   624,   625,  2180,
    2116,  2184,  2117,  2118,   225,   230,  2185,   232,  2186,  2224,
    2194,  2261,  1027,  1027,  2187,  2339,  2122,  2236,  2226,   238,
    2238,   225,  2124,  2144,  2020,  2240,  2244,  2252,  2253,  2126,
    2254,  2264,  2129,  2150,     3,  -287,  2273,     4,  2133,     5,
    2153,   225,  2276,  2310,  2277,  2022,  2032,  2039,  2308,  2309,
     226,  2328,   225,   528,  -288,  2331,  1421,  1423,   237,     6,
       7,     8,     9,  1357,   230,  1247,  1422,   226,    18,    19,
    1246,  2023,  2033,  2040,  1775,  1245,  1136,  1776,   403,  1248,
       3,  1491,  1800,     4,  1425,     5,  1132,   226,   500,  2192,
      72,   808,   233,   807,   229,   879,  1783,  1064,   226,  2198,
    1993,  2299,  1801,    18,    19,     6,     7,     8,     9,  2218,
    2196,  2134,  -428,  2255,  2257,  2256,   225,  1778,    35,  2258,
     232,  2247,   232,  1637,  2329,  1936,   815,  1061,    36,  2195,
    1337,   229,   235,  1350,    37,  2064,  2175,   608,   609,  2202,
    2094,  2066,  2081,  1063,  1392,  2246,   238,  1804,  2285,  1665,
    2193,  1666,   610,    35,   611,   612,   613,   229,    38,  1684,
    1400,  1667,   226,    36,  1882,   502,  1879,   229,  1318,    37,
    2219,  2220,  1687,   845,   232,   225,  1406,   614,   615,   616,
      18,    19,  2229,  2230,  1641,  2231,  2232,  2233,  2234,  2235,
    1779,  1486,  2237,    38,  1707,   786,  1777,  1861,   230,  1897,
    1052,     3,  1900,  1077,     4,   233,     5,   233,  1076,  1074,
    2332,  1075,   855,  1962,   859,  1212,  1184,   860,  1534,     0,
       0,   226,     0,  1178,     0,     0,     6,     7,     8,     9,
      35,     0,     0,     0,     0,   230,     0,     0,  2192,  2263,
      36,   229,     0,     0,     0,   235,    37,   235,  2271,  2272,
    1717,     0,  1734,  1745,  1761,  1773,   879,     0,     0,   233,
       0,   230,     0,     0,     0,     0,     0,     0,     0,     0,
      38,   230,  2286,     0,   403,     0,     0,     0,  2304,  2327,
     236,     0,     0,     0,     0,     0,  1715,  1740,  1758,  1770,
     229,     0,     0,     0,  1828,  1835,  1840,  1846,     0,   235,
       0,  2303,     0,     0,  -428,  2305,   229,  2112,     0,   225,
       0,     0,  1716,  1741,  1759,  1771,     0,   232,     0,  2313,
    1829,  1836,  1841,  1847,  1778,  2314,  2315,  2316,  2317,  2318,
    2022,  2032,  2039,  2322,  2323,  2324,  2325,     3,   232,     0,
       4,     0,     5,  1954,     0,   230,   225,     0,     0,     0,
    1025,  2333,   237,     0,     0,   226,  2023,  2033,  2040,   232,
       0,     0,     6,     7,     8,     9,  1830,  1041,     0,  1837,
       0,  1842,   225,   706,  1848,  2345,  2346,  2347,  1041,  1041,
       0,     0,   225,     0,     0,   707,     0,   708,     0,  1268,
       0,     0,   226,   236,   230,   236,  1027,  2005,     0,     0,
       0,     0,   233,  1040,   504,   709,     0,   232,     0,   710,
     230,     0,   711,     0,  1040,  1040,     0,     0,   226,    18,
      19,     0,     0,  1316,     0,     0,     3,   879,   226,     4,
    2018,     5,     0,     0,  1637,  1229,  1230,     0,     0,     0,
     238,     0,   235,  2295,   233,     0,     0,   236,     0,  1231,
       0,     6,     7,     8,     9,     0,   225,  1232,     0,   595,
       0,   596,     0,  1317,   232,   237,     0,   237,     0,    35,
    2019,     3,     0,  1233,     4,     0,     5,     0,     0,    36,
     597,   232,     0,     0,   235,    37,     0,     0,   598,   599,
     600,   601,   233,  1265,     0,     0,     6,     7,     8,     9,
     712,   232,   226,     3,     0,   225,     4,  1719,     5,    38,
       0,     0,   232,  2082,  2083,     0,  2085,  1720,     0,   237,
       0,   225,  1721,     0,  1722,     0,  1723,     0,     6,     7,
       8,     9,   235,   713,   714,     3,     0,     0,     4,  2036,
       5,     0,     0,  1775,     0,     0,  1776,     0,   879,   233,
       0,   226,     0,   238,     0,   238,     0,     0,     0,     0,
       6,     7,     8,     9,  2294,     0,   233,   226,     0,     0,
       0,     0,     0,     0,     0,  1775,   232,     0,  1776,  1734,
    1745,  1761,  1773,     0,     0,     0,   233,     0,     0,   235,
     236,  1745,     0,     0,     0,     0,     0,   233,     0,     0,
    1234,  1235,  1236,   765,     0,     0,   235,   407,     0,     0,
       0,   236,     0,  2020,     0,   715,   775,   776,   777,  2024,
    2034,  2041,     0,     0,   506,     3,   235,     0,     4,     0,
       5,     3,   236,  1724,     4,   232,     5,   235,     0,    18,
      19,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     7,     8,     9,     0,     0,     6,     7,     8,     9,
     511,   233,   237,     0,  1747,  1777,     3,     0,     0,     4,
       0,     5,     0,     0,     0,    18,    19,     0,     0,     0,
     236,     0,     0,   237,   879,     0,     0,     0,     0,    35,
       0,     6,     7,     8,     9,     0,     0,  1777,     0,    36,
    2319,   235,  2037,     0,   237,    37,  1775,     0,     0,  1776,
       0,     0,     0,  1748,  1749,  1750,  1751,     0,  1752,     0,
     233,  1753,     0,     0,     0,    35,     0,     0,  2197,    38,
       0,     0,     0,     0,  1280,    36,  1282,   236,  1754,     0,
       0,    37,     0,     0,  2036,     0,  1725,     0,     0,     0,
     407,     0,   237,  1299,   236,  1303,     0,  1307,     0,     0,
     235,  1726,     0,  1319,  1320,    38,     0,     0,     0,   232,
       0,   238,     0,   879,   236,     0,     0,     0,     0,  1727,
       0,     0,     0,     0,  1728,   236,  1729,  1755,     0,  2038,
       0,     0,   407,  1778,     0,  1355,     0,     0,  1359,     0,
       0,     0,  2024,  2034,  2041,     0,   232,     0,     0,   237,
       0,     0,     0,     0,     0,     0,     0,     0,   879,     0,
       0,     0,     0,     0,     0,  1778,   237,     0,  1777,     0,
       0,     0,   232,     0,  1730,     0,     0,     0,     0,     0,
     407,     0,   232,     0,  1041,     0,   237,     0,     0,   236,
       0,     0,     0,     0,   233,     0,     0,   237,     0,     0,
       0,     0,     3,  1396,     0,     4,  2010,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2306,  2307,     0,
    1040,     0,     0,     0,     0,     0,     0,     6,     7,     8,
       9,   233,  1372,     0,   235,     0,     0,   238,  2017,     0,
    1756,  1747,     0,     0,     0,     0,     0,  2037,   236,     0,
       0,  2330,     0,     0,   238,   334,   232,   233,     0,  2334,
     335,   237,     0,     0,  2203,     0,     0,   233,     0,     0,
       0,   235,     0,   337,   407,     0,  1446,  1447,   338,     0,
       0,     0,     0,     3,     0,   407,     4,     0,     5,     0,
    1748,  1749,  1750,  1751,     0,  1752,  1778,   235,  1753,  1041,
    1041,  1041,  1041,  1041,     0,   232,  1041,   235,     6,     7,
       8,     9,   879,     0,  2204,  1754,     0,     0,   879,     0,
     237,   232,     0,     0,     0,     0,     0,     0,  1757,     0,
       0,  1970,  1041,     0,  2136,  1040,  1040,  1040,  1040,  1040,
       0,   233,  1040,     0,     0,     0,     0,     0,     0,   238,
       0,  1041,     0,     0,     0,     0,  1971,  1972,     0,     0,
       0,     0,     0,     0,  1755,     0,     0,     0,  1040,  2290,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   235,   236,  1717,  1745,  1761,  1773,  1040,     0,     0,
     233,  1830,  1837,  1842,  1848,     0,  2036,     0,     0,     0,
       0,    10,     0,     0,     0,     0,   233,     0,   238,    11,
       0,    12,     0,    13,     0,     0,    14,    15,    16,   236,
      17,     0,     0,     0,    18,    19,     0,  2024,  2034,  2041,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,   236,   235,     4,     0,     5,
       0,     0,     0,     0,   237,   236,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       7,     8,     9,     0,    35,     0,     0,  1756,     0,     0,
    1973,     0,     0,  1747,    36,     0,     0,     0,     0,     0,
      37,   237,   334,     0,     0,     0,     0,   335,     0,     0,
    1974,  1975,     0,     0,     0,     0,     0,     0,     0,  1580,
     337,     0,     0,  1583,    38,   338,     0,   237,  2205,     0,
       0,     0,     0,  1602,  1603,  1604,     0,   237,  1607,   236,
    1609,     0,  1748,  1749,  1750,  1751,  2206,  1752,     0,     0,
    1753,  2207,   407,  2208,     0,     0,     0,     0,   904,   879,
       0,     0,     0,  1624,   905,     0,   280,  1754,     0,  2037,
       0,     0,     0,     0,   281,  2003,   282,     0,   283,     0,
       0,   284,   285,   286,     0,   287,     0,     0,   236,   238,
       0,     0,   158,   159,   160,     0,     0,     0,     0,  1006,
    1658,     0,  1660,  1007,   236,     0,     0,     0,  1008,  1661,
       0,   237,     0,     0,  1009,   238,  1755,     0,   912,     0,
       0,     0,     0,     0,  1674,   238,  1675,     0,     0,     0,
       0,     0,     0,     0,     0,  1683,     0,  1685,  1012,     0,
     879,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      39,   581,   582,     0,     0,   583,  2321,     0,     0,     0,
     237,     0,     0,     0,     0,    40,   584,   585,   586,   587,
     588,   589,   590,   591,   592,     0,   237,     0,     0,     0,
       0,     0,     0,    41,     3,     0,     0,     4,    42,     5,
      43,  1372,  1372,  1372,  1372,  1372,     0,  1372,  1372,   238,
       0,     0,     0,     0,     0,     0,  1680,  1680,     0,     6,
       7,     8,     9,     0,     0,   593,     0,     0,     0,     0,
    1719,     0,     0,     0,     0,     0,     0,     0,     0,  1756,
    1720,     0,     0,     0,     0,  1721,     0,  1722,     0,  1723,
       0,     0,     0,     0,   334,     0,     0,     0,   407,   335,
    1041,  1041,  1041,  1041,  1041,  1041,  1041,  1041,  1041,  1041,
    1041,     0,   337,     0,   238,     0,     0,   338,     0,     0,
       0,     0,     0,     0,   915,     0,     0,   916,   917,     0,
       0,     0,     0,     0,   918,     0,  1040,  1040,  1040,  1040,
    1040,  1040,  1040,  1040,  1040,  1040,  1040,    51,     0,     0,
       0,   879,     0,     0,     0,   288,     0,    63,    51,    51,
      66,    66,    66,    70,   920,   921,    51,  2288,     0,     0,
     289,     0,     0,  1850,  1851,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   290,     0,
       0,     0,     0,   291,     0,   292,  1724,     0,     0,     0,
    1867,     0,     0,     0,     0,     0,   221,     0,     0,     0,
       0,     0,     0,     0,     0,  1884,     0,     0,     0,    51,
       0,     0,   429,    51,    66,    66,    66,    70,     0,     0,
       0,     0,     0,     0,    51,     0,   444,   449,   452,    51,
     457,    66,    66,   462,     0,   444,   444,   444,   444,     0,
      66,  1911,     0,     0,   478,     0,    51,     0,     0,    66,
      66,     0,    70,     0,     0,    66,     0,     0,  1913,     0,
    1915,     0,     0,     0,     0,     0,     0,     0,     0,    51,
     518,   457,    66,   457,     0,   526,   529,     0,     0,   533,
      51,    66,    66,     3,  1041,    66,     4,    51,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1041,  1725,
       0,     0,     3,     0,     0,     4,     0,     5,     6,     7,
       8,     9,     0,     0,  1726,     0,     0,     0,     0,     0,
    1040,     0,  1764,   747,   650,     0,     0,     6,     7,     8,
       9,     0,  1727,   651,  1040,     0,     0,  1728,     0,  1729,
       0,  1764,     0,     0,  1160,     0,     0,     0,   652,  1041,
     748,     0,   653,   749,     0,     0,   654,   655,     0,  1161,
       0,   656,   657,   658,   659,   660,     0,  1041,  1041,     0,
     750,   879,  1765,     0,  1766,     0,  1752,     0,     0,  1753,
       0,     0,     0,     0,     0,  1040,     0,  2001,     0,     0,
       0,  1765,     0,  1766,     0,  1752,  1767,     0,  1753,     0,
       0,     0,     0,  1040,  1040,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1767,   444,   449,   452,    51,
     457,    66,    66,   462,  1162,   444,   444,   444,   444,     0,
       0,     0,     3,     0,  2051,     4,     0,     5,     0,     0,
       0,     0,     0,     0,     0,  1768,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     7,     8,
       9,     0,     0,     0,  1768,     0,     0,  2071,     0,     0,
       0,  1764,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,     0,  2086,  1163,     0,     0,  1164,  1165,
    1166,  1167,  1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,
    1176,     0,     0,     0,   161,     0,     0,     0,     0,     0,
       0,  1765,     0,  1766,     0,  1752,     0,     0,  1753,     0,
       0,   165,     0,     0,     0,   751,     0,     0,     0,   213,
     214,     0,     0,     0,     0,  1767,     0,   166,     0,   752,
       0,     0,   167,     0,     0,   168,     0,     0,  1756,     0,
     169,     0,     0,   170,     0,     0,   171,   172,     0,     0,
       0,   173,     0,   334,   174,   753,   175,  1756,   335,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   337,   334,     0,  1768,     0,   338,   335,     0,     0,
       0,   176,     0,     0,     0,     0,     0,   181,     0,     0,
     337,     0,     0,     0,     0,   338,     0,     0,  1097,     0,
       0,     0,     0,     0,     0,    66,     0,     0,     0,     0,
     879,     0,     0,     0,     0,     0,  1103,   856,  1104,     0,
    1105,     0,  1106,     0,     0,     0,  1769,  1110,     0,   879,
       3,  1111,    51,     4,     0,     5,     0,     0,     0,   757,
     758,  1115,     0,   759,  1116,  2004,     0,     0,     0,  2169,
       0,     0,   153,     0,    66,     6,     7,     8,     9,   154,
     155,   760,     0,     0,   317,   156,   318,     0,     0,     0,
       0,     0,     0,  1735,     0,     0,     0,     0,     0,     0,
       0,   319,     0,     0,     0,     0,     0,  1756,     0,     0,
       0,   320,   321,     0,     0,     0,   322,     0,     0,   323,
       0,     0,   334,     0,     0,     0,     0,   335,   324,   325,
     326,   327,   328,   329,     0,     0,     0,   857,     0,     0,
     337,     0,     0,  1736,     0,   338,     0,   330,     0,   331,
       0,  1041,   157,   158,   159,   160,     0,     0,   161,     0,
     162,     0,     0,  1737,   163,     0,     0,     0,     0,   164,
       0,     0,     0,     0,     0,   165,     0,     0,     0,   879,
       0,     0,     0,     0,     0,     0,     0,  1040,  1590,     0,
       0,   166,     0,     0,     0,  2289,   167,     0,     0,   168,
     761,     0,     0,     0,   169,     0,     0,   170,     0,     0,
     171,   172,  1738,     0,     0,   173,     0,     0,   174,     0,
     175,     0,     0,     0,   762,   763,   764,   765,   766,   767,
     858,   768,   769,   770,   771,   772,   773,   774,     0,     0,
     775,   776,   777,     0,     0,   176,   177,     0,   178,   179,
     180,   181,     0,  1162,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   778,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   757,   758,     0,     0,   759,
       0,     0,     0,     0,     0,     0,   182,   183,   184,   185,
       0,     0,     0,     0,     0,   186,   187,   760,     0,   188,
     189,   332,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,     0,  1591,   333,     0,  1164,  1165,  1592,
    1167,  1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,  1593,
     334,     0,     0,     0,     0,   335,     0,     0,     0,     0,
       0,     0,   336,     0,     0,     0,     0,     0,   337,     0,
       0,     0,     0,   338,     0,     0,     0,     0,     0,   213,
     214,     0,   339,     0,     0,   340,   341,   342,   343,     0,
       0,     0,   344,     0,     0,     0,   345,   346,   215,     0,
       0,     0,   216,   217,     0,     0,     0,   879,     0,     0,
       0,   347,     0,     3,   218,   219,     4,     0,     5,     0,
     348,     0,   349,  1739,   220,     0,   761,   221,     0,     0,
       0,     0,     0,     0,     0,   153,     0,     0,     6,     7,
       8,     9,   154,   155,     0,     0,     0,   317,   156,   318,
     762,   763,   764,   765,   766,   767,  1735,   768,   769,   770,
     771,   772,   773,   774,   319,     0,   775,   776,   777,     0,
       0,     0,     0,     0,   320,   321,     0,     0,     0,   322,
       0,     0,   323,     0,     0,     0,     0,     0,     0,   778,
       0,   324,   325,   326,   327,   328,   329,     0,     0,     0,
       0,     0,     0,   161,     0,   162,  1736,     0,     0,   163,
     330,     0,   331,     0,   164,   157,   158,   159,   160,     0,
     165,   161,     0,   162,     0,     0,  1737,   163,     0,     0,
       0,     0,   164,     0,     0,     0,   166,     0,   165,     0,
       0,   167,     0,     0,   168,     0,     0,     0,     0,   169,
       0,     0,   170,     0,   166,   171,   172,   667,     0,   167,
     173,     0,   168,   174,     0,   175,     0,   169,     0,     0,
     170,     0,     0,   171,   172,  1738,     0,     0,   173,     0,
       0,   174,     0,   175,     0,     0,     0,     0,     0,     0,
     176,     0,   668,     0,  1187,     0,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   176,   177,
       0,   178,   179,   180,   181,     0,     0,  1188,  1189,  1190,
    1191,  1192,  1193,  1194,  1195,  1196,  1197,  1198,  1199,  1200,
    1201,  1202,  1203,  1204,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1484,     0,   182,
     183,   184,   185,     0,     0,     0,     0,     0,   186,   187,
       0,     0,   188,   189,   332,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,     0,     0,   333,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   334,     0,     0,     0,     0,   335,     0,
       0,     0,     0,     0,     0,   336,     0,     0,     0,     0,
       0,   337,     0,     0,     0,     0,   338,     0,     0,     0,
       0,     0,   213,   214,     0,   339,     0,     0,   340,   341,
     342,   343,     0,     0,     0,   344,     0,     0,     0,   345,
     346,   215,     0,     0,     0,   216,   217,     0,     0,     0,
     879,     0,     0,     0,   347,     0,     3,   218,   219,     4,
       0,     5,     0,   348,     0,   349,  2002,   220,     0,     0,
     221,     0,     0,     0,     0,     0,     0,     0,   153,     0,
       0,     6,     7,     8,     9,   154,   155,     0,     0,     0,
     317,   156,   318,     0,     0,     0,     0,     0,     0,  1735,
       0,     0,     0,     0,     0,     0,     0,   319,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   320,   321,     0,
       0,   854,   322,     0,     0,   323,     0,     0,     0,     0,
       0,     0,     0,     0,   324,   325,   326,   327,   328,   329,
       0,     0,     0,     0,     0,     0,     0,     0,   748,  1736,
       0,   749,     0,   330,     0,   331,     0,     0,   157,   158,
     159,   160,     0,     0,   161,     0,   162,     0,   750,  1737,
     163,     0,     0,     0,     0,   164,     0,     0,     0,     0,
       0,   165,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   166,     0,     0,
       0,     0,   167,     0,     0,   168,     0,     0,     0,     0,
     169,     0,     0,   170,     0,     0,   171,   172,  1738,     0,
       0,   173,     0,     0,   174,     0,   175,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   176,   177,     0,   178,   179,   180,   181,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,     0,   182,   183,   184,   185,     0,     0,     0,     0,
       0,   186,   187,     0,     0,   188,   189,   332,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,     0,
       0,   333,     0,   751,     0,     0,     0,   213,   214,     0,
       0,     0,     0,     0,     0,     0,   334,   752,     0,     0,
       0,   335,     0,     0,     0,     0,     0,     0,   336,     0,
       0,     0,     0,     0,   337,     0,     0,     0,     0,   338,
       0,     0,     0,   753,     0,   213,   214,     0,   339,     0,
       0,   340,   341,   342,   343,     0,     0,     0,   344,     0,
       0,     0,   345,   346,   215,     0,     0,     0,   216,   217,
       0,     0,     0,   879,     0,     0,     0,   347,     0,     3,
     218,   219,     4,     0,     5,     0,   348,     0,   349,  2009,
     220,     0,     0,   221,     0,     0,     0,     0,     0,     0,
       0,   153,     0,     0,     6,     7,     8,     9,   154,   155,
       0,     0,     0,   317,   156,   318,     0,     0,     0,     0,
       0,     0,  1735,     0,     0,     0,     0,     0,     0,     0,
     319,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     320,   321,     0,     0,     0,   322,     0,     0,   323,     0,
       0,     0,     0,     0,     0,     0,     0,   324,   325,   326,
     327,   328,   329,     0,     0,     0,     0,     0,     0,   161,
       0,   162,  1736,     0,   696,   163,   330,     0,   331,     0,
     164,   157,   158,   159,   160,     0,   165,   161,     0,   162,
       0,     0,  1737,   163,     0,     0,     0,     0,   164,     0,
       0,     0,   166,     0,   165,     0,     0,   167,     0,     0,
     168,     0,     0,     0,     0,   169,     0,     0,   170,     0,
     166,   171,   172,     0,     0,   167,   173,     0,   168,   174,
       0,   175,     0,   169,     0,     0,   170,     0,     0,   171,
     172,  1738,     0,     0,   173,     0,     0,   174,     0,   175,
       0,     0,     0,     0,     0,     0,   176,     0,   697,     0,
       0,     0,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,   177,     0,   178,   179,   180,
     181,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,     0,
       0,     0,     0,     0,   186,   187,     0,     0,   188,   189,
     332,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,     0,     0,   333,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   334,
       0,     0,     0,     0,   335,     0,     0,     0,     0,     0,
       0,   336,     0,     0,     0,     0,     0,   337,     0,     0,
       0,     0,   338,     0,     0,     0,     0,     0,   213,   214,
       0,   339,     0,     0,   340,   341,   342,   343,     0,     0,
       0,   344,     0,     0,     0,   345,   346,   215,     4,     0,
       5,   216,   217,     0,     0,     0,   879,     0,     0,     0,
     347,     0,     0,   218,   219,     0,     0,   153,     0,   348,
       0,   349,  2287,   220,   154,   155,   221,     0,     0,   317,
     156,   318,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   319,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   320,   321,     0,     0,
       0,   322,     0,     0,   323,     0,     0,     0,     0,     0,
       0,     0,     0,   324,   325,   326,   327,   328,   329,     0,
       0,     0,     0,     0,     0,   161,     0,   162,     0,     0,
       0,   163,   330,     0,   331,     0,   164,   157,   158,   159,
     160,     0,   165,   161,     0,   162,     0,     0,     0,   163,
       0,     0,     0,     0,   164,     0,     0,     0,   166,     0,
     165,     0,     0,   167,     0,     0,   168,     0,     0,     0,
       0,   169,     0,     0,   170,     0,   166,   171,   172,     0,
       0,   167,   173,     0,   168,   174,     0,   175,     0,   169,
       0,     0,   170,     0,     0,   171,   172,     0,     0,     0,
     173,     0,     0,   174,     0,   175,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,     0,   178,   179,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   183,   184,   185,     0,     0,     0,     0,     0,
     186,   187,     0,     0,   188,   189,   332,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,     0,     0,
     333,     0,     0,     0,   903,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   334,     0,     0,     0,     0,
     335,     0,   153,     0,     0,     0,     0,   336,     0,     0,
     155,     0,     0,   337,     0,   156,     0,     0,   338,     0,
       0,     0,     0,     0,   213,   214,     0,   339,     0,     0,
     340,   341,   342,   343,     0,     0,     0,   344,     0,     0,
       0,   345,   346,   215,     0,     0,     0,   216,   217,   904,
       0,     0,     0,     0,     0,   905,   347,     0,     0,   218,
     219,     0,     0,     0,   906,   348,   907,   349,  1901,   220,
       0,     0,   221,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   157,   158,   159,   160,     0,     0,   161,     0,
     908,     0,     0,     0,   909,     0,     0,     0,     0,   910,
       0,     0,     0,     0,     0,   911,     0,     0,     0,   912,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,     0,     0,     0,     0,   167,     0,     0,   913,
       0,     0,     0,     0,   169,     0,     0,   170,     0,     0,
     171,   172,     0,     0,     0,   173,     0,     0,   174,     0,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   176,   177,     0,   178,   179,
     180,   181,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1277,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     153,     0,     0,     0,     0,     0,   914,     0,   155,     0,
       0,     0,     0,   156,     0,     0,     0,     0,     0,     0,
       0,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,     0,     0,   212,     0,   904,     0,     0,
       0,     0,     0,   905,     0,   915,     0,     0,   916,   917,
       0,     0,     0,     0,     0,   918,     0,     0,     0,     0,
       0,     0,     0,   919,     0,     0,     0,     0,     0,     0,
     157,   158,   159,   160,     0,     0,   161,     0,   908,   213,
     214,     0,   909,     0,     0,   920,   921,   910,     0,     0,
       0,     0,     0,  1278,     0,     0,     0,   912,   215,     0,
       0,     0,   216,   217,     0,     0,     0,     0,     0,   166,
       0,     0,   922,   923,   167,   753,     0,  1279,     0,     0,
       0,     0,   169,     0,   924,   170,     0,   221,   171,   172,
       0,     0,     0,   173,     0,     0,   174,     0,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,     0,   178,   179,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1358,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   153,     0,
       0,     0,     0,     0,   914,     0,   155,     0,     0,     0,
       0,   156,     0,     0,     0,     0,     0,     0,     0,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,     0,     0,   212,     0,   904,     0,     0,     0,     0,
       0,   905,     0,   915,     0,     0,   916,   917,     0,     0,
       0,     0,     0,   918,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,   158,
     159,   160,     0,     0,   161,     0,   908,   213,   214,     0,
     909,     0,     0,   920,   921,   910,     0,     0,     0,     0,
       0,  1278,     0,     0,     0,   912,   215,     0,     0,     0,
     216,   217,     0,     0,     0,     0,     0,   166,     0,     0,
     922,   923,   167,   753,     0,  1279,     0,     0,     0,     0,
     169,     0,   924,   170,     0,   221,   171,   172,     0,     0,
       0,   173,     0,     0,   174,     0,   175,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   176,   177,     0,   178,   179,   180,   181,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1395,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   153,     0,     0,     0,
       0,     0,   914,     0,   155,     0,     0,     0,     0,   156,
       0,     0,     0,     0,     0,     0,     0,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,     0,
       0,   212,     0,   904,     0,     0,     0,     0,     0,   905,
       0,   915,     0,     0,   916,   917,     0,     0,     0,     0,
       0,   918,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,   158,   159,   160,
       0,     0,   161,     0,   908,   213,   214,     0,   909,     0,
       0,   920,   921,   910,     0,     0,     0,     0,     0,  1278,
       0,     0,     0,   912,   215,     0,     0,     0,   216,   217,
       0,     0,     0,     0,     0,   166,     0,     0,   922,   923,
     167,   753,     0,  1279,     0,     0,     0,     0,   169,     0,
     924,   170,     0,   221,   171,   172,     0,     0,     0,   173,
       0,     0,   174,     0,   175,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,     0,   178,   179,   180,   181,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1582,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   153,     0,     0,     0,     0,     0,
     914,     0,   155,     0,     0,     0,     0,   156,     0,     0,
       0,     0,     0,     0,     0,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,     0,     0,   212,
       0,   904,     0,     0,     0,     0,     0,   905,     0,   915,
       0,     0,   916,   917,     0,     0,     0,     0,     0,   918,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   157,   158,   159,   160,     0,     0,
     161,     0,   908,   213,   214,     0,   909,     0,     0,   920,
     921,   910,     0,     0,     0,     0,     0,  1278,     0,     0,
       0,   912,   215,     0,     0,     0,   216,   217,     0,     0,
       0,     0,     0,   166,     0,     0,   922,   923,   167,   753,
       0,  1279,     0,     0,     0,     0,   169,     0,   924,   170,
       0,   221,   171,   172,     0,     0,     0,   173,     0,     0,
     174,     0,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   176,   177,     0,
     178,   179,   180,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   999,  1000,
    1001,  1002,  1003,  1004,     0,     0,     0,     0,  1005,     0,
       0,     0,   984,     0,     0,     0,     0,     0,   914,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,     0,     0,   212,     0,   904,
       0,     0,     0,     0,     0,   905,     0,   915,     0,     0,
     916,   917,     0,     0,     0,     0,     0,   918,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   157,   158,   159,   160,     0,     0,     0,  1323,
    1006,   213,   214,     0,  1007,     0,     0,   920,   921,  1008,
       0,     0,     0,     0,     0,  1009,     0,  1323,     0,   912,
     215,     0,     0,     0,   216,   217,     0,     0,     0,     0,
       0,  1010,     0,     0,   922,   923,  1011,   753,     0,  1012,
       0,     0,     0,     0,  1013,     0,   924,  1014,   904,   221,
    1015,  1016,     0,     0,   905,  1017,     0,     0,  1018,     0,
    1019,     0,     0,     0,     0,     0,   904,     0,     0,     0,
       0,     0,   905,     0,     0,     0,     0,     0,     0,     0,
       0,   157,   158,   159,   160,  1020,     0,     0,  1021,  1006,
       0,  1022,     0,  1007,     0,     0,     0,     0,  1008,   157,
     158,   159,   160,     0,  1009,     0,     0,  1006,   912,     0,
       0,  1007,     0,     0,     0,     0,  1008,     0,     0,     0,
    1010,     0,  1009,     0,     0,  1011,   912,     0,  1012,     0,
       0,     0,     0,  1013,     0,     0,  1014,     0,  1010,  1015,
    1016,     0,     0,  1011,  1017,     0,  1012,  1018,     0,  1019,
       0,  1013,     0,     0,  1014,     0,     0,  1015,  1016,     0,
       0,     0,  1017,     0,     0,  1018,     0,  1019,     0,     0,
       0,     0,     0,     0,  1020,   915,     0,  1021,   916,   917,
    1022,     0,     0,     0,     0,   918,     0,     0,     0,     0,
       0,     0,  1020,     0,     0,  1021,     0,     0,  1022,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   920,   921,     0,  1023,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   922,   923,     0,     0,     0,     0,     0,     0,
       0,     0,   349,     0,  1024,  1046,   984,   221,     0,     0,
       0,     0,     0,     0,   915,     0,     0,   916,   917,     0,
       0,     0,     0,     0,   918,     0,     0,     0,     0,     0,
       0,     0,   915,     0,     0,   916,   917,     0,     0,     0,
       0,     0,   918,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   904,   920,   921,     0,  1023,     0,   905,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   920,   921,     0,  1023,     0,     0,     0,     0,
       0,   922,   923,     0,     0,     0,   157,   158,   159,   160,
       0,   349,     0,  1024,  1006,     0,   221,     0,  1007,   922,
     923,     0,     0,  1008,     0,     0,     0,     0,     0,  1009,
       0,  1024,     0,   912,   221,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1010,     0,     0,     0,     0,
    1011,     0,     0,  1012,     0,     0,     0,     0,  1013,     0,
       0,  1014,     0,     0,  1015,  1016,     0,     0,     0,  1017,
       0,   153,  1018,     0,  1019,     0,     0,     0,   154,   155,
       0,     0,     0,   317,   156,   318,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1020,
     319,     0,  1021,     0,     0,  1022,     0,     0,     0,     0,
     320,   321,     0,     0,     0,   322,     0,     0,   323,     0,
       0,     0,     0,     0,     0,     0,     0,   324,   325,   326,
     327,   328,   329,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   330,     0,   331,     0,
       0,   157,   158,   159,   160,     0,     0,   161,     0,   162,
       0,     0,     0,   163,     0,     0,     0,     0,   164,     0,
       0,     0,     0,     0,   165,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   915,
     166,     0,   916,   917,     0,   167,     0,     0,   168,   918,
       0,     0,     0,   169,     0,     0,   170,     0,     0,   171,
     172,     0,     0,     0,   173,     0,     0,   174,     0,   175,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   920,
     921,     0,  1023,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,   177,     0,   178,   179,   180,
     181,     0,     0,     0,     0,     0,   922,   923,     0,     0,
       0,     0,     0,     0,     0,     0,  1047,     0,  1024,     0,
       0,   221,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,     0,
       0,     0,     0,     0,   186,   187,     0,     0,   188,   189,
     332,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,     0,     0,   333,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   153,     0,   334,
       0,     0,     0,     0,   335,   155,     0,     0,     0,     0,
     156,   336,     0,     0,     0,     0,     0,   337,     0,     0,
       0,     0,   338,     0,     0,     0,     0,     0,   213,   214,
       0,   339,     0,     0,   340,   341,   342,   343,     0,     0,
       0,   344,     0,     0,   904,   345,   346,   215,     0,     0,
     905,   216,   217,     0,     0,     0,     0,     0,     0,     0,
     347,     0,     0,   218,   219,     0,     0,     0,     0,   348,
       0,   349,     0,   220,     0,     0,   221,   157,   158,   159,
     160,     0,     0,   161,     0,   908,     0,     0,     0,   909,
       0,     0,     0,     0,   910,     0,     0,     0,     0,     0,
    1278,     0,     0,     0,   912,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   166,     0,     0,     0,
       0,   167,     0,     0,  1279,     0,     0,     0,     0,   169,
       0,     0,   170,     0,     0,   171,   172,     0,     0,     0,
     173,     0,     0,   174,     0,   175,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,     0,   178,   179,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,     0,     0,     0,     0,
       0,   914,   154,   155,     0,     0,     0,     0,   156,     0,
       0,     0,     0,     0,     0,     0,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,     0,     0,
     212,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     915,     0,     0,   916,   917,     0,     0,     0,     0,     0,
     918,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   158,   159,   160,     0,
       0,   161,     0,   162,   213,   214,     0,   163,     0,     0,
     920,   921,   164,     0,     0,     0,     0,     0,   165,     0,
       0,     0,     0,   215,     0,     0,     0,   216,   217,     0,
       0,     0,     0,     0,   166,     0,     0,   922,   923,   167,
     753,     0,   168,     0,     0,     0,     0,   169,     0,   924,
     170,     0,   221,   171,   172,     0,     0,     0,   173,     0,
       0,   174,     0,   175,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   176,   177,
       0,   178,   179,   180,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   153,     0,     0,     0,
       0,     0,     0,   154,   155,     0,     0,     0,     0,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     183,   184,   185,     0,     0,     0,     0,     0,   186,   187,
       0,     0,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,     0,     0,   212,     0,
    2199,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,   158,   159,   160,
       0,     0,   161,     0,   162,     0,     0,     0,   163,     0,
       0,     0,     0,   164,     0,     0,     0,     0,     0,   165,
       0,     0,   213,   214,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   166,     0,     0,     0,     0,
     167,   215,     0,   168,     0,   216,   217,     0,   169,     0,
       0,   170,     0,     0,   171,   172,     0,   218,   219,   173,
       0,     0,   174,     0,   175,   349,     0,   220,     0,     0,
     221,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,     0,   178,   179,   180,   181,   153,     0,     0,     0,
       0,     0,     0,   154,   155,     0,     0,     0,     0,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     182,   183,   184,   185,     0,     0,     0,     0,     0,   186,
     187,     0,     0,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,     0,     0,   212,
       0,     0,     0,     0,     0,     0,   157,   158,   159,   160,
       0,     0,   161,     0,   162,     0,     0,     0,   163,     0,
       0,     0,     0,   164,     0,     0,     0,     0,     0,   165,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   213,   214,   166,     0,     0,     0,     0,
     167,     0,     0,   168,     0,     0,     0,     0,   169,     0,
       0,   170,   215,     0,   171,   172,   216,   217,     0,   173,
       0,     0,   174,     0,   175,     0,     0,     0,   218,   219,
       0,     0,     0,     0,     0,     0,     0,     0,   220,     0,
       0,   221,     0,     0,     0,     0,     0,     0,     0,   176,
     177,     0,   178,   179,   180,   181,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   984,     0,     0,
     182,   183,   184,   185,     0,     0,     0,     0,     0,   186,
     187,     0,     0,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,     0,     0,   212,
       0,     0,     0,     0,   904,     0,     0,     0,     0,     0,
     905,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,   158,   159,
     160,     0,     0,   213,   214,  1006,     0,     0,     0,  1007,
       0,     0,     0,     0,  1008,     0,     0,     0,     0,     0,
    1009,     0,   215,     0,   912,     0,   216,   217,     0,     0,
       0,     0,     0,     0,     0,     0,  1010,     0,   218,   219,
       0,  1011,     0,     0,  1012,     0,     0,     0,   220,  1013,
       0,   221,  1014,     0,     0,  1015,  1016,     0,     0,     0,
    1017,     0,     0,  1018,     0,  1019,     0,     0,     0,     0,
       0,     0,     2,     3,     0,     0,     4,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1020,     0,     0,  1021,     0,     0,  1022,     0,     6,     7,
       8,     9,     0,     0,     0,     0,     0,     0,     0,    10,
       0,     0,     0,     0,     0,     0,     0,    11,     0,    12,
       0,    13,     0,     0,    14,    15,    16,     0,    17,     0,
       0,     0,    18,    19,    20,     0,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -428,     0,     0,     0,
     915,     0,    35,   916,   917,     0,     0,     0,     0,     0,
     918,     0,    36,   904,     0,     0,     0,     0,    37,   905,
       0,     0,   324,   325,   326,  1886,  1887,   329,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     920,   921,    38,  1023,     0,     0,   157,   158,   159,   160,
       0,     0,     0,     0,  1006,     0,     0,     0,  1007,     0,
       0,     0,     0,  1008,     0,     0,     0,   922,   923,  1009,
       0,     0,     0,   912,     0,     0,     0,   349,     0,  1024,
       0,     0,   221,     0,     0,  1010,     0,     0,     0,     0,
    1011,     0,     0,  1012,     0,     0,     0,     0,  1013,     0,
       0,  1014,     0,     0,  1015,  1016,     0,     0,     0,  1017,
       0,     0,  1018,     0,  1019,     0,     0,     0,     0,   904,
       0,     0,     0,     0,     0,   905,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1020,
       0,     0,  1021,     0,     0,  1022,     0,     0,     0,     0,
       0,     0,   157,   158,   159,   160,     0,     0,     0,     0,
    1006,     0,     0,     0,  1007,     0,     0,     0,    39,  1008,
       0,     0,     0,     0,     0,  1009,     0,     0,     0,   912,
       0,     0,     0,    40,     0,     0,     0,     0,  -428,     0,
       0,  1010,     0,     0,     0,     0,  1011,     0,     0,  1012,
       0,    41,     0,     0,  1013,     0,    42,  1014,    43,     0,
    1015,  1016,     0,     0,     0,  1017,     0,     0,  1018,     0,
    1019,   904,     0,     0,     0,     0,     0,   905,     0,   915,
       0,     0,   916,   917,     0,     0,     0,     0,     0,   918,
       0,     0,     0,     0,     0,  1020,     0,     0,  1021,     0,
       0,  1022,     0,     0,  1704,   158,   159,   160,     0,     0,
       0,     0,  1006,     0,     0,     0,  1007,     0,     0,   920,
     921,  1008,  1023,     0,     0,     0,     0,  1009,     0,     0,
       0,   912,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1010,     0,     0,   922,   923,  1011,     0,
       0,  1012,     0,     0,     0,     0,  1013,     0,  1024,  1014,
       0,   221,  1015,  1016,     0,     0,     0,  1017,     0,     0,
    1018,     0,  1019,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   915,     0,     0,   916,   917,
       0,     0,     0,     0,     0,   918,   106,  1020,     0,     0,
    1021,   107,     0,  1022,   108,   109,   110,   111,     0,     0,
     112,   113,     0,   114,   115,   116,     0,   117,     0,     0,
       0,     0,     0,     0,     0,   920,   921,     0,  1023,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   922,   923,     0,     0,     0,   118,     0,   119,
     120,   121,     0,     0,  1024,     0,     0,   221,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   915,     0,     0,
     916,   917,     0,     0,     0,     0,     0,   918,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   920,   921,     0,
    1023,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   922,   923,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1024,     0,     0,   221,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   122,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     123,     0,     0,     0,     0,     0,     0,   124,   125,   126,
     127,     0,     0,     0,     0,     0,     0,     0,   128,     0,
       0,     0,     0,   129,     0,   130,   131
};

static const yytype_int16 yycheck[] =
{
       1,    68,     3,   356,    30,   216,   328,    68,   432,   443,
      38,   431,   434,   626,   361,   352,   433,   378,   338,   918,
     510,   508,    53,  1017,   179,   682,     1,    37,   904,   876,
     509,   399,    30,   715,    65,   399,   460,   566,   754,    53,
     474,   463,   410,   411,    32,   385,    47,  1458,  1459,   473,
    1459,    65,   531,   317,    55,    53,  1464,  1459,   220,    60,
     869,  1465,     7,     8,     9,   414,  1403,    65,   977,  1402,
     107,  1268,   109,   838,   111,   112,  1311,   430,   115,    36,
     117,  1466,   346,   120,   121,  1324,  1325,   124,   125,   126,
     127,   438,  1331,   399,   131,  1480,  1022,   134,   522,   180,
     453,  1626,   139,   140,    49,  1463,    51,   371,   924,   874,
     147,  1572,  1572,   993,   879,   375,    61,   377,   995,  1477,
     177,    66,   469,   180,    10,    70,  1790,   892,  1788,  1576,
    1764,   896,  1789,  1405,   177,   177,    30,   180,   180,   855,
     994,   718,  1691,   720,   997,   722,  1968,    23,   177,  1767,
     727,   180,   499,     4,    40,    41,    42,    43,  1832,    53,
       5,  1100,  1833,  1555,  1556,   177,    45,  1998,   180,   177,
     177,    65,   180,   180,  1413,   177,   190,   524,   180,  1564,
      23,   991,   992,   177,   177,    58,   180,   180,   177,    75,
       7,   180,   177,   177,     4,   180,   180,    83,    84,    85,
      86,   177,     7,   177,   180,   177,   180,   177,   180,     7,
     180,   788,    23,     7,    97,  1286,    38,     7,   216,     7,
     106,  1814,   220,   835,    57,    12,     8,    15,    16,    17,
      18,    20,    57,    15,    16,    17,    18,   123,  1844,    58,
      22,  1588,   128,   129,   130,    57,    90,    30,   832,   833,
       8,   126,   138,    22,   837,   141,   103,    15,    16,    17,
      18,   751,   838,  1596,  1597,   104,   327,   328,   104,   836,
      53,   104,    54,  2028,   104,   150,   221,   105,  1689,   104,
    1689,   779,    65,   271,     5,   160,    73,   127,   778,   277,
      77,    85,    85,    30,   104,   105,    54,   103,  1237,  1238,
     104,   105,   106,    49,    13,    92,    93,   104,    79,    80,
      90,   293,  1077,    93,  1020,   104,    53,    49,   332,   104,
     105,   106,   216,   110,   385,     4,   220,     6,    65,   144,
     820,   818,   399,   128,   103,   104,   104,   105,   352,     8,
     819,     8,    53,   410,   411,   160,   133,   134,     4,   293,
       6,  1762,   122,   104,   352,  1294,    47,   144,   153,     8,
      39,   859,  1019,  1774,   151,   432,    15,    16,    17,    18,
     163,   432,   806,    22,  1785,  1786,   111,  1786,   135,    88,
     137,   363,   327,   328,  1786,    54,   331,    54,   812,   103,
      91,   126,   814,   460,     8,    85,   427,  1010,    57,   460,
    1013,    15,    16,    17,    18,    54,   473,    81,   292,   104,
     128,   442,   473,   427,   300,   301,   302,   342,    90,   363,
     345,    93,     1,    97,   104,     4,   310,     6,   442,   427,
    1283,   276,  1503,   216,  1352,   153,  1354,   220,    57,   283,
      54,   285,   116,     8,   442,   104,   291,    26,    27,    28,
      29,   296,   292,   490,     4,   522,     6,   296,   352,    24,
     296,   522,  1074,   296,   309,  1585,  1586,   297,   363,   314,
     817,   296,    14,    15,    16,  1181,   349,   350,   351,   216,
     363,  2236,   357,   220,   363,   104,  1070,  1071,  1072,    54,
    2164,  2125,   368,  1076,  2165,   282,   283,  2328,   362,   444,
     297,  1077,    85,   448,  1088,   294,   312,   452,  1075,  1920,
    2128,  2333,   457,   364,  1861,  1635,  1636,   462,   288,   364,
     363,   368,  1287,  1288,   103,   368,   146,   284,  1381,   368,
     349,   350,   351,   427,   346,   347,    78,    79,    80,   694,
     334,   363,  1481,   294,  2093,  1484,  2139,   364,   442,   435,
     436,   437,   363,    95,    96,   276,  1436,   368,   368,   364,
    2166,  1438,   104,  1379,   368,  2199,   364,  2092,   348,   352,
     291,   113,   114,   518,   364,   296,   937,   119,   363,   367,
     281,  1918,   468,  1437,   594,   367,  2204,  1859,   309,   617,
    2254,   360,  2252,   314,   136,   540,  2253,   368,   312,   368,
     368,   296,    22,   145,   146,    25,   362,   149,  1137,   367,
    1139,   497,    90,   287,   695,   352,   399,  2078,  2078,  1545,
    2067,  1055,  2014,   580,  1434,  1435,  1565,   410,   411,  1749,
    1750,   111,  2079,    57,   845,  1212,   693,   296,   695,   104,
     330,   331,   332,   364,   427,  1765,   126,  1882,  1883,  1888,
     693,   693,   695,   695,   274,   275,  1024,   997,   869,   442,
     920,   921,   399,    93,   693,  1604,   695,  1606,  1607,     5,
    1609,  1255,     8,   410,   411,  1043,   348,   296,  2011,  1043,
     104,   693,   710,   695,  1923,   693,   693,   695,   695,   144,
     427,   693,   998,   695,   149,    90,  1353,   707,  1895,   693,
     693,   695,   695,   133,   693,   442,   695,    30,   693,   693,
     695,   695,     5,  1622,  1063,     8,   363,   693,   367,   695,
      85,   695,    87,   695,    90,   695,   276,    45,   310,   516,
      53,   114,  1650,   312,   313,  1653,   356,  1043,  1656,    85,
      62,   291,    65,   285,   286,   812,   296,   330,   331,   332,
     330,   812,  2089,   367,  1726,  1727,  1728,  1729,   133,   309,
     340,   242,     1,  1023,   314,     4,    85,     6,    87,   348,
    2178,    32,    33,    34,  1894,  2179,   242,    99,   341,  1626,
     126,   363,   350,  1270,   127,   364,  1276,    26,    27,    28,
      29,   134,    30,  1640,  1273,  2180,     1,   114,    85,     4,
      87,     6,    38,    39,   150,   283,   103,   285,   869,   876,
    1339,    90,  1621,  1578,   131,    53,  1303,   312,   313,  2177,
     163,    26,    27,    28,    29,   103,   131,    65,  1307,   294,
     135,   103,    30,    38,   996,    85,   142,     7,  2249,  2250,
     126,  2250,   830,    20,  1691,    22,   163,   845,  2250,   155,
      20,    90,    22,   283,   292,    53,     1,   114,    97,     4,
     146,     6,   167,   168,   150,   171,  1021,    65,   363,    45,
      46,   869,   296,   171,   257,   258,   126,   242,   135,     7,
    1562,    26,    27,    28,    29,   913,  1602,  1603,   283,   292,
     285,   148,    20,   216,    22,   134,   109,   220,   111,   112,
     150,   911,   115,    20,   117,    22,  2026,   120,   121,   312,
     313,   124,   125,   126,   127,   292,   977,   283,   131,   285,
    1267,   134,     7,   242,   167,   168,   139,   140,  1867,   168,
     816,   998,    85,  2172,   147,    20,   997,    22,  1595,   304,
     104,    49,    50,  1283,    52,    53,    54,   489,    37,   114,
     186,   845,   363,   189,   315,   242,    45,   368,    47,   104,
     105,   106,   135,    52,    53,    54,   131,    56,  1940,  1941,
    1942,   136,   137,   163,     1,   869,  1043,     4,   216,     6,
      30,   348,   220,  1473,  1471,   304,  1250,     4,   274,   275,
    1647,   324,   253,  1472,   167,   168,   538,    37,   996,    26,
      27,    28,    29,    53,   283,    45,   285,    47,   163,    49,
      45,     7,    52,    53,    54,    65,    56,   304,   216,   325,
    2259,   363,   220,   302,    20,    17,   368,  1461,    18,   352,
     203,     1,     7,  1909,     4,  1396,     6,   166,   277,   984,
     367,  1381,   171,   988,   114,    20,    52,  1048,   305,   363,
     153,  1052,    30,   243,   244,   245,    26,    27,    28,    29,
     163,   164,   845,   236,  1432,  1433,    52,    78,   363,  1433,
     356,  1439,  1440,  1441,  1442,    53,  1440,   242,   363,  1290,
     103,   104,  2021,   103,   104,     1,   869,    65,     4,   135,
       6,   114,  2031,   876,   114,   359,   360,   167,   168,  2038,
     111,   104,   996,   363,   427,   363,   176,   351,   845,   348,
      26,    27,    28,    29,   352,   126,     4,    57,     6,   442,
       8,   167,   168,  1470,   170,   364,   129,   130,  1138,   363,
    1140,   293,   869,   567,  2073,    43,  1146,     7,  1820,   876,
      30,   924,    45,   348,    47,   293,   294,  2141,   128,   304,
     305,   306,   307,   308,   352,   112,   113,    60,    61,   364,
     171,   595,    45,    53,   144,     4,   216,     6,     7,   603,
     220,   103,   104,   153,    90,    65,     8,  2076,  2077,   159,
     160,    97,   114,   291,   618,    15,    16,   276,    45,   427,
     298,   299,  1403,    45,  1405,  2134,  2135,  2136,  1373,  1374,
     104,   104,   291,   348,   442,  1380,   314,   110,   991,   992,
     993,   994,   995,   996,   308,   998,   103,   120,   134,   364,
     309,  2160,  1283,   126,   358,   314,   369,   316,   662,   427,
      99,   100,   101,   102,   312,   313,   276,   369,   216,     0,
     977,  1024,   220,     4,   442,     6,  2093,   150,   341,   260,
     253,   291,   168,   341,   991,   992,   993,   994,   995,   996,
    1043,   998,   103,  1600,   335,   336,   293,    15,    16,   309,
     273,   274,   706,    85,   314,   366,   316,   490,    15,    16,
    1714,   237,  1629,     1,    62,    63,     4,  1024,     6,    67,
     246,   247,  1290,    23,   250,   251,   253,   254,   176,   226,
     257,    23,   352,   230,   231,   232,  1043,   741,    26,    27,
      28,    29,  1632,     4,  1381,     6,    45,     8,    47,    52,
    1381,   348,  1683,    52,  1685,    54,   216,   312,   313,    58,
     220,     1,    52,   116,     4,    52,     6,   364,   193,   194,
     310,  1709,  1710,   191,   192,  1709,  1710,  1834,   103,   132,
      86,    87,    88,  1690,    90,  1845,    26,    27,    28,    29,
    1839,   277,   112,   113,   114,  1943,  1944,  1945,  1946,    98,
     153,   100,    90,    52,   352,    52,   159,   427,   348,    97,
    2319,  2320,  2321,   349,   350,   351,  1873,    85,  1875,   334,
     335,   336,   442,   296,   364,   363,  1290,   276,   103,  1878,
     103,    60,    61,   112,   113,  1403,   103,  1405,   112,   113,
    1621,   280,   291,    45,     4,     5,   134,   296,   112,   113,
     289,   290,   291,   292,   138,   139,   140,   141,    60,    61,
     309,  1778,   348,   103,   103,   314,    79,    80,    81,    82,
      83,    84,   114,  1457,   116,   117,   118,   119,   364,   427,
     168,   110,  1453,  1454,   103,  1456,  1457,  1458,  1459,  1457,
      85,   120,   352,    85,   442,   248,   249,   126,    17,  2082,
    2083,     1,   104,    18,     4,   367,     6,     5,   110,  1454,
    1827,  1456,  1457,  1458,  1459,  2142,   103,   104,   120,    95,
      96,   150,  1502,  2258,   126,     7,    26,    27,    28,    29,
     225,   226,   227,   228,   229,     1,     7,  1290,     4,  1403,
       6,  1405,   104,   105,   106,  1935,  1938,     7,   150,  1936,
      43,    44,   845,  1551,  1552,  2103,  2104,  2105,  1388,  1389,
      26,    27,    28,    29,     7,  2300,   114,   427,   103,  1549,
    1550,  1965,     5,    46,   103,    48,   869,    50,    51,     7,
     128,     7,   442,  1290,   363,    58,    59,   135,  1619,   277,
    1621,  1622,    17,  1457,    94,  1887,    18,  1991,   367,  1570,
       8,   103,  1573,  1640,  1575,   153,     7,  1578,    38,   104,
    1933,   159,   107,   108,   109,   103,  1600,   363,   363,    92,
    1373,  1374,  1375,  1376,  1377,  1570,  1379,  1380,  1573,   363,
    1575,   363,  1600,  1578,   134,  1388,  1389,   845,   104,   105,
     106,  1642,   363,   293,  1351,  1352,   103,  1354,   310,   103,
    1403,   103,  1405,  1621,   363,   103,   112,   113,  1642,   103,
     348,   869,   363,   104,  1644,   121,   122,   123,   124,   125,
      97,  1642,   312,   313,  1642,   195,   364,   845,  1859,  1432,
    1433,  1434,  1435,  1436,  1437,  1438,  1439,  1440,  1441,  1442,
     221,   222,   223,   224,   296,   131,  1403,   103,  1405,   103,
     190,   869,   230,   996,  1457,  1736,  1690,   233,   348,   318,
     319,   320,   321,   322,   330,   331,   332,   233,   235,  1123,
     234,   234,  1690,   103,   364,  1432,  1433,  1434,  1435,  1436,
    1437,  1438,  1439,  1440,  1441,  1442,  1600,  1918,     1,   103,
     103,     4,   103,     6,   342,  2052,   103,   103,  2208,  2206,
    1457,  1747,   363,   363,    45,   363,   363,  1621,  2207,   103,
       5,     8,  1733,    26,    27,    28,    29,   103,  1764,    60,
      61,  1742,  1743,  1744,  1745,  1746,   103,   277,  1642,  1747,
      52,   103,    22,    43,  2241,  2242,     5,   149,   996,  1760,
    1761,  1762,   366,   103,  2243,    85,  1764,     8,    85,  2203,
    1784,  1772,  1773,  1774,    22,  1720,  1721,  1722,  1723,    22,
     366,  1795,  1783,  1784,  1785,  1786,  1784,     1,   103,   110,
       4,   363,     6,   363,  1795,   845,  1690,  1795,   996,   120,
     363,    94,     7,   370,   370,   126,   103,     5,  1783,  1784,
    1785,  1786,    26,    27,    28,    29,   104,  1600,   348,   869,
    1795,   363,  1823,  1824,  1825,  1886,  1887,    41,   311,   150,
      44,   311,   294,    20,   364,  2325,  2323,    43,  1621,   315,
     190,   134,   293,  1626,     7,  2324,   315,    70,  1823,  1824,
    1825,   310,   348,  1747,     5,   165,   103,  1640,  2205,  1642,
       7,  1859,    39,  1600,   104,   362,    99,   845,   364,     1,
    1764,   362,     4,   103,     6,   104,   190,   362,  2089,    99,
    2314,   362,  1619,     7,  1621,  1622,   103,  1948,   103,  1626,
    1784,   869,   103,  2240,    26,    27,    28,    29,  1965,   364,
      20,  1795,  1903,  1640,  1965,  1642,    38,  1690,  1691,   103,
     103,   103,   103,  1650,   103,   114,  1653,   116,    85,  1656,
    1918,   364,     5,   189,  1991,   103,  1709,  1710,   104,   151,
    1991,   103,   362,   103,   103,   293,   135,  1998,   103,   105,
     294,  1886,  1887,   364,   143,   144,   996,   146,   186,   163,
     363,   363,   363,  1690,  1691,   845,   363,   156,   157,   363,
    1961,   363,  1963,  1964,  1747,  1859,   363,  1290,   363,     7,
      41,   104,  1709,  1710,   363,  2322,  1977,   134,   363,   869,
     364,  1764,  1983,  2020,   277,   103,   364,   363,   363,  1990,
     363,     8,  1993,  2030,     1,     8,   103,     4,  1999,     6,
    2037,  1784,   103,     5,   104,  2006,  2007,  2008,   103,   103,
    1747,   362,  1795,    45,     8,   103,  1014,  1016,   996,    26,
      27,    28,    29,   905,  1918,   791,  1015,  1764,    60,    61,
     790,  2006,  2007,  2008,    41,   789,   572,    44,  2052,   792,
       1,  1131,  1489,     4,  1018,     6,   562,  1784,    45,  2110,
      20,   282,  1290,   281,  2052,   348,  1462,   429,  1795,  2123,
    1768,  2259,  1496,    60,    61,    26,    27,    28,    29,  2130,
    2121,   364,   104,  2184,  2186,  2185,  1859,   291,   110,  2187,
    1403,  2176,  1405,  1327,  2302,  1722,   287,   426,   120,  2115,
     887,  2089,  1290,   897,   126,  1874,  2097,   112,   113,  2125,
    1923,  1876,  1905,   428,   960,  2175,   996,  1541,  2246,  1375,
    2111,  1376,   127,   110,   129,   130,   131,  2115,   150,  1394,
     980,  1377,  1859,   120,  1621,    45,  1619,  2125,   870,   126,
    2131,  2132,  1401,   319,  1457,  1918,   989,   152,   153,   154,
      60,    61,  2143,  2144,  1331,  2146,  2147,  2148,  2149,  2150,
     364,  1122,  2153,   150,  1442,   216,   163,  1601,  2052,  1633,
     411,     1,  1638,   441,     4,  1403,     6,  1405,   440,   438,
    2311,   439,   332,  2199,   333,   716,   693,   333,  1190,    -1,
      -1,  1918,    -1,   660,    -1,    -1,    26,    27,    28,    29,
     110,    -1,    -1,    -1,    -1,  2089,    -1,    -1,  2259,  2200,
     120,  2199,    -1,    -1,    -1,  1403,   126,  1405,  2209,  2210,
    1454,    -1,  1456,  1457,  1458,  1459,   348,    -1,    -1,  1457,
      -1,  2115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     150,  2125,   364,    -1,  2248,    -1,    -1,    -1,  2264,  2300,
    1290,    -1,    -1,    -1,    -1,    -1,  2247,  2248,  2249,  2250,
    2248,    -1,    -1,    -1,  2255,  2256,  2257,  2258,    -1,  1457,
      -1,  2262,    -1,    -1,   296,  2266,  2264,  2328,    -1,  2052,
      -1,    -1,  2247,  2248,  2249,  2250,    -1,  1600,    -1,  2280,
    2255,  2256,  2257,  2258,   291,  2286,  2287,  2288,  2289,  2290,
    2291,  2292,  2293,  2294,  2295,  2296,  2297,     1,  1621,    -1,
       4,    -1,     6,  1737,    -1,  2199,  2089,    -1,    -1,    -1,
    2093,  2312,  1290,    -1,    -1,  2052,  2291,  2292,  2293,  1642,
      -1,    -1,    26,    27,    28,    29,  1570,   399,    -1,  1573,
      -1,  1575,  2115,   114,  1578,  2336,  2337,  2338,   410,   411,
      -1,    -1,  2125,    -1,    -1,   126,    -1,   128,    -1,   310,
      -1,    -1,  2089,  1403,  2248,  1405,  2093,   364,    -1,    -1,
      -1,    -1,  1600,   399,    45,   146,    -1,  1690,    -1,   150,
    2264,    -1,   153,    -1,   410,   411,    -1,    -1,  2115,    60,
      61,    -1,    -1,  1621,    -1,    -1,     1,   348,  2125,     4,
      94,     6,    -1,    -1,  1638,   112,   113,    -1,    -1,    -1,
    1290,    -1,  1600,   364,  1642,    -1,    -1,  1457,    -1,   126,
      -1,    26,    27,    28,    29,    -1,  2199,   134,    -1,   114,
      -1,   116,    -1,  1621,  1747,  1403,    -1,  1405,    -1,   110,
     134,     1,    -1,   150,     4,    -1,     6,    -1,    -1,   120,
     135,  1764,    -1,    -1,  1642,   126,    -1,    -1,   143,   144,
     145,   146,  1690,   293,    -1,    -1,    26,    27,    28,    29,
     241,  1784,  2199,     1,    -1,  2248,     4,    37,     6,   150,
      -1,    -1,  1795,  1907,  1908,    -1,  1910,    47,    -1,  1457,
      -1,  2264,    52,    -1,    54,    -1,    56,    -1,    26,    27,
      28,    29,  1690,   274,   275,     1,    -1,    -1,     4,   114,
       6,    -1,    -1,    41,    -1,    -1,    44,    -1,   348,  1747,
      -1,  2248,    -1,  1403,    -1,  1405,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,   364,    -1,  1764,  2264,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,  1859,    -1,    44,  1783,
    1784,  1785,  1786,    -1,    -1,    -1,  1784,    -1,    -1,  1747,
    1600,  1795,    -1,    -1,    -1,    -1,    -1,  1795,    -1,    -1,
     277,   278,   279,   280,    -1,    -1,  1764,  1457,    -1,    -1,
      -1,  1621,    -1,   277,    -1,   356,   293,   294,   295,  1823,
    1824,  1825,    -1,    -1,    45,     1,  1784,    -1,     4,    -1,
       6,     1,  1642,   163,     4,  1918,     6,  1795,    -1,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,    -1,    -1,    26,    27,    28,    29,
      45,  1859,  1600,    -1,    40,   163,     1,    -1,    -1,     4,
      -1,     6,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
    1690,    -1,    -1,  1621,   348,    -1,    -1,    -1,    -1,   110,
      -1,    26,    27,    28,    29,    -1,    -1,   163,    -1,   120,
     364,  1859,   277,    -1,  1642,   126,    41,    -1,    -1,    44,
      -1,    -1,    -1,    89,    90,    91,    92,    -1,    94,    -1,
    1918,    97,    -1,    -1,    -1,   110,    -1,    -1,  2122,   150,
      -1,    -1,    -1,    -1,   842,   120,   844,  1747,   114,    -1,
      -1,   126,    -1,    -1,   114,    -1,   276,    -1,    -1,    -1,
    1600,    -1,  1690,   861,  1764,   863,    -1,   865,    -1,    -1,
    1918,   291,    -1,   871,   872,   150,    -1,    -1,    -1,  2052,
      -1,  1621,    -1,   348,  1784,    -1,    -1,    -1,    -1,   309,
      -1,    -1,    -1,    -1,   314,  1795,   316,   163,    -1,   364,
      -1,    -1,  1642,   291,    -1,   903,    -1,    -1,   906,    -1,
      -1,    -1,  2006,  2007,  2008,    -1,  2089,    -1,    -1,  1747,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   348,    -1,
      -1,    -1,    -1,    -1,    -1,   291,  1764,    -1,   163,    -1,
      -1,    -1,  2115,    -1,   364,    -1,    -1,    -1,    -1,    -1,
    1690,    -1,  2125,    -1,   876,    -1,  1784,    -1,    -1,  1859,
      -1,    -1,    -1,    -1,  2052,    -1,    -1,  1795,    -1,    -1,
      -1,    -1,     1,   971,    -1,     4,   364,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2271,  2272,    -1,
     876,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,  2089,   924,    -1,  2052,    -1,    -1,  1747,   364,    -1,
     276,    40,    -1,    -1,    -1,    -1,    -1,   277,  1918,    -1,
      -1,  2305,    -1,    -1,  1764,   291,  2199,  2115,    -1,  2313,
     296,  1859,    -1,    -1,    37,    -1,    -1,  2125,    -1,    -1,
      -1,  2089,    -1,   309,  1784,    -1,  1044,  1045,   314,    -1,
      -1,    -1,    -1,     1,    -1,  1795,     4,    -1,     6,    -1,
      89,    90,    91,    92,    -1,    94,   291,  2115,    97,   991,
     992,   993,   994,   995,    -1,  2248,   998,  2125,    26,    27,
      28,    29,   348,    -1,    87,   114,    -1,    -1,   348,    -1,
    1918,  2264,    -1,    -1,    -1,    -1,    -1,    -1,   364,    -1,
      -1,   104,  1024,    -1,   364,   991,   992,   993,   994,   995,
      -1,  2199,   998,    -1,    -1,    -1,    -1,    -1,    -1,  1859,
      -1,  1043,    -1,    -1,    -1,    -1,   129,   130,    -1,    -1,
      -1,    -1,    -1,    -1,   163,    -1,    -1,    -1,  1024,   364,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2199,  2052,  2247,  2248,  2249,  2250,  1043,    -1,    -1,
    2248,  2255,  2256,  2257,  2258,    -1,   114,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    -1,  2264,    -1,  1918,    45,
      -1,    47,    -1,    49,    -1,    -1,    52,    53,    54,  2089,
      56,    -1,    -1,    -1,    60,    61,    -1,  2291,  2292,  2293,
    2248,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,  2115,  2264,     4,    -1,     6,
      -1,    -1,    -1,    -1,  2052,  2125,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    -1,   110,    -1,    -1,   276,    -1,    -1,
     253,    -1,    -1,    40,   120,    -1,    -1,    -1,    -1,    -1,
     126,  2089,   291,    -1,    -1,    -1,    -1,   296,    -1,    -1,
     273,   274,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1277,
     309,    -1,    -1,  1281,   150,   314,    -1,  2115,   291,    -1,
      -1,    -1,    -1,  1291,  1292,  1293,    -1,  2125,  1296,  2199,
    1298,    -1,    89,    90,    91,    92,   309,    94,    -1,    -1,
      97,   314,  2052,   316,    -1,    -1,    -1,    -1,    70,   348,
      -1,    -1,    -1,  1321,    76,    -1,    37,   114,    -1,   277,
      -1,    -1,    -1,    -1,    45,   364,    47,    -1,    49,    -1,
      -1,    52,    53,    54,    -1,    56,    -1,    -1,  2248,  2089,
      -1,    -1,   104,   105,   106,    -1,    -1,    -1,    -1,   111,
    1358,    -1,  1360,   115,  2264,    -1,    -1,    -1,   120,  1367,
      -1,  2199,    -1,    -1,   126,  2115,   163,    -1,   130,    -1,
      -1,    -1,    -1,    -1,  1382,  2125,  1384,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1393,    -1,  1395,   150,    -1,
     348,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     276,   112,   113,    -1,    -1,   116,   364,    -1,    -1,    -1,
    2248,    -1,    -1,    -1,    -1,   291,   127,   128,   129,   130,
     131,   132,   133,   134,   135,    -1,  2264,    -1,    -1,    -1,
      -1,    -1,    -1,   309,     1,    -1,    -1,     4,   314,     6,
     316,  1373,  1374,  1375,  1376,  1377,    -1,  1379,  1380,  2199,
      -1,    -1,    -1,    -1,    -1,    -1,  1388,  1389,    -1,    26,
      27,    28,    29,    -1,    -1,   176,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   276,
      47,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,    56,
      -1,    -1,    -1,    -1,   291,    -1,    -1,    -1,  2248,   296,
    1432,  1433,  1434,  1435,  1436,  1437,  1438,  1439,  1440,  1441,
    1442,    -1,   309,    -1,  2264,    -1,    -1,   314,    -1,    -1,
      -1,    -1,    -1,    -1,   286,    -1,    -1,   289,   290,    -1,
      -1,    -1,    -1,    -1,   296,    -1,  1432,  1433,  1434,  1435,
    1436,  1437,  1438,  1439,  1440,  1441,  1442,     1,    -1,    -1,
      -1,   348,    -1,    -1,    -1,   276,    -1,    11,    12,    13,
      14,    15,    16,    17,   326,   327,    20,   364,    -1,    -1,
     291,    -1,    -1,  1581,  1582,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   309,    -1,
      -1,    -1,    -1,   314,    -1,   316,   163,    -1,    -1,    -1,
    1608,    -1,    -1,    -1,    -1,    -1,   368,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1623,    -1,    -1,    -1,    73,
      -1,    -1,    76,    77,    78,    79,    80,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,
      94,    95,    96,    97,    -1,    99,   100,   101,   102,    -1,
     104,  1659,    -1,    -1,   108,    -1,   110,    -1,    -1,   113,
     114,    -1,   116,    -1,    -1,   119,    -1,    -1,  1676,    -1,
    1678,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   133,
     134,   135,   136,   137,    -1,   139,   140,    -1,    -1,   143,
     144,   145,   146,     1,  1626,   149,     4,   151,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1640,   276,
      -1,    -1,     1,    -1,    -1,     4,    -1,     6,    26,    27,
      28,    29,    -1,    -1,   291,    -1,    -1,    -1,    -1,    -1,
    1626,    -1,    40,   104,   135,    -1,    -1,    26,    27,    28,
      29,    -1,   309,   144,  1640,    -1,    -1,   314,    -1,   316,
      -1,    40,    -1,    -1,    23,    -1,    -1,    -1,   159,  1691,
     131,    -1,   163,   134,    -1,    -1,   167,   168,    -1,    38,
      -1,   172,   173,   174,   175,   176,    -1,  1709,  1710,    -1,
     151,   348,    90,    -1,    92,    -1,    94,    -1,    -1,    97,
      -1,    -1,    -1,    -1,    -1,  1691,    -1,   364,    -1,    -1,
      -1,    90,    -1,    92,    -1,    94,   114,    -1,    97,    -1,
      -1,    -1,    -1,  1709,  1710,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   114,   280,   281,   282,   283,
     284,   285,   286,   287,   103,   289,   290,   291,   292,    -1,
      -1,    -1,     1,    -1,  1852,     4,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   163,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,    -1,   163,    -1,    -1,  1885,    -1,    -1,
      -1,    40,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,    -1,  1912,   174,    -1,    -1,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,    -1,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    -1,    92,    -1,    94,    -1,    -1,    97,    -1,
      -1,   126,    -1,    -1,    -1,   316,    -1,    -1,    -1,   320,
     321,    -1,    -1,    -1,    -1,   114,    -1,   142,    -1,   330,
      -1,    -1,   147,    -1,    -1,   150,    -1,    -1,   276,    -1,
     155,    -1,    -1,   158,    -1,    -1,   161,   162,    -1,    -1,
      -1,   166,    -1,   291,   169,   356,   171,   276,   296,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   309,   291,    -1,   163,    -1,   314,   296,    -1,    -1,
      -1,   196,    -1,    -1,    -1,    -1,    -1,   202,    -1,    -1,
     309,    -1,    -1,    -1,    -1,   314,    -1,    -1,   482,    -1,
      -1,    -1,    -1,    -1,    -1,   489,    -1,    -1,    -1,    -1,
     348,    -1,    -1,    -1,    -1,    -1,   500,    90,   502,    -1,
     504,    -1,   506,    -1,    -1,    -1,   364,   511,    -1,   348,
       1,   515,   516,     4,    -1,     6,    -1,    -1,    -1,   112,
     113,   525,    -1,   116,   528,   364,    -1,    -1,    -1,  2087,
      -1,    -1,    23,    -1,   538,    26,    27,    28,    29,    30,
      31,   134,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,   276,    -1,    -1,
      -1,    62,    63,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,   291,    -1,    -1,    -1,    -1,   296,    79,    80,
      81,    82,    83,    84,    -1,    -1,    -1,   190,    -1,    -1,
     309,    -1,    -1,    94,    -1,   314,    -1,    98,    -1,   100,
      -1,  2093,   103,   104,   105,   106,    -1,    -1,   109,    -1,
     111,    -1,    -1,   114,   115,    -1,    -1,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,   348,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2093,    38,    -1,
      -1,   142,    -1,    -1,    -1,   364,   147,    -1,    -1,   150,
     253,    -1,    -1,    -1,   155,    -1,    -1,   158,    -1,    -1,
     161,   162,   163,    -1,    -1,   166,    -1,    -1,   169,    -1,
     171,    -1,    -1,    -1,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,    -1,    -1,
     293,   294,   295,    -1,    -1,   196,   197,    -1,   199,   200,
     201,   202,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   316,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,   113,    -1,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,   237,   238,   239,   240,
      -1,    -1,    -1,    -1,    -1,   246,   247,   134,    -1,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,    -1,   174,   276,    -1,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     291,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,
      -1,    -1,   303,    -1,    -1,    -1,    -1,    -1,   309,    -1,
      -1,    -1,    -1,   314,    -1,    -1,    -1,    -1,    -1,   320,
     321,    -1,   323,    -1,    -1,   326,   327,   328,   329,    -1,
      -1,    -1,   333,    -1,    -1,    -1,   337,   338,   339,    -1,
      -1,    -1,   343,   344,    -1,    -1,    -1,   348,    -1,    -1,
      -1,   352,    -1,     1,   355,   356,     4,    -1,     6,    -1,
     361,    -1,   363,   364,   365,    -1,   253,   368,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    35,    36,    37,
     277,   278,   279,   280,   281,   282,    44,   284,   285,   286,
     287,   288,   289,   290,    52,    -1,   293,   294,   295,    -1,
      -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,   316,
      -1,    79,    80,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    -1,    -1,   109,    -1,   111,    94,    -1,    -1,   115,
      98,    -1,   100,    -1,   120,   103,   104,   105,   106,    -1,
     126,   109,    -1,   111,    -1,    -1,   114,   115,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,   142,    -1,   126,    -1,
      -1,   147,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,
      -1,    -1,   158,    -1,   142,   161,   162,   163,    -1,   147,
     166,    -1,   150,   169,    -1,   171,    -1,   155,    -1,    -1,
     158,    -1,    -1,   161,   162,   163,    -1,    -1,   166,    -1,
      -1,   169,    -1,   171,    -1,    -1,    -1,    -1,    -1,    -1,
     196,    -1,   198,    -1,   181,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,   197,
      -1,   199,   200,   201,   202,    -1,    -1,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1101,    -1,   237,
     238,   239,   240,    -1,    -1,    -1,    -1,    -1,   246,   247,
      -1,    -1,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,    -1,    -1,   276,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,   296,    -1,
      -1,    -1,    -1,    -1,    -1,   303,    -1,    -1,    -1,    -1,
      -1,   309,    -1,    -1,    -1,    -1,   314,    -1,    -1,    -1,
      -1,    -1,   320,   321,    -1,   323,    -1,    -1,   326,   327,
     328,   329,    -1,    -1,    -1,   333,    -1,    -1,    -1,   337,
     338,   339,    -1,    -1,    -1,   343,   344,    -1,    -1,    -1,
     348,    -1,    -1,    -1,   352,    -1,     1,   355,   356,     4,
      -1,     6,    -1,   361,    -1,   363,   364,   365,    -1,    -1,
     368,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,
      -1,   104,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    80,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   131,    94,
      -1,   134,    -1,    98,    -1,   100,    -1,    -1,   103,   104,
     105,   106,    -1,    -1,   109,    -1,   111,    -1,   151,   114,
     115,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,
      -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,
      -1,    -1,   147,    -1,    -1,   150,    -1,    -1,    -1,    -1,
     155,    -1,    -1,   158,    -1,    -1,   161,   162,   163,    -1,
      -1,   166,    -1,    -1,   169,    -1,   171,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   196,   197,    -1,   199,   200,   201,   202,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,    -1,   237,   238,   239,   240,    -1,    -1,    -1,    -1,
      -1,   246,   247,    -1,    -1,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    -1,
      -1,   276,    -1,   316,    -1,    -1,    -1,   320,   321,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   291,   330,    -1,    -1,
      -1,   296,    -1,    -1,    -1,    -1,    -1,    -1,   303,    -1,
      -1,    -1,    -1,    -1,   309,    -1,    -1,    -1,    -1,   314,
      -1,    -1,    -1,   356,    -1,   320,   321,    -1,   323,    -1,
      -1,   326,   327,   328,   329,    -1,    -1,    -1,   333,    -1,
      -1,    -1,   337,   338,   339,    -1,    -1,    -1,   343,   344,
      -1,    -1,    -1,   348,    -1,    -1,    -1,   352,    -1,     1,
     355,   356,     4,    -1,     6,    -1,   361,    -1,   363,   364,
     365,    -1,    -1,   368,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    -1,    -1,    -1,    67,    -1,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,   109,
      -1,   111,    94,    -1,   114,   115,    98,    -1,   100,    -1,
     120,   103,   104,   105,   106,    -1,   126,   109,    -1,   111,
      -1,    -1,   114,   115,    -1,    -1,    -1,    -1,   120,    -1,
      -1,    -1,   142,    -1,   126,    -1,    -1,   147,    -1,    -1,
     150,    -1,    -1,    -1,    -1,   155,    -1,    -1,   158,    -1,
     142,   161,   162,    -1,    -1,   147,   166,    -1,   150,   169,
      -1,   171,    -1,   155,    -1,    -1,   158,    -1,    -1,   161,
     162,   163,    -1,    -1,   166,    -1,    -1,   169,    -1,   171,
      -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,   198,    -1,
      -1,    -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   196,   197,    -1,   199,   200,   201,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   237,   238,   239,   240,    -1,
      -1,    -1,    -1,    -1,   246,   247,    -1,    -1,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,    -1,    -1,   276,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   291,
      -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,    -1,
      -1,   303,    -1,    -1,    -1,    -1,    -1,   309,    -1,    -1,
      -1,    -1,   314,    -1,    -1,    -1,    -1,    -1,   320,   321,
      -1,   323,    -1,    -1,   326,   327,   328,   329,    -1,    -1,
      -1,   333,    -1,    -1,    -1,   337,   338,   339,     4,    -1,
       6,   343,   344,    -1,    -1,    -1,   348,    -1,    -1,    -1,
     352,    -1,    -1,   355,   356,    -1,    -1,    23,    -1,   361,
      -1,   363,   364,   365,    30,    31,   368,    -1,    -1,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,   109,    -1,   111,    -1,    -1,
      -1,   115,    98,    -1,   100,    -1,   120,   103,   104,   105,
     106,    -1,   126,   109,    -1,   111,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,   142,    -1,
     126,    -1,    -1,   147,    -1,    -1,   150,    -1,    -1,    -1,
      -1,   155,    -1,    -1,   158,    -1,   142,   161,   162,    -1,
      -1,   147,   166,    -1,   150,   169,    -1,   171,    -1,   155,
      -1,    -1,   158,    -1,    -1,   161,   162,    -1,    -1,    -1,
     166,    -1,    -1,   169,    -1,   171,    -1,    -1,    -1,    -1,
      -1,    -1,   196,    -1,    -1,    -1,    -1,    -1,   202,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     196,   197,    -1,   199,   200,   201,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   237,   238,   239,   240,    -1,    -1,    -1,    -1,    -1,
     246,   247,    -1,    -1,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,    -1,    -1,
     276,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,
     296,    -1,    23,    -1,    -1,    -1,    -1,   303,    -1,    -1,
      31,    -1,    -1,   309,    -1,    36,    -1,    -1,   314,    -1,
      -1,    -1,    -1,    -1,   320,   321,    -1,   323,    -1,    -1,
     326,   327,   328,   329,    -1,    -1,    -1,   333,    -1,    -1,
      -1,   337,   338,   339,    -1,    -1,    -1,   343,   344,    70,
      -1,    -1,    -1,    -1,    -1,    76,   352,    -1,    -1,   355,
     356,    -1,    -1,    -1,    85,   361,    87,   363,   364,   365,
      -1,    -1,   368,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   104,   105,   106,    -1,    -1,   109,    -1,
     111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,   130,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,    -1,    -1,    -1,    -1,   147,    -1,    -1,   150,
      -1,    -1,    -1,    -1,   155,    -1,    -1,   158,    -1,    -1,
     161,   162,    -1,    -1,    -1,   166,    -1,    -1,   169,    -1,
     171,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,   197,    -1,   199,   200,
     201,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,   237,    -1,    31,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,    -1,    -1,   276,    -1,    70,    -1,    -1,
      -1,    -1,    -1,    76,    -1,   286,    -1,    -1,   289,   290,
      -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   304,    -1,    -1,    -1,    -1,    -1,    -1,
     103,   104,   105,   106,    -1,    -1,   109,    -1,   111,   320,
     321,    -1,   115,    -1,    -1,   326,   327,   120,    -1,    -1,
      -1,    -1,    -1,   126,    -1,    -1,    -1,   130,   339,    -1,
      -1,    -1,   343,   344,    -1,    -1,    -1,    -1,    -1,   142,
      -1,    -1,   353,   354,   147,   356,    -1,   150,    -1,    -1,
      -1,    -1,   155,    -1,   365,   158,    -1,   368,   161,   162,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,   171,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   196,   197,    -1,   199,   200,   201,   202,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,   237,    -1,    31,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,    -1,    -1,   276,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    76,    -1,   286,    -1,    -1,   289,   290,    -1,    -1,
      -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,    -1,    -1,   109,    -1,   111,   320,   321,    -1,
     115,    -1,    -1,   326,   327,   120,    -1,    -1,    -1,    -1,
      -1,   126,    -1,    -1,    -1,   130,   339,    -1,    -1,    -1,
     343,   344,    -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,
     353,   354,   147,   356,    -1,   150,    -1,    -1,    -1,    -1,
     155,    -1,   365,   158,    -1,   368,   161,   162,    -1,    -1,
      -1,   166,    -1,    -1,   169,    -1,   171,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   196,   197,    -1,   199,   200,   201,   202,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,   237,    -1,    31,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    -1,
      -1,   276,    -1,    70,    -1,    -1,    -1,    -1,    -1,    76,
      -1,   286,    -1,    -1,   289,   290,    -1,    -1,    -1,    -1,
      -1,   296,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,
      -1,    -1,   109,    -1,   111,   320,   321,    -1,   115,    -1,
      -1,   326,   327,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,   130,   339,    -1,    -1,    -1,   343,   344,
      -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,   353,   354,
     147,   356,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,
     365,   158,    -1,   368,   161,   162,    -1,    -1,    -1,   166,
      -1,    -1,   169,    -1,   171,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,
     197,    -1,   199,   200,   201,   202,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
     237,    -1,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,    -1,    -1,   276,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,   286,
      -1,    -1,   289,   290,    -1,    -1,    -1,    -1,    -1,   296,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   103,   104,   105,   106,    -1,    -1,
     109,    -1,   111,   320,   321,    -1,   115,    -1,    -1,   326,
     327,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,
      -1,   130,   339,    -1,    -1,    -1,   343,   344,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    -1,   353,   354,   147,   356,
      -1,   150,    -1,    -1,    -1,    -1,   155,    -1,   365,   158,
      -1,   368,   161,   162,    -1,    -1,    -1,   166,    -1,    -1,
     169,    -1,   171,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,   197,    -1,
     199,   200,   201,   202,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,   237,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,    -1,    -1,   276,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    76,    -1,   286,    -1,    -1,
     289,   290,    -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   104,   105,   106,    -1,    -1,    -1,    21,
     111,   320,   321,    -1,   115,    -1,    -1,   326,   327,   120,
      -1,    -1,    -1,    -1,    -1,   126,    -1,    21,    -1,   130,
     339,    -1,    -1,    -1,   343,   344,    -1,    -1,    -1,    -1,
      -1,   142,    -1,    -1,   353,   354,   147,   356,    -1,   150,
      -1,    -1,    -1,    -1,   155,    -1,   365,   158,    70,   368,
     161,   162,    -1,    -1,    76,   166,    -1,    -1,   169,    -1,
     171,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   196,    -1,    -1,   199,   111,
      -1,   202,    -1,   115,    -1,    -1,    -1,    -1,   120,   103,
     104,   105,   106,    -1,   126,    -1,    -1,   111,   130,    -1,
      -1,   115,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,
     142,    -1,   126,    -1,    -1,   147,   130,    -1,   150,    -1,
      -1,    -1,    -1,   155,    -1,    -1,   158,    -1,   142,   161,
     162,    -1,    -1,   147,   166,    -1,   150,   169,    -1,   171,
      -1,   155,    -1,    -1,   158,    -1,    -1,   161,   162,    -1,
      -1,    -1,   166,    -1,    -1,   169,    -1,   171,    -1,    -1,
      -1,    -1,    -1,    -1,   196,   286,    -1,   199,   289,   290,
     202,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,
      -1,    -1,   196,    -1,    -1,   199,    -1,    -1,   202,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   326,   327,    -1,   329,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   353,   354,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   363,    -1,   365,    22,    23,   368,    -1,    -1,
      -1,    -1,    -1,    -1,   286,    -1,    -1,   289,   290,    -1,
      -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   286,    -1,    -1,   289,   290,    -1,    -1,    -1,
      -1,    -1,   296,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,   326,   327,    -1,   329,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   326,   327,    -1,   329,    -1,    -1,    -1,    -1,
      -1,   353,   354,    -1,    -1,    -1,   103,   104,   105,   106,
      -1,   363,    -1,   365,   111,    -1,   368,    -1,   115,   353,
     354,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,   365,    -1,   130,   368,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,
     147,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,
      -1,   158,    -1,    -1,   161,   162,    -1,    -1,    -1,   166,
      -1,    23,   169,    -1,   171,    -1,    -1,    -1,    30,    31,
      -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,
      52,    -1,   199,    -1,    -1,   202,    -1,    -1,    -1,    -1,
      62,    63,    -1,    -1,    -1,    67,    -1,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,
      -1,   103,   104,   105,   106,    -1,    -1,   109,    -1,   111,
      -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,   120,    -1,
      -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   286,
     142,    -1,   289,   290,    -1,   147,    -1,    -1,   150,   296,
      -1,    -1,    -1,   155,    -1,    -1,   158,    -1,    -1,   161,
     162,    -1,    -1,    -1,   166,    -1,    -1,   169,    -1,   171,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   326,
     327,    -1,   329,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   196,   197,    -1,   199,   200,   201,
     202,    -1,    -1,    -1,    -1,    -1,   353,   354,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   363,    -1,   365,    -1,
      -1,   368,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   237,   238,   239,   240,    -1,
      -1,    -1,    -1,    -1,   246,   247,    -1,    -1,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,    -1,    -1,   276,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,   291,
      -1,    -1,    -1,    -1,   296,    31,    -1,    -1,    -1,    -1,
      36,   303,    -1,    -1,    -1,    -1,    -1,   309,    -1,    -1,
      -1,    -1,   314,    -1,    -1,    -1,    -1,    -1,   320,   321,
      -1,   323,    -1,    -1,   326,   327,   328,   329,    -1,    -1,
      -1,   333,    -1,    -1,    70,   337,   338,   339,    -1,    -1,
      76,   343,   344,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     352,    -1,    -1,   355,   356,    -1,    -1,    -1,    -1,   361,
      -1,   363,    -1,   365,    -1,    -1,   368,   103,   104,   105,
     106,    -1,    -1,   109,    -1,   111,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,
     126,    -1,    -1,    -1,   130,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,    -1,
      -1,   147,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,
      -1,    -1,   158,    -1,    -1,   161,   162,    -1,    -1,    -1,
     166,    -1,    -1,   169,    -1,   171,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     196,   197,    -1,   199,   200,   201,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,   237,    30,    31,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,    -1,    -1,
     276,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     286,    -1,    -1,   289,   290,    -1,    -1,    -1,    -1,    -1,
     296,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,    -1,
      -1,   109,    -1,   111,   320,   321,    -1,   115,    -1,    -1,
     326,   327,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,
      -1,    -1,    -1,   339,    -1,    -1,    -1,   343,   344,    -1,
      -1,    -1,    -1,    -1,   142,    -1,    -1,   353,   354,   147,
     356,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,   365,
     158,    -1,   368,   161,   162,    -1,    -1,    -1,   166,    -1,
      -1,   169,    -1,   171,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,   197,
      -1,   199,   200,   201,   202,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   237,
     238,   239,   240,    -1,    -1,    -1,    -1,    -1,   246,   247,
      -1,    -1,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,    -1,    -1,   276,    -1,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,
      -1,    -1,   109,    -1,   111,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,   320,   321,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,
     147,   339,    -1,   150,    -1,   343,   344,    -1,   155,    -1,
      -1,   158,    -1,    -1,   161,   162,    -1,   355,   356,   166,
      -1,    -1,   169,    -1,   171,   363,    -1,   365,    -1,    -1,
     368,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,
     197,    -1,   199,   200,   201,   202,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     237,   238,   239,   240,    -1,    -1,    -1,    -1,    -1,   246,
     247,    -1,    -1,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,    -1,    -1,   276,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,
      -1,    -1,   109,    -1,   111,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   320,   321,   142,    -1,    -1,    -1,    -1,
     147,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,
      -1,   158,   339,    -1,   161,   162,   343,   344,    -1,   166,
      -1,    -1,   169,    -1,   171,    -1,    -1,    -1,   355,   356,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,
      -1,   368,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,
     197,    -1,   199,   200,   201,   202,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,
     237,   238,   239,   240,    -1,    -1,    -1,    -1,    -1,   246,
     247,    -1,    -1,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,    -1,    -1,   276,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,
     106,    -1,    -1,   320,   321,   111,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,
     126,    -1,   339,    -1,   130,    -1,   343,   344,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,   355,   356,
      -1,   147,    -1,    -1,   150,    -1,    -1,    -1,   365,   155,
      -1,   368,   158,    -1,    -1,   161,   162,    -1,    -1,    -1,
     166,    -1,    -1,   169,    -1,   171,    -1,    -1,    -1,    -1,
      -1,    -1,     0,     1,    -1,    -1,     4,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     196,    -1,    -1,   199,    -1,    -1,   202,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,
      -1,    49,    -1,    -1,    52,    53,    54,    -1,    56,    -1,
      -1,    -1,    60,    61,    62,    -1,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,
     286,    -1,   110,   289,   290,    -1,    -1,    -1,    -1,    -1,
     296,    -1,   120,    70,    -1,    -1,    -1,    -1,   126,    76,
      -1,    -1,    79,    80,    81,    82,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     326,   327,   150,   329,    -1,    -1,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,   353,   354,   126,
      -1,    -1,    -1,   130,    -1,    -1,    -1,   363,    -1,   365,
      -1,    -1,   368,    -1,    -1,   142,    -1,    -1,    -1,    -1,
     147,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,
      -1,   158,    -1,    -1,   161,   162,    -1,    -1,    -1,   166,
      -1,    -1,   169,    -1,   171,    -1,    -1,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,
      -1,    -1,   199,    -1,    -1,   202,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   104,   105,   106,    -1,    -1,    -1,    -1,
     111,    -1,    -1,    -1,   115,    -1,    -1,    -1,   276,   120,
      -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,   130,
      -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,   296,    -1,
      -1,   142,    -1,    -1,    -1,    -1,   147,    -1,    -1,   150,
      -1,   309,    -1,    -1,   155,    -1,   314,   158,   316,    -1,
     161,   162,    -1,    -1,    -1,   166,    -1,    -1,   169,    -1,
     171,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,   286,
      -1,    -1,   289,   290,    -1,    -1,    -1,    -1,    -1,   296,
      -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,   199,    -1,
      -1,   202,    -1,    -1,   103,   104,   105,   106,    -1,    -1,
      -1,    -1,   111,    -1,    -1,    -1,   115,    -1,    -1,   326,
     327,   120,   329,    -1,    -1,    -1,    -1,   126,    -1,    -1,
      -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    -1,   353,   354,   147,    -1,
      -1,   150,    -1,    -1,    -1,    -1,   155,    -1,   365,   158,
      -1,   368,   161,   162,    -1,    -1,    -1,   166,    -1,    -1,
     169,    -1,   171,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   286,    -1,    -1,   289,   290,
      -1,    -1,    -1,    -1,    -1,   296,    37,   196,    -1,    -1,
     199,    42,    -1,   202,    45,    46,    47,    48,    -1,    -1,
      51,    52,    -1,    54,    55,    56,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   326,   327,    -1,   329,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   353,   354,    -1,    -1,    -1,    98,    -1,   100,
     101,   102,    -1,    -1,   365,    -1,    -1,   368,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   286,    -1,    -1,
     289,   290,    -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   326,   327,    -1,
     329,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   353,   354,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,    -1,   368,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   276,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     291,    -1,    -1,    -1,    -1,    -1,    -1,   298,   299,   300,
     301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   309,    -1,
      -1,    -1,    -1,   314,    -1,   316,   317
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
     316,   317,   443,    49,    50,    52,    53,    54,   291,   298,
     299,   314,   446,    45,    47,    52,    54,    58,    98,   100,
     447,    47,   448,    23,    30,    31,    36,   103,   104,   105,
     106,   109,   111,   115,   120,   126,   142,   147,   150,   155,
     158,   161,   162,   166,   169,   171,   196,   197,   199,   200,
     201,   202,   237,   238,   239,   240,   246,   247,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   276,   320,   321,   339,   343,   344,   355,   356,
     365,   368,   456,   503,   628,   629,   632,   633,   634,   638,
     701,   704,   706,   710,   715,   716,   718,   720,   730,   731,
     733,   735,   737,   739,   743,   745,   747,   749,   751,   753,
     755,   757,   759,   761,   765,   767,   769,   771,   782,   790,
     792,   794,   795,   797,   799,   801,   803,   805,   807,   809,
     811,    58,   349,   350,   351,   449,   455,    58,   450,   455,
      37,    45,    47,    49,    52,    53,    54,    56,   276,   291,
     309,   314,   316,   441,   104,   451,   452,   376,   395,   396,
      90,   283,   285,   518,   518,   518,   518,     0,   373,   502,
     502,    57,   346,   347,   521,   522,   523,    35,    37,    52,
      62,    63,    67,    70,    79,    80,    81,    82,    83,    84,
      98,   100,   252,   276,   291,   296,   303,   309,   314,   323,
     326,   327,   328,   329,   333,   337,   338,   352,   361,   363,
     528,   529,   530,   532,   533,   534,   535,   536,   537,   538,
     542,   543,   544,   547,   548,   549,   556,   560,   568,   569,
     572,   573,   574,   575,   576,   597,   598,   600,   601,   603,
     604,   607,   608,   609,   619,   620,   621,   622,   623,   626,
     627,   633,   640,   641,   642,   643,   644,   645,   649,   650,
     651,   685,   699,   704,   705,   728,   729,   730,   772,   373,
     362,   362,   373,   502,   580,   457,   460,   528,   502,   465,
     467,   628,   651,   470,   502,   475,   509,   525,   518,   507,
     509,   512,   512,   512,   515,    90,   283,   285,   518,   518,
     518,   518,   524,   439,   507,   518,   519,   436,   505,   507,
     508,   437,   507,   509,   510,   525,   438,   507,   512,   513,
     512,   512,   507,   515,   516,    90,   283,   285,   674,   439,
     439,   439,   439,   512,   518,   445,   506,   527,   507,   527,
     509,   527,    45,   527,   512,   512,   527,   515,   527,    45,
      46,   512,   527,   527,    90,   283,   302,   674,   675,   518,
      45,   527,    45,   527,    45,   527,    45,   527,   518,   518,
     518,    45,   527,   402,   525,    45,    47,   506,   507,   509,
     527,   438,   512,   438,   518,    45,   507,   527,    45,   507,
     527,   518,   414,   507,   509,   512,   512,   527,    45,   512,
     509,   104,   107,   108,   109,   732,   112,   113,   253,   254,
     257,   636,   637,    32,    33,    34,   253,   707,   133,   639,
     167,   168,   793,   112,   113,   114,   734,   114,   116,   117,
     118,   119,   736,   112,   113,   121,   122,   123,   124,   125,
     738,   112,   113,   116,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   176,   740,   114,   116,   135,   143,   144,
     145,   146,   744,   114,   135,   148,   305,   746,   112,   113,
     127,   129,   130,   131,   152,   153,   154,   748,   114,   116,
     135,   143,   144,   146,   156,   157,   750,   128,   144,   153,
     159,   160,   752,   144,   160,   754,   153,   163,   164,   756,
     131,   135,   167,   168,   758,   135,   167,   168,   170,   760,
     135,   144,   159,   163,   167,   168,   172,   173,   174,   175,
     176,   773,   114,   167,   168,   176,   783,   163,   198,   733,
     735,   737,   739,   743,   745,   747,   749,   751,   753,   755,
     757,   759,   761,   762,   763,   764,   766,   782,   790,   792,
     127,   134,   163,   392,   770,   392,   114,   198,   764,   768,
     135,   167,   168,   203,   236,   791,   114,   126,   128,   146,
     150,   153,   241,   274,   275,   356,   717,   719,   798,   242,
     800,   242,   802,   163,   243,   244,   245,   804,   128,   153,
     796,   116,   132,   153,   159,   248,   249,   806,   128,   153,
     808,   114,   128,   135,   153,   159,   810,   104,   131,   134,
     151,   316,   330,   356,   702,   703,   704,   112,   113,   116,
     134,   253,   277,   278,   279,   280,   281,   282,   284,   285,
     286,   287,   288,   289,   290,   293,   294,   295,   316,   721,
     722,   725,   330,   340,   709,   645,   650,   341,   237,   246,
     247,   250,   251,   812,   359,   360,   401,   712,   644,   502,
     420,   455,   350,   400,   455,   388,   439,   436,   437,   509,
     525,   438,   512,   512,   515,   516,   674,   439,   439,   439,
     439,   383,   406,    46,    48,    50,    51,    58,    59,    92,
     453,   518,   518,   518,   380,   669,   684,   671,   673,   103,
     103,   103,    85,   717,   292,   620,   171,   502,   628,   700,
     700,    62,    99,   502,   104,   702,    90,   190,   283,   721,
     722,   292,   315,   292,   310,   292,   312,   313,   557,    85,
     163,    85,    85,   717,   104,     4,   374,   652,   653,   348,
     526,   533,   428,   460,   380,   293,   294,   545,   546,   381,
     426,   163,   304,   305,   306,   307,   308,   550,   551,   413,
     324,   571,   407,     5,    70,    76,    85,    87,   111,   115,
     120,   126,   130,   150,   237,   286,   289,   290,   296,   304,
     326,   327,   353,   354,   365,   583,   584,   585,   586,   587,
     588,   589,   591,   592,   593,   594,   595,   596,   629,   632,
     638,   694,   695,   696,   701,   706,   710,   716,   717,   718,
     720,   726,   727,   730,   421,   427,    38,    39,   186,   189,
     577,   578,   407,    85,   330,   331,   332,   599,   605,   606,
     407,    85,   602,   605,   385,   391,   412,   334,   335,   336,
     610,   611,   615,   616,    23,   628,   630,   631,    45,   624,
     625,    15,    16,    17,    18,   367,     8,    24,    54,     9,
      10,    11,    12,    13,    14,    19,   111,   115,   120,   126,
     142,   147,   150,   155,   158,   161,   162,   166,   169,   171,
     196,   199,   202,   329,   365,   629,   631,   632,   646,   647,
     648,   651,   686,   687,   688,   689,   690,   691,   692,   693,
     695,   696,   697,   698,    52,    52,    22,   363,   667,   686,
     687,   692,   667,    38,   363,   579,   363,   363,   363,   363,
     363,   521,   528,   580,   457,   460,   465,   467,   470,   475,
     518,   518,   518,   380,   669,   684,   671,   673,   528,   427,
      57,    57,    57,   460,    57,   467,    57,   475,   518,   380,
     403,   411,   418,   467,   427,    43,   444,   507,   512,   527,
     518,    45,   380,   507,   507,   507,   507,   403,   411,   418,
     507,   507,   509,   467,   380,   507,   507,   411,   512,   502,
     423,     7,     8,   114,   257,   258,   635,   308,   419,   104,
     127,   292,   423,   422,   387,   422,   397,   111,   126,   111,
     126,   376,   138,   139,   140,   141,   741,   395,   422,   398,
     422,   399,   396,   422,   398,   375,   386,   378,   424,   425,
      23,    38,   103,   174,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   774,   775,   776,
     422,   103,   382,   420,   762,   392,   764,   181,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   784,   789,   416,   422,   395,
     396,   401,   719,   415,   415,   369,   415,   415,   369,   415,
     394,   390,   384,   422,   405,   404,   418,   404,   418,   112,
     113,   126,   134,   150,   277,   278,   279,   723,   724,   725,
     379,   341,   341,   103,   415,   394,   390,   384,   405,   358,
     711,   366,   427,   467,   475,   518,   380,   403,   411,   418,
     454,   455,   682,   682,   682,   293,   363,   668,   310,   363,
     683,   363,   557,   670,   363,   503,   672,     5,   126,   150,
     595,    85,   595,   617,   618,   645,   176,    23,    23,    97,
     363,    52,    52,    52,   103,   312,    52,   725,    52,   595,
     104,   297,   504,   595,   312,   313,   561,   595,   103,   612,
     613,   614,   628,   632,   645,   649,   710,   716,   615,   595,
     595,    85,   503,    21,   651,   656,   657,   658,   665,   692,
     693,     7,   364,   503,   363,   103,   103,   546,    78,   111,
     126,   171,   260,   553,   503,   103,   103,   103,   503,   552,
     551,   142,   155,   171,   325,   595,   414,   383,     5,   595,
      85,   387,   397,   376,   395,   396,   381,    85,   407,   407,
     588,   629,   696,    15,    16,    17,    18,   367,    20,    22,
       8,    54,     5,   605,    85,    87,   242,   304,     7,     7,
     103,   103,   578,     5,     7,     5,   595,   613,   628,   632,
     611,     7,   502,   363,   502,   363,   625,   697,   697,   688,
     689,   690,   644,   363,   539,   630,   687,   395,   398,   396,
     398,   375,   386,   378,   424,   425,   420,   382,   392,   416,
     407,   692,     7,    20,    15,    16,    17,    18,   367,     7,
      20,    22,     8,   686,   687,   692,   595,   595,   103,   364,
     373,    20,   373,   103,   490,   427,   459,   461,   466,   472,
     476,   579,   363,   363,   363,   363,   363,   682,   682,   682,
     668,   683,   670,   672,   103,   103,   103,   363,   103,   103,
     363,   682,   104,   379,   507,   103,   637,   422,   389,   103,
     409,   409,   387,   395,   387,   395,   114,   131,   136,   137,
     242,   395,   742,   377,    97,   780,   190,   778,   195,   781,
     193,   194,   779,   191,   192,   777,   131,   382,   226,   230,
     231,   232,   788,   221,   222,   223,   224,   786,   225,   226,
     227,   228,   229,   787,   787,   230,   233,   233,   234,   235,
     234,   114,   131,   163,   785,   417,   415,   103,   103,   112,
     113,   112,   113,   379,   379,   103,   103,   342,   708,   103,
     160,   357,   713,   717,   363,   682,   363,   363,   363,   103,
     483,   380,   561,   488,   403,   484,   103,   411,   489,   418,
     595,     5,     5,   595,   630,    90,    93,   526,   659,   660,
      38,   174,   179,   189,   775,   776,   503,   503,   103,   645,
     654,   655,   595,   595,   595,   379,   103,   595,    52,   595,
     403,   103,   563,   565,   566,   411,   104,   294,   558,    22,
     412,    85,   334,    43,   595,   374,     5,   374,   276,   291,
     296,   309,   314,   662,   663,    90,    93,   526,   661,   664,
     374,   653,   462,   387,   149,   144,   149,   554,   555,   104,
     114,   570,   632,   114,   570,   420,   114,   570,   595,     5,
     595,   595,   366,   583,   583,   584,   585,   586,   103,   588,
     583,   590,   630,   651,   595,   595,    85,     8,    85,   629,
     696,   726,   726,   595,   606,   595,   605,   616,   377,   617,
     654,   374,   540,   541,   366,   692,   686,   692,   697,   697,
     688,   689,   690,   692,   103,   686,   692,   648,   692,    20,
      20,   103,    39,   373,   364,   373,   429,   526,   579,    37,
      47,    52,    54,    56,   163,   276,   291,   309,   314,   316,
     364,   373,   429,   458,   526,    44,    94,   114,   163,   364,
     373,   429,   492,   498,   499,   526,   528,    40,    89,    90,
      91,    92,    94,    97,   114,   163,   276,   364,   373,   429,
     473,   526,   531,   532,    40,    90,    92,   114,   163,   364,
     373,   429,   473,   526,   531,    41,    44,   163,   291,   364,
     373,   429,   427,   459,   461,   466,   472,   476,   363,   363,
     363,   380,   403,   411,   418,   461,   476,   379,   379,     7,
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
      90,   283,   285,   520,   520,   520,   520,   373,   362,    79,
      80,   500,   501,   628,   422,    99,   373,   373,   373,   373,
     373,   464,   633,   504,   504,   362,    95,    96,   474,   103,
     104,   129,   130,   253,   273,   274,   480,   481,   491,    86,
      87,    88,    90,   468,   469,   373,   373,   373,   532,   464,
     504,   362,   481,   468,   373,   373,   373,   104,   362,    99,
     380,   364,   364,   364,   364,   364,   486,   487,   485,   364,
     364,   103,     7,   408,   103,   393,   401,   364,    94,   134,
     277,   364,   373,   429,   526,   680,    90,    97,   134,   168,
     277,   364,   373,   429,   526,   681,   114,   277,   364,   373,
     429,   526,   677,   103,   380,   562,   564,   403,   411,   559,
     418,   595,   654,   364,   379,   318,   319,   320,   321,   322,
     567,   103,   403,   103,   566,   403,   567,   103,   411,   412,
     412,   595,   374,   103,   312,   103,   297,   504,   561,   103,
     373,   555,   422,   422,   414,   422,   595,    85,   617,     5,
     364,   364,     5,   374,   541,   189,   581,   103,   482,   460,
     465,   470,   475,   520,   520,   520,   482,   482,   482,   482,
     363,   477,   628,   410,   104,     8,   373,   373,   373,   467,
     410,     8,   373,     7,   373,     5,   373,   467,     5,   373,
     151,   493,   477,   373,   364,   364,   364,   377,   103,   708,
     362,   166,   171,   676,   506,   379,   504,   103,   676,   103,
     506,   379,   105,   506,   379,   533,   293,   104,   558,   379,
     103,   294,   381,   381,   563,   565,   558,   398,   398,   595,
     364,   617,   699,   186,   582,   373,   363,   363,   363,   363,
     363,   482,   482,   482,   363,   363,   363,   363,   104,   105,
     478,   479,   628,   373,    41,   633,   480,   422,   469,    87,
     463,   464,   633,    37,    87,   291,   309,   314,   316,   471,
     481,    22,   103,   104,   360,   494,   495,   496,   628,   373,
     373,   379,   379,   379,     7,   393,   363,   424,   420,   373,
     373,   373,   373,   373,   373,   373,   134,   373,   364,   379,
     103,   562,   564,   559,   364,   374,   581,   490,   461,   466,
     472,   476,   363,   363,   363,   483,   488,   484,   489,     7,
     364,   104,   464,   373,     8,   427,   481,   380,   403,   411,
     418,   373,   373,   103,    22,    25,   103,   104,   678,   679,
     676,   380,   403,   403,   411,   582,   364,   364,   364,   364,
     364,   486,   487,   485,   364,   364,   364,   364,   374,   479,
      43,    44,   497,   373,   633,   373,   422,   422,   103,   103,
       5,     7,   364,   373,   373,   373,   373,   373,   373,   364,
     364,   364,   373,   373,   373,   373,   503,   628,   362,   493,
     422,   103,   679,   373,   422,   427,   379,   379,   379,   380,
     403,   411,   418,   477,   410,   373,   373,   373
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
     440,   440,   440,   440,   441,   441,   441,   441,   441,   441,
     441,   441,   441,   441,   441,   441,   441,   441,   441,   442,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   444,   445,   445,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   447,   447,   447,   447,   447,   447,
     447,   448,   449,   449,   450,   450,   451,   452,   452,   453,
     453,   453,   453,   453,   453,   453,   453,   454,   454,   455,
     455,   455,   456,   457,   458,   458,   459,   459,   459,   459,
     459,   459,   459,   459,   459,   459,   459,   459,   459,   459,
     459,   459,   460,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   462,   462,   462,   463,   463,   464,   464,   465,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   467,   467,   468,   468,   469,   469,   469,
     469,   470,   471,   471,   471,   471,   471,   472,   472,   472,
     472,   472,   472,   472,   472,   472,   472,   472,   472,   472,
     472,   473,   473,   474,   474,   475,   476,   476,   476,   476,
     476,   476,   476,   477,   477,   478,   478,   478,   479,   479,
     479,   480,   480,   481,   481,   482,   483,   483,   483,   483,
     483,   484,   484,   484,   484,   484,   485,   485,   485,   485,
     485,   486,   486,   486,   486,   486,   487,   487,   487,   487,
     487,   488,   488,   488,   488,   488,   489,   489,   489,   489,
     489,   490,   490,   490,   490,   490,   491,   491,   491,   491,
     491,   492,   493,   494,   494,   495,   495,   495,   495,   495,
     496,   496,   497,   497,   497,   497,   498,   499,   500,   500,
     501,   501,   502,   502,   503,   503,   503,   504,   505,   505,
     506,   506,   506,   506,   506,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   524,   524,   524,   525,   526,   527,
     527,   528,   528,   529,   530,   530,   531,   531,   532,   532,
     532,   532,   532,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   534,   535,   535,   536,   537,
     537,   538,   539,   539,   540,   540,   540,   541,   542,   542,
     543,   543,   544,   544,   545,   545,   546,   546,   547,   547,
     547,   548,   548,   549,   550,   550,   551,   551,   551,   551,
     551,   551,   552,   553,   553,   553,   553,   553,   554,   554,
     555,   555,   556,   556,   556,   557,   557,   557,   558,   558,
     559,   559,   560,   560,   561,   561,   561,   562,   562,   563,
     564,   564,   565,   565,   566,   566,   567,   567,   567,   567,
     567,   568,   569,   570,   570,   571,   571,   571,   571,   571,
     571,   571,   571,   572,   573,   573,   574,   574,   574,   574,
     574,   574,   575,   575,   576,   576,   577,   577,   578,   578,
     578,   578,   579,   579,   580,   581,   581,   582,   582,   583,
     583,   583,   583,   583,   583,   583,   583,   583,   583,   583,
     583,   583,   584,   584,   584,   585,   585,   586,   586,   587,
     587,   588,   589,   589,   590,   590,   591,   591,   592,   593,
     594,   594,   595,   595,   595,   596,   596,   596,   596,   596,
     596,   596,   596,   596,   596,   596,   596,   596,   596,   597,
     597,   598,   599,   599,   599,   600,   600,   601,   602,   602,
     602,   602,   602,   603,   603,   604,   604,   605,   605,   606,
     606,   606,   607,   607,   607,   607,   608,   608,   609,   610,
     610,   611,   611,   612,   612,   613,   613,   613,   614,   614,
     614,   614,   615,   615,   616,   616,   617,   617,   618,   619,
     619,   619,   620,   620,   620,   621,   621,   622,   622,   623,
     624,   624,   625,   626,   626,   627,   628,   629,   629,   630,
     630,   631,   632,   633,   633,   633,   633,   633,   633,   633,
     633,   633,   633,   633,   633,   633,   633,   633,   634,   635,
     635,   635,   636,   636,   636,   636,   636,   637,   637,   638,
     638,   639,   639,   640,   640,   640,   641,   641,   642,   642,
     643,   643,   644,   645,   645,   646,   647,   648,   648,   649,
     650,   650,   650,   651,   652,   652,   652,   653,   653,   653,
     654,   654,   655,   656,   656,   657,   657,   658,   658,   659,
     659,   660,   660,   660,   661,   661,   662,   662,   663,   663,
     663,   663,   663,   663,   663,   663,   663,   664,   664,   664,
     665,   666,   666,   667,   667,   667,   667,   668,   669,   670,
     671,   672,   673,   674,   674,   674,   675,   675,   675,   676,
     676,   677,   677,   678,   678,   679,   680,   680,   680,   681,
     681,   681,   681,   681,   682,   683,   683,   684,   685,   685,
     685,   685,   685,   685,   685,   685,   686,   686,   687,   687,
     687,   688,   688,   688,   689,   689,   690,   690,   691,   691,
     692,   693,   693,   693,   693,   694,   694,   695,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   697,   697,   697,   697,   697,   697,   697,   697,
     697,   697,   697,   697,   697,   697,   697,   697,   697,   697,
     698,   698,   698,   698,   698,   698,   698,   699,   699,   699,
     699,   699,   699,   700,   700,   701,   701,   701,   702,   702,
     703,   703,   703,   703,   703,   704,   704,   704,   704,   704,
     704,   704,   704,   704,   704,   704,   704,   704,   704,   704,
     704,   704,   704,   704,   704,   704,   704,   704,   704,   705,
     705,   705,   705,   705,   705,   706,   706,   707,   707,   707,
     708,   708,   709,   709,   710,   711,   711,   712,   712,   713,
     713,   714,   714,   715,   715,   716,   716,   716,   717,   717,
     718,   718,   719,   719,   719,   719,   720,   720,   720,   721,
     721,   722,   722,   722,   722,   722,   722,   722,   722,   722,
     722,   722,   722,   722,   722,   722,   722,   722,   723,   723,
     723,   723,   723,   723,   723,   724,   724,   724,   724,   725,
     725,   725,   725,   726,   726,   727,   727,   728,   728,   728,
     728,   729,   730,   730,   730,   730,   730,   730,   730,   730,
     730,   730,   730,   730,   730,   730,   730,   730,   730,   730,
     730,   730,   730,   730,   731,   732,   732,   732,   732,   733,
     734,   734,   734,   735,   736,   736,   736,   736,   736,   737,
     738,   738,   738,   738,   738,   738,   738,   738,   738,   739,
     739,   739,   740,   740,   740,   740,   740,   740,   740,   740,
     740,   740,   740,   740,   741,   741,   741,   741,   742,   742,
     742,   742,   742,   743,   744,   744,   744,   744,   744,   744,
     744,   745,   746,   746,   746,   746,   747,   748,   748,   748,
     748,   748,   748,   748,   748,   748,   749,   750,   750,   750,
     750,   750,   750,   750,   750,   751,   752,   752,   752,   752,
     752,   753,   754,   754,   755,   756,   756,   756,   757,   758,
     758,   758,   758,   759,   760,   760,   760,   760,   761,   761,
     761,   761,   762,   762,   762,   762,   762,   762,   762,   762,
     762,   762,   762,   762,   762,   762,   763,   763,   763,   764,
     764,   765,   765,   766,   766,   767,   767,   768,   768,   769,
     769,   770,   770,   770,   771,   772,   773,   773,   773,   773,
     773,   773,   773,   773,   773,   773,   774,   774,   774,   774,
     774,   774,   775,   775,   775,   775,   775,   776,   776,   776,
     776,   776,   776,   776,   776,   776,   776,   776,   776,   777,
     777,   778,   779,   779,   780,   781,   782,   782,   783,   783,
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
       1,     0,     2,     2,     2,     2,     2,     0,     2,     2,
       4,     7,     8,     6,     7,     7,     4,     3,     4,     3,
       3,     3,     2,     1,     1,     0,     0,     2,     2,     5,
       5,     3,     4,     3,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     3,     0,     0,     2,     2,     2,
       2,     0,     2,     2,     2,     2,     0,     2,     2,     2,
       2,     0,     2,     2,     2,     2,     0,     2,     2,     2,
       2,     0,     2,     2,     2,     2,     0,     2,     2,     2,
       2,     0,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     7,     2,     1,     1,     1,     1,     1,     3,     3,
       1,     2,     2,     2,     3,     0,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       2,     2,     1,     2,     1,     1,     2,     3,     2,     3,
       1,     2,     3,     1,     2,     3,     1,     2,     3,     1,
       2,     2,     2,     1,     2,     2,     2,     2,     2,     0,
       1,     1,     2,     1,     1,     2,     1,     2,     2,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     1,     1,     2,     2,     2,     2,     1,
       1,     2,     1,     1,     2,     3,     1,     1,     5,     1,
       1,     3,     3,     1,     1,     3,     3,     5,     4,     5,
       1,     2,     1,     3,     1,     2,     2,     2,     1,     3,
       3,     1,     2,     1,     1,     2,     2,     2,     2,     2,
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
       6,     6,     4,     5,     6,     4,     4,     2,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     4,     0,     4,
       0,     1,     0,     1,     1,     1,     1,     1,     1,     2,
       2,     6,     3,     1,     3,     3,     3,     7,     3,     3,
       3,     3,     3,     3,     0,     4,     4,     0,     2,     2,
       4,     4,     5,     5,     3,     3,     3,     3,     1,     1,
       1,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     1,     1,     3,     3,     1,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     1,     2,     2,     1,     1,
       1,     2,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     1,     2,     2,     2,     2,     2,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     5,
       3,     5,     1,     5,     5,     3,     5,     1,     1,     1,
       0,     2,     1,     1,     6,     2,     0,     1,     1,     1,
       1,     1,     1,     5,     6,     8,     6,     5,     2,     2,
       3,     4,     1,     1,     1,     2,     3,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     5,     5,     5,
       6,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     7,     1,     1,     2,     1,     3,
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
       3,     9,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     2,     2,     1,     1,     3,
       3,     1,     1,     1,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     4,     1,     1,
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
#line 359 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6214 "parser_bison.c"
        break;

    case YYSYMBOL_QUOTED_STRING: /* "quoted string"  */
#line 359 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6220 "parser_bison.c"
        break;

    case YYSYMBOL_ASTERISK_STRING: /* "string with a trailing asterisk"  */
#line 359 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6226 "parser_bison.c"
        break;

    case YYSYMBOL_line: /* line  */
#line 682 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6232 "parser_bison.c"
        break;

    case YYSYMBOL_base_cmd: /* base_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6238 "parser_bison.c"
        break;

    case YYSYMBOL_add_cmd: /* add_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6244 "parser_bison.c"
        break;

    case YYSYMBOL_replace_cmd: /* replace_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6250 "parser_bison.c"
        break;

    case YYSYMBOL_create_cmd: /* create_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6256 "parser_bison.c"
        break;

    case YYSYMBOL_insert_cmd: /* insert_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6262 "parser_bison.c"
        break;

    case YYSYMBOL_table_or_id_spec: /* table_or_id_spec  */
#line 688 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6268 "parser_bison.c"
        break;

    case YYSYMBOL_chain_or_id_spec: /* chain_or_id_spec  */
#line 690 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6274 "parser_bison.c"
        break;

    case YYSYMBOL_set_or_id_spec: /* set_or_id_spec  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6280 "parser_bison.c"
        break;

    case YYSYMBOL_obj_or_id_spec: /* obj_or_id_spec  */
#line 697 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6286 "parser_bison.c"
        break;

    case YYSYMBOL_delete_cmd: /* delete_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6292 "parser_bison.c"
        break;

    case YYSYMBOL_destroy_cmd: /* destroy_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6298 "parser_bison.c"
        break;

    case YYSYMBOL_get_cmd: /* get_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6304 "parser_bison.c"
        break;

    case YYSYMBOL_list_cmd: /* list_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6310 "parser_bison.c"
        break;

    case YYSYMBOL_basehook_device_name: /* basehook_device_name  */
#line 709 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6316 "parser_bison.c"
        break;

    case YYSYMBOL_basehook_spec: /* basehook_spec  */
#line 703 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6322 "parser_bison.c"
        break;

    case YYSYMBOL_reset_cmd: /* reset_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6328 "parser_bison.c"
        break;

    case YYSYMBOL_flush_cmd: /* flush_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6334 "parser_bison.c"
        break;

    case YYSYMBOL_rename_cmd: /* rename_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6340 "parser_bison.c"
        break;

    case YYSYMBOL_import_cmd: /* import_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6346 "parser_bison.c"
        break;

    case YYSYMBOL_export_cmd: /* export_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6352 "parser_bison.c"
        break;

    case YYSYMBOL_monitor_cmd: /* monitor_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6358 "parser_bison.c"
        break;

    case YYSYMBOL_monitor_event: /* monitor_event  */
#line 928 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6364 "parser_bison.c"
        break;

    case YYSYMBOL_describe_cmd: /* describe_cmd  */
#line 685 "parser_bison.y"
            { cmd_free(((*yyvaluep).cmd)); }
#line 6370 "parser_bison.c"
        break;

    case YYSYMBOL_table_block_alloc: /* table_block_alloc  */
#line 715 "parser_bison.y"
            { close_scope(state); table_free(((*yyvaluep).table)); }
#line 6376 "parser_bison.c"
        break;

    case YYSYMBOL_chain_block_alloc: /* chain_block_alloc  */
#line 717 "parser_bison.y"
            { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 6382 "parser_bison.c"
        break;

    case YYSYMBOL_typeof_data_expr: /* typeof_data_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6388 "parser_bison.c"
        break;

    case YYSYMBOL_typeof_expr: /* typeof_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6394 "parser_bison.c"
        break;

    case YYSYMBOL_set_block_alloc: /* set_block_alloc  */
#line 726 "parser_bison.y"
            { set_free(((*yyvaluep).set)); }
#line 6400 "parser_bison.c"
        break;

    case YYSYMBOL_set_block_expr: /* set_block_expr  */
#line 830 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6406 "parser_bison.c"
        break;

    case YYSYMBOL_map_block_alloc: /* map_block_alloc  */
#line 729 "parser_bison.y"
            { set_free(((*yyvaluep).set)); }
#line 6412 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_block_alloc: /* flowtable_block_alloc  */
#line 733 "parser_bison.y"
            { flowtable_free(((*yyvaluep).flowtable)); }
#line 6418 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_expr: /* flowtable_expr  */
#line 830 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6424 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_list_expr: /* flowtable_list_expr  */
#line 830 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6430 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_expr_member: /* flowtable_expr_member  */
#line 830 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6436 "parser_bison.c"
        break;

    case YYSYMBOL_data_type_atom_expr: /* data_type_atom_expr  */
#line 679 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6442 "parser_bison.c"
        break;

    case YYSYMBOL_data_type_expr: /* data_type_expr  */
#line 679 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6448 "parser_bison.c"
        break;

    case YYSYMBOL_obj_block_alloc: /* obj_block_alloc  */
#line 736 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6454 "parser_bison.c"
        break;

    case YYSYMBOL_type_identifier: /* type_identifier  */
#line 674 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6460 "parser_bison.c"
        break;

    case YYSYMBOL_extended_prio_name: /* extended_prio_name  */
#line 709 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6466 "parser_bison.c"
        break;

    case YYSYMBOL_dev_spec: /* dev_spec  */
#line 712 "parser_bison.y"
            { xfree(((*yyvaluep).expr)); }
#line 6472 "parser_bison.c"
        break;

    case YYSYMBOL_policy_expr: /* policy_expr  */
#line 787 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6478 "parser_bison.c"
        break;

    case YYSYMBOL_identifier: /* identifier  */
#line 674 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6484 "parser_bison.c"
        break;

    case YYSYMBOL_string: /* string  */
#line 674 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6490 "parser_bison.c"
        break;

    case YYSYMBOL_table_spec: /* table_spec  */
#line 688 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6496 "parser_bison.c"
        break;

    case YYSYMBOL_tableid_spec: /* tableid_spec  */
#line 688 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6502 "parser_bison.c"
        break;

    case YYSYMBOL_chain_spec: /* chain_spec  */
#line 690 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6508 "parser_bison.c"
        break;

    case YYSYMBOL_chainid_spec: /* chainid_spec  */
#line 690 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6514 "parser_bison.c"
        break;

    case YYSYMBOL_chain_identifier: /* chain_identifier  */
#line 693 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6520 "parser_bison.c"
        break;

    case YYSYMBOL_set_spec: /* set_spec  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6526 "parser_bison.c"
        break;

    case YYSYMBOL_setid_spec: /* setid_spec  */
#line 695 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6532 "parser_bison.c"
        break;

    case YYSYMBOL_set_identifier: /* set_identifier  */
#line 700 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6538 "parser_bison.c"
        break;

    case YYSYMBOL_flowtable_spec: /* flowtable_spec  */
#line 693 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6544 "parser_bison.c"
        break;

    case YYSYMBOL_flowtableid_spec: /* flowtableid_spec  */
#line 700 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6550 "parser_bison.c"
        break;

    case YYSYMBOL_obj_spec: /* obj_spec  */
#line 697 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6556 "parser_bison.c"
        break;

    case YYSYMBOL_objid_spec: /* objid_spec  */
#line 697 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6562 "parser_bison.c"
        break;

    case YYSYMBOL_obj_identifier: /* obj_identifier  */
#line 700 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6568 "parser_bison.c"
        break;

    case YYSYMBOL_handle_spec: /* handle_spec  */
#line 693 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6574 "parser_bison.c"
        break;

    case YYSYMBOL_position_spec: /* position_spec  */
#line 693 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6580 "parser_bison.c"
        break;

    case YYSYMBOL_index_spec: /* index_spec  */
#line 693 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6586 "parser_bison.c"
        break;

    case YYSYMBOL_rule_position: /* rule_position  */
#line 693 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6592 "parser_bison.c"
        break;

    case YYSYMBOL_ruleid_spec: /* ruleid_spec  */
#line 693 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6598 "parser_bison.c"
        break;

    case YYSYMBOL_comment_spec: /* comment_spec  */
#line 674 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6604 "parser_bison.c"
        break;

    case YYSYMBOL_ruleset_spec: /* ruleset_spec  */
#line 693 "parser_bison.y"
            { handle_free(&((*yyvaluep).handle)); }
#line 6610 "parser_bison.c"
        break;

    case YYSYMBOL_rule: /* rule  */
#line 719 "parser_bison.y"
            { rule_free(((*yyvaluep).rule)); }
#line 6616 "parser_bison.c"
        break;

    case YYSYMBOL_stmt_list: /* stmt_list  */
#line 739 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6622 "parser_bison.c"
        break;

    case YYSYMBOL_stateful_stmt_list: /* stateful_stmt_list  */
#line 739 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 6628 "parser_bison.c"
        break;

    case YYSYMBOL_stateful_stmt: /* stateful_stmt  */
#line 743 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6634 "parser_bison.c"
        break;

    case YYSYMBOL_stmt: /* stmt  */
#line 741 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6640 "parser_bison.c"
        break;

    case YYSYMBOL_xt_stmt: /* xt_stmt  */
#line 952 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6646 "parser_bison.c"
        break;

    case YYSYMBOL_chain_stmt: /* chain_stmt  */
#line 766 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6652 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_stmt: /* verdict_stmt  */
#line 741 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6658 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_stmt: /* verdict_map_stmt  */
#line 824 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6664 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_expr: /* verdict_map_expr  */
#line 827 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6670 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_list_expr: /* verdict_map_list_expr  */
#line 827 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6676 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_map_list_member_expr: /* verdict_map_list_member_expr  */
#line 827 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6682 "parser_bison.c"
        break;

    case YYSYMBOL_connlimit_stmt: /* connlimit_stmt  */
#line 754 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6688 "parser_bison.c"
        break;

    case YYSYMBOL_counter_stmt: /* counter_stmt  */
#line 743 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6694 "parser_bison.c"
        break;

    case YYSYMBOL_counter_stmt_alloc: /* counter_stmt_alloc  */
#line 743 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6700 "parser_bison.c"
        break;

    case YYSYMBOL_last_stmt: /* last_stmt  */
#line 743 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6706 "parser_bison.c"
        break;

    case YYSYMBOL_log_stmt: /* log_stmt  */
#line 751 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6712 "parser_bison.c"
        break;

    case YYSYMBOL_log_stmt_alloc: /* log_stmt_alloc  */
#line 751 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6718 "parser_bison.c"
        break;

    case YYSYMBOL_limit_stmt: /* limit_stmt  */
#line 754 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6724 "parser_bison.c"
        break;

    case YYSYMBOL_quota_unit: /* quota_unit  */
#line 709 "parser_bison.y"
            { xfree(((*yyvaluep).string)); }
#line 6730 "parser_bison.c"
        break;

    case YYSYMBOL_quota_stmt: /* quota_stmt  */
#line 754 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6736 "parser_bison.c"
        break;

    case YYSYMBOL_reject_stmt: /* reject_stmt  */
#line 757 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6742 "parser_bison.c"
        break;

    case YYSYMBOL_reject_stmt_alloc: /* reject_stmt_alloc  */
#line 757 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6748 "parser_bison.c"
        break;

    case YYSYMBOL_reject_with_expr: /* reject_with_expr  */
#line 772 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6754 "parser_bison.c"
        break;

    case YYSYMBOL_nat_stmt: /* nat_stmt  */
#line 759 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6760 "parser_bison.c"
        break;

    case YYSYMBOL_nat_stmt_alloc: /* nat_stmt_alloc  */
#line 759 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6766 "parser_bison.c"
        break;

    case YYSYMBOL_tproxy_stmt: /* tproxy_stmt  */
#line 762 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6772 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_stmt: /* synproxy_stmt  */
#line 764 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6778 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_stmt_alloc: /* synproxy_stmt_alloc  */
#line 764 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6784 "parser_bison.c"
        break;

    case YYSYMBOL_synproxy_obj: /* synproxy_obj  */
#line 850 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 6790 "parser_bison.c"
        break;

    case YYSYMBOL_primary_stmt_expr: /* primary_stmt_expr  */
#line 811 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6796 "parser_bison.c"
        break;

    case YYSYMBOL_shift_stmt_expr: /* shift_stmt_expr  */
#line 813 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6802 "parser_bison.c"
        break;

    case YYSYMBOL_and_stmt_expr: /* and_stmt_expr  */
#line 815 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6808 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_stmt_expr: /* exclusive_or_stmt_expr  */
#line 815 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6814 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_stmt_expr: /* inclusive_or_stmt_expr  */
#line 815 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6820 "parser_bison.c"
        break;

    case YYSYMBOL_basic_stmt_expr: /* basic_stmt_expr  */
#line 811 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6826 "parser_bison.c"
        break;

    case YYSYMBOL_concat_stmt_expr: /* concat_stmt_expr  */
#line 803 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6832 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt_expr_set: /* map_stmt_expr_set  */
#line 803 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6838 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt_expr: /* map_stmt_expr  */
#line 803 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6844 "parser_bison.c"
        break;

    case YYSYMBOL_prefix_stmt_expr: /* prefix_stmt_expr  */
#line 808 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6850 "parser_bison.c"
        break;

    case YYSYMBOL_range_stmt_expr: /* range_stmt_expr  */
#line 808 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6856 "parser_bison.c"
        break;

    case YYSYMBOL_multiton_stmt_expr: /* multiton_stmt_expr  */
#line 806 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6862 "parser_bison.c"
        break;

    case YYSYMBOL_stmt_expr: /* stmt_expr  */
#line 803 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6868 "parser_bison.c"
        break;

    case YYSYMBOL_masq_stmt: /* masq_stmt  */
#line 759 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6874 "parser_bison.c"
        break;

    case YYSYMBOL_masq_stmt_alloc: /* masq_stmt_alloc  */
#line 759 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6880 "parser_bison.c"
        break;

    case YYSYMBOL_redir_stmt: /* redir_stmt  */
#line 759 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6886 "parser_bison.c"
        break;

    case YYSYMBOL_redir_stmt_alloc: /* redir_stmt_alloc  */
#line 759 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6892 "parser_bison.c"
        break;

    case YYSYMBOL_dup_stmt: /* dup_stmt  */
#line 775 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6898 "parser_bison.c"
        break;

    case YYSYMBOL_fwd_stmt: /* fwd_stmt  */
#line 777 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6904 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt: /* queue_stmt  */
#line 770 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6910 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_compat: /* queue_stmt_compat  */
#line 770 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6916 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_alloc: /* queue_stmt_alloc  */
#line 770 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6922 "parser_bison.c"
        break;

    case YYSYMBOL_queue_expr: /* queue_expr  */
#line 772 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6928 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_expr_simple: /* queue_stmt_expr_simple  */
#line 772 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6934 "parser_bison.c"
        break;

    case YYSYMBOL_queue_stmt_expr: /* queue_stmt_expr  */
#line 772 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6940 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_stmt: /* set_elem_expr_stmt  */
#line 834 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6946 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_stmt_alloc: /* set_elem_expr_stmt_alloc  */
#line 834 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6952 "parser_bison.c"
        break;

    case YYSYMBOL_set_stmt: /* set_stmt  */
#line 779 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6958 "parser_bison.c"
        break;

    case YYSYMBOL_map_stmt: /* map_stmt  */
#line 782 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6964 "parser_bison.c"
        break;

    case YYSYMBOL_meter_stmt: /* meter_stmt  */
#line 784 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6970 "parser_bison.c"
        break;

    case YYSYMBOL_flow_stmt_legacy_alloc: /* flow_stmt_legacy_alloc  */
#line 784 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6976 "parser_bison.c"
        break;

    case YYSYMBOL_meter_stmt_alloc: /* meter_stmt_alloc  */
#line 784 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6982 "parser_bison.c"
        break;

    case YYSYMBOL_match_stmt: /* match_stmt  */
#line 741 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 6988 "parser_bison.c"
        break;

    case YYSYMBOL_variable_expr: /* variable_expr  */
#line 787 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 6994 "parser_bison.c"
        break;

    case YYSYMBOL_symbol_expr: /* symbol_expr  */
#line 787 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7000 "parser_bison.c"
        break;

    case YYSYMBOL_set_ref_expr: /* set_ref_expr  */
#line 795 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7006 "parser_bison.c"
        break;

    case YYSYMBOL_set_ref_symbol_expr: /* set_ref_symbol_expr  */
#line 795 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7012 "parser_bison.c"
        break;

    case YYSYMBOL_integer_expr: /* integer_expr  */
#line 787 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7018 "parser_bison.c"
        break;

    case YYSYMBOL_primary_expr: /* primary_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7024 "parser_bison.c"
        break;

    case YYSYMBOL_fib_expr: /* fib_expr  */
#line 919 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7030 "parser_bison.c"
        break;

    case YYSYMBOL_osf_expr: /* osf_expr  */
#line 924 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7036 "parser_bison.c"
        break;

    case YYSYMBOL_shift_expr: /* shift_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7042 "parser_bison.c"
        break;

    case YYSYMBOL_and_expr: /* and_expr  */
#line 789 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7048 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_expr: /* exclusive_or_expr  */
#line 791 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7054 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_expr: /* inclusive_or_expr  */
#line 791 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7060 "parser_bison.c"
        break;

    case YYSYMBOL_basic_expr: /* basic_expr  */
#line 793 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7066 "parser_bison.c"
        break;

    case YYSYMBOL_concat_expr: /* concat_expr  */
#line 818 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7072 "parser_bison.c"
        break;

    case YYSYMBOL_prefix_rhs_expr: /* prefix_rhs_expr  */
#line 800 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7078 "parser_bison.c"
        break;

    case YYSYMBOL_range_rhs_expr: /* range_rhs_expr  */
#line 800 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7084 "parser_bison.c"
        break;

    case YYSYMBOL_multiton_rhs_expr: /* multiton_rhs_expr  */
#line 798 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7090 "parser_bison.c"
        break;

    case YYSYMBOL_map_expr: /* map_expr  */
#line 821 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7096 "parser_bison.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 840 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7102 "parser_bison.c"
        break;

    case YYSYMBOL_set_expr: /* set_expr  */
#line 830 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7108 "parser_bison.c"
        break;

    case YYSYMBOL_set_list_expr: /* set_list_expr  */
#line 830 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7114 "parser_bison.c"
        break;

    case YYSYMBOL_set_list_member_expr: /* set_list_member_expr  */
#line 830 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7120 "parser_bison.c"
        break;

    case YYSYMBOL_meter_key_expr: /* meter_key_expr  */
#line 837 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7126 "parser_bison.c"
        break;

    case YYSYMBOL_meter_key_expr_alloc: /* meter_key_expr_alloc  */
#line 837 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7132 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr: /* set_elem_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7138 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_key_expr: /* set_elem_key_expr  */
#line 972 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7144 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_expr_alloc: /* set_elem_expr_alloc  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7150 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_stmt_list: /* set_elem_stmt_list  */
#line 739 "parser_bison.y"
            { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 7156 "parser_bison.c"
        break;

    case YYSYMBOL_set_elem_stmt: /* set_elem_stmt  */
#line 741 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7162 "parser_bison.c"
        break;

    case YYSYMBOL_set_lhs_expr: /* set_lhs_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7168 "parser_bison.c"
        break;

    case YYSYMBOL_set_rhs_expr: /* set_rhs_expr  */
#line 832 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7174 "parser_bison.c"
        break;

    case YYSYMBOL_initializer_expr: /* initializer_expr  */
#line 840 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7180 "parser_bison.c"
        break;

    case YYSYMBOL_counter_obj: /* counter_obj  */
#line 850 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7186 "parser_bison.c"
        break;

    case YYSYMBOL_quota_obj: /* quota_obj  */
#line 850 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7192 "parser_bison.c"
        break;

    case YYSYMBOL_secmark_obj: /* secmark_obj  */
#line 850 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7198 "parser_bison.c"
        break;

    case YYSYMBOL_timeout_states: /* timeout_states  */
#line 965 "parser_bison.y"
            { xfree(((*yyvaluep).list)); }
#line 7204 "parser_bison.c"
        break;

    case YYSYMBOL_timeout_state: /* timeout_state  */
#line 965 "parser_bison.y"
            { xfree(((*yyvaluep).list)); }
#line 7210 "parser_bison.c"
        break;

    case YYSYMBOL_ct_obj_alloc: /* ct_obj_alloc  */
#line 850 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7216 "parser_bison.c"
        break;

    case YYSYMBOL_limit_obj: /* limit_obj  */
#line 850 "parser_bison.y"
            { obj_free(((*yyvaluep).obj)); }
#line 7222 "parser_bison.c"
        break;

    case YYSYMBOL_relational_expr: /* relational_expr  */
#line 853 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7228 "parser_bison.c"
        break;

    case YYSYMBOL_list_rhs_expr: /* list_rhs_expr  */
#line 845 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7234 "parser_bison.c"
        break;

    case YYSYMBOL_rhs_expr: /* rhs_expr  */
#line 843 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7240 "parser_bison.c"
        break;

    case YYSYMBOL_shift_rhs_expr: /* shift_rhs_expr  */
#line 845 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7246 "parser_bison.c"
        break;

    case YYSYMBOL_and_rhs_expr: /* and_rhs_expr  */
#line 847 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7252 "parser_bison.c"
        break;

    case YYSYMBOL_exclusive_or_rhs_expr: /* exclusive_or_rhs_expr  */
#line 847 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7258 "parser_bison.c"
        break;

    case YYSYMBOL_inclusive_or_rhs_expr: /* inclusive_or_rhs_expr  */
#line 847 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7264 "parser_bison.c"
        break;

    case YYSYMBOL_basic_rhs_expr: /* basic_rhs_expr  */
#line 843 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7270 "parser_bison.c"
        break;

    case YYSYMBOL_concat_rhs_expr: /* concat_rhs_expr  */
#line 843 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7276 "parser_bison.c"
        break;

    case YYSYMBOL_boolean_expr: /* boolean_expr  */
#line 955 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7282 "parser_bison.c"
        break;

    case YYSYMBOL_keyword_expr: /* keyword_expr  */
#line 840 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7288 "parser_bison.c"
        break;

    case YYSYMBOL_primary_rhs_expr: /* primary_rhs_expr  */
#line 845 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7294 "parser_bison.c"
        break;

    case YYSYMBOL_verdict_expr: /* verdict_expr  */
#line 787 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7300 "parser_bison.c"
        break;

    case YYSYMBOL_chain_expr: /* chain_expr  */
#line 787 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7306 "parser_bison.c"
        break;

    case YYSYMBOL_meta_expr: /* meta_expr  */
#line 901 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7312 "parser_bison.c"
        break;

    case YYSYMBOL_meta_stmt: /* meta_stmt  */
#line 749 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7318 "parser_bison.c"
        break;

    case YYSYMBOL_socket_expr: /* socket_expr  */
#line 905 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7324 "parser_bison.c"
        break;

    case YYSYMBOL_numgen_expr: /* numgen_expr  */
#line 866 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7330 "parser_bison.c"
        break;

    case YYSYMBOL_xfrm_expr: /* xfrm_expr  */
#line 969 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7336 "parser_bison.c"
        break;

    case YYSYMBOL_hash_expr: /* hash_expr  */
#line 866 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7342 "parser_bison.c"
        break;

    case YYSYMBOL_rt_expr: /* rt_expr  */
#line 911 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7348 "parser_bison.c"
        break;

    case YYSYMBOL_ct_expr: /* ct_expr  */
#line 915 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7354 "parser_bison.c"
        break;

    case YYSYMBOL_symbol_stmt_expr: /* symbol_stmt_expr  */
#line 845 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7360 "parser_bison.c"
        break;

    case YYSYMBOL_list_stmt_expr: /* list_stmt_expr  */
#line 813 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7366 "parser_bison.c"
        break;

    case YYSYMBOL_ct_stmt: /* ct_stmt  */
#line 747 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7372 "parser_bison.c"
        break;

    case YYSYMBOL_payload_stmt: /* payload_stmt  */
#line 745 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7378 "parser_bison.c"
        break;

    case YYSYMBOL_payload_expr: /* payload_expr  */
#line 857 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7384 "parser_bison.c"
        break;

    case YYSYMBOL_payload_raw_expr: /* payload_raw_expr  */
#line 857 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7390 "parser_bison.c"
        break;

    case YYSYMBOL_eth_hdr_expr: /* eth_hdr_expr  */
#line 860 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7396 "parser_bison.c"
        break;

    case YYSYMBOL_vlan_hdr_expr: /* vlan_hdr_expr  */
#line 860 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7402 "parser_bison.c"
        break;

    case YYSYMBOL_arp_hdr_expr: /* arp_hdr_expr  */
#line 863 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7408 "parser_bison.c"
        break;

    case YYSYMBOL_ip_hdr_expr: /* ip_hdr_expr  */
#line 866 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7414 "parser_bison.c"
        break;

    case YYSYMBOL_icmp_hdr_expr: /* icmp_hdr_expr  */
#line 866 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7420 "parser_bison.c"
        break;

    case YYSYMBOL_igmp_hdr_expr: /* igmp_hdr_expr  */
#line 866 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7426 "parser_bison.c"
        break;

    case YYSYMBOL_ip6_hdr_expr: /* ip6_hdr_expr  */
#line 870 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7432 "parser_bison.c"
        break;

    case YYSYMBOL_icmp6_hdr_expr: /* icmp6_hdr_expr  */
#line 870 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7438 "parser_bison.c"
        break;

    case YYSYMBOL_auth_hdr_expr: /* auth_hdr_expr  */
#line 873 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7444 "parser_bison.c"
        break;

    case YYSYMBOL_esp_hdr_expr: /* esp_hdr_expr  */
#line 873 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7450 "parser_bison.c"
        break;

    case YYSYMBOL_comp_hdr_expr: /* comp_hdr_expr  */
#line 873 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7456 "parser_bison.c"
        break;

    case YYSYMBOL_udp_hdr_expr: /* udp_hdr_expr  */
#line 876 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7462 "parser_bison.c"
        break;

    case YYSYMBOL_udplite_hdr_expr: /* udplite_hdr_expr  */
#line 876 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7468 "parser_bison.c"
        break;

    case YYSYMBOL_tcp_hdr_expr: /* tcp_hdr_expr  */
#line 934 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7474 "parser_bison.c"
        break;

    case YYSYMBOL_inner_inet_expr: /* inner_inet_expr  */
#line 942 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7480 "parser_bison.c"
        break;

    case YYSYMBOL_inner_eth_expr: /* inner_eth_expr  */
#line 942 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7486 "parser_bison.c"
        break;

    case YYSYMBOL_inner_expr: /* inner_expr  */
#line 942 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7492 "parser_bison.c"
        break;

    case YYSYMBOL_vxlan_hdr_expr: /* vxlan_hdr_expr  */
#line 945 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7498 "parser_bison.c"
        break;

    case YYSYMBOL_geneve_hdr_expr: /* geneve_hdr_expr  */
#line 945 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7504 "parser_bison.c"
        break;

    case YYSYMBOL_gre_hdr_expr: /* gre_hdr_expr  */
#line 945 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7510 "parser_bison.c"
        break;

    case YYSYMBOL_gretap_hdr_expr: /* gretap_hdr_expr  */
#line 945 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7516 "parser_bison.c"
        break;

    case YYSYMBOL_optstrip_stmt: /* optstrip_stmt  */
#line 949 "parser_bison.y"
            { stmt_free(((*yyvaluep).stmt)); }
#line 7522 "parser_bison.c"
        break;

    case YYSYMBOL_dccp_hdr_expr: /* dccp_hdr_expr  */
#line 879 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7528 "parser_bison.c"
        break;

    case YYSYMBOL_sctp_chunk_alloc: /* sctp_chunk_alloc  */
#line 879 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7534 "parser_bison.c"
        break;

    case YYSYMBOL_sctp_hdr_expr: /* sctp_hdr_expr  */
#line 879 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7540 "parser_bison.c"
        break;

    case YYSYMBOL_th_hdr_expr: /* th_hdr_expr  */
#line 885 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7546 "parser_bison.c"
        break;

    case YYSYMBOL_exthdr_expr: /* exthdr_expr  */
#line 889 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7552 "parser_bison.c"
        break;

    case YYSYMBOL_hbh_hdr_expr: /* hbh_hdr_expr  */
#line 891 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7558 "parser_bison.c"
        break;

    case YYSYMBOL_rt_hdr_expr: /* rt_hdr_expr  */
#line 894 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7564 "parser_bison.c"
        break;

    case YYSYMBOL_rt0_hdr_expr: /* rt0_hdr_expr  */
#line 894 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7570 "parser_bison.c"
        break;

    case YYSYMBOL_rt2_hdr_expr: /* rt2_hdr_expr  */
#line 894 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7576 "parser_bison.c"
        break;

    case YYSYMBOL_rt4_hdr_expr: /* rt4_hdr_expr  */
#line 894 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7582 "parser_bison.c"
        break;

    case YYSYMBOL_frag_hdr_expr: /* frag_hdr_expr  */
#line 891 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7588 "parser_bison.c"
        break;

    case YYSYMBOL_dst_hdr_expr: /* dst_hdr_expr  */
#line 891 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7594 "parser_bison.c"
        break;

    case YYSYMBOL_mh_hdr_expr: /* mh_hdr_expr  */
#line 897 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7600 "parser_bison.c"
        break;

    case YYSYMBOL_exthdr_exists_expr: /* exthdr_exists_expr  */
#line 959 "parser_bison.y"
            { expr_free(((*yyvaluep).expr)); }
#line 7606 "parser_bison.c"
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
#line 196 "parser_bison.y"
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 7711 "parser_bison.c"

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
#line 978 "parser_bison.y"
                        {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 7928 "parser_bison.c"
    break;

  case 8: /* close_scope_ah: %empty  */
#line 994 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_AH); }
#line 7934 "parser_bison.c"
    break;

  case 9: /* close_scope_arp: %empty  */
#line 995 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ARP); }
#line 7940 "parser_bison.c"
    break;

  case 10: /* close_scope_at: %empty  */
#line 996 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_AT); }
#line 7946 "parser_bison.c"
    break;

  case 11: /* close_scope_comp: %empty  */
#line 997 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_COMP); }
#line 7952 "parser_bison.c"
    break;

  case 12: /* close_scope_ct: %empty  */
#line 998 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CT); }
#line 7958 "parser_bison.c"
    break;

  case 13: /* close_scope_counter: %empty  */
#line 999 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_COUNTER); }
#line 7964 "parser_bison.c"
    break;

  case 14: /* close_scope_last: %empty  */
#line 1000 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_LAST); }
#line 7970 "parser_bison.c"
    break;

  case 15: /* close_scope_dccp: %empty  */
#line 1001 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_DCCP); }
#line 7976 "parser_bison.c"
    break;

  case 16: /* close_scope_destroy: %empty  */
#line 1002 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_DESTROY); }
#line 7982 "parser_bison.c"
    break;

  case 17: /* close_scope_dst: %empty  */
#line 1003 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_DST); }
#line 7988 "parser_bison.c"
    break;

  case 18: /* close_scope_dup: %empty  */
#line 1004 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_DUP); }
#line 7994 "parser_bison.c"
    break;

  case 19: /* close_scope_esp: %empty  */
#line 1005 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_ESP); }
#line 8000 "parser_bison.c"
    break;

  case 20: /* close_scope_eth: %empty  */
#line 1006 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ETH); }
#line 8006 "parser_bison.c"
    break;

  case 21: /* close_scope_export: %empty  */
#line 1007 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_EXPORT); }
#line 8012 "parser_bison.c"
    break;

  case 22: /* close_scope_fib: %empty  */
#line 1008 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FIB); }
#line 8018 "parser_bison.c"
    break;

  case 23: /* close_scope_frag: %empty  */
#line 1009 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FRAG); }
#line 8024 "parser_bison.c"
    break;

  case 24: /* close_scope_fwd: %empty  */
#line 1010 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_FWD); }
#line 8030 "parser_bison.c"
    break;

  case 25: /* close_scope_gre: %empty  */
#line 1011 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_GRE); }
#line 8036 "parser_bison.c"
    break;

  case 26: /* close_scope_hash: %empty  */
#line 1012 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HASH); }
#line 8042 "parser_bison.c"
    break;

  case 27: /* close_scope_hbh: %empty  */
#line 1013 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HBH); }
#line 8048 "parser_bison.c"
    break;

  case 28: /* close_scope_ip: %empty  */
#line 1014 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP); }
#line 8054 "parser_bison.c"
    break;

  case 29: /* close_scope_ip6: %empty  */
#line 1015 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP6); }
#line 8060 "parser_bison.c"
    break;

  case 30: /* close_scope_vlan: %empty  */
#line 1016 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_VLAN); }
#line 8066 "parser_bison.c"
    break;

  case 31: /* close_scope_icmp: %empty  */
#line 1017 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_ICMP); }
#line 8072 "parser_bison.c"
    break;

  case 32: /* close_scope_igmp: %empty  */
#line 1018 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_IGMP); }
#line 8078 "parser_bison.c"
    break;

  case 33: /* close_scope_import: %empty  */
#line 1019 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_IMPORT); }
#line 8084 "parser_bison.c"
    break;

  case 34: /* close_scope_ipsec: %empty  */
#line 1020 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_IPSEC); }
#line 8090 "parser_bison.c"
    break;

  case 35: /* close_scope_list: %empty  */
#line 1021 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_LIST); }
#line 8096 "parser_bison.c"
    break;

  case 36: /* close_scope_limit: %empty  */
#line 1022 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_LIMIT); }
#line 8102 "parser_bison.c"
    break;

  case 37: /* close_scope_meta: %empty  */
#line 1023 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_META); }
#line 8108 "parser_bison.c"
    break;

  case 38: /* close_scope_mh: %empty  */
#line 1024 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_MH); }
#line 8114 "parser_bison.c"
    break;

  case 39: /* close_scope_monitor: %empty  */
#line 1025 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_MONITOR); }
#line 8120 "parser_bison.c"
    break;

  case 40: /* close_scope_nat: %empty  */
#line 1026 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_NAT); }
#line 8126 "parser_bison.c"
    break;

  case 41: /* close_scope_numgen: %empty  */
#line 1027 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_NUMGEN); }
#line 8132 "parser_bison.c"
    break;

  case 42: /* close_scope_osf: %empty  */
#line 1028 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_OSF); }
#line 8138 "parser_bison.c"
    break;

  case 43: /* close_scope_policy: %empty  */
#line 1029 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_POLICY); }
#line 8144 "parser_bison.c"
    break;

  case 44: /* close_scope_quota: %empty  */
#line 1030 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_QUOTA); }
#line 8150 "parser_bison.c"
    break;

  case 45: /* close_scope_queue: %empty  */
#line 1031 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_QUEUE); }
#line 8156 "parser_bison.c"
    break;

  case 46: /* close_scope_reject: %empty  */
#line 1032 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_REJECT); }
#line 8162 "parser_bison.c"
    break;

  case 47: /* close_scope_reset: %empty  */
#line 1033 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_RESET); }
#line 8168 "parser_bison.c"
    break;

  case 48: /* close_scope_rt: %empty  */
#line 1034 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_RT); }
#line 8174 "parser_bison.c"
    break;

  case 49: /* close_scope_sctp: %empty  */
#line 1035 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_SCTP); }
#line 8180 "parser_bison.c"
    break;

  case 50: /* close_scope_sctp_chunk: %empty  */
#line 1036 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SCTP_CHUNK); }
#line 8186 "parser_bison.c"
    break;

  case 51: /* close_scope_secmark: %empty  */
#line 1037 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_SECMARK); }
#line 8192 "parser_bison.c"
    break;

  case 52: /* close_scope_socket: %empty  */
#line 1038 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SOCKET); }
#line 8198 "parser_bison.c"
    break;

  case 53: /* close_scope_tcp: %empty  */
#line 1039 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_TCP); }
#line 8204 "parser_bison.c"
    break;

  case 54: /* close_scope_tproxy: %empty  */
#line 1040 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_TPROXY); }
#line 8210 "parser_bison.c"
    break;

  case 55: /* close_scope_type: %empty  */
#line 1041 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_TYPE); }
#line 8216 "parser_bison.c"
    break;

  case 56: /* close_scope_th: %empty  */
#line 1042 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_TH); }
#line 8222 "parser_bison.c"
    break;

  case 57: /* close_scope_udp: %empty  */
#line 1043 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_UDP); }
#line 8228 "parser_bison.c"
    break;

  case 58: /* close_scope_udplite: %empty  */
#line 1044 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_UDPLITE); }
#line 8234 "parser_bison.c"
    break;

  case 59: /* close_scope_log: %empty  */
#line 1046 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_LOG); }
#line 8240 "parser_bison.c"
    break;

  case 60: /* close_scope_synproxy: %empty  */
#line 1047 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_SYNPROXY); }
#line 8246 "parser_bison.c"
    break;

  case 61: /* close_scope_xt: %empty  */
#line 1048 "parser_bison.y"
                          { scanner_pop_start_cond(nft->scanner, PARSER_SC_XT); }
#line 8252 "parser_bison.c"
    break;

  case 62: /* common_block: "include" "quoted string" stmt_separator  */
#line 1051 "parser_bison.y"
                        {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 8264 "parser_bison.c"
    break;

  case 63: /* common_block: "define" identifier '=' initializer_expr stmt_separator  */
#line 1059 "parser_bison.y"
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
#line 8283 "parser_bison.c"
    break;

  case 64: /* common_block: "redefine" identifier '=' initializer_expr stmt_separator  */
#line 1074 "parser_bison.y"
                        {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 8294 "parser_bison.c"
    break;

  case 65: /* common_block: "undefine" identifier stmt_separator  */
#line 1081 "parser_bison.y"
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
#line 8310 "parser_bison.c"
    break;

  case 66: /* common_block: error stmt_separator  */
#line 1093 "parser_bison.y"
                        {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 8320 "parser_bison.c"
    break;

  case 67: /* line: common_block  */
#line 1100 "parser_bison.y"
                                                                { (yyval.cmd) = NULL; }
#line 8326 "parser_bison.c"
    break;

  case 68: /* line: stmt_separator  */
#line 1101 "parser_bison.y"
                                                                { (yyval.cmd) = NULL; }
#line 8332 "parser_bison.c"
    break;

  case 69: /* line: base_cmd stmt_separator  */
#line 1102 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8338 "parser_bison.c"
    break;

  case 70: /* line: base_cmd "end of file"  */
#line 1104 "parser_bison.y"
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
#line 8360 "parser_bison.c"
    break;

  case 71: /* base_cmd: add_cmd  */
#line 1123 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8366 "parser_bison.c"
    break;

  case 72: /* base_cmd: "add" add_cmd  */
#line 1124 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8372 "parser_bison.c"
    break;

  case 73: /* base_cmd: "replace" replace_cmd  */
#line 1125 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8378 "parser_bison.c"
    break;

  case 74: /* base_cmd: "create" create_cmd  */
#line 1126 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8384 "parser_bison.c"
    break;

  case 75: /* base_cmd: "insert" insert_cmd  */
#line 1127 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8390 "parser_bison.c"
    break;

  case 76: /* base_cmd: "delete" delete_cmd  */
#line 1128 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8396 "parser_bison.c"
    break;

  case 77: /* base_cmd: "get" get_cmd  */
#line 1129 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8402 "parser_bison.c"
    break;

  case 78: /* base_cmd: "list" list_cmd close_scope_list  */
#line 1130 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8408 "parser_bison.c"
    break;

  case 79: /* base_cmd: "reset" reset_cmd close_scope_reset  */
#line 1131 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8414 "parser_bison.c"
    break;

  case 80: /* base_cmd: "flush" flush_cmd  */
#line 1132 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8420 "parser_bison.c"
    break;

  case 81: /* base_cmd: "rename" rename_cmd  */
#line 1133 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8426 "parser_bison.c"
    break;

  case 82: /* base_cmd: "import" import_cmd close_scope_import  */
#line 1134 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8432 "parser_bison.c"
    break;

  case 83: /* base_cmd: "export" export_cmd close_scope_export  */
#line 1135 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8438 "parser_bison.c"
    break;

  case 84: /* base_cmd: "monitor" monitor_cmd close_scope_monitor  */
#line 1136 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8444 "parser_bison.c"
    break;

  case 85: /* base_cmd: "describe" describe_cmd  */
#line 1137 "parser_bison.y"
                                                                { (yyval.cmd) = (yyvsp[0].cmd); }
#line 8450 "parser_bison.c"
    break;

  case 86: /* base_cmd: "destroy" destroy_cmd close_scope_destroy  */
#line 1138 "parser_bison.y"
                                                                                        { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 8456 "parser_bison.c"
    break;

  case 87: /* add_cmd: "table" table_spec  */
#line 1142 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8464 "parser_bison.c"
    break;

  case 88: /* add_cmd: "table" table_spec table_block_alloc '{' table_block '}'  */
#line 1147 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 8474 "parser_bison.c"
    break;

  case 89: /* add_cmd: "chain" chain_spec  */
#line 1153 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8482 "parser_bison.c"
    break;

  case 90: /* add_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1158 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 8493 "parser_bison.c"
    break;

  case 91: /* add_cmd: "rule" rule_position rule  */
#line 1165 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8501 "parser_bison.c"
    break;

  case 92: /* add_cmd: rule_position rule  */
#line 1169 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8509 "parser_bison.c"
    break;

  case 93: /* add_cmd: "set" set_spec set_block_alloc '{' set_block '}'  */
#line 1174 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8519 "parser_bison.c"
    break;

  case 94: /* add_cmd: "map" set_spec map_block_alloc '{' map_block '}'  */
#line 1181 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8529 "parser_bison.c"
    break;

  case 95: /* add_cmd: "element" set_spec set_block_expr  */
#line 1187 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8537 "parser_bison.c"
    break;

  case 96: /* add_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1192 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8547 "parser_bison.c"
    break;

  case 97: /* add_cmd: "counter" obj_spec close_scope_counter  */
#line 1198 "parser_bison.y"
                        {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 8560 "parser_bison.c"
    break;

  case 98: /* add_cmd: "counter" obj_spec counter_obj counter_config close_scope_counter  */
#line 1207 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8568 "parser_bison.c"
    break;

  case 99: /* add_cmd: "counter" obj_spec counter_obj '{' counter_block '}' close_scope_counter  */
#line 1211 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8576 "parser_bison.c"
    break;

  case 100: /* add_cmd: "quota" obj_spec quota_obj quota_config close_scope_quota  */
#line 1215 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8584 "parser_bison.c"
    break;

  case 101: /* add_cmd: "quota" obj_spec quota_obj '{' quota_block '}' close_scope_quota  */
#line 1219 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8592 "parser_bison.c"
    break;

  case 102: /* add_cmd: "ct" "helper" obj_spec ct_obj_alloc '{' ct_helper_block '}' close_scope_ct  */
#line 1223 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8600 "parser_bison.c"
    break;

  case 103: /* add_cmd: "ct" "timeout" obj_spec ct_obj_alloc '{' ct_timeout_block '}' close_scope_ct  */
#line 1227 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8608 "parser_bison.c"
    break;

  case 104: /* add_cmd: "ct" "expectation" obj_spec ct_obj_alloc '{' ct_expect_block '}' close_scope_ct  */
#line 1231 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8616 "parser_bison.c"
    break;

  case 105: /* add_cmd: "limit" obj_spec limit_obj limit_config close_scope_limit  */
#line 1235 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8624 "parser_bison.c"
    break;

  case 106: /* add_cmd: "limit" obj_spec limit_obj '{' limit_block '}' close_scope_limit  */
#line 1239 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8632 "parser_bison.c"
    break;

  case 107: /* add_cmd: "secmark" obj_spec secmark_obj secmark_config close_scope_secmark  */
#line 1243 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8640 "parser_bison.c"
    break;

  case 108: /* add_cmd: "secmark" obj_spec secmark_obj '{' secmark_block '}' close_scope_secmark  */
#line 1247 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8648 "parser_bison.c"
    break;

  case 109: /* add_cmd: "synproxy" obj_spec synproxy_obj synproxy_config close_scope_synproxy  */
#line 1251 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8656 "parser_bison.c"
    break;

  case 110: /* add_cmd: "synproxy" obj_spec synproxy_obj '{' synproxy_block '}' close_scope_synproxy  */
#line 1255 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8664 "parser_bison.c"
    break;

  case 111: /* replace_cmd: "rule" ruleid_spec rule  */
#line 1261 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8672 "parser_bison.c"
    break;

  case 112: /* create_cmd: "table" table_spec  */
#line 1267 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8680 "parser_bison.c"
    break;

  case 113: /* create_cmd: "table" table_spec table_block_alloc '{' table_block '}'  */
#line 1272 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 8690 "parser_bison.c"
    break;

  case 114: /* create_cmd: "chain" chain_spec  */
#line 1278 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8698 "parser_bison.c"
    break;

  case 115: /* create_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1283 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 8709 "parser_bison.c"
    break;

  case 116: /* create_cmd: "set" set_spec set_block_alloc '{' set_block '}'  */
#line 1291 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8719 "parser_bison.c"
    break;

  case 117: /* create_cmd: "map" set_spec map_block_alloc '{' map_block '}'  */
#line 1298 "parser_bison.y"
                        {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 8729 "parser_bison.c"
    break;

  case 118: /* create_cmd: "element" set_spec set_block_expr  */
#line 1304 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8737 "parser_bison.c"
    break;

  case 119: /* create_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1309 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8747 "parser_bison.c"
    break;

  case 120: /* create_cmd: "counter" obj_spec close_scope_counter  */
#line 1315 "parser_bison.y"
                        {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 8760 "parser_bison.c"
    break;

  case 121: /* create_cmd: "counter" obj_spec counter_obj counter_config close_scope_counter  */
#line 1324 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8768 "parser_bison.c"
    break;

  case 122: /* create_cmd: "quota" obj_spec quota_obj quota_config close_scope_quota  */
#line 1328 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8776 "parser_bison.c"
    break;

  case 123: /* create_cmd: "ct" "helper" obj_spec ct_obj_alloc '{' ct_helper_block '}' close_scope_ct  */
#line 1332 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8784 "parser_bison.c"
    break;

  case 124: /* create_cmd: "ct" "timeout" obj_spec ct_obj_alloc '{' ct_timeout_block '}' close_scope_ct  */
#line 1336 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8792 "parser_bison.c"
    break;

  case 125: /* create_cmd: "ct" "expectation" obj_spec ct_obj_alloc '{' ct_expect_block '}' close_scope_ct  */
#line 1340 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 8800 "parser_bison.c"
    break;

  case 126: /* create_cmd: "limit" obj_spec limit_obj limit_config close_scope_limit  */
#line 1344 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8808 "parser_bison.c"
    break;

  case 127: /* create_cmd: "secmark" obj_spec secmark_obj secmark_config close_scope_secmark  */
#line 1348 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8816 "parser_bison.c"
    break;

  case 128: /* create_cmd: "synproxy" obj_spec synproxy_obj synproxy_config close_scope_synproxy  */
#line 1352 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 8824 "parser_bison.c"
    break;

  case 129: /* insert_cmd: "rule" rule_position rule  */
#line 1358 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 8832 "parser_bison.c"
    break;

  case 138: /* delete_cmd: "table" table_or_id_spec  */
#line 1380 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8840 "parser_bison.c"
    break;

  case 139: /* delete_cmd: "chain" chain_or_id_spec  */
#line 1384 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8848 "parser_bison.c"
    break;

  case 140: /* delete_cmd: "chain" chain_spec chain_block_alloc '{' chain_block '}'  */
#line 1389 "parser_bison.y"
                        {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 8858 "parser_bison.c"
    break;

  case 141: /* delete_cmd: "rule" ruleid_spec  */
#line 1395 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8866 "parser_bison.c"
    break;

  case 142: /* delete_cmd: "set" set_or_id_spec  */
#line 1399 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8874 "parser_bison.c"
    break;

  case 143: /* delete_cmd: "map" set_spec  */
#line 1403 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8882 "parser_bison.c"
    break;

  case 144: /* delete_cmd: "element" set_spec set_block_expr  */
#line 1407 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 8890 "parser_bison.c"
    break;

  case 145: /* delete_cmd: "flowtable" flowtable_spec  */
#line 1411 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8898 "parser_bison.c"
    break;

  case 146: /* delete_cmd: "flowtable" flowtableid_spec  */
#line 1415 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8906 "parser_bison.c"
    break;

  case 147: /* delete_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1420 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 8916 "parser_bison.c"
    break;

  case 148: /* delete_cmd: "counter" obj_or_id_spec close_scope_counter  */
#line 1426 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8924 "parser_bison.c"
    break;

  case 149: /* delete_cmd: "quota" obj_or_id_spec close_scope_quota  */
#line 1430 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8932 "parser_bison.c"
    break;

  case 150: /* delete_cmd: "ct" ct_obj_type obj_spec ct_obj_alloc close_scope_ct  */
#line 1434 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-3].val), &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
				if ((yyvsp[-3].val) == NFT_OBJECT_CT_TIMEOUT)
					init_list_head(&(yyvsp[-1].obj)->ct_timeout.timeout_list);
			}
#line 8942 "parser_bison.c"
    break;

  case 151: /* delete_cmd: "limit" obj_or_id_spec close_scope_limit  */
#line 1440 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8950 "parser_bison.c"
    break;

  case 152: /* delete_cmd: "secmark" obj_or_id_spec close_scope_secmark  */
#line 1444 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8958 "parser_bison.c"
    break;

  case 153: /* delete_cmd: "synproxy" obj_or_id_spec close_scope_synproxy  */
#line 1448 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 8966 "parser_bison.c"
    break;

  case 154: /* destroy_cmd: "table" table_or_id_spec  */
#line 1454 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8974 "parser_bison.c"
    break;

  case 155: /* destroy_cmd: "chain" chain_or_id_spec  */
#line 1458 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8982 "parser_bison.c"
    break;

  case 156: /* destroy_cmd: "rule" ruleid_spec  */
#line 1462 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8990 "parser_bison.c"
    break;

  case 157: /* destroy_cmd: "set" set_or_id_spec  */
#line 1466 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 8998 "parser_bison.c"
    break;

  case 158: /* destroy_cmd: "map" set_spec  */
#line 1470 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9006 "parser_bison.c"
    break;

  case 159: /* destroy_cmd: "element" set_spec set_block_expr  */
#line 1474 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 9014 "parser_bison.c"
    break;

  case 160: /* destroy_cmd: "flowtable" flowtable_spec  */
#line 1478 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9022 "parser_bison.c"
    break;

  case 161: /* destroy_cmd: "flowtable" flowtableid_spec  */
#line 1482 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9030 "parser_bison.c"
    break;

  case 162: /* destroy_cmd: "flowtable" flowtable_spec flowtable_block_alloc '{' flowtable_block '}'  */
#line 1487 "parser_bison.y"
                        {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 9040 "parser_bison.c"
    break;

  case 163: /* destroy_cmd: "counter" obj_or_id_spec close_scope_counter  */
#line 1493 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9048 "parser_bison.c"
    break;

  case 164: /* destroy_cmd: "quota" obj_or_id_spec close_scope_quota  */
#line 1497 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9056 "parser_bison.c"
    break;

  case 165: /* destroy_cmd: "ct" ct_obj_type obj_spec ct_obj_alloc close_scope_ct  */
#line 1501 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DESTROY, (yyvsp[-3].val), &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
				if ((yyvsp[-3].val) == NFT_OBJECT_CT_TIMEOUT)
					init_list_head(&(yyvsp[-1].obj)->ct_timeout.timeout_list);
			}
#line 9066 "parser_bison.c"
    break;

  case 166: /* destroy_cmd: "limit" obj_or_id_spec close_scope_limit  */
#line 1507 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9074 "parser_bison.c"
    break;

  case 167: /* destroy_cmd: "secmark" obj_or_id_spec close_scope_secmark  */
#line 1511 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9082 "parser_bison.c"
    break;

  case 168: /* destroy_cmd: "synproxy" obj_or_id_spec close_scope_synproxy  */
#line 1515 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_DESTROY, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9090 "parser_bison.c"
    break;

  case 169: /* get_cmd: "element" set_spec set_block_expr  */
#line 1522 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 9098 "parser_bison.c"
    break;

  case 170: /* list_cmd: "table" table_spec  */
#line 1528 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9106 "parser_bison.c"
    break;

  case 171: /* list_cmd: "tables" ruleset_spec  */
#line 1532 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9114 "parser_bison.c"
    break;

  case 172: /* list_cmd: "chain" chain_spec  */
#line 1536 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9122 "parser_bison.c"
    break;

  case 173: /* list_cmd: "chains" ruleset_spec  */
#line 1540 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9130 "parser_bison.c"
    break;

  case 174: /* list_cmd: "sets" ruleset_spec  */
#line 1544 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9138 "parser_bison.c"
    break;

  case 175: /* list_cmd: "sets" "table" table_spec  */
#line 1548 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9146 "parser_bison.c"
    break;

  case 176: /* list_cmd: "set" set_spec  */
#line 1552 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9154 "parser_bison.c"
    break;

  case 177: /* list_cmd: "counters" ruleset_spec  */
#line 1556 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9162 "parser_bison.c"
    break;

  case 178: /* list_cmd: "counters" "table" table_spec  */
#line 1560 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9170 "parser_bison.c"
    break;

  case 179: /* list_cmd: "counter" obj_spec close_scope_counter  */
#line 1564 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9178 "parser_bison.c"
    break;

  case 180: /* list_cmd: "quotas" ruleset_spec  */
#line 1568 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9186 "parser_bison.c"
    break;

  case 181: /* list_cmd: "quotas" "table" table_spec  */
#line 1572 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9194 "parser_bison.c"
    break;

  case 182: /* list_cmd: "quota" obj_spec close_scope_quota  */
#line 1576 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9202 "parser_bison.c"
    break;

  case 183: /* list_cmd: "limits" ruleset_spec  */
#line 1580 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9210 "parser_bison.c"
    break;

  case 184: /* list_cmd: "limits" "table" table_spec  */
#line 1584 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9218 "parser_bison.c"
    break;

  case 185: /* list_cmd: "limit" obj_spec close_scope_limit  */
#line 1588 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9226 "parser_bison.c"
    break;

  case 186: /* list_cmd: "secmarks" ruleset_spec  */
#line 1592 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9234 "parser_bison.c"
    break;

  case 187: /* list_cmd: "secmarks" "table" table_spec  */
#line 1596 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9242 "parser_bison.c"
    break;

  case 188: /* list_cmd: "secmark" obj_spec close_scope_secmark  */
#line 1600 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9250 "parser_bison.c"
    break;

  case 189: /* list_cmd: "synproxys" ruleset_spec  */
#line 1604 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9258 "parser_bison.c"
    break;

  case 190: /* list_cmd: "synproxys" "table" table_spec  */
#line 1608 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9266 "parser_bison.c"
    break;

  case 191: /* list_cmd: "synproxy" obj_spec close_scope_synproxy  */
#line 1612 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9274 "parser_bison.c"
    break;

  case 192: /* list_cmd: "ruleset" ruleset_spec  */
#line 1616 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9282 "parser_bison.c"
    break;

  case 193: /* list_cmd: "flow" "tables" ruleset_spec  */
#line 1620 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9290 "parser_bison.c"
    break;

  case 194: /* list_cmd: "flow" "table" set_spec  */
#line 1624 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9298 "parser_bison.c"
    break;

  case 195: /* list_cmd: "meters" ruleset_spec  */
#line 1628 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9306 "parser_bison.c"
    break;

  case 196: /* list_cmd: "meter" set_spec  */
#line 1632 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9314 "parser_bison.c"
    break;

  case 197: /* list_cmd: "flowtables" ruleset_spec  */
#line 1636 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9322 "parser_bison.c"
    break;

  case 198: /* list_cmd: "flowtable" flowtable_spec  */
#line 1640 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9330 "parser_bison.c"
    break;

  case 199: /* list_cmd: "maps" ruleset_spec  */
#line 1644 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9338 "parser_bison.c"
    break;

  case 200: /* list_cmd: "map" set_spec  */
#line 1648 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9346 "parser_bison.c"
    break;

  case 201: /* list_cmd: "ct" ct_obj_type obj_spec close_scope_ct  */
#line 1652 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9354 "parser_bison.c"
    break;

  case 202: /* list_cmd: "ct" ct_cmd_type "table" table_spec close_scope_ct  */
#line 1656 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, (yyvsp[-3].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9362 "parser_bison.c"
    break;

  case 203: /* list_cmd: "hooks" basehook_spec  */
#line 1660 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_HOOKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9370 "parser_bison.c"
    break;

  case 204: /* basehook_device_name: "device" "string"  */
#line 1666 "parser_bison.y"
                        {
				(yyval.string) = (yyvsp[0].string);
			}
#line 9378 "parser_bison.c"
    break;

  case 205: /* basehook_spec: ruleset_spec  */
#line 1672 "parser_bison.y"
                        {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 9386 "parser_bison.c"
    break;

  case 206: /* basehook_spec: ruleset_spec basehook_device_name  */
#line 1676 "parser_bison.y"
                        {
				if ((yyvsp[0].string)) {
					(yyvsp[-1].handle).obj.name = (yyvsp[0].string);
					(yyvsp[-1].handle).obj.location = (yylsp[0]);
				}
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9398 "parser_bison.c"
    break;

  case 207: /* reset_cmd: "counters" ruleset_spec  */
#line 1686 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9406 "parser_bison.c"
    break;

  case 208: /* reset_cmd: "counters" table_spec  */
#line 1690 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9414 "parser_bison.c"
    break;

  case 209: /* reset_cmd: "counters" "table" table_spec  */
#line 1694 "parser_bison.y"
                        {
				/* alias of previous rule. */
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9423 "parser_bison.c"
    break;

  case 210: /* reset_cmd: "counter" obj_spec close_scope_counter  */
#line 1699 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[-1].handle),&(yyloc), NULL);
			}
#line 9431 "parser_bison.c"
    break;

  case 211: /* reset_cmd: "quotas" ruleset_spec  */
#line 1703 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9439 "parser_bison.c"
    break;

  case 212: /* reset_cmd: "quotas" "table" table_spec  */
#line 1707 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9447 "parser_bison.c"
    break;

  case 213: /* reset_cmd: "quotas" table_spec  */
#line 1711 "parser_bison.y"
                        {
				/* alias of previous rule. */
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9456 "parser_bison.c"
    break;

  case 214: /* reset_cmd: "quota" obj_spec close_scope_quota  */
#line 1716 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 9464 "parser_bison.c"
    break;

  case 215: /* reset_cmd: "rules" ruleset_spec  */
#line 1720 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9472 "parser_bison.c"
    break;

  case 216: /* reset_cmd: "rules" table_spec  */
#line 1724 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9480 "parser_bison.c"
    break;

  case 217: /* reset_cmd: "rules" "table" table_spec  */
#line 1728 "parser_bison.y"
                        {
				/* alias of previous rule. */
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9489 "parser_bison.c"
    break;

  case 218: /* reset_cmd: "rules" chain_spec  */
#line 1733 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9497 "parser_bison.c"
    break;

  case 219: /* reset_cmd: "rules" "chain" chain_spec  */
#line 1737 "parser_bison.y"
                        {
				/* alias of previous rule. */
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9506 "parser_bison.c"
    break;

  case 220: /* reset_cmd: "rule" ruleid_spec  */
#line 1742 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9514 "parser_bison.c"
    break;

  case 221: /* reset_cmd: "element" set_spec set_block_expr  */
#line 1746 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 9522 "parser_bison.c"
    break;

  case 222: /* reset_cmd: "set" set_or_id_spec  */
#line 1750 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9530 "parser_bison.c"
    break;

  case 223: /* reset_cmd: "map" set_or_id_spec  */
#line 1754 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9538 "parser_bison.c"
    break;

  case 224: /* flush_cmd: "table" table_spec  */
#line 1760 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9546 "parser_bison.c"
    break;

  case 225: /* flush_cmd: "chain" chain_spec  */
#line 1764 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9554 "parser_bison.c"
    break;

  case 226: /* flush_cmd: "set" set_spec  */
#line 1768 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9562 "parser_bison.c"
    break;

  case 227: /* flush_cmd: "map" set_spec  */
#line 1772 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9570 "parser_bison.c"
    break;

  case 228: /* flush_cmd: "flow" "table" set_spec  */
#line 1776 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9578 "parser_bison.c"
    break;

  case 229: /* flush_cmd: "meter" set_spec  */
#line 1780 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9586 "parser_bison.c"
    break;

  case 230: /* flush_cmd: "ruleset" ruleset_spec  */
#line 1784 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 9594 "parser_bison.c"
    break;

  case 231: /* rename_cmd: "chain" chain_spec identifier  */
#line 1790 "parser_bison.y"
                        {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 9603 "parser_bison.c"
    break;

  case 232: /* import_cmd: "ruleset" markup_format  */
#line 1797 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9613 "parser_bison.c"
    break;

  case 233: /* import_cmd: markup_format  */
#line 1803 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9623 "parser_bison.c"
    break;

  case 234: /* export_cmd: "ruleset" markup_format  */
#line 1811 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9633 "parser_bison.c"
    break;

  case 235: /* export_cmd: markup_format  */
#line 1817 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 9643 "parser_bison.c"
    break;

  case 236: /* monitor_cmd: monitor_event monitor_object monitor_format  */
#line 1825 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 9654 "parser_bison.c"
    break;

  case 237: /* monitor_event: %empty  */
#line 1833 "parser_bison.y"
                                                { (yyval.string) = NULL; }
#line 9660 "parser_bison.c"
    break;

  case 238: /* monitor_event: "string"  */
#line 1834 "parser_bison.y"
                                                { (yyval.string) = (yyvsp[0].string); }
#line 9666 "parser_bison.c"
    break;

  case 239: /* monitor_object: %empty  */
#line 1837 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 9672 "parser_bison.c"
    break;

  case 240: /* monitor_object: "tables"  */
#line 1838 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 9678 "parser_bison.c"
    break;

  case 241: /* monitor_object: "chains"  */
#line 1839 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 9684 "parser_bison.c"
    break;

  case 242: /* monitor_object: "sets"  */
#line 1840 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 9690 "parser_bison.c"
    break;

  case 243: /* monitor_object: "rules"  */
#line 1841 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 9696 "parser_bison.c"
    break;

  case 244: /* monitor_object: "elements"  */
#line 1842 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 9702 "parser_bison.c"
    break;

  case 245: /* monitor_object: "ruleset"  */
#line 1843 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 9708 "parser_bison.c"
    break;

  case 246: /* monitor_object: "trace"  */
#line 1844 "parser_bison.y"
                                                { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 9714 "parser_bison.c"
    break;

  case 247: /* monitor_format: %empty  */
#line 1847 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 9720 "parser_bison.c"
    break;

  case 249: /* markup_format: "xml"  */
#line 1851 "parser_bison.y"
                                                { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 9726 "parser_bison.c"
    break;

  case 250: /* markup_format: "json"  */
#line 1852 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 9732 "parser_bison.c"
    break;

  case 251: /* markup_format: "vm" "json"  */
#line 1853 "parser_bison.y"
                                                { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 9738 "parser_bison.c"
    break;

  case 252: /* describe_cmd: primary_expr  */
#line 1857 "parser_bison.y"
                        {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 9748 "parser_bison.c"
    break;

  case 253: /* table_block_alloc: %empty  */
#line 1865 "parser_bison.y"
                        {
				(yyval.table) = table_alloc();
				if (open_scope(state, &(yyval.table)->scope) < 0) {
					erec_queue(error(&(yyloc), "too many levels of nesting"),
						   state->msgs);
					state->nerrs++;
				}
			}
#line 9761 "parser_bison.c"
    break;

  case 254: /* table_options: "flags" "string"  */
#line 1876 "parser_bison.y"
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
#line 9780 "parser_bison.c"
    break;

  case 255: /* table_options: comment_spec  */
#line 1891 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].table)->comment, &(yyloc), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].table)->comment = (yyvsp[0].string);
			}
#line 9792 "parser_bison.c"
    break;

  case 256: /* table_block: %empty  */
#line 1900 "parser_bison.y"
                                                { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 9798 "parser_bison.c"
    break;

  case 260: /* table_block: table_block "chain" chain_identifier chain_block_alloc '{' chain_block '}' stmt_separator  */
#line 1907 "parser_bison.y"
                        {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9811 "parser_bison.c"
    break;

  case 261: /* table_block: table_block "set" set_identifier set_block_alloc '{' set_block '}' stmt_separator  */
#line 1918 "parser_bison.y"
                        {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9823 "parser_bison.c"
    break;

  case 262: /* table_block: table_block "map" set_identifier map_block_alloc '{' map_block '}' stmt_separator  */
#line 1928 "parser_bison.y"
                        {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9835 "parser_bison.c"
    break;

  case 263: /* table_block: table_block "flowtable" flowtable_identifier flowtable_block_alloc '{' flowtable_block '}' stmt_separator  */
#line 1939 "parser_bison.y"
                        {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 9847 "parser_bison.c"
    break;

  case 264: /* table_block: table_block "counter" obj_identifier obj_block_alloc '{' counter_block '}' stmt_separator close_scope_counter  */
#line 1949 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9860 "parser_bison.c"
    break;

  case 265: /* table_block: table_block "quota" obj_identifier obj_block_alloc '{' quota_block '}' stmt_separator close_scope_quota  */
#line 1960 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9873 "parser_bison.c"
    break;

  case 266: /* table_block: table_block "ct" "helper" obj_identifier obj_block_alloc '{' ct_helper_block '}' close_scope_ct stmt_separator  */
#line 1969 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9886 "parser_bison.c"
    break;

  case 267: /* table_block: table_block "ct" "timeout" obj_identifier obj_block_alloc '{' ct_timeout_block '}' close_scope_ct stmt_separator  */
#line 1978 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9899 "parser_bison.c"
    break;

  case 268: /* table_block: table_block "ct" "expectation" obj_identifier obj_block_alloc '{' ct_expect_block '}' close_scope_ct stmt_separator  */
#line 1987 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 9912 "parser_bison.c"
    break;

  case 269: /* table_block: table_block "limit" obj_identifier obj_block_alloc '{' limit_block '}' stmt_separator close_scope_limit  */
#line 1998 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9925 "parser_bison.c"
    break;

  case 270: /* table_block: table_block "secmark" obj_identifier obj_block_alloc '{' secmark_block '}' stmt_separator close_scope_secmark  */
#line 2009 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9938 "parser_bison.c"
    break;

  case 271: /* table_block: table_block "synproxy" obj_identifier obj_block_alloc '{' synproxy_block '}' stmt_separator close_scope_synproxy  */
#line 2020 "parser_bison.y"
                        {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 9951 "parser_bison.c"
    break;

  case 272: /* chain_block_alloc: %empty  */
#line 2031 "parser_bison.y"
                        {
				(yyval.chain) = chain_alloc(NULL);
				if (open_scope(state, &(yyval.chain)->scope) < 0) {
					erec_queue(error(&(yyloc), "too many levels of nesting"),
						   state->msgs);
					state->nerrs++;
				}
			}
#line 9964 "parser_bison.c"
    break;

  case 273: /* chain_block: %empty  */
#line 2041 "parser_bison.y"
                                                { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 9970 "parser_bison.c"
    break;

  case 279: /* chain_block: chain_block rule stmt_separator  */
#line 2048 "parser_bison.y"
                        {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 9979 "parser_bison.c"
    break;

  case 280: /* chain_block: chain_block "devices" '=' flowtable_expr stmt_separator  */
#line 2053 "parser_bison.y"
                        {
				if ((yyval.chain)->dev_expr) {
					list_splice_init(&(yyvsp[-1].expr)->expressions, &(yyval.chain)->dev_expr->expressions);
					expr_free((yyvsp[-1].expr));
					break;
				}
				(yyval.chain)->dev_expr = (yyvsp[-1].expr);
			}
#line 9992 "parser_bison.c"
    break;

  case 281: /* chain_block: chain_block comment_spec stmt_separator  */
#line 2062 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].chain)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].chain)->comment = (yyvsp[-1].string);
			}
#line 10004 "parser_bison.c"
    break;

  case 282: /* subchain_block: %empty  */
#line 2071 "parser_bison.y"
                                                { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 10010 "parser_bison.c"
    break;

  case 284: /* subchain_block: subchain_block rule stmt_separator  */
#line 2074 "parser_bison.y"
                        {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 10019 "parser_bison.c"
    break;

  case 285: /* typeof_data_expr: primary_expr  */
#line 2081 "parser_bison.y"
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
#line 10044 "parser_bison.c"
    break;

  case 286: /* typeof_data_expr: typeof_expr "." primary_expr  */
#line 2102 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10057 "parser_bison.c"
    break;

  case 287: /* typeof_expr: primary_expr  */
#line 2113 "parser_bison.y"
                        {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10072 "parser_bison.c"
    break;

  case 288: /* typeof_expr: typeof_expr "." primary_expr  */
#line 2124 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10085 "parser_bison.c"
    break;

  case 289: /* set_block_alloc: %empty  */
#line 2136 "parser_bison.y"
                        {
				(yyval.set) = set_alloc(NULL);
			}
#line 10093 "parser_bison.c"
    break;

  case 290: /* set_block: %empty  */
#line 2141 "parser_bison.y"
                                                { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 10099 "parser_bison.c"
    break;

  case 293: /* set_block: set_block "type" data_type_expr stmt_separator close_scope_type  */
#line 2145 "parser_bison.y"
                        {
				(yyvsp[-4].set)->key = (yyvsp[-2].expr);
				(yyval.set) = (yyvsp[-4].set);
			}
#line 10108 "parser_bison.c"
    break;

  case 294: /* set_block: set_block "typeof" typeof_expr stmt_separator  */
#line 2150 "parser_bison.y"
                        {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10118 "parser_bison.c"
    break;

  case 295: /* set_block: set_block "flags" set_flag_list stmt_separator  */
#line 2156 "parser_bison.y"
                        {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10127 "parser_bison.c"
    break;

  case 296: /* set_block: set_block "timeout" time_spec stmt_separator  */
#line 2161 "parser_bison.y"
                        {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10136 "parser_bison.c"
    break;

  case 297: /* set_block: set_block "gc-interval" time_spec stmt_separator  */
#line 2166 "parser_bison.y"
                        {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10145 "parser_bison.c"
    break;

  case 298: /* set_block: set_block stateful_stmt_list stmt_separator  */
#line 2171 "parser_bison.y"
                        {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 10155 "parser_bison.c"
    break;

  case 299: /* set_block: set_block "elements" '=' set_block_expr  */
#line 2177 "parser_bison.y"
                        {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10164 "parser_bison.c"
    break;

  case 300: /* set_block: set_block "auto-merge"  */
#line 2182 "parser_bison.y"
                        {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 10173 "parser_bison.c"
    break;

  case 302: /* set_block: set_block comment_spec stmt_separator  */
#line 2188 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 10186 "parser_bison.c"
    break;

  case 305: /* set_flag_list: set_flag_list "comma" set_flag  */
#line 2203 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10194 "parser_bison.c"
    break;

  case 307: /* set_flag: "constant"  */
#line 2209 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_CONSTANT; }
#line 10200 "parser_bison.c"
    break;

  case 308: /* set_flag: "interval"  */
#line 2210 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_INTERVAL; }
#line 10206 "parser_bison.c"
    break;

  case 309: /* set_flag: "timeout"  */
#line 2211 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_TIMEOUT; }
#line 10212 "parser_bison.c"
    break;

  case 310: /* set_flag: "dynamic"  */
#line 2212 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_EVAL; }
#line 10218 "parser_bison.c"
    break;

  case 311: /* map_block_alloc: %empty  */
#line 2216 "parser_bison.y"
                        {
				(yyval.set) = set_alloc(NULL);
			}
#line 10226 "parser_bison.c"
    break;

  case 312: /* map_block_obj_type: "counter" close_scope_counter  */
#line 2221 "parser_bison.y"
                                                            { (yyval.val) = NFT_OBJECT_COUNTER; }
#line 10232 "parser_bison.c"
    break;

  case 313: /* map_block_obj_type: "quota" close_scope_quota  */
#line 2222 "parser_bison.y"
                                                          { (yyval.val) = NFT_OBJECT_QUOTA; }
#line 10238 "parser_bison.c"
    break;

  case 314: /* map_block_obj_type: "limit" close_scope_limit  */
#line 2223 "parser_bison.y"
                                                          { (yyval.val) = NFT_OBJECT_LIMIT; }
#line 10244 "parser_bison.c"
    break;

  case 315: /* map_block_obj_type: "secmark" close_scope_secmark  */
#line 2224 "parser_bison.y"
                                                            { (yyval.val) = NFT_OBJECT_SECMARK; }
#line 10250 "parser_bison.c"
    break;

  case 316: /* map_block_obj_type: "synproxy" close_scope_synproxy  */
#line 2225 "parser_bison.y"
                                                              { (yyval.val) = NFT_OBJECT_SYNPROXY; }
#line 10256 "parser_bison.c"
    break;

  case 317: /* map_block: %empty  */
#line 2228 "parser_bison.y"
                                                { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 10262 "parser_bison.c"
    break;

  case 320: /* map_block: map_block "timeout" time_spec stmt_separator  */
#line 2232 "parser_bison.y"
                        {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10271 "parser_bison.c"
    break;

  case 321: /* map_block: map_block "type" data_type_expr "colon" data_type_expr stmt_separator close_scope_type  */
#line 2239 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->data = (yyvsp[-2].expr);

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 10283 "parser_bison.c"
    break;

  case 322: /* map_block: map_block "type" data_type_expr "colon" "interval" data_type_expr stmt_separator close_scope_type  */
#line 2249 "parser_bison.y"
                        {
				(yyvsp[-7].set)->key = (yyvsp[-5].expr);
				(yyvsp[-7].set)->data = (yyvsp[-2].expr);
				(yyvsp[-7].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-7].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-7].set);
			}
#line 10296 "parser_bison.c"
    break;

  case 323: /* map_block: map_block "typeof" typeof_expr "colon" typeof_data_expr stmt_separator  */
#line 2260 "parser_bison.y"
                        {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 10309 "parser_bison.c"
    break;

  case 324: /* map_block: map_block "typeof" typeof_expr "colon" "interval" typeof_expr stmt_separator  */
#line 2271 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				datatype_set((yyvsp[-6].set)->key, (yyvsp[-4].expr)->dtype);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 10323 "parser_bison.c"
    break;

  case 325: /* map_block: map_block "type" data_type_expr "colon" map_block_obj_type stmt_separator close_scope_type  */
#line 2283 "parser_bison.y"
                        {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->objtype = (yyvsp[-2].val);
				(yyvsp[-6].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 10334 "parser_bison.c"
    break;

  case 326: /* map_block: map_block "flags" set_flag_list stmt_separator  */
#line 2290 "parser_bison.y"
                        {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10343 "parser_bison.c"
    break;

  case 327: /* map_block: map_block stateful_stmt_list stmt_separator  */
#line 2295 "parser_bison.y"
                        {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 10353 "parser_bison.c"
    break;

  case 328: /* map_block: map_block "elements" '=' set_block_expr  */
#line 2301 "parser_bison.y"
                        {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 10362 "parser_bison.c"
    break;

  case 329: /* map_block: map_block comment_spec stmt_separator  */
#line 2306 "parser_bison.y"
                        {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 10375 "parser_bison.c"
    break;

  case 331: /* set_mechanism: "policy" set_policy_spec close_scope_policy  */
#line 2318 "parser_bison.y"
                        {
				(yyvsp[-3].set)->policy = (yyvsp[-1].val);
			}
#line 10383 "parser_bison.c"
    break;

  case 332: /* set_mechanism: "size" "number"  */
#line 2322 "parser_bison.y"
                        {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 10391 "parser_bison.c"
    break;

  case 333: /* set_policy_spec: "performance"  */
#line 2327 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 10397 "parser_bison.c"
    break;

  case 334: /* set_policy_spec: "memory"  */
#line 2328 "parser_bison.y"
                                                { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 10403 "parser_bison.c"
    break;

  case 335: /* flowtable_block_alloc: %empty  */
#line 2332 "parser_bison.y"
                        {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 10411 "parser_bison.c"
    break;

  case 336: /* flowtable_block: %empty  */
#line 2337 "parser_bison.y"
                                                { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 10417 "parser_bison.c"
    break;

  case 339: /* flowtable_block: flowtable_block "hook" "string" prio_spec stmt_separator  */
#line 2341 "parser_bison.y"
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
#line 10435 "parser_bison.c"
    break;

  case 340: /* flowtable_block: flowtable_block "devices" '=' flowtable_expr stmt_separator  */
#line 2355 "parser_bison.y"
                        {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 10443 "parser_bison.c"
    break;

  case 341: /* flowtable_block: flowtable_block "counter" close_scope_counter  */
#line 2359 "parser_bison.y"
                        {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 10451 "parser_bison.c"
    break;

  case 342: /* flowtable_block: flowtable_block "flags" "offload" stmt_separator  */
#line 2363 "parser_bison.y"
                        {
				(yyval.flowtable)->flags |= FLOWTABLE_F_HW_OFFLOAD;
			}
#line 10459 "parser_bison.c"
    break;

  case 343: /* flowtable_expr: '{' flowtable_list_expr '}'  */
#line 2369 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10468 "parser_bison.c"
    break;

  case 344: /* flowtable_expr: variable_expr  */
#line 2374 "parser_bison.y"
                        {
				(yyvsp[0].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10477 "parser_bison.c"
    break;

  case 345: /* flowtable_list_expr: flowtable_expr_member  */
#line 2381 "parser_bison.y"
                        {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10486 "parser_bison.c"
    break;

  case 346: /* flowtable_list_expr: flowtable_list_expr "comma" flowtable_expr_member  */
#line 2386 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10495 "parser_bison.c"
    break;

  case 348: /* flowtable_expr_member: "quoted string"  */
#line 2394 "parser_bison.y"
                        {
				struct expr *expr = ifname_expr_alloc(&(yyloc), state->msgs, (yyvsp[0].string));

				if (!expr)
					YYERROR;

				(yyval.expr) = expr;
			}
#line 10508 "parser_bison.c"
    break;

  case 349: /* flowtable_expr_member: "string"  */
#line 2403 "parser_bison.y"
                        {
				struct expr *expr = ifname_expr_alloc(&(yyloc), state->msgs, (yyvsp[0].string));

				if (!expr)
					YYERROR;

				(yyval.expr) = expr;
			}
#line 10521 "parser_bison.c"
    break;

  case 350: /* flowtable_expr_member: variable_expr  */
#line 2412 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10530 "parser_bison.c"
    break;

  case 351: /* data_type_atom_expr: type_identifier  */
#line 2419 "parser_bison.y"
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
#line 10547 "parser_bison.c"
    break;

  case 352: /* data_type_atom_expr: "time"  */
#line 2432 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 10556 "parser_bison.c"
    break;

  case 354: /* data_type_expr: data_type_expr "." data_type_atom_expr  */
#line 2440 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10569 "parser_bison.c"
    break;

  case 355: /* obj_block_alloc: %empty  */
#line 2451 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 10577 "parser_bison.c"
    break;

  case 356: /* counter_block: %empty  */
#line 2456 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10583 "parser_bison.c"
    break;

  case 359: /* counter_block: counter_block counter_config  */
#line 2460 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10591 "parser_bison.c"
    break;

  case 360: /* counter_block: counter_block comment_spec  */
#line 2464 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10603 "parser_bison.c"
    break;

  case 361: /* quota_block: %empty  */
#line 2473 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10609 "parser_bison.c"
    break;

  case 364: /* quota_block: quota_block quota_config  */
#line 2477 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10617 "parser_bison.c"
    break;

  case 365: /* quota_block: quota_block comment_spec  */
#line 2481 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10629 "parser_bison.c"
    break;

  case 366: /* ct_helper_block: %empty  */
#line 2490 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10635 "parser_bison.c"
    break;

  case 369: /* ct_helper_block: ct_helper_block ct_helper_config  */
#line 2494 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10643 "parser_bison.c"
    break;

  case 370: /* ct_helper_block: ct_helper_block comment_spec  */
#line 2498 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10655 "parser_bison.c"
    break;

  case 371: /* ct_timeout_block: %empty  */
#line 2508 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[(-1) - (0)].obj);
				init_list_head(&(yyval.obj)->ct_timeout.timeout_list);
			}
#line 10664 "parser_bison.c"
    break;

  case 374: /* ct_timeout_block: ct_timeout_block ct_timeout_config  */
#line 2515 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10672 "parser_bison.c"
    break;

  case 375: /* ct_timeout_block: ct_timeout_block comment_spec  */
#line 2519 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10684 "parser_bison.c"
    break;

  case 376: /* ct_expect_block: %empty  */
#line 2528 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10690 "parser_bison.c"
    break;

  case 379: /* ct_expect_block: ct_expect_block ct_expect_config  */
#line 2532 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10698 "parser_bison.c"
    break;

  case 380: /* ct_expect_block: ct_expect_block comment_spec  */
#line 2536 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10710 "parser_bison.c"
    break;

  case 381: /* limit_block: %empty  */
#line 2545 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10716 "parser_bison.c"
    break;

  case 384: /* limit_block: limit_block limit_config  */
#line 2549 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10724 "parser_bison.c"
    break;

  case 385: /* limit_block: limit_block comment_spec  */
#line 2553 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10736 "parser_bison.c"
    break;

  case 386: /* secmark_block: %empty  */
#line 2562 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10742 "parser_bison.c"
    break;

  case 389: /* secmark_block: secmark_block secmark_config  */
#line 2566 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10750 "parser_bison.c"
    break;

  case 390: /* secmark_block: secmark_block comment_spec  */
#line 2570 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10762 "parser_bison.c"
    break;

  case 391: /* synproxy_block: %empty  */
#line 2579 "parser_bison.y"
                                                { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 10768 "parser_bison.c"
    break;

  case 394: /* synproxy_block: synproxy_block synproxy_config  */
#line 2583 "parser_bison.y"
                        {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 10776 "parser_bison.c"
    break;

  case 395: /* synproxy_block: synproxy_block comment_spec  */
#line 2587 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 10788 "parser_bison.c"
    break;

  case 396: /* type_identifier: "string"  */
#line 2596 "parser_bison.y"
                                        { (yyval.string) = (yyvsp[0].string); }
#line 10794 "parser_bison.c"
    break;

  case 397: /* type_identifier: "mark"  */
#line 2597 "parser_bison.y"
                                        { (yyval.string) = xstrdup("mark"); }
#line 10800 "parser_bison.c"
    break;

  case 398: /* type_identifier: "dscp"  */
#line 2598 "parser_bison.y"
                                        { (yyval.string) = xstrdup("dscp"); }
#line 10806 "parser_bison.c"
    break;

  case 399: /* type_identifier: "ecn"  */
#line 2599 "parser_bison.y"
                                        { (yyval.string) = xstrdup("ecn"); }
#line 10812 "parser_bison.c"
    break;

  case 400: /* type_identifier: "classid"  */
#line 2600 "parser_bison.y"
                                        { (yyval.string) = xstrdup("classid"); }
#line 10818 "parser_bison.c"
    break;

  case 401: /* hook_spec: "type" close_scope_type "string" "hook" "string" dev_spec prio_spec  */
#line 2604 "parser_bison.y"
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
#line 10851 "parser_bison.c"
    break;

  case 402: /* prio_spec: "priority" extended_prio_spec  */
#line 2635 "parser_bison.y"
                        {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 10860 "parser_bison.c"
    break;

  case 403: /* extended_prio_name: "out"  */
#line 2642 "parser_bison.y"
                        {
				(yyval.string) = strdup("out");
			}
#line 10868 "parser_bison.c"
    break;

  case 405: /* extended_prio_spec: int_num  */
#line 2649 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 10882 "parser_bison.c"
    break;

  case 406: /* extended_prio_spec: variable_expr  */
#line 2659 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 10893 "parser_bison.c"
    break;

  case 407: /* extended_prio_spec: extended_prio_name  */
#line 2666 "parser_bison.y"
                        {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 10908 "parser_bison.c"
    break;

  case 408: /* extended_prio_spec: extended_prio_name "+" "number"  */
#line 2677 "parser_bison.y"
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
#line 10925 "parser_bison.c"
    break;

  case 409: /* extended_prio_spec: extended_prio_name "-" "number"  */
#line 2690 "parser_bison.y"
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
#line 10942 "parser_bison.c"
    break;

  case 410: /* int_num: "number"  */
#line 2704 "parser_bison.y"
                                                        { (yyval.val32) = (yyvsp[0].val); }
#line 10948 "parser_bison.c"
    break;

  case 411: /* int_num: "-" "number"  */
#line 2705 "parser_bison.y"
                                                        { (yyval.val32) = -(yyvsp[0].val); }
#line 10954 "parser_bison.c"
    break;

  case 412: /* dev_spec: "device" string  */
#line 2709 "parser_bison.y"
                        {
				struct expr *expr = ifname_expr_alloc(&(yyloc), state->msgs, (yyvsp[0].string));

				if (!expr)
					YYERROR;

				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 10969 "parser_bison.c"
    break;

  case 413: /* dev_spec: "device" variable_expr  */
#line 2720 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10979 "parser_bison.c"
    break;

  case 414: /* dev_spec: "devices" '=' flowtable_expr  */
#line 2726 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 10987 "parser_bison.c"
    break;

  case 415: /* dev_spec: %empty  */
#line 2729 "parser_bison.y"
                                                        { (yyval.expr) = NULL; }
#line 10993 "parser_bison.c"
    break;

  case 416: /* flags_spec: "flags" "offload"  */
#line 2733 "parser_bison.y"
                        {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 11001 "parser_bison.c"
    break;

  case 417: /* policy_spec: "policy" policy_expr close_scope_policy  */
#line 2739 "parser_bison.y"
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
#line 11016 "parser_bison.c"
    break;

  case 418: /* policy_expr: variable_expr  */
#line 2752 "parser_bison.y"
                        {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 11025 "parser_bison.c"
    break;

  case 419: /* policy_expr: chain_policy  */
#line 2757 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 11036 "parser_bison.c"
    break;

  case 420: /* chain_policy: "accept"  */
#line 2765 "parser_bison.y"
                                                { (yyval.val32) = NF_ACCEPT; }
#line 11042 "parser_bison.c"
    break;

  case 421: /* chain_policy: "drop"  */
#line 2766 "parser_bison.y"
                                                { (yyval.val32) = NF_DROP;   }
#line 11048 "parser_bison.c"
    break;

  case 423: /* identifier: "last"  */
#line 2770 "parser_bison.y"
                                                { (yyval.string) = xstrdup("last"); }
#line 11054 "parser_bison.c"
    break;

  case 427: /* time_spec: "string"  */
#line 2779 "parser_bison.y"
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
#line 11071 "parser_bison.c"
    break;

  case 428: /* family_spec: %empty  */
#line 2793 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV4; }
#line 11077 "parser_bison.c"
    break;

  case 430: /* family_spec_explicit: "ip" close_scope_ip  */
#line 2797 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV4; }
#line 11083 "parser_bison.c"
    break;

  case 431: /* family_spec_explicit: "ip6" close_scope_ip6  */
#line 2798 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV6; }
#line 11089 "parser_bison.c"
    break;

  case 432: /* family_spec_explicit: "inet"  */
#line 2799 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_INET; }
#line 11095 "parser_bison.c"
    break;

  case 433: /* family_spec_explicit: "arp" close_scope_arp  */
#line 2800 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_ARP; }
#line 11101 "parser_bison.c"
    break;

  case 434: /* family_spec_explicit: "bridge"  */
#line 2801 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_BRIDGE; }
#line 11107 "parser_bison.c"
    break;

  case 435: /* family_spec_explicit: "netdev"  */
#line 2802 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_NETDEV; }
#line 11113 "parser_bison.c"
    break;

  case 436: /* table_spec: family_spec identifier  */
#line 2806 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 11124 "parser_bison.c"
    break;

  case 437: /* tableid_spec: family_spec "handle" "number"  */
#line 2815 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 11135 "parser_bison.c"
    break;

  case 438: /* chain_spec: table_spec identifier  */
#line 2824 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 11145 "parser_bison.c"
    break;

  case 439: /* chainid_spec: table_spec "handle" "number"  */
#line 2832 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 11155 "parser_bison.c"
    break;

  case 440: /* chain_identifier: identifier  */
#line 2840 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 11165 "parser_bison.c"
    break;

  case 441: /* set_spec: table_spec identifier  */
#line 2848 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 11175 "parser_bison.c"
    break;

  case 442: /* setid_spec: table_spec "handle" "number"  */
#line 2856 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 11185 "parser_bison.c"
    break;

  case 443: /* set_identifier: identifier  */
#line 2864 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 11195 "parser_bison.c"
    break;

  case 444: /* flowtable_spec: table_spec identifier  */
#line 2872 "parser_bison.y"
                        {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 11205 "parser_bison.c"
    break;

  case 445: /* flowtableid_spec: table_spec "handle" "number"  */
#line 2880 "parser_bison.y"
                        {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 11215 "parser_bison.c"
    break;

  case 446: /* flowtable_identifier: identifier  */
#line 2888 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 11225 "parser_bison.c"
    break;

  case 447: /* obj_spec: table_spec identifier  */
#line 2896 "parser_bison.y"
                        {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 11235 "parser_bison.c"
    break;

  case 448: /* objid_spec: table_spec "handle" "number"  */
#line 2904 "parser_bison.y"
                        {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 11245 "parser_bison.c"
    break;

  case 449: /* obj_identifier: identifier  */
#line 2912 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 11255 "parser_bison.c"
    break;

  case 450: /* handle_spec: "handle" "number"  */
#line 2920 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 11265 "parser_bison.c"
    break;

  case 451: /* position_spec: "position" "number"  */
#line 2928 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 11275 "parser_bison.c"
    break;

  case 452: /* index_spec: "index" "number"  */
#line 2936 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 11285 "parser_bison.c"
    break;

  case 453: /* rule_position: chain_spec  */
#line 2944 "parser_bison.y"
                        {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 11293 "parser_bison.c"
    break;

  case 454: /* rule_position: chain_spec position_spec  */
#line 2948 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11302 "parser_bison.c"
    break;

  case 455: /* rule_position: chain_spec handle_spec  */
#line 2953 "parser_bison.y"
                        {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11314 "parser_bison.c"
    break;

  case 456: /* rule_position: chain_spec index_spec  */
#line 2961 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11323 "parser_bison.c"
    break;

  case 457: /* ruleid_spec: chain_spec handle_spec  */
#line 2968 "parser_bison.y"
                        {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 11332 "parser_bison.c"
    break;

  case 458: /* comment_spec: "comment" string  */
#line 2975 "parser_bison.y"
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
#line 11347 "parser_bison.c"
    break;

  case 459: /* ruleset_spec: %empty  */
#line 2988 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 11356 "parser_bison.c"
    break;

  case 460: /* ruleset_spec: family_spec_explicit  */
#line 2993 "parser_bison.y"
                        {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 11365 "parser_bison.c"
    break;

  case 461: /* rule: rule_alloc  */
#line 3000 "parser_bison.y"
                        {
				(yyval.rule)->comment = NULL;
			}
#line 11373 "parser_bison.c"
    break;

  case 462: /* rule: rule_alloc comment_spec  */
#line 3004 "parser_bison.y"
                        {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 11381 "parser_bison.c"
    break;

  case 463: /* rule_alloc: stmt_list  */
#line 3010 "parser_bison.y"
                        {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 11395 "parser_bison.c"
    break;

  case 464: /* stmt_list: stmt  */
#line 3022 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 11405 "parser_bison.c"
    break;

  case 465: /* stmt_list: stmt_list stmt  */
#line 3028 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 11414 "parser_bison.c"
    break;

  case 466: /* stateful_stmt_list: stateful_stmt  */
#line 3035 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 11424 "parser_bison.c"
    break;

  case 467: /* stateful_stmt_list: stateful_stmt_list stateful_stmt  */
#line 3041 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 11433 "parser_bison.c"
    break;

  case 495: /* xt_stmt: "xt" "string" string  */
#line 3079 "parser_bison.y"
                        {
				(yyval.stmt) = NULL;
				xfree((yyvsp[-1].string));
				xfree((yyvsp[0].string));
				erec_queue(error(&(yyloc), "unsupported xtables compat expression, use iptables-nft with this ruleset"),
					   state->msgs);
				YYERROR;
			}
#line 11446 "parser_bison.c"
    break;

  case 496: /* chain_stmt_type: "jump"  */
#line 3089 "parser_bison.y"
                                        { (yyval.val) = NFT_JUMP; }
#line 11452 "parser_bison.c"
    break;

  case 497: /* chain_stmt_type: "goto"  */
#line 3090 "parser_bison.y"
                                        { (yyval.val) = NFT_GOTO; }
#line 11458 "parser_bison.c"
    break;

  case 498: /* chain_stmt: chain_stmt_type chain_block_alloc '{' subchain_block '}'  */
#line 3094 "parser_bison.y"
                        {
				(yyvsp[-3].chain)->location = (yylsp[-3]);
				close_scope(state);
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				(yyval.stmt) = chain_stmt_alloc(&(yyloc), (yyvsp[-1].chain), (yyvsp[-4].val));
			}
#line 11469 "parser_bison.c"
    break;

  case 499: /* verdict_stmt: verdict_expr  */
#line 3103 "parser_bison.y"
                        {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 11477 "parser_bison.c"
    break;

  case 500: /* verdict_stmt: verdict_map_stmt  */
#line 3107 "parser_bison.y"
                        {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 11485 "parser_bison.c"
    break;

  case 501: /* verdict_map_stmt: concat_expr "vmap" verdict_map_expr  */
#line 3113 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11493 "parser_bison.c"
    break;

  case 502: /* verdict_map_expr: '{' verdict_map_list_expr '}'  */
#line 3119 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11502 "parser_bison.c"
    break;

  case 504: /* verdict_map_list_expr: verdict_map_list_member_expr  */
#line 3127 "parser_bison.y"
                        {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11511 "parser_bison.c"
    break;

  case 505: /* verdict_map_list_expr: verdict_map_list_expr "comma" verdict_map_list_member_expr  */
#line 3132 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11520 "parser_bison.c"
    break;

  case 507: /* verdict_map_list_member_expr: opt_newline set_elem_expr "colon" verdict_expr opt_newline  */
#line 3140 "parser_bison.y"
                        {
				(yyval.expr) = mapping_expr_alloc(&(yylsp[-3]), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 11528 "parser_bison.c"
    break;

  case 508: /* connlimit_stmt: "ct" "count" "number" close_scope_ct  */
#line 3146 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 11537 "parser_bison.c"
    break;

  case 509: /* connlimit_stmt: "ct" "count" "over" "number" close_scope_ct  */
#line 3151 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 11547 "parser_bison.c"
    break;

  case 512: /* counter_stmt_alloc: "counter"  */
#line 3162 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 11555 "parser_bison.c"
    break;

  case 513: /* counter_stmt_alloc: "counter" "name" stmt_expr  */
#line 3166 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 11565 "parser_bison.c"
    break;

  case 514: /* counter_args: counter_arg  */
#line 3174 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 11573 "parser_bison.c"
    break;

  case 516: /* counter_arg: "packets" "number"  */
#line 3181 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 11581 "parser_bison.c"
    break;

  case 517: /* counter_arg: "bytes" "number"  */
#line 3185 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 11589 "parser_bison.c"
    break;

  case 518: /* last_stmt: "last"  */
#line 3191 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
			}
#line 11597 "parser_bison.c"
    break;

  case 519: /* last_stmt: "last" "used" "never"  */
#line 3195 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
			}
#line 11605 "parser_bison.c"
    break;

  case 520: /* last_stmt: "last" "used" time_spec  */
#line 3199 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
				(yyval.stmt)->last.used = (yyvsp[0].val);
				(yyval.stmt)->last.set = true;
			}
#line 11615 "parser_bison.c"
    break;

  case 523: /* log_stmt_alloc: "log"  */
#line 3211 "parser_bison.y"
                        {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 11623 "parser_bison.c"
    break;

  case 524: /* log_args: log_arg  */
#line 3217 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 11631 "parser_bison.c"
    break;

  case 526: /* log_arg: "prefix" string  */
#line 3224 "parser_bison.y"
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
#line 11760 "parser_bison.c"
    break;

  case 527: /* log_arg: "group" "number"  */
#line 3349 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 11769 "parser_bison.c"
    break;

  case 528: /* log_arg: "snaplen" "number"  */
#line 3354 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 11778 "parser_bison.c"
    break;

  case 529: /* log_arg: "queue-threshold" "number"  */
#line 3359 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 11787 "parser_bison.c"
    break;

  case 530: /* log_arg: "level" level_type  */
#line 3364 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 11796 "parser_bison.c"
    break;

  case 531: /* log_arg: "flags" log_flags  */
#line 3369 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 11804 "parser_bison.c"
    break;

  case 532: /* level_type: string  */
#line 3375 "parser_bison.y"
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
#line 11836 "parser_bison.c"
    break;

  case 533: /* log_flags: "tcp" log_flags_tcp close_scope_tcp  */
#line 3405 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-1].val);
			}
#line 11844 "parser_bison.c"
    break;

  case 534: /* log_flags: "ip" "options" close_scope_ip  */
#line 3409 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 11852 "parser_bison.c"
    break;

  case 535: /* log_flags: "skuid"  */
#line 3413 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_UID;
			}
#line 11860 "parser_bison.c"
    break;

  case 536: /* log_flags: "ether" close_scope_eth  */
#line 3417 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 11868 "parser_bison.c"
    break;

  case 537: /* log_flags: "all"  */
#line 3421 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_MASK;
			}
#line 11876 "parser_bison.c"
    break;

  case 538: /* log_flags_tcp: log_flags_tcp "comma" log_flag_tcp  */
#line 3427 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 11884 "parser_bison.c"
    break;

  case 540: /* log_flag_tcp: "seq"  */
#line 3434 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 11892 "parser_bison.c"
    break;

  case 541: /* log_flag_tcp: "options"  */
#line 3438 "parser_bison.y"
                        {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 11900 "parser_bison.c"
    break;

  case 542: /* limit_stmt: "limit" "rate" limit_mode limit_rate_pkts limit_burst_pkts close_scope_limit  */
#line 3444 "parser_bison.y"
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
#line 11918 "parser_bison.c"
    break;

  case 543: /* limit_stmt: "limit" "rate" limit_mode limit_rate_bytes limit_burst_bytes close_scope_limit  */
#line 3458 "parser_bison.y"
                        {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-2].limit_rate).rate;
				(yyval.stmt)->limit.unit	= (yyvsp[-2].limit_rate).unit;
				(yyval.stmt)->limit.burst	= (yyvsp[-1].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKT_BYTES;
				(yyval.stmt)->limit.flags = (yyvsp[-3].val);
			}
#line 11931 "parser_bison.c"
    break;

  case 544: /* limit_stmt: "limit" "name" stmt_expr close_scope_limit  */
#line 3467 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 11941 "parser_bison.c"
    break;

  case 545: /* quota_mode: "over"  */
#line 3474 "parser_bison.y"
                                                { (yyval.val) = NFT_QUOTA_F_INV; }
#line 11947 "parser_bison.c"
    break;

  case 546: /* quota_mode: "until"  */
#line 3475 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11953 "parser_bison.c"
    break;

  case 547: /* quota_mode: %empty  */
#line 3476 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11959 "parser_bison.c"
    break;

  case 548: /* quota_unit: "bytes"  */
#line 3479 "parser_bison.y"
                                                { (yyval.string) = xstrdup("bytes"); }
#line 11965 "parser_bison.c"
    break;

  case 549: /* quota_unit: "string"  */
#line 3480 "parser_bison.y"
                                                { (yyval.string) = (yyvsp[0].string); }
#line 11971 "parser_bison.c"
    break;

  case 550: /* quota_used: %empty  */
#line 3483 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 11977 "parser_bison.c"
    break;

  case 551: /* quota_used: "used" "number" quota_unit  */
#line 3485 "parser_bison.y"
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
#line 11994 "parser_bison.c"
    break;

  case 552: /* quota_stmt: "quota" quota_mode "number" quota_unit quota_used close_scope_quota  */
#line 3500 "parser_bison.y"
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
#line 12014 "parser_bison.c"
    break;

  case 553: /* quota_stmt: "quota" "name" stmt_expr close_scope_quota  */
#line 3516 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 12024 "parser_bison.c"
    break;

  case 554: /* limit_mode: "over"  */
#line 3523 "parser_bison.y"
                                                                { (yyval.val) = NFT_LIMIT_F_INV; }
#line 12030 "parser_bison.c"
    break;

  case 555: /* limit_mode: "until"  */
#line 3524 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 12036 "parser_bison.c"
    break;

  case 556: /* limit_mode: %empty  */
#line 3525 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 12042 "parser_bison.c"
    break;

  case 557: /* limit_burst_pkts: %empty  */
#line 3528 "parser_bison.y"
                                                                { (yyval.val) = 5; }
#line 12048 "parser_bison.c"
    break;

  case 558: /* limit_burst_pkts: "burst" "number" "packets"  */
#line 3529 "parser_bison.y"
                                                                { (yyval.val) = (yyvsp[-1].val); }
#line 12054 "parser_bison.c"
    break;

  case 559: /* limit_rate_pkts: "number" "/" time_unit  */
#line 3533 "parser_bison.y"
                        {
				(yyval.limit_rate).rate = (yyvsp[-2].val);
				(yyval.limit_rate).unit = (yyvsp[0].val);
			}
#line 12063 "parser_bison.c"
    break;

  case 560: /* limit_burst_bytes: %empty  */
#line 3539 "parser_bison.y"
                                                                { (yyval.val) = 0; }
#line 12069 "parser_bison.c"
    break;

  case 561: /* limit_burst_bytes: "burst" limit_bytes  */
#line 3540 "parser_bison.y"
                                                                { (yyval.val) = (yyvsp[0].val); }
#line 12075 "parser_bison.c"
    break;

  case 562: /* limit_rate_bytes: "number" "string"  */
#line 3544 "parser_bison.y"
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
#line 12093 "parser_bison.c"
    break;

  case 563: /* limit_rate_bytes: limit_bytes "/" time_unit  */
#line 3558 "parser_bison.y"
                        {
				(yyval.limit_rate).rate = (yyvsp[-2].val);
				(yyval.limit_rate).unit = (yyvsp[0].val);
			}
#line 12102 "parser_bison.c"
    break;

  case 564: /* limit_bytes: "number" "bytes"  */
#line 3564 "parser_bison.y"
                                                        { (yyval.val) = (yyvsp[-1].val); }
#line 12108 "parser_bison.c"
    break;

  case 565: /* limit_bytes: "number" "string"  */
#line 3566 "parser_bison.y"
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
#line 12125 "parser_bison.c"
    break;

  case 566: /* time_unit: "second"  */
#line 3580 "parser_bison.y"
                                                { (yyval.val) = 1ULL; }
#line 12131 "parser_bison.c"
    break;

  case 567: /* time_unit: "minute"  */
#line 3581 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60; }
#line 12137 "parser_bison.c"
    break;

  case 568: /* time_unit: "hour"  */
#line 3582 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60; }
#line 12143 "parser_bison.c"
    break;

  case 569: /* time_unit: "day"  */
#line 3583 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 12149 "parser_bison.c"
    break;

  case 570: /* time_unit: "week"  */
#line 3584 "parser_bison.y"
                                                { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 12155 "parser_bison.c"
    break;

  case 572: /* reject_stmt_alloc: "reject"  */
#line 3591 "parser_bison.y"
                        {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 12163 "parser_bison.c"
    break;

  case 573: /* reject_with_expr: "string"  */
#line 3597 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state), (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 12173 "parser_bison.c"
    break;

  case 574: /* reject_with_expr: integer_expr  */
#line 3602 "parser_bison.y"
                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12179 "parser_bison.c"
    break;

  case 575: /* reject_opts: %empty  */
#line 3606 "parser_bison.y"
                        {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 12188 "parser_bison.c"
    break;

  case 576: /* reject_opts: "with" "icmp" "type" reject_with_expr close_scope_type close_scope_icmp  */
#line 3611 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-6].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-6].stmt)->reject.expr = (yyvsp[-2].expr);
				datatype_set((yyvsp[-6].stmt)->reject.expr, &icmp_code_type);
			}
#line 12199 "parser_bison.c"
    break;

  case 577: /* reject_opts: "with" "icmp" reject_with_expr  */
#line 3618 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmp_code_type);
			}
#line 12210 "parser_bison.c"
    break;

  case 578: /* reject_opts: "with" "icmpv6" "type" reject_with_expr close_scope_type close_scope_icmp  */
#line 3625 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-6].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-6].stmt)->reject.expr = (yyvsp[-2].expr);
				datatype_set((yyvsp[-6].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 12221 "parser_bison.c"
    break;

  case 579: /* reject_opts: "with" "icmpv6" reject_with_expr  */
#line 3632 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 12232 "parser_bison.c"
    break;

  case 580: /* reject_opts: "with" "icmpx" "type" reject_with_expr close_scope_type  */
#line 3639 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-5].stmt)->reject.expr = (yyvsp[-1].expr);
				datatype_set((yyvsp[-5].stmt)->reject.expr, &icmpx_code_type);
			}
#line 12242 "parser_bison.c"
    break;

  case 581: /* reject_opts: "with" "icmpx" reject_with_expr  */
#line 3645 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpx_code_type);
			}
#line 12252 "parser_bison.c"
    break;

  case 582: /* reject_opts: "with" "tcp" close_scope_tcp "reset" close_scope_reset  */
#line 3651 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 12260 "parser_bison.c"
    break;

  case 584: /* nat_stmt_alloc: "snat"  */
#line 3659 "parser_bison.y"
                                        { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 12266 "parser_bison.c"
    break;

  case 585: /* nat_stmt_alloc: "dnat"  */
#line 3660 "parser_bison.y"
                                        { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 12272 "parser_bison.c"
    break;

  case 586: /* tproxy_stmt: "tproxy" "to" stmt_expr  */
#line 3664 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 12282 "parser_bison.c"
    break;

  case 587: /* tproxy_stmt: "tproxy" nf_key_proto "to" stmt_expr  */
#line 3670 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 12292 "parser_bison.c"
    break;

  case 588: /* tproxy_stmt: "tproxy" "to" "colon" stmt_expr  */
#line 3676 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12302 "parser_bison.c"
    break;

  case 589: /* tproxy_stmt: "tproxy" "to" stmt_expr "colon" stmt_expr  */
#line 3682 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12313 "parser_bison.c"
    break;

  case 590: /* tproxy_stmt: "tproxy" nf_key_proto "to" stmt_expr "colon" stmt_expr  */
#line 3689 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12324 "parser_bison.c"
    break;

  case 591: /* tproxy_stmt: "tproxy" nf_key_proto "to" "colon" stmt_expr  */
#line 3696 "parser_bison.y"
                        {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 12334 "parser_bison.c"
    break;

  case 594: /* synproxy_stmt_alloc: "synproxy"  */
#line 3708 "parser_bison.y"
                        {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 12342 "parser_bison.c"
    break;

  case 595: /* synproxy_stmt_alloc: "synproxy" "name" stmt_expr  */
#line 3712 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 12352 "parser_bison.c"
    break;

  case 596: /* synproxy_args: synproxy_arg  */
#line 3720 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 12360 "parser_bison.c"
    break;

  case 598: /* synproxy_arg: "mss" "number"  */
#line 3727 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 12369 "parser_bison.c"
    break;

  case 599: /* synproxy_arg: "wscale" "number"  */
#line 3732 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 12378 "parser_bison.c"
    break;

  case 600: /* synproxy_arg: "timestamp"  */
#line 3737 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 12386 "parser_bison.c"
    break;

  case 601: /* synproxy_arg: "sack-permitted"  */
#line 3741 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 12394 "parser_bison.c"
    break;

  case 602: /* synproxy_config: "mss" "number" "wscale" "number" synproxy_ts synproxy_sack  */
#line 3747 "parser_bison.y"
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
#line 12414 "parser_bison.c"
    break;

  case 603: /* synproxy_config: "mss" "number" stmt_separator "wscale" "number" stmt_separator synproxy_ts synproxy_sack  */
#line 3763 "parser_bison.y"
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
#line 12434 "parser_bison.c"
    break;

  case 604: /* synproxy_obj: %empty  */
#line 3781 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 12443 "parser_bison.c"
    break;

  case 605: /* synproxy_ts: %empty  */
#line 3787 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 12449 "parser_bison.c"
    break;

  case 606: /* synproxy_ts: "timestamp"  */
#line 3789 "parser_bison.y"
                        {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 12457 "parser_bison.c"
    break;

  case 607: /* synproxy_sack: %empty  */
#line 3794 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 12463 "parser_bison.c"
    break;

  case 608: /* synproxy_sack: "sack-permitted"  */
#line 3796 "parser_bison.y"
                        {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 12471 "parser_bison.c"
    break;

  case 609: /* primary_stmt_expr: symbol_expr  */
#line 3801 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12477 "parser_bison.c"
    break;

  case 610: /* primary_stmt_expr: integer_expr  */
#line 3802 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12483 "parser_bison.c"
    break;

  case 611: /* primary_stmt_expr: boolean_expr  */
#line 3803 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12489 "parser_bison.c"
    break;

  case 612: /* primary_stmt_expr: meta_expr  */
#line 3804 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12495 "parser_bison.c"
    break;

  case 613: /* primary_stmt_expr: rt_expr  */
#line 3805 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12501 "parser_bison.c"
    break;

  case 614: /* primary_stmt_expr: ct_expr  */
#line 3806 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12507 "parser_bison.c"
    break;

  case 615: /* primary_stmt_expr: numgen_expr  */
#line 3807 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12513 "parser_bison.c"
    break;

  case 616: /* primary_stmt_expr: hash_expr  */
#line 3808 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12519 "parser_bison.c"
    break;

  case 617: /* primary_stmt_expr: payload_expr  */
#line 3809 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12525 "parser_bison.c"
    break;

  case 618: /* primary_stmt_expr: keyword_expr  */
#line 3810 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12531 "parser_bison.c"
    break;

  case 619: /* primary_stmt_expr: socket_expr  */
#line 3811 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12537 "parser_bison.c"
    break;

  case 620: /* primary_stmt_expr: osf_expr  */
#line 3812 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 12543 "parser_bison.c"
    break;

  case 621: /* primary_stmt_expr: '(' basic_stmt_expr ')'  */
#line 3813 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 12549 "parser_bison.c"
    break;

  case 623: /* shift_stmt_expr: shift_stmt_expr "<<" primary_stmt_expr  */
#line 3818 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12557 "parser_bison.c"
    break;

  case 624: /* shift_stmt_expr: shift_stmt_expr ">>" primary_stmt_expr  */
#line 3822 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12565 "parser_bison.c"
    break;

  case 626: /* and_stmt_expr: and_stmt_expr "&" shift_stmt_expr  */
#line 3829 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12573 "parser_bison.c"
    break;

  case 628: /* exclusive_or_stmt_expr: exclusive_or_stmt_expr "^" and_stmt_expr  */
#line 3836 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12581 "parser_bison.c"
    break;

  case 630: /* inclusive_or_stmt_expr: inclusive_or_stmt_expr '|' exclusive_or_stmt_expr  */
#line 3843 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12589 "parser_bison.c"
    break;

  case 633: /* concat_stmt_expr: concat_stmt_expr "." primary_stmt_expr  */
#line 3853 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 12602 "parser_bison.c"
    break;

  case 636: /* map_stmt_expr: concat_stmt_expr "map" map_stmt_expr_set  */
#line 3868 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12610 "parser_bison.c"
    break;

  case 637: /* map_stmt_expr: concat_stmt_expr  */
#line 3871 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 12616 "parser_bison.c"
    break;

  case 638: /* prefix_stmt_expr: basic_stmt_expr "/" "number"  */
#line 3875 "parser_bison.y"
                        {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 12624 "parser_bison.c"
    break;

  case 639: /* range_stmt_expr: basic_stmt_expr "-" basic_stmt_expr  */
#line 3881 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12632 "parser_bison.c"
    break;

  case 645: /* nat_stmt_args: stmt_expr  */
#line 3896 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12640 "parser_bison.c"
    break;

  case 646: /* nat_stmt_args: "to" stmt_expr  */
#line 3900 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12648 "parser_bison.c"
    break;

  case 647: /* nat_stmt_args: nf_key_proto "to" stmt_expr  */
#line 3904 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12657 "parser_bison.c"
    break;

  case 648: /* nat_stmt_args: stmt_expr "colon" stmt_expr  */
#line 3909 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12666 "parser_bison.c"
    break;

  case 649: /* nat_stmt_args: "to" stmt_expr "colon" stmt_expr  */
#line 3914 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12675 "parser_bison.c"
    break;

  case 650: /* nat_stmt_args: nf_key_proto "to" stmt_expr "colon" stmt_expr  */
#line 3919 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12685 "parser_bison.c"
    break;

  case 651: /* nat_stmt_args: "colon" stmt_expr  */
#line 3925 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12693 "parser_bison.c"
    break;

  case 652: /* nat_stmt_args: "to" "colon" stmt_expr  */
#line 3929 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12701 "parser_bison.c"
    break;

  case 653: /* nat_stmt_args: nat_stmt_args nf_nat_flags  */
#line 3933 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12709 "parser_bison.c"
    break;

  case 654: /* nat_stmt_args: nf_key_proto "addr" "." "port" "to" stmt_expr  */
#line 3937 "parser_bison.y"
                        {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.type_flags = STMT_NAT_F_CONCAT;
			}
#line 12719 "parser_bison.c"
    break;

  case 655: /* nat_stmt_args: nf_key_proto "interval" "to" stmt_expr  */
#line 3943 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12728 "parser_bison.c"
    break;

  case 656: /* nat_stmt_args: "interval" "to" stmt_expr  */
#line 3948 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 12736 "parser_bison.c"
    break;

  case 657: /* nat_stmt_args: nf_key_proto "prefix" "to" stmt_expr  */
#line 3952 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-4].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 12748 "parser_bison.c"
    break;

  case 658: /* nat_stmt_args: "prefix" "to" stmt_expr  */
#line 3960 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-3].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 12759 "parser_bison.c"
    break;

  case 661: /* masq_stmt_alloc: "masquerade"  */
#line 3972 "parser_bison.y"
                                                { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 12765 "parser_bison.c"
    break;

  case 662: /* masq_stmt_args: "to" "colon" stmt_expr  */
#line 3976 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12773 "parser_bison.c"
    break;

  case 663: /* masq_stmt_args: "to" "colon" stmt_expr nf_nat_flags  */
#line 3980 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12782 "parser_bison.c"
    break;

  case 664: /* masq_stmt_args: nf_nat_flags  */
#line 3985 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12790 "parser_bison.c"
    break;

  case 667: /* redir_stmt_alloc: "redirect"  */
#line 3994 "parser_bison.y"
                                                { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 12796 "parser_bison.c"
    break;

  case 668: /* redir_stmt_arg: "to" stmt_expr  */
#line 3998 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12804 "parser_bison.c"
    break;

  case 669: /* redir_stmt_arg: "to" "colon" stmt_expr  */
#line 4002 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 12812 "parser_bison.c"
    break;

  case 670: /* redir_stmt_arg: nf_nat_flags  */
#line 4006 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12820 "parser_bison.c"
    break;

  case 671: /* redir_stmt_arg: "to" stmt_expr nf_nat_flags  */
#line 4010 "parser_bison.y"
                        {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12829 "parser_bison.c"
    break;

  case 672: /* redir_stmt_arg: "to" "colon" stmt_expr nf_nat_flags  */
#line 4015 "parser_bison.y"
                        {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 12838 "parser_bison.c"
    break;

  case 673: /* dup_stmt: "dup" "to" stmt_expr  */
#line 4022 "parser_bison.y"
                        {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 12847 "parser_bison.c"
    break;

  case 674: /* dup_stmt: "dup" "to" stmt_expr "device" stmt_expr  */
#line 4027 "parser_bison.y"
                        {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 12857 "parser_bison.c"
    break;

  case 675: /* fwd_stmt: "fwd" "to" stmt_expr  */
#line 4035 "parser_bison.y"
                        {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 12866 "parser_bison.c"
    break;

  case 676: /* fwd_stmt: "fwd" nf_key_proto "to" stmt_expr "device" stmt_expr  */
#line 4040 "parser_bison.y"
                        {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 12877 "parser_bison.c"
    break;

  case 678: /* nf_nat_flags: nf_nat_flags "comma" nf_nat_flag  */
#line 4050 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 12885 "parser_bison.c"
    break;

  case 679: /* nf_nat_flag: "random"  */
#line 4055 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 12891 "parser_bison.c"
    break;

  case 680: /* nf_nat_flag: "fully-random"  */
#line 4056 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 12897 "parser_bison.c"
    break;

  case 681: /* nf_nat_flag: "persistent"  */
#line 4057 "parser_bison.y"
                                                { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 12903 "parser_bison.c"
    break;

  case 683: /* queue_stmt: "queue" "to" queue_stmt_expr close_scope_queue  */
#line 4062 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), 0);
			}
#line 12911 "parser_bison.c"
    break;

  case 684: /* queue_stmt: "queue" "flags" queue_stmt_flags "to" queue_stmt_expr close_scope_queue  */
#line 4066 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 12919 "parser_bison.c"
    break;

  case 685: /* queue_stmt: "queue" "flags" queue_stmt_flags "num" queue_stmt_expr_simple close_scope_queue  */
#line 4070 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 12927 "parser_bison.c"
    break;

  case 688: /* queue_stmt_alloc: "queue"  */
#line 4080 "parser_bison.y"
                        {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), NULL, 0);
			}
#line 12935 "parser_bison.c"
    break;

  case 689: /* queue_stmt_args: queue_stmt_arg  */
#line 4086 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 12943 "parser_bison.c"
    break;

  case 691: /* queue_stmt_arg: "num" queue_stmt_expr_simple  */
#line 4093 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 12952 "parser_bison.c"
    break;

  case 692: /* queue_stmt_arg: queue_stmt_flags  */
#line 4098 "parser_bison.y"
                        {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 12960 "parser_bison.c"
    break;

  case 697: /* queue_stmt_expr_simple: queue_expr "-" queue_expr  */
#line 4110 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12968 "parser_bison.c"
    break;

  case 703: /* queue_stmt_flags: queue_stmt_flags "comma" queue_stmt_flag  */
#line 4123 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 12976 "parser_bison.c"
    break;

  case 704: /* queue_stmt_flag: "bypass"  */
#line 4128 "parser_bison.y"
                                        { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 12982 "parser_bison.c"
    break;

  case 705: /* queue_stmt_flag: "fanout"  */
#line 4129 "parser_bison.y"
                                        { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 12988 "parser_bison.c"
    break;

  case 708: /* set_elem_expr_stmt_alloc: concat_expr  */
#line 4137 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 12996 "parser_bison.c"
    break;

  case 709: /* set_stmt: "set" set_stmt_op set_elem_expr_stmt set_ref_expr  */
#line 4143 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 13007 "parser_bison.c"
    break;

  case 710: /* set_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt '}'  */
#line 4150 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 13018 "parser_bison.c"
    break;

  case 711: /* set_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt stateful_stmt_list '}'  */
#line 4157 "parser_bison.y"
                        {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				list_splice_tail((yyvsp[-1].list), &(yyval.stmt)->set.stmt_list);
				free((yyvsp[-1].list));
			}
#line 13031 "parser_bison.c"
    break;

  case 712: /* set_stmt_op: "add"  */
#line 4167 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 13037 "parser_bison.c"
    break;

  case 713: /* set_stmt_op: "update"  */
#line 4168 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 13043 "parser_bison.c"
    break;

  case 714: /* set_stmt_op: "delete"  */
#line 4169 "parser_bison.y"
                                        { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 13049 "parser_bison.c"
    break;

  case 715: /* map_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt "colon" set_elem_expr_stmt '}'  */
#line 4173 "parser_bison.y"
                        {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 13061 "parser_bison.c"
    break;

  case 716: /* map_stmt: set_stmt_op set_ref_expr '{' set_elem_expr_stmt stateful_stmt_list "colon" set_elem_expr_stmt '}'  */
#line 4181 "parser_bison.y"
                        {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
				list_splice_tail((yyvsp[-3].list), &(yyval.stmt)->map.stmt_list);
				free((yyvsp[-3].list));
			}
#line 13075 "parser_bison.c"
    break;

  case 717: /* meter_stmt: flow_stmt_legacy_alloc flow_stmt_opts '{' meter_key_expr stmt '}'  */
#line 4193 "parser_bison.y"
                        {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 13086 "parser_bison.c"
    break;

  case 718: /* meter_stmt: meter_stmt_alloc  */
#line 4199 "parser_bison.y"
                                                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 13092 "parser_bison.c"
    break;

  case 719: /* flow_stmt_legacy_alloc: "flow"  */
#line 4203 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 13100 "parser_bison.c"
    break;

  case 720: /* flow_stmt_opts: flow_stmt_opt  */
#line 4209 "parser_bison.y"
                        {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 13108 "parser_bison.c"
    break;

  case 722: /* flow_stmt_opt: "table" identifier  */
#line 4216 "parser_bison.y"
                        {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 13116 "parser_bison.c"
    break;

  case 723: /* meter_stmt_alloc: "meter" identifier '{' meter_key_expr stmt '}'  */
#line 4222 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 13129 "parser_bison.c"
    break;

  case 724: /* meter_stmt_alloc: "meter" identifier "size" "number" '{' meter_key_expr stmt '}'  */
#line 4231 "parser_bison.y"
                        {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 13142 "parser_bison.c"
    break;

  case 725: /* match_stmt: relational_expr  */
#line 4242 "parser_bison.y"
                        {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 13150 "parser_bison.c"
    break;

  case 726: /* variable_expr: '$' identifier  */
#line 4248 "parser_bison.y"
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
#line 13178 "parser_bison.c"
    break;

  case 728: /* symbol_expr: string  */
#line 4275 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 13189 "parser_bison.c"
    break;

  case 731: /* set_ref_symbol_expr: "@" identifier close_scope_at  */
#line 4288 "parser_bison.y"
                        {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[-1].string));
				xfree((yyvsp[-1].string));
			}
#line 13200 "parser_bison.c"
    break;

  case 732: /* integer_expr: "number"  */
#line 4297 "parser_bison.y"
                        {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 13213 "parser_bison.c"
    break;

  case 733: /* primary_expr: symbol_expr  */
#line 4307 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13219 "parser_bison.c"
    break;

  case 734: /* primary_expr: integer_expr  */
#line 4308 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13225 "parser_bison.c"
    break;

  case 735: /* primary_expr: payload_expr  */
#line 4309 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13231 "parser_bison.c"
    break;

  case 736: /* primary_expr: exthdr_expr  */
#line 4310 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13237 "parser_bison.c"
    break;

  case 737: /* primary_expr: exthdr_exists_expr  */
#line 4311 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13243 "parser_bison.c"
    break;

  case 738: /* primary_expr: meta_expr  */
#line 4312 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13249 "parser_bison.c"
    break;

  case 739: /* primary_expr: socket_expr  */
#line 4313 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13255 "parser_bison.c"
    break;

  case 740: /* primary_expr: rt_expr  */
#line 4314 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13261 "parser_bison.c"
    break;

  case 741: /* primary_expr: ct_expr  */
#line 4315 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13267 "parser_bison.c"
    break;

  case 742: /* primary_expr: numgen_expr  */
#line 4316 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13273 "parser_bison.c"
    break;

  case 743: /* primary_expr: hash_expr  */
#line 4317 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13279 "parser_bison.c"
    break;

  case 744: /* primary_expr: fib_expr  */
#line 4318 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13285 "parser_bison.c"
    break;

  case 745: /* primary_expr: osf_expr  */
#line 4319 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13291 "parser_bison.c"
    break;

  case 746: /* primary_expr: xfrm_expr  */
#line 4320 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 13297 "parser_bison.c"
    break;

  case 747: /* primary_expr: '(' basic_expr ')'  */
#line 4321 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 13303 "parser_bison.c"
    break;

  case 748: /* fib_expr: "fib" fib_tuple fib_result close_scope_fib  */
#line 4325 "parser_bison.y"
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
#line 13328 "parser_bison.c"
    break;

  case 749: /* fib_result: "oif"  */
#line 4347 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 13334 "parser_bison.c"
    break;

  case 750: /* fib_result: "oifname"  */
#line 4348 "parser_bison.y"
                                        { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 13340 "parser_bison.c"
    break;

  case 751: /* fib_result: "type" close_scope_type  */
#line 4349 "parser_bison.y"
                                                                { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 13346 "parser_bison.c"
    break;

  case 752: /* fib_flag: "saddr"  */
#line 4352 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 13352 "parser_bison.c"
    break;

  case 753: /* fib_flag: "daddr"  */
#line 4353 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 13358 "parser_bison.c"
    break;

  case 754: /* fib_flag: "mark"  */
#line 4354 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_MARK; }
#line 13364 "parser_bison.c"
    break;

  case 755: /* fib_flag: "iif"  */
#line 4355 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_IIF; }
#line 13370 "parser_bison.c"
    break;

  case 756: /* fib_flag: "oif"  */
#line 4356 "parser_bison.y"
                                        { (yyval.val) = NFTA_FIB_F_OIF; }
#line 13376 "parser_bison.c"
    break;

  case 757: /* fib_tuple: fib_flag "." fib_tuple  */
#line 4360 "parser_bison.y"
                        {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 13384 "parser_bison.c"
    break;

  case 759: /* osf_expr: "osf" osf_ttl "version" close_scope_osf  */
#line 4367 "parser_bison.y"
                        {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-2].val), NFT_OSF_F_VERSION);
			}
#line 13392 "parser_bison.c"
    break;

  case 760: /* osf_expr: "osf" osf_ttl "name" close_scope_osf  */
#line 4371 "parser_bison.y"
                        {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-2].val), 0);
			}
#line 13400 "parser_bison.c"
    break;

  case 761: /* osf_ttl: %empty  */
#line 4377 "parser_bison.y"
                        {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 13408 "parser_bison.c"
    break;

  case 762: /* osf_ttl: "ttl" "string"  */
#line 4381 "parser_bison.y"
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
#line 13426 "parser_bison.c"
    break;

  case 764: /* shift_expr: shift_expr "<<" primary_rhs_expr  */
#line 4398 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13434 "parser_bison.c"
    break;

  case 765: /* shift_expr: shift_expr ">>" primary_rhs_expr  */
#line 4402 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13442 "parser_bison.c"
    break;

  case 767: /* and_expr: and_expr "&" shift_rhs_expr  */
#line 4409 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13450 "parser_bison.c"
    break;

  case 769: /* exclusive_or_expr: exclusive_or_expr "^" and_rhs_expr  */
#line 4416 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13458 "parser_bison.c"
    break;

  case 771: /* inclusive_or_expr: inclusive_or_expr '|' exclusive_or_rhs_expr  */
#line 4423 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13466 "parser_bison.c"
    break;

  case 774: /* concat_expr: concat_expr "." basic_expr  */
#line 4433 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 13479 "parser_bison.c"
    break;

  case 775: /* prefix_rhs_expr: basic_rhs_expr "/" "number"  */
#line 4444 "parser_bison.y"
                        {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 13487 "parser_bison.c"
    break;

  case 776: /* range_rhs_expr: basic_rhs_expr "-" basic_rhs_expr  */
#line 4450 "parser_bison.y"
                        {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13495 "parser_bison.c"
    break;

  case 779: /* map_expr: concat_expr "map" rhs_expr  */
#line 4460 "parser_bison.y"
                        {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13503 "parser_bison.c"
    break;

  case 783: /* set_expr: '{' set_list_expr '}'  */
#line 4471 "parser_bison.y"
                        {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13512 "parser_bison.c"
    break;

  case 784: /* set_list_expr: set_list_member_expr  */
#line 4478 "parser_bison.y"
                        {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 13521 "parser_bison.c"
    break;

  case 785: /* set_list_expr: set_list_expr "comma" set_list_member_expr  */
#line 4483 "parser_bison.y"
                        {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 13530 "parser_bison.c"
    break;

  case 787: /* set_list_member_expr: opt_newline set_expr opt_newline  */
#line 4491 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13538 "parser_bison.c"
    break;

  case 788: /* set_list_member_expr: opt_newline set_elem_expr opt_newline  */
#line 4495 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13546 "parser_bison.c"
    break;

  case 789: /* set_list_member_expr: opt_newline set_elem_expr "colon" set_rhs_expr opt_newline  */
#line 4499 "parser_bison.y"
                        {
				(yyval.expr) = mapping_expr_alloc(&(yylsp[-3]), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 13554 "parser_bison.c"
    break;

  case 791: /* meter_key_expr: meter_key_expr_alloc set_elem_options  */
#line 4506 "parser_bison.y"
                        {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 13563 "parser_bison.c"
    break;

  case 792: /* meter_key_expr_alloc: concat_expr  */
#line 4513 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 13571 "parser_bison.c"
    break;

  case 795: /* set_elem_key_expr: set_lhs_expr  */
#line 4522 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 13577 "parser_bison.c"
    break;

  case 796: /* set_elem_key_expr: "*"  */
#line 4523 "parser_bison.y"
                                                        { (yyval.expr) = set_elem_catchall_expr_alloc(&(yylsp[0])); }
#line 13583 "parser_bison.c"
    break;

  case 797: /* set_elem_expr_alloc: set_elem_key_expr set_elem_stmt_list  */
#line 4527 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[-1]), (yyvsp[-1].expr));
				list_splice_tail((yyvsp[0].list), &(yyval.expr)->stmt_list);
				xfree((yyvsp[0].list));
			}
#line 13593 "parser_bison.c"
    break;

  case 798: /* set_elem_expr_alloc: set_elem_key_expr  */
#line 4533 "parser_bison.y"
                        {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 13601 "parser_bison.c"
    break;

  case 799: /* set_elem_options: set_elem_option  */
#line 4539 "parser_bison.y"
                        {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 13609 "parser_bison.c"
    break;

  case 801: /* set_elem_option: "timeout" time_spec  */
#line 4546 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 13617 "parser_bison.c"
    break;

  case 802: /* set_elem_option: "expires" time_spec  */
#line 4550 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 13625 "parser_bison.c"
    break;

  case 803: /* set_elem_option: comment_spec  */
#line 4554 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 13637 "parser_bison.c"
    break;

  case 804: /* set_elem_expr_options: set_elem_expr_option  */
#line 4564 "parser_bison.y"
                        {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 13645 "parser_bison.c"
    break;

  case 806: /* set_elem_stmt_list: set_elem_stmt  */
#line 4571 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 13655 "parser_bison.c"
    break;

  case 807: /* set_elem_stmt_list: set_elem_stmt_list set_elem_stmt  */
#line 4577 "parser_bison.y"
                        {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 13664 "parser_bison.c"
    break;

  case 808: /* set_elem_stmt: "counter" close_scope_counter  */
#line 4584 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 13672 "parser_bison.c"
    break;

  case 809: /* set_elem_stmt: "counter" "packets" "number" "bytes" "number" close_scope_counter  */
#line 4588 "parser_bison.y"
                        {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
				(yyval.stmt)->counter.packets = (yyvsp[-3].val);
				(yyval.stmt)->counter.bytes = (yyvsp[-1].val);
			}
#line 13682 "parser_bison.c"
    break;

  case 810: /* set_elem_stmt: "limit" "rate" limit_mode limit_rate_pkts limit_burst_pkts close_scope_limit  */
#line 4594 "parser_bison.y"
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
#line 13700 "parser_bison.c"
    break;

  case 811: /* set_elem_stmt: "limit" "rate" limit_mode limit_rate_bytes limit_burst_bytes close_scope_limit  */
#line 4608 "parser_bison.y"
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
#line 13718 "parser_bison.c"
    break;

  case 812: /* set_elem_stmt: "ct" "count" "number" close_scope_ct  */
#line 4622 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 13727 "parser_bison.c"
    break;

  case 813: /* set_elem_stmt: "ct" "count" "over" "number" close_scope_ct  */
#line 4627 "parser_bison.y"
                        {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 13737 "parser_bison.c"
    break;

  case 814: /* set_elem_stmt: "quota" quota_mode "number" quota_unit quota_used close_scope_quota  */
#line 4633 "parser_bison.y"
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
#line 13757 "parser_bison.c"
    break;

  case 815: /* set_elem_stmt: "last" "used" "never" close_scope_last  */
#line 4649 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
			}
#line 13765 "parser_bison.c"
    break;

  case 816: /* set_elem_stmt: "last" "used" time_spec close_scope_last  */
#line 4653 "parser_bison.y"
                        {
				(yyval.stmt) = last_stmt_alloc(&(yyloc));
				(yyval.stmt)->last.used = (yyvsp[-1].val);
				(yyval.stmt)->last.set = true;
			}
#line 13775 "parser_bison.c"
    break;

  case 817: /* set_elem_expr_option: "timeout" time_spec  */
#line 4661 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 13783 "parser_bison.c"
    break;

  case 818: /* set_elem_expr_option: "expires" time_spec  */
#line 4665 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 13791 "parser_bison.c"
    break;

  case 819: /* set_elem_expr_option: comment_spec  */
#line 4669 "parser_bison.y"
                        {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 13803 "parser_bison.c"
    break;

  case 825: /* initializer_expr: '{' '}'  */
#line 4687 "parser_bison.y"
                                                { (yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_SET); }
#line 13809 "parser_bison.c"
    break;

  case 826: /* initializer_expr: "-" "number"  */
#line 4689 "parser_bison.y"
                        {
				int32_t num = -(yyvsp[0].val);

				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(num) * BITS_PER_BYTE,
							 &num);
			}
#line 13822 "parser_bison.c"
    break;

  case 827: /* counter_config: "packets" "number" "bytes" "number"  */
#line 4700 "parser_bison.y"
                        {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 13834 "parser_bison.c"
    break;

  case 828: /* counter_obj: %empty  */
#line 4710 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 13843 "parser_bison.c"
    break;

  case 829: /* quota_config: quota_mode "number" quota_unit quota_used  */
#line 4717 "parser_bison.y"
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
#line 13865 "parser_bison.c"
    break;

  case 830: /* quota_obj: %empty  */
#line 4737 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 13874 "parser_bison.c"
    break;

  case 831: /* secmark_config: string  */
#line 4744 "parser_bison.y"
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
#line 13892 "parser_bison.c"
    break;

  case 832: /* secmark_obj: %empty  */
#line 4760 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 13901 "parser_bison.c"
    break;

  case 833: /* ct_obj_type: "helper"  */
#line 4766 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 13907 "parser_bison.c"
    break;

  case 834: /* ct_obj_type: "timeout"  */
#line 4767 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 13913 "parser_bison.c"
    break;

  case 835: /* ct_obj_type: "expectation"  */
#line 4768 "parser_bison.y"
                                                { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 13919 "parser_bison.c"
    break;

  case 836: /* ct_cmd_type: "helpers"  */
#line 4771 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_HELPERS; }
#line 13925 "parser_bison.c"
    break;

  case 837: /* ct_cmd_type: "timeout"  */
#line 4772 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_TIMEOUTS; }
#line 13931 "parser_bison.c"
    break;

  case 838: /* ct_cmd_type: "expectation"  */
#line 4773 "parser_bison.y"
                                                { (yyval.val) = CMD_OBJ_CT_EXPECT; }
#line 13937 "parser_bison.c"
    break;

  case 839: /* ct_l4protoname: "tcp" close_scope_tcp  */
#line 4776 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_TCP; }
#line 13943 "parser_bison.c"
    break;

  case 840: /* ct_l4protoname: "udp" close_scope_udp  */
#line 4777 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_UDP; }
#line 13949 "parser_bison.c"
    break;

  case 841: /* ct_helper_config: "type" "quoted string" "protocol" ct_l4protoname stmt_separator close_scope_type  */
#line 4781 "parser_bison.y"
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
#line 13969 "parser_bison.c"
    break;

  case 842: /* ct_helper_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4797 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 13977 "parser_bison.c"
    break;

  case 843: /* timeout_states: timeout_state  */
#line 4803 "parser_bison.y"
                        {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 13987 "parser_bison.c"
    break;

  case 844: /* timeout_states: timeout_states "comma" timeout_state  */
#line 4809 "parser_bison.y"
                        {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 13996 "parser_bison.c"
    break;

  case 845: /* timeout_state: "string" "colon" "number"  */
#line 4817 "parser_bison.y"
                        {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 14011 "parser_bison.c"
    break;

  case 846: /* ct_timeout_config: "protocol" ct_l4protoname stmt_separator  */
#line 4830 "parser_bison.y"
                        {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 14023 "parser_bison.c"
    break;

  case 847: /* ct_timeout_config: "policy" '=' '{' timeout_states '}' stmt_separator close_scope_policy  */
#line 4838 "parser_bison.y"
                        {
				struct ct_timeout *ct;

				ct = &(yyvsp[-7].obj)->ct_timeout;
				list_splice_tail((yyvsp[-3].list), &ct->timeout_list);
				xfree((yyvsp[-3].list));
			}
#line 14035 "parser_bison.c"
    break;

  case 848: /* ct_timeout_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4846 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 14043 "parser_bison.c"
    break;

  case 849: /* ct_expect_config: "protocol" ct_l4protoname stmt_separator  */
#line 4852 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 14051 "parser_bison.c"
    break;

  case 850: /* ct_expect_config: "dport" "number" stmt_separator  */
#line 4856 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 14059 "parser_bison.c"
    break;

  case 851: /* ct_expect_config: "timeout" time_spec stmt_separator  */
#line 4860 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 14067 "parser_bison.c"
    break;

  case 852: /* ct_expect_config: "size" "number" stmt_separator  */
#line 4864 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 14075 "parser_bison.c"
    break;

  case 853: /* ct_expect_config: "l3proto" family_spec_explicit stmt_separator  */
#line 4868 "parser_bison.y"
                        {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 14083 "parser_bison.c"
    break;

  case 854: /* ct_obj_alloc: %empty  */
#line 4874 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 14091 "parser_bison.c"
    break;

  case 855: /* limit_config: "rate" limit_mode limit_rate_pkts limit_burst_pkts  */
#line 4880 "parser_bison.y"
                        {
				struct limit *limit;

				limit = &(yyvsp[-4].obj)->limit;
				limit->rate	= (yyvsp[-1].limit_rate).rate;
				limit->unit	= (yyvsp[-1].limit_rate).unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-2].val);
			}
#line 14106 "parser_bison.c"
    break;

  case 856: /* limit_config: "rate" limit_mode limit_rate_bytes limit_burst_bytes  */
#line 4891 "parser_bison.y"
                        {
				struct limit *limit;

				limit = &(yyvsp[-4].obj)->limit;
				limit->rate	= (yyvsp[-1].limit_rate).rate;
				limit->unit	= (yyvsp[-1].limit_rate).unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKT_BYTES;
				limit->flags	= (yyvsp[-2].val);
			}
#line 14121 "parser_bison.c"
    break;

  case 857: /* limit_obj: %empty  */
#line 4904 "parser_bison.y"
                        {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 14130 "parser_bison.c"
    break;

  case 858: /* relational_expr: expr rhs_expr  */
#line 4911 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 14138 "parser_bison.c"
    break;

  case 859: /* relational_expr: expr list_rhs_expr  */
#line 4915 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 14146 "parser_bison.c"
    break;

  case 860: /* relational_expr: expr basic_rhs_expr "/" list_rhs_expr  */
#line 4919 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 14154 "parser_bison.c"
    break;

  case 861: /* relational_expr: expr list_rhs_expr "/" list_rhs_expr  */
#line 4923 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 14162 "parser_bison.c"
    break;

  case 862: /* relational_expr: expr relational_op basic_rhs_expr "/" list_rhs_expr  */
#line 4927 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 14170 "parser_bison.c"
    break;

  case 863: /* relational_expr: expr relational_op list_rhs_expr "/" list_rhs_expr  */
#line 4931 "parser_bison.y"
                        {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 14178 "parser_bison.c"
    break;

  case 864: /* relational_expr: expr relational_op rhs_expr  */
#line 4935 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14186 "parser_bison.c"
    break;

  case 865: /* relational_expr: expr relational_op list_rhs_expr  */
#line 4939 "parser_bison.y"
                        {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14194 "parser_bison.c"
    break;

  case 866: /* list_rhs_expr: basic_rhs_expr "comma" basic_rhs_expr  */
#line 4945 "parser_bison.y"
                        {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 14204 "parser_bison.c"
    break;

  case 867: /* list_rhs_expr: list_rhs_expr "comma" basic_rhs_expr  */
#line 4951 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 14214 "parser_bison.c"
    break;

  case 868: /* rhs_expr: concat_rhs_expr  */
#line 4958 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14220 "parser_bison.c"
    break;

  case 869: /* rhs_expr: set_expr  */
#line 4959 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14226 "parser_bison.c"
    break;

  case 870: /* rhs_expr: set_ref_symbol_expr  */
#line 4960 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14232 "parser_bison.c"
    break;

  case 872: /* shift_rhs_expr: shift_rhs_expr "<<" primary_rhs_expr  */
#line 4965 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14240 "parser_bison.c"
    break;

  case 873: /* shift_rhs_expr: shift_rhs_expr ">>" primary_rhs_expr  */
#line 4969 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14248 "parser_bison.c"
    break;

  case 875: /* and_rhs_expr: and_rhs_expr "&" shift_rhs_expr  */
#line 4976 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14256 "parser_bison.c"
    break;

  case 877: /* exclusive_or_rhs_expr: exclusive_or_rhs_expr "^" and_rhs_expr  */
#line 4983 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14264 "parser_bison.c"
    break;

  case 879: /* inclusive_or_rhs_expr: inclusive_or_rhs_expr '|' exclusive_or_rhs_expr  */
#line 4990 "parser_bison.y"
                        {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 14272 "parser_bison.c"
    break;

  case 883: /* concat_rhs_expr: concat_rhs_expr "." multiton_rhs_expr  */
#line 5001 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 14285 "parser_bison.c"
    break;

  case 884: /* concat_rhs_expr: concat_rhs_expr "." basic_rhs_expr  */
#line 5010 "parser_bison.y"
                        {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 14298 "parser_bison.c"
    break;

  case 885: /* boolean_keys: "exists"  */
#line 5020 "parser_bison.y"
                                                { (yyval.val8) = true; }
#line 14304 "parser_bison.c"
    break;

  case 886: /* boolean_keys: "missing"  */
#line 5021 "parser_bison.y"
                                                { (yyval.val8) = false; }
#line 14310 "parser_bison.c"
    break;

  case 887: /* boolean_expr: boolean_keys  */
#line 5025 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 14320 "parser_bison.c"
    break;

  case 888: /* keyword_expr: "ether" close_scope_eth  */
#line 5032 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 14326 "parser_bison.c"
    break;

  case 889: /* keyword_expr: "ip" close_scope_ip  */
#line 5033 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 14332 "parser_bison.c"
    break;

  case 890: /* keyword_expr: "ip6" close_scope_ip6  */
#line 5034 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 14338 "parser_bison.c"
    break;

  case 891: /* keyword_expr: "vlan" close_scope_vlan  */
#line 5035 "parser_bison.y"
                                                         { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 14344 "parser_bison.c"
    break;

  case 892: /* keyword_expr: "arp" close_scope_arp  */
#line 5036 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 14350 "parser_bison.c"
    break;

  case 893: /* keyword_expr: "dnat" close_scope_nat  */
#line 5037 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 14356 "parser_bison.c"
    break;

  case 894: /* keyword_expr: "snat" close_scope_nat  */
#line 5038 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 14362 "parser_bison.c"
    break;

  case 895: /* keyword_expr: "ecn"  */
#line 5039 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 14368 "parser_bison.c"
    break;

  case 896: /* keyword_expr: "reset" close_scope_reset  */
#line 5040 "parser_bison.y"
                                                                { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 14374 "parser_bison.c"
    break;

  case 897: /* keyword_expr: "destroy" close_scope_destroy  */
#line 5041 "parser_bison.y"
                                                                { (yyval.expr) = symbol_value(&(yyloc), "destroy"); }
#line 14380 "parser_bison.c"
    break;

  case 898: /* keyword_expr: "original"  */
#line 5042 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 14386 "parser_bison.c"
    break;

  case 899: /* keyword_expr: "reply"  */
#line 5043 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 14392 "parser_bison.c"
    break;

  case 900: /* keyword_expr: "label"  */
#line 5044 "parser_bison.y"
                                                        { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 14398 "parser_bison.c"
    break;

  case 901: /* keyword_expr: "last" close_scope_last  */
#line 5045 "parser_bison.y"
                                                                { (yyval.expr) = symbol_value(&(yyloc), "last"); }
#line 14404 "parser_bison.c"
    break;

  case 902: /* primary_rhs_expr: symbol_expr  */
#line 5048 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14410 "parser_bison.c"
    break;

  case 903: /* primary_rhs_expr: integer_expr  */
#line 5049 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14416 "parser_bison.c"
    break;

  case 904: /* primary_rhs_expr: boolean_expr  */
#line 5050 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14422 "parser_bison.c"
    break;

  case 905: /* primary_rhs_expr: keyword_expr  */
#line 5051 "parser_bison.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 14428 "parser_bison.c"
    break;

  case 906: /* primary_rhs_expr: "tcp" close_scope_tcp  */
#line 5053 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14439 "parser_bison.c"
    break;

  case 907: /* primary_rhs_expr: "udp" close_scope_udp  */
#line 5060 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14450 "parser_bison.c"
    break;

  case 908: /* primary_rhs_expr: "udplite" close_scope_udplite  */
#line 5067 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14461 "parser_bison.c"
    break;

  case 909: /* primary_rhs_expr: "esp" close_scope_esp  */
#line 5074 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14472 "parser_bison.c"
    break;

  case 910: /* primary_rhs_expr: "ah" close_scope_ah  */
#line 5081 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14483 "parser_bison.c"
    break;

  case 911: /* primary_rhs_expr: "icmp" close_scope_icmp  */
#line 5088 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14494 "parser_bison.c"
    break;

  case 912: /* primary_rhs_expr: "igmp"  */
#line 5095 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14505 "parser_bison.c"
    break;

  case 913: /* primary_rhs_expr: "icmpv6" close_scope_icmp  */
#line 5102 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14516 "parser_bison.c"
    break;

  case 914: /* primary_rhs_expr: "gre" close_scope_gre  */
#line 5109 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_GRE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14527 "parser_bison.c"
    break;

  case 915: /* primary_rhs_expr: "comp" close_scope_comp  */
#line 5116 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14538 "parser_bison.c"
    break;

  case 916: /* primary_rhs_expr: "dccp" close_scope_dccp  */
#line 5123 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14549 "parser_bison.c"
    break;

  case 917: /* primary_rhs_expr: "sctp" close_scope_sctp  */
#line 5130 "parser_bison.y"
                        {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14560 "parser_bison.c"
    break;

  case 918: /* primary_rhs_expr: "redirect" close_scope_nat  */
#line 5137 "parser_bison.y"
                        {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 14571 "parser_bison.c"
    break;

  case 919: /* primary_rhs_expr: '(' basic_rhs_expr ')'  */
#line 5143 "parser_bison.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 14577 "parser_bison.c"
    break;

  case 920: /* relational_op: "=="  */
#line 5146 "parser_bison.y"
                                                { (yyval.val) = OP_EQ; }
#line 14583 "parser_bison.c"
    break;

  case 921: /* relational_op: "!="  */
#line 5147 "parser_bison.y"
                                                { (yyval.val) = OP_NEQ; }
#line 14589 "parser_bison.c"
    break;

  case 922: /* relational_op: "<"  */
#line 5148 "parser_bison.y"
                                                { (yyval.val) = OP_LT; }
#line 14595 "parser_bison.c"
    break;

  case 923: /* relational_op: ">"  */
#line 5149 "parser_bison.y"
                                                { (yyval.val) = OP_GT; }
#line 14601 "parser_bison.c"
    break;

  case 924: /* relational_op: ">="  */
#line 5150 "parser_bison.y"
                                                { (yyval.val) = OP_GTE; }
#line 14607 "parser_bison.c"
    break;

  case 925: /* relational_op: "<="  */
#line 5151 "parser_bison.y"
                                                { (yyval.val) = OP_LTE; }
#line 14613 "parser_bison.c"
    break;

  case 926: /* relational_op: "!"  */
#line 5152 "parser_bison.y"
                                                { (yyval.val) = OP_NEG; }
#line 14619 "parser_bison.c"
    break;

  case 927: /* verdict_expr: "accept"  */
#line 5156 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 14627 "parser_bison.c"
    break;

  case 928: /* verdict_expr: "drop"  */
#line 5160 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 14635 "parser_bison.c"
    break;

  case 929: /* verdict_expr: "continue"  */
#line 5164 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 14643 "parser_bison.c"
    break;

  case 930: /* verdict_expr: "jump" chain_expr  */
#line 5168 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 14651 "parser_bison.c"
    break;

  case 931: /* verdict_expr: "goto" chain_expr  */
#line 5172 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 14659 "parser_bison.c"
    break;

  case 932: /* verdict_expr: "return"  */
#line 5176 "parser_bison.y"
                        {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 14667 "parser_bison.c"
    break;

  case 934: /* chain_expr: identifier  */
#line 5183 "parser_bison.y"
                        {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 14679 "parser_bison.c"
    break;

  case 935: /* meta_expr: "meta" meta_key close_scope_meta  */
#line 5193 "parser_bison.y"
                        {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[-1].val));
			}
#line 14687 "parser_bison.c"
    break;

  case 936: /* meta_expr: meta_key_unqualified  */
#line 5197 "parser_bison.y"
                        {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 14695 "parser_bison.c"
    break;

  case 937: /* meta_expr: "meta" "string" close_scope_meta  */
#line 5201 "parser_bison.y"
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
#line 14713 "parser_bison.c"
    break;

  case 940: /* meta_key_qualified: "length"  */
#line 5220 "parser_bison.y"
                                                { (yyval.val) = NFT_META_LEN; }
#line 14719 "parser_bison.c"
    break;

  case 941: /* meta_key_qualified: "protocol"  */
#line 5221 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PROTOCOL; }
#line 14725 "parser_bison.c"
    break;

  case 942: /* meta_key_qualified: "priority"  */
#line 5222 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PRIORITY; }
#line 14731 "parser_bison.c"
    break;

  case 943: /* meta_key_qualified: "random"  */
#line 5223 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PRANDOM; }
#line 14737 "parser_bison.c"
    break;

  case 944: /* meta_key_qualified: "secmark" close_scope_secmark  */
#line 5224 "parser_bison.y"
                                                            { (yyval.val) = NFT_META_SECMARK; }
#line 14743 "parser_bison.c"
    break;

  case 945: /* meta_key_unqualified: "mark"  */
#line 5227 "parser_bison.y"
                                                { (yyval.val) = NFT_META_MARK; }
#line 14749 "parser_bison.c"
    break;

  case 946: /* meta_key_unqualified: "iif"  */
#line 5228 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIF; }
#line 14755 "parser_bison.c"
    break;

  case 947: /* meta_key_unqualified: "iifname"  */
#line 5229 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFNAME; }
#line 14761 "parser_bison.c"
    break;

  case 948: /* meta_key_unqualified: "iiftype"  */
#line 5230 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFTYPE; }
#line 14767 "parser_bison.c"
    break;

  case 949: /* meta_key_unqualified: "oif"  */
#line 5231 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIF; }
#line 14773 "parser_bison.c"
    break;

  case 950: /* meta_key_unqualified: "oifname"  */
#line 5232 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFNAME; }
#line 14779 "parser_bison.c"
    break;

  case 951: /* meta_key_unqualified: "oiftype"  */
#line 5233 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFTYPE; }
#line 14785 "parser_bison.c"
    break;

  case 952: /* meta_key_unqualified: "skuid"  */
#line 5234 "parser_bison.y"
                                                { (yyval.val) = NFT_META_SKUID; }
#line 14791 "parser_bison.c"
    break;

  case 953: /* meta_key_unqualified: "skgid"  */
#line 5235 "parser_bison.y"
                                                { (yyval.val) = NFT_META_SKGID; }
#line 14797 "parser_bison.c"
    break;

  case 954: /* meta_key_unqualified: "nftrace"  */
#line 5236 "parser_bison.y"
                                                { (yyval.val) = NFT_META_NFTRACE; }
#line 14803 "parser_bison.c"
    break;

  case 955: /* meta_key_unqualified: "rtclassid"  */
#line 5237 "parser_bison.y"
                                                { (yyval.val) = NFT_META_RTCLASSID; }
#line 14809 "parser_bison.c"
    break;

  case 956: /* meta_key_unqualified: "ibriport"  */
#line 5238 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 14815 "parser_bison.c"
    break;

  case 957: /* meta_key_unqualified: "obriport"  */
#line 5239 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 14821 "parser_bison.c"
    break;

  case 958: /* meta_key_unqualified: "ibrname"  */
#line 5240 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 14827 "parser_bison.c"
    break;

  case 959: /* meta_key_unqualified: "obrname"  */
#line 5241 "parser_bison.y"
                                                { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 14833 "parser_bison.c"
    break;

  case 960: /* meta_key_unqualified: "pkttype"  */
#line 5242 "parser_bison.y"
                                                { (yyval.val) = NFT_META_PKTTYPE; }
#line 14839 "parser_bison.c"
    break;

  case 961: /* meta_key_unqualified: "cpu"  */
#line 5243 "parser_bison.y"
                                                { (yyval.val) = NFT_META_CPU; }
#line 14845 "parser_bison.c"
    break;

  case 962: /* meta_key_unqualified: "iifgroup"  */
#line 5244 "parser_bison.y"
                                                { (yyval.val) = NFT_META_IIFGROUP; }
#line 14851 "parser_bison.c"
    break;

  case 963: /* meta_key_unqualified: "oifgroup"  */
#line 5245 "parser_bison.y"
                                                { (yyval.val) = NFT_META_OIFGROUP; }
#line 14857 "parser_bison.c"
    break;

  case 964: /* meta_key_unqualified: "cgroup"  */
#line 5246 "parser_bison.y"
                                                { (yyval.val) = NFT_META_CGROUP; }
#line 14863 "parser_bison.c"
    break;

  case 965: /* meta_key_unqualified: "ipsec" close_scope_ipsec  */
#line 5247 "parser_bison.y"
                                                          { (yyval.val) = NFT_META_SECPATH; }
#line 14869 "parser_bison.c"
    break;

  case 966: /* meta_key_unqualified: "time"  */
#line 5248 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_NS; }
#line 14875 "parser_bison.c"
    break;

  case 967: /* meta_key_unqualified: "day"  */
#line 5249 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_DAY; }
#line 14881 "parser_bison.c"
    break;

  case 968: /* meta_key_unqualified: "hour"  */
#line 5250 "parser_bison.y"
                                                { (yyval.val) = NFT_META_TIME_HOUR; }
#line 14887 "parser_bison.c"
    break;

  case 969: /* meta_stmt: "meta" meta_key "set" stmt_expr close_scope_meta  */
#line 5254 "parser_bison.y"
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
#line 14911 "parser_bison.c"
    break;

  case 970: /* meta_stmt: meta_key_unqualified "set" stmt_expr  */
#line 5274 "parser_bison.y"
                        {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 14919 "parser_bison.c"
    break;

  case 971: /* meta_stmt: "meta" "string" "set" stmt_expr close_scope_meta  */
#line 5278 "parser_bison.y"
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
#line 14937 "parser_bison.c"
    break;

  case 972: /* meta_stmt: "notrack"  */
#line 5292 "parser_bison.y"
                        {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 14945 "parser_bison.c"
    break;

  case 973: /* meta_stmt: "flow" "offload" "@" string close_scope_at  */
#line 5296 "parser_bison.y"
                        {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[-1].string));
			}
#line 14953 "parser_bison.c"
    break;

  case 974: /* meta_stmt: "flow" "add" "@" string close_scope_at  */
#line 5300 "parser_bison.y"
                        {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[-1].string));
			}
#line 14961 "parser_bison.c"
    break;

  case 975: /* socket_expr: "socket" socket_key close_scope_socket  */
#line 5306 "parser_bison.y"
                        {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 14969 "parser_bison.c"
    break;

  case 976: /* socket_expr: "socket" "cgroupv2" "level" "number" close_scope_socket  */
#line 5310 "parser_bison.y"
                        {
				(yyval.expr) = socket_expr_alloc(&(yyloc), NFT_SOCKET_CGROUPV2, (yyvsp[-1].val));
			}
#line 14977 "parser_bison.c"
    break;

  case 977: /* socket_key: "transparent"  */
#line 5315 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 14983 "parser_bison.c"
    break;

  case 978: /* socket_key: "mark"  */
#line 5316 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_MARK; }
#line 14989 "parser_bison.c"
    break;

  case 979: /* socket_key: "wildcard"  */
#line 5317 "parser_bison.y"
                                                { (yyval.val) = NFT_SOCKET_WILDCARD; }
#line 14995 "parser_bison.c"
    break;

  case 980: /* offset_opt: %empty  */
#line 5320 "parser_bison.y"
                                                { (yyval.val) = 0; }
#line 15001 "parser_bison.c"
    break;

  case 981: /* offset_opt: "offset" "number"  */
#line 5321 "parser_bison.y"
                                                { (yyval.val) = (yyvsp[0].val); }
#line 15007 "parser_bison.c"
    break;

  case 982: /* numgen_type: "inc"  */
#line 5324 "parser_bison.y"
                                                { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 15013 "parser_bison.c"
    break;

  case 983: /* numgen_type: "random"  */
#line 5325 "parser_bison.y"
                                                { (yyval.val) = NFT_NG_RANDOM; }
#line 15019 "parser_bison.c"
    break;

  case 984: /* numgen_expr: "numgen" numgen_type "mod" "number" offset_opt close_scope_numgen  */
#line 5329 "parser_bison.y"
                        {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 15027 "parser_bison.c"
    break;

  case 985: /* xfrm_spnum: "spnum" "number"  */
#line 5334 "parser_bison.y"
                                            { (yyval.val) = (yyvsp[0].val); }
#line 15033 "parser_bison.c"
    break;

  case 986: /* xfrm_spnum: %empty  */
#line 5335 "parser_bison.y"
                                            { (yyval.val) = 0; }
#line 15039 "parser_bison.c"
    break;

  case 987: /* xfrm_dir: "in"  */
#line 5338 "parser_bison.y"
                                        { (yyval.val) = XFRM_POLICY_IN; }
#line 15045 "parser_bison.c"
    break;

  case 988: /* xfrm_dir: "out"  */
#line 5339 "parser_bison.y"
                                        { (yyval.val) = XFRM_POLICY_OUT; }
#line 15051 "parser_bison.c"
    break;

  case 989: /* xfrm_state_key: "spi"  */
#line 5342 "parser_bison.y"
                                    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 15057 "parser_bison.c"
    break;

  case 990: /* xfrm_state_key: "reqid"  */
#line 5343 "parser_bison.y"
                                      { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 15063 "parser_bison.c"
    break;

  case 991: /* xfrm_state_proto_key: "daddr"  */
#line 5346 "parser_bison.y"
                                                { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 15069 "parser_bison.c"
    break;

  case 992: /* xfrm_state_proto_key: "saddr"  */
#line 5347 "parser_bison.y"
                                                { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 15075 "parser_bison.c"
    break;

  case 993: /* xfrm_expr: "ipsec" xfrm_dir xfrm_spnum xfrm_state_key close_scope_ipsec  */
#line 5351 "parser_bison.y"
                        {
				if ((yyvsp[-2].val) > 255) {
					erec_queue(error(&(yylsp[-2]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 15087 "parser_bison.c"
    break;

  case 994: /* xfrm_expr: "ipsec" xfrm_dir xfrm_spnum nf_key_proto xfrm_state_proto_key close_scope_ipsec  */
#line 5359 "parser_bison.y"
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
#line 15116 "parser_bison.c"
    break;

  case 995: /* hash_expr: "jhash" expr "mod" "number" "seed" "number" offset_opt close_scope_hash  */
#line 5386 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-4].val), true, (yyvsp[-2].val), (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-6].expr);
			}
#line 15125 "parser_bison.c"
    break;

  case 996: /* hash_expr: "jhash" expr "mod" "number" offset_opt close_scope_hash  */
#line 5391 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-4].expr);
			}
#line 15134 "parser_bison.c"
    break;

  case 997: /* hash_expr: "symhash" "mod" "number" offset_opt close_scope_hash  */
#line 5396 "parser_bison.y"
                        {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_SYM);
			}
#line 15142 "parser_bison.c"
    break;

  case 998: /* nf_key_proto: "ip" close_scope_ip  */
#line 5401 "parser_bison.y"
                                                       { (yyval.val) = NFPROTO_IPV4; }
#line 15148 "parser_bison.c"
    break;

  case 999: /* nf_key_proto: "ip6" close_scope_ip6  */
#line 5402 "parser_bison.y"
                                                        { (yyval.val) = NFPROTO_IPV6; }
#line 15154 "parser_bison.c"
    break;

  case 1000: /* rt_expr: "rt" rt_key close_scope_rt  */
#line 5406 "parser_bison.y"
                        {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[-1].val), true);
			}
#line 15162 "parser_bison.c"
    break;

  case 1001: /* rt_expr: "rt" nf_key_proto rt_key close_scope_rt  */
#line 5410 "parser_bison.y"
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
#line 15184 "parser_bison.c"
    break;

  case 1002: /* rt_key: "classid"  */
#line 5429 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_CLASSID; }
#line 15190 "parser_bison.c"
    break;

  case 1003: /* rt_key: "nexthop"  */
#line 5430 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 15196 "parser_bison.c"
    break;

  case 1004: /* rt_key: "mtu"  */
#line 5431 "parser_bison.y"
                                                { (yyval.val) = NFT_RT_TCPMSS; }
#line 15202 "parser_bison.c"
    break;

  case 1005: /* rt_key: "ipsec" close_scope_ipsec  */
#line 5432 "parser_bison.y"
                                                          { (yyval.val) = NFT_RT_XFRM; }
#line 15208 "parser_bison.c"
    break;

  case 1006: /* ct_expr: "ct" ct_key close_scope_ct  */
#line 5436 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), -1);
			}
#line 15216 "parser_bison.c"
    break;

  case 1007: /* ct_expr: "ct" ct_dir ct_key_dir close_scope_ct  */
#line 5440 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 15224 "parser_bison.c"
    break;

  case 1008: /* ct_expr: "ct" ct_dir ct_key_proto_field close_scope_ct  */
#line 5444 "parser_bison.y"
                        {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 15232 "parser_bison.c"
    break;

  case 1009: /* ct_dir: "original"  */
#line 5449 "parser_bison.y"
                                                { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 15238 "parser_bison.c"
    break;

  case 1010: /* ct_dir: "reply"  */
#line 5450 "parser_bison.y"
                                                { (yyval.val) = IP_CT_DIR_REPLY; }
#line 15244 "parser_bison.c"
    break;

  case 1011: /* ct_key: "l3proto"  */
#line 5453 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 15250 "parser_bison.c"
    break;

  case 1012: /* ct_key: "protocol"  */
#line 5454 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTOCOL; }
#line 15256 "parser_bison.c"
    break;

  case 1013: /* ct_key: "mark"  */
#line 5455 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_MARK; }
#line 15262 "parser_bison.c"
    break;

  case 1014: /* ct_key: "state"  */
#line 5456 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_STATE; }
#line 15268 "parser_bison.c"
    break;

  case 1015: /* ct_key: "direction"  */
#line 5457 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DIRECTION; }
#line 15274 "parser_bison.c"
    break;

  case 1016: /* ct_key: "status"  */
#line 5458 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_STATUS; }
#line 15280 "parser_bison.c"
    break;

  case 1017: /* ct_key: "expiration"  */
#line 5459 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_EXPIRATION; }
#line 15286 "parser_bison.c"
    break;

  case 1018: /* ct_key: "helper"  */
#line 5460 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_HELPER; }
#line 15292 "parser_bison.c"
    break;

  case 1019: /* ct_key: "saddr"  */
#line 5461 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_SRC; }
#line 15298 "parser_bison.c"
    break;

  case 1020: /* ct_key: "daddr"  */
#line 5462 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DST; }
#line 15304 "parser_bison.c"
    break;

  case 1021: /* ct_key: "proto-src"  */
#line 5463 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 15310 "parser_bison.c"
    break;

  case 1022: /* ct_key: "proto-dst"  */
#line 5464 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_DST; }
#line 15316 "parser_bison.c"
    break;

  case 1023: /* ct_key: "label"  */
#line 5465 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_LABELS; }
#line 15322 "parser_bison.c"
    break;

  case 1024: /* ct_key: "event"  */
#line 5466 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_EVENTMASK; }
#line 15328 "parser_bison.c"
    break;

  case 1025: /* ct_key: "secmark" close_scope_secmark  */
#line 5467 "parser_bison.y"
                                                            { (yyval.val) = NFT_CT_SECMARK; }
#line 15334 "parser_bison.c"
    break;

  case 1026: /* ct_key: "id"  */
#line 5468 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_ID; }
#line 15340 "parser_bison.c"
    break;

  case 1028: /* ct_key_dir: "saddr"  */
#line 5472 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_SRC; }
#line 15346 "parser_bison.c"
    break;

  case 1029: /* ct_key_dir: "daddr"  */
#line 5473 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_DST; }
#line 15352 "parser_bison.c"
    break;

  case 1030: /* ct_key_dir: "l3proto"  */
#line 5474 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 15358 "parser_bison.c"
    break;

  case 1031: /* ct_key_dir: "protocol"  */
#line 5475 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTOCOL; }
#line 15364 "parser_bison.c"
    break;

  case 1032: /* ct_key_dir: "proto-src"  */
#line 5476 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 15370 "parser_bison.c"
    break;

  case 1033: /* ct_key_dir: "proto-dst"  */
#line 5477 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PROTO_DST; }
#line 15376 "parser_bison.c"
    break;

  case 1035: /* ct_key_proto_field: "ip" "saddr" close_scope_ip  */
#line 5481 "parser_bison.y"
                                                               { (yyval.val) = NFT_CT_SRC_IP; }
#line 15382 "parser_bison.c"
    break;

  case 1036: /* ct_key_proto_field: "ip" "daddr" close_scope_ip  */
#line 5482 "parser_bison.y"
                                                               { (yyval.val) = NFT_CT_DST_IP; }
#line 15388 "parser_bison.c"
    break;

  case 1037: /* ct_key_proto_field: "ip6" "saddr" close_scope_ip6  */
#line 5483 "parser_bison.y"
                                                                { (yyval.val) = NFT_CT_SRC_IP6; }
#line 15394 "parser_bison.c"
    break;

  case 1038: /* ct_key_proto_field: "ip6" "daddr" close_scope_ip6  */
#line 5484 "parser_bison.y"
                                                                { (yyval.val) = NFT_CT_DST_IP6; }
#line 15400 "parser_bison.c"
    break;

  case 1039: /* ct_key_dir_optional: "bytes"  */
#line 5487 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_BYTES; }
#line 15406 "parser_bison.c"
    break;

  case 1040: /* ct_key_dir_optional: "packets"  */
#line 5488 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_PKTS; }
#line 15412 "parser_bison.c"
    break;

  case 1041: /* ct_key_dir_optional: "avgpkt"  */
#line 5489 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_AVGPKT; }
#line 15418 "parser_bison.c"
    break;

  case 1042: /* ct_key_dir_optional: "zone"  */
#line 5490 "parser_bison.y"
                                                { (yyval.val) = NFT_CT_ZONE; }
#line 15424 "parser_bison.c"
    break;

  case 1045: /* list_stmt_expr: symbol_stmt_expr "comma" symbol_stmt_expr  */
#line 5498 "parser_bison.y"
                        {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 15434 "parser_bison.c"
    break;

  case 1046: /* list_stmt_expr: list_stmt_expr "comma" symbol_stmt_expr  */
#line 5504 "parser_bison.y"
                        {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 15444 "parser_bison.c"
    break;

  case 1047: /* ct_stmt: "ct" ct_key "set" stmt_expr close_scope_ct  */
#line 5512 "parser_bison.y"
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
#line 15461 "parser_bison.c"
    break;

  case 1048: /* ct_stmt: "ct" "timeout" "set" stmt_expr close_scope_ct  */
#line 5525 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);

			}
#line 15472 "parser_bison.c"
    break;

  case 1049: /* ct_stmt: "ct" "expectation" "set" stmt_expr close_scope_ct  */
#line 5532 "parser_bison.y"
                        {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 15482 "parser_bison.c"
    break;

  case 1050: /* ct_stmt: "ct" ct_dir ct_key_dir_optional "set" stmt_expr close_scope_ct  */
#line 5538 "parser_bison.y"
                        {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].val), (yyvsp[-1].expr));
			}
#line 15490 "parser_bison.c"
    break;

  case 1051: /* payload_stmt: payload_expr "set" stmt_expr  */
#line 5544 "parser_bison.y"
                        {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 15501 "parser_bison.c"
    break;

  case 1074: /* payload_raw_expr: "@" payload_base_spec "comma" "number" "comma" "number" close_scope_at  */
#line 5577 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-5].val), (yyvsp[-3].val), (yyvsp[-1].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 15512 "parser_bison.c"
    break;

  case 1075: /* payload_base_spec: "ll"  */
#line 5585 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 15518 "parser_bison.c"
    break;

  case 1076: /* payload_base_spec: "nh"  */
#line 5586 "parser_bison.y"
                                                { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 15524 "parser_bison.c"
    break;

  case 1077: /* payload_base_spec: "th" close_scope_th  */
#line 5587 "parser_bison.y"
                                                                { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 15530 "parser_bison.c"
    break;

  case 1078: /* payload_base_spec: "string"  */
#line 5589 "parser_bison.y"
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
#line 15545 "parser_bison.c"
    break;

  case 1079: /* eth_hdr_expr: "ether" eth_hdr_field close_scope_eth  */
#line 5602 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[-1].val));
			}
#line 15553 "parser_bison.c"
    break;

  case 1080: /* eth_hdr_field: "saddr"  */
#line 5607 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_SADDR; }
#line 15559 "parser_bison.c"
    break;

  case 1081: /* eth_hdr_field: "daddr"  */
#line 5608 "parser_bison.y"
                                                { (yyval.val) = ETHHDR_DADDR; }
#line 15565 "parser_bison.c"
    break;

  case 1082: /* eth_hdr_field: "type" close_scope_type  */
#line 5609 "parser_bison.y"
                                                                        { (yyval.val) = ETHHDR_TYPE; }
#line 15571 "parser_bison.c"
    break;

  case 1083: /* vlan_hdr_expr: "vlan" vlan_hdr_field close_scope_vlan  */
#line 5613 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[-1].val));
			}
#line 15579 "parser_bison.c"
    break;

  case 1084: /* vlan_hdr_field: "id"  */
#line 5618 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_VID; }
#line 15585 "parser_bison.c"
    break;

  case 1085: /* vlan_hdr_field: "cfi"  */
#line 5619 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_CFI; }
#line 15591 "parser_bison.c"
    break;

  case 1086: /* vlan_hdr_field: "dei"  */
#line 5620 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_DEI; }
#line 15597 "parser_bison.c"
    break;

  case 1087: /* vlan_hdr_field: "pcp"  */
#line 5621 "parser_bison.y"
                                                { (yyval.val) = VLANHDR_PCP; }
#line 15603 "parser_bison.c"
    break;

  case 1088: /* vlan_hdr_field: "type" close_scope_type  */
#line 5622 "parser_bison.y"
                                                                        { (yyval.val) = VLANHDR_TYPE; }
#line 15609 "parser_bison.c"
    break;

  case 1089: /* arp_hdr_expr: "arp" arp_hdr_field close_scope_arp  */
#line 5626 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[-1].val));
			}
#line 15617 "parser_bison.c"
    break;

  case 1090: /* arp_hdr_field: "htype"  */
#line 5631 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_HRD; }
#line 15623 "parser_bison.c"
    break;

  case 1091: /* arp_hdr_field: "ptype"  */
#line 5632 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_PRO; }
#line 15629 "parser_bison.c"
    break;

  case 1092: /* arp_hdr_field: "hlen"  */
#line 5633 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_HLN; }
#line 15635 "parser_bison.c"
    break;

  case 1093: /* arp_hdr_field: "plen"  */
#line 5634 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_PLN; }
#line 15641 "parser_bison.c"
    break;

  case 1094: /* arp_hdr_field: "operation"  */
#line 5635 "parser_bison.y"
                                                { (yyval.val) = ARPHDR_OP; }
#line 15647 "parser_bison.c"
    break;

  case 1095: /* arp_hdr_field: "saddr" "ether" close_scope_eth  */
#line 5636 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 15653 "parser_bison.c"
    break;

  case 1096: /* arp_hdr_field: "daddr" "ether" close_scope_eth  */
#line 5637 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 15659 "parser_bison.c"
    break;

  case 1097: /* arp_hdr_field: "saddr" "ip" close_scope_ip  */
#line 5638 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_SADDR_IP; }
#line 15665 "parser_bison.c"
    break;

  case 1098: /* arp_hdr_field: "daddr" "ip" close_scope_ip  */
#line 5639 "parser_bison.y"
                                                                { (yyval.val) = ARPHDR_DADDR_IP; }
#line 15671 "parser_bison.c"
    break;

  case 1099: /* ip_hdr_expr: "ip" ip_hdr_field close_scope_ip  */
#line 5643 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[-1].val));
			}
#line 15679 "parser_bison.c"
    break;

  case 1100: /* ip_hdr_expr: "ip" "option" ip_option_type ip_option_field close_scope_ip  */
#line 5647 "parser_bison.y"
                        {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val));
				if (!(yyval.expr)) {
					erec_queue(error(&(yylsp[-4]), "unknown ip option type/field"), state->msgs);
					YYERROR;
				}
			}
#line 15691 "parser_bison.c"
    break;

  case 1101: /* ip_hdr_expr: "ip" "option" ip_option_type close_scope_ip  */
#line 5655 "parser_bison.y"
                        {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), IPOPT_FIELD_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 15700 "parser_bison.c"
    break;

  case 1102: /* ip_hdr_field: "version"  */
#line 5661 "parser_bison.y"
                                                { (yyval.val) = IPHDR_VERSION; }
#line 15706 "parser_bison.c"
    break;

  case 1103: /* ip_hdr_field: "hdrlength"  */
#line 5662 "parser_bison.y"
                                                { (yyval.val) = IPHDR_HDRLENGTH; }
#line 15712 "parser_bison.c"
    break;

  case 1104: /* ip_hdr_field: "dscp"  */
#line 5663 "parser_bison.y"
                                                { (yyval.val) = IPHDR_DSCP; }
#line 15718 "parser_bison.c"
    break;

  case 1105: /* ip_hdr_field: "ecn"  */
#line 5664 "parser_bison.y"
                                                { (yyval.val) = IPHDR_ECN; }
#line 15724 "parser_bison.c"
    break;

  case 1106: /* ip_hdr_field: "length"  */
#line 5665 "parser_bison.y"
                                                { (yyval.val) = IPHDR_LENGTH; }
#line 15730 "parser_bison.c"
    break;

  case 1107: /* ip_hdr_field: "id"  */
#line 5666 "parser_bison.y"
                                                { (yyval.val) = IPHDR_ID; }
#line 15736 "parser_bison.c"
    break;

  case 1108: /* ip_hdr_field: "frag-off"  */
#line 5667 "parser_bison.y"
                                                { (yyval.val) = IPHDR_FRAG_OFF; }
#line 15742 "parser_bison.c"
    break;

  case 1109: /* ip_hdr_field: "ttl"  */
#line 5668 "parser_bison.y"
                                                { (yyval.val) = IPHDR_TTL; }
#line 15748 "parser_bison.c"
    break;

  case 1110: /* ip_hdr_field: "protocol"  */
#line 5669 "parser_bison.y"
                                                { (yyval.val) = IPHDR_PROTOCOL; }
#line 15754 "parser_bison.c"
    break;

  case 1111: /* ip_hdr_field: "checksum"  */
#line 5670 "parser_bison.y"
                                                { (yyval.val) = IPHDR_CHECKSUM; }
#line 15760 "parser_bison.c"
    break;

  case 1112: /* ip_hdr_field: "saddr"  */
#line 5671 "parser_bison.y"
                                                { (yyval.val) = IPHDR_SADDR; }
#line 15766 "parser_bison.c"
    break;

  case 1113: /* ip_hdr_field: "daddr"  */
#line 5672 "parser_bison.y"
                                                { (yyval.val) = IPHDR_DADDR; }
#line 15772 "parser_bison.c"
    break;

  case 1114: /* ip_option_type: "lsrr"  */
#line 5675 "parser_bison.y"
                                                { (yyval.val) = IPOPT_LSRR; }
#line 15778 "parser_bison.c"
    break;

  case 1115: /* ip_option_type: "rr"  */
#line 5676 "parser_bison.y"
                                                { (yyval.val) = IPOPT_RR; }
#line 15784 "parser_bison.c"
    break;

  case 1116: /* ip_option_type: "ssrr"  */
#line 5677 "parser_bison.y"
                                                { (yyval.val) = IPOPT_SSRR; }
#line 15790 "parser_bison.c"
    break;

  case 1117: /* ip_option_type: "ra"  */
#line 5678 "parser_bison.y"
                                                { (yyval.val) = IPOPT_RA; }
#line 15796 "parser_bison.c"
    break;

  case 1118: /* ip_option_field: "type" close_scope_type  */
#line 5681 "parser_bison.y"
                                                                        { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 15802 "parser_bison.c"
    break;

  case 1119: /* ip_option_field: "length"  */
#line 5682 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 15808 "parser_bison.c"
    break;

  case 1120: /* ip_option_field: "value"  */
#line 5683 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 15814 "parser_bison.c"
    break;

  case 1121: /* ip_option_field: "ptr"  */
#line 5684 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_PTR; }
#line 15820 "parser_bison.c"
    break;

  case 1122: /* ip_option_field: "addr"  */
#line 5685 "parser_bison.y"
                                                { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 15826 "parser_bison.c"
    break;

  case 1123: /* icmp_hdr_expr: "icmp" icmp_hdr_field close_scope_icmp  */
#line 5689 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[-1].val));
			}
#line 15834 "parser_bison.c"
    break;

  case 1124: /* icmp_hdr_field: "type" close_scope_type  */
#line 5694 "parser_bison.y"
                                                                        { (yyval.val) = ICMPHDR_TYPE; }
#line 15840 "parser_bison.c"
    break;

  case 1125: /* icmp_hdr_field: "code"  */
#line 5695 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_CODE; }
#line 15846 "parser_bison.c"
    break;

  case 1126: /* icmp_hdr_field: "checksum"  */
#line 5696 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 15852 "parser_bison.c"
    break;

  case 1127: /* icmp_hdr_field: "id"  */
#line 5697 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_ID; }
#line 15858 "parser_bison.c"
    break;

  case 1128: /* icmp_hdr_field: "seq"  */
#line 5698 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_SEQ; }
#line 15864 "parser_bison.c"
    break;

  case 1129: /* icmp_hdr_field: "gateway"  */
#line 5699 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_GATEWAY; }
#line 15870 "parser_bison.c"
    break;

  case 1130: /* icmp_hdr_field: "mtu"  */
#line 5700 "parser_bison.y"
                                                { (yyval.val) = ICMPHDR_MTU; }
#line 15876 "parser_bison.c"
    break;

  case 1131: /* igmp_hdr_expr: "igmp" igmp_hdr_field close_scope_igmp  */
#line 5704 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[-1].val));
			}
#line 15884 "parser_bison.c"
    break;

  case 1132: /* igmp_hdr_field: "type" close_scope_type  */
#line 5709 "parser_bison.y"
                                                                        { (yyval.val) = IGMPHDR_TYPE; }
#line 15890 "parser_bison.c"
    break;

  case 1133: /* igmp_hdr_field: "checksum"  */
#line 5710 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 15896 "parser_bison.c"
    break;

  case 1134: /* igmp_hdr_field: "mrt"  */
#line 5711 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_MRT; }
#line 15902 "parser_bison.c"
    break;

  case 1135: /* igmp_hdr_field: "group"  */
#line 5712 "parser_bison.y"
                                                { (yyval.val) = IGMPHDR_GROUP; }
#line 15908 "parser_bison.c"
    break;

  case 1136: /* ip6_hdr_expr: "ip6" ip6_hdr_field close_scope_ip6  */
#line 5716 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[-1].val));
			}
#line 15916 "parser_bison.c"
    break;

  case 1137: /* ip6_hdr_field: "version"  */
#line 5721 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_VERSION; }
#line 15922 "parser_bison.c"
    break;

  case 1138: /* ip6_hdr_field: "dscp"  */
#line 5722 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_DSCP; }
#line 15928 "parser_bison.c"
    break;

  case 1139: /* ip6_hdr_field: "ecn"  */
#line 5723 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_ECN; }
#line 15934 "parser_bison.c"
    break;

  case 1140: /* ip6_hdr_field: "flowlabel"  */
#line 5724 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 15940 "parser_bison.c"
    break;

  case 1141: /* ip6_hdr_field: "length"  */
#line 5725 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_LENGTH; }
#line 15946 "parser_bison.c"
    break;

  case 1142: /* ip6_hdr_field: "nexthdr"  */
#line 5726 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_NEXTHDR; }
#line 15952 "parser_bison.c"
    break;

  case 1143: /* ip6_hdr_field: "hoplimit"  */
#line 5727 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 15958 "parser_bison.c"
    break;

  case 1144: /* ip6_hdr_field: "saddr"  */
#line 5728 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_SADDR; }
#line 15964 "parser_bison.c"
    break;

  case 1145: /* ip6_hdr_field: "daddr"  */
#line 5729 "parser_bison.y"
                                                { (yyval.val) = IP6HDR_DADDR; }
#line 15970 "parser_bison.c"
    break;

  case 1146: /* icmp6_hdr_expr: "icmpv6" icmp6_hdr_field close_scope_icmp  */
#line 5732 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[-1].val));
			}
#line 15978 "parser_bison.c"
    break;

  case 1147: /* icmp6_hdr_field: "type" close_scope_type  */
#line 5737 "parser_bison.y"
                                                                        { (yyval.val) = ICMP6HDR_TYPE; }
#line 15984 "parser_bison.c"
    break;

  case 1148: /* icmp6_hdr_field: "code"  */
#line 5738 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_CODE; }
#line 15990 "parser_bison.c"
    break;

  case 1149: /* icmp6_hdr_field: "checksum"  */
#line 5739 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 15996 "parser_bison.c"
    break;

  case 1150: /* icmp6_hdr_field: "param-problem"  */
#line 5740 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_PPTR; }
#line 16002 "parser_bison.c"
    break;

  case 1151: /* icmp6_hdr_field: "mtu"  */
#line 5741 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_MTU; }
#line 16008 "parser_bison.c"
    break;

  case 1152: /* icmp6_hdr_field: "id"  */
#line 5742 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_ID; }
#line 16014 "parser_bison.c"
    break;

  case 1153: /* icmp6_hdr_field: "seq"  */
#line 5743 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_SEQ; }
#line 16020 "parser_bison.c"
    break;

  case 1154: /* icmp6_hdr_field: "max-delay"  */
#line 5744 "parser_bison.y"
                                                { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 16026 "parser_bison.c"
    break;

  case 1155: /* auth_hdr_expr: "ah" auth_hdr_field close_scope_ah  */
#line 5748 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[-1].val));
			}
#line 16034 "parser_bison.c"
    break;

  case 1156: /* auth_hdr_field: "nexthdr"  */
#line 5753 "parser_bison.y"
                                                { (yyval.val) = AHHDR_NEXTHDR; }
#line 16040 "parser_bison.c"
    break;

  case 1157: /* auth_hdr_field: "hdrlength"  */
#line 5754 "parser_bison.y"
                                                { (yyval.val) = AHHDR_HDRLENGTH; }
#line 16046 "parser_bison.c"
    break;

  case 1158: /* auth_hdr_field: "reserved"  */
#line 5755 "parser_bison.y"
                                                { (yyval.val) = AHHDR_RESERVED; }
#line 16052 "parser_bison.c"
    break;

  case 1159: /* auth_hdr_field: "spi"  */
#line 5756 "parser_bison.y"
                                                { (yyval.val) = AHHDR_SPI; }
#line 16058 "parser_bison.c"
    break;

  case 1160: /* auth_hdr_field: "seq"  */
#line 5757 "parser_bison.y"
                                                { (yyval.val) = AHHDR_SEQUENCE; }
#line 16064 "parser_bison.c"
    break;

  case 1161: /* esp_hdr_expr: "esp" esp_hdr_field close_scope_esp  */
#line 5761 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[-1].val));
			}
#line 16072 "parser_bison.c"
    break;

  case 1162: /* esp_hdr_field: "spi"  */
#line 5766 "parser_bison.y"
                                                { (yyval.val) = ESPHDR_SPI; }
#line 16078 "parser_bison.c"
    break;

  case 1163: /* esp_hdr_field: "seq"  */
#line 5767 "parser_bison.y"
                                                { (yyval.val) = ESPHDR_SEQUENCE; }
#line 16084 "parser_bison.c"
    break;

  case 1164: /* comp_hdr_expr: "comp" comp_hdr_field close_scope_comp  */
#line 5771 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[-1].val));
			}
#line 16092 "parser_bison.c"
    break;

  case 1165: /* comp_hdr_field: "nexthdr"  */
#line 5776 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_NEXTHDR; }
#line 16098 "parser_bison.c"
    break;

  case 1166: /* comp_hdr_field: "flags"  */
#line 5777 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_FLAGS; }
#line 16104 "parser_bison.c"
    break;

  case 1167: /* comp_hdr_field: "cpi"  */
#line 5778 "parser_bison.y"
                                                { (yyval.val) = COMPHDR_CPI; }
#line 16110 "parser_bison.c"
    break;

  case 1168: /* udp_hdr_expr: "udp" udp_hdr_field close_scope_udp  */
#line 5782 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[-1].val));
			}
#line 16118 "parser_bison.c"
    break;

  case 1169: /* udp_hdr_field: "sport"  */
#line 5787 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_SPORT; }
#line 16124 "parser_bison.c"
    break;

  case 1170: /* udp_hdr_field: "dport"  */
#line 5788 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_DPORT; }
#line 16130 "parser_bison.c"
    break;

  case 1171: /* udp_hdr_field: "length"  */
#line 5789 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_LENGTH; }
#line 16136 "parser_bison.c"
    break;

  case 1172: /* udp_hdr_field: "checksum"  */
#line 5790 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_CHECKSUM; }
#line 16142 "parser_bison.c"
    break;

  case 1173: /* udplite_hdr_expr: "udplite" udplite_hdr_field close_scope_udplite  */
#line 5794 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[-1].val));
			}
#line 16150 "parser_bison.c"
    break;

  case 1174: /* udplite_hdr_field: "sport"  */
#line 5799 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_SPORT; }
#line 16156 "parser_bison.c"
    break;

  case 1175: /* udplite_hdr_field: "dport"  */
#line 5800 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_DPORT; }
#line 16162 "parser_bison.c"
    break;

  case 1176: /* udplite_hdr_field: "csumcov"  */
#line 5801 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_LENGTH; }
#line 16168 "parser_bison.c"
    break;

  case 1177: /* udplite_hdr_field: "checksum"  */
#line 5802 "parser_bison.y"
                                                { (yyval.val) = UDPHDR_CHECKSUM; }
#line 16174 "parser_bison.c"
    break;

  case 1178: /* tcp_hdr_expr: "tcp" tcp_hdr_field  */
#line 5806 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 16182 "parser_bison.c"
    break;

  case 1179: /* tcp_hdr_expr: "tcp" "option" tcp_hdr_option_type  */
#line 5810 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPT_COMMON_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 16191 "parser_bison.c"
    break;

  case 1180: /* tcp_hdr_expr: "tcp" "option" tcp_hdr_option_kind_and_field  */
#line 5815 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].tcp_kind_field).kind, (yyvsp[0].tcp_kind_field).field);
			}
#line 16199 "parser_bison.c"
    break;

  case 1181: /* tcp_hdr_expr: "tcp" "option" "@" close_scope_at tcp_hdr_option_type "comma" "number" "comma" "number"  */
#line 5819 "parser_bison.y"
                        {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-4].val), 0);
				tcpopt_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val), 0);
			}
#line 16208 "parser_bison.c"
    break;

  case 1201: /* vxlan_hdr_expr: "vxlan" vxlan_hdr_field  */
#line 5851 "parser_bison.y"
                        {
				struct expr *expr;

				expr = payload_expr_alloc(&(yyloc), &proto_vxlan, (yyvsp[0].val));
				expr->payload.inner_desc = &proto_vxlan;
				(yyval.expr) = expr;
			}
#line 16220 "parser_bison.c"
    break;

  case 1202: /* vxlan_hdr_expr: "vxlan" inner_expr  */
#line 5859 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->location = (yyloc);
				(yyval.expr)->payload.inner_desc = &proto_vxlan;
			}
#line 16230 "parser_bison.c"
    break;

  case 1203: /* vxlan_hdr_field: "vni"  */
#line 5866 "parser_bison.y"
                                                        { (yyval.val) = VXLANHDR_VNI; }
#line 16236 "parser_bison.c"
    break;

  case 1204: /* vxlan_hdr_field: "flags"  */
#line 5867 "parser_bison.y"
                                                        { (yyval.val) = VXLANHDR_FLAGS; }
#line 16242 "parser_bison.c"
    break;

  case 1205: /* geneve_hdr_expr: "geneve" geneve_hdr_field  */
#line 5871 "parser_bison.y"
                        {
				struct expr *expr;

				expr = payload_expr_alloc(&(yyloc), &proto_geneve, (yyvsp[0].val));
				expr->payload.inner_desc = &proto_geneve;
				(yyval.expr) = expr;
			}
#line 16254 "parser_bison.c"
    break;

  case 1206: /* geneve_hdr_expr: "geneve" inner_expr  */
#line 5879 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->location = (yyloc);
				(yyval.expr)->payload.inner_desc = &proto_geneve;
			}
#line 16264 "parser_bison.c"
    break;

  case 1207: /* geneve_hdr_field: "vni"  */
#line 5886 "parser_bison.y"
                                                        { (yyval.val) = GNVHDR_VNI; }
#line 16270 "parser_bison.c"
    break;

  case 1208: /* geneve_hdr_field: "type"  */
#line 5887 "parser_bison.y"
                                                        { (yyval.val) = GNVHDR_TYPE; }
#line 16276 "parser_bison.c"
    break;

  case 1209: /* gre_hdr_expr: "gre" gre_hdr_field close_scope_gre  */
#line 5891 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_gre, (yyvsp[-1].val));
			}
#line 16284 "parser_bison.c"
    break;

  case 1210: /* gre_hdr_expr: "gre" close_scope_gre inner_inet_expr  */
#line 5895 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->payload.inner_desc = &proto_gre;
			}
#line 16293 "parser_bison.c"
    break;

  case 1211: /* gre_hdr_field: "version"  */
#line 5901 "parser_bison.y"
                                                        { (yyval.val) = GREHDR_VERSION;	}
#line 16299 "parser_bison.c"
    break;

  case 1212: /* gre_hdr_field: "flags"  */
#line 5902 "parser_bison.y"
                                                        { (yyval.val) = GREHDR_FLAGS; }
#line 16305 "parser_bison.c"
    break;

  case 1213: /* gre_hdr_field: "protocol"  */
#line 5903 "parser_bison.y"
                                                        { (yyval.val) = GREHDR_PROTOCOL; }
#line 16311 "parser_bison.c"
    break;

  case 1214: /* gretap_hdr_expr: "gretap" close_scope_gre inner_expr  */
#line 5907 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[0].expr);
				(yyval.expr)->payload.inner_desc = &proto_gretap;
			}
#line 16320 "parser_bison.c"
    break;

  case 1215: /* optstrip_stmt: "reset" "tcp" "option" tcp_hdr_option_type close_scope_tcp  */
#line 5914 "parser_bison.y"
                        {
				(yyval.stmt) = optstrip_stmt_alloc(&(yyloc), tcpopt_expr_alloc(&(yyloc),
										(yyvsp[-1].val), TCPOPT_COMMON_KIND));
			}
#line 16329 "parser_bison.c"
    break;

  case 1216: /* tcp_hdr_field: "sport"  */
#line 5920 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_SPORT; }
#line 16335 "parser_bison.c"
    break;

  case 1217: /* tcp_hdr_field: "dport"  */
#line 5921 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_DPORT; }
#line 16341 "parser_bison.c"
    break;

  case 1218: /* tcp_hdr_field: "seq"  */
#line 5922 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_SEQ; }
#line 16347 "parser_bison.c"
    break;

  case 1219: /* tcp_hdr_field: "ackseq"  */
#line 5923 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_ACKSEQ; }
#line 16353 "parser_bison.c"
    break;

  case 1220: /* tcp_hdr_field: "doff"  */
#line 5924 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_DOFF; }
#line 16359 "parser_bison.c"
    break;

  case 1221: /* tcp_hdr_field: "reserved"  */
#line 5925 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_RESERVED; }
#line 16365 "parser_bison.c"
    break;

  case 1222: /* tcp_hdr_field: "flags"  */
#line 5926 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_FLAGS; }
#line 16371 "parser_bison.c"
    break;

  case 1223: /* tcp_hdr_field: "window"  */
#line 5927 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_WINDOW; }
#line 16377 "parser_bison.c"
    break;

  case 1224: /* tcp_hdr_field: "checksum"  */
#line 5928 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_CHECKSUM; }
#line 16383 "parser_bison.c"
    break;

  case 1225: /* tcp_hdr_field: "urgptr"  */
#line 5929 "parser_bison.y"
                                                { (yyval.val) = TCPHDR_URGPTR; }
#line 16389 "parser_bison.c"
    break;

  case 1226: /* tcp_hdr_option_kind_and_field: "mss" tcpopt_field_maxseg  */
#line 5933 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_MAXSEG, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16398 "parser_bison.c"
    break;

  case 1227: /* tcp_hdr_option_kind_and_field: tcp_hdr_option_sack tcpopt_field_sack  */
#line 5938 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = (yyvsp[-1].val), .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16407 "parser_bison.c"
    break;

  case 1228: /* tcp_hdr_option_kind_and_field: "window" tcpopt_field_window  */
#line 5943 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_WINDOW, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16416 "parser_bison.c"
    break;

  case 1229: /* tcp_hdr_option_kind_and_field: "timestamp" tcpopt_field_tsopt  */
#line 5948 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_TIMESTAMP, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16425 "parser_bison.c"
    break;

  case 1230: /* tcp_hdr_option_kind_and_field: tcp_hdr_option_type "length"  */
#line 5953 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = (yyvsp[-1].val), .field = TCPOPT_COMMON_LENGTH };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16434 "parser_bison.c"
    break;

  case 1231: /* tcp_hdr_option_kind_and_field: "mptcp" tcpopt_field_mptcp  */
#line 5958 "parser_bison.y"
                                {
					struct tcp_kind_field kind_field = { .kind = TCPOPT_KIND_MPTCP, .field = (yyvsp[0].val) };
					(yyval.tcp_kind_field) = kind_field;
				}
#line 16443 "parser_bison.c"
    break;

  case 1232: /* tcp_hdr_option_sack: "sack"  */
#line 5964 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK; }
#line 16449 "parser_bison.c"
    break;

  case 1233: /* tcp_hdr_option_sack: "sack0"  */
#line 5965 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK; }
#line 16455 "parser_bison.c"
    break;

  case 1234: /* tcp_hdr_option_sack: "sack1"  */
#line 5966 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK1; }
#line 16461 "parser_bison.c"
    break;

  case 1235: /* tcp_hdr_option_sack: "sack2"  */
#line 5967 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK2; }
#line 16467 "parser_bison.c"
    break;

  case 1236: /* tcp_hdr_option_sack: "sack3"  */
#line 5968 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_KIND_SACK3; }
#line 16473 "parser_bison.c"
    break;

  case 1237: /* tcp_hdr_option_type: "echo"  */
#line 5971 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_ECHO; }
#line 16479 "parser_bison.c"
    break;

  case 1238: /* tcp_hdr_option_type: "eol"  */
#line 5972 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_EOL; }
#line 16485 "parser_bison.c"
    break;

  case 1239: /* tcp_hdr_option_type: "fastopen"  */
#line 5973 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_FASTOPEN; }
#line 16491 "parser_bison.c"
    break;

  case 1240: /* tcp_hdr_option_type: "md5sig"  */
#line 5974 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MD5SIG; }
#line 16497 "parser_bison.c"
    break;

  case 1241: /* tcp_hdr_option_type: "mptcp"  */
#line 5975 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MPTCP; }
#line 16503 "parser_bison.c"
    break;

  case 1242: /* tcp_hdr_option_type: "mss"  */
#line 5976 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_MAXSEG; }
#line 16509 "parser_bison.c"
    break;

  case 1243: /* tcp_hdr_option_type: "nop"  */
#line 5977 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_NOP; }
#line 16515 "parser_bison.c"
    break;

  case 1244: /* tcp_hdr_option_type: "sack-permitted"  */
#line 5978 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_SACK_PERMITTED; }
#line 16521 "parser_bison.c"
    break;

  case 1245: /* tcp_hdr_option_type: "timestamp"  */
#line 5979 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_TIMESTAMP; }
#line 16527 "parser_bison.c"
    break;

  case 1246: /* tcp_hdr_option_type: "window"  */
#line 5980 "parser_bison.y"
                                                        { (yyval.val) = TCPOPT_KIND_WINDOW; }
#line 16533 "parser_bison.c"
    break;

  case 1247: /* tcp_hdr_option_type: tcp_hdr_option_sack  */
#line 5981 "parser_bison.y"
                                                        { (yyval.val) = (yyvsp[0].val); }
#line 16539 "parser_bison.c"
    break;

  case 1248: /* tcp_hdr_option_type: "number"  */
#line 5982 "parser_bison.y"
                                                        {
				if ((yyvsp[0].val) > 255) {
					erec_queue(error(&(yylsp[0]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[0].val);
			}
#line 16551 "parser_bison.c"
    break;

  case 1249: /* tcpopt_field_sack: "left"  */
#line 5991 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_SACK_LEFT; }
#line 16557 "parser_bison.c"
    break;

  case 1250: /* tcpopt_field_sack: "right"  */
#line 5992 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_SACK_RIGHT; }
#line 16563 "parser_bison.c"
    break;

  case 1251: /* tcpopt_field_window: "count"  */
#line 5995 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_WINDOW_COUNT; }
#line 16569 "parser_bison.c"
    break;

  case 1252: /* tcpopt_field_tsopt: "tsval"  */
#line 5998 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_TS_TSVAL; }
#line 16575 "parser_bison.c"
    break;

  case 1253: /* tcpopt_field_tsopt: "tsecr"  */
#line 5999 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_TS_TSECR; }
#line 16581 "parser_bison.c"
    break;

  case 1254: /* tcpopt_field_maxseg: "size"  */
#line 6002 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_MAXSEG_SIZE; }
#line 16587 "parser_bison.c"
    break;

  case 1255: /* tcpopt_field_mptcp: "subtype"  */
#line 6005 "parser_bison.y"
                                                { (yyval.val) = TCPOPT_MPTCP_SUBTYPE; }
#line 16593 "parser_bison.c"
    break;

  case 1256: /* dccp_hdr_expr: "dccp" dccp_hdr_field close_scope_dccp  */
#line 6009 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[-1].val));
			}
#line 16601 "parser_bison.c"
    break;

  case 1257: /* dccp_hdr_expr: "dccp" "option" "number" close_scope_dccp  */
#line 6013 "parser_bison.y"
                        {
				if ((yyvsp[-1].val) > DCCPOPT_TYPE_MAX) {
					erec_queue(error(&(yylsp[-3]), "value too large"),
						   state->msgs);
					YYERROR;
				}
				(yyval.expr) = dccpopt_expr_alloc(&(yyloc), (yyvsp[-1].val));
			}
#line 16614 "parser_bison.c"
    break;

  case 1258: /* dccp_hdr_field: "sport"  */
#line 6023 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_SPORT; }
#line 16620 "parser_bison.c"
    break;

  case 1259: /* dccp_hdr_field: "dport"  */
#line 6024 "parser_bison.y"
                                                { (yyval.val) = DCCPHDR_DPORT; }
#line 16626 "parser_bison.c"
    break;

  case 1260: /* dccp_hdr_field: "type" close_scope_type  */
#line 6025 "parser_bison.y"
                                                                        { (yyval.val) = DCCPHDR_TYPE; }
#line 16632 "parser_bison.c"
    break;

  case 1261: /* sctp_chunk_type: "data"  */
#line 6028 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_DATA; }
#line 16638 "parser_bison.c"
    break;

  case 1262: /* sctp_chunk_type: "init"  */
#line 6029 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_INIT; }
#line 16644 "parser_bison.c"
    break;

  case 1263: /* sctp_chunk_type: "init-ack"  */
#line 6030 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_INIT_ACK; }
#line 16650 "parser_bison.c"
    break;

  case 1264: /* sctp_chunk_type: "sack"  */
#line 6031 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SACK; }
#line 16656 "parser_bison.c"
    break;

  case 1265: /* sctp_chunk_type: "heartbeat"  */
#line 6032 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT; }
#line 16662 "parser_bison.c"
    break;

  case 1266: /* sctp_chunk_type: "heartbeat-ack"  */
#line 6033 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT_ACK; }
#line 16668 "parser_bison.c"
    break;

  case 1267: /* sctp_chunk_type: "abort"  */
#line 6034 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ABORT; }
#line 16674 "parser_bison.c"
    break;

  case 1268: /* sctp_chunk_type: "shutdown"  */
#line 6035 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN; }
#line 16680 "parser_bison.c"
    break;

  case 1269: /* sctp_chunk_type: "shutdown-ack"  */
#line 6036 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_ACK; }
#line 16686 "parser_bison.c"
    break;

  case 1270: /* sctp_chunk_type: "error"  */
#line 6037 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ERROR; }
#line 16692 "parser_bison.c"
    break;

  case 1271: /* sctp_chunk_type: "cookie-echo"  */
#line 6038 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ECHO; }
#line 16698 "parser_bison.c"
    break;

  case 1272: /* sctp_chunk_type: "cookie-ack"  */
#line 6039 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ACK; }
#line 16704 "parser_bison.c"
    break;

  case 1273: /* sctp_chunk_type: "ecne"  */
#line 6040 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ECNE; }
#line 16710 "parser_bison.c"
    break;

  case 1274: /* sctp_chunk_type: "cwr"  */
#line 6041 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_CWR; }
#line 16716 "parser_bison.c"
    break;

  case 1275: /* sctp_chunk_type: "shutdown-complete"  */
#line 6042 "parser_bison.y"
                                                  { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_COMPLETE; }
#line 16722 "parser_bison.c"
    break;

  case 1276: /* sctp_chunk_type: "asconf-ack"  */
#line 6043 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF_ACK; }
#line 16728 "parser_bison.c"
    break;

  case 1277: /* sctp_chunk_type: "forward-tsn"  */
#line 6044 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_FORWARD_TSN; }
#line 16734 "parser_bison.c"
    break;

  case 1278: /* sctp_chunk_type: "asconf"  */
#line 6045 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF; }
#line 16740 "parser_bison.c"
    break;

  case 1279: /* sctp_chunk_common_field: "type" close_scope_type  */
#line 6048 "parser_bison.y"
                                                                { (yyval.val) = SCTP_CHUNK_COMMON_TYPE; }
#line 16746 "parser_bison.c"
    break;

  case 1280: /* sctp_chunk_common_field: "flags"  */
#line 6049 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_FLAGS; }
#line 16752 "parser_bison.c"
    break;

  case 1281: /* sctp_chunk_common_field: "length"  */
#line 6050 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_COMMON_LENGTH; }
#line 16758 "parser_bison.c"
    break;

  case 1282: /* sctp_chunk_data_field: "tsn"  */
#line 6053 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_TSN; }
#line 16764 "parser_bison.c"
    break;

  case 1283: /* sctp_chunk_data_field: "stream"  */
#line 6054 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_STREAM; }
#line 16770 "parser_bison.c"
    break;

  case 1284: /* sctp_chunk_data_field: "ssn"  */
#line 6055 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_SSN; }
#line 16776 "parser_bison.c"
    break;

  case 1285: /* sctp_chunk_data_field: "ppid"  */
#line 6056 "parser_bison.y"
                                        { (yyval.val) = SCTP_CHUNK_DATA_PPID; }
#line 16782 "parser_bison.c"
    break;

  case 1286: /* sctp_chunk_init_field: "init-tag"  */
#line 6059 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_TAG; }
#line 16788 "parser_bison.c"
    break;

  case 1287: /* sctp_chunk_init_field: "a-rwnd"  */
#line 6060 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_RWND; }
#line 16794 "parser_bison.c"
    break;

  case 1288: /* sctp_chunk_init_field: "num-outbound-streams"  */
#line 6061 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_OSTREAMS; }
#line 16800 "parser_bison.c"
    break;

  case 1289: /* sctp_chunk_init_field: "num-inbound-streams"  */
#line 6062 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_ISTREAMS; }
#line 16806 "parser_bison.c"
    break;

  case 1290: /* sctp_chunk_init_field: "initial-tsn"  */
#line 6063 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_INIT_TSN; }
#line 16812 "parser_bison.c"
    break;

  case 1291: /* sctp_chunk_sack_field: "cum-tsn-ack"  */
#line 6066 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_CTSN_ACK; }
#line 16818 "parser_bison.c"
    break;

  case 1292: /* sctp_chunk_sack_field: "a-rwnd"  */
#line 6067 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_RWND; }
#line 16824 "parser_bison.c"
    break;

  case 1293: /* sctp_chunk_sack_field: "num-gap-ack-blocks"  */
#line 6068 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_GACK_BLOCKS; }
#line 16830 "parser_bison.c"
    break;

  case 1294: /* sctp_chunk_sack_field: "num-dup-tsns"  */
#line 6069 "parser_bison.y"
                                                { (yyval.val) = SCTP_CHUNK_SACK_DUP_TSNS; }
#line 16836 "parser_bison.c"
    break;

  case 1295: /* sctp_chunk_alloc: sctp_chunk_type  */
#line 6073 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[0].val), SCTP_CHUNK_COMMON_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 16845 "parser_bison.c"
    break;

  case 1296: /* sctp_chunk_alloc: sctp_chunk_type sctp_chunk_common_field  */
#line 6078 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 16853 "parser_bison.c"
    break;

  case 1297: /* sctp_chunk_alloc: "data" sctp_chunk_data_field  */
#line 6082 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_DATA, (yyvsp[0].val));
			}
#line 16861 "parser_bison.c"
    break;

  case 1298: /* sctp_chunk_alloc: "init" sctp_chunk_init_field  */
#line 6086 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT, (yyvsp[0].val));
			}
#line 16869 "parser_bison.c"
    break;

  case 1299: /* sctp_chunk_alloc: "init-ack" sctp_chunk_init_field  */
#line 6090 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT_ACK, (yyvsp[0].val));
			}
#line 16877 "parser_bison.c"
    break;

  case 1300: /* sctp_chunk_alloc: "sack" sctp_chunk_sack_field  */
#line 6094 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SACK, (yyvsp[0].val));
			}
#line 16885 "parser_bison.c"
    break;

  case 1301: /* sctp_chunk_alloc: "shutdown" "cum-tsn-ack"  */
#line 6098 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SHUTDOWN,
							   SCTP_CHUNK_SHUTDOWN_CTSN_ACK);
			}
#line 16894 "parser_bison.c"
    break;

  case 1302: /* sctp_chunk_alloc: "ecne" "lowest-tsn"  */
#line 6103 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ECNE,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 16903 "parser_bison.c"
    break;

  case 1303: /* sctp_chunk_alloc: "cwr" "lowest-tsn"  */
#line 6108 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_CWR,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 16912 "parser_bison.c"
    break;

  case 1304: /* sctp_chunk_alloc: "asconf-ack" "seqno"  */
#line 6113 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF_ACK,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 16921 "parser_bison.c"
    break;

  case 1305: /* sctp_chunk_alloc: "forward-tsn" "new-cum-tsn"  */
#line 6118 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_FORWARD_TSN,
							   SCTP_CHUNK_FORWARD_TSN_NCTSN);
			}
#line 16930 "parser_bison.c"
    break;

  case 1306: /* sctp_chunk_alloc: "asconf" "seqno"  */
#line 6123 "parser_bison.y"
                        {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 16939 "parser_bison.c"
    break;

  case 1307: /* sctp_hdr_expr: "sctp" sctp_hdr_field close_scope_sctp  */
#line 6130 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[-1].val));
			}
#line 16947 "parser_bison.c"
    break;

  case 1308: /* sctp_hdr_expr: "sctp" "chunk" sctp_chunk_alloc close_scope_sctp_chunk close_scope_sctp  */
#line 6134 "parser_bison.y"
                        {
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 16955 "parser_bison.c"
    break;

  case 1309: /* sctp_hdr_field: "sport"  */
#line 6139 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_SPORT; }
#line 16961 "parser_bison.c"
    break;

  case 1310: /* sctp_hdr_field: "dport"  */
#line 6140 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_DPORT; }
#line 16967 "parser_bison.c"
    break;

  case 1311: /* sctp_hdr_field: "vtag"  */
#line 6141 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_VTAG; }
#line 16973 "parser_bison.c"
    break;

  case 1312: /* sctp_hdr_field: "checksum"  */
#line 6142 "parser_bison.y"
                                                { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 16979 "parser_bison.c"
    break;

  case 1313: /* th_hdr_expr: "th" th_hdr_field close_scope_th  */
#line 6146 "parser_bison.y"
                        {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[-1].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 16989 "parser_bison.c"
    break;

  case 1314: /* th_hdr_field: "sport"  */
#line 6153 "parser_bison.y"
                                                { (yyval.val) = THDR_SPORT; }
#line 16995 "parser_bison.c"
    break;

  case 1315: /* th_hdr_field: "dport"  */
#line 6154 "parser_bison.y"
                                                { (yyval.val) = THDR_DPORT; }
#line 17001 "parser_bison.c"
    break;

  case 1324: /* hbh_hdr_expr: "hbh" hbh_hdr_field close_scope_hbh  */
#line 6168 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[-1].val));
			}
#line 17009 "parser_bison.c"
    break;

  case 1325: /* hbh_hdr_field: "nexthdr"  */
#line 6173 "parser_bison.y"
                                                { (yyval.val) = HBHHDR_NEXTHDR; }
#line 17015 "parser_bison.c"
    break;

  case 1326: /* hbh_hdr_field: "hdrlength"  */
#line 6174 "parser_bison.y"
                                                { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 17021 "parser_bison.c"
    break;

  case 1327: /* rt_hdr_expr: "rt" rt_hdr_field close_scope_rt  */
#line 6178 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[-1].val));
			}
#line 17029 "parser_bison.c"
    break;

  case 1328: /* rt_hdr_field: "nexthdr"  */
#line 6183 "parser_bison.y"
                                                { (yyval.val) = RTHDR_NEXTHDR; }
#line 17035 "parser_bison.c"
    break;

  case 1329: /* rt_hdr_field: "hdrlength"  */
#line 6184 "parser_bison.y"
                                                { (yyval.val) = RTHDR_HDRLENGTH; }
#line 17041 "parser_bison.c"
    break;

  case 1330: /* rt_hdr_field: "type" close_scope_type  */
#line 6185 "parser_bison.y"
                                                                        { (yyval.val) = RTHDR_TYPE; }
#line 17047 "parser_bison.c"
    break;

  case 1331: /* rt_hdr_field: "seg-left"  */
#line 6186 "parser_bison.y"
                                                { (yyval.val) = RTHDR_SEG_LEFT; }
#line 17053 "parser_bison.c"
    break;

  case 1332: /* rt0_hdr_expr: "rt0" rt0_hdr_field close_scope_rt  */
#line 6190 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[-1].val));
			}
#line 17061 "parser_bison.c"
    break;

  case 1333: /* rt0_hdr_field: "addr" '[' "number" ']'  */
#line 6196 "parser_bison.y"
                        {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 17069 "parser_bison.c"
    break;

  case 1334: /* rt2_hdr_expr: "rt2" rt2_hdr_field close_scope_rt  */
#line 6202 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[-1].val));
			}
#line 17077 "parser_bison.c"
    break;

  case 1335: /* rt2_hdr_field: "addr"  */
#line 6207 "parser_bison.y"
                                                { (yyval.val) = RT2HDR_ADDR; }
#line 17083 "parser_bison.c"
    break;

  case 1336: /* rt4_hdr_expr: "srh" rt4_hdr_field close_scope_rt  */
#line 6211 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[-1].val));
			}
#line 17091 "parser_bison.c"
    break;

  case 1337: /* rt4_hdr_field: "last-entry"  */
#line 6216 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_LASTENT; }
#line 17097 "parser_bison.c"
    break;

  case 1338: /* rt4_hdr_field: "flags"  */
#line 6217 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_FLAGS; }
#line 17103 "parser_bison.c"
    break;

  case 1339: /* rt4_hdr_field: "tag"  */
#line 6218 "parser_bison.y"
                                                { (yyval.val) = RT4HDR_TAG; }
#line 17109 "parser_bison.c"
    break;

  case 1340: /* rt4_hdr_field: "sid" '[' "number" ']'  */
#line 6220 "parser_bison.y"
                        {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 17117 "parser_bison.c"
    break;

  case 1341: /* frag_hdr_expr: "frag" frag_hdr_field close_scope_frag  */
#line 6226 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[-1].val));
			}
#line 17125 "parser_bison.c"
    break;

  case 1342: /* frag_hdr_field: "nexthdr"  */
#line 6231 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 17131 "parser_bison.c"
    break;

  case 1343: /* frag_hdr_field: "reserved"  */
#line 6232 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_RESERVED; }
#line 17137 "parser_bison.c"
    break;

  case 1344: /* frag_hdr_field: "frag-off"  */
#line 6233 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 17143 "parser_bison.c"
    break;

  case 1345: /* frag_hdr_field: "reserved2"  */
#line 6234 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_RESERVED2; }
#line 17149 "parser_bison.c"
    break;

  case 1346: /* frag_hdr_field: "more-fragments"  */
#line 6235 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_MFRAGS; }
#line 17155 "parser_bison.c"
    break;

  case 1347: /* frag_hdr_field: "id"  */
#line 6236 "parser_bison.y"
                                                { (yyval.val) = FRAGHDR_ID; }
#line 17161 "parser_bison.c"
    break;

  case 1348: /* dst_hdr_expr: "dst" dst_hdr_field close_scope_dst  */
#line 6240 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[-1].val));
			}
#line 17169 "parser_bison.c"
    break;

  case 1349: /* dst_hdr_field: "nexthdr"  */
#line 6245 "parser_bison.y"
                                                { (yyval.val) = DSTHDR_NEXTHDR; }
#line 17175 "parser_bison.c"
    break;

  case 1350: /* dst_hdr_field: "hdrlength"  */
#line 6246 "parser_bison.y"
                                                { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 17181 "parser_bison.c"
    break;

  case 1351: /* mh_hdr_expr: "mh" mh_hdr_field close_scope_mh  */
#line 6250 "parser_bison.y"
                        {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[-1].val));
			}
#line 17189 "parser_bison.c"
    break;

  case 1352: /* mh_hdr_field: "nexthdr"  */
#line 6255 "parser_bison.y"
                                                { (yyval.val) = MHHDR_NEXTHDR; }
#line 17195 "parser_bison.c"
    break;

  case 1353: /* mh_hdr_field: "hdrlength"  */
#line 6256 "parser_bison.y"
                                                { (yyval.val) = MHHDR_HDRLENGTH; }
#line 17201 "parser_bison.c"
    break;

  case 1354: /* mh_hdr_field: "type" close_scope_type  */
#line 6257 "parser_bison.y"
                                                                        { (yyval.val) = MHHDR_TYPE; }
#line 17207 "parser_bison.c"
    break;

  case 1355: /* mh_hdr_field: "reserved"  */
#line 6258 "parser_bison.y"
                                                { (yyval.val) = MHHDR_RESERVED; }
#line 17213 "parser_bison.c"
    break;

  case 1356: /* mh_hdr_field: "checksum"  */
#line 6259 "parser_bison.y"
                                                { (yyval.val) = MHHDR_CHECKSUM; }
#line 17219 "parser_bison.c"
    break;

  case 1357: /* exthdr_exists_expr: "exthdr" exthdr_key  */
#line 6263 "parser_bison.y"
                        {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the first one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 17235 "parser_bison.c"
    break;

  case 1358: /* exthdr_key: "hbh" close_scope_hbh  */
#line 6276 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_HOPOPTS; }
#line 17241 "parser_bison.c"
    break;

  case 1359: /* exthdr_key: "rt" close_scope_rt  */
#line 6277 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_ROUTING; }
#line 17247 "parser_bison.c"
    break;

  case 1360: /* exthdr_key: "frag" close_scope_frag  */
#line 6278 "parser_bison.y"
                                                                { (yyval.val) = IPPROTO_FRAGMENT; }
#line 17253 "parser_bison.c"
    break;

  case 1361: /* exthdr_key: "dst" close_scope_dst  */
#line 6279 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_DSTOPTS; }
#line 17259 "parser_bison.c"
    break;

  case 1362: /* exthdr_key: "mh" close_scope_mh  */
#line 6280 "parser_bison.y"
                                                        { (yyval.val) = IPPROTO_MH; }
#line 17265 "parser_bison.c"
    break;


#line 17269 "parser_bison.c"

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

#line 6283 "parser_bison.y"

