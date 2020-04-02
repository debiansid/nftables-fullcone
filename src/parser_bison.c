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

#define YYLLOC_DEFAULT(Current, Rhs, N)	location_update(&Current, Rhs, N)

#define symbol_value(loc, str) \
	symbol_expr_alloc(loc, SYMBOL_VALUE, current_scope(state), str)

/* Declare those here to avoid compiler warnings */
void nft_set_debug(int, void *);
int nft_lex(void *, void *, void *);

#line 199 "parser_bison.c" /* yacc.c:337  */
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
    TYPEOF = 294,
    HOOK = 295,
    DEVICE = 296,
    DEVICES = 297,
    TABLE = 298,
    TABLES = 299,
    CHAIN = 300,
    CHAINS = 301,
    RULE = 302,
    RULES = 303,
    SETS = 304,
    SET = 305,
    ELEMENT = 306,
    MAP = 307,
    MAPS = 308,
    FLOWTABLE = 309,
    HANDLE = 310,
    RULESET = 311,
    TRACE = 312,
    INET = 313,
    NETDEV = 314,
    ADD = 315,
    UPDATE = 316,
    REPLACE = 317,
    CREATE = 318,
    INSERT = 319,
    DELETE = 320,
    GET = 321,
    LIST = 322,
    RESET = 323,
    FLUSH = 324,
    RENAME = 325,
    DESCRIBE = 326,
    IMPORT = 327,
    EXPORT = 328,
    MONITOR = 329,
    ALL = 330,
    ACCEPT = 331,
    DROP = 332,
    CONTINUE = 333,
    JUMP = 334,
    GOTO = 335,
    RETURN = 336,
    TO = 337,
    CONSTANT = 338,
    INTERVAL = 339,
    DYNAMIC = 340,
    AUTOMERGE = 341,
    TIMEOUT = 342,
    GC_INTERVAL = 343,
    ELEMENTS = 344,
    EXPIRES = 345,
    POLICY = 346,
    MEMORY = 347,
    PERFORMANCE = 348,
    SIZE = 349,
    FLOW = 350,
    OFFLOAD = 351,
    METER = 352,
    METERS = 353,
    FLOWTABLES = 354,
    NUM = 355,
    STRING = 356,
    QUOTED_STRING = 357,
    ASTERISK_STRING = 358,
    LL_HDR = 359,
    NETWORK_HDR = 360,
    TRANSPORT_HDR = 361,
    BRIDGE = 362,
    ETHER = 363,
    SADDR = 364,
    DADDR = 365,
    TYPE = 366,
    VLAN = 367,
    ID = 368,
    CFI = 369,
    PCP = 370,
    ARP = 371,
    HTYPE = 372,
    PTYPE = 373,
    HLEN = 374,
    PLEN = 375,
    OPERATION = 376,
    IP = 377,
    HDRVERSION = 378,
    HDRLENGTH = 379,
    DSCP = 380,
    ECN = 381,
    LENGTH = 382,
    FRAG_OFF = 383,
    TTL = 384,
    PROTOCOL = 385,
    CHECKSUM = 386,
    PTR = 387,
    VALUE = 388,
    LSRR = 389,
    RR = 390,
    SSRR = 391,
    RA = 392,
    ICMP = 393,
    CODE = 394,
    SEQUENCE = 395,
    GATEWAY = 396,
    MTU = 397,
    IGMP = 398,
    MRT = 399,
    OPTIONS = 400,
    IP6 = 401,
    PRIORITY = 402,
    FLOWLABEL = 403,
    NEXTHDR = 404,
    HOPLIMIT = 405,
    ICMP6 = 406,
    PPTR = 407,
    MAXDELAY = 408,
    AH = 409,
    RESERVED = 410,
    SPI = 411,
    ESP = 412,
    COMP = 413,
    FLAGS = 414,
    CPI = 415,
    PORT = 416,
    UDP = 417,
    SPORT = 418,
    DPORT = 419,
    UDPLITE = 420,
    CSUMCOV = 421,
    TCP = 422,
    ACKSEQ = 423,
    DOFF = 424,
    WINDOW = 425,
    URGPTR = 426,
    OPTION = 427,
    ECHO = 428,
    EOL = 429,
    MAXSEG = 430,
    NOOP = 431,
    SACK = 432,
    SACK0 = 433,
    SACK1 = 434,
    SACK2 = 435,
    SACK3 = 436,
    SACK_PERMITTED = 437,
    TIMESTAMP = 438,
    KIND = 439,
    COUNT = 440,
    LEFT = 441,
    RIGHT = 442,
    TSVAL = 443,
    TSECR = 444,
    DCCP = 445,
    SCTP = 446,
    VTAG = 447,
    RT = 448,
    RT0 = 449,
    RT2 = 450,
    RT4 = 451,
    SEG_LEFT = 452,
    ADDR = 453,
    LAST_ENT = 454,
    TAG = 455,
    SID = 456,
    HBH = 457,
    FRAG = 458,
    RESERVED2 = 459,
    MORE_FRAGMENTS = 460,
    DST = 461,
    MH = 462,
    META = 463,
    MARK = 464,
    IIF = 465,
    IIFNAME = 466,
    IIFTYPE = 467,
    OIF = 468,
    OIFNAME = 469,
    OIFTYPE = 470,
    SKUID = 471,
    SKGID = 472,
    NFTRACE = 473,
    RTCLASSID = 474,
    IBRIPORT = 475,
    OBRIPORT = 476,
    IBRIDGENAME = 477,
    OBRIDGENAME = 478,
    PKTTYPE = 479,
    CPU = 480,
    IIFGROUP = 481,
    OIFGROUP = 482,
    CGROUP = 483,
    TIME = 484,
    CLASSID = 485,
    NEXTHOP = 486,
    CT = 487,
    L3PROTOCOL = 488,
    PROTO_SRC = 489,
    PROTO_DST = 490,
    ZONE = 491,
    DIRECTION = 492,
    EVENT = 493,
    EXPECTATION = 494,
    EXPIRATION = 495,
    HELPER = 496,
    LABEL = 497,
    STATE = 498,
    STATUS = 499,
    ORIGINAL = 500,
    REPLY = 501,
    COUNTER = 502,
    NAME = 503,
    PACKETS = 504,
    BYTES = 505,
    AVGPKT = 506,
    COUNTERS = 507,
    QUOTAS = 508,
    LIMITS = 509,
    SYNPROXYS = 510,
    HELPERS = 511,
    LOG = 512,
    PREFIX = 513,
    GROUP = 514,
    SNAPLEN = 515,
    QUEUE_THRESHOLD = 516,
    LEVEL = 517,
    LIMIT = 518,
    RATE = 519,
    BURST = 520,
    OVER = 521,
    UNTIL = 522,
    QUOTA = 523,
    USED = 524,
    SECMARK = 525,
    SECMARKS = 526,
    NANOSECOND = 527,
    MICROSECOND = 528,
    MILLISECOND = 529,
    SECOND = 530,
    MINUTE = 531,
    HOUR = 532,
    DAY = 533,
    WEEK = 534,
    _REJECT = 535,
    WITH = 536,
    ICMPX = 537,
    SNAT = 538,
    DNAT = 539,
    MASQUERADE = 540,
    REDIRECT = 541,
    RANDOM = 542,
    FULLY_RANDOM = 543,
    PERSISTENT = 544,
    QUEUE = 545,
    QUEUENUM = 546,
    BYPASS = 547,
    FANOUT = 548,
    DUP = 549,
    FWD = 550,
    NUMGEN = 551,
    INC = 552,
    MOD = 553,
    OFFSET = 554,
    JHASH = 555,
    SYMHASH = 556,
    SEED = 557,
    POSITION = 558,
    INDEX = 559,
    COMMENT = 560,
    XML = 561,
    JSON = 562,
    VM = 563,
    NOTRACK = 564,
    EXISTS = 565,
    MISSING = 566,
    EXTHDR = 567,
    IPSEC = 568,
    MODE = 569,
    REQID = 570,
    SPNUM = 571,
    TRANSPORT = 572,
    TUNNEL = 573,
    IN = 574,
    OUT = 575
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
#define TYPEOF 294
#define HOOK 295
#define DEVICE 296
#define DEVICES 297
#define TABLE 298
#define TABLES 299
#define CHAIN 300
#define CHAINS 301
#define RULE 302
#define RULES 303
#define SETS 304
#define SET 305
#define ELEMENT 306
#define MAP 307
#define MAPS 308
#define FLOWTABLE 309
#define HANDLE 310
#define RULESET 311
#define TRACE 312
#define INET 313
#define NETDEV 314
#define ADD 315
#define UPDATE 316
#define REPLACE 317
#define CREATE 318
#define INSERT 319
#define DELETE 320
#define GET 321
#define LIST 322
#define RESET 323
#define FLUSH 324
#define RENAME 325
#define DESCRIBE 326
#define IMPORT 327
#define EXPORT 328
#define MONITOR 329
#define ALL 330
#define ACCEPT 331
#define DROP 332
#define CONTINUE 333
#define JUMP 334
#define GOTO 335
#define RETURN 336
#define TO 337
#define CONSTANT 338
#define INTERVAL 339
#define DYNAMIC 340
#define AUTOMERGE 341
#define TIMEOUT 342
#define GC_INTERVAL 343
#define ELEMENTS 344
#define EXPIRES 345
#define POLICY 346
#define MEMORY 347
#define PERFORMANCE 348
#define SIZE 349
#define FLOW 350
#define OFFLOAD 351
#define METER 352
#define METERS 353
#define FLOWTABLES 354
#define NUM 355
#define STRING 356
#define QUOTED_STRING 357
#define ASTERISK_STRING 358
#define LL_HDR 359
#define NETWORK_HDR 360
#define TRANSPORT_HDR 361
#define BRIDGE 362
#define ETHER 363
#define SADDR 364
#define DADDR 365
#define TYPE 366
#define VLAN 367
#define ID 368
#define CFI 369
#define PCP 370
#define ARP 371
#define HTYPE 372
#define PTYPE 373
#define HLEN 374
#define PLEN 375
#define OPERATION 376
#define IP 377
#define HDRVERSION 378
#define HDRLENGTH 379
#define DSCP 380
#define ECN 381
#define LENGTH 382
#define FRAG_OFF 383
#define TTL 384
#define PROTOCOL 385
#define CHECKSUM 386
#define PTR 387
#define VALUE 388
#define LSRR 389
#define RR 390
#define SSRR 391
#define RA 392
#define ICMP 393
#define CODE 394
#define SEQUENCE 395
#define GATEWAY 396
#define MTU 397
#define IGMP 398
#define MRT 399
#define OPTIONS 400
#define IP6 401
#define PRIORITY 402
#define FLOWLABEL 403
#define NEXTHDR 404
#define HOPLIMIT 405
#define ICMP6 406
#define PPTR 407
#define MAXDELAY 408
#define AH 409
#define RESERVED 410
#define SPI 411
#define ESP 412
#define COMP 413
#define FLAGS 414
#define CPI 415
#define PORT 416
#define UDP 417
#define SPORT 418
#define DPORT 419
#define UDPLITE 420
#define CSUMCOV 421
#define TCP 422
#define ACKSEQ 423
#define DOFF 424
#define WINDOW 425
#define URGPTR 426
#define OPTION 427
#define ECHO 428
#define EOL 429
#define MAXSEG 430
#define NOOP 431
#define SACK 432
#define SACK0 433
#define SACK1 434
#define SACK2 435
#define SACK3 436
#define SACK_PERMITTED 437
#define TIMESTAMP 438
#define KIND 439
#define COUNT 440
#define LEFT 441
#define RIGHT 442
#define TSVAL 443
#define TSECR 444
#define DCCP 445
#define SCTP 446
#define VTAG 447
#define RT 448
#define RT0 449
#define RT2 450
#define RT4 451
#define SEG_LEFT 452
#define ADDR 453
#define LAST_ENT 454
#define TAG 455
#define SID 456
#define HBH 457
#define FRAG 458
#define RESERVED2 459
#define MORE_FRAGMENTS 460
#define DST 461
#define MH 462
#define META 463
#define MARK 464
#define IIF 465
#define IIFNAME 466
#define IIFTYPE 467
#define OIF 468
#define OIFNAME 469
#define OIFTYPE 470
#define SKUID 471
#define SKGID 472
#define NFTRACE 473
#define RTCLASSID 474
#define IBRIPORT 475
#define OBRIPORT 476
#define IBRIDGENAME 477
#define OBRIDGENAME 478
#define PKTTYPE 479
#define CPU 480
#define IIFGROUP 481
#define OIFGROUP 482
#define CGROUP 483
#define TIME 484
#define CLASSID 485
#define NEXTHOP 486
#define CT 487
#define L3PROTOCOL 488
#define PROTO_SRC 489
#define PROTO_DST 490
#define ZONE 491
#define DIRECTION 492
#define EVENT 493
#define EXPECTATION 494
#define EXPIRATION 495
#define HELPER 496
#define LABEL 497
#define STATE 498
#define STATUS 499
#define ORIGINAL 500
#define REPLY 501
#define COUNTER 502
#define NAME 503
#define PACKETS 504
#define BYTES 505
#define AVGPKT 506
#define COUNTERS 507
#define QUOTAS 508
#define LIMITS 509
#define SYNPROXYS 510
#define HELPERS 511
#define LOG 512
#define PREFIX 513
#define GROUP 514
#define SNAPLEN 515
#define QUEUE_THRESHOLD 516
#define LEVEL 517
#define LIMIT 518
#define RATE 519
#define BURST 520
#define OVER 521
#define UNTIL 522
#define QUOTA 523
#define USED 524
#define SECMARK 525
#define SECMARKS 526
#define NANOSECOND 527
#define MICROSECOND 528
#define MILLISECOND 529
#define SECOND 530
#define MINUTE 531
#define HOUR 532
#define DAY 533
#define WEEK 534
#define _REJECT 535
#define WITH 536
#define ICMPX 537
#define SNAT 538
#define DNAT 539
#define MASQUERADE 540
#define REDIRECT 541
#define RANDOM 542
#define FULLY_RANDOM 543
#define PERSISTENT 544
#define QUEUE 545
#define QUEUENUM 546
#define BYPASS 547
#define FANOUT 548
#define DUP 549
#define FWD 550
#define NUMGEN 551
#define INC 552
#define MOD 553
#define OFFSET 554
#define JHASH 555
#define SYMHASH 556
#define SEED 557
#define POSITION 558
#define INDEX 559
#define COMMENT 560
#define XML 561
#define JSON 562
#define VM 563
#define NOTRACK 564
#define EXISTS 565
#define MISSING 566
#define EXTHDR 567
#define IPSEC 568
#define MODE 569
#define REQID 570
#define SPNUM 571
#define TRANSPORT 572
#define TUNNEL 573
#define IN 574
#define OUT 575

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 154 "parser_bison.y" /* yacc.c:352  */

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

#line 909 "parser_bison.c" /* yacc.c:352  */
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
#define YYLAST   6466

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  330
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  339
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1080
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1755

#define YYUNDEFTOK  2
#define YYMAXUTOK   575

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
       2,     2,     2,     2,     2,     2,   327,     2,     2,     2,
     324,   325,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   321,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   328,     2,   329,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   322,   326,   323,     2,     2,     2,     2,
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
     315,   316,   317,   318,   319,   320
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   830,   830,   831,   840,   841,   844,   845,   848,   856,
     870,   877,   888,   896,   897,   898,   899,   919,   920,   921,
     922,   923,   924,   925,   926,   927,   928,   929,   930,   931,
     932,   933,   936,   940,   947,   951,   959,   963,   967,   974,
     981,   985,   992,  1001,  1005,  1009,  1013,  1017,  1021,  1025,
    1029,  1035,  1041,  1045,  1052,  1056,  1064,  1071,  1078,  1082,
    1089,  1098,  1102,  1106,  1110,  1114,  1118,  1122,  1126,  1132,
    1138,  1142,  1146,  1150,  1154,  1158,  1162,  1166,  1170,  1174,
    1178,  1182,  1186,  1190,  1194,  1198,  1202,  1206,  1210,  1214,
    1218,  1222,  1228,  1234,  1238,  1242,  1246,  1250,  1254,  1258,
    1262,  1266,  1270,  1274,  1278,  1282,  1286,  1290,  1294,  1298,
    1302,  1306,  1310,  1314,  1318,  1322,  1326,  1330,  1334,  1338,
    1342,  1346,  1350,  1354,  1358,  1362,  1366,  1370,  1376,  1380,
    1384,  1388,  1392,  1396,  1402,  1406,  1410,  1414,  1418,  1422,
    1426,  1432,  1439,  1445,  1453,  1459,  1467,  1476,  1477,  1480,
    1481,  1482,  1483,  1484,  1485,  1486,  1487,  1490,  1491,  1494,
    1495,  1496,  1499,  1508,  1514,  1528,  1529,  1530,  1531,  1532,
    1543,  1553,  1564,  1574,  1585,  1596,  1605,  1614,  1623,  1634,
    1645,  1659,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1678,
    1689,  1702,  1707,  1708,  1709,  1710,  1715,  1721,  1726,  1731,
    1736,  1741,  1746,  1751,  1754,  1755,  1758,  1762,  1765,  1766,
    1767,  1768,  1772,  1777,  1778,  1779,  1780,  1785,  1795,  1806,
    1815,  1824,  1833,  1842,  1847,  1852,  1855,  1859,  1865,  1866,
    1870,  1875,  1876,  1877,  1878,  1892,  1896,  1902,  1909,  1914,
    1919,  1922,  1931,  1943,  1950,  1951,  1963,  1968,  1969,  1970,
    1971,  1977,  1978,  1979,  1980,  1986,  1987,  1988,  1989,  1995,
    1996,  1997,  1998,  2004,  2005,  2006,  2007,  2013,  2014,  2015,
    2016,  2022,  2023,  2024,  2025,  2031,  2032,  2033,  2034,  2040,
    2041,  2042,  2043,  2044,  2047,  2077,  2084,  2088,  2091,  2101,
    2109,  2120,  2133,  2147,  2148,  2151,  2163,  2167,  2170,  2176,
    2189,  2194,  2203,  2204,  2207,  2210,  2211,  2212,  2215,  2230,
    2231,  2234,  2235,  2236,  2237,  2238,  2239,  2242,  2251,  2260,
    2268,  2276,  2284,  2292,  2300,  2308,  2316,  2324,  2332,  2340,
    2348,  2356,  2364,  2372,  2380,  2384,  2389,  2397,  2404,  2411,
    2424,  2428,  2435,  2439,  2445,  2457,  2463,  2470,  2471,  2472,
    2473,  2476,  2477,  2478,  2479,  2480,  2481,  2482,  2483,  2484,
    2485,  2486,  2487,  2488,  2489,  2490,  2491,  2492,  2493,  2494,
    2497,  2501,  2507,  2513,  2518,  2521,  2526,  2531,  2534,  2540,
    2545,  2553,  2554,  2556,  2560,  2568,  2572,  2575,  2579,  2585,
    2586,  2589,  2595,  2599,  2602,  2607,  2612,  2617,  2622,  2627,
    2633,  2663,  2667,  2671,  2675,  2679,  2685,  2689,  2692,  2696,
    2702,  2711,  2730,  2738,  2739,  2740,  2743,  2744,  2747,  2748,
    2763,  2779,  2787,  2788,  2789,  2792,  2793,  2796,  2797,  2798,
    2813,  2814,  2815,  2816,  2817,  2820,  2823,  2830,  2834,  2845,
    2856,  2866,  2872,  2875,  2876,  2879,  2885,  2891,  2897,  2904,
    2911,  2919,  2920,  2923,  2927,  2935,  2939,  2942,  2947,  2952,
    2956,  2962,  2978,  2997,  3003,  3004,  3010,  3011,  3017,  3018,
    3019,  3020,  3021,  3022,  3023,  3024,  3025,  3026,  3027,  3028,
    3029,  3032,  3033,  3037,  3043,  3044,  3050,  3051,  3057,  3058,
    3064,  3067,  3068,  3079,  3080,  3083,  3087,  3090,  3096,  3102,
    3113,  3114,  3115,  3118,  3119,  3120,  3123,  3127,  3131,  3136,
    3141,  3146,  3152,  3156,  3160,  3164,  3172,  3173,  3176,  3179,
    3183,  3188,  3194,  3195,  3198,  3201,  3205,  3209,  3213,  3218,
    3225,  3230,  3238,  3243,  3252,  3253,  3259,  3260,  3261,  3264,
    3265,  3268,  3274,  3278,  3281,  3286,  3292,  3293,  3299,  3300,
    3303,  3304,  3307,  3313,  3320,  3327,  3337,  3338,  3339,  3342,
    3350,  3361,  3368,  3371,  3377,  3381,  3384,  3390,  3399,  3410,
    3416,  3442,  3443,  3452,  3453,  3456,  3465,  3476,  3477,  3478,
    3479,  3480,  3481,  3482,  3483,  3484,  3485,  3486,  3487,  3488,
    3489,  3490,  3493,  3516,  3517,  3518,  3521,  3522,  3523,  3524,
    3525,  3528,  3532,  3535,  3539,  3546,  3549,  3563,  3564,  3568,
    3574,  3575,  3581,  3582,  3588,  3589,  3595,  3598,  3599,  3610,
    3616,  3622,  3623,  3626,  3632,  3633,  3634,  3637,  3644,  3649,
    3654,  3657,  3661,  3665,  3671,  3672,  3679,  3685,  3686,  3689,
    3695,  3699,  3702,  3706,  3710,  3716,  3720,  3723,  3727,  3731,
    3735,  3744,  3750,  3751,  3754,  3755,  3758,  3759,  3762,  3773,
    3779,  3800,  3806,  3823,  3829,  3830,  3831,  3834,  3835,  3838,
    3853,  3859,  3865,  3872,  3886,  3894,  3902,  3908,  3912,  3916,
    3920,  3924,  3931,  3936,  3947,  3969,  3975,  3979,  3983,  3989,
    3995,  4003,  4004,  4005,  4006,  4009,  4010,  4014,  4020,  4021,
    4027,  4028,  4034,  4035,  4041,  4044,  4045,  4046,  4055,  4066,
    4067,  4070,  4078,  4079,  4080,  4081,  4082,  4083,  4084,  4085,
    4086,  4087,  4088,  4089,  4092,  4093,  4094,  4095,  4096,  4103,
    4110,  4117,  4124,  4131,  4138,  4145,  4152,  4159,  4166,  4173,
    4180,  4183,  4184,  4185,  4186,  4187,  4188,  4191,  4195,  4199,
    4203,  4207,  4211,  4217,  4218,  4228,  4232,  4236,  4252,  4253,
    4256,  4257,  4258,  4259,  4260,  4263,  4264,  4265,  4266,  4267,
    4268,  4269,  4270,  4271,  4272,  4273,  4274,  4275,  4276,  4277,
    4278,  4279,  4280,  4281,  4282,  4283,  4284,  4285,  4286,  4289,
    4309,  4313,  4327,  4331,  4335,  4341,  4347,  4348,  4351,  4352,
    4355,  4356,  4359,  4365,  4366,  4369,  4370,  4373,  4374,  4377,
    4378,  4381,  4389,  4416,  4421,  4426,  4432,  4433,  4436,  4440,
    4460,  4461,  4462,  4463,  4466,  4470,  4474,  4480,  4481,  4484,
    4485,  4486,  4487,  4488,  4489,  4490,  4491,  4492,  4493,  4494,
    4495,  4496,  4497,  4498,  4499,  4502,  4503,  4504,  4505,  4506,
    4507,  4508,  4511,  4512,  4513,  4514,  4517,  4518,  4519,  4520,
    4523,  4524,  4527,  4533,  4541,  4554,  4561,  4567,  4573,  4582,
    4583,  4584,  4585,  4586,  4587,  4588,  4589,  4590,  4591,  4592,
    4593,  4594,  4595,  4596,  4597,  4598,  4599,  4602,  4611,  4612,
    4613,  4616,  4622,  4623,  4624,  4627,  4633,  4634,  4635,  4636,
    4639,  4645,  4646,  4647,  4648,  4649,  4650,  4651,  4652,  4653,
    4656,  4660,  4664,  4671,  4672,  4673,  4674,  4675,  4676,  4677,
    4678,  4679,  4680,  4681,  4682,  4685,  4686,  4687,  4688,  4691,
    4692,  4693,  4694,  4695,  4698,  4704,  4705,  4706,  4707,  4708,
    4709,  4710,  4713,  4719,  4720,  4721,  4722,  4725,  4731,  4732,
    4733,  4734,  4735,  4736,  4737,  4738,  4739,  4741,  4747,  4748,
    4749,  4750,  4751,  4752,  4753,  4754,  4757,  4763,  4764,  4765,
    4766,  4767,  4770,  4776,  4777,  4780,  4786,  4787,  4788,  4791,
    4797,  4798,  4799,  4800,  4803,  4809,  4810,  4811,  4812,  4815,
    4819,  4823,  4830,  4831,  4832,  4833,  4834,  4835,  4836,  4837,
    4838,  4839,  4842,  4843,  4844,  4845,  4846,  4847,  4848,  4849,
    4850,  4851,  4852,  4853,  4856,  4857,  4858,  4859,  4860,  4861,
    4862,  4863,  4866,  4872,  4873,  4874,  4877,  4883,  4884,  4885,
    4886,  4889,  4897,  4898,  4901,  4902,  4903,  4904,  4905,  4906,
    4907,  4908,  4911,  4917,  4918,  4921,  4927,  4928,  4929,  4930,
    4933,  4939,  4945,  4951,  4954,  4960,  4961,  4962,  4963,  4969,
    4975,  4976,  4977,  4978,  4979,  4980,  4983,  4989,  4990,  4993,
    4999,  5000,  5001,  5002,  5003,  5006,  5020,  5021,  5022,  5023,
    5024
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
  "\"synproxy\"", "\"mss\"", "\"wscale\"", "\"sack-perm\"", "\"typeof\"",
  "\"hook\"", "\"device\"", "\"devices\"", "\"table\"", "\"tables\"",
  "\"chain\"", "\"chains\"", "\"rule\"", "\"rules\"", "\"sets\"",
  "\"set\"", "\"element\"", "\"map\"", "\"maps\"", "\"flowtable\"",
  "\"handle\"", "\"ruleset\"", "\"trace\"", "\"inet\"", "\"netdev\"",
  "\"add\"", "\"update\"", "\"replace\"", "\"create\"", "\"insert\"",
  "\"delete\"", "\"get\"", "\"list\"", "\"reset\"", "\"flush\"",
  "\"rename\"", "\"describe\"", "\"import\"", "\"export\"", "\"monitor\"",
  "\"all\"", "\"accept\"", "\"drop\"", "\"continue\"", "\"jump\"",
  "\"goto\"", "\"return\"", "\"to\"", "\"constant\"", "\"interval\"",
  "\"dynamic\"", "\"auto-merge\"", "\"timeout\"", "\"gc-interval\"",
  "\"elements\"", "\"expires\"", "\"policy\"", "\"memory\"",
  "\"performance\"", "\"size\"", "\"flow\"", "\"offload\"", "\"meter\"",
  "\"meters\"", "\"flowtables\"", "\"number\"", "\"string\"",
  "\"quoted string\"", "\"string with a trailing asterisk\"", "\"ll\"",
  "\"nh\"", "\"th\"", "\"bridge\"", "\"ether\"", "\"saddr\"", "\"daddr\"",
  "\"type\"", "\"vlan\"", "\"id\"", "\"cfi\"", "\"pcp\"", "\"arp\"",
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
  "\"eol\"", "\"maxseg\"", "\"noop\"", "\"sack\"", "\"sack0\"",
  "\"sack1\"", "\"sack2\"", "\"sack3\"", "\"sack-permitted\"",
  "\"timestamp\"", "\"kind\"", "\"count\"", "\"left\"", "\"right\"",
  "\"tsval\"", "\"tsecr\"", "\"dccp\"", "\"sctp\"", "\"vtag\"", "\"rt\"",
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
  "'('", "')'", "'|'", "'$'", "'['", "']'", "$accept", "input",
  "stmt_separator", "opt_newline", "common_block", "line", "base_cmd",
  "add_cmd", "replace_cmd", "create_cmd", "insert_cmd", "delete_cmd",
  "get_cmd", "list_cmd", "reset_cmd", "flush_cmd", "rename_cmd",
  "import_cmd", "export_cmd", "monitor_cmd", "monitor_event",
  "monitor_object", "monitor_format", "markup_format", "describe_cmd",
  "table_block_alloc", "table_options", "table_block", "chain_block_alloc",
  "chain_block", "typeof_expr", "set_block_alloc", "set_block",
  "set_block_expr", "set_flag_list", "set_flag", "map_block_alloc",
  "map_block", "set_mechanism", "set_policy_spec", "flowtable_block_alloc",
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
  "ruleset_spec", "rule", "rule_alloc", "stmt_list", "stateful_stmt",
  "stmt", "verdict_stmt", "verdict_map_stmt", "verdict_map_expr",
  "verdict_map_list_expr", "verdict_map_list_member_expr",
  "connlimit_stmt", "counter_stmt", "counter_stmt_alloc", "counter_args",
  "counter_arg", "log_stmt", "log_stmt_alloc", "log_args", "log_arg",
  "level_type", "log_flags", "log_flags_tcp", "log_flag_tcp", "limit_stmt",
  "quota_mode", "quota_unit", "quota_used", "quota_stmt", "limit_mode",
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
  "set_elem_options", "set_elem_option", "set_elem_expr_options",
  "set_elem_expr_option", "set_lhs_expr", "set_rhs_expr",
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
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,    61,   123,   125,    40,    41,   124,    36,    91,    93
};
# endif

