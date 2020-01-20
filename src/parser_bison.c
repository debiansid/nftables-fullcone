/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

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
#line 11 "parser_bison.y" /* yacc.c:337  */


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

#define YYLLOC_DEFAULT(Current, Rhs, N)	location_update(&Current, Rhs, N)

#define symbol_value(loc, str) \
	symbol_expr_alloc(loc, SYMBOL_VALUE, current_scope(state), str)

/* Declare those here to avoid compiler warnings */
void nft_set_debug(int, void *);
int nft_lex(void *, void *, void *);

#line 180 "parser_bison.c" /* yacc.c:337  */
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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_NFT_PARSER_BISON_H_INCLUDED
# define YY_NFT_PARSER_BISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int nft_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_EOF = 0,
    JUNK = 258,
    NEWLINE = 259,
    COLON = 260,
    SEMICOLON = 261,
    COMMA = 262,
    DOT = 263,
    EQ = 264,
    NEQ = 265,
    LT = 266,
    GT = 267,
    GTE = 268,
    LTE = 269,
    LSHIFT = 270,
    RSHIFT = 271,
    AMPERSAND = 272,
    CARET = 273,
    NOT = 274,
    SLASH = 275,
    ASTERISK = 276,
    DASH = 277,
    AT = 278,
    VMAP = 279,
    PLUS = 280,
    INCLUDE = 281,
    DEFINE = 282,
    REDEFINE = 283,
    UNDEFINE = 284,
    FIB = 285,
    SOCKET = 286,
    TRANSPARENT = 287,
    TPROXY = 288,
    OSF = 289,
    SYNPROXY = 290,
    MSS = 291,
    WSCALE = 292,
    SACKPERM = 293,
    HOOK = 294,
    DEVICE = 295,
    DEVICES = 296,
    TABLE = 297,
    TABLES = 298,
    CHAIN = 299,
    CHAINS = 300,
    RULE = 301,
    RULES = 302,
    SETS = 303,
    SET = 304,
    ELEMENT = 305,
    MAP = 306,
    MAPS = 307,
    FLOWTABLE = 308,
    HANDLE = 309,
    RULESET = 310,
    TRACE = 311,
    INET = 312,
    NETDEV = 313,
    ADD = 314,
    UPDATE = 315,
    REPLACE = 316,
    CREATE = 317,
    INSERT = 318,
    DELETE = 319,
    GET = 320,
    LIST = 321,
    RESET = 322,
    FLUSH = 323,
    RENAME = 324,
    DESCRIBE = 325,
    IMPORT = 326,
    EXPORT = 327,
    MONITOR = 328,
    ALL = 329,
    ACCEPT = 330,
    DROP = 331,
    CONTINUE = 332,
    JUMP = 333,
    GOTO = 334,
    RETURN = 335,
    TO = 336,
    CONSTANT = 337,
    INTERVAL = 338,
    DYNAMIC = 339,
    AUTOMERGE = 340,
    TIMEOUT = 341,
    GC_INTERVAL = 342,
    ELEMENTS = 343,
    EXPIRES = 344,
    POLICY = 345,
    MEMORY = 346,
    PERFORMANCE = 347,
    SIZE = 348,
    FLOW = 349,
    OFFLOAD = 350,
    METER = 351,
    METERS = 352,
    FLOWTABLES = 353,
    NUM = 354,
    STRING = 355,
    QUOTED_STRING = 356,
    ASTERISK_STRING = 357,
    LL_HDR = 358,
    NETWORK_HDR = 359,
    TRANSPORT_HDR = 360,
    BRIDGE = 361,
    ETHER = 362,
    SADDR = 363,
    DADDR = 364,
    TYPE = 365,
    VLAN = 366,
    ID = 367,
    CFI = 368,
    PCP = 369,
    ARP = 370,
    HTYPE = 371,
    PTYPE = 372,
    HLEN = 373,
    PLEN = 374,
    OPERATION = 375,
    IP = 376,
    HDRVERSION = 377,
    HDRLENGTH = 378,
    DSCP = 379,
    ECN = 380,
    LENGTH = 381,
    FRAG_OFF = 382,
    TTL = 383,
    PROTOCOL = 384,
    CHECKSUM = 385,
    PTR = 386,
    VALUE = 387,
    LSRR = 388,
    RR = 389,
    SSRR = 390,
    RA = 391,
    ICMP = 392,
    CODE = 393,
    SEQUENCE = 394,
    GATEWAY = 395,
    MTU = 396,
    IGMP = 397,
    MRT = 398,
    OPTIONS = 399,
    IP6 = 400,
    PRIORITY = 401,
    FLOWLABEL = 402,
    NEXTHDR = 403,
    HOPLIMIT = 404,
    ICMP6 = 405,
    PPTR = 406,
    MAXDELAY = 407,
    AH = 408,
    RESERVED = 409,
    SPI = 410,
    ESP = 411,
    COMP = 412,
    FLAGS = 413,
    CPI = 414,
    UDP = 415,
    SPORT = 416,
    DPORT = 417,
    UDPLITE = 418,
    CSUMCOV = 419,
    TCP = 420,
    ACKSEQ = 421,
    DOFF = 422,
    WINDOW = 423,
    URGPTR = 424,
    OPTION = 425,
    ECHO = 426,
    EOL = 427,
    MAXSEG = 428,
    NOOP = 429,
    SACK = 430,
    SACK0 = 431,
    SACK1 = 432,
    SACK2 = 433,
    SACK3 = 434,
    SACK_PERMITTED = 435,
    TIMESTAMP = 436,
    KIND = 437,
    COUNT = 438,
    LEFT = 439,
    RIGHT = 440,
    TSVAL = 441,
    TSECR = 442,
    DCCP = 443,
    SCTP = 444,
    VTAG = 445,
    RT = 446,
    RT0 = 447,
    RT2 = 448,
    RT4 = 449,
    SEG_LEFT = 450,
    ADDR = 451,
    LAST_ENT = 452,
    TAG = 453,
    SID = 454,
    HBH = 455,
    FRAG = 456,
    RESERVED2 = 457,
    MORE_FRAGMENTS = 458,
    DST = 459,
    MH = 460,
    META = 461,
    MARK = 462,
    IIF = 463,
    IIFNAME = 464,
    IIFTYPE = 465,
    OIF = 466,
    OIFNAME = 467,
    OIFTYPE = 468,
    SKUID = 469,
    SKGID = 470,
    NFTRACE = 471,
    RTCLASSID = 472,
    IBRIPORT = 473,
    OBRIPORT = 474,
    IBRIDGENAME = 475,
    OBRIDGENAME = 476,
    PKTTYPE = 477,
    CPU = 478,
    IIFGROUP = 479,
    OIFGROUP = 480,
    CGROUP = 481,
    TIME = 482,
    CLASSID = 483,
    NEXTHOP = 484,
    CT = 485,
    L3PROTOCOL = 486,
    PROTO_SRC = 487,
    PROTO_DST = 488,
    ZONE = 489,
    DIRECTION = 490,
    EVENT = 491,
    EXPECTATION = 492,
    EXPIRATION = 493,
    HELPER = 494,
    LABEL = 495,
    STATE = 496,
    STATUS = 497,
    ORIGINAL = 498,
    REPLY = 499,
    COUNTER = 500,
    NAME = 501,
    PACKETS = 502,
    BYTES = 503,
    AVGPKT = 504,
    COUNTERS = 505,
    QUOTAS = 506,
    LIMITS = 507,
    SYNPROXYS = 508,
    HELPERS = 509,
    LOG = 510,
    PREFIX = 511,
    GROUP = 512,
    SNAPLEN = 513,
    QUEUE_THRESHOLD = 514,
    LEVEL = 515,
    LIMIT = 516,
    RATE = 517,
    BURST = 518,
    OVER = 519,
    UNTIL = 520,
    QUOTA = 521,
    USED = 522,
    SECMARK = 523,
    SECMARKS = 524,
    NANOSECOND = 525,
    MICROSECOND = 526,
    MILLISECOND = 527,
    SECOND = 528,
    MINUTE = 529,
    HOUR = 530,
    DAY = 531,
    WEEK = 532,
    _REJECT = 533,
    WITH = 534,
    ICMPX = 535,
    SNAT = 536,
    DNAT = 537,
    MASQUERADE = 538,
    REDIRECT = 539,
    RANDOM = 540,
    FULLY_RANDOM = 541,
    PERSISTENT = 542,
    QUEUE = 543,
    QUEUENUM = 544,
    BYPASS = 545,
    FANOUT = 546,
    DUP = 547,
    FWD = 548,
    NUMGEN = 549,
    INC = 550,
    MOD = 551,
    OFFSET = 552,
    JHASH = 553,
    SYMHASH = 554,
    SEED = 555,
    POSITION = 556,
    INDEX = 557,
    COMMENT = 558,
    XML = 559,
    JSON = 560,
    VM = 561,
    NOTRACK = 562,
    EXISTS = 563,
    MISSING = 564,
    EXTHDR = 565,
    IPSEC = 566,
    MODE = 567,
    REQID = 568,
    SPNUM = 569,
    TRANSPORT = 570,
    TUNNEL = 571,
    IN = 572,
    OUT = 573
  };
#endif
/* Tokens.  */
#define TOKEN_EOF 0
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
#define TPROXY 288
#define OSF 289
#define SYNPROXY 290
#define MSS 291
#define WSCALE 292
#define SACKPERM 293
#define HOOK 294
#define DEVICE 295
#define DEVICES 296
#define TABLE 297
#define TABLES 298
#define CHAIN 299
#define CHAINS 300
#define RULE 301
#define RULES 302
#define SETS 303
#define SET 304
#define ELEMENT 305
#define MAP 306
#define MAPS 307
#define FLOWTABLE 308
#define HANDLE 309
#define RULESET 310
#define TRACE 311
#define INET 312
#define NETDEV 313
#define ADD 314
#define UPDATE 315
#define REPLACE 316
#define CREATE 317
#define INSERT 318
#define DELETE 319
#define GET 320
#define LIST 321
#define RESET 322
#define FLUSH 323
#define RENAME 324
#define DESCRIBE 325
#define IMPORT 326
#define EXPORT 327
#define MONITOR 328
#define ALL 329
#define ACCEPT 330
#define DROP 331
#define CONTINUE 332
#define JUMP 333
#define GOTO 334
#define RETURN 335
#define TO 336
#define CONSTANT 337
#define INTERVAL 338
#define DYNAMIC 339
#define AUTOMERGE 340
#define TIMEOUT 341
#define GC_INTERVAL 342
#define ELEMENTS 343
#define EXPIRES 344
#define POLICY 345
#define MEMORY 346
#define PERFORMANCE 347
#define SIZE 348
#define FLOW 349
#define OFFLOAD 350
#define METER 351
#define METERS 352
#define FLOWTABLES 353
#define NUM 354
#define STRING 355
#define QUOTED_STRING 356
#define ASTERISK_STRING 357
#define LL_HDR 358
#define NETWORK_HDR 359
#define TRANSPORT_HDR 360
#define BRIDGE 361
#define ETHER 362
#define SADDR 363
#define DADDR 364
#define TYPE 365
#define VLAN 366
#define ID 367
#define CFI 368
#define PCP 369
#define ARP 370
#define HTYPE 371
#define PTYPE 372
#define HLEN 373
#define PLEN 374
#define OPERATION 375
#define IP 376
#define HDRVERSION 377
#define HDRLENGTH 378
#define DSCP 379
#define ECN 380
#define LENGTH 381
#define FRAG_OFF 382
#define TTL 383
#define PROTOCOL 384
#define CHECKSUM 385
#define PTR 386
#define VALUE 387
#define LSRR 388
#define RR 389
#define SSRR 390
#define RA 391
#define ICMP 392
#define CODE 393
#define SEQUENCE 394
#define GATEWAY 395
#define MTU 396
#define IGMP 397
#define MRT 398
#define OPTIONS 399
#define IP6 400
#define PRIORITY 401
#define FLOWLABEL 402
#define NEXTHDR 403
#define HOPLIMIT 404
#define ICMP6 405
#define PPTR 406
#define MAXDELAY 407
#define AH 408
#define RESERVED 409
#define SPI 410
#define ESP 411
#define COMP 412
#define FLAGS 413
#define CPI 414
#define UDP 415
#define SPORT 416
#define DPORT 417
#define UDPLITE 418
#define CSUMCOV 419
#define TCP 420
#define ACKSEQ 421
#define DOFF 422
#define WINDOW 423
#define URGPTR 424
#define OPTION 425
#define ECHO 426
#define EOL 427
#define MAXSEG 428
#define NOOP 429
#define SACK 430
#define SACK0 431
#define SACK1 432
#define SACK2 433
#define SACK3 434
#define SACK_PERMITTED 435
#define TIMESTAMP 436
#define KIND 437
#define COUNT 438
#define LEFT 439
#define RIGHT 440
#define TSVAL 441
#define TSECR 442
#define DCCP 443
#define SCTP 444
#define VTAG 445
#define RT 446
#define RT0 447
#define RT2 448
#define RT4 449
#define SEG_LEFT 450
#define ADDR 451
#define LAST_ENT 452
#define TAG 453
#define SID 454
#define HBH 455
#define FRAG 456
#define RESERVED2 457
#define MORE_FRAGMENTS 458
#define DST 459
#define MH 460
#define META 461
#define MARK 462
#define IIF 463
#define IIFNAME 464
#define IIFTYPE 465
#define OIF 466
#define OIFNAME 467
#define OIFTYPE 468
#define SKUID 469
#define SKGID 470
#define NFTRACE 471
#define RTCLASSID 472
#define IBRIPORT 473
#define OBRIPORT 474
#define IBRIDGENAME 475
#define OBRIDGENAME 476
#define PKTTYPE 477
#define CPU 478
#define IIFGROUP 479
#define OIFGROUP 480
#define CGROUP 481
#define TIME 482
#define CLASSID 483
#define NEXTHOP 484
#define CT 485
#define L3PROTOCOL 486
#define PROTO_SRC 487
#define PROTO_DST 488
#define ZONE 489
#define DIRECTION 490
#define EVENT 491
#define EXPECTATION 492
#define EXPIRATION 493
#define HELPER 494
#define LABEL 495
#define STATE 496
#define STATUS 497
#define ORIGINAL 498
#define REPLY 499
#define COUNTER 500
#define NAME 501
#define PACKETS 502
#define BYTES 503
#define AVGPKT 504
#define COUNTERS 505
#define QUOTAS 506
#define LIMITS 507
#define SYNPROXYS 508
#define HELPERS 509
#define LOG 510
#define PREFIX 511
#define GROUP 512
#define SNAPLEN 513
#define QUEUE_THRESHOLD 514
#define LEVEL 515
#define LIMIT 516
#define RATE 517
#define BURST 518
#define OVER 519
#define UNTIL 520
#define QUOTA 521
#define USED 522
#define SECMARK 523
#define SECMARKS 524
#define NANOSECOND 525
#define MICROSECOND 526
#define MILLISECOND 527
#define SECOND 528
#define MINUTE 529
#define HOUR 530
#define DAY 531
#define WEEK 532
#define _REJECT 533
#define WITH 534
#define ICMPX 535
#define SNAT 536
#define DNAT 537
#define MASQUERADE 538
#define REDIRECT 539
#define RANDOM 540
#define FULLY_RANDOM 541
#define PERSISTENT 542
#define QUEUE 543
#define QUEUENUM 544
#define BYPASS 545
#define FANOUT 546
#define DUP 547
#define FWD 548
#define NUMGEN 549
#define INC 550
#define MOD 551
#define OFFSET 552
#define JHASH 553
#define SYMHASH 554
#define SEED 555
#define POSITION 556
#define INDEX 557
#define COMMENT 558
#define XML 559
#define JSON 560
#define VM 561
#define NOTRACK 562
#define EXISTS 563
#define MISSING 564
#define EXTHDR 565
#define IPSEC 566
#define MODE 567
#define REQID 568
#define SPNUM 569
#define TRANSPORT 570
#define TUNNEL 571
#define IN 572
#define OUT 573

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 135 "parser_bison.y" /* yacc.c:352  */

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
	const struct exthdr_desc *exthdr_desc;

#line 886 "parser_bison.c" /* yacc.c:352  */
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



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   6265

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  328
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  335
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1062
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1717

#define YYUNDEFTOK  2
#define YYMAXUTOK   573

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   323,     2,     2,     2,
     324,   325,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   319,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   326,     2,   327,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   320,   322,   321,     2,     2,     2,     2,
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
     315,   316,   317,   318
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   808,   808,   809,   818,   819,   822,   823,   826,   834,
     848,   855,   866,   874,   875,   876,   877,   897,   898,   899,
     900,   901,   902,   903,   904,   905,   906,   907,   908,   909,
     910,   911,   914,   918,   925,   929,   937,   941,   945,   952,
     959,   963,   970,   979,   983,   987,   991,   995,   999,  1003,
    1007,  1013,  1019,  1023,  1030,  1034,  1042,  1049,  1056,  1060,
    1067,  1076,  1080,  1084,  1088,  1092,  1096,  1100,  1104,  1110,
    1116,  1120,  1124,  1128,  1132,  1136,  1140,  1144,  1148,  1152,
    1156,  1160,  1164,  1168,  1172,  1176,  1180,  1184,  1188,  1192,
    1196,  1200,  1206,  1212,  1216,  1220,  1224,  1228,  1232,  1236,
    1240,  1244,  1248,  1252,  1256,  1260,  1264,  1268,  1272,  1276,
    1280,  1284,  1288,  1292,  1296,  1300,  1304,  1308,  1312,  1316,
    1320,  1324,  1328,  1332,  1336,  1340,  1344,  1348,  1354,  1358,
    1362,  1366,  1370,  1374,  1380,  1384,  1388,  1392,  1396,  1400,
    1404,  1410,  1417,  1423,  1431,  1437,  1445,  1454,  1455,  1458,
    1459,  1460,  1461,  1462,  1463,  1464,  1465,  1468,  1469,  1472,
    1473,  1474,  1477,  1486,  1492,  1506,  1507,  1508,  1509,  1510,
    1521,  1531,  1542,  1552,  1563,  1574,  1583,  1592,  1601,  1612,
    1623,  1637,  1643,  1644,  1645,  1646,  1647,  1648,  1656,  1661,
    1662,  1663,  1664,  1669,  1674,  1679,  1684,  1689,  1694,  1697,
    1698,  1701,  1705,  1708,  1709,  1710,  1711,  1715,  1720,  1721,
    1722,  1723,  1728,  1739,  1748,  1757,  1766,  1775,  1780,  1785,
    1788,  1792,  1798,  1799,  1803,  1808,  1809,  1810,  1811,  1824,
    1830,  1837,  1842,  1847,  1850,  1859,  1871,  1878,  1879,  1899,
    1904,  1905,  1906,  1907,  1913,  1914,  1915,  1916,  1922,  1923,
    1924,  1925,  1931,  1932,  1933,  1934,  1940,  1941,  1942,  1943,
    1949,  1950,  1951,  1952,  1958,  1959,  1960,  1961,  1967,  1968,
    1969,  1970,  1976,  1977,  1978,  1979,  1980,  1983,  2011,  2018,
    2022,  2025,  2035,  2043,  2054,  2067,  2081,  2082,  2085,  2096,
    2100,  2103,  2115,  2120,  2129,  2130,  2133,  2136,  2137,  2138,
    2141,  2156,  2157,  2160,  2161,  2162,  2163,  2164,  2165,  2168,
    2177,  2186,  2194,  2202,  2210,  2218,  2226,  2234,  2242,  2250,
    2258,  2266,  2274,  2282,  2290,  2298,  2306,  2310,  2315,  2323,
    2330,  2337,  2350,  2354,  2361,  2365,  2371,  2383,  2389,  2396,
    2397,  2398,  2399,  2402,  2403,  2404,  2405,  2406,  2407,  2408,
    2409,  2410,  2411,  2412,  2413,  2414,  2415,  2416,  2417,  2418,
    2419,  2420,  2423,  2427,  2433,  2439,  2444,  2447,  2452,  2457,
    2460,  2466,  2471,  2479,  2480,  2482,  2486,  2494,  2498,  2501,
    2505,  2511,  2512,  2515,  2521,  2525,  2528,  2533,  2538,  2543,
    2548,  2553,  2559,  2589,  2593,  2597,  2601,  2605,  2611,  2615,
    2618,  2622,  2628,  2637,  2656,  2664,  2665,  2666,  2669,  2670,
    2673,  2674,  2689,  2705,  2713,  2714,  2715,  2718,  2719,  2722,
    2723,  2724,  2739,  2740,  2741,  2742,  2743,  2746,  2749,  2756,
    2760,  2771,  2782,  2792,  2798,  2801,  2802,  2805,  2811,  2817,
    2823,  2830,  2837,  2845,  2846,  2849,  2853,  2861,  2865,  2868,
    2873,  2878,  2882,  2888,  2904,  2923,  2929,  2930,  2936,  2937,
    2943,  2944,  2945,  2946,  2947,  2948,  2949,  2950,  2951,  2952,
    2953,  2954,  2957,  2958,  2962,  2968,  2969,  2975,  2976,  2982,
    2983,  2989,  2992,  2993,  3012,  3013,  3016,  3020,  3023,  3029,
    3035,  3046,  3047,  3048,  3051,  3052,  3053,  3056,  3060,  3064,
    3069,  3074,  3079,  3085,  3089,  3093,  3099,  3100,  3103,  3106,
    3110,  3115,  3121,  3122,  3125,  3128,  3132,  3136,  3140,  3145,
    3152,  3157,  3165,  3170,  3179,  3180,  3186,  3187,  3188,  3191,
    3192,  3195,  3201,  3205,  3208,  3213,  3219,  3220,  3226,  3227,
    3230,  3231,  3234,  3240,  3247,  3254,  3264,  3265,  3266,  3269,
    3277,  3288,  3295,  3298,  3304,  3308,  3311,  3317,  3326,  3337,
    3343,  3369,  3370,  3379,  3380,  3383,  3392,  3403,  3404,  3405,
    3406,  3407,  3408,  3409,  3410,  3411,  3412,  3413,  3414,  3415,
    3416,  3417,  3420,  3443,  3444,  3445,  3448,  3449,  3450,  3451,
    3452,  3455,  3459,  3462,  3466,  3473,  3476,  3490,  3491,  3495,
    3501,  3502,  3508,  3509,  3515,  3516,  3522,  3525,  3526,  3545,
    3551,  3557,  3558,  3559,  3562,  3568,  3569,  3570,  3573,  3580,
    3585,  3590,  3593,  3597,  3601,  3607,  3608,  3615,  3621,  3622,
    3625,  3631,  3635,  3638,  3642,  3646,  3652,  3653,  3656,  3657,
    3660,  3661,  3664,  3675,  3681,  3702,  3708,  3725,  3731,  3732,
    3733,  3736,  3737,  3740,  3755,  3761,  3767,  3774,  3788,  3796,
    3804,  3810,  3814,  3818,  3822,  3826,  3833,  3838,  3849,  3871,
    3877,  3881,  3885,  3891,  3897,  3905,  3906,  3907,  3908,  3911,
    3912,  3916,  3922,  3923,  3929,  3930,  3936,  3937,  3943,  3946,
    3947,  3966,  3967,  3970,  3978,  3979,  3980,  3981,  3982,  3983,
    3984,  3985,  3986,  3987,  3988,  3989,  3992,  3993,  3994,  3995,
    3996,  4003,  4010,  4017,  4024,  4031,  4038,  4045,  4052,  4059,
    4066,  4073,  4080,  4083,  4084,  4085,  4086,  4087,  4088,  4091,
    4095,  4099,  4103,  4107,  4111,  4117,  4118,  4128,  4132,  4136,
    4152,  4153,  4156,  4157,  4158,  4159,  4160,  4163,  4164,  4165,
    4166,  4167,  4168,  4169,  4170,  4171,  4172,  4173,  4174,  4175,
    4176,  4177,  4178,  4179,  4180,  4181,  4182,  4183,  4184,  4185,
    4186,  4189,  4209,  4213,  4227,  4231,  4235,  4241,  4247,  4248,
    4251,  4252,  4255,  4256,  4259,  4265,  4266,  4269,  4270,  4273,
    4274,  4277,  4278,  4281,  4289,  4316,  4321,  4326,  4332,  4333,
    4336,  4340,  4360,  4361,  4362,  4363,  4366,  4370,  4374,  4380,
    4381,  4384,  4385,  4386,  4387,  4388,  4389,  4390,  4391,  4392,
    4393,  4394,  4395,  4396,  4397,  4398,  4399,  4402,  4403,  4404,
    4405,  4406,  4407,  4408,  4411,  4412,  4413,  4414,  4417,  4418,
    4419,  4420,  4423,  4424,  4427,  4433,  4441,  4454,  4461,  4467,
    4473,  4482,  4483,  4484,  4485,  4486,  4487,  4488,  4489,  4490,
    4491,  4492,  4493,  4494,  4495,  4496,  4497,  4498,  4499,  4502,
    4511,  4512,  4513,  4516,  4522,  4523,  4524,  4527,  4533,  4534,
    4535,  4536,  4539,  4545,  4546,  4547,  4548,  4549,  4550,  4551,
    4552,  4553,  4556,  4560,  4564,  4571,  4572,  4573,  4574,  4575,
    4576,  4577,  4578,  4579,  4580,  4581,  4582,  4585,  4586,  4587,
    4588,  4591,  4592,  4593,  4594,  4595,  4598,  4604,  4605,  4606,
    4607,  4608,  4609,  4610,  4613,  4619,  4620,  4621,  4622,  4625,
    4631,  4632,  4633,  4634,  4635,  4636,  4637,  4638,  4639,  4641,
    4647,  4648,  4649,  4650,  4651,  4652,  4653,  4654,  4657,  4663,
    4664,  4665,  4666,  4667,  4670,  4676,  4677,  4680,  4686,  4687,
    4688,  4691,  4697,  4698,  4699,  4700,  4703,  4709,  4710,  4711,
    4712,  4715,  4719,  4723,  4730,  4731,  4732,  4733,  4734,  4735,
    4736,  4737,  4738,  4739,  4742,  4743,  4744,  4745,  4746,  4747,
    4748,  4749,  4750,  4751,  4752,  4753,  4756,  4757,  4758,  4759,
    4760,  4761,  4762,  4763,  4766,  4772,  4773,  4774,  4777,  4783,
    4784,  4785,  4786,  4789,  4797,  4798,  4801,  4802,  4803,  4804,
    4805,  4806,  4807,  4808,  4811,  4817,  4818,  4821,  4827,  4828,
    4829,  4830,  4833,  4839,  4845,  4851,  4854,  4860,  4861,  4862,
    4863,  4869,  4875,  4876,  4877,  4878,  4879,  4880,  4883,  4889,
    4890,  4893,  4899,  4900,  4901,  4902,  4903,  4906,  4920,  4921,
    4922,  4923,  4924
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "\"junk\"", "\"newline\"",
  "\"colon\"", "\"semicolon\"", "\"comma\"", "\".\"", "\"==\"", "\"!=\"",
  "\"<\"", "\">\"", "\">=\"", "\"<=\"", "\"<<\"", "\">>\"", "\"&\"",
  "\"^\"", "\"!\"", "\"/\"", "\"*\"", "\"-\"", "\"@\"", "\"vmap\"",
  "\"+\"", "\"include\"", "\"define\"", "\"redefine\"", "\"undefine\"",
  "\"fib\"", "\"socket\"", "\"transparent\"", "\"tproxy\"", "\"osf\"",
  "\"synproxy\"", "\"mss\"", "\"wscale\"", "\"sack-perm\"", "\"hook\"",
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
  "\"vlan\"", "\"id\"", "\"cfi\"", "\"pcp\"", "\"arp\"", "\"htype\"",
  "\"ptype\"", "\"hlen\"", "\"plen\"", "\"operation\"", "\"ip\"",
  "\"version\"", "\"hdrlength\"", "\"dscp\"", "\"ecn\"", "\"length\"",
  "\"frag-off\"", "\"ttl\"", "\"protocol\"", "\"checksum\"", "\"ptr\"",
  "\"value\"", "\"lsrr\"", "\"rr\"", "\"ssrr\"", "\"ra\"", "\"icmp\"",
  "\"code\"", "\"seq\"", "\"gateway\"", "\"mtu\"", "\"igmp\"", "\"mrt\"",
  "\"options\"", "\"ip6\"", "\"priority\"", "\"flowlabel\"", "\"nexthdr\"",
  "\"hoplimit\"", "\"icmpv6\"", "\"param-problem\"", "\"max-delay\"",
  "\"ah\"", "\"reserved\"", "\"spi\"", "\"esp\"", "\"comp\"", "\"flags\"",
  "\"cpi\"", "\"udp\"", "\"sport\"", "\"dport\"", "\"udplite\"",
  "\"csumcov\"", "\"tcp\"", "\"ackseq\"", "\"doff\"", "\"window\"",
  "\"urgptr\"", "\"option\"", "\"echo\"", "\"eol\"", "\"maxseg\"",
  "\"noop\"", "\"sack\"", "\"sack0\"", "\"sack1\"", "\"sack2\"",
  "\"sack3\"", "\"sack-permitted\"", "\"timestamp\"", "\"kind\"",
  "\"count\"", "\"left\"", "\"right\"", "\"tsval\"", "\"tsecr\"",
  "\"dccp\"", "\"sctp\"", "\"vtag\"", "\"rt\"", "\"rt0\"", "\"rt2\"",
  "\"srh\"", "\"seg-left\"", "\"addr\"", "\"last-entry\"", "\"tag\"",
  "\"sid\"", "\"hbh\"", "\"frag\"", "\"reserved2\"", "\"more-fragments\"",
  "\"dst\"", "\"mh\"", "\"meta\"", "\"mark\"", "\"iif\"", "\"iifname\"",
  "\"iiftype\"", "\"oif\"", "\"oifname\"", "\"oiftype\"", "\"skuid\"",
  "\"skgid\"", "\"nftrace\"", "\"rtclassid\"", "\"ibriport\"",
  "\"obriport\"", "\"ibrname\"", "\"obrname\"", "\"pkttype\"", "\"cpu\"",
  "\"iifgroup\"", "\"oifgroup\"", "\"cgroup\"", "\"time\"", "\"classid\"",
  "\"nexthop\"", "\"ct\"", "\"l3proto\"", "\"proto-src\"", "\"proto-dst\"",
  "\"zone\"", "\"direction\"", "\"event\"", "\"expectation\"",
  "\"expiration\"", "\"helper\"", "\"label\"", "\"state\"", "\"status\"",
  "\"original\"", "\"reply\"", "\"counter\"", "\"name\"", "\"packets\"",
  "\"bytes\"", "\"avgpkt\"", "\"counters\"", "\"quotas\"", "\"limits\"",
  "\"synproxys\"", "\"helpers\"", "\"log\"", "\"prefix\"", "\"group\"",
  "\"snaplen\"", "\"queue-threshold\"", "\"level\"", "\"limit\"",
  "\"rate\"", "\"burst\"", "\"over\"", "\"until\"", "\"quota\"",
  "\"used\"", "\"secmark\"", "\"secmarks\"", "\"nanosecond\"",
  "\"microsecond\"", "\"millisecond\"", "\"second\"", "\"minute\"",
  "\"hour\"", "\"day\"", "\"week\"", "\"reject\"", "\"with\"", "\"icmpx\"",
  "\"snat\"", "\"dnat\"", "\"masquerade\"", "\"redirect\"", "\"random\"",
  "\"fully-random\"", "\"persistent\"", "\"queue\"", "\"num\"",
  "\"bypass\"", "\"fanout\"", "\"dup\"", "\"fwd\"", "\"numgen\"",
  "\"inc\"", "\"mod\"", "\"offset\"", "\"jhash\"", "\"symhash\"",
  "\"seed\"", "\"position\"", "\"index\"", "\"comment\"", "\"xml\"",
  "\"json\"", "\"vm\"", "\"notrack\"", "\"exists\"", "\"missing\"",
  "\"exthdr\"", "\"ipsec\"", "\"mode\"", "\"reqid\"", "\"spnum\"",
  "\"transport\"", "\"tunnel\"", "\"in\"", "\"out\"", "'='", "'{'", "'}'",
  "'|'", "'$'", "'('", "')'", "'['", "']'", "$accept", "input",
  "stmt_separator", "opt_newline", "common_block", "line", "base_cmd",
  "add_cmd", "replace_cmd", "create_cmd", "insert_cmd", "delete_cmd",
  "get_cmd", "list_cmd", "reset_cmd", "flush_cmd", "rename_cmd",
  "import_cmd", "export_cmd", "monitor_cmd", "monitor_event",
  "monitor_object", "monitor_format", "markup_format", "describe_cmd",
  "table_block_alloc", "table_options", "table_block", "chain_block_alloc",
  "chain_block", "set_block_alloc", "set_block", "set_block_expr",
  "set_flag_list", "set_flag", "map_block_alloc", "map_block",
  "set_mechanism", "set_policy_spec", "flowtable_block_alloc",
  "flowtable_block", "flowtable_expr", "flowtable_list_expr",
  "flowtable_expr_member", "data_type_atom_expr", "data_type_expr",
  "obj_block_alloc", "counter_block", "quota_block", "ct_helper_block",
  "ct_timeout_block", "ct_expect_block", "limit_block", "secmark_block",
  "synproxy_block", "type_identifier", "hook_spec", "prio_spec",
  "extended_prio_name", "extended_prio_spec", "int_num", "dev_spec",
  "policy_spec", "policy_expr", "chain_policy", "identifier", "string",
  "time_spec", "family_spec", "family_spec_explicit", "table_spec",
  "tableid_spec", "chain_spec", "chainid_spec", "chain_identifier",
  "set_spec", "setid_spec", "set_identifier", "flowtable_spec",
  "flowtableid_spec", "flowtable_identifier", "obj_spec", "objid_spec",
  "obj_identifier", "handle_spec", "position_spec", "index_spec",
  "rule_position", "ruleid_spec", "comment_spec", "ruleset_spec", "rule",
  "rule_alloc", "stmt_list", "stateful_stmt", "stmt", "verdict_stmt",
  "verdict_map_stmt", "verdict_map_expr", "verdict_map_list_expr",
  "verdict_map_list_member_expr", "connlimit_stmt", "counter_stmt",
  "counter_stmt_alloc", "counter_args", "counter_arg", "log_stmt",
  "log_stmt_alloc", "log_args", "log_arg", "level_type", "log_flags",
  "log_flags_tcp", "log_flag_tcp", "limit_stmt", "quota_mode",
  "quota_unit", "quota_used", "quota_stmt", "limit_mode",
  "limit_burst_pkts", "limit_burst_bytes", "time_unit", "reject_stmt",
  "reject_stmt_alloc", "reject_opts", "nat_stmt", "nat_stmt_alloc",
  "tproxy_stmt", "synproxy_stmt", "synproxy_stmt_alloc", "synproxy_args",
  "synproxy_arg", "synproxy_config", "synproxy_obj", "synproxy_ts",
  "synproxy_sack", "primary_stmt_expr", "shift_stmt_expr", "and_stmt_expr",
  "exclusive_or_stmt_expr", "inclusive_or_stmt_expr", "basic_stmt_expr",
  "concat_stmt_expr", "map_stmt_expr_set", "map_stmt_expr",
  "prefix_stmt_expr", "range_stmt_expr", "wildcard_expr",
  "multiton_stmt_expr", "stmt_expr", "nat_stmt_args", "masq_stmt",
  "masq_stmt_alloc", "masq_stmt_args", "redir_stmt", "redir_stmt_alloc",
  "redir_stmt_arg", "dup_stmt", "fwd_stmt", "nf_nat_flags", "nf_nat_flag",
  "queue_stmt", "queue_stmt_alloc", "queue_stmt_args", "queue_stmt_arg",
  "queue_stmt_flags", "queue_stmt_flag", "set_elem_expr_stmt",
  "set_elem_expr_stmt_alloc", "set_stmt", "set_stmt_op", "map_stmt",
  "meter_stmt", "flow_stmt_legacy_alloc", "flow_stmt_opts",
  "flow_stmt_opt", "meter_stmt_alloc", "match_stmt", "variable_expr",
  "symbol_expr", "set_ref_expr", "set_ref_symbol_expr", "integer_expr",
  "primary_expr", "fib_expr", "fib_result", "fib_flag", "fib_tuple",
  "osf_expr", "osf_ttl", "shift_expr", "and_expr", "exclusive_or_expr",
  "inclusive_or_expr", "basic_expr", "concat_expr", "prefix_rhs_expr",
  "range_rhs_expr", "multiton_rhs_expr", "map_expr", "expr", "set_expr",
  "set_list_expr", "set_list_member_expr", "meter_key_expr",
  "meter_key_expr_alloc", "set_elem_expr", "set_elem_expr_alloc",
  "set_elem_options", "set_elem_option", "set_lhs_expr", "set_rhs_expr",
  "initializer_expr", "counter_config", "counter_obj", "quota_config",
  "quota_obj", "secmark_config", "secmark_obj", "ct_obj_type",
  "ct_l4protoname", "ct_helper_config", "timeout_states", "timeout_state",
  "ct_timeout_config", "ct_expect_config", "ct_obj_alloc", "limit_config",
  "limit_obj", "relational_expr", "list_rhs_expr", "rhs_expr",
  "shift_rhs_expr", "and_rhs_expr", "exclusive_or_rhs_expr",
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
  "dccp_hdr_expr", "dccp_hdr_field", "sctp_hdr_expr", "sctp_hdr_field",
  "th_hdr_expr", "th_hdr_field", "exthdr_expr", "hbh_hdr_expr",
  "hbh_hdr_field", "rt_hdr_expr", "rt_hdr_field", "rt0_hdr_expr",
  "rt0_hdr_field", "rt2_hdr_expr", "rt2_hdr_field", "rt4_hdr_expr",
  "rt4_hdr_field", "frag_hdr_expr", "frag_hdr_field", "dst_hdr_expr",
  "dst_hdr_field", "mh_hdr_expr", "mh_hdr_field", "exthdr_exists_expr",
  "exthdr_key", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
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
     565,   566,   567,   568,   569,   570,   571,   572,   573,    61,
     123,   125,   124,    36,    40,    41,    91,    93
};
# endif

