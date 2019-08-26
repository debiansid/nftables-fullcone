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
		 struct list_head *msgs, struct list_head *cmds)
{
	memset(state, 0, sizeof(*state));
	init_list_head(&state->top_scope.symbols);
	state->msgs = msgs;
	state->cmds = cmds;
	state->scopes[0] = scope_init(&state->top_scope, NULL);
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
    CLASSID = 482,
    NEXTHOP = 483,
    CT = 484,
    L3PROTOCOL = 485,
    PROTO_SRC = 486,
    PROTO_DST = 487,
    ZONE = 488,
    DIRECTION = 489,
    EVENT = 490,
    EXPECTATION = 491,
    EXPIRATION = 492,
    HELPER = 493,
    LABEL = 494,
    STATE = 495,
    STATUS = 496,
    ORIGINAL = 497,
    REPLY = 498,
    COUNTER = 499,
    NAME = 500,
    PACKETS = 501,
    BYTES = 502,
    AVGPKT = 503,
    COUNTERS = 504,
    QUOTAS = 505,
    LIMITS = 506,
    HELPERS = 507,
    LOG = 508,
    PREFIX = 509,
    GROUP = 510,
    SNAPLEN = 511,
    QUEUE_THRESHOLD = 512,
    LEVEL = 513,
    LIMIT = 514,
    RATE = 515,
    BURST = 516,
    OVER = 517,
    UNTIL = 518,
    QUOTA = 519,
    USED = 520,
    SECMARK = 521,
    SECMARKS = 522,
    NANOSECOND = 523,
    MICROSECOND = 524,
    MILLISECOND = 525,
    SECOND = 526,
    MINUTE = 527,
    HOUR = 528,
    DAY = 529,
    WEEK = 530,
    _REJECT = 531,
    WITH = 532,
    ICMPX = 533,
    SNAT = 534,
    DNAT = 535,
    MASQUERADE = 536,
    REDIRECT = 537,
    RANDOM = 538,
    FULLY_RANDOM = 539,
    PERSISTENT = 540,
    QUEUE = 541,
    QUEUENUM = 542,
    BYPASS = 543,
    FANOUT = 544,
    DUP = 545,
    FWD = 546,
    NUMGEN = 547,
    INC = 548,
    MOD = 549,
    OFFSET = 550,
    JHASH = 551,
    SYMHASH = 552,
    SEED = 553,
    POSITION = 554,
    INDEX = 555,
    COMMENT = 556,
    XML = 557,
    JSON = 558,
    VM = 559,
    NOTRACK = 560,
    EXISTS = 561,
    MISSING = 562,
    EXTHDR = 563,
    IPSEC = 564,
    MODE = 565,
    REQID = 566,
    SPNUM = 567,
    TRANSPORT = 568,
    TUNNEL = 569,
    IN = 570,
    OUT = 571
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
#define CLASSID 482
#define NEXTHOP 483
#define CT 484
#define L3PROTOCOL 485
#define PROTO_SRC 486
#define PROTO_DST 487
#define ZONE 488
#define DIRECTION 489
#define EVENT 490
#define EXPECTATION 491
#define EXPIRATION 492
#define HELPER 493
#define LABEL 494
#define STATE 495
#define STATUS 496
#define ORIGINAL 497
#define REPLY 498
#define COUNTER 499
#define NAME 500
#define PACKETS 501
#define BYTES 502
#define AVGPKT 503
#define COUNTERS 504
#define QUOTAS 505
#define LIMITS 506
#define HELPERS 507
#define LOG 508
#define PREFIX 509
#define GROUP 510
#define SNAPLEN 511
#define QUEUE_THRESHOLD 512
#define LEVEL 513
#define LIMIT 514
#define RATE 515
#define BURST 516
#define OVER 517
#define UNTIL 518
#define QUOTA 519
#define USED 520
#define SECMARK 521
#define SECMARKS 522
#define NANOSECOND 523
#define MICROSECOND 524
#define MILLISECOND 525
#define SECOND 526
#define MINUTE 527
#define HOUR 528
#define DAY 529
#define WEEK 530
#define _REJECT 531
#define WITH 532
#define ICMPX 533
#define SNAT 534
#define DNAT 535
#define MASQUERADE 536
#define REDIRECT 537
#define RANDOM 538
#define FULLY_RANDOM 539
#define PERSISTENT 540
#define QUEUE 541
#define QUEUENUM 542
#define BYPASS 543
#define FANOUT 544
#define DUP 545
#define FWD 546
#define NUMGEN 547
#define INC 548
#define MOD 549
#define OFFSET 550
#define JHASH 551
#define SYMHASH 552
#define SEED 553
#define POSITION 554
#define INDEX 555
#define COMMENT 556
#define XML 557
#define JSON 558
#define VM 559
#define NOTRACK 560
#define EXISTS 561
#define MISSING 562
#define EXTHDR 563
#define IPSEC 564
#define MODE 565
#define REQID 566
#define SPNUM 567
#define TRANSPORT 568
#define TUNNEL 569
#define IN 570
#define OUT 571

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 135 "parser_bison.y" /* yacc.c:352  */

	uint64_t		val;
	uint32_t		val32;
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
	struct counter		*counter;
	struct quota		*quota;
	struct secmark		*secmark;
	struct ct		*ct;
	struct limit		*limit;
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;
	struct prio_spec	prio_spec;
	const struct exthdr_desc *exthdr_desc;

#line 885 "parser_bison.c" /* yacc.c:352  */
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
#define YYLAST   5712

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  326
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  327
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1029
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1653

#define YYUNDEFTOK  2
#define YYMAXUTOK   571

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
       2,     2,     2,     2,     2,     2,   321,     2,     2,     2,
     322,   323,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   317,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   324,     2,   325,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   318,   320,   319,     2,     2,     2,     2,
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
     315,   316
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   814,   814,   815,   824,   825,   828,   829,   832,   840,
     854,   861,   872,   880,   881,   882,   883,   903,   904,   905,
     906,   907,   908,   909,   910,   911,   912,   913,   914,   915,
     916,   917,   920,   924,   931,   935,   943,   947,   951,   958,
     965,   969,   976,   985,   989,   993,   998,  1002,  1006,  1010,
    1016,  1022,  1026,  1033,  1037,  1045,  1052,  1059,  1063,  1070,
    1079,  1083,  1087,  1091,  1095,  1099,  1103,  1109,  1115,  1119,
    1123,  1127,  1131,  1135,  1139,  1143,  1147,  1151,  1155,  1159,
    1163,  1167,  1171,  1175,  1179,  1183,  1187,  1193,  1199,  1203,
    1207,  1211,  1215,  1219,  1223,  1227,  1231,  1235,  1239,  1243,
    1247,  1251,  1255,  1259,  1263,  1267,  1271,  1275,  1279,  1283,
    1287,  1291,  1295,  1299,  1303,  1307,  1311,  1315,  1319,  1325,
    1329,  1333,  1337,  1341,  1345,  1351,  1355,  1359,  1363,  1367,
    1371,  1375,  1381,  1388,  1394,  1402,  1408,  1416,  1425,  1426,
    1429,  1430,  1431,  1432,  1433,  1434,  1435,  1436,  1439,  1440,
    1443,  1444,  1445,  1448,  1457,  1463,  1477,  1478,  1479,  1480,
    1481,  1492,  1502,  1513,  1523,  1534,  1545,  1554,  1563,  1572,
    1583,  1597,  1603,  1604,  1605,  1606,  1607,  1608,  1616,  1621,
    1622,  1623,  1624,  1629,  1634,  1639,  1644,  1649,  1654,  1657,
    1658,  1661,  1665,  1668,  1669,  1670,  1671,  1675,  1680,  1681,
    1682,  1683,  1688,  1699,  1708,  1717,  1726,  1735,  1740,  1745,
    1748,  1752,  1758,  1759,  1763,  1768,  1769,  1770,  1771,  1784,
    1790,  1797,  1802,  1807,  1810,  1818,  1832,  1833,  1853,  1858,
    1859,  1860,  1861,  1868,  1869,  1870,  1871,  1878,  1879,  1880,
    1881,  1887,  1888,  1889,  1890,  1896,  1897,  1898,  1899,  1905,
    1906,  1907,  1908,  1915,  1916,  1917,  1918,  1925,  1926,  1927,
    1928,  1929,  1932,  1960,  1967,  1971,  1974,  1984,  1992,  2003,
    2016,  2030,  2031,  2034,  2035,  2038,  2050,  2055,  2064,  2065,
    2068,  2071,  2072,  2073,  2076,  2091,  2092,  2095,  2096,  2097,
    2098,  2099,  2100,  2103,  2112,  2121,  2129,  2137,  2145,  2153,
    2161,  2170,  2177,  2184,  2192,  2200,  2208,  2216,  2224,  2232,
    2236,  2241,  2249,  2256,  2263,  2276,  2280,  2287,  2291,  2297,
    2309,  2315,  2322,  2323,  2324,  2325,  2328,  2329,  2330,  2331,
    2332,  2333,  2334,  2335,  2336,  2337,  2338,  2339,  2340,  2341,
    2342,  2343,  2344,  2345,  2346,  2349,  2353,  2359,  2365,  2370,
    2379,  2384,  2389,  2392,  2398,  2403,  2411,  2412,  2414,  2418,
    2426,  2430,  2433,  2437,  2443,  2444,  2447,  2453,  2457,  2460,
    2465,  2470,  2475,  2480,  2485,  2491,  2521,  2525,  2529,  2533,
    2537,  2543,  2547,  2550,  2554,  2560,  2569,  2588,  2596,  2597,
    2598,  2601,  2602,  2605,  2606,  2621,  2637,  2645,  2646,  2647,
    2650,  2651,  2654,  2655,  2656,  2671,  2672,  2673,  2674,  2675,
    2678,  2681,  2688,  2692,  2703,  2714,  2724,  2730,  2733,  2734,
    2737,  2743,  2749,  2755,  2762,  2769,  2777,  2778,  2781,  2787,
    2791,  2794,  2799,  2804,  2808,  2814,  2815,  2816,  2817,  2818,
    2819,  2820,  2821,  2822,  2823,  2824,  2825,  2828,  2829,  2833,
    2839,  2840,  2846,  2847,  2853,  2854,  2860,  2863,  2864,  2883,
    2884,  2887,  2891,  2894,  2900,  2906,  2917,  2918,  2919,  2922,
    2923,  2924,  2927,  2931,  2935,  2940,  2945,  2950,  2956,  2960,
    2964,  2970,  2971,  2974,  2977,  2981,  2986,  2992,  2993,  2996,
    2999,  3003,  3007,  3011,  3016,  3023,  3028,  3036,  3041,  3050,
    3051,  3057,  3058,  3059,  3062,  3063,  3066,  3072,  3076,  3079,
    3084,  3090,  3091,  3097,  3098,  3101,  3102,  3105,  3111,  3118,
    3125,  3135,  3136,  3139,  3147,  3158,  3165,  3168,  3174,  3178,
    3181,  3187,  3196,  3207,  3213,  3239,  3240,  3247,  3256,  3267,
    3268,  3269,  3270,  3271,  3272,  3273,  3274,  3275,  3276,  3277,
    3278,  3279,  3280,  3281,  3284,  3307,  3308,  3309,  3312,  3313,
    3314,  3315,  3316,  3319,  3323,  3326,  3330,  3337,  3340,  3354,
    3355,  3359,  3365,  3366,  3372,  3373,  3379,  3380,  3386,  3389,
    3390,  3409,  3415,  3421,  3422,  3423,  3426,  3432,  3433,  3434,
    3437,  3444,  3449,  3454,  3457,  3461,  3465,  3471,  3472,  3479,
    3485,  3486,  3489,  3495,  3499,  3502,  3506,  3510,  3516,  3517,
    3520,  3521,  3524,  3525,  3528,  3539,  3547,  3568,  3576,  3590,
    3598,  3599,  3600,  3603,  3604,  3607,  3622,  3628,  3634,  3641,
    3655,  3663,  3671,  3677,  3681,  3685,  3689,  3693,  3700,  3705,
    3716,  3738,  3746,  3750,  3754,  3760,  3766,  3774,  3775,  3776,
    3779,  3780,  3784,  3790,  3791,  3797,  3798,  3804,  3805,  3811,
    3814,  3815,  3834,  3835,  3838,  3846,  3847,  3848,  3849,  3850,
    3851,  3852,  3853,  3854,  3855,  3856,  3857,  3860,  3861,  3862,
    3863,  3864,  3871,  3878,  3885,  3892,  3899,  3906,  3913,  3920,
    3927,  3934,  3941,  3948,  3951,  3952,  3953,  3954,  3955,  3956,
    3959,  3963,  3967,  3971,  3975,  3979,  3985,  3986,  3996,  4000,
    4004,  4020,  4021,  4024,  4025,  4026,  4027,  4028,  4031,  4032,
    4033,  4034,  4035,  4036,  4037,  4038,  4039,  4040,  4041,  4042,
    4043,  4044,  4045,  4046,  4047,  4048,  4049,  4050,  4051,  4054,
    4067,  4071,  4085,  4089,  4093,  4099,  4105,  4106,  4109,  4110,
    4113,  4114,  4117,  4123,  4124,  4127,  4128,  4131,  4132,  4135,
    4136,  4139,  4147,  4174,  4179,  4184,  4190,  4191,  4194,  4198,
    4218,  4219,  4220,  4221,  4224,  4228,  4232,  4238,  4239,  4242,
    4243,  4244,  4245,  4246,  4247,  4248,  4249,  4250,  4251,  4252,
    4253,  4254,  4255,  4256,  4259,  4260,  4261,  4262,  4263,  4264,
    4265,  4268,  4269,  4270,  4271,  4274,  4275,  4276,  4277,  4280,
    4281,  4284,  4290,  4298,  4311,  4318,  4324,  4330,  4339,  4340,
    4341,  4342,  4343,  4344,  4345,  4346,  4347,  4348,  4349,  4350,
    4351,  4352,  4353,  4354,  4355,  4356,  4359,  4368,  4369,  4370,
    4373,  4379,  4380,  4381,  4384,  4390,  4391,  4392,  4393,  4396,
    4402,  4403,  4404,  4405,  4406,  4407,  4408,  4409,  4410,  4413,
    4417,  4421,  4428,  4429,  4430,  4431,  4432,  4433,  4434,  4435,
    4436,  4437,  4438,  4439,  4442,  4443,  4444,  4445,  4448,  4449,
    4450,  4451,  4452,  4455,  4461,  4462,  4463,  4464,  4465,  4466,
    4467,  4470,  4476,  4477,  4478,  4479,  4482,  4488,  4489,  4490,
    4491,  4492,  4493,  4494,  4495,  4496,  4498,  4504,  4505,  4506,
    4507,  4508,  4509,  4510,  4511,  4514,  4520,  4521,  4522,  4523,
    4524,  4527,  4533,  4534,  4537,  4543,  4544,  4545,  4548,  4554,
    4555,  4556,  4557,  4560,  4566,  4567,  4568,  4569,  4572,  4576,
    4580,  4587,  4588,  4589,  4590,  4591,  4592,  4593,  4594,  4595,
    4596,  4599,  4600,  4601,  4602,  4603,  4604,  4605,  4606,  4607,
    4608,  4609,  4610,  4613,  4614,  4615,  4616,  4617,  4618,  4619,
    4620,  4623,  4629,  4630,  4631,  4634,  4640,  4641,  4642,  4643,
    4646,  4654,  4655,  4658,  4659,  4660,  4661,  4662,  4663,  4664,
    4665,  4668,  4674,  4675,  4678,  4684,  4685,  4686,  4687,  4690,
    4696,  4702,  4708,  4711,  4717,  4718,  4719,  4720,  4726,  4732,
    4733,  4734,  4735,  4736,  4737,  4740,  4746,  4747,  4750,  4756,
    4757,  4758,  4759,  4760,  4763,  4777,  4778,  4779,  4780,  4781
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
  "\"iifgroup\"", "\"oifgroup\"", "\"cgroup\"", "\"classid\"",
  "\"nexthop\"", "\"ct\"", "\"l3proto\"", "\"proto-src\"", "\"proto-dst\"",
  "\"zone\"", "\"direction\"", "\"event\"", "\"expectation\"",
  "\"expiration\"", "\"helper\"", "\"label\"", "\"state\"", "\"status\"",
  "\"original\"", "\"reply\"", "\"counter\"", "\"name\"", "\"packets\"",
  "\"bytes\"", "\"avgpkt\"", "\"counters\"", "\"quotas\"", "\"limits\"",
  "\"helpers\"", "\"log\"", "\"prefix\"", "\"group\"", "\"snaplen\"",
  "\"queue-threshold\"", "\"level\"", "\"limit\"", "\"rate\"", "\"burst\"",
  "\"over\"", "\"until\"", "\"quota\"", "\"used\"", "\"secmark\"",
  "\"secmarks\"", "\"nanosecond\"", "\"microsecond\"", "\"millisecond\"",
  "\"second\"", "\"minute\"", "\"hour\"", "\"day\"", "\"week\"",
  "\"reject\"", "\"with\"", "\"icmpx\"", "\"snat\"", "\"dnat\"",
  "\"masquerade\"", "\"redirect\"", "\"random\"", "\"fully-random\"",
  "\"persistent\"", "\"queue\"", "\"num\"", "\"bypass\"", "\"fanout\"",
  "\"dup\"", "\"fwd\"", "\"numgen\"", "\"inc\"", "\"mod\"", "\"offset\"",
  "\"jhash\"", "\"symhash\"", "\"seed\"", "\"position\"", "\"index\"",
  "\"comment\"", "\"xml\"", "\"json\"", "\"vm\"", "\"notrack\"",
  "\"exists\"", "\"missing\"", "\"exthdr\"", "\"ipsec\"", "\"mode\"",
  "\"reqid\"", "\"spnum\"", "\"transport\"", "\"tunnel\"", "\"in\"",
  "\"out\"", "'='", "'{'", "'}'", "'|'", "'$'", "'('", "')'", "'['", "']'",
  "$accept", "input", "stmt_separator", "opt_newline", "common_block",
  "line", "base_cmd", "add_cmd", "replace_cmd", "create_cmd", "insert_cmd",
  "delete_cmd", "get_cmd", "list_cmd", "reset_cmd", "flush_cmd",
  "rename_cmd", "import_cmd", "export_cmd", "monitor_cmd", "monitor_event",
  "monitor_object", "monitor_format", "markup_format", "describe_cmd",
  "table_block_alloc", "table_options", "table_block", "chain_block_alloc",
  "chain_block", "set_block_alloc", "set_block", "set_block_expr",
  "set_flag_list", "set_flag", "map_block_alloc", "map_block",
  "set_mechanism", "set_policy_spec", "flowtable_block_alloc",
  "flowtable_block", "flowtable_expr", "flowtable_list_expr",
  "flowtable_expr_member", "data_type_atom_expr", "data_type_expr",
  "obj_block_alloc", "counter_block", "quota_block", "ct_helper_block",
  "ct_timeout_block", "ct_expect_block", "limit_block", "secmark_block",
  "type_identifier", "hook_spec", "prio_spec", "extended_prio_name",
  "extended_prio_spec", "int_num", "dev_spec", "policy_spec",
  "policy_expr", "chain_policy", "identifier", "string", "time_spec",
  "family_spec", "family_spec_explicit", "table_spec", "tableid_spec",
  "chain_spec", "chainid_spec", "chain_identifier", "set_spec",
  "setid_spec", "set_identifier", "flowtable_spec", "flowtable_identifier",
  "obj_spec", "objid_spec", "obj_identifier", "handle_spec",
  "position_spec", "index_spec", "rule_position", "ruleid_spec",
  "comment_spec", "ruleset_spec", "rule", "rule_alloc", "stmt_list",
  "stateful_stmt", "stmt", "verdict_stmt", "verdict_map_stmt",
  "verdict_map_expr", "verdict_map_list_expr",
  "verdict_map_list_member_expr", "connlimit_stmt", "counter_stmt",
  "counter_stmt_alloc", "counter_args", "counter_arg", "log_stmt",
  "log_stmt_alloc", "log_args", "log_arg", "level_type", "log_flags",
  "log_flags_tcp", "log_flag_tcp", "limit_stmt", "quota_mode",
  "quota_unit", "quota_used", "quota_stmt", "limit_mode",
  "limit_burst_pkts", "limit_burst_bytes", "time_unit", "reject_stmt",
  "reject_stmt_alloc", "reject_opts", "nat_stmt", "nat_stmt_alloc",
  "tproxy_stmt", "synproxy_stmt", "synproxy_stmt_alloc", "synproxy_args",
  "synproxy_arg", "primary_stmt_expr", "shift_stmt_expr", "and_stmt_expr",
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
  "symbol_expr", "integer_expr", "primary_expr", "fib_expr", "fib_result",
  "fib_flag", "fib_tuple", "osf_expr", "osf_ttl", "shift_expr", "and_expr",
  "exclusive_or_expr", "inclusive_or_expr", "basic_expr", "concat_expr",
  "prefix_rhs_expr", "range_rhs_expr", "multiton_rhs_expr", "map_expr",
  "expr", "set_expr", "set_list_expr", "set_list_member_expr",
  "meter_key_expr", "meter_key_expr_alloc", "set_elem_expr",
  "set_elem_expr_alloc", "set_elem_options", "set_elem_option",
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
     565,   566,   567,   568,   569,   570,   571,    61,   123,   125,
     124,    36,    40,    41,    91,    93
};
# endif

#define YYPACT_NINF -1327

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1327)))

