/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

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


/* Copy the first part of user declarations.  */
#line 11 "parser_bison.y" /* yacc.c:339  */


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

#line 175 "parser_bison.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
    HOOK = 290,
    DEVICE = 291,
    DEVICES = 292,
    TABLE = 293,
    TABLES = 294,
    CHAIN = 295,
    CHAINS = 296,
    RULE = 297,
    RULES = 298,
    SETS = 299,
    SET = 300,
    ELEMENT = 301,
    MAP = 302,
    MAPS = 303,
    FLOWTABLE = 304,
    HANDLE = 305,
    RULESET = 306,
    TRACE = 307,
    INET = 308,
    NETDEV = 309,
    ADD = 310,
    UPDATE = 311,
    REPLACE = 312,
    CREATE = 313,
    INSERT = 314,
    DELETE = 315,
    GET = 316,
    LIST = 317,
    RESET = 318,
    FLUSH = 319,
    RENAME = 320,
    DESCRIBE = 321,
    IMPORT = 322,
    EXPORT = 323,
    MONITOR = 324,
    ALL = 325,
    ACCEPT = 326,
    DROP = 327,
    CONTINUE = 328,
    JUMP = 329,
    GOTO = 330,
    RETURN = 331,
    TO = 332,
    CONSTANT = 333,
    INTERVAL = 334,
    DYNAMIC = 335,
    AUTOMERGE = 336,
    TIMEOUT = 337,
    GC_INTERVAL = 338,
    ELEMENTS = 339,
    POLICY = 340,
    MEMORY = 341,
    PERFORMANCE = 342,
    SIZE = 343,
    FLOW = 344,
    OFFLOAD = 345,
    METER = 346,
    METERS = 347,
    FLOWTABLES = 348,
    NUM = 349,
    STRING = 350,
    QUOTED_STRING = 351,
    ASTERISK_STRING = 352,
    LL_HDR = 353,
    NETWORK_HDR = 354,
    TRANSPORT_HDR = 355,
    BRIDGE = 356,
    ETHER = 357,
    SADDR = 358,
    DADDR = 359,
    TYPE = 360,
    VLAN = 361,
    ID = 362,
    CFI = 363,
    PCP = 364,
    ARP = 365,
    HTYPE = 366,
    PTYPE = 367,
    HLEN = 368,
    PLEN = 369,
    OPERATION = 370,
    IP = 371,
    HDRVERSION = 372,
    HDRLENGTH = 373,
    DSCP = 374,
    ECN = 375,
    LENGTH = 376,
    FRAG_OFF = 377,
    TTL = 378,
    PROTOCOL = 379,
    CHECKSUM = 380,
    ICMP = 381,
    CODE = 382,
    SEQUENCE = 383,
    GATEWAY = 384,
    MTU = 385,
    IGMP = 386,
    MRT = 387,
    OPTIONS = 388,
    IP6 = 389,
    PRIORITY = 390,
    FLOWLABEL = 391,
    NEXTHDR = 392,
    HOPLIMIT = 393,
    ICMP6 = 394,
    PPTR = 395,
    MAXDELAY = 396,
    AH = 397,
    RESERVED = 398,
    SPI = 399,
    ESP = 400,
    COMP = 401,
    FLAGS = 402,
    CPI = 403,
    UDP = 404,
    SPORT = 405,
    DPORT = 406,
    UDPLITE = 407,
    CSUMCOV = 408,
    TCP = 409,
    ACKSEQ = 410,
    DOFF = 411,
    WINDOW = 412,
    URGPTR = 413,
    OPTION = 414,
    ECHO = 415,
    EOL = 416,
    MAXSEG = 417,
    NOOP = 418,
    SACK = 419,
    SACK0 = 420,
    SACK1 = 421,
    SACK2 = 422,
    SACK3 = 423,
    SACK_PERMITTED = 424,
    TIMESTAMP = 425,
    KIND = 426,
    COUNT = 427,
    LEFT = 428,
    RIGHT = 429,
    TSVAL = 430,
    TSECR = 431,
    DCCP = 432,
    SCTP = 433,
    VTAG = 434,
    RT = 435,
    RT0 = 436,
    RT2 = 437,
    RT4 = 438,
    SEG_LEFT = 439,
    ADDR = 440,
    LAST_ENT = 441,
    TAG = 442,
    SID = 443,
    HBH = 444,
    FRAG = 445,
    RESERVED2 = 446,
    MORE_FRAGMENTS = 447,
    DST = 448,
    MH = 449,
    META = 450,
    MARK = 451,
    IIF = 452,
    IIFNAME = 453,
    IIFTYPE = 454,
    OIF = 455,
    OIFNAME = 456,
    OIFTYPE = 457,
    SKUID = 458,
    SKGID = 459,
    NFTRACE = 460,
    RTCLASSID = 461,
    IBRIPORT = 462,
    OBRIPORT = 463,
    IBRIDGENAME = 464,
    OBRIDGENAME = 465,
    PKTTYPE = 466,
    CPU = 467,
    IIFGROUP = 468,
    OIFGROUP = 469,
    CGROUP = 470,
    CLASSID = 471,
    NEXTHOP = 472,
    CT = 473,
    L3PROTOCOL = 474,
    PROTO_SRC = 475,
    PROTO_DST = 476,
    ZONE = 477,
    DIRECTION = 478,
    EVENT = 479,
    EXPIRATION = 480,
    HELPER = 481,
    LABEL = 482,
    STATE = 483,
    STATUS = 484,
    ORIGINAL = 485,
    REPLY = 486,
    COUNTER = 487,
    NAME = 488,
    PACKETS = 489,
    BYTES = 490,
    AVGPKT = 491,
    COUNTERS = 492,
    QUOTAS = 493,
    LIMITS = 494,
    HELPERS = 495,
    LOG = 496,
    PREFIX = 497,
    GROUP = 498,
    SNAPLEN = 499,
    QUEUE_THRESHOLD = 500,
    LEVEL = 501,
    LIMIT = 502,
    RATE = 503,
    BURST = 504,
    OVER = 505,
    UNTIL = 506,
    QUOTA = 507,
    USED = 508,
    SECMARK = 509,
    SECMARKS = 510,
    NANOSECOND = 511,
    MICROSECOND = 512,
    MILLISECOND = 513,
    SECOND = 514,
    MINUTE = 515,
    HOUR = 516,
    DAY = 517,
    WEEK = 518,
    _REJECT = 519,
    WITH = 520,
    ICMPX = 521,
    SNAT = 522,
    DNAT = 523,
    MASQUERADE = 524,
    REDIRECT = 525,
    RANDOM = 526,
    FULLY_RANDOM = 527,
    PERSISTENT = 528,
    QUEUE = 529,
    QUEUENUM = 530,
    BYPASS = 531,
    FANOUT = 532,
    DUP = 533,
    FWD = 534,
    NUMGEN = 535,
    INC = 536,
    MOD = 537,
    OFFSET = 538,
    JHASH = 539,
    SYMHASH = 540,
    SEED = 541,
    POSITION = 542,
    INDEX = 543,
    COMMENT = 544,
    XML = 545,
    JSON = 546,
    VM = 547,
    NOTRACK = 548,
    EXISTS = 549,
    MISSING = 550,
    EXTHDR = 551,
    IPSEC = 552,
    MODE = 553,
    REQID = 554,
    SPNUM = 555,
    TRANSPORT = 556,
    TUNNEL = 557,
    IN = 558,
    OUT = 559
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
#define HOOK 290
#define DEVICE 291
#define DEVICES 292
#define TABLE 293
#define TABLES 294
#define CHAIN 295
#define CHAINS 296
#define RULE 297
#define RULES 298
#define SETS 299
#define SET 300
#define ELEMENT 301
#define MAP 302
#define MAPS 303
#define FLOWTABLE 304
#define HANDLE 305
#define RULESET 306
#define TRACE 307
#define INET 308
#define NETDEV 309
#define ADD 310
#define UPDATE 311
#define REPLACE 312
#define CREATE 313
#define INSERT 314
#define DELETE 315
#define GET 316
#define LIST 317
#define RESET 318
#define FLUSH 319
#define RENAME 320
#define DESCRIBE 321
#define IMPORT 322
#define EXPORT 323
#define MONITOR 324
#define ALL 325
#define ACCEPT 326
#define DROP 327
#define CONTINUE 328
#define JUMP 329
#define GOTO 330
#define RETURN 331
#define TO 332
#define CONSTANT 333
#define INTERVAL 334
#define DYNAMIC 335
#define AUTOMERGE 336
#define TIMEOUT 337
#define GC_INTERVAL 338
#define ELEMENTS 339
#define POLICY 340
#define MEMORY 341
#define PERFORMANCE 342
#define SIZE 343
#define FLOW 344
#define OFFLOAD 345
#define METER 346
#define METERS 347
#define FLOWTABLES 348
#define NUM 349
#define STRING 350
#define QUOTED_STRING 351
#define ASTERISK_STRING 352
#define LL_HDR 353
#define NETWORK_HDR 354
#define TRANSPORT_HDR 355
#define BRIDGE 356
#define ETHER 357
#define SADDR 358
#define DADDR 359
#define TYPE 360
#define VLAN 361
#define ID 362
#define CFI 363
#define PCP 364
#define ARP 365
#define HTYPE 366
#define PTYPE 367
#define HLEN 368
#define PLEN 369
#define OPERATION 370
#define IP 371
#define HDRVERSION 372
#define HDRLENGTH 373
#define DSCP 374
#define ECN 375
#define LENGTH 376
#define FRAG_OFF 377
#define TTL 378
#define PROTOCOL 379
#define CHECKSUM 380
#define ICMP 381
#define CODE 382
#define SEQUENCE 383
#define GATEWAY 384
#define MTU 385
#define IGMP 386
#define MRT 387
#define OPTIONS 388
#define IP6 389
#define PRIORITY 390
#define FLOWLABEL 391
#define NEXTHDR 392
#define HOPLIMIT 393
#define ICMP6 394
#define PPTR 395
#define MAXDELAY 396
#define AH 397
#define RESERVED 398
#define SPI 399
#define ESP 400
#define COMP 401
#define FLAGS 402
#define CPI 403
#define UDP 404
#define SPORT 405
#define DPORT 406
#define UDPLITE 407
#define CSUMCOV 408
#define TCP 409
#define ACKSEQ 410
#define DOFF 411
#define WINDOW 412
#define URGPTR 413
#define OPTION 414
#define ECHO 415
#define EOL 416
#define MAXSEG 417
#define NOOP 418
#define SACK 419
#define SACK0 420
#define SACK1 421
#define SACK2 422
#define SACK3 423
#define SACK_PERMITTED 424
#define TIMESTAMP 425
#define KIND 426
#define COUNT 427
#define LEFT 428
#define RIGHT 429
#define TSVAL 430
#define TSECR 431
#define DCCP 432
#define SCTP 433
#define VTAG 434
#define RT 435
#define RT0 436
#define RT2 437
#define RT4 438
#define SEG_LEFT 439
#define ADDR 440
#define LAST_ENT 441
#define TAG 442
#define SID 443
#define HBH 444
#define FRAG 445
#define RESERVED2 446
#define MORE_FRAGMENTS 447
#define DST 448
#define MH 449
#define META 450
#define MARK 451
#define IIF 452
#define IIFNAME 453
#define IIFTYPE 454
#define OIF 455
#define OIFNAME 456
#define OIFTYPE 457
#define SKUID 458
#define SKGID 459
#define NFTRACE 460
#define RTCLASSID 461
#define IBRIPORT 462
#define OBRIPORT 463
#define IBRIDGENAME 464
#define OBRIDGENAME 465
#define PKTTYPE 466
#define CPU 467
#define IIFGROUP 468
#define OIFGROUP 469
#define CGROUP 470
#define CLASSID 471
#define NEXTHOP 472
#define CT 473
#define L3PROTOCOL 474
#define PROTO_SRC 475
#define PROTO_DST 476
#define ZONE 477
#define DIRECTION 478
#define EVENT 479
#define EXPIRATION 480
#define HELPER 481
#define LABEL 482
#define STATE 483
#define STATUS 484
#define ORIGINAL 485
#define REPLY 486
#define COUNTER 487
#define NAME 488
#define PACKETS 489
#define BYTES 490
#define AVGPKT 491
#define COUNTERS 492
#define QUOTAS 493
#define LIMITS 494
#define HELPERS 495
#define LOG 496
#define PREFIX 497
#define GROUP 498
#define SNAPLEN 499
#define QUEUE_THRESHOLD 500
#define LEVEL 501
#define LIMIT 502
#define RATE 503
#define BURST 504
#define OVER 505
#define UNTIL 506
#define QUOTA 507
#define USED 508
#define SECMARK 509
#define SECMARKS 510
#define NANOSECOND 511
#define MICROSECOND 512
#define MILLISECOND 513
#define SECOND 514
#define MINUTE 515
#define HOUR 516
#define DAY 517
#define WEEK 518
#define _REJECT 519
#define WITH 520
#define ICMPX 521
#define SNAT 522
#define DNAT 523
#define MASQUERADE 524
#define REDIRECT 525
#define RANDOM 526
#define FULLY_RANDOM 527
#define PERSISTENT 528
#define QUEUE 529
#define QUEUENUM 530
#define BYPASS 531
#define FANOUT 532
#define DUP 533
#define FWD 534
#define NUMGEN 535
#define INC 536
#define MOD 537
#define OFFSET 538
#define JHASH 539
#define SYMHASH 540
#define SEED 541
#define POSITION 542
#define INDEX 543
#define COMMENT 544
#define XML 545
#define JSON 546
#define VM 547
#define NOTRACK 548
#define EXISTS 549
#define MISSING 550
#define EXTHDR 551
#define IPSEC 552
#define MODE 553
#define REQID 554
#define SPNUM 555
#define TRANSPORT 556
#define TUNNEL 557
#define IN 558
#define OUT 559

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 134 "parser_bison.y" /* yacc.c:355  */

	uint64_t		val;
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

#line 852 "parser_bison.c" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 882 "parser_bison.c" /* yacc.c:358  */

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
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
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
#  define YYSIZE_T unsigned int
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYLAST   5557

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  314
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  316
/* YYNRULES -- Number of rules.  */
#define YYNRULES  985
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1575

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   559

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   309,     2,     2,     2,
     310,   311,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   305,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   312,     2,   313,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   306,   308,   307,     2,     2,     2,     2,
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   789,   789,   790,   799,   800,   803,   804,   807,   815,
     829,   836,   847,   855,   856,   857,   858,   878,   879,   880,
     881,   882,   883,   884,   885,   886,   887,   888,   889,   890,
     891,   892,   895,   899,   906,   910,   918,   922,   926,   933,
     940,   944,   951,   960,   964,   968,   973,   977,   981,   987,
     993,   997,  1004,  1008,  1016,  1023,  1030,  1034,  1041,  1050,
    1054,  1058,  1062,  1066,  1070,  1076,  1082,  1086,  1090,  1094,
    1098,  1102,  1106,  1110,  1114,  1118,  1122,  1126,  1130,  1134,
    1138,  1142,  1146,  1150,  1154,  1160,  1166,  1170,  1174,  1178,
    1182,  1186,  1190,  1194,  1198,  1202,  1206,  1210,  1214,  1218,
    1222,  1226,  1230,  1234,  1238,  1242,  1246,  1250,  1254,  1258,
    1262,  1266,  1270,  1274,  1278,  1282,  1288,  1292,  1296,  1300,
    1304,  1308,  1314,  1318,  1322,  1326,  1330,  1334,  1338,  1344,
    1351,  1357,  1365,  1371,  1379,  1388,  1389,  1392,  1393,  1394,
    1395,  1396,  1397,  1398,  1399,  1402,  1403,  1406,  1407,  1408,
    1411,  1420,  1426,  1440,  1441,  1442,  1443,  1444,  1455,  1465,
    1476,  1486,  1497,  1508,  1517,  1526,  1537,  1551,  1557,  1558,
    1559,  1560,  1561,  1562,  1570,  1575,  1576,  1577,  1578,  1583,
    1588,  1593,  1598,  1603,  1608,  1611,  1612,  1615,  1619,  1622,
    1623,  1624,  1625,  1629,  1634,  1635,  1636,  1637,  1642,  1653,
    1662,  1671,  1680,  1689,  1694,  1699,  1702,  1706,  1712,  1713,
    1717,  1722,  1723,  1724,  1725,  1738,  1744,  1751,  1756,  1761,
    1764,  1772,  1786,  1787,  1807,  1812,  1813,  1814,  1815,  1822,
    1823,  1824,  1825,  1832,  1833,  1834,  1835,  1841,  1842,  1843,
    1844,  1850,  1851,  1852,  1853,  1860,  1861,  1862,  1863,  1870,
    1871,  1872,  1873,  1874,  1877,  1905,  1912,  1916,  1919,  1925,
    1931,  1938,  1947,  1948,  1951,  1952,  1955,  1966,  1967,  1970,
    1973,  1974,  1975,  1978,  1993,  1994,  1997,  1998,  1999,  2000,
    2001,  2002,  2005,  2014,  2023,  2031,  2039,  2047,  2055,  2063,
    2072,  2079,  2086,  2094,  2102,  2110,  2118,  2126,  2134,  2138,
    2143,  2151,  2158,  2165,  2178,  2182,  2189,  2193,  2199,  2211,
    2217,  2224,  2225,  2226,  2227,  2230,  2231,  2232,  2233,  2234,
    2235,  2236,  2237,  2238,  2239,  2240,  2241,  2242,  2243,  2244,
    2245,  2246,  2247,  2250,  2254,  2260,  2266,  2271,  2280,  2285,
    2290,  2293,  2299,  2304,  2312,  2313,  2315,  2319,  2327,  2331,
    2334,  2338,  2344,  2345,  2348,  2354,  2358,  2361,  2366,  2371,
    2376,  2381,  2386,  2392,  2422,  2426,  2430,  2434,  2438,  2444,
    2448,  2451,  2455,  2461,  2470,  2489,  2497,  2498,  2499,  2502,
    2503,  2506,  2507,  2522,  2538,  2546,  2547,  2548,  2551,  2552,
    2555,  2556,  2557,  2572,  2573,  2574,  2575,  2576,  2579,  2582,
    2589,  2593,  2604,  2615,  2625,  2631,  2634,  2635,  2638,  2644,
    2650,  2656,  2663,  2670,  2678,  2679,  2680,  2681,  2682,  2683,
    2684,  2685,  2686,  2687,  2688,  2689,  2692,  2693,  2697,  2703,
    2704,  2710,  2711,  2717,  2718,  2724,  2727,  2728,  2747,  2748,
    2751,  2755,  2758,  2764,  2770,  2781,  2782,  2783,  2786,  2787,
    2788,  2791,  2795,  2799,  2804,  2809,  2814,  2820,  2824,  2828,
    2834,  2835,  2838,  2841,  2845,  2850,  2856,  2857,  2860,  2863,
    2867,  2871,  2875,  2880,  2887,  2892,  2900,  2905,  2914,  2915,
    2921,  2922,  2923,  2926,  2927,  2930,  2936,  2940,  2943,  2948,
    2954,  2955,  2961,  2962,  2965,  2966,  2969,  2975,  2982,  2989,
    2999,  3000,  3003,  3011,  3022,  3029,  3032,  3038,  3042,  3045,
    3051,  3060,  3071,  3077,  3103,  3104,  3111,  3120,  3131,  3132,
    3133,  3134,  3135,  3136,  3137,  3138,  3139,  3140,  3141,  3142,
    3143,  3144,  3145,  3148,  3171,  3172,  3173,  3176,  3177,  3178,
    3179,  3180,  3183,  3187,  3190,  3194,  3201,  3204,  3218,  3219,
    3223,  3229,  3230,  3236,  3237,  3243,  3244,  3250,  3253,  3254,
    3273,  3279,  3285,  3286,  3287,  3290,  3296,  3297,  3298,  3301,
    3308,  3313,  3318,  3321,  3325,  3329,  3335,  3336,  3343,  3349,
    3350,  3353,  3359,  3363,  3366,  3370,  3376,  3377,  3380,  3381,
    3384,  3385,  3388,  3399,  3407,  3428,  3436,  3450,  3458,  3459,
    3462,  3463,  3466,  3481,  3487,  3493,  3500,  3514,  3522,  3530,
    3537,  3542,  3553,  3575,  3583,  3587,  3591,  3597,  3603,  3611,
    3612,  3613,  3616,  3617,  3621,  3627,  3628,  3634,  3635,  3641,
    3642,  3648,  3651,  3652,  3671,  3672,  3675,  3683,  3684,  3685,
    3686,  3687,  3688,  3689,  3690,  3691,  3692,  3693,  3694,  3697,
    3698,  3699,  3700,  3701,  3708,  3715,  3722,  3729,  3736,  3743,
    3750,  3757,  3764,  3771,  3778,  3785,  3788,  3789,  3790,  3791,
    3792,  3793,  3796,  3800,  3804,  3808,  3812,  3816,  3822,  3823,
    3833,  3837,  3841,  3857,  3858,  3861,  3862,  3863,  3864,  3865,
    3868,  3869,  3870,  3871,  3872,  3873,  3874,  3875,  3876,  3877,
    3878,  3879,  3880,  3881,  3882,  3883,  3884,  3885,  3886,  3887,
    3888,  3891,  3904,  3908,  3922,  3926,  3930,  3936,  3942,  3943,
    3946,  3947,  3950,  3951,  3954,  3960,  3961,  3964,  3965,  3968,
    3969,  3972,  3973,  3976,  3984,  4011,  4016,  4021,  4027,  4028,
    4031,  4035,  4055,  4056,  4057,  4058,  4061,  4065,  4069,  4075,
    4076,  4079,  4080,  4081,  4082,  4083,  4084,  4085,  4086,  4087,
    4088,  4089,  4090,  4091,  4092,  4093,  4096,  4097,  4098,  4099,
    4100,  4101,  4102,  4105,  4106,  4107,  4108,  4111,  4112,  4113,
    4114,  4117,  4118,  4121,  4127,  4135,  4148,  4155,  4161,  4170,
    4171,  4172,  4173,  4174,  4175,  4176,  4177,  4178,  4179,  4180,
    4181,  4182,  4183,  4184,  4185,  4186,  4189,  4198,  4199,  4200,
    4203,  4209,  4210,  4211,  4214,  4220,  4221,  4222,  4223,  4226,
    4232,  4233,  4234,  4235,  4236,  4237,  4238,  4239,  4240,  4243,
    4249,  4250,  4251,  4252,  4253,  4254,  4255,  4256,  4257,  4258,
    4259,  4260,  4263,  4269,  4270,  4271,  4272,  4273,  4274,  4275,
    4278,  4284,  4285,  4286,  4287,  4290,  4296,  4297,  4298,  4299,
    4300,  4301,  4302,  4303,  4304,  4306,  4312,  4313,  4314,  4315,
    4316,  4317,  4318,  4319,  4322,  4328,  4329,  4330,  4331,  4332,
    4335,  4341,  4342,  4345,  4351,  4352,  4353,  4356,  4362,  4363,
    4364,  4365,  4368,  4374,  4375,  4376,  4377,  4380,  4384,  4388,
    4395,  4396,  4397,  4398,  4399,  4400,  4401,  4402,  4403,  4404,
    4407,  4408,  4409,  4410,  4411,  4412,  4413,  4414,  4415,  4416,
    4417,  4418,  4421,  4422,  4423,  4424,  4425,  4426,  4427,  4428,
    4431,  4437,  4438,  4439,  4442,  4448,  4449,  4450,  4451,  4454,
    4455,  4456,  4457,  4458,  4459,  4460,  4461,  4464,  4470,  4471,
    4474,  4480,  4481,  4482,  4483,  4486,  4492,  4498,  4504,  4507,
    4513,  4514,  4515,  4516,  4522,  4528,  4529,  4530,  4531,  4532,
    4533,  4536,  4542,  4543,  4546,  4552,  4553,  4554,  4555,  4556,
    4559,  4573,  4574,  4575,  4576,  4577
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
  "\"elements\"", "\"policy\"", "\"memory\"", "\"performance\"",
  "\"size\"", "\"flow\"", "\"offload\"", "\"meter\"", "\"meters\"",
  "\"flowtables\"", "\"number\"", "\"string\"", "\"quoted string\"",
  "\"string with a trailing asterisk\"", "\"ll\"", "\"nh\"", "\"th\"",
  "\"bridge\"", "\"ether\"", "\"saddr\"", "\"daddr\"", "\"type\"",
  "\"vlan\"", "\"id\"", "\"cfi\"", "\"pcp\"", "\"arp\"", "\"htype\"",
  "\"ptype\"", "\"hlen\"", "\"plen\"", "\"operation\"", "\"ip\"",
  "\"version\"", "\"hdrlength\"", "\"dscp\"", "\"ecn\"", "\"length\"",
  "\"frag-off\"", "\"ttl\"", "\"protocol\"", "\"checksum\"", "\"icmp\"",
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
  "\"zone\"", "\"direction\"", "\"event\"", "\"expiration\"", "\"helper\"",
  "\"label\"", "\"state\"", "\"status\"", "\"original\"", "\"reply\"",
  "\"counter\"", "\"name\"", "\"packets\"", "\"bytes\"", "\"avgpkt\"",
  "\"counters\"", "\"quotas\"", "\"limits\"", "\"helpers\"", "\"log\"",
  "\"prefix\"", "\"group\"", "\"snaplen\"", "\"queue-threshold\"",
  "\"level\"", "\"limit\"", "\"rate\"", "\"burst\"", "\"over\"",
  "\"until\"", "\"quota\"", "\"used\"", "\"secmark\"", "\"secmarks\"",
  "\"nanosecond\"", "\"microsecond\"", "\"millisecond\"", "\"second\"",
  "\"minute\"", "\"hour\"", "\"day\"", "\"week\"", "\"reject\"",
  "\"with\"", "\"icmpx\"", "\"snat\"", "\"dnat\"", "\"masquerade\"",
  "\"redirect\"", "\"random\"", "\"fully-random\"", "\"persistent\"",
  "\"queue\"", "\"num\"", "\"bypass\"", "\"fanout\"", "\"dup\"", "\"fwd\"",
  "\"numgen\"", "\"inc\"", "\"mod\"", "\"offset\"", "\"jhash\"",
  "\"symhash\"", "\"seed\"", "\"position\"", "\"index\"", "\"comment\"",
  "\"xml\"", "\"json\"", "\"vm\"", "\"notrack\"", "\"exists\"",
  "\"missing\"", "\"exthdr\"", "\"ipsec\"", "\"mode\"", "\"reqid\"",
  "\"spnum\"", "\"transport\"", "\"tunnel\"", "\"in\"", "\"out\"", "'='",
  "'{'", "'}'", "'|'", "'$'", "'('", "')'", "'['", "']'", "$accept",
  "input", "stmt_separator", "opt_newline", "common_block", "line",
  "base_cmd", "add_cmd", "replace_cmd", "create_cmd", "insert_cmd",
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
  "ct_timeout_block", "limit_block", "secmark_block", "type_identifier",
  "hook_spec", "prio_spec", "extended_prio_name", "extended_prio_spec",
  "int_num", "dev_spec", "policy_spec", "chain_policy", "identifier",
  "string", "time_spec", "family_spec", "family_spec_explicit",
  "table_spec", "tableid_spec", "chain_spec", "chainid_spec",
  "chain_identifier", "set_spec", "setid_spec", "set_identifier",
  "flowtable_spec", "flowtable_identifier", "obj_spec", "objid_spec",
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
  "tproxy_stmt", "primary_stmt_expr", "shift_stmt_expr", "and_stmt_expr",
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
  "timeout_states", "timeout_state", "ct_timeout_config", "ct_obj_alloc",
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
  "arp_hdr_field", "ip_hdr_expr", "ip_hdr_field", "icmp_hdr_expr",
  "icmp_hdr_field", "igmp_hdr_expr", "igmp_hdr_field", "ip6_hdr_expr",
  "ip6_hdr_field", "icmp6_hdr_expr", "icmp6_hdr_field", "auth_hdr_expr",
  "auth_hdr_field", "esp_hdr_expr", "esp_hdr_field", "comp_hdr_expr",
  "comp_hdr_field", "udp_hdr_expr", "udp_hdr_field", "udplite_hdr_expr",
  "udplite_hdr_field", "tcp_hdr_expr", "tcp_hdr_field",
  "tcp_hdr_option_type", "tcp_hdr_option_field", "dccp_hdr_expr",
  "dccp_hdr_field", "sctp_hdr_expr", "sctp_hdr_field", "exthdr_expr",
  "hbh_hdr_expr", "hbh_hdr_field", "rt_hdr_expr", "rt_hdr_field",
  "rt0_hdr_expr", "rt0_hdr_field", "rt2_hdr_expr", "rt2_hdr_field",
  "rt4_hdr_expr", "rt4_hdr_field", "frag_hdr_expr", "frag_hdr_field",
  "dst_hdr_expr", "dst_hdr_field", "mh_hdr_expr", "mh_hdr_field",
  "exthdr_exists_expr", "exthdr_key", YY_NULLPTR
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
     555,   556,   557,   558,   559,    61,   123,   125,   124,    36,
      40,    41,    91,    93
};
# endif

