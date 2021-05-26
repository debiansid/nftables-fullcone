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

#line 211 "parser_bison.c" /* yacc.c:337  */
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
    CGROUPV2 = 289,
    TPROXY = 290,
    OSF = 291,
    SYNPROXY = 292,
    MSS = 293,
    WSCALE = 294,
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
    NOP = 431,
    SACK = 432,
    SACK0 = 433,
    SACK1 = 434,
    SACK2 = 435,
    SACK3 = 436,
    SACK_PERM = 437,
    TIMESTAMP = 438,
    KIND = 439,
    COUNT = 440,
    LEFT = 441,
    RIGHT = 442,
    TSVAL = 443,
    TSECR = 444,
    DCCP = 445,
    SCTP = 446,
    CHUNK = 447,
    DATA = 448,
    INIT = 449,
    INIT_ACK = 450,
    HEARTBEAT = 451,
    HEARTBEAT_ACK = 452,
    ABORT = 453,
    SHUTDOWN = 454,
    SHUTDOWN_ACK = 455,
    ERROR = 456,
    COOKIE_ECHO = 457,
    COOKIE_ACK = 458,
    ECNE = 459,
    CWR = 460,
    SHUTDOWN_COMPLETE = 461,
    ASCONF_ACK = 462,
    FORWARD_TSN = 463,
    ASCONF = 464,
    TSN = 465,
    STREAM = 466,
    SSN = 467,
    PPID = 468,
    INIT_TAG = 469,
    A_RWND = 470,
    NUM_OSTREAMS = 471,
    NUM_ISTREAMS = 472,
    INIT_TSN = 473,
    CUM_TSN_ACK = 474,
    NUM_GACK_BLOCKS = 475,
    NUM_DUP_TSNS = 476,
    LOWEST_TSN = 477,
    SEQNO = 478,
    NEW_CUM_TSN = 479,
    VTAG = 480,
    RT = 481,
    RT0 = 482,
    RT2 = 483,
    RT4 = 484,
    SEG_LEFT = 485,
    ADDR = 486,
    LAST_ENT = 487,
    TAG = 488,
    SID = 489,
    HBH = 490,
    FRAG = 491,
    RESERVED2 = 492,
    MORE_FRAGMENTS = 493,
    DST = 494,
    MH = 495,
    META = 496,
    MARK = 497,
    IIF = 498,
    IIFNAME = 499,
    IIFTYPE = 500,
    OIF = 501,
    OIFNAME = 502,
    OIFTYPE = 503,
    SKUID = 504,
    SKGID = 505,
    NFTRACE = 506,
    RTCLASSID = 507,
    IBRIPORT = 508,
    OBRIPORT = 509,
    IBRIDGENAME = 510,
    OBRIDGENAME = 511,
    PKTTYPE = 512,
    CPU = 513,
    IIFGROUP = 514,
    OIFGROUP = 515,
    CGROUP = 516,
    TIME = 517,
    CLASSID = 518,
    NEXTHOP = 519,
    CT = 520,
    L3PROTOCOL = 521,
    PROTO_SRC = 522,
    PROTO_DST = 523,
    ZONE = 524,
    DIRECTION = 525,
    EVENT = 526,
    EXPECTATION = 527,
    EXPIRATION = 528,
    HELPER = 529,
    LABEL = 530,
    STATE = 531,
    STATUS = 532,
    ORIGINAL = 533,
    REPLY = 534,
    COUNTER = 535,
    NAME = 536,
    PACKETS = 537,
    BYTES = 538,
    AVGPKT = 539,
    COUNTERS = 540,
    QUOTAS = 541,
    LIMITS = 542,
    SYNPROXYS = 543,
    HELPERS = 544,
    LOG = 545,
    PREFIX = 546,
    GROUP = 547,
    SNAPLEN = 548,
    QUEUE_THRESHOLD = 549,
    LEVEL = 550,
    LIMIT = 551,
    RATE = 552,
    BURST = 553,
    OVER = 554,
    UNTIL = 555,
    QUOTA = 556,
    USED = 557,
    SECMARK = 558,
    SECMARKS = 559,
    SECOND = 560,
    MINUTE = 561,
    HOUR = 562,
    DAY = 563,
    WEEK = 564,
    _REJECT = 565,
    WITH = 566,
    ICMPX = 567,
    SNAT = 568,
    DNAT = 569,
    MASQUERADE = 570,
    REDIRECT = 571,
    RANDOM = 572,
    FULLY_RANDOM = 573,
    PERSISTENT = 574,
    QUEUE = 575,
    QUEUENUM = 576,
    BYPASS = 577,
    FANOUT = 578,
    DUP = 579,
    FWD = 580,
    NUMGEN = 581,
    INC = 582,
    MOD = 583,
    OFFSET = 584,
    JHASH = 585,
    SYMHASH = 586,
    SEED = 587,
    POSITION = 588,
    INDEX = 589,
    COMMENT = 590,
    XML = 591,
    JSON = 592,
    VM = 593,
    NOTRACK = 594,
    EXISTS = 595,
    MISSING = 596,
    EXTHDR = 597,
    IPSEC = 598,
    REQID = 599,
    SPNUM = 600,
    IN = 601,
    OUT = 602
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
#define CGROUPV2 289
#define TPROXY 290
#define OSF 291
#define SYNPROXY 292
#define MSS 293
#define WSCALE 294
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
#define NOP 431
#define SACK 432
#define SACK0 433
#define SACK1 434
#define SACK2 435
#define SACK3 436
#define SACK_PERM 437
#define TIMESTAMP 438
#define KIND 439
#define COUNT 440
#define LEFT 441
#define RIGHT 442
#define TSVAL 443
#define TSECR 444
#define DCCP 445
#define SCTP 446
#define CHUNK 447
#define DATA 448
#define INIT 449
#define INIT_ACK 450
#define HEARTBEAT 451
#define HEARTBEAT_ACK 452
#define ABORT 453
#define SHUTDOWN 454
#define SHUTDOWN_ACK 455
#define ERROR 456
#define COOKIE_ECHO 457
#define COOKIE_ACK 458
#define ECNE 459
#define CWR 460
#define SHUTDOWN_COMPLETE 461
#define ASCONF_ACK 462
#define FORWARD_TSN 463
#define ASCONF 464
#define TSN 465
#define STREAM 466
#define SSN 467
#define PPID 468
#define INIT_TAG 469
#define A_RWND 470
#define NUM_OSTREAMS 471
#define NUM_ISTREAMS 472
#define INIT_TSN 473
#define CUM_TSN_ACK 474
#define NUM_GACK_BLOCKS 475
#define NUM_DUP_TSNS 476
#define LOWEST_TSN 477
#define SEQNO 478
#define NEW_CUM_TSN 479
#define VTAG 480
#define RT 481
#define RT0 482
#define RT2 483
#define RT4 484
#define SEG_LEFT 485
#define ADDR 486
#define LAST_ENT 487
#define TAG 488
#define SID 489
#define HBH 490
#define FRAG 491
#define RESERVED2 492
#define MORE_FRAGMENTS 493
#define DST 494
#define MH 495
#define META 496
#define MARK 497
#define IIF 498
#define IIFNAME 499
#define IIFTYPE 500
#define OIF 501
#define OIFNAME 502
#define OIFTYPE 503
#define SKUID 504
#define SKGID 505
#define NFTRACE 506
#define RTCLASSID 507
#define IBRIPORT 508
#define OBRIPORT 509
#define IBRIDGENAME 510
#define OBRIDGENAME 511
#define PKTTYPE 512
#define CPU 513
#define IIFGROUP 514
#define OIFGROUP 515
#define CGROUP 516
#define TIME 517
#define CLASSID 518
#define NEXTHOP 519
#define CT 520
#define L3PROTOCOL 521
#define PROTO_SRC 522
#define PROTO_DST 523
#define ZONE 524
#define DIRECTION 525
#define EVENT 526
#define EXPECTATION 527
#define EXPIRATION 528
#define HELPER 529
#define LABEL 530
#define STATE 531
#define STATUS 532
#define ORIGINAL 533
#define REPLY 534
#define COUNTER 535
#define NAME 536
#define PACKETS 537
#define BYTES 538
#define AVGPKT 539
#define COUNTERS 540
#define QUOTAS 541
#define LIMITS 542
#define SYNPROXYS 543
#define HELPERS 544
#define LOG 545
#define PREFIX 546
#define GROUP 547
#define SNAPLEN 548
#define QUEUE_THRESHOLD 549
#define LEVEL 550
#define LIMIT 551
#define RATE 552
#define BURST 553
#define OVER 554
#define UNTIL 555
#define QUOTA 556
#define USED 557
#define SECMARK 558
#define SECMARKS 559
#define SECOND 560
#define MINUTE 561
#define HOUR 562
#define DAY 563
#define WEEK 564
#define _REJECT 565
#define WITH 566
#define ICMPX 567
#define SNAT 568
#define DNAT 569
#define MASQUERADE 570
#define REDIRECT 571
#define RANDOM 572
#define FULLY_RANDOM 573
#define PERSISTENT 574
#define QUEUE 575
#define QUEUENUM 576
#define BYPASS 577
#define FANOUT 578
#define DUP 579
#define FWD 580
#define NUMGEN 581
#define INC 582
#define MOD 583
#define OFFSET 584
#define JHASH 585
#define SYMHASH 586
#define SEED 587
#define POSITION 588
#define INDEX 589
#define COMMENT 590
#define XML 591
#define JSON 592
#define VM 593
#define NOTRACK 594
#define EXISTS 595
#define MISSING 596
#define EXTHDR 597
#define IPSEC 598
#define REQID 599
#define SPNUM 600
#define IN 601
#define OUT 602

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 166 "parser_bison.y" /* yacc.c:352  */

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

#line 974 "parser_bison.c" /* yacc.c:352  */
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
#define YYLAST   7982

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  357
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  378
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1206
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2037

#define YYUNDEFTOK  2
#define YYMAXUTOK   602

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
       2,     2,     2,     2,     2,     2,   354,     2,     2,     2,
     351,   352,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   348,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   355,     2,   356,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   349,   353,   350,     2,     2,     2,     2,
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
     345,   346,   347
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   888,   888,   889,   898,   899,   902,   903,   906,   907,
     908,   909,   910,   911,   912,   913,   914,   915,   916,   917,
     918,   919,   920,   921,   922,   923,   924,   926,   928,   936,
     951,   958,   969,   977,   978,   979,   980,  1000,  1001,  1002,
    1003,  1004,  1005,  1006,  1007,  1008,  1009,  1010,  1011,  1012,
    1013,  1014,  1017,  1021,  1028,  1032,  1040,  1044,  1048,  1055,
    1062,  1066,  1073,  1082,  1086,  1090,  1094,  1098,  1102,  1106,
    1110,  1114,  1118,  1122,  1126,  1130,  1136,  1142,  1146,  1153,
    1157,  1165,  1172,  1179,  1183,  1190,  1199,  1203,  1207,  1211,
    1215,  1219,  1223,  1227,  1233,  1239,  1240,  1243,  1244,  1247,
    1248,  1251,  1252,  1255,  1259,  1263,  1267,  1271,  1275,  1279,
    1283,  1287,  1294,  1298,  1302,  1306,  1310,  1314,  1320,  1326,
    1330,  1334,  1338,  1342,  1346,  1350,  1354,  1358,  1362,  1366,
    1370,  1374,  1378,  1382,  1386,  1390,  1394,  1398,  1402,  1406,
    1410,  1414,  1418,  1422,  1426,  1430,  1434,  1438,  1442,  1446,
    1450,  1454,  1460,  1464,  1468,  1472,  1476,  1480,  1486,  1490,
    1494,  1498,  1502,  1506,  1510,  1516,  1523,  1529,  1537,  1543,
    1551,  1560,  1561,  1564,  1565,  1566,  1567,  1568,  1569,  1570,
    1571,  1574,  1575,  1578,  1579,  1580,  1583,  1592,  1598,  1613,
    1623,  1624,  1625,  1626,  1627,  1638,  1648,  1659,  1669,  1680,
    1691,  1700,  1709,  1718,  1729,  1740,  1754,  1760,  1761,  1762,
    1763,  1764,  1765,  1766,  1771,  1781,  1782,  1783,  1790,  1811,
    1822,  1833,  1846,  1851,  1852,  1853,  1854,  1859,  1865,  1870,
    1875,  1880,  1886,  1891,  1896,  1897,  1908,  1909,  1912,  1916,
    1919,  1920,  1921,  1922,  1926,  1931,  1932,  1933,  1934,  1937,
    1938,  1939,  1940,  1945,  1955,  1966,  1977,  1989,  1998,  2003,
    2008,  2017,  2020,  2024,  2030,  2031,  2035,  2040,  2041,  2042,
    2043,  2057,  2061,  2065,  2071,  2076,  2083,  2088,  2093,  2096,
    2103,  2110,  2122,  2129,  2130,  2142,  2147,  2148,  2149,  2150,
    2154,  2164,  2165,  2166,  2167,  2171,  2181,  2182,  2183,  2184,
    2188,  2199,  2203,  2204,  2205,  2209,  2219,  2220,  2221,  2222,
    2226,  2236,  2237,  2238,  2239,  2243,  2253,  2254,  2255,  2256,
    2260,  2270,  2271,  2272,  2273,  2277,  2287,  2288,  2289,  2290,
    2291,  2294,  2325,  2332,  2336,  2339,  2349,  2356,  2367,  2380,
    2395,  2396,  2399,  2411,  2417,  2421,  2424,  2430,  2443,  2448,
    2457,  2458,  2461,  2464,  2465,  2466,  2469,  2484,  2485,  2488,
    2489,  2490,  2491,  2492,  2493,  2496,  2505,  2514,  2522,  2530,
    2538,  2546,  2554,  2562,  2570,  2578,  2586,  2594,  2602,  2610,
    2618,  2626,  2634,  2638,  2643,  2651,  2658,  2665,  2678,  2682,
    2689,  2693,  2699,  2711,  2717,  2724,  2730,  2737,  2738,  2739,
    2740,  2743,  2744,  2745,  2746,  2747,  2748,  2749,  2750,  2751,
    2752,  2753,  2754,  2755,  2756,  2757,  2758,  2759,  2760,  2761,
    2762,  2765,  2766,  2769,  2778,  2782,  2788,  2794,  2799,  2802,
    2807,  2812,  2815,  2821,  2826,  2834,  2835,  2837,  2841,  2849,
    2853,  2856,  2860,  2866,  2867,  2870,  2876,  2880,  2883,  3008,
    3013,  3018,  3023,  3028,  3034,  3064,  3068,  3072,  3076,  3080,
    3086,  3090,  3093,  3097,  3103,  3117,  3142,  3150,  3151,  3152,
    3155,  3156,  3159,  3160,  3175,  3191,  3199,  3200,  3201,  3204,
    3205,  3208,  3209,  3210,  3225,  3226,  3227,  3228,  3229,  3232,
    3235,  3242,  3246,  3257,  3268,  3278,  3284,  3287,  3288,  3291,
    3297,  3303,  3309,  3316,  3323,  3331,  3332,  3335,  3339,  3347,
    3351,  3354,  3359,  3364,  3368,  3374,  3390,  3409,  3415,  3416,
    3422,  3423,  3429,  3430,  3431,  3432,  3433,  3434,  3435,  3436,
    3437,  3438,  3439,  3440,  3441,  3444,  3445,  3449,  3455,  3456,
    3462,  3463,  3469,  3470,  3476,  3479,  3480,  3491,  3492,  3495,
    3499,  3502,  3508,  3514,  3515,  3518,  3519,  3520,  3523,  3527,
    3531,  3536,  3541,  3546,  3552,  3556,  3560,  3564,  3570,  3576,
    3581,  3590,  3600,  3601,  3604,  3607,  3611,  3616,  3622,  3623,
    3626,  3629,  3633,  3637,  3641,  3646,  3653,  3658,  3666,  3671,
    3680,  3681,  3687,  3688,  3689,  3692,  3693,  3696,  3702,  3706,
    3709,  3714,  3720,  3721,  3727,  3728,  3731,  3732,  3735,  3741,
    3748,  3755,  3766,  3767,  3768,  3771,  3779,  3791,  3798,  3801,
    3807,  3811,  3814,  3820,  3829,  3840,  3846,  3872,  3873,  3882,
    3883,  3886,  3895,  3906,  3907,  3908,  3909,  3910,  3911,  3912,
    3913,  3914,  3915,  3916,  3917,  3918,  3919,  3920,  3923,  3946,
    3947,  3948,  3951,  3952,  3953,  3954,  3955,  3958,  3962,  3965,
    3969,  3976,  3979,  3993,  3994,  3998,  4004,  4005,  4011,  4012,
    4018,  4019,  4025,  4028,  4029,  4040,  4046,  4052,  4053,  4056,
    4062,  4063,  4064,  4067,  4074,  4079,  4084,  4087,  4091,  4095,
    4101,  4102,  4109,  4115,  4116,  4119,  4120,  4123,  4129,  4135,
    4139,  4142,  4146,  4150,  4160,  4164,  4167,  4173,  4180,  4184,
    4190,  4204,  4228,  4233,  4241,  4245,  4249,  4259,  4262,  4263,
    4266,  4267,  4268,  4269,  4280,  4291,  4297,  4318,  4324,  4341,
    4347,  4348,  4349,  4352,  4353,  4354,  4357,  4358,  4361,  4377,
    4383,  4389,  4396,  4410,  4418,  4426,  4432,  4436,  4440,  4444,
    4448,  4455,  4460,  4471,  4493,  4499,  4503,  4507,  4511,  4515,
    4519,  4523,  4527,  4533,  4539,  4547,  4548,  4549,  4552,  4553,
    4557,  4563,  4564,  4570,  4571,  4577,  4578,  4584,  4587,  4588,
    4589,  4598,  4609,  4610,  4613,  4621,  4622,  4623,  4624,  4625,
    4626,  4627,  4628,  4629,  4630,  4631,  4632,  4635,  4636,  4637,
    4638,  4639,  4646,  4653,  4660,  4667,  4674,  4681,  4688,  4695,
    4702,  4709,  4716,  4723,  4726,  4727,  4728,  4729,  4730,  4731,
    4732,  4735,  4739,  4743,  4747,  4751,  4755,  4761,  4762,  4772,
    4776,  4780,  4796,  4797,  4800,  4801,  4802,  4803,  4804,  4807,
    4808,  4809,  4810,  4811,  4812,  4813,  4814,  4815,  4816,  4817,
    4818,  4819,  4820,  4821,  4822,  4823,  4824,  4825,  4826,  4827,
    4828,  4829,  4830,  4833,  4853,  4857,  4871,  4875,  4879,  4885,
    4889,  4895,  4896,  4897,  4900,  4901,  4904,  4905,  4908,  4914,
    4915,  4918,  4919,  4922,  4923,  4926,  4927,  4930,  4938,  4965,
    4970,  4975,  4981,  4982,  4985,  4989,  5009,  5010,  5011,  5012,
    5015,  5019,  5023,  5029,  5030,  5033,  5034,  5035,  5036,  5037,
    5038,  5039,  5040,  5041,  5042,  5043,  5044,  5045,  5046,  5047,
    5048,  5049,  5052,  5053,  5054,  5055,  5056,  5057,  5058,  5061,
    5062,  5063,  5064,  5067,  5068,  5069,  5070,  5073,  5074,  5077,
    5083,  5091,  5104,  5111,  5117,  5123,  5132,  5133,  5134,  5135,
    5136,  5137,  5138,  5139,  5140,  5141,  5142,  5143,  5144,  5145,
    5146,  5147,  5148,  5149,  5152,  5161,  5162,  5163,  5166,  5172,
    5173,  5174,  5177,  5183,  5184,  5185,  5186,  5189,  5195,  5196,
    5197,  5198,  5199,  5200,  5201,  5202,  5203,  5206,  5210,  5214,
    5221,  5222,  5223,  5224,  5225,  5226,  5227,  5228,  5229,  5230,
    5231,  5232,  5235,  5236,  5237,  5238,  5241,  5242,  5243,  5244,
    5245,  5248,  5254,  5255,  5256,  5257,  5258,  5259,  5260,  5263,
    5269,  5270,  5271,  5272,  5275,  5281,  5282,  5283,  5284,  5285,
    5286,  5287,  5288,  5289,  5291,  5297,  5298,  5299,  5300,  5301,
    5302,  5303,  5304,  5307,  5313,  5314,  5315,  5316,  5317,  5320,
    5326,  5327,  5330,  5336,  5337,  5338,  5341,  5347,  5348,  5349,
    5350,  5353,  5359,  5360,  5361,  5362,  5365,  5369,  5373,  5378,
    5385,  5386,  5387,  5388,  5389,  5390,  5391,  5392,  5393,  5394,
    5397,  5398,  5399,  5400,  5401,  5402,  5403,  5404,  5405,  5406,
    5407,  5408,  5409,  5418,  5419,  5420,  5421,  5422,  5423,  5424,
    5425,  5428,  5434,  5435,  5436,  5439,  5440,  5441,  5442,  5443,
    5444,  5445,  5446,  5447,  5448,  5449,  5450,  5451,  5452,  5453,
    5454,  5455,  5456,  5459,  5460,  5461,  5464,  5465,  5466,  5467,
    5470,  5471,  5472,  5473,  5474,  5477,  5478,  5479,  5480,  5483,
    5488,  5492,  5496,  5500,  5504,  5508,  5513,  5518,  5523,  5528,
    5533,  5540,  5544,  5550,  5551,  5552,  5553,  5556,  5564,  5565,
    5568,  5569,  5570,  5571,  5572,  5573,  5574,  5575,  5578,  5584,
    5585,  5588,  5594,  5595,  5596,  5597,  5600,  5606,  5612,  5618,
    5621,  5627,  5628,  5629,  5630,  5636,  5642,  5643,  5644,  5645,
    5646,  5647,  5650,  5656,  5657,  5660,  5666,  5667,  5668,  5669,
    5670,  5673,  5687,  5688,  5689,  5690,  5691
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
  "\"fib\"", "\"socket\"", "\"transparent\"", "\"wildcard\"",
  "\"cgroupv2\"", "\"tproxy\"", "\"osf\"", "\"synproxy\"", "\"mss\"",
  "\"wscale\"", "\"typeof\"", "\"hook\"", "\"device\"", "\"devices\"",
  "\"table\"", "\"tables\"", "\"chain\"", "\"chains\"", "\"rule\"",
  "\"rules\"", "\"sets\"", "\"set\"", "\"element\"", "\"map\"", "\"maps\"",
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
  "close_scope_limit", "close_scope_numgen", "close_scope_quota",
  "close_scope_queue", "close_scope_rt", "close_scope_sctp",
  "close_scope_sctp_chunk", "close_scope_secmark", "close_scope_socket",
  "close_scope_log", "common_block", "line", "base_cmd", "add_cmd",
  "replace_cmd", "create_cmd", "insert_cmd", "table_or_id_spec",
  "chain_or_id_spec", "set_or_id_spec", "obj_or_id_spec", "delete_cmd",
  "get_cmd", "list_cmd", "reset_cmd", "flush_cmd", "rename_cmd",
  "import_cmd", "export_cmd", "monitor_cmd", "monitor_event",
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
  "limit_burst_pkts", "limit_burst_bytes", "time_unit", "reject_stmt",
  "reject_stmt_alloc", "reject_opts", "nat_stmt", "nat_stmt_alloc",
  "tproxy_stmt", "synproxy_stmt", "synproxy_stmt_alloc", "synproxy_args",
  "synproxy_arg", "synproxy_config", "synproxy_obj", "synproxy_ts",
  "synproxy_sack", "primary_stmt_expr", "shift_stmt_expr", "and_stmt_expr",
  "exclusive_or_stmt_expr", "inclusive_or_stmt_expr", "basic_stmt_expr",
  "concat_stmt_expr", "map_stmt_expr_set", "map_stmt_expr",
  "prefix_stmt_expr", "range_stmt_expr", "multiton_stmt_expr", "stmt_expr",
  "nat_stmt_args", "masq_stmt", "masq_stmt_alloc", "masq_stmt_args",
  "redir_stmt", "redir_stmt_alloc", "redir_stmt_arg", "dup_stmt",
  "fwd_stmt", "nf_nat_flags", "nf_nat_flag", "queue_stmt",
  "queue_stmt_alloc", "queue_stmt_args", "queue_stmt_arg",
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
  "meter_key_expr_alloc", "set_elem_expr", "set_elem_key_expr",
  "set_elem_expr_alloc", "set_elem_options", "set_elem_option",
  "set_elem_expr_options", "set_elem_stmt_list", "set_elem_stmt",
  "set_elem_expr_option", "set_lhs_expr", "set_rhs_expr",
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
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,    61,   123,
     125,    40,    41,   124,    36,    91,    93
};
# endif

#define YYPACT_NINF -1700

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1700)))

