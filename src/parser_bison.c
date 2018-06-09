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
#include <netinet/if_ether.h>
#include <linux/netfilter.h>
#include <linux/netfilter/nf_tables.h>
#include <linux/netfilter/nf_conntrack_tuple_common.h>
#include <linux/netfilter/nf_nat.h>
#include <linux/netfilter/nf_log.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <libnftnl/common.h>
#include <libnftnl/set.h>

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
	state->ectx.cache = &nft->cache;
	state->ectx.msgs = msgs;
	state->ectx.nf_sock = nft->nf_sock;
	state->ectx.debug_mask = nft->debug_mask;
	state->ectx.octx = &nft->output;
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
    INCLUDE = 280,
    DEFINE = 281,
    REDEFINE = 282,
    UNDEFINE = 283,
    FIB = 284,
    SOCKET = 285,
    TRANSPARENT = 286,
    HOOK = 287,
    DEVICE = 288,
    DEVICES = 289,
    TABLE = 290,
    TABLES = 291,
    CHAIN = 292,
    CHAINS = 293,
    RULE = 294,
    RULES = 295,
    SETS = 296,
    SET = 297,
    ELEMENT = 298,
    MAP = 299,
    MAPS = 300,
    FLOWTABLE = 301,
    HANDLE = 302,
    RULESET = 303,
    TRACE = 304,
    INET = 305,
    NETDEV = 306,
    ADD = 307,
    UPDATE = 308,
    REPLACE = 309,
    CREATE = 310,
    INSERT = 311,
    DELETE = 312,
    GET = 313,
    LIST = 314,
    RESET = 315,
    FLUSH = 316,
    RENAME = 317,
    DESCRIBE = 318,
    IMPORT = 319,
    EXPORT = 320,
    MONITOR = 321,
    ALL = 322,
    ACCEPT = 323,
    DROP = 324,
    CONTINUE = 325,
    JUMP = 326,
    GOTO = 327,
    RETURN = 328,
    TO = 329,
    CONSTANT = 330,
    INTERVAL = 331,
    AUTOMERGE = 332,
    TIMEOUT = 333,
    GC_INTERVAL = 334,
    ELEMENTS = 335,
    POLICY = 336,
    MEMORY = 337,
    PERFORMANCE = 338,
    SIZE = 339,
    FLOW = 340,
    OFFLOAD = 341,
    METER = 342,
    METERS = 343,
    FLOWTABLES = 344,
    NUM = 345,
    STRING = 346,
    QUOTED_STRING = 347,
    ASTERISK_STRING = 348,
    LL_HDR = 349,
    NETWORK_HDR = 350,
    TRANSPORT_HDR = 351,
    BRIDGE = 352,
    ETHER = 353,
    SADDR = 354,
    DADDR = 355,
    TYPE = 356,
    VLAN = 357,
    ID = 358,
    CFI = 359,
    PCP = 360,
    ARP = 361,
    HTYPE = 362,
    PTYPE = 363,
    HLEN = 364,
    PLEN = 365,
    OPERATION = 366,
    IP = 367,
    HDRVERSION = 368,
    HDRLENGTH = 369,
    DSCP = 370,
    ECN = 371,
    LENGTH = 372,
    FRAG_OFF = 373,
    TTL = 374,
    PROTOCOL = 375,
    CHECKSUM = 376,
    ICMP = 377,
    CODE = 378,
    SEQUENCE = 379,
    GATEWAY = 380,
    MTU = 381,
    OPTIONS = 382,
    IP6 = 383,
    PRIORITY = 384,
    FLOWLABEL = 385,
    NEXTHDR = 386,
    HOPLIMIT = 387,
    ICMP6 = 388,
    PPTR = 389,
    MAXDELAY = 390,
    AH = 391,
    RESERVED = 392,
    SPI = 393,
    ESP = 394,
    COMP = 395,
    FLAGS = 396,
    CPI = 397,
    UDP = 398,
    SPORT = 399,
    DPORT = 400,
    UDPLITE = 401,
    CSUMCOV = 402,
    TCP = 403,
    ACKSEQ = 404,
    DOFF = 405,
    WINDOW = 406,
    URGPTR = 407,
    OPTION = 408,
    ECHO = 409,
    EOL = 410,
    MAXSEG = 411,
    NOOP = 412,
    SACK = 413,
    SACK0 = 414,
    SACK1 = 415,
    SACK2 = 416,
    SACK3 = 417,
    SACK_PERMITTED = 418,
    TIMESTAMP = 419,
    KIND = 420,
    COUNT = 421,
    LEFT = 422,
    RIGHT = 423,
    TSVAL = 424,
    TSECR = 425,
    DCCP = 426,
    SCTP = 427,
    VTAG = 428,
    RT = 429,
    RT0 = 430,
    RT2 = 431,
    RT4 = 432,
    SEG_LEFT = 433,
    ADDR = 434,
    LAST_ENT = 435,
    TAG = 436,
    SID = 437,
    HBH = 438,
    FRAG = 439,
    RESERVED2 = 440,
    MORE_FRAGMENTS = 441,
    DST = 442,
    MH = 443,
    META = 444,
    MARK = 445,
    IIF = 446,
    IIFNAME = 447,
    IIFTYPE = 448,
    OIF = 449,
    OIFNAME = 450,
    OIFTYPE = 451,
    SKUID = 452,
    SKGID = 453,
    NFTRACE = 454,
    RTCLASSID = 455,
    IBRIPORT = 456,
    OBRIPORT = 457,
    IBRIDGENAME = 458,
    OBRIDGENAME = 459,
    PKTTYPE = 460,
    CPU = 461,
    IIFGROUP = 462,
    OIFGROUP = 463,
    CGROUP = 464,
    CLASSID = 465,
    NEXTHOP = 466,
    CT = 467,
    L3PROTOCOL = 468,
    PROTO_SRC = 469,
    PROTO_DST = 470,
    ZONE = 471,
    DIRECTION = 472,
    EVENT = 473,
    EXPIRATION = 474,
    HELPER = 475,
    LABEL = 476,
    STATE = 477,
    STATUS = 478,
    ORIGINAL = 479,
    REPLY = 480,
    COUNTER = 481,
    NAME = 482,
    PACKETS = 483,
    BYTES = 484,
    AVGPKT = 485,
    COUNTERS = 486,
    QUOTAS = 487,
    LIMITS = 488,
    HELPERS = 489,
    LOG = 490,
    PREFIX = 491,
    GROUP = 492,
    SNAPLEN = 493,
    QUEUE_THRESHOLD = 494,
    LEVEL = 495,
    LIMIT = 496,
    RATE = 497,
    BURST = 498,
    OVER = 499,
    UNTIL = 500,
    QUOTA = 501,
    USED = 502,
    NANOSECOND = 503,
    MICROSECOND = 504,
    MILLISECOND = 505,
    SECOND = 506,
    MINUTE = 507,
    HOUR = 508,
    DAY = 509,
    WEEK = 510,
    _REJECT = 511,
    WITH = 512,
    ICMPX = 513,
    SNAT = 514,
    DNAT = 515,
    MASQUERADE = 516,
    REDIRECT = 517,
    RANDOM = 518,
    FULLY_RANDOM = 519,
    PERSISTENT = 520,
    QUEUE = 521,
    QUEUENUM = 522,
    BYPASS = 523,
    FANOUT = 524,
    DUP = 525,
    FWD = 526,
    NUMGEN = 527,
    INC = 528,
    MOD = 529,
    OFFSET = 530,
    JHASH = 531,
    SYMHASH = 532,
    SEED = 533,
    POSITION = 534,
    INDEX = 535,
    COMMENT = 536,
    XML = 537,
    JSON = 538,
    VM = 539,
    NOTRACK = 540,
    EXISTS = 541,
    MISSING = 542,
    EXTHDR = 543
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
#define INCLUDE 280
#define DEFINE 281
#define REDEFINE 282
#define UNDEFINE 283
#define FIB 284
#define SOCKET 285
#define TRANSPARENT 286
#define HOOK 287
#define DEVICE 288
#define DEVICES 289
#define TABLE 290
#define TABLES 291
#define CHAIN 292
#define CHAINS 293
#define RULE 294
#define RULES 295
#define SETS 296
#define SET 297
#define ELEMENT 298
#define MAP 299
#define MAPS 300
#define FLOWTABLE 301
#define HANDLE 302
#define RULESET 303
#define TRACE 304
#define INET 305
#define NETDEV 306
#define ADD 307
#define UPDATE 308
#define REPLACE 309
#define CREATE 310
#define INSERT 311
#define DELETE 312
#define GET 313
#define LIST 314
#define RESET 315
#define FLUSH 316
#define RENAME 317
#define DESCRIBE 318
#define IMPORT 319
#define EXPORT 320
#define MONITOR 321
#define ALL 322
#define ACCEPT 323
#define DROP 324
#define CONTINUE 325
#define JUMP 326
#define GOTO 327
#define RETURN 328
#define TO 329
#define CONSTANT 330
#define INTERVAL 331
#define AUTOMERGE 332
#define TIMEOUT 333
#define GC_INTERVAL 334
#define ELEMENTS 335
#define POLICY 336
#define MEMORY 337
#define PERFORMANCE 338
#define SIZE 339
#define FLOW 340
#define OFFLOAD 341
#define METER 342
#define METERS 343
#define FLOWTABLES 344
#define NUM 345
#define STRING 346
#define QUOTED_STRING 347
#define ASTERISK_STRING 348
#define LL_HDR 349
#define NETWORK_HDR 350
#define TRANSPORT_HDR 351
#define BRIDGE 352
#define ETHER 353
#define SADDR 354
#define DADDR 355
#define TYPE 356
#define VLAN 357
#define ID 358
#define CFI 359
#define PCP 360
#define ARP 361
#define HTYPE 362
#define PTYPE 363
#define HLEN 364
#define PLEN 365
#define OPERATION 366
#define IP 367
#define HDRVERSION 368
#define HDRLENGTH 369
#define DSCP 370
#define ECN 371
#define LENGTH 372
#define FRAG_OFF 373
#define TTL 374
#define PROTOCOL 375
#define CHECKSUM 376
#define ICMP 377
#define CODE 378
#define SEQUENCE 379
#define GATEWAY 380
#define MTU 381
#define OPTIONS 382
#define IP6 383
#define PRIORITY 384
#define FLOWLABEL 385
#define NEXTHDR 386
#define HOPLIMIT 387
#define ICMP6 388
#define PPTR 389
#define MAXDELAY 390
#define AH 391
#define RESERVED 392
#define SPI 393
#define ESP 394
#define COMP 395
#define FLAGS 396
#define CPI 397
#define UDP 398
#define SPORT 399
#define DPORT 400
#define UDPLITE 401
#define CSUMCOV 402
#define TCP 403
#define ACKSEQ 404
#define DOFF 405
#define WINDOW 406
#define URGPTR 407
#define OPTION 408
#define ECHO 409
#define EOL 410
#define MAXSEG 411
#define NOOP 412
#define SACK 413
#define SACK0 414
#define SACK1 415
#define SACK2 416
#define SACK3 417
#define SACK_PERMITTED 418
#define TIMESTAMP 419
#define KIND 420
#define COUNT 421
#define LEFT 422
#define RIGHT 423
#define TSVAL 424
#define TSECR 425
#define DCCP 426
#define SCTP 427
#define VTAG 428
#define RT 429
#define RT0 430
#define RT2 431
#define RT4 432
#define SEG_LEFT 433
#define ADDR 434
#define LAST_ENT 435
#define TAG 436
#define SID 437
#define HBH 438
#define FRAG 439
#define RESERVED2 440
#define MORE_FRAGMENTS 441
#define DST 442
#define MH 443
#define META 444
#define MARK 445
#define IIF 446
#define IIFNAME 447
#define IIFTYPE 448
#define OIF 449
#define OIFNAME 450
#define OIFTYPE 451
#define SKUID 452
#define SKGID 453
#define NFTRACE 454
#define RTCLASSID 455
#define IBRIPORT 456
#define OBRIPORT 457
#define IBRIDGENAME 458
#define OBRIDGENAME 459
#define PKTTYPE 460
#define CPU 461
#define IIFGROUP 462
#define OIFGROUP 463
#define CGROUP 464
#define CLASSID 465
#define NEXTHOP 466
#define CT 467
#define L3PROTOCOL 468
#define PROTO_SRC 469
#define PROTO_DST 470
#define ZONE 471
#define DIRECTION 472
#define EVENT 473
#define EXPIRATION 474
#define HELPER 475
#define LABEL 476
#define STATE 477
#define STATUS 478
#define ORIGINAL 479
#define REPLY 480
#define COUNTER 481
#define NAME 482
#define PACKETS 483
#define BYTES 484
#define AVGPKT 485
#define COUNTERS 486
#define QUOTAS 487
#define LIMITS 488
#define HELPERS 489
#define LOG 490
#define PREFIX 491
#define GROUP 492
#define SNAPLEN 493
#define QUEUE_THRESHOLD 494
#define LEVEL 495
#define LIMIT 496
#define RATE 497
#define BURST 498
#define OVER 499
#define UNTIL 500
#define QUOTA 501
#define USED 502
#define NANOSECOND 503
#define MICROSECOND 504
#define MILLISECOND 505
#define SECOND 506
#define MINUTE 507
#define HOUR 508
#define DAY 509
#define WEEK 510
#define _REJECT 511
#define WITH 512
#define ICMPX 513
#define SNAT 514
#define DNAT 515
#define MASQUERADE 516
#define REDIRECT 517
#define RANDOM 518
#define FULLY_RANDOM 519
#define PERSISTENT 520
#define QUEUE 521
#define QUEUENUM 522
#define BYPASS 523
#define FANOUT 524
#define DUP 525
#define FWD 526
#define NUMGEN 527
#define INC 528
#define MOD 529
#define OFFSET 530
#define JHASH 531
#define SYMHASH 532
#define SEED 533
#define POSITION 534
#define INDEX 535
#define COMMENT 536
#define XML 537
#define JSON 538
#define VM 539
#define NOTRACK 540
#define EXISTS 541
#define MISSING 542
#define EXTHDR 543

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
	struct ct		*ct;
	struct limit		*limit;
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;
	const struct exthdr_desc *exthdr_desc;

#line 818 "parser_bison.c" /* yacc.c:355  */
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

