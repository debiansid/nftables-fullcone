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

#line 210 "parser_bison.c" /* yacc.c:337  */
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
    WILDCARD = 288,
    TPROXY = 289,
    OSF = 290,
    SYNPROXY = 291,
    MSS = 292,
    WSCALE = 293,
    SACKPERM = 294,
    TYPEOF = 295,
    HOOK = 296,
    DEVICE = 297,
    DEVICES = 298,
    TABLE = 299,
    TABLES = 300,
    CHAIN = 301,
    CHAINS = 302,
    RULE = 303,
    RULES = 304,
    SETS = 305,
    SET = 306,
    ELEMENT = 307,
    MAP = 308,
    MAPS = 309,
    FLOWTABLE = 310,
    HANDLE = 311,
    RULESET = 312,
    TRACE = 313,
    INET = 314,
    NETDEV = 315,
    ADD = 316,
    UPDATE = 317,
    REPLACE = 318,
    CREATE = 319,
    INSERT = 320,
    DELETE = 321,
    GET = 322,
    LIST = 323,
    RESET = 324,
    FLUSH = 325,
    RENAME = 326,
    DESCRIBE = 327,
    IMPORT = 328,
    EXPORT = 329,
    MONITOR = 330,
    ALL = 331,
    ACCEPT = 332,
    DROP = 333,
    CONTINUE = 334,
    JUMP = 335,
    GOTO = 336,
    RETURN = 337,
    TO = 338,
    CONSTANT = 339,
    INTERVAL = 340,
    DYNAMIC = 341,
    AUTOMERGE = 342,
    TIMEOUT = 343,
    GC_INTERVAL = 344,
    ELEMENTS = 345,
    EXPIRES = 346,
    POLICY = 347,
    MEMORY = 348,
    PERFORMANCE = 349,
    SIZE = 350,
    FLOW = 351,
    OFFLOAD = 352,
    METER = 353,
    METERS = 354,
    FLOWTABLES = 355,
    NUM = 356,
    STRING = 357,
    QUOTED_STRING = 358,
    ASTERISK_STRING = 359,
    LL_HDR = 360,
    NETWORK_HDR = 361,
    TRANSPORT_HDR = 362,
    BRIDGE = 363,
    ETHER = 364,
    SADDR = 365,
    DADDR = 366,
    TYPE = 367,
    VLAN = 368,
    ID = 369,
    CFI = 370,
    PCP = 371,
    ARP = 372,
    HTYPE = 373,
    PTYPE = 374,
    HLEN = 375,
    PLEN = 376,
    OPERATION = 377,
    IP = 378,
    HDRVERSION = 379,
    HDRLENGTH = 380,
    DSCP = 381,
    ECN = 382,
    LENGTH = 383,
    FRAG_OFF = 384,
    TTL = 385,
    PROTOCOL = 386,
    CHECKSUM = 387,
    PTR = 388,
    VALUE = 389,
    LSRR = 390,
    RR = 391,
    SSRR = 392,
    RA = 393,
    ICMP = 394,
    CODE = 395,
    SEQUENCE = 396,
    GATEWAY = 397,
    MTU = 398,
    IGMP = 399,
    MRT = 400,
    OPTIONS = 401,
    IP6 = 402,
    PRIORITY = 403,
    FLOWLABEL = 404,
    NEXTHDR = 405,
    HOPLIMIT = 406,
    ICMP6 = 407,
    PPTR = 408,
    MAXDELAY = 409,
    AH = 410,
    RESERVED = 411,
    SPI = 412,
    ESP = 413,
    COMP = 414,
    FLAGS = 415,
    CPI = 416,
    PORT = 417,
    UDP = 418,
    SPORT = 419,
    DPORT = 420,
    UDPLITE = 421,
    CSUMCOV = 422,
    TCP = 423,
    ACKSEQ = 424,
    DOFF = 425,
    WINDOW = 426,
    URGPTR = 427,
    OPTION = 428,
    ECHO = 429,
    EOL = 430,
    MAXSEG = 431,
    NOOP = 432,
    SACK = 433,
    SACK0 = 434,
    SACK1 = 435,
    SACK2 = 436,
    SACK3 = 437,
    SACK_PERMITTED = 438,
    TIMESTAMP = 439,
    KIND = 440,
    COUNT = 441,
    LEFT = 442,
    RIGHT = 443,
    TSVAL = 444,
    TSECR = 445,
    DCCP = 446,
    SCTP = 447,
    VTAG = 448,
    RT = 449,
    RT0 = 450,
    RT2 = 451,
    RT4 = 452,
    SEG_LEFT = 453,
    ADDR = 454,
    LAST_ENT = 455,
    TAG = 456,
    SID = 457,
    HBH = 458,
    FRAG = 459,
    RESERVED2 = 460,
    MORE_FRAGMENTS = 461,
    DST = 462,
    MH = 463,
    META = 464,
    MARK = 465,
    IIF = 466,
    IIFNAME = 467,
    IIFTYPE = 468,
    OIF = 469,
    OIFNAME = 470,
    OIFTYPE = 471,
    SKUID = 472,
    SKGID = 473,
    NFTRACE = 474,
    RTCLASSID = 475,
    IBRIPORT = 476,
    OBRIPORT = 477,
    IBRIDGENAME = 478,
    OBRIDGENAME = 479,
    PKTTYPE = 480,
    CPU = 481,
    IIFGROUP = 482,
    OIFGROUP = 483,
    CGROUP = 484,
    TIME = 485,
    CLASSID = 486,
    NEXTHOP = 487,
    CT = 488,
    L3PROTOCOL = 489,
    PROTO_SRC = 490,
    PROTO_DST = 491,
    ZONE = 492,
    DIRECTION = 493,
    EVENT = 494,
    EXPECTATION = 495,
    EXPIRATION = 496,
    HELPER = 497,
    LABEL = 498,
    STATE = 499,
    STATUS = 500,
    ORIGINAL = 501,
    REPLY = 502,
    COUNTER = 503,
    NAME = 504,
    PACKETS = 505,
    BYTES = 506,
    AVGPKT = 507,
    COUNTERS = 508,
    QUOTAS = 509,
    LIMITS = 510,
    SYNPROXYS = 511,
    HELPERS = 512,
    LOG = 513,
    PREFIX = 514,
    GROUP = 515,
    SNAPLEN = 516,
    QUEUE_THRESHOLD = 517,
    LEVEL = 518,
    LIMIT = 519,
    RATE = 520,
    BURST = 521,
    OVER = 522,
    UNTIL = 523,
    QUOTA = 524,
    USED = 525,
    SECMARK = 526,
    SECMARKS = 527,
    NANOSECOND = 528,
    MICROSECOND = 529,
    MILLISECOND = 530,
    SECOND = 531,
    MINUTE = 532,
    HOUR = 533,
    DAY = 534,
    WEEK = 535,
    _REJECT = 536,
    WITH = 537,
    ICMPX = 538,
    SNAT = 539,
    DNAT = 540,
    MASQUERADE = 541,
    REDIRECT = 542,
    RANDOM = 543,
    FULLY_RANDOM = 544,
    PERSISTENT = 545,
    QUEUE = 546,
    QUEUENUM = 547,
    BYPASS = 548,
    FANOUT = 549,
    DUP = 550,
    FWD = 551,
    NUMGEN = 552,
    INC = 553,
    MOD = 554,
    OFFSET = 555,
    JHASH = 556,
    SYMHASH = 557,
    SEED = 558,
    POSITION = 559,
    INDEX = 560,
    COMMENT = 561,
    XML = 562,
    JSON = 563,
    VM = 564,
    NOTRACK = 565,
    EXISTS = 566,
    MISSING = 567,
    EXTHDR = 568,
    IPSEC = 569,
    MODE = 570,
    REQID = 571,
    SPNUM = 572,
    TRANSPORT = 573,
    TUNNEL = 574,
    IN = 575,
    OUT = 576
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
#define WILDCARD 288
#define TPROXY 289
#define OSF 290
#define SYNPROXY 291
#define MSS 292
#define WSCALE 293
#define SACKPERM 294
#define TYPEOF 295
#define HOOK 296
#define DEVICE 297
#define DEVICES 298
#define TABLE 299
#define TABLES 300
#define CHAIN 301
#define CHAINS 302
#define RULE 303
#define RULES 304
#define SETS 305
#define SET 306
#define ELEMENT 307
#define MAP 308
#define MAPS 309
#define FLOWTABLE 310
#define HANDLE 311
#define RULESET 312
#define TRACE 313
#define INET 314
#define NETDEV 315
#define ADD 316
#define UPDATE 317
#define REPLACE 318
#define CREATE 319
#define INSERT 320
#define DELETE 321
#define GET 322
#define LIST 323
#define RESET 324
#define FLUSH 325
#define RENAME 326
#define DESCRIBE 327
#define IMPORT 328
#define EXPORT 329
#define MONITOR 330
#define ALL 331
#define ACCEPT 332
#define DROP 333
#define CONTINUE 334
#define JUMP 335
#define GOTO 336
#define RETURN 337
#define TO 338
#define CONSTANT 339
#define INTERVAL 340
#define DYNAMIC 341
#define AUTOMERGE 342
#define TIMEOUT 343
#define GC_INTERVAL 344
#define ELEMENTS 345
#define EXPIRES 346
#define POLICY 347
#define MEMORY 348
#define PERFORMANCE 349
#define SIZE 350
#define FLOW 351
#define OFFLOAD 352
#define METER 353
#define METERS 354
#define FLOWTABLES 355
#define NUM 356
#define STRING 357
#define QUOTED_STRING 358
#define ASTERISK_STRING 359
#define LL_HDR 360
#define NETWORK_HDR 361
#define TRANSPORT_HDR 362
#define BRIDGE 363
#define ETHER 364
#define SADDR 365
#define DADDR 366
#define TYPE 367
#define VLAN 368
#define ID 369
#define CFI 370
#define PCP 371
#define ARP 372
#define HTYPE 373
#define PTYPE 374
#define HLEN 375
#define PLEN 376
#define OPERATION 377
#define IP 378
#define HDRVERSION 379
#define HDRLENGTH 380
#define DSCP 381
#define ECN 382
#define LENGTH 383
#define FRAG_OFF 384
#define TTL 385
#define PROTOCOL 386
#define CHECKSUM 387
#define PTR 388
#define VALUE 389
#define LSRR 390
#define RR 391
#define SSRR 392
#define RA 393
#define ICMP 394
#define CODE 395
#define SEQUENCE 396
#define GATEWAY 397
#define MTU 398
#define IGMP 399
#define MRT 400
#define OPTIONS 401
#define IP6 402
#define PRIORITY 403
#define FLOWLABEL 404
#define NEXTHDR 405
#define HOPLIMIT 406
#define ICMP6 407
#define PPTR 408
#define MAXDELAY 409
#define AH 410
#define RESERVED 411
#define SPI 412
#define ESP 413
#define COMP 414
#define FLAGS 415
#define CPI 416
#define PORT 417
#define UDP 418
#define SPORT 419
#define DPORT 420
#define UDPLITE 421
#define CSUMCOV 422
#define TCP 423
#define ACKSEQ 424
#define DOFF 425
#define WINDOW 426
#define URGPTR 427
#define OPTION 428
#define ECHO 429
#define EOL 430
#define MAXSEG 431
#define NOOP 432
#define SACK 433
#define SACK0 434
#define SACK1 435
#define SACK2 436
#define SACK3 437
#define SACK_PERMITTED 438
#define TIMESTAMP 439
#define KIND 440
#define COUNT 441
#define LEFT 442
#define RIGHT 443
#define TSVAL 444
#define TSECR 445
#define DCCP 446
#define SCTP 447
#define VTAG 448
#define RT 449
#define RT0 450
#define RT2 451
#define RT4 452
#define SEG_LEFT 453
#define ADDR 454
#define LAST_ENT 455
#define TAG 456
#define SID 457
#define HBH 458
#define FRAG 459
#define RESERVED2 460
#define MORE_FRAGMENTS 461
#define DST 462
#define MH 463
#define META 464
#define MARK 465
#define IIF 466
#define IIFNAME 467
#define IIFTYPE 468
#define OIF 469
#define OIFNAME 470
#define OIFTYPE 471
#define SKUID 472
#define SKGID 473
#define NFTRACE 474
#define RTCLASSID 475
#define IBRIPORT 476
#define OBRIPORT 477
#define IBRIDGENAME 478
#define OBRIDGENAME 479
#define PKTTYPE 480
#define CPU 481
#define IIFGROUP 482
#define OIFGROUP 483
#define CGROUP 484
#define TIME 485
#define CLASSID 486
#define NEXTHOP 487
#define CT 488
#define L3PROTOCOL 489
#define PROTO_SRC 490
#define PROTO_DST 491
#define ZONE 492
#define DIRECTION 493
#define EVENT 494
#define EXPECTATION 495
#define EXPIRATION 496
#define HELPER 497
#define LABEL 498
#define STATE 499
#define STATUS 500
#define ORIGINAL 501
#define REPLY 502
#define COUNTER 503
#define NAME 504
#define PACKETS 505
#define BYTES 506
#define AVGPKT 507
#define COUNTERS 508
#define QUOTAS 509
#define LIMITS 510
#define SYNPROXYS 511
#define HELPERS 512
#define LOG 513
#define PREFIX 514
#define GROUP 515
#define SNAPLEN 516
#define QUEUE_THRESHOLD 517
#define LEVEL 518
#define LIMIT 519
#define RATE 520
#define BURST 521
#define OVER 522
#define UNTIL 523
#define QUOTA 524
#define USED 525
#define SECMARK 526
#define SECMARKS 527
#define NANOSECOND 528
#define MICROSECOND 529
#define MILLISECOND 530
#define SECOND 531
#define MINUTE 532
#define HOUR 533
#define DAY 534
#define WEEK 535
#define _REJECT 536
#define WITH 537
#define ICMPX 538
#define SNAT 539
#define DNAT 540
#define MASQUERADE 541
#define REDIRECT 542
#define RANDOM 543
#define FULLY_RANDOM 544
#define PERSISTENT 545
#define QUEUE 546
#define QUEUENUM 547
#define BYPASS 548
#define FANOUT 549
#define DUP 550
#define FWD 551
#define NUMGEN 552
#define INC 553
#define MOD 554
#define OFFSET 555
#define JHASH 556
#define SYMHASH 557
#define SEED 558
#define POSITION 559
#define INDEX 560
#define COMMENT 561
#define XML 562
#define JSON 563
#define VM 564
#define NOTRACK 565
#define EXISTS 566
#define MISSING 567
#define EXTHDR 568
#define IPSEC 569
#define MODE 570
#define REQID 571
#define SPNUM 572
#define TRANSPORT 573
#define TUNNEL 574
#define IN 575
#define OUT 576

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 165 "parser_bison.y" /* yacc.c:352  */

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

#line 922 "parser_bison.c" /* yacc.c:352  */
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
#define YYLAST   7431

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  331
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  342
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1827

#define YYUNDEFTOK  2
#define YYMAXUTOK   576

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
       2,     2,     2,     2,     2,     2,   328,     2,     2,     2,
     325,   326,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   322,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   329,     2,   330,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   323,   327,   324,     2,     2,     2,     2,
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
     315,   316,   317,   318,   319,   320,   321
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   844,   844,   845,   854,   855,   858,   859,   862,   870,
     885,   892,   903,   911,   912,   913,   914,   934,   935,   936,
     937,   938,   939,   940,   941,   942,   943,   944,   945,   946,
     947,   948,   951,   955,   962,   966,   974,   978,   982,   989,
     996,  1000,  1007,  1016,  1020,  1024,  1028,  1032,  1036,  1040,
    1044,  1048,  1052,  1056,  1060,  1064,  1070,  1076,  1080,  1087,
    1091,  1099,  1106,  1113,  1117,  1124,  1133,  1137,  1141,  1145,
    1149,  1153,  1157,  1161,  1167,  1173,  1177,  1181,  1185,  1189,
    1193,  1197,  1201,  1205,  1209,  1213,  1217,  1224,  1228,  1232,
    1236,  1240,  1244,  1248,  1252,  1256,  1260,  1264,  1270,  1276,
    1280,  1284,  1288,  1292,  1296,  1300,  1304,  1308,  1312,  1316,
    1320,  1324,  1328,  1332,  1336,  1340,  1344,  1348,  1352,  1356,
    1360,  1364,  1368,  1372,  1376,  1380,  1384,  1388,  1392,  1396,
    1400,  1404,  1408,  1412,  1418,  1422,  1426,  1430,  1434,  1438,
    1444,  1448,  1452,  1456,  1460,  1464,  1468,  1474,  1481,  1487,
    1495,  1501,  1509,  1518,  1519,  1522,  1523,  1524,  1525,  1526,
    1527,  1528,  1529,  1532,  1533,  1536,  1537,  1538,  1541,  1550,
    1556,  1568,  1578,  1579,  1580,  1581,  1582,  1593,  1603,  1614,
    1624,  1635,  1646,  1655,  1664,  1673,  1684,  1695,  1709,  1715,
    1716,  1717,  1718,  1719,  1720,  1721,  1726,  1736,  1737,  1738,
    1745,  1756,  1769,  1774,  1775,  1776,  1777,  1782,  1788,  1793,
    1798,  1803,  1808,  1813,  1818,  1819,  1830,  1831,  1834,  1838,
    1841,  1842,  1843,  1844,  1848,  1853,  1854,  1855,  1856,  1861,
    1871,  1882,  1893,  1905,  1914,  1923,  1932,  1941,  1946,  1951,
    1960,  1963,  1967,  1973,  1974,  1978,  1983,  1984,  1985,  1986,
    2000,  2004,  2010,  2015,  2022,  2027,  2032,  2035,  2042,  2049,
    2061,  2068,  2069,  2081,  2086,  2087,  2088,  2089,  2093,  2103,
    2104,  2105,  2106,  2110,  2120,  2121,  2122,  2123,  2127,  2138,
    2142,  2143,  2144,  2148,  2158,  2159,  2160,  2161,  2165,  2175,
    2176,  2177,  2178,  2182,  2192,  2193,  2194,  2195,  2199,  2209,
    2210,  2211,  2212,  2216,  2226,  2227,  2228,  2229,  2230,  2233,
    2263,  2270,  2274,  2277,  2287,  2294,  2305,  2318,  2333,  2334,
    2337,  2349,  2355,  2359,  2362,  2368,  2381,  2386,  2395,  2396,
    2399,  2402,  2403,  2404,  2407,  2422,  2423,  2426,  2427,  2428,
    2429,  2430,  2431,  2434,  2443,  2452,  2460,  2468,  2476,  2484,
    2492,  2500,  2508,  2516,  2524,  2532,  2540,  2548,  2556,  2564,
    2572,  2576,  2581,  2589,  2596,  2603,  2616,  2620,  2627,  2631,
    2637,  2649,  2655,  2662,  2663,  2664,  2665,  2668,  2669,  2670,
    2671,  2672,  2673,  2674,  2675,  2676,  2677,  2678,  2679,  2680,
    2681,  2682,  2683,  2684,  2685,  2686,  2687,  2690,  2691,  2694,
    2703,  2707,  2713,  2719,  2724,  2727,  2732,  2737,  2740,  2746,
    2751,  2759,  2760,  2762,  2766,  2774,  2778,  2781,  2785,  2791,
    2792,  2795,  2801,  2805,  2808,  2933,  2938,  2943,  2948,  2953,
    2959,  2989,  2993,  2997,  3001,  3005,  3011,  3015,  3018,  3022,
    3028,  3037,  3056,  3064,  3065,  3066,  3069,  3070,  3073,  3074,
    3089,  3105,  3113,  3114,  3115,  3118,  3119,  3122,  3123,  3124,
    3139,  3140,  3141,  3142,  3143,  3146,  3149,  3156,  3160,  3171,
    3182,  3192,  3198,  3201,  3202,  3205,  3211,  3217,  3223,  3230,
    3237,  3245,  3246,  3249,  3253,  3261,  3265,  3268,  3273,  3278,
    3282,  3288,  3304,  3323,  3329,  3330,  3336,  3337,  3343,  3344,
    3345,  3346,  3347,  3348,  3349,  3350,  3351,  3352,  3353,  3354,
    3355,  3358,  3359,  3363,  3369,  3370,  3376,  3377,  3383,  3384,
    3390,  3393,  3394,  3405,  3406,  3409,  3413,  3416,  3422,  3428,
    3439,  3440,  3441,  3444,  3445,  3446,  3449,  3453,  3457,  3462,
    3467,  3472,  3478,  3482,  3486,  3490,  3496,  3502,  3507,  3516,
    3526,  3527,  3530,  3533,  3537,  3542,  3548,  3549,  3552,  3555,
    3559,  3563,  3567,  3572,  3579,  3584,  3592,  3597,  3606,  3607,
    3613,  3614,  3615,  3618,  3619,  3622,  3628,  3632,  3635,  3640,
    3646,  3647,  3653,  3654,  3657,  3658,  3661,  3667,  3674,  3681,
    3691,  3692,  3693,  3696,  3704,  3715,  3722,  3725,  3731,  3735,
    3738,  3744,  3753,  3764,  3770,  3796,  3797,  3806,  3807,  3810,
    3819,  3830,  3831,  3832,  3833,  3834,  3835,  3836,  3837,  3838,
    3839,  3840,  3841,  3842,  3843,  3844,  3847,  3870,  3871,  3872,
    3875,  3876,  3877,  3878,  3879,  3882,  3886,  3889,  3893,  3900,
    3903,  3917,  3918,  3922,  3928,  3929,  3935,  3936,  3942,  3943,
    3949,  3952,  3953,  3964,  3970,  3976,  3977,  3980,  3986,  3987,
    3988,  3991,  3998,  4003,  4008,  4011,  4015,  4019,  4025,  4026,
    4033,  4039,  4040,  4043,  4049,  4053,  4056,  4060,  4064,  4074,
    4078,  4081,  4085,  4089,  4093,  4102,  4112,  4113,  4116,  4117,
    4120,  4121,  4122,  4123,  4134,  4145,  4151,  4172,  4178,  4195,
    4201,  4202,  4203,  4206,  4207,  4210,  4226,  4232,  4238,  4245,
    4259,  4267,  4275,  4281,  4285,  4289,  4293,  4297,  4304,  4309,
    4320,  4342,  4348,  4352,  4356,  4362,  4368,  4376,  4377,  4378,
    4379,  4382,  4383,  4387,  4393,  4394,  4400,  4401,  4407,  4408,
    4414,  4417,  4418,  4419,  4428,  4439,  4440,  4443,  4451,  4452,
    4453,  4454,  4455,  4456,  4457,  4458,  4459,  4460,  4461,  4462,
    4465,  4466,  4467,  4468,  4469,  4476,  4483,  4490,  4497,  4504,
    4511,  4518,  4525,  4532,  4539,  4546,  4553,  4556,  4557,  4558,
    4559,  4560,  4561,  4564,  4568,  4572,  4576,  4580,  4584,  4590,
    4591,  4601,  4605,  4609,  4625,  4626,  4629,  4630,  4631,  4632,
    4633,  4636,  4637,  4638,  4639,  4640,  4641,  4642,  4643,  4644,
    4645,  4646,  4647,  4648,  4649,  4650,  4651,  4652,  4653,  4654,
    4655,  4656,  4657,  4658,  4659,  4662,  4682,  4686,  4700,  4704,
    4708,  4714,  4720,  4721,  4722,  4725,  4726,  4729,  4730,  4733,
    4739,  4740,  4743,  4744,  4747,  4748,  4751,  4752,  4755,  4763,
    4790,  4795,  4800,  4806,  4807,  4810,  4814,  4834,  4835,  4836,
    4837,  4840,  4844,  4848,  4854,  4855,  4858,  4859,  4860,  4861,
    4862,  4863,  4864,  4865,  4866,  4867,  4868,  4869,  4870,  4871,
    4872,  4873,  4874,  4877,  4878,  4879,  4880,  4881,  4882,  4883,
    4886,  4887,  4888,  4889,  4892,  4893,  4894,  4895,  4898,  4899,
    4902,  4908,  4916,  4929,  4936,  4942,  4948,  4957,  4958,  4959,
    4960,  4961,  4962,  4963,  4964,  4965,  4966,  4967,  4968,  4969,
    4970,  4971,  4972,  4973,  4974,  4977,  4986,  4987,  4988,  4991,
    4997,  4998,  4999,  5002,  5008,  5009,  5010,  5011,  5014,  5020,
    5021,  5022,  5023,  5024,  5025,  5026,  5027,  5028,  5031,  5035,
    5039,  5046,  5047,  5048,  5049,  5050,  5051,  5052,  5053,  5054,
    5055,  5056,  5057,  5060,  5061,  5062,  5063,  5066,  5067,  5068,
    5069,  5070,  5073,  5079,  5080,  5081,  5082,  5083,  5084,  5085,
    5088,  5094,  5095,  5096,  5097,  5100,  5106,  5107,  5108,  5109,
    5110,  5111,  5112,  5113,  5114,  5116,  5122,  5123,  5124,  5125,
    5126,  5127,  5128,  5129,  5132,  5138,  5139,  5140,  5141,  5142,
    5145,  5151,  5152,  5155,  5161,  5162,  5163,  5166,  5172,  5173,
    5174,  5175,  5178,  5184,  5185,  5186,  5187,  5190,  5194,  5198,
    5205,  5206,  5207,  5208,  5209,  5210,  5211,  5212,  5213,  5214,
    5217,  5218,  5219,  5220,  5221,  5222,  5223,  5224,  5225,  5226,
    5227,  5228,  5231,  5232,  5233,  5234,  5235,  5236,  5237,  5238,
    5241,  5247,  5248,  5249,  5252,  5258,  5259,  5260,  5261,  5264,
    5272,  5273,  5276,  5277,  5278,  5279,  5280,  5281,  5282,  5283,
    5286,  5292,  5293,  5296,  5302,  5303,  5304,  5305,  5308,  5314,
    5320,  5326,  5329,  5335,  5336,  5337,  5338,  5344,  5350,  5351,
    5352,  5353,  5354,  5355,  5358,  5364,  5365,  5368,  5374,  5375,
    5376,  5377,  5378,  5381,  5395,  5396,  5397,  5398,  5399
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
  "\"fib\"", "\"socket\"", "\"transparent\"", "\"wildcard\"", "\"tproxy\"",
  "\"osf\"", "\"synproxy\"", "\"mss\"", "\"wscale\"", "\"sack-perm\"",
  "\"typeof\"", "\"hook\"", "\"device\"", "\"devices\"", "\"table\"",
  "\"tables\"", "\"chain\"", "\"chains\"", "\"rule\"", "\"rules\"",
  "\"sets\"", "\"set\"", "\"element\"", "\"map\"", "\"maps\"",
  "\"flowtable\"", "\"handle\"", "\"ruleset\"", "\"trace\"", "\"inet\"",
  "\"netdev\"", "\"add\"", "\"update\"", "\"replace\"", "\"create\"",
  "\"insert\"", "\"delete\"", "\"get\"", "\"list\"", "\"reset\"",
  "\"flush\"", "\"rename\"", "\"describe\"", "\"import\"", "\"export\"",
  "\"monitor\"", "\"all\"", "\"accept\"", "\"drop\"", "\"continue\"",
  "\"jump\"", "\"goto\"", "\"return\"", "\"to\"", "\"constant\"",
  "\"interval\"", "\"dynamic\"", "\"auto-merge\"", "\"timeout\"",
  "\"gc-interval\"", "\"elements\"", "\"expires\"", "\"policy\"",
  "\"memory\"", "\"performance\"", "\"size\"", "\"flow\"", "\"offload\"",
  "\"meter\"", "\"meters\"", "\"flowtables\"", "\"number\"", "\"string\"",
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
  "chain_block", "subchain_block", "typeof_expr", "set_block_alloc",
  "set_block", "set_block_expr", "set_flag_list", "set_flag",
  "map_block_alloc", "map_block", "set_mechanism", "set_policy_spec",
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
  "stmt_list", "stateful_stmt", "stmt", "chain_stmt_type", "chain_stmt",
  "verdict_stmt", "verdict_map_stmt", "verdict_map_expr",
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
     575,   576,    61,   123,   125,    40,    41,   124,    36,    91,
      93
};
# endif