#define YYPACT_NINF -1340

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1340)))

#define YYTABLE_NINF -844

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1340,  5764, -1340,   704, -1340, -1340,    77,    87,    87,    87,
    1466,  1466,  1466,  1466,  1466,  1466,  1466,  1466, -1340, -1340,
    2603,   165,  2252,   192,  1889,   199,  5996,   425,  1237,   228,
    5264,    40,   139,   232, -1340, -1340, -1340, -1340,   225,  1466,
    1466,  1466,  1466, -1340, -1340, -1340,   878, -1340,    87, -1340,
      87,   155,  4824, -1340,   704, -1340,    44,    79,   704,    87,
   -1340,    66,   191,  4824,    87, -1340,   -29, -1340,    87, -1340,
   -1340,  1466, -1340,  1466,  1466,  1466,  1466,  1466,  1466,  1466,
     226,  1466,  1466,  1466,  1466, -1340,  1466, -1340,  1466,  1466,
    1466,  1466,  1466,  1466,  1466,  1466,   261,  1466,  1466,  1466,
    1466, -1340,  1466, -1340,  1466,  1466,  1466,  1466,  1466,   603,
    1466,  1466,  1466,  1466,  1466,   513,  1466,  1466,  1466,   193,
    1466,   963,   970,  1048,  1240,  1466,  1466,  1466,  1831, -1340,
    1466,  1923,  1983,  1466, -1340,  1466,  1466,  1466,  1466,  1466,
     392,  1466, -1340,  1466, -1340,   559,   184,    70,   331, -1340,
   -1340, -1340, -1340,   623,   578,   733,  1318,  2420,  1277,   468,
    2302,  1438,   813,   270,   401,   143,   473,  1787,   290,   343,
    1119,   338,   369,   712,   179,  1043,   233,   548,  3190, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
    3930, -1340, -1340,   288,  5050,   281,   973,   502,    87,  5264,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340,   591, -1340, -1340,   299, -1340,
   -1340,   591, -1340, -1340, -1340, -1340,  1483,  1466,  1466,  1466,
     339, -1340, -1340, -1340, -1340, -1340, -1340, -1340,   541,   558,
     621, -1340, -1340, -1340,   358,   427,   711, -1340, -1340, -1340,
   -1340, -1340, -1340,    -8,    -8, -1340,    58,    87,  3416,  3844,
     431, -1340,   -45,   447, -1340, -1340, -1340, -1340, -1340, -1340,
     659,   374, -1340,   762, -1340,   488,  4824, -1340, -1340, -1340,
   -1340, -1340, -1340,   590, -1340,   574, -1340, -1340, -1340,   471,
   -1340,  3004, -1340, -1340,   432, -1340,   237, -1340,   309, -1340,
   -1340, -1340,   633, -1340,    47, -1340, -1340,   734, -1340, -1340,
   -1340,   844,   781,   787,   492, -1340,   564, -1340,  4133, -1340,
   -1340, -1340,   780, -1340, -1340, -1340,   791, -1340,  4204,  4204,
   -1340, -1340,   812,   507,   535, -1340, -1340,   551, -1340, -1340,
   -1340,   554, -1340,   557,   825,  4824, -1340,    66,   191, -1340,
     -29, -1340, -1340,  1466,  1466,  1466,   339, -1340, -1340, -1340,
    4824,   116, -1340, -1340,   190, -1340, -1340,   222, -1340, -1340,
   -1340,   388, -1340, -1340,   -29, -1340,   464, -1340, -1340, -1340,
   -1340, -1340,  1466, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340,   -29, -1340, -1340, -1340, -1340, -1340, -1340,  1466, -1340,
   -1340, -1340, -1340, -1340, -1340,  1466,  1466, -1340, -1340, -1340,
     858,   866,   870,  1466, -1340,  1466, -1340,  1466, -1340,  1466,
   -1340,  1466, -1340, -1340, -1340, -1340,  1466, -1340, -1340,  1466,
   -1340,  1466, -1340, -1340, -1340, -1340, -1340, -1340, -1340,  1466,
   -1340,    87, -1340, -1340, -1340,   932, -1340, -1340, -1340, -1340,
   -1340,   941,   118, -1340, -1340, -1340,   851,     5, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
     202,   333, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
    1023, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340,  2182, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,   286, -1340,
   -1340,   631, -1340, -1340, -1340, -1340, -1340, -1340,   656, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
     885, -1340, -1340, -1340, -1340,   663,   352,   689,   888, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340,   675, -1340,   673,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
     591, -1340, -1340, -1340,   757,   749,   638,   864, -1340, -1340,
   -1340,  3230,   937,  4599,  5264, -1340, -1340, -1340, -1340,   990,
    1006,    -3,   987,   995,   998,    36,  1000,   885,  1002,  4599,
    4599,   690,  4599, -1340, -1340,   961,  4599,  4599,   991, -1340,
    4366,    57, -1340,   864, -1340, -1340,   978,   993,   590, -1340,
     525,   864,  1003,  1029,  1031,   864,   574, -1340,   347, -1340,
    4599, -1340, -1340,  3456,   578,   733,  1318,  2137, -1340,  2051,
     622, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,   980,
    1077,  1117,   816,   742,   470, -1340, -1340, -1340, -1340, -1340,
    1137,   746,  1158, -1340, -1340, -1340, -1340,  1161, -1340, -1340,
   -1340, -1340,  1091, -1340, -1340,  1172,  1175, -1340,  1086,  1087,
   -1340, -1340,   432, -1340,  1183, -1340, -1340, -1340, -1340,  1182,
   -1340,  3682, -1340,  1182,  4599, -1340, -1340,   633, -1340,  1188,
   -1340,    87, -1340,   876, -1340,    87,    46, -1340,  5845,  5845,
    5845,  5845,  5845,  5264,    74,  4204, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,  5845,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,  1196, -1340,
     992,  1191,  1193,   891,   594,  1217, -1340, -1340, -1340,  4204,
    4599,  4599,   704,  1196, -1340,   704,  1128, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340,   812,   910,   917,   918, -1340,
     921,   923, -1340, -1340, -1340,   757,   749,   638,   864, -1340,
    1145,  1151,  1152,  1154, -1340,  1156, -1340, -1340, -1340, -1340,
   -1340,  1466,  1466,  1466, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340,  1162,   184, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340,   677, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340,   680, -1340,  1163,  1164, -1340, -1340,
     907, -1340,   933, -1340, -1340, -1340, -1340, -1340, -1340,  1166,
    1167,   960,  1169,   153, -1340, -1340, -1340,   949,   951,   964,
    1173, -1340,   690, -1340,  1181, -1340, -1340, -1340,  4599,  2420,
    2302,  1278,  3908, -1340,    47,   133,  1282,   864,   864,  1186,
    5264,  4599,  4599,  4599, -1340,  1192,  4599,  1244,  4599, -1340,
   -1340, -1340, -1340,  1204, -1340,    23,  1255, -1340,  4599, -1340,
     762,  1049,   133, -1340,   779,  1217,   762, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340,  1177,   381, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340,  1207,  1209,  1249,  1212, -1340,
    4599,  1321,  5478,  5845,  5478,  5478,  5478,  1224,  5478,  5478,
      95,  4599,  1182,  4599,  5073,  5073, -1340, -1340, -1340,  4599,
     746,  4599,   746, -1340, -1340,   775, -1340,  5264, -1340,  5264,
   -1340, -1340, -1340,   992,  1191,  1193, -1340,   762, -1340, -1340,
   -1340,  1005,  5845,  5845,  5845,  5845,  5845,  5845,  5845,  1236,
    5845,  5845, -1340, -1340, -1340, -1340, -1340,   575,  1739,  2178,
     481,  1901,    85, -1340, -1340, -1340, -1340, -1340, -1340,  1016,
    1017,  1019, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340,  1338, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340,  1022,  1024, -1340, -1340, -1340, -1340,   960,   293,
    1260, -1340, -1340, -1340, -1340, -1340,   966, -1340, -1340, -1340,
    1112,  1264,    23, -1340,  4599,  4599,  1359, -1340,  1271,  1271,
   -1340,   133, -1340, -1340, -1340,  1052,  1282,  4824,   133, -1340,
   -1340, -1340, -1340, -1340,  4599, -1340,   148, -1340, -1340,  1106,
    4599,  1335, -1340,  5773, -1340,   133,  4366, -1340, -1340, -1340,
   -1340,  1371, -1340,  1283,  1286, -1340,  1288, -1340,  4599, -1340,
   -1340, -1340, -1340,   980,  1077,  1117, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340,  1385, -1340, -1340, -1340, -1340,   746, -1340,
     746,  1182, -1340,    89,  4824,  4437,    59, -1340, -1340, -1340,
   -1340, -1340,   992,  1191,  1193, -1340, -1340, -1340, -1340,  1296,
    1363,    87,    87,    87,    87,    87,  1301,   313,    87,    87,
      87,    87, -1340, -1340, -1340,   704,    82,  1308, -1340, -1340,
   -1340,   704,   704,   704, -1340,  1271,  1271,  1090,  1018,  1311,
     939,   834, -1340, -1340, -1340,   704,  1271,  1093,   939,   834,
   -1340, -1340, -1340,   704,  1324,  1120, -1340, -1340, -1340,  1865,
    2477,   725,  2027,   214, -1340, -1340, -1340,  1326, -1340, -1340,
   -1340,  1332, -1340, -1340, -1340, -1340, -1340,   259,   137,   206,
    1341,   154,  1106, -1340, -1340,  4599, -1340, -1340, -1340, -1340,
    5264,  1122,   133, -1340,   850,  1178,  1345, -1340, -1340,  4599,
     762, -1340,  1217, -1340,   381, -1340, -1340, -1340, -1340,  4599,
    1182,  1182,  5264,  1263, -1340,    54,  1126,  1444,   762, -1340,
    1272,  1353, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340,    87,    87,    87, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340,  1416, -1340, -1340, -1340,   704,
     704,   -29, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340,   485, -1340, -1340, -1340, -1340, -1340,   694,
   -1340, -1340,   704,   -29,   714,   694, -1340,  1313,  1140, -1340,
   -1340, -1340, -1340, -1340,   688,   952,   255, -1340,   960,  1142,
     371,  1466, -1340, -1340, -1340, -1340,  1271,  1368,   371,  1372,
    1466, -1340, -1340, -1340, -1340,  1369,  1466, -1340, -1340, -1340,
   -1340, -1340,   850,  1178, -1340, -1340,  4824, -1340, -1340, -1340,
   -1340, -1340, -1340,  1219,  1392, -1340,    23, -1340, -1340, -1340,
   -1340,  1174,  5264, -1340, -1340,  1541,  4437, -1340, -1340,  1455,
     704,  1176,  1184,  1187,  1190,  1195, -1340, -1340, -1340,  1197,
    1200,  1201,  1205,  1394, -1340, -1340, -1340,   939, -1340,   834,
   -1340, -1340, -1340,   756, -1340,    93,   704,  1397,   704, -1340,
   -1340, -1340, -1340,  1213, -1340, -1340,   704,   704,   704,   704,
     704,   704,   704,  1373,   704,  1219, -1340,  1180,  1412, -1340,
     114, -1340, -1340,  1208,   762, -1340, -1340,  1272, -1340, -1340,
   -1340, -1340, -1340,  1215,  1216,  1220, -1340, -1340, -1340, -1340,
    1080, -1340, -1340,   704,   704,   704,   704,   485,  1413, -1340,
   -1340, -1340,   716, -1340, -1340, -1340, -1340, -1340,    61, -1340,
   -1340,  1432, -1340, -1340, -1340, -1340, -1340, -1340, -1340,   371,
   -1340, -1340, -1340,  1266, -1340, -1340, -1340, -1340,  1455,   768,
    2776,  1393,  2142,  1248, -1340, -1340, -1340,   678,  1206,    72,
     102,   864,  1222,  1313, -1340, -1340, -1340, -1340, -1340, -1340,
    1443,  1445,   129, -1340,  1538,    62, -1340,   704, -1340, -1340,
     704, -1340, -1340, -1340,   704,   704,   704,   704,  1376,  1781,
     729,   704, -1340, -1340, -1340,   704, -1340, -1340, -1340,   704,
   -1340, -1340, -1340,   704, -1340, -1340, -1340, -1340,  1140, -1340,
   -1340, -1340, -1340, -1340,  1447,  1432,   704, -1340, -1340, -1340,
   -1340, -1340, -1340,   704,   704,   704, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     301,   301,   301,   301,   301,   301,   301,   301,   305,   308,
     301,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,   307,   306,   303,   304,     0,   301,
     301,   301,   301,    14,    13,     3,     0,    17,     0,   302,
       0,   326,     0,    12,     0,   296,     0,     0,     0,     0,
     455,    32,    34,     0,     0,   188,     0,   207,     0,   224,
      18,   301,    19,   301,   301,   301,   301,   301,   301,   301,
       0,   301,   301,   301,   301,    20,   301,    21,   301,   301,
     301,   301,   301,   301,   301,   301,     0,   301,   301,   301,
     301,    22,   301,    23,   301,   301,   332,   301,   332,   332,
     301,   301,   332,   301,   332,     0,   301,   332,   332,     0,
     301,   332,   332,   332,   332,   301,   301,   301,   332,    24,
     301,   332,   332,   301,    25,   301,   301,   301,   301,   332,
       0,   301,    26,   301,    27,     0,     0,     0,   595,   566,
     297,   298,   299,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   747,
     748,   749,   750,   751,   752,   753,   754,   755,   756,   757,
     758,   759,   760,   761,   762,   763,   764,   765,   766,   768,
       0,   770,   769,     0,     0,     0,     0,   767,     0,     0,
      31,   562,   561,   567,   568,   162,   578,   579,   572,   738,
     573,   576,   580,   577,   574,   575,   569,   851,   852,   853,
     854,   855,   856,   857,   858,   859,   860,   861,   862,   863,
     864,   865,   866,   867,   868,   570,  1016,  1017,  1018,  1019,
    1020,  1021,  1022,  1023,   571,     0,   159,   160,     0,    28,
     143,     0,    29,   145,   148,    30,   149,   301,   301,   301,
      42,   669,   645,   647,    16,    15,   309,   311,     0,     0,
       0,   328,   327,   329,     0,   445,     0,   546,   547,   548,
     729,   730,   731,     0,     0,   734,   553,     0,     0,     0,
     375,   383,     0,   407,   428,   435,   436,   508,   514,   531,
       0,     0,   774,     7,    37,   334,   336,   347,   337,   343,
     363,   342,   339,   373,   349,   381,   340,   341,   350,   429,
     351,     0,   352,   361,   443,   355,   507,   356,   513,   357,
     358,   353,   529,   359,     0,   360,   345,     0,   552,   344,
     597,   600,   602,   604,   606,   607,   615,   617,     0,   616,
     559,   362,   738,   348,   354,   346,   569,     8,     0,     0,
      11,   320,     0,     0,     0,    36,   314,     0,    40,   200,
     199,     0,   317,     0,     0,     0,   455,    52,    54,   188,
       0,   207,   224,   301,   301,   301,    60,   669,   645,   647,
       0,     0,    90,    91,     0,    70,    71,     0,    72,    73,
      74,     0,    75,    76,     0,    77,     0,    79,    80,   649,
     650,   648,   301,    81,    82,    86,    87,    83,    84,    88,
      89,     0,   114,    93,   333,    94,    95,    96,   301,    97,
      99,   123,   122,   121,   115,   301,   332,   119,   118,   120,
     649,   650,     0,   301,   102,   301,   100,   301,   103,   301,
     106,   301,   112,   108,   105,   111,   301,   109,   130,   301,
     128,   301,   131,   133,   134,   135,   136,   137,   140,   301,
     139,     0,   870,   871,   872,     0,   586,   587,   588,   589,
     590,   592,     0,   778,   779,   777,     0,     0,  1014,  1015,
    1013,   874,   875,   876,   873,   881,   878,   879,   880,   877,
       0,     0,   883,   884,   885,   886,   887,   882,   905,   906,
     900,   895,   896,   897,   898,   899,   901,   902,   903,   904,
       0,   892,   917,   920,   919,   918,   921,   922,   923,   916,
     925,   926,   927,   928,   924,   937,   938,   930,   931,   932,
     934,   933,   935,   936,   929,   940,   945,   942,   941,   946,
     944,   943,   947,   939,   950,   953,   949,   951,   952,   948,
     956,   955,   954,   958,   959,   960,   957,   964,   965,   962,
     963,   961,   970,   967,   968,   969,   966,   982,   976,   979,
     980,   974,   975,   977,   978,   981,   983,     0,   971,  1007,
    1005,  1006,  1004,  1012,  1009,  1010,  1011,  1008,  1030,   798,
    1029,   804,   799,  1028,  1031,   802,   803,   805,     0,   800,
    1027,     0,  1032,  1035,  1034,  1038,  1037,  1039,     0,  1036,
    1026,  1025,  1024,  1047,  1044,  1042,  1043,  1045,  1046,  1041,
    1050,  1049,  1048,  1054,  1053,  1056,  1052,  1055,  1051,   739,
     742,   743,   744,   746,   745,   767,   737,   740,   741,   819,
     820,   812,   813,   811,   821,   822,   841,   815,   824,   817,
     818,   823,   814,   816,   809,   810,   839,   838,   840,   825,
       0,   806,   826,   783,   782,     0,   615,     0,     0,  1059,
    1058,  1060,  1061,  1062,  1057,   787,   788,   786,   560,     0,
     142,   161,   144,   150,   151,   153,   152,   155,   156,   154,
     157,   666,   666,   666,     0,     0,   407,     0,   323,   324,
     325,     0,     0,     0,     0,   736,   735,   732,   733,     0,
       0,     0,   739,   737,     0,     0,     0,     0,   806,     0,
       0,   416,     0,   405,   406,     0,     0,     0,     0,     6,
       0,     0,   619,     0,   335,   338,     0,     0,   374,   377,
       0,     0,     0,     0,     0,     0,   382,   384,     0,   427,
       0,   490,   702,     0,   694,   697,   698,   695,   701,   696,
       0,   705,   703,   704,   700,   699,   691,   692,   472,   475,
     477,   479,   481,   482,   487,   494,   491,   492,   493,   495,
     497,   434,   460,   461,   471,   693,   462,   469,   463,   470,
     466,   467,     0,   464,   465,     0,   496,   468,     0,     0,
     452,   451,   444,   447,     0,   526,   527,   528,   506,   511,
     524,     0,   512,   517,     0,   538,   539,   530,   532,   535,
     536,     0,   564,     0,   563,     0,     0,   554,     0,     0,
       0,     0,     0,     0,     0,     0,   723,   724,   725,   726,
     727,   728,   694,   697,   698,   695,   715,   716,   696,   717,
     714,   713,   718,   711,   712,   710,   719,   720,   721,     0,
     613,   706,   678,   707,   611,   612,   676,   677,   671,   670,
     682,   684,   686,   688,   689,   675,   708,   709,   679,     0,
       0,     0,     0,   641,   640,     0,     0,    50,   165,   182,
     189,   208,   225,   330,    51,     0,     0,     0,     0,    58,
       0,     0,   666,   666,   666,     0,     0,   407,     0,    69,
       0,     0,     0,     0,    78,     0,   666,    92,    98,   117,
     116,   301,   301,   301,   124,   101,   104,   107,   113,   110,
     129,   132,   138,   141,     0,     0,   585,   583,   584,   582,
     596,   593,   594,   888,   890,   889,   891,   907,   908,   909,
     910,   894,   987,   994,   984,   986,   985,   989,   990,   991,
     992,   993,   988,   995,   973,   801,     0,     0,   827,   828,
       0,   830,     0,   829,   831,   832,   807,   808,   833,     0,
       0,   780,     0,     0,   581,   146,   158,     0,     0,     0,
       0,    43,   416,    48,     0,    44,   646,    49,     0,   695,
     696,   437,     0,   446,     0,   540,   542,     0,     0,     0,
       0,     0,     0,     0,   371,     0,     0,   833,     0,   376,
     404,   414,   415,     0,   413,     0,   520,   522,     0,   637,
       7,     7,   628,   630,   689,   636,     7,   618,   331,   379,
     380,   378,   397,   396,     0,     0,   395,   391,   386,   387,
     388,   389,   392,   390,   385,     0,     0,     0,     0,   503,
       0,   498,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   505,     0,     0,     0,   449,   450,   448,     0,
       0,     0,   515,   534,   533,     0,   565,     0,   556,     0,
     555,   598,   599,   601,   603,   605,   608,     7,   364,   366,
     614,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   672,   772,   850,     9,    10,     0,     0,     0,
       0,     0,     0,    68,   165,   182,   189,   208,   225,     0,
       0,     0,    61,    66,    62,    67,   321,   310,   312,   315,
     318,    85,   126,   127,   125,     0,   591,   911,   912,   914,
     913,   915,   893,   998,   997,   996,   999,  1000,  1001,  1002,
    1003,   972,     0,     0,   834,   835,   836,   837,   780,   780,
       0,   797,   785,   789,   790,   793,     0,   252,   256,   248,
       0,     0,     0,   439,     0,     0,   438,   543,     0,     0,
     635,   541,   631,   776,   775,     0,   627,     0,   625,   773,
     771,   847,   372,   848,     0,   846,     0,   409,   408,   410,
       0,     0,   622,     0,   623,   629,   621,   620,   394,   400,
     401,   393,   399,     0,     0,   433,     0,   504,     0,   473,
     460,   469,   474,   476,   478,   480,   488,   489,   483,   486,
     485,   484,   500,   499,   842,   843,   844,   845,   509,   525,
     516,   518,   537,     0,     0,     0,     0,   367,   722,   674,
     680,   681,   683,   685,   687,   673,   609,   610,   690,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,   167,   166,     0,     0,     0,    35,   184,
     183,     0,     0,     0,   197,     0,     0,     0,     0,     0,
       0,     0,    38,   191,   190,     0,     0,     0,     0,     0,
      39,   210,   209,     0,     0,     0,    41,   227,   226,     0,
       0,     0,     0,     0,   252,   256,   248,     0,  1033,  1040,
     784,     0,   796,   781,   792,   791,   794,     0,     0,     0,
       0,     0,   410,   440,   442,     0,   300,   633,   634,   632,
       0,     0,   626,   849,     0,   419,     0,   412,   521,     0,
       7,   689,   638,   639,     0,   430,   431,   432,   501,     0,
     510,   519,     0,     0,   544,     0,     0,     0,     7,   365,
     456,     0,   322,   239,   313,   181,   316,   188,   207,   319,
     224,   164,     0,     0,     0,   239,   239,   239,   239,   168,
     294,   295,   291,   293,   292,     0,   185,   186,   187,     0,
       0,     0,   223,   222,   220,   221,   272,   274,   275,   273,
     236,   276,   237,     0,   235,   203,   204,   206,   205,     0,
     202,   198,     0,     0,     0,     0,   219,     0,     0,    53,
      55,    56,    57,    59,     0,     0,     0,   869,   780,     0,
       0,     0,    46,   254,   253,   255,     0,     0,     0,     0,
       0,    47,   258,   257,   259,     0,     0,    45,   250,   249,
     251,   642,     0,   419,   644,   441,     0,   557,   422,   423,
     424,   425,   426,   417,     0,   403,     0,   523,   624,   398,
     502,     0,     0,   545,   551,     0,   369,   368,   457,   458,
       0,     0,     0,     0,     0,     0,   239,   239,   239,     0,
       0,     0,     0,     0,   194,   195,   196,     0,   192,     0,
     193,   211,   218,     0,   217,     0,     0,     0,     0,    64,
      65,    63,   795,     0,   652,   651,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   417,   668,     0,     0,   402,
       0,   411,   549,     0,     7,   459,   453,   456,   268,   182,
     189,   208,   225,     0,     0,     0,   240,   260,   244,   264,
     290,   238,   201,     0,     0,     0,     0,     0,     0,   286,
     280,   279,   283,   278,   281,   282,   228,   234,     0,   231,
     229,     0,   658,   660,   663,   664,   661,   662,   665,     0,
     654,   667,   558,     0,   421,   420,   550,   370,   458,     0,
       0,     0,     0,     0,   252,   256,   248,     0,     0,     0,
       0,     0,     0,     0,   213,   215,   214,   216,   212,   287,
       0,     0,     7,   230,     0,     0,   655,     0,   418,   454,
       0,   270,   269,   271,     0,     0,     0,     0,     0,     0,
       0,     0,   242,   241,   243,     0,   262,   261,   263,     0,
     246,   245,   247,     0,   266,   265,   267,   288,     0,   277,
     285,   284,   233,   232,     0,     0,     0,   653,   180,   169,
     170,   171,   172,     0,     0,     0,   173,   178,   174,   179,
     289,   657,   656,   659,   176,   177,   175
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1340, -1340,    -1,  -931,    11, -1340, -1340,  1532, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340,     3, -1340,  1210, -1340,   410,  -380, -1104,
    -388, -1100,  -383,   235,    31,  -382, -1105, -1103, -1340,  -387,
   -1099,  -126, -1340,   -85,    37, -1248,  -767, -1340, -1340, -1264,
   -1260, -1258, -1340, -1340, -1340, -1340, -1340,   -70, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340,    13,  -703, -1048,  1486,    28,
     531, -1340,   778, -1340, -1340,  1684, -1340,   284,   505, -1340,
   -1340,  1730,  1202,  -326,  1198, -1340, -1340,   141,  1489,  1276,
      67,     2, -1340, -1340,   325,  -312, -1340, -1340, -1340, -1340,
     201, -1340, -1340, -1340, -1340,   843, -1340, -1340, -1340,   839,
   -1340, -1340, -1340,   218, -1340,  1303, -1142,   247, -1340,   598,
      49,   119,   130, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340,   802,  -892,  1239,    56,    -2,  -500,   543,   550,
     555, -1340,   565, -1340, -1340, -1340, -1340, -1340,  -329, -1340,
     986, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
    -320,   545, -1340, -1340, -1340,   809, -1340,   542, -1064, -1340,
   -1340,  1374, -1340, -1340, -1340, -1340,   808, -1340, -1340,   -47,
     -27,  -671,  -297,    92,  1625, -1340, -1340, -1340,   703,     4,
   -1340, -1340, -1340, -1340, -1340,  -172,  -194, -1340, -1340,  -735,
   -1340,  1457,   -55, -1340,   606, -1030, -1340, -1168, -1340,  -943,
   -1011, -1340, -1340,  1304,  -901,  1279,  -897,  1274,  -896,  1291,
    1557, -1339, -1340, -1340,   -18, -1340, -1340,  -361,  -893,  1295,
   -1340,  1336,  -314,  -754,  -741,  -731, -1340,  -342,  -737, -1340,
     836,  -196,  -652, -1340, -1182,  1402,    22,  1400, -1340,   -46,
   -1340,    41, -1340,  -952, -1340,    53, -1340, -1340, -1340, -1340,
   -1340,   117,  -256,   349,  1083,   383,  1406,  1407, -1340, -1340,
    -532,    50, -1340, -1340, -1340,   476, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340, -1340,
   -1340, -1340, -1340, -1340, -1340
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1309,   750,  1310,    45,    46,    47,    72,    85,
      87,   101,   103,   129,   134,   142,   144,   259,   262,   265,
     266,   710,  1005,   260,   210,   373,  1305,  1138,   374,  1139,
     377,  1140,   378,  1449,  1450,   381,  1141,  1325,  1434,   383,
    1142,  1548,  1608,  1609,  1442,  1443,  1521,  1637,  1639,  1359,
    1357,  1358,  1638,  1640,  1629,  1444,  1311,  1546,  1602,  1603,
    1604,  1643,  1312,  1422,  1423,  1402,   211,  1367,    48,    49,
      59,   406,    51,   409,  1405,    65,   413,  1407,    69,   418,
    1410,    60,   403,  1403,   281,   282,   283,    52,   385,  1210,
     435,  1313,   315,   316,   317,   318,   319,   320,  1118,  1276,
    1277,   321,   322,   323,   758,   759,   324,   325,   766,   767,
    1073,  1067,  1241,  1242,   326,  1014,  1229,  1377,   327,  1043,
    1569,  1505,  1503,   328,   329,   769,   330,   331,   332,   333,
     334,   822,   823,   907,   372,  1519,  1576,   788,   789,   790,
     791,   792,   793,   794,  1259,   795,   796,   797,   798,   799,
     800,   801,   335,   336,   828,   337,   338,   832,   339,   340,
     829,   830,   341,   342,   837,   838,   839,   840,  1024,  1025,
     343,   344,   345,   346,   347,   846,   847,   348,   349,   212,
     802,   843,   882,   803,   350,   216,   959,   491,   492,   804,
     497,   351,   352,   353,   354,   355,   356,   884,   885,   886,
     357,   358,   359,   751,   752,  1217,  1218,  1051,  1052,  1211,
    1212,  1053,  1380,   902,  1011,   714,  1015,   716,  1017,   717,
     422,  1556,  1490,  1655,  1656,  1475,  1484,  1007,  1013,   715,
     360,   903,   904,   890,   891,   892,   893,  1054,   895,   805,
     806,   807,   898,   899,   361,   727,   808,   656,   657,   219,
     363,   809,   495,  1191,   685,   810,  1003,   697,  1195,  1356,
     222,   811,   618,   813,   619,   814,   680,   681,   996,   997,
     682,   815,   816,   364,   365,   817,   227,   485,   228,   504,
     229,   509,   230,   517,   231,   531,   971,  1172,   232,   539,
     233,   544,   234,   554,   235,   563,   236,   569,   237,   572,
     238,   576,   239,   581,   240,   586,   241,   598,   984,  1181,
     242,   602,   243,   607,   244,   500,   245,   246,   632,   247,
     620,   248,   622,   249,   624,   250,   629,   251,   639,   252,
     642,   253,   648,   254,   694
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   918,    53,   213,   755,   921,   362,   919,   917,   920,
     686,   380,    44,  1055,  1016,  1049,   894,   362,   833,   379,
      56,    57,    58,  1143,  1152,   213,   894,   894,   722,   880,
    1154,   934,  1155,  1153,   217,   263,   213,   699,  1333,   880,
     880,  1340,  1342,  1273,   889,   275,  1341,   844,   937,  1343,
    1058,  1383,   218,   367,   314,   748,   217,   370,  1068,  1512,
    1362,   276,  1072,   277,  1056,   375,  1398,   217,  1652,  1695,
     841,   220,   371,     3,   218,   812,     4,   376,     5,  1274,
    1454,   382,  1466,   221,  1464,   218,     3,  1465,   845,     4,
    1029,     5,    55,   220,  1392,   255,  1113,   841,     6,     7,
       8,     9,   493,     3,   220,   221,     4,  1397,     5,  1235,
    1114,     6,     7,     8,     9,  1598,   221,   729,   841,  1232,
    1234,  1115,   214,  1227,  1334,  1236,  1335,   961,     6,     7,
       8,     9,   658,   749,   434,  1034,   434,   434,     3,  1560,
     434,     4,   434,     5,   214,   434,   434,   223,   998,   434,
     434,   434,   434,   730,    63,   214,   434,  1420,  1421,   434,
     434,  1368,   897,     6,     7,     8,     9,   434,  1374,   223,
     930,  -407,   897,   897,  1492,   437,   439,   213,    54,   442,
     223,   444,   213,  1119,   448,   449,  1275,    55,   456,   458,
     460,   462,  1599,  1600,   261,   467,  1111,  1112,   470,   472,
    1369,   740,   150,   151,   152,  1037,   478,     3,   217,   278,
       4,    71,     5,   217,  1624,     3,    55,   741,     4,  1208,
       5,   698,  1209,  1476,  1369,  1016,   218,   400,   956,  1607,
    1477,   218,     6,     7,     8,     9,  1350,  1352,    86,  1333,
       6,     7,     8,     9,   931,   220,   726,   726,  1375,   102,
     220,   962,   658,  1334,  1493,  1335,     3,   221,   700,     4,
       3,     5,   221,     4,   702,     5,  1478,  1429,  1430,   577,
     362,  1228,   143,   578,   609,  1372,   932,   494,  1452,   450,
    1657,     6,     7,     8,     9,     6,     7,     8,     9,   213,
      55,   313,   486,   487,   208,  1597,   214,   842,   612,  1479,
    1035,   214,   630,   887,   579,   580,   725,   725,  1193,   963,
     731,   267,   393,   887,   887,   208,  1485,  1030,   824,  1393,
     217,   223,    55,   964,  1213,  1214,   223,   631,  1511,   957,
     958,   881,   264,  1574,   300,   380,   743,   744,   218,   362,
    1496,   881,   881,   379,   256,   257,   258,   419,  1397,  1469,
     302,  1008,  1009,  1207,   362,   303,   640,   220,   213,   380,
     853,  1369,  1625,   368,  1571,  1485,  1109,   379,  1480,   221,
     208,  1282,  1670,   213,  1668,  1513,   380,  1669,  1057,   224,
    1399,   641,  1653,  1696,   379,  1283,  -163,   914,  1470,   217,
     831,   488,   489,  1679,  1117,   490,  1284,   208,   369,  1412,
     599,   224,   929,   855,   217,   208,  1336,   218,   214,   570,
    1394,  1601,   224,   225,   371,   313,   208,   276,   208,  1260,
     277,   880,   218,  1683,   376,   571,   220,   611,  1558,   382,
     451,  1252,   421,   223,   479,   225,   753,  1486,   221,   721,
     965,   220,   933,   256,   257,   258,   225,   452,  1573,  1508,
     883,   600,   601,   221,   966,   747,   279,   280,  1481,   496,
     883,   883,   268,   394,   269,   395,  1194,  1516,   818,   819,
     820,  1280,  1281,   603,   434,  1630,  1632,   214,  1089,   609,
    1631,  1092,     3,  1633,  1075,     4,  1486,     5,    55,     4,
    1471,     5,   214,  1537,   953,   609,  1382,  1076,   420,  1055,
     421,  1049,   223,   612,   604,   605,   226,     6,     7,     8,
       9,  -181,  1077,   940,   615,   616,  1552,   223,   935,   612,
    1239,  1090,   825,   826,   827,  1240,   880,  1487,   366,  1333,
    1026,  1554,    50,   606,   621,  1463,  1555,  1121,  1055,   366,
    1049,  1120,    61,    50,    50,    64,    64,    64,    68,   573,
    1413,    50,  1414,   224,   897,   445,   446,   844,   224,   574,
     575,  1149,  1150,  1151,    55,   623,  1314,  1315,  1316,  1317,
     880,  1318,   853,   683,  1319,  1161,  1551,   688,   540,     4,
    1472,     5,  1249,   684,   392,  1132,  -643,   225,   854,  1258,
    1190,  1320,   225,  1351,   825,   826,   827,   617,   541,  1062,
     417,  1128,    50,   582,   701,   387,    50,    64,    64,    64,
      68,   542,  1289,   821,  1129,   855,  1130,    50,   443,   401,
     405,   407,    50,   411,    64,    64,   416,  1078,   401,   401,
     401,   401,  1063,    64,   583,   584,   433,   585,    50,  1321,
     718,    64,    64,  1627,    68,   438,  1064,    64,  1529,  1530,
    1531,  1532,   897,   897,   897,   897,   897,   719,   643,   897,
      18,    19,   482,   483,   484,   224,   474,    50,    64,    64,
     130,   644,    64,   723,    50,   131,   132,   739,   645,     3,
     226,  1116,     4,   897,     5,   226,   501,   502,   503,     3,
    1065,   133,     4,   742,     5,  1050,   646,   213,     4,   225,
       5,  1539,   647,   897,     6,     7,     8,     9,     4,    34,
       5,   743,   744,  1006,     6,     7,     8,     9,    35,  1543,
     720,  1692,  1537,   881,    36,   543,     3,   844,   217,     4,
       3,     5,   760,     4,   224,     5,  1674,  1663,  1650,  1066,
     746,  1651,  1682,   609,  1686,  1678,   218,  1196,    37,   224,
     768,     6,     7,     8,     9,     6,     7,     8,     9,  1583,
    1584,  1585,  1087,   611,  1088,   220,   749,   612,   225,     3,
     287,   288,     4,  1173,     5,   289,   845,   221,  1469,  1055,
    1279,  1049,  1271,   225,   498,   499,  1285,  1167,  1287,  1288,
      62,   753,   366,   844,     6,     7,     8,     9,   850,  1129,
     887,  1130,  1322,  1168,   906,   851,  1174,   842,  1169,  1170,
    1314,  1315,  1316,  1317,   852,  1318,   214,  1470,  1319,   695,
     696,   881,   881,   881,   881,   881,   213,   908,   881,   900,
     761,   762,   763,   764,   765,  1320,  1216,   756,   757,  1485,
     901,   223,   883,   505,   887,   506,   507,   508,   906,   384,
     615,   616,   881,   388,  1106,   909,  1436,   217,  1108,   848,
     849,   366,  1175,  1176,  1177,  1178,  1179,  1180,   408,   384,
     625,   910,   881,  1171,   911,   218,   366,   912,   274,   278,
    1437,  1438,     4,  1321,     5,   436,  1251,   897,  1251,  1251,
    1251,  1381,  1251,  1251,   220,   256,   257,   258,  1265,  1265,
     941,  1135,   743,   744,  1136,  1371,   221,   880,   942,   626,
     627,   628,   943,  1026,   475,  1216,  1445,  1446,  1447,  1471,
    1448,   481,   834,   835,   836,  1010,   897,   897,   897,   897,
     897,   897,   897,   617,   897,   897,   564,  1016,  1687,   954,
     883,   883,   883,   883,   883,   214,   880,   883,  1390,   955,
    1391,   960,   565,     3,  1041,  1042,     4,   986,     5,   999,
    1486,   566,  1396,  1439,   150,   151,   152,   567,   568,   938,
     223,   883,  1415,  1416,  1417,  1418,    64,   842,     6,     7,
       8,     9,   987,  1440,  1441,  1000,   945,  1001,   946,  1002,
     947,   883,   948,   988,   989,  1082,  1083,   949,  1004,  1671,
     950,  1593,   951,   213,  1010,   455,   990,  1123,  1124,  1549,
      64,  1012,   457,  1027,   991,  1184,  1185,  1594,  1022,  1523,
      18,    19,  1595,  1525,  1596,  1522,  1524,    18,    19,  1028,
     992,   825,   826,   827,   217,  1261,  1031,   897,  1476,  1436,
     897,  1186,  1187,   842,  1032,  1477,  1461,  1033,  1536,  1036,
    1705,  1038,   218,   749,  1233,  1250,   881,  1250,  1250,  1250,
    1045,  1250,  1250,  1437,  1438,   835,   836,  1264,  1264,    34,
    1542,   220,  1048,   224,  1354,  1355,    34,  1059,    35,   897,
     213,  1478,   213,   221,    36,    35,  1526,  1527,  1528,  1660,
     459,    36,  1060,   362,  1084,   881,   881,   881,   881,   881,
     881,   881,  1069,   881,   881,    18,    19,   225,    37,  1432,
    1433,   217,   213,   217,  1479,    37,   993,   994,   995,   666,
    1641,  1642,   214,  1498,  1499,  1500,  1501,  1502,  1070,   218,
    1071,   218,   676,   677,   678,  1085,  1290,  1303,  1086,  1323,
    1331,  1337,  1091,   217,  1266,  1267,  1439,   223,   220,  1304,
     220,  1324,  1332,  1338,    34,   633,   967,   968,   969,   970,
     221,   218,   221,    35,   689,  -842,  1440,  1441,  -843,    36,
     634,   362,  1093,   690,   691,   883,  1216,   692,   693,  1094,
     220,  1050,  1095,  1480,  1567,  1096,  1097,   880,  1099,  1100,
     213,   635,   221,    37,   896,  1105,  1107,   636,  1026,   214,
     226,   214,   224,  1122,   896,   896,   881,     3,  1125,   881,
       4,  1126,     5,  1127,   883,   883,   883,   883,   883,   883,
     883,   217,   883,   883,   223,  1131,   223,  1137,   362,   608,
    1144,   214,     6,     7,     8,     9,   225,  1145,  1146,   218,
     609,  1147,   610,  1148,  1156,   637,   638,   213,   881,     3,
    1157,  1158,     4,  1159,     5,  1160,   223,  1190,   220,  1424,
     611,  1165,  1182,  1183,   612,  1188,  1189,   613,  1192,  1197,
     221,  1198,  1200,  1550,     6,     7,     8,     9,   217,   135,
    1202,   136,   461,  1204,  1199,  1215,   137,  1334,   138,  1335,
     853,  1222,   139,  1224,   362,  1230,   218,    18,    19,   424,
     426,   428,   430,  1226,  1419,  1404,  1406,  1406,  1409,   214,
    1426,  1427,  1428,   213,   614,   220,  1245,  1243,  1026,  1244,
     897,  1238,  1246,  1256,  1451,   883,  1248,   221,   883,   226,
    1278,   140,  1456,   141,   223,  1286,  1344,  1345,  1303,  1346,
    1323,  1331,  1337,   213,   217,  1347,    34,   615,   616,  1348,
    1304,  1349,  1324,  1332,  1338,    35,  1473,  1482,  1488,  1353,
    1360,    36,   218,  1361,  1365,   213,   214,   883,  1474,  1483,
    1489,  1366,  1370,  1376,   217,  1379,   380,     3,  1384,   224,
       4,   220,     5,  1385,   379,    37,  1386,   532,  1387,   533,
    1389,   223,   218,   221,     3,  1400,   217,     4,   380,     5,
    1401,  1411,     6,     7,     8,     9,   379,   534,  1425,  1431,
    1435,   220,  1453,   225,   218,   535,   536,   537,   538,     6,
       7,     8,     9,   221,  1457,  1467,   510,   511,  1534,  1535,
     617,  1468,   214,   220,   512,   513,   514,   515,   516,  1458,
    1491,  1504,  1538,  1497,  1506,   221,   735,  1514,  1540,  1515,
     362,  1541,  1520,  1518,  1544,  1533,   224,   223,   224,  1545,
    1547,  1553,   214,  1473,  1482,  1488,  1469,  1559,  1012,   213,
    1563,  1561,  1162,  1163,  1164,  1474,  1483,  1489,  1314,  1315,
    1316,  1317,  1568,  1318,   214,   213,  1319,   223,   224,   881,
     225,  1570,   225,  1575,  1590,  1572,  1578,  1607,  1605,  1557,
     217,  1622,  1619,  1320,  1579,  1470,   226,  1580,  1562,   223,
    1581,  1623,  1649,  1658,  1564,  1582,   217,  1586,   218,  1577,
    1587,  1588,   225,    18,    19,  1589,   703,  1675,   704,  1626,
     705,   706,  1654,  1611,   218,  1634,  1635,   220,   707,   708,
    1636,  1688,  1690,  1694,  1691,  1606,  1711,  1610,   555,   221,
     556,  1321,    70,   220,  1339,  1612,  1613,  1614,  1615,  1616,
    1617,  1618,  1710,  1620,  1455,   221,   224,  1693,   557,  1667,
    1592,   709,    34,  1689,  1591,   404,   558,   559,  1408,   560,
     410,    35,   913,   226,   362,   226,   896,    36,   214,   561,
     562,   754,  1644,  1645,  1646,  1647,  1648,   916,  1395,  1517,
     225,  1061,  1509,   213,   214,  1074,   745,  1471,   883,  1494,
    1201,    37,  1566,   223,  1621,   366,   290,   291,   292,   293,
     294,   295,  1565,   224,  1098,   915,  1659,  1253,  1661,   223,
    1323,  1331,  1337,  1628,   217,  1254,  1672,  1676,  1680,  1684,
    1662,  1255,  1324,  1332,  1338,  1269,  1104,  1272,  1673,  1677,
    1681,  1685,   218,  1257,  1110,   215,  1697,   225,  1166,  1698,
     724,   687,  1237,  1699,  1700,  1701,  1702,  1473,  1482,  1488,
    1706,   220,   927,   905,  1707,   925,   453,  1712,  1708,  1474,
    1483,  1489,  1709,   221,   896,   896,   896,   896,   896,   224,
     928,   896,   926,   366,   888,  1713,   728,  1703,   733,    66,
      67,   985,  1714,  1715,  1716,   737,   738,  1021,     0,  1023,
       0,     0,     0,     0,  1665,   896,     0,     0,     0,   224,
       0,     0,   214,   225,     0,  1039,  1040,     0,  1044,     0,
       0,     0,  1046,  1047,     0,   896,     0,     0,     0,     0,
       3,   224,     0,     4,     0,     5,     0,   223,     0,     0,
     366,     0,     0,   225,     0,     0,  1079,     0,     0,  1081,
     389,   390,   391,     0,     0,     6,     7,     8,     9,   270,
     271,   272,   273,     0,  1291,   225,   412,   414,   415,     0,
       0,     0,     3,  1292,     0,     4,   431,     5,  1293,     0,
    1294,     0,  1295,     0,   440,   441,     0,     0,     0,     0,
     447,     0,     0,   386,     0,     0,     0,     6,     7,     8,
       9,   396,   397,   398,   399,     0,   366,  1102,   402,     0,
    1103,   476,   477,     0,     0,   480,     0,   423,   425,   427,
     429,     0,     0,     0,   432,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   224,   226,     0,     0,     0,
     454,     0,     0,     0,     0,   463,   464,   465,     0,     0,
     468,   224,     0,   473,     0,     0,     3,  1476,   226,     4,
       0,     5,     0,   466,  1477,     0,     0,     0,     0,   225,
       0,     0,     0,     0,     0,     0,  1133,  1134,    18,    19,
       0,     6,     7,     8,     9,   225,     0,  1296,     0,     0,
    1291,     0,     3,     0,     0,     4,     0,     5,     0,  1292,
    1478,     0,     0,     0,  1293,     0,  1294,   587,  1295,   896,
       0,     0,     0,     0,    88,     0,   588,     6,     7,     8,
       9,    89,     0,    90,     0,    91,     0,    34,    92,    93,
      94,   589,    95,  1479,     0,   590,    35,     0,   591,   592,
       0,     0,    36,   593,   594,   595,   596,   597,   896,   896,
     896,   896,   896,   896,   896,   469,   896,   896,     0,  1297,
       0,     0,   366,     0,     0,     0,    37,     0,     0,   224,
      18,    19,     0,     0,  1298,     0,     0,  1326,   226,  1327,
       0,  1318,     0,     0,  1319,     0,     0,   711,   712,   713,
    1299,     0,     0,     0,  1203,  1300,     0,  1301,  1206,     0,
       0,  1328,  1480,   225,     0,     0,     0,  1219,  1220,  1221,
       0,     0,  1223,  1296,  1225,   471,     0,     0,     3,    34,
       0,     4,     0,     5,  1231,     0,     0,     0,    35,     0,
      18,    19,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     7,     8,     9,     0,     0,  1329,
    1302,     0,     0,     0,     0,     0,  1247,     0,    37,   896,
       0,     0,   896,     0,     0,     0,     0,  1262,     0,  1263,
       0,     0,     0,     0,     0,  1268,     0,  1270,     0,    34,
       0,     0,     0,     0,     0,  1297,     0,     0,    35,     0,
       0,     0,  1704,     0,    36,     0,   366,     0,     0,     0,
    1298,   896,     0,  1326,     0,  1327,     0,  1318,     0,    96,
    1319,     0,     0,   922,   923,   924,  1299,     0,    37,   939,
       0,  1300,  -799,  1301,    97,     0,     0,  1328,     0,     0,
       0,     0,     0,     3,     0,     0,     4,     0,     5,     0,
      98,     0,   936,     0,     0,    99,     0,   100,     0,   545,
     546,     0,     0,   952,     0,     0,     0,     0,     6,     7,
       8,     9,     0,   547,     0,   548,   549,   550,     0,     3,
       0,     0,     4,   944,     5,  1329,  1459,     0,     0,     0,
    1363,  1364,     0,     0,     0,     0,     0,     0,   551,   552,
     553,   145,     0,     0,     6,     7,     8,     9,   146,   147,
    1373,   284,   148,   285,     0,     0,  1378,     0,  -798,     0,
       0,     0,  1330,     0,     0,     0,     0,   286,  1326,     0,
    1327,     0,  1318,     0,  1388,  1319,     0,   287,   288,     0,
       0,     0,   289,     0,     0,   518,   519,     0,     0,   520,
       0,     0,  1328,   290,   291,   292,   293,   294,   295,   521,
     522,   523,   524,   525,   526,   527,   528,   529,  1306,     0,
       0,     0,   296,     0,   297,     0,     0,   149,   150,   151,
     152,     0,     0,   153,     0,   154,     0,    73,  1307,   155,
       0,     0,     0,   156,    74,     0,    75,     0,     0,   157,
    1329,    76,    77,    78,     0,    79,     0,   530,     0,     0,
       0,     0,     0,     0,     0,   158,     0,     0,     0,     0,
     159,     0,     0,   160,     0,     0,     0,     0,   161,     0,
       0,   162,     0,     0,   163,   164,     0,     0,   165,     0,
       0,   166,     0,   167,     0,     0,     0,     0,  1462,     0,
     972,  1495,   896,   973,   974,   975,   976,   977,   978,   979,
     980,   981,   982,   983,     0,  1507,   168,   169,     0,   170,
     171,   172,   173,     0,     0,  1510,     0,     0,   174,   175,
       0,     0,   176,   177,   298,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,     0,     0,   299,     0,
     545,   546,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   300,   547,     0,   548,   549,   550,     0,
       0,     0,     0,   301,     0,     0,     0,     0,     0,   302,
       0,     0,     0,     0,   303,     0,     0,     0,     0,   551,
     552,   553,     0,   201,   202,     0,   304,     0,     0,   305,
     306,   307,   308,  1666,     0,     0,   309,     0,     0,     0,
     310,   311,   203,     0,     0,     0,   204,   205,     3,     0,
       0,     4,    80,     5,     0,   312,     0,     0,   206,   207,
       0,     0,     0,     0,     0,     0,     0,    81,   313,  1308,
     145,   208,   209,     6,     7,     8,     9,   146,   147,     0,
     284,   148,   285,    82,     0,     0,     0,     0,    83,     0,
      84,     0,     0,     0,     0,     0,   286,     0,   518,   519,
       0,     0,   520,     0,     0,     0,   287,   288,     0,     0,
       0,   289,   521,   522,   523,   524,   525,   526,   527,   528,
     529,     0,   290,   291,   292,   293,   294,   295,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1306,     0,     0,
       0,   296,     0,   297,     0,     0,   149,   150,   151,   152,
       0,     0,   153,     0,   154,     0,     0,  1307,   155,     0,
     530,     0,   156,     0,     0,     0,     0,     0,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   158,     0,     0,     0,     0,   159,
       0,     0,   160,     0,     0,     0,     0,   161,     0,     0,
     162,     0,     0,   163,   164,     0,     0,   165,    10,     0,
     166,     0,   167,     0,     0,    11,     0,    12,     0,    13,
       0,     0,    14,    15,    16,     0,    17,     0,     0,     0,
      18,    19,     0,     0,     0,   168,   169,     0,   170,   171,
     172,   173,     0,     0,     0,     0,     0,   174,   175,     0,
       0,   176,   177,   298,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,     0,     0,   299,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     0,   300,     0,    36,     0,     0,     0,     0,     0,
       0,     0,   301,     0,     0,     0,     0,     0,   302,     0,
       0,     0,     0,   303,     0,     0,     0,     0,    37,     0,
       0,     0,   201,   202,     0,   304,     0,     0,   305,   306,
     307,   308,     0,     0,     0,   309,     0,     0,     0,   310,
     311,   203,     0,     0,     0,   204,   205,     3,     0,     0,
       4,     0,     5,     0,   312,     0,     0,   206,   207,     0,
       0,     0,     0,     0,     0,     0,     0,   313,  1460,   145,
     208,   209,     6,     7,     8,     9,   146,   147,     0,   284,
     148,   285,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   286,     0,     0,     0,     0,
       0,     0,     0,    38,     0,   287,   288,     0,     0,     0,
     289,     0,     0,     0,     0,     0,     0,     0,    39,     0,
       0,   290,   291,   292,   293,   294,   295,     0,     0,     0,
       0,     0,     0,     0,    40,     0,  1306,     0,     0,    41,
     296,    42,   297,     0,     0,   149,   150,   151,   152,     0,
       0,   153,     0,   154,     0,     0,  1307,   155,     0,     0,
       0,   156,     0,     0,     0,     0,     0,   157,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158,     0,     0,     0,     0,   159,     0,
       0,   160,     0,     0,     0,     0,   161,     0,     0,   162,
       0,     0,   163,   164,     0,     0,   165,     0,     0,   166,
       0,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   168,   169,     0,   170,   171,   172,
     173,     0,     0,     0,     0,     0,   174,   175,     0,     0,
     176,   177,   298,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,     0,     0,   299,     0,     0,   770,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   300,     0,     0,     0,   771,     0,   145,     0,     0,
       0,   301,     0,     0,     0,   147,     0,   302,   148,     0,
       0,     0,   303,     0,     0,     0,     0,     0,     0,     0,
       0,   201,   202,     0,   304,     0,     0,   305,   306,   307,
     308,     0,     0,     0,   309,     0,     0,     0,   310,   311,
     203,   772,     0,     0,   204,   205,     0,     0,     0,     0,
       0,     0,     0,   312,     0,   773,   206,   207,     0,     0,
       0,     0,     0,     0,     0,     0,   313,  1664,     0,   208,
     209,     0,     0,   149,   150,   151,   152,     0,     0,   153,
       0,   774,     0,     0,     0,   775,     0,     0,     0,   776,
       0,     0,     0,     0,     0,   777,     0,     0,     0,   778,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,     0,     0,     0,   159,     0,     0,   779,
       0,     0,     0,     0,   161,     0,     0,   162,     0,     0,
     163,   164,     0,     0,   165,     0,     0,   166,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,   169,     0,   780,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,     0,     0,   200,  1018,     0,     0,     0,     0,
       0,     0,     0,     0,   781,     0,     0,   782,   783,     0,
       0,   771,     0,   145,     0,     0,     0,     0,     0,     0,
       0,   147,     0,     0,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
     202,     0,     0,     0,     0,   784,   785,     0,     0,     0,
     649,     0,     0,     0,     0,     0,     0,   772,   203,     0,
       0,     0,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,   786,   787,     0,   655,   650,     0,     0,   651,
       0,     0,     0,     0,     0,     0,     0,   208,     0,   149,
     150,   151,   152,     0,     0,   153,   652,   774,     0,     0,
       0,   775,     0,     0,     0,   776,     0,     0,     0,     0,
       0,  1019,     0,     0,     0,   778,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,     0,     0,  1020,     0,     0,     0,     0,
     161,     0,     0,   162,     0,     0,   163,   164,     0,     0,
     165,     0,     0,   166,     0,   167,     0,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   168,   169,
       0,   780,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   653,     0,
     200,  1080,     0,     0,     0,   201,   202,     0,     0,     0,
     781,     0,     0,   782,   783,   654,     0,   771,     0,   145,
       0,     0,     0,     0,     0,     0,     0,   147,     0,     0,
     148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   655,     0,     0,     0,   201,   202,     0,     0,     0,
       0,   784,   785,     0,     0,     0,   732,     0,     0,     0,
       0,     0,     0,   772,   203,     0,     0,     0,   204,   205,
       0,     0,     0,     0,     0,     0,     0,     0,   786,   787,
       0,   655,   650,     0,     0,   651,     0,     0,     0,     0,
       0,     0,     0,   208,     0,   149,   150,   151,   152,     0,
       0,   153,   652,   774,     0,     0,     0,   775,     0,     0,
       0,   776,     0,     0,     0,     0,     0,  1019,     0,     0,
       0,   778,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158,     0,     0,     0,     0,   159,     0,
       0,  1020,     0,     0,     0,     0,   161,     0,     0,   162,
       0,     0,   163,   164,     0,     0,   165,     0,     0,   166,
       0,   167,     0,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   168,   169,     0,   780,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   653,     0,   200,  1101,     0,     0,
       0,   201,   202,     0,     0,     0,   781,     0,     0,   782,
     783,   654,     0,   771,     0,   145,     0,     0,     0,     0,
       0,     0,     0,   147,     0,     0,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   655,     0,     0,
       0,   201,   202,     0,     0,     0,     0,   784,   785,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   772,
     203,     0,     0,     0,   204,   205,     0,     0,     0,     0,
       0,     0,     0,     0,   786,   787,     0,   655,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   208,
       0,   149,   150,   151,   152,     0,     0,   153,     0,   774,
       0,     0,     0,   775,     0,     0,     0,   776,     0,     0,
       0,     0,     0,  1019,     0,     0,     0,   778,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
       0,     0,     0,     0,   159,     0,     0,  1020,     0,     0,
       0,     0,   161,     0,     0,   162,     0,     0,   163,   164,
       0,     0,   165,     0,     0,   166,     0,   167,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     168,   169,     0,   780,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
       0,     0,   200,  1205,     0,     0,     0,     0,     0,     0,
       0,     0,   781,     0,     0,   782,   783,     0,     0,   771,
     734,   145,     0,     0,     0,     0,     0,     0,     0,   147,
       0,     0,   148,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   659,   660,     0,     0,     0,   201,   202,     0,
       0,     0,     0,   784,   785,     0,     0,     0,     0,     0,
       0,     0,     0,   661,     0,   772,   203,     0,     0,     0,
     204,   205,     0,     0,     0,     0,     0,     0,     0,     0,
     786,   787,     0,   655,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   208,     0,   149,   150,   151,
     152,     0,     0,   153,     0,   774,     0,     0,     0,   775,
       0,     0,     0,   776,     0,     0,     0,   735,     0,  1019,
       0,     0,     0,   778,     0,     0,     0,     0,   659,   660,
       0,     0,     0,     0,     0,   158,     0,     0,     0,     0,
     159,   662,     0,  1020,     0,     0,     0,     0,   161,   661,
       0,   162,     0,     0,   163,   164,     0,     0,   165,     0,
       0,   166,     0,   167,     0,   663,   664,   665,   666,   667,
     668,   736,   669,   670,   671,   672,   673,   674,   675,     0,
       0,   676,   677,   678,     0,     0,   168,   169,     0,   780,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   679,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,     0,   662,   200,     0,
       0,     0,   856,   857,   858,   859,   860,   861,   781,     0,
       0,   782,   783,     0,   771,     0,   841,     0,     0,     0,
       0,   663,   664,   665,   666,   667,   668,     0,   669,   670,
     671,   672,   673,   674,   675,     0,     0,   676,   677,   678,
       0,     0,     0,   201,   202,     0,     0,     0,     0,   784,
     785,     0,     0,     0,     0,     0,     0,     0,   679,     0,
     772,     0,   203,     0,     0,     0,   204,   205,     0,     0,
       0,     0,     0,     0,     0,     0,   786,   787,     0,   655,
       0,     0,     0,     0,     0,   771,     0,   841,     0,     0,
       0,   208,   149,   150,   151,   152,     0,     0,     0,     0,
     862,     0,     0,     0,   863,     0,     0,     0,   864,     0,
       0,     0,     0,     0,   865,     0,     0,     0,   778,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     866,   772,     0,     0,     0,   867,     0,     0,   868,     0,
       0,     0,     0,   869,     0,     0,   870,     0,     0,   871,
     872,     0,     0,   873,     0,     0,   874,     0,   875,     0,
       0,     0,     0,   149,   150,   151,   152,     0,     0,     0,
       0,   862,     0,     0,     0,   863,     0,     0,     0,   864,
       0,   876,   877,     0,     0,   865,     0,     0,     0,   778,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   866,     0,     0,     0,     0,   867,     0,     0,   868,
       0,     0,     0,     0,   869,     0,     0,   870,     0,     0,
     871,   872,     0,     0,   873,     0,     0,   874,     0,   875,
       0,     0,     0,   781,     0,     0,   782,   783,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   771,     0,     0,
       0,     0,   876,   877,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   784,   785,     0,   878,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   772,     0,     0,     0,     0,     0,     0,
       0,   786,   787,     0,   781,     0,     0,   782,   783,     0,
       0,     0,     0,   313,     0,     0,   208,   879,   771,     0,
       0,     0,     0,     0,     0,   149,   150,   151,   152,     0,
       0,     0,     0,   862,     0,     0,     0,   863,     0,     0,
       0,   864,     0,     0,     0,   784,   785,   865,   878,     0,
       0,   778,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   866,   772,     0,     0,     0,   867,     0,
       0,   868,   786,   787,     0,     0,   869,     0,     0,   870,
       0,     0,   871,   872,   313,     0,   873,   208,   879,   874,
       0,   875,     0,     0,     0,     0,   149,   150,   151,   152,
       0,     0,     0,     0,   862,     0,     0,     0,   863,     0,
       0,     0,   864,     0,   876,   877,     0,     0,   865,     0,
       0,     0,   778,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   866,     0,     0,     0,     0,   867,
       0,     0,   868,     0,     0,     0,     0,   869,     0,     0,
     870,     0,     0,   871,   872,     0,     0,   873,     0,     0,
     874,     0,   875,     0,     0,     0,   781,     0,     0,   782,
     783,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     771,     0,   145,     0,     0,   876,   877,     0,     0,     0,
     147,     0,     0,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   784,   785,     0,
     878,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   772,     0,     0,     0,
       0,     0,     0,     0,   786,   787,     0,   781,     0,     0,
     782,   783,     0,     0,     0,     0,   313,     0,     0,   208,
     879,     0,     0,     0,     0,     0,     0,     0,   149,   150,
     151,   152,     0,     0,   153,     0,   774,     0,     0,     0,
     775,     0,     0,     0,   776,     0,     0,     0,   784,   785,
    1019,   878,     0,     0,   778,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   158,     0,     0,     0,
       0,   159,     0,     0,  1020,   786,   787,     0,     0,   161,
       0,     0,   162,     0,     0,   163,   164,     0,     0,   165,
     208,   879,   166,     0,   167,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   168,   169,     0,
     780,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,     0,     0,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   781,
       0,     0,   782,   783,     0,     0,     0,   145,     0,     0,
       0,     0,     0,     0,   146,   147,     0,   284,   148,   285,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   286,   201,   202,     0,     0,     0,     0,
     784,   785,     0,   287,   288,     0,     0,     0,   289,     0,
       0,     0,     0,   203,     0,     0,     0,   204,   205,   290,
     291,   292,   293,   294,   295,     0,     0,   786,   787,     0,
     655,     0,     0,     0,     0,     0,     0,     0,   296,     0,
     297,     0,   208,   149,   150,   151,   152,     0,     0,   153,
       0,   154,     0,     0,     0,   155,     0,     0,     0,   156,
       0,     0,     0,     0,     0,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,     0,     0,     0,   159,     0,     0,   160,
       0,     0,     0,     0,   161,     0,     0,   162,     0,     0,
     163,   164,     0,     0,   165,     0,     0,   166,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,   169,     0,   170,   171,   172,   173,     0,
       0,     0,     0,     0,   174,   175,     0,     0,   176,   177,
     298,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,     0,     0,   299,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   300,
       0,     0,     0,   145,     0,     0,     0,     0,     0,   301,
     146,   147,     0,     0,   148,   302,     0,     0,     0,     0,
     303,     0,     0,     0,     0,     0,     0,     0,     0,   201,
     202,     0,   304,     0,     0,   305,   306,   307,   308,     0,
       0,     0,   309,     0,     0,     0,   310,   311,   203,     0,
       0,     0,   204,   205,     0,     0,     0,     0,     0,     0,
       0,   312,     0,     0,   206,   207,     0,     0,     0,     0,
     772,     0,     0,     0,   313,     0,     0,   208,   209,   149,
     150,   151,   152,     0,     0,   153,     0,   154,     0,     0,
       0,   155,     0,     0,     0,   156,     0,     0,     0,     0,
       0,   157,     0,   150,   151,   152,     0,     0,     0,     0,
     862,     0,     0,     0,   863,     0,     0,   158,   864,     0,
       0,     0,   159,     0,   865,   160,     0,     0,   778,     0,
     161,     0,     0,   162,     0,     0,   163,   164,     0,     0,
     165,     0,     0,   166,     0,   167,     0,     0,   868,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   168,   169,
       0,   170,   171,   172,   173,     0,     0,     0,     0,     0,
     174,   175,     0,     0,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,     0,     0,
     200,     0,     0,     0,     0,     0,     0,   145,     0,     0,
       0,     0,     0,     0,   146,   147,     0,     0,   148,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   781,     0,     0,   782,   783,     0,     0,
       0,     0,     0,     0,     0,   201,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,     0,     0,     0,   204,   205,
       0,     0,     0,     0,   784,   785,     0,     0,     0,     0,
     206,   207,     0,   149,   150,   151,   152,     0,     0,   153,
     313,   154,     0,   208,   209,   155,     0,     0,     0,   156,
       0,     0,     0,     0,     0,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   208,     0,     0,     0,
       0,   158,     0,     0,     0,     0,   159,     0,     0,   160,
       0,     0,     0,     0,   161,     0,     0,   162,     0,     0,
     163,   164,     0,     0,   165,     0,     0,   166,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,   169,     0,   170,   171,   172,   173,     0,
       0,     0,     0,     0,   174,   175,     0,     0,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,     0,     0,   200,     0,     0,     0,     0,     0,
       0,   145,     0,     0,     0,     0,     0,     0,     0,   147,
       0,     0,   148,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
     202,     0,     0,     0,     0,   772,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,     0,
       0,     0,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   206,   207,     0,   149,   150,   151,
     152,     0,     0,   153,     0,   774,     0,   208,   209,   775,
       0,     0,     0,   776,     0,     0,     0,     0,     0,  1019,
       0,     0,     0,   778,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   158,     0,     0,     0,     0,
     159,     0,     0,  1020,     0,     0,     0,     0,   161,     0,
       0,   162,     0,     0,   163,   164,     0,     0,   165,     0,
       0,   166,     0,   167,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   168,   169,     0,   780,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,     0,     0,   200,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   781,     0,
       0,   782,   783,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,   202,     0,     0,     0,     0,   784,
     785,     0,     0,     0,     2,     3,     0,     0,     4,     0,
       5,     0,   203,     0,     0,     0,   204,   205,     0,     0,
       0,     0,     0,     0,     0,     0,   786,   787,     0,   655,
       6,     7,     8,     9,     0,     0,     0,     0,     0,    10,
       0,   208,     0,     0,     0,     0,    11,     0,    12,     0,
      13,     0,     0,    14,    15,    16,     0,    17,     0,     0,
       0,    18,    19,    20,     0,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     0,     0,
     772,     0,     0,     0,     0,     0,     0,     0,   290,   291,
     292,   293,   294,   295,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -301,     0,     0,     0,     0,     0,
      34,     0,   149,   150,   151,   152,     0,     0,     0,    35,
     862,     0,     0,     0,   863,    36,     0,     0,   864,     0,
       0,     0,     0,     0,   865,     0,     0,     0,   778,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
     866,     0,   772,     0,     0,   867,     0,     0,   868,     0,
       0,     0,     0,   869,     0,     0,   870,     0,     0,   871,
     872,     0,     0,   873,     0,     0,   874,     0,   875,     0,
       0,     0,     0,     0,   149,   150,   151,   152,     0,     0,
       0,     0,   862,     0,     0,     0,   863,     0,     0,     0,
     864,   876,   877,     0,     0,     0,   865,     0,     0,     0,
     778,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   866,     0,     0,     0,     0,   867,     0,     0,
     868,     0,     0,     0,    38,   869,     0,     0,   870,     0,
       0,   871,   872,     0,     0,   873,     0,     0,   874,    39,
     875,     0,     0,   781,     0,     0,   782,   783,     0,     0,
       0,     0,     0,     0,     0,    40,     0,     0,     0,     0,
      41,   104,    42,   876,   877,     0,     0,     0,   105,   106,
     107,   108,     0,     0,   109,   110,     0,   111,   112,   113,
       0,   114,     0,     0,   784,   785,     0,   878,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   786,   787,     0,     0,   781,     0,     0,   782,   783,
     115,     0,   116,   117,   118,     0,   208,   879,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   784,   785,     0,   878,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   786,   787,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   208,   879,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   119,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   120,     0,     0,     0,     0,   121,   122,   123,   124,
       0,     0,     0,     0,     0,     0,     0,   125,     0,     0,
       0,     0,   126,     0,   127,   128
};