#line 848 "parser_bison.c" /* yacc.c:358  */

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
#define YYLAST   5050

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  298
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  294
/* YYNRULES -- Number of rules.  */
#define YYNRULES  897
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1413

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   543

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   293,     2,     2,     2,
     294,   295,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   289,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   296,     2,   297,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   290,   292,   291,     2,     2,     2,     2,
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
     285,   286,   287,   288
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   747,   747,   748,   766,   767,   770,   771,   774,   782,
     796,   803,   814,   822,   823,   824,   825,   857,   858,   859,
     860,   861,   862,   863,   864,   865,   866,   867,   868,   869,
     870,   871,   874,   878,   885,   889,   897,   901,   905,   912,
     919,   923,   930,   939,   943,   947,   952,   958,   964,   968,
     975,   979,   987,   994,  1001,  1005,  1012,  1021,  1025,  1029,
    1033,  1039,  1045,  1049,  1053,  1057,  1061,  1065,  1069,  1073,
    1077,  1081,  1085,  1089,  1093,  1097,  1101,  1105,  1109,  1115,
    1121,  1125,  1129,  1133,  1137,  1141,  1145,  1149,  1153,  1157,
    1161,  1165,  1169,  1173,  1177,  1181,  1185,  1189,  1193,  1197,
    1201,  1205,  1209,  1213,  1217,  1221,  1227,  1231,  1235,  1239,
    1243,  1247,  1253,  1257,  1261,  1265,  1269,  1273,  1277,  1283,
    1290,  1296,  1304,  1310,  1318,  1327,  1328,  1331,  1332,  1333,
    1334,  1335,  1336,  1337,  1338,  1341,  1342,  1345,  1346,  1347,
    1350,  1359,  1365,  1379,  1380,  1381,  1382,  1383,  1394,  1404,
    1415,  1425,  1436,  1447,  1456,  1470,  1476,  1477,  1478,  1479,
    1480,  1481,  1489,  1494,  1495,  1496,  1497,  1502,  1507,  1512,
    1517,  1522,  1527,  1530,  1531,  1534,  1538,  1541,  1542,  1543,
    1547,  1552,  1553,  1554,  1555,  1560,  1571,  1580,  1589,  1598,
    1603,  1608,  1611,  1615,  1621,  1622,  1626,  1631,  1632,  1633,
    1634,  1647,  1653,  1660,  1665,  1670,  1673,  1681,  1695,  1696,
    1716,  1721,  1722,  1723,  1724,  1731,  1732,  1733,  1734,  1741,
    1742,  1743,  1744,  1750,  1751,  1752,  1753,  1760,  1761,  1762,
    1763,  1764,  1767,  1795,  1796,  1799,  1800,  1803,  1814,  1815,
    1818,  1821,  1822,  1823,  1826,  1841,  1842,  1845,  1846,  1847,
    1848,  1849,  1850,  1853,  1862,  1871,  1879,  1887,  1895,  1903,
    1911,  1920,  1927,  1934,  1942,  1950,  1958,  1966,  1974,  1982,
    1986,  1991,  1999,  2006,  2013,  2025,  2029,  2036,  2040,  2046,
    2058,  2064,  2071,  2072,  2073,  2074,  2075,  2076,  2077,  2078,
    2079,  2080,  2081,  2082,  2083,  2084,  2085,  2086,  2087,  2088,
    2089,  2090,  2093,  2097,  2103,  2109,  2114,  2123,  2128,  2133,
    2136,  2142,  2147,  2155,  2156,  2158,  2162,  2170,  2174,  2177,
    2181,  2187,  2188,  2191,  2197,  2201,  2204,  2209,  2214,  2219,
    2224,  2229,  2235,  2265,  2269,  2273,  2277,  2281,  2287,  2291,
    2294,  2298,  2304,  2313,  2332,  2340,  2341,  2342,  2345,  2346,
    2349,  2350,  2365,  2381,  2389,  2390,  2391,  2394,  2395,  2396,
    2397,  2412,  2413,  2414,  2415,  2416,  2419,  2422,  2429,  2433,
    2444,  2455,  2465,  2471,  2474,  2475,  2478,  2479,  2480,  2481,
    2482,  2483,  2484,  2485,  2486,  2487,  2490,  2491,  2495,  2501,
    2502,  2508,  2509,  2515,  2516,  2522,  2525,  2526,  2545,  2546,
    2549,  2553,  2556,  2562,  2568,  2579,  2580,  2581,  2584,  2585,
    2586,  2589,  2593,  2597,  2602,  2607,  2611,  2615,  2621,  2622,
    2625,  2628,  2632,  2637,  2643,  2644,  2647,  2650,  2654,  2658,
    2662,  2667,  2674,  2679,  2687,  2688,  2691,  2696,  2705,  2706,
    2712,  2713,  2714,  2717,  2718,  2721,  2727,  2731,  2734,  2739,
    2745,  2746,  2752,  2753,  2756,  2757,  2760,  2766,  2773,  2782,
    2783,  2786,  2795,  2802,  2805,  2811,  2815,  2818,  2824,  2833,
    2844,  2850,  2868,  2869,  2876,  2885,  2896,  2897,  2898,  2899,
    2900,  2901,  2902,  2903,  2904,  2905,  2906,  2907,  2908,  2911,
    2934,  2935,  2936,  2939,  2940,  2941,  2942,  2943,  2946,  2950,
    2953,  2954,  2958,  2964,  2965,  2971,  2972,  2978,  2979,  2985,
    2988,  2989,  3008,  3014,  3020,  3021,  3022,  3025,  3031,  3032,
    3033,  3036,  3043,  3048,  3053,  3056,  3060,  3064,  3070,  3071,
    3078,  3084,  3085,  3088,  3094,  3098,  3101,  3105,  3111,  3112,
    3115,  3116,  3119,  3120,  3123,  3134,  3142,  3163,  3171,  3174,
    3175,  3178,  3193,  3200,  3205,  3216,  3238,  3246,  3250,  3254,
    3258,  3264,  3270,  3278,  3279,  3280,  3283,  3284,  3288,  3294,
    3295,  3301,  3302,  3308,  3309,  3315,  3318,  3319,  3338,  3339,
    3342,  3350,  3351,  3352,  3353,  3354,  3355,  3356,  3357,  3358,
    3359,  3360,  3361,  3364,  3365,  3366,  3367,  3368,  3375,  3382,
    3389,  3396,  3403,  3410,  3417,  3424,  3431,  3438,  3447,  3448,
    3449,  3450,  3451,  3452,  3455,  3459,  3463,  3467,  3471,  3475,
    3481,  3485,  3489,  3505,  3506,  3509,  3510,  3511,  3512,  3515,
    3516,  3517,  3518,  3519,  3520,  3521,  3522,  3523,  3524,  3525,
    3526,  3527,  3528,  3529,  3530,  3531,  3532,  3533,  3534,  3537,
    3541,  3545,  3559,  3563,  3569,  3575,  3578,  3579,  3582,  3583,
    3586,  3592,  3597,  3602,  3608,  3609,  3612,  3616,  3636,  3637,
    3638,  3641,  3645,  3649,  3655,  3656,  3659,  3660,  3661,  3662,
    3663,  3664,  3665,  3666,  3667,  3668,  3669,  3670,  3671,  3672,
    3673,  3676,  3677,  3678,  3679,  3680,  3681,  3682,  3685,  3686,
    3689,  3690,  3691,  3692,  3695,  3696,  3699,  3705,  3713,  3726,
    3732,  3741,  3742,  3743,  3744,  3745,  3746,  3747,  3748,  3749,
    3750,  3751,  3752,  3753,  3754,  3755,  3756,  3759,  3768,  3769,
    3770,  3773,  3779,  3780,  3781,  3784,  3790,  3791,  3792,  3793,
    3796,  3802,  3803,  3804,  3805,  3806,  3809,  3815,  3816,  3817,
    3818,  3819,  3820,  3821,  3822,  3823,  3824,  3825,  3826,  3829,
    3835,  3836,  3837,  3838,  3839,  3840,  3841,  3844,  3850,  3851,
    3852,  3853,  3854,  3855,  3856,  3857,  3858,  3860,  3866,  3867,
    3868,  3869,  3870,  3871,  3872,  3873,  3876,  3882,  3883,  3884,
    3885,  3886,  3889,  3895,  3896,  3899,  3905,  3906,  3907,  3910,
    3916,  3917,  3918,  3919,  3922,  3928,  3929,  3930,  3931,  3934,
    3938,  3942,  3949,  3950,  3951,  3952,  3953,  3954,  3955,  3956,
    3957,  3958,  3961,  3962,  3963,  3964,  3965,  3966,  3967,  3968,
    3969,  3970,  3971,  3972,  3975,  3976,  3977,  3978,  3979,  3980,
    3981,  3982,  3985,  3991,  3992,  3993,  3996,  4002,  4003,  4004,
    4005,  4008,  4009,  4010,  4011,  4012,  4013,  4014,  4015,  4018,
    4024,  4025,  4028,  4034,  4035,  4036,  4037,  4040,  4046,  4052,
    4058,  4061,  4067,  4068,  4069,  4070,  4076,  4082,  4083,  4084,
    4085,  4086,  4087,  4090,  4096,  4097,  4100,  4106,  4107,  4108,
    4109,  4110,  4113,  4127,  4128,  4129,  4130,  4131
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
  "\"include\"", "\"define\"", "\"redefine\"", "\"undefine\"", "\"fib\"",
  "\"socket\"", "\"transparent\"", "\"hook\"", "\"device\"", "\"devices\"",
  "\"table\"", "\"tables\"", "\"chain\"", "\"chains\"", "\"rule\"",
  "\"rules\"", "\"sets\"", "\"set\"", "\"element\"", "\"map\"", "\"maps\"",
  "\"flowtable\"", "\"handle\"", "\"ruleset\"", "\"trace\"", "\"inet\"",
  "\"netdev\"", "\"add\"", "\"update\"", "\"replace\"", "\"create\"",
  "\"insert\"", "\"delete\"", "\"get\"", "\"list\"", "\"reset\"",
  "\"flush\"", "\"rename\"", "\"describe\"", "\"import\"", "\"export\"",
  "\"monitor\"", "\"all\"", "\"accept\"", "\"drop\"", "\"continue\"",
  "\"jump\"", "\"goto\"", "\"return\"", "\"to\"", "\"constant\"",
  "\"interval\"", "\"auto-merge\"", "\"timeout\"", "\"gc-interval\"",
  "\"elements\"", "\"policy\"", "\"memory\"", "\"performance\"",
  "\"size\"", "\"flow\"", "\"offload\"", "\"meter\"", "\"meters\"",
  "\"flowtables\"", "\"number\"", "\"string\"", "\"quoted string\"",
  "\"string with a trailing asterisk\"", "\"ll\"", "\"nh\"", "\"th\"",
  "\"bridge\"", "\"ether\"", "\"saddr\"", "\"daddr\"", "\"type\"",
  "\"vlan\"", "\"id\"", "\"cfi\"", "\"pcp\"", "\"arp\"", "\"htype\"",
  "\"ptype\"", "\"hlen\"", "\"plen\"", "\"operation\"", "\"ip\"",
  "\"version\"", "\"hdrlength\"", "\"dscp\"", "\"ecn\"", "\"length\"",
  "\"frag-off\"", "\"ttl\"", "\"protocol\"", "\"checksum\"", "\"icmp\"",
  "\"code\"", "\"seq\"", "\"gateway\"", "\"mtu\"", "\"options\"",
  "\"ip6\"", "\"priority\"", "\"flowlabel\"", "\"nexthdr\"",
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
  "\"until\"", "\"quota\"", "\"used\"", "\"nanosecond\"",
  "\"microsecond\"", "\"millisecond\"", "\"second\"", "\"minute\"",
  "\"hour\"", "\"day\"", "\"week\"", "\"reject\"", "\"with\"", "\"icmpx\"",
  "\"snat\"", "\"dnat\"", "\"masquerade\"", "\"redirect\"", "\"random\"",
  "\"fully-random\"", "\"persistent\"", "\"queue\"", "\"num\"",
  "\"bypass\"", "\"fanout\"", "\"dup\"", "\"fwd\"", "\"numgen\"",
  "\"inc\"", "\"mod\"", "\"offset\"", "\"jhash\"", "\"symhash\"",
  "\"seed\"", "\"position\"", "\"index\"", "\"comment\"", "\"xml\"",
  "\"json\"", "\"vm\"", "\"notrack\"", "\"exists\"", "\"missing\"",
  "\"exthdr\"", "'='", "'{'", "'}'", "'|'", "'$'", "'('", "')'", "'['",
  "']'", "$accept", "input", "stmt_separator", "opt_newline",
  "common_block", "line", "base_cmd", "add_cmd", "replace_cmd",
  "create_cmd", "insert_cmd", "delete_cmd", "get_cmd", "list_cmd",
  "reset_cmd", "flush_cmd", "rename_cmd", "import_cmd", "export_cmd",
  "monitor_cmd", "monitor_event", "monitor_object", "monitor_format",
  "markup_format", "describe_cmd", "table_block_alloc", "table_options",
  "table_block", "chain_block_alloc", "chain_block", "set_block_alloc",
  "set_block", "set_block_expr", "set_flag_list", "set_flag",
  "map_block_alloc", "map_block", "set_mechanism", "set_policy_spec",
  "flowtable_block_alloc", "flowtable_block", "flowtable_expr",
  "flowtable_list_expr", "flowtable_expr_member", "data_type_atom_expr",
  "data_type_expr", "obj_block_alloc", "counter_block", "quota_block",
  "ct_helper_block", "limit_block", "type_identifier", "hook_spec",
  "prio_spec", "dev_spec", "policy_spec", "chain_policy", "identifier",
  "string", "time_spec", "family_spec", "family_spec_explicit",
  "table_spec", "tableid_spec", "chain_spec", "chainid_spec",
  "chain_identifier", "set_spec", "setid_spec", "set_identifier",
  "flowtable_spec", "flowtable_identifier", "obj_spec", "objid_spec",
  "obj_identifier", "handle_spec", "position_spec", "index_spec",
  "rule_position", "ruleid_spec", "comment_spec", "ruleset_spec", "rule",
  "rule_alloc", "stmt_list", "stmt", "verdict_stmt", "verdict_map_stmt",
  "verdict_map_expr", "verdict_map_list_expr",
  "verdict_map_list_member_expr", "connlimit_stmt", "counter_stmt",
  "counter_stmt_alloc", "counter_args", "counter_arg", "log_stmt",
  "log_stmt_alloc", "log_args", "log_arg", "level_type", "log_flags",
  "log_flags_tcp", "log_flag_tcp", "limit_stmt", "quota_mode",
  "quota_unit", "quota_used", "quota_stmt", "limit_mode", "limit_burst",
  "time_unit", "reject_stmt", "reject_stmt_alloc", "reject_opts",
  "nat_stmt", "nat_stmt_alloc", "primary_stmt_expr", "shift_stmt_expr",
  "and_stmt_expr", "exclusive_or_stmt_expr", "inclusive_or_stmt_expr",
  "basic_stmt_expr", "concat_stmt_expr", "map_stmt_expr_set",
  "map_stmt_expr", "prefix_stmt_expr", "range_stmt_expr", "wildcard_expr",
  "multiton_stmt_expr", "stmt_expr", "nat_stmt_args", "masq_stmt",
  "masq_stmt_alloc", "masq_stmt_args", "redir_stmt", "redir_stmt_alloc",
  "redir_stmt_arg", "dup_stmt", "fwd_key_proto", "fwd_stmt",
  "nf_nat_flags", "nf_nat_flag", "queue_stmt", "queue_stmt_alloc",
  "queue_stmt_args", "queue_stmt_arg", "queue_stmt_flags",
  "queue_stmt_flag", "set_elem_expr_stmt", "set_elem_expr_stmt_alloc",
  "set_stmt", "set_stmt_op", "map_stmt", "meter_stmt",
  "flow_stmt_legacy_alloc", "flow_stmt_opts", "flow_stmt_opt",
  "meter_stmt_alloc", "match_stmt", "variable_expr", "symbol_expr",
  "integer_expr", "primary_expr", "fib_expr", "fib_result", "fib_flag",
  "fib_tuple", "shift_expr", "and_expr", "exclusive_or_expr",
  "inclusive_or_expr", "basic_expr", "concat_expr", "prefix_rhs_expr",
  "range_rhs_expr", "multiton_rhs_expr", "map_expr", "expr", "set_expr",
  "set_list_expr", "set_list_member_expr", "meter_key_expr",
  "meter_key_expr_alloc", "set_elem_expr", "set_elem_expr_alloc",
  "set_elem_options", "set_elem_option", "set_lhs_expr", "set_rhs_expr",
  "initializer_expr", "counter_config", "counter_obj", "quota_config",
  "quota_obj", "ct_obj_type", "ct_l4protoname", "ct_helper_config",
  "ct_obj_alloc", "limit_config", "limit_obj", "relational_expr",
  "list_rhs_expr", "rhs_expr", "shift_rhs_expr", "and_rhs_expr",
  "exclusive_or_rhs_expr", "inclusive_or_rhs_expr", "basic_rhs_expr",
  "concat_rhs_expr", "boolean_keys", "boolean_expr", "keyword_expr",
  "primary_rhs_expr", "relational_op", "verdict_expr", "meta_expr",
  "meta_key", "meta_key_qualified", "meta_key_unqualified", "meta_stmt",
  "socket_expr", "socket_key", "offset_opt", "numgen_type", "numgen_expr",
  "hash_expr", "nf_key_proto", "rt_expr", "rt_key", "ct_expr", "ct_dir",
  "ct_key", "ct_key_dir", "ct_key_proto_field", "ct_key_dir_optional",
  "symbol_stmt_expr", "list_stmt_expr", "ct_stmt", "payload_stmt",
  "payload_expr", "payload_raw_expr", "payload_base_spec", "eth_hdr_expr",
  "eth_hdr_field", "vlan_hdr_expr", "vlan_hdr_field", "arp_hdr_expr",
  "arp_hdr_field", "ip_hdr_expr", "ip_hdr_field", "icmp_hdr_expr",
  "icmp_hdr_field", "ip6_hdr_expr", "ip6_hdr_field", "icmp6_hdr_expr",
  "icmp6_hdr_field", "auth_hdr_expr", "auth_hdr_field", "esp_hdr_expr",
  "esp_hdr_field", "comp_hdr_expr", "comp_hdr_field", "udp_hdr_expr",
  "udp_hdr_field", "udplite_hdr_expr", "udplite_hdr_field", "tcp_hdr_expr",
  "tcp_hdr_field", "tcp_hdr_option_type", "tcp_hdr_option_field",
  "dccp_hdr_expr", "dccp_hdr_field", "sctp_hdr_expr", "sctp_hdr_field",
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
     535,   536,   537,   538,   539,   540,   541,   542,   543,    61,
     123,   125,   124,    36,    40,    41,    91,    93
};
# endif

#define YYPACT_NINF -1115

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1115)))