#define YYPACT_NINF -1376

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1376)))

#define YYTABLE_NINF -862

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1376,  6032, -1376,   275, -1376, -1376,    65,   160,   160,   160,
     822,   822,   822,   822,   822,   822,   822,   822, -1376, -1376,
    2749,   146,  1874,   225,  1783,   234,  4568,   547,  1479,   270,
    5530,   128,   147,   193, -1376, -1376, -1376, -1376,   101,   822,
     822,   822,   822, -1376, -1376, -1376,   841, -1376,   160, -1376,
     160,   115,  5161, -1376,   275, -1376,     3,     9,   275,   160,
   -1376,    41,    99,  5161,   160, -1376,   135, -1376,   160, -1376,
   -1376,   822, -1376,   822,   822,   822,   822,   822,   822,   822,
     208,   822,   822,   822,   822, -1376,   822, -1376,   822,   822,
     822,   822,   822,   822,   822,   822,   233,   822,   822,   822,
     822, -1376,   822, -1376,   822,   822,   822,   822,   822,  1150,
     822,   822,   822,   822,   822,   636,   822,   822,   822,   190,
     822,  1353,  1501,  1503,  1743,   822,   822,   822,  1796, -1376,
     822,  1827,  1864,   822, -1376,   822,   822,   822,   822,   822,
     307,   822, -1376,   822, -1376,   704,   495,    73,   251, -1376,
   -1376, -1376, -1376,   602,   798,   628,  1781,  2085,  1639,   396,
    1457,  1142,   633,    38,   482,   426,   124,  2305,    76,   466,
     525,   197,   299,   527,   320,  1015,   449,   872,  3422, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
    3856, -1376, -1376,  -131,  5389,   183,  1281,   451,  5530,   160,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376,   605, -1376, -1376,   194, -1376,
   -1376,   605, -1376, -1376, -1376, -1376,   488,   822,   822,   822,
     259, -1376, -1376, -1376, -1376, -1376, -1376, -1376,   418,   423,
     469, -1376, -1376, -1376,   378,   347,   523, -1376, -1376, -1376,
   -1376, -1376, -1376,     5,     5, -1376,   114,   160,  3651,  4084,
     386, -1376,   211,   283, -1376, -1376, -1376, -1376, -1376, -1376,
     556,   433, -1376,   641, -1376,   352,  5161, -1376, -1376, -1376,
   -1376, -1376, -1376,   594, -1376,   305, -1376, -1376, -1376,   371,
   -1376,  2292, -1376, -1376,   483, -1376,   154, -1376,   202, -1376,
   -1376, -1376,   682, -1376,    75, -1376, -1376,   621, -1376, -1376,
   -1376,   764,   652,   658,   367, -1376,   149, -1376,  4387, -1376,
   -1376, -1376,   651, -1376, -1376, -1376,   657, -1376,  4748,  4748,
   -1376, -1376,   648,   399,   402, -1376, -1376,   407, -1376, -1376,
   -1376,   425, -1376,   428,   698,  5161, -1376,    41,    99, -1376,
     135, -1376, -1376,   822,   822,   822,   259, -1376, -1376, -1376,
    5161,    94, -1376, -1376,   116, -1376, -1376,   120, -1376, -1376,
   -1376,   163, -1376, -1376,   135, -1376,   168, -1376, -1376, -1376,
   -1376, -1376,   822, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376,   135, -1376, -1376, -1376, -1376, -1376, -1376,   822, -1376,
   -1376, -1376, -1376, -1376, -1376,   822,   822, -1376, -1376, -1376,
     716,   742,   749,   822, -1376,   822, -1376,   822, -1376,   822,
   -1376,   822, -1376, -1376, -1376, -1376,   822, -1376, -1376,   822,
   -1376,   822, -1376, -1376, -1376, -1376, -1376, -1376, -1376,   822,
   -1376,   160, -1376, -1376, -1376,   795, -1376, -1376, -1376, -1376,
   -1376,   805,   132, -1376, -1376, -1376,   718,    28, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
     213,   219, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
     785, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376,  2796, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,    -3, -1376,
   -1376,   512, -1376, -1376, -1376, -1376, -1376, -1376,   534, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
    1167, -1376, -1376, -1376, -1376,   568,   221,   585,   723, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376,   587,   572, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
     605, -1376, -1376, -1376,   675,   666,   634,   916, -1376, -1376,
   -1376,  3462,   853,  4534,  5530, -1376, -1376, -1376, -1376,   914,
     918,   -11,   903,   913,   920,    12,   934,  1167,   947,  4534,
    4534,   661,  4534, -1376, -1376,   843,  4534,  4534,   906, -1376,
    4819,    53, -1376,   916, -1376, -1376,   902,   905,   594, -1376,
     472,   916,   912,   915,   922,   916,   305, -1376,   401, -1376,
    4534, -1376, -1376,  3691,   798,   628,  1781,  1317, -1376,  2417,
     387, -1376, -1376, -1376, -1376, -1376, -1376, -1376,  5744, -1376,
     781,  1018,  1023,   721,   667,   257, -1376, -1376, -1376, -1376,
   -1376,  1039,   767,  1045, -1376, -1376, -1376, -1376,  1059, -1376,
   -1376, -1376, -1376,    64, -1376, -1376,  1062,  1063, -1376,   972,
     973, -1376, -1376,   483, -1376,  1083, -1376, -1376, -1376, -1376,
    1089, -1376,  3920, -1376,  1089,  4534, -1376, -1376,   682, -1376,
    1090, -1376,   160, -1376,   768, -1376,   160,    35, -1376,  6139,
    6139,  6139,  6139,  6139,  5530,    69,  4748, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
    6139, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,  1091,
   -1376,   943,  1082,  1095,   775,   639,  1101, -1376, -1376, -1376,
    4748,  4534,  4534,   275,  1091, -1376,   275,  1016, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376,   648,   796,   802,   803,
   -1376,   804,   813, -1376, -1376, -1376,   675,   666,   634,   916,
   -1376,  1020,  1050,  1051,  1052, -1376,  1053, -1376, -1376, -1376,
   -1376, -1376,   822,   822,   822, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376,  1055,   495, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376,   500, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376,   893, -1376,  1061,  1067, -1376,
   -1376,   856, -1376,   870, -1376, -1376, -1376, -1376, -1376, -1376,
    1069,  1071,   873,  1074,     7, -1376, -1376, -1376,   840,   858,
     868,  1079, -1376,   661, -1376,  1094, -1376, -1376, -1376,  4534,
    2085,  1457,  1186,  4149, -1376,    75,   125,  1187,   916,   916,
    1102,  5530,  4534,  4534,  4534, -1376,  1103,  4534,  1161,  4534,
   -1376, -1376, -1376, -1376,  1114, -1376,    39,  1177, -1376,  4534,
   -1376,   641,   989,   173, -1376,   857,  1101,   641, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376,  1077,   436, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376,  1112,  1113,  1164,  1124,
   -1376,  4534,  1240,   921, -1376, -1376,  5744,  5744,  5744,  5744,
    5744,  1147,  5744,  5744,    78,  4534,  1089,  4534,  1248,  1873,
    1873, -1376, -1376, -1376,  4534,   767,  4534,   767, -1376, -1376,
     707, -1376,  5530, -1376,  5530, -1376, -1376, -1376,   943,  1082,
    1095, -1376,   641, -1376, -1376, -1376,   923,  6139,  6139,  6139,
    6139,  6139,  6139,  6139,  1158,  6139,  6139, -1376, -1376, -1376,
   -1376, -1376,   756,  1786,  2620,   845,   467,   325, -1376, -1376,
   -1376, -1376, -1376, -1376,   939,   940,   941, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
    1258, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376,   942,   946, -1376,
   -1376, -1376, -1376,   873,   -94,  1168, -1376, -1376, -1376, -1376,
   -1376,   898, -1376, -1376, -1376,  1019,  1178,    39, -1376,  4534,
    4534,  1274, -1376,  1179,  1179, -1376,   125, -1376, -1376, -1376,
     961,  1187,  5161,   125, -1376, -1376, -1376, -1376, -1376,  4534,
   -1376,   134, -1376, -1376,  1021,  4534,  1250, -1376,  6041, -1376,
    1179,  1179,  1043, -1376,   173, -1376,  4819, -1376, -1376, -1376,
   -1376,  1286, -1376,  1198,  1200, -1376,  1202, -1376,  4534, -1376,
   -1376, -1376,   781,  1018,  1023, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376,  1302,  1148, -1376, -1376, -1376, -1376,   767, -1376,
     767,  1089, -1376,    51,  5161,  4982,    55, -1376, -1376, -1376,
   -1376, -1376,   943,  1082,  1095, -1376, -1376, -1376, -1376,   857,
    1210,  1275,   160,   160,   160,   160,   160,  1216,   241,   160,
     160,   160,   160, -1376, -1376, -1376,   275,    82,  1218,  1215,
   -1376, -1376, -1376,   275,   275,   275,   275,  5530, -1376,  1179,
    1179,  1008,   938,  1231,   577,   774,   275, -1376, -1376, -1376,
     275,  5530,  1179,  1017,   577,   774, -1376, -1376, -1376,   275,
    1236,  1024, -1376, -1376, -1376, -1376,  2336,  2930,  1709,   581,
     397, -1376, -1376, -1376,  1241, -1376, -1376, -1376,  1242, -1376,
   -1376, -1376, -1376, -1376,    90,   218,   205,  1246,   140,  1021,
   -1376, -1376,  4534, -1376, -1376, -1376, -1376,  5530,  1027,   125,
   -1376,   962,  1075,  1251, -1376, -1376,  4534,   641,  1101, -1376,
   -1376, -1376,  1252, -1376,   436, -1376, -1376, -1376, -1376,  4534,
    1271,  1089,  1089,  5530,  1171, -1376,    45,  1038,  1361,   641,
   -1376,  1185,  1272, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376,   160,   160,   160, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376,  1337, -1376, -1376, -1376,
   -1376, -1376,   826, -1376,   275,   275,   135, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,   846, -1376,
   -1376, -1376, -1376, -1376,   863, -1376, -1376, -1376,   530,   275,
     135,   620,   863, -1376,  1233,  1056, -1376, -1376, -1376, -1376,
   -1376,   690,   358,  1010, -1376,   873,  1060,   303,   822, -1376,
   -1376, -1376, -1376,  1179,  1289,   303,  1293,   822, -1376, -1376,
   -1376, -1376,  1295,   822, -1376, -1376, -1376, -1376, -1376,   962,
    1075, -1376, -1376,  5161, -1376, -1376, -1376, -1376, -1376, -1376,
    1130,  1298, -1376,    39, -1376, -1376,  1155, -1376, -1376,  4534,
    1084,  5530, -1376, -1376,  1729,  4982, -1376, -1376,  1368,   275,
    1088,  1092,  1099,  1100,  1106, -1376, -1376, -1376,  1109,  1110,
    1116,  1135,  1322,  5530, -1376, -1376, -1376, -1376,   577, -1376,
     774, -1376,  5530, -1376, -1376,  1058, -1376,   113,   275,  1323,
     275, -1376, -1376, -1376, -1376,  1136, -1376, -1376,   275,   275,
     275,   275,   275,   275,   275,  1329,   275,  1130, -1376,  1129,
    1362, -1376,    42, -1376,  1363, -1376, -1376,  1138,   641, -1376,
   -1376,  1185, -1376, -1376, -1376, -1376, -1376,  1144,  1146,  1174,
   -1376, -1376, -1376, -1376,   992, -1376, -1376, -1376,   826,   275,
     275,   275,   275,   846,  1372, -1376, -1376, -1376,   629, -1376,
   -1376, -1376, -1376, -1376,    58, -1376, -1376,  1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376,   303, -1376, -1376, -1376,  1237,
   -1376, -1376, -1376, -1376, -1376,  1368,   709,  3232,  2142,  2665,
     595, -1376, -1376, -1376,  1111,  1172,   705,   859,   916,  1173,
    1233, -1376, -1376, -1376, -1376, -1376, -1376, -1376,  1380,  1397,
     158, -1376,  1495,    70, -1376,   275, -1376, -1376,   275, -1376,
   -1376, -1376,   275,   275,   275,   275,   748,   963,  1159,   275,
   -1376, -1376, -1376,   275, -1376, -1376, -1376,   275, -1376, -1376,
   -1376,   275, -1376, -1376, -1376, -1376,  1056, -1376, -1376, -1376,
   -1376, -1376,  1401,  1376,   275, -1376, -1376, -1376, -1376, -1376,
   -1376,   275,   275,   275, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     309,   309,   309,   309,   309,   309,   309,   309,   313,   316,
     309,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,   315,   314,   311,   312,     0,   309,
     309,   309,   309,    14,    13,     3,     0,    17,     0,   310,
       0,   334,     0,    12,     0,   304,     0,     0,     0,     0,
     463,    32,    34,     0,     0,   191,     0,   212,     0,   230,
      18,   309,    19,   309,   309,   309,   309,   309,   309,   309,
       0,   309,   309,   309,   309,    20,   309,    21,   309,   309,
     309,   309,   309,   309,   309,   309,     0,   309,   309,   309,
     309,    22,   309,    23,   309,   309,   340,   309,   340,   340,
     309,   309,   340,   309,   340,     0,   309,   340,   340,     0,
     309,   340,   340,   340,   340,   309,   309,   309,   340,    24,
     309,   340,   340,   309,    25,   309,   309,   309,   309,   340,
       0,   309,    26,   309,    27,     0,     0,     0,   605,   576,
     305,   306,   307,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   765,
     766,   767,   768,   769,   770,   771,   772,   773,   774,   775,
     776,   777,   778,   779,   780,   781,   782,   783,   784,   786,
       0,   788,   787,     0,     0,     0,     0,   785,     0,     0,
      31,   572,   571,   577,   578,   162,   588,   589,   582,   756,
     583,   586,   590,   587,   584,   585,   579,   869,   870,   871,
     872,   873,   874,   875,   876,   877,   878,   879,   880,   881,
     882,   883,   884,   885,   886,   580,  1034,  1035,  1036,  1037,
    1038,  1039,  1040,  1041,   581,     0,   159,   160,     0,    28,
     143,     0,    29,   145,   148,    30,   149,   309,   309,   309,
      42,   685,   661,   663,    16,    15,   317,   319,     0,     0,
       0,   336,   335,   337,     0,   453,     0,   556,   557,   558,
     747,   748,   749,     0,     0,   752,   563,     0,     0,     0,
     383,   391,     0,   415,   436,   443,   444,   518,   524,   541,
       0,     0,   792,     7,    37,   342,   344,   355,   345,   351,
     371,   350,   347,   381,   357,   389,   348,   349,   358,   437,
     359,     0,   360,   369,   451,   363,   517,   364,   523,   365,
     366,   361,   539,   367,     0,   368,   353,     0,   562,   352,
     607,   610,   612,   614,   616,   617,   624,   626,     0,   625,
     569,   370,   756,   356,   362,   354,   579,     8,     0,     0,
      11,   328,     0,     0,     0,    36,   322,     0,    40,   205,
     204,     0,   325,     0,     0,     0,   463,    52,    54,   191,
       0,   212,   230,   309,   309,   309,    60,   685,   661,   663,
       0,     0,    90,    91,     0,    70,    71,     0,    72,    73,
      74,     0,    75,    76,     0,    77,     0,    79,    80,   665,
     666,   664,   309,    81,    82,    86,    87,    83,    84,    88,
      89,     0,   114,    93,   341,    94,    95,    96,   309,    97,
      99,   123,   122,   121,   115,   309,   340,   119,   118,   120,
     665,   666,     0,   309,   102,   309,   100,   309,   103,   309,
     106,   309,   112,   108,   105,   111,   309,   109,   130,   309,
     128,   309,   131,   133,   134,   135,   136,   137,   140,   309,
     139,     0,   888,   889,   890,     0,   596,   597,   598,   599,
     600,   602,     0,   796,   797,   795,     0,     0,  1032,  1033,
    1031,   892,   893,   894,   891,   899,   896,   897,   898,   895,
       0,     0,   901,   902,   903,   904,   905,   900,   923,   924,
     918,   913,   914,   915,   916,   917,   919,   920,   921,   922,
       0,   910,   935,   938,   937,   936,   939,   940,   941,   934,
     943,   944,   945,   946,   942,   955,   956,   948,   949,   950,
     952,   951,   953,   954,   947,   958,   963,   960,   959,   964,
     962,   961,   965,   957,   968,   971,   967,   969,   970,   966,
     974,   973,   972,   976,   977,   978,   975,   982,   983,   980,
     981,   979,   988,   985,   986,   987,   984,  1000,   994,   997,
     998,   992,   993,   995,   996,   999,  1001,     0,   989,  1025,
    1023,  1024,  1022,  1030,  1027,  1028,  1029,  1026,  1048,   816,
    1047,   822,   817,  1046,  1049,   820,   821,   823,     0,   818,
    1045,     0,  1050,  1053,  1052,  1056,  1055,  1057,     0,  1054,
    1044,  1043,  1042,  1065,  1062,  1060,  1061,  1063,  1064,  1059,
    1068,  1067,  1066,  1072,  1071,  1074,  1070,  1073,  1069,   757,
     760,   761,   762,   764,   763,   785,   755,   758,   759,   837,
     838,   830,   831,   829,   839,   840,   859,   833,   842,   835,
     836,   841,   832,   834,   827,   828,   857,   856,   858,   843,
       0,   824,   844,   801,   800,     0,   624,     0,     0,  1077,
    1076,  1078,  1079,  1080,  1075,   805,   806,   804,     0,   570,
     142,   161,   144,   150,   151,   153,   152,   155,   156,   154,
     157,   682,   682,   682,     0,     0,   415,     0,   331,   332,
     333,     0,     0,     0,     0,   754,   753,   750,   751,     0,
       0,     0,   757,   755,     0,     0,     0,     0,   824,     0,
       0,   424,     0,   413,   414,     0,     0,     0,     0,     6,
       0,     0,   628,     0,   343,   346,     0,     0,   382,   385,
       0,     0,     0,     0,     0,     0,   390,   392,     0,   435,
       0,   499,   720,     0,   712,   715,   716,   713,   719,   714,
       0,   723,   721,   722,   718,   717,   709,   710,     0,   481,
     484,   486,   488,   490,   491,   496,   503,   500,   501,   502,
     504,   506,   442,   468,   469,   479,   711,   470,   477,   471,
     478,   474,   475,     0,   472,   473,     0,   505,   476,     0,
       0,   460,   459,   452,   455,     0,   536,   537,   538,   516,
     521,   534,     0,   522,   527,     0,   548,   549,   540,   542,
     545,   546,     0,   574,     0,   573,     0,     0,   564,     0,
       0,     0,     0,     0,     0,     0,     0,   741,   742,   743,
     744,   745,   746,   712,   715,   716,   713,   733,   734,   714,
     735,   732,   731,   736,   729,   730,   728,   737,   738,   739,
       0,   692,   724,   694,   725,   621,   622,   706,   693,   687,
     686,   698,   700,   702,   704,   705,   691,   726,   727,   695,
       0,     0,     0,     0,   657,   656,     0,     0,    50,   165,
     182,   192,   213,   231,   338,    51,     0,     0,     0,     0,
      58,     0,     0,   682,   682,   682,     0,     0,   415,     0,
      69,     0,     0,     0,     0,    78,     0,   682,    92,    98,
     117,   116,   309,   309,   309,   124,   101,   104,   107,   113,
     110,   129,   132,   138,   141,     0,     0,   595,   593,   594,
     592,   606,   603,   604,   906,   908,   907,   909,   925,   926,
     927,   928,   912,  1005,  1012,  1002,  1004,  1003,  1007,  1008,
    1009,  1010,  1011,  1006,  1013,   991,   819,     0,     0,   845,
     846,     0,   848,     0,   847,   849,   850,   825,   826,   851,
       0,     0,   798,     0,     0,   591,   146,   158,     0,     0,
       0,     0,    43,   424,    48,     0,    44,   662,    49,     0,
     713,   714,   445,     0,   454,     0,   550,   552,     0,     0,
       0,     0,     0,     0,     0,   379,     0,     0,   851,     0,
     384,   412,   422,   423,     0,   421,     0,   530,   532,     0,
     653,     7,     7,   637,   639,   705,   652,     7,   627,   339,
     387,   388,   386,   405,   404,     0,     0,   403,   399,   394,
     395,   396,   397,   400,   398,   393,     0,     0,     0,     0,
     512,     0,   507,     0,   468,   477,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   514,     0,     0,     0,
       0,   457,   458,   456,     0,     0,     0,   525,   544,   543,
       0,   575,     0,   566,     0,   565,   608,   609,   611,   613,
     615,   618,     7,   372,   374,   623,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   688,   790,   868,
       9,    10,     0,     0,     0,     0,     0,     0,    68,   165,
     182,   192,   213,   231,     0,     0,     0,    61,    66,    62,
      67,   329,   318,   320,   323,   326,    85,   126,   127,   125,
       0,   601,   929,   930,   932,   931,   933,   911,  1016,  1015,
    1014,  1017,  1018,  1019,  1020,  1021,   990,     0,     0,   852,
     853,   854,   855,   798,   798,     0,   815,   803,   807,   808,
     811,     0,   259,   263,   255,     0,     0,     0,   447,     0,
       0,   446,   553,     0,     0,   644,   551,   640,   794,   793,
       0,   636,     0,   634,   791,   789,   865,   380,   866,     0,
     864,     0,   417,   416,   418,     0,     0,   631,     0,   632,
       0,     0,   649,   651,   638,   645,   630,   629,   402,   408,
     409,   401,   407,     0,     0,   441,     0,   513,     0,   480,
     482,   483,   485,   487,   489,   497,   498,   492,   495,   494,
     493,   509,   508,     0,   860,   861,   862,   863,   519,   535,
     526,   528,   547,     0,     0,     0,     0,   375,   740,   690,
     696,   697,   699,   701,   703,   689,   619,   620,   707,   708,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,   167,   166,     0,     0,     0,     0,
      35,   184,   183,     0,     0,     0,     0,     0,   202,     0,
       0,     0,     0,     0,     0,     0,     0,    38,   194,   193,
       0,     0,     0,     0,     0,     0,    39,   215,   214,     0,
       0,     0,   236,    41,   233,   232,     0,     0,     0,     0,
       0,   259,   263,   255,     0,  1051,  1058,   802,     0,   814,
     799,   810,   809,   812,     0,     0,     0,     0,     0,   418,
     448,   450,     0,   308,   642,   643,   641,     0,     0,   635,
     867,     0,   427,     0,   420,   531,     0,     7,   654,   655,
     647,   648,     0,   646,     0,   438,   439,   440,   510,     0,
       0,   520,   529,     0,     0,   554,     0,     0,     0,     7,
     373,   464,     0,   330,   246,   321,   181,   324,   191,   212,
     327,   230,   164,     0,     0,     0,   246,   246,   246,   246,
     168,   302,   303,   299,   301,   300,     0,   298,   185,   187,
     186,   188,     0,   189,     0,     0,     0,   229,   228,   226,
     227,   279,   281,   282,   280,   243,   283,   244,     0,   242,
     208,   209,   211,   210,     0,   207,   200,   203,     0,     0,
       0,     0,     0,   225,     0,     0,    53,    55,    56,    57,
      59,     0,     0,     0,   887,   798,     0,     0,     0,    46,
     261,   260,   262,     0,     0,     0,     0,     0,    47,   265,
     264,   266,     0,     0,    45,   257,   256,   258,   658,     0,
     427,   660,   449,     0,   567,   430,   431,   432,   433,   434,
     425,     0,   411,     0,   533,   633,     0,   406,   511,     0,
       0,     0,   555,   561,     0,   377,   376,   465,   466,     0,
       0,     0,     0,     0,     0,   246,   246,   246,     0,     0,
       0,     0,     0,     0,   196,   198,   199,   201,     0,   195,
       0,   197,     0,   216,   224,     0,   223,     0,     0,     0,
       0,    64,    65,    63,   813,     0,   668,   667,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   425,   684,     0,
       0,   410,     0,   419,     0,   515,   559,     0,     7,   467,
     461,   464,   275,   182,   192,   213,   231,     0,     0,     0,
     247,   267,   251,   271,   297,   190,   245,   206,     0,     0,
       0,     0,     0,     0,     0,   293,   287,   286,   290,   285,
     288,   289,   234,   241,     0,   238,   235,     0,   674,   676,
     679,   680,   677,   678,   681,     0,   670,   683,   568,     0,
     429,   428,   650,   560,   378,   466,     0,     0,     0,     0,
       0,   259,   263,   255,     0,     0,     0,     0,     0,     0,
       0,   218,   219,   221,   220,   222,   217,   294,     0,     0,
       7,   237,     0,     0,   671,     0,   426,   462,     0,   277,
     276,   278,     0,     0,     0,     0,     0,     0,     0,     0,
     249,   248,   250,     0,   269,   268,   270,     0,   253,   252,
     254,     0,   273,   272,   274,   295,     0,   284,   292,   291,
     240,   239,     0,     0,     0,   669,   180,   169,   170,   171,
     172,     0,     0,     0,   173,   178,   174,   179,   296,   673,
     672,   675,   176,   177,   175
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1376, -1376,    -1, -1008,    11, -1376, -1376,  1486, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376,   -13, -1376,  1120, -1376,   359,  -377, -1110,
   -1238,  -386, -1109,  -380,   164,   -53,  -383, -1104, -1107, -1376,
    -388, -1099,  -208, -1376,  -171,   -47, -1217,  -306, -1376, -1376,
   -1304, -1298, -1275, -1376, -1376, -1376, -1376, -1376,  -157, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376,   249,  -692, -1076,
    1436,   -42,  2173, -1376,   746, -1376, -1376,    31, -1376,   223,
     480, -1376, -1376,  1832,   986,  -286,  1149, -1376, -1376,   139,
    1435,  -302,    68,    32, -1376, -1376,   247,  -307, -1376, -1376,
   -1376, -1376,   117, -1376, -1376, -1376, -1376,   779, -1376, -1376,
   -1376,   766, -1376, -1376, -1376,   137, -1376,  1247, -1172,   172,
   -1376,   526,   -40,    36,    46, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376,   735,  -899,  1182,   -39,  -101,  -889,
     481,   486,   491, -1376,  -686, -1376, -1376, -1376, -1376, -1376,
    -340, -1376,  1320, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376,  -323,   465, -1376, -1376, -1376,   740, -1376,   487,
   -1057, -1376, -1376,  1310, -1376, -1376, -1376, -1376,   751, -1376,
   -1376,   -43,   -25,  -755,  -330,    98,   -23, -1376, -1376, -1376,
     644,    22, -1376, -1376, -1376, -1376, -1376,  -177,  -198, -1376,
   -1376,   473, -1376,  1398,   -65, -1376,   544, -1015, -1376, -1227,
   -1376,   380, -1082, -1376,   368, -1376, -1376,  1244,  -906,  1220,
    -907,  1213,  -905,  1219,  1505, -1375, -1376, -1376,  -119, -1376,
   -1376,  -438,  -897,  1225, -1376,  1276,  -326,  -747,  -739,  -733,
   -1376,  -332,  -734, -1376,  -237,   996,  -713, -1376, -1167,  1342,
      63,  1340, -1376,   -30, -1376,    92, -1376, -1083, -1376,   186,
   -1376, -1376, -1376, -1376, -1376,   398,  -243,   540,  1022,   610,
    1345,  1346, -1376, -1376,  -535,   -41, -1376, -1376, -1376,   660,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376,
   -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376, -1376
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1321,   750,  1322,    45,    46,    47,    72,    85,
      87,   101,   103,   129,   134,   142,   144,   259,   262,   265,
     266,   710,  1006,   260,   210,   373,  1316,  1143,   374,  1144,
    1452,   377,  1145,   378,  1474,  1475,   381,  1146,  1340,  1459,
     383,  1147,  1580,  1644,  1645,  1467,  1468,  1550,  1674,  1676,
    1376,  1374,  1375,  1675,  1677,  1666,  1469,  1323,  1578,  1638,
    1639,  1640,  1680,  1324,  1325,  1443,  1444,  1423,   211,  1384,
      48,    49,    59,   406,    51,   409,  1426,    65,   413,  1428,
      69,   418,  1431,    60,   403,  1424,   281,   282,   283,    52,
     385,  1215,   435,  1326,   315,   316,   317,   318,   319,   320,
    1123,  1286,  1287,   321,   322,   323,   758,   759,   324,   325,
     766,   767,  1074,  1068,  1251,  1252,   326,  1015,  1234,  1394,
     327,  1044,  1601,  1532,  1530,   328,   329,   769,   330,   331,
     332,   333,   334,   823,   824,   908,   372,  1548,  1610,   789,
     790,   791,   792,   793,   794,   795,  1268,   796,   797,   798,
     799,   800,   801,   802,   335,   336,   829,   337,   338,   833,
     339,   340,   830,   831,   341,   342,   838,   839,   840,   841,
    1025,  1026,   343,   344,   345,   346,   347,   847,   848,   348,
     349,   212,   803,   844,   883,   804,   350,   216,   960,   491,
     492,   805,   497,   351,   352,   353,   354,   355,   356,   885,
     886,   887,   357,   358,   359,   751,   752,  1222,  1223,  1052,
    1053,  1216,  1217,  1244,  1245,  1054,  1397,   903,  1012,   714,
    1016,   716,  1018,   717,   422,  1588,  1517,  1693,  1694,  1502,
    1511,  1008,  1014,   715,   360,   904,   905,   891,   892,   893,
     894,  1055,   896,   806,   807,   808,   899,   900,   361,   727,
     809,   656,   657,   219,   363,   810,   495,  1196,   685,   811,
    1004,   697,  1200,  1373,   222,   812,   618,   814,   619,   815,
     680,   681,   997,   998,   682,   816,   817,   364,   365,   818,
     227,   485,   228,   504,   229,   509,   230,   517,   231,   531,
     972,  1177,   232,   539,   233,   544,   234,   554,   235,   563,
     236,   569,   237,   572,   238,   576,   239,   581,   240,   586,
     241,   598,   985,  1186,   242,   602,   243,   607,   244,   500,
     245,   246,   632,   247,   620,   248,   622,   249,   624,   250,
     629,   251,   639,   252,   642,   253,   648,   254,   694
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   380,    53,   919,   922,   213,   686,   215,   921,   755,
     920,   918,    44,   754,   845,   834,  1056,  1148,   881,   263,
    1157,  1159,   362,   379,  1160,  1017,   895,   213,   881,   881,
    1158,   698,   890,   362,   935,  1379,   895,   895,   213,  1349,
    1357,   722,  1358,  1237,  1239,   275,    66,    67,  1359,  1246,
    1541,   938,   217,   367,  1360,  1283,  1413,   370,  1418,  1493,
    1057,  1059,  1419,  1491,   434,  1690,   434,   434,   748,  1069,
     434,  1399,   434,  1073,   217,   434,   434,  1733,   846,   434,
     434,   434,   434,  1030,   314,   217,   434,  1492,   813,   434,
     434,     3,   842,   218,     4,   375,     5,   434,   842,  1284,
    1124,   842,  1083,  1478,  1118,   493,    55,   389,   390,   391,
    1367,  1369,  1035,  1119,  1285,   218,     6,     7,     8,     9,
    1120,   897,   220,   412,   414,   415,   218,  1481,   214,   609,
    1592,   897,   897,   431,  1386,  1634,  1116,  1117,  1385,   611,
    1232,   440,   441,  1660,   220,   999,  1097,   447,   658,   931,
     214,   962,    63,   612,  1391,   220,   683,   854,  1441,  1442,
    1519,   214,   749,  1198,  1400,  1401,   684,    54,   476,   477,
     278,   932,   480,   855,   729,   933,   437,   439,   570,   213,
     442,  1496,   444,   213,   255,   448,   449,   599,   267,   456,
     458,   460,   462,    71,   571,    55,   467,  1260,  1261,   470,
     472,   856,  1038,   261,  1267,  1195,     3,   478,  1368,     4,
     730,     5,  1213,  1635,  1636,  1214,   221,    55,   934,     3,
    1497,    55,     4,   936,     5,   400,   217,   615,   616,   854,
     217,     6,     7,     8,     9,  1392,   825,  1017,   221,   600,
     601,  1520,   700,   957,     6,     7,     8,     9,   702,   221,
     726,   726,  1349,  1454,  1455,   582,    56,    57,    58,  1643,
    1240,    55,  1098,  1241,    55,  1093,  1479,   218,   658,    55,
    1212,   218,    86,   856,  1009,  1010,   963,   450,  1036,     4,
    1695,     5,   494,  1414,   832,   102,   362,   583,   584,  1233,
     585,   213,  1661,   888,   264,   393,   220,   276,   300,   277,
     220,   843,   214,   888,   888,  1503,   214,  1386,   371,  1094,
     617,  1031,  1504,   376,   302,   143,  1512,   382,  1418,   303,
     419,   964,  1199,  1498,   368,   380,     3,   966,  1433,     4,
     369,     5,   209,   882,  1628,   965,  1218,  1219,   217,  1269,
     268,   967,   269,   882,   882,   958,   959,   379,  1505,   380,
     479,     6,     7,     8,     9,   362,  1540,  1114,  1633,     3,
     213,  1603,     4,  -163,     5,  1350,   380,  1351,  1542,  1708,
     362,   379,  1523,  1706,  1415,   213,  1058,  1608,  1420,   218,
     496,  1691,  1506,  1292,     6,     7,     8,     9,   379,  1535,
     221,  1122,  1293,  1734,   221,   621,   209,  1707,     3,  1294,
     313,     4,   209,     5,   434,   209,  1266,   217,   220,   209,
    1050,  1545,  1584,  1499,   214,  1290,  1291,   915,   279,   280,
    1242,  -181,   217,     6,     7,     8,     9,  1590,   223,   451,
     753,   421,   930,  1637,   256,   257,   258,  1350,  1513,  1351,
     209,   826,   827,   828,   630,  1503,   452,   394,   218,   395,
     223,  1507,  1504,   256,   257,   258,   884,   313,   699,   740,
     721,   223,   209,   218,   760,  1586,   884,   884,     3,   631,
    1587,     4,   420,     5,   421,   741,   940,   220,   753,  1096,
    1434,   688,  1435,   214,  1607,  1154,  1155,  1156,  1505,   826,
     827,   828,   220,     6,     7,     8,     9,   623,   214,  1166,
     609,   701,   221,  1667,  1398,  1668,  1341,   540,  -659,   609,
     953,  1669,  1056,   897,   941,   747,   881,  1670,   718,   819,
     820,   821,  1506,   719,   612,   845,  1027,   541,  1514,   611,
    1125,   742,   703,   612,   704,  1572,   705,   706,  1563,  1076,
     542,  1508,   725,   725,   707,   708,   731,  1063,  1126,   743,
     744,  1056,  1077,   577,  1342,   609,  1343,   578,  1332,   392,
     881,  1333,  1349,   761,   762,   763,   764,   765,  1078,   720,
     224,   221,  1352,   640,  1137,   417,  1249,   709,  1344,   612,
    1064,  1250,     3,   287,   288,     4,   221,     5,   289,   579,
     580,  1507,   224,   443,  1065,   723,     3,   603,   641,     4,
    1664,     5,   223,   224,   486,   487,   223,     6,     7,     8,
       9,  1172,   897,   897,   897,   897,   897,   615,   616,   897,
    1341,     6,     7,     8,     9,  1575,  1345,  1173,  1568,   604,
     605,   573,  1174,  1175,   739,  1350,   608,  1351,   746,  1066,
     225,   574,   575,   897,  1352,   749,  1133,   609,  1353,   610,
     371,  1688,   768,   276,  1689,   543,   277,   753,   606,  1134,
     376,  1135,   225,   897,   846,   382,   822,   611,  1342,   851,
    1343,   612,  1332,   225,   613,  1333,   852,  1121,  1461,   445,
     446,  1582,  1730,  1079,   907,  1051,   625,  1091,  1067,  1092,
     226,     3,  1344,   853,     4,   845,     5,  1007,  1176,   213,
     617,   901,  1462,  1463,   488,   489,     3,   902,   490,     4,
       3,     5,   366,     4,   223,     5,     6,     7,     8,     9,
    1490,   909,   614,   366,   910,   882,   626,   627,   628,   911,
     954,     6,     7,     8,     9,     6,     7,     8,     9,   505,
    1345,   506,   507,   508,   224,   907,   217,   912,   224,     3,
     913,  1243,     4,   278,     5,   615,   616,   564,    62,   942,
       4,  1201,     5,  1084,   845,   498,   499,  1701,  1712,  1720,
     695,   696,  1724,   565,     6,     7,     8,     9,  1716,   849,
     850,  1496,   566,   223,  1281,   943,  1464,   218,   567,   568,
    1346,   888,   944,  1300,   130,  1289,  1086,  1087,   223,   131,
     132,  1295,   955,  1297,  1299,  -415,  1465,  1466,   482,   483,
     484,  1056,   843,   956,   225,   133,   220,   384,   225,   961,
    1497,   388,   214,  1002,   882,   882,   882,   882,   882,   213,
       4,   882,     5,  1221,  1563,   888,   408,   384,   617,  1496,
     987,   274,  1352,   756,   757,     4,     3,     5,   884,     4,
       4,     5,     5,   436,  1568,   882,   224,  1470,  1471,  1472,
       3,  1473,   988,     4,   226,     5,  1000,     4,   226,     5,
    1570,     6,     7,     8,     9,   882,   217,  1134,  1497,  1135,
      18,    19,   475,  1001,  1327,     6,     7,     8,     9,   481,
     897,   897,   897,   897,   897,   897,   897,  1005,   897,   897,
     743,   744,  1140,  1003,  1489,  1141,  1050,   501,   502,   503,
     221,   256,   257,   258,  1027,  1388,  1221,   218,  1705,   968,
     969,   970,   971,  1498,  1011,   224,   225,  1042,  1043,    34,
    1013,  1328,  1329,  1330,  1331,  1023,  1332,  1028,    35,  1333,
     224,  1029,  1243,  1046,    36,  1050,   220,   884,   884,   884,
     884,   884,   214,  1032,   884,  1411,  1334,  1412,  1128,  1129,
     150,   151,   152,  1033,     3,  1189,  1190,     4,    37,     5,
    1034,   743,   744,   835,   836,   837,   366,  1417,   884,  1191,
    1192,  1498,   843,   643,  1037,  1017,  1725,  1178,  1049,     6,
       7,     8,     9,   749,  1238,   225,   644,  1039,   884,   836,
     837,   897,  1060,   645,  1335,  1061,   213,  1371,  1372,   897,
     225,     3,  1070,  1581,     4,  1071,     5,   150,   151,   152,
    1179,   646,  1072,  1436,  1437,  1438,  1439,   647,  1717,  1270,
    1457,  1458,  1698,  1678,  1679,  1088,     6,     7,     8,     9,
     221,  1089,  1552,  1554,  1095,   366,  1553,  1090,   897,  1551,
    1503,   843,  -860,   217,   826,   827,   828,  1504,  1276,  1277,
     366,  1084,  1084,  1084,  1084,  1084,  -861,  1084,  1084,  1099,
    1100,  1741,  1101,  1102,  1274,  1274,  1567,  1180,  1181,  1182,
    1183,  1184,  1185,   424,   426,   428,   430,   213,  1104,   213,
    1112,  1111,  1336,  1505,   218,  1113,  1105,  1110,  1127,  1130,
    1574,  1132,   882,   882,   882,   882,   882,   882,   882,  1136,
     882,   882,     3,  1131,   362,     4,  1142,     5,  1149,   213,
    1161,  1512,   223,   220,  1150,  1151,  1152,  1506,   633,   214,
    1558,  1559,  1560,  1561,   217,  1153,   217,     6,     7,     8,
       9,  1301,  1314,   634,  1338,  1347,  1354,  1555,  1556,  1557,
    1162,  1163,  1164,  1165,  1315,  1170,  1339,  1348,  1355,  1461,
       3,  1187,  1202,     4,   635,     5,   217,  1188,  1337,  1193,
     636,  1194,  1195,     3,  1197,   218,     4,   218,     5,  1205,
    1203,  1051,  1721,  1462,  1463,     6,     7,     8,     9,  1221,
    1204,  1209,   362,   438,  1207,   854,  1507,   213,     6,     7,
       8,     9,  1220,  1227,   220,  1050,   220,   218,    18,    19,
     214,  1229,   214,   882,  1231,  1027,  1599,   221,  1235,   637,
     638,   882,  1248,  1253,  1254,   884,   884,   884,   884,   884,
     884,   884,  1255,   884,   884,  1256,   220,  1525,  1526,  1527,
    1528,  1529,   214,  1513,   217,  1258,  1259,  1265,  1288,  1617,
    1618,  1619,   223,   555,   362,   556,  1273,    34,  1296,   213,
     882,  1361,  1362,  1363,   224,  1364,    35,  1464,  1370,  1377,
    1512,  1365,    36,   557,  1445,  1366,   989,   990,  1378,  1382,
    1383,   558,   559,  1387,   560,   218,  1742,  1465,  1466,   991,
    1393,  1396,  1402,  1404,   561,   562,    37,   992,   221,  1405,
     221,  1406,   213,  1407,  1453,  1629,   217,  1409,   897,  1410,
    1421,  1447,  1422,   993,   220,  1440,   213,  1432,  1453,  1446,
     214,  1630,  1448,  1449,  1450,  1451,  1631,   362,  1632,  1456,
     221,  1460,   213,  1583,   225,  1476,   884,  1484,  1480,  1477,
    1531,  1494,  1495,  1027,   884,  1485,  1518,   218,  1483,   217,
    1524,  1533,  1536,  1539,   898,  1314,   735,  1338,  1347,  1354,
    1011,  1543,   213,   217,   898,   898,  1544,  1315,  1547,  1339,
    1348,  1355,  1549,  1500,  1509,  1515,   220,  1562,  1579,   217,
    1577,  1585,   214,   884,   226,  1501,  1510,  1516,   213,  1591,
     218,   380,  1513,  1593,   224,  1600,   455,  1595,  1602,  -816,
     994,   995,   996,   666,   218,  1604,  1609,  1606,   221,   217,
    1612,    18,    19,   379,  1613,   380,   676,   677,   678,   220,
     218,  1614,  1615,  1624,  1643,   214,   518,   519,  1616,   223,
     520,  1620,  1621,   220,  1709,   217,  1013,   379,  1622,   214,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   220,
     218,  1564,  1658,  1565,  1566,   214,  1589,  1623,  1647,  1655,
      34,  1663,  1659,  1662,   225,  1594,  1671,  1569,  1672,    35,
     221,  1596,  1687,  1571,   689,    36,   218,  1692,  1573,   220,
    1728,  1576,  1743,   690,   691,   214,  1696,   692,   693,   530,
    1500,  1509,  1515,   362,  1726,  1713,  1673,  1729,   213,    37,
    1732,  1749,  1501,  1510,  1516,   220,    70,   917,  1356,  1482,
     223,   214,   223,   221,   226,  -816,   213,  1627,  1748,  1731,
     882,  1626,   135,  1727,   136,   404,   410,   221,  1429,   137,
    1416,   138,  1075,   914,  1641,   139,  1546,  1062,   213,  1206,
    1625,  1537,   223,   221,   457,   217,   459,   213,  1611,  1453,
     745,  1521,  1425,  1427,  1427,  1430,  1598,  1657,  1103,    18,
      19,    18,    19,   217,  1697,  1597,   545,   546,   916,  1262,
    1279,   224,  1665,   221,   140,  1263,   141,  1642,  1109,  1646,
     547,  1264,   548,   549,   550,   217,   218,  1648,  1649,  1650,
    1651,  1652,  1653,  1654,   217,  1656,   724,  1282,  1115,   221,
    1171,  1247,   687,  1389,   218,   551,   552,   553,    34,  1298,
      34,   928,  1403,   906,  1750,   220,   926,    35,   929,    35,
     223,   214,   927,    36,   453,    36,   218,  1681,  1682,  1683,
    1684,  1685,  1686,   220,   889,   218,   728,   362,   733,   214,
     986,   225,   213,   884,   737,   738,     0,    37,     0,    37,
       0,     0,   224,     0,   224,   220,     0,     0,     0,     0,
       0,   214,     0,     0,   220,  1699,     0,  1338,  1347,  1354,
     214,     0,     0,  1710,  1714,  1718,  1722,  1700,     0,  1339,
    1348,  1355,   223,     0,   224,  1711,  1715,  1719,  1723,   217,
       0,   226,     0,     0,  1735,     0,     0,  1736,     0,     0,
       0,  1737,  1738,  1739,  1740,  1500,  1509,  1515,  1744,   221,
       3,     0,  1745,     4,     0,     5,  1746,  1501,  1510,  1516,
    1747,     0,   225,     0,   225,   223,     0,   221,     0,     0,
     218,     0,     0,  1751,     0,     6,     7,     8,     9,   223,
    1752,  1753,  1754,     0,     0,     0,   898,     0,  1327,   221,
     532,     0,   533,     0,   225,   223,     0,     0,   221,   220,
       0,     0,   224,     0,     0,   214,     0,     0,     0,     0,
     534,     0,   226,     0,   226,     0,     0,     0,   535,   536,
     537,   538,     0,     0,  1085,   223,   461,     3,     0,     0,
       4,     0,     5,     0,     0,  1328,  1329,  1330,  1331,     0,
    1332,    18,    19,  1333,   366,   290,   291,   292,   293,   294,
     295,   223,     6,     7,     8,     9,     0,     0,    88,     0,
    1334,  1302,     0,     0,   224,     0,    89,     0,    90,     0,
      91,  1303,   225,    92,    93,    94,  1304,    95,  1305,   466,
    1306,     0,     0,     0,     0,   898,   898,   898,   898,   898,
      34,     0,   898,   221,    18,    19,     0,     0,     0,    35,
       0,     0,     0,     0,     0,    36,     0,   224,  1335,     0,
     469,   270,   271,   272,   273,     0,   898,     0,     0,     0,
       0,   224,   366,     0,     0,    18,    19,     0,     0,    37,
     510,   511,     0,     0,   225,     0,   898,   224,   512,   513,
     514,   515,   516,    34,     0,   386,     0,   471,     0,    73,
       0,     0,    35,   396,   397,   398,   399,    74,    36,    75,
     402,   223,    18,    19,    76,    77,    78,   224,    79,   423,
     425,   427,   429,     0,    34,     0,   432,   225,     0,   223,
       0,   772,    37,    35,   366,  1307,     0,     0,     0,    36,
       0,   225,   454,   224,     0,     0,  1336,   463,   464,   465,
       0,   223,   468,     0,     0,   473,     0,   225,     0,     0,
     223,    34,     0,    37,   150,   151,   152,     0,     0,     0,
      35,   863,     0,     0,     0,   864,    36,   226,     0,   865,
       0,     0,     0,     0,     0,   866,     0,   225,     0,   778,
       0,   226,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     0,     0,     0,     0,    96,     0,   366,  1308,   869,
       0,     0,     0,   225,     0,     0,     0,     0,     0,     0,
      97,     0,  1488,  1309,     0,     0,     0,     0,     0,     0,
       0,  1022,     0,  1024,     0,     0,    98,   226,     0,  1310,
       0,    99,     0,   100,  1311,     0,  1312,     0,     0,  1040,
    1041,     0,  1045,   224,     0,   223,  1047,  1048,     0,     0,
       0,     0,     0,   226,     0,     0,     0,     0,     0,     0,
       0,   224,  1085,  1085,  1085,  1085,  1085,     0,  1085,  1085,
    1080,     0,     0,  1082,     0,  1275,  1275,     0,     0,   711,
     712,   713,     0,   224,     0,     0,    80,     0,     0,  1313,
       0,     0,   224,     0,     0,   781,     0,     0,   782,   783,
       0,    81,     0,   898,   898,   898,   898,   898,   898,   898,
       0,   898,   898,   225,     0,     0,     0,    82,     0,     0,
       0,     0,    83,     3,    84,     0,     4,     0,     5,     0,
       0,   225,  1107,     0,     0,  1108,   784,   785,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,     7,
       8,     9,     0,   225,    50,     0,     0,     0,     0,     0,
       0,  1327,   225,   366,    61,    50,    50,    64,    64,    64,
      68,     0,     0,    50,   518,   519,     0,     0,   520,     0,
     209,   226,     0,     0,     0,     0,     0,   224,   521,   522,
     523,   524,   525,   526,   527,   528,   529,     0,     0,     0,
       0,  1138,  1139,   226,     0,   923,   924,   925,  1328,  1329,
    1330,  1331,   226,  1332,   898,     0,  1333,     0,     0,     0,
       0,     0,   898,     0,    50,     0,     0,   387,    50,    64,
      64,    64,    68,  1334,   937,     0,     0,   530,     0,    50,
       0,   401,   405,   407,    50,   411,    64,    64,   416,     0,
     401,   401,   401,   401,     0,    64,     0,   225,   433,     0,
      50,   898,     0,    64,    64,   945,    68,     0,     0,    64,
       0,     0,     0,     0,     0,     0,     0,   770,     0,     0,
       0,  1335,     0,     0,     0,     0,     0,     0,   474,    50,
      64,    64,     0,   771,    64,   145,    50,     0,     0,     0,
       0,     0,     0,   147,     0,     0,   148,   366,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     0,  1208,
       4,     0,     5,  1211,     0,     0,     0,     0,     0,     0,
       0,     0,  1224,  1225,  1226,     0,     0,  1228,     0,  1230,
     772,     0,     6,     7,     8,     9,     0,     0,     0,  1236,
       0,  1302,     0,     0,   773,     0,     0,     0,     0,     0,
       0,  1303,     0,     0,     0,     0,  1304,     0,  1305,  1336,
    1306,     0,   149,   150,   151,   152,     0,     0,   153,     0,
     774,  1257,     0,     0,   775,     0,     0,     0,   776,     0,
       0,     0,     0,     0,   777,  1271,     0,  1272,   778,     0,
       0,     0,     0,     0,  1278,     0,  1280,     0,     0,     0,
     158,     0,     0,     0,     0,   159,   587,     0,   779,     0,
       0,     0,     0,   161,     0,   588,   162,     0,     0,   163,
     164,     0,     0,     0,   165,     0,     0,   166,     0,   167,
     589,     0,     0,     0,   590,  1703,     0,     0,   591,   592,
       0,     0,     0,   593,   594,   595,   596,   597,     0,     0,
       0,     0,   168,   169,     0,   780,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1307,     0,     0,     0,  -817,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,     0,     0,   200,     0,   545,   546,     0,  1380,
    1381,     0,     0,     0,   781,     0,     0,   782,   783,     0,
     547,   898,   548,   549,   550,     0,     0,     0,     0,  1390,
       0,     0,     0,     0,     0,  1395,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   551,   552,   553,  1308,   201,
     202,     0,     0,     0,     0,   784,   785,     0,  1408,     0,
       0,     0,     0,  1309,     0,     0,     0,     0,   203,     0,
       0,     0,   204,   205,     0,     0,     0,     0,     0,  1310,
       0,     0,   786,   787,  1311,   655,  1312,     0,     0,     0,
       0,   939,     0,     0,     0,  -817,   788,     0,    64,   209,
       0,     3,     0,     0,     4,     0,     5,     0,   946,     0,
     947,     0,   948,     0,   949,     0,     0,     0,     0,   950,
       0,     0,   951,   145,   952,     0,     6,     7,     8,     9,
     146,   147,    64,   284,   148,   285,     0,     0,     0,  1486,
       0,     0,     0,     0,     0,     0,     3,     0,     0,     4,
     286,     5,     0,     0,     0,     0,     0,     0,     0,     0,
     287,   288,     0,     0,     0,   289,     0,     0,     0,     0,
       0,     6,     7,     8,     9,     0,   290,   291,   292,   293,
     294,   295,  1522,     0,  1341,     0,     0,     0,     0,     0,
       0,  1317,     0,     0,     0,   296,  1534,   297,     0,     0,
     149,   150,   151,   152,     0,     0,   153,     0,   154,  1538,
       0,  1318,   155,     0,     0,     0,   156,     0,     0,     0,
       0,     0,   157,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1342,     0,  1343,     0,  1332,     0,   158,  1333,
       0,     0,     0,   159,     0,     0,   160,     0,     0,     0,
       0,   161,     0,     0,   162,     0,  1344,   163,   164,  1319,
       0,     0,   165,     0,    10,   166,     0,   167,     0,     0,
       0,     0,    11,     0,    12,     0,    13,     0,     0,    14,
      15,    16,     0,    17,     0,     0,     0,    18,    19,     0,
     168,   169,     0,   170,   171,   172,   173,     0,     0,     0,
       0,     0,   174,   175,  1345,     0,   176,   177,   298,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
       0,     0,   299,     0,     0,     0,    34,     0,     0,  1605,
       0,     0,     0,     0,     0,    35,     0,   300,     0,     0,
       0,    36,     0,     0,     0,     0,     0,   301,     0,     0,
       0,     0,     0,   302,     0,     0,     0,     0,   303,     0,
       0,     0,     0,     0,     0,    37,     0,   201,   202,     0,
     304,     0,     0,   305,   306,   307,   308,     0,     0,     0,
     309,     0,     0,     0,   310,   311,   203,     0,     0,     0,
     204,   205,     0,     0,     0,     0,     0,     0,     0,   312,
       0,     3,   206,   207,     4,     0,     5,     0,     0,     0,
       0,     0,   313,  1320,   208,     0,     0,   209,     0,     0,
       0,     0,     0,   145,     0,     0,     6,     7,     8,     9,
     146,   147,     0,   284,   148,   285,   973,     0,     0,   974,
     975,   976,   977,   978,   979,   980,   981,   982,   983,   984,
     286,    38,     0,     0,     0,     0,     0,     0,  1704,     0,
     287,   288,     0,     0,     0,   289,    39,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   290,   291,   292,   293,
     294,   295,    40,     0,     0,     0,     0,    41,     0,    42,
       0,  1317,     0,     0,     0,   296,     0,   297,     0,     0,
     149,   150,   151,   152,     0,     0,   153,     0,   154,     0,
       0,  1318,   155,     0,     0,     0,   156,     0,     0,     0,
       0,     0,   157,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,   159,     0,     0,   160,     0,     0,     0,
       0,   161,     0,     0,   162,     0,     0,   163,   164,  1319,
       0,     0,   165,     0,     0,   166,     0,   167,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1167,  1168,  1169,     0,     0,
     168,   169,     0,   170,   171,   172,   173,     0,     0,     0,
       0,     0,   174,   175,     0,     0,   176,   177,   298,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
       0,     0,   299,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   300,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   301,     0,     0,
       0,     0,     0,   302,     0,     0,     0,     0,   303,     0,
       0,     0,     0,     0,     0,     0,     0,   201,   202,     0,
     304,     0,     0,   305,   306,   307,   308,     0,     0,     0,
     309,     0,     0,     0,   310,   311,   203,     0,     0,     0,
     204,   205,     0,     3,     0,     0,     4,     0,     5,   312,
       0,     0,   206,   207,     0,     0,     0,     0,     0,     0,
       0,     0,   313,  1487,   208,   145,     0,   209,     6,     7,
       8,     9,   146,   147,     0,   284,   148,   285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   286,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   287,   288,     0,     0,     0,   289,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   290,   291,
     292,   293,   294,   295,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1317,     0,     0,     0,   296,     0,   297,
       0,     0,   149,   150,   151,   152,     0,     0,   153,     0,
     154,     0,     0,  1318,   155,     0,     0,     0,   156,     0,
       0,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,   159,     0,     0,   160,     0,
       0,     0,     0,   161,     0,     0,   162,     0,     0,   163,
     164,  1319,     0,     0,   165,     0,     0,   166,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,   169,     0,   170,   171,   172,   173,     0,
       0,     0,     0,     0,   174,   175,     0,     0,   176,   177,
     298,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,     0,     0,   299,     0,     0,  1019,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   300,
       0,     0,     0,   771,     0,   145,     0,     0,     0,   301,
       0,     0,     0,   147,     0,   302,   148,     0,     0,     0,
     303,     0,     0,     0,     0,     0,     0,     0,     0,   201,
     202,     0,   304,     0,     0,   305,   306,   307,   308,     0,
       0,     0,   309,   649,     0,     0,   310,   311,   203,     0,
     772,     0,   204,   205,     0,     0,     0,     0,     0,     0,
       0,   312,     0,     0,   206,   207,     0,     0,     0,   650,
       0,     0,   651,     0,   313,  1702,   208,     0,     0,   209,
       0,     0,   149,   150,   151,   152,     0,     0,   153,   652,
     774,     0,     0,     0,   775,     0,     0,     0,   776,     0,
       0,     0,     0,     0,  1020,     0,     0,     0,   778,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,   159,     0,     0,  1021,     0,
       0,     0,     0,   161,     0,     0,   162,     0,     0,   163,
     164,     0,     0,     0,   165,     0,     0,   166,     0,   167,
       0,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   168,   169,     0,   780,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   653,     0,   200,     0,  1081,     0,     0,   201,
     202,     0,     0,     0,   781,     0,     0,   782,   783,   654,
       0,     0,   771,     0,   145,     0,     0,     0,     0,     0,
       0,     0,   147,     0,     0,   148,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   655,     0,     0,     0,   201,
     202,     0,     0,     0,     0,   784,   785,     0,     0,     0,
       0,     0,   732,     0,     0,     0,     0,     0,   203,   772,
       0,     0,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,   786,   787,     0,   655,     0,     0,   650,     0,
       0,   651,     0,     0,     0,     0,   788,     0,     0,   209,
       0,   149,   150,   151,   152,     0,     0,   153,   652,   774,
       0,     0,     0,   775,     0,     0,     0,   776,     0,     0,
       0,     0,     0,  1020,     0,     0,     0,   778,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
       0,     0,     0,     0,   159,     0,     0,  1021,     0,     0,
       0,     0,   161,     0,     0,   162,     0,     0,   163,   164,
       0,     0,     0,   165,     0,     0,   166,     0,   167,     0,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   168,   169,     0,   780,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   653,     0,   200,     0,  1106,     0,     0,   201,   202,
       0,     0,     0,   781,     0,     0,   782,   783,   654,     0,
       0,   771,     0,   145,     0,     0,     0,     0,     0,     0,
       0,   147,     0,     0,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   655,   659,   660,     0,   201,   202,
       0,     0,     0,     0,   784,   785,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   661,   203,   772,     0,
       0,   204,   205,     0,     0,     0,     0,     0,     0,     0,
       0,   786,   787,     0,   655,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   788,     0,     0,   209,     0,
     149,   150,   151,   152,     0,     0,   153,     0,   774,     0,
       0,     0,   775,     0,     0,     0,   776,     0,     0,     0,
       0,     0,  1020,     0,     0,     0,   778,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,   159,     0,   662,  1021,     0,     0,     0,
       0,   161,     0,     0,   162,     0,     0,   163,   164,     0,
       0,     0,   165,     0,     0,   166,     0,   167,     0,   663,
     664,   665,   666,   667,   668,     0,   669,   670,   671,   672,
     673,   674,   675,     0,     0,   676,   677,   678,     0,     0,
     168,   169,     0,   780,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   679,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
       0,     0,   200,     0,  1210,     0,     0,     0,     0,     0,
       0,     0,   781,     0,     0,   782,   783,     0,     0,     0,
     771,   734,   145,     0,     0,     0,     0,     0,     0,     0,
     147,     0,     0,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   659,   660,     0,     0,   201,   202,     0,
       0,     0,     0,   784,   785,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   661,     0,   203,   772,     0,     0,
     204,   205,     0,     0,     0,     0,     0,     0,     0,     0,
     786,   787,     0,   655,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   788,     0,     0,   209,     0,   149,
     150,   151,   152,     0,     0,   153,     0,   774,     0,     0,
       0,   775,     0,     0,     0,   776,     0,     0,     0,   735,
       0,  1020,     0,     0,     0,   778,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,   662,     0,  1021,     0,     0,     0,     0,
     161,     0,     0,   162,     0,     0,   163,   164,     0,     0,
       0,   165,     0,     0,   166,     0,   167,   663,   664,   665,
     666,   667,   668,   736,   669,   670,   671,   672,   673,   674,
     675,     0,     0,   676,   677,   678,     0,     0,     0,   168,
     169,     0,   780,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   679,     0,     0,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   781,     0,     0,   782,   783,   857,   858,   859,   860,
     861,   862,     0,     0,     0,     0,     0,     0,   771,     0,
     842,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   201,   202,     0,     0,
       0,     0,   784,   785,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   203,     0,     0,     0,   204,
     205,     0,     0,     0,     0,   772,     0,     0,     0,   786,
     787,     0,   655,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   788,     0,     0,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   149,   150,   151,
     152,     0,     0,     0,     0,   863,     0,     0,     0,   864,
       0,     0,     0,   865,     0,     0,     0,     0,     0,   866,
       0,     0,     0,   778,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   867,     0,     0,     0,     0,
     868,     0,     0,   869,     0,     0,     0,     0,   870,     0,
       0,   871,     0,     0,   872,   873,     0,     0,     0,   874,
       0,     0,   875,     0,   876,   771,     0,   145,     0,     0,
       0,     0,     0,     0,     0,   147,     0,     0,   148,     0,
       0,     0,     0,     0,     0,     0,     0,   877,   878,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   772,   104,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,     0,     0,   109,   110,     0,
     111,   112,   113,     0,   114,     0,     0,     0,     0,   781,
       0,     0,   782,   783,   149,   150,   151,   152,     0,     0,
     153,     0,   774,     0,     0,     0,   775,     0,     0,     0,
     776,     0,     0,     0,     0,     0,  1020,     0,     0,     0,
     778,     0,     0,   115,     0,   116,   117,   118,     0,     0,
     784,   785,   158,   879,     0,     0,     0,   159,     0,     0,
    1021,     0,     0,     0,     0,   161,     0,     0,   162,     0,
       0,   163,   164,     0,     0,     0,   165,   786,   787,   166,
       0,   167,     0,     0,     0,     0,     0,     0,     0,   313,
       0,   880,     0,     0,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   168,   169,     0,   780,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,     0,     0,   200,     0,     0,   771,
       0,   842,     0,     0,     0,     0,   781,     0,     0,   782,
     783,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     119,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,   202,     0,     0,   120,   772,   784,   785,     0,
     121,   122,   123,   124,     0,     0,     0,     0,     0,     0,
     203,   125,     0,     0,   204,   205,   126,     0,   127,   128,
     771,     0,     0,     0,   786,   787,     0,   655,   149,   150,
     151,   152,     0,     0,     0,     0,   863,     0,   788,     0,
     864,   209,     0,     0,   865,     0,     0,     0,     0,     0,
     866,     0,     0,     0,   778,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   867,   772,     0,     0,
       0,   868,     0,     0,   869,     0,     0,     0,     0,   870,
       0,     0,   871,     0,     0,   872,   873,     0,     0,     0,
     874,     0,     0,   875,     0,   876,     0,     0,     0,   149,
     150,   151,   152,     0,     0,     0,     0,   863,     0,     0,
       0,   864,     0,     0,     0,   865,     0,     0,   877,   878,
       0,   866,     0,     0,     0,   778,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   867,     0,     0,
       0,     0,   868,     0,     0,   869,     0,     0,     0,     0,
     870,     0,     0,   871,     0,     0,   872,   873,     0,     0,
       0,   874,     0,     0,   875,     0,   876,     0,     0,     0,
     781,     0,     0,   782,   783,     0,     0,     0,     0,     0,
       0,     0,     0,   771,     0,     0,     0,     0,     0,   877,
     878,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   784,   785,     0,   879,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     772,     0,     0,     0,     0,     0,     0,     0,   786,   787,
       0,   781,     0,     0,   782,   783,     0,     0,     0,     0,
     313,     0,   880,     0,     0,   209,     0,     0,     0,     0,
       0,     0,   149,   150,   151,   152,     0,     0,     0,     0,
     863,     0,     0,     0,   864,     0,     0,     0,   865,     0,
       0,     0,   784,   785,   866,   879,     0,     0,   778,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     867,     0,     0,     0,     0,   868,     0,     0,   869,   786,
     787,     0,     0,   870,     0,     0,   871,     0,     0,   872,
     873,   313,     0,   880,   874,     0,   209,   875,     0,   876,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   877,   878,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
       0,   146,   147,     0,   284,   148,   285,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   286,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   287,   288,     0,   781,     0,   289,   782,   783,     0,
       0,     0,     0,     0,     0,     0,     0,   290,   291,   292,
     293,   294,   295,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   296,     0,   297,     0,
       0,   149,   150,   151,   152,   784,   785,   153,   879,   154,
       0,     0,     0,   155,     0,     0,     0,   156,     0,     0,
       0,     0,     0,   157,     0,     0,     0,     0,     0,     0,
       0,     0,   786,   787,     0,     0,     0,     0,     0,   158,
       0,     0,     0,     0,   159,     0,   880,   160,     0,   209,
       0,     0,   161,     0,     0,   162,     0,     0,   163,   164,
       0,     0,     0,   165,     0,     0,   166,     0,   167,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   168,   169,     0,   170,   171,   172,   173,     0,     0,
       0,     0,     0,   174,   175,     0,     0,   176,   177,   298,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,     0,     0,   299,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   300,     0,
       0,     0,   145,     0,     0,     0,     0,     0,   301,   146,
     147,     0,     0,   148,   302,     0,     0,     0,     0,   303,
       0,     0,     0,     0,     0,     0,     0,     0,   201,   202,
       0,   304,     0,     0,   305,   306,   307,   308,     0,     0,
       0,   309,     0,     0,     0,   310,   311,   203,     0,     0,
       0,   204,   205,     0,     0,     0,     0,     0,     0,     0,
     312,     0,     0,   206,   207,     0,     0,     0,     0,     0,
       0,     0,     0,   313,     0,   208,     0,     0,   209,   149,
     150,   151,   152,     0,     0,   153,     0,   154,     0,     0,
       0,   155,     0,     0,     0,   156,     0,     0,     0,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,     0,     0,   160,     0,     0,     0,     0,
     161,     0,     0,   162,     0,     0,   163,   164,     0,     0,
       0,   165,     0,   145,   166,     0,   167,     0,     0,     0,
     146,   147,     0,     0,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   168,
     169,     0,   170,   171,   172,   173,     0,     0,     0,     0,
       0,   174,   175,     0,     0,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,   200,     0,     0,     0,     0,     0,     0,     0,     0,
     149,   150,   151,   152,     0,     0,   153,     0,   154,     0,
       0,     0,   155,     0,     0,     0,   156,     0,     0,     0,
       0,     0,   157,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   201,   202,   158,     0,
       0,     0,     0,   159,     0,     0,   160,     0,     0,     0,
       0,   161,     0,     0,   162,   203,     0,   163,   164,   204,
     205,     0,   165,     0,     0,   166,     0,   167,     0,     0,
       0,   206,   207,     0,     0,     0,     0,     0,     0,     0,
       0,   313,     0,   208,     0,     0,   209,     0,     0,     0,
     168,   169,     0,   170,   171,   172,   173,     0,     0,     0,
       0,     0,   174,   175,     0,     0,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
       0,     0,   200,     0,     0,     0,     0,   145,     0,     0,
       0,     0,     0,     0,     0,   147,     0,     0,   148,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   201,   202,     0,
       0,     0,   772,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   203,     0,     0,     0,
     204,   205,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   206,   207,   149,   150,   151,   152,     0,     0,
     153,     0,   774,     0,   208,     0,   775,   209,     0,     0,
     776,     0,     0,     0,     0,     0,  1020,     0,     0,     0,
     778,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,   159,     0,     0,
    1021,     0,     0,     0,     0,   161,     0,     0,   162,     0,
       0,   163,   164,     0,     0,     0,   165,     0,     0,   166,
       0,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   168,   169,     0,   780,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,     0,     0,   200,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   781,     0,     0,   782,
     783,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,   202,     0,     0,     0,     0,   784,   785,     0,
       0,     0,     2,     3,     0,     0,     4,     0,     5,     0,
     203,     0,     0,     0,   204,   205,     0,     0,     0,     0,
       0,     0,     0,     0,   786,   787,     0,   655,     6,     7,
       8,     9,     0,     0,     0,     0,     0,    10,   788,     0,
       0,   209,     0,     0,     0,    11,     0,    12,     0,    13,
       0,     0,    14,    15,    16,     0,    17,     0,     0,     0,
      18,    19,    20,     0,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,   772,
       0,     0,     0,     0,     0,     0,     0,   290,   291,   292,
     293,   294,   295,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -309,     0,     0,     0,     0,     0,    34,
       0,   149,   150,   151,   152,     0,     0,     0,    35,   863,
       0,     0,     0,   864,    36,     0,     0,   865,     0,     0,
       0,     0,     0,   866,     0,     0,     0,   778,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,   867,
       0,     0,     0,     0,   868,     0,     0,   869,     0,     0,
       0,     0,   870,     0,     0,   871,     0,     0,   872,   873,
       0,     0,     0,   874,     0,     0,   875,   772,   876,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   877,   878,     0,     0,     0,     0,     0,     0,   149,
     150,   151,   152,     0,     0,     0,     0,   863,     0,     0,
       0,   864,     0,     0,     0,   865,     0,     0,     0,     0,
       0,   866,     0,     0,    38,   778,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   867,     0,    39,
       0,     0,   868,   781,     0,   869,   782,   783,     0,     0,
     870,     0,     0,   871,     0,    40,   872,   873,     0,     0,
      41,   874,    42,     0,   875,     0,   876,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   784,   785,     0,   879,     0,   877,
     878,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   786,   787,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   880,     0,     0,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   781,     0,     0,   782,   783,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   784,   785,     0,   879,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   786,
     787,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   880,     0,     0,   209
};