#define YYTABLE_NINF -939

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1700,  7372, -1700,  1017, -1700, -1700,   292,   300,   300,   300,
    1281,  1281,  1281,  1281,  1281,  1281,  1281,  1281, -1700, -1700,
    4248,   233,  2008,   373,  1237,   449,  4526,   339,  1121,   215,
    6736,    75,   209,   407, -1700, -1700, -1700, -1700,   190,  1281,
    1281,  1281,  1281, -1700, -1700, -1700,   722, -1700,   300, -1700,
     300,    66,  6138, -1700,  1017, -1700,   204,   280,  1017,   300,
   -1700,   351,   375,  6138,   300, -1700,  -128, -1700,   300, -1700,
   -1700,  1281, -1700,  1281,  1281,  1281,  1281,  1281,  1281,  1281,
     262,  1281,  1281,  1281,  1281, -1700,  1281, -1700,  1281,  1281,
    1281,  1281,  1281,  1281,  1281,  1281,   382,  1281,  1281,  1281,
    1281, -1700,  1281, -1700,  1281,  1281,  1281,  1281,  1281,   747,
    1281,  1281,  1281,  1281,  1281,   285,  1281,  1281,  1281,   281,
    1281,   875,   926,  1161,  1186,  1281,  1281,  1281,  1238, -1700,
    1281,  1531,  1703,  1281, -1700,  1281,  1281,  1281,  1281,  1281,
     611,  1281, -1700,  1281, -1700,   820,   163,   264,   532, -1700,
   -1700, -1700, -1700,   670,   970,   888,  1352,  2330,  1745,   179,
    1310,  1639,   927,   453,   762,   586,   746,  2394,   510,   752,
     590,   511,   521,   460,   158,   630,   423,   571,  4835, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
    3951, -1700, -1700,    46,  6381,   411,   626,   535,  6736,   300,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700,   783, -1700, -1700,   425, -1700,
   -1700,   783, -1700, -1700, -1700, -1700,  1266, -1700, -1700, -1700,
    1281,  1281,  1281,  -125, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700,   684,   698,   704, -1700, -1700, -1700,   109,   490,   306,
   -1700, -1700, -1700, -1700, -1700, -1700,    22,    22, -1700,   433,
     300,  5093,  2785,   496, -1700,   -62,   352, -1700, -1700, -1700,
   -1700, -1700, -1700,   709,   145, -1700,   807, -1700,   486,  6138,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,   613, -1700,
     344, -1700, -1700, -1700,   517, -1700,  4356, -1700, -1700,   522,
   -1700,   133, -1700,   240, -1700, -1700, -1700,   829, -1700,    82,
   -1700, -1700,   806, -1700, -1700, -1700,   899,   840,   854,   533,
   -1700,   560, -1700,  5646, -1700, -1700, -1700,   857, -1700, -1700,
   -1700,   907, -1700,  5913,  5913, -1700, -1700,    90,   620,   635,
   -1700, -1700,   657, -1700, -1700, -1700,   683, -1700,   686,   964,
    6138, -1700,   351,   375, -1700,  -128, -1700, -1700,  1281,  1281,
    1281,   697, -1700, -1700, -1700,  6138, -1700,   156, -1700, -1700,
   -1700,   188, -1700, -1700, -1700,   243, -1700, -1700, -1700, -1700,
     405, -1700, -1700,  -128, -1700,   464,   692, -1700, -1700, -1700,
   -1700,  1281, -1700, -1700, -1700, -1700,  -128, -1700, -1700, -1700,
   -1700, -1700, -1700,  1281, -1700, -1700, -1700, -1700, -1700, -1700,
    1281,  1281, -1700, -1700, -1700,   985,  1001, -1700,  1281,  1014,
   -1700,  1281, -1700,  1281, -1700,  1281, -1700,  1281, -1700, -1700,
   -1700, -1700,  1281, -1700, -1700,  1281, -1700,  1281, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700,  1281, -1700,   300, -1700, -1700,
   -1700,  1043, -1700, -1700, -1700, -1700, -1700,  1055,    69, -1700,
   -1700,   765, -1700, -1700,   972,    77, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,   387,   508,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,  1000, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700,  2829, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700,  3775, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700,     6, -1700, -1700,
     733, -1700, -1700, -1700, -1700, -1700, -1700,   741, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
    1446, -1700, -1700, -1700, -1700,   788,   242,   796,   997, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,   781,   777,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700,   783, -1700, -1700, -1700, -1700,  -103,  -113,   213,    40,
   -1700, -1700, -1700,  4614,  1048,  6979,  6736, -1700, -1700, -1700,
   -1700,  1117,  1136,     8,  1113,  1119,  1126,    52,  1129,  1446,
    1137,  6979,  6979,   654,  6979, -1700, -1700,  1086,  6979,  6979,
    1131, -1700,  5715,    91, -1700,  1052, -1700, -1700,   851, -1700,
    1114,  1122,   613, -1700, -1700,   509,  1052,  1124,  1125,  1127,
    1052,   344, -1700,   108, -1700,  6979, -1700,  4872,  1139,   970,
     888,  1352,  2330, -1700,  1310,   102, -1700, -1700, -1700,  1148,
   -1700, -1700, -1700, -1700,  6979, -1700,   923,  1215,  1216,   890,
    1018,   527, -1700, -1700, -1700, -1700,  1239,   889,  1235, -1700,
   -1700, -1700, -1700,  1240, -1700, -1700, -1700, -1700,   105, -1700,
   -1700,  1241,  1247, -1700,  1154,  1155, -1700, -1700,   522, -1700,
    1257, -1700, -1700, -1700, -1700,  1256, -1700,  5130, -1700,  1256,
    6979, -1700, -1700, -1700,   829, -1700,  1258, -1700,   300, -1700,
     917, -1700,   300,    68, -1700,  7499,  7499,  7499,  7499,  7499,
    6736,   123,  7222, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700,  7499, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700,   569, -1700,   960,  1251,  1255,
     933,   710,  1268, -1700, -1700, -1700,  7222,  6979,  6979,  1179,
      81,  1017,  1280, -1700,   753,  1017,  1190, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700,  1263,   944,   946,   956,
   -1700,   957,   958, -1700, -1700, -1700, -1700,  1028,  1015,   689,
    1052, -1700,  1217,  1220,  1225,  1226, -1700,  1227,   981, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,  1281,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700,  1230,   163, -1700, -1700, -1700,
   -1700,  1236, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700,   676, -1700, -1700,
    3173, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700,   717,   598,  1180,  1185,  1185, -1700,
   -1700, -1700,  1130, -1700, -1700, -1700, -1700,  1123,  1128, -1700,
    1120,  1112,  1135,   174, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700,  1261,  1265, -1700, -1700, -1700, -1700,   906, -1700,
     959, -1700, -1700, -1700, -1700, -1700, -1700, -1700,  1269,  1271,
    1019, -1700,  1285,    11, -1700, -1700, -1700,  1003,  1005,  1046,
    1304, -1700, -1700,   654, -1700, -1700, -1700,  1305, -1700, -1700,
   -1700, -1700,  6979,  2330,  1310,  1403,  5388, -1700,    82,    39,
    1402,  1052,  1052,  1311,  6736,  6979,  6979,  6979, -1700,  1322,
    6979,  1374,  6979, -1700, -1700, -1700, -1700,  1325, -1700,    37,
    1385, -1700,  6979, -1700,   807,  1081,   347,    45, -1700,  1026,
    1268,   807, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
    1283,   440, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700,  1318,  1327,  1382,  1346, -1700,  6979,  1460,  6979, -1700,
   -1700, -1700,   227,   438,  6979,  1132, -1700, -1700,  6979,  6979,
    6979,  6979,  6979,  1365,  6979,  6979,   141,  6979,  1256,  6979,
    1400,  1479,  1405,  2872,  2872, -1700, -1700, -1700,  6979,   889,
    6979,   889, -1700, -1700, -1700,   786, -1700,  6736, -1700,  6736,
   -1700, -1700, -1700,   960,  1251,  1255, -1700,   807, -1700, -1700,
   -1700, -1700, -1700, -1700,  1143,  7499,  7499,  7499,  7499,  7499,
    7499,  7499,  7499,  7628,  7499,  7499,   665, -1700,   809, -1700,
   -1700, -1700, -1700, -1700,  1395, -1700,   386,   214,  2250,  3080,
    2691,   768,   134, -1700, -1700, -1700, -1700, -1700, -1700,  1150,
    1162,  1163, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700,  1490, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
    1496, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,  1157,
    1158, -1700, -1700, -1700, -1700, -1700, -1700,  1019,   279,  1409,
   -1700, -1700, -1700, -1700, -1700,   995, -1700, -1700, -1700,  1233,
    1223, -1700,  1417,  1878, -1700,   737,    37, -1700,   680, -1700,
   -1700,  6979,  6979,  1516, -1700,  1421,  1421, -1700,    39, -1700,
   -1700, -1700,  1177,  1402,  6138,    39, -1700, -1700, -1700, -1700,
   -1700, -1700,  6979, -1700, -1700,   173, -1700, -1700, -1700,  1222,
    6979,  1485, -1700,  7430, -1700,  1347,  1252,  1242,   347, -1700,
    1421,  1421, -1700,    45, -1700,  5715, -1700,  4093, -1700, -1700,
   -1700, -1700,  1528, -1700,  1434,  1435, -1700,  1441, -1700,  6979,
   -1700, -1700, -1700, -1700, -1700,   923,  1215,  1216, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700,  1540,  6979,  1384,  6979, -1700,
   -1700, -1700, -1700,   889, -1700,   889,  1256, -1700,   142,  6138,
    5844,    97, -1700, -1700, -1700,  1280,  1541, -1700, -1700,   960,
    1251,  1255, -1700,   103,  1280, -1700, -1700,  1026,  7499,  7628,
   -1700,  1452,  1508, -1700, -1700, -1700, -1700, -1700,   300,   300,
     300,   300,   300,  1459,   394,   300,   300,   300,   300, -1700,
   -1700, -1700,  1017, -1700,    74,  1464,  1470, -1700, -1700, -1700,
    1017,  1017,  1017,  1017,  1017,  6736, -1700,  1421,  1421,  1228,
    1020,  1473,   585,  1016,  1393, -1700, -1700, -1700,  1017,  1017,
     276, -1700,  6736,  1421,  1234,   585,  1016, -1700, -1700, -1700,
    1017,  1017,  1481,  1244,  1484, -1700, -1700, -1700, -1700,  2346,
    3412,  2933,   797,   313, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700,   499, -1700, -1700,  1486, -1700, -1700,  1487, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700,  1494, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700,   299,  2679,  1811,  1497, -1700, -1700,
   -1700, -1700, -1700,   182, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700,  1222, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700,  6979, -1700, -1700, -1700, -1700,  6736,  1250,    39,
   -1700, -1700, -1700, -1700, -1700,  1110,  1299,  1500, -1700, -1700,
    6979,    22,    22,   807,  1268, -1700,    98,  1502, -1700,   654,
   -1700, -1700, -1700, -1700, -1700, -1700,  1017, -1700,   440, -1700,
   -1700, -1700, -1700,  6979, -1700,  1522, -1700,  1256,  1256,  6736,
   -1700,   201,  1262,  1606,   807, -1700,  1280,  1280,  1431,  1514,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
     300,   300,   300, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700,  1582, -1700, -1700, -1700, -1700, -1700, -1700,
     691, -1700,  1017,  1017,  -128, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700,  1006, -1700, -1700, -1700,
   -1700, -1700,   939, -1700, -1700, -1700, -1700, -1700,   639,  1017,
    -128,   656,   939, -1700, -1700,  1476,   -45,  1017, -1700, -1700,
   -1700, -1700, -1700, -1700,  1038,  3126,  2495, -1700, -1700,  1621,
   -1700,  1019, -1700, -1700,  1286,   419,  1281, -1700, -1700, -1700,
   -1700, -1700,  1421,  1532,   419,  1534,  1281, -1700, -1700, -1700,
   -1700, -1700,  1535,  1281, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700,  1110,  1299, -1700, -1700, -1700, -1700, -1700,  6138, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700,  1339,  1542, -1700,    37,
   -1700, -1700, -1700, -1700,  1543,  1358,  1544, -1700, -1700, -1700,
    6979,  1296,  6736, -1700, -1700,   885,  5844, -1700, -1700,  1467,
    1017,  1301,  1302,  1306,  1307,  1308, -1700, -1700, -1700,  1313,
    1314,  1317,  1320,  1551,  6736, -1700, -1700, -1700, -1700,   585,
   -1700,  1016, -1700,  6570, -1700, -1700,  2735, -1700,   161,  1017,
      29,  1017, -1700, -1700, -1700, -1700, -1700,  1566, -1700,  1321,
   -1700, -1700,  1017,  1017, -1700,  1017,  1017,  1017,  1017,  1017,
   -1700,  1545,  1017, -1700,  1339, -1700,  1323,  1570, -1700,    78,
   -1700, -1700, -1700, -1700,  1571,   185, -1700, -1700,  1324,   807,
   -1700, -1700,  1431, -1700, -1700, -1700, -1700, -1700,  1326,  1328,
    1336, -1700, -1700, -1700, -1700,  1140, -1700, -1700, -1700,  6736,
    1017,  1678,  1679,   585, -1700, -1700, -1700, -1700,  1017,  1006,
    1588, -1700, -1700, -1700,   866, -1700, -1700, -1700, -1700, -1700,
     118, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,  1589,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700,   419, -1700, -1700,
   -1700,  1408, -1700, -1700, -1700, -1700, -1700,  1110,  1299, -1700,
   -1700,  1467,  2206,  3763,  3593,   967,  1175, -1700, -1700, -1700,
    2315,  2359,  1603,  1730,    70,  1344,  1476,   691, -1700,  6736,
    1006, -1700, -1700, -1700, -1700, -1700, -1700, -1700,  1592,  1595,
      92, -1700,  1692,   119, -1700,  1017, -1700, -1700,  1339, -1700,
   -1700,  1017,  1017,  1017,  1017,  1017,  1780,  3938,  2697,  1017,
    1017,  1017,  1017, -1700, -1700,   -45, -1700, -1700,  1694, -1700,
   -1700, -1700, -1700, -1700,  1605,  1589,  1017, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700,  1017,  1017,  1017,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     357,   357,   357,   357,   357,   357,   357,   357,   361,   364,
     357,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   171,   363,     8,    14,    15,     0,   357,
     357,   357,   357,    34,    33,     3,     0,    37,     0,   358,
       0,   382,     0,    32,     0,   352,     0,     0,     0,     0,
     517,    52,    54,     0,     0,   222,     0,   244,     0,   266,
      38,   357,    39,   357,   357,   357,   357,   357,   357,   357,
       0,   357,   357,   357,   357,    40,   357,    41,   357,   357,
     357,   357,   357,   357,   357,   357,     0,   357,   357,   357,
     357,    42,   357,    43,   357,   357,   388,   357,   388,   388,
     357,   357,   388,   357,   388,     0,   357,   388,   388,     0,
     357,   388,   388,   388,   388,   357,   357,   357,   388,    44,
     357,   388,   388,   357,    45,   357,   357,   357,   357,   388,
       0,   357,    46,   357,    47,     0,     0,     0,   661,   632,
     353,   354,   355,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   839,
     840,   841,   842,   843,   844,   845,   846,   847,   848,   849,
     850,   851,   852,   853,   854,   855,   856,   857,   858,   860,
       0,   862,   861,     0,     0,     0,     0,    17,     0,     0,
      51,   628,   627,   633,   634,   186,   644,   645,   638,   830,
     639,   642,   646,   643,   640,   641,   635,   946,   947,   948,
     949,   950,   951,   952,   953,   954,   955,   956,   957,   958,
     959,   960,   961,   962,   963,   636,  1160,  1161,  1162,  1163,
    1164,  1165,  1166,  1167,   637,     0,   183,   184,     0,    48,
     167,     0,    49,   169,   172,    50,   173,   362,   359,   360,
     357,   357,   357,    10,   754,   727,   729,    36,    35,   365,
     367,     0,     0,     0,   384,   383,   385,     0,   507,     0,
     612,   613,   614,   821,   822,   823,   421,   422,   826,   619,
       0,     0,     0,   437,   445,     0,   469,   490,   497,   498,
     574,   580,   597,     0,     0,   866,     7,    57,   390,   392,
     405,   393,   206,   420,   401,   425,   400,    10,   435,    27,
     443,   398,   399,   408,   491,   409,     0,   410,   419,   505,
     413,   573,   414,   579,   415,   416,   411,    21,   417,     0,
     418,   403,     0,   618,   402,   663,   666,   668,   670,   672,
     673,   680,   682,     0,   681,   625,   424,   830,   406,   412,
     404,   635,    28,     0,     0,    31,   376,     0,     0,     0,
      56,   370,     0,    60,   237,   236,     0,   373,     0,     0,
       0,   517,    77,    79,   222,     0,   244,   266,   357,   357,
     357,    10,   754,   727,   729,     0,   117,     0,   101,   102,
     103,     0,    95,    96,   104,     0,    97,    98,   105,   106,
       0,    99,   100,     0,   107,     0,   109,   110,   731,   732,
     730,   357,    10,    18,    20,    25,     0,   140,   119,   389,
     120,   121,   122,   357,   123,   125,   149,   148,   147,   141,
     357,   388,   145,   144,   146,   731,   732,   733,   357,     0,
      10,   357,   126,   357,   129,   357,   132,   357,   138,    18,
      20,    25,   357,   135,    10,   357,   152,   357,   155,    20,
     158,   159,   160,   161,   164,   357,   163,     0,   965,   966,
     967,     0,   652,   653,   654,   655,   656,   658,     0,   871,
     873,     0,   872,    26,     0,     0,  1158,  1159,  1157,   969,
     970,   971,    11,   976,   973,   974,   975,    16,     0,     0,
     978,   979,   980,   981,   982,     8,  1000,  1001,   995,   990,
     991,   992,   993,   994,   996,   997,   998,   999,     0,    14,
    1012,  1015,  1014,  1013,  1016,  1017,  1018,  1011,  1020,  1021,
    1022,  1023,  1019,  1032,  1033,  1025,  1026,  1027,  1029,  1028,
    1030,  1031,    15,  1035,  1040,  1037,  1036,  1041,  1039,  1038,
    1042,  1034,  1045,  1048,  1044,  1046,  1047,  1043,  1051,  1050,
    1049,  1053,  1054,  1055,  1052,  1059,  1060,  1057,  1058,  1056,
    1065,  1062,  1063,  1064,  1061,  1078,  1072,  1075,  1076,  1070,
    1071,  1073,  1074,  1077,  1079,     0,  1066,  1104,  1102,  1103,
    1101,  1156,  1153,  1154,     0,  1155,    23,  1174,    14,  1173,
     898,    15,  1172,  1175,   896,   897,    17,     0,    22,    22,
       0,  1176,  1179,  1178,  1182,  1181,  1183,     0,  1180,  1170,
    1169,  1168,  1191,  1188,  1186,  1187,  1189,  1190,  1185,  1194,
    1193,  1192,  1198,  1197,  1200,  1196,  1199,  1195,   831,   834,
     835,   836,    25,   837,    17,   829,   832,   833,   913,   914,
     920,   906,   907,   905,   915,   916,   936,   909,   918,   911,
     912,   917,   908,   910,   903,   904,   934,   933,   935,    25,
       0,     9,   921,   877,   876,     0,   680,     0,     0,    22,
    1202,  1204,  1205,  1206,  1201,   881,   882,   859,   880,     0,
     626,   166,   185,   168,   174,   175,   177,   176,   179,   180,
     178,   181,   751,   751,   751,    62,     0,     0,   469,     0,
     379,   380,   381,     0,     0,     0,     0,   828,   827,   824,
     825,     0,     0,     0,   831,   829,     0,     0,     0,     0,
       9,     0,     0,   478,     0,   467,   468,     0,     0,     0,
       0,     6,     0,     0,   684,     0,   391,   394,     0,   397,
       0,     0,   436,   439,   407,     0,     0,     0,     0,     0,
       0,   444,   446,     0,   489,     0,   793,     0,     0,    11,
      16,     8,    14,   792,    15,     0,   796,   794,   795,     0,
     791,   790,   782,   783,     0,   535,   538,   540,   542,   544,
     545,   550,   555,   553,   554,   556,   558,   496,   522,   523,
     533,   784,   524,   531,   525,   532,   528,   529,     0,   526,
     527,     0,   557,   530,     0,     0,   514,   513,   506,   509,
       0,   592,   593,   594,   572,   577,   590,     0,   578,   583,
       0,   604,   605,   595,    21,   598,   601,   602,     0,   630,
       0,   629,     0,     0,   620,     0,     0,     0,     0,     0,
       0,     0,     0,   814,   815,   816,   817,   818,   819,   820,
      11,    16,     8,    14,   806,   807,    15,   808,   805,   804,
     809,   802,   803,   801,   810,    23,   812,     0,   797,   767,
     798,   677,   678,   779,   766,   756,   755,   771,   773,   775,
     777,   778,   765,   799,   800,   768,     0,     0,     0,     0,
       7,     0,   721,   720,   778,     0,     0,   321,    74,   190,
     207,   223,   249,   267,   386,    76,     0,     0,     0,     0,
      83,     0,     0,   751,   751,   751,    85,     0,     0,   469,
       0,    94,     0,     0,     0,     0,   108,     0,     0,   751,
     112,   115,   113,   116,   118,   124,   143,   142,     9,   357,
     128,   127,   130,   133,   139,   134,   131,   137,   136,   154,
     153,   156,   157,   162,   165,     0,     0,   651,   649,   650,
      12,     0,   869,   662,   659,   660,   968,   972,    11,    14,
      11,    14,   977,  1002,  1003,  1004,  1005,    14,   987,  1024,
       0,  1082,  1092,  1083,  1090,  1080,  1081,  1085,  1086,  1087,
    1088,  1089,  1084,  1091,  1068,  1108,  1105,  1106,  1107,  1109,
    1110,  1111,  1112,  1113,  1114,  1115,  1116,  1117,  1118,  1119,
    1120,  1121,  1122,  1139,    24,  1151,   892,   893,   899,    22,
     894,  1171,     0,     0,   838,   919,   922,   923,     0,   925,
       0,   924,   926,   927,     9,     9,   928,   900,     0,     0,
     874,  1203,     0,     0,   647,   170,   182,     0,     0,     0,
       0,   286,    10,   478,   311,    18,   291,     0,    20,   316,
     728,    25,     0,    14,    15,   499,     0,   508,     0,   606,
     608,     0,     0,     0,     0,     0,     0,     0,     9,     0,
       0,   928,     0,   438,    18,   476,   477,     0,    20,     0,
     586,   588,     0,   696,     7,     7,   698,   693,   695,   778,
     717,     7,   683,   387,   215,   441,   442,   440,   459,    11,
       0,     0,   457,   453,   448,   449,   450,   451,   454,   452,
     447,     0,     0,     0,     0,   564,     0,   559,     0,   785,
     788,   789,   786,   787,     0,     0,   522,   531,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   566,     0,
       0,     0,     0,     0,     0,   511,   512,   510,     0,     0,
       0,   581,   600,   596,   599,     0,   631,     0,   622,     0,
     621,   664,   665,   667,   669,   671,   674,     7,   426,   428,
     679,   786,   787,   811,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   762,   761,   778,   864,
     945,   723,   722,    29,     0,    30,     0,     0,     0,     0,
       0,     0,     0,    93,   190,   207,   223,   249,   267,     0,
       0,     0,    10,    18,    20,    25,   377,   366,   368,   371,
     374,   267,     9,   150,     9,     0,   657,   648,    26,   983,
     985,   984,   986,  1006,  1007,  1009,  1008,  1010,   989,    14,
       0,  1095,  1094,  1093,  1096,  1097,  1098,  1099,  1100,  1067,
    1136,  1135,  1137,  1138,  1144,  1126,  1127,  1128,  1129,  1141,
    1130,  1131,  1132,  1133,  1134,  1142,  1143,  1145,  1146,  1147,
    1148,  1149,  1150,  1123,  1125,  1124,  1140,    23,   895,     0,
       0,    14,    14,    15,    15,   901,   902,   874,   874,     0,
      13,   879,   883,   884,    17,     0,   301,   306,   296,     0,
       0,    63,     0,     0,    70,     0,     0,    65,     0,    72,
     501,     0,     0,   500,   609,     0,     0,   703,   607,   699,
     868,   867,     0,   692,     0,   690,   865,   863,     9,   433,
       9,     9,     0,     9,   466,     0,   475,   471,   470,   472,
       0,     0,   687,     0,   688,     0,    10,     0,   697,   706,
       0,     0,   716,   694,   704,   686,   685,     0,   458,    14,
     462,   463,   455,   461,     0,     0,   495,     0,   565,     0,
     569,   571,   534,   536,   537,   539,   541,   543,   551,   552,
     546,   549,   548,   547,   561,   560,     0,     0,     0,   937,
     938,   939,   940,   575,   591,   582,   584,   603,     0,     0,
       0,     0,   429,   813,   764,   758,     0,   769,   770,   772,
     774,   776,   763,   675,   757,   676,   780,   781,     0,     0,
     675,     0,     0,    75,   323,   322,   325,   324,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
     192,   191,     0,   189,     0,     0,     0,    55,   209,   208,
       0,     0,     0,     0,     0,     0,   233,     0,     0,     0,
       0,     0,     0,     0,     0,    58,   225,   224,     0,     0,
       0,   395,     0,     0,     0,     0,     0,    59,   251,   250,
       0,     0,     0,     0,     0,    10,    61,   269,   268,     0,
       0,     0,     0,     0,   301,   306,   296,    86,    91,    87,
      92,     0,   114,   151,     0,   870,   988,     0,  1152,  1177,
    1184,   929,   930,   931,   932,    19,     0,    13,   875,   891,
     887,   886,   885,    17,     0,     0,     0,     0,    10,   288,
     287,   290,   289,     0,    18,   313,   312,   315,   314,    20,
     293,   292,   295,   294,   472,    25,   318,   317,   320,   319,
     502,   504,     0,   356,   701,   702,   700,     0,     0,   691,
     942,   434,   943,     9,   941,     0,   481,     0,    20,   587,
       0,     0,     0,     7,   718,   719,     0,     0,   708,   478,
     707,   714,   715,   705,   423,   216,     0,   456,     0,   492,
     493,   494,   562,     0,   568,     0,   570,   576,   585,     0,
     610,     0,     0,     0,     7,   427,   760,   759,   518,     0,
     378,   285,   369,   206,   372,   222,   244,   375,   266,   188,
       0,     0,     0,   285,   285,   285,   285,   193,   350,   351,
     347,   349,   348,     0,   346,   210,   212,   211,   214,   213,
       0,   220,     0,     0,     0,   265,   264,   262,   263,   326,
     328,   329,   327,   282,   330,   283,     0,   281,   240,   241,
     243,   242,     0,   239,   234,   235,   231,   396,     0,     0,
       0,     0,     0,   261,   260,     0,     0,     0,   272,    78,
      80,    81,    82,    84,     0,     0,     0,   111,   964,     0,
     878,   874,   890,   888,     0,     0,     0,     9,   303,   302,
     305,   304,     0,     0,     0,     0,     0,     9,   308,   307,
     310,   309,     0,     0,     9,   298,   297,   300,   299,   724,
      64,     0,   481,    71,    66,   726,    73,   503,     0,   623,
     944,   484,   485,   486,   487,   488,   479,     0,    18,     0,
     474,   589,   689,     9,     0,     0,     0,   217,   460,   563,
       0,     0,     0,   611,   617,     0,   431,   430,   519,   520,
       0,     0,     0,     0,     0,     0,   285,   285,   285,     0,
       0,     0,     0,     0,     0,   227,   229,   230,   232,     0,
     226,     0,   228,     0,   252,   259,     0,   258,     0,     0,
       0,     0,   275,   273,     9,     9,     9,     0,    13,     0,
     737,   736,     0,     0,    68,     0,     0,     0,     0,     0,
      69,     0,     0,    67,   479,   753,     0,     0,    18,     0,
     465,   473,   712,     9,     0,     0,   567,   615,     0,     7,
     521,   515,   518,   321,   207,   223,   249,   267,     0,     0,
       0,   286,   311,   291,   316,   345,   221,   284,   238,     0,
       0,     0,   218,     0,    10,    18,    20,    25,     0,     0,
       0,   340,   334,   333,   337,   332,   335,   336,   270,   279,
       0,   276,   280,   271,    89,    90,    88,  1069,   889,     0,
     743,   745,   748,   749,   746,   747,   750,     0,   739,   752,
     624,     0,   464,   483,   482,   713,    10,     0,   481,   616,
     432,   520,     0,     0,     0,     0,     0,   301,   306,   296,
       0,     0,     0,     0,     0,     0,     0,     0,   255,     0,
       0,   245,   247,   246,   248,   257,   253,   341,     0,     0,
       7,   274,     0,     0,   740,     0,   480,   709,   479,    18,
     516,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   342,   343,     0,   331,   256,   219,   254,
     339,   338,   278,   277,     0,     0,     0,   738,    18,   711,
     205,   194,   195,   196,   197,     9,     9,     9,    10,    18,
      20,    25,   344,   742,   741,   744,   710,     0,     0,     0,
     198,   203,   199,   204,   201,   202,   200
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1700, -1700,    -1, -1018,    14,  -854,  -315,  -469, -1700, -1434,
      -2,   -24,  1192,  -603,  -464, -1700,  -440,   853,  -570,  -843,
   -1700,  -462,   442, -1700,    20, -1700, -1700,  1697, -1700, -1700,
   -1700, -1700, -1700, -1700,  1379, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700,     4, -1700,  1329,
   -1700,   474,  -321, -1207, -1700, -1700, -1441,  -380, -1204,  -388,
     203,   -95,  -377, -1700, -1197, -1226, -1700,  -386, -1220,  -262,
   -1700,  -231,   -79, -1438,  -909,  -140,  -135, -1474, -1471, -1470,
    -139,  -132,  -124, -1700, -1700,  -202, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700,   189,  -683, -1275,  1675,   -48,  2812,
   -1700,   865, -1700, -1700,    93, -1700,   294,   138, -1700, -1700,
    2407, -1700,  -730,  1380, -1700, -1700,   178,  1682,   848,  2624,
     -46, -1700, -1700,   336, -1209,  -311, -1700, -1700, -1700, -1700,
   -1700, -1700,   132, -1700, -1700, -1700, -1700,  1011, -1700, -1700,
   -1700,   996, -1700, -1700, -1700,   162, -1700,  1483, -1291,   207,
   -1700, -1036, -1699, -1595, -1585, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700,   965,  -333,  1414,   -58,  -123,  -961,
     646,   648,   649, -1700,  -717, -1700, -1700, -1700, -1700, -1700,
   -1700,  1512, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700,  -318,   634, -1700, -1700, -1700,   975, -1700,   629, -1146,
   -1700, -1700,  1546, -1700, -1700, -1700, -1700,   968, -1700, -1700,
      88,   -26,  -760,  -317,   225,   -27, -1700, -1700, -1700,   863,
     255, -1700, -1700, -1700, -1700, -1700,  -181,  -186, -1700, -1700,
     618, -1700,  1649,   -42, -1700,   723, -1132, -1700, -1361, -1700,
   -1700,   491, -1221, -1700, -1700,   467,   468, -1700, -1700,  1491,
    -585,  1468,  -572,  1457,  -564,  1469,  1752, -1700, -1594, -1700,
   -1700,  -129, -1700, -1700,  -353,  -561,  1488, -1700,  -347,  -309,
    -779,  -778,  -777, -1700,  -274,  -742, -1700,   159,  1253,  -764,
   -1700, -1315,  -287,   283,  1577, -1700,   -30, -1700,   363, -1700,
   -1233, -1700,   371, -1700, -1700, -1700, -1700, -1700,   397,  -258,
     628,  1254,   671,  1593,  1594, -1700, -1700,  -477,    28, -1700,
   -1700, -1700,   770, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700,   881, -1700, -1700, -1700, -1700,
   -1700, -1700,   871, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700,
   -1700, -1700, -1700, -1700, -1700, -1700, -1700, -1700
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1527,   762,  1161,  1067,   725,  1159,  1267,  1559,
    1211,  1212,  1160,   707,   961,  1730,   962,   853,  1050,  1045,
    1317,   963,   992,   774,  1528,    45,    46,    47,    72,    85,
      87,   410,   414,   419,   406,   101,   103,   129,   134,   142,
     144,   259,   262,   265,   266,   721,  1075,   260,   210,   378,
    1482,  1238,   379,  1239,  1397,  1890,  1680,   382,  1240,   383,
    1702,  1703,   386,  1898,  1241,  1508,  1687,   388,  1242,  1831,
    1910,  1911,  1695,  1696,  1801,  1340,  1345,  1566,  1564,  1565,
    1343,  1348,  1237,  1697,  1490,  1829,  1904,  1905,  1906,  1956,
    1491,  1492,  1670,  1671,  1650,   211,  1594,    48,    49,    59,
     413,    51,   417,  1653,    65,   422,  1655,    69,   427,  1658,
     408,   409,  1651,   284,   285,   286,    52,   390,  1357,   440,
    1494,   318,   319,  1510,   320,   321,   322,   323,   324,   325,
    1208,  1441,  1442,   326,   327,   328,   772,   773,   329,   330,
     781,   782,  1149,  1143,  1402,  1403,   331,  1087,  1379,  1608,
     332,  1117,  1858,  1778,  1776,   333,   334,   784,   335,   336,
     337,   338,   339,   838,   839,  1467,   377,  1799,  1871,   805,
     806,   807,   808,   809,   810,   811,  1421,   812,   813,   814,
     815,   816,   817,   340,   341,   844,   342,   343,   848,   344,
     345,   845,   846,   346,   347,   854,   855,   856,   857,  1098,
    1099,   348,   349,   350,   351,   352,   863,   864,   353,   354,
     212,   818,   860,   899,   819,   355,   216,   990,   497,   498,
     820,   505,   356,   357,   358,   359,   360,   361,   901,   902,
     903,   362,   363,   364,   763,   764,  1364,  1365,  1125,  1126,
    1127,  1358,  1359,  1393,  1388,  1389,  1394,  1128,  1613,   921,
    1572,   726,  1583,   728,  1589,   729,   431,   459,  1842,  1758,
    1973,  1974,  1741,  1751,  1077,  1578,   727,   365,   922,   923,
     907,   908,   909,   910,  1129,   912,   821,   822,   823,   915,
     916,   366,   739,   824,   665,   666,   219,   368,   825,   503,
    1330,   695,   826,  1073,   708,  1334,  1563,   222,   827,   627,
     829,   628,   830,   690,   691,  1064,  1065,   692,   831,   832,
     369,   370,   833,   227,   491,   228,   512,   229,   517,   230,
     525,   231,   539,  1007,  1279,   232,   547,   233,   552,   234,
     562,   235,   571,   236,   577,   237,   580,   238,   584,   239,
     589,   240,   594,   241,   606,  1024,  1289,   242,   610,  1043,
    1316,  1299,  1305,  1294,  1044,   243,   616,   244,   508,   245,
     246,   641,   247,   629,   248,   631,   249,   633,   250,   638,
     251,   648,   252,   651,   253,   657,   254,   704
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   768,    53,   215,   213,   975,   317,   940,   767,   977,
     740,   942,   769,   269,   939,  1520,   905,   380,   696,   941,
    1130,    44,   367,  1048,   385,   849,   213,   709,  1533,   734,
     976,  1511,   861,   367,   268,   956,   263,   213,  1530,   982,
     958,  1541,  1531,   996,   928,   278,  1090,  1342,   964,   267,
    1532,  1438,  1213,   372,   906,  1584,   760,   375,   439,  1051,
     439,   439,  1726,  1724,   439,  1725,   439,  1439,  1615,   439,
     439,  1708,   938,   439,   439,   439,   439,  1711,   828,  1643,
     439,  1595,  1133,   439,   439,   761,   946,  1165,  1203,   911,
    1204,   439,  1205,  1144,  1555,  1557,   761,  1148,  1131,   924,
     924,  1201,  1202,  1103,  1644,   858,  1382,  1384,    66,    67,
    -632,  1209,   862,  1395,  1263,  1621,  1622,   960,  -632,  -632,
    -632,  -632,   281,  1732,    55,  1970,  2005,  1355,   926,  1071,
    1356,  1909,   255,  1390,   618,     3,  1391,  1596,     4,  1377,
       5,  1082,   150,   151,   152,   970,   858,  1639,   667,   620,
    1847,  1668,  1669,  1108,   384,  1929,  1088,  -725,   621,   979,
       6,     7,     8,     9,   858,  1091,  1085,  1855,  1332,   394,
     395,   396,   150,   151,   152,  1522,  1854,  1523,   213,  1080,
    1933,   987,   213,  1900,  1083,   421,   423,   424,  1179,  1440,
    1180,    63,   733,  1605,  1909,   436,    56,    57,    58,  1783,
    1054,   994,  1761,   445,   446,  1937,  1792,  1413,  1414,   452,
    1325,  1326,   952,  1066,  1420,     3,   840,   397,     4,   752,
       5,   316,  1682,  1683,  -725,   618,   209,  1055,   759,  1511,
     482,   483,   618,   426,   486,   753,  1084,   279,  1709,   280,
       6,     7,     8,     9,   953,   620,  1081,  1151,   376,   621,
     870,   448,   926,   381,  1369,   214,   621,   387,    55,   711,
    1152,   143,  1901,  1902,   405,   713,   261,  1090,   618,   624,
     625,   667,  1111,   492,   493,  1606,  1153,   214,   270,  2008,
       4,    71,     5,   639,  1762,   217,  1313,  1938,   214,   367,
      55,   548,   621,   213,  1524,   872,   499,   500,   501,   954,
       3,  1707,  1314,     4,  1830,     5,  1520,   217,   640,   209,
    -892,   549,  -892,   218,     3,   988,   989,     4,   217,     5,
    1378,   904,  1511,   847,   550,     6,     7,     8,     9,   450,
     451,   904,   904,  1975,  1315,   218,  1181,   898,  1354,     6,
       7,     8,     9,  1979,   935,    55,   218,   898,   898,   626,
     398,  1109,  1978,   385,  1522,  1333,  1523,  1104,   995,   951,
     367,  1934,  1252,   693,   213,   624,   625,   290,   291,   455,
    1078,  1079,   292,   694,   765,   367,   209,  1254,  1596,   213,
     765,   385,  1891,   209,   738,   738,  1255,  1253,  1899,  1089,
       4,  1734,     5,   220,   385,    54,  1182,  1784,   710,   282,
     283,   221,    55,   439,  1918,   494,   495,  1504,  1542,   496,
    1543,   256,   257,   258,  1525,   220,  1422,  1199,  1360,  1361,
    1154,    86,   303,   221,   209,  1461,   220,   223,   209,   214,
    1735,  1232,  1707,   214,   221,  1643,   209,   859,   305,   927,
    1449,  1132,  1450,   306,  1451,   626,   209,  1645,  1957,   223,
     841,   842,   843,  1447,  1448,  1960,  -632,  1419,  -892,   217,
     223,   955,   271,   217,   272,  1768,  1504,  1845,  1971,  2006,
     428,   551,  1207,  1524,  1548,  1988,  1986,   209,  1987,  1318,
    1869,   303,  1660,   384,  1526,   737,   737,   218,  1861,   743,
     316,   218,  1640,  1791,   741,   209,   998,   305,  1838,  1178,
       3,   102,   306,     4,   775,     5,   502,    55,  1903,   264,
     999,   384,   755,   756,  1600,   209,  1601,  1602,  -892,  1604,
     957,  -893,   913,  -893,   384,     6,     7,     8,     9,  1269,
     742,  1271,   913,   913,   399,  1175,   400,  1008,  1009,  1002,
    1522,  1504,  1523,   966,   214,   256,   257,   258,   649,   765,
    1100,  1793,   373,   456,   861,   430,   303,   841,   842,   843,
     834,   835,  1086,  1210,  1463,  1736,    55,   220,   870,  1226,
     457,   220,   305,   650,   217,   221,  1215,   306,   983,   221,
    1176,  1400,  1840,  1786,   871,  1138,  1401,  1841,   900,  1216,
    1249,  1250,  1251,  1525,   578,  1782,   376,  1047,   900,   900,
     279,   223,   218,  1243,   280,   223,  1262,  1227,  1329,   381,
     579,  1556,  1385,   872,   387,   214,  1046,  1000,  1139,   130,
     634,  1344,   607,  1214,   131,   132,  1796,  1386,   374,  1349,
     214,  1001,  1140,   754,   765,   776,   777,   778,   779,   780,
     133,  1614,  1228,  1387,  1823,   217,  1868,  1814,  1347,  1737,
    1374,   755,   756,  1130,   429,   485,   430,  1946,   224,  1524,
     217,  1826,   504,  1723,  1819,  1090,  1661,  1943,  1662,  -893,
    1398,  1944,  1215,   218,   608,   609,   984,  1141,  1376,  1945,
     224,     3,   220,   652,     4,  1458,     5,  1689,   218,  1206,
     221,   224,   635,   636,   637,     4,   653,     5,  1130,  1814,
    -187,   225,   617,   654,   836,   837,     6,     7,     8,     9,
     213,  1690,  1691,   618,   585,   619,   223,  1222,   586,  1520,
    1124,   655,   277,   225,  -206,  1076,     4,   656,     5,  -893,
    1223,  1560,  1224,   620,   225,  1511,   898,   621,     3,   698,
     622,     4,   630,     5,   642,  1663,  1664,  1665,  1666,  1770,
     587,   588,   632,   220,  1809,  1810,  1811,  1812,  1142,   643,
    1222,   221,   712,     6,     7,     8,     9,  1341,   220,     3,
    1163,   735,     4,  1234,     5,  1224,   221,   751,  1166,  1525,
     644,   861,   150,   151,   152,   730,   645,   223,  1273,  1538,
    1162,   443,   758,  1540,     6,     7,     8,     9,     3,   731,
     226,     4,   223,     5,  1274,   732,    18,    19,  1512,  1275,
    1276,   761,  1281,  1290,  1539,  1335,  1222,  1291,  1292,  1293,
     623,   765,   371,     6,     7,     8,     9,  1692,   783,  1459,
     904,  1224,   224,   371,   506,   507,   224,  1512,  -469,   898,
     898,   898,   898,   898,   213,  1282,   898,  1693,  1694,  1727,
     862,  1940,   699,   624,   625,    34,  1513,   867,  1514,   861,
    1500,   700,   701,  1501,    35,   702,   703,   646,   647,  1445,
      36,   898,   868,  1436,   904,   225,  1454,    62,   590,   225,
    1515,   705,   706,  1844,   611,  1513,   869,  1514,  1968,  1500,
     898,  1969,  1501,  1850,    37,   770,   771,  1878,  1879,  1880,
    1853,  1283,  1284,  1285,  1286,  1287,  1288,  1277,   917,  1515,
     591,   592,   581,   593,   865,   866,   612,   613,  1363,   461,
    1233,   913,   582,   583,  1235,   488,   489,   490,  1516,  1862,
    1806,  1807,  1808,   626,    18,    19,   389,  1537,  1168,  1169,
     393,  1444,  1446,     4,   614,     5,  1821,   224,  1452,  1446,
    1455,  1457,  2002,  1115,  1116,   416,   389,  1516,   918,   859,
    1733,   214,   293,   294,   295,  1611,  1612,   298,     3,   929,
     463,     4,   441,     5,   226,  1217,  1218,   615,   226,  -725,
    1914,  1915,  1916,    34,   930,    18,    19,   900,   755,   756,
     225,   217,    35,     6,     7,     8,     9,  1270,    36,  1272,
     513,   481,   514,   515,   516,  1278,   931,  1512,   487,  1935,
       4,  1100,     5,  1363,  1819,   765,  1321,  1322,   224,   218,
     281,     4,    37,     5,   913,   913,   913,   913,   913,  -734,
    1585,   913,   932,   224,    34,   933,   755,   756,  1173,     3,
    1174,  -266,     4,    35,     5,  -735,  1234,  1196,  1224,    36,
     985,  1198,   572,  1598,  1130,  1513,   913,  1514,   969,  1500,
     991,   225,  1501,   986,     6,     7,     8,     9,   573,  1323,
    1324,  1618,   765,    37,   993,   913,   225,   574,   213,  1515,
     509,   510,   511,   575,   576,   761,  1383,  1579,  1052,   371,
     900,   900,   900,   900,   900,   214,  1053,   900,  1070,   220,
    1698,  1699,  1700,   765,  1701,  1561,  1562,   221,   851,   852,
    1763,  1646,  1647,  1685,  1686,  1637,  1068,  1638,  1517,   256,
     257,   258,   900,  1766,  1069,   217,  1072,  1516,  1642,  1074,
    1734,  1096,   765,   223,  1423,  1003,  1004,  1005,  1006,  1764,
    1101,   900,  1166,  1166,  1166,  1166,  1166,  1722,  1166,  1166,
     850,   851,   852,   218,   150,   151,   152,  1429,  1429,  1102,
     371,  2027,  2028,  2029,  1105,   135,   766,   136,  1780,  1735,
    1106,   213,   137,   213,   138,   371,     3,  1107,   139,     4,
    1110,     5,  1954,  1955,  1446,  1446,   859,  1119,  1112,   898,
     898,   898,   898,   898,   898,   898,   898,   898,   898,   898,
    1134,     6,     7,     8,     9,   465,   841,   842,   843,   367,
    1718,  1431,  1432,   213,  1122,  1135,  1522,   140,  1523,   141,
      18,    19,  1158,  1136,     3,  1145,  1146,     4,  1147,     5,
     467,  1164,  1170,   220,  1171,  1462,  1464,  1480,  1488,  1506,
    1518,   221,  -937,  1172,  1177,    18,    19,  -938,  1183,     6,
       7,     8,     9,  1760,  1184,  1185,  1186,  1465,  1481,  1489,
    1507,  1519,  1188,  1189,   859,  1195,  1197,   223,  1219,    34,
    1090,  1993,  1805,  1220,    88,  1803,  1225,  1546,    35,  1804,
    1231,    89,   472,    90,    36,    91,  1221,  1215,    92,    93,
      94,  1236,    95,  1244,    34,  1245,  1818,    18,    19,  1553,
    1554,   926,   765,    35,  1736,  1246,  1247,  1248,    37,    36,
    1080,   714,  1083,   715,  1860,   716,   717,  1984,  1256,  1551,
    1552,  1257,  1825,   718,   719,   740,  1258,  1259,  1260,   214,
    1261,  1265,  1802,    37,   367,  1524,  1311,  1268,   213,  1569,
      18,    19,  1575,  1310,  1580,  1308,    34,  1586,  1329,  1307,
    1309,  1626,  1336,  1124,  1337,    35,   720,   898,  1312,   217,
    1570,    36,  1319,  1576,   224,  1581,  1320,   367,  1587,   898,
    1327,   213,  1328,   765,   913,   913,   913,   913,   913,   913,
     913,   913,   913,   913,   913,    37,  1331,   218,  1834,    34,
    1295,  1296,  1297,  1298,  1932,  1338,  1625,  1627,    35,  1300,
    1301,  1302,  1303,  1304,    36,  1339,  1346,   225,  1351,   367,
     870,  1363,  1362,   213,   898,  1771,  1772,  1773,  1774,  1775,
     553,   554,   214,  1370,   214,  1372,  1375,  1380,    37,  1399,
    1404,  1962,   898,   898,   555,  1964,   556,   557,   558,  1405,
     900,   900,   900,   900,   900,   900,   900,   900,   900,   900,
     900,  1406,   217,  1100,   217,  1525,  1963,  1856,  1407,   559,
     560,   561,   518,   519,   214,  1409,  1418,   220,  1681,   213,
     520,   521,   522,   523,   524,   221,   432,   433,   434,   435,
     218,  1667,   218,  1426,  1412,  1681,   213,  1427,  1428,  1675,
    1676,  1677,  1678,  1679,   217,  1443,  1460,  1544,   224,  1534,
     367,   223,    96,  1547,   213,  1080,   226,  1704,  1705,  1706,
    1558,  1535,  1536,  1549,  1550,  2009,  1567,    97,  1573,  1713,
    1714,  1592,   218,  1593,  1607,  1985,  1597,  1610,  1480,  1488,
    1506,  1518,  1616,    98,  1617,  1628,  1629,  1630,    99,  1619,
     100,   225,   913,  1631,  2026,  1633,  1635,  1649,  1222,  1481,
    1489,  1507,  1519,  1648,   913,  2031,  1056,  1057,   765,  2033,
     220,  1659,   220,  1738,  1748,  1755,  1673,  1674,   221,  1058,
     221,   213,  1672,  1568,  1688,   475,  1684,  1059,   747,  1961,
    2032,  1717,  1710,  1715,  1739,  1749,  1756,  1728,  1729,   214,
      18,    19,  1716,  1060,   223,  1731,   223,  1777,  1759,   913,
    1769,  1779,   220,  1785,     3,  1790,  1100,     4,   900,     5,
     221,  1795,  1794,   213,  1798,  1800,   914,   913,   913,   217,
     900,  1977,   214,  1813,  1828,  1787,   914,   914,  1837,     6,
       7,     8,     9,  1846,  1839,  1848,   223,  1857,  1851,    34,
     226,  1864,   385,  1859,  1863,  1865,  1867,   218,    35,  1870,
    1873,  1874,   217,  1885,    36,  1875,  1876,  1877,  1652,  1654,
    1654,  1657,  1881,  1882,   214,   900,  1883,  1917,   385,  1884,
    1919,  1931,  1936,  1930,  1939,  1947,  1927,  1948,    37,  1815,
     218,  1816,  1817,   900,   900,  1949,  1959,  -220,  1843,  1967,
    1976,  1972,  1995,  2000,   217,  1820,  2001,  2004,  1849,   738,
     738,  1822,  -221,  2030,  -469,  1852,  2023,  1193,  1824,   997,
    1545,  1827,  1061,  1062,  1063,   676,  1833,    70,  1529,  1712,
     214,   937,   218,  1738,  1748,  1755,  1888,   220,   686,   687,
     688,     3,   224,  2022,     4,   221,     5,   214,   367,  2003,
    1887,  1950,   213,  1951,  1739,  1749,  1756,   477,  1952,  1942,
     217,   563,  1953,   564,  1996,   214,     6,     7,     8,     9,
     220,   223,    18,    19,   411,  1656,   213,   217,   221,   934,
     898,   565,   384,   418,  1641,   225,  1797,  1150,   218,   566,
     567,     3,   568,  1137,     4,   217,     5,  1886,   213,   757,
    1788,  1765,   569,   570,   223,   218,  1892,   213,   384,  1872,
     737,   737,   220,  1187,  1832,   936,     6,     7,     8,     9,
     221,    34,     3,   218,  1941,     4,  1415,     5,  1980,  1416,
      35,  1417,   214,  1434,  1437,   224,    36,   224,  1908,  1194,
    1913,  1200,   150,   151,   152,   736,   223,     6,     7,     8,
       9,  1920,  1921,  1456,  1922,  1923,  1924,  1925,  1926,  1266,
      37,  1928,   217,   697,  1396,  1620,  1599,   540,   220,   541,
     949,  1623,  1681,   213,   214,   925,   221,   224,   225,   947,
     225,   458,  1734,   950,   226,   220,  2024,   542,   745,     3,
     218,  1049,     4,   221,     5,   543,   544,   545,   546,  1958,
     948,  1280,   223,   220,   217,   749,   750,  1965,  1966,  1306,
       0,   221,   755,   756,     6,     7,     8,     9,     0,   223,
     225,  1735,     0,   367,     0,     0,  1907,   213,  1912,     0,
       0,     0,   218,  1752,     0,     0,     0,   223,     0,     0,
       0,     0,  1998,   213,     0,     0,     0,     0,   765,     0,
       0,  1464,  1488,  1506,  1518,     0,     0,     0,     0,  1569,
    1575,  1580,  1586,  1991,     0,   913,  1997,     0,     0,  1999,
     220,     0,  1465,  1489,  1507,  1519,     0,   226,   221,   226,
    1570,  1576,  1581,  1587,  2007,  1392,     0,     0,     0,     0,
    2010,  2011,  2012,  2013,  2014,  1738,  1748,  1755,  2018,  2019,
    2020,  2021,   224,   214,   223,     0,     0,     0,     0,     0,
       0,     0,   220,     0,     0,  2025,  1739,  1749,  1756,   371,
     221,     0,     0,     0,     0,   914,     0,   214,     0,     0,
       0,   900,     0,   217,     0,   224,  2034,  2035,  2036,     0,
       0,     0,     0,     0,     0,   225,   223,     0,     0,   214,
       0,     0,  1994,     0,     0,    73,  1736,   217,   214,     0,
       0,   218,    74,     0,    75,     0,     0,  1167,  1912,    76,
      77,    78,     0,    79,     0,   765,     0,   224,   225,   217,
       0,     0,     0,     0,     0,   218,     0,  1753,   217,     0,
    1992,     0,     0,  1832,     0,  1466,  1483,  1493,  1509,  1521,
       0,     0,     0,     0,     0,     0,     0,   218,     0,     0,
       0,     0,     0,     0,     0,     0,   218,     0,     0,     0,
     225,     0,     0,     0,   214,   765,     0,     0,   914,   914,
     914,   914,   914,   224,     0,   914,     0,     0,     0,     0,
    2015,   220,     0,     0,   371,     0,     0,     0,     0,   221,
     224,     0,     0,     0,   217,     0,   765,     0,     0,     0,
     914,     0,     0,     0,     0,   220,     0,     0,   224,     0,
       0,  1754,     0,   221,     0,   223,   225,   371,   214,   914,
       0,     0,   218,     0,     0,  1083,     0,   220,     0,     0,
       0,     0,     0,   225,   214,   221,   220,     0,  1571,   223,
       0,  1577,     0,  1582,   221,     0,  1588,     0,   217,     0,
       0,   225,     0,     0,     0,     0,     0,     3,     0,   371,
       4,   223,     5,   765,   217,     0,     0,     0,     0,     0,
     223,     0,     0,     0,     0,   224,   218,     0,  1574,     0,
       0,     0,     6,     7,     8,     9,     0,     0,     0,     0,
       0,  1392,   218,     0,   926,  1095,     0,  1097,     0,     0,
       0,     3,   220,     0,     4,     0,     5,     0,     0,     0,
     221,     0,     0,  1113,  1114,   226,  1118,   224,   225,     0,
    1120,  1121,     0,    80,     0,     0,     6,     7,     8,     9,
       0,     0,   226,     0,     0,     0,   223,  1468,    81,     0,
       0,     0,     0,     0,     0,     0,  1469,  1155,     0,  1157,
     371,  1470,     0,  1471,    82,  1472,   220,     0,     0,    83,
     225,    84,     0,     0,   221,     0,     3,     0,     0,     4,
       0,     5,   220,     0,     0,     0,     0,     0,     0,     0,
     221,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     223,     6,     7,     8,     9,     0,     0,     3,     0,     0,
       4,     0,     5,     0,     0,     0,   223,     0,     0,  1191,
       3,     0,  1192,     4,     0,     5,     0,   226,     0,     0,
       0,     0,     6,     7,     8,     9,     0,  1483,  1493,  1509,
    1521,     0,     0,  1468,     0,     6,     7,     8,     9,     0,
       0,     0,  1469,     0,     0,     0,   224,  1470,     0,  1471,
       0,  1472,     0,     0,     0,     0,     0,     0,     0,   226,
    1473,     0,  1740,  1750,  1757,     0,     0,    60,     0,     0,
     224,  1167,  1167,  1167,  1167,  1167,     0,  1167,  1167,  1229,
    1230,     0,     0,     0,     0,     0,  1430,  1430,     0,   225,
     526,   527,   224,     0,   528,     0,   273,   274,   275,   276,
       0,   224,     0,     0,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   225,     0,     0,     0,     0,   914,   914,
     914,   914,   914,   914,   914,   914,   914,   914,   914,     0,
     391,     0,     0,     0,     0,   225,     0,     0,   401,   402,
     403,   404,     0,     0,   225,     0,     3,     0,     0,     4,
       0,     5,     0,   538,     0,     0,  1473,     0,     0,     0,
       0,   437,     0,     0,     0,  1474,     0,   224,     0,     0,
       0,     6,     7,     8,     9,     0,   595,   460,     0,     0,
    1475,     0,   469,   470,   471,   596,     0,   474,   371,     0,
     479,   765,     0,     0,     0,     0,  1476,     0,     0,     0,
     597,  1477,     0,  1478,   598,     0,  1981,     0,   599,   600,
     225,     0,   226,   601,   602,   603,   604,   605,     0,     0,
       0,   224,  1740,  1750,  1757,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   226,   765,     0,   224,     0,     0,
       0,     0,     0,   226,     0,     0,     0,  1080,     0,     0,
    1479,     0,     0,     0,  1350,     0,     0,  1752,  1353,     0,
       0,  1474,     0,     0,   225,     0,     0,  1366,  1367,  1368,
       0,     0,  1371,     0,  1373,     0,  1475,     0,     0,     0,
     225,     0,     0,     0,  1381,     0,   914,     0,     0,     0,
       0,     0,  1476,     0,     0,     0,     0,  1477,   914,  1478,
     765,     0,     0,     0,     0,     0,  1083,     0,     0,   226,
       0,     0,     0,     0,     0,  1989,     0,     0,  1408,     0,
    1410,     0,     0,     0,     0,     0,  1411,   722,   723,   724,
       3,   765,     0,     4,     0,     5,     0,     0,     0,  1424,
       0,  1425,     3,   914,   765,     4,  1719,     5,     3,     0,
    1433,     4,  1435,     5,     0,     6,     7,     8,     9,  1990,
       0,   914,   914,   371,     0,     0,     0,     6,     7,     8,
       9,     0,     0,     6,     7,     8,     9,     0,     0,   226,
       0,  1495,   442,   444,     0,     0,   447,     0,   449,     0,
       0,   453,   454,     0,     0,   462,   464,   466,   468,     0,
       0,     0,   473,     0,     0,   476,   478,     0,     0,     0,
       0,  1753,     0,   484,     0,     0,     0,  1742,     0,     0,
       0,     0,     0,     0,  1743,     0,     0,     0,  1496,  1497,
    1498,  1499,     0,  1500,     0,     0,  1501,     0,     0,     0,
    1466,  1493,  1509,  1521,     0,     0,     0,     0,  1571,  1577,
    1582,  1588,     0,  1502,     0,   943,   944,   945,     0,  1752,
    1744,     0,     0,    50,     0,     0,     0,     0,     0,     0,
    1893,     0,     0,    61,    50,    50,    64,    64,    64,    68,
     765,     0,    50,     0,  1740,  1750,  1757,  1689,   959,     0,
       0,     0,     0,     0,  1745,  1836,     0,     0,     0,     0,
       0,  1503,  1010,     0,     0,     0,     0,     0,     0,     0,
       0,  1690,  1691,  1590,  1591,   968,     0,  1011,     0,     0,
       0,     0,     0,   746,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,  1603,     0,   392,    50,    64,    64,
      64,    68,  1609,     0,     0,   668,   669,     0,    50,   670,
     407,   412,   415,    50,   420,    64,    64,   425,     0,   407,
     407,   407,   407,     0,    64,     0,   671,   438,     0,    50,
       0,  1632,    64,    64,     0,    68,     0,     0,    64,     0,
    1012,     0,     0,     0,     3,     0,     0,     4,  1634,     5,
    1636,   786,     0,     0,     0,  1746,     0,   480,    50,    64,
      64,     0,     0,    64,     0,    50,  1504,     0,     0,     6,
       7,     8,     9,  1753,     0,     0,     0,     0,     0,     0,
     747,   303,     0,  1495,   150,   151,   152,  1692,     0,     0,
       0,   880,     0,     0,     0,   881,     0,   305,     0,   882,
       0,     0,   306,     0,     0,   883,     0,  1693,  1694,   793,
    1013,     0,     0,  1014,  1015,  1016,  1017,  1018,  1019,  1020,
    1021,  1022,  1023,     0,   765,  1894,     0,     0,     0,   886,
    1496,  1497,  1498,  1499,     0,  1500,   765,   672,  1501,  1747,
       0,  1895,   765,     0,     0,     0,  1896,     0,  1897,     0,
       0,  1505,     0,     0,     0,  1502,     0,  2017,     0,   914,
       0,   673,   674,   675,   676,   677,   678,   748,   679,   680,
     681,   682,   683,   684,   685,     0,     0,   686,   687,   688,
       0,     0,     0,     0,     0,   967,     0,     0,     0,     0,
       0,     3,     0,     0,     4,     0,     5,     0,   689,     0,
       0,     0,     0,  1503,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   145,  1767,     0,     6,     7,     8,     9,
     146,   147,     0,     0,     0,   287,   148,   288,     0,     0,
       0,     0,  1781,     0,     0,     0,     0,     3,     0,     0,
       4,   289,     5,     0,     0,     0,     0,     0,     0,     0,
       0,   290,   291,     0,     0,  1789,   292,   796,     0,     0,
     797,   798,     6,     7,     8,     9,     0,   293,   294,   295,
     296,   297,   298,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1484,     0,     0,     0,   299,     0,   300,     0,
       0,   149,   150,   151,   152,   800,   801,   153,     0,   154,
       0,     0,  1485,   155,     0,     0,     0,   156,  1504,     0,
       0,     0,     0,   157,     0,     0,     0,     0,     0,     0,
       0,  1011,     0,   303,  1742,     0,     0,     0,     0,   158,
       0,  1743,     0,     0,   159,     0,   209,   160,     0,   305,
       0,     0,   161,     0,   306,   162,     0,     0,   163,   164,
    1486,     0,     0,   165,     0,     0,   166,     0,   167,     0,
       0,     0,     0,     0,     0,   965,     0,  1744,     0,     0,
       0,     0,    64,     0,     0,     0,     0,     0,   765,     0,
     168,   169,     0,   971,  1012,   972,     0,   973,     0,   974,
       0,     0,     0,  1721,   978,     0,     0,   980,     0,   981,
       0,  1745,     0,     0,     0,     0,     0,    64,     0,     0,
       0,     0,  1866,     0,     0,     0,   170,   171,   172,   173,
       0,     0,     0,     0,     0,   174,   175,     0,     0,   176,
     177,   301,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,     0,  1013,   302,     0,  1014,  1015,  1016,
    1017,  1018,  1019,  1020,  1021,  1022,  1023,     0,     0,     0,
     303,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     304,     0,     0,     0,     0,     0,   305,     0,     0,     0,
       0,   306,     0,     0,     0,     0,     0,   201,   202,     0,
     307,     0,  1746,   308,   309,   310,   311,     0,     0,     0,
     312,     0,     0,     0,   313,   314,   203,     0,     0,     0,
     204,   205,     0,     3,     0,   765,     4,     0,     5,   315,
       0,     0,   206,   207,     0,     0,     0,     0,     0,   316,
    1487,   208,     0,     0,   209,   145,     0,     0,     6,     7,
       8,     9,   146,   147,     0,     0,     0,   287,   148,   288,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   765,     0,   289,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   290,   291,     0,  1835,     0,   292,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   293,
     294,   295,   296,   297,   298,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1484,     0,     0,     0,   299,     0,
     300,     0,     0,   149,   150,   151,   152,     0,     0,   153,
       0,   154,     0,     0,  1485,   155,     0,     0,     0,   156,
       0,     0,     0,     0,     0,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,     0,     0,     0,   159,     0,     0,   160,
       0,     0,     0,     0,   161,     0,     0,   162,     0,     0,
     163,   164,  1486,     0,     0,   165,     0,     0,   166,     0,
     167,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     0,     0,     4,     0,     5,
       0,     0,   168,   169,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       7,     8,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1495,     0,     0,     0,     0,   170,   171,
     172,   173,     0,     0,     0,     0,     0,   174,   175,     0,
       0,   176,   177,   301,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,     0,     0,   302,     0,     0,
    1496,  1497,  1498,  1499,     0,  1500,     0,     0,  1501,     0,
       0,     0,   303,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   304,     0,     0,  1502,     0,     0,   305,     0,
       0,     0,     0,   306,     0,     0,     0,     0,     0,   201,
     202,     0,   307,     0,     0,   308,   309,   310,   311,     0,
       0,     0,   312,     0,     0,     0,   313,   314,   203,     0,
       0,     0,   204,   205,     0,     0,     0,   765,     0,     0,
       0,   315,     0,  1503,   206,   207,     0,     0,     0,     0,
       0,   316,  1720,   208,     3,     0,   209,     4,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1264,     0,     0,     0,     0,   145,     0,     0,     6,
       7,     8,     9,   146,   147,     0,     0,     0,   287,   148,
     288,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   289,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   290,   291,     0,     0,     0,   292,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     293,   294,   295,   296,   297,   298,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1484,     0,     0,  1504,   299,
       0,   300,     0,     0,   149,   150,   151,   152,     0,     0,
     153,     0,   154,   303,     0,  1485,   155,     0,     0,     0,
     156,     0,     0,     0,     0,     0,   157,     0,     0,   305,
       0,     0,     0,     0,   306,     0,     0,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,   159,     0,     0,
     160,     0,     0,     0,     0,   161,     0,     0,   162,     0,
       0,   163,   164,  1486,     0,     0,   165,     0,   765,   166,
       0,   167,     0,     0,     0,     0,     0,     0,     0,     3,
       0,     0,     4,  1983,     5,     0,     0,     0,     0,     0,
       0,     0,  1025,   168,   169,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     7,     8,     9,  1026,  1027,
    1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,
    1038,  1039,  1040,  1041,  1042,     0,     0,     0,     0,   170,
     171,   172,   173,     0,     0,     0,     0,     0,   174,   175,
       0,     0,   176,   177,   301,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,  1742,     0,   302,     0,
       0,     0,     0,  1743,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   304,     0,     0,     0,     0,     0,   305,
       0,   668,   669,     0,   306,   670,     0,     0,     0,  1744,
     201,   202,     0,   307,     0,     0,   308,   309,   310,   311,
       0,     0,   671,   312,     0,     0,     0,   313,   314,   203,
       0,     0,     0,   204,   205,     0,     0,     4,   765,     5,
       0,     0,   315,  1745,     0,   206,   207,     0,     0,     0,
       0,     0,   316,  1982,   208,     0,   145,   209,     0,     0,
       0,     0,     0,   146,   147,     0,     0,     0,   287,   148,
     288,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   289,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   290,   291,     0,     0,     0,   292,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     293,   294,   295,   296,   297,   298,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   299,
       0,   300,     0,   672,   149,   150,   151,   152,     0,     0,
     153,     0,   154,     0,  1746,     0,   155,     0,     0,     0,
     156,     0,     0,     0,     0,     0,   157,   673,   674,   675,
     676,   677,   678,     0,   679,   680,   681,   682,   683,   684,
     685,     0,   158,   686,   687,   688,     0,   159,     0,     0,
     160,     0,     0,     0,     0,   161,     0,     0,   162,     0,
       0,   163,   164,     0,   689,     0,   165,     0,     0,   166,
       0,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   765,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   168,   169,    10,     0,     0,  2016,     0,
       0,     0,    11,     0,    12,     0,    13,     0,     0,    14,
      15,    16,     0,    17,     0,     0,     0,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   170,
     171,   172,   173,     0,     0,     0,     0,     0,   174,   175,
       0,     0,   176,   177,   301,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,    34,     0,   302,     0,
       0,   785,     0,     0,     0,    35,     0,     0,     0,     0,
       0,    36,     0,   303,     0,     0,     0,     0,     0,   145,
       0,     0,     0,   304,     0,     0,     0,   147,     0,   305,
       0,     0,   148,     0,   306,    37,     0,     0,     0,     0,
     201,   202,     0,   307,     0,     0,   308,   309,   310,   311,
       0,     0,     0,   312,     0,     0,     0,   313,   314,   203,
       0,     0,     0,   204,   205,   786,     0,     0,     0,     0,
       0,     0,   315,     0,     0,   206,   207,     0,     0,   787,
       0,   788,   316,  1624,   208,     0,     0,   209,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   149,   150,   151,
     152,     0,     0,   153,     0,   789,     0,     0,     0,   790,
       0,     0,     0,   791,     0,     0,     0,     0,     0,   792,
       0,     0,     0,   793,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   158,     0,     0,     0,     0,
     159,     0,     0,   794,     0,     0,     0,     0,   161,     0,
       0,   162,     0,    38,   163,   164,     0,     0,     0,   165,
       0,     0,   166,     0,   167,     0,     0,     0,    39,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    40,     0,   168,   169,     0,    41,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   104,     0,     0,     0,     0,     0,     0,
     105,   106,   107,   108,     0,     0,   109,   110,     0,   111,
     112,   113,   795,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,  1092,
       0,   200,   115,     0,   116,   117,   118,     0,     0,     0,
       0,   796,     0,     0,   797,   798,     0,   145,     0,     0,
       0,     0,     0,     0,     0,   147,     0,   799,     0,     0,
     148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,   202,     0,     0,     0,     0,   800,
     801,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   203,   786,     0,     0,   204,   205,     0,     0,
       0,     0,     0,     0,     0,     0,   802,   803,     0,   664,
       0,     0,     0,     0,     0,     0,     0,   804,     0,     0,
     209,     0,     0,     0,     0,   149,   150,   151,   152,     0,
       0,   153,     0,   789,     0,     0,     0,   790,     0,     0,
       0,   791,     0,     0,     0,     0,     0,  1093,     0,     0,
       0,   793,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158,     0,     0,     0,     0,   159,     0,
       0,  1094,     0,     0,     0,     0,   161,     0,     0,   162,
       0,     0,   163,   164,     0,     0,     0,   165,     0,     0,
     166,     0,   167,     0,     0,     0,     0,     0,     0,     0,
       0,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   168,   169,   120,     0,     0,     0,
       0,   121,   122,   123,   124,     0,     0,     0,     0,     0,
       0,     0,   125,     0,     0,     0,     0,   126,     0,   127,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     795,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,  1156,     0,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   796,
       0,     0,   797,   798,     0,   145,     0,     0,     0,     0,
       0,     0,     0,   147,     0,     0,     0,     0,   148,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,   202,     0,     0,     0,     0,   800,   801,     0,
       0,     0,     0,     0,     0,     0,     0,   658,     0,     0,
     203,   786,     0,     0,   204,   205,     0,     0,     0,     0,
       0,     0,     0,     0,   802,   803,     0,   664,     0,     0,
       0,     0,     0,   659,     0,   804,   660,     0,   209,     0,
       0,     0,     0,   149,   150,   151,   152,     0,     0,   153,
       0,   789,     0,   661,     0,   790,     0,     0,     0,   791,
       0,     0,     0,     0,     0,  1093,     0,     0,     0,   793,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,     0,     0,     0,   159,     0,     0,  1094,
       0,     0,     0,     0,   161,     0,     0,   162,     0,     0,
     163,   164,     0,     0,     0,   165,     0,     0,   166,     0,
     167,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,   169,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   795,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,  1190,     0,   200,   662,     0,
       0,     0,   201,   202,     0,     0,     0,   796,     0,     0,
     797,   798,   663,   145,     0,     0,     0,     0,     0,     0,
       0,   147,     0,     0,     0,     0,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   664,   201,
     202,     0,     0,     0,     0,   800,   801,     0,     0,     0,
       0,     0,     0,     0,     0,   744,     0,     0,   203,   786,
       0,     0,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,   802,   803,     0,   664,     0,     0,     0,     0,
       0,   659,     0,   804,   660,     0,   209,     0,     0,     0,
       0,   149,   150,   151,   152,     0,     0,   153,     0,   789,
       0,   661,     0,   790,     0,     0,     0,   791,     0,     0,
       0,     0,     0,  1093,     0,     0,     0,   793,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
       0,     0,     0,     0,   159,     0,     0,  1094,     0,     0,
       0,     0,   161,     0,     0,   162,     0,     0,   163,   164,
       0,     0,     0,   165,     0,     0,   166,     0,   167,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     168,   169,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   795,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,  1352,     0,   200,   662,     0,     0,     0,
     201,   202,     0,     0,     0,   796,     0,     0,   797,   798,
     663,   145,     0,     0,     0,     0,     0,     0,     0,   147,
       0,     0,     0,     0,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   664,   201,   202,     0,
       0,     0,     0,   800,   801,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   203,   786,     0,     0,
     204,   205,     0,     0,     0,     0,     0,     0,     0,     0,
     802,   803,     0,   664,     0,     0,     0,     0,     0,     0,
       0,   804,     0,     0,   209,     0,     0,     0,     0,   149,
     150,   151,   152,     0,     0,   153,     0,   789,     0,     0,
       0,   790,     0,     0,     0,   791,     0,     0,     0,     0,
       0,  1093,     0,     0,     0,   793,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,     0,     0,  1094,     0,     0,     0,     0,
     161,     0,     0,   162,     0,     0,   163,   164,     0,     0,
       0,   165,     0,     0,   166,     0,   167,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   168,   169,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   795,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,     0,     0,   200,     0,   873,   874,   875,   876,   877,
     878,     0,     0,   796,     0,   879,   797,   798,     0,   858,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,   202,     0,     0,     0,
       0,   800,   801,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,   786,     0,     0,   204,   205,
       0,     0,     0,     0,     0,     0,     0,     0,   802,   803,
       0,   664,     0,     0,     0,     0,  1123,     0,     0,   804,
       0,     0,   209,     0,     0,     0,     0,   149,   150,   151,
     152,     0,     0,     0,     0,   880,     0,     0,     0,   881,
       0,     0,     0,   882,     0,     0,     0,     0,     0,   883,
       0,     0,     0,   793,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   786,   884,     0,     0,     0,     0,
     885,     0,     0,   886,     0,     0,     0,     0,   887,     0,
       0,   888,     0,     0,   889,   890,     0,     0,     0,   891,
       0,     0,   892,     0,   893,     0,   149,   150,   151,   152,
       0,     0,     0,     0,   880,     0,     0,     0,   881,     0,
       0,     0,   882,     0,     0,     0,   894,   895,   883,     0,
       0,     0,   793,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   884,     0,     0,     0,     0,   885,
       0,     0,   886,     0,     0,  1123,     0,   887,     0,     0,
     888,     0,     0,   889,   890,     0,     0,     0,   891,     0,
       0,   892,     0,   893,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   894,   895,     0,     0,     0,
       0,     0,     0,   786,     0,     0,     0,     0,     0,     0,
       0,   796,     0,     0,   797,   798,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   919,   858,     0,     0,     0,
       0,     0,     0,     0,     0,   149,   150,   151,   152,     0,
       0,     0,     0,   880,     0,     0,     0,   881,     0,   800,
     801,   882,   896,     0,     0,     0,     0,   883,     0,     0,
       0,   793,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   786,   884,     0,     0,   802,   803,   885,     0,
     796,   886,     0,   797,   798,   316,   887,   897,     0,   888,
     209,     0,   889,   890,     0,     0,     0,   891,     0,     0,
     892,     0,   893,     0,   149,   150,   151,   152,     0,     0,
       0,     0,   880,     0,     0,     0,   881,     0,   800,   801,
     882,   896,     0,     0,   894,   895,   883,     0,     0,     0,
     793,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   884,     0,     0,   802,   803,   885,     0,     0,
     886,     0,     0,     0,   316,   887,   897,     0,   888,   209,
       0,   889,   890,     0,     0,     0,   891,     0,     0,   892,
       0,   893,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   894,   895,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   796,
       0,     0,   797,   798,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   800,   801,     0,
     896,   145,     0,     0,     0,     0,     0,     0,   146,   147,
       0,     0,     0,   287,   148,   288,     0,     0,     0,     0,
       0,     0,     0,     0,   802,   803,     0,     0,   796,   289,
       0,   797,   798,     0,     0,   897,     0,     0,   209,   290,
     291,     0,     0,     0,   292,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   293,   294,   295,   296,   297,
     298,     0,     0,     0,     0,     0,   800,   801,     0,   896,
       0,     0,     0,     0,   299,     0,   300,     0,     0,   149,
     150,   151,   152,     0,     0,   153,     0,   154,     0,     0,
       0,   155,     0,   802,   803,   156,     0,     0,     0,     0,
       0,   157,   920,     0,   897,     0,     0,   209,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   159,     0,     0,   160,     0,     0,     0,     0,
     161,     0,     0,   162,     0,     0,   163,   164,     0,     0,
       0,   165,     0,     0,   166,     0,   167,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   168,   169,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   170,   171,   172,   173,     0,     0,
       0,     0,     0,   174,   175,     0,     0,   176,   177,   301,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,     0,     0,   302,   145,     0,     0,     0,     0,     0,
       0,   146,   147,     0,     0,     0,     0,   148,   303,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   304,     0,
       0,     0,     0,     0,   305,     0,     0,     0,     0,   306,
       0,     0,     0,     0,     0,   201,   202,     0,   307,     0,
       0,   308,   309,   310,   311,     0,     0,     0,   312,     0,
       0,     0,   313,   314,   203,     0,     0,     0,   204,   205,
       0,     0,     0,     0,     0,     0,     0,   315,     0,     0,
     206,   207,   149,   150,   151,   152,     0,   316,   153,   208,
     154,     0,   209,     0,   155,     0,     0,     0,   156,     0,
       0,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,   159,     0,     0,   160,     0,
       0,     0,     0,   161,     0,     0,   162,     0,     0,   163,
     164,     0,     0,     0,   165,     0,     0,   166,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   168,   169,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   145,     0,     0,     0,     0,     0,     0,
     146,   147,     0,     0,     0,     0,   148,   170,   171,   172,
     173,     0,     0,     0,     0,     0,   174,   175,     0,     0,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,     0,     0,   200,     0,     0,     0,
       0,     0,     0,     0,     0,  1889,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   150,   151,   152,     0,     0,   153,     0,   154,
       0,     0,     0,   155,     0,     0,     0,   156,   201,   202,
       0,     0,     0,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   203,     0,   158,
       0,   204,   205,     0,   159,     0,     0,   160,     0,     0,
       0,     0,   161,   206,   207,   162,     0,     0,   163,   164,
     316,     0,   208,   165,     0,   209,   166,     0,   167,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   145,
     168,   169,     0,     0,     0,     0,   146,   147,     0,     0,
       0,     0,   148,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   170,   171,   172,   173,
       0,     0,     0,     0,     0,   174,   175,     0,     0,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,     0,     0,   200,     0,   149,   150,   151,
     152,     0,     0,   153,     0,   154,     0,     0,     0,   155,
       0,     0,     0,   156,     0,     0,     0,     0,     0,   157,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   158,     0,   201,   202,     0,
     159,     0,     0,   160,     0,     0,     0,     0,   161,     0,
       0,   162,     0,     0,   163,   164,   203,     0,     0,   165,
     204,   205,   166,     0,   167,     0,     0,     0,     0,     0,
       0,     0,   206,   207,     0,     0,     0,     0,     0,     0,
       0,   208,     0,     0,   209,     0,   168,   169,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   170,   171,   172,   173,     0,     0,     0,     0,
       0,   174,   175,     0,     0,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,   200,   145,     0,     0,     0,     0,     0,     0,     0,
     147,     0,     0,     0,     0,   148,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,   202,     0,     0,     0,   786,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   203,     0,     0,     0,   204,   205,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   206,   207,
     149,   150,   151,   152,     0,     0,   153,   208,   789,     0,
     209,     0,   790,     0,     0,     0,   791,     0,     0,     0,
       0,     0,  1093,     0,     0,     0,   793,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,   159,     0,     0,  1094,     0,     0,     0,
       0,   161,     0,     0,   162,     0,     0,   163,   164,     0,
       0,     0,   165,     0,     0,   166,     0,   167,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   168,
     169,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   795,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,     0,     0,   200,   858,     0,     0,     0,     0,
       0,     0,     0,     0,   796,     0,     0,   797,   798,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   201,   202,     0,     0,
       0,   786,   800,   801,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   203,     0,     0,     0,   204,
     205,     0,     0,     0,     0,     0,     0,     0,     0,   802,
     803,     0,   664,   149,   150,   151,   152,     0,     0,     0,
     804,   880,     0,   209,     0,   881,     0,     0,     0,   882,
       0,     0,     0,     0,     0,   883,     0,     0,     0,   793,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   884,     0,     0,     0,     0,   885,     0,     0,   886,
       0,     0,     2,     3,   887,     0,     4,   888,     5,     0,
     889,   890,     0,     0,     0,   891,     0,     0,   892,     0,
     893,     0,     0,     0,     0,     0,     0,     0,     6,     7,
       8,     9,     0,     0,     0,     0,     0,     0,     0,    10,
       0,     0,   894,   895,     0,     0,    11,     0,    12,     0,
      13,     0,     0,    14,    15,    16,     0,    17,     0,     0,
       0,    18,    19,    20,     0,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -357,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,     0,    35,
       0,     0,     0,     0,     0,    36,     0,   796,     0,   786,
     797,   798,     0,     0,     0,     0,     0,   293,   294,   295,
    1611,  1612,   298,     0,     0,     0,     0,     0,     0,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   150,   151,   152,   800,   801,     0,   896,   880,
       0,     0,     0,   881,     0,     0,     0,   882,     0,     0,
       0,     0,     0,   883,     0,     0,     0,   793,     0,     0,
       0,     0,   802,   803,     0,     0,     0,     0,   786,   884,
       0,   316,     0,   897,   885,     0,   209,   886,     0,     0,
       0,     0,   887,     0,     0,   888,     0,     0,   889,   890,
       0,     0,     0,   891,     0,     0,   892,     0,   893,     0,
     149,   150,   151,   152,     0,     0,     0,     0,   880,     0,
       0,     0,   881,     0,     0,     0,   882,     0,     0,     0,
     894,   895,   883,     0,     0,     0,   793,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    38,   884,     0,
       0,     0,     0,   885,     0,     0,   886,     0,     0,     0,
       0,   887,    39,     0,   888,     0,     0,   889,   890,     0,
       0,     0,   891,     0,     0,   892,     0,   893,    40,     0,
       0,     0,     0,    41,     0,    42,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   894,
     895,     0,     0,     0,     0,     0,     0,   786,     0,     0,
       0,     0,     0,     0,     0,   796,     0,     0,   797,   798,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1453,
     150,   151,   152,     0,     0,     0,     0,   880,     0,     0,
       0,   881,     0,   800,   801,   882,   896,     0,     0,     0,
       0,   883,     0,     0,     0,   793,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   884,     0,     0,
     802,   803,   885,     0,   796,   886,     0,   797,   798,     0,
     887,   897,     0,   888,   209,     0,   889,   890,     0,     0,
       0,   891,     0,     0,   892,     0,   893,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   800,   801,     0,   896,     0,     0,   894,   895,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   802,
     803,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     897,     0,     0,   209,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   796,     0,     0,   797,   798,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   800,   801,     0,   896,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   802,   803,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   897,
       0,     0,   209
};