#define YYPACT_NINF -1184

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1184)))

#define YYTABLE_NINF -783

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1184,  5303, -1184,   362, -1184, -1184,    88,   111,   111,   111,
     572,   572,   572,   572,   572,   572,   572, -1184, -1184,  1895,
     194,  1378,   198,   892,   342,  3864,   775,   793,   280,  4607,
      24,   101,   363, -1184, -1184, -1184, -1184,    34,   572,   572,
     572,   572, -1184, -1184, -1184,   624, -1184,   111, -1184,   111,
     108,  4265, -1184,   362, -1184,   145,   157,   362,   160,   165,
    4265,   111, -1184,   169, -1184,   111, -1184, -1184,   572, -1184,
     572,   572,   572,   572,   572,   572,    47,   572,   572,   572,
     572, -1184,   572, -1184,   572,   572,   572,   572,   572,   572,
     572,    69,   572,   572,   572,   572, -1184,   572, -1184,   572,
     572,   572,   572,  1381,   572,   572,   572,   572,   379,   572,
     572,   572,    22,   572,  1535,  1633,  1892,   572,   572,   572,
    1941, -1184,   572,  2358,  2362,   572, -1184,   572,   572,   572,
     572,   572,   465,   572, -1184,   572, -1184,   631,   567,    70,
     391, -1184, -1184, -1184, -1184,   695,   701,  1103,  3011,   765,
     136,  1715,  1567,   857,   150,   386,   494,   444,  2500,    17,
     394,  1664,   324,   336,   286,    41,   736,   170,   446,  3925,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
    2529,   171,  4470,   243,   755,   254,   111,  4607, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184,   536, -1184, -1184,   240, -1184, -1184,   536, -1184,
   -1184, -1184, -1184,   938,   572,   572,   111,   302,   314,   341,
     828, -1184, -1184, -1184, -1184,   485,   502,   518, -1184, -1184,
   -1184,   138,   585, -1184, -1184, -1184, -1184, -1184,     4,     4,
   -1184,   227,   111,  4636,  2020,   384, -1184,   274,   175, -1184,
   -1184, -1184, -1184, -1184, -1184,   557,   143, -1184,   655, -1184,
     378,  4265, -1184, -1184, -1184, -1184, -1184, -1184,   388, -1184,
     474, -1184, -1184, -1184,   409, -1184,  2816, -1184, -1184,    12,
   -1184,   174, -1184, -1184, -1184,   692, -1184,    68, -1184, -1184,
     641, -1184, -1184, -1184,   681,   668,   691,   415, -1184,   223,
   -1184,  3703, -1184, -1184, -1184,   694, -1184, -1184, -1184,   700,
   -1184,  3720,  3720, -1184,   441,   454, -1184, -1184,   459, -1184,
   -1184, -1184,   482, -1184,   497,   677,  4265,   160,   165, -1184,
     169, -1184, -1184,   572,   572,   302,   314,   341,   828,  4265,
     112, -1184, -1184,   133, -1184, -1184, -1184,   328, -1184, -1184,
     169, -1184, -1184, -1184, -1184,   572,   333, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184,   169, -1184, -1184, -1184, -1184,
   -1184,   572, -1184, -1184, -1184, -1184, -1184,   572,   572, -1184,
   -1184, -1184,   714,   731,   572, -1184,   572, -1184,   572, -1184,
     572, -1184, -1184, -1184, -1184,   572, -1184, -1184,   572, -1184,
     572, -1184, -1184, -1184, -1184, -1184, -1184, -1184,   572, -1184,
     111, -1184, -1184, -1184, -1184,   809, -1184, -1184, -1184, -1184,
   -1184,   814,    18, -1184, -1184, -1184,   737,    -6, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184,   303,   337, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184,  2367, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184,    27, -1184, -1184,   522, -1184, -1184,
   -1184, -1184, -1184, -1184,   524, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184,  1800, -1184, -1184, -1184, -1184,
     559,   139,   564,   760, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184,   560, -1184,   551, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184,   536, -1184, -1184, -1184,   784,
   -1184, -1184,   453, -1184, -1184, -1184, -1184,   827, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184,  2943,   852,  4607, -1184,
   -1184, -1184, -1184,   860,   908,     0,   888,   891,   901,    13,
    1800,   913,  4049,  4049,   453,  4049,   867,  4049,  4049,   893,
   -1184,  3720,    52, -1184,   828, -1184, -1184,   878,   880,   388,
   -1184,   504,   828,   886,   890,   894,   828,   474, -1184,   247,
   -1184,  4049, -1184, -1184,  3154,   695,   701,  1103,  2880, -1184,
    1074,   416, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
     859,   969,   978,   703,   377,   161, -1184, -1184, -1184, -1184,
   -1184,  1016,   746,  1026, -1184, -1184, -1184, -1184,  1027, -1184,
   -1184, -1184, -1184,   960, -1184, -1184,  1038,  1042, -1184,  1046,
   -1184, -1184, -1184, -1184,  1045, -1184,  3281, -1184,  1045,  4049,
   -1184, -1184,   692, -1184,  1053, -1184,   111,   756,   111,    20,
   -1184,  4872,  4872,  4872,  4872,  4872,  4607,    64,  3720, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184,  4872, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
    1062, -1184,   865,  1054,  1055,   764,   159,  1067, -1184, -1184,
   -1184,  3720,  4049,  4049,   362,  1062, -1184,   362, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184,   774,   777,   778, -1184,   780,
     785, -1184, -1184, -1184, -1184, -1184, -1184, -1184,   999,  1002,
    1003, -1184, -1184,  1004, -1184, -1184, -1184, -1184,   572,   572,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,  1006,
     567, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184,   601, -1184,  1007,  1009, -1184, -1184,
     794, -1184,   806, -1184, -1184, -1184, -1184, -1184, -1184,  1010,
    1013,   826,  1017,   361, -1184, -1184, -1184,   808,   810,   877,
   -1184, -1184,  1021,    14,  4049,  3011,  1715,  1112,  3492,    68,
      21,  1114,   828,   828,  1029,  4607,  4049,  4049,  4049, -1184,
    1032,  1083,  4049, -1184, -1184,  1035, -1184,    14,  1097, -1184,
    4049, -1184,   655,   911,    21, -1184,   463,  1067,   655, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184,  1005,   124, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184,  1030,  1031,  1078,
    1037, -1184,  4049,  1140,  5031,  4872,  5031,  5031,  5031,  1056,
    5031,  5031,   340,  4049,  1045,  4049,  2335,  2335,  4049,   746,
    4049,   746, -1184, -1184,   642,  4607, -1184,  4607, -1184, -1184,
   -1184,   865,  1054,  1055, -1184,   111,   655, -1184, -1184,   836,
    4872,  4872,  4872,  4872,  4872,  4872,  4872,  1063,  4872,  4872,
   -1184, -1184, -1184, -1184, -1184,   514,  2081,   581,  1886,   500,
   -1184, -1184, -1184, -1184, -1184,   842,   854, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184,  1151, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184,   850,   851, -1184, -1184, -1184,
   -1184,   826,   392,  1072, -1184, -1184, -1184, -1184, -1184,   848,
   -1184, -1184,  1075,   107, -1184, -1184,   915, -1184,  4049,  4049,
    1165, -1184,  1080, -1184,    21, -1184, -1184, -1184,   870,  1114,
    4265,    21, -1184, -1184, -1184, -1184,  4049, -1184,   140,   915,
    4049,  1144, -1184,  4803, -1184,    21,  3720, -1184, -1184, -1184,
   -1184,  1179, -1184,  1107,  1108, -1184,  1109, -1184,  4049, -1184,
   -1184, -1184, -1184,   859,   969,   978, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184,  1200, -1184, -1184, -1184, -1184,   746, -1184,
     746,  1045, -1184,   395,  4265, -1184,  3922,    53, -1184, -1184,
   -1184, -1184, -1184,   865,  1054,  1055, -1184, -1184, -1184, -1184,
     111,   111,   111,   111,  1113,   121,   111,   111,   111,   111,
   -1184, -1184, -1184,   362,   884,  1124, -1184, -1184, -1184,   362,
     362,   362, -1184,  1080,  1080,   904,   912,  1130,   360,   789,
   -1184, -1184, -1184,   362,  1080,   921,   360,   789, -1184, -1184,
   -1184,   362,  1137,   928, -1184, -1184, -1184,  1579,  2308,   610,
    1893,   885, -1184, -1184,  1141, -1184, -1184, -1184,  1147, -1184,
   -1184, -1184, -1184, -1184,   263,   195, -1184,   523,   985,  1150,
   -1184, -1184, -1184,  4049, -1184, -1184, -1184,  4607,   931,    21,
   -1184,   523,   985, -1184, -1184,  4049,   655, -1184,  1067, -1184,
     124, -1184, -1184, -1184, -1184,  4049,  1045,  1045,  4607,  1077,
   -1184,    43,   944,  1248,   655, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184,   111,   111, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184,  1222, -1184, -1184, -1184,   362,
     362,   169, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184,   580, -1184, -1184, -1184, -1184, -1184,   729, -1184,
   -1184,   362,   169,   682,   729, -1184,  1119,   962, -1184, -1184,
   -1184, -1184, -1184,   270,  1126, -1184,   826,   970,   183,   572,
   -1184, -1184, -1184, -1184,  1180,   572, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184,  1033,  1184, -1184,    14, -1184,
    4265, -1184,  1033, -1184, -1184, -1184, -1184, -1184,   973,  4607,
   -1184, -1184,  1233,  3922, -1184,   975,   977,   982,   983, -1184,
   -1184,   986,   988,   989,   990,  1196, -1184, -1184, -1184,   360,
   -1184,   789, -1184, -1184, -1184,   710, -1184,    48,   362,  1203,
     362, -1184, -1184, -1184,   995, -1184, -1184,  1296,   362,  1186,
     362,  1228, -1184,    40, -1184,  1019, -1184, -1184,  1020,   655,
   -1184, -1184, -1184, -1184,  1023,  1025, -1184, -1184, -1184, -1184,
    1287, -1184, -1184,   362,   362,   362,   362,   580,  1239, -1184,
   -1184, -1184,   719, -1184, -1184, -1184, -1184,    54, -1184, -1184,
    1240, -1184, -1184,   183, -1184,  1106, -1184, -1184, -1184, -1184,
   -1184,  2593,  1594,  1925,  1161, -1184, -1184,  1155,   464,    91,
     403,   828,  1119, -1184, -1184, -1184, -1184, -1184, -1184,  1243,
    1249,   130, -1184,  1337,    60, -1184,   362, -1184,   362,   362,
     362,   362,   752,  1219,   362, -1184, -1184, -1184,   362, -1184,
   -1184, -1184,   362, -1184, -1184, -1184,   362, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184,  1250,  1240,   362, -1184,
   -1184, -1184, -1184, -1184,   362,   362, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     274,   274,   274,   274,   274,   274,   274,   278,   281,   274,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   135,   280,   279,   276,   277,     0,   274,   274,
     274,   274,    14,    13,     3,     0,    17,     0,   275,     0,
     298,     0,    12,     0,   269,     0,     0,     0,    32,    34,
       0,     0,   174,     0,   193,     0,   210,    18,   274,    19,
     274,   274,   274,   274,   274,   274,     0,   274,   274,   274,
     274,    20,   274,    21,   274,   274,   274,   274,   274,   274,
     274,     0,   274,   274,   274,   274,    22,   274,    23,   274,
     304,   274,   304,   304,   274,   274,   304,   304,     0,   274,
     304,   304,     0,   274,   304,   304,   304,   274,   274,   274,
     304,    24,   274,   304,   304,   274,    25,   274,   274,   274,
     274,   304,     0,   274,    26,   274,    27,     0,     0,     0,
     546,   517,   270,   271,   272,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     690,   691,   692,   693,   694,   695,   696,   697,   698,   699,
     700,   701,   702,   703,   704,   705,   706,   707,   708,   709,
       0,     0,     0,     0,     0,   710,     0,     0,    31,   515,
     514,   518,   519,   150,   529,   530,   523,   681,   524,   527,
     531,   528,   525,   526,   520,   789,   790,   791,   792,   793,
     794,   795,   796,   797,   798,   799,   800,   801,   802,   803,
     804,   805,   521,   939,   940,   941,   942,   943,   944,   945,
     946,   522,     0,   147,   148,     0,    28,   131,     0,    29,
     133,   136,    30,   137,   274,   274,     0,    42,     0,   378,
       0,    16,    15,   282,   284,     0,     0,     0,   300,   299,
     301,     0,     0,   500,   501,   672,   673,   674,     0,     0,
     677,   506,     0,     0,     0,   346,   354,     0,   378,   399,
     406,   407,   462,   468,   485,     0,     0,   714,     7,    37,
     306,   308,   319,   309,   315,   334,   314,   311,   344,   321,
     352,   312,   313,   322,   400,   323,     0,   324,   327,   461,
     328,   467,   329,   330,   325,   483,   331,     0,   332,   317,
       0,   505,   316,   548,   551,   553,   555,   557,   558,   566,
     568,     0,   567,   512,   333,   681,   320,   326,   318,   520,
       8,     0,     0,    11,     0,     0,    36,   287,     0,    40,
     186,   185,     0,   290,     0,     0,     0,    50,    52,   174,
       0,   193,   210,   274,   274,    58,     0,   378,     0,     0,
       0,    66,    67,     0,    68,    69,    70,     0,    71,    72,
       0,    73,    75,   599,   598,   274,     0,    76,    77,    81,
      82,    78,    79,    83,    84,     0,    86,   305,    87,    88,
      89,   274,    90,    92,   112,   111,   105,   274,   304,   109,
     108,   110,   599,     0,   274,    95,   274,    93,   274,    96,
     274,    99,   101,    98,   104,   274,   102,   118,   274,   116,
     274,   119,   121,   122,   123,   124,   125,   128,   274,   127,
       0,   807,   808,   809,   516,     0,   537,   538,   539,   540,
     541,   543,     0,   718,   719,   717,     0,     0,   811,   812,
     813,   810,   818,   815,   816,   817,   814,     0,     0,   820,
     821,   822,   823,   824,   819,   840,   841,   835,   830,   831,
     832,   833,   834,   836,   837,   838,   839,   829,   843,   846,
     845,   844,   847,   848,   849,   842,   851,   852,   853,   854,
     850,   863,   864,   856,   857,   858,   860,   859,   861,   862,
     855,   866,   871,   868,   867,   872,   870,   869,   873,   865,
     876,   879,   875,   877,   878,   874,   882,   881,   880,   884,
     885,   886,   883,   890,   891,   888,   889,   887,   896,   893,
     894,   895,   892,   908,   902,   905,   906,   900,   901,   903,
     904,   907,   909,     0,   897,   933,   931,   932,   930,   938,
     935,   936,   937,   934,   953,   738,   952,   744,   739,   951,
     954,   742,   743,   745,     0,   740,   950,     0,   955,   958,
     957,   961,   960,   962,     0,   959,   949,   948,   947,   970,
     967,   965,   966,   968,   969,   964,   973,   972,   971,   977,
     976,   979,   975,   978,   974,   682,   685,   686,   687,   689,
     688,   710,   680,   683,   684,   759,   760,   752,   753,   751,
     761,   762,   780,   755,   764,   757,   758,   763,   754,   756,
     749,   750,   778,   777,   779,     0,   746,   765,   723,   722,
       0,   566,     0,     0,   982,   981,   983,   984,   985,   980,
     727,   728,   726,   513,     0,   130,   149,   132,   138,   139,
     141,   140,   143,   144,   142,   145,   610,   610,   292,     0,
     593,    43,   387,   613,    47,   376,   377,     0,   595,    44,
     596,   597,    48,   295,   296,   297,     0,     0,     0,   679,
     678,   675,   676,     0,     0,     0,   682,   680,     0,     0,
       0,   746,     0,     0,   387,     0,     0,     0,     0,     0,
       6,     0,     0,   570,     0,   307,   310,     0,     0,   345,
     348,     0,     0,     0,     0,     0,     0,   353,   355,     0,
     398,     0,   444,   645,     0,   637,   640,   641,   638,   644,
     639,     0,   648,   646,   647,   643,   642,   634,   635,   426,
     429,   431,   433,   435,   436,   441,   448,   445,   446,   447,
     449,   451,   405,   414,   415,   425,   636,   416,   423,   417,
     424,   420,   421,     0,   418,   419,     0,   450,   422,     0,
     480,   481,   482,   460,   465,   478,     0,   466,   471,     0,
     492,   493,   484,   486,   489,   490,     0,     0,     0,     0,
     507,     0,     0,     0,     0,     0,     0,     0,     0,   666,
     667,   668,   669,   670,   671,   637,   640,   641,   638,   658,
     659,   639,   660,   657,   656,   661,   654,   655,   653,   662,
     663,   664,     0,   564,   649,   650,   562,   563,   620,   621,
     615,   614,   625,   627,   629,   631,   632,   619,   651,   652,
     622,     0,     0,     0,     0,   591,   590,     0,   153,   168,
     175,   194,   211,   302,    49,     0,     0,     0,    56,     0,
       0,   610,   610,    59,    63,    60,    64,    65,     0,     0,
       0,    74,   610,     0,    85,    91,   107,   106,   274,   274,
     113,    94,    97,   100,   103,   117,   120,   126,   129,     0,
       0,   536,   534,   535,   533,   547,   544,   545,   825,   827,
     826,   828,   913,   920,   910,   912,   911,   915,   916,   917,
     918,   919,   914,   921,   899,   741,     0,     0,   766,   767,
       0,   769,     0,   768,   770,   771,   747,   748,   772,     0,
       0,   720,     0,     0,   532,   134,   146,     0,     0,     0,
     385,   386,     0,     0,     0,   638,   639,   408,     0,     0,
     494,   496,     0,     0,     0,     0,     0,     0,     0,   342,
       0,   772,     0,   347,   375,     0,   384,     0,   474,   476,
       0,   587,     7,     7,   579,   581,   632,   586,     7,   569,
     303,   350,   351,   349,   368,   367,     0,     0,   366,   362,
     357,   358,   359,   360,   363,   361,   356,     0,     0,     0,
       0,   457,     0,   452,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   459,     0,     0,     0,     0,     0,
       0,   469,   488,   487,     0,     0,   509,     0,   508,   549,
     550,   552,   554,   556,   559,     0,     7,   335,   565,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     616,   712,   788,     9,    10,     0,     0,     0,     0,     0,
     153,   168,   175,   194,   211,     0,     0,   283,   285,   288,
      80,   293,   115,   114,     0,   542,   924,   923,   922,   925,
     926,   927,   928,   929,   898,     0,     0,   773,   774,   775,
     776,   720,   720,     0,   737,   725,   729,   730,   733,     0,
     237,   233,     0,     0,   380,   379,   381,   410,     0,     0,
     409,   497,     0,   585,   495,   582,   716,   715,     0,   578,
       0,   576,   713,   711,   786,   343,     0,   785,     0,   381,
       0,     0,   573,     0,   574,   580,   572,   571,   365,   371,
     372,   364,   370,     0,     0,   404,     0,   458,     0,   427,
     414,   423,   428,   430,   432,   434,   442,   443,   437,   440,
     439,   438,   454,   453,   781,   782,   783,   784,   463,   479,
     470,   472,   491,     0,     0,   337,     0,     0,   338,   665,
     618,   623,   624,   626,   628,   630,   617,   560,   561,   633,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      33,   155,   154,     0,     0,     0,    35,   170,   169,     0,
       0,     0,   183,     0,     0,     0,     0,     0,     0,     0,
      38,   177,   176,     0,     0,     0,     0,     0,    39,   196,
     195,     0,     0,     0,    41,   213,   212,     0,     0,     0,
       0,     0,   237,   233,     0,   956,   963,   724,     0,   736,
     721,   732,   731,   734,     0,     0,   592,     0,   390,     0,
     594,   411,   413,     0,   273,   584,   583,     0,     0,   577,
     787,     0,   390,   383,   475,     0,     7,   632,   588,   589,
       0,   401,   402,   403,   455,     0,   464,   473,     0,     0,
     498,     0,     0,     0,     7,   336,   286,   167,   289,   174,
     193,   291,   210,   152,     0,     0,   294,   224,   224,   224,
     224,   156,   267,   268,   266,     0,   171,   172,   173,     0,
       0,     0,   209,   208,   206,   207,   249,   251,   252,   250,
     253,   222,     0,   221,   189,   190,   192,   191,     0,   188,
     184,     0,     0,     0,     0,   205,     0,     0,    51,    53,
      54,    55,    57,     0,     0,   806,   720,     0,     0,     0,
      46,   239,   238,   240,     0,     0,    45,   235,   234,   236,
     393,   394,   395,   396,   397,   388,     0,   612,     0,   412,
       0,   510,   388,   374,   477,   575,   369,   456,     0,     0,
     499,   504,     0,   340,   339,     0,     0,     0,     0,   224,
     224,     0,     0,     0,     0,     0,   180,   181,   182,     0,
     178,     0,   179,   197,   204,     0,   203,     0,     0,     0,
       0,    62,    61,   735,     0,   601,   600,     0,     0,     0,
       0,     0,   611,     0,   382,     0,   373,   502,     0,     7,
     168,   175,   194,   211,     0,     0,   225,   241,   229,   245,
     265,   223,   187,     0,     0,     0,     0,     0,     0,   262,
     257,   256,   259,   255,   258,   214,   220,     0,   217,   215,
       0,   607,   609,     0,   603,     0,   392,   391,   511,   503,
     341,     0,     0,     0,     0,   237,   233,     0,     0,     0,
       0,     0,     0,   199,   201,   200,   202,   198,   263,     0,
       0,     7,   216,     0,     0,   604,     0,   389,     0,     0,
       0,     0,     0,     0,     0,   227,   226,   228,     0,   243,
     242,   244,     0,   231,   230,   232,     0,   247,   246,   248,
     264,   254,   261,   260,   219,   218,     0,     0,     0,   602,
     157,   158,   159,   160,     0,     0,   161,   165,   162,   166,
     606,   605,   608,   164,   163
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1184, -1184,    -1,  -943,    10, -1184, -1184,  1330, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184,    -3, -1184,   987, -1184,   272,  -352, -1044,
    -360, -1041,  -365,   103,   -75,  -354, -1040, -1047, -1184,  -359,
   -1042, -1184, -1184,  -162,   -68, -1148, -1118, -1184, -1184, -1183,
   -1178, -1184, -1184, -1184, -1184,  -150, -1184, -1184, -1184, -1184,
   -1184, -1184,   185,  -248,  -695,  1280,   -38,  1643, -1184,   669,
   -1184, -1184,   100, -1184,   154,   421, -1184,  1745,   963,  -758,
    1011, -1184, -1184,   144,  1281,  1068,    30,     6, -1184, -1184,
     177,  -298, -1184, -1184, -1184, -1184,    57, -1184, -1184, -1184,
   -1184,   645, -1184, -1184, -1184,   638, -1184, -1184, -1184,    77,
   -1184,  1092,  -960,   232, -1184,   672,   -20,    98,   102, -1184,
   -1184, -1184, -1184, -1184, -1184,  -876,   373,   374,   376, -1184,
     380, -1184, -1184, -1184, -1184, -1184,  -331, -1184,   838, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,  -303,   367,
   -1184, -1184, -1184,   605, -1184,   365,  -999, -1184, -1184,  1139,
   -1184, -1184, -1184, -1184,   604, -1184, -1184,   -62,   -22,   252,
    1385, -1184, -1184, -1184,   505,   -21, -1184, -1184, -1184, -1184,
   -1184,  -173,  -188, -1184, -1184,  -699, -1184,  1225,   -16, -1184,
     422,  -994, -1184, -1102, -1184,  -886, -1024, -1184, -1184,  1069,
     -85,  1051,   -77,  1059,   -70,  1064,  1329,   -50, -1184, -1184,
    -113, -1184,  -479,   -58,  1076, -1184,  1110,  -306,  -732,  -731,
    -709, -1184,  -318,  -702, -1184,  -161,  -213,  -686, -1184, -1074,
    1174,   -15,  1172, -1184,   -45, -1184,     3, -1184, -1011, -1184,
      45, -1184, -1184, -1184, -1184, -1184,    61,  -245,   289,   873,
     355,  1176,  1181, -1184, -1184,  -496,    -8, -1184, -1184, -1184,
     383, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184, -1184,
   -1184, -1184, -1184, -1184, -1184, -1184
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1227,   721,  1228,    44,    45,    46,    69,    81,
      83,    96,    98,   121,   126,   134,   136,   246,   249,   252,
     253,   675,   955,   247,   198,   354,  1223,  1075,   355,  1076,
     358,  1077,   359,  1358,  1359,   362,  1078,  1243,  1344,   364,
    1079,  1440,  1487,  1488,  1351,  1352,  1421,  1507,  1509,  1275,
    1274,  1508,  1510,  1353,  1229,  1438,  1482,  1483,  1484,  1512,
    1230,  1334,  1326,   199,  1285,    47,    48,   256,   382,    50,
     385,  1317,    62,   389,  1319,    66,  1322,   257,   398,  1327,
     268,   269,   270,    51,   366,  1133,   408,  1231,   300,   301,
     302,   303,   304,   305,  1057,  1197,  1198,   306,   307,   308,
     729,   730,   309,   310,   737,   738,  1015,  1009,  1161,  1162,
     311,   687,  1126,  1280,   312,   962,  1452,  1397,  1395,   313,
     314,   740,   315,   316,   317,   759,   760,   761,   762,   763,
     764,   765,  1179,   766,   767,   768,   769,   770,   771,   772,
     318,   319,   793,   320,   321,   797,   322,   323,   794,   795,
     324,   325,   802,   803,   804,   805,   969,   970,   326,   327,
     328,   329,   330,   809,   810,   331,   332,   200,   773,   774,
     333,   204,   914,   461,   462,   775,   467,   334,   335,   336,
     337,   338,   339,   846,   847,   848,   340,   341,   342,   722,
     723,  1140,  1141,   993,   994,  1134,  1135,   995,  1296,   864,
     680,   681,   688,   689,   691,   692,   395,  1447,  1389,  1524,
    1525,  1383,   957,   683,   684,   343,   865,   866,   852,   853,
     854,   855,   996,   857,   776,   777,   778,   860,   861,   344,
     701,   779,   622,   623,   207,   346,   780,   465,  1114,   650,
     781,   953,   662,  1118,  1273,   210,   782,   584,   784,   585,
     785,   645,   646,   946,   947,   647,   786,   787,   347,   348,
     788,   215,   455,   216,   471,   217,   476,   218,   484,   219,
     497,   220,   505,   221,   510,   222,   520,   223,   529,   224,
     535,   225,   538,   226,   542,   227,   547,   228,   552,   229,
     564,   934,  1104,   230,   568,   231,   573,   232,   233,   598,
     234,   586,   235,   588,   236,   590,   237,   595,   238,   605,
     239,   608,   240,   614,   241,   659
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,   360,    52,   726,   651,   878,   345,   201,   205,   877,
     843,    43,   690,   880,   206,   345,   876,   879,   798,   997,
     843,   843,   991,   856,   664,   891,   697,  1149,   250,   201,
     205,  1251,   208,   856,   856,   851,   206,  1258,   201,   205,
     894,  1259,  1261,  1260,   262,   206,  1193,   361,  1409,  1152,
    1154,   719,   350,  1194,   208,  1156,   353,   299,   808,   998,
    1314,  1521,   407,   208,   407,   407,   356,  1557,   407,   407,
    1478,   783,   407,   407,   209,   242,   407,   407,   407,  1299,
    1374,  1051,   407,  1052,  1373,   407,   407,  1055,   974,   789,
     211,   806,     3,   407,  1313,     4,   209,     5,  1363,    54,
    1267,  1269,   463,  1132,   422,   209,  1053,   979,  1155,  1124,
    1286,   916,   211,  1196,    63,    64,   254,     6,     7,     8,
       9,   211,   565,   911,   624,  1049,  1050,  1277,   859,   373,
     690,  1286,   410,   412,   720,  1496,   415,   416,   859,   859,
     420,   421,  1479,  1480,   427,   429,   431,   816,  1169,   948,
     436,   393,   248,   439,   441,  1178,    60,   577,   265,   596,
    1291,   447,   888,   142,   143,   144,  1066,   566,   567,  1031,
     201,   205,   369,   370,   371,   201,   205,   206,   597,  1067,
     858,  1068,   206,   889,    53,  -378,   818,   388,   390,   391,
     858,   858,    55,    56,    57,   208,     3,   405,   958,     4,
     208,     5,  1278,  1324,   413,   414,    54,    54,  1032,   419,
    1422,  1423,  1424,  1251,   981,   696,   700,   700,   912,   913,
     718,     6,     7,     8,     9,  1486,   379,   917,    54,   445,
     446,   816,   263,   449,   264,  1292,    68,   209,   624,   665,
      82,   506,   209,   581,   582,   667,   357,   817,   394,  1125,
     363,   796,  1159,   211,   575,  1289,   345,  1160,   211,   575,
     255,   507,   423,   980,     3,  1286,   464,     4,   508,     5,
     818,     3,   578,   374,     4,  1497,     5,   578,   536,   201,
     205,   202,   703,   790,   791,   792,   206,  1477,   606,     6,
       7,     8,     9,  1400,   537,   394,     6,     7,     8,     9,
    1384,  1464,  1465,   202,   208,   807,   975,   607,   360,  1408,
     724,  1313,   202,   196,   243,   244,   245,   704,   212,   844,
     135,   345,   454,  1533,   583,   849,  1047,  1532,   360,   844,
     844,  1203,  1445,  1204,   345,   849,   849,  1446,  1459,  1172,
     212,   685,   686,   360,   201,   205,   209,  1325,  1377,   212,
    1410,   206,  1481,  1405,   361,  1377,  1205,   201,   205,   999,
    1315,  1522,   211,   806,   206,  1443,     4,  1558,     5,   208,
    1056,  1413,   874,  1017,   361,  1201,  1202,   196,   890,   509,
     407,   663,   208,   893,   213,   887,  1018,  1378,    97,   361,
     843,   243,   244,   245,  1378,   266,   267,  1029,  1542,  1030,
    1308,  1019,  1085,  1086,     3,   918,   213,     4,   715,     5,
    1458,   209,   214,  1090,  1385,   213,  1501,   417,   418,   919,
    1502,  1504,  1503,    54,   209,   685,   686,   211,    54,     6,
       7,     8,     9,   591,   349,   142,   143,   144,  1454,   920,
     211,   678,   648,   349,   202,   790,   791,   792,   897,   202,
     351,  1298,   649,   921,   997,  1346,  1251,   991,   251,  1328,
    1329,  1330,   352,   699,   699,     3,  -151,   705,     4,  1034,
       5,  -167,   592,   593,   594,   298,  1000,   575,   196,  1347,
    1348,   212,  1379,  1067,  1010,  1068,   212,   843,  1014,  1379,
       6,     7,     8,     9,   997,   578,   372,   991,   142,   143,
     144,     3,  1386,   448,     4,  1116,     5,   713,   859,   587,
     971,   392,  1058,  1020,   466,     3,  1500,   896,     4,   569,
       5,   589,   714,   539,  1059,   653,     6,     7,     8,     9,
     843,   666,   575,   540,   541,  1252,   679,  1253,  1339,  1340,
       6,     7,     8,     9,   570,   571,   577,   213,   907,  1361,
     578,   609,   213,   202,  1210,  1070,  1349,   660,   661,  1211,
     858,  1212,   682,  1213,   610,   263,  1419,  1420,   264,   548,
    1380,   611,   357,   572,  1004,   214,  1350,  1441,  1554,   693,
     214,   678,     3,   612,     4,     4,     5,     5,  1429,   613,
     212,   685,   686,   845,   549,   550,   694,   551,   859,   859,
     859,   859,   859,   845,   845,   859,  1005,     6,     7,     8,
       9,     3,   695,  1309,     4,   543,     5,   712,   202,   544,
    1006,   731,   727,   728,   261,    17,    18,   285,     4,   859,
       5,   202,   581,   582,   717,   908,     6,     7,     8,     9,
     273,   274,   287,  1054,   545,   546,   298,   288,   859,   196,
     858,   858,   858,   858,   858,   212,   213,   858,  1007,   720,
    1117,  1214,  1232,  1233,  1234,  1235,  1236,   724,   212,  1237,
     456,   457,   956,    33,   739,  1113,   201,   205,  1268,   808,
      59,   858,    34,   206,   349,   813,  1238,  1435,    35,  1096,
    1429,  1232,  1233,  1234,  1235,  1236,   811,   812,  1237,   844,
     858,   208,  1310,   960,   961,   992,    36,  1008,  1119,   814,
    1546,   997,   682,   583,   991,  1238,   732,   733,   734,   735,
     736,   213,  1097,   815,  1136,  1137,    54,   265,  1239,   451,
     452,   453,  1215,     4,   213,     5,  1431,   365,  1191,   862,
     368,  1519,  1200,   209,  1520,   863,  1216,   868,  1206,   349,
    1208,  1209,   898,     3,   384,   365,     4,  1239,     5,   211,
     869,  1217,   349,   458,   459,   870,  1218,   460,  1219,   899,
     409,  1538,  1098,  1099,  1100,  1101,  1102,  1103,     6,     7,
       8,     9,  1390,  1391,  1392,  1393,  1394,  1139,   871,   844,
     844,   844,   844,   844,   201,   205,   844,   444,   468,   469,
     470,   206,   849,   872,   450,  1346,   472,  1254,   473,   474,
     475,  1171,   859,  1171,  1171,  1171,   909,  1171,  1171,   208,
     844,  1220,   910,  1185,  1185,   843,   243,   244,   245,  1347,
    1348,   127,   915,   128,   936,  1297,   937,  1377,   129,   844,
     130,   949,  1288,   599,   131,   849,   950,   859,   859,   859,
     859,   859,   859,   859,   951,   859,   859,   971,   600,  1139,
     952,   209,   954,  1073,   858,   843,  1074,  1354,  1355,  1356,
     498,  1357,   499,   601,  1024,  1025,  1378,   211,   959,   602,
    1061,  1062,   132,   972,   133,  1306,     3,  1307,  1240,     4,
     500,     5,   501,   502,   503,   504,  1312,  1107,  1108,   858,
     858,   858,   858,   858,   858,   858,  1349,   858,   858,  1109,
    1110,     6,     7,     8,     9,   720,  1153,  1370,   800,   801,
    1252,   963,  1253,   142,   143,   144,  1350,   603,   604,   968,
      84,   973,    85,   976,    86,   654,   977,    87,    88,    89,
     859,    90,  1473,   859,   655,   656,   978,  1131,   657,   658,
     202,  1271,  1272,   201,   205,  1332,  1333,  1474,   982,  1416,
     206,   987,  1475,  1418,  1476,  1415,  1417,   799,   800,   801,
     990,  1379,  1001,   845,  1002,   530,  1428,   668,   208,   669,
    1011,   670,   671,   859,  1012,   531,  1026,   212,  1013,   672,
     673,   454,   858,  1046,   532,   858,  1027,  1434,  1342,  1343,
     533,   534,  1170,   844,  1170,  1170,  1170,   122,  1170,  1170,
    1180,  1028,   123,   124,  1184,  1184,  1181,   790,   791,   792,
     209,  1033,   674,   201,   205,   201,   205,   125,  1186,  1187,
     206,   345,   206,  -781,  -782,   858,   211,  1035,   844,   844,
     844,   844,   844,   844,   844,  1036,   844,   844,   208,  1037,
     208,  1038,  1039,   213,   201,   205,   400,   402,   404,  1564,
    1044,   206,  1045,   845,   845,   845,   845,   845,   202,  1060,
     845,  1063,  1065,  1064,  1221,  1069,  1241,  1249,  1255,   208,
    1080,   214,   843,  1081,  1082,  1222,  1083,  1242,  1250,  1256,
     209,  1084,   209,  1087,   845,   345,  1088,  1089,  1091,  1139,
    1094,  1105,  1455,  1106,  1111,   212,   211,  1112,   211,  1113,
      91,  1115,  1122,   845,  1120,  1123,  1121,  1128,   201,   205,
     971,   209,   816,  1138,    92,   206,  1145,     3,  1146,  1148,
       4,   844,     5,  1150,   844,  1163,  1164,   211,  1158,    93,
     992,  1165,  1166,   208,    94,  1168,    95,  1199,  1262,   345,
    1176,  -739,     6,     7,     8,     9,     3,  1207,  1264,     4,
    1263,     5,     3,  1265,  1266,     4,  1270,     5,  1279,  1276,
    1283,   213,   201,   205,   844,  1284,  1287,   511,   512,   206,
    1295,     6,     7,     8,     9,   209,  1300,     6,     7,     8,
       9,   513,  1372,   514,   515,   516,  1252,   208,  1253,   214,
     859,   211,  1301,  1302,  1303,  1305,   477,   478,  1323,  1341,
     517,   518,   519,   345,   479,   480,   481,   482,   483,  1335,
       3,   971,  1331,     4,  1345,     5,  1362,   202,  1336,  1337,
    1338,  1384,  1366,  1367,  1396,  1375,   201,   205,  1401,   209,
    1195,  1376,  1360,   206,  1398,     6,     7,     8,     9,   709,
    1365,  1411,   858,  1412,  1437,   211,  1221,  1425,  1241,  1249,
    1255,   208,   690,  1550,   212,   201,   205,  1222,  1439,  1242,
    1250,  1256,   206,  1381,  1387,  1444,  1449,   845,  1453,   360,
    1457,  1460,  1451,  1461,  1382,  1388,   201,   205,  1462,  1463,
     208,  1470,  1466,   206,  1467,  1468,  1469,   202,  1486,   202,
     360,  1490,  1491,   209,   275,   276,   277,   278,   279,   280,
    1493,   208,   845,   845,   845,   845,   845,   845,   845,   211,
     845,   845,  1495,  1511,  1384,   361,  1498,  1499,   202,  1505,
     213,  1506,   209,  1518,   212,  1523,   212,  1552,  1426,  1427,
    1527,  1448,  1556,  1553,  1570,  1385,   361,  1450,   211,    67,
    1364,  1430,  1257,   209,   875,   345,  1472,  1432,   214,  1555,
    1433,  1471,  1551,  1436,   380,   212,  1320,   386,   725,   211,
    1311,  1414,  1381,  1387,  1003,  1016,   873,  1406,   201,   205,
     716,  1293,  1456,  1382,  1388,   206,   985,   201,   205,   679,
    1403,   844,   202,  1402,   206,  1316,  1318,  1318,  1321,  1173,
     213,  1174,   213,   208,  1175,   845,  1189,  1043,   845,  1192,
    1177,   698,   208,  1048,   203,  1095,    70,   652,    71,   411,
    1157,   867,  1537,    72,    73,    74,   883,    75,   214,   212,
     214,   213,  1545,  1442,    17,    18,   885,  1485,  1385,  1489,
    1549,   424,   886,  1526,  1571,   209,   202,  1492,   845,  1494,
    1541,   850,   884,   702,   209,   707,   345,   935,     0,   349,
     710,   211,  1534,     0,     0,   711,     0,     0,  1531,     0,
     211,     0,  1513,  1514,  1515,  1516,  1517,     0,     0,   201,
     205,     0,    33,   212,     0,     0,   206,     0,     0,     0,
       0,    34,     0,     0,     0,   213,     0,    35,     0,     0,
       0,  1241,  1249,  1255,   208,     0,  1535,  1539,  1543,  1547,
     202,     0,  1242,  1250,  1256,    36,     0,  1536,  1540,  1544,
    1548,     0,     0,   349,     0,  1559,  1565,  1560,  1561,  1562,
    1563,  1381,  1387,  1566,   967,     0,     0,  1567,     0,   202,
       0,  1568,  1382,  1388,     0,  1569,   209,   212,     0,   213,
     983,   984,     0,   986,     0,   988,   989,  1572,     0,     0,
     202,     0,   211,  1573,  1574,     0,     0,     0,     0,     0,
       0,     0,     0,   426,     0,     0,   212,   349,     0,  1021,
       3,     0,  1023,     4,     0,     5,     0,     0,    17,    18,
       0,     0,     0,     0,     0,     3,    76,   212,     4,     0,
       5,     0,     0,     0,     0,     6,     7,     8,     9,     0,
      77,     0,     0,   213,     0,     0,     0,     0,     0,  1210,
       6,     7,     8,     9,  1211,    78,  1212,     0,  1213,     0,
      79,     0,    80,     0,  1041,     0,    33,  1042,     0,     0,
       0,   349,   213,     0,    49,    34,     0,     0,     0,     0,
       0,    35,   202,    58,    49,    49,    61,    61,    61,    65,
       0,   202,    49,   213,     0,   845,     0,     0,     0,    36,
     214,   428,   521,     0,   522,  1232,  1233,  1234,  1235,  1236,
       0,     0,  1237,     0,     0,     0,    17,    18,     0,   212,
       0,   214,   523,     0,   524,   525,     0,   526,   212,  1238,
    1071,  1072,     0,     0,     0,     0,     0,   527,   528,     0,
       0,    49,     0,   367,    49,    61,    61,    61,    65,     0,
       0,     0,     0,     0,     0,    49,  1214,   381,   383,    49,
     387,    61,    61,    65,    33,   396,   396,   396,   396,     0,
      61,  1239,   406,    34,    49,     0,     0,    61,    61,    35,
       0,     0,    61,   202,     0,   213,     0,     0,     0,     0,
       0,     0,     0,     0,   213,     0,     0,    36,     0,   574,
     443,    49,    61,    61,     0,     0,    61,     0,    49,     0,
     575,     0,   576,   349,   258,   259,   260,     0,     0,     0,
     212,     0,   214,     0,   577,     0,     0,  1215,   578,     0,
       0,   579,  1127,     0,     0,     0,  1130,     0,     0,     0,
       0,  1216,     0,     0,  1142,  1143,  1144,     0,   511,   512,
    1147,     0,   375,   376,   377,   378,  1217,     0,  1151,     0,
       0,  1218,   513,  1219,   514,   515,   516,   397,   399,   401,
     403,     0,     0,     0,     0,     0,     0,     0,   580,     0,
       0,   517,   518,   519,     0,     0,   213,     0,   425,     0,
    1167,     0,   432,   433,   434,     0,     0,   437,     0,     0,
     442,  1182,     0,  1183,     0,     0,  1188,     0,  1190,     0,
     581,   582,     0,     0,   349,     0,  1368,     3,     0,     0,
       4,     0,     5,     0,     3,     0,     0,     4,     0,     5,
       0,  1529,     0,   938,   939,     0,     0,     0,     0,     0,
       0,     0,     6,     7,     8,     9,   940,     0,     0,     6,
       7,     8,     9,     0,   941,     0,     3,     0,     0,     4,
     430,     5,     0,    10,   942,    11,     0,    12,     0,     0,
      13,    14,    15,     0,    16,    17,    18,     0,    17,    18,
       0,     6,     7,     8,     9,     0,     0,     0,     0,     0,
       0,   583,     0,     0,     0,     0,  1281,  1282,  1244,     0,
    1245,  1236,     0,     0,  1237,  1244,     0,  1245,  1236,   435,
       0,  1237,     0,     0,  1290,     0,     0,     0,  1294,     0,
       0,  1246,     0,    33,    17,    18,    33,     0,  1246,   676,
     677,     0,    34,     0,     0,    34,  1304,  1244,    35,  1245,
    1236,    35,     0,  1237,     0,     0,     0,     0,     0,   943,
     944,   945,   632,     0,     0,     0,    36,     0,     0,    36,
    1246,     0,     0,  1247,   642,   643,   644,     0,     0,     0,
    1247,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,   895,     0,     0,    35,     0,     0,
      61,     0,     0,     0,     0,     0,     0,     0,     0,   901,
       0,   902,  1247,   903,     0,    36,     0,     0,   904,     0,
       0,   905,     3,   906,     0,     4,     0,     5,     0,     0,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   708,     0,   137,     0,     0,     6,     7,     8,
       9,   138,   139,    37,   271,   140,     0,     0,   881,   882,
       0,  1399,     0,   625,   626,     0,   272,    38,     0,     0,
       0,     0,     0,  1404,     0,     0,   273,   274,     0,     0,
     892,     0,    39,  1407,   627,     0,     0,    40,     0,    41,
       0,     0,   275,   276,   277,   278,   279,   280,     0,     0,
       0,     0,     0,     0,     0,     0,  1224,     0,     0,   900,
     281,     0,   282,     0,     0,   141,   142,   143,   144,     0,
       0,     0,     0,   145,     0,     0,  1225,   146,     0,     0,
       0,   147,   709,  1248,     0,     0,     0,   148,     0,     0,
    1371,     0,     0,     0,     0,     0,     0,   149,     0,     0,
       0,     0,   150,     0,     0,   151,   628,     0,     0,     0,
     152,     0,     0,   153,     0,     0,   154,   155,     0,     0,
     156,     0,  1530,   157,     0,   158,     0,     0,     0,   629,
     630,   631,   632,   633,   634,   635,   636,   637,   638,   639,
     640,   641,     0,     0,   642,   643,   644,     0,   159,   160,
       0,   161,   162,   163,   164,     0,     0,     0,     0,     0,
     165,   166,     0,     0,   167,   168,   283,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,     0,   284,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       0,     0,     4,   285,     5,     0,     0,     0,     0,     0,
       0,     0,   286,     0,     0,     0,     0,     0,   287,     0,
       0,   137,     0,   288,     6,     7,     8,     9,   138,   139,
       0,   271,   140,     0,     0,   289,     0,     0,   290,   291,
     292,   293,     0,   272,     0,   294,     0,     0,   806,   295,
     296,   191,     0,   273,   274,   192,   193,     0,     0,     0,
       0,     0,     0,     0,   297,     0,     0,   194,   195,   275,
     276,   277,   278,   279,   280,     0,     0,   298,  1226,     0,
     196,   197,     0,  1224,     0,     0,   438,   281,   743,   282,
     440,     0,   141,   142,   143,   144,     0,     0,     0,     0,
     145,    17,    18,  1225,   146,    17,    18,     0,   147,     0,
       0,     0,     0,     0,   148,     0,     0,     0,     0,     0,
     142,   143,   144,     0,   149,     0,     0,   825,     0,   150,
       0,   826,   151,     0,     0,   827,     0,   152,     0,     0,
     153,   828,     0,   154,   155,   749,     0,   156,     0,    33,
     157,     0,   158,    33,     0,     0,     0,     0,    34,   831,
       0,     0,    34,     0,    35,     0,     0,     0,    35,     0,
       0,     0,     0,     0,     0,   159,   160,     0,   161,   162,
     163,   164,    36,     0,     0,     0,    36,   165,   166,     0,
       0,   167,   168,   283,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   922,     0,   284,   923,   924,   925,
     926,   927,   928,   929,   930,   931,   932,   933,     0,     0,
     285,  1092,  1093,     0,     0,     0,     0,     0,     0,   286,
       0,     0,     0,     0,     0,   287,     0,     0,     0,     0,
     288,     0,   752,     0,     0,   753,   754,     0,     0,     0,
       0,     0,   289,     0,     0,   290,   291,   292,   293,     0,
       0,     0,   294,     0,     0,     0,   295,   296,   191,     0,
       0,     0,   192,   193,     3,     0,     0,     4,     0,     5,
       0,   297,   755,   756,   194,   195,     0,     0,     0,     0,
       0,     0,     0,     0,   298,  1369,   137,   196,   197,     6,
       7,     8,     9,   138,   139,   553,   271,   140,   554,     0,
       0,     0,   625,   626,     0,     0,     0,     0,   272,     0,
       0,     0,     0,   555,   196,     0,     0,   556,   273,   274,
     557,   558,     0,   627,     0,   559,   560,   561,   562,   563,
       0,     0,     0,     0,   275,   276,   277,   278,   279,   280,
       0,     0,     0,     0,     0,     0,     0,     0,  1224,     0,
       0,     0,   281,     0,   282,     0,     0,   141,   142,   143,
     144,     0,     0,     0,     0,   145,     0,     0,  1225,   146,
       0,     0,     0,   147,     0,     0,     0,     0,     0,   148,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   149,
       0,     0,     0,     0,   150,   628,     0,   151,     0,     0,
       0,     0,   152,     0,     0,   153,     0,     0,   154,   155,
       0,     0,   156,     0,     0,   157,     0,   158,   629,   630,
     631,   632,   633,   634,   635,   636,   637,   638,   639,   640,
     641,     0,     0,   642,   643,   644,     0,     0,     0,     0,
     159,   160,     0,   161,   162,   163,   164,     0,     0,     0,
       0,     0,   165,   166,     0,     0,   167,   168,   283,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
       0,   284,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   741,     0,     0,     0,   285,     0,     0,     0,     0,
       0,     0,     0,     0,   286,     0,     0,   742,     0,   137,
     287,     0,     0,     0,     0,   288,     0,   139,     0,     0,
     140,     0,     0,     0,     0,     0,     0,   289,     0,     0,
     290,   291,   292,   293,     0,     0,     0,   294,     0,     0,
       0,   295,   296,   191,     0,     0,     0,   192,   193,   743,
       0,     0,     0,     0,     0,     0,   297,     0,     0,   194,
     195,     0,     0,   744,     0,     0,     0,     0,     0,   298,
    1528,     0,   196,   197,     0,     0,     0,     0,     0,     0,
     141,   142,   143,   144,     0,     0,     0,     0,   745,     0,
       0,     0,   746,     0,     0,     0,   747,     0,     0,     0,
       0,     0,   748,     0,     0,     0,   749,     0,     0,     0,
       0,     0,   149,     0,     0,     0,     0,   150,   964,     0,
     750,     0,     0,     0,     0,   152,     0,  -738,   153,     0,
       0,   154,   155,     0,   742,   156,   137,     0,   157,     0,
     158,     0,     0,     0,   139,     0,     0,   140,     0,     0,
       0,     0,     0,   485,   486,     0,     0,   487,     0,     0,
       0,     0,     0,   159,   160,     0,   751,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   743,     0,     0,     0,
       0,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,     0,     0,   190,     0,     0,   141,   142,   143,
     144,     0,     0,   752,     0,   745,   753,   754,     0,   746,
       0,     0,     0,   747,     0,     0,     0,     0,     0,   965,
       0,     0,     0,   749,     0,     0,     0,     0,     0,   149,
       0,     0,     0,     0,   150,     0,     0,   966,     0,     0,
       0,     0,   152,   755,   756,   153,     0,     0,   154,   155,
       0,     0,   156,     0,     0,   157,   191,   158,     0,     0,
     192,   193,     0,     0,     0,     0,     0,     0,     0,     0,
     757,   758,     0,   621,   485,   486,     0,     0,   487,     0,
     159,   160,     0,   751,     0,   196,     0,     0,   488,   489,
     490,   491,   492,   493,   494,   495,   496,     0,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,  1022,
       0,   190,     0,     0,     0,     0,     0,     0,     0,     0,
     752,     0,     0,   753,   754,   742,     0,   137,     0,     0,
       0,     0,     0,     0,     0,   139,     0,     0,   140,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     755,   756,     0,     0,     0,     0,     0,   743,     0,     0,
       0,     0,     0,   191,     0,     0,     0,   192,   193,     0,
       0,     0,     0,     0,     0,     0,     0,   757,   758,     0,
     621,     0,     0,     0,     0,     0,     0,     0,   141,   142,
     143,   144,   196,     0,     0,     0,   745,     0,     0,     0,
     746,     0,     0,     0,   747,     0,     0,     0,     0,     0,
     965,     0,     0,     0,   749,     0,     0,     0,     0,     0,
     149,     0,     0,     0,     0,   150,  1040,     0,   966,     0,
       0,     0,     0,   152,     0,     0,   153,     0,     0,   154,
     155,     0,   742,   156,   137,     0,   157,     0,   158,     0,
       0,     0,   139,     0,     0,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,   160,     0,   751,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   743,     0,     0,     0,     0,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
       0,     0,   190,     0,     0,   141,   142,   143,   144,     0,
       0,   752,     0,   745,   753,   754,     0,   746,     0,     0,
       0,   747,     0,     0,     0,     0,     0,   965,     0,     0,
       0,   749,     0,     0,     0,     0,     0,   149,     0,     0,
       0,     0,   150,     0,     0,   966,     0,     0,     0,     0,
     152,   755,   756,   153,     0,     0,   154,   155,     0,     0,
     156,     0,     0,   157,   191,   158,     0,     0,   192,   193,
       0,     0,     0,     0,     0,     0,     0,     0,   757,   758,
       0,   621,     0,     0,     0,     0,     0,     0,   159,   160,
       0,   751,     0,   196,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,  1129,     0,   190,
       0,     0,     0,     0,     0,     0,     0,     0,   752,     0,
       0,   753,   754,   742,     0,   137,     0,     0,     0,     0,
       0,     0,     0,   139,     0,     0,   140,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   755,   756,
       0,     0,     0,     0,     0,   743,     0,     0,     0,     0,
       0,   191,     0,     0,     0,   192,   193,     0,     0,     0,
       0,     0,     0,     0,     0,   757,   758,     0,   621,     0,
       0,     0,     0,     0,     0,     0,   141,   142,   143,   144,
     196,     0,     0,     0,   745,     0,     0,     0,   746,     0,
       0,     0,   747,     0,     0,     0,     0,     0,   965,     0,
       0,     0,   749,     0,     0,     0,     0,     0,   149,     0,
       0,     0,     0,   150,     0,     0,   966,     0,     0,     0,
       0,   152,     0,     0,   153,     0,     0,   154,   155,     0,
       0,   156,     0,     0,   157,     0,   158,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   159,
     160,     0,   751,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,     0,     0,
     190,     0,   819,   820,   821,   822,   823,   824,     0,   752,
       0,     0,   753,   754,   742,     0,   806,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   742,     0,   806,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   755,
     756,     0,     0,     0,     0,     0,   743,     0,     0,     0,
       0,     0,   191,     0,     0,     0,   192,   193,     0,     0,
       0,     0,     0,   743,     0,     0,   757,   758,     0,   621,
       0,     0,     0,     0,     0,     0,     0,   141,   142,   143,
     144,   196,     0,     0,     0,   825,     0,     0,     0,   826,
       0,     0,     0,   827,   141,   142,   143,   144,     0,   828,
       0,     0,   825,   749,     0,     0,   826,     0,     0,   829,
     827,     0,     0,     0,   830,     0,   828,   831,     0,     0,
     749,     0,   832,     0,     0,   833,   829,     0,   834,   835,
       0,   830,   836,     0,   831,   837,     0,   838,     0,   832,
       0,     0,   833,     0,     0,   834,   835,     0,     0,   836,
       0,     0,   837,     0,   838,     0,     0,     0,     0,     0,
     839,   840,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   839,   840,     0,
       0,     0,    99,   100,   101,   102,     0,     0,   103,   104,
       0,   105,   106,     0,     0,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     752,     0,     0,   753,   754,     0,     0,     0,     0,     0,
       0,     0,     0,   742,     0,   806,     0,   752,     0,     0,
     753,   754,     0,   108,     0,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     755,   756,     0,   841,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   743,     0,   755,   756,     0,
     841,     0,     0,     0,     0,     0,     0,   757,   758,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   298,
       0,     0,   196,   842,   757,   758,   141,   142,   143,   144,
     615,     0,     0,     0,   825,     0,   298,     0,   826,   196,
     842,     0,   827,     0,     0,     0,     0,     0,   828,     0,
       0,     0,   749,     0,     0,     0,   616,     0,   829,   617,
       0,     0,     0,   830,     0,     0,   831,     0,     0,     0,
     618,   832,     0,     0,   833,     0,     0,   834,   835,     0,
     742,   836,   137,     0,   837,     0,   838,     0,     0,     0,
     139,     0,   112,   140,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,     0,     0,   839,
     840,   114,   115,   116,     0,     0,     0,     0,     0,     0,
       0,   117,   743,     0,     0,     0,   118,     0,   119,   120,
       0,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,     0,     0,   141,   142,   143,   144,     0,     0,   752,
       0,   745,   753,   754,     0,   746,     0,     0,     0,   747,
       0,     0,     0,     0,     0,   965,     0,     0,     0,   749,
       0,     0,     0,     0,     0,   149,     0,     0,     0,   619,
     150,     0,     0,   966,     0,     0,     0,     0,   152,   755,
     756,   153,   841,     0,   154,   155,   620,     0,   156,     0,
       0,   157,     0,   158,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   757,   758,     0,     0,
       0,     0,   621,     0,     0,     0,   159,   160,     0,   751,
       0,   196,   842,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,     0,     0,   190,     0,     0,
       0,     0,     0,     0,     0,     0,   752,     0,     0,   753,
     754,     0,     0,     0,     0,     0,     0,     0,   137,     0,
       0,     0,     0,     0,     0,   138,   139,     0,   271,   140,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     272,     0,     0,     0,     0,     0,   755,   756,     0,     0,
     273,   274,     0,     0,     0,     0,     0,     0,     0,   191,
       0,     0,     0,   192,   193,     0,   275,   276,   277,   278,
     279,   280,     0,   757,   758,     0,   621,     0,     0,     0,
       0,     0,     0,     0,   281,     0,   282,     0,   196,   141,
     142,   143,   144,     0,     0,     0,     0,   145,     0,     0,
       0,   146,     0,     0,     0,   147,     0,     0,     0,     0,
       0,   148,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,     0,     0,     0,     0,   150,     0,     0,   151,
       0,     0,     0,     0,   152,     0,     0,   153,     0,     0,
     154,   155,     0,     0,   156,     0,     0,   157,     0,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,   160,     0,   161,   162,   163,   164,     0,
       0,     0,     0,     0,   165,   166,     0,     0,   167,   168,
     283,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,     0,     0,   284,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   137,     0,     0,     0,   285,     0,     0,
     138,   139,     0,     0,   140,     0,   286,     0,     0,     0,
       0,     0,   287,     0,     0,     0,     0,   288,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   289,
       0,     0,   290,   291,   292,   293,     0,     0,     0,   294,
       0,     0,     0,   295,   296,   191,     0,     0,     0,   192,
     193,     0,     0,     0,     0,     0,     0,     0,   297,     0,
       0,   194,   195,     0,   141,   142,   143,   144,     0,     0,
       0,   298,   145,     0,   196,   197,   146,     0,     0,     0,
     147,     0,     0,     0,     0,     0,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   149,     0,     0,     0,
       0,   150,     0,     0,   151,     0,     0,     0,     0,   152,
       0,     0,   153,     0,     0,   154,   155,     0,     0,   156,
       0,     0,   157,     0,   158,     0,     0,     0,     0,     0,
     137,     0,     0,     0,     0,     0,     0,   138,   139,     0,
       0,   140,     0,     0,     0,     0,     0,   159,   160,     0,
     161,   162,   163,   164,     0,     0,     0,     0,     0,   165,
     166,     0,     0,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,     0,     0,   190,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   141,   142,   143,   144,     0,     0,     0,     0,   145,
       0,     0,     0,   146,     0,     0,     0,   147,     0,     0,
       0,     0,     0,   148,     0,     0,     0,     0,     0,     0,
       0,   706,     0,   149,     0,     0,     0,     0,   150,     0,
       0,   151,     0,     0,     0,     0,   152,     0,     0,   153,
     191,     0,   154,   155,   192,   193,   156,   616,     0,   157,
     617,   158,     0,     0,     0,     0,   194,   195,     0,     0,
       0,   618,     0,     0,     0,     0,   298,     0,     0,   196,
     197,     0,     0,     0,   159,   160,     0,   161,   162,   163,
     164,     0,     0,     0,     0,     0,   165,   166,     0,     0,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,     0,   190,   806,     0,     0,     0,
       0,     0,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   743,     0,     0,     0,
       0,     0,     0,     0,   275,   276,   277,   278,   279,   280,
       0,     0,     0,     0,     0,     0,     0,   191,     0,     0,
     619,   192,   193,     0,     0,   806,     0,   141,   142,   143,
     144,     0,     0,   194,   195,   825,     0,   620,     0,   826,
       0,     0,     0,   827,     0,     0,   196,   197,     0,   828,
       0,     0,     0,   749,     0,     0,     0,     0,     0,   829,
       0,     0,     0,   621,   830,   743,     0,   831,     0,     0,
       0,     0,   832,     0,     0,   833,     0,     0,   834,   835,
       0,     0,   836,     0,     0,   837,     0,   838,     0,     0,
       0,     0,     0,     0,     0,     0,   141,   142,   143,   144,
       0,     0,     0,     0,   825,     0,     0,     0,   826,     0,
     839,   840,   827,     0,     0,     0,     0,     0,   828,     0,
       0,     0,   749,     0,     0,     0,     0,     0,   829,     0,
       0,     0,     0,   830,     0,     0,   831,     0,     0,     0,
       0,   832,     0,     0,   833,     0,     0,   834,   835,     0,
       0,   836,     0,     0,   837,     0,   838,     0,     0,     0,
     752,     0,     0,   753,   754,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   839,
     840,     0,     0,     0,   137,     0,     0,     0,     0,     0,
       0,     0,   139,     0,     0,   140,     0,     0,     0,     0,
     755,   756,     0,   841,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   743,     0,     0,   757,   758,   752,
       0,     0,   753,   754,     0,     0,     0,     0,     0,     0,
       0,     0,   196,   842,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   141,   142,   143,   144,     0,
       0,     0,     0,   745,     0,     0,     0,   746,     0,   755,
     756,   747,   841,     0,     0,     0,     0,   965,     0,     0,
       0,   749,     0,     0,     0,     0,     0,   149,     0,     0,
       0,     0,   150,     0,     0,   966,   757,   758,     0,     0,
     152,     0,     0,   153,     0,     0,   154,   155,     0,     0,
     156,   196,   842,   157,     0,   158,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,   160,
       0,   751,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,     0,   190,
       0,     0,     0,     0,     0,     0,     0,     0,   752,     0,
       0,   753,   754,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   755,   756,
       0,     0,     0,     2,     3,     0,     0,     4,     0,     5,
       0,   191,     0,     0,     0,   192,   193,     0,     0,     0,
       0,     0,     0,     0,     0,   757,   758,     0,   621,     6,
       7,     8,     9,     0,     0,     0,     0,     0,     0,     0,
     196,    10,     0,    11,     0,    12,     0,     0,    13,    14,
      15,     0,    16,     0,     0,     0,    17,    18,    19,     0,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -274,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,    34,     0,     0,     0,     0,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      39,     0,     0,     0,     0,    40,     0,    41
};