#define YYTABLE_NINF -811

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1327,  5446, -1327,   589, -1327, -1327,    33,    45,    45,    45,
     702,   702,   702,   702,   702,   702,   702, -1327, -1327,  2297,
     146,   693,   191,  1607,   198,  3834,   469,  1452,   208,  4758,
     121,   194,   164, -1327, -1327, -1327, -1327,   153,   702,   702,
     702,   702, -1327, -1327, -1327,   532, -1327,    45, -1327,    45,
      76,  4408, -1327,   589, -1327,   -47,   -19,   589,   -44,    -5,
    4408,    45, -1327,  -148, -1327,    45, -1327, -1327,   702, -1327,
     702,   702,   702,   702,   702,   702,   209,   702,   702,   702,
     702, -1327,   702, -1327,   702,   702,   702,   702,   702,   702,
     702,   248,   702,   702,   702,   702, -1327,   702, -1327,   702,
     702,   702,   702,  1088,   702,   702,   702,   702,   389,   702,
     702,   702,    47,   702,  1322,  1510,  1521,   702,   702,   702,
    1708, -1327,   702,  1924,  1957,   702, -1327,   702,   702,   702,
     702,   702,   279,   702, -1327,   702, -1327,   881,   353,    55,
     211, -1327, -1327, -1327, -1327,   290,   731,   792,  1372,  2058,
    1701,   390,  2016,  1233,   870,    -3,   450,   701,   570,  2277,
      85,   648,  1524,   183,   222,   416,    78,   770,   318,  1105,
    4046, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327,  2406,   -58,  4620,    54,   644,   206,    45,  4758, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327,   639, -1327, -1327,   160, -1327, -1327,
     639, -1327, -1327, -1327, -1327,  1730,   702,   702,   702,    45,
     264,   265,   240,   952, -1327, -1327, -1327, -1327,   440,   449,
     466, -1327, -1327, -1327,   327, -1327,   732, -1327, -1327, -1327,
   -1327, -1327,    69,    69, -1327,    92,    45,  5211,  4344,   336,
   -1327,  -106,   272, -1327, -1327, -1327, -1327, -1327, -1327,   518,
     398, -1327,   598, -1327,   320,  4408, -1327, -1327, -1327, -1327,
   -1327, -1327,   501, -1327,   498, -1327, -1327, -1327,   350, -1327,
    2993, -1327, -1327,   420, -1327,    22, -1327,    26, -1327, -1327,
   -1327,   803, -1327,   109, -1327, -1327,   593, -1327, -1327, -1327,
     779,   613,   619,   322, -1327,   170, -1327,  3808, -1327, -1327,
   -1327,   595, -1327, -1327, -1327,   617, -1327,  3877,  3877, -1327,
     328,   351, -1327, -1327,   356, -1327, -1327, -1327,   362, -1327,
     365,   632,  4408,   -44,    -5, -1327,  -148, -1327, -1327,   702,
     702,   702,   264,   265,   240,   952,  4408,   112, -1327, -1327,
     117, -1327, -1327, -1327,   129, -1327, -1327,  -148, -1327, -1327,
   -1327, -1327, -1327,   702,   190, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327,  -148, -1327, -1327, -1327, -1327, -1327,   702,
   -1327, -1327, -1327, -1327, -1327,   702,   702, -1327, -1327, -1327,
     646,   660,   663,   702, -1327,   702, -1327,   702, -1327,   702,
   -1327, -1327, -1327, -1327,   702, -1327, -1327,   702, -1327,   702,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327,   702, -1327,    45,
   -1327, -1327, -1327, -1327,   707, -1327, -1327, -1327, -1327, -1327,
     682,   344, -1327, -1327, -1327,   607,    15, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,   154,
     173, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,   863,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327,  2421, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327,   303, -1327, -1327,
     393, -1327, -1327, -1327, -1327, -1327, -1327,   397, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,  1122, -1327,
   -1327, -1327, -1327,   429,   139,   431,   631, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327,   424, -1327,   422, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,   639, -1327,
   -1327, -1327, -1327,   651, -1327, -1327,   588, -1327, -1327, -1327,
   -1327,   659, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
    3156,   684,  4758, -1327, -1327, -1327, -1327,   754,   774,     1,
     757,   776,   783,    10,   785,  1122,   794,  4185,  4185,   588,
    4185,   747,  4185,  4185,   719, -1327,  3877,    48, -1327,   952,
   -1327, -1327,   786,   789,   501, -1327,   402,   952,   796,   799,
     811,   952,   498, -1327,   407, -1327,  4185, -1327, -1327,  3319,
     731,   792,  1372,  1896, -1327,  1971,   319, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327,   840,   895,   896,   596,   311,
     156, -1327, -1327, -1327, -1327, -1327,   914,   859,   924, -1327,
   -1327, -1327, -1327,   938, -1327, -1327, -1327, -1327,   866, -1327,
   -1327,   963,   967, -1327,   822,   857, -1327, -1327,   420, -1327,
     971, -1327, -1327, -1327, -1327,   973, -1327,  3482, -1327,   973,
    4185, -1327, -1327,   803, -1327,   975, -1327,    45,   671,    45,
      27, -1327,  5002,  5002,  5002,  5002,  5002,  4758,    12,  3877,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327,  5002, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327,   997, -1327,   843,   961,   988,   690,   504,  1000, -1327,
   -1327, -1327,  3877,  4185,  4185,   589,   997, -1327,   589, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327,   709,   711,   729, -1327,
     737,   738, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
     921,   959,   969, -1327, -1327,   994, -1327, -1327, -1327, -1327,
     702,   702,   702, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327,   998,   353, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,   912,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327,  1517, -1327,   999,  1003, -1327, -1327,   820, -1327,
     842, -1327, -1327, -1327, -1327, -1327, -1327,  1004,  1006,   765,
    1015,    75, -1327, -1327, -1327,   744,   745,   748,   823, -1327,
   -1327,  1016,    50,  4185,  2058,  2016,  1115,  3645,   109,    13,
    1109,   952,   952,  1026,  4758,  4185,  4185,  4185, -1327,  1032,
    4185,  1085,  4185, -1327, -1327,  1037, -1327,    50,  1117, -1327,
    4185, -1327,   598,   949,    13, -1327,   597,  1000,   598, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327,  1017,   143, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327,  1055,  1057,  1097,
    1058, -1327,  4185,  1166,  5162,  5002,  5162,  5162,  5162,  1078,
    5162,  5162,   333,  4185,   973,  4185,  3924,  3924, -1327, -1327,
   -1327,  4185,   859,  4185,   859, -1327, -1327,   675,  4758, -1327,
    4758, -1327, -1327, -1327,   843,   961,   988, -1327,    45,   598,
   -1327, -1327,   855,  5002,  5002,  5002,  5002,  5002,  5002,  5002,
    1081,  5002,  5002, -1327, -1327, -1327, -1327, -1327,  1709,  2173,
     562,   239,   230, -1327, -1327, -1327, -1327, -1327,   864,   865,
     873, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,  1174,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327,   867,   876, -1327, -1327,
   -1327, -1327,   765,   176,  1096, -1327, -1327, -1327, -1327, -1327,
     858, -1327, -1327, -1327,  1113,   102, -1327, -1327,   943, -1327,
    4185,  4185,  1206, -1327,  1116,  1116, -1327,    13, -1327, -1327,
   -1327,   900,  1109,  4408,    13, -1327, -1327, -1327, -1327, -1327,
    4185, -1327,   106,   943,  4185,  1173, -1327,  4931, -1327,    13,
    3877, -1327, -1327, -1327, -1327,  1213, -1327,  1121,  1123, -1327,
    1127, -1327,  4185, -1327, -1327, -1327, -1327,   840,   895,   896,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327,  1229, -1327, -1327,
   -1327, -1327,   859, -1327,   859,   973, -1327,   163,  4408, -1327,
    4037,    51, -1327, -1327, -1327, -1327, -1327,   843,   961,   988,
   -1327, -1327, -1327, -1327,    45,    45,    45,    45,  1136,   315,
      45,    45,    45,    45, -1327, -1327, -1327,   589,    14,  1137,
   -1327, -1327, -1327,   589,   589,   589, -1327,  1116,  1116,   928,
     925,  1139,   404,   688, -1327, -1327, -1327,   589,  1116,   930,
     404,   688, -1327, -1327, -1327,   589,  1141,   932, -1327, -1327,
   -1327,  1743,  2470,  1100,  1389,   760, -1327, -1327, -1327,  1143,
   -1327, -1327, -1327,  1151, -1327, -1327, -1327, -1327, -1327,   134,
    1984,   275, -1327,   603,   991,  1156, -1327, -1327, -1327,  4185,
   -1327, -1327, -1327, -1327,  4758,   937,    13, -1327,   603,   991,
   -1327, -1327,  4185,   598, -1327,  1000, -1327,   143, -1327, -1327,
   -1327, -1327,  4185,   973,   973,  4758,  1077, -1327,    35,   944,
    1259,   598, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327,    45,    45,    45, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327,  1226, -1327, -1327, -1327,   589,
     589,  -148, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327,   565, -1327, -1327, -1327, -1327, -1327,   654, -1327,
   -1327,   589,  -148,   394,   654, -1327,  1125,   950, -1327, -1327,
   -1327, -1327, -1327,   187,  2030,   486, -1327,   765,   958,   432,
     702, -1327, -1327, -1327, -1327,  1116,  1170,   432,  1177,   702,
   -1327, -1327, -1327, -1327,  1178,   702, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327,  1019,  1184, -1327,    50, -1327,
    4408, -1327,  1019, -1327, -1327, -1327, -1327, -1327,   965,  4758,
   -1327, -1327,  1007,  4037, -1327,   972,   974,   978,   983, -1327,
   -1327, -1327,   989,   990,   992,   993,  1185, -1327, -1327, -1327,
     404, -1327,   688, -1327, -1327, -1327,   696, -1327,   105,   589,
    1187,   589, -1327, -1327, -1327, -1327,  1008, -1327, -1327,   589,
     589,   589,   589,   589,   589,   589,  1162,   589,  1207, -1327,
      53, -1327,  1009, -1327, -1327,  1010,   598, -1327, -1327, -1327,
   -1327,  1018,  1020,  1021, -1327, -1327, -1327, -1327,  1269, -1327,
   -1327,   589,   589,   589,   589,   565,  1218, -1327, -1327, -1327,
     458, -1327, -1327, -1327, -1327, -1327,    59, -1327, -1327,  1222,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327,   432, -1327,  1094,
   -1327, -1327, -1327, -1327, -1327,  2767,  1112,  1907,   907, -1327,
   -1327, -1327,   986,  1022,   314,   683,   952,  1125, -1327, -1327,
   -1327, -1327, -1327, -1327,  1228,  1245,   108, -1327,  1342,    63,
   -1327,   589, -1327,   589,   589,   589,   589,   700,  2082,   669,
     589, -1327, -1327, -1327,   589, -1327, -1327, -1327,   589, -1327,
   -1327, -1327,   589, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327,  1249,  1222,   589, -1327, -1327, -1327, -1327, -1327,
     589,   589,   589, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     285,   285,   285,   285,   285,   285,   285,   289,   292,   285,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   138,   291,   290,   287,   288,     0,   285,   285,
     285,   285,    14,    13,     3,     0,    17,     0,   286,     0,
     309,     0,    12,     0,   280,     0,     0,     0,    32,    34,
       0,     0,   178,     0,   197,     0,   214,    18,   285,    19,
     285,   285,   285,   285,   285,   285,     0,   285,   285,   285,
     285,    20,   285,    21,   285,   285,   285,   285,   285,   285,
     285,     0,   285,   285,   285,   285,    22,   285,    23,   285,
     315,   285,   315,   315,   285,   285,   315,   315,     0,   285,
     315,   315,     0,   285,   315,   315,   315,   285,   285,   285,
     315,    24,   285,   315,   315,   285,    25,   285,   285,   285,
     285,   315,     0,   285,    26,   285,    27,     0,     0,     0,
     567,   538,   281,   282,   283,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   718,   719,   720,   721,   722,   723,   724,   725,   726,
     727,   728,   729,   730,   731,   732,   733,   734,   735,   736,
     737,     0,     0,     0,     0,     0,   738,     0,     0,    31,
     536,   535,   539,   540,   153,   550,   551,   544,   709,   545,
     548,   552,   549,   546,   547,   541,   818,   819,   820,   821,
     822,   823,   824,   825,   826,   827,   828,   829,   830,   831,
     832,   833,   834,   835,   542,   983,   984,   985,   986,   987,
     988,   989,   990,   543,     0,   150,   151,     0,    28,   134,
       0,    29,   136,   139,    30,   140,   285,   285,   285,     0,
      42,     0,   390,     0,    16,    15,   293,   295,     0,     0,
       0,   311,   310,   312,     0,   428,     0,   521,   522,   700,
     701,   702,     0,     0,   705,   527,     0,     0,     0,   358,
     366,     0,   390,   411,   418,   419,   483,   489,   506,     0,
       0,   742,     7,    37,   317,   319,   330,   320,   326,   346,
     325,   322,   356,   332,   364,   323,   324,   333,   412,   334,
       0,   335,   344,   426,   338,   482,   339,   488,   340,   341,
     336,   504,   342,     0,   343,   328,     0,   526,   327,   569,
     572,   574,   576,   578,   579,   587,   589,     0,   588,   533,
     345,   709,   331,   337,   329,   541,     8,     0,     0,    11,
       0,     0,    36,   298,     0,    40,   190,   189,     0,   301,
       0,     0,     0,    51,    53,   178,     0,   197,   214,   285,
     285,   285,    59,     0,   390,     0,     0,     0,    68,    69,
       0,    70,    71,    72,     0,    73,    74,     0,    75,    77,
     621,   622,   620,   285,     0,    78,    79,    83,    84,    80,
      81,    85,    86,     0,    88,   316,    89,    90,    91,   285,
      92,    94,   114,   113,   107,   285,   315,   111,   110,   112,
     621,   622,     0,   285,    97,   285,    95,   285,    98,   285,
     101,   103,   100,   106,   285,   104,   121,   285,   119,   285,
     122,   124,   125,   126,   127,   128,   131,   285,   130,     0,
     837,   838,   839,   537,     0,   558,   559,   560,   561,   562,
     564,     0,   746,   747,   745,     0,     0,   981,   982,   980,
     841,   842,   843,   840,   848,   845,   846,   847,   844,     0,
       0,   850,   851,   852,   853,   854,   849,   872,   873,   867,
     862,   863,   864,   865,   866,   868,   869,   870,   871,     0,
     859,   884,   887,   886,   885,   888,   889,   890,   883,   892,
     893,   894,   895,   891,   904,   905,   897,   898,   899,   901,
     900,   902,   903,   896,   907,   912,   909,   908,   913,   911,
     910,   914,   906,   917,   920,   916,   918,   919,   915,   923,
     922,   921,   925,   926,   927,   924,   931,   932,   929,   930,
     928,   937,   934,   935,   936,   933,   949,   943,   946,   947,
     941,   942,   944,   945,   948,   950,     0,   938,   974,   972,
     973,   971,   979,   976,   977,   978,   975,   997,   766,   996,
     772,   767,   995,   998,   770,   771,   773,     0,   768,   994,
       0,   999,  1002,  1001,  1005,  1004,  1006,     0,  1003,   993,
     992,   991,  1014,  1011,  1009,  1010,  1012,  1013,  1008,  1017,
    1016,  1015,  1021,  1020,  1023,  1019,  1022,  1018,   710,   713,
     714,   715,   717,   716,   738,   708,   711,   712,   787,   788,
     780,   781,   779,   789,   790,   808,   783,   792,   785,   786,
     791,   782,   784,   777,   778,   806,   805,   807,     0,   774,
     793,   751,   750,     0,   587,     0,     0,  1026,  1025,  1027,
    1028,  1029,  1024,   755,   756,   754,   534,     0,   133,   152,
     135,   141,   142,   144,   143,   146,   147,   145,   148,   638,
     638,   638,   303,     0,   615,    43,   399,   641,    48,   388,
     389,     0,   617,    44,   618,   619,    49,   306,   307,   308,
       0,     0,     0,   707,   706,   703,   704,     0,     0,     0,
     710,   708,     0,     0,     0,     0,   774,     0,     0,   399,
       0,     0,     0,     0,     0,     6,     0,     0,   591,     0,
     318,   321,     0,     0,   357,   360,     0,     0,     0,     0,
       0,     0,   365,   367,     0,   410,     0,   465,   673,     0,
     665,   668,   669,   666,   672,   667,     0,   676,   674,   675,
     671,   670,   662,   663,   447,   450,   452,   454,   456,   457,
     462,   469,   466,   467,   468,   470,   472,   417,   435,   436,
     446,   664,   437,   444,   438,   445,   441,   442,     0,   439,
     440,     0,   471,   443,     0,     0,   434,   433,   427,   429,
       0,   501,   502,   503,   481,   486,   499,     0,   487,   492,
       0,   513,   514,   505,   507,   510,   511,     0,     0,     0,
       0,   528,     0,     0,     0,     0,     0,     0,     0,     0,
     694,   695,   696,   697,   698,   699,   665,   668,   669,   666,
     686,   687,   667,   688,   685,   684,   689,   682,   683,   681,
     690,   691,   692,     0,   585,   677,   678,   583,   584,   648,
     649,   643,   642,   653,   655,   657,   659,   660,   647,   679,
     680,   650,     0,     0,     0,     0,   613,   612,     0,   156,
     172,   179,   198,   215,   313,    50,     0,     0,     0,    57,
       0,     0,   638,   638,   638,    60,    65,    61,    66,    67,
       0,     0,     0,    76,   638,     0,    87,    93,   109,   108,
     285,   285,   285,   115,    96,    99,   102,   105,   120,   123,
     129,   132,     0,     0,   557,   555,   556,   554,   568,   565,
     566,   855,   857,   856,   858,   874,   875,   876,   877,   861,
     954,   961,   951,   953,   952,   956,   957,   958,   959,   960,
     955,   962,   940,   769,     0,     0,   794,   795,     0,   797,
       0,   796,   798,   799,   775,   776,   800,     0,     0,   748,
       0,     0,   553,   137,   149,     0,     0,     0,     0,   397,
     398,     0,     0,     0,   666,   667,   420,     0,     0,   515,
     517,     0,     0,     0,     0,     0,     0,     0,   354,     0,
       0,   800,     0,   359,   387,     0,   396,     0,   495,   497,
       0,   609,     7,     7,   600,   602,   660,   608,     7,   590,
     314,   362,   363,   361,   380,   379,     0,     0,   378,   374,
     369,   370,   371,   372,   375,   373,   368,     0,     0,     0,
       0,   478,     0,   473,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   480,     0,     0,     0,   431,   432,
     430,     0,     0,     0,   490,   509,   508,     0,     0,   530,
       0,   529,   570,   571,   573,   575,   577,   580,     0,     7,
     347,   586,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   644,   740,   817,     9,    10,     0,     0,
       0,     0,     0,   156,   172,   179,   198,   215,     0,     0,
       0,   294,   296,   299,    82,   304,   117,   118,   116,     0,
     563,   878,   879,   881,   880,   882,   860,   965,   964,   963,
     966,   967,   968,   969,   970,   939,     0,     0,   801,   802,
     803,   804,   748,   748,     0,   765,   753,   757,   758,   761,
       0,   241,   245,   237,     0,     0,   392,   391,   393,   422,
       0,     0,   421,   518,     0,     0,   607,   516,   603,   744,
     743,     0,   599,     0,   597,   741,   739,   814,   355,   815,
       0,   813,     0,   393,     0,     0,   594,     0,   595,   601,
     593,   592,   377,   383,   384,   376,   382,     0,     0,   416,
       0,   479,     0,   448,   435,   444,   449,   451,   453,   455,
     463,   464,   458,   461,   460,   459,   475,   474,   809,   810,
     811,   812,   484,   500,   491,   493,   512,     0,     0,   349,
       0,     0,   350,   693,   646,   651,   652,   654,   656,   658,
     645,   581,   582,   661,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    33,   158,   157,     0,     0,     0,
      35,   174,   173,     0,     0,     0,   187,     0,     0,     0,
       0,     0,     0,     0,    38,   181,   180,     0,     0,     0,
       0,     0,    39,   200,   199,     0,     0,     0,    41,   217,
     216,     0,     0,     0,     0,     0,   241,   245,   237,     0,
    1000,  1007,   752,     0,   764,   749,   760,   759,   762,     0,
       0,     0,   614,     0,   402,     0,   616,   423,   425,     0,
     284,   605,   606,   604,     0,     0,   598,   816,     0,   402,
     395,   496,     0,     7,   660,   610,   611,     0,   413,   414,
     415,   476,     0,   485,   494,     0,     0,   519,     0,     0,
       0,     7,   348,   297,   171,   300,   178,   197,   302,   214,
     155,     0,     0,     0,   305,   228,   228,   228,   228,   159,
     278,   279,   275,   277,   276,     0,   175,   176,   177,     0,
       0,     0,   213,   212,   210,   211,   257,   259,   260,   258,
     261,   226,     0,   225,   193,   194,   196,   195,     0,   192,
     188,     0,     0,     0,     0,   209,     0,     0,    52,    54,
      55,    56,    58,     0,     0,     0,   836,   748,     0,     0,
       0,    46,   243,   242,   244,     0,     0,     0,     0,     0,
      47,   247,   246,   248,     0,     0,    45,   239,   238,   240,
     405,   406,   407,   408,   409,   400,     0,   640,     0,   424,
       0,   531,   400,   386,   498,   596,   381,   477,     0,     0,
     520,   525,     0,   352,   351,     0,     0,     0,     0,   228,
     228,   228,     0,     0,     0,     0,     0,   184,   185,   186,
       0,   182,     0,   183,   201,   208,     0,   207,     0,     0,
       0,     0,    63,    64,    62,   763,     0,   624,   623,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   639,
       0,   394,     0,   385,   523,     0,     7,   172,   179,   198,
     215,     0,     0,     0,   229,   249,   233,   253,   274,   227,
     191,     0,     0,     0,     0,     0,     0,   271,   265,   264,
     268,   263,   266,   267,   218,   224,     0,   221,   219,     0,
     630,   632,   635,   636,   633,   634,   637,     0,   626,     0,
     404,   403,   532,   524,   353,     0,     0,     0,     0,   241,
     245,   237,     0,     0,     0,     0,     0,     0,   203,   205,
     204,   206,   202,   272,     0,     0,     7,   220,     0,     0,
     627,     0,   401,     0,     0,     0,     0,     0,     0,     0,
       0,   231,   230,   232,     0,   251,   250,   252,     0,   235,
     234,   236,     0,   255,   254,   256,   273,   262,   270,   269,
     223,   222,     0,     0,     0,   625,   160,   161,   162,   163,
       0,     0,     0,   164,   169,   165,   170,   629,   628,   631,
     167,   168,   166
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1327, -1327,    -1,  -974,    11, -1327, -1327,  1330, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327,   -12, -1327,   977, -1327,   244,  -363, -1088,
    -372, -1082,  -370,    67,  -132,  -364, -1087, -1086, -1327,  -369,
   -1081, -1327, -1327,  -235,  -125, -1207,  -699, -1327, -1327, -1258,
   -1241, -1228, -1327, -1327, -1327, -1327,  -220, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327,   571,  -262, -1055,  1292,   -43,  1790,
   -1327,   751, -1327, -1327,    70, -1327,   122,   152, -1327,   546,
    1054,  -679,  1011, -1327, -1327,   104,  1291,  1082,   -10,     2,
   -1327, -1327,   155,  -300, -1327, -1327, -1327, -1327,    38, -1327,
   -1327, -1327, -1327,   650, -1327, -1327, -1327,   653, -1327, -1327,
   -1327,    56, -1327,  1119,  -989,   215, -1327,   680,   -48,    81,
      83, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
     618,  -560,   369,   370,   375, -1327,   378, -1327, -1327, -1327,
   -1327, -1327,  -340, -1327,   964, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327,  -317,   372, -1327, -1327, -1327,   622,
   -1327,   364, -1033, -1327, -1327,  1182, -1327, -1327, -1327, -1327,
     612, -1327, -1327,   -29,   -21,    57,  1420, -1327, -1327, -1327,
     521,   -13, -1327, -1327, -1327, -1327, -1327,  -175,  -171, -1327,
   -1327,  -722, -1327,  1266,    62, -1327,   434, -1006, -1327, -1075,
   -1327,  -933, -1058, -1327, -1327,  1106,  -119,  1083,  -118,  1084,
    -114,  1087,  1361, -1326, -1327, -1327,  -157, -1327, -1327,  -509,
    -100,  1101, -1327,  1138,  -323,  -752,  -740,  -738, -1327,  -326,
    -732, -1327,  -229,   849,  -684, -1327, -1119,  1204,    -9,  1210,
   -1327,   -14, -1327,    95, -1327, -1077, -1327,   168, -1327, -1327,
   -1327, -1327, -1327,   257,  -259,   295,   908,   352,  1205,  1216,
   -1327, -1327,  -527,   -35, -1327, -1327, -1327,   377, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327, -1327,
   -1327, -1327, -1327, -1327, -1327, -1327, -1327
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1271,   736,  1272,    44,    45,    46,    69,    81,
      83,    96,    98,   121,   126,   134,   136,   248,   251,   254,
     255,   688,   983,   249,   199,   360,  1267,  1108,   361,  1109,
     364,  1110,   365,  1408,  1409,   368,  1111,  1287,  1394,   370,
    1112,  1501,  1556,  1557,  1401,  1402,  1482,  1582,  1584,  1321,
    1319,  1320,  1583,  1585,  1403,  1273,  1499,  1550,  1551,  1552,
    1587,  1274,  1382,  1383,  1374,   200,  1331,    47,    48,   259,
     389,    50,   392,  1364,    62,   396,  1366,    66,  1369,   260,
     406,  1375,   271,   272,   273,    51,   372,  1176,   416,  1275,
     304,   305,   306,   307,   308,   309,  1090,  1241,  1242,   310,
     311,   312,   744,   745,   313,   314,   752,   753,  1045,  1039,
    1205,  1206,   315,   701,  1168,  1326,   316,   991,  1519,  1457,
    1455,   317,   318,   755,   319,   320,   321,   322,   323,   808,
     809,   774,   775,   776,   777,   778,   779,   780,  1223,   781,
     782,   783,   784,   785,   786,   787,   324,   325,   814,   326,
     327,   818,   328,   329,   815,   816,   330,   331,   823,   824,
     825,   826,   998,   999,   332,   333,   334,   335,   336,   830,
     831,   337,   338,   201,   788,   789,   339,   205,   937,   470,
     471,   790,   476,   340,   341,   342,   343,   344,   345,   867,
     868,   869,   346,   347,   348,   737,   738,  1183,  1184,  1023,
    1024,  1177,  1178,  1025,  1343,   885,   694,   695,   702,   703,
     705,   706,   403,  1509,  1449,  1599,  1600,  1434,  1443,   985,
     697,   698,   349,   886,   887,   873,   874,   875,   876,  1026,
     878,   791,   792,   793,   881,   882,   350,   715,   794,   635,
     636,   208,   352,   795,   474,  1155,   663,   796,   981,   675,
    1159,  1318,   211,   797,   597,   799,   598,   800,   658,   659,
     974,   975,   660,   801,   802,   353,   354,   803,   216,   464,
     217,   483,   218,   488,   219,   496,   220,   510,   949,  1136,
     221,   518,   222,   523,   223,   533,   224,   542,   225,   548,
     226,   551,   227,   555,   228,   560,   229,   565,   230,   577,
     962,  1145,   231,   581,   232,   586,   233,   479,   234,   235,
     611,   236,   599,   237,   601,   238,   603,   239,   608,   240,
     618,   241,   621,   242,   627,   243,   672
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,   704,    52,   898,  1027,   741,   899,   864,   202,   901,
     819,   897,    43,   900,  1021,   711,   206,   864,   864,   252,
     207,   877,   664,   677,   872,  1295,  1302,   913,  1193,  1304,
     202,   877,   877,  1303,   366,  1088,  1305,   351,   206,   202,
    1469,   734,   207,   916,   265,  1237,   351,   206,  1196,  1198,
    1425,   207,   356,   303,  1200,  1028,   359,   415,  1361,   415,
     415,   798,   362,   415,   415,  1423,  1596,   415,   415,   829,
    1633,   415,   415,   415,  1238,  1312,  1314,   415,  1346,  1424,
     415,   415,  1084,  1413,    63,    64,   203,   472,   415,  1380,
    1381,  1199,   418,   420,  1003,  1085,   423,   424,  1086,  1174,
     428,   429,  1175,   810,   436,   438,   440,   817,   203,  1008,
     445,  1513,   735,   448,   450,  1240,    60,   203,   879,  1333,
    1332,   456,  1323,   704,   209,   367,  1338,  1546,   879,   879,
     268,   976,   827,   430,    53,     3,   549,   939,     4,   728,
       5,  1333,   375,   376,   377,    54,   209,   837,  1082,  1083,
    1166,   717,   550,  1570,   729,   209,   637,   395,   397,   398,
       6,     7,     8,     9,  1061,  1360,   910,   413,  1355,    54,
     302,   911,   202,   197,   421,   422,   244,   202,   837,   427,
     206,   986,   987,   912,   207,   206,   386,   718,     3,   207,
     839,     4,    68,     5,   838,   578,   588,   210,  1011,   454,
     455,   609,  1324,   458,  1547,  1548,  1339,  1062,  1555,   142,
     143,   144,    54,     6,     7,     8,     9,    54,  1295,   210,
     591,   839,  1389,  1390,  1428,   661,   610,   378,   210,    54,
    1157,     3,   678,  1411,     4,   662,     5,    82,   680,   256,
       3,  1601,   399,     4,   915,     5,   579,   580,    97,   250,
     203,  1336,   135,   714,   714,   203,     6,     7,     8,     9,
     940,   941,   473,  1429,   253,     6,     7,     8,     9,  1296,
     357,  1297,  1009,   637,  -154,   942,     3,  1428,  1333,     4,
     943,     5,  1203,   431,   202,   402,   212,  1204,   209,  1545,
      54,   351,   206,   209,   944,   379,   207,  1167,   358,   432,
    1571,     6,     7,     8,     9,   811,   812,   813,   212,   811,
     812,   813,   828,  -171,   739,     3,  1429,   212,     4,  1004,
       5,   457,  1468,  1609,   213,  1288,   865,  1289,  1460,  1280,
    1089,  1059,  1281,  1060,   400,   197,   865,   865,  1607,   475,
       6,     7,     8,     9,  1247,  1080,   213,   366,   666,  1290,
    1505,   202,  1608,  1526,  1470,   213,   827,  1248,   351,   206,
    1249,   210,   203,   207,  1430,   202,   210,  1029,   366,  1465,
    1362,  1216,   351,   206,   895,   269,   270,   207,  1597,   600,
    1511,   214,  1634,   415,   366,  1444,  1158,  1473,   909,   257,
     197,   258,  1356,  1118,  1119,  1120,   864,  1291,  1360,  1496,
     209,  1371,  1490,   214,   866,  1124,   215,   289,   710,   870,
    1245,  1246,   214,  -390,   866,   866,   919,  1430,   602,   870,
     870,  1549,   291,   245,   246,   247,   197,   292,   355,   203,
     197,   425,   426,   142,   143,   144,  1525,   355,   367,  1575,
     588,   619,  1577,   203,   590,   380,  1576,   381,   588,  1578,
     212,   477,   478,  1431,   934,   212,   804,   805,   806,   367,
     590,   465,   466,   679,   591,  1345,   620,   209,  1027,  1521,
    1064,  1154,   591,   210,  1313,   367,  1034,  1030,  1021,   733,
    1594,   209,  1357,  1595,   401,  1040,   402,     3,   213,  1044,
       4,  1295,     5,   213,  1213,   918,   245,   246,   247,   864,
     519,  1222,   699,   700,  1396,  1445,  1502,   879,  1027,  1035,
     693,  1099,     6,     7,     8,     9,  1091,   730,  1021,   588,
     520,   673,   674,  1036,  1100,   696,  1101,   930,  1397,  1398,
     594,   595,   264,   521,   699,   700,     4,  1092,     5,   707,
     210,  1000,   864,   591,  1047,   214,   594,   595,   708,  1298,
     214,  1372,  1574,  1373,   210,   935,   936,  1048,  1292,  1103,
     467,   468,   212,     3,   469,   709,     4,  1037,     5,     4,
     215,     5,  1049,  1490,   604,   215,   699,   700,    55,    56,
      57,   727,  1376,  1377,  1378,   261,   262,   263,     6,     7,
       8,     9,  1507,     4,  1446,     5,  1444,  1508,   552,   732,
     213,   807,   735,   879,   879,   879,   879,   879,   553,   554,
     879,  1399,   596,   605,   606,   607,  1038,  1100,   266,  1101,
     267,   739,  1630,   382,   383,   384,   385,   754,   596,   212,
     834,  1400,   363,  1618,   879,   829,   369,   835,   405,   407,
     409,   411,   836,   212,   883,   522,   889,  1276,  1277,  1278,
    1279,   302,  1280,   879,   197,  1281,   746,   214,     4,   434,
       5,  1492,  1087,   441,   442,   443,   884,   213,   446,   890,
       3,   451,  1282,     4,   891,     5,   984,  1483,  1484,  1485,
     892,   213,   355,   893,     3,  1050,   268,     4,   920,     5,
     933,   202,  1479,  1480,  1481,     6,     7,     8,     9,   206,
     561,     3,   921,   207,     4,   922,     5,   938,   463,     6,
       7,     8,     9,   122,   932,   865,  1445,   964,   123,   124,
    1283,   965,  1160,   977,   214,   978,     6,     7,     8,     9,
     979,   562,   563,   125,   564,    70,   980,    71,   214,  1179,
    1180,  1027,    72,    73,    74,   982,    75,   742,   743,   355,
     988,  1021,   747,   748,   749,   750,   751,  1235,   992,    17,
      18,     3,    59,   355,     4,   997,     5,  1244,   676,   203,
    1404,  1405,  1406,  1250,  1407,  1252,  1253,  1001,   582,  1444,
    1531,  1532,  1533,   142,   143,   144,     6,     7,     8,     9,
    1428,   277,   278,   866,   832,   833,  1396,  1002,  1022,  1296,
    1020,  1297,   689,   690,   691,  1504,  1005,   209,    33,   583,
     584,   865,   865,   865,   865,   865,   202,    34,   865,   371,
    1397,  1398,   374,    35,   206,  1006,   879,   556,   207,  1429,
     692,   557,  1007,  1182,  1010,   667,   391,   371,   585,   480,
     481,   482,   865,  1012,   668,   669,  1017,    36,   670,   671,
     989,   990,   417,   713,   713,  1054,  1055,   719,  1094,  1095,
     864,   865,   558,   559,   879,   879,   879,   879,   879,   879,
     879,  1344,   879,   879,  1450,  1451,  1452,  1453,  1454,   453,
     210,  1284,   612,  1335,  1106,  1031,   459,  1107,  1032,   866,
     866,   866,   866,   866,   203,  1041,   866,   613,  1042,  1445,
     864,   870,   484,  1399,   485,   486,   487,  1000,     3,  1182,
    1043,     4,  1056,     5,  1057,  1353,  1058,  1354,   614,  1063,
     866,  1068,    76,  1400,   615,   902,   903,   904,  1148,  1149,
    1430,  -809,   209,     6,     7,     8,     9,    77,  1359,   866,
    1541,   245,   246,   247,   870,  -810,  1296,  1065,  1297,   914,
    1150,  1151,    78,   735,  1197,  1542,  1069,    79,   266,    80,
    1543,   267,  1544,   821,   822,   363,  1316,  1317,   879,   212,
    1066,   879,   616,   617,  1067,   692,  1071,  1173,  1096,   923,
    1072,    54,  1077,   202,   460,   461,   462,     3,  1642,  1078,
       4,   206,     5,   543,  1476,   207,   945,   946,   947,   948,
    1478,  1475,  1622,  1477,  1093,   210,  1097,   213,  1102,   544,
    1098,   879,     6,     7,     8,     9,  1392,  1393,   545,  1640,
    1121,  1489,  1131,     3,   546,   547,     4,  1113,     5,  1114,
     931,  1230,  1231,  1214,   865,  1214,  1214,  1214,  1132,  1214,
    1214,  1224,  1495,  1133,  1134,  1228,  1228,  1115,     6,     7,
       8,     9,   142,   143,   144,  1116,  1117,   202,  1122,   202,
    1154,   203,  1161,  1162,   214,   206,  1163,   206,  1123,   207,
    1164,   207,   865,   865,   865,   865,   865,   865,   865,  1422,
     865,   865,   279,   280,   281,   282,   283,   284,   202,   215,
     820,   821,   822,  1125,   212,   351,   206,  1129,  1146,   209,
     207,     3,  1147,  1152,     4,  1153,     5,  1265,  1135,  1285,
    1293,  1299,   866,     3,  1156,  1165,     4,   837,     5,  1266,
    1170,  1286,  1294,  1300,  1225,  1181,     6,     7,     8,     9,
     419,  1188,   213,   864,  1190,   203,  1192,   203,     6,     7,
       8,     9,   811,   812,   813,    17,    18,   408,   410,   412,
     866,   866,   866,   866,   866,   866,   866,  1194,   866,   866,
    1522,  1202,   202,  1182,  1209,  1207,   203,  1208,  1210,   351,
     206,  1212,   210,   209,   207,   209,   865,  1220,  1243,   865,
    1251,  1309,  1306,  1307,  1000,  1276,  1277,  1278,  1279,   214,
    1280,  1308,  1310,  1281,    33,  1315,   880,  1276,  1277,  1278,
    1279,  1311,  1280,    34,   209,  1281,   880,   880,  1325,    35,
    1282,  1329,  1322,  1342,   215,   622,  1330,   202,  1334,   865,
    1347,  1348,  1282,  1349,   351,   206,  1606,  1350,   623,   207,
     966,   967,   693,    36,  1352,   624,  1370,  1385,  1395,  1384,
     203,  1416,  1426,   968,   879,  1391,   210,  1412,   210,  1417,
    1427,   969,  1456,   625,   866,  1458,  1461,   866,  1283,   626,
     723,   212,  1022,  1471,  1472,  1486,  1379,   970,  1500,  1512,
    1283,  1498,  1386,  1387,  1388,  1506,  1514,   210,   209,  1516,
    1518,   202,   696,  1520,  1524,  1538,  1410,  1555,   351,   206,
    1527,  1567,  1528,   207,  1415,   203,  1529,   866,  1000,   213,
    1265,  1530,  1285,  1293,  1299,  1610,  1569,  1534,  1535,  1586,
    1536,  1537,  1266,   202,  1286,  1294,  1300,  1593,  1432,  1441,
    1447,   206,  1598,   704,  1626,   207,  1559,  1628,  1572,  1573,
    1433,  1442,  1448,   209,   202,   212,  1579,   212,  1580,  1581,
    1602,  1614,   206,   534,  1629,   535,   207,  1632,  1647,    67,
     896,   210,   971,   972,   973,   645,   214,  1301,  1414,   203,
    1540,  1631,   366,   536,   435,  1539,   212,  1627,   655,   656,
     657,   537,   538,   213,   539,   213,   387,   393,  1367,    17,
      18,   215,   894,   366,   540,   541,   740,  1510,  1487,  1488,
       3,   203,  1358,     4,  1033,     5,  1515,   209,   463,  1474,
    1079,  1491,  1517,  1466,   213,  1046,   210,  1493,  1340,  1015,
    1494,   731,   203,  1497,  1523,     6,     7,     8,     9,  1420,
    1463,  1462,  1432,  1441,  1447,  1217,  1070,  1218,    33,   209,
     214,  1604,   214,  1219,  1433,  1442,  1448,    34,  1221,   202,
     212,  1236,  1081,    35,  1233,  1076,   351,   206,   202,   204,
     209,   207,   865,   367,  1130,   215,   206,   215,   712,   665,
     207,   214,  1201,  1613,   888,   905,  1621,    36,   907,  1553,
     210,  1625,   908,   433,   367,  1288,  1648,  1289,   213,  1280,
     489,   490,  1281,  1617,   906,   871,   355,   716,   491,   492,
     493,   494,   495,   725,   127,   212,   128,   721,  1554,  1290,
    1558,   129,   210,   130,   726,   963,     0,   131,  1560,  1561,
    1562,  1563,  1564,  1565,  1566,     0,  1568,   203,     0,     0,
       0,     0,     0,   210,     0,     0,   203,     0,     0,     0,
     866,     0,     0,   213,     0,   214,     0,     0,     0,     0,
    1588,  1589,  1590,  1591,  1592,     0,   132,  1291,   133,     0,
       0,     0,   437,     0,   202,   209,     0,     0,     0,   212,
     355,   351,   206,   439,   209,     0,   207,    17,    18,     0,
       0,     0,     0,     0,     0,  1285,  1293,  1299,    17,    18,
       0,  1611,  1615,  1619,  1623,   880,     0,  1286,  1294,  1300,
     214,   212,     0,  1612,  1616,  1620,  1624,   213,     0,     0,
    1635,     0,  1636,  1637,  1638,  1639,  1432,  1441,  1447,  1643,
    1137,     0,   212,  1644,     0,   355,    33,  1645,  1433,  1442,
    1448,  1646,     0,     0,     0,    34,     0,    33,   210,   213,
       0,    35,   203,  1649,   587,     0,    34,   210,     0,  1650,
    1651,  1652,    35,  1138,     0,   588,     0,   589,     0,    84,
     213,    85,     0,    86,   214,    36,    87,    88,    89,  1239,
      90,     0,     0,     0,     0,   590,    36,     0,     0,   591,
     209,     0,   592,     0,   996,     0,     0,     0,     0,   355,
       0,   880,   880,   880,   880,   880,   214,     0,   880,     0,
       0,  1013,  1014,     0,  1016,     0,  1018,  1019,     0,  1139,
    1140,  1141,  1142,  1143,  1144,     0,     0,   214,  1421,     0,
       3,   215,   880,     4,     0,     5,     0,   212,     0,   593,
    1051,     0,     0,  1053,     0,     0,   212,     0,     0,     0,
       0,   880,   215,     0,     0,     6,     7,     8,     9,     0,
       0,     0,     0,   210,     3,     0,     0,     4,     0,     5,
     444,   594,   595,  1254,     0,   213,     0,     0,  1255,     0,
    1256,     0,  1257,     0,   213,    17,    18,     0,     0,     6,
       7,     8,     9,   681,     0,   682,     0,   683,   684,     0,
       0,  1074,     0,     0,  1075,   685,   686,  1254,     0,     0,
       0,    49,  1255,     0,  1256,     0,  1257,     0,     0,     0,
      58,    49,    49,    61,    61,    61,    65,     0,     0,    49,
       0,   511,   214,   512,    33,     0,     0,     0,   687,     0,
       0,   214,     0,    34,     0,  1363,  1365,  1365,  1368,    35,
       0,   513,   212,   596,     0,     0,    91,   355,     0,   514,
     515,   516,   517,     0,     0,     0,   215,  1104,  1105,     0,
       0,    92,     0,    36,     0,     0,     0,     0,    49,     0,
     373,    49,    61,    61,    61,    65,    93,  1258,     0,     0,
     213,    94,    49,    95,   388,   390,    49,   394,    61,    61,
      65,     0,   404,   404,   404,   404,     0,    61,     0,   414,
       0,    49,     0,     0,    61,    61,     0,     0,     0,    61,
       0,  1258,     0,  1215,   880,  1215,  1215,  1215,     3,  1215,
    1215,     4,     0,     5,     0,  1229,  1229,   452,    49,    61,
      61,     0,     0,    61,     0,    49,     0,   214,     0,     0,
       0,     0,     0,     6,     7,     8,     9,     0,  1259,     0,
       0,     0,   880,   880,   880,   880,   880,   880,   880,     0,
     880,   880,   355,  1260,     0,     0,     0,  1169,     0,     0,
       0,  1172,     0,     0,     0,     0,   447,     0,  1261,  1185,
    1186,  1187,  1259,  1262,  1189,  1263,  1191,  -766,     0,     0,
       0,    17,    18,     0,  1195,     3,     0,  1260,     4,     0,
       5,     0,     0,  1288,     0,  1289,     0,  1280,     0,   449,
    1281,     0,  1261,     0,   497,   498,     0,  1262,   499,  1263,
       6,     7,     8,     9,    17,    18,  1211,  1290,   500,   501,
     502,   503,   504,   505,   506,   507,   508,  1226,  1264,  1227,
      33,     3,     0,     0,     4,  1232,     5,  1234,     0,    34,
       0,     0,     0,     0,     0,    35,   880,     0,     0,   880,
       0,     0,  -767,     0,     0,     0,     6,     7,     8,     9,
       0,     0,  1418,    33,     0,  1291,   509,     0,     0,    36,
    1435,     0,    34,     0,     0,     0,     0,  1436,    35,   524,
     525,     0,     0,     3,     0,     0,     4,     0,     5,   880,
       0,     0,     0,   526,     0,   527,   528,   529,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     6,     7,
       8,     9,     0,  1437,     0,     0,  1435,     0,   530,   531,
     532,     0,     0,  1436,   524,   525,     0,     0,     0,     0,
       0,     0,     0,     0,  1327,  1328,     0,     0,   526,     0,
     527,   528,   529,     0,     0,     0,  1438,     0,     0,     0,
       0,     0,     0,     0,  1337,     0,     0,     0,  1341,  1437,
       0,     0,     0,   530,   531,   532,   497,   498,  1435,     0,
     499,     0,     0,     0,     3,  1436,  1351,     4,     0,     5,
     500,   501,   502,   503,   504,   505,   506,   507,   508,     0,
       0,     0,  1438,     0,     0,     0,   137,     0,     0,     6,
       7,     8,     9,   138,   139,     0,   274,   140,   275,   917,
       0,  1437,     0,     0,  1439,    61,     0,     0,     0,     0,
       0,     0,   276,     0,     0,   924,  1605,   925,   509,   926,
       0,     0,   277,   278,   927,     0,     0,   928,     0,   929,
       0,     0,     0,     0,  1438,     0,     0,    61,   279,   280,
     281,   282,   283,   284,     0,     0,     0,     0,     0,     0,
    1439,     0,     0,  1268,     0,     0,     0,   285,     0,   286,
       0,     0,   141,   142,   143,   144,     0,     0,   145,     0,
     146,     0,     0,  1269,   147,     0,     0,     0,   148,     0,
       0,     0,     0,  1459,   149,     0,     0,     0,     0,     0,
       0,     0,     0,  1440,     0,     0,  1464,     0,     0,     0,
     150,     0,  1439,     0,     0,   151,  1467,     0,   152,     0,
       0,     0,   880,   153,     0,     0,   154,     0,     0,   155,
     156,     0,     0,   157,     0,     0,   158,     0,   159,    10,
       0,    11,     0,    12,     0,     0,    13,    14,    15,  1503,
      16,     0,     0,     0,    17,    18,     0,     0,     0,     0,
       0,   160,   161,     0,   162,   163,   164,   165,     0,     0,
       0,     0,     0,   166,   167,     0,     0,   168,   169,   287,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
       0,  1641,   288,    33,     0,     0,     0,   566,     0,     0,
       0,     0,    34,     0,     0,     0,   567,   289,    35,     0,
       0,     0,     0,     0,     0,     0,   290,     0,     0,     0,
       0,   568,   291,     0,     0,   569,     0,   292,   570,   571,
       0,     0,    36,   572,   573,   574,   575,   576,     0,   293,
       0,     0,   294,   295,   296,   297,     0,     0,     0,   298,
       0,     0,     0,   299,   300,   192,     0,     0,     0,   193,
     194,     3,     0,     0,     4,     0,     5,     0,   301,     0,
       0,   195,   196,     0,     0,     0,     0,     0,     0,     0,
       0,   302,  1270,   137,   197,   198,     6,     7,     8,     9,
     138,   139,     0,   274,   140,   275,     0,     0,     0,     0,
       0,     0,     0,     0,   638,   639,     0,     0,     0,   276,
       0,     0,     0,     0,     0,     0,    37,     0,     0,   277,
     278,     0,     0,     0,     0,   640,     0,     0,     0,     0,
       0,    38,     0,     0,     0,   279,   280,   281,   282,   283,
     284,     0,     0,     0,     0,     0,    39,     0,     0,     0,
    1268,    40,     0,    41,   285,     0,   286,     0,     0,   141,
     142,   143,   144,     0,     0,   145,     0,   146,     0,     0,
    1269,   147,     0,     0,     0,   148,     0,     0,     0,   950,
       0,   149,   951,   952,   953,   954,   955,   956,   957,   958,
     959,   960,   961,     0,     0,     0,     0,   150,     0,     0,
       0,     0,   151,   641,     0,   152,     0,     0,     0,     0,
     153,     0,     0,   154,     0,     0,   155,   156,     0,     0,
     157,     0,     0,   158,     0,   159,   642,   643,   644,   645,
     646,   647,     0,   648,   649,   650,   651,   652,   653,   654,
       0,     0,   655,   656,   657,     0,     0,     0,   160,   161,
       0,   162,   163,   164,   165,     0,     0,     0,     0,     0,
     166,   167,     0,     0,   168,   169,   287,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,     0,     0,   288,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1126,  1127,  1128,     0,   289,     0,     0,     0,     0,     0,
       0,     0,     0,   290,     0,     0,     0,     0,     0,   291,
       0,     0,     0,     0,   292,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   293,     0,     0,   294,
     295,   296,   297,     0,     0,     0,   298,     0,     0,     0,
     299,   300,   192,     0,     0,     0,   193,   194,     3,     0,
       0,     4,     0,     5,     0,   301,     0,     0,   195,   196,
       0,     0,     0,     0,     0,     0,     0,     0,   302,  1419,
     137,   197,   198,     6,     7,     8,     9,   138,   139,     0,
     274,   140,   275,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   276,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   277,   278,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   279,   280,   281,   282,   283,   284,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1268,     0,     0,
       0,   285,     0,   286,     0,     0,   141,   142,   143,   144,
       0,     0,   145,     0,   146,     0,     0,  1269,   147,     0,
       0,     0,   148,     0,     0,     0,     0,     0,   149,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150,     0,     0,     0,     0,   151,
       0,     0,   152,     0,     0,     0,     0,   153,     0,     0,
     154,     0,     0,   155,   156,     0,     0,   157,     0,     0,
     158,     0,   159,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   160,   161,     0,   162,   163,
     164,   165,     0,     0,     0,     0,     0,   166,   167,     0,
       0,   168,   169,   287,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,     0,     0,   288,     0,   756,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   289,     0,     0,   757,     0,   137,     0,     0,     0,
     290,     0,     0,     0,   139,     0,   291,   140,     0,     0,
       0,   292,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   293,     0,     0,   294,   295,   296,   297,
       0,     0,     0,   298,     0,     0,     0,   299,   300,   192,
     758,     0,     0,   193,   194,     0,     0,     0,     0,     0,
       0,     0,   301,     0,   759,   195,   196,     0,     0,     0,
       0,     0,     0,     0,     0,   302,  1603,     0,   197,   198,
       0,     0,   141,   142,   143,   144,     0,     0,   145,     0,
     760,     0,     0,     0,   761,     0,     0,     0,   762,     0,
       0,     0,     0,     0,   763,     0,     0,     0,   764,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     150,     0,     0,     0,     0,   151,     0,     0,   765,     0,
       0,     0,     0,   153,     0,     0,   154,     0,     0,   155,
     156,     0,     0,   157,     0,     0,   158,     0,   159,     0,
       0,   993,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   757,     0,   137,
       0,   160,   161,     0,   766,     0,     0,   139,     0,     0,
     140,     0,     0,     0,     0,     0,     0,     0,     0,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
       0,     0,   191,   758,     0,     0,     0,     0,     0,     0,
       0,     0,   767,     0,     0,   768,   769,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   141,   142,   143,   144,     0,
       0,   145,     0,   760,     0,     0,     0,   761,     0,     0,
       0,   762,   770,   771,     0,     0,     0,   994,     0,     0,
       0,   764,     0,     0,     0,   192,     0,     0,     0,   193,
     194,     0,     0,   150,     0,     0,     0,     0,   151,   772,
     773,   995,   634,     0,     0,     0,   153,     0,     0,   154,
       0,     0,   155,   156,   197,     0,   157,     0,     0,   158,
       0,   159,     0,     0,  1052,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     757,     0,   137,     0,   160,   161,     0,   766,     0,     0,
     139,     0,     0,   140,     0,     0,     0,     0,     0,     0,
       0,     0,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,     0,     0,   191,   758,     0,     0,     0,
       0,     0,     0,     0,     0,   767,     0,     0,   768,   769,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   141,   142,
     143,   144,     0,     0,   145,     0,   760,     0,     0,     0,
     761,     0,     0,     0,   762,   770,   771,     0,     0,     0,
     994,     0,     0,     0,   764,     0,     0,     0,   192,     0,
       0,     0,   193,   194,     0,     0,   150,     0,     0,     0,
       0,   151,   772,   773,   995,   634,     0,     0,     0,   153,
       0,     0,   154,     0,     0,   155,   156,   197,     0,   157,
       0,     0,   158,     0,   159,     0,     0,  1073,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   757,     0,   137,     0,   160,   161,     0,
     766,     0,     0,   139,     0,     0,   140,     0,     0,     0,
       0,     0,     0,     0,     0,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,     0,     0,   191,   758,
       0,     0,     0,     0,     0,     0,     0,     0,   767,     0,
       0,   768,   769,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   141,   142,   143,   144,     0,     0,   145,     0,   760,
       0,     0,     0,   761,     0,     0,     0,   762,   770,   771,
       0,     0,     0,   994,     0,     0,     0,   764,     0,     0,
       0,   192,     0,     0,     0,   193,   194,     0,     0,   150,
       0,     0,     0,     0,   151,   772,   773,   995,   634,     0,
       0,     0,   153,     0,     0,   154,     0,     0,   155,   156,
     197,     0,   157,     0,     0,   158,     0,   159,     0,     0,
    1171,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   757,     0,   137,     0,
     160,   161,     0,   766,     0,     0,   139,     0,     0,   140,
       0,     0,     0,     0,     0,     0,     0,     0,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,     0,
       0,   191,   758,     0,     0,     0,     0,     0,     0,     0,
       0,   767,     0,     0,   768,   769,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   141,   142,   143,   144,     0,     0,
     145,     0,   760,     0,     0,     0,   761,     0,     0,     0,
     762,   770,   771,     0,     0,     0,   994,     0,     0,     0,
     764,     0,     0,     0,   192,     0,     0,     0,   193,   194,
       0,     0,   150,     0,     0,     0,     0,   151,   772,   773,
     995,   634,     0,     0,     0,   153,     0,     0,   154,     0,
       0,   155,   156,   197,     0,   157,     0,     0,   158,     0,
     159,     0,     0,     0,     0,     0,     0,   840,   841,   842,
     843,   844,   845,     0,     0,     0,     0,     0,     0,   757,
       0,   827,     0,   160,   161,     0,   766,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,     0,     0,   191,   758,    99,   100,   101,   102,
       0,     0,   103,   104,   767,   105,   106,   768,   769,   107,
       0,     0,     0,     0,     0,     0,     0,     0,   757,     0,
     827,     0,     0,     0,     0,     0,     0,   141,   142,   143,
     144,     0,     0,     0,     0,   846,     0,     0,     0,   847,
       0,     0,     0,   848,   770,   771,     0,     0,   108,   849,
     109,   110,   111,   764,     0,     0,     0,   192,     0,     0,
       0,   193,   194,     0,   758,   850,     0,   827,     0,     0,
     851,   772,   773,   852,   634,     0,     0,     0,   853,     0,
       0,   854,     0,     0,   855,   856,   197,     0,   857,     0,
       0,   858,     0,   859,     0,     0,   141,   142,   143,   144,
       0,     0,     0,     0,   846,     0,     0,     0,   847,     0,
       0,   758,   848,     0,     0,     0,   860,   861,   849,     0,
       0,     0,   764,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   850,     0,     0,     0,     0,   851,
       0,     0,   852,     0,   142,   143,   144,   853,     0,     0,
     854,   846,     0,   855,   856,   847,     0,   857,     0,   848,
     858,     0,   859,     0,     0,   849,     0,   767,     0,   764,
     768,   769,     0,     0,     0,     0,     0,     0,   757,     0,
     827,     0,     0,   112,     0,   860,   861,     0,     0,   852,
       0,     0,     0,     0,     0,     0,     0,     0,   113,     0,
       0,     0,     0,   114,   115,   116,     0,   770,   771,     0,
     862,     0,     0,   117,     0,     0,     0,     0,   118,     0,
     119,   120,     0,     0,   758,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   772,   773,   767,     0,     0,   768,
     769,     0,     0,     0,     0,     0,   302,     0,     0,   197,
     863,     0,     0,     0,     0,     0,   141,   142,   143,   144,
       0,     0,     0,     0,   846,     0,   628,     0,   847,     0,
       0,     0,   848,     0,     0,     0,   770,   771,   849,   862,
       0,     0,   764,   767,     0,     0,   768,   769,     0,     0,
       0,     0,   629,     0,   850,   630,     0,     0,     0,   851,
       0,     0,   852,   772,   773,     0,     0,   853,     0,     0,
     854,     0,   631,   855,   856,   302,     0,   857,   197,   863,
     858,     0,   859,   770,   771,     0,   757,     0,   137,     0,
       0,     0,     0,     0,     0,     0,   139,     0,     0,   140,
       0,     0,     0,     0,     0,   860,   861,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   197,     0,     0,     0,     0,
       0,     0,   758,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,     0,     0,     0,   767,     0,     0,   768,
     769,     0,     0,     0,   141,   142,   143,   144,     0,     0,
     145,     0,   760,     0,     0,     0,   761,     0,     0,     0,
     762,     0,     0,     0,     0,     0,   994,     0,     0,     0,
     764,     0,   632,     0,     0,     0,   770,   771,     0,   862,
       0,     0,   150,     0,     0,     0,     0,   151,     0,   633,
     995,     0,     0,     0,     0,   153,     0,     0,   154,     0,
       0,   155,   156,   772,   773,   157,     0,     0,   158,     0,
     159,     0,     0,     0,     0,   634,     0,     0,   197,   863,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   160,   161,     0,   766,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,     0,     0,   191,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   767,     0,     0,   768,   769,     0,
     722,   137,     0,     0,     0,     0,     0,     0,   138,   139,
       0,   274,   140,   275,     0,     0,     0,     0,     0,     0,
       0,     0,   638,   639,     0,     0,     0,   276,     0,     0,
       0,     0,     0,     0,   770,   771,     0,   277,   278,     0,
       0,     0,     0,   640,     0,     0,     0,   192,     0,     0,
       0,   193,   194,   279,   280,   281,   282,   283,   284,     0,
       0,   772,   773,     0,   634,     0,     0,     0,     0,     0,
       0,     0,   285,     0,   286,     0,   197,   141,   142,   143,
     144,     0,     0,   145,     0,   146,     0,     0,     0,   147,
       0,     0,     0,   148,     0,     0,     0,   723,     0,   149,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,     0,     0,     0,     0,
     151,   641,     0,   152,     0,     0,     0,     0,   153,     0,
       0,   154,     0,     0,   155,   156,     0,     0,   157,     0,
       0,   158,     0,   159,   642,   643,   644,   645,   646,   647,
     724,   648,   649,   650,   651,   652,   653,   654,     0,     0,
     655,   656,   657,     0,     0,     0,   160,   161,     0,   162,
     163,   164,   165,     0,     0,     0,     0,     0,   166,   167,
       0,     0,   168,   169,   287,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,     0,     0,   288,     0,     0,
       0,     0,     0,   137,     0,     0,     0,     0,     0,     0,
     138,   139,   289,     0,   140,     0,     0,     0,     0,     0,
       0,   290,     0,     0,     0,     0,     0,   291,     0,     0,
       0,     0,   292,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   293,     0,     0,   294,   295,   296,
     297,     0,     0,     0,   298,     0,     0,     0,   299,   300,
     192,     0,     0,     0,   193,   194,     0,     0,     0,     0,
       0,     0,     0,   301,     0,     0,   195,   196,     0,   141,
     142,   143,   144,     0,     0,   145,   302,   146,     0,   197,
     198,   147,     0,     0,     0,   148,     0,     0,     0,     0,
       0,   149,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   150,     0,     0,
       0,     0,   151,     0,     0,   152,     0,     0,     0,     0,
     153,     0,     0,   154,     0,     0,   155,   156,     0,     0,
     157,   137,     0,   158,     0,   159,     0,     0,   138,   139,
       0,     0,   140,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   160,   161,
       0,   162,   163,   164,   165,     0,     0,     0,     0,     0,
     166,   167,     0,     0,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,     0,     0,   191,
       0,     0,     0,     0,     0,     0,     0,   141,   142,   143,
     144,     0,     0,   145,     0,   146,     0,     0,     0,   147,
       0,     0,     0,   148,     0,     0,     0,     0,     0,   149,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,     0,     0,     0,     0,
     151,     0,     0,   152,     0,     0,     0,     0,   153,     0,
       0,   154,   192,     0,   155,   156,   193,   194,   157,     0,
       0,   158,     0,   159,     0,     0,     0,     0,   195,   196,
       0,     0,     0,     0,     0,     0,     0,     0,   302,     0,
       0,   197,   198,     0,     0,     0,   160,   161,     0,   162,
     163,   164,   165,     0,   827,     0,     0,     0,   166,   167,
       0,     0,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,     0,     0,   191,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   758,     0,
       0,     0,     0,     0,     0,     0,   279,   280,   281,   282,
     283,   284,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   827,     0,     0,     0,     0,
     141,   142,   143,   144,     0,     0,     0,     0,   846,     0,
       0,     0,   847,     0,     0,     0,   848,     0,     0,     0,
     192,     0,   849,     0,   193,   194,   764,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   195,   196,   850,   758,
       0,     0,     0,   851,     0,     0,   852,     0,     0,   197,
     198,   853,     0,     0,   854,     0,     0,   855,   856,     0,
       0,   857,     0,     0,   858,     0,   859,     0,     0,     0,
       0,   141,   142,   143,   144,     0,     0,     0,     0,   846,
       0,     0,     0,   847,     0,     0,     0,   848,     0,   860,
     861,     0,     0,   849,     0,     0,     0,   764,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   850,
       0,     0,     0,     0,   851,     0,     0,   852,     0,     0,
       0,     0,   853,     0,     0,   854,     0,     0,   855,   856,
       0,     0,   857,     0,     0,   858,     0,   859,     0,     0,
     767,     0,     0,   768,   769,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   137,     0,     0,     0,     0,
     860,   861,     0,   139,     0,     0,   140,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     770,   771,     0,   862,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   758,
       0,     0,     0,     0,     0,     0,     0,   772,   773,     0,
       0,   767,     0,     0,   768,   769,     0,     0,     0,     0,
       0,     0,   197,   863,     0,     0,     0,     0,     0,     0,
       0,   141,   142,   143,   144,     0,     0,   145,     0,   760,
       0,     0,     0,   761,     0,     0,     0,   762,     0,     0,
       0,   770,   771,   994,   862,     0,     0,   764,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
       0,     0,     0,     0,   151,     0,     0,   995,   772,   773,
       0,   720,   153,     0,     0,   154,     0,     0,   155,   156,
       0,     0,   157,   197,   863,   158,     0,   159,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   629,     0,     0,
     630,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     160,   161,     0,   766,     0,     0,     0,   631,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,     0,
       0,   191,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   767,     0,     0,   768,   769,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,     0,     0,
       0,   770,   771,     0,     0,     0,     2,     3,     0,     0,
       4,     0,     5,     0,   192,     0,     0,     0,   193,   194,
       0,     0,     0,     0,     0,     0,     0,     0,   772,   773,
       0,   634,     6,     7,     8,     9,     0,   632,     0,     0,
       0,     0,     0,   197,     0,     0,     0,     0,    10,     0,
      11,     0,    12,     0,   633,    13,    14,    15,     0,    16,
       0,     0,     0,    17,    18,    19,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
     634,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -285,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,     0,     0,     0,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    39,     0,     0,     0,     0,
      40,     0,    41
};

