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
    NOP = 430,
    SACK = 431,
    SACK0 = 432,
    SACK1 = 433,
    SACK2 = 434,
    SACK3 = 435,
    SACK_PERM = 436,
    TIMESTAMP = 437,
    KIND = 438,
    COUNT = 439,
    LEFT = 440,
    RIGHT = 441,
    TSVAL = 442,
    TSECR = 443,
    DCCP = 444,
    SCTP = 445,
    VTAG = 446,
    RT = 447,
    RT0 = 448,
    RT2 = 449,
    RT4 = 450,
    SEG_LEFT = 451,
    ADDR = 452,
    LAST_ENT = 453,
    TAG = 454,
    SID = 455,
    HBH = 456,
    FRAG = 457,
    RESERVED2 = 458,
    MORE_FRAGMENTS = 459,
    DST = 460,
    MH = 461,
    META = 462,
    MARK = 463,
    IIF = 464,
    IIFNAME = 465,
    IIFTYPE = 466,
    OIF = 467,
    OIFNAME = 468,
    OIFTYPE = 469,
    SKUID = 470,
    SKGID = 471,
    NFTRACE = 472,
    RTCLASSID = 473,
    IBRIPORT = 474,
    OBRIPORT = 475,
    IBRIDGENAME = 476,
    OBRIDGENAME = 477,
    PKTTYPE = 478,
    CPU = 479,
    IIFGROUP = 480,
    OIFGROUP = 481,
    CGROUP = 482,
    TIME = 483,
    CLASSID = 484,
    NEXTHOP = 485,
    CT = 486,
    L3PROTOCOL = 487,
    PROTO_SRC = 488,
    PROTO_DST = 489,
    ZONE = 490,
    DIRECTION = 491,
    EVENT = 492,
    EXPECTATION = 493,
    EXPIRATION = 494,
    HELPER = 495,
    LABEL = 496,
    STATE = 497,
    STATUS = 498,
    ORIGINAL = 499,
    REPLY = 500,
    COUNTER = 501,
    NAME = 502,
    PACKETS = 503,
    BYTES = 504,
    AVGPKT = 505,
    COUNTERS = 506,
    QUOTAS = 507,
    LIMITS = 508,
    SYNPROXYS = 509,
    HELPERS = 510,
    LOG = 511,
    PREFIX = 512,
    GROUP = 513,
    SNAPLEN = 514,
    QUEUE_THRESHOLD = 515,
    LEVEL = 516,
    LIMIT = 517,
    RATE = 518,
    BURST = 519,
    OVER = 520,
    UNTIL = 521,
    QUOTA = 522,
    USED = 523,
    SECMARK = 524,
    SECMARKS = 525,
    NANOSECOND = 526,
    MICROSECOND = 527,
    MILLISECOND = 528,
    SECOND = 529,
    MINUTE = 530,
    HOUR = 531,
    DAY = 532,
    WEEK = 533,
    _REJECT = 534,
    WITH = 535,
    ICMPX = 536,
    SNAT = 537,
    DNAT = 538,
    MASQUERADE = 539,
    REDIRECT = 540,
    RANDOM = 541,
    FULLY_RANDOM = 542,
    PERSISTENT = 543,
    QUEUE = 544,
    QUEUENUM = 545,
    BYPASS = 546,
    FANOUT = 547,
    DUP = 548,
    FWD = 549,
    NUMGEN = 550,
    INC = 551,
    MOD = 552,
    OFFSET = 553,
    JHASH = 554,
    SYMHASH = 555,
    SEED = 556,
    POSITION = 557,
    INDEX = 558,
    COMMENT = 559,
    XML = 560,
    JSON = 561,
    VM = 562,
    NOTRACK = 563,
    EXISTS = 564,
    MISSING = 565,
    EXTHDR = 566,
    IPSEC = 567,
    MODE = 568,
    REQID = 569,
    SPNUM = 570,
    TRANSPORT = 571,
    TUNNEL = 572,
    IN = 573,
    OUT = 574
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
#define NOP 430
#define SACK 431
#define SACK0 432
#define SACK1 433
#define SACK2 434
#define SACK3 435
#define SACK_PERM 436
#define TIMESTAMP 437
#define KIND 438
#define COUNT 439
#define LEFT 440
#define RIGHT 441
#define TSVAL 442
#define TSECR 443
#define DCCP 444
#define SCTP 445
#define VTAG 446
#define RT 447
#define RT0 448
#define RT2 449
#define RT4 450
#define SEG_LEFT 451
#define ADDR 452
#define LAST_ENT 453
#define TAG 454
#define SID 455
#define HBH 456
#define FRAG 457
#define RESERVED2 458
#define MORE_FRAGMENTS 459
#define DST 460
#define MH 461
#define META 462
#define MARK 463
#define IIF 464
#define IIFNAME 465
#define IIFTYPE 466
#define OIF 467
#define OIFNAME 468
#define OIFTYPE 469
#define SKUID 470
#define SKGID 471
#define NFTRACE 472
#define RTCLASSID 473
#define IBRIPORT 474
#define OBRIPORT 475
#define IBRIDGENAME 476
#define OBRIDGENAME 477
#define PKTTYPE 478
#define CPU 479
#define IIFGROUP 480
#define OIFGROUP 481
#define CGROUP 482
#define TIME 483
#define CLASSID 484
#define NEXTHOP 485
#define CT 486
#define L3PROTOCOL 487
#define PROTO_SRC 488
#define PROTO_DST 489
#define ZONE 490
#define DIRECTION 491
#define EVENT 492
#define EXPECTATION 493
#define EXPIRATION 494
#define HELPER 495
#define LABEL 496
#define STATE 497
#define STATUS 498
#define ORIGINAL 499
#define REPLY 500
#define COUNTER 501
#define NAME 502
#define PACKETS 503
#define BYTES 504
#define AVGPKT 505
#define COUNTERS 506
#define QUOTAS 507
#define LIMITS 508
#define SYNPROXYS 509
#define HELPERS 510
#define LOG 511
#define PREFIX 512
#define GROUP 513
#define SNAPLEN 514
#define QUEUE_THRESHOLD 515
#define LEVEL 516
#define LIMIT 517
#define RATE 518
#define BURST 519
#define OVER 520
#define UNTIL 521
#define QUOTA 522
#define USED 523
#define SECMARK 524
#define SECMARKS 525
#define NANOSECOND 526
#define MICROSECOND 527
#define MILLISECOND 528
#define SECOND 529
#define MINUTE 530
#define HOUR 531
#define DAY 532
#define WEEK 533
#define _REJECT 534
#define WITH 535
#define ICMPX 536
#define SNAT 537
#define DNAT 538
#define MASQUERADE 539
#define REDIRECT 540
#define RANDOM 541
#define FULLY_RANDOM 542
#define PERSISTENT 543
#define QUEUE 544
#define QUEUENUM 545
#define BYPASS 546
#define FANOUT 547
#define DUP 548
#define FWD 549
#define NUMGEN 550
#define INC 551
#define MOD 552
#define OFFSET 553
#define JHASH 554
#define SYMHASH 555
#define SEED 556
#define POSITION 557
#define INDEX 558
#define COMMENT 559
#define XML 560
#define JSON 561
#define VM 562
#define NOTRACK 563
#define EXISTS 564
#define MISSING 565
#define EXTHDR 566
#define IPSEC 567
#define MODE 568
#define REQID 569
#define SPNUM 570
#define TRANSPORT 571
#define TUNNEL 572
#define IN 573
#define OUT 574

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

#line 917 "parser_bison.c" /* yacc.c:352  */
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
#define YYLAST   7523

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  329
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  345
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1127
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1848

#define YYUNDEFTOK  2
#define YYMAXUTOK   574

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
       2,     2,     2,     2,     2,     2,   326,     2,     2,     2,
     323,   324,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   320,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   327,     2,   328,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   321,   325,   322,     2,     2,     2,     2,
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
     315,   316,   317,   318,   319
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   841,   841,   842,   851,   852,   855,   856,   859,   867,
     882,   889,   900,   908,   909,   910,   911,   931,   932,   933,
     934,   935,   936,   937,   938,   939,   940,   941,   942,   943,
     944,   945,   948,   952,   959,   963,   971,   975,   979,   986,
     993,   997,  1004,  1013,  1017,  1021,  1025,  1029,  1033,  1037,
    1041,  1045,  1049,  1053,  1057,  1061,  1067,  1073,  1077,  1084,
    1088,  1096,  1103,  1110,  1114,  1121,  1130,  1134,  1138,  1142,
    1146,  1150,  1154,  1158,  1164,  1170,  1174,  1178,  1182,  1186,
    1190,  1194,  1198,  1202,  1206,  1210,  1214,  1221,  1225,  1229,
    1233,  1237,  1241,  1245,  1249,  1253,  1257,  1261,  1267,  1273,
    1277,  1281,  1285,  1289,  1293,  1297,  1301,  1305,  1309,  1313,
    1317,  1321,  1325,  1329,  1333,  1337,  1341,  1345,  1349,  1353,
    1357,  1361,  1365,  1369,  1373,  1377,  1381,  1385,  1389,  1393,
    1397,  1401,  1405,  1409,  1415,  1419,  1423,  1427,  1431,  1435,
    1441,  1445,  1449,  1453,  1457,  1461,  1465,  1471,  1478,  1484,
    1492,  1498,  1506,  1515,  1516,  1519,  1520,  1521,  1522,  1523,
    1524,  1525,  1526,  1529,  1530,  1533,  1534,  1535,  1538,  1547,
    1553,  1565,  1575,  1576,  1577,  1578,  1579,  1590,  1600,  1611,
    1621,  1632,  1643,  1652,  1661,  1670,  1681,  1692,  1706,  1712,
    1713,  1714,  1715,  1716,  1717,  1718,  1723,  1733,  1734,  1735,
    1742,  1753,  1766,  1771,  1772,  1773,  1774,  1779,  1785,  1790,
    1795,  1800,  1806,  1811,  1816,  1817,  1828,  1829,  1832,  1836,
    1839,  1840,  1841,  1842,  1846,  1851,  1852,  1853,  1854,  1859,
    1869,  1880,  1891,  1903,  1912,  1921,  1930,  1939,  1944,  1949,
    1958,  1961,  1965,  1971,  1972,  1976,  1981,  1982,  1983,  1984,
    1998,  2002,  2008,  2013,  2020,  2025,  2030,  2033,  2040,  2047,
    2059,  2066,  2067,  2079,  2084,  2085,  2086,  2087,  2091,  2101,
    2102,  2103,  2104,  2108,  2118,  2119,  2120,  2121,  2125,  2136,
    2140,  2141,  2142,  2146,  2156,  2157,  2158,  2159,  2163,  2173,
    2174,  2175,  2176,  2180,  2190,  2191,  2192,  2193,  2197,  2207,
    2208,  2209,  2210,  2214,  2224,  2225,  2226,  2227,  2228,  2231,
    2261,  2268,  2272,  2275,  2285,  2292,  2303,  2316,  2331,  2332,
    2335,  2347,  2353,  2357,  2360,  2366,  2379,  2384,  2393,  2394,
    2397,  2400,  2401,  2402,  2405,  2420,  2421,  2424,  2425,  2426,
    2427,  2428,  2429,  2432,  2441,  2450,  2458,  2466,  2474,  2482,
    2490,  2498,  2506,  2514,  2522,  2530,  2538,  2546,  2554,  2562,
    2570,  2574,  2579,  2587,  2594,  2601,  2614,  2618,  2625,  2629,
    2635,  2647,  2653,  2660,  2666,  2673,  2674,  2675,  2676,  2679,
    2680,  2681,  2682,  2683,  2684,  2685,  2686,  2687,  2688,  2689,
    2690,  2691,  2692,  2693,  2694,  2695,  2696,  2697,  2698,  2701,
    2702,  2705,  2714,  2718,  2724,  2730,  2735,  2738,  2743,  2748,
    2751,  2757,  2762,  2770,  2771,  2773,  2777,  2785,  2789,  2792,
    2796,  2802,  2803,  2806,  2812,  2816,  2819,  2944,  2949,  2954,
    2959,  2964,  2970,  3000,  3004,  3008,  3012,  3016,  3022,  3026,
    3029,  3033,  3039,  3053,  3078,  3086,  3087,  3088,  3091,  3092,
    3095,  3096,  3111,  3127,  3135,  3136,  3137,  3140,  3141,  3144,
    3145,  3146,  3161,  3162,  3163,  3164,  3165,  3168,  3171,  3178,
    3182,  3193,  3204,  3214,  3220,  3223,  3224,  3227,  3233,  3239,
    3245,  3252,  3259,  3267,  3268,  3271,  3275,  3283,  3287,  3290,
    3295,  3300,  3304,  3310,  3326,  3345,  3351,  3352,  3358,  3359,
    3365,  3366,  3367,  3368,  3369,  3370,  3371,  3372,  3373,  3374,
    3375,  3376,  3377,  3380,  3381,  3385,  3391,  3392,  3398,  3399,
    3405,  3406,  3412,  3415,  3416,  3427,  3428,  3431,  3435,  3438,
    3444,  3450,  3461,  3462,  3463,  3466,  3467,  3468,  3471,  3475,
    3479,  3484,  3489,  3494,  3500,  3504,  3508,  3512,  3518,  3524,
    3529,  3538,  3548,  3549,  3552,  3555,  3559,  3564,  3570,  3571,
    3574,  3577,  3581,  3585,  3589,  3594,  3601,  3606,  3614,  3619,
    3628,  3629,  3635,  3636,  3637,  3640,  3641,  3644,  3650,  3654,
    3657,  3662,  3668,  3669,  3675,  3676,  3679,  3680,  3683,  3689,
    3696,  3703,  3714,  3715,  3716,  3719,  3727,  3739,  3746,  3749,
    3755,  3759,  3762,  3768,  3777,  3788,  3794,  3820,  3821,  3830,
    3831,  3834,  3843,  3854,  3855,  3856,  3857,  3858,  3859,  3860,
    3861,  3862,  3863,  3864,  3865,  3866,  3867,  3868,  3871,  3894,
    3895,  3896,  3899,  3900,  3901,  3902,  3903,  3906,  3910,  3913,
    3917,  3924,  3927,  3941,  3942,  3946,  3952,  3953,  3959,  3960,
    3966,  3967,  3973,  3976,  3977,  3988,  3994,  4000,  4001,  4004,
    4010,  4011,  4012,  4015,  4022,  4027,  4032,  4035,  4039,  4043,
    4049,  4050,  4057,  4063,  4064,  4067,  4073,  4079,  4083,  4086,
    4090,  4094,  4104,  4108,  4111,  4117,  4124,  4128,  4134,  4148,
    4174,  4178,  4182,  4192,  4193,  4196,  4197,  4200,  4201,  4202,
    4203,  4214,  4225,  4231,  4252,  4258,  4275,  4281,  4282,  4283,
    4286,  4287,  4290,  4306,  4312,  4318,  4325,  4339,  4347,  4355,
    4361,  4365,  4369,  4373,  4377,  4384,  4389,  4400,  4422,  4428,
    4432,  4436,  4442,  4448,  4456,  4457,  4458,  4459,  4462,  4463,
    4467,  4473,  4474,  4480,  4481,  4487,  4488,  4494,  4497,  4498,
    4499,  4508,  4519,  4520,  4523,  4531,  4532,  4533,  4534,  4535,
    4536,  4537,  4538,  4539,  4540,  4541,  4542,  4545,  4546,  4547,
    4548,  4549,  4556,  4563,  4570,  4577,  4584,  4591,  4598,  4605,
    4612,  4619,  4626,  4633,  4636,  4637,  4638,  4639,  4640,  4641,
    4644,  4648,  4652,  4656,  4660,  4664,  4670,  4671,  4681,  4685,
    4689,  4705,  4706,  4709,  4710,  4711,  4712,  4713,  4716,  4717,
    4718,  4719,  4720,  4721,  4722,  4723,  4724,  4725,  4726,  4727,
    4728,  4729,  4730,  4731,  4732,  4733,  4734,  4735,  4736,  4737,
    4738,  4739,  4742,  4762,  4766,  4780,  4784,  4788,  4794,  4800,
    4801,  4802,  4805,  4806,  4809,  4810,  4813,  4819,  4820,  4823,
    4824,  4827,  4828,  4831,  4832,  4835,  4843,  4870,  4875,  4880,
    4886,  4887,  4890,  4894,  4914,  4915,  4916,  4917,  4920,  4924,
    4928,  4934,  4935,  4938,  4939,  4940,  4941,  4942,  4943,  4944,
    4945,  4946,  4947,  4948,  4949,  4950,  4951,  4952,  4953,  4954,
    4957,  4958,  4959,  4960,  4961,  4962,  4963,  4966,  4967,  4968,
    4969,  4972,  4973,  4974,  4975,  4978,  4979,  4982,  4988,  4996,
    5009,  5016,  5022,  5028,  5037,  5038,  5039,  5040,  5041,  5042,
    5043,  5044,  5045,  5046,  5047,  5048,  5049,  5050,  5051,  5052,
    5053,  5054,  5057,  5066,  5067,  5068,  5071,  5077,  5078,  5079,
    5082,  5088,  5089,  5090,  5091,  5094,  5100,  5101,  5102,  5103,
    5104,  5105,  5106,  5107,  5108,  5111,  5115,  5119,  5126,  5127,
    5128,  5129,  5130,  5131,  5132,  5133,  5134,  5135,  5136,  5137,
    5140,  5141,  5142,  5143,  5146,  5147,  5148,  5149,  5150,  5153,
    5159,  5160,  5161,  5162,  5163,  5164,  5165,  5168,  5174,  5175,
    5176,  5177,  5180,  5186,  5187,  5188,  5189,  5190,  5191,  5192,
    5193,  5194,  5196,  5202,  5203,  5204,  5205,  5206,  5207,  5208,
    5209,  5212,  5218,  5219,  5220,  5221,  5222,  5225,  5231,  5232,
    5235,  5241,  5242,  5243,  5246,  5252,  5253,  5254,  5255,  5258,
    5264,  5265,  5266,  5267,  5270,  5274,  5278,  5283,  5290,  5291,
    5292,  5293,  5294,  5295,  5296,  5297,  5298,  5299,  5302,  5303,
    5304,  5305,  5306,  5307,  5308,  5309,  5310,  5311,  5312,  5313,
    5314,  5323,  5324,  5325,  5326,  5327,  5328,  5329,  5330,  5333,
    5339,  5340,  5341,  5344,  5350,  5351,  5352,  5353,  5356,  5364,
    5365,  5368,  5369,  5370,  5371,  5372,  5373,  5374,  5375,  5378,
    5384,  5385,  5388,  5394,  5395,  5396,  5397,  5400,  5406,  5412,
    5418,  5421,  5427,  5428,  5429,  5430,  5436,  5442,  5443,  5444,
    5445,  5446,  5447,  5450,  5456,  5457,  5460,  5466,  5467,  5468,
    5469,  5470,  5473,  5487,  5488,  5489,  5490,  5491
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
  "\"osf\"", "\"synproxy\"", "\"mss\"", "\"wscale\"", "\"typeof\"",
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
  "\"eol\"", "\"nop\"", "\"sack\"", "\"sack0\"", "\"sack1\"", "\"sack2\"",
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
  "stmt_list", "stateful_stmt_list", "stateful_stmt", "stmt",
  "chain_stmt_type", "chain_stmt", "verdict_stmt", "verdict_map_stmt",
  "verdict_map_expr", "verdict_map_list_expr",
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
  "set_elem_options", "set_elem_option", "set_elem_expr_options",
  "set_elem_stmt_list", "set_elem_stmt", "set_elem_expr_option",
  "set_lhs_expr", "set_rhs_expr", "initializer_expr", "counter_config",
  "counter_obj", "quota_config", "quota_obj", "secmark_config",
  "secmark_obj", "ct_obj_type", "ct_l4protoname", "ct_helper_config",
  "timeout_states", "timeout_state", "ct_timeout_config",
  "ct_expect_config", "ct_obj_alloc", "limit_config", "limit_obj",
  "relational_expr", "list_rhs_expr", "rhs_expr", "shift_rhs_expr",
  "and_rhs_expr", "exclusive_or_rhs_expr", "inclusive_or_rhs_expr",
  "basic_rhs_expr", "concat_rhs_expr", "boolean_keys", "boolean_expr",
  "keyword_expr", "primary_rhs_expr", "relational_op", "verdict_expr",
  "chain_expr", "meta_expr", "meta_key", "meta_key_qualified",
  "meta_key_unqualified", "meta_stmt", "socket_expr", "socket_key",
  "offset_opt", "numgen_type", "numgen_expr", "xfrm_spnum", "xfrm_dir",
  "xfrm_state_key", "xfrm_state_proto_key", "xfrm_expr", "hash_expr",
  "nf_key_proto", "rt_expr", "rt_key", "ct_expr", "ct_dir", "ct_key",
  "ct_key_dir", "ct_key_proto_field", "ct_key_dir_optional",
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
      61,   123,   125,    40,    41,   124,    36,    91,    93
};
# endif

#define YYPACT_NINF -1553

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1553)))

