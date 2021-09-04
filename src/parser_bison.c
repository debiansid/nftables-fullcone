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

#line 212 "parser_bison.c" /* yacc.c:337  */
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
    HOOKS = 297,
    DEVICE = 298,
    DEVICES = 299,
    TABLE = 300,
    TABLES = 301,
    CHAIN = 302,
    CHAINS = 303,
    RULE = 304,
    RULES = 305,
    SETS = 306,
    SET = 307,
    ELEMENT = 308,
    MAP = 309,
    MAPS = 310,
    FLOWTABLE = 311,
    HANDLE = 312,
    RULESET = 313,
    TRACE = 314,
    INET = 315,
    NETDEV = 316,
    ADD = 317,
    UPDATE = 318,
    REPLACE = 319,
    CREATE = 320,
    INSERT = 321,
    DELETE = 322,
    GET = 323,
    LIST = 324,
    RESET = 325,
    FLUSH = 326,
    RENAME = 327,
    DESCRIBE = 328,
    IMPORT = 329,
    EXPORT = 330,
    MONITOR = 331,
    ALL = 332,
    ACCEPT = 333,
    DROP = 334,
    CONTINUE = 335,
    JUMP = 336,
    GOTO = 337,
    RETURN = 338,
    TO = 339,
    CONSTANT = 340,
    INTERVAL = 341,
    DYNAMIC = 342,
    AUTOMERGE = 343,
    TIMEOUT = 344,
    GC_INTERVAL = 345,
    ELEMENTS = 346,
    EXPIRES = 347,
    POLICY = 348,
    MEMORY = 349,
    PERFORMANCE = 350,
    SIZE = 351,
    FLOW = 352,
    OFFLOAD = 353,
    METER = 354,
    METERS = 355,
    FLOWTABLES = 356,
    NUM = 357,
    STRING = 358,
    QUOTED_STRING = 359,
    ASTERISK_STRING = 360,
    LL_HDR = 361,
    NETWORK_HDR = 362,
    TRANSPORT_HDR = 363,
    BRIDGE = 364,
    ETHER = 365,
    SADDR = 366,
    DADDR = 367,
    TYPE = 368,
    VLAN = 369,
    ID = 370,
    CFI = 371,
    DEI = 372,
    PCP = 373,
    ARP = 374,
    HTYPE = 375,
    PTYPE = 376,
    HLEN = 377,
    PLEN = 378,
    OPERATION = 379,
    IP = 380,
    HDRVERSION = 381,
    HDRLENGTH = 382,
    DSCP = 383,
    ECN = 384,
    LENGTH = 385,
    FRAG_OFF = 386,
    TTL = 387,
    PROTOCOL = 388,
    CHECKSUM = 389,
    PTR = 390,
    VALUE = 391,
    LSRR = 392,
    RR = 393,
    SSRR = 394,
    RA = 395,
    ICMP = 396,
    CODE = 397,
    SEQUENCE = 398,
    GATEWAY = 399,
    MTU = 400,
    IGMP = 401,
    MRT = 402,
    OPTIONS = 403,
    IP6 = 404,
    PRIORITY = 405,
    FLOWLABEL = 406,
    NEXTHDR = 407,
    HOPLIMIT = 408,
    ICMP6 = 409,
    PPTR = 410,
    MAXDELAY = 411,
    AH = 412,
    RESERVED = 413,
    SPI = 414,
    ESP = 415,
    COMP = 416,
    FLAGS = 417,
    CPI = 418,
    PORT = 419,
    UDP = 420,
    SPORT = 421,
    DPORT = 422,
    UDPLITE = 423,
    CSUMCOV = 424,
    TCP = 425,
    ACKSEQ = 426,
    DOFF = 427,
    WINDOW = 428,
    URGPTR = 429,
    OPTION = 430,
    ECHO = 431,
    EOL = 432,
    NOP = 433,
    SACK = 434,
    SACK0 = 435,
    SACK1 = 436,
    SACK2 = 437,
    SACK3 = 438,
    SACK_PERM = 439,
    TIMESTAMP = 440,
    KIND = 441,
    COUNT = 442,
    LEFT = 443,
    RIGHT = 444,
    TSVAL = 445,
    TSECR = 446,
    DCCP = 447,
    SCTP = 448,
    CHUNK = 449,
    DATA = 450,
    INIT = 451,
    INIT_ACK = 452,
    HEARTBEAT = 453,
    HEARTBEAT_ACK = 454,
    ABORT = 455,
    SHUTDOWN = 456,
    SHUTDOWN_ACK = 457,
    ERROR = 458,
    COOKIE_ECHO = 459,
    COOKIE_ACK = 460,
    ECNE = 461,
    CWR = 462,
    SHUTDOWN_COMPLETE = 463,
    ASCONF_ACK = 464,
    FORWARD_TSN = 465,
    ASCONF = 466,
    TSN = 467,
    STREAM = 468,
    SSN = 469,
    PPID = 470,
    INIT_TAG = 471,
    A_RWND = 472,
    NUM_OSTREAMS = 473,
    NUM_ISTREAMS = 474,
    INIT_TSN = 475,
    CUM_TSN_ACK = 476,
    NUM_GACK_BLOCKS = 477,
    NUM_DUP_TSNS = 478,
    LOWEST_TSN = 479,
    SEQNO = 480,
    NEW_CUM_TSN = 481,
    VTAG = 482,
    RT = 483,
    RT0 = 484,
    RT2 = 485,
    RT4 = 486,
    SEG_LEFT = 487,
    ADDR = 488,
    LAST_ENT = 489,
    TAG = 490,
    SID = 491,
    HBH = 492,
    FRAG = 493,
    RESERVED2 = 494,
    MORE_FRAGMENTS = 495,
    DST = 496,
    MH = 497,
    META = 498,
    MARK = 499,
    IIF = 500,
    IIFNAME = 501,
    IIFTYPE = 502,
    OIF = 503,
    OIFNAME = 504,
    OIFTYPE = 505,
    SKUID = 506,
    SKGID = 507,
    NFTRACE = 508,
    RTCLASSID = 509,
    IBRIPORT = 510,
    OBRIPORT = 511,
    IBRIDGENAME = 512,
    OBRIDGENAME = 513,
    PKTTYPE = 514,
    CPU = 515,
    IIFGROUP = 516,
    OIFGROUP = 517,
    CGROUP = 518,
    TIME = 519,
    CLASSID = 520,
    NEXTHOP = 521,
    CT = 522,
    L3PROTOCOL = 523,
    PROTO_SRC = 524,
    PROTO_DST = 525,
    ZONE = 526,
    DIRECTION = 527,
    EVENT = 528,
    EXPECTATION = 529,
    EXPIRATION = 530,
    HELPER = 531,
    LABEL = 532,
    STATE = 533,
    STATUS = 534,
    ORIGINAL = 535,
    REPLY = 536,
    COUNTER = 537,
    NAME = 538,
    PACKETS = 539,
    BYTES = 540,
    AVGPKT = 541,
    COUNTERS = 542,
    QUOTAS = 543,
    LIMITS = 544,
    SYNPROXYS = 545,
    HELPERS = 546,
    LOG = 547,
    PREFIX = 548,
    GROUP = 549,
    SNAPLEN = 550,
    QUEUE_THRESHOLD = 551,
    LEVEL = 552,
    LIMIT = 553,
    RATE = 554,
    BURST = 555,
    OVER = 556,
    UNTIL = 557,
    QUOTA = 558,
    USED = 559,
    SECMARK = 560,
    SECMARKS = 561,
    SECOND = 562,
    MINUTE = 563,
    HOUR = 564,
    DAY = 565,
    WEEK = 566,
    _REJECT = 567,
    WITH = 568,
    ICMPX = 569,
    SNAT = 570,
    DNAT = 571,
    MASQUERADE = 572,
    REDIRECT = 573,
    RANDOM = 574,
    FULLY_RANDOM = 575,
    PERSISTENT = 576,
    QUEUE = 577,
    QUEUENUM = 578,
    BYPASS = 579,
    FANOUT = 580,
    DUP = 581,
    FWD = 582,
    NUMGEN = 583,
    INC = 584,
    MOD = 585,
    OFFSET = 586,
    JHASH = 587,
    SYMHASH = 588,
    SEED = 589,
    POSITION = 590,
    INDEX = 591,
    COMMENT = 592,
    XML = 593,
    JSON = 594,
    VM = 595,
    NOTRACK = 596,
    EXISTS = 597,
    MISSING = 598,
    EXTHDR = 599,
    IPSEC = 600,
    REQID = 601,
    SPNUM = 602,
    IN = 603,
    OUT = 604
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
#line 167 "parser_bison.y" /* yacc.c:352  */

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

#line 979 "parser_bison.c" /* yacc.c:352  */
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
#define YYLAST   7697

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  359
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  385
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1227
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2070

#define YYUNDEFTOK  2
#define YYMAXUTOK   604

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
static const yytype_uint16 yyrline[] =
{
       0,   897,   897,   898,   907,   908,   911,   912,   915,   916,
     917,   918,   919,   920,   921,   922,   923,   924,   925,   926,
     927,   928,   929,   930,   931,   932,   933,   934,   936,   938,
     946,   961,   968,   980,   988,   989,   990,   991,  1011,  1012,
    1013,  1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,  1022,
    1023,  1024,  1025,  1028,  1032,  1039,  1043,  1051,  1055,  1059,
    1066,  1073,  1077,  1084,  1093,  1097,  1101,  1105,  1109,  1113,
    1117,  1121,  1125,  1129,  1133,  1137,  1141,  1147,  1153,  1157,
    1164,  1168,  1176,  1183,  1190,  1194,  1201,  1210,  1214,  1218,
    1222,  1226,  1230,  1234,  1238,  1244,  1250,  1251,  1254,  1255,
    1258,  1259,  1262,  1263,  1266,  1270,  1274,  1278,  1282,  1286,
    1290,  1294,  1298,  1305,  1309,  1313,  1319,  1323,  1327,  1333,
    1339,  1343,  1347,  1351,  1355,  1359,  1363,  1367,  1371,  1375,
    1379,  1383,  1387,  1391,  1395,  1399,  1403,  1407,  1411,  1415,
    1419,  1423,  1427,  1431,  1435,  1439,  1443,  1447,  1451,  1455,
    1459,  1463,  1467,  1471,  1477,  1483,  1487,  1497,  1501,  1505,
    1509,  1513,  1517,  1523,  1527,  1531,  1535,  1539,  1543,  1547,
    1553,  1560,  1566,  1574,  1580,  1588,  1597,  1598,  1601,  1602,
    1603,  1604,  1605,  1606,  1607,  1608,  1611,  1612,  1615,  1616,
    1617,  1620,  1629,  1635,  1650,  1660,  1661,  1662,  1663,  1664,
    1675,  1685,  1696,  1706,  1717,  1728,  1737,  1746,  1755,  1766,
    1777,  1791,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1808,
    1818,  1819,  1820,  1827,  1848,  1859,  1870,  1883,  1888,  1889,
    1890,  1891,  1896,  1902,  1907,  1912,  1917,  1923,  1928,  1933,
    1934,  1945,  1946,  1949,  1953,  1956,  1957,  1958,  1959,  1963,
    1968,  1969,  1970,  1971,  1974,  1975,  1976,  1977,  1982,  1992,
    2003,  2014,  2026,  2035,  2040,  2046,  2051,  2060,  2063,  2067,
    2073,  2074,  2078,  2083,  2084,  2085,  2086,  2100,  2104,  2108,
    2114,  2119,  2126,  2131,  2136,  2139,  2146,  2153,  2166,  2173,
    2174,  2186,  2191,  2192,  2193,  2194,  2198,  2208,  2209,  2210,
    2211,  2215,  2225,  2226,  2227,  2228,  2232,  2243,  2247,  2248,
    2249,  2253,  2263,  2264,  2265,  2266,  2270,  2280,  2281,  2282,
    2283,  2287,  2297,  2298,  2299,  2300,  2304,  2314,  2315,  2316,
    2317,  2321,  2331,  2332,  2333,  2334,  2335,  2338,  2369,  2376,
    2380,  2383,  2393,  2400,  2411,  2424,  2439,  2440,  2443,  2455,
    2461,  2465,  2468,  2474,  2487,  2492,  2501,  2502,  2505,  2508,
    2509,  2510,  2513,  2528,  2529,  2532,  2533,  2534,  2535,  2536,
    2537,  2540,  2549,  2558,  2566,  2574,  2582,  2590,  2598,  2606,
    2614,  2622,  2630,  2638,  2646,  2654,  2662,  2670,  2678,  2682,
    2687,  2695,  2702,  2709,  2723,  2727,  2734,  2738,  2744,  2756,
    2762,  2769,  2775,  2782,  2783,  2784,  2785,  2788,  2789,  2790,
    2791,  2792,  2793,  2794,  2795,  2796,  2797,  2798,  2799,  2800,
    2801,  2802,  2803,  2804,  2805,  2806,  2807,  2810,  2811,  2814,
    2823,  2827,  2833,  2839,  2844,  2847,  2852,  2857,  2860,  2866,
    2871,  2879,  2880,  2882,  2886,  2894,  2898,  2901,  2905,  2911,
    2912,  2915,  2921,  2925,  2928,  3053,  3058,  3063,  3068,  3073,
    3079,  3109,  3113,  3117,  3121,  3125,  3131,  3135,  3138,  3142,
    3148,  3162,  3187,  3195,  3196,  3197,  3200,  3201,  3204,  3205,
    3220,  3236,  3244,  3245,  3246,  3249,  3250,  3253,  3254,  3255,
    3270,  3271,  3272,  3273,  3274,  3277,  3280,  3286,  3292,  3296,
    3300,  3307,  3314,  3321,  3328,  3334,  3340,  3346,  3349,  3350,
    3353,  3359,  3365,  3371,  3378,  3385,  3393,  3394,  3397,  3401,
    3409,  3413,  3416,  3421,  3426,  3430,  3436,  3452,  3471,  3477,
    3478,  3484,  3485,  3491,  3492,  3493,  3494,  3495,  3496,  3497,
    3498,  3499,  3500,  3501,  3502,  3503,  3506,  3507,  3511,  3517,
    3518,  3524,  3525,  3531,  3532,  3538,  3541,  3542,  3553,  3554,
    3557,  3561,  3564,  3570,  3576,  3577,  3580,  3581,  3582,  3585,
    3589,  3593,  3598,  3603,  3608,  3614,  3618,  3622,  3626,  3632,
    3637,  3641,  3649,  3658,  3659,  3662,  3665,  3669,  3674,  3680,
    3681,  3684,  3687,  3691,  3695,  3699,  3704,  3711,  3716,  3724,
    3729,  3738,  3739,  3745,  3746,  3747,  3750,  3751,  3755,  3759,
    3765,  3766,  3769,  3775,  3779,  3782,  3787,  3793,  3794,  3797,
    3798,  3799,  3802,  3803,  3809,  3810,  3813,  3814,  3817,  3823,
    3830,  3837,  3848,  3849,  3850,  3853,  3861,  3873,  3880,  3883,
    3889,  3893,  3896,  3902,  3911,  3922,  3928,  3954,  3955,  3964,
    3965,  3968,  3977,  3988,  3989,  3990,  3991,  3992,  3993,  3994,
    3995,  3996,  3997,  3998,  3999,  4000,  4001,  4002,  4005,  4028,
    4029,  4030,  4033,  4034,  4035,  4036,  4037,  4040,  4044,  4047,
    4051,  4058,  4061,  4077,  4078,  4082,  4088,  4089,  4095,  4096,
    4102,  4103,  4109,  4112,  4113,  4124,  4130,  4136,  4137,  4140,
    4146,  4147,  4148,  4151,  4158,  4163,  4168,  4171,  4175,  4179,
    4185,  4186,  4193,  4199,  4200,  4203,  4204,  4207,  4213,  4219,
    4223,  4226,  4230,  4234,  4244,  4248,  4251,  4257,  4264,  4268,
    4274,  4288,  4312,  4317,  4325,  4329,  4333,  4343,  4346,  4347,
    4350,  4351,  4352,  4353,  4364,  4375,  4381,  4402,  4408,  4425,
    4431,  4432,  4433,  4436,  4437,  4438,  4441,  4442,  4445,  4461,
    4467,  4473,  4480,  4494,  4502,  4510,  4516,  4520,  4524,  4528,
    4532,  4539,  4544,  4555,  4578,  4584,  4588,  4592,  4596,  4600,
    4604,  4608,  4612,  4618,  4624,  4632,  4633,  4634,  4637,  4638,
    4642,  4648,  4649,  4655,  4656,  4662,  4663,  4669,  4672,  4673,
    4674,  4683,  4694,  4695,  4698,  4706,  4707,  4708,  4709,  4710,
    4711,  4712,  4713,  4714,  4715,  4716,  4717,  4720,  4721,  4722,
    4723,  4724,  4731,  4738,  4745,  4752,  4759,  4766,  4773,  4780,
    4787,  4794,  4801,  4808,  4811,  4812,  4813,  4814,  4815,  4816,
    4817,  4820,  4824,  4828,  4832,  4836,  4840,  4846,  4847,  4857,
    4861,  4865,  4881,  4882,  4885,  4886,  4887,  4888,  4889,  4892,
    4893,  4894,  4895,  4896,  4897,  4898,  4899,  4900,  4901,  4902,
    4903,  4904,  4905,  4906,  4907,  4908,  4909,  4910,  4911,  4912,
    4913,  4914,  4915,  4918,  4938,  4942,  4956,  4960,  4964,  4970,
    4974,  4980,  4981,  4982,  4985,  4986,  4989,  4990,  4993,  4999,
    5000,  5003,  5004,  5007,  5008,  5011,  5012,  5015,  5023,  5050,
    5055,  5060,  5066,  5067,  5070,  5074,  5094,  5095,  5096,  5097,
    5100,  5104,  5108,  5114,  5115,  5118,  5119,  5120,  5121,  5122,
    5123,  5124,  5125,  5126,  5127,  5128,  5129,  5130,  5131,  5132,
    5133,  5134,  5137,  5138,  5139,  5140,  5141,  5142,  5143,  5146,
    5147,  5148,  5149,  5152,  5153,  5154,  5155,  5158,  5159,  5162,
    5168,  5176,  5189,  5196,  5202,  5208,  5217,  5218,  5219,  5220,
    5221,  5222,  5223,  5224,  5225,  5226,  5227,  5228,  5229,  5230,
    5231,  5232,  5233,  5234,  5237,  5246,  5247,  5248,  5251,  5257,
    5258,  5259,  5262,  5268,  5269,  5270,  5271,  5272,  5275,  5281,
    5282,  5283,  5284,  5285,  5286,  5287,  5288,  5289,  5292,  5296,
    5300,  5307,  5308,  5309,  5310,  5311,  5312,  5313,  5314,  5315,
    5316,  5317,  5318,  5321,  5322,  5323,  5324,  5327,  5328,  5329,
    5330,  5331,  5334,  5340,  5341,  5342,  5343,  5344,  5345,  5346,
    5349,  5355,  5356,  5357,  5358,  5361,  5367,  5368,  5369,  5370,
    5371,  5372,  5373,  5374,  5375,  5377,  5383,  5384,  5385,  5386,
    5387,  5388,  5389,  5390,  5393,  5399,  5400,  5401,  5402,  5403,
    5406,  5412,  5413,  5416,  5422,  5423,  5424,  5427,  5433,  5434,
    5435,  5436,  5439,  5445,  5446,  5447,  5448,  5451,  5455,  5459,
    5464,  5471,  5472,  5473,  5474,  5475,  5476,  5477,  5478,  5479,
    5480,  5483,  5484,  5485,  5486,  5487,  5488,  5489,  5490,  5491,
    5492,  5493,  5494,  5495,  5504,  5505,  5506,  5507,  5508,  5509,
    5510,  5511,  5514,  5520,  5521,  5522,  5525,  5526,  5527,  5528,
    5529,  5530,  5531,  5532,  5533,  5534,  5535,  5536,  5537,  5538,
    5539,  5540,  5541,  5542,  5545,  5546,  5547,  5550,  5551,  5552,
    5553,  5556,  5557,  5558,  5559,  5560,  5563,  5564,  5565,  5566,
    5569,  5574,  5578,  5582,  5586,  5590,  5594,  5599,  5604,  5609,
    5614,  5619,  5626,  5630,  5636,  5637,  5638,  5639,  5642,  5650,
    5651,  5654,  5655,  5656,  5657,  5658,  5659,  5660,  5661,  5664,
    5670,  5671,  5674,  5680,  5681,  5682,  5683,  5686,  5692,  5698,
    5704,  5707,  5713,  5714,  5715,  5716,  5722,  5728,  5729,  5730,
    5731,  5732,  5733,  5736,  5742,  5743,  5746,  5752,  5753,  5754,
    5755,  5756,  5759,  5773,  5774,  5775,  5776,  5777
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
  "\"wscale\"", "\"typeof\"", "\"hook\"", "\"hooks\"", "\"device\"",
  "\"devices\"", "\"table\"", "\"tables\"", "\"chain\"", "\"chains\"",
  "\"rule\"", "\"rules\"", "\"sets\"", "\"set\"", "\"element\"", "\"map\"",
  "\"maps\"", "\"flowtable\"", "\"handle\"", "\"ruleset\"", "\"trace\"",
  "\"inet\"", "\"netdev\"", "\"add\"", "\"update\"", "\"replace\"",
  "\"create\"", "\"insert\"", "\"delete\"", "\"get\"", "\"list\"",
  "\"reset\"", "\"flush\"", "\"rename\"", "\"describe\"", "\"import\"",
  "\"export\"", "\"monitor\"", "\"all\"", "\"accept\"", "\"drop\"",
  "\"continue\"", "\"jump\"", "\"goto\"", "\"return\"", "\"to\"",
  "\"constant\"", "\"interval\"", "\"dynamic\"", "\"auto-merge\"",
  "\"timeout\"", "\"gc-interval\"", "\"elements\"", "\"expires\"",
  "\"policy\"", "\"memory\"", "\"performance\"", "\"size\"", "\"flow\"",
  "\"offload\"", "\"meter\"", "\"meters\"", "\"flowtables\"", "\"number\"",
  "\"string\"", "\"quoted string\"", "\"string with a trailing asterisk\"",
  "\"ll\"", "\"nh\"", "\"th\"", "\"bridge\"", "\"ether\"", "\"saddr\"",
  "\"daddr\"", "\"type\"", "\"vlan\"", "\"id\"", "\"cfi\"", "\"dei\"",
  "\"pcp\"", "\"arp\"", "\"htype\"", "\"ptype\"", "\"hlen\"", "\"plen\"",
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
  "\"option\"", "\"echo\"", "\"eol\"", "\"nop\"", "\"sack\"", "\"sack0\"",
  "\"sack1\"", "\"sack2\"", "\"sack3\"", "\"sack-permitted\"",
  "\"timestamp\"", "\"kind\"", "\"count\"", "\"left\"", "\"right\"",
  "\"tsval\"", "\"tsecr\"", "\"dccp\"", "\"sctp\"", "\"chunk\"",
  "\"data\"", "\"init\"", "\"init-ack\"", "\"heartbeat\"",
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
  "limit_burst_pkts", "limit_burst_bytes", "time_unit", "reject_stmt",
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
  "queue_stmt_arg", "queue_stmt_expr_simple", "queue_stmt_expr",
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
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
      61,   123,   125,    40,    41,   124,    36,    91,    93
};
# endif

#define YYPACT_NINF -1682

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1682)))