static const yytype_int16 yycheck[] =
{
       1,    63,     3,   301,   192,   370,    51,    29,    29,   369,
     341,     1,   260,   372,    29,    60,   368,   371,   321,   721,
     351,   352,   721,   341,   197,   390,   271,   987,    31,    51,
      51,  1078,    29,   351,   352,   341,    51,  1081,    60,    60,
     405,  1082,  1084,  1083,    45,    60,  1045,    63,     5,   992,
     993,   296,    53,  1047,    51,   998,    57,    51,    38,     7,
       7,     7,   100,    60,   102,   103,    60,     7,   106,   107,
      22,   316,   110,   111,    29,    51,   114,   115,   116,  1153,
    1263,   813,   120,   814,  1262,   123,   124,    23,    88,    77,
      29,    23,     1,   131,  1196,     4,    51,     6,  1246,    95,
    1111,  1112,    32,    82,    82,    60,   815,    94,   994,    95,
    1134,   117,    51,  1056,    14,    15,    82,    26,    27,    28,
      29,    60,   105,   105,   169,   811,   812,    20,   341,    82,
     378,  1155,   102,   103,     4,    95,   106,   107,   351,   352,
     110,   111,    94,    95,   114,   115,   116,     8,  1024,   645,
     120,    82,    51,   123,   124,  1031,    12,   130,    50,   118,
      20,   131,    50,    95,    96,    97,     7,   150,   151,     8,
     192,   192,    72,    73,    74,   197,   197,   192,   137,    20,
     341,    22,   197,    50,    96,    94,    47,    87,    88,    89,
     351,   352,     7,     8,     9,   192,     1,    97,   677,     4,
     197,     6,    95,    82,   104,   105,    95,    95,    47,   109,
    1328,  1329,  1330,  1260,   710,    77,   278,   279,   200,   201,
      77,    26,    27,    28,    29,    95,    82,   233,    95,   129,
     130,     8,    47,   133,    49,    95,    42,   192,   283,   242,
      42,   105,   197,   216,   217,   248,    61,    24,   226,   235,
      65,    77,   128,   192,   116,  1141,   301,   133,   197,   116,
     226,   125,   240,   250,     1,  1289,   196,     4,   132,     6,
      47,     1,   134,   226,     4,   235,     6,   134,   128,   301,
     301,    29,    55,   271,   272,   273,   301,  1435,   118,    26,
      27,    28,    29,  1287,   144,   226,    26,    27,    28,    29,
     105,  1419,  1420,    51,   301,   327,   306,   137,   370,  1308,
     289,  1413,    60,   309,   290,   291,   292,    90,    29,   341,
      40,   366,   137,  1506,   297,   341,   306,  1505,   390,   351,
     352,  1063,   149,  1064,   379,   351,   352,   154,  1412,  1025,
      51,   250,   251,   405,   366,   366,   301,   226,    85,    60,
     307,   366,   304,  1296,   370,    85,  1065,   379,   379,   307,
     307,   307,   301,    23,   379,  1376,     4,   307,     6,   366,
     306,  1314,   366,   126,   390,  1061,  1062,   309,    50,   243,
     418,   196,   379,    50,    29,   379,   139,   124,    46,   405,
     721,   290,   291,   292,   124,   287,   288,    20,   307,    22,
       5,   154,   881,   882,     1,   102,    51,     4,   233,     6,
    1409,   366,    29,   892,   219,    60,  1460,    38,    39,   116,
    1461,  1463,  1462,    95,   379,   250,   251,   366,    95,    26,
      27,    28,    29,   147,    51,    95,    96,    97,  1398,   102,
     379,   256,   271,    60,   192,   271,   272,   273,   418,   197,
     305,  1153,   281,   116,  1156,    95,  1503,  1156,    95,  1217,
    1218,  1219,   305,   278,   279,     1,   306,   282,     4,   772,
       6,   306,   186,   187,   188,   306,   724,   116,   309,   119,
     120,   192,   219,    20,   732,    22,   197,   818,   736,   219,
      26,    27,    28,    29,  1196,   134,    75,  1196,    95,    96,
      97,     1,   307,    38,     4,   144,     6,   233,   721,   185,
     698,    90,   818,   266,   123,     1,  1459,   417,     4,   125,
       6,   185,   248,   137,   842,   282,    26,    27,    28,    29,
     861,   291,   116,   147,   148,    35,   234,    37,  1233,  1234,
      26,    27,    28,    29,   150,   151,   130,   192,   448,  1244,
     134,   105,   197,   301,    40,   861,   196,   303,   304,    45,
     721,    47,   248,    49,   118,   380,  1324,  1325,   383,   125,
     307,   125,   387,   179,    70,   192,   216,   307,  1521,    94,
     197,   396,     1,   137,     4,     4,     6,     6,     8,   143,
     301,   250,   251,   341,   150,   151,    94,   153,   811,   812,
     813,   814,   815,   351,   352,   818,   102,    26,    27,    28,
      29,     1,    94,   218,     4,   121,     6,   233,   366,   125,
     116,   147,   234,   235,     0,    53,    54,   232,     4,   842,
       6,   379,   216,   217,    77,   450,    26,    27,    28,    29,
      55,    56,   247,   816,   150,   151,   306,   252,   861,   309,
     811,   812,   813,   814,   815,   366,   301,   818,   154,     4,
     299,   147,    81,    82,    83,    84,    85,   289,   379,    88,
     103,   104,   675,   101,   265,   283,   698,   698,   286,    38,
      11,   842,   110,   698,   301,    17,   105,     5,   116,    88,
       8,    81,    82,    83,    84,    85,    15,    16,    88,   721,
     861,   698,   307,   250,   251,   721,   134,   203,   953,    18,
     307,  1413,   248,   297,  1413,   105,   242,   243,   244,   245,
     246,   366,   121,   308,   972,   973,    95,    50,   147,    98,
      99,   100,   218,     4,   379,     6,     7,    68,  1041,    45,
      71,    22,  1060,   698,    25,    45,   232,   306,  1066,   366,
    1068,  1069,    38,     1,    85,    86,     4,   147,     6,   698,
     306,   247,   379,   196,   197,   306,   252,   200,   254,    38,
     101,   307,   171,   172,   173,   174,   175,   176,    26,    27,
      28,    29,   259,   260,   261,   262,   263,   975,   306,   811,
     812,   813,   814,   815,   816,   816,   818,   128,   103,   104,
     105,   816,   818,   306,   135,    95,   105,   307,   107,   108,
     109,  1024,  1025,  1026,  1027,  1028,     7,  1030,  1031,   816,
     842,   307,     8,  1036,  1037,  1156,   290,   291,   292,   119,
     120,    38,    95,    40,   312,  1153,   312,    85,    45,   861,
      47,   282,  1140,   107,    51,   861,   282,  1060,  1061,  1062,
    1063,  1064,  1065,  1066,    94,  1068,  1069,  1045,   122,  1047,
     300,   816,   311,   864,  1025,  1196,   867,    78,    79,    80,
     105,    82,   107,   137,    15,    16,   124,   816,    94,   143,
      15,    16,    89,    23,    91,  1188,     1,  1190,   307,     4,
     125,     6,   127,   128,   129,   130,  1194,   103,   104,  1060,
    1061,  1062,  1063,  1064,  1065,  1066,   196,  1068,  1069,   103,
     104,    26,    27,    28,    29,     4,     5,   307,   276,   277,
      35,    94,    37,    95,    96,    97,   216,   191,   192,    77,
      38,    23,    40,    45,    42,   180,    45,    45,    46,    47,
    1153,    49,   232,  1156,   189,   190,    45,   969,   193,   194,
     698,   103,   104,   975,   975,    71,    72,   247,    45,  1319,
     975,    94,   252,  1322,   254,  1317,  1320,   275,   276,   277,
      77,   219,    94,   721,    94,   118,  1341,    39,   975,    41,
      94,    43,    44,  1196,    94,   128,    17,   698,    94,    51,
      52,   806,  1153,   808,   137,  1156,    18,  1362,    86,    87,
     143,   144,  1024,  1025,  1026,  1027,  1028,   232,  1030,  1031,
    1032,   308,   237,   238,  1036,  1037,  1032,   271,   272,   273,
     975,     5,    84,  1045,  1045,  1047,  1047,   252,  1036,  1037,
    1045,  1076,  1047,     7,     7,  1196,   975,    77,  1060,  1061,
    1062,  1063,  1064,  1065,  1066,     7,  1068,  1069,  1045,     7,
    1047,     5,     7,   698,  1076,  1076,    93,    94,    95,   307,
       7,  1076,   306,   811,   812,   813,   814,   815,   816,     7,
     818,    17,   308,    18,  1075,     8,  1077,  1078,  1079,  1076,
     306,   698,  1413,   306,   306,  1075,   306,  1077,  1078,  1079,
    1045,   306,  1047,    94,   842,  1140,    94,    94,    94,  1287,
      94,    94,  1400,    94,    94,   816,  1045,    94,  1047,   283,
     218,    94,   235,   861,   306,    94,   306,     5,  1140,  1140,
    1308,  1076,     8,    94,   232,  1140,    94,     1,    45,    94,
       4,  1153,     6,    36,  1156,   105,   105,  1076,   133,   247,
    1156,    63,   105,  1140,   252,     5,   254,   311,   306,  1194,
      94,    77,    26,    27,    28,    29,     1,    94,     7,     4,
     306,     6,     1,   313,   313,     4,    94,     6,   253,    94,
       5,   816,  1194,  1194,  1196,    95,   306,   103,   104,  1194,
      36,    26,    27,    28,    29,  1140,     7,    26,    27,    28,
      29,   117,   307,   119,   120,   121,    35,  1194,    37,   816,
    1413,  1140,    95,    95,    95,     5,   103,   104,    95,   305,
     136,   137,   138,  1258,   111,   112,   113,   114,   115,    95,
       1,  1409,  1223,     4,    94,     6,   305,   975,  1229,  1230,
    1231,   105,    95,   305,   249,    94,  1258,  1258,   307,  1194,
    1055,    94,  1243,  1258,    94,    26,    27,    28,    29,   172,
    1251,   307,  1413,     5,   135,  1194,  1257,    35,  1259,  1260,
    1261,  1258,  1510,  1511,   975,  1287,  1287,  1257,   306,  1259,
    1260,  1261,  1287,  1274,  1275,   305,    96,  1025,    94,  1341,
     307,   306,   249,   306,  1274,  1275,  1308,  1308,   306,   306,
    1287,    95,   306,  1308,   306,   306,   306,  1045,    95,  1047,
    1362,   306,     6,  1258,    71,    72,    73,    74,    75,    76,
     124,  1308,  1060,  1061,  1062,  1063,  1064,  1065,  1066,  1258,
    1068,  1069,    94,    36,   105,  1341,   307,   307,  1076,   306,
     975,   306,  1287,    94,  1045,    95,  1047,    94,  1339,  1340,
     234,  1379,     5,    94,    94,   219,  1362,  1385,  1287,    19,
    1247,  1352,  1080,  1308,   367,  1400,  1431,  1358,   975,  1521,
    1361,  1429,  1512,  1364,    84,  1076,  1212,    86,   300,  1308,
    1193,  1314,  1373,  1374,   729,   737,   365,  1300,  1400,  1400,
     288,  1149,  1402,  1373,  1374,  1400,   714,  1409,  1409,   234,
    1292,  1413,  1140,  1291,  1409,  1210,  1211,  1212,  1213,  1026,
    1045,  1027,  1047,  1400,  1028,  1153,  1039,   802,  1156,  1044,
    1030,   272,  1409,   809,    29,   910,    38,   192,    40,    38,
     998,   352,  1507,    45,    46,    47,   375,    49,  1045,  1140,
    1047,  1076,  1509,   307,    53,    54,   377,  1438,   219,  1440,
    1510,   112,   378,  1493,  1557,  1400,  1194,  1448,  1196,  1450,
    1508,   341,   376,   279,  1409,   283,  1501,   584,    -1,  1076,
     284,  1400,   307,    -1,    -1,   284,    -1,    -1,   307,    -1,
    1409,    -1,  1473,  1474,  1475,  1476,  1477,    -1,    -1,  1501,
    1501,    -1,   101,  1194,    -1,    -1,  1501,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    -1,  1140,    -1,   116,    -1,    -1,
      -1,  1502,  1503,  1504,  1501,    -1,  1507,  1508,  1509,  1510,
    1258,    -1,  1502,  1503,  1504,   134,    -1,  1507,  1508,  1509,
    1510,    -1,    -1,  1140,    -1,  1526,   307,  1528,  1529,  1530,
    1531,  1532,  1533,  1534,   696,    -1,    -1,  1538,    -1,  1287,
      -1,  1542,  1532,  1533,    -1,  1546,  1501,  1258,    -1,  1194,
     712,   713,    -1,   715,    -1,   717,   718,  1558,    -1,    -1,
    1308,    -1,  1501,  1564,  1565,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,  1287,  1194,    -1,   741,
       1,    -1,   744,     4,    -1,     6,    -1,    -1,    53,    54,
      -1,    -1,    -1,    -1,    -1,     1,   218,  1308,     4,    -1,
       6,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    -1,
     232,    -1,    -1,  1258,    -1,    -1,    -1,    -1,    -1,    40,
      26,    27,    28,    29,    45,   247,    47,    -1,    49,    -1,
     252,    -1,   254,    -1,   796,    -1,   101,   799,    -1,    -1,
      -1,  1258,  1287,    -1,     1,   110,    -1,    -1,    -1,    -1,
      -1,   116,  1400,    10,    11,    12,    13,    14,    15,    16,
      -1,  1409,    19,  1308,    -1,  1413,    -1,    -1,    -1,   134,
    1287,    38,   105,    -1,   107,    81,    82,    83,    84,    85,
      -1,    -1,    88,    -1,    -1,    -1,    53,    54,    -1,  1400,
      -1,  1308,   125,    -1,   127,   128,    -1,   130,  1409,   105,
     862,   863,    -1,    -1,    -1,    -1,    -1,   140,   141,    -1,
      -1,    68,    -1,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    82,   147,    84,    85,    86,
      87,    88,    89,    90,   101,    92,    93,    94,    95,    -1,
      97,   147,    99,   110,   101,    -1,    -1,   104,   105,   116,
      -1,    -1,   109,  1501,    -1,  1400,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1409,    -1,    -1,   134,    -1,   105,
     127,   128,   129,   130,    -1,    -1,   133,    -1,   135,    -1,
     116,    -1,   118,  1400,    39,    40,    41,    -1,    -1,    -1,
    1501,    -1,  1409,    -1,   130,    -1,    -1,   218,   134,    -1,
      -1,   137,   964,    -1,    -1,    -1,   968,    -1,    -1,    -1,
      -1,   232,    -1,    -1,   976,   977,   978,    -1,   103,   104,
     982,    -1,    77,    78,    79,    80,   247,    -1,   990,    -1,
      -1,   252,   117,   254,   119,   120,   121,    92,    93,    94,
      95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,
      -1,   136,   137,   138,    -1,    -1,  1501,    -1,   113,    -1,
    1022,    -1,   117,   118,   119,    -1,    -1,   122,    -1,    -1,
     125,  1033,    -1,  1035,    -1,    -1,  1038,    -1,  1040,    -1,
     216,   217,    -1,    -1,  1501,    -1,   307,     1,    -1,    -1,
       4,    -1,     6,    -1,     1,    -1,    -1,     4,    -1,     6,
      -1,   307,    -1,   103,   104,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,   116,    -1,    -1,    26,
      27,    28,    29,    -1,   124,    -1,     1,    -1,    -1,     4,
      38,     6,    -1,    38,   134,    40,    -1,    42,    -1,    -1,
      45,    46,    47,    -1,    49,    53,    54,    -1,    53,    54,
      -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,   297,    -1,    -1,    -1,    -1,  1128,  1129,    82,    -1,
      84,    85,    -1,    -1,    88,    82,    -1,    84,    85,    38,
      -1,    88,    -1,    -1,  1146,    -1,    -1,    -1,  1150,    -1,
      -1,   105,    -1,   101,    53,    54,   101,    -1,   105,   254,
     255,    -1,   110,    -1,    -1,   110,  1168,    82,   116,    84,
      85,   116,    -1,    88,    -1,    -1,    -1,    -1,    -1,   219,
     220,   221,   222,    -1,    -1,    -1,   134,    -1,    -1,   134,
     105,    -1,    -1,   147,   234,   235,   236,    -1,    -1,    -1,
     147,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   110,    -1,    -1,   411,    -1,    -1,   116,    -1,    -1,
     417,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   426,
      -1,   428,   147,   430,    -1,   134,    -1,    -1,   435,    -1,
      -1,   438,     1,   440,    -1,     4,    -1,     6,    -1,    -1,
      -1,   448,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    23,    -1,    -1,    26,    27,    28,
      29,    30,    31,   218,    33,    34,    -1,    -1,   373,   374,
      -1,  1283,    -1,   103,   104,    -1,    45,   232,    -1,    -1,
      -1,    -1,    -1,  1295,    -1,    -1,    55,    56,    -1,    -1,
     395,    -1,   247,  1305,   124,    -1,    -1,   252,    -1,   254,
      -1,    -1,    71,    72,    73,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,   424,
      89,    -1,    91,    -1,    -1,    94,    95,    96,    97,    -1,
      -1,    -1,    -1,   102,    -1,    -1,   105,   106,    -1,    -1,
      -1,   110,   172,   307,    -1,    -1,    -1,   116,    -1,    -1,
     307,    -1,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,
      -1,    -1,   131,    -1,    -1,   134,   196,    -1,    -1,    -1,
     139,    -1,    -1,   142,    -1,    -1,   145,   146,    -1,    -1,
     149,    -1,   307,   152,    -1,   154,    -1,    -1,    -1,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,    -1,    -1,   234,   235,   236,    -1,   177,   178,
      -1,   180,   181,   182,   183,    -1,    -1,    -1,    -1,    -1,
     189,   190,    -1,    -1,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,    -1,    -1,   218,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,     4,   232,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   241,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,    23,    -1,   252,    26,    27,    28,    29,    30,    31,
      -1,    33,    34,    -1,    -1,   264,    -1,    -1,   267,   268,
     269,   270,    -1,    45,    -1,   274,    -1,    -1,    23,   278,
     279,   280,    -1,    55,    56,   284,   285,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   293,    -1,    -1,   296,   297,    71,
      72,    73,    74,    75,    76,    -1,    -1,   306,   307,    -1,
     309,   310,    -1,    85,    -1,    -1,    38,    89,    63,    91,
      38,    -1,    94,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,    53,    54,   105,   106,    53,    54,    -1,   110,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,
      95,    96,    97,    -1,   126,    -1,    -1,   102,    -1,   131,
      -1,   106,   134,    -1,    -1,   110,    -1,   139,    -1,    -1,
     142,   116,    -1,   145,   146,   120,    -1,   149,    -1,   101,
     152,    -1,   154,   101,    -1,    -1,    -1,    -1,   110,   134,
      -1,    -1,   110,    -1,   116,    -1,    -1,    -1,   116,    -1,
      -1,    -1,    -1,    -1,    -1,   177,   178,    -1,   180,   181,
     182,   183,   134,    -1,    -1,    -1,   134,   189,   190,    -1,
      -1,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   157,    -1,   218,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,    -1,    -1,
     232,   898,   899,    -1,    -1,    -1,    -1,    -1,    -1,   241,
      -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,
     252,    -1,   227,    -1,    -1,   230,   231,    -1,    -1,    -1,
      -1,    -1,   264,    -1,    -1,   267,   268,   269,   270,    -1,
      -1,    -1,   274,    -1,    -1,    -1,   278,   279,   280,    -1,
      -1,    -1,   284,   285,     1,    -1,    -1,     4,    -1,     6,
      -1,   293,   267,   268,   296,   297,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   306,   307,    23,   309,   310,    26,
      27,    28,    29,    30,    31,   125,    33,    34,   128,    -1,
      -1,    -1,   103,   104,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,   143,   309,    -1,    -1,   147,    55,    56,
     150,   151,    -1,   124,    -1,   155,   156,   157,   158,   159,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    89,    -1,    91,    -1,    -1,    94,    95,    96,
      97,    -1,    -1,    -1,    -1,   102,    -1,    -1,   105,   106,
      -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,    -1,   131,   196,    -1,   134,    -1,    -1,
      -1,    -1,   139,    -1,    -1,   142,    -1,    -1,   145,   146,
      -1,    -1,   149,    -1,    -1,   152,    -1,   154,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,    -1,    -1,   234,   235,   236,    -1,    -1,    -1,    -1,
     177,   178,    -1,   180,   181,   182,   183,    -1,    -1,    -1,
      -1,    -1,   189,   190,    -1,    -1,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,    -1,
      -1,   218,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,   232,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   241,    -1,    -1,    21,    -1,    23,
     247,    -1,    -1,    -1,    -1,   252,    -1,    31,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,   264,    -1,    -1,
     267,   268,   269,   270,    -1,    -1,    -1,   274,    -1,    -1,
      -1,   278,   279,   280,    -1,    -1,    -1,   284,   285,    63,
      -1,    -1,    -1,    -1,    -1,    -1,   293,    -1,    -1,   296,
     297,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,   306,
     307,    -1,   309,   310,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    95,    96,    97,    -1,    -1,    -1,    -1,   102,    -1,
      -1,    -1,   106,    -1,    -1,    -1,   110,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,    -1,   120,    -1,    -1,    -1,
      -1,    -1,   126,    -1,    -1,    -1,    -1,   131,     5,    -1,
     134,    -1,    -1,    -1,    -1,   139,    -1,    77,   142,    -1,
      -1,   145,   146,    -1,    21,   149,    23,    -1,   152,    -1,
     154,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    -1,
      -1,    -1,    -1,   103,   104,    -1,    -1,   107,    -1,    -1,
      -1,    -1,    -1,   177,   178,    -1,   180,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    63,    -1,    -1,    -1,
      -1,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,    -1,    -1,   218,    -1,    -1,    94,    95,    96,
      97,    -1,    -1,   227,    -1,   102,   230,   231,    -1,   106,
      -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,   116,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,    -1,   131,    -1,    -1,   134,    -1,    -1,
      -1,    -1,   139,   267,   268,   142,    -1,    -1,   145,   146,
      -1,    -1,   149,    -1,    -1,   152,   280,   154,    -1,    -1,
     284,   285,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     294,   295,    -1,   297,   103,   104,    -1,    -1,   107,    -1,
     177,   178,    -1,   180,    -1,   309,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    -1,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,     5,
      -1,   218,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     227,    -1,    -1,   230,   231,    21,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     267,   268,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,   280,    -1,    -1,    -1,   284,   285,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   294,   295,    -1,
     297,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    97,   309,    -1,    -1,    -1,   102,    -1,    -1,    -1,
     106,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,
     116,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,
     126,    -1,    -1,    -1,    -1,   131,     5,    -1,   134,    -1,
      -1,    -1,    -1,   139,    -1,    -1,   142,    -1,    -1,   145,
     146,    -1,    21,   149,    23,    -1,   152,    -1,   154,    -1,
      -1,    -1,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,   178,    -1,   180,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
      -1,    -1,   218,    -1,    -1,    94,    95,    96,    97,    -1,
      -1,   227,    -1,   102,   230,   231,    -1,   106,    -1,    -1,
      -1,   110,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,
      -1,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,
      -1,    -1,   131,    -1,    -1,   134,    -1,    -1,    -1,    -1,
     139,   267,   268,   142,    -1,    -1,   145,   146,    -1,    -1,
     149,    -1,    -1,   152,   280,   154,    -1,    -1,   284,   285,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   294,   295,
      -1,   297,    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,
      -1,   180,    -1,   309,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,     5,    -1,   218,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,    -1,
      -1,   230,   231,    21,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,   268,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,
      -1,   280,    -1,    -1,    -1,   284,   285,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   294,   295,    -1,   297,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    97,
     309,    -1,    -1,    -1,   102,    -1,    -1,    -1,   106,    -1,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,   116,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,
      -1,    -1,    -1,   131,    -1,    -1,   134,    -1,    -1,    -1,
      -1,   139,    -1,    -1,   142,    -1,    -1,   145,   146,    -1,
      -1,   149,    -1,    -1,   152,    -1,   154,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,
     178,    -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,    -1,    -1,
     218,    -1,     9,    10,    11,    12,    13,    14,    -1,   227,
      -1,    -1,   230,   231,    21,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,
     268,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,   280,    -1,    -1,    -1,   284,   285,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,   294,   295,    -1,   297,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,
      97,   309,    -1,    -1,    -1,   102,    -1,    -1,    -1,   106,
      -1,    -1,    -1,   110,    94,    95,    96,    97,    -1,   116,
      -1,    -1,   102,   120,    -1,    -1,   106,    -1,    -1,   126,
     110,    -1,    -1,    -1,   131,    -1,   116,   134,    -1,    -1,
     120,    -1,   139,    -1,    -1,   142,   126,    -1,   145,   146,
      -1,   131,   149,    -1,   134,   152,    -1,   154,    -1,   139,
      -1,    -1,   142,    -1,    -1,   145,   146,    -1,    -1,   149,
      -1,    -1,   152,    -1,   154,    -1,    -1,    -1,    -1,    -1,
     177,   178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,
      -1,    -1,    38,    39,    40,    41,    -1,    -1,    44,    45,
      -1,    47,    48,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     227,    -1,    -1,   230,   231,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,   227,    -1,    -1,
     230,   231,    -1,    89,    -1,    91,    92,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     267,   268,    -1,   270,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,   267,   268,    -1,
     270,    -1,    -1,    -1,    -1,    -1,    -1,   294,   295,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,
      -1,    -1,   309,   310,   294,   295,    94,    95,    96,    97,
      95,    -1,    -1,    -1,   102,    -1,   306,    -1,   106,   309,
     310,    -1,   110,    -1,    -1,    -1,    -1,    -1,   116,    -1,
      -1,    -1,   120,    -1,    -1,    -1,   121,    -1,   126,   124,
      -1,    -1,    -1,   131,    -1,    -1,   134,    -1,    -1,    -1,
     135,   139,    -1,    -1,   142,    -1,    -1,   145,   146,    -1,
      21,   149,    23,    -1,   152,    -1,   154,    -1,    -1,    -1,
      31,    -1,   218,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,   177,
     178,   237,   238,   239,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    63,    -1,    -1,    -1,   252,    -1,   254,   255,
      -1,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,    -1,    -1,    94,    95,    96,    97,    -1,    -1,   227,
      -1,   102,   230,   231,    -1,   106,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,   254,
     131,    -1,    -1,   134,    -1,    -1,    -1,    -1,   139,   267,
     268,   142,   270,    -1,   145,   146,   271,    -1,   149,    -1,
      -1,   152,    -1,   154,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   294,   295,    -1,    -1,
      -1,    -1,   297,    -1,    -1,    -1,   177,   178,    -1,   180,
      -1,   309,   310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,    -1,    -1,   218,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   227,    -1,    -1,   230,
     231,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,   267,   268,    -1,    -1,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   280,
      -1,    -1,    -1,   284,   285,    -1,    71,    72,    73,    74,
      75,    76,    -1,   294,   295,    -1,   297,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    91,    -1,   309,    94,
      95,    96,    97,    -1,    -1,    -1,    -1,   102,    -1,    -1,
      -1,   106,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   126,    -1,    -1,    -1,    -1,   131,    -1,    -1,   134,
      -1,    -1,    -1,    -1,   139,    -1,    -1,   142,    -1,    -1,
     145,   146,    -1,    -1,   149,    -1,    -1,   152,    -1,   154,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,   178,    -1,   180,   181,   182,   183,    -1,
      -1,    -1,    -1,    -1,   189,   190,    -1,    -1,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,    -1,    -1,   218,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    -1,   232,    -1,    -1,
      30,    31,    -1,    -1,    34,    -1,   241,    -1,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,   252,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   264,
      -1,    -1,   267,   268,   269,   270,    -1,    -1,    -1,   274,
      -1,    -1,    -1,   278,   279,   280,    -1,    -1,    -1,   284,
     285,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   293,    -1,
      -1,   296,   297,    -1,    94,    95,    96,    97,    -1,    -1,
      -1,   306,   102,    -1,   309,   310,   106,    -1,    -1,    -1,
     110,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,   134,    -1,    -1,    -1,    -1,   139,
      -1,    -1,   142,    -1,    -1,   145,   146,    -1,    -1,   149,
      -1,    -1,   152,    -1,   154,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,
     180,   181,   182,   183,    -1,    -1,    -1,    -1,    -1,   189,
     190,    -1,    -1,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,    -1,    -1,   218,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    95,    96,    97,    -1,    -1,    -1,    -1,   102,
      -1,    -1,    -1,   106,    -1,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,   126,    -1,    -1,    -1,    -1,   131,    -1,
      -1,   134,    -1,    -1,    -1,    -1,   139,    -1,    -1,   142,
     280,    -1,   145,   146,   284,   285,   149,   121,    -1,   152,
     124,   154,    -1,    -1,    -1,    -1,   296,   297,    -1,    -1,
      -1,   135,    -1,    -1,    -1,    -1,   306,    -1,    -1,   309,
     310,    -1,    -1,    -1,   177,   178,    -1,   180,   181,   182,
     183,    -1,    -1,    -1,    -1,    -1,   189,   190,    -1,    -1,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,    -1,    -1,   218,    23,    -1,    -1,    -1,
      -1,    -1,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   280,    -1,    -1,
     254,   284,   285,    -1,    -1,    23,    -1,    94,    95,    96,
      97,    -1,    -1,   296,   297,   102,    -1,   271,    -1,   106,
      -1,    -1,    -1,   110,    -1,    -1,   309,   310,    -1,   116,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,   297,   131,    63,    -1,   134,    -1,    -1,
      -1,    -1,   139,    -1,    -1,   142,    -1,    -1,   145,   146,
      -1,    -1,   149,    -1,    -1,   152,    -1,   154,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    97,
      -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,   106,    -1,
     177,   178,   110,    -1,    -1,    -1,    -1,    -1,   116,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,
      -1,    -1,    -1,   131,    -1,    -1,   134,    -1,    -1,    -1,
      -1,   139,    -1,    -1,   142,    -1,    -1,   145,   146,    -1,
      -1,   149,    -1,    -1,   152,    -1,   154,    -1,    -1,    -1,
     227,    -1,    -1,   230,   231,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,
     178,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,
     267,   268,    -1,   270,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,   294,   295,   227,
      -1,    -1,   230,   231,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   309,   310,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    95,    96,    97,    -1,
      -1,    -1,    -1,   102,    -1,    -1,    -1,   106,    -1,   267,
     268,   110,   270,    -1,    -1,    -1,    -1,   116,    -1,    -1,
      -1,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,
      -1,    -1,   131,    -1,    -1,   134,   294,   295,    -1,    -1,
     139,    -1,    -1,   142,    -1,    -1,   145,   146,    -1,    -1,
     149,   309,   310,   152,    -1,   154,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,
      -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,    -1,    -1,   218,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,    -1,
      -1,   230,   231,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,   268,
      -1,    -1,    -1,     0,     1,    -1,    -1,     4,    -1,     6,
      -1,   280,    -1,    -1,    -1,   284,   285,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   294,   295,    -1,   297,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     309,    38,    -1,    40,    -1,    42,    -1,    -1,    45,    46,
      47,    -1,    49,    -1,    -1,    -1,    53,    54,    55,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   134,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   218,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,    -1,    -1,    -1,    -1,   252,    -1,   254
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   315,     0,     1,     4,     6,    26,    27,    28,    29,
      38,    40,    42,    45,    46,    47,    49,    53,    54,    55,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,   101,   110,   116,   134,   218,   232,   247,
     252,   254,   316,   318,   319,   320,   321,   379,   380,   381,
     383,   397,   316,    96,    95,   376,   376,   376,   381,   383,
     397,   381,   386,   386,   386,   381,   389,   321,    42,   322,
      38,    40,    45,    46,    47,    49,   218,   232,   247,   252,
     254,   323,    42,   324,    38,    40,    42,    45,    46,    47,
      49,   218,   232,   247,   252,   254,   325,    46,   326,    38,
      39,    40,    41,    44,    45,    47,    48,    51,    89,    91,
      92,    93,   218,   232,   237,   238,   239,   247,   252,   254,
     255,   327,   232,   237,   238,   252,   328,    38,    40,    45,
      47,    51,    89,    91,   329,    40,   330,    23,    30,    31,
      34,    94,    95,    96,    97,   102,   106,   110,   116,   126,
     131,   134,   139,   142,   145,   146,   149,   152,   154,   177,
     178,   180,   181,   182,   183,   189,   190,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     218,   280,   284,   285,   296,   297,   309,   310,   338,   377,
     481,   482,   483,   484,   485,   489,   545,   548,   550,   554,
     559,   560,   562,   564,   574,   575,   577,   579,   581,   583,
     585,   587,   589,   591,   593,   595,   597,   599,   601,   603,
     607,   609,   611,   612,   614,   616,   618,   620,   622,   624,
     626,   628,    51,   290,   291,   292,   331,   337,    51,   332,
     337,    95,   333,   334,    82,   226,   381,   391,   391,   391,
     391,     0,   316,   376,   376,    50,   287,   288,   394,   395,
     396,    33,    45,    55,    56,    71,    72,    73,    74,    75,
      76,    89,    91,   195,   218,   232,   241,   247,   252,   264,
     267,   268,   269,   270,   274,   278,   279,   293,   306,   401,
     402,   403,   404,   405,   406,   407,   411,   412,   413,   416,
     417,   424,   428,   433,   434,   436,   437,   438,   454,   455,
     457,   458,   460,   461,   464,   465,   472,   473,   474,   475,
     476,   479,   480,   484,   491,   492,   493,   494,   495,   496,
     500,   501,   502,   529,   543,   548,   549,   572,   573,   574,
     316,   305,   305,   316,   339,   342,   401,   376,   344,   346,
     481,   502,   349,   376,   353,   383,   398,   381,   383,   386,
     386,   386,   389,    82,   226,   391,   391,   391,   391,   397,
     379,   381,   382,   381,   383,   384,   398,   381,   386,   387,
     386,   386,   389,    82,   226,   520,   381,   391,   392,   391,
     392,   391,   392,   391,   392,   386,   381,   380,   400,   383,
     400,    38,   400,   386,   386,   400,   400,    38,    39,   386,
     400,   400,    82,   240,   520,   391,    38,   400,    38,   400,
      38,   400,   391,   391,   391,    38,   400,   391,    38,   400,
      38,   400,   391,   381,   383,   386,   386,   400,    38,   386,
     383,    98,    99,   100,   376,   576,   103,   104,   196,   197,
     200,   487,   488,    32,   196,   551,   123,   490,   103,   104,
     105,   578,   105,   107,   108,   109,   580,   103,   104,   111,
     112,   113,   114,   115,   582,   103,   104,   107,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   584,   105,   107,
     125,   127,   128,   129,   130,   586,   105,   125,   132,   243,
     588,   103,   104,   117,   119,   120,   121,   136,   137,   138,
     590,   105,   107,   125,   127,   128,   130,   140,   141,   592,
     118,   128,   137,   143,   144,   594,   128,   144,   596,   137,
     147,   148,   598,   121,   125,   150,   151,   600,   125,   150,
     151,   153,   602,   125,   128,   143,   147,   150,   151,   155,
     156,   157,   158,   159,   604,   105,   150,   151,   608,   125,
     150,   151,   179,   610,   105,   116,   118,   130,   134,   137,
     184,   216,   217,   297,   561,   563,   615,   185,   617,   185,
     619,   147,   186,   187,   188,   621,   118,   137,   613,   107,
     122,   137,   143,   191,   192,   623,   118,   137,   625,   105,
     118,   125,   137,   143,   627,    95,   121,   124,   135,   254,
     271,   297,   546,   547,   548,   103,   104,   124,   196,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   234,   235,   236,   565,   566,   569,   271,   281,
     553,   496,   501,   282,   180,   189,   190,   193,   194,   629,
     303,   304,   556,   376,   495,   337,   291,   337,    39,    41,
      43,    44,    51,    52,    84,   335,   391,   391,   376,   234,
     514,   515,   248,   527,   528,   250,   251,   425,   516,   517,
     377,   518,   519,    94,    94,    94,    77,   561,   473,   376,
     481,   544,   544,    55,    90,   376,    95,   546,    82,   172,
     565,   566,   233,   233,   248,   233,   425,    77,    77,   561,
       4,   317,   503,   504,   289,   399,   405,   234,   235,   414,
     415,   147,   242,   243,   244,   245,   246,   418,   419,   265,
     435,     5,    21,    63,    77,   102,   106,   110,   116,   120,
     134,   180,   227,   230,   231,   267,   268,   294,   295,   439,
     440,   441,   442,   443,   444,   445,   447,   448,   449,   450,
     451,   452,   453,   482,   483,   489,   538,   539,   540,   545,
     550,   554,   560,   561,   562,   564,   570,   571,   574,    77,
     271,   272,   273,   456,   462,   463,    77,   459,   462,   275,
     276,   277,   466,   467,   468,   469,    23,   482,    38,   477,
     478,    15,    16,    17,    18,   308,     8,    24,    47,     9,
      10,    11,    12,    13,    14,   102,   106,   110,   116,   126,
     131,   134,   139,   142,   145,   146,   149,   152,   154,   177,
     178,   270,   310,   450,   482,   483,   497,   498,   499,   502,
     530,   531,   532,   533,   534,   535,   536,   537,   539,   540,
     541,   542,    45,    45,   513,   530,   531,   513,   306,   306,
     306,   306,   306,   394,   401,   339,   342,   344,   346,   349,
     353,   391,   391,   515,   528,   517,   519,   401,    50,    50,
      50,   346,   391,    50,   346,   381,   386,   400,    38,    38,
     391,   381,   381,   381,   381,   381,   381,   386,   376,     7,
       8,   105,   200,   201,   486,    95,   117,   233,   102,   116,
     102,   116,   157,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   605,   563,   312,   312,   103,   104,
     116,   124,   134,   219,   220,   221,   567,   568,   569,   282,
     282,    94,   300,   555,   311,   336,   337,   526,   526,    94,
     250,   251,   429,    94,     5,   116,   134,   452,    77,   470,
     471,   496,    23,    23,    88,   306,    45,    45,    45,    94,
     250,   569,    45,   452,   452,   429,   452,    94,   452,   452,
      77,   499,   502,   507,   508,   511,   536,   537,     7,   307,
     377,    94,    94,   415,    70,   102,   116,   154,   203,   421,
     377,    94,    94,    94,   377,   420,   419,   126,   139,   154,
     266,   452,     5,   452,    15,    16,    17,    18,   308,    20,
      22,     8,    47,     5,   462,    77,     7,     7,     5,     7,
       5,   452,   452,   467,     7,   306,   376,   306,   478,   541,
     541,   532,   533,   534,   495,    23,   306,   408,   531,   536,
       7,    15,    16,    17,    18,   308,     7,    20,    22,     8,
     531,   452,   452,   316,   316,   341,   343,   345,   350,   354,
     306,   306,   306,   306,   306,   526,   526,    94,    94,    94,
     526,    94,   381,   381,    94,   488,    88,   121,   171,   172,
     173,   174,   175,   176,   606,    94,    94,   103,   104,   103,
     104,    94,    94,   283,   552,    94,   144,   299,   557,   561,
     306,   306,   235,    94,    95,   235,   426,   452,     5,     5,
     452,   482,    82,   399,   509,   510,   377,   377,    94,   496,
     505,   506,   452,   452,   452,    94,    45,   452,    94,   426,
      36,   452,   317,     5,   317,   509,   317,   504,   133,   128,
     133,   422,   423,   105,   105,    63,   105,   452,     5,   439,
     482,   540,   541,   440,   441,   442,    94,   444,   439,   446,
     482,   502,   452,   452,   482,   540,   570,   570,   452,   463,
     452,   462,   469,   470,   505,   376,   317,   409,   410,   311,
     536,   541,   541,   532,   533,   534,   536,    94,   536,   536,
      40,    45,    47,    49,   147,   218,   232,   247,   252,   254,
     307,   316,   318,   340,    85,   105,   307,   316,   318,   368,
     374,   401,    81,    82,    83,    84,    85,    88,   105,   147,
     307,   316,   318,   351,    82,    84,   105,   147,   307,   316,
     318,   351,    35,    37,   307,   316,   318,   341,   343,   345,
     350,   354,   306,   306,     7,   313,   313,   552,   286,   552,
      94,   103,   104,   558,   364,   363,    94,    20,    95,   253,
     427,   452,   452,     5,    95,   378,   510,   306,   405,   509,
     452,    20,    95,   427,   452,    36,   512,   536,   537,   543,
       7,    95,    95,    95,   452,     5,   462,   462,     5,   218,
     307,   404,   405,   507,     7,   307,   376,   385,   376,   388,
     388,   376,   390,    95,    82,   226,   376,   393,   393,   393,
     393,   316,    71,    72,   375,    95,   316,   316,   316,   378,
     378,   305,    86,    87,   352,    94,    95,   119,   120,   196,
     216,   358,   359,   367,    78,    79,    80,    82,   347,   348,
     316,   378,   305,   359,   347,   316,    95,   305,   307,   307,
     307,   307,   307,   364,   363,    94,    94,    85,   124,   219,
     307,   316,   318,   525,   105,   219,   307,   316,   318,   522,
     259,   260,   261,   262,   263,   432,   249,   431,    94,   452,
     505,   307,   432,   431,   452,   317,   423,   452,   470,     5,
     307,   307,     5,   317,   410,   342,   344,   349,   353,   393,
     393,   360,   360,   360,   360,    35,   316,   316,   346,     8,
     316,     7,   316,   316,   346,     5,   316,   135,   369,   306,
     355,   307,   307,   552,   305,   149,   154,   521,   380,    96,
     380,   249,   430,    94,   426,   405,   430,   307,   470,   543,
     306,   306,   306,   306,   360,   360,   306,   306,   306,   306,
      95,   358,   348,   232,   247,   252,   254,   359,    22,    94,
      95,   304,   370,   371,   372,   316,    95,   356,   357,   316,
     306,     6,   316,   124,   316,    94,    95,   235,   307,   307,
     317,   343,   345,   350,   354,   306,   306,   361,   365,   362,
     366,    36,   373,   316,   316,   316,   316,   316,    94,    22,
      25,     7,   307,    95,   523,   524,   521,   234,   307,   307,
     307,   307,   364,   363,   307,   316,   318,   514,   307,   316,
     318,   527,   307,   316,   318,   516,   307,   316,   318,   518,
     377,   369,    94,    94,   317,   357,     5,     7,   307,   316,
     316,   316,   316,   316,   307,   307,   316,   316,   316,   316,
      94,   524,   316,   316,   316
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   314,   315,   315,   316,   316,   317,   317,   318,   318,
     318,   318,   318,   319,   319,   319,   319,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   321,   321,   321,   321,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   322,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   324,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   326,   327,   327,   327,   327,
     327,   327,   327,   327,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   327,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   327,   327,   327,   328,   328,   328,   328,
     328,   328,   329,   329,   329,   329,   329,   329,   329,   330,
     331,   331,   332,   332,   333,   334,   334,   335,   335,   335,
     335,   335,   335,   335,   335,   336,   336,   337,   337,   337,
     338,   339,   340,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   342,   343,   343,
     343,   343,   343,   343,   344,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   346,   346,   347,   347,   348,
     348,   348,   348,   349,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   351,   351,   352,   352,
     353,   354,   354,   354,   354,   354,   355,   356,   356,   356,
     357,   358,   359,   359,   360,   361,   361,   361,   361,   362,
     362,   362,   362,   363,   363,   363,   363,   364,   364,   364,
     364,   365,   365,   365,   365,   366,   366,   366,   366,   367,
     367,   367,   367,   367,   368,   369,   370,   370,   371,   371,
     371,   371,   372,   372,   373,   373,   374,   375,   375,   376,
     377,   377,   377,   378,   379,   379,   380,   380,   380,   380,
     380,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   397,
     397,   397,   398,   399,   400,   400,   401,   401,   402,   403,
     403,   404,   404,   404,   404,   405,   405,   405,   405,   405,
     405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   405,   405,   406,   406,   407,   408,   408,   409,   409,
     409,   410,   411,   411,   412,   412,   413,   413,   414,   414,
     415,   415,   416,   416,   417,   418,   418,   419,   419,   419,
     419,   419,   419,   420,   421,   421,   421,   421,   421,   422,
     422,   423,   423,   424,   424,   424,   425,   425,   425,   426,
     426,   427,   427,   428,   428,   429,   429,   429,   430,   430,
     431,   431,   431,   432,   432,   432,   432,   432,   433,   434,
     435,   435,   435,   435,   435,   436,   437,   437,   438,   438,
     438,   438,   438,   438,   439,   439,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   440,   440,   440,   441,
     441,   442,   442,   443,   443,   444,   445,   445,   446,   446,
     447,   447,   448,   449,   450,   451,   451,   451,   452,   452,
     452,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     454,   454,   455,   456,   456,   456,   457,   457,   458,   459,
     459,   459,   459,   459,   460,   460,   461,   461,   462,   462,
     463,   463,   463,   464,   464,   465,   466,   466,   467,   467,
     468,   468,   469,   469,   470,   470,   471,   472,   472,   472,
     473,   473,   474,   474,   475,   475,   476,   477,   477,   478,
     479,   479,   480,   481,   482,   482,   482,   483,   484,   484,
     484,   484,   484,   484,   484,   484,   484,   484,   484,   484,
     484,   484,   484,   485,   486,   486,   486,   487,   487,   487,
     487,   487,   488,   488,   489,   489,   490,   490,   491,   491,
     491,   492,   492,   493,   493,   494,   494,   495,   496,   496,
     497,   498,   499,   499,   499,   500,   501,   501,   501,   502,
     503,   503,   503,   504,   504,   504,   505,   505,   506,   507,
     507,   508,   509,   509,   510,   510,   511,   511,   512,   512,
     513,   513,   514,   515,   516,   517,   518,   519,   520,   520,
     521,   521,   522,   522,   523,   523,   524,   525,   525,   525,
     526,   527,   527,   528,   529,   529,   529,   530,   530,   531,
     531,   531,   532,   532,   532,   533,   533,   534,   534,   535,
     535,   536,   537,   537,   538,   538,   539,   540,   540,   540,
     540,   540,   540,   540,   540,   540,   540,   540,   540,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   541,   542,   542,   542,   542,
     542,   542,   543,   543,   543,   543,   543,   543,   544,   544,
     545,   545,   545,   546,   546,   547,   547,   547,   547,   547,
     548,   548,   548,   548,   548,   548,   548,   548,   548,   548,
     548,   548,   548,   548,   548,   548,   548,   548,   548,   548,
     548,   549,   549,   549,   549,   549,   549,   550,   551,   551,
     552,   552,   553,   553,   554,   555,   555,   556,   556,   557,
     557,   558,   558,   559,   559,   560,   560,   560,   561,   561,
     562,   562,   563,   563,   563,   563,   564,   564,   564,   565,
     565,   566,   566,   566,   566,   566,   566,   566,   566,   566,
     566,   566,   566,   566,   566,   566,   567,   567,   567,   567,
     567,   567,   567,   568,   568,   568,   568,   569,   569,   569,
     569,   570,   570,   571,   571,   572,   572,   572,   573,   574,
     574,   574,   574,   574,   574,   574,   574,   574,   574,   574,
     574,   574,   574,   574,   574,   574,   575,   576,   576,   576,
     577,   578,   578,   578,   579,   580,   580,   580,   580,   581,
     582,   582,   582,   582,   582,   582,   582,   582,   582,   583,
     584,   584,   584,   584,   584,   584,   584,   584,   584,   584,
     584,   584,   585,   586,   586,   586,   586,   586,   586,   586,
     587,   588,   588,   588,   588,   589,   590,   590,   590,   590,
     590,   590,   590,   590,   590,   591,   592,   592,   592,   592,
     592,   592,   592,   592,   593,   594,   594,   594,   594,   594,
     595,   596,   596,   597,   598,   598,   598,   599,   600,   600,
     600,   600,   601,   602,   602,   602,   602,   603,   603,   603,
     604,   604,   604,   604,   604,   604,   604,   604,   604,   604,
     605,   605,   605,   605,   605,   605,   605,   605,   605,   605,
     605,   605,   606,   606,   606,   606,   606,   606,   606,   606,
     607,   608,   608,   608,   609,   610,   610,   610,   610,   611,
     611,   611,   611,   611,   611,   611,   611,   612,   613,   613,
     614,   615,   615,   615,   615,   616,   617,   618,   619,   620,
     621,   621,   621,   621,   622,   623,   623,   623,   623,   623,
     623,   624,   625,   625,   626,   627,   627,   627,   627,   627,
     628,   629,   629,   629,   629,   629
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       5,     3,     2,     1,     1,     2,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     6,     2,     6,     3,     2,     6,     6,
       3,     6,     2,     3,     3,     7,     7,     3,     3,     3,
       2,     6,     2,     6,     6,     6,     3,     6,     2,     3,
       3,     7,     7,     3,     3,     3,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     2,     2,     2,     2,     2,
       4,     2,     2,     2,     2,     3,     2,     2,     2,     2,
       2,     3,     2,     2,     3,     2,     2,     3,     2,     2,
       3,     2,     2,     3,     2,     2,     3,     3,     2,     2,
       2,     2,     2,     3,     4,     4,     2,     3,     2,     2,
       3,     2,     2,     2,     2,     2,     3,     2,     2,     3,
       2,     1,     2,     1,     3,     0,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     2,
       1,     0,     2,     0,     2,     2,     3,     8,     8,     8,
       8,     8,     8,     9,     9,     8,     8,     0,     0,     2,
       2,     3,     3,     3,     0,     0,     2,     2,     4,     4,
       4,     4,     4,     2,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     0,     0,     2,     2,     4,     6,     6,
       6,     6,     6,     4,     4,     3,     2,     2,     1,     1,
       0,     0,     2,     2,     5,     5,     3,     1,     3,     3,
       1,     1,     1,     3,     0,     0,     2,     2,     2,     0,
       2,     2,     2,     0,     2,     2,     2,     0,     2,     2,
       2,     0,     2,     2,     2,     0,     2,     2,     2,     1,
       1,     1,     1,     1,     6,     2,     1,     1,     1,     1,
       3,     3,     1,     2,     2,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     2,     3,     1,     2,     3,     1,
       2,     1,     2,     3,     1,     2,     2,     2,     1,     2,
       2,     2,     2,     2,     0,     1,     1,     2,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     2,     1,     3,
       3,     5,     3,     4,     1,     2,     1,     3,     1,     2,
       2,     2,     1,     2,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     1,     2,     2,     1,     1,     1,     3,
       1,     1,     1,     7,     6,     3,     1,     1,     0,     1,
       1,     0,     3,     5,     3,     1,     1,     0,     0,     3,
       0,     3,     3,     1,     1,     1,     1,     1,     2,     1,
       0,     4,     4,     4,     3,     2,     1,     1,     3,     4,
       4,     5,     6,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     3,     1,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     3,     4,     5,     2,     3,     2,
       2,     1,     1,     3,     4,     1,     2,     1,     1,     2,
       3,     1,     3,     4,     3,     5,     3,     6,     1,     3,
       1,     1,     1,     1,     2,     1,     1,     2,     2,     1,
       1,     3,     1,     1,     1,     2,     1,     4,     5,     6,
       1,     1,     7,     8,     6,     1,     1,     1,     2,     2,
       6,     8,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     3,     0,     2,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     3,
       3,     3,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     3,     3,     3,     3,     5,     1,     2,     1,     1,
       2,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     4,     1,     4,     1,     1,     1,     1,     1,
       1,     1,     5,     3,     1,     3,     3,     3,     6,     3,
       0,     6,     5,     1,     2,     2,     3,     3,     3,     1,
       1,     1,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     1,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     3,     4,     1,     4,     4,     2,     1,     1,
       0,     2,     1,     1,     5,     2,     0,     1,     1,     1,
       1,     1,     1,     4,     5,     7,     5,     4,     1,     1,
       2,     3,     1,     1,     1,     1,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     3,     3,     4,     4,     5,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     6,     1,     1,     1,
       2,     1,     1,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
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
       2,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     1,     1,     1,     1,     2,     4,     2,     1,     2,
       1,     1,     1,     4,     2,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (nft);
  YYUSE (scanner);
  YYUSE (state);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct nft_ctx *nft, void *scanner, struct parser_state *state)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, nft, scanner, state);
  YYFPRINTF (yyoutput, ")");
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
  unsigned long int yylno = yyrline[yyrule];
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
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
            /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
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
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          case 95: /* "string"  */
#line 275 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3908 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 96: /* "quoted string"  */
#line 275 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3914 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 97: /* "string with a trailing asterisk"  */
#line 275 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3920 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 319: /* line  */
#line 539 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3926 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 320: /* base_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3932 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 321: /* add_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3938 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 322: /* replace_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3944 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 323: /* create_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3950 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 324: /* insert_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3956 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 325: /* delete_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3962 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 326: /* get_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3968 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 327: /* list_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3974 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 328: /* reset_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3980 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 329: /* flush_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3986 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 330: /* rename_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3992 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 331: /* import_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3998 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 332: /* export_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4004 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 333: /* monitor_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4010 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 334: /* monitor_event  */
#line 753 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4016 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* describe_cmd  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 4022 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* table_block_alloc  */
#line 557 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 4028 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* chain_block_alloc  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 4034 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* set_block_alloc  */
#line 568 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4040 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* set_block_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4046 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 349: /* map_block_alloc  */
#line 571 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 4052 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 353: /* flowtable_block_alloc  */
#line 574 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 4058 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 355: /* flowtable_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4064 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* flowtable_list_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4070 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 357: /* flowtable_expr_member  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4076 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* data_type_atom_expr  */
#line 536 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4082 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 359: /* data_type_expr  */
#line 536 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4088 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* obj_block_alloc  */
#line 577 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4094 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 367: /* type_identifier  */
#line 531 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4100 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 370: /* extended_prio_name  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4106 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* dev_spec  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4112 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* identifier  */
#line 531 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4118 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* string  */
#line 531 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4124 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 381: /* table_spec  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4130 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 382: /* tableid_spec  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4136 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* chain_spec  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4142 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* chainid_spec  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4148 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* chain_identifier  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4154 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* set_spec  */
#line 547 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4160 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* setid_spec  */
#line 547 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4166 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* set_identifier  */
#line 547 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4172 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* flowtable_spec  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4178 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* obj_spec  */
#line 547 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4184 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* objid_spec  */
#line 547 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4190 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 393: /* obj_identifier  */
#line 547 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4196 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* handle_spec  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4202 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* position_spec  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4208 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 396: /* index_spec  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4214 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* rule_position  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4220 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* ruleid_spec  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4226 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* comment_spec  */
#line 531 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4232 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* ruleset_spec  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4238 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* rule  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 4244 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* stmt_list  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 4250 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* stateful_stmt  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4256 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* stmt  */
#line 582 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4262 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* verdict_stmt  */
#line 582 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4268 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* verdict_map_stmt  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4274 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* verdict_map_expr  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4280 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* verdict_map_list_expr  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4286 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* verdict_map_list_member_expr  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4292 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* connlimit_stmt  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4298 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 412: /* counter_stmt  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4304 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* counter_stmt_alloc  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4310 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* log_stmt  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4316 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* log_stmt_alloc  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4322 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* limit_stmt  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4328 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* quota_unit  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4334 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* quota_stmt  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4340 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* reject_stmt  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4346 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* reject_stmt_alloc  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4352 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 436: /* nat_stmt  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4358 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* nat_stmt_alloc  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4364 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* tproxy_stmt  */
#line 603 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4370 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 439: /* primary_stmt_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4376 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 440: /* shift_stmt_expr  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4382 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 441: /* and_stmt_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4388 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* exclusive_or_stmt_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4394 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* inclusive_or_stmt_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4400 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 444: /* basic_stmt_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4406 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 445: /* concat_stmt_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4412 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 446: /* map_stmt_expr_set  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4418 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 447: /* map_stmt_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4424 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* prefix_stmt_expr  */
#line 640 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4430 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 449: /* range_stmt_expr  */
#line 640 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4436 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 450: /* wildcard_expr  */
#line 640 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4442 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* multiton_stmt_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4448 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* stmt_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4454 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 454: /* masq_stmt  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4460 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 455: /* masq_stmt_alloc  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4466 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* redir_stmt  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4472 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* redir_stmt_alloc  */
#line 600 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4478 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* dup_stmt  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4484 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* fwd_stmt  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4490 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* queue_stmt  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4496 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* queue_stmt_alloc  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4502 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* set_elem_expr_stmt  */
#line 666 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4508 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* set_elem_expr_stmt_alloc  */
#line 666 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4514 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* set_stmt  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4520 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* map_stmt  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4526 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* meter_stmt  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4532 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* flow_stmt_legacy_alloc  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4538 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* meter_stmt_alloc  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4544 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* match_stmt  */
#line 582 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4550 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* variable_expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4556 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* symbol_expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4562 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 483: /* integer_expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4568 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* primary_expr  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4574 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* fib_expr  */
#line 744 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4580 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 489: /* osf_expr  */
#line 749 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4586 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 491: /* shift_expr  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4592 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 492: /* and_expr  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4598 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 493: /* exclusive_or_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4604 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* inclusive_or_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4610 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 495: /* basic_expr  */
#line 627 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4616 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 496: /* concat_expr  */
#line 650 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4622 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 497: /* prefix_rhs_expr  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4628 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 498: /* range_rhs_expr  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4634 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 499: /* multiton_rhs_expr  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4640 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* map_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4646 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* expr  */
#line 672 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4652 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 502: /* set_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4658 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 503: /* set_list_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4664 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 504: /* set_list_member_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4670 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* meter_key_expr  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4676 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* meter_key_expr_alloc  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4682 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* set_elem_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4688 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 508: /* set_elem_expr_alloc  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4694 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 511: /* set_lhs_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4700 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 512: /* set_rhs_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4706 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* initializer_expr  */
#line 672 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4712 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 514: /* counter_config  */
#line 757 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).counter)); }
#line 4718 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 515: /* counter_obj  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4724 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 516: /* quota_config  */
#line 759 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).quota)); }
#line 4730 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* quota_obj  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4736 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* secmark_config  */
#line 763 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).secmark)); }
#line 4742 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* secmark_obj  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4748 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* timeout_states  */
#line 781 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 4754 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 524: /* timeout_state  */
#line 781 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).list)); }
#line 4760 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 526: /* ct_obj_alloc  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4766 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 527: /* limit_config  */
#line 761 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).limit)); }
#line 4772 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* limit_obj  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4778 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* relational_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4784 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* list_rhs_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4790 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* rhs_expr  */
#line 675 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4796 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* shift_rhs_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4802 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* and_rhs_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4808 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* exclusive_or_rhs_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4814 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* inclusive_or_rhs_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4820 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* basic_rhs_expr  */
#line 675 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4826 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 537: /* concat_rhs_expr  */
#line 675 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4832 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* boolean_expr  */
#line 771 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4838 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* keyword_expr  */
#line 672 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4844 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* primary_rhs_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4850 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* verdict_expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4856 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 544: /* chain_expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4862 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 545: /* meta_expr  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4868 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 549: /* meta_stmt  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4874 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 550: /* socket_expr  */
#line 730 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4880 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 554: /* numgen_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4886 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 559: /* xfrm_expr  */
#line 785 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4892 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 560: /* hash_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4898 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 562: /* rt_expr  */
#line 736 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4904 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 564: /* ct_expr  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4910 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 570: /* symbol_stmt_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4916 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 571: /* list_stmt_expr  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4922 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 572: /* ct_stmt  */
#line 588 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4928 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 573: /* payload_stmt  */
#line 586 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4934 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 574: /* payload_expr  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4940 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 575: /* payload_raw_expr  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4946 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 577: /* eth_hdr_expr  */
#line 692 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4952 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 579: /* vlan_hdr_expr  */
#line 692 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4958 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 581: /* arp_hdr_expr  */
#line 695 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4964 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 583: /* ip_hdr_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4970 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 585: /* icmp_hdr_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4976 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 587: /* igmp_hdr_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4982 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 589: /* ip6_hdr_expr  */
#line 701 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4988 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 591: /* icmp6_hdr_expr  */
#line 701 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4994 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 593: /* auth_hdr_expr  */
#line 704 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5000 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 595: /* esp_hdr_expr  */
#line 704 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5006 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 597: /* comp_hdr_expr  */
#line 704 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5012 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 599: /* udp_hdr_expr  */
#line 707 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5018 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 601: /* udplite_hdr_expr  */
#line 707 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5024 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 603: /* tcp_hdr_expr  */
#line 766 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5030 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 607: /* dccp_hdr_expr  */
#line 710 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5036 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 609: /* sctp_hdr_expr  */
#line 710 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5042 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 611: /* exthdr_expr  */
#line 714 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5048 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 612: /* hbh_hdr_expr  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5054 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 614: /* rt_hdr_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5060 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 616: /* rt0_hdr_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5066 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 618: /* rt2_hdr_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5072 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 620: /* rt4_hdr_expr  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5078 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 622: /* frag_hdr_expr  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5084 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 624: /* dst_hdr_expr  */
#line 716 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5090 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 626: /* mh_hdr_expr  */
#line 722 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5096 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 628: /* exthdr_exists_expr  */
#line 775 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 5102 "parser_bison.c" /* yacc.c:1257  */
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
#line 126 "parser_bison.y" /* yacc.c:1429  */
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 5219 "parser_bison.c" /* yacc.c:1429  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
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

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 791 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[0].cmd) != NULL) {
					(yyvsp[0].cmd)->location = (yylsp[0]);
					list_add_tail(&(yyvsp[0].cmd)->list, state->cmds);
				}
			}
#line 5413 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 8:
#line 808 "parser_bison.y" /* yacc.c:1646  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5425 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 9:
#line 816 "parser_bison.y" /* yacc.c:1646  */
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
#line 5443 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 830 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 5454 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 11:
#line 837 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5469 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 848 "parser_bison.y" /* yacc.c:1646  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 5479 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 855 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 5485 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 856 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 5491 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 857 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 5497 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 16:
#line 859 "parser_bison.y" /* yacc.c:1646  */
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
#line 5519 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 878 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5525 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 879 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5531 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 880 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5537 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 881 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5543 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 882 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5549 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 883 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5555 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 884 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5561 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 885 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5567 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 886 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5573 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 887 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5579 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 888 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5585 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 889 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 890 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5597 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 891 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5603 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 892 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5609 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 896 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5617 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 901 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5627 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 907 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5635 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 912 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5646 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 919 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5654 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 923 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5662 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 928 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5672 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 935 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5682 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 941 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5690 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 946 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5700 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 42:
#line 952 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5713 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 961 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5721 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 965 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5729 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 969 "parser_bison.y" /* yacc.c:1646  */
    {

				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 5738 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 974 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 5746 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 978 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5754 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 982 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5762 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 988 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5770 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 994 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5778 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 999 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5788 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1005 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5796 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1010 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5807 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1018 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5817 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1025 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5827 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1031 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5835 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1036 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5845 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1042 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5858 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1051 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5866 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1055 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1059 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 5882 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1063 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_TIMEOUT, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-3].obj));
			}