static const yytype_int16 yycheck[] =
{
       1,    66,     3,   389,   392,    30,   204,    30,   391,   316,
     390,   388,     1,   315,   344,   338,   750,   916,   358,    32,
     926,   928,    52,    66,   929,   717,   358,    52,   368,   369,
     927,   208,   358,    63,   414,  1207,   368,   369,    63,  1146,
    1150,   284,  1151,  1051,  1052,    46,    15,    16,  1152,  1057,
       5,   431,    30,    54,  1153,  1112,     5,    58,  1285,  1363,
       7,   753,     7,  1361,   106,     7,   108,   109,   311,   761,
     112,  1238,   114,   765,    52,   117,   118,     7,    43,   121,
     122,   123,   124,    94,    52,    63,   128,  1362,   331,   131,
     132,     1,    23,    30,     4,    63,     6,   139,    23,  1114,
     855,    23,   788,  1341,   851,    32,   101,    76,    77,    78,
    1193,  1194,   100,   852,  1122,    52,    26,    27,    28,    29,
     853,   358,    30,    92,    93,    94,    63,  1344,    30,   122,
    1505,   368,   369,   102,  1216,    22,   849,   850,  1214,   142,
     101,   110,   111,   101,    52,   680,    82,   116,   178,    55,
      52,   123,    13,   146,    20,    63,   287,     8,    76,    77,
      20,    63,     4,   156,  1240,  1241,   297,   102,   137,   138,
      55,    55,   141,    24,    60,    55,   108,   109,   140,   204,
     112,    91,   114,   208,    56,   117,   118,   111,    87,   121,
     122,   123,   124,    47,   156,   101,   128,  1086,  1087,   131,
     132,    52,   737,    56,  1093,   299,     1,   139,   302,     4,
      96,     6,    87,   100,   101,    90,    30,   101,    55,     1,
     130,   101,     4,    55,     6,    86,   204,   230,   231,     8,
     208,    26,    27,    28,    29,   101,    82,   929,    52,   163,
     164,   101,   255,   111,    26,    27,    28,    29,   261,    63,
     293,   294,  1359,  1329,  1330,   131,     7,     8,     9,   101,
      87,   101,   198,    90,   101,     8,  1342,   204,   298,   101,
    1025,   208,    47,    52,   712,   713,   248,    87,   266,     4,
    1655,     6,   209,   232,    82,    51,   316,   163,   164,   250,
     166,   316,   250,   358,   101,    87,   204,    48,   247,    50,
     208,   344,   204,   368,   369,    87,   208,  1389,    59,    52,
     313,   322,    94,    64,   263,    45,   111,    68,  1545,   268,
      87,   108,   315,   233,   321,   390,     1,   108,    87,     4,
     321,     6,   327,   358,  1572,   122,  1028,  1029,   316,  1094,
     239,   122,   241,   368,   369,   213,   214,   390,   130,   414,
      43,    26,    27,    28,    29,   385,  1413,   322,  1575,     1,
     385,  1533,     4,   322,     6,    40,   431,    42,   323,  1673,
     400,   414,  1387,  1671,   323,   400,   323,  1544,   323,   316,
     129,   323,   164,  1130,    26,    27,    28,    29,   431,  1397,
     204,   322,  1131,   323,   208,   198,   327,  1672,     1,  1132,
     322,     4,   327,     6,   446,   327,  1092,   385,   316,   327,
     750,  1419,  1495,   323,   316,  1128,  1129,   385,   303,   304,
     247,   322,   400,    26,    27,    28,    29,  1503,    30,   239,
     305,   241,   400,   320,   306,   307,   308,    40,   233,    42,
     327,   287,   288,   289,   124,    87,   256,   239,   385,   241,
      52,   233,    94,   306,   307,   308,   358,   322,   209,   248,
      82,    63,   327,   400,   159,   162,   368,   369,     1,   149,
     167,     4,   239,     6,   241,   264,   445,   385,   305,   802,
     239,   298,   241,   385,  1541,   923,   924,   925,   130,   287,
     288,   289,   400,    26,    27,    28,    29,   198,   400,   937,
     122,   307,   316,  1613,  1238,  1614,    39,   111,   249,   122,
     479,  1615,  1246,   750,   446,    82,   856,  1616,   100,    36,
      37,    38,   164,   100,   146,   855,   724,   131,   323,   142,
     856,   248,    44,   146,    46,     5,    48,    49,     8,   138,
     144,   323,   293,   294,    56,    57,   297,    75,   880,   266,
     267,  1285,   151,   127,    87,   122,    89,   131,    91,    79,
     900,    94,  1669,   258,   259,   260,   261,   262,   167,   100,
      30,   385,   247,   124,   900,    95,   140,    89,   111,   146,
     108,   145,     1,    60,    61,     4,   400,     6,    65,   163,
     164,   233,    52,   113,   122,   248,     1,   131,   149,     4,
    1608,     6,   204,    63,   109,   110,   208,    26,    27,    28,
      29,   111,   849,   850,   851,   852,   853,   230,   231,   856,
      39,    26,    27,    28,    29,     5,   159,   127,     8,   163,
     164,   149,   132,   133,   248,    40,   111,    42,    82,   167,
      30,   159,   160,   880,   247,     4,     7,   122,   323,   124,
     401,    22,   281,   404,    25,   259,   407,   305,   192,    20,
     411,    22,    52,   900,    43,   416,   183,   142,    87,    17,
      89,   146,    91,    63,   149,    94,    18,   854,   101,    43,
      44,   323,  1690,   282,    36,   750,   159,    20,   216,    22,
      30,     1,   111,   326,     4,  1025,     6,   710,   198,   724,
     313,    50,   125,   126,   209,   210,     1,    50,   213,     4,
       1,     6,    52,     4,   316,     6,    26,    27,    28,    29,
     323,   322,   197,    63,   322,   750,   199,   200,   201,   322,
     481,    26,    27,    28,    29,    26,    27,    28,    29,   111,
     159,   113,   114,   115,   204,    36,   724,   322,   208,     1,
     322,  1053,     4,    55,     6,   230,   231,   124,    12,    43,
       4,  1004,     6,   788,  1094,   163,   164,  1666,  1674,  1676,
     319,   320,  1677,   140,    26,    27,    28,    29,  1675,    15,
      16,    91,   149,   385,  1107,    43,   209,   724,   155,   156,
     323,   856,    43,    37,   247,  1127,    15,    16,   400,   252,
     253,  1133,     7,  1135,  1136,   100,   229,   230,   104,   105,
     106,  1545,   855,     8,   204,   268,   724,    71,   208,   101,
     130,    75,   724,   100,   849,   850,   851,   852,   853,   854,
       4,   856,     6,  1031,     8,   900,    90,    91,   313,    91,
     328,     0,   247,   249,   250,     4,     1,     6,   750,     4,
       4,     6,     6,   107,     8,   880,   316,    83,    84,    85,
       1,    87,   328,     4,   204,     6,   298,     4,   208,     6,
       7,    26,    27,    28,    29,   900,   854,    20,   130,    22,
      58,    59,   136,   298,    39,    26,    27,    28,    29,   143,
    1127,  1128,  1129,  1130,  1131,  1132,  1133,   325,  1135,  1136,
     266,   267,   903,   316,   323,   906,  1246,   109,   110,   111,
     724,   306,   307,   308,  1112,  1222,  1114,   854,   323,   134,
     135,   136,   137,   233,   249,   385,   316,   266,   267,   107,
     264,    86,    87,    88,    89,    82,    91,    23,   116,    94,
     400,    23,  1244,   100,   122,  1285,   854,   849,   850,   851,
     852,   853,   854,    50,   856,  1278,   111,  1280,    15,    16,
     101,   102,   103,    50,     1,   109,   110,     4,   146,     6,
      50,   266,   267,   291,   292,   293,   316,  1284,   880,   109,
     110,   233,  1025,   111,    50,  1677,  1678,    94,    82,    26,
      27,    28,    29,     4,     5,   385,   124,    50,   900,   292,
     293,  1238,   100,   131,   159,   100,  1031,   109,   110,  1246,
     400,     1,   100,   323,     4,   100,     6,   101,   102,   103,
     127,   149,   100,  1309,  1310,  1311,  1312,   155,   323,  1094,
      92,    93,   323,    41,    42,    17,    26,    27,    28,    29,
     854,    18,  1428,  1431,     5,   385,  1429,   326,  1285,  1426,
      87,  1094,     7,  1031,   287,   288,   289,    94,  1099,  1100,
     400,  1086,  1087,  1088,  1089,  1090,     7,  1092,  1093,     7,
       7,   323,   100,   100,  1099,  1100,  1456,   184,   185,   186,
     187,   188,   189,    97,    98,    99,   100,  1112,     5,  1114,
     322,   842,   247,   130,  1031,   846,     7,     7,     7,    17,
    1480,   326,  1127,  1128,  1129,  1130,  1131,  1132,  1133,     8,
    1135,  1136,     1,    18,  1144,     4,   100,     6,   322,  1144,
     100,   111,   724,  1031,   322,   322,   322,   164,   113,  1031,
    1436,  1437,  1438,  1439,  1112,   322,  1114,    26,    27,    28,
      29,  1142,  1143,   128,  1145,  1146,  1147,  1433,  1434,  1435,
     100,   100,   100,   100,  1143,   100,  1145,  1146,  1147,   101,
       1,   100,   322,     4,   149,     6,  1144,   100,   323,   100,
     155,   100,   299,     1,   100,  1112,     4,  1114,     6,   100,
     322,  1246,   323,   125,   126,    26,    27,    28,    29,  1387,
     322,     5,  1222,    43,   100,     8,   233,  1222,    26,    27,
      28,    29,   100,   100,  1112,  1545,  1114,  1144,    58,    59,
    1112,    50,  1114,  1238,   100,  1413,  1523,  1031,    41,   204,
     205,  1246,   145,   111,   111,  1127,  1128,  1129,  1130,  1131,
    1132,  1133,    68,  1135,  1136,   111,  1144,   275,   276,   277,
     278,   279,  1144,   233,  1222,     5,   325,   100,   325,  1555,
    1556,  1557,   854,   111,  1284,   113,     8,   107,   100,  1284,
    1285,   322,   322,   322,   724,     7,   116,   209,   100,   250,
     111,   329,   122,   131,  1317,   329,   109,   110,   100,     5,
     101,   139,   140,   322,   142,  1222,   323,   229,   230,   122,
     269,    41,   249,     7,   152,   153,   146,   130,  1112,   101,
    1114,   101,  1327,   101,  1327,   247,  1284,     5,  1545,   161,
     100,    96,    37,   146,  1222,  1316,  1341,   101,  1341,   101,
    1222,   263,  1323,  1324,  1325,  1326,   268,  1357,   270,   321,
    1144,   100,  1357,   323,   724,  1336,  1238,   101,   321,  1340,
     265,   100,   100,  1541,  1246,   321,   100,  1284,  1349,  1327,
     323,   100,   100,    82,   358,  1356,   185,  1358,  1359,  1360,
     249,   323,  1387,  1341,   368,   369,     5,  1356,   183,  1358,
    1359,  1360,   100,  1374,  1375,  1376,  1284,    40,   322,  1357,
     147,   321,  1284,  1285,   724,  1374,  1375,  1376,  1413,   100,
    1327,  1456,   233,   100,   854,   265,    43,   102,   100,    82,
     233,   234,   235,   236,  1341,   250,    38,   323,  1222,  1387,
     322,    58,    59,  1456,   322,  1480,   249,   250,   251,  1327,
    1357,   322,   322,   101,   101,  1327,   109,   110,   322,  1031,
     113,   322,   322,  1341,   323,  1413,   264,  1480,   322,  1341,
     123,   124,   125,   126,   127,   128,   129,   130,   131,  1357,
    1387,  1452,   323,  1454,  1455,  1357,  1498,   322,   322,   130,
     107,   323,   100,   100,   854,  1507,   322,  1468,   322,   116,
    1284,  1513,   100,  1474,   193,   122,  1413,   101,  1479,  1387,
     100,  1482,   323,   202,   203,  1387,   249,   206,   207,   172,
    1491,  1492,  1493,  1523,   321,   323,   322,   100,  1523,   146,
       5,   100,  1491,  1492,  1493,  1413,    20,   387,  1149,  1345,
    1112,  1413,  1114,  1327,   854,   198,  1541,  1570,  1726,  1690,
    1545,  1568,    43,  1680,    45,    89,    91,  1341,  1305,    50,
    1283,    52,   766,   384,  1577,    56,  1419,   758,  1563,  1013,
    1563,  1404,  1144,  1357,    43,  1523,    43,  1572,  1549,  1572,
     303,  1379,  1303,  1304,  1305,  1306,  1520,  1597,   823,    58,
      59,    58,    59,  1541,  1665,  1519,   109,   110,   386,  1088,
    1105,  1031,  1611,  1387,    95,  1089,    97,  1578,   838,  1580,
     123,  1090,   125,   126,   127,  1563,  1523,  1588,  1589,  1590,
    1591,  1592,  1593,  1594,  1572,  1596,   286,  1110,   847,  1413,
     956,  1057,   204,  1223,  1541,   148,   149,   150,   107,  1136,
     107,   398,  1244,   369,  1733,  1523,   396,   116,   399,   116,
    1222,  1523,   397,   122,   119,   122,  1563,  1628,  1629,  1630,
    1631,  1632,  1633,  1541,   358,  1572,   294,  1667,   298,  1541,
     618,  1031,  1667,  1545,   299,   299,    -1,   146,    -1,   146,
      -1,    -1,  1112,    -1,  1114,  1563,    -1,    -1,    -1,    -1,
      -1,  1563,    -1,    -1,  1572,  1666,    -1,  1668,  1669,  1670,
    1572,    -1,    -1,  1674,  1675,  1676,  1677,  1666,    -1,  1668,
    1669,  1670,  1284,    -1,  1144,  1674,  1675,  1676,  1677,  1667,
      -1,  1031,    -1,    -1,  1695,    -1,    -1,  1698,    -1,    -1,
      -1,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,  1523,
       1,    -1,  1713,     4,    -1,     6,  1717,  1706,  1707,  1708,
    1721,    -1,  1112,    -1,  1114,  1327,    -1,  1541,    -1,    -1,
    1667,    -1,    -1,  1734,    -1,    26,    27,    28,    29,  1341,
    1741,  1742,  1743,    -1,    -1,    -1,   750,    -1,    39,  1563,
     111,    -1,   113,    -1,  1144,  1357,    -1,    -1,  1572,  1667,
      -1,    -1,  1222,    -1,    -1,  1667,    -1,    -1,    -1,    -1,
     131,    -1,  1112,    -1,  1114,    -1,    -1,    -1,   139,   140,
     141,   142,    -1,    -1,   788,  1387,    43,     1,    -1,    -1,
       4,    -1,     6,    -1,    -1,    86,    87,    88,    89,    -1,
      91,    58,    59,    94,  1144,    76,    77,    78,    79,    80,
      81,  1413,    26,    27,    28,    29,    -1,    -1,    35,    -1,
     111,    35,    -1,    -1,  1284,    -1,    43,    -1,    45,    -1,
      47,    45,  1222,    50,    51,    52,    50,    54,    52,    43,
      54,    -1,    -1,    -1,    -1,   849,   850,   851,   852,   853,
     107,    -1,   856,  1667,    58,    59,    -1,    -1,    -1,   116,
      -1,    -1,    -1,    -1,    -1,   122,    -1,  1327,   159,    -1,
      43,    39,    40,    41,    42,    -1,   880,    -1,    -1,    -1,
      -1,  1341,  1222,    -1,    -1,    58,    59,    -1,    -1,   146,
     109,   110,    -1,    -1,  1284,    -1,   900,  1357,   117,   118,
     119,   120,   121,   107,    -1,    73,    -1,    43,    -1,    35,
      -1,    -1,   116,    81,    82,    83,    84,    43,   122,    45,
      88,  1523,    58,    59,    50,    51,    52,  1387,    54,    97,
      98,    99,   100,    -1,   107,    -1,   104,  1327,    -1,  1541,
      -1,    68,   146,   116,  1284,   159,    -1,    -1,    -1,   122,
      -1,  1341,   120,  1413,    -1,    -1,   247,   125,   126,   127,
      -1,  1563,   130,    -1,    -1,   133,    -1,  1357,    -1,    -1,
    1572,   107,    -1,   146,   101,   102,   103,    -1,    -1,    -1,
     116,   108,    -1,    -1,    -1,   112,   122,  1327,    -1,   116,
      -1,    -1,    -1,    -1,    -1,   122,    -1,  1387,    -1,   126,
      -1,  1341,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     146,    -1,    -1,    -1,    -1,   232,    -1,  1357,   232,   146,
      -1,    -1,    -1,  1413,    -1,    -1,    -1,    -1,    -1,    -1,
     247,    -1,   323,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   721,    -1,   723,    -1,    -1,   263,  1387,    -1,   263,
      -1,   268,    -1,   270,   268,    -1,   270,    -1,    -1,   739,
     740,    -1,   742,  1523,    -1,  1667,   746,   747,    -1,    -1,
      -1,    -1,    -1,  1413,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1541,  1086,  1087,  1088,  1089,  1090,    -1,  1092,  1093,
     770,    -1,    -1,   773,    -1,  1099,  1100,    -1,    -1,   267,
     268,   269,    -1,  1563,    -1,    -1,   232,    -1,    -1,   323,
      -1,    -1,  1572,    -1,    -1,   242,    -1,    -1,   245,   246,
      -1,   247,    -1,  1127,  1128,  1129,  1130,  1131,  1132,  1133,
      -1,  1135,  1136,  1523,    -1,    -1,    -1,   263,    -1,    -1,
      -1,    -1,   268,     1,   270,    -1,     4,    -1,     6,    -1,
      -1,  1541,   832,    -1,    -1,   835,   283,   284,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    -1,  1563,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,  1572,  1523,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    20,   109,   110,    -1,    -1,   113,    -1,
     327,  1541,    -1,    -1,    -1,    -1,    -1,  1667,   123,   124,
     125,   126,   127,   128,   129,   130,   131,    -1,    -1,    -1,
      -1,   901,   902,  1563,    -1,   393,   394,   395,    86,    87,
      88,    89,  1572,    91,  1238,    -1,    94,    -1,    -1,    -1,
      -1,    -1,  1246,    -1,    71,    -1,    -1,    74,    75,    76,
      77,    78,    79,   111,   422,    -1,    -1,   172,    -1,    86,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    -1,
      97,    98,    99,   100,    -1,   102,    -1,  1667,   105,    -1,
     107,  1285,    -1,   110,   111,   453,   113,    -1,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,
      -1,   159,    -1,    -1,    -1,    -1,    -1,    -1,   135,   136,
     137,   138,    -1,    21,   141,    23,   143,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    34,  1667,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,  1019,
       4,    -1,     6,  1023,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1032,  1033,  1034,    -1,    -1,  1037,    -1,  1039,
      68,    -1,    26,    27,    28,    29,    -1,    -1,    -1,  1049,
      -1,    35,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    52,   247,
      54,    -1,   100,   101,   102,   103,    -1,    -1,   106,    -1,
     108,  1081,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,
      -1,    -1,    -1,    -1,   122,  1095,    -1,  1097,   126,    -1,
      -1,    -1,    -1,    -1,  1104,    -1,  1106,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,   143,   131,    -1,   146,    -1,
      -1,    -1,    -1,   151,    -1,   140,   154,    -1,    -1,   157,
     158,    -1,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,
     155,    -1,    -1,    -1,   159,   323,    -1,    -1,   163,   164,
      -1,    -1,    -1,   168,   169,   170,   171,   172,    -1,    -1,
      -1,    -1,   190,   191,    -1,   193,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   159,    -1,    -1,    -1,    82,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,    -1,    -1,   232,    -1,   109,   110,    -1,  1209,
    1210,    -1,    -1,    -1,   242,    -1,    -1,   245,   246,    -1,
     123,  1545,   125,   126,   127,    -1,    -1,    -1,    -1,  1229,
      -1,    -1,    -1,    -1,    -1,  1235,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   148,   149,   150,   232,   277,
     278,    -1,    -1,    -1,    -1,   283,   284,    -1,  1258,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,   296,    -1,
      -1,    -1,   300,   301,    -1,    -1,    -1,    -1,    -1,   263,
      -1,    -1,   310,   311,   268,   313,   270,    -1,    -1,    -1,
      -1,   438,    -1,    -1,    -1,   198,   324,    -1,   445,   327,
      -1,     1,    -1,    -1,     4,    -1,     6,    -1,   455,    -1,
     457,    -1,   459,    -1,   461,    -1,    -1,    -1,    -1,   466,
      -1,    -1,   469,    23,   471,    -1,    26,    27,    28,    29,
      30,    31,   479,    33,    34,    35,    -1,    -1,    -1,   323,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,     4,
      50,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    -1,    76,    77,    78,    79,
      80,    81,  1382,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    -1,    95,  1396,    97,    -1,    -1,
     100,   101,   102,   103,    -1,    -1,   106,    -1,   108,  1409,
      -1,   111,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87,    -1,    89,    -1,    91,    -1,   138,    94,
      -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,
      -1,   151,    -1,    -1,   154,    -1,   111,   157,   158,   159,
      -1,    -1,   162,    -1,    35,   165,    -1,   167,    -1,    -1,
      -1,    -1,    43,    -1,    45,    -1,    47,    -1,    -1,    50,
      51,    52,    -1,    54,    -1,    -1,    -1,    58,    59,    -1,
     190,   191,    -1,   193,   194,   195,   196,    -1,    -1,    -1,
      -1,    -1,   202,   203,   159,    -1,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,   232,    -1,    -1,    -1,   107,    -1,    -1,  1539,
      -1,    -1,    -1,    -1,    -1,   116,    -1,   247,    -1,    -1,
      -1,   122,    -1,    -1,    -1,    -1,    -1,   257,    -1,    -1,
      -1,    -1,    -1,   263,    -1,    -1,    -1,    -1,   268,    -1,
      -1,    -1,    -1,    -1,    -1,   146,    -1,   277,   278,    -1,
     280,    -1,    -1,   283,   284,   285,   286,    -1,    -1,    -1,
     290,    -1,    -1,    -1,   294,   295,   296,    -1,    -1,    -1,
     300,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   309,
      -1,     1,   312,   313,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,   322,   323,   324,    -1,    -1,   327,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    26,    27,    28,    29,
      30,    31,    -1,    33,    34,    35,   170,    -1,    -1,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
      50,   232,    -1,    -1,    -1,    -1,    -1,    -1,   323,    -1,
      60,    61,    -1,    -1,    -1,    65,   247,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,   263,    -1,    -1,    -1,    -1,   268,    -1,   270,
      -1,    91,    -1,    -1,    -1,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,
      -1,   111,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,
      -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,   159,
      -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   942,   943,   944,    -1,    -1,
     190,   191,    -1,   193,   194,   195,   196,    -1,    -1,    -1,
      -1,    -1,   202,   203,    -1,    -1,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   257,    -1,    -1,
      -1,    -1,    -1,   263,    -1,    -1,    -1,    -1,   268,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,   278,    -1,
     280,    -1,    -1,   283,   284,   285,   286,    -1,    -1,    -1,
     290,    -1,    -1,    -1,   294,   295,   296,    -1,    -1,    -1,
     300,   301,    -1,     1,    -1,    -1,     4,    -1,     6,   309,
      -1,    -1,   312,   313,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   322,   323,   324,    23,    -1,   327,    26,    27,
      28,    29,    30,    31,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,    -1,    -1,   106,    -1,
     108,    -1,    -1,   111,   112,    -1,    -1,    -1,   116,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,   143,    -1,    -1,   146,    -1,
      -1,    -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,
     158,   159,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   190,   191,    -1,   193,   194,   195,   196,    -1,
      -1,    -1,    -1,    -1,   202,   203,    -1,    -1,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,    -1,    -1,   232,    -1,    -1,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,
      -1,    -1,    -1,    21,    -1,    23,    -1,    -1,    -1,   257,
      -1,    -1,    -1,    31,    -1,   263,    34,    -1,    -1,    -1,
     268,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,
     278,    -1,   280,    -1,    -1,   283,   284,   285,   286,    -1,
      -1,    -1,   290,   101,    -1,    -1,   294,   295,   296,    -1,
      68,    -1,   300,   301,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   309,    -1,    -1,   312,   313,    -1,    -1,    -1,   127,
      -1,    -1,   130,    -1,   322,   323,   324,    -1,    -1,   327,
      -1,    -1,   100,   101,   102,   103,    -1,    -1,   106,   147,
     108,    -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,   143,    -1,    -1,   146,    -1,
      -1,    -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,
     158,    -1,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,
      -1,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   190,   191,    -1,   193,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   270,    -1,   232,    -1,     5,    -1,    -1,   277,
     278,    -1,    -1,    -1,   242,    -1,    -1,   245,   246,   287,
      -1,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   313,    -1,    -1,    -1,   277,
     278,    -1,    -1,    -1,    -1,   283,   284,    -1,    -1,    -1,
      -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,   296,    68,
      -1,    -1,   300,   301,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   310,   311,    -1,   313,    -1,    -1,   127,    -1,
      -1,   130,    -1,    -1,    -1,    -1,   324,    -1,    -1,   327,
      -1,   100,   101,   102,   103,    -1,    -1,   106,   147,   108,
      -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,    -1,   126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,
      -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,
      -1,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   190,   191,    -1,   193,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   270,    -1,   232,    -1,     5,    -1,    -1,   277,   278,
      -1,    -1,    -1,   242,    -1,    -1,   245,   246,   287,    -1,
      -1,    21,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   313,   109,   110,    -1,   277,   278,
      -1,    -1,    -1,    -1,   283,   284,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   130,   296,    68,    -1,
      -1,   300,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   310,   311,    -1,   313,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   324,    -1,    -1,   327,    -1,
     100,   101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,
      -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,   126,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,   143,    -1,   209,   146,    -1,    -1,    -1,
      -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,
      -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,   233,
     234,   235,   236,   237,   238,    -1,   240,   241,   242,   243,
     244,   245,   246,    -1,    -1,   249,   250,   251,    -1,    -1,
     190,   191,    -1,   193,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   270,    -1,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,   232,    -1,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   242,    -1,    -1,   245,   246,    -1,    -1,    -1,
      21,    87,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   109,   110,    -1,    -1,   277,   278,    -1,
      -1,    -1,    -1,   283,   284,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   130,    -1,   296,    68,    -1,    -1,
     300,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     310,   311,    -1,   313,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   324,    -1,    -1,   327,    -1,   100,
     101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,    -1,
      -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,   185,
      -1,   122,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,
      -1,    -1,   143,   209,    -1,   146,    -1,    -1,    -1,    -1,
     151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,    -1,
      -1,   162,    -1,    -1,   165,    -1,   167,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,    -1,    -1,   249,   250,   251,    -1,    -1,    -1,   190,
     191,    -1,   193,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   270,    -1,    -1,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,    -1,
      -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   242,    -1,    -1,   245,   246,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   277,   278,    -1,    -1,
      -1,    -1,   283,   284,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,   300,
     301,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,   310,
     311,    -1,   313,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   324,    -1,    -1,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,   112,
      -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,
      -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,
     143,    -1,    -1,   146,    -1,    -1,    -1,    -1,   151,    -1,
      -1,   154,    -1,    -1,   157,   158,    -1,    -1,    -1,   162,
      -1,    -1,   165,    -1,   167,    21,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,   191,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    -1,    -1,    49,    50,    -1,
      52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,   246,   100,   101,   102,   103,    -1,    -1,
     106,    -1,   108,    -1,    -1,    -1,   112,    -1,    -1,    -1,
     116,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,
     126,    -1,    -1,    95,    -1,    97,    98,    99,    -1,    -1,
     283,   284,   138,   286,    -1,    -1,    -1,   143,    -1,    -1,
     146,    -1,    -1,    -1,    -1,   151,    -1,    -1,   154,    -1,
      -1,   157,   158,    -1,    -1,    -1,   162,   310,   311,   165,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   322,
      -1,   324,    -1,    -1,   327,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   190,   191,    -1,   193,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,    -1,    -1,   232,    -1,    -1,    21,
      -1,    23,    -1,    -1,    -1,    -1,   242,    -1,    -1,   245,
     246,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     232,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   277,   278,    -1,    -1,   247,    68,   283,   284,    -1,
     252,   253,   254,   255,    -1,    -1,    -1,    -1,    -1,    -1,
     296,   263,    -1,    -1,   300,   301,   268,    -1,   270,   271,
      21,    -1,    -1,    -1,   310,   311,    -1,   313,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,   108,    -1,   324,    -1,
     112,   327,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   138,    68,    -1,    -1,
      -1,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,   151,
      -1,    -1,   154,    -1,    -1,   157,   158,    -1,    -1,    -1,
     162,    -1,    -1,   165,    -1,   167,    -1,    -1,    -1,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,
      -1,   112,    -1,    -1,    -1,   116,    -1,    -1,   190,   191,
      -1,   122,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,
      -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,
     151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,    -1,
      -1,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,    -1,
     242,    -1,    -1,   245,   246,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,   190,
     191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   283,   284,    -1,   286,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,   311,
      -1,   242,    -1,    -1,   245,   246,    -1,    -1,    -1,    -1,
     322,    -1,   324,    -1,    -1,   327,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
     108,    -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,
      -1,    -1,   283,   284,   122,   286,    -1,    -1,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,   143,    -1,    -1,   146,   310,
     311,    -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,
     158,   322,    -1,   324,   162,    -1,   327,   165,    -1,   167,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   190,   191,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,   242,    -1,    65,   245,   246,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   283,   284,   106,   286,   108,
      -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   310,   311,    -1,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,    -1,   143,    -1,   324,   146,    -1,   327,
      -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,
      -1,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   190,   191,    -1,   193,   194,   195,   196,    -1,    -1,
      -1,    -1,    -1,   202,   203,    -1,    -1,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,    -1,    -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,   257,    30,
      31,    -1,    -1,    34,   263,    -1,    -1,    -1,    -1,   268,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,   278,
      -1,   280,    -1,    -1,   283,   284,   285,   286,    -1,    -1,
      -1,   290,    -1,    -1,    -1,   294,   295,   296,    -1,    -1,
      -1,   300,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     309,    -1,    -1,   312,   313,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   322,    -1,   324,    -1,    -1,   327,   100,
     101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,    -1,
      -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,
      -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,
     151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,    -1,
      -1,   162,    -1,    23,   165,    -1,   167,    -1,    -1,    -1,
      30,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,
     191,    -1,   193,   194,   195,   196,    -1,    -1,    -1,    -1,
      -1,   202,   203,    -1,    -1,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,    -1,
      -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,
      -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   277,   278,   138,    -1,
      -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,
      -1,   151,    -1,    -1,   154,   296,    -1,   157,   158,   300,
     301,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,
      -1,   312,   313,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   322,    -1,   324,    -1,    -1,   327,    -1,    -1,    -1,
     190,   191,    -1,   193,   194,   195,   196,    -1,    -1,    -1,
      -1,    -1,   202,   203,    -1,    -1,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,   232,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,   278,    -1,
      -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,
     300,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   312,   313,   100,   101,   102,   103,    -1,    -1,
     106,    -1,   108,    -1,   324,    -1,   112,   327,    -1,    -1,
     116,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,
     126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    -1,    -1,   143,    -1,    -1,
     146,    -1,    -1,    -1,    -1,   151,    -1,    -1,   154,    -1,
      -1,   157,   158,    -1,    -1,    -1,   162,    -1,    -1,   165,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   190,   191,    -1,   193,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,    -1,    -1,   232,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,   245,
     246,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   277,   278,    -1,    -1,    -1,    -1,   283,   284,    -1,
      -1,    -1,     0,     1,    -1,    -1,     4,    -1,     6,    -1,
     296,    -1,    -1,    -1,   300,   301,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,   311,    -1,   313,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    35,   324,    -1,
      -1,   327,    -1,    -1,    -1,    43,    -1,    45,    -1,    47,
      -1,    -1,    50,    51,    52,    -1,    54,    -1,    -1,    -1,
      58,    59,    60,    -1,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,   107,
      -1,   100,   101,   102,   103,    -1,    -1,    -1,   116,   108,
      -1,    -1,    -1,   112,   122,    -1,    -1,   116,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,    -1,   126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   146,   138,
      -1,    -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,
      -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,
      -1,    -1,    -1,   162,    -1,    -1,   165,    68,   167,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   190,   191,    -1,    -1,    -1,    -1,    -1,    -1,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,
      -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,   232,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,   247,
      -1,    -1,   143,   242,    -1,   146,   245,   246,    -1,    -1,
     151,    -1,    -1,   154,    -1,   263,   157,   158,    -1,    -1,
     268,   162,   270,    -1,   165,    -1,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   283,   284,    -1,   286,    -1,   190,
     191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   310,   311,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   324,    -1,    -1,   327,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   242,    -1,    -1,   245,   246,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   283,   284,    -1,   286,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,
     311,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   324,    -1,    -1,   327
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   331,     0,     1,     4,     6,    26,    27,    28,    29,
      35,    43,    45,    47,    50,    51,    52,    54,    58,    59,
      60,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   107,   116,   122,   146,   232,   247,
     263,   268,   270,   332,   334,   335,   336,   337,   400,   401,
     402,   404,   419,   332,   102,   101,   397,   397,   397,   402,
     413,   402,   404,   419,   402,   407,   407,   407,   402,   410,
     337,    47,   338,    35,    43,    45,    50,    51,    52,    54,
     232,   247,   263,   268,   270,   339,    47,   340,    35,    43,
      45,    47,    50,    51,    52,    54,   232,   247,   263,   268,
     270,   341,    51,   342,    35,    43,    44,    45,    46,    49,
      50,    52,    53,    54,    56,    95,    97,    98,    99,   232,
     247,   252,   253,   254,   255,   263,   268,   270,   271,   343,
     247,   252,   253,   268,   344,    43,    45,    50,    52,    56,
      95,    97,   345,    45,   346,    23,    30,    31,    34,   100,
     101,   102,   103,   106,   108,   112,   116,   122,   138,   143,
     146,   151,   154,   157,   158,   162,   165,   167,   190,   191,
     193,   194,   195,   196,   202,   203,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     232,   277,   278,   296,   300,   301,   312,   313,   324,   327,
     354,   398,   511,   512,   515,   516,   517,   521,   580,   583,
     585,   589,   594,   595,   597,   599,   609,   610,   612,   614,
     616,   618,   622,   624,   626,   628,   630,   632,   634,   636,
     638,   640,   644,   646,   648,   650,   651,   653,   655,   657,
     659,   661,   663,   665,   667,    56,   306,   307,   308,   347,
     353,    56,   348,   353,   101,   349,   350,    87,   239,   241,
     413,   413,   413,   413,     0,   332,   397,   397,    55,   303,
     304,   416,   417,   418,    33,    35,    50,    60,    61,    65,
      76,    77,    78,    79,    80,    81,    95,    97,   208,   232,
     247,   257,   263,   268,   280,   283,   284,   285,   286,   290,
     294,   295,   309,   322,   423,   424,   425,   426,   427,   428,
     429,   433,   434,   435,   438,   439,   446,   450,   455,   456,
     458,   459,   460,   461,   462,   484,   485,   487,   488,   490,
     491,   494,   495,   502,   503,   504,   505,   506,   509,   510,
     516,   523,   524,   525,   526,   527,   528,   532,   533,   534,
     564,   578,   583,   584,   607,   608,   609,   332,   321,   321,
     332,   397,   466,   355,   358,   423,   397,   361,   363,   511,
     534,   366,   397,   370,   404,   420,   413,   402,   404,   407,
     407,   407,   410,    87,   239,   241,   413,   413,   413,   413,
     419,   402,   413,   414,   400,   402,   403,   402,   404,   405,
     420,   402,   407,   408,   407,   407,   402,   410,   411,    87,
     239,   241,   554,   413,   414,   413,   414,   413,   414,   413,
     414,   407,   413,   402,   401,   422,   404,   422,    43,   422,
     407,   407,   422,   410,   422,    43,    44,   407,   422,   422,
      87,   239,   256,   554,   413,    43,   422,    43,   422,    43,
     422,    43,   422,   413,   413,   413,    43,   422,   413,    43,
     422,    43,   422,   413,   402,   404,   407,   407,   422,    43,
     407,   404,   104,   105,   106,   611,   109,   110,   209,   210,
     213,   519,   520,    32,   209,   586,   129,   522,   163,   164,
     649,   109,   110,   111,   613,   111,   113,   114,   115,   615,
     109,   110,   117,   118,   119,   120,   121,   617,   109,   110,
     113,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     172,   619,   111,   113,   131,   139,   140,   141,   142,   623,
     111,   131,   144,   259,   625,   109,   110,   123,   125,   126,
     127,   148,   149,   150,   627,   111,   113,   131,   139,   140,
     142,   152,   153,   629,   124,   140,   149,   155,   156,   631,
     140,   156,   633,   149,   159,   160,   635,   127,   131,   163,
     164,   637,   131,   163,   164,   166,   639,   131,   140,   155,
     159,   163,   164,   168,   169,   170,   171,   172,   641,   111,
     163,   164,   645,   131,   163,   164,   192,   647,   111,   122,
     124,   142,   146,   149,   197,   230,   231,   313,   596,   598,
     654,   198,   656,   198,   658,   159,   199,   200,   201,   660,
     124,   149,   652,   113,   128,   149,   155,   204,   205,   662,
     124,   149,   664,   111,   124,   131,   149,   155,   666,   101,
     127,   130,   147,   270,   287,   313,   581,   582,   583,   109,
     110,   130,   209,   233,   234,   235,   236,   237,   238,   240,
     241,   242,   243,   244,   245,   246,   249,   250,   251,   270,
     600,   601,   604,   287,   297,   588,   528,   533,   298,   193,
     202,   203,   206,   207,   668,   319,   320,   591,   527,   397,
     353,   307,   353,    44,    46,    48,    49,    56,    57,    89,
     351,   413,   413,   413,   549,   563,   551,   553,   100,   100,
     100,    82,   596,   248,   503,   397,   511,   579,   579,    60,
      96,   397,   101,   581,    87,   185,   239,   600,   601,   248,
     248,   264,   248,   266,   267,   447,    82,    82,   596,     4,
     333,   535,   536,   305,   421,   427,   249,   250,   436,   437,
     159,   258,   259,   260,   261,   262,   440,   441,   281,   457,
       5,    21,    68,    82,   108,   112,   116,   122,   126,   146,
     193,   242,   245,   246,   283,   284,   310,   311,   324,   469,
     470,   471,   472,   473,   474,   475,   477,   478,   479,   480,
     481,   482,   483,   512,   515,   521,   573,   574,   575,   580,
     585,   589,   595,   596,   597,   599,   605,   606,   609,    36,
      37,    38,   183,   463,   464,    82,   287,   288,   289,   486,
     492,   493,    82,   489,   492,   291,   292,   293,   496,   497,
     498,   499,    23,   511,   513,   514,    43,   507,   508,    15,
      16,    17,    18,   326,     8,    24,    52,     9,    10,    11,
      12,    13,    14,   108,   112,   116,   122,   138,   143,   146,
     151,   154,   157,   158,   162,   165,   167,   190,   191,   286,
     324,   480,   512,   514,   515,   529,   530,   531,   534,   565,
     566,   567,   568,   569,   570,   571,   572,   574,   575,   576,
     577,    50,    50,   547,   565,   566,   547,    36,   465,   322,
     322,   322,   322,   322,   416,   423,   466,   355,   358,   361,
     363,   366,   370,   413,   413,   413,   549,   563,   551,   553,
     423,    55,    55,    55,    55,   363,    55,   413,   363,   402,
     407,   422,    43,    43,    43,   413,   402,   402,   402,   402,
     402,   402,   402,   407,   397,     7,     8,   111,   213,   214,
     518,   101,   123,   248,   108,   122,   108,   122,   134,   135,
     136,   137,   620,   170,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   642,   598,   328,   328,   109,
     110,   122,   130,   146,   233,   234,   235,   602,   603,   604,
     298,   298,   100,   316,   590,   325,   352,   353,   561,   561,
     561,   249,   548,   264,   562,   447,   550,   398,   552,     5,
     122,   146,   482,    82,   482,   500,   501,   528,    23,    23,
      94,   322,    50,    50,    50,   100,   266,    50,   604,    50,
     482,   482,   266,   267,   451,   482,   100,   482,   482,    82,
     480,   534,   539,   540,   545,   571,   572,     7,   323,   398,
     100,   100,   437,    75,   108,   122,   167,   216,   443,   398,
     100,   100,   100,   398,   442,   441,   138,   151,   167,   282,
     482,     5,   482,   474,   512,   575,    15,    16,    17,    18,
     326,    20,    22,     8,    52,     5,   492,    82,   198,     7,
       7,   100,   100,   464,     5,     7,     5,   482,   482,   497,
       7,   397,   322,   397,   322,   508,   576,   576,   567,   568,
     569,   527,   322,   430,   513,   566,   571,     7,    15,    16,
      17,    18,   326,     7,    20,    22,     8,   566,   482,   482,
     332,   332,   100,   357,   359,   362,   367,   371,   465,   322,
     322,   322,   322,   322,   561,   561,   561,   548,   562,   550,
     552,   100,   100,   100,   100,   100,   561,   402,   402,   402,
     100,   520,   111,   127,   132,   133,   198,   621,    94,   127,
     184,   185,   186,   187,   188,   189,   643,   100,   100,   109,
     110,   109,   110,   100,   100,   299,   587,   100,   156,   315,
     592,   596,   322,   322,   322,   100,   451,   100,   482,     5,
       5,   482,   513,    87,    90,   421,   541,   542,   398,   398,
     100,   528,   537,   538,   482,   482,   482,   100,   482,    50,
     482,   100,   101,   250,   448,    41,   482,   333,     5,   333,
      87,    90,   247,   421,   543,   544,   333,   536,   145,   140,
     145,   444,   445,   111,   111,    68,   111,   482,     5,   325,
     469,   469,   470,   471,   472,   100,   474,   469,   476,   513,
     534,   482,   482,     8,   512,   575,   605,   605,   482,   493,
     482,   492,   499,   500,   537,   333,   431,   432,   325,   571,
     576,   576,   567,   568,   569,   571,   100,   571,   531,   571,
      37,   332,    35,    45,    50,    52,    54,   159,   232,   247,
     263,   268,   270,   323,   332,   334,   356,    91,   111,   159,
     323,   332,   334,   387,   393,   394,   423,    39,    86,    87,
      88,    89,    91,    94,   111,   159,   247,   323,   332,   334,
     368,    39,    87,    89,   111,   159,   323,   332,   334,   368,
      40,    42,   247,   323,   332,   334,   357,   359,   362,   367,
     371,   322,   322,   322,     7,   329,   329,   587,   302,   587,
     100,   109,   110,   593,   381,   382,   380,   250,   100,   448,
     482,   482,     5,   101,   399,   399,   542,   322,   427,   541,
     482,    20,   101,   269,   449,   482,    41,   546,   572,   578,
     399,   399,   249,   544,     7,   101,   101,   101,   482,     5,
     161,   492,   492,     5,   232,   323,   426,   427,   539,     7,
     323,   100,    37,   397,   415,   397,   406,   397,   409,   409,
     397,   412,   101,    87,   239,   241,   415,   415,   415,   415,
     332,    76,    77,   395,   396,   511,   101,    96,   332,   332,
     332,   332,   360,   516,   399,   399,   321,    92,    93,   369,
     100,   101,   125,   126,   209,   229,   230,   375,   376,   386,
      83,    84,    85,    87,   364,   365,   332,   332,   360,   399,
     321,   376,   364,   332,   101,   321,   323,   323,   323,   323,
     323,   381,   382,   380,   100,   100,    91,   130,   233,   323,
     332,   334,   559,    87,    94,   130,   164,   233,   323,   332,
     334,   560,   111,   233,   323,   332,   334,   556,   100,    20,
     101,   449,   482,   537,   323,   275,   276,   277,   278,   279,
     454,   265,   453,   100,   482,   333,   100,   445,   482,    82,
     500,     5,   323,   323,     5,   333,   432,   183,   467,   100,
     377,   358,   361,   366,   370,   415,   415,   415,   377,   377,
     377,   377,    40,     8,   332,   332,   332,   363,     8,   332,
       7,   332,     5,   332,   363,     5,   332,   147,   388,   322,
     372,   323,   323,   323,   587,   321,   162,   167,   555,   401,
     399,   100,   555,   100,   401,   102,   401,   454,   453,   427,
     265,   452,   100,   448,   250,   482,   323,   500,   578,    38,
     468,   332,   322,   322,   322,   322,   322,   377,   377,   377,
     322,   322,   322,   322,   101,   516,   375,   365,   360,   247,
     263,   268,   270,   376,    22,   100,   101,   320,   389,   390,
     391,   511,   332,   101,   373,   374,   332,   322,   332,   332,
     332,   332,   332,   332,   332,   130,   332,   452,   323,   100,
     101,   250,   100,   323,   333,   467,   385,   359,   362,   367,
     371,   322,   322,   322,   378,   383,   379,   384,    41,    42,
     392,   332,   332,   332,   332,   332,   332,   100,    22,    25,
       7,   323,   101,   557,   558,   555,   249,   468,   323,   332,
     334,   465,   323,   323,   323,   323,   381,   382,   380,   323,
     332,   334,   548,   323,   332,   334,   562,   323,   332,   334,
     550,   323,   332,   334,   552,   398,   321,   388,   100,   100,
     333,   374,     5,     7,   323,   332,   332,   332,   332,   332,
     332,   323,   323,   323,   332,   332,   332,   332,   372,   100,
     558,   332,   332,   332,   332
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   330,   331,   331,   332,   332,   333,   333,   334,   334,
     334,   334,   334,   335,   335,   335,   335,   336,   336,   336,
     336,   336,   336,   336,   336,   336,   336,   336,   336,   336,
     336,   336,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   338,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   340,
     341,   341,   341,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   342,   343,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   343,   344,   344,
     344,   344,   344,   344,   345,   345,   345,   345,   345,   345,
     345,   346,   347,   347,   348,   348,   349,   350,   350,   351,
     351,   351,   351,   351,   351,   351,   351,   352,   352,   353,
     353,   353,   354,   355,   356,   357,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   358,   359,   359,   359,   359,   359,   359,   359,   360,
     360,   361,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   363,   363,   364,   364,   365,   365,
     365,   365,   366,   367,   367,   367,   367,   367,   367,   367,
     367,   367,   367,   367,   367,   367,   368,   368,   369,   369,
     370,   371,   371,   371,   371,   371,   371,   372,   373,   373,
     373,   374,   375,   375,   376,   376,   377,   378,   378,   378,
     378,   379,   379,   379,   379,   380,   380,   380,   380,   381,
     381,   381,   381,   382,   382,   382,   382,   383,   383,   383,
     383,   384,   384,   384,   384,   385,   385,   385,   385,   386,
     386,   386,   386,   386,   387,   388,   389,   389,   390,   390,
     390,   390,   390,   391,   391,   392,   392,   392,   393,   394,
     395,   395,   396,   396,   397,   398,   398,   398,   399,   400,
     400,   401,   401,   401,   401,   401,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   419,   419,   419,   420,   421,
     422,   422,   423,   423,   424,   425,   425,   426,   426,   426,
     426,   427,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   427,   427,   427,   427,   427,   427,   427,
     428,   428,   429,   430,   430,   431,   431,   431,   432,   433,
     433,   434,   434,   435,   435,   436,   436,   437,   437,   438,
     438,   439,   440,   440,   441,   441,   441,   441,   441,   441,
     442,   443,   443,   443,   443,   443,   444,   444,   445,   445,
     446,   446,   446,   447,   447,   447,   448,   448,   449,   449,
     450,   450,   451,   451,   451,   452,   452,   453,   453,   453,
     454,   454,   454,   454,   454,   455,   456,   457,   457,   457,
     457,   457,   458,   459,   459,   460,   460,   460,   460,   460,
     460,   461,   461,   462,   462,   463,   463,   464,   464,   464,
     464,   465,   465,   466,   467,   467,   468,   468,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   470,   470,   470,   471,   471,   472,   472,   473,   473,
     474,   475,   475,   476,   476,   477,   477,   478,   479,   480,
     481,   481,   481,   482,   482,   482,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   484,   484,   485,   486,
     486,   486,   487,   487,   488,   489,   489,   489,   489,   489,
     490,   490,   491,   491,   492,   492,   493,   493,   493,   494,
     494,   495,   496,   496,   497,   497,   498,   498,   499,   499,
     500,   500,   501,   502,   502,   502,   503,   503,   503,   504,
     504,   505,   505,   506,   507,   507,   508,   509,   509,   510,
     511,   512,   512,   513,   513,   514,   515,   516,   516,   516,
     516,   516,   516,   516,   516,   516,   516,   516,   516,   516,
     516,   516,   517,   518,   518,   518,   519,   519,   519,   519,
     519,   520,   520,   521,   521,   522,   522,   523,   523,   523,
     524,   524,   525,   525,   526,   526,   527,   528,   528,   529,
     530,   531,   531,   532,   533,   533,   533,   534,   535,   535,
     535,   536,   536,   536,   537,   537,   538,   539,   539,   540,
     541,   541,   542,   542,   542,   543,   543,   544,   544,   544,
     544,   544,   545,   545,   546,   546,   547,   547,   548,   549,
     550,   551,   552,   553,   554,   554,   554,   555,   555,   556,
     556,   557,   557,   558,   559,   559,   559,   560,   560,   560,
     560,   560,   561,   562,   562,   563,   564,   564,   564,   565,
     565,   566,   566,   566,   566,   567,   567,   567,   568,   568,
     569,   569,   570,   570,   571,   572,   572,   572,   572,   573,
     573,   574,   575,   575,   575,   575,   575,   575,   575,   575,
     575,   575,   575,   575,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   577,   577,   577,   577,   577,   577,   578,   578,   578,
     578,   578,   578,   579,   579,   580,   580,   580,   581,   581,
     582,   582,   582,   582,   582,   583,   583,   583,   583,   583,
     583,   583,   583,   583,   583,   583,   583,   583,   583,   583,
     583,   583,   583,   583,   583,   583,   583,   583,   583,   584,
     584,   584,   584,   584,   584,   585,   586,   586,   587,   587,
     588,   588,   589,   590,   590,   591,   591,   592,   592,   593,
     593,   594,   594,   595,   595,   595,   596,   596,   597,   597,
     598,   598,   598,   598,   599,   599,   599,   600,   600,   601,
     601,   601,   601,   601,   601,   601,   601,   601,   601,   601,
     601,   601,   601,   601,   601,   602,   602,   602,   602,   602,
     602,   602,   603,   603,   603,   603,   604,   604,   604,   604,
     605,   605,   606,   606,   607,   607,   607,   607,   608,   609,
     609,   609,   609,   609,   609,   609,   609,   609,   609,   609,
     609,   609,   609,   609,   609,   609,   609,   610,   611,   611,
     611,   612,   613,   613,   613,   614,   615,   615,   615,   615,
     616,   617,   617,   617,   617,   617,   617,   617,   617,   617,
     618,   618,   618,   619,   619,   619,   619,   619,   619,   619,
     619,   619,   619,   619,   619,   620,   620,   620,   620,   621,
     621,   621,   621,   621,   622,   623,   623,   623,   623,   623,
     623,   623,   624,   625,   625,   625,   625,   626,   627,   627,
     627,   627,   627,   627,   627,   627,   627,   628,   629,   629,
     629,   629,   629,   629,   629,   629,   630,   631,   631,   631,
     631,   631,   632,   633,   633,   634,   635,   635,   635,   636,
     637,   637,   637,   637,   638,   639,   639,   639,   639,   640,
     640,   640,   641,   641,   641,   641,   641,   641,   641,   641,
     641,   641,   642,   642,   642,   642,   642,   642,   642,   642,
     642,   642,   642,   642,   643,   643,   643,   643,   643,   643,
     643,   643,   644,   645,   645,   645,   646,   647,   647,   647,
     647,   648,   649,   649,   650,   650,   650,   650,   650,   650,
     650,   650,   651,   652,   652,   653,   654,   654,   654,   654,
     655,   656,   657,   658,   659,   660,   660,   660,   660,   661,
     662,   662,   662,   662,   662,   662,   663,   664,   664,   665,
     666,   666,   666,   666,   666,   667,   668,   668,   668,   668,
     668
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
       8,     0,     0,     2,     2,     3,     3,     3,     3,     1,
       3,     0,     0,     2,     2,     4,     4,     4,     4,     4,
       3,     4,     2,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     0,     0,     2,     2,     4,     6,     6,     6,
       6,     6,     6,     4,     4,     3,     2,     2,     1,     1,
       0,     0,     2,     2,     5,     5,     2,     3,     1,     3,
       3,     1,     1,     1,     1,     3,     0,     0,     2,     2,
       2,     0,     2,     2,     2,     0,     2,     2,     2,     0,
       2,     2,     2,     0,     2,     2,     2,     0,     2,     2,
       2,     0,     2,     2,     2,     0,     2,     2,     2,     1,
       1,     1,     1,     1,     6,     2,     1,     1,     1,     1,
       1,     3,     3,     1,     2,     2,     3,     0,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     2,
       3,     1,     2,     3,     1,     2,     3,     1,     2,     3,
       1,     2,     2,     2,     1,     2,     2,     2,     2,     2,
       0,     1,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     1,     3,     3,     5,     3,
       4,     1,     2,     1,     3,     1,     2,     2,     2,     1,
       2,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       1,     2,     2,     1,     1,     1,     3,     1,     1,     1,
       7,     6,     3,     1,     1,     0,     1,     1,     0,     3,
       5,     3,     1,     1,     0,     0,     3,     0,     3,     3,
       1,     1,     1,     1,     1,     2,     1,     0,     4,     4,
       4,     3,     2,     1,     1,     3,     4,     4,     5,     6,
       5,     1,     2,     1,     3,     1,     2,     2,     2,     1,
       1,     6,     8,     0,     0,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     1,     3,     1,     1,     3,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     3,
       4,     5,     2,     3,     2,     6,     2,     1,     1,     3,
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
       3,     1,     1,     3,     1,     1,     1,     3,     1,     3,
       3,     3,     3,     5,     1,     2,     1,     1,     2,     1,
       1,     2,     2,     2,     1,     1,     2,     2,     2,     1,
       5,     1,     1,     1,     1,     1,     1,     1,     4,     0,
       4,     0,     1,     0,     1,     1,     1,     1,     1,     5,
       3,     1,     3,     3,     3,     6,     3,     3,     3,     3,
       3,     3,     0,     6,     5,     0,     2,     2,     3,     3,
       3,     1,     1,     1,     1,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     4,     1,     4,     4,     2,     1,     1,     0,     2,
       1,     1,     5,     2,     0,     1,     1,     1,     1,     1,
       1,     4,     5,     7,     5,     4,     1,     1,     2,     3,
       1,     1,     1,     1,     2,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     3,     3,     4,     4,     4,     5,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     1,     1,
       1,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     2,     1,     1,     2,     1,     1,     1,     2,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     2,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     2,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     2,     1,     1,     1,     1,
       2,     4,     2,     1,     2,     1,     1,     1,     4,     2,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     2,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1
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
    case 101: /* "string"  */
#line 301 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4242 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 102: /* "quoted string"  */
#line 301 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4248 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 103: /* "string with a trailing asterisk"  */
#line 301 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4254 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* line  */
#line 577 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4260 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 336: /* base_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4266 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* add_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4272 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* replace_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4278 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* create_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4284 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* insert_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4290 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* delete_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4296 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* get_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4302 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* list_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4308 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* reset_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4314 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 345: /* flush_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4320 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* rename_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4326 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* import_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4332 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 348: /* export_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4338 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 349: /* monitor_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4344 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* monitor_event  */
#line 801 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4350 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* describe_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4356 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 355: /* table_block_alloc  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 4362 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* chain_block_alloc  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 4368 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* typeof_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4374 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* set_block_alloc  */
#line 607 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4380 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 363: /* set_block_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4386 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 366: /* map_block_alloc  */
#line 610 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4392 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 370: /* flowtable_block_alloc  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 4398 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 372: /* flowtable_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4404 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* flowtable_list_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4410 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 374: /* flowtable_expr_member  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4416 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* data_type_atom_expr  */
#line 574 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4422 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* data_type_expr  */
#line 574 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4428 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* obj_block_alloc  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4434 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* type_identifier  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4440 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* extended_prio_name  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4446 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* dev_spec  */
#line 593 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).expr)); }
#line 4452 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* policy_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4458 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* identifier  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4464 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* string  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4470 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* table_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4476 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* tableid_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4482 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* chain_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4488 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* chainid_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4494 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* chain_identifier  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4500 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* set_spec  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4506 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* setid_spec  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4512 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* set_identifier  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4518 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* flowtable_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4524 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* flowtableid_spec  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4530 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* obj_spec  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4536 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* objid_spec  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4542 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* obj_identifier  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4548 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* handle_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4554 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* position_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4560 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* index_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4566 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* rule_position  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4572 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* ruleid_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4578 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* comment_spec  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4584 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* ruleset_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4590 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* rule  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 4596 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* stmt_list  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 4602 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* stateful_stmt  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4608 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* stmt  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4614 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* verdict_stmt  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4620 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* verdict_map_stmt  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4626 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* verdict_map_expr  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4632 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* verdict_map_list_expr  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4638 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 432: /* verdict_map_list_member_expr  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4644 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* connlimit_stmt  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4650 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* counter_stmt  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4656 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* counter_stmt_alloc  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4662 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* log_stmt  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4668 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 439: /* log_stmt_alloc  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4674 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 446: /* limit_stmt  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4680 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* quota_unit  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4686 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 450: /* quota_stmt  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4692 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 455: /* reject_stmt  */
#line 637 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4698 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 456: /* reject_stmt_alloc  */
#line 637 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4704 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* nat_stmt  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4710 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* nat_stmt_alloc  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4716 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* tproxy_stmt  */
#line 642 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4722 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* synproxy_stmt  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4728 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* synproxy_stmt_alloc  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4734 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* synproxy_obj  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4740 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* primary_stmt_expr  */
#line 687 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4746 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* shift_stmt_expr  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4752 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* and_stmt_expr  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4758 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* exclusive_or_stmt_expr  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4764 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* inclusive_or_stmt_expr  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4770 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* basic_stmt_expr  */
#line 687 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4776 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* concat_stmt_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4782 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* map_stmt_expr_set  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4788 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* map_stmt_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4794 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* prefix_stmt_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4800 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* range_stmt_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4806 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* wildcard_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4812 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* multiton_stmt_expr  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4818 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* stmt_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4824 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* masq_stmt  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4830 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* masq_stmt_alloc  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4836 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* redir_stmt  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4842 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* redir_stmt_alloc  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4848 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 490: /* dup_stmt  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4854 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 491: /* fwd_stmt  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4860 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* queue_stmt  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4866 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 495: /* queue_stmt_alloc  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4872 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* set_elem_expr_stmt  */
#line 710 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4878 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* set_elem_expr_stmt_alloc  */
#line 710 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4884 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 502: /* set_stmt  */
#line 655 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4890 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 504: /* map_stmt  */
#line 658 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4896 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* meter_stmt  */
#line 660 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4902 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* flow_stmt_legacy_alloc  */
#line 660 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4908 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 509: /* meter_stmt_alloc  */
#line 660 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4914 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* match_stmt  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4920 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 511: /* variable_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4926 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 512: /* symbol_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4932 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* set_ref_expr  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4938 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 514: /* set_ref_symbol_expr  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4944 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 515: /* integer_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4950 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 516: /* primary_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4956 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* fib_expr  */
#line 792 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4962 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 521: /* osf_expr  */
#line 797 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4968 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* shift_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4974 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 524: /* and_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4980 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 525: /* exclusive_or_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4986 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 526: /* inclusive_or_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4992 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 527: /* basic_expr  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4998 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* concat_expr  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5004 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* prefix_rhs_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5010 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* range_rhs_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5016 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* multiton_rhs_expr  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5022 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* map_expr  */
#line 697 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5028 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* expr  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5034 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* set_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5040 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* set_list_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5046 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* set_list_member_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5052 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 537: /* meter_key_expr  */
#line 713 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5058 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* meter_key_expr_alloc  */
#line 713 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5064 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* set_elem_expr  */
#line 708 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5070 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* set_elem_expr_alloc  */
#line 708 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5076 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 545: /* set_lhs_expr  */
#line 708 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5082 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 546: /* set_rhs_expr  */
#line 708 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5088 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* initializer_expr  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5094 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 549: /* counter_obj  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5100 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* quota_obj  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5106 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 553: /* secmark_obj  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5112 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 557: /* timeout_states  */
#line 822 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5118 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 558: /* timeout_state  */
#line 822 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5124 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 561: /* ct_obj_alloc  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5130 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 563: /* limit_obj  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5136 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 564: /* relational_expr  */
#line 729 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5142 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 565: /* list_rhs_expr  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5148 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 566: /* rhs_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5154 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 567: /* shift_rhs_expr  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5160 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 568: /* and_rhs_expr  */
#line 723 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5166 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 569: /* exclusive_or_rhs_expr  */
#line 723 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5172 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 570: /* inclusive_or_rhs_expr  */
#line 723 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5178 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 571: /* basic_rhs_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5184 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 572: /* concat_rhs_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5190 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 574: /* boolean_expr  */
#line 812 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5196 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 575: /* keyword_expr  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5202 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 576: /* primary_rhs_expr  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5208 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 578: /* verdict_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5214 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 579: /* chain_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5220 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 580: /* meta_expr  */
#line 774 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5226 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 584: /* meta_stmt  */
#line 629 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5232 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 585: /* socket_expr  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5238 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 589: /* numgen_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5244 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 594: /* xfrm_expr  */
#line 826 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5250 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 595: /* hash_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5256 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 597: /* rt_expr  */
#line 784 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5262 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 599: /* ct_expr  */
#line 788 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5268 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 605: /* symbol_stmt_expr  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5274 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 606: /* list_stmt_expr  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5280 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 607: /* ct_stmt  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5286 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 608: /* payload_stmt  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5292 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 609: /* payload_expr  */
#line 733 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5298 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 610: /* payload_raw_expr  */
#line 733 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5304 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 612: /* eth_hdr_expr  */
#line 736 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5310 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 614: /* vlan_hdr_expr  */
#line 736 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5316 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 616: /* arp_hdr_expr  */
#line 739 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5322 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 618: /* ip_hdr_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5328 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 622: /* icmp_hdr_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5334 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 624: /* igmp_hdr_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5340 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 626: /* ip6_hdr_expr  */
#line 746 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5346 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 628: /* icmp6_hdr_expr  */
#line 746 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5352 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 630: /* auth_hdr_expr  */
#line 749 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5358 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 632: /* esp_hdr_expr  */
#line 749 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5364 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 634: /* comp_hdr_expr  */
#line 749 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5370 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 636: /* udp_hdr_expr  */
#line 752 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5376 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 638: /* udplite_hdr_expr  */
#line 752 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5382 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 640: /* tcp_hdr_expr  */
#line 807 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5388 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 644: /* dccp_hdr_expr  */
#line 755 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5394 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 646: /* sctp_hdr_expr  */
#line 755 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5400 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 648: /* th_hdr_expr  */
#line 758 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5406 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 650: /* exthdr_expr  */
#line 762 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5412 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 651: /* hbh_hdr_expr  */
#line 764 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5418 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 653: /* rt_hdr_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5424 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 655: /* rt0_hdr_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5430 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 657: /* rt2_hdr_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5436 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 659: /* rt4_hdr_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5442 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 661: /* frag_hdr_expr  */
#line 764 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5448 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 663: /* dst_hdr_expr  */
#line 764 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5454 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 665: /* mh_hdr_expr  */
#line 770 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5460 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 667: /* exthdr_exists_expr  */
#line 816 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5466 "parser_bison.c" /* yacc.c:1257  */
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
#line 146 "parser_bison.y" /* yacc.c:1431  */
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 5582 "parser_bison.c" /* yacc.c:1431  */
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
#line 832 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 5781 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 8:
#line 849 "parser_bison.y" /* yacc.c:1652  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 9:
#line 857 "parser_bison.y" /* yacc.c:1652  */
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
#line 5811 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 10:
#line 871 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 5822 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 11:
#line 878 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5837 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 12:
#line 889 "parser_bison.y" /* yacc.c:1652  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 5847 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 13:
#line 896 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 5853 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 14:
#line 897 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 5859 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 15:
#line 898 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 5865 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 16:
#line 900 "parser_bison.y" /* yacc.c:1652  */
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
#line 5887 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 17:
#line 919 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5893 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 18:
#line 920 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5899 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 19:
#line 921 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5905 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 20:
#line 922 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5911 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 21:
#line 923 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5917 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 22:
#line 924 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5923 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 23:
#line 925 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5929 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 24:
#line 926 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5935 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 25:
#line 927 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5941 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 26:
#line 928 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5947 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 27:
#line 929 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 28:
#line 930 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5959 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 29:
#line 931 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5965 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 30:
#line 932 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 31:
#line 933 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5977 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 32:
#line 937 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5985 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 33:
#line 942 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 34:
#line 948 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6003 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 35:
#line 953 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6014 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 36:
#line 960 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6022 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 37:
#line 964 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6030 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 38:
#line 969 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 39:
#line 976 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6050 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 40:
#line 982 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6058 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 41:
#line 987 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6068 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 42:
#line 993 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 6081 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 43:
#line 1002 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6089 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 44:
#line 1006 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6097 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 45:
#line 1010 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6105 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 46:
#line 1014 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6113 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 47:
#line 1018 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6121 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 48:
#line 1022 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6129 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 49:
#line 1026 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6137 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 50:
#line 1030 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6145 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 51:
#line 1036 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6153 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 52:
#line 1042 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 53:
#line 1047 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6171 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 54:
#line 1053 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 55:
#line 1058 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6190 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 56:
#line 1066 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6200 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 57:
#line 1073 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6210 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 58:
#line 1079 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6218 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 59:
#line 1084 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 60:
#line 1090 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 6241 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 61:
#line 1099 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 62:
#line 1103 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 63:
#line 1107 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6265 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 64:
#line 1111 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 65:
#line 1115 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6281 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 66:
#line 1119 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6289 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 67:
#line 1123 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6297 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 68:
#line 1127 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6305 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 69:
#line 1133 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6313 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 70:
#line 1139 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6321 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 71:
#line 1143 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6329 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 72:
#line 1147 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 73:
#line 1151 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6345 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 74:
#line 1155 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6353 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 75:
#line 1159 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6361 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 76:
#line 1163 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6369 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 77:
#line 1167 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6377 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 78:
#line 1171 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 79:
#line 1175 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 80:
#line 1179 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6401 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 81:
#line 1183 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 82:
#line 1187 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 83:
#line 1191 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 84:
#line 1195 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 85:
#line 1199 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 86:
#line 1203 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6449 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 87:
#line 1207 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 88:
#line 1211 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6465 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 89:
#line 1215 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 90:
#line 1219 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6481 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 91:
#line 1223 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6489 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 92:
#line 1229 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6497 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 93:
#line 1235 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6505 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 94:
#line 1239 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 95:
#line 1243 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6521 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 96:
#line 1247 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6529 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 97:
#line 1251 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6537 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 98:
#line 1255 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6545 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 99:
#line 1259 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6553 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 100:
#line 1263 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6561 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 101:
#line 1267 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6569 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 102:
#line 1271 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 103:
#line 1275 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 104:
#line 1279 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6593 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 105:
#line 1283 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6601 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1287 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6609 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1291 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6617 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1295 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1299 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6633 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1303 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1307 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6649 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1311 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6657 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1315 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6665 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1319 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6673 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 115:
#line 1323 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6681 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 116:
#line 1327 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6689 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 117:
#line 1331 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6697 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 118:
#line 1335 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6705 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 119:
#line 1339 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6713 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1343 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6721 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1347 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6729 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1351 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1355 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6745 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1359 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1363 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1367 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_TIMEOUT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6769 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1371 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_EXPECT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6777 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1377 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6785 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1381 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1385 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 6801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1389 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1393 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6817 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1397 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6825 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1403 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6833 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1407 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6841 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1411 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1415 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6857 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 138:
#line 1419 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6865 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 139:
#line 1423 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6873 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 140:
#line 1427 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6881 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 141:
#line 1433 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 6890 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1440 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6900 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1446 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1454 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6920 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 145:
#line 1460 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6930 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 146:
#line 1468 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 6941 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 147:
#line 1476 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = NULL; }
#line 6947 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 148:
#line 1477 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 149:
#line 1480 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 6959 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 150:
#line 1481 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 6965 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 151:
#line 1482 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 6971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 152:
#line 1483 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 6977 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 153:
#line 1484 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 6983 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1485 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 6989 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1486 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 6995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1487 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 7001 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 157:
#line 1490 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 7007 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 159:
#line 1494 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 7013 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1495 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7019 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1496 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7025 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1500 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 7035 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1508 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 7044 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 164:
#line 1515 "parser_bison.y" /* yacc.c:1652  */
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
#line 7060 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1528 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 7066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 169:
#line 1535 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7079 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1546 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7091 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1556 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7103 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1567 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7115 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 173:
#line 1577 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7128 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 174:
#line 1588 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 175:
#line 1597 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7154 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 176:
#line 1606 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 177:
#line 1615 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7180 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 178:
#line 1626 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7193 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 179:
#line 1637 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7206 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 180:
#line 1648 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7219 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 181:
#line 1659 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 7228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 182:
#line 1665 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 188:
#line 1672 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 7243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 189:
#line 1679 "parser_bison.y" /* yacc.c:1652  */
    {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 7258 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 190:
#line 1690 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 7271 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 191:
#line 1702 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 192:
#line 1707 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 195:
#line 1711 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7294 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 196:
#line 1716 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7304 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 197:
#line 1722 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7313 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 198:
#line 1727 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7322 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 199:
#line 1732 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7331 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 200:
#line 1737 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->stmt = counter_stmt_alloc(&(yyloc));
				(yyval.set) = (yyvsp[-2].set);
			}
#line 7340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 201:
#line 1742 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7349 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 202:
#line 1747 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 7358 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 206:
#line 1759 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7366 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 208:
#line 1765 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 7372 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 209:
#line 1766 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 7378 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 210:
#line 1767 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 7384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 211:
#line 1768 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_EVAL; }
#line 7390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 212:
#line 1772 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7398 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 213:
#line 1777 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7404 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 216:
#line 1781 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7413 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 217:
#line 1788 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 218:
#line 1798 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7438 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 219:
#line 1809 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7449 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 220:
#line 1818 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7460 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 221:
#line 1827 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7471 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 222:
#line 1836 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_SECMARK;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7482 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 223:
#line 1843 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7491 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 224:
#line 1848 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7500 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 226:
#line 1856 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 7508 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 227:
#line 1860 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 7516 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 228:
#line 1865 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 7522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 229:
#line 1866 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 7528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 230:
#line 1870 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 7536 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 231:
#line 1875 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 7542 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 234:
#line 1879 "parser_bison.y" /* yacc.c:1652  */
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
#line 7560 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 235:
#line 1893 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 7568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 236:
#line 1897 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 7576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 237:
#line 1903 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 238:
#line 1910 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7594 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 239:
#line 1915 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 241:
#line 1923 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7614 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 242:
#line 1932 "parser_bison.y" /* yacc.c:1652  */
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
#line 7630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 243:
#line 1944 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 7639 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 245:
#line 1952 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 7652 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 246:
#line 1963 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 7660 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 247:
#line 1968 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7666 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 250:
#line 1972 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7674 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 251:
#line 1977 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7680 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 254:
#line 1981 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 255:
#line 1986 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 258:
#line 1990 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7702 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 259:
#line 1995 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 262:
#line 1999 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 263:
#line 2004 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7722 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 266:
#line 2008 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 267:
#line 2013 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 270:
#line 2017 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7744 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 271:
#line 2022 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7750 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 274:
#line 2026 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7758 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 275:
#line 2031 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7764 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 278:
#line 2035 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7772 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 279:
#line 2040 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7778 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 280:
#line 2041 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("mark"); }
#line 7784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 281:
#line 2042 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("dscp"); }
#line 7790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 282:
#line 2043 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("ecn"); }
#line 7796 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 283:
#line 2044 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("classid"); }
#line 7802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 284:
#line 2048 "parser_bison.y" /* yacc.c:1652  */
    {
				const char *chain_type = chain_type_name_lookup((yyvsp[-4].string));

				if (chain_type == NULL) {
					erec_queue(error(&(yylsp[-4]), "unknown chain type"),
						   state->msgs);
					xfree((yyvsp[-4].string));
					YYERROR;
				}
				(yyvsp[-6].chain)->type		= xstrdup(chain_type);
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
#line 7834 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 285:
#line 2078 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 7843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 286:
#line 2085 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.string) = strdup("out");
			}
#line 7851 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 288:
#line 2092 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 7865 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 289:
#line 2102 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				datatype_set((yyvsp[0].expr)->sym->expr, &priority_type);
				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 7877 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 290:
#line 2110 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 7892 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 291:
#line 2121 "parser_bison.y" /* yacc.c:1652  */
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
#line 7909 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 292:
#line 2134 "parser_bison.y" /* yacc.c:1652  */
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
#line 7925 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 293:
#line 2147 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = (yyvsp[0].val); }
#line 7931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 294:
#line 2148 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = -(yyvsp[0].val); }
#line 7937 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 295:
#line 2152 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 7953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 296:
#line 2164 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 7961 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 297:
#line 2167 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = NULL; }
#line 7967 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 298:
#line 2171 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 7975 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 299:
#line 2177 "parser_bison.y" /* yacc.c:1652  */
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
#line 7990 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 300:
#line 2190 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 7999 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 301:
#line 2195 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 8010 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 302:
#line 2203 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_ACCEPT; }
#line 8016 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 303:
#line 2204 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_DROP;   }
#line 8022 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 308:
#line 2216 "parser_bison.y" /* yacc.c:1652  */
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
#line 8039 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 309:
#line 2230 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8045 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 311:
#line 2234 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8051 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 312:
#line 2235 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 8057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 313:
#line 2236 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_INET; }
#line 8063 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 314:
#line 2237 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_ARP; }
#line 8069 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 315:
#line 2238 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 8075 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 316:
#line 2239 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 8081 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 317:
#line 2243 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 8092 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 318:
#line 2252 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 8103 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 319:
#line 2261 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 8113 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 320:
#line 2269 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 8123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 321:
#line 2277 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 8133 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 322:
#line 2285 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 8143 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 323:
#line 2293 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 8153 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 324:
#line 2301 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 8163 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 325:
#line 2309 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 8173 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 326:
#line 2317 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8183 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 327:
#line 2325 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 8193 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 328:
#line 2333 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 8203 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 329:
#line 2341 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 330:
#line 2349 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 8223 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 331:
#line 2357 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8233 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 332:
#line 2365 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 8243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 333:
#line 2373 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 8253 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 334:
#line 2381 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 8261 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 335:
#line 2385 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8270 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 336:
#line 2390 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 337:
#line 2398 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8291 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 338:
#line 2405 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8300 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 339:
#line 2412 "parser_bison.y" /* yacc.c:1652  */
    {
				if (strlen((yyvsp[0].string)) > NFTNL_UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed",
							 NFTNL_UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 8314 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 340:
#line 2424 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 8323 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 341:
#line 2429 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 8332 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 342:
#line 2436 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 8340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 343:
#line 2440 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 8348 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 344:
#line 2446 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 8362 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 345:
#line 2458 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 8372 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 346:
#line 2464 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 8381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 370:
#line 2498 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8389 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 371:
#line 2502 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8397 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 372:
#line 2508 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8405 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 373:
#line 2514 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8414 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 375:
#line 2522 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8423 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 376:
#line 2527 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8432 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 378:
#line 2535 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 8440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 379:
#line 2541 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[0].val);
			}
#line 8449 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 380:
#line 2546 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[0].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 8459 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 383:
#line 2557 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 8467 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 384:
#line 2561 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8477 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 385:
#line 2569 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 387:
#line 2576 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 8493 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 388:
#line 2580 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 8501 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 391:
#line 2590 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 8509 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 392:
#line 2596 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8517 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 394:
#line 2603 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 8526 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 395:
#line 2608 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 8535 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 396:
#line 2613 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 8544 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 397:
#line 2618 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 8553 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 398:
#line 2623 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 8562 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 399:
#line 2628 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 8570 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 400:
#line 2634 "parser_bison.y" /* yacc.c:1652  */
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
#line 8602 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 401:
#line 2664 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 8610 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 402:
#line 2668 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 8618 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 403:
#line 2672 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 8626 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 404:
#line 2676 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 8634 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 405:
#line 2680 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 8642 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 406:
#line 2686 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8650 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 408:
#line 2693 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 8658 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 409:
#line 2697 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 8666 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 410:
#line 2703 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 8679 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 411:
#line 2712 "parser_bison.y" /* yacc.c:1652  */
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
#line 8702 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 412:
#line 2731 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 413:
#line 2738 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 8718 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 414:
#line 2739 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8724 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 415:
#line 2740 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 416:
#line 2743 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("bytes"); }
#line 8736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 417:
#line 2744 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 8742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 418:
#line 2747 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 419:
#line 2749 "parser_bison.y" /* yacc.c:1652  */
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
#line 8765 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 420:
#line 2764 "parser_bison.y" /* yacc.c:1652  */
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
#line 8785 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 421:
#line 2780 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8795 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 422:
#line 2787 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 8801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 423:
#line 2788 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8807 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 424:
#line 2789 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8813 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 425:
#line 2792 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8819 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 426:
#line 2793 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 8825 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 427:
#line 2796 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8831 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 428:
#line 2797 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 8837 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 429:
#line 2799 "parser_bison.y" /* yacc.c:1652  */
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
#line 8854 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 430:
#line 2813 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL; }
#line 8860 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 431:
#line 2814 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60; }
#line 8866 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 432:
#line 2815 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 8872 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 433:
#line 2816 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 8878 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 434:
#line 2817 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 8884 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 436:
#line 2824 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 8892 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 437:
#line 2830 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 8901 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 438:
#line 2835 "parser_bison.y" /* yacc.c:1652  */
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
#line 8916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 439:
#line 2846 "parser_bison.y" /* yacc.c:1652  */
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
#line 8931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 440:
#line 2857 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpx_code_type);
				xfree((yyvsp[0].string));
			}
#line 8945 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 441:
#line 2867 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 8953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 443:
#line 2875 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 8959 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 444:
#line 2876 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 8965 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 445:
#line 2880 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 8975 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 446:
#line 2886 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 8985 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 447:
#line 2892 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 448:
#line 2898 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9006 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 449:
#line 2905 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9017 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 450:
#line 2912 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9027 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 453:
#line 2924 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 9035 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 454:
#line 2928 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9045 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 455:
#line 2936 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9053 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 457:
#line 2943 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 9062 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 458:
#line 2948 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 9071 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 459:
#line 2953 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 9079 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 460:
#line 2957 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 9087 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 461:
#line 2963 "parser_bison.y" /* yacc.c:1652  */
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
#line 9107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 462:
#line 2979 "parser_bison.y" /* yacc.c:1652  */
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
#line 9127 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 463:
#line 2997 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 9136 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 464:
#line 3003 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9142 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 465:
#line 3005 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 9150 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 466:
#line 3010 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9156 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 467:
#line 3012 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 9164 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 468:
#line 3017 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9170 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 469:
#line 3018 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9176 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 470:
#line 3019 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9182 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 471:
#line 3020 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9188 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 472:
#line 3021 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9194 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 473:
#line 3022 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9200 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 474:
#line 3023 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9206 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 475:
#line 3024 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9212 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 476:
#line 3025 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9218 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 477:
#line 3026 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9224 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 478:
#line 3027 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9230 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 479:
#line 3028 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9236 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 480:
#line 3029 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 9242 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 482:
#line 3034 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9250 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 483:
#line 3038 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9258 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 485:
#line 3045 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9266 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 487:
#line 3052 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 489:
#line 3059 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 492:
#line 3069 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 9295 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 495:
#line 3084 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9303 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 496:
#line 3087 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9309 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 497:
#line 3091 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 9317 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 498:
#line 3097 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9325 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 499:
#line 3103 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 9338 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 506:
#line 3124 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 9346 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 507:
#line 3128 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 9354 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 508:
#line 3132 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 9363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 509:
#line 3137 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9372 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 510:
#line 3142 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 511:
#line 3147 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 512:
#line 3153 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 513:
#line 3157 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9407 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 514:
#line 3161 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9415 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 515:
#line 3165 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.ipportmap = true;
			}