#define YYTABLE_NINF -907

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1553,  6982, -1553,   351, -1553, -1553,    86,   122,   122,   122,
     876,   876,   876,   876,   876,   876,   876,   876, -1553, -1553,
    3376,   188,  2201,   191,  2085,   193,  7253,   344,   906,   219,
    6481,   140,   176,   165, -1553, -1553, -1553, -1553,   260,   876,
     876,   876,   876, -1553, -1553, -1553,   562, -1553,   122, -1553,
     122,   137,  5951, -1553,   351, -1553,   -48,   -15,   351,   122,
   -1553,     1,    19,  5951,   122, -1553,   315, -1553,   122, -1553,
   -1553,   876, -1553,   876,   876,   876,   876,   876,   876,   876,
     370,   876,   876,   876,   876, -1553,   876, -1553,   876,   876,
     876,   876,   876,   876,   876,   876,   410,   876,   876,   876,
     876, -1553,   876, -1553,   876,   876,   876,   876,   876,   496,
     876,   876,   876,   876,   876,   779,   876,   876,   876,   421,
     876,  1094,  1330,  1514,  1613,   876,   876,   876,  1672, -1553,
     876,  1935,  2046,   876, -1553,   876,   876,   876,   876,   876,
     301,   876, -1553,   876, -1553,   748,   523,   230,   252, -1553,
   -1553, -1553, -1553,   738,   769,   770,  1373,  3207,  1108,    76,
    1718,  1391,   824,   443,   599,   555,   564,  2945,   422,   652,
    1194,   238,   306,   545,   345,   701,   368,   716,  4238, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
    5370, -1553, -1553,   279,  6179,   159,   861,   492,  6481,   122,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553,   626, -1553, -1553,   215, -1553,
   -1553,   626, -1553, -1553, -1553, -1553,  1273,   876,   876,   876,
     -71, -1553, -1553, -1553, -1553, -1553, -1553, -1553,   480,   554,
     572, -1553, -1553, -1553,   170,   360,   727, -1553, -1553, -1553,
   -1553, -1553, -1553,    -2,    -2, -1553,   114,   122,  4466,  5160,
     433, -1553,   446,   423, -1553, -1553, -1553, -1553, -1553, -1553,
     602,   425, -1553,   709, -1553,   416,  5951, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553,   688, -1553,   708, -1553, -1553,
   -1553,   454, -1553,  4050, -1553, -1553,   447, -1553,    31, -1553,
     333, -1553, -1553, -1553,   686, -1553,   111, -1553, -1553,   695,
   -1553, -1553, -1553,   925,   735,   754,   449, -1553,   565, -1553,
    5199, -1553, -1553, -1553,   749, -1553, -1553, -1553,   755, -1553,
    5561,  5561, -1553, -1553,    61,   521,   525, -1553, -1553,   528,
   -1553, -1553, -1553,   547, -1553,   577,   762,  5951, -1553,     1,
      19, -1553,   315, -1553, -1553,   876,   876,   876,   615, -1553,
   -1553, -1553,  5951,   259, -1553, -1553,   411, -1553, -1553,   436,
   -1553, -1553, -1553,   455, -1553, -1553,   315, -1553,   497,   592,
   -1553, -1553, -1553, -1553,   876, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553,   315, -1553, -1553, -1553, -1553, -1553, -1553,
     876, -1553, -1553, -1553, -1553, -1553, -1553,   876,   876, -1553,
   -1553, -1553,   850,   872,   883,   876, -1553,   876, -1553,   876,
   -1553,   876, -1553,   876, -1553, -1553, -1553, -1553,   876, -1553,
   -1553,   876, -1553,   876, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553,   876, -1553,   122, -1553, -1553, -1553,   938, -1553, -1553,
   -1553, -1553, -1553,   973,    45, -1553, -1553, -1553, -1553,   858,
      59, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553,   529,   583, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553,  1041, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
    2891, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553,   409, -1553, -1553,   666, -1553, -1553, -1553, -1553, -1553,
   -1553,   670, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553,  3056, -1553, -1553, -1553, -1553,   702,
     189,   710,   912, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553,   700,   693, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553,   626, -1553, -1553, -1553,   -46,   -85,
     261,    47, -1553, -1553, -1553,  4278,   968,  5348,  6481, -1553,
   -1553, -1553, -1553,  1052,  1063,    10,  1040,  1066,  1068,    28,
    1073,  3056,  1081,  5348,  5348,   687,  5348, -1553, -1553,  1034,
    5348,  5348,  1061, -1553,  2577,    66, -1553,   918, -1553, -1553,
     829,  1057,  1058,   688, -1553,   681,   918,  1062,  1084,  1089,
     918,   708, -1553,   394, -1553,  5348, -1553, -1553,  4506,  1079,
     769,   770,  1373,  2823, -1553,  1456,    71, -1553, -1553, -1553,
    1099, -1553, -1553, -1553, -1553,  6694, -1553,   994,  1146,  1177,
     871,   808,   312, -1553, -1553, -1553, -1553, -1553,  1193,   792,
    1195, -1553, -1553, -1553, -1553,  1210, -1553, -1553, -1553, -1553,
     458, -1553, -1553,  1213,  1224, -1553,  1136,  1138, -1553, -1553,
     447, -1553,  1236, -1553, -1553, -1553, -1553,  1239, -1553,  4734,
   -1553,  1239,  5348, -1553, -1553,   686, -1553,  1244, -1553,   122,
   -1553,   931, -1553,   122,    42, -1553,  7096,  7096,  7096,  7096,
    7096,  6481,   106,  5632, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553,  7096, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553,  1247, -1553,  1027,  1243,
    1245,   937,   640,  1263, -1553, -1553, -1553,  5632,  5348,  5348,
    1172,    89,   351,  1247, -1553,   351,  1178, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553,  1242,   962,   963,   967,
   -1553,   970,   975, -1553, -1553, -1553,  1042,  1031,   719,   918,
   -1553,  1200,  1201,  1203,  1204, -1553,  1206,   990, -1553, -1553,
   -1553, -1553, -1553,   876,   876,   876, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553,  1212,   523, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553,    79,  2393, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,  1021, -1553,
    1223,  1225, -1553, -1553,   936, -1553,   951, -1553, -1553, -1553,
   -1553, -1553, -1553,  1226,  1235,  1015,  1237,   109, -1553, -1553,
   -1553,  1003,  1017,  1018,  1241, -1553, -1553,   687, -1553, -1553,
   -1553,  1249, -1553, -1553, -1553, -1553,  5348,  3207,  1718,  1337,
    4962, -1553,   111,   150,  1336,   918,   918,  1250,  6481,  5348,
    5348,  5348, -1553,  1252,  5348,  1295,  5348, -1553, -1553, -1553,
   -1553,  1253, -1553,    24,  1314, -1553,  5348, -1553,   709,  1060,
     164,   507,   969,  1263,   709, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553,  1211,   561, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553,  1246,  1255,  1290,  1268, -1553,  5348,
    1356,  5348,  5348,  1050, -1553, -1553,  6694,  6694,  6694,  6694,
    6694,  1264,  6694,  6694,   132,  5348,  1239,  5348,  1311,  1386,
    1313,  2780,  2780, -1553, -1553, -1553,  5348,   792,  5348,   792,
   -1553, -1553,   802, -1553,  6481, -1553,  6481, -1553, -1553, -1553,
    1027,  1243,  1245, -1553,   709, -1553, -1553, -1553,  1072,  7096,
    7096,  7096,  7096,  7096,  7096,  7096,  1300,  7096,  7096, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553,   743,   138,  1845,  2936,
    1857,   596,   255, -1553, -1553, -1553, -1553, -1553, -1553,  1091,
    1093,  1098, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553,  1395, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553,  1408, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553,  1092,  1100, -1553, -1553, -1553, -1553,
    1015,  -125,  1321, -1553, -1553, -1553, -1553, -1553,   997, -1553,
   -1553, -1553,  1173,   322,  1338,   390,   104,    24,   639, -1553,
    5348,  5348,  1431, -1553,  1343,  1343, -1553,   150, -1553, -1553,
   -1553,  1118,  1336,  5951,   150, -1553, -1553, -1553, -1553, -1553,
    5348, -1553,   152, -1553, -1553,  1179,  5348,  1404, -1553,  6991,
   -1553,  1343,  1343, -1553,   164, -1553,  1207,  1185,   507, -1553,
    2577, -1553,  3816, -1553, -1553, -1553,  1447, -1553,  1361,  1363,
   -1553,  1364, -1553,  5348, -1553, -1553, -1553, -1553, -1553,   994,
    1146,  1177, -1553, -1553, -1553, -1553, -1553, -1553, -1553,  1461,
    5348,  1307,  5348, -1553, -1553, -1553, -1553,   792, -1553,   792,
    1239, -1553,   112,  5951,  5794,    85, -1553, -1553, -1553, -1553,
   -1553,  1027,  1243,  1245, -1553, -1553, -1553, -1553,   969,  1371,
    1434, -1553, -1553, -1553, -1553, -1553,   122,   122,   122,   122,
     122,  1372,   431,   122,   122,   122,   122, -1553, -1553, -1553,
     351, -1553,    35,  1377,  1383, -1553, -1553, -1553,   351,   351,
     351,   351,   351,  6481, -1553,  1343,  1343,  1160,  1020,  1384,
     699,  1182,  1301, -1553, -1553, -1553,   351,   351,   274, -1553,
    6481,  1343,  1166,   699,  1182, -1553, -1553, -1553,   351,   351,
    1387,  1169, -1553, -1553, -1553, -1553,  2494,  3248,  1958,  2506,
     767, -1553, -1553, -1553,  1145,  1396,  1398, -1553, -1553, -1553,
    1399, -1553, -1553, -1553, -1553, -1553,   242,   587,  1913,  1410,
   -1553, -1553, -1553, -1553, -1553,   202, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553,  1179, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553,  5348, -1553, -1553, -1553, -1553,  6481,
    1189,   150, -1553,   826,  1231,  1412, -1553, -1553,  5348,    -2,
      -2,   709,  1263, -1553, -1553, -1553, -1553,  1414,   687, -1553,
   -1553, -1553,   351,   561, -1553, -1553, -1553, -1553,  5348, -1553,
    1443, -1553,  1239,  1239,  6481, -1553,   213,  1205,  1523,   709,
   -1553,  1354,  1437, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553,   122,   122,   122, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553,  1499, -1553, -1553, -1553,
   -1553, -1553, -1553,   833, -1553,   351,   351,   315, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,   904,
   -1553, -1553, -1553, -1553, -1553,   853, -1553, -1553, -1553, -1553,
   -1553,   471,   351,   315,   752,   853, -1553, -1553,  1394,   441,
   -1553, -1553, -1553, -1553, -1553,   374,   860,  1999, -1553, -1553,
    1538,  1015,  1227,   549,   876, -1553, -1553, -1553, -1553, -1553,
    1343,  1446,   549,  1449,   876, -1553, -1553, -1553, -1553, -1553,
    1448,   876, -1553, -1553, -1553, -1553, -1553, -1553,   826,  1231,
   -1553, -1553,  5951, -1553, -1553, -1553, -1553, -1553, -1553,  1287,
    1453, -1553,    24, -1553, -1553,  1320,  1460, -1553, -1553, -1553,
    5348,  1234,  6481, -1553, -1553,  1515,  5794, -1553, -1553,  1397,
     351,  1259,  1265,  1267,  1276,  1280, -1553, -1553, -1553,  1288,
    1291,  1292,  1293,  1476,  6481, -1553, -1553, -1553, -1553,   699,
   -1553,  1182, -1553,  6330, -1553, -1553,  2604, -1553,   124,   351,
      26,   351, -1553, -1553, -1553, -1553,  1484, -1553,  1297, -1553,
   -1553,   351,   351,   351,   351,   351,   351,   351,  1459,   351,
    1287, -1553,  1294,  1502, -1553,    39, -1553,  1519,   210, -1553,
   -1553,  1302,   709, -1553, -1553,  1354, -1553, -1553, -1553, -1553,
   -1553,  1304,  1305,  1306, -1553, -1553, -1553, -1553,  1080, -1553,
   -1553, -1553,  6481,   833,   699,   351,   351,   351,   351,   904,
    1522, -1553, -1553, -1553,   579, -1553, -1553, -1553, -1553, -1553,
      87, -1553, -1553, -1553, -1553,  1527, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553,   549, -1553, -1553, -1553,  1385, -1553, -1553,
   -1553,   826,  1231, -1553, -1553,  1397,   696,  3549,  2154,  2525,
    2334, -1553, -1553, -1553,  1029,  1113,  1010,   893,    13,  1312,
    1394,   833, -1553,   904, -1553, -1553, -1553, -1553, -1553, -1553,
    1531,  1540,    67, -1553,  1637,   102, -1553,   351, -1553,  1287,
   -1553, -1553,   351,   351,   351,   351,   351,  1281,  1954,  2595,
     351,   351,   351,   351, -1553, -1553,   441, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553,  1544,  1527,   351, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553,   351,   351,   351, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553
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
     495,    32,    34,     0,     0,   202,     0,   224,     0,   245,
      18,   335,    19,   335,   335,   335,   335,   335,   335,   335,
       0,   335,   335,   335,   335,    20,   335,    21,   335,   335,
     335,   335,   335,   335,   335,   335,     0,   335,   335,   335,
     335,    22,   335,    23,   335,   335,   366,   335,   366,   366,
     335,   335,   366,   335,   366,     0,   335,   366,   366,     0,
     335,   366,   366,   366,   366,   335,   335,   335,   366,    24,
     335,   366,   366,   335,    25,   335,   335,   335,   335,   366,
       0,   335,    26,   335,    27,     0,     0,     0,   641,   612,
     331,   332,   333,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   808,
     809,   810,   811,   812,   813,   814,   815,   816,   817,   818,
     819,   820,   821,   822,   823,   824,   825,   826,   827,   829,
       0,   831,   830,     0,     0,     0,     0,   828,     0,     0,
      31,   608,   607,   613,   614,   168,   624,   625,   618,   799,
     619,   622,   626,   623,   620,   621,   615,   914,   915,   916,
     917,   918,   919,   920,   921,   922,   923,   924,   925,   926,
     927,   928,   929,   930,   931,   616,  1081,  1082,  1083,  1084,
    1085,  1086,  1087,  1088,   617,     0,   165,   166,     0,    28,
     149,     0,    29,   151,   154,    30,   155,   335,   335,   335,
      42,   728,   704,   706,    16,    15,   343,   345,     0,     0,
       0,   362,   361,   363,     0,   485,     0,   592,   593,   594,
     790,   791,   792,   399,   400,   795,   599,     0,     0,     0,
     415,   423,     0,   447,   468,   475,   476,   554,   560,   577,
       0,     0,   835,     7,    37,   368,   370,   383,   371,   188,
     398,   379,   403,   378,   375,   413,   385,   421,   376,   377,
     386,   469,   387,     0,   388,   397,   483,   391,   553,   392,
     559,   393,   394,   389,   575,   395,     0,   396,   381,     0,
     598,   380,   643,   646,   648,   650,   652,   653,   660,   662,
       0,   661,   605,   402,   799,   384,   390,   382,   615,     8,
       0,     0,    11,   354,     0,     0,     0,    36,   348,     0,
      40,   217,   216,     0,   351,     0,     0,     0,   495,    57,
      59,   202,     0,   224,   245,   335,   335,   335,    65,   728,
     704,   706,     0,     0,    96,    97,     0,    75,    76,     0,
      77,    78,    79,     0,    80,    81,     0,    82,     0,    84,
      85,   708,   709,   707,   335,    87,    88,    92,    93,    89,
      90,    94,    95,     0,   120,    99,   367,   100,   101,   102,
     335,   103,   105,   129,   128,   127,   121,   335,   366,   125,
     124,   126,   708,   709,     0,   335,   108,   335,   106,   335,
     109,   335,   112,   335,   118,   114,   111,   117,   335,   115,
     136,   335,   134,   335,   137,   139,   140,   141,   142,   143,
     146,   335,   145,     0,   933,   934,   935,     0,   632,   633,
     634,   635,   636,   638,     0,   839,   841,   840,   838,     0,
       0,  1079,  1080,  1078,   937,   938,   939,   936,   944,   941,
     942,   943,   940,     0,     0,   946,   947,   948,   949,   950,
     945,   968,   969,   963,   958,   959,   960,   961,   962,   964,
     965,   966,   967,     0,   955,   980,   983,   982,   981,   984,
     985,   986,   979,   988,   989,   990,   991,   987,  1000,  1001,
     993,   994,   995,   997,   996,   998,   999,   992,  1003,  1008,
    1005,  1004,  1009,  1007,  1006,  1010,  1002,  1013,  1016,  1012,
    1014,  1015,  1011,  1019,  1018,  1017,  1021,  1022,  1023,  1020,
    1027,  1028,  1025,  1026,  1024,  1033,  1030,  1031,  1032,  1029,
    1046,  1040,  1043,  1044,  1038,  1039,  1041,  1042,  1045,  1047,
       0,  1034,  1072,  1070,  1071,  1069,  1077,  1074,  1075,  1076,
    1073,  1095,   860,  1094,   866,   861,  1093,  1096,   864,   865,
     867,     0,   862,  1092,     0,  1097,  1100,  1099,  1103,  1102,
    1104,     0,  1101,  1091,  1090,  1089,  1112,  1109,  1107,  1108,
    1110,  1111,  1106,  1115,  1114,  1113,  1119,  1118,  1121,  1117,
    1120,  1116,   800,   803,   804,   805,   807,   806,   828,   798,
     801,   802,   881,   882,   888,   874,   875,   873,   883,   884,
     904,   877,   886,   879,   880,   885,   876,   878,   871,   872,
     902,   901,   903,   887,     0,   868,   889,   845,   844,     0,
     660,     0,     0,  1124,  1123,  1125,  1126,  1127,  1122,   849,
     850,   848,     0,   606,   148,   167,   150,   156,   157,   159,
     158,   161,   162,   160,   163,   725,   725,   725,     0,     0,
     447,     0,   357,   358,   359,     0,     0,     0,     0,   797,
     796,   793,   794,     0,     0,     0,   800,   798,     0,     0,
       0,     0,   868,     0,     0,   456,     0,   445,   446,     0,
       0,     0,     0,     6,     0,     0,   664,     0,   369,   372,
       0,     0,     0,   414,   417,     0,     0,     0,     0,     0,
       0,   422,   424,     0,   467,     0,   531,   763,     0,     0,
     755,   758,   759,   756,   762,   757,     0,   766,   764,   765,
       0,   761,   760,   752,   753,     0,   513,   516,   518,   520,
     522,   523,   528,   535,   532,   533,   534,   536,   538,   474,
     500,   501,   511,   754,   502,   509,   503,   510,   506,   507,
       0,   504,   505,     0,   537,   508,     0,     0,   492,   491,
     484,   487,     0,   572,   573,   574,   552,   557,   570,     0,
     558,   563,     0,   584,   585,   576,   578,   581,   582,     0,
     610,     0,   609,     0,     0,   600,     0,     0,     0,     0,
       0,     0,     0,     0,   784,   785,   786,   787,   788,   789,
     755,   758,   759,   756,   776,   777,   757,   778,   775,   774,
     779,   772,   773,   771,   780,   781,   782,     0,   735,   767,
     737,   768,   657,   658,   749,   736,   730,   729,   741,   743,
     745,   747,   748,   734,   769,   770,   738,     0,     0,     0,
       0,     7,     0,   698,   697,     0,     0,   299,    54,   172,
     189,   203,   225,   246,   364,    56,     0,     0,     0,     0,
      63,     0,     0,   725,   725,   725,     0,     0,   447,     0,
      74,     0,     0,     0,     0,    83,     0,     0,   725,    98,
     104,   123,   122,   335,   335,   335,   130,   107,   110,   113,
     119,   116,   135,   138,   144,   147,     0,     0,   631,   629,
     630,   628,   642,   639,   640,   951,   953,   952,   954,   970,
     971,   972,   973,   957,     0,  1050,  1060,  1051,  1058,  1048,
    1049,  1053,  1054,  1055,  1056,  1057,  1052,  1059,  1036,   863,
       0,     0,   890,   891,     0,   893,     0,   892,   894,   895,
     869,   870,   896,     0,     0,   842,     0,     0,   627,   152,
     164,     0,     0,     0,     0,   264,    43,   456,   289,    50,
     269,     0,    45,   294,   705,    52,     0,   756,   757,   477,
       0,   486,     0,   586,   588,     0,     0,     0,     0,     0,
       0,     0,   411,     0,     0,   896,     0,   416,   444,   454,
     455,     0,   453,     0,   566,   568,     0,   694,     7,     7,
     673,   676,   748,   693,     7,   663,   365,   197,   419,   420,
     418,   437,   436,     0,     0,   435,   431,   426,   427,   428,
     429,   432,   430,   425,     0,     0,     0,     0,   544,     0,
     539,     0,     0,     0,   500,   509,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   546,     0,     0,     0,
       0,     0,     0,   489,   490,   488,     0,     0,     0,   561,
     580,   579,     0,   611,     0,   602,     0,   601,   644,   645,
     647,   649,   651,   654,     7,   404,   406,   659,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   731,
     833,   913,   700,   699,     9,    10,     0,     0,     0,     0,
       0,     0,     0,    73,   172,   189,   203,   225,   246,     0,
       0,     0,    66,    71,    67,    72,   355,   344,   346,   349,
     352,   246,    91,   132,   133,   131,     0,   637,   974,   975,
     977,   976,   978,   956,     0,  1063,  1062,  1061,  1064,  1065,
    1066,  1067,  1068,  1035,     0,     0,   897,   898,   899,   900,
     842,   842,     0,   859,   847,   851,   852,   855,     0,   279,
     284,   274,     0,     0,     0,     0,     0,     0,     0,   479,
       0,     0,   478,   589,     0,     0,   681,   587,   677,   837,
     836,     0,   672,     0,   670,   834,   832,   910,   412,   911,
       0,   909,     0,   449,   448,   450,     0,     0,   667,     0,
     668,     0,     0,   692,   674,   682,   686,     0,   675,   684,
     666,   665,     0,   434,   440,   441,   433,   439,     0,     0,
     473,     0,   545,     0,   549,   551,   512,   514,   515,   517,
     519,   521,   529,   530,   524,   527,   526,   525,   541,   540,
       0,     0,     0,   905,   906,   907,   908,   555,   571,   562,
     564,   583,     0,     0,     0,     0,   407,   783,   733,   739,
     740,   742,   744,   746,   732,   655,   656,   750,   751,     0,
       0,    55,   301,   300,   303,   302,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,   174,   173,
       0,   171,     0,     0,     0,    35,   191,   190,     0,     0,
       0,     0,     0,     0,   213,     0,     0,     0,     0,     0,
       0,     0,     0,    38,   205,   204,     0,     0,     0,   373,
       0,     0,     0,     0,     0,    39,   227,   226,     0,     0,
       0,     0,   251,    41,   248,   247,     0,     0,     0,     0,
       0,   279,   284,   274,     0,     0,     0,  1098,  1105,   846,
       0,   858,   843,   854,   853,   856,     0,     0,     0,     0,
      44,   266,   265,   268,   267,     0,    51,   291,   290,   293,
     292,    46,   271,   270,   273,   272,   450,    53,   296,   295,
     298,   297,   480,   482,     0,   334,   679,   680,   678,     0,
       0,   671,   912,     0,   459,     0,   452,   567,     0,     0,
       0,     7,   695,   696,   690,   691,   683,     0,   456,   685,
     401,   198,     0,     0,   470,   471,   472,   542,     0,   548,
       0,   550,   556,   565,     0,   590,     0,     0,     0,     7,
     405,   496,     0,   356,   263,   347,   188,   350,   202,   224,
     353,   245,   170,     0,     0,     0,   263,   263,   263,   263,
     175,   328,   329,   325,   327,   326,     0,   324,   192,   194,
     193,   196,   195,     0,   200,     0,     0,     0,   244,   243,
     241,   242,   304,   306,   307,   305,   260,   308,   261,     0,
     259,   220,   221,   223,   222,     0,   219,   214,   215,   211,
     374,     0,     0,     0,     0,     0,   240,   239,     0,     0,
      58,    60,    61,    62,    64,     0,     0,     0,    86,   932,
       0,   842,     0,     0,     0,    48,   281,   280,   283,   282,
       0,     0,     0,     0,     0,    49,   286,   285,   288,   287,
       0,     0,    47,   276,   275,   278,   277,   701,     0,   459,
     703,   481,     0,   603,   462,   463,   464,   465,   466,   457,
       0,   443,     0,   569,   669,     0,     0,   199,   438,   543,
       0,     0,     0,   591,   597,     0,   409,   408,   497,   498,
       0,     0,     0,     0,     0,     0,   263,   263,   263,     0,
       0,     0,     0,     0,     0,   207,   209,   210,   212,     0,
     206,     0,   208,     0,   228,   238,     0,   237,     0,     0,
       0,     0,   253,    69,    70,    68,     0,   857,     0,   711,
     710,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     457,   727,     0,     0,   442,     0,   451,     0,     0,   547,
     595,     0,     7,   499,   493,   496,   299,   189,   203,   225,
     246,     0,     0,     0,   264,   289,   269,   294,   323,   201,
     262,   218,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   318,   312,   311,   315,   310,   313,   314,   249,   257,
       0,   254,   258,   250,  1037,     0,   717,   719,   722,   723,
     720,   721,   724,     0,   713,   726,   604,     0,   461,   460,
     687,     0,   459,   596,   410,   498,     0,     0,     0,     0,
       0,   279,   284,   274,     0,     0,     0,     0,     0,     0,
       0,     0,   231,     0,   233,   235,   234,   236,   229,   319,
       0,     0,     7,   252,     0,     0,   714,     0,   458,   457,
     689,   494,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   320,   321,     0,   309,   232,   230,
     317,   316,   256,   255,     0,     0,     0,   712,   688,   187,
     176,   177,   178,   179,     0,     0,     0,   180,   185,   181,
     186,   322,   716,   715,   718,   183,   184,   182
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1553, -1553,    -1, -1038,    23, -1553, -1553,  1625, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553,   -16, -1553,  1258, -1553,   475,  -306, -1138,
   -1553, -1338,  -372, -1129,  -377,   258,    -6,  -371, -1128, -1142,
   -1553,  -376, -1143,  -159, -1553,  -134,     0, -1325,  -642,   -53,
     -54, -1359, -1349, -1347,   -52,   -51,   -39, -1553, -1553,  -116,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,    93,  -679,
   -1149,  1580,   -42,  2313, -1553,  1256, -1553, -1553,    43, -1553,
     324,   479, -1553, -1553,   389,  1114,  -590,  1289, -1553, -1553,
     208,  1586,   864,    77,   -49, -1553, -1553,   357, -1159,  -315,
   -1553, -1553, -1553, -1553, -1553, -1553,   190, -1553, -1553, -1553,
   -1553,   924, -1553, -1553, -1553,   920, -1553, -1553, -1553,   209,
   -1553,  1390, -1186,   248, -1553,  -983, -1552, -1458, -1446, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,   866,  -342,
    1310,    -5,   -66,  -316,   594,   598,   595, -1553,  -707, -1553,
   -1553, -1553, -1553, -1553,  -350, -1553,  1739, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553,  -331,   581, -1553, -1553,
   -1553,   865, -1553,   580, -1084, -1553, -1553,  1428, -1553, -1553,
   -1553, -1553,   862, -1553, -1553,   -60,   -25,  -755,  -334,   600,
     -13, -1553, -1553, -1553,   750,    11, -1553, -1553, -1553, -1553,
   -1553,  -182,  -179, -1553, -1553,   563, -1553,  1533,   -62, -1553,
     645, -1067, -1553, -1241, -1553,   469, -1076, -1553, -1553,   461,
     466, -1553, -1553,  1374,  -600,  1345,  -596,  1344,  -574,  1346,
    1627, -1432, -1553, -1553,   -65, -1553, -1553,  -404,  -561,  1362,
   -1553,  1402,  -320,  -763,  -756,  -734, -1553,  -337,  -746, -1553,
     366,   -81,  -687, -1553, -1223,  -287,   244,  1466, -1553,   151,
   -1553,   247, -1553, -1160, -1553,   542, -1553, -1553, -1553, -1553,
   -1553,   647,  -256,   840,  1149,   843,  1472,  1473, -1553, -1553,
    -456,    33, -1553, -1553, -1553,   887, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,   793, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553, -1553,
   -1553, -1553, -1553, -1553, -1553
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1404,   754,  1405,    45,    46,    47,    72,    85,
      87,   101,   103,   129,   134,   142,   144,   259,   262,   265,
     266,   714,  1019,   260,   210,   375,  1360,  1168,   376,  1169,
    1282,  1533,   379,  1170,   380,  1555,  1556,   383,  1171,  1386,
    1540,   385,  1172,  1671,  1740,  1741,  1548,  1549,  1641,  1233,
    1236,  1428,  1426,  1427,  1235,  1238,  1167,  1550,  1368,  1669,
    1734,  1735,  1736,  1780,  1369,  1370,  1523,  1524,  1503,   211,
    1456,    48,    49,    59,   408,    51,   411,  1506,    65,   415,
    1508,    69,   420,  1511,    60,   405,  1504,   281,   282,   283,
      52,   387,  1246,   437,  1372,   315,   316,  1388,   317,   318,
     319,   320,   321,   322,  1145,  1325,  1326,   323,   324,   325,
     763,   764,   326,   327,   771,   772,  1092,  1086,  1286,  1287,
     328,  1031,  1265,  1466,   329,  1061,  1694,  1621,  1619,   330,
     331,   774,   332,   333,   334,   335,   336,   830,   831,  1345,
     374,  1639,  1704,   796,   797,   798,   799,   800,   801,   802,
    1305,   803,   804,   805,   806,   807,   808,   809,   337,   338,
     836,   339,   340,   840,   341,   342,   837,   838,   343,   344,
     845,   846,   847,   848,  1042,  1043,   345,   346,   347,   348,
     349,   854,   855,   350,   351,   212,   810,   851,   890,   811,
     352,   216,   971,   493,   494,   812,   500,   353,   354,   355,
     356,   357,   358,   892,   893,   894,   359,   360,   361,   755,
     756,  1253,  1254,  1069,  1070,  1247,  1248,  1274,  1278,  1279,
    1275,  1071,  1471,   912,  1434,   718,  1445,   720,  1451,   721,
     424,  1681,  1606,  1795,  1796,  1589,  1599,  1021,  1440,   719,
     362,   913,   914,   898,   899,   900,   901,  1072,   903,   813,
     814,   815,   906,   907,   363,   731,   816,   659,   660,   219,
     365,   817,   498,  1223,   689,   818,  1017,   701,  1227,  1425,
     222,   819,   621,   821,   622,   822,   684,   685,  1010,  1011,
     686,   823,   824,   366,   367,   825,   227,   487,   228,   507,
     229,   512,   230,   520,   231,   534,   983,  1203,   232,   542,
     233,   547,   234,   557,   235,   566,   236,   572,   237,   575,
     238,   579,   239,   584,   240,   589,   241,   601,   998,  1213,
     242,   605,   243,   610,   244,   503,   245,   246,   635,   247,
     623,   248,   625,   249,   627,   250,   632,   251,   642,   252,
     645,   253,   651,   254,   698
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   759,    53,   314,   382,   213,   381,   732,  1073,   841,
     888,  1389,   852,   760,   377,   930,   263,   215,   932,   929,
     888,   888,   931,   902,    44,   690,   702,   213,   726,  1398,
    1268,  1270,   918,   902,   902,  1410,  1280,  1407,   213,   945,
     897,   217,  1034,   947,  1234,   275,  1473,  1408,  1414,  1409,
    1322,  1446,  1561,   369,  1577,   752,   949,   372,    66,    67,
    1419,  1421,  1575,   217,   436,  1576,   436,   436,  1564,  1323,
     436,   753,   436,  1074,   217,   436,   436,   820,  1076,   436,
     436,   436,   436,  1498,   928,   853,   436,  1087,  1103,   436,
     436,  1091,  1499,   753,  1792,  1140,  1457,   436,   916,    55,
      56,    57,    58,  1141,  1047,     3,  1324,  1146,     4,  1825,
       5,  1521,  1522,   832,   150,   151,   152,  1494,  1026,   391,
     392,   393,  1474,  1475,  1032,  1263,  1142,  1739,  1052,   849,
       6,     7,     8,     9,   849,   414,   416,   417,  1755,     3,
    1758,   276,     4,   277,     5,   433,  1730,  1035,   150,   151,
     152,  1691,   373,   442,   443,   849,   968,   378,  1029,   449,
    1685,   384,  1690,  1389,     6,     7,     8,     9,  1739,  1138,
    1139,  1458,  1463,  1222,   733,   916,  1420,  -702,  1027,   213,
     478,   479,   973,   213,   482,   439,   441,   543,    54,   444,
    1198,   446,   278,   612,   450,   451,   255,   861,   458,   460,
     462,   464,  1024,   364,  -447,   469,  1199,   544,   472,   474,
     734,  1200,  1201,   614,   364,   217,   480,   615,  1632,   217,
     545,    63,  1608,    55,  1731,  1732,  1535,  1536,  1012,  1560,
    1761,   612,   261,   730,   730,    71,  1028,  1244,    86,   704,
    1245,   863,  1562,     3,   102,   706,     4,  1828,     5,  1389,
    -702,  1271,   725,  1464,  1272,   615,     3,   969,   970,     4,
    1034,     5,   495,   496,   143,  1225,   264,  1398,     6,     7,
       8,     9,   370,  1264,   218,  1025,  1202,   220,     4,   905,
       5,     6,     7,     8,     9,  1055,   850,  1243,  1759,   905,
     905,   213,   612,  1053,   402,  1400,   218,  1401,   895,   220,
     618,   619,   703,  1609,  1800,   371,   974,   218,   895,   895,
     220,  1762,  1022,  1023,   941,  1799,   615,   833,   834,   835,
    1113,  1797,  -169,     3,   209,  1723,     4,   217,     5,   661,
     382,  1048,   381,  1582,   546,   889,  1182,  1560,   925,   209,
    -188,  1729,  1184,  1382,   481,   889,   889,   267,     6,     7,
       8,     9,   209,   940,   382,     4,   381,     5,   300,  1306,
      55,   209,   213,  1136,  1114,  1185,  1249,  1250,  1033,   747,
     748,   382,  1583,   381,   302,     3,  1183,   213,     4,   303,
       5,   499,   917,   620,  1781,  1458,   729,   729,  1075,  1331,
     735,     3,  1612,   209,     4,  1498,     5,  1332,   217,  1783,
       6,     7,     8,     9,  1067,  1303,   436,  1500,   757,  1793,
    1631,  1163,  1702,   217,  1809,   839,     6,     7,     8,     9,
    1333,  1677,  1807,  1226,  1826,  1808,  1441,  1144,   270,   271,
     272,   273,   209,  1624,  1495,   624,  1696,   209,   497,   279,
     280,  1683,   757,  1733,  1382,   256,   257,   258,   218,   661,
     209,   220,   218,   313,   757,   220,   692,   395,   209,   300,
    1341,  1636,   388,  1329,  1330,  1582,   942,   364,   757,   633,
     398,   399,   400,   401,  1584,   302,  1663,   404,  1116,  1654,
     303,   256,   257,   258,   826,   827,   425,   427,   429,   431,
     951,   943,   643,   434,   634,  1626,   373,   421,   268,   276,
     269,  1402,   277,   626,  1583,  1382,   378,   751,   452,   456,
     944,   384,    55,   888,   465,   466,   467,   644,  1513,   470,
     300,   705,   475,  1472,   964,   952,   747,   748,   852,  1179,
    1180,  1181,  1094,   602,  1073,  1633,   302,    55,   364,   440,
    1117,   303,  1118,  1147,  1192,  1095,   757,   612,  1701,  1044,
    1148,   614,   946,   364,    18,    19,    55,   888,   394,  1034,
     218,  1096,   274,   220,  1585,   687,     4,  1770,     5,  1767,
    1024,   615,   221,   861,   419,   688,   965,  1403,  1073,  1768,
     722,  1769,  1030,   573,  1173,   603,   604,  1159,     3,   862,
     130,     4,   445,     5,   221,   131,   132,     3,    55,   574,
       4,  1790,     5,    34,  1791,   221,  1584,   727,   396,  1389,
     397,   133,    35,     6,     7,     8,     9,   863,    36,   833,
     834,   835,     6,     7,     8,     9,   757,  1398,   828,   829,
     214,   218,   488,   489,   220,  1390,   313,   975,   618,   619,
       3,   209,    37,     4,  1430,     5,   218,  1155,   422,   220,
     423,   976,   214,  1027,   723,  1119,   715,   716,   717,   453,
    1156,   423,  1157,   214,  1764,     6,     7,     8,     9,  1514,
     746,  1515,   724,   905,  1590,  1097,   454,   223,   757,  1143,
     743,  1591,   580,  1391,   750,  1392,   581,  1378,   747,   748,
    1379,   977,  1068,   744,   757,   585,  1673,     3,  1020,   223,
       4,  1284,     5,   213,   628,   978,  1285,  1393,   852,   745,
     223,  1679,  1436,   753,  1105,  1120,  1680,  1592,   582,   583,
     757,   620,     6,     7,     8,     9,   904,   586,   587,   889,
     588,   490,   491,   916,   773,   492,   904,   904,   853,   217,
     150,   151,   152,   629,   630,   631,   221,     4,   576,     5,
     221,  1593,   858,  1276,  1822,  1394,  1081,  1666,   577,   578,
    1659,  1228,  1670,  1516,  1517,  1518,  1519,   209,     3,  1277,
    1104,     4,   859,     5,   860,   905,   905,   905,   905,   905,
     852,  1339,   905,   606,   933,   934,   935,   287,   288,  1082,
    1297,  1298,   289,     6,     7,     8,     9,  1304,  1320,   908,
    1542,   895,   850,  1083,   214,   909,   905,  1400,   214,  1401,
     699,   700,  1328,   948,   636,   607,   608,   278,  1334,  1594,
    1336,  1338,   447,   448,  1543,  1544,   905,   646,  1111,   637,
    1112,   889,   889,   889,   889,   889,   213,     4,   889,     5,
     647,  1654,   919,   609,   956,   895,   920,   648,  1084,   921,
     638,   223,   484,   485,   486,   223,   639,     4,   221,     5,
    1661,     3,   889,  -702,     4,   649,     5,   765,   922,  1252,
     224,   650,   217,   225,  1649,  1650,  1651,  1652,   504,   505,
     506,   508,   889,   509,   510,   511,     6,     7,     8,     9,
    1073,   757,   224,   953,     3,   225,  1085,     4,   923,     5,
     757,   501,   502,   224,   640,   641,   225,  1545,     4,  1595,
       5,  1164,  1659,  -245,  1165,   954,   214,   226,  1395,     6,
       7,     8,     9,  1646,  1647,  1648,   955,  1546,  1547,   221,
    1067,   256,   257,   258,    18,    19,   761,   762,  1460,   368,
     856,   857,  1133,   757,   221,   966,  1135,  1590,   567,   135,
     368,   136,  1059,  1060,  1591,  1044,   137,  1252,   138,   972,
     891,  1447,   139,   223,   568,   766,   767,   768,   769,   770,
     891,   891,   218,   569,  1067,   220,   842,   843,   844,   570,
     571,   967,   850,    34,   747,   748,  1492,   214,  1493,  1156,
    1592,  1157,    35,  1000,   150,   151,   152,  1001,    36,  1013,
     757,   140,   214,   141,  1711,  1712,  1713,  1014,  1497,  1106,
    1107,     3,  1015,  1402,     4,  1016,     5,  1018,  1802,   150,
     151,   152,    37,   213,  1593,  1105,  1105,  1105,  1105,  1105,
       3,  1105,  1105,     4,   223,     5,     6,     7,     8,     9,
    1314,  1314,  1150,  1151,   224,  1216,  1217,   225,   224,   223,
    1040,   225,  1307,   693,   850,     6,     7,     8,     9,   217,
    1218,  1219,   694,   695,   753,  1269,   696,   697,   905,   905,
     905,   905,   905,   905,   905,  1045,   905,   905,   833,   834,
     835,  1104,  1104,  1104,  1104,  1104,  1046,  1104,  1104,  1574,
    1049,   226,  1594,   843,   844,   226,  1313,  1313,  1034,  1814,
    1614,  1615,  1616,  1617,  1618,   218,  1423,  1424,   220,   213,
    -447,   213,  1538,  1539,     3,  1205,  1050,     4,  1051,     5,
     904,  1778,  1779,  1054,   889,   889,   889,   889,   889,   889,
     889,  1056,   889,   889,  1063,  1645,  1643,   457,  1644,     6,
       7,     8,     9,  1066,   213,   217,     3,   217,  1206,     4,
    1077,     5,    18,    19,  1315,  1316,   224,  1078,  1079,   225,
    1658,  1101,  1088,  1108,   757,  1340,  1342,  1358,  1366,  1384,
    1396,     6,     7,     8,     9,   979,   980,   981,   982,   758,
     217,  1102,  1674,   732,  1089,  1400,  1665,  1401,   905,  1090,
    1343,  1359,  1367,  1385,  1397,  1109,  1110,   757,  1115,   905,
    1642,    34,  -905,   368,  1207,  1208,  1209,  1210,  1211,  1212,
      35,   426,   428,   430,   432,  1813,    36,  -906,  1068,   535,
    1121,   536,   904,   904,   904,   904,   904,   224,   213,   904,
     225,  1122,  1431,  1482,  1437,  1442,  1123,  1448,  1124,   537,
      37,  1126,   224,   905,   889,   225,  1127,   538,   539,   540,
     541,  1132,  1134,   904,  1149,   889,  1432,   213,  1438,  1443,
    1152,  1449,  1154,  1153,   217,  1551,  1552,  1553,    62,  1554,
     221,  1158,  1162,   904,   368,   747,   748,  1024,  1166,   916,
    1252,  1481,     3,  1174,  1175,     4,  1067,     5,  1176,   368,
    1024,  1177,   218,   217,  1027,   220,  1178,  1692,   213,   889,
    1186,  1187,  1525,  1188,  1189,   611,  1190,     6,     7,     8,
       9,  1191,  1196,  1222,   757,  1044,   612,   707,   613,   708,
     364,   709,   710,  1214,  1229,  1215,  1220,   386,   214,   711,
     712,   390,  1812,   757,   217,  1221,   614,  1224,  1230,  1231,
     615,  1232,  1240,   616,   861,  1260,   410,   386,   213,  1237,
    1251,  1810,  1258,  1262,   891,  1266,  1283,  1288,  1290,  1520,
    1534,  1293,   713,   438,  1302,   213,  1289,  1528,  1529,  1530,
    1531,  1532,  1582,   459,  1296,   223,  1027,  1534,   218,  1291,
     218,   220,   213,   220,   217,  1557,  1558,  1559,    18,    19,
     617,  1402,   477,  1310,  1311,  1312,  1327,  1566,  1567,   483,
    1335,   217,  1415,   221,   364,  1358,  1366,  1384,  1396,   730,
     730,  1583,  1411,   218,  1412,  1416,   220,   757,   217,  1413,
    1417,  1422,  1429,   618,   619,  1586,  1596,  1603,  1418,  1359,
    1367,  1385,  1397,   364,   213,  1811,  1454,    34,  1435,  1459,
    1505,  1507,  1507,  1510,  1455,  1468,    35,  1465,  1478,  1587,
    1597,  1604,    36,  1044,  1483,  1477,   891,   891,   891,   891,
     891,   214,  1484,   891,  1485,  1486,  1488,  1578,  1490,   213,
     217,  1501,  1502,  1512,   364,   382,    37,   381,  1526,  1527,
    1537,  1627,   513,   514,  1541,   739,  1563,   891,  1568,  1569,
     515,   516,   517,   518,   519,  1620,  1579,   218,  1580,  1581,
     220,   382,   558,   381,   559,   217,   620,   891,   223,  1672,
    1607,  1613,  1622,  1584,  1625,   904,   904,   904,   904,   904,
     904,   904,   560,   904,   904,  1630,   218,  1634,  1635,   220,
     561,   562,  1655,   563,  1656,  1657,  1638,  1640,  -861,  1653,
    -861,  1668,  1682,   564,   565,  1676,  1684,  1678,  1660,  1686,
    1688,  1693,  1687,  1695,  1662,   905,  1700,   461,   364,  1689,
    1698,  1664,   729,   729,  1667,   548,   549,   218,   224,  1697,
     220,   225,    18,    19,  1586,  1596,  1603,  1718,  1703,   550,
    1706,   551,   552,   553,  1744,   757,  1707,   213,  1708,  1753,
     221,   290,   291,   292,  1469,  1470,   295,  1709,  1587,  1597,
    1604,  1710,  1757,  1834,   554,   555,   556,   213,  1737,  1714,
    1742,   889,  1715,  1716,  1717,   226,  1756,   218,  1745,  1760,
     220,    34,  1789,   217,  1763,  1771,  1772,  1773,  1794,   213,
      35,  1820,  1816,  1798,   218,   904,    36,   220,   213,  1705,
    1821,  1719,  1824,   217,  1842,    70,   904,   927,   214,  1406,
    1534,   218,  1565,  -861,   220,  1721,   463,  1841,  1823,  1720,
      37,  1774,  1776,  1775,  1817,   217,  1777,  1766,  1738,   406,
    1743,    18,    19,  1509,   217,   924,   221,   412,   221,  1496,
    1746,  1747,  1748,  1749,  1750,  1751,  1752,  1080,  1754,  1637,
     904,  1093,  1628,   749,  1610,   223,  1125,   213,   926,  1801,
    1765,   224,  1299,   218,   225,  1301,   220,  1300,  1318,  1534,
    1131,   221,  1321,  -861,   728,   468,  1137,  1197,  1815,  1281,
      34,  1337,  1782,  1461,  1784,  1785,  1786,  1787,  1788,    35,
      18,    19,  1742,   217,   214,    36,   214,   691,   218,  1479,
    1476,   220,   213,   936,   938,   915,   455,   939,   226,   891,
     891,   891,   891,   891,   891,   891,  1672,   891,   891,    37,
    1843,   937,   896,   364,   737,  1342,  1366,  1384,  1396,   214,
     999,   741,   742,  1431,  1437,  1442,  1448,  1204,   217,    34,
    1818,   223,  1819,   223,     0,     0,     0,     0,    35,  1343,
    1367,  1385,  1397,     0,    36,   221,  1827,  1432,  1438,  1443,
    1449,  1829,  1830,  1831,  1832,  1833,  1586,  1596,  1603,  1837,
    1838,  1839,  1840,     0,     0,     0,   223,     0,    37,     0,
       0,     0,     0,     0,   221,  1844,     0,   548,   549,     0,
    1587,  1597,  1604,  1845,  1846,  1847,     0,     0,     0,     0,
       0,   550,     0,   551,   552,   553,     3,     0,     0,     4,
       0,     5,     0,   214,     0,     0,   218,     0,     3,   220,
       0,     4,     0,     5,     0,   221,   554,   555,   556,   891,
       0,     6,     7,     8,     9,     0,   218,     0,     0,   220,
     891,  1346,   214,     6,     7,     8,     9,     0,   224,     0,
    1347,   225,     0,     0,     0,  1348,  1373,  1349,   218,  1350,
     223,   220,     0,     0,     0,     0,     0,   218,     0,     0,
     220,     0,     0,     0,     3,   221,     0,     4,   364,     5,
       0,     0,     0,   214,   891,     0,     0,     0,     0,   223,
       0,     0,   221,     0,  1273,   226,     0,     0,     0,     6,
       7,     8,     9,  1374,  1375,  1376,  1377,     0,  1378,   221,
       0,  1379,     0,     0,     0,     3,     0,     0,     4,     3,
       5,     0,     4,     0,     5,     0,   218,     0,  1380,   220,
     223,     0,     0,   214,   224,     0,   224,   225,   471,   225,
       6,     7,     8,     9,     6,     7,     8,     9,     0,     0,
     214,     0,     0,    18,    19,     0,     0,  1373,     0,     0,
       3,   221,   904,     4,  1351,     5,     0,   214,     0,   224,
       0,   218,   225,     0,   220,     0,  1381,     0,     0,     0,
     223,   226,     0,   226,  1600,     6,     7,     8,     9,     0,
       0,  1344,  1361,  1371,  1387,  1399,   221,   223,     0,     0,
       0,  1590,    34,     0,  1374,  1375,  1376,  1377,  1591,  1378,
       0,    35,  1379,     0,   223,     0,   368,    36,     0,   214,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1380,
       0,     0,     0,     0,     0,     0,  1352,     0,     0,     0,
       0,    37,     0,     0,  1592,     0,     0,     0,  1382,   473,
       0,  1353,     0,   224,   214,     0,   225,  1433,     0,  1439,
    1444,     0,  1450,   300,    18,    19,   223,  1354,     0,     0,
    1600,     0,  1355,     0,  1356,     0,     0,  1381,  1593,   302,
       0,    88,   224,     0,   303,   225,     0,     0,    89,     0,
      90,     0,    91,     0,     0,    92,    93,    94,  1273,    95,
     368,   223,     0,     0,     0,  1601,     0,     0,     0,   757,
       0,     0,     0,    34,   221,     3,     0,     0,     4,     0,
       5,   757,    35,   224,     0,     0,   225,  1357,    36,   368,
       0,     0,     0,     0,   221,     0,     0,     0,     0,  1383,
       6,     7,     8,     9,     0,     0,  1594,     0,     0,  1382,
       0,     0,    37,  1373,     0,     0,   221,     0,     0,     0,
       0,     0,     0,     0,   300,   221,     0,     0,     0,     0,
     368,     0,   214,   224,     0,     0,   225,   757,     0,     0,
     302,     0,     0,     0,     0,   303,     0,     0,     0,     0,
     224,  1601,   214,   225,     0,  1602,   891,    73,     0,     0,
    1374,  1375,  1376,  1377,    74,  1378,    75,   224,  1379,     0,
     225,    76,    77,    78,   214,    79,     0,     0,   757,   223,
     226,     0,   757,   214,   221,  1380,     0,     0,     0,     0,
    1361,  1371,  1387,  1399,     0,     0,  1835,   226,     0,   223,
    1572,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1588,  1598,  1605,     0,   368,     0,     0,     0,     0,   224,
       0,   223,   225,   757,     0,     0,     0,     0,     0,   221,
     223,     0,     0,  1381,    50,     0,    96,     0,     0,     0,
       0,  1675,   214,     0,    61,    50,    50,    64,    64,    64,
      68,    97,     0,    50,   224,     3,     0,   225,     4,     0,
       5,     0,     0,     0,     0,     0,   226,    98,     0,     0,
       0,     0,    99,     0,   100,     0,     0,     0,     0,     0,
       6,     7,     8,     9,     0,     0,     0,   214,     0,   223,
       0,     0,     0,     0,  1400,     0,  1401,     0,     0,     0,
       0,   226,     0,     0,    50,  1382,     0,   389,    50,    64,
      64,    64,    68,     0,     0,     0,     0,     0,     0,    50,
     300,   403,   407,   409,    50,   413,    64,    64,   418,     0,
     403,   403,   403,   403,   223,    64,   302,     0,   435,     0,
      50,   303,     0,    64,    64,     0,    68,     0,     0,    64,
     985,     0,    80,     0,     0,     0,     0,     0,     0,  1588,
    1598,  1605,     0,     0,     0,     0,     0,    81,   476,    50,
      64,    64,   224,     0,    64,   225,    50,     0,   757,     0,
       0,     0,     0,    82,  1039,     0,  1041,     0,    83,     0,
      84,     0,   224,     0,     0,   225,  1804,     0,     0,     0,
       0,     0,  1057,  1058,     0,  1062,     0,     0,     0,  1064,
    1065,     0,     0,   986,   224,     3,     0,   225,     4,   368,
       5,     0,     0,   224,     0,     0,   225,     3,     0,     0,
       4,     0,     5,     0,  1098,     0,     0,  1100,     0,   226,
       6,     7,     8,     9,     0,     0,     3,     0,     0,     4,
    1346,     5,     6,     7,     8,     9,     0,     0,     0,  1347,
       0,   226,     0,     0,  1348,  1390,  1349,     0,  1350,     0,
     226,     6,     7,     8,     9,     0,     0,     0,     0,     0,
       0,     0,   224,   987,  1390,   225,   988,   989,   990,   991,
     992,   993,   994,   995,   996,   997,     0,     0,  1129,     0,
    1402,  1130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1391,     0,  1392,     3,  1378,   776,     4,
    1379,     5,     0,     0,     0,     0,     0,   224,     0,   226,
     225,     0,  1391,     0,  1392,     0,  1378,  1393,     0,  1379,
       0,     6,     7,     8,     9,     0,     0,     0,     0,     0,
    1344,  1371,  1387,  1399,     0,     0,  1393,     0,  1433,  1439,
    1444,  1450,     0,     0,     0,   777,     0,  1160,  1161,     0,
       0,     0,     0,  1351,   368,     0,  1806,     0,     0,     0,
       0,     0,     0,     0,     0,  1394,     0,     0,     0,     0,
       0,  1588,  1598,  1605,     0,     0,     0,   149,   150,   151,
     152,     0,     0,     0,  1394,   870,     0,     0,  1724,   871,
       0,     0,     0,   872,     0,     0,     0,     0,     0,   873,
       0,     0,     0,   784,     0,  1542,  1600,     0,     0,     0,
       0,     0,     0,     0,     0,   874,     0,     0,     0,     0,
     875,     0,     0,   876,     0,  1352,     0,     0,   877,  1543,
    1544,   878,     0,     0,   879,   880,     0,     0,     0,   881,
    1353,     0,   882,     0,   883,     0,     0,     0,     0,     0,
       0,     0,     0,   950,     0,     0,  1354,     0,     0,     0,
      64,  1355,     0,  1356,     0,     0,   884,   885,     0,     0,
     957,     0,   958,     0,   959,  1239,   960,     0,     0,  1242,
       0,   961,     0,     0,   962,     0,   963,     0,  1255,  1256,
    1257,     0,     0,  1259,    64,  1261,     0,     0,   757,     0,
       0,     0,     0,     0,     0,  1267,     0,     0,     0,     0,
     757,     0,  1545,     0,     0,     0,  1570,     0,   787,     0,
       0,   788,   789,     0,     0,     0,     0,  1601,  1573,   757,
       0,     0,  1546,  1547,     0,     0,     0,     0,  1292,     0,
    1294,  1295,     0,     0,     0,     0,     0,  1805,   777,     0,
    1725,     0,     0,     0,  1308,     0,  1309,     0,     0,   791,
     792,     0,   886,     0,     0,  1317,  1726,  1319,     0,     0,
       0,  1727,     0,  1728,     0,     0,     0,     0,     0,     0,
       0,   150,   151,   152,     0,     0,   793,   794,   870,     0,
       0,     0,   871,     0,     0,     0,   872,     0,   313,   757,
     887,     0,   873,   209,     0,  -860,   784,  -860,     0,     0,
       0,     0,     0,     0,   984,     0,     0,  1836,     0,     0,
       0,     0,     0,     0,     0,     0,   876,     0,   985,     0,
       0,     0,   521,   522,     0,     0,   523,     3,     0,     0,
       4,     0,     5,     0,     0,     0,   524,   525,   526,   527,
     528,   529,   530,   531,   532,     0,     0,     0,     0,   145,
       0,     0,     6,     7,     8,     9,   146,   147,     0,     0,
     284,   148,   285,     0,     0,     0,     0,     0,     0,  1452,
    1453,     0,     0,     0,     0,     0,   286,     0,     0,     0,
       0,   986,     0,     0,     0,   533,   287,   288,     0,  1462,
       0,   289,     0,     0,     0,  1467,     0,     0,     0,     0,
       0,     0,   290,   291,   292,   293,   294,   295,     0,     0,
    -860,   787,     0,     0,   788,   789,     0,  1362,     0,     0,
       0,   296,  1487,   297,     0,     0,   149,   150,   151,   152,
       0,     0,   153,     0,   154,     0,     0,  1363,   155,  1489,
       0,  1491,   156,     0,     0,     0,     0,     0,   157,     0,
       0,   987,   791,   792,   988,   989,   990,   991,   992,   993,
     994,   995,   996,   997,   158,     0,   590,     0,     0,   159,
    -860,     0,   160,     0,     0,   591,     0,   161,     0,     0,
     162,     0,     0,   163,   164,  1364,     0,     0,   165,     0,
     592,   166,     0,   167,   593,     0,   209,     0,   594,   595,
       0,     0,     0,   596,   597,   598,   599,   600,     0,     0,
       0,     0,     0,     0,     0,   168,   169,     0,   170,   171,
     172,   173,     0,     0,     0,     0,     0,   174,   175,     0,
       0,   176,   177,   298,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,  1002,  1003,   299,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1004,     0,
       0,     0,   300,     0,     0,     0,  1005,     0,     0,     0,
       0,     0,   301,  1611,     0,     0,     0,     0,   302,     0,
       0,     0,  1006,   303,     0,     0,     0,  1623,     0,     0,
       0,     0,   201,   202,     0,   304,     0,     0,   305,   306,
     307,   308,     0,     0,     0,   309,     0,  1629,     0,   310,
     311,   203,     0,     0,     0,   204,   205,     0,     0,     0,
     757,     0,     0,     0,   312,     0,     0,   206,   207,     3,
       0,     0,     4,     0,     5,     0,     0,   313,  1365,   208,
       0,     0,   209,     0,     0,     0,  1193,  1194,  1195,     0,
       0,   145,     0,     0,     6,     7,     8,     9,   146,   147,
       0,     0,   284,   148,   285,     0,     0,     0,  1007,  1008,
    1009,   670,     0,     0,     0,     0,     0,     0,   286,     0,
       0,     0,     0,     0,   680,   681,   682,     0,   287,   288,
       0,     0,     0,   289,     0,     0,   521,   522,     0,     0,
     523,     0,     0,     0,   290,   291,   292,   293,   294,   295,
     524,   525,   526,   527,   528,   529,   530,   531,   532,  1362,
       0,     0,     0,   296,     0,   297,     0,     0,   149,   150,
     151,   152,     0,     0,   153,     0,   154,     0,     0,  1363,
     155,     0,     0,     0,   156,     0,     0,     0,     0,  1699,
     157,     0,     0,     0,     0,     0,     0,     0,     0,   533,
       0,     0,     0,     0,     0,     0,   158,     0,     0,     0,
       0,   159,     0,     0,   160,     0,     0,     0,     0,   161,
       0,     0,   162,     0,     0,   163,   164,  1364,     0,     0,
     165,     0,    10,   166,     0,   167,     0,     0,     0,    11,
       0,    12,     0,    13,     0,     0,    14,    15,    16,     0,
      17,     0,     0,     0,    18,    19,     0,   168,   169,     0,
     170,   171,   172,   173,     0,     0,     0,     0,     0,   174,
     175,     0,     0,   176,   177,   298,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,     0,     0,   299,
       0,     0,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,    35,     0,   300,     0,     0,     0,    36,     0,
       0,     0,     0,     0,   301,     0,     0,     0,     0,     0,
     302,     0,     0,     0,     0,   303,     0,     0,     0,     0,
       0,     0,    37,     0,   201,   202,     0,   304,     0,     0,
     305,   306,   307,   308,     0,     0,     0,   309,     0,     0,
       0,   310,   311,   203,     0,     0,     0,   204,   205,     0,
       3,     0,   757,     4,     0,     5,   312,     0,     0,   206,
     207,     0,     0,     0,     0,     0,     0,     0,     0,   313,
    1571,   208,   145,     0,   209,     6,     7,     8,     9,   146,
     147,     0,     0,   284,   148,   285,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   286,
       0,     0,     0,     0,     0,     0,     0,    38,     0,   287,
     288,     0,     0,     0,   289,     0,     0,     0,     0,     0,
       0,     0,    39,     0,     0,   290,   291,   292,   293,   294,
     295,     0,     0,     0,     0,     0,     0,     0,    40,     0,
    1362,     0,     0,    41,   296,    42,   297,     0,     0,   149,
     150,   151,   152,     0,     0,   153,     0,   154,     0,     0,
    1363,   155,     0,     0,     0,   156,     0,     0,     0,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,     0,     0,   160,     0,     0,     0,     0,
     161,     0,     0,   162,     0,     0,   163,   164,  1364,     0,
       0,   165,     0,     0,   166,     0,   167,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   168,   169,
       0,   170,   171,   172,   173,     0,     0,     0,     0,     0,
     174,   175,     0,     0,   176,   177,   298,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,     0,     0,
     299,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   300,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   301,     0,     0,     0,     0,
       0,   302,     0,     0,     0,     0,   303,     0,     0,     0,
       4,     0,     5,     0,     0,   201,   202,     0,   304,     0,
       0,   305,   306,   307,   308,     0,     0,     0,   309,   145,
       0,     0,   310,   311,   203,     0,   146,   147,   204,   205,
     284,   148,   285,   757,     0,     0,     0,   312,     0,     0,
     206,   207,     0,     0,     0,     0,   286,     0,     0,     0,
     313,  1803,   208,     0,     0,   209,   287,   288,     0,     0,
       0,   289,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   290,   291,   292,   293,   294,   295,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   296,     0,   297,     0,     0,   149,   150,   151,   152,
       0,     0,   153,     0,   154,     0,     0,     0,   155,     0,
       0,     0,   156,     0,     0,     0,     0,     0,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   158,     0,     0,     0,     0,   159,
       0,     0,   160,     0,     0,     0,     0,   161,     0,     0,
     162,     0,     0,   163,   164,     0,     0,     0,   165,     0,
       0,   166,     0,   167,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   168,   169,     0,   170,   171,
     172,   173,     0,     0,     0,     0,     0,   174,   175,     0,
       0,   176,   177,   298,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,     0,     0,   299,     0,     0,
       0,     0,     0,     0,     0,   775,     0,     0,     0,     0,
       0,     0,   300,     0,     0,     0,     0,     0,     0,     0,
       0,   776,   301,   145,     0,     0,     0,     0,   302,     0,
       0,   147,     0,   303,     0,   148,     0,     0,     0,     0,
       0,     0,   201,   202,     0,   304,     0,     0,   305,   306,
     307,   308,     0,     0,     0,   309,     0,     0,     0,   310,
     311,   203,     0,     0,     0,   204,   205,     0,   777,     0,
       0,     0,     0,     0,   312,     0,     0,   206,   207,     0,
       0,     0,   778,     0,   779,     0,     0,   313,  1480,   208,
       0,     0,   209,     0,     0,     0,     0,     0,     0,     0,
     149,   150,   151,   152,     0,     0,   153,     0,   780,     0,
       0,     0,   781,     0,     0,     0,   782,     0,     0,     0,
       0,     0,   783,     0,     0,     0,   784,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,   159,     0,     0,   785,     0,     0,     0,
       0,   161,     0,     0,   162,     0,     0,   163,   164,     0,
       0,     0,   165,     0,     0,   166,     0,   167,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   168,
     169,     0,   786,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,   200,     0,  1036,     0,     0,     0,     0,     0,     0,
       0,   787,     0,     0,   788,   789,     0,     0,     0,   776,
       0,   145,     0,     0,     0,     0,     0,   790,     0,   147,
       0,     0,     0,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   201,   202,     0,     0,
       0,     0,   791,   792,     0,     0,     0,     0,     0,   652,
       0,     0,     0,     0,     0,   203,   777,     0,     0,   204,
     205,     0,     0,     0,     0,     0,     0,     0,     0,   793,
     794,     0,   658,     0,     0,   653,     0,     0,   654,     0,
       0,     0,     0,   795,     0,     0,   209,     0,   149,   150,
     151,   152,     0,     0,   153,   655,   780,     0,     0,     0,
     781,     0,     0,     0,   782,     0,     0,     0,     0,     0,
    1037,     0,     0,     0,   784,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   158,     0,     0,     0,
       0,   159,     0,     0,  1038,     0,     0,     0,     0,   161,
       0,     0,   162,     0,     0,   163,   164,     0,     0,     0,
     165,     0,     0,   166,     0,   167,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   168,   169,     0,
     786,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   656,     0,   200,
       0,  1099,     0,     0,   201,   202,     0,     0,     0,   787,
       0,     0,   788,   789,   657,     0,     0,   776,     0,   145,
       0,     0,     0,     0,     0,     0,     0,   147,     0,     0,
       0,   148,     0,     0,     0,     0,     0,     0,     0,     0,
     658,     0,     0,     0,   201,   202,     0,     0,     0,     0,
     791,   792,     0,     0,     0,     0,     0,   736,     0,     0,
       0,     0,     0,   203,   777,     0,     0,   204,   205,     0,
       0,     0,     0,     0,     0,     0,     0,   793,   794,     0,
     658,     0,     0,   653,     0,     0,   654,     0,     0,     0,
       0,   795,     0,     0,   209,     0,   149,   150,   151,   152,
       0,     0,   153,   655,   780,     0,     0,     0,   781,     0,
       0,     0,   782,     0,     0,     0,     0,     0,  1037,     0,
       0,     0,   784,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   158,     0,     0,     0,     0,   159,
       0,     0,  1038,     0,     0,     0,     0,   161,     0,     0,
     162,     0,     0,   163,   164,     0,     0,     0,   165,     0,
       0,   166,     0,   167,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   168,   169,     0,   786,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   656,     0,   200,     0,  1128,
       0,     0,   201,   202,     0,     0,     0,   787,     0,     0,
     788,   789,   657,     0,     0,   776,     0,   145,     0,     0,
       0,     0,     0,     0,     0,   147,     0,     0,     0,   148,
       0,     0,     0,     0,     0,     0,     0,     0,   658,     0,
       0,     0,   201,   202,     0,     0,     0,     0,   791,   792,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,   777,     0,     0,   204,   205,     0,     0,     0,
       0,     0,     0,     0,     0,   793,   794,     0,   658,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   795,
       0,     0,   209,     0,   149,   150,   151,   152,     0,     0,
     153,     0,   780,     0,     0,     0,   781,     0,     0,     0,
     782,     0,     0,     0,     0,     0,  1037,     0,     0,     0,
     784,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,   159,     0,     0,
    1038,     0,     0,     0,     0,   161,     0,     0,   162,     0,
       0,   163,   164,     0,     0,     0,   165,     0,     0,   166,
       0,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   168,   169,     0,   786,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,     0,     0,   200,     0,  1241,     0,     0,
       0,     0,     0,     0,     0,   787,     0,     0,   788,   789,
       0,     0,     0,   776,     0,   145,     0,     0,     0,     0,
       0,     0,     0,   147,     0,     0,     0,   148,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     201,   202,     0,     0,     0,     0,   791,   792,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   203,
     777,     0,     0,   204,   205,     0,     0,     0,     0,     0,
       0,     0,     0,   793,   794,     0,   658,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   795,     0,     0,
     209,     0,   149,   150,   151,   152,     0,     0,   153,     0,
     780,     0,     0,     0,   781,     0,     0,     0,   782,     0,
       0,     0,     0,     0,  1037,     0,     0,     0,   784,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,   159,     0,     0,  1038,     0,
       0,     0,     0,   161,     0,     0,   162,     0,     0,   163,
     164,     0,     0,     0,   165,     0,     0,   166,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   168,   169,     0,   786,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,     0,     0,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   787,     0,     0,   788,   789,   864,   865,
     866,   867,   868,   869,     0,     0,     0,     0,     0,     0,
     776,     0,   849,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   201,   202,
       0,     0,     0,     0,   791,   792,     0,   738,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   203,     0,     0,
       0,   204,   205,     0,     0,     0,     0,   777,     0,   662,
     663,   793,   794,   664,   658,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   795,     0,     0,   209,     0,
     665,     0,     0,     0,     0,     0,     0,     0,     0,   149,
     150,   151,   152,     0,     0,     0,     0,   870,     0,     0,
       0,   871,     0,     0,     0,   872,     0,     0,     0,     0,
       0,   873,     0,     0,     0,   784,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   874,     0,     0,
       0,     0,   875,     0,   739,   876,     0,     0,     0,     0,
     877,     0,     0,   878,     0,     0,   879,   880,     0,     0,
       0,   881,     0,     0,   882,     0,   883,     0,   666,   776,
       0,   145,     0,     0,     0,     0,     0,     0,     0,   147,
       0,     0,     0,   148,     0,     0,     0,     0,   884,   885,
       0,     0,   667,   668,   669,   670,   671,   672,   740,   673,
     674,   675,   676,   677,   678,   679,     0,     0,   680,   681,
     682,     0,     0,     0,     0,     0,   777,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   683,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     787,     0,     0,   788,   789,     0,     0,     0,   149,   150,
     151,   152,     0,     0,   153,     0,   780,     0,     0,     0,
     781,     0,     0,     0,   782,     0,     0,     0,     0,     0,
    1037,     0,     0,     0,   784,     0,     0,     0,     0,   662,
     663,   791,   792,   664,   886,     0,   158,     0,     0,     0,
       0,   159,     0,     0,  1038,     0,     0,     0,     0,   161,
     665,     0,   162,     0,     0,   163,   164,     0,   793,   794,
     165,     0,     0,   166,     0,   167,     0,     0,     0,     0,
     313,     0,   887,     0,     0,   209,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   168,   169,     0,
     786,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,     0,   666,   200,
       0,     0,   776,   910,   849,     0,     0,     0,     0,   787,
       0,     0,   788,   789,     0,     0,     0,     0,     0,     0,
       0,     0,   667,   668,   669,   670,   671,   672,     0,   673,
     674,   675,   676,   677,   678,   679,     0,     0,   680,   681,
     682,     0,     0,     0,   201,   202,     0,     0,     0,   777,
     791,   792,     0,     0,     0,     0,     0,     0,     0,   683,
       0,     0,     0,   203,     0,     0,     0,   204,   205,     0,
       0,     0,     0,   776,     0,   849,     0,   793,   794,     0,
     658,   149,   150,   151,   152,     0,     0,     0,     0,   870,
       0,   795,     0,   871,   209,     0,     0,   872,     0,     0,
       0,     0,     0,   873,     0,     0,     0,   784,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   874,
     777,     0,     0,     0,   875,     0,     0,   876,     0,     0,
       0,     0,   877,     0,     0,   878,     0,     0,   879,   880,
       0,     0,     0,   881,     0,     0,   882,     0,   883,     0,
       0,     0,   149,   150,   151,   152,     0,     0,     0,     0,
     870,     0,     0,     0,   871,     0,     0,     0,   872,     0,
     884,   885,     0,     0,   873,     0,     0,     0,   784,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     874,     0,     0,     0,     0,   875,     0,     0,   876,     0,
       0,     0,     0,   877,     0,     0,   878,     0,     0,   879,
     880,     0,     0,     0,   881,     0,     0,   882,     0,   883,
       0,     0,   787,     0,     0,   788,   789,     0,     0,     0,
       0,     0,     0,     0,     0,   776,     0,     0,     0,     0,
       0,   884,   885,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   791,   792,     0,   886,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   777,     0,     0,     0,     0,     0,     0,     0,
     793,   794,     0,   787,     0,     0,   788,   789,     0,     0,
       0,     0,   911,     0,   887,     0,     0,   209,     0,     0,
       0,     0,     0,     0,   149,   150,   151,   152,     0,     0,
       0,     0,   870,     0,     0,     0,   871,     0,     0,     0,
     872,     0,     0,     0,   791,   792,   873,   886,     0,     0,
     784,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   874,     0,     0,     0,     0,   875,     0,     0,
     876,   793,   794,     0,     0,   877,     0,     0,   878,     0,
       0,   879,   880,   313,     0,   887,   881,     0,   209,   882,
       0,   883,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
       0,   146,   147,   884,   885,   284,   148,   285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   286,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   287,   288,     0,     0,     0,   289,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   290,   291,   292,
     293,   294,   295,     0,     0,   787,     0,     0,   788,   789,
       0,     0,     0,     0,     0,     0,   296,     0,   297,     0,
       0,   149,   150,   151,   152,     0,     0,   153,     0,   154,
       0,     0,     0,   155,     0,     0,     0,   156,     0,     0,
       0,     0,     0,   157,     0,     0,   791,   792,     0,   886,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
       0,     0,     0,     0,   159,     0,     0,   160,     0,     0,
       0,     0,   161,   793,   794,   162,     0,     0,   163,   164,
       0,     0,     0,   165,     0,     0,   166,   887,   167,     0,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     168,   169,     0,   170,   171,   172,   173,     0,     0,     0,
       0,     0,   174,   175,     0,     0,   176,   177,   298,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
       0,     0,   299,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   300,     0,     0,
       0,     0,   145,     0,     0,     0,     0,   301,     0,   146,
     147,     0,     0,   302,   148,     0,     0,     0,   303,     0,
       0,     0,     0,     0,     0,     0,     0,   201,   202,     0,
     304,     0,     0,   305,   306,   307,   308,     0,     0,     0,
     309,     0,     0,     0,   310,   311,   203,     0,     0,     0,
     204,   205,     0,     0,     0,     0,     0,     0,     0,   312,
       0,     0,   206,   207,     0,     0,     0,     0,     0,     0,
       0,     0,   313,     0,   208,     0,     0,   209,     0,   149,
     150,   151,   152,     0,     0,   153,     0,   154,     0,     0,
       0,   155,     0,     0,     0,   156,     0,     0,     0,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,     0,     0,   160,     0,     0,     0,     0,
     161,     0,     0,   162,     0,     0,   163,   164,     0,     0,
       0,   165,     0,     0,   166,     0,   167,     0,     0,     0,
       0,     0,     0,   145,     0,     0,     0,     0,     0,     0,
     146,   147,     0,     0,     0,   148,     0,     0,   168,   169,
       0,   170,   171,   172,   173,     0,     0,     0,     0,     0,
     174,   175,     0,     0,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,     0,     0,
     200,     0,     0,     0,  1722,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     149,   150,   151,   152,     0,     0,   153,     0,   154,     0,
       0,     0,   155,     0,     0,     0,   156,     0,     0,     0,
       0,     0,   157,     0,     0,   201,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,   159,   203,     0,   160,     0,   204,   205,
       0,   161,     0,     0,   162,     0,     0,   163,   164,     0,
     206,   207,   165,     0,     0,   166,     0,   167,     0,     0,
     313,     0,   208,     0,   145,   209,     0,     0,     0,     0,
       0,   146,   147,     0,     0,     0,   148,     0,     0,   168,
     169,     0,   170,   171,   172,   173,     0,     0,     0,     0,
       0,   174,   175,     0,     0,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   150,   151,   152,     0,     0,   153,     0,   154,
       0,     0,     0,   155,     0,     0,     0,   156,     0,     0,
       0,     0,     0,   157,     0,     0,   201,   202,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
       0,     0,     0,     0,   159,   203,     0,   160,     0,   204,
     205,     0,   161,     0,     0,   162,     0,     0,   163,   164,
       0,   206,   207,   165,     0,     0,   166,     0,   167,     0,
       0,     0,     0,   208,     0,     0,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     168,   169,     0,   170,   171,   172,   173,     0,     0,     0,
       0,     0,   174,   175,     0,     0,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
       0,     0,   200,     0,     0,     0,     0,   145,     0,     0,
       0,     0,     0,     0,     0,   147,     0,     0,     0,   148,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   201,   202,     0,
       0,     0,   777,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   203,     0,     0,     0,
     204,   205,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   206,   207,   149,   150,   151,   152,     0,     0,
     153,     0,   780,     0,   208,     0,   781,   209,     0,     0,
     782,     0,     0,     0,     0,     0,  1037,     0,     0,     0,
     784,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,   159,     0,     0,
    1038,     0,     0,     0,     0,   161,     0,     0,   162,     0,
       0,   163,   164,     0,     0,     0,   165,     0,     0,   166,
       0,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   168,   169,     0,   786,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,     0,     0,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   787,     0,     0,   788,   789,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     201,   202,     0,     0,     0,     0,   791,   792,     0,     0,
       0,     0,     2,     3,     0,     0,     4,     0,     5,   203,
       0,     0,     0,   204,   205,     0,     0,     0,     0,     0,
       0,     0,     0,   793,   794,     0,   658,     0,     6,     7,
       8,     9,     0,     0,     0,     0,     0,   795,    10,     0,
     209,     0,     0,     0,     0,    11,     0,    12,     0,    13,
       0,     0,    14,    15,    16,     0,    17,     0,     0,     0,
      18,    19,    20,     0,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,   777,
       0,     0,     0,     0,     0,     0,     0,   290,   291,   292,
    1469,  1470,   295,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -335,     0,     0,     0,     0,     0,    34,
       0,   149,   150,   151,   152,     0,     0,     0,    35,   870,
       0,     0,     0,   871,    36,     0,     0,   872,     0,     0,
       0,     0,     0,   873,     0,     0,     0,   784,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,   874,
       0,     0,     0,     0,   875,     0,     0,   876,     0,     0,
       0,     0,   877,     0,     0,   878,     0,     0,   879,   880,
       0,     0,     0,   881,     0,     0,   882,     0,   883,     0,
       0,     0,     0,     0,   777,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     884,   885,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   149,   150,   151,   152,
       0,     0,     0,     0,   870,     0,     0,     0,   871,     0,
       0,     0,   872,    38,     0,     0,     0,     0,   873,     0,
       0,     0,   784,     0,     0,     0,     0,     0,    39,     0,
       0,     0,   787,     0,   874,   788,   789,     0,     0,   875,
       0,     0,   876,     0,    40,     0,     0,   877,     0,    41,
     878,    42,     0,   879,   880,     0,     0,     0,   881,     0,
       0,   882,     0,   883,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   791,   792,     0,   886,     0,     0,     0,
       0,     0,     0,     0,     0,   884,   885,     0,     0,   104,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
     793,   794,   109,   110,     0,   111,   112,   113,     0,   114,
       0,     0,     0,     0,   887,     0,     0,   209,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   787,     0,     0,
     788,   789,     0,     0,     0,     0,     0,     0,   115,     0,
     116,   117,   118,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   791,   792,
       0,   886,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   793,   794,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   887,
       0,     0,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   120,
       0,     0,     0,     0,   121,   122,   123,   124,     0,     0,
       0,     0,     0,     0,     0,   125,     0,     0,     0,     0,
     126,     0,   127,   128
};