#define YYPACT_NINF -1426

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1426)))

#define YYTABLE_NINF -900

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1426,  6996, -1426,   590, -1426, -1426,    87,   128,   128,   128,
     809,   809,   809,   809,   809,   809,   809,   809, -1426, -1426,
    2564,   156,  1008,   186,  2475,   190,  7138,   301,   639,   220,
    6492,   126,   129,   196, -1426, -1426, -1426, -1426,   152,   809,
     809,   809,   809, -1426, -1426, -1426,   587, -1426,   128, -1426,
     128,    61,  5958, -1426,   590, -1426,    -4,    46,   590,   128,
   -1426,   -17,     4,  5958,   128, -1426,  -125, -1426,   128, -1426,
   -1426,   809, -1426,   809,   809,   809,   809,   809,   809,   809,
     214,   809,   809,   809,   809, -1426,   809, -1426,   809,   809,
     809,   809,   809,   809,   809,   809,   286,   809,   809,   809,
     809, -1426,   809, -1426,   809,   809,   809,   809,   809,  1075,
     809,   809,   809,   809,   809,   654,   809,   809,   809,    82,
     809,  1142,  1144,  1396,  1709,   809,   809,   809,  2150, -1426,
     809,  2188,  2272,   809, -1426,   809,   809,   809,   809,   809,
     313,   809, -1426,   809, -1426,   892,    64,   103,   276, -1426,
   -1426, -1426, -1426,   569,   906,   751,  1355,  3064,  1207,   332,
     839,  1497,   774,    60,   485,   677,   451,  2301,   295,   387,
    1296,   240,   250,   331,   195,   769,   351,   591,  4126, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
    5264, -1426, -1426,    -9,  6188,   116,   608,   457,  6492,   128,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426,   718, -1426, -1426,   185, -1426,
   -1426,   718, -1426, -1426, -1426, -1426,  1266,   809,   809,   809,
     -82, -1426, -1426, -1426, -1426, -1426, -1426, -1426,   401,   409,
     416, -1426, -1426, -1426,    97,   281,   683, -1426, -1426, -1426,
   -1426, -1426, -1426,     2,     2, -1426,   102,   128,  4355,  5052,
     310, -1426,   319,   370, -1426, -1426, -1426, -1426, -1426, -1426,
     483,   101, -1426,   605, -1426,   327,  5958, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426,   575, -1426,   388, -1426, -1426,
   -1426,   361, -1426,  3937, -1426, -1426,   139, -1426,   216, -1426,
     226, -1426, -1426, -1426,   753, -1426,   100, -1426, -1426,   610,
   -1426, -1426, -1426,   692,   660,   650,   359, -1426,   549, -1426,
    5092, -1426, -1426, -1426,   670, -1426, -1426, -1426,   703, -1426,
    5456,  5456, -1426, -1426,    58,   420,   466, -1426, -1426,   476,
   -1426, -1426, -1426,   484, -1426,   520,   713,  5958, -1426,   -17,
       4, -1426,  -125, -1426, -1426,   809,   809,   809,   595, -1426,
   -1426, -1426,  5958,   154, -1426, -1426,   171, -1426, -1426,   179,
   -1426, -1426, -1426,   208, -1426, -1426,  -125, -1426,   230,   547,
   -1426, -1426, -1426, -1426,   809, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426,  -125, -1426, -1426, -1426, -1426, -1426, -1426,
     809, -1426, -1426, -1426, -1426, -1426, -1426,   809,   809, -1426,
   -1426, -1426,   844,   853,   864,   809, -1426,   809, -1426,   809,
   -1426,   809, -1426,   809, -1426, -1426, -1426, -1426,   809, -1426,
   -1426,   809, -1426,   809, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426,   809, -1426,   128, -1426, -1426, -1426,   921, -1426, -1426,
   -1426, -1426, -1426,   927,   111, -1426, -1426, -1426, -1426,   838,
      23, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426,   402,   480, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426,   823, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
    2600, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426,    -3, -1426, -1426,   643, -1426, -1426, -1426, -1426, -1426,
   -1426,   672, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426,  1612, -1426, -1426, -1426, -1426,   712,
     262,   738,   913, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426,   731,   725, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426,   718, -1426, -1426, -1426,   -38,  -109,
     217,    48, -1426, -1426, -1426,  4166,   979,  5242,  6492, -1426,
   -1426, -1426, -1426,  1030,  1032,     5,  1014,  1015,  1024,    27,
    1025,  1612,  1029,  5242,  5242,   614,  5242, -1426, -1426,   985,
    5242,  5242,  1007, -1426,  5690,    72, -1426,   967, -1426, -1426,
     770,   994,  1000,   575, -1426,    84,   967,  1001,  1009,  1019,
     967,   388, -1426,   314, -1426,  5242, -1426, -1426,  4395,  1039,
     906,   751,  1355,  3702, -1426,  2740,   144, -1426, -1426, -1426,
    1048, -1426, -1426, -1426, -1426,  6706, -1426,   929,  1090,  1120,
     781,   640,   288, -1426, -1426, -1426, -1426, -1426,  1134,   827,
    1133, -1426, -1426, -1426, -1426,  1136, -1426, -1426, -1426, -1426,
      81, -1426, -1426,  1138,  1139, -1426,  1040,  1046, -1426, -1426,
     139, -1426,  1145, -1426, -1426, -1426, -1426,  1146, -1426,  4624,
   -1426,  1146,  5242, -1426, -1426,   753, -1426,  1147, -1426,   128,
   -1426,   826, -1426,   128,    55, -1426,  7103,  7103,  7103,  7103,
    7103,  6492,    62,  5527, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426,  7103, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426,  1148, -1426,   970,  1153,
    1154,   829,   680,  1169, -1426, -1426, -1426,  5527,  5242,  5242,
    1078,    73,   590,  1148, -1426,   590,  1079, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426,  1156,   858,   861,   867,
   -1426,   868,   872, -1426, -1426, -1426,   944,   931,   715,   967,
   -1426,  1096,  1098,  1099,  1104, -1426,  1105,   889, -1426, -1426,
   -1426, -1426, -1426,   809,   809,   809, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426,  1112,    64, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426,   541, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426,   972, -1426,  1113,  1122,
   -1426, -1426,   765, -1426,   811, -1426, -1426, -1426, -1426, -1426,
   -1426,  1123,  1124,   926,  1135,    22, -1426, -1426, -1426,   912,
     914,   915,  1141, -1426, -1426,   614, -1426, -1426, -1426,  1143,
   -1426, -1426, -1426, -1426,  5242,  3064,   839,  1240,  4853, -1426,
     100,    66,  1238,   967,   967,  1157,  6492,  5242,  5242,  5242,
   -1426,  1159,  5242,  1197,  5242, -1426, -1426, -1426, -1426,  1163,
   -1426,    41,  1212, -1426,  5242, -1426,   605,   988,   125, -1426,
     948,  1169,   605, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426,  1103,   543, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426,  1162,  1175,  1186,  1176, -1426,  5242,  1261,  5242,
    5242,   966, -1426, -1426,  6706,  6706,  6706,  6706,  6706,  1196,
    6706,  6706,    99,  5242,  1146,  5242,  1215,  1293,  1219,  2690,
    2690, -1426, -1426, -1426,  5242,   827,  5242,   827, -1426, -1426,
     711, -1426,  6492, -1426,  6492, -1426, -1426, -1426,   970,  1153,
    1154, -1426,   605, -1426, -1426, -1426,   978,  7103,  7103,  7103,
    7103,  7103,  7103,  7103,  1204,  7103,  7103, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426,   676,  1907,   700,  2818,  1181,   446,
     638, -1426, -1426, -1426, -1426, -1426, -1426,   991,   995,   997,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426,  1303, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426,   992,   996, -1426, -1426, -1426, -1426,   926,   488,  1216,
   -1426, -1426, -1426, -1426, -1426,   898, -1426, -1426, -1426,  1074,
     461,  1226,  2017,   442,    41,    92, -1426,  5242,  5242,  1333,
   -1426,  1241,  1241, -1426,    66, -1426, -1426, -1426,  1017,  1238,
    5958,    66, -1426, -1426, -1426, -1426, -1426,  5242, -1426,   141,
   -1426, -1426,  1072,  5242,  1310, -1426,  7005, -1426,  1241,  1241,
    1095, -1426,   125, -1426,  5690, -1426,  3701, -1426, -1426, -1426,
    1347, -1426,  1253,  1255, -1426,  1256, -1426,  5242, -1426, -1426,
   -1426, -1426, -1426,   929,  1090,  1120, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426,  1362,  5242,  1198,  5242, -1426, -1426, -1426,
   -1426,   827, -1426,   827,  1146, -1426,    86,  5958,  5761,    76,
   -1426, -1426, -1426, -1426, -1426,   970,  1153,  1154, -1426, -1426,
   -1426, -1426,   948,  1267,  1331, -1426, -1426, -1426, -1426, -1426,
     128,   128,   128,   128,   128,  1269,   325,   128,   128,   128,
     128, -1426, -1426, -1426,   590, -1426,    52,  1271,  1277, -1426,
   -1426, -1426,   590,   590,   590,   590,   590,  6492, -1426,  1241,
    1241,  1056,   928,  1285,   394,   673,   590, -1426, -1426, -1426,
     590,   590,  6492,  1241,  1059,   394,   673, -1426, -1426, -1426,
     590,   590,  1286,  1069, -1426, -1426, -1426, -1426,   767,  3121,
    1869,   630,   851, -1426, -1426, -1426,  1480,  1291, -1426, -1426,
   -1426,  1292, -1426, -1426, -1426, -1426, -1426,   845,  2234,  1659,
    1294, -1426, -1426, -1426, -1426, -1426,   145, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426,  1072, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426,  5242, -1426, -1426, -1426, -1426,
    6492,  1070,    66, -1426,   763,  1130,  1300, -1426, -1426,  5242,
       2,     2,   605,  1169, -1426, -1426, -1426,  1301, -1426, -1426,
   -1426,   590,   543, -1426, -1426, -1426, -1426,  5242, -1426,  1320,
   -1426,  1146,  1146,  6492,  1220, -1426,    77,  1083,  1404,   605,
   -1426,  1227,  1309, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426,   128,   128,   128, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426,  1371, -1426, -1426, -1426,
   -1426, -1426, -1426,   881, -1426,   590,   590,  -125, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,   947,
   -1426, -1426, -1426, -1426, -1426,   852, -1426, -1426, -1426, -1426,
     793,   590,  -125,   822,   852, -1426, -1426,  1274,   396, -1426,
   -1426, -1426, -1426, -1426,  1006,  2298,  1814, -1426, -1426,   926,
    1092,   651,   809, -1426, -1426, -1426, -1426, -1426,  1241,  1327,
     651,  1329,   809, -1426, -1426, -1426, -1426, -1426,  1328,   809,
   -1426, -1426, -1426, -1426, -1426, -1426,   763,  1130, -1426, -1426,
    5958, -1426, -1426, -1426, -1426, -1426, -1426,  1166,  1332, -1426,
      41, -1426, -1426,  1183, -1426, -1426, -1426,  5242,  1117,  6492,
   -1426, -1426,  1254,  5761, -1426, -1426,  1403,   590,  1121,  1131,
    1149,  1160,  1167, -1426, -1426, -1426,  1168,  1170,  1174,  1177,
    1343,  6492, -1426, -1426, -1426, -1426,   394, -1426,   673, -1426,
    6340, -1426, -1426,  2286, -1426,    90,   590,     7,   590, -1426,
   -1426, -1426, -1426, -1426,  1178, -1426, -1426,   590,   590,   590,
     590,   590,   590,   590,  1316,   590,  1166, -1426,  1129,  1356,
   -1426,    44, -1426,  1358, -1426, -1426,  1155,   605, -1426, -1426,
    1227, -1426, -1426, -1426, -1426, -1426,  1188,  1191,  1193, -1426,
   -1426, -1426, -1426,   987, -1426, -1426, -1426,  6492,   881,   394,
     590,   590,   590,   590,   947,  1379, -1426, -1426, -1426,   871,
   -1426, -1426, -1426, -1426, -1426,    79, -1426, -1426, -1426,  1383,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426,   651, -1426, -1426,
   -1426,  1248, -1426, -1426, -1426, -1426, -1426,  1403,  1985,  3432,
    2052,  2250,  1531, -1426, -1426, -1426,  2067,  2161,   594,  1280,
      35,  1195,  1274,   881, -1426,   947, -1426, -1426, -1426, -1426,
   -1426, -1426,  1417,  1419,    65, -1426,  1521,    80, -1426,   590,
   -1426, -1426,   590,   590,   590,   590,   590,  1901,  2449,  1947,
     590,   590,   590,   590, -1426, -1426,   396, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426,  1429,  1383,   590, -1426, -1426, -1426,
   -1426, -1426, -1426,   590,   590,   590, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     335,   335,   335,   335,   335,   335,   335,   335,   339,   342,
     335,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   153,   341,   340,   337,   338,     0,   335,
     335,   335,   335,    14,    13,     3,     0,    17,     0,   336,
       0,   360,     0,    12,     0,   330,     0,     0,     0,     0,
     493,    32,    34,     0,     0,   202,     0,   224,     0,   245,
      18,   335,    19,   335,   335,   335,   335,   335,   335,   335,
       0,   335,   335,   335,   335,    20,   335,    21,   335,   335,
     335,   335,   335,   335,   335,   335,     0,   335,   335,   335,
     335,    22,   335,    23,   335,   335,   366,   335,   366,   366,
     335,   335,   366,   335,   366,     0,   335,   366,   366,     0,
     335,   366,   366,   366,   366,   335,   335,   335,   366,    24,
     335,   366,   366,   335,    25,   335,   335,   335,   335,   366,
       0,   335,    26,   335,    27,     0,     0,     0,   639,   610,
     331,   332,   333,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   801,
     802,   803,   804,   805,   806,   807,   808,   809,   810,   811,
     812,   813,   814,   815,   816,   817,   818,   819,   820,   822,
       0,   824,   823,     0,     0,     0,     0,   821,     0,     0,
      31,   606,   605,   611,   612,   168,   622,   623,   616,   792,
     617,   620,   624,   621,   618,   619,   613,   907,   908,   909,
     910,   911,   912,   913,   914,   915,   916,   917,   918,   919,
     920,   921,   922,   923,   924,   614,  1072,  1073,  1074,  1075,
    1076,  1077,  1078,  1079,   615,     0,   165,   166,     0,    28,
     149,     0,    29,   151,   154,    30,   155,   335,   335,   335,
      42,   721,   697,   699,    16,    15,   343,   345,     0,     0,
       0,   362,   361,   363,     0,   483,     0,   590,   591,   592,
     783,   784,   785,   397,   398,   788,   597,     0,     0,     0,
     413,   421,     0,   445,   466,   473,   474,   552,   558,   575,
       0,     0,   828,     7,    37,   368,   370,   381,   371,   188,
     396,   377,   401,   376,   373,   411,   383,   419,   374,   375,
     384,   467,   385,     0,   386,   395,   481,   389,   551,   390,
     557,   391,   392,   387,   573,   393,     0,   394,   379,     0,
     596,   378,   641,   644,   646,   648,   650,   651,   658,   660,
       0,   659,   603,   400,   792,   382,   388,   380,   613,     8,
       0,     0,    11,   354,     0,     0,     0,    36,   348,     0,
      40,   217,   216,     0,   351,     0,     0,     0,   493,    57,
      59,   202,     0,   224,   245,   335,   335,   335,    65,   721,
     697,   699,     0,     0,    96,    97,     0,    75,    76,     0,
      77,    78,    79,     0,    80,    81,     0,    82,     0,    84,
      85,   701,   702,   700,   335,    87,    88,    92,    93,    89,
      90,    94,    95,     0,   120,    99,   367,   100,   101,   102,
     335,   103,   105,   129,   128,   127,   121,   335,   366,   125,
     124,   126,   701,   702,     0,   335,   108,   335,   106,   335,
     109,   335,   112,   335,   118,   114,   111,   117,   335,   115,
     136,   335,   134,   335,   137,   139,   140,   141,   142,   143,
     146,   335,   145,     0,   926,   927,   928,     0,   630,   631,
     632,   633,   634,   636,     0,   832,   834,   833,   831,     0,
       0,  1070,  1071,  1069,   930,   931,   932,   929,   937,   934,
     935,   936,   933,     0,     0,   939,   940,   941,   942,   943,
     938,   961,   962,   956,   951,   952,   953,   954,   955,   957,
     958,   959,   960,     0,   948,   973,   976,   975,   974,   977,
     978,   979,   972,   981,   982,   983,   984,   980,   993,   994,
     986,   987,   988,   990,   989,   991,   992,   985,   996,  1001,
     998,   997,  1002,  1000,   999,  1003,   995,  1006,  1009,  1005,
    1007,  1008,  1004,  1012,  1011,  1010,  1014,  1015,  1016,  1013,
    1020,  1021,  1018,  1019,  1017,  1026,  1023,  1024,  1025,  1022,
    1038,  1032,  1035,  1036,  1030,  1031,  1033,  1034,  1037,  1039,
       0,  1027,  1063,  1061,  1062,  1060,  1068,  1065,  1066,  1067,
    1064,  1086,   853,  1085,   859,   854,  1084,  1087,   857,   858,
     860,     0,   855,  1083,     0,  1088,  1091,  1090,  1094,  1093,
    1095,     0,  1092,  1082,  1081,  1080,  1103,  1100,  1098,  1099,
    1101,  1102,  1097,  1106,  1105,  1104,  1110,  1109,  1112,  1108,
    1111,  1107,   793,   796,   797,   798,   800,   799,   821,   791,
     794,   795,   874,   875,   881,   867,   868,   866,   876,   877,
     897,   870,   879,   872,   873,   878,   869,   871,   864,   865,
     895,   894,   896,   880,     0,   861,   882,   838,   837,     0,
     658,     0,     0,  1115,  1114,  1116,  1117,  1118,  1113,   842,
     843,   841,     0,   604,   148,   167,   150,   156,   157,   159,
     158,   161,   162,   160,   163,   718,   718,   718,     0,     0,
     445,     0,   357,   358,   359,     0,     0,     0,     0,   790,
     789,   786,   787,     0,     0,     0,   793,   791,     0,     0,
       0,     0,   861,     0,     0,   454,     0,   443,   444,     0,
       0,     0,     0,     6,     0,     0,   662,     0,   369,   372,
       0,     0,     0,   412,   415,     0,     0,     0,     0,     0,
       0,   420,   422,     0,   465,     0,   529,   756,     0,     0,
     748,   751,   752,   749,   755,   750,     0,   759,   757,   758,
       0,   754,   753,   745,   746,     0,   511,   514,   516,   518,
     520,   521,   526,   533,   530,   531,   532,   534,   536,   472,
     498,   499,   509,   747,   500,   507,   501,   508,   504,   505,
       0,   502,   503,     0,   535,   506,     0,     0,   490,   489,
     482,   485,     0,   570,   571,   572,   550,   555,   568,     0,
     556,   561,     0,   582,   583,   574,   576,   579,   580,     0,
     608,     0,   607,     0,     0,   598,     0,     0,     0,     0,
       0,     0,     0,     0,   777,   778,   779,   780,   781,   782,
     748,   751,   752,   749,   769,   770,   750,   771,   768,   767,
     772,   765,   766,   764,   773,   774,   775,     0,   728,   760,
     730,   761,   655,   656,   742,   729,   723,   722,   734,   736,
     738,   740,   741,   727,   762,   763,   731,     0,     0,     0,
       0,     7,     0,   691,   690,     0,     0,   299,    54,   172,
     189,   203,   225,   246,   364,    56,     0,     0,     0,     0,
      63,     0,     0,   718,   718,   718,     0,     0,   445,     0,
      74,     0,     0,     0,     0,    83,     0,     0,   718,    98,
     104,   123,   122,   335,   335,   335,   130,   107,   110,   113,
     119,   116,   135,   138,   144,   147,     0,     0,   629,   627,
     628,   626,   640,   637,   638,   944,   946,   945,   947,   963,
     964,   965,   966,   950,  1043,  1050,  1040,  1042,  1041,  1045,
    1046,  1047,  1048,  1049,  1044,  1051,  1029,   856,     0,     0,
     883,   884,     0,   886,     0,   885,   887,   888,   862,   863,
     889,     0,     0,   835,     0,     0,   625,   152,   164,     0,
       0,     0,     0,   264,    43,   454,   289,    50,   269,     0,
      45,   294,   698,    52,     0,   749,   750,   475,     0,   484,
       0,   584,   586,     0,     0,     0,     0,     0,     0,     0,
     409,     0,     0,   889,     0,   414,   442,   452,   453,     0,
     451,     0,   564,   566,     0,   687,     7,     7,   671,   673,
     741,   686,     7,   661,   365,   197,   417,   418,   416,   435,
     434,     0,     0,   433,   429,   424,   425,   426,   427,   430,
     428,   423,     0,     0,     0,     0,   542,     0,   537,     0,
       0,     0,   498,   507,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   544,     0,     0,     0,     0,     0,
       0,   487,   488,   486,     0,     0,     0,   559,   578,   577,
       0,   609,     0,   600,     0,   599,   642,   643,   645,   647,
     649,   652,     7,   402,   404,   657,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   724,   826,   906,
     693,   692,     9,    10,     0,     0,     0,     0,     0,     0,
       0,    73,   172,   189,   203,   225,   246,     0,     0,     0,
      66,    71,    67,    72,   355,   344,   346,   349,   352,   246,
      91,   132,   133,   131,     0,   635,   967,   968,   970,   969,
     971,   949,  1054,  1053,  1052,  1055,  1056,  1057,  1058,  1059,
    1028,     0,     0,   890,   891,   892,   893,   835,   835,     0,
     852,   840,   844,   845,   848,     0,   279,   284,   274,     0,
       0,     0,     0,     0,     0,     0,   477,     0,     0,   476,
     587,     0,     0,   678,   585,   674,   830,   829,     0,   670,
       0,   668,   827,   825,   903,   410,   904,     0,   902,     0,
     447,   446,   448,     0,     0,   665,     0,   666,     0,     0,
     683,   685,   672,   679,   664,   663,     0,   432,   438,   439,
     431,   437,     0,     0,   471,     0,   543,     0,   547,   549,
     510,   512,   513,   515,   517,   519,   527,   528,   522,   525,
     524,   523,   539,   538,     0,     0,     0,   898,   899,   900,
     901,   553,   569,   560,   562,   581,     0,     0,     0,     0,
     405,   776,   726,   732,   733,   735,   737,   739,   725,   653,
     654,   743,   744,     0,     0,    55,   301,   300,   303,   302,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,   174,   173,     0,   171,     0,     0,     0,    35,
     191,   190,     0,     0,     0,     0,     0,     0,   213,     0,
       0,     0,     0,     0,     0,     0,     0,    38,   205,   204,
       0,     0,     0,     0,     0,     0,     0,    39,   227,   226,
       0,     0,     0,     0,   251,    41,   248,   247,     0,     0,
       0,     0,     0,   279,   284,   274,     0,     0,  1089,  1096,
     839,     0,   851,   836,   847,   846,   849,     0,     0,     0,
       0,    44,   266,   265,   268,   267,     0,    51,   291,   290,
     293,   292,    46,   271,   270,   273,   272,   448,    53,   296,
     295,   298,   297,   478,   480,     0,   334,   676,   677,   675,
       0,     0,   669,   905,     0,   457,     0,   450,   565,     0,
       0,     0,     7,   688,   689,   681,   682,     0,   680,   399,
     198,     0,     0,   468,   469,   470,   540,     0,   546,     0,
     548,   554,   563,     0,     0,   588,     0,     0,     0,     7,
     403,   494,     0,   356,   263,   347,   188,   350,   202,   224,
     353,   245,   170,     0,     0,     0,   263,   263,   263,   263,
     175,   328,   329,   325,   327,   326,     0,   324,   192,   194,
     193,   196,   195,     0,   200,     0,     0,     0,   244,   243,
     241,   242,   304,   306,   307,   305,   260,   308,   261,     0,
     259,   220,   221,   223,   222,     0,   219,   211,   214,   215,
       0,     0,     0,     0,     0,   240,   239,     0,     0,    58,
      60,    61,    62,    64,     0,     0,     0,    86,   925,   835,
       0,     0,     0,    48,   281,   280,   283,   282,     0,     0,
       0,     0,     0,    49,   286,   285,   288,   287,     0,     0,
      47,   276,   275,   278,   277,   694,     0,   457,   696,   479,
       0,   601,   460,   461,   462,   463,   464,   455,     0,   441,
       0,   567,   667,     0,   199,   436,   541,     0,     0,     0,
     589,   595,     0,   407,   406,   495,   496,     0,     0,     0,
       0,     0,     0,   263,   263,   263,     0,     0,     0,     0,
       0,     0,   207,   209,   210,   212,     0,   206,     0,   208,
       0,   228,   238,     0,   237,     0,     0,     0,     0,   253,
      69,    70,    68,   850,     0,   704,   703,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,   720,     0,     0,
     440,     0,   449,     0,   545,   593,     0,     7,   497,   491,
     494,   299,   189,   203,   225,   246,     0,     0,     0,   264,
     289,   269,   294,   323,   201,   262,   218,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   318,   312,   311,   315,
     310,   313,   314,   249,   257,     0,   254,   258,   250,     0,
     710,   712,   715,   716,   713,   714,   717,     0,   706,   719,
     602,     0,   459,   458,   684,   594,   408,   496,     0,     0,
       0,     0,     0,   279,   284,   274,     0,     0,     0,     0,
       0,     0,     0,     0,   231,     0,   233,   235,   234,   236,
     229,   319,     0,     0,     7,   252,     0,     0,   707,     0,
     456,   492,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   320,   321,     0,   309,   232,   230,
     317,   316,   256,   255,     0,     0,     0,   705,   187,   176,
     177,   178,   179,     0,     0,     0,   180,   185,   181,   186,
     322,   709,   708,   711,   183,   184,   182
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1426, -1426,    -1, -1011,    50, -1426, -1426,  1511, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426,    16, -1426,  1150, -1426,   362,  -318, -1114,
   -1426, -1308,  -385, -1112,  -379,   147,  -112,  -376, -1115, -1119,
   -1426,  -389, -1124,  -256, -1426,  -232,   -99, -1307,  -962,  -150,
    -149, -1334, -1330, -1328,  -144,  -151,  -130, -1426, -1426,  -200,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,    94,  -682,
   -1161,  1477,   -90,  2627, -1426,   685, -1426, -1426,    95, -1426,
     225,   350, -1426, -1426,  2025,   880,  -721,  1185, -1426, -1426,
     202,  1478,   803,   137,   -43, -1426, -1426,   257,  -304, -1426,
   -1426, -1426, -1426, -1426, -1426,    89, -1426, -1426, -1426, -1426,
     812, -1426, -1426, -1426,   805, -1426, -1426, -1426,   108, -1426,
    1278, -1168,   146, -1426,   557,   -92,   -12,    -7, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426,   757,  -366,  1210,
     -88,  -142,  -257,   497,   499,   504, -1426,  -715, -1426, -1426,
   -1426, -1426, -1426,  -345, -1426,  -525, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426,  -317,   482, -1426, -1426, -1426,
     768, -1426,   487, -1069, -1426, -1426,  1336, -1426, -1426, -1426,
   -1426,   776, -1426, -1426,   -56,   -23,  -756,  -325,   734,   -16,
   -1426, -1426, -1426,   652,    96, -1426, -1426, -1426, -1426, -1426,
    -173,  -193, -1426, -1426,   467, -1426,  1420,   -63, -1426,   559,
   -1045, -1426, -1191, -1426,   381, -1103, -1426,   364, -1426, -1426,
    1262,  -605,  1244,  -586,  1239,  -606,  1242,  1525, -1425, -1426,
   -1426,  -160, -1426, -1426,  -454,  -570,  1250, -1426,  1287,  -302,
    -768,  -765,  -763, -1426,  -324,  -710, -1426,  -246,  1544,  -724,
   -1426, -1202,  -290,   253,  1361, -1426,    53, -1426,   291, -1426,
   -1150, -1426,   378, -1426, -1426, -1426, -1426, -1426,   600,  -241,
     687,  1035,   787,  1363,  1365, -1426, -1426,  -502,   -62, -1426,
   -1426, -1426,   860, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426, -1426,
   -1426, -1426
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1396,   754,  1397,    45,    46,    47,    72,    85,
      87,   101,   103,   129,   134,   142,   144,   259,   262,   265,
     266,   714,  1017,   260,   210,   375,  1354,  1166,   376,  1167,
    1276,  1523,   379,  1168,   380,  1545,  1546,   383,  1169,  1380,
    1530,   385,  1170,  1658,  1725,  1726,  1538,  1539,  1628,  1230,
    1233,  1419,  1417,  1418,  1232,  1235,  1165,  1540,  1362,  1656,
    1719,  1720,  1721,  1762,  1363,  1364,  1513,  1514,  1493,   211,
    1447,    48,    49,    59,   408,    51,   411,  1496,    65,   415,
    1498,    69,   420,  1501,    60,   405,  1494,   281,   282,   283,
      52,   387,  1243,   437,  1366,   315,   316,   317,   318,   319,
     320,   321,   322,  1143,  1319,  1320,   323,   324,   325,   763,
     764,   326,   327,   771,   772,  1090,  1084,  1280,  1281,   328,
    1029,  1262,  1457,   329,  1059,  1680,  1609,  1607,   330,   331,
     774,   332,   333,   334,   335,   336,   830,   831,  1339,   374,
    1626,  1689,   796,   797,   798,   799,   800,   801,   802,  1299,
     803,   804,   805,   806,   807,   808,   809,   337,   338,   836,
     339,   340,   840,   341,   342,   837,   838,   343,   344,   845,
     846,   847,   848,  1040,  1041,   345,   346,   347,   348,   349,
     854,   855,   350,   351,   212,   810,   851,   890,   811,   352,
     216,   971,   493,   494,   812,   500,   353,   354,   355,   356,
     357,   358,   892,   893,   894,   359,   360,   361,   755,   756,
    1250,  1251,  1067,  1068,  1244,  1245,  1272,  1273,  1069,  1462,
     912,  1425,   718,  1436,   720,  1442,   721,   424,  1667,  1594,
    1777,  1778,  1577,  1587,  1019,  1431,   719,   362,   913,   914,
     898,   899,   900,   901,  1070,   903,   813,   814,   815,   906,
     907,   363,   731,   816,   659,   660,   219,   365,   817,   498,
    1220,   689,   818,  1015,   701,  1224,  1416,   222,   819,   621,
     821,   622,   822,   684,   685,  1008,  1009,   686,   823,   824,
     366,   367,   825,   227,   487,   228,   507,   229,   512,   230,
     520,   231,   534,   983,  1201,   232,   542,   233,   547,   234,
     557,   235,   566,   236,   572,   237,   575,   238,   579,   239,
     584,   240,   589,   241,   601,   996,  1210,   242,   605,   243,
     610,   244,   503,   245,   246,   635,   247,   623,   248,   625,
     249,   627,   250,   632,   251,   642,   252,   645,   253,   651,
     254,   698
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   760,    53,   382,   732,   932,   929,   213,   918,   314,
     381,   690,   759,   930,   215,   888,   436,   931,   436,   436,
     377,   852,   436,   841,   436,   888,   888,   436,   436,   213,
     947,   436,   436,   436,   436,   702,   902,   945,   436,  1032,
     213,   436,   436,   726,  1071,   275,   902,   902,   263,   436,
    1390,    44,  1402,   369,   949,  1265,  1267,   372,   897,  1399,
    1401,  1274,  1400,  1316,  1464,  1406,  1437,  1410,  1412,   753,
     752,  1566,   928,  1564,  1550,  1074,  1565,   753,  1553,  1072,
    1101,  1448,  1619,  1489,  1085,   849,  1774,  1805,  1089,  1317,
    1138,  1483,   820,     3,  1139,   916,     4,  1140,     5,   853,
    1045,    56,    57,    58,    55,   364,  1144,  1465,  1466,  1724,
      66,    67,  1715,  1024,   904,  1033,   364,   278,     6,     7,
       8,     9,   849,   849,   904,   904,   217,  1488,  1050,  1511,
    1512,  1318,  1136,  1137,  1030,   495,   496,   150,   151,   152,
     614,  1449,   276,  1260,   277,   612,  1742,   973,   217,  1027,
     150,   151,   152,   373,  1241,  1671,  1025,  1242,   378,   217,
    1079,  1454,   384,   733,  1115,  1596,  1116,  1724,  -695,   615,
     452,   391,   392,   393,   488,   489,   826,   827,   828,  1222,
     725,   213,  1010,   255,   751,   213,   261,   414,   416,   417,
      54,  1716,  1717,  1080,   150,   151,   152,   433,   313,   734,
    1037,   573,  1039,   209,    71,   442,   443,  1081,  1525,  1526,
     941,   449,  1022,  1268,  1026,    63,  1269,   574,  1055,  1056,
     612,  1060,  1551,   968,   612,  1062,  1063,   942,   618,   619,
      55,   661,   478,   479,    86,   943,   482,   730,   730,  1053,
     267,  -695,   102,  1455,   615,   439,   441,  1597,   615,   444,
    1096,   446,  1082,  1098,   450,   451,    55,  1032,   458,   460,
     462,   464,  1020,  1021,   944,   469,   143,   612,   472,   474,
     861,   704,   974,    55,   490,   491,   480,   706,   492,   687,
    1117,    55,  1390,   218,  1240,  1023,   946,   614,   402,   688,
     850,   615,  1261,   213,  1051,  1743,  1111,   895,   264,   832,
     217,  1083,   395,   703,   217,   218,  -169,   895,   895,   839,
      55,   620,  1779,   497,  1127,   863,   218,  1128,   370,  1484,
     633,   220,   453,   829,   423,   969,   970,  -188,  1046,   382,
     209,  1180,    55,  1183,   300,   209,   381,   889,  1223,   454,
    1118,  1112,  1708,   220,   925,   634,  1714,   889,   889,  1449,
     302,   661,  1182,   382,   220,   303,  1300,   481,   436,   940,
     381,  1246,  1247,   209,   213,   279,   280,  1181,   371,   364,
     382,  1031,   757,  1270,   421,   618,   619,   381,  1134,   213,
     209,   917,  1325,  1158,  1159,  1142,  1326,   729,   729,  1327,
     209,   735,   268,   209,   269,  1297,  1073,  1161,   757,  1763,
    1490,  1620,  1765,  1775,  1806,  1600,   499,   602,   221,  1065,
    1485,  1718,   217,  1503,  1618,   692,  1438,  1669,   209,  1663,
    1687,  1789,   313,  1787,  1323,  1324,  1788,   209,   209,   394,
     221,   757,  1488,   256,   257,   258,   256,   257,   258,   624,
     364,   221,  1682,     3,   543,   419,     4,     3,     5,   626,
       4,  1612,     5,  1092,   396,   364,   397,   218,   620,   603,
     604,   218,     3,   445,   544,     4,  1093,     5,     6,     7,
       8,     9,     6,     7,     8,     9,   643,   545,  1623,  1177,
    1178,  1179,  1094,   217,   747,   748,  1382,     6,     7,     8,
       9,   628,  1114,   705,  1190,   220,  1532,   373,   217,   220,
     276,   644,   722,   277,   833,   834,   835,   378,   904,  1236,
     723,   975,   384,  1239,   833,   834,   835,   724,   888,   606,
    1533,  1534,  1252,  1253,  1254,   976,   422,  1256,   423,  1258,
     727,   629,   630,   631,  1383,  1042,  1384,   852,  1372,  1264,
    1028,  1373,   951,  -445,  1636,  1637,  1638,  1639,   765,   130,
    1686,   607,   608,  1032,   131,   132,  1463,   861,  1385,   743,
    1171,  1145,   888,  1146,  1071,  1504,   750,  1505,   744,   218,
     133,  1752,  1286,   862,  1288,  1289,   964,   965,  1749,  1751,
     609,  1750,   221,   585,   745,   952,   221,   274,  1302,   977,
    1303,     4,   546,     5,     4,     3,     5,  1095,     4,  1311,
       5,  1313,   863,   978,  1535,  1157,  1386,   220,  1071,   753,
     904,   904,   904,   904,   904,   586,   587,   904,   588,   746,
       6,     7,     8,     9,  1536,  1537,  1506,  1507,  1508,  1509,
     223,     3,  1390,   757,     4,   576,     5,   747,   748,     3,
     218,   904,     4,   773,     5,   577,   578,   766,   767,   768,
     769,   770,   223,  1196,   853,   218,     6,     7,     8,     9,
    1109,   904,  1110,   223,     6,     7,     8,     9,   859,  1197,
    1382,  1696,  1697,  1698,  1198,  1199,  1746,   858,   220,  1392,
       4,  1393,     5,   135,  1278,   136,   860,  1153,  1141,  1279,
     137,  1066,   138,   220,   221,  -445,   139,    62,   447,   448,
    1154,     3,  1155,   646,     4,   213,     5,   856,   857,   747,
     748,  1022,  1443,  1444,  1333,   852,   647,   224,  1383,  1657,
    1384,   908,  1372,   648,   209,  1373,     6,     7,     8,     9,
    1018,   889,  1453,   501,   502,   140,  1340,   141,  1458,   224,
    1200,   649,  1385,   919,   287,   288,  1341,   650,   757,   289,
     224,  1342,   757,  1343,   909,  1344,   386,  1541,  1542,  1543,
     390,  1544,  1476,  1802,   214,   221,  1432,   757,     3,   278,
    1387,     4,  1102,     5,  1225,   410,   386,   699,   700,  1478,
     221,  1480,  1633,  1634,  1635,  1421,   214,   852,  1219,   920,
    1386,  1411,   438,     6,     7,     8,     9,   214,  1650,   921,
     895,  1641,   693,  1340,   223,   580,   850,   922,   223,   581,
    1314,   694,   695,  1341,  1665,   696,   697,   225,  1342,  1666,
    1343,   477,  1344,  1322,   217,   761,   762,  1653,   483,  1328,
    1646,  1330,  1332,   889,   889,   889,   889,   889,   213,   225,
     889,   582,   583,   923,   895,  -695,     3,  1291,  1292,     4,
     225,     5,     3,  1249,  1298,     4,     4,     5,     5,  1648,
    1345,   747,   748,   508,   889,   509,   510,   511,    18,    19,
    -245,     6,     7,     8,     9,  1213,  1214,     6,     7,     8,
       9,  1057,  1058,   636,   889,     4,  1394,     5,   953,  1641,
     226,   224,  1392,  1772,  1393,   224,  1773,   954,   637,   567,
     757,   904,   904,   904,   904,   904,   904,   904,   955,   904,
     904,  1162,   368,  1071,  1163,   568,   223,    34,  1792,   638,
    1599,  1215,  1216,   368,   569,   639,    35,  1345,   966,  1065,
     570,   571,    36,  1346,  1611,   967,   757,  1570,   214,  1042,
     972,  1249,   214,  1131,  1104,  1105,  1451,  1133,  1347,   548,
     549,     4,  1616,     5,  1562,  1646,    37,   217,   979,   980,
     981,   982,  1395,   550,  1348,   551,   552,   553,  1154,  1349,
    1155,  1350,   998,  1065,   640,   641,  1571,   426,   428,   430,
     432,   218,   747,   748,   850,  1148,  1149,   223,   554,   555,
     556,   225,   753,  1266,  1481,   225,  1482,   484,   485,   486,
    1346,   999,   223,   224,   843,   844,   757,     3,  1414,  1415,
       4,  1011,     5,  1487,  1013,  1347,   504,   505,   506,   220,
     904,  1528,  1529,   213,  1351,   256,   257,   258,   904,  1760,
    1761,  1348,     6,     7,     8,     9,  1349,  1012,  1350,  1602,
    1603,  1604,  1605,  1606,    73,   842,   843,   844,  1014,  1301,
     214,  1016,    74,  1043,    75,  1044,   850,  1309,  1310,    76,
      77,    78,  1038,    79,   226,  1047,  1048,  1202,   226,   150,
     151,   152,   904,   757,   224,  1049,  1052,  1032,  1794,  1572,
    1054,  1102,  1102,  1102,  1102,  1102,  1061,  1102,  1102,   224,
    1064,  1559,  1684,  1075,   891,  1076,  1307,  1307,  1570,  1394,
    1203,  1077,  1086,   225,   891,   891,   221,  1106,  1108,   213,
    1087,   213,  1632,  1630,   218,   833,   834,   835,   758,   440,
    1088,   214,  1099,  1631,   889,   889,   889,   889,   889,   889,
     889,  1100,   889,   889,    18,    19,   214,  1571,  1107,  1113,
    -898,  1121,   217,  -899,   213,  1119,  1120,  1122,  1645,  1132,
    1124,   757,   220,  1125,  1130,  1147,  1152,  1204,  1205,  1206,
    1207,  1208,  1209,  1334,  1336,  1352,  1360,  1378,  1388,  1573,
    1150,   732,  1151,  1652,   225,  1563,   368,  1156,  1629,  1160,
    1164,  1172,     3,    34,  1173,     4,   457,     5,   459,   225,
    1174,  1175,    35,   916,  1022,  1176,  1025,  1184,    36,  1185,
    1186,    18,    19,    18,    19,  1187,  1188,     6,     7,     8,
       9,  1066,  1189,  1194,  1211,  1337,  1353,  1361,  1379,  1389,
     364,  1367,    37,  1212,  1217,  1218,  1219,   213,   217,  1422,
     217,  1428,  1433,  1471,  1439,  1226,  1221,  1227,  1228,   221,
    1572,    80,  1229,   889,  1234,  1237,   861,   368,  1257,  1277,
      34,   889,    34,   213,  1263,  1284,    81,  1249,  1248,    35,
    1255,    35,   368,   217,  1259,    36,  1287,    36,  1368,  1369,
    1370,  1371,    82,  1372,  1282,  1470,  1373,    83,  1065,    84,
    1423,     3,  1429,  1434,     4,  1440,     5,  1283,  1285,    37,
    1042,    37,  1290,  1374,   213,   889,  1678,  1296,  1304,   218,
    1515,  1305,  1306,   364,  1321,  1329,     6,     7,     8,     9,
    1407,   707,   757,   708,  1403,   709,   710,  1413,  1404,   535,
    1405,   536,  1408,   711,   712,  1420,  1409,  1426,   223,   364,
    1660,   290,   291,   292,  1460,  1461,   295,   220,  1445,   537,
    1450,  1375,  1456,  1446,   213,  1467,   217,   538,   539,   540,
     541,  1524,  1459,  1510,  1472,  1473,   713,  1474,  1475,   213,
    1479,  1518,  1519,  1520,  1521,  1522,  1524,  1477,  1491,  1492,
     364,  1502,   217,  1516,  1517,  1547,   213,   904,  1527,  1548,
    1549,  1552,   150,   151,   152,   218,  1531,   218,  1557,  1555,
    1556,  1558,  1568,  1569,  1601,  1595,  1608,  1352,  1360,  1378,
    1388,  1610,  1613,  1617,   730,   730,   739,  1621,   611,  1622,
    1627,  1625,  1640,   217,  1664,   224,  1574,  1584,  1591,   612,
     218,   613,  1655,   220,   221,   220,  1042,   213,  1670,  1376,
    1672,  1674,  1679,  1681,  1683,  1495,  1497,  1497,  1500,   614,
     461,  1685,  1688,   615,  1691,  1703,   616,  1737,  1353,  1361,
    1379,  1389,   364,  1740,  1692,    18,    19,  1741,   220,  1744,
     213,   223,   214,   217,   382,   513,   514,  1575,  1585,  1592,
    1614,   381,  1693,   515,   516,   517,   518,   519,   217,  1745,
    1771,     3,  1668,  1694,     4,  1776,     5,   757,   891,   382,
    1695,  1699,  1673,  1700,   617,   217,   381,  1701,  1780,  1675,
    1702,  1729,  1659,   218,    34,  1377,     6,     7,     8,     9,
     221,  1753,   221,    35,  1754,   225,  1755,  1796,  1800,    36,
    1801,  1392,  1642,  1393,  1643,  1644,  1804,   618,   619,   218,
    1821,    70,     3,  1554,  1398,     4,  1706,     5,  1647,   927,
    1820,   220,  1803,    37,  1649,   221,   217,  1705,   224,  1756,
    1651,  1759,  1758,  1654,   729,   729,  1757,     6,     7,     8,
       9,  1748,  1797,  1574,  1584,  1591,   406,   220,  1499,   412,
     218,   924,  1392,  1486,  1393,  1078,  1091,   213,  1624,   217,
    1615,   749,  1231,  1598,  1739,  1677,   757,  1123,   226,  1676,
     891,   891,   891,   891,   891,   214,   213,   891,   926,  1722,
     889,  1727,  1747,  1293,  1793,  1781,  1294,  1312,   220,   558,
     620,   559,  1295,  1129,  1575,  1585,  1592,  1315,   213,  1195,
     218,   891,   728,  1331,   691,  1704,  1690,   213,   221,   560,
    1135,  1275,  1452,   915,  1524,   218,  1468,   561,   562,   938,
     563,   891,   936,   939,   455,  1822,   223,   896,   225,   937,
     564,   565,   218,   364,   221,  1723,   997,  1728,   220,   737,
       3,     0,   741,     4,   742,     5,  1730,  1731,  1732,  1733,
    1734,  1735,  1736,   220,  1738,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   213,     6,     7,     8,     9,     0,
     220,  1524,     0,     0,     0,   221,   217,     0,     0,     0,
       0,     0,     0,   218,  1795,     0,     0,  1764,     0,  1766,
    1767,  1768,  1769,  1770,     0,   217,     0,     0,  1727,     0,
       0,   226,  1000,  1001,     0,     0,   213,     0,  1394,     0,
       0,     0,   223,   224,   223,  1002,   218,   217,     0,     0,
    1659,   220,     0,  1003,     0,   221,   217,  1336,  1360,  1378,
    1388,     0,     0,   463,     0,  1422,  1428,  1433,  1439,  1004,
     221,     0,  1798,     0,  1799,     0,     0,   223,    18,    19,
       0,  1588,     0,     0,   220,     0,     0,   221,  1807,  1394,
     214,  1808,  1809,  1810,  1811,  1812,  1574,  1584,  1591,  1816,
    1817,  1818,  1819,     0,     0,     0,     0,     0,  1337,  1361,
    1379,  1389,   364,   217,  1567,  1823,  1423,  1429,  1434,  1440,
       0,     0,  1824,  1825,  1826,     3,     0,    34,     4,   224,
       5,   224,     0,     0,     0,     0,    35,     0,   221,     0,
       0,     0,    36,   225,     0,     0,     0,  1575,  1585,  1592,
       6,     7,     8,     9,     0,   217,  1005,  1006,  1007,   670,
     223,     0,     0,   218,   224,  1786,    37,     0,     0,     0,
       0,   221,   680,   681,   682,     0,   214,     0,   214,     0,
       3,  1271,   218,     4,     0,     5,   223,     0,     0,     0,
       0,   891,   891,   891,   891,   891,   891,   891,     0,   891,
     891,   220,     0,  1589,   218,     6,     7,     8,     9,     0,
       0,   214,     3,   218,   905,     4,   226,     5,     3,  1367,
     220,     4,     0,     5,   905,   905,     0,   223,     0,   225,
       0,   225,     0,     0,     0,     0,  1588,     6,     7,     8,
       9,     0,   220,     6,     7,     8,     9,   224,     0,     0,
       0,   220,     0,     0,   916,     0,     0,     0,     3,     0,
       0,     4,     0,     5,   225,     0,  1368,  1369,  1370,  1371,
     218,  1372,     0,   224,  1373,   757,     0,   223,  1338,  1355,
    1365,  1381,  1391,     6,     7,     8,     9,     0,   221,     0,
       0,  1374,   223,  1590,   214,     0,     3,     0,     0,     4,
       0,     5,   226,  1570,   226,     0,     0,   221,   220,   223,
     891,     0,   218,     0,   224,     0,     0,     0,   891,     0,
     214,     6,     7,     8,     9,     0,     0,     0,     3,   221,
       0,     4,   916,     5,     0,     0,     0,   368,   221,  1375,
       0,     0,  1571,  1424,     0,  1430,  1435,   225,  1441,     0,
     220,     0,     0,     6,     7,     8,     9,     0,  1589,     0,
     223,   214,   891,     3,   224,     0,     4,     0,     5,  1588,
       0,     0,     0,   225,   270,   271,   272,   273,     3,   224,
       0,     4,     0,     5,     0,  1271,     0,     0,     6,     7,
       8,     9,     0,   223,     0,   221,   224,     0,     0,     0,
       0,     0,  1367,     6,     7,     8,     9,     0,   388,     0,
       0,   214,     0,     0,   225,     0,   398,   399,   400,   401,
     368,     0,     0,   404,     0,     0,   214,  1376,     0,     0,
     757,     0,   425,   427,   429,   431,     0,   221,     0,   434,
       0,     0,     0,   214,     0,  1572,   368,   224,  1662,  1368,
    1369,  1370,  1371,     0,  1372,   456,     0,  1373,     0,     0,
     465,   466,   467,     0,   225,   470,     0,     0,   475,     0,
       0,     0,     3,     0,  1374,     4,     0,     5,     0,   225,
     224,     0,     0,     0,     0,   757,     0,   368,     0,     0,
       0,  1589,     0,     0,   214,     0,   225,     6,     7,     8,
       9,     0,     0,  1561,   468,     0,     0,     0,     0,     0,
     223,  1355,  1365,  1381,  1391,     0,     0,   757,     0,    18,
      19,     0,  1375,   757,     0,     0,     0,   214,     0,   223,
    1576,  1586,  1593,     0,     0,  1813,     0,   226,     0,     0,
       0,  1335,   471,     0,     0,     3,     0,   225,     4,     0,
       5,   223,   226,     0,     0,     0,     0,    18,    19,     0,
     223,     3,     0,   757,     4,     0,     5,     0,    34,   368,
       6,     7,     8,     9,     0,     0,     0,    35,     0,     0,
     225,  1815,     0,    36,     0,     0,     6,     7,     8,     9,
       0,     0,  1025,     0,     0,     0,     0,   224,     0,     0,
    1382,   757,   715,   716,   717,     0,    34,    37,   905,     3,
    1376,     0,     4,     0,     5,    35,   224,   223,     0,  1782,
     226,    36,     0,     0,     0,     0,   473,  1022,     0,     0,
       0,     0,  1578,   757,     6,     7,     8,     9,   224,  1579,
       0,    18,    19,     0,   214,    37,     0,   224,  1383,  1103,
    1384,  1427,  1372,   226,     0,  1373,     0,     0,     0,   223,
       0,     0,     0,   214,     0,     0,     0,   891,   757,     0,
       0,     0,  1385,     0,     0,  1580,     0,  1576,  1586,  1593,
       0,  1709,     0,   757,     0,   214,  1784,     0,     0,     0,
      34,     0,     0,     0,   214,     0,  1578,   225,  1532,    35,
       0,  1790,     0,  1579,   224,    36,     0,     0,     0,  1581,
     905,   905,   905,   905,   905,     0,   225,   905,     0,     0,
    1386,     0,  1533,  1534,     0,     0,     0,     0,     0,    37,
     933,   934,   935,     0,     0,     0,  1025,     0,   225,  1580,
       0,   905,     0,   590,     0,     0,   224,   225,     0,     0,
       0,   214,   591,     0,     0,     0,     0,     0,     0,   948,
       3,   905,     0,     4,     0,     5,     0,   592,     0,     0,
     368,   593,     0,  1581,     0,   594,   595,   757,  1582,     0,
     596,   597,   598,   599,   600,     6,     7,     8,     9,   226,
     956,     0,     0,   214,     0,  1791,     0,     0,     0,     0,
       0,     0,     0,     0,   225,     0,  1535,     0,     0,     0,
       0,   226,     0,     0,     0,     0,     0,     0,     0,     0,
     226,    88,     0,     0,     0,     0,  1536,  1537,     0,    89,
       0,    90,     0,    91,     0,     0,    92,    93,    94,     0,
      95,     0,  1582,     0,  1710,     0,   225,  1578,     0,     0,
     757,     0,     0,     0,  1579,     0,     0,     0,     0,     0,
    1711,  1338,  1365,  1381,  1391,  1712,   757,  1713,  1583,  1424,
    1430,  1435,  1441,     0,     0,     0,     0,   226,     0,     0,
       0,     0,     0,     0,  1785,     0,     0,     0,     0,     0,
    1580,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1576,  1586,  1593,     0,     0,     0,     0,     0,     0,     0,
      10,     0,     0,     0,   757,     0,     0,     0,    11,   368,
      12,     0,    13,     0,  1581,    14,    15,    16,     0,    17,
       0,     0,  1661,    18,    19,     0,     0,     0,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    50,
      50,    64,    64,    64,    68,     0,     0,    50,  1103,  1103,
    1103,  1103,  1103,     0,  1103,  1103,     0,     0,     0,     0,
       0,     0,     0,  1308,  1308,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,  1582,     0,     0,     0,    36,     0,     0,
       0,   905,   905,   905,   905,   905,   905,   905,    50,   905,
     905,   389,    50,    64,    64,    64,    68,     0,    96,     0,
       0,    37,     0,    50,     0,   403,   407,   409,    50,   413,
      64,    64,   418,    97,   403,   403,   403,   403,     0,    64,
       0,     0,   435,     0,    50,     0,     0,    64,    64,    98,
      68,     0,     0,    64,    99,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,   757,     0,     0,     0,   777,
       0,     0,   476,    50,    64,    64,     0,     0,    64,     0,
      50,   984,     0,  1814,   985,   986,   987,   988,   989,   990,
     991,   992,   993,   994,   995,     0,     0,     0,     0,     0,
       0,     0,   150,   151,   152,     0,     0,    38,     0,   870,
       0,     0,     0,   871,     0,     0,     0,   872,     0,     0,
     905,     0,    39,   873,     0,     0,     0,   784,   905,     3,
       0,     0,     4,  -854,     5,  -854,     0,     0,    40,     0,
       0,     0,     0,    41,     0,    42,     0,   876,     0,     0,
       0,   145,     0,     0,     6,     7,     8,     9,   146,   147,
     548,   549,   284,   148,   285,     0,     0,     0,     0,     0,
       0,     0,   905,     0,   550,     0,   551,   552,   553,   286,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   287,
     288,     0,     0,     0,   289,     0,     0,     0,     0,   554,
     555,   556,     0,     0,     0,   290,   291,   292,   293,   294,
     295,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1356,     0,     0,     0,   296,     0,   297,     0,     0,   149,
     150,   151,   152,     0,     0,   153,     0,   154,     0,     0,
    1357,   155,     0,   787,     0,   156,   788,   789,     0,  -854,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,     0,     0,   160,     0,     0,     0,     0,
     161,     0,     0,   162,   791,   792,   163,   164,  1358,     0,
       0,   165,     0,     0,   166,     0,   167,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -854,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   168,
     169,     0,   170,   171,   172,   173,     0,     0,   209,     0,
       0,   174,   175,     0,     0,   176,   177,   298,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   300,   950,     0,     0,
       0,     0,     0,     0,    64,     0,   301,     0,     0,     0,
       0,     0,   302,     0,   957,     0,   958,   303,   959,     0,
     960,     0,     0,     0,     0,   961,   201,   202,   962,   304,
     963,     0,   305,   306,   307,   308,     0,     0,    64,   309,
       0,     0,     0,   310,   311,   203,     0,     0,     0,   204,
     205,     0,     3,     0,   757,     4,     0,     5,   312,     0,
       0,   206,   207,     0,     0,     0,     0,     0,     0,     0,
       0,   313,  1359,   208,   145,     0,   209,     6,     7,     8,
       9,   146,   147,     0,     0,   284,   148,   285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   905,     0,     0,
       0,     0,   286,     0,   521,   522,     0,     0,   523,     0,
       0,     0,   287,   288,     0,     0,     0,   289,   524,   525,
     526,   527,   528,   529,   530,   531,   532,     0,   290,   291,
     292,   293,   294,   295,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1356,     0,     0,     0,   296,     0,   297,
       0,     0,   149,   150,   151,   152,     0,     0,   153,     0,
     154,     0,     0,  1357,   155,     0,     0,   533,   156,     0,
       0,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,   159,     0,     0,   160,     0,
       0,     0,     0,   161,     0,     0,   162,     0,     0,   163,
     164,  1358,     0,     0,   165,     0,     0,   166,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,   169,     0,   170,   171,   172,   173,     0,
       0,     0,     0,     0,   174,   175,     0,     0,   176,   177,
     298,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,     0,     0,   299,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   300,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   301,
       0,     0,     0,     0,     0,   302,     0,     0,     0,     0,
     303,     0,     0,     0,     0,     0,     0,     0,     0,   201,
     202,     0,   304,     0,     0,   305,   306,   307,   308,     0,
       0,     0,   309,     0,     0,     0,   310,   311,   203,     0,
       0,     0,   204,   205,     0,     0,     0,   757,     0,     0,
       0,   312,     0,     3,   206,   207,     4,     0,     5,     0,
       0,     0,     0,     0,   313,  1560,   208,     0,     0,   209,
       0,     0,     0,     0,     0,   145,     0,     0,     6,     7,
       8,     9,   146,   147,     0,     0,   284,   148,   285,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   286,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   287,   288,     0,     0,     0,   289,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   290,
     291,   292,   293,   294,   295,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1356,     0,     0,     0,   296,     0,
     297,     0,     0,   149,   150,   151,   152,     0,     0,   153,
       0,   154,     0,     0,  1357,   155,     0,     0,     0,   156,
       0,     0,     0,     0,     0,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,     0,     0,     0,   159,     0,     0,   160,
    1191,  1192,  1193,     0,   161,     0,     0,   162,     0,     0,
     163,   164,  1358,     0,     0,   165,     0,     0,   166,     0,
     167,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   168,   169,     0,   170,   171,   172,   173,
       0,     0,     0,     0,     0,   174,   175,     0,     0,   176,
     177,   298,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,     0,     0,   299,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     300,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     301,     0,     0,     0,     0,     0,   302,     0,     0,     0,
       0,   303,     0,     0,     0,     4,     0,     5,     0,     0,
     201,   202,     0,   304,     0,     0,   305,   306,   307,   308,
       0,     0,     0,   309,   145,     0,     0,   310,   311,   203,
       0,   146,   147,   204,   205,   284,   148,   285,   757,     0,
       0,     0,   312,     0,     0,   206,   207,     0,     0,     0,
       0,     0,   286,     0,     0,   313,  1783,   208,     0,     0,
     209,     0,   287,   288,     0,     0,     0,   289,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   290,   291,
     292,   293,   294,   295,     0,  -853,     0,  -853,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   296,     0,   297,
       0,     0,   149,   150,   151,   152,     0,     0,   153,     0,
     154,     0,   521,   522,   155,     0,   523,     0,   156,     0,
       0,     0,     0,     0,   157,     0,   524,   525,   526,   527,
     528,   529,   530,   531,   532,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,   159,     0,     0,   160,     0,
       0,     0,     0,   161,     0,     0,   162,     0,     0,   163,
     164,     0,     0,     0,   165,     0,     0,   166,     0,   167,
       0,     0,     0,     0,     0,   533,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,   169,     0,   170,   171,   172,   173,     0,
       0,  -853,     0,     0,   174,   175,     0,     0,   176,   177,
     298,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,     0,     0,   299,     0,     0,     0,     0,     0,
       0,     0,   775,     0,     0,     0,     0,     0,     0,   300,
       0,     0,     0,     0,     0,     0,     0,     0,   776,   301,
     145,  -853,     0,     0,     0,   302,     0,     0,   147,     0,
     303,     0,   148,     0,     0,     0,     0,     0,     0,   201,
     202,     0,   304,     0,     0,   305,   306,   307,   308,     0,
       0,     0,   309,     0,     0,     0,   310,   311,   203,     0,
       0,     0,   204,   205,     0,     0,   777,     0,     0,     0,
       0,   312,     0,     0,   206,   207,     0,     0,     0,     0,
     778,     0,   779,     0,   313,  1469,   208,     0,     0,   209,
       0,     0,     0,     0,     0,     0,     0,     0,   149,   150,
     151,   152,     0,     0,   153,     0,   780,     0,     0,     0,
     781,     0,     0,     0,   782,     0,     0,     0,     0,     0,
     783,     0,     0,     0,   784,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   158,     0,     0,     0,
       0,   159,     0,     0,   785,     0,     0,     0,     0,   161,
       0,     0,   162,     0,     0,   163,   164,     0,     0,     0,
     165,     0,     0,   166,     0,   167,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   168,   169,
       0,   786,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,     0,     0,
     200,  1034,     0,     0,     0,     0,     0,     0,     0,     0,
     787,     0,     0,   788,   789,     0,     0,   776,     0,   145,
       0,     0,     0,     0,     0,     0,   790,   147,     0,     0,
       0,   148,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,   202,     0,     0,     0,
       0,   791,   792,     0,     0,     0,     0,     0,   652,     0,
       0,     0,     0,     0,   203,   777,     0,     0,   204,   205,
       0,     0,     0,     0,     0,     0,     0,     0,   793,   794,
       0,   658,     0,     0,   653,     0,     0,   654,     0,     0,
       0,     0,   795,     0,     0,   209,     0,   149,   150,   151,
     152,     0,     0,   153,   655,   780,     0,     0,     0,   781,
       0,     0,     0,   782,     0,     0,     0,     0,     0,  1035,
       0,     0,     0,   784,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   158,     0,     0,     0,     0,
     159,     0,     0,  1036,     0,     0,     0,     0,   161,     0,
       0,   162,     0,     0,   163,   164,     0,     0,     0,   165,
       0,     0,   166,     0,   167,     0,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   168,   169,     0,
     786,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   656,     0,   200,
    1097,     0,     0,     0,   201,   202,     0,     0,     0,   787,
       0,     0,   788,   789,   657,     0,   776,     0,   145,     0,
       0,     0,     0,     0,     0,     0,   147,     0,     0,     0,
     148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     658,     0,     0,     0,   201,   202,     0,     0,     0,     0,
     791,   792,     0,     0,     0,     0,     0,   736,     0,     0,
       0,     0,     0,   203,   777,     0,     0,   204,   205,     0,
       0,     0,     0,     0,     0,     0,     0,   793,   794,     0,
     658,     0,     0,   653,     0,     0,   654,     0,     0,     0,
       0,   795,     0,     0,   209,     0,   149,   150,   151,   152,
       0,     0,   153,   655,   780,     0,     0,     0,   781,     0,
       0,     0,   782,     0,     0,     0,     0,     0,  1035,     0,
       0,     0,   784,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   158,     0,     0,     0,     0,   159,
       0,     0,  1036,     0,     0,     0,     0,   161,     0,     0,
     162,     0,     0,   163,   164,     0,     0,     0,   165,     0,
       0,   166,     0,   167,     0,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   168,   169,     0,   786,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   656,     0,   200,  1126,
       0,     0,     0,   201,   202,     0,     0,     0,   787,     0,
       0,   788,   789,   657,     0,   776,     0,   145,     0,     0,
       0,     0,     0,     0,     0,   147,     0,     0,     0,   148,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   658,
       0,     0,     0,   201,   202,     0,     0,     0,     0,   791,
     792,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   203,   777,     0,     0,   204,   205,     0,     0,
       0,     0,     0,     0,     0,     0,   793,   794,     0,   658,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     795,     0,     0,   209,     0,   149,   150,   151,   152,     0,
       0,   153,     0,   780,     0,     0,     0,   781,     0,     0,
       0,   782,     0,     0,     0,     0,     0,  1035,     0,     0,
       0,   784,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158,     0,     0,     0,     0,   159,     0,
       0,  1036,     0,     0,     0,     0,   161,     0,     0,   162,
       0,     0,   163,   164,     0,     0,     0,   165,     0,     0,
     166,     0,   167,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   168,   169,     0,   786,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,     0,     0,   200,  1238,     0,
       0,     0,     0,     0,     0,     0,     0,   787,     0,     0,
     788,   789,     0,     0,   776,     0,   145,     0,     0,     0,
       0,     0,     0,     0,   147,     0,     0,     0,   148,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   201,   202,     0,     0,     0,     0,   791,   792,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,   777,     0,     0,   204,   205,     0,     0,     0,
       0,     0,     0,     0,     0,   793,   794,     0,   658,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   795,
       0,     0,   209,     0,   149,   150,   151,   152,     0,     0,
     153,     0,   780,     0,     0,     0,   781,     0,     0,     0,
     782,     0,     0,     0,     0,     0,  1035,     0,     0,     0,
     784,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,   159,     0,     0,
    1036,     0,     0,     0,     0,   161,     0,     0,   162,     0,
       0,   163,   164,     0,     0,     0,   165,     0,     0,   166,
       0,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   168,   169,     0,   786,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,     0,     0,   200,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   787,     0,     0,   788,
     789,   864,   865,   866,   867,   868,   869,     0,     0,     0,
       0,     0,     0,   776,     0,   849,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,   202,     0,     0,     0,     0,   791,   792,     0,
     738,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     203,     0,     0,     0,   204,   205,     0,     0,     0,     0,
       0,   777,   662,   663,   793,   794,   664,   658,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   795,     0,
       0,   209,     0,   665,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,   150,   151,   152,     0,     0,     0,
       0,   870,     0,     0,     0,   871,     0,     0,     0,   872,
       0,     0,     0,     0,     0,   873,     0,     0,     0,   784,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   874,     0,     0,     0,     0,   875,     0,   739,   876,
       0,     0,     0,     0,   877,     0,     0,   878,     0,     0,
     879,   880,     0,     0,     0,   881,     0,     0,   882,     0,
     883,     0,   666,   776,     0,   145,     0,     0,     0,     0,
       0,     0,     0,   147,     0,     0,     0,   148,     0,     0,
       0,     0,     0,   884,   885,     0,   667,   668,   669,   670,
     671,   672,   740,   673,   674,   675,   676,   677,   678,   679,
       0,     0,   680,   681,   682,     0,     0,     0,     0,     0,
       0,   777,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   683,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   787,     0,     0,   788,   789,
       0,     0,     0,   149,   150,   151,   152,     0,     0,   153,
       0,   780,     0,     0,     0,   781,     0,     0,     0,   782,
       0,     0,     0,     0,     0,  1035,     0,     0,     0,   784,
       0,     0,     0,     0,   662,   663,   791,   792,   664,   886,
       0,   158,     0,     0,     0,     0,   159,     0,     0,  1036,
       0,     0,     0,     0,   161,   665,     0,   162,     0,     0,
     163,   164,     0,   793,   794,   165,     0,     0,   166,     0,
     167,     0,     0,     0,     0,   313,     0,   887,     0,     0,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   168,   169,     0,   786,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,     0,   666,   200,     0,   776,   910,   849,
       0,     0,     0,     0,     0,   787,     0,     0,   788,   789,
       0,     0,     0,     0,     0,     0,     0,     0,   667,   668,
     669,   670,   671,   672,     0,   673,   674,   675,   676,   677,
     678,   679,     0,     0,   680,   681,   682,     0,     0,     0,
     201,   202,     0,     0,     0,   777,   791,   792,     0,     0,
       0,     0,     0,     0,     0,   683,     0,     0,     0,   203,
       0,     0,     0,   204,   205,     0,     0,     0,   776,     0,
     849,     0,     0,   793,   794,     0,   658,   149,   150,   151,
     152,     0,     0,     0,     0,   870,     0,   795,     0,   871,
     209,     0,     0,   872,     0,     0,     0,     0,     0,   873,
       0,     0,     0,   784,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   874,   777,     0,     0,     0,
     875,     0,     0,   876,     0,     0,     0,     0,   877,     0,
       0,   878,     0,     0,   879,   880,     0,     0,     0,   881,
       0,     0,   882,     0,   883,     0,     0,     0,   149,   150,
     151,   152,     0,     0,     0,     0,   870,     0,     0,     0,
     871,     0,     0,     0,   872,     0,     0,   884,   885,     0,
     873,     0,     0,     0,   784,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   874,     0,     0,     0,
       0,   875,     0,     0,   876,     0,     0,     0,     0,   877,
       0,     0,   878,     0,     0,   879,   880,     0,     0,     0,
     881,     0,     0,   882,     0,   883,     0,     0,     0,   787,
       0,     0,   788,   789,     0,     0,     0,     0,     0,     0,
       0,   776,     0,     0,     0,     0,     0,     0,   884,   885,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     791,   792,     0,   886,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   777,
       0,     0,     0,     0,     0,     0,     0,   793,   794,     0,
     787,     0,     0,   788,   789,     0,     0,     0,     0,   911,
       0,   887,   776,     0,   209,     0,     0,     0,     0,     0,
       0,   149,   150,   151,   152,     0,     0,     0,     0,   870,
       0,     0,     0,   871,     0,     0,     0,   872,     0,     0,
       0,   791,   792,   873,   886,     0,     0,   784,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   874,
     777,     0,     0,     0,   875,     0,     0,   876,   793,   794,
       0,     0,   877,     0,     0,   878,     0,     0,   879,   880,
     313,     0,   887,   881,     0,   209,   882,     0,   883,     0,
       0,     0,   149,   150,   151,   152,     0,     0,     0,     0,
     870,     0,     0,     0,   871,     0,     0,     0,   872,     0,
       0,   884,   885,     0,   873,     0,     0,     0,   784,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     874,     0,     0,     0,     0,   875,     0,     0,   876,     0,
       0,     0,     0,   877,     0,     0,   878,     0,     0,   879,
     880,     0,     0,     0,   881,     0,     0,   882,     0,   883,
       0,     0,     0,   787,     0,     0,   788,   789,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   884,   885,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   791,   792,     0,   886,     0,     0,
       0,   145,     0,     0,     0,     0,     0,     0,   146,   147,
       0,     0,   284,   148,   285,     0,     0,     0,     0,     0,
       0,   793,   794,     0,   787,     0,     0,   788,   789,   286,
       0,     0,     0,   313,     0,   887,     0,     0,   209,   287,
     288,     0,     0,     0,   289,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   290,   291,   292,   293,   294,
     295,     0,     0,     0,     0,   791,   792,     0,   886,     0,
       0,     0,     0,     0,   296,     0,   297,     0,     0,   149,
     150,   151,   152,     0,     0,   153,     0,   154,     0,     0,
       0,   155,   793,   794,     0,   156,     0,     0,     0,     0,
       0,   157,     0,     0,     0,     0,   887,     0,     0,   209,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,     0,     0,   160,     0,     0,     0,     0,
     161,     0,     0,   162,     0,     0,   163,   164,     0,     0,
       0,   165,     0,     0,   166,     0,   167,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   168,
     169,     0,   170,   171,   172,   173,     0,     0,     0,     0,
       0,   174,   175,     0,     0,   176,   177,   298,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   300,     0,     0,     0,
       0,   145,     0,     0,     0,     0,   301,     0,   146,   147,
       0,     0,   302,   148,     0,     0,     0,   303,     0,     0,
       0,     0,     0,     0,     0,     0,   201,   202,     0,   304,
       0,     0,   305,   306,   307,   308,     0,     0,     0,   309,
       0,     0,     0,   310,   311,   203,     0,     0,     0,   204,
     205,     0,     0,     0,     0,     0,     0,     0,   312,     0,
       0,   206,   207,     0,     0,     0,     0,     0,     0,     0,
       0,   313,     0,   208,     0,     0,   209,     0,     0,   149,
     150,   151,   152,     0,     0,   153,     0,   154,     0,     0,
       0,   155,     0,     0,     0,   156,     0,     0,     0,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,     0,     0,   160,     0,     0,     0,     0,
     161,     0,     0,   162,     0,     0,   163,   164,     0,     0,
       0,   165,     0,     0,   166,     0,   167,     0,     0,     0,
       0,     0,     0,   145,     0,     0,     0,     0,     0,     0,
     146,   147,     0,     0,     0,   148,     0,     0,     0,   168,
     169,     0,   170,   171,   172,   173,     0,     0,     0,     0,
       0,   174,   175,     0,     0,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,   200,     0,     0,     0,  1707,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   150,   151,   152,     0,     0,   153,     0,   154,
       0,     0,     0,   155,     0,     0,     0,   156,     0,     0,
       0,     0,     0,   157,     0,     0,   201,   202,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
       0,     0,     0,     0,   159,   203,     0,   160,     0,   204,
     205,     0,   161,     0,     0,   162,     0,     0,   163,   164,
       0,   206,   207,   165,     0,     0,   166,     0,   167,     0,
       0,   313,     0,   208,     0,   145,   209,     0,     0,     0,
       0,     0,   146,   147,     0,     0,     0,   148,     0,     0,
       0,   168,   169,     0,   170,   171,   172,   173,     0,     0,
       0,     0,     0,   174,   175,     0,     0,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,     0,     0,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,   150,   151,   152,     0,     0,   153,
       0,   154,     0,     0,     0,   155,     0,     0,     0,   156,
       0,     0,     0,     0,     0,   157,     0,     0,   201,   202,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,     0,     0,     0,   159,   203,     0,   160,
       0,   204,   205,     0,   161,     0,     0,   162,     0,     0,
     163,   164,     0,   206,   207,   165,     0,     0,   166,     0,
     167,     0,     0,     0,     0,   208,     0,     0,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   168,   169,     0,   170,   171,   172,   173,
       0,     0,     0,     0,     0,   174,   175,     0,     0,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,     0,     0,   200,     0,     0,     0,   145,
       0,     0,     0,     0,     0,     0,     0,   147,     0,     0,
       0,   148,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     201,   202,     0,     0,     0,   777,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   203,
       0,     0,     0,   204,   205,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   206,   207,   149,   150,   151,
     152,     0,     0,   153,     0,   780,     0,   208,     0,   781,
     209,     0,     0,   782,     0,     0,     0,     0,     0,  1035,
       0,     0,     0,   784,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   158,     0,     0,     0,     0,
     159,     0,     0,  1036,     0,     0,     0,     0,   161,     0,
       0,   162,     0,     0,   163,   164,     0,     0,     0,   165,
       0,     0,   166,     0,   167,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   168,   169,     0,
     786,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,     0,     0,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   787,
       0,     0,   788,   789,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   201,   202,     0,     0,     0,     0,
     791,   792,     0,     0,     0,     0,     2,     3,     0,     0,
       4,     0,     5,   203,     0,     0,     0,   204,   205,     0,
       0,     0,     0,     0,     0,     0,     0,   793,   794,     0,
     658,     0,     6,     7,     8,     9,     0,     0,     0,     0,
       0,   795,    10,     0,   209,     0,     0,     0,     0,     0,
      11,     0,    12,     0,    13,     0,     0,    14,    15,    16,
       0,    17,     0,     0,     0,    18,    19,    20,     0,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,     0,   777,     0,     0,     0,     0,     0,
       0,     0,   290,   291,   292,  1460,  1461,   295,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -335,     0,
       0,     0,     0,     0,    34,     0,   149,   150,   151,   152,
       0,     0,     0,    35,   870,     0,     0,     0,   871,    36,
       0,     0,   872,     0,     0,     0,     0,     0,   873,     0,
       0,     0,   784,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,   874,     0,     0,     0,     0,   875,
       0,     0,   876,     0,     0,     0,     0,   877,     0,     0,
     878,     0,     0,   879,   880,     0,     0,     0,   881,     0,
       0,   882,   777,   883,   104,     0,     0,     0,     0,     0,
       0,     0,   105,   106,   107,   108,     0,     0,   109,   110,
       0,   111,   112,   113,     0,   114,   884,   885,     0,     0,
       0,     0,     0,     0,   149,   150,   151,   152,     0,     0,
       0,     0,   870,     0,     0,     0,   871,     0,     0,     0,
     872,     0,     0,     0,     0,     0,   873,     0,     0,    38,
     784,     0,     0,     0,   115,     0,   116,   117,   118,     0,
       0,     0,   874,     0,    39,     0,     0,   875,   787,     0,
     876,   788,   789,     0,     0,   877,     0,     0,   878,     0,
      40,   879,   880,     0,     0,    41,   881,    42,     0,   882,
       0,   883,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   791,
     792,     0,   886,     0,   884,   885,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   793,   794,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     887,     0,     0,   209,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   787,     0,     0,   788,
     789,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   120,   791,   792,     0,
     886,   121,   122,   123,   124,     0,     0,     0,     0,     0,
       0,     0,   125,     0,     0,     0,     0,   126,     0,   127,
     128,     0,     0,     0,   793,   794,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   887,     0,
       0,   209
};