#line 5890 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1067 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1071 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SECMARK, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5906 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1077 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5914 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1083 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1087 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5930 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1091 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5938 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1095 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5946 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1099 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1103 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1107 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1111 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1115 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5986 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1119 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5994 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1123 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6002 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1127 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6010 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1131 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6018 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1135 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6026 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1139 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 6034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1143 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6042 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1147 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6050 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1151 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1155 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1161 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 6074 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1167 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1171 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6090 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1175 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6098 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1179 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1183 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6114 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1187 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6122 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1191 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1195 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6138 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1199 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6146 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1203 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6154 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1207 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6162 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1211 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6170 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1215 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6178 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1219 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6186 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1223 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1227 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6202 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1231 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6210 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1235 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARKS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6218 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1239 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SECMARK, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6226 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1243 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6234 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1247 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6242 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1251 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6250 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1255 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6258 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1259 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6266 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1263 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6274 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1267 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6282 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1271 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6290 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1275 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6298 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1279 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6306 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1283 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_TIMEOUT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6314 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1289 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6322 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1293 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6330 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1297 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 6338 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1301 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6346 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1305 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6354 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1309 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6362 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1315 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6370 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1319 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6378 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1323 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6386 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1327 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6394 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1331 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6402 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1335 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6410 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1339 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6418 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1345 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 6427 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1352 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6437 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1358 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1366 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6457 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1372 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6467 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1380 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 6478 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1388 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6484 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1389 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6490 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1392 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 6496 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1393 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 6502 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1394 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 6508 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1395 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 6514 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1396 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 6520 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1397 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 6526 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1398 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 6532 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1399 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 6538 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1402 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 6544 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1406 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 6550 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1407 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 6556 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1408 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 6562 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1412 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 6572 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1420 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 6581 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1427 "parser_bison.y" /* yacc.c:1646  */
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
#line 6597 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1440 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 6603 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1447 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6616 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1458 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6628 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1468 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6640 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1479 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6652 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1489 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6665 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1500 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6678 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1509 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 6691 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1518 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_TIMEOUT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 6704 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1529 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6717 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1540 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_SECMARK;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6730 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1551 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 6739 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1557 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 6745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1563 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 6754 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1570 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6762 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1575 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6768 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1579 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6777 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1584 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6786 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1589 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6795 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1594 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6804 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1599 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6813 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1604 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 6822 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1616 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6830 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1622 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 6836 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1623 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 6842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1624 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 6848 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1625 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_EVAL; }
#line 6854 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1629 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6862 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1634 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6868 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1638 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6877 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1645 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].expr)->dtype;

				expr_free((yyvsp[-1].expr));
				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6890 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1656 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6901 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1665 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6912 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1674 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6923 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1683 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_SECMARK;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6934 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1690 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6943 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1695 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6952 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1703 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 6960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1707 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 6968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1712 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 6974 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1713 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 6980 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1717 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 6988 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1722 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 6994 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1726 "parser_bison.y" /* yacc.c:1646  */
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
#line 7011 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1739 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 7019 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1745 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1752 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), EXPR_INVALID);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7037 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1757 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1765 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
			}