static const yytype_int16 yycheck[] =
{
       1,   263,     3,   375,   736,   305,   376,   347,    29,   378,
     327,   374,     1,   377,   736,   274,    29,   357,   358,    31,
      29,   347,   193,   198,   347,  1111,  1114,   397,  1017,  1116,
      51,   357,   358,  1115,    63,    23,  1117,    51,    51,    60,
       5,   300,    51,   413,    45,  1078,    60,    60,  1022,  1023,
    1308,    60,    53,    51,  1028,     7,    57,   100,     7,   102,
     103,   320,    60,   106,   107,  1306,     7,   110,   111,    42,
       7,   114,   115,   116,  1080,  1152,  1153,   120,  1197,  1307,
     123,   124,   834,  1290,    14,    15,    29,    32,   131,    75,
      76,  1024,   102,   103,    93,   835,   106,   107,   836,    86,
     110,   111,    89,    81,   114,   115,   116,    81,    51,    99,
     120,  1437,     4,   123,   124,  1089,    12,    60,   347,  1177,
    1175,   131,    20,   385,    29,    63,    20,    22,   357,   358,
      54,   658,    23,    86,   101,     1,   139,   122,     4,   245,
       6,  1199,    72,    73,    74,   100,    51,     8,   832,   833,
     100,    59,   155,   100,   260,    60,   170,    87,    88,    89,
      26,    27,    28,    29,     8,  1240,    54,    97,     5,   100,
     318,    54,   193,   321,   104,   105,    55,   198,     8,   109,
     193,   690,   691,    54,   193,   198,    82,    95,     1,   198,
      51,     4,    46,     6,    24,   110,   121,    29,   725,   129,
     130,   123,   100,   133,    99,   100,   100,    51,   100,   100,
     101,   102,   100,    26,    27,    28,    29,   100,  1304,    51,
     145,    51,  1277,  1278,    90,   283,   148,    75,    60,   100,
     155,     1,   244,  1288,     4,   293,     6,    46,   250,    86,
       1,  1567,    90,     4,    54,     6,   161,   162,    50,    55,
     193,  1184,    44,   282,   283,   198,    26,    27,    28,    29,
     245,   107,   207,   129,   100,    26,    27,    28,    29,    39,
     317,    41,   262,   287,   318,   121,     1,    90,  1336,     4,
     107,     6,   139,   236,   305,   238,    29,   144,   193,  1496,
     100,   305,   305,   198,   121,    86,   305,   247,   317,   252,
     247,    26,    27,    28,    29,   283,   284,   285,    51,   283,
     284,   285,   333,   318,   301,     1,   129,    60,     4,   318,
       6,    42,  1355,  1581,    29,    86,   347,    88,  1334,    90,
     318,    20,    93,    22,    86,   321,   357,   358,  1579,   128,
      26,    27,    28,    29,  1096,   318,    51,   376,   294,   110,
    1427,   372,  1580,  1472,   319,    60,    23,  1097,   372,   372,
    1098,   193,   305,   372,   230,   386,   198,   319,   397,  1343,
     319,  1055,   386,   386,   372,   299,   300,   386,   319,   196,
    1435,    29,   319,   426,   413,   110,   311,  1361,   386,   236,
     321,   238,   229,   902,   903,   904,   736,   158,  1473,     5,
     305,    86,     8,    51,   347,   914,    29,   244,    81,   347,
    1094,  1095,    60,    99,   357,   358,   426,   230,   196,   357,
     358,   316,   259,   302,   303,   304,   321,   264,    51,   372,
     321,    42,    43,   100,   101,   102,  1469,    60,   376,  1527,
     121,   123,  1529,   386,   141,   236,  1528,   238,   121,  1530,
     193,   161,   162,   319,   110,   198,    36,    37,    38,   397,
     141,   108,   109,   303,   145,  1197,   148,   372,  1200,  1458,
     787,   295,   145,   305,   298,   413,    74,   739,  1200,    81,
      22,   386,   319,    25,   236,   747,   238,     1,   193,   751,
       4,  1577,     6,   198,  1054,   425,   302,   303,   304,   839,
     110,  1061,   262,   263,   100,   230,   319,   736,  1240,   107,
     246,     7,    26,    27,    28,    29,   839,   245,  1240,   121,
     130,   315,   316,   121,    20,   260,    22,   457,   124,   125,
     227,   228,     0,   143,   262,   263,     4,   863,     6,    99,
     372,   712,   882,   145,   137,   193,   227,   228,    99,   319,
     198,   236,  1526,   238,   386,   211,   212,   150,   319,   882,
     207,   208,   305,     1,   211,    99,     4,   165,     6,     4,
     193,     6,   165,     8,   158,   198,   262,   263,     7,     8,
       9,   245,  1261,  1262,  1263,    39,    40,    41,    26,    27,
      28,    29,   160,     4,   319,     6,   110,   165,   148,    81,
     305,   181,     4,   832,   833,   834,   835,   836,   158,   159,
     839,   207,   309,   197,   198,   199,   214,    20,    47,    22,
      49,   301,  1596,    77,    78,    79,    80,   277,   309,   372,
      17,   227,    61,   319,   863,    42,    65,    18,    92,    93,
      94,    95,   320,   386,    49,   255,   318,    85,    86,    87,
      88,   318,    90,   882,   321,    93,   158,   305,     4,   113,
       6,     7,   837,   117,   118,   119,    49,   372,   122,   318,
       1,   125,   110,     4,   318,     6,   688,  1376,  1377,  1378,
     318,   386,   305,   318,     1,   278,    54,     4,    42,     6,
       8,   712,  1371,  1372,  1373,    26,    27,    28,    29,   712,
     130,     1,    42,   712,     4,    42,     6,   100,   137,    26,
      27,    28,    29,   244,     7,   736,   230,   324,   249,   250,
     158,   324,   981,   294,   372,   294,    26,    27,    28,    29,
      99,   161,   162,   264,   164,    42,   312,    44,   386,  1001,
    1002,  1473,    49,    50,    51,   323,    53,   246,   247,   372,
      99,  1473,   254,   255,   256,   257,   258,  1074,    99,    57,
      58,     1,    11,   386,     4,    81,     6,  1093,   197,   712,
      82,    83,    84,  1099,    86,  1101,  1102,    23,   130,   110,
    1479,  1480,  1481,   100,   101,   102,    26,    27,    28,    29,
      90,    59,    60,   736,    15,    16,   100,    23,   736,    39,
      81,    41,   256,   257,   258,   319,    49,   712,   106,   161,
     162,   832,   833,   834,   835,   836,   837,   115,   839,    68,
     124,   125,    71,   121,   837,    49,  1055,   126,   837,   129,
     259,   130,    49,  1004,    49,   191,    85,    86,   190,   108,
     109,   110,   863,    49,   200,   201,    99,   145,   204,   205,
     262,   263,   101,   282,   283,    15,    16,   286,    15,    16,
    1200,   882,   161,   162,  1093,  1094,  1095,  1096,  1097,  1098,
    1099,  1197,  1101,  1102,   271,   272,   273,   274,   275,   128,
     712,   319,   112,  1183,   885,    99,   135,   888,    99,   832,
     833,   834,   835,   836,   837,    99,   839,   127,    99,   230,
    1240,   839,   110,   207,   112,   113,   114,  1078,     1,  1080,
      99,     4,    17,     6,    18,  1232,   320,  1234,   148,     5,
     863,    99,   229,   227,   154,   379,   380,   381,   108,   109,
     230,     7,   837,    26,    27,    28,    29,   244,  1238,   882,
     244,   302,   303,   304,   882,     7,    39,    81,    41,   403,
     108,   109,   259,     4,     5,   259,    99,   264,   387,   266,
     264,   390,   266,   288,   289,   394,   108,   109,  1197,   712,
       7,  1200,   202,   203,     7,   404,     5,   998,    17,   433,
       7,   100,     7,  1004,   103,   104,   105,     1,   319,   318,
       4,  1004,     6,   123,  1366,  1004,   133,   134,   135,   136,
    1369,  1364,   319,  1367,     7,   837,    18,   712,     8,   139,
     320,  1240,    26,    27,    28,    29,    91,    92,   148,   319,
      99,  1391,   110,     1,   154,   155,     4,   318,     6,   318,
     459,  1066,  1067,  1054,  1055,  1056,  1057,  1058,   126,  1060,
    1061,  1062,  1412,   131,   132,  1066,  1067,   318,    26,    27,
      28,    29,   100,   101,   102,   318,   318,  1078,    99,  1080,
     295,  1004,   318,   318,   712,  1078,   318,  1080,    99,  1078,
     247,  1080,  1093,  1094,  1095,  1096,  1097,  1098,  1099,   319,
    1101,  1102,    75,    76,    77,    78,    79,    80,  1109,   712,
     287,   288,   289,    99,   837,  1109,  1109,    99,    99,  1004,
    1109,     1,    99,    99,     4,    99,     6,  1108,   196,  1110,
    1111,  1112,  1055,     1,    99,    99,     4,     8,     6,  1108,
       5,  1110,  1111,  1112,  1062,    99,    26,    27,    28,    29,
      42,    99,   837,  1473,    49,  1078,    99,  1080,    26,    27,
      28,    29,   283,   284,   285,    57,    58,    93,    94,    95,
    1093,  1094,  1095,  1096,  1097,  1098,  1099,    40,  1101,  1102,
    1460,   144,  1183,  1334,    67,   110,  1109,   110,   110,  1183,
    1183,     5,  1004,  1078,  1183,  1080,  1197,    99,   323,  1200,
      99,     7,   318,   318,  1355,    85,    86,    87,    88,   837,
      90,   318,   325,    93,   106,    99,   347,    85,    86,    87,
      88,   325,    90,   115,  1109,    93,   357,   358,   265,   121,
     110,     5,    99,    40,   837,   110,   100,  1238,   318,  1240,
       7,   100,   110,   100,  1238,  1238,   319,   100,   123,  1238,
     108,   109,   246,   145,     5,   130,   100,   100,    99,  1268,
    1183,   100,    99,   121,  1473,   317,  1078,   317,  1080,   317,
      99,   129,   261,   148,  1197,    99,   319,  1200,   158,   154,
     183,  1004,  1200,   319,     5,    39,  1267,   145,   318,    99,
     158,   146,  1273,  1274,  1275,   317,    99,  1109,  1183,   101,
     261,  1302,   260,    99,   319,   100,  1287,   100,  1302,  1302,
     318,   129,   318,  1302,  1295,  1238,   318,  1240,  1469,  1004,
    1301,   318,  1303,  1304,  1305,   319,    99,   318,   318,    40,
     318,   318,  1301,  1334,  1303,  1304,  1305,    99,  1319,  1320,
    1321,  1334,   100,  1585,  1586,  1334,   318,    99,   319,   319,
    1319,  1320,  1321,  1238,  1355,  1078,   318,  1080,   318,   318,
     246,   319,  1355,   110,    99,   112,  1355,     5,    99,    19,
     373,  1183,   230,   231,   232,   233,  1004,  1113,  1291,  1302,
    1492,  1596,  1391,   130,    42,  1490,  1109,  1587,   246,   247,
     248,   138,   139,  1078,   141,  1080,    84,    86,  1256,    57,
      58,  1004,   371,  1412,   151,   152,   304,  1430,  1389,  1390,
       1,  1334,  1237,     4,   744,     6,  1439,  1302,   827,  1361,
     829,  1402,  1445,  1347,  1109,   752,  1238,  1408,  1193,   729,
    1411,   292,  1355,  1414,  1462,    26,    27,    28,    29,   319,
    1339,  1338,  1423,  1424,  1425,  1056,   808,  1057,   106,  1334,
    1078,   319,  1080,  1058,  1423,  1424,  1425,   115,  1060,  1460,
    1183,  1077,   830,   121,  1072,   823,  1460,  1460,  1469,    29,
    1355,  1460,  1473,  1391,   933,  1078,  1469,  1080,   276,   193,
    1469,  1109,  1028,  1582,   358,   382,  1584,   145,   384,  1498,
    1302,  1585,   385,   112,  1412,    86,  1633,    88,  1183,    90,
     108,   109,    93,  1583,   383,   347,  1109,   283,   116,   117,
     118,   119,   120,   288,    42,  1238,    44,   287,  1499,   110,
    1501,    49,  1334,    51,   288,   597,    -1,    55,  1509,  1510,
    1511,  1512,  1513,  1514,  1515,    -1,  1517,  1460,    -1,    -1,
      -1,    -1,    -1,  1355,    -1,    -1,  1469,    -1,    -1,    -1,
    1473,    -1,    -1,  1238,    -1,  1183,    -1,    -1,    -1,    -1,
    1541,  1542,  1543,  1544,  1545,    -1,    94,   158,    96,    -1,
      -1,    -1,    42,    -1,  1575,  1460,    -1,    -1,    -1,  1302,
    1183,  1575,  1575,    42,  1469,    -1,  1575,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,  1576,  1577,  1578,    57,    58,
      -1,  1582,  1583,  1584,  1585,   736,    -1,  1576,  1577,  1578,
    1238,  1334,    -1,  1582,  1583,  1584,  1585,  1302,    -1,    -1,
    1601,    -1,  1603,  1604,  1605,  1606,  1607,  1608,  1609,  1610,
      93,    -1,  1355,  1614,    -1,  1238,   106,  1618,  1607,  1608,
    1609,  1622,    -1,    -1,    -1,   115,    -1,   106,  1460,  1334,
      -1,   121,  1575,  1634,   110,    -1,   115,  1469,    -1,  1640,
    1641,  1642,   121,   126,    -1,   121,    -1,   123,    -1,    42,
    1355,    44,    -1,    46,  1302,   145,    49,    50,    51,  1088,
      53,    -1,    -1,    -1,    -1,   141,   145,    -1,    -1,   145,
    1575,    -1,   148,    -1,   710,    -1,    -1,    -1,    -1,  1302,
      -1,   832,   833,   834,   835,   836,  1334,    -1,   839,    -1,
      -1,   727,   728,    -1,   730,    -1,   732,   733,    -1,   182,
     183,   184,   185,   186,   187,    -1,    -1,  1355,   319,    -1,
       1,  1334,   863,     4,    -1,     6,    -1,  1460,    -1,   195,
     756,    -1,    -1,   759,    -1,    -1,  1469,    -1,    -1,    -1,
      -1,   882,  1355,    -1,    -1,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,  1575,     1,    -1,    -1,     4,    -1,     6,
      42,   227,   228,    44,    -1,  1460,    -1,    -1,    49,    -1,
      51,    -1,    53,    -1,  1469,    57,    58,    -1,    -1,    26,
      27,    28,    29,    43,    -1,    45,    -1,    47,    48,    -1,
      -1,   817,    -1,    -1,   820,    55,    56,    44,    -1,    -1,
      -1,     1,    49,    -1,    51,    -1,    53,    -1,    -1,    -1,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    19,
      -1,   110,  1460,   112,   106,    -1,    -1,    -1,    88,    -1,
      -1,  1469,    -1,   115,    -1,  1254,  1255,  1256,  1257,   121,
      -1,   130,  1575,   309,    -1,    -1,   229,  1460,    -1,   138,
     139,   140,   141,    -1,    -1,    -1,  1469,   883,   884,    -1,
      -1,   244,    -1,   145,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    73,    74,    75,   259,   158,    -1,    -1,
    1575,   264,    82,   266,    84,    85,    86,    87,    88,    89,
      90,    -1,    92,    93,    94,    95,    -1,    97,    -1,    99,
      -1,   101,    -1,    -1,   104,   105,    -1,    -1,    -1,   109,
      -1,   158,    -1,  1054,  1055,  1056,  1057,  1058,     1,  1060,
    1061,     4,    -1,     6,    -1,  1066,  1067,   127,   128,   129,
     130,    -1,    -1,   133,    -1,   135,    -1,  1575,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    29,    -1,   229,    -1,
      -1,    -1,  1093,  1094,  1095,  1096,  1097,  1098,  1099,    -1,
    1101,  1102,  1575,   244,    -1,    -1,    -1,   993,    -1,    -1,
      -1,   997,    -1,    -1,    -1,    -1,    42,    -1,   259,  1005,
    1006,  1007,   229,   264,  1010,   266,  1012,    81,    -1,    -1,
      -1,    57,    58,    -1,  1020,     1,    -1,   244,     4,    -1,
       6,    -1,    -1,    86,    -1,    88,    -1,    90,    -1,    42,
      93,    -1,   259,    -1,   108,   109,    -1,   264,   112,   266,
      26,    27,    28,    29,    57,    58,  1052,   110,   122,   123,
     124,   125,   126,   127,   128,   129,   130,  1063,   319,  1065,
     106,     1,    -1,    -1,     4,  1071,     6,  1073,    -1,   115,
      -1,    -1,    -1,    -1,    -1,   121,  1197,    -1,    -1,  1200,
      -1,    -1,    81,    -1,    -1,    -1,    26,    27,    28,    29,
      -1,    -1,   319,   106,    -1,   158,   170,    -1,    -1,   145,
      86,    -1,   115,    -1,    -1,    -1,    -1,    93,   121,   108,
     109,    -1,    -1,     1,    -1,    -1,     4,    -1,     6,  1240,
      -1,    -1,    -1,   122,    -1,   124,   125,   126,    -1,    -1,
      -1,    -1,   145,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    -1,   129,    -1,    -1,    86,    -1,   147,   148,
     149,    -1,    -1,    93,   108,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1170,  1171,    -1,    -1,   122,    -1,
     124,   125,   126,    -1,    -1,    -1,   162,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1190,    -1,    -1,    -1,  1194,   129,
      -1,    -1,    -1,   147,   148,   149,   108,   109,    86,    -1,
     112,    -1,    -1,    -1,     1,    93,  1212,     4,    -1,     6,
     122,   123,   124,   125,   126,   127,   128,   129,   130,    -1,
      -1,    -1,   162,    -1,    -1,    -1,    23,    -1,    -1,    26,
      27,    28,    29,    30,    31,    -1,    33,    34,    35,   419,
      -1,   129,    -1,    -1,   230,   425,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,   435,   319,   437,   170,   439,
      -1,    -1,    59,    60,   444,    -1,    -1,   447,    -1,   449,
      -1,    -1,    -1,    -1,   162,    -1,    -1,   457,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
     230,    -1,    -1,    90,    -1,    -1,    -1,    94,    -1,    96,
      -1,    -1,    99,   100,   101,   102,    -1,    -1,   105,    -1,
     107,    -1,    -1,   110,   111,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,  1329,   121,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   319,    -1,    -1,  1342,    -1,    -1,    -1,
     137,    -1,   230,    -1,    -1,   142,  1352,    -1,   145,    -1,
      -1,    -1,  1473,   150,    -1,    -1,   153,    -1,    -1,   156,
     157,    -1,    -1,   160,    -1,    -1,   163,    -1,   165,    42,
      -1,    44,    -1,    46,    -1,    -1,    49,    50,    51,   319,
      53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    -1,
      -1,   188,   189,    -1,   191,   192,   193,   194,    -1,    -1,
      -1,    -1,    -1,   200,   201,    -1,    -1,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
      -1,   319,   229,   106,    -1,    -1,    -1,   130,    -1,    -1,
      -1,    -1,   115,    -1,    -1,    -1,   139,   244,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   253,    -1,    -1,    -1,
      -1,   154,   259,    -1,    -1,   158,    -1,   264,   161,   162,
      -1,    -1,   145,   166,   167,   168,   169,   170,    -1,   276,
      -1,    -1,   279,   280,   281,   282,    -1,    -1,    -1,   286,
      -1,    -1,    -1,   290,   291,   292,    -1,    -1,    -1,   296,
     297,     1,    -1,    -1,     4,    -1,     6,    -1,   305,    -1,
      -1,   308,   309,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   318,   319,    23,   321,   322,    26,    27,    28,    29,
      30,    31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,   109,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,   229,    -1,    -1,    59,
      60,    -1,    -1,    -1,    -1,   129,    -1,    -1,    -1,    -1,
      -1,   244,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,   259,    -1,    -1,    -1,
      90,   264,    -1,   266,    94,    -1,    96,    -1,    -1,    99,
     100,   101,   102,    -1,    -1,   105,    -1,   107,    -1,    -1,
     110,   111,    -1,    -1,    -1,   115,    -1,    -1,    -1,   168,
      -1,   121,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,    -1,    -1,    -1,    -1,   137,    -1,    -1,
      -1,    -1,   142,   207,    -1,   145,    -1,    -1,    -1,    -1,
     150,    -1,    -1,   153,    -1,    -1,   156,   157,    -1,    -1,
     160,    -1,    -1,   163,    -1,   165,   230,   231,   232,   233,
     234,   235,    -1,   237,   238,   239,   240,   241,   242,   243,
      -1,    -1,   246,   247,   248,    -1,    -1,    -1,   188,   189,
      -1,   191,   192,   193,   194,    -1,    -1,    -1,    -1,    -1,
     200,   201,    -1,    -1,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,    -1,    -1,   229,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     920,   921,   922,    -1,   244,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   253,    -1,    -1,    -1,    -1,    -1,   259,
      -1,    -1,    -1,    -1,   264,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   276,    -1,    -1,   279,
     280,   281,   282,    -1,    -1,    -1,   286,    -1,    -1,    -1,
     290,   291,   292,    -1,    -1,    -1,   296,   297,     1,    -1,
      -1,     4,    -1,     6,    -1,   305,    -1,    -1,   308,   309,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   318,   319,
      23,   321,   322,    26,    27,    28,    29,    30,    31,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,
      -1,    94,    -1,    96,    -1,    -1,    99,   100,   101,   102,
      -1,    -1,   105,    -1,   107,    -1,    -1,   110,   111,    -1,
      -1,    -1,   115,    -1,    -1,    -1,    -1,    -1,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,   142,
      -1,    -1,   145,    -1,    -1,    -1,    -1,   150,    -1,    -1,
     153,    -1,    -1,   156,   157,    -1,    -1,   160,    -1,    -1,
     163,    -1,   165,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   188,   189,    -1,   191,   192,
     193,   194,    -1,    -1,    -1,    -1,    -1,   200,   201,    -1,
      -1,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,    -1,    -1,   229,    -1,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   244,    -1,    -1,    21,    -1,    23,    -1,    -1,    -1,
     253,    -1,    -1,    -1,    31,    -1,   259,    34,    -1,    -1,
      -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   276,    -1,    -1,   279,   280,   281,   282,
      -1,    -1,    -1,   286,    -1,    -1,    -1,   290,   291,   292,
      67,    -1,    -1,   296,   297,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   305,    -1,    81,   308,   309,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   318,   319,    -1,   321,   322,
      -1,    -1,    99,   100,   101,   102,    -1,    -1,   105,    -1,
     107,    -1,    -1,    -1,   111,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,   125,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     137,    -1,    -1,    -1,    -1,   142,    -1,    -1,   145,    -1,
      -1,    -1,    -1,   150,    -1,    -1,   153,    -1,    -1,   156,
     157,    -1,    -1,   160,    -1,    -1,   163,    -1,   165,    -1,
      -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      -1,   188,   189,    -1,   191,    -1,    -1,    31,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
      -1,    -1,   229,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   239,    -1,    -1,   242,   243,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    99,   100,   101,   102,    -1,
      -1,   105,    -1,   107,    -1,    -1,    -1,   111,    -1,    -1,
      -1,   115,   279,   280,    -1,    -1,    -1,   121,    -1,    -1,
      -1,   125,    -1,    -1,    -1,   292,    -1,    -1,    -1,   296,
     297,    -1,    -1,   137,    -1,    -1,    -1,    -1,   142,   306,
     307,   145,   309,    -1,    -1,    -1,   150,    -1,    -1,   153,
      -1,    -1,   156,   157,   321,    -1,   160,    -1,    -1,   163,
      -1,   165,    -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    -1,   188,   189,    -1,   191,    -1,    -1,
      31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,    -1,    -1,   229,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   239,    -1,    -1,   242,   243,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,
     101,   102,    -1,    -1,   105,    -1,   107,    -1,    -1,    -1,
     111,    -1,    -1,    -1,   115,   279,   280,    -1,    -1,    -1,
     121,    -1,    -1,    -1,   125,    -1,    -1,    -1,   292,    -1,
      -1,    -1,   296,   297,    -1,    -1,   137,    -1,    -1,    -1,
      -1,   142,   306,   307,   145,   309,    -1,    -1,    -1,   150,
      -1,    -1,   153,    -1,    -1,   156,   157,   321,    -1,   160,
      -1,    -1,   163,    -1,   165,    -1,    -1,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,   188,   189,    -1,
     191,    -1,    -1,    31,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,    -1,    -1,   229,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,    -1,
      -1,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    99,   100,   101,   102,    -1,    -1,   105,    -1,   107,
      -1,    -1,    -1,   111,    -1,    -1,    -1,   115,   279,   280,
      -1,    -1,    -1,   121,    -1,    -1,    -1,   125,    -1,    -1,
      -1,   292,    -1,    -1,    -1,   296,   297,    -1,    -1,   137,
      -1,    -1,    -1,    -1,   142,   306,   307,   145,   309,    -1,
      -1,    -1,   150,    -1,    -1,   153,    -1,    -1,   156,   157,
     321,    -1,   160,    -1,    -1,   163,    -1,   165,    -1,    -1,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    -1,
     188,   189,    -1,   191,    -1,    -1,    31,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,    -1,
      -1,   229,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   239,    -1,    -1,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    99,   100,   101,   102,    -1,    -1,
     105,    -1,   107,    -1,    -1,    -1,   111,    -1,    -1,    -1,
     115,   279,   280,    -1,    -1,    -1,   121,    -1,    -1,    -1,
     125,    -1,    -1,    -1,   292,    -1,    -1,    -1,   296,   297,
      -1,    -1,   137,    -1,    -1,    -1,    -1,   142,   306,   307,
     145,   309,    -1,    -1,    -1,   150,    -1,    -1,   153,    -1,
      -1,   156,   157,   321,    -1,   160,    -1,    -1,   163,    -1,
     165,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    -1,   188,   189,    -1,   191,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,    -1,    -1,   229,    67,    42,    43,    44,    45,
      -1,    -1,    48,    49,   239,    51,    52,   242,   243,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,   101,
     102,    -1,    -1,    -1,    -1,   107,    -1,    -1,    -1,   111,
      -1,    -1,    -1,   115,   279,   280,    -1,    -1,    94,   121,
      96,    97,    98,   125,    -1,    -1,    -1,   292,    -1,    -1,
      -1,   296,   297,    -1,    67,   137,    -1,    23,    -1,    -1,
     142,   306,   307,   145,   309,    -1,    -1,    -1,   150,    -1,
      -1,   153,    -1,    -1,   156,   157,   321,    -1,   160,    -1,
      -1,   163,    -1,   165,    -1,    -1,    99,   100,   101,   102,
      -1,    -1,    -1,    -1,   107,    -1,    -1,    -1,   111,    -1,
      -1,    67,   115,    -1,    -1,    -1,   188,   189,   121,    -1,
      -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,   142,
      -1,    -1,   145,    -1,   100,   101,   102,   150,    -1,    -1,
     153,   107,    -1,   156,   157,   111,    -1,   160,    -1,   115,
     163,    -1,   165,    -1,    -1,   121,    -1,   239,    -1,   125,
     242,   243,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    -1,    -1,   229,    -1,   188,   189,    -1,    -1,   145,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,    -1,
      -1,    -1,    -1,   249,   250,   251,    -1,   279,   280,    -1,
     282,    -1,    -1,   259,    -1,    -1,    -1,    -1,   264,    -1,
     266,   267,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   306,   307,   239,    -1,    -1,   242,
     243,    -1,    -1,    -1,    -1,    -1,   318,    -1,    -1,   321,
     322,    -1,    -1,    -1,    -1,    -1,    99,   100,   101,   102,
      -1,    -1,    -1,    -1,   107,    -1,   100,    -1,   111,    -1,
      -1,    -1,   115,    -1,    -1,    -1,   279,   280,   121,   282,
      -1,    -1,   125,   239,    -1,    -1,   242,   243,    -1,    -1,
      -1,    -1,   126,    -1,   137,   129,    -1,    -1,    -1,   142,
      -1,    -1,   145,   306,   307,    -1,    -1,   150,    -1,    -1,
     153,    -1,   146,   156,   157,   318,    -1,   160,   321,   322,
     163,    -1,   165,   279,   280,    -1,    21,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    -1,   188,   189,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   321,    -1,    -1,    -1,    -1,
      -1,    -1,    67,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,    -1,    -1,    -1,   239,    -1,    -1,   242,
     243,    -1,    -1,    -1,    99,   100,   101,   102,    -1,    -1,
     105,    -1,   107,    -1,    -1,    -1,   111,    -1,    -1,    -1,
     115,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,
     125,    -1,   266,    -1,    -1,    -1,   279,   280,    -1,   282,
      -1,    -1,   137,    -1,    -1,    -1,    -1,   142,    -1,   283,
     145,    -1,    -1,    -1,    -1,   150,    -1,    -1,   153,    -1,
      -1,   156,   157,   306,   307,   160,    -1,    -1,   163,    -1,
     165,    -1,    -1,    -1,    -1,   309,    -1,    -1,   321,   322,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   188,   189,    -1,   191,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,    -1,    -1,   229,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   239,    -1,    -1,   242,   243,    -1,
      86,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,   279,   280,    -1,    59,    60,    -1,
      -1,    -1,    -1,   129,    -1,    -1,    -1,   292,    -1,    -1,
      -1,   296,   297,    75,    76,    77,    78,    79,    80,    -1,
      -1,   306,   307,    -1,   309,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    -1,    96,    -1,   321,    99,   100,   101,
     102,    -1,    -1,   105,    -1,   107,    -1,    -1,    -1,   111,
      -1,    -1,    -1,   115,    -1,    -1,    -1,   183,    -1,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,
     142,   207,    -1,   145,    -1,    -1,    -1,    -1,   150,    -1,
      -1,   153,    -1,    -1,   156,   157,    -1,    -1,   160,    -1,
      -1,   163,    -1,   165,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,    -1,    -1,
     246,   247,   248,    -1,    -1,    -1,   188,   189,    -1,   191,
     192,   193,   194,    -1,    -1,    -1,    -1,    -1,   200,   201,
      -1,    -1,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,    -1,    -1,   229,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,   244,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,   253,    -1,    -1,    -1,    -1,    -1,   259,    -1,    -1,
      -1,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   276,    -1,    -1,   279,   280,   281,
     282,    -1,    -1,    -1,   286,    -1,    -1,    -1,   290,   291,
     292,    -1,    -1,    -1,   296,   297,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   305,    -1,    -1,   308,   309,    -1,    99,
     100,   101,   102,    -1,    -1,   105,   318,   107,    -1,   321,
     322,   111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,
      -1,   121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,    -1,    -1,
      -1,    -1,   142,    -1,    -1,   145,    -1,    -1,    -1,    -1,
     150,    -1,    -1,   153,    -1,    -1,   156,   157,    -1,    -1,
     160,    23,    -1,   163,    -1,   165,    -1,    -1,    30,    31,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   188,   189,
      -1,   191,   192,   193,   194,    -1,    -1,    -1,    -1,    -1,
     200,   201,    -1,    -1,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,    -1,    -1,   229,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,   101,
     102,    -1,    -1,   105,    -1,   107,    -1,    -1,    -1,   111,
      -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,    -1,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,
     142,    -1,    -1,   145,    -1,    -1,    -1,    -1,   150,    -1,
      -1,   153,   292,    -1,   156,   157,   296,   297,   160,    -1,
      -1,   163,    -1,   165,    -1,    -1,    -1,    -1,   308,   309,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   318,    -1,
      -1,   321,   322,    -1,    -1,    -1,   188,   189,    -1,   191,
     192,   193,   194,    -1,    23,    -1,    -1,    -1,   200,   201,
      -1,    -1,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,    -1,    -1,   229,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      99,   100,   101,   102,    -1,    -1,    -1,    -1,   107,    -1,
      -1,    -1,   111,    -1,    -1,    -1,   115,    -1,    -1,    -1,
     292,    -1,   121,    -1,   296,   297,   125,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   308,   309,   137,    67,
      -1,    -1,    -1,   142,    -1,    -1,   145,    -1,    -1,   321,
     322,   150,    -1,    -1,   153,    -1,    -1,   156,   157,    -1,
      -1,   160,    -1,    -1,   163,    -1,   165,    -1,    -1,    -1,
      -1,    99,   100,   101,   102,    -1,    -1,    -1,    -1,   107,
      -1,    -1,    -1,   111,    -1,    -1,    -1,   115,    -1,   188,
     189,    -1,    -1,   121,    -1,    -1,    -1,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,
      -1,    -1,    -1,    -1,   142,    -1,    -1,   145,    -1,    -1,
      -1,    -1,   150,    -1,    -1,   153,    -1,    -1,   156,   157,
      -1,    -1,   160,    -1,    -1,   163,    -1,   165,    -1,    -1,
     239,    -1,    -1,   242,   243,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
     188,   189,    -1,    31,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     279,   280,    -1,   282,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,   307,    -1,
      -1,   239,    -1,    -1,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,   321,   322,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    99,   100,   101,   102,    -1,    -1,   105,    -1,   107,
      -1,    -1,    -1,   111,    -1,    -1,    -1,   115,    -1,    -1,
      -1,   279,   280,   121,   282,    -1,    -1,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,
      -1,    -1,    -1,    -1,   142,    -1,    -1,   145,   306,   307,
      -1,   100,   150,    -1,    -1,   153,    -1,    -1,   156,   157,
      -1,    -1,   160,   321,   322,   163,    -1,   165,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,
     129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     188,   189,    -1,   191,    -1,    -1,    -1,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,    -1,
      -1,   229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   239,    -1,    -1,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,    -1,    -1,
      -1,   279,   280,    -1,    -1,    -1,     0,     1,    -1,    -1,
       4,    -1,     6,    -1,   292,    -1,    -1,    -1,   296,   297,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,   307,
      -1,   309,    26,    27,    28,    29,    -1,   266,    -1,    -1,
      -1,    -1,    -1,   321,    -1,    -1,    -1,    -1,    42,    -1,
      44,    -1,    46,    -1,   283,    49,    50,    51,    -1,    53,
      -1,    -1,    -1,    57,    58,    59,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
     309,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,
      -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   115,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   145,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   229,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     244,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   259,    -1,    -1,    -1,    -1,
     264,    -1,   266
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   327,     0,     1,     4,     6,    26,    27,    28,    29,
      42,    44,    46,    49,    50,    51,    53,    57,    58,    59,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,   106,   115,   121,   145,   229,   244,   259,
     264,   266,   328,   330,   331,   332,   333,   393,   394,   395,
     397,   411,   328,   101,   100,   390,   390,   390,   395,   397,
     411,   395,   400,   400,   400,   395,   403,   333,    46,   334,
      42,    44,    49,    50,    51,    53,   229,   244,   259,   264,
     266,   335,    46,   336,    42,    44,    46,    49,    50,    51,
      53,   229,   244,   259,   264,   266,   337,    50,   338,    42,
      43,    44,    45,    48,    49,    51,    52,    55,    94,    96,
      97,    98,   229,   244,   249,   250,   251,   259,   264,   266,
     267,   339,   244,   249,   250,   264,   340,    42,    44,    49,
      51,    55,    94,    96,   341,    44,   342,    23,    30,    31,
      34,    99,   100,   101,   102,   105,   107,   111,   115,   121,
     137,   142,   145,   150,   153,   156,   157,   160,   163,   165,
     188,   189,   191,   192,   193,   194,   200,   201,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   229,   292,   296,   297,   308,   309,   321,   322,   350,
     391,   499,   500,   501,   502,   503,   507,   564,   567,   569,
     573,   578,   579,   581,   583,   593,   594,   596,   598,   600,
     602,   606,   608,   610,   612,   614,   616,   618,   620,   622,
     624,   628,   630,   632,   634,   635,   637,   639,   641,   643,
     645,   647,   649,   651,    55,   302,   303,   304,   343,   349,
      55,   344,   349,   100,   345,   346,    86,   236,   238,   395,
     405,   405,   405,   405,     0,   328,   390,   390,    54,   299,
     300,   408,   409,   410,    33,    35,    49,    59,    60,    75,
      76,    77,    78,    79,    80,    94,    96,   206,   229,   244,
     253,   259,   264,   276,   279,   280,   281,   282,   286,   290,
     291,   305,   318,   415,   416,   417,   418,   419,   420,   421,
     425,   426,   427,   430,   431,   438,   442,   447,   448,   450,
     451,   452,   453,   454,   472,   473,   475,   476,   478,   479,
     482,   483,   490,   491,   492,   493,   494,   497,   498,   502,
     509,   510,   511,   512,   513,   514,   518,   519,   520,   548,
     562,   567,   568,   591,   592,   593,   328,   317,   317,   328,
     351,   354,   415,   390,   356,   358,   499,   520,   361,   390,
     365,   397,   412,   395,   397,   400,   400,   400,   403,    86,
     236,   238,   405,   405,   405,   405,   411,   393,   395,   396,
     395,   397,   398,   412,   395,   400,   401,   400,   400,   403,
      86,   236,   238,   538,   395,   405,   406,   405,   406,   405,
     406,   405,   406,   400,   395,   394,   414,   397,   414,    42,
     414,   400,   400,   414,   414,    42,    43,   400,   414,   414,
      86,   236,   252,   538,   405,    42,   414,    42,   414,    42,
     414,   405,   405,   405,    42,   414,   405,    42,   414,    42,
     414,   405,   395,   397,   400,   400,   414,    42,   400,   397,
     103,   104,   105,   390,   595,   108,   109,   207,   208,   211,
     505,   506,    32,   207,   570,   128,   508,   161,   162,   633,
     108,   109,   110,   597,   110,   112,   113,   114,   599,   108,
     109,   116,   117,   118,   119,   120,   601,   108,   109,   112,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   170,
     603,   110,   112,   130,   138,   139,   140,   141,   607,   110,
     130,   143,   255,   609,   108,   109,   122,   124,   125,   126,
     147,   148,   149,   611,   110,   112,   130,   138,   139,   141,
     151,   152,   613,   123,   139,   148,   154,   155,   615,   139,
     155,   617,   148,   158,   159,   619,   126,   130,   161,   162,
     621,   130,   161,   162,   164,   623,   130,   139,   154,   158,
     161,   162,   166,   167,   168,   169,   170,   625,   110,   161,
     162,   629,   130,   161,   162,   190,   631,   110,   121,   123,
     141,   145,   148,   195,   227,   228,   309,   580,   582,   638,
     196,   640,   196,   642,   158,   197,   198,   199,   644,   123,
     148,   636,   112,   127,   148,   154,   202,   203,   646,   123,
     148,   648,   110,   123,   130,   148,   154,   650,   100,   126,
     129,   146,   266,   283,   309,   565,   566,   567,   108,   109,
     129,   207,   230,   231,   232,   233,   234,   235,   237,   238,
     239,   240,   241,   242,   243,   246,   247,   248,   584,   585,
     588,   283,   293,   572,   514,   519,   294,   191,   200,   201,
     204,   205,   652,   315,   316,   575,   390,   513,   349,   303,
     349,    43,    45,    47,    48,    55,    56,    88,   347,   405,
     405,   405,   390,   246,   532,   533,   260,   546,   547,   262,
     263,   439,   534,   535,   391,   536,   537,    99,    99,    99,
      81,   580,   491,   390,   499,   563,   563,    59,    95,   390,
     100,   565,    86,   183,   236,   584,   585,   245,   245,   260,
     245,   439,    81,    81,   580,     4,   329,   521,   522,   301,
     413,   419,   246,   247,   428,   429,   158,   254,   255,   256,
     257,   258,   432,   433,   277,   449,     5,    21,    67,    81,
     107,   111,   115,   121,   125,   145,   191,   239,   242,   243,
     279,   280,   306,   307,   457,   458,   459,   460,   461,   462,
     463,   465,   466,   467,   468,   469,   470,   471,   500,   501,
     507,   557,   558,   559,   564,   569,   573,   579,   580,   581,
     583,   589,   590,   593,    36,    37,    38,   181,   455,   456,
      81,   283,   284,   285,   474,   480,   481,    81,   477,   480,
     287,   288,   289,   484,   485,   486,   487,    23,   500,    42,
     495,   496,    15,    16,    17,    18,   320,     8,    24,    51,
       9,    10,    11,    12,    13,    14,   107,   111,   115,   121,
     137,   142,   145,   150,   153,   156,   157,   160,   163,   165,
     188,   189,   282,   322,   468,   500,   501,   515,   516,   517,
     520,   549,   550,   551,   552,   553,   554,   555,   556,   558,
     559,   560,   561,    49,    49,   531,   549,   550,   531,   318,
     318,   318,   318,   318,   408,   415,   351,   354,   356,   358,
     361,   365,   405,   405,   405,   533,   547,   535,   537,   415,
      54,    54,    54,   358,   405,    54,   358,   395,   400,   414,
      42,    42,    42,   405,   395,   395,   395,   395,   395,   395,
     400,   390,     7,     8,   110,   211,   212,   504,   100,   122,
     245,   107,   121,   107,   121,   133,   134,   135,   136,   604,
     168,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   626,   582,   324,   324,   108,   109,   121,   129,
     145,   230,   231,   232,   586,   587,   588,   294,   294,    99,
     312,   574,   323,   348,   349,   545,   545,   545,    99,   262,
     263,   443,    99,     5,   121,   145,   470,    81,   488,   489,
     514,    23,    23,    93,   318,    49,    49,    49,    99,   262,
      49,   588,    49,   470,   470,   443,   470,    99,   470,   470,
      81,   517,   520,   525,   526,   529,   555,   556,     7,   319,
     391,    99,    99,   429,    74,   107,   121,   165,   214,   435,
     391,    99,    99,    99,   391,   434,   433,   137,   150,   165,
     278,   470,     5,   470,    15,    16,    17,    18,   320,    20,
      22,     8,    51,     5,   480,    81,     7,     7,    99,    99,
     456,     5,     7,     5,   470,   470,   485,     7,   318,   390,
     318,   496,   560,   560,   551,   552,   553,   513,    23,   318,
     422,   550,   555,     7,    15,    16,    17,    18,   320,     7,
      20,    22,     8,   550,   470,   470,   328,   328,   353,   355,
     357,   362,   366,   318,   318,   318,   318,   318,   545,   545,
     545,    99,    99,    99,   545,    99,   395,   395,   395,    99,
     506,   110,   126,   131,   132,   196,   605,    93,   126,   182,
     183,   184,   185,   186,   187,   627,    99,    99,   108,   109,
     108,   109,    99,    99,   295,   571,    99,   155,   311,   576,
     580,   318,   318,   318,   247,    99,   100,   247,   440,   470,
       5,     5,   470,   500,    86,    89,   413,   527,   528,   391,
     391,    99,   514,   523,   524,   470,   470,   470,    99,   470,
      49,   470,    99,   440,    40,   470,   329,     5,   329,   527,
     329,   522,   144,   139,   144,   436,   437,   110,   110,    67,
     110,   470,     5,   457,   500,   559,   560,   458,   459,   460,
      99,   462,   457,   464,   500,   520,   470,   470,   500,   559,
     589,   589,   470,   481,   470,   480,   487,   488,   523,   390,
     329,   423,   424,   323,   555,   560,   560,   551,   552,   553,
     555,    99,   555,   555,    44,    49,    51,    53,   158,   229,
     244,   259,   264,   266,   319,   328,   330,   352,    90,   110,
     319,   328,   330,   381,   387,   415,    85,    86,    87,    88,
      90,    93,   110,   158,   319,   328,   330,   363,    86,    88,
     110,   158,   319,   328,   330,   363,    39,    41,   319,   328,
     330,   353,   355,   357,   362,   366,   318,   318,   318,     7,
     325,   325,   571,   298,   571,    99,   108,   109,   577,   376,
     377,   375,    99,    20,   100,   265,   441,   470,   470,     5,
     100,   392,   392,   528,   318,   419,   527,   470,    20,   100,
     441,   470,    40,   530,   555,   556,   562,     7,   100,   100,
     100,   470,     5,   480,   480,     5,   229,   319,   418,   419,
     525,     7,   319,   390,   399,   390,   402,   402,   390,   404,
     100,    86,   236,   238,   390,   407,   407,   407,   407,   328,
      75,    76,   388,   389,   499,   100,   328,   328,   328,   392,
     392,   317,    91,    92,   364,    99,   100,   124,   125,   207,
     227,   370,   371,   380,    82,    83,    84,    86,   359,   360,
     328,   392,   317,   371,   359,   328,   100,   317,   319,   319,
     319,   319,   319,   376,   377,   375,    99,    99,    90,   129,
     230,   319,   328,   330,   543,    86,    93,   129,   162,   230,
     319,   328,   330,   544,   110,   230,   319,   328,   330,   540,
     271,   272,   273,   274,   275,   446,   261,   445,    99,   470,
     523,   319,   446,   445,   470,   329,   437,   470,   488,     5,
     319,   319,     5,   329,   424,   354,   356,   361,   365,   407,
     407,   407,   372,   372,   372,   372,    39,   328,   328,   358,
       8,   328,     7,   328,   328,   358,     5,   328,   146,   382,
     318,   367,   319,   319,   319,   571,   317,   160,   165,   539,
     394,   392,    99,   539,    99,   394,   101,   394,   261,   444,
      99,   440,   419,   444,   319,   488,   562,   318,   318,   318,
     318,   372,   372,   372,   318,   318,   318,   318,   100,   370,
     360,   244,   259,   264,   266,   371,    22,    99,   100,   316,
     383,   384,   385,   499,   328,   100,   368,   369,   328,   318,
     328,   328,   328,   328,   328,   328,   328,   129,   328,    99,
     100,   247,   319,   319,   329,   355,   357,   362,   366,   318,
     318,   318,   373,   378,   374,   379,    40,   386,   328,   328,
     328,   328,   328,    99,    22,    25,     7,   319,   100,   541,
     542,   539,   246,   319,   319,   319,   319,   376,   377,   375,
     319,   328,   330,   532,   319,   328,   330,   546,   319,   328,
     330,   534,   319,   328,   330,   536,   391,   382,    99,    99,
     329,   369,     5,     7,   319,   328,   328,   328,   328,   328,
     319,   319,   319,   328,   328,   328,   328,    99,   542,   328,
     328,   328,   328
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   326,   327,   327,   328,   328,   329,   329,   330,   330,
     330,   330,   330,   331,   331,   331,   331,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     334,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   336,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   338,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   340,
     340,   340,   340,   340,   340,   341,   341,   341,   341,   341,
     341,   341,   342,   343,   343,   344,   344,   345,   346,   346,
     347,   347,   347,   347,   347,   347,   347,   347,   348,   348,
     349,   349,   349,   350,   351,   352,   353,   353,   353,   353,
     353,   353,   353,   353,   353,   353,   353,   353,   353,   353,
     353,   354,   355,   355,   355,   355,   355,   355,   356,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   358,
     358,   359,   359,   360,   360,   360,   360,   361,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     363,   363,   364,   364,   365,   366,   366,   366,   366,   366,
     367,   368,   368,   368,   369,   370,   371,   371,   372,   373,
     373,   373,   373,   374,   374,   374,   374,   375,   375,   375,
     375,   376,   376,   376,   376,   377,   377,   377,   377,   378,
     378,   378,   378,   379,   379,   379,   379,   380,   380,   380,
     380,   380,   381,   382,   383,   383,   384,   384,   384,   384,
     384,   385,   385,   386,   386,   387,   388,   388,   389,   389,
     390,   391,   391,   391,   392,   393,   393,   394,   394,   394,
     394,   394,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     411,   411,   411,   412,   413,   414,   414,   415,   415,   416,
     417,   417,   418,   418,   418,   418,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   420,   420,   421,   422,   422,
     423,   423,   423,   424,   425,   425,   426,   426,   427,   427,
     428,   428,   429,   429,   430,   430,   431,   432,   432,   433,
     433,   433,   433,   433,   433,   434,   435,   435,   435,   435,
     435,   436,   436,   437,   437,   438,   438,   438,   439,   439,
     439,   440,   440,   441,   441,   442,   442,   443,   443,   443,
     444,   444,   445,   445,   445,   446,   446,   446,   446,   446,
     447,   448,   449,   449,   449,   449,   449,   450,   451,   451,
     452,   452,   452,   452,   452,   452,   453,   453,   454,   455,
     455,   456,   456,   456,   456,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,   457,   458,   458,   458,
     459,   459,   460,   460,   461,   461,   462,   463,   463,   464,
     464,   465,   465,   466,   467,   468,   469,   469,   469,   470,
     470,   470,   471,   471,   471,   471,   471,   471,   471,   471,
     471,   472,   472,   473,   474,   474,   474,   475,   475,   476,
     477,   477,   477,   477,   477,   478,   478,   479,   479,   480,
     480,   481,   481,   481,   482,   482,   483,   484,   484,   485,
     485,   486,   486,   487,   487,   488,   488,   489,   490,   490,
     490,   491,   491,   492,   492,   493,   493,   494,   495,   495,
     496,   497,   497,   498,   499,   500,   500,   500,   501,   502,
     502,   502,   502,   502,   502,   502,   502,   502,   502,   502,
     502,   502,   502,   502,   503,   504,   504,   504,   505,   505,
     505,   505,   505,   506,   506,   507,   507,   508,   508,   509,
     509,   509,   510,   510,   511,   511,   512,   512,   513,   514,
     514,   515,   516,   517,   517,   517,   518,   519,   519,   519,
     520,   521,   521,   521,   522,   522,   522,   523,   523,   524,
     525,   525,   526,   527,   527,   528,   528,   528,   529,   529,
     530,   530,   531,   531,   532,   533,   534,   535,   536,   537,
     538,   538,   538,   539,   539,   540,   540,   541,   541,   542,
     543,   543,   543,   544,   544,   544,   544,   544,   545,   546,
     546,   547,   548,   548,   548,   549,   549,   550,   550,   550,
     551,   551,   551,   552,   552,   553,   553,   554,   554,   555,
     556,   556,   557,   557,   558,   559,   559,   559,   559,   559,
     559,   559,   559,   559,   559,   559,   559,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   561,   561,   561,   561,   561,   561,
     562,   562,   562,   562,   562,   562,   563,   563,   564,   564,
     564,   565,   565,   566,   566,   566,   566,   566,   567,   567,
     567,   567,   567,   567,   567,   567,   567,   567,   567,   567,
     567,   567,   567,   567,   567,   567,   567,   567,   567,   568,
     568,   568,   568,   568,   568,   569,   570,   570,   571,   571,
     572,   572,   573,   574,   574,   575,   575,   576,   576,   577,
     577,   578,   578,   579,   579,   579,   580,   580,   581,   581,
     582,   582,   582,   582,   583,   583,   583,   584,   584,   585,
     585,   585,   585,   585,   585,   585,   585,   585,   585,   585,
     585,   585,   585,   585,   586,   586,   586,   586,   586,   586,
     586,   587,   587,   587,   587,   588,   588,   588,   588,   589,
     589,   590,   590,   591,   591,   591,   591,   592,   593,   593,
     593,   593,   593,   593,   593,   593,   593,   593,   593,   593,
     593,   593,   593,   593,   593,   593,   594,   595,   595,   595,
     596,   597,   597,   597,   598,   599,   599,   599,   599,   600,
     601,   601,   601,   601,   601,   601,   601,   601,   601,   602,
     602,   602,   603,   603,   603,   603,   603,   603,   603,   603,
     603,   603,   603,   603,   604,   604,   604,   604,   605,   605,
     605,   605,   605,   606,   607,   607,   607,   607,   607,   607,
     607,   608,   609,   609,   609,   609,   610,   611,   611,   611,
     611,   611,   611,   611,   611,   611,   612,   613,   613,   613,
     613,   613,   613,   613,   613,   614,   615,   615,   615,   615,
     615,   616,   617,   617,   618,   619,   619,   619,   620,   621,
     621,   621,   621,   622,   623,   623,   623,   623,   624,   624,
     624,   625,   625,   625,   625,   625,   625,   625,   625,   625,
     625,   626,   626,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   627,   627,   627,   627,   627,   627,   627,
     627,   628,   629,   629,   629,   630,   631,   631,   631,   631,
     632,   633,   633,   634,   634,   634,   634,   634,   634,   634,
     634,   635,   636,   636,   637,   638,   638,   638,   638,   639,
     640,   641,   642,   643,   644,   644,   644,   644,   645,   646,
     646,   646,   646,   646,   646,   647,   648,   648,   649,   650,
     650,   650,   650,   650,   651,   652,   652,   652,   652,   652
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       5,     3,     2,     1,     1,     2,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     6,     2,     6,     3,     2,     6,     6,
       3,     6,     2,     3,     3,     7,     7,     7,     3,     3,
       3,     2,     6,     2,     6,     6,     6,     3,     6,     2,
       3,     3,     7,     7,     7,     3,     3,     3,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     2,     2,     2,
       2,     2,     4,     2,     2,     2,     2,     3,     2,     2,
       2,     2,     2,     3,     2,     2,     3,     2,     2,     3,
       2,     2,     3,     2,     2,     3,     2,     2,     3,     3,
       2,     2,     2,     2,     2,     3,     4,     4,     4,     2,
       3,     2,     2,     3,     2,     2,     2,     2,     2,     3,
       2,     2,     3,     2,     1,     2,     1,     3,     0,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     1,     2,     1,     0,     2,     0,     2,     2,     3,
       8,     8,     8,     8,     8,     8,     9,     9,     9,     8,
       8,     0,     0,     2,     2,     3,     3,     3,     0,     0,
       2,     2,     4,     4,     4,     4,     4,     2,     3,     1,
       1,     3,     1,     1,     1,     1,     1,     0,     0,     2,
       2,     4,     6,     6,     6,     6,     6,     4,     4,     3,
       2,     2,     1,     1,     0,     0,     2,     2,     5,     5,
       3,     1,     3,     3,     1,     1,     1,     3,     0,     0,
       2,     2,     2,     0,     2,     2,     2,     0,     2,     2,
       2,     0,     2,     2,     2,     0,     2,     2,     2,     0,
       2,     2,     2,     0,     2,     2,     2,     1,     1,     1,
       1,     1,     6,     2,     1,     1,     1,     1,     1,     3,
       3,     1,     2,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     2,     3,     1,     2,     3,
       1,     2,     1,     2,     3,     1,     2,     2,     2,     1,
       2,     2,     2,     2,     2,     0,     1,     1,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       1,     3,     3,     5,     3,     4,     1,     2,     1,     3,
       1,     2,     2,     2,     1,     2,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     1,     2,     2,     1,     1,
       1,     3,     1,     1,     1,     7,     6,     3,     1,     1,
       0,     1,     1,     0,     3,     5,     3,     1,     1,     0,
       0,     3,     0,     3,     3,     1,     1,     1,     1,     1,
       2,     1,     0,     4,     4,     4,     3,     2,     1,     1,
       3,     4,     4,     5,     6,     5,     1,     2,     1,     1,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     1,     3,     1,
       1,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     3,     4,     5,     2,     3,
       2,     2,     1,     1,     3,     4,     1,     2,     1,     1,
       2,     3,     1,     3,     4,     3,     5,     3,     6,     1,
       3,     1,     1,     1,     1,     2,     1,     1,     2,     2,
       1,     1,     3,     1,     1,     1,     2,     1,     4,     5,
       6,     1,     1,     7,     8,     6,     1,     1,     1,     2,
       2,     6,     8,     1,     2,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     3,     0,     2,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     1,
       3,     3,     3,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     3,     3,     3,     3,     5,     1,     2,     1,
       1,     2,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     3,     1,     3,     3,
       3,     6,     3,     3,     3,     3,     3,     3,     0,     6,
       5,     1,     2,     2,     3,     3,     3,     1,     1,     1,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     4,     1,     4,     4,     2,     1,     1,     0,     2,
       1,     1,     5,     2,     0,     1,     1,     1,     1,     1,
       1,     4,     5,     7,     5,     4,     1,     1,     2,     3,
       1,     1,     1,     1,     2,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     4,     4,     4,     5,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     6,     1,     1,     1,
       2,     1,     1,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     2,     1,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     2,     4,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     2,     1,     1,     1,     1,     2,
       4,     2,     1,     2,     1,     1,     1,     4,     2,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1
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
#line 283 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4014 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 101: /* "quoted string"  */
#line 283 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4020 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 102: /* "string with a trailing asterisk"  */
#line 283 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4026 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 331: /* line  */
#line 556 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4032 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 332: /* base_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4038 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 333: /* add_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4044 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 334: /* replace_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4050 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* create_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4056 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 336: /* insert_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4062 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* delete_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4068 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* get_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4074 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* list_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4080 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* reset_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4086 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* flush_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4092 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* rename_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4098 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* import_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4104 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* export_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4110 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 345: /* monitor_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4116 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* monitor_event  */
#line 778 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4122 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* describe_cmd  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4128 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 351: /* table_block_alloc  */
#line 575 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 4134 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* chain_block_alloc  */
#line 577 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 4140 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* set_block_alloc  */
#line 586 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4146 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* set_block_expr  */
#line 683 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4152 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* map_block_alloc  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4158 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 365: /* flowtable_block_alloc  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 4164 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 367: /* flowtable_expr  */
#line 683 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4170 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 368: /* flowtable_list_expr  */
#line 683 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4176 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 369: /* flowtable_expr_member  */
#line 683 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4182 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 370: /* data_type_atom_expr  */
#line 553 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4188 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 371: /* data_type_expr  */
#line 553 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4194 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 372: /* obj_block_alloc  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4200 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 380: /* type_identifier  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4206 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* extended_prio_name  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4212 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* dev_spec  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4218 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* policy_expr  */
#line 642 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4224 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* identifier  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4230 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* string  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4236 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* table_spec  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4242 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 396: /* tableid_spec  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4248 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* chain_spec  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4254 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* chainid_spec  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4260 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* chain_identifier  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4266 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* set_spec  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4272 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* setid_spec  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4278 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* set_identifier  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4284 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* flowtable_spec  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4290 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* obj_spec  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4296 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* objid_spec  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4302 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* obj_identifier  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4308 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* handle_spec  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4314 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* position_spec  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4320 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* index_spec  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4326 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* rule_position  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4332 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 412: /* ruleid_spec  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4338 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* comment_spec  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4344 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* ruleset_spec  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4350 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* rule  */
#line 579 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 4356 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* stmt_list  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 4362 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* stateful_stmt  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4368 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* stmt  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4374 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* verdict_stmt  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4380 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* verdict_map_stmt  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4386 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* verdict_map_expr  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4392 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* verdict_map_list_expr  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4398 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* verdict_map_list_member_expr  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4404 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* connlimit_stmt  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4410 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* counter_stmt  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4416 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* counter_stmt_alloc  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4422 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* log_stmt  */
#line 610 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4428 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* log_stmt_alloc  */
#line 610 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4434 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* limit_stmt  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4440 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 440: /* quota_unit  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4446 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* quota_stmt  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4452 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 447: /* reject_stmt  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4458 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* reject_stmt_alloc  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4464 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 450: /* nat_stmt  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4470 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* nat_stmt_alloc  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4476 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* tproxy_stmt  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4482 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 453: /* synproxy_stmt  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4488 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 454: /* synproxy_stmt_alloc  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4494 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* primary_stmt_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4500 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* shift_stmt_expr  */
#line 666 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4506 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* and_stmt_expr  */
#line 668 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4512 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* exclusive_or_stmt_expr  */
#line 668 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4518 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* inclusive_or_stmt_expr  */
#line 668 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4524 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* basic_stmt_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4530 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 463: /* concat_stmt_expr  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4536 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* map_stmt_expr_set  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4542 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* map_stmt_expr  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4548 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* prefix_stmt_expr  */
#line 661 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4554 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 467: /* range_stmt_expr  */
#line 661 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4560 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* wildcard_expr  */
#line 661 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4566 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* multiton_stmt_expr  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4572 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* stmt_expr  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4578 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* masq_stmt  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4584 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* masq_stmt_alloc  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4590 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* redir_stmt  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4596 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* redir_stmt_alloc  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4602 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* dup_stmt  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4608 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* fwd_stmt  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4614 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* queue_stmt  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4620 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 483: /* queue_stmt_alloc  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4626 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* set_elem_expr_stmt  */
#line 687 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4632 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 489: /* set_elem_expr_stmt_alloc  */
#line 687 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4638 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 490: /* set_stmt  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4644 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 492: /* map_stmt  */
#line 637 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4650 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 493: /* meter_stmt  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4656 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* flow_stmt_legacy_alloc  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4662 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 497: /* meter_stmt_alloc  */
#line 639 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4668 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 498: /* match_stmt  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4674 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 499: /* variable_expr  */
#line 642 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4680 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* symbol_expr  */
#line 642 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4686 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* integer_expr  */
#line 642 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4692 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 502: /* primary_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4698 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 503: /* fib_expr  */
#line 769 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4704 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* osf_expr  */
#line 774 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4710 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 509: /* shift_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4716 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* and_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4722 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 511: /* exclusive_or_expr  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4728 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 512: /* inclusive_or_expr  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4734 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* basic_expr  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4740 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 514: /* concat_expr  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4746 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 515: /* prefix_rhs_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4752 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 516: /* range_rhs_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4758 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* multiton_rhs_expr  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4764 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* map_expr  */
#line 674 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4770 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* expr  */
#line 693 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4776 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 520: /* set_expr  */
#line 683 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4782 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 521: /* set_list_expr  */
#line 683 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4788 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 522: /* set_list_member_expr  */
#line 683 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4794 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* meter_key_expr  */
#line 690 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4800 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 524: /* meter_key_expr_alloc  */
#line 690 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4806 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 525: /* set_elem_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4812 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 526: /* set_elem_expr_alloc  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4818 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* set_lhs_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4824 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* set_rhs_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4830 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* initializer_expr  */
#line 693 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4836 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* counter_config  */
#line 782 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).counter)); }
#line 4842 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* counter_obj  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4848 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* quota_config  */
#line 784 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).quota)); }
#line 4854 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* quota_obj  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4860 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* secmark_config  */
#line 788 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).secmark)); }
#line 4866 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 537: /* secmark_obj  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4872 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* timeout_states  */
#line 806 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 4878 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 542: /* timeout_state  */
#line 806 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 4884 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 545: /* ct_obj_alloc  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4890 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 546: /* limit_config  */
#line 786 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).limit)); }
#line 4896 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* limit_obj  */
#line 703 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4902 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 548: /* relational_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4908 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 549: /* list_rhs_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4914 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 550: /* rhs_expr  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4920 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* shift_rhs_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4926 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 552: /* and_rhs_expr  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4932 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 553: /* exclusive_or_rhs_expr  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4938 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 554: /* inclusive_or_rhs_expr  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4944 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 555: /* basic_rhs_expr  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4950 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 556: /* concat_rhs_expr  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4956 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 558: /* boolean_expr  */
#line 796 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4962 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 559: /* keyword_expr  */
#line 693 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4968 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 560: /* primary_rhs_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4974 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 562: /* verdict_expr  */
#line 642 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4980 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 563: /* chain_expr  */
#line 642 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4986 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 564: /* meta_expr  */
#line 751 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4992 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 568: /* meta_stmt  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4998 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 569: /* socket_expr  */
#line 755 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5004 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 573: /* numgen_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5010 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 578: /* xfrm_expr  */
#line 810 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5016 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 579: /* hash_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5022 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 581: /* rt_expr  */
#line 761 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5028 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 583: /* ct_expr  */
#line 765 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5034 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 589: /* symbol_stmt_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5040 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 590: /* list_stmt_expr  */
#line 666 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5046 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 591: /* ct_stmt  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5052 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 592: /* payload_stmt  */
#line 604 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 5058 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 593: /* payload_expr  */
#line 710 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5064 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 594: /* payload_raw_expr  */
#line 710 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5070 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 596: /* eth_hdr_expr  */
#line 713 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5076 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 598: /* vlan_hdr_expr  */
#line 713 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5082 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 600: /* arp_hdr_expr  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5088 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 602: /* ip_hdr_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5094 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 606: /* icmp_hdr_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5100 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 608: /* igmp_hdr_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5106 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 610: /* ip6_hdr_expr  */
#line 723 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5112 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 612: /* icmp6_hdr_expr  */
#line 723 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5118 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 614: /* auth_hdr_expr  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5124 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 616: /* esp_hdr_expr  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5130 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 618: /* comp_hdr_expr  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5136 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 620: /* udp_hdr_expr  */
#line 729 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5142 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 622: /* udplite_hdr_expr  */
#line 729 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5148 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 624: /* tcp_hdr_expr  */
#line 791 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5154 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 628: /* dccp_hdr_expr  */
#line 732 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5160 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 630: /* sctp_hdr_expr  */
#line 732 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5166 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 632: /* th_hdr_expr  */
#line 735 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5172 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 634: /* exthdr_expr  */
#line 739 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5178 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 635: /* hbh_hdr_expr  */
#line 741 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5184 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 637: /* rt_hdr_expr  */
#line 744 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5190 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 639: /* rt0_hdr_expr  */
#line 744 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5196 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 641: /* rt2_hdr_expr  */
#line 744 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5202 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 643: /* rt4_hdr_expr  */
#line 744 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5208 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 645: /* frag_hdr_expr  */
#line 741 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5214 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 647: /* dst_hdr_expr  */
#line 741 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5220 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 649: /* mh_hdr_expr  */
#line 747 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5226 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 651: /* exthdr_exists_expr  */
#line 800 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5232 "parser_bison.c" /* yacc.c:1257  */
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

#line 5348 "parser_bison.c" /* yacc.c:1431  */
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
#line 816 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 5547 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 8:
#line 833 "parser_bison.y" /* yacc.c:1652  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 9:
#line 841 "parser_bison.y" /* yacc.c:1652  */
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
#line 5577 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 10:
#line 855 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 5588 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 11:
#line 862 "parser_bison.y" /* yacc.c:1652  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 12:
#line 873 "parser_bison.y" /* yacc.c:1652  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 5613 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 13:
#line 880 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 5619 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 14:
#line 881 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = NULL; }
#line 5625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 15:
#line 882 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 5631 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 16:
#line 884 "parser_bison.y" /* yacc.c:1652  */
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
#line 5653 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 17:
#line 903 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5659 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 18:
#line 904 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5665 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 19:
#line 905 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5671 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 20:
#line 906 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5677 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 21:
#line 907 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5683 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 22:
#line 908 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5689 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 23:
#line 909 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5695 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 24:
#line 910 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5701 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 25:
#line 911 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5707 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 26:
#line 912 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5713 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 27:
#line 913 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5719 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 28:
#line 914 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5725 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 29:
#line 915 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5731 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 30:
#line 916 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 31:
#line 917 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5743 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 32:
#line 921 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5751 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 33:
#line 926 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 34:
#line 932 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5769 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 35:
#line 937 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5780 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 36:
#line 944 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5788 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 37:
#line 948 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5796 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 38:
#line 953 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5806 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 39:
#line 960 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5816 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 40:
#line 966 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5824 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 41:
#line 971 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5834 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 42:
#line 977 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5847 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 43:
#line 986 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5855 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 44:
#line 990 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5863 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 45:
#line 994 "parser_bison.y" /* yacc.c:1652  */
    {

				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 5872 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 46:
#line 999 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 5880 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 47:
#line 1003 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 5888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 48:
#line 1007 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5896 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 49:
#line 1011 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5904 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 50:
#line 1017 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5912 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 51:
#line 1023 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5920 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 52:
#line 1028 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5930 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 53:
#line 1034 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5938 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 54:
#line 1039 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5949 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 55:
#line 1047 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5959 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 56:
#line 1054 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5969 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 57:
#line 1060 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5977 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 58:
#line 1065 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5987 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 59:
#line 1071 "parser_bison.y" /* yacc.c:1652  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 6000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 60:
#line 1080 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6008 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 61:
#line 1084 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6016 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 62:
#line 1088 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6024 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 63:
#line 1092 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6032 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 64:
#line 1096 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_EXPECT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 6040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 65:
#line 1100 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 66:
#line 1104 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 67:
#line 1110 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 6064 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 68:
#line 1116 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 69:
#line 1120 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6080 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 70:
#line 1124 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6088 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 71:
#line 1128 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6096 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 72:
#line 1132 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6104 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 73:
#line 1136 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6112 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 74:
#line 1140 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6120 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 75:
#line 1144 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6128 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 76:
#line 1148 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6136 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 77:
#line 1152 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6144 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 78:
#line 1156 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6152 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 79:
#line 1160 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6160 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 80:
#line 1164 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6168 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 81:
#line 1168 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6176 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 82:
#line 1172 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6184 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 83:
#line 1176 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6192 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 84:
#line 1180 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6200 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 85:
#line 1184 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6208 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 86:
#line 1188 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6216 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 87:
#line 1194 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6224 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 88:
#line 1200 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6232 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 89:
#line 1204 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6240 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 90:
#line 1208 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6248 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 91:
#line 1212 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6256 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 92:
#line 1216 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6264 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 93:
#line 1220 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6272 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 94:
#line 1224 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6280 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 95:
#line 1228 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6288 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 96:
#line 1232 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6296 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 97:
#line 1236 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6304 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 98:
#line 1240 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6312 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 99:
#line 1244 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6320 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 100:
#line 1248 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6328 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 101:
#line 1252 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6336 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 102:
#line 1256 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6344 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 103:
#line 1260 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6352 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 104:
#line 1264 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6360 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 105:
#line 1268 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6368 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1272 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6376 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1276 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1280 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6392 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1284 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6400 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1288 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6408 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1292 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6416 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1296 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6424 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1300 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6432 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1304 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6440 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 115:
#line 1308 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6448 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 116:
#line 1312 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6456 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 117:
#line 1316 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_TIMEOUT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6464 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 118:
#line 1320 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_EXPECT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6472 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 119:
#line 1326 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6480 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1330 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6488 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1334 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 6496 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1338 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6504 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1342 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6512 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1346 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6520 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1352 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6528 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1356 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6536 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1360 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6544 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1364 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6552 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1368 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6560 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1372 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1376 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1382 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 6585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1389 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6595 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1395 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6605 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1403 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1409 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6625 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1417 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 6636 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 138:
#line 1425 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = NULL; }
#line 6642 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 139:
#line 1426 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6648 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 140:
#line 1429 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 6654 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 141:
#line 1430 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 6660 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1431 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 6666 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1432 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 6672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1433 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 6678 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 145:
#line 1434 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 6684 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 146:
#line 1435 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 6690 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 147:
#line 1436 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 6696 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 148:
#line 1439 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 6702 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 150:
#line 1443 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 6708 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 151:
#line 1444 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 6714 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 152:
#line 1445 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 6720 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 153:
#line 1449 "parser_bison.y" /* yacc.c:1652  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 6730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1457 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 6739 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1464 "parser_bison.y" /* yacc.c:1652  */
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
#line 6755 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1477 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 6761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1484 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1495 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6786 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1505 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6798 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1516 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6810 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 164:
#line 1526 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6823 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1537 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6836 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 166:
#line 1546 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 6849 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 167:
#line 1555 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 6862 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 168:
#line 1564 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_EXPECT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 6875 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 169:
#line 1575 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6888 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1586 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6901 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1597 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 6910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1603 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 6916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 177:
#line 1609 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 6925 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 178:
#line 1616 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 179:
#line 1621 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6939 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 182:
#line 1625 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6948 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 183:
#line 1630 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6957 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 184:
#line 1635 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6966 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 185:
#line 1640 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6975 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 186:
#line 1645 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6984 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 187:
#line 1650 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 6993 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 191:
#line 1662 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7001 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 193:
#line 1668 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 7007 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 194:
#line 1669 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 7013 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 195:
#line 1670 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 7019 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 196:
#line 1671 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_EVAL; }
#line 7025 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 197:
#line 1675 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 7033 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 198:
#line 1680 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 7039 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 201:
#line 1684 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7048 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 202:
#line 1691 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].expr)->dtype;

				expr_free((yyvsp[-1].expr));
				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7061 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 203:
#line 1702 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 204:
#line 1711 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7083 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 205:
#line 1720 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7094 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 206:
#line 1729 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_SECMARK;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 7105 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 207:
#line 1736 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7114 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 208:
#line 1741 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 7123 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 210:
#line 1749 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 7131 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 211:
#line 1753 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 7139 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 212:
#line 1758 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 7145 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 213:
#line 1759 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 7151 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 214:
#line 1763 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 7159 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 215:
#line 1768 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 7165 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 218:
#line 1772 "parser_bison.y" /* yacc.c:1652  */
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
#line 7182 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 219:
#line 1785 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 7190 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 220:
#line 1791 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7199 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 221:
#line 1798 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_INVALID);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7208 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 222:
#line 1803 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7217 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 224:
#line 1811 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
			}
#line 7227 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 225:
#line 1819 "parser_bison.y" /* yacc.c:1652  */
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
#line 7243 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 227:
#line 1834 "parser_bison.y" /* yacc.c:1652  */
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
#line 7264 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 228:
#line 1853 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 7272 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 229:
#line 1858 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7278 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 232:
#line 1862 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].obj)->counter = *(yyvsp[0].counter);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7287 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 233:
#line 1868 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7293 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 236:
#line 1872 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].obj)->quota = *(yyvsp[0].quota);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7302 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 237:
#line 1878 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7308 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 240:
#line 1882 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7316 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 241:
#line 1887 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7322 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 244:
#line 1891 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7330 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 245:
#line 1896 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7336 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 248:
#line 1900 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7344 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 249:
#line 1905 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7350 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 252:
#line 1909 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].obj)->limit = *(yyvsp[0].limit);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7359 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 253:
#line 1915 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7365 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 256:
#line 1919 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].obj)->secmark = *(yyvsp[0].secmark);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7374 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 257:
#line 1925 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7380 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 258:
#line 1926 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("mark"); }
#line 7386 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 259:
#line 1927 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("dscp"); }
#line 7392 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 260:
#line 1928 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("ecn"); }
#line 7398 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 261:
#line 1929 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("classid"); }
#line 7404 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 262:
#line 1933 "parser_bison.y" /* yacc.c:1652  */
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

				(yyvsp[-6].chain)->dev		= (yyvsp[-1].string);
				(yyvsp[-6].chain)->priority	= (yyvsp[0].prio_spec);
				(yyvsp[-6].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
#line 7434 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 263:
#line 1961 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 7443 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 264:
#line 1968 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.string) = strdup("out");
			}
#line 7451 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 266:
#line 1975 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &integer_type,
								BYTEORDER_HOST_ENDIAN,
								sizeof(int) *
								BITS_PER_BYTE, &(yyvsp[0].val32));
				(yyval.prio_spec) = spec;
			}