#define YYTABLE_NINF -959

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1682,  7175, -1682,   584, -1682, -1682,   130,   173,   173,   173,
    1544,  1544,  1544,  1544,  1544,  1544,  1544,  1544, -1682, -1682,
    2477,   248,  2567,   283,  1585,   359,  6713,   518,  1069,   293,
    6638,   146,   149,   373, -1682, -1682, -1682, -1682,   290,  1544,
    1544,  1544,  1544, -1682, -1682, -1682,   814, -1682,   173, -1682,
     173,   102,  6028, -1682,   584, -1682,   148,   154,   584,   173,
   -1682,   164,   183,  6028,   173, -1682,   -63, -1682,   173, -1682,
   -1682,  1544, -1682,  1544,  1544,  1544,  1544,  1544,  1544,  1544,
     319,  1544,  1544,  1544,  1544, -1682,  1544, -1682,  1544,  1544,
    1544,  1544,  1544,  1544,  1544,  1544,   412,  1544,  1544,  1544,
    1544, -1682,  1544, -1682,  1544,  1544,  1544,  1544,  1544,  1544,
    1226,  1544,  1544,  1544,  1544,  1544,   208,  1544,  1544,  1544,
     240,  1544,  1366,  1601,  1662,  1737,  1544,  1544,  1544,  1745,
   -1682,  1544,  1799,  1808,  1544, -1682,  1544,  1544,  1544,  1544,
    1544,   589,  1544, -1682,  1544, -1682,  1074,   676,   253,   424,
   -1682, -1682, -1682, -1682,   759,  1206,   954,  1383,  3096,  1168,
     218,  2000,  2070,  1042,   152,   543,   741,   749,  2406,   570,
     567,   533,   418,   422,   491,   420,   804,   430,   747,  4300,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682,  4903, -1682, -1682,   280,  6283,   315,  1127,   494,  6638,
     173, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682,   989, -1682, -1682,   323,
   -1682, -1682,   989, -1682, -1682, -1682, -1682,  1059, -1682, -1682,
   -1682,  1544,  1544,  1544,   -38, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682,   596,   600,   606, -1682, -1682, -1682,   538,   437,
     966, -1682, -1682, -1682, -1682, -1682, -1682,    26,    26, -1682,
     171,   173,  5989,  4705,   446, -1682,    25,   683, -1682, -1682,
   -1682, -1682, -1682,   138,   668,   644, -1682,   770, -1682,   441,
    6028, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,   697,
   -1682,   710, -1682, -1682, -1682,   477, -1682,  4603, -1682, -1682,
     641, -1682,    76, -1682,   266, -1682, -1682, -1682, -1682,  1089,
   -1682,   101, -1682, -1682,   762, -1682, -1682, -1682,   973,   806,
     820,   495, -1682,   212, -1682,  5593, -1682, -1682, -1682,   818,
   -1682, -1682, -1682,   821, -1682,  5860,  5860, -1682, -1682,    90,
     526,   536, -1682, -1682,   582, -1682, -1682, -1682,   587, -1682,
     616,   901,  6028, -1682,   164,   183, -1682,   -63, -1682, -1682,
    1544,  1544,  1544,   685, -1682, -1682, -1682,  6028, -1682,   225,
   -1682, -1682, -1682,   255, -1682, -1682, -1682,   259, -1682, -1682,
   -1682, -1682,   356, -1682, -1682,   -63, -1682,   421,   623, -1682,
   -1682, -1682, -1682,  1544, -1682, -1682, -1682, -1682,   -63, -1682,
   -1682, -1682,   933, -1682, -1682, -1682, -1682,  1544, -1682, -1682,
   -1682, -1682, -1682, -1682,  1544,  1544, -1682, -1682, -1682,   956,
     968, -1682,  1544,   994, -1682,  1544, -1682,  1544, -1682,  1544,
   -1682,  1544, -1682, -1682, -1682, -1682,  1544, -1682, -1682, -1682,
    1544, -1682,  1544, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
    1544, -1682,   173, -1682, -1682, -1682,  1039, -1682, -1682, -1682,
   -1682, -1682,   988,   112, -1682, -1682,   751, -1682, -1682,   938,
     100, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682,   196,   566, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682,   919, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682,   763, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
    3093, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682,   365, -1682, -1682,   708, -1682, -1682, -1682,
   -1682, -1682, -1682,   719, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682,  1283, -1682, -1682, -1682,
   -1682,   757,   474,   768,  1001, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682,   761,   752, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682,   989, -1682, -1682,
   -1682, -1682,   -32,   -83,    24,    70, -1682, -1682, -1682,  4801,
    1031,  6804,  6638, -1682, -1682, -1682, -1682,  1097,  1107,    40,
    1081,  1090,  1099,    53,  1108,  1283,  1121,  6804,  6804,   729,
    6804, -1682, -1682,  1082,  6638,   712,  6804,  6804,  1111, -1682,
    5662,   103, -1682,  1316, -1682, -1682,   824, -1682,  1124,  1130,
     697, -1682, -1682,   607,  1316,  1150,  1157,  1163,  1316,   710,
   -1682,   450, -1682,  6804, -1682,  4999,  1189,  1206,   954,  1383,
    3096, -1682,  2000,   664, -1682, -1682, -1682,  1198, -1682, -1682,
   -1682, -1682,  6804, -1682,  1096,  1267,  1277,   942,   724,   554,
   -1682, -1682, -1682, -1682,  1294,  1114,  1301, -1682, -1682, -1682,
   -1682,  1302, -1682, -1682, -1682, -1682,   143, -1682, -1682,  1307,
    1314, -1682,  1222,  1230, -1682, -1682,   641, -1682,  1329, -1682,
   -1682, -1682, -1682,  1334, -1682,  5197, -1682,  1334, -1682,  7271,
   -1682, -1682,  1089, -1682,  1336, -1682,   173, -1682,   995, -1682,
     173,    74, -1682,  7271,  7271,  7271,  7271,  7271,  6638,   179,
    7002, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682,  7271, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682,   303, -1682,  1110,  1330,  1331,  1018,   649,
    1342, -1682, -1682, -1682,  7002,  6804,  6804,  1250,   117,   584,
    1349, -1682,   736,   584,  1275, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682,  1340,  1032,  1038,  1040, -1682,  1045,
    1046, -1682, -1682, -1682, -1682,  1116,  1093,   838,  1316, -1682,
    1299,  1305,  1313,  1315, -1682,  1320,  1058, -1682, -1682, -1682,
   -1682, -1682, -1682,  1325, -1682, -1682, -1682, -1682, -1682,  1544,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682,  1327,   676, -1682, -1682, -1682,
   -1682,  1345, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682,   108, -1682, -1682,
    2192, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682,   864,   798,  1079,   874,   874, -1682,
   -1682, -1682,  1183, -1682, -1682, -1682, -1682,  1207,  1212, -1682,
    1223,  1224,  1229,   286, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682,  1356,  1357, -1682, -1682, -1682, -1682,  1053, -1682,
    1091, -1682, -1682, -1682, -1682, -1682, -1682, -1682,  1360,  1361,
    1120, -1682,  1362,    59, -1682, -1682, -1682,  1115,  1117,  1123,
    1365, -1682, -1682,   729, -1682, -1682, -1682,  1367, -1682, -1682,
   -1682, -1682,  6804,  3096,  2000,  1466,  5395, -1682,   101,   109,
    1464,  1316,  1316,  1374,  6638,  6804,  6804,  6804, -1682,  1376,
    6804,  1427,  6804, -1682, -1682, -1682, -1682,  1378, -1682,    58,
   -1682,   474, -1682,   174,   247,   111,  1438, -1682,  6804, -1682,
     770,  1214,   302,   181, -1682,   876,  1342,   770, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682,  1339,   276, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682,   788,   810,  1414,
     848, -1682,  6804,  1483,  6804, -1682, -1682, -1682,   304,   320,
    6804,  1136, -1682, -1682,  6804,  6804,  6804,  6804,  6804,  1387,
    6804,  6804,   192,  6804,  1334,  6804,  1408,  1489,  1415,  2998,
    2998, -1682, -1682, -1682,  6804,  1114,  6804,  1114, -1682,   287,
   -1682,  1476, -1682,   712, -1682,  6638, -1682,  6638, -1682, -1682,
   -1682,  1110,  1330,  1331, -1682,   770, -1682, -1682, -1682, -1682,
   -1682, -1682,  1155,  7271,  7271,  7271,  7271,  7271,  7271,  7271,
    7271,  7341,  7271,  7271,   331, -1682,   790, -1682, -1682, -1682,
   -1682, -1682,  1410, -1682,   501,   213,  3125,  3339,   744,  2308,
     597, -1682, -1682, -1682, -1682, -1682, -1682,  1170,  1171,  1172,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682,  1507, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,  1518,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,  1169,  1173,
   -1682, -1682, -1682, -1682, -1682, -1682,  1120,   423,  1424, -1682,
   -1682, -1682, -1682, -1682,  1138, -1682, -1682, -1682,  1245,  1118,
   -1682,  1431,  1915, -1682,   835,    58, -1682,   416, -1682, -1682,
    6804,  6804,  1533, -1682,  1437,  1437, -1682,   109, -1682, -1682,
   -1682,  1190,  1464,  6028,   109, -1682, -1682, -1682, -1682, -1682,
   -1682,  6804, -1682, -1682,   145, -1682, -1682, -1682,  1240, -1682,
    6638,  7271,  6804,  1500, -1682,  7223, -1682,  1363,  1265,  1256,
     302, -1682,  1437,  1437, -1682,   181, -1682,  5662, -1682,  4339,
   -1682, -1682, -1682, -1682,  1553, -1682, -1682,  1119, -1682, -1682,
    1119, -1682, -1682,  1119, -1682, -1682,  6804, -1682, -1682, -1682,
   -1682, -1682,  1096,  1267,  1277, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682,  1556,  6804,  1398,  6804, -1682, -1682, -1682, -1682,
    1114, -1682,  1114,  1334, -1682,   125,  6028,  5731,   127, -1682,
   -1682, -1682,  1349,  1558, -1682, -1682,  1110,  1330,  1331, -1682,
     170,  1349, -1682, -1682,   876,  7271,  7341, -1682,  1461,  1531,
   -1682, -1682, -1682, -1682, -1682,   173,   173,   173,   173,   173,
    1469,   433,   173,   173,   173,   173, -1682, -1682, -1682,   584,
   -1682,    91,  1470,  1477, -1682, -1682, -1682,   584,   584,   584,
     584,   584,  6638, -1682,  1437,  1437,  1231,  1135,  1474,   511,
     997,  1395, -1682, -1682, -1682,   584,   584,   329, -1682,  6638,
    1437,  1233,   511,   997, -1682, -1682, -1682,   584,   584,   329,
    1484,  1247,  1492, -1682, -1682, -1682, -1682,  3507,  3673,  2813,
    3857,   951, -1682, -1682, -1682, -1682, -1682, -1682, -1682,  1034,
   -1682, -1682,  1493, -1682, -1682,  1498, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682,  1501, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682,   646,   116,  1933,  1504, -1682, -1682, -1682, -1682,
   -1682,   189, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682,  1240, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
    6804, -1682, -1682, -1682, -1682,  6638,  1242,   109, -1682, -1682,
   -1682, -1682, -1682,   930,  1308,  1505, -1682, -1682, -1682, -1682,
    6804,    26,    26,   770,  1342, -1682,    69,  1508, -1682,   729,
   -1682, -1682, -1682, -1682, -1682, -1682,   584, -1682,   276, -1682,
   -1682, -1682, -1682,  6804, -1682,  1535, -1682,  1334,  1334,  6638,
   -1682,   151,  1259,  1610,   770, -1682,  1349,  1349,  1435,  1519,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
     173,   173,   173, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682,  1583, -1682, -1682, -1682, -1682, -1682, -1682,
     878, -1682,   584,   584,   -63, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682,  1006, -1682, -1682, -1682,
   -1682, -1682,  1186, -1682, -1682, -1682, -1682, -1682,   787,   584,
     -63,   823,  1186, -1682, -1682, -1682,  1478,   292,   584, -1682,
   -1682, -1682, -1682, -1682, -1682,   996,   231,  2141, -1682, -1682,
    1624, -1682,  1120, -1682, -1682,  1297,   549,  1544, -1682, -1682,
   -1682, -1682, -1682,  1437,  1542,   549,  1546,  1544, -1682, -1682,
   -1682, -1682, -1682,  1529,  1544, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682,   930,  1308, -1682, -1682, -1682, -1682, -1682,  6028,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682,  1350,  1547, -1682,
      58, -1682, -1682, -1682, -1682, -1682, -1682,  1550,  1369,  1555,
   -1682, -1682, -1682,  6804,  1318,  6638, -1682, -1682,  1598,  5731,
   -1682, -1682,  1475,   584,  1321,  1322,  1323,  1332,  1335, -1682,
   -1682, -1682,  1337,  1338,  1346,  1347,  1563,  6638, -1682, -1682,
   -1682, -1682,   511, -1682,   997, -1682,  6472, -1682, -1682,  1141,
   -1682,   177,   584,    37,   584, -1682, -1682, -1682, -1682, -1682,
    1588, -1682,  1348, -1682, -1682,   584,   584, -1682,   584,   584,
     584,   584,   584, -1682,  1567,   584, -1682,  1350, -1682,  1344,
    1589, -1682,   142, -1682, -1682, -1682, -1682,  1599,   211, -1682,
   -1682,  1351,   770, -1682, -1682,  1435, -1682, -1682, -1682, -1682,
   -1682,  1354,  1355,  1364, -1682, -1682, -1682, -1682,  1218, -1682,
   -1682, -1682,  6638,   584,  1694,  1700,   511, -1682, -1682, -1682,
   -1682,   584,  1006,  1611, -1682, -1682, -1682,   834, -1682, -1682,
   -1682, -1682, -1682,   128, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682,  1616, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
     549, -1682, -1682, -1682,  1430, -1682, -1682, -1682, -1682, -1682,
     930,  1308, -1682, -1682,  1475,  2301,  4007,  3044,  4184,  1219,
   -1682, -1682, -1682,  2421,  2463,  1813,  1073,    47,  1371,  1478,
     878, -1682,  6638,  1006, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682,  1622,  1625,   107, -1682,  1723,   131, -1682,   584, -1682,
   -1682,  1350, -1682, -1682,   584,   584,   584,   584,   584,  2027,
     548,  2160,   584,   584,   584,   584, -1682, -1682,   292, -1682,
   -1682,  1721, -1682, -1682, -1682, -1682, -1682,  1628,  1616,   584,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
     584,   584,   584, -1682, -1682, -1682, -1682, -1682, -1682, -1682
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     363,   363,   363,   363,   363,   363,   363,   363,   367,   370,
     363,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   369,     8,    14,    15,     0,   363,
     363,   363,   363,    35,    34,     3,     0,    38,     0,   364,
       0,   388,     0,    33,     0,   358,     0,     0,     0,     0,
     528,    53,    55,     0,     0,   227,     0,   249,     0,   272,
      39,   363,    40,   363,   363,   363,   363,   363,   363,   363,
       0,   363,   363,   363,   363,    41,   363,    42,   363,   363,
     363,   363,   363,   363,   363,   363,     0,   363,   363,   363,
     363,    43,   363,    44,   363,   394,   363,   394,   363,   394,
     394,   363,   363,   394,   363,   394,     0,   363,   394,   394,
       0,   363,   394,   394,   394,   394,   363,   363,   363,   394,
      18,   363,   394,   394,   363,    46,   363,   363,   363,   363,
     394,     0,   363,    47,   363,    48,     0,     0,     0,   681,
     652,   359,   360,   361,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     859,   860,   861,   862,   863,   864,   865,   866,   867,   868,
     869,   870,   871,   872,   873,   874,   875,   876,   877,   878,
     880,     0,   882,   881,     0,     0,     0,     0,    17,     0,
       0,    52,   648,   647,   653,   654,   191,   664,   665,   658,
     850,   659,   662,   666,   663,   660,   661,   655,   966,   967,
     968,   969,   970,   971,   972,   973,   974,   975,   976,   977,
     978,   979,   980,   981,   982,   983,   656,  1181,  1182,  1183,
    1184,  1185,  1186,  1187,  1188,   657,     0,   188,   189,     0,
      49,   172,     0,    50,   174,   177,    51,   178,   368,   365,
     366,   363,   363,   363,    10,   774,   747,   749,    37,    36,
     371,   373,     0,     0,     0,   390,   389,   391,     0,   518,
       0,   632,   633,   634,   841,   842,   843,   427,   428,   846,
     639,     0,     0,     0,   443,   451,     0,   475,   496,   508,
     509,   585,   591,   612,     0,     0,   886,     7,    58,   396,
     398,   411,   399,   211,   426,   407,   431,   406,    10,   441,
      28,   449,   404,   405,   414,   499,   415,     0,   416,   425,
     516,   419,   584,   420,   590,   421,   422,   417,    22,   610,
     423,     0,   424,   409,     0,   638,   408,   683,   686,   688,
     690,   692,   693,   700,   702,     0,   701,   645,   430,   850,
     412,   418,   410,   655,    29,     0,     0,    32,   382,     0,
       0,     0,    57,   376,     0,    61,   242,   241,     0,   379,
       0,     0,     0,   528,    78,    80,   227,     0,   249,   272,
     363,   363,   363,    10,   774,   747,   749,     0,   118,     0,
     102,   103,   104,     0,    96,    97,   105,     0,    98,    99,
     106,   107,     0,   100,   101,     0,   108,     0,   110,   111,
     751,   752,   750,   363,    10,    19,    21,    26,     0,   141,
     153,   395,   155,   120,   121,   122,   123,   363,   124,   126,
     150,   149,   148,   142,   363,   394,   146,   145,   147,   751,
     752,   753,   363,     0,    10,   363,   127,   363,   130,   363,
     133,   363,   139,    19,    21,    26,   363,   136,    45,    10,
     363,   157,   363,   160,    21,   163,   164,   165,   166,   169,
     363,   168,     0,   985,   986,   987,     0,   672,   673,   674,
     675,   676,   678,     0,   891,   893,     0,   892,    27,     0,
       0,  1179,  1180,  1178,   989,   990,   991,    11,   997,   993,
     994,   995,   996,    16,     0,     0,   999,  1000,  1001,  1002,
    1003,     8,  1021,  1022,  1016,  1011,  1012,  1013,  1014,  1015,
    1017,  1018,  1019,  1020,     0,    14,  1033,  1036,  1035,  1034,
    1037,  1038,  1039,  1032,  1041,  1042,  1043,  1044,  1040,  1053,
    1054,  1046,  1047,  1048,  1050,  1049,  1051,  1052,    15,  1056,
    1061,  1058,  1057,  1062,  1060,  1059,  1063,  1055,  1066,  1069,
    1065,  1067,  1068,  1064,  1072,  1071,  1070,  1074,  1075,  1076,
    1073,  1080,  1081,  1078,  1079,  1077,  1086,  1083,  1084,  1085,
    1082,  1099,  1093,  1096,  1097,  1091,  1092,  1094,  1095,  1098,
    1100,     0,  1087,  1125,  1123,  1124,  1122,  1177,  1174,  1175,
       0,  1176,    24,  1195,    14,  1194,   918,    15,  1193,  1196,
     916,   917,    17,     0,    23,    23,     0,  1197,  1200,  1199,
    1203,  1202,  1204,     0,  1201,  1191,  1190,  1189,  1212,  1209,
    1207,  1208,  1210,  1211,  1206,  1215,  1214,  1213,  1219,  1218,
    1221,  1217,  1220,  1216,   851,   854,   855,   856,    26,   857,
      17,   849,   852,   853,   933,   934,   940,   926,   927,   925,
     935,   936,   956,   929,   938,   931,   932,   937,   928,   930,
     923,   924,   954,   953,   955,    26,     0,     9,   941,   897,
     896,     0,   700,     0,     0,    23,  1223,  1225,  1226,  1227,
    1222,   901,   902,   879,   900,     0,   646,   171,   190,   173,
     179,   180,   182,   181,   184,   185,   183,   186,   771,   771,
     771,    63,     0,     0,   475,     0,   385,   386,   387,     0,
       0,     0,     0,   848,   847,   844,   845,     0,     0,     0,
     851,   849,     0,     0,     0,     0,     9,     0,     0,   484,
       0,   473,   474,     0,     0,     0,     0,     0,     0,     6,
       0,     0,   704,     0,   397,   400,     0,   403,     0,     0,
     442,   445,   413,     0,     0,     0,     0,     0,     0,   450,
     452,     0,   495,     0,   813,     0,     0,    11,    16,     8,
      14,   812,    15,     0,   816,   814,   815,     0,   811,   810,
     802,   803,     0,   546,   549,   551,   553,   555,   556,   561,
     566,   564,   565,   567,   569,   507,   533,   534,   544,   804,
     535,   542,   536,   543,   539,   540,     0,   537,   538,     0,
     568,   541,     0,     0,   525,   524,   517,   520,     0,   603,
     604,   605,   583,   588,   601,     0,   589,   594,   606,     0,
     624,   625,   611,   613,   616,   622,     0,   650,     0,   649,
       0,     0,   640,     0,     0,     0,     0,     0,     0,     0,
       0,   834,   835,   836,   837,   838,   839,   840,    11,    16,
       8,    14,   826,   827,    15,   828,   825,   824,   829,   822,
     823,   821,   830,    24,   832,     0,   817,   787,   818,   697,
     698,   799,   786,   776,   775,   791,   793,   795,   797,   798,
     785,   819,   820,   788,     0,     0,     0,     0,     7,     0,
     741,   740,   798,     0,     0,   327,    75,   195,   212,   228,
     254,   273,   392,    77,     0,     0,     0,     0,    84,     0,
       0,   771,   771,   771,    86,     0,     0,   475,     0,    95,
       0,     0,     0,     0,   109,     0,     0,   771,   113,   116,
     114,   117,   119,     0,   156,   125,   144,   143,     9,   363,
     129,   128,   131,   134,   140,   135,   132,   138,   137,   159,
     158,   161,   162,   167,   170,     0,     0,   671,   669,   670,
      12,     0,   889,   682,   679,   680,   988,   992,    11,    14,
      11,    14,   998,  1023,  1024,  1025,  1026,    14,  1008,  1045,
       0,  1103,  1113,  1104,  1111,  1101,  1102,  1106,  1107,  1108,
    1109,  1110,  1105,  1112,  1089,  1129,  1126,  1127,  1128,  1130,
    1131,  1132,  1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,
    1141,  1142,  1143,  1160,    25,  1172,   912,   913,   919,    23,
     914,  1192,     0,     0,   858,   939,   942,   943,     0,   945,
       0,   944,   946,   947,     9,     9,   948,   920,     0,     0,
     894,  1224,     0,     0,   667,   175,   187,     0,     0,     0,
       0,   292,    10,   484,   317,    19,   297,     0,    21,   322,
     748,    26,     0,    14,    15,   510,     0,   519,     0,   626,
     628,     0,     0,     0,     0,     0,     0,     0,     9,     0,
       0,   948,     0,   444,    19,   482,   483,     0,    21,     0,
      22,     0,   621,   619,   620,     0,   597,   599,     0,   716,
       7,     7,   718,   713,   715,   798,   737,     7,   703,   393,
     220,   447,   448,   446,   465,    11,     0,     0,   463,   459,
     454,   455,   456,   457,   460,   458,   453,     0,     0,     0,
       0,   575,     0,   570,     0,   805,   808,   809,   806,   807,
       0,     0,   533,   542,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   577,     0,     0,     0,     0,     0,
       0,   522,   523,   521,     0,     0,     0,   592,   615,   617,
     618,     0,   614,     0,   651,     0,   642,     0,   641,   684,
     685,   687,   689,   691,   694,     7,   432,   434,   699,   806,
     807,   831,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   782,   781,   798,   884,   965,   743,
     742,    30,     0,    31,     0,     0,     0,     0,     0,     0,
       0,    94,   195,   212,   228,   254,   273,     0,     0,     0,
      10,    19,    21,    26,   383,   372,   374,   377,   380,   273,
       9,   154,   151,     9,     0,   677,   668,    27,  1004,  1006,
    1005,  1007,  1027,  1028,  1030,  1029,  1031,  1010,    14,     0,
    1116,  1115,  1114,  1117,  1118,  1119,  1120,  1121,  1088,  1157,
    1156,  1158,  1159,  1165,  1147,  1148,  1149,  1150,  1162,  1151,
    1152,  1153,  1154,  1155,  1163,  1164,  1166,  1167,  1168,  1169,
    1170,  1171,  1144,  1146,  1145,  1161,    24,   915,     0,     0,
      14,    14,    15,    15,   921,   922,   894,   894,     0,    13,
     899,   903,   904,    17,     0,   307,   312,   302,     0,     0,
      64,     0,     0,    71,     0,     0,    66,     0,    73,   512,
       0,     0,   511,   629,     0,     0,   723,   627,   719,   888,
     887,     0,   712,     0,   710,   885,   883,     9,   439,     9,
       9,     0,     9,   472,     0,   481,   477,   476,   478,   607,
       0,     0,     0,     0,   707,     0,   708,     0,    10,     0,
     717,   726,     0,     0,   736,   714,   724,   706,   705,     0,
     464,    14,   468,   469,   461,   467,   497,     0,   501,   498,
       0,   503,   506,     0,   505,   576,     0,   580,   582,   545,
     547,   548,   550,   552,   554,   562,   563,   557,   560,   559,
     558,   572,   571,     0,     0,     0,   957,   958,   959,   960,
     586,   602,   593,   595,   623,     0,     0,     0,     0,   435,
     833,   784,   778,     0,   789,   790,   792,   794,   796,   783,
     695,   777,   696,   800,   801,     0,     0,   695,     0,     0,
      76,   329,   328,   331,   330,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    54,   197,   196,     0,
     194,     0,     0,     0,    56,   214,   213,     0,     0,     0,
       0,     0,     0,   238,     0,     0,     0,     0,     0,     0,
       0,     0,    59,   230,   229,     0,     0,     0,   401,     0,
       0,     0,     0,     0,    60,   256,   255,     0,     0,     0,
       0,     0,     0,    10,    62,   275,   274,     0,     0,     0,
       0,     0,   307,   312,   302,    87,    92,    88,    93,     0,
     115,   152,     0,   890,  1009,     0,  1173,  1198,  1205,   949,
     950,   951,   952,    20,     0,    13,   895,   911,   907,   906,
     905,    17,     0,     0,     0,     0,    10,   294,   293,   296,
     295,     0,    19,   319,   318,   321,   320,    21,   299,   298,
     301,   300,   478,    26,   324,   323,   326,   325,   513,   515,
       0,   362,   721,   722,   720,     0,     0,   711,   962,   440,
     963,     9,   961,     0,   487,     0,    21,    22,    22,   598,
       0,     0,     0,     7,   738,   739,     0,     0,   728,   484,
     727,   734,   735,   725,   429,   221,     0,   462,     0,   500,
     502,   504,   573,     0,   579,     0,   581,   587,   596,     0,
     630,     0,     0,     0,     7,   433,   780,   779,   529,     0,
     384,   291,   375,   211,   378,   227,   249,   381,   272,   193,
       0,     0,     0,   291,   291,   291,   291,   198,   356,   357,
     353,   355,   354,     0,   352,   215,   217,   216,   219,   218,
       0,   225,     0,     0,     0,   271,   270,   268,   269,   332,
     334,   335,   333,   288,   336,   289,     0,   287,   245,   246,
     248,   247,     0,   244,   239,   240,   236,   402,     0,     0,
       0,     0,     0,   267,   266,   264,     0,     0,     0,   278,
      79,    81,    82,    83,    85,     0,     0,     0,   112,   984,
       0,   898,   894,   910,   908,     0,     0,     0,     9,   309,
     308,   311,   310,     0,     0,     0,     0,     0,     9,   314,
     313,   316,   315,     0,     0,     9,   304,   303,   306,   305,
     744,    65,     0,   487,    72,    67,   746,    74,   514,     0,
     643,   964,   490,   491,   492,   493,   494,   485,     0,    19,
       0,   480,   608,   609,   600,   709,     9,     0,     0,     0,
     222,   466,   574,     0,     0,     0,   631,   637,     0,   437,
     436,   530,   531,     0,     0,     0,     0,     0,     0,   291,
     291,   291,     0,     0,     0,     0,     0,     0,   232,   234,
     235,   237,     0,   231,     0,   233,     0,   257,   265,     0,
     263,     0,     0,     0,     0,   281,   279,     9,     9,     9,
       0,    13,     0,   757,   756,     0,     0,    69,     0,     0,
       0,     0,     0,    70,     0,     0,    68,   485,   773,     0,
       0,    19,     0,   471,   479,   732,     9,     0,     0,   578,
     635,     0,     7,   532,   526,   529,   327,   212,   228,   254,
     273,     0,     0,     0,   292,   317,   297,   322,   351,   226,
     290,   243,     0,     0,     0,   223,     0,    10,    19,    21,
      26,     0,     0,     0,   346,   340,   339,   343,   338,   341,
     342,   276,   285,     0,   282,   286,   277,    90,    91,    89,
    1090,   909,     0,   763,   765,   768,   769,   766,   767,   770,
       0,   759,   772,   644,     0,   470,   489,   488,   733,    10,
       0,   487,   636,   438,   531,     0,     0,     0,     0,     0,
     307,   312,   302,     0,     0,     0,     0,     0,     0,     0,
       0,   260,     0,     0,   250,   252,   251,   253,   262,   258,
     347,     0,     0,     7,   280,     0,     0,   760,     0,   486,
     729,   485,    19,   527,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   348,   349,     0,   337,
     261,   224,   259,   345,   344,   284,   283,     0,     0,     0,
     758,    19,   731,   210,   199,   200,   201,   202,     9,     9,
       9,    10,    19,    21,    26,   350,   762,   761,   764,   730,
       0,     0,     0,   203,   208,   204,   209,   206,   207,   205
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1682, -1682,    -1, -1111,    29,  -851,  -311,  -466, -1682, -1469,
     -18,   -17,  1220,  -604, -1682,  -467, -1682,  -469, -1067,  -568,
    -834, -1682,  -465,   457, -1682,    20, -1682, -1682,  1725, -1682,
   -1682, -1682, -1682, -1682, -1682,  1239, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
      15, -1682,  1352, -1682,   487,  -316, -1213, -1682, -1682, -1462,
    -384, -1212,  -370,   210,   -97,  -382, -1682, -1219, -1211, -1682,
    -388, -1217,  -268, -1682,  -245,   -91, -1459,  -972,  -152,  -153,
   -1490, -1487, -1485,  -149,  -150,  -138, -1682, -1682,  -220, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682,   402,  -697, -1250,
    1683,   -25,  2870, -1682,  1527, -1682, -1682,    55, -1682,   281,
     652, -1682, -1682,  2312, -1682,  -837,  1389, -1682, -1682,   198,
    1695,  1041,  2810,   -39, -1682, -1682, -1218, -1215,  -317, -1682,
   -1682, -1682, -1682, -1682, -1682,   114, -1682, -1682, -1682, -1682,
    1005, -1682, -1682, -1682,   985, -1682, -1682, -1682,   133, -1682,
    1485, -1299,   182, -1682, -1033, -1681, -1612, -1596, -1682, -1682,
    -872, -1682, -1682, -1682, -1682, -1682, -1682, -1682,   949,  -323,
    1411,  -102,  -166,  -281,   626,   622,   625, -1682,  -726, -1682,
   -1682, -1682, -1682, -1682, -1682,  1883, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682,  -319,   611, -1682, -1682, -1682,
   -1682,   958,   425,   428,  1060,   610, -1161, -1682, -1682,  1541,
   -1682, -1682, -1682, -1682,   962, -1682, -1682,    75,   -29,  -753,
    -312,   859,   -11, -1682, -1682, -1682,   839,   -26, -1682, -1682,
   -1682, -1682, -1682,  -174,  -183, -1682,  -794,   591,  -703,  1632,
     -58, -1682,   691, -1144, -1682, -1378, -1682, -1682,   463, -1238,
   -1682, -1682,   438,   434, -1682, -1682,  1479,  -586,  1447,  -580,
    1452,  -571,  1459,  1738, -1682, -1575, -1682, -1682,  -172, -1682,
   -1682,  -373,  -555,  1467, -1682,  -332,  -307,  -779,  -773,  -768,
   -1682,  -270,  -756, -1682,  1797,  1319,  -761, -1682, -1333,  -289,
     226,  1570, -1682,   -21, -1682,   285, -1682, -1245, -1682,   410,
   -1682, -1682, -1682, -1682, -1682,   688,  -256,   923,  1249,  1244,
    1582,  1584, -1682, -1682,  -483,   106, -1682, -1682, -1682,  1268,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682,   853, -1682, -1682, -1682, -1682, -1682, -1682,   851,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682, -1682,
   -1682, -1682, -1682, -1682, -1682
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1555,   770,  1177,  1077,   731,  1175,  1286,  1587,
    1229,  1230,  1176,   713,   478,   969,  1761,   970,   858,  1060,
    1055,  1336,   971,  1002,   782,  1556,    45,    46,    47,    72,
      85,    87,   412,   416,   421,   408,   101,   103,   130,   974,
     440,   135,   143,   145,   260,   263,   266,   267,   727,  1085,
     261,   211,   380,  1509,  1256,   381,  1257,  1419,  1923,  1710,
     384,  1258,   385,  1732,  1733,   388,  1931,  1259,  1535,  1717,
     390,  1260,  1864,  1943,  1944,  1725,  1726,  1834,  1359,  1364,
    1594,  1592,  1593,  1362,  1367,  1255,  1727,  1517,  1862,  1937,
    1938,  1939,  1989,  1518,  1519,  1700,  1701,  1680,   212,  1622,
      48,    49,    59,   415,    51,   419,  1683,    65,   424,  1685,
      69,   429,  1688,   410,   411,  1681,   285,   286,   287,    52,
     392,  1376,   442,  1521,   319,   320,  1537,   321,   322,   323,
     324,   325,   326,  1226,  1468,  1469,   327,   328,   329,   780,
     781,   330,   331,   789,   790,  1165,  1159,  1424,  1425,   332,
    1097,  1398,  1636,   333,  1127,  1891,  1809,  1807,   334,   335,
    1428,   792,   336,   337,   338,   339,   340,   846,   847,  1494,
     379,  1832,  1904,   813,   814,   815,   816,   817,   818,   819,
    1448,   820,   821,   822,   823,   824,   825,   341,   342,   852,
     343,   344,   856,   345,   346,   853,   854,   347,   348,   349,
     862,   863,  1208,  1130,   864,   865,  1108,  1109,   350,   351,
     352,   353,   354,   871,   872,   355,   356,   213,   826,   868,
     907,   827,   357,   217,  1000,   502,   503,   828,   510,   358,
     359,   360,   361,   362,   363,   909,   910,   911,   364,   365,
     366,   771,   772,  1383,  1384,  1141,  1142,  1143,  1377,  1378,
    1415,  1410,  1411,  1416,  1144,  1643,   929,  1600,   732,  1611,
     734,  1617,   735,   433,   463,  1875,  1789,  2006,  2007,  1772,
    1782,  1087,  1606,   733,   367,   930,   931,   915,   916,   917,
     918,  1145,   920,   829,   830,   831,   923,   924,   368,   745,
     832,   671,   672,   220,   370,   833,   508,  1349,   701,   834,
    1083,   714,  1353,  1591,   223,   835,   633,   837,   634,   838,
     696,   697,  1074,  1075,   698,   839,   840,   371,   372,   841,
     228,   496,   229,   517,   230,   523,   231,   531,   232,   545,
    1017,  1298,   233,   553,   234,   558,   235,   568,   236,   577,
     237,   583,   238,   586,   239,   590,   240,   595,   241,   600,
     242,   612,  1034,  1308,   243,   616,  1053,  1335,  1318,  1324,
    1313,  1054,   244,   622,   245,   513,   246,   247,   647,   248,
     635,   249,   637,   250,   639,   251,   644,   252,   654,   253,
     657,   254,   663,   255,   710
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   214,    53,   775,   218,   986,   985,   776,   387,   746,
     987,   950,   947,   318,  1146,   992,   949,   777,   269,   216,
     270,    44,   702,   214,   382,   857,   218,   948,  1058,  1404,
    1406,   369,   740,   913,   214,   715,  1417,   218,  1100,   869,
     966,  1549,   369,  1538,  1538,   279,  1560,   264,  1547,  1561,
    1558,  1006,  1559,   374,  1465,   964,   936,   377,   914,   768,
    1361,  1132,  1569,  1399,   268,  1210,  1612,  1061,   972,  1231,
      66,    67,  1645,  1466,  1757,  1755,  1149,  1738,  1756,   946,
     441,   836,   441,  1741,   441,   441,  1181,  1160,   441,  1673,
     441,  1164,   954,   441,   441,   919,  1221,   441,   441,   441,
     441,  1583,  1585,  1222,   441,   932,   932,   441,   441,  1223,
    1147,   769,  1219,  1220,  1467,   441,  1763,     3,  1213,   870,
       4,   769,     5,   968,   866,  1623,  1227,  1282,   934,    55,
    1669,   396,   397,   398,  1674,  2003,  1113,  1081,  2038,  1624,
    1942,   386,     6,     7,     8,     9,  1092,   423,   425,   426,
     151,   152,   153,   980,  1098,  1118,  1825,   438,   673,   282,
     848,  1396,  1651,  1652,  1101,  1633,   449,   450,   989,  1698,
    1699,  1816,   456,   151,   152,   153,   214,  -652,  1095,   218,
     214,  1888,  -662,   218,   624,  -652,  -652,  -652,  -652,  -662,
    -662,  -662,  -662,   487,   488,  1400,  1887,   491,  1374,  1933,
    1880,  1375,   866,  1064,   256,  1773,  1962,   262,   627,  1792,
    1942,    63,  1774,  1076,     3,   866,  1093,     4,  1351,     5,
     878,  1292,   764,  1344,  1345,   997,  1004,  1195,  -662,  1196,
    1065,  1970,     3,   747,    54,     4,   879,     5,  1293,     6,
       7,     8,     9,  1294,  1295,  1966,  -745,  1671,  1634,  1775,
    1538,   934,  1090,   454,   455,  -663,   219,     6,     7,     8,
       9,  1100,  -663,  -663,  -663,  -663,   880,  1388,  1094,   748,
    1412,   717,  1121,  1413,  1712,  1713,    55,   719,   219,  1934,
    1935,   673,   960,  1776,   407,   504,   505,   506,   317,   219,
    1739,   214,  1793,   210,   218,   584,  1431,    71,  1434,   369,
     765,  -663,  -818,  -818,  -818,  -818,  1008,   912,   758,  -818,
    1233,   585,   961,  -745,  1971,   221,   962,   912,   912,  1091,
    1773,  1009,  1737,  1234,   759,   761,   762,  1774,    55,   459,
    2041,   554,    86,     4,  1737,     5,   906,   221,  1233,   387,
     144,  1296,  1549,  1397,  1538,  1538,   906,   906,   221,  1547,
     855,  1485,   555,   943,  1119,  1373,  1088,  1089,    55,  2012,
     998,   999,    55,   214,  1775,   556,   218,   387,   959,  1270,
    1817,   369,   744,   744,  2011,  1096,  1197,  1272,   214,   271,
     387,   218,   210,  1005,  1777,  2008,   369,  1273,  -912,  1624,
    -912,  1114,  1531,   210,  1924,   849,   850,   851,  1776,  1332,
    1932,  1271,  1951,   210,  -913,  1352,  -913,   304,   400,    56,
      57,    58,   102,   963,  1379,  1380,  1333,     3,  1531,  1422,
       4,  1099,     5,   306,  1423,  1217,   867,  1967,   307,  1570,
     441,   219,  1571,   304,  1401,   219,  1198,   283,   284,  1449,
     222,   935,     6,     7,     8,     9,   773,   210,  1334,   306,
     280,  1673,   281,   773,   307,  1148,  1737,   210,  1476,    55,
    1990,   378,   222,   210,  1446,  1477,   383,  1993,  1778,  1250,
     389,  1478,   386,   222,  1474,  1475,   265,  1670,   965,  1675,
    2004,  1799,   878,  2039,   257,   258,   259,   257,   258,   259,
     221,  1337,  2021,  2019,   221,  1902,  2020,   507,   375,  1777,
     386,   430,  1576,  1826,   376,     4,  1194,     5,  1824,   976,
     626,  1894,   557,   386,   460,  -192,   432,  1871,   773,   151,
     152,   153,  1690,  1878,    55,  -652,  1936,  1018,   880,  -662,
    1225,   461,  1815,   210,  -211,   210,  1628,  -912,  1629,  1630,
    1488,  1632,  1288,   317,  1290,   993,   219,   645,   210,     3,
     773,  1019,     4,  -913,     5,  1659,   509,   655,  1660,  1110,
    1012,  1661,  1191,  1829,   272,  1490,   273,   869,   773,  1407,
    1812,  1813,   646,  1228,     6,     7,     8,     9,  1267,  1268,
    1269,  1131,   656,  1868,  1408,   849,   850,   851,     4,  1211,
       5,  1167,  1244,   401,  1280,   402,  1531,  -912,     3,   699,
    1409,     4,  -663,     5,  1168,   221,  1056,  1210,  1192,   700,
    1057,   304,   716,  -913,  1719,   222,  1819,  1245,   219,   222,
    1169,  1261,   739,     6,     7,     8,     9,   306,  1363,  1366,
     630,   631,   307,   219,   490,  1232,  1368,  1773,  1550,  1720,
    1721,  1551,  -818,  1863,  1774,   704,   623,     3,   210,  1644,
       4,   636,     5,   640,  1246,   638,  1240,  1393,   624,  1395,
     625,  1146,   718,   624,  1901,  1693,  1694,  1695,  1696,  1241,
    1100,  1242,     6,     7,     8,     9,  1010,   221,   626,   842,
     843,  1775,   627,   613,  1154,   628,   431,   627,   432,  1420,
    1978,  1011,   221,  1979,  1976,   587,  1977,  1132,   736,   743,
     743,   617,   737,   749,  1224,   588,   589,  1691,   738,  1692,
     632,  1146,  1140,   214,  1873,  1776,   218,  1155,   224,  1874,
     741,  1842,  1843,  1844,  1845,   641,   642,   643,   767,   757,
     222,   399,  1156,   618,   619,   214,   614,   615,   218,  1765,
     224,   906,  1086,  1240,  1189,     3,  1190,   428,     4,  1588,
       5,   224,   766,   773,  1348,  1722,  1252,  1584,  1242,  1552,
    1549,   620,  1538,  1538,  1170,   629,   452,  1547,  1613,   624,
       6,     7,     8,     9,   769,  1723,  1724,  1157,   773,  1766,
    1801,  1360,  1178,  1182,  1522,  1179,  1020,   497,   498,   624,
     791,  1973,  1856,   627,   621,  1847,   869,  1240,   630,   631,
     131,  1021,   222,  1567,  1566,   132,   133,   870,  1568,   626,
    1486,   378,  1242,   627,   278,   280,  1777,   222,     4,   281,
       5,   134,   912,   875,   383,   844,   845,  1354,  1859,   389,
     906,  1852,  1523,  1524,  1525,  1526,     3,  1527,   876,     4,
    1528,     5,   711,   712,   906,   906,   906,   906,   906,   214,
     877,   906,   218,  1839,  1840,  1841,  2001,  1529,  1158,  2002,
     658,     6,     7,     8,     9,  1022,   912,  1911,  1912,  1913,
     925,   591,   783,   926,   659,   592,   906,   937,   632,  1553,
     869,   660,     4,   596,     5,   773,  1847,   938,  1463,   215,
     150,  1426,  2035,   224,   994,   906,  1252,   224,  1242,   661,
    2049,  1427,  1472,  1440,  1441,   662,  1530,   593,   594,  1481,
    1447,   215,   150,  1426,  1767,   597,   598,  1877,   599,   648,
     499,   500,   215,  1430,   501,   511,   512,  1883,  1251,   630,
     631,  1382,  1253,   939,  1886,   649,  1023,  -475,   940,  1024,
    1025,  1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1554,
     150,  1426,     3,   225,   867,     4,   650,     5,   282,  1565,
    1300,  1433,   651,  1471,  1473,  1895,   760,   941,   219,  -745,
    1479,  1473,  1482,  1484,  -272,   225,   973,     6,     7,     8,
       9,   778,   779,   773,   761,   762,   225,  1764,   873,   874,
     219,  1289,  1550,  1291,  1301,  1551,   996,     3,  1768,  1297,
       4,  -754,     5,   784,   785,   786,   787,   788,   224,   632,
       4,  1531,     5,  -755,  1852,  1309,  1947,  1948,  1949,  1310,
    1311,  1312,     6,     7,     8,     9,   304,   221,   291,   292,
    1125,  1126,  1110,   293,  1382,     3,   860,   861,     4,   979,
       5,  1003,   306,   652,   653,  1968,   995,   307,  1001,   221,
    1302,  1303,  1304,  1305,  1306,  1307,  1013,  1014,  1015,  1016,
       6,     7,     8,     9,   215,  1062,  1626,   518,   215,   519,
     520,   521,   522,  1146,     3,  1550,  1063,     4,  1551,     5,
     224,   773,  1728,  1729,  1730,   214,  1731,  1078,   218,  1765,
    1319,  1320,  1321,  1322,  1323,   224,  1532,  1648,  1079,     6,
       7,     8,     9,  1080,   219,   720,  1084,   721,  1082,   722,
     723,  1184,  1185,  1552,   136,  1106,   137,   724,   725,     3,
    1111,   138,     4,   139,     5,  1235,  1236,   140,   225,  1766,
    1112,  1211,   225,  1115,  1450,  1794,   761,   762,  1795,   761,
     762,  1667,  1116,  1668,     6,     7,     8,     9,  1797,  1672,
     726,  1117,   222,  1676,  1677,  1182,  1182,  1182,  1182,  1182,
    1120,  1182,  1182,   221,  1340,  1341,   141,  1811,   142,   578,
    1456,  1456,   773,  1122,  1133,  1150,   151,   152,   153,   215,
     493,   494,   495,   867,  1129,   579,   214,  1607,   214,   218,
       4,   218,     5,  1854,   580,  1138,  1552,  2060,  2061,  2062,
     581,   582,  1342,  1343,   906,   906,   906,   906,   906,   906,
     906,   906,   906,   906,   906,  1473,  1473,  1131,   769,  1405,
       3,   150,  1426,     4,   908,     5,  1151,  1926,   214,  1715,
    1716,   218,  1152,  1553,   908,   908,   369,  1802,  1803,  1804,
    1805,  1806,  1749,   225,  1719,     6,     7,     8,     9,  1589,
    1590,   215,  1161,  1489,  1491,  1507,  1515,  1533,  1545,  1162,
    1550,  1987,  1988,  1551,  1767,  1163,   215,   867,  1214,  1720,
    1721,   447,  1216,  1174,   226,  1492,  1508,  1516,  1534,  1546,
    1574,   546,  1180,   547,  1186,  1791,    18,    19,   222,  1100,
    2026,  1314,  1315,  1316,  1317,  1187,   226,  1188,   227,  1193,
    1838,  1836,   548,  1754,  1837,  1458,  1459,   226,  -957,  -958,
     549,   550,   551,   552,  1199,   225,  1553,   514,   515,   516,
     373,  1200,  1579,  1580,  1201,  1581,  1582,   257,   258,   259,
     225,   373,  1202,   773,  1204,    34,   434,   435,   436,   437,
     219,  1205,  1893,  1213,  1851,    35,  1215,  1237,  1867,  1238,
    1243,    36,  1249,   746,   214,   705,  1233,   218,  1597,  1140,
     774,  1603,   369,  1608,   706,   707,  1614,  1835,   708,   709,
    1858,   214,   906,  1239,   218,    37,   906,  1254,   934,  1598,
    1656,  1552,  1604,  1262,  1609,  1722,  1758,  1615,   906,  1263,
     214,  1264,  1093,   218,  1066,  1067,  1265,  1266,   369,   221,
    1090,  1274,  1090,  1657,  1326,  1723,  1724,  1275,  1068,  1279,
     773,   465,   859,   860,   861,  1276,  1069,  1277,  1655,   151,
     152,   153,  1278,  1927,  1965,  2025,    18,    19,  1281,  1284,
     224,  1327,  1070,   849,   850,   851,  1328,   214,   906,  1928,
     218,   219,  1382,   219,  1929,   369,  1930,  1287,  1329,   226,
    1330,  1348,  1134,   226,  1331,   773,   906,   906,  1338,  1339,
    1996,  1995,  1346,  1347,  1350,  1997,  1355,  1358,  1356,  1365,
    1596,  1370,   878,   227,  1357,    34,  1381,   227,  1389,  1391,
    1394,  1402,  1889,   219,  1432,    35,  1110,  1421,  1436,  1445,
    1439,    36,  1453,   214,   524,   525,   218,  1454,  1242,  1455,
     221,  1553,   221,   526,   527,   528,   529,   530,  1697,  1470,
     214,  1711,  1487,   218,  1572,    37,  1705,  1706,  1707,  1708,
    1709,  1562,  1563,  1564,   222,  1575,  1586,  1577,  1711,   214,
    1595,  1578,   218,  1601,  1734,  1735,  1736,   369,  1620,    62,
    1621,  1625,   221,  1640,  1635,  2042,  1743,  1744,  1745,  1647,
    1646,  1071,  1072,  1073,   682,  1649,  1507,  1515,  1533,  1545,
    1658,  1663,  1665,  1678,   226,  1240,   224,   692,   693,   694,
    1679,  2018,  1689,  1703,  2059,  1704,  1718,  1508,  1516,  1534,
    1546,  1714,   753,  1740,  2065,  2064,  1702,  1746,   373,  2066,
    1748,  1769,  1779,  1786,  1800,  1759,   214,  1747,   391,   218,
    1760,   215,   395,  1762,    18,    19,  1790,  1810,  1808,   219,
    1818,  1827,  1770,  1780,  1787,  1828,  1994,   418,   391,  1823,
    1831,  1833,    88,   215,  1846,   222,   219,   222,  1861,   908,
      89,  1870,    90,  1884,    91,   445,   226,    92,    93,    94,
     214,    95,  1110,   218,  1879,   219,   467,  1872,  1881,  1892,
    1890,   226,  1896,    34,  1897,  1820,   387,  1898,  2010,  1903,
     373,    18,    19,    35,   486,   225,  1918,   222,   221,    36,
    1900,   492,  1906,  1907,  1908,   373,   294,   295,   296,  1641,
    1642,   299,   387,  1909,   922,   221,  1910,   225,  1914,  1915,
    1950,  1964,   219,    37,   922,   922,  1963,  1916,  1917,  1952,
    1960,  1969,  1992,  1972,   221,  1980,  1981,   469,  -225,  1848,
      34,  1849,  1850,  2000,  2009,  1982,   744,   744,  1209,  2005,
      35,  2028,    18,    19,  2033,  1853,    36,  2034,  2037,  -226,
    2056,  1855,   908,   908,   908,   908,   908,   215,  1857,   908,
    2063,  1860,  1876,  1007,  1573,    70,   945,  1866,   219,  1557,
      37,   221,  1882,  1742,  1769,  1779,  1786,  1921,  2036,  1885,
    2055,  1920,  1983,  1985,   908,   219,  1984,  1986,  1975,  2029,
     214,    34,   413,   218,  1166,  1770,  1780,  1787,   369,  1686,
     942,    35,   471,   908,   219,  1153,   420,    36,  1830,   386,
     476,  1821,   763,   222,  1796,  1203,   214,    18,    19,   218,
     906,   225,   224,  1974,   944,    18,    19,   221,  2013,  1443,
    1133,    37,  1442,  1444,     3,   386,  1461,     4,   214,     5,
    1212,   218,  1865,  1464,   221,  1135,  1638,   214,  1637,   222,
     218,   742,  1905,  1218,  1483,  1285,  1919,   703,  1418,     6,
       7,     8,     9,   221,   480,  1925,    34,  1627,  1650,  1653,
     955,   219,    96,   482,    34,   933,    35,   957,   462,    18,
      19,  1941,    36,  1946,    35,   958,  2057,    97,    18,    19,
      36,   956,   751,  1299,  1953,  1954,   222,  1955,  1956,  1957,
    1958,  1959,  1059,    98,  1961,   755,    37,   756,    99,  1325,
     100,     0,     0,   214,    37,   219,   218,     0,  1682,  1684,
    1684,  1687,     0,   224,     0,   224,     0,     0,    34,     0,
     221,  1711,     0,     0,     0,  -475,     3,    34,    35,     4,
       0,     5,  1991,     0,    36,     0,     0,    35,     0,     0,
    1998,  1999,   222,    36,     3,     0,  1940,     4,  1945,     5,
       0,     6,     7,     8,     9,   224,     0,   214,    37,   222,
     218,     0,     0,     0,   221,   369,     0,    37,     0,     6,
       7,     8,     9,   214,     0,     0,   218,     0,   222,     0,
       0,     0,     0,   215,  1491,  1515,  1533,  1545,     0,     0,
       0,  2031,  1597,  1603,  1608,  1614,   226,     0,     0,  2030,
       0,     0,  2032,     0,     0,  1492,  1516,  1534,  1546,     0,
       0,     0,     0,  1598,  1604,  1609,  1615,  2040,   226,     0,
     227,     0,     0,  2043,  2044,  2045,  2046,  2047,  1769,  1779,
    1786,  2051,  2052,  2053,  2054,   219,  1429,  1429,     3,  1429,
       0,     4,   227,     5,     0,   222,     0,   225,  2058,  1770,
    1780,  1787,     0,   743,   743,     0,  1783,     0,     0,     0,
       0,   219,     0,     6,     7,     8,     9,     0,     0,  2067,
    2068,  2069,  2027,     0,     0,     0,     0,     0,     0,     0,
       0,   224,     0,   219,   215,     0,   215,     0,  1945,   222,
       0,     0,   219,     0,   221,     0,     0,     0,  1134,   922,
       0,     0,   908,   908,   908,   908,   908,   908,   908,   908,
     908,   908,   908,  1865,     0,     0,     0,   224,     0,     0,
     221,   559,   560,     0,   761,   762,   215,     0,     0,     0,
    1765,     0,   226,     0,     0,     0,   561,     0,   562,   563,
     564,  1183,   221,     0,     0,     0,     0,     0,   225,     0,
     225,   221,     3,     0,     0,     4,   227,     5,   219,     0,
     773,   565,   566,   567,   224,     0,     0,     0,     0,     0,
    1766,     3,   921,     0,     4,  2024,     5,     6,     7,     8,
       9,     0,   921,   921,     0,     0,     0,     0,   922,     0,
     225,     0,     0,   569,  1414,   570,     6,     7,     8,     9,
       0,     0,   922,   922,   922,   922,   922,     0,     0,   922,
       0,  1784,   219,     0,   571,     0,     0,   221,     0,   222,
     224,     0,   572,   573,  1093,   574,     0,     0,   219,     0,
       0,     0,     0,     0,   922,   575,   576,   224,     0,     0,
    1021,     0,     0,     0,     0,   222,     0,     0,     0,     0,
       0,     0,   215,   922,     0,     0,   224,     0,     0,     0,
       0,     0,   773,     0,  1783,     0,     0,   222,     0,   215,
    1209,   221,     0,     0,   908,     0,   222,  1602,     0,     0,
     773,     0,     0,  1783,     0,     0,   908,   221,   215,     0,
       0,     0,     0,     0,     0,  1785,  1429,     0,     0,  1429,
       0,     0,  1429,     0,  1022,  1767,  1493,  1510,  1520,  1536,
    1548,     0,     3,     0,     0,     4,   225,     5,     0,     3,
       0,     0,     4,   224,     5,     0,     0,     0,     0,     0,
       0,     0,    60,   225,     0,   215,   908,     6,     7,     8,
       9,     0,   222,     0,     6,     7,     8,     9,     0,   934,
       0,     0,   225,     0,   908,   908,     0,     0,  1539,     0,
       0,   274,   275,   276,   277,     0,     0,   224,   226,     0,
       0,     0,     0,     0,   773,  1023,     0,     0,  1024,  1025,
    1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,     0,  2048,
       0,   215,   227,     0,     0,   393,   222,     0,     0,   225,
       0,     0,     0,   403,   404,   405,   406,  1540,   215,  1541,
    1599,  1527,   222,  1605,  1528,  1610,     0,     0,  1616,  1784,
       0,     0,     0,     0,     0,     0,   439,   215,     0,     0,
       0,  1542,     3,     0,     0,     4,     0,     5,  1784,     0,
       0,     0,     0,   464,     0,     0,     0,     0,   473,   474,
     475,     0,     0,   479,     0,   225,   484,     6,     7,     8,
       9,     0,     0,     0,     0,     0,  1414,     0,     0,   226,
       0,   226,   225,     0,     3,     0,     0,     4,     0,     5,
    1543,     0,     0,     0,     0,     0,     0,     0,   773,     0,
       0,   225,     0,   227,   215,   227,     0,   224,     0,     6,
       7,     8,     9,  1869,     0,     0,     0,   773,     0,     0,
       0,   226,     0,  1183,  1183,  1183,  1183,  1183,     0,  1183,
    1183,     0,  2050,   224,    10,     0,     0,     0,  1457,  1457,
       0,     0,    11,     0,    12,   373,    13,     0,   215,    14,
      15,    16,     0,    17,     0,   224,     0,    18,    19,     0,
     601,     0,     0,     0,   224,     0,     0,     0,   225,   602,
       0,     0,   922,   922,   922,   922,   922,   922,   922,   922,
     922,   922,   922,     0,   603,     0,     0,   921,   604,     0,
       0,     0,   605,   606,     0,  1531,     0,   607,   608,   609,
     610,   611,     0,   728,   729,   730,    34,     0,     0,     0,
     304,     0,   225,     0,     0,     0,    35,     0,  1510,  1520,
    1536,  1548,    36,     0,    73,     0,   306,     0,     0,     0,
     224,   307,    74,     0,    75,     0,     0,     0,     0,    76,
      77,    78,  1105,    79,  1107,     0,    37,   226,     0,     0,
       0,     0,     0,  1771,  1781,  1788,     0,     0,   773,     0,
    1123,  1124,     0,  1128,   226,   773,     0,     0,     0,  1136,
    1137,   373,     0,  2014,     0,     0,   921,     0,   215,     0,
    1544,     0,     0,   226,   224,     0,     0,     0,   227,     0,
     921,   921,   921,   921,   921,     0,  1171,   921,  1173,     0,
     224,     0,     0,     0,   215,     0,     0,   373,   908,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   921,     0,     0,  1090,   215,     0,     0,     0,
     226,     0,   951,   952,   953,   215,     0,     0,     0,     0,
     922,   921,   225,     0,   922,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   373,     0,   922,     0,  1207,     0,
       0,     0,     0,     0,    38,   967,     0,     0,   225,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   773,    39,
       0,     0,  1093,     0,     0,     0,   226,     0,     0,     0,
     225,     0,     0,  2022,   978,    40,     0,     0,     0,   225,
      41,   215,    42,   226,     0,     0,   922,     0,     0,     0,
     227,     0,     0,     0,     0,     0,  1771,  1781,  1788,     0,
     773,     0,   226,     0,   922,   922,     0,   227,  1247,  1248,
       0,     0,     0,     0,     3,  2023,     0,     4,     0,     5,
       0,     0,     0,     0,     0,     0,   373,     0,     0,     0,
       0,     0,     0,     0,    80,   215,     0,     0,     0,     6,
       7,     8,     9,     0,     0,   225,     0,     0,     0,    81,
       0,   215,     0,  1522,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,   226,
      83,    50,    84,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    50,    50,    64,    64,    64,    68,     0,     0,
      50,     0,     0,   227,     0,     0,     0,     0,     0,   225,
       0,  1523,  1524,  1525,  1526,     0,  1527,     0,     0,  1528,
       0,     0,     0,   226,     0,   225,     0,   444,     0,   446,
     448,     0,     0,   451,     0,   453,  1529,     0,   457,   458,
       0,     0,   466,   468,   470,   472,     0,   227,     0,   477,
       0,    50,   481,   483,   394,    50,    64,    64,    64,    68,
     489,     0,     0,     0,     0,     0,    50,     0,   409,   414,
     417,    50,   422,    64,    64,   427,     0,   409,   409,   409,
     409,     0,    64,     0,     0,  1530,   443,     0,    50,     0,
       0,    64,    64,     0,    68,  1369,     0,    64,     0,  1372,
       0,     0,     0,     0,     0,     0,     0,     0,  1385,  1386,
    1387,     0,     0,  1390,     0,  1392,   485,    50,    64,    64,
       0,     0,    64,     0,    50,     0,  1493,  1520,  1536,  1548,
       0,  1403,     0,     0,  1599,  1605,  1610,  1616,     0,     0,
     921,   921,   921,   921,   921,   921,   921,   921,   921,   921,
     921,     0,     0,   226,     0,     3,     0,     0,     4,     0,
       5,     0,     0,     0,     0,  1435,     0,  1437,     0,     0,
    1771,  1781,  1788,  1438,     0,     0,     0,   373,   794,   226,
       6,     7,     8,     9,     0,     0,  1451,     0,  1452,     0,
    1531,     0,     0,     0,  1522,     0,     0,  1460,     0,  1462,
       0,   226,     0,   227,     0,   304,     0,     0,     0,     0,
     226,   151,   152,   153,     0,     0,     0,     0,   888,     0,
       0,   306,   889,     0,     0,   227,   307,   890,     0,     0,
       0,     0,     0,   891,   227,     0,     3,   801,     0,     4,
       0,     5,  1523,  1524,  1525,  1526,     0,  1527,     0,     0,
    1528,     0,     0,     0,     0,     0,     0,   894,   922,     0,
     773,     6,     7,     8,     9,     0,     0,  1529,     0,     0,
       0,     0,  1495,     0,     0,  1752,   226,     0,     0,     0,
       0,     0,  1496,     0,     0,     0,     0,  1497,     0,  1498,
       0,  1499,     0,     0,     0,     0,     0,     0,     0,     0,
     227,     0,     0,     0,     0,     0,     0,     0,   921,     0,
       0,     0,   921,     0,     0,     0,  1530,   532,   533,     0,
       0,   534,     0,     0,   921,     0,     0,     0,     0,     0,
     226,     0,   535,   536,   537,   538,   539,   540,   541,   542,
     543,     0,     0,     0,     0,     0,   226,     0,     0,     0,
       0,     0,     0,     0,   373,     0,     0,     0,     0,     0,
       0,     0,     0,  1618,  1619,     0,     0,     0,     0,     0,
     227,     0,     0,     0,   921,   977,     0,     0,     0,     0,
       0,   544,  1035,     0,  1631,   804,     0,     0,   805,   806,
       0,     0,   921,   921,     0,  1639,     0,  1500,  1036,  1037,
    1038,  1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,
    1048,  1049,  1050,  1051,  1052,     0,     0,     0,     0,     0,
       0,  1531,     0,   808,   809,     0,     0,   975,     0,  1662,
       0,     0,     0,     0,    64,     0,   304,     0,     0,     0,
       0,     0,     0,     0,     0,   981,  1664,   982,  1666,   983,
       3,   984,   306,     4,     0,     5,   988,   307,     0,     0,
     990,     0,   991,     0,   210,     0,     0,     0,     0,     0,
      64,     0,   146,     0,     0,     6,     7,     8,     9,   147,
     148,     0,     0,     0,   288,   149,   289,     0,     0,     0,
       0,   773,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   290,  1501,     0,     0,     0,  2016,     0,     0,     0,
       0,   291,   292,     0,     0,     0,   293,  1502,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   294,   295,   296,
     297,   298,   299,  1503,     0,     0,     0,     0,  1504,     0,
    1505,     0,  1511,     0,     0,     0,   300,     0,   301,     0,
       0,   150,   151,   152,   153,     0,     0,   154,     0,   155,
       0,     0,  1512,   156,     0,     0,     0,     0,   157,     0,
       0,     0,   773,     0,   158,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1506,     0,     0,
     159,     0,     0,     0,     0,   160,     0,     0,   161,     0,
       0,     0,     0,   162,     0,     0,   163,     0,     0,   164,
     165,  1513,     0,  1798,   166,     0,     0,   167,     3,   168,
       0,     4,     0,     5,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1814,     0,     0,     0,     0,     0,     0,
       0,   169,   170,     6,     7,     8,     9,     0,     0,     0,
       0,     0,     0,     0,  1495,     0,  1822,     0,     0,     0,
       0,     0,     0,     0,  1496,     0,     0,     0,     0,  1497,
       0,  1498,     0,  1499,     0,     0,     0,   171,   172,   173,
     174,     0,     0,     0,     0,     0,   175,   176,     0,     0,
     177,   178,   302,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,     0,     0,   303,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   304,     0,     0,     0,     0,   921,     0,     0,     0,
       0,   305,     0,     0,     0,     0,     0,   306,     0,     0,
       0,     0,   307,     0,     0,     0,     0,     0,   202,   203,
       0,   308,     0,     0,   309,   310,   311,   312,     0,     0,
       0,   313,     0,     0,     0,   314,   315,   204,     0,  1500,
       0,   205,   206,     0,     3,     0,   773,     4,     0,     5,
     316,     0,     0,   207,   208,     0,     0,     0,     0,     0,
     317,  1514,   209,     0,     0,   210,   146,     0,     0,     6,
       7,     8,     9,   147,   148,     0,  1899,     0,   288,   149,
     289,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   290,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   291,   292,     0,     0,     0,
     293,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   294,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1511,     0,     0,     0,
     300,     0,   301,     0,  1501,   150,   151,   152,   153,     0,
       0,   154,     0,   155,     0,     0,  1512,   156,     0,  1502,
       0,     0,   157,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,     0,     0,  1503,     0,     0,     0,     0,
    1504,     0,  1505,     0,   159,     0,     0,     0,     0,   160,
       0,     0,   161,     0,     0,     0,     0,   162,     0,     0,
     163,     0,     0,   164,   165,  1513,     0,     0,   166,     0,
       0,   167,     0,   168,   773,     0,     0,     0,     0,  1283,
       0,     0,     0,     0,     0,     0,     0,     0,     3,  1750,
       0,     4,     0,     5,     0,   169,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     7,     8,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1539,     0,     0,
       0,   171,   172,   173,   174,     0,     0,     0,     0,     0,
     175,   176,     0,     0,   177,   178,   302,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,     0,
     303,     0,     0,     0,     0,     0,  1540,     0,  1541,     0,
    1527,     0,     0,  1528,     0,   304,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   305,     0,     0,     0,     0,
    1542,   306,     0,     0,     0,     0,   307,     0,     0,     0,
       0,     0,   202,   203,     0,   308,     0,     0,   309,   310,
     311,   312,     0,     0,     0,   313,     0,     0,     0,   314,
     315,   204,     0,     0,     0,   205,   206,     0,     3,     0,
     773,     4,     0,     5,   316,     0,     0,   207,   208,  1543,
       0,     0,     0,     0,   317,  1751,   209,     0,     0,   210,
     146,     0,     0,     6,     7,     8,     9,   147,   148,     0,
       0,     0,   288,   149,   289,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   290,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   291,
     292,     0,     0,     0,   293,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   294,   295,   296,   297,   298,
     299,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1511,     0,     0,     0,   300,     0,   301,     0,     0,   150,
     151,   152,   153,     0,     0,   154,     0,   155,     0,     0,
    1512,   156,     0,     0,  1531,     0,   157,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,     0,     0,   304,
       0,     0,     0,     0,     0,     0,     0,     0,   159,     0,
       0,     0,     0,   160,     0,   306,   161,     0,     0,     0,
     307,   162,     0,     0,   163,     0,     0,   164,   165,  1513,
       0,     0,   166,     0,     0,   167,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     3,     0,     0,     4,     0,
       5,     0,     0,     0,   773,     0,     0,     0,     0,   169,
     170,     0,     0,     0,     0,     0,     0,     0,     0,  1753,
       6,     7,     8,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1539,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   171,   172,   173,   174,     0,
       0,     0,     0,     0,   175,   176,     0,     0,   177,   178,
     302,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,     0,  1540,   303,  1541,     0,  1527,     0,     0,
    1528,     0,     0,     0,     0,     0,     0,     0,     0,   304,
       0,     0,     0,     0,     0,     0,     0,  1542,     0,   305,
       0,     0,     0,     0,     0,   306,     0,     0,     0,     0,
     307,     0,     0,     0,     0,     0,   202,   203,     0,   308,
       0,     0,   309,   310,   311,   312,     0,     0,     0,   313,
       0,     0,     0,   314,   315,   204,     0,     0,     0,   205,
     206,     0,     0,     4,   773,     5,  1543,     0,   316,     0,
       0,   207,   208,     0,     0,     0,     0,     0,   317,  2015,
     209,     0,   146,   210,     0,     0,     0,     0,     0,   147,
     148,     0,     0,     0,   288,   149,   289,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   290,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   291,   292,   664,     0,     0,   293,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   294,   295,   296,
     297,   298,   299,     0,     0,     0,     0,     0,     0,     0,
     665,     0,     0,   666,     0,     0,   300,     0,   301,     0,
       0,   150,   151,   152,   153,     0,     0,   154,     0,   155,
     667,  1531,     0,   156,     0,     0,     0,     0,   157,     0,
       0,     0,     0,     0,   158,     0,   304,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     159,     0,   306,     0,     0,   160,     0,   307,   161,     0,
       0,     0,     0,   162,     0,     0,   163,     0,     0,   164,
     165,     0,     0,     0,   166,     0,     0,   167,     0,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   773,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   169,   170,     0,     0,     0,  2017,     0,     0,     0,
       0,     0,     0,     0,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,     0,     0,   171,   172,   173,
     174,     0,     0,     0,     0,     0,   175,   176,     0,     0,
     177,   178,   302,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,     0,   668,   303,     0,   793,   202,
     203,     0,     0,     0,     0,     0,     0,     0,     0,   669,
       0,   304,     0,     0,     0,     0,   146,     0,     0,     0,
       0,   305,     0,     0,   148,     0,     0,   306,     0,   149,
       0,     0,   307,     0,     0,   670,     0,     0,   202,   203,
       0,   308,     0,     0,   309,   310,   311,   312,     0,     0,
       0,   313,     0,     0,     0,   314,   315,   204,     0,     0,
       0,   205,   206,   794,     0,     0,     0,     0,     0,     0,
     316,     0,     0,   207,   208,     0,     0,   795,     0,   796,
     317,  1654,   209,     0,     0,   210,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,   151,   152,   153,     0,
       0,   154,     0,   797,     0,     0,     0,   798,     0,     0,
       0,     0,   799,     0,     0,     0,     0,     0,   800,     0,
       0,     0,   801,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,     0,     0,     0,     0,   160,
       0,     0,   802,     0,     0,     0,     0,   162,     0,     0,
     163,     0,     0,   164,   165,     0,     0,     0,   166,     0,
       0,   167,     0,   168,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   752,   169,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1102,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   674,   675,     0,     0,
     676,     0,     0,     0,   146,     0,     0,     0,     0,     0,
       0,   803,   148,     0,     0,     0,     0,   149,   677,     0,
       0,     0,     0,     0,     0,     0,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,     0,
     201,   794,     0,     0,     0,     0,     0,     0,     0,     0,
     804,     0,     0,   805,   806,     0,     0,     0,     0,     0,
       0,     0,   753,     0,     0,     0,   807,     0,     0,     0,
       0,     0,     0,   150,   151,   152,   153,     0,     0,   154,
       0,   797,   202,   203,     0,   798,     0,     0,   808,   809,
     799,     0,     0,     0,     0,     0,  1103,     0,     0,     0,
     801,   204,     0,     0,     0,   205,   206,     0,     0,     0,
       0,     0,   159,     0,     0,   810,   811,   160,   670,   678,
    1104,     0,     0,     0,     0,   162,   812,     0,   163,   210,
       0,   164,   165,     0,     0,     0,   166,     0,     0,   167,
       0,   168,     0,   679,   680,   681,   682,   683,   684,   754,
     685,   686,   687,   688,   689,   690,   691,     0,     0,   692,
     693,   694,     0,   169,   170,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1172,     0,     0,     0,     0,     0,
     695,     0,     0,     0,   674,   675,     0,     0,   676,     0,
       0,     0,   146,     0,     0,     0,     0,     0,     0,   803,
     148,     0,     0,     0,     0,   149,   677,     0,     0,     0,
       0,     0,     0,     0,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     0,     0,   201,   794,
       0,     0,     0,     0,     0,     0,     0,     0,   804,     0,
       0,   805,   806,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   150,   151,   152,   153,     0,     0,   154,     0,   797,
     202,   203,     0,   798,     0,     0,   808,   809,   799,     0,
       0,     0,     0,     0,  1103,     0,     0,     0,   801,   204,
       0,     0,     0,   205,   206,     0,     0,     0,     0,     0,
     159,     0,     0,   810,   811,   160,   670,   678,  1104,     0,
       0,     0,     0,   162,   812,     0,   163,   210,     0,   164,
     165,     0,     0,     0,   166,     0,     0,   167,     0,   168,
       0,   679,   680,   681,   682,   683,   684,     0,   685,   686,
     687,   688,   689,   690,   691,     0,     0,   692,   693,   694,
       0,   169,   170,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1206,     0,     0,     0,     0,     0,   695,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,     0,     0,     0,     0,     0,     0,   803,   148,     0,
       0,     0,     0,   149,     0,     0,     0,     0,     0,     0,
       0,     0,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,     0,     0,   201,   794,     0,     0,
       0,     0,     0,     0,     0,     0,   804,     0,     0,   805,
     806,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
     151,   152,   153,     0,     0,   154,     0,   797,   202,   203,
       0,   798,     0,     0,   808,   809,   799,     0,     0,     0,
       0,     0,  1103,     0,     0,     0,   801,   204,     0,     0,
       0,   205,   206,     0,     0,     0,     0,     0,   159,     0,
       0,   810,   811,   160,   670,     0,  1104,     0,     0,     0,
       0,   162,   812,     0,   163,   210,     0,   164,   165,     0,
       0,     0,   166,     0,     0,   167,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   169,
     170,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1371,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   146,     0,
       0,     0,     0,     0,     0,   803,   148,     0,     0,     0,
       0,   149,     0,     0,     0,     0,     0,     0,     0,     0,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,     0,     0,   201,   794,     0,     0,     0,     0,
       0,     0,     0,     0,   804,     0,     0,   805,   806,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   150,   151,   152,
     153,     0,     0,   154,     0,   797,   202,   203,     0,   798,
       0,     0,   808,   809,   799,     0,     0,     0,     0,     0,
    1103,     0,     0,     0,   801,   204,     0,     0,     0,   205,
     206,     0,     0,     0,     0,     0,   159,     0,     0,   810,
     811,   160,   670,     0,  1104,     0,     0,     0,     0,   162,
     812,     0,   163,   210,     0,   164,   165,     0,     0,     0,
     166,     0,     0,   167,     0,   168,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   169,   170,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   881,   882,   883,   884,   885,   886,     0,     0,
       0,     0,   887,     0,     0,     0,   866,     0,     0,     0,
       0,     0,     0,   803,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
       0,     0,   201,   794,     0,     0,     0,     0,     0,     0,
       0,     0,   804,     0,     0,   805,   806,     0,     0,     0,
       0,     0,     0,  1139,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,   151,   152,   153,     0,
       0,     0,     0,   888,   202,   203,     0,   889,     0,     0,
     808,   809,   890,     0,     0,     0,     0,     0,   891,     0,
       0,     0,   801,   204,     0,     0,     0,   205,   206,     0,
       0,     0,   794,     0,   892,     0,     0,   810,   811,   893,
     670,     0,   894,     0,     0,     0,     0,   895,   812,     0,
     896,   210,  1139,   897,   898,     0,     0,     0,   899,     0,
       0,   900,     0,   901,   150,   151,   152,   153,     0,     0,
       0,     0,   888,     0,     0,     0,   889,     0,     0,     0,
       0,   890,     0,     0,     0,   902,   903,   891,     0,     0,
       0,   801,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   794,     0,   892,     0,     0,     0,     0,   893,     0,
       0,   894,     0,     0,     0,     0,   895,     0,     0,   896,
       0,     0,   897,   898,     0,     0,     0,   899,     0,     0,
     900,     0,   901,   150,   151,   152,   153,     0,     0,     0,
       0,   888,     0,     0,     0,   889,     0,     0,     0,     0,
     890,     0,     0,     0,   902,   903,   891,     0,     0,     0,
     801,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     804,     0,   892,   805,   806,     0,     0,   893,     0,     0,
     894,     0,   927,   866,     0,   895,     0,     0,   896,     0,
       0,   897,   898,     0,     0,     0,   899,     0,     0,   900,
       0,   901,     0,     0,     0,     0,     0,     0,   808,   809,
       0,   904,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   902,   903,     0,     0,     0,     0,     0,
     794,     0,     0,     0,     0,   810,   811,     0,     0,   804,
       0,     0,   805,   806,   317,     0,   905,     0,     0,   210,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,   151,   152,   153,     0,     0,     0,     0,
     888,     0,     0,     0,   889,     0,     0,   808,   809,   890,
     904,     0,     0,     0,     0,   891,     0,     0,     0,   801,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   892,     0,     0,   810,   811,   893,     0,   804,   894,
       0,   805,   806,   317,   895,   905,     0,   896,   210,     0,
     897,   898,     0,     0,     0,   899,     0,     0,   900,     0,
     901,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   808,   809,     0,   904,
       0,   146,   902,   903,     0,     0,     0,     0,   147,   148,
       0,     0,     0,   288,   149,   289,     0,     0,     0,     0,
       0,     0,     0,   810,   811,     0,     0,     0,     0,     0,
     290,     0,     0,     0,   905,     0,     0,   210,     0,     0,
     291,   292,   750,     0,     0,   293,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,   665,
       0,     0,   666,     0,     0,   300,     0,   301,     0,     0,
     150,   151,   152,   153,     0,     0,   154,   804,   155,   667,
     805,   806,   156,     0,     0,     0,     0,   157,     0,     0,
       0,     0,     0,   158,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   159,
       0,     0,     0,     0,   160,   808,   809,   161,   904,     0,
       0,     0,   162,     0,     0,   163,     0,     0,   164,   165,
       0,     0,     0,   166,     0,     0,   167,     0,   168,     0,
       0,     0,   810,   811,     0,     0,     0,     0,     0,     0,
       0,   928,     0,   905,     0,     0,   210,     0,     0,     0,
     169,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,     0,     0,   171,   172,   173,   174,
       0,     0,     0,     0,     0,   175,   176,     0,     0,   177,
     178,   302,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,     0,   668,   303,     0,     0,   202,   203,
       0,     0,     0,     0,     0,     0,   146,     0,   669,     0,
     304,     0,     0,   147,   148,     0,     0,     0,     0,   149,
     305,     0,     0,     0,     0,     0,   306,     0,     0,     0,
       0,   307,     0,     0,   670,     0,     0,   202,   203,     0,
     308,     0,     0,   309,   310,   311,   312,     0,     0,     0,
     313,     0,     0,     0,   314,   315,   204,     0,     0,     0,
     205,   206,     0,     0,     0,     0,     0,     0,     0,   316,
       0,     0,   207,   208,     0,     0,     0,     0,     0,   317,
       0,   209,     0,     0,   210,   150,   151,   152,   153,     0,
       0,   154,     0,   155,     0,     0,     0,   156,     0,     0,
       0,     0,   157,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,     0,     0,     0,     0,   160,
       0,     0,   161,     0,     0,     0,     0,   162,     0,     0,
     163,     0,     0,   164,   165,     0,     0,     0,   166,     0,
       0,   167,     0,   168,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   169,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   146,     0,     0,     0,     0,
       0,     0,   147,   148,     0,     0,     0,     0,   149,     0,
       0,   171,   172,   173,   174,     0,     0,     0,     0,     0,
     175,   176,     0,     0,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,     0,
     201,     0,     0,     0,     0,     0,     0,     0,  1922,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150,   151,   152,   153,     0,     0,
     154,     0,   155,     0,     0,     0,   156,     0,     0,     0,
       0,   157,   202,   203,     0,     0,     0,   158,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   204,     0,   159,     0,   205,   206,     0,   160,     0,
       0,   161,     0,     0,     0,     0,   162,   207,   208,   163,
       0,     0,   164,   165,   317,     0,   209,   166,     0,   210,
     167,     0,   168,     0,     0,     0,     0,     0,     0,     0,
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
     104,     0,   156,     0,     0,   105,     0,   157,   106,   107,
     108,   109,     0,   158,   110,   111,     0,   112,   113,   114,
       0,   115,     0,     0,     0,     0,     0,     0,     0,   159,
       0,   202,   203,     0,   160,     0,     0,   161,     0,     0,
       0,     0,   162,     0,     0,   163,     0,     0,   164,   165,
     204,     0,     0,   166,   205,   206,   167,     0,   168,     0,
     116,     0,   117,   118,   119,     0,   207,   208,     0,     0,
       0,     0,     0,     0,     0,   209,     0,   146,   210,     0,
     169,   170,     0,     0,     0,   148,     0,     0,     0,     0,
     149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   171,   172,   173,   174,
       0,     0,     0,     0,   794,   175,   176,     0,     0,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,     0,     0,   201,   150,   151,   152,   153,
       0,     0,   154,     0,   797,     0,     0,     0,   798,     0,
       0,     0,     0,   799,     0,     0,     0,     0,     0,  1103,
       0,     0,     0,   801,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   159,     0,   202,   203,     0,
     160,     0,     0,  1104,     0,     0,     0,     0,   162,     0,
       0,   163,     0,     0,   164,   165,   204,     0,     0,   166,
     205,   206,   167,     0,   168,     0,     0,     0,     0,     0,
     120,     0,   207,   208,     0,     0,     0,     0,     0,     0,
       0,   209,     0,     0,   210,   121,   169,   170,     0,     0,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,   126,     0,     0,     0,     0,   127,     0,   128,   129,
       0,     0,     0,     0,     0,   866,     0,     0,     0,     0,
       0,     0,   803,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,     0,
       0,   201,   794,     0,     0,     0,     0,     0,     0,     0,
       0,   804,     0,     0,   805,   806,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150,   151,   152,   153,     0,     0,
       0,     0,   888,   202,   203,     0,   889,     0,     0,   808,
     809,   890,     0,     0,     0,     0,     0,   891,     0,     0,
       0,   801,   204,     0,     0,     0,   205,   206,     0,     0,
       0,     0,     0,   892,     0,     0,   810,   811,   893,   670,
       0,   894,     0,     0,     0,     0,   895,   812,     0,   896,
     210,     0,   897,   898,     0,     0,     0,   899,     0,     0,
     900,     0,   901,     0,     0,     2,     3,     0,     0,     4,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   902,   903,     0,     0,     0,     0,
       0,     6,     7,     8,     9,     0,     0,     0,     0,     0,
       0,     0,    10,     0,     0,     0,     0,     0,     0,     0,
      11,     0,    12,     0,    13,     0,     0,    14,    15,    16,
       0,    17,     0,     0,     0,    18,    19,    20,     0,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -363,   804,
       0,     0,   805,   806,    34,     0,     0,     0,     0,     0,
       0,     0,     0,   794,    35,     0,     0,     0,     0,     0,
      36,   294,   295,   296,  1641,  1642,   299,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   808,   809,     0,
     904,     0,     0,     0,    37,   150,   151,   152,   153,     0,
       0,     0,     0,   888,     0,     0,     0,   889,     0,     0,
       0,   794,   890,     0,   810,   811,     0,     0,   891,     0,
       0,     0,   801,   317,     0,   905,     0,     0,   210,     0,
       0,     0,     0,     0,   892,     0,     0,     0,     0,   893,
       0,     0,   894,   150,   151,   152,   153,   895,     0,     0,
     896,   888,     0,   897,   898,   889,     0,     0,   899,     0,
     890,   900,     0,   901,     0,     0,   891,     0,     0,     0,
     801,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   794,   892,     0,     0,   902,   903,   893,     0,     0,
     894,     0,     0,     0,     0,   895,     0,     0,   896,     0,
       0,   897,   898,     0,     0,     0,   899,     0,     0,   900,
       0,   901,    38,  1480,   151,   152,   153,     0,     0,     0,
       0,   888,     0,     0,     0,   889,     0,    39,     0,     0,
     890,     0,     0,   902,   903,     0,   891,     0,     0,     0,
     801,     0,     0,    40,     0,     0,     0,     0,    41,     0,
      42,     0,   892,     0,     0,     0,     0,   893,     0,     0,
     894,     0,     0,     0,     0,   895,     0,     0,   896,     0,
     804,   897,   898,   805,   806,     0,   899,     0,     0,   900,
       0,   901,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   902,   903,     0,     0,     0,   808,   809,
       0,   904,     0,     0,     0,     0,     0,     0,   804,     0,
       0,   805,   806,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   810,   811,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   905,     0,     0,   210,
       0,     0,     0,     0,     0,     0,   808,   809,     0,   904,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   810,   811,     0,     0,     0,   804,     0,
       0,   805,   806,     0,   905,     0,     0,   210,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   808,   809,     0,   904,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   810,   811,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   905,     0,     0,   210
};