static const yytype_int16 yycheck[] =
{
       1,   322,     3,    30,    30,   469,    52,   395,   319,   471,
     297,   397,   327,    37,   394,  1241,   363,    63,   204,   396,
     762,     1,    52,   626,    66,   343,    52,   208,  1248,   287,
     470,  1240,   349,    63,    36,   423,    32,    63,  1245,   479,
     426,  1261,  1246,   512,   377,    46,   729,  1083,   436,    35,
    1247,  1197,   895,    54,   363,  1346,   314,    58,   106,   629,
     108,   109,  1536,  1534,   112,  1535,   114,  1199,  1383,   117,
     118,  1512,   393,   121,   122,   123,   124,  1515,   336,  1440,
     128,  1356,   765,   131,   132,     4,   401,   804,   867,   363,
     868,   139,   869,   776,  1327,  1328,     4,   780,     7,   373,
     374,   865,   866,    95,     7,    23,  1124,  1125,    15,    16,
       7,   871,    44,  1131,   968,  1390,  1391,   432,    15,    16,
      17,    18,    56,  1557,   102,     7,     7,    88,    38,   699,
      91,   102,    57,    88,   123,     1,    91,  1358,     4,   102,
       6,   726,   102,   103,   104,   460,    23,     5,   178,   143,
    1744,    77,    78,   101,    66,  1854,   728,   282,   147,   474,
      26,    27,    28,    29,    23,   729,   727,  1762,   157,    76,
      77,    78,   102,   103,   104,    41,  1761,    43,   204,   282,
     102,   112,   208,    22,   297,    92,    93,    94,    83,  1207,
      85,    13,    83,    20,   102,   102,     7,     8,     9,   101,
     662,   124,    20,   110,   111,    20,     5,  1168,  1169,   116,
    1064,  1065,    56,   690,  1175,     1,    83,    79,     4,   281,
       6,   349,  1497,  1498,   349,   123,   354,   689,    83,  1438,
     137,   138,   123,    95,   141,   297,   349,    48,  1513,    50,
      26,    27,    28,    29,    56,   143,   349,   139,    59,   147,
       8,   113,    38,    64,  1108,    30,   147,    68,   102,   255,
     152,    46,   101,   102,    86,   261,    57,   950,   123,   263,
     264,   301,   749,   110,   111,   102,   168,    52,    88,  1978,
       4,    48,     6,   125,   102,    30,   112,   102,    63,   319,
     102,   112,   147,   319,   160,    53,    32,    33,    34,    56,
       1,  1510,   128,     4,   349,     6,  1532,    52,   150,   354,
      83,   132,    85,    30,     1,   246,   247,     4,    63,     6,
     283,   363,  1531,    83,   145,    26,    27,    28,    29,    44,
      45,   373,   374,  1927,   160,    52,   231,   363,  1098,    26,
      27,    28,    29,  1938,   390,   102,    63,   373,   374,   343,
      88,   299,  1937,   395,    41,   344,    43,   349,   281,   405,
     390,   283,   947,   317,   390,   263,   264,    61,    62,    88,
     723,   724,    66,   327,   335,   405,   354,   949,  1599,   405,
     335,   423,  1823,   354,   296,   297,   950,   948,  1826,   349,
       4,    92,     6,    30,   436,   103,   291,   299,   209,   333,
     334,    30,   102,   451,  1838,   242,   243,   265,  1262,   246,
    1264,   336,   337,   338,   280,    52,  1176,   349,  1101,  1102,
     312,    48,   280,    52,   354,    39,    63,    30,   354,   204,
     131,   350,  1641,   208,    63,  1796,   354,   349,   296,   349,
    1219,   350,  1220,   301,  1221,   343,   354,   350,  1889,    52,
     317,   318,   319,  1217,  1218,  1893,   353,  1174,   231,   204,
      63,    56,   272,   208,   274,  1597,   265,  1742,   350,   350,
      88,   292,   349,   160,  1317,  1949,  1947,   354,  1948,  1049,
    1795,   280,    88,   395,   350,   296,   297,   204,  1779,   300,
     349,   208,   350,  1639,    61,   354,   109,   296,  1731,   817,
       1,    52,   301,     4,   160,     6,   242,   102,   347,   102,
     123,   423,   299,   300,  1368,   354,  1370,  1371,   291,  1373,
      56,    83,   363,    85,   436,    26,    27,    28,    29,   998,
      97,  1000,   373,   374,   272,     8,   274,   539,   562,   525,
      41,   265,    43,   450,   319,   336,   337,   338,   125,   335,
     736,   350,   348,   272,   871,   274,   280,   317,   318,   319,
      38,    39,   349,   872,   350,   266,   102,   204,     8,   916,
     289,   208,   296,   150,   319,   204,     7,   301,   485,   208,
      53,   141,   163,  1619,    24,    76,   146,   168,   363,    20,
     943,   944,   945,   280,   141,  1613,   407,   621,   373,   374,
     411,   204,   319,   936,   415,   208,   959,   916,   329,   420,
     157,   332,   265,    53,   425,   390,   618,   109,   109,   280,
     160,  1085,   112,   897,   285,   286,  1644,   280,   348,  1091,
     405,   123,   123,   281,   335,   291,   292,   293,   294,   295,
     301,  1383,   916,   296,     5,   390,  1792,     8,  1088,   350,
    1114,   299,   300,  1395,   272,    44,   274,  1877,    30,   160,
     405,     5,   130,   350,     8,  1348,   272,  1874,   274,   231,
    1139,  1875,     7,   390,   164,   165,   487,   168,  1118,  1876,
      52,     1,   319,   112,     4,    20,     6,   102,   405,   870,
     319,    63,   232,   233,   234,     4,   125,     6,  1440,     8,
     349,    30,   112,   132,   182,   183,    26,    27,    28,    29,
     736,   126,   127,   123,   128,   125,   319,     7,   132,  1945,
     762,   150,     0,    52,   349,   721,     4,   156,     6,   291,
      20,  1334,    22,   143,    63,  1944,   762,   147,     1,   328,
     150,     4,   231,     6,   114,  1475,  1476,  1477,  1478,  1603,
     164,   165,   231,   390,  1663,  1664,  1665,  1666,   249,   129,
       7,   390,   337,    26,    27,    28,    29,  1082,   405,     1,
     794,   281,     4,    20,     6,    22,   405,   281,   804,   280,
     150,  1098,   102,   103,   104,   101,   156,   390,   112,  1253,
     792,    44,    83,  1255,    26,    27,    28,    29,     1,   101,
      30,     4,   405,     6,   128,   101,    59,    60,    40,   133,
     134,     4,    95,   215,  1254,  1073,     7,   219,   220,   221,
     230,   335,    52,    26,    27,    28,    29,   242,   311,    20,
     872,    22,   204,    63,   164,   165,   208,    40,   101,   865,
     866,   867,   868,   869,   870,   128,   872,   262,   263,   350,
      44,  1869,   226,   263,   264,   108,    88,    17,    90,  1176,
      92,   235,   236,    95,   117,   239,   240,   237,   238,  1216,
     123,   897,    18,  1191,   916,   204,  1223,    12,   132,   208,
     112,   346,   347,  1737,   132,    88,   353,    90,    22,    92,
     916,    25,    95,  1747,   147,   282,   283,  1806,  1807,  1808,
    1754,   184,   185,   186,   187,   188,   189,   231,    51,   112,
     164,   165,   150,   167,    15,    16,   164,   165,  1104,    44,
     921,   762,   160,   161,   925,   105,   106,   107,   160,  1783,
    1660,  1661,  1662,   343,    59,    60,    71,  1252,    15,    16,
      75,  1215,  1216,     4,   192,     6,     7,   319,  1222,  1223,
    1224,  1225,  1970,   299,   300,    90,    91,   160,    51,   871,
    1563,   736,    77,    78,    79,    80,    81,    82,     1,   349,
      44,     4,   107,     6,   204,    15,    16,   225,   208,   282,
    1834,  1835,  1836,   108,   349,    59,    60,   762,   299,   300,
     319,   736,   117,    26,    27,    28,    29,   999,   123,  1001,
     112,   136,   114,   115,   116,  1007,   349,    40,   143,  1863,
       4,  1197,     6,  1199,     8,   335,   110,   111,   390,   736,
      56,     4,   147,     6,   865,   866,   867,   868,   869,    44,
     350,   872,   349,   405,   108,   349,   299,   300,    20,     1,
      22,   349,     4,   117,     6,    44,    20,   858,    22,   123,
       7,   862,   125,  1364,  1796,    88,   897,    90,    44,    92,
     295,   390,    95,     8,    26,    27,    28,    29,   141,   110,
     111,  1386,   335,   147,   102,   916,   405,   150,  1104,   112,
     110,   111,   112,   156,   157,     4,     5,   350,   355,   319,
     865,   866,   867,   868,   869,   870,   355,   872,   101,   736,
      84,    85,    86,   335,    88,   110,   111,   736,   322,   323,
    1574,  1458,  1459,    93,    94,  1433,   328,  1435,   350,   336,
     337,   338,   897,  1585,   328,   870,   345,   160,  1439,   352,
      92,    83,   335,   736,  1176,   135,   136,   137,   138,  1579,
      23,   916,  1168,  1169,  1170,  1171,  1172,   350,  1174,  1175,
     321,   322,   323,   870,   102,   103,   104,  1183,  1184,    23,
     390,  2015,  2016,  2017,    51,    44,   318,    46,  1608,   131,
      51,  1197,    51,  1199,    53,   405,     1,    51,    57,     4,
      51,     6,    42,    43,  1458,  1459,  1098,   101,    51,  1215,
    1216,  1217,  1218,  1219,  1220,  1221,  1222,  1223,  1224,  1225,
     349,    26,    27,    28,    29,    44,   317,   318,   319,  1239,
    1525,  1183,  1184,  1239,    83,   101,    41,    96,    43,    98,
      59,    60,    83,   101,     1,   101,   101,     4,   101,     6,
      44,    83,    17,   870,    18,  1236,  1237,  1238,  1239,  1240,
    1241,   870,     7,   353,     5,    59,    60,     7,     7,    26,
      27,    28,    29,  1568,     7,   101,   101,  1237,  1238,  1239,
    1240,  1241,     5,     7,  1176,     7,   349,   870,    17,   108,
    1953,  1954,  1658,    18,    37,  1655,     8,  1279,   117,  1656,
     101,    44,    44,    46,   123,    48,   353,     7,    51,    52,
      53,   101,    55,   349,   108,   349,  1684,    59,    60,  1323,
    1324,    38,   335,   117,   266,   349,   349,   349,   147,   123,
     282,    45,   297,    47,  1778,    49,    50,   350,   101,  1321,
    1322,   101,  1710,    57,    58,  1612,   101,   101,   101,  1104,
     349,   101,  1653,   147,  1364,   160,   224,   101,  1364,  1340,
      59,    60,  1343,   223,  1345,   222,   108,  1348,   329,   219,
     222,  1397,   349,  1395,   349,   117,    90,  1383,   223,  1104,
    1340,   123,   101,  1343,   736,  1345,   101,  1397,  1348,  1395,
     101,  1397,   101,   335,  1215,  1216,  1217,  1218,  1219,  1220,
    1221,  1222,  1223,  1224,  1225,   147,   101,  1104,   350,   108,
     210,   211,   212,   213,  1858,   349,  1397,  1399,   117,   214,
     215,   216,   217,   218,   123,   101,   101,   736,     5,  1439,
       8,  1597,   101,  1439,  1440,   305,   306,   307,   308,   309,
     110,   111,  1197,   101,  1199,    51,   101,    42,   147,   146,
     112,  1895,  1458,  1459,   124,  1897,   126,   127,   128,   112,
    1215,  1216,  1217,  1218,  1219,  1220,  1221,  1222,  1223,  1224,
    1225,    69,  1197,  1639,  1199,   280,  1896,  1768,   112,   149,
     150,   151,   110,   111,  1239,     5,   101,  1104,  1495,  1495,
     118,   119,   120,   121,   122,  1104,    97,    98,    99,   100,
    1197,  1482,  1199,    83,   352,  1512,  1512,     8,    83,  1490,
    1491,  1492,  1493,  1494,  1239,   352,   101,     7,   870,   349,
    1530,  1104,   265,     7,  1530,   282,   736,  1508,  1509,  1510,
     101,   349,   349,   356,   356,  1979,   283,   280,   101,  1520,
    1521,     5,  1239,   102,   302,   350,   349,    42,  1529,  1530,
    1531,  1532,   185,   296,   282,     7,   102,   102,   301,   297,
     303,   870,  1383,   102,  2008,     5,   162,    39,     7,  1529,
    1530,  1531,  1532,   101,  1395,  2019,   110,   111,   335,  2021,
    1197,   102,  1199,  1564,  1565,  1566,   102,    97,  1197,   123,
    1199,  1597,  1484,   350,   101,    44,   348,   131,   185,  1894,
    2020,    97,   348,   102,  1564,  1565,  1566,   101,   101,  1364,
      59,    60,   348,   147,  1197,   101,  1199,   298,   101,  1440,
     350,   101,  1239,   101,     1,    83,  1792,     4,  1383,     6,
    1239,     5,   350,  1639,   183,   101,   363,  1458,  1459,  1364,
    1395,  1936,  1397,    41,   148,  1626,   373,   374,     7,    26,
      27,    28,    29,   101,   348,   101,  1239,   298,   103,   108,
     870,   283,  1684,   101,   101,   101,   350,  1364,   117,   182,
     349,   349,  1397,   102,   123,   349,   349,   349,  1469,  1470,
    1471,  1472,   349,   349,  1439,  1440,   349,   101,  1710,   349,
     349,   101,   101,   350,   350,   349,   131,   349,   147,  1680,
    1397,  1682,  1683,  1458,  1459,   349,     8,     8,  1736,   101,
     282,   102,   348,   101,  1439,  1696,   101,     5,  1746,  1611,
    1612,  1702,     8,  2018,   101,  1753,   101,   854,  1709,   517,
    1268,  1712,   266,   267,   268,   269,  1717,    20,  1244,  1516,
    1495,   392,  1439,  1724,  1725,  1726,  1821,  1364,   282,   283,
     284,     1,  1104,  1995,     4,  1364,     6,  1512,  1768,  1970,
    1819,  1881,  1768,  1882,  1724,  1725,  1726,    44,  1883,  1873,
    1495,   112,  1884,   114,  1956,  1530,    26,    27,    28,    29,
    1397,  1364,    59,    60,    89,  1471,  1792,  1512,  1397,   389,
    1796,   132,  1684,    91,  1438,  1104,  1644,   781,  1495,   140,
     141,     1,   143,   772,     4,  1530,     6,  1814,  1814,   306,
    1628,  1584,   153,   154,  1397,  1512,  1823,  1823,  1710,  1800,
    1611,  1612,  1439,   838,  1716,   391,    26,    27,    28,    29,
    1439,   108,     1,  1530,  1872,     4,  1170,     6,  1941,  1171,
     117,  1172,  1597,  1189,  1195,  1197,   123,  1199,  1829,   854,
    1831,   863,   102,   103,   104,   289,  1439,    26,    27,    28,
      29,  1842,  1843,  1225,  1845,  1846,  1847,  1848,  1849,   986,
     147,  1852,  1597,   204,  1131,  1388,  1365,   112,  1495,   114,
     403,  1393,  1889,  1889,  1639,   374,  1495,  1239,  1197,   401,
    1199,   119,    92,   404,  1104,  1512,  2005,   132,   301,     1,
    1597,   627,     4,  1512,     6,   140,   141,   142,   143,  1890,
     402,  1010,  1495,  1530,  1639,   302,   302,  1898,  1899,  1028,
      -1,  1530,   299,   300,    26,    27,    28,    29,    -1,  1512,
    1239,   131,    -1,  1943,    -1,    -1,  1828,  1943,  1830,    -1,
      -1,    -1,  1639,   112,    -1,    -1,    -1,  1530,    -1,    -1,
      -1,    -1,  1959,  1959,    -1,    -1,    -1,    -1,   335,    -1,
      -1,  1942,  1943,  1944,  1945,    -1,    -1,    -1,    -1,  1950,
    1951,  1952,  1953,   350,    -1,  1796,  1957,    -1,    -1,  1960,
    1597,    -1,  1942,  1943,  1944,  1945,    -1,  1197,  1597,  1199,
    1950,  1951,  1952,  1953,  1975,  1127,    -1,    -1,    -1,    -1,
    1981,  1982,  1983,  1984,  1985,  1986,  1987,  1988,  1989,  1990,
    1991,  1992,  1364,  1768,  1597,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1639,    -1,    -1,  2006,  1986,  1987,  1988,  1239,
    1639,    -1,    -1,    -1,    -1,   762,    -1,  1792,    -1,    -1,
      -1,  1796,    -1,  1768,    -1,  1397,  2027,  2028,  2029,    -1,
      -1,    -1,    -1,    -1,    -1,  1364,  1639,    -1,    -1,  1814,
      -1,    -1,  1954,    -1,    -1,    37,   266,  1792,  1823,    -1,
      -1,  1768,    44,    -1,    46,    -1,    -1,   804,  1970,    51,
      52,    53,    -1,    55,    -1,   335,    -1,  1439,  1397,  1814,
      -1,    -1,    -1,    -1,    -1,  1792,    -1,   266,  1823,    -1,
     350,    -1,    -1,  1995,    -1,  1237,  1238,  1239,  1240,  1241,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1814,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1823,    -1,    -1,    -1,
    1439,    -1,    -1,    -1,  1889,   335,    -1,    -1,   865,   866,
     867,   868,   869,  1495,    -1,   872,    -1,    -1,    -1,    -1,
     350,  1768,    -1,    -1,  1364,    -1,    -1,    -1,    -1,  1768,
    1512,    -1,    -1,    -1,  1889,    -1,   335,    -1,    -1,    -1,
     897,    -1,    -1,    -1,    -1,  1792,    -1,    -1,  1530,    -1,
      -1,   350,    -1,  1792,    -1,  1768,  1495,  1397,  1943,   916,
      -1,    -1,  1889,    -1,    -1,   297,    -1,  1814,    -1,    -1,
      -1,    -1,    -1,  1512,  1959,  1814,  1823,    -1,  1340,  1792,
      -1,  1343,    -1,  1345,  1823,    -1,  1348,    -1,  1943,    -1,
      -1,  1530,    -1,    -1,    -1,    -1,    -1,     1,    -1,  1439,
       4,  1814,     6,   335,  1959,    -1,    -1,    -1,    -1,    -1,
    1823,    -1,    -1,    -1,    -1,  1597,  1943,    -1,   350,    -1,
      -1,    -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,  1393,  1959,    -1,    38,   733,    -1,   735,    -1,    -1,
      -1,     1,  1889,    -1,     4,    -1,     6,    -1,    -1,    -1,
    1889,    -1,    -1,   751,   752,  1495,   754,  1639,  1597,    -1,
     758,   759,    -1,   265,    -1,    -1,    26,    27,    28,    29,
      -1,    -1,  1512,    -1,    -1,    -1,  1889,    37,   280,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,   785,    -1,   787,
    1530,    51,    -1,    53,   296,    55,  1943,    -1,    -1,   301,
    1639,   303,    -1,    -1,  1943,    -1,     1,    -1,    -1,     4,
      -1,     6,  1959,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1959,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1943,    26,    27,    28,    29,    -1,    -1,     1,    -1,    -1,
       4,    -1,     6,    -1,    -1,    -1,  1959,    -1,    -1,   847,
       1,    -1,   850,     4,    -1,     6,    -1,  1597,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    -1,  1529,  1530,  1531,
    1532,    -1,    -1,    37,    -1,    26,    27,    28,    29,    -1,
      -1,    -1,    46,    -1,    -1,    -1,  1768,    51,    -1,    53,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1639,
     160,    -1,  1564,  1565,  1566,    -1,    -1,    10,    -1,    -1,
    1792,  1168,  1169,  1170,  1171,  1172,    -1,  1174,  1175,   917,
     918,    -1,    -1,    -1,    -1,    -1,  1183,  1184,    -1,  1768,
     110,   111,  1814,    -1,   114,    -1,    39,    40,    41,    42,
      -1,  1823,    -1,    -1,   124,   125,   126,   127,   128,   129,
     130,   131,   132,  1792,    -1,    -1,    -1,    -1,  1215,  1216,
    1217,  1218,  1219,  1220,  1221,  1222,  1223,  1224,  1225,    -1,
      73,    -1,    -1,    -1,    -1,  1814,    -1,    -1,    81,    82,
      83,    84,    -1,    -1,  1823,    -1,     1,    -1,    -1,     4,
      -1,     6,    -1,   173,    -1,    -1,   160,    -1,    -1,    -1,
      -1,   104,    -1,    -1,    -1,   265,    -1,  1889,    -1,    -1,
      -1,    26,    27,    28,    29,    -1,   132,   120,    -1,    -1,
     280,    -1,   125,   126,   127,   141,    -1,   130,  1768,    -1,
     133,   335,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,
     156,   301,    -1,   303,   160,    -1,   350,    -1,   164,   165,
    1889,    -1,  1792,   169,   170,   171,   172,   173,    -1,    -1,
      -1,  1943,  1724,  1725,  1726,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1814,   335,    -1,  1959,    -1,    -1,
      -1,    -1,    -1,  1823,    -1,    -1,    -1,   282,    -1,    -1,
     350,    -1,    -1,    -1,  1092,    -1,    -1,   112,  1096,    -1,
      -1,   265,    -1,    -1,  1943,    -1,    -1,  1105,  1106,  1107,
      -1,    -1,  1110,    -1,  1112,    -1,   280,    -1,    -1,    -1,
    1959,    -1,    -1,    -1,  1122,    -1,  1383,    -1,    -1,    -1,
      -1,    -1,   296,    -1,    -1,    -1,    -1,   301,  1395,   303,
     335,    -1,    -1,    -1,    -1,    -1,   297,    -1,    -1,  1889,
      -1,    -1,    -1,    -1,    -1,   350,    -1,    -1,  1156,    -1,
    1158,    -1,    -1,    -1,    -1,    -1,  1164,   270,   271,   272,
       1,   335,    -1,     4,    -1,     6,    -1,    -1,    -1,  1177,
      -1,  1179,     1,  1440,   335,     4,   350,     6,     1,    -1,
    1188,     4,  1190,     6,    -1,    26,    27,    28,    29,   350,
      -1,  1458,  1459,  1943,    -1,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,    26,    27,    28,    29,    -1,    -1,  1959,
      -1,    40,   108,   109,    -1,    -1,   112,    -1,   114,    -1,
      -1,   117,   118,    -1,    -1,   121,   122,   123,   124,    -1,
      -1,    -1,   128,    -1,    -1,   131,   132,    -1,    -1,    -1,
      -1,   266,    -1,   139,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    87,    88,
      89,    90,    -1,    92,    -1,    -1,    95,    -1,    -1,    -1,
    1942,  1943,  1944,  1945,    -1,    -1,    -1,    -1,  1950,  1951,
    1952,  1953,    -1,   112,    -1,   398,   399,   400,    -1,   112,
     131,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    -1,    -1,    11,    12,    13,    14,    15,    16,    17,
     335,    -1,    20,    -1,  1986,  1987,  1988,   102,   431,    -1,
      -1,    -1,    -1,    -1,   165,   350,    -1,    -1,    -1,    -1,
      -1,   160,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   126,   127,  1351,  1352,   458,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,  1372,    -1,    74,    75,    76,    77,
      78,    79,  1380,    -1,    -1,   110,   111,    -1,    86,   114,
      88,    89,    90,    91,    92,    93,    94,    95,    -1,    97,
      98,    99,   100,    -1,   102,    -1,   131,   105,    -1,   107,
      -1,  1409,   110,   111,    -1,   113,    -1,    -1,   116,    -1,
     101,    -1,    -1,    -1,     1,    -1,    -1,     4,  1426,     6,
    1428,    69,    -1,    -1,    -1,   266,    -1,   135,   136,   137,
     138,    -1,    -1,   141,    -1,   143,   265,    -1,    -1,    26,
      27,    28,    29,   266,    -1,    -1,    -1,    -1,    -1,    -1,
     185,   280,    -1,    40,   102,   103,   104,   242,    -1,    -1,
      -1,   109,    -1,    -1,    -1,   113,    -1,   296,    -1,   117,
      -1,    -1,   301,    -1,    -1,   123,    -1,   262,   263,   127,
     171,    -1,    -1,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,    -1,   335,   280,    -1,    -1,    -1,   147,
      87,    88,    89,    90,    -1,    92,   335,   242,    95,   350,
      -1,   296,   335,    -1,    -1,    -1,   301,    -1,   303,    -1,
      -1,   350,    -1,    -1,    -1,   112,    -1,   350,    -1,  1796,
      -1,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    -1,    -1,   282,   283,   284,
      -1,    -1,    -1,    -1,    -1,   451,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,     4,    -1,     6,    -1,   303,    -1,
      -1,    -1,    -1,   160,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,  1592,    -1,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,
      -1,    -1,  1610,    -1,    -1,    -1,    -1,     1,    -1,    -1,
       4,    51,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    -1,    -1,  1633,    66,   275,    -1,    -1,
     278,   279,    26,    27,    28,    29,    -1,    77,    78,    79,
      80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    92,    -1,    -1,    -1,    96,    -1,    98,    -1,
      -1,   101,   102,   103,   104,   313,   314,   107,    -1,   109,
      -1,    -1,   112,   113,    -1,    -1,    -1,   117,   265,    -1,
      -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,   280,    88,    -1,    -1,    -1,    -1,   139,
      -1,    95,    -1,    -1,   144,    -1,   354,   147,    -1,   296,
      -1,    -1,   152,    -1,   301,   155,    -1,    -1,   158,   159,
     160,    -1,    -1,   163,    -1,    -1,   166,    -1,   168,    -1,
      -1,    -1,    -1,    -1,    -1,   443,    -1,   131,    -1,    -1,
      -1,    -1,   450,    -1,    -1,    -1,    -1,    -1,   335,    -1,
     190,   191,    -1,   461,   101,   463,    -1,   465,    -1,   467,
      -1,    -1,    -1,   350,   472,    -1,    -1,   475,    -1,   477,
      -1,   165,    -1,    -1,    -1,    -1,    -1,   485,    -1,    -1,
      -1,    -1,  1790,    -1,    -1,    -1,   226,   227,   228,   229,
      -1,    -1,    -1,    -1,    -1,   235,   236,    -1,    -1,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,    -1,   171,   265,    -1,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,    -1,    -1,    -1,
     280,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     290,    -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,
      -1,   301,    -1,    -1,    -1,    -1,    -1,   307,   308,    -1,
     310,    -1,   266,   313,   314,   315,   316,    -1,    -1,    -1,
     320,    -1,    -1,    -1,   324,   325,   326,    -1,    -1,    -1,
     330,   331,    -1,     1,    -1,   335,     4,    -1,     6,   339,
      -1,    -1,   342,   343,    -1,    -1,    -1,    -1,    -1,   349,
     350,   351,    -1,    -1,   354,    23,    -1,    -1,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   335,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,   350,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,    96,    -1,
      98,    -1,    -1,   101,   102,   103,   104,    -1,    -1,   107,
      -1,   109,    -1,    -1,   112,   113,    -1,    -1,    -1,   117,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   139,    -1,    -1,    -1,    -1,   144,    -1,    -1,   147,
      -1,    -1,    -1,    -1,   152,    -1,    -1,   155,    -1,    -1,
     158,   159,   160,    -1,    -1,   163,    -1,    -1,   166,    -1,
     168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,     4,    -1,     6,
      -1,    -1,   190,   191,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,   226,   227,
     228,   229,    -1,    -1,    -1,    -1,    -1,   235,   236,    -1,
      -1,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,    -1,    -1,   265,    -1,    -1,
      87,    88,    89,    90,    -1,    92,    -1,    -1,    95,    -1,
      -1,    -1,   280,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   290,    -1,    -1,   112,    -1,    -1,   296,    -1,
      -1,    -1,    -1,   301,    -1,    -1,    -1,    -1,    -1,   307,
     308,    -1,   310,    -1,    -1,   313,   314,   315,   316,    -1,
      -1,    -1,   320,    -1,    -1,    -1,   324,   325,   326,    -1,
      -1,    -1,   330,   331,    -1,    -1,    -1,   335,    -1,    -1,
      -1,   339,    -1,   160,   342,   343,    -1,    -1,    -1,    -1,
      -1,   349,   350,   351,     1,    -1,   354,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   969,    -1,    -1,    -1,    -1,    23,    -1,    -1,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,    79,    80,    81,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,   265,    96,
      -1,    98,    -1,    -1,   101,   102,   103,   104,    -1,    -1,
     107,    -1,   109,   280,    -1,   112,   113,    -1,    -1,    -1,
     117,    -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,   296,
      -1,    -1,    -1,    -1,   301,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,    -1,    -1,    -1,    -1,   144,    -1,    -1,
     147,    -1,    -1,    -1,    -1,   152,    -1,    -1,   155,    -1,
      -1,   158,   159,   160,    -1,    -1,   163,    -1,   335,   166,
      -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,     4,   350,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,   190,   191,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    29,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,    -1,    -1,    -1,    -1,   226,
     227,   228,   229,    -1,    -1,    -1,    -1,    -1,   235,   236,
      -1,    -1,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,    88,    -1,   265,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   280,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   290,    -1,    -1,    -1,    -1,    -1,   296,
      -1,   110,   111,    -1,   301,   114,    -1,    -1,    -1,   131,
     307,   308,    -1,   310,    -1,    -1,   313,   314,   315,   316,
      -1,    -1,   131,   320,    -1,    -1,    -1,   324,   325,   326,
      -1,    -1,    -1,   330,   331,    -1,    -1,     4,   335,     6,
      -1,    -1,   339,   165,    -1,   342,   343,    -1,    -1,    -1,
      -1,    -1,   349,   350,   351,    -1,    23,   354,    -1,    -1,
      -1,    -1,    -1,    30,    31,    -1,    -1,    -1,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,    79,    80,    81,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    98,    -1,   242,   101,   102,   103,   104,    -1,    -1,
     107,    -1,   109,    -1,   266,    -1,   113,    -1,    -1,    -1,
     117,    -1,    -1,    -1,    -1,    -1,   123,   266,   267,   268,
     269,   270,   271,    -1,   273,   274,   275,   276,   277,   278,
     279,    -1,   139,   282,   283,   284,    -1,   144,    -1,    -1,
     147,    -1,    -1,    -1,    -1,   152,    -1,    -1,   155,    -1,
      -1,   158,   159,    -1,   303,    -1,   163,    -1,    -1,   166,
      -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   190,   191,    37,    -1,    -1,   350,    -1,
      -1,    -1,    44,    -1,    46,    -1,    48,    -1,    -1,    51,
      52,    53,    -1,    55,    -1,    -1,    -1,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,
     227,   228,   229,    -1,    -1,    -1,    -1,    -1,   235,   236,
      -1,    -1,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   108,    -1,   265,    -1,
      -1,     5,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,
      -1,   123,    -1,   280,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,   290,    -1,    -1,    -1,    31,    -1,   296,
      -1,    -1,    36,    -1,   301,   147,    -1,    -1,    -1,    -1,
     307,   308,    -1,   310,    -1,    -1,   313,   314,   315,   316,
      -1,    -1,    -1,   320,    -1,    -1,    -1,   324,   325,   326,
      -1,    -1,    -1,   330,   331,    69,    -1,    -1,    -1,    -1,
      -1,    -1,   339,    -1,    -1,   342,   343,    -1,    -1,    83,
      -1,    85,   349,   350,   351,    -1,    -1,   354,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,
     104,    -1,    -1,   107,    -1,   109,    -1,    -1,    -1,   113,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,    -1,    -1,
     144,    -1,    -1,   147,    -1,    -1,    -1,    -1,   152,    -1,
      -1,   155,    -1,   265,   158,   159,    -1,    -1,    -1,   163,
      -1,    -1,   166,    -1,   168,    -1,    -1,    -1,   280,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   296,    -1,   190,   191,    -1,   301,
      -1,   303,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    -1,    -1,    50,    51,    -1,    53,
      54,    55,   226,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,     5,
      -1,   265,    96,    -1,    98,    99,   100,    -1,    -1,    -1,
      -1,   275,    -1,    -1,   278,   279,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,   291,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   307,   308,    -1,    -1,    -1,    -1,   313,
     314,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   326,    69,    -1,    -1,   330,   331,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   340,   341,    -1,   343,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   351,    -1,    -1,
     354,    -1,    -1,    -1,    -1,   101,   102,   103,   104,    -1,
      -1,   107,    -1,   109,    -1,    -1,    -1,   113,    -1,    -1,
      -1,   117,    -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,
      -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,    -1,    -1,    -1,    -1,   144,    -1,
      -1,   147,    -1,    -1,    -1,    -1,   152,    -1,    -1,   155,
      -1,    -1,   158,   159,    -1,    -1,    -1,   163,    -1,    -1,
     166,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   265,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   190,   191,   280,    -1,    -1,    -1,
      -1,   285,   286,   287,   288,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   296,    -1,    -1,    -1,    -1,   301,    -1,   303,
     304,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,     5,    -1,   265,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   275,
      -1,    -1,   278,   279,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   307,   308,    -1,    -1,    -1,    -1,   313,   314,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,
     326,    69,    -1,    -1,   330,   331,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   340,   341,    -1,   343,    -1,    -1,
      -1,    -1,    -1,   128,    -1,   351,   131,    -1,   354,    -1,
      -1,    -1,    -1,   101,   102,   103,   104,    -1,    -1,   107,
      -1,   109,    -1,   148,    -1,   113,    -1,    -1,    -1,   117,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   139,    -1,    -1,    -1,    -1,   144,    -1,    -1,   147,
      -1,    -1,    -1,    -1,   152,    -1,    -1,   155,    -1,    -1,
     158,   159,    -1,    -1,    -1,   163,    -1,    -1,   166,    -1,
     168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   190,   191,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   226,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,     5,    -1,   265,   303,    -1,
      -1,    -1,   307,   308,    -1,    -1,    -1,   275,    -1,    -1,
     278,   279,   317,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   343,   307,
     308,    -1,    -1,    -1,    -1,   313,   314,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,   326,    69,
      -1,    -1,   330,   331,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   340,   341,    -1,   343,    -1,    -1,    -1,    -1,
      -1,   128,    -1,   351,   131,    -1,   354,    -1,    -1,    -1,
      -1,   101,   102,   103,   104,    -1,    -1,   107,    -1,   109,
      -1,   148,    -1,   113,    -1,    -1,    -1,   117,    -1,    -1,
      -1,    -1,    -1,   123,    -1,    -1,    -1,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      -1,    -1,    -1,    -1,   144,    -1,    -1,   147,    -1,    -1,
      -1,    -1,   152,    -1,    -1,   155,    -1,    -1,   158,   159,
      -1,    -1,    -1,   163,    -1,    -1,   166,    -1,   168,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     190,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   226,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,     5,    -1,   265,   303,    -1,    -1,    -1,
     307,   308,    -1,    -1,    -1,   275,    -1,    -1,   278,   279,
     317,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   343,   307,   308,    -1,
      -1,    -1,    -1,   313,   314,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   326,    69,    -1,    -1,
     330,   331,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     340,   341,    -1,   343,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   351,    -1,    -1,   354,    -1,    -1,    -1,    -1,   101,
     102,   103,   104,    -1,    -1,   107,    -1,   109,    -1,    -1,
      -1,   113,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,
      -1,   123,    -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,
      -1,    -1,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,
     152,    -1,    -1,   155,    -1,    -1,   158,   159,    -1,    -1,
      -1,   163,    -1,    -1,   166,    -1,   168,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,    -1,    -1,   265,    -1,     9,    10,    11,    12,    13,
      14,    -1,    -1,   275,    -1,    19,   278,   279,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   307,   308,    -1,    -1,    -1,
      -1,   313,   314,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   326,    69,    -1,    -1,   330,   331,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   340,   341,
      -1,   343,    -1,    -1,    -1,    -1,    21,    -1,    -1,   351,
      -1,    -1,   354,    -1,    -1,    -1,    -1,   101,   102,   103,
     104,    -1,    -1,    -1,    -1,   109,    -1,    -1,    -1,   113,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,   139,    -1,    -1,    -1,    -1,
     144,    -1,    -1,   147,    -1,    -1,    -1,    -1,   152,    -1,
      -1,   155,    -1,    -1,   158,   159,    -1,    -1,    -1,   163,
      -1,    -1,   166,    -1,   168,    -1,   101,   102,   103,   104,
      -1,    -1,    -1,    -1,   109,    -1,    -1,    -1,   113,    -1,
      -1,    -1,   117,    -1,    -1,    -1,   190,   191,   123,    -1,
      -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,    -1,    -1,    -1,    -1,   144,
      -1,    -1,   147,    -1,    -1,    21,    -1,   152,    -1,    -1,
     155,    -1,    -1,   158,   159,    -1,    -1,    -1,   163,    -1,
      -1,   166,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   190,   191,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   275,    -1,    -1,   278,   279,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,   104,    -1,
      -1,    -1,    -1,   109,    -1,    -1,    -1,   113,    -1,   313,
     314,   117,   316,    -1,    -1,    -1,    -1,   123,    -1,    -1,
      -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,   139,    -1,    -1,   340,   341,   144,    -1,
     275,   147,    -1,   278,   279,   349,   152,   351,    -1,   155,
     354,    -1,   158,   159,    -1,    -1,    -1,   163,    -1,    -1,
     166,    -1,   168,    -1,   101,   102,   103,   104,    -1,    -1,
      -1,    -1,   109,    -1,    -1,    -1,   113,    -1,   313,   314,
     117,   316,    -1,    -1,   190,   191,   123,    -1,    -1,    -1,
     127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,    -1,    -1,   340,   341,   144,    -1,    -1,
     147,    -1,    -1,    -1,   349,   152,   351,    -1,   155,   354,
      -1,   158,   159,    -1,    -1,    -1,   163,    -1,    -1,   166,
      -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   190,   191,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   275,
      -1,    -1,   278,   279,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   313,   314,    -1,
     316,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   340,   341,    -1,    -1,   275,    51,
      -1,   278,   279,    -1,    -1,   351,    -1,    -1,   354,    61,
      62,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      82,    -1,    -1,    -1,    -1,    -1,   313,   314,    -1,   316,
      -1,    -1,    -1,    -1,    96,    -1,    98,    -1,    -1,   101,
     102,   103,   104,    -1,    -1,   107,    -1,   109,    -1,    -1,
      -1,   113,    -1,   340,   341,   117,    -1,    -1,    -1,    -1,
      -1,   123,   349,    -1,   351,    -1,    -1,   354,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,
      -1,    -1,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,
     152,    -1,    -1,   155,    -1,    -1,   158,   159,    -1,    -1,
      -1,   163,    -1,    -1,   166,    -1,   168,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   226,   227,   228,   229,    -1,    -1,
      -1,    -1,    -1,   235,   236,    -1,    -1,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,    -1,    -1,   265,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    -1,    -1,    -1,    36,   280,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   290,    -1,
      -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,   301,
      -1,    -1,    -1,    -1,    -1,   307,   308,    -1,   310,    -1,
      -1,   313,   314,   315,   316,    -1,    -1,    -1,   320,    -1,
      -1,    -1,   324,   325,   326,    -1,    -1,    -1,   330,   331,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   339,    -1,    -1,
     342,   343,   101,   102,   103,   104,    -1,   349,   107,   351,
     109,    -1,   354,    -1,   113,    -1,    -1,    -1,   117,    -1,
      -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,    -1,    -1,    -1,   144,    -1,    -1,   147,    -1,
      -1,    -1,    -1,   152,    -1,    -1,   155,    -1,    -1,   158,
     159,    -1,    -1,    -1,   163,    -1,    -1,   166,    -1,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   190,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,    -1,    -1,    -1,    36,   226,   227,   228,
     229,    -1,    -1,    -1,    -1,    -1,   235,   236,    -1,    -1,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,    -1,    -1,   265,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,   104,    -1,    -1,   107,    -1,   109,
      -1,    -1,    -1,   113,    -1,    -1,    -1,   117,   307,   308,
      -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   326,    -1,   139,
      -1,   330,   331,    -1,   144,    -1,    -1,   147,    -1,    -1,
      -1,    -1,   152,   342,   343,   155,    -1,    -1,   158,   159,
     349,    -1,   351,   163,    -1,   354,   166,    -1,   168,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
     190,   191,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,   227,   228,   229,
      -1,    -1,    -1,    -1,    -1,   235,   236,    -1,    -1,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,    -1,    -1,   265,    -1,   101,   102,   103,
     104,    -1,    -1,   107,    -1,   109,    -1,    -1,    -1,   113,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,    -1,   307,   308,    -1,
     144,    -1,    -1,   147,    -1,    -1,    -1,    -1,   152,    -1,
      -1,   155,    -1,    -1,   158,   159,   326,    -1,    -1,   163,
     330,   331,   166,    -1,   168,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   342,   343,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   351,    -1,    -1,   354,    -1,   190,   191,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,   227,   228,   229,    -1,    -1,    -1,    -1,
      -1,   235,   236,    -1,    -1,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,    -1,
      -1,   265,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   307,   308,    -1,    -1,    -1,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   326,    -1,    -1,    -1,   330,   331,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   342,   343,
     101,   102,   103,   104,    -1,    -1,   107,   351,   109,    -1,
     354,    -1,   113,    -1,    -1,    -1,   117,    -1,    -1,    -1,
      -1,    -1,   123,    -1,    -1,    -1,   127,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,
      -1,    -1,    -1,   144,    -1,    -1,   147,    -1,    -1,    -1,
      -1,   152,    -1,    -1,   155,    -1,    -1,   158,   159,    -1,
      -1,    -1,   163,    -1,    -1,   166,    -1,   168,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,
     191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,    -1,    -1,   265,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   275,    -1,    -1,   278,   279,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   307,   308,    -1,    -1,
      -1,    69,   313,   314,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   326,    -1,    -1,    -1,   330,
     331,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   340,
     341,    -1,   343,   101,   102,   103,   104,    -1,    -1,    -1,
     351,   109,    -1,   354,    -1,   113,    -1,    -1,    -1,   117,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   139,    -1,    -1,    -1,    -1,   144,    -1,    -1,   147,
      -1,    -1,     0,     1,   152,    -1,     4,   155,     6,    -1,
     158,   159,    -1,    -1,    -1,   163,    -1,    -1,   166,    -1,
     168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    -1,   190,   191,    -1,    -1,    44,    -1,    46,    -1,
      48,    -1,    -1,    51,    52,    53,    -1,    55,    -1,    -1,
      -1,    59,    60,    61,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
      -1,    -1,    -1,    -1,    -1,   123,    -1,   275,    -1,    69,
     278,   279,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,
      80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,   147,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,   104,   313,   314,    -1,   316,   109,
      -1,    -1,    -1,   113,    -1,    -1,    -1,   117,    -1,    -1,
      -1,    -1,    -1,   123,    -1,    -1,    -1,   127,    -1,    -1,
      -1,    -1,   340,   341,    -1,    -1,    -1,    -1,    69,   139,
      -1,   349,    -1,   351,   144,    -1,   354,   147,    -1,    -1,
      -1,    -1,   152,    -1,    -1,   155,    -1,    -1,   158,   159,
      -1,    -1,    -1,   163,    -1,    -1,   166,    -1,   168,    -1,
     101,   102,   103,   104,    -1,    -1,    -1,    -1,   109,    -1,
      -1,    -1,   113,    -1,    -1,    -1,   117,    -1,    -1,    -1,
     190,   191,   123,    -1,    -1,    -1,   127,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,   139,    -1,
      -1,    -1,    -1,   144,    -1,    -1,   147,    -1,    -1,    -1,
      -1,   152,   280,    -1,   155,    -1,    -1,   158,   159,    -1,
      -1,    -1,   163,    -1,    -1,   166,    -1,   168,   296,    -1,
      -1,    -1,    -1,   301,    -1,   303,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,
     191,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   275,    -1,    -1,   278,   279,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,   104,    -1,    -1,    -1,    -1,   109,    -1,    -1,
      -1,   113,    -1,   313,   314,   117,   316,    -1,    -1,    -1,
      -1,   123,    -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,
     340,   341,   144,    -1,   275,   147,    -1,   278,   279,    -1,
     152,   351,    -1,   155,   354,    -1,   158,   159,    -1,    -1,
      -1,   163,    -1,    -1,   166,    -1,   168,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   313,   314,    -1,   316,    -1,    -1,   190,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   340,
     341,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     351,    -1,    -1,   354,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   275,    -1,    -1,   278,   279,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   313,   314,    -1,   316,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   340,   341,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   351,
      -1,    -1,   354
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   358,     0,     1,     4,     6,    26,    27,    28,    29,
      37,    44,    46,    48,    51,    52,    53,    55,    59,    60,
      61,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,   108,   117,   123,   147,   265,   280,
     296,   301,   303,   359,   381,   382,   383,   384,   454,   455,
     456,   458,   473,   359,   103,   102,   451,   451,   451,   456,
     467,   456,   458,   473,   456,   461,   461,   461,   456,   464,
     384,    48,   385,    37,    44,    46,    51,    52,    53,    55,
     265,   280,   296,   301,   303,   386,    48,   387,    37,    44,
      46,    48,    51,    52,    53,    55,   265,   280,   296,   301,
     303,   392,    52,   393,    37,    44,    45,    46,    47,    50,
      51,    53,    54,    55,    57,    96,    98,    99,   100,   265,
     280,   285,   286,   287,   288,   296,   301,   303,   304,   394,
     280,   285,   286,   301,   395,    44,    46,    51,    53,    57,
      96,    98,   396,    46,   397,    23,    30,    31,    36,   101,
     102,   103,   104,   107,   109,   113,   117,   123,   139,   144,
     147,   152,   155,   158,   159,   163,   166,   168,   190,   191,
     226,   227,   228,   229,   235,   236,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     265,   307,   308,   326,   330,   331,   342,   343,   351,   354,
     405,   452,   567,   568,   571,   572,   573,   577,   640,   643,
     645,   649,   654,   655,   657,   659,   669,   670,   672,   674,
     676,   678,   682,   684,   686,   688,   690,   692,   694,   696,
     698,   700,   704,   712,   714,   716,   717,   719,   721,   723,
     725,   727,   729,   731,   733,    57,   336,   337,   338,   398,
     404,    57,   399,   404,   102,   400,   401,   361,   367,   368,
      88,   272,   274,   467,   467,   467,   467,     0,   359,   451,
     451,    56,   333,   334,   470,   471,   472,    35,    37,    51,
      61,    62,    66,    77,    78,    79,    80,    81,    82,    96,
      98,   241,   265,   280,   290,   296,   301,   310,   313,   314,
     315,   316,   320,   324,   325,   339,   349,   477,   478,   479,
     481,   482,   483,   484,   485,   486,   490,   491,   492,   495,
     496,   503,   507,   512,   513,   515,   516,   517,   518,   519,
     540,   541,   543,   544,   546,   547,   550,   551,   558,   559,
     560,   561,   562,   565,   566,   572,   579,   580,   581,   582,
     583,   584,   588,   589,   590,   624,   638,   643,   644,   667,
     668,   669,   359,   348,   348,   359,   451,   523,   406,   409,
     477,   451,   414,   416,   567,   590,   419,   451,   424,   458,
     474,   467,   456,   458,   461,   461,   461,   464,    88,   272,
     274,   467,   467,   467,   467,   473,   391,   456,   467,   468,
     388,   454,   456,   457,   389,   456,   458,   459,   474,   390,
     456,   461,   462,   461,   461,   456,   464,   465,    88,   272,
     274,   613,   391,   391,   391,   391,   461,   467,   456,   455,
     476,   458,   476,    44,   476,   461,   461,   476,   464,   476,
      44,    45,   461,   476,   476,    88,   272,   289,   613,   614,
     467,    44,   476,    44,   476,    44,   476,    44,   476,   467,
     467,   467,    44,   476,   467,    44,   476,    44,   476,   467,
     456,   458,   461,   461,   476,    44,   461,   458,   105,   106,
     107,   671,   110,   111,   242,   243,   246,   575,   576,    32,
      33,    34,   242,   646,   130,   578,   164,   165,   715,   110,
     111,   112,   673,   112,   114,   115,   116,   675,   110,   111,
     118,   119,   120,   121,   122,   677,   110,   111,   114,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   173,   679,
     112,   114,   132,   140,   141,   142,   143,   683,   112,   132,
     145,   292,   685,   110,   111,   124,   126,   127,   128,   149,
     150,   151,   687,   112,   114,   132,   140,   141,   143,   153,
     154,   689,   125,   141,   150,   156,   157,   691,   141,   157,
     693,   150,   160,   161,   695,   128,   132,   164,   165,   697,
     132,   164,   165,   167,   699,   132,   141,   156,   160,   164,
     165,   169,   170,   171,   172,   173,   701,   112,   164,   165,
     705,   132,   164,   165,   192,   225,   713,   112,   123,   125,
     143,   147,   150,   230,   263,   264,   343,   656,   658,   720,
     231,   722,   231,   724,   160,   232,   233,   234,   726,   125,
     150,   718,   114,   129,   150,   156,   237,   238,   728,   125,
     150,   730,   112,   125,   132,   150,   156,   732,   102,   128,
     131,   148,   303,   317,   343,   641,   642,   643,   110,   111,
     114,   131,   242,   266,   267,   268,   269,   270,   271,   273,
     274,   275,   276,   277,   278,   279,   282,   283,   284,   303,
     660,   661,   664,   317,   327,   648,   584,   589,   328,   226,
     235,   236,   239,   240,   734,   346,   347,   370,   651,   583,
     451,   404,   337,   404,    45,    47,    49,    50,    57,    58,
      90,   402,   467,   467,   467,   363,   608,   623,   610,   612,
     101,   101,   101,    83,   656,   281,   559,   451,   567,   639,
     639,    61,    97,   451,   102,   641,    88,   185,   272,   660,
     661,   281,   281,   297,   281,   299,   300,   504,    83,    83,
     656,     4,   360,   591,   592,   335,   475,   482,   409,   363,
     282,   283,   493,   494,   380,   160,   291,   292,   293,   294,
     295,   497,   498,   311,   514,     5,    69,    83,    85,   109,
     113,   117,   123,   127,   147,   226,   275,   278,   279,   291,
     313,   314,   340,   341,   351,   526,   527,   528,   529,   530,
     531,   532,   534,   535,   536,   537,   538,   539,   568,   571,
     577,   633,   634,   635,   640,   645,   649,   655,   656,   657,
     659,   665,   666,   669,    38,    39,   182,   183,   520,   521,
      83,   317,   318,   319,   542,   548,   549,    83,   545,   548,
     321,   322,   323,   374,   552,   553,   554,   555,    23,   567,
     569,   570,    44,   563,   564,    15,    16,    17,    18,   353,
       8,    24,    53,     9,    10,    11,    12,    13,    14,    19,
     109,   113,   117,   123,   139,   144,   147,   152,   155,   158,
     159,   163,   166,   168,   190,   191,   316,   351,   568,   570,
     571,   585,   586,   587,   590,   625,   626,   627,   628,   629,
     630,   631,   632,   634,   635,   636,   637,    51,    51,    22,
     349,   606,   625,   626,   631,   606,    38,   349,   522,   349,
     349,   349,   349,   349,   470,   477,   523,   406,   409,   414,
     416,   419,   424,   467,   467,   467,   363,   608,   623,   610,
     612,   477,    56,    56,    56,    56,   416,    56,   424,   467,
     363,   371,   373,   378,   416,   456,   461,   476,   467,    44,
     363,   456,   456,   456,   456,   371,   373,   378,   456,   363,
     456,   456,   373,   461,   451,     7,     8,   112,   246,   247,
     574,   295,   379,   102,   124,   281,   364,   369,   109,   123,
     109,   123,   361,   135,   136,   137,   138,   680,   367,   368,
      23,    38,   101,   171,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   702,   177,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   706,   711,   376,   367,   368,   370,   658,
     375,   375,   355,   355,   378,   378,   110,   111,   123,   131,
     147,   266,   267,   268,   662,   663,   664,   362,   328,   328,
     101,   375,   345,   650,   352,   403,   404,   621,   621,   621,
     282,   349,   607,   297,   349,   622,   349,   504,   609,   349,
     452,   611,     5,   123,   147,   538,    83,   538,   556,   557,
     584,    23,    23,    95,   349,    51,    51,    51,   101,   299,
      51,   664,    51,   538,   538,   299,   300,   508,   538,   101,
     538,   538,    83,    21,   590,   595,   596,   597,   604,   631,
     632,     7,   350,   452,   349,   101,   101,   494,    76,   109,
     123,   168,   249,   500,   452,   101,   101,   101,   452,   499,
     498,   139,   152,   168,   312,   538,     5,   538,    83,   364,
     369,   361,   367,   368,    83,   531,   568,   635,    15,    16,
      17,    18,   353,    20,    22,     8,    53,     5,   548,    83,
      85,   231,   291,     7,     7,   101,   101,   521,     5,     7,
       5,   538,   538,   374,   553,     7,   451,   349,   451,   349,
     564,   636,   636,   627,   628,   629,   583,   349,   487,   569,
     626,   367,   368,   376,   631,     7,    20,    15,    16,    17,
      18,   353,     7,    20,    22,     8,   625,   626,   631,   538,
     538,   101,   350,   359,    20,   359,   101,   439,   408,   410,
     415,   421,   425,   522,   349,   349,   349,   349,   349,   621,
     621,   621,   607,   622,   609,   611,   101,   101,   101,   101,
     101,   349,   621,   362,   456,   101,   576,   365,   101,   364,
     367,   364,   367,   112,   128,   133,   134,   231,   367,   681,
     702,    95,   128,   184,   185,   186,   187,   188,   189,   703,
     215,   219,   220,   221,   710,   210,   211,   212,   213,   708,
     214,   215,   216,   217,   218,   709,   709,   219,   222,   222,
     223,   224,   223,   112,   128,   160,   707,   377,   375,   101,
     101,   110,   111,   110,   111,   362,   362,   101,   101,   329,
     647,   101,   157,   344,   652,   656,   349,   349,   349,   101,
     432,   363,   508,   437,   371,   433,   101,   373,   438,   378,
     538,     5,     5,   538,   569,    88,    91,   475,   598,   599,
     452,   452,   101,   584,   593,   594,   538,   538,   538,   362,
     101,   538,    51,   538,   371,   101,   373,   102,   283,   505,
      42,   538,   360,     5,   360,   265,   280,   296,   601,   602,
      88,    91,   475,   600,   603,   360,   592,   411,   364,   146,
     141,   146,   501,   502,   112,   112,    69,   112,   538,     5,
     538,   538,   352,   526,   526,   527,   528,   529,   101,   531,
     526,   533,   569,   590,   538,   538,    83,     8,    83,   568,
     635,   665,   665,   538,   549,   538,   548,   555,   556,   593,
     360,   488,   489,   352,   631,   625,   631,   636,   636,   627,
     628,   629,   631,   101,   625,   631,   587,   631,    20,    20,
     101,    39,   359,   350,   359,   381,   475,   522,    37,    46,
      51,    53,    55,   160,   265,   280,   296,   301,   303,   350,
     359,   381,   407,   475,    92,   112,   160,   350,   359,   381,
     441,   447,   448,   475,   477,    40,    87,    88,    89,    90,
      92,    95,   112,   160,   265,   350,   359,   381,   422,   475,
     480,   481,    40,    88,    90,   112,   160,   350,   359,   381,
     422,   475,    41,    43,   160,   280,   350,   359,   381,   408,
     410,   415,   421,   425,   349,   349,   349,   363,   371,   373,
     378,   425,   362,   362,     7,   379,   367,     7,   376,   356,
     356,   367,   367,   368,   368,   647,   332,   647,   101,   366,
     370,   110,   111,   653,   435,   436,   434,   283,   350,   359,
     381,   475,   607,   101,   350,   359,   381,   475,   622,   350,
     359,   381,   475,   609,   505,   350,   359,   381,   475,   611,
     538,   538,     5,   102,   453,   453,   599,   349,   482,   598,
     362,   362,   362,   538,   362,    20,   102,   302,   506,   538,
      42,    80,    81,   605,   632,   638,   185,   282,   363,   297,
     602,   453,   453,   603,   350,   359,   477,   367,     7,   102,
     102,   102,   538,     5,   538,   162,   538,   548,   548,     5,
     350,   480,   482,   595,     7,   350,   625,   625,   101,    39,
     451,   469,   451,   460,   451,   463,   463,   451,   466,   102,
      88,   272,   274,   469,   469,   469,   469,   359,    77,    78,
     449,   450,   567,   102,    97,   359,   359,   359,   359,   359,
     413,   572,   453,   453,   348,    93,    94,   423,   101,   102,
     126,   127,   242,   262,   263,   429,   430,   440,    84,    85,
      86,    88,   417,   418,   359,   359,   359,   481,   413,   453,
     348,   430,   417,   359,   359,   102,   348,    97,   363,   350,
     350,   350,   350,   350,   435,   436,   434,   350,   101,   101,
     372,   101,   366,   370,    92,   131,   266,   350,   359,   381,
     475,   619,    88,    95,   131,   165,   266,   350,   359,   381,
     475,   620,   112,   266,   350,   359,   381,   475,   616,   101,
     363,    20,   102,   371,   373,   506,   378,   538,   593,   350,
     362,   305,   306,   307,   308,   309,   511,   298,   510,   101,
     373,   538,   360,   101,   299,   101,   508,   359,   502,   538,
      83,   556,     5,   350,   350,     5,   360,   489,   183,   524,
     101,   431,   409,   414,   419,   424,   469,   469,   469,   431,
     431,   431,   431,    41,     8,   359,   359,   359,   416,     8,
     359,     7,   359,     5,   359,   416,     5,   359,   148,   442,
     349,   426,   567,   359,   350,   350,   350,     7,   647,   348,
     163,   168,   615,   455,   362,   453,   101,   615,   101,   455,
     362,   103,   455,   362,   511,   510,   482,   298,   509,   101,
     371,   505,   362,   101,   283,   101,   538,   350,   556,   638,
     182,   525,   359,   349,   349,   349,   349,   349,   431,   431,
     431,   349,   349,   349,   349,   102,   572,   429,   418,    85,
     412,   413,   572,    85,   280,   296,   301,   303,   420,   430,
      22,   101,   102,   347,   443,   444,   445,   567,   359,   102,
     427,   428,   567,   359,   362,   362,   362,   101,   366,   349,
     359,   359,   359,   359,   359,   359,   359,   131,   359,   509,
     350,   101,   371,   102,   283,   362,   101,    20,   102,   350,
     360,   524,   439,   410,   415,   421,   425,   349,   349,   349,
     432,   437,   433,   438,    42,    43,   446,   413,   359,     8,
     430,   363,   371,   373,   378,   359,   359,   101,    22,    25,
       7,   350,   102,   617,   618,   615,   282,   363,   511,   510,
     525,   350,   350,   350,   350,   350,   435,   436,   434,   350,
     350,   350,   350,   452,   567,   348,   442,   359,   572,   359,
     101,   101,   360,   428,     5,     7,   350,   359,   509,   371,
     359,   359,   359,   359,   359,   350,   350,   350,   359,   359,
     359,   359,   426,   101,   618,   359,   371,   362,   362,   362,
     363,   371,   373,   378,   359,   359,   359
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   357,   358,   358,   359,   359,   360,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   381,
     381,   381,   381,   382,   382,   382,   382,   383,   383,   383,
     383,   383,   383,   383,   383,   383,   383,   383,   383,   383,
     383,   383,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   385,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   387,   388,   388,   389,   389,   390,
     390,   391,   391,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   393,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   395,   395,   395,   395,   395,   395,   396,   396,
     396,   396,   396,   396,   396,   397,   398,   398,   399,   399,
     400,   401,   401,   402,   402,   402,   402,   402,   402,   402,
     402,   403,   403,   404,   404,   404,   405,   406,   407,   407,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   408,   408,   409,   410,   410,   410,
     410,   410,   410,   410,   410,   411,   411,   411,   412,   412,
     413,   413,   414,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   416,   416,   417,   417,
     418,   418,   418,   418,   419,   420,   420,   420,   420,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   422,   422,   423,   423,   424,   425,   425,   425,
     425,   425,   425,   425,   426,   426,   427,   427,   427,   428,
     428,   429,   429,   430,   430,   431,   432,   432,   432,   432,
     432,   433,   433,   433,   433,   433,   434,   434,   434,   434,
     434,   435,   435,   435,   435,   435,   436,   436,   436,   436,
     436,   437,   437,   437,   437,   437,   438,   438,   438,   438,
     438,   439,   439,   439,   439,   439,   440,   440,   440,   440,
     440,   441,   442,   443,   443,   444,   444,   444,   444,   444,
     445,   445,   446,   446,   446,   446,   447,   448,   449,   449,
     450,   450,   451,   452,   452,   452,   453,   454,   454,   455,
     455,   455,   455,   455,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   473,   473,   473,   474,   475,   476,   476,
     477,   477,   478,   479,   479,   480,   480,   481,   481,   481,
     481,   482,   482,   482,   482,   482,   482,   482,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   482,
     482,   483,   483,   484,   485,   485,   486,   487,   487,   488,
     488,   488,   489,   490,   490,   491,   491,   492,   492,   493,
     493,   494,   494,   495,   495,   496,   497,   497,   498,   498,
     498,   498,   498,   498,   499,   500,   500,   500,   500,   500,
     501,   501,   502,   502,   503,   503,   503,   504,   504,   504,
     505,   505,   506,   506,   507,   507,   508,   508,   508,   509,
     509,   510,   510,   510,   511,   511,   511,   511,   511,   512,
     513,   514,   514,   514,   514,   514,   515,   516,   516,   517,
     517,   517,   517,   517,   517,   518,   518,   519,   519,   520,
     520,   521,   521,   521,   521,   522,   522,   523,   524,   524,
     525,   525,   526,   526,   526,   526,   526,   526,   526,   526,
     526,   526,   526,   526,   526,   527,   527,   527,   528,   528,
     529,   529,   530,   530,   531,   532,   532,   533,   533,   534,
     534,   535,   536,   537,   537,   538,   538,   538,   539,   539,
     539,   539,   539,   539,   539,   539,   539,   539,   539,   539,
     539,   539,   540,   540,   541,   542,   542,   542,   543,   543,
     544,   545,   545,   545,   545,   545,   546,   546,   547,   547,
     548,   548,   549,   549,   549,   550,   550,   551,   552,   552,
     553,   553,   554,   554,   555,   555,   556,   556,   557,   558,
     558,   558,   559,   559,   559,   560,   560,   561,   561,   562,
     563,   563,   564,   565,   565,   566,   567,   568,   568,   569,
     569,   570,   571,   572,   572,   572,   572,   572,   572,   572,
     572,   572,   572,   572,   572,   572,   572,   572,   573,   574,
     574,   574,   575,   575,   575,   575,   575,   576,   576,   577,
     577,   578,   578,   579,   579,   579,   580,   580,   581,   581,
     582,   582,   583,   584,   584,   585,   586,   587,   587,   588,
     589,   589,   589,   590,   591,   591,   591,   592,   592,   592,
     593,   593,   594,   595,   595,   596,   596,   597,   597,   598,
     598,   599,   599,   599,   600,   600,   601,   601,   602,   602,
     602,   602,   602,   602,   603,   603,   603,   604,   605,   605,
     606,   606,   606,   606,   607,   608,   609,   610,   611,   612,
     613,   613,   613,   614,   614,   614,   615,   615,   616,   616,
     617,   617,   618,   619,   619,   619,   620,   620,   620,   620,
     620,   621,   622,   622,   623,   624,   624,   624,   624,   624,
     624,   624,   624,   625,   625,   626,   626,   626,   627,   627,
     627,   628,   628,   629,   629,   630,   630,   631,   632,   632,
     632,   632,   633,   633,   634,   635,   635,   635,   635,   635,
     635,   635,   635,   635,   635,   635,   635,   636,   636,   636,
     636,   636,   636,   636,   636,   636,   636,   636,   636,   636,
     636,   636,   636,   636,   637,   637,   637,   637,   637,   637,
     637,   638,   638,   638,   638,   638,   638,   639,   639,   640,
     640,   640,   641,   641,   642,   642,   642,   642,   642,   643,
     643,   643,   643,   643,   643,   643,   643,   643,   643,   643,
     643,   643,   643,   643,   643,   643,   643,   643,   643,   643,
     643,   643,   643,   644,   644,   644,   644,   644,   644,   645,
     645,   646,   646,   646,   647,   647,   648,   648,   649,   650,
     650,   651,   651,   652,   652,   653,   653,   654,   654,   655,
     655,   655,   656,   656,   657,   657,   658,   658,   658,   658,
     659,   659,   659,   660,   660,   661,   661,   661,   661,   661,
     661,   661,   661,   661,   661,   661,   661,   661,   661,   661,
     661,   661,   662,   662,   662,   662,   662,   662,   662,   663,
     663,   663,   663,   664,   664,   664,   664,   665,   665,   666,
     666,   667,   667,   667,   667,   668,   669,   669,   669,   669,
     669,   669,   669,   669,   669,   669,   669,   669,   669,   669,
     669,   669,   669,   669,   670,   671,   671,   671,   672,   673,
     673,   673,   674,   675,   675,   675,   675,   676,   677,   677,
     677,   677,   677,   677,   677,   677,   677,   678,   678,   678,
     679,   679,   679,   679,   679,   679,   679,   679,   679,   679,
     679,   679,   680,   680,   680,   680,   681,   681,   681,   681,
     681,   682,   683,   683,   683,   683,   683,   683,   683,   684,
     685,   685,   685,   685,   686,   687,   687,   687,   687,   687,
     687,   687,   687,   687,   688,   689,   689,   689,   689,   689,
     689,   689,   689,   690,   691,   691,   691,   691,   691,   692,
     693,   693,   694,   695,   695,   695,   696,   697,   697,   697,
     697,   698,   699,   699,   699,   699,   700,   700,   700,   700,
     701,   701,   701,   701,   701,   701,   701,   701,   701,   701,
     702,   702,   702,   702,   702,   702,   702,   702,   702,   702,
     702,   702,   702,   703,   703,   703,   703,   703,   703,   703,
     703,   704,   705,   705,   705,   706,   706,   706,   706,   706,
     706,   706,   706,   706,   706,   706,   706,   706,   706,   706,
     706,   706,   706,   707,   707,   707,   708,   708,   708,   708,
     709,   709,   709,   709,   709,   710,   710,   710,   710,   711,
     711,   711,   711,   711,   711,   711,   711,   711,   711,   711,
     711,   712,   712,   713,   713,   713,   713,   714,   715,   715,
     716,   716,   716,   716,   716,   716,   716,   716,   717,   718,
     718,   719,   720,   720,   720,   720,   721,   722,   723,   724,
     725,   726,   726,   726,   726,   727,   728,   728,   728,   728,
     728,   728,   729,   730,   730,   731,   732,   732,   732,   732,
     732,   733,   734,   734,   734,   734,   734
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     5,
       5,     3,     2,     1,     1,     2,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     6,     2,     6,     3,     2,     6,     6,
       3,     6,     3,     5,     7,     5,     7,     8,     8,     8,
       5,     7,     5,     7,     4,     6,     3,     2,     6,     2,
       6,     6,     6,     3,     6,     3,     5,     5,     8,     8,
       8,     5,     5,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     3,     2,
       2,     6,     3,     3,     5,     3,     3,     2,     3,     2,
       2,     2,     2,     2,     3,     2,     2,     3,     3,     2,
       3,     3,     2,     3,     3,     2,     3,     3,     2,     3,
       2,     2,     3,     3,     2,     2,     2,     2,     2,     2,
       4,     5,     2,     3,     3,     2,     3,     3,     2,     2,
       2,     2,     3,     2,     2,     3,     2,     1,     2,     1,
       3,     0,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     1,     1,     2,     1,     0,     2,     1,
       0,     2,     2,     3,     8,     8,     8,     8,     9,     9,
      10,    10,    10,     9,     9,     8,     0,     0,     2,     2,
       3,     3,     3,     3,     3,     0,     2,     3,     1,     3,
       1,     3,     0,     0,     2,     2,     4,     4,     4,     4,
       4,     3,     4,     2,     3,     3,     1,     1,     3,     1,
       1,     1,     1,     1,     0,     2,     2,     2,     2,     0,
       2,     2,     4,     6,     7,     6,     7,     6,     4,     4,
       3,     3,     2,     2,     1,     1,     0,     0,     2,     2,
       5,     5,     3,     4,     3,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     3,     0,     0,     2,     2,     2,
       2,     0,     2,     2,     2,     2,     0,     2,     2,     2,
       2,     0,     2,     2,     2,     2,     0,     2,     2,     2,
       2,     0,     2,     2,     2,     2,     0,     2,     2,     2,
       2,     0,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     6,     2,     1,     1,     1,     1,     1,     3,     3,
       1,     2,     2,     2,     3,     0,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     2,
       2,     1,     2,     1,     1,     2,     3,     2,     3,     1,
       2,     3,     1,     2,     3,     1,     2,     3,     1,     2,
       2,     2,     1,     2,     2,     2,     2,     2,     0,     1,
       1,     2,     1,     1,     2,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     1,     1,     3,     3,     1,     1,
       3,     3,     5,     4,     5,     1,     2,     1,     3,     1,
       2,     2,     2,     1,     2,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     1,     2,     3,     1,     2,     1,
       3,     1,     1,     1,     8,     7,     4,     1,     1,     0,
       1,     1,     0,     3,     6,     4,     1,     1,     0,     0,
       3,     0,     3,     3,     1,     1,     1,     1,     1,     2,
       1,     0,     4,     4,     4,     3,     2,     1,     1,     3,
       4,     4,     5,     6,     5,     1,     2,     1,     3,     1,
       2,     2,     2,     1,     1,     6,     8,     0,     0,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     3,     1,     1,     3,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     2,
       3,     3,     4,     5,     2,     3,     2,     6,     4,     3,
       4,     3,     2,     1,     1,     3,     4,     1,     2,     1,
       1,     2,     3,     1,     3,     4,     3,     5,     3,     6,
       1,     3,     1,     1,     1,     2,     3,     1,     1,     2,
       2,     1,     1,     3,     1,     1,     1,     2,     1,     4,
       5,     6,     1,     1,     1,     7,     8,     6,     1,     1,
       1,     2,     2,     6,     8,     1,     2,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       3,     0,     2,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     3,     3,     1,     1,     3,
       1,     1,     1,     3,     1,     3,     3,     3,     3,     5,
       1,     2,     1,     1,     2,     1,     1,     2,     1,     1,
       2,     2,     2,     1,     1,     2,     1,     2,     2,     6,
       8,     7,     4,     5,     2,     2,     1,     1,     1,     1,
       1,     1,     2,     2,     4,     0,     4,     0,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     3,
       1,     3,     3,     3,     6,     3,     3,     3,     3,     3,
       3,     0,     6,     5,     0,     2,     2,     4,     4,     5,
       5,     3,     3,     3,     3,     1,     1,     1,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     1,
       3,     3,     1,     1,     1,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     1,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     4,     3,     4,     1,     4,     4,     3,
       5,     1,     1,     1,     0,     2,     1,     1,     6,     2,
       0,     1,     1,     1,     1,     1,     1,     5,     6,     8,
       6,     5,     2,     2,     3,     4,     1,     1,     1,     2,
       3,     4,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     5,     5,     5,     6,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     3,     1,     1,
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
#line 4764 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 103: /* "quoted string"  */
#line 313 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4770 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 104: /* "string with a trailing asterisk"  */
#line 313 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4776 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 382: /* line  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4782 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* base_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4788 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* add_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4794 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* replace_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4800 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* create_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4806 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* insert_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4812 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* table_or_id_spec  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4818 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* chain_or_id_spec  */
#line 624 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4824 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* set_or_id_spec  */
#line 629 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4830 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* obj_or_id_spec  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4836 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* delete_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4842 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 393: /* get_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4848 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* list_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4854 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* reset_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4860 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 396: /* flush_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4866 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* rename_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4872 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* import_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4878 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* export_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4884 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* monitor_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4890 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* monitor_event  */
#line 856 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4896 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* describe_cmd  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4902 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* table_block_alloc  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 4908 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* chain_block_alloc  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 4914 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 412: /* typeof_data_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4920 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* typeof_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4926 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* set_block_alloc  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4932 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* set_block_expr  */
#line 758 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4938 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* map_block_alloc  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4944 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* flowtable_block_alloc  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 4950 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* flowtable_expr  */
#line 758 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4956 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* flowtable_list_expr  */
#line 758 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4962 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* flowtable_expr_member  */
#line 758 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4968 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* data_type_atom_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4974 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* data_type_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4980 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* obj_block_alloc  */
#line 666 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4986 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 440: /* type_identifier  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4992 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* extended_prio_name  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4998 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 446: /* dev_spec  */
#line 642 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).expr)); }
#line 5004 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 449: /* policy_expr  */
#line 715 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5010 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* identifier  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 5016 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* string  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 5022 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 456: /* table_spec  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5028 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* tableid_spec  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5034 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* chain_spec  */
#line 624 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5040 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* chainid_spec  */
#line 624 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5046 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* chain_identifier  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5052 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* set_spec  */
#line 629 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5058 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* setid_spec  */
#line 629 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5064 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 463: /* set_identifier  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5070 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* flowtable_spec  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5076 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* flowtableid_spec  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5082 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 467: /* obj_spec  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5088 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* objid_spec  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5094 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* obj_identifier  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5100 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* handle_spec  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5106 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* position_spec  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5112 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* index_spec  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5118 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* rule_position  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5124 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* ruleid_spec  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5130 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* comment_spec  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 5136 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* ruleset_spec  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5142 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* rule  */
#line 649 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 5148 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* stmt_list  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 5154 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* stateful_stmt_list  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 5160 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* stateful_stmt  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5166 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* stmt  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5172 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* chain_stmt  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5178 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* verdict_stmt  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5184 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 486: /* verdict_map_stmt  */
#line 752 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5190 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* verdict_map_expr  */
#line 755 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5196 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* verdict_map_list_expr  */
#line 755 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5202 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 489: /* verdict_map_list_member_expr  */
#line 755 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5208 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 490: /* connlimit_stmt  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5214 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 491: /* counter_stmt  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5220 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 492: /* counter_stmt_alloc  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5226 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 495: /* log_stmt  */
#line 681 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5232 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 496: /* log_stmt_alloc  */
#line 681 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5238 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 503: /* limit_stmt  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5244 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* quota_unit  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 5250 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* quota_stmt  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5256 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 512: /* reject_stmt  */
#line 687 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5262 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* reject_stmt_alloc  */
#line 687 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5268 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 515: /* nat_stmt  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5274 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 516: /* nat_stmt_alloc  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5280 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* tproxy_stmt  */
#line 692 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5286 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* synproxy_stmt  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5292 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* synproxy_stmt_alloc  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5298 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* synproxy_obj  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5304 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 526: /* primary_stmt_expr  */
#line 739 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5310 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 527: /* shift_stmt_expr  */
#line 741 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5316 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* and_stmt_expr  */
#line 743 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5322 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* exclusive_or_stmt_expr  */
#line 743 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5328 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* inclusive_or_stmt_expr  */
#line 743 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5334 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* basic_stmt_expr  */
#line 739 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5340 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* concat_stmt_expr  */
#line 731 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5346 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* map_stmt_expr_set  */
#line 731 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5352 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* map_stmt_expr  */
#line 731 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5358 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* prefix_stmt_expr  */
#line 736 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5364 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* range_stmt_expr  */
#line 736 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5370 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 537: /* multiton_stmt_expr  */
#line 734 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5376 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* stmt_expr  */
#line 731 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5382 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* masq_stmt  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5388 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* masq_stmt_alloc  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5394 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* redir_stmt  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5400 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 544: /* redir_stmt_alloc  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5406 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 546: /* dup_stmt  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5412 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* fwd_stmt  */
#line 705 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5418 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 550: /* queue_stmt  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5424 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* queue_stmt_alloc  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5430 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 556: /* set_elem_expr_stmt  */
#line 762 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5436 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 557: /* set_elem_expr_stmt_alloc  */
#line 762 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5442 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 558: /* set_stmt  */
#line 707 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5448 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 560: /* map_stmt  */
#line 710 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5454 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 561: /* meter_stmt  */
#line 712 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5460 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 562: /* flow_stmt_legacy_alloc  */
#line 712 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5466 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 565: /* meter_stmt_alloc  */
#line 712 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5472 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 566: /* match_stmt  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5478 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 567: /* variable_expr  */
#line 715 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5484 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 568: /* symbol_expr  */
#line 715 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5490 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 569: /* set_ref_expr  */
#line 723 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5496 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 570: /* set_ref_symbol_expr  */
#line 723 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5502 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 571: /* integer_expr  */
#line 715 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5508 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 572: /* primary_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5514 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 573: /* fib_expr  */
#line 847 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5520 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 577: /* osf_expr  */
#line 852 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5526 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 579: /* shift_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5532 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 580: /* and_expr  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5538 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 581: /* exclusive_or_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5544 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 582: /* inclusive_or_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5550 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 583: /* basic_expr  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5556 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 584: /* concat_expr  */
#line 746 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5562 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 585: /* prefix_rhs_expr  */
#line 728 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5568 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 586: /* range_rhs_expr  */
#line 728 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5574 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 587: /* multiton_rhs_expr  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5580 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 588: /* map_expr  */
#line 749 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5586 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 589: /* expr  */
#line 768 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5592 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 590: /* set_expr  */
#line 758 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5598 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 591: /* set_list_expr  */
#line 758 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5604 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 592: /* set_list_member_expr  */
#line 758 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5610 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 593: /* meter_key_expr  */
#line 765 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5616 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 594: /* meter_key_expr_alloc  */
#line 765 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5622 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 595: /* set_elem_expr  */
#line 760 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5628 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 596: /* set_elem_key_expr  */
#line 884 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5634 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 597: /* set_elem_expr_alloc  */
#line 760 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5640 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 601: /* set_elem_stmt_list  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 5646 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 602: /* set_elem_stmt  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5652 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 604: /* set_lhs_expr  */
#line 760 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5658 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 605: /* set_rhs_expr  */
#line 760 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5664 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 606: /* initializer_expr  */
#line 768 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5670 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 608: /* counter_obj  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5676 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 610: /* quota_obj  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5682 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 612: /* secmark_obj  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5688 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 617: /* timeout_states  */
#line 877 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5694 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 618: /* timeout_state  */
#line 877 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5700 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 621: /* ct_obj_alloc  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5706 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 623: /* limit_obj  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5712 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 624: /* relational_expr  */
#line 781 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5718 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 625: /* list_rhs_expr  */
#line 773 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5724 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 626: /* rhs_expr  */
#line 771 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5730 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 627: /* shift_rhs_expr  */
#line 773 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5736 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 628: /* and_rhs_expr  */
#line 775 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5742 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 629: /* exclusive_or_rhs_expr  */
#line 775 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5748 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 630: /* inclusive_or_rhs_expr  */
#line 775 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5754 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 631: /* basic_rhs_expr  */
#line 771 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5760 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 632: /* concat_rhs_expr  */
#line 771 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5766 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 634: /* boolean_expr  */
#line 867 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5772 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 635: /* keyword_expr  */
#line 768 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5778 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 636: /* primary_rhs_expr  */
#line 773 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5784 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 638: /* verdict_expr  */
#line 715 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5790 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 639: /* chain_expr  */
#line 715 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5796 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 640: /* meta_expr  */
#line 829 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5802 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 644: /* meta_stmt  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5808 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 645: /* socket_expr  */
#line 833 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5814 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 649: /* numgen_expr  */
#line 794 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5820 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 654: /* xfrm_expr  */
#line 881 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5826 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 655: /* hash_expr  */
#line 794 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5832 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 657: /* rt_expr  */
#line 839 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5838 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 659: /* ct_expr  */
#line 843 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5844 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 665: /* symbol_stmt_expr  */
#line 773 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5850 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 666: /* list_stmt_expr  */
#line 741 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5856 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 667: /* ct_stmt  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5862 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 668: /* payload_stmt  */
#line 675 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5868 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 669: /* payload_expr  */
#line 785 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5874 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 670: /* payload_raw_expr  */
#line 785 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5880 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 672: /* eth_hdr_expr  */
#line 788 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5886 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 674: /* vlan_hdr_expr  */
#line 788 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5892 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 676: /* arp_hdr_expr  */
#line 791 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5898 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 678: /* ip_hdr_expr  */
#line 794 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5904 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 682: /* icmp_hdr_expr  */
#line 794 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5910 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 684: /* igmp_hdr_expr  */
#line 794 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5916 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 686: /* ip6_hdr_expr  */
#line 798 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5922 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 688: /* icmp6_hdr_expr  */
#line 798 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5928 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 690: /* auth_hdr_expr  */
#line 801 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5934 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 692: /* esp_hdr_expr  */
#line 801 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5940 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 694: /* comp_hdr_expr  */
#line 801 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5946 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 696: /* udp_hdr_expr  */
#line 804 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5952 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 698: /* udplite_hdr_expr  */
#line 804 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5958 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 700: /* tcp_hdr_expr  */
#line 862 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5964 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 704: /* dccp_hdr_expr  */
#line 807 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5970 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 711: /* sctp_chunk_alloc  */
#line 807 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5976 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 712: /* sctp_hdr_expr  */
#line 807 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5982 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 714: /* th_hdr_expr  */
#line 813 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5988 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 716: /* exthdr_expr  */
#line 817 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5994 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 717: /* hbh_hdr_expr  */
#line 819 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6000 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 719: /* rt_hdr_expr  */
#line 822 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6006 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 721: /* rt0_hdr_expr  */
#line 822 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6012 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 723: /* rt2_hdr_expr  */
#line 822 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6018 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 725: /* rt4_hdr_expr  */
#line 822 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6024 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 727: /* frag_hdr_expr  */
#line 819 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6030 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 729: /* dst_hdr_expr  */
#line 819 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6036 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 731: /* mh_hdr_expr  */
#line 825 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6042 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 733: /* exthdr_exists_expr  */
#line 871 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6048 "parser_bison.c" /* yacc.c:1257  */
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
#line 158 "parser_bison.y" /* yacc.c:1431  */
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 6164 "parser_bison.c" /* yacc.c:1431  */
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
#line 890 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 6363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 8:
#line 906 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_ARP); }
#line 6369 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 9:
#line 907 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_CT); }
#line 6375 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 10:
#line 908 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_COUNTER); }
#line 6381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 11:
#line 909 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_ETH); }
#line 6387 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 12:
#line 910 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FIB); }
#line 6393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 13:
#line 911 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HASH); }
#line 6399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 14:
#line 912 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP); }
#line 6405 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 15:
#line 913 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP6); }
#line 6411 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 16:
#line 914 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_VLAN); }
#line 6417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 17:
#line 915 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_IPSEC); }
#line 6423 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 18:
#line 916 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_LIMIT); }
#line 6429 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 19:
#line 917 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_NUMGEN); }
#line 6435 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 20:
#line 918 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_QUOTA); }
#line 6441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 21:
#line 919 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_QUEUE); }
#line 6447 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 22:
#line 920 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_RT); }
#line 6453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 23:
#line 921 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_SCTP); }
#line 6459 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 24:
#line 922 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SCTP_CHUNK); }
#line 6465 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 25:
#line 923 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_SECMARK); }
#line 6471 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 26:
#line 924 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SOCKET); }
#line 6477 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 27:
#line 926 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_LOG); }
#line 6483 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 28:
#line 929 "parser_bison.y" /* yacc.c:1652  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 6495 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 29:
#line 937 "parser_bison.y" /* yacc.c:1652  */
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
#line 6514 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 30:
#line 952 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 6525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 31:
#line 959 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 6540 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 32:
#line 970 "parser_bison.y" /* yacc.c:1652  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 6550 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 33:
#line 977 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 6556 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 34:
#line 978 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 6562 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 35:
#line 979 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 6568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 36:
#line 981 "parser_bison.y" /* yacc.c:1652  */
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
#line 6590 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 37:
#line 1000 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6596 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 38:
#line 1001 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6602 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 39:
#line 1002 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6608 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 40:
#line 1003 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6614 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 41:
#line 1004 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6620 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 42:
#line 1005 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6626 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 43:
#line 1006 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6632 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 44:
#line 1007 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6638 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 45:
#line 1008 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6644 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 46:
#line 1009 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6650 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 47:
#line 1010 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6656 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 48:
#line 1011 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6662 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 49:
#line 1012 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6668 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 50:
#line 1013 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6674 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 51:
#line 1014 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6680 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 52:
#line 1018 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 53:
#line 1023 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6698 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 54:
#line 1029 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 55:
#line 1034 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6717 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 56:
#line 1041 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6725 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 57:
#line 1045 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6733 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 58:
#line 1050 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6743 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 59:
#line 1057 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 60:
#line 1063 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 61:
#line 1068 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6771 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 62:
#line 1074 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 6784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 63:
#line 1083 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 6792 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 64:
#line 1087 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6800 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 65:
#line 1091 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 6808 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 66:
#line 1095 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6816 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 67:
#line 1099 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6824 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 68:
#line 1103 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6832 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 69:
#line 1107 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6840 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 70:
#line 1111 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 6848 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 71:
#line 1115 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6856 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 72:
#line 1119 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 6864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 73:
#line 1123 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6872 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 74:
#line 1127 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6880 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 75:
#line 1131 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 76:
#line 1137 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6896 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 77:
#line 1143 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6904 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 78:
#line 1148 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6914 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 79:
#line 1154 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6922 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 80:
#line 1159 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 81:
#line 1167 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6943 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 82:
#line 1174 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 83:
#line 1180 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6961 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 84:
#line 1185 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 85:
#line 1191 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 6984 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 86:
#line 1200 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 6992 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 87:
#line 1204 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 88:
#line 1208 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7008 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 89:
#line 1212 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7016 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 90:
#line 1216 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 91:
#line 1220 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 92:
#line 1224 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 93:
#line 1228 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 7048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 94:
#line 1234 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 7056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 103:
#line 1256 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7064 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 104:
#line 1260 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 105:
#line 1264 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1268 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7088 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1272 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7096 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1276 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 7104 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1280 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7112 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1284 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7120 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1289 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 7130 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1295 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7138 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1299 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7146 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1303 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-3].val), &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 7154 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 115:
#line 1307 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7162 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 116:
#line 1311 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7170 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 117:
#line 1315 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7178 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 118:
#line 1321 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 7186 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 119:
#line 1327 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7194 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1331 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7202 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1335 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7210 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1339 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7218 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1343 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7226 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1347 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1351 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7242 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1355 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7250 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1359 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7258 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1363 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7266 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1367 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1371 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1375 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1379 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7298 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1383 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7306 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1387 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7314 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1391 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7322 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1395 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7330 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1399 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7338 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 138:
#line 1403 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7346 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 139:
#line 1407 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7354 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 140:
#line 1411 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7362 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 141:
#line 1415 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7370 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1419 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7378 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1423 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7386 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1427 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7394 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 145:
#line 1431 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7402 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 146:
#line 1435 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7410 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 147:
#line 1439 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7418 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 148:
#line 1443 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7426 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 149:
#line 1447 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7434 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 150:
#line 1451 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7442 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 151:
#line 1455 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, (yyvsp[-3].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7450 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 152:
#line 1461 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7458 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 153:
#line 1465 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7466 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1469 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[-1].handle),&(yyloc), NULL);
			}