static const yytype_int16 yycheck[] =
{
       1,   316,     3,    52,    66,    30,    66,   294,   754,   340,
     360,  1170,   346,   319,    63,   392,    32,    30,   394,   391,
     370,   371,   393,   360,     1,   204,   208,    52,   284,  1171,
    1068,  1069,   374,   370,   371,  1178,  1074,  1175,    63,   416,
     360,    30,   721,   419,  1027,    46,  1269,  1176,  1191,  1177,
    1134,  1237,  1390,    54,  1413,   311,   433,    58,    15,    16,
    1220,  1221,  1411,    52,   106,  1412,   108,   109,  1393,  1136,
     112,     4,   114,     7,    63,   117,   118,   333,   757,   121,
     122,   123,   124,  1324,   390,    43,   128,   766,   795,   131,
     132,   770,     7,     4,     7,   858,  1245,   139,    37,   101,
       7,     8,     9,   859,    94,     1,  1144,   862,     4,     7,
       6,    76,    77,    82,   101,   102,   103,     5,   718,    76,
      77,    78,  1271,  1272,   720,   101,   860,   101,   100,    23,
      26,    27,    28,    29,    23,    92,    93,    94,  1690,     1,
     101,    48,     4,    50,     6,   102,    22,   721,   101,   102,
     103,  1609,    59,   110,   111,    23,   111,    64,   719,   116,
    1592,    68,  1608,  1322,    26,    27,    28,    29,   101,   856,
     857,  1247,    20,   298,    60,    37,   301,   248,   263,   204,
     137,   138,   123,   208,   141,   108,   109,   111,   102,   112,
     111,   114,    55,   122,   117,   118,    56,     8,   121,   122,
     123,   124,   248,    52,   100,   128,   127,   131,   131,   132,
      96,   132,   133,   142,    63,   204,   139,   146,     5,   208,
     144,    13,    20,   101,   100,   101,  1375,  1376,   684,  1388,
      20,   122,    56,   293,   294,    47,   321,    87,    47,   255,
      90,    52,  1391,     1,    51,   261,     4,  1799,     6,  1408,
     321,    87,    82,   101,    90,   146,     1,   212,   213,     4,
     939,     6,    32,    33,    45,   156,   101,  1409,    26,    27,
      28,    29,   320,   249,    30,   321,   197,    30,     4,   360,
       6,    26,    27,    28,    29,   741,   346,  1042,   249,   370,
     371,   316,   122,   265,    86,    40,    52,    42,   360,    52,
     229,   230,   209,   101,  1762,   320,   247,    63,   370,   371,
      63,   101,   716,   717,    55,  1761,   146,   286,   287,   288,
       8,  1753,   321,     1,   326,  1663,     4,   316,     6,   178,
     392,   321,   392,    91,   258,   360,   936,  1496,   387,   326,
     321,  1666,   938,   231,    43,   370,   371,    87,    26,    27,
      28,    29,   326,   402,   416,     4,   416,     6,   246,  1114,
     101,   326,   387,   321,    52,   939,  1045,  1046,   321,   265,
     266,   433,   130,   433,   262,     1,   937,   402,     4,   267,
       6,   129,   321,   312,  1722,  1461,   293,   294,   322,  1152,
     297,     1,  1459,   326,     4,  1636,     6,  1153,   387,  1724,
      26,    27,    28,    29,   754,  1112,   448,   322,   304,   322,
    1494,   322,  1635,   402,  1773,    82,    26,    27,    28,    29,
    1154,  1581,  1771,   314,   322,  1772,   322,   321,    39,    40,
      41,    42,   326,  1471,   322,   197,  1622,   326,   208,   302,
     303,  1590,   304,   319,   231,   305,   306,   307,   204,   298,
     326,   204,   208,   321,   304,   208,   297,    87,   326,   246,
     322,  1499,    73,  1150,  1151,    91,    55,   316,   304,   124,
      81,    82,    83,    84,   232,   262,     5,    88,   809,     8,
     267,   305,   306,   307,    37,    38,    97,    98,    99,   100,
     447,    55,   124,   104,   149,  1478,   403,    87,   238,   406,
     240,   246,   409,   197,   130,   231,   413,    82,    87,   120,
      55,   418,   101,   863,   125,   126,   127,   149,    87,   130,
     246,   306,   133,  1269,   481,   448,   265,   266,   862,   933,
     934,   935,   138,   111,  1280,   322,   262,   101,   387,    43,
      82,   267,    84,   863,   948,   151,   304,   122,  1632,   728,
     887,   142,    55,   402,    58,    59,   101,   907,    79,  1238,
     316,   167,     0,   316,   322,   286,     4,  1710,     6,  1707,
     248,   146,    30,     8,    95,   296,   483,   322,  1324,  1708,
     100,  1709,   321,   140,   926,   163,   164,   907,     1,    24,
     246,     4,   113,     6,    52,   251,   252,     1,   101,   156,
       4,    22,     6,   107,    25,    63,   232,   247,   238,  1768,
     240,   267,   116,    26,    27,    28,    29,    52,   122,   286,
     287,   288,    26,    27,    28,    29,   304,  1769,   181,   182,
      30,   387,   109,   110,   387,    39,   321,   108,   229,   230,
       1,   326,   146,     4,   322,     6,   402,     7,   238,   402,
     240,   122,    52,   263,   100,   197,   267,   268,   269,   238,
      20,   240,    22,    63,  1702,    26,    27,    28,    29,   238,
     247,   240,   100,   754,    87,   281,   255,    30,   304,   861,
     247,    94,   127,    87,    82,    89,   131,    91,   265,   266,
      94,   108,   754,   247,   304,   131,   322,     1,   714,    52,
       4,   140,     6,   728,   159,   122,   145,   111,  1042,   263,
      63,   162,   322,     4,   795,   257,   167,   130,   163,   164,
     304,   312,    26,    27,    28,    29,   360,   163,   164,   754,
     166,   208,   209,    37,   280,   212,   370,   371,    43,   728,
     101,   102,   103,   198,   199,   200,   204,     4,   149,     6,
     208,   164,    17,   246,  1792,   159,    75,     5,   159,   160,
       8,  1017,   321,  1353,  1354,  1355,  1356,   326,     1,   262,
     795,     4,    18,     6,   325,   856,   857,   858,   859,   860,
    1114,    38,   863,   131,   395,   396,   397,    60,    61,   108,
    1106,  1107,    65,    26,    27,    28,    29,  1113,  1129,    50,
     101,   863,   862,   122,   204,    50,   887,    40,   208,    42,
     318,   319,  1149,   424,   113,   163,   164,    55,  1155,   232,
    1157,  1158,    43,    44,   125,   126,   907,   111,    20,   128,
      22,   856,   857,   858,   859,   860,   861,     4,   863,     6,
     124,     8,   321,   191,   455,   907,   321,   131,   167,   321,
     149,   204,   104,   105,   106,   208,   155,     4,   316,     6,
       7,     1,   887,   248,     4,   149,     6,   159,   321,  1048,
      30,   155,   861,    30,  1516,  1517,  1518,  1519,   109,   110,
     111,   111,   907,   113,   114,   115,    26,    27,    28,    29,
    1636,   304,    52,    43,     1,    52,   215,     4,   321,     6,
     304,   163,   164,    63,   203,   204,    63,   208,     4,   322,
       6,   912,     8,   321,   915,    43,   316,    30,   322,    26,
      27,    28,    29,  1513,  1514,  1515,    43,   228,   229,   387,
    1280,   305,   306,   307,    58,    59,   248,   249,  1253,    52,
      15,    16,   849,   304,   402,     7,   853,    87,   124,    43,
      63,    45,   265,   266,    94,  1134,    50,  1136,    52,   101,
     360,   322,    56,   316,   140,   257,   258,   259,   260,   261,
     370,   371,   728,   149,  1324,   728,   290,   291,   292,   155,
     156,     8,  1042,   107,   265,   266,  1317,   387,  1319,    20,
     130,    22,   116,   327,   101,   102,   103,   327,   122,   297,
     304,    95,   402,    97,  1646,  1647,  1648,   297,  1323,    15,
      16,     1,   100,   246,     4,   315,     6,   324,   322,   101,
     102,   103,   146,  1048,   164,  1106,  1107,  1108,  1109,  1110,
       1,  1112,  1113,     4,   387,     6,    26,    27,    28,    29,
    1121,  1122,    15,    16,   204,   109,   110,   204,   208,   402,
      82,   208,  1114,   192,  1114,    26,    27,    28,    29,  1048,
     109,   110,   201,   202,     4,     5,   205,   206,  1149,  1150,
    1151,  1152,  1153,  1154,  1155,    23,  1157,  1158,   286,   287,
     288,  1106,  1107,  1108,  1109,  1110,    23,  1112,  1113,   322,
      50,   204,   232,   291,   292,   208,  1121,  1122,  1777,  1778,
     274,   275,   276,   277,   278,   861,   109,   110,   861,  1134,
     100,  1136,    92,    93,     1,    94,    50,     4,    50,     6,
     754,    41,    42,    50,  1149,  1150,  1151,  1152,  1153,  1154,
    1155,    50,  1157,  1158,   100,  1511,  1508,    43,  1509,    26,
      27,    28,    29,    82,  1169,  1134,     1,  1136,   127,     4,
     321,     6,    58,    59,  1121,  1122,   316,   100,   100,   316,
    1537,    82,   100,    17,   304,  1166,  1167,  1168,  1169,  1170,
    1171,    26,    27,    28,    29,   134,   135,   136,   137,   315,
    1169,    82,   322,  1470,   100,    40,  1563,    42,  1269,   100,
    1167,  1168,  1169,  1170,  1171,    18,   325,   304,     5,  1280,
    1506,   107,     7,   316,   183,   184,   185,   186,   187,   188,
     116,    97,    98,    99,   100,   322,   122,     7,  1280,   111,
       7,   113,   856,   857,   858,   859,   860,   387,  1253,   863,
     387,     7,  1233,  1282,  1235,  1236,   100,  1238,   100,   131,
     146,     5,   402,  1324,  1269,   402,     7,   139,   140,   141,
     142,     7,   321,   887,     7,  1280,  1233,  1282,  1235,  1236,
      17,  1238,   325,    18,  1253,    83,    84,    85,    12,    87,
     728,     8,   100,   907,   387,   265,   266,   248,   100,    37,
    1459,  1282,     1,   321,   321,     4,  1636,     6,   321,   402,
     248,   321,  1048,  1282,   263,  1048,   321,  1612,  1323,  1324,
     100,   100,  1362,   100,   100,   111,   100,    26,    27,    28,
      29,   321,   100,   298,   304,  1494,   122,    44,   124,    46,
    1169,    48,    49,   100,   321,   100,   100,    71,   728,    56,
      57,    75,   322,   304,  1323,   100,   142,   100,   321,   321,
     146,   100,     5,   149,     8,    50,    90,    91,  1373,   100,
     100,   322,   100,   100,   754,    41,   145,   111,    68,  1360,
    1373,     5,    89,   107,   100,  1390,   111,  1368,  1369,  1370,
    1371,  1372,    91,    43,   324,   728,   263,  1390,  1134,   111,
    1136,  1134,  1407,  1136,  1373,  1386,  1387,  1388,    58,    59,
     196,   246,   136,    82,     8,    82,   324,  1398,  1399,   143,
     100,  1390,     7,   861,  1253,  1406,  1407,  1408,  1409,  1469,
    1470,   130,   321,  1169,   321,     7,  1169,   304,  1407,   321,
     328,   100,   249,   229,   230,  1426,  1427,  1428,   328,  1406,
    1407,  1408,  1409,  1282,  1459,   322,     5,   107,   100,   321,
    1347,  1348,  1349,  1350,   101,    41,   116,   268,   263,  1426,
    1427,  1428,   122,  1632,     7,   248,   856,   857,   858,   859,
     860,   861,   101,   863,   101,   101,     5,   322,   161,  1494,
    1459,   100,    38,   101,  1323,  1537,   146,  1537,   101,    96,
     320,  1482,   109,   110,   100,   184,   320,   887,   101,   320,
     117,   118,   119,   120,   121,   264,   100,  1253,   100,   100,
    1253,  1563,   111,  1563,   113,  1494,   312,   907,   861,  1569,
     100,   322,   100,   232,   100,  1149,  1150,  1151,  1152,  1153,
    1154,  1155,   131,  1157,  1158,    82,  1282,   322,     5,  1282,
     139,   140,  1533,   142,  1535,  1536,   182,   100,    82,    40,
      84,   147,  1584,   152,   153,     7,   100,   320,  1549,   100,
     102,   264,  1594,   100,  1555,  1636,   322,    43,  1407,  1601,
     100,  1562,  1469,  1470,  1565,   109,   110,  1323,   728,   249,
    1323,   728,    58,    59,  1575,  1576,  1577,   101,   181,   123,
     321,   125,   126,   127,   100,   304,   321,  1612,   321,   130,
    1048,    76,    77,    78,    79,    80,    81,   321,  1575,  1576,
    1577,   321,   100,   322,   148,   149,   150,  1632,  1668,   321,
    1670,  1636,   321,   321,   321,   728,   322,  1373,   321,   100,
    1373,   107,   100,  1612,   322,   321,   321,   321,   101,  1654,
     116,   100,   320,   248,  1390,  1269,   122,  1390,  1663,  1640,
     100,  1654,     5,  1632,   100,    20,  1280,   389,  1048,  1174,
    1663,  1407,  1394,   197,  1407,  1661,    43,  1816,  1792,  1659,
     146,  1714,  1716,  1715,  1780,  1654,  1717,  1706,  1669,    89,
    1671,    58,    59,  1349,  1663,   386,  1134,    91,  1136,  1322,
    1681,  1682,  1683,  1684,  1685,  1686,  1687,   763,  1689,  1499,
    1324,   771,  1483,   303,  1446,  1048,   830,  1722,   388,  1765,
    1705,   861,  1108,  1459,   861,  1110,  1459,  1109,  1127,  1722,
     845,  1169,  1132,   257,   286,    43,   854,   967,  1778,  1074,
     107,  1158,  1723,  1254,  1725,  1726,  1727,  1728,  1729,   116,
      58,    59,  1792,  1722,  1134,   122,  1136,   204,  1494,  1278,
    1274,  1494,  1767,   398,   400,   371,   119,   401,   861,  1149,
    1150,  1151,  1152,  1153,  1154,  1155,  1816,  1157,  1158,   146,
    1825,   399,   360,  1612,   298,  1766,  1767,  1768,  1769,  1169,
     621,   299,   299,  1774,  1775,  1776,  1777,   984,  1767,   107,
    1781,  1134,  1783,  1136,    -1,    -1,    -1,    -1,   116,  1766,
    1767,  1768,  1769,    -1,   122,  1253,  1797,  1774,  1775,  1776,
    1777,  1802,  1803,  1804,  1805,  1806,  1807,  1808,  1809,  1810,
    1811,  1812,  1813,    -1,    -1,    -1,  1169,    -1,   146,    -1,
      -1,    -1,    -1,    -1,  1282,  1826,    -1,   109,   110,    -1,
    1807,  1808,  1809,  1834,  1835,  1836,    -1,    -1,    -1,    -1,
      -1,   123,    -1,   125,   126,   127,     1,    -1,    -1,     4,
      -1,     6,    -1,  1253,    -1,    -1,  1612,    -1,     1,  1612,
      -1,     4,    -1,     6,    -1,  1323,   148,   149,   150,  1269,
      -1,    26,    27,    28,    29,    -1,  1632,    -1,    -1,  1632,
    1280,    36,  1282,    26,    27,    28,    29,    -1,  1048,    -1,
      45,  1048,    -1,    -1,    -1,    50,    39,    52,  1654,    54,
    1253,  1654,    -1,    -1,    -1,    -1,    -1,  1663,    -1,    -1,
    1663,    -1,    -1,    -1,     1,  1373,    -1,     4,  1767,     6,
      -1,    -1,    -1,  1323,  1324,    -1,    -1,    -1,    -1,  1282,
      -1,    -1,  1390,    -1,  1070,  1048,    -1,    -1,    -1,    26,
      27,    28,    29,    86,    87,    88,    89,    -1,    91,  1407,
      -1,    94,    -1,    -1,    -1,     1,    -1,    -1,     4,     1,
       6,    -1,     4,    -1,     6,    -1,  1722,    -1,   111,  1722,
    1323,    -1,    -1,  1373,  1134,    -1,  1136,  1134,    43,  1136,
      26,    27,    28,    29,    26,    27,    28,    29,    -1,    -1,
    1390,    -1,    -1,    58,    59,    -1,    -1,    39,    -1,    -1,
       1,  1459,  1636,     4,   159,     6,    -1,  1407,    -1,  1169,
      -1,  1767,  1169,    -1,  1767,    -1,   159,    -1,    -1,    -1,
    1373,  1134,    -1,  1136,   111,    26,    27,    28,    29,    -1,
      -1,  1167,  1168,  1169,  1170,  1171,  1494,  1390,    -1,    -1,
      -1,    87,   107,    -1,    86,    87,    88,    89,    94,    91,
      -1,   116,    94,    -1,  1407,    -1,  1169,   122,    -1,  1459,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,
      -1,    -1,    -1,    -1,    -1,    -1,   231,    -1,    -1,    -1,
      -1,   146,    -1,    -1,   130,    -1,    -1,    -1,   231,    43,
      -1,   246,    -1,  1253,  1494,    -1,  1253,  1233,    -1,  1235,
    1236,    -1,  1238,   246,    58,    59,  1459,   262,    -1,    -1,
     111,    -1,   267,    -1,   269,    -1,    -1,   159,   164,   262,
      -1,    36,  1282,    -1,   267,  1282,    -1,    -1,    43,    -1,
      45,    -1,    47,    -1,    -1,    50,    51,    52,  1274,    54,
    1253,  1494,    -1,    -1,    -1,   232,    -1,    -1,    -1,   304,
      -1,    -1,    -1,   107,  1612,     1,    -1,    -1,     4,    -1,
       6,   304,   116,  1323,    -1,    -1,  1323,   322,   122,  1282,
      -1,    -1,    -1,    -1,  1632,    -1,    -1,    -1,    -1,   322,
      26,    27,    28,    29,    -1,    -1,   232,    -1,    -1,   231,
      -1,    -1,   146,    39,    -1,    -1,  1654,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   246,  1663,    -1,    -1,    -1,    -1,
    1323,    -1,  1612,  1373,    -1,    -1,  1373,   304,    -1,    -1,
     262,    -1,    -1,    -1,    -1,   267,    -1,    -1,    -1,    -1,
    1390,   232,  1632,  1390,    -1,   322,  1636,    36,    -1,    -1,
      86,    87,    88,    89,    43,    91,    45,  1407,    94,    -1,
    1407,    50,    51,    52,  1654,    54,    -1,    -1,   304,  1612,
    1373,    -1,   304,  1663,  1722,   111,    -1,    -1,    -1,    -1,
    1406,  1407,  1408,  1409,    -1,    -1,   322,  1390,    -1,  1632,
     322,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1426,  1427,  1428,    -1,  1407,    -1,    -1,    -1,    -1,  1459,
      -1,  1654,  1459,   304,    -1,    -1,    -1,    -1,    -1,  1767,
    1663,    -1,    -1,   159,     1,    -1,   231,    -1,    -1,    -1,
      -1,   322,  1722,    -1,    11,    12,    13,    14,    15,    16,
      17,   246,    -1,    20,  1494,     1,    -1,  1494,     4,    -1,
       6,    -1,    -1,    -1,    -1,    -1,  1459,   262,    -1,    -1,
      -1,    -1,   267,    -1,   269,    -1,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,    -1,    -1,    -1,  1767,    -1,  1722,
      -1,    -1,    -1,    -1,    40,    -1,    42,    -1,    -1,    -1,
      -1,  1494,    -1,    -1,    71,   231,    -1,    74,    75,    76,
      77,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    86,
     246,    88,    89,    90,    91,    92,    93,    94,    95,    -1,
      97,    98,    99,   100,  1767,   102,   262,    -1,   105,    -1,
     107,   267,    -1,   110,   111,    -1,   113,    -1,    -1,   116,
      37,    -1,   231,    -1,    -1,    -1,    -1,    -1,    -1,  1575,
    1576,  1577,    -1,    -1,    -1,    -1,    -1,   246,   135,   136,
     137,   138,  1612,    -1,   141,  1612,   143,    -1,   304,    -1,
      -1,    -1,    -1,   262,   725,    -1,   727,    -1,   267,    -1,
     269,    -1,  1632,    -1,    -1,  1632,   322,    -1,    -1,    -1,
      -1,    -1,   743,   744,    -1,   746,    -1,    -1,    -1,   750,
     751,    -1,    -1,   100,  1654,     1,    -1,  1654,     4,  1612,
       6,    -1,    -1,  1663,    -1,    -1,  1663,     1,    -1,    -1,
       4,    -1,     6,    -1,   775,    -1,    -1,   778,    -1,  1632,
      26,    27,    28,    29,    -1,    -1,     1,    -1,    -1,     4,
      36,     6,    26,    27,    28,    29,    -1,    -1,    -1,    45,
      -1,  1654,    -1,    -1,    50,    39,    52,    -1,    54,    -1,
    1663,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1722,   170,    39,  1722,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,    -1,    -1,   839,    -1,
     246,   842,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    87,    -1,    89,     1,    91,    21,     4,
      94,     6,    -1,    -1,    -1,    -1,    -1,  1767,    -1,  1722,
    1767,    -1,    87,    -1,    89,    -1,    91,   111,    -1,    94,
      -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
    1766,  1767,  1768,  1769,    -1,    -1,   111,    -1,  1774,  1775,
    1776,  1777,    -1,    -1,    -1,    68,    -1,   908,   909,    -1,
      -1,    -1,    -1,   159,  1767,    -1,   322,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   159,    -1,    -1,    -1,    -1,
      -1,  1807,  1808,  1809,    -1,    -1,    -1,   100,   101,   102,
     103,    -1,    -1,    -1,   159,   108,    -1,    -1,    84,   112,
      -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,
      -1,    -1,    -1,   126,    -1,   101,   111,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,
     143,    -1,    -1,   146,    -1,   231,    -1,    -1,   151,   125,
     126,   154,    -1,    -1,   157,   158,    -1,    -1,    -1,   162,
     246,    -1,   165,    -1,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   440,    -1,    -1,   262,    -1,    -1,    -1,
     447,   267,    -1,   269,    -1,    -1,   189,   190,    -1,    -1,
     457,    -1,   459,    -1,   461,  1036,   463,    -1,    -1,  1040,
      -1,   468,    -1,    -1,   471,    -1,   473,    -1,  1049,  1050,
    1051,    -1,    -1,  1054,   481,  1056,    -1,    -1,   304,    -1,
      -1,    -1,    -1,    -1,    -1,  1066,    -1,    -1,    -1,    -1,
     304,    -1,   208,    -1,    -1,    -1,   322,    -1,   241,    -1,
      -1,   244,   245,    -1,    -1,    -1,    -1,   232,   322,   304,
      -1,    -1,   228,   229,    -1,    -1,    -1,    -1,  1099,    -1,
    1101,  1102,    -1,    -1,    -1,    -1,    -1,   322,    68,    -1,
     246,    -1,    -1,    -1,  1115,    -1,  1117,    -1,    -1,   282,
     283,    -1,   285,    -1,    -1,  1126,   262,  1128,    -1,    -1,
      -1,   267,    -1,   269,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,   309,   310,   108,    -1,
      -1,    -1,   112,    -1,    -1,    -1,   116,    -1,   321,   304,
     323,    -1,   122,   326,    -1,    82,   126,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,   322,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   146,    -1,    37,    -1,
      -1,    -1,   109,   110,    -1,    -1,   113,     1,    -1,    -1,
       4,    -1,     6,    -1,    -1,    -1,   123,   124,   125,   126,
     127,   128,   129,   130,   131,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    26,    27,    28,    29,    30,    31,    -1,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,  1240,
    1241,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,   100,    -1,    -1,    -1,   172,    60,    61,    -1,  1260,
      -1,    65,    -1,    -1,    -1,  1266,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    -1,    -1,
     197,   241,    -1,    -1,   244,   245,    -1,    91,    -1,    -1,
      -1,    95,  1293,    97,    -1,    -1,   100,   101,   102,   103,
      -1,    -1,   106,    -1,   108,    -1,    -1,   111,   112,  1310,
      -1,  1312,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,   170,   282,   283,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   138,    -1,   131,    -1,    -1,   143,
     257,    -1,   146,    -1,    -1,   140,    -1,   151,    -1,    -1,
     154,    -1,    -1,   157,   158,   159,    -1,    -1,   162,    -1,
     155,   165,    -1,   167,   159,    -1,   326,    -1,   163,   164,
      -1,    -1,    -1,   168,   169,   170,   171,   172,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   189,   190,    -1,   192,   193,
     194,   195,    -1,    -1,    -1,    -1,    -1,   201,   202,    -1,
      -1,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   109,   110,   231,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,    -1,   246,    -1,    -1,    -1,   130,    -1,    -1,    -1,
      -1,    -1,   256,  1454,    -1,    -1,    -1,    -1,   262,    -1,
      -1,    -1,   146,   267,    -1,    -1,    -1,  1468,    -1,    -1,
      -1,    -1,   276,   277,    -1,   279,    -1,    -1,   282,   283,
     284,   285,    -1,    -1,    -1,   289,    -1,  1488,    -1,   293,
     294,   295,    -1,    -1,    -1,   299,   300,    -1,    -1,    -1,
     304,    -1,    -1,    -1,   308,    -1,    -1,   311,   312,     1,
      -1,    -1,     4,    -1,     6,    -1,    -1,   321,   322,   323,
      -1,    -1,   326,    -1,    -1,    -1,   953,   954,   955,    -1,
      -1,    23,    -1,    -1,    26,    27,    28,    29,    30,    31,
      -1,    -1,    34,    35,    36,    -1,    -1,    -1,   232,   233,
     234,   235,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    -1,    -1,   248,   249,   250,    -1,    60,    61,
      -1,    -1,    -1,    65,    -1,    -1,   109,   110,    -1,    -1,
     113,    -1,    -1,    -1,    76,    77,    78,    79,    80,    81,
     123,   124,   125,   126,   127,   128,   129,   130,   131,    91,
      -1,    -1,    -1,    95,    -1,    97,    -1,    -1,   100,   101,
     102,   103,    -1,    -1,   106,    -1,   108,    -1,    -1,   111,
     112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,  1630,
     122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,
      -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,
      -1,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,   151,
      -1,    -1,   154,    -1,    -1,   157,   158,   159,    -1,    -1,
     162,    -1,    36,   165,    -1,   167,    -1,    -1,    -1,    43,
      -1,    45,    -1,    47,    -1,    -1,    50,    51,    52,    -1,
      54,    -1,    -1,    -1,    58,    59,    -1,   189,   190,    -1,
     192,   193,   194,   195,    -1,    -1,    -1,    -1,    -1,   201,
     202,    -1,    -1,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,    -1,    -1,   231,
      -1,    -1,    -1,   107,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,    -1,   246,    -1,    -1,    -1,   122,    -1,
      -1,    -1,    -1,    -1,   256,    -1,    -1,    -1,    -1,    -1,
     262,    -1,    -1,    -1,    -1,   267,    -1,    -1,    -1,    -1,
      -1,    -1,   146,    -1,   276,   277,    -1,   279,    -1,    -1,
     282,   283,   284,   285,    -1,    -1,    -1,   289,    -1,    -1,
      -1,   293,   294,   295,    -1,    -1,    -1,   299,   300,    -1,
       1,    -1,   304,     4,    -1,     6,   308,    -1,    -1,   311,
     312,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   321,
     322,   323,    23,    -1,   326,    26,    27,    28,    29,    30,
      31,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,    -1,    60,
      61,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   246,    -1,    -1,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   262,    -1,
      91,    -1,    -1,   267,    95,   269,    97,    -1,    -1,   100,
     101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,    -1,
     111,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,
      -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,
     151,    -1,    -1,   154,    -1,    -1,   157,   158,   159,    -1,
      -1,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   189,   190,
      -1,   192,   193,   194,   195,    -1,    -1,    -1,    -1,    -1,
     201,   202,    -1,    -1,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,    -1,    -1,
     231,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   246,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   256,    -1,    -1,    -1,    -1,
      -1,   262,    -1,    -1,    -1,    -1,   267,    -1,    -1,    -1,
       4,    -1,     6,    -1,    -1,   276,   277,    -1,   279,    -1,
      -1,   282,   283,   284,   285,    -1,    -1,    -1,   289,    23,
      -1,    -1,   293,   294,   295,    -1,    30,    31,   299,   300,
      34,    35,    36,   304,    -1,    -1,    -1,   308,    -1,    -1,
     311,   312,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
     321,   322,   323,    -1,    -1,   326,    60,    61,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
      -1,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,    -1,
      -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,   143,
      -1,    -1,   146,    -1,    -1,    -1,    -1,   151,    -1,    -1,
     154,    -1,    -1,   157,   158,    -1,    -1,    -1,   162,    -1,
      -1,   165,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   189,   190,    -1,   192,   193,
     194,   195,    -1,    -1,    -1,    -1,    -1,   201,   202,    -1,
      -1,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,    -1,    -1,   231,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,
      -1,    -1,   246,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,   256,    23,    -1,    -1,    -1,    -1,   262,    -1,
      -1,    31,    -1,   267,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    -1,   276,   277,    -1,   279,    -1,    -1,   282,   283,
     284,   285,    -1,    -1,    -1,   289,    -1,    -1,    -1,   293,
     294,   295,    -1,    -1,    -1,   299,   300,    -1,    68,    -1,
      -1,    -1,    -1,    -1,   308,    -1,    -1,   311,   312,    -1,
      -1,    -1,    82,    -1,    84,    -1,    -1,   321,   322,   323,
      -1,    -1,   326,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,
      -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,   126,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,
      -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,
      -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   189,
     190,    -1,   192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,    -1,
      -1,   231,    -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   241,    -1,    -1,   244,   245,    -1,    -1,    -1,    21,
      -1,    23,    -1,    -1,    -1,    -1,    -1,   257,    -1,    31,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   276,   277,    -1,    -1,
      -1,    -1,   282,   283,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,    -1,    -1,   295,    68,    -1,    -1,   299,
     300,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   309,
     310,    -1,   312,    -1,    -1,   127,    -1,    -1,   130,    -1,
      -1,    -1,    -1,   323,    -1,    -1,   326,    -1,   100,   101,
     102,   103,    -1,    -1,   106,   147,   108,    -1,    -1,    -1,
     112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,
      -1,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,   151,
      -1,    -1,   154,    -1,    -1,   157,   158,    -1,    -1,    -1,
     162,    -1,    -1,   165,    -1,   167,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   189,   190,    -1,
     192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   269,    -1,   231,
      -1,     5,    -1,    -1,   276,   277,    -1,    -1,    -1,   241,
      -1,    -1,   244,   245,   286,    -1,    -1,    21,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     312,    -1,    -1,    -1,   276,   277,    -1,    -1,    -1,    -1,
     282,   283,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      -1,    -1,    -1,   295,    68,    -1,    -1,   299,   300,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   309,   310,    -1,
     312,    -1,    -1,   127,    -1,    -1,   130,    -1,    -1,    -1,
      -1,   323,    -1,    -1,   326,    -1,   100,   101,   102,   103,
      -1,    -1,   106,   147,   108,    -1,    -1,    -1,   112,    -1,
      -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,   143,
      -1,    -1,   146,    -1,    -1,    -1,    -1,   151,    -1,    -1,
     154,    -1,    -1,   157,   158,    -1,    -1,    -1,   162,    -1,
      -1,   165,    -1,   167,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   189,   190,    -1,   192,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   269,    -1,   231,    -1,     5,
      -1,    -1,   276,   277,    -1,    -1,    -1,   241,    -1,    -1,
     244,   245,   286,    -1,    -1,    21,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   312,    -1,
      -1,    -1,   276,   277,    -1,    -1,    -1,    -1,   282,   283,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   295,    68,    -1,    -1,   299,   300,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   309,   310,    -1,   312,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   323,
      -1,    -1,   326,    -1,   100,   101,   102,   103,    -1,    -1,
     106,    -1,   108,    -1,    -1,    -1,   112,    -1,    -1,    -1,
     116,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,
     126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    -1,    -1,   143,    -1,    -1,
     146,    -1,    -1,    -1,    -1,   151,    -1,    -1,   154,    -1,
      -1,   157,   158,    -1,    -1,    -1,   162,    -1,    -1,   165,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   189,   190,    -1,   192,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,    -1,    -1,   231,    -1,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   241,    -1,    -1,   244,   245,
      -1,    -1,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     276,   277,    -1,    -1,    -1,    -1,   282,   283,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   295,
      68,    -1,    -1,   299,   300,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   309,   310,    -1,   312,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   323,    -1,    -1,
     326,    -1,   100,   101,   102,   103,    -1,    -1,   106,    -1,
     108,    -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,   143,    -1,    -1,   146,    -1,
      -1,    -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,
     158,    -1,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   189,   190,    -1,   192,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,    -1,    -1,   231,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   241,    -1,    -1,   244,   245,     9,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   276,   277,
      -1,    -1,    -1,    -1,   282,   283,    -1,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   295,    -1,    -1,
      -1,   299,   300,    -1,    -1,    -1,    -1,    68,    -1,   109,
     110,   309,   310,   113,   312,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   323,    -1,    -1,   326,    -1,
     130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,
      -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,
      -1,    -1,   143,    -1,   184,   146,    -1,    -1,    -1,    -1,
     151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,    -1,
      -1,   162,    -1,    -1,   165,    -1,   167,    -1,   208,    21,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,   189,   190,
      -1,    -1,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,    -1,    -1,   248,   249,
     250,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   269,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     241,    -1,    -1,   244,   245,    -1,    -1,    -1,   100,   101,
     102,   103,    -1,    -1,   106,    -1,   108,    -1,    -1,    -1,
     112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,   109,
     110,   282,   283,   113,   285,    -1,   138,    -1,    -1,    -1,
      -1,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,   151,
     130,    -1,   154,    -1,    -1,   157,   158,    -1,   309,   310,
     162,    -1,    -1,   165,    -1,   167,    -1,    -1,    -1,    -1,
     321,    -1,   323,    -1,    -1,   326,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   189,   190,    -1,
     192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,    -1,   208,   231,
      -1,    -1,    21,    22,    23,    -1,    -1,    -1,    -1,   241,
      -1,    -1,   244,   245,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   232,   233,   234,   235,   236,   237,    -1,   239,
     240,   241,   242,   243,   244,   245,    -1,    -1,   248,   249,
     250,    -1,    -1,    -1,   276,   277,    -1,    -1,    -1,    68,
     282,   283,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   269,
      -1,    -1,    -1,   295,    -1,    -1,    -1,   299,   300,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,   309,   310,    -1,
     312,   100,   101,   102,   103,    -1,    -1,    -1,    -1,   108,
      -1,   323,    -1,   112,   326,    -1,    -1,   116,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,    -1,   126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,
      68,    -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,
      -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,
      -1,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,
      -1,    -1,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
     108,    -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,
     189,   190,    -1,    -1,   122,    -1,    -1,    -1,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,   143,    -1,    -1,   146,    -1,
      -1,    -1,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,
     158,    -1,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,
      -1,    -1,   241,    -1,    -1,   244,   245,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,   189,   190,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   282,   283,    -1,   285,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     309,   310,    -1,   241,    -1,    -1,   244,   245,    -1,    -1,
      -1,    -1,   321,    -1,   323,    -1,    -1,   326,    -1,    -1,
      -1,    -1,    -1,    -1,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,   108,    -1,    -1,    -1,   112,    -1,    -1,    -1,
     116,    -1,    -1,    -1,   282,   283,   122,   285,    -1,    -1,
     126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    -1,    -1,   143,    -1,    -1,
     146,   309,   310,    -1,    -1,   151,    -1,    -1,   154,    -1,
      -1,   157,   158,   321,    -1,   323,   162,    -1,   326,   165,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,   189,   190,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    -1,    -1,   241,    -1,    -1,   244,   245,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,    -1,    -1,   106,    -1,   108,
      -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,   282,   283,    -1,   285,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,
      -1,    -1,   151,   309,   310,   154,    -1,    -1,   157,   158,
      -1,    -1,    -1,   162,    -1,    -1,   165,   323,   167,    -1,
     326,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     189,   190,    -1,   192,   193,   194,   195,    -1,    -1,    -1,
      -1,    -1,   201,   202,    -1,    -1,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
      -1,    -1,   231,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   246,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,   256,    -1,    30,
      31,    -1,    -1,   262,    35,    -1,    -1,    -1,   267,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   276,   277,    -1,
     279,    -1,    -1,   282,   283,   284,   285,    -1,    -1,    -1,
     289,    -1,    -1,    -1,   293,   294,   295,    -1,    -1,    -1,
     299,   300,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   308,
      -1,    -1,   311,   312,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   321,    -1,   323,    -1,    -1,   326,    -1,   100,
     101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,    -1,
      -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,
      -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,
     151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,    -1,
      -1,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,    -1,    -1,    35,    -1,    -1,   189,   190,
      -1,   192,   193,   194,   195,    -1,    -1,    -1,    -1,    -1,
     201,   202,    -1,    -1,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,    -1,    -1,
     231,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,   102,   103,    -1,    -1,   106,    -1,   108,    -1,
      -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,   276,   277,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,   143,   295,    -1,   146,    -1,   299,   300,
      -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,    -1,
     311,   312,   162,    -1,    -1,   165,    -1,   167,    -1,    -1,
     321,    -1,   323,    -1,    23,   326,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    -1,    -1,    35,    -1,    -1,   189,
     190,    -1,   192,   193,   194,   195,    -1,    -1,    -1,    -1,
      -1,   201,   202,    -1,    -1,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,    -1,
      -1,   231,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   100,   101,   102,   103,    -1,    -1,   106,    -1,   108,
      -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,   276,   277,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,    -1,   143,   295,    -1,   146,    -1,   299,
     300,    -1,   151,    -1,    -1,   154,    -1,    -1,   157,   158,
      -1,   311,   312,   162,    -1,    -1,   165,    -1,   167,    -1,
      -1,    -1,    -1,   323,    -1,    -1,   326,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     189,   190,    -1,   192,   193,   194,   195,    -1,    -1,    -1,
      -1,    -1,   201,   202,    -1,    -1,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
      -1,    -1,   231,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   276,   277,    -1,
      -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   295,    -1,    -1,    -1,
     299,   300,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   311,   312,   100,   101,   102,   103,    -1,    -1,
     106,    -1,   108,    -1,   323,    -1,   112,   326,    -1,    -1,
     116,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,
     126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    -1,    -1,   143,    -1,    -1,
     146,    -1,    -1,    -1,    -1,   151,    -1,    -1,   154,    -1,
      -1,   157,   158,    -1,    -1,    -1,   162,    -1,    -1,   165,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   189,   190,    -1,   192,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,    -1,    -1,   231,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   241,    -1,    -1,   244,   245,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     276,   277,    -1,    -1,    -1,    -1,   282,   283,    -1,    -1,
      -1,    -1,     0,     1,    -1,    -1,     4,    -1,     6,   295,
      -1,    -1,    -1,   299,   300,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   309,   310,    -1,   312,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,   323,    36,    -1,
     326,    -1,    -1,    -1,    -1,    43,    -1,    45,    -1,    47,
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
      -1,    -1,    -1,   162,    -1,    -1,   165,    -1,   167,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     189,   190,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,   112,    -1,
      -1,    -1,   116,   231,    -1,    -1,    -1,    -1,   122,    -1,
      -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,   246,    -1,
      -1,    -1,   241,    -1,   138,   244,   245,    -1,    -1,   143,
      -1,    -1,   146,    -1,   262,    -1,    -1,   151,    -1,   267,
     154,   269,    -1,   157,   158,    -1,    -1,    -1,   162,    -1,
      -1,   165,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   282,   283,    -1,   285,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   189,   190,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
     309,   310,    49,    50,    -1,    52,    53,    54,    -1,    56,
      -1,    -1,    -1,    -1,   323,    -1,    -1,   326,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   241,    -1,    -1,
     244,   245,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,
      97,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   282,   283,
      -1,   285,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   309,   310,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   323,
      -1,    -1,   326,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   231,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   246,
      -1,    -1,    -1,    -1,   251,   252,   253,   254,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   262,    -1,    -1,    -1,    -1,
     267,    -1,   269,   270
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   330,     0,     1,     4,     6,    26,    27,    28,    29,
      36,    43,    45,    47,    50,    51,    52,    54,    58,    59,
      60,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   107,   116,   122,   146,   231,   246,
     262,   267,   269,   331,   333,   334,   335,   336,   400,   401,
     402,   404,   419,   331,   102,   101,   397,   397,   397,   402,
     413,   402,   404,   419,   402,   407,   407,   407,   402,   410,
     336,    47,   337,    36,    43,    45,    50,    51,    52,    54,
     231,   246,   262,   267,   269,   338,    47,   339,    36,    43,
      45,    47,    50,    51,    52,    54,   231,   246,   262,   267,
     269,   340,    51,   341,    36,    43,    44,    45,    46,    49,
      50,    52,    53,    54,    56,    95,    97,    98,    99,   231,
     246,   251,   252,   253,   254,   262,   267,   269,   270,   342,
     246,   251,   252,   267,   343,    43,    45,    50,    52,    56,
      95,    97,   344,    45,   345,    23,    30,    31,    35,   100,
     101,   102,   103,   106,   108,   112,   116,   122,   138,   143,
     146,   151,   154,   157,   158,   162,   165,   167,   189,   190,
     192,   193,   194,   195,   201,   202,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     231,   276,   277,   295,   299,   300,   311,   312,   323,   326,
     353,   398,   514,   515,   518,   519,   520,   524,   585,   588,
     590,   594,   599,   600,   602,   604,   614,   615,   617,   619,
     621,   623,   627,   629,   631,   633,   635,   637,   639,   641,
     643,   645,   649,   651,   653,   655,   656,   658,   660,   662,
     664,   666,   668,   670,   672,    56,   305,   306,   307,   346,
     352,    56,   347,   352,   101,   348,   349,    87,   238,   240,
     413,   413,   413,   413,     0,   331,   397,   397,    55,   302,
     303,   416,   417,   418,    34,    36,    50,    60,    61,    65,
      76,    77,    78,    79,    80,    81,    95,    97,   207,   231,
     246,   256,   262,   267,   279,   282,   283,   284,   285,   289,
     293,   294,   308,   321,   423,   424,   425,   427,   428,   429,
     430,   431,   432,   436,   437,   438,   441,   442,   449,   453,
     458,   459,   461,   462,   463,   464,   465,   487,   488,   490,
     491,   493,   494,   497,   498,   505,   506,   507,   508,   509,
     512,   513,   519,   526,   527,   528,   529,   530,   531,   535,
     536,   537,   569,   583,   588,   589,   612,   613,   614,   331,
     320,   320,   331,   397,   469,   354,   357,   423,   397,   361,
     363,   514,   537,   366,   397,   370,   404,   420,   413,   402,
     404,   407,   407,   407,   410,    87,   238,   240,   413,   413,
     413,   413,   419,   402,   413,   414,   400,   402,   403,   402,
     404,   405,   420,   402,   407,   408,   407,   407,   402,   410,
     411,    87,   238,   240,   559,   413,   414,   413,   414,   413,
     414,   413,   414,   407,   413,   402,   401,   422,   404,   422,
      43,   422,   407,   407,   422,   410,   422,    43,    44,   407,
     422,   422,    87,   238,   255,   559,   413,    43,   422,    43,
     422,    43,   422,    43,   422,   413,   413,   413,    43,   422,
     413,    43,   422,    43,   422,   413,   402,   404,   407,   407,
     422,    43,   407,   404,   104,   105,   106,   616,   109,   110,
     208,   209,   212,   522,   523,    32,    33,   208,   591,   129,
     525,   163,   164,   654,   109,   110,   111,   618,   111,   113,
     114,   115,   620,   109,   110,   117,   118,   119,   120,   121,
     622,   109,   110,   113,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   172,   624,   111,   113,   131,   139,   140,
     141,   142,   628,   111,   131,   144,   258,   630,   109,   110,
     123,   125,   126,   127,   148,   149,   150,   632,   111,   113,
     131,   139,   140,   142,   152,   153,   634,   124,   140,   149,
     155,   156,   636,   140,   156,   638,   149,   159,   160,   640,
     127,   131,   163,   164,   642,   131,   163,   164,   166,   644,
     131,   140,   155,   159,   163,   164,   168,   169,   170,   171,
     172,   646,   111,   163,   164,   650,   131,   163,   164,   191,
     652,   111,   122,   124,   142,   146,   149,   196,   229,   230,
     312,   601,   603,   659,   197,   661,   197,   663,   159,   198,
     199,   200,   665,   124,   149,   657,   113,   128,   149,   155,
     203,   204,   667,   124,   149,   669,   111,   124,   131,   149,
     155,   671,   101,   127,   130,   147,   269,   286,   312,   586,
     587,   588,   109,   110,   113,   130,   208,   232,   233,   234,
     235,   236,   237,   239,   240,   241,   242,   243,   244,   245,
     248,   249,   250,   269,   605,   606,   609,   286,   296,   593,
     531,   536,   297,   192,   201,   202,   205,   206,   673,   318,
     319,   596,   530,   397,   352,   306,   352,    44,    46,    48,
      49,    56,    57,    89,   350,   413,   413,   413,   554,   568,
     556,   558,   100,   100,   100,    82,   601,   247,   506,   397,
     514,   584,   584,    60,    96,   397,   101,   586,    87,   184,
     238,   605,   606,   247,   247,   263,   247,   265,   266,   450,
      82,    82,   601,     4,   332,   538,   539,   304,   421,   428,
     357,   248,   249,   439,   440,   159,   257,   258,   259,   260,
     261,   443,   444,   280,   460,     5,    21,    68,    82,    84,
     108,   112,   116,   122,   126,   146,   192,   241,   244,   245,
     257,   282,   283,   309,   310,   323,   472,   473,   474,   475,
     476,   477,   478,   480,   481,   482,   483,   484,   485,   486,
     515,   518,   524,   578,   579,   580,   585,   590,   594,   600,
     601,   602,   604,   610,   611,   614,    37,    38,   181,   182,
     466,   467,    82,   286,   287,   288,   489,   495,   496,    82,
     492,   495,   290,   291,   292,   499,   500,   501,   502,    23,
     514,   516,   517,    43,   510,   511,    15,    16,    17,    18,
     325,     8,    24,    52,     9,    10,    11,    12,    13,    14,
     108,   112,   116,   122,   138,   143,   146,   151,   154,   157,
     158,   162,   165,   167,   189,   190,   285,   323,   483,   515,
     517,   518,   532,   533,   534,   537,   570,   571,   572,   573,
     574,   575,   576,   577,   579,   580,   581,   582,    50,    50,
      22,   321,   552,   570,   571,   552,    37,   321,   468,   321,
     321,   321,   321,   321,   416,   423,   469,   354,   357,   361,
     363,   366,   370,   413,   413,   413,   554,   568,   556,   558,
     423,    55,    55,    55,    55,   363,    55,   370,   413,   363,
     402,   407,   422,    43,    43,    43,   413,   402,   402,   402,
     402,   402,   402,   402,   407,   397,     7,     8,   111,   212,
     213,   521,   101,   123,   247,   108,   122,   108,   122,   134,
     135,   136,   137,   625,    23,    37,   100,   170,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   647,   603,
     327,   327,   109,   110,   122,   130,   146,   232,   233,   234,
     607,   608,   609,   297,   297,   100,   315,   595,   324,   351,
     352,   566,   566,   566,   248,   321,   553,   263,   321,   567,
     321,   450,   555,   321,   398,   557,     5,   122,   146,   485,
      82,   485,   503,   504,   531,    23,    23,    94,   321,    50,
      50,    50,   100,   265,    50,   609,    50,   485,   485,   265,
     266,   454,   485,   100,   485,   485,    82,   483,   537,   542,
     543,   550,   576,   577,     7,   322,   398,   321,   100,   100,
     440,    75,   108,   122,   167,   215,   446,   398,   100,   100,
     100,   398,   445,   444,   138,   151,   167,   281,   485,     5,
     485,    82,    82,   477,   515,   580,    15,    16,    17,    18,
     325,    20,    22,     8,    52,     5,   495,    82,    84,   197,
     257,     7,     7,   100,   100,   467,     5,     7,     5,   485,
     485,   500,     7,   397,   321,   397,   321,   511,   581,   581,
     572,   573,   574,   530,   321,   433,   516,   571,   576,     7,
      15,    16,    17,    18,   325,     7,    20,    22,     8,   571,
     485,   485,   100,   322,   331,   331,   100,   385,   356,   358,
     362,   367,   371,   468,   321,   321,   321,   321,   321,   566,
     566,   566,   553,   567,   555,   557,   100,   100,   100,   100,
     100,   321,   566,   402,   402,   402,   100,   523,   111,   127,
     132,   133,   197,   626,   647,    94,   127,   183,   184,   185,
     186,   187,   188,   648,   100,   100,   109,   110,   109,   110,
     100,   100,   298,   592,   100,   156,   314,   597,   601,   321,
     321,   321,   100,   378,   454,   383,   379,   100,   384,   485,
       5,     5,   485,   516,    87,    90,   421,   544,   545,   398,
     398,   100,   531,   540,   541,   485,   485,   485,   100,   485,
      50,   485,   100,   101,   249,   451,    41,   485,   332,     5,
     332,    87,    90,   421,   546,   549,   246,   262,   547,   548,
     332,   539,   359,   145,   140,   145,   447,   448,   111,   111,
      68,   111,   485,     5,   485,   485,   324,   472,   472,   473,
     474,   475,   100,   477,   472,   479,   516,   537,   485,   485,
      82,     8,    82,   515,   580,   610,   610,   485,   496,   485,
     495,   502,   503,   540,   332,   434,   435,   324,   576,   581,
     581,   572,   573,   574,   576,   100,   576,   534,   576,    38,
     331,   322,   331,   333,   421,   468,    36,    45,    50,    52,
      54,   159,   231,   246,   262,   267,   269,   322,   331,   333,
     355,   421,    91,   111,   159,   322,   331,   333,   387,   393,
     394,   421,   423,    39,    86,    87,    88,    89,    91,    94,
     111,   159,   231,   322,   331,   333,   368,   421,   426,   427,
      39,    87,    89,   111,   159,   322,   331,   333,   368,   421,
      40,    42,   246,   322,   331,   333,   356,   358,   362,   367,
     371,   321,   321,   321,   371,     7,     7,   328,   328,   592,
     301,   592,   100,   109,   110,   598,   381,   382,   380,   249,
     322,   331,   333,   421,   553,   100,   322,   331,   333,   421,
     567,   322,   331,   333,   421,   555,   451,   322,   331,   333,
     421,   557,   485,   485,     5,   101,   399,   399,   545,   321,
     428,   544,   485,    20,   101,   268,   452,   485,    41,    79,
      80,   551,   577,   583,   399,   399,   549,   248,   263,   548,
     322,   331,   423,     7,   101,   101,   101,   485,     5,   485,
     161,   485,   495,   495,     5,   322,   426,   428,   542,     7,
     322,   100,    38,   397,   415,   397,   406,   397,   409,   409,
     397,   412,   101,    87,   238,   240,   415,   415,   415,   415,
     331,    76,    77,   395,   396,   514,   101,    96,   331,   331,
     331,   331,   331,   360,   519,   399,   399,   320,    92,    93,
     369,   100,   101,   125,   126,   208,   228,   229,   375,   376,
     386,    83,    84,    85,    87,   364,   365,   331,   331,   331,
     427,   360,   399,   320,   376,   364,   331,   331,   101,   320,
     322,   322,   322,   322,   322,   381,   382,   380,   322,   100,
     100,   100,    91,   130,   232,   322,   331,   333,   421,   564,
      87,    94,   130,   164,   232,   322,   331,   333,   421,   565,
     111,   232,   322,   331,   333,   421,   561,   100,    20,   101,
     452,   485,   540,   322,   274,   275,   276,   277,   278,   457,
     264,   456,   100,   485,   332,   100,   454,   331,   448,   485,
      82,   503,     5,   322,   322,     5,   332,   435,   182,   470,
     100,   377,   357,   361,   366,   370,   415,   415,   415,   377,
     377,   377,   377,    40,     8,   331,   331,   331,   363,     8,
     331,     7,   331,     5,   331,   363,     5,   331,   147,   388,
     321,   372,   514,   322,   322,   322,     7,   592,   320,   162,
     167,   560,   401,   399,   100,   560,   100,   401,   102,   401,
     457,   456,   428,   264,   455,   100,   451,   249,   100,   485,
     322,   503,   583,   181,   471,   331,   321,   321,   321,   321,
     321,   377,   377,   377,   321,   321,   321,   321,   101,   519,
     375,   365,    84,   360,    84,   246,   262,   267,   269,   376,
      22,   100,   101,   319,   389,   390,   391,   514,   331,   101,
     373,   374,   514,   331,   100,   321,   331,   331,   331,   331,
     331,   331,   331,   130,   331,   455,   322,   100,   101,   249,
     100,    20,   101,   322,   332,   470,   385,   358,   362,   367,
     371,   321,   321,   321,   378,   383,   379,   384,    41,    42,
     392,   360,   331,   376,   331,   331,   331,   331,   331,   100,
      22,    25,     7,   322,   101,   562,   563,   560,   248,   457,
     456,   471,   322,   322,   322,   322,   322,   381,   382,   380,
     322,   322,   322,   322,   398,   514,   320,   388,   331,   331,
     100,   100,   332,   374,     5,     7,   322,   331,   455,   331,
     331,   331,   331,   331,   322,   322,   322,   331,   331,   331,
     331,   372,   100,   563,   331,   331,   331,   331
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   329,   330,   330,   331,   331,   332,   332,   333,   333,
     333,   333,   333,   334,   334,   334,   334,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   336,   336,   336,   336,   336,   336,   336,   336,
     336,   336,   336,   336,   336,   336,   336,   336,   336,   336,
     336,   336,   336,   336,   336,   336,   337,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   339,   340,   340,   340,   340,   340,
     340,   340,   340,   340,   340,   340,   340,   340,   340,   340,
     340,   340,   340,   340,   340,   340,   340,   340,   341,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   343,   343,   343,   343,   343,   343,
     344,   344,   344,   344,   344,   344,   344,   345,   346,   346,
     347,   347,   348,   349,   349,   350,   350,   350,   350,   350,
     350,   350,   350,   351,   351,   352,   352,   352,   353,   354,
     355,   355,   356,   356,   356,   356,   356,   356,   356,   356,
     356,   356,   356,   356,   356,   356,   356,   356,   357,   358,
     358,   358,   358,   358,   358,   358,   358,   359,   359,   359,
     360,   360,   361,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   363,   363,   364,   364,
     365,   365,   365,   365,   366,   367,   367,   367,   367,   367,
     367,   367,   367,   367,   367,   367,   367,   367,   367,   367,
     367,   368,   368,   369,   369,   370,   371,   371,   371,   371,
     371,   371,   372,   372,   373,   373,   373,   374,   374,   375,
     375,   376,   376,   377,   378,   378,   378,   378,   378,   379,
     379,   379,   379,   379,   380,   380,   380,   380,   380,   381,
     381,   381,   381,   381,   382,   382,   382,   382,   382,   383,
     383,   383,   383,   383,   384,   384,   384,   384,   384,   385,
     385,   385,   385,   385,   386,   386,   386,   386,   386,   387,
     388,   389,   389,   390,   390,   390,   390,   390,   391,   391,
     392,   392,   392,   392,   393,   394,   395,   395,   396,   396,
     397,   398,   398,   398,   399,   400,   400,   401,   401,   401,
     401,   401,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   419,   419,   419,   420,   421,   422,   422,   423,   423,
     424,   425,   425,   426,   426,   427,   427,   427,   427,   428,
     428,   428,   428,   428,   428,   428,   428,   428,   428,   428,
     428,   428,   428,   428,   428,   428,   428,   428,   428,   429,
     429,   430,   431,   431,   432,   433,   433,   434,   434,   434,
     435,   436,   436,   437,   437,   438,   438,   439,   439,   440,
     440,   441,   441,   442,   443,   443,   444,   444,   444,   444,
     444,   444,   445,   446,   446,   446,   446,   446,   447,   447,
     448,   448,   449,   449,   449,   450,   450,   450,   451,   451,
     452,   452,   453,   453,   454,   454,   454,   455,   455,   456,
     456,   456,   457,   457,   457,   457,   457,   458,   459,   460,
     460,   460,   460,   460,   461,   462,   462,   463,   463,   463,
     463,   463,   463,   464,   464,   465,   465,   466,   466,   467,
     467,   467,   467,   468,   468,   469,   470,   470,   471,   471,
     472,   472,   472,   472,   472,   472,   472,   472,   472,   472,
     472,   472,   472,   473,   473,   473,   474,   474,   475,   475,
     476,   476,   477,   478,   478,   479,   479,   480,   480,   481,
     482,   483,   484,   484,   484,   485,   485,   485,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   487,   487,   488,   489,   489,   489,   490,   490,
     491,   492,   492,   492,   492,   492,   493,   493,   494,   494,
     495,   495,   496,   496,   496,   497,   497,   498,   499,   499,
     500,   500,   501,   501,   502,   502,   503,   503,   504,   505,
     505,   505,   506,   506,   506,   507,   507,   508,   508,   509,
     510,   510,   511,   512,   512,   513,   514,   515,   515,   516,
     516,   517,   518,   519,   519,   519,   519,   519,   519,   519,
     519,   519,   519,   519,   519,   519,   519,   519,   520,   521,
     521,   521,   522,   522,   522,   522,   522,   523,   523,   524,
     524,   525,   525,   526,   526,   526,   527,   527,   528,   528,
     529,   529,   530,   531,   531,   532,   533,   534,   534,   535,
     536,   536,   536,   537,   538,   538,   538,   539,   539,   539,
     540,   540,   541,   542,   542,   543,   543,   544,   544,   545,
     545,   545,   546,   546,   547,   547,   548,   548,   548,   548,
     549,   549,   549,   550,   550,   551,   551,   552,   552,   552,
     552,   553,   554,   555,   556,   557,   558,   559,   559,   559,
     560,   560,   561,   561,   562,   562,   563,   564,   564,   564,
     565,   565,   565,   565,   565,   566,   567,   567,   568,   569,
     569,   569,   570,   570,   571,   571,   571,   571,   572,   572,
     572,   573,   573,   574,   574,   575,   575,   576,   577,   577,
     577,   577,   578,   578,   579,   580,   580,   580,   580,   580,
     580,   580,   580,   580,   580,   580,   580,   581,   581,   581,
     581,   581,   581,   581,   581,   581,   581,   581,   581,   581,
     581,   581,   581,   581,   582,   582,   582,   582,   582,   582,
     583,   583,   583,   583,   583,   583,   584,   584,   585,   585,
     585,   586,   586,   587,   587,   587,   587,   587,   588,   588,
     588,   588,   588,   588,   588,   588,   588,   588,   588,   588,
     588,   588,   588,   588,   588,   588,   588,   588,   588,   588,
     588,   588,   589,   589,   589,   589,   589,   589,   590,   591,
     591,   591,   592,   592,   593,   593,   594,   595,   595,   596,
     596,   597,   597,   598,   598,   599,   599,   600,   600,   600,
     601,   601,   602,   602,   603,   603,   603,   603,   604,   604,
     604,   605,   605,   606,   606,   606,   606,   606,   606,   606,
     606,   606,   606,   606,   606,   606,   606,   606,   606,   606,
     607,   607,   607,   607,   607,   607,   607,   608,   608,   608,
     608,   609,   609,   609,   609,   610,   610,   611,   611,   612,
     612,   612,   612,   613,   614,   614,   614,   614,   614,   614,
     614,   614,   614,   614,   614,   614,   614,   614,   614,   614,
     614,   614,   615,   616,   616,   616,   617,   618,   618,   618,
     619,   620,   620,   620,   620,   621,   622,   622,   622,   622,
     622,   622,   622,   622,   622,   623,   623,   623,   624,   624,
     624,   624,   624,   624,   624,   624,   624,   624,   624,   624,
     625,   625,   625,   625,   626,   626,   626,   626,   626,   627,
     628,   628,   628,   628,   628,   628,   628,   629,   630,   630,
     630,   630,   631,   632,   632,   632,   632,   632,   632,   632,
     632,   632,   633,   634,   634,   634,   634,   634,   634,   634,
     634,   635,   636,   636,   636,   636,   636,   637,   638,   638,
     639,   640,   640,   640,   641,   642,   642,   642,   642,   643,
     644,   644,   644,   644,   645,   645,   645,   645,   646,   646,
     646,   646,   646,   646,   646,   646,   646,   646,   647,   647,
     647,   647,   647,   647,   647,   647,   647,   647,   647,   647,
     647,   648,   648,   648,   648,   648,   648,   648,   648,   649,
     650,   650,   650,   651,   652,   652,   652,   652,   653,   654,
     654,   655,   655,   655,   655,   655,   655,   655,   655,   656,
     657,   657,   658,   659,   659,   659,   659,   660,   661,   662,
     663,   664,   665,   665,   665,   665,   666,   667,   667,   667,
     667,   667,   667,   668,   669,   669,   670,   671,   671,   671,
     671,   671,   672,   673,   673,   673,   673,   673
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
       1,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     1,     1,     3,     3,     1,     1,     3,     3,
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
       1,     1,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     1,     1,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     3,     4,     5,     2,     3,     2,     6,     4,     3,
       4,     3,     2,     1,     1,     3,     4,     1,     2,     1,
       1,     2,     3,     1,     3,     4,     3,     5,     3,     6,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     2,
       2,     1,     1,     3,     1,     1,     1,     2,     1,     4,
       5,     6,     1,     1,     1,     7,     8,     6,     1,     1,
       1,     2,     2,     6,     8,     1,     2,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       3,     0,     2,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     3,     3,     1,     1,     3,
       1,     1,     1,     3,     1,     3,     3,     3,     3,     5,
       1,     2,     1,     1,     2,     2,     1,     1,     2,     2,
       2,     1,     1,     2,     1,     2,     1,     5,     7,     6,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     4,     0,     4,     0,     1,     0,     1,     1,     1,
       1,     1,     5,     3,     1,     3,     3,     3,     6,     3,
       3,     3,     3,     3,     3,     0,     6,     5,     0,     2,
       2,     3,     3,     3,     1,     1,     1,     1,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     3,     4,     1,     4,     4,     2,     1,
       1,     1,     0,     2,     1,     1,     5,     2,     0,     1,
       1,     1,     1,     1,     1,     4,     5,     7,     5,     4,
       1,     1,     2,     3,     1,     1,     1,     1,     2,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     4,
       4,     4,     5,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     6,     1,     1,     1,     2,     1,     1,     1,
       2,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     4,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     1,     1,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     2,     4,     3,     8,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     2,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     1,     1,     1,     1,     2,     4,     2,
       1,     2,     1,     1,     1,     4,     2,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1
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
#line 311 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4505 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 102: /* "quoted string"  */
#line 311 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4511 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 103: /* "string with a trailing asterisk"  */
#line 311 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4517 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 334: /* line  */
#line 586 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4523 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* base_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4529 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 336: /* add_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4535 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* replace_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4541 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* create_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4547 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* insert_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4553 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* delete_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4559 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* get_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4565 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* list_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4571 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* reset_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4577 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* flush_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4583 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 345: /* rename_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4589 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* import_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4595 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* export_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4601 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 348: /* monitor_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4607 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 349: /* monitor_event  */
#line 812 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4613 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 353: /* describe_cmd  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4619 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* table_block_alloc  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 4625 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 357: /* chain_block_alloc  */
#line 607 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 4631 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* typeof_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4637 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* set_block_alloc  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4643 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 363: /* set_block_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4649 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 366: /* map_block_alloc  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4655 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 370: /* flowtable_block_alloc  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 4661 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 372: /* flowtable_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4667 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* flowtable_list_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4673 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 374: /* flowtable_expr_member  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4679 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* data_type_atom_expr  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4685 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* data_type_expr  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4691 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* obj_block_alloc  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4697 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* type_identifier  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4703 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* extended_prio_name  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4709 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* dev_spec  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).expr)); }
#line 4715 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* policy_expr  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4721 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* identifier  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4727 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* string  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4733 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* table_spec  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4739 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* tableid_spec  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4745 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* chain_spec  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4751 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* chainid_spec  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4757 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* chain_identifier  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4763 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* set_spec  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4769 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* setid_spec  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4775 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* set_identifier  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4781 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* flowtable_spec  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4787 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* flowtableid_spec  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4793 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* obj_spec  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4799 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* objid_spec  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4805 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* obj_identifier  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4811 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* handle_spec  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4817 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* position_spec  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4823 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* index_spec  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4829 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* rule_position  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4835 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* ruleid_spec  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4841 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* comment_spec  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4847 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* ruleset_spec  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4853 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* rule  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 4859 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* stmt_list  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 4865 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* stateful_stmt_list  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 4871 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* stateful_stmt  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4877 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* stmt  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4883 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* chain_stmt  */
#line 655 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4889 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* verdict_stmt  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4895 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 432: /* verdict_map_stmt  */
#line 711 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4901 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* verdict_map_expr  */
#line 714 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4907 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* verdict_map_list_expr  */
#line 714 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4913 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* verdict_map_list_member_expr  */
#line 714 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4919 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 436: /* connlimit_stmt  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4925 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* counter_stmt  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4931 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* counter_stmt_alloc  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4937 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 441: /* log_stmt  */
#line 640 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4943 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* log_stmt_alloc  */
#line 640 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4949 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 449: /* limit_stmt  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4955 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* quota_unit  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4961 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 453: /* quota_stmt  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4967 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* reject_stmt  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4973 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* reject_stmt_alloc  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4979 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* nat_stmt  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4985 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* nat_stmt_alloc  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4991 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 463: /* tproxy_stmt  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4997 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* synproxy_stmt  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5003 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* synproxy_stmt_alloc  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5009 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* synproxy_obj  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5015 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* primary_stmt_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5021 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* shift_stmt_expr  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5027 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* and_stmt_expr  */
#line 702 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5033 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* exclusive_or_stmt_expr  */
#line 702 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5039 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* inclusive_or_stmt_expr  */
#line 702 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5045 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* basic_stmt_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5051 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* concat_stmt_expr  */
#line 690 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5057 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* map_stmt_expr_set  */
#line 690 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5063 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* map_stmt_expr  */
#line 690 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5069 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* prefix_stmt_expr  */
#line 695 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5075 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* range_stmt_expr  */
#line 695 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5081 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 483: /* wildcard_expr  */
#line 695 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5087 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* multiton_stmt_expr  */
#line 693 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5093 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* stmt_expr  */
#line 690 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5099 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* masq_stmt  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5105 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* masq_stmt_alloc  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5111 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 490: /* redir_stmt  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5117 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 491: /* redir_stmt_alloc  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5123 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 493: /* dup_stmt  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5129 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* fwd_stmt  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5135 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 497: /* queue_stmt  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5141 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 498: /* queue_stmt_alloc  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5147 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 503: /* set_elem_expr_stmt  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5153 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 504: /* set_elem_expr_stmt_alloc  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5159 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* set_stmt  */
#line 666 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5165 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* map_stmt  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5171 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 508: /* meter_stmt  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5177 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 509: /* flow_stmt_legacy_alloc  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5183 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 512: /* meter_stmt_alloc  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5189 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* match_stmt  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5195 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 514: /* variable_expr  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5201 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 515: /* symbol_expr  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5207 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 516: /* set_ref_expr  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5213 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* set_ref_symbol_expr  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5219 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* integer_expr  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5225 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* primary_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5231 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 520: /* fib_expr  */
#line 803 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5237 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 524: /* osf_expr  */
#line 808 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5243 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 526: /* shift_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5249 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 527: /* and_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5255 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* exclusive_or_expr  */
#line 678 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5261 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* inclusive_or_expr  */
#line 678 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5267 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* basic_expr  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5273 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* concat_expr  */
#line 705 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5279 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* prefix_rhs_expr  */
#line 687 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5285 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* range_rhs_expr  */
#line 687 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5291 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* multiton_rhs_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5297 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* map_expr  */
#line 708 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5303 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* expr  */
#line 727 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5309 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 537: /* set_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5315 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* set_list_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5321 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* set_list_member_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5327 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* meter_key_expr  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5333 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* meter_key_expr_alloc  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5339 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 542: /* set_elem_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5345 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* set_elem_expr_alloc  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5351 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* set_elem_stmt_list  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 5357 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 548: /* set_elem_stmt  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5363 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 550: /* set_lhs_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5369 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* set_rhs_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5375 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 552: /* initializer_expr  */
#line 727 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5381 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 554: /* counter_obj  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5387 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 556: /* quota_obj  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5393 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 558: /* secmark_obj  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5399 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 562: /* timeout_states  */
#line 833 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5405 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 563: /* timeout_state  */
#line 833 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5411 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 566: /* ct_obj_alloc  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5417 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 568: /* limit_obj  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5423 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 569: /* relational_expr  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5429 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 570: /* list_rhs_expr  */
#line 732 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5435 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 571: /* rhs_expr  */
#line 730 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5441 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 572: /* shift_rhs_expr  */
#line 732 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5447 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 573: /* and_rhs_expr  */
#line 734 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5453 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 574: /* exclusive_or_rhs_expr  */
#line 734 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5459 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 575: /* inclusive_or_rhs_expr  */
#line 734 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5465 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 576: /* basic_rhs_expr  */
#line 730 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5471 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 577: /* concat_rhs_expr  */
#line 730 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5477 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 579: /* boolean_expr  */
#line 823 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5483 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 580: /* keyword_expr  */
#line 727 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5489 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 581: /* primary_rhs_expr  */
#line 732 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5495 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 583: /* verdict_expr  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5501 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 584: /* chain_expr  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5507 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 585: /* meta_expr  */
#line 785 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5513 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 589: /* meta_stmt  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5519 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 590: /* socket_expr  */
#line 789 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5525 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 594: /* numgen_expr  */
#line 753 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5531 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 599: /* xfrm_expr  */
#line 837 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5537 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 600: /* hash_expr  */
#line 753 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5543 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 602: /* rt_expr  */
#line 795 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5549 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 604: /* ct_expr  */
#line 799 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5555 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 610: /* symbol_stmt_expr  */
#line 732 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5561 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 611: /* list_stmt_expr  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5567 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 612: /* ct_stmt  */
#line 636 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5573 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 613: /* payload_stmt  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5579 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 614: /* payload_expr  */
#line 744 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5585 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 615: /* payload_raw_expr  */
#line 744 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5591 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 617: /* eth_hdr_expr  */
#line 747 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5597 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 619: /* vlan_hdr_expr  */
#line 747 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5603 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 621: /* arp_hdr_expr  */
#line 750 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5609 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 623: /* ip_hdr_expr  */
#line 753 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5615 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 627: /* icmp_hdr_expr  */
#line 753 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5621 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 629: /* igmp_hdr_expr  */
#line 753 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5627 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 631: /* ip6_hdr_expr  */
#line 757 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5633 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 633: /* icmp6_hdr_expr  */
#line 757 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5639 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 635: /* auth_hdr_expr  */
#line 760 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5645 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 637: /* esp_hdr_expr  */
#line 760 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5651 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 639: /* comp_hdr_expr  */
#line 760 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5657 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 641: /* udp_hdr_expr  */
#line 763 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5663 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 643: /* udplite_hdr_expr  */
#line 763 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5669 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 645: /* tcp_hdr_expr  */
#line 818 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5675 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 649: /* dccp_hdr_expr  */
#line 766 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5681 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 651: /* sctp_hdr_expr  */
#line 766 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5687 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 653: /* th_hdr_expr  */
#line 769 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5693 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 655: /* exthdr_expr  */
#line 773 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5699 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 656: /* hbh_hdr_expr  */
#line 775 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5705 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 658: /* rt_hdr_expr  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5711 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 660: /* rt0_hdr_expr  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5717 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 662: /* rt2_hdr_expr  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5723 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 664: /* rt4_hdr_expr  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5729 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 666: /* frag_hdr_expr  */
#line 775 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5735 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 668: /* dst_hdr_expr  */
#line 775 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5741 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 670: /* mh_hdr_expr  */
#line 781 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5747 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 672: /* exthdr_exists_expr  */
#line 827 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5753 "parser_bison.c" /* yacc.c:1257  */
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

#line 5869 "parser_bison.c" /* yacc.c:1431  */
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
#line 843 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 6068 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 8:
#line 860 "parser_bison.y" /* yacc.c:1652  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 6080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 9:
#line 868 "parser_bison.y" /* yacc.c:1652  */
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
#line 6099 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 10:
#line 883 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 6110 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 11:
#line 890 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 6125 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 12:
#line 901 "parser_bison.y" /* yacc.c:1652  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 6135 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 13:
#line 908 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 6141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 14:
#line 909 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 6147 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 15:
#line 910 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 6153 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 16:
#line 912 "parser_bison.y" /* yacc.c:1652  */
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
#line 6175 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 17:
#line 931 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6181 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 18:
#line 932 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 19:
#line 933 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6193 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 20:
#line 934 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6199 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 21:
#line 935 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6205 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 22:
#line 936 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6211 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 23:
#line 937 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6217 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 24:
#line 938 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6223 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 25:
#line 939 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6229 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 26:
#line 940 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6235 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 27:
#line 941 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6241 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 28:
#line 942 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6247 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 29:
#line 943 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6253 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 30:
#line 944 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6259 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 31:
#line 945 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6265 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 32:
#line 949 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 33:
#line 954 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6283 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 34:
#line 960 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6291 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 35:
#line 965 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6302 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 36:
#line 972 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6310 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 37:
#line 976 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6318 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 38:
#line 981 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6328 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 39:
#line 988 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6338 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 40:
#line 994 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6346 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 41:
#line 999 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6356 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 42:
#line 1005 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 6369 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 43:
#line 1014 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6377 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 44:
#line 1018 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 45:
#line 1022 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 46:
#line 1026 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6401 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 47:
#line 1030 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 48:
#line 1034 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 49:
#line 1038 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 50:
#line 1042 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 51:
#line 1046 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 52:
#line 1050 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6449 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 53:
#line 1054 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 54:
#line 1058 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6465 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 55:
#line 1062 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 56:
#line 1068 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6481 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 57:
#line 1074 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6489 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 58:
#line 1079 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6499 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 59:
#line 1085 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6507 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 60:
#line 1090 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6518 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 61:
#line 1098 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 62:
#line 1105 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 63:
#line 1111 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6546 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 64:
#line 1116 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6556 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 65:
#line 1122 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 6569 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 66:
#line 1131 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 67:
#line 1135 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 68:
#line 1139 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6593 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 69:
#line 1143 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6601 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 70:
#line 1147 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6609 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 71:
#line 1151 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6617 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 72:
#line 1155 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 73:
#line 1159 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6633 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 74:
#line 1165 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 75:
#line 1171 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6649 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 76:
#line 1175 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6657 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 77:
#line 1179 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6665 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 78:
#line 1183 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6673 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 79:
#line 1187 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6681 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 80:
#line 1191 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6689 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 81:
#line 1195 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6697 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 82:
#line 1199 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6705 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 83:
#line 1203 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6713 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 84:
#line 1207 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6721 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 85:
#line 1211 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6729 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 86:
#line 1216 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6739 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 87:
#line 1222 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6747 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 88:
#line 1226 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6755 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 89:
#line 1230 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6763 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 90:
#line 1234 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6771 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 91:
#line 1238 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 92:
#line 1242 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6787 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 93:
#line 1246 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6795 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 94:
#line 1250 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6803 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 95:
#line 1254 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6811 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 96:
#line 1258 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6819 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 97:
#line 1262 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6827 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 98:
#line 1268 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6835 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 99:
#line 1274 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 100:
#line 1278 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6851 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 101:
#line 1282 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6859 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 102:
#line 1286 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6867 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 103:
#line 1290 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6875 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 104:
#line 1294 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6883 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 105:
#line 1298 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6891 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1302 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6899 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1306 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6907 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1310 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6915 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1314 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6923 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1318 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1322 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6939 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1326 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6947 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1330 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6955 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1334 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6963 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 115:
#line 1338 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 116:
#line 1342 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6979 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 117:
#line 1346 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6987 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 118:
#line 1350 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 119:
#line 1354 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7003 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1358 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7011 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1362 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7019 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1366 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7027 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1370 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7035 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1374 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7043 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1378 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7051 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1382 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7059 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1386 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7067 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1390 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7075 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1394 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7083 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1398 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7091 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1402 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7099 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1406 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_TIMEOUT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1410 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_EXPECT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7115 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1416 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1420 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7131 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1424 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 7139 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1428 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7147 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 138:
#line 1432 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7155 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 139:
#line 1436 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7163 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 140:
#line 1442 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7171 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 141:
#line 1446 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1450 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1454 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1458 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7203 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 145:
#line 1462 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7211 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 146:
#line 1466 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7219 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 147:
#line 1472 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 7228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 148:
#line 1479 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7238 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 149:
#line 1485 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7248 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 150:
#line 1493 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7258 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 151:
#line 1499 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7268 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 152:
#line 1507 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 7279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 153:
#line 1515 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = NULL; }
#line 7285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1516 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7291 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1519 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 7297 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1520 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 7303 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 157:
#line 1521 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 7309 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 158:
#line 1522 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 7315 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 159:
#line 1523 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 7321 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1524 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 7327 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1525 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 7333 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1526 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 7339 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1529 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 7345 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1533 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 7351 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 166:
#line 1534 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7357 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 167:
#line 1535 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 168:
#line 1539 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 7373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 169:
#line 1547 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 7382 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1554 "parser_bison.y" /* yacc.c:1652  */
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
#line 7398 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1566 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].table)->comment, &(yyloc), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].table)->comment = (yyvsp[0].string);
			}