#line 9425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 518:
#line 3176 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 9431 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 519:
#line 3180 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9439 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 520:
#line 3184 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9448 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 521:
#line 3189 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9456 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 524:
#line 3198 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 9462 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 525:
#line 3202 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9470 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 526:
#line 3206 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9478 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 527:
#line 3210 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9486 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 528:
#line 3214 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9495 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 529:
#line 3219 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 530:
#line 3226 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 9513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 531:
#line 3231 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 9523 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 532:
#line 3239 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 9532 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 533:
#line 3244 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 9543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 535:
#line 3254 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9551 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 536:
#line 3259 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 9557 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 537:
#line 3260 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 9563 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 538:
#line 3261 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 9569 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 541:
#line 3269 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 9577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 542:
#line 3275 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 544:
#line 3282 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 9594 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 545:
#line 3287 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 9602 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 547:
#line 3294 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9610 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 548:
#line 3299 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 9616 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 549:
#line 3300 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 9622 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 552:
#line 3308 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 9630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 553:
#line 3314 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 9641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 554:
#line 3321 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 9652 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 555:
#line 3328 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				(yyval.stmt)->set.stmt = (yyvsp[-1].stmt);
			}
#line 9664 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 556:
#line 3337 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 9670 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 557:
#line 3338 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 9676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 558:
#line 3339 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 9682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 559:
#line 3343 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 9694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 560:
#line 3351 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.stmt = (yyvsp[-3].stmt);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
			}