#line 7474 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1473 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7482 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1477 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7490 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 157:
#line 1481 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 158:
#line 1487 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7506 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 159:
#line 1491 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7514 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1495 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1499 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7530 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1503 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1507 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7546 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 164:
#line 1511 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7554 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1517 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 7563 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 166:
#line 1524 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7573 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 167:
#line 1530 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7583 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 168:
#line 1538 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7593 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 169:
#line 1544 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1552 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 7614 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1560 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = NULL; }
#line 7620 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1561 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7626 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 173:
#line 1564 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 7632 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 174:
#line 1565 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 7638 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 175:
#line 1566 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 7644 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 176:
#line 1567 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 7650 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 177:
#line 1568 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 7656 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 178:
#line 1569 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 7662 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 179:
#line 1570 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 7668 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 180:
#line 1571 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 7674 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 181:
#line 1574 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 7680 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 183:
#line 1578 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 7686 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 184:
#line 1579 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7692 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 185:
#line 1580 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7698 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 186:
#line 1584 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 7708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 187:
#line 1592 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 7717 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 188:
#line 1599 "parser_bison.y" /* yacc.c:1652  */
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
#line 7736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 189:
#line 1614 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].table)->comment, &(yyloc), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].table)->comment = (yyvsp[0].string);
			}