#define YYTABLE_NINF -706

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1115,  4804, -1115,   392, -1115, -1115,     9,    64,    64,    64,
     369,   369,   369,   369,   369,   369,   369, -1115, -1115,  1723,
     138,   843,   194,   614,   248,  1745,   562,  1226,   250,  4136,
      11,    60,   207, -1115, -1115, -1115, -1115,   153,   369,   369,
     369, -1115, -1115, -1115,   613, -1115,    64, -1115,    64,    21,
    3802, -1115,   392, -1115,   133,   144,   392,    44,   184,  3802,
      64, -1115,   148, -1115,    64, -1115, -1115,   369, -1115,   369,
     369,   369,   369,   369,   369,   159,   369,   369,   369, -1115,
     369, -1115,   369,   369,   369,   369,   369,   369,   369,   228,
     369,   369,   369, -1115,   369, -1115,   369,   369,   369,   369,
     633,   369,   369,   369,   369,   549,   369,   369,   369,   -63,
     369,   713,   793,   856,   369,   369, -1115,   369,  1095,  1225,
     369, -1115,   369,   369,   369,   369,   369,   444,   369, -1115,
     369, -1115,   662,   418,   459, -1115, -1115, -1115, -1115,   616,
     877,   803,  1994,   758,  1173,   994,   354,   127,   100,   383,
     436,  1461,   244,   311,   931,   319,   326,   417,   105,   963,
     304,   356,  1819, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115,  2556,   158,  4009,   245,   447,    64,  4136,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115,   340, -1115, -1115,   255, -1115, -1115,   340, -1115, -1115,
   -1115, -1115,   523,   369,    64,   321,   323,   441, -1115, -1115,
   -1115, -1115,   480,   488,   521, -1115, -1115, -1115,   548, -1115,
   -1115, -1115, -1115, -1115,    64,    64, -1115,   546,    64,  2097,
    2349,   368, -1115,   134,   280, -1115, -1115, -1115, -1115, -1115,
   -1115,   565,   253, -1115,   638, -1115,   363,  3802, -1115, -1115,
   -1115, -1115, -1115,   434, -1115,   176, -1115, -1115, -1115,   402,
   -1115,  2620, -1115,   -18, -1115,   119, -1115, -1115, -1115,   498,
   -1115,    77, -1115, -1115,   631, -1115, -1115, -1115,   716,   665,
     677,   410, -1115,   186, -1115,  3151, -1115, -1115, -1115,   668,
   -1115, -1115, -1115,   683, -1115,  3530,  3530, -1115,   438,   451,
   -1115, -1115,   454, -1115, -1115, -1115,   460, -1115,   470,   721,
    3802,    44,   184, -1115,   148, -1115, -1115,   369,   321,   323,
     441,  3802,    52, -1115, -1115,   265, -1115, -1115, -1115,   300,
   -1115, -1115,   148, -1115, -1115, -1115,   369,   301, -1115, -1115,
   -1115, -1115, -1115, -1115,   148, -1115, -1115, -1115, -1115, -1115,
     369, -1115, -1115, -1115, -1115, -1115,   369,   369, -1115, -1115,
   -1115,   749,   369, -1115,   369, -1115,   369, -1115,   369, -1115,
   -1115, -1115, -1115,   369, -1115,   369, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115,   369, -1115,    64, -1115, -1115, -1115, -1115,
     804, -1115, -1115, -1115, -1115, -1115,   815,   -28, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,  1512, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,    24, -1115,
   -1115,   535, -1115, -1115, -1115, -1115, -1115, -1115,   537, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115,  1224, -1115, -1115,
   -1115, -1115,   597,   116,   623,   812, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115,   609, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115,   340, -1115, -1115,   838, -1115, -1115,
     576, -1115, -1115, -1115, -1115,   839, -1115, -1115, -1115, -1115,
   -1115,  4136, -1115, -1115,   893,   -22,   889,   890,   -27,  1224,
     894,  3367,  3367,   576,  3367,   844,  3367,  3367, -1115, -1115,
     863, -1115,  3530,    28, -1115,   699, -1115, -1115,   850,   859,
     434, -1115,   297,   699,   860,   861,   862,   699,   176, -1115,
      32, -1115,  3367, -1115, -1115,  2783,   616,   877,   803,  1994,
   -1115,  1173,   112, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115,   814,   937,   952,   679,   594,   141, -1115, -1115, -1115,
   -1115, -1115,   968,   553,   969, -1115, -1115, -1115,   980, -1115,
   -1115, -1115, -1115, -1115,   981,   983, -1115,   970, -1115, -1115,
   -1115, -1115,   984, -1115,  2946, -1115,   984,  3367, -1115, -1115,
     498, -1115,   985, -1115,    64,   704,    64,    15, -1115,  4136,
    4136,  4136,  4136,  4136,  4136,    23,  3530, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115,   988, -1115,   830,   992,
     995,   709,   365,  1009, -1115, -1115, -1115,  3215,  3367,  3367,
     392,   988, -1115,   392, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115,   728,   729,   730, -1115,   731,   735, -1115, -1115, -1115,
   -1115, -1115,   938,   939,   940, -1115, -1115,   941, -1115, -1115,
   -1115, -1115,   369, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115,   943,   418, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,   385,
   -1115,   945,   946, -1115, -1115, -1115, -1115, -1115, -1115,   578,
   -1115, -1115,   948,   962,   781, -1115, -1115, -1115,   737,   831,
   -1115, -1115,   971,   -20,    77,     5,  1057,   699,   977,  4136,
    3367,  3367, -1115,   990,  1029,  3367, -1115, -1115,   993, -1115,
     -20,  1042, -1115,  3367, -1115,   638,   864,     5, -1115,   779,
    1009,   638, -1115, -1115, -1115, -1115, -1115, -1115, -1115,   951,
     145, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
     989,   991,  1022,   997, -1115,  3367,  1080,  4295,  4529,  4295,
    4295,  4295,  1003,  4295,  4295,    14,  3367,   984,  4593,  4593,
    3367,   553,  3367,   553, -1115, -1115,   608,  4136, -1115,  4136,
   -1115, -1115, -1115,   716,   665,   677, -1115,    64,   638, -1115,
   -1115,  4529,  4529,  4529,  4529,  4529,  4529,  4529,  1006,  4529,
    4529,  3530, -1115, -1115, -1115, -1115, -1115,   601,  1860,   509,
     495,   374, -1115, -1115, -1115, -1115, -1115,   809, -1115, -1115,
   -1115, -1115, -1115, -1115,  1096, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115,   805,   807, -1115, -1115, -1115,
     781,   208,  1016, -1115, -1115,  1017,    90, -1115, -1115,   865,
   -1115,  1020, -1115,     5, -1115, -1115,   823,  1057,  3802,     5,
   -1115, -1115, -1115,  3367, -1115,    99,   865,  3367,  1075, -1115,
    4458, -1115,     5,  3530, -1115, -1115, -1115, -1115,  1107, -1115,
    1028,  1030, -1115,  1031, -1115,  3367, -1115, -1115, -1115, -1115,
     814,   937,   952, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115,   553, -1115,   553,   984, -1115,    17,
    3802, -1115,  3624,    45, -1115, -1115, -1115, -1115,   830,   992,
     995, -1115, -1115, -1115, -1115,   829,    64,    64,    64,    64,
    1034,   906,    64,    64,    64, -1115, -1115, -1115,   392,   826,
    1041, -1115, -1115, -1115,   392,   392,   392, -1115,  1020,  1020,
     847,   818,  1048,     1,   622, -1115, -1115, -1115,   392,  1020,
     851,     1,   622, -1115, -1115, -1115,   392,  1053,   868, -1115,
   -1115, -1115,  1184,  2138,  1494,  1614,   433, -1115,  1049, -1115,
   -1115, -1115,  1060, -1115, -1115,   327, -1115,   693,   909,  1063,
   -1115, -1115, -1115, -1115,  4136,   871,     5, -1115,   693,   909,
   -1115, -1115,  3367,   638, -1115,  1009, -1115,   145, -1115, -1115,
   -1115, -1115,   984,   984,  4136, -1115,   875,  1149,   638, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,    64,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,  1127, -1115,
   -1115, -1115,   392,   392,   148, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115,   508, -1115, -1115, -1115, -1115,
     648, -1115, -1115,   392,   148,   586,   648, -1115,  1038,   879,
   -1115, -1115, -1115, -1115, -1115,   505, -1115,   781,  1085,   369,
     392, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,   909,
    1090, -1115,   -20,  3802, -1115,   909, -1115, -1115, -1115, -1115,
     896, -1115,   620,  3624, -1115,   899,   901,   903,   905, -1115,
     907,   908,   914,  1093, -1115, -1115, -1115,     1, -1115,   622,
   -1115, -1115, -1115,   336, -1115,    89,  1108,   392,   392, -1115,
    1088,   392, -1115, -1115,   -21, -1115,   922, -1115, -1115,   638,
   -1115, -1115, -1115, -1115,   915, -1115, -1115, -1115,  1182, -1115,
   -1115,   392,   392,   392,   508,  1126, -1115,   392, -1115,    47,
   -1115, -1115, -1115,   101, -1115, -1115, -1115, -1115, -1115, -1115,
    2412,  1603,  2175,   695, -1115,   252,   541,   114,  1128,  1089,
   -1115, -1115, -1115, -1115, -1115, -1115,    82, -1115, -1115, -1115,
     392,   392,   392,   392,   392,   892,   392, -1115, -1115, -1115,
     392, -1115, -1115, -1115,   392, -1115, -1115, -1115, -1115,    89,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115,   392, -1115, -1115,
   -1115, -1115, -1115
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     245,   245,   245,   245,   245,   245,   245,   249,   252,   245,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   125,   251,   250,   247,   248,     0,   245,   245,
     245,    14,    13,     3,     0,    17,     0,   246,     0,   269,
       0,    12,     0,   240,     0,     0,     0,    32,    34,     0,
       0,   162,     0,   180,     0,   196,    18,   245,    19,   245,
     245,   245,   245,   245,   245,     0,   245,   245,   245,    20,
     245,    21,   245,   245,   245,   245,   245,   245,   245,     0,
     245,   245,   245,    22,   245,    23,   245,   275,   245,   275,
     275,   245,   245,   275,   275,     0,   245,   275,   275,     0,
     245,   275,   275,   275,   245,   245,    24,   245,   275,   275,
     245,    25,   245,   245,   245,   245,   275,     0,   245,    26,
     245,    27,     0,     0,     0,   475,   241,   242,   243,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   629,   630,   631,   632,   633,   634,   635,
     636,   637,   638,   639,   640,   641,   642,   643,   644,   645,
     646,   647,   648,     0,     0,     0,     0,     0,     0,     0,
      31,   473,   472,   476,   477,   140,   487,   481,   621,   482,
     485,   486,   483,   484,   478,   711,   712,   713,   714,   715,
     716,   717,   718,   719,   720,   721,   722,   723,   724,   725,
     726,   479,   851,   852,   853,   854,   855,   856,   857,   858,
     480,     0,   137,   138,     0,    28,   121,     0,    29,   123,
     126,    30,   127,   245,     0,    42,     0,   347,    16,    15,
     253,   255,     0,     0,     0,   271,   270,   272,     0,   459,
     460,   614,   615,   616,     0,     0,   619,   464,     0,     0,
       0,   315,   323,     0,   347,   367,   374,   375,   420,   426,
     445,     0,     0,   652,     7,    37,   277,   279,   280,   282,
     303,   285,   286,   313,   289,   321,   290,   291,   292,   368,
     293,     0,   296,   419,   297,   425,   298,   299,   294,   443,
     300,     0,   301,   284,     0,   463,   283,   500,   503,   505,
     507,   509,   510,   518,   520,     0,   519,   470,   302,   621,
     288,   295,   287,   478,     8,     0,     0,    11,     0,     0,
      36,   258,     0,    40,   174,   173,     0,   261,     0,     0,
       0,    48,    50,   162,     0,   180,   196,   245,    56,     0,
     347,     0,     0,    62,    63,     0,    64,    65,    66,     0,
      67,    68,     0,    69,    71,   548,   245,     0,    72,    73,
      77,    78,    74,    75,     0,    80,   276,    81,    82,    83,
     245,    84,    86,   103,   102,    96,   245,   275,   100,    99,
     101,     0,   245,    89,   245,    87,   245,    90,   245,    93,
      95,    92,   108,   245,   106,   245,   109,   111,   112,   113,
     114,   115,   118,   245,   117,     0,   728,   729,   730,   474,
       0,   493,   494,   495,   496,   497,   499,     0,   655,   654,
     732,   733,   734,   731,   739,   736,   737,   738,   735,   741,
     742,   743,   744,   745,   740,   757,   758,   752,   747,   748,
     749,   750,   751,   753,   754,   755,   756,   746,   760,   763,
     762,   761,   764,   765,   766,   759,   775,   776,   768,   769,
     770,   772,   771,   773,   774,   767,   778,   783,   780,   779,
     784,   782,   781,   785,   777,   788,   791,   787,   789,   790,
     786,   794,   793,   792,   796,   797,   798,   795,   802,   803,
     800,   801,   799,   808,   805,   806,   807,   804,   820,   814,
     817,   818,   812,   813,   815,   816,   819,   821,     0,   809,
     845,   843,   844,   842,   850,   847,   848,   849,   846,   865,
     664,   864,   670,   665,   863,   866,   668,   669,     0,   666,
     862,     0,   867,   870,   869,   873,   872,   874,     0,   871,
     861,   860,   859,   882,   879,   877,   878,   880,   881,   876,
     885,   884,   883,   889,   888,   891,   887,   890,   886,   622,
     625,   626,   627,   628,   620,   623,   624,   684,   685,   677,
     678,   676,   686,   687,   703,   680,   689,   682,   683,   688,
     679,   681,   674,   675,   701,   700,   702,     0,   671,   690,
     659,   658,     0,   518,     0,     0,   894,   893,   895,   896,
     897,   892,   471,     0,   120,   139,   122,   128,   129,   131,
     130,   133,   134,   132,   135,   553,   263,     0,   545,    43,
     356,   556,    46,   345,   346,     0,   547,    44,   266,   267,
     268,     0,   617,   618,     0,     0,   622,   620,     0,     0,
     671,     0,     0,   356,     0,     0,     0,     0,   434,   435,
       0,     6,     0,     0,   522,     0,   278,   281,     0,     0,
     314,   317,     0,     0,     0,     0,     0,     0,   322,   324,
       0,   366,     0,   404,   589,     0,   581,   584,   585,   582,
     588,   583,     0,   592,   590,   591,   587,   586,   578,   579,
     386,   389,   391,   393,   395,   396,   401,   408,   405,   406,
     407,   409,   411,   373,   376,   377,   580,   378,   385,   379,
     382,   383,   380,   381,     0,   410,   384,     0,   440,   441,
     442,   418,   423,   438,     0,   424,   429,     0,   452,   453,
     444,   446,   449,   450,     0,     0,     0,     0,   465,     0,
       0,     0,     0,     0,     0,     0,     0,   608,   609,   610,
     611,   612,   613,   581,   584,   585,   582,   602,   583,   603,
     601,   600,   604,   598,   599,   597,   605,   606,   607,   516,
     593,   594,   514,   515,   564,   565,   558,   557,   569,   571,
     573,   575,   576,   563,   595,   596,   566,     0,     0,     0,
       0,   543,   542,     0,   143,   156,   163,   181,   197,   273,
      47,     0,     0,     0,    54,     0,     0,   553,    57,    60,
      58,    61,     0,     0,     0,    70,   553,     0,    79,    85,
      98,    97,   245,   104,    88,    91,    94,   107,   110,   116,
     119,     0,     0,   492,   490,   491,   489,   825,   832,   822,
     824,   823,   827,   828,   829,   830,   831,   826,   833,   811,
     667,     0,     0,   691,   692,   694,   693,   695,   696,     0,
     672,   697,     0,     0,   656,   488,   124,   136,     0,     0,
     354,   355,     0,     0,     0,   454,   456,     0,     0,     0,
       0,     0,   311,     0,   697,     0,   316,   344,     0,   353,
       0,   432,   436,     0,   539,     7,     7,   531,   533,   576,
     538,     7,   521,   274,   319,   320,   318,   337,   336,     0,
       0,   335,   331,   326,   327,   328,   329,   332,   330,   325,
       0,     0,     0,     0,   415,     0,   412,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   417,     0,     0,
       0,     0,     0,   427,   448,   447,     0,     0,   467,     0,
     466,   501,   502,   504,   506,   508,   511,     0,     7,   304,
     517,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   559,   650,   710,     9,    10,     0,     0,     0,
       0,     0,   143,   156,   163,   181,   197,     0,   254,   256,
     259,    76,   264,   105,     0,   498,   836,   835,   834,   837,
     838,   839,   840,   841,   810,     0,     0,   698,   699,   673,
     656,   656,     0,   663,   219,     0,     0,   349,   348,   350,
     457,     0,   537,   455,   534,   653,     0,   530,     0,   528,
     651,   649,   312,     0,   708,     0,   350,     0,     0,   525,
       0,   526,   532,   524,   523,   334,   340,   341,   333,   339,
       0,     0,   372,     0,   416,     0,   387,   376,   385,   388,
     390,   392,   394,   402,   403,   397,   400,   399,   398,   413,
     704,   705,   706,   707,   421,   439,   428,   430,   451,     0,
       0,   306,     0,     0,   307,   562,   567,   568,   570,   572,
     574,   561,   512,   513,   577,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,   145,   144,     0,     0,
       0,    35,   158,   157,     0,     0,     0,   171,     0,     0,
       0,     0,     0,     0,     0,    38,   165,   164,     0,     0,
       0,     0,     0,    39,   183,   182,     0,     0,     0,    41,
     199,   198,     0,     0,     0,     0,     0,   219,     0,   868,
     875,   660,     0,   662,   657,     0,   544,     0,   357,     0,
     546,   244,   536,   535,     0,     0,   529,   709,     0,   357,
     352,   433,     0,     7,   576,   540,   541,     0,   369,   370,
     371,   414,   422,   431,     0,   458,     0,     0,     7,   305,
     560,   257,   155,   260,   162,   180,   262,   196,   142,     0,
     265,   210,   210,   210,   146,   238,   239,   237,     0,   159,
     160,   161,     0,     0,     0,   195,   194,   192,   193,   227,
     229,   230,   228,   231,   208,     0,   207,   177,   178,   179,
       0,   176,   172,     0,     0,     0,     0,   191,     0,     0,
      49,    51,    52,    53,    55,     0,   727,   656,     0,     0,
       0,   221,   220,   222,   361,   362,   363,   364,   365,   357,
       0,   555,     0,     0,   468,   357,   343,   437,   527,   338,
       0,   462,     0,   309,   308,     0,     0,     0,     0,   210,
       0,     0,     0,     0,   168,   169,   170,     0,   166,     0,
     167,   184,   190,     0,   189,     0,     0,     0,     0,   661,
       0,     0,    45,   554,     0,   351,     0,   342,   461,     7,
     156,   163,   181,   197,     0,   211,   223,   215,   236,   209,
     175,     0,     0,     0,     0,     0,   233,     0,   206,     0,
     203,   201,    59,     0,   552,   360,   358,   359,   469,   310,
       0,     0,     0,     0,   219,     0,     0,     0,     0,     0,
     186,   188,   187,   185,   234,   200,     7,   202,   550,   549,
       0,     0,     0,     0,     0,     0,     0,   213,   212,   214,
       0,   225,   224,   226,     0,   217,   216,   218,   235,     0,
     205,   204,   551,   147,   148,   149,   150,     0,   151,   154,
     152,   232,   153
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1115, -1115,    -1,  -887,     6, -1115, -1115,  1198, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115,   -19, -1115,   873, -1115,   220,  -338,  -980,
    -344,  -974,  -346,    73,   -80,  -340,  -969,  -959, -1115,  -345,
    -964, -1115, -1115,  -143,   -73, -1084, -1110, -1115, -1115, -1114,
   -1115, -1115, -1115,  -164, -1115, -1115, -1115,   179,  -511,  -709,
    1154,   -23,  1466, -1115,   956, -1115, -1115,    50, -1115,   121,
     251, -1115,   106,   832,  -997,   888, -1115, -1115,   135,  1156,
     955,   163,   -10, -1115, -1115,  -286, -1115, -1115, -1115, -1115,
      34, -1115, -1115, -1115, -1115,   563, -1115, -1115, -1115,   557,
   -1115, -1115, -1115,    51, -1115,   976,  -885,   197, -1115,   595,
   -1031,    74, -1115, -1115, -1115, -1115, -1115,  -816,   316,   328,
     329, -1115,   324, -1115, -1115, -1115, -1115, -1115,  -304, -1115,
     846, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115,  -299,   320, -1115, -1115, -1115,   532, -1115,   317,  -919,
   -1115, -1115,  1026, -1115, -1115, -1115, -1115,   534, -1115, -1115,
     -58,   752,   -26,   -13, -1115, -1115, -1115,   440,   533,   538,
     539, -1115,  -172,  -180, -1115, -1115,  -652, -1115,  1116,   -52,
   -1115,   387,  -925, -1115, -1041, -1115,  -835,  -929, -1115, -1115,
     973,   -59,   954,   -57,   958,  1205, -1115, -1115,  -410,   -51,
     960, -1115,   996,  -312,   343,   344,   346, -1115,  -238,  -653,
   -1115,  -133,  -278,  -854, -1115,  -951,    10,  1061, -1115,   -32,
   -1115, -1115, -1115,  -952, -1115,    16,    43,  -459,    75,   785,
     103,  1068,  1069, -1115, -1115,  -446,   -33, -1115, -1115, -1115,
     287, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115, -1115,
   -1115, -1115, -1115, -1115
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1132,   672,  1133,    43,    44,    45,    68,    79,
      81,    93,    95,   116,   121,   129,   131,   235,   238,   241,
     242,   634,   886,   236,   190,   338,  1128,   997,   339,   998,
     342,   999,   343,  1250,  1251,   346,  1000,  1148,  1237,   348,
    1001,  1317,  1349,  1350,  1244,  1245,  1300,  1365,  1367,  1175,
    1366,  1246,  1134,  1347,  1369,  1135,  1227,  1220,   191,  1182,
      46,    47,    60,   364,    49,   367,  1212,    61,   371,  1214,
      65,  1217,   245,   379,  1221,   255,   256,   257,    50,   350,
    1042,   387,  1136,   286,   287,   288,   289,   290,   979,  1103,
    1104,   291,   292,   293,   680,   681,   294,   295,   688,   689,
     938,   932,  1068,  1069,   296,   645,  1039,  1180,   297,   892,
    1281,  1279,   298,   299,   691,   300,   301,   710,   711,   712,
     713,   714,   715,   716,  1086,   717,   718,   719,   720,   721,
     722,   723,   302,   303,   741,   304,   305,   745,   306,   670,
     307,   742,   743,   308,   309,   750,   751,   752,   753,   894,
     895,   310,   311,   312,   313,   314,   757,   758,   315,   316,
     192,   193,   725,   317,   196,   856,   436,   437,   318,   319,
     320,   321,   322,   323,   792,   793,   794,   324,   325,   326,
     673,   674,  1048,  1049,   916,   917,  1043,  1044,   918,  1193,
     810,   638,   639,   646,   647,   376,  1380,  1273,   888,   641,
     642,   327,   811,   812,   798,   799,   800,   801,   919,   803,
     726,   727,   728,   806,   807,   328,   729,   584,   585,   198,
     330,   199,   439,  1033,   612,   730,   731,   548,   732,   549,
     733,   607,   608,   880,  1029,   609,   734,   735,   331,   332,
     736,   205,   430,   206,   443,   207,   448,   208,   454,   209,
     467,   210,   475,   211,   485,   212,   494,   213,   500,   214,
     503,   215,   507,   216,   512,   217,   517,   218,   529,   869,
    1024,   219,   533,   220,   538,   221,   222,   562,   223,   550,
     224,   552,   225,   554,   226,   559,   227,   569,   228,   572,
     229,   578,   230,   621
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,   677,    51,   194,   344,   613,   746,    42,   824,   823,
     345,   826,   239,   797,   822,   825,   195,   623,   329,   920,
     914,   789,  1204,  1163,   194,  1056,   835,   329,  1059,  1061,
    1164,   789,   789,   194,  1063,   921,  1165,   754,   838,   197,
     285,  1156,  1166,   249,  1100,   200,   977,   805,  1099,   340,
     756,   334,  1208,  1265,  1376,   337,   737,   805,   805,   231,
     197,  1207,   898,   902,    62,    63,   200,  1255,   252,   197,
    1355,  1037,   201,   853,   386,   200,   386,   386,  1171,  1173,
     386,   386,  1062,  1041,   386,   386,   671,   802,   386,   386,
     386,  1102,  1239,   201,  1079,   386,   386,   802,   802,   832,
     754,    52,   201,   386,   202,   136,   137,   138,   237,  1196,
    1177,  1345,  1301,  1302,  1183,     3,  1240,  1241,     4,  1188,
       5,   353,   354,   355,   764,   202,  1222,  1223,  1106,  1107,
     586,  1076,   203,  1183,   202,   370,   372,   373,  1085,     6,
       7,     8,     9,    53,   384,   246,   247,    59,   879,   954,
     542,   392,   393,   203,   940,    53,   398,   375,  1286,   194,
     766,   881,   203,   194,   923,   941,   854,   855,   136,   137,
     138,   401,   933,  1348,   420,   421,   937,    67,   424,  1346,
     942,  1178,   358,   359,   360,   955,    54,    55,    56,  1334,
    1189,  1242,   804,   744,   764,   197,   378,   380,   382,   197,
     879,   200,   804,   804,  -347,   200,  1156,  1356,  1357,  1038,
     765,  1243,   624,   904,  1186,   361,   403,   903,   626,   560,
     410,   411,  1299,   412,   540,   250,   417,   251,   201,  1344,
     766,   504,   201,    80,   546,   547,   561,   586,   542,   341,
     543,   505,   506,   347,  1378,   738,   739,   740,  1323,  1379,
    1385,   501,  1207,     3,  1327,   329,     4,  1183,     5,  1283,
     202,   194,   389,   391,   202,   502,   394,   395,   899,  1066,
     399,   400,  1067,   795,   405,   407,   409,     6,     7,     8,
       9,   414,   416,   795,   795,  1290,   675,   130,   203,   422,
     943,    94,   203,   232,   233,   234,   344,   197,   240,   791,
     253,   254,   345,   200,   284,   969,  1288,   188,  1205,   791,
     791,   429,   833,   978,   344,  1319,   204,   682,   329,   922,
     345,  1293,   546,   547,   194,   356,   344,   667,     3,   329,
     201,     4,   345,     5,  -141,   194,  1209,   333,  1377,   374,
     820,  1329,   232,   233,   234,   530,   333,   834,   837,   635,
    1360,   831,     6,     7,     8,     9,    53,  1361,   643,   644,
     197,   662,   202,  1362,   927,   668,   200,   622,   789,  1363,
     188,   197,   987,   243,   386,     3,   663,   200,     4,   357,
       5,   669,   738,   739,   740,   988,  1045,   989,   531,   532,
     203,    53,    53,   201,   805,   928,     4,  1325,     5,     6,
       7,     8,     9,  1156,   201,  1394,  1157,  1195,  1158,   929,
     920,   914,   683,   684,   685,   686,   687,  1007,   570,    17,
      18,   610,   335,   636,   957,   202,  1011,  1239,  1268,  1232,
    1233,   611,   534,   336,     3,   571,   202,     4,   284,     5,
    1253,   188,  1359,   652,   653,   930,   840,   655,   375,   920,
     914,  1240,  1241,   203,   980,   535,   536,   573,     6,     7,
       8,     9,   789,   827,   203,  1157,    33,  1158,   495,  1016,
     574,   896,   204,   849,  -155,    34,   204,   575,   496,   423,
     637,    35,   836,  1032,   537,   497,  1172,   576,   805,  1400,
     438,   498,   499,   577,   931,   992,     3,    36,   551,     4,
     508,     5,  1017,   789,   509,   553,     3,   664,   843,     4,
       3,     5,     4,     4,     5,     5,  1307,   431,   432,   615,
       6,     7,     8,     9,   643,   644,  1242,   510,   511,   805,
       6,     7,     8,     9,     6,     7,     8,     9,   625,   804,
    1269,   250,     3,  1386,   251,     4,  1243,     5,   341,   637,
    1018,  1019,  1020,  1021,  1022,  1023,   636,   513,   555,   627,
     841,   628,  1341,   629,   630,   640,     6,     7,     8,     9,
     648,   631,   632,  1149,   333,  1150,  1141,  1342,   649,  1142,
     514,   515,  1343,   516,   396,   397,  1137,  1138,  1139,  1140,
    1141,  1313,   976,  1142,  1307,   661,  1151,   556,   557,   558,
     259,   260,     3,   633,   850,     4,  1268,     5,   433,   434,
    1143,   650,   435,   248,   952,   887,   953,     4,  1270,     5,
     915,   616,   232,   233,   234,   194,     6,     7,     8,     9,
     617,   618,   654,   804,   619,   620,  1152,   333,  1116,   666,
     920,   914,   671,  1117,   675,  1118,   791,  1119,   333,    82,
    1144,    83,     4,    84,     5,  1309,    85,    86,    87,   690,
      88,   197,   678,   679,  1097,  1159,   756,   200,   390,  1078,
     805,  1078,  1078,  1078,   804,  1078,  1078,  1027,  1028,  1115,
    1091,  1091,   761,    17,    18,   643,   644,   789,   261,   262,
     263,   264,   265,   266,   201,   762,     3,  1247,  1248,     4,
    1249,     5,   763,   805,   805,   805,   805,   805,   805,   805,
     808,   805,   805,   805,   795,   440,   441,   442,  1269,  1047,
       6,     7,     8,     9,  1264,   809,   202,  1157,   814,  1158,
      33,   759,   760,   194,   194,   194,   194,   194,   194,    34,
     791,   815,  1120,  1105,   816,    35,   971,   972,   404,  1111,
     817,  1113,  1114,    53,   203,   795,   426,   427,   428,   789,
     818,    36,  1185,    17,    18,   747,   748,   749,   252,   197,
     197,   197,   197,   197,   197,   200,   200,   200,   200,   200,
     200,   791,   805,   640,   842,   805,  1153,   896,   117,  1047,
     136,   137,   138,   118,   119,  1202,  1318,  1203,   789,   988,
    1145,   989,   201,   201,   201,   201,   201,   201,   120,   995,
      33,   851,   996,  1121,  1206,   804,   738,   739,   740,    34,
     890,   891,  1194,   852,   805,    35,    89,  1122,   406,   947,
     948,   871,  1390,   872,   202,   202,   202,   202,   202,   202,
      90,    36,  1123,    17,    18,   982,   983,  1124,   804,   804,
     804,   804,   804,   804,   804,    91,   804,   804,   804,   468,
      92,   469,   203,   203,   203,   203,   203,   203,   671,  1060,
    1296,   882,  1298,   194,  1295,  1297,   748,   749,    69,   470,
      70,   471,   472,   473,   474,    71,    72,    73,  1306,    74,
      33,   408,  1125,     3,  1225,  1226,     4,   883,     5,    34,
    1235,  1236,   884,  1088,   885,    35,    17,    18,  1312,   197,
     449,   450,   451,   452,   453,   200,   897,     6,     7,     8,
       9,    36,   791,   381,   383,  1092,  1093,   804,   889,   893,
     804,   900,   901,   429,   910,   968,   905,   913,   204,   795,
     924,   194,   201,   194,  1274,  1275,  1276,  1277,  1278,   925,
     934,   935,   936,    33,   949,   791,   791,   791,   791,   791,
     791,   791,    34,   791,   791,   791,   329,    58,    35,   804,
     950,   951,   194,   956,   202,   960,  -704,   197,   444,   197,
     445,   446,   447,   200,    36,   200,  1384,  -705,   958,   789,
     959,   961,   966,  1268,   967,   981,  1126,  1326,  1146,  1154,
    1160,   986,   203,  1127,  1047,  1147,  1155,  1161,   197,   984,
     201,   915,   201,   985,   200,   805,   329,   990,  1002,  1003,
    1004,  1005,   194,   349,   896,  1006,   352,  1034,  1008,  1009,
    1010,  1012,   539,  1014,   791,  1025,  1026,   791,  1030,   366,
     349,   201,   202,   540,   202,   541,   204,   204,   204,   204,
     204,   204,  1031,   724,   388,    75,  1032,   542,   197,   543,
    1035,  1036,   544,   755,   200,   764,   563,  1046,   329,    76,
     203,  1053,   203,   202,   194,  1057,   791,   790,  1065,   419,
    1052,   564,  1072,  1055,    77,  1075,   425,   790,   790,    78,
    1070,   201,  1071,  1083,   565,   486,  1112,   487,  1073,  1167,
     566,   203,  1169,  1168,  1170,  1269,  1174,  1176,  1192,   545,
     197,  1181,  1179,  1184,  1197,   488,   200,   489,   490,  1198,
     491,  1199,  1200,   202,  1210,  1218,  1219,  1224,   492,   493,
     413,   329,  1228,  1229,  1230,  1231,  1234,   194,  1238,  1266,
    1254,   546,   547,   201,  1258,    17,    18,  1252,   567,   568,
    1267,   203,  1280,  1282,  1292,  1257,  1101,  1259,   194,  1303,
     804,  1126,  1284,  1146,  1154,  1160,  1291,  1315,  1127,  1316,
    1147,  1155,  1161,   197,  1271,   202,   344,  1320,   194,   200,
    1324,  1272,   345,  1407,  1338,     3,   204,  1328,     4,  1330,
       5,  1331,    33,  1332,   197,  1333,   344,  1335,  1336,  1348,
     200,    34,   345,   203,  1337,  1364,   201,    35,  1353,     6,
       7,     8,     9,  1358,   197,  1368,  1374,    66,  1399,  1398,
     200,  1116,  1162,    36,   821,  1256,  1117,   201,  1118,  1340,
    1119,  1304,  1305,  1401,  1339,  1411,   362,   819,   202,  1215,
     368,   676,  1294,   926,  1308,   939,  1321,   201,  1289,  1310,
     665,   329,  1311,  1190,   204,  1314,   204,   194,   908,   202,
     415,   122,  1285,   123,  1271,  1080,   203,   791,   124,  1322,
     125,  1272,   476,   477,   126,    17,    18,  1084,  1081,   202,
    1082,  1095,   965,  1098,   651,   333,   478,   203,   479,   480,
     481,   970,  1015,   197,   973,  1211,  1213,  1213,  1216,   200,
     974,   614,   975,   482,   483,   484,  1389,   203,  1064,   813,
    1397,   127,   828,   128,   402,  1393,  1351,  1352,   830,   829,
    1354,   796,    33,   873,   874,  1120,   201,  1108,   329,  1109,
     657,    34,  1110,   870,   194,   333,   540,    35,   659,   660,
    1370,  1371,  1372,  1373,   875,     0,  1375,     0,     0,     0,
       0,     0,   543,    36,     0,     0,     0,     0,   202,     0,
    1146,  1154,  1160,     0,  1387,  1391,  1395,  1147,  1155,  1161,
     197,  1388,  1392,  1396,     0,     0,   200,     0,     0,  1402,
    1403,  1404,  1405,  1406,  1271,  1408,   203,   333,     0,  1409,
       0,  1272,     0,  1410,     0,     0,  1121,     0,     0,     0,
       0,     0,     0,   201,     0,     0,  1412,     0,     0,     0,
    1122,     0,     0,   724,   724,     0,   724,     0,   724,   724,
       0,     0,     0,     0,   790,  1123,     0,     0,     0,     0,
    1124,     0,     0,     0,     0,   202,     0,   876,   877,   878,
     594,     0,     0,     0,   724,     0,     0,   724,     0,     0,
     333,     0,   604,   605,   606,     0,     0,     0,     0,     0,
       0,     0,     0,   203,     0,     0,     0,    48,     0,     0,
       0,   204,     0,     0,     0,  1260,    57,    48,    48,     0,
       0,     0,    64,     0,     0,    48,     0,     0,     0,     0,
       0,   204,     0,     0,     0,     3,   724,     0,     4,   724,
       5,     0,     0,     0,   244,   244,   244,   906,   907,     0,
     909,     0,   911,   912,     0,     0,     0,     0,   790,     6,
       7,     8,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,   351,    48,     0,   944,     0,
      64,   946,   244,   244,   244,     0,    48,     0,   363,   365,
      48,   369,     0,     0,    64,     0,   377,   377,   377,   790,
     724,   724,   385,     0,    48,     0,     0,     0,     0,     0,
     333,  1137,  1138,  1139,  1140,  1141,   244,     0,  1142,     0,
     244,   244,   518,   244,     0,   519,   244,     0,   418,    48,
     963,     0,     0,   964,     0,  1143,    48,     0,   520,     0,
       0,     0,   521,     0,     3,   522,   523,     4,     0,     5,
     524,   525,   526,   527,   528,     3,     0,     0,     4,     0,
       5,     0,     0,     0,     0,     0,     0,     0,     6,     7,
       8,     9,     0,     0,     0,  1144,     0,     0,     0,     6,
       7,     8,     9,     0,     0,     0,  1040,   333,     0,     0,
       0,     0,   724,   724,   993,   994,     0,   724,     0,     0,
       0,     0,     0,   857,     0,   724,   858,   859,   860,   861,
     862,   863,   864,   865,   866,   867,   868,     0,     0,     0,
    1137,  1138,  1139,  1140,  1141,     0,     0,  1142,     0,     0,
       0,     0,  1149,     0,  1150,  1141,     0,   724,  1142,  1077,
     790,  1077,  1077,  1077,  1143,  1077,  1077,  1087,   724,   244,
    1090,  1090,   724,     0,   724,  1151,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   790,   790,   790,   790,   790,   790,   790,
       0,   790,   790,   790,  1144,     0,  1050,  1051,     0,     0,
       0,  1054,     0,     0,     0,  1152,     0,     0,    10,  1058,
      11,     0,    12,     0,     0,    13,    14,    15,     0,    16,
       0,     0,     0,    17,    18,     0,     0,     0,     0,     0,
      96,    97,    98,    99,     0,  1262,   100,   101,     0,   102,
     103,  1074,     0,   104,     0,     0,     0,     0,     0,     0,
       0,     0,  1089,     0,     0,   724,  1094,     0,  1096,   724,
       0,     0,   790,     0,     0,   790,     0,     0,     0,     0,
      33,     0,     0,   244,     0,     0,     0,   724,     0,    34,
     105,     0,   106,   107,   108,    35,     0,     0,     0,     0,
       0,     0,   244,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,   790,     0,   839,     0,     0,     0,
       0,     3,     0,     0,     4,     0,     5,     0,   244,     0,
     844,     0,   845,     0,   846,     0,     0,     0,     0,   847,
       0,   848,     0,   132,     0,     6,     7,     8,     9,   133,
     134,     0,     0,     0,  1382,     0,     0,     0,     0,  1187,
       0,     0,   258,  1191,     0,  1263,     0,     0,     0,     0,
     579,     0,   259,   260,     0,     0,     0,     0,     0,     0,
       0,  1201,     0,     0,     0,     0,     0,     0,   261,   262,
     263,   264,   265,   266,     0,    37,   580,     0,     0,   581,
       0,  1129,     0,     0,   724,   267,     0,   268,   582,    38,
     135,   136,   137,   138,     0,     0,     0,   109,   139,     0,
       0,  1130,   140,     0,    39,     0,   141,     0,     0,    40,
       0,   110,   142,     0,     0,     0,   111,   112,   113,     0,
       0,     0,   143,     0,     0,     0,   114,     0,   144,     0,
       0,   115,     0,   145,     0,     0,   146,     0,     0,   147,
     148,     0,     0,   149,     0,     0,   150,     0,   151,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
       0,   152,   153,     0,   154,   155,   156,   157,  1287,     0,
       0,     0,     0,   158,   159,   790,     0,   160,   161,   269,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
       0,     0,   270,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   583,     0,     0,     0,   271,     0,     0,     0,
       0,     0,     0,   455,   456,   272,     0,   457,     0,     0,
       0,   273,     0,     0,     0,     0,   274,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   275,     0,     0,   276,
     277,   278,   279,     0,     0,     0,   280,     0,     0,     0,
     281,   282,   184,     0,     0,     0,   185,   186,     0,     3,
       0,     0,     4,     0,     5,   283,     0,     0,   187,     0,
     284,  1131,     0,   188,   189,     0,     0,     0,     0,     0,
       0,   132,     0,     6,     7,     8,     9,   133,   134,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,     4,
     258,     5,     0,     0,     0,     0,     0,     0,   656,     0,
     259,   260,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     7,     8,     9,     0,     0,   261,   262,   263,   264,
     265,   266,     0,     0,   580,     0,     0,   581,     0,  1129,
       0,     0,     0,   267,     0,   268,   582,     0,   135,   136,
     137,   138,     0,     0,     0,     0,   139,     0,     0,  1130,
     140,     0,     0,     0,   141,     0,     0,     0,     0,     0,
     142,     0,     0,  1149,     0,  1150,  1141,     0,     0,  1142,
     143,     0,     0,     0,     0,     0,   144,     0,     0,     0,
       0,   145,     0,     0,   146,     0,  1151,   147,   148,     0,
       0,   149,     0,     0,   150,     0,   151,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,     0,  1013,   152,
     153,     0,   154,   155,   156,   157,  1152,     0,     0,     0,
       0,   158,   159,     0,     0,   160,   161,   269,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,     0,     0,
     270,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     583,     0,     0,     0,   271,     0,     0,     0,     0,     0,
       0,     0,     0,   272,     0,     0,     0,     0,     0,   273,
       0,     0,     0,     0,   274,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   275,     0,     0,   276,   277,   278,
     279,     0,     0,     0,   280,     0,     0,     0,   281,   282,
     184,     0,     0,     3,   185,   186,     4,     0,     5,     0,
       0,     0,     0,   283,     0,     0,   187,     0,   284,  1261,
       0,   188,   189,     0,     0,   132,     0,     6,     7,     8,
       9,   133,   134,     0,     0,     0,     0,     0,   587,   588,
       0,     0,     0,     0,   258,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   259,   260,  1383,     0,     0,   589,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     261,   262,   263,   264,   265,   266,     0,     0,     0,     0,
       0,     0,     0,  1129,     0,     0,     0,   267,     0,   268,
       0,     0,   135,   136,   137,   138,     0,     0,     0,     0,
     139,     0,     0,  1130,   140,   658,     0,     0,   141,     0,
       0,     0,     0,     0,   142,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   143,     0,     0,     0,     0,   590,
     144,     0,     0,     0,     0,   145,     0,     0,   146,     0,
       0,   147,   148,     0,     0,   149,     0,     0,   150,     0,
     151,     0,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   601,   602,   603,     0,     0,   604,   605,   606,
       0,     0,     0,   152,   153,     0,   154,   155,   156,   157,
       0,     0,     0,     0,     0,   158,   159,     0,     0,   160,
     161,   269,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,     0,     0,   270,   692,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   271,     0,
       0,   693,     0,   132,     0,     0,     0,   272,     0,     0,
       0,     0,     0,   273,     0,   587,   588,     0,   274,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   275,     0,
       0,   276,   277,   278,   279,     0,   589,     0,   280,     0,
     694,     0,   281,   282,   184,     0,     0,     0,   185,   186,
       0,     0,     0,     0,   695,     0,     0,   283,     0,     0,
     187,     0,   284,  1381,     0,   188,   189,     0,     0,     0,
     135,   136,   137,   138,     0,     0,     0,     0,   696,     0,
       0,     0,   697,     0,     0,     0,   698,     0,     0,     0,
       0,     0,   699,     0,     0,     0,   700,     0,     0,     0,
       0,     0,   143,     0,     0,     0,   590,     0,   701,     0,
       0,     0,     0,   145,     0,     0,   146,     0,     0,   147,
     148,     0,     0,   149,     0,     0,   150,     0,   151,   591,
     592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     602,   603,     0,     0,   604,   605,   606,     0,   945,     0,
       0,   152,   153,     0,   702,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   693,     0,   132,     0,     0,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
       0,     0,   183,     0,     0,     0,     0,     0,     0,     0,
       0,   703,     0,   694,   704,   705,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   136,   137,   138,     0,     0,   706,
     707,   696,     0,     0,     0,   697,     0,     0,     0,   698,
       0,     0,   184,     0,     0,   699,   185,   186,     0,   700,
       0,     0,     0,     0,     0,   143,   708,   709,     0,     0,
       0,   701,     0,   188,     0,     0,   145,     0,     0,   146,
       0,     0,   147,   148,     0,     0,   149,     0,     0,   150,
       0,   151,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   962,     0,     0,   152,   153,     0,   702,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   693,     0,   132,
       0,     0,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,     0,     0,   183,     0,     0,     0,     0,
       0,     0,     0,     0,   703,     0,   694,   704,   705,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   135,   136,   137,   138,
       0,     0,   706,   707,   696,     0,     0,     0,   697,     0,
       0,     0,   698,     0,     0,   184,     0,     0,   699,   185,
     186,     0,   700,     0,     0,     0,     0,     0,   143,   708,
     709,     0,     0,     0,   701,     0,   188,     0,     0,   145,
       0,     0,   146,     0,     0,   147,   148,     0,     0,   149,
       0,     0,   150,     0,   151,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   152,   153,     0,
     702,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,     0,     0,   183,     0,
     767,   768,   769,   770,   771,   772,     0,   703,     0,     0,
     704,   705,   693,     0,   754,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   706,   707,     0,     0,     0,
       0,   694,     0,     0,     0,     0,     0,     0,   184,     0,
       0,     0,   185,   186,     0,     0,     0,     0,     0,     0,
       0,     0,   708,   709,     0,     0,   693,     0,   754,   188,
       0,   135,   136,   137,   138,     0,     0,     0,     0,   773,
       0,     0,     0,   774,     0,     0,     0,   775,     0,     0,
       0,     0,     0,   776,     0,     0,     0,   700,     0,     0,
       0,     0,     0,   777,     0,   694,     0,     0,     0,   778,
       0,     0,     0,     0,   779,     0,     0,   780,     0,     0,
     781,   782,     0,     0,   783,     0,     0,   784,     0,   785,
       0,     0,     0,     0,     0,   135,   136,   137,   138,     0,
       0,     0,     0,   773,     0,     0,     0,   774,     0,     0,
       0,   775,   786,   787,     0,     0,     0,   776,     0,     0,
       0,   700,     0,     0,     0,     0,     0,   777,     0,     0,
       0,     0,     0,   778,     0,     0,     0,     0,   779,     0,
       0,   780,     0,     0,   781,   782,     0,     0,   783,     0,
       0,   784,     0,   785,     0,     0,     0,     0,     0,     0,
       0,     0,   703,     0,     0,   704,   705,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   786,   787,   693,     0,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     706,   707,     0,   788,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   694,     0,     0,
       0,     0,     0,     0,     0,     0,   703,   708,   709,   704,
     705,   284,     0,     0,   188,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,   137,
     138,     0,     0,     0,     0,   696,     0,     0,     0,   697,
       0,     0,     0,   698,   706,   707,     0,   788,     0,   699,
       0,     0,     0,   700,     0,     0,     0,     0,     0,   143,
       0,     0,     0,     0,     0,   701,     0,     0,     0,     0,
     145,   708,   709,   146,     0,   284,   147,   148,   188,   991,
     149,     0,     0,   150,     0,   151,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   152,   153,
       0,   702,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   693,     0,   754,     0,     0,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,     0,     0,   183,
       0,     0,     0,     0,     0,     0,     0,     0,   703,     0,
     694,   704,   705,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   136,   137,   138,     0,     0,   706,   707,   773,     0,
       0,     0,   774,     0,     0,     0,   775,     0,     0,   184,
       0,     0,   776,   185,   186,   693,   700,   754,     0,     0,
       0,     0,   777,   708,   709,     0,     0,     0,   778,     0,
     188,     0,     0,   779,     0,     0,   780,     0,     0,   781,
     782,     0,     0,   783,     0,     0,   784,     0,   785,     0,
       0,     0,     0,     0,   694,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   786,   787,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   135,   136,   137,   138,     0,     0,
       0,     0,   773,     0,     0,     0,   774,     0,     0,     0,
     775,     0,     0,     0,     0,     0,   776,     0,     0,     0,
     700,     0,     0,     0,     0,     0,   777,     0,     0,     0,
       0,   703,   778,     0,   704,   705,     0,   779,     0,     0,
     780,     0,     0,   781,   782,     0,     0,   783,     0,     0,
     784,     0,   785,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   706,
     707,     0,   788,     0,     0,   786,   787,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   708,   709,     0,     0,
     284,     0,     0,   188,     0,   132,     0,     0,     0,     0,
       0,   133,   134,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   258,   703,     0,     0,   704,   705,
       0,     0,     0,     0,   259,   260,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     261,   262,   263,   264,   265,   266,     0,     0,     0,     0,
       0,     0,     0,   706,   707,     0,   788,   267,     0,   268,
       0,     0,   135,   136,   137,   138,     0,     0,     0,     0,
     139,     0,     0,     0,   140,     0,     0,     0,   141,     0,
     708,   709,     0,     0,   142,     0,     0,   188,     0,     0,
       0,     0,     0,     0,   143,     0,     0,     0,     0,     0,
     144,     0,     0,     0,     0,   145,     0,     0,   146,     0,
       0,   147,   148,     0,     0,   149,     0,     0,   150,     0,
     151,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,   153,     0,   154,   155,   156,   157,
       0,     0,     0,     0,     0,   158,   159,     0,     0,   160,
     161,   269,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,     0,     0,   270,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   271,     0,
       0,     0,   132,     0,     0,     0,     0,   272,   133,   134,
       0,     0,     0,   273,     0,     0,     0,     0,   274,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   275,     0,
       0,   276,   277,   278,   279,     0,     0,     0,   280,     0,
       0,     0,   281,   282,   184,     0,     0,     0,   185,   186,
       0,     0,     0,     0,     0,     0,     0,   283,     0,     0,
     187,     0,   284,     0,     0,   188,   189,     0,     0,   135,
     136,   137,   138,     0,     0,     0,     0,   139,     0,     0,
       0,   140,     0,     0,     0,   141,     0,     0,     0,     0,
       0,   142,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,     0,     0,   144,     0,     0,
       0,     0,   145,     0,     0,   146,     0,     0,   147,   148,
       0,     0,   149,     0,     0,   150,     0,   151,     0,   132,
       0,     0,     0,     0,     0,   133,   134,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     152,   153,     0,   154,   155,   156,   157,     0,     0,     0,
       0,     0,   158,   159,     0,     0,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
       0,   183,     0,     0,     0,     0,   135,   136,   137,   138,
       0,     0,     0,     0,   139,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,     0,     0,     0,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143,     0,
       0,     0,     0,     0,   144,     0,     0,     0,     0,   145,
       0,     0,   146,     0,     0,   147,   148,     0,     0,   149,
       0,   184,   150,     0,   151,   185,   186,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   187,     0,   284,
       0,     0,   188,   189,     0,     0,     0,   152,   153,     0,
     154,   155,   156,   157,     0,     0,     0,     0,   132,   158,
     159,     0,     0,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,     0,     0,   183,     0,
       0,     0,     0,     0,     0,   694,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,   137,   138,     0,
       0,     0,     0,   696,     0,     0,     0,   697,     0,     0,
       0,   698,     0,     0,     0,     0,     0,   699,   184,     0,
       0,   700,   185,   186,     0,     0,     0,   143,     0,     0,
       0,     0,     0,   701,   187,     0,     0,     0,   145,   188,
     189,   146,     0,     0,   147,   148,     0,     0,   149,     0,
       0,   150,     0,   151,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   152,   153,     0,   702,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   754,     0,     0,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,     0,     0,   183,     0,     0,
       0,     0,     0,     0,     0,     0,   703,     0,   694,   704,
     705,     0,     0,     0,     0,     0,   261,   262,   263,   264,
     265,   266,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   135,   136,
     137,   138,   754,     0,   706,   707,   773,     0,     0,     0,
     774,     0,     0,     0,   775,     0,     0,   184,     0,     0,
     776,   185,   186,     0,   700,     0,     0,     0,     0,     0,
     777,   708,   709,     0,     0,     0,   778,     0,   188,   694,
       0,   779,     0,     0,   780,     0,     0,   781,   782,     0,
       0,   783,     0,     0,   784,     0,   785,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   754,     0,     0,   135,
     136,   137,   138,     0,     0,     0,     0,   773,     0,   786,
     787,   774,     0,     0,     0,   775,     0,     0,     0,     0,
       0,   776,     0,     0,     0,   700,     0,     0,     0,     0,
       0,   777,     0,   694,     0,     0,     0,   778,     0,     0,
       0,     0,   779,     0,     0,   780,     0,     0,   781,   782,
       0,     0,   783,     0,     0,   784,     0,   785,     0,   703,
       0,     0,   704,   705,   136,   137,   138,     0,     0,     0,
       0,   773,     0,     0,     0,   774,     0,     0,     0,   775,
     786,   787,     0,     0,     0,   776,     0,     0,     0,   700,
       0,     0,     0,     0,     0,     0,     0,   706,   707,     0,
     788,   778,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   708,   709,     0,     0,     0,     0,
     703,   188,     0,   704,   705,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   706,   707,
       0,   788,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     3,     0,     0,     4,     0,
       5,     0,     0,     0,   703,   708,   709,   704,   705,     0,
       0,     0,   188,     0,     0,     0,     0,     0,     0,     6,
       7,     8,     9,     0,     0,     0,     0,     0,     0,    10,
       0,    11,     0,    12,     0,     0,    13,    14,    15,     0,
      16,     0,   706,   707,    17,    18,    19,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   188,     0,     0,     0,
       0,     0,     0,     0,     0,  -245,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    39,     0,     0,     0,     0,
      40
};