static const yytype_int16 yycheck[] =
{
       1,   389,     3,    30,   316,   392,    52,   390,   388,   391,
     204,    66,     1,   750,   717,   750,   358,    63,   338,    66,
       7,     8,     9,   915,   925,    52,   368,   369,   284,   358,
     927,   414,   928,   926,    30,    32,    63,   209,  1141,   368,
     369,  1145,  1147,  1107,   358,    46,  1146,   344,   431,  1148,
     753,  1233,    30,    54,    52,   311,    52,    58,   761,     5,
    1202,    48,   765,    50,     7,    63,     7,    63,     7,     7,
      23,    30,    59,     1,    52,   331,     4,    64,     6,  1109,
    1328,    68,  1346,    30,  1344,    63,     1,  1345,    42,     4,
      93,     6,   100,    52,     5,    55,   850,    23,    26,    27,
      28,    29,    32,     1,    63,    52,     4,  1275,     6,  1052,
     851,    26,    27,    28,    29,    22,    63,    59,    23,  1050,
    1051,   852,    30,   100,    39,  1056,    41,   122,    26,    27,
      28,    29,   178,     4,   106,    99,   108,   109,     1,  1478,
     112,     4,   114,     6,    52,   117,   118,    30,   680,   121,
     122,   123,   124,    95,    13,    63,   128,    75,    76,   131,
     132,  1209,   358,    26,    27,    28,    29,   139,    20,    52,
      54,    99,   368,   369,    20,   108,   109,   204,   101,   112,
      63,   114,   209,   854,   117,   118,  1117,   100,   121,   122,
     123,   124,    99,   100,    55,   128,   848,   849,   131,   132,
    1211,   246,   100,   101,   102,   737,   139,     1,   204,    54,
       4,    46,     6,   209,   100,     1,   100,   262,     4,    86,
       6,   208,    89,    86,  1235,   928,   204,    86,   110,   100,
      93,   209,    26,    27,    28,    29,  1188,  1189,    46,  1342,
      26,    27,    28,    29,    54,   204,   293,   294,   100,    50,
     209,   246,   298,    39,   100,    41,     1,   204,   255,     4,
       1,     6,   209,     4,   261,     6,   129,  1315,  1316,   126,
     316,   248,    44,   130,   121,  1218,    54,   207,  1326,    86,
    1619,    26,    27,    28,    29,    26,    27,    28,    29,   316,
     100,   320,   108,   109,   323,  1543,   204,   344,   145,   162,
     264,   209,   123,   358,   161,   162,   293,   294,   155,   107,
     297,    86,    86,   368,   369,   323,   110,   320,    81,   230,
     316,   204,   100,   121,  1027,  1028,   209,   148,  1392,   211,
     212,   358,   100,  1515,   245,   390,   264,   265,   316,   385,
    1370,   368,   369,   390,   304,   305,   306,    86,  1516,    90,
     261,   712,   713,  1024,   400,   266,   123,   316,   385,   414,
       8,  1372,   248,   319,  1506,   110,   320,   414,   231,   316,
     323,  1125,  1636,   400,  1634,   321,   431,  1635,   321,    30,
     321,   148,   321,   321,   431,  1126,   320,   385,   129,   385,
      81,   207,   208,   321,   320,   211,  1127,   323,   319,    86,
     110,    52,   400,    51,   400,   323,   321,   385,   316,   139,
     321,   318,    63,    30,   401,   320,   323,   404,   323,  1090,
     407,   750,   400,   321,   411,   155,   385,   141,  1476,   416,
     237,  1083,   239,   316,    42,    52,   303,   231,   385,    81,
     107,   400,    54,   304,   305,   306,    63,   254,  1512,  1380,
     358,   161,   162,   400,   121,    81,   301,   302,   321,   128,
     368,   369,   237,   237,   239,   239,   313,  1398,    36,    37,
      38,  1123,  1124,   130,   446,  1579,  1581,   385,     8,   121,
    1580,   801,     1,  1582,   137,     4,   231,     6,   100,     4,
     231,     6,   400,     8,   481,   121,  1233,   150,   237,  1236,
     239,  1236,   385,   145,   161,   162,    30,    26,    27,    28,
      29,   320,   165,   446,   228,   229,  1468,   400,    54,   145,
     139,    51,   285,   286,   287,   144,   855,   321,    52,  1632,
     724,   160,     1,   190,   196,   321,   165,   879,  1275,    63,
    1275,   855,    11,    12,    13,    14,    15,    16,    17,   148,
     237,    20,   239,   204,   750,    42,    43,   854,   209,   158,
     159,   922,   923,   924,   100,   196,    85,    86,    87,    88,
     899,    90,     8,   285,    93,   936,   321,   296,   110,     4,
     321,     6,  1082,   295,    79,   899,   247,   204,    24,  1089,
     297,   110,   209,   300,   285,   286,   287,   311,   130,    74,
      95,     7,    71,   130,   305,    74,    75,    76,    77,    78,
      79,   143,    37,   181,    20,    51,    22,    86,   113,    88,
      89,    90,    91,    92,    93,    94,    95,   280,    97,    98,
      99,   100,   107,   102,   161,   162,   105,   164,   107,   158,
      99,   110,   111,  1574,   113,    42,   121,   116,  1415,  1416,
    1417,  1418,   848,   849,   850,   851,   852,    99,   110,   855,
      57,    58,   103,   104,   105,   316,   135,   136,   137,   138,
     245,   123,   141,   246,   143,   250,   251,   246,   130,     1,
     204,   853,     4,   879,     6,   209,   108,   109,   110,     1,
     165,   266,     4,   246,     6,   750,   148,   724,     4,   316,
       6,     7,   154,   899,    26,    27,    28,    29,     4,   106,
       6,   264,   265,   710,    26,    27,    28,    29,   115,     5,
      99,  1652,     8,   750,   121,   257,     1,  1024,   724,     4,
       1,     6,   158,     4,   385,     6,  1637,  1629,    22,   214,
      81,    25,  1639,   121,  1640,  1638,   724,  1003,   145,   400,
     279,    26,    27,    28,    29,    26,    27,    28,    29,  1526,
    1527,  1528,    20,   141,    22,   724,     4,   145,   385,     1,
      59,    60,     4,    93,     6,    64,    42,   724,    90,  1516,
    1122,  1516,  1102,   400,   161,   162,  1128,   110,  1130,  1131,
      12,   303,   316,  1090,    26,    27,    28,    29,    17,    20,
     855,    22,   321,   126,    36,    18,   126,   854,   131,   132,
      85,    86,    87,    88,   322,    90,   724,   129,    93,   317,
     318,   848,   849,   850,   851,   852,   853,   320,   855,    49,
     256,   257,   258,   259,   260,   110,  1030,   247,   248,   110,
      49,   724,   750,   110,   899,   112,   113,   114,    36,    71,
     228,   229,   879,    75,   841,   320,   100,   853,   845,    15,
      16,   385,   182,   183,   184,   185,   186,   187,    90,    91,
     158,   320,   899,   196,   320,   853,   400,   320,     0,    54,
     124,   125,     4,   158,     6,   107,  1082,  1083,  1084,  1085,
    1086,  1233,  1088,  1089,   853,   304,   305,   306,  1094,  1095,
      42,   902,   264,   265,   905,  1217,   853,  1236,    42,   197,
     198,   199,    42,  1107,   136,  1109,    82,    83,    84,   231,
      86,   143,   289,   290,   291,   247,  1122,  1123,  1124,  1125,
    1126,  1127,  1128,   311,  1130,  1131,   123,  1640,  1641,     7,
     848,   849,   850,   851,   852,   853,  1275,   855,  1268,     8,
    1270,   100,   139,     1,   264,   265,     4,   326,     6,   296,
     231,   148,  1274,   207,   100,   101,   102,   154,   155,   438,
     853,   879,  1298,  1299,  1300,  1301,   445,  1024,    26,    27,
      28,    29,   326,   227,   228,   296,   455,    99,   457,   314,
     459,   899,   461,   108,   109,    15,    16,   466,   325,   321,
     469,   245,   471,  1030,   247,    42,   121,    15,    16,   321,
     479,   262,    42,    23,   129,   108,   109,   261,    81,  1407,
      57,    58,   266,  1410,   268,  1405,  1408,    57,    58,    23,
     145,   285,   286,   287,  1030,  1090,    49,  1233,    86,   100,
    1236,   108,   109,  1090,    49,    93,   321,    49,  1431,    49,
     321,    49,  1030,     4,     5,  1082,  1083,  1084,  1085,  1086,
      99,  1088,  1089,   124,   125,   290,   291,  1094,  1095,   106,
    1453,  1030,    81,   724,   108,   109,   106,    99,   115,  1275,
    1107,   129,  1109,  1030,   121,   115,  1412,  1413,  1414,   321,
      42,   121,    99,  1139,    17,  1122,  1123,  1124,  1125,  1126,
    1127,  1128,    99,  1130,  1131,    57,    58,   724,   145,    91,
      92,  1107,  1139,  1109,   162,   145,   231,   232,   233,   234,
      40,    41,  1030,   273,   274,   275,   276,   277,    99,  1107,
      99,  1109,   247,   248,   249,    18,  1137,  1138,   322,  1140,
    1141,  1142,     5,  1139,  1094,  1095,   207,  1030,  1107,  1138,
    1109,  1140,  1141,  1142,   106,   112,   133,   134,   135,   136,
    1107,  1139,  1109,   115,   191,     7,   227,   228,     7,   121,
     127,  1217,    81,   200,   201,  1083,  1370,   204,   205,     7,
    1139,  1236,     7,   231,  1496,    99,    99,  1516,     5,     7,
    1217,   148,  1139,   145,   358,     7,   320,   154,  1392,  1107,
     724,  1109,   853,     7,   368,   369,  1233,     1,    17,  1236,
       4,    18,     6,   322,  1122,  1123,  1124,  1125,  1126,  1127,
    1128,  1217,  1130,  1131,  1107,     8,  1109,    99,  1274,   110,
     320,  1139,    26,    27,    28,    29,   853,   320,   320,  1217,
     121,   320,   123,   320,    99,   202,   203,  1274,  1275,     1,
      99,    99,     4,    99,     6,    99,  1139,   297,  1217,  1306,
     141,    99,    99,    99,   145,    99,    99,   148,    99,   320,
    1217,   320,    99,   321,    26,    27,    28,    29,  1274,    42,
      99,    44,    42,     5,   320,    99,    49,    39,    51,    41,
       8,    99,    55,    49,  1340,    40,  1274,    57,    58,    97,
      98,    99,   100,    99,  1305,  1292,  1293,  1294,  1295,  1217,
    1311,  1312,  1313,  1340,   195,  1274,    67,   110,  1512,   110,
    1516,   144,   110,    99,  1325,  1233,     5,  1274,  1236,   853,
     325,    94,  1333,    96,  1217,    99,   320,   320,  1339,   320,
    1341,  1342,  1343,  1370,  1340,     7,   106,   228,   229,   327,
    1339,   327,  1341,  1342,  1343,   115,  1357,  1358,  1359,    99,
     248,   121,  1340,    99,     5,  1392,  1274,  1275,  1357,  1358,
    1359,   100,   320,   267,  1370,    40,  1431,     1,     7,  1030,
       4,  1340,     6,   100,  1431,   145,   100,   110,   100,   112,
       5,  1274,  1370,  1340,     1,    99,  1392,     4,  1453,     6,
      37,   100,    26,    27,    28,    29,  1453,   130,   100,   319,
      99,  1370,   319,  1030,  1392,   138,   139,   140,   141,    26,
      27,    28,    29,  1370,   100,    99,   108,   109,  1429,  1430,
     311,    99,  1340,  1392,   116,   117,   118,   119,   120,   319,
      99,   263,  1443,   321,    99,  1392,   183,   321,  1449,     5,
    1496,  1452,    99,   181,  1455,    39,  1107,  1340,  1109,   146,
     320,   319,  1370,  1464,  1465,  1466,    90,    99,   262,  1496,
     101,    99,   941,   942,   943,  1464,  1465,  1466,    85,    86,
      87,    88,   263,    90,  1392,  1512,    93,  1370,  1139,  1516,
    1107,    99,  1109,    38,   100,   321,   320,   100,  1545,  1471,
    1496,   321,   129,   110,   320,   129,  1030,   320,  1480,  1392,
     320,    99,    99,   247,  1486,   320,  1512,   320,  1496,  1520,
     320,   320,  1139,    57,    58,   320,    43,   321,    45,   321,
      47,    48,   100,   320,  1512,   320,   320,  1496,    55,    56,
     320,   319,    99,     5,    99,  1546,    99,  1548,   110,  1496,
     112,   158,    20,  1512,  1144,  1556,  1557,  1558,  1559,  1560,
    1561,  1562,  1688,  1564,  1329,  1512,  1217,  1652,   130,   321,
    1539,    88,   106,  1643,  1537,    89,   138,   139,  1294,   141,
      91,   115,   384,  1107,  1630,  1109,   750,   121,  1496,   151,
     152,   315,  1593,  1594,  1595,  1596,  1597,   387,  1273,  1398,
    1217,   758,  1384,  1630,  1512,   766,   303,   231,  1516,  1362,
    1012,   145,  1493,  1496,  1565,  1139,    75,    76,    77,    78,
      79,    80,  1492,  1274,   822,   386,  1628,  1084,  1629,  1512,
    1631,  1632,  1633,  1577,  1630,  1085,  1637,  1638,  1639,  1640,
    1629,  1086,  1631,  1632,  1633,  1100,   837,  1105,  1637,  1638,
    1639,  1640,  1630,  1088,   846,    30,  1657,  1274,   955,  1660,
     286,   204,  1056,  1664,  1665,  1666,  1667,  1668,  1669,  1670,
    1671,  1630,   398,   369,  1675,   396,   119,  1695,  1679,  1668,
    1669,  1670,  1683,  1630,   848,   849,   850,   851,   852,  1340,
     399,   855,   397,  1217,   358,  1696,   294,   321,   298,    15,
      16,   618,  1703,  1704,  1705,   299,   299,   721,    -1,   723,
      -1,    -1,    -1,    -1,   321,   879,    -1,    -1,    -1,  1370,
      -1,    -1,  1630,  1340,    -1,   739,   740,    -1,   742,    -1,
      -1,    -1,   746,   747,    -1,   899,    -1,    -1,    -1,    -1,
       1,  1392,    -1,     4,    -1,     6,    -1,  1630,    -1,    -1,
    1274,    -1,    -1,  1370,    -1,    -1,   770,    -1,    -1,   773,
      76,    77,    78,    -1,    -1,    26,    27,    28,    29,    39,
      40,    41,    42,    -1,    35,  1392,    92,    93,    94,    -1,
      -1,    -1,     1,    44,    -1,     4,   102,     6,    49,    -1,
      51,    -1,    53,    -1,   110,   111,    -1,    -1,    -1,    -1,
     116,    -1,    -1,    73,    -1,    -1,    -1,    26,    27,    28,
      29,    81,    82,    83,    84,    -1,  1340,   831,    88,    -1,
     834,   137,   138,    -1,    -1,   141,    -1,    97,    98,    99,
     100,    -1,    -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1496,  1370,    -1,    -1,    -1,
     120,    -1,    -1,    -1,    -1,   125,   126,   127,    -1,    -1,
     130,  1512,    -1,   133,    -1,    -1,     1,    86,  1392,     4,
      -1,     6,    -1,    42,    93,    -1,    -1,    -1,    -1,  1496,
      -1,    -1,    -1,    -1,    -1,    -1,   900,   901,    57,    58,
      -1,    26,    27,    28,    29,  1512,    -1,   158,    -1,    -1,
      35,    -1,     1,    -1,    -1,     4,    -1,     6,    -1,    44,
     129,    -1,    -1,    -1,    49,    -1,    51,   130,    53,  1083,
      -1,    -1,    -1,    -1,    35,    -1,   139,    26,    27,    28,
      29,    42,    -1,    44,    -1,    46,    -1,   106,    49,    50,
      51,   154,    53,   162,    -1,   158,   115,    -1,   161,   162,
      -1,    -1,   121,   166,   167,   168,   169,   170,  1122,  1123,
    1124,  1125,  1126,  1127,  1128,    42,  1130,  1131,    -1,   230,
      -1,    -1,  1496,    -1,    -1,    -1,   145,    -1,    -1,  1630,
      57,    58,    -1,    -1,   245,    -1,    -1,    86,  1512,    88,
      -1,    90,    -1,    -1,    93,    -1,    -1,   267,   268,   269,
     261,    -1,    -1,    -1,  1018,   266,    -1,   268,  1022,    -1,
      -1,   110,   231,  1630,    -1,    -1,    -1,  1031,  1032,  1033,
      -1,    -1,  1036,   158,  1038,    42,    -1,    -1,     1,   106,
      -1,     4,    -1,     6,  1048,    -1,    -1,    -1,   115,    -1,
      57,    58,    -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    29,    -1,    -1,   158,
     321,    -1,    -1,    -1,    -1,    -1,  1080,    -1,   145,  1233,
      -1,    -1,  1236,    -1,    -1,    -1,    -1,  1091,    -1,  1093,
      -1,    -1,    -1,    -1,    -1,  1099,    -1,  1101,    -1,   106,
      -1,    -1,    -1,    -1,    -1,   230,    -1,    -1,   115,    -1,
      -1,    -1,   321,    -1,   121,    -1,  1630,    -1,    -1,    -1,
     245,  1275,    -1,    86,    -1,    88,    -1,    90,    -1,   230,
      93,    -1,    -1,   393,   394,   395,   261,    -1,   145,   445,
      -1,   266,    81,   268,   245,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,     4,    -1,     6,    -1,
     261,    -1,   422,    -1,    -1,   266,    -1,   268,    -1,   108,
     109,    -1,    -1,   479,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    -1,   122,    -1,   124,   125,   126,    -1,     1,
      -1,    -1,     4,   453,     6,   158,   321,    -1,    -1,    -1,
    1204,  1205,    -1,    -1,    -1,    -1,    -1,    -1,   147,   148,
     149,    23,    -1,    -1,    26,    27,    28,    29,    30,    31,
    1224,    33,    34,    35,    -1,    -1,  1230,    -1,    81,    -1,
      -1,    -1,   321,    -1,    -1,    -1,    -1,    49,    86,    -1,
      88,    -1,    90,    -1,  1248,    93,    -1,    59,    60,    -1,
      -1,    -1,    64,    -1,    -1,   108,   109,    -1,    -1,   112,
      -1,    -1,   110,    75,    76,    77,    78,    79,    80,   122,
     123,   124,   125,   126,   127,   128,   129,   130,    90,    -1,
      -1,    -1,    94,    -1,    96,    -1,    -1,    99,   100,   101,
     102,    -1,    -1,   105,    -1,   107,    -1,    35,   110,   111,
      -1,    -1,    -1,   115,    42,    -1,    44,    -1,    -1,   121,
     158,    49,    50,    51,    -1,    53,    -1,   170,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,
     142,    -1,    -1,   145,    -1,    -1,    -1,    -1,   150,    -1,
      -1,   153,    -1,    -1,   156,   157,    -1,    -1,   160,    -1,
      -1,   163,    -1,   165,    -1,    -1,    -1,    -1,   321,    -1,
     168,  1365,  1516,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,    -1,  1379,   188,   189,    -1,   191,
     192,   193,   194,    -1,    -1,  1389,    -1,    -1,   200,   201,
      -1,    -1,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,    -1,    -1,   230,    -1,
     108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   245,   122,    -1,   124,   125,   126,    -1,
      -1,    -1,    -1,   255,    -1,    -1,    -1,    -1,    -1,   261,
      -1,    -1,    -1,    -1,   266,    -1,    -1,    -1,    -1,   147,
     148,   149,    -1,   275,   276,    -1,   278,    -1,    -1,   281,
     282,   283,   284,   321,    -1,    -1,   288,    -1,    -1,    -1,
     292,   293,   294,    -1,    -1,    -1,   298,   299,     1,    -1,
      -1,     4,   230,     6,    -1,   307,    -1,    -1,   310,   311,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   245,   320,   321,
      23,   323,   324,    26,    27,    28,    29,    30,    31,    -1,
      33,    34,    35,   261,    -1,    -1,    -1,    -1,   266,    -1,
     268,    -1,    -1,    -1,    -1,    -1,    49,    -1,   108,   109,
      -1,    -1,   112,    -1,    -1,    -1,    59,    60,    -1,    -1,
      -1,    64,   122,   123,   124,   125,   126,   127,   128,   129,
     130,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,
      -1,    94,    -1,    96,    -1,    -1,    99,   100,   101,   102,
      -1,    -1,   105,    -1,   107,    -1,    -1,   110,   111,    -1,
     170,    -1,   115,    -1,    -1,    -1,    -1,    -1,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,   142,
      -1,    -1,   145,    -1,    -1,    -1,    -1,   150,    -1,    -1,
     153,    -1,    -1,   156,   157,    -1,    -1,   160,    35,    -1,
     163,    -1,   165,    -1,    -1,    42,    -1,    44,    -1,    46,
      -1,    -1,    49,    50,    51,    -1,    53,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,   188,   189,    -1,   191,   192,
     193,   194,    -1,    -1,    -1,    -1,    -1,   200,   201,    -1,
      -1,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,    -1,    -1,   230,    -1,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,    -1,
      -1,    -1,   245,    -1,   121,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   255,    -1,    -1,    -1,    -1,    -1,   261,    -1,
      -1,    -1,    -1,   266,    -1,    -1,    -1,    -1,   145,    -1,
      -1,    -1,   275,   276,    -1,   278,    -1,    -1,   281,   282,
     283,   284,    -1,    -1,    -1,   288,    -1,    -1,    -1,   292,
     293,   294,    -1,    -1,    -1,   298,   299,     1,    -1,    -1,
       4,    -1,     6,    -1,   307,    -1,    -1,   310,   311,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   320,   321,    23,
     323,   324,    26,    27,    28,    29,    30,    31,    -1,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   230,    -1,    59,    60,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   245,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   261,    -1,    90,    -1,    -1,   266,
      94,   268,    96,    -1,    -1,    99,   100,   101,   102,    -1,
      -1,   105,    -1,   107,    -1,    -1,   110,   111,    -1,    -1,
      -1,   115,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,   142,    -1,
      -1,   145,    -1,    -1,    -1,    -1,   150,    -1,    -1,   153,
      -1,    -1,   156,   157,    -1,    -1,   160,    -1,    -1,   163,
      -1,   165,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   188,   189,    -1,   191,   192,   193,
     194,    -1,    -1,    -1,    -1,    -1,   200,   201,    -1,    -1,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,    -1,    -1,   230,    -1,    -1,     5,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   245,    -1,    -1,    -1,    21,    -1,    23,    -1,    -1,
      -1,   255,    -1,    -1,    -1,    31,    -1,   261,    34,    -1,
      -1,    -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   275,   276,    -1,   278,    -1,    -1,   281,   282,   283,
     284,    -1,    -1,    -1,   288,    -1,    -1,    -1,   292,   293,
     294,    67,    -1,    -1,   298,   299,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   307,    -1,    81,   310,   311,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   320,   321,    -1,   323,
     324,    -1,    -1,    99,   100,   101,   102,    -1,    -1,   105,
      -1,   107,    -1,    -1,    -1,   111,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,   125,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   137,    -1,    -1,    -1,    -1,   142,    -1,    -1,   145,
      -1,    -1,    -1,    -1,   150,    -1,    -1,   153,    -1,    -1,
     156,   157,    -1,    -1,   160,    -1,    -1,   163,    -1,   165,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   188,   189,    -1,   191,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,    -1,    -1,   230,     5,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   240,    -1,    -1,   243,   244,    -1,
      -1,    21,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   275,
     276,    -1,    -1,    -1,    -1,   281,   282,    -1,    -1,    -1,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    67,   294,    -1,
      -1,    -1,   298,   299,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   308,   309,    -1,   311,   126,    -1,    -1,   129,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   323,    -1,    99,
     100,   101,   102,    -1,    -1,   105,   146,   107,    -1,    -1,
      -1,   111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,
      -1,   121,    -1,    -1,    -1,   125,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,    -1,    -1,
      -1,    -1,   142,    -1,    -1,   145,    -1,    -1,    -1,    -1,
     150,    -1,    -1,   153,    -1,    -1,   156,   157,    -1,    -1,
     160,    -1,    -1,   163,    -1,   165,    -1,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   188,   189,
      -1,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   268,    -1,
     230,     5,    -1,    -1,    -1,   275,   276,    -1,    -1,    -1,
     240,    -1,    -1,   243,   244,   285,    -1,    21,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   311,    -1,    -1,    -1,   275,   276,    -1,    -1,    -1,
      -1,   281,   282,    -1,    -1,    -1,   100,    -1,    -1,    -1,
      -1,    -1,    -1,    67,   294,    -1,    -1,    -1,   298,   299,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   308,   309,
      -1,   311,   126,    -1,    -1,   129,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   323,    -1,    99,   100,   101,   102,    -1,
      -1,   105,   146,   107,    -1,    -1,    -1,   111,    -1,    -1,
      -1,   115,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,
      -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,   142,    -1,
      -1,   145,    -1,    -1,    -1,    -1,   150,    -1,    -1,   153,
      -1,    -1,   156,   157,    -1,    -1,   160,    -1,    -1,   163,
      -1,   165,    -1,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   188,   189,    -1,   191,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   268,    -1,   230,     5,    -1,    -1,
      -1,   275,   276,    -1,    -1,    -1,   240,    -1,    -1,   243,
     244,   285,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   311,    -1,    -1,
      -1,   275,   276,    -1,    -1,    -1,    -1,   281,   282,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
     294,    -1,    -1,    -1,   298,   299,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   308,   309,    -1,   311,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   323,
      -1,    99,   100,   101,   102,    -1,    -1,   105,    -1,   107,
      -1,    -1,    -1,   111,    -1,    -1,    -1,   115,    -1,    -1,
      -1,    -1,    -1,   121,    -1,    -1,    -1,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,
      -1,    -1,    -1,    -1,   142,    -1,    -1,   145,    -1,    -1,
      -1,    -1,   150,    -1,    -1,   153,    -1,    -1,   156,   157,
      -1,    -1,   160,    -1,    -1,   163,    -1,   165,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     188,   189,    -1,   191,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
      -1,    -1,   230,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   240,    -1,    -1,   243,   244,    -1,    -1,    21,
      86,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,    -1,    -1,    -1,   275,   276,    -1,
      -1,    -1,    -1,   281,   282,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,    -1,    67,   294,    -1,    -1,    -1,
     298,   299,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     308,   309,    -1,   311,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   323,    -1,    99,   100,   101,
     102,    -1,    -1,   105,    -1,   107,    -1,    -1,    -1,   111,
      -1,    -1,    -1,   115,    -1,    -1,    -1,   183,    -1,   121,
      -1,    -1,    -1,   125,    -1,    -1,    -1,    -1,   108,   109,
      -1,    -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,
     142,   207,    -1,   145,    -1,    -1,    -1,    -1,   150,   129,
      -1,   153,    -1,    -1,   156,   157,    -1,    -1,   160,    -1,
      -1,   163,    -1,   165,    -1,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,    -1,
      -1,   247,   248,   249,    -1,    -1,   188,   189,    -1,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   268,    -1,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,    -1,   207,   230,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,   240,    -1,
      -1,   243,   244,    -1,    21,    -1,    23,    -1,    -1,    -1,
      -1,   231,   232,   233,   234,   235,   236,    -1,   238,   239,
     240,   241,   242,   243,   244,    -1,    -1,   247,   248,   249,
      -1,    -1,    -1,   275,   276,    -1,    -1,    -1,    -1,   281,
     282,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   268,    -1,
      67,    -1,   294,    -1,    -1,    -1,   298,   299,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   308,   309,    -1,   311,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    -1,    -1,
      -1,   323,    99,   100,   101,   102,    -1,    -1,    -1,    -1,
     107,    -1,    -1,    -1,   111,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,   125,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     137,    67,    -1,    -1,    -1,   142,    -1,    -1,   145,    -1,
      -1,    -1,    -1,   150,    -1,    -1,   153,    -1,    -1,   156,
     157,    -1,    -1,   160,    -1,    -1,   163,    -1,   165,    -1,
      -1,    -1,    -1,    99,   100,   101,   102,    -1,    -1,    -1,
      -1,   107,    -1,    -1,    -1,   111,    -1,    -1,    -1,   115,
      -1,   188,   189,    -1,    -1,   121,    -1,    -1,    -1,   125,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   137,    -1,    -1,    -1,    -1,   142,    -1,    -1,   145,
      -1,    -1,    -1,    -1,   150,    -1,    -1,   153,    -1,    -1,
     156,   157,    -1,    -1,   160,    -1,    -1,   163,    -1,   165,
      -1,    -1,    -1,   240,    -1,    -1,   243,   244,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,
      -1,    -1,   188,   189,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   308,   309,    -1,   240,    -1,    -1,   243,   244,    -1,
      -1,    -1,    -1,   320,    -1,    -1,   323,   324,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    99,   100,   101,   102,    -1,
      -1,    -1,    -1,   107,    -1,    -1,    -1,   111,    -1,    -1,
      -1,   115,    -1,    -1,    -1,   281,   282,   121,   284,    -1,
      -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   137,    67,    -1,    -1,    -1,   142,    -1,
      -1,   145,   308,   309,    -1,    -1,   150,    -1,    -1,   153,
      -1,    -1,   156,   157,   320,    -1,   160,   323,   324,   163,
      -1,   165,    -1,    -1,    -1,    -1,    99,   100,   101,   102,
      -1,    -1,    -1,    -1,   107,    -1,    -1,    -1,   111,    -1,
      -1,    -1,   115,    -1,   188,   189,    -1,    -1,   121,    -1,
      -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,   142,
      -1,    -1,   145,    -1,    -1,    -1,    -1,   150,    -1,    -1,
     153,    -1,    -1,   156,   157,    -1,    -1,   160,    -1,    -1,
     163,    -1,   165,    -1,    -1,    -1,   240,    -1,    -1,   243,
     244,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    -1,    -1,   188,   189,    -1,    -1,    -1,
      31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   281,   282,    -1,
     284,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   308,   309,    -1,   240,    -1,    -1,
     243,   244,    -1,    -1,    -1,    -1,   320,    -1,    -1,   323,
     324,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,
     101,   102,    -1,    -1,   105,    -1,   107,    -1,    -1,    -1,
     111,    -1,    -1,    -1,   115,    -1,    -1,    -1,   281,   282,
     121,   284,    -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,
      -1,   142,    -1,    -1,   145,   308,   309,    -1,    -1,   150,
      -1,    -1,   153,    -1,    -1,   156,   157,    -1,    -1,   160,
     323,   324,   163,    -1,   165,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   188,   189,    -1,
     191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,    -1,    -1,   230,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   240,
      -1,    -1,   243,   244,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,   275,   276,    -1,    -1,    -1,    -1,
     281,   282,    -1,    59,    60,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,   294,    -1,    -1,    -1,   298,   299,    75,
      76,    77,    78,    79,    80,    -1,    -1,   308,   309,    -1,
     311,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,
      96,    -1,   323,    99,   100,   101,   102,    -1,    -1,   105,
      -1,   107,    -1,    -1,    -1,   111,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   137,    -1,    -1,    -1,    -1,   142,    -1,    -1,   145,
      -1,    -1,    -1,    -1,   150,    -1,    -1,   153,    -1,    -1,
     156,   157,    -1,    -1,   160,    -1,    -1,   163,    -1,   165,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   188,   189,    -1,   191,   192,   193,   194,    -1,
      -1,    -1,    -1,    -1,   200,   201,    -1,    -1,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,    -1,    -1,   230,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   245,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,   255,
      30,    31,    -1,    -1,    34,   261,    -1,    -1,    -1,    -1,
     266,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   275,
     276,    -1,   278,    -1,    -1,   281,   282,   283,   284,    -1,
      -1,    -1,   288,    -1,    -1,    -1,   292,   293,   294,    -1,
      -1,    -1,   298,   299,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   307,    -1,    -1,   310,   311,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,   320,    -1,    -1,   323,   324,    99,
     100,   101,   102,    -1,    -1,   105,    -1,   107,    -1,    -1,
      -1,   111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,
      -1,   121,    -1,   100,   101,   102,    -1,    -1,    -1,    -1,
     107,    -1,    -1,    -1,   111,    -1,    -1,   137,   115,    -1,
      -1,    -1,   142,    -1,   121,   145,    -1,    -1,   125,    -1,
     150,    -1,    -1,   153,    -1,    -1,   156,   157,    -1,    -1,
     160,    -1,    -1,   163,    -1,   165,    -1,    -1,   145,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   188,   189,
      -1,   191,   192,   193,   194,    -1,    -1,    -1,    -1,    -1,
     200,   201,    -1,    -1,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,    -1,    -1,
     230,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   240,    -1,    -1,   243,   244,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   275,   276,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   294,    -1,    -1,    -1,   298,   299,
      -1,    -1,    -1,    -1,   281,   282,    -1,    -1,    -1,    -1,
     310,   311,    -1,    99,   100,   101,   102,    -1,    -1,   105,
     320,   107,    -1,   323,   324,   111,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   323,    -1,    -1,    -1,
      -1,   137,    -1,    -1,    -1,    -1,   142,    -1,    -1,   145,
      -1,    -1,    -1,    -1,   150,    -1,    -1,   153,    -1,    -1,
     156,   157,    -1,    -1,   160,    -1,    -1,   163,    -1,   165,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   188,   189,    -1,   191,   192,   193,   194,    -1,
      -1,    -1,    -1,    -1,   200,   201,    -1,    -1,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,    -1,    -1,   230,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   275,
     276,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   294,    -1,
      -1,    -1,   298,   299,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,   311,    -1,    99,   100,   101,
     102,    -1,    -1,   105,    -1,   107,    -1,   323,   324,   111,
      -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,    -1,   121,
      -1,    -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,
     142,    -1,    -1,   145,    -1,    -1,    -1,    -1,   150,    -1,
      -1,   153,    -1,    -1,   156,   157,    -1,    -1,   160,    -1,
      -1,   163,    -1,   165,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   188,   189,    -1,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,    -1,    -1,   230,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   240,    -1,
      -1,   243,   244,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   275,   276,    -1,    -1,    -1,    -1,   281,
     282,    -1,    -1,    -1,     0,     1,    -1,    -1,     4,    -1,
       6,    -1,   294,    -1,    -1,    -1,   298,   299,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   308,   309,    -1,   311,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,    35,
      -1,   323,    -1,    -1,    -1,    -1,    42,    -1,    44,    -1,
      46,    -1,    -1,    49,    50,    51,    -1,    53,    -1,    -1,
      -1,    57,    58,    59,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    99,   100,   101,   102,    -1,    -1,    -1,   115,
     107,    -1,    -1,    -1,   111,   121,    -1,    -1,   115,    -1,
      -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,   125,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,
     137,    -1,    67,    -1,    -1,   142,    -1,    -1,   145,    -1,
      -1,    -1,    -1,   150,    -1,    -1,   153,    -1,    -1,   156,
     157,    -1,    -1,   160,    -1,    -1,   163,    -1,   165,    -1,
      -1,    -1,    -1,    -1,    99,   100,   101,   102,    -1,    -1,
      -1,    -1,   107,    -1,    -1,    -1,   111,    -1,    -1,    -1,
     115,   188,   189,    -1,    -1,    -1,   121,    -1,    -1,    -1,
     125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   137,    -1,    -1,    -1,    -1,   142,    -1,    -1,
     145,    -1,    -1,    -1,   230,   150,    -1,    -1,   153,    -1,
      -1,   156,   157,    -1,    -1,   160,    -1,    -1,   163,   245,
     165,    -1,    -1,   240,    -1,    -1,   243,   244,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   261,    -1,    -1,    -1,    -1,
     266,    35,   268,   188,   189,    -1,    -1,    -1,    42,    43,
      44,    45,    -1,    -1,    48,    49,    -1,    51,    52,    53,
      -1,    55,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   308,   309,    -1,    -1,   240,    -1,    -1,   243,   244,
      94,    -1,    96,    97,    98,    -1,   323,   324,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   281,   282,    -1,   284,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   308,   309,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   323,   324,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   230,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   245,    -1,    -1,    -1,    -1,   250,   251,   252,   253,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   261,    -1,    -1,
      -1,    -1,   266,    -1,   268,   269
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   329,     0,     1,     4,     6,    26,    27,    28,    29,
      35,    42,    44,    46,    49,    50,    51,    53,    57,    58,
      59,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,   106,   115,   121,   145,   230,   245,
     261,   266,   268,   330,   332,   333,   334,   335,   396,   397,
     398,   400,   415,   330,   101,   100,   393,   393,   393,   398,
     409,   398,   400,   415,   398,   403,   403,   403,   398,   406,
     335,    46,   336,    35,    42,    44,    49,    50,    51,    53,
     230,   245,   261,   266,   268,   337,    46,   338,    35,    42,
      44,    46,    49,    50,    51,    53,   230,   245,   261,   266,
     268,   339,    50,   340,    35,    42,    43,    44,    45,    48,
      49,    51,    52,    53,    55,    94,    96,    97,    98,   230,
     245,   250,   251,   252,   253,   261,   266,   268,   269,   341,
     245,   250,   251,   266,   342,    42,    44,    49,    51,    55,
      94,    96,   343,    44,   344,    23,    30,    31,    34,    99,
     100,   101,   102,   105,   107,   111,   115,   121,   137,   142,
     145,   150,   153,   156,   157,   160,   163,   165,   188,   189,
     191,   192,   193,   194,   200,   201,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     230,   275,   276,   294,   298,   299,   310,   311,   323,   324,
     352,   394,   507,   508,   511,   512,   513,   517,   574,   577,
     579,   583,   588,   589,   591,   593,   603,   604,   606,   608,
     610,   612,   616,   618,   620,   622,   624,   626,   628,   630,
     632,   634,   638,   640,   642,   644,   645,   647,   649,   651,
     653,   655,   657,   659,   661,    55,   304,   305,   306,   345,
     351,    55,   346,   351,   100,   347,   348,    86,   237,   239,
     409,   409,   409,   409,     0,   330,   393,   393,    54,   301,
     302,   412,   413,   414,    33,    35,    49,    59,    60,    64,
      75,    76,    77,    78,    79,    80,    94,    96,   206,   230,
     245,   255,   261,   266,   278,   281,   282,   283,   284,   288,
     292,   293,   307,   320,   419,   420,   421,   422,   423,   424,
     425,   429,   430,   431,   434,   435,   442,   446,   451,   452,
     454,   455,   456,   457,   458,   480,   481,   483,   484,   486,
     487,   490,   491,   498,   499,   500,   501,   502,   505,   506,
     512,   519,   520,   521,   522,   523,   524,   528,   529,   530,
     558,   572,   577,   578,   601,   602,   603,   330,   319,   319,
     330,   393,   462,   353,   356,   419,   393,   358,   360,   507,
     530,   363,   393,   367,   400,   416,   409,   398,   400,   403,
     403,   403,   406,    86,   237,   239,   409,   409,   409,   409,
     415,   398,   409,   410,   396,   398,   399,   398,   400,   401,
     416,   398,   403,   404,   403,   403,   398,   406,   407,    86,
     237,   239,   548,   409,   410,   409,   410,   409,   410,   409,
     410,   403,   409,   398,   397,   418,   400,   418,    42,   418,
     403,   403,   418,   406,   418,    42,    43,   403,   418,   418,
      86,   237,   254,   548,   409,    42,   418,    42,   418,    42,
     418,    42,   418,   409,   409,   409,    42,   418,   409,    42,
     418,    42,   418,   409,   398,   400,   403,   403,   418,    42,
     403,   400,   103,   104,   105,   605,   108,   109,   207,   208,
     211,   515,   516,    32,   207,   580,   128,   518,   161,   162,
     643,   108,   109,   110,   607,   110,   112,   113,   114,   609,
     108,   109,   116,   117,   118,   119,   120,   611,   108,   109,
     112,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     170,   613,   110,   112,   130,   138,   139,   140,   141,   617,
     110,   130,   143,   257,   619,   108,   109,   122,   124,   125,
     126,   147,   148,   149,   621,   110,   112,   130,   138,   139,
     141,   151,   152,   623,   123,   139,   148,   154,   155,   625,
     139,   155,   627,   148,   158,   159,   629,   126,   130,   161,
     162,   631,   130,   161,   162,   164,   633,   130,   139,   154,
     158,   161,   162,   166,   167,   168,   169,   170,   635,   110,
     161,   162,   639,   130,   161,   162,   190,   641,   110,   121,
     123,   141,   145,   148,   195,   228,   229,   311,   590,   592,
     648,   196,   650,   196,   652,   158,   197,   198,   199,   654,
     123,   148,   646,   112,   127,   148,   154,   202,   203,   656,
     123,   148,   658,   110,   123,   130,   148,   154,   660,   100,
     126,   129,   146,   268,   285,   311,   575,   576,   577,   108,
     109,   129,   207,   231,   232,   233,   234,   235,   236,   238,
     239,   240,   241,   242,   243,   244,   247,   248,   249,   268,
     594,   595,   598,   285,   295,   582,   524,   529,   296,   191,
     200,   201,   204,   205,   662,   317,   318,   585,   393,   523,
     351,   305,   351,    43,    45,    47,    48,    55,    56,    88,
     349,   409,   409,   409,   543,   557,   545,   547,    99,    99,
      99,    81,   590,   246,   499,   393,   507,   573,   573,    59,
      95,   393,   100,   575,    86,   183,   237,   594,   595,   246,
     246,   262,   246,   264,   265,   443,    81,    81,   590,     4,
     331,   531,   532,   303,   417,   423,   247,   248,   432,   433,
     158,   256,   257,   258,   259,   260,   436,   437,   279,   453,
       5,    21,    67,    81,   107,   111,   115,   121,   125,   145,
     191,   240,   243,   244,   281,   282,   308,   309,   465,   466,
     467,   468,   469,   470,   471,   473,   474,   475,   476,   477,
     478,   479,   508,   511,   517,   567,   568,   569,   574,   579,
     583,   589,   590,   591,   593,   599,   600,   603,    36,    37,
      38,   181,   459,   460,    81,   285,   286,   287,   482,   488,
     489,    81,   485,   488,   289,   290,   291,   492,   493,   494,
     495,    23,   507,   509,   510,    42,   503,   504,    15,    16,
      17,    18,   322,     8,    24,    51,     9,    10,    11,    12,
      13,    14,   107,   111,   115,   121,   137,   142,   145,   150,
     153,   156,   157,   160,   163,   165,   188,   189,   284,   324,
     476,   508,   510,   511,   525,   526,   527,   530,   559,   560,
     561,   562,   563,   564,   565,   566,   568,   569,   570,   571,
      49,    49,   541,   559,   560,   541,    36,   461,   320,   320,
     320,   320,   320,   412,   419,   462,   353,   356,   358,   360,
     363,   367,   409,   409,   409,   543,   557,   545,   547,   419,
      54,    54,    54,    54,   360,    54,   409,   360,   398,   403,
     418,    42,    42,    42,   409,   398,   398,   398,   398,   398,
     398,   398,   403,   393,     7,     8,   110,   211,   212,   514,
     100,   122,   246,   107,   121,   107,   121,   133,   134,   135,
     136,   614,   168,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   636,   592,   326,   326,   108,   109,
     121,   129,   145,   231,   232,   233,   596,   597,   598,   296,
     296,    99,   314,   584,   325,   350,   351,   555,   555,   555,
     247,   542,   262,   556,   443,   544,   394,   546,     5,   121,
     145,   478,    81,   478,   496,   497,   524,    23,    23,    93,
     320,    49,    49,    49,    99,   264,    49,   598,    49,   478,
     478,   264,   265,   447,   478,    99,   478,   478,    81,   527,
     530,   535,   536,   539,   565,   566,     7,   321,   394,    99,
      99,   433,    74,   107,   121,   165,   214,   439,   394,    99,
      99,    99,   394,   438,   437,   137,   150,   165,   280,   478,
       5,   478,    15,    16,    17,    18,   322,    20,    22,     8,
      51,     5,   488,    81,     7,     7,    99,    99,   460,     5,
       7,     5,   478,   478,   493,     7,   393,   320,   393,   320,
     504,   570,   570,   561,   562,   563,   523,   320,   426,   509,
     560,   565,     7,    15,    16,    17,    18,   322,     7,    20,
      22,     8,   560,   478,   478,   330,   330,    99,   355,   357,
     359,   364,   368,   461,   320,   320,   320,   320,   320,   555,
     555,   555,   542,   556,   544,   546,    99,    99,    99,    99,
      99,   555,   398,   398,   398,    99,   516,   110,   126,   131,
     132,   196,   615,    93,   126,   182,   183,   184,   185,   186,
     187,   637,    99,    99,   108,   109,   108,   109,    99,    99,
     297,   581,    99,   155,   313,   586,   590,   320,   320,   320,
      99,   447,    99,   478,     5,     5,   478,   509,    86,    89,
     417,   537,   538,   394,   394,    99,   524,   533,   534,   478,
     478,   478,    99,   478,    49,   478,    99,   100,   248,   444,
      40,   478,   331,     5,   331,   537,   331,   532,   144,   139,
     144,   440,   441,   110,   110,    67,   110,   478,     5,   465,
     508,   569,   570,   466,   467,   468,    99,   470,   465,   472,
     509,   530,   478,   478,   508,   569,   599,   599,   478,   489,
     478,   488,   495,   496,   533,   331,   427,   428,   325,   565,
     570,   570,   561,   562,   563,   565,    99,   565,   565,    37,
     330,    35,    44,    49,    51,    53,   158,   230,   245,   261,
     266,   268,   321,   330,   332,   354,    90,   110,   321,   330,
     332,   384,   390,   419,    85,    86,    87,    88,    90,    93,
     110,   158,   321,   330,   332,   365,    86,    88,   110,   158,
     321,   330,   332,   365,    39,    41,   321,   330,   332,   355,
     357,   359,   364,   368,   320,   320,   320,     7,   327,   327,
     581,   300,   581,    99,   108,   109,   587,   378,   379,   377,
     248,    99,   444,   478,   478,     5,   100,   395,   395,   538,
     320,   423,   537,   478,    20,   100,   267,   445,   478,    40,
     540,   565,   566,   572,     7,   100,   100,   100,   478,     5,
     488,   488,     5,   230,   321,   422,   423,   535,     7,   321,
      99,    37,   393,   411,   393,   402,   393,   405,   405,   393,
     408,   100,    86,   237,   239,   411,   411,   411,   411,   330,
      75,    76,   391,   392,   507,   100,   330,   330,   330,   395,
     395,   319,    91,    92,   366,    99,   100,   124,   125,   207,
     227,   228,   372,   373,   383,    82,    83,    84,    86,   361,
     362,   330,   395,   319,   373,   361,   330,   100,   319,   321,
     321,   321,   321,   321,   378,   379,   377,    99,    99,    90,
     129,   231,   321,   330,   332,   553,    86,    93,   129,   162,
     231,   321,   330,   332,   554,   110,   231,   321,   330,   332,
     550,    99,    20,   100,   445,   478,   533,   321,   273,   274,
     275,   276,   277,   450,   263,   449,    99,   478,   331,   441,
     478,   496,     5,   321,   321,     5,   331,   428,   181,   463,
      99,   374,   356,   358,   363,   367,   411,   411,   411,   374,
     374,   374,   374,    39,   330,   330,   360,     8,   330,     7,
     330,   330,   360,     5,   330,   146,   385,   320,   369,   321,
     321,   321,   581,   319,   160,   165,   549,   397,   395,    99,
     549,    99,   397,   101,   397,   450,   449,   423,   263,   448,
      99,   444,   321,   496,   572,    38,   464,   330,   320,   320,
     320,   320,   320,   374,   374,   374,   320,   320,   320,   320,
     100,   372,   362,   245,   261,   266,   268,   373,    22,    99,
     100,   318,   386,   387,   388,   507,   330,   100,   370,   371,
     330,   320,   330,   330,   330,   330,   330,   330,   330,   129,
     330,   448,   321,    99,   100,   248,   321,   331,   463,   382,
     357,   359,   364,   368,   320,   320,   320,   375,   380,   376,
     381,    40,    41,   389,   330,   330,   330,   330,   330,    99,
      22,    25,     7,   321,   100,   551,   552,   549,   247,   464,
     321,   330,   332,   461,   321,   321,   321,   321,   378,   379,
     377,   321,   330,   332,   542,   321,   330,   332,   556,   321,
     330,   332,   544,   321,   330,   332,   546,   394,   319,   385,
      99,    99,   331,   371,     5,     7,   321,   330,   330,   330,
     330,   330,   330,   321,   321,   321,   330,   330,   330,   330,
     369,    99,   552,   330,   330,   330,   330
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   328,   329,   329,   330,   330,   331,   331,   332,   332,
     332,   332,   332,   333,   333,   333,   333,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   336,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   338,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   340,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   341,   342,   342,
     342,   342,   342,   342,   343,   343,   343,   343,   343,   343,
     343,   344,   345,   345,   346,   346,   347,   348,   348,   349,
     349,   349,   349,   349,   349,   349,   349,   350,   350,   351,
     351,   351,   352,   353,   354,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   356,   357,   357,   357,   357,   357,   357,   358,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   360,
     360,   361,   361,   362,   362,   362,   362,   363,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   364,   364,
     365,   365,   366,   366,   367,   368,   368,   368,   368,   368,
     369,   370,   370,   370,   371,   372,   372,   373,   373,   374,
     375,   375,   375,   375,   376,   376,   376,   376,   377,   377,
     377,   377,   378,   378,   378,   378,   379,   379,   379,   379,
     380,   380,   380,   380,   381,   381,   381,   381,   382,   382,
     382,   382,   383,   383,   383,   383,   383,   384,   385,   386,
     386,   387,   387,   387,   387,   387,   388,   388,   389,   389,
     389,   390,   391,   391,   392,   392,   393,   394,   394,   394,
     395,   396,   396,   397,   397,   397,   397,   397,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   413,   414,   415,   415,   415,   415,
     416,   417,   418,   418,   419,   419,   420,   421,   421,   422,
     422,   422,   422,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   424,   424,   425,   426,   426,   427,   427,   427,
     428,   429,   429,   430,   430,   431,   431,   432,   432,   433,
     433,   434,   434,   435,   436,   436,   437,   437,   437,   437,
     437,   437,   438,   439,   439,   439,   439,   439,   440,   440,
     441,   441,   442,   442,   442,   443,   443,   443,   444,   444,
     445,   445,   446,   446,   447,   447,   447,   448,   448,   449,
     449,   449,   450,   450,   450,   450,   450,   451,   452,   453,
     453,   453,   453,   453,   454,   455,   455,   456,   456,   456,
     456,   456,   456,   457,   457,   458,   458,   459,   459,   460,
     460,   460,   460,   461,   461,   462,   463,   463,   464,   464,
     465,   465,   465,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   466,   466,   466,   467,   467,   468,   468,   469,
     469,   470,   471,   471,   472,   472,   473,   473,   474,   475,
     476,   477,   477,   477,   478,   478,   478,   479,   479,   479,
     479,   479,   479,   479,   479,   479,   480,   480,   481,   482,
     482,   482,   483,   483,   484,   485,   485,   485,   485,   485,
     486,   486,   487,   487,   488,   488,   489,   489,   489,   490,
     490,   491,   492,   492,   493,   493,   494,   494,   495,   495,
     496,   496,   497,   498,   498,   498,   499,   499,   499,   500,
     500,   501,   501,   502,   503,   503,   504,   505,   505,   506,
     507,   508,   508,   509,   509,   510,   511,   512,   512,   512,
     512,   512,   512,   512,   512,   512,   512,   512,   512,   512,
     512,   512,   513,   514,   514,   514,   515,   515,   515,   515,
     515,   516,   516,   517,   517,   518,   518,   519,   519,   519,
     520,   520,   521,   521,   522,   522,   523,   524,   524,   525,
     526,   527,   527,   527,   528,   529,   529,   529,   530,   531,
     531,   531,   532,   532,   532,   533,   533,   534,   535,   535,
     536,   537,   537,   538,   538,   538,   539,   539,   540,   540,
     541,   541,   542,   543,   544,   545,   546,   547,   548,   548,
     548,   549,   549,   550,   550,   551,   551,   552,   553,   553,
     553,   554,   554,   554,   554,   554,   555,   556,   556,   557,
     558,   558,   558,   559,   559,   560,   560,   560,   560,   561,
     561,   561,   562,   562,   563,   563,   564,   564,   565,   566,
     566,   567,   567,   568,   569,   569,   569,   569,   569,   569,
     569,   569,   569,   569,   569,   569,   570,   570,   570,   570,
     570,   570,   570,   570,   570,   570,   570,   570,   570,   570,
     570,   570,   570,   571,   571,   571,   571,   571,   571,   572,
     572,   572,   572,   572,   572,   573,   573,   574,   574,   574,
     575,   575,   576,   576,   576,   576,   576,   577,   577,   577,
     577,   577,   577,   577,   577,   577,   577,   577,   577,   577,
     577,   577,   577,   577,   577,   577,   577,   577,   577,   577,
     577,   578,   578,   578,   578,   578,   578,   579,   580,   580,
     581,   581,   582,   582,   583,   584,   584,   585,   585,   586,
     586,   587,   587,   588,   588,   589,   589,   589,   590,   590,
     591,   591,   592,   592,   592,   592,   593,   593,   593,   594,
     594,   595,   595,   595,   595,   595,   595,   595,   595,   595,
     595,   595,   595,   595,   595,   595,   595,   596,   596,   596,
     596,   596,   596,   596,   597,   597,   597,   597,   598,   598,
     598,   598,   599,   599,   600,   600,   601,   601,   601,   601,
     602,   603,   603,   603,   603,   603,   603,   603,   603,   603,
     603,   603,   603,   603,   603,   603,   603,   603,   603,   604,
     605,   605,   605,   606,   607,   607,   607,   608,   609,   609,
     609,   609,   610,   611,   611,   611,   611,   611,   611,   611,
     611,   611,   612,   612,   612,   613,   613,   613,   613,   613,
     613,   613,   613,   613,   613,   613,   613,   614,   614,   614,
     614,   615,   615,   615,   615,   615,   616,   617,   617,   617,
     617,   617,   617,   617,   618,   619,   619,   619,   619,   620,
     621,   621,   621,   621,   621,   621,   621,   621,   621,   622,
     623,   623,   623,   623,   623,   623,   623,   623,   624,   625,
     625,   625,   625,   625,   626,   627,   627,   628,   629,   629,
     629,   630,   631,   631,   631,   631,   632,   633,   633,   633,
     633,   634,   634,   634,   635,   635,   635,   635,   635,   635,
     635,   635,   635,   635,   636,   636,   636,   636,   636,   636,
     636,   636,   636,   636,   636,   636,   637,   637,   637,   637,
     637,   637,   637,   637,   638,   639,   639,   639,   640,   641,
     641,   641,   641,   642,   643,   643,   644,   644,   644,   644,
     644,   644,   644,   644,   645,   646,   646,   647,   648,   648,
     648,   648,   649,   650,   651,   652,   653,   654,   654,   654,
     654,   655,   656,   656,   656,   656,   656,   656,   657,   658,
     658,   659,   660,   660,   660,   660,   660,   661,   662,   662,
     662,   662,   662
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       5,     3,     2,     1,     1,     2,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     6,     2,     6,     3,     2,     6,     6,
       3,     6,     2,     4,     4,     7,     7,     7,     4,     4,
       4,     3,     2,     6,     2,     6,     6,     6,     3,     6,
       2,     4,     4,     7,     7,     7,     4,     4,     4,     3,
       2,     2,     2,     2,     2,     2,     2,     2,     3,     2,
       2,     2,     2,     2,     2,     4,     2,     2,     2,     2,
       2,     2,     3,     2,     2,     2,     2,     2,     3,     2,
       2,     3,     2,     2,     3,     2,     2,     3,     2,     2,
       3,     2,     2,     3,     2,     2,     3,     3,     2,     2,
       2,     2,     2,     2,     3,     4,     4,     4,     2,     3,
       2,     2,     3,     2,     2,     2,     2,     2,     3,     2,
       2,     3,     2,     1,     2,     1,     3,     0,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       1,     2,     1,     0,     2,     0,     2,     2,     3,     8,
       8,     8,     8,     8,     8,     9,     9,     9,     8,     8,
       8,     0,     0,     2,     2,     3,     3,     3,     0,     0,
       2,     2,     4,     4,     4,     4,     4,     2,     3,     1,
       1,     3,     1,     1,     1,     1,     1,     0,     0,     2,
       2,     4,     6,     6,     6,     6,     6,     4,     4,     3,
       2,     2,     1,     1,     0,     0,     2,     2,     5,     5,
       3,     1,     3,     3,     1,     1,     1,     1,     3,     0,
       0,     2,     2,     2,     0,     2,     2,     2,     0,     2,
       2,     2,     0,     2,     2,     2,     0,     2,     2,     2,
       0,     2,     2,     2,     0,     2,     2,     2,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     6,     2,     1,
       1,     1,     1,     1,     3,     3,     1,     2,     2,     3,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     2,     3,     1,     2,     3,     1,     2,     3,     1,
       2,     3,     1,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     0,     1,     1,     2,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     1,     3,     3,
       5,     3,     4,     1,     2,     1,     3,     1,     2,     2,
       2,     1,     2,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     1,     2,     2,     1,     1,     1,     3,     1,
       1,     1,     7,     6,     3,     1,     1,     0,     1,     1,
       0,     3,     5,     3,     1,     1,     0,     0,     3,     0,
       3,     3,     1,     1,     1,     1,     1,     2,     1,     0,
       4,     4,     4,     3,     2,     1,     1,     3,     4,     4,
       5,     6,     5,     1,     2,     1,     3,     1,     2,     2,
       2,     1,     1,     6,     8,     0,     0,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     3,     1,     1,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       3,     4,     5,     2,     3,     2,     2,     1,     1,     3,
       4,     1,     2,     1,     1,     2,     3,     1,     3,     4,
       3,     5,     3,     6,     1,     3,     1,     1,     1,     1,
       2,     1,     1,     2,     2,     1,     1,     3,     1,     1,
       1,     2,     1,     4,     5,     6,     1,     1,     1,     7,
       8,     6,     1,     1,     1,     2,     2,     6,     8,     1,
       2,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     3,     0,     2,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     1,     3,     3,
       3,     1,     1,     1,     3,     1,     1,     1,     3,     1,
       3,     3,     3,     3,     5,     1,     2,     1,     1,     2,
       1,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     4,     0,     4,     0,     1,     0,     1,     1,
       1,     1,     1,     5,     3,     1,     3,     3,     3,     6,
       3,     3,     3,     3,     3,     3,     0,     6,     5,     0,
       2,     2,     3,     3,     3,     1,     1,     1,     1,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     3,     4,     1,     4,     4,     2,     1,     1,
       0,     2,     1,     1,     5,     2,     0,     1,     1,     1,
       1,     1,     1,     4,     5,     7,     5,     4,     1,     1,
       2,     3,     1,     1,     1,     1,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     3,     3,     4,     4,     4,     5,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     6,
       1,     1,     1,     2,     1,     1,     1,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     2,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     1,     1,
       1,     2,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     2,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     1,     1,
       1,     1,     2,     4,     2,     1,     2,     1,     1,     1,
       4,     2,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, nft, scanner, state); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (nft);
  YYUSE (scanner);
  YYUSE (state);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, nft, scanner, state);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , nft, scanner, state);
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (nft);
  YYUSE (scanner);
  YYUSE (state);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
    case 100: /* "string"  */