#line 7748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 190:
#line 1623 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 7754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 194:
#line 1630 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7767 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 195:
#line 1641 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 196:
#line 1651 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7791 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 197:
#line 1662 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7803 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 198:
#line 1672 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7816 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 199:
#line 1683 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7829 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 200:
#line 1692 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 7842 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 201:
#line 1701 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 7855 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 202:
#line 1710 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 7868 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 203:
#line 1721 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7881 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 204:
#line 1732 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7894 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 205:
#line 1743 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7907 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 206:
#line 1754 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 7916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 207:
#line 1760 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7922 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 213:
#line 1767 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 7931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 214:
#line 1772 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].chain)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].chain)->comment = (yyvsp[-1].string);
			}
#line 7943 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 215:
#line 1781 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7949 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 217:
#line 1784 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 7958 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 218:
#line 1791 "parser_bison.y" /* yacc.c:1652  */
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
#line 7983 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 219:
#line 1812 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 7996 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 220:
#line 1823 "parser_bison.y" /* yacc.c:1652  */
    {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8011 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 221:
#line 1834 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 8024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 222:
#line 1846 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 8032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 223:
#line 1851 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 8038 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 226:
#line 1855 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8047 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 227:
#line 1860 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 228:
#line 1866 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 229:
#line 1871 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8075 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 230:
#line 1876 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8084 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 231:
#line 1881 "parser_bison.y" /* yacc.c:1652  */
    {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 8094 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 232:
#line 1887 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8103 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 233:
#line 1892 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 8112 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 235:
#line 1898 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 8125 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 238:
#line 1913 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8133 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 240:
#line 1919 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 8139 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 241:
#line 1920 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 8145 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 242:
#line 1921 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 8151 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 243:
#line 1922 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_EVAL; }
#line 8157 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 244:
#line 1926 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 8165 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 245:
#line 1931 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_COUNTER; }
#line 8171 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 246:
#line 1932 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_QUOTA; }
#line 8177 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 247:
#line 1933 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_LIMIT; }
#line 8183 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 248:
#line 1934 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_SECMARK; }
#line 8189 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 249:
#line 1937 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 8195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 252:
#line 1941 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 253:
#line 1948 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 8216 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 254:
#line 1958 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 8229 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 255:
#line 1969 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 8242 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 256:
#line 1980 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				datatype_set((yyvsp[-6].set)->key, (yyvsp[-4].expr)->dtype);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 8256 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 257:
#line 1992 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = (yyvsp[-1].val);
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 8267 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 258:
#line 1999 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8276 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 259:
#line 2004 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 260:
#line 2009 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 8298 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 262:
#line 2021 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 8306 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 263:
#line 2025 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 8314 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 264:
#line 2030 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 8320 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 265:
#line 2031 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 8326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 266:
#line 2035 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 8334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 267:
#line 2040 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 8340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 270:
#line 2044 "parser_bison.y" /* yacc.c:1652  */
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
#line 8358 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 271:
#line 2058 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 8366 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 272:
#line 2062 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 8374 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 273:
#line 2066 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->flags |= FLOWTABLE_F_HW_OFFLOAD;
			}
#line 8382 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 274:
#line 2072 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 275:
#line 2077 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8400 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 276:
#line 2084 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 277:
#line 2089 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8418 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 279:
#line 2097 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 8429 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 280:
#line 2104 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8438 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 281:
#line 2111 "parser_bison.y" /* yacc.c:1652  */
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
#line 8454 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 282:
#line 2123 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 8463 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 284:
#line 2131 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 8476 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 285:
#line 2142 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 8484 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 286:
#line 2147 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8490 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 289:
#line 2151 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 290:
#line 2155 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8510 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 291:
#line 2164 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8516 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 294:
#line 2168 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8524 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 295:
#line 2172 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8536 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 296:
#line 2181 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8542 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 299:
#line 2185 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8550 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 300:
#line 2189 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8562 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 301:
#line 2199 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[(-1) - (0)].obj);
				init_list_head(&(yyval.obj)->ct_timeout.timeout_list);
			}