static const yytype_int16 yycheck[] =
{
       1,   287,     3,    29,    62,   185,   305,     1,   354,   353,
      62,   356,    31,   325,   352,   355,    29,   189,    50,   672,
     672,   325,     5,  1003,    50,   910,   372,    59,   915,   916,
    1004,   335,   336,    59,   921,     7,  1005,    23,   384,    29,
      50,  1000,  1006,    44,   969,    29,    23,   325,   967,    59,
      35,    52,     7,  1167,     7,    56,    74,   335,   336,    48,
      50,  1102,    84,    90,    14,    15,    50,  1151,    47,    59,
      91,    91,    29,   101,    97,    59,    99,   100,  1030,  1031,
     103,   104,   917,    78,   107,   108,     4,   325,   111,   112,
     113,   978,    91,    50,   948,   118,   119,   335,   336,    47,
      23,    92,    59,   126,    29,    91,    92,    93,    48,  1060,
      20,    22,  1222,  1223,  1043,     1,   115,   116,     4,    20,
       6,    71,    72,    73,     8,    50,  1123,  1124,   982,   983,
     162,   947,    29,  1062,    59,    85,    86,    87,   954,    25,
      26,    27,    28,    91,    94,    39,    40,    12,   607,     8,
     126,   101,   102,    50,   122,    91,   106,   220,  1189,   185,
      44,   607,    59,   189,   675,   133,   194,   195,    91,    92,
      93,   234,   683,    91,   124,   125,   687,    39,   128,    90,
     148,    91,    76,    77,    78,    44,     7,     8,     9,  1299,
      91,   190,   325,    74,     8,   185,    90,    91,    92,   189,
     659,   185,   335,   336,    90,   189,  1165,   228,   229,   229,
      24,   210,   231,   659,  1049,    80,   110,   244,   237,   114,
     114,   115,  1219,   117,   112,    46,   120,    48,   185,  1313,
      44,   131,   189,    39,   210,   211,   131,   269,   126,    60,
     128,   141,   142,    64,   143,   263,   264,   265,  1279,   148,
    1364,   124,  1293,     1,  1285,   287,     4,  1186,     6,  1184,
     185,   287,    99,   100,   189,   138,   103,   104,   290,   124,
     107,   108,   127,   325,   111,   112,   113,    25,    26,    27,
      28,   118,   119,   335,   336,  1204,   281,    37,   185,   126,
     258,    43,   189,   282,   283,   284,   354,   287,    91,   325,
     279,   280,   354,   287,   290,   290,  1193,   293,   291,   335,
     336,   132,    47,   290,   372,  1267,    29,   141,   350,   291,
     372,  1208,   210,   211,   350,    74,   384,    74,     1,   361,
     287,     4,   384,     6,   290,   361,   291,    50,   291,    88,
     350,  1292,   282,   283,   284,   101,    59,    47,    47,   243,
    1330,   361,    25,    26,    27,    28,    91,  1331,   244,   245,
     350,   227,   287,  1332,    67,   112,   350,   188,   672,  1333,
     293,   361,     7,   220,   397,     1,   242,   361,     4,   220,
       6,   128,   263,   264,   265,    20,   897,    22,   144,   145,
     287,    91,    91,   350,   672,    98,     4,  1282,     6,    25,
      26,    27,    28,  1362,   361,   291,    32,  1060,    34,   112,
    1063,  1063,   236,   237,   238,   239,   240,   827,   114,    50,
      51,   263,   289,   244,   723,   350,   836,    91,   101,  1138,
    1139,   273,   121,   289,     1,   131,   361,     4,   290,     6,
    1149,   293,  1329,   264,   265,   148,   396,   268,   220,  1102,
    1102,   115,   116,   350,   766,   144,   145,   101,    25,    26,
      27,    28,   766,   357,   361,    32,    97,    34,   114,    84,
     114,   651,   185,   423,   290,   106,   189,   121,   124,    35,
     228,   112,   376,   275,   173,   131,   278,   131,   766,  1376,
      31,   137,   138,   137,   197,   807,     1,   128,   179,     4,
     117,     6,   117,   807,   121,   179,     1,   227,   402,     4,
       1,     6,     4,     4,     6,     6,     8,    99,   100,   274,
      25,    26,    27,    28,   244,   245,   190,   144,   145,   807,
      25,    26,    27,    28,    25,    26,    27,    28,   283,   672,
     213,   362,     1,   291,   365,     4,   210,     6,   369,   228,
     165,   166,   167,   168,   169,   170,   377,   121,   141,    36,
     397,    38,   226,    40,    41,   242,    25,    26,    27,    28,
      90,    48,    49,    78,   287,    80,    81,   241,    90,    84,
     144,   145,   246,   147,    35,    36,    77,    78,    79,    80,
      81,     5,   764,    84,     8,   227,   101,   180,   181,   182,
      52,    53,     1,    80,   425,     4,   101,     6,   190,   191,
     101,    90,   194,     0,    20,   634,    22,     4,   291,     6,
     672,   174,   282,   283,   284,   651,    25,    26,    27,    28,
     183,   184,    86,   766,   187,   188,   141,   350,    37,    74,
    1293,  1293,     4,    42,   281,    44,   672,    46,   361,    35,
     141,    37,     4,    39,     6,     7,    42,    43,    44,   257,
      46,   651,   228,   229,   963,   291,    35,   651,    35,   947,
     948,   949,   950,   951,   807,   953,   954,    99,   100,   991,
     958,   959,    17,    50,    51,   244,   245,   991,    68,    69,
      70,    71,    72,    73,   651,    18,     1,    75,    76,     4,
      78,     6,   292,   981,   982,   983,   984,   985,   986,   987,
      42,   989,   990,   991,   766,    99,   100,   101,   213,   899,
      25,    26,    27,    28,   291,    42,   651,    32,   290,    34,
      97,    15,    16,   759,   760,   761,   762,   763,   764,   106,
     766,   290,   141,   981,   290,   112,   759,   760,    35,   987,
     290,   989,   990,    91,   651,   807,    94,    95,    96,  1063,
     290,   128,  1048,    50,    51,   267,   268,   269,    47,   759,
     760,   761,   762,   763,   764,   759,   760,   761,   762,   763,
     764,   807,  1060,   242,    35,  1063,   291,   967,   226,   969,
      91,    92,    93,   231,   232,  1094,   291,  1096,  1102,    20,
     291,    22,   759,   760,   761,   762,   763,   764,   246,   810,
      97,     7,   813,   212,  1100,   948,   263,   264,   265,   106,
     244,   245,  1060,     8,  1102,   112,   212,   226,    35,    15,
      16,   296,   291,   296,   759,   760,   761,   762,   763,   764,
     226,   128,   241,    50,    51,    15,    16,   246,   981,   982,
     983,   984,   985,   986,   987,   241,   989,   990,   991,   101,
     246,   103,   759,   760,   761,   762,   763,   764,     4,     5,
    1214,   274,  1217,   899,  1212,  1215,   268,   269,    35,   121,
      37,   123,   124,   125,   126,    42,    43,    44,  1234,    46,
      97,    35,   291,     1,    68,    69,     4,   274,     6,   106,
      82,    83,    90,   955,   295,   112,    50,    51,  1254,   899,
     107,   108,   109,   110,   111,   899,    23,    25,    26,    27,
      28,   128,   948,    91,    92,   958,   959,  1060,    90,    90,
    1063,    42,    42,   754,    90,   756,    42,    74,   651,   991,
      90,   967,   899,   969,   251,   252,   253,   254,   255,    90,
      90,    90,    90,    97,    17,   981,   982,   983,   984,   985,
     986,   987,   106,   989,   990,   991,   998,    11,   112,  1102,
      18,   292,   998,     5,   899,     5,     7,   967,   101,   969,
     103,   104,   105,   967,   128,   969,   291,     7,     7,  1293,
       7,     7,     7,   101,   290,     7,   997,  1283,   999,  1000,
    1001,   292,   899,   997,  1184,   999,  1000,  1001,   998,    17,
     967,  1063,   969,    18,   998,  1293,  1048,     8,   290,   290,
     290,   290,  1048,    67,  1204,   290,    70,   290,    90,    90,
      90,    90,   101,    90,  1060,    90,    90,  1063,    90,    83,
      84,   998,   967,   112,   969,   114,   759,   760,   761,   762,
     763,   764,    90,   301,    98,   212,   275,   126,  1048,   128,
     229,    90,   131,   311,  1048,     8,   103,    90,  1100,   226,
     967,    42,   969,   998,  1100,    33,  1102,   325,   127,   123,
      90,   118,    60,    90,   241,     5,   130,   335,   336,   246,
     101,  1048,   101,    90,   131,   101,    90,   103,   101,   290,
     137,   998,   297,     7,   297,   213,    90,    90,    33,   178,
    1100,    91,   247,   290,     7,   121,  1100,   123,   124,    91,
     126,    91,    91,  1048,   295,    91,   220,  1128,   134,   135,
      35,  1163,    91,  1134,  1135,  1136,   289,  1163,    90,    90,
     289,   210,   211,  1100,    91,    50,    51,  1148,   185,   186,
      90,  1048,   243,    90,     5,  1156,   977,   289,  1184,    32,
    1293,  1162,   291,  1164,  1165,  1166,   291,   129,  1162,   290,
    1164,  1165,  1166,  1163,  1175,  1100,  1234,    92,  1204,  1163,
      90,  1175,  1234,   291,    91,     1,   899,   291,     4,   290,
       6,   290,    97,   290,  1184,   290,  1254,   290,   290,    91,
    1184,   106,  1254,  1100,   290,   290,  1163,   112,   120,    25,
      26,    27,    28,   291,  1204,    33,    90,    19,   129,    91,
    1204,    37,  1002,   128,   351,  1152,    42,  1184,    44,  1309,
      46,  1232,  1233,  1376,  1307,  1399,    82,   349,  1163,  1118,
      84,   286,  1208,   680,  1245,   688,  1269,  1204,  1197,  1250,
     274,  1283,  1253,  1056,   967,  1256,   969,  1283,   663,  1184,
      35,    35,  1188,    37,  1265,   949,  1163,  1293,    42,  1270,
      44,  1265,    99,   100,    48,    50,    51,   953,   950,  1204,
     951,   961,   750,   966,   258,   998,   113,  1184,   115,   116,
     117,   757,   852,  1283,   761,  1116,  1117,  1118,  1119,  1283,
     762,   185,   763,   130,   131,   132,  1365,  1204,   921,   336,
    1367,    85,   358,    87,   109,  1366,  1317,  1318,   360,   359,
    1321,   325,    97,    99,   100,   141,  1283,   984,  1360,   985,
     269,   106,   986,   548,  1360,  1048,   112,   112,   270,   270,
    1341,  1342,  1343,  1344,   120,    -1,  1347,    -1,    -1,    -1,
      -1,    -1,   128,   128,    -1,    -1,    -1,    -1,  1283,    -1,
    1361,  1362,  1363,    -1,  1365,  1366,  1367,  1361,  1362,  1363,
    1360,  1365,  1366,  1367,    -1,    -1,  1360,    -1,    -1,  1380,
    1381,  1382,  1383,  1384,  1385,  1386,  1283,  1100,    -1,  1390,
      -1,  1385,    -1,  1394,    -1,    -1,   212,    -1,    -1,    -1,
      -1,    -1,    -1,  1360,    -1,    -1,  1407,    -1,    -1,    -1,
     226,    -1,    -1,   661,   662,    -1,   664,    -1,   666,   667,
      -1,    -1,    -1,    -1,   672,   241,    -1,    -1,    -1,    -1,
     246,    -1,    -1,    -1,    -1,  1360,    -1,   213,   214,   215,
     216,    -1,    -1,    -1,   692,    -1,    -1,   695,    -1,    -1,
    1163,    -1,   228,   229,   230,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1360,    -1,    -1,    -1,     1,    -1,    -1,
      -1,  1184,    -1,    -1,    -1,   291,    10,    11,    12,    -1,
      -1,    -1,    16,    -1,    -1,    19,    -1,    -1,    -1,    -1,
      -1,  1204,    -1,    -1,    -1,     1,   744,    -1,     4,   747,
       6,    -1,    -1,    -1,    38,    39,    40,   661,   662,    -1,
     664,    -1,   666,   667,    -1,    -1,    -1,    -1,   766,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    70,    -1,   692,    -1,
      74,   695,    76,    77,    78,    -1,    80,    -1,    82,    83,
      84,    85,    -1,    -1,    88,    -1,    90,    91,    92,   807,
     808,   809,    96,    -1,    98,    -1,    -1,    -1,    -1,    -1,
    1283,    77,    78,    79,    80,    81,   110,    -1,    84,    -1,
     114,   115,   121,   117,    -1,   124,   120,    -1,   122,   123,
     744,    -1,    -1,   747,    -1,   101,   130,    -1,   137,    -1,
      -1,    -1,   141,    -1,     1,   144,   145,     4,    -1,     6,
     149,   150,   151,   152,   153,     1,    -1,    -1,     4,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,
      27,    28,    -1,    -1,    -1,   141,    -1,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    -1,   894,  1360,    -1,    -1,
      -1,    -1,   900,   901,   808,   809,    -1,   905,    -1,    -1,
      -1,    -1,    -1,   151,    -1,   913,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,    -1,    -1,    -1,
      77,    78,    79,    80,    81,    -1,    -1,    84,    -1,    -1,
      -1,    -1,    78,    -1,    80,    81,    -1,   945,    84,   947,
     948,   949,   950,   951,   101,   953,   954,   955,   956,   243,
     958,   959,   960,    -1,   962,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   981,   982,   983,   984,   985,   986,   987,
      -1,   989,   990,   991,   141,    -1,   900,   901,    -1,    -1,
      -1,   905,    -1,    -1,    -1,   141,    -1,    -1,    35,   913,
      37,    -1,    39,    -1,    -1,    42,    43,    44,    -1,    46,
      -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    -1,   291,    41,    42,    -1,    44,
      45,   945,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   956,    -1,    -1,  1053,   960,    -1,   962,  1057,
      -1,    -1,  1060,    -1,    -1,  1063,    -1,    -1,    -1,    -1,
      97,    -1,    -1,   357,    -1,    -1,    -1,  1075,    -1,   106,
      85,    -1,    87,    88,    89,   112,    -1,    -1,    -1,    -1,
      -1,    -1,   376,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   128,    -1,    -1,  1102,    -1,   390,    -1,    -1,    -1,
      -1,     1,    -1,    -1,     4,    -1,     6,    -1,   402,    -1,
     404,    -1,   406,    -1,   408,    -1,    -1,    -1,    -1,   413,
      -1,   415,    -1,    23,    -1,    25,    26,    27,    28,    29,
      30,    -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,  1053,
      -1,    -1,    42,  1057,    -1,   291,    -1,    -1,    -1,    -1,
      91,    -1,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1075,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    -1,   212,   117,    -1,    -1,   120,
      -1,    81,    -1,    -1,  1192,    85,    -1,    87,   129,   226,
      90,    91,    92,    93,    -1,    -1,    -1,   212,    98,    -1,
      -1,   101,   102,    -1,   241,    -1,   106,    -1,    -1,   246,
      -1,   226,   112,    -1,    -1,    -1,   231,   232,   233,    -1,
      -1,    -1,   122,    -1,    -1,    -1,   241,    -1,   128,    -1,
      -1,   246,    -1,   133,    -1,    -1,   136,    -1,    -1,   139,
     140,    -1,    -1,   143,    -1,    -1,   146,    -1,   148,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,    -1,
      -1,   171,   172,    -1,   174,   175,   176,   177,  1192,    -1,
      -1,    -1,    -1,   183,   184,  1293,    -1,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
      -1,    -1,   212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   263,    -1,    -1,    -1,   226,    -1,    -1,    -1,
      -1,    -1,    -1,    99,   100,   235,    -1,   103,    -1,    -1,
      -1,   241,    -1,    -1,    -1,    -1,   246,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   256,    -1,    -1,   259,
     260,   261,   262,    -1,    -1,    -1,   266,    -1,    -1,    -1,
     270,   271,   272,    -1,    -1,    -1,   276,   277,    -1,     1,
      -1,    -1,     4,    -1,     6,   285,    -1,    -1,   288,    -1,
     290,   291,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,     4,
      42,     6,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    28,    -1,    -1,    68,    69,    70,    71,
      72,    73,    -1,    -1,   117,    -1,    -1,   120,    -1,    81,
      -1,    -1,    -1,    85,    -1,    87,   129,    -1,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    98,    -1,    -1,   101,
     102,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,
     112,    -1,    -1,    78,    -1,    80,    81,    -1,    -1,    84,
     122,    -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,    -1,
      -1,   133,    -1,    -1,   136,    -1,   101,   139,   140,    -1,
      -1,   143,    -1,    -1,   146,    -1,   148,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,    -1,   842,   171,
     172,    -1,   174,   175,   176,   177,   141,    -1,    -1,    -1,
      -1,   183,   184,    -1,    -1,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,    -1,    -1,
     212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     263,    -1,    -1,    -1,   226,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   235,    -1,    -1,    -1,    -1,    -1,   241,
      -1,    -1,    -1,    -1,   246,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   256,    -1,    -1,   259,   260,   261,
     262,    -1,    -1,    -1,   266,    -1,    -1,    -1,   270,   271,
     272,    -1,    -1,     1,   276,   277,     4,    -1,     6,    -1,
      -1,    -1,    -1,   285,    -1,    -1,   288,    -1,   290,   291,
      -1,   293,   294,    -1,    -1,    23,    -1,    25,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    -1,    99,   100,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    53,   291,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    -1,    87,
      -1,    -1,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
      98,    -1,    -1,   101,   102,   166,    -1,    -1,   106,    -1,
      -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,    -1,   190,
     128,    -1,    -1,    -1,    -1,   133,    -1,    -1,   136,    -1,
      -1,   139,   140,    -1,    -1,   143,    -1,    -1,   146,    -1,
     148,    -1,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,    -1,    -1,   228,   229,   230,
      -1,    -1,    -1,   171,   172,    -1,   174,   175,   176,   177,
      -1,    -1,    -1,    -1,    -1,   183,   184,    -1,    -1,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,    -1,   212,     5,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,    -1,
      -1,    21,    -1,    23,    -1,    -1,    -1,   235,    -1,    -1,
      -1,    -1,    -1,   241,    -1,    99,   100,    -1,   246,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   256,    -1,
      -1,   259,   260,   261,   262,    -1,   120,    -1,   266,    -1,
      60,    -1,   270,   271,   272,    -1,    -1,    -1,   276,   277,
      -1,    -1,    -1,    -1,    74,    -1,    -1,   285,    -1,    -1,
     288,    -1,   290,   291,    -1,   293,   294,    -1,    -1,    -1,
      90,    91,    92,    93,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,   102,    -1,    -1,    -1,   106,    -1,    -1,    -1,
      -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,   190,    -1,   128,    -1,
      -1,    -1,    -1,   133,    -1,    -1,   136,    -1,    -1,   139,
     140,    -1,    -1,   143,    -1,    -1,   146,    -1,   148,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,    -1,    -1,   228,   229,   230,    -1,     5,    -1,
      -1,   171,   172,    -1,   174,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    -1,    -1,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
      -1,    -1,   212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   221,    -1,    60,   224,   225,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    91,    92,    93,    -1,    -1,   259,
     260,    98,    -1,    -1,    -1,   102,    -1,    -1,    -1,   106,
      -1,    -1,   272,    -1,    -1,   112,   276,   277,    -1,   116,
      -1,    -1,    -1,    -1,    -1,   122,   286,   287,    -1,    -1,
      -1,   128,    -1,   293,    -1,    -1,   133,    -1,    -1,   136,
      -1,    -1,   139,   140,    -1,    -1,   143,    -1,    -1,   146,
      -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,   171,   172,    -1,   174,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      -1,    -1,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,    -1,    -1,   212,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   221,    -1,    60,   224,   225,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    91,    92,    93,
      -1,    -1,   259,   260,    98,    -1,    -1,    -1,   102,    -1,
      -1,    -1,   106,    -1,    -1,   272,    -1,    -1,   112,   276,
     277,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,   286,
     287,    -1,    -1,    -1,   128,    -1,   293,    -1,    -1,   133,
      -1,    -1,   136,    -1,    -1,   139,   140,    -1,    -1,   143,
      -1,    -1,   146,    -1,   148,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   171,   172,    -1,
     174,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,    -1,    -1,   212,    -1,
       9,    10,    11,    12,    13,    14,    -1,   221,    -1,    -1,
     224,   225,    21,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   259,   260,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    -1,   272,    -1,
      -1,    -1,   276,   277,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   286,   287,    -1,    -1,    21,    -1,    23,   293,
      -1,    90,    91,    92,    93,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,   102,    -1,    -1,    -1,   106,    -1,    -1,
      -1,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    60,    -1,    -1,    -1,   128,
      -1,    -1,    -1,    -1,   133,    -1,    -1,   136,    -1,    -1,
     139,   140,    -1,    -1,   143,    -1,    -1,   146,    -1,   148,
      -1,    -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,   102,    -1,    -1,
      -1,   106,   171,   172,    -1,    -1,    -1,   112,    -1,    -1,
      -1,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,
      -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,   133,    -1,
      -1,   136,    -1,    -1,   139,   140,    -1,    -1,   143,    -1,
      -1,   146,    -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   221,    -1,    -1,   224,   225,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   171,   172,    21,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     259,   260,    -1,   262,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   221,   286,   287,   224,
     225,   290,    -1,    -1,   293,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,    92,
      93,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,   102,
      -1,    -1,    -1,   106,   259,   260,    -1,   262,    -1,   112,
      -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,
      -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,
     133,   286,   287,   136,    -1,   290,   139,   140,   293,   294,
     143,    -1,    -1,   146,    -1,   148,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   171,   172,
      -1,   174,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    -1,    -1,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,    -1,    -1,   212,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   221,    -1,
      60,   224,   225,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    91,    92,    93,    -1,    -1,   259,   260,    98,    -1,
      -1,    -1,   102,    -1,    -1,    -1,   106,    -1,    -1,   272,
      -1,    -1,   112,   276,   277,    21,   116,    23,    -1,    -1,
      -1,    -1,   122,   286,   287,    -1,    -1,    -1,   128,    -1,
     293,    -1,    -1,   133,    -1,    -1,   136,    -1,    -1,   139,
     140,    -1,    -1,   143,    -1,    -1,   146,    -1,   148,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   171,   172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,   102,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,
     116,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,
      -1,   221,   128,    -1,   224,   225,    -1,   133,    -1,    -1,
     136,    -1,    -1,   139,   140,    -1,    -1,   143,    -1,    -1,
     146,    -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   259,
     260,    -1,   262,    -1,    -1,   171,   172,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   286,   287,    -1,    -1,
     290,    -1,    -1,   293,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,   221,    -1,    -1,   224,   225,
      -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   259,   260,    -1,   262,    85,    -1,    87,
      -1,    -1,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,   102,    -1,    -1,    -1,   106,    -1,
     286,   287,    -1,    -1,   112,    -1,    -1,   293,    -1,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,
     128,    -1,    -1,    -1,    -1,   133,    -1,    -1,   136,    -1,
      -1,   139,   140,    -1,    -1,   143,    -1,    -1,   146,    -1,
     148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   171,   172,    -1,   174,   175,   176,   177,
      -1,    -1,    -1,    -1,    -1,   183,   184,    -1,    -1,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,    -1,   212,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,   235,    29,    30,
      -1,    -1,    -1,   241,    -1,    -1,    -1,    -1,   246,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   256,    -1,
      -1,   259,   260,   261,   262,    -1,    -1,    -1,   266,    -1,
      -1,    -1,   270,   271,   272,    -1,    -1,    -1,   276,   277,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   285,    -1,    -1,
     288,    -1,   290,    -1,    -1,   293,   294,    -1,    -1,    90,
      91,    92,    93,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,   102,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,
      -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,
      -1,    -1,   133,    -1,    -1,   136,    -1,    -1,   139,   140,
      -1,    -1,   143,    -1,    -1,   146,    -1,   148,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     171,   172,    -1,   174,   175,   176,   177,    -1,    -1,    -1,
      -1,    -1,   183,   184,    -1,    -1,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,    -1,
      -1,   212,    -1,    -1,    -1,    -1,    90,    91,    92,    93,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,   102,    -1,
      -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,    -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,   133,
      -1,    -1,   136,    -1,    -1,   139,   140,    -1,    -1,   143,
      -1,   272,   146,    -1,   148,   276,   277,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   288,    -1,   290,
      -1,    -1,   293,   294,    -1,    -1,    -1,   171,   172,    -1,
     174,   175,   176,   177,    -1,    -1,    -1,    -1,    23,   183,
     184,    -1,    -1,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,    -1,    -1,   212,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,   102,    -1,    -1,
      -1,   106,    -1,    -1,    -1,    -1,    -1,   112,   272,    -1,
      -1,   116,   276,   277,    -1,    -1,    -1,   122,    -1,    -1,
      -1,    -1,    -1,   128,   288,    -1,    -1,    -1,   133,   293,
     294,   136,    -1,    -1,   139,   140,    -1,    -1,   143,    -1,
      -1,   146,    -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   171,   172,    -1,   174,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,    -1,    -1,   212,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   221,    -1,    60,   224,
     225,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    23,    -1,   259,   260,    98,    -1,    -1,    -1,
     102,    -1,    -1,    -1,   106,    -1,    -1,   272,    -1,    -1,
     112,   276,   277,    -1,   116,    -1,    -1,    -1,    -1,    -1,
     122,   286,   287,    -1,    -1,    -1,   128,    -1,   293,    60,
      -1,   133,    -1,    -1,   136,    -1,    -1,   139,   140,    -1,
      -1,   143,    -1,    -1,   146,    -1,   148,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    90,
      91,    92,    93,    -1,    -1,    -1,    -1,    98,    -1,   171,
     172,   102,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,
      -1,   112,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    60,    -1,    -1,    -1,   128,    -1,    -1,
      -1,    -1,   133,    -1,    -1,   136,    -1,    -1,   139,   140,
      -1,    -1,   143,    -1,    -1,   146,    -1,   148,    -1,   221,
      -1,    -1,   224,   225,    91,    92,    93,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,   102,    -1,    -1,    -1,   106,
     171,   172,    -1,    -1,    -1,   112,    -1,    -1,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   259,   260,    -1,
     262,   128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   286,   287,    -1,    -1,    -1,    -1,
     221,   293,    -1,   224,   225,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   259,   260,
      -1,   262,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     0,     1,    -1,    -1,     4,    -1,
       6,    -1,    -1,    -1,   221,   286,   287,   224,   225,    -1,
      -1,    -1,   293,    -1,    -1,    -1,    -1,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    37,    -1,    39,    -1,    -1,    42,    43,    44,    -1,
      46,    -1,   259,   260,    50,    51,    52,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   293,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   241,    -1,    -1,    -1,    -1,
     246
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   299,     0,     1,     4,     6,    25,    26,    27,    28,
      35,    37,    39,    42,    43,    44,    46,    50,    51,    52,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    97,   106,   112,   128,   212,   226,   241,
     246,   300,   302,   303,   304,   305,   358,   359,   360,   362,
     376,   300,    92,    91,   355,   355,   355,   360,   362,   376,
     360,   365,   365,   365,   360,   368,   305,    39,   306,    35,
      37,    42,    43,    44,    46,   212,   226,   241,   246,   307,
      39,   308,    35,    37,    39,    42,    43,    44,    46,   212,
     226,   241,   246,   309,    43,   310,    35,    36,    37,    38,
      41,    42,    44,    45,    48,    85,    87,    88,    89,   212,
     226,   231,   232,   233,   241,   246,   311,   226,   231,   232,
     246,   312,    35,    37,    42,    44,    48,    85,    87,   313,
      37,   314,    23,    29,    30,    90,    91,    92,    93,    98,
     102,   106,   112,   122,   128,   133,   136,   139,   140,   143,
     146,   148,   171,   172,   174,   175,   176,   177,   183,   184,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   212,   272,   276,   277,   288,   293,   294,
     322,   356,   458,   459,   460,   461,   462,   514,   517,   519,
     523,   524,   526,   528,   538,   539,   541,   543,   545,   547,
     549,   551,   553,   555,   557,   559,   561,   563,   565,   569,
     571,   573,   574,   576,   578,   580,   582,   584,   586,   588,
     590,    48,   282,   283,   284,   315,   321,    48,   316,   321,
      91,   317,   318,   220,   360,   370,   370,   370,     0,   300,
     355,   355,    47,   279,   280,   373,   374,   375,    42,    52,
      53,    68,    69,    70,    71,    72,    73,    85,    87,   189,
     212,   226,   235,   241,   246,   256,   259,   260,   261,   262,
     266,   270,   271,   285,   290,   380,   381,   382,   383,   384,
     385,   389,   390,   391,   394,   395,   402,   406,   410,   411,
     413,   414,   430,   431,   433,   434,   436,   438,   441,   442,
     449,   450,   451,   452,   453,   456,   457,   461,   466,   467,
     468,   469,   470,   471,   475,   476,   477,   499,   513,   517,
     518,   536,   537,   538,   300,   289,   289,   300,   323,   326,
     380,   355,   328,   330,   458,   477,   333,   355,   337,   362,
     377,   360,   362,   365,   365,   365,   368,   220,   370,   370,
     370,   376,   358,   360,   361,   360,   362,   363,   377,   360,
     365,   366,   365,   365,   368,   220,   493,   360,   370,   371,
     370,   371,   370,   371,   365,   360,   359,   379,   362,   379,
      35,   379,   365,   365,   379,   379,    35,    36,   365,   379,
     379,   234,   493,   370,    35,   379,    35,   379,    35,   379,
     370,   370,   370,    35,   379,    35,   379,   370,   360,   362,
     365,   365,   379,    35,   365,   362,    94,    95,    96,   355,
     540,    99,   100,   190,   191,   194,   464,   465,    31,   520,
      99,   100,   101,   542,   101,   103,   104,   105,   544,   107,
     108,   109,   110,   111,   546,    99,   100,   103,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   548,   101,   103,
     121,   123,   124,   125,   126,   550,    99,   100,   113,   115,
     116,   117,   130,   131,   132,   552,   101,   103,   121,   123,
     124,   126,   134,   135,   554,   114,   124,   131,   137,   138,
     556,   124,   138,   558,   131,   141,   142,   560,   117,   121,
     144,   145,   562,   121,   144,   145,   147,   564,   121,   124,
     137,   141,   144,   145,   149,   150,   151,   152,   153,   566,
     101,   144,   145,   570,   121,   144,   145,   173,   572,   101,
     112,   114,   126,   128,   131,   178,   210,   211,   525,   527,
     577,   179,   579,   179,   581,   141,   180,   181,   182,   583,
     114,   131,   575,   103,   118,   131,   137,   185,   186,   585,
     114,   131,   587,   101,   114,   121,   131,   137,   589,    91,
     117,   120,   129,   263,   515,   516,   517,    99,   100,   120,
     190,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   228,   229,   230,   529,   530,   533,
     263,   273,   522,   471,   476,   274,   174,   183,   184,   187,
     188,   591,   355,   470,   321,   283,   321,    36,    38,    40,
      41,    48,    49,    80,   319,   370,   355,   228,   489,   490,
     242,   497,   498,   244,   245,   403,   491,   492,    90,    90,
      90,   450,   355,   355,    86,   355,    91,   515,   166,   529,
     530,   227,   227,   242,   227,   403,    74,    74,   112,   128,
     437,     4,   301,   478,   479,   281,   378,   383,   228,   229,
     392,   393,   141,   236,   237,   238,   239,   240,   396,   397,
     257,   412,     5,    21,    60,    74,    98,   102,   106,   112,
     116,   128,   174,   221,   224,   225,   259,   260,   286,   287,
     415,   416,   417,   418,   419,   420,   421,   423,   424,   425,
     426,   427,   428,   429,   459,   460,   508,   509,   510,   514,
     523,   524,   526,   528,   534,   535,   538,    74,   263,   264,
     265,   432,   439,   440,    74,   435,   439,   267,   268,   269,
     443,   444,   445,   446,    23,   459,    35,   454,   455,    15,
      16,    17,    18,   292,     8,    24,    44,     9,    10,    11,
      12,    13,    14,    98,   102,   106,   112,   122,   128,   133,
     136,   139,   140,   143,   146,   148,   171,   172,   262,   426,
     459,   460,   472,   473,   474,   477,   500,   501,   502,   503,
     504,   505,   506,   507,   509,   510,   511,   512,    42,    42,
     488,   500,   501,   488,   290,   290,   290,   290,   290,   373,
     380,   323,   326,   328,   330,   333,   337,   370,   490,   498,
     492,   380,    47,    47,    47,   330,   370,    47,   330,   360,
     365,   379,    35,   370,   360,   360,   360,   360,   360,   365,
     355,     7,     8,   101,   194,   195,   463,   151,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   567,
     527,   296,   296,    99,   100,   120,   213,   214,   215,   525,
     531,   533,   274,   274,    90,   295,   320,   321,   496,    90,
     244,   245,   407,    90,   447,   448,   471,    23,    84,   290,
      42,    42,    90,   244,   533,    42,   428,   428,   407,   428,
      90,   428,   428,    74,   474,   477,   482,   483,   486,   506,
     507,     7,   291,   356,    90,    90,   393,    67,    98,   112,
     148,   197,   399,   356,    90,    90,    90,   356,   398,   397,
     122,   133,   148,   258,   428,     5,   428,    15,    16,    17,
      18,   292,    20,    22,     8,    44,     5,   439,     7,     7,
       5,     7,     5,   428,   428,   444,     7,   290,   355,   290,
     455,   461,   461,   466,   467,   468,   470,    23,   290,   386,
     501,     7,    15,    16,    17,    18,   292,     7,    20,    22,
       8,   294,   501,   428,   428,   300,   300,   325,   327,   329,
     334,   338,   290,   290,   290,   290,   290,   496,    90,    90,
      90,   496,    90,   360,    90,   465,    84,   117,   165,   166,
     167,   168,   169,   170,   568,    90,    90,    99,   100,   532,
      90,    90,   275,   521,   290,   229,    90,    91,   229,   404,
     459,    78,   378,   484,   485,   356,    90,   471,   480,   481,
     428,   428,    90,    42,   428,    90,   404,    33,   428,   301,
       5,   301,   484,   301,   479,   127,   124,   127,   400,   401,
     101,   101,    60,   101,   428,     5,   415,   459,   510,   511,
     416,   417,   418,    90,   420,   415,   422,   459,   477,   428,
     459,   510,   534,   534,   428,   440,   428,   439,   446,   447,
     480,   355,   301,   387,   388,   506,   511,   511,   502,   503,
     504,   506,    90,   506,   506,   501,    37,    42,    44,    46,
     141,   212,   226,   241,   246,   291,   300,   302,   324,    81,
     101,   291,   300,   302,   350,   353,   380,    77,    78,    79,
      80,    81,    84,   101,   141,   291,   300,   302,   335,    78,
      80,   101,   141,   291,   300,   302,   335,    32,    34,   291,
     300,   302,   325,   327,   329,   334,   338,   290,     7,   297,
     297,   521,   278,   521,    90,   347,    90,    20,    91,   247,
     405,    91,   357,   485,   290,   383,   484,   428,    20,    91,
     405,   428,    33,   487,   506,   507,   513,     7,    91,    91,
      91,   428,   439,   439,     5,   291,   383,   482,     7,   291,
     295,   355,   364,   355,   367,   367,   355,   369,    91,   220,
     355,   372,   372,   372,   300,    68,    69,   354,    91,   300,
     300,   300,   357,   357,   289,    82,    83,   336,    90,    91,
     115,   116,   190,   210,   342,   343,   349,    75,    76,    78,
     331,   332,   300,   357,   289,   343,   331,   300,    91,   289,
     291,   291,   291,   291,   291,   347,    90,    90,   101,   213,
     291,   300,   302,   495,   251,   252,   253,   254,   255,   409,
     243,   408,    90,   480,   291,   409,   408,   428,   301,   401,
     447,   291,     5,   301,   388,   326,   328,   333,   337,   372,
     344,   344,   344,    32,   300,   300,   330,     8,   300,     7,
     300,   300,   330,     5,   300,   129,   290,   339,   291,   521,
      92,   359,   300,   408,    90,   404,   383,   408,   291,   513,
     290,   290,   290,   290,   344,   290,   290,   290,    91,   342,
     332,   226,   241,   246,   343,    22,    90,   351,    91,   340,
     341,   300,   300,   120,   300,    91,   228,   229,   291,   301,
     327,   329,   334,   338,   290,   345,   348,   346,    33,   352,
     300,   300,   300,   300,    90,   300,     7,   291,   143,   148,
     494,   291,   291,   291,   291,   347,   291,   300,   302,   489,
     291,   300,   302,   497,   291,   300,   302,   491,    91,   129,
     301,   341,   300,   300,   300,   300,   300,   291,   300,   300,
     300,   351,   300
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   298,   299,   299,   300,   300,   301,   301,   302,   302,
     302,   302,   302,   303,   303,   303,   303,   304,   304,   304,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   306,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   308,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   310,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   312,   312,   312,   312,
     312,   312,   313,   313,   313,   313,   313,   313,   313,   314,
     315,   315,   316,   316,   317,   318,   318,   319,   319,   319,
     319,   319,   319,   319,   319,   320,   320,   321,   321,   321,
     322,   323,   324,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   326,   327,   327,   327,   327,
     327,   327,   328,   329,   329,   329,   329,   329,   329,   329,
     329,   329,   329,   330,   330,   331,   331,   332,   332,   332,
     333,   334,   334,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   335,   335,   336,   336,   337,   338,   338,   338,
     338,   338,   339,   340,   340,   340,   341,   342,   343,   343,
     344,   345,   345,   345,   345,   346,   346,   346,   346,   347,
     347,   347,   347,   348,   348,   348,   348,   349,   349,   349,
     349,   349,   350,   351,   351,   352,   352,   353,   354,   354,
     355,   356,   356,   356,   357,   358,   358,   359,   359,   359,
     359,   359,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     376,   376,   376,   377,   378,   379,   379,   380,   380,   381,
     382,   382,   383,   383,   383,   383,   383,   383,   383,   383,
     383,   383,   383,   383,   383,   383,   383,   383,   383,   383,
     383,   383,   384,   384,   385,   386,   386,   387,   387,   387,
     388,   389,   389,   390,   390,   391,   391,   392,   392,   393,
     393,   394,   394,   395,   396,   396,   397,   397,   397,   397,
     397,   397,   398,   399,   399,   399,   399,   399,   400,   400,
     401,   401,   402,   402,   402,   403,   403,   403,   404,   404,
     405,   405,   406,   406,   407,   407,   407,   408,   408,   408,
     408,   409,   409,   409,   409,   409,   410,   411,   412,   412,
     412,   412,   412,   413,   414,   414,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   416,   416,   416,   417,
     417,   418,   418,   419,   419,   420,   421,   421,   422,   422,
     423,   423,   424,   425,   426,   427,   427,   427,   428,   428,
     428,   429,   429,   429,   429,   429,   429,   429,   430,   430,
     431,   432,   432,   432,   433,   433,   434,   435,   435,   435,
     435,   435,   436,   436,   437,   437,   438,   438,   439,   439,
     440,   440,   440,   441,   441,   442,   443,   443,   444,   444,
     445,   445,   446,   446,   447,   447,   448,   449,   449,   450,
     450,   451,   452,   452,   453,   454,   454,   455,   456,   456,
     457,   458,   459,   459,   459,   460,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   462,
     463,   463,   463,   464,   464,   464,   464,   464,   465,   465,
     466,   466,   466,   467,   467,   468,   468,   469,   469,   470,
     471,   471,   472,   473,   474,   474,   474,   475,   476,   476,
     476,   477,   478,   478,   478,   479,   479,   479,   480,   480,
     481,   482,   482,   483,   484,   484,   485,   485,   486,   486,
     487,   487,   488,   488,   489,   490,   491,   492,   493,   494,
     494,   495,   495,   496,   497,   497,   498,   499,   499,   499,
     499,   500,   500,   501,   501,   501,   502,   502,   502,   503,
     503,   504,   504,   505,   505,   506,   507,   507,   508,   508,
     509,   510,   510,   510,   510,   510,   510,   510,   510,   510,
     510,   510,   510,   511,   511,   511,   511,   511,   511,   511,
     511,   511,   511,   511,   511,   511,   511,   511,   512,   512,
     512,   512,   512,   512,   513,   513,   513,   513,   513,   513,
     514,   514,   514,   515,   515,   516,   516,   516,   516,   517,
     517,   517,   517,   517,   517,   517,   517,   517,   517,   517,
     517,   517,   517,   517,   517,   517,   517,   517,   517,   518,
     518,   518,   518,   518,   519,   520,   521,   521,   522,   522,
     523,   524,   524,   524,   525,   525,   526,   526,   527,   527,
     527,   528,   528,   528,   529,   529,   530,   530,   530,   530,
     530,   530,   530,   530,   530,   530,   530,   530,   530,   530,
     530,   531,   531,   531,   531,   531,   531,   531,   532,   532,
     533,   533,   533,   533,   534,   534,   535,   535,   536,   536,
     537,   538,   538,   538,   538,   538,   538,   538,   538,   538,
     538,   538,   538,   538,   538,   538,   538,   539,   540,   540,
     540,   541,   542,   542,   542,   543,   544,   544,   544,   544,
     545,   546,   546,   546,   546,   546,   547,   548,   548,   548,
     548,   548,   548,   548,   548,   548,   548,   548,   548,   549,
     550,   550,   550,   550,   550,   550,   550,   551,   552,   552,
     552,   552,   552,   552,   552,   552,   552,   553,   554,   554,
     554,   554,   554,   554,   554,   554,   555,   556,   556,   556,
     556,   556,   557,   558,   558,   559,   560,   560,   560,   561,
     562,   562,   562,   562,   563,   564,   564,   564,   564,   565,
     565,   565,   566,   566,   566,   566,   566,   566,   566,   566,
     566,   566,   567,   567,   567,   567,   567,   567,   567,   567,
     567,   567,   567,   567,   568,   568,   568,   568,   568,   568,
     568,   568,   569,   570,   570,   570,   571,   572,   572,   572,
     572,   573,   573,   573,   573,   573,   573,   573,   573,   574,
     575,   575,   576,   577,   577,   577,   577,   578,   579,   580,
     581,   582,   583,   583,   583,   583,   584,   585,   585,   585,
     585,   585,   585,   586,   587,   587,   588,   589,   589,   589,
     589,   589,   590,   591,   591,   591,   591,   591
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       5,     3,     2,     1,     1,     2,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     6,     2,     6,     3,     2,     6,     6,
       3,     6,     2,     3,     3,     8,     3,     3,     2,     6,
       2,     6,     6,     6,     3,     6,     2,     3,     3,     8,
       3,     3,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     2,     2,     2,     2,     2,     4,     2,     2,     3,
       2,     2,     2,     2,     2,     3,     2,     2,     3,     2,
       2,     3,     2,     2,     3,     2,     2,     3,     3,     2,
       2,     2,     2,     2,     3,     4,     2,     3,     2,     2,
       3,     2,     2,     2,     2,     2,     3,     2,     2,     3,
       2,     1,     2,     1,     3,     0,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     2,
       1,     0,     2,     0,     2,     2,     3,     8,     8,     8,
       8,     8,     8,     9,     8,     0,     0,     2,     2,     3,
       3,     3,     0,     0,     2,     2,     4,     4,     4,     4,
       4,     2,     3,     1,     1,     3,     1,     1,     1,     1,
       0,     0,     2,     2,     4,     6,     6,     6,     6,     4,
       4,     3,     2,     2,     1,     1,     0,     0,     2,     2,
       6,     5,     3,     1,     3,     3,     1,     1,     1,     3,
       0,     0,     2,     2,     2,     0,     2,     2,     2,     0,
       2,     2,     2,     0,     2,     2,     2,     1,     1,     1,
       1,     1,     7,     1,     2,     2,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     2,     3,     1,     2,     3,
       1,     2,     1,     2,     3,     1,     2,     2,     2,     1,
       2,     2,     2,     2,     2,     0,     1,     1,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     2,     1,     3,     3,
       5,     3,     4,     1,     2,     1,     3,     1,     2,     2,
       2,     1,     2,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     1,     2,     2,     1,     1,     1,     3,     1,
       1,     1,     7,     6,     3,     1,     1,     0,     1,     1,
       0,     3,     5,     3,     1,     1,     0,     0,     3,     3,
       3,     1,     1,     1,     1,     1,     2,     1,     0,     4,
       4,     4,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     3,     1,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     4,     2,     3,     2,     2,     1,
       1,     3,     4,     1,     2,     1,     1,     2,     3,     1,
       3,     4,     3,     5,     1,     1,     3,     6,     1,     3,
       1,     1,     1,     1,     2,     1,     1,     2,     2,     1,
       1,     3,     1,     1,     1,     2,     1,     4,     5,     1,
       1,     7,     6,     1,     1,     1,     2,     2,     6,     8,
       1,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       1,     3,     3,     3,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     3,     3,     3,     3,     5,     1,     2,
       1,     1,     2,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     4,     1,     1,     1,
       1,     5,     3,     0,     6,     5,     1,     2,     2,     3,
       5,     3,     3,     1,     1,     1,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     4,     1,     4,     2,     1,     0,     2,     1,     1,
       5,     7,     5,     4,     1,     1,     2,     3,     1,     1,
       1,     2,     3,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     4,     5,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     1,     1,
       1,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     2,     1,     1,     2,     1,     1,     1,     2,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     2,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     2,     1,     1,     1,
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
          case 91: /* "string"  */
#line 266 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3684 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 92: /* "quoted string"  */
#line 266 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3690 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 93: /* "string with a trailing asterisk"  */
#line 266 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3696 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 303: /* line  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3702 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 304: /* base_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3708 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 305: /* add_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3714 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 306: /* replace_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3720 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 307: /* create_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3726 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 308: /* insert_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3732 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 309: /* delete_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3738 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 310: /* get_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3744 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 311: /* list_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3750 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 312: /* reset_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3756 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 313: /* flush_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3762 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 314: /* rename_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3768 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 315: /* import_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3774 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 316: /* export_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3780 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 317: /* monitor_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3786 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 318: /* monitor_event  */
#line 720 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3792 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 322: /* describe_cmd  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3798 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 323: /* table_block_alloc  */
#line 529 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 3804 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 326: /* chain_block_alloc  */
#line 531 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 3810 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 328: /* set_block_alloc  */
#line 540 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3816 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 330: /* set_block_expr  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3822 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 333: /* map_block_alloc  */
#line 543 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3828 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* flowtable_block_alloc  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 3834 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* flowtable_expr  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3840 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* flowtable_list_expr  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3846 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* flowtable_expr_member  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3852 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* data_type_atom_expr  */
#line 511 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3858 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* data_type_expr  */
#line 511 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3864 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* obj_block_alloc  */
#line 549 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 3870 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 349: /* type_identifier  */
#line 506 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3876 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 352: /* dev_spec  */
#line 526 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3882 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 355: /* identifier  */
#line 506 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3888 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* string  */
#line 506 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3894 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* table_spec  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3900 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* tableid_spec  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3906 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 362: /* chain_spec  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3912 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 363: /* chainid_spec  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3918 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 364: /* chain_identifier  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3924 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 365: /* set_spec  */
#line 522 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3930 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 366: /* setid_spec  */
#line 522 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3936 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 367: /* set_identifier  */
#line 522 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3942 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 368: /* flowtable_spec  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3948 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 370: /* obj_spec  */
#line 522 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3954 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 371: /* objid_spec  */
#line 522 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3960 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 372: /* obj_identifier  */
#line 522 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3966 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* handle_spec  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3972 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 374: /* position_spec  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3978 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* index_spec  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3984 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* rule_position  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3990 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* ruleid_spec  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3996 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 378: /* comment_spec  */
#line 506 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4002 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 379: /* ruleset_spec  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 4008 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 380: /* rule  */
#line 533 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 4014 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 382: /* stmt_list  */
#line 552 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 4020 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* stmt  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4026 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* verdict_stmt  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4032 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* verdict_map_stmt  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4038 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* verdict_map_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4044 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* verdict_map_list_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4050 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* verdict_map_list_member_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4056 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* connlimit_stmt  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4062 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* counter_stmt  */
#line 556 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4068 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* counter_stmt_alloc  */
#line 556 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4074 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* log_stmt  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4080 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* log_stmt_alloc  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4086 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* limit_stmt  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4092 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* quota_unit  */
#line 526 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4098 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* quota_stmt  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4104 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* reject_stmt  */
#line 570 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4110 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* reject_stmt_alloc  */
#line 570 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4116 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* nat_stmt  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4122 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* nat_stmt_alloc  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4128 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* primary_stmt_expr  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4134 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* shift_stmt_expr  */
#line 614 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4140 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* and_stmt_expr  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4146 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* exclusive_or_stmt_expr  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4152 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* inclusive_or_stmt_expr  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4158 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* basic_stmt_expr  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4164 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* concat_stmt_expr  */
#line 604 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4170 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* map_stmt_expr_set  */
#line 604 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4176 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* map_stmt_expr  */
#line 604 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4182 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* prefix_stmt_expr  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4188 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* range_stmt_expr  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4194 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* wildcard_expr  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4200 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* multiton_stmt_expr  */
#line 607 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4206 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* stmt_expr  */
#line 604 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4212 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* masq_stmt  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4218 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* masq_stmt_alloc  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4224 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* redir_stmt  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4230 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* redir_stmt_alloc  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4236 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 436: /* dup_stmt  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4242 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* fwd_stmt  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4248 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 441: /* queue_stmt  */
#line 575 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4254 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* queue_stmt_alloc  */
#line 575 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4260 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 447: /* set_elem_expr_stmt  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4266 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* set_elem_expr_stmt_alloc  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4272 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 449: /* set_stmt  */
#line 582 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4278 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* map_stmt  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4284 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* meter_stmt  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4290 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 453: /* flow_stmt_legacy_alloc  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4296 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 456: /* meter_stmt_alloc  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4302 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* match_stmt  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4308 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* variable_expr  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4314 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* symbol_expr  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4320 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* integer_expr  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4326 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* primary_expr  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4332 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* fib_expr  */
#line 715 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4338 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* shift_expr  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4344 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 467: /* and_expr  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4350 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* exclusive_or_expr  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4356 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* inclusive_or_expr  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4362 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* basic_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4368 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* concat_expr  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4374 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* prefix_rhs_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4380 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* range_rhs_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4386 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* multiton_rhs_expr  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4392 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* map_expr  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4398 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4404 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* set_expr  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4410 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* set_list_expr  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4416 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* set_list_member_expr  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4422 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* meter_key_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4428 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* meter_key_expr_alloc  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4434 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* set_elem_expr  */
#line 633 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4440 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 483: /* set_elem_expr_alloc  */
#line 633 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4446 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 486: /* set_lhs_expr  */
#line 633 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4452 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* set_rhs_expr  */
#line 633 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4458 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* initializer_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4464 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 489: /* counter_config  */
#line 724 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).counter)); }
#line 4470 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 490: /* counter_obj  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4476 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 491: /* quota_config  */
#line 726 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).quota)); }
#line 4482 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 492: /* quota_obj  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4488 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 496: /* ct_obj_alloc  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4494 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 497: /* limit_config  */
#line 728 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).limit)); }
#line 4500 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 498: /* limit_obj  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4506 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 499: /* relational_expr  */
#line 654 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4512 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* list_rhs_expr  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4518 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* rhs_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4524 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 502: /* shift_rhs_expr  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4530 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 503: /* and_rhs_expr  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4536 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 504: /* exclusive_or_rhs_expr  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4542 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* inclusive_or_rhs_expr  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4548 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* basic_rhs_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4554 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* concat_rhs_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4560 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 509: /* boolean_expr  */
#line 736 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4566 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* keyword_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4572 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 511: /* primary_rhs_expr  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4578 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* verdict_expr  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4584 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 514: /* meta_expr  */
#line 695 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4590 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* meta_stmt  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4596 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* socket_expr  */
#line 699 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4602 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* numgen_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4608 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 524: /* hash_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4614 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 526: /* rt_expr  */
#line 705 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4620 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* ct_expr  */
#line 711 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4626 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* symbol_stmt_expr  */
#line 646 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4632 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* list_stmt_expr  */
#line 614 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4638 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* ct_stmt  */
#line 560 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4644 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 537: /* payload_stmt  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4650 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* payload_expr  */
#line 658 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4656 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* payload_raw_expr  */
#line 658 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4662 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* eth_hdr_expr  */
#line 661 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4668 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* vlan_hdr_expr  */
#line 661 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4674 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 545: /* arp_hdr_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4680 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* ip_hdr_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4686 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 549: /* icmp_hdr_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4692 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* ip6_hdr_expr  */
#line 670 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4698 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 553: /* icmp6_hdr_expr  */
#line 670 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4704 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 555: /* auth_hdr_expr  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4710 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 557: /* esp_hdr_expr  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4716 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 559: /* comp_hdr_expr  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4722 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 561: /* udp_hdr_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4728 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 563: /* udplite_hdr_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4734 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 565: /* tcp_hdr_expr  */
#line 731 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4740 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 569: /* dccp_hdr_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4746 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 571: /* sctp_hdr_expr  */
#line 679 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4752 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 573: /* exthdr_expr  */
#line 683 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4758 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 574: /* hbh_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4764 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 576: /* rt_hdr_expr  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4770 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 578: /* rt0_hdr_expr  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4776 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 580: /* rt2_hdr_expr  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4782 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 582: /* rt4_hdr_expr  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4788 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 584: /* frag_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4794 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 586: /* dst_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4800 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 588: /* mh_hdr_expr  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4806 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 590: /* exthdr_exists_expr  */
#line 740 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4812 "parser_bison.c" /* yacc.c:1257  */
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

#line 4929 "parser_bison.c" /* yacc.c:1429  */
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
#line 749 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[0].cmd) != NULL) {
					LIST_HEAD(list);

					(yyvsp[0].cmd)->location = (yylsp[0]);

					list_add_tail(&(yyvsp[0].cmd)->list, &list);
					if (cmd_evaluate(&state->ectx, (yyvsp[0].cmd)) < 0) {
						cmd_free((yyvsp[0].cmd));
						if (++state->nerrs == nft->parser_max_errors)
							YYABORT;
					} else
						list_splice_tail(&list, state->cmds);
				}
			}
