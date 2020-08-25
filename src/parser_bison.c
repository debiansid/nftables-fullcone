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
#define YYLAST   6632

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  330
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  339
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1088
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1778

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
    1178,  1182,  1189,  1193,  1197,  1201,  1205,  1209,  1213,  1217,
    1221,  1225,  1229,  1235,  1241,  1245,  1249,  1253,  1257,  1261,
    1265,  1269,  1273,  1277,  1281,  1285,  1289,  1293,  1297,  1301,
    1305,  1309,  1313,  1317,  1321,  1325,  1329,  1333,  1337,  1341,
    1345,  1349,  1353,  1357,  1361,  1365,  1369,  1373,  1377,  1383,
    1387,  1391,  1395,  1399,  1403,  1409,  1413,  1417,  1421,  1425,
    1429,  1433,  1439,  1446,  1452,  1460,  1466,  1474,  1483,  1484,
    1487,  1488,  1489,  1490,  1491,  1492,  1493,  1494,  1497,  1498,
    1501,  1502,  1503,  1506,  1515,  1521,  1535,  1536,  1537,  1538,
    1539,  1550,  1560,  1571,  1581,  1592,  1603,  1612,  1621,  1630,
    1641,  1652,  1666,  1672,  1673,  1674,  1675,  1676,  1677,  1678,
    1685,  1696,  1709,  1714,  1715,  1716,  1717,  1722,  1728,  1733,
    1738,  1743,  1748,  1753,  1758,  1761,  1762,  1765,  1769,  1772,
    1773,  1774,  1775,  1779,  1784,  1785,  1786,  1787,  1792,  1802,
    1813,  1824,  1836,  1845,  1854,  1863,  1872,  1877,  1882,  1885,
    1889,  1895,  1896,  1900,  1905,  1906,  1907,  1908,  1922,  1926,
    1932,  1939,  1944,  1949,  1952,  1961,  1973,  1980,  1981,  1993,
    1998,  1999,  2000,  2001,  2007,  2008,  2009,  2010,  2016,  2017,
    2018,  2019,  2026,  2030,  2031,  2032,  2038,  2039,  2040,  2041,
    2047,  2048,  2049,  2050,  2056,  2057,  2058,  2059,  2065,  2066,
    2067,  2068,  2074,  2075,  2076,  2077,  2078,  2081,  2111,  2118,
    2122,  2125,  2135,  2143,  2154,  2167,  2182,  2183,  2186,  2198,
    2202,  2205,  2211,  2224,  2229,  2238,  2239,  2242,  2245,  2246,
    2247,  2250,  2265,  2266,  2269,  2270,  2271,  2272,  2273,  2274,
    2277,  2286,  2295,  2303,  2311,  2319,  2327,  2335,  2343,  2351,
    2359,  2367,  2375,  2383,  2391,  2399,  2407,  2415,  2419,  2424,
    2432,  2439,  2446,  2459,  2463,  2470,  2474,  2480,  2492,  2498,
    2505,  2506,  2507,  2508,  2511,  2512,  2513,  2514,  2515,  2516,
    2517,  2518,  2519,  2520,  2521,  2522,  2523,  2524,  2525,  2526,
    2527,  2528,  2529,  2532,  2536,  2542,  2548,  2553,  2556,  2561,
    2566,  2569,  2575,  2580,  2588,  2589,  2591,  2595,  2603,  2607,
    2610,  2614,  2620,  2621,  2624,  2630,  2634,  2637,  2642,  2647,
    2652,  2657,  2662,  2668,  2698,  2702,  2706,  2710,  2714,  2720,
    2724,  2727,  2731,  2737,  2746,  2765,  2773,  2774,  2775,  2778,
    2779,  2782,  2783,  2798,  2814,  2822,  2823,  2824,  2827,  2828,
    2831,  2832,  2833,  2848,  2849,  2850,  2851,  2852,  2855,  2858,
    2865,  2869,  2880,  2891,  2901,  2907,  2910,  2911,  2914,  2920,
    2926,  2932,  2939,  2946,  2954,  2955,  2958,  2962,  2970,  2974,
    2977,  2982,  2987,  2991,  2997,  3013,  3032,  3038,  3039,  3045,
    3046,  3052,  3053,  3054,  3055,  3056,  3057,  3058,  3059,  3060,
    3061,  3062,  3063,  3064,  3067,  3068,  3072,  3078,  3079,  3085,
    3086,  3092,  3093,  3099,  3102,  3103,  3114,  3115,  3118,  3122,
    3125,  3131,  3137,  3148,  3149,  3150,  3153,  3154,  3155,  3158,
    3162,  3166,  3171,  3176,  3181,  3187,  3191,  3195,  3199,  3205,
    3211,  3216,  3225,  3235,  3236,  3239,  3242,  3246,  3251,  3257,
    3258,  3261,  3264,  3268,  3272,  3276,  3281,  3288,  3293,  3301,
    3306,  3315,  3316,  3322,  3323,  3324,  3327,  3328,  3331,  3337,
    3341,  3344,  3349,  3355,  3356,  3362,  3363,  3366,  3367,  3370,
    3376,  3383,  3390,  3400,  3401,  3402,  3405,  3413,  3424,  3431,
    3434,  3440,  3444,  3447,  3453,  3462,  3473,  3479,  3505,  3506,
    3515,  3516,  3519,  3528,  3539,  3540,  3541,  3542,  3543,  3544,
    3545,  3546,  3547,  3548,  3549,  3550,  3551,  3552,  3553,  3556,
    3579,  3580,  3581,  3584,  3585,  3586,  3587,  3588,  3591,  3595,
    3598,  3602,  3609,  3612,  3626,  3627,  3631,  3637,  3638,  3644,
    3645,  3651,  3652,  3658,  3661,  3662,  3673,  3679,  3685,  3686,
    3689,  3695,  3696,  3697,  3700,  3707,  3712,  3717,  3720,  3724,
    3728,  3734,  3735,  3742,  3748,  3749,  3752,  3758,  3762,  3765,
    3769,  3773,  3779,  3783,  3786,  3790,  3794,  3798,  3807,  3813,
    3814,  3817,  3818,  3821,  3822,  3825,  3836,  3842,  3863,  3869,
    3886,  3892,  3893,  3894,  3897,  3898,  3901,  3917,  3923,  3929,
    3936,  3950,  3958,  3966,  3972,  3976,  3980,  3984,  3988,  3995,
    4000,  4011,  4033,  4039,  4043,  4047,  4053,  4059,  4067,  4068,
    4069,  4070,  4073,  4074,  4078,  4084,  4085,  4091,  4092,  4098,
    4099,  4105,  4108,  4109,  4110,  4119,  4130,  4131,  4134,  4142,
    4143,  4144,  4145,  4146,  4147,  4148,  4149,  4150,  4151,  4152,
    4153,  4156,  4157,  4158,  4159,  4160,  4167,  4174,  4181,  4188,
    4195,  4202,  4209,  4216,  4223,  4230,  4237,  4244,  4247,  4248,
    4249,  4250,  4251,  4252,  4255,  4259,  4263,  4267,  4271,  4275,
    4281,  4282,  4292,  4296,  4300,  4316,  4317,  4320,  4321,  4322,
    4323,  4324,  4327,  4328,  4329,  4330,  4331,  4332,  4333,  4334,
    4335,  4336,  4337,  4338,  4339,  4340,  4341,  4342,  4343,  4344,
    4345,  4346,  4347,  4348,  4349,  4350,  4353,  4373,  4377,  4391,
    4395,  4399,  4405,  4411,  4412,  4415,  4416,  4419,  4420,  4423,
    4429,  4430,  4433,  4434,  4437,  4438,  4441,  4442,  4445,  4453,
    4480,  4485,  4490,  4496,  4497,  4500,  4504,  4524,  4525,  4526,
    4527,  4530,  4534,  4538,  4544,  4545,  4548,  4549,  4550,  4551,
    4552,  4553,  4554,  4555,  4556,  4557,  4558,  4559,  4560,  4561,
    4562,  4563,  4564,  4567,  4568,  4569,  4570,  4571,  4572,  4573,
    4576,  4577,  4578,  4579,  4582,  4583,  4584,  4585,  4588,  4589,
    4592,  4598,  4606,  4619,  4626,  4632,  4638,  4647,  4648,  4649,
    4650,  4651,  4652,  4653,  4654,  4655,  4656,  4657,  4658,  4659,
    4660,  4661,  4662,  4663,  4664,  4667,  4676,  4677,  4678,  4681,
    4687,  4688,  4689,  4692,  4698,  4699,  4700,  4701,  4704,  4710,
    4711,  4712,  4713,  4714,  4715,  4716,  4717,  4718,  4721,  4725,
    4729,  4736,  4737,  4738,  4739,  4740,  4741,  4742,  4743,  4744,
    4745,  4746,  4747,  4750,  4751,  4752,  4753,  4756,  4757,  4758,
    4759,  4760,  4763,  4769,  4770,  4771,  4772,  4773,  4774,  4775,
    4778,  4784,  4785,  4786,  4787,  4790,  4796,  4797,  4798,  4799,
    4800,  4801,  4802,  4803,  4804,  4806,  4812,  4813,  4814,  4815,
    4816,  4817,  4818,  4819,  4822,  4828,  4829,  4830,  4831,  4832,
    4835,  4841,  4842,  4845,  4851,  4852,  4853,  4856,  4862,  4863,
    4864,  4865,  4868,  4874,  4875,  4876,  4877,  4880,  4884,  4888,
    4895,  4896,  4897,  4898,  4899,  4900,  4901,  4902,  4903,  4904,
    4907,  4908,  4909,  4910,  4911,  4912,  4913,  4914,  4915,  4916,
    4917,  4918,  4921,  4922,  4923,  4924,  4925,  4926,  4927,  4928,
    4931,  4937,  4938,  4939,  4942,  4948,  4949,  4950,  4951,  4954,
    4962,  4963,  4966,  4967,  4968,  4969,  4970,  4971,  4972,  4973,
    4976,  4982,  4983,  4986,  4992,  4993,  4994,  4995,  4998,  5004,
    5010,  5016,  5019,  5025,  5026,  5027,  5028,  5034,  5040,  5041,
    5042,  5043,  5044,  5045,  5048,  5054,  5055,  5058,  5064,  5065,
    5066,  5067,  5068,  5071,  5085,  5086,  5087,  5088,  5089
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

#define YYPACT_NINF -1402

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1402)))