#line 8571 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 304:
#line 2206 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8579 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 305:
#line 2210 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8591 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 306:
#line 2219 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8597 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 309:
#line 2223 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8605 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 310:
#line 2227 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8617 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 311:
#line 2236 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8623 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 314:
#line 2240 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8631 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 315:
#line 2244 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8643 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 316:
#line 2253 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8649 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 319:
#line 2257 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8657 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 320:
#line 2261 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8669 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 321:
#line 2270 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8675 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 324:
#line 2274 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8683 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 325:
#line 2278 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8695 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 326:
#line 2287 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 8701 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 327:
#line 2288 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("mark"); }
#line 8707 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 328:
#line 2289 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("dscp"); }
#line 8713 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 329:
#line 2290 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("ecn"); }
#line 8719 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 330:
#line 2291 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("classid"); }
#line 8725 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 331:
#line 2295 "parser_bison.y" /* yacc.c:1652  */
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
#line 8758 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 332:
#line 2326 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 8767 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 333:
#line 2333 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.string) = strdup("out");
			}
#line 8775 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 335:
#line 2340 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 8789 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 336:
#line 2350 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 8800 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 337:
#line 2357 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 8815 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 338:
#line 2368 "parser_bison.y" /* yacc.c:1652  */
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
#line 8832 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 339:
#line 2381 "parser_bison.y" /* yacc.c:1652  */
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
#line 8849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 340:
#line 2395 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = (yyvsp[0].val); }
#line 8855 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 341:
#line 2396 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = -(yyvsp[0].val); }
#line 8861 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 342:
#line 2400 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 8877 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 343:
#line 2412 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8887 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 344:
#line 2418 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8895 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 345:
#line 2421 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = NULL; }
#line 8901 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 346:
#line 2425 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 8909 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 347:
#line 2431 "parser_bison.y" /* yacc.c:1652  */
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
#line 8924 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 348:
#line 2444 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 349:
#line 2449 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 8944 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 350:
#line 2457 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_ACCEPT; }
#line 8950 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 351:
#line 2458 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_DROP;   }
#line 8956 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 356:
#line 2470 "parser_bison.y" /* yacc.c:1652  */
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
#line 8973 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 357:
#line 2484 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8979 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 359:
#line 2488 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8985 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 360:
#line 2489 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 8991 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 361:
#line 2490 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_INET; }
#line 8997 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 362:
#line 2491 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_ARP; }
#line 9003 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 363:
#line 2492 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 9009 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 364:
#line 2493 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 9015 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 365:
#line 2497 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 9026 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 366:
#line 2506 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 9037 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 367:
#line 2515 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 9047 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 368:
#line 2523 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 9057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 369:
#line 2531 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 9067 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 370:
#line 2539 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 9077 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 371:
#line 2547 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 9087 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 372:
#line 2555 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 9097 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 373:
#line 2563 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 9107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 374:
#line 2571 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 9117 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 375:
#line 2579 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 9127 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 376:
#line 2587 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 9137 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 377:
#line 2595 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 9147 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 378:
#line 2603 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 9157 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 379:
#line 2611 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 9167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 380:
#line 2619 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 9177 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 381:
#line 2627 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 9187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 382:
#line 2635 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 9195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 383:
#line 2639 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 384:
#line 2644 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9216 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 385:
#line 2652 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9225 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 386:
#line 2659 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 387:
#line 2666 "parser_bison.y" /* yacc.c:1652  */
    {
				if (strlen((yyvsp[0].string)) > NFTNL_UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed",
							 NFTNL_UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 9248 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 388:
#line 2678 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 9257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 389:
#line 2683 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 9266 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 390:
#line 2690 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 9274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 391:
#line 2694 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 9282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 392:
#line 2700 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 9296 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 393:
#line 2712 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 9306 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 394:
#line 2718 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 9315 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 395:
#line 2725 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 9325 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 396:
#line 2731 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 9334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 421:
#line 2765 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_JUMP; }
#line 9340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 422:
#line 2766 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_GOTO; }
#line 9346 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 423:
#line 2770 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].chain)->location = (yylsp[-3]);
				close_scope(state);
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				(yyval.stmt) = chain_stmt_alloc(&(yyloc), (yyvsp[-1].chain), (yyvsp[-4].val));
			}
#line 9357 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 424:
#line 2779 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 9365 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 425:
#line 2783 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 9373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 426:
#line 2789 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 427:
#line 2795 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 429:
#line 2803 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 430:
#line 2808 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9408 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 432:
#line 2816 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 9416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 433:
#line 2822 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 9425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 434:
#line 2827 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 9435 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 437:
#line 2838 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 9443 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 438:
#line 2842 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 439:
#line 2850 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9461 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 441:
#line 2857 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 9469 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 442:
#line 2861 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 9477 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 445:
#line 2871 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 9485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 446:
#line 2877 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9493 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 448:
#line 2884 "parser_bison.y" /* yacc.c:1652  */
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
#line 9622 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 449:
#line 3009 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 9631 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 450:
#line 3014 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 9640 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 451:
#line 3019 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 9649 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 452:
#line 3024 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 9658 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 453:
#line 3029 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 9666 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 454:
#line 3035 "parser_bison.y" /* yacc.c:1652  */
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
#line 9698 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 455:
#line 3065 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 9706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 456:
#line 3069 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 9714 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 457:
#line 3073 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 9722 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 458:
#line 3077 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 9730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 459:
#line 3081 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 9738 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 460:
#line 3087 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9746 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 462:
#line 3094 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 9754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 463:
#line 3098 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 9762 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 464:
#line 3104 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-1].val) == 0) {
					erec_queue(error(&(yylsp[-1]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-4].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-2].val);
				(yyval.stmt)->limit.burst	= (yyvsp[-1].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-5].val);
			}