#line 280 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4159 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 101: /* "quoted string"  */
#line 280 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4165 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 102: /* "string with a trailing asterisk"  */
#line 280 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4171 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 333: /* line  */
#line 555 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4177 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 334: /* base_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4183 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* add_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4189 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 336: /* replace_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4195 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* create_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4201 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* insert_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4207 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* delete_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4213 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* get_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4219 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* list_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4225 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* reset_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4231 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* flush_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4237 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* rename_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4243 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 345: /* import_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4249 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* export_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4255 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* monitor_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4261 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 348: /* monitor_event  */
#line 779 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4267 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 352: /* describe_cmd  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4273 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 353: /* table_block_alloc  */
#line 574 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 4279 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* chain_block_alloc  */
#line 576 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 4285 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* set_block_alloc  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4291 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* set_block_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4297 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 363: /* map_block_alloc  */
#line 588 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4303 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 367: /* flowtable_block_alloc  */
#line 591 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 4309 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 369: /* flowtable_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4315 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 370: /* flowtable_list_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4321 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 371: /* flowtable_expr_member  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4327 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 372: /* data_type_atom_expr  */
#line 552 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4333 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* data_type_expr  */
#line 552 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4339 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 374: /* obj_block_alloc  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4345 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* type_identifier  */
#line 547 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4351 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* extended_prio_name  */
#line 568 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4357 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* dev_spec  */
#line 571 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).expr)); }
#line 4363 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* policy_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4369 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 393: /* identifier  */
#line 547 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4375 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* string  */
#line 547 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4381 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* table_spec  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4387 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* tableid_spec  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4393 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* chain_spec  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4399 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* chainid_spec  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4405 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* chain_identifier  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4411 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* set_spec  */
#line 563 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4417 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* setid_spec  */
#line 563 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4423 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* set_identifier  */
#line 563 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4429 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* flowtable_spec  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4435 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* flowtableid_spec  */
#line 563 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4441 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* obj_spec  */
#line 563 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4447 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* objid_spec  */
#line 563 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4453 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* obj_identifier  */
#line 563 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4459 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 412: /* handle_spec  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4465 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* position_spec  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4471 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* index_spec  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4477 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* rule_position  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4483 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* ruleid_spec  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4489 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* comment_spec  */
#line 547 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4495 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* ruleset_spec  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4501 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* rule  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 4507 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* stmt_list  */
#line 597 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 4513 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* stateful_stmt  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4519 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* stmt  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4525 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* verdict_stmt  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4531 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* verdict_map_stmt  */
#line 678 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4537 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* verdict_map_expr  */
#line 681 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4543 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* verdict_map_list_expr  */
#line 681 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4549 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* verdict_map_list_member_expr  */
#line 681 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4555 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* connlimit_stmt  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4561 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* counter_stmt  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4567 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* counter_stmt_alloc  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4573 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* log_stmt  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4579 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* log_stmt_alloc  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4585 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* limit_stmt  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4591 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 444: /* quota_unit  */
#line 568 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4597 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 446: /* quota_stmt  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4603 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* reject_stmt  */
#line 615 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4609 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* reject_stmt_alloc  */
#line 615 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4615 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 454: /* nat_stmt  */
#line 617 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4621 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 455: /* nat_stmt_alloc  */
#line 617 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4627 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 456: /* tproxy_stmt  */
#line 620 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4633 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* synproxy_stmt  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4639 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* synproxy_stmt_alloc  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4645 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* synproxy_obj  */
#line 704 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4651 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* primary_stmt_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4657 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* shift_stmt_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4663 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 467: /* and_stmt_expr  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4669 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* exclusive_or_stmt_expr  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4675 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* inclusive_or_stmt_expr  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4681 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* basic_stmt_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4687 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* concat_stmt_expr  */
#line 657 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4693 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* map_stmt_expr_set  */
#line 657 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4699 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* map_stmt_expr  */
#line 657 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4705 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* prefix_stmt_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4711 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* range_stmt_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4717 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* wildcard_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4723 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* multiton_stmt_expr  */
#line 660 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4729 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* stmt_expr  */
#line 657 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4735 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* masq_stmt  */
#line 617 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4741 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* masq_stmt_alloc  */
#line 617 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4747 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 483: /* redir_stmt  */
#line 617 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4753 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* redir_stmt_alloc  */
#line 617 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4759 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 486: /* dup_stmt  */
#line 629 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4765 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* fwd_stmt  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4771 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 490: /* queue_stmt  */
#line 626 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4777 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 491: /* queue_stmt_alloc  */
#line 626 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4783 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 496: /* set_elem_expr_stmt  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4789 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 497: /* set_elem_expr_stmt_alloc  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4795 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 498: /* set_stmt  */
#line 633 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4801 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* map_stmt  */
#line 636 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4807 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* meter_stmt  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4813 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 502: /* flow_stmt_legacy_alloc  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4819 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* meter_stmt_alloc  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4825 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* match_stmt  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4831 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* variable_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4837 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 508: /* symbol_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4843 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 509: /* set_ref_expr  */
#line 649 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4849 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* set_ref_symbol_expr  */
#line 649 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4855 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 511: /* integer_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4861 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 512: /* primary_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4867 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* fib_expr  */
#line 770 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4873 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* osf_expr  */
#line 775 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4879 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* shift_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4885 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 520: /* and_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4891 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 521: /* exclusive_or_expr  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4897 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 522: /* inclusive_or_expr  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4903 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* basic_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4909 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 524: /* concat_expr  */
#line 672 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4915 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 525: /* prefix_rhs_expr  */
#line 654 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4921 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 526: /* range_rhs_expr  */
#line 654 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4927 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 527: /* multiton_rhs_expr  */
#line 652 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4933 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* map_expr  */
#line 675 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4939 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* expr  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4945 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* set_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4951 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* set_list_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4957 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* set_list_member_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4963 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* meter_key_expr  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4969 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* meter_key_expr_alloc  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4975 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* set_elem_expr  */
#line 686 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4981 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* set_elem_expr_alloc  */
#line 686 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4987 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* set_lhs_expr  */
#line 686 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4993 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* set_rhs_expr  */
#line 686 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4999 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* initializer_expr  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5005 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* counter_obj  */
#line 704 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5011 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 545: /* quota_obj  */
#line 704 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5017 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* secmark_obj  */
#line 704 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5023 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* timeout_states  */
#line 800 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5029 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 552: /* timeout_state  */
#line 800 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5035 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 555: /* ct_obj_alloc  */
#line 704 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5041 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 557: /* limit_obj  */
#line 704 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5047 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 558: /* relational_expr  */
#line 707 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5053 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 559: /* list_rhs_expr  */
#line 699 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5059 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 560: /* rhs_expr  */
#line 697 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5065 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 561: /* shift_rhs_expr  */
#line 699 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5071 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 562: /* and_rhs_expr  */
#line 701 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5077 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 563: /* exclusive_or_rhs_expr  */
#line 701 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5083 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 564: /* inclusive_or_rhs_expr  */
#line 701 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5089 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 565: /* basic_rhs_expr  */
#line 697 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5095 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 566: /* concat_rhs_expr  */
#line 697 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5101 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 568: /* boolean_expr  */
#line 790 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5107 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 569: /* keyword_expr  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5113 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 570: /* primary_rhs_expr  */
#line 699 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5119 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 572: /* verdict_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5125 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 573: /* chain_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5131 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 574: /* meta_expr  */
#line 752 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5137 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 578: /* meta_stmt  */
#line 607 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5143 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 579: /* socket_expr  */
#line 756 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5149 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 583: /* numgen_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5155 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 588: /* xfrm_expr  */
#line 804 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5161 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 589: /* hash_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5167 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 591: /* rt_expr  */
#line 762 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5173 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 593: /* ct_expr  */
#line 766 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5179 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 599: /* symbol_stmt_expr  */
#line 699 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5185 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 600: /* list_stmt_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5191 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 601: /* ct_stmt  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5197 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 602: /* payload_stmt  */
#line 603 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5203 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 603: /* payload_expr  */
#line 711 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5209 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 604: /* payload_raw_expr  */
#line 711 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5215 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 606: /* eth_hdr_expr  */
#line 714 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5221 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 608: /* vlan_hdr_expr  */
#line 714 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5227 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 610: /* arp_hdr_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5233 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 612: /* ip_hdr_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5239 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 616: /* icmp_hdr_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5245 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 618: /* igmp_hdr_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5251 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 620: /* ip6_hdr_expr  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5257 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 622: /* icmp6_hdr_expr  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5263 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 624: /* auth_hdr_expr  */
#line 727 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5269 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 626: /* esp_hdr_expr  */
#line 727 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5275 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 628: /* comp_hdr_expr  */
#line 727 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5281 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 630: /* udp_hdr_expr  */
#line 730 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5287 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 632: /* udplite_hdr_expr  */
#line 730 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5293 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 634: /* tcp_hdr_expr  */
#line 785 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5299 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 638: /* dccp_hdr_expr  */
#line 733 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5305 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 640: /* sctp_hdr_expr  */
#line 733 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5311 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 642: /* th_hdr_expr  */
#line 736 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5317 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 644: /* exthdr_expr  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5323 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 645: /* hbh_hdr_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5329 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 647: /* rt_hdr_expr  */
#line 745 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5335 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 649: /* rt0_hdr_expr  */
#line 745 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5341 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 651: /* rt2_hdr_expr  */
#line 745 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5347 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 653: /* rt4_hdr_expr  */
#line 745 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5353 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 655: /* frag_hdr_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5359 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 657: /* dst_hdr_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5365 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 659: /* mh_hdr_expr  */
#line 748 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5371 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 661: /* exthdr_exists_expr  */
#line 794 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5377 "parser_bison.c" /* yacc.c:1257  */
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
/* The lookahead symbol.  */
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
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
#line 127 "parser_bison.y" /* yacc.c:1431  */
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 5493 "parser_bison.c" /* yacc.c:1431  */
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
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
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
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
        case 3:
#line 810 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 5692 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 8:
#line 827 "parser_bison.y" /* yacc.c:1652  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5704 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 9:
#line 835 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, (yyvsp[-3].string)) != NULL) {
					erec_queue(error(&(yylsp[-3]), "redefinition of symbol '%s'", (yyvsp[-3].string)),
						   state->msgs);
					xfree((yyvsp[-3].string));
					YYERROR;
				}

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 5722 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 10:
#line 849 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 5733 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 11:
#line 856 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 12:
#line 867 "parser_bison.y" /* yacc.c:1652  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 5758 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 13:
#line 874 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 5764 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 14:
#line 875 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 5770 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 15:
#line 876 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 5776 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 16:
#line 878 "parser_bison.y" /* yacc.c:1652  */
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
#line 5798 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 17:
#line 897 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5804 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 18:
#line 898 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5810 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 19:
#line 899 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5816 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 20:
#line 900 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5822 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 21:
#line 901 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5828 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 22:
#line 902 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5834 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 23:
#line 903 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5840 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 24:
#line 904 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5846 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 25:
#line 905 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 26:
#line 906 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 27:
#line 907 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 28:
#line 908 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5870 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 29:
#line 909 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5876 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 30:
#line 910 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5882 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 31:
#line 911 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 32:
#line 915 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5896 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 33:
#line 920 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5906 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 34:
#line 926 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5914 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 35:
#line 931 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5925 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 36:
#line 938 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 37:
#line 942 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5941 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 38:
#line 947 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5951 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 39:
#line 954 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5961 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 40:
#line 960 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5969 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 41:
#line 965 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5979 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 42:
#line 971 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5992 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 43:
#line 980 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 44:
#line 984 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6008 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 45:
#line 988 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6016 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 46:
#line 992 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 47:
#line 996 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 48:
#line 1000 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 49:
#line 1004 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 50:
#line 1008 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 51:
#line 1014 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6064 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 52:
#line 1020 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 53:
#line 1025 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6082 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 54:
#line 1031 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6090 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 55:
#line 1036 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 56:
#line 1044 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6111 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 57:
#line 1051 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6121 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 58:
#line 1057 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6129 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 59:
#line 1062 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6139 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 60:
#line 1068 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 6152 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 61:
#line 1077 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 62:
#line 1081 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6168 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 63:
#line 1085 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6176 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 64:
#line 1089 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6184 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 65:
#line 1093 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6192 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 66:
#line 1097 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6200 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 67:
#line 1101 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6208 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 68:
#line 1105 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6216 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 69:
#line 1111 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6224 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 70:
#line 1117 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6232 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 71:
#line 1121 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6240 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 72:
#line 1125 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6248 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 73:
#line 1129 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6256 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 74:
#line 1133 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6264 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 75:
#line 1137 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6272 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 76:
#line 1141 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6280 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 77:
#line 1145 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6288 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 78:
#line 1149 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6296 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 79:
#line 1153 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6304 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 80:
#line 1157 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6312 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 81:
#line 1161 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6320 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 82:
#line 1165 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6328 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 83:
#line 1169 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6336 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 84:
#line 1173 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6344 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 85:
#line 1177 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6352 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 86:
#line 1181 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6360 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 87:
#line 1185 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6368 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 88:
#line 1189 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6376 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 89:
#line 1193 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 90:
#line 1197 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6392 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 91:
#line 1201 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6400 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 92:
#line 1207 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6408 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 93:
#line 1213 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 94:
#line 1217 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6424 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 95:
#line 1221 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6432 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 96:
#line 1225 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 97:
#line 1229 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6448 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 98:
#line 1233 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6456 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 99:
#line 1237 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6464 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 100:
#line 1241 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6472 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 101:
#line 1245 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6480 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 102:
#line 1249 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6488 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 103:
#line 1253 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6496 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 104:
#line 1257 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 105:
#line 1261 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6512 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1265 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6520 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1269 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1273 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6536 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1277 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6544 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1281 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6552 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1285 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6560 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1289 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1293 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1297 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6584 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 115:
#line 1301 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6592 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 116:
#line 1305 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6600 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 117:
#line 1309 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6608 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 118:
#line 1313 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6616 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 119:
#line 1317 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1321 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6632 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1325 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6640 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1329 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6648 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1333 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6656 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1337 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6664 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1341 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1345 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_TIMEOUT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6680 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1349 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_EXPECT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1355 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6696 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1359 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6704 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1363 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 6712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1367 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6720 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1371 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6728 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1375 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1381 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6744 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1385 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6752 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1389 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1393 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6768 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 138:
#line 1397 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6776 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 139:
#line 1401 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 140:
#line 1405 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6792 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 141:
#line 1411 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 6801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1418 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6811 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1424 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6821 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1432 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6831 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 145:
#line 1438 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6841 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 146:
#line 1446 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 6852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 147:
#line 1454 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = NULL; }
#line 6858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 148:
#line 1455 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 149:
#line 1458 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 6870 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 150:
#line 1459 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 6876 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 151:
#line 1460 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 6882 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 152:
#line 1461 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 6888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 153:
#line 1462 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 6894 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1463 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 6900 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1464 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 6906 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1465 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 6912 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 157:
#line 1468 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 6918 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 159:
#line 1472 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 6924 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1473 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 6930 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1474 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 6936 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1478 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 6946 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1486 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 6955 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 164:
#line 1493 "parser_bison.y" /* yacc.c:1652  */
    {
				if (strcmp((yyvsp[0].string), "dormant") == 0) {
					(yyvsp[-2].table)->flags = TABLE_F_DORMANT;
					xfree((yyvsp[0].string));
				} else {
					erec_queue(error(&(yylsp[0]), "unknown table option %s", (yyvsp[0].string)),
						   state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}
			}
#line 6971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1506 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 6977 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 169:
#line 1513 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6990 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1524 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7002 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1534 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7014 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1545 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7026 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 173:
#line 1555 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7039 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 174:
#line 1566 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7052 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 175:
#line 1575 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7065 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 176:
#line 1584 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7078 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 177:
#line 1593 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7091 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 178:
#line 1604 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7104 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 179:
#line 1615 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7117 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 180:
#line 1626 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7130 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 181:
#line 1637 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 7139 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 182:
#line 1643 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7145 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 187:
#line 1649 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 7154 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 188:
#line 1656 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7162 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 189:
#line 1661 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7168 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 192:
#line 1665 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7177 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 193:
#line 1670 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7186 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 194:
#line 1675 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 195:
#line 1680 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 196:
#line 1685 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 197:
#line 1690 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 7222 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 201:
#line 1702 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7230 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 203:
#line 1708 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 7236 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 204:
#line 1709 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 7242 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 205:
#line 1710 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 7248 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 206:
#line 1711 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_EVAL; }
#line 7254 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 207:
#line 1715 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7262 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 208:
#line 1720 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7268 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 211:
#line 1724 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7277 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 212:
#line 1731 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].expr)->dtype;

				expr_free((yyvsp[-1].expr));
				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 213:
#line 1742 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7301 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 214:
#line 1751 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7312 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 215:
#line 1760 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7323 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 216:
#line 1769 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_SECMARK;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 217:
#line 1776 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7343 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 218:
#line 1781 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7352 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 220:
#line 1789 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 7360 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 221:
#line 1793 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 7368 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 222:
#line 1798 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 7374 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 223:
#line 1799 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 7380 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 224:
#line 1803 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 7388 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 225:
#line 1808 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 7394 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 228:
#line 1812 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->hookstr	= chain_hookname_lookup((yyvsp[-2].string));
				if ((yyval.flowtable)->hookstr == NULL) {
					erec_queue(error(&(yylsp[-2]), "unknown chain hook %s", (yyvsp[-2].string)),
						   state->msgs);
					xfree((yyvsp[-2].string));
					YYERROR;
				}
				xfree((yyvsp[-2].string));

				(yyval.flowtable)->priority = (yyvsp[-1].prio_spec);
			}