static const yytype_int16 yycheck[] =
{
       1,    30,     3,   320,    30,   474,   473,   323,    66,   298,
     475,   399,   396,    52,   770,   484,   398,   328,    36,    30,
      37,     1,   205,    52,    63,   344,    52,   397,   632,  1140,
    1141,    52,   288,   365,    63,   209,  1147,    63,   735,   351,
     428,  1259,    63,  1258,  1259,    46,  1265,    32,  1259,  1266,
    1263,   517,  1264,    54,  1215,   425,   379,    58,   365,   315,
    1093,   764,  1279,  1130,    35,   859,  1365,   635,   438,   903,
      15,    16,  1405,  1217,  1564,  1562,   773,  1539,  1563,   395,
     105,   337,   107,  1542,   109,   110,   812,   784,   113,  1467,
     115,   788,   403,   118,   119,   365,   875,   122,   123,   124,
     125,  1346,  1347,   876,   129,   375,   376,   132,   133,   877,
       7,     4,   873,   874,  1225,   140,  1585,     1,     7,    45,
       4,     4,     6,   434,    23,  1375,   879,   978,    38,   103,
       5,    76,    77,    78,     7,     7,    96,   705,     7,  1377,
     103,    66,    26,    27,    28,    29,   732,    92,    93,    94,
     103,   104,   105,   464,   734,   102,     5,   102,   179,    57,
      84,   103,  1412,  1413,   735,    20,   111,   112,   479,    78,
      79,   102,   117,   103,   104,   105,   205,     7,   733,   205,
     209,  1793,     8,   209,   125,    15,    16,    17,    18,    15,
      16,    17,    18,   138,   139,    84,  1792,   142,    89,    22,
    1775,    92,    23,   668,    58,    89,  1887,    58,   149,    20,
     103,    13,    96,   696,     1,    23,   299,     4,   159,     6,
       8,   113,    84,  1074,  1075,   113,   126,    84,    54,    86,
     695,    20,     1,    62,   104,     4,    24,     6,   130,    26,
      27,    28,    29,   135,   136,   103,   284,  1465,   103,   133,
    1465,    38,   284,    45,    46,     8,    30,    26,    27,    28,
      29,   958,    15,    16,    17,    18,    54,  1118,   351,    98,
      89,   256,   755,    92,  1524,  1525,   103,   262,    52,   102,
     103,   302,    57,   167,    86,    32,    33,    34,   351,    63,
    1540,   320,   103,   356,   320,   143,  1168,    49,  1170,   320,
     162,    54,    15,    16,    17,    18,   110,   365,   283,    22,
       7,   159,    57,   351,   103,    30,    57,   375,   376,   351,
      89,   125,  1537,    20,   299,   301,   302,    96,   103,    89,
    2011,   113,    49,     4,  1549,     6,   365,    52,     7,   397,
      47,   233,  1560,   285,  1559,  1560,   375,   376,    63,  1560,
      84,    20,   134,   392,   301,  1108,   729,   730,   103,  1971,
     248,   249,   103,   392,   133,   147,   392,   425,   407,   955,
     301,   392,   297,   298,  1970,   351,   233,   957,   407,    89,
     438,   407,   356,   283,   268,  1960,   407,   958,    84,  1627,
      86,   351,   267,   356,  1856,   319,   320,   321,   167,   113,
    1859,   956,  1871,   356,    84,   346,    86,   282,    89,     7,
       8,     9,    53,    57,  1111,  1112,   130,     1,   267,   143,
       4,   351,     6,   298,   148,   351,   351,   285,   303,  1280,
     455,   205,  1283,   282,   323,   209,   293,   335,   336,  1192,
      30,   351,    26,    27,    28,    29,   337,   356,   162,   298,
      48,  1829,    50,   337,   303,   352,  1671,   356,  1237,   103,
    1922,    59,    52,   356,  1190,  1238,    64,  1926,   352,   352,
      68,  1239,   397,    63,  1235,  1236,   103,   352,    57,   352,
     352,  1625,     8,   352,   338,   339,   340,   338,   339,   340,
     205,  1059,  1982,  1980,   209,  1828,  1981,   244,   350,   268,
     425,    89,  1336,   352,   350,     4,   825,     6,  1669,   454,
     145,  1810,   294,   438,   274,   351,   276,  1762,   337,   103,
     104,   105,    89,  1773,   103,   355,   349,   545,    54,   355,
     351,   291,  1643,   356,   351,   356,  1387,   233,  1389,  1390,
      39,  1392,  1008,   351,  1010,   490,   320,   127,   356,     1,
     337,   568,     4,   233,     6,  1427,   132,   127,  1430,   742,
     531,  1433,     8,  1674,   274,   352,   276,   879,   337,   267,
    1637,  1638,   152,   880,    26,    27,    28,    29,   951,   952,
     953,   764,   152,   352,   282,   319,   320,   321,     4,   859,
       6,   141,   924,   274,   967,   276,   267,   293,     1,   319,
     298,     4,   355,     6,   154,   320,   624,  1401,    54,   329,
     627,   282,   210,   293,   103,   205,  1649,   924,   392,   209,
     170,   944,    84,    26,    27,    28,    29,   298,  1095,  1098,
     265,   266,   303,   407,    45,   905,  1101,    89,    41,   128,
     129,    44,   355,   351,    96,   330,   113,     1,   356,  1405,
       4,   233,     6,   162,   924,   233,     7,  1124,   125,  1128,
     127,  1417,   339,   125,  1825,  1502,  1503,  1504,  1505,    20,
    1367,    22,    26,    27,    28,    29,   110,   392,   145,    38,
      39,   133,   149,   113,    77,   152,   274,   149,   276,  1155,
    1909,   125,   407,  1910,  1907,   152,  1908,  1400,   102,   297,
     298,   134,   102,   301,   878,   162,   163,   274,   102,   276,
     345,  1467,   770,   742,   165,   167,   742,   110,    30,   170,
     283,  1693,  1694,  1695,  1696,   234,   235,   236,    84,   283,
     320,    79,   125,   166,   167,   764,   166,   167,   764,    93,
      52,   770,   727,     7,    20,     1,    22,    95,     4,  1353,
       6,    63,    84,   337,   331,   244,    20,   334,    22,   162,
    1978,   194,  1977,  1978,   314,   232,   114,  1978,   352,   125,
      26,    27,    28,    29,     4,   264,   265,   170,   337,   133,
    1631,  1092,   800,   812,    40,   802,    23,   111,   112,   125,
     313,  1902,     5,   149,   227,     8,  1108,     7,   265,   266,
     282,    38,   392,  1272,  1271,   287,   288,    45,  1273,   145,
      20,   409,    22,   149,     0,   413,   268,   407,     4,   417,
       6,   303,   880,    17,   422,   184,   185,  1083,     5,   427,
     859,     8,    88,    89,    90,    91,     1,    93,    18,     4,
      96,     6,   348,   349,   873,   874,   875,   876,   877,   878,
     355,   880,   878,  1690,  1691,  1692,    22,   113,   251,    25,
     113,    26,    27,    28,    29,   102,   924,  1839,  1840,  1841,
      52,   130,   162,    52,   127,   134,   905,   351,   345,   282,
    1192,   134,     4,   134,     6,   337,     8,   351,  1207,    30,
     102,   103,  2003,   205,   492,   924,    20,   209,    22,   152,
     352,   113,  1234,  1184,  1185,   158,   162,   166,   167,  1241,
    1191,    52,   102,   103,   268,   166,   167,  1768,   169,   115,
     244,   245,    63,   113,   248,   166,   167,  1778,   929,   265,
     266,  1114,   933,   351,  1785,   131,   173,   102,   351,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   352,
     102,   103,     1,    30,   879,     4,   152,     6,    57,  1270,
      96,   113,   158,  1233,  1234,  1816,   283,   351,   742,   284,
    1240,  1241,  1242,  1243,   351,    52,    43,    26,    27,    28,
      29,   284,   285,   337,   301,   302,    63,  1591,    15,    16,
     764,  1009,    41,  1011,   130,    44,     8,     1,   352,  1017,
       4,    45,     6,   293,   294,   295,   296,   297,   320,   345,
       4,   267,     6,    45,     8,   217,  1867,  1868,  1869,   221,
     222,   223,    26,    27,    28,    29,   282,   742,    62,    63,
     301,   302,  1215,    67,  1217,     1,   324,   325,     4,    45,
       6,   103,   298,   239,   240,  1896,     7,   303,   297,   764,
     186,   187,   188,   189,   190,   191,   137,   138,   139,   140,
      26,    27,    28,    29,   205,   357,  1383,   113,   209,   115,
     116,   117,   118,  1829,     1,    41,   357,     4,    44,     6,
     392,   337,    85,    86,    87,  1114,    89,   330,  1114,    93,
     216,   217,   218,   219,   220,   407,   352,  1408,   330,    26,
      27,    28,    29,   102,   878,    46,   354,    48,   347,    50,
      51,    15,    16,   162,    45,    84,    47,    58,    59,     1,
      23,    52,     4,    54,     6,    15,    16,    58,   205,   133,
      23,  1401,   209,    52,  1192,  1602,   301,   302,  1607,   301,
     302,  1460,    52,  1462,    26,    27,    28,    29,  1613,  1466,
      91,    52,   742,  1485,  1486,  1184,  1185,  1186,  1187,  1188,
      52,  1190,  1191,   878,   111,   112,    97,  1636,    99,   127,
    1199,  1200,   337,    52,   764,   351,   103,   104,   105,   320,
     106,   107,   108,  1108,   102,   143,  1215,   352,  1217,  1215,
       4,  1217,     6,     7,   152,    84,   162,  2048,  2049,  2050,
     158,   159,   111,   112,  1233,  1234,  1235,  1236,  1237,  1238,
    1239,  1240,  1241,  1242,  1243,  1485,  1486,  1400,     4,     5,
       1,   102,   103,     4,   365,     6,   102,    86,  1257,    94,
      95,  1257,   102,   282,   375,   376,  1257,   307,   308,   309,
     310,   311,  1553,   320,   103,    26,    27,    28,    29,   111,
     112,   392,   102,  1254,  1255,  1256,  1257,  1258,  1259,   102,
      41,    43,    44,    44,   268,   102,   407,  1192,   866,   128,
     129,    45,   870,    84,    30,  1255,  1256,  1257,  1258,  1259,
    1298,   113,    84,   115,    17,  1596,    60,    61,   878,  1986,
    1987,   212,   213,   214,   215,    18,    52,   355,    30,     5,
    1688,  1685,   134,   352,  1686,  1199,  1200,    63,     7,     7,
     142,   143,   144,   145,     7,   392,   282,   111,   112,   113,
      52,     7,  1340,  1341,   102,  1342,  1343,   338,   339,   340,
     407,    63,   102,   337,     5,   109,    97,    98,    99,   100,
    1114,     7,  1809,     7,  1714,   119,   351,    17,   352,    18,
       8,   125,   102,  1642,  1383,   228,     7,  1383,  1359,  1417,
     319,  1362,  1383,  1364,   237,   238,  1367,  1683,   241,   242,
    1740,  1400,  1401,   355,  1400,   149,  1405,   102,    38,  1359,
    1419,   162,  1362,   351,  1364,   244,   352,  1367,  1417,   351,
    1419,   351,   299,  1419,   111,   112,   351,   351,  1419,  1114,
     284,   102,   284,  1421,   221,   264,   265,   102,   125,   351,
     337,    45,   323,   324,   325,   102,   133,   102,  1419,   103,
     104,   105,   102,   282,  1891,   352,    60,    61,   103,   102,
     742,   224,   149,   319,   320,   321,   224,  1466,  1467,   298,
    1466,  1215,  1625,  1217,   303,  1466,   305,   102,   225,   205,
     226,   331,   764,   209,   225,   337,  1485,  1486,   102,   102,
    1929,  1928,   102,   102,   102,  1930,   351,   102,   351,   102,
     352,     5,     8,   205,   351,   109,   102,   209,   102,    52,
     102,    43,  1799,  1257,    70,   119,  1669,   148,     5,   102,
     354,   125,    84,  1522,   111,   112,  1522,     8,    22,    84,
    1215,   282,  1217,   120,   121,   122,   123,   124,  1509,   354,
    1539,  1522,   102,  1539,     7,   149,  1517,  1518,  1519,  1520,
    1521,   351,   351,   351,  1114,     7,   102,   358,  1539,  1558,
     285,   358,  1558,   102,  1535,  1536,  1537,  1558,     5,    12,
     103,   351,  1257,    43,   304,  2012,  1547,  1548,  1549,   284,
     187,   268,   269,   270,   271,   299,  1557,  1558,  1559,  1560,
       7,     5,   164,   102,   320,     7,   878,   284,   285,   286,
      39,   352,   103,   103,  2041,    98,   102,  1557,  1558,  1559,
    1560,   350,   187,   350,  2053,  2052,  1511,   103,   320,  2054,
      98,  1592,  1593,  1594,   352,   102,  1625,   350,    71,  1625,
     102,   742,    75,   102,    60,    61,   102,   102,   300,  1383,
     102,   352,  1592,  1593,  1594,     5,  1927,    90,    91,    84,
     185,   102,    37,   764,    41,  1215,  1400,  1217,   150,   770,
      45,     7,    47,   104,    49,   108,   392,    52,    53,    54,
    1669,    56,  1825,  1669,   102,  1419,    45,   350,   102,   102,
     300,   407,   102,   109,   285,  1656,  1714,   102,  1969,   184,
     392,    60,    61,   119,   137,   742,   103,  1257,  1383,   125,
     352,   144,   351,   351,   351,   407,    78,    79,    80,    81,
      82,    83,  1740,   351,   365,  1400,   351,   764,   351,   351,
     102,   102,  1466,   149,   375,   376,   352,   351,   351,   351,
     133,   102,     8,   352,  1419,   351,   351,    45,     8,  1710,
     109,  1712,  1713,   102,   284,   351,  1641,  1642,   859,   103,
     119,   350,    60,    61,   102,  1726,   125,   102,     5,     8,
     102,  1732,   873,   874,   875,   876,   877,   878,  1739,   880,
    2051,  1742,  1767,   523,  1287,    20,   394,  1748,  1522,  1262,
     149,  1466,  1777,  1543,  1755,  1756,  1757,  1854,  2003,  1784,
    2028,  1852,  1914,  1916,   905,  1539,  1915,  1917,  1906,  1989,
    1799,   109,    89,  1799,   789,  1755,  1756,  1757,  1799,  1498,
     391,   119,    45,   924,  1558,   780,    91,   125,  1674,  1714,
      45,  1658,   307,  1383,  1612,   846,  1825,    60,    61,  1825,
    1829,   878,  1114,  1905,   393,    60,    61,  1522,  1974,  1187,
    1400,   149,  1186,  1188,     1,  1740,  1205,     4,  1847,     6,
     862,  1847,  1747,  1213,  1539,   765,  1401,  1856,  1400,  1419,
    1856,   290,  1833,   871,  1243,   996,  1847,   205,  1147,    26,
      27,    28,    29,  1558,    45,  1856,   109,  1384,  1410,  1415,
     403,  1625,   267,    45,   109,   376,   119,   405,   120,    60,
      61,  1862,   125,  1864,   119,   406,  2038,   282,    60,    61,
     125,   404,   302,  1020,  1875,  1876,  1466,  1878,  1879,  1880,
    1881,  1882,   633,   298,  1885,   303,   149,   303,   303,  1038,
     305,    -1,    -1,  1922,   149,  1669,  1922,    -1,  1496,  1497,
    1498,  1499,    -1,  1215,    -1,  1217,    -1,    -1,   109,    -1,
    1625,  1922,    -1,    -1,    -1,   102,     1,   109,   119,     4,
      -1,     6,  1923,    -1,   125,    -1,    -1,   119,    -1,    -1,
    1931,  1932,  1522,   125,     1,    -1,  1861,     4,  1863,     6,
      -1,    26,    27,    28,    29,  1257,    -1,  1976,   149,  1539,
    1976,    -1,    -1,    -1,  1669,  1976,    -1,   149,    -1,    26,
      27,    28,    29,  1992,    -1,    -1,  1992,    -1,  1558,    -1,
      -1,    -1,    -1,  1114,  1975,  1976,  1977,  1978,    -1,    -1,
      -1,  1992,  1983,  1984,  1985,  1986,   742,    -1,    -1,  1990,
      -1,    -1,  1993,    -1,    -1,  1975,  1976,  1977,  1978,    -1,
      -1,    -1,    -1,  1983,  1984,  1985,  1986,  2008,   764,    -1,
     742,    -1,    -1,  2014,  2015,  2016,  2017,  2018,  2019,  2020,
    2021,  2022,  2023,  2024,  2025,  1799,  1167,  1168,     1,  1170,
      -1,     4,   764,     6,    -1,  1625,    -1,  1114,  2039,  2019,
    2020,  2021,    -1,  1641,  1642,    -1,   113,    -1,    -1,    -1,
      -1,  1825,    -1,    26,    27,    28,    29,    -1,    -1,  2060,
    2061,  2062,  1987,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1383,    -1,  1847,  1215,    -1,  1217,    -1,  2003,  1669,
      -1,    -1,  1856,    -1,  1799,    -1,    -1,    -1,  1400,   770,
      -1,    -1,  1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,
    1241,  1242,  1243,  2028,    -1,    -1,    -1,  1419,    -1,    -1,
    1825,   111,   112,    -1,   301,   302,  1257,    -1,    -1,    -1,
      93,    -1,   878,    -1,    -1,    -1,   126,    -1,   128,   129,
     130,   812,  1847,    -1,    -1,    -1,    -1,    -1,  1215,    -1,
    1217,  1856,     1,    -1,    -1,     4,   878,     6,  1922,    -1,
     337,   151,   152,   153,  1466,    -1,    -1,    -1,    -1,    -1,
     133,     1,   365,    -1,     4,   352,     6,    26,    27,    28,
      29,    -1,   375,   376,    -1,    -1,    -1,    -1,   859,    -1,
    1257,    -1,    -1,   113,  1143,   115,    26,    27,    28,    29,
      -1,    -1,   873,   874,   875,   876,   877,    -1,    -1,   880,
      -1,   268,  1976,    -1,   134,    -1,    -1,  1922,    -1,  1799,
    1522,    -1,   142,   143,   299,   145,    -1,    -1,  1992,    -1,
      -1,    -1,    -1,    -1,   905,   155,   156,  1539,    -1,    -1,
      38,    -1,    -1,    -1,    -1,  1825,    -1,    -1,    -1,    -1,
      -1,    -1,  1383,   924,    -1,    -1,  1558,    -1,    -1,    -1,
      -1,    -1,   337,    -1,   113,    -1,    -1,  1847,    -1,  1400,
    1401,  1976,    -1,    -1,  1405,    -1,  1856,   352,    -1,    -1,
     337,    -1,    -1,   113,    -1,    -1,  1417,  1992,  1419,    -1,
      -1,    -1,    -1,    -1,    -1,   352,  1427,    -1,    -1,  1430,
      -1,    -1,  1433,    -1,   102,   268,  1255,  1256,  1257,  1258,
    1259,    -1,     1,    -1,    -1,     4,  1383,     6,    -1,     1,
      -1,    -1,     4,  1625,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    10,  1400,    -1,  1466,  1467,    26,    27,    28,
      29,    -1,  1922,    -1,    26,    27,    28,    29,    -1,    38,
      -1,    -1,  1419,    -1,  1485,  1486,    -1,    -1,    40,    -1,
      -1,    39,    40,    41,    42,    -1,    -1,  1669,  1114,    -1,
      -1,    -1,    -1,    -1,   337,   173,    -1,    -1,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,    -1,   352,
      -1,  1522,  1114,    -1,    -1,    73,  1976,    -1,    -1,  1466,
      -1,    -1,    -1,    81,    82,    83,    84,    89,  1539,    91,
    1359,    93,  1992,  1362,    96,  1364,    -1,    -1,  1367,   268,
      -1,    -1,    -1,    -1,    -1,    -1,   104,  1558,    -1,    -1,
      -1,   113,     1,    -1,    -1,     4,    -1,     6,   268,    -1,
      -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,   126,   127,
     128,    -1,    -1,   131,    -1,  1522,   134,    26,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,  1415,    -1,    -1,  1215,
      -1,  1217,  1539,    -1,     1,    -1,    -1,     4,    -1,     6,
     162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,    -1,
      -1,  1558,    -1,  1215,  1625,  1217,    -1,  1799,    -1,    26,
      27,    28,    29,   352,    -1,    -1,    -1,   337,    -1,    -1,
      -1,  1257,    -1,  1184,  1185,  1186,  1187,  1188,    -1,  1190,
    1191,    -1,   352,  1825,    37,    -1,    -1,    -1,  1199,  1200,
      -1,    -1,    45,    -1,    47,  1257,    49,    -1,  1669,    52,
      53,    54,    -1,    56,    -1,  1847,    -1,    60,    61,    -1,
     134,    -1,    -1,    -1,  1856,    -1,    -1,    -1,  1625,   143,
      -1,    -1,  1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,
    1241,  1242,  1243,    -1,   158,    -1,    -1,   770,   162,    -1,
      -1,    -1,   166,   167,    -1,   267,    -1,   171,   172,   173,
     174,   175,    -1,   271,   272,   273,   109,    -1,    -1,    -1,
     282,    -1,  1669,    -1,    -1,    -1,   119,    -1,  1557,  1558,
    1559,  1560,   125,    -1,    37,    -1,   298,    -1,    -1,    -1,
    1922,   303,    45,    -1,    47,    -1,    -1,    -1,    -1,    52,
      53,    54,   739,    56,   741,    -1,   149,  1383,    -1,    -1,
      -1,    -1,    -1,  1592,  1593,  1594,    -1,    -1,   337,    -1,
     757,   758,    -1,   760,  1400,   337,    -1,    -1,    -1,   766,
     767,  1383,    -1,   352,    -1,    -1,   859,    -1,  1799,    -1,
     352,    -1,    -1,  1419,  1976,    -1,    -1,    -1,  1400,    -1,
     873,   874,   875,   876,   877,    -1,   793,   880,   795,    -1,
    1992,    -1,    -1,    -1,  1825,    -1,    -1,  1419,  1829,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   905,    -1,    -1,   284,  1847,    -1,    -1,    -1,
    1466,    -1,   400,   401,   402,  1856,    -1,    -1,    -1,    -1,
    1401,   924,  1799,    -1,  1405,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1466,    -1,  1417,    -1,   855,    -1,
      -1,    -1,    -1,    -1,   267,   433,    -1,    -1,  1825,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   282,
      -1,    -1,   299,    -1,    -1,    -1,  1522,    -1,    -1,    -1,
    1847,    -1,    -1,   352,   462,   298,    -1,    -1,    -1,  1856,
     303,  1922,   305,  1539,    -1,    -1,  1467,    -1,    -1,    -1,
    1522,    -1,    -1,    -1,    -1,    -1,  1755,  1756,  1757,    -1,
     337,    -1,  1558,    -1,  1485,  1486,    -1,  1539,   925,   926,
      -1,    -1,    -1,    -1,     1,   352,    -1,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,  1558,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   267,  1976,    -1,    -1,    -1,    26,
      27,    28,    29,    -1,    -1,  1922,    -1,    -1,    -1,   282,
      -1,  1992,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   298,    -1,    -1,    -1,  1625,
     303,     1,   305,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      20,    -1,    -1,  1625,    -1,    -1,    -1,    -1,    -1,  1976,
      -1,    88,    89,    90,    91,    -1,    93,    -1,    -1,    96,
      -1,    -1,    -1,  1669,    -1,  1992,    -1,   107,    -1,   109,
     110,    -1,    -1,   113,    -1,   115,   113,    -1,   118,   119,
      -1,    -1,   122,   123,   124,   125,    -1,  1669,    -1,   129,
      -1,    71,   132,   133,    74,    75,    76,    77,    78,    79,
     140,    -1,    -1,    -1,    -1,    -1,    86,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    -1,    97,    98,    99,
     100,    -1,   102,    -1,    -1,   162,   106,    -1,   108,    -1,
      -1,   111,   112,    -1,   114,  1102,    -1,   117,    -1,  1106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1115,  1116,
    1117,    -1,    -1,  1120,    -1,  1122,   136,   137,   138,   139,
      -1,    -1,   142,    -1,   144,    -1,  1975,  1976,  1977,  1978,
      -1,  1138,    -1,    -1,  1983,  1984,  1985,  1986,    -1,    -1,
    1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,  1241,  1242,
    1243,    -1,    -1,  1799,    -1,     1,    -1,    -1,     4,    -1,
       6,    -1,    -1,    -1,    -1,  1172,    -1,  1174,    -1,    -1,
    2019,  2020,  2021,  1180,    -1,    -1,    -1,  1799,    70,  1825,
      26,    27,    28,    29,    -1,    -1,  1193,    -1,  1195,    -1,
     267,    -1,    -1,    -1,    40,    -1,    -1,  1204,    -1,  1206,
      -1,  1847,    -1,  1825,    -1,   282,    -1,    -1,    -1,    -1,
    1856,   103,   104,   105,    -1,    -1,    -1,    -1,   110,    -1,
      -1,   298,   114,    -1,    -1,  1847,   303,   119,    -1,    -1,
      -1,    -1,    -1,   125,  1856,    -1,     1,   129,    -1,     4,
      -1,     6,    88,    89,    90,    91,    -1,    93,    -1,    -1,
      96,    -1,    -1,    -1,    -1,    -1,    -1,   149,  1829,    -1,
     337,    26,    27,    28,    29,    -1,    -1,   113,    -1,    -1,
      -1,    -1,    37,    -1,    -1,   352,  1922,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    52,    -1,    54,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1922,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1401,    -1,
      -1,    -1,  1405,    -1,    -1,    -1,   162,   111,   112,    -1,
      -1,   115,    -1,    -1,  1417,    -1,    -1,    -1,    -1,    -1,
    1976,    -1,   126,   127,   128,   129,   130,   131,   132,   133,
     134,    -1,    -1,    -1,    -1,    -1,  1992,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1976,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1370,  1371,    -1,    -1,    -1,    -1,    -1,
    1992,    -1,    -1,    -1,  1467,   455,    -1,    -1,    -1,    -1,
      -1,   175,   179,    -1,  1391,   277,    -1,    -1,   280,   281,
      -1,    -1,  1485,  1486,    -1,  1402,    -1,   162,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,    -1,    -1,    -1,    -1,    -1,
      -1,   267,    -1,   315,   316,    -1,    -1,   447,    -1,  1436,
      -1,    -1,    -1,    -1,   454,    -1,   282,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   465,  1453,   467,  1455,   469,
       1,   471,   298,     4,    -1,     6,   476,   303,    -1,    -1,
     480,    -1,   482,    -1,   356,    -1,    -1,    -1,    -1,    -1,
     490,    -1,    23,    -1,    -1,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,
      -1,   337,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,   267,    -1,    -1,    -1,   352,    -1,    -1,    -1,
      -1,    62,    63,    -1,    -1,    -1,    67,   282,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      81,    82,    83,   298,    -1,    -1,    -1,    -1,   303,    -1,
     305,    -1,    93,    -1,    -1,    -1,    97,    -1,    99,    -1,
      -1,   102,   103,   104,   105,    -1,    -1,   108,    -1,   110,
      -1,    -1,   113,   114,    -1,    -1,    -1,    -1,   119,    -1,
      -1,    -1,   337,    -1,   125,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   352,    -1,    -1,
     141,    -1,    -1,    -1,    -1,   146,    -1,    -1,   149,    -1,
      -1,    -1,    -1,   154,    -1,    -1,   157,    -1,    -1,   160,
     161,   162,    -1,  1620,   165,    -1,    -1,   168,     1,   170,
      -1,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1640,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   192,   193,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,  1663,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    52,
      -1,    54,    -1,    56,    -1,    -1,    -1,   228,   229,   230,
     231,    -1,    -1,    -1,    -1,    -1,   237,   238,    -1,    -1,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,    -1,    -1,   267,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   282,    -1,    -1,    -1,    -1,  1829,    -1,    -1,    -1,
      -1,   292,    -1,    -1,    -1,    -1,    -1,   298,    -1,    -1,
      -1,    -1,   303,    -1,    -1,    -1,    -1,    -1,   309,   310,
      -1,   312,    -1,    -1,   315,   316,   317,   318,    -1,    -1,
      -1,   322,    -1,    -1,    -1,   326,   327,   328,    -1,   162,
      -1,   332,   333,    -1,     1,    -1,   337,     4,    -1,     6,
     341,    -1,    -1,   344,   345,    -1,    -1,    -1,    -1,    -1,
     351,   352,   353,    -1,    -1,   356,    23,    -1,    -1,    26,
      27,    28,    29,    30,    31,    -1,  1823,    -1,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,
      97,    -1,    99,    -1,   267,   102,   103,   104,   105,    -1,
      -1,   108,    -1,   110,    -1,    -1,   113,   114,    -1,   282,
      -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,    -1,    -1,    -1,    -1,   298,    -1,    -1,    -1,    -1,
     303,    -1,   305,    -1,   141,    -1,    -1,    -1,    -1,   146,
      -1,    -1,   149,    -1,    -1,    -1,    -1,   154,    -1,    -1,
     157,    -1,    -1,   160,   161,   162,    -1,    -1,   165,    -1,
      -1,   168,    -1,   170,   337,    -1,    -1,    -1,    -1,   979,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,   352,
      -1,     4,    -1,     6,    -1,   192,   193,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,   228,   229,   230,   231,    -1,    -1,    -1,    -1,    -1,
     237,   238,    -1,    -1,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,    -1,
     267,    -1,    -1,    -1,    -1,    -1,    89,    -1,    91,    -1,
      93,    -1,    -1,    96,    -1,   282,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   292,    -1,    -1,    -1,    -1,
     113,   298,    -1,    -1,    -1,    -1,   303,    -1,    -1,    -1,
      -1,    -1,   309,   310,    -1,   312,    -1,    -1,   315,   316,
     317,   318,    -1,    -1,    -1,   322,    -1,    -1,    -1,   326,
     327,   328,    -1,    -1,    -1,   332,   333,    -1,     1,    -1,
     337,     4,    -1,     6,   341,    -1,    -1,   344,   345,   162,
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
     113,   114,    -1,    -1,   267,    -1,   119,    -1,    -1,    -1,
      -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,   282,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,
      -1,    -1,    -1,   146,    -1,   298,   149,    -1,    -1,    -1,
     303,   154,    -1,    -1,   157,    -1,    -1,   160,   161,   162,
      -1,    -1,   165,    -1,    -1,   168,    -1,   170,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,     4,    -1,
       6,    -1,    -1,    -1,   337,    -1,    -1,    -1,    -1,   192,
     193,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   352,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   228,   229,   230,   231,    -1,
      -1,    -1,    -1,    -1,   237,   238,    -1,    -1,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,    -1,    89,   267,    91,    -1,    93,    -1,    -1,
      96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   282,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,   292,
      -1,    -1,    -1,    -1,    -1,   298,    -1,    -1,    -1,    -1,
     303,    -1,    -1,    -1,    -1,    -1,   309,   310,    -1,   312,
      -1,    -1,   315,   316,   317,   318,    -1,    -1,    -1,   322,
      -1,    -1,    -1,   326,   327,   328,    -1,    -1,    -1,   332,
     333,    -1,    -1,     4,   337,     6,   162,    -1,   341,    -1,
      -1,   344,   345,    -1,    -1,    -1,    -1,    -1,   351,   352,
     353,    -1,    23,   356,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,   103,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     130,    -1,    -1,   133,    -1,    -1,    97,    -1,    99,    -1,
      -1,   102,   103,   104,   105,    -1,    -1,   108,    -1,   110,
     150,   267,    -1,   114,    -1,    -1,    -1,    -1,   119,    -1,
      -1,    -1,    -1,    -1,   125,    -1,   282,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     141,    -1,   298,    -1,    -1,   146,    -1,   303,   149,    -1,
      -1,    -1,    -1,   154,    -1,    -1,   157,    -1,    -1,   160,
     161,    -1,    -1,    -1,   165,    -1,    -1,   168,    -1,   170,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   337,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   192,   193,    -1,    -1,    -1,   352,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,    -1,   228,   229,   230,
     231,    -1,    -1,    -1,    -1,    -1,   237,   238,    -1,    -1,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,    -1,   305,   267,    -1,     5,   309,
     310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   319,
      -1,   282,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,   292,    -1,    -1,    31,    -1,    -1,   298,    -1,    36,
      -1,    -1,   303,    -1,    -1,   345,    -1,    -1,   309,   310,
      -1,   312,    -1,    -1,   315,   316,   317,   318,    -1,    -1,
      -1,   322,    -1,    -1,    -1,   326,   327,   328,    -1,    -1,
      -1,   332,   333,    70,    -1,    -1,    -1,    -1,    -1,    -1,
     341,    -1,    -1,   344,   345,    -1,    -1,    84,    -1,    86,
     351,   352,   353,    -1,    -1,   356,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,    -1,
      -1,   108,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,
      -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,    -1,   129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,
      -1,    -1,   149,    -1,    -1,    -1,    -1,   154,    -1,    -1,
     157,    -1,    -1,   160,   161,    -1,    -1,    -1,   165,    -1,
      -1,   168,    -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,   192,   193,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   111,   112,    -1,    -1,
     115,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,   228,    31,    -1,    -1,    -1,    -1,    36,   133,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,    -1,
     267,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     277,    -1,    -1,   280,   281,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   187,    -1,    -1,    -1,   293,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,    -1,    -1,   108,
      -1,   110,   309,   310,    -1,   114,    -1,    -1,   315,   316,
     119,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,
     129,   328,    -1,    -1,    -1,   332,   333,    -1,    -1,    -1,
      -1,    -1,   141,    -1,    -1,   342,   343,   146,   345,   244,
     149,    -1,    -1,    -1,    -1,   154,   353,    -1,   157,   356,
      -1,   160,   161,    -1,    -1,    -1,   165,    -1,    -1,   168,
      -1,   170,    -1,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    -1,    -1,   284,
     285,   286,    -1,   192,   193,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,
     305,    -1,    -1,    -1,   111,   112,    -1,    -1,   115,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,   228,
      31,    -1,    -1,    -1,    -1,    36,   133,    -1,    -1,    -1,
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
     141,    -1,    -1,   342,   343,   146,   345,   244,   149,    -1,
      -1,    -1,    -1,   154,   353,    -1,   157,   356,    -1,   160,
     161,    -1,    -1,    -1,   165,    -1,    -1,   168,    -1,   170,
      -1,   268,   269,   270,   271,   272,   273,    -1,   275,   276,
     277,   278,   279,   280,   281,    -1,    -1,   284,   285,   286,
      -1,   192,   193,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,   305,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,   228,    31,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,    -1,    -1,   267,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   277,    -1,    -1,   280,
     281,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,    -1,    -1,   108,    -1,   110,   309,   310,
      -1,   114,    -1,    -1,   315,   316,   119,    -1,    -1,    -1,
      -1,    -1,   125,    -1,    -1,    -1,   129,   328,    -1,    -1,
      -1,   332,   333,    -1,    -1,    -1,    -1,    -1,   141,    -1,
      -1,   342,   343,   146,   345,    -1,   149,    -1,    -1,    -1,
      -1,   154,   353,    -1,   157,   356,    -1,   160,   161,    -1,
      -1,    -1,   165,    -1,    -1,   168,    -1,   170,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,
     193,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,   228,    31,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,    -1,    -1,   267,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   277,    -1,    -1,   280,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,    -1,    -1,   108,    -1,   110,   309,   310,    -1,   114,
      -1,    -1,   315,   316,   119,    -1,    -1,    -1,    -1,    -1,
     125,    -1,    -1,    -1,   129,   328,    -1,    -1,    -1,   332,
     333,    -1,    -1,    -1,    -1,    -1,   141,    -1,    -1,   342,
     343,   146,   345,    -1,   149,    -1,    -1,    -1,    -1,   154,
     353,    -1,   157,   356,    -1,   160,   161,    -1,    -1,    -1,
     165,    -1,    -1,   168,    -1,   170,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,   193,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,   228,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      -1,    -1,   267,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   277,    -1,    -1,   280,   281,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,   110,   309,   310,    -1,   114,    -1,    -1,
     315,   316,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,    -1,   129,   328,    -1,    -1,    -1,   332,   333,    -1,
      -1,    -1,    70,    -1,   141,    -1,    -1,   342,   343,   146,
     345,    -1,   149,    -1,    -1,    -1,    -1,   154,   353,    -1,
     157,   356,    21,   160,   161,    -1,    -1,    -1,   165,    -1,
      -1,   168,    -1,   170,   102,   103,   104,   105,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,   119,    -1,    -1,    -1,   192,   193,   125,    -1,    -1,
      -1,   129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,   141,    -1,    -1,    -1,    -1,   146,    -1,
      -1,   149,    -1,    -1,    -1,    -1,   154,    -1,    -1,   157,
      -1,    -1,   160,   161,    -1,    -1,    -1,   165,    -1,    -1,
     168,    -1,   170,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,
     119,    -1,    -1,    -1,   192,   193,   125,    -1,    -1,    -1,
     129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     277,    -1,   141,   280,   281,    -1,    -1,   146,    -1,    -1,
     149,    -1,    22,    23,    -1,   154,    -1,    -1,   157,    -1,
      -1,   160,   161,    -1,    -1,    -1,   165,    -1,    -1,   168,
      -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,   315,   316,
      -1,   318,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   192,   193,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    -1,    -1,    -1,   342,   343,    -1,    -1,   277,
      -1,    -1,   280,   281,   351,    -1,   353,    -1,    -1,   356,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,    -1,    -1,    -1,    -1,
     110,    -1,    -1,    -1,   114,    -1,    -1,   315,   316,   119,
     318,    -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,   129,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,    -1,    -1,   342,   343,   146,    -1,   277,   149,
      -1,   280,   281,   351,   154,   353,    -1,   157,   356,    -1,
     160,   161,    -1,    -1,    -1,   165,    -1,    -1,   168,    -1,
     170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   315,   316,    -1,   318,
      -1,    23,   192,   193,    -1,    -1,    -1,    -1,    30,    31,
      -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   342,   343,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,   353,    -1,    -1,   356,    -1,    -1,
      62,    63,   103,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
      82,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,
      -1,    -1,   133,    -1,    -1,    97,    -1,    99,    -1,    -1,
     102,   103,   104,   105,    -1,    -1,   108,   277,   110,   150,
     280,   281,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,
      -1,    -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
      -1,    -1,    -1,    -1,   146,   315,   316,   149,   318,    -1,
      -1,    -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,
      -1,    -1,    -1,   165,    -1,    -1,   168,    -1,   170,    -1,
      -1,    -1,   342,   343,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   351,    -1,   353,    -1,    -1,   356,    -1,    -1,    -1,
     192,   193,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,    -1,    -1,   228,   229,   230,   231,
      -1,    -1,    -1,    -1,    -1,   237,   238,    -1,    -1,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,    -1,   305,   267,    -1,    -1,   309,   310,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,   319,    -1,
     282,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    36,
     292,    -1,    -1,    -1,    -1,    -1,   298,    -1,    -1,    -1,
      -1,   303,    -1,    -1,   345,    -1,    -1,   309,   310,    -1,
     312,    -1,    -1,   315,   316,   317,   318,    -1,    -1,    -1,
     322,    -1,    -1,    -1,   326,   327,   328,    -1,    -1,    -1,
     332,   333,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   341,
      -1,    -1,   344,   345,    -1,    -1,    -1,    -1,    -1,   351,
      -1,   353,    -1,    -1,   356,   102,   103,   104,   105,    -1,
      -1,   108,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,
      -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,
      -1,    -1,   149,    -1,    -1,    -1,    -1,   154,    -1,    -1,
     157,    -1,    -1,   160,   161,    -1,    -1,    -1,   165,    -1,
      -1,   168,    -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   192,   193,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    36,    -1,
      -1,   228,   229,   230,   231,    -1,    -1,    -1,    -1,    -1,
     237,   238,    -1,    -1,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,    -1,
     267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,    -1,    -1,
     108,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,   119,   309,   310,    -1,    -1,    -1,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   328,    -1,   141,    -1,   332,   333,    -1,   146,    -1,
      -1,   149,    -1,    -1,    -1,    -1,   154,   344,   345,   157,
      -1,    -1,   160,   161,   351,    -1,   353,   165,    -1,   356,
     168,    -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,   192,   193,    -1,    -1,    30,    31,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     228,   229,   230,   231,    -1,    -1,    -1,    -1,    -1,   237,
     238,    -1,    -1,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,    -1,    -1,   267,
     102,   103,   104,   105,    -1,    -1,   108,    -1,   110,    -1,
      37,    -1,   114,    -1,    -1,    42,    -1,   119,    45,    46,
      47,    48,    -1,   125,    51,    52,    -1,    54,    55,    56,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
      -1,   309,   310,    -1,   146,    -1,    -1,   149,    -1,    -1,
      -1,    -1,   154,    -1,    -1,   157,    -1,    -1,   160,   161,
     328,    -1,    -1,   165,   332,   333,   168,    -1,   170,    -1,
      97,    -1,    99,   100,   101,    -1,   344,   345,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   353,    -1,    23,   356,    -1,
     192,   193,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   228,   229,   230,   231,
      -1,    -1,    -1,    -1,    70,   237,   238,    -1,    -1,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,    -1,    -1,   267,   102,   103,   104,   105,
      -1,    -1,   108,    -1,   110,    -1,    -1,    -1,   114,    -1,
      -1,    -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,   125,
      -1,    -1,    -1,   129,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   141,    -1,   309,   310,    -1,
     146,    -1,    -1,   149,    -1,    -1,    -1,    -1,   154,    -1,
      -1,   157,    -1,    -1,   160,   161,   328,    -1,    -1,   165,
     332,   333,   168,    -1,   170,    -1,    -1,    -1,    -1,    -1,
     267,    -1,   344,   345,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   353,    -1,    -1,   356,   282,   192,   193,    -1,    -1,
     287,   288,   289,   290,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   298,    -1,    -1,    -1,    -1,   303,    -1,   305,   306,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,   228,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
      -1,   267,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   277,    -1,    -1,   280,   281,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,    -1,    -1,
      -1,    -1,   110,   309,   310,    -1,   114,    -1,    -1,   315,
     316,   119,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,
      -1,   129,   328,    -1,    -1,    -1,   332,   333,    -1,    -1,
      -1,    -1,    -1,   141,    -1,    -1,   342,   343,   146,   345,
      -1,   149,    -1,    -1,    -1,    -1,   154,   353,    -1,   157,
     356,    -1,   160,   161,    -1,    -1,    -1,   165,    -1,    -1,
     168,    -1,   170,    -1,    -1,     0,     1,    -1,    -1,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   192,   193,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    -1,    49,    -1,    -1,    52,    53,    54,
      -1,    56,    -1,    -1,    -1,    60,    61,    62,    -1,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   277,
      -1,    -1,   280,   281,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,   119,    -1,    -1,    -1,    -1,    -1,
     125,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   315,   316,    -1,
     318,    -1,    -1,    -1,   149,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,
      -1,    70,   119,    -1,   342,   343,    -1,    -1,   125,    -1,
      -1,    -1,   129,   351,    -1,   353,    -1,    -1,   356,    -1,
      -1,    -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,
      -1,    -1,   149,   102,   103,   104,   105,   154,    -1,    -1,
     157,   110,    -1,   160,   161,   114,    -1,    -1,   165,    -1,
     119,   168,    -1,   170,    -1,    -1,   125,    -1,    -1,    -1,
     129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,   141,    -1,    -1,   192,   193,   146,    -1,    -1,
     149,    -1,    -1,    -1,    -1,   154,    -1,    -1,   157,    -1,
      -1,   160,   161,    -1,    -1,    -1,   165,    -1,    -1,   168,
      -1,   170,   267,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    -1,   114,    -1,   282,    -1,    -1,
     119,    -1,    -1,   192,   193,    -1,   125,    -1,    -1,    -1,
     129,    -1,    -1,   298,    -1,    -1,    -1,    -1,   303,    -1,
     305,    -1,   141,    -1,    -1,    -1,    -1,   146,    -1,    -1,
     149,    -1,    -1,    -1,    -1,   154,    -1,    -1,   157,    -1,
     277,   160,   161,   280,   281,    -1,   165,    -1,    -1,   168,
      -1,   170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   192,   193,    -1,    -1,    -1,   315,   316,
      -1,   318,    -1,    -1,    -1,    -1,    -1,    -1,   277,    -1,
      -1,   280,   281,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   342,   343,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   353,    -1,    -1,   356,
      -1,    -1,    -1,    -1,    -1,    -1,   315,   316,    -1,   318,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   342,   343,    -1,    -1,    -1,   277,    -1,
      -1,   280,   281,    -1,   353,    -1,    -1,   356,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   315,   316,    -1,   318,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   342,   343,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   353,    -1,    -1,   356
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
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
     356,   410,   457,   576,   577,   580,   581,   582,   586,   649,
     652,   654,   658,   663,   664,   666,   668,   678,   679,   681,
     683,   685,   687,   691,   693,   695,   697,   699,   701,   703,
     705,   707,   709,   713,   721,   723,   725,   726,   728,   730,
     732,   734,   736,   738,   740,   742,    58,   338,   339,   340,
     403,   409,    58,   404,   409,   103,   405,   406,   363,   369,
     370,    89,   274,   276,   472,   472,   472,   472,     0,   361,
     456,   456,    57,   335,   336,   475,   476,   477,    35,    37,
      52,    62,    63,    67,    78,    79,    80,    81,    82,    83,
      97,    99,   243,   267,   282,   292,   298,   303,   312,   315,
     316,   317,   318,   322,   326,   327,   341,   351,   482,   483,
     484,   486,   487,   488,   489,   490,   491,   495,   496,   497,
     500,   501,   508,   512,   517,   518,   521,   522,   523,   524,
     525,   546,   547,   549,   550,   552,   553,   556,   557,   558,
     567,   568,   569,   570,   571,   574,   575,   581,   588,   589,
     590,   591,   592,   593,   597,   598,   599,   633,   647,   652,
     653,   676,   677,   678,   361,   350,   350,   361,   456,   529,
     411,   414,   482,   456,   419,   421,   576,   599,   424,   456,
     429,   463,   479,   472,   461,   463,   466,   466,   466,   469,
      89,   274,   276,   472,   472,   472,   472,   478,   394,   461,
     472,   473,   391,   459,   461,   462,   392,   461,   463,   464,
     479,   393,   461,   466,   467,   466,   466,   461,   469,   470,
      89,   274,   276,   622,   394,   394,   394,   394,   466,   472,
     399,   460,   481,   461,   481,   463,   481,    45,   481,   466,
     466,   481,   469,   481,    45,    46,   466,   481,   481,    89,
     274,   291,   622,   623,   472,    45,   481,    45,   481,    45,
     481,    45,   481,   472,   472,   472,    45,   481,   373,   472,
      45,   481,    45,   481,   472,   461,   463,   466,   466,   481,
      45,   466,   463,   106,   107,   108,   680,   111,   112,   244,
     245,   248,   584,   585,    32,    33,    34,   244,   655,   132,
     587,   166,   167,   724,   111,   112,   113,   682,   113,   115,
     116,   117,   118,   684,   111,   112,   120,   121,   122,   123,
     124,   686,   111,   112,   115,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   175,   688,   113,   115,   134,   142,
     143,   144,   145,   692,   113,   134,   147,   294,   694,   111,
     112,   126,   128,   129,   130,   151,   152,   153,   696,   113,
     115,   134,   142,   143,   145,   155,   156,   698,   127,   143,
     152,   158,   159,   700,   143,   159,   702,   152,   162,   163,
     704,   130,   134,   166,   167,   706,   134,   166,   167,   169,
     708,   134,   143,   158,   162,   166,   167,   171,   172,   173,
     174,   175,   710,   113,   166,   167,   714,   134,   166,   167,
     194,   227,   722,   113,   125,   127,   145,   149,   152,   232,
     265,   266,   345,   665,   667,   729,   233,   731,   233,   733,
     162,   234,   235,   236,   735,   127,   152,   727,   115,   131,
     152,   158,   239,   240,   737,   127,   152,   739,   113,   127,
     134,   152,   158,   741,   103,   130,   133,   150,   305,   319,
     345,   650,   651,   652,   111,   112,   115,   133,   244,   268,
     269,   270,   271,   272,   273,   275,   276,   277,   278,   279,
     280,   281,   284,   285,   286,   305,   669,   670,   673,   319,
     329,   657,   593,   598,   330,   228,   237,   238,   241,   242,
     743,   348,   349,   372,   660,   592,   456,   409,   339,   409,
      46,    48,    50,    51,    58,    59,    91,   407,   472,   472,
     472,   365,   617,   632,   619,   621,   102,   102,   102,    84,
     665,   283,   568,   456,   576,   648,   648,    62,    98,   456,
     103,   650,    89,   187,   274,   669,   670,   283,   283,   299,
     283,   301,   302,   509,    84,   162,    84,    84,   665,     4,
     362,   600,   601,   337,   480,   487,   414,   365,   284,   285,
     498,   499,   383,   162,   293,   294,   295,   296,   297,   502,
     503,   313,   520,     5,    70,    84,    86,   110,   114,   119,
     125,   129,   149,   228,   277,   280,   281,   293,   315,   316,
     342,   343,   353,   532,   533,   534,   535,   536,   537,   538,
     540,   541,   542,   543,   544,   545,   577,   580,   586,   642,
     643,   644,   649,   654,   658,   664,   665,   666,   668,   674,
     675,   678,    38,    39,   184,   185,   526,   527,    84,   319,
     320,   321,   548,   554,   555,    84,   551,   554,   377,   323,
     324,   325,   559,   560,   563,   564,    23,   576,   578,   579,
      45,   572,   573,    15,    16,    17,    18,   355,     8,    24,
      54,     9,    10,    11,    12,    13,    14,    19,   110,   114,
     119,   125,   141,   146,   149,   154,   157,   160,   161,   165,
     168,   170,   192,   193,   318,   353,   577,   579,   580,   594,
     595,   596,   599,   634,   635,   636,   637,   638,   639,   640,
     641,   643,   644,   645,   646,    52,    52,    22,   351,   615,
     634,   635,   640,   615,    38,   351,   528,   351,   351,   351,
     351,   351,   475,   482,   529,   411,   414,   419,   421,   424,
     429,   472,   472,   472,   365,   617,   632,   619,   621,   482,
      57,    57,    57,    57,   421,    57,   429,   472,   365,   374,
     376,   381,   421,    43,   398,   461,   466,   481,   472,    45,
     365,   461,   461,   461,   461,   374,   376,   381,   461,   365,
     461,   461,   376,   466,   456,     7,     8,   113,   248,   249,
     583,   297,   382,   103,   126,   283,   366,   371,   110,   125,
     110,   125,   363,   137,   138,   139,   140,   689,   369,   370,
      23,    38,   102,   173,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   711,   179,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   715,   720,   379,   369,   370,   372,   667,
     378,   378,   357,   357,   381,   381,   111,   112,   125,   133,
     149,   268,   269,   270,   671,   672,   673,   364,   330,   330,
     102,   378,   347,   659,   354,   408,   409,   630,   630,   630,
     284,   351,   616,   299,   351,   631,   351,   509,   618,   351,
     457,   620,     5,   125,   149,   544,    84,   544,   565,   566,
     593,    23,    23,    96,   351,    52,    52,    52,   102,   301,
      52,   673,    52,   544,   544,   301,   302,   513,   544,   102,
     562,   593,   597,   658,   664,   563,   544,   544,    84,    21,
     599,   604,   605,   606,   613,   640,   641,     7,   352,   457,
     351,   102,   102,   499,    77,   110,   125,   170,   251,   505,
     457,   102,   102,   102,   457,   504,   503,   141,   154,   170,
     314,   544,     5,   544,    84,   366,   371,   363,   369,   370,
      84,   537,   577,   644,    15,    16,    17,    18,   355,    20,
      22,     8,    54,     5,   554,    84,    86,   233,   293,     7,
       7,   102,   102,   527,     5,     7,     5,   544,   561,   580,
     595,   640,   560,     7,   456,   351,   456,   351,   573,   645,
     645,   636,   637,   638,   592,   351,   492,   578,   635,   369,
     370,   379,   640,     7,    20,    15,    16,    17,    18,   355,
       7,    20,    22,     8,   634,   635,   640,   544,   544,   102,
     352,   361,    20,   361,   102,   444,   413,   415,   420,   426,
     430,   528,   351,   351,   351,   351,   351,   630,   630,   630,
     616,   631,   618,   620,   102,   102,   102,   102,   102,   351,
     630,   103,   364,   461,   102,   585,   367,   102,   366,   369,
     366,   369,   113,   130,   135,   136,   233,   369,   690,   711,
      96,   130,   186,   187,   188,   189,   190,   191,   712,   217,
     221,   222,   223,   719,   212,   213,   214,   215,   717,   216,
     217,   218,   219,   220,   718,   718,   221,   224,   224,   225,
     226,   225,   113,   130,   162,   716,   380,   378,   102,   102,
     111,   112,   111,   112,   364,   364,   102,   102,   331,   656,
     102,   159,   346,   661,   665,   351,   351,   351,   102,   437,
     365,   513,   442,   374,   438,   102,   376,   443,   381,   544,
       5,     5,   544,   578,    89,    92,   480,   607,   608,   457,
     457,   102,   593,   602,   603,   544,   544,   544,   364,   102,
     544,    52,   544,   374,   102,   376,   103,   285,   510,   377,
      84,   323,    43,   544,   362,     5,   362,   267,   282,   298,
     610,   611,    89,    92,   480,   609,   612,   362,   601,   416,
     366,   148,   143,   148,   506,   507,   103,   113,   519,   580,
     113,   519,    70,   113,   519,   544,     5,   544,   544,   354,
     532,   532,   533,   534,   535,   102,   537,   532,   539,   578,
     599,   544,   544,    84,     8,    84,   577,   644,   674,   674,
     544,   555,   544,   554,   564,   565,   602,   362,   493,   494,
     354,   640,   634,   640,   645,   645,   636,   637,   638,   640,
     102,   634,   640,   596,   640,    20,    20,   102,    39,   361,
     352,   361,   384,   480,   528,    37,    47,    52,    54,    56,
     162,   267,   282,   298,   303,   305,   352,   361,   384,   412,
     480,    93,   113,   162,   352,   361,   384,   446,   452,   453,
     480,   482,    40,    88,    89,    90,    91,    93,    96,   113,
     162,   267,   352,   361,   384,   427,   480,   485,   486,    40,
      89,    91,   113,   162,   352,   361,   384,   427,   480,   485,
      41,    44,   162,   282,   352,   361,   384,   413,   415,   420,
     426,   430,   351,   351,   351,   365,   374,   376,   381,   430,
     364,   364,     7,   382,   369,     7,   379,   358,   358,   369,
     369,   370,   370,   656,   334,   656,   102,   368,   372,   111,
     112,   662,   440,   441,   439,   285,   352,   361,   384,   480,
     616,   102,   352,   361,   384,   480,   631,   352,   361,   384,
     480,   618,   510,   352,   361,   384,   480,   620,   544,   544,
       5,   103,   458,   458,   608,   351,   487,   607,   364,   364,
     364,   544,   364,    20,   103,   304,   511,   562,   561,   544,
      43,    81,    82,   614,   641,   647,   187,   284,   365,   299,
     611,   458,   458,   612,   352,   361,   482,   369,     7,   519,
     519,   519,   544,     5,   544,   164,   544,   554,   554,     5,
     352,   485,   487,   604,     7,   352,   634,   634,   102,    39,
     456,   474,   456,   465,   456,   468,   468,   456,   471,   103,
      89,   274,   276,   474,   474,   474,   474,   361,    78,    79,
     454,   455,   576,   103,    98,   361,   361,   361,   361,   361,
     418,   581,   458,   458,   350,    94,    95,   428,   102,   103,
     128,   129,   244,   264,   265,   434,   435,   445,    85,    86,
      87,    89,   422,   423,   361,   361,   361,   486,   418,   458,
     350,   435,   422,   361,   361,   361,   103,   350,    98,   365,
     352,   352,   352,   352,   352,   440,   441,   439,   352,   102,
     102,   375,   102,   368,   372,    93,   133,   268,   352,   361,
     384,   480,   628,    89,    96,   133,   167,   268,   352,   361,
     384,   480,   629,   113,   268,   352,   361,   384,   480,   625,
     102,   365,    20,   103,   374,   376,   511,   381,   544,   602,
     352,   364,   307,   308,   309,   310,   311,   516,   300,   515,
     102,   376,   377,   377,   544,   362,   102,   301,   102,   513,
     361,   507,   544,    84,   565,     5,   352,   352,     5,   362,
     494,   185,   530,   102,   436,   414,   419,   424,   429,   474,
     474,   474,   436,   436,   436,   436,    41,     8,   361,   361,
     361,   421,     8,   361,     7,   361,     5,   361,   421,     5,
     361,   150,   447,   351,   431,   576,   361,   352,   352,   352,
       7,   656,   350,   165,   170,   624,   460,   364,   458,   102,
     624,   102,   460,   364,   104,   460,   364,   516,   515,   487,
     300,   514,   102,   374,   510,   364,   102,   285,   102,   544,
     352,   565,   647,   184,   531,   361,   351,   351,   351,   351,
     351,   436,   436,   436,   351,   351,   351,   351,   103,   581,
     434,   423,    86,   417,   418,   581,    86,   282,   298,   303,
     305,   425,   435,    22,   102,   103,   349,   448,   449,   450,
     576,   361,   103,   432,   433,   576,   361,   364,   364,   364,
     102,   368,   351,   361,   361,   361,   361,   361,   361,   361,
     133,   361,   514,   352,   102,   374,   103,   285,   364,   102,
      20,   103,   352,   362,   530,   444,   415,   420,   426,   430,
     351,   351,   351,   437,   442,   438,   443,    43,    44,   451,
     418,   361,     8,   435,   365,   374,   376,   381,   361,   361,
     102,    22,    25,     7,   352,   103,   626,   627,   624,   284,
     365,   516,   515,   531,   352,   352,   352,   352,   352,   440,
     441,   439,   352,   352,   352,   352,   457,   576,   350,   447,
     361,   581,   361,   102,   102,   362,   433,     5,     7,   352,
     361,   514,   374,   361,   361,   361,   361,   361,   352,   352,
     352,   361,   361,   361,   361,   431,   102,   627,   361,   374,
     364,   364,   364,   365,   374,   376,   381,   361,   361,   361
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
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
     512,   512,   513,   513,   513,   514,   514,   515,   515,   515,
     516,   516,   516,   516,   516,   517,   518,   519,   519,   520,
     520,   520,   520,   520,   520,   520,   520,   521,   522,   522,
     523,   523,   523,   523,   523,   523,   524,   524,   525,   525,
     526,   526,   527,   527,   527,   527,   528,   528,   529,   530,
     530,   531,   531,   532,   532,   532,   532,   532,   532,   532,
     532,   532,   532,   532,   532,   532,   533,   533,   533,   534,
     534,   535,   535,   536,   536,   537,   538,   538,   539,   539,
     540,   540,   541,   542,   543,   543,   544,   544,   544,   545,
     545,   545,   545,   545,   545,   545,   545,   545,   545,   545,
     545,   545,   545,   546,   546,   547,   548,   548,   548,   549,
     549,   550,   551,   551,   551,   551,   551,   552,   552,   553,
     553,   554,   554,   555,   555,   555,   556,   556,   556,   556,
     557,   557,   558,   559,   559,   560,   560,   561,   561,   562,
     562,   562,   563,   563,   564,   564,   565,   565,   566,   567,
     567,   567,   568,   568,   568,   569,   569,   570,   570,   571,
     572,   572,   573,   574,   574,   575,   576,   577,   577,   578,
     578,   579,   580,   581,   581,   581,   581,   581,   581,   581,
     581,   581,   581,   581,   581,   581,   581,   581,   582,   583,
     583,   583,   584,   584,   584,   584,   584,   585,   585,   586,
     586,   587,   587,   588,   588,   588,   589,   589,   590,   590,
     591,   591,   592,   593,   593,   594,   595,   596,   596,   597,
     598,   598,   598,   599,   600,   600,   600,   601,   601,   601,
     602,   602,   603,   604,   604,   605,   605,   606,   606,   607,
     607,   608,   608,   608,   609,   609,   610,   610,   611,   611,
     611,   611,   611,   611,   612,   612,   612,   613,   614,   614,
     615,   615,   615,   615,   616,   617,   618,   619,   620,   621,
     622,   622,   622,   623,   623,   623,   624,   624,   625,   625,
     626,   626,   627,   628,   628,   628,   629,   629,   629,   629,
     629,   630,   631,   631,   632,   633,   633,   633,   633,   633,
     633,   633,   633,   634,   634,   635,   635,   635,   636,   636,
     636,   637,   637,   638,   638,   639,   639,   640,   641,   641,
     641,   641,   642,   642,   643,   644,   644,   644,   644,   644,
     644,   644,   644,   644,   644,   644,   644,   645,   645,   645,
     645,   645,   645,   645,   645,   645,   645,   645,   645,   645,
     645,   645,   645,   645,   646,   646,   646,   646,   646,   646,
     646,   647,   647,   647,   647,   647,   647,   648,   648,   649,
     649,   649,   650,   650,   651,   651,   651,   651,   651,   652,
     652,   652,   652,   652,   652,   652,   652,   652,   652,   652,
     652,   652,   652,   652,   652,   652,   652,   652,   652,   652,
     652,   652,   652,   653,   653,   653,   653,   653,   653,   654,
     654,   655,   655,   655,   656,   656,   657,   657,   658,   659,
     659,   660,   660,   661,   661,   662,   662,   663,   663,   664,
     664,   664,   665,   665,   666,   666,   667,   667,   667,   667,
     668,   668,   668,   669,   669,   670,   670,   670,   670,   670,
     670,   670,   670,   670,   670,   670,   670,   670,   670,   670,
     670,   670,   671,   671,   671,   671,   671,   671,   671,   672,
     672,   672,   672,   673,   673,   673,   673,   674,   674,   675,
     675,   676,   676,   676,   676,   677,   678,   678,   678,   678,
     678,   678,   678,   678,   678,   678,   678,   678,   678,   678,
     678,   678,   678,   678,   679,   680,   680,   680,   681,   682,
     682,   682,   683,   684,   684,   684,   684,   684,   685,   686,
     686,   686,   686,   686,   686,   686,   686,   686,   687,   687,
     687,   688,   688,   688,   688,   688,   688,   688,   688,   688,
     688,   688,   688,   689,   689,   689,   689,   690,   690,   690,
     690,   690,   691,   692,   692,   692,   692,   692,   692,   692,
     693,   694,   694,   694,   694,   695,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   697,   698,   698,   698,   698,
     698,   698,   698,   698,   699,   700,   700,   700,   700,   700,
     701,   702,   702,   703,   704,   704,   704,   705,   706,   706,
     706,   706,   707,   708,   708,   708,   708,   709,   709,   709,
     709,   710,   710,   710,   710,   710,   710,   710,   710,   710,
     710,   711,   711,   711,   711,   711,   711,   711,   711,   711,
     711,   711,   711,   711,   712,   712,   712,   712,   712,   712,
     712,   712,   713,   714,   714,   714,   715,   715,   715,   715,
     715,   715,   715,   715,   715,   715,   715,   715,   715,   715,
     715,   715,   715,   715,   716,   716,   716,   717,   717,   717,
     717,   718,   718,   718,   718,   718,   719,   719,   719,   719,
     720,   720,   720,   720,   720,   720,   720,   720,   720,   720,
     720,   720,   721,   721,   722,   722,   722,   722,   723,   724,
     724,   725,   725,   725,   725,   725,   725,   725,   725,   726,
     727,   727,   728,   729,   729,   729,   729,   730,   731,   732,
     733,   734,   735,   735,   735,   735,   736,   737,   737,   737,
     737,   737,   737,   738,   739,   739,   740,   741,   741,   741,
     741,   741,   742,   743,   743,   743,   743,   743
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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
       8,     7,     4,     1,     1,     0,     1,     1,     0,     3,
       6,     4,     1,     1,     0,     0,     3,     0,     3,     3,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     0,
       4,     3,     4,     3,     4,     3,     3,     2,     1,     1,
       3,     4,     4,     5,     6,     5,     1,     2,     1,     3,
       1,     2,     2,     2,     1,     1,     6,     8,     0,     0,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     3,     1,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       2,     3,     3,     4,     5,     2,     3,     2,     6,     4,
       3,     4,     3,     2,     1,     1,     3,     4,     1,     2,
       1,     1,     2,     3,     1,     3,     4,     3,     5,     3,
       6,     1,     3,     1,     1,     1,     2,     4,     6,     6,
       1,     2,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     2,     1,     4,
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
       1,     1,     3,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     5,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     1,     1,     2,     1,     1,     1,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     2,     4,     3,
       8,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     5,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     3,     1,     1,     1,     1,     2,     4,     2,
       1,     2,     1,     1,     1,     4,     2,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     1,     1
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
    case 103: /* "string"  */
#line 315 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4731 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 104: /* "quoted string"  */
#line 315 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4737 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 105: /* "string with a trailing asterisk"  */
#line 315 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4743 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* line  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4749 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* base_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4755 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* add_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4761 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* replace_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4767 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* create_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4773 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* insert_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4779 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* table_or_id_spec  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4785 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* chain_or_id_spec  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4791 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 393: /* set_or_id_spec  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4797 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* obj_or_id_spec  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4803 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* delete_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4809 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 396: /* get_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4815 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* list_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4821 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* basehook_device_name  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4827 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* basehook_spec  */
#line 640 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4833 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* reset_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4839 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* flush_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4845 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* rename_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4851 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* import_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4857 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* export_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4863 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* monitor_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4869 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* monitor_event  */
#line 865 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4875 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* describe_cmd  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4881 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* table_block_alloc  */
#line 652 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 4887 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* chain_block_alloc  */
#line 654 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 4893 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* typeof_data_expr  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4899 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* typeof_expr  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4905 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* set_block_alloc  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4911 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* set_block_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4917 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* map_block_alloc  */
#line 666 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4923 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* flowtable_block_alloc  */
#line 670 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 4929 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* flowtable_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4935 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 432: /* flowtable_list_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4941 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* flowtable_expr_member  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4947 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* data_type_atom_expr  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4953 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* data_type_expr  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4959 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 436: /* obj_block_alloc  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4965 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 445: /* type_identifier  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4971 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* extended_prio_name  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4977 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* dev_spec  */
#line 649 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).expr)); }
#line 4983 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 454: /* policy_expr  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4989 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 456: /* identifier  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4995 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* string  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 5001 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* table_spec  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5007 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* tableid_spec  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5013 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 463: /* chain_spec  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5019 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* chainid_spec  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5025 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* chain_identifier  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5031 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* set_spec  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5037 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 467: /* setid_spec  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5043 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* set_identifier  */
#line 637 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5049 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* flowtable_spec  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5055 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* flowtableid_spec  */
#line 637 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5061 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* obj_spec  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5067 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* objid_spec  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5073 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* obj_identifier  */
#line 637 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5079 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* handle_spec  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5085 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* position_spec  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5091 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* index_spec  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5097 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* rule_position  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5103 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* ruleid_spec  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5109 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* comment_spec  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 5115 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* ruleset_spec  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 5121 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* rule  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 5127 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* stmt_list  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 5133 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* stateful_stmt_list  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 5139 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 486: /* stateful_stmt  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5145 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* stmt  */
#line 678 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5151 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 489: /* chain_stmt  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5157 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 490: /* verdict_stmt  */
#line 678 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5163 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 491: /* verdict_map_stmt  */
#line 761 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5169 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 492: /* verdict_map_expr  */
#line 764 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5175 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 493: /* verdict_map_list_expr  */
#line 764 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5181 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* verdict_map_list_member_expr  */
#line 764 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5187 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 495: /* connlimit_stmt  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5193 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 496: /* counter_stmt  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5199 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 497: /* counter_stmt_alloc  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5205 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* log_stmt  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5211 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* log_stmt_alloc  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5217 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 508: /* limit_stmt  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5223 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* quota_unit  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 5229 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 512: /* quota_stmt  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5235 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* reject_stmt  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5241 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* reject_stmt_alloc  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5247 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* reject_with_expr  */
#line 709 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5253 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 521: /* nat_stmt  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5259 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 522: /* nat_stmt_alloc  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5265 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* tproxy_stmt  */
#line 699 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5271 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 524: /* synproxy_stmt  */
#line 701 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5277 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 525: /* synproxy_stmt_alloc  */
#line 701 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5283 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* synproxy_obj  */
#line 787 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5289 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* primary_stmt_expr  */
#line 748 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5295 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* shift_stmt_expr  */
#line 750 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5301 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* and_stmt_expr  */
#line 752 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5307 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* exclusive_or_stmt_expr  */
#line 752 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5313 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* inclusive_or_stmt_expr  */
#line 752 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5319 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 537: /* basic_stmt_expr  */
#line 748 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5325 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* concat_stmt_expr  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5331 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* map_stmt_expr_set  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5337 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* map_stmt_expr  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5343 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* prefix_stmt_expr  */
#line 745 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5349 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 542: /* range_stmt_expr  */
#line 745 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5355 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* multiton_stmt_expr  */
#line 743 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5361 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 544: /* stmt_expr  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5367 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 546: /* masq_stmt  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5373 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* masq_stmt_alloc  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5379 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 549: /* redir_stmt  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5385 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 550: /* redir_stmt_alloc  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5391 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 552: /* dup_stmt  */
#line 712 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5397 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 553: /* fwd_stmt  */
#line 714 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5403 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 556: /* queue_stmt  */
#line 707 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5409 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 557: /* queue_stmt_compat  */
#line 707 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5415 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 558: /* queue_stmt_alloc  */
#line 707 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5421 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 561: /* queue_stmt_expr_simple  */
#line 709 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5427 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 562: /* queue_stmt_expr  */
#line 709 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5433 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 565: /* set_elem_expr_stmt  */
#line 771 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5439 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 566: /* set_elem_expr_stmt_alloc  */
#line 771 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5445 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 567: /* set_stmt  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5451 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 569: /* map_stmt  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5457 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 570: /* meter_stmt  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5463 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 571: /* flow_stmt_legacy_alloc  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5469 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 574: /* meter_stmt_alloc  */
#line 721 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5475 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 575: /* match_stmt  */
#line 678 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5481 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 576: /* variable_expr  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5487 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 577: /* symbol_expr  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5493 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 578: /* set_ref_expr  */
#line 732 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5499 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 579: /* set_ref_symbol_expr  */
#line 732 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5505 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 580: /* integer_expr  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5511 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 581: /* primary_expr  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5517 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 582: /* fib_expr  */
#line 856 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5523 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 586: /* osf_expr  */
#line 861 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5529 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 588: /* shift_expr  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5535 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 589: /* and_expr  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5541 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 590: /* exclusive_or_expr  */
#line 728 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5547 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 591: /* inclusive_or_expr  */
#line 728 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5553 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 592: /* basic_expr  */
#line 730 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5559 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 593: /* concat_expr  */
#line 755 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5565 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 594: /* prefix_rhs_expr  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5571 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 595: /* range_rhs_expr  */
#line 737 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5577 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 596: /* multiton_rhs_expr  */
#line 735 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5583 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 597: /* map_expr  */
#line 758 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5589 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 598: /* expr  */
#line 777 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5595 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 599: /* set_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5601 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 600: /* set_list_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5607 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 601: /* set_list_member_expr  */
#line 767 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5613 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 602: /* meter_key_expr  */
#line 774 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5619 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 603: /* meter_key_expr_alloc  */
#line 774 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5625 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 604: /* set_elem_expr  */
#line 769 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5631 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 605: /* set_elem_key_expr  */
#line 893 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5637 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 606: /* set_elem_expr_alloc  */
#line 769 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5643 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 610: /* set_elem_stmt_list  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 5649 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 611: /* set_elem_stmt  */
#line 678 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5655 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 613: /* set_lhs_expr  */
#line 769 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5661 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 614: /* set_rhs_expr  */
#line 769 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5667 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 615: /* initializer_expr  */
#line 777 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5673 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 617: /* counter_obj  */
#line 787 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5679 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 619: /* quota_obj  */
#line 787 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5685 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 621: /* secmark_obj  */
#line 787 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5691 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 626: /* timeout_states  */
#line 886 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5697 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 627: /* timeout_state  */
#line 886 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 5703 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 630: /* ct_obj_alloc  */
#line 787 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5709 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 632: /* limit_obj  */
#line 787 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 5715 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 633: /* relational_expr  */
#line 790 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5721 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 634: /* list_rhs_expr  */
#line 782 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5727 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 635: /* rhs_expr  */
#line 780 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5733 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 636: /* shift_rhs_expr  */
#line 782 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5739 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 637: /* and_rhs_expr  */
#line 784 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5745 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 638: /* exclusive_or_rhs_expr  */
#line 784 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5751 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 639: /* inclusive_or_rhs_expr  */
#line 784 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5757 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 640: /* basic_rhs_expr  */
#line 780 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5763 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 641: /* concat_rhs_expr  */
#line 780 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5769 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 643: /* boolean_expr  */
#line 876 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5775 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 644: /* keyword_expr  */
#line 777 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5781 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 645: /* primary_rhs_expr  */
#line 782 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5787 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 647: /* verdict_expr  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5793 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 648: /* chain_expr  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5799 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 649: /* meta_expr  */
#line 838 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5805 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 653: /* meta_stmt  */
#line 686 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5811 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 654: /* socket_expr  */
#line 842 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5817 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 658: /* numgen_expr  */
#line 803 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5823 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 663: /* xfrm_expr  */
#line 890 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5829 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 664: /* hash_expr  */
#line 803 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5835 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 666: /* rt_expr  */
#line 848 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5841 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 668: /* ct_expr  */
#line 852 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5847 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 674: /* symbol_stmt_expr  */
#line 782 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5853 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 675: /* list_stmt_expr  */
#line 750 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5859 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 676: /* ct_stmt  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5865 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 677: /* payload_stmt  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5871 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 678: /* payload_expr  */
#line 794 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5877 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 679: /* payload_raw_expr  */
#line 794 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5883 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 681: /* eth_hdr_expr  */
#line 797 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5889 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 683: /* vlan_hdr_expr  */
#line 797 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5895 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 685: /* arp_hdr_expr  */
#line 800 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5901 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 687: /* ip_hdr_expr  */
#line 803 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5907 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 691: /* icmp_hdr_expr  */
#line 803 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5913 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 693: /* igmp_hdr_expr  */
#line 803 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5919 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 695: /* ip6_hdr_expr  */
#line 807 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5925 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 697: /* icmp6_hdr_expr  */
#line 807 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5931 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 699: /* auth_hdr_expr  */
#line 810 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5937 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 701: /* esp_hdr_expr  */
#line 810 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5943 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 703: /* comp_hdr_expr  */
#line 810 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5949 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 705: /* udp_hdr_expr  */
#line 813 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5955 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 707: /* udplite_hdr_expr  */
#line 813 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5961 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 709: /* tcp_hdr_expr  */
#line 871 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5967 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 713: /* dccp_hdr_expr  */
#line 816 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5973 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 720: /* sctp_chunk_alloc  */
#line 816 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5979 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 721: /* sctp_hdr_expr  */
#line 816 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5985 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 723: /* th_hdr_expr  */
#line 822 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5991 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 725: /* exthdr_expr  */
#line 826 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5997 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 726: /* hbh_hdr_expr  */
#line 828 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6003 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 728: /* rt_hdr_expr  */
#line 831 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6009 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 730: /* rt0_hdr_expr  */
#line 831 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6015 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 732: /* rt2_hdr_expr  */
#line 831 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6021 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 734: /* rt4_hdr_expr  */
#line 831 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6027 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 736: /* frag_hdr_expr  */
#line 828 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6033 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 738: /* dst_hdr_expr  */
#line 828 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6039 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 740: /* mh_hdr_expr  */
#line 834 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6045 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 742: /* exthdr_exists_expr  */
#line 880 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 6051 "parser_bison.c" /* yacc.c:1257  */
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
#line 159 "parser_bison.y" /* yacc.c:1431  */
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 6167 "parser_bison.c" /* yacc.c:1431  */
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
#line 899 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 6366 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 8:
#line 915 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_ARP); }
#line 6372 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 9:
#line 916 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_CT); }
#line 6378 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 10:
#line 917 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_COUNTER); }
#line 6384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 11:
#line 918 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_ETH); }
#line 6390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 12:
#line 919 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_FIB); }
#line 6396 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 13:
#line 920 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_HASH); }
#line 6402 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 14:
#line 921 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP); }
#line 6408 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 15:
#line 922 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_IP6); }
#line 6414 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 16:
#line 923 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_VLAN); }
#line 6420 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 17:
#line 924 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_IPSEC); }
#line 6426 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 18:
#line 925 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_CMD_LIST); }
#line 6432 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 19:
#line 926 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_LIMIT); }
#line 6438 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 20:
#line 927 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_NUMGEN); }
#line 6444 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 21:
#line 928 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_QUOTA); }
#line 6450 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 22:
#line 929 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_QUEUE); }
#line 6456 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 23:
#line 930 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_RT); }
#line 6462 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 24:
#line 931 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_SCTP); }
#line 6468 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 25:
#line 932 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SCTP_CHUNK); }
#line 6474 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 26:
#line 933 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_SECMARK); }
#line 6480 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 27:
#line 934 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_EXPR_SOCKET); }
#line 6486 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 28:
#line 936 "parser_bison.y" /* yacc.c:1652  */
    { scanner_pop_start_cond(nft->scanner, PARSER_SC_STMT_LOG); }
#line 6492 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 29:
#line 939 "parser_bison.y" /* yacc.c:1652  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 6504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 30:
#line 947 "parser_bison.y" /* yacc.c:1652  */
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
#line 6523 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 31:
#line 962 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 6534 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 32:
#line 969 "parser_bison.y" /* yacc.c:1652  */
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
#line 6550 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 33:
#line 981 "parser_bison.y" /* yacc.c:1652  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 6560 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 34:
#line 988 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 6566 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 35:
#line 989 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 6572 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 36:
#line 990 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 6578 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 37:
#line 992 "parser_bison.y" /* yacc.c:1652  */
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
#line 6600 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 38:
#line 1011 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6606 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 39:
#line 1012 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6612 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 40:
#line 1013 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6618 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 41:
#line 1014 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 42:
#line 1015 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 43:
#line 1016 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6636 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 44:
#line 1017 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6642 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 45:
#line 1018 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 6648 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 46:
#line 1019 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6654 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 47:
#line 1020 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6660 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 48:
#line 1021 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6666 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 49:
#line 1022 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 50:
#line 1023 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6678 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 51:
#line 1024 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6684 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 52:
#line 1025 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 6690 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 53:
#line 1029 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6698 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 54:
#line 1034 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 55:
#line 1040 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 56:
#line 1045 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6727 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 57:
#line 1052 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6735 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 58:
#line 1056 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6743 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 59:
#line 1061 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 60:
#line 1068 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6763 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 61:
#line 1074 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6771 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 62:
#line 1079 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6781 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 63:
#line 1085 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 6794 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 64:
#line 1094 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 6802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 65:
#line 1098 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6810 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 66:
#line 1102 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 6818 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 67:
#line 1106 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6826 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 68:
#line 1110 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6834 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 69:
#line 1114 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6842 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 70:
#line 1118 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6850 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 71:
#line 1122 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 6858 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 72:
#line 1126 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6866 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 73:
#line 1130 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 6874 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 74:
#line 1134 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 6882 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 75:
#line 1138 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 6890 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 76:
#line 1142 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SYNPROXY, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6898 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 77:
#line 1148 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6906 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 78:
#line 1154 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6914 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 79:
#line 1159 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 6924 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 80:
#line 1165 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6932 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 81:
#line 1170 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 6943 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 82:
#line 1178 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 83:
#line 1185 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 6963 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 84:
#line 1191 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 85:
#line 1196 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 6981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 86:
#line 1202 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[-1].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), obj);
			}