#line 7465 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 267:
#line 1985 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				datatype_set((yyvsp[0].expr)->sym->expr, &priority_type);
				spec.expr = (yyvsp[0].expr);
				(yyval.prio_spec) = spec;
			}
#line 7477 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 268:
#line 1993 "parser_bison.y" /* yacc.c:1652  */
    {
				struct prio_spec spec = {0};

				spec.expr = constant_expr_alloc(&(yyloc), &string_type,
								BYTEORDER_HOST_ENDIAN,
								strlen((yyvsp[0].string)) * BITS_PER_BYTE,
								(yyvsp[0].string));
				xfree((yyvsp[0].string));
				(yyval.prio_spec) = spec;
			}
#line 7492 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 269:
#line 2004 "parser_bison.y" /* yacc.c:1652  */
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
#line 7509 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 270:
#line 2017 "parser_bison.y" /* yacc.c:1652  */
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
#line 7525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 271:
#line 2030 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = (yyvsp[0].val); }
#line 7531 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 272:
#line 2031 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = -(yyvsp[0].val); }
#line 7537 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 273:
#line 2034 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 274:
#line 2035 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = NULL; }
#line 7549 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 275:
#line 2039 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].chain)->policy) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					expr_free((yyvsp[0].expr));
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].expr);
			}