static const yytype_int16 yycheck[] =
{
       1,   319,     3,    66,   294,   394,   391,    30,   374,    52,
      66,   204,   316,   392,    30,   360,   106,   393,   108,   109,
      63,   346,   112,   340,   114,   370,   371,   117,   118,    52,
     419,   121,   122,   123,   124,   208,   360,   416,   128,   721,
      63,   131,   132,   284,   754,    46,   370,   371,    32,   139,
    1169,     1,  1176,    54,   433,  1066,  1067,    58,   360,  1173,
    1175,  1072,  1174,  1132,  1266,  1189,  1234,  1217,  1218,     4,
     311,  1405,   390,  1403,  1382,   757,  1404,     4,  1385,     7,
     795,  1242,     5,     7,   766,    23,     7,     7,   770,  1134,
     858,     5,   333,     1,   859,    37,     4,   860,     6,    44,
      95,     7,     8,     9,   102,    52,   862,  1268,  1269,   102,
      15,    16,    22,   718,   360,   721,    63,    56,    26,    27,
      28,    29,    23,    23,   370,   371,    30,  1318,   101,    77,
      78,  1142,   856,   857,   720,    32,    33,   102,   103,   104,
     143,  1244,    48,   102,    50,   123,   102,   124,    52,   719,
     102,   103,   104,    59,    88,  1580,   265,    91,    64,    63,
      76,    20,    68,    61,    83,    20,    85,   102,   250,   147,
      88,    76,    77,    78,   110,   111,    37,    38,    39,   157,
      83,   204,   684,    57,    83,   208,    57,    92,    93,    94,
     103,   101,   102,   109,   102,   103,   104,   102,   323,    97,
     725,   141,   727,   328,    48,   110,   111,   123,  1369,  1370,
      56,   116,   250,    88,   323,    13,    91,   157,   743,   744,
     123,   746,  1383,   112,   123,   750,   751,    56,   231,   232,
     102,   178,   137,   138,    48,    56,   141,   293,   294,   741,
      88,   323,    52,   102,   147,   108,   109,   102,   147,   112,
     775,   114,   168,   778,   117,   118,   102,   939,   121,   122,
     123,   124,   716,   717,    56,   128,    46,   123,   131,   132,
       8,   255,   249,   102,   210,   211,   139,   261,   214,   288,
     199,   102,  1401,    30,  1040,   323,    56,   143,    86,   298,
     346,   147,   251,   316,   267,   251,     8,   360,   102,    83,
     204,   217,    88,   209,   208,    52,   323,   370,   371,    83,
     102,   314,  1737,   210,   839,    53,    63,   842,   322,   233,
     125,    30,   240,   184,   242,   214,   215,   323,   323,   392,
     328,   936,   102,   939,   248,   328,   392,   360,   316,   257,
     259,    53,  1650,    52,   387,   150,  1653,   370,   371,  1452,
     264,   298,   938,   416,    63,   269,  1112,    44,   448,   402,
     416,  1043,  1044,   328,   387,   304,   305,   937,   322,   316,
     433,   323,   306,   248,    88,   231,   232,   433,   323,   402,
     328,   323,  1150,   908,   909,   323,  1151,   293,   294,  1152,
     328,   297,   240,   328,   242,  1110,   324,   324,   306,  1707,
     324,   324,  1709,   324,   324,  1450,   130,   112,    30,   754,
     324,   321,   316,    88,  1483,   299,   324,  1578,   328,  1569,
    1622,  1755,   323,  1753,  1148,  1149,  1754,   328,   328,    79,
      52,   306,  1623,   307,   308,   309,   307,   308,   309,   199,
     387,    63,  1610,     1,   112,    95,     4,     1,     6,   199,
       4,  1462,     6,   139,   240,   402,   242,   204,   314,   164,
     165,   208,     1,   113,   132,     4,   152,     6,    26,    27,
      28,    29,    26,    27,    28,    29,   125,   145,  1489,   933,
     934,   935,   168,   387,   267,   268,    40,    26,    27,    28,
      29,   160,   809,   308,   948,   204,   102,   403,   402,   208,
     406,   150,   101,   409,   288,   289,   290,   413,   754,  1034,
     101,   109,   418,  1038,   288,   289,   290,   101,   863,   132,
     126,   127,  1047,  1048,  1049,   123,   240,  1052,   242,  1054,
     249,   200,   201,   202,    88,   728,    90,   862,    92,  1064,
     323,    95,   447,   101,  1506,  1507,  1508,  1509,   160,   248,
    1619,   164,   165,  1235,   253,   254,  1266,     8,   112,   249,
     926,   863,   907,   887,  1274,   240,    83,   242,   249,   316,
     269,  1695,  1097,    24,  1099,  1100,   481,   483,  1692,  1694,
     193,  1693,   204,   132,   265,   448,   208,     0,  1113,   109,
    1115,     4,   260,     6,     4,     1,     6,   283,     4,  1124,
       6,  1126,    53,   123,   210,   907,   160,   316,  1318,     4,
     856,   857,   858,   859,   860,   164,   165,   863,   167,   249,
      26,    27,    28,    29,   230,   231,  1347,  1348,  1349,  1350,
      30,     1,  1751,   306,     4,   150,     6,   267,   268,     1,
     387,   887,     4,   282,     6,   160,   161,   259,   260,   261,
     262,   263,    52,   112,    44,   402,    26,    27,    28,    29,
      20,   907,    22,    63,    26,    27,    28,    29,    18,   128,
      40,  1633,  1634,  1635,   133,   134,  1687,    17,   387,    41,
       4,    43,     6,    44,   141,    46,   327,     7,   861,   146,
      51,   754,    53,   402,   316,   101,    57,    12,    44,    45,
      20,     1,    22,   112,     4,   728,     6,    15,    16,   267,
     268,   250,  1237,  1238,    38,  1040,   125,    30,    88,   323,
      90,    51,    92,   132,   328,    95,    26,    27,    28,    29,
     714,   754,  1257,   164,   165,    96,    36,    98,  1263,    52,
     199,   150,   112,   323,    61,    62,    46,   156,   306,    66,
      63,    51,   306,    53,    51,    55,    71,    84,    85,    86,
      75,    88,  1287,  1774,    30,   387,   324,   306,     1,    56,
     324,     4,   795,     6,  1015,    90,    91,   320,   321,  1304,
     402,  1306,  1503,  1504,  1505,   324,    52,  1112,   300,   323,
     160,   303,   107,    26,    27,    28,    29,    63,     5,   323,
     863,     8,   194,    36,   204,   128,   862,   323,   208,   132,
    1127,   203,   204,    46,   163,   207,   208,    30,    51,   168,
      53,   136,    55,  1147,   728,   250,   251,     5,   143,  1153,
       8,  1155,  1156,   856,   857,   858,   859,   860,   861,    52,
     863,   164,   165,   323,   907,   250,     1,  1104,  1105,     4,
      63,     6,     1,  1046,  1111,     4,     4,     6,     6,     7,
     160,   267,   268,   112,   887,   114,   115,   116,    59,    60,
     323,    26,    27,    28,    29,   110,   111,    26,    27,    28,
      29,   267,   268,   114,   907,     4,   248,     6,    44,     8,
      30,   204,    41,    22,    43,   208,    25,    44,   129,   125,
     306,  1147,  1148,  1149,  1150,  1151,  1152,  1153,    44,  1155,
    1156,   912,    52,  1623,   915,   141,   316,   108,   324,   150,
    1445,   110,   111,    63,   150,   156,   117,   160,     7,  1274,
     156,   157,   123,   233,  1459,     8,   306,    92,   204,  1132,
     102,  1134,   208,   849,    15,    16,  1250,   853,   248,   110,
     111,     4,  1477,     6,   324,     8,   147,   861,   135,   136,
     137,   138,   324,   124,   264,   126,   127,   128,    20,   269,
      22,   271,   329,  1318,   205,   206,   131,    97,    98,    99,
     100,   728,   267,   268,  1040,    15,    16,   387,   149,   150,
     151,   204,     4,     5,  1311,   208,  1313,   105,   106,   107,
     233,   329,   402,   316,   293,   294,   306,     1,   110,   111,
       4,   299,     6,  1317,   101,   248,   110,   111,   112,   728,
    1266,    93,    94,  1046,   324,   307,   308,   309,  1274,    42,
      43,   264,    26,    27,    28,    29,   269,   299,   271,   276,
     277,   278,   279,   280,    36,   292,   293,   294,   317,  1112,
     316,   326,    44,    23,    46,    23,  1112,  1119,  1120,    51,
      52,    53,    83,    55,   204,    51,    51,    95,   208,   102,
     103,   104,  1318,   306,   387,    51,    51,  1759,  1760,   234,
      51,  1104,  1105,  1106,  1107,  1108,   101,  1110,  1111,   402,
      83,   324,  1617,   323,   360,   101,  1119,  1120,    92,   248,
     128,   101,   101,   316,   370,   371,   728,    17,   327,  1132,
     101,  1134,  1501,  1498,   861,   288,   289,   290,   315,    44,
     101,   387,    83,  1499,  1147,  1148,  1149,  1150,  1151,  1152,
    1153,    83,  1155,  1156,    59,    60,   402,   131,    18,     5,
       7,   101,  1046,     7,  1167,     7,     7,   101,  1527,   323,
       5,   306,   861,     7,     7,     7,   327,   185,   186,   187,
     188,   189,   190,  1164,  1165,  1166,  1167,  1168,  1169,   324,
      17,  1461,    18,  1552,   387,   324,   316,     8,  1496,   101,
     101,   323,     1,   108,   323,     4,    44,     6,    44,   402,
     323,   323,   117,    37,   250,   323,   265,   101,   123,   101,
     101,    59,    60,    59,    60,   101,   101,    26,    27,    28,
      29,  1274,   323,   101,   101,  1165,  1166,  1167,  1168,  1169,
    1167,    40,   147,   101,   101,   101,   300,  1250,  1132,  1230,
    1134,  1232,  1233,  1276,  1235,   323,   101,   323,   323,   861,
     234,   233,   101,  1266,   101,     5,     8,   387,    51,   146,
     108,  1274,   108,  1276,    42,    69,   248,  1450,   101,   117,
     101,   117,   402,  1167,   101,   123,     5,   123,    87,    88,
      89,    90,   264,    92,   112,  1276,    95,   269,  1623,   271,
    1230,     1,  1232,  1233,     4,  1235,     6,   112,   112,   147,
    1483,   147,   326,   112,  1317,  1318,  1600,   101,    83,  1046,
    1356,     8,    83,  1250,   326,   101,    26,    27,    28,    29,
       7,    45,   306,    47,   323,    49,    50,   101,   323,   112,
     323,   114,   330,    57,    58,   251,   330,   101,   728,  1276,
     324,    77,    78,    79,    80,    81,    82,  1046,     5,   132,
     323,   160,   270,   102,  1367,   250,  1250,   140,   141,   142,
     143,  1367,    42,  1354,     7,   102,    90,   102,   102,  1382,
     162,  1362,  1363,  1364,  1365,  1366,  1382,     5,   101,    38,
    1317,   102,  1276,   102,    97,  1376,  1399,  1623,   322,  1380,
    1381,   322,   102,   103,   104,  1132,   101,  1134,   102,  1390,
    1391,   322,   101,   101,   324,   101,   266,  1398,  1399,  1400,
    1401,   101,   101,    83,  1460,  1461,   186,   324,   112,     5,
     101,   184,    41,  1317,   322,   728,  1417,  1418,  1419,   123,
    1167,   125,   148,  1132,  1046,  1134,  1619,  1450,   101,   248,
     101,   103,   266,   101,   251,  1341,  1342,  1343,  1344,   143,
      44,   324,    39,   147,   323,   102,   150,   131,  1398,  1399,
    1400,  1401,  1399,   324,   323,    59,    60,   101,  1167,   101,
    1483,   861,   728,  1367,  1527,   110,   111,  1417,  1418,  1419,
    1471,  1527,   323,   118,   119,   120,   121,   122,  1382,   324,
     101,     1,  1572,   323,     4,   102,     6,   306,   754,  1552,
     323,   323,  1582,   323,   198,  1399,  1552,   323,   250,  1589,
     323,   323,  1558,  1250,   108,   324,    26,    27,    28,    29,
    1132,   323,  1134,   117,   323,   728,   323,   322,   101,   123,
     101,    41,  1523,    43,  1525,  1526,     5,   231,   232,  1276,
     101,    20,     1,  1386,  1172,     4,  1648,     6,  1539,   389,
    1796,  1250,  1774,   147,  1545,  1167,  1450,  1646,   861,  1699,
    1551,  1702,  1701,  1554,  1460,  1461,  1700,    26,    27,    28,
      29,  1691,  1762,  1564,  1565,  1566,    89,  1276,  1343,    91,
    1317,   386,    41,  1316,    43,   763,   771,  1600,  1489,  1483,
    1472,   303,  1025,  1437,  1676,  1597,   306,   830,   728,  1596,
     856,   857,   858,   859,   860,   861,  1619,   863,   388,  1655,
    1623,  1657,  1690,  1106,   324,  1747,  1107,  1125,  1317,   112,
     314,   114,  1108,   845,  1564,  1565,  1566,  1130,  1641,   967,
    1367,   887,   286,  1156,   204,  1641,  1627,  1650,  1250,   132,
     854,  1072,  1251,   371,  1650,  1382,  1272,   140,   141,   400,
     143,   907,   398,   401,   119,  1805,  1046,   360,   861,   399,
     153,   154,  1399,  1600,  1276,  1656,   621,  1658,  1367,   298,
       1,    -1,   299,     4,   299,     6,  1667,  1668,  1669,  1670,
    1671,  1672,  1673,  1382,  1675,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1707,    26,    27,    28,    29,    -1,
    1399,  1707,    -1,    -1,    -1,  1317,  1600,    -1,    -1,    -1,
      -1,    -1,    -1,  1450,  1760,    -1,    -1,  1708,    -1,  1710,
    1711,  1712,  1713,  1714,    -1,  1619,    -1,    -1,  1774,    -1,
      -1,   861,   110,   111,    -1,    -1,  1749,    -1,   248,    -1,
      -1,    -1,  1132,  1046,  1134,   123,  1483,  1641,    -1,    -1,
    1796,  1450,    -1,   131,    -1,  1367,  1650,  1748,  1749,  1750,
    1751,    -1,    -1,    44,    -1,  1756,  1757,  1758,  1759,   147,
    1382,    -1,  1763,    -1,  1765,    -1,    -1,  1167,    59,    60,
      -1,   112,    -1,    -1,  1483,    -1,    -1,  1399,  1779,   248,
    1046,  1782,  1783,  1784,  1785,  1786,  1787,  1788,  1789,  1790,
    1791,  1792,  1793,    -1,    -1,    -1,    -1,    -1,  1748,  1749,
    1750,  1751,  1749,  1707,   324,  1806,  1756,  1757,  1758,  1759,
      -1,    -1,  1813,  1814,  1815,     1,    -1,   108,     4,  1132,
       6,  1134,    -1,    -1,    -1,    -1,   117,    -1,  1450,    -1,
      -1,    -1,   123,  1046,    -1,    -1,    -1,  1787,  1788,  1789,
      26,    27,    28,    29,    -1,  1749,   234,   235,   236,   237,
    1250,    -1,    -1,  1600,  1167,   324,   147,    -1,    -1,    -1,
      -1,  1483,   250,   251,   252,    -1,  1132,    -1,  1134,    -1,
       1,  1068,  1619,     4,    -1,     6,  1276,    -1,    -1,    -1,
      -1,  1147,  1148,  1149,  1150,  1151,  1152,  1153,    -1,  1155,
    1156,  1600,    -1,   234,  1641,    26,    27,    28,    29,    -1,
      -1,  1167,     1,  1650,   360,     4,  1046,     6,     1,    40,
    1619,     4,    -1,     6,   370,   371,    -1,  1317,    -1,  1132,
      -1,  1134,    -1,    -1,    -1,    -1,   112,    26,    27,    28,
      29,    -1,  1641,    26,    27,    28,    29,  1250,    -1,    -1,
      -1,  1650,    -1,    -1,    37,    -1,    -1,    -1,     1,    -1,
      -1,     4,    -1,     6,  1167,    -1,    87,    88,    89,    90,
    1707,    92,    -1,  1276,    95,   306,    -1,  1367,  1165,  1166,
    1167,  1168,  1169,    26,    27,    28,    29,    -1,  1600,    -1,
      -1,   112,  1382,   324,  1250,    -1,     1,    -1,    -1,     4,
      -1,     6,  1132,    92,  1134,    -1,    -1,  1619,  1707,  1399,
    1266,    -1,  1749,    -1,  1317,    -1,    -1,    -1,  1274,    -1,
    1276,    26,    27,    28,    29,    -1,    -1,    -1,     1,  1641,
      -1,     4,    37,     6,    -1,    -1,    -1,  1167,  1650,   160,
      -1,    -1,   131,  1230,    -1,  1232,  1233,  1250,  1235,    -1,
    1749,    -1,    -1,    26,    27,    28,    29,    -1,   234,    -1,
    1450,  1317,  1318,     1,  1367,    -1,     4,    -1,     6,   112,
      -1,    -1,    -1,  1276,    39,    40,    41,    42,     1,  1382,
      -1,     4,    -1,     6,    -1,  1272,    -1,    -1,    26,    27,
      28,    29,    -1,  1483,    -1,  1707,  1399,    -1,    -1,    -1,
      -1,    -1,    40,    26,    27,    28,    29,    -1,    73,    -1,
      -1,  1367,    -1,    -1,  1317,    -1,    81,    82,    83,    84,
    1250,    -1,    -1,    88,    -1,    -1,  1382,   248,    -1,    -1,
     306,    -1,    97,    98,    99,   100,    -1,  1749,    -1,   104,
      -1,    -1,    -1,  1399,    -1,   234,  1276,  1450,   324,    87,
      88,    89,    90,    -1,    92,   120,    -1,    95,    -1,    -1,
     125,   126,   127,    -1,  1367,   130,    -1,    -1,   133,    -1,
      -1,    -1,     1,    -1,   112,     4,    -1,     6,    -1,  1382,
    1483,    -1,    -1,    -1,    -1,   306,    -1,  1317,    -1,    -1,
      -1,   234,    -1,    -1,  1450,    -1,  1399,    26,    27,    28,
      29,    -1,    -1,   324,    44,    -1,    -1,    -1,    -1,    -1,
    1600,  1398,  1399,  1400,  1401,    -1,    -1,   306,    -1,    59,
      60,    -1,   160,   306,    -1,    -1,    -1,  1483,    -1,  1619,
    1417,  1418,  1419,    -1,    -1,   324,    -1,  1367,    -1,    -1,
      -1,   324,    44,    -1,    -1,     1,    -1,  1450,     4,    -1,
       6,  1641,  1382,    -1,    -1,    -1,    -1,    59,    60,    -1,
    1650,     1,    -1,   306,     4,    -1,     6,    -1,   108,  1399,
      26,    27,    28,    29,    -1,    -1,    -1,   117,    -1,    -1,
    1483,   324,    -1,   123,    -1,    -1,    26,    27,    28,    29,
      -1,    -1,   265,    -1,    -1,    -1,    -1,  1600,    -1,    -1,
      40,   306,   267,   268,   269,    -1,   108,   147,   754,     1,
     248,    -1,     4,    -1,     6,   117,  1619,  1707,    -1,   324,
    1450,   123,    -1,    -1,    -1,    -1,    44,   250,    -1,    -1,
      -1,    -1,    88,   306,    26,    27,    28,    29,  1641,    95,
      -1,    59,    60,    -1,  1600,   147,    -1,  1650,    88,   795,
      90,   324,    92,  1483,    -1,    95,    -1,    -1,    -1,  1749,
      -1,    -1,    -1,  1619,    -1,    -1,    -1,  1623,   306,    -1,
      -1,    -1,   112,    -1,    -1,   131,    -1,  1564,  1565,  1566,
      -1,    85,    -1,   306,    -1,  1641,   324,    -1,    -1,    -1,
     108,    -1,    -1,    -1,  1650,    -1,    88,  1600,   102,   117,
      -1,   324,    -1,    95,  1707,   123,    -1,    -1,    -1,   165,
     856,   857,   858,   859,   860,    -1,  1619,   863,    -1,    -1,
     160,    -1,   126,   127,    -1,    -1,    -1,    -1,    -1,   147,
     395,   396,   397,    -1,    -1,    -1,   265,    -1,  1641,   131,
      -1,   887,    -1,   132,    -1,    -1,  1749,  1650,    -1,    -1,
      -1,  1707,   141,    -1,    -1,    -1,    -1,    -1,    -1,   424,
       1,   907,    -1,     4,    -1,     6,    -1,   156,    -1,    -1,
    1600,   160,    -1,   165,    -1,   164,   165,   306,   234,    -1,
     169,   170,   171,   172,   173,    26,    27,    28,    29,  1619,
     455,    -1,    -1,  1749,    -1,   324,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1707,    -1,   210,    -1,    -1,    -1,
      -1,  1641,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1650,    36,    -1,    -1,    -1,    -1,   230,   231,    -1,    44,
      -1,    46,    -1,    48,    -1,    -1,    51,    52,    53,    -1,
      55,    -1,   234,    -1,   248,    -1,  1749,    88,    -1,    -1,
     306,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,
     264,  1748,  1749,  1750,  1751,   269,   306,   271,   324,  1756,
    1757,  1758,  1759,    -1,    -1,    -1,    -1,  1707,    -1,    -1,
      -1,    -1,    -1,    -1,   324,    -1,    -1,    -1,    -1,    -1,
     131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1787,  1788,  1789,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,   306,    -1,    -1,    -1,    44,  1749,
      46,    -1,    48,    -1,   165,    51,    52,    53,    -1,    55,
      -1,    -1,   324,    59,    60,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    20,  1104,  1105,
    1106,  1107,  1108,    -1,  1110,  1111,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1119,  1120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,    -1,   234,    -1,    -1,    -1,   123,    -1,    -1,
      -1,  1147,  1148,  1149,  1150,  1151,  1152,  1153,    71,  1155,
    1156,    74,    75,    76,    77,    78,    79,    -1,   233,    -1,
      -1,   147,    -1,    86,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,   248,    97,    98,    99,   100,    -1,   102,
      -1,    -1,   105,    -1,   107,    -1,    -1,   110,   111,   264,
     113,    -1,    -1,   116,   269,    -1,   271,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   306,    -1,    -1,    -1,    69,
      -1,    -1,   135,   136,   137,   138,    -1,    -1,   141,    -1,
     143,   171,    -1,   324,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,    -1,    -1,   233,    -1,   109,
      -1,    -1,    -1,   113,    -1,    -1,    -1,   117,    -1,    -1,
    1266,    -1,   248,   123,    -1,    -1,    -1,   127,  1274,     1,
      -1,    -1,     4,    83,     6,    85,    -1,    -1,   264,    -1,
      -1,    -1,    -1,   269,    -1,   271,    -1,   147,    -1,    -1,
      -1,    23,    -1,    -1,    26,    27,    28,    29,    30,    31,
     110,   111,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1318,    -1,   124,    -1,   126,   127,   128,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,   149,
     150,   151,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    -1,    96,    -1,    98,    -1,    -1,   101,
     102,   103,   104,    -1,    -1,   107,    -1,   109,    -1,    -1,
     112,   113,    -1,   243,    -1,   117,   246,   247,    -1,   199,
      -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,
      -1,    -1,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,
     152,    -1,    -1,   155,   284,   285,   158,   159,   160,    -1,
      -1,   163,    -1,    -1,   166,    -1,   168,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   259,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,
     192,    -1,   194,   195,   196,   197,    -1,    -1,   328,    -1,
      -1,   203,   204,    -1,    -1,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,    -1,
      -1,   233,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   248,   440,    -1,    -1,
      -1,    -1,    -1,    -1,   447,    -1,   258,    -1,    -1,    -1,
      -1,    -1,   264,    -1,   457,    -1,   459,   269,   461,    -1,
     463,    -1,    -1,    -1,    -1,   468,   278,   279,   471,   281,
     473,    -1,   284,   285,   286,   287,    -1,    -1,   481,   291,
      -1,    -1,    -1,   295,   296,   297,    -1,    -1,    -1,   301,
     302,    -1,     1,    -1,   306,     4,    -1,     6,   310,    -1,
      -1,   313,   314,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   323,   324,   325,    23,    -1,   328,    26,    27,    28,
      29,    30,    31,    -1,    -1,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1623,    -1,    -1,
      -1,    -1,    51,    -1,   110,   111,    -1,    -1,   114,    -1,
      -1,    -1,    61,    62,    -1,    -1,    -1,    66,   124,   125,
     126,   127,   128,   129,   130,   131,   132,    -1,    77,    78,
      79,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    -1,    96,    -1,    98,
      -1,    -1,   101,   102,   103,   104,    -1,    -1,   107,    -1,
     109,    -1,    -1,   112,   113,    -1,    -1,   173,   117,    -1,
      -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,    -1,    -1,    -1,   144,    -1,    -1,   147,    -1,
      -1,    -1,    -1,   152,    -1,    -1,   155,    -1,    -1,   158,
     159,   160,    -1,    -1,   163,    -1,    -1,   166,    -1,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   191,   192,    -1,   194,   195,   196,   197,    -1,
      -1,    -1,    -1,    -1,   203,   204,    -1,    -1,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,    -1,    -1,   233,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   248,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   258,
      -1,    -1,    -1,    -1,    -1,   264,    -1,    -1,    -1,    -1,
     269,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   278,
     279,    -1,   281,    -1,    -1,   284,   285,   286,   287,    -1,
      -1,    -1,   291,    -1,    -1,    -1,   295,   296,   297,    -1,
      -1,    -1,   301,   302,    -1,    -1,    -1,   306,    -1,    -1,
      -1,   310,    -1,     1,   313,   314,     4,    -1,     6,    -1,
      -1,    -1,    -1,    -1,   323,   324,   325,    -1,    -1,   328,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    26,    27,
      28,    29,    30,    31,    -1,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,    96,    -1,
      98,    -1,    -1,   101,   102,   103,   104,    -1,    -1,   107,
      -1,   109,    -1,    -1,   112,   113,    -1,    -1,    -1,   117,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   139,    -1,    -1,    -1,    -1,   144,    -1,    -1,   147,
     953,   954,   955,    -1,   152,    -1,    -1,   155,    -1,    -1,
     158,   159,   160,    -1,    -1,   163,    -1,    -1,   166,    -1,
     168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   191,   192,    -1,   194,   195,   196,   197,
      -1,    -1,    -1,    -1,    -1,   203,   204,    -1,    -1,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,    -1,    -1,   233,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     248,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     258,    -1,    -1,    -1,    -1,    -1,   264,    -1,    -1,    -1,
      -1,   269,    -1,    -1,    -1,     4,    -1,     6,    -1,    -1,
     278,   279,    -1,   281,    -1,    -1,   284,   285,   286,   287,
      -1,    -1,    -1,   291,    23,    -1,    -1,   295,   296,   297,
      -1,    30,    31,   301,   302,    34,    35,    36,   306,    -1,
      -1,    -1,   310,    -1,    -1,   313,   314,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,   323,   324,   325,    -1,    -1,
     328,    -1,    61,    62,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,
      79,    80,    81,    82,    -1,    83,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    98,
      -1,    -1,   101,   102,   103,   104,    -1,    -1,   107,    -1,
     109,    -1,   110,   111,   113,    -1,   114,    -1,   117,    -1,
      -1,    -1,    -1,    -1,   123,    -1,   124,   125,   126,   127,
     128,   129,   130,   131,   132,    -1,    -1,    -1,    -1,    -1,
     139,    -1,    -1,    -1,    -1,   144,    -1,    -1,   147,    -1,
      -1,    -1,    -1,   152,    -1,    -1,   155,    -1,    -1,   158,
     159,    -1,    -1,    -1,   163,    -1,    -1,   166,    -1,   168,
      -1,    -1,    -1,    -1,    -1,   173,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   191,   192,    -1,   194,   195,   196,   197,    -1,
      -1,   199,    -1,    -1,   203,   204,    -1,    -1,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,    -1,    -1,   233,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,   248,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,   258,
      23,   259,    -1,    -1,    -1,   264,    -1,    -1,    31,    -1,
     269,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,   278,
     279,    -1,   281,    -1,    -1,   284,   285,   286,   287,    -1,
      -1,    -1,   291,    -1,    -1,    -1,   295,   296,   297,    -1,
      -1,    -1,   301,   302,    -1,    -1,    69,    -1,    -1,    -1,
      -1,   310,    -1,    -1,   313,   314,    -1,    -1,    -1,    -1,
      83,    -1,    85,    -1,   323,   324,   325,    -1,    -1,   328,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,
     103,   104,    -1,    -1,   107,    -1,   109,    -1,    -1,    -1,
     113,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,
     123,    -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,    -1,
      -1,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,   152,
      -1,    -1,   155,    -1,    -1,   158,   159,    -1,    -1,    -1,
     163,    -1,    -1,   166,    -1,   168,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,   192,
      -1,   194,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,    -1,    -1,
     233,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     243,    -1,    -1,   246,   247,    -1,    -1,    21,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,   259,    31,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   278,   279,    -1,    -1,    -1,
      -1,   284,   285,    -1,    -1,    -1,    -1,    -1,   102,    -1,
      -1,    -1,    -1,    -1,   297,    69,    -1,    -1,   301,   302,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   311,   312,
      -1,   314,    -1,    -1,   128,    -1,    -1,   131,    -1,    -1,
      -1,    -1,   325,    -1,    -1,   328,    -1,   101,   102,   103,
     104,    -1,    -1,   107,   148,   109,    -1,    -1,    -1,   113,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,    -1,    -1,
     144,    -1,    -1,   147,    -1,    -1,    -1,    -1,   152,    -1,
      -1,   155,    -1,    -1,   158,   159,    -1,    -1,    -1,   163,
      -1,    -1,   166,    -1,   168,    -1,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   191,   192,    -1,
     194,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   271,    -1,   233,
       5,    -1,    -1,    -1,   278,   279,    -1,    -1,    -1,   243,
      -1,    -1,   246,   247,   288,    -1,    21,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     314,    -1,    -1,    -1,   278,   279,    -1,    -1,    -1,    -1,
     284,   285,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,
      -1,    -1,    -1,   297,    69,    -1,    -1,   301,   302,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   311,   312,    -1,
     314,    -1,    -1,   128,    -1,    -1,   131,    -1,    -1,    -1,
      -1,   325,    -1,    -1,   328,    -1,   101,   102,   103,   104,
      -1,    -1,   107,   148,   109,    -1,    -1,    -1,   113,    -1,
      -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,   123,    -1,
      -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,    -1,    -1,    -1,    -1,   144,
      -1,    -1,   147,    -1,    -1,    -1,    -1,   152,    -1,    -1,
     155,    -1,    -1,   158,   159,    -1,    -1,    -1,   163,    -1,
      -1,   166,    -1,   168,    -1,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   191,   192,    -1,   194,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   271,    -1,   233,     5,
      -1,    -1,    -1,   278,   279,    -1,    -1,    -1,   243,    -1,
      -1,   246,   247,   288,    -1,    21,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   314,
      -1,    -1,    -1,   278,   279,    -1,    -1,    -1,    -1,   284,
     285,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   297,    69,    -1,    -1,   301,   302,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   311,   312,    -1,   314,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     325,    -1,    -1,   328,    -1,   101,   102,   103,   104,    -1,
      -1,   107,    -1,   109,    -1,    -1,    -1,   113,    -1,    -1,
      -1,   117,    -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,
      -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,    -1,    -1,    -1,    -1,   144,    -1,
      -1,   147,    -1,    -1,    -1,    -1,   152,    -1,    -1,   155,
      -1,    -1,   158,   159,    -1,    -1,    -1,   163,    -1,    -1,
     166,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   191,   192,    -1,   194,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,    -1,    -1,   233,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   243,    -1,    -1,
     246,   247,    -1,    -1,    21,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   278,   279,    -1,    -1,    -1,    -1,   284,   285,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   297,    69,    -1,    -1,   301,   302,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   311,   312,    -1,   314,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   325,
      -1,    -1,   328,    -1,   101,   102,   103,   104,    -1,    -1,
     107,    -1,   109,    -1,    -1,    -1,   113,    -1,    -1,    -1,
     117,    -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,
     127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,    -1,    -1,    -1,    -1,   144,    -1,    -1,
     147,    -1,    -1,    -1,    -1,   152,    -1,    -1,   155,    -1,
      -1,   158,   159,    -1,    -1,    -1,   163,    -1,    -1,   166,
      -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   191,   192,    -1,   194,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,    -1,    -1,   233,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   243,    -1,    -1,   246,
     247,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   278,   279,    -1,    -1,    -1,    -1,   284,   285,    -1,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     297,    -1,    -1,    -1,   301,   302,    -1,    -1,    -1,    -1,
      -1,    69,   110,   111,   311,   312,   114,   314,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   325,    -1,
      -1,   328,    -1,   131,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,   104,    -1,    -1,    -1,
      -1,   109,    -1,    -1,    -1,   113,    -1,    -1,    -1,   117,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   139,    -1,    -1,    -1,    -1,   144,    -1,   186,   147,
      -1,    -1,    -1,    -1,   152,    -1,    -1,   155,    -1,    -1,
     158,   159,    -1,    -1,    -1,   163,    -1,    -1,   166,    -1,
     168,    -1,   210,    21,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    -1,    -1,   191,   192,    -1,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
      -1,    -1,   250,   251,   252,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   271,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   243,    -1,    -1,   246,   247,
      -1,    -1,    -1,   101,   102,   103,   104,    -1,    -1,   107,
      -1,   109,    -1,    -1,    -1,   113,    -1,    -1,    -1,   117,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,   127,
      -1,    -1,    -1,    -1,   110,   111,   284,   285,   114,   287,
      -1,   139,    -1,    -1,    -1,    -1,   144,    -1,    -1,   147,
      -1,    -1,    -1,    -1,   152,   131,    -1,   155,    -1,    -1,
     158,   159,    -1,   311,   312,   163,    -1,    -1,   166,    -1,
     168,    -1,    -1,    -1,    -1,   323,    -1,   325,    -1,    -1,
     328,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   191,   192,    -1,   194,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,    -1,   210,   233,    -1,    21,    22,    23,
      -1,    -1,    -1,    -1,    -1,   243,    -1,    -1,   246,   247,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   234,   235,
     236,   237,   238,   239,    -1,   241,   242,   243,   244,   245,
     246,   247,    -1,    -1,   250,   251,   252,    -1,    -1,    -1,
     278,   279,    -1,    -1,    -1,    69,   284,   285,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,    -1,   297,
      -1,    -1,    -1,   301,   302,    -1,    -1,    -1,    21,    -1,
      23,    -1,    -1,   311,   312,    -1,   314,   101,   102,   103,
     104,    -1,    -1,    -1,    -1,   109,    -1,   325,    -1,   113,
     328,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,    69,    -1,    -1,    -1,
     144,    -1,    -1,   147,    -1,    -1,    -1,    -1,   152,    -1,
      -1,   155,    -1,    -1,   158,   159,    -1,    -1,    -1,   163,
      -1,    -1,   166,    -1,   168,    -1,    -1,    -1,   101,   102,
     103,   104,    -1,    -1,    -1,    -1,   109,    -1,    -1,    -1,
     113,    -1,    -1,    -1,   117,    -1,    -1,   191,   192,    -1,
     123,    -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,    -1,
      -1,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,   152,
      -1,    -1,   155,    -1,    -1,   158,   159,    -1,    -1,    -1,
     163,    -1,    -1,   166,    -1,   168,    -1,    -1,    -1,   243,
      -1,    -1,   246,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,   191,   192,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     284,   285,    -1,   287,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   311,   312,    -1,
     243,    -1,    -1,   246,   247,    -1,    -1,    -1,    -1,   323,
      -1,   325,    21,    -1,   328,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,   104,    -1,    -1,    -1,    -1,   109,
      -1,    -1,    -1,   113,    -1,    -1,    -1,   117,    -1,    -1,
      -1,   284,   285,   123,   287,    -1,    -1,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      69,    -1,    -1,    -1,   144,    -1,    -1,   147,   311,   312,
      -1,    -1,   152,    -1,    -1,   155,    -1,    -1,   158,   159,
     323,    -1,   325,   163,    -1,   328,   166,    -1,   168,    -1,
      -1,    -1,   101,   102,   103,   104,    -1,    -1,    -1,    -1,
     109,    -1,    -1,    -1,   113,    -1,    -1,    -1,   117,    -1,
      -1,   191,   192,    -1,   123,    -1,    -1,    -1,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,    -1,    -1,    -1,   144,    -1,    -1,   147,    -1,
      -1,    -1,    -1,   152,    -1,    -1,   155,    -1,    -1,   158,
     159,    -1,    -1,    -1,   163,    -1,    -1,   166,    -1,   168,
      -1,    -1,    -1,   243,    -1,    -1,   246,   247,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   284,   285,    -1,   287,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,   311,   312,    -1,   243,    -1,    -1,   246,   247,    51,
      -1,    -1,    -1,   323,    -1,   325,    -1,    -1,   328,    61,
      62,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      82,    -1,    -1,    -1,    -1,   284,   285,    -1,   287,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    98,    -1,    -1,   101,
     102,   103,   104,    -1,    -1,   107,    -1,   109,    -1,    -1,
      -1,   113,   311,   312,    -1,   117,    -1,    -1,    -1,    -1,
      -1,   123,    -1,    -1,    -1,    -1,   325,    -1,    -1,   328,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,
      -1,    -1,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,
     152,    -1,    -1,   155,    -1,    -1,   158,   159,    -1,    -1,
      -1,   163,    -1,    -1,   166,    -1,   168,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,
     192,    -1,   194,   195,   196,   197,    -1,    -1,    -1,    -1,
      -1,   203,   204,    -1,    -1,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,    -1,
      -1,   233,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,   258,    -1,    30,    31,
      -1,    -1,   264,    35,    -1,    -1,    -1,   269,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   278,   279,    -1,   281,
      -1,    -1,   284,   285,   286,   287,    -1,    -1,    -1,   291,
      -1,    -1,    -1,   295,   296,   297,    -1,    -1,    -1,   301,
     302,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,
      -1,   313,   314,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   323,    -1,   325,    -1,    -1,   328,    -1,    -1,   101,
     102,   103,   104,    -1,    -1,   107,    -1,   109,    -1,    -1,
      -1,   113,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,
      -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,
      -1,    -1,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,
     152,    -1,    -1,   155,    -1,    -1,   158,   159,    -1,    -1,
      -1,   163,    -1,    -1,   166,    -1,   168,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,    -1,    -1,    35,    -1,    -1,    -1,   191,
     192,    -1,   194,   195,   196,   197,    -1,    -1,    -1,    -1,
      -1,   203,   204,    -1,    -1,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,    -1,
      -1,   233,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,   104,    -1,    -1,   107,    -1,   109,
      -1,    -1,    -1,   113,    -1,    -1,    -1,   117,    -1,    -1,
      -1,    -1,    -1,   123,    -1,    -1,   278,   279,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      -1,    -1,    -1,    -1,   144,   297,    -1,   147,    -1,   301,
     302,    -1,   152,    -1,    -1,   155,    -1,    -1,   158,   159,
      -1,   313,   314,   163,    -1,    -1,   166,    -1,   168,    -1,
      -1,   323,    -1,   325,    -1,    23,   328,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    35,    -1,    -1,
      -1,   191,   192,    -1,   194,   195,   196,   197,    -1,    -1,
      -1,    -1,    -1,   203,   204,    -1,    -1,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,    -1,    -1,   233,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,   104,    -1,    -1,   107,
      -1,   109,    -1,    -1,    -1,   113,    -1,    -1,    -1,   117,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,   278,   279,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   139,    -1,    -1,    -1,    -1,   144,   297,    -1,   147,
      -1,   301,   302,    -1,   152,    -1,    -1,   155,    -1,    -1,
     158,   159,    -1,   313,   314,   163,    -1,    -1,   166,    -1,
     168,    -1,    -1,    -1,    -1,   325,    -1,    -1,   328,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   191,   192,    -1,   194,   195,   196,   197,
      -1,    -1,    -1,    -1,    -1,   203,   204,    -1,    -1,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,    -1,    -1,   233,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     278,   279,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   297,
      -1,    -1,    -1,   301,   302,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   313,   314,   101,   102,   103,
     104,    -1,    -1,   107,    -1,   109,    -1,   325,    -1,   113,
     328,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,    -1,    -1,
     144,    -1,    -1,   147,    -1,    -1,    -1,    -1,   152,    -1,
      -1,   155,    -1,    -1,   158,   159,    -1,    -1,    -1,   163,
      -1,    -1,   166,    -1,   168,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,   192,    -1,
     194,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,    -1,    -1,   233,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   243,
      -1,    -1,   246,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   278,   279,    -1,    -1,    -1,    -1,
     284,   285,    -1,    -1,    -1,    -1,     0,     1,    -1,    -1,
       4,    -1,     6,   297,    -1,    -1,    -1,   301,   302,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   311,   312,    -1,
     314,    -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,   325,    36,    -1,   328,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    46,    -1,    48,    -1,    -1,    51,    52,    53,
      -1,    55,    -1,    -1,    -1,    59,    60,    61,    -1,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
      -1,    -1,    -1,    -1,   108,    -1,   101,   102,   103,   104,
      -1,    -1,    -1,   117,   109,    -1,    -1,    -1,   113,   123,
      -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,   123,    -1,
      -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   147,   139,    -1,    -1,    -1,    -1,   144,
      -1,    -1,   147,    -1,    -1,    -1,    -1,   152,    -1,    -1,
     155,    -1,    -1,   158,   159,    -1,    -1,    -1,   163,    -1,
      -1,   166,    69,   168,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    -1,    -1,    50,    51,
      -1,    53,    54,    55,    -1,    57,   191,   192,    -1,    -1,
      -1,    -1,    -1,    -1,   101,   102,   103,   104,    -1,    -1,
      -1,    -1,   109,    -1,    -1,    -1,   113,    -1,    -1,    -1,
     117,    -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,   233,
     127,    -1,    -1,    -1,    96,    -1,    98,    99,   100,    -1,
      -1,    -1,   139,    -1,   248,    -1,    -1,   144,   243,    -1,
     147,   246,   247,    -1,    -1,   152,    -1,    -1,   155,    -1,
     264,   158,   159,    -1,    -1,   269,   163,   271,    -1,   166,
      -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   284,
     285,    -1,   287,    -1,   191,   192,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   311,   312,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     325,    -1,    -1,   328,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   243,    -1,    -1,   246,
     247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   233,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   248,   284,   285,    -1,
     287,   253,   254,   255,   256,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   264,    -1,    -1,    -1,    -1,   269,    -1,   271,
     272,    -1,    -1,    -1,   311,   312,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   325,    -1,
      -1,   328
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   332,     0,     1,     4,     6,    26,    27,    28,    29,
      36,    44,    46,    48,    51,    52,    53,    55,    59,    60,
      61,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,   108,   117,   123,   147,   233,   248,
     264,   269,   271,   333,   335,   336,   337,   338,   402,   403,
     404,   406,   421,   333,   103,   102,   399,   399,   399,   404,
     415,   404,   406,   421,   404,   409,   409,   409,   404,   412,
     338,    48,   339,    36,    44,    46,    51,    52,    53,    55,
     233,   248,   264,   269,   271,   340,    48,   341,    36,    44,
      46,    48,    51,    52,    53,    55,   233,   248,   264,   269,
     271,   342,    52,   343,    36,    44,    45,    46,    47,    50,
      51,    53,    54,    55,    57,    96,    98,    99,   100,   233,
     248,   253,   254,   255,   256,   264,   269,   271,   272,   344,
     248,   253,   254,   269,   345,    44,    46,    51,    53,    57,
      96,    98,   346,    46,   347,    23,    30,    31,    35,   101,
     102,   103,   104,   107,   109,   113,   117,   123,   139,   144,
     147,   152,   155,   158,   159,   163,   166,   168,   191,   192,
     194,   195,   196,   197,   203,   204,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     233,   278,   279,   297,   301,   302,   313,   314,   325,   328,
     355,   400,   515,   516,   519,   520,   521,   525,   584,   587,
     589,   593,   598,   599,   601,   603,   613,   614,   616,   618,
     620,   622,   626,   628,   630,   632,   634,   636,   638,   640,
     642,   644,   648,   650,   652,   654,   655,   657,   659,   661,
     663,   665,   667,   669,   671,    57,   307,   308,   309,   348,
     354,    57,   349,   354,   102,   350,   351,    88,   240,   242,
     415,   415,   415,   415,     0,   333,   399,   399,    56,   304,
     305,   418,   419,   420,    34,    36,    51,    61,    62,    66,
      77,    78,    79,    80,    81,    82,    96,    98,   209,   233,
     248,   258,   264,   269,   281,   284,   285,   286,   287,   291,
     295,   296,   310,   323,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   437,   438,   439,   442,   443,   450,   454,
     459,   460,   462,   463,   464,   465,   466,   488,   489,   491,
     492,   494,   495,   498,   499,   506,   507,   508,   509,   510,
     513,   514,   520,   527,   528,   529,   530,   531,   532,   536,
     537,   538,   568,   582,   587,   588,   611,   612,   613,   333,
     322,   322,   333,   399,   470,   356,   359,   425,   399,   363,
     365,   515,   538,   368,   399,   372,   406,   422,   415,   404,
     406,   409,   409,   409,   412,    88,   240,   242,   415,   415,
     415,   415,   421,   404,   415,   416,   402,   404,   405,   404,
     406,   407,   422,   404,   409,   410,   409,   409,   404,   412,
     413,    88,   240,   242,   558,   415,   416,   415,   416,   415,
     416,   415,   416,   409,   415,   404,   403,   424,   406,   424,
      44,   424,   409,   409,   424,   412,   424,    44,    45,   409,
     424,   424,    88,   240,   257,   558,   415,    44,   424,    44,
     424,    44,   424,    44,   424,   415,   415,   415,    44,   424,
     415,    44,   424,    44,   424,   415,   404,   406,   409,   409,
     424,    44,   409,   406,   105,   106,   107,   615,   110,   111,
     210,   211,   214,   523,   524,    32,    33,   210,   590,   130,
     526,   164,   165,   653,   110,   111,   112,   617,   112,   114,
     115,   116,   619,   110,   111,   118,   119,   120,   121,   122,
     621,   110,   111,   114,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   173,   623,   112,   114,   132,   140,   141,
     142,   143,   627,   112,   132,   145,   260,   629,   110,   111,
     124,   126,   127,   128,   149,   150,   151,   631,   112,   114,
     132,   140,   141,   143,   153,   154,   633,   125,   141,   150,
     156,   157,   635,   141,   157,   637,   150,   160,   161,   639,
     128,   132,   164,   165,   641,   132,   164,   165,   167,   643,
     132,   141,   156,   160,   164,   165,   169,   170,   171,   172,
     173,   645,   112,   164,   165,   649,   132,   164,   165,   193,
     651,   112,   123,   125,   143,   147,   150,   198,   231,   232,
     314,   600,   602,   658,   199,   660,   199,   662,   160,   200,
     201,   202,   664,   125,   150,   656,   114,   129,   150,   156,
     205,   206,   666,   125,   150,   668,   112,   125,   132,   150,
     156,   670,   102,   128,   131,   148,   271,   288,   314,   585,
     586,   587,   110,   111,   114,   131,   210,   234,   235,   236,
     237,   238,   239,   241,   242,   243,   244,   245,   246,   247,
     250,   251,   252,   271,   604,   605,   608,   288,   298,   592,
     532,   537,   299,   194,   203,   204,   207,   208,   672,   320,
     321,   595,   531,   399,   354,   308,   354,    45,    47,    49,
      50,    57,    58,    90,   352,   415,   415,   415,   553,   567,
     555,   557,   101,   101,   101,    83,   600,   249,   507,   399,
     515,   583,   583,    61,    97,   399,   102,   585,    88,   186,
     240,   604,   605,   249,   249,   265,   249,   267,   268,   451,
      83,    83,   600,     4,   334,   539,   540,   306,   423,   429,
     359,   250,   251,   440,   441,   160,   259,   260,   261,   262,
     263,   444,   445,   282,   461,     5,    21,    69,    83,    85,
     109,   113,   117,   123,   127,   147,   194,   243,   246,   247,
     259,   284,   285,   311,   312,   325,   473,   474,   475,   476,
     477,   478,   479,   481,   482,   483,   484,   485,   486,   487,
     516,   519,   525,   577,   578,   579,   584,   589,   593,   599,
     600,   601,   603,   609,   610,   613,    37,    38,    39,   184,
     467,   468,    83,   288,   289,   290,   490,   496,   497,    83,
     493,   496,   292,   293,   294,   500,   501,   502,   503,    23,
     515,   517,   518,    44,   511,   512,    15,    16,    17,    18,
     327,     8,    24,    53,     9,    10,    11,    12,    13,    14,
     109,   113,   117,   123,   139,   144,   147,   152,   155,   158,
     159,   163,   166,   168,   191,   192,   287,   325,   484,   516,
     518,   519,   533,   534,   535,   538,   569,   570,   571,   572,
     573,   574,   575,   576,   578,   579,   580,   581,    51,    51,
      22,   323,   551,   569,   570,   551,    37,   323,   469,   323,
     323,   323,   323,   323,   418,   425,   470,   356,   359,   363,
     365,   368,   372,   415,   415,   415,   553,   567,   555,   557,
     425,    56,    56,    56,    56,   365,    56,   372,   415,   365,
     404,   409,   424,    44,    44,    44,   415,   404,   404,   404,
     404,   404,   404,   404,   409,   399,     7,     8,   112,   214,
     215,   522,   102,   124,   249,   109,   123,   109,   123,   135,
     136,   137,   138,   624,   171,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   646,   602,   329,   329,
     110,   111,   123,   131,   147,   234,   235,   236,   606,   607,
     608,   299,   299,   101,   317,   594,   326,   353,   354,   565,
     565,   565,   250,   323,   552,   265,   323,   566,   323,   451,
     554,   323,   400,   556,     5,   123,   147,   486,    83,   486,
     504,   505,   532,    23,    23,    95,   323,    51,    51,    51,
     101,   267,    51,   608,    51,   486,   486,   267,   268,   455,
     486,   101,   486,   486,    83,   484,   538,   543,   544,   549,
     575,   576,     7,   324,   400,   323,   101,   101,   441,    76,
     109,   123,   168,   217,   447,   400,   101,   101,   101,   400,
     446,   445,   139,   152,   168,   283,   486,     5,   486,    83,
      83,   478,   516,   579,    15,    16,    17,    18,   327,    20,
      22,     8,    53,     5,   496,    83,    85,   199,   259,     7,
       7,   101,   101,   468,     5,     7,     5,   486,   486,   501,
       7,   399,   323,   399,   323,   512,   580,   580,   571,   572,
     573,   531,   323,   434,   517,   570,   575,     7,    15,    16,
      17,    18,   327,     7,    20,    22,     8,   570,   486,   486,
     101,   324,   333,   333,   101,   387,   358,   360,   364,   369,
     373,   469,   323,   323,   323,   323,   323,   565,   565,   565,
     552,   566,   554,   556,   101,   101,   101,   101,   101,   323,
     565,   404,   404,   404,   101,   524,   112,   128,   133,   134,
     199,   625,    95,   128,   185,   186,   187,   188,   189,   190,
     647,   101,   101,   110,   111,   110,   111,   101,   101,   300,
     591,   101,   157,   316,   596,   600,   323,   323,   323,   101,
     380,   455,   385,   381,   101,   386,   486,     5,     5,   486,
     517,    88,    91,   423,   545,   546,   400,   400,   101,   532,
     541,   542,   486,   486,   486,   101,   486,    51,   486,   101,
     102,   251,   452,    42,   486,   334,     5,   334,    88,    91,
     248,   423,   547,   548,   334,   540,   361,   146,   141,   146,
     448,   449,   112,   112,    69,   112,   486,     5,   486,   486,
     326,   473,   473,   474,   475,   476,   101,   478,   473,   480,
     517,   538,   486,   486,    83,     8,    83,   516,   579,   609,
     609,   486,   497,   486,   496,   503,   504,   541,   334,   435,
     436,   326,   575,   580,   580,   571,   572,   573,   575,   101,
     575,   535,   575,    38,   333,   324,   333,   335,   423,   469,
      36,    46,    51,    53,    55,   160,   233,   248,   264,   269,
     271,   324,   333,   335,   357,   423,    92,   112,   160,   324,
     333,   335,   389,   395,   396,   423,   425,    40,    87,    88,
      89,    90,    92,    95,   112,   160,   248,   324,   333,   335,
     370,   423,    40,    88,    90,   112,   160,   324,   333,   335,
     370,   423,    41,    43,   248,   324,   333,   335,   358,   360,
     364,   369,   373,   323,   323,   323,   373,     7,   330,   330,
     591,   303,   591,   101,   110,   111,   597,   383,   384,   382,
     251,   324,   333,   335,   423,   552,   101,   324,   333,   335,
     423,   566,   324,   333,   335,   423,   554,   452,   324,   333,
     335,   423,   556,   486,   486,     5,   102,   401,   401,   546,
     323,   429,   545,   486,    20,   102,   270,   453,   486,    42,
      80,    81,   550,   576,   582,   401,   401,   250,   548,   324,
     333,   425,     7,   102,   102,   102,   486,     5,   486,   162,
     486,   496,   496,     5,   233,   324,   428,   429,   543,     7,
     324,   101,    38,   399,   417,   399,   408,   399,   411,   411,
     399,   414,   102,    88,   240,   242,   417,   417,   417,   417,
     333,    77,    78,   397,   398,   515,   102,    97,   333,   333,
     333,   333,   333,   362,   520,   401,   401,   322,    93,    94,
     371,   101,   102,   126,   127,   210,   230,   231,   377,   378,
     388,    84,    85,    86,    88,   366,   367,   333,   333,   333,
     362,   401,   322,   378,   366,   333,   333,   102,   322,   324,
     324,   324,   324,   324,   383,   384,   382,   324,   101,   101,
      92,   131,   234,   324,   333,   335,   423,   563,    88,    95,
     131,   165,   234,   324,   333,   335,   423,   564,   112,   234,
     324,   333,   335,   423,   560,   101,    20,   102,   453,   486,
     541,   324,   276,   277,   278,   279,   280,   458,   266,   457,
     101,   486,   334,   101,   333,   449,   486,    83,   504,     5,
     324,   324,     5,   334,   436,   184,   471,   101,   379,   359,
     363,   368,   372,   417,   417,   417,   379,   379,   379,   379,
      41,     8,   333,   333,   333,   365,     8,   333,     7,   333,
       5,   333,   365,     5,   333,   148,   390,   323,   374,   515,
     324,   324,   324,   591,   322,   163,   168,   559,   403,   401,
     101,   559,   101,   403,   103,   403,   458,   457,   429,   266,
     456,   101,   452,   251,   486,   324,   504,   582,    39,   472,
     333,   323,   323,   323,   323,   323,   379,   379,   379,   323,
     323,   323,   323,   102,   520,   377,   367,    85,   362,    85,
     248,   264,   269,   271,   378,    22,   101,   102,   321,   391,
     392,   393,   515,   333,   102,   375,   376,   515,   333,   323,
     333,   333,   333,   333,   333,   333,   333,   131,   333,   456,
     324,   101,   102,   251,   101,   324,   334,   471,   387,   360,
     364,   369,   373,   323,   323,   323,   380,   385,   381,   386,
      42,    43,   394,   362,   333,   378,   333,   333,   333,   333,
     333,   101,    22,    25,     7,   324,   102,   561,   562,   559,
     250,   472,   324,   324,   324,   324,   324,   383,   384,   382,
     324,   324,   324,   324,   400,   515,   322,   390,   333,   333,
     101,   101,   334,   376,     5,     7,   324,   333,   333,   333,
     333,   333,   333,   324,   324,   324,   333,   333,   333,   333,
     374,   101,   562,   333,   333,   333,   333
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   331,   332,   332,   333,   333,   334,   334,   335,   335,
     335,   335,   335,   336,   336,   336,   336,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   339,   340,   340,   340,
     340,   340,   340,   340,   340,   340,   340,   340,   340,   340,
     340,   340,   340,   340,   341,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   343,   344,
     344,   344,   344,   344,   344,   344,   344,   344,   344,   344,
     344,   344,   344,   344,   344,   344,   344,   344,   344,   344,
     344,   344,   344,   344,   344,   344,   344,   344,   344,   344,
     344,   344,   344,   344,   345,   345,   345,   345,   345,   345,
     346,   346,   346,   346,   346,   346,   346,   347,   348,   348,
     349,   349,   350,   351,   351,   352,   352,   352,   352,   352,
     352,   352,   352,   353,   353,   354,   354,   354,   355,   356,
     357,   357,   358,   358,   358,   358,   358,   358,   358,   358,
     358,   358,   358,   358,   358,   358,   358,   358,   359,   360,
     360,   360,   360,   360,   360,   360,   360,   361,   361,   361,
     362,   362,   363,   364,   364,   364,   364,   364,   364,   364,
     364,   364,   364,   364,   364,   364,   365,   365,   366,   366,
     367,   367,   367,   367,   368,   369,   369,   369,   369,   369,
     369,   369,   369,   369,   369,   369,   369,   369,   369,   369,
     369,   370,   370,   371,   371,   372,   373,   373,   373,   373,
     373,   373,   374,   374,   375,   375,   375,   376,   376,   377,
     377,   378,   378,   379,   380,   380,   380,   380,   380,   381,
     381,   381,   381,   381,   382,   382,   382,   382,   382,   383,
     383,   383,   383,   383,   384,   384,   384,   384,   384,   385,
     385,   385,   385,   385,   386,   386,   386,   386,   386,   387,
     387,   387,   387,   387,   388,   388,   388,   388,   388,   389,
     390,   391,   391,   392,   392,   392,   392,   392,   393,   393,
     394,   394,   394,   394,   395,   396,   397,   397,   398,   398,
     399,   400,   400,   400,   401,   402,   402,   403,   403,   403,
     403,   403,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   420,
     421,   421,   421,   421,   422,   423,   424,   424,   425,   425,
     426,   427,   427,   428,   428,   428,   428,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   430,   430,   431,
     432,   432,   433,   434,   434,   435,   435,   435,   436,   437,
     437,   438,   438,   439,   439,   440,   440,   441,   441,   442,
     442,   443,   444,   444,   445,   445,   445,   445,   445,   445,
     446,   447,   447,   447,   447,   447,   448,   448,   449,   449,
     450,   450,   450,   451,   451,   451,   452,   452,   453,   453,
     454,   454,   455,   455,   455,   456,   456,   457,   457,   457,
     458,   458,   458,   458,   458,   459,   460,   461,   461,   461,
     461,   461,   462,   463,   463,   464,   464,   464,   464,   464,
     464,   465,   465,   466,   466,   467,   467,   468,   468,   468,
     468,   469,   469,   470,   471,   471,   472,   472,   473,   473,
     473,   473,   473,   473,   473,   473,   473,   473,   473,   473,
     473,   474,   474,   474,   475,   475,   476,   476,   477,   477,
     478,   479,   479,   480,   480,   481,   481,   482,   483,   484,
     485,   485,   485,   486,   486,   486,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     488,   488,   489,   490,   490,   490,   491,   491,   492,   493,
     493,   493,   493,   493,   494,   494,   495,   495,   496,   496,
     497,   497,   497,   498,   498,   499,   500,   500,   501,   501,
     502,   502,   503,   503,   504,   504,   505,   506,   506,   506,
     507,   507,   507,   508,   508,   509,   509,   510,   511,   511,
     512,   513,   513,   514,   515,   516,   516,   517,   517,   518,
     519,   520,   520,   520,   520,   520,   520,   520,   520,   520,
     520,   520,   520,   520,   520,   520,   521,   522,   522,   522,
     523,   523,   523,   523,   523,   524,   524,   525,   525,   526,
     526,   527,   527,   527,   528,   528,   529,   529,   530,   530,
     531,   532,   532,   533,   534,   535,   535,   536,   537,   537,
     537,   538,   539,   539,   539,   540,   540,   540,   541,   541,
     542,   543,   543,   544,   545,   545,   546,   546,   546,   547,
     547,   548,   548,   548,   548,   548,   549,   549,   550,   550,
     551,   551,   551,   551,   552,   553,   554,   555,   556,   557,
     558,   558,   558,   559,   559,   560,   560,   561,   561,   562,
     563,   563,   563,   564,   564,   564,   564,   564,   565,   566,
     566,   567,   568,   568,   568,   569,   569,   570,   570,   570,
     570,   571,   571,   571,   572,   572,   573,   573,   574,   574,
     575,   576,   576,   576,   576,   577,   577,   578,   579,   579,
     579,   579,   579,   579,   579,   579,   579,   579,   579,   579,
     580,   580,   580,   580,   580,   580,   580,   580,   580,   580,
     580,   580,   580,   580,   580,   580,   580,   581,   581,   581,
     581,   581,   581,   582,   582,   582,   582,   582,   582,   583,
     583,   584,   584,   584,   585,   585,   586,   586,   586,   586,
     586,   587,   587,   587,   587,   587,   587,   587,   587,   587,
     587,   587,   587,   587,   587,   587,   587,   587,   587,   587,
     587,   587,   587,   587,   587,   588,   588,   588,   588,   588,
     588,   589,   590,   590,   590,   591,   591,   592,   592,   593,
     594,   594,   595,   595,   596,   596,   597,   597,   598,   598,
     599,   599,   599,   600,   600,   601,   601,   602,   602,   602,
     602,   603,   603,   603,   604,   604,   605,   605,   605,   605,
     605,   605,   605,   605,   605,   605,   605,   605,   605,   605,
     605,   605,   605,   606,   606,   606,   606,   606,   606,   606,
     607,   607,   607,   607,   608,   608,   608,   608,   609,   609,
     610,   610,   611,   611,   611,   611,   612,   613,   613,   613,
     613,   613,   613,   613,   613,   613,   613,   613,   613,   613,
     613,   613,   613,   613,   613,   614,   615,   615,   615,   616,
     617,   617,   617,   618,   619,   619,   619,   619,   620,   621,
     621,   621,   621,   621,   621,   621,   621,   621,   622,   622,
     622,   623,   623,   623,   623,   623,   623,   623,   623,   623,
     623,   623,   623,   624,   624,   624,   624,   625,   625,   625,
     625,   625,   626,   627,   627,   627,   627,   627,   627,   627,
     628,   629,   629,   629,   629,   630,   631,   631,   631,   631,
     631,   631,   631,   631,   631,   632,   633,   633,   633,   633,
     633,   633,   633,   633,   634,   635,   635,   635,   635,   635,
     636,   637,   637,   638,   639,   639,   639,   640,   641,   641,
     641,   641,   642,   643,   643,   643,   643,   644,   644,   644,
     645,   645,   645,   645,   645,   645,   645,   645,   645,   645,
     646,   646,   646,   646,   646,   646,   646,   646,   646,   646,
     646,   646,   647,   647,   647,   647,   647,   647,   647,   647,
     648,   649,   649,   649,   650,   651,   651,   651,   651,   652,
     653,   653,   654,   654,   654,   654,   654,   654,   654,   654,
     655,   656,   656,   657,   658,   658,   658,   658,   659,   660,
     661,   662,   663,   664,   664,   664,   664,   665,   666,   666,
     666,   666,   666,   666,   667,   668,   668,   669,   670,   670,
     670,   670,   670,   671,   672,   672,   672,   672,   672
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       5,     3,     2,     1,     1,     2,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     6,     2,     6,     3,     2,     6,     6,
       3,     6,     2,     4,     6,     4,     6,     7,     7,     7,
       4,     6,     4,     6,     4,     6,     3,     2,     6,     2,
       6,     6,     6,     3,     6,     2,     4,     4,     7,     7,
       7,     4,     4,     4,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     2,     2,     6,     2,     2,     2,
       2,     4,     2,     2,     2,     2,     2,     2,     3,     2,
       2,     2,     2,     2,     3,     2,     2,     3,     2,     2,
       3,     2,     2,     3,     2,     2,     3,     2,     2,     3,
       2,     2,     3,     3,     2,     2,     2,     2,     2,     2,
       3,     4,     4,     4,     2,     3,     2,     2,     3,     2,
       2,     2,     2,     2,     3,     2,     2,     3,     2,     1,
       2,     1,     3,     0,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     1,     1,     2,     1,     0,
       2,     1,     0,     2,     2,     3,     8,     8,     8,     8,
       8,     8,     9,     9,     9,     8,     8,     8,     0,     0,
       2,     2,     3,     3,     3,     3,     3,     0,     2,     3,
       1,     3,     0,     0,     2,     2,     4,     4,     4,     4,
       4,     3,     4,     2,     3,     3,     1,     1,     3,     1,
       1,     1,     1,     1,     0,     0,     2,     2,     4,     6,
       7,     6,     7,     6,     6,     6,     6,     4,     4,     3,
       3,     2,     2,     1,     1,     0,     0,     2,     2,     5,
       5,     2,     3,     1,     1,     3,     3,     1,     1,     1,
       1,     1,     3,     0,     0,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     0,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     0,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     0,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     1,     1,     1,     1,     1,     6,
       2,     1,     1,     1,     1,     1,     3,     3,     1,     2,
       2,     2,     3,     0,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     2,     3,     1,     2,     3,
       1,     2,     3,     1,     2,     3,     1,     2,     2,     2,
       1,     2,     2,     2,     2,     2,     0,     1,     1,     2,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
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
       4,     5,     2,     3,     2,     6,     4,     3,     4,     3,
       2,     1,     1,     3,     4,     1,     2,     1,     1,     2,
       3,     1,     3,     4,     3,     5,     3,     6,     1,     3,
       1,     1,     1,     1,     2,     1,     1,     2,     2,     1,
       1,     3,     1,     1,     1,     2,     1,     4,     5,     6,
       1,     1,     1,     7,     8,     6,     1,     1,     1,     2,
       2,     6,     8,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     3,     0,
       2,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     1,     3,     3,     3,     1,     1,     3,     1,     1,
       1,     3,     1,     3,     3,     3,     3,     5,     1,     2,
       1,     1,     2,     1,     1,     2,     2,     2,     1,     1,
       2,     2,     2,     1,     5,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     4,     0,     4,     0,     1,     0,
       1,     1,     1,     1,     1,     5,     3,     1,     3,     3,
       3,     6,     3,     3,     3,     3,     3,     3,     0,     6,
       5,     0,     2,     2,     3,     3,     3,     1,     1,     1,
       1,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     1,     4,
       4,     2,     1,     1,     1,     0,     2,     1,     1,     5,
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
    case 102: /* "string"  */
#line 313 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4483 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 103: /* "quoted string"  */
#line 313 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4489 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 104: /* "string with a trailing asterisk"  */
#line 313 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4495 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 336: /* line  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4501 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* base_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4507 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* add_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4513 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* replace_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4519 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* create_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4525 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* insert_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4531 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* delete_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4537 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* get_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4543 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* list_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4549 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 345: /* reset_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4555 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* flush_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4561 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* rename_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4567 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 348: /* import_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4573 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 349: /* export_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4579 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* monitor_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4585 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 351: /* monitor_event  */
#line 815 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4591 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 355: /* describe_cmd  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4597 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* table_block_alloc  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 4603 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 359: /* chain_block_alloc  */
#line 610 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 4609 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* subchain_block  */
#line 610 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 4615 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 362: /* typeof_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4621 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 363: /* set_block_alloc  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4627 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 365: /* set_block_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4633 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 368: /* map_block_alloc  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4639 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 372: /* flowtable_block_alloc  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 4645 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 374: /* flowtable_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4651 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* flowtable_list_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4657 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* flowtable_expr_member  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4663 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* data_type_atom_expr  */
#line 586 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4669 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 378: /* data_type_expr  */
#line 586 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4675 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 379: /* obj_block_alloc  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4681 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* type_identifier  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4687 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* extended_prio_name  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4693 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* dev_spec  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).expr)); }
#line 4699 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* policy_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4705 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* identifier  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4711 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* string  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4717 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* table_spec  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4723 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* tableid_spec  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4729 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* chain_spec  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4735 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* chainid_spec  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4741 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* chain_identifier  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4747 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* set_spec  */
#line 597 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4753 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* setid_spec  */
#line 597 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4759 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* set_identifier  */
#line 597 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4765 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 412: /* flowtable_spec  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4771 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* flowtableid_spec  */
#line 597 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4777 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* obj_spec  */
#line 597 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4783 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* objid_spec  */
#line 597 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4789 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* obj_identifier  */
#line 597 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4795 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* handle_spec  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4801 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* position_spec  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4807 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* index_spec  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4813 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* rule_position  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4819 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* ruleid_spec  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4825 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* comment_spec  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4831 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* ruleset_spec  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4837 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* rule  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 4843 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* stmt_list  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 4849 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* stateful_stmt  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4855 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* stmt  */
#line 633 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4861 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* chain_stmt  */
#line 658 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4867 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 432: /* verdict_stmt  */
#line 633 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4873 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* verdict_map_stmt  */
#line 714 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4879 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* verdict_map_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4885 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* verdict_map_list_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4891 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 436: /* verdict_map_list_member_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4897 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* connlimit_stmt  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4903 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* counter_stmt  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4909 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 439: /* counter_stmt_alloc  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4915 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* log_stmt  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4921 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* log_stmt_alloc  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4927 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 450: /* limit_stmt  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4933 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* quota_unit  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4939 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 454: /* quota_stmt  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4945 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* reject_stmt  */
#line 649 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4951 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* reject_stmt_alloc  */
#line 649 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4957 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* nat_stmt  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4963 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 463: /* nat_stmt_alloc  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4969 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* tproxy_stmt  */
#line 654 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4975 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* synproxy_stmt  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4981 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* synproxy_stmt_alloc  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4987 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* synproxy_obj  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4993 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* primary_stmt_expr  */
#line 701 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4999 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* shift_stmt_expr  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5005 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* and_stmt_expr  */
#line 705 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5011 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* exclusive_or_stmt_expr  */
#line 705 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5017 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* inclusive_or_stmt_expr  */
#line 705 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5023 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* basic_stmt_expr  */
#line 701 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5029 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* concat_stmt_expr  */
#line 693 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5035 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* map_stmt_expr_set  */
#line 693 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5041 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* map_stmt_expr  */
#line 693 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5047 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* prefix_stmt_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5053 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 483: /* range_stmt_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5059 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* wildcard_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5065 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* multiton_stmt_expr  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5071 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 486: /* stmt_expr  */
#line 693 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5077 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* masq_stmt  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5083 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 489: /* masq_stmt_alloc  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5089 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 491: /* redir_stmt  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5095 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 492: /* redir_stmt_alloc  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5101 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* dup_stmt  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5107 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 495: /* fwd_stmt  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5113 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 498: /* queue_stmt  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5119 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 499: /* queue_stmt_alloc  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5125 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 504: /* set_elem_expr_stmt  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5131 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* set_elem_expr_stmt_alloc  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5137 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* set_stmt  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5143 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 508: /* map_stmt  */
#line 672 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5149 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 509: /* meter_stmt  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5155 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* flow_stmt_legacy_alloc  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5161 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* meter_stmt_alloc  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5167 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 514: /* match_stmt  */
#line 633 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5173 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 515: /* variable_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5179 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 516: /* symbol_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5185 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* set_ref_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5191 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* set_ref_symbol_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5197 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* integer_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5203 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 520: /* primary_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5209 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 521: /* fib_expr  */
#line 806 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5215 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 525: /* osf_expr  */
#line 811 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5221 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 527: /* shift_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5227 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* and_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5233 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* exclusive_or_expr  */
#line 681 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5239 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* inclusive_or_expr  */
#line 681 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5245 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* basic_expr  */
#line 683 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5251 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* concat_expr  */
#line 708 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5257 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* prefix_rhs_expr  */
#line 690 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5263 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* range_rhs_expr  */
#line 690 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5269 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* multiton_rhs_expr  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5275 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* map_expr  */
#line 711 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5281 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 537: /* expr  */
#line 730 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5287 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* set_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5293 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* set_list_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5299 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* set_list_member_expr  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5305 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* meter_key_expr  */
#line 727 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5311 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 542: /* meter_key_expr_alloc  */
#line 727 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5317 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* set_elem_expr  */
#line 722 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5323 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 544: /* set_elem_expr_alloc  */
#line 722 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5329 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 549: /* set_lhs_expr  */
#line 722 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5335 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 550: /* set_rhs_expr  */
#line 722 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5341 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* initializer_expr  */
#line 730 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5347 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 553: /* counter_obj  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5353 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 555: /* quota_obj  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5359 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 557: /* secmark_obj  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5365 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 561: /* timeout_states  */
#line 836 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5371 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 562: /* timeout_state  */
#line 836 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5377 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 565: /* ct_obj_alloc  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5383 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 567: /* limit_obj  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5389 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 568: /* relational_expr  */
#line 743 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5395 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 569: /* list_rhs_expr  */
#line 735 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5401 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 570: /* rhs_expr  */
#line 733 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5407 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 571: /* shift_rhs_expr  */
#line 735 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5413 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 572: /* and_rhs_expr  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5419 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 573: /* exclusive_or_rhs_expr  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5425 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 574: /* inclusive_or_rhs_expr  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5431 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 575: /* basic_rhs_expr  */
#line 733 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5437 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 576: /* concat_rhs_expr  */
#line 733 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5443 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 578: /* boolean_expr  */
#line 826 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5449 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 579: /* keyword_expr  */
#line 730 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5455 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 580: /* primary_rhs_expr  */
#line 735 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5461 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 582: /* verdict_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5467 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 583: /* chain_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5473 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 584: /* meta_expr  */
#line 788 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5479 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 588: /* meta_stmt  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5485 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 589: /* socket_expr  */
#line 792 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5491 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 593: /* numgen_expr  */
#line 756 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5497 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 598: /* xfrm_expr  */
#line 840 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5503 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 599: /* hash_expr  */
#line 756 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5509 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 601: /* rt_expr  */
#line 798 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5515 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 603: /* ct_expr  */
#line 802 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5521 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 609: /* symbol_stmt_expr  */
#line 735 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5527 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 610: /* list_stmt_expr  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5533 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 611: /* ct_stmt  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5539 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 612: /* payload_stmt  */
#line 637 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5545 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 613: /* payload_expr  */
#line 747 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5551 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 614: /* payload_raw_expr  */
#line 747 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5557 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 616: /* eth_hdr_expr  */
#line 750 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5563 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 618: /* vlan_hdr_expr  */
#line 750 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5569 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 620: /* arp_hdr_expr  */
#line 753 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5575 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 622: /* ip_hdr_expr  */
#line 756 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5581 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 626: /* icmp_hdr_expr  */
#line 756 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5587 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 628: /* igmp_hdr_expr  */
#line 756 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5593 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 630: /* ip6_hdr_expr  */
#line 760 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5599 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 632: /* icmp6_hdr_expr  */
#line 760 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5605 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 634: /* auth_hdr_expr  */
#line 763 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5611 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 636: /* esp_hdr_expr  */
#line 763 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5617 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 638: /* comp_hdr_expr  */
#line 763 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5623 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 640: /* udp_hdr_expr  */
#line 766 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5629 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 642: /* udplite_hdr_expr  */
#line 766 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5635 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 644: /* tcp_hdr_expr  */
#line 821 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5641 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 648: /* dccp_hdr_expr  */
#line 769 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5647 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 650: /* sctp_hdr_expr  */
#line 769 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5653 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 652: /* th_hdr_expr  */
#line 772 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5659 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 654: /* exthdr_expr  */
#line 776 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5665 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 655: /* hbh_hdr_expr  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5671 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 657: /* rt_hdr_expr  */
#line 781 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5677 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 659: /* rt0_hdr_expr  */
#line 781 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5683 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 661: /* rt2_hdr_expr  */
#line 781 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5689 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 663: /* rt4_hdr_expr  */
#line 781 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5695 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 665: /* frag_hdr_expr  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5701 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 667: /* dst_hdr_expr  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5707 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 669: /* mh_hdr_expr  */
#line 784 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5713 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 671: /* exthdr_exists_expr  */
#line 830 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5719 "parser_bison.c" /* yacc.c:1257  */
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
#line 157 "parser_bison.y" /* yacc.c:1431  */
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 5835 "parser_bison.c" /* yacc.c:1431  */
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
#line 846 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 6034 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 8:
#line 863 "parser_bison.y" /* yacc.c:1652  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 6046 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 9:
#line 871 "parser_bison.y" /* yacc.c:1652  */
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
#line 6065 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 10:
#line 886 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 6076 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 11:
#line 893 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 6091 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 12:
#line 904 "parser_bison.y" /* yacc.c:1652  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 6101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 13:
#line 911 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 6107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 14:
#line 912 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 6113 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 15:
#line 913 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 6119 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 16:
#line 915 "parser_bison.y" /* yacc.c:1652  */
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
#line 6141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 17:
#line 934 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6147 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 18:
#line 935 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6153 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 19:
#line 936 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6159 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 20:
#line 937 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6165 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 21:
#line 938 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6171 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 22:
#line 939 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6177 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 23:
#line 940 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6183 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 24:
#line 941 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6189 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 25:
#line 942 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 26:
#line 943 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6201 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 27:
#line 944 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6207 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 28:
#line 945 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 29:
#line 946 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6219 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 30:
#line 947 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6225 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 31:
#line 948 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6231 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 32:
#line 952 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6239 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 33:
#line 957 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 34:
#line 963 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 35:
#line 968 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6268 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 36:
#line 975 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6276 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 37:
#line 979 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6284 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 38:
#line 984 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6294 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 39:
#line 991 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6304 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 40:
#line 997 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6312 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 41:
#line 1002 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6322 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 42:
#line 1008 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 6335 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 43:
#line 1017 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6343 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 44:
#line 1021 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6351 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 45:
#line 1025 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6359 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 46:
#line 1029 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6367 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 47:
#line 1033 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6375 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 48:
#line 1037 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6383 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 49:
#line 1041 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 50:
#line 1045 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 51:
#line 1049 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6407 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 52:
#line 1053 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6415 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 53:
#line 1057 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6423 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 54:
#line 1061 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6431 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 55:
#line 1065 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6439 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 56:
#line 1071 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6447 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 57:
#line 1077 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6455 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 58:
#line 1082 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6465 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 59:
#line 1088 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 60:
#line 1093 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6484 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 61:
#line 1101 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6494 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 62:
#line 1108 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 63:
#line 1114 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6512 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 64:
#line 1119 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 65:
#line 1125 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 6535 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 66:
#line 1134 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 67:
#line 1138 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6551 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 68:
#line 1142 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 69:
#line 1146 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6567 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 70:
#line 1150 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6575 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 71:
#line 1154 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6583 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 72:
#line 1158 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6591 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 73:
#line 1162 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6599 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 74:
#line 1168 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6607 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 75:
#line 1174 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 76:
#line 1178 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6623 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 77:
#line 1182 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6631 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 78:
#line 1186 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6639 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 79:
#line 1190 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6647 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 80:
#line 1194 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6655 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 81:
#line 1198 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6663 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 82:
#line 1202 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6671 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 83:
#line 1206 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6679 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 84:
#line 1210 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6687 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 85:
#line 1214 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6695 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 86:
#line 1219 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6705 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 87:
#line 1225 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6713 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 88:
#line 1229 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6721 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 89:
#line 1233 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6729 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 90:
#line 1237 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 91:
#line 1241 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6745 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 92:
#line 1245 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 93:
#line 1249 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 94:
#line 1253 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6769 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 95:
#line 1257 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6777 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 96:
#line 1261 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6785 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 97:
#line 1265 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 98:
#line 1271 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 99:
#line 1277 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 100:
#line 1281 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6817 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 101:
#line 1285 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6825 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 102:
#line 1289 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6833 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 103:
#line 1293 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6841 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 104:
#line 1297 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 105:
#line 1301 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6857 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1305 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6865 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1309 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6873 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1313 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6881 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1317 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6889 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1321 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6897 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1325 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6905 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1329 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6913 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1333 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6921 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1337 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6929 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 115:
#line 1341 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6937 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 116:
#line 1345 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6945 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 117:
#line 1349 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 118:
#line 1353 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6961 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 119:
#line 1357 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6969 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1361 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6977 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1365 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6985 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1369 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6993 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1373 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7001 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1377 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7009 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1381 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7017 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1385 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7025 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1389 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7033 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1393 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7041 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1397 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7049 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1401 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1405 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7065 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1409 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_TIMEOUT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7073 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1413 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_EXPECT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7081 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1419 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7089 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1423 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7097 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1427 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 7105 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1431 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7113 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 138:
#line 1435 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7121 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 139:
#line 1439 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7129 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 140:
#line 1445 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7137 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 141:
#line 1449 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7145 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1453 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7153 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1457 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1461 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7169 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 145:
#line 1465 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7177 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 146:
#line 1469 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7185 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 147:
#line 1475 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 7194 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 148:
#line 1482 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 149:
#line 1488 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7214 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 150:
#line 1496 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7224 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 151:
#line 1502 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 152:
#line 1510 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 7245 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 153:
#line 1518 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = NULL; }
#line 7251 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1519 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1522 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 7263 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1523 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 7269 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 157:
#line 1524 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 7275 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 158:
#line 1525 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 7281 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 159:
#line 1526 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 7287 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1527 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 7293 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1528 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 7299 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1529 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 7305 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1532 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 7311 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1536 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 7317 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 166:
#line 1537 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7323 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 167:
#line 1538 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7329 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 168:
#line 1542 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 7339 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 169:
#line 1550 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 7348 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1557 "parser_bison.y" /* yacc.c:1652  */
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
#line 7364 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1569 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].table)->comment, &(yyloc), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].table)->comment = (yyvsp[0].string);
			}