#define YYTABLE_NINF -870

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1402,  6198, -1402,   260, -1402, -1402,    74,    95,    95,    95,
    1038,  1038,  1038,  1038,  1038,  1038,  1038,  1038, -1402, -1402,
    2763,   106,  1863,   112,  1249,   151,  4509,   153,  1369,   186,
    5696,   132,   143,   107, -1402, -1402, -1402, -1402,    65,  1038,
    1038,  1038,  1038, -1402, -1402, -1402,   859, -1402,    95, -1402,
      95,    56,  5102, -1402,   260, -1402,   -84,   -51,   260,    95,
   -1402,    -5,    10,  5102,    95, -1402,    14, -1402,    95, -1402,
   -1402,  1038, -1402,  1038,  1038,  1038,  1038,  1038,  1038,  1038,
     227,  1038,  1038,  1038,  1038, -1402,  1038, -1402,  1038,  1038,
    1038,  1038,  1038,  1038,  1038,  1038,   231,  1038,  1038,  1038,
    1038, -1402,  1038, -1402,  1038,  1038,  1038,  1038,  1038,   651,
    1038,  1038,  1038,  1038,  1038,    98,  1038,  1038,  1038,    47,
    1038,  1059,  1653,  1869,  1930,  1038,  1038,  1038,  2035, -1402,
    1038,  2201,  2291,  1038, -1402,  1038,  1038,  1038,  1038,  1038,
     250,  1038, -1402,  1038, -1402,   499,   439,    87,   218, -1402,
   -1402, -1402, -1402,   518,   790,  1011,  1157,  1462,   876,   178,
    2475,   703,   837,   338,   584,   675,   803,  2522,    69,   358,
    2644,   193,   245,   595,    58,   747,   200,   465,  3363, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
    5504, -1402, -1402,   127,  5330,   169,   828,   394,  5696,    95,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402,   639, -1402, -1402,   166, -1402,
   -1402,   639, -1402, -1402, -1402, -1402,  1584,  1038,  1038,  1038,
     232, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   409,   427,
     432, -1402, -1402, -1402,    90,   291,   740, -1402, -1402, -1402,
   -1402, -1402, -1402,     7,     7, -1402,   150,    95,  3592,  4720,
     303, -1402,    12,   161, -1402, -1402, -1402, -1402, -1402, -1402,
     488,   121, -1402,   569, -1402,   270,  5102, -1402, -1402, -1402,
   -1402, -1402, -1402,   486, -1402,   530, -1402, -1402, -1402,   298,
   -1402,  3174, -1402, -1402,   549, -1402,    23, -1402,   176, -1402,
   -1402, -1402,   712, -1402,    72, -1402, -1402,   540, -1402, -1402,
   -1402,   794,   598,   594,   295, -1402,   445, -1402,  4328, -1402,
   -1402, -1402,   575, -1402, -1402, -1402,   579, -1402,  4689,  4689,
   -1402, -1402,   600,   317,   320, -1402, -1402,   325, -1402, -1402,
   -1402,   337, -1402,   348,   596,  5102, -1402,    -5,    10, -1402,
      14, -1402, -1402,  1038,  1038,  1038,   232, -1402, -1402, -1402,
    5102,    82, -1402, -1402,    92, -1402, -1402,   118, -1402, -1402,
   -1402,   126, -1402, -1402,    14, -1402,   168,   370, -1402, -1402,
   -1402, -1402,  1038, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402,    14, -1402, -1402, -1402, -1402, -1402, -1402,  1038, -1402,
   -1402, -1402, -1402, -1402, -1402,  1038,  1038, -1402, -1402, -1402,
     663,   665,   677,  1038, -1402,  1038, -1402,  1038, -1402,  1038,
   -1402,  1038, -1402, -1402, -1402, -1402,  1038, -1402, -1402,  1038,
   -1402,  1038, -1402, -1402, -1402, -1402, -1402, -1402, -1402,  1038,
   -1402,    95, -1402, -1402, -1402,   717, -1402, -1402, -1402, -1402,
   -1402,   743,   286, -1402, -1402, -1402,   673,     9, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
      43,   236, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
     994, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402,  2805, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   252, -1402,
   -1402,   444, -1402, -1402, -1402, -1402, -1402, -1402,   449, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402,  2324, -1402, -1402, -1402, -1402,   505,   140,   515,   687,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   521,   493,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402,   639, -1402, -1402, -1402,   572,   576,   591,   997, -1402,
   -1402, -1402,  3403,   769,  4475,  5696, -1402, -1402, -1402, -1402,
     821,   854,    -3,   819,   867,   869,    25,   875,  2324,   885,
    4475,  4475,   605,  4475, -1402, -1402,   787,  4475,  4475,   822,
   -1402,  4760,    44, -1402,   997, -1402, -1402,   839,   842,   486,
   -1402,   134,   997,   853,   868,   888,   997,   530, -1402,   280,
   -1402,  4475, -1402, -1402,  3632,   877,   790,  1011,  1157,  3865,
   -1402,  3105,   392, -1402, -1402, -1402,   883, -1402, -1402, -1402,
   -1402,  5910, -1402,   865,   959,   973,   682,   434,   163, -1402,
   -1402, -1402, -1402, -1402,  1009,   762,  1012, -1402, -1402, -1402,
   -1402,  1017, -1402, -1402, -1402, -1402,   246, -1402, -1402,  1026,
    1029, -1402,   943,   958, -1402, -1402,   549, -1402,  1063, -1402,
   -1402, -1402, -1402,  1065, -1402,  3861, -1402,  1065,  4475, -1402,
   -1402,   712, -1402,  1070, -1402,    95, -1402,   758, -1402,    95,
      60, -1402,  6305,  6305,  6305,  6305,  6305,  5696,    26,  4689,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402,  6305, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402,  1081, -1402,   891,  1073,  1076,   777,   522,  1097,
   -1402, -1402, -1402,  4689,  4475,  4475,   260,  1081, -1402,   260,
    1013, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   600,
     798,   841,   850, -1402,   851,   856, -1402, -1402, -1402,   572,
     576,   591,   997, -1402,  1061,  1064,  1080,  1082, -1402,  1091,
     881, -1402, -1402, -1402, -1402, -1402,  1038,  1038,  1038, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,  1099,
     439, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402,   466, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   948,
   -1402,  1104,  1115, -1402, -1402,   812, -1402,   846, -1402, -1402,
   -1402, -1402, -1402, -1402,  1116,  1120,   922,  1133,    68, -1402,
   -1402, -1402,   915,   928,   929,  1164, -1402,   605, -1402,  1165,
   -1402, -1402, -1402,  4475,  1462,  2475,  1171,  4090, -1402,    72,
     111,  1253,   997,   997,  1170,  5696,  4475,  4475,  4475, -1402,
    1180,  4475,  1231,  4475, -1402, -1402, -1402, -1402,  1185, -1402,
      30,  1245, -1402,  4475, -1402,   569,   975,    28, -1402,   539,
    1097,   569, -1402, -1402, -1402, -1402, -1402, -1402, -1402,  1144,
     339, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
    1176,  1179,  1225,  1184, -1402,  4475,  1292,  4475,  4475,   977,
   -1402, -1402,  5910,  5910,  5910,  5910,  5910,  1198,  5910,  5910,
      71,  4475,  1065,  4475,  1227,  1299,  1232,  4296,  4296, -1402,
   -1402, -1402,  4475,   762,  4475,   762, -1402, -1402,   690, -1402,
    5696, -1402,  5696, -1402, -1402, -1402,   891,  1073,  1076, -1402,
     569, -1402, -1402, -1402,   988,  6305,  6305,  6305,  6305,  6305,
    6305,  6305,  1218,  6305,  6305, -1402, -1402, -1402, -1402, -1402,
     397,  1777,  2309,  1789,   100,   212, -1402, -1402, -1402, -1402,
   -1402, -1402,   998,   999,  1001, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,  1319,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402,  1005,  1010, -1402, -1402,
   -1402, -1402,   922,   -77,  1240, -1402, -1402, -1402, -1402, -1402,
     890, -1402, -1402, -1402,  1077,  1244,    30, -1402,  4475,  4475,
    1340, -1402,  1246,  1246, -1402,   111, -1402, -1402, -1402,  1024,
    1253,  5102,   111, -1402, -1402, -1402, -1402, -1402,  4475, -1402,
     104, -1402, -1402,  1087,  4475,  1316, -1402,  6207, -1402,  1246,
    1246,  1109, -1402,    28, -1402,  4760, -1402, -1402, -1402, -1402,
    1352, -1402,  1262,  1264, -1402,  1266, -1402,  4475, -1402, -1402,
   -1402, -1402, -1402,   865,   959,   973, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402,  1368,  4475,  1216,  4475, -1402, -1402, -1402,
   -1402,   762, -1402,   762,  1065, -1402,    45,  5102,  4923,    51,
   -1402, -1402, -1402, -1402, -1402,   891,  1073,  1076, -1402, -1402,
   -1402, -1402,   539,  1279,  1343,    95,    95,    95,    95,    95,
    1280,   267,    95,    95,    95,    95, -1402, -1402, -1402,   260,
      37,  1281,  1288, -1402, -1402, -1402,   260,   260,   260,   260,
    5696, -1402,  1246,  1246,  1069,   918,  1285,   456,  1147,   260,
   -1402, -1402, -1402,   260,  5696,  1246,  1075,   456,  1147, -1402,
   -1402, -1402,   260,  1300,  1083, -1402, -1402, -1402, -1402,  1915,
    2637,  1993,   634,   689, -1402, -1402, -1402,  1474,  1286, -1402,
   -1402, -1402,  1302, -1402, -1402, -1402, -1402, -1402,   497,   640,
    1213,  1303,   116,  1087, -1402, -1402,  4475, -1402, -1402, -1402,
   -1402,  5696,  1084,   111, -1402,   880,  1141,  1308, -1402, -1402,
    4475,   569,  1097, -1402, -1402, -1402,  1310, -1402,   339, -1402,
   -1402, -1402, -1402,  4475, -1402,  1334, -1402,  1065,  1065,  5696,
    1233, -1402,    42,  1101,  1415,   569, -1402,  1239,  1332, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,    95,
      95,    95, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402,  1393, -1402, -1402, -1402, -1402, -1402,   753, -1402,
     260,   260,    14, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402,   825, -1402, -1402, -1402, -1402, -1402,
     672, -1402, -1402, -1402,   405,   260,    14,   502,   672, -1402,
    1287,  1113, -1402, -1402, -1402, -1402, -1402,  1161,  1142,  2112,
   -1402, -1402,   922,  1117,   329,  1038, -1402, -1402, -1402, -1402,
    1246,  1336,   329,  1339,  1038, -1402, -1402, -1402, -1402,  1341,
    1038, -1402, -1402, -1402, -1402, -1402,   880,  1141, -1402, -1402,
    5102, -1402, -1402, -1402, -1402, -1402, -1402,  1177,  1344, -1402,
      30, -1402, -1402,  1195, -1402, -1402,  4475,  1127,  5696, -1402,
   -1402,  1167,  4923, -1402, -1402,  1421,   260,  1138,  1139,  1140,
    1146,  1149, -1402, -1402, -1402,  1150,  1152,  1154,  1155,  1378,
    5696, -1402, -1402, -1402, -1402,   456, -1402,  1147, -1402,  5482,
   -1402, -1402,  1965, -1402,   128,   260,  1389,   260, -1402, -1402,
   -1402, -1402,  1169, -1402, -1402,   260,   260,   260,   260,   260,
     260,   260,  1363,   260,  1177, -1402,  1172,  1398, -1402,    34,
   -1402,  1404, -1402, -1402,  1182,   569, -1402, -1402,  1239, -1402,
   -1402, -1402, -1402, -1402,  1187,  1188,  1191, -1402, -1402, -1402,
   -1402,  1043, -1402, -1402, -1402,  5696,   753,   456,   260,   260,
     260,   260,   825,  1418, -1402, -1402, -1402,   531, -1402, -1402,
   -1402, -1402, -1402,    52, -1402, -1402,  1419, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402,   329, -1402, -1402, -1402,  1272, -1402,
   -1402, -1402, -1402, -1402,  1421,  1925,  2939,  2458,  1304,  1521,
   -1402, -1402, -1402,   627,  1019,   671,   489,   997,  1203,  1287,
     753, -1402,   825, -1402, -1402, -1402, -1402, -1402, -1402,  1426,
    1428,   162, -1402,  1525,    55, -1402,   260, -1402, -1402,   260,
   -1402, -1402, -1402,   260,   260,   260,   260,  1865,  1836,  2350,
     260, -1402, -1402, -1402,   260, -1402, -1402, -1402,   260, -1402,
   -1402, -1402,   260, -1402, -1402, -1402, -1402,  1113, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402,  1432,  1419,   260, -1402, -1402,
   -1402, -1402, -1402, -1402,   260,   260,   260, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     312,   312,   312,   312,   312,   312,   312,   312,   316,   319,
     312,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   148,   318,   317,   314,   315,     0,   312,
     312,   312,   312,    14,    13,     3,     0,    17,     0,   313,
       0,   337,     0,    12,     0,   307,     0,     0,     0,     0,
     466,    32,    34,     0,     0,   192,     0,   213,     0,   233,
      18,   312,    19,   312,   312,   312,   312,   312,   312,   312,
       0,   312,   312,   312,   312,    20,   312,    21,   312,   312,
     312,   312,   312,   312,   312,   312,     0,   312,   312,   312,
     312,    22,   312,    23,   312,   312,   343,   312,   343,   343,
     312,   312,   343,   312,   343,     0,   312,   343,   343,     0,
     312,   343,   343,   343,   343,   312,   312,   312,   343,    24,
     312,   343,   343,   312,    25,   312,   312,   312,   312,   343,
       0,   312,    26,   312,    27,     0,     0,     0,   612,   583,
     308,   309,   310,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   772,
     773,   774,   775,   776,   777,   778,   779,   780,   781,   782,
     783,   784,   785,   786,   787,   788,   789,   790,   791,   793,
       0,   795,   794,     0,     0,     0,     0,   792,     0,     0,
      31,   579,   578,   584,   585,   163,   595,   596,   589,   763,
     590,   593,   597,   594,   591,   592,   586,   877,   878,   879,
     880,   881,   882,   883,   884,   885,   886,   887,   888,   889,
     890,   891,   892,   893,   894,   587,  1042,  1043,  1044,  1045,
    1046,  1047,  1048,  1049,   588,     0,   160,   161,     0,    28,
     144,     0,    29,   146,   149,    30,   150,   312,   312,   312,
      42,   692,   668,   670,    16,    15,   320,   322,     0,     0,
       0,   339,   338,   340,     0,   456,     0,   563,   564,   565,
     754,   755,   756,     0,     0,   759,   570,     0,     0,     0,
     386,   394,     0,   418,   439,   446,   447,   525,   531,   548,
       0,     0,   799,     7,    37,   345,   347,   358,   348,   354,
     374,   353,   350,   384,   360,   392,   351,   352,   361,   440,
     362,     0,   363,   372,   454,   366,   524,   367,   530,   368,
     369,   364,   546,   370,     0,   371,   356,     0,   569,   355,
     614,   617,   619,   621,   623,   624,   631,   633,     0,   632,
     576,   373,   763,   359,   365,   357,   586,     8,     0,     0,
      11,   331,     0,     0,     0,    36,   325,     0,    40,   206,
     205,     0,   328,     0,     0,     0,   466,    52,    54,   192,
       0,   213,   233,   312,   312,   312,    60,   692,   668,   670,
       0,     0,    91,    92,     0,    70,    71,     0,    72,    73,
      74,     0,    75,    76,     0,    77,     0,    79,    80,   672,
     673,   671,   312,    82,    83,    87,    88,    84,    85,    89,
      90,     0,   115,    94,   344,    95,    96,    97,   312,    98,
     100,   124,   123,   122,   116,   312,   343,   120,   119,   121,
     672,   673,     0,   312,   103,   312,   101,   312,   104,   312,
     107,   312,   113,   109,   106,   112,   312,   110,   131,   312,
     129,   312,   132,   134,   135,   136,   137,   138,   141,   312,
     140,     0,   896,   897,   898,     0,   603,   604,   605,   606,
     607,   609,     0,   803,   804,   802,     0,     0,  1040,  1041,
    1039,   900,   901,   902,   899,   907,   904,   905,   906,   903,
       0,     0,   909,   910,   911,   912,   913,   908,   931,   932,
     926,   921,   922,   923,   924,   925,   927,   928,   929,   930,
       0,   918,   943,   946,   945,   944,   947,   948,   949,   942,
     951,   952,   953,   954,   950,   963,   964,   956,   957,   958,
     960,   959,   961,   962,   955,   966,   971,   968,   967,   972,
     970,   969,   973,   965,   976,   979,   975,   977,   978,   974,
     982,   981,   980,   984,   985,   986,   983,   990,   991,   988,
     989,   987,   996,   993,   994,   995,   992,  1008,  1002,  1005,
    1006,  1000,  1001,  1003,  1004,  1007,  1009,     0,   997,  1033,
    1031,  1032,  1030,  1038,  1035,  1036,  1037,  1034,  1056,   823,
    1055,   829,   824,  1054,  1057,   827,   828,   830,     0,   825,
    1053,     0,  1058,  1061,  1060,  1064,  1063,  1065,     0,  1062,
    1052,  1051,  1050,  1073,  1070,  1068,  1069,  1071,  1072,  1067,
    1076,  1075,  1074,  1080,  1079,  1082,  1078,  1081,  1077,   764,
     767,   768,   769,   771,   770,   792,   762,   765,   766,   844,
     845,   851,   837,   838,   836,   846,   847,   867,   840,   849,
     842,   843,   848,   839,   841,   834,   835,   865,   864,   866,
     850,     0,   831,   852,   808,   807,     0,   631,     0,     0,
    1085,  1084,  1086,  1087,  1088,  1083,   812,   813,   811,     0,
     577,   143,   162,   145,   151,   152,   154,   153,   156,   157,
     155,   158,   689,   689,   689,     0,     0,   418,     0,   334,
     335,   336,     0,     0,     0,     0,   761,   760,   757,   758,
       0,     0,     0,   764,   762,     0,     0,     0,     0,   831,
       0,     0,   427,     0,   416,   417,     0,     0,     0,     0,
       6,     0,     0,   635,     0,   346,   349,     0,     0,   385,
     388,     0,     0,     0,     0,     0,     0,   393,   395,     0,
     438,     0,   502,   727,     0,     0,   719,   722,   723,   720,
     726,   721,     0,   730,   728,   729,     0,   725,   724,   716,
     717,     0,   484,   487,   489,   491,   493,   494,   499,   506,
     503,   504,   505,   507,   509,   445,   471,   472,   482,   718,
     473,   480,   474,   481,   477,   478,     0,   475,   476,     0,
     508,   479,     0,     0,   463,   462,   455,   458,     0,   543,
     544,   545,   523,   528,   541,     0,   529,   534,     0,   555,
     556,   547,   549,   552,   553,     0,   581,     0,   580,     0,
       0,   571,     0,     0,     0,     0,     0,     0,     0,     0,
     748,   749,   750,   751,   752,   753,   719,   722,   723,   720,
     740,   741,   721,   742,   739,   738,   743,   736,   737,   735,
     744,   745,   746,     0,   699,   731,   701,   732,   628,   629,
     713,   700,   694,   693,   705,   707,   709,   711,   712,   698,
     733,   734,   702,     0,     0,     0,     0,   664,   663,     0,
       0,    50,   166,   183,   193,   214,   234,   341,    51,     0,
       0,     0,     0,    58,     0,     0,   689,   689,   689,     0,
       0,   418,     0,    69,     0,     0,     0,     0,    78,     0,
       0,   689,    93,    99,   118,   117,   312,   312,   312,   125,
     102,   105,   108,   114,   111,   130,   133,   139,   142,     0,
       0,   602,   600,   601,   599,   613,   610,   611,   914,   916,
     915,   917,   933,   934,   935,   936,   920,  1013,  1020,  1010,
    1012,  1011,  1015,  1016,  1017,  1018,  1019,  1014,  1021,   999,
     826,     0,     0,   853,   854,     0,   856,     0,   855,   857,
     858,   832,   833,   859,     0,     0,   805,     0,     0,   598,
     147,   159,     0,     0,     0,     0,    43,   427,    48,     0,
      44,   669,    49,     0,   720,   721,   448,     0,   457,     0,
     557,   559,     0,     0,     0,     0,     0,     0,     0,   382,
       0,     0,   859,     0,   387,   415,   425,   426,     0,   424,
       0,   537,   539,     0,   660,     7,     7,   644,   646,   712,
     659,     7,   634,   342,   390,   391,   389,   408,   407,     0,
       0,   406,   402,   397,   398,   399,   400,   403,   401,   396,
       0,     0,     0,     0,   515,     0,   510,     0,     0,     0,
     471,   480,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   517,     0,     0,     0,     0,     0,     0,   460,
     461,   459,     0,     0,     0,   532,   551,   550,     0,   582,
       0,   573,     0,   572,   615,   616,   618,   620,   622,   625,
       7,   375,   377,   630,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   695,   797,   876,     9,    10,
       0,     0,     0,     0,     0,     0,    68,   166,   183,   193,
     214,   234,     0,     0,     0,    61,    66,    62,    67,   332,
     321,   323,   326,   329,   234,    86,   127,   128,   126,     0,
     608,   937,   938,   940,   939,   941,   919,  1024,  1023,  1022,
    1025,  1026,  1027,  1028,  1029,   998,     0,     0,   860,   861,
     862,   863,   805,   805,     0,   822,   810,   814,   815,   818,
       0,   262,   266,   258,     0,     0,     0,   450,     0,     0,
     449,   560,     0,     0,   651,   558,   647,   801,   800,     0,
     643,     0,   641,   798,   796,   873,   383,   874,     0,   872,
       0,   420,   419,   421,     0,     0,   638,     0,   639,     0,
       0,   656,   658,   645,   652,   637,   636,   405,   411,   412,
     404,   410,     0,     0,   444,     0,   516,     0,   520,   522,
     483,   485,   486,   488,   490,   492,   500,   501,   495,   498,
     497,   496,   512,   511,     0,     0,     0,   868,   869,   870,
     871,   526,   542,   533,   535,   554,     0,     0,     0,     0,
     378,   747,   697,   703,   704,   706,   708,   710,   696,   626,
     627,   714,   715,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    33,   168,   167,     0,
       0,     0,     0,    35,   185,   184,     0,     0,     0,     0,
       0,   203,     0,     0,     0,     0,     0,     0,     0,     0,
      38,   195,   194,     0,     0,     0,     0,     0,     0,    39,
     216,   215,     0,     0,     0,   239,    41,   236,   235,     0,
       0,     0,     0,     0,   262,   266,   258,     0,     0,  1059,
    1066,   809,     0,   821,   806,   817,   816,   819,     0,     0,
       0,     0,     0,   421,   451,   453,     0,   311,   649,   650,
     648,     0,     0,   642,   875,     0,   430,     0,   423,   538,
       0,     7,   661,   662,   654,   655,     0,   653,     0,   441,
     442,   443,   513,     0,   519,     0,   521,   527,   536,     0,
       0,   561,     0,     0,     0,     7,   376,   467,     0,   333,
     249,   324,   182,   327,   192,   213,   330,   233,   165,     0,
       0,     0,   249,   249,   249,   249,   169,   305,   306,   302,
     304,   303,     0,   301,   186,   188,   187,   189,     0,   190,
       0,     0,     0,   232,   231,   229,   230,   282,   284,   285,
     283,   246,   286,   247,     0,   245,   209,   210,   212,   211,
       0,   208,   201,   204,     0,     0,     0,     0,     0,   228,
       0,     0,    53,    55,    56,    57,    59,     0,     0,     0,
      81,   895,   805,     0,     0,     0,    46,   264,   263,   265,
       0,     0,     0,     0,     0,    47,   268,   267,   269,     0,
       0,    45,   260,   259,   261,   665,     0,   430,   667,   452,
       0,   574,   433,   434,   435,   436,   437,   428,     0,   414,
       0,   540,   640,     0,   409,   514,     0,     0,     0,   562,
     568,     0,   380,   379,   468,   469,     0,     0,     0,     0,
       0,     0,   249,   249,   249,     0,     0,     0,     0,     0,
       0,   197,   199,   200,   202,     0,   196,     0,   198,     0,
     217,   227,     0,   226,     0,     0,     0,     0,    64,    65,
      63,   820,     0,   675,   674,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   428,   691,     0,     0,   413,     0,
     422,     0,   518,   566,     0,     7,   470,   464,   467,   278,
     183,   193,   214,   234,     0,     0,     0,   250,   270,   254,
     274,   300,   191,   248,   207,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   296,   290,   289,   293,   288,   291,
     292,   237,   244,     0,   241,   238,     0,   681,   683,   686,
     687,   684,   685,   688,     0,   677,   690,   575,     0,   432,
     431,   657,   567,   381,   469,     0,     0,     0,     0,     0,
     262,   266,   258,     0,     0,     0,     0,     0,     0,     0,
       0,   220,     0,   222,   224,   223,   225,   218,   297,     0,
       0,     7,   240,     0,     0,   678,     0,   429,   465,     0,
     280,   279,   281,     0,     0,     0,     0,     0,     0,     0,
       0,   252,   251,   253,     0,   272,   271,   273,     0,   256,
     255,   257,     0,   276,   275,   277,   298,     0,   287,   221,
     219,   295,   294,   243,   242,     0,     0,     0,   676,   181,
     170,   171,   172,   173,     0,     0,     0,   174,   179,   175,
     180,   299,   680,   679,   682,   177,   178,   176
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1402, -1402,    -1, -1023,    59, -1402, -1402,  1514, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402,   -10, -1402,  1153, -1402,   380,  -380, -1119,
   -1266,  -373, -1118,  -377,   181,   -46,  -372, -1120, -1128, -1402,
    -386, -1131,  -204, -1402,  -166,   -39, -1257,  -689, -1402, -1402,
   -1311, -1306, -1304, -1402, -1402, -1402, -1402, -1402,  -147, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402,   136,  -670,  -923,
    1464,   -42,  2190, -1402,   612, -1402, -1402,   205, -1402,   238,
     451, -1402, -1402,   956,  1041,  -583,  1173, -1402, -1402,   120,
    1463,  -304,    46,    -8, -1402, -1402,   262,  -313, -1402, -1402,
   -1402, -1402,   124, -1402, -1402, -1402, -1402,   810, -1402, -1402,
   -1402,   809, -1402, -1402, -1402,   152, -1402,  1274, -1170,   185,
   -1402,   562,   -33,    61,    48, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402,   756,  -905,  1209,   -28,   -85,  -498,
     507,   508,   517, -1402,  -722, -1402, -1402, -1402, -1402, -1402,
    -340, -1402,  -469, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402,  -329,   501, -1402, -1402, -1402,   776, -1402,   500,
   -1078, -1402, -1402,  1335, -1402, -1402, -1402, -1402,   772, -1402,
   -1402,   -59,   -29,  -780,  -317,    57,   -25, -1402, -1402, -1402,
     664,    22, -1402, -1402, -1402, -1402, -1402,  -183,  -194, -1402,
   -1402,   485, -1402,  1427,    27, -1402,   574, -1012, -1402, -1237,
   -1402,   404, -1108, -1402,   386, -1402, -1402,  1273,  -917,  1247,
    -914,  1254,  -912,  1255,  1537, -1401, -1402, -1402,   -98, -1402,
   -1402,  -466,  -909,  1263, -1402,  1301,  -323,  -781,  -778,  -754,
   -1402,  -212,  -727, -1402,   119,  -246,  -691, -1402, -1191,  1367,
      86,  1364, -1402,   -48, -1402,   422, -1402, -1104, -1402,   503,
   -1402, -1402, -1402, -1402, -1402,   548,  -248,   628,  1046,   674,
    1366,  1370, -1402, -1402,  -541,    78, -1402, -1402, -1402,   716,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1367,   751,  1368,    45,    46,    47,    72,    85,
      87,   101,   103,   129,   134,   142,   144,   259,   262,   265,
     266,   711,  1010,   260,   210,   373,  1329,  1151,   374,  1152,
    1468,   377,  1153,   378,  1490,  1491,   381,  1154,  1353,  1475,
     383,  1155,  1597,  1663,  1664,  1483,  1484,  1567,  1693,  1695,
    1390,  1388,  1389,  1694,  1696,  1685,  1485,  1336,  1595,  1657,
    1658,  1659,  1699,  1337,  1338,  1459,  1460,  1439,   211,  1398,
      48,    49,    59,   406,    51,   409,  1442,    65,   413,  1444,
      69,   418,  1447,    60,   403,  1440,   281,   282,   283,    52,
     385,  1224,   435,  1339,   315,   316,   317,   318,   319,   320,
    1131,  1299,  1300,   321,   322,   323,   759,   760,   324,   325,
     767,   768,  1078,  1072,  1260,  1261,   326,  1019,  1243,  1408,
     327,  1048,  1618,  1549,  1547,   328,   329,   770,   330,   331,
     332,   333,   334,   826,   827,   911,   372,  1565,  1627,   792,
     793,   794,   795,   796,   797,   798,  1279,   799,   800,   801,
     802,   803,   804,   805,   335,   336,   832,   337,   338,   836,
     339,   340,   833,   834,   341,   342,   841,   842,   843,   844,
    1029,  1030,   343,   344,   345,   346,   347,   850,   851,   348,
     349,   212,   806,   847,   886,   807,   350,   216,   964,   491,
     492,   808,   497,   351,   352,   353,   354,   355,   356,   888,
     889,   890,   357,   358,   359,   752,   753,  1231,  1232,  1056,
    1057,  1225,  1226,  1253,  1254,  1058,  1411,   906,  1016,   715,
    1020,   717,  1022,   718,   422,  1605,  1534,  1714,  1715,  1519,
    1528,  1012,  1018,   716,   360,   907,   908,   894,   895,   896,
     897,  1059,   899,   809,   810,   811,   902,   903,   361,   728,
     812,   656,   657,   219,   363,   813,   495,  1205,   686,   814,
    1008,   698,  1209,  1387,   222,   815,   618,   817,   619,   818,
     681,   682,  1001,  1002,   683,   819,   820,   364,   365,   821,
     227,   485,   228,   504,   229,   509,   230,   517,   231,   531,
     976,  1186,   232,   539,   233,   544,   234,   554,   235,   563,
     236,   569,   237,   572,   238,   576,   239,   581,   240,   586,
     241,   598,   989,  1195,   242,   602,   243,   607,   244,   500,
     245,   246,   632,   247,   620,   248,   622,   249,   624,   250,
     629,   251,   639,   252,   642,   253,   648,   254,   695
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   213,    53,   756,   362,   215,   925,   379,   921,   837,
     687,   755,  1165,   923,  1156,   362,   922,  1167,   884,   924,
    1168,  1166,   263,   213,  1060,   699,  1362,   848,   884,   884,
    1373,   940,  1246,  1248,   213,   893,   723,   938,  1255,  1370,
    1372,  1371,  1296,  1377,   314,   275,  1393,  1558,  1021,   845,
    1429,  1061,   217,   367,   942,   375,  1413,   370,  1435,  1711,
      44,  1434,  1756,   749,   434,  1509,   434,   434,  1507,  1089,
     434,  1508,   434,  1126,   217,   434,   434,  1127,  1132,   434,
     434,   434,   434,   816,  1063,   217,   434,   214,  1494,   434,
     434,  1034,  1073,   380,   845,   845,  1077,   434,  1381,  1383,
    1497,     3,  1128,   849,     4,   828,     5,  1298,    55,   214,
    1297,   278,   901,  1457,  1458,  1249,   218,  1400,  1250,   493,
     214,  1609,   901,   901,  1405,  1039,     6,     7,     8,     9,
     658,  1241,   966,    63,   450,  1679,  1536,   934,   218,  1354,
    1003,   445,   446,    56,    57,    58,   898,   935,   857,   218,
    1653,   968,   267,    71,   437,   439,   898,   898,   442,    86,
     444,  1124,  1125,   448,   449,   969,   750,   456,   458,   460,
     462,  1099,   722,   936,   467,   213,    54,   470,   472,   213,
     599,   937,   630,    55,   276,   478,   277,  1355,   255,  1356,
     609,  1345,   859,    55,  1346,   371,    55,  1042,  1222,   261,
     376,  1223,   102,   748,   382,  1406,   400,   631,   264,  1067,
     730,  1357,   609,     3,   612,  1100,     4,  1537,     5,    55,
      66,    67,  1204,   939,  1207,  1382,   217,    55,  1654,  1655,
     217,   143,   600,   601,   727,   727,   612,   368,     6,     7,
       8,     9,  1068,   609,  1362,   701,   731,  1013,  1014,  1221,
     658,   703,  1363,  1026,  1364,  1028,  1069,   967,   835,  1358,
     741,   214,  1021,  1662,     4,   214,     5,   612,   362,    55,
     369,  1044,  1045,  1716,  1049,  1251,   742,  1430,  1051,  1052,
    1242,   389,   390,   391,  1680,   846,   451,   213,   421,   540,
     218,  1040,   300,   479,   218,  1400,   494,   412,   414,   415,
    1399,  1070,  1084,   452,   268,  1086,   269,   431,   302,   541,
     829,   830,   831,   303,   393,   440,   441,  -164,   419,  1035,
    1280,   447,   542,  1646,   640,  1434,  1414,  1415,  1103,   885,
    1104,   379,  -182,   754,   209,  1652,   313,   362,   217,   885,
     885,   209,   476,   477,   970,   700,   480,   496,  1130,   641,
    1071,  1557,   362,   209,  1449,   379,   213,  1305,   971,   279,
     280,  1306,  1227,  1228,   209,  1559,  1115,  1062,  1431,  1116,
    1625,   213,   379,   214,  1436,  1712,  1277,   918,  1757,  1700,
    1620,  1729,  1122,  1208,  1727,   891,  1307,  1728,  1552,  1540,
    1702,   621,   933,   313,   611,   891,   891,   961,   209,   209,
     130,     4,   218,     5,   434,   131,   132,   217,  1601,   743,
    1589,  1054,  1562,  1580,   684,   887,   754,   380,  1080,  1470,
    1471,   133,   217,  1359,   685,   887,   887,   744,   745,   726,
     726,  1081,  1495,   732,  1313,  1146,  1147,   543,   256,   257,
     258,   380,   214,   623,  1105,  1303,  1304,  1082,  1656,   256,
     257,   258,   220,   857,  1097,   209,  1098,   214,   380,  1365,
    1162,  1163,  1164,   829,   830,   831,   394,   689,   395,   858,
     420,   218,   421,   702,   220,  1175,  1102,   900,   570,  1258,
    1624,  -666,   615,   616,  1259,   220,   218,   900,   900,   603,
       3,  1603,   945,     4,   571,     5,  1604,   859,     3,   962,
     963,     4,  1689,     5,  1106,   901,  1450,  1592,  1451,   719,
    1585,  1686,  1688,  1687,   609,     6,     7,     8,     9,   884,
    1412,   604,   605,     6,     7,     8,     9,   720,  1060,  1141,
     392,  1031,   721,   221,   611,  1366,  1133,   371,   612,   724,
     276,   848,  1142,   277,  1143,  1091,   417,   376,   486,   487,
     606,   740,   382,  1709,  1217,   221,  1710,  1477,  1220,  1142,
    1362,  1143,  1083,   884,   443,   617,   221,  1233,  1234,  1235,
     747,  1060,  1237,   750,  1239,   754,   643,  1181,   223,   769,
    1145,  1478,  1479,   849,  1245,   822,   823,   824,  1513,   644,
     150,   151,   152,  1182,  1271,  1272,   645,  1607,  1183,  1184,
     223,  1278,  1683,   482,   483,   484,   901,   901,   901,   901,
     901,   223,   855,   901,   646,   854,  1266,   958,  1268,  1269,
     647,   856,   615,   616,    62,   904,   220,  1514,     3,   905,
     220,     4,  1282,     5,  1283,     3,   910,   901,     4,   912,
       5,     3,   913,  1291,     4,  1293,     5,   914,   488,   489,
     944,   278,   490,     6,     7,     8,     9,   901,   224,   915,
       6,     7,     8,     9,  1185,  1480,     6,     7,     8,     9,
     916,  1134,     3,  1354,  1129,     4,     4,     5,     5,  1587,
     224,   498,   499,   384,   957,  1481,  1482,   388,  1753,   761,
       3,   224,  -233,     4,   438,     5,   213,     6,     7,     8,
       9,  1011,   408,   384,   225,   617,   946,   221,   947,    18,
      19,   221,   848,   696,   697,     6,     7,     8,     9,   436,
     948,  1355,   885,  1356,   959,  1345,   225,  1520,  1346,  1363,
    1515,  1364,   825,   573,  1521,   757,   758,   225,   220,  1452,
    1453,  1454,  1455,   574,   575,  1357,   226,   217,   475,  1394,
    1395,   960,   223,  1252,   625,   481,   223,     4,    34,     5,
    1210,  1580,  1090,  1575,  1576,  1577,  1578,    35,   366,  1404,
    1522,  -418,   991,    36,   965,  1409,  1733,   992,  1055,   366,
    1722,  1741,   214,   848,  1745,  1737,  1294,  1006,   762,   763,
     764,   765,   766,  1358,   626,   627,   628,    37,  1422,   846,
     287,   288,   577,  1004,  1523,   289,   578,   220,   887,   852,
     853,   218,  1742,  1005,   555,  1424,   556,  1426,  1009,   221,
    1516,  1015,   220,   885,   885,   885,   885,   885,   213,     4,
     885,     5,   224,  1585,   557,  1060,   224,  1007,   579,   580,
    1017,  1230,   558,   559,  1032,   560,  1091,  1091,  1091,  1091,
    1091,  1027,  1091,  1091,   885,   561,   562,   744,   745,   274,
     633,  1288,  1288,     4,   223,     5,  1572,  1573,  1574,  1036,
     900,  1046,  1047,  1524,   885,   634,  1015,  1033,   225,   217,
    1092,  1093,   225,  1634,  1635,  1636,   891,  1050,   221,   901,
     901,   901,   901,   901,   901,   901,   635,   901,   901,   501,
     502,   503,   636,   221,  1053,  1148,  1136,  1137,  1149,   887,
     887,   887,   887,   887,   214,  1054,   887,  1037,  1402,  1038,
     226,  1198,  1199,  1302,   226,  1041,  1031,  1539,  1230,  1308,
     891,  1310,  1312,   223,   582,  1043,  1365,   744,   745,  1064,
     887,  1551,  1065,   218,   224,   256,   257,   258,   223,  1252,
    1730,   637,   638,  1074,  1555,  1200,  1201,  1505,  1054,  1087,
     887,   564,  1427,  1525,  1428,  1088,   583,   584,  1075,   585,
     846,   900,   900,   900,   900,   900,  1094,   565,   900,   750,
    1247,  1119,   839,   840,  1433,  1121,   566,   532,  1076,   533,
     225,  1095,   567,   568,  1738,   270,   271,   272,   273,  1385,
    1386,   901,   900,   838,   839,   840,   213,   534,  1096,   901,
    1473,  1474,  1506,   224,  1101,   535,   536,   537,   538,  -868,
       3,   690,   900,     4,  -869,     5,  1021,  1746,   224,   386,
     691,   692,   366,  1107,   693,   694,  1108,   396,   397,   398,
     399,   846,  1187,  1109,   402,     6,     7,     8,     9,   829,
     830,   831,   901,   423,   425,   427,   429,   217,  1110,   225,
     432,  1571,  1568,  1090,  1090,  1090,  1090,  1090,  1112,  1090,
    1090,  1569,  1113,  1570,   225,  1188,   454,  1118,  1287,  1287,
    1120,   463,   464,   465,  1697,  1698,   468,  1622,  1135,   473,
    1138,   213,   214,   213,  1139,  1584,    18,    19,   150,   151,
     152,   366,   455,  1140,   362,  1144,   885,   885,   885,   885,
     885,   885,   885,  1150,   885,   885,   366,    18,    19,  1591,
    1157,   218,   505,   213,   506,   507,   508,  1281,   972,   973,
     974,   975,  1189,  1190,  1191,  1192,  1193,  1194,   424,   426,
     428,   430,   217,     3,   217,    34,     4,   220,     5,  1314,
    1327,  1334,  1351,  1360,    35,  1542,  1543,  1544,  1545,  1546,
      36,  1169,     3,  1158,  1170,     4,    34,     5,     6,     7,
       8,     9,  1159,  1160,   217,    35,  1218,   214,  1161,   214,
    1171,    36,  1172,   362,    37,  1289,  1290,     6,     7,     8,
       9,  1173,   887,   887,   887,   887,   887,   887,   887,  1179,
     887,   887,   213,  1174,  1196,    37,   218,  1230,   218,   214,
    1328,  1335,  1352,  1361,     3,  1197,  1202,     4,   885,     5,
    1203,  1204,  1054,   712,   713,   714,   885,  1616,   221,  1520,
    1486,  1487,  1488,  1206,  1489,  1031,  1521,  1211,   218,     6,
       7,     8,     9,   290,   291,   292,   293,   294,   295,   362,
    1212,  1213,  1513,   217,   900,   900,   900,   900,   900,   900,
     900,   857,   900,   900,  1214,  1216,   510,   511,   213,   885,
    1229,  1461,  1522,   223,   512,   513,   514,   515,   516,   220,
    1236,  1238,  1055,  1017,    88,  1240,  1244,  1262,   214,  1257,
    1263,  1514,    89,  1264,    90,  1265,    91,  1267,  1276,    92,
      93,    94,  1270,    95,   887,     3,  1523,  1285,     4,  1284,
       5,   213,   887,  1301,  1286,  1469,   901,   218,  1309,   217,
    1374,  1375,   362,  1376,  1529,   213,  1378,  1391,  1456,  1469,
       6,     7,     8,     9,  1379,  1464,  1465,  1466,  1467,  1380,
    1384,   213,  1734,  1354,  1392,  1396,  1401,  1397,  1492,   926,
     927,   928,  1493,   224,   214,   887,  1407,  1410,  1416,  1418,
     221,  1499,   217,  1419,  1031,  1420,   900,  1421,  1327,  1334,
    1351,  1360,   213,  1423,   900,  1524,   217,  1425,   941,  1437,
    1438,  1448,  1462,   218,  1463,  1476,  1511,  1517,  1526,  1532,
    1472,  1355,   217,  1356,  1515,  1345,  1496,   214,  1346,   225,
     213,  1500,  1512,  1535,  1501,   223,  1548,  1541,  1550,   949,
    1553,   214,   135,   379,   136,  1357,  1556,   900,   736,   137,
    1561,   138,  1564,   217,  1560,   139,   218,   214,  1328,  1335,
    1352,  1361,  1566,  1579,  1594,  1596,  1608,   379,  1602,  1610,
     218,   226,  1617,  1612,  1619,  1621,  1530,  1518,  1527,  1533,
    1623,   217,  1441,  1443,  1443,  1446,   218,   220,   214,  1626,
    1629,  1630,  1631,  1358,   140,  1599,   141,  1581,  1632,  1582,
    1583,  1633,  1637,  1606,  1638,     3,  1639,  1640,     4,  1641,
       5,    96,  1611,  1586,  1598,   224,   214,   218,  1613,  1588,
    1662,  1666,   362,  1674,  1590,  1677,    97,  1593,  1678,   380,
       6,     7,     8,     9,  1681,  1682,  1517,  1526,  1532,  1690,
    1691,   213,    98,  1692,  1363,   218,  1364,    99,  1708,   100,
    1713,  1717,     3,   380,  1747,     4,  1751,     5,  1752,   213,
    1755,   225,  1772,   885,    70,  1660,  1531,  1369,   221,  1498,
     920,  1644,   220,  1771,   220,  1754,  1643,     6,     7,     8,
       9,   213,  1748,   404,   410,  1642,  1445,   917,  1432,  1563,
     213,  1363,   217,  1364,  1469,  1628,  1518,  1527,  1533,  1066,
    1554,   518,   519,   226,   220,   520,  1079,   746,  1538,  1215,
     217,  1676,  1111,   223,  1614,   521,   522,   523,   524,   525,
     526,   527,   528,   529,  1661,   919,  1665,   214,  1615,  1718,
    1684,  1273,   217,  1274,  1667,  1668,  1669,  1670,  1671,  1672,
    1673,   217,  1675,  1275,  1292,   214,   213,  1117,  1295,   887,
    1469,   725,  1123,   221,  1180,   221,   218,  1725,   704,  1311,
     705,   688,   706,   707,   530,  1256,  1403,   214,   362,  1417,
     708,   709,   909,   929,   218,  1701,   214,  1703,  1704,  1705,
    1706,  1707,   931,   220,   932,   221,   453,   213,  1773,   892,
     930,   729,   734,   224,   990,   738,   218,   217,   223,   739,
     223,     0,     0,   710,     0,   218,     0,     0,     0,     0,
       0,   900,     0,     0,  1720,  1334,  1351,  1360,     0,     0,
       0,     0,  1731,  1735,  1739,  1743,   457,     0,     0,  1749,
     223,  1750,   214,     0,     0,     0,     0,     0,   217,   225,
       0,    18,    19,     0,     0,  1758,     0,     0,  1759,   220,
       0,  1365,  1760,  1761,  1762,  1763,  1517,  1526,  1532,  1767,
       0,   218,     0,  1768,   221,     0,     0,  1769,     0,     0,
       0,  1770,     0,   214,  1721,  1335,  1352,  1361,   224,     0,
     224,   226,  1732,  1736,  1740,  1744,  1774,     0,     0,     0,
      34,     0,   220,  1775,  1776,  1777,     0,     0,  1365,    35,
       0,     0,   218,     0,     0,    36,   220,     0,     3,   223,
     224,     4,     0,     5,     0,     0,  1518,  1527,  1533,     0,
       3,     0,   220,     4,   225,     5,   225,  1510,     0,    37,
     221,     0,     0,     6,     7,     8,     9,     0,     0,     0,
       0,     0,  1315,     0,     0,     6,     7,     8,     9,     0,
       0,     0,  1316,   220,     0,     0,   225,  1317,  1340,  1318,
       0,  1319,     0,     0,     0,     0,   226,     3,   226,     0,
       4,     0,     5,   221,  1726,   223,     0,     0,     0,     0,
       0,   220,     0,     0,     0,     0,     0,   221,     0,   224,
       0,     0,     6,     7,     8,     9,     3,     0,   366,     4,
       0,     5,     0,   221,     0,  1341,  1342,  1343,  1344,     0,
    1345,     0,     0,  1346,     0,     0,     0,     0,   223,     0,
       0,     6,     7,     8,     9,     0,     0,     0,    73,     0,
    1347,     0,   223,     0,   221,   225,    74,     0,    75,     0,
       0,     0,   459,    76,    77,    78,     3,    79,   223,     4,
       0,     5,     0,  1520,     0,   224,     3,    18,    19,     4,
    1521,     5,   221,     0,     0,     0,  1320,     0,     0,     0,
       0,     6,     7,     8,     9,     0,     0,   366,  1348,   223,
    1315,     6,     7,     8,     9,     0,  1513,     0,     0,     0,
    1316,   910,   220,     0,     0,  1317,  1522,  1318,   224,  1319,
       0,   225,     0,   461,     0,     0,    34,   223,     0,     0,
     220,     0,   224,     0,     0,    35,     0,     0,    18,    19,
       0,    36,     0,     0,     3,  1514,     0,     4,   224,     5,
    1523,     0,   220,     0,     0,     0,     0,     0,     0,  1321,
       0,   220,     0,   366,   225,    37,     0,     0,     0,     6,
       7,     8,     9,     0,  1322,     0,     0,     0,   225,   224,
       0,     0,  1340,     0,     0,     0,  1349,    34,     0,     0,
    1323,     0,     0,   221,   225,  1324,    35,  1325,     0,  1647,
       0,     0,    36,     0,     0,     0,   226,   224,     0,     0,
       0,   221,     0,     0,     0,     0,  1477,   220,     0,  1524,
     226,     0,     0,     0,  1320,   225,    37,     0,   466,  1341,
    1342,  1343,  1344,   221,  1345,     0,   366,  1346,   223,     0,
    1478,  1479,   221,    18,    19,    80,     0,     0,  1515,     0,
    1326,     0,     0,   225,  1347,     0,   223,     0,   220,     0,
      81,     0,  1350,     3,     0,     0,     4,   226,     5,     0,
       0,     0,     0,     0,     0,     0,    82,     0,   223,     0,
       0,    83,     0,    84,     0,     0,     0,   223,     6,     7,
       8,     9,    34,     0,     0,   226,     0,  1321,   221,     0,
       0,    35,  1348,     0,     0,     0,     0,    36,     0,  1765,
       0,     0,  1322,     0,     0,     0,     0,     0,   224,     0,
       0,     0,     0,     0,  1480,     0,     0,     0,  1323,     0,
       0,    37,     0,  1324,     0,  1325,   224,     0,  1764,   221,
       0,    50,     0,   223,  1481,  1482,     0,     0,     0,     0,
       0,    61,    50,    50,    64,    64,    64,    68,   224,     0,
      50,     0,  1648,     0,   225,     0,     0,   224,     0,     0,
       0,     0,     0,  1529,     0,     0,     0,     0,  1649,     0,
       0,     0,   225,  1650,   223,  1651,     0,     0,  1502,     0,
    1349,     0,     0,     0,   469,     0,     0,     0,  1719,     0,
       0,     0,     0,     0,   225,     0,   366,     0,     0,    18,
      19,    50,     0,   225,   387,    50,    64,    64,    64,    68,
       0,     0,     0,   224,   226,     0,    50,     0,   401,   405,
     407,    50,   411,    64,    64,   416,     0,   401,   401,   401,
     401,     0,    64,     0,     0,   433,   226,    50,     0,     0,
      64,    64,     0,    68,     0,   226,    64,     0,    34,     0,
       3,     0,     0,     4,   224,     5,  1504,    35,     0,   225,
       0,     0,     0,    36,     0,   474,    50,    64,    64,     0,
       0,    64,   145,    50,   471,     6,     7,     8,     9,   146,
     147,     0,   284,   148,   285,  1530,     0,    37,     0,    18,
      19,     3,     0,     0,     4,     0,     5,     0,     0,   286,
     225,   226,     0,     0,     0,     0,     0,     0,     0,   287,
     288,     0,     0,     0,   289,     0,     6,     7,     8,     9,
       0,     0,     0,     0,     0,   290,   291,   292,   293,   294,
     295,     0,     0,     0,     0,     0,     0,     0,    34,     0,
    1330,     0,   366,     0,   296,     0,   297,    35,     0,   149,
     150,   151,   152,    36,     0,   153,     0,   154,     0,     0,
    1331,   155,     0,     0,     0,   156,     0,     0,     0,     0,
       0,   157,     0,   993,   994,  1600,     0,    37,     0,     0,
       0,     0,     0,     0,     0,     0,   995,   158,     0,     0,
       0,     0,   159,     0,   996,   160,     0,     0,     0,     3,
     161,  1529,     4,   162,     5,     0,   163,   164,  1332,     0,
     997,   165,     0,     0,   166,     0,   167,     0,     0,     0,
       0,     0,     0,     0,     6,     7,     8,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1340,     0,   168,
     169,     0,   170,   171,   172,   173,     0,     0,     0,     0,
       0,   174,   175,     0,     0,   176,   177,   298,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,   299,     0,     0,  1341,  1342,  1343,  1344,     0,  1345,
       0,     0,  1346,     0,     0,     0,   300,   998,   999,  1000,
     667,     0,     0,     0,     0,     0,   301,     0,     0,  1347,
       0,     0,   302,   677,   678,   679,     0,   303,     0,     0,
       0,     0,     0,  1530,   545,   546,   201,   202,     0,   304,
       0,     0,   305,   306,   307,   308,     0,     0,   547,   309,
     548,   549,   550,   310,   311,   203,     0,     0,     0,   204,
     205,     0,     0,     0,     0,     0,     0,  1348,   312,     0,
       0,   206,   207,   551,   552,   553,     0,     0,   943,     0,
       0,   313,  1333,   208,     0,    64,   209,     0,     3,     0,
       0,     4,     0,     5,     0,   950,     0,   951,     0,   952,
       0,   953,     0,   587,     0,     0,   954,     0,     0,   955,
     145,   956,   588,     6,     7,     8,     9,   146,   147,    64,
     284,   148,   285,  1766,     0,     0,     0,   589,     0,     0,
       0,   590,     0,     0,     0,   591,   592,   286,     0,     0,
     593,   594,   595,   596,   597,     0,     0,   287,   288,     0,
       0,     0,   289,     0,     0,  1349,     0,     0,     0,     0,
       0,     0,     0,   290,   291,   292,   293,   294,   295,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1330,     0,
       0,     0,   296,     0,   297,     0,     0,   149,   150,   151,
     152,     0,     0,   153,     0,   154,     0,     0,  1331,   155,
       0,     0,     0,   156,     0,   608,     0,     0,     0,   157,
       0,     0,     0,     0,     0,     0,   609,     0,   610,     0,
       0,     0,     0,     0,     0,   158,     0,     0,     0,     0,
     159,  1724,     0,   160,     0,     0,   611,     0,   161,     0,
     612,   162,     0,   613,   163,   164,  1332,     0,    10,   165,
       0,     0,   166,     0,   167,     0,    11,     0,    12,     0,
      13,     0,     0,    14,    15,    16,     0,    17,     0,     0,
       0,    18,    19,     0,     0,     0,     0,   168,   169,     0,
     170,   171,   172,   173,     0,     0,     0,     0,     0,   174,
     175,   614,     0,   176,   177,   298,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,     0,     0,   299,
      34,     0,     0,     0,   615,   616,     0,     0,     0,    35,
       0,     0,     0,     0,   300,    36,     0,     0,     0,     0,
       0,     0,     0,     0,   301,     0,     0,     0,     0,     0,
     302,     0,     0,     0,     0,   303,     0,     0,     0,    37,
       0,     0,     0,     0,   201,   202,     0,   304,     0,     0,
     305,   306,   307,   308,     0,     0,     0,   309,     0,     0,
       0,   310,   311,   203,     0,     0,     0,   204,   205,     0,
       3,     0,     0,     4,     0,     5,   312,     0,     0,   206,
     207,     0,     0,     0,     0,     0,     0,   617,     0,   313,
    1503,   208,   145,     0,   209,     6,     7,     8,     9,   146,
     147,     0,   284,   148,   285,   977,     0,     0,   978,   979,
     980,   981,   982,   983,   984,   985,   986,   987,   988,   286,
       0,     0,     0,     0,     0,    38,     0,     0,     0,   287,
     288,     0,     0,     0,   289,     0,     0,     0,     0,     0,
      39,     0,     0,     0,     0,   290,   291,   292,   293,   294,
     295,     0,     0,     0,     0,     0,    40,     0,     0,     0,
    1330,    41,     0,    42,   296,     0,   297,     0,     0,   149,
     150,   151,   152,     0,     0,   153,     0,   154,     0,     0,
    1331,   155,     0,     0,     0,   156,     0,     0,     0,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,     0,     0,   160,     0,     0,     0,     0,
     161,     0,     0,   162,     0,     0,   163,   164,  1332,     0,
       0,   165,     0,     0,   166,     0,   167,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   168,
     169,     0,   170,   171,   172,   173,  1176,  1177,  1178,     0,
       0,   174,   175,     0,     0,   176,   177,   298,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,   299,     0,     0,     0,     0,     0,     0,     0,   771,
       0,     0,     0,     0,     0,     0,   300,  -824,     0,  -824,
       0,     0,     0,     0,     0,   772,   301,   145,     0,     0,
       0,     0,   302,     0,     0,   147,     0,   303,   148,     0,
       0,     0,     0,     0,   545,   546,   201,   202,     0,   304,
       0,     0,   305,   306,   307,   308,     0,     0,   547,   309,
     548,   549,   550,   310,   311,   203,     0,     0,     0,   204,
     205,     0,   773,     0,     0,     0,     0,     0,   312,     0,
       0,   206,   207,   551,   552,   553,   774,     0,   775,     0,
       0,   313,  1723,   208,     0,     0,   209,     0,     0,     0,
       0,     0,     0,     0,   149,   150,   151,   152,     0,     0,
     153,     0,   776,     0,     0,     0,   777,     0,     0,     0,
     778,     0,     0,     0,     0,     0,   779,     0,     0,     0,
     780,     0,     0,  -824,     0,     0,     0,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,   159,     0,     0,
     781,     0,     0,     0,     0,   161,     0,     0,   162,     0,
       0,   163,   164,     0,     0,     0,   165,     0,     0,   166,
       0,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -824,   168,   169,     0,   782,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,     0,     0,   200,     0,  1023,     0,
       0,     0,     0,     0,     0,     0,   783,     0,     0,   784,
     785,     0,     0,     0,   772,     0,   145,     0,     0,     0,
       0,     0,   786,     0,   147,     0,     0,   148,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,   202,     0,     0,     0,     0,   787,   788,     0,
       0,     0,     0,     0,   649,     0,     0,     0,     0,     0,
     203,   773,     0,     0,   204,   205,     0,     0,     0,     0,
       0,     0,     0,     0,   789,   790,     0,   655,     0,     0,
     650,     0,     0,   651,     0,     0,     0,     0,   791,     0,
       0,   209,     0,   149,   150,   151,   152,     0,     0,   153,
     652,   776,     0,     0,     0,   777,     0,     0,     0,   778,
       0,     0,     0,     0,     0,  1024,     0,     0,     0,   780,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,     0,     0,     0,   159,     0,     0,  1025,
       0,     0,     0,     0,   161,     0,     0,   162,     0,     0,
     163,   164,     0,     0,     0,   165,     0,     0,   166,     0,
     167,     0,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   168,   169,     0,   782,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   653,     0,   200,     0,  1085,     0,     0,
     201,   202,     0,     0,     0,   783,     0,     0,   784,   785,
     654,     0,     0,   772,     0,   145,     0,     0,     0,     0,
       0,     0,     0,   147,     0,     0,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   655,     0,     0,     0,
     201,   202,     0,     0,     0,     0,   787,   788,     0,     0,
       0,     0,     0,   733,     0,     0,     0,     0,     0,   203,
     773,     0,     0,   204,   205,     0,     0,     0,     0,     0,
       0,     0,     0,   789,   790,     0,   655,     0,     0,   650,
       0,     0,   651,     0,     0,     0,     0,   791,     0,     0,
     209,     0,   149,   150,   151,   152,     0,     0,   153,   652,
     776,     0,     0,     0,   777,     0,     0,     0,   778,     0,
       0,     0,     0,     0,  1024,     0,     0,     0,   780,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,   159,     0,     0,  1025,     0,
       0,     0,     0,   161,     0,     0,   162,     0,     0,   163,
     164,     0,     0,     0,   165,     0,     0,   166,     0,   167,
       0,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   168,   169,     0,   782,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   653,     0,   200,     0,  1114,     0,     0,   201,
     202,     0,     0,     0,   783,     0,     0,   784,   785,   654,
       0,     0,   772,     0,   145,     0,     0,     0,     0,     0,
       0,     0,   147,     0,     0,   148,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   655,     0,     0,     0,   201,
     202,     0,     0,     0,     0,   787,   788,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,   773,
       0,     0,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,   789,   790,     0,   655,     0,  -823,     0,  -823,
       0,     0,     0,     0,     0,     0,   791,     0,     0,   209,
       0,   149,   150,   151,   152,     0,     0,   153,     0,   776,
       0,     0,     0,   777,   518,   519,     0,   778,   520,     0,
       0,     0,     0,  1024,     0,     0,     0,   780,   521,   522,
     523,   524,   525,   526,   527,   528,   529,     0,     0,   158,
       0,     0,     0,     0,   159,     0,     0,  1025,     0,     0,
       0,     0,   161,     0,     0,   162,     0,     0,   163,   164,
       0,     0,     0,   165,     0,     0,   166,     0,   167,     0,
       0,     0,     0,     0,     0,     0,     0,   530,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   168,   169,     0,   782,     0,     0,     0,     0,     0,
       0,     0,     0,  -823,     0,     0,     0,     0,     0,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,     0,     0,   200,     0,  1219,     0,     0,     0,     0,
       0,     0,     0,   783,     0,     0,   784,   785,     0,     0,
       0,   772,     0,   145,     0,     0,     0,     0,     0,     0,
       0,   147,     0,  -823,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   201,   202,
       0,     0,     0,     0,   787,   788,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   203,   773,     0,
       0,   204,   205,     0,     0,     0,     0,     0,     0,     0,
       0,   789,   790,     0,   655,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   791,     0,     0,   209,     0,
     149,   150,   151,   152,     0,     0,   153,     0,   776,     0,
       0,     0,   777,     0,     0,     0,   778,     0,     0,     0,
       0,     0,  1024,     0,     0,     0,   780,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,   159,     0,     0,  1025,     0,     0,     0,
       0,   161,     0,     0,   162,     0,     0,   163,   164,     0,
       0,     0,   165,     0,     0,   166,     0,   167,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     168,   169,     0,   782,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
       0,     0,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   783,     0,     0,   784,   785,   860,   861,   862,
     863,   864,   865,     0,     0,     0,     0,     0,     0,   772,
       0,   845,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   773,     0,     0,   201,   202,     0,
       0,     0,     0,   787,   788,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   203,     0,     0,     0,
     204,   205,     0,     0,     0,     0,   773,   150,   151,   152,
     789,   790,     0,   655,   866,     0,     0,     0,   867,     0,
       0,     0,   868,     0,   791,     0,     0,   209,   869,     0,
       0,     0,   780,     0,     0,     0,     0,     0,   149,   150,
     151,   152,     0,     0,     0,     0,   866,     0,     0,     0,
     867,     0,   872,     0,   868,     0,     0,     0,     0,     0,
     869,     0,     0,     0,   780,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   870,     0,     0,     0,
       0,   871,     0,     0,   872,     0,     0,     0,     0,   873,
       0,     0,   874,     0,     0,   875,   876,     0,     0,     0,
     877,     0,     0,   878,     0,   879,   772,     0,   145,     0,
       0,     0,     0,     0,     0,     0,   147,     0,     0,   148,
       0,     0,     0,     0,     0,     0,     0,     0,   880,   881,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   783,     0,
       0,   784,   785,   773,   104,     0,     0,     0,     0,     0,
       0,     0,   105,   106,   107,   108,     0,     0,   109,   110,
       0,   111,   112,   113,     0,   114,     0,     0,     0,     0,
     783,     0,     0,   784,   785,   149,   150,   151,   152,   787,
     788,   153,     0,   776,     0,     0,     0,   777,     0,     0,
       0,   778,     0,     0,     0,     0,     0,  1024,     0,     0,
       0,   780,     0,     0,   115,     0,   116,   117,   118,     0,
       0,   787,   788,   158,   882,     0,     0,     0,   159,     0,
       0,  1025,     0,   209,     0,     0,   161,     0,     0,   162,
       0,     0,   163,   164,     0,     0,     0,   165,   789,   790,
     166,     0,   167,     0,     0,     0,     0,     0,     0,     0,
     313,     0,   883,     0,     0,   209,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   168,   169,     0,   782,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,     0,     0,   200,     0,     0,
     772,     0,   845,     0,     0,     0,     0,   783,     0,     0,
     784,   785,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   201,   202,     0,     0,   120,   773,   787,   788,
       0,   121,   122,   123,   124,     0,     0,     0,     0,     0,
       0,   203,   125,     0,     0,   204,   205,   126,     0,   127,
     128,   772,     0,     0,     0,   789,   790,     0,   655,   149,
     150,   151,   152,     0,     0,     0,     0,   866,     0,   791,
       0,   867,   209,     0,     0,   868,     0,   735,     0,     0,
       0,   869,     0,     0,     0,   780,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   870,   773,   659,
     660,     0,   871,   661,     0,   872,     0,     0,     0,     0,
     873,     0,     0,   874,     0,     0,   875,   876,     0,     0,
     662,   877,     0,     0,   878,     0,   879,     0,     0,     0,
     149,   150,   151,   152,     0,     0,     0,     0,   866,     0,
       0,     0,   867,     0,     0,     0,   868,     0,     0,   880,
     881,     0,   869,     0,     0,     0,   780,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   870,     0,
       0,     0,     0,   871,     0,   736,   872,     0,     0,     0,
       0,   873,     0,     0,   874,     0,     0,   875,   876,     0,
       0,     0,   877,     0,     0,   878,     0,   879,     0,   663,
       0,   783,     0,     0,   784,   785,     0,     0,     0,     0,
       0,     0,     0,     0,   772,     0,     0,     0,     0,     0,
     880,   881,     0,   664,   665,   666,   667,   668,   669,   737,
     670,   671,   672,   673,   674,   675,   676,     0,     0,   677,
     678,   679,   787,   788,     0,   882,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     680,   773,     0,     0,     0,     0,     0,     0,     0,   789,
     790,     0,   783,     0,     0,   784,   785,     0,     0,     0,
       0,   313,     0,   883,     0,     0,   209,     0,     0,     0,
       0,     0,     0,   149,   150,   151,   152,     0,     0,     0,
       0,   866,     0,     0,     0,   867,     0,     0,     0,   868,
       0,     0,     0,   787,   788,   869,   882,     0,     0,   780,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   870,     0,     0,     0,     0,   871,     0,     0,   872,
     789,   790,     0,     0,   873,     0,     0,   874,     0,     0,
     875,   876,   313,     0,   883,   877,     0,   209,   878,     0,
     879,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   880,   881,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,     0,     0,     0,     0,
       0,     0,   146,   147,     0,   284,   148,   285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   286,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   287,   288,     0,   783,     0,   289,   784,   785,
       0,     0,     0,     0,     0,     0,     0,     0,   290,   291,
     292,   293,   294,   295,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   296,     0,   297,
       0,     0,   149,   150,   151,   152,   787,   788,   153,   882,
     154,     0,     0,     0,   155,     0,     0,     0,   156,     0,
       0,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,   789,   790,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,   159,     0,   883,   160,     0,
     209,     0,     0,   161,     0,     0,   162,     0,     0,   163,
     164,     0,     0,     0,   165,     0,     0,   166,     0,   167,
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
       0,     0,     0,     0,   313,     0,   208,     0,     0,   209,
     149,   150,   151,   152,     0,     0,   153,     0,   154,     0,
       0,     0,   155,     0,     0,     0,   156,     0,     0,     0,
       0,     0,   157,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,   159,     0,     0,   160,     0,     0,     0,
       0,   161,     0,     0,   162,     0,     0,   163,   164,     0,
       0,     0,   165,     0,     0,   166,     0,   167,     0,     0,
       0,     0,     0,     0,     0,   145,     0,     0,     0,     0,
       0,     0,   146,   147,     0,     0,   148,     0,     0,     0,
     168,   169,     0,   170,   171,   172,   173,     0,     0,     0,
       0,     0,   174,   175,     0,     0,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
       0,     0,   200,     0,     0,     0,  1645,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   149,   150,   151,   152,     0,     0,   153,     0,
     154,     0,     0,     0,   155,     0,     0,     0,   156,     0,
       0,     0,     0,     0,   157,     0,     0,   201,   202,     0,
       0,     0,     0,   659,   660,     0,     0,   661,     0,     0,
     158,     0,     0,     0,     0,   159,   203,     0,   160,     0,
     204,   205,     0,   161,   662,     0,   162,     0,     0,   163,
     164,     0,   206,   207,   165,     0,     0,   166,     0,   167,
       0,     0,   313,     0,   208,     0,     0,   209,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,   169,     0,   170,   171,   172,   173,     0,
       0,     0,     0,     0,   174,   175,     0,     0,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,     0,   663,   200,     0,     0,     0,     0,   145,
       0,     0,     0,     0,     0,     0,   146,   147,     0,     0,
     148,     0,     0,     0,     0,     0,     0,   664,   665,   666,
     667,   668,   669,     0,   670,   671,   672,   673,   674,   675,
     676,     0,     0,   677,   678,   679,     0,     0,     0,   201,
     202,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   680,     0,     0,     0,   203,     0,
       0,     0,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   206,   207,   149,   150,   151,   152,
       0,     0,   153,     0,   154,     0,   208,     0,   155,   209,
       0,     0,   156,     0,     0,     0,     0,     0,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   158,     0,     0,     0,     0,   159,
       0,     0,   160,     0,     0,     0,     0,   161,     0,     0,
     162,     0,     0,   163,   164,     0,     0,     0,   165,     0,
       0,   166,     0,   167,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   168,   169,     0,   170,
     171,   172,   173,     0,     0,     0,     0,     0,   174,   175,
       0,     0,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,     0,     0,   200,     0,
       0,     0,     0,   145,     0,     0,     0,     0,     0,     0,
       0,   147,     0,     0,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,   202,     0,     0,     0,   773,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   203,     0,     0,     0,   204,   205,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   206,   207,
     149,   150,   151,   152,     0,     0,   153,     0,   776,     0,
     208,     0,   777,   209,     0,     0,   778,     0,     0,     0,
       0,     0,  1024,     0,     0,     0,   780,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,   159,     0,     0,  1025,     0,     0,     0,
       0,   161,     0,     0,   162,     0,     0,   163,   164,     0,
       0,     0,   165,     0,     0,   166,     0,   167,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     168,   169,     0,   782,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
       0,     0,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   783,     0,     0,   784,   785,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   201,   202,     0,
       0,     0,     0,   787,   788,     0,     0,     0,     2,     3,
       0,     0,     4,     0,     5,     0,   203,     0,     0,     0,
     204,   205,     0,     0,     0,     0,     0,     0,     0,     0,
     789,   790,     0,   655,     6,     7,     8,     9,     0,     0,
       0,     0,     0,    10,   791,     0,     0,   209,     0,     0,
       0,    11,     0,    12,     0,    13,     0,     0,    14,    15,
      16,     0,    17,     0,     0,     0,    18,    19,    20,     0,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,   773,     0,     0,     0,     0,
       0,     0,     0,   290,   291,   292,   293,   294,   295,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -312,
       0,     0,     0,     0,     0,    34,     0,   149,   150,   151,
     152,     0,     0,     0,    35,   866,     0,     0,     0,   867,
      36,     0,     0,   868,     0,     0,     0,     0,     0,   869,
       0,     0,     0,   780,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,   870,     0,     0,     0,     0,
     871,     0,     0,   872,     0,     0,     0,     0,   873,     0,
       0,   874,     0,     0,   875,   876,     0,     0,     0,   877,
       0,     0,   878,   773,   879,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   880,   881,     0,
       0,     0,     0,     0,     0,   149,   150,   151,   152,     0,
       0,     0,     0,   866,     0,     0,     0,   867,     0,     0,
       0,   868,     0,     0,     0,     0,     0,   869,     0,     0,
      38,   780,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   870,     0,    39,     0,     0,   871,   783,
       0,   872,   784,   785,     0,     0,   873,     0,     0,   874,
       0,    40,   875,   876,     0,     0,    41,   877,    42,     0,
     878,     0,   879,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     787,   788,     0,   882,     0,   880,   881,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   789,   790,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   883,     0,     0,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   783,     0,     0,
     784,   785,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   787,   788,
       0,   882,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   789,   790,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   883,
       0,     0,   209
};