#line 7410 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1575 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 7416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 176:
#line 1582 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7429 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 177:
#line 1593 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 178:
#line 1603 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 179:
#line 1614 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7465 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 180:
#line 1624 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7478 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 181:
#line 1635 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7491 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 182:
#line 1644 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 183:
#line 1653 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7517 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 184:
#line 1662 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7530 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 185:
#line 1673 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 186:
#line 1684 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7556 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 187:
#line 1695 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7569 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 188:
#line 1706 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 7578 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 189:
#line 1712 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7584 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 195:
#line 1719 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 7593 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 196:
#line 1724 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].chain)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].chain)->comment = (yyvsp[-1].string);
			}
#line 7605 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 197:
#line 1733 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7611 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 199:
#line 1736 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 7620 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 200:
#line 1743 "parser_bison.y" /* yacc.c:1652  */
    {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 7635 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 201:
#line 1754 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 7648 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 202:
#line 1766 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7656 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 203:
#line 1771 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7662 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 206:
#line 1775 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7671 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 207:
#line 1780 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7681 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 208:
#line 1786 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7690 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 209:
#line 1791 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7699 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 210:
#line 1796 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 211:
#line 1801 "parser_bison.y" /* yacc.c:1652  */
    {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 7718 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 212:
#line 1807 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7727 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 213:
#line 1812 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 7736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 215:
#line 1818 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 7749 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 218:
#line 1833 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7757 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 220:
#line 1839 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 7763 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 221:
#line 1840 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 7769 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 222:
#line 1841 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 7775 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 223:
#line 1842 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_EVAL; }
#line 7781 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 224:
#line 1846 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7789 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 225:
#line 1851 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7795 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 228:
#line 1855 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7804 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 229:
#line 1862 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7816 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 230:
#line 1872 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 7829 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 231:
#line 1883 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7842 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 232:
#line 1894 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				datatype_set((yyvsp[-6].set)->key, (yyvsp[-4].expr)->dtype);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 7856 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 233:
#line 1906 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7867 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 234:
#line 1915 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7878 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 235:
#line 1924 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7889 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 236:
#line 1933 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_SECMARK;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7900 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 237:
#line 1940 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7909 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 238:
#line 1945 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7918 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 239:
#line 1950 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 7931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 241:
#line 1962 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 7939 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 242:
#line 1966 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 7947 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 243:
#line 1971 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 7953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 244:
#line 1972 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 7959 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 245:
#line 1976 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 7967 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 246:
#line 1981 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 7973 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 249:
#line 1985 "parser_bison.y" /* yacc.c:1652  */
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
#line 7991 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 250:
#line 1999 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 7999 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 251:
#line 2003 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 8007 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 252:
#line 2009 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8016 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 253:
#line 2014 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8025 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 254:
#line 2021 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8034 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 255:
#line 2026 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8043 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 257:
#line 2034 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 8054 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 258:
#line 2041 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8063 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 259:
#line 2048 "parser_bison.y" /* yacc.c:1652  */
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
#line 8079 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 260:
#line 2060 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 8088 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 262:
#line 2068 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 8101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 263:
#line 2079 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 8109 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 264:
#line 2084 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8115 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 267:
#line 2088 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 268:
#line 2092 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8135 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 269:
#line 2101 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 272:
#line 2105 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8149 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 273:
#line 2109 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 274:
#line 2118 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 277:
#line 2122 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8175 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 278:
#line 2126 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 279:
#line 2136 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[(-1) - (0)].obj);
				init_list_head(&(yyval.obj)->ct_timeout.timeout_list);
			}
#line 8196 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 282:
#line 2143 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 283:
#line 2147 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8216 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 284:
#line 2156 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8222 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 287:
#line 2160 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8230 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 288:
#line 2164 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8242 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 289:
#line 2173 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8248 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 292:
#line 2177 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8256 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 293:
#line 2181 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8268 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 294:
#line 2190 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 297:
#line 2194 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 298:
#line 2198 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8294 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 299:
#line 2207 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8300 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 302:
#line 2211 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8308 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 303:
#line 2215 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8320 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 304:
#line 2224 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 8326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 305:
#line 2225 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("mark"); }
#line 8332 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 306:
#line 2226 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("dscp"); }
#line 8338 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 307:
#line 2227 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("ecn"); }
#line 8344 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 308:
#line 2228 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("classid"); }
#line 8350 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 309:
#line 2232 "parser_bison.y" /* yacc.c:1652  */
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
#line 8382 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 310:
#line 2262 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 8391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 311:
#line 2269 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.string) = strdup("out");
			}