#line 7056 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1773 "parser_bison.y" /* yacc.c:1646  */
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
#line 7072 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1788 "parser_bison.y" /* yacc.c:1646  */
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
#line 7093 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1807 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 7101 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1812 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7107 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1816 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->counter = *(yyvsp[0].counter);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7116 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1822 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7122 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1826 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->quota = *(yyvsp[0].quota);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7131 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1832 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7137 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1836 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7145 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1841 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7151 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1845 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1850 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1854 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->limit = *(yyvsp[0].limit);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7174 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1860 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 7180 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1864 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->secmark = *(yyvsp[0].secmark);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 7189 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1870 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7195 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1871 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("mark"); }
#line 7201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1872 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("dscp"); }
#line 7207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1873 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("ecn"); }
#line 7213 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1874 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("classid"); }
#line 7219 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1878 "parser_bison.y" /* yacc.c:1646  */
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
#line 7249 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1906 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.prio_spec) = (yyvsp[0].prio_spec);
				(yyval.prio_spec).loc = (yyloc);
			}
#line 7258 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1913 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.string) = strdup("out");
			}
#line 7266 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1920 "parser_bison.y" /* yacc.c:1646  */
    {
				struct prio_spec spec = {0};
				spec.num = (yyvsp[0].val);
				(yyval.prio_spec) = spec;
			}