static const yytype_int16 yycheck[] =
{
       1,    30,     3,   316,    52,    30,   392,    66,   388,   338,
     204,   315,   929,   390,   919,    63,   389,   931,   358,   391,
     932,   930,    32,    52,   751,   208,  1154,   344,   368,   369,
    1161,   417,  1055,  1056,    63,   358,   284,   414,  1061,  1158,
    1160,  1159,  1120,  1174,    52,    46,  1216,     5,   718,    23,
       5,     7,    30,    54,   431,    63,  1247,    58,     7,     7,
       1,  1298,     7,   311,   106,  1376,   108,   109,  1374,   791,
     112,  1375,   114,   854,    52,   117,   118,   855,   858,   121,
     122,   123,   124,   331,   754,    63,   128,    30,  1354,   131,
     132,    94,   762,    66,    23,    23,   766,   139,  1202,  1203,
    1357,     1,   856,    43,     4,    82,     6,  1130,   101,    52,
    1122,    55,   358,    76,    77,    87,    30,  1225,    90,    32,
      63,  1522,   368,   369,    20,   100,    26,    27,    28,    29,
     178,   101,   123,    13,    87,   101,    20,    55,    52,    39,
     681,    43,    44,     7,     8,     9,   358,    55,     8,    63,
      22,   108,    87,    47,   108,   109,   368,   369,   112,    47,
     114,   852,   853,   117,   118,   122,     4,   121,   122,   123,
     124,     8,    82,    55,   128,   204,   102,   131,   132,   208,
     111,    55,   124,   101,    48,   139,    50,    87,    56,    89,
     122,    91,    52,   101,    94,    59,   101,   738,    87,    56,
      64,    90,    51,    82,    68,   101,    86,   149,   101,    75,
      60,   111,   122,     1,   146,    52,     4,   101,     6,   101,
      15,    16,   299,    55,   156,   302,   204,   101,   100,   101,
     208,    45,   163,   164,   293,   294,   146,   321,    26,    27,
      28,    29,   108,   122,  1372,   255,    96,   713,   714,  1029,
     298,   261,    40,   722,    42,   724,   122,   248,    82,   159,
     248,   204,   932,   101,     4,   208,     6,   146,   316,   101,
     321,   740,   741,  1674,   743,   247,   264,   232,   747,   748,
     250,    76,    77,    78,   250,   344,   239,   316,   241,   111,
     204,   266,   247,    43,   208,  1403,   209,    92,    93,    94,
    1223,   167,   771,   256,   239,   774,   241,   102,   263,   131,
     287,   288,   289,   268,    87,   110,   111,   322,    87,   322,
    1100,   116,   144,  1589,   124,  1562,  1249,  1250,    82,   358,
      84,   390,   322,   305,   327,  1592,   322,   385,   316,   368,
     369,   327,   137,   138,   108,   209,   141,   129,   322,   149,
     216,  1429,   400,   327,    87,   414,   385,  1138,   122,   303,
     304,  1139,  1032,  1033,   327,   323,   835,   323,   323,   838,
    1561,   400,   431,   316,   323,   323,  1098,   385,   323,  1645,
    1550,  1692,   322,   315,  1690,   358,  1140,  1691,  1411,  1401,
    1647,   198,   400,   322,   142,   368,   369,   111,   327,   327,
     247,     4,   316,     6,   446,   252,   253,   385,  1512,   248,
       5,   751,  1435,     8,   287,   358,   305,   390,   138,  1342,
    1343,   268,   400,   323,   297,   368,   369,   266,   267,   293,
     294,   151,  1355,   297,    37,   904,   905,   259,   306,   307,
     308,   414,   385,   198,   198,  1136,  1137,   167,   320,   306,
     307,   308,    30,     8,    20,   327,    22,   400,   431,   247,
     926,   927,   928,   287,   288,   289,   239,   298,   241,    24,
     239,   385,   241,   307,    52,   941,   805,   358,   140,   140,
    1558,   249,   230,   231,   145,    63,   400,   368,   369,   131,
       1,   162,   446,     4,   156,     6,   167,    52,     1,   213,
     214,     4,  1633,     6,   258,   751,   239,     5,   241,   100,
       8,  1630,  1632,  1631,   122,    26,    27,    28,    29,   859,
    1247,   163,   164,    26,    27,    28,    29,   100,  1255,     7,
      79,   725,   100,    30,   142,   323,   859,   401,   146,   248,
     404,   858,    20,   407,    22,   791,    95,   411,   109,   110,
     192,   248,   416,    22,  1023,    52,    25,   101,  1027,    20,
    1688,    22,   282,   903,   113,   313,    63,  1036,  1037,  1038,
      82,  1298,  1041,     4,  1043,   305,   111,   111,    30,   281,
     903,   125,   126,    43,  1053,    36,    37,    38,    91,   124,
     101,   102,   103,   127,  1092,  1093,   131,  1520,   132,   133,
      52,  1099,  1625,   104,   105,   106,   852,   853,   854,   855,
     856,    63,    18,   859,   149,    17,  1085,   481,  1087,  1088,
     155,   326,   230,   231,    12,    50,   204,   130,     1,    50,
     208,     4,  1101,     6,  1103,     1,    36,   883,     4,   322,
       6,     1,   322,  1112,     4,  1114,     6,   322,   209,   210,
     445,    55,   213,    26,    27,    28,    29,   903,    30,   322,
      26,    27,    28,    29,   198,   209,    26,    27,    28,    29,
     322,   883,     1,    39,   857,     4,     4,     6,     6,     7,
      52,   163,   164,    71,   479,   229,   230,    75,  1711,   159,
       1,    63,   322,     4,    43,     6,   725,    26,    27,    28,
      29,   711,    90,    91,    30,   313,    43,   204,    43,    58,
      59,   208,  1029,   319,   320,    26,    27,    28,    29,   107,
      43,    87,   751,    89,     7,    91,    52,    87,    94,    40,
     233,    42,   183,   149,    94,   249,   250,    63,   316,  1322,
    1323,  1324,  1325,   159,   160,   111,    30,   725,   136,  1218,
    1219,     8,   204,  1057,   159,   143,   208,     4,   107,     6,
    1008,     8,   791,  1452,  1453,  1454,  1455,   116,    52,  1238,
     130,   100,   328,   122,   101,  1244,  1693,   328,   751,    63,
    1685,  1695,   725,  1100,  1696,  1694,  1115,   100,   258,   259,
     260,   261,   262,   159,   199,   200,   201,   146,  1267,   858,
      60,    61,   127,   298,   164,    65,   131,   385,   751,    15,
      16,   725,   323,   298,   111,  1284,   113,  1286,   325,   316,
     323,   249,   400,   852,   853,   854,   855,   856,   857,     4,
     859,     6,   204,     8,   131,  1562,   208,   316,   163,   164,
     264,  1035,   139,   140,    23,   142,  1092,  1093,  1094,  1095,
    1096,    82,  1098,  1099,   883,   152,   153,   266,   267,     0,
     113,  1107,  1108,     4,   316,     6,  1449,  1450,  1451,    50,
     751,   266,   267,   233,   903,   128,   249,    23,   204,   857,
      15,    16,   208,  1572,  1573,  1574,   859,   100,   385,  1135,
    1136,  1137,  1138,  1139,  1140,  1141,   149,  1143,  1144,   109,
     110,   111,   155,   400,    82,   906,    15,    16,   909,   852,
     853,   854,   855,   856,   857,  1255,   859,    50,  1231,    50,
     204,   109,   110,  1135,   208,    50,  1120,  1396,  1122,  1141,
     903,  1143,  1144,   385,   131,    50,   247,   266,   267,   100,
     883,  1410,   100,   857,   316,   306,   307,   308,   400,  1253,
     323,   204,   205,   100,  1423,   109,   110,   323,  1298,    82,
     903,   124,  1291,   323,  1293,    82,   163,   164,   100,   166,
    1029,   852,   853,   854,   855,   856,    17,   140,   859,     4,
       5,   845,   292,   293,  1297,   849,   149,   111,   100,   113,
     316,    18,   155,   156,   323,    39,    40,    41,    42,   109,
     110,  1247,   883,   291,   292,   293,  1035,   131,   326,  1255,
      92,    93,   323,   385,     5,   139,   140,   141,   142,     7,
       1,   193,   903,     4,     7,     6,  1696,  1697,   400,    73,
     202,   203,   316,     7,   206,   207,     7,    81,    82,    83,
      84,  1100,    94,   100,    88,    26,    27,    28,    29,   287,
     288,   289,  1298,    97,    98,    99,   100,  1035,   100,   385,
     104,  1447,  1442,  1092,  1093,  1094,  1095,  1096,     5,  1098,
    1099,  1444,     7,  1445,   400,   127,   120,     7,  1107,  1108,
     322,   125,   126,   127,    41,    42,   130,  1556,     7,   133,
      17,  1120,  1035,  1122,    18,  1472,    58,    59,   101,   102,
     103,   385,    43,   326,  1152,     8,  1135,  1136,  1137,  1138,
    1139,  1140,  1141,   100,  1143,  1144,   400,    58,    59,  1496,
     322,  1035,   111,  1152,   113,   114,   115,  1100,   134,   135,
     136,   137,   184,   185,   186,   187,   188,   189,    97,    98,
      99,   100,  1120,     1,  1122,   107,     4,   725,     6,  1150,
    1151,  1152,  1153,  1154,   116,   275,   276,   277,   278,   279,
     122,   100,     1,   322,   100,     4,   107,     6,    26,    27,
      28,    29,   322,   322,  1152,   116,     5,  1120,   322,  1122,
     100,   122,   100,  1231,   146,  1107,  1108,    26,    27,    28,
      29,   100,  1135,  1136,  1137,  1138,  1139,  1140,  1141,   100,
    1143,  1144,  1231,   322,   100,   146,  1120,  1401,  1122,  1152,
    1151,  1152,  1153,  1154,     1,   100,   100,     4,  1247,     6,
     100,   299,  1562,   267,   268,   269,  1255,  1540,   725,    87,
      83,    84,    85,   100,    87,  1429,    94,   322,  1152,    26,
      27,    28,    29,    76,    77,    78,    79,    80,    81,  1297,
     322,   322,    91,  1231,  1135,  1136,  1137,  1138,  1139,  1140,
    1141,     8,  1143,  1144,   100,   100,   109,   110,  1297,  1298,
     100,  1330,   130,   725,   117,   118,   119,   120,   121,   857,
     100,    50,  1255,   264,    35,   100,    41,   111,  1231,   145,
     111,   130,    43,    68,    45,   111,    47,     5,   100,    50,
      51,    52,   325,    54,  1247,     1,   164,     8,     4,    82,
       6,  1340,  1255,   325,    82,  1340,  1562,  1231,   100,  1297,
     322,   322,  1370,   322,   111,  1354,     7,   250,  1329,  1354,
      26,    27,    28,    29,   329,  1336,  1337,  1338,  1339,   329,
     100,  1370,   323,    39,   100,     5,   322,   101,  1349,   393,
     394,   395,  1353,   725,  1297,  1298,   269,    41,   249,     7,
     857,  1362,  1340,   101,  1558,   101,  1247,   101,  1369,  1370,
    1371,  1372,  1401,     5,  1255,   233,  1354,   161,   422,   100,
      37,   101,   101,  1297,    96,   100,   100,  1388,  1389,  1390,
     321,    87,  1370,    89,   233,    91,   321,  1340,    94,   725,
    1429,   101,   100,   100,   321,   857,   265,   323,   100,   453,
     100,  1354,    43,  1472,    45,   111,    82,  1298,   185,    50,
       5,    52,   183,  1401,   323,    56,  1340,  1370,  1369,  1370,
    1371,  1372,   100,    40,   147,   322,   100,  1496,   321,   100,
    1354,   725,   265,   102,   100,   250,   233,  1388,  1389,  1390,
     323,  1429,  1316,  1317,  1318,  1319,  1370,  1035,  1401,    38,
     322,   322,   322,   159,    95,   323,    97,  1468,   322,  1470,
    1471,   322,   322,  1515,   322,     1,   322,   322,     4,   101,
       6,   232,  1524,  1484,   323,   857,  1429,  1401,  1530,  1490,
     101,   322,  1540,   130,  1495,   323,   247,  1498,   100,  1472,
      26,    27,    28,    29,   100,   323,  1507,  1508,  1509,   322,
     322,  1540,   263,   322,    40,  1429,    42,   268,   100,   270,
     101,   249,     1,  1496,   321,     4,   100,     6,   100,  1558,
       5,   857,   100,  1562,    20,  1594,   323,  1157,  1035,  1358,
     387,  1587,  1120,  1747,  1122,  1711,  1585,    26,    27,    28,
      29,  1580,  1699,    89,    91,  1580,  1318,   384,  1296,  1435,
    1589,    40,  1540,    42,  1589,  1566,  1507,  1508,  1509,   759,
    1418,   109,   110,   857,  1152,   113,   767,   303,  1393,  1017,
    1558,  1614,   826,  1035,  1536,   123,   124,   125,   126,   127,
     128,   129,   130,   131,  1595,   386,  1597,  1540,  1537,  1684,
    1628,  1094,  1580,  1095,  1605,  1606,  1607,  1608,  1609,  1610,
    1611,  1589,  1613,  1096,  1113,  1558,  1645,   841,  1118,  1562,
    1645,   286,   850,  1120,   960,  1122,  1540,   323,    44,  1144,
      46,   204,    48,    49,   172,  1061,  1232,  1580,  1686,  1253,
      56,    57,   369,   396,  1558,  1646,  1589,  1648,  1649,  1650,
    1651,  1652,   398,  1231,   399,  1152,   119,  1686,  1756,   358,
     397,   294,   298,  1035,   618,   299,  1580,  1645,  1120,   299,
    1122,    -1,    -1,    89,    -1,  1589,    -1,    -1,    -1,    -1,
      -1,  1562,    -1,    -1,  1685,  1686,  1687,  1688,    -1,    -1,
      -1,    -1,  1693,  1694,  1695,  1696,    43,    -1,    -1,  1700,
    1152,  1702,  1645,    -1,    -1,    -1,    -1,    -1,  1686,  1035,
      -1,    58,    59,    -1,    -1,  1716,    -1,    -1,  1719,  1297,
      -1,   247,  1723,  1724,  1725,  1726,  1727,  1728,  1729,  1730,
      -1,  1645,    -1,  1734,  1231,    -1,    -1,  1738,    -1,    -1,
      -1,  1742,    -1,  1686,  1685,  1686,  1687,  1688,  1120,    -1,
    1122,  1035,  1693,  1694,  1695,  1696,  1757,    -1,    -1,    -1,
     107,    -1,  1340,  1764,  1765,  1766,    -1,    -1,   247,   116,
      -1,    -1,  1686,    -1,    -1,   122,  1354,    -1,     1,  1231,
    1152,     4,    -1,     6,    -1,    -1,  1727,  1728,  1729,    -1,
       1,    -1,  1370,     4,  1120,     6,  1122,   323,    -1,   146,
    1297,    -1,    -1,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    26,    27,    28,    29,    -1,
      -1,    -1,    45,  1401,    -1,    -1,  1152,    50,    39,    52,
      -1,    54,    -1,    -1,    -1,    -1,  1120,     1,  1122,    -1,
       4,    -1,     6,  1340,   323,  1297,    -1,    -1,    -1,    -1,
      -1,  1429,    -1,    -1,    -1,    -1,    -1,  1354,    -1,  1231,
      -1,    -1,    26,    27,    28,    29,     1,    -1,  1152,     4,
      -1,     6,    -1,  1370,    -1,    86,    87,    88,    89,    -1,
      91,    -1,    -1,    94,    -1,    -1,    -1,    -1,  1340,    -1,
      -1,    26,    27,    28,    29,    -1,    -1,    -1,    35,    -1,
     111,    -1,  1354,    -1,  1401,  1231,    43,    -1,    45,    -1,
      -1,    -1,    43,    50,    51,    52,     1,    54,  1370,     4,
      -1,     6,    -1,    87,    -1,  1297,     1,    58,    59,     4,
      94,     6,  1429,    -1,    -1,    -1,   159,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    -1,    -1,  1231,   159,  1401,
      35,    26,    27,    28,    29,    -1,    91,    -1,    -1,    -1,
      45,    36,  1540,    -1,    -1,    50,   130,    52,  1340,    54,
      -1,  1297,    -1,    43,    -1,    -1,   107,  1429,    -1,    -1,
    1558,    -1,  1354,    -1,    -1,   116,    -1,    -1,    58,    59,
      -1,   122,    -1,    -1,     1,   130,    -1,     4,  1370,     6,
     164,    -1,  1580,    -1,    -1,    -1,    -1,    -1,    -1,   232,
      -1,  1589,    -1,  1297,  1340,   146,    -1,    -1,    -1,    26,
      27,    28,    29,    -1,   247,    -1,    -1,    -1,  1354,  1401,
      -1,    -1,    39,    -1,    -1,    -1,   247,   107,    -1,    -1,
     263,    -1,    -1,  1540,  1370,   268,   116,   270,    -1,    84,
      -1,    -1,   122,    -1,    -1,    -1,  1340,  1429,    -1,    -1,
      -1,  1558,    -1,    -1,    -1,    -1,   101,  1645,    -1,   233,
    1354,    -1,    -1,    -1,   159,  1401,   146,    -1,    43,    86,
      87,    88,    89,  1580,    91,    -1,  1370,    94,  1540,    -1,
     125,   126,  1589,    58,    59,   232,    -1,    -1,   233,    -1,
     323,    -1,    -1,  1429,   111,    -1,  1558,    -1,  1686,    -1,
     247,    -1,   323,     1,    -1,    -1,     4,  1401,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   263,    -1,  1580,    -1,
      -1,   268,    -1,   270,    -1,    -1,    -1,  1589,    26,    27,
      28,    29,   107,    -1,    -1,  1429,    -1,   232,  1645,    -1,
      -1,   116,   159,    -1,    -1,    -1,    -1,   122,    -1,   323,
      -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,  1540,    -1,
      -1,    -1,    -1,    -1,   209,    -1,    -1,    -1,   263,    -1,
      -1,   146,    -1,   268,    -1,   270,  1558,    -1,   323,  1686,
      -1,     1,    -1,  1645,   229,   230,    -1,    -1,    -1,    -1,
      -1,    11,    12,    13,    14,    15,    16,    17,  1580,    -1,
      20,    -1,   247,    -1,  1540,    -1,    -1,  1589,    -1,    -1,
      -1,    -1,    -1,   111,    -1,    -1,    -1,    -1,   263,    -1,
      -1,    -1,  1558,   268,  1686,   270,    -1,    -1,   323,    -1,
     247,    -1,    -1,    -1,    43,    -1,    -1,    -1,   323,    -1,
      -1,    -1,    -1,    -1,  1580,    -1,  1540,    -1,    -1,    58,
      59,    71,    -1,  1589,    74,    75,    76,    77,    78,    79,
      -1,    -1,    -1,  1645,  1558,    -1,    86,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    -1,    97,    98,    99,
     100,    -1,   102,    -1,    -1,   105,  1580,   107,    -1,    -1,
     110,   111,    -1,   113,    -1,  1589,   116,    -1,   107,    -1,
       1,    -1,    -1,     4,  1686,     6,   323,   116,    -1,  1645,
      -1,    -1,    -1,   122,    -1,   135,   136,   137,   138,    -1,
      -1,   141,    23,   143,    43,    26,    27,    28,    29,    30,
      31,    -1,    33,    34,    35,   233,    -1,   146,    -1,    58,
      59,     1,    -1,    -1,     4,    -1,     6,    -1,    -1,    50,
    1686,  1645,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    65,    -1,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,
      91,    -1,  1686,    -1,    95,    -1,    97,   116,    -1,   100,
     101,   102,   103,   122,    -1,   106,    -1,   108,    -1,    -1,
     111,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,   122,    -1,   109,   110,   323,    -1,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,   138,    -1,    -1,
      -1,    -1,   143,    -1,   130,   146,    -1,    -1,    -1,     1,
     151,   111,     4,   154,     6,    -1,   157,   158,   159,    -1,
     146,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,   190,
     191,    -1,   193,   194,   195,   196,    -1,    -1,    -1,    -1,
      -1,   202,   203,    -1,    -1,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,    -1,
      -1,   232,    -1,    -1,    86,    87,    88,    89,    -1,    91,
      -1,    -1,    94,    -1,    -1,    -1,   247,   233,   234,   235,
     236,    -1,    -1,    -1,    -1,    -1,   257,    -1,    -1,   111,
      -1,    -1,   263,   249,   250,   251,    -1,   268,    -1,    -1,
      -1,    -1,    -1,   233,   109,   110,   277,   278,    -1,   280,
      -1,    -1,   283,   284,   285,   286,    -1,    -1,   123,   290,
     125,   126,   127,   294,   295,   296,    -1,    -1,    -1,   300,
     301,    -1,    -1,    -1,    -1,    -1,    -1,   159,   309,    -1,
      -1,   312,   313,   148,   149,   150,    -1,    -1,   438,    -1,
      -1,   322,   323,   324,    -1,   445,   327,    -1,     1,    -1,
      -1,     4,    -1,     6,    -1,   455,    -1,   457,    -1,   459,
      -1,   461,    -1,   131,    -1,    -1,   466,    -1,    -1,   469,
      23,   471,   140,    26,    27,    28,    29,    30,    31,   479,
      33,    34,    35,   323,    -1,    -1,    -1,   155,    -1,    -1,
      -1,   159,    -1,    -1,    -1,   163,   164,    50,    -1,    -1,
     168,   169,   170,   171,   172,    -1,    -1,    60,    61,    -1,
      -1,    -1,    65,    -1,    -1,   247,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,
      -1,    -1,    95,    -1,    97,    -1,    -1,   100,   101,   102,
     103,    -1,    -1,   106,    -1,   108,    -1,    -1,   111,   112,
      -1,    -1,    -1,   116,    -1,   111,    -1,    -1,    -1,   122,
      -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,
     143,   323,    -1,   146,    -1,    -1,   142,    -1,   151,    -1,
     146,   154,    -1,   149,   157,   158,   159,    -1,    35,   162,
      -1,    -1,   165,    -1,   167,    -1,    43,    -1,    45,    -1,
      47,    -1,    -1,    50,    51,    52,    -1,    54,    -1,    -1,
      -1,    58,    59,    -1,    -1,    -1,    -1,   190,   191,    -1,
     193,   194,   195,   196,    -1,    -1,    -1,    -1,    -1,   202,
     203,   197,    -1,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,    -1,    -1,   232,
     107,    -1,    -1,    -1,   230,   231,    -1,    -1,    -1,   116,
      -1,    -1,    -1,    -1,   247,   122,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   257,    -1,    -1,    -1,    -1,    -1,
     263,    -1,    -1,    -1,    -1,   268,    -1,    -1,    -1,   146,
      -1,    -1,    -1,    -1,   277,   278,    -1,   280,    -1,    -1,
     283,   284,   285,   286,    -1,    -1,    -1,   290,    -1,    -1,
      -1,   294,   295,   296,    -1,    -1,    -1,   300,   301,    -1,
       1,    -1,    -1,     4,    -1,     6,   309,    -1,    -1,   312,
     313,    -1,    -1,    -1,    -1,    -1,    -1,   313,    -1,   322,
     323,   324,    23,    -1,   327,    26,    27,    28,    29,    30,
      31,    -1,    33,    34,    35,   170,    -1,    -1,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,    50,
      -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
     247,    -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    -1,   263,    -1,    -1,    -1,
      91,   268,    -1,   270,    95,    -1,    97,    -1,    -1,   100,
     101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,    -1,
     111,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,
      -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,
     151,    -1,    -1,   154,    -1,    -1,   157,   158,   159,    -1,
      -1,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,
     191,    -1,   193,   194,   195,   196,   946,   947,   948,    -1,
      -1,   202,   203,    -1,    -1,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,    -1,
      -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
      -1,    -1,    -1,    -1,    -1,    -1,   247,    82,    -1,    84,
      -1,    -1,    -1,    -1,    -1,    21,   257,    23,    -1,    -1,
      -1,    -1,   263,    -1,    -1,    31,    -1,   268,    34,    -1,
      -1,    -1,    -1,    -1,   109,   110,   277,   278,    -1,   280,
      -1,    -1,   283,   284,   285,   286,    -1,    -1,   123,   290,
     125,   126,   127,   294,   295,   296,    -1,    -1,    -1,   300,
     301,    -1,    68,    -1,    -1,    -1,    -1,    -1,   309,    -1,
      -1,   312,   313,   148,   149,   150,    82,    -1,    84,    -1,
      -1,   322,   323,   324,    -1,    -1,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,   101,   102,   103,    -1,    -1,
     106,    -1,   108,    -1,    -1,    -1,   112,    -1,    -1,    -1,
     116,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,
     126,    -1,    -1,   198,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    -1,    -1,   143,    -1,    -1,
     146,    -1,    -1,    -1,    -1,   151,    -1,    -1,   154,    -1,
      -1,   157,   158,    -1,    -1,    -1,   162,    -1,    -1,   165,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   258,   190,   191,    -1,   193,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,    -1,    -1,   232,    -1,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,   245,
     246,    -1,    -1,    -1,    21,    -1,    23,    -1,    -1,    -1,
      -1,    -1,   258,    -1,    31,    -1,    -1,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   277,   278,    -1,    -1,    -1,    -1,   283,   284,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,
     296,    68,    -1,    -1,   300,   301,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,   311,    -1,   313,    -1,    -1,
     127,    -1,    -1,   130,    -1,    -1,    -1,    -1,   324,    -1,
      -1,   327,    -1,   100,   101,   102,   103,    -1,    -1,   106,
     147,   108,    -1,    -1,    -1,   112,    -1,    -1,    -1,   116,
      -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   138,    -1,    -1,    -1,    -1,   143,    -1,    -1,   146,
      -1,    -1,    -1,    -1,   151,    -1,    -1,   154,    -1,    -1,
     157,   158,    -1,    -1,    -1,   162,    -1,    -1,   165,    -1,
     167,    -1,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   190,   191,    -1,   193,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   270,    -1,   232,    -1,     5,    -1,    -1,
     277,   278,    -1,    -1,    -1,   242,    -1,    -1,   245,   246,
     287,    -1,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   313,    -1,    -1,    -1,
     277,   278,    -1,    -1,    -1,    -1,   283,   284,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,   296,
      68,    -1,    -1,   300,   301,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   310,   311,    -1,   313,    -1,    -1,   127,
      -1,    -1,   130,    -1,    -1,    -1,    -1,   324,    -1,    -1,
     327,    -1,   100,   101,   102,   103,    -1,    -1,   106,   147,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   296,    68,
      -1,    -1,   300,   301,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   310,   311,    -1,   313,    -1,    82,    -1,    84,
      -1,    -1,    -1,    -1,    -1,    -1,   324,    -1,    -1,   327,
      -1,   100,   101,   102,   103,    -1,    -1,   106,    -1,   108,
      -1,    -1,    -1,   112,   109,   110,    -1,   116,   113,    -1,
      -1,    -1,    -1,   122,    -1,    -1,    -1,   126,   123,   124,
     125,   126,   127,   128,   129,   130,   131,    -1,    -1,   138,
      -1,    -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,
      -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,
      -1,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   190,   191,    -1,   193,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   198,    -1,    -1,    -1,    -1,    -1,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,    -1,    -1,   232,    -1,     5,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   242,    -1,    -1,   245,   246,    -1,    -1,
      -1,    21,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,   258,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,   278,
      -1,    -1,    -1,    -1,   283,   284,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   296,    68,    -1,
      -1,   300,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   310,   311,    -1,   313,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   324,    -1,    -1,   327,    -1,
     100,   101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,
      -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,   126,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,
      -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,
      -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     190,   191,    -1,   193,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   242,    -1,    -1,   245,   246,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,   277,   278,    -1,
      -1,    -1,    -1,   283,   284,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,
     300,   301,    -1,    -1,    -1,    -1,    68,   101,   102,   103,
     310,   311,    -1,   313,   108,    -1,    -1,    -1,   112,    -1,
      -1,    -1,   116,    -1,   324,    -1,    -1,   327,   122,    -1,
      -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
     112,    -1,   146,    -1,   116,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,
      -1,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,   151,
      -1,    -1,   154,    -1,    -1,   157,   158,    -1,    -1,    -1,
     162,    -1,    -1,   165,    -1,   167,    21,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   242,    -1,
      -1,   245,   246,    68,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    -1,    -1,    49,    50,
      -1,    52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
     242,    -1,    -1,   245,   246,   100,   101,   102,   103,   283,
     284,   106,    -1,   108,    -1,    -1,    -1,   112,    -1,    -1,
      -1,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,
      -1,   126,    -1,    -1,    95,    -1,    97,    98,    99,    -1,
      -1,   283,   284,   138,   286,    -1,    -1,    -1,   143,    -1,
      -1,   146,    -1,   327,    -1,    -1,   151,    -1,    -1,   154,
      -1,    -1,   157,   158,    -1,    -1,    -1,   162,   310,   311,
     165,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     322,    -1,   324,    -1,    -1,   327,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   190,   191,    -1,   193,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,    -1,    -1,   232,    -1,    -1,
      21,    -1,    23,    -1,    -1,    -1,    -1,   242,    -1,    -1,
     245,   246,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   277,   278,    -1,    -1,   247,    68,   283,   284,
      -1,   252,   253,   254,   255,    -1,    -1,    -1,    -1,    -1,
      -1,   296,   263,    -1,    -1,   300,   301,   268,    -1,   270,
     271,    21,    -1,    -1,    -1,   310,   311,    -1,   313,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,   108,    -1,   324,
      -1,   112,   327,    -1,    -1,   116,    -1,    87,    -1,    -1,
      -1,   122,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    68,   109,
     110,    -1,   143,   113,    -1,   146,    -1,    -1,    -1,    -1,
     151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,    -1,
     130,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,    -1,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,   108,    -1,
      -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,   190,
     191,    -1,   122,    -1,    -1,    -1,   126,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,   143,    -1,   185,   146,    -1,    -1,    -1,
      -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,
      -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,   209,
      -1,   242,    -1,    -1,   245,   246,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
     190,   191,    -1,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,    -1,    -1,   249,
     250,   251,   283,   284,    -1,   286,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     270,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,
     311,    -1,   242,    -1,    -1,   245,   246,    -1,    -1,    -1,
      -1,   322,    -1,   324,    -1,    -1,   327,    -1,    -1,    -1,
      -1,    -1,    -1,   100,   101,   102,   103,    -1,    -1,    -1,
      -1,   108,    -1,    -1,    -1,   112,    -1,    -1,    -1,   116,
      -1,    -1,    -1,   283,   284,   122,   286,    -1,    -1,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   138,    -1,    -1,    -1,    -1,   143,    -1,    -1,   146,
     310,   311,    -1,    -1,   151,    -1,    -1,   154,    -1,    -1,
     157,   158,   322,    -1,   324,   162,    -1,   327,   165,    -1,
     167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   190,   191,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,   242,    -1,    65,   245,   246,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   283,   284,   106,   286,
     108,    -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   310,   311,    -1,    -1,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,   143,    -1,   324,   146,    -1,
     327,    -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,
     158,    -1,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   190,   191,    -1,   193,   194,   195,   196,    -1,
      -1,    -1,    -1,    -1,   202,   203,    -1,    -1,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,    -1,    -1,   232,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,   257,
      30,    31,    -1,    -1,    34,   263,    -1,    -1,    -1,    -1,
     268,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,
     278,    -1,   280,    -1,    -1,   283,   284,   285,   286,    -1,
      -1,    -1,   290,    -1,    -1,    -1,   294,   295,   296,    -1,
      -1,    -1,   300,   301,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   309,    -1,    -1,   312,   313,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   322,    -1,   324,    -1,    -1,   327,
     100,   101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,
      -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,
      -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,
      -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    -1,    34,    -1,    -1,    -1,
     190,   191,    -1,   193,   194,   195,   196,    -1,    -1,    -1,
      -1,    -1,   202,   203,    -1,    -1,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,   232,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,   102,   103,    -1,    -1,   106,    -1,
     108,    -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,   277,   278,    -1,
      -1,    -1,    -1,   109,   110,    -1,    -1,   113,    -1,    -1,
     138,    -1,    -1,    -1,    -1,   143,   296,    -1,   146,    -1,
     300,   301,    -1,   151,   130,    -1,   154,    -1,    -1,   157,
     158,    -1,   312,   313,   162,    -1,    -1,   165,    -1,   167,
      -1,    -1,   322,    -1,   324,    -1,    -1,   327,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   190,   191,    -1,   193,   194,   195,   196,    -1,
      -1,    -1,    -1,    -1,   202,   203,    -1,    -1,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,    -1,   209,   232,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,   233,   234,   235,
     236,   237,   238,    -1,   240,   241,   242,   243,   244,   245,
     246,    -1,    -1,   249,   250,   251,    -1,    -1,    -1,   277,
     278,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   270,    -1,    -1,    -1,   296,    -1,
      -1,    -1,   300,   301,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   312,   313,   100,   101,   102,   103,
      -1,    -1,   106,    -1,   108,    -1,   324,    -1,   112,   327,
      -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,   143,
      -1,    -1,   146,    -1,    -1,    -1,    -1,   151,    -1,    -1,
     154,    -1,    -1,   157,   158,    -1,    -1,    -1,   162,    -1,
      -1,   165,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   190,   191,    -1,   193,
     194,   195,   196,    -1,    -1,    -1,    -1,    -1,   202,   203,
      -1,    -1,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,    -1,    -1,   232,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   277,   278,    -1,    -1,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   296,    -1,    -1,    -1,   300,   301,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   312,   313,
     100,   101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,
     324,    -1,   112,   327,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,   126,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,
      -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,
      -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     190,   191,    -1,   193,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   242,    -1,    -1,   245,   246,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,   278,    -1,
      -1,    -1,    -1,   283,   284,    -1,    -1,    -1,     0,     1,
      -1,    -1,     4,    -1,     6,    -1,   296,    -1,    -1,    -1,
     300,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     310,   311,    -1,   313,    26,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    35,   324,    -1,    -1,   327,    -1,    -1,
      -1,    43,    -1,    45,    -1,    47,    -1,    -1,    50,    51,
      52,    -1,    54,    -1,    -1,    -1,    58,    59,    60,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,    -1,    -1,   107,    -1,   100,   101,   102,
     103,    -1,    -1,    -1,   116,   108,    -1,    -1,    -1,   112,
     122,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,
      -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   146,   138,    -1,    -1,    -1,    -1,
     143,    -1,    -1,   146,    -1,    -1,    -1,    -1,   151,    -1,
      -1,   154,    -1,    -1,   157,   158,    -1,    -1,    -1,   162,
      -1,    -1,   165,    68,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,   191,    -1,
      -1,    -1,    -1,    -1,    -1,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    -1,   112,    -1,    -1,
      -1,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,
     232,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   138,    -1,   247,    -1,    -1,   143,   242,
      -1,   146,   245,   246,    -1,    -1,   151,    -1,    -1,   154,
      -1,   263,   157,   158,    -1,    -1,   268,   162,   270,    -1,
     165,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     283,   284,    -1,   286,    -1,   190,   191,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,   311,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   324,    -1,    -1,   327,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,
     245,   246,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   283,   284,
      -1,   286,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   310,   311,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   324,
      -1,    -1,   327
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
     110,   113,   130,   209,   233,   234,   235,   236,   237,   238,
     240,   241,   242,   243,   244,   245,   246,   249,   250,   251,
     270,   600,   601,   604,   287,   297,   588,   528,   533,   298,
     193,   202,   203,   206,   207,   668,   319,   320,   591,   527,
     397,   353,   307,   353,    44,    46,    48,    49,    56,    57,
      89,   351,   413,   413,   413,   549,   563,   551,   553,   100,
     100,   100,    82,   596,   248,   503,   397,   511,   579,   579,
      60,    96,   397,   101,   581,    87,   185,   239,   600,   601,
     248,   248,   264,   248,   266,   267,   447,    82,    82,   596,
       4,   333,   535,   536,   305,   421,   427,   249,   250,   436,
     437,   159,   258,   259,   260,   261,   262,   440,   441,   281,
     457,     5,    21,    68,    82,    84,   108,   112,   116,   122,
     126,   146,   193,   242,   245,   246,   258,   283,   284,   310,
     311,   324,   469,   470,   471,   472,   473,   474,   475,   477,
     478,   479,   480,   481,   482,   483,   512,   515,   521,   573,
     574,   575,   580,   585,   589,   595,   596,   597,   599,   605,
     606,   609,    36,    37,    38,   183,   463,   464,    82,   287,
     288,   289,   486,   492,   493,    82,   489,   492,   291,   292,
     293,   496,   497,   498,   499,    23,   511,   513,   514,    43,
     507,   508,    15,    16,    17,    18,   326,     8,    24,    52,
       9,    10,    11,    12,    13,    14,   108,   112,   116,   122,
     138,   143,   146,   151,   154,   157,   158,   162,   165,   167,
     190,   191,   286,   324,   480,   512,   514,   515,   529,   530,
     531,   534,   565,   566,   567,   568,   569,   570,   571,   572,
     574,   575,   576,   577,    50,    50,   547,   565,   566,   547,
      36,   465,   322,   322,   322,   322,   322,   416,   423,   466,
     355,   358,   361,   363,   366,   370,   413,   413,   413,   549,
     563,   551,   553,   423,    55,    55,    55,    55,   363,    55,
     370,   413,   363,   402,   407,   422,    43,    43,    43,   413,
     402,   402,   402,   402,   402,   402,   402,   407,   397,     7,
       8,   111,   213,   214,   518,   101,   123,   248,   108,   122,
     108,   122,   134,   135,   136,   137,   620,   170,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   642,
     598,   328,   328,   109,   110,   122,   130,   146,   233,   234,
     235,   602,   603,   604,   298,   298,   100,   316,   590,   325,
     352,   353,   561,   561,   561,   249,   548,   264,   562,   447,
     550,   398,   552,     5,   122,   146,   482,    82,   482,   500,
     501,   528,    23,    23,    94,   322,    50,    50,    50,   100,
     266,    50,   604,    50,   482,   482,   266,   267,   451,   482,
     100,   482,   482,    82,   480,   534,   539,   540,   545,   571,
     572,     7,   323,   398,   100,   100,   437,    75,   108,   122,
     167,   216,   443,   398,   100,   100,   100,   398,   442,   441,
     138,   151,   167,   282,   482,     5,   482,    82,    82,   474,
     512,   575,    15,    16,    17,    18,   326,    20,    22,     8,
      52,     5,   492,    82,    84,   198,   258,     7,     7,   100,
     100,   464,     5,     7,     5,   482,   482,   497,     7,   397,
     322,   397,   322,   508,   576,   576,   567,   568,   569,   527,
     322,   430,   513,   566,   571,     7,    15,    16,    17,    18,
     326,     7,    20,    22,     8,   566,   482,   482,   332,   332,
     100,   357,   359,   362,   367,   371,   465,   322,   322,   322,
     322,   322,   561,   561,   561,   548,   562,   550,   552,   100,
     100,   100,   100,   100,   322,   561,   402,   402,   402,   100,
     520,   111,   127,   132,   133,   198,   621,    94,   127,   184,
     185,   186,   187,   188,   189,   643,   100,   100,   109,   110,
     109,   110,   100,   100,   299,   587,   100,   156,   315,   592,
     596,   322,   322,   322,   100,   451,   100,   482,     5,     5,
     482,   513,    87,    90,   421,   541,   542,   398,   398,   100,
     528,   537,   538,   482,   482,   482,   100,   482,    50,   482,
     100,   101,   250,   448,    41,   482,   333,     5,   333,    87,
      90,   247,   421,   543,   544,   333,   536,   145,   140,   145,
     444,   445,   111,   111,    68,   111,   482,     5,   482,   482,
     325,   469,   469,   470,   471,   472,   100,   474,   469,   476,
     513,   534,   482,   482,    82,     8,    82,   512,   575,   605,
     605,   482,   493,   482,   492,   499,   500,   537,   333,   431,
     432,   325,   571,   576,   576,   567,   568,   569,   571,   100,
     571,   531,   571,    37,   332,    35,    45,    50,    52,    54,
     159,   232,   247,   263,   268,   270,   323,   332,   334,   356,
      91,   111,   159,   323,   332,   334,   387,   393,   394,   423,
      39,    86,    87,    88,    89,    91,    94,   111,   159,   247,
     323,   332,   334,   368,    39,    87,    89,   111,   159,   323,
     332,   334,   368,    40,    42,   247,   323,   332,   334,   357,
     359,   362,   367,   371,   322,   322,   322,   371,     7,   329,
     329,   587,   302,   587,   100,   109,   110,   593,   381,   382,
     380,   250,   100,   448,   482,   482,     5,   101,   399,   399,
     542,   322,   427,   541,   482,    20,   101,   269,   449,   482,
      41,   546,   572,   578,   399,   399,   249,   544,     7,   101,
     101,   101,   482,     5,   482,   161,   482,   492,   492,     5,
     232,   323,   426,   427,   539,     7,   323,   100,    37,   397,
     415,   397,   406,   397,   409,   409,   397,   412,   101,    87,
     239,   241,   415,   415,   415,   415,   332,    76,    77,   395,
     396,   511,   101,    96,   332,   332,   332,   332,   360,   516,
     399,   399,   321,    92,    93,   369,   100,   101,   125,   126,
     209,   229,   230,   375,   376,   386,    83,    84,    85,    87,
     364,   365,   332,   332,   360,   399,   321,   376,   364,   332,
     101,   321,   323,   323,   323,   323,   323,   381,   382,   380,
     323,   100,   100,    91,   130,   233,   323,   332,   334,   559,
      87,    94,   130,   164,   233,   323,   332,   334,   560,   111,
     233,   323,   332,   334,   556,   100,    20,   101,   449,   482,
     537,   323,   275,   276,   277,   278,   279,   454,   265,   453,
     100,   482,   333,   100,   445,   482,    82,   500,     5,   323,
     323,     5,   333,   432,   183,   467,   100,   377,   358,   361,
     366,   370,   415,   415,   415,   377,   377,   377,   377,    40,
       8,   332,   332,   332,   363,     8,   332,     7,   332,     5,
     332,   363,     5,   332,   147,   388,   322,   372,   323,   323,
     323,   587,   321,   162,   167,   555,   401,   399,   100,   555,
     100,   401,   102,   401,   454,   453,   427,   265,   452,   100,
     448,   250,   482,   323,   500,   578,    38,   468,   332,   322,
     322,   322,   322,   322,   377,   377,   377,   322,   322,   322,
     322,   101,   516,   375,   365,    84,   360,    84,   247,   263,
     268,   270,   376,    22,   100,   101,   320,   389,   390,   391,
     511,   332,   101,   373,   374,   332,   322,   332,   332,   332,
     332,   332,   332,   332,   130,   332,   452,   323,   100,   101,
     250,   100,   323,   333,   467,   385,   359,   362,   367,   371,
     322,   322,   322,   378,   383,   379,   384,    41,    42,   392,
     360,   332,   376,   332,   332,   332,   332,   332,   100,    22,
      25,     7,   323,   101,   557,   558,   555,   249,   468,   323,
     332,   334,   465,   323,   323,   323,   323,   381,   382,   380,
     323,   332,   334,   548,   323,   332,   334,   562,   323,   332,
     334,   550,   323,   332,   334,   552,   398,   321,   388,   332,
     332,   100,   100,   333,   374,     5,     7,   323,   332,   332,
     332,   332,   332,   332,   323,   323,   323,   332,   332,   332,
     332,   372,   100,   558,   332,   332,   332,   332
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
     341,   341,   341,   342,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   343,   343,   344,
     344,   344,   344,   344,   344,   345,   345,   345,   345,   345,
     345,   345,   346,   347,   347,   348,   348,   349,   350,   350,
     351,   351,   351,   351,   351,   351,   351,   351,   352,   352,
     353,   353,   353,   354,   355,   356,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   358,   359,   359,   359,   359,   359,   359,   359,
     360,   360,   361,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   363,   363,   364,   364,   365,
     365,   365,   365,   366,   367,   367,   367,   367,   367,   367,
     367,   367,   367,   367,   367,   367,   367,   367,   367,   368,
     368,   369,   369,   370,   371,   371,   371,   371,   371,   371,
     372,   373,   373,   373,   374,   375,   375,   376,   376,   377,
     378,   378,   378,   378,   379,   379,   379,   379,   380,   380,
     380,   380,   381,   381,   381,   381,   382,   382,   382,   382,
     383,   383,   383,   383,   384,   384,   384,   384,   385,   385,
     385,   385,   386,   386,   386,   386,   386,   387,   388,   389,
     389,   390,   390,   390,   390,   390,   391,   391,   392,   392,
     392,   393,   394,   395,   395,   396,   396,   397,   398,   398,
     398,   399,   400,   400,   401,   401,   401,   401,   401,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   419,   419,
     419,   420,   421,   422,   422,   423,   423,   424,   425,   425,
     426,   426,   426,   426,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   428,   428,   429,   430,   430,   431,   431,
     431,   432,   433,   433,   434,   434,   435,   435,   436,   436,
     437,   437,   438,   438,   439,   440,   440,   441,   441,   441,
     441,   441,   441,   442,   443,   443,   443,   443,   443,   444,
     444,   445,   445,   446,   446,   446,   447,   447,   447,   448,
     448,   449,   449,   450,   450,   451,   451,   451,   452,   452,
     453,   453,   453,   454,   454,   454,   454,   454,   455,   456,
     457,   457,   457,   457,   457,   458,   459,   459,   460,   460,
     460,   460,   460,   460,   461,   461,   462,   462,   463,   463,
     464,   464,   464,   464,   465,   465,   466,   467,   467,   468,
     468,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   470,   470,   470,   471,   471,   472,
     472,   473,   473,   474,   475,   475,   476,   476,   477,   477,
     478,   479,   480,   481,   481,   481,   482,   482,   482,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   484,   484,   485,   486,   486,   486,   487,
     487,   488,   489,   489,   489,   489,   489,   490,   490,   491,
     491,   492,   492,   493,   493,   493,   494,   494,   495,   496,
     496,   497,   497,   498,   498,   499,   499,   500,   500,   501,
     502,   502,   502,   503,   503,   503,   504,   504,   505,   505,
     506,   507,   507,   508,   509,   509,   510,   511,   512,   512,
     513,   513,   514,   515,   516,   516,   516,   516,   516,   516,
     516,   516,   516,   516,   516,   516,   516,   516,   516,   517,
     518,   518,   518,   519,   519,   519,   519,   519,   520,   520,
     521,   521,   522,   522,   523,   523,   523,   524,   524,   525,
     525,   526,   526,   527,   528,   528,   529,   530,   531,   531,
     532,   533,   533,   533,   534,   535,   535,   535,   536,   536,
     536,   537,   537,   538,   539,   539,   540,   541,   541,   542,
     542,   542,   543,   543,   544,   544,   544,   544,   544,   545,
     545,   546,   546,   547,   547,   548,   549,   550,   551,   552,
     553,   554,   554,   554,   555,   555,   556,   556,   557,   557,
     558,   559,   559,   559,   560,   560,   560,   560,   560,   561,
     562,   562,   563,   564,   564,   564,   565,   565,   566,   566,
     566,   566,   567,   567,   567,   568,   568,   569,   569,   570,
     570,   571,   572,   572,   572,   572,   573,   573,   574,   575,
     575,   575,   575,   575,   575,   575,   575,   575,   575,   575,
     575,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   577,   577,
     577,   577,   577,   577,   578,   578,   578,   578,   578,   578,
     579,   579,   580,   580,   580,   581,   581,   582,   582,   582,
     582,   582,   583,   583,   583,   583,   583,   583,   583,   583,
     583,   583,   583,   583,   583,   583,   583,   583,   583,   583,
     583,   583,   583,   583,   583,   583,   584,   584,   584,   584,
     584,   584,   585,   586,   586,   587,   587,   588,   588,   589,
     590,   590,   591,   591,   592,   592,   593,   593,   594,   594,
     595,   595,   595,   596,   596,   597,   597,   598,   598,   598,
     598,   599,   599,   599,   600,   600,   601,   601,   601,   601,
     601,   601,   601,   601,   601,   601,   601,   601,   601,   601,
     601,   601,   601,   602,   602,   602,   602,   602,   602,   602,
     603,   603,   603,   603,   604,   604,   604,   604,   605,   605,
     606,   606,   607,   607,   607,   607,   608,   609,   609,   609,
     609,   609,   609,   609,   609,   609,   609,   609,   609,   609,
     609,   609,   609,   609,   609,   610,   611,   611,   611,   612,
     613,   613,   613,   614,   615,   615,   615,   615,   616,   617,
     617,   617,   617,   617,   617,   617,   617,   617,   618,   618,
     618,   619,   619,   619,   619,   619,   619,   619,   619,   619,
     619,   619,   619,   620,   620,   620,   620,   621,   621,   621,
     621,   621,   622,   623,   623,   623,   623,   623,   623,   623,
     624,   625,   625,   625,   625,   626,   627,   627,   627,   627,
     627,   627,   627,   627,   627,   628,   629,   629,   629,   629,
     629,   629,   629,   629,   630,   631,   631,   631,   631,   631,
     632,   633,   633,   634,   635,   635,   635,   636,   637,   637,
     637,   637,   638,   639,   639,   639,   639,   640,   640,   640,
     641,   641,   641,   641,   641,   641,   641,   641,   641,   641,
     642,   642,   642,   642,   642,   642,   642,   642,   642,   642,
     642,   642,   643,   643,   643,   643,   643,   643,   643,   643,
     644,   645,   645,   645,   646,   647,   647,   647,   647,   648,
     649,   649,   650,   650,   650,   650,   650,   650,   650,   650,
     651,   652,   652,   653,   654,   654,   654,   654,   655,   656,
     657,   658,   659,   660,   660,   660,   660,   661,   662,   662,
     662,   662,   662,   662,   663,   664,   664,   665,   666,   666,
     666,   666,   666,   667,   668,   668,   668,   668,   668
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
       2,     6,     2,     2,     2,     2,     4,     2,     2,     2,
       2,     2,     2,     3,     2,     2,     2,     2,     2,     3,
       2,     2,     3,     2,     2,     3,     2,     2,     3,     2,
       2,     3,     2,     2,     3,     2,     2,     3,     3,     2,
       2,     2,     2,     2,     2,     3,     4,     4,     4,     2,
       3,     2,     2,     3,     2,     2,     2,     2,     2,     3,
       2,     2,     3,     2,     1,     2,     1,     3,     0,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     1,     2,     1,     0,     2,     0,     2,     2,     3,
       8,     8,     8,     8,     8,     8,     9,     9,     9,     8,
       8,     8,     0,     0,     2,     2,     3,     3,     3,     3,
       1,     3,     0,     0,     2,     2,     4,     4,     4,     4,
       4,     3,     4,     2,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     0,     0,     2,     2,     4,     6,     7,
       6,     7,     6,     6,     6,     6,     4,     4,     3,     2,
       2,     1,     1,     0,     0,     2,     2,     5,     5,     2,
       3,     1,     3,     3,     1,     1,     1,     1,     3,     0,
       0,     2,     2,     2,     0,     2,     2,     2,     0,     2,
       2,     2,     0,     2,     2,     2,     0,     2,     2,     2,
       0,     2,     2,     2,     0,     2,     2,     2,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     6,     2,     1,
       1,     1,     1,     1,     3,     3,     1,     2,     2,     3,
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     2,     3,     1,     2,     3,     1,     2,     3,
       1,     2,     3,     1,     2,     2,     2,     1,     2,     2,
       2,     2,     2,     0,     1,     1,     2,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     1,     1,     3,
       3,     5,     3,     4,     1,     2,     1,     3,     1,     2,
       2,     2,     1,     2,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     1,     2,     2,     1,     1,     1,     3,
       1,     1,     1,     7,     6,     3,     1,     1,     0,     1,
       1,     0,     3,     5,     3,     1,     1,     0,     0,     3,
       0,     3,     3,     1,     1,     1,     1,     1,     2,     1,
       0,     4,     4,     4,     3,     2,     1,     1,     3,     4,
       4,     5,     6,     5,     1,     2,     1,     3,     1,     2,
       2,     2,     1,     1,     6,     8,     0,     0,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     3,     1,     1,     3,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     3,     4,     5,     2,     3,     2,     6,     4,
       3,     4,     3,     2,     1,     1,     3,     4,     1,     2,
       1,     1,     2,     3,     1,     3,     4,     3,     5,     3,
       6,     1,     3,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     1,     1,     3,     1,     1,     1,     2,     1,
       4,     5,     6,     1,     1,     1,     7,     8,     6,     1,
       1,     1,     2,     2,     6,     8,     1,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     3,     0,     2,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     3,     3,     3,     1,     1,
       3,     1,     1,     1,     3,     1,     3,     3,     3,     3,
       5,     1,     2,     1,     1,     2,     1,     1,     2,     2,
       2,     1,     1,     2,     2,     2,     1,     5,     1,     1,
       1,     1,     1,     1,     1,     4,     0,     4,     0,     1,
       0,     1,     1,     1,     1,     1,     5,     3,     1,     3,
       3,     3,     6,     3,     3,     3,     3,     3,     3,     0,
       6,     5,     0,     2,     2,     3,     3,     3,     1,     1,
       1,     1,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       1,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     3,     4,     1,
       4,     4,     2,     1,     1,     0,     2,     1,     1,     5,
       2,     0,     1,     1,     1,     1,     1,     1,     4,     5,
       7,     5,     4,     1,     1,     2,     3,     1,     1,     1,
       1,     2,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       3,     3,     4,     4,     4,     5,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     6,     1,     1,     1,     2,
       1,     1,     1,     2,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     4,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     1,     1,     2,     1,     1,     1,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     2,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     2,     1,     1,     1,     1,     2,     4,
       2,     1,     2,     1,     1,     1,     4,     2,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1
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
#line 4282 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 102: /* "quoted string"  */
#line 301 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4288 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 103: /* "string with a trailing asterisk"  */
#line 301 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4294 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* line  */
#line 577 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4300 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 336: /* base_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4306 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* add_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4312 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* replace_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4318 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* create_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4324 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* insert_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4330 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* delete_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4336 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* get_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4342 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* list_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4348 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* reset_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4354 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 345: /* flush_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4360 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* rename_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4366 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* import_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4372 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 348: /* export_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4378 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 349: /* monitor_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4384 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* monitor_event  */
#line 801 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4390 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* describe_cmd  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4396 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 355: /* table_block_alloc  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 4402 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* chain_block_alloc  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 4408 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* typeof_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4414 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* set_block_alloc  */
#line 607 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4420 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 363: /* set_block_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4426 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 366: /* map_block_alloc  */
#line 610 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4432 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 370: /* flowtable_block_alloc  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 4438 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 372: /* flowtable_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4444 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* flowtable_list_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4450 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 374: /* flowtable_expr_member  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4456 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* data_type_atom_expr  */
#line 574 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4462 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* data_type_expr  */
#line 574 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4468 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* obj_block_alloc  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4474 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* type_identifier  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4480 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* extended_prio_name  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4486 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* dev_spec  */
#line 593 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).expr)); }
#line 4492 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* policy_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4498 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* identifier  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4504 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* string  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4510 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* table_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4516 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* tableid_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4522 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* chain_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4528 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* chainid_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4534 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* chain_identifier  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4540 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* set_spec  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4546 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* setid_spec  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4552 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* set_identifier  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4558 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* flowtable_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4564 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* flowtableid_spec  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4570 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* obj_spec  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4576 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* objid_spec  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4582 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* obj_identifier  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4588 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* handle_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4594 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* position_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4600 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* index_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4606 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* rule_position  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4612 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* ruleid_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4618 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* comment_spec  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4624 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* ruleset_spec  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4630 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* rule  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 4636 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* stmt_list  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 4642 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* stateful_stmt  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4648 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* stmt  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4654 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* verdict_stmt  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4660 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* verdict_map_stmt  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4666 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* verdict_map_expr  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4672 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* verdict_map_list_expr  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4678 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 432: /* verdict_map_list_member_expr  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4684 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* connlimit_stmt  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4690 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* counter_stmt  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4696 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* counter_stmt_alloc  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4702 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* log_stmt  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4708 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 439: /* log_stmt_alloc  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4714 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 446: /* limit_stmt  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4720 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* quota_unit  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4726 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 450: /* quota_stmt  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4732 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 455: /* reject_stmt  */
#line 637 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4738 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 456: /* reject_stmt_alloc  */
#line 637 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4744 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* nat_stmt  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4750 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* nat_stmt_alloc  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4756 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* tproxy_stmt  */
#line 642 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4762 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* synproxy_stmt  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4768 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* synproxy_stmt_alloc  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4774 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* synproxy_obj  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4780 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* primary_stmt_expr  */
#line 687 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4786 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* shift_stmt_expr  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4792 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* and_stmt_expr  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4798 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* exclusive_or_stmt_expr  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4804 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* inclusive_or_stmt_expr  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4810 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* basic_stmt_expr  */
#line 687 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4816 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* concat_stmt_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4822 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* map_stmt_expr_set  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4828 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* map_stmt_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4834 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* prefix_stmt_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4840 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* range_stmt_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4846 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* wildcard_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4852 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* multiton_stmt_expr  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4858 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* stmt_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4864 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* masq_stmt  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4870 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* masq_stmt_alloc  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4876 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* redir_stmt  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4882 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* redir_stmt_alloc  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4888 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 490: /* dup_stmt  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4894 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 491: /* fwd_stmt  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4900 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* queue_stmt  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4906 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 495: /* queue_stmt_alloc  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4912 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* set_elem_expr_stmt  */
#line 710 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4918 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* set_elem_expr_stmt_alloc  */
#line 710 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4924 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 502: /* set_stmt  */
#line 655 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4930 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 504: /* map_stmt  */
#line 658 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4936 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* meter_stmt  */
#line 660 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4942 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* flow_stmt_legacy_alloc  */
#line 660 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4948 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 509: /* meter_stmt_alloc  */
#line 660 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4954 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* match_stmt  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4960 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 511: /* variable_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4966 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 512: /* symbol_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4972 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* set_ref_expr  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4978 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 514: /* set_ref_symbol_expr  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4984 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 515: /* integer_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4990 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 516: /* primary_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4996 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* fib_expr  */
#line 792 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5002 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 521: /* osf_expr  */
#line 797 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5008 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* shift_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5014 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 524: /* and_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5020 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 525: /* exclusive_or_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5026 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 526: /* inclusive_or_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5032 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 527: /* basic_expr  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5038 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* concat_expr  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5044 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* prefix_rhs_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5050 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* range_rhs_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5056 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* multiton_rhs_expr  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5062 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* map_expr  */
#line 697 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5068 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* expr  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5074 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* set_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5080 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* set_list_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5086 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* set_list_member_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5092 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 537: /* meter_key_expr  */
#line 713 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5098 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* meter_key_expr_alloc  */
#line 713 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5104 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* set_elem_expr  */
#line 708 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5110 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* set_elem_expr_alloc  */
#line 708 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5116 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 545: /* set_lhs_expr  */
#line 708 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5122 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 546: /* set_rhs_expr  */
#line 708 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5128 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* initializer_expr  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5134 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 549: /* counter_obj  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5140 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* quota_obj  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5146 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 553: /* secmark_obj  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5152 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 557: /* timeout_states  */
#line 822 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5158 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 558: /* timeout_state  */
#line 822 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5164 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 561: /* ct_obj_alloc  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5170 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 563: /* limit_obj  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5176 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 564: /* relational_expr  */
#line 729 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5182 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 565: /* list_rhs_expr  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5188 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 566: /* rhs_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5194 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 567: /* shift_rhs_expr  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5200 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 568: /* and_rhs_expr  */
#line 723 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5206 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 569: /* exclusive_or_rhs_expr  */
#line 723 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5212 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 570: /* inclusive_or_rhs_expr  */
#line 723 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5218 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 571: /* basic_rhs_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5224 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 572: /* concat_rhs_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5230 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 574: /* boolean_expr  */
#line 812 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5236 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 575: /* keyword_expr  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5242 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 576: /* primary_rhs_expr  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5248 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 578: /* verdict_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5254 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 579: /* chain_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5260 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 580: /* meta_expr  */
#line 774 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5266 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 584: /* meta_stmt  */
#line 629 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5272 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 585: /* socket_expr  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5278 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 589: /* numgen_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5284 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 594: /* xfrm_expr  */
#line 826 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5290 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 595: /* hash_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5296 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 597: /* rt_expr  */
#line 784 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5302 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 599: /* ct_expr  */
#line 788 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5308 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 605: /* symbol_stmt_expr  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5314 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 606: /* list_stmt_expr  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5320 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 607: /* ct_stmt  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5326 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 608: /* payload_stmt  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5332 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 609: /* payload_expr  */
#line 733 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5338 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 610: /* payload_raw_expr  */
#line 733 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5344 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 612: /* eth_hdr_expr  */
#line 736 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5350 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 614: /* vlan_hdr_expr  */
#line 736 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5356 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 616: /* arp_hdr_expr  */
#line 739 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5362 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 618: /* ip_hdr_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5368 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 622: /* icmp_hdr_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5374 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 624: /* igmp_hdr_expr  */
#line 742 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5380 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 626: /* ip6_hdr_expr  */
#line 746 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5386 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 628: /* icmp6_hdr_expr  */
#line 746 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5392 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 630: /* auth_hdr_expr  */
#line 749 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5398 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 632: /* esp_hdr_expr  */
#line 749 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5404 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 634: /* comp_hdr_expr  */
#line 749 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5410 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 636: /* udp_hdr_expr  */
#line 752 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5416 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 638: /* udplite_hdr_expr  */
#line 752 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5422 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 640: /* tcp_hdr_expr  */
#line 807 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5428 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 644: /* dccp_hdr_expr  */
#line 755 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5434 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 646: /* sctp_hdr_expr  */
#line 755 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5440 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 648: /* th_hdr_expr  */
#line 758 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5446 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 650: /* exthdr_expr  */
#line 762 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5452 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 651: /* hbh_hdr_expr  */
#line 764 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5458 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 653: /* rt_hdr_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5464 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 655: /* rt0_hdr_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5470 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 657: /* rt2_hdr_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5476 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 659: /* rt4_hdr_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5482 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 661: /* frag_hdr_expr  */
#line 764 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5488 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 663: /* dst_hdr_expr  */
#line 764 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5494 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 665: /* mh_hdr_expr  */
#line 770 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5500 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 667: /* exthdr_exists_expr  */
#line 816 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5506 "parser_bison.c" /* yacc.c:1257  */
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

#line 5622 "parser_bison.c" /* yacc.c:1431  */
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
#line 5821 "parser_bison.c" /* yacc.c:1652  */
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
#line 5833 "parser_bison.c" /* yacc.c:1652  */
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
#line 5851 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 10:
#line 871 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 5862 "parser_bison.c" /* yacc.c:1652  */
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
#line 5877 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 12:
#line 889 "parser_bison.y" /* yacc.c:1652  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 5887 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 13:
#line 896 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 5893 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 14:
#line 897 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 5899 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 15:
#line 898 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 5905 "parser_bison.c" /* yacc.c:1652  */
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
#line 5927 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 17:
#line 919 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 18:
#line 920 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5939 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 19:
#line 921 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5945 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 20:
#line 922 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5951 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 21:
#line 923 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5957 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 22:
#line 924 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5963 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 23:
#line 925 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5969 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 24:
#line 926 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5975 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 25:
#line 927 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 26:
#line 928 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5987 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 27:
#line 929 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5993 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 28:
#line 930 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5999 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 29:
#line 931 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6005 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 30:
#line 932 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6011 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 31:
#line 933 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6017 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 32:
#line 937 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6025 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 33:
#line 942 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6035 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 34:
#line 948 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6043 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 35:
#line 953 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6054 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 36:
#line 960 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6062 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 37:
#line 964 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6070 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 38:
#line 969 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 39:
#line 976 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6090 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 40:
#line 982 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6098 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 41:
#line 987 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6108 "parser_bison.c" /* yacc.c:1652  */
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
#line 6121 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 43:
#line 1002 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6129 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 44:
#line 1006 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6137 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 45:
#line 1010 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6145 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 46:
#line 1014 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6153 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 47:
#line 1018 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 48:
#line 1022 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6169 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 49:
#line 1026 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6177 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 50:
#line 1030 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6185 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 51:
#line 1036 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6193 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 52:
#line 1042 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6201 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 53:
#line 1047 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6211 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 54:
#line 1053 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6219 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 55:
#line 1058 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6230 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 56:
#line 1066 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6240 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 57:
#line 1073 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6250 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 58:
#line 1079 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6258 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 59:
#line 1084 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6268 "parser_bison.c" /* yacc.c:1652  */
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
#line 6281 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 61:
#line 1099 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6289 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 62:
#line 1103 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6297 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 63:
#line 1107 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6305 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 64:
#line 1111 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6313 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 65:
#line 1115 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6321 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 66:
#line 1119 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6329 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 67:
#line 1123 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 68:
#line 1127 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6345 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 69:
#line 1133 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6353 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 70:
#line 1139 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6361 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 71:
#line 1143 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6369 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 72:
#line 1147 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6377 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 73:
#line 1151 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 74:
#line 1155 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 75:
#line 1159 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6401 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 76:
#line 1163 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 77:
#line 1167 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 78:
#line 1171 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 79:
#line 1175 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 80:
#line 1179 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 81:
#line 1184 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6451 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 82:
#line 1190 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6459 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 83:
#line 1194 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6467 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 84:
#line 1198 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6475 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 85:
#line 1202 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6483 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 86:
#line 1206 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6491 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 87:
#line 1210 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6499 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 88:
#line 1214 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6507 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 89:
#line 1218 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6515 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 90:
#line 1222 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6523 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 91:
#line 1226 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6531 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 92:
#line 1230 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6539 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 93:
#line 1236 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6547 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 94:
#line 1242 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6555 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 95:
#line 1246 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6563 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 96:
#line 1250 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6571 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 97:
#line 1254 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6579 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 98:
#line 1258 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6587 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 99:
#line 1262 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6595 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 100:
#line 1266 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 101:
#line 1270 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6611 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 102:
#line 1274 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6619 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 103:
#line 1278 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6627 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 104:
#line 1282 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6635 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 105:
#line 1286 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6643 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1290 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6651 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1294 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6659 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1298 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6667 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1302 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6675 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1306 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6683 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1310 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1314 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6699 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1318 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6707 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1322 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6715 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 115:
#line 1326 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6723 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 116:
#line 1330 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6731 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 117:
#line 1334 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6739 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 118:
#line 1338 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6747 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 119:
#line 1342 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6755 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1346 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6763 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1350 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6771 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1354 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1358 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6787 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1362 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6795 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1366 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6803 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1370 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6811 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1374 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_TIMEOUT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6819 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1378 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_EXPECT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6827 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1384 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6835 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1388 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1392 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 6851 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1396 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6859 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1400 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6867 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1404 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6875 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1410 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6883 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1414 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6891 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1418 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6899 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 138:
#line 1422 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6907 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 139:
#line 1426 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6915 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 140:
#line 1430 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6923 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 141:
#line 1434 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1440 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 6940 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1447 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6950 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1453 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6960 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 145:
#line 1461 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6970 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 146:
#line 1467 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6980 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 147:
#line 1475 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 6991 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 148:
#line 1483 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = NULL; }
#line 6997 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 149:
#line 1484 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7003 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 150:
#line 1487 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 7009 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 151:
#line 1488 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 7015 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 152:
#line 1489 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 7021 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 153:
#line 1490 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 7027 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1491 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 7033 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1492 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 7039 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1493 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 7045 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 157:
#line 1494 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 7051 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 158:
#line 1497 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 7057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1501 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 7063 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1502 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7069 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1503 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7075 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1507 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 7085 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 164:
#line 1515 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 7094 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1522 "parser_bison.y" /* yacc.c:1652  */
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
#line 7110 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 166:
#line 1535 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 7116 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1542 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7129 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1553 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1563 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7153 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 173:
#line 1574 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7165 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 174:
#line 1584 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7178 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 175:
#line 1595 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7191 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 176:
#line 1604 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 177:
#line 1613 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7217 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 178:
#line 1622 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7230 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 179:
#line 1633 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 180:
#line 1644 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7256 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 181:
#line 1655 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7269 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 182:
#line 1666 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 7278 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 183:
#line 1672 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7284 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 189:
#line 1679 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 7293 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 190:
#line 1686 "parser_bison.y" /* yacc.c:1652  */
    {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 7308 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 191:
#line 1697 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 7321 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 192:
#line 1709 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7329 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 193:
#line 1714 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7335 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 196:
#line 1718 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7344 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 197:
#line 1723 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7354 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 198:
#line 1729 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 199:
#line 1734 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7372 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 200:
#line 1739 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 201:
#line 1744 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->stmt = counter_stmt_alloc(&(yyloc));
				(yyval.set) = (yyvsp[-2].set);
			}
#line 7390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 202:
#line 1749 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 203:
#line 1754 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 7408 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 207:
#line 1766 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 209:
#line 1772 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 7422 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 210:
#line 1773 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 7428 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 211:
#line 1774 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 7434 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 212:
#line 1775 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_EVAL; }
#line 7440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 213:
#line 1779 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7448 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 214:
#line 1784 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7454 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 217:
#line 1788 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7463 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 218:
#line 1795 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7475 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 219:
#line 1805 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 7488 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 220:
#line 1816 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7501 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 221:
#line 1827 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				datatype_set((yyvsp[-6].set)->key, (yyvsp[-4].expr)->dtype);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 7515 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 222:
#line 1839 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7526 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 223:
#line 1848 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7537 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 224:
#line 1857 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7548 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 225:
#line 1866 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_SECMARK;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 226:
#line 1873 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 227:
#line 1878 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 229:
#line 1886 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 7585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 230:
#line 1890 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 7593 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 231:
#line 1895 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 7599 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 232:
#line 1896 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 7605 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 233:
#line 1900 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 7613 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 234:
#line 1905 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 7619 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 237:
#line 1909 "parser_bison.y" /* yacc.c:1652  */
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
#line 7637 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 238:
#line 1923 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 7645 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 239:
#line 1927 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 7653 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 240:
#line 1933 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7662 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 241:
#line 1940 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7671 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 242:
#line 1945 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7680 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 244:
#line 1953 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 245:
#line 1962 "parser_bison.y" /* yacc.c:1652  */
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
#line 7707 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 246:
#line 1974 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 7716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 248:
#line 1982 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 7729 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 249:
#line 1993 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 7737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 250:
#line 1998 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7743 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 253:
#line 2002 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7751 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 254:
#line 2007 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7757 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 257:
#line 2011 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7765 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 258:
#line 2016 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7771 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 261:
#line 2020 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 262:
#line 2026 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[(-1) - (0)].obj);
				init_list_head(&(yyval.obj)->ct_timeout.timeout_list);
			}