#line 7376 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1578 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 7382 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 176:
#line 1585 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7395 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 177:
#line 1596 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7407 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 178:
#line 1606 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7419 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 179:
#line 1617 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7431 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 180:
#line 1627 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7444 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 181:
#line 1638 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 182:
#line 1647 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7470 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 183:
#line 1656 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7483 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 184:
#line 1665 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7496 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 185:
#line 1676 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7509 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 186:
#line 1687 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 187:
#line 1698 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7535 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 188:
#line 1709 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 7544 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 189:
#line 1715 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7550 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 195:
#line 1722 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 7559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 196:
#line 1727 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].chain)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].chain)->comment = (yyvsp[-1].string);
			}
#line 7571 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 197:
#line 1736 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 199:
#line 1739 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 7586 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 200:
#line 1746 "parser_bison.y" /* yacc.c:1652  */
    {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 7601 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 201:
#line 1757 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 7614 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 202:
#line 1769 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7622 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 203:
#line 1774 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7628 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 206:
#line 1778 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7637 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 207:
#line 1783 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7647 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 208:
#line 1789 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7656 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 209:
#line 1794 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7665 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 210:
#line 1799 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7674 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 211:
#line 1804 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->stmt = counter_stmt_alloc(&(yyloc));
				(yyval.set) = (yyvsp[-2].set);
			}