#line 9707 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 561:
#line 3362 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 9718 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 562:
#line 3368 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 9724 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 563:
#line 3372 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 9732 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 564:
#line 3378 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9740 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 566:
#line 3385 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 9748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 567:
#line 3391 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 9761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 568:
#line 3400 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 9774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 569:
#line 3411 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 9782 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 570:
#line 3417 "parser_bison.y" /* yacc.c:1652  */
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
#line 9810 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 572:
#line 3444 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9821 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 575:
#line 3457 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9832 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 576:
#line 3466 "parser_bison.y" /* yacc.c:1652  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 9845 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 577:
#line 3476 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9851 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 578:
#line 3477 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9857 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 579:
#line 3478 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9863 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 580:
#line 3479 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9869 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 581:
#line 3480 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9875 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 582:
#line 3481 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9881 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 583:
#line 3482 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9887 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 584:
#line 3483 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9893 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 585:
#line 3484 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9899 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 586:
#line 3485 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9905 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 587:
#line 3486 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9911 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 588:
#line 3487 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9917 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 589:
#line 3488 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9923 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 590:
#line 3489 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9929 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 591:
#line 3490 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 9935 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 592:
#line 3494 "parser_bison.y" /* yacc.c:1652  */
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
#line 9960 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 593:
#line 3516 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 9966 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 594:
#line 3517 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 9972 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 595:
#line 3518 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 9978 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 596:
#line 3521 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 9984 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 597:
#line 3522 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 9990 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 598:
#line 3523 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 9996 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 599:
#line 3524 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 10002 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 600:
#line 3525 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 10008 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 601:
#line 3529 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10016 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 603:
#line 3536 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), NFT_OSF_F_VERSION);
			}