#line 6994 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 87:
#line 1211 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7002 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 88:
#line 1215 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7010 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 89:
#line 1219 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7018 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 90:
#line 1223 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7026 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 91:
#line 1227 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 7034 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 92:
#line 1231 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7042 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 93:
#line 1235 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-3].handle), &(yyloc), (yyvsp[-2].obj));
			}
#line 7050 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 94:
#line 1239 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SYNPROXY, &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
			}
#line 7058 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 95:
#line 1245 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 7066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 104:
#line 1267 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7074 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 105:
#line 1271 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7082 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1275 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7090 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1279 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7098 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1283 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7106 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1287 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 7114 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1291 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7122 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1295 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7130 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1300 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 7140 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1306 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7148 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1310 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7156 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 115:
#line 1314 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-3].val), &(yyvsp[-2].handle), &(yyloc), (yyvsp[-1].obj));
				if ((yyvsp[-3].val) == NFT_OBJECT_CT_TIMEOUT)
					init_list_head(&(yyvsp[-1].obj)->ct_timeout.timeout_list);
			}
#line 7166 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 116:
#line 1320 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7174 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 117:
#line 1324 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7182 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 118:
#line 1328 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7190 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 119:
#line 1334 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_ELEMENTS, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 7198 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1340 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7206 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1344 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7214 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1348 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7222 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1352 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7230 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1356 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7238 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1360 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7246 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1364 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7254 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1368 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7262 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1372 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7270 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1376 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7278 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1380 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7286 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1384 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7294 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1388 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7302 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1392 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7310 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1396 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7318 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1400 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1404 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1408 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7342 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 138:
#line 1412 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7350 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 139:
#line 1416 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7358 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 140:
#line 1420 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXYS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7366 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 141:
#line 1424 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SYNPROXY, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7374 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1428 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7382 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1432 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1436 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7398 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 145:
#line 1440 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7406 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 146:
#line 1444 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7414 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 147:
#line 1448 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7422 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 148:
#line 1452 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7430 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 149:
#line 1456 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7438 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 150:
#line 1460 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7446 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 151:
#line 1464 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7454 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 152:
#line 1468 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, (yyvsp[-3].val), &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7462 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 153:
#line 1472 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_HOOKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7470 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1478 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.string) = (yyvsp[0].string);
			}