#line 7276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1926 "parser_bison.y" /* yacc.c:1646  */
    {
				struct prio_spec spec = {0};
				spec.str = (yyvsp[0].string);
				(yyval.prio_spec) = spec;
			}
#line 7286 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1932 "parser_bison.y" /* yacc.c:1646  */
    {
				struct prio_spec spec = {0};
				spec.num = (yyvsp[0].val);
				spec.str = (yyvsp[-2].string);
				(yyval.prio_spec) = spec;
			}
#line 7297 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1939 "parser_bison.y" /* yacc.c:1646  */
    {
				struct prio_spec spec = {0};
				spec.num = -(yyvsp[0].val);
				spec.str = (yyvsp[-2].string);
				(yyval.prio_spec) = spec;
			}
#line 7308 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1947 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 7314 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1948 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = -(yyvsp[0].val); }
#line 7320 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1951 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7326 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1952 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 7332 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1956 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].chain)->policy != -1) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].val);
			}
#line 7345 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1966 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_ACCEPT; }
#line 7351 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1967 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_DROP;   }
#line 7357 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1979 "parser_bison.y" /* yacc.c:1646  */
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
#line 7374 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1993 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 7380 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1997 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 7386 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1998 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 7392 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1999 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_INET; }
#line 7398 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 279:
#line 2000 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_ARP; }
#line 7404 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 280:
#line 2001 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 7410 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 281:
#line 2002 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 7416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 282:
#line 2006 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 7427 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 283:
#line 2015 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yyloc);
			}