#line 7563 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 276:
#line 2051 "parser_bison.y" /* yacc.c:1652  */
    {
				datatype_set((yyvsp[0].expr)->sym->expr, &policy_type);
				(yyval.expr) = (yyvsp[0].expr);
			}
#line 7572 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 277:
#line 2056 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &integer_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(int) *
							 BITS_PER_BYTE, &(yyvsp[0].val32));
			}
#line 7583 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 278:
#line 2064 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_ACCEPT; }
#line 7589 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 279:
#line 2065 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val32) = NF_DROP;   }
#line 7595 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 284:
#line 2077 "parser_bison.y" /* yacc.c:1652  */
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
#line 7612 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 285:
#line 2091 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 7618 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 287:
#line 2095 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 7624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 288:
#line 2096 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 7630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 289:
#line 2097 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_INET; }
#line 7636 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 290:
#line 2098 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_ARP; }
#line 7642 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 291:
#line 2099 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 7648 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 292:
#line 2100 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 7654 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 293:
#line 2104 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 7665 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 294:
#line 2113 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yyloc);
			}
#line 7676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 295:
#line 2122 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 7686 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 296:
#line 2130 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 7696 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 297:
#line 2138 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 7706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 298:
#line 2146 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 7716 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 299:
#line 2154 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 7726 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 300:
#line 2162 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 7736 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 301:
#line 2171 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).flowtable	= (yyvsp[0].string);
			}