#line 9780 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 465:
#line 3118 "parser_bison.y" /* yacc.c:1652  */
    {
				struct error_record *erec;
				uint64_t rate, unit;

				if ((yyvsp[-1].val) == 0) {
					erec_queue(error(&(yylsp[-1]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}

				erec = rate_parse(&(yyloc), (yyvsp[-2].string), &rate, &unit);
				xfree((yyvsp[-2].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= rate * (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= unit;
				(yyval.stmt)->limit.burst	= (yyvsp[-1].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKT_BYTES;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 9809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 466:
#line 3143 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 9819 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 467:
#line 3150 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 9825 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 468:
#line 3151 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9831 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 469:
#line 3152 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9837 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 470:
#line 3155 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("bytes"); }
#line 9843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 471:
#line 3156 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 9849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 472:
#line 3159 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9855 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 473:
#line 3161 "parser_bison.y" /* yacc.c:1652  */
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
#line 9872 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 474:
#line 3176 "parser_bison.y" /* yacc.c:1652  */
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
#line 9892 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 475:
#line 3192 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 9902 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 476:
#line 3199 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 9908 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 477:
#line 3200 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9914 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 478:
#line 3201 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9920 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 479:
#line 3204 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 5; }
#line 9926 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 480:
#line 3205 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 9932 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 481:
#line 3208 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 5; }
#line 9938 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 482:
#line 3209 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 9944 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 483:
#line 3211 "parser_bison.y" /* yacc.c:1652  */
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
#line 9961 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 484:
#line 3225 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL; }
#line 9967 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 485:
#line 3226 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60; }
#line 9973 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 486:
#line 3227 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 9979 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 487:
#line 3228 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 9985 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 488:
#line 3229 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 9991 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 490:
#line 3236 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 9999 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 491:
#line 3242 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 10008 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 492:
#line 3247 "parser_bison.y" /* yacc.c:1652  */
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
#line 10023 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 493:
#line 3258 "parser_bison.y" /* yacc.c:1652  */
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
#line 10038 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 494:
#line 3269 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpx_code_type);
				xfree((yyvsp[0].string));
			}
#line 10052 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 495:
#line 3279 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 10060 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 497:
#line 3287 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 10066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 498:
#line 3288 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 10072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 499:
#line 3292 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 10082 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 500:
#line 3298 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 10092 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 501:
#line 3304 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 10102 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 502:
#line 3310 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 10113 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 503:
#line 3317 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 10124 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 504:
#line 3324 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 10134 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 507:
#line 3336 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 10142 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 508:
#line 3340 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 10152 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 509:
#line 3348 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 511:
#line 3355 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 10169 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 512:
#line 3360 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 10178 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 513:
#line 3365 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 10186 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 514:
#line 3369 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 10194 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 515:
#line 3375 "parser_bison.y" /* yacc.c:1652  */
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
#line 10214 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 516:
#line 3391 "parser_bison.y" /* yacc.c:1652  */
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
#line 10234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 517:
#line 3409 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 10243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 518:
#line 3415 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 10249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 519:
#line 3417 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 10257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 520:
#line 3422 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 10263 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 521:
#line 3424 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 10271 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 522:
#line 3429 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10277 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 523:
#line 3430 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10283 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 524:
#line 3431 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10289 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 525:
#line 3432 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10295 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 526:
#line 3433 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10301 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 527:
#line 3434 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10307 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 528:
#line 3435 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10313 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 529:
#line 3436 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10319 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 530:
#line 3437 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10325 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 531:
#line 3438 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10331 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 532:
#line 3439 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 533:
#line 3440 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10343 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 534:
#line 3441 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 10349 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 536:
#line 3446 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10357 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 537:
#line 3450 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10365 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 539:
#line 3457 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 541:
#line 3464 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 543:
#line 3471 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10389 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 546:
#line 3481 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10402 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 549:
#line 3496 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10410 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 550:
#line 3499 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 551:
#line 3503 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 10424 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 552:
#line 3509 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10432 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 558:
#line 3524 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 559:
#line 3528 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10448 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 560:
#line 3532 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 561:
#line 3537 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10466 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 562:
#line 3542 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10475 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 563:
#line 3547 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 564:
#line 3553 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10493 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 565:
#line 3557 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10501 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 566:
#line 3561 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10509 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 567:
#line 3565 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.type_flags = STMT_NAT_F_CONCAT;
			}
#line 10519 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 568:
#line 3571 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags = STMT_NAT_F_INTERVAL;
			}
#line 10529 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 569:
#line 3577 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags = STMT_NAT_F_INTERVAL;
			}
#line 10538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 570:
#line 3582 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX |
						STMT_NAT_F_INTERVAL;
				(yyvsp[-4].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 10551 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 571:
#line 3591 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX |
						STMT_NAT_F_INTERVAL;
				(yyvsp[-3].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 10563 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 574:
#line 3604 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 10569 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 575:
#line 3608 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 576:
#line 3612 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10586 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 577:
#line 3617 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10594 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 580:
#line 3626 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 10600 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 581:
#line 3630 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10608 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 582:
#line 3634 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10616 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 583:
#line 3638 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 584:
#line 3642 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10633 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 585:
#line 3647 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10642 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 586:
#line 3654 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 10651 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 587:
#line 3659 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 10661 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 588:
#line 3667 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 10670 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 589:
#line 3672 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 10681 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 591:
#line 3682 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10689 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 592:
#line 3687 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 10695 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 593:
#line 3688 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 10701 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 594:
#line 3689 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 10707 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 597:
#line 3697 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 10715 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 598:
#line 3703 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10723 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 600:
#line 3710 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 10732 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 601:
#line 3715 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 10740 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 603:
#line 3722 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 604:
#line 3727 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 10754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 605:
#line 3728 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 10760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 608:
#line 3736 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10768 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 609:
#line 3742 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 10779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 610:
#line 3749 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 10790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 611:
#line 3756 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				list_splice_tail((yyvsp[-1].list), &(yyval.stmt)->set.stmt_list);
				free((yyvsp[-1].list));
			}
#line 10803 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 612:
#line 3766 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 10809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 613:
#line 3767 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 10815 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 614:
#line 3768 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 10821 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 615:
#line 3772 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 10833 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 616:
#line 3780 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
				list_splice_tail((yyvsp[-3].list), &(yyval.stmt)->map.stmt_list);
				free((yyvsp[-3].list));
			}
#line 10847 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 617:
#line 3792 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 10858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 618:
#line 3798 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 10864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 619:
#line 3802 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 10872 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 620:
#line 3808 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10880 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 622:
#line 3815 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 10888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 623:
#line 3821 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 10901 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 624:
#line 3830 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 10914 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 625:
#line 3841 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 10922 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 626:
#line 3847 "parser_bison.y" /* yacc.c:1652  */
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
#line 10950 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 628:
#line 3874 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10961 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 631:
#line 3887 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10972 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 632:
#line 3896 "parser_bison.y" /* yacc.c:1652  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 10985 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 633:
#line 3906 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10991 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 634:
#line 3907 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10997 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 635:
#line 3908 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11003 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 636:
#line 3909 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11009 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 637:
#line 3910 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11015 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 638:
#line 3911 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11021 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 639:
#line 3912 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11027 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 640:
#line 3913 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11033 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 641:
#line 3914 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11039 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 642:
#line 3915 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11045 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 643:
#line 3916 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11051 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 644:
#line 3917 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 645:
#line 3918 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11063 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 646:
#line 3919 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11069 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 647:
#line 3920 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 11075 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 648:
#line 3924 "parser_bison.y" /* yacc.c:1652  */
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
#line 11100 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 649:
#line 3946 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 11106 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 650:
#line 3947 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 11112 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 651:
#line 3948 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 11118 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 652:
#line 3951 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 11124 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 653:
#line 3952 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 11130 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 654:
#line 3953 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 11136 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 655:
#line 3954 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 11142 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 656:
#line 3955 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 11148 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 657:
#line 3959 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 11156 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 659:
#line 3966 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), NFT_OSF_F_VERSION);
			}
#line 11164 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 660:
#line 3970 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 11172 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 661:
#line 3976 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 11180 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 662:
#line 3980 "parser_bison.y" /* yacc.c:1652  */
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
#line 11196 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 664:
#line 3995 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 665:
#line 3999 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11212 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 667:
#line 4006 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11220 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 669:
#line 4013 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 671:
#line 4020 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11236 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 674:
#line 4030 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 11249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 675:
#line 4041 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 11257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 676:
#line 4047 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11265 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 679:
#line 4057 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 683:
#line 4068 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 684:
#line 4075 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11291 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 685:
#line 4080 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11300 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 687:
#line 4088 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11308 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 688:
#line 4092 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11316 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 689:
#line 4096 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 11324 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 691:
#line 4103 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11333 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 692:
#line 4110 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 11341 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 695:
#line 4119 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11347 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 696:
#line 4120 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = set_elem_catchall_expr_alloc(&(yylsp[0])); }
#line 11353 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 697:
#line 4124 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[-1]), (yyvsp[-1].expr));
				list_splice_tail((yyvsp[0].list), &(yyval.expr)->stmt_list);
				xfree((yyvsp[0].list));
			}
#line 11363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 698:
#line 4130 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 11371 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 699:
#line 4136 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 11379 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 701:
#line 4143 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 11387 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 702:
#line 4147 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 11395 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 703:
#line 4151 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 11407 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 704:
#line 4161 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 11415 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 706:
#line 4168 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 11425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 707:
#line 4174 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 11434 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 708:
#line 4181 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 11442 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 709:
#line 4185 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
				(yyval.stmt)->counter.packets = (yyvsp[-3].val);
				(yyval.stmt)->counter.bytes = (yyvsp[-1].val);
			}
#line 11452 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 710:
#line 4191 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-1].val) == 0) {
					erec_queue(error(&(yylsp[-1]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate  = (yyvsp[-4].val);
				(yyval.stmt)->limit.unit  = (yyvsp[-2].val);
				(yyval.stmt)->limit.burst = (yyvsp[-1].val);
				(yyval.stmt)->limit.type  = NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-5].val);
			}
#line 11470 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 711:
#line 4205 "parser_bison.y" /* yacc.c:1652  */
    {
				struct error_record *erec;
				uint64_t rate, unit;

				if ((yyvsp[-1].val) == 0) {
					erec_queue(error(&(yylsp[-1]), "limit burst must be > 0"),
						   state->msgs);
					YYERROR;
				}
				erec = rate_parse(&(yyloc), (yyvsp[-2].string), &rate, &unit);
				xfree((yyvsp[-2].string));
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate  = rate * (yyvsp[-3].val);
				(yyval.stmt)->limit.unit  = unit;
				(yyval.stmt)->limit.burst = (yyvsp[-1].val);
				(yyval.stmt)->limit.type  = NFT_LIMIT_PKT_BYTES;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
                        }
#line 11498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 712:
#line 4229 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 11507 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 713:
#line 4234 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 11517 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 714:
#line 4242 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 11525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 715:
#line 4246 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 11533 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 716:
#line 4250 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 11545 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 722:
#line 4268 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_SET); }
#line 11551 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 723:
#line 4270 "parser_bison.y" /* yacc.c:1652  */
    {
				int32_t num = -(yyvsp[0].val);

				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(num) * BITS_PER_BYTE,
							 &num);
			}