#line 7438 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 284:
#line 2024 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 7448 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 285:
#line 2032 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 7458 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 286:
#line 2040 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 7468 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 287:
#line 2048 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 7478 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 288:
#line 2056 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 7488 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 289:
#line 2064 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 7498 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 290:
#line 2073 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).flowtable	= (yyvsp[0].string);
			}
#line 7507 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 291:
#line 2080 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable	= (yyvsp[0].string);
			}
#line 7516 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 292:
#line 2087 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 7526 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 293:
#line 2095 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 7536 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 294:
#line 2103 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 7546 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 295:
#line 2111 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 7556 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 296:
#line 2119 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 7566 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 297:
#line 2127 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 7576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 298:
#line 2135 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 7584 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 299:
#line 2139 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7593 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 300:
#line 2144 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7605 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 301:
#line 2152 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7614 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 302:
#line 2159 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7623 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 303:
#line 2166 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strlen((yyvsp[0].string)) > NFTNL_UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed",
							 NFTNL_UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 7637 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2178 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 7646 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2183 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 7655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2190 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 7663 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2194 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 7671 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 308:
#line 2200 "parser_bison.y" /* yacc.c:1646  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 7685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 309:
#line 2212 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 7695 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 310:
#line 2218 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 7704 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2251 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7712 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2255 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7720 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2261 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7728 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2267 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7737 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2272 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7748 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2281 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7757 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2286 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7766 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2294 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 7774 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2300 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[0].val);
			}
#line 7783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2305 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[0].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 7793 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2316 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 7801 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2320 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7811 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 348:
#line 2328 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7819 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 350:
#line 2335 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 7827 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2339 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 7835 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 354:
#line 2349 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 7843 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 355:
#line 2355 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7851 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 357:
#line 2362 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 7860 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 358:
#line 2367 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 7869 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2372 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 7878 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 360:
#line 2377 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 7887 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 361:
#line 2382 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 7896 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2387 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 7904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 363:
#line 2393 "parser_bison.y" /* yacc.c:1646  */
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
#line 7936 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 364:
#line 2423 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 7944 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2427 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 7952 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2431 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 7960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2435 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 7968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2439 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 7976 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2445 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7984 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 371:
#line 2452 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 7992 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 372:
#line 2456 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 8000 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2462 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 8013 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2471 "parser_bison.y" /* yacc.c:1646  */
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
#line 8036 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2490 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2497 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 8052 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2498 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 8058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2499 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 8064 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2502 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("bytes"); }
#line 8070 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2503 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 8076 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 381:
#line 2506 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 8082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2508 "parser_bison.y" /* yacc.c:1646  */
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
#line 8099 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2523 "parser_bison.y" /* yacc.c:1646  */
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
#line 8119 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2539 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 8129 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2546 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 8135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 386:
#line 2547 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 8141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 387:
#line 2548 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 8147 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2551 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 8153 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 389:
#line 2552 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 8159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 390:
#line 2555 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 8165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2556 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 8171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 392:
#line 2558 "parser_bison.y" /* yacc.c:1646  */
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
#line 8188 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 393:
#line 2572 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL; }
#line 8194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2573 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60; }
#line 8200 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2574 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 8206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2575 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 8212 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2576 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 8218 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2583 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 8226 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2589 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 8235 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2594 "parser_bison.y" /* yacc.c:1646  */
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
#line 8250 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 402:
#line 2605 "parser_bison.y" /* yacc.c:1646  */
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
#line 8265 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 403:
#line 2616 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				datatype_set((yyvsp[-4].stmt)->reject.expr, &icmpx_code_type);
				xfree((yyvsp[0].string));
			}
#line 8279 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 404:
#line 2626 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 8287 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 406:
#line 2634 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 8293 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 407:
#line 2635 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 8299 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2639 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 8309 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2645 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-2].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[0].expr);
			}
#line 8319 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2651 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8329 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2657 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = NFPROTO_UNSPEC;
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8340 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2664 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-4].val);
				(yyval.stmt)->tproxy.addr = (yyvsp[-2].expr);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8351 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2671 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = tproxy_stmt_alloc(&(yyloc));
				(yyval.stmt)->tproxy.family = (yyvsp[-3].val);
				(yyval.stmt)->tproxy.port = (yyvsp[0].expr);
			}