#line 7411 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 229:
#line 1825 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 7419 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 230:
#line 1831 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7428 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 231:
#line 1838 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7437 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 232:
#line 1843 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7446 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 234:
#line 1851 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 235:
#line 1860 "parser_bison.y" /* yacc.c:1652  */
    {
				const struct datatype *dtype = datatype_lookup_byname((yyvsp[0].string));
				if (dtype == NULL) {
					erec_queue(error(&(yylsp[0]), "unknown datatype %s", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), dtype, dtype->byteorder,
							 dtype->size, NULL);
				xfree((yyvsp[0].string));
			}
#line 7473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 236:
#line 1872 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 7482 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 238:
#line 1880 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].expr)->etype != EXPR_CONCAT) {
					(yyval.expr) = concat_expr_alloc(&(yyloc));
					compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				} else {
					struct location rhs[] = {
						[1]	= (yylsp[-1]),
						[2]	= (yylsp[0]),
					};
					location_update(&(yyvsp[0].expr)->location, rhs, 2);

					(yyval.expr) = (yyvsp[-2].expr);
					(yyval.expr)->location = (yyloc);
				}
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7503 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 239:
#line 1899 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 7511 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 240:
#line 1904 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7517 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 243:
#line 1908 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 244:
#line 1913 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7531 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 247:
#line 1917 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7539 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 248:
#line 1922 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7545 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 251:
#line 1926 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7553 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 252:
#line 1931 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 255:
#line 1935 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7567 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 256:
#line 1940 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7573 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 259:
#line 1944 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7581 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 260:
#line 1949 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7587 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 263:
#line 1953 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7595 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 264:
#line 1958 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7601 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 267:
#line 1962 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7609 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 268:
#line 1967 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 271:
#line 1971 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7623 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 272:
#line 1976 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7629 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 273:
#line 1977 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("mark"); }
#line 7635 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 274:
#line 1978 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("dscp"); }
#line 7641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 275:
#line 1979 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("ecn"); }
#line 7647 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 276:
#line 1980 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("classid"); }
#line 7653 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 277:
#line 1984 "parser_bison.y" /* yacc.c:1652  */
    {
				const char *chain_type = chain_type_name_lookup((yyvsp[-4].string));

				if (chain_type == NULL) {
					erec_queue(error(&(yylsp[-4]), "unknown chain type %s", (yyvsp[-4].string)),
						   state->msgs);
					xfree((yyvsp[-4].string));
					YYERROR;
				}
				(yyvsp[-6].chain)->type		= xstrdup(chain_type);
				xfree((yyvsp[-4].string));

				(yyvsp[-6].chain)->hookstr	= chain_hookname_lookup((yyvsp[-2].string));
				if ((yyvsp[-6].chain)->hookstr == NULL) {
					erec_queue(error(&(yylsp[-2]), "unknown chain hook %s", (yyvsp[-2].string)),
						   state->msgs);
					xfree((yyvsp[-2].string));
					YYERROR;
				}
				xfree((yyvsp[-2].string));

				(yyvsp[-6].chain)->dev_expr	= (yyvsp[-1].expr);
				(yyvsp[-6].chain)->priority	= (yyvsp[0].prio_spec);
				(yyvsp[-6].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
#line 7683 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 278:
#line 2012 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 7692 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 279:
#line 2019 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.string) = strdup("out");
			}
#line 7700 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 281:
#line 2026 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 7714 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 282:
#line 2036 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				datatype_set((yyvsp[0].expr)->sym->expr, &priority_type);
				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 7726 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 283:
#line 2044 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 7741 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 284:
#line 2055 "parser_bison.y" /* yacc.c:1652  */
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
#line 7758 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 285:
#line 2068 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};
				char str[NFT_NAME_MAXLEN];

				snprintf(str, sizeof(str), "%s - %" PRIu64, (yyvsp[-2].string), (yyvsp[0].val));
				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen(str) * BITS_PER_BYTE,
								str);
				(yyval.prio_spec) = spec;
			}