#line 7788 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 265:
#line 2033 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7796 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 266:
#line 2038 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 269:
#line 2042 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7810 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 270:
#line 2047 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7816 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 273:
#line 2051 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7824 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 274:
#line 2056 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7830 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 277:
#line 2060 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7838 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 278:
#line 2065 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7844 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 281:
#line 2069 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 282:
#line 2074 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 283:
#line 2075 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("mark"); }
#line 7864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 284:
#line 2076 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("dscp"); }
#line 7870 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 285:
#line 2077 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("ecn"); }
#line 7876 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 286:
#line 2078 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("classid"); }
#line 7882 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 287:
#line 2082 "parser_bison.y" /* yacc.c:1652  */
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
#line 7914 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 288:
#line 2112 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 7923 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 289:
#line 2119 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.string) = strdup("out");
			}
#line 7931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 291:
#line 2126 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 7945 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 292:
#line 2136 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				datatype_set((yyvsp[0].expr)->sym->expr, &priority_type);
				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 7957 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 293:
#line 2144 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 7972 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 294:
#line 2155 "parser_bison.y" /* yacc.c:1652  */
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
#line 7989 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 295:
#line 2168 "parser_bison.y" /* yacc.c:1652  */
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
#line 8006 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 296:
#line 2182 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = (yyvsp[0].val); }
#line 8012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 297:
#line 2183 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = -(yyvsp[0].val); }
#line 8018 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 298:
#line 2187 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 8034 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 299:
#line 2199 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8042 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 300:
#line 2202 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = NULL; }
#line 8048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 301:
#line 2206 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 8056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 302:
#line 2212 "parser_bison.y" /* yacc.c:1652  */
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
#line 8071 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 303:
#line 2225 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 304:
#line 2230 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 8091 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 305:
#line 2238 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_ACCEPT; }
#line 8097 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 306:
#line 2239 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_DROP;   }
#line 8103 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 311:
#line 2251 "parser_bison.y" /* yacc.c:1652  */
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
#line 8120 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 312:
#line 2265 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8126 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 314:
#line 2269 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8132 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 315:
#line 2270 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 8138 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 316:
#line 2271 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_INET; }
#line 8144 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 317:
#line 2272 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_ARP; }
#line 8150 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 318:
#line 2273 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 8156 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 319:
#line 2274 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 8162 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 320:
#line 2278 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 8173 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 321:
#line 2287 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 8184 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 322:
#line 2296 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 8194 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 323:
#line 2304 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 8204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 324:
#line 2312 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 8214 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 325:
#line 2320 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 8224 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 326:
#line 2328 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 8234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 327:
#line 2336 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 8244 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 328:
#line 2344 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 8254 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 329:
#line 2352 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8264 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 330:
#line 2360 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 8274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 331:
#line 2368 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 8284 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 332:
#line 2376 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8294 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 333:
#line 2384 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 8304 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 334:
#line 2392 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8314 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 335:
#line 2400 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 8324 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 336:
#line 2408 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 8334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 337:
#line 2416 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 8342 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 338:
#line 2420 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8351 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 339:
#line 2425 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 340:
#line 2433 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8372 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 341:
#line 2440 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 342:
#line 2447 "parser_bison.y" /* yacc.c:1652  */
    {
				if (strlen((yyvsp[0].string)) > NFTNL_UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed",
							 NFTNL_UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 8395 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 343:
#line 2459 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 8404 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 344:
#line 2464 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 8413 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 345:
#line 2471 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 8421 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 346:
#line 2475 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 8429 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 347:
#line 2481 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 8443 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 348:
#line 2493 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 8453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 349:
#line 2499 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 8462 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 373:
#line 2533 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8470 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 374:
#line 2537 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8478 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 375:
#line 2543 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8486 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 376:
#line 2549 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8495 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 378:
#line 2557 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 379:
#line 2562 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 381:
#line 2570 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 8521 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 382:
#line 2576 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[0].val);
			}
#line 8530 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 383:
#line 2581 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[0].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 8540 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 386:
#line 2592 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 8548 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 387:
#line 2596 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8558 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 388:
#line 2604 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8566 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 390:
#line 2611 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 8574 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 391:
#line 2615 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 8582 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 394:
#line 2625 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 8590 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 395:
#line 2631 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8598 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 397:
#line 2638 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 8607 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 398:
#line 2643 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 8616 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 399:
#line 2648 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 8625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 400:
#line 2653 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 8634 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 401:
#line 2658 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 8643 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 402:
#line 2663 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 8651 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 403:
#line 2669 "parser_bison.y" /* yacc.c:1652  */
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
#line 8683 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 404:
#line 2699 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 8691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 405:
#line 2703 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 8699 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 406:
#line 2707 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 8707 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 407:
#line 2711 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 8715 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 408:
#line 2715 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 8723 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 409:
#line 2721 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8731 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 411:
#line 2728 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 8739 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 412:
#line 2732 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 8747 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 413:
#line 2738 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 8760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 414:
#line 2747 "parser_bison.y" /* yacc.c:1652  */
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
#line 8783 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 415:
#line 2766 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 416:
#line 2773 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 8799 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 417:
#line 2774 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8805 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 418:
#line 2775 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8811 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 419:
#line 2778 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("bytes"); }
#line 8817 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 420:
#line 2779 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 8823 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 421:
#line 2782 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8829 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 422:
#line 2784 "parser_bison.y" /* yacc.c:1652  */
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
#line 8846 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 423:
#line 2799 "parser_bison.y" /* yacc.c:1652  */
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
#line 8866 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 424:
#line 2815 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8876 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 425:
#line 2822 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 8882 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 426:
#line 2823 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 427:
#line 2824 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8894 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 428:
#line 2827 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8900 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 429:
#line 2828 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 8906 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 430:
#line 2831 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8912 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 431:
#line 2832 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 8918 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 432:
#line 2834 "parser_bison.y" /* yacc.c:1652  */
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
#line 8935 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 433:
#line 2848 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL; }
#line 8941 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 434:
#line 2849 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60; }
#line 8947 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 435:
#line 2850 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 8953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 436:
#line 2851 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 8959 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 437:
#line 2852 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 8965 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 439:
#line 2859 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 8973 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 440:
#line 2865 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 8982 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 441:
#line 2870 "parser_bison.y" /* yacc.c:1652  */
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
#line 8997 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 442:
#line 2881 "parser_bison.y" /* yacc.c:1652  */
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
#line 9012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 443:
#line 2892 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpx_code_type);
				xfree((yyvsp[0].string));
			}