#line 8399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 313:
#line 2276 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 8413 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 314:
#line 2286 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 8424 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 315:
#line 2293 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 8439 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 316:
#line 2304 "parser_bison.y" /* yacc.c:1652  */
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
#line 8456 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 317:
#line 2317 "parser_bison.y" /* yacc.c:1652  */
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
#line 8473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 318:
#line 2331 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = (yyvsp[0].val); }
#line 8479 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 319:
#line 2332 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = -(yyvsp[0].val); }
#line 8485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 320:
#line 2336 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 8501 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 321:
#line 2348 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8511 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 322:
#line 2354 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8519 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 323:
#line 2357 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = NULL; }
#line 8525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 324:
#line 2361 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 8533 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 325:
#line 2367 "parser_bison.y" /* yacc.c:1652  */
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
#line 8548 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 326:
#line 2380 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8557 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 327:
#line 2385 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 8568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 328:
#line 2393 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_ACCEPT; }
#line 8574 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 329:
#line 2394 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_DROP;   }
#line 8580 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 334:
#line 2406 "parser_bison.y" /* yacc.c:1652  */
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
#line 8597 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 335:
#line 2420 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 337:
#line 2424 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8609 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 338:
#line 2425 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 8615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 339:
#line 2426 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_INET; }
#line 8621 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 340:
#line 2427 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_ARP; }
#line 8627 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 341:
#line 2428 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 8633 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 342:
#line 2429 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 8639 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 343:
#line 2433 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 8650 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 344:
#line 2442 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 8661 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 345:
#line 2451 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 8671 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 346:
#line 2459 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 8681 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 347:
#line 2467 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 8691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 348:
#line 2475 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 8701 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 349:
#line 2483 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 8711 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 350:
#line 2491 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 8721 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 351:
#line 2499 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 8731 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 352:
#line 2507 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8741 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 353:
#line 2515 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 8751 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 354:
#line 2523 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 8761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 355:
#line 2531 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8771 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 356:
#line 2539 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 8781 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 357:
#line 2547 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 8791 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 358:
#line 2555 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 8801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 359:
#line 2563 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 8811 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 360:
#line 2571 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 8819 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 361:
#line 2575 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8828 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 362:
#line 2580 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8840 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 363:
#line 2588 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 364:
#line 2595 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 8858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 365:
#line 2602 "parser_bison.y" /* yacc.c:1652  */
    {
				if (strlen((yyvsp[0].string)) > NFTNL_UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed",
							 NFTNL_UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 8872 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 366:
#line 2614 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 8881 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 367:
#line 2619 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 8890 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 368:
#line 2626 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 8898 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 369:
#line 2630 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 8906 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 370:
#line 2636 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 8920 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 371:
#line 2648 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 8930 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 372:
#line 2654 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 8939 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 373:
#line 2661 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 8949 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 374:
#line 2667 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 8958 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 399:
#line 2701 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_JUMP; }
#line 8964 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 400:
#line 2702 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_GOTO; }
#line 8970 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 401:
#line 2706 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].chain)->location = (yylsp[-3]);
				close_scope(state);
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				(yyval.stmt) = chain_stmt_alloc(&(yyloc), (yyvsp[-1].chain), (yyvsp[-4].val));
			}
#line 8981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 402:
#line 2715 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8989 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 403:
#line 2719 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8997 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 404:
#line 2725 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9005 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 405:
#line 2731 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9014 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 407:
#line 2739 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9023 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 408:
#line 2744 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 410:
#line 2752 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 9040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 411:
#line 2758 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[0].val);
			}