#line 10024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 604:
#line 3540 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 10032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 605:
#line 3546 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 10040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 606:
#line 3550 "parser_bison.y" /* yacc.c:1652  */
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
#line 10056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 608:
#line 3565 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10064 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 609:
#line 3569 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 611:
#line 3576 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 613:
#line 3583 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10088 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 615:
#line 3590 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10096 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 618:
#line 3600 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10109 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 619:
#line 3611 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 10117 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 620:
#line 3617 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10125 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 623:
#line 3627 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10133 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 627:
#line 3638 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10142 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 628:
#line 3645 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10151 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 629:
#line 3650 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 631:
#line 3658 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10168 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 632:
#line 3662 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10176 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 633:
#line 3666 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 10184 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 635:
#line 3673 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10193 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 636:
#line 3680 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10201 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 639:
#line 3690 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10209 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 640:
#line 3696 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 10217 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 642:
#line 3703 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 10225 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 643:
#line 3707 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 10233 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 644:
#line 3711 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 10241 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 645:
#line 3717 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 10249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 647:
#line 3724 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 10257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 648:
#line 3728 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 10265 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 649:
#line 3732 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->stmt = counter_stmt_alloc(&(yyloc));
			}
#line 10273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 650:
#line 3736 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *stmt;

				stmt = counter_stmt_alloc(&(yyloc));
				stmt->counter.packets = (yyvsp[-2].val);
				stmt->counter.bytes = (yyvsp[0].val);
				(yyvsp[-5].expr)->stmt = stmt;
			}