#line 9026 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 444:
#line 2902 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 9034 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 446:
#line 2910 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 9040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 447:
#line 2911 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 9046 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 448:
#line 2915 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 9056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 449:
#line 2921 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 9066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 450:
#line 2927 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9076 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 451:
#line 2933 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9087 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 452:
#line 2940 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9098 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 453:
#line 2947 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9108 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 456:
#line 2959 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 9116 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 457:
#line 2963 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9126 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 458:
#line 2971 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9134 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 460:
#line 2978 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 9143 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 461:
#line 2983 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 9152 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 462:
#line 2988 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 9160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 463:
#line 2992 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 9168 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 464:
#line 2998 "parser_bison.y" /* yacc.c:1652  */
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
#line 9188 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 465:
#line 3014 "parser_bison.y" /* yacc.c:1652  */
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
#line 9208 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 466:
#line 3032 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 9217 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 467:
#line 3038 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9223 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 468:
#line 3040 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 9231 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 469:
#line 3045 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9237 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 470:
#line 3047 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 9245 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 471:
#line 3052 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9251 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 472:
#line 3053 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 473:
#line 3054 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9263 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 474:
#line 3055 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9269 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 475:
#line 3056 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9275 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 476:
#line 3057 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9281 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 477:
#line 3058 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9287 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 478:
#line 3059 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9293 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 479:
#line 3060 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9299 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 480:
#line 3061 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9305 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 481:
#line 3062 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9311 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 482:
#line 3063 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9317 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 483:
#line 3064 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 9323 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 485:
#line 3069 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9331 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 486:
#line 3073 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9339 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 488:
#line 3080 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9347 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 490:
#line 3087 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9355 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 492:
#line 3094 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 495:
#line 3104 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 9376 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 498:
#line 3119 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 499:
#line 3122 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 500:
#line 3126 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 9398 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 501:
#line 3132 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9406 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 502:
#line 3138 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 9419 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 509:
#line 3159 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 9427 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 510:
#line 3163 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 9435 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 511:
#line 3167 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 9444 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 512:
#line 3172 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 513:
#line 3177 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9462 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 514:
#line 3182 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9472 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 515:
#line 3188 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9480 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 516:
#line 3192 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9488 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 517:
#line 3196 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9496 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 518:
#line 3200 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.type_flags = STMT_NAT_F_CONCAT;
			}