#line 9049 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 412:
#line 2763 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[0].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 9059 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 415:
#line 2774 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 9067 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 416:
#line 2778 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9077 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 417:
#line 2786 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9085 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 419:
#line 2793 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 9093 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 420:
#line 2797 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 9101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 423:
#line 2807 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 9109 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 424:
#line 2813 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9117 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 426:
#line 2820 "parser_bison.y" /* yacc.c:1652  */
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
#line 9246 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 427:
#line 2945 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 9255 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 428:
#line 2950 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 9264 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 429:
#line 2955 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 9273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 430:
#line 2960 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 9282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 431:
#line 2965 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 9290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 432:
#line 2971 "parser_bison.y" /* yacc.c:1652  */
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
#line 9322 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 433:
#line 3001 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 9330 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 434:
#line 3005 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 9338 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 435:
#line 3009 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 9346 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 436:
#line 3013 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 9354 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 437:
#line 3017 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 9362 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 438:
#line 3023 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9370 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 440:
#line 3030 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 9378 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 441:
#line 3034 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 9386 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 442:
#line 3040 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].val) == 0) {
					erec_queue(error(&(yylsp[0]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 9404 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 443:
#line 3054 "parser_bison.y" /* yacc.c:1652  */
    {
				struct error_record *erec;
				uint64_t rate, unit;

				if ((yyvsp[0].val) == 0) {
					erec_queue(error(&(yylsp[0]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}

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
#line 9433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 444:
#line 3079 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9443 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 445:
#line 3086 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 9449 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 446:
#line 3087 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9455 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 447:
#line 3088 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9461 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 448:
#line 3091 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("bytes"); }
#line 9467 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 449:
#line 3092 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 9473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 450:
#line 3095 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9479 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 451:
#line 3097 "parser_bison.y" /* yacc.c:1652  */
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
#line 9496 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 452:
#line 3112 "parser_bison.y" /* yacc.c:1652  */
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
#line 9516 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 453:
#line 3128 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9526 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 454:
#line 3135 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 9532 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 455:
#line 3136 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 456:
#line 3137 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9544 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 457:
#line 3140 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 5; }
#line 9550 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 458:
#line 3141 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 9556 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 459:
#line 3144 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 5; }
#line 9562 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 460:
#line 3145 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 9568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 461:
#line 3147 "parser_bison.y" /* yacc.c:1652  */
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
#line 9585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 462:
#line 3161 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL; }
#line 9591 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 463:
#line 3162 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60; }
#line 9597 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 464:
#line 3163 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 9603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 465:
#line 3164 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 9609 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 466:
#line 3165 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 9615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 468:
#line 3172 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 9623 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 469:
#line 3178 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 9632 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 470:
#line 3183 "parser_bison.y" /* yacc.c:1652  */
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
#line 9647 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 471:
#line 3194 "parser_bison.y" /* yacc.c:1652  */
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
#line 9662 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 472:
#line 3205 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpx_code_type);
				xfree((yyvsp[0].string));
			}
#line 9676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 473:
#line 3215 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 9684 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 475:
#line 3223 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 9690 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 476:
#line 3224 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 9696 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 477:
#line 3228 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 9706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 478:
#line 3234 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 9716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 479:
#line 3240 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9726 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 480:
#line 3246 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 481:
#line 3253 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 482:
#line 3260 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 9758 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 485:
#line 3272 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 9766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 486:
#line 3276 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9776 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 487:
#line 3284 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 489:
#line 3291 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 9793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 490:
#line 3296 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 9802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 491:
#line 3301 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 9810 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 492:
#line 3305 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 9818 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 493:
#line 3311 "parser_bison.y" /* yacc.c:1652  */
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
#line 9838 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 494:
#line 3327 "parser_bison.y" /* yacc.c:1652  */
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
#line 9858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 495:
#line 3345 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 9867 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 496:
#line 3351 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9873 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 497:
#line 3353 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 9881 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 498:
#line 3358 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9887 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 499:
#line 3360 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 9895 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 500:
#line 3365 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9901 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 501:
#line 3366 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9907 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 502:
#line 3367 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9913 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 503:
#line 3368 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9919 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 504:
#line 3369 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9925 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 505:
#line 3370 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 506:
#line 3371 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9937 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 507:
#line 3372 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9943 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 508:
#line 3373 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9949 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 509:
#line 3374 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9955 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 510:
#line 3375 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9961 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 511:
#line 3376 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9967 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 512:
#line 3377 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 9973 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 514:
#line 3382 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 515:
#line 3386 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9989 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 517:
#line 3393 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9997 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 519:
#line 3400 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10005 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 521:
#line 3407 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10013 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 524:
#line 3417 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10026 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 527:
#line 3432 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10034 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 528:
#line 3435 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 529:
#line 3439 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 10048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 530:
#line 3445 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 531:
#line 3451 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 10069 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 538:
#line 3472 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10077 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 539:
#line 3476 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10085 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 540:
#line 3480 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10094 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 541:
#line 3485 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10103 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 542:
#line 3490 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10112 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 543:
#line 3495 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10122 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 544:
#line 3501 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10130 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 545:
#line 3505 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10138 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 546:
#line 3509 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10146 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 547:
#line 3513 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.type_flags = STMT_NAT_F_CONCAT;
			}
#line 10156 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 548:
#line 3519 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags = STMT_NAT_F_INTERVAL;
			}
#line 10166 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 549:
#line 3525 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags = STMT_NAT_F_INTERVAL;
			}
#line 10175 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 550:
#line 3530 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX |
						STMT_NAT_F_INTERVAL;
				(yyvsp[-4].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 10188 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 551:
#line 3539 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX |
						STMT_NAT_F_INTERVAL;
				(yyvsp[-3].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 10200 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 554:
#line 3552 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 10206 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 555:
#line 3556 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10214 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 556:
#line 3560 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10223 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 557:
#line 3565 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10231 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 560:
#line 3574 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 10237 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 561:
#line 3578 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10245 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 562:
#line 3582 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10253 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 563:
#line 3586 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10261 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 564:
#line 3590 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10270 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 565:
#line 3595 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 566:
#line 3602 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 10288 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 567:
#line 3607 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 10298 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 568:
#line 3615 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 10307 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 569:
#line 3620 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 10318 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 571:
#line 3630 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 572:
#line 3635 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 10332 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 573:
#line 3636 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 10338 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 574:
#line 3637 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 10344 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 577:
#line 3645 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 10352 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 578:
#line 3651 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10360 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 580:
#line 3658 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 10369 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 581:
#line 3663 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 10377 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 583:
#line 3670 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 584:
#line 3675 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 10391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 585:
#line 3676 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 10397 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 588:
#line 3684 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10405 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 589:
#line 3690 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 10416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 590:
#line 3697 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 10427 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 591:
#line 3704 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				list_splice_tail((yyvsp[-1].list), &(yyval.stmt)->set.stmt_list);
				free((yyvsp[-1].list));
			}
#line 10440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 592:
#line 3714 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 10446 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 593:
#line 3715 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 10452 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 594:
#line 3716 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 10458 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 595:
#line 3720 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 10470 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 596:
#line 3728 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
				list_splice_tail((yyvsp[-3].list), &(yyval.stmt)->map.stmt_list);
				free((yyvsp[-3].list));
			}
#line 10484 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 597:
#line 3740 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 10495 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 598:
#line 3746 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 10501 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 599:
#line 3750 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 10509 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 600:
#line 3756 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10517 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 602:
#line 3763 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 10525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 603:
#line 3769 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 10538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 604:
#line 3778 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 10551 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 605:
#line 3789 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 10559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 606:
#line 3795 "parser_bison.y" /* yacc.c:1652  */
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
#line 10587 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 608:
#line 3822 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10598 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 611:
#line 3835 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10609 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 612:
#line 3844 "parser_bison.y" /* yacc.c:1652  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 10622 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 613:
#line 3854 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10628 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 614:
#line 3855 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10634 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 615:
#line 3856 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10640 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 616:
#line 3857 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10646 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 617:
#line 3858 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10652 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 618:
#line 3859 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10658 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 619:
#line 3860 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10664 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 620:
#line 3861 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10670 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 621:
#line 3862 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 622:
#line 3863 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 623:
#line 3864 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 624:
#line 3865 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 625:
#line 3866 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10700 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 626:
#line 3867 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 627:
#line 3868 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 10712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 628:
#line 3872 "parser_bison.y" /* yacc.c:1652  */
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
#line 10737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 629:
#line 3894 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 10743 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 630:
#line 3895 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 10749 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 631:
#line 3896 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 10755 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 632:
#line 3899 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 10761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 633:
#line 3900 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 10767 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 634:
#line 3901 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 10773 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 635:
#line 3902 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 10779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 636:
#line 3903 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 10785 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 637:
#line 3907 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 639:
#line 3914 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), NFT_OSF_F_VERSION);
			}
#line 10801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 640:
#line 3918 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 10809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 641:
#line 3924 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 10817 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 642:
#line 3928 "parser_bison.y" /* yacc.c:1652  */
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
#line 10833 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 644:
#line 3943 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10841 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 645:
#line 3947 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 647:
#line 3954 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10857 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 649:
#line 3961 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10865 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 651:
#line 3968 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10873 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 654:
#line 3978 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10886 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 655:
#line 3989 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 10894 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 656:
#line 3995 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10902 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 659:
#line 4005 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 663:
#line 4016 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10919 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 664:
#line 4023 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10928 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 665:
#line 4028 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10937 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 667:
#line 4036 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10945 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 668:
#line 4040 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 669:
#line 4044 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 10961 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 671:
#line 4051 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 10970 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 672:
#line 4058 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10978 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 675:
#line 4068 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[-1]), (yyvsp[-1].expr));
				list_splice_tail((yyvsp[0].list), &(yyval.expr)->stmt_list);
				xfree((yyvsp[0].list));
			}
#line 10988 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 676:
#line 4074 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10996 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 677:
#line 4080 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 11004 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 679:
#line 4087 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 11012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 680:
#line 4091 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 11020 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 681:
#line 4095 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 11032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 682:
#line 4105 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 11040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 684:
#line 4112 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 11050 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 685:
#line 4118 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 11059 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 686:
#line 4125 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 11067 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 687:
#line 4129 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
				(yyval.stmt)->counter.packets = (yyvsp[-2].val);
				(yyval.stmt)->counter.bytes = (yyvsp[0].val);
			}