#line 7478 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1484 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 7486 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1488 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].string)) {
					(yyvsp[-1].handle).obj.name = (yyvsp[0].string);
					(yyvsp[-1].handle).obj.location = (yylsp[0]);
				}
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 157:
#line 1498 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7506 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 158:
#line 1502 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7514 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 159:
#line 1506 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[-1].handle),&(yyloc), NULL);
			}
#line 7522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1510 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7530 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1514 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1518 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), NULL);
			}
#line 7546 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1524 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7554 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 164:
#line 1528 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7562 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1532 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7570 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 166:
#line 1536 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7578 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 167:
#line 1540 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7586 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 168:
#line 1544 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7594 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 169:
#line 1548 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 7602 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1554 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 7611 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1561 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7621 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1567 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7631 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 173:
#line 1575 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 174:
#line 1581 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 7651 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 175:
#line 1589 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 7662 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 176:
#line 1597 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = NULL; }
#line 7668 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 177:
#line 1598 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7674 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 178:
#line 1601 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 7680 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 179:
#line 1602 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 7686 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 180:
#line 1603 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 7692 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 181:
#line 1604 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 7698 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 182:
#line 1605 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 7704 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 183:
#line 1606 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 7710 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 184:
#line 1607 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 7716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 185:
#line 1608 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 7722 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 186:
#line 1611 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 7728 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 188:
#line 1615 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 7734 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 189:
#line 1616 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7740 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 190:
#line 1617 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 7746 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 191:
#line 1621 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 7756 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 192:
#line 1629 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 7765 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 193:
#line 1636 "parser_bison.y" /* yacc.c:1652  */
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
#line 7784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 194:
#line 1651 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].table)->comment, &(yyloc), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].table)->comment = (yyvsp[0].string);
			}