#line 10286 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 651:
#line 3745 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 10294 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 658:
#line 3763 "parser_bison.y" /* yacc.c:1652  */
    {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 10306 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 659:
#line 3773 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 10315 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 660:
#line 3780 "parser_bison.y" /* yacc.c:1652  */
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
#line 10337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 661:
#line 3800 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 10346 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 662:
#line 3807 "parser_bison.y" /* yacc.c:1652  */
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
#line 10364 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 663:
#line 3823 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 10373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 664:
#line 3829 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 10379 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 665:
#line 3830 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 10385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 666:
#line 3831 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 10391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 667:
#line 3834 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_TCP; }
#line 10397 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 668:
#line 3835 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_UDP; }
#line 10403 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 669:
#line 3839 "parser_bison.y" /* yacc.c:1652  */
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
#line 10422 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 670:
#line 3854 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 10430 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 671:
#line 3860 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 10440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 672:
#line 3866 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 10449 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 673:
#line 3874 "parser_bison.y" /* yacc.c:1652  */
    {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 10464 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 674:
#line 3887 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 10476 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 675:
#line 3895 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;

				ct = &(yyvsp[-6].obj)->ct_timeout;
				init_list_head(&ct->timeout_list);
				list_splice_tail((yyvsp[-2].list), &ct->timeout_list);
			}
#line 10488 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 676:
#line 3903 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 10496 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 677:
#line 3909 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 10504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 678:
#line 3913 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 10512 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 679:
#line 3917 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 10520 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 680:
#line 3921 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 10528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 681:
#line 3925 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 10536 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 682:
#line 3931 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 10544 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 683:
#line 3937 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;

				limit = &(yyvsp[-6].obj)->limit;
				limit->rate	= (yyvsp[-3].val);
				limit->unit	= (yyvsp[-1].val);
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-4].val);
			}