#line 9506 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 519:
#line 3206 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags = STMT_NAT_F_INTERVAL;
			}
#line 9516 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 520:
#line 3212 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags = STMT_NAT_F_INTERVAL;
			}
#line 9525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 521:
#line 3217 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX |
						STMT_NAT_F_INTERVAL;
				(yyvsp[-4].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 9538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 522:
#line 3226 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX |
						STMT_NAT_F_INTERVAL;
				(yyvsp[-3].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 9550 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 525:
#line 3239 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 9556 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 526:
#line 3243 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9564 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 527:
#line 3247 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9573 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 528:
#line 3252 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9581 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 531:
#line 3261 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 9587 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 532:
#line 3265 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9595 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 533:
#line 3269 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 9603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 534:
#line 3273 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9611 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 535:
#line 3277 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9620 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 536:
#line 3282 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 9629 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 537:
#line 3289 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 9638 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 538:
#line 3294 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 9648 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 539:
#line 3302 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 9657 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 540:
#line 3307 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 9668 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 542:
#line 3317 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 543:
#line 3322 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 9682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 544:
#line 3323 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 9688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 545:
#line 3324 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 9694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 548:
#line 3332 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 9702 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 549:
#line 3338 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9710 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 551:
#line 3345 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 9719 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 552:
#line 3350 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 9727 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 554:
#line 3357 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9735 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 555:
#line 3362 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 9741 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 556:
#line 3363 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 9747 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 559:
#line 3371 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 9755 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 560:
#line 3377 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 9766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 561:
#line 3384 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 9777 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 562:
#line 3391 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				(yyval.stmt)->set.stmt = (yyvsp[-1].stmt);
			}
#line 9789 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 563:
#line 3400 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 9795 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 564:
#line 3401 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 9801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 565:
#line 3402 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 9807 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 566:
#line 3406 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 9819 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 567:
#line 3414 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.stmt = (yyvsp[-3].stmt);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
			}