#line 11077 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 688:
#line 4135 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].val) == 0) {
					erec_queue(error(&(yylsp[0]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate  = (yyvsp[-3].val);
				(yyval.stmt)->limit.unit  = (yyvsp[-1].val);
				(yyval.stmt)->limit.burst = (yyvsp[0].val);
				(yyval.stmt)->limit.type  = NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 11095 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 689:
#line 4149 "parser_bison.y" /* yacc.c:1652  */
    {
				struct error_record *erec;
				uint64_t rate, unit;

				if ((yyvsp[0].val) == 0) {
					erec_queue(error(&(yylsp[0]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				erec = rate_parse(&(yyloc), (yyvsp[-1].string), &rate, &unit);
				xfree((yyvsp[-1].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate  = rate * (yyvsp[-2].val);
				(yyval.stmt)->limit.unit  = unit;
				(yyval.stmt)->limit.burst = (yyvsp[0].val);
				(yyval.stmt)->limit.type  = NFT_LIMIT_PKT_BYTES;
				(yyval.stmt)->limit.flags = (yyvsp[-3].val);
                        }
#line 11123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 690:
#line 4175 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 11131 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 691:
#line 4179 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 11139 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 692:
#line 4183 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 11151 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 699:
#line 4202 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_SET); }
#line 11157 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 700:
#line 4204 "parser_bison.y" /* yacc.c:1652  */
    {
				int32_t num = -(yyvsp[0].val);

				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(num) * BITS_PER_BYTE,
							 &num);
			}
#line 11170 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 701:
#line 4215 "parser_bison.y" /* yacc.c:1652  */
    {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 11182 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 702:
#line 4225 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 11191 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 703:
#line 4232 "parser_bison.y" /* yacc.c:1652  */
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
#line 11213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 704:
#line 4252 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 11222 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 705:
#line 4259 "parser_bison.y" /* yacc.c:1652  */
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
#line 11240 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 706:
#line 4275 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 11249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 707:
#line 4281 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 11255 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 708:
#line 4282 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 11261 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 709:
#line 4283 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 11267 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 710:
#line 4286 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_TCP; }
#line 11273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 711:
#line 4287 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_UDP; }
#line 11279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 712:
#line 4291 "parser_bison.y" /* yacc.c:1652  */
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
#line 11299 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 713:
#line 4307 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 11307 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 714:
#line 4313 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 11317 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 715:
#line 4319 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 11326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 716:
#line 4327 "parser_bison.y" /* yacc.c:1652  */
    {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 11341 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 717:
#line 4340 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 11353 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 718:
#line 4348 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;

				ct = &(yyvsp[-6].obj)->ct_timeout;
				list_splice_tail((yyvsp[-2].list), &ct->timeout_list);
				xfree((yyvsp[-2].list));
			}
#line 11365 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 719:
#line 4356 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 11373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 720:
#line 4362 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 11381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 721:
#line 4366 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 11389 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 722:
#line 4370 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 11397 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 723:
#line 4374 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 11405 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 724:
#line 4378 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 11413 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 725:
#line 4384 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 11421 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 726:
#line 4390 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;

				limit = &(yyvsp[-6].obj)->limit;
				limit->rate	= (yyvsp[-3].val);
				limit->unit	= (yyvsp[-1].val);
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-4].val);
			}
#line 11436 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 727:
#line 4401 "parser_bison.y" /* yacc.c:1652  */
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
#line 11459 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 728:
#line 4422 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 11468 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 729:
#line 4429 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 11476 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 730:
#line 4433 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 11484 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 731:
#line 4437 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11492 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 732:
#line 4443 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11502 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 733:
#line 4449 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11512 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 734:
#line 4456 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11518 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 735:
#line 4457 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11524 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 736:
#line 4458 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11530 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 737:
#line 4459 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11536 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 739:
#line 4464 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11544 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 740:
#line 4468 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11552 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 742:
#line 4475 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11560 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 744:
#line 4482 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 746:
#line 4489 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 750:
#line 4500 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 11589 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 751:
#line 4509 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 11602 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 752:
#line 4519 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = true; }
#line 11608 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 753:
#line 4520 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = false; }
#line 11614 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 754:
#line 4524 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 11624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 755:
#line 4531 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 11630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 756:
#line 4532 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 11636 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 757:
#line 4533 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 11642 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 758:
#line 4534 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 11648 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 759:
#line 4535 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 11654 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 760:
#line 4536 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 11660 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 761:
#line 4537 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 11666 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 762:
#line 4538 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 11672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 763:
#line 4539 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 11678 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 764:
#line 4540 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 11684 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 765:
#line 4541 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 11690 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 766:
#line 4542 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 11696 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 767:
#line 4545 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11702 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 768:
#line 4546 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 769:
#line 4547 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11714 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 770:
#line 4548 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11720 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 771:
#line 4550 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11731 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 772:
#line 4557 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 773:
#line 4564 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 774:
#line 4571 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11764 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 775:
#line 4578 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11775 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 776:
#line 4585 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11786 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 777:
#line 4592 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11797 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 778:
#line 4599 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11808 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 779:
#line 4606 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11819 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 780:
#line 4613 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11830 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 781:
#line 4620 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11841 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 782:
#line 4627 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 11852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 783:
#line 4633 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 11858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 784:
#line 4636 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_EQ; }
#line 11864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 785:
#line 4637 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_NEQ; }
#line 11870 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 786:
#line 4638 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LT; }
#line 11876 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 787:
#line 4639 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GT; }
#line 11882 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 788:
#line 4640 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GTE; }
#line 11888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 789:
#line 4641 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LTE; }
#line 11894 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 790:
#line 4645 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 11902 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 791:
#line 4649 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 11910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 792:
#line 4653 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 11918 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 793:
#line 4657 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 11926 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 794:
#line 4661 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 11934 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 795:
#line 4665 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 11942 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 797:
#line 4672 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 11954 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 798:
#line 4682 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11962 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 799:
#line 4686 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 11970 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 800:
#line 4690 "parser_bison.y" /* yacc.c:1652  */
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
#line 11988 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 803:
#line 4709 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_LEN; }
#line 11994 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 804:
#line 4710 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 12000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 805:
#line 4711 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 12006 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 806:
#line 4712 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 12012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 807:
#line 4713 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECMARK; }
#line 12018 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 808:
#line 4716 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_MARK; }
#line 12024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 809:
#line 4717 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIF; }
#line 12030 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 810:
#line 4718 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 12036 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 811:
#line 4719 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 12042 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 812:
#line 4720 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIF; }
#line 12048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 813:
#line 4721 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 12054 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 814:
#line 4722 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 12060 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 815:
#line 4723 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKUID; }
#line 12066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 816:
#line 4724 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKGID; }
#line 12072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 817:
#line 4725 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 12078 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 818:
#line 4726 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 12084 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 819:
#line 4727 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 12090 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 820:
#line 4728 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 12096 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 821:
#line 4729 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 12102 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 822:
#line 4730 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 12108 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 823:
#line 4731 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 12114 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 824:
#line 4732 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CPU; }
#line 12120 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 825:
#line 4733 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 12126 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 826:
#line 4734 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 12132 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 827:
#line 4735 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 12138 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 828:
#line 4736 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECPATH; }
#line 12144 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 829:
#line 4737 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_NS; }
#line 12150 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 830:
#line 4738 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_DAY; }
#line 12156 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 831:
#line 4739 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_HOUR; }
#line 12162 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 832:
#line 4743 "parser_bison.y" /* yacc.c:1652  */
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
#line 12186 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 833:
#line 4763 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 12194 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 834:
#line 4767 "parser_bison.y" /* yacc.c:1652  */
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
#line 12212 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 835:
#line 4781 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 12220 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 836:
#line 4785 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 12228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 837:
#line 4789 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 12236 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 838:
#line 4795 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 12244 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 839:
#line 4800 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 12250 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 840:
#line 4801 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_MARK; }
#line 12256 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 841:
#line 4802 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_WILDCARD; }
#line 12262 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 842:
#line 4805 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 12268 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 843:
#line 4806 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 12274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 844:
#line 4809 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 12280 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 845:
#line 4810 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 12286 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 846:
#line 4814 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 12294 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 847:
#line 4819 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 12300 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 848:
#line 4820 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 12306 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 849:
#line 4823 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_IN; }
#line 12312 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 850:
#line 4824 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_OUT; }
#line 12318 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 851:
#line 4827 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 12324 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 852:
#line 4828 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 12330 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 853:
#line 4831 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 12336 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 854:
#line 4832 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 12342 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 855:
#line 4836 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-1].val) > 255) {
					erec_queue(error(&(yylsp[-1]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 12354 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 856:
#line 4844 "parser_bison.y" /* yacc.c:1652  */
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
#line 12383 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 857:
#line 4871 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 12392 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 858:
#line 4876 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 12401 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 859:
#line 4881 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 12409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 860:
#line 4886 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 12415 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 861:
#line 4887 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 12421 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 862:
#line 4891 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 12429 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 863:
#line 4895 "parser_bison.y" /* yacc.c:1652  */
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
#line 12451 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 864:
#line 4914 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 12457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 865:
#line 4915 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 12463 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 866:
#line 4916 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 12469 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 867:
#line 4917 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_XFRM; }
#line 12475 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 868:
#line 4921 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1);
			}
#line 12483 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 869:
#line 4925 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 12491 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 870:
#line 4929 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 12499 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 871:
#line 4934 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 12505 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 872:
#line 4935 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 12511 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 873:
#line 4938 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 12517 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 874:
#line 4939 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 12523 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 875:
#line 4940 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_MARK; }
#line 12529 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 876:
#line 4941 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATE; }
#line 12535 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 877:
#line 4942 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 12541 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 878:
#line 4943 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 12547 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 879:
#line 4944 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 12553 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 880:
#line 4945 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 12559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 881:
#line 4946 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 12565 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 882:
#line 4947 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 12571 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 883:
#line 4948 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 12577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 884:
#line 4949 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 12583 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 885:
#line 4950 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 12589 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 886:
#line 4951 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 12595 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 887:
#line 4952 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SECMARK; }
#line 12601 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 888:
#line 4953 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ID; }
#line 12607 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 890:
#line 4957 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 12613 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 891:
#line 4958 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 12619 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 892:
#line 4959 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 12625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 893:
#line 4960 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 12631 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 894:
#line 4961 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 12637 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 895:
#line 4962 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 12643 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 897:
#line 4966 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP; }
#line 12649 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 898:
#line 4967 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP; }
#line 12655 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 899:
#line 4968 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP6; }
#line 12661 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 900:
#line 4969 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP6; }
#line 12667 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 901:
#line 4972 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 12673 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 902:
#line 4973 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 12679 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 903:
#line 4974 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 12685 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 904:
#line 4975 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 12691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 907:
#line 4983 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 12701 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 908:
#line 4989 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 12711 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 909:
#line 4997 "parser_bison.y" /* yacc.c:1652  */
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
#line 12728 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 910:
#line 5010 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);

			}
#line 12739 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 911:
#line 5017 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 12749 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 912:
#line 5023 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 12757 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 913:
#line 5029 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12768 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 932:
#line 5058 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 12779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 933:
#line 5066 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 12785 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 934:
#line 5067 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 12791 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 935:
#line 5068 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 12797 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 936:
#line 5072 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 12805 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 937:
#line 5077 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 12811 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 938:
#line 5078 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 12817 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 939:
#line 5079 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 12823 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 940:
#line 5083 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 12831 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 941:
#line 5088 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_VID; }
#line 12837 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 942:
#line 5089 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_CFI; }
#line 12843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 943:
#line 5090 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_PCP; }
#line 12849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 944:
#line 5091 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 12855 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 945:
#line 5095 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 12863 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 946:
#line 5100 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HRD; }
#line 12869 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 947:
#line 5101 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PRO; }
#line 12875 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 948:
#line 5102 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HLN; }
#line 12881 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 949:
#line 5103 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PLN; }
#line 12887 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 950:
#line 5104 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_OP; }
#line 12893 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 951:
#line 5105 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 12899 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 952:
#line 5106 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 12905 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 953:
#line 5107 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_IP; }
#line 12911 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 954:
#line 5108 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_IP; }
#line 12917 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 955:
#line 5112 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 12925 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 956:
#line 5116 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val), 0);
			}
#line 12933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 957:
#line 5120 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[0].val), IPOPT_FIELD_TYPE, 0);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 12942 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 958:
#line 5126 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_VERSION; }
#line 12948 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 959:
#line 5127 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 12954 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 960:
#line 5128 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DSCP; }
#line 12960 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 961:
#line 5129 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ECN; }
#line 12966 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 962:
#line 5130 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 12972 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 963:
#line 5131 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ID; }
#line 12978 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 964:
#line 5132 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 12984 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 965:
#line 5133 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_TTL; }
#line 12990 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 966:
#line 5134 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 12996 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 967:
#line 5135 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 13002 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 968:
#line 5136 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_SADDR; }
#line 13008 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 969:
#line 5137 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DADDR; }
#line 13014 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 970:
#line 5140 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_LSRR; }
#line 13020 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 971:
#line 5141 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RR; }
#line 13026 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 972:
#line 5142 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_SSRR; }
#line 13032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 973:
#line 5143 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RA; }
#line 13038 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 974:
#line 5146 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 13044 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 975:
#line 5147 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 13050 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 976:
#line 5148 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 13056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 977:
#line 5149 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_PTR; }
#line 13062 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 978:
#line 5150 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 13068 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 979:
#line 5154 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 13076 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 980:
#line 5159 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 13082 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 981:
#line 5160 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 13088 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 982:
#line 5161 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 13094 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 983:
#line 5162 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_ID; }
#line 13100 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 984:
#line 5163 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 13106 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 985:
#line 5164 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 13112 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 986:
#line 5165 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 13118 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 987:
#line 5169 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[0].val));
			}
#line 13126 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 988:
#line 5174 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_TYPE; }
#line 13132 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 989:
#line 5175 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 13138 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 990:
#line 5176 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_MRT; }
#line 13144 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 991:
#line 5177 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_GROUP; }
#line 13150 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 992:
#line 5181 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 13158 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 993:
#line 5186 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 13164 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 994:
#line 5187 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 13170 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 995:
#line 5188 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_ECN; }
#line 13176 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 996:
#line 5189 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 13182 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 997:
#line 5190 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 13188 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 998:
#line 5191 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 13194 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 999:
#line 5192 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 13200 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1000:
#line 5193 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 13206 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1001:
#line 5194 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 13212 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1002:
#line 5197 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 13220 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1003:
#line 5202 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 13226 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1004:
#line 5203 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 13232 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1005:
#line 5204 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 13238 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1006:
#line 5205 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 13244 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1007:
#line 5206 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 13250 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1008:
#line 5207 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 13256 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1009:
#line 5208 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 13262 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1010:
#line 5209 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 13268 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1011:
#line 5213 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 13276 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1012:
#line 5218 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 13282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1013:
#line 5219 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 13288 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1014:
#line 5220 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 13294 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1015:
#line 5221 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SPI; }
#line 13300 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1016:
#line 5222 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 13306 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1017:
#line 5226 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 13314 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1018:
#line 5231 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SPI; }
#line 13320 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1019:
#line 5232 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 13326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1020:
#line 5236 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 13334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1021:
#line 5241 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 13340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1022:
#line 5242 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 13346 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1023:
#line 5243 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_CPI; }
#line 13352 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1024:
#line 5247 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 13360 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1025:
#line 5252 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 13366 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1026:
#line 5253 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 13372 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1027:
#line 5254 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 13378 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1028:
#line 5255 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 13384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1029:
#line 5259 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 13392 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1030:
#line 5264 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 13398 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1031:
#line 5265 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 13404 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1032:
#line 5266 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 13410 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1033:
#line 5267 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 13416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1034:
#line 5271 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 13424 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1035:
#line 5275 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 13432 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1036:
#line 5279 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPT_COMMON_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 13441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1037:
#line 5284 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-4].val), 0);
				tcpopt_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val), 0);
			}
#line 13450 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1038:
#line 5290 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 13456 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1039:
#line 5291 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 13462 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1040:
#line 5292 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 13468 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1041:
#line 5293 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 13474 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1042:
#line 5294 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 13480 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1043:
#line 5295 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 13486 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1044:
#line 5296 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 13492 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1045:
#line 5297 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 13498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1046:
#line 5298 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 13504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1047:
#line 5299 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 13510 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1048:
#line 5302 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_EOL; }
#line 13516 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1049:
#line 5303 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_NOP; }
#line 13522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1050:
#line 5304 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_MAXSEG; }
#line 13528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1051:
#line 5305 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_WINDOW; }
#line 13534 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1052:
#line 5306 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK_PERMITTED; }
#line 13540 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1053:
#line 5307 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK; }
#line 13546 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1054:
#line 5308 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK; }
#line 13552 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1055:
#line 5309 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK1; }
#line 13558 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1056:
#line 5310 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK2; }
#line 13564 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1057:
#line 5311 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK3; }
#line 13570 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1058:
#line 5312 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_ECHO; }
#line 13576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1059:
#line 5313 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_TIMESTAMP; }
#line 13582 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1060:
#line 5314 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].val) > 255) {
					erec_queue(error(&(yylsp[0]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[0].val);
			}
#line 13594 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1061:
#line 5323 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_COMMON_KIND; }
#line 13600 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1062:
#line 5324 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_COMMON_LENGTH; }
#line 13606 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1063:
#line 5325 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_MAXSEG_SIZE; }
#line 13612 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1064:
#line 5326 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_WINDOW_COUNT; }
#line 13618 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1065:
#line 5327 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_SACK_LEFT; }
#line 13624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1066:
#line 5328 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_SACK_RIGHT; }
#line 13630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1067:
#line 5329 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_TS_TSVAL; }
#line 13636 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1068:
#line 5330 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_TS_TSECR; }
#line 13642 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1069:
#line 5334 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 13650 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1070:
#line 5339 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 13656 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1071:
#line 5340 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 13662 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1072:
#line 5341 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 13668 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1073:
#line 5345 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 13676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1074:
#line 5350 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 13682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1075:
#line 5351 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 13688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1076:
#line 5352 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 13694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1077:
#line 5353 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 13700 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1078:
#line 5357 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[0].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 13710 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1079:
#line 5364 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_SPORT; }
#line 13716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1080:
#line 5365 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_DPORT; }
#line 13722 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1089:
#line 5379 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 13730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1090:
#line 5384 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 13736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1091:
#line 5385 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 13742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1092:
#line 5389 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 13750 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1093:
#line 5394 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 13756 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1094:
#line 5395 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 13762 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1095:
#line 5396 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_TYPE; }
#line 13768 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1096:
#line 5397 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 13774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1097:
#line 5401 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 13782 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1098:
#line 5407 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 13790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1099:
#line 5413 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 13798 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1100:
#line 5418 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 13804 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1101:
#line 5422 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 13812 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1102:
#line 5427 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 13818 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1103:
#line 5428 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 13824 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1104:
#line 5429 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_TAG; }
#line 13830 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1105:
#line 5431 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 13838 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1106:
#line 5437 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 13846 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1107:
#line 5442 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 13852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1108:
#line 5443 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 13858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1109:
#line 5444 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 13864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1110:
#line 5445 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 13870 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1111:
#line 5446 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 13876 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1112:
#line 5447 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_ID; }
#line 13882 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1113:
#line 5451 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 13890 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1114:
#line 5456 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 13896 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1115:
#line 5457 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 13902 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1116:
#line 5461 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 13910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1117:
#line 5466 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 13916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1118:
#line 5467 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 13922 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1119:
#line 5468 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_TYPE; }
#line 13928 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1120:
#line 5469 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 13934 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1121:
#line 5470 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 13940 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1122:
#line 5474 "parser_bison.y" /* yacc.c:1652  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 13956 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1123:
#line 5487 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 13962 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1124:
#line 5488 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 13968 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1125:
#line 5489 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 13974 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1126:
#line 5490 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 13980 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1127:
#line 5491 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_MH; }
#line 13986 "parser_bison.c" /* yacc.c:1652  */
    break;


#line 13990 "parser_bison.c" /* yacc.c:1652  */
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
#line 5494 "parser_bison.y" /* yacc.c:1918  */