#line 7745 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 302:
#line 2178 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable	= (yyvsp[0].string);
			}
#line 7754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 303:
#line 2185 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 7764 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 304:
#line 2193 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 7774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 305:
#line 2201 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 7784 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 306:
#line 2209 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 7794 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 307:
#line 2217 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 7804 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 308:
#line 2225 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 7814 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 309:
#line 2233 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 7822 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 310:
#line 2237 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7831 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 311:
#line 2242 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7843 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 312:
#line 2250 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 313:
#line 2257 "parser_bison.y" /* yacc.c:1652  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7861 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 314:
#line 2264 "parser_bison.y" /* yacc.c:1652  */
    {
				if (strlen((yyvsp[0].string)) > NFTNL_UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed",
							 NFTNL_UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 7875 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 315:
#line 2276 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 7884 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 316:
#line 2281 "parser_bison.y" /* yacc.c:1652  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 7893 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 317:
#line 2288 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 7901 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 318:
#line 2292 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 7909 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 319:
#line 2298 "parser_bison.y" /* yacc.c:1652  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 7923 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 320:
#line 2310 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 7933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 321:
#line 2316 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 7942 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 345:
#line 2350 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7950 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 346:
#line 2354 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7958 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 347:
#line 2360 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7966 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 348:
#line 2366 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7975 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 349:
#line 2371 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7986 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 350:
#line 2380 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 351:
#line 2385 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8004 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 353:
#line 2393 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 8012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 354:
#line 2399 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[0].val);
			}
#line 8021 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 355:
#line 2404 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[0].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 8031 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 358:
#line 2415 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 8039 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 359:
#line 2419 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8049 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 360:
#line 2427 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8057 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 362:
#line 2434 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 8065 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 363:
#line 2438 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 8073 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 366:
#line 2448 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 8081 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 367:
#line 2454 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8089 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 369:
#line 2461 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 8098 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 370:
#line 2466 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 8107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 371:
#line 2471 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 8116 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 372:
#line 2476 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 8125 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 373:
#line 2481 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 8134 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 374:
#line 2486 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 8142 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 375:
#line 2492 "parser_bison.y" /* yacc.c:1652  */
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
#line 8174 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 376:
#line 2522 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 8182 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 377:
#line 2526 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 8190 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 378:
#line 2530 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 8198 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 379:
#line 2534 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 8206 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 380:
#line 2538 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 8214 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 381:
#line 2544 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8222 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 383:
#line 2551 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 8230 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 384:
#line 2555 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 8238 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 385:
#line 2561 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 8251 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 386:
#line 2570 "parser_bison.y" /* yacc.c:1652  */
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
#line 8274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 387:
#line 2589 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8284 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 388:
#line 2596 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 8290 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 389:
#line 2597 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8296 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 390:
#line 2598 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8302 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 391:
#line 2601 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = xstrdup("bytes"); }
#line 8308 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 392:
#line 2602 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 8314 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 393:
#line 2605 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8320 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 394:
#line 2607 "parser_bison.y" /* yacc.c:1652  */
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
#line 8337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 395:
#line 2622 "parser_bison.y" /* yacc.c:1652  */
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
#line 8357 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 396:
#line 2638 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8367 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 397:
#line 2645 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 8373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 398:
#line 2646 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8379 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 399:
#line 2647 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8385 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 400:
#line 2650 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8391 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 401:
#line 2651 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 8397 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 402:
#line 2654 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 8403 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 403:
#line 2655 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 8409 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 404:
#line 2657 "parser_bison.y" /* yacc.c:1652  */
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
#line 8426 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 405:
#line 2671 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL; }
#line 8432 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 406:
#line 2672 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60; }
#line 8438 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 407:
#line 2673 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 8444 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 408:
#line 2674 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 8450 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 409:
#line 2675 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 8456 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 411:
#line 2682 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 8464 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 412:
#line 2688 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 8473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 413:
#line 2693 "parser_bison.y" /* yacc.c:1652  */
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
#line 8488 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 414:
#line 2704 "parser_bison.y" /* yacc.c:1652  */
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
#line 8503 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 415:
#line 2715 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpx_code_type);
				xfree((yyvsp[0].string));
			}