#line 7683 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 212:
#line 1809 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7692 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 213:
#line 1814 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 7701 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 215:
#line 1820 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 7714 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 218:
#line 1835 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7722 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 220:
#line 1841 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 7728 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 221:
#line 1842 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 7734 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 222:
#line 1843 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 7740 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 223:
#line 1844 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_EVAL; }
#line 7746 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 224:
#line 1848 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 225:
#line 1853 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 228:
#line 1857 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7769 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 229:
#line 1864 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7781 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 230:
#line 1874 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 7794 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 231:
#line 1885 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7807 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 232:
#line 1896 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				datatype_set((yyvsp[-6].set)->key, (yyvsp[-4].expr)->dtype);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 7821 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 233:
#line 1908 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7832 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 234:
#line 1917 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 235:
#line 1926 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7854 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 236:
#line 1935 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_SECMARK;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7865 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 237:
#line 1942 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7874 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 238:
#line 1947 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7883 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 239:
#line 1952 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 7896 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 241:
#line 1964 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 7904 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 242:
#line 1968 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 7912 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 243:
#line 1973 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 7918 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 244:
#line 1974 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 7924 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 245:
#line 1978 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 7932 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 246:
#line 1983 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 7938 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 249:
#line 1987 "parser_bison.y" /* yacc.c:1652  */
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
#line 7956 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 250:
#line 2001 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 7964 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 251:
#line 2005 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 7972 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 252:
#line 2011 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 253:
#line 2016 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 7990 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 254:
#line 2023 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7999 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 255:
#line 2028 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8008 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 257:
#line 2036 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 8019 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 258:
#line 2043 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8028 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 259:
#line 2050 "parser_bison.y" /* yacc.c:1652  */
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
#line 8044 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 260:
#line 2062 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 8053 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 262:
#line 2070 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 8066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 263:
#line 2081 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 8074 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 264:
#line 2086 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 267:
#line 2090 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8088 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 268:
#line 2094 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8100 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 269:
#line 2103 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8106 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 272:
#line 2107 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8114 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 273:
#line 2111 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8126 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 274:
#line 2120 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8132 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 277:
#line 2124 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8140 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 278:
#line 2128 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8152 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 279:
#line 2138 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[(-1) - (0)].obj);
				init_list_head(&(yyval.obj)->ct_timeout.timeout_list);
			}