#line 5132 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 8:
#line 775 "parser_bison.y" /* yacc.c:1646  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5144 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 9:
#line 783 "parser_bison.y" /* yacc.c:1646  */
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
#line 5162 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 797 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 5173 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 11:
#line 804 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5188 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 815 "parser_bison.y" /* yacc.c:1646  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 5198 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 822 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 5204 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 823 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 5210 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 824 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 5216 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 16:
#line 826 "parser_bison.y" /* yacc.c:1646  */
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
					LIST_HEAD(list);

					(yyvsp[-1].cmd)->location = (yylsp[-1]);

					list_add_tail(&(yyvsp[-1].cmd)->list, &list);
					if (cmd_evaluate(&state->ectx, (yyvsp[-1].cmd)) < 0) {
						cmd_free((yyvsp[-1].cmd));
						if (++state->nerrs == nft->parser_max_errors)
							YYABORT;
					} else
						list_splice_tail(&list, state->cmds);
				}
				if (state->nerrs)
					YYABORT;
				(yyval.cmd) = NULL;

				YYACCEPT;
			}
#line 5250 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 857 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5256 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 858 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5262 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 859 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5268 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 860 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5274 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 861 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5280 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 862 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5286 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 863 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5292 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 864 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5298 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 865 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5304 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 866 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5310 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 867 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5316 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 868 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5322 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 869 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5328 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 870 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5334 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 871 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5340 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 875 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5348 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 880 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5358 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 886 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5366 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 891 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5377 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 898 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5385 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 902 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5393 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 907 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5403 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 914 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5413 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 920 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5421 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 925 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5431 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 42:
#line 931 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5444 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 940 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5452 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 944 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5460 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 948 "parser_bison.y" /* yacc.c:1646  */
    {

				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5469 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 953 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5477 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 959 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5485 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 965 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5493 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 970 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5503 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 976 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5511 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 981 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 989 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5532 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 996 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5542 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1002 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5550 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1007 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5560 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1013 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5573 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1022 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5581 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1026 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5589 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1030 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5597 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1034 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5605 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1040 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1046 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5621 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1050 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5629 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1054 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5637 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1058 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5645 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1062 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5653 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1066 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1070 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1074 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5677 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1078 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1082 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1086 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5701 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1090 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5709 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1094 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5717 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1098 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5725 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1102 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5733 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1106 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5741 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1110 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5749 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1116 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5757 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1122 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5765 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1126 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5773 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1130 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5781 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1134 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5789 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1138 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5797 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1142 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5805 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1146 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5813 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1150 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5821 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1154 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5829 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1158 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5837 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1162 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5845 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1166 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1170 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5861 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1174 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5869 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1178 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5877 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1182 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5885 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1186 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5893 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1190 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5901 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1194 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5909 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1198 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5917 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1202 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5925 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1206 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5933 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1210 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5941 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1214 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5949 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1218 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5957 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1222 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5965 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1228 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5973 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1232 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5981 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1236 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 5989 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1240 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5997 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1244 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6005 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1248 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6013 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1254 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6021 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1258 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6029 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1262 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6037 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1266 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6045 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1270 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1274 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6061 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1278 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6069 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1284 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 6078 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1291 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6088 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1297 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6098 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1305 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6108 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1311 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1319 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 6129 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1327 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1328 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1331 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 6147 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1332 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 6153 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1333 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 6159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1334 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 6165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1335 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 6171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1336 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 6177 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1337 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 6183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1338 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 6189 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1341 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 6195 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1345 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 6201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1346 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 6207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1347 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 6213 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1351 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 6223 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1359 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 6232 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1366 "parser_bison.y" /* yacc.c:1646  */
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
#line 6248 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1379 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 6254 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1386 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6267 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1397 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6279 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1407 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6291 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1418 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6303 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1428 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6316 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1439 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6329 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1448 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 6342 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1459 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1470 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 6364 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1476 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 6370 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1482 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 6379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1489 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6387 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1494 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6393 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1498 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6402 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1503 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6411 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1508 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6420 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1513 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1518 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6438 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1523 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 6447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1535 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1541 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 6461 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1542 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 6467 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1543 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 6473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1547 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6481 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1552 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6487 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1556 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6496 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1563 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].expr)->dtype;

				expr_free((yyvsp[-1].expr));
				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6509 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1574 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6520 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1583 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6531 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1592 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6542 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1599 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6551 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1604 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6560 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1612 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 6568 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1616 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 6576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1621 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 6582 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1622 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 6588 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1626 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 6596 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1631 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 6602 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1635 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.flowtable)->hookstr	= chain_hookname_lookup((yyvsp[-3].string));
				if ((yyval.flowtable)->hookstr == NULL) {
					erec_queue(error(&(yylsp[-3]), "unknown chain hook %s", (yyvsp[-3].string)),
						   state->msgs);
					xfree((yyvsp[-3].string));
					YYERROR;
				}
				xfree((yyvsp[-3].string));

				(yyval.flowtable)->priority = (yyvsp[-1].val);
			}