#line 7774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 286:
#line 2081 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = (yyvsp[0].val); }
#line 7780 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 287:
#line 2082 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = -(yyvsp[0].val); }
#line 7786 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 288:
#line 2086 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 7801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 289:
#line 2097 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 7809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 290:
#line 2100 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = NULL; }
#line 7815 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 291:
#line 2104 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].chain)->policy) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].expr);
			}
#line 7829 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 292:
#line 2116 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 7838 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 293:
#line 2121 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 7849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 294:
#line 2129 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_ACCEPT; }
#line 7855 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 295:
#line 2130 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_DROP;   }
#line 7861 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 300:
#line 2142 "parser_bison.y" /* yacc.c:1652  */
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
#line 7878 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 301:
#line 2156 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 7884 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 303:
#line 2160 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 7890 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 304:
#line 2161 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 7896 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 305:
#line 2162 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_INET; }
#line 7902 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 306:
#line 2163 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_ARP; }
#line 7908 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 307:
#line 2164 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 7914 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 308:
#line 2165 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 7920 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 309:
#line 2169 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 7931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 310:
#line 2178 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yyloc);
			}
#line 7942 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 311:
#line 2187 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 7952 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 312:
#line 2195 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 7962 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 313:
#line 2203 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 7972 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 314:
#line 2211 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 7982 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 315:
#line 2219 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 7992 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 316:
#line 2227 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 8002 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 317:
#line 2235 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 8012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 318:
#line 2243 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8022 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 319:
#line 2251 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 8032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 320:
#line 2259 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 8042 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 321:
#line 2267 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8052 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 322:
#line 2275 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 8062 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 323:
#line 2283 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 324:
#line 2291 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 8082 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 325:
#line 2299 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 8092 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 326:
#line 2307 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 8100 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 327:
#line 2311 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8109 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 328:
#line 2316 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8121 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 329:
#line 2324 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8130 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 330:
#line 2331 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8139 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 331:
#line 2338 "parser_bison.y" /* yacc.c:1652  */
    {
				if (strlen((yyvsp[0].string)) > NFTNL_UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed",
							 NFTNL_UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 8153 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 332:
#line 2350 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 8162 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 333:
#line 2355 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 8171 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 334:
#line 2362 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 8179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 335:
#line 2366 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 8187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 336:
#line 2372 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 8201 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 337:
#line 2384 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 8211 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 338:
#line 2390 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 8220 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 362:
#line 2424 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 363:
#line 2428 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8236 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 364:
#line 2434 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8244 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 365:
#line 2440 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8253 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 367:
#line 2448 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8262 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 368:
#line 2453 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8271 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 370:
#line 2461 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 8279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 371:
#line 2467 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[0].val);
			}
#line 8288 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 372:
#line 2472 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[0].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 8298 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 375:
#line 2483 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 8306 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 376:
#line 2487 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8316 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 377:
#line 2495 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8324 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 379:
#line 2502 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 8332 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 380:
#line 2506 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 8340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 383:
#line 2516 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 8348 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 384:
#line 2522 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8356 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 386:
#line 2529 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 8365 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 387:
#line 2534 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 8374 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 388:
#line 2539 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 8383 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 389:
#line 2544 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 8392 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 390:
#line 2549 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 8401 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 391:
#line 2554 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 8409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 392:
#line 2560 "parser_bison.y" /* yacc.c:1652  */
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
#line 8441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 393:
#line 2590 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 8449 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 394:
#line 2594 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 8457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 395:
#line 2598 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 8465 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 396:
#line 2602 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 8473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 397:
#line 2606 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 8481 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 398:
#line 2612 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8489 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 400:
#line 2619 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 8497 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 401:
#line 2623 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 8505 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 402:
#line 2629 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 8518 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 403:
#line 2638 "parser_bison.y" /* yacc.c:1652  */
    {
				struct error_record *erec;
				uint64_t rate, unit;

				erec = rate_parse(&(yyloc), (yyvsp[-1].string), &rate, &unit);
				xfree((yyvsp[-1].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= rate * (yyvsp[-2].val);
				(yyval.stmt)->limit.unit	= unit;
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKT_BYTES;
				(yyval.stmt)->limit.flags = (yyvsp[-3].val);
			}
#line 8541 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 404:
#line 2657 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8551 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 405:
#line 2664 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 8557 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 406:
#line 2665 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8563 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 407:
#line 2666 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8569 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 408:
#line 2669 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("bytes"); }
#line 8575 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 409:
#line 2670 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 8581 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 410:
#line 2673 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8587 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 411:
#line 2675 "parser_bison.y" /* yacc.c:1652  */
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
#line 8604 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 412:
#line 2690 "parser_bison.y" /* yacc.c:1652  */
    {
				struct error_record *erec;
				uint64_t rate;

				erec = data_unit_parse(&(yyloc), (yyvsp[-1].string), &rate);
				xfree((yyvsp[-1].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.stmt) = quota_stmt_alloc(&(yyloc));
				(yyval.stmt)->quota.bytes	= (yyvsp[-2].val) * rate;
				(yyval.stmt)->quota.used = (yyvsp[0].val);
				(yyval.stmt)->quota.flags	= (yyvsp[-3].val);
			}
#line 8624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 413:
#line 2706 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8634 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 414:
#line 2713 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 8640 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 415:
#line 2714 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8646 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 416:
#line 2715 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8652 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 417:
#line 2718 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8658 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 418:
#line 2719 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 8664 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 419:
#line 2722 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8670 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 420:
#line 2723 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 8676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 421:
#line 2725 "parser_bison.y" /* yacc.c:1652  */
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
#line 8693 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 422:
#line 2739 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL; }
#line 8699 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 423:
#line 2740 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60; }
#line 8705 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 424:
#line 2741 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 8711 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 425:
#line 2742 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 8717 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 426:
#line 2743 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 8723 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 428:
#line 2750 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 8731 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 429:
#line 2756 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 8740 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 430:
#line 2761 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmp_code_type);
				xfree((yyvsp[0].string));
			}
#line 8755 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 431:
#line 2772 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpv6_code_type);
				xfree((yyvsp[0].string));
			}
#line 8770 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 432:
#line 2783 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpx_code_type);
				xfree((yyvsp[0].string));
			}
#line 8784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 433:
#line 2793 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 8792 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 435:
#line 2801 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 8798 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 436:
#line 2802 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 8804 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 437:
#line 2806 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 8814 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 438:
#line 2812 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 8824 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 439:
#line 2818 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8834 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 440:
#line 2824 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8845 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 441:
#line 2831 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8856 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 442:
#line 2838 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8866 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 445:
#line 2850 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 8874 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 446:
#line 2854 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8884 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 447:
#line 2862 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8892 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 449:
#line 2869 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 8901 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 450:
#line 2874 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 8910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 451:
#line 2879 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 8918 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 452:
#line 2883 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 8926 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 453:
#line 2889 "parser_bison.y" /* yacc.c:1652  */
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
#line 8946 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 454:
#line 2905 "parser_bison.y" /* yacc.c:1652  */
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
#line 8966 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 455:
#line 2923 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 8975 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 456:
#line 2929 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 457:
#line 2931 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 8989 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 458:
#line 2936 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 459:
#line 2938 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 9003 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 460:
#line 2943 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9009 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 461:
#line 2944 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9015 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 462:
#line 2945 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9021 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 463:
#line 2946 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9027 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 464:
#line 2947 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9033 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 465:
#line 2948 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9039 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 466:
#line 2949 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9045 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 467:
#line 2950 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9051 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 468:
#line 2951 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 469:
#line 2952 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9063 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 470:
#line 2953 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9069 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 471:
#line 2954 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9075 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 473:
#line 2959 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9083 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 474:
#line 2963 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9091 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 476:
#line 2970 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9099 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 478:
#line 2977 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 480:
#line 2984 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9115 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 483:
#line 2994 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyval.expr)->etype != EXPR_CONCAT) {
					(yyval.expr) = concat_expr_alloc(&(yyloc));
					compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				} else {
					struct location rhs[] = {
						[1]	= (yylsp[-1]),
						[2]	= (yylsp[0]),
					};
					location_update(&(yyvsp[0].expr)->location, rhs, 2);

					(yyval.expr) = (yyvsp[-2].expr);
					(yyval.expr)->location = (yyloc);
				}
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9136 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 486:
#line 3017 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9144 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 487:
#line 3020 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9150 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 488:
#line 3024 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 9158 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 489:
#line 3030 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9166 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 490:
#line 3036 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 9179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 497:
#line 3057 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 9187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 498:
#line 3061 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 9195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 499:
#line 3065 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 9204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 500:
#line 3070 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 501:
#line 3075 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9222 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 502:
#line 3080 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9232 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 503:
#line 3086 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9240 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 504:
#line 3090 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9248 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 505:
#line 3094 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9256 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 508:
#line 3103 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 9262 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 509:
#line 3107 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9270 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 510:
#line 3111 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 511:
#line 3116 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9287 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 514:
#line 3125 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 9293 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 515:
#line 3129 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9301 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 516:
#line 3133 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9309 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 517:
#line 3137 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9317 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 518:
#line 3141 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 519:
#line 3146 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9335 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 520:
#line 3153 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 9344 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 521:
#line 3158 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 9354 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 522:
#line 3166 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 9363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 523:
#line 3171 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 9374 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 525:
#line 3181 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9382 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 526:
#line 3186 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 9388 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 527:
#line 3187 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 9394 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 528:
#line 3188 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 9400 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 531:
#line 3196 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 9408 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 532:
#line 3202 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 534:
#line 3209 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 9425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 535:
#line 3214 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 9433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 537:
#line 3221 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 538:
#line 3226 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 9447 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 539:
#line 3227 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 9453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 542:
#line 3235 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 9461 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 543:
#line 3241 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 9472 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 544:
#line 3248 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 9483 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 545:
#line 3255 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				(yyval.stmt)->set.stmt = (yyvsp[-1].stmt);
			}