#line 8161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 282:
#line 2145 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8169 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 283:
#line 2149 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8181 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 284:
#line 2158 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 287:
#line 2162 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 288:
#line 2166 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8207 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 289:
#line 2175 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 292:
#line 2179 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8221 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 293:
#line 2183 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8233 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 294:
#line 2192 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8239 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 297:
#line 2196 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8247 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 298:
#line 2200 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8259 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 299:
#line 2209 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8265 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 302:
#line 2213 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 303:
#line 2217 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 304:
#line 2226 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 8291 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 305:
#line 2227 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("mark"); }
#line 8297 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 306:
#line 2228 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("dscp"); }
#line 8303 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 307:
#line 2229 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("ecn"); }
#line 8309 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 308:
#line 2230 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("classid"); }
#line 8315 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 309:
#line 2234 "parser_bison.y" /* yacc.c:1652  */
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
#line 8347 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 310:
#line 2264 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 8356 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 311:
#line 2271 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.string) = strdup("out");
			}
#line 8364 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 313:
#line 2278 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 8378 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 314:
#line 2288 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 8389 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 315:
#line 2295 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 8404 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 316:
#line 2306 "parser_bison.y" /* yacc.c:1652  */
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
#line 8421 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 317:
#line 2319 "parser_bison.y" /* yacc.c:1652  */
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
#line 8438 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 318:
#line 2333 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = (yyvsp[0].val); }
#line 8444 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 319:
#line 2334 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = -(yyvsp[0].val); }
#line 8450 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 320:
#line 2338 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 8466 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 321:
#line 2350 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8476 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 322:
#line 2356 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8484 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 323:
#line 2359 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = NULL; }
#line 8490 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 324:
#line 2363 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 8498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 325:
#line 2369 "parser_bison.y" /* yacc.c:1652  */
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
#line 8513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 326:
#line 2382 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 327:
#line 2387 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 8533 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 328:
#line 2395 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_ACCEPT; }
#line 8539 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 329:
#line 2396 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_DROP;   }
#line 8545 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 334:
#line 2408 "parser_bison.y" /* yacc.c:1652  */
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
#line 8562 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 335:
#line 2422 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 337:
#line 2426 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8574 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 338:
#line 2427 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 8580 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 339:
#line 2428 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_INET; }
#line 8586 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 340:
#line 2429 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_ARP; }
#line 8592 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 341:
#line 2430 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 8598 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 342:
#line 2431 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 8604 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 343:
#line 2435 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 8615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 344:
#line 2444 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 8626 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 345:
#line 2453 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 8636 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 346:
#line 2461 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 8646 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 347:
#line 2469 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 8656 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 348:
#line 2477 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 8666 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 349:
#line 2485 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 8676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 350:
#line 2493 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 8686 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 351:
#line 2501 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 8696 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 352:
#line 2509 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 353:
#line 2517 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 8716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 354:
#line 2525 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 8726 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 355:
#line 2533 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 356:
#line 2541 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 8746 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 357:
#line 2549 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8756 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 358:
#line 2557 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 8766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 359:
#line 2565 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 8776 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 360:
#line 2573 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 8784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 361:
#line 2577 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 362:
#line 2582 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8805 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 363:
#line 2590 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8814 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 364:
#line 2597 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8823 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 365:
#line 2604 "parser_bison.y" /* yacc.c:1652  */
    {
				if (strlen((yyvsp[0].string)) > NFTNL_UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed",
							 NFTNL_UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 8837 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 366:
#line 2616 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 8846 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 367:
#line 2621 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 8855 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 368:
#line 2628 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 8863 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 369:
#line 2632 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 8871 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 370:
#line 2638 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 8885 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 371:
#line 2650 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 8895 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 372:
#line 2656 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 8904 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 397:
#line 2690 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_JUMP; }
#line 8910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 398:
#line 2691 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_GOTO; }
#line 8916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 399:
#line 2695 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].chain)->location = (yylsp[-3]);
				close_scope(state);
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				(yyval.stmt) = chain_stmt_alloc(&(yyloc), (yyvsp[-1].chain), (yyvsp[-4].val));
			}
#line 8927 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 400:
#line 2704 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8935 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 401:
#line 2708 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8943 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 402:
#line 2714 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8951 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 403:
#line 2720 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8960 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 405:
#line 2728 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8969 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 406:
#line 2733 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8978 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 408:
#line 2741 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 8986 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 409:
#line 2747 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[0].val);
			}