#line 7796 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 195:
#line 1660 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 7802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 199:
#line 1667 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7815 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 200:
#line 1678 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7827 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 201:
#line 1688 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7839 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 202:
#line 1699 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7851 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 203:
#line 1709 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 204:
#line 1720 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7877 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 205:
#line 1729 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 7890 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 206:
#line 1738 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 7903 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 207:
#line 1747 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-9].table)->objs);
				(yyval.table) = (yyvsp[-9].table);
			}
#line 7916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 208:
#line 1758 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7929 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 209:
#line 1769 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].obj)->location = (yylsp[-6]);
				(yyvsp[-5].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-5].obj)->handle, &(yyvsp[-6].handle));
				handle_free(&(yyvsp[-6].handle));
				list_add_tail(&(yyvsp[-5].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 7942 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 210:
#line 1780 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SYNPROXY;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 7955 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 211:
#line 1791 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 7964 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 212:
#line 1797 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7970 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 218:
#line 1804 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 7979 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 219:
#line 1809 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].chain)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].chain)->comment = (yyvsp[-1].string);
			}
#line 7991 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 220:
#line 1818 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 7997 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 222:
#line 1821 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 8006 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 223:
#line 1828 "parser_bison.y" /* yacc.c:1652  */
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
#line 8031 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 224:
#line 1849 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 8044 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 225:
#line 1860 "parser_bison.y" /* yacc.c:1652  */
    {
				if (expr_ops((yyvsp[0].expr))->build_udata == NULL) {
					erec_queue(error(&(yylsp[0]), "primary expression type '%s' lacks typeof serialization", expr_ops((yyvsp[0].expr))->name),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}

				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8059 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 226:
#line 1871 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 8072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 227:
#line 1883 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 8080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 228:
#line 1888 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 8086 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 231:
#line 1892 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8095 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 232:
#line 1897 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				datatype_set((yyvsp[-3].set)->key, (yyvsp[-1].expr)->dtype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8105 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 233:
#line 1903 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8114 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 234:
#line 1908 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 235:
#line 1913 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8132 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 236:
#line 1918 "parser_bison.y" /* yacc.c:1652  */
    {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 8142 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 237:
#line 1924 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8151 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 238:
#line 1929 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 8160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 240:
#line 1935 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 8173 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 243:
#line 1950 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8181 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 245:
#line 1956 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 8187 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 246:
#line 1957 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 8193 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 247:
#line 1958 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 8199 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 248:
#line 1959 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_EVAL; }
#line 8205 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 249:
#line 1963 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 8213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 250:
#line 1968 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_COUNTER; }
#line 8219 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 251:
#line 1969 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_QUOTA; }
#line 8225 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 252:
#line 1970 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_LIMIT; }
#line 8231 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 253:
#line 1971 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_SECMARK; }
#line 8237 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 254:
#line 1974 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 8243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 257:
#line 1978 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8252 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 258:
#line 1985 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 8264 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 259:
#line 1995 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 8277 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 260:
#line 2006 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				datatype_set((yyvsp[-5].set)->key, (yyvsp[-3].expr)->dtype);
				(yyvsp[-5].set)->data = (yyvsp[-1].expr);

				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 8290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 261:
#line 2017 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].set)->key = (yyvsp[-4].expr);
				datatype_set((yyvsp[-6].set)->key, (yyvsp[-4].expr)->dtype);
				(yyvsp[-6].set)->data = (yyvsp[-1].expr);
				(yyvsp[-6].set)->data->flags |= EXPR_F_INTERVAL;

				(yyvsp[-6].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-6].set);
			}
#line 8304 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 262:
#line 2029 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = (yyvsp[-1].val);
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 8315 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 263:
#line 2036 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8324 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 264:
#line 2041 "parser_bison.y" /* yacc.c:1652  */
    {
				list_splice_tail((yyvsp[-1].list), &(yyvsp[-2].set)->stmt_list);
				(yyval.set) = (yyvsp[-2].set);
				free((yyvsp[-1].list));
			}
#line 8334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 265:
#line 2047 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 8343 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 266:
#line 2052 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-2].set)->comment, &(yylsp[-1]), state)) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				(yyvsp[-2].set)->comment = (yyvsp[-1].string);
				(yyval.set) = (yyvsp[-2].set);
			}
#line 8356 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 268:
#line 2064 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 8364 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 269:
#line 2068 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 8372 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 270:
#line 2073 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 8378 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 271:
#line 2074 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 8384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 272:
#line 2078 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 8392 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 273:
#line 2083 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 8398 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 276:
#line 2087 "parser_bison.y" /* yacc.c:1652  */
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
#line 8416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 277:
#line 2101 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 8424 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 278:
#line 2105 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->flags |= NFT_FLOWTABLE_COUNTER;
			}