#line 8517 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 416:
#line 2725 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 8525 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 418:
#line 2733 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 8531 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 419:
#line 2734 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 8537 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 420:
#line 2738 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 8547 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 421:
#line 2744 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 8557 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 422:
#line 2750 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8567 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 423:
#line 2756 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8578 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 424:
#line 2763 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8589 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 425:
#line 2770 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8599 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 428:
#line 2782 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = synproxy_stmt_alloc(&(yyloc));
			}
#line 8607 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 429:
#line 2788 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 431:
#line 2795 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.mss = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_MSS;
			}
#line 8624 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 432:
#line 2800 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->synproxy.wscale = (yyvsp[0].val);
				(yyvsp[-2].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_WSCALE;
			}
#line 8633 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 433:
#line 2805 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_TIMESTAMP;
			}
#line 8641 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 434:
#line 2809 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->synproxy.flags |= NF_SYNPROXY_OPT_SACK_PERM;
			}
#line 8649 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 435:
#line 2814 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8655 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 436:
#line 2815 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8661 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 437:
#line 2816 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8667 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 438:
#line 2817 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8673 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 439:
#line 2818 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8679 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 440:
#line 2819 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8685 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 441:
#line 2820 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8691 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 442:
#line 2821 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8697 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 443:
#line 2822 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8703 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 444:
#line 2823 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8709 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 445:
#line 2824 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8715 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 446:
#line 2825 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8721 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 448:
#line 2830 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8729 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 449:
#line 2834 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8737 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 451:
#line 2841 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8745 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 453:
#line 2848 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8753 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 455:
#line 2855 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8761 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 458:
#line 2865 "parser_bison.y" /* yacc.c:1652  */
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
#line 8782 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 461:
#line 2888 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8790 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 462:
#line 2891 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8796 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 463:
#line 2895 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 8804 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 464:
#line 2901 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8812 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 465:
#line 2907 "parser_bison.y" /* yacc.c:1652  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 8825 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 472:
#line 2928 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 8833 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 473:
#line 2932 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 8841 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 474:
#line 2936 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 8850 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 475:
#line 2941 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8859 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 476:
#line 2946 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8868 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 477:
#line 2951 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8878 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 478:
#line 2957 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8886 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 479:
#line 2961 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8894 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 480:
#line 2965 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8902 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 483:
#line 2974 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 8908 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 484:
#line 2978 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 485:
#line 2982 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8925 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 486:
#line 2987 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 489:
#line 2996 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 8939 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 490:
#line 3000 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8947 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 491:
#line 3004 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8955 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 492:
#line 3008 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8963 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 493:
#line 3012 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8972 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 494:
#line 3017 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 495:
#line 3024 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 8990 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 496:
#line 3029 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 9000 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 497:
#line 3037 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 9009 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 498:
#line 3042 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 9020 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 500:
#line 3052 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9028 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 501:
#line 3057 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 9034 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 502:
#line 3058 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 9040 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 503:
#line 3059 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 9046 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 506:
#line 3067 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 9054 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 507:
#line 3073 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9062 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 509:
#line 3080 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 9071 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 510:
#line 3085 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 9079 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 512:
#line 3092 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9087 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 513:
#line 3097 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 9093 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 514:
#line 3098 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 9099 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 517:
#line 3106 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 9107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 518:
#line 3112 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 9118 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 519:
#line 3119 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 9129 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 520:
#line 3126 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				(yyval.stmt)->set.stmt = (yyvsp[-1].stmt);
			}