#line 8995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 410:
#line 2752 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[0].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 9005 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 413:
#line 2763 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 9013 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 414:
#line 2767 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9023 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 415:
#line 2775 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9031 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 417:
#line 2782 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 9039 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 418:
#line 2786 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 9047 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 421:
#line 2796 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 9055 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 422:
#line 2802 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9063 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 424:
#line 2809 "parser_bison.y" /* yacc.c:1652  */
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
#line 9192 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 425:
#line 2934 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 9201 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 426:
#line 2939 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 9210 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 427:
#line 2944 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 9219 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 428:
#line 2949 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 9228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 429:
#line 2954 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 9236 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 430:
#line 2960 "parser_bison.y" /* yacc.c:1652  */
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
#line 9268 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 431:
#line 2990 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 9276 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 432:
#line 2994 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 9284 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 433:
#line 2998 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 9292 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 434:
#line 3002 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 9300 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 435:
#line 3006 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 9308 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 436:
#line 3012 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9316 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 438:
#line 3019 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 9324 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 439:
#line 3023 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 9332 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 440:
#line 3029 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 9345 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 441:
#line 3038 "parser_bison.y" /* yacc.c:1652  */
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
#line 9368 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 442:
#line 3057 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9378 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 443:
#line 3064 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 9384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 444:
#line 3065 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 445:
#line 3066 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9396 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 446:
#line 3069 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("bytes"); }
#line 9402 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 447:
#line 3070 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 9408 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 448:
#line 3073 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9414 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 449:
#line 3075 "parser_bison.y" /* yacc.c:1652  */
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
#line 9431 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 450:
#line 3090 "parser_bison.y" /* yacc.c:1652  */
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
#line 9451 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 451:
#line 3106 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9461 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 452:
#line 3113 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 9467 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 453:
#line 3114 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 454:
#line 3115 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9479 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 455:
#line 3118 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 456:
#line 3119 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 9491 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 457:
#line 3122 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9497 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 458:
#line 3123 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 9503 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 459:
#line 3125 "parser_bison.y" /* yacc.c:1652  */
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
#line 9520 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 460:
#line 3139 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL; }
#line 9526 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 461:
#line 3140 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60; }
#line 9532 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 462:
#line 3141 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 9538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 463:
#line 3142 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 9544 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 464:
#line 3143 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 9550 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 466:
#line 3150 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 9558 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 467:
#line 3156 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 9567 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 468:
#line 3161 "parser_bison.y" /* yacc.c:1652  */
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
#line 9582 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 469:
#line 3172 "parser_bison.y" /* yacc.c:1652  */
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
#line 9597 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 470:
#line 3183 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpx_code_type);
				xfree((yyvsp[0].string));
			}