#line 8432 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 279:
#line 2109 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->flags |= FLOWTABLE_F_HW_OFFLOAD;
			}
#line 8440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 280:
#line 2115 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8449 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 281:
#line 2120 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8458 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 282:
#line 2127 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8467 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 283:
#line 2132 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8476 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 285:
#line 2140 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 8487 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 286:
#line 2147 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8496 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 287:
#line 2154 "parser_bison.y" /* yacc.c:1652  */
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
#line 8513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 288:
#line 2167 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yylsp[0]), &time_type, time_type.byteorder,
							 time_type.size, NULL);
			}
#line 8522 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 290:
#line 2175 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 8535 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 291:
#line 2186 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 8543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 292:
#line 2191 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8549 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 295:
#line 2195 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8557 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 296:
#line 2199 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8569 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 297:
#line 2208 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8575 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 300:
#line 2212 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8583 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 301:
#line 2216 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8595 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 302:
#line 2225 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8601 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 305:
#line 2229 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8609 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 306:
#line 2233 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8621 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 307:
#line 2243 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[(-1) - (0)].obj);
				init_list_head(&(yyval.obj)->ct_timeout.timeout_list);
			}
#line 8630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 310:
#line 2250 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8638 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 311:
#line 2254 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8650 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 312:
#line 2263 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8656 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 315:
#line 2267 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8664 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 316:
#line 2271 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 317:
#line 2280 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 320:
#line 2284 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8690 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 321:
#line 2288 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8702 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 322:
#line 2297 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 325:
#line 2301 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 326:
#line 2305 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8728 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 327:
#line 2314 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 8734 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 330:
#line 2318 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 8742 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 331:
#line 2322 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].obj)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].obj)->comment = (yyvsp[0].string);
			}
#line 8754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 332:
#line 2331 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 8760 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 333:
#line 2332 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("mark"); }
#line 8766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 334:
#line 2333 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("dscp"); }
#line 8772 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 335:
#line 2334 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("ecn"); }
#line 8778 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 336:
#line 2335 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("classid"); }
#line 8784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 337:
#line 2339 "parser_bison.y" /* yacc.c:1652  */
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
#line 8817 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 338:
#line 2370 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 8826 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 339:
#line 2377 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.string) = strdup("out");
			}
#line 8834 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 341:
#line 2384 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 8848 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 342:
#line 2394 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 8859 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 343:
#line 2401 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 8874 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 344:
#line 2412 "parser_bison.y" /* yacc.c:1652  */
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
#line 8891 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 345:
#line 2425 "parser_bison.y" /* yacc.c:1652  */
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
#line 8908 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 346:
#line 2439 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = (yyvsp[0].val); }
#line 8914 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 347:
#line 2440 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = -(yyvsp[0].val); }
#line 8920 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 348:
#line 2444 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &string_type,
							   BYTEORDER_HOST_ENDIAN,
							   strlen((yyvsp[0].string)) * BITS_PER_BYTE, (yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), expr);

			}
#line 8936 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 349:
#line 2456 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &ifname_type);
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_LIST);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8946 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 350:
#line 2462 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8954 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 351:
#line 2465 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = NULL; }
#line 8960 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 352:
#line 2469 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].chain)->flags |= CHAIN_F_HW_OFFLOAD;
			}
#line 8968 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 353:
#line 2475 "parser_bison.y" /* yacc.c:1652  */
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
#line 8983 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 354:
#line 2488 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 8992 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 355:
#line 2493 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 9003 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 356:
#line 2501 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_ACCEPT; }
#line 9009 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 357:
#line 2502 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_DROP;   }
#line 9015 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 362:
#line 2514 "parser_bison.y" /* yacc.c:1652  */
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
#line 9032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 363:
#line 2528 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 9038 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 365:
#line 2532 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 9044 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 366:
#line 2533 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 9050 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 367:
#line 2534 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_INET; }
#line 9056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 368:
#line 2535 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_ARP; }
#line 9062 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 369:
#line 2536 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 9068 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 370:
#line 2537 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 9074 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 371:
#line 2541 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 9085 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 372:
#line 2550 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yylsp[0]);
			}
#line 9096 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 373:
#line 2559 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 9106 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 374:
#line 2567 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 9116 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 375:
#line 2575 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 9126 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 376:
#line 2583 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 9136 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 377:
#line 2591 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yylsp[0]);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 9146 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 378:
#line 2599 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 9156 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 379:
#line 2607 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-1].handle);
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 9166 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 380:
#line 2615 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 9176 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 381:
#line 2623 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable.name	= (yyvsp[0].string);
				(yyval.handle).flowtable.location	= (yylsp[0]);
			}
#line 9186 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 382:
#line 2631 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 9196 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 383:
#line 2639 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 9206 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 384:
#line 2647 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 9216 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 385:
#line 2655 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yylsp[0]);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 9226 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 386:
#line 2663 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 9236 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 387:
#line 2671 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 9246 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 388:
#line 2679 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 9254 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 389:
#line 2683 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9263 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 390:
#line 2688 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9275 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 391:
#line 2696 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9284 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 392:
#line 2703 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 9293 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 393:
#line 2710 "parser_bison.y" /* yacc.c:1652  */
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
#line 9308 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 394:
#line 2723 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 9317 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 395:
#line 2728 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 9326 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 396:
#line 2735 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 9334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 397:
#line 2739 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 9342 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 398:
#line 2745 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 9356 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 399:
#line 2757 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 9366 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 400:
#line 2763 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 9375 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 401:
#line 2770 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 9385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 402:
#line 2776 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 9394 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 427:
#line 2810 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_JUMP; }
#line 9400 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 428:
#line 2811 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_GOTO; }
#line 9406 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 429:
#line 2815 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].chain)->location = (yylsp[-3]);
				close_scope(state);
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				(yyval.stmt) = chain_stmt_alloc(&(yyloc), (yyvsp[-1].chain), (yyvsp[-4].val));
			}
#line 9417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 430:
#line 2824 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 9425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 431:
#line 2828 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 9433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 432:
#line 2834 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 433:
#line 2840 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9450 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 435:
#line 2848 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9459 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 436:
#line 2853 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9468 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 438:
#line 2861 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 9476 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 439:
#line 2867 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 9485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 440:
#line 2872 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 9495 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 443:
#line 2883 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 9503 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 444:
#line 2887 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 9513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 445:
#line 2895 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9521 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 447:
#line 2902 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 9529 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 448:
#line 2906 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 9537 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 451:
#line 2916 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 9545 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 452:
#line 2922 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9553 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 454:
#line 2929 "parser_bison.y" /* yacc.c:1652  */
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
#line 9682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 455:
#line 3054 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 9691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 456:
#line 3059 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 9700 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 457:
#line 3064 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 9709 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 458:
#line 3069 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 9718 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 459:
#line 3074 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 9726 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 460:
#line 3080 "parser_bison.y" /* yacc.c:1652  */
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
#line 9758 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 461:
#line 3110 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 9766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 462:
#line 3114 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 9774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 463:
#line 3118 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 9782 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 464:
#line 3122 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 9790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 465:
#line 3126 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 9798 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 466:
#line 3132 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9806 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 468:
#line 3139 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 9814 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 469:
#line 3143 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 9822 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 470:
#line 3149 "parser_bison.y" /* yacc.c:1652  */
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
#line 9840 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 471:
#line 3163 "parser_bison.y" /* yacc.c:1652  */
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
#line 9869 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 472:
#line 3188 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 9879 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 473:
#line 3195 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 9885 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 474:
#line 3196 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9891 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 475:
#line 3197 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9897 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 476:
#line 3200 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("bytes"); }
#line 9903 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 477:
#line 3201 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 9909 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 478:
#line 3204 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9915 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 479:
#line 3206 "parser_bison.y" /* yacc.c:1652  */
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
#line 9932 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 480:
#line 3221 "parser_bison.y" /* yacc.c:1652  */
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
#line 9952 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 481:
#line 3237 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 9962 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 482:
#line 3244 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 9968 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 483:
#line 3245 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9974 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 484:
#line 3246 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 9980 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 485:
#line 3249 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 5; }
#line 9986 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 486:
#line 3250 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 9992 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 487:
#line 3253 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 5; }
#line 9998 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 488:
#line 3254 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 10004 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 489:
#line 3256 "parser_bison.y" /* yacc.c:1652  */
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
#line 10021 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 490:
#line 3270 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL; }
#line 10027 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 491:
#line 3271 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60; }
#line 10033 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 492:
#line 3272 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 10039 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 493:
#line 3273 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 10045 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 494:
#line 3274 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 10051 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 496:
#line 3281 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 10059 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 497:
#line 3287 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state), (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10069 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 498:
#line 3292 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10075 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 499:
#line 3296 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 10084 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 500:
#line 3301 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmp_code_type);
			}
#line 10095 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 501:
#line 3308 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmp_code_type);
			}
#line 10106 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 502:
#line 3315 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 10117 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 503:
#line 3322 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpv6_code_type);
			}
#line 10128 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 504:
#line 3329 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpx_code_type);
			}
#line 10138 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 505:
#line 3335 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-3].stmt)->reject.expr = (yyvsp[0].expr);
				datatype_set((yyvsp[-3].stmt)->reject.expr, &icmpx_code_type);
			}
#line 10148 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 506:
#line 3341 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 10156 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 508:
#line 3349 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 10162 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 509:
#line 3350 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 10168 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 510:
#line 3354 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 10178 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 511:
#line 3360 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 10188 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 512:
#line 3366 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 10198 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 513:
#line 3372 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 10209 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 514:
#line 3379 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 10220 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 515:
#line 3386 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 10230 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 518:
#line 3398 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 10238 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 519:
#line 3402 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_SYNPROXY;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 10248 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 520:
#line 3410 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10256 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 522:
#line 3417 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 10265 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 523:
#line 3422 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 10274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 524:
#line 3427 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 10282 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 525:
#line 3431 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 10290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 526:
#line 3437 "parser_bison.y" /* yacc.c:1652  */
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
#line 10310 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 527:
#line 3453 "parser_bison.y" /* yacc.c:1652  */
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
#line 10330 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 528:
#line 3471 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SYNPROXY;
			}
#line 10339 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 529:
#line 3477 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 10345 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 530:
#line 3479 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 10353 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 531:
#line 3484 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 10359 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 532:
#line 3486 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 10367 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 533:
#line 3491 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 534:
#line 3492 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10379 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 535:
#line 3493 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 536:
#line 3494 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 537:
#line 3495 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10397 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 538:
#line 3496 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10403 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 539:
#line 3497 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 540:
#line 3498 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10415 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 541:
#line 3499 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10421 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 542:
#line 3500 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10427 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 543:
#line 3501 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 544:
#line 3502 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10439 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 545:
#line 3503 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 10445 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 547:
#line 3508 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 548:
#line 3512 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10461 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 550:
#line 3519 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10469 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 552:
#line 3526 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10477 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 554:
#line 3533 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 557:
#line 3543 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 10498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 560:
#line 3558 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10506 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 561:
#line 3561 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10512 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 562:
#line 3565 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 10520 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 563:
#line 3571 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 569:
#line 3586 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10536 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 570:
#line 3590 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10544 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 571:
#line 3594 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10553 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 572:
#line 3599 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10562 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 573:
#line 3604 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10571 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 574:
#line 3609 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10581 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 575:
#line 3615 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10589 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 576:
#line 3619 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10597 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 577:
#line 3623 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10605 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 578:
#line 3627 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-6].stmt)->nat.family = (yyvsp[-5].val);
				(yyvsp[-6].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-6].stmt)->nat.type_flags = STMT_NAT_F_CONCAT;
			}
#line 10615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 579:
#line 3633 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 580:
#line 3638 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 10632 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 581:
#line 3642 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.family = (yyvsp[-3].val);
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-4].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-4].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 10644 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 582:
#line 3650 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
				(yyvsp[-3].stmt)->nat.type_flags =
						STMT_NAT_F_PREFIX;
				(yyvsp[-3].stmt)->nat.flags |= NF_NAT_RANGE_NETMAP;
			}
#line 10655 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 585:
#line 3662 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 10661 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 586:
#line 3666 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10669 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 587:
#line 3670 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10678 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 588:
#line 3675 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10686 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 591:
#line 3684 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 10692 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 592:
#line 3688 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10700 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 593:
#line 3692 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 10708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 594:
#line 3696 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 595:
#line 3700 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10725 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 596:
#line 3705 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 10734 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 597:
#line 3712 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 10743 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 598:
#line 3717 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 10753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 599:
#line 3725 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 10762 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 600:
#line 3730 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 10773 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 602:
#line 3740 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10781 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 603:
#line 3745 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 10787 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 604:
#line 3746 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 10793 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 605:
#line 3747 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 10799 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 607:
#line 3752 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), 0);
			}