#line 11564 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 724:
#line 4281 "parser_bison.y" /* yacc.c:1652  */
    {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 11576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 725:
#line 4291 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 11585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 726:
#line 4298 "parser_bison.y" /* yacc.c:1652  */
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
#line 11607 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 727:
#line 4318 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 11616 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 728:
#line 4325 "parser_bison.y" /* yacc.c:1652  */
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
#line 11634 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 729:
#line 4341 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 11643 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 730:
#line 4347 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 11649 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 731:
#line 4348 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 11655 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 732:
#line 4349 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 11661 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 733:
#line 4352 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_OBJ_CT_HELPERS; }
#line 11667 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 734:
#line 4353 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_OBJ_CT_TIMEOUT; }
#line 11673 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 735:
#line 4354 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_OBJ_CT_EXPECT; }
#line 11679 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 736:
#line 4357 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_TCP; }
#line 11685 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 737:
#line 4358 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_UDP; }
#line 11691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 738:
#line 4362 "parser_bison.y" /* yacc.c:1652  */
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
#line 11711 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 739:
#line 4378 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 11719 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 740:
#line 4384 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 11729 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 741:
#line 4390 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 11738 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 742:
#line 4398 "parser_bison.y" /* yacc.c:1652  */
    {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 11753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 743:
#line 4411 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 11765 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 744:
#line 4419 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;

				ct = &(yyvsp[-6].obj)->ct_timeout;
				list_splice_tail((yyvsp[-2].list), &ct->timeout_list);
				xfree((yyvsp[-2].list));
			}
#line 11777 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 745:
#line 4427 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 11785 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 746:
#line 4433 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 11793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 747:
#line 4437 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 11801 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 748:
#line 4441 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 11809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 749:
#line 4445 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 11817 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 750:
#line 4449 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 11825 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 751:
#line 4455 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 11833 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 752:
#line 4461 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;

				limit = &(yyvsp[-6].obj)->limit;
				limit->rate	= (yyvsp[-3].val);
				limit->unit	= (yyvsp[-1].val);
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-4].val);
			}
#line 11848 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 753:
#line 4472 "parser_bison.y" /* yacc.c:1652  */
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
#line 11871 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 754:
#line 4493 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 11880 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 755:
#line 4500 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 11888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 756:
#line 4504 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 11896 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 757:
#line 4508 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 11904 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 758:
#line 4512 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 11912 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 759:
#line 4516 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 11920 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 760:
#line 4520 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 11928 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 761:
#line 4524 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11936 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 762:
#line 4528 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11944 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 763:
#line 4534 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11954 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 764:
#line 4540 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11964 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 765:
#line 4547 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11970 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 766:
#line 4548 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11976 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 767:
#line 4549 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11982 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 769:
#line 4554 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11990 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 770:
#line 4558 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11998 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 772:
#line 4565 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12006 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 774:
#line 4572 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12014 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 776:
#line 4579 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12022 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 780:
#line 4590 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 12035 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 781:
#line 4599 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 12048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 782:
#line 4609 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = true; }
#line 12054 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 783:
#line 4610 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = false; }
#line 12060 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 784:
#line 4614 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 12070 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 785:
#line 4621 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 12076 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 786:
#line 4622 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 12082 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 787:
#line 4623 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 12088 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 788:
#line 4624 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 12094 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 789:
#line 4625 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 12100 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 790:
#line 4626 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 12106 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 791:
#line 4627 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 12112 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 792:
#line 4628 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 12118 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 793:
#line 4629 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 12124 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 794:
#line 4630 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 12130 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 795:
#line 4631 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 12136 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 796:
#line 4632 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 12142 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 797:
#line 4635 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12148 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 798:
#line 4636 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12154 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 799:
#line 4637 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 800:
#line 4638 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12166 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 801:
#line 4640 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12177 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 802:
#line 4647 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12188 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 803:
#line 4654 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12199 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 804:
#line 4661 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12210 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 805:
#line 4668 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12221 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 806:
#line 4675 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12232 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 807:
#line 4682 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 808:
#line 4689 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12254 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 809:
#line 4696 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12265 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 810:
#line 4703 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12276 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 811:
#line 4710 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12287 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 812:
#line 4717 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12298 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 813:
#line 4723 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 12304 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 814:
#line 4726 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_EQ; }
#line 12310 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 815:
#line 4727 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_NEQ; }
#line 12316 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 816:
#line 4728 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LT; }
#line 12322 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 817:
#line 4729 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GT; }
#line 12328 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 818:
#line 4730 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GTE; }
#line 12334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 819:
#line 4731 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LTE; }
#line 12340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 820:
#line 4732 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_NEG; }
#line 12346 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 821:
#line 4736 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 12354 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 822:
#line 4740 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 12362 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 823:
#line 4744 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 12370 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 824:
#line 4748 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 12378 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 825:
#line 4752 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 12386 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 826:
#line 4756 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 12394 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 828:
#line 4763 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 12406 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 829:
#line 4773 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 12414 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 830:
#line 4777 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 12422 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 831:
#line 4781 "parser_bison.y" /* yacc.c:1652  */
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
#line 12440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 834:
#line 4800 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_LEN; }
#line 12446 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 835:
#line 4801 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 12452 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 836:
#line 4802 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 12458 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 837:
#line 4803 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 12464 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 838:
#line 4804 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECMARK; }
#line 12470 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 839:
#line 4807 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_MARK; }
#line 12476 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 840:
#line 4808 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIF; }
#line 12482 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 841:
#line 4809 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 12488 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 842:
#line 4810 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 12494 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 843:
#line 4811 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIF; }
#line 12500 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 844:
#line 4812 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 12506 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 845:
#line 4813 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 12512 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 846:
#line 4814 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKUID; }
#line 12518 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 847:
#line 4815 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKGID; }
#line 12524 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 848:
#line 4816 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 12530 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 849:
#line 4817 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 12536 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 850:
#line 4818 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 12542 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 851:
#line 4819 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 12548 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 852:
#line 4820 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 12554 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 853:
#line 4821 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 12560 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 854:
#line 4822 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 12566 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 855:
#line 4823 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CPU; }
#line 12572 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 856:
#line 4824 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 12578 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 857:
#line 4825 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 12584 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 858:
#line 4826 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 12590 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 859:
#line 4827 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECPATH; }
#line 12596 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 860:
#line 4828 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_NS; }
#line 12602 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 861:
#line 4829 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_DAY; }
#line 12608 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 862:
#line 4830 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_HOUR; }
#line 12614 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 863:
#line 4834 "parser_bison.y" /* yacc.c:1652  */
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
#line 12638 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 864:
#line 4854 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 12646 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 865:
#line 4858 "parser_bison.y" /* yacc.c:1652  */
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
#line 12664 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 866:
#line 4872 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 12672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 867:
#line 4876 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 12680 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 868:
#line 4880 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 12688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 869:
#line 4886 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 12696 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 870:
#line 4890 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), NFT_SOCKET_CGROUPV2, (yyvsp[-1].val));
			}
#line 12704 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 871:
#line 4895 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 12710 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 872:
#line 4896 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_MARK; }
#line 12716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 873:
#line 4897 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_WILDCARD; }
#line 12722 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 874:
#line 4900 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 12728 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 875:
#line 4901 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 12734 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 876:
#line 4904 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 12740 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 877:
#line 4905 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 12746 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 878:
#line 4909 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 12754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 879:
#line 4914 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 12760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 880:
#line 4915 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 12766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 881:
#line 4918 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_IN; }
#line 12772 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 882:
#line 4919 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_OUT; }
#line 12778 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 883:
#line 4922 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 12784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 884:
#line 4923 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 12790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 885:
#line 4926 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 12796 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 886:
#line 4927 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 12802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 887:
#line 4931 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].val) > 255) {
					erec_queue(error(&(yylsp[-2]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 12814 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 888:
#line 4939 "parser_bison.y" /* yacc.c:1652  */
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
#line 12843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 889:
#line 4966 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-4].val), true, (yyvsp[-2].val), (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-6].expr);
			}
#line 12852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 890:
#line 4971 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-4].expr);
			}
#line 12861 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 891:
#line 4976 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_SYM);
			}
#line 12869 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 892:
#line 4981 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 12875 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 893:
#line 4982 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 12881 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 894:
#line 4986 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[-1].val), true);
			}
#line 12889 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 895:
#line 4990 "parser_bison.y" /* yacc.c:1652  */
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
#line 12911 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 896:
#line 5009 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 12917 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 897:
#line 5010 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 12923 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 898:
#line 5011 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 12929 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 899:
#line 5012 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_XFRM; }
#line 12935 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 900:
#line 5016 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), -1);
			}
#line 12943 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 901:
#line 5020 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 12951 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 902:
#line 5024 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 12959 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 903:
#line 5029 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 12965 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 904:
#line 5030 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 12971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 905:
#line 5033 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 12977 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 906:
#line 5034 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 12983 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 907:
#line 5035 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_MARK; }
#line 12989 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 908:
#line 5036 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATE; }
#line 12995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 909:
#line 5037 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 13001 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 910:
#line 5038 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 13007 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 911:
#line 5039 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 13013 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 912:
#line 5040 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 13019 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 913:
#line 5041 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 13025 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 914:
#line 5042 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 13031 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 915:
#line 5043 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 13037 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 916:
#line 5044 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 13043 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 917:
#line 5045 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 13049 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 918:
#line 5046 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 13055 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 919:
#line 5047 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SECMARK; }
#line 13061 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 920:
#line 5048 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ID; }
#line 13067 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 922:
#line 5052 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 13073 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 923:
#line 5053 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 13079 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 924:
#line 5054 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 13085 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 925:
#line 5055 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 13091 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 926:
#line 5056 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 13097 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 927:
#line 5057 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 13103 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 929:
#line 5061 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP; }
#line 13109 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 930:
#line 5062 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP; }
#line 13115 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 931:
#line 5063 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP6; }
#line 13121 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 932:
#line 5064 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP6; }
#line 13127 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 933:
#line 5067 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 13133 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 934:
#line 5068 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 13139 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 935:
#line 5069 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 13145 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 936:
#line 5070 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 13151 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 939:
#line 5078 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 13161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 940:
#line 5084 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 13171 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 941:
#line 5092 "parser_bison.y" /* yacc.c:1652  */
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
#line 13188 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 942:
#line 5105 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);

			}
#line 13199 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 943:
#line 5112 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 13209 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 944:
#line 5118 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].val), (yyvsp[-1].expr));
			}
#line 13217 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 945:
#line 5124 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 964:
#line 5153 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 13239 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 965:
#line 5161 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 13245 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 966:
#line 5162 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 13251 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 967:
#line 5163 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 13257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 968:
#line 5167 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[-1].val));
			}
#line 13265 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 969:
#line 5172 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 13271 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 970:
#line 5173 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 13277 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 971:
#line 5174 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 13283 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 972:
#line 5178 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[-1].val));
			}
#line 13291 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 973:
#line 5183 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_VID; }
#line 13297 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 974:
#line 5184 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_CFI; }
#line 13303 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 975:
#line 5185 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_PCP; }
#line 13309 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 976:
#line 5186 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 13315 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 977:
#line 5190 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[-1].val));
			}
#line 13323 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 978:
#line 5195 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HRD; }
#line 13329 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 979:
#line 5196 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PRO; }
#line 13335 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 980:
#line 5197 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HLN; }
#line 13341 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 981:
#line 5198 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PLN; }
#line 13347 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 982:
#line 5199 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_OP; }
#line 13353 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 983:
#line 5200 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 13359 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 984:
#line 5201 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 13365 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 985:
#line 5202 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_IP; }
#line 13371 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 986:
#line 5203 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_IP; }
#line 13377 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 987:
#line 5207 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[-1].val));
			}
#line 13385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 988:
#line 5211 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val), 0);
			}
#line 13393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 989:
#line 5215 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), IPOPT_FIELD_TYPE, 0);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 13402 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 990:
#line 5221 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_VERSION; }
#line 13408 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 991:
#line 5222 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 13414 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 992:
#line 5223 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DSCP; }
#line 13420 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 993:
#line 5224 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ECN; }
#line 13426 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 994:
#line 5225 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 13432 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 995:
#line 5226 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ID; }
#line 13438 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 996:
#line 5227 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 13444 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 997:
#line 5228 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_TTL; }
#line 13450 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 998:
#line 5229 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 13456 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 999:
#line 5230 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 13462 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1000:
#line 5231 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_SADDR; }
#line 13468 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1001:
#line 5232 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DADDR; }
#line 13474 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1002:
#line 5235 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_LSRR; }
#line 13480 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1003:
#line 5236 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RR; }
#line 13486 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1004:
#line 5237 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_SSRR; }
#line 13492 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1005:
#line 5238 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RA; }
#line 13498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1006:
#line 5241 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 13504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1007:
#line 5242 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 13510 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1008:
#line 5243 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 13516 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1009:
#line 5244 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_PTR; }
#line 13522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1010:
#line 5245 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 13528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1011:
#line 5249 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 13536 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1012:
#line 5254 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 13542 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1013:
#line 5255 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 13548 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1014:
#line 5256 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 13554 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1015:
#line 5257 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_ID; }
#line 13560 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1016:
#line 5258 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 13566 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1017:
#line 5259 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 13572 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1018:
#line 5260 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 13578 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1019:
#line 5264 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[0].val));
			}
#line 13586 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1020:
#line 5269 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_TYPE; }
#line 13592 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1021:
#line 5270 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 13598 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1022:
#line 5271 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_MRT; }
#line 13604 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1023:
#line 5272 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_GROUP; }
#line 13610 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1024:
#line 5276 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[-1].val));
			}
#line 13618 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1025:
#line 5281 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 13624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1026:
#line 5282 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 13630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1027:
#line 5283 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_ECN; }
#line 13636 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1028:
#line 5284 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 13642 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1029:
#line 5285 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 13648 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1030:
#line 5286 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 13654 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1031:
#line 5287 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 13660 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1032:
#line 5288 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 13666 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1033:
#line 5289 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 13672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1034:
#line 5292 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 13680 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1035:
#line 5297 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 13686 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1036:
#line 5298 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 13692 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1037:
#line 5299 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 13698 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1038:
#line 5300 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 13704 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1039:
#line 5301 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 13710 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1040:
#line 5302 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 13716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1041:
#line 5303 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 13722 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1042:
#line 5304 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 13728 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1043:
#line 5308 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 13736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1044:
#line 5313 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 13742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1045:
#line 5314 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 13748 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1046:
#line 5315 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 13754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1047:
#line 5316 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SPI; }
#line 13760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1048:
#line 5317 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 13766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1049:
#line 5321 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 13774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1050:
#line 5326 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SPI; }
#line 13780 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1051:
#line 5327 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 13786 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1052:
#line 5331 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 13794 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1053:
#line 5336 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 13800 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1054:
#line 5337 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 13806 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1055:
#line 5338 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_CPI; }
#line 13812 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1056:
#line 5342 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 13820 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1057:
#line 5347 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 13826 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1058:
#line 5348 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 13832 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1059:
#line 5349 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 13838 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1060:
#line 5350 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 13844 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1061:
#line 5354 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 13852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1062:
#line 5359 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 13858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1063:
#line 5360 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 13864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1064:
#line 5361 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 13870 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1065:
#line 5362 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 13876 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1066:
#line 5366 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 13884 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1067:
#line 5370 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 13892 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1068:
#line 5374 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPT_COMMON_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 13901 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1069:
#line 5379 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-4].val), 0);
				tcpopt_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val), 0);
			}
#line 13910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1070:
#line 5385 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 13916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1071:
#line 5386 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 13922 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1072:
#line 5387 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 13928 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1073:
#line 5388 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 13934 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1074:
#line 5389 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 13940 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1075:
#line 5390 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 13946 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1076:
#line 5391 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 13952 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1077:
#line 5392 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 13958 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1078:
#line 5393 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 13964 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1079:
#line 5394 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 13970 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1080:
#line 5397 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_EOL; }
#line 13976 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1081:
#line 5398 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_NOP; }
#line 13982 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1082:
#line 5399 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_MAXSEG; }
#line 13988 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1083:
#line 5400 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_WINDOW; }
#line 13994 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1084:
#line 5401 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK_PERMITTED; }
#line 14000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1085:
#line 5402 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK; }
#line 14006 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1086:
#line 5403 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK; }
#line 14012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1087:
#line 5404 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK1; }
#line 14018 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1088:
#line 5405 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK2; }
#line 14024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1089:
#line 5406 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK3; }
#line 14030 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1090:
#line 5407 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_ECHO; }
#line 14036 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1091:
#line 5408 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_TIMESTAMP; }
#line 14042 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1092:
#line 5409 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].val) > 255) {
					erec_queue(error(&(yylsp[0]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[0].val);
			}
#line 14054 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1093:
#line 5418 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_COMMON_KIND; }
#line 14060 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1094:
#line 5419 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_COMMON_LENGTH; }
#line 14066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1095:
#line 5420 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_MAXSEG_SIZE; }
#line 14072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1096:
#line 5421 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_WINDOW_COUNT; }
#line 14078 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1097:
#line 5422 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_SACK_LEFT; }
#line 14084 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1098:
#line 5423 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_SACK_RIGHT; }
#line 14090 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1099:
#line 5424 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_TS_TSVAL; }
#line 14096 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1100:
#line 5425 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_TS_TSECR; }
#line 14102 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1101:
#line 5429 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 14110 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1102:
#line 5434 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 14116 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1103:
#line 5435 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 14122 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1104:
#line 5436 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 14128 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1105:
#line 5439 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_DATA; }
#line 14134 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1106:
#line 5440 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_INIT; }
#line 14140 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1107:
#line 5441 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_INIT_ACK; }
#line 14146 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1108:
#line 5442 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_SACK; }
#line 14152 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1109:
#line 5443 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT; }
#line 14158 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1110:
#line 5444 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT_ACK; }
#line 14164 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1111:
#line 5445 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_ABORT; }
#line 14170 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1112:
#line 5446 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN; }
#line 14176 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1113:
#line 5447 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_ACK; }
#line 14182 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1114:
#line 5448 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_ERROR; }
#line 14188 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1115:
#line 5449 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ECHO; }
#line 14194 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1116:
#line 5450 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ACK; }
#line 14200 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1117:
#line 5451 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_ECNE; }
#line 14206 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1118:
#line 5452 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_CWR; }
#line 14212 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1119:
#line 5453 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_COMPLETE; }
#line 14218 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1120:
#line 5454 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF_ACK; }
#line 14224 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1121:
#line 5455 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_FORWARD_TSN; }
#line 14230 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1122:
#line 5456 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF; }
#line 14236 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1123:
#line 5459 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_COMMON_TYPE; }
#line 14242 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1124:
#line 5460 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_COMMON_FLAGS; }
#line 14248 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1125:
#line 5461 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_COMMON_LENGTH; }
#line 14254 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1126:
#line 5464 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_DATA_TSN; }
#line 14260 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1127:
#line 5465 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_DATA_STREAM; }
#line 14266 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1128:
#line 5466 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_DATA_SSN; }
#line 14272 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1129:
#line 5467 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_DATA_PPID; }
#line 14278 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1130:
#line 5470 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_INIT_TAG; }
#line 14284 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1131:
#line 5471 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_INIT_RWND; }
#line 14290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1132:
#line 5472 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_INIT_OSTREAMS; }
#line 14296 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1133:
#line 5473 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_INIT_ISTREAMS; }
#line 14302 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1134:
#line 5474 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_INIT_TSN; }
#line 14308 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1135:
#line 5477 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_SACK_CTSN_ACK; }
#line 14314 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1136:
#line 5478 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_SACK_RWND; }
#line 14320 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1137:
#line 5479 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_SACK_GACK_BLOCKS; }
#line 14326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1138:
#line 5480 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_SACK_DUP_TSNS; }
#line 14332 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1139:
#line 5484 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[0].val), SCTP_CHUNK_COMMON_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 14341 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1140:
#line 5489 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 14349 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1141:
#line 5493 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_DATA, (yyvsp[0].val));
			}
#line 14357 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1142:
#line 5497 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT, (yyvsp[0].val));
			}
#line 14365 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1143:
#line 5501 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT_ACK, (yyvsp[0].val));
			}
#line 14373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1144:
#line 5505 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SACK, (yyvsp[0].val));
			}
#line 14381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1145:
#line 5509 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SHUTDOWN,
							   SCTP_CHUNK_SHUTDOWN_CTSN_ACK);
			}
#line 14390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1146:
#line 5514 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ECNE,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 14399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1147:
#line 5519 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_CWR,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 14408 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1148:
#line 5524 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF_ACK,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 14417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1149:
#line 5529 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_FORWARD_TSN,
							   SCTP_CHUNK_FORWARD_TSN_NCTSN);
			}
#line 14426 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1150:
#line 5534 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 14435 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1151:
#line 5541 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[-1].val));
			}
#line 14443 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1152:
#line 5545 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 14451 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1153:
#line 5550 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 14457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1154:
#line 5551 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 14463 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1155:
#line 5552 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 14469 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1156:
#line 5553 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 14475 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1157:
#line 5557 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[0].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 14485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1158:
#line 5564 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_SPORT; }
#line 14491 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1159:
#line 5565 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_DPORT; }
#line 14497 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1168:
#line 5579 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 14505 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1169:
#line 5584 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 14511 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1170:
#line 5585 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 14517 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1171:
#line 5589 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[-1].val));
			}
#line 14525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1172:
#line 5594 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 14531 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1173:
#line 5595 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 14537 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1174:
#line 5596 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_TYPE; }
#line 14543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1175:
#line 5597 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 14549 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1176:
#line 5601 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 14557 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1177:
#line 5607 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 14565 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1178:
#line 5613 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 14573 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1179:
#line 5618 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 14579 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1180:
#line 5622 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 14587 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1181:
#line 5627 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 14593 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1182:
#line 5628 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 14599 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1183:
#line 5629 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_TAG; }
#line 14605 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1184:
#line 5631 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 14613 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1185:
#line 5637 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 14621 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1186:
#line 5642 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 14627 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1187:
#line 5643 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 14633 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1188:
#line 5644 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 14639 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1189:
#line 5645 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 14645 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1190:
#line 5646 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 14651 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1191:
#line 5647 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_ID; }
#line 14657 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1192:
#line 5651 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 14665 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1193:
#line 5656 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 14671 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1194:
#line 5657 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 14677 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1195:
#line 5661 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 14685 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1196:
#line 5666 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 14691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1197:
#line 5667 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 14697 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1198:
#line 5668 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_TYPE; }
#line 14703 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1199:
#line 5669 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 14709 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1200:
#line 5670 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 14715 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1201:
#line 5674 "parser_bison.y" /* yacc.c:1652  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 14731 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1202:
#line 5687 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 14737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1203:
#line 5688 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 14743 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1204:
#line 5689 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 14749 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1205:
#line 5690 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 14755 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1206:
#line 5691 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_MH; }
#line 14761 "parser_bison.c" /* yacc.c:1652  */
    break;


#line 14765 "parser_bison.c" /* yacc.c:1652  */
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
#line 5694 "parser_bison.y" /* yacc.c:1918  */