#line 9611 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 471:
#line 3193 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 9619 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 473:
#line 3201 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 9625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 474:
#line 3202 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 9631 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 475:
#line 3206 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 9641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 476:
#line 3212 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 9651 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 477:
#line 3218 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9661 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 478:
#line 3224 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 479:
#line 3231 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9683 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 480:
#line 3238 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9693 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 483:
#line 3250 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 9701 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 484:
#line 3254 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9711 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 485:
#line 3262 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9719 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 487:
#line 3269 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 9728 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 488:
#line 3274 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 9737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 489:
#line 3279 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 9745 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 490:
#line 3283 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 9753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 491:
#line 3289 "parser_bison.y" /* yacc.c:1652  */
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
#line 9773 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 492:
#line 3305 "parser_bison.y" /* yacc.c:1652  */
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
#line 9793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 493:
#line 3323 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 9802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 494:
#line 3329 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9808 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 495:
#line 3331 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 9816 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 496:
#line 3336 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9822 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 497:
#line 3338 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 9830 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 498:
#line 3343 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9836 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 499:
#line 3344 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9842 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 500:
#line 3345 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9848 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 501:
#line 3346 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9854 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 502:
#line 3347 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9860 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 503:
#line 3348 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9866 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 504:
#line 3349 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9872 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 505:
#line 3350 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9878 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 506:
#line 3351 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9884 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 507:
#line 3352 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9890 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 508:
#line 3353 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9896 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 509:
#line 3354 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9902 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 510:
#line 3355 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 9908 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 512:
#line 3360 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 513:
#line 3364 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9924 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 515:
#line 3371 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9932 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 517:
#line 3378 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9940 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 519:
#line 3385 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9948 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 522:
#line 3395 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 9961 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 525:
#line 3410 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9969 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 526:
#line 3413 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9975 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 527:
#line 3417 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 9983 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 528:
#line 3423 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9991 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 529:
#line 3429 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 10004 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 536:
#line 3450 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 537:
#line 3454 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10020 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 538:
#line 3458 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10029 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 539:
#line 3463 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10038 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 540:
#line 3468 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10047 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 541:
#line 3473 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 542:
#line 3479 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10065 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 543:
#line 3483 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10073 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 544:
#line 3487 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10081 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 545:
#line 3491 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.type_flags = STMT_NAT_F_CONCAT;
			}
#line 10091 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 546:
#line 3497 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags = STMT_NAT_F_INTERVAL;
			}
#line 10101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 547:
#line 3503 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags = STMT_NAT_F_INTERVAL;
			}
#line 10110 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 548:
#line 3508 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX |
						STMT_NAT_F_INTERVAL;
				(yyvsp[-4].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 10123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 549:
#line 3517 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX |
						STMT_NAT_F_INTERVAL;
				(yyvsp[-3].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 10135 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 552:
#line 3530 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 10141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 553:
#line 3534 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10149 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 554:
#line 3538 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10158 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 555:
#line 3543 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10166 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 558:
#line 3552 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 10172 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 559:
#line 3556 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10180 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 560:
#line 3560 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10188 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 561:
#line 3564 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10196 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 562:
#line 3568 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10205 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 563:
#line 3573 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10214 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 564:
#line 3580 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 10223 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 565:
#line 3585 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 10233 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 566:
#line 3593 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 10242 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 567:
#line 3598 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 10253 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 569:
#line 3608 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10261 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 570:
#line 3613 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 10267 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 571:
#line 3614 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 10273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 572:
#line 3615 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 10279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 575:
#line 3623 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 10287 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 576:
#line 3629 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10295 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 578:
#line 3636 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 10304 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 579:
#line 3641 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 10312 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 581:
#line 3648 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10320 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 582:
#line 3653 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 10326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 583:
#line 3654 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 10332 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 586:
#line 3662 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 587:
#line 3668 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 10351 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 588:
#line 3675 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 10362 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 589:
#line 3682 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				(yyval.stmt)->set.stmt = (yyvsp[-1].stmt);
			}
#line 10374 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 590:
#line 3691 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 10380 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 591:
#line 3692 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 10386 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 592:
#line 3693 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 10392 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 593:
#line 3697 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 10404 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 594:
#line 3705 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.stmt = (yyvsp[-3].stmt);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
			}
#line 10417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 595:
#line 3716 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 10428 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 596:
#line 3722 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 10434 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 597:
#line 3726 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 10442 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 598:
#line 3732 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10450 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 600:
#line 3739 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 10458 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 601:
#line 3745 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 10471 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 602:
#line 3754 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 10484 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 603:
#line 3765 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 10492 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 604:
#line 3771 "parser_bison.y" /* yacc.c:1652  */
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
#line 10520 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 606:
#line 3798 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10531 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 609:
#line 3811 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10542 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 610:
#line 3820 "parser_bison.y" /* yacc.c:1652  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 10555 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 611:
#line 3830 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10561 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 612:
#line 3831 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10567 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 613:
#line 3832 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10573 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 614:
#line 3833 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10579 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 615:
#line 3834 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 616:
#line 3835 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10591 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 617:
#line 3836 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10597 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 618:
#line 3837 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 619:
#line 3838 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10609 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 620:
#line 3839 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 621:
#line 3840 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10621 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 622:
#line 3841 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10627 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 623:
#line 3842 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10633 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 624:
#line 3843 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10639 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 625:
#line 3844 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 10645 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 626:
#line 3848 "parser_bison.y" /* yacc.c:1652  */
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
#line 10670 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 627:
#line 3870 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 10676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 628:
#line 3871 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 10682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 629:
#line 3872 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 10688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 630:
#line 3875 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 10694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 631:
#line 3876 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 10700 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 632:
#line 3877 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 10706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 633:
#line 3878 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 10712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 634:
#line 3879 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 10718 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 635:
#line 3883 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10726 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 637:
#line 3890 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), NFT_OSF_F_VERSION);
			}
#line 10734 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 638:
#line 3894 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 10742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 639:
#line 3900 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 10750 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 640:
#line 3904 "parser_bison.y" /* yacc.c:1652  */
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
#line 10766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 642:
#line 3919 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 643:
#line 3923 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10782 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 645:
#line 3930 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 647:
#line 3937 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10798 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 649:
#line 3944 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10806 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 652:
#line 3954 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10819 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 653:
#line 3965 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 10827 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 654:
#line 3971 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10835 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 657:
#line 3981 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 661:
#line 3992 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 662:
#line 3999 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10861 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 663:
#line 4004 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10870 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 665:
#line 4012 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10878 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 666:
#line 4016 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10886 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 667:
#line 4020 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 10894 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 669:
#line 4027 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10903 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 670:
#line 4034 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10911 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 673:
#line 4044 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10919 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 674:
#line 4050 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 10927 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 676:
#line 4057 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 10935 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 677:
#line 4061 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 10943 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 678:
#line 4065 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 10955 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 679:
#line 4075 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 10963 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 681:
#line 4082 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 10971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 682:
#line 4086 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 10979 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 683:
#line 4090 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->stmt = counter_stmt_alloc(&(yyloc));
			}
#line 10987 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 684:
#line 4094 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *stmt;

				stmt = counter_stmt_alloc(&(yyloc));
				stmt->counter.packets = (yyvsp[-2].val);
				stmt->counter.bytes = (yyvsp[0].val);
				(yyvsp[-5].expr)->stmt = stmt;
			}
#line 11000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 685:
#line 4103 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 11012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 692:
#line 4122 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_SET); }
#line 11018 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 693:
#line 4124 "parser_bison.y" /* yacc.c:1652  */
    {
				int32_t num = -(yyvsp[0].val);

				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(num) * BITS_PER_BYTE,
							 &num);
			}
#line 11031 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 694:
#line 4135 "parser_bison.y" /* yacc.c:1652  */
    {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 11043 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 695:
#line 4145 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 11052 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 696:
#line 4152 "parser_bison.y" /* yacc.c:1652  */
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
#line 11074 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 697:
#line 4172 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 11083 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 698:
#line 4179 "parser_bison.y" /* yacc.c:1652  */
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
#line 11101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 699:
#line 4195 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 11110 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 700:
#line 4201 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 11116 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 701:
#line 4202 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 11122 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 702:
#line 4203 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 11128 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 703:
#line 4206 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_TCP; }
#line 11134 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 704:
#line 4207 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_UDP; }
#line 11140 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 705:
#line 4211 "parser_bison.y" /* yacc.c:1652  */
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
#line 11160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 706:
#line 4227 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 11168 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 707:
#line 4233 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 11178 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 708:
#line 4239 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 11187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 709:
#line 4247 "parser_bison.y" /* yacc.c:1652  */
    {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 11202 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 710:
#line 4260 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 11214 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 711:
#line 4268 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;

				ct = &(yyvsp[-6].obj)->ct_timeout;
				list_splice_tail((yyvsp[-2].list), &ct->timeout_list);
				xfree((yyvsp[-2].list));
			}
#line 11226 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 712:
#line 4276 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 11234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 713:
#line 4282 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 11242 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 714:
#line 4286 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 11250 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 715:
#line 4290 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 11258 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 716:
#line 4294 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 11266 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 717:
#line 4298 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 11274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 718:
#line 4304 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 11282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 719:
#line 4310 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;

				limit = &(yyvsp[-6].obj)->limit;
				limit->rate	= (yyvsp[-3].val);
				limit->unit	= (yyvsp[-1].val);
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-4].val);
			}
#line 11297 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 720:
#line 4321 "parser_bison.y" /* yacc.c:1652  */
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
#line 11320 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 721:
#line 4342 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 11329 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 722:
#line 4349 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 11337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 723:
#line 4353 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 11345 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 724:
#line 4357 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11353 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 725:
#line 4363 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 726:
#line 4369 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 727:
#line 4376 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11379 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 728:
#line 4377 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 729:
#line 4378 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 730:
#line 4379 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11397 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 732:
#line 4384 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11405 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 733:
#line 4388 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11413 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 735:
#line 4395 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11421 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 737:
#line 4402 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11429 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 739:
#line 4409 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11437 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 743:
#line 4420 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 11450 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 744:
#line 4429 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 11463 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 745:
#line 4439 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = true; }
#line 11469 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 746:
#line 4440 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = false; }
#line 11475 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 747:
#line 4444 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 11485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 748:
#line 4451 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 11491 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 749:
#line 4452 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 11497 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 750:
#line 4453 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 11503 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 751:
#line 4454 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 11509 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 752:
#line 4455 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 11515 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 753:
#line 4456 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 11521 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 754:
#line 4457 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 11527 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 755:
#line 4458 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 11533 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 756:
#line 4459 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 11539 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 757:
#line 4460 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 11545 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 758:
#line 4461 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 11551 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 759:
#line 4462 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 11557 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 760:
#line 4465 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11563 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 761:
#line 4466 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11569 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 762:
#line 4467 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11575 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 763:
#line 4468 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11581 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 764:
#line 4470 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11592 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 765:
#line 4477 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 766:
#line 4484 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11614 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 767:
#line 4491 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 768:
#line 4498 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11636 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 769:
#line 4505 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11647 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 770:
#line 4512 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11658 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 771:
#line 4519 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11669 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 772:
#line 4526 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11680 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 773:
#line 4533 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 774:
#line 4540 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11702 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 775:
#line 4547 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11713 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 776:
#line 4553 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 11719 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 777:
#line 4556 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_EQ; }
#line 11725 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 778:
#line 4557 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_NEQ; }
#line 11731 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 779:
#line 4558 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LT; }
#line 11737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 780:
#line 4559 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GT; }
#line 11743 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 781:
#line 4560 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GTE; }
#line 11749 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 782:
#line 4561 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LTE; }
#line 11755 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 783:
#line 4565 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 11763 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 784:
#line 4569 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 11771 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 785:
#line 4573 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 11779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 786:
#line 4577 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 11787 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 787:
#line 4581 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 11795 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 788:
#line 4585 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 11803 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 790:
#line 4592 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 11815 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 791:
#line 4602 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11823 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 792:
#line 4606 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11831 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 793:
#line 4610 "parser_bison.y" /* yacc.c:1652  */
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
#line 11849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 796:
#line 4629 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_LEN; }
#line 11855 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 797:
#line 4630 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 11861 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 798:
#line 4631 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 11867 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 799:
#line 4632 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 11873 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 800:
#line 4633 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECMARK; }
#line 11879 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 801:
#line 4636 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_MARK; }
#line 11885 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 802:
#line 4637 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIF; }
#line 11891 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 803:
#line 4638 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 11897 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 804:
#line 4639 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 11903 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 805:
#line 4640 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIF; }
#line 11909 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 806:
#line 4641 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 11915 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 807:
#line 4642 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 11921 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 808:
#line 4643 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKUID; }
#line 11927 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 809:
#line 4644 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKGID; }
#line 11933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 810:
#line 4645 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 11939 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 811:
#line 4646 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 11945 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 812:
#line 4647 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 11951 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 813:
#line 4648 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 11957 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 814:
#line 4649 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 11963 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 815:
#line 4650 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 11969 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 816:
#line 4651 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 11975 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 817:
#line 4652 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CPU; }
#line 11981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 818:
#line 4653 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 11987 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 819:
#line 4654 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 11993 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 820:
#line 4655 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 11999 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 821:
#line 4656 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECPATH; }
#line 12005 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 822:
#line 4657 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_NS; }
#line 12011 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 823:
#line 4658 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_DAY; }
#line 12017 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 824:
#line 4659 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_HOUR; }
#line 12023 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 825:
#line 4663 "parser_bison.y" /* yacc.c:1652  */
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
#line 12047 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 826:
#line 4683 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 12055 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 827:
#line 4687 "parser_bison.y" /* yacc.c:1652  */
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
#line 12073 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 828:
#line 4701 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 12081 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 829:
#line 4705 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 12089 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 830:
#line 4709 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 12097 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 831:
#line 4715 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 12105 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 832:
#line 4720 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 12111 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 833:
#line 4721 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_MARK; }
#line 12117 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 834:
#line 4722 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_WILDCARD; }
#line 12123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 835:
#line 4725 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 12129 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 836:
#line 4726 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 12135 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 837:
#line 4729 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 12141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 838:
#line 4730 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 12147 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 839:
#line 4734 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 12155 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 840:
#line 4739 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 12161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 841:
#line 4740 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 12167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 842:
#line 4743 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_IN; }
#line 12173 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 843:
#line 4744 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_OUT; }
#line 12179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 844:
#line 4747 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 12185 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 845:
#line 4748 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 12191 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 846:
#line 4751 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 12197 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 847:
#line 4752 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 12203 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 848:
#line 4756 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-1].val) > 255) {
					erec_queue(error(&(yylsp[-1]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 12215 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 849:
#line 4764 "parser_bison.y" /* yacc.c:1652  */
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
#line 12244 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 850:
#line 4791 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 12253 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 851:
#line 4796 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 12262 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 852:
#line 4801 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 12270 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 853:
#line 4806 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 12276 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 854:
#line 4807 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 12282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 855:
#line 4811 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 12290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 856:
#line 4815 "parser_bison.y" /* yacc.c:1652  */
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
#line 12312 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 857:
#line 4834 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 12318 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 858:
#line 4835 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 12324 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 859:
#line 4836 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 12330 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 860:
#line 4837 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_XFRM; }
#line 12336 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 861:
#line 4841 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1);
			}
#line 12344 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 862:
#line 4845 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 12352 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 863:
#line 4849 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 12360 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 864:
#line 4854 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 12366 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 865:
#line 4855 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 12372 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 866:
#line 4858 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 12378 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 867:
#line 4859 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 12384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 868:
#line 4860 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_MARK; }
#line 12390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 869:
#line 4861 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATE; }
#line 12396 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 870:
#line 4862 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 12402 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 871:
#line 4863 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 12408 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 872:
#line 4864 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 12414 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 873:
#line 4865 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 12420 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 874:
#line 4866 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 12426 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 875:
#line 4867 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 12432 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 876:
#line 4868 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 12438 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 877:
#line 4869 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 12444 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 878:
#line 4870 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 12450 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 879:
#line 4871 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 12456 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 880:
#line 4872 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SECMARK; }
#line 12462 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 881:
#line 4873 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ID; }
#line 12468 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 883:
#line 4877 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 12474 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 884:
#line 4878 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 12480 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 885:
#line 4879 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 12486 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 886:
#line 4880 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 12492 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 887:
#line 4881 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 12498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 888:
#line 4882 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 12504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 890:
#line 4886 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP; }
#line 12510 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 891:
#line 4887 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP; }
#line 12516 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 892:
#line 4888 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP6; }
#line 12522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 893:
#line 4889 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP6; }
#line 12528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 894:
#line 4892 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 12534 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 895:
#line 4893 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 12540 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 896:
#line 4894 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 12546 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 897:
#line 4895 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 12552 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 900:
#line 4903 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 12562 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 901:
#line 4909 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 12572 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 902:
#line 4917 "parser_bison.y" /* yacc.c:1652  */
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
#line 12589 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 903:
#line 4930 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);

			}
#line 12600 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 904:
#line 4937 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 12610 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 905:
#line 4943 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 12618 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 906:
#line 4949 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12629 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 925:
#line 4978 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 12640 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 926:
#line 4986 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 12646 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 927:
#line 4987 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 12652 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 928:
#line 4988 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 12658 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 929:
#line 4992 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 12666 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 930:
#line 4997 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 12672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 931:
#line 4998 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 12678 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 932:
#line 4999 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 12684 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 933:
#line 5003 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 12692 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 934:
#line 5008 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_VID; }
#line 12698 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 935:
#line 5009 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_CFI; }
#line 12704 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 936:
#line 5010 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_PCP; }
#line 12710 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 937:
#line 5011 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 12716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 938:
#line 5015 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 12724 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 939:
#line 5020 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HRD; }
#line 12730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 940:
#line 5021 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PRO; }
#line 12736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 941:
#line 5022 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HLN; }
#line 12742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 942:
#line 5023 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PLN; }
#line 12748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 943:
#line 5024 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_OP; }
#line 12754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 944:
#line 5025 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 12760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 945:
#line 5026 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 12766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 946:
#line 5027 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_IP; }
#line 12772 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 947:
#line 5028 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_IP; }
#line 12778 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 948:
#line 5032 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 12786 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 949:
#line 5036 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val), 0);
			}
#line 12794 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 950:
#line 5040 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[0].val), IPOPT_FIELD_TYPE, 0);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 12803 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 951:
#line 5046 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_VERSION; }
#line 12809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 952:
#line 5047 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 12815 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 953:
#line 5048 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DSCP; }
#line 12821 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 954:
#line 5049 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ECN; }
#line 12827 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 955:
#line 5050 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 12833 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 956:
#line 5051 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ID; }
#line 12839 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 957:
#line 5052 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 12845 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 958:
#line 5053 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_TTL; }
#line 12851 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 959:
#line 5054 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 12857 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 960:
#line 5055 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 12863 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 961:
#line 5056 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_SADDR; }
#line 12869 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 962:
#line 5057 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DADDR; }
#line 12875 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 963:
#line 5060 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_LSRR; }
#line 12881 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 964:
#line 5061 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RR; }
#line 12887 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 965:
#line 5062 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_SSRR; }
#line 12893 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 966:
#line 5063 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RA; }
#line 12899 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 967:
#line 5066 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 12905 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 968:
#line 5067 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 12911 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 969:
#line 5068 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 12917 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 970:
#line 5069 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_PTR; }
#line 12923 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 971:
#line 5070 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 12929 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 972:
#line 5074 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 12937 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 973:
#line 5079 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 12943 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 974:
#line 5080 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 12949 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 975:
#line 5081 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 12955 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 976:
#line 5082 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_ID; }
#line 12961 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 977:
#line 5083 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 12967 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 978:
#line 5084 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 12973 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 979:
#line 5085 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 12979 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 980:
#line 5089 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[0].val));
			}
#line 12987 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 981:
#line 5094 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_TYPE; }
#line 12993 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 982:
#line 5095 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 12999 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 983:
#line 5096 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_MRT; }
#line 13005 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 984:
#line 5097 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_GROUP; }
#line 13011 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 985:
#line 5101 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 13019 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 986:
#line 5106 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 13025 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 987:
#line 5107 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 13031 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 988:
#line 5108 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_ECN; }
#line 13037 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 989:
#line 5109 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 13043 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 990:
#line 5110 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 13049 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 991:
#line 5111 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 13055 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 992:
#line 5112 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 13061 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 993:
#line 5113 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 13067 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 994:
#line 5114 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 13073 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 995:
#line 5117 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 13081 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 996:
#line 5122 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 13087 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 997:
#line 5123 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 13093 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 998:
#line 5124 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 13099 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 999:
#line 5125 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 13105 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1000:
#line 5126 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 13111 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1001:
#line 5127 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 13117 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1002:
#line 5128 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 13123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1003:
#line 5129 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 13129 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1004:
#line 5133 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 13137 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1005:
#line 5138 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 13143 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1006:
#line 5139 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 13149 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1007:
#line 5140 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 13155 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1008:
#line 5141 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SPI; }
#line 13161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1009:
#line 5142 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 13167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1010:
#line 5146 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 13175 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1011:
#line 5151 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SPI; }
#line 13181 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1012:
#line 5152 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 13187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1013:
#line 5156 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 13195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1014:
#line 5161 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 13201 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1015:
#line 5162 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 13207 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1016:
#line 5163 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_CPI; }
#line 13213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1017:
#line 5167 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 13221 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1018:
#line 5172 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 13227 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1019:
#line 5173 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 13233 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1020:
#line 5174 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 13239 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1021:
#line 5175 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 13245 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1022:
#line 5179 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 13253 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1023:
#line 5184 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 13259 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1024:
#line 5185 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 13265 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1025:
#line 5186 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 13271 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1026:
#line 5187 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 13277 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1027:
#line 5191 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 13285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1028:
#line 5195 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 13293 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1029:
#line 5199 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 13302 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1030:
#line 5205 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 13308 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1031:
#line 5206 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 13314 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1032:
#line 5207 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 13320 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1033:
#line 5208 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 13326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1034:
#line 5209 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 13332 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1035:
#line 5210 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 13338 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1036:
#line 5211 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 13344 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1037:
#line 5212 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 13350 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1038:
#line 5213 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 13356 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1039:
#line 5214 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 13362 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1040:
#line 5217 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 13368 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1041:
#line 5218 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 13374 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1042:
#line 5219 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 13380 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1043:
#line 5220 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 13386 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1044:
#line 5221 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 13392 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1045:
#line 5222 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 13398 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1046:
#line 5223 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 13404 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1047:
#line 5224 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 13410 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1048:
#line 5225 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 13416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1049:
#line 5226 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 13422 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1050:
#line 5227 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 13428 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1051:
#line 5228 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 13434 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1052:
#line 5231 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 13440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1053:
#line 5232 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 13446 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1054:
#line 5233 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 13452 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1055:
#line 5234 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 13458 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1056:
#line 5235 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 13464 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1057:
#line 5236 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 13470 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1058:
#line 5237 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 13476 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1059:
#line 5238 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 13482 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1060:
#line 5242 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 13490 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1061:
#line 5247 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 13496 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1062:
#line 5248 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 13502 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1063:
#line 5249 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 13508 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1064:
#line 5253 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 13516 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1065:
#line 5258 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 13522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1066:
#line 5259 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 13528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1067:
#line 5260 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 13534 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1068:
#line 5261 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 13540 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1069:
#line 5265 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[0].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 13550 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1070:
#line 5272 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_SPORT; }
#line 13556 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1071:
#line 5273 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_DPORT; }
#line 13562 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1080:
#line 5287 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 13570 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1081:
#line 5292 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 13576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1082:
#line 5293 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 13582 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1083:
#line 5297 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 13590 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1084:
#line 5302 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 13596 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1085:
#line 5303 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 13602 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1086:
#line 5304 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_TYPE; }
#line 13608 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1087:
#line 5305 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 13614 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1088:
#line 5309 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 13622 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1089:
#line 5315 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 13630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1090:
#line 5321 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 13638 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1091:
#line 5326 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 13644 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1092:
#line 5330 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 13652 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1093:
#line 5335 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 13658 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1094:
#line 5336 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 13664 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1095:
#line 5337 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_TAG; }
#line 13670 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1096:
#line 5339 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 13678 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1097:
#line 5345 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 13686 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1098:
#line 5350 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 13692 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1099:
#line 5351 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 13698 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1100:
#line 5352 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 13704 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1101:
#line 5353 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 13710 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1102:
#line 5354 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 13716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1103:
#line 5355 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_ID; }
#line 13722 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1104:
#line 5359 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 13730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1105:
#line 5364 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 13736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1106:
#line 5365 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 13742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1107:
#line 5369 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 13750 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1108:
#line 5374 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 13756 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1109:
#line 5375 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 13762 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1110:
#line 5376 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_TYPE; }
#line 13768 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1111:
#line 5377 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 13774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1112:
#line 5378 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 13780 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1113:
#line 5382 "parser_bison.y" /* yacc.c:1652  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 13796 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1114:
#line 5395 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 13802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1115:
#line 5396 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 13808 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1116:
#line 5397 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 13814 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1117:
#line 5398 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 13820 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1118:
#line 5399 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_MH; }
#line 13826 "parser_bison.c" /* yacc.c:1652  */
    break;


#line 13830 "parser_bison.c" /* yacc.c:1652  */
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
#line 5402 "parser_bison.y" /* yacc.c:1918  */