#line 8361 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2678 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8367 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2679 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2680 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2681 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8385 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2682 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8391 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2683 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2684 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8403 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2685 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8409 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2686 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8415 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2687 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8421 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2688 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8427 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2689 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8433 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2694 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8441 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2698 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8449 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2705 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8457 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2712 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8465 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2719 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2729 "parser_bison.y" /* yacc.c:1646  */
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
#line 8494 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2752 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8502 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2755 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8508 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2759 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 8516 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2765 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8524 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2771 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 8537 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2792 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 8545 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2796 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 8553 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2800 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.family = (yyvsp[-2].val);
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 8562 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2805 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8571 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 455:
#line 2810 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8580 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2815 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->nat.family = (yyvsp[-4].val);
				(yyvsp[-5].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8590 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2821 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8598 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2825 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8606 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2829 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8614 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2838 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 8620 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 463:
#line 2842 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8628 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2846 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8637 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2851 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8645 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2860 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 8651 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2864 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8659 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2868 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8667 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2872 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8675 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 472:
#line 2876 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8684 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2881 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2888 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 8702 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2893 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 8712 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2901 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 8721 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2906 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 8732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2916 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8740 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2921 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 8746 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2922 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 8752 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2923 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 8758 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2931 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 8766 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2937 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8774 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 488:
#line 2944 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 8783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 489:
#line 2949 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 8791 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 491:
#line 2956 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8799 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 492:
#line 2961 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 8805 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2962 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 8811 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 496:
#line 2970 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8819 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2976 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 8830 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 498:
#line 2983 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 8841 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 499:
#line 2990 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-5].val);
				(yyval.stmt)->set.key = (yyvsp[-2].expr);
				(yyval.stmt)->set.set = (yyvsp[-4].expr);
				(yyval.stmt)->set.stmt = (yyvsp[-1].stmt);
			}
#line 8853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 500:
#line 2999 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 8859 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 501:
#line 3000 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 8865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 502:
#line 3004 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.key = (yyvsp[-3].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 8877 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 503:
#line 3012 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-7].val);
				(yyval.stmt)->map.key = (yyvsp[-4].expr);
				(yyval.stmt)->map.data = (yyvsp[-1].expr);
				(yyval.stmt)->map.stmt = (yyvsp[-3].stmt);
				(yyval.stmt)->map.set = (yyvsp[-6].expr);
			}
#line 8890 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 504:
#line 3023 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 8901 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 505:
#line 3029 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 8907 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 506:
#line 3033 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 8915 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 507:
#line 3039 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8923 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 509:
#line 3046 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 8931 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 510:
#line 3052 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 8944 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 511:
#line 3061 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 8957 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 512:
#line 3072 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8965 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 513:
#line 3078 "parser_bison.y" /* yacc.c:1646  */
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
#line 8993 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 515:
#line 3105 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9004 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 516:
#line 3112 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 9015 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 517:
#line 3121 "parser_bison.y" /* yacc.c:1646  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 9028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 518:
#line 3131 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 519:
#line 3132 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 520:
#line 3133 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 521:
#line 3134 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9052 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 522:
#line 3135 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 523:
#line 3136 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9064 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 524:
#line 3137 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9070 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 525:
#line 3138 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9076 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 526:
#line 3139 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 527:
#line 3140 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9088 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 528:
#line 3141 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9094 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 529:
#line 3142 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9100 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 530:
#line 3143 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 531:
#line 3144 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9112 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 532:
#line 3145 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 9118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 533:
#line 3149 "parser_bison.y" /* yacc.c:1646  */
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
#line 9143 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 534:
#line 3171 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 9149 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 535:
#line 3172 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 9155 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 536:
#line 3173 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 9161 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 537:
#line 3176 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 9167 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 538:
#line 3177 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 9173 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 539:
#line 3178 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 9179 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 540:
#line 3179 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 9185 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 541:
#line 3180 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 9191 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 542:
#line 3184 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 9199 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 544:
#line 3191 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), NFT_OSF_F_VERSION);
			}
#line 9207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 545:
#line 3195 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = osf_expr_alloc(&(yyloc), (yyvsp[-1].val), 0);
			}
#line 9215 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 546:
#line 3201 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_OSF_TTL_TRUE;
			}
#line 9223 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 547:
#line 3205 "parser_bison.y" /* yacc.c:1646  */
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
#line 9239 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 549:
#line 3220 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 550:
#line 3224 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9255 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 552:
#line 3231 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9263 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 554:
#line 3238 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9271 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 556:
#line 3245 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9279 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 559:
#line 3255 "parser_bison.y" /* yacc.c:1646  */
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
#line 9300 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 560:
#line 3274 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 9308 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 561:
#line 3280 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9316 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 565:
#line 3291 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9324 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 569:
#line 3302 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9333 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 570:
#line 3309 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9342 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 571:
#line 3314 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9351 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 573:
#line 3322 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9359 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 574:
#line 3326 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9367 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 575:
#line 3330 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 9375 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 577:
#line 3337 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 9384 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 578:
#line 3344 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 9392 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 581:
#line 3354 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 9400 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 582:
#line 3360 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 9408 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 584:
#line 3367 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 9416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 585:
#line 3371 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 9424 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 592:
#line 3389 "parser_bison.y" /* yacc.c:1646  */
    {
				struct counter *counter;

				counter = xzalloc(sizeof(*counter));
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
				(yyval.counter) = counter;
			}
#line 9437 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 593:
#line 3400 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
				(yyval.obj)->counter = *(yyvsp[0].counter);
			}
#line 9447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 594:
#line 3408 "parser_bison.y" /* yacc.c:1646  */
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
#line 9470 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 595:
#line 3429 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
				(yyval.obj)->quota = *(yyvsp[0].quota);
			}
#line 9480 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 596:
#line 3437 "parser_bison.y" /* yacc.c:1646  */
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
#line 9496 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 597:
#line 3451 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_SECMARK;
				(yyval.obj)->secmark = *(yyvsp[0].secmark);
			}
#line 9506 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 598:
#line 3458 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 9512 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 599:
#line 3459 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_OBJECT_CT_TIMEOUT; }
#line 9518 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 600:
#line 3462 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_TCP; }
#line 9524 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 601:
#line 3463 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_UDP; }
#line 9530 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 602:
#line 3467 "parser_bison.y" /* yacc.c:1646  */
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
#line 9549 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 603:
#line 3482 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 9557 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 604:
#line 3488 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail((yyvsp[0].list), (yyval.list));
			}
#line 9567 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 605:
#line 3494 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail((yyvsp[0].list), (yyvsp[-2].list));
				(yyval.list) = (yyvsp[-2].list);
			}
#line 9576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 606:
#line 3502 "parser_bison.y" /* yacc.c:1646  */
    {
				struct timeout_state *ts;

				ts = xzalloc(sizeof(*ts));
				ts->timeout_str = (yyvsp[-2].string);
				ts->timeout_value = (yyvsp[0].val);
				ts->location = (yylsp[-2]);
				init_list_head(&ts->head);
				(yyval.list) = &ts->head;
			}
#line 9591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 607:
#line 3515 "parser_bison.y" /* yacc.c:1646  */
    {
				struct ct_timeout *ct;
				int l4proto = (yyvsp[-1].val);

				ct = &(yyvsp[-3].obj)->ct_timeout;
				ct->l4proto = l4proto;
			}
#line 9603 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 608:
#line 3523 "parser_bison.y" /* yacc.c:1646  */
    {
				struct ct_timeout *ct;

				ct = &(yyvsp[-6].obj)->ct_timeout;
				init_list_head(&ct->timeout_list);
				list_splice_tail((yyvsp[-2].list), &ct->timeout_list);
			}
#line 9615 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 609:
#line 3531 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].obj)->ct_timeout.l3proto = (yyvsp[-1].val);
			}
#line 9623 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 610:
#line 3537 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 9631 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 611:
#line 3543 "parser_bison.y" /* yacc.c:1646  */
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
#line 9646 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 612:
#line 3554 "parser_bison.y" /* yacc.c:1646  */
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
#line 9670 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 613:
#line 3576 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
				(yyval.obj)->limit = *(yyvsp[0].limit);
			}
#line 9680 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 614:
#line 3584 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 9688 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 615:
#line 3588 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 9696 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 616:
#line 3592 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9704 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 617:
#line 3598 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9714 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 618:
#line 3604 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 619:
#line 3611 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9730 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 620:
#line 3612 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9736 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 621:
#line 3613 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9742 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 623:
#line 3618 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9750 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 624:
#line 3622 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9758 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 626:
#line 3629 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9766 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 628:
#line 3636 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9774 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 630:
#line 3643 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9782 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 633:
#line 3653 "parser_bison.y" /* yacc.c:1646  */
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
#line 9803 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 634:
#line 3671 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = true; }
#line 9809 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 635:
#line 3672 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = false; }
#line 9815 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 636:
#line 3676 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 1, &(yyvsp[0].val));
			}
#line 9825 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 637:
#line 3683 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 9831 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 638:
#line 3684 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 9837 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3685 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 9843 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 640:
#line 3686 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 9849 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 641:
#line 3687 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 9855 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 642:
#line 3688 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 9861 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3689 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 9867 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 644:
#line 3690 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 9873 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 645:
#line 3691 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 9879 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 646:
#line 3692 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 9885 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 647:
#line 3693 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 9891 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 648:
#line 3694 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 9897 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 649:
#line 3697 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9903 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 650:
#line 3698 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9909 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 651:
#line 3699 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9915 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 652:
#line 3700 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9921 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 653:
#line 3702 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9932 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 654:
#line 3709 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9943 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 655:
#line 3716 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 656:
#line 3723 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9965 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 657:
#line 3730 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9976 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 658:
#line 3737 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9987 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 659:
#line 3744 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_IGMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9998 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 660:
#line 3751 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10009 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 661:
#line 3758 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10020 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 662:
#line 3765 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10031 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 663:
#line 3772 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10042 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 664:
#line 3779 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 10053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 665:
#line 3785 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 10059 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 666:
#line 3788 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_EQ; }
#line 10065 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 667:
#line 3789 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_NEQ; }
#line 10071 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 668:
#line 3790 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LT; }
#line 10077 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 669:
#line 3791 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GT; }
#line 10083 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 670:
#line 3792 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GTE; }
#line 10089 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 671:
#line 3793 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LTE; }
#line 10095 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 672:
#line 3797 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 10103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 673:
#line 3801 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 10111 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 674:
#line 3805 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 10119 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 675:
#line 3809 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].expr));
			}
#line 10127 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 676:
#line 3813 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].expr));
			}
#line 10135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 677:
#line 3817 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 10143 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 679:
#line 3824 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &string_type,
							 BYTEORDER_HOST_ENDIAN,
							 strlen((yyvsp[0].string)) * BITS_PER_BYTE,
							 (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 10155 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 680:
#line 3834 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 10163 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 681:
#line 3838 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 10171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 682:
#line 3842 "parser_bison.y" /* yacc.c:1646  */
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
#line 10189 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 685:
#line 3861 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_LEN; }
#line 10195 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 686:
#line 3862 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 10201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 687:
#line 3863 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 10207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 688:
#line 3864 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 10213 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 689:
#line 3865 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SECMARK; }
#line 10219 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 690:
#line 3868 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_MARK; }
#line 10225 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 691:
#line 3869 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIF; }
#line 10231 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 692:
#line 3870 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 10237 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 693:
#line 3871 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 10243 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 694:
#line 3872 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIF; }
#line 10249 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 695:
#line 3873 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 10255 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 696:
#line 3874 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 10261 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 697:
#line 3875 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKUID; }
#line 10267 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 698:
#line 3876 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKGID; }
#line 10273 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 699:
#line 3877 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 10279 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 700:
#line 3878 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 10285 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 701:
#line 3879 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 10291 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 702:
#line 3880 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 10297 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 703:
#line 3881 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 10303 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 704:
#line 3882 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 10309 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 705:
#line 3883 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 10315 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 706:
#line 3884 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CPU; }
#line 10321 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 707:
#line 3885 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 10327 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 708:
#line 3886 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 10333 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 709:
#line 3887 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 10339 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 710:
#line 3888 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SECPATH; }
#line 10345 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 711:
#line 3892 "parser_bison.y" /* yacc.c:1646  */
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
#line 10362 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 712:
#line 3905 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 10370 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 713:
#line 3909 "parser_bison.y" /* yacc.c:1646  */
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
#line 10388 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 714:
#line 3923 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 10396 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 715:
#line 3927 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 10404 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 716:
#line 3931 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 10412 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 717:
#line 3937 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 10420 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 718:
#line 3942 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 10426 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 719:
#line 3943 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SOCKET_MARK; }
#line 10432 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 720:
#line 3946 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 10438 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 721:
#line 3947 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 10444 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 722:
#line 3950 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 10450 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 723:
#line 3951 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 10456 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 724:
#line 3955 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 10464 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 725:
#line 3960 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 10470 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 726:
#line 3961 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 10476 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 727:
#line 3964 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = XFRM_POLICY_IN; }
#line 10482 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 728:
#line 3965 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = XFRM_POLICY_OUT; }
#line 10488 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 729:
#line 3968 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_XFRM_KEY_SPI; }
#line 10494 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 730:
#line 3969 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_XFRM_KEY_REQID; }
#line 10500 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 731:
#line 3972 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_XFRM_KEY_DADDR_IP4; }
#line 10506 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 732:
#line 3973 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_XFRM_KEY_SADDR_IP4; }
#line 10512 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 733:
#line 3977 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-1].val) > 255) {
					erec_queue(error(&(yylsp[-1]), "value too large"), state->msgs);
					YYERROR;
				}
				(yyval.expr) = xfrm_expr_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 10524 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 734:
#line 3985 "parser_bison.y" /* yacc.c:1646  */
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
#line 10553 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 735:
#line 4012 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 10562 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 736:
#line 4017 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 10571 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 737:
#line 4022 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 10579 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 738:
#line 4027 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 10585 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 739:
#line 4028 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 10591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 740:
#line 4032 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 10599 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 741:
#line 4036 "parser_bison.y" /* yacc.c:1646  */
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
#line 10621 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 742:
#line 4055 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 10627 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 743:
#line 4056 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 10633 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 744:
#line 4057 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 10639 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 745:
#line 4058 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_XFRM; }
#line 10645 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 746:
#line 4062 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1);
			}
#line 10653 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 747:
#line 4066 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 10661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 748:
#line 4070 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val));
			}
#line 10669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 749:
#line 4075 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 10675 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 750:
#line 4076 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 10681 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 751:
#line 4079 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 10687 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 752:
#line 4080 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 10693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 753:
#line 4081 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_MARK; }
#line 10699 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 754:
#line 4082 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATE; }
#line 10705 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 755:
#line 4083 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 10711 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 756:
#line 4084 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 10717 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 757:
#line 4085 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 10723 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 758:
#line 4086 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 10729 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 759:
#line 4087 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 10735 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 760:
#line 4088 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 10741 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 761:
#line 4089 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 10747 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 762:
#line 4090 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 10753 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 763:
#line 4091 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 10759 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 764:
#line 4092 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 10765 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 766:
#line 4096 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 10771 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 767:
#line 4097 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 10777 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 768:
#line 4098 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 10783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 769:
#line 4099 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 10789 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 770:
#line 4100 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 10795 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 771:
#line 4101 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 10801 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 773:
#line 4105 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC_IP; }
#line 10807 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 774:
#line 4106 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST_IP; }
#line 10813 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 775:
#line 4107 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC_IP6; }
#line 10819 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 776:
#line 4108 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST_IP6; }
#line 10825 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 777:
#line 4111 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 10831 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 778:
#line 4112 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 10837 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 779:
#line 4113 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 10843 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 780:
#line 4114 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 10849 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 783:
#line 4122 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 10859 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 784:
#line 4128 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 10869 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 785:
#line 4136 "parser_bison.y" /* yacc.c:1646  */
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
#line 10886 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 786:
#line 4149 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_CT_TIMEOUT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);

			}
#line 10897 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 787:
#line 4156 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 10905 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 788:
#line 4162 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].expr)->etype == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 10916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 806:
#line 4190 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 10927 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 807:
#line 4198 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 10933 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 808:
#line 4199 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 10939 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 809:
#line 4200 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 10945 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 810:
#line 4204 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 10953 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 811:
#line 4209 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 10959 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 812:
#line 4210 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 10965 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 813:
#line 4211 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 10971 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 814:
#line 4215 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 10979 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 815:
#line 4220 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_VID; }
#line 10985 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 816:
#line 4221 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_CFI; }
#line 10991 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 817:
#line 4222 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_PCP; }
#line 10997 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 818:
#line 4223 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 11003 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 819:
#line 4227 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 11011 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 820:
#line 4232 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HRD; }
#line 11017 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 821:
#line 4233 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PRO; }
#line 11023 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 822:
#line 4234 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HLN; }
#line 11029 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 823:
#line 4235 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PLN; }
#line 11035 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 824:
#line 4236 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_OP; }
#line 11041 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 825:
#line 4237 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_SADDR_ETHER; }
#line 11047 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 826:
#line 4238 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_DADDR_ETHER; }
#line 11053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 827:
#line 4239 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_SADDR_IP; }
#line 11059 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 828:
#line 4240 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_DADDR_IP; }
#line 11065 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 829:
#line 4244 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 11073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 830:
#line 4249 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_VERSION; }
#line 11079 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 831:
#line 4250 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 11085 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 832:
#line 4251 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DSCP; }
#line 11091 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 833:
#line 4252 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ECN; }
#line 11097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 834:
#line 4253 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 11103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 835:
#line 4254 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ID; }
#line 11109 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 836:
#line 4255 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 11115 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 837:
#line 4256 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_TTL; }
#line 11121 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 838:
#line 4257 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 11127 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 839:
#line 4258 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 11133 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 840:
#line 4259 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_SADDR; }
#line 11139 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 841:
#line 4260 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DADDR; }
#line 11145 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 842:
#line 4264 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 11153 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 843:
#line 4269 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 11159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 844:
#line 4270 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 11165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 845:
#line 4271 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 11171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 846:
#line 4272 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_ID; }
#line 11177 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 847:
#line 4273 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 11183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 848:
#line 4274 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 11189 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 849:
#line 4275 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 11195 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 850:
#line 4279 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_igmp, (yyvsp[0].val));
			}
#line 11203 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 851:
#line 4284 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IGMPHDR_TYPE; }
#line 11209 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 852:
#line 4285 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IGMPHDR_CHECKSUM; }
#line 11215 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 853:
#line 4286 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IGMPHDR_MRT; }
#line 11221 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 854:
#line 4287 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IGMPHDR_GROUP; }
#line 11227 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 855:
#line 4291 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 11235 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 856:
#line 4296 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 11241 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 857:
#line 4297 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 11247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 858:
#line 4298 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_ECN; }
#line 11253 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 859:
#line 4299 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 11259 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 860:
#line 4300 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 11265 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 861:
#line 4301 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 11271 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 862:
#line 4302 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 11277 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 863:
#line 4303 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 11283 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 864:
#line 4304 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 11289 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 865:
#line 4307 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 11297 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 866:
#line 4312 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 11303 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 867:
#line 4313 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 11309 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 868:
#line 4314 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 11315 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 869:
#line 4315 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 11321 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 870:
#line 4316 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 11327 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 871:
#line 4317 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 11333 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 872:
#line 4318 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 11339 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 873:
#line 4319 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 11345 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 874:
#line 4323 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 11353 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 875:
#line 4328 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 11359 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 876:
#line 4329 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 11365 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 877:
#line 4330 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 11371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 878:
#line 4331 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SPI; }
#line 11377 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 879:
#line 4332 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 11383 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 880:
#line 4336 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 11391 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 881:
#line 4341 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SPI; }
#line 11397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 882:
#line 4342 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 11403 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 883:
#line 4346 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 11411 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 884:
#line 4351 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 11417 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 885:
#line 4352 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 11423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 886:
#line 4353 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_CPI; }
#line 11429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 887:
#line 4357 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 11437 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 888:
#line 4362 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 11443 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 889:
#line 4363 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 11449 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 890:
#line 4364 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 11455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 891:
#line 4365 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 11461 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 892:
#line 4369 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 11469 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 893:
#line 4374 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 11475 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 894:
#line 4375 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 11481 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 895:
#line 4376 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 11487 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 896:
#line 4377 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 11493 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 897:
#line 4381 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 11501 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 898:
#line 4385 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 11509 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 899:
#line 4389 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 11518 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 900:
#line 4395 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 11524 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 901:
#line 4396 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 11530 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 902:
#line 4397 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 11536 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 903:
#line 4398 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 11542 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 904:
#line 4399 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 11548 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 905:
#line 4400 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 11554 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 906:
#line 4401 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 11560 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 907:
#line 4402 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 11566 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 908:
#line 4403 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 11572 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 909:
#line 4404 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 11578 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 910:
#line 4407 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 11584 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 911:
#line 4408 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 11590 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 912:
#line 4409 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 11596 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 913:
#line 4410 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 11602 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 914:
#line 4411 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 11608 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 915:
#line 4412 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 11614 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 916:
#line 4413 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 11620 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 917:
#line 4414 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 11626 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 918:
#line 4415 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 11632 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 919:
#line 4416 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 11638 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 920:
#line 4417 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 11644 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 921:
#line 4418 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 11650 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 922:
#line 4421 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 11656 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 923:
#line 4422 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 11662 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 924:
#line 4423 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 11668 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 925:
#line 4424 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 11674 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 926:
#line 4425 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 11680 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 927:
#line 4426 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 11686 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 928:
#line 4427 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 11692 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 929:
#line 4428 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 11698 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 930:
#line 4432 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 11706 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 931:
#line 4437 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 11712 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 932:
#line 4438 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 11718 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 933:
#line 4439 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 11724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 934:
#line 4443 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 11732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 935:
#line 4448 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 11738 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 936:
#line 4449 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 11744 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 937:
#line 4450 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 11750 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 938:
#line 4451 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 11756 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 947:
#line 4465 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 11764 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 948:
#line 4470 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 11770 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 949:
#line 4471 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 11776 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 950:
#line 4475 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 11784 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 951:
#line 4480 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 11790 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 952:
#line 4481 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 11796 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 953:
#line 4482 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_TYPE; }
#line 11802 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 954:
#line 4483 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 11808 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 955:
#line 4487 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 11816 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 956:
#line 4493 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 11824 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 957:
#line 4499 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 11832 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 958:
#line 4504 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 11838 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 959:
#line 4508 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 11846 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 960:
#line 4513 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 11852 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 961:
#line 4514 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 11858 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 962:
#line 4515 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_TAG; }
#line 11864 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 963:
#line 4517 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 11872 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 964:
#line 4523 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 11880 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 965:
#line 4528 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 11886 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 966:
#line 4529 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 11892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 967:
#line 4530 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 11898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 968:
#line 4531 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 11904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 969:
#line 4532 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 11910 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 970:
#line 4533 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_ID; }
#line 11916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 971:
#line 4537 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 11924 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 972:
#line 4542 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 11930 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 973:
#line 4543 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 11936 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 974:
#line 4547 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 11944 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 975:
#line 4552 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 11950 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 976:
#line 4553 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 11956 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 977:
#line 4554 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_TYPE; }
#line 11962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 978:
#line 4555 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 11968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 979:
#line 4556 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 11974 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 980:
#line 4560 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 11990 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 981:
#line 4573 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 11996 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 982:
#line 4574 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 12002 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 983:
#line 4575 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 12008 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 984:
#line 4576 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 12014 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 985:
#line 4577 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_MH; }
#line 12020 "parser_bison.c" /* yacc.c:1646  */
    break;


#line 12024 "parser_bison.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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
#line 4580 "parser_bison.y" /* yacc.c:1906  */