#line 6619 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1648 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 6627 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1654 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6636 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1661 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 6645 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1666 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 6654 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1674 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
			}
#line 6664 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1682 "parser_bison.y" /* yacc.c:1646  */
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
			}
#line 6680 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1697 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].expr)->ops->type != EXPR_CONCAT) {
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
#line 6701 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1716 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 6709 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1721 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6715 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1725 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->counter = *(yyvsp[0].counter);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1731 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6730 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1735 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->quota = *(yyvsp[0].quota);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6739 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1741 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1745 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6753 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1750 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6759 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1754 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->limit = *(yyvsp[0].limit);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6768 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1760 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6774 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1761 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("mark"); }
#line 6780 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1762 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("dscp"); }
#line 6786 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1763 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("ecn"); }
#line 6792 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1764 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("classid"); }
#line 6798 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1768 "parser_bison.y" /* yacc.c:1646  */
    {
				const char *chain_type = chain_type_name_lookup((yyvsp[-5].string));

				if (chain_type == NULL) {
					erec_queue(error(&(yylsp[-5]), "unknown chain type %s", (yyvsp[-5].string)),
						   state->msgs);
					xfree((yyvsp[-5].string));
					YYERROR;
				}
				(yyvsp[-7].chain)->type		= xstrdup(chain_type);
				xfree((yyvsp[-5].string));

				(yyvsp[-7].chain)->hookstr	= chain_hookname_lookup((yyvsp[-3].string));
				if ((yyvsp[-7].chain)->hookstr == NULL) {
					erec_queue(error(&(yylsp[-3]), "unknown chain hook %s", (yyvsp[-3].string)),
						   state->msgs);
					xfree((yyvsp[-3].string));
					YYERROR;
				}
				xfree((yyvsp[-3].string));

				(yyvsp[-7].chain)->dev		= (yyvsp[-2].string);
				(yyvsp[-7].chain)->priority	= (yyvsp[0].val);
				(yyvsp[-7].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
#line 6828 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1795 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 6834 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1796 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = -(yyvsp[0].val); }
#line 6840 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1799 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6846 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1800 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6852 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1804 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].chain)->policy != -1) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].val);
			}
#line 6865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1814 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_ACCEPT; }
#line 6871 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1815 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_DROP;   }
#line 6877 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1827 "parser_bison.y" /* yacc.c:1646  */
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
#line 6894 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1841 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6900 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1845 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6906 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1846 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 6912 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1847 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_INET; }
#line 6918 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1848 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_ARP; }
#line 6924 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1849 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 6930 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1850 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 6936 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1854 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 6947 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1863 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yyloc);
			}