#line 9832 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 568:
#line 3425 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 9843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 569:
#line 3431 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 9849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 570:
#line 3435 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 9857 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 571:
#line 3441 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9865 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 573:
#line 3448 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 9873 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 574:
#line 3454 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 9886 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 575:
#line 3463 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 9899 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 576:
#line 3474 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 9907 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 577:
#line 3480 "parser_bison.y" /* yacc.c:1652  */
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
#line 9935 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 579:
#line 3507 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9946 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 582:
#line 3520 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9957 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 583:
#line 3529 "parser_bison.y" /* yacc.c:1652  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 9970 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 584:
#line 3539 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9976 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 585:
#line 3540 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9982 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 586:
#line 3541 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9988 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 587:
#line 3542 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9994 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 588:
#line 3543 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 589:
#line 3544 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10006 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 590:
#line 3545 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 591:
#line 3546 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10018 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 592:
#line 3547 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 593:
#line 3548 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10030 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 594:
#line 3549 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10036 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 595:
#line 3550 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10042 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 596:
#line 3551 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 597:
#line 3552 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10054 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 598:
#line 3553 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 10060 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 599:
#line 3557 "parser_bison.y" /* yacc.c:1652  */
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
#line 10085 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 600:
#line 3579 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 10091 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 601:
#line 3580 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 10097 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 602:
#line 3581 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 10103 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 603:
#line 3584 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 10109 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 604:
#line 3585 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 10115 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 605:
#line 3586 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 10121 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 606:
#line 3587 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 10127 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 607:
#line 3588 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 10133 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 608:
#line 3592 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 610:
#line 3599 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), NFT_OSF_F_VERSION);
			}