#line 10807 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 608:
#line 3756 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 10815 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 609:
#line 3760 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), (yyvsp[-1].expr), (yyvsp[-3].val));
			}
#line 10823 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 612:
#line 3770 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc), NULL, 0);
			}
#line 10831 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 613:
#line 3776 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10839 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 615:
#line 3783 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 10848 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 616:
#line 3788 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 10856 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 623:
#line 3804 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 10864 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 624:
#line 3809 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 10870 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 625:
#line 3810 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 10876 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 628:
#line 3818 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 10884 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 629:
#line 3824 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 10895 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 630:
#line 3831 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 10906 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 631:
#line 3838 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				list_splice_tail((yyvsp[-1].list), &(yyval.stmt)->set.stmt_list);
				free((yyvsp[-1].list));
			}
#line 10919 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 632:
#line 3848 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 10925 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 633:
#line 3849 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 10931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 634:
#line 3850 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_DELETE; }
#line 10937 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 635:
#line 3854 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 10949 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 636:
#line 3862 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
				list_splice_tail((yyvsp[-3].list), &(yyval.stmt)->map.stmt_list);
				free((yyvsp[-3].list));
			}
#line 10963 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 637:
#line 3874 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 10974 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 638:
#line 3880 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 10980 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 639:
#line 3884 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 10988 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 640:
#line 3890 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 10996 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 642:
#line 3897 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 11004 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 643:
#line 3903 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 11017 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 644:
#line 3912 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 11030 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 645:
#line 3923 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 11038 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 646:
#line 3929 "parser_bison.y" /* yacc.c:1652  */
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
#line 11066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 648:
#line 3956 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 11077 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 651:
#line 3969 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 11088 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 652:
#line 3978 "parser_bison.y" /* yacc.c:1652  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 11101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 653:
#line 3988 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 654:
#line 3989 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11113 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 655:
#line 3990 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11119 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 656:
#line 3991 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11125 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 657:
#line 3992 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11131 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 658:
#line 3993 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11137 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 659:
#line 3994 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11143 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 660:
#line 3995 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11149 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 661:
#line 3996 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11155 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 662:
#line 3997 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 663:
#line 3998 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 664:
#line 3999 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11173 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 665:
#line 4000 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 666:
#line 4001 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11185 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 667:
#line 4002 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 11191 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 668:
#line 4006 "parser_bison.y" /* yacc.c:1652  */
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
#line 11216 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 669:
#line 4028 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 11222 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 670:
#line 4029 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 11228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 671:
#line 4030 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 11234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 672:
#line 4033 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 11240 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 673:
#line 4034 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 11246 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 674:
#line 4035 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 11252 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 675:
#line 4036 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 11258 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 676:
#line 4037 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 11264 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 677:
#line 4041 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 11272 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 679:
#line 4048 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), NFT_OSF_F_VERSION);
			}
#line 11280 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 680:
#line 4052 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 11288 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 681:
#line 4058 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 11296 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 682:
#line 4062 "parser_bison.y" /* yacc.c:1652  */
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
#line 11314 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 684:
#line 4079 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11322 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 685:
#line 4083 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11330 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 687:
#line 4090 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11338 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 689:
#line 4097 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11346 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 691:
#line 4104 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11354 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 694:
#line 4114 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 11367 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 695:
#line 4125 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 11375 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 696:
#line 4131 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11383 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 699:
#line 4141 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 703:
#line 4152 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11400 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 704:
#line 4159 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 705:
#line 4164 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11418 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 707:
#line 4172 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11426 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 708:
#line 4176 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11434 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 709:
#line 4180 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 11442 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 711:
#line 4187 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 11451 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 712:
#line 4194 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 11459 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 715:
#line 4203 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 11465 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 716:
#line 4204 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = set_elem_catchall_expr_alloc(&(yylsp[0])); }
#line 11471 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 717:
#line 4208 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[-1]), (yyvsp[-1].expr));
				list_splice_tail((yyvsp[0].list), &(yyval.expr)->stmt_list);
				xfree((yyvsp[0].list));
			}
#line 11481 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 718:
#line 4214 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 11489 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 719:
#line 4220 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 11497 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 721:
#line 4227 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 11505 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 722:
#line 4231 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 11513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 723:
#line 4235 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 11525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 724:
#line 4245 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 11533 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 726:
#line 4252 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 11543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 727:
#line 4258 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 11552 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 728:
#line 4265 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 11560 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 729:
#line 4269 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
				(yyval.stmt)->counter.packets = (yyvsp[-3].val);
				(yyval.stmt)->counter.bytes = (yyvsp[-1].val);
			}
#line 11570 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 730:
#line 4275 "parser_bison.y" /* yacc.c:1652  */
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
#line 11588 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 731:
#line 4289 "parser_bison.y" /* yacc.c:1652  */
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
#line 11616 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 732:
#line 4313 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[-1].val);
			}
#line 11625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 733:
#line 4318 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[-1].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 11635 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 734:
#line 4326 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 11643 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 735:
#line 4330 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 11651 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 736:
#line 4334 "parser_bison.y" /* yacc.c:1652  */
    {
				if (already_set((yyvsp[-1].expr)->comment, &(yylsp[0]), state)) {
					xfree((yyvsp[0].string));
					YYERROR;
				}
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 11663 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 742:
#line 4352 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_SET); }
#line 11669 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 743:
#line 4354 "parser_bison.y" /* yacc.c:1652  */
    {
				int32_t num = -(yyvsp[0].val);

				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(num) * BITS_PER_BYTE,
							 &num);
			}
#line 11682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 744:
#line 4365 "parser_bison.y" /* yacc.c:1652  */
    {
				struct counter *counter;

				counter = &(yyvsp[-4].obj)->counter;
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
			}
#line 11694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 745:
#line 4375 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
			}
#line 11703 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 746:
#line 4382 "parser_bison.y" /* yacc.c:1652  */
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
#line 11725 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 747:
#line 4402 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
			}
#line 11734 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 748:
#line 4409 "parser_bison.y" /* yacc.c:1652  */
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
#line 11752 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 749:
#line 4425 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
			}
#line 11761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 750:
#line 4431 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 11767 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 751:
#line 4432 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 11773 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 752:
#line 4433 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 11779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 753:
#line 4436 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_OBJ_CT_HELPERS; }
#line 11785 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 754:
#line 4437 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_OBJ_CT_TIMEOUT; }
#line 11791 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 755:
#line 4438 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_OBJ_CT_EXPECT; }
#line 11797 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 756:
#line 4441 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_TCP; }
#line 11803 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 757:
#line 4442 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_UDP; }
#line 11809 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 758:
#line 4446 "parser_bison.y" /* yacc.c:1652  */
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
#line 11829 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 759:
#line 4462 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 11837 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 760:
#line 4468 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 11847 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 761:
#line 4474 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 11856 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 762:
#line 4482 "parser_bison.y" /* yacc.c:1652  */
    {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 11871 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 763:
#line 4495 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 11883 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 764:
#line 4503 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;

				ct = &(yyvsp[-6].obj)->ct_timeout;
				list_splice_tail((yyvsp[-2].list), &ct->timeout_list);
				xfree((yyvsp[-2].list));
			}
#line 11895 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 765:
#line 4511 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 11903 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 766:
#line 4517 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 11911 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 767:
#line 4521 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 11919 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 768:
#line 4525 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 11927 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 769:
#line 4529 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 11935 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 770:
#line 4533 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 11943 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 771:
#line 4539 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 11951 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 772:
#line 4545 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;

				limit = &(yyvsp[-6].obj)->limit;
				limit->rate	= (yyvsp[-3].val);
				limit->unit	= (yyvsp[-1].val);
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-4].val);
			}
#line 11966 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 773:
#line 4556 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;
				struct error_record *erec;
				uint64_t rate, unit;

				erec = rate_parse(&(yyloc), (yyvsp[-1].string), &rate, &unit);
				xfree((yyvsp[-1].string));
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
#line 11990 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 774:
#line 4578 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
			}
#line 11999 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 775:
#line 4585 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 12007 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 776:
#line 4589 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 12015 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 777:
#line 4593 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 12023 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 778:
#line 4597 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), OP_EQ, (yyvsp[-3].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 12031 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 779:
#line 4601 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 12039 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 780:
#line 4605 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = flagcmp_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[0].expr), (yyvsp[-2].expr));
			}
#line 12047 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 781:
#line 4609 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12055 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 782:
#line 4613 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12063 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 783:
#line 4619 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 12073 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 784:
#line 4625 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 12083 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 785:
#line 4632 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12089 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 786:
#line 4633 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12095 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 787:
#line 4634 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 789:
#line 4639 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12109 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 790:
#line 4643 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12117 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 792:
#line 4650 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12125 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 794:
#line 4657 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12133 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 796:
#line 4664 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 12141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 800:
#line 4675 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 12154 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 801:
#line 4684 "parser_bison.y" /* yacc.c:1652  */
    {
				struct location rhs[] = {
					[1]	= (yylsp[-1]),
					[2]	= (yylsp[0]),
				};

				(yyval.expr) = handle_concat_expr(&(yyloc), (yyval.expr), (yyvsp[-2].expr), (yyvsp[0].expr), rhs);
			}
#line 12167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 802:
#line 4694 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = true; }
#line 12173 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 803:
#line 4695 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val8) = false; }
#line 12179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 804:
#line 4699 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof((yyvsp[0].val8)) * BITS_PER_BYTE, &(yyvsp[0].val8));
			}
#line 12189 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 805:
#line 4706 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 12195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 806:
#line 4707 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 12201 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 807:
#line 4708 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 12207 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 808:
#line 4709 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 12213 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 809:
#line 4710 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 12219 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 810:
#line 4711 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 12225 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 811:
#line 4712 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 12231 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 812:
#line 4713 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 12237 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 813:
#line 4714 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 12243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 814:
#line 4715 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 12249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 815:
#line 4716 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 12255 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 816:
#line 4717 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 12261 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 817:
#line 4720 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12267 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 818:
#line 4721 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12273 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 819:
#line 4722 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 820:
#line 4723 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 12285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 821:
#line 4725 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12296 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 822:
#line 4732 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12307 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 823:
#line 4739 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12318 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 824:
#line 4746 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12329 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 825:
#line 4753 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 826:
#line 4760 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12351 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 827:
#line 4767 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12362 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 828:
#line 4774 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 829:
#line 4781 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 830:
#line 4788 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12395 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 831:
#line 4795 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12406 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 832:
#line 4802 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 12417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 833:
#line 4808 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 12423 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 834:
#line 4811 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_EQ; }
#line 12429 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 835:
#line 4812 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_NEQ; }
#line 12435 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 836:
#line 4813 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LT; }
#line 12441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 837:
#line 4814 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GT; }
#line 12447 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 838:
#line 4815 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GTE; }
#line 12453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 839:
#line 4816 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LTE; }
#line 12459 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 840:
#line 4817 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_NEG; }
#line 12465 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 841:
#line 4821 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 12473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 842:
#line 4825 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 12481 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 843:
#line 4829 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 12489 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 844:
#line 4833 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 12497 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 845:
#line 4837 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 12505 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 846:
#line 4841 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 12513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 848:
#line 4848 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 12525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 849:
#line 4858 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 12533 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 850:
#line 4862 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 12541 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 851:
#line 4866 "parser_bison.y" /* yacc.c:1652  */
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
#line 12559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 854:
#line 4885 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_LEN; }
#line 12565 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 855:
#line 4886 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 12571 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 856:
#line 4887 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 12577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 857:
#line 4888 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 12583 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 858:
#line 4889 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECMARK; }
#line 12589 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 859:
#line 4892 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_MARK; }
#line 12595 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 860:
#line 4893 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIF; }
#line 12601 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 861:
#line 4894 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 12607 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 862:
#line 4895 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 12613 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 863:
#line 4896 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIF; }
#line 12619 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 864:
#line 4897 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 12625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 865:
#line 4898 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 12631 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 866:
#line 4899 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKUID; }
#line 12637 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 867:
#line 4900 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKGID; }
#line 12643 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 868:
#line 4901 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 12649 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 869:
#line 4902 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 12655 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 870:
#line 4903 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 12661 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 871:
#line 4904 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 12667 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 872:
#line 4905 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 12673 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 873:
#line 4906 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 12679 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 874:
#line 4907 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 12685 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 875:
#line 4908 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CPU; }
#line 12691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 876:
#line 4909 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 12697 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 877:
#line 4910 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 12703 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 878:
#line 4911 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 12709 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 879:
#line 4912 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECPATH; }
#line 12715 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 880:
#line 4913 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_NS; }
#line 12721 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 881:
#line 4914 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_DAY; }
#line 12727 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 882:
#line 4915 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_TIME_HOUR; }
#line 12733 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 883:
#line 4919 "parser_bison.y" /* yacc.c:1652  */
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
#line 12757 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 884:
#line 4939 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 12765 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 885:
#line 4943 "parser_bison.y" /* yacc.c:1652  */
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
#line 12783 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 886:
#line 4957 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 12791 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 887:
#line 4961 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 12799 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 888:
#line 4965 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 12807 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 889:
#line 4971 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 12815 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 890:
#line 4975 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), NFT_SOCKET_CGROUPV2, (yyvsp[-1].val));
			}
#line 12823 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 891:
#line 4980 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 12829 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 892:
#line 4981 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_MARK; }
#line 12835 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 893:
#line 4982 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_WILDCARD; }
#line 12841 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 894:
#line 4985 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 12847 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 895:
#line 4986 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 12853 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 896:
#line 4989 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 12859 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 897:
#line 4990 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 12865 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 898:
#line 4994 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 12873 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 899:
#line 4999 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 12879 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 900:
#line 5000 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 12885 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 901:
#line 5003 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_IN; }
#line 12891 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 902:
#line 5004 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_OUT; }
#line 12897 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 903:
#line 5007 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 12903 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 904:
#line 5008 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 12909 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 905:
#line 5011 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 12915 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 906:
#line 5012 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 12921 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 907:
#line 5016 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].val) > 255) {
					erec_queue(error(&(yylsp[-2]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 12933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 908:
#line 5024 "parser_bison.y" /* yacc.c:1652  */
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
#line 12962 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 909:
#line 5051 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-4].val), true, (yyvsp[-2].val), (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-6].expr);
			}
#line 12971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 910:
#line 5056 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-4].expr);
			}
#line 12980 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 911:
#line 5061 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-2].val), false, 0, (yyvsp[-1].val), NFT_HASH_SYM);
			}
#line 12988 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 912:
#line 5066 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 12994 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 913:
#line 5067 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 13000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 914:
#line 5071 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[-1].val), true);
			}
#line 13008 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 915:
#line 5075 "parser_bison.y" /* yacc.c:1652  */
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
#line 13030 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 916:
#line 5094 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 13036 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 917:
#line 5095 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 13042 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 918:
#line 5096 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 13048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 919:
#line 5097 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_XFRM; }
#line 13054 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 920:
#line 5101 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), -1);
			}
#line 13062 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 921:
#line 5105 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 13070 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 922:
#line 5109 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[-2].val));
			}
#line 13078 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 923:
#line 5114 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 13084 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 924:
#line 5115 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 13090 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 925:
#line 5118 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 13096 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 926:
#line 5119 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 13102 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 927:
#line 5120 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_MARK; }
#line 13108 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 928:
#line 5121 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATE; }
#line 13114 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 929:
#line 5122 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 13120 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 930:
#line 5123 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 13126 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 931:
#line 5124 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 13132 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 932:
#line 5125 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 13138 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 933:
#line 5126 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 13144 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 934:
#line 5127 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 13150 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 935:
#line 5128 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 13156 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 936:
#line 5129 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 13162 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 937:
#line 5130 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 13168 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 938:
#line 5131 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 13174 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 939:
#line 5132 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SECMARK; }
#line 13180 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 940:
#line 5133 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ID; }
#line 13186 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 942:
#line 5137 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 13192 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 943:
#line 5138 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 13198 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 944:
#line 5139 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 13204 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 945:
#line 5140 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 13210 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 946:
#line 5141 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 13216 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 947:
#line 5142 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 13222 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 949:
#line 5146 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP; }
#line 13228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 950:
#line 5147 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP; }
#line 13234 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 951:
#line 5148 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP6; }
#line 13240 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 952:
#line 5149 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP6; }
#line 13246 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 953:
#line 5152 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 13252 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 954:
#line 5153 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 13258 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 955:
#line 5154 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 13264 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 956:
#line 5155 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 13270 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 959:
#line 5163 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 13280 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 960:
#line 5169 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 13290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 961:
#line 5177 "parser_bison.y" /* yacc.c:1652  */
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
#line 13307 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 962:
#line 5190 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);

			}
#line 13318 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 963:
#line 5197 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[-1].expr);
			}
#line 13328 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 964:
#line 5203 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-4].val), (yyvsp[-1].expr));
			}
#line 13336 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 965:
#line 5209 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 13347 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 984:
#line 5238 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 13358 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 985:
#line 5246 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 13364 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 986:
#line 5247 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 13370 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 987:
#line 5248 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 13376 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 988:
#line 5252 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[-1].val));
			}
#line 13384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 989:
#line 5257 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 13390 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 990:
#line 5258 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 13396 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 991:
#line 5259 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 13402 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 992:
#line 5263 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[-1].val));
			}
#line 13410 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 993:
#line 5268 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_VID; }
#line 13416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 994:
#line 5269 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_CFI; }
#line 13422 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 995:
#line 5270 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_DEI; }
#line 13428 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 996:
#line 5271 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_PCP; }
#line 13434 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 997:
#line 5272 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 13440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 998:
#line 5276 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[-1].val));
			}
#line 13448 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 999:
#line 5281 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HRD; }
#line 13454 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1000:
#line 5282 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PRO; }
#line 13460 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1001:
#line 5283 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HLN; }
#line 13466 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1002:
#line 5284 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PLN; }
#line 13472 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1003:
#line 5285 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_OP; }
#line 13478 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1004:
#line 5286 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 13484 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1005:
#line 5287 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 13490 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1006:
#line 5288 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_IP; }
#line 13496 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1007:
#line 5289 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_IP; }
#line 13502 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1008:
#line 5293 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[-1].val));
			}
#line 13510 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1009:
#line 5297 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val), 0);
			}
#line 13518 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1010:
#line 5301 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), IPOPT_FIELD_TYPE, 0);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 13527 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1011:
#line 5307 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_VERSION; }
#line 13533 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1012:
#line 5308 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 13539 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1013:
#line 5309 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DSCP; }
#line 13545 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1014:
#line 5310 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ECN; }
#line 13551 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1015:
#line 5311 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 13557 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1016:
#line 5312 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ID; }
#line 13563 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1017:
#line 5313 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 13569 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1018:
#line 5314 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_TTL; }
#line 13575 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1019:
#line 5315 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 13581 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1020:
#line 5316 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 13587 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1021:
#line 5317 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_SADDR; }
#line 13593 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1022:
#line 5318 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DADDR; }
#line 13599 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1023:
#line 5321 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_LSRR; }
#line 13605 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1024:
#line 5322 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RR; }
#line 13611 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1025:
#line 5323 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_SSRR; }
#line 13617 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1026:
#line 5324 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RA; }
#line 13623 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1027:
#line 5327 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 13629 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1028:
#line 5328 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 13635 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1029:
#line 5329 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 13641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1030:
#line 5330 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_PTR; }
#line 13647 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1031:
#line 5331 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 13653 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1032:
#line 5335 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 13661 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1033:
#line 5340 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 13667 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1034:
#line 5341 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 13673 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1035:
#line 5342 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 13679 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1036:
#line 5343 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_ID; }
#line 13685 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1037:
#line 5344 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 13691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1038:
#line 5345 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 13697 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1039:
#line 5346 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 13703 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1040:
#line 5350 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[0].val));
			}
#line 13711 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1041:
#line 5355 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_TYPE; }
#line 13717 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1042:
#line 5356 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 13723 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1043:
#line 5357 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_MRT; }
#line 13729 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1044:
#line 5358 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_GROUP; }
#line 13735 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1045:
#line 5362 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[-1].val));
			}
#line 13743 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1046:
#line 5367 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 13749 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1047:
#line 5368 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 13755 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1048:
#line 5369 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_ECN; }
#line 13761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1049:
#line 5370 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 13767 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1050:
#line 5371 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 13773 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1051:
#line 5372 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 13779 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1052:
#line 5373 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 13785 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1053:
#line 5374 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 13791 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1054:
#line 5375 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 13797 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1055:
#line 5378 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 13805 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1056:
#line 5383 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 13811 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1057:
#line 5384 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 13817 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1058:
#line 5385 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 13823 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1059:
#line 5386 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 13829 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1060:
#line 5387 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 13835 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1061:
#line 5388 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 13841 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1062:
#line 5389 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 13847 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1063:
#line 5390 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 13853 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1064:
#line 5394 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 13861 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1065:
#line 5399 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 13867 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1066:
#line 5400 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 13873 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1067:
#line 5401 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 13879 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1068:
#line 5402 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SPI; }
#line 13885 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1069:
#line 5403 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 13891 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1070:
#line 5407 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 13899 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1071:
#line 5412 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SPI; }
#line 13905 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1072:
#line 5413 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 13911 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1073:
#line 5417 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 13919 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1074:
#line 5422 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 13925 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1075:
#line 5423 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 13931 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1076:
#line 5424 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_CPI; }
#line 13937 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1077:
#line 5428 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 13945 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1078:
#line 5433 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 13951 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1079:
#line 5434 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 13957 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1080:
#line 5435 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 13963 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1081:
#line 5436 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 13969 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1082:
#line 5440 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 13977 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1083:
#line 5445 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 13983 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1084:
#line 5446 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 13989 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1085:
#line 5447 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 13995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1086:
#line 5448 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 14001 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1087:
#line 5452 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 14009 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1088:
#line 5456 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 14017 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1089:
#line 5460 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPT_COMMON_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 14026 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1090:
#line 5465 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-4].val), 0);
				tcpopt_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val), 0);
			}
#line 14035 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1091:
#line 5471 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 14041 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1092:
#line 5472 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 14047 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1093:
#line 5473 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 14053 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1094:
#line 5474 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 14059 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1095:
#line 5475 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 14065 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1096:
#line 5476 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 14071 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1097:
#line 5477 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 14077 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1098:
#line 5478 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 14083 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1099:
#line 5479 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 14089 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1100:
#line 5480 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 14095 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1101:
#line 5483 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_EOL; }
#line 14101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1102:
#line 5484 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_NOP; }
#line 14107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1103:
#line 5485 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_MAXSEG; }
#line 14113 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1104:
#line 5486 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_WINDOW; }
#line 14119 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1105:
#line 5487 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK_PERMITTED; }
#line 14125 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1106:
#line 5488 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK; }
#line 14131 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1107:
#line 5489 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK; }
#line 14137 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1108:
#line 5490 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK1; }
#line 14143 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1109:
#line 5491 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK2; }
#line 14149 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1110:
#line 5492 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_SACK3; }
#line 14155 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1111:
#line 5493 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_ECHO; }
#line 14161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1112:
#line 5494 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_KIND_TIMESTAMP; }
#line 14167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1113:
#line 5495 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].val) > 255) {
					erec_queue(error(&(yylsp[0]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[0].val);
			}
#line 14179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1114:
#line 5504 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_COMMON_KIND; }
#line 14185 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1115:
#line 5505 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_COMMON_LENGTH; }
#line 14191 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1116:
#line 5506 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_MAXSEG_SIZE; }
#line 14197 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1117:
#line 5507 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_WINDOW_COUNT; }
#line 14203 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1118:
#line 5508 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_SACK_LEFT; }
#line 14209 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1119:
#line 5509 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_SACK_RIGHT; }
#line 14215 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1120:
#line 5510 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_TS_TSVAL; }
#line 14221 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1121:
#line 5511 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPT_TS_TSECR; }
#line 14227 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1122:
#line 5515 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 14235 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1123:
#line 5520 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 14241 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1124:
#line 5521 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 14247 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1125:
#line 5522 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 14253 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1126:
#line 5525 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_DATA; }
#line 14259 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1127:
#line 5526 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_INIT; }
#line 14265 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1128:
#line 5527 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_INIT_ACK; }
#line 14271 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1129:
#line 5528 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_SACK; }
#line 14277 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1130:
#line 5529 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT; }
#line 14283 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1131:
#line 5530 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_HEARTBEAT_ACK; }
#line 14289 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1132:
#line 5531 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_ABORT; }
#line 14295 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1133:
#line 5532 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN; }
#line 14301 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1134:
#line 5533 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_ACK; }
#line 14307 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1135:
#line 5534 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_ERROR; }
#line 14313 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1136:
#line 5535 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ECHO; }
#line 14319 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1137:
#line 5536 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_COOKIE_ACK; }
#line 14325 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1138:
#line 5537 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_ECNE; }
#line 14331 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1139:
#line 5538 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_CWR; }
#line 14337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1140:
#line 5539 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_SHUTDOWN_COMPLETE; }
#line 14343 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1141:
#line 5540 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF_ACK; }
#line 14349 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1142:
#line 5541 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_FORWARD_TSN; }
#line 14355 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1143:
#line 5542 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_TYPE_ASCONF; }
#line 14361 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1144:
#line 5545 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_COMMON_TYPE; }
#line 14367 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1145:
#line 5546 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_COMMON_FLAGS; }
#line 14373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1146:
#line 5547 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_COMMON_LENGTH; }
#line 14379 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1147:
#line 5550 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_DATA_TSN; }
#line 14385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1148:
#line 5551 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_DATA_STREAM; }
#line 14391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1149:
#line 5552 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_DATA_SSN; }
#line 14397 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1150:
#line 5553 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_DATA_PPID; }
#line 14403 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1151:
#line 5556 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_INIT_TAG; }
#line 14409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1152:
#line 5557 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_INIT_RWND; }
#line 14415 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1153:
#line 5558 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_INIT_OSTREAMS; }
#line 14421 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1154:
#line 5559 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_INIT_ISTREAMS; }
#line 14427 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1155:
#line 5560 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_INIT_TSN; }
#line 14433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1156:
#line 5563 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_SACK_CTSN_ACK; }
#line 14439 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1157:
#line 5564 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_SACK_RWND; }
#line 14445 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1158:
#line 5565 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_SACK_GACK_BLOCKS; }
#line 14451 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1159:
#line 5566 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTP_CHUNK_SACK_DUP_TSNS; }
#line 14457 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1160:
#line 5570 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[0].val), SCTP_CHUNK_COMMON_TYPE);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 14466 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1161:
#line 5575 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 14474 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1162:
#line 5579 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_DATA, (yyvsp[0].val));
			}
#line 14482 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1163:
#line 5583 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT, (yyvsp[0].val));
			}
#line 14490 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1164:
#line 5587 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_INIT_ACK, (yyvsp[0].val));
			}
#line 14498 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1165:
#line 5591 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SACK, (yyvsp[0].val));
			}
#line 14506 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1166:
#line 5595 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_SHUTDOWN,
							   SCTP_CHUNK_SHUTDOWN_CTSN_ACK);
			}
#line 14515 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1167:
#line 5600 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ECNE,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 14524 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1168:
#line 5605 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_CWR,
							   SCTP_CHUNK_ECNE_CWR_MIN_TSN);
			}
#line 14533 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1169:
#line 5610 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF_ACK,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 14542 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1170:
#line 5615 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_FORWARD_TSN,
							   SCTP_CHUNK_FORWARD_TSN_NCTSN);
			}
#line 14551 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1171:
#line 5620 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = sctp_chunk_expr_alloc(&(yyloc), SCTP_CHUNK_TYPE_ASCONF,
							   SCTP_CHUNK_ASCONF_SEQNO);
			}
#line 14560 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1172:
#line 5627 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[-1].val));
			}
#line 14568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1173:
#line 5631 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 14576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1174:
#line 5636 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 14582 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1175:
#line 5637 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 14588 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1176:
#line 5638 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 14594 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1177:
#line 5639 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 14600 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1178:
#line 5643 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[0].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 14610 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1179:
#line 5650 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_SPORT; }
#line 14616 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1180:
#line 5651 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_DPORT; }
#line 14622 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1189:
#line 5665 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 14630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1190:
#line 5670 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 14636 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1191:
#line 5671 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 14642 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1192:
#line 5675 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[-1].val));
			}
#line 14650 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1193:
#line 5680 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 14656 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1194:
#line 5681 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 14662 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1195:
#line 5682 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_TYPE; }
#line 14668 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1196:
#line 5683 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 14674 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1197:
#line 5687 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 14682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1198:
#line 5693 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 14690 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1199:
#line 5699 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 14698 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1200:
#line 5704 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 14704 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1201:
#line 5708 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 14712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1202:
#line 5713 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 14718 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1203:
#line 5714 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 14724 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1204:
#line 5715 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_TAG; }
#line 14730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1205:
#line 5717 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 14738 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1206:
#line 5723 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 14746 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1207:
#line 5728 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 14752 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1208:
#line 5729 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 14758 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1209:
#line 5730 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 14764 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1210:
#line 5731 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 14770 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1211:
#line 5732 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 14776 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1212:
#line 5733 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_ID; }
#line 14782 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1213:
#line 5737 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 14790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1214:
#line 5742 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 14796 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1215:
#line 5743 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 14802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1216:
#line 5747 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 14810 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1217:
#line 5752 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 14816 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1218:
#line 5753 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 14822 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1219:
#line 5754 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_TYPE; }
#line 14828 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1220:
#line 5755 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 14834 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1221:
#line 5756 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 14840 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1222:
#line 5760 "parser_bison.y" /* yacc.c:1652  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 14856 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1223:
#line 5773 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 14862 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1224:
#line 5774 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 14868 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1225:
#line 5775 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 14874 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1226:
#line 5776 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 14880 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1227:
#line 5777 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_MH; }
#line 14886 "parser_bison.c" /* yacc.c:1652  */
    break;


#line 14890 "parser_bison.c" /* yacc.c:1652  */
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
#line 5780 "parser_bison.y" /* yacc.c:1918  */