#line 9495 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 546:
#line 3264 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 9501 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 547:
#line 3265 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 9507 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 548:
#line 3266 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 9513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 549:
#line 3270 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 9525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 550:
#line 3278 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.stmt = (yyvsp[-3].stmt);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
			}
#line 9538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 551:
#line 3289 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 9549 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 552:
#line 3295 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 9555 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 553:
#line 3299 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 9563 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 554:
#line 3305 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9571 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 556:
#line 3312 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 9579 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 557:
#line 3318 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 9592 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 558:
#line 3327 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 9605 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 559:
#line 3338 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 9613 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 560:
#line 3344 "parser_bison.y" /* yacc.c:1652  */
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
#line 9641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 562:
#line 3371 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9652 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 565:
#line 3384 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9663 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 566:
#line 3393 "parser_bison.y" /* yacc.c:1652  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 9676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 567:
#line 3403 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 568:
#line 3404 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 569:
#line 3405 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 570:
#line 3406 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9700 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 571:
#line 3407 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 572:
#line 3408 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 573:
#line 3409 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9718 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 574:
#line 3410 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9724 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 575:
#line 3411 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 576:
#line 3412 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 577:
#line 3413 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 578:
#line 3414 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 579:
#line 3415 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 580:
#line 3416 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 581:
#line 3417 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 9766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 582:
#line 3421 "parser_bison.y" /* yacc.c:1652  */
    {
				if (((yyvsp[-1].val) & (NFTA_FIB_F_SADDR|NFTA_FIB_F_DADDR)) == 0) {
					erec_queue(error(&(yylsp[-1]), "fib: need either saddr or daddr"), state->msgs);
					YYERROR;
				}

				if (((yyvsp[-1].val) & (NFTA_FIB_F_SADDR|NFTA_FIB_F_DADDR)) ==
					  (NFTA_FIB_F_SADDR|NFTA_FIB_F_DADDR)) {
					erec_queue(error(&(yylsp[-1]), "fib: saddr and daddr are mutually exclusive"), state->msgs);
					YYERROR;
				}

				if (((yyvsp[-1].val) & (NFTA_FIB_F_IIF|NFTA_FIB_F_OIF)) ==
					  (NFTA_FIB_F_IIF|NFTA_FIB_F_OIF)) {
					erec_queue(error(&(yylsp[-1]), "fib: iif and oif are mutually exclusive"), state->msgs);
					YYERROR;
				}

				(yyval.expr) = fib_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 9791 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 583:
#line 3443 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 9797 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 584:
#line 3444 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 9803 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 585:
#line 3445 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 9809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 586:
#line 3448 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 9815 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 587:
#line 3449 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 9821 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 588:
#line 3450 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 9827 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 589:
#line 3451 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 9833 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 590:
#line 3452 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 9839 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 591:
#line 3456 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9847 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 593:
#line 3463 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), NFT_OSF_F_VERSION);
			}
#line 9855 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 594:
#line 3467 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 9863 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 595:
#line 3473 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 9871 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 596:
#line 3477 "parser_bison.y" /* yacc.c:1652  */
    {
				if (!strcmp((yyvsp[0].string), "loose"))
					(yyval.val) = NF_OSF_TTL_LESS;
				else if (!strcmp((yyvsp[0].string), "skip"))
					(yyval.val) = NF_OSF_TTL_NOCHECK;
				else {
					erec_queue(error(&(yylsp[0]), "invalid ttl option"),
						   state->msgs);
					YYERROR;
				}
			}
#line 9887 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 598:
#line 3492 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9895 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 599:
#line 3496 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9903 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 601:
#line 3503 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9911 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 603:
#line 3510 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9919 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 605:
#line 3517 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9927 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 608:
#line 3527 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyval.expr)->etype != EXPR_CONCAT) {
					(yyval.expr) = concat_expr_alloc(&(yyloc));
					compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				} else {
					struct location rhs[] = {
						[1]	= (yylsp[-1]),
						[2]	= (yylsp[0]),
					};
					location_update(&(yyvsp[0].expr)->location, rhs, 2);

					(yyval.expr) = (yyvsp[-2].expr);
					(yyval.expr)->location = (yyloc);
				}
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9948 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 609:
#line 3546 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 9956 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 610:
#line 3552 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9964 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 614:
#line 3563 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9972 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 618:
#line 3574 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 619:
#line 3581 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9990 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 620:
#line 3586 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9999 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 622:
#line 3594 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10007 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 623:
#line 3598 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10015 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 624:
#line 3602 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 10023 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 626:
#line 3609 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 627:
#line 3616 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 630:
#line 3626 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 631:
#line 3632 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 10056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 633:
#line 3639 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 10064 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 634:
#line 3643 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 10072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 635:
#line 3647 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 10080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 642:
#line 3665 "parser_bison.y" /* yacc.c:1652  */
    {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 10092 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 643:
#line 3675 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 10101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 644:
#line 3682 "parser_bison.y" /* yacc.c:1652  */
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
#line 10123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 645:
#line 3702 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 10132 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 646:
#line 3709 "parser_bison.y" /* yacc.c:1652  */
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
#line 10150 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 647:
#line 3725 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 10159 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 648:
#line 3731 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 10165 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 649:
#line 3732 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 10171 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 650:
#line 3733 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 10177 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 651:
#line 3736 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_TCP; }
#line 10183 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 652:
#line 3737 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_UDP; }
#line 10189 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 653:
#line 3741 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_helper *ct;
				int ret;

				ct = &(yyvsp[-5].obj)->ct_helper;

				ret = snprintf(ct->name, sizeof(ct->name), "%s", (yyvsp[-3].string));
				if (ret <= 0 || ret >= (int)sizeof(ct->name)) {
					erec_queue(error(&(yylsp[-3]), "invalid name '%s', max length is %u\n", (yyvsp[-3].string), (int)sizeof(ct->name)), state->msgs);
					YYERROR;
				}

				ct->l4proto = (yyvsp[-1].val);
			}
#line 10208 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 654:
#line 3756 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 10216 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 655:
#line 3762 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 10226 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 656:
#line 3768 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 10235 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 657:
#line 3776 "parser_bison.y" /* yacc.c:1652  */
    {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 10250 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 658:
#line 3789 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 10262 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 659:
#line 3797 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;

				ct = &(yyvsp[-6].obj)->ct_timeout;
				init_list_head(&ct->timeout_list);
				list_splice_tail((yyvsp[-2].list), &ct->timeout_list);
			}
#line 10274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 660:
#line 3805 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 10282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 661:
#line 3811 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 10290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 662:
#line 3815 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 10298 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 663:
#line 3819 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 10306 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 664:
#line 3823 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 10314 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 665:
#line 3827 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 10322 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 666:
#line 3833 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 10330 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 667:
#line 3839 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;

				limit = &(yyvsp[-6].obj)->limit;
				limit->rate	= (yyvsp[-3].val);
				limit->unit	= (yyvsp[-1].val);
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-4].val);
			}
#line 10345 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 668:
#line 3850 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;
				struct error_record *erec;
				uint64_t rate, unit;

				erec = rate_parse(&(yyloc), (yyvsp[-1].string), &rate, &unit);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				limit = &(yyvsp[-5].obj)->limit;
				limit->rate	= rate * (yyvsp[-2].val);
				limit->unit	= unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKT_BYTES;
				limit->flags	= (yyvsp[-3].val);
			}
#line 10368 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 669:
#line 3871 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 10377 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 670:
#line 3878 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 10385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 671:
#line 3882 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 10393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 672:
#line 3886 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10401 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 673:
#line 3892 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10411 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 674:
#line 3898 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10421 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 675:
#line 3905 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10427 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 676:
#line 3906 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 677:
#line 3907 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10439 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 678:
#line 3908 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10445 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 680:
#line 3913 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 681:
#line 3917 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10461 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 683:
#line 3924 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10469 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 685:
#line 3931 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10477 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 687:
#line 3938 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 690:
#line 3948 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyval.expr)->etype != EXPR_CONCAT) {
					(yyval.expr) = concat_expr_alloc(&(yyloc));
					compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				} else {
					struct location rhs[] = {
						[1]	= (yylsp[-1]),
						[2]	= (yylsp[0]),
					};
					location_update(&(yyvsp[0].expr)->location, rhs, 2);

					(yyval.expr) = (yyvsp[-2].expr);
					(yyval.expr)->location = (yyloc);
				}
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10506 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 691:
#line 3966 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = true; }
#line 10512 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 692:
#line 3967 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = false; }
#line 10518 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 693:
#line 3971 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 10528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 694:
#line 3978 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 10534 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 695:
#line 3979 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 10540 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 696:
#line 3980 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 10546 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 697:
#line 3981 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 10552 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 698:
#line 3982 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 10558 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 699:
#line 3983 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 10564 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 700:
#line 3984 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 10570 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 701:
#line 3985 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 10576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 702:
#line 3986 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 10582 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 703:
#line 3987 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 10588 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 704:
#line 3988 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 10594 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 705:
#line 3989 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 10600 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 706:
#line 3992 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10606 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 707:
#line 3993 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10612 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 708:
#line 3994 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10618 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 709:
#line 3995 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 710:
#line 3997 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10635 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 711:
#line 4004 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10646 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 712:
#line 4011 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10657 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 713:
#line 4018 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10668 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 714:
#line 4025 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10679 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 715:
#line 4032 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10690 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 716:
#line 4039 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10701 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 717:
#line 4046 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 718:
#line 4053 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10723 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 719:
#line 4060 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10734 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 720:
#line 4067 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10745 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 721:
#line 4074 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10756 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 722:
#line 4080 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 10762 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 723:
#line 4083 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_EQ; }
#line 10768 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 724:
#line 4084 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_NEQ; }
#line 10774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 725:
#line 4085 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LT; }
#line 10780 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 726:
#line 4086 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GT; }
#line 10786 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 727:
#line 4087 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GTE; }
#line 10792 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 728:
#line 4088 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LTE; }
#line 10798 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 729:
#line 4092 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 10806 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 730:
#line 4096 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 10814 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 731:
#line 4100 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 10822 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 732:
#line 4104 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 10830 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 733:
#line 4108 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 10838 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 734:
#line 4112 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 10846 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 736:
#line 4119 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 737:
#line 4129 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 10866 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 738:
#line 4133 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 10874 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 739:
#line 4137 "parser_bison.y" /* yacc.c:1652  */
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
#line 10892 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 742:
#line 4156 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_LEN; }
#line 10898 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 743:
#line 4157 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 10904 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 744:
#line 4158 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 10910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 745:
#line 4159 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 10916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 746:
#line 4160 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECMARK; }
#line 10922 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 747:
#line 4163 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_MARK; }
#line 10928 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 748:
#line 4164 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIF; }
#line 10934 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 749:
#line 4165 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 10940 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 750:
#line 4166 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 10946 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 751:
#line 4167 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIF; }
#line 10952 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 752:
#line 4168 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 10958 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 753:
#line 4169 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 10964 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 754:
#line 4170 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKUID; }
#line 10970 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 755:
#line 4171 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKGID; }
#line 10976 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 756:
#line 4172 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 10982 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 757:
#line 4173 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 10988 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 758:
#line 4174 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 10994 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 759:
#line 4175 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 11000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 760:
#line 4176 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 11006 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 761:
#line 4177 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 11012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 762:
#line 4178 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 11018 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 763:
#line 4179 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CPU; }
#line 11024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 764:
#line 4180 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 11030 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 765:
#line 4181 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 11036 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 766:
#line 4182 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 11042 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 767:
#line 4183 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECPATH; }
#line 11048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 768:
#line 4184 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_NS; }
#line 11054 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 769:
#line 4185 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_DAY; }
#line 11060 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 770:
#line 4186 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_HOUR; }
#line 11066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 771:
#line 4190 "parser_bison.y" /* yacc.c:1652  */
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
#line 11090 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 772:
#line 4210 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 11098 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 773:
#line 4214 "parser_bison.y" /* yacc.c:1652  */
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
#line 11116 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 774:
#line 4228 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 11124 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 775:
#line 4232 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 11132 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 776:
#line 4236 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 11140 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 777:
#line 4242 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11148 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 778:
#line 4247 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 11154 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 779:
#line 4248 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_MARK; }
#line 11160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 780:
#line 4251 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 11166 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 781:
#line 4252 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 11172 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 782:
#line 4255 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 11178 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 783:
#line 4256 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 11184 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 784:
#line 4260 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 11192 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 785:
#line 4265 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 11198 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 786:
#line 4266 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 11204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 787:
#line 4269 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_IN; }
#line 11210 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 788:
#line 4270 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_OUT; }
#line 11216 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 789:
#line 4273 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 11222 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 790:
#line 4274 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 11228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 791:
#line 4277 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 11234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 792:
#line 4278 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 11240 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 793:
#line 4282 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-1].val) > 255) {
					erec_queue(error(&(yylsp[-1]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 11252 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 794:
#line 4290 "parser_bison.y" /* yacc.c:1652  */
    {
				enum nft_xfrm_keys xfrmk = (yyvsp[0].val);

				switch ((yyvsp[-1].val)) {
				case NFPROTO_IPV4:
					break;
				case NFPROTO_IPV6:
					if ((yyvsp[0].val) == NFT_XFRM_KEY_SADDR_IP4)
						xfrmk = NFT_XFRM_KEY_SADDR_IP6;
					else if ((yyvsp[0].val) == NFT_XFRM_KEY_DADDR_IP4)
						xfrmk = NFT_XFRM_KEY_DADDR_IP6;
					break;
				default:
					YYERROR;
					break;
				}

				if ((yyvsp[-2].val) > 255) {
					erec_queue(error(&(yylsp[-2]), "value too large"), state->msgs);
					YYERROR;
				}

				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-2].val), xfrmk);
			}
#line 11281 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 795:
#line 4317 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 11290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 796:
#line 4322 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 11299 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 797:
#line 4327 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 11307 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 798:
#line 4332 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 11313 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 799:
#line 4333 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 11319 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 800:
#line 4337 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 11327 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 801:
#line 4341 "parser_bison.y" /* yacc.c:1652  */
    {
				enum nft_rt_keys rtk = (yyvsp[0].val);

				switch ((yyvsp[-1].val)) {
				case NFPROTO_IPV4:
					break;
				case NFPROTO_IPV6:
					if ((yyvsp[0].val) == NFT_RT_NEXTHOP4)
						rtk = NFT_RT_NEXTHOP6;
					break;
				default:
					YYERROR;
					break;
				}

				(yyval.expr) = rt_expr_alloc(&(yyloc), rtk, false);
			}
#line 11349 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 802:
#line 4360 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 11355 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 803:
#line 4361 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 11361 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 804:
#line 4362 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 11367 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 805:
#line 4363 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_XFRM; }
#line 11373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 806:
#line 4367 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1);
			}
#line 11381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 807:
#line 4371 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 11389 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 808:
#line 4375 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 11397 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 809:
#line 4380 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 11403 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 810:
#line 4381 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 11409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 811:
#line 4384 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 11415 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 812:
#line 4385 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 11421 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 813:
#line 4386 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_MARK; }
#line 11427 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 814:
#line 4387 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATE; }
#line 11433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 815:
#line 4388 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 11439 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 816:
#line 4389 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 11445 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 817:
#line 4390 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 11451 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 818:
#line 4391 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 11457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 819:
#line 4392 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 11463 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 820:
#line 4393 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 11469 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 821:
#line 4394 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 11475 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 822:
#line 4395 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 11481 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 823:
#line 4396 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 11487 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 824:
#line 4397 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 11493 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 825:
#line 4398 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SECMARK; }
#line 11499 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 827:
#line 4402 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 11505 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 828:
#line 4403 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 11511 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 829:
#line 4404 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 11517 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 830:
#line 4405 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 11523 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 831:
#line 4406 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 11529 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 832:
#line 4407 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 11535 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 834:
#line 4411 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP; }
#line 11541 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 835:
#line 4412 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP; }
#line 11547 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 836:
#line 4413 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP6; }
#line 11553 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 837:
#line 4414 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP6; }
#line 11559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 838:
#line 4417 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 11565 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 839:
#line 4418 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 11571 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 840:
#line 4419 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 11577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 841:
#line 4420 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 11583 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 844:
#line 4428 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11593 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 845:
#line 4434 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 846:
#line 4442 "parser_bison.y" /* yacc.c:1652  */
    {
				switch ((yyvsp[-2].val)) {
				case NFT_CT_HELPER:
					(yyval.stmt) = objref_stmt_alloc(&(yyloc));
					(yyval.stmt)->objref.type = NFT_OBJECT_CT_HELPER;
					(yyval.stmt)->objref.expr = (yyvsp[0].expr);
					break;
				default:
					(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), -1, (yyvsp[0].expr));
					break;
				}
			}
#line 11620 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 847:
#line 4455 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);

			}
#line 11631 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 848:
#line 4462 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 11641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 849:
#line 4468 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 11649 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 850:
#line 4474 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11660 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 869:
#line 4503 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 11671 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 870:
#line 4511 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 11677 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 871:
#line 4512 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 11683 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 872:
#line 4513 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 11689 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 873:
#line 4517 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 11697 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 874:
#line 4522 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 11703 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 875:
#line 4523 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 11709 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 876:
#line 4524 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 11715 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 877:
#line 4528 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 11723 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 878:
#line 4533 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_VID; }
#line 11729 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 879:
#line 4534 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_CFI; }
#line 11735 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 880:
#line 4535 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_PCP; }
#line 11741 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 881:
#line 4536 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 11747 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 882:
#line 4540 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 11755 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 883:
#line 4545 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HRD; }
#line 11761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 884:
#line 4546 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PRO; }
#line 11767 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 885:
#line 4547 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HLN; }
#line 11773 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 886:
#line 4548 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PLN; }
#line 11779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 887:
#line 4549 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_OP; }
#line 11785 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 888:
#line 4550 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 11791 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 889:
#line 4551 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 11797 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 890:
#line 4552 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_IP; }
#line 11803 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 891:
#line 4553 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_IP; }
#line 11809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 892:
#line 4557 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 11817 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 893:
#line 4561 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val), 0);
			}
#line 11825 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 894:
#line 4565 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[0].val), IPOPT_FIELD_TYPE, 0);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 11834 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 895:
#line 4571 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_VERSION; }
#line 11840 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 896:
#line 4572 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 11846 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 897:
#line 4573 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DSCP; }
#line 11852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 898:
#line 4574 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ECN; }
#line 11858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 899:
#line 4575 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 11864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 900:
#line 4576 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ID; }
#line 11870 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 901:
#line 4577 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 11876 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 902:
#line 4578 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_TTL; }
#line 11882 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 903:
#line 4579 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 11888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 904:
#line 4580 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 11894 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 905:
#line 4581 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_SADDR; }
#line 11900 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 906:
#line 4582 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DADDR; }
#line 11906 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 907:
#line 4585 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_LSRR; }
#line 11912 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 908:
#line 4586 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RR; }
#line 11918 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 909:
#line 4587 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_SSRR; }
#line 11924 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 910:
#line 4588 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RA; }
#line 11930 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 911:
#line 4591 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 11936 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 912:
#line 4592 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 11942 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 913:
#line 4593 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 11948 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 914:
#line 4594 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_PTR; }
#line 11954 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 915:
#line 4595 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 11960 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 916:
#line 4599 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 11968 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 917:
#line 4604 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 11974 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 918:
#line 4605 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 11980 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 919:
#line 4606 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 11986 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 920:
#line 4607 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_ID; }
#line 11992 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 921:
#line 4608 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 11998 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 922:
#line 4609 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 12004 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 923:
#line 4610 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 12010 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 924:
#line 4614 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[0].val));
			}
#line 12018 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 925:
#line 4619 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_TYPE; }
#line 12024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 926:
#line 4620 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 12030 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 927:
#line 4621 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_MRT; }
#line 12036 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 928:
#line 4622 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_GROUP; }
#line 12042 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 929:
#line 4626 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 12050 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 930:
#line 4631 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 12056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 931:
#line 4632 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 12062 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 932:
#line 4633 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_ECN; }
#line 12068 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 933:
#line 4634 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 12074 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 934:
#line 4635 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 12080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 935:
#line 4636 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 12086 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 936:
#line 4637 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 12092 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 937:
#line 4638 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 12098 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 938:
#line 4639 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 12104 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 939:
#line 4642 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 12112 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 940:
#line 4647 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 12118 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 941:
#line 4648 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 12124 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 942:
#line 4649 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 12130 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 943:
#line 4650 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 12136 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 944:
#line 4651 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 12142 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 945:
#line 4652 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 12148 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 946:
#line 4653 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 12154 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 947:
#line 4654 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 12160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 948:
#line 4658 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 12168 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 949:
#line 4663 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 12174 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 950:
#line 4664 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 12180 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 951:
#line 4665 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 12186 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 952:
#line 4666 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SPI; }
#line 12192 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 953:
#line 4667 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 12198 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 954:
#line 4671 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 12206 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 955:
#line 4676 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SPI; }
#line 12212 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 956:
#line 4677 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 12218 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 957:
#line 4681 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 12226 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 958:
#line 4686 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 12232 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 959:
#line 4687 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 12238 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 960:
#line 4688 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_CPI; }
#line 12244 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 961:
#line 4692 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 12252 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 962:
#line 4697 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 12258 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 963:
#line 4698 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 12264 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 964:
#line 4699 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 12270 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 965:
#line 4700 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 12276 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 966:
#line 4704 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 12284 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 967:
#line 4709 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 12290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 968:
#line 4710 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 12296 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 969:
#line 4711 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 12302 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 970:
#line 4712 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 12308 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 971:
#line 4716 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 12316 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 972:
#line 4720 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 12324 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 973:
#line 4724 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 12333 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 974:
#line 4730 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 12339 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 975:
#line 4731 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 12345 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 976:
#line 4732 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 12351 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 977:
#line 4733 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 12357 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 978:
#line 4734 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 12363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 979:
#line 4735 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 12369 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 980:
#line 4736 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 12375 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 981:
#line 4737 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 12381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 982:
#line 4738 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 12387 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 983:
#line 4739 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 12393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 984:
#line 4742 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 12399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 985:
#line 4743 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 12405 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 986:
#line 4744 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 12411 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 987:
#line 4745 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 12417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 988:
#line 4746 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 12423 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 989:
#line 4747 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 12429 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 990:
#line 4748 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 12435 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 991:
#line 4749 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 12441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 992:
#line 4750 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 12447 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 993:
#line 4751 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 12453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 994:
#line 4752 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 12459 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 995:
#line 4753 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 12465 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 996:
#line 4756 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 12471 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 997:
#line 4757 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 12477 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 998:
#line 4758 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 12483 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 999:
#line 4759 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 12489 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1000:
#line 4760 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 12495 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1001:
#line 4761 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 12501 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1002:
#line 4762 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 12507 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1003:
#line 4763 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 12513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1004:
#line 4767 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 12521 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1005:
#line 4772 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 12527 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1006:
#line 4773 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 12533 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1007:
#line 4774 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 12539 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1008:
#line 4778 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 12547 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1009:
#line 4783 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 12553 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1010:
#line 4784 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 12559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1011:
#line 4785 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 12565 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1012:
#line 4786 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 12571 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1013:
#line 4790 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[0].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 12581 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1014:
#line 4797 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_SPORT; }
#line 12587 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1015:
#line 4798 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_DPORT; }
#line 12593 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1024:
#line 4812 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 12601 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1025:
#line 4817 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 12607 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1026:
#line 4818 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 12613 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1027:
#line 4822 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 12621 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1028:
#line 4827 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 12627 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1029:
#line 4828 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 12633 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1030:
#line 4829 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_TYPE; }
#line 12639 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1031:
#line 4830 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 12645 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1032:
#line 4834 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 12653 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1033:
#line 4840 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 12661 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1034:
#line 4846 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 12669 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1035:
#line 4851 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 12675 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1036:
#line 4855 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 12683 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1037:
#line 4860 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 12689 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1038:
#line 4861 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 12695 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1039:
#line 4862 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_TAG; }
#line 12701 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1040:
#line 4864 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 12709 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1041:
#line 4870 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 12717 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1042:
#line 4875 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 12723 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1043:
#line 4876 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 12729 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1044:
#line 4877 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 12735 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1045:
#line 4878 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 12741 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1046:
#line 4879 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 12747 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1047:
#line 4880 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_ID; }
#line 12753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1048:
#line 4884 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 12761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1049:
#line 4889 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 12767 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1050:
#line 4890 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 12773 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1051:
#line 4894 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 12781 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1052:
#line 4899 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 12787 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1053:
#line 4900 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 12793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1054:
#line 4901 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_TYPE; }
#line 12799 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1055:
#line 4902 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 12805 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1056:
#line 4903 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 12811 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1057:
#line 4907 "parser_bison.y" /* yacc.c:1652  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 12827 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1058:
#line 4920 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 12833 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1059:
#line 4921 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 12839 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1060:
#line 4922 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 12845 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1061:
#line 4923 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 12851 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1062:
#line 4924 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_MH; }
#line 12857 "parser_bison.c" /* yacc.c:1652  */
    break;


#line 12861 "parser_bison.c" /* yacc.c:1652  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, nft, scanner, state, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, nft, scanner, state, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, yylsp, nft, scanner, state);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, nft, scanner, state, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[*yyssp], yyvsp, yylsp, nft, scanner, state);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 4927 "parser_bison.y" /* yacc.c:1918  */