#line 9141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 521:
#line 3135 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 9147 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 522:
#line 3136 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 9153 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 523:
#line 3140 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 9165 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 524:
#line 3148 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.stmt = (yyvsp[-3].stmt);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
			}
#line 9178 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 525:
#line 3159 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 9189 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 526:
#line 3165 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 9195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 527:
#line 3169 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 9203 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 528:
#line 3175 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 9211 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 530:
#line 3182 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 9219 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 531:
#line 3188 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 9232 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 532:
#line 3197 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 9245 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 533:
#line 3208 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 9253 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 534:
#line 3214 "parser_bison.y" /* yacc.c:1652  */
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
#line 9281 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 536:
#line 3241 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9292 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 537:
#line 3248 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9303 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 538:
#line 3257 "parser_bison.y" /* yacc.c:1652  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 9316 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 539:
#line 3267 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9322 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 540:
#line 3268 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9328 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 541:
#line 3269 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9334 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 542:
#line 3270 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 543:
#line 3271 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9346 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 544:
#line 3272 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9352 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 545:
#line 3273 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9358 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 546:
#line 3274 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9364 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 547:
#line 3275 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9370 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 548:
#line 3276 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9376 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 549:
#line 3277 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9382 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 550:
#line 3278 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9388 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 551:
#line 3279 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9394 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 552:
#line 3280 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9400 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 553:
#line 3281 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 9406 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 554:
#line 3285 "parser_bison.y" /* yacc.c:1652  */
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
#line 9431 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 555:
#line 3307 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 9437 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 556:
#line 3308 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 9443 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 557:
#line 3309 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 9449 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 558:
#line 3312 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 9455 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 559:
#line 3313 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 9461 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 560:
#line 3314 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 9467 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 561:
#line 3315 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 9473 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 562:
#line 3316 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 9479 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 563:
#line 3320 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9487 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 565:
#line 3327 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), NFT_OSF_F_VERSION);
			}
#line 9495 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 566:
#line 3331 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 9503 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 567:
#line 3337 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 9511 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 568:
#line 3341 "parser_bison.y" /* yacc.c:1652  */
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
#line 9527 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 570:
#line 3356 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9535 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 571:
#line 3360 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 573:
#line 3367 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9551 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 575:
#line 3374 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9559 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 577:
#line 3381 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9567 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 580:
#line 3391 "parser_bison.y" /* yacc.c:1652  */
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
#line 9588 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 581:
#line 3410 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 9596 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 582:
#line 3416 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9604 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 586:
#line 3427 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9612 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 590:
#line 3438 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9621 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 591:
#line 3445 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9630 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 592:
#line 3450 "parser_bison.y" /* yacc.c:1652  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9639 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 594:
#line 3458 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9647 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 595:
#line 3462 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9655 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 596:
#line 3466 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 9663 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 598:
#line 3473 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9672 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 599:
#line 3480 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 9680 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 602:
#line 3490 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 9688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 603:
#line 3496 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 9696 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 605:
#line 3503 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 9704 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 606:
#line 3507 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->expiration = (yyvsp[0].val);
			}
#line 9712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 607:
#line 3511 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 9720 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 614:
#line 3529 "parser_bison.y" /* yacc.c:1652  */
    {
				struct counter *counter;

				counter = xzalloc(sizeof(*counter));
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
				(yyval.counter) = counter;
			}
#line 9733 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 615:
#line 3540 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
				(yyval.obj)->counter = *(yyvsp[0].counter);
			}
#line 9743 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 616:
#line 3548 "parser_bison.y" /* yacc.c:1652  */
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

				quota = xzalloc(sizeof(*quota));
				quota->bytes	= (yyvsp[-2].val) * rate;
				quota->used	= (yyvsp[0].val);
				quota->flags	= (yyvsp[-3].val);
				(yyval.quota) = quota;
			}
#line 9766 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 617:
#line 3569 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
				(yyval.obj)->quota = *(yyvsp[0].quota);
			}
#line 9776 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 618:
#line 3577 "parser_bison.y" /* yacc.c:1652  */
    {
				int ret;
				struct secmark *secmark;
				secmark = xzalloc(sizeof(*secmark));
				ret = snprintf(secmark->ctx, sizeof(secmark->ctx), "%s", (yyvsp[0].string));
				if (ret <= 0 || ret >= (int)sizeof(secmark->ctx)) {
					erec_queue(error(&(yylsp[0]), "invalid context '%s', max length is %u\n", (yyvsp[0].string), (int)sizeof(secmark->ctx)), state->msgs);
					YYERROR;
				}
				(yyval.secmark) = secmark;
			}
#line 9792 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 619:
#line 3591 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
				(yyval.obj)->secmark = *(yyvsp[0].secmark);
			}
#line 9802 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 620:
#line 3598 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 9808 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 621:
#line 3599 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 9814 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 622:
#line 3600 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_OBJECT_CT_EXPECT; }
#line 9820 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 623:
#line 3603 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_TCP; }
#line 9826 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 624:
#line 3604 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_UDP; }
#line 9832 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 625:
#line 3608 "parser_bison.y" /* yacc.c:1652  */
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
#line 9851 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 626:
#line 3623 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 9859 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 627:
#line 3629 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 9869 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 628:
#line 3635 "parser_bison.y" /* yacc.c:1652  */
    {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 9878 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 629:
#line 3643 "parser_bison.y" /* yacc.c:1652  */
    {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 9893 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 630:
#line 3656 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 9905 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 631:
#line 3664 "parser_bison.y" /* yacc.c:1652  */
    {
				struct ct_timeout *ct;

				ct = &(yyvsp[-6].obj)->ct_timeout;
				init_list_head(&ct->timeout_list);
				list_splice_tail((yyvsp[-2].list), &ct->timeout_list);
			}
#line 9917 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 632:
#line 3672 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 9925 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 633:
#line 3678 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l4proto = (yyvsp[-1].val);
			}
#line 9933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 634:
#line 3682 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.dport = (yyvsp[-1].val);
			}
#line 9941 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 635:
#line 3686 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.timeout = (yyvsp[-1].val);
			}
#line 9949 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 636:
#line 3690 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.size = (yyvsp[-1].val);
			}
#line 9957 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 637:
#line 3694 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-3].obj)->ct_expect.l3proto = (yyvsp[-1].val);
			}
#line 9965 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 638:
#line 3700 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 9973 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 639:
#line 3706 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;
				limit = xzalloc(sizeof(*limit));
				limit->rate	= (yyvsp[-3].val);
				limit->unit	= (yyvsp[-1].val);
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKTS;
				limit->flags	= (yyvsp[-4].val);
				(yyval.limit) = limit;
			}
#line 9988 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 640:
#line 3717 "parser_bison.y" /* yacc.c:1652  */
    {
				struct limit *limit;
				struct error_record *erec;
				uint64_t rate, unit;

				erec = rate_parse(&(yyloc), (yyvsp[-1].string), &rate, &unit);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				limit = xzalloc(sizeof(*limit));
				limit->rate	= rate * (yyvsp[-2].val);
				limit->unit	= unit;
				limit->burst	= (yyvsp[0].val);
				limit->type	= NFT_LIMIT_PKT_BYTES;
				limit->flags	= (yyvsp[-3].val);
				(yyval.limit) = limit;
			}
#line 10012 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 641:
#line 3739 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
				(yyval.obj)->limit = *(yyvsp[0].limit);
			}
#line 10022 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 642:
#line 3747 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 10030 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 643:
#line 3751 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 10038 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 644:
#line 3755 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10046 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 645:
#line 3761 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10056 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 646:
#line 3767 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10066 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 647:
#line 3774 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10072 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 648:
#line 3775 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10078 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 649:
#line 3776 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10084 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 651:
#line 3781 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10092 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 652:
#line 3785 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10100 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 654:
#line 3792 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10108 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 656:
#line 3799 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10116 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 658:
#line 3806 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10124 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 661:
#line 3816 "parser_bison.y" /* yacc.c:1652  */
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
#line 10145 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 662:
#line 3834 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = true; }
#line 10151 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 663:
#line 3835 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = false; }
#line 10157 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 664:
#line 3839 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 1, &(yyvsp[0].val));
			}
#line 10167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 665:
#line 3846 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 10173 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 666:
#line 3847 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 10179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 667:
#line 3848 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 10185 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 668:
#line 3849 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 10191 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 669:
#line 3850 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 10197 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 670:
#line 3851 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 10203 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 671:
#line 3852 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 10209 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 672:
#line 3853 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 10215 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 673:
#line 3854 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 10221 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 674:
#line 3855 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 10227 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 675:
#line 3856 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 10233 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 676:
#line 3857 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 10239 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 677:
#line 3860 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10245 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 678:
#line 3861 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10251 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 679:
#line 3862 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 680:
#line 3863 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 10263 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 681:
#line 3865 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10274 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 682:
#line 3872 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 683:
#line 3879 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10296 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 684:
#line 3886 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10307 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 685:
#line 3893 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10318 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 686:
#line 3900 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10329 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 687:
#line 3907 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10340 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 688:
#line 3914 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10351 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 689:
#line 3921 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10362 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 690:
#line 3928 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10373 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 691:
#line 3935 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10384 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 692:
#line 3942 "parser_bison.y" /* yacc.c:1652  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10395 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 693:
#line 3948 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 10401 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 694:
#line 3951 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_EQ; }
#line 10407 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 695:
#line 3952 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_NEQ; }
#line 10413 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 696:
#line 3953 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LT; }
#line 10419 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 697:
#line 3954 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GT; }
#line 10425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 698:
#line 3955 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_GTE; }
#line 10431 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 699:
#line 3956 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = OP_LTE; }
#line 10437 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 700:
#line 3960 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 10445 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 701:
#line 3964 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 10453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 702:
#line 3968 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 10461 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 703:
#line 3972 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 10469 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 704:
#line 3976 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 10477 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 705:
#line 3980 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 10485 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 707:
#line 3987 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10497 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 708:
#line 3997 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 10505 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 709:
#line 4001 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 10513 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 710:
#line 4005 "parser_bison.y" /* yacc.c:1652  */
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
#line 10531 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 713:
#line 4024 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_LEN; }
#line 10537 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 714:
#line 4025 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 10543 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 715:
#line 4026 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 10549 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 716:
#line 4027 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 10555 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 717:
#line 4028 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECMARK; }
#line 10561 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 718:
#line 4031 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_MARK; }
#line 10567 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 719:
#line 4032 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIF; }
#line 10573 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 720:
#line 4033 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 10579 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 721:
#line 4034 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 10585 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 722:
#line 4035 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIF; }
#line 10591 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 723:
#line 4036 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 10597 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 724:
#line 4037 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 10603 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 725:
#line 4038 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKUID; }
#line 10609 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 726:
#line 4039 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SKGID; }
#line 10615 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 727:
#line 4040 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 10621 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 728:
#line 4041 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 10627 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 729:
#line 4042 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 10633 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 730:
#line 4043 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 10639 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 731:
#line 4044 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 10645 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 732:
#line 4045 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 10651 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 733:
#line 4046 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 10657 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 734:
#line 4047 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CPU; }
#line 10663 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 735:
#line 4048 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 10669 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 736:
#line 4049 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 10675 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 737:
#line 4050 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 10681 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 738:
#line 4051 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_META_SECPATH; }
#line 10687 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 739:
#line 4055 "parser_bison.y" /* yacc.c:1652  */
    {
				switch ((yyvsp[-2].val)) {
				case NFT_META_SECMARK:
					(yyval.stmt) = objref_stmt_alloc(&(yyloc));
					(yyval.stmt)->objref.type = NFT_OBJECT_SECMARK;
					(yyval.stmt)->objref.expr = (yyvsp[0].expr);
					break;
				default:
					(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
					break;
				}
			}
#line 10704 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 740:
#line 4068 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 10712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 741:
#line 4072 "parser_bison.y" /* yacc.c:1652  */
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
#line 10730 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 742:
#line 4086 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 10738 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 743:
#line 4090 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 10746 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 744:
#line 4094 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 10754 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 745:
#line 4100 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 10762 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 746:
#line 4105 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 10768 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 747:
#line 4106 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_SOCKET_MARK; }
#line 10774 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 748:
#line 4109 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 10780 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 749:
#line 4110 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 10786 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 750:
#line 4113 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 10792 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 751:
#line 4114 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 10798 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 752:
#line 4118 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 10806 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 753:
#line 4123 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = (yyvsp[0].val); }
#line 10812 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 754:
#line 4124 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = 0; }
#line 10818 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 755:
#line 4127 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_IN; }
#line 10824 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 756:
#line 4128 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = XFRM_POLICY_OUT; }
#line 10830 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 757:
#line 4131 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 10836 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 758:
#line 4132 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 10842 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 759:
#line 4135 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 10848 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 760:
#line 4136 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 10854 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 761:
#line 4140 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-1].val) > 255) {
					erec_queue(error(&(yylsp[-1]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 10866 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 762:
#line 4148 "parser_bison.y" /* yacc.c:1652  */
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
#line 10895 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 763:
#line 4175 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 10904 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 764:
#line 4180 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 10913 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 765:
#line 4185 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 10921 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 766:
#line 4190 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 10927 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 767:
#line 4191 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 10933 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 768:
#line 4195 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 10941 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 769:
#line 4199 "parser_bison.y" /* yacc.c:1652  */
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
#line 10963 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 770:
#line 4218 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 10969 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 771:
#line 4219 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 10975 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 772:
#line 4220 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 10981 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 773:
#line 4221 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_RT_XFRM; }
#line 10987 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 774:
#line 4225 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1);
			}
#line 10995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 775:
#line 4229 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 11003 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 776:
#line 4233 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 11011 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 777:
#line 4238 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 11017 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 778:
#line 4239 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 11023 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 779:
#line 4242 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 11029 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 780:
#line 4243 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 11035 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 781:
#line 4244 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_MARK; }
#line 11041 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 782:
#line 4245 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATE; }
#line 11047 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 783:
#line 4246 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 11053 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 784:
#line 4247 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 11059 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 785:
#line 4248 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 11065 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 786:
#line 4249 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 11071 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 787:
#line 4250 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 11077 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 788:
#line 4251 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 11083 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 789:
#line 4252 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 11089 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 790:
#line 4253 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 11095 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 791:
#line 4254 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 11101 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 792:
#line 4255 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 11107 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 794:
#line 4259 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC; }
#line 11113 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 795:
#line 4260 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST; }
#line 11119 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 796:
#line 4261 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 11125 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 797:
#line 4262 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 11131 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 798:
#line 4263 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 11137 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 799:
#line 4264 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 11143 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 801:
#line 4268 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP; }
#line 11149 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 802:
#line 4269 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP; }
#line 11155 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 803:
#line 4270 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_SRC_IP6; }
#line 11161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 804:
#line 4271 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_DST_IP6; }
#line 11167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 805:
#line 4274 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 11173 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 806:
#line 4275 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 11179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 807:
#line 4276 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 11185 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 808:
#line 4277 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 11191 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 811:
#line 4285 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 11201 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 812:
#line 4291 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 11211 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 813:
#line 4299 "parser_bison.y" /* yacc.c:1652  */
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
#line 11228 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 814:
#line 4312 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);

			}
#line 11239 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 815:
#line 4319 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_EXPECT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 11249 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 816:
#line 4325 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 11257 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 817:
#line 4331 "parser_bison.y" /* yacc.c:1652  */
    {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 11268 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 836:
#line 4360 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 11279 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 837:
#line 4368 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 11285 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 838:
#line 4369 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 11291 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 839:
#line 4370 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 11297 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 840:
#line 4374 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 11305 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 841:
#line 4379 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 11311 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 842:
#line 4380 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 11317 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 843:
#line 4381 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 11323 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 844:
#line 4385 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 11331 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 845:
#line 4390 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_VID; }
#line 11337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 846:
#line 4391 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_CFI; }
#line 11343 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 847:
#line 4392 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_PCP; }
#line 11349 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 848:
#line 4393 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 11355 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 849:
#line 4397 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 11363 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 850:
#line 4402 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HRD; }
#line 11369 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 851:
#line 4403 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PRO; }
#line 11375 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 852:
#line 4404 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_HLN; }
#line 11381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 853:
#line 4405 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_PLN; }
#line 11387 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 854:
#line 4406 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_OP; }
#line 11393 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 855:
#line 4407 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 11399 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 856:
#line 4408 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 11405 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 857:
#line 4409 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_SADDR_IP; }
#line 11411 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 858:
#line 4410 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ARPHDR_DADDR_IP; }
#line 11417 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 859:
#line 4414 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 11425 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 860:
#line 4418 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val), 0);
			}
#line 11433 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 861:
#line 4422 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = ipopt_expr_alloc(&(yyloc), (yyvsp[0].val), IPOPT_FIELD_TYPE, 0);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 11442 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 862:
#line 4428 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_VERSION; }
#line 11448 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 863:
#line 4429 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 11454 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 864:
#line 4430 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DSCP; }
#line 11460 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 865:
#line 4431 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ECN; }
#line 11466 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 866:
#line 4432 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 11472 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 867:
#line 4433 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_ID; }
#line 11478 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 868:
#line 4434 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 11484 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 869:
#line 4435 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_TTL; }
#line 11490 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 870:
#line 4436 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 11496 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 871:
#line 4437 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 11502 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 872:
#line 4438 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_SADDR; }
#line 11508 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 873:
#line 4439 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPHDR_DADDR; }
#line 11514 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 874:
#line 4442 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_LSRR; }
#line 11520 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 875:
#line 4443 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RR; }
#line 11526 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 876:
#line 4444 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_SSRR; }
#line 11532 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 877:
#line 4445 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_RA; }
#line 11538 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 878:
#line 4448 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_TYPE; }
#line 11544 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 879:
#line 4449 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_LENGTH; }
#line 11550 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 880:
#line 4450 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_VALUE; }
#line 11556 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 881:
#line 4451 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_PTR; }
#line 11562 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 882:
#line 4452 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPOPT_FIELD_ADDR_0; }
#line 11568 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 883:
#line 4456 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 11576 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 884:
#line 4461 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 11582 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 885:
#line 4462 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 11588 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 886:
#line 4463 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 11594 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 887:
#line 4464 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_ID; }
#line 11600 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 888:
#line 4465 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 11606 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 889:
#line 4466 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 11612 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 890:
#line 4467 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 11618 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 891:
#line 4471 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[0].val));
			}
#line 11626 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 892:
#line 4476 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_TYPE; }
#line 11632 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 893:
#line 4477 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 11638 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 894:
#line 4478 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_MRT; }
#line 11644 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 895:
#line 4479 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IGMPHDR_GROUP; }
#line 11650 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 896:
#line 4483 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 11658 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 897:
#line 4488 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 11664 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 898:
#line 4489 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 11670 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 899:
#line 4490 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_ECN; }
#line 11676 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 900:
#line 4491 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 11682 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 901:
#line 4492 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 11688 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 902:
#line 4493 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 11694 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 903:
#line 4494 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 11700 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 904:
#line 4495 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 11706 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 905:
#line 4496 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 11712 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 906:
#line 4499 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 11720 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 907:
#line 4504 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 11726 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 908:
#line 4505 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 11732 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 909:
#line 4506 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 11738 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 910:
#line 4507 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 11744 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 911:
#line 4508 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 11750 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 912:
#line 4509 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 11756 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 913:
#line 4510 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 11762 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 914:
#line 4511 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 11768 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 915:
#line 4515 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 11776 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 916:
#line 4520 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 11782 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 917:
#line 4521 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 11788 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 918:
#line 4522 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 11794 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 919:
#line 4523 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SPI; }
#line 11800 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 920:
#line 4524 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 11806 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 921:
#line 4528 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 11814 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 922:
#line 4533 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SPI; }
#line 11820 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 923:
#line 4534 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 11826 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 924:
#line 4538 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 11834 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 925:
#line 4543 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 11840 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 926:
#line 4544 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 11846 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 927:
#line 4545 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = COMPHDR_CPI; }
#line 11852 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 928:
#line 4549 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 11860 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 929:
#line 4554 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 11866 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 930:
#line 4555 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 11872 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 931:
#line 4556 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 11878 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 932:
#line 4557 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 11884 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 933:
#line 4561 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 11892 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 934:
#line 4566 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 11898 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 935:
#line 4567 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 11904 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 936:
#line 4568 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 11910 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 937:
#line 4569 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 11916 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 938:
#line 4573 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 11924 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 939:
#line 4577 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 11932 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 940:
#line 4581 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 11941 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 941:
#line 4587 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 11947 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 942:
#line 4588 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 11953 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 943:
#line 4589 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 11959 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 944:
#line 4590 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 11965 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 945:
#line 4591 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 11971 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 946:
#line 4592 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 11977 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 947:
#line 4593 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 11983 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 948:
#line 4594 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 11989 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 949:
#line 4595 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 11995 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 950:
#line 4596 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 12001 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 951:
#line 4599 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 12007 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 952:
#line 4600 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 12013 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 953:
#line 4601 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 12019 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 954:
#line 4602 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 12025 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 955:
#line 4603 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 12031 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 956:
#line 4604 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 12037 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 957:
#line 4605 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 12043 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 958:
#line 4606 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 12049 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 959:
#line 4607 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 12055 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 960:
#line 4608 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 12061 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 961:
#line 4609 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 12067 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 962:
#line 4610 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 12073 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 963:
#line 4613 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 12079 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 964:
#line 4614 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 12085 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 965:
#line 4615 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 12091 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 966:
#line 4616 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 12097 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 967:
#line 4617 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 12103 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 968:
#line 4618 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 12109 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 969:
#line 4619 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 12115 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 970:
#line 4620 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 12121 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 971:
#line 4624 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 12129 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 972:
#line 4629 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 12135 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 973:
#line 4630 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 12141 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 974:
#line 4631 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 12147 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 975:
#line 4635 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 12155 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 976:
#line 4640 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 12161 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 977:
#line 4641 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 12167 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 978:
#line 4642 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 12173 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 979:
#line 4643 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 12179 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 980:
#line 4647 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_th, (yyvsp[0].val));
				if ((yyval.expr))
					(yyval.expr)->payload.is_raw = true;
			}
#line 12189 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 981:
#line 4654 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_SPORT; }
#line 12195 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 982:
#line 4655 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = THDR_DPORT; }
#line 12201 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 991:
#line 4669 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 12209 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 992:
#line 4674 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 12215 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 993:
#line 4675 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 12221 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 994:
#line 4679 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 12229 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 995:
#line 4684 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 12235 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 996:
#line 4685 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 12241 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 997:
#line 4686 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_TYPE; }
#line 12247 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 998:
#line 4687 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 12253 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 999:
#line 4691 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 12261 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1000:
#line 4697 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 12269 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1001:
#line 4703 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 12277 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1002:
#line 4708 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 12283 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1003:
#line 4712 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 12291 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1004:
#line 4717 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 12297 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1005:
#line 4718 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 12303 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1006:
#line 4719 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = RT4HDR_TAG; }
#line 12309 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1007:
#line 4721 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 12317 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1008:
#line 4727 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 12325 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1009:
#line 4732 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 12331 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1010:
#line 4733 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 12337 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1011:
#line 4734 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 12343 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1012:
#line 4735 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 12349 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1013:
#line 4736 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 12355 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1014:
#line 4737 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = FRAGHDR_ID; }
#line 12361 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1015:
#line 4741 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 12369 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1016:
#line 4746 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 12375 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1017:
#line 4747 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 12381 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1018:
#line 4751 "parser_bison.y" /* yacc.c:1652  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 12389 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1019:
#line 4756 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 12395 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1020:
#line 4757 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 12401 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1021:
#line 4758 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_TYPE; }
#line 12407 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1022:
#line 4759 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 12413 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1023:
#line 4760 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 12419 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1024:
#line 4764 "parser_bison.y" /* yacc.c:1652  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 12435 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1025:
#line 4777 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 12441 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1026:
#line 4778 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 12447 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1027:
#line 4779 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 12453 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1028:
#line 4780 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 12459 "parser_bison.c" /* yacc.c:1652  */
    break;

  case 1029:
#line 4781 "parser_bison.y" /* yacc.c:1652  */
    { (yyval.val) = IPPROTO_MH; }
#line 12465 "parser_bison.c" /* yacc.c:1652  */
    break;


#line 12469 "parser_bison.c" /* yacc.c:1652  */
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
#line 4784 "parser_bison.y" /* yacc.c:1918  */