#line 10149 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 611:
#line 3603 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 10157 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 612:
#line 3609 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 10165 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 613:
#line 3613 "parser_bison.y" /* yacc.c:1652  */
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
#line 10181 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 615:
#line 3628 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10189 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 616:
#line 3632 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10197 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 618:
#line 3639 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10205 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 620:
#line 3646 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 622:
#line 3653 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10221 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 625:
#line 3663 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 626:
#line 3674 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 10242 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 627:
#line 3680 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10250 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 630:
#line 3690 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10258 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 634:
#line 3701 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10267 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 635:
#line 3708 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10276 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 636:
#line 3713 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 638:
#line 3721 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10293 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 639:
#line 3725 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10301 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 640:
#line 3729 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 10309 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 642:
#line 3736 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10318 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 643:
#line 3743 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 646:
#line 3753 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 647:
#line 3759 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 10342 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 649:
#line 3766 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 10350 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 650:
#line 3770 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 10358 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 651:
#line 3774 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 10366 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 652:
#line 3780 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 10374 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 654:
#line 3787 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 10382 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 655:
#line 3791 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 10390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 656:
#line 3795 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->stmt = counter_stmt_alloc(&(yyloc));
			}
#line 10398 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 657:
#line 3799 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *stmt;

				stmt = counter_stmt_alloc(&(yyloc));
				stmt->counter.packets = (yyvsp[-2].val);
				stmt->counter.bytes = (yyvsp[0].val);
				(yyvsp[-5].expr)->stmt = stmt;
			}
#line 10411 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 658:
#line 3808 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 10419 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 665:
#line 3826 "parser_bison.y" /* yacc.c:1652  */
    {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 10431 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 666:
#line 3836 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 10440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 667:
#line 3843 "parser_bison.y" /* yacc.c:1652  */
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
#line 10462 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 668:
#line 3863 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 10471 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 669:
#line 3870 "parser_bison.y" /* yacc.c:1652  */
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
#line 10489 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 670:
#line 3886 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 10498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 671:
#line 3892 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 10504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 672:
#line 3893 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 10510 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 673:
#line 3894 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 10516 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 674:
#line 3897 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_TCP; }
#line 10522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 675:
#line 3898 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_UDP; }
#line 10528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 676:
#line 3902 "parser_bison.y" /* yacc.c:1652  */
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
#line 10548 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 677:
#line 3918 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 10556 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 678:
#line 3924 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 10566 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 679:
#line 3930 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 10575 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 680:
#line 3938 "parser_bison.y" /* yacc.c:1652  */
    {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 10590 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 681:
#line 3951 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 10602 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 682:
#line 3959 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;

				ct = &(yyvsp[-6].obj)->ct_timeout;
				list_splice_tail((yyvsp[-2].list), &ct->timeout_list);
				xfree((yyvsp[-2].list));
			}
#line 10614 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 683:
#line 3967 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 10622 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 684:
#line 3973 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 10630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 685:
#line 3977 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 10638 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 686:
#line 3981 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 10646 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 687:
#line 3985 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 10654 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 688:
#line 3989 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 10662 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 689:
#line 3995 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 10670 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 690:
#line 4001 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;

				limit = &(yyvsp[-6].obj)->limit;
				limit->rate	= (yyvsp[-3].val);
				limit->unit	= (yyvsp[-1].val);
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-4].val);
			}
#line 10685 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 691:
#line 4012 "parser_bison.y" /* yacc.c:1652  */
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
#line 10708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 692:
#line 4033 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 10717 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 693:
#line 4040 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 10725 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 694:
#line 4044 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 10733 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 695:
#line 4048 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10741 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 696:
#line 4054 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10751 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 697:
#line 4060 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 698:
#line 4067 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10767 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 699:
#line 4068 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10773 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 700:
#line 4069 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 701:
#line 4070 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10785 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 703:
#line 4075 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 704:
#line 4079 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 706:
#line 4086 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 708:
#line 4093 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10817 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 710:
#line 4100 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10825 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 714:
#line 4111 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10838 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 715:
#line 4120 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10851 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 716:
#line 4130 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = true; }
#line 10857 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 717:
#line 4131 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = false; }
#line 10863 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 718:
#line 4135 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 10873 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 719:
#line 4142 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 10879 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 720:
#line 4143 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 10885 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 721:
#line 4144 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 10891 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 722:
#line 4145 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 10897 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 723:
#line 4146 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 10903 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 724:
#line 4147 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 10909 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 725:
#line 4148 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 10915 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 726:
#line 4149 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 10921 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 727:
#line 4150 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 10927 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 728:
#line 4151 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 10933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 729:
#line 4152 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 10939 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 730:
#line 4153 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 10945 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 731:
#line 4156 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10951 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 732:
#line 4157 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10957 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 733:
#line 4158 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10963 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 734:
#line 4159 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10969 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 735:
#line 4161 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10980 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 736:
#line 4168 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10991 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 737:
#line 4175 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11002 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 738:
#line 4182 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11013 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 739:
#line 4189 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 740:
#line 4196 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11035 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 741:
#line 4203 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11046 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 742:
#line 4210 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 743:
#line 4217 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11068 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 744:
#line 4224 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11079 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 745:
#line 4231 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11090 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 746:
#line 4238 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 747:
#line 4244 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 11107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 748:
#line 4247 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_EQ; }
#line 11113 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 749:
#line 4248 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_NEQ; }
#line 11119 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 750:
#line 4249 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LT; }
#line 11125 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 751:
#line 4250 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GT; }
#line 11131 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 752:
#line 4251 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GTE; }
#line 11137 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 753:
#line 4252 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LTE; }
#line 11143 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 754:
#line 4256 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 11151 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 755:
#line 4260 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 11159 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 756:
#line 4264 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 11167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 757:
#line 4268 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 11175 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 758:
#line 4272 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 11183 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 759:
#line 4276 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 11191 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 761:
#line 4283 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 11203 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 762:
#line 4293 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11211 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 763:
#line 4297 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11219 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 764:
#line 4301 "parser_bison.y" /* yacc.c:1652  */
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
#line 11237 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 767:
#line 4320 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_LEN; }
#line 11243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 768:
#line 4321 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 11249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 769:
#line 4322 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 11255 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 770:
#line 4323 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 11261 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 771:
#line 4324 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECMARK; }
#line 11267 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 772:
#line 4327 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_MARK; }
#line 11273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 773:
#line 4328 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIF; }
#line 11279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 774:
#line 4329 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 11285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 775:
#line 4330 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 11291 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 776:
#line 4331 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIF; }
#line 11297 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 777:
#line 4332 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 11303 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 778:
#line 4333 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 11309 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 779:
#line 4334 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKUID; }
#line 11315 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 780:
#line 4335 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKGID; }
#line 11321 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 781:
#line 4336 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 11327 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 782:
#line 4337 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 11333 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 783:
#line 4338 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 11339 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 784:
#line 4339 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 11345 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 785:
#line 4340 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 11351 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 786:
#line 4341 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 11357 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 787:
#line 4342 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 11363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 788:
#line 4343 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CPU; }
#line 11369 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 789:
#line 4344 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 11375 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 790:
#line 4345 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 11381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 791:
#line 4346 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 11387 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 792:
#line 4347 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECPATH; }
#line 11393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 793:
#line 4348 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_NS; }
#line 11399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 794:
#line 4349 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_DAY; }
#line 11405 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 795:
#line 4350 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_HOUR; }
#line 11411 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 796:
#line 4354 "parser_bison.y" /* yacc.c:1652  */
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
#line 11435 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 797:
#line 4374 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 11443 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 798:
#line 4378 "parser_bison.y" /* yacc.c:1652  */
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
#line 11461 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 799:
#line 4392 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 11469 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 800:
#line 4396 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 11477 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 801:
#line 4400 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 11485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 802:
#line 4406 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11493 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 803:
#line 4411 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 11499 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 804:
#line 4412 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_MARK; }
#line 11505 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 805:
#line 4415 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 11511 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 806:
#line 4416 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 11517 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 807:
#line 4419 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 11523 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 808:
#line 4420 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 11529 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 809:
#line 4424 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 11537 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 810:
#line 4429 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 11543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 811:
#line 4430 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 11549 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 812:
#line 4433 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_IN; }
#line 11555 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 813:
#line 4434 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_OUT; }
#line 11561 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 814:
#line 4437 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 11567 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 815:
#line 4438 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 11573 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 816:
#line 4441 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 11579 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 817:
#line 4442 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 11585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 818:
#line 4446 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-1].val) > 255) {
					erec_queue(error(&(yylsp[-1]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 11597 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 819:
#line 4454 "parser_bison.y" /* yacc.c:1652  */
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
#line 11626 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 820:
#line 4481 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 11635 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 821:
#line 4486 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 11644 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 822:
#line 4491 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 11652 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 823:
#line 4496 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 11658 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 824:
#line 4497 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 11664 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 825:
#line 4501 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 11672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 826:
#line 4505 "parser_bison.y" /* yacc.c:1652  */
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
#line 11694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 827:
#line 4524 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 11700 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 828:
#line 4525 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 11706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 829:
#line 4526 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 11712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 830:
#line 4527 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_XFRM; }
#line 11718 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 831:
#line 4531 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1);
			}
#line 11726 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 832:
#line 4535 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 11734 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 833:
#line 4539 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 11742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 834:
#line 4544 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 11748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 835:
#line 4545 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 11754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 836:
#line 4548 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 11760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 837:
#line 4549 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 11766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 838:
#line 4550 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_MARK; }
#line 11772 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 839:
#line 4551 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATE; }
#line 11778 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 840:
#line 4552 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 11784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 841:
#line 4553 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 11790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 842:
#line 4554 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 11796 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 843:
#line 4555 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 11802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 844:
#line 4556 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 11808 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 845:
#line 4557 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 11814 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 846:
#line 4558 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 11820 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 847:
#line 4559 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 11826 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 848:
#line 4560 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 11832 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 849:
#line 4561 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 11838 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 850:
#line 4562 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SECMARK; }
#line 11844 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 851:
#line 4563 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ID; }
#line 11850 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 853:
#line 4567 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 11856 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 854:
#line 4568 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 11862 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 855:
#line 4569 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 11868 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 856:
#line 4570 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 11874 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 857:
#line 4571 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 11880 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 858:
#line 4572 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 11886 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 860:
#line 4576 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP; }
#line 11892 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 861:
#line 4577 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP; }
#line 11898 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 862:
#line 4578 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP6; }
#line 11904 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 863:
#line 4579 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP6; }
#line 11910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 864:
#line 4582 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 11916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 865:
#line 4583 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 11922 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 866:
#line 4584 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 11928 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 867:
#line 4585 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 11934 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 870:
#line 4593 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11944 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 871:
#line 4599 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11954 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 872:
#line 4607 "parser_bison.y" /* yacc.c:1652  */
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
#line 11971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 873:
#line 4620 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);

			}
#line 11982 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 874:
#line 4627 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 11992 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 875:
#line 4633 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 12000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 876:
#line 4639 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12011 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 895:
#line 4668 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 12022 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 896:
#line 4676 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 12028 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 897:
#line 4677 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 12034 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 898:
#line 4678 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 12040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 899:
#line 4682 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 12048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 900:
#line 4687 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 12054 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 901:
#line 4688 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 12060 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 902:
#line 4689 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 12066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 903:
#line 4693 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 12074 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 904:
#line 4698 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_VID; }
#line 12080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 905:
#line 4699 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_CFI; }
#line 12086 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 906:
#line 4700 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_PCP; }
#line 12092 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 907:
#line 4701 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 12098 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 908:
#line 4705 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 12106 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 909:
#line 4710 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HRD; }
#line 12112 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 910:
#line 4711 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PRO; }
#line 12118 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 911:
#line 4712 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HLN; }
#line 12124 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 912:
#line 4713 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PLN; }
#line 12130 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 913:
#line 4714 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_OP; }
#line 12136 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 914:
#line 4715 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 12142 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 915:
#line 4716 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 12148 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 916:
#line 4717 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_IP; }
#line 12154 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 917:
#line 4718 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_IP; }
#line 12160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 918:
#line 4722 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 12168 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 919:
#line 4726 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val), 0);
			}
#line 12176 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 920:
#line 4730 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[0].val), IPOPT_FIELD_TYPE, 0);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 12185 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 921:
#line 4736 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_VERSION; }
#line 12191 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 922:
#line 4737 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 12197 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 923:
#line 4738 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DSCP; }
#line 12203 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 924:
#line 4739 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ECN; }
#line 12209 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 925:
#line 4740 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 12215 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 926:
#line 4741 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ID; }
#line 12221 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 927:
#line 4742 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 12227 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 928:
#line 4743 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_TTL; }
#line 12233 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 929:
#line 4744 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 12239 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 930:
#line 4745 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 12245 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 931:
#line 4746 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_SADDR; }
#line 12251 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 932:
#line 4747 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DADDR; }
#line 12257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 933:
#line 4750 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_LSRR; }
#line 12263 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 934:
#line 4751 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RR; }
#line 12269 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 935:
#line 4752 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_SSRR; }
#line 12275 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 936:
#line 4753 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RA; }
#line 12281 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 937:
#line 4756 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 12287 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 938:
#line 4757 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 12293 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 939:
#line 4758 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 12299 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 940:
#line 4759 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_PTR; }
#line 12305 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 941:
#line 4760 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 12311 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 942:
#line 4764 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 12319 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 943:
#line 4769 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 12325 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 944:
#line 4770 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 12331 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 945:
#line 4771 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 12337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 946:
#line 4772 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_ID; }
#line 12343 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 947:
#line 4773 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 12349 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 948:
#line 4774 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 12355 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 949:
#line 4775 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 12361 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 950:
#line 4779 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[0].val));
			}
#line 12369 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 951:
#line 4784 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_TYPE; }
#line 12375 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 952:
#line 4785 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 12381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 953:
#line 4786 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_MRT; }
#line 12387 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 954:
#line 4787 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_GROUP; }
#line 12393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 955:
#line 4791 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 12401 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 956:
#line 4796 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 12407 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 957:
#line 4797 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 12413 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 958:
#line 4798 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_ECN; }
#line 12419 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 959:
#line 4799 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 12425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 960:
#line 4800 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 12431 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 961:
#line 4801 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 12437 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 962:
#line 4802 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 12443 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 963:
#line 4803 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 12449 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 964:
#line 4804 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 12455 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 965:
#line 4807 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 12463 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 966:
#line 4812 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 12469 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 967:
#line 4813 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 12475 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 968:
#line 4814 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 12481 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 969:
#line 4815 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 12487 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 970:
#line 4816 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 12493 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 971:
#line 4817 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 12499 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 972:
#line 4818 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 12505 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 973:
#line 4819 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 12511 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 974:
#line 4823 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 12519 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 975:
#line 4828 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 12525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 976:
#line 4829 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 12531 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 977:
#line 4830 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 12537 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 978:
#line 4831 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SPI; }
#line 12543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 979:
#line 4832 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 12549 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 980:
#line 4836 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 12557 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 981:
#line 4841 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SPI; }
#line 12563 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 982:
#line 4842 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 12569 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 983:
#line 4846 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 12577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 984:
#line 4851 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 12583 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 985:
#line 4852 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 12589 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 986:
#line 4853 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_CPI; }
#line 12595 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 987:
#line 4857 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 12603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 988:
#line 4862 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 12609 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 989:
#line 4863 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 12615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 990:
#line 4864 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 12621 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 991:
#line 4865 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 12627 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 992:
#line 4869 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 12635 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 993:
#line 4874 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 12641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 994:
#line 4875 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 12647 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 995:
#line 4876 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 12653 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 996:
#line 4877 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 12659 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 997:
#line 4881 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 12667 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 998:
#line 4885 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 12675 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 999:
#line 4889 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 12684 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1000:
#line 4895 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 12690 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1001:
#line 4896 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 12696 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1002:
#line 4897 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 12702 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1003:
#line 4898 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 12708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1004:
#line 4899 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 12714 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1005:
#line 4900 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 12720 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1006:
#line 4901 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 12726 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1007:
#line 4902 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 12732 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1008:
#line 4903 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 12738 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1009:
#line 4904 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 12744 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1010:
#line 4907 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 12750 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1011:
#line 4908 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 12756 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1012:
#line 4909 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 12762 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1013:
#line 4910 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 12768 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1014:
#line 4911 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 12774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1015:
#line 4912 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 12780 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1016:
#line 4913 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 12786 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1017:
#line 4914 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 12792 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1018:
#line 4915 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 12798 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1019:
#line 4916 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 12804 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1020:
#line 4917 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 12810 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1021:
#line 4918 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 12816 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1022:
#line 4921 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 12822 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1023:
#line 4922 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 12828 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1024:
#line 4923 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 12834 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1025:
#line 4924 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 12840 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1026:
#line 4925 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 12846 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1027:
#line 4926 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 12852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1028:
#line 4927 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 12858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1029:
#line 4928 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 12864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1030:
#line 4932 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 12872 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1031:
#line 4937 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 12878 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1032:
#line 4938 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 12884 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1033:
#line 4939 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 12890 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1034:
#line 4943 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 12898 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1035:
#line 4948 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 12904 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1036:
#line 4949 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 12910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1037:
#line 4950 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 12916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1038:
#line 4951 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 12922 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1039:
#line 4955 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[0].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 12932 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1040:
#line 4962 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_SPORT; }
#line 12938 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1041:
#line 4963 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_DPORT; }
#line 12944 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1050:
#line 4977 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 12952 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1051:
#line 4982 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 12958 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1052:
#line 4983 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 12964 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1053:
#line 4987 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 12972 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1054:
#line 4992 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 12978 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1055:
#line 4993 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 12984 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1056:
#line 4994 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_TYPE; }
#line 12990 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1057:
#line 4995 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 12996 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1058:
#line 4999 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 13004 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1059:
#line 5005 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 13012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1060:
#line 5011 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 13020 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1061:
#line 5016 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 13026 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1062:
#line 5020 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 13034 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1063:
#line 5025 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 13040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1064:
#line 5026 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 13046 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1065:
#line 5027 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_TAG; }
#line 13052 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1066:
#line 5029 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 13060 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1067:
#line 5035 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 13068 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1068:
#line 5040 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 13074 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1069:
#line 5041 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 13080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1070:
#line 5042 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 13086 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1071:
#line 5043 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 13092 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1072:
#line 5044 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 13098 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1073:
#line 5045 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_ID; }
#line 13104 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1074:
#line 5049 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 13112 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1075:
#line 5054 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 13118 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1076:
#line 5055 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 13124 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1077:
#line 5059 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 13132 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1078:
#line 5064 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 13138 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1079:
#line 5065 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 13144 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1080:
#line 5066 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_TYPE; }
#line 13150 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1081:
#line 5067 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 13156 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1082:
#line 5068 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 13162 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1083:
#line 5072 "parser_bison.y" /* yacc.c:1652  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 13178 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1084:
#line 5085 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 13184 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1085:
#line 5086 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 13190 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1086:
#line 5087 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 13196 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1087:
#line 5088 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 13202 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1088:
#line 5089 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_MH; }
#line 13208 "parser_bison.c" /* yacc.c:1652  */
    break;


#line 13212 "parser_bison.c" /* yacc.c:1652  */
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
#line 5092 "parser_bison.y" /* yacc.c:1918  */