#line 6958 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1872 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 6968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1880 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 6978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1888 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 6988 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1896 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 6998 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1904 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 7008 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1912 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 7018 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1921 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).flowtable	= (yyvsp[0].string);
			}
#line 7027 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1928 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable	= (yyvsp[0].string);
			}
#line 7036 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1935 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 7046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1943 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 7056 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1951 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 7066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1959 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 7076 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1967 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 7086 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1975 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 7096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1983 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 7104 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1987 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7113 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1992 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7125 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 272:
#line 2000 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7134 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 273:
#line 2007 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7143 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 274:
#line 2014 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strlen((yyvsp[0].string)) > UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed", UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 7156 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 275:
#line 2025 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 7165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 276:
#line 2030 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 7174 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 277:
#line 2037 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 7182 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 278:
#line 2041 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 7190 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 279:
#line 2047 "parser_bison.y" /* yacc.c:1646  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 7204 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 280:
#line 2059 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 7214 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 281:
#line 2065 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 7223 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 302:
#line 2094 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7231 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 303:
#line 2098 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7239 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2104 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2110 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7256 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2115 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7267 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2124 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 308:
#line 2129 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7285 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 310:
#line 2137 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 7293 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 311:
#line 2143 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count	= (yyvsp[0].val);
			}
#line 7302 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 312:
#line 2148 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = connlimit_stmt_alloc(&(yyloc));
				(yyval.stmt)->connlimit.count = (yyvsp[0].val);
				(yyval.stmt)->connlimit.flags = NFT_CONNLIMIT_F_INV;
			}