#line 10559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 684:
#line 3948 "parser_bison.y" /* yacc.c:1652  */
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
#line 10582 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 685:
#line 3969 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 10591 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 686:
#line 3976 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 10599 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 687:
#line 3980 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 10607 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 688:
#line 3984 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 689:
#line 3990 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 690:
#line 3996 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10635 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 691:
#line 4003 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 692:
#line 4004 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10647 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 693:
#line 4005 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10653 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 694:
#line 4006 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10659 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 696:
#line 4011 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10667 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 697:
#line 4015 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10675 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 699:
#line 4022 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10683 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 701:
#line 4029 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 703:
#line 4036 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10699 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 707:
#line 4047 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 708:
#line 4056 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10725 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 709:
#line 4066 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = true; }
#line 10731 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 710:
#line 4067 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = false; }
#line 10737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 711:
#line 4071 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 10747 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 712:
#line 4078 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 10753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 713:
#line 4079 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 10759 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 714:
#line 4080 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 10765 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 715:
#line 4081 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 10771 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 716:
#line 4082 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 10777 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 717:
#line 4083 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 10783 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 718:
#line 4084 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 10789 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 719:
#line 4085 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 10795 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 720:
#line 4086 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 10801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 721:
#line 4087 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 10807 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 722:
#line 4088 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 10813 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 723:
#line 4089 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 10819 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 724:
#line 4092 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10825 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 725:
#line 4093 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10831 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 726:
#line 4094 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10837 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 727:
#line 4095 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 728:
#line 4097 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10854 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 729:
#line 4104 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10865 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 730:
#line 4111 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10876 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 731:
#line 4118 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10887 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 732:
#line 4125 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10898 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 733:
#line 4132 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10909 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 734:
#line 4139 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10920 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 735:
#line 4146 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 736:
#line 4153 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10942 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 737:
#line 4160 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 738:
#line 4167 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10964 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 739:
#line 4174 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10975 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 740:
#line 4180 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 10981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 741:
#line 4183 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_EQ; }
#line 10987 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 742:
#line 4184 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_NEQ; }
#line 10993 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 743:
#line 4185 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LT; }
#line 10999 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 744:
#line 4186 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GT; }
#line 11005 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 745:
#line 4187 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GTE; }
#line 11011 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 746:
#line 4188 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LTE; }
#line 11017 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 747:
#line 4192 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 11025 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 748:
#line 4196 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 11033 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 749:
#line 4200 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 11041 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 750:
#line 4204 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 11049 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 751:
#line 4208 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 11057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 752:
#line 4212 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 11065 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 754:
#line 4219 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 11077 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 755:
#line 4229 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11085 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 756:
#line 4233 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11093 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 757:
#line 4237 "parser_bison.y" /* yacc.c:1652  */
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
#line 11111 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 760:
#line 4256 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_LEN; }
#line 11117 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 761:
#line 4257 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 11123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 762:
#line 4258 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 11129 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 763:
#line 4259 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 11135 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 764:
#line 4260 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECMARK; }
#line 11141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 765:
#line 4263 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_MARK; }
#line 11147 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 766:
#line 4264 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIF; }
#line 11153 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 767:
#line 4265 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 11159 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 768:
#line 4266 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 11165 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 769:
#line 4267 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIF; }
#line 11171 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 770:
#line 4268 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 11177 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 771:
#line 4269 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 11183 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 772:
#line 4270 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKUID; }
#line 11189 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 773:
#line 4271 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKGID; }
#line 11195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 774:
#line 4272 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 11201 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 775:
#line 4273 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 11207 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 776:
#line 4274 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 11213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 777:
#line 4275 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 11219 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 778:
#line 4276 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 11225 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 779:
#line 4277 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 11231 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 780:
#line 4278 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 11237 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 781:
#line 4279 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CPU; }
#line 11243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 782:
#line 4280 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 11249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 783:
#line 4281 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 11255 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 784:
#line 4282 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 11261 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 785:
#line 4283 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECPATH; }
#line 11267 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 786:
#line 4284 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_NS; }
#line 11273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 787:
#line 4285 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_DAY; }
#line 11279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 788:
#line 4286 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_HOUR; }
#line 11285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 789:
#line 4290 "parser_bison.y" /* yacc.c:1652  */
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
#line 11309 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 790:
#line 4310 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 11317 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 791:
#line 4314 "parser_bison.y" /* yacc.c:1652  */
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
#line 11335 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 792:
#line 4328 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 11343 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 793:
#line 4332 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 11351 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 794:
#line 4336 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 11359 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 795:
#line 4342 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11367 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 796:
#line 4347 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 11373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 797:
#line 4348 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_MARK; }
#line 11379 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 798:
#line 4351 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 11385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 799:
#line 4352 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 11391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 800:
#line 4355 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 11397 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 801:
#line 4356 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 11403 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 802:
#line 4360 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 11411 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 803:
#line 4365 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 11417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 804:
#line 4366 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 11423 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 805:
#line 4369 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_IN; }
#line 11429 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 806:
#line 4370 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_OUT; }
#line 11435 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 807:
#line 4373 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 11441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 808:
#line 4374 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 11447 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 809:
#line 4377 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 11453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 810:
#line 4378 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 11459 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 811:
#line 4382 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-1].val) > 255) {
					erec_queue(error(&(yylsp[-1]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 11471 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 812:
#line 4390 "parser_bison.y" /* yacc.c:1652  */
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
#line 11500 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 813:
#line 4417 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 11509 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 814:
#line 4422 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 11518 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 815:
#line 4427 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 11526 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 816:
#line 4432 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 11532 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 817:
#line 4433 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 11538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 818:
#line 4437 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 11546 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 819:
#line 4441 "parser_bison.y" /* yacc.c:1652  */
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
#line 11568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 820:
#line 4460 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 11574 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 821:
#line 4461 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 11580 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 822:
#line 4462 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 11586 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 823:
#line 4463 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_XFRM; }
#line 11592 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 824:
#line 4467 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1);
			}
#line 11600 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 825:
#line 4471 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 11608 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 826:
#line 4475 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 11616 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 827:
#line 4480 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 11622 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 828:
#line 4481 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 11628 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 829:
#line 4484 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 11634 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 830:
#line 4485 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 11640 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 831:
#line 4486 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_MARK; }
#line 11646 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 832:
#line 4487 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATE; }
#line 11652 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 833:
#line 4488 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 11658 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 834:
#line 4489 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 11664 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 835:
#line 4490 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 11670 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 836:
#line 4491 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 11676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 837:
#line 4492 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 11682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 838:
#line 4493 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 11688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 839:
#line 4494 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 11694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 840:
#line 4495 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 11700 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 841:
#line 4496 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 11706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 842:
#line 4497 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 11712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 843:
#line 4498 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SECMARK; }
#line 11718 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 845:
#line 4502 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 11724 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 846:
#line 4503 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 11730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 847:
#line 4504 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 11736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 848:
#line 4505 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 11742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 849:
#line 4506 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 11748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 850:
#line 4507 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 11754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 852:
#line 4511 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP; }
#line 11760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 853:
#line 4512 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP; }
#line 11766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 854:
#line 4513 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP6; }
#line 11772 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 855:
#line 4514 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP6; }
#line 11778 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 856:
#line 4517 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 11784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 857:
#line 4518 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 11790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 858:
#line 4519 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 11796 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 859:
#line 4520 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 11802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 862:
#line 4528 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11812 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 863:
#line 4534 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11822 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 864:
#line 4542 "parser_bison.y" /* yacc.c:1652  */
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
#line 11839 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 865:
#line 4555 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);

			}
#line 11850 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 866:
#line 4562 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 11860 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 867:
#line 4568 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 11868 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 868:
#line 4574 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11879 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 887:
#line 4603 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 11890 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 888:
#line 4611 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 11896 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 889:
#line 4612 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 11902 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 890:
#line 4613 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 11908 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 891:
#line 4617 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 11916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 892:
#line 4622 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 11922 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 893:
#line 4623 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 11928 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 894:
#line 4624 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 11934 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 895:
#line 4628 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 11942 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 896:
#line 4633 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_VID; }
#line 11948 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 897:
#line 4634 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_CFI; }
#line 11954 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 898:
#line 4635 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_PCP; }
#line 11960 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 899:
#line 4636 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 11966 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 900:
#line 4640 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 11974 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 901:
#line 4645 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HRD; }
#line 11980 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 902:
#line 4646 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PRO; }
#line 11986 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 903:
#line 4647 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HLN; }
#line 11992 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 904:
#line 4648 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PLN; }
#line 11998 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 905:
#line 4649 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_OP; }
#line 12004 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 906:
#line 4650 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 12010 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 907:
#line 4651 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 12016 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 908:
#line 4652 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_IP; }
#line 12022 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 909:
#line 4653 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_IP; }
#line 12028 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 910:
#line 4657 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 12036 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 911:
#line 4661 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val), 0);
			}
#line 12044 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 912:
#line 4665 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[0].val), IPOPT_FIELD_TYPE, 0);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 12053 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 913:
#line 4671 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_VERSION; }
#line 12059 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 914:
#line 4672 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 12065 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 915:
#line 4673 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DSCP; }
#line 12071 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 916:
#line 4674 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ECN; }
#line 12077 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 917:
#line 4675 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 12083 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 918:
#line 4676 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ID; }
#line 12089 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 919:
#line 4677 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 12095 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 920:
#line 4678 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_TTL; }
#line 12101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 921:
#line 4679 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 12107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 922:
#line 4680 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 12113 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 923:
#line 4681 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_SADDR; }
#line 12119 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 924:
#line 4682 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DADDR; }
#line 12125 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 925:
#line 4685 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_LSRR; }
#line 12131 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 926:
#line 4686 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RR; }
#line 12137 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 927:
#line 4687 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_SSRR; }
#line 12143 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 928:
#line 4688 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RA; }
#line 12149 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 929:
#line 4691 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 12155 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 930:
#line 4692 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 12161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 931:
#line 4693 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 12167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 932:
#line 4694 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_PTR; }
#line 12173 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 933:
#line 4695 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 12179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 934:
#line 4699 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 12187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 935:
#line 4704 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 12193 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 936:
#line 4705 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 12199 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 937:
#line 4706 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 12205 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 938:
#line 4707 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_ID; }
#line 12211 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 939:
#line 4708 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 12217 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 940:
#line 4709 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 12223 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 941:
#line 4710 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 12229 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 942:
#line 4714 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[0].val));
			}
#line 12237 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 943:
#line 4719 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_TYPE; }
#line 12243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 944:
#line 4720 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 12249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 945:
#line 4721 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_MRT; }
#line 12255 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 946:
#line 4722 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_GROUP; }
#line 12261 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 947:
#line 4726 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 12269 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 948:
#line 4731 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 12275 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 949:
#line 4732 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 12281 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 950:
#line 4733 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_ECN; }
#line 12287 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 951:
#line 4734 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 12293 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 952:
#line 4735 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 12299 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 953:
#line 4736 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 12305 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 954:
#line 4737 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 12311 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 955:
#line 4738 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 12317 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 956:
#line 4739 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 12323 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 957:
#line 4742 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 12331 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 958:
#line 4747 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 12337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 959:
#line 4748 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 12343 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 960:
#line 4749 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 12349 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 961:
#line 4750 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 12355 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 962:
#line 4751 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 12361 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 963:
#line 4752 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 12367 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 964:
#line 4753 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 12373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 965:
#line 4754 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 12379 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 966:
#line 4758 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 12387 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 967:
#line 4763 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 12393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 968:
#line 4764 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 12399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 969:
#line 4765 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 12405 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 970:
#line 4766 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SPI; }
#line 12411 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 971:
#line 4767 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 12417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 972:
#line 4771 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 12425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 973:
#line 4776 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SPI; }
#line 12431 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 974:
#line 4777 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 12437 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 975:
#line 4781 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 12445 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 976:
#line 4786 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 12451 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 977:
#line 4787 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 12457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 978:
#line 4788 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_CPI; }
#line 12463 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 979:
#line 4792 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 12471 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 980:
#line 4797 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 12477 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 981:
#line 4798 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 12483 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 982:
#line 4799 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 12489 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 983:
#line 4800 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 12495 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 984:
#line 4804 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 12503 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 985:
#line 4809 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 12509 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 986:
#line 4810 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 12515 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 987:
#line 4811 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 12521 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 988:
#line 4812 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 12527 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 989:
#line 4816 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 12535 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 990:
#line 4820 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 12543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 991:
#line 4824 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 12552 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 992:
#line 4830 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 12558 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 993:
#line 4831 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 12564 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 994:
#line 4832 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 12570 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 995:
#line 4833 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 12576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 996:
#line 4834 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 12582 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 997:
#line 4835 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 12588 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 998:
#line 4836 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 12594 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 999:
#line 4837 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 12600 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1000:
#line 4838 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 12606 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1001:
#line 4839 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 12612 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1002:
#line 4842 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 12618 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1003:
#line 4843 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 12624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1004:
#line 4844 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 12630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1005:
#line 4845 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 12636 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1006:
#line 4846 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 12642 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1007:
#line 4847 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 12648 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1008:
#line 4848 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 12654 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1009:
#line 4849 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 12660 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1010:
#line 4850 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 12666 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1011:
#line 4851 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 12672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1012:
#line 4852 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 12678 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1013:
#line 4853 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 12684 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1014:
#line 4856 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 12690 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1015:
#line 4857 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 12696 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1016:
#line 4858 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 12702 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1017:
#line 4859 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 12708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1018:
#line 4860 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 12714 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1019:
#line 4861 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 12720 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1020:
#line 4862 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 12726 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1021:
#line 4863 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 12732 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1022:
#line 4867 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 12740 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1023:
#line 4872 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 12746 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1024:
#line 4873 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 12752 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1025:
#line 4874 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 12758 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1026:
#line 4878 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 12766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1027:
#line 4883 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 12772 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1028:
#line 4884 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 12778 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1029:
#line 4885 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 12784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1030:
#line 4886 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 12790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1031:
#line 4890 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[0].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 12800 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1032:
#line 4897 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_SPORT; }
#line 12806 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1033:
#line 4898 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_DPORT; }
#line 12812 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1042:
#line 4912 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 12820 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1043:
#line 4917 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 12826 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1044:
#line 4918 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 12832 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1045:
#line 4922 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 12840 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1046:
#line 4927 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 12846 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1047:
#line 4928 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 12852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1048:
#line 4929 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_TYPE; }
#line 12858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1049:
#line 4930 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 12864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1050:
#line 4934 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 12872 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1051:
#line 4940 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 12880 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1052:
#line 4946 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 12888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1053:
#line 4951 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 12894 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1054:
#line 4955 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 12902 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1055:
#line 4960 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 12908 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1056:
#line 4961 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 12914 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1057:
#line 4962 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_TAG; }
#line 12920 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1058:
#line 4964 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 12928 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1059:
#line 4970 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 12936 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1060:
#line 4975 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 12942 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1061:
#line 4976 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 12948 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1062:
#line 4977 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 12954 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1063:
#line 4978 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 12960 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1064:
#line 4979 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 12966 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1065:
#line 4980 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_ID; }
#line 12972 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1066:
#line 4984 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 12980 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1067:
#line 4989 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 12986 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1068:
#line 4990 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 12992 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1069:
#line 4994 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 13000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1070:
#line 4999 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 13006 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1071:
#line 5000 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 13012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1072:
#line 5001 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_TYPE; }
#line 13018 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1073:
#line 5002 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 13024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1074:
#line 5003 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 13030 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1075:
#line 5007 "parser_bison.y" /* yacc.c:1652  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 13046 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1076:
#line 5020 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 13052 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1077:
#line 5021 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 13058 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1078:
#line 5022 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 13064 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1079:
#line 5023 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 13070 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1080:
#line 5024 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_MH; }
#line 13076 "parser_bison.c" /* yacc.c:1652  */
    break;


#line 13080 "parser_bison.c" /* yacc.c:1652  */
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
#line 5027 "parser_bison.y" /* yacc.c:1918  */