#line 7312 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 315:
#line 2159 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 7320 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 316:
#line 2163 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7330 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 317:
#line 2171 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7338 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 319:
#line 2178 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 7346 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2182 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 7354 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2192 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 7362 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2198 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7370 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2205 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 7379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2210 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 7388 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 328:
#line 2215 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 7397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 329:
#line 2220 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 7406 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2225 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 7415 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2230 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 7423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2236 "parser_bison.y" /* yacc.c:1646  */
    {
				if (!strcmp("emerg", (yyvsp[0].string)))
					(yyval.val) = LOG_EMERG;
				else if (!strcmp("alert", (yyvsp[0].string)))
					(yyval.val) = LOG_ALERT;
				else if (!strcmp("crit", (yyvsp[0].string)))
					(yyval.val) = LOG_CRIT;
				else if (!strcmp("err", (yyvsp[0].string)))
					(yyval.val) = LOG_ERR;
				else if (!strcmp("warn", (yyvsp[0].string)))
					(yyval.val) = LOG_WARNING;
				else if (!strcmp("notice", (yyvsp[0].string)))
					(yyval.val) = LOG_NOTICE;
				else if (!strcmp("info", (yyvsp[0].string)))
					(yyval.val) = LOG_INFO;
				else if (!strcmp("debug", (yyvsp[0].string)))
					(yyval.val) = LOG_DEBUG;
				else if (!strcmp("audit", (yyvsp[0].string)))
					(yyval.val) = LOGLEVEL_AUDIT;
				else {
					erec_queue(error(&(yylsp[0]), "invalid log level"),
						   state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}
				xfree((yyvsp[0].string));
			}
#line 7455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2266 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 7463 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2270 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 7471 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2274 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 7479 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2278 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 7487 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2282 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 7495 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2288 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7503 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2295 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 7511 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2299 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 7519 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2305 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 7532 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2314 "parser_bison.y" /* yacc.c:1646  */
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
#line 7555 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2333 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7565 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2340 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 7571 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2341 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7577 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2342 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7583 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 348:
#line 2345 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("bytes"); }
#line 7589 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 349:
#line 2346 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7595 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 350:
#line 2349 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7601 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2351 "parser_bison.y" /* yacc.c:1646  */
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
#line 7618 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 352:
#line 2366 "parser_bison.y" /* yacc.c:1646  */
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
#line 7638 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 353:
#line 2382 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7648 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 354:
#line 2389 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 7654 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 355:
#line 2390 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7660 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 356:
#line 2391 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7666 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 357:
#line 2394 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7672 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 358:
#line 2395 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 7678 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2396 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 7684 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 360:
#line 2398 "parser_bison.y" /* yacc.c:1646  */
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
#line 7701 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 361:
#line 2412 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL; }
#line 7707 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2413 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60; }
#line 7713 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 363:
#line 2414 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 7719 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 364:
#line 2415 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 7725 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2416 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 7731 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2423 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 7739 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2429 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 7748 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2434 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmp_code_type;
				xfree((yyvsp[0].string));
			}
#line 7763 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 370:
#line 2445 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpv6_code_type;
				xfree((yyvsp[0].string));
			}
#line 7778 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 371:
#line 2456 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpx_code_type;
				xfree((yyvsp[0].string));
			}
#line 7792 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 372:
#line 2466 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 7800 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2474 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 7806 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2475 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 7812 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2478 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7818 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2479 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7824 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2480 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7830 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2481 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7836 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2482 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 381:
#line 2483 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7848 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2484 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7854 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2485 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7860 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2486 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7866 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2487 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7872 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 387:
#line 2492 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7880 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2496 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7888 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 390:
#line 2503 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7896 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 392:
#line 2510 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2517 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7912 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2527 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyval.expr)->ops->type != EXPR_CONCAT) {
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
#line 7933 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2550 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7941 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2553 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7947 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 402:
#line 2557 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 7955 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 403:
#line 2563 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7963 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 404:
#line 2569 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 7976 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2590 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7984 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2594 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7992 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2598 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8001 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2603 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8010 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2608 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8018 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2612 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8026 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2616 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2625 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 8040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2629 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8048 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2633 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8057 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2638 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8065 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2647 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 8071 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2651 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8079 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2655 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8087 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2659 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8095 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2663 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8104 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2668 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8113 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2675 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 8122 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2680 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 8132 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2687 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8138 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2688 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 8144 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2692 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 8153 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2697 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.family = (yyvsp[-4].val);
				(yyval.stmt)->fwd.addr = (yyvsp[-2].expr);
				(yyval.stmt)->fwd.dev = (yyvsp[0].expr);
			}
#line 8164 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2707 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8172 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2712 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 8178 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2713 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 8184 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2714 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 8190 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2722 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 8198 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2728 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 448:
#line 2735 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 8215 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2740 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 8223 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2747 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8231 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2752 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 8237 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2753 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 8243 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2761 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8251 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2767 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 8262 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2774 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 8273 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2782 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 8279 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 460:
#line 2783 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 8285 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2787 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.map = map_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 8296 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2796 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 8307 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 463:
#line 2802 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 8313 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2806 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 8321 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2812 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8329 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2819 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 8337 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2825 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 8350 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2834 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 8363 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2845 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2851 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);
				struct symbol *sym;

				sym = symbol_get(scope, (yyvsp[0].string));
				if (!sym) {
					erec_queue(error(&(yylsp[0]), "unknown identifier '%s'", (yyvsp[0].string)),
						   state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}

				(yyval.expr) = variable_expr_alloc(&(yyloc), scope, sym);
				xfree((yyvsp[0].string));
			}
#line 8391 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2870 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 8402 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2877 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 8413 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2886 "parser_bison.y" /* yacc.c:1646  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 8426 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2896 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8432 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2897 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8438 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2898 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8444 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2899 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8450 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2900 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8456 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2901 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8462 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2902 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8468 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2903 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8474 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2904 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8480 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2905 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8486 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2906 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8492 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 487:
#line 2907 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8498 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 488:
#line 2908 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 8504 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 489:
#line 2912 "parser_bison.y" /* yacc.c:1646  */
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
#line 8529 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2934 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 8535 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 491:
#line 2935 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 8541 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 492:
#line 2936 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 8547 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2939 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 8553 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 494:
#line 2940 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 8559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 495:
#line 2941 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 8565 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 496:
#line 2942 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 8571 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2943 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 8577 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 498:
#line 2947 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8585 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2955 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8593 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2959 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8601 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 504:
#line 2966 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8609 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 506:
#line 2973 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8617 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 508:
#line 2980 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8625 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 511:
#line 2990 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyval.expr)->ops->type != EXPR_CONCAT) {
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
#line 8646 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 512:
#line 3009 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 8654 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 513:
#line 3015 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8662 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 517:
#line 3026 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8670 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 521:
#line 3037 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8679 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 522:
#line 3044 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8688 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 523:
#line 3049 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8697 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 525:
#line 3057 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8705 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 526:
#line 3061 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8713 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 527:
#line 3065 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 8721 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 529:
#line 3072 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8730 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 530:
#line 3079 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8738 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 533:
#line 3089 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8746 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 534:
#line 3095 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 8754 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 536:
#line 3102 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 8762 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 537:
#line 3106 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 8770 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 544:
#line 3124 "parser_bison.y" /* yacc.c:1646  */
    {
				struct counter *counter;

				counter = xzalloc(sizeof(*counter));
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
				(yyval.counter) = counter;
			}
#line 8783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 545:
#line 3135 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
				(yyval.obj)->counter = *(yyvsp[0].counter);
			}
#line 8793 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 546:
#line 3143 "parser_bison.y" /* yacc.c:1646  */
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
#line 8816 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 547:
#line 3164 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
				(yyval.obj)->quota = *(yyvsp[0].quota);
			}
#line 8826 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 548:
#line 3171 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 8832 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 549:
#line 3174 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_TCP; }
#line 8838 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 550:
#line 3175 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_UDP; }
#line 8844 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 551:
#line 3179 "parser_bison.y" /* yacc.c:1646  */
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
#line 8863 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 552:
#line 3194 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 8871 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 553:
#line 3200 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 8879 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 554:
#line 3206 "parser_bison.y" /* yacc.c:1646  */
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
#line 8894 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 555:
#line 3217 "parser_bison.y" /* yacc.c:1646  */
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
#line 8918 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 556:
#line 3239 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
				(yyval.obj)->limit = *(yyvsp[0].limit);
			}
#line 8928 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 557:
#line 3247 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8936 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 558:
#line 3251 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8944 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 559:
#line 3255 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8952 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 560:
#line 3259 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-3]), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[-1].expr));
			}
#line 8960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 561:
#line 3265 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 562:
#line 3271 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8980 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 563:
#line 3278 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8986 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 564:
#line 3279 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8992 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 565:
#line 3280 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8998 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 567:
#line 3285 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9006 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 568:
#line 3289 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9014 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 570:
#line 3296 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9022 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 572:
#line 3303 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9030 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 574:
#line 3310 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9038 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 577:
#line 3320 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyval.expr)->ops->type != EXPR_CONCAT) {
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
#line 9059 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 578:
#line 3338 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = true; }
#line 9065 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 579:
#line 3339 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = false; }
#line 9071 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 580:
#line 3343 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 1, &(yyvsp[0].val));
			}
#line 9081 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 581:
#line 3350 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 9087 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 582:
#line 3351 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 9093 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 583:
#line 3352 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 9099 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 584:
#line 3353 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 9105 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 585:
#line 3354 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 9111 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 586:
#line 3355 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 9117 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 587:
#line 3356 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 9123 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 588:
#line 3357 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 9129 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 589:
#line 3358 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 9135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 590:
#line 3359 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 9141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 591:
#line 3360 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 9147 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 592:
#line 3361 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 9153 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 593:
#line 3364 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 594:
#line 3365 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 595:
#line 3366 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 596:
#line 3367 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9177 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 597:
#line 3369 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9188 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 598:
#line 3376 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9199 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 599:
#line 3383 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9210 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 600:
#line 3390 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9221 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 601:
#line 3397 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9232 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 602:
#line 3404 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9243 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 603:
#line 3411 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9254 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 604:
#line 3418 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9265 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 605:
#line 3425 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 606:
#line 3432 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9287 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 607:
#line 3439 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9298 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 608:
#line 3447 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_EQ; }
#line 9304 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 609:
#line 3448 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_NEQ; }
#line 9310 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 610:
#line 3449 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LT; }
#line 9316 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 611:
#line 3450 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GT; }
#line 9322 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 612:
#line 3451 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GTE; }
#line 9328 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 613:
#line 3452 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LTE; }
#line 9334 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 614:
#line 3456 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 9342 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 615:
#line 3460 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 9350 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 616:
#line 3464 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 9358 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 617:
#line 3468 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].string));
			}
#line 9366 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 618:
#line 3472 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].string));
			}
#line 9374 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 619:
#line 3476 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 9382 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 620:
#line 3482 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 9390 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 621:
#line 3486 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 9398 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 622:
#line 3490 "parser_bison.y" /* yacc.c:1646  */
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
#line 9416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 625:
#line 3509 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_LEN; }
#line 9422 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 626:
#line 3510 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 9428 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 627:
#line 3511 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 9434 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 628:
#line 3512 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 9440 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 629:
#line 3515 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_MARK; }
#line 9446 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 630:
#line 3516 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIF; }
#line 9452 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 631:
#line 3517 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 9458 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 632:
#line 3518 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 9464 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 633:
#line 3519 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIF; }
#line 9470 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 634:
#line 3520 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 9476 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 635:
#line 3521 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 9482 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 636:
#line 3522 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKUID; }
#line 9488 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 637:
#line 3523 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKGID; }
#line 9494 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 638:
#line 3524 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 9500 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3525 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 9506 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 640:
#line 3526 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 9512 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 641:
#line 3527 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 9518 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 642:
#line 3528 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 9524 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3529 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 9530 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 644:
#line 3530 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 9536 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 645:
#line 3531 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CPU; }
#line 9542 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 646:
#line 3532 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 9548 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 647:
#line 3533 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 9554 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 648:
#line 3534 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 9560 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 649:
#line 3538 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 9568 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 650:
#line 3542 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 9576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 651:
#line 3546 "parser_bison.y" /* yacc.c:1646  */
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
#line 9594 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 652:
#line 3560 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 9602 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 653:
#line 3564 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 9610 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 654:
#line 3570 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = socket_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 9618 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 655:
#line 3575 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SOCKET_TRANSPARENT; }
#line 9624 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 656:
#line 3578 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 9630 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 657:
#line 3579 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 9636 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 658:
#line 3582 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 9642 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 659:
#line 3583 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 9648 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 660:
#line 3587 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 9656 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 661:
#line 3593 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 9665 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 662:
#line 3598 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 9674 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 663:
#line 3603 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 9682 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 664:
#line 3608 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 9688 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 665:
#line 3609 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 9694 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 666:
#line 3613 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 9702 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 667:
#line 3617 "parser_bison.y" /* yacc.c:1646  */
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
#line 9724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 668:
#line 3636 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 9730 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 669:
#line 3637 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 9736 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 670:
#line 3638 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 9742 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 671:
#line 3642 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1, NFPROTO_UNSPEC);
			}
#line 9750 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 672:
#line 3646 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val), NFPROTO_UNSPEC);
			}
#line 9758 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 673:
#line 3650 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 9766 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 674:
#line 3655 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 9772 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 675:
#line 3656 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 9778 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 676:
#line 3659 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9784 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 677:
#line 3660 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9790 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 678:
#line 3661 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_MARK; }
#line 9796 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 679:
#line 3662 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATE; }
#line 9802 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 680:
#line 3663 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 9808 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 681:
#line 3664 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 9814 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 682:
#line 3665 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 9820 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 683:
#line 3666 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 9826 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 684:
#line 3667 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9832 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 685:
#line 3668 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9838 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 686:
#line 3669 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9844 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 687:
#line 3670 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9850 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 688:
#line 3671 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 9856 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 689:
#line 3672 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 9862 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 691:
#line 3676 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9868 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 692:
#line 3677 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 693:
#line 3678 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9880 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 694:
#line 3679 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9886 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 695:
#line 3680 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 696:
#line 3681 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 698:
#line 3685 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 699:
#line 3686 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9910 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 700:
#line 3689 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 9916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 701:
#line 3690 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 9922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 702:
#line 3691 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 9928 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 703:
#line 3692 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 9934 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 706:
#line 3700 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9944 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 707:
#line 3706 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 708:
#line 3714 "parser_bison.y" /* yacc.c:1646  */
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
#line 9971 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 709:
#line 3727 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 9979 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 710:
#line 3733 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].expr)->ops->type == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9990 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 727:
#line 3760 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 10001 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 728:
#line 3768 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 10007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 729:
#line 3769 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 10013 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 730:
#line 3770 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 10019 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 731:
#line 3774 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 10027 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 732:
#line 3779 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 10033 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 733:
#line 3780 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 10039 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 734:
#line 3781 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 10045 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 735:
#line 3785 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 10053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 736:
#line 3790 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_VID; }
#line 10059 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 737:
#line 3791 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_CFI; }
#line 10065 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 738:
#line 3792 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_PCP; }
#line 10071 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 739:
#line 3793 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 10077 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 740:
#line 3797 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 10085 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 741:
#line 3802 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HRD; }
#line 10091 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 742:
#line 3803 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PRO; }
#line 10097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 743:
#line 3804 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HLN; }
#line 10103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 744:
#line 3805 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PLN; }
#line 10109 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 745:
#line 3806 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_OP; }
#line 10115 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 746:
#line 3810 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 10123 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 747:
#line 3815 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_VERSION; }
#line 10129 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 748:
#line 3816 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 10135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 749:
#line 3817 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DSCP; }
#line 10141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 750:
#line 3818 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ECN; }
#line 10147 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 751:
#line 3819 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 10153 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 752:
#line 3820 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ID; }
#line 10159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 753:
#line 3821 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 10165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 754:
#line 3822 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_TTL; }
#line 10171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 755:
#line 3823 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 10177 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 756:
#line 3824 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 10183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 757:
#line 3825 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_SADDR; }
#line 10189 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 758:
#line 3826 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DADDR; }
#line 10195 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 759:
#line 3830 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 10203 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 760:
#line 3835 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 10209 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 761:
#line 3836 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 10215 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 762:
#line 3837 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 10221 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 763:
#line 3838 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_ID; }
#line 10227 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 764:
#line 3839 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 10233 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 765:
#line 3840 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 10239 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 766:
#line 3841 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 10245 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 767:
#line 3845 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 10253 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 768:
#line 3850 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 10259 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 769:
#line 3851 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 10265 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 770:
#line 3852 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_ECN; }
#line 10271 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 771:
#line 3853 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 10277 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 772:
#line 3854 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 10283 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 773:
#line 3855 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 10289 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 774:
#line 3856 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 10295 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 775:
#line 3857 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 10301 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 776:
#line 3858 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 10307 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 777:
#line 3861 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 10315 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 778:
#line 3866 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 10321 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 779:
#line 3867 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 10327 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 780:
#line 3868 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 10333 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 781:
#line 3869 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 10339 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 782:
#line 3870 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 10345 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 783:
#line 3871 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 10351 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 784:
#line 3872 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 10357 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 785:
#line 3873 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 10363 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 786:
#line 3877 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 10371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 787:
#line 3882 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 10377 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 788:
#line 3883 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 10383 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 789:
#line 3884 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 10389 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 790:
#line 3885 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SPI; }
#line 10395 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 791:
#line 3886 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 10401 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 792:
#line 3890 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 10409 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 793:
#line 3895 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SPI; }
#line 10415 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 794:
#line 3896 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 10421 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 795:
#line 3900 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 10429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 796:
#line 3905 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 10435 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 797:
#line 3906 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 10441 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 798:
#line 3907 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_CPI; }
#line 10447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 799:
#line 3911 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 10455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 800:
#line 3916 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 10461 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 801:
#line 3917 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 10467 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 802:
#line 3918 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 10473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 803:
#line 3919 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 10479 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 804:
#line 3923 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 10487 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 805:
#line 3928 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 10493 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 806:
#line 3929 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 10499 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 807:
#line 3930 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 10505 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 808:
#line 3931 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 10511 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 809:
#line 3935 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 10519 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 810:
#line 3939 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 10527 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 811:
#line 3943 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 10536 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 812:
#line 3949 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 10542 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 813:
#line 3950 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 10548 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 814:
#line 3951 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 10554 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 815:
#line 3952 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 10560 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 816:
#line 3953 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 10566 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 817:
#line 3954 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 10572 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 818:
#line 3955 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 10578 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 819:
#line 3956 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 10584 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 820:
#line 3957 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 10590 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 821:
#line 3958 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 10596 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 822:
#line 3961 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 10602 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 823:
#line 3962 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 10608 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 824:
#line 3963 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 10614 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 825:
#line 3964 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 10620 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 826:
#line 3965 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 10626 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 827:
#line 3966 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 10632 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 828:
#line 3967 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 10638 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 829:
#line 3968 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 10644 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 830:
#line 3969 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 10650 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 831:
#line 3970 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 10656 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 832:
#line 3971 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 10662 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 833:
#line 3972 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 10668 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 834:
#line 3975 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 10674 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 835:
#line 3976 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 10680 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 836:
#line 3977 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 10686 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 837:
#line 3978 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 10692 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 838:
#line 3979 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 10698 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 839:
#line 3980 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 10704 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 840:
#line 3981 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 10710 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 841:
#line 3982 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 10716 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 842:
#line 3986 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 10724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 843:
#line 3991 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 10730 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 844:
#line 3992 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 10736 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 845:
#line 3993 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 10742 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 846:
#line 3997 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 10750 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 847:
#line 4002 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 10756 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 848:
#line 4003 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 10762 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 849:
#line 4004 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 10768 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 850:
#line 4005 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 10774 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 859:
#line 4019 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 10782 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 860:
#line 4024 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 10788 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 861:
#line 4025 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 10794 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 862:
#line 4029 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 10802 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 863:
#line 4034 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 10808 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 864:
#line 4035 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 10814 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 865:
#line 4036 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_TYPE; }
#line 10820 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 866:
#line 4037 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 10826 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 867:
#line 4041 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 10834 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 868:
#line 4047 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 10842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 869:
#line 4053 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 10850 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 870:
#line 4058 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 10856 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 871:
#line 4062 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 10864 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 872:
#line 4067 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 10870 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 873:
#line 4068 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 10876 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 874:
#line 4069 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_TAG; }
#line 10882 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 875:
#line 4071 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 10890 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 876:
#line 4077 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 10898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 877:
#line 4082 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 10904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 878:
#line 4083 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 10910 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 879:
#line 4084 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 10916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 880:
#line 4085 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 10922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 881:
#line 4086 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 10928 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 882:
#line 4087 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_ID; }
#line 10934 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 883:
#line 4091 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 10942 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 884:
#line 4096 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 10948 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 885:
#line 4097 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 10954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 886:
#line 4101 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 10962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 887:
#line 4106 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 10968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 888:
#line 4107 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 10974 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 889:
#line 4108 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_TYPE; }
#line 10980 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 890:
#line 4109 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 10986 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 891:
#line 4110 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 10992 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 892:
#line 4114 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 11008 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 893:
#line 4127 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 11014 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 894:
#line 4128 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 11020 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 895:
#line 4129 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 11026 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 896:
#line 4130 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 11032 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 897:
#line 4131 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_MH; }
#line 11038 "parser_bison.c" /* yacc.c:1646  */
    break;


#line 11042 "parser_bison.c" /* yacc.c:1646  */
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
#line 4134 "parser_bison.y" /* yacc.c:1906  */

