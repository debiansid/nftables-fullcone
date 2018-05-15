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
    HOOK = 285,
    DEVICE = 286,
    DEVICES = 287,
    TABLE = 288,
    TABLES = 289,
    CHAIN = 290,
    CHAINS = 291,
    RULE = 292,
    RULES = 293,
    SETS = 294,
    SET = 295,
    ELEMENT = 296,
    MAP = 297,
    MAPS = 298,
    FLOWTABLE = 299,
    HANDLE = 300,
    RULESET = 301,
    TRACE = 302,
    INET = 303,
    NETDEV = 304,
    ADD = 305,
    UPDATE = 306,
    REPLACE = 307,
    CREATE = 308,
    INSERT = 309,
    DELETE = 310,
    GET = 311,
    LIST = 312,
    RESET = 313,
    FLUSH = 314,
    RENAME = 315,
    DESCRIBE = 316,
    IMPORT = 317,
    EXPORT = 318,
    MONITOR = 319,
    ALL = 320,
    ACCEPT = 321,
    DROP = 322,
    CONTINUE = 323,
    JUMP = 324,
    GOTO = 325,
    RETURN = 326,
    TO = 327,
    CONSTANT = 328,
    INTERVAL = 329,
    AUTOMERGE = 330,
    TIMEOUT = 331,
    GC_INTERVAL = 332,
    ELEMENTS = 333,
    POLICY = 334,
    MEMORY = 335,
    PERFORMANCE = 336,
    SIZE = 337,
    FLOW = 338,
    OFFLOAD = 339,
    METER = 340,
    METERS = 341,
    FLOWTABLES = 342,
    NUM = 343,
    STRING = 344,
    QUOTED_STRING = 345,
    ASTERISK_STRING = 346,
    LL_HDR = 347,
    NETWORK_HDR = 348,
    TRANSPORT_HDR = 349,
    BRIDGE = 350,
    ETHER = 351,
    SADDR = 352,
    DADDR = 353,
    TYPE = 354,
    VLAN = 355,
    ID = 356,
    CFI = 357,
    PCP = 358,
    ARP = 359,
    HTYPE = 360,
    PTYPE = 361,
    HLEN = 362,
    PLEN = 363,
    OPERATION = 364,
    IP = 365,
    HDRVERSION = 366,
    HDRLENGTH = 367,
    DSCP = 368,
    ECN = 369,
    LENGTH = 370,
    FRAG_OFF = 371,
    TTL = 372,
    PROTOCOL = 373,
    CHECKSUM = 374,
    ICMP = 375,
    CODE = 376,
    SEQUENCE = 377,
    GATEWAY = 378,
    MTU = 379,
    OPTIONS = 380,
    IP6 = 381,
    PRIORITY = 382,
    FLOWLABEL = 383,
    NEXTHDR = 384,
    HOPLIMIT = 385,
    ICMP6 = 386,
    PPTR = 387,
    MAXDELAY = 388,
    AH = 389,
    RESERVED = 390,
    SPI = 391,
    ESP = 392,
    COMP = 393,
    FLAGS = 394,
    CPI = 395,
    UDP = 396,
    SPORT = 397,
    DPORT = 398,
    UDPLITE = 399,
    CSUMCOV = 400,
    TCP = 401,
    ACKSEQ = 402,
    DOFF = 403,
    WINDOW = 404,
    URGPTR = 405,
    OPTION = 406,
    ECHO = 407,
    EOL = 408,
    MAXSEG = 409,
    NOOP = 410,
    SACK = 411,
    SACK0 = 412,
    SACK1 = 413,
    SACK2 = 414,
    SACK3 = 415,
    SACK_PERMITTED = 416,
    TIMESTAMP = 417,
    KIND = 418,
    COUNT = 419,
    LEFT = 420,
    RIGHT = 421,
    TSVAL = 422,
    TSECR = 423,
    DCCP = 424,
    SCTP = 425,
    VTAG = 426,
    RT = 427,
    RT0 = 428,
    RT2 = 429,
    RT4 = 430,
    SEG_LEFT = 431,
    ADDR = 432,
    LAST_ENT = 433,
    TAG = 434,
    SID = 435,
    HBH = 436,
    FRAG = 437,
    RESERVED2 = 438,
    MORE_FRAGMENTS = 439,
    DST = 440,
    MH = 441,
    META = 442,
    MARK = 443,
    IIF = 444,
    IIFNAME = 445,
    IIFTYPE = 446,
    OIF = 447,
    OIFNAME = 448,
    OIFTYPE = 449,
    SKUID = 450,
    SKGID = 451,
    NFTRACE = 452,
    RTCLASSID = 453,
    IBRIPORT = 454,
    OBRIPORT = 455,
    IBRIDGENAME = 456,
    OBRIDGENAME = 457,
    PKTTYPE = 458,
    CPU = 459,
    IIFGROUP = 460,
    OIFGROUP = 461,
    CGROUP = 462,
    CLASSID = 463,
    NEXTHOP = 464,
    CT = 465,
    L3PROTOCOL = 466,
    PROTO_SRC = 467,
    PROTO_DST = 468,
    ZONE = 469,
    DIRECTION = 470,
    EVENT = 471,
    EXPIRATION = 472,
    HELPER = 473,
    LABEL = 474,
    STATE = 475,
    STATUS = 476,
    ORIGINAL = 477,
    REPLY = 478,
    COUNTER = 479,
    NAME = 480,
    PACKETS = 481,
    BYTES = 482,
    AVGPKT = 483,
    COUNTERS = 484,
    QUOTAS = 485,
    LIMITS = 486,
    HELPERS = 487,
    LOG = 488,
    PREFIX = 489,
    GROUP = 490,
    SNAPLEN = 491,
    QUEUE_THRESHOLD = 492,
    LEVEL = 493,
    LIMIT = 494,
    RATE = 495,
    BURST = 496,
    OVER = 497,
    UNTIL = 498,
    QUOTA = 499,
    USED = 500,
    NANOSECOND = 501,
    MICROSECOND = 502,
    MILLISECOND = 503,
    SECOND = 504,
    MINUTE = 505,
    HOUR = 506,
    DAY = 507,
    WEEK = 508,
    _REJECT = 509,
    WITH = 510,
    ICMPX = 511,
    SNAT = 512,
    DNAT = 513,
    MASQUERADE = 514,
    REDIRECT = 515,
    RANDOM = 516,
    FULLY_RANDOM = 517,
    PERSISTENT = 518,
    QUEUE = 519,
    QUEUENUM = 520,
    BYPASS = 521,
    FANOUT = 522,
    DUP = 523,
    FWD = 524,
    NUMGEN = 525,
    INC = 526,
    MOD = 527,
    OFFSET = 528,
    JHASH = 529,
    SYMHASH = 530,
    SEED = 531,
    POSITION = 532,
    INDEX = 533,
    COMMENT = 534,
    XML = 535,
    JSON = 536,
    VM = 537,
    NOTRACK = 538,
    EXISTS = 539,
    MISSING = 540,
    EXTHDR = 541
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
#define HOOK 285
#define DEVICE 286
#define DEVICES 287
#define TABLE 288
#define TABLES 289
#define CHAIN 290
#define CHAINS 291
#define RULE 292
#define RULES 293
#define SETS 294
#define SET 295
#define ELEMENT 296
#define MAP 297
#define MAPS 298
#define FLOWTABLE 299
#define HANDLE 300
#define RULESET 301
#define TRACE 302
#define INET 303
#define NETDEV 304
#define ADD 305
#define UPDATE 306
#define REPLACE 307
#define CREATE 308
#define INSERT 309
#define DELETE 310
#define GET 311
#define LIST 312
#define RESET 313
#define FLUSH 314
#define RENAME 315
#define DESCRIBE 316
#define IMPORT 317
#define EXPORT 318
#define MONITOR 319
#define ALL 320
#define ACCEPT 321
#define DROP 322
#define CONTINUE 323
#define JUMP 324
#define GOTO 325
#define RETURN 326
#define TO 327
#define CONSTANT 328
#define INTERVAL 329
#define AUTOMERGE 330
#define TIMEOUT 331
#define GC_INTERVAL 332
#define ELEMENTS 333
#define POLICY 334
#define MEMORY 335
#define PERFORMANCE 336
#define SIZE 337
#define FLOW 338
#define OFFLOAD 339
#define METER 340
#define METERS 341
#define FLOWTABLES 342
#define NUM 343
#define STRING 344
#define QUOTED_STRING 345
#define ASTERISK_STRING 346
#define LL_HDR 347
#define NETWORK_HDR 348
#define TRANSPORT_HDR 349
#define BRIDGE 350
#define ETHER 351
#define SADDR 352
#define DADDR 353
#define TYPE 354
#define VLAN 355
#define ID 356
#define CFI 357
#define PCP 358
#define ARP 359
#define HTYPE 360
#define PTYPE 361
#define HLEN 362
#define PLEN 363
#define OPERATION 364
#define IP 365
#define HDRVERSION 366
#define HDRLENGTH 367
#define DSCP 368
#define ECN 369
#define LENGTH 370
#define FRAG_OFF 371
#define TTL 372
#define PROTOCOL 373
#define CHECKSUM 374
#define ICMP 375
#define CODE 376
#define SEQUENCE 377
#define GATEWAY 378
#define MTU 379
#define OPTIONS 380
#define IP6 381
#define PRIORITY 382
#define FLOWLABEL 383
#define NEXTHDR 384
#define HOPLIMIT 385
#define ICMP6 386
#define PPTR 387
#define MAXDELAY 388
#define AH 389
#define RESERVED 390
#define SPI 391
#define ESP 392
#define COMP 393
#define FLAGS 394
#define CPI 395
#define UDP 396
#define SPORT 397
#define DPORT 398
#define UDPLITE 399
#define CSUMCOV 400
#define TCP 401
#define ACKSEQ 402
#define DOFF 403
#define WINDOW 404
#define URGPTR 405
#define OPTION 406
#define ECHO 407
#define EOL 408
#define MAXSEG 409
#define NOOP 410
#define SACK 411
#define SACK0 412
#define SACK1 413
#define SACK2 414
#define SACK3 415
#define SACK_PERMITTED 416
#define TIMESTAMP 417
#define KIND 418
#define COUNT 419
#define LEFT 420
#define RIGHT 421
#define TSVAL 422
#define TSECR 423
#define DCCP 424
#define SCTP 425
#define VTAG 426
#define RT 427
#define RT0 428
#define RT2 429
#define RT4 430
#define SEG_LEFT 431
#define ADDR 432
#define LAST_ENT 433
#define TAG 434
#define SID 435
#define HBH 436
#define FRAG 437
#define RESERVED2 438
#define MORE_FRAGMENTS 439
#define DST 440
#define MH 441
#define META 442
#define MARK 443
#define IIF 444
#define IIFNAME 445
#define IIFTYPE 446
#define OIF 447
#define OIFNAME 448
#define OIFTYPE 449
#define SKUID 450
#define SKGID 451
#define NFTRACE 452
#define RTCLASSID 453
#define IBRIPORT 454
#define OBRIPORT 455
#define IBRIDGENAME 456
#define OBRIDGENAME 457
#define PKTTYPE 458
#define CPU 459
#define IIFGROUP 460
#define OIFGROUP 461
#define CGROUP 462
#define CLASSID 463
#define NEXTHOP 464
#define CT 465
#define L3PROTOCOL 466
#define PROTO_SRC 467
#define PROTO_DST 468
#define ZONE 469
#define DIRECTION 470
#define EVENT 471
#define EXPIRATION 472
#define HELPER 473
#define LABEL 474
#define STATE 475
#define STATUS 476
#define ORIGINAL 477
#define REPLY 478
#define COUNTER 479
#define NAME 480
#define PACKETS 481
#define BYTES 482
#define AVGPKT 483
#define COUNTERS 484
#define QUOTAS 485
#define LIMITS 486
#define HELPERS 487
#define LOG 488
#define PREFIX 489
#define GROUP 490
#define SNAPLEN 491
#define QUEUE_THRESHOLD 492
#define LEVEL 493
#define LIMIT 494
#define RATE 495
#define BURST 496
#define OVER 497
#define UNTIL 498
#define QUOTA 499
#define USED 500
#define NANOSECOND 501
#define MICROSECOND 502
#define MILLISECOND 503
#define SECOND 504
#define MINUTE 505
#define HOUR 506
#define DAY 507
#define WEEK 508
#define _REJECT 509
#define WITH 510
#define ICMPX 511
#define SNAT 512
#define DNAT 513
#define MASQUERADE 514
#define REDIRECT 515
#define RANDOM 516
#define FULLY_RANDOM 517
#define PERSISTENT 518
#define QUEUE 519
#define QUEUENUM 520
#define BYPASS 521
#define FANOUT 522
#define DUP 523
#define FWD 524
#define NUMGEN 525
#define INC 526
#define MOD 527
#define OFFSET 528
#define JHASH 529
#define SYMHASH 530
#define SEED 531
#define POSITION 532
#define INDEX 533
#define COMMENT 534
#define XML 535
#define JSON 536
#define VM 537
#define NOTRACK 538
#define EXISTS 539
#define MISSING 540
#define EXTHDR 541

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

#line 814 "parser_bison.c" /* yacc.c:355  */
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

#line 844 "parser_bison.c" /* yacc.c:358  */

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
#define YYLAST   4960

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  296
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  291
/* YYNRULES -- Number of rules.  */
#define YYNRULES  889
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1398

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   541

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   291,     2,     2,     2,
     292,   293,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   287,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   294,     2,   295,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   288,   290,   289,     2,     2,     2,     2,
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
     285,   286
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   738,   738,   739,   757,   758,   761,   762,   765,   773,
     787,   794,   805,   813,   814,   815,   816,   848,   849,   850,
     851,   852,   853,   854,   855,   856,   857,   858,   859,   860,
     861,   862,   865,   869,   876,   880,   888,   892,   896,   903,
     910,   914,   921,   930,   934,   938,   943,   949,   955,   959,
     966,   970,   978,   985,   992,   996,  1003,  1012,  1016,  1020,
    1024,  1030,  1036,  1040,  1044,  1048,  1052,  1056,  1060,  1064,
    1068,  1072,  1076,  1080,  1084,  1088,  1092,  1096,  1100,  1106,
    1112,  1116,  1120,  1124,  1128,  1132,  1136,  1140,  1144,  1148,
    1152,  1156,  1160,  1164,  1168,  1172,  1176,  1180,  1184,  1188,
    1192,  1196,  1200,  1204,  1208,  1212,  1218,  1222,  1226,  1230,
    1234,  1238,  1244,  1248,  1252,  1256,  1260,  1264,  1268,  1274,
    1281,  1287,  1295,  1301,  1309,  1318,  1319,  1322,  1323,  1324,
    1325,  1326,  1327,  1328,  1329,  1332,  1333,  1336,  1337,  1338,
    1341,  1350,  1356,  1370,  1371,  1372,  1373,  1374,  1385,  1395,
    1406,  1416,  1427,  1438,  1447,  1461,  1467,  1468,  1469,  1470,
    1471,  1472,  1480,  1485,  1486,  1487,  1488,  1493,  1498,  1503,
    1508,  1513,  1518,  1521,  1522,  1525,  1529,  1532,  1533,  1534,
    1538,  1543,  1544,  1545,  1546,  1551,  1562,  1571,  1580,  1589,
    1594,  1599,  1602,  1606,  1612,  1613,  1617,  1622,  1623,  1624,
    1625,  1638,  1644,  1651,  1656,  1661,  1664,  1672,  1686,  1687,
    1707,  1712,  1713,  1714,  1715,  1722,  1723,  1724,  1725,  1732,
    1733,  1734,  1735,  1741,  1742,  1743,  1744,  1751,  1752,  1753,
    1754,  1755,  1758,  1786,  1787,  1790,  1791,  1794,  1805,  1806,
    1809,  1812,  1813,  1814,  1817,  1832,  1833,  1836,  1837,  1838,
    1839,  1840,  1841,  1844,  1853,  1862,  1870,  1878,  1886,  1894,
    1902,  1911,  1918,  1925,  1933,  1941,  1949,  1957,  1965,  1973,
    1977,  1982,  1990,  1997,  2004,  2016,  2020,  2027,  2031,  2037,
    2049,  2055,  2062,  2063,  2064,  2065,  2066,  2067,  2068,  2069,
    2070,  2071,  2072,  2073,  2074,  2075,  2076,  2077,  2078,  2079,
    2080,  2083,  2087,  2093,  2099,  2104,  2113,  2118,  2123,  2126,
    2132,  2133,  2135,  2139,  2147,  2151,  2154,  2158,  2164,  2165,
    2168,  2174,  2178,  2181,  2186,  2191,  2196,  2201,  2206,  2212,
    2240,  2244,  2248,  2252,  2256,  2262,  2266,  2269,  2273,  2279,
    2288,  2307,  2315,  2316,  2317,  2320,  2321,  2324,  2325,  2340,
    2356,  2364,  2365,  2366,  2369,  2370,  2371,  2372,  2387,  2388,
    2389,  2390,  2391,  2394,  2397,  2404,  2408,  2419,  2430,  2440,
    2446,  2449,  2450,  2453,  2454,  2455,  2456,  2457,  2458,  2459,
    2460,  2461,  2462,  2465,  2466,  2470,  2476,  2477,  2483,  2484,
    2490,  2491,  2497,  2500,  2501,  2520,  2521,  2524,  2528,  2531,
    2537,  2543,  2554,  2555,  2556,  2559,  2560,  2561,  2564,  2568,
    2572,  2577,  2582,  2586,  2590,  2596,  2597,  2600,  2603,  2607,
    2612,  2618,  2619,  2622,  2625,  2629,  2633,  2637,  2642,  2649,
    2654,  2662,  2669,  2670,  2676,  2677,  2678,  2681,  2682,  2685,
    2691,  2695,  2698,  2703,  2709,  2710,  2716,  2717,  2720,  2721,
    2724,  2730,  2737,  2746,  2747,  2750,  2759,  2766,  2769,  2775,
    2779,  2782,  2788,  2797,  2808,  2814,  2832,  2833,  2840,  2849,
    2860,  2861,  2862,  2863,  2864,  2865,  2866,  2867,  2868,  2869,
    2870,  2871,  2874,  2897,  2898,  2899,  2902,  2903,  2904,  2905,
    2906,  2909,  2913,  2916,  2917,  2921,  2927,  2928,  2934,  2935,
    2941,  2942,  2948,  2951,  2952,  2971,  2977,  2983,  2994,  2995,
    2996,  2999,  3005,  3006,  3007,  3010,  3017,  3022,  3027,  3030,
    3034,  3038,  3044,  3045,  3052,  3058,  3059,  3062,  3068,  3072,
    3075,  3079,  3085,  3086,  3089,  3090,  3093,  3094,  3097,  3108,
    3116,  3137,  3145,  3148,  3149,  3152,  3167,  3174,  3179,  3190,
    3212,  3220,  3224,  3228,  3232,  3238,  3244,  3252,  3253,  3254,
    3257,  3258,  3262,  3268,  3269,  3275,  3276,  3282,  3283,  3289,
    3292,  3293,  3312,  3313,  3316,  3324,  3325,  3326,  3327,  3328,
    3329,  3330,  3331,  3332,  3333,  3334,  3335,  3338,  3339,  3340,
    3341,  3342,  3349,  3356,  3363,  3370,  3377,  3384,  3391,  3398,
    3405,  3412,  3421,  3422,  3423,  3424,  3425,  3426,  3429,  3433,
    3437,  3441,  3445,  3449,  3455,  3459,  3463,  3479,  3480,  3483,
    3484,  3485,  3486,  3489,  3490,  3491,  3492,  3493,  3494,  3495,
    3496,  3497,  3498,  3499,  3500,  3501,  3502,  3503,  3504,  3505,
    3506,  3507,  3508,  3511,  3515,  3519,  3533,  3537,  3543,  3544,
    3547,  3548,  3551,  3557,  3562,  3567,  3573,  3574,  3577,  3581,
    3601,  3602,  3603,  3606,  3610,  3614,  3620,  3621,  3624,  3625,
    3626,  3627,  3628,  3629,  3630,  3631,  3632,  3633,  3634,  3635,
    3636,  3637,  3638,  3641,  3642,  3643,  3644,  3645,  3646,  3647,
    3650,  3651,  3654,  3655,  3656,  3657,  3660,  3661,  3664,  3670,
    3678,  3691,  3697,  3706,  3707,  3708,  3709,  3710,  3711,  3712,
    3713,  3714,  3715,  3716,  3717,  3718,  3719,  3720,  3721,  3724,
    3733,  3734,  3735,  3738,  3744,  3745,  3746,  3749,  3755,  3756,
    3757,  3758,  3761,  3767,  3768,  3769,  3770,  3771,  3774,  3780,
    3781,  3782,  3783,  3784,  3785,  3786,  3787,  3788,  3789,  3790,
    3791,  3794,  3800,  3801,  3802,  3803,  3804,  3805,  3806,  3809,
    3815,  3816,  3817,  3818,  3819,  3820,  3821,  3822,  3823,  3825,
    3831,  3832,  3833,  3834,  3835,  3836,  3837,  3838,  3841,  3847,
    3848,  3849,  3850,  3851,  3854,  3860,  3861,  3864,  3870,  3871,
    3872,  3875,  3881,  3882,  3883,  3884,  3887,  3893,  3894,  3895,
    3896,  3899,  3903,  3907,  3914,  3915,  3916,  3917,  3918,  3919,
    3920,  3921,  3922,  3923,  3926,  3927,  3928,  3929,  3930,  3931,
    3932,  3933,  3934,  3935,  3936,  3937,  3940,  3941,  3942,  3943,
    3944,  3945,  3946,  3947,  3950,  3956,  3957,  3958,  3961,  3967,
    3968,  3969,  3970,  3973,  3974,  3975,  3976,  3977,  3978,  3979,
    3980,  3983,  3989,  3990,  3993,  3999,  4000,  4001,  4002,  4005,
    4011,  4017,  4023,  4026,  4032,  4033,  4034,  4035,  4041,  4047,
    4048,  4049,  4050,  4051,  4052,  4055,  4061,  4062,  4065,  4071,
    4072,  4073,  4074,  4075,  4078,  4092,  4093,  4094,  4095,  4096
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
  "\"hook\"", "\"device\"", "\"devices\"", "\"table\"", "\"tables\"",
  "\"chain\"", "\"chains\"", "\"rule\"", "\"rules\"", "\"sets\"",
  "\"set\"", "\"element\"", "\"map\"", "\"maps\"", "\"flowtable\"",
  "\"handle\"", "\"ruleset\"", "\"trace\"", "\"inet\"", "\"netdev\"",
  "\"add\"", "\"update\"", "\"replace\"", "\"create\"", "\"insert\"",
  "\"delete\"", "\"get\"", "\"list\"", "\"reset\"", "\"flush\"",
  "\"rename\"", "\"describe\"", "\"import\"", "\"export\"", "\"monitor\"",
  "\"all\"", "\"accept\"", "\"drop\"", "\"continue\"", "\"jump\"",
  "\"goto\"", "\"return\"", "\"to\"", "\"constant\"", "\"interval\"",
  "\"auto-merge\"", "\"timeout\"", "\"gc-interval\"", "\"elements\"",
  "\"policy\"", "\"memory\"", "\"performance\"", "\"size\"", "\"flow\"",
  "\"offload\"", "\"meter\"", "\"meters\"", "\"flowtables\"", "\"number\"",
  "\"string\"", "\"quoted string\"", "\"string with a trailing asterisk\"",
  "\"ll\"", "\"nh\"", "\"th\"", "\"bridge\"", "\"ether\"", "\"saddr\"",
  "\"daddr\"", "\"type\"", "\"vlan\"", "\"id\"", "\"cfi\"", "\"pcp\"",
  "\"arp\"", "\"htype\"", "\"ptype\"", "\"hlen\"", "\"plen\"",
  "\"operation\"", "\"ip\"", "\"version\"", "\"hdrlength\"", "\"dscp\"",
  "\"ecn\"", "\"length\"", "\"frag-off\"", "\"ttl\"", "\"protocol\"",
  "\"checksum\"", "\"icmp\"", "\"code\"", "\"seq\"", "\"gateway\"",
  "\"mtu\"", "\"options\"", "\"ip6\"", "\"priority\"", "\"flowlabel\"",
  "\"nexthdr\"", "\"hoplimit\"", "\"icmpv6\"", "\"param-problem\"",
  "\"max-delay\"", "\"ah\"", "\"reserved\"", "\"spi\"", "\"esp\"",
  "\"comp\"", "\"flags\"", "\"cpi\"", "\"udp\"", "\"sport\"", "\"dport\"",
  "\"udplite\"", "\"csumcov\"", "\"tcp\"", "\"ackseq\"", "\"doff\"",
  "\"window\"", "\"urgptr\"", "\"option\"", "\"echo\"", "\"eol\"",
  "\"maxseg\"", "\"noop\"", "\"sack\"", "\"sack0\"", "\"sack1\"",
  "\"sack2\"", "\"sack3\"", "\"sack-permitted\"", "\"timestamp\"",
  "\"kind\"", "\"count\"", "\"left\"", "\"right\"", "\"tsval\"",
  "\"tsecr\"", "\"dccp\"", "\"sctp\"", "\"vtag\"", "\"rt\"", "\"rt0\"",
  "\"rt2\"", "\"srh\"", "\"seg-left\"", "\"addr\"", "\"last-entry\"",
  "\"tag\"", "\"sid\"", "\"hbh\"", "\"frag\"", "\"reserved2\"",
  "\"more-fragments\"", "\"dst\"", "\"mh\"", "\"meta\"", "\"mark\"",
  "\"iif\"", "\"iifname\"", "\"iiftype\"", "\"oif\"", "\"oifname\"",
  "\"oiftype\"", "\"skuid\"", "\"skgid\"", "\"nftrace\"", "\"rtclassid\"",
  "\"ibriport\"", "\"obriport\"", "\"ibrname\"", "\"obrname\"",
  "\"pkttype\"", "\"cpu\"", "\"iifgroup\"", "\"oifgroup\"", "\"cgroup\"",
  "\"classid\"", "\"nexthop\"", "\"ct\"", "\"l3proto\"", "\"proto-src\"",
  "\"proto-dst\"", "\"zone\"", "\"direction\"", "\"event\"",
  "\"expiration\"", "\"helper\"", "\"label\"", "\"state\"", "\"status\"",
  "\"original\"", "\"reply\"", "\"counter\"", "\"name\"", "\"packets\"",
  "\"bytes\"", "\"avgpkt\"", "\"counters\"", "\"quotas\"", "\"limits\"",
  "\"helpers\"", "\"log\"", "\"prefix\"", "\"group\"", "\"snaplen\"",
  "\"queue-threshold\"", "\"level\"", "\"limit\"", "\"rate\"", "\"burst\"",
  "\"over\"", "\"until\"", "\"quota\"", "\"used\"", "\"nanosecond\"",
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
  "verdict_map_list_member_expr", "counter_stmt", "counter_stmt_alloc",
  "counter_args", "counter_arg", "log_stmt", "log_stmt_alloc", "log_args",
  "log_arg", "level_type", "log_flags", "log_flags_tcp", "log_flag_tcp",
  "limit_stmt", "quota_mode", "quota_unit", "quota_used", "quota_stmt",
  "limit_mode", "limit_burst", "time_unit", "reject_stmt",
  "reject_stmt_alloc", "reject_opts", "nat_stmt", "nat_stmt_alloc",
  "primary_stmt_expr", "shift_stmt_expr", "and_stmt_expr",
  "exclusive_or_stmt_expr", "inclusive_or_stmt_expr", "basic_stmt_expr",
  "concat_stmt_expr", "map_stmt_expr_set", "map_stmt_expr",
  "prefix_stmt_expr", "range_stmt_expr", "wildcard_stmt_expr",
  "multiton_stmt_expr", "stmt_expr", "nat_stmt_args", "masq_stmt",
  "masq_stmt_alloc", "masq_stmt_args", "redir_stmt", "redir_stmt_alloc",
  "redir_stmt_arg", "dup_stmt", "fwd_stmt", "nf_nat_flags", "nf_nat_flag",
  "queue_stmt", "queue_stmt_alloc", "queue_stmt_args", "queue_stmt_arg",
  "queue_stmt_flags", "queue_stmt_flag", "set_elem_expr_stmt",
  "set_elem_expr_stmt_alloc", "set_stmt", "set_stmt_op", "map_stmt",
  "meter_stmt", "flow_stmt_legacy_alloc", "flow_stmt_opts",
  "flow_stmt_opt", "meter_stmt_alloc", "match_stmt", "variable_expr",
  "symbol_expr", "integer_expr", "primary_expr", "fib_expr", "fib_result",
  "fib_flag", "fib_tuple", "shift_expr", "and_expr", "exclusive_or_expr",
  "inclusive_or_expr", "basic_expr", "concat_expr", "prefix_rhs_expr",
  "range_rhs_expr", "wildcard_rhs_expr", "multiton_rhs_expr", "map_expr",
  "expr", "set_expr", "set_list_expr", "set_list_member_expr",
  "meter_key_expr", "meter_key_expr_alloc", "set_elem_expr",
  "set_elem_expr_alloc", "set_elem_options", "set_elem_option",
  "set_lhs_expr", "set_rhs_expr", "initializer_expr", "counter_config",
  "counter_obj", "quota_config", "quota_obj", "ct_obj_type",
  "ct_l4protoname", "ct_helper_config", "ct_obj_alloc", "limit_config",
  "limit_obj", "relational_expr", "list_rhs_expr", "rhs_expr",
  "shift_rhs_expr", "and_rhs_expr", "exclusive_or_rhs_expr",
  "inclusive_or_rhs_expr", "basic_rhs_expr", "concat_rhs_expr",
  "boolean_keys", "boolean_expr", "keyword_expr", "primary_rhs_expr",
  "relational_op", "verdict_expr", "meta_expr", "meta_key",
  "meta_key_qualified", "meta_key_unqualified", "meta_stmt", "offset_opt",
  "numgen_type", "numgen_expr", "hash_expr", "nf_key_proto", "rt_expr",
  "rt_key", "ct_expr", "ct_dir", "ct_key", "ct_key_dir",
  "ct_key_proto_field", "ct_key_dir_optional", "symbol_stmt_expr",
  "list_stmt_expr", "ct_stmt", "payload_stmt", "payload_expr",
  "payload_raw_expr", "payload_base_spec", "eth_hdr_expr", "eth_hdr_field",
  "vlan_hdr_expr", "vlan_hdr_field", "arp_hdr_expr", "arp_hdr_field",
  "ip_hdr_expr", "ip_hdr_field", "icmp_hdr_expr", "icmp_hdr_field",
  "ip6_hdr_expr", "ip6_hdr_field", "icmp6_hdr_expr", "icmp6_hdr_field",
  "auth_hdr_expr", "auth_hdr_field", "esp_hdr_expr", "esp_hdr_field",
  "comp_hdr_expr", "comp_hdr_field", "udp_hdr_expr", "udp_hdr_field",
  "udplite_hdr_expr", "udplite_hdr_field", "tcp_hdr_expr", "tcp_hdr_field",
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
     535,   536,   537,   538,   539,   540,   541,    61,   123,   125,
     124,    36,    40,    41,    91,    93
};
# endif

#define YYPACT_NINF -1073

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1073)))

#define YYTABLE_NINF -698

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1073,  4716, -1073,   368, -1073, -1073,    11,    42,    42,    42,
     783,   783,   783,   783,   783,   783,   783, -1073, -1073,  1171,
     166,  1044,   178,   349,   120,  1698,   285,   765,   197,  4182,
      38,    74,   162, -1073, -1073, -1073, -1073,    39,   783,   783,
     783, -1073, -1073, -1073,   545, -1073,    42, -1073,    42,    62,
    3868, -1073,   368, -1073,    43,    65,   368,    -6,    34,  3868,
      42, -1073,   -24, -1073,    42, -1073, -1073,   783, -1073,   783,
     783,   783,   783,   783,   783,   167,   783,   783,   783, -1073,
     783, -1073,   783,   783,   783,   783,   783,   783,   783,   205,
     783,   783,   783, -1073,   783, -1073,   783,   783,   783,   783,
    1005,   783,   783,   783,   783,   575,   783,   783,   783,   145,
     783,  1127,  1132,  1344,   783,   783, -1073,   783,  1356,  1538,
     783, -1073,   783,   783,   783,   783,   783,   309,   783, -1073,
     783, -1073,   568,   425, -1073, -1073, -1073, -1073,   535,   907,
     874,  1654,   836,   699,  1493,   235,   258,   352,   268,   397,
    1575,   103,   282,   919,   297,   303,   249,    79,   565,   188,
     431,  1941, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073,  2461,   206,  4057,   223,   791,    42,  4182, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,   439,
   -1073, -1073,   222, -1073, -1073,   439, -1073, -1073, -1073, -1073,
     806,   783,    42,   307,   306,   383, -1073, -1073, -1073, -1073,
     467,   493,   506, -1073, -1073, -1073,   587, -1073, -1073, -1073,
   -1073, -1073,    42,    42, -1073,   514,    42,  2212,  2461,   390,
   -1073,   -57,   207, -1073, -1073, -1073, -1073, -1073, -1073,   556,
     574, -1073,   618, -1073,   380,  3868, -1073, -1073, -1073, -1073,
     472, -1073,   418, -1073, -1073, -1073,   413, -1073,  2732, -1073,
      31, -1073,   158, -1073, -1073, -1073,   494, -1073,    82, -1073,
   -1073,   657, -1073, -1073, -1073,   687,   675,   696,   415, -1073,
     422, -1073,  3262, -1073, -1073, -1073,   683, -1073, -1073, -1073,
     691, -1073,  3632,  3632, -1073,   475,   477, -1073, -1073,   485,
   -1073, -1073, -1073,   491, -1073,   511,   732,  3868,    -6,    34,
   -1073,   -24, -1073, -1073,   783,   307,   306,   383,  3868,   213,
   -1073, -1073,   217, -1073, -1073, -1073,   221, -1073, -1073,   -24,
   -1073, -1073, -1073,   783,   225, -1073, -1073, -1073, -1073, -1073,
   -1073,   -24, -1073, -1073, -1073, -1073, -1073,   783, -1073, -1073,
   -1073, -1073, -1073,   783,   783, -1073, -1073, -1073,   753,   783,
   -1073,   783, -1073,   783, -1073,   783, -1073, -1073, -1073, -1073,
     783, -1073,   783, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
     783, -1073,    42, -1073, -1073, -1073, -1073,   781, -1073, -1073,
   -1073, -1073, -1073,   786,    56, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073,  1791, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073,    46, -1073, -1073,   512, -1073, -1073, -1073,
   -1073, -1073, -1073,   515, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073,  1172, -1073, -1073, -1073, -1073,   558,   101,   566,
     734, -1073, -1073, -1073, -1073, -1073, -1073, -1073,   561, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,   439,
   -1073, -1073,   761, -1073, -1073,   549, -1073, -1073, -1073, -1073,
     778, -1073, -1073, -1073, -1073, -1073,  4182, -1073, -1073,   846,
      -5,   833,   840,  1172,   854,  3469,  3469,   549,  3469,   817,
    3469,  4057, -1073,  3632,    37, -1073,   792, -1073, -1073,   826,
     828,   472, -1073,   366,   792,   845,   848,   850,   792,   418,
   -1073,   122, -1073,  3469, -1073, -1073,  2895,   535,   907,   874,
    1654, -1073,   699,   -12, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073,   787,   890,   910,   649,   395,   108, -1073, -1073,
   -1073, -1073, -1073,   937,   627,   941, -1073, -1073, -1073,   947,
   -1073, -1073, -1073, -1073, -1073,   955,   967, -1073,   951, -1073,
   -1073, -1073, -1073,   968, -1073,  3058, -1073,   968,  3469, -1073,
   -1073,   494, -1073,   971, -1073,    42,   658,    42,    35, -1073,
    4182,  4182,  4182,  4182,  4182,  4182,    41,  3632, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,   977, -1073,
     819,   969,   975,   710,   346,   994, -1073, -1073, -1073,  3333,
    3469,  3469,   368,   977, -1073,   368, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073,   717,   725,   726, -1073,   728,   735, -1073,
   -1073, -1073, -1073, -1073,   932,   938,   952, -1073, -1073,   956,
   -1073, -1073, -1073, -1073,   783, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073,   959,   425, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073,   757, -1073,   962,   964, -1073, -1073, -1073, -1073, -1073,
   -1073,   759, -1073, -1073,   972,   978,   766, -1073, -1073, -1073,
     768,   832, -1073, -1073,   979,    17,    82,    10,  1049,   792,
     980,  4182,  3469,  3469,  1023,  3469, -1073, -1073,   981, -1073,
      17,  1034, -1073, -1073,   618,   859,    10, -1073,   570,   994,
     618, -1073, -1073, -1073, -1073, -1073, -1073, -1073,   950,   450,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,   982,
     988,  1018,   990, -1073,  3469,  1073,  4307,  4564,  4307,  4307,
    4307,   992,  4307,  4307,    57,  3469,   968,  1540,  1540,  3469,
     627,  3469,   627, -1073, -1073,   609,  4182, -1073,  4182, -1073,
   -1073, -1073,   687,   675,   696, -1073,    42,   618, -1073, -1073,
    4564,  4564,  4564,  4564,  4564,  4564,  4564,  1002,  4564,  4564,
    3632, -1073, -1073, -1073, -1073, -1073,   623,  1981,   259,   500,
     208, -1073, -1073, -1073, -1073, -1073,   803, -1073, -1073, -1073,
   -1073, -1073, -1073,  1085, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073,   798,   799, -1073, -1073, -1073,   766,
     313,  1008, -1073, -1073,  1010,   124, -1073, -1073,   856, -1073,
    1013, -1073,    10, -1073, -1073,   811,  1049,  3868,    10, -1073,
   -1073,  3469, -1073,   140,   856,  3469, -1073,  4470, -1073,    10,
    3632, -1073, -1073, -1073, -1073,  1096, -1073,  1016,  1017, -1073,
    1019, -1073,  3469, -1073, -1073, -1073, -1073,   787,   890,   910,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073,   627, -1073,   627,   968, -1073,    55,  3868, -1073,  3726,
      54, -1073, -1073, -1073, -1073,   819,   969,   975, -1073, -1073,
   -1073, -1073,   818,    42,    42,    42,    42,  1024,   898,    42,
      42,    42, -1073, -1073, -1073,   368,   830,  1029, -1073, -1073,
   -1073,   368,   368,   368, -1073,  1013,  1013,   838,   822,  1031,
     356,   489, -1073, -1073, -1073,   368,  1013,   839,   356,   489,
   -1073, -1073, -1073,   368,  1040,   843, -1073, -1073, -1073,   873,
    2253,   408,   925,   246, -1073,  1047, -1073, -1073, -1073,  1052,
   -1073, -1073,   412, -1073,   784,   891,  1053, -1073, -1073, -1073,
   -1073,  4182,   844,    10, -1073,   784,   891, -1073, -1073,   618,
   -1073,   994, -1073,   450, -1073, -1073, -1073, -1073,   968,   968,
    4182, -1073,   857,  1138,   618, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073,    42, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073,  1117, -1073, -1073, -1073,   368,   368,
     -24, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073,   550, -1073, -1073, -1073, -1073,   665, -1073, -1073,   368,
     -24,   595,   665, -1073,  1026,   861, -1073, -1073, -1073, -1073,
   -1073,   579, -1073,   766,  1064,   783,   368, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073,   891,  1068, -1073,    17,  3868,
   -1073,   891, -1073, -1073, -1073,   880, -1073,   686,  3726, -1073,
     875,   882,   883,   889, -1073,   894,   895,   896,  1089, -1073,
   -1073, -1073,   356, -1073,   489, -1073, -1073, -1073,   498, -1073,
      99,  1099,   368,   368, -1073,  1067,   368, -1073, -1073,    -4,
   -1073,   900, -1073, -1073,   618, -1073, -1073, -1073, -1073,   902,
   -1073, -1073, -1073,  1160, -1073, -1073,   368,   368,   368,   550,
    1104, -1073,   368, -1073,    60, -1073, -1073, -1073,   322, -1073,
   -1073, -1073, -1073, -1073, -1073,  2525,   492,   943,   615, -1073,
     107,   939,   200,  1106,  1070, -1073, -1073, -1073, -1073, -1073,
   -1073,   106, -1073, -1073, -1073,   368,   368,   368,   368,   368,
    1045,   368, -1073, -1073, -1073,   368, -1073, -1073, -1073,   368,
   -1073, -1073, -1073, -1073,    99, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073,   368, -1073, -1073, -1073, -1073, -1073
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
     245,    27,     0,     0,   469,   241,   242,   243,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,   633,   634,   635,   636,   637,   638,   639,   640,
     641,   642,     0,     0,     0,     0,     0,     0,     0,    31,
     467,   466,   470,   471,   140,   480,   475,   615,   478,   479,
     476,   477,   472,   703,   704,   705,   706,   707,   708,   709,
     710,   711,   712,   713,   714,   715,   716,   717,   718,   473,
     843,   844,   845,   846,   847,   848,   849,   850,   474,     0,
     137,   138,     0,    28,   121,     0,    29,   123,   126,    30,
     127,   245,     0,    42,     0,   344,    16,    15,   253,   255,
       0,     0,     0,   271,   270,   272,     0,   453,   454,   608,
     609,   610,     0,     0,   613,   458,     0,     0,     0,   312,
     320,     0,   344,   364,   371,   372,   417,   423,   439,     0,
       0,   646,     7,    37,   277,   279,   280,   282,   302,   285,
     310,   288,   318,   289,   290,   291,   365,   292,     0,   295,
     416,   296,   422,   297,   298,   293,   437,   299,     0,   300,
     284,     0,   457,   283,   493,   496,   498,   500,   502,   503,
     512,   514,     0,   513,   464,   301,   615,   287,   294,   286,
     472,     8,     0,     0,    11,     0,     0,    36,   258,     0,
      40,   174,   173,     0,   261,     0,     0,     0,    48,    50,
     162,     0,   180,   196,   245,    56,     0,   344,     0,     0,
      62,    63,     0,    64,    65,    66,     0,    67,    68,     0,
      69,    71,   542,   245,     0,    72,    73,    77,    78,    74,
      75,     0,    80,   276,    81,    82,    83,   245,    84,    86,
     103,   102,    96,   245,   275,   100,    99,   101,     0,   245,
      89,   245,    87,   245,    90,   245,    93,    95,    92,   108,
     245,   106,   245,   109,   111,   112,   113,   114,   115,   118,
     245,   117,     0,   720,   721,   722,   468,     0,   486,   487,
     488,   489,   490,   492,     0,   724,   725,   726,   723,   731,
     728,   729,   730,   727,   733,   734,   735,   736,   737,   732,
     749,   750,   744,   739,   740,   741,   742,   743,   745,   746,
     747,   748,   738,   752,   755,   754,   753,   756,   757,   758,
     751,   767,   768,   760,   761,   762,   764,   763,   765,   766,
     759,   770,   775,   772,   771,   776,   774,   773,   777,   769,
     780,   783,   779,   781,   782,   778,   786,   785,   784,   788,
     789,   790,   787,   794,   795,   792,   793,   791,   800,   797,
     798,   799,   796,   812,   806,   809,   810,   804,   805,   807,
     808,   811,   813,     0,   801,   837,   835,   836,   834,   842,
     839,   840,   841,   838,   857,   656,   856,   662,   657,   855,
     858,   660,   661,     0,   658,   854,     0,   859,   862,   861,
     865,   864,   866,     0,   863,   853,   852,   851,   874,   871,
     869,   870,   872,   873,   868,   877,   876,   875,   881,   880,
     883,   879,   882,   878,   616,   619,   620,   621,   622,   614,
     617,   618,   676,   677,   669,   670,   668,   678,   679,   695,
     672,   681,   674,   675,   680,   671,   673,   666,   667,   693,
     692,   694,     0,   663,   682,   651,   650,     0,   512,     0,
       0,   886,   885,   887,   888,   889,   884,   465,     0,   120,
     139,   122,   128,   129,   131,   130,   133,   134,   132,   135,
     547,   263,     0,   539,    43,   353,   550,    46,   342,   343,
       0,   541,    44,   266,   267,   268,     0,   611,   612,     0,
       0,   616,   614,     0,   663,     0,     0,   353,     0,     0,
       0,     0,     6,     0,     0,   516,     0,   278,   281,     0,
       0,   311,   314,     0,     0,     0,     0,     0,     0,   319,
     321,     0,   363,     0,   401,   583,     0,   575,   578,   579,
     576,   582,   577,     0,   586,   584,   585,   581,   580,   572,
     573,   383,   386,   388,   390,   392,   393,   398,   405,   402,
     403,   404,   406,   408,   370,   373,   374,   574,   375,   382,
     376,   379,   380,   377,   378,     0,   407,   381,     0,   434,
     435,   436,   415,   420,   432,     0,   421,   426,     0,   446,
     447,   438,   440,   443,   444,     0,     0,     0,     0,   459,
       0,     0,     0,     0,     0,     0,     0,     0,   602,   603,
     604,   605,   606,   607,   507,   575,   578,   579,   576,   596,
     577,   597,   595,   594,   598,   592,   593,   591,   599,   600,
     601,   587,   588,   508,   509,   510,   558,   559,   552,   551,
     563,   565,   567,   569,   570,   557,   589,   590,   560,     0,
       0,     0,     0,   537,   536,     0,   143,   156,   163,   181,
     197,   273,    47,     0,     0,     0,    54,     0,     0,   547,
      57,    60,    58,    61,     0,     0,     0,    70,   547,     0,
      79,    85,    98,    97,   245,   104,    88,    91,    94,   107,
     110,   116,   119,     0,     0,   485,   483,   484,   482,   817,
     824,   814,   816,   815,   819,   820,   821,   822,   823,   818,
     825,   803,   659,     0,     0,   683,   684,   686,   685,   687,
     688,     0,   664,   689,     0,     0,   648,   481,   124,   136,
       0,     0,   351,   352,     0,     0,     0,   448,   450,     0,
       0,     0,     0,     0,   689,     0,   313,   341,     0,   350,
       0,   429,   431,   533,     7,     7,   525,   527,   570,   532,
       7,   515,   274,   316,   317,   315,   334,   333,     0,     0,
     332,   328,   323,   324,   325,   326,   329,   327,   322,     0,
       0,     0,     0,   412,     0,   409,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   414,     0,     0,     0,
       0,     0,   424,   442,   441,     0,     0,   461,     0,   460,
     494,   495,   497,   499,   501,   504,     0,     7,   303,   511,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   553,   644,   702,     9,    10,     0,     0,     0,     0,
       0,   143,   156,   163,   181,   197,     0,   254,   256,   259,
      76,   264,   105,     0,   491,   828,   827,   826,   829,   830,
     831,   832,   833,   802,     0,     0,   690,   691,   665,   648,
     648,     0,   655,   219,     0,     0,   346,   345,   347,   451,
       0,   531,   449,   528,   647,     0,   524,     0,   522,   645,
     643,     0,   700,     0,   347,     0,   519,     0,   520,   526,
     518,   517,   331,   337,   338,   330,   336,     0,     0,   369,
       0,   413,     0,   384,   373,   382,   385,   387,   389,   391,
     399,   400,   394,   397,   396,   395,   410,   696,   697,   698,
     699,   418,   433,   425,   427,   445,     0,     0,   305,     0,
       0,   306,   556,   561,   562,   564,   566,   568,   555,   505,
     506,   571,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,   145,   144,     0,     0,     0,    35,   158,
     157,     0,     0,     0,   171,     0,     0,     0,     0,     0,
       0,     0,    38,   165,   164,     0,     0,     0,     0,     0,
      39,   183,   182,     0,     0,     0,    41,   199,   198,     0,
       0,     0,     0,     0,   219,     0,   860,   867,   652,     0,
     654,   649,     0,   538,     0,   354,     0,   540,   244,   530,
     529,     0,     0,   523,   701,     0,   354,   349,   430,     7,
     570,   534,   535,     0,   366,   367,   368,   411,   419,   428,
       0,   452,     0,     0,     7,   304,   554,   257,   155,   260,
     162,   180,   262,   196,   142,     0,   265,   210,   210,   210,
     146,   238,   239,   237,     0,   159,   160,   161,     0,     0,
       0,   195,   194,   192,   193,   227,   229,   230,   228,   231,
     208,     0,   207,   177,   178,   179,     0,   176,   172,     0,
       0,     0,     0,   191,     0,     0,    49,    51,    52,    53,
      55,     0,   719,   648,     0,     0,     0,   221,   220,   222,
     358,   359,   360,   361,   362,   354,     0,   549,     0,     0,
     462,   354,   340,   521,   335,     0,   456,     0,   308,   307,
       0,     0,     0,     0,   210,     0,     0,     0,     0,   168,
     169,   170,     0,   166,     0,   167,   184,   190,     0,   189,
       0,     0,     0,     0,   653,     0,     0,    45,   548,     0,
     348,     0,   339,   455,     7,   156,   163,   181,   197,     0,
     211,   223,   215,   236,   209,   175,     0,     0,     0,     0,
       0,   233,     0,   206,     0,   203,   201,    59,     0,   546,
     357,   355,   356,   463,   309,     0,     0,     0,     0,   219,
       0,     0,     0,     0,     0,   186,   188,   187,   185,   234,
     200,     7,   202,   544,   543,     0,     0,     0,     0,     0,
       0,     0,   213,   212,   214,     0,   225,   224,   226,     0,
     217,   216,   218,   235,     0,   205,   204,   545,   147,   148,
     149,   150,     0,   151,   154,   152,   232,   153
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1073, -1073,    -1,  -848,     6, -1073, -1073,  1180, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073,   -11, -1073,   852, -1073,   211,  -339,  -946,
    -349,  -940,  -334,    64,   -89,  -340,  -942,  -941, -1073,  -348,
    -937, -1073, -1073,  -152,   -85, -1055,  -905, -1073, -1073, -1072,
   -1073, -1073, -1073,  -174, -1073, -1073, -1073,    33,  -492,  -626,
    1134,   -81,  1452, -1073,   454, -1073, -1073,    51, -1073,   121,
     384, -1073,    49,   827, -1015,   879, -1073, -1073,   118,  1145,
     960,    81,     4, -1073, -1073,  -279, -1073, -1073, -1073, -1073,
      40, -1073, -1073, -1073,   569, -1073, -1073, -1073,   560, -1073,
   -1073, -1073,    63, -1073,   973,  -864,   204, -1073,   592, -1034,
      76, -1073, -1073, -1073, -1073, -1073,  -787,   314,   320,   321,
   -1073,   318, -1073, -1073, -1073, -1073, -1073, -1073, -1073,  -584,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,  -288,
     312, -1073, -1073, -1073,   522, -1073,   316,  -883, -1073, -1073,
    1021, -1073, -1073, -1073, -1073,   524, -1073, -1073,   -54,  -204,
     538,     0, -1073, -1073, -1073,   430,   526,   527,   525, -1073,
    -154,  -173, -1073, -1073, -1073,  -648, -1073,  -156,   -53, -1073,
     374,  -880, -1073,  -997, -1073,  -819,  -932, -1073, -1073,   953,
     -65,   934,   -61,   930,  1183, -1073, -1073,  -287,   -58,   940,
   -1073,   985,  -297,   327,   329,   319, -1073,  -283,  -642, -1073,
    -155,  -263,  -612, -1073,  -972,   372,  1037, -1073,   -46, -1073,
    -929, -1073,   764,   935,  -397,   949,   770,  1022,  1041,  1048,
   -1073, -1073,  -392,   -37, -1073, -1073, -1073,   -26, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1119,   663,  1120,    43,    44,    45,    68,    79,
      81,    93,    95,   116,   121,   129,   131,   233,   236,   239,
     240,   629,   878,   234,   189,   335,  1115,   986,   336,   987,
     339,   988,   340,  1236,  1237,   343,   989,  1135,  1223,   345,
     990,  1302,  1334,  1335,  1230,  1231,  1285,  1350,  1352,  1162,
    1351,  1232,  1121,  1332,  1354,  1122,  1213,  1206,   190,  1169,
      46,    47,    60,   361,    49,   364,  1198,    61,   368,  1200,
      65,  1203,   243,   376,  1207,   253,   254,   255,    50,   347,
    1031,   384,  1123,   284,   285,   286,   287,   288,   968,  1090,
    1091,   289,   290,   671,   672,   291,   292,   679,   680,   927,
     921,  1055,  1056,   293,   640,  1028,  1167,   294,   884,  1267,
    1265,   295,   296,   682,   297,   298,   701,   702,   703,   704,
     705,   706,   707,  1073,   708,   709,   710,   711,   712,   713,
     714,   299,   300,   732,   301,   302,   736,   303,   304,   733,
     734,   305,   306,   741,   742,   743,   744,   886,   887,   307,
     308,   309,   310,   311,   748,   749,   312,   313,   191,   192,
     193,   314,   195,   848,   433,   434,   315,   316,   317,   318,
     319,   320,   783,   784,   785,   786,   321,   322,   323,   664,
     665,  1037,  1038,   905,   906,  1032,  1033,   907,  1179,   802,
     633,   634,   641,   642,   373,  1365,  1259,   880,   636,   637,
     324,   803,   804,   790,   791,   792,   793,   908,   795,   717,
     718,   719,   798,   799,   325,   196,   579,   580,   197,   327,
    1022,   607,   198,   199,   543,   200,   544,   201,   602,   603,
     872,  1018,   604,   725,   726,   328,   329,   727,   203,   427,
     204,   438,   205,   443,   206,   449,   207,   462,   208,   470,
     209,   480,   210,   489,   211,   495,   212,   498,   213,   502,
     214,   507,   215,   512,   216,   524,   861,  1013,   217,   528,
     218,   533,   219,   220,   557,   221,   545,   222,   547,   223,
     549,   224,   554,   225,   564,   226,   567,   227,   573,   228,
     616
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,   815,    51,   202,   326,   818,   668,    42,   341,   342,
     814,   608,   817,   326,   737,   903,   383,   816,   383,   383,
     237,   909,   383,   383,   330,   789,   383,   383,   609,   194,
     383,   383,   383,   330,   618,   827,  1044,   383,   383,   794,
      54,    55,    56,   247,   910,   383,  1150,   830,  1143,   794,
     794,   331,  1152,  1151,   283,   334,  1046,  1048,  1153,   797,
    1190,  1194,  1050,   337,   966,    62,    63,  1361,   747,   797,
     797,   896,   897,  1086,   899,  1182,   901,   890,  1087,   248,
     745,   249,  1251,  1241,   229,  1340,  1030,  1049,   244,   245,
    1158,  1160,  1193,   338,   715,  1208,  1209,   344,   535,   933,
    1170,    52,   935,   728,   746,   745,  1026,   250,     3,   755,
     662,     4,   537,     5,   538,   581,   943,  1170,   781,  1089,
     235,  1330,   350,   351,   352,   355,   356,   357,   781,   781,
      59,    53,     6,     7,     8,     9,   367,   369,   370,   375,
     377,   379,  1272,   757,  1164,   381,   135,   136,   137,  1063,
     944,   952,   389,   390,   953,   845,  1072,   395,   202,   400,
    1175,    94,   202,   407,   408,   426,   409,   796,   656,   414,
     537,   135,   136,   137,   912,   417,   418,   796,   796,   421,
     386,   388,   922,   657,   391,   392,   926,  1331,   396,   397,
    1284,   555,   402,   404,   406,  1333,   541,   542,   358,   411,
     413,     3,   525,    67,     4,   871,     5,   419,   556,     3,
     873,  1143,     4,  1165,     5,    80,   982,   983,   619,  1173,
     617,   581,  1341,  1342,   621,     6,     7,     8,     9,  1176,
     735,  1308,   130,     6,     7,     8,     9,  1312,  1144,   326,
    1145,  1170,   929,  1329,  1027,   526,   527,     3,   846,   847,
       4,   238,     5,   930,   541,   542,   871,   241,   824,   330,
       3,   894,   825,     4,   282,     5,   826,   187,   931,   787,
     829,     6,     7,     8,     9,   631,  1144,  1370,  1145,   787,
     787,  1193,  -141,   891,     6,     7,     8,     9,  -344,   666,
     630,  1269,   729,   730,   731,   647,   648,   341,   342,   650,
     565,   326,    53,  1286,  1287,  1314,    53,  1275,  1039,  1040,
      53,  1042,   326,   383,    53,   341,   342,   566,   230,   231,
     232,   330,  -155,   958,  1304,  1066,   911,   341,   342,   967,
     332,  1273,   330,   632,  1124,  1125,  1126,  1127,  1128,   251,
     252,  1129,   420,  1195,  1191,   282,  1278,   490,   187,  1362,
    1061,   812,   333,   976,   230,   231,   232,   491,  1130,  1093,
    1094,  1076,   823,   372,   492,  1081,   977,  1083,   978,  1345,
     493,   494,     4,   187,     5,  1347,  1346,   398,   932,  1319,
     496,  1348,    82,   503,    83,   354,    84,   504,   550,    85,
      86,    87,   248,    88,   497,   249,  1371,  1034,  1131,   338,
     797,   529,   903,   819,  1310,  1181,  1143,   631,   909,     3,
     505,   506,     4,     3,     5,   941,     4,   942,     5,   729,
     730,   731,   828,   372,   530,   531,   946,   551,   552,   553,
     755,   916,   658,     6,     7,     8,     9,     6,     7,     8,
       9,   903,   638,   639,   832,  1225,   756,   909,   835,   638,
     639,   715,   715,   532,   715,   842,   715,  1174,   353,   781,
     969,  1178,   917,  1363,   757,    58,  1344,   605,  1364,  1226,
    1227,   841,   371,   888,   546,   833,   918,   606,  1187,   715,
     548,   499,   715,  1124,  1125,  1126,  1127,  1128,   608,  1379,
    1129,   500,   501,     3,   797,   610,     4,  1146,     5,  1218,
    1219,     3,   981,   620,     4,   902,     5,  1130,   796,   117,
    1239,  1254,   919,  1385,   118,   119,   508,     6,     7,     8,
       9,   346,   428,   429,   349,     6,     7,     8,     9,   120,
     568,   715,   996,   632,   715,  1250,   797,   363,   346,   509,
     510,  1000,   511,   569,  1228,   246,   635,  1131,  1132,     4,
     570,     5,   385,   781,     4,   643,     5,   673,  1292,    89,
     571,   920,  1233,  1234,  1229,  1235,   572,  1124,  1125,  1126,
    1127,  1128,  1053,    90,  1129,  1054,  1136,   416,  1137,  1128,
       3,   644,  1129,     4,   422,     5,  1021,  1225,    91,  1159,
     977,  1130,   978,    92,   645,   781,   715,   715,   649,  1138,
    1298,   965,   796,  1292,     6,     7,     8,     9,   393,   394,
     904,  1226,  1227,   430,   431,   655,     3,   432,   879,     4,
     202,     5,   662,  1255,     3,   638,   639,     4,   660,     5,
     903,  1131,   435,   436,   437,   202,   909,   257,   258,  1139,
       6,     7,     8,     9,   796,  1144,   661,  1145,     6,     7,
       8,     9,   674,   675,   676,   677,   678,    53,  1103,   666,
     423,   424,   425,  1104,  1084,  1105,   558,  1106,   681,     4,
     720,     5,  1294,  1065,   797,  1065,  1065,  1065,  1254,  1065,
    1065,   559,  1029,  1102,  1078,  1078,  1228,  1092,   715,   715,
     747,   715,   752,  1098,   560,  1100,  1101,  1248,   669,   670,
     561,  1256,   750,   751,   787,   754,  1229,   797,   797,   797,
     797,   797,   797,   797,   753,   797,   797,   797,  1036,   230,
     231,   232,  1326,   800,   202,   202,   202,   202,   202,   202,
     715,   801,  1064,   781,  1064,  1064,  1064,  1327,  1064,  1064,
    1074,   715,  1328,  1077,  1077,   715,   787,   715,   562,   563,
     960,   961,   259,   260,   261,   262,   263,   264,  1172,   738,
     739,   740,  1107,   806,  1180,   807,   781,   781,   781,   781,
     781,   781,   781,   808,   781,   781,   781,   250,   426,   809,
     957,  1367,   796,   888,   797,  1036,   834,   797,   843,  1140,
    1255,   882,   883,  1188,   844,  1189,   471,   472,   122,   810,
     123,   984,   936,   937,   985,   124,   863,   125,  1192,   864,
     473,   126,   474,   475,   476,   796,   796,   796,   796,   796,
     796,   796,   876,   796,   796,   796,   797,   477,   478,   479,
     874,    17,    18,  1108,   971,   972,   716,   715,   875,  1005,
     622,   715,   623,   781,   624,   625,   781,  1109,   127,   881,
     128,  1281,   626,   627,   877,  1283,  1016,  1017,   715,  1280,
     782,  1282,  1110,   662,  1047,   202,   885,  1111,  1303,   889,
     782,   782,  1006,   892,     3,   739,   740,     4,    33,     5,
     893,   135,   136,   137,   628,   781,  1291,    34,   729,   730,
     731,  1075,   796,    35,   895,   796,  1211,  1212,     6,     7,
       8,     9,  1221,  1222,  1369,   900,  1297,   938,  1103,    36,
    1079,  1080,  1112,  1104,   913,  1105,   914,  1106,   378,   380,
    1007,  1008,  1009,  1010,  1011,  1012,     3,   787,   939,     4,
     202,     5,   202,   923,   796,   463,   924,   464,   925,   940,
       3,   326,   945,     4,     3,     5,   956,     4,  -696,     5,
       6,     7,     8,     9,  -697,   465,   949,   466,   467,   468,
     469,   330,   947,   611,     6,     7,     8,     9,     6,     7,
       8,     9,   612,   613,   948,   950,   614,   615,   955,   444,
     445,   446,   447,   448,   970,  1113,   973,  1133,  1141,  1147,
    1311,   326,  1114,   974,  1134,  1142,  1148,   904,  1036,  1088,
     975,  1136,   979,  1137,  1128,   991,   439,  1129,   440,   441,
     442,   330,  1107,   992,   993,   797,   994,   888,   534,  1136,
     997,  1137,  1128,   995,  1138,  1129,   998,   720,   720,   535,
     720,   536,   720,  1260,  1261,  1262,  1263,  1264,   387,  1021,
     999,   326,  1138,   537,  1001,   538,     3,  1003,   539,     4,
    1014,     5,  1015,    17,    18,   720,  1023,   755,   720,  1024,
    1019,   330,   721,  1041,  1139,  1045,  1020,  1025,  1035,  1043,
       6,     7,     8,     9,   781,  1052,  1059,    69,  1062,    70,
    1070,  1057,  1139,  1108,    71,    72,    73,  1058,    74,  1060,
    1099,  1154,  1155,  1156,  1157,   540,  1161,  1109,  1163,  1171,
      33,  1166,  1168,  1183,   326,  1184,  1185,   720,  1186,    34,
     720,  1196,  1110,  1204,  1210,    35,  1205,  1111,  1214,  1224,
    1215,  1216,  1217,   796,   330,  1220,  1240,   541,   542,  1244,
    1245,    36,  1266,  1270,  1238,  1252,  1197,  1199,  1199,  1202,
    1253,  1268,  1243,  1277,  1254,   202,  1276,  1288,  1113,  1301,
    1133,  1141,  1147,  1300,  1305,  1114,  1309,  1134,  1142,  1148,
     401,  1257,  1246,  1315,   202,   403,   341,   342,  1258,  1313,
    1316,  1317,   720,   720,  1306,    17,    18,  1318,  1323,   635,
      17,    18,  1320,  1321,  1322,  1338,   341,   342,  1333,  1343,
    1349,  1353,  1359,   716,   716,  1383,   716,  1384,   716,    66,
     813,   782,  1149,  1242,    10,  1325,    11,  1324,    12,  1386,
    1396,    13,    14,    15,  1249,    16,   359,  1289,  1290,    17,
      18,   716,    33,   326,   716,   811,  1201,    33,  1375,   365,
    1293,    34,  1368,   722,  1279,  1295,    34,    35,  1296,   928,
     915,  1299,    35,   330,   667,   659,  1274,   723,  1177,   898,
    1257,  1271,  1067,    36,    75,  1307,  1255,  1258,    36,  1068,
    1071,  1069,  1082,   954,   720,   720,    33,   720,    76,   865,
     866,  1085,   959,   716,  1004,    34,   716,   646,   962,   964,
     963,    35,   535,    77,  1051,  1374,   805,   822,    78,   820,
     867,  1382,   399,  1378,  1097,   782,   821,    36,   538,   326,
    1095,  1336,  1337,  1096,   652,  1339,   720,   788,   720,   653,
     720,   720,   720,   862,   720,   720,   654,   720,     0,   330,
     724,   720,     0,   720,     0,  1355,  1356,  1357,  1358,     0,
       0,  1360,     0,     0,  1392,     0,     0,   782,   716,   716,
       0,     0,     0,     0,     0,  1133,  1141,  1147,     0,  1372,
    1376,  1380,  1134,  1142,  1148,     0,  1373,  1377,  1381,     0,
       0,     0,     0,     0,  1387,  1388,  1389,  1390,  1391,  1257,
    1393,     0,     0,     0,  1394,     0,  1258,   405,  1395,     0,
       0,    37,     0,   868,   869,   870,   589,     0,     0,   410,
       0,  1397,    17,    18,     0,    38,     0,     0,   599,   600,
     601,     0,     0,     0,    17,    18,     0,     0,     0,     0,
      39,     0,     0,   720,     0,    40,     0,   720,     0,   721,
     721,     0,   721,     0,   721,     0,     0,     0,     0,     0,
     716,   716,     0,   716,   720,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,   721,    34,     0,
     721,    33,     0,    48,    35,     0,     0,     0,     0,     0,
      34,     0,    57,    48,    48,     0,    35,     0,    64,     0,
      36,    48,   716,     0,   716,   782,   716,   716,   716,     0,
     716,   716,    36,   716,     0,     0,     0,   716,     0,   716,
     242,   242,   242,     0,     0,     0,     0,     0,     0,   721,
       0,     0,   721,     0,     0,     0,     0,     0,   782,   782,
     782,   782,   782,   782,   782,     0,   782,   782,   782,    48,
       0,   348,    48,     0,     0,     0,    64,     0,   242,   242,
     242,     0,    48,     0,   360,   362,    48,   366,     0,     0,
      64,     0,   374,   374,   374,     0,     0,     0,   382,     0,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   242,   745,   721,   721,   242,   242,     0,   242,
       0,   412,   242,     0,   415,    48,     0,     0,     0,   716,
       0,     0,    48,   716,     0,   782,    17,    18,   782,     0,
     722,   722,   481,   722,   482,   722,     0,     0,   685,     0,
     716,     0,     0,     0,   723,   723,     0,   723,     0,   723,
       0,     0,   483,     0,   484,   485,     0,   486,   722,     0,
       0,   722,     0,     0,     0,   487,   488,   782,     0,   135,
     136,   137,   723,    33,     0,   723,   765,     0,     0,     0,
     766,     0,    34,     0,   767,     0,     0,     0,    35,     0,
     768,     0,     0,     0,   691,     0,   721,   721,     0,   721,
       0,     0,     0,     0,    36,     0,   770,     0,     0,     0,
     722,     0,     0,   722,     0,     0,     0,   724,   724,     0,
     724,     0,   724,     0,   723,     0,     0,   723,     0,     0,
       0,     0,     0,   242,   513,     0,     0,   514,   721,     0,
     721,     0,   721,   721,   721,   724,   721,   721,   724,   721,
     515,     0,     0,   721,   516,   721,     0,   517,   518,     0,
       0,     0,   519,   520,   521,   522,   523,     0,     0,     0,
       0,    96,    97,    98,    99,   722,   722,   100,   101,     0,
     102,   103,     0,     0,   104,     0,     0,     0,     0,   723,
     723,   450,   451,     0,     0,   452,     0,   724,     0,   694,
     724,     0,   695,   696,     0,   453,   454,   455,   456,   457,
     458,   459,   460,   461,     0,     0,     0,     0,     0,     0,
       0,   105,     0,   106,   107,   108,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   697,   698,     0,
       0,     0,     0,     0,     0,   721,   242,     0,     0,   721,
       0,     0,     0,     0,     0,     0,   782,     0,     0,     0,
       0,     0,   724,   724,     0,   242,   721,   722,   722,     0,
     722,   187,     0,     0,     0,     0,     0,     0,     0,   831,
       0,   723,   723,     0,   723,     0,     0,     0,     0,     0,
       0,   242,     0,   836,     0,   837,     0,   838,     0,     0,
       0,     0,   839,     0,   840,     0,     0,     0,     0,   722,
       0,   722,     0,   722,   722,   722,     0,   722,   722,     0,
     722,     0,     0,   723,   722,   723,   722,   723,   723,   723,
       0,   723,   723,     0,   723,     0,     0,     0,   723,     0,
     723,     0,     0,     0,     0,     0,     0,     0,   109,     0,
       0,     0,     0,     0,   724,   724,     0,   724,     0,     0,
       0,     0,   110,     0,     0,     0,     0,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,   114,     0,     0,
     849,     0,   115,   850,   851,   852,   853,   854,   855,   856,
     857,   858,   859,   860,     0,     0,   724,     0,   724,     0,
     724,   724,   724,     0,   724,   724,     0,   724,     0,     0,
       0,   724,     0,   724,     0,     0,   722,     0,     0,     0,
     722,     0,     3,     0,     0,     4,     0,     5,     0,     0,
     723,     0,     0,     0,   723,     0,     0,   722,     0,     0,
       0,     0,     0,     0,   132,     0,     6,     7,     8,     9,
     133,   723,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   256,     0,     0,     0,     0,     0,     0,     0,     0,
     574,   257,   258,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   259,   260,   261,
     262,   263,   264,     0,     0,     0,   575,     0,     0,   576,
    1116,     0,     0,   724,   265,     0,   266,   724,   577,   134,
     135,   136,   137,     0,     0,     0,     0,   138,     0,     0,
    1117,   139,     0,     0,   724,   140,     0,     0,     0,     0,
       0,   141,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   142,     0,     0,     0,     0,     0,   143,     0,     0,
       0,     0,   144,     0,     0,   145,     0,     0,   146,   147,
       0,     0,   148,     0,     0,   149,     0,   150,     0,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,     0,
     151,   152,     0,   153,   154,   155,   156,     0,     0,     0,
       0,     0,   157,   158,     0,     0,   159,   160,   267,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,     0,
       0,   268,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   578,     0,     0,   269,     0,     0,     0,     0,
       0,     0,     0,     0,   270,     0,     0,     0,     0,     0,
     271,     0,     0,     0,     0,   272,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   273,     0,     0,   274,   275,
     276,   277,     0,     0,     0,   278,     0,     0,     0,   279,
     280,   183,     0,     0,     3,   184,   185,     4,     0,     5,
       0,     0,     0,     0,   281,     0,     0,   186,     0,   282,
    1118,     0,   187,   188,     0,     0,   132,     0,     6,     7,
       8,     9,   133,     0,     0,     0,  1002,     0,     0,     0,
       0,     0,     0,   256,     0,     0,     0,     0,     0,     0,
       0,   651,     0,   257,   258,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   259,
     260,   261,   262,   263,   264,     0,     0,   575,     0,     0,
     576,     0,  1116,     0,     0,     0,   265,     0,   266,   577,
       0,   134,   135,   136,   137,     0,     0,     0,     0,   138,
       0,     0,  1117,   139,     0,     0,     0,   140,     0,     0,
       0,     0,     0,   141,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   142,     0,     0,     0,     0,     0,   143,
       0,     0,     0,     0,   144,     0,     0,   145,     0,     0,
     146,   147,     0,     0,   148,     0,     0,   149,     0,   150,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
       0,     0,   151,   152,     0,   153,   154,   155,   156,     0,
       0,     0,     0,     0,   157,   158,     0,     0,   159,   160,
     267,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,     0,     0,   268,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   578,     0,     0,     0,   269,     0,     0,
       0,     0,     0,     0,     0,     0,   270,     0,     0,     0,
       0,     0,   271,     0,     0,     0,     0,   272,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   273,     0,     0,
     274,   275,   276,   277,     0,     0,     0,   278,     0,     0,
       0,   279,   280,   183,     0,     0,     3,   184,   185,     4,
       0,     5,     0,     0,     0,     0,   281,     0,     0,   186,
       0,   282,  1247,     0,   187,   188,     0,     0,   132,     0,
       6,     7,     8,     9,   133,     0,     0,     0,   582,   583,
       0,     0,     0,     0,     0,   256,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   257,   258,     0,     0,   584,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   259,   260,   261,   262,   263,   264,     0,     0,     0,
       0,     0,     0,     0,  1116,     0,     0,     0,   265,     0,
     266,     0,     0,   134,   135,   136,   137,     0,     0,     0,
       0,   138,     0,     0,  1117,   139,     0,     0,     0,   140,
       0,     0,     0,     0,     0,   141,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   142,     0,     0,     0,   585,
       0,   143,     0,     0,     0,     0,   144,     0,     0,   145,
       0,     0,   146,   147,     0,     0,   148,     0,     0,   149,
       0,   150,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,     0,     0,   599,   600,   601,
       0,     0,     0,     0,   151,   152,     0,   153,   154,   155,
     156,     0,     0,     0,     0,     0,   157,   158,     0,     0,
     159,   160,   267,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,     0,     0,   268,     0,   683,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   269,
       0,     0,     0,   684,     0,   132,     0,     0,   270,     0,
       0,     0,     0,     0,   271,     0,     0,     0,     0,   272,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   273,
       0,     0,   274,   275,   276,   277,     0,     0,     0,   278,
     685,     0,     0,   279,   280,   183,     0,     0,     0,   184,
     185,     0,     0,     0,   686,     0,     0,     0,   281,     0,
       0,   186,     0,   282,  1366,     0,   187,   188,     0,     0,
     134,   135,   136,   137,     0,     0,     0,     0,   687,     0,
       0,     0,   688,     0,     0,     0,   689,     0,     0,     0,
       0,     0,   690,     0,     0,     0,   691,     0,     0,     0,
       0,     0,   142,     0,     0,     0,     0,     0,   692,     0,
       0,     0,     0,   144,     0,     0,   145,     0,     0,   146,
     147,     0,     0,   148,     0,     0,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     934,   151,   152,     0,   693,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   684,     0,   132,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
       0,     0,   182,     0,     0,     0,     0,     0,     0,     0,
       0,   694,     0,   685,   695,   696,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   134,   135,   136,   137,     0,     0,   697,
     698,   687,     0,     0,     0,   688,     0,     0,     0,   689,
       0,     0,   183,     0,     0,   690,   184,   185,     0,   691,
       0,     0,     0,     0,     0,   142,   699,   700,     0,     0,
       0,   692,     0,   187,     0,     0,   144,     0,     0,   145,
       0,     0,   146,   147,     0,     0,   148,     0,     0,   149,
       0,   150,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   951,   151,   152,     0,   693,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   684,
       0,   132,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,     0,     0,   182,     0,     0,     0,     0,
       0,     0,     0,     0,   694,     0,   685,   695,   696,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   134,   135,   136,   137,
       0,     0,   697,   698,   687,     0,     0,     0,   688,     0,
       0,     0,   689,     0,     0,   183,     0,     0,   690,   184,
     185,     0,   691,     0,     0,     0,     0,     0,   142,   699,
     700,     0,     0,     0,   692,     0,   187,     0,     0,   144,
       0,     0,   145,     0,     0,   146,   147,     0,     0,   148,
       0,     0,   149,     0,   150,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   151,   152,     0,
     693,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,     0,     0,   182,     0,
       0,   758,   759,   760,   761,   762,   763,   694,     0,     0,
     695,   696,     0,   764,     0,   745,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   697,   698,     0,     0,     0,
     685,     0,     0,     0,     0,     0,     0,     0,   183,     0,
       0,     0,   184,   185,     0,     0,     0,     0,     0,     0,
       0,     0,   699,   700,     0,     0,     0,     0,     0,   187,
     134,   135,   136,   137,   764,     0,   745,     0,   765,     0,
       0,     0,   766,     0,     0,     0,   767,     0,     0,     0,
       0,     0,   768,     0,     0,     0,   691,     0,     0,     0,
       0,     0,   769,     0,     0,     0,     0,     0,   770,     0,
       0,   685,     0,   771,     0,     0,   772,     0,     0,   773,
     774,     0,     0,   775,     0,     0,   776,     0,   777,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   134,   135,   136,   137,     0,     0,     0,     0,   765,
       0,   778,   779,   766,     0,     0,     0,   767,     0,     0,
       0,     0,     0,   768,     0,     0,     0,   691,     0,     0,
       0,     0,     0,   769,     0,     0,     0,     0,     0,   770,
       0,     0,     0,     0,   771,     0,     0,   772,     0,     0,
     773,   774,     0,     0,   775,     0,     0,   776,     0,   777,
       0,   694,     0,     0,   695,   696,     0,     0,     0,     0,
     684,     0,   132,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   778,   779,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   697,
     698,     0,   780,     0,     0,     0,     0,   685,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   699,   700,     0,     0,
     282,     0,   694,   187,     0,   695,   696,   134,   135,   136,
     137,     0,     0,     0,     0,   687,     0,     0,     0,   688,
       0,     0,     0,   689,     0,     0,     0,     0,     0,   690,
       0,     0,     0,   691,     0,     0,     0,     0,     0,   142,
     697,   698,     0,   780,     0,   692,     0,     0,     0,     0,
     144,     0,     0,   145,     0,     0,   146,   147,     0,     0,
     148,     0,     0,   149,     0,   150,     0,   699,   700,     0,
       0,   282,     0,     0,   187,   980,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   151,   152,
       0,   693,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   764,     0,   745,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,     0,     0,   182,
       0,     0,     0,     0,     0,     0,     0,     0,   694,     0,
     685,   695,   696,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     134,   135,   136,   137,     0,     0,   697,   698,   765,     0,
       0,     0,   766,     0,     0,     0,   767,     0,     0,   183,
       0,     0,   768,   184,   185,     0,   691,   764,     0,   745,
       0,     0,   769,   699,   700,     0,     0,     0,   770,     0,
     187,     0,     0,   771,     0,     0,   772,     0,     0,   773,
     774,     0,     0,   775,     0,     0,   776,     0,   777,     0,
       0,     0,     0,     0,   685,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   778,   779,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   134,   135,   136,   137,     0,     0,
       0,     0,   765,     0,     0,     0,   766,     0,     0,     0,
     767,     0,     0,     0,     0,     0,   768,     0,     0,     0,
     691,     0,     0,     0,     0,     0,   769,     0,     0,     0,
       0,   694,   770,     0,   695,   696,     0,   771,     0,     0,
     772,     0,     0,   773,   774,     0,     0,   775,     0,     0,
     776,     0,   777,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   697,
     698,   132,   780,     0,     0,   778,   779,   133,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   256,     0,
       0,     0,     0,     0,     0,     0,   699,   700,   257,   258,
     282,     0,     0,   187,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   259,   260,   261,   262,   263,   264,
       0,     0,     0,     0,     0,   694,     0,     0,   695,   696,
       0,   265,     0,   266,     0,     0,   134,   135,   136,   137,
       0,     0,     0,     0,   138,     0,     0,     0,   139,     0,
       0,     0,   140,     0,     0,     0,     0,     0,   141,     0,
       0,     0,     0,   697,   698,     0,   780,     0,   142,     0,
       0,     0,     0,     0,   143,     0,     0,     0,     0,   144,
       0,     0,   145,     0,     0,   146,   147,     0,     0,   148,
     699,   700,   149,     0,   150,     0,     0,   187,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   151,   152,     0,
     153,   154,   155,   156,     0,     0,     0,     0,     0,   157,
     158,     0,     0,   159,   160,   267,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,     0,     0,   268,     0,
     132,     0,     0,     0,     0,     0,   133,     0,     0,     0,
       0,     0,   269,     0,     0,     0,     0,     0,     0,     0,
       0,   270,     0,     0,     0,     0,     0,   271,     0,     0,
       0,     0,   272,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   273,     0,     0,   274,   275,   276,   277,     0,
       0,     0,   278,     0,     0,     0,   279,   280,   183,     0,
       0,     0,   184,   185,     0,   134,   135,   136,   137,     0,
       0,   281,     0,   138,   186,     0,   282,   139,     0,   187,
     188,   140,     0,     0,     0,     0,     0,   141,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   142,     0,     0,
       0,     0,     0,   143,     0,     0,     0,     0,   144,     0,
       0,   145,     0,     0,   146,   147,     0,     0,   148,     0,
       0,   149,     0,   150,     0,   132,     0,     0,     0,     0,
       0,   133,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   151,   152,     0,   153,
     154,   155,   156,     0,     0,     0,     0,     0,   157,   158,
       0,     0,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,     0,     0,   182,     0,     0,
     134,   135,   136,   137,     0,     0,     0,     0,   138,     0,
       0,     0,   139,     0,     0,     0,   140,     0,     0,     0,
       0,     0,   141,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   142,     0,     0,     0,     0,     0,   143,     0,
       0,     0,     0,   144,     0,     0,   145,     0,     0,   146,
     147,     0,     0,   148,     0,     0,   149,   183,   150,     0,
     132,   184,   185,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   186,     0,   282,     0,     0,   187,   188,
       0,   151,   152,     0,   153,   154,   155,   156,     0,     0,
       0,     0,     0,   157,   158,   685,     0,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
       0,     0,   182,     0,     0,   134,   135,   136,   137,     0,
       0,     0,     0,   687,     0,     0,     0,   688,     0,     0,
       0,   689,     0,     0,     0,     0,     0,   690,     0,     0,
       0,   691,     0,     0,     0,     0,     0,   142,     0,     0,
       0,     0,     0,   692,     0,     0,     0,     0,   144,     0,
       0,   145,     0,     0,   146,   147,     0,     0,   148,     0,
       0,   149,   183,   150,     0,     0,   184,   185,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   186,     0,
       0,     0,     0,   187,   188,     0,   151,   152,     0,   693,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   745,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,     0,     0,   182,     0,     0,
       0,     0,     0,     0,     0,     0,   694,     0,   685,   695,
     696,     0,     0,     0,     0,     0,   259,   260,   261,   262,
     263,   264,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   134,   135,
     136,   137,     0,     0,   697,   698,   765,     0,     0,     0,
     766,     0,     0,     0,   767,     0,     0,   183,     0,     0,
     768,   184,   185,     0,   691,     0,     0,   745,     0,     0,
     769,   699,   700,     0,     0,     0,   770,     0,   187,     0,
       0,   771,     0,     0,   772,     0,     0,   773,   774,     0,
       0,   775,     0,     0,   776,     0,   777,     0,     0,     0,
       0,     0,   685,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   778,
     779,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   134,   135,   136,   137,     0,     0,     0,     0,
     765,     0,     0,     0,   766,     0,     0,     0,   767,     0,
       0,     0,     0,     0,   768,     0,     0,     0,   691,     0,
       0,     0,     0,     0,   769,     0,     0,     0,     0,   694,
     770,     0,   695,   696,     0,   771,     0,     0,   772,     0,
       0,   773,   774,     0,     0,   775,     0,     0,   776,     0,
     777,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       4,     0,     5,     0,     0,     0,     0,   697,   698,     0,
     780,     0,     0,   778,   779,     0,     0,     0,     0,     0,
       0,     6,     7,     8,     9,     0,     0,     0,     0,    10,
       0,    11,     0,    12,   699,   700,    13,    14,    15,     0,
      16,   187,     0,     0,    17,    18,    19,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,   694,     0,     0,   695,   696,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -245,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
      34,   697,   698,     0,   780,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,   699,   700,
       0,     0,     0,     0,     0,   187,     0,     0,     0,     0,
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
       1,   350,     3,    29,    50,   353,   285,     1,    62,    62,
     349,   184,   352,    59,   302,   663,    97,   351,    99,   100,
      31,   663,   103,   104,    50,   322,   107,   108,   184,    29,
     111,   112,   113,    59,   188,   369,   900,   118,   119,   322,
       7,     8,     9,    44,     7,   126,   992,   381,   989,   332,
     333,    52,   994,   993,    50,    56,   904,   905,   995,   322,
       5,     7,   910,    59,    23,    14,    15,     7,    33,   332,
     333,   655,   656,   956,   658,  1047,   660,    82,   958,    46,
      23,    48,  1154,  1138,    46,    89,    76,   906,    39,    40,
    1019,  1020,  1089,    60,   298,  1110,  1111,    64,   110,   683,
    1032,    90,   686,    72,   308,    23,    89,    45,     1,     8,
       4,     4,   124,     6,   126,   161,     8,  1049,   322,   967,
      46,    22,    71,    72,    73,    76,    77,    78,   332,   333,
      12,    89,    25,    26,    27,    28,    85,    86,    87,    90,
      91,    92,  1176,    42,    20,    94,    89,    90,    91,   936,
      42,   735,   101,   102,   738,    99,   943,   106,   184,   110,
      20,    41,   188,   114,   115,   132,   117,   322,   225,   120,
     124,    89,    90,    91,   666,   124,   125,   332,   333,   128,
      99,   100,   674,   240,   103,   104,   678,    88,   107,   108,
    1205,   112,   111,   112,   113,    89,   208,   209,    80,   118,
     119,     1,    99,    37,     4,   602,     6,   126,   129,     1,
     602,  1152,     4,    89,     6,    37,   800,   801,   229,  1038,
     187,   267,   226,   227,   235,    25,    26,    27,    28,    89,
      72,  1265,    35,    25,    26,    27,    28,  1271,    30,   285,
      32,  1173,   120,  1298,   227,   142,   143,     1,   192,   193,
       4,    89,     6,   131,   208,   209,   653,   218,    45,   285,
       1,   653,    45,     4,   288,     6,    45,   291,   146,   322,
      45,    25,    26,    27,    28,   242,    30,  1349,    32,   332,
     333,  1278,   288,   288,    25,    26,    27,    28,    88,   279,
     241,  1171,   261,   262,   263,   262,   263,   351,   351,   266,
     112,   347,    89,  1208,  1209,  1277,    89,  1190,   892,   893,
      89,   895,   358,   394,    89,   369,   369,   129,   280,   281,
     282,   347,   288,   288,  1253,   937,   289,   381,   381,   288,
     287,  1179,   358,   226,    75,    76,    77,    78,    79,   277,
     278,    82,    33,   289,   289,   288,  1194,   112,   291,   289,
     934,   347,   287,     7,   280,   281,   282,   122,    99,   971,
     972,   945,   358,   218,   129,   949,    20,   951,    22,  1315,
     135,   136,     4,   291,     6,  1317,  1316,   232,   256,  1284,
     122,  1318,    33,   115,    35,   218,    37,   119,   139,    40,
      41,    42,   359,    44,   136,   362,   289,   889,   139,   366,
     663,   119,  1050,   354,  1268,  1047,  1347,   374,  1050,     1,
     142,   143,     4,     1,     6,    20,     4,    22,     6,   261,
     262,   263,   373,   218,   142,   143,   714,   178,   179,   180,
       8,    65,   225,    25,    26,    27,    28,    25,    26,    27,
      28,  1089,   242,   243,   393,    89,    24,  1089,   399,   242,
     243,   655,   656,   171,   658,   422,   660,  1041,    74,   663,
     757,  1045,    96,   141,    42,    11,  1314,   261,   146,   113,
     114,   420,    88,   646,   177,   394,   110,   271,  1062,   683,
     177,   129,   686,    75,    76,    77,    78,    79,   661,   289,
      82,   139,   140,     1,   757,   272,     4,   289,     6,  1125,
    1126,     1,   799,   281,     4,   661,     6,    99,   663,   224,
    1136,    99,   146,  1361,   229,   230,   119,    25,    26,    27,
      28,    67,    97,    98,    70,    25,    26,    27,    28,   244,
      99,   735,   819,   226,   738,   289,   799,    83,    84,   142,
     143,   828,   145,   112,   188,     0,   240,   139,   289,     4,
     119,     6,    98,   757,     4,    88,     6,   139,     8,   210,
     129,   195,    73,    74,   208,    76,   135,    75,    76,    77,
      78,    79,   122,   224,    82,   125,    76,   123,    78,    79,
       1,    88,    82,     4,   130,     6,   273,    89,   239,   276,
      20,    99,    22,   244,    88,   799,   800,   801,    84,    99,
       5,   755,   757,     8,    25,    26,    27,    28,    33,    34,
     663,   113,   114,   188,   189,   225,     1,   192,   629,     4,
     646,     6,     4,   211,     1,   242,   243,     4,    72,     6,
    1278,   139,    97,    98,    99,   661,  1278,    50,    51,   139,
      25,    26,    27,    28,   799,    30,    72,    32,    25,    26,
      27,    28,   234,   235,   236,   237,   238,    89,    35,   279,
      92,    93,    94,    40,   952,    42,   101,    44,   255,     4,
     298,     6,     7,   936,   937,   938,   939,   940,    99,   942,
     943,   116,   886,   980,   947,   948,   188,   970,   892,   893,
      33,   895,    17,   976,   129,   978,   979,   289,   226,   227,
     135,   289,    15,    16,   757,   290,   208,   970,   971,   972,
     973,   974,   975,   976,    18,   978,   979,   980,   891,   280,
     281,   282,   224,    40,   750,   751,   752,   753,   754,   755,
     934,    40,   936,   937,   938,   939,   940,   239,   942,   943,
     944,   945,   244,   947,   948,   949,   799,   951,   183,   184,
     750,   751,    66,    67,    68,    69,    70,    71,  1037,   265,
     266,   267,   139,   288,  1047,   288,   970,   971,   972,   973,
     974,   975,   976,   288,   978,   979,   980,    45,   745,   288,
     747,   289,   937,   956,  1047,   958,    33,  1050,     7,   289,
     211,   242,   243,  1081,     8,  1083,    97,    98,    33,   288,
      35,   802,    15,    16,   805,    40,   294,    42,  1087,   294,
     111,    46,   113,   114,   115,   970,   971,   972,   973,   974,
     975,   976,    88,   978,   979,   980,  1089,   128,   129,   130,
     272,    48,    49,   210,    15,    16,   298,  1041,   272,    82,
      34,  1045,    36,  1047,    38,    39,  1050,   224,    83,    88,
      85,  1200,    46,    47,   293,  1203,    97,    98,  1062,  1198,
     322,  1201,   239,     4,     5,   891,    88,   244,   289,    23,
     332,   333,   115,    40,     1,   266,   267,     4,    95,     6,
      40,    89,    90,    91,    78,  1089,  1220,   104,   261,   262,
     263,   944,  1047,   110,    40,  1050,    66,    67,    25,    26,
      27,    28,    80,    81,   289,    88,  1240,    17,    35,   126,
     947,   948,   289,    40,    88,    42,    88,    44,    91,    92,
     163,   164,   165,   166,   167,   168,     1,   980,    18,     4,
     956,     6,   958,    88,  1089,    99,    88,   101,    88,   290,
       1,   987,     5,     4,     1,     6,   288,     4,     7,     6,
      25,    26,    27,    28,     7,   119,     5,   121,   122,   123,
     124,   987,     7,   172,    25,    26,    27,    28,    25,    26,
      27,    28,   181,   182,     7,     7,   185,   186,     7,   105,
     106,   107,   108,   109,     7,   986,    17,   988,   989,   990,
    1269,  1037,   986,    18,   988,   989,   990,  1050,  1171,   966,
     290,    76,     8,    78,    79,   288,    99,    82,   101,   102,
     103,  1037,   139,   288,   288,  1278,   288,  1190,    99,    76,
      88,    78,    79,   288,    99,    82,    88,   655,   656,   110,
     658,   112,   660,   249,   250,   251,   252,   253,    33,   273,
      88,  1087,    99,   124,    88,   126,     1,    88,   129,     4,
      88,     6,    88,    48,    49,   683,   288,     8,   686,   227,
      88,  1087,   298,    40,   139,    31,    88,    88,    88,    88,
      25,    26,    27,    28,  1278,   125,    58,    33,     5,    35,
      88,    99,   139,   210,    40,    41,    42,    99,    44,    99,
      88,   288,     7,   295,   295,   176,    88,   224,    88,   288,
      95,   245,    89,     7,  1150,    89,    89,   735,    89,   104,
     738,   293,   239,    89,  1115,   110,   218,   244,    89,    88,
    1121,  1122,  1123,  1278,  1150,   287,   287,   208,   209,    89,
     287,   126,   241,   289,  1135,    88,  1103,  1104,  1105,  1106,
      88,    88,  1143,     5,    99,  1171,   289,    30,  1149,   288,
    1151,  1152,  1153,   127,    90,  1149,    88,  1151,  1152,  1153,
      33,  1162,   289,   288,  1190,    33,  1220,  1220,  1162,   289,
     288,   288,   800,   801,  1255,    48,    49,   288,    89,   240,
      48,    49,   288,   288,   288,   118,  1240,  1240,    89,   289,
     288,    31,    88,   655,   656,    89,   658,   127,   660,    19,
     348,   663,   991,  1139,    33,  1294,    35,  1292,    37,  1361,
    1384,    40,    41,    42,   289,    44,    82,  1218,  1219,    48,
      49,   683,    95,  1269,   686,   346,  1105,    95,   289,    84,
    1231,   104,   289,   298,  1194,  1236,   104,   110,  1239,   679,
     671,  1242,   110,  1269,   284,   272,  1183,   298,  1044,   657,
    1251,  1175,   938,   126,   210,  1256,   211,  1251,   126,   939,
     942,   940,   950,   741,   892,   893,    95,   895,   224,    97,
      98,   955,   748,   735,   844,   104,   738,   256,   752,   754,
     753,   110,   110,   239,   910,  1350,   333,   357,   244,   355,
     118,  1352,   109,  1351,   975,   757,   356,   126,   126,  1345,
     973,  1302,  1303,   974,   267,  1306,   934,   322,   936,   268,
     938,   939,   940,   543,   942,   943,   268,   945,    -1,  1345,
     298,   949,    -1,   951,    -1,  1326,  1327,  1328,  1329,    -1,
      -1,  1332,    -1,    -1,   289,    -1,    -1,   799,   800,   801,
      -1,    -1,    -1,    -1,    -1,  1346,  1347,  1348,    -1,  1350,
    1351,  1352,  1346,  1347,  1348,    -1,  1350,  1351,  1352,    -1,
      -1,    -1,    -1,    -1,  1365,  1366,  1367,  1368,  1369,  1370,
    1371,    -1,    -1,    -1,  1375,    -1,  1370,    33,  1379,    -1,
      -1,   210,    -1,   211,   212,   213,   214,    -1,    -1,    33,
      -1,  1392,    48,    49,    -1,   224,    -1,    -1,   226,   227,
     228,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,    -1,
     239,    -1,    -1,  1041,    -1,   244,    -1,  1045,    -1,   655,
     656,    -1,   658,    -1,   660,    -1,    -1,    -1,    -1,    -1,
     892,   893,    -1,   895,  1062,    -1,    -1,    -1,    -1,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   683,   104,    -1,
     686,    95,    -1,     1,   110,    -1,    -1,    -1,    -1,    -1,
     104,    -1,    10,    11,    12,    -1,   110,    -1,    16,    -1,
     126,    19,   934,    -1,   936,   937,   938,   939,   940,    -1,
     942,   943,   126,   945,    -1,    -1,    -1,   949,    -1,   951,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,   735,
      -1,    -1,   738,    -1,    -1,    -1,    -1,    -1,   970,   971,
     972,   973,   974,   975,   976,    -1,   978,   979,   980,    67,
      -1,    69,    70,    -1,    -1,    -1,    74,    -1,    76,    77,
      78,    -1,    80,    -1,    82,    83,    84,    85,    -1,    -1,
      88,    -1,    90,    91,    92,    -1,    -1,    -1,    96,    -1,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,    23,   800,   801,   114,   115,    -1,   117,
      -1,    33,   120,    -1,   122,   123,    -1,    -1,    -1,  1041,
      -1,    -1,   130,  1045,    -1,  1047,    48,    49,  1050,    -1,
     655,   656,    99,   658,   101,   660,    -1,    -1,    58,    -1,
    1062,    -1,    -1,    -1,   655,   656,    -1,   658,    -1,   660,
      -1,    -1,   119,    -1,   121,   122,    -1,   124,   683,    -1,
      -1,   686,    -1,    -1,    -1,   132,   133,  1089,    -1,    89,
      90,    91,   683,    95,    -1,   686,    96,    -1,    -1,    -1,
     100,    -1,   104,    -1,   104,    -1,    -1,    -1,   110,    -1,
     110,    -1,    -1,    -1,   114,    -1,   892,   893,    -1,   895,
      -1,    -1,    -1,    -1,   126,    -1,   126,    -1,    -1,    -1,
     735,    -1,    -1,   738,    -1,    -1,    -1,   655,   656,    -1,
     658,    -1,   660,    -1,   735,    -1,    -1,   738,    -1,    -1,
      -1,    -1,    -1,   241,   119,    -1,    -1,   122,   934,    -1,
     936,    -1,   938,   939,   940,   683,   942,   943,   686,   945,
     135,    -1,    -1,   949,   139,   951,    -1,   142,   143,    -1,
      -1,    -1,   147,   148,   149,   150,   151,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,   800,   801,    39,    40,    -1,
      42,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,   800,
     801,    97,    98,    -1,    -1,   101,    -1,   735,    -1,   219,
     738,    -1,   222,   223,    -1,   111,   112,   113,   114,   115,
     116,   117,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    -1,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   257,   258,    -1,
      -1,    -1,    -1,    -1,    -1,  1041,   354,    -1,    -1,  1045,
      -1,    -1,    -1,    -1,    -1,    -1,  1278,    -1,    -1,    -1,
      -1,    -1,   800,   801,    -1,   373,  1062,   892,   893,    -1,
     895,   291,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,
      -1,   892,   893,    -1,   895,    -1,    -1,    -1,    -1,    -1,
      -1,   399,    -1,   401,    -1,   403,    -1,   405,    -1,    -1,
      -1,    -1,   410,    -1,   412,    -1,    -1,    -1,    -1,   934,
      -1,   936,    -1,   938,   939,   940,    -1,   942,   943,    -1,
     945,    -1,    -1,   934,   949,   936,   951,   938,   939,   940,
      -1,   942,   943,    -1,   945,    -1,    -1,    -1,   949,    -1,
     951,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   210,    -1,
      -1,    -1,    -1,    -1,   892,   893,    -1,   895,    -1,    -1,
      -1,    -1,   224,    -1,    -1,    -1,    -1,   229,   230,   231,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,    -1,    -1,
     149,    -1,   244,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,    -1,    -1,   934,    -1,   936,    -1,
     938,   939,   940,    -1,   942,   943,    -1,   945,    -1,    -1,
      -1,   949,    -1,   951,    -1,    -1,  1041,    -1,    -1,    -1,
    1045,    -1,     1,    -1,    -1,     4,    -1,     6,    -1,    -1,
    1041,    -1,    -1,    -1,  1045,    -1,    -1,  1062,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    25,    26,    27,    28,
      29,  1062,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    71,    -1,    -1,    -1,   115,    -1,    -1,   118,
      79,    -1,    -1,  1041,    83,    -1,    85,  1045,   127,    88,
      89,    90,    91,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      99,   100,    -1,    -1,  1062,   104,    -1,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,
      -1,    -1,   131,    -1,    -1,   134,    -1,    -1,   137,   138,
      -1,    -1,   141,    -1,    -1,   144,    -1,   146,    -1,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,    -1,
     169,   170,    -1,   172,   173,   174,   175,    -1,    -1,    -1,
      -1,    -1,   181,   182,    -1,    -1,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,    -1,
      -1,   210,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   261,    -1,    -1,   224,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,    -1,    -1,
     239,    -1,    -1,    -1,    -1,   244,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   254,    -1,    -1,   257,   258,
     259,   260,    -1,    -1,    -1,   264,    -1,    -1,    -1,   268,
     269,   270,    -1,    -1,     1,   274,   275,     4,    -1,     6,
      -1,    -1,    -1,    -1,   283,    -1,    -1,   286,    -1,   288,
     289,    -1,   291,   292,    -1,    -1,    23,    -1,    25,    26,
      27,    28,    29,    -1,    -1,    -1,   834,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    71,    -1,    -1,   115,    -1,    -1,
     118,    -1,    79,    -1,    -1,    -1,    83,    -1,    85,   127,
      -1,    88,    89,    90,    91,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    99,   100,    -1,    -1,    -1,   104,    -1,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,    -1,   131,    -1,    -1,   134,    -1,    -1,
     137,   138,    -1,    -1,   141,    -1,    -1,   144,    -1,   146,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
      -1,    -1,   169,   170,    -1,   172,   173,   174,   175,    -1,
      -1,    -1,    -1,    -1,   181,   182,    -1,    -1,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,    -1,    -1,   210,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   261,    -1,    -1,    -1,   224,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,
      -1,    -1,   239,    -1,    -1,    -1,    -1,   244,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   254,    -1,    -1,
     257,   258,   259,   260,    -1,    -1,    -1,   264,    -1,    -1,
      -1,   268,   269,   270,    -1,    -1,     1,   274,   275,     4,
      -1,     6,    -1,    -1,    -1,    -1,   283,    -1,    -1,   286,
      -1,   288,   289,    -1,   291,   292,    -1,    -1,    23,    -1,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    97,    98,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,   118,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,    -1,
      85,    -1,    -1,    88,    89,    90,    91,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,   100,    -1,    -1,    -1,   104,
      -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,   188,
      -1,   126,    -1,    -1,    -1,    -1,   131,    -1,    -1,   134,
      -1,    -1,   137,   138,    -1,    -1,   141,    -1,    -1,   144,
      -1,   146,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,    -1,    -1,   226,   227,   228,
      -1,    -1,    -1,    -1,   169,   170,    -1,   172,   173,   174,
     175,    -1,    -1,    -1,    -1,    -1,   181,   182,    -1,    -1,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,    -1,    -1,   210,    -1,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   224,
      -1,    -1,    -1,    21,    -1,    23,    -1,    -1,   233,    -1,
      -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,    -1,   244,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   254,
      -1,    -1,   257,   258,   259,   260,    -1,    -1,    -1,   264,
      58,    -1,    -1,   268,   269,   270,    -1,    -1,    -1,   274,
     275,    -1,    -1,    -1,    72,    -1,    -1,    -1,   283,    -1,
      -1,   286,    -1,   288,   289,    -1,   291,   292,    -1,    -1,
      88,    89,    90,    91,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    -1,   100,    -1,    -1,    -1,   104,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,
      -1,    -1,    -1,   131,    -1,    -1,   134,    -1,    -1,   137,
     138,    -1,    -1,   141,    -1,    -1,   144,    -1,   146,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,   169,   170,    -1,   172,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
      -1,    -1,   210,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   219,    -1,    58,   222,   223,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    -1,   257,
     258,    96,    -1,    -1,    -1,   100,    -1,    -1,    -1,   104,
      -1,    -1,   270,    -1,    -1,   110,   274,   275,    -1,   114,
      -1,    -1,    -1,    -1,    -1,   120,   284,   285,    -1,    -1,
      -1,   126,    -1,   291,    -1,    -1,   131,    -1,    -1,   134,
      -1,    -1,   137,   138,    -1,    -1,   141,    -1,    -1,   144,
      -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,   169,   170,    -1,   172,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,    -1,    -1,   210,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   219,    -1,    58,   222,   223,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      -1,    -1,   257,   258,    96,    -1,    -1,    -1,   100,    -1,
      -1,    -1,   104,    -1,    -1,   270,    -1,    -1,   110,   274,
     275,    -1,   114,    -1,    -1,    -1,    -1,    -1,   120,   284,
     285,    -1,    -1,    -1,   126,    -1,   291,    -1,    -1,   131,
      -1,    -1,   134,    -1,    -1,   137,   138,    -1,    -1,   141,
      -1,    -1,   144,    -1,   146,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   169,   170,    -1,
     172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,    -1,    -1,   210,    -1,
      -1,     9,    10,    11,    12,    13,    14,   219,    -1,    -1,
     222,   223,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   257,   258,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   270,    -1,
      -1,    -1,   274,   275,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   284,   285,    -1,    -1,    -1,    -1,    -1,   291,
      88,    89,    90,    91,    21,    -1,    23,    -1,    96,    -1,
      -1,    -1,   100,    -1,    -1,    -1,   104,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,
      -1,    58,    -1,   131,    -1,    -1,   134,    -1,    -1,   137,
     138,    -1,    -1,   141,    -1,    -1,   144,    -1,   146,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    -1,    -1,    -1,    -1,    96,
      -1,   169,   170,   100,    -1,    -1,    -1,   104,    -1,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,   114,    -1,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,    -1,   131,    -1,    -1,   134,    -1,    -1,
     137,   138,    -1,    -1,   141,    -1,    -1,   144,    -1,   146,
      -1,   219,    -1,    -1,   222,   223,    -1,    -1,    -1,    -1,
      21,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   169,   170,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   257,
     258,    -1,   260,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   284,   285,    -1,    -1,
     288,    -1,   219,   291,    -1,   222,   223,    88,    89,    90,
      91,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,   100,
      -1,    -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,    -1,   120,
     257,   258,    -1,   260,    -1,   126,    -1,    -1,    -1,    -1,
     131,    -1,    -1,   134,    -1,    -1,   137,   138,    -1,    -1,
     141,    -1,    -1,   144,    -1,   146,    -1,   284,   285,    -1,
      -1,   288,    -1,    -1,   291,   292,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   169,   170,
      -1,   172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,    -1,    -1,   210,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   219,    -1,
      58,   222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    -1,    -1,   257,   258,    96,    -1,
      -1,    -1,   100,    -1,    -1,    -1,   104,    -1,    -1,   270,
      -1,    -1,   110,   274,   275,    -1,   114,    21,    -1,    23,
      -1,    -1,   120,   284,   285,    -1,    -1,    -1,   126,    -1,
     291,    -1,    -1,   131,    -1,    -1,   134,    -1,    -1,   137,
     138,    -1,    -1,   141,    -1,    -1,   144,    -1,   146,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   169,   170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    -1,   100,    -1,    -1,    -1,
     104,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,
     114,    -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,
      -1,   219,   126,    -1,   222,   223,    -1,   131,    -1,    -1,
     134,    -1,    -1,   137,   138,    -1,    -1,   141,    -1,    -1,
     144,    -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   257,
     258,    23,   260,    -1,    -1,   169,   170,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   284,   285,    50,    51,
     288,    -1,    -1,   291,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,   219,    -1,    -1,   222,   223,
      -1,    83,    -1,    85,    -1,    -1,    88,    89,    90,    91,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,   100,    -1,
      -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,   110,    -1,
      -1,    -1,    -1,   257,   258,    -1,   260,    -1,   120,    -1,
      -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,   131,
      -1,    -1,   134,    -1,    -1,   137,   138,    -1,    -1,   141,
     284,   285,   144,    -1,   146,    -1,    -1,   291,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   169,   170,    -1,
     172,   173,   174,   175,    -1,    -1,    -1,    -1,    -1,   181,
     182,    -1,    -1,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,    -1,    -1,   210,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,   224,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   233,    -1,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,    -1,   244,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   254,    -1,    -1,   257,   258,   259,   260,    -1,
      -1,    -1,   264,    -1,    -1,    -1,   268,   269,   270,    -1,
      -1,    -1,   274,   275,    -1,    88,    89,    90,    91,    -1,
      -1,   283,    -1,    96,   286,    -1,   288,   100,    -1,   291,
     292,   104,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,
      -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,   131,    -1,
      -1,   134,    -1,    -1,   137,   138,    -1,    -1,   141,    -1,
      -1,   144,    -1,   146,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   169,   170,    -1,   172,
     173,   174,   175,    -1,    -1,    -1,    -1,    -1,   181,   182,
      -1,    -1,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,    -1,    -1,   210,    -1,    -1,
      88,    89,    90,    91,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    -1,   100,    -1,    -1,    -1,   104,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,
      -1,    -1,    -1,   131,    -1,    -1,   134,    -1,    -1,   137,
     138,    -1,    -1,   141,    -1,    -1,   144,   270,   146,    -1,
      23,   274,   275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   286,    -1,   288,    -1,    -1,   291,   292,
      -1,   169,   170,    -1,   172,   173,   174,   175,    -1,    -1,
      -1,    -1,    -1,   181,   182,    58,    -1,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
      -1,    -1,   210,    -1,    -1,    88,    89,    90,    91,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    -1,   100,    -1,    -1,
      -1,   104,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,
      -1,   114,    -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,
      -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,   131,    -1,
      -1,   134,    -1,    -1,   137,   138,    -1,    -1,   141,    -1,
      -1,   144,   270,   146,    -1,    -1,   274,   275,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   286,    -1,
      -1,    -1,    -1,   291,   292,    -1,   169,   170,    -1,   172,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,    -1,    -1,   210,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   219,    -1,    58,   222,
     223,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    -1,   257,   258,    96,    -1,    -1,    -1,
     100,    -1,    -1,    -1,   104,    -1,    -1,   270,    -1,    -1,
     110,   274,   275,    -1,   114,    -1,    -1,    23,    -1,    -1,
     120,   284,   285,    -1,    -1,    -1,   126,    -1,   291,    -1,
      -1,   131,    -1,    -1,   134,    -1,    -1,   137,   138,    -1,
      -1,   141,    -1,    -1,   144,    -1,   146,    -1,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   169,
     170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    -1,   100,    -1,    -1,    -1,   104,    -1,
      -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,   114,    -1,
      -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,   219,
     126,    -1,   222,   223,    -1,   131,    -1,    -1,   134,    -1,
      -1,   137,   138,    -1,    -1,   141,    -1,    -1,   144,    -1,
     146,    -1,    -1,    -1,    -1,    -1,     0,     1,    -1,    -1,
       4,    -1,     6,    -1,    -1,    -1,    -1,   257,   258,    -1,
     260,    -1,    -1,   169,   170,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    26,    27,    28,    -1,    -1,    -1,    -1,    33,
      -1,    35,    -1,    37,   284,   285,    40,    41,    42,    -1,
      44,   291,    -1,    -1,    48,    49,    50,    -1,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,   219,    -1,    -1,   222,   223,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,   257,   258,    -1,   260,    -1,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,   284,   285,
      -1,    -1,    -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   210,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     224,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,    -1,
     244
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   297,     0,     1,     4,     6,    25,    26,    27,    28,
      33,    35,    37,    40,    41,    42,    44,    48,    49,    50,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    95,   104,   110,   126,   210,   224,   239,
     244,   298,   300,   301,   302,   303,   356,   357,   358,   360,
     374,   298,    90,    89,   353,   353,   353,   358,   360,   374,
     358,   363,   363,   363,   358,   366,   303,    37,   304,    33,
      35,    40,    41,    42,    44,   210,   224,   239,   244,   305,
      37,   306,    33,    35,    37,    40,    41,    42,    44,   210,
     224,   239,   244,   307,    41,   308,    33,    34,    35,    36,
      39,    40,    42,    43,    46,    83,    85,    86,    87,   210,
     224,   229,   230,   231,   239,   244,   309,   224,   229,   230,
     244,   310,    33,    35,    40,    42,    46,    83,    85,   311,
      35,   312,    23,    29,    88,    89,    90,    91,    96,   100,
     104,   110,   120,   126,   131,   134,   137,   138,   141,   144,
     146,   169,   170,   172,   173,   174,   175,   181,   182,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   210,   270,   274,   275,   286,   291,   292,   320,
     354,   454,   455,   456,   457,   458,   511,   514,   518,   519,
     521,   523,   533,   534,   536,   538,   540,   542,   544,   546,
     548,   550,   552,   554,   556,   558,   560,   564,   566,   568,
     569,   571,   573,   575,   577,   579,   581,   583,   585,    46,
     280,   281,   282,   313,   319,    46,   314,   319,    89,   315,
     316,   218,   358,   368,   368,   368,     0,   298,   353,   353,
      45,   277,   278,   371,   372,   373,    40,    50,    51,    66,
      67,    68,    69,    70,    71,    83,    85,   187,   210,   224,
     233,   239,   244,   254,   257,   258,   259,   260,   264,   268,
     269,   283,   288,   378,   379,   380,   381,   382,   383,   387,
     388,   391,   392,   399,   403,   407,   408,   410,   411,   427,
     428,   430,   431,   433,   434,   437,   438,   445,   446,   447,
     448,   449,   452,   453,   457,   462,   463,   464,   465,   466,
     467,   472,   473,   474,   496,   510,   514,   515,   531,   532,
     533,   298,   287,   287,   298,   321,   324,   378,   353,   326,
     328,   454,   474,   331,   353,   335,   360,   375,   358,   360,
     363,   363,   363,   366,   218,   368,   368,   368,   374,   356,
     358,   359,   358,   360,   361,   375,   358,   363,   364,   363,
     363,   366,   218,   490,   358,   368,   369,   368,   369,   368,
     369,   363,   358,   357,   377,   360,   377,    33,   377,   363,
     363,   377,   377,    33,    34,   363,   377,   377,   232,   490,
     368,    33,   377,    33,   377,    33,   377,   368,   368,   368,
      33,   377,    33,   377,   368,   358,   360,   363,   363,   377,
      33,   363,   360,    92,    93,    94,   353,   535,    97,    98,
     188,   189,   192,   460,   461,    97,    98,    99,   537,    99,
     101,   102,   103,   539,   105,   106,   107,   108,   109,   541,
      97,    98,   101,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   543,    99,   101,   119,   121,   122,   123,   124,
     545,    97,    98,   111,   113,   114,   115,   128,   129,   130,
     547,    99,   101,   119,   121,   122,   124,   132,   133,   549,
     112,   122,   129,   135,   136,   551,   122,   136,   553,   129,
     139,   140,   555,   115,   119,   142,   143,   557,   119,   142,
     143,   145,   559,   119,   122,   135,   139,   142,   143,   147,
     148,   149,   150,   151,   561,    99,   142,   143,   565,   119,
     142,   143,   171,   567,    99,   110,   112,   124,   126,   129,
     176,   208,   209,   520,   522,   572,   177,   574,   177,   576,
     139,   178,   179,   180,   578,   112,   129,   570,   101,   116,
     129,   135,   183,   184,   580,   112,   129,   582,    99,   112,
     119,   129,   135,   584,    89,   115,   118,   127,   261,   512,
     513,   514,    97,    98,   118,   188,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   226,
     227,   228,   524,   525,   528,   261,   271,   517,   467,   473,
     272,   172,   181,   182,   185,   186,   586,   353,   466,   319,
     281,   319,    34,    36,    38,    39,    46,    47,    78,   317,
     368,   353,   226,   486,   487,   240,   494,   495,   242,   243,
     400,   488,   489,    88,    88,    88,   446,   353,   353,    84,
     353,    89,   512,   524,   525,   225,   225,   240,   225,   400,
      72,    72,     4,   299,   475,   476,   279,   376,   381,   226,
     227,   389,   390,   139,   234,   235,   236,   237,   238,   393,
     394,   255,   409,     5,    21,    58,    72,    96,   100,   104,
     110,   114,   126,   172,   219,   222,   223,   257,   258,   284,
     285,   412,   413,   414,   415,   416,   417,   418,   420,   421,
     422,   423,   424,   425,   426,   455,   456,   505,   506,   507,
     511,   518,   519,   521,   523,   529,   530,   533,    72,   261,
     262,   263,   429,   435,   436,    72,   432,   435,   265,   266,
     267,   439,   440,   441,   442,    23,   455,    33,   450,   451,
      15,    16,    17,    18,   290,     8,    24,    42,     9,    10,
      11,    12,    13,    14,    21,    96,   100,   104,   110,   120,
     126,   131,   134,   137,   138,   141,   144,   146,   169,   170,
     260,   455,   456,   468,   469,   470,   471,   474,   497,   498,
     499,   500,   501,   502,   503,   504,   506,   507,   508,   509,
      40,    40,   485,   497,   498,   485,   288,   288,   288,   288,
     288,   371,   378,   321,   324,   326,   328,   331,   335,   368,
     487,   495,   489,   378,    45,    45,    45,   328,   368,    45,
     328,   358,   363,   377,    33,   368,   358,   358,   358,   358,
     358,   363,   353,     7,     8,    99,   192,   193,   459,   149,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   562,   522,   294,   294,    97,    98,   118,   211,   212,
     213,   520,   526,   528,   272,   272,    88,   293,   318,   319,
     493,    88,   242,   243,   404,    88,   443,   444,   467,    23,
      82,   288,    40,    40,   528,    40,   425,   425,   404,   425,
      88,   425,   473,   471,   474,   479,   480,   483,   503,   504,
       7,   289,   354,    88,    88,   390,    65,    96,   110,   146,
     195,   396,   354,    88,    88,    88,   354,   395,   394,   120,
     131,   146,   256,   425,     5,   425,    15,    16,    17,    18,
     290,    20,    22,     8,    42,     5,   435,     7,     7,     5,
       7,     5,   425,   425,   440,     7,   288,   353,   288,   451,
     457,   457,   462,   463,   464,   466,    23,   288,   384,   498,
       7,    15,    16,    17,    18,   290,     7,    20,    22,     8,
     292,   498,   425,   425,   298,   298,   323,   325,   327,   332,
     336,   288,   288,   288,   288,   288,   493,    88,    88,    88,
     493,    88,   358,    88,   461,    82,   115,   163,   164,   165,
     166,   167,   168,   563,    88,    88,    97,    98,   527,    88,
      88,   273,   516,   288,   227,    88,    89,   227,   401,   455,
      76,   376,   481,   482,   354,    88,   467,   477,   478,   425,
     425,    40,   425,    88,   401,    31,   299,     5,   299,   481,
     299,   476,   125,   122,   125,   397,   398,    99,    99,    58,
      99,   425,     5,   412,   455,   507,   508,   413,   414,   415,
      88,   417,   412,   419,   455,   474,   425,   455,   507,   529,
     529,   425,   436,   425,   435,   442,   443,   477,   353,   299,
     385,   386,   503,   508,   508,   499,   500,   501,   503,    88,
     503,   503,   498,    35,    40,    42,    44,   139,   210,   224,
     239,   244,   289,   298,   300,   322,    79,    99,   289,   298,
     300,   348,   351,   378,    75,    76,    77,    78,    79,    82,
      99,   139,   289,   298,   300,   333,    76,    78,    99,   139,
     289,   298,   300,   333,    30,    32,   289,   298,   300,   323,
     325,   327,   332,   336,   288,     7,   295,   295,   516,   276,
     516,    88,   345,    88,    20,    89,   245,   402,    89,   355,
     482,   288,   381,   481,   425,    20,    89,   402,   425,   484,
     503,   504,   510,     7,    89,    89,    89,   425,   435,   435,
       5,   289,   381,   479,     7,   289,   293,   353,   362,   353,
     365,   365,   353,   367,    89,   218,   353,   370,   370,   370,
     298,    66,    67,   352,    89,   298,   298,   298,   355,   355,
     287,    80,    81,   334,    88,    89,   113,   114,   188,   208,
     340,   341,   347,    73,    74,    76,   329,   330,   298,   355,
     287,   341,   329,   298,    89,   287,   289,   289,   289,   289,
     289,   345,    88,    88,    99,   211,   289,   298,   300,   492,
     249,   250,   251,   252,   253,   406,   241,   405,    88,   477,
     289,   406,   405,   299,   398,   443,   289,     5,   299,   386,
     324,   326,   331,   335,   370,   342,   342,   342,    30,   298,
     298,   328,     8,   298,     7,   298,   298,   328,     5,   298,
     127,   288,   337,   289,   516,    90,   357,   298,   405,    88,
     401,   381,   405,   289,   510,   288,   288,   288,   288,   342,
     288,   288,   288,    89,   340,   330,   224,   239,   244,   341,
      22,    88,   349,    89,   338,   339,   298,   298,   118,   298,
      89,   226,   227,   289,   299,   325,   327,   332,   336,   288,
     343,   346,   344,    31,   350,   298,   298,   298,   298,    88,
     298,     7,   289,   141,   146,   491,   289,   289,   289,   289,
     345,   289,   298,   300,   486,   289,   298,   300,   494,   289,
     298,   300,   488,    89,   127,   299,   339,   298,   298,   298,
     298,   298,   289,   298,   298,   298,   349,   298
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   296,   297,   297,   298,   298,   299,   299,   300,   300,
     300,   300,   300,   301,   301,   301,   301,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   304,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   306,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   307,   308,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   310,   310,   310,   310,
     310,   310,   311,   311,   311,   311,   311,   311,   311,   312,
     313,   313,   314,   314,   315,   316,   316,   317,   317,   317,
     317,   317,   317,   317,   317,   318,   318,   319,   319,   319,
     320,   321,   322,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   324,   325,   325,   325,   325,
     325,   325,   326,   327,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   328,   328,   329,   329,   330,   330,   330,
     331,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   333,   333,   334,   334,   335,   336,   336,   336,
     336,   336,   337,   338,   338,   338,   339,   340,   341,   341,
     342,   343,   343,   343,   343,   344,   344,   344,   344,   345,
     345,   345,   345,   346,   346,   346,   346,   347,   347,   347,
     347,   347,   348,   349,   349,   350,   350,   351,   352,   352,
     353,   354,   354,   354,   355,   356,   356,   357,   357,   357,
     357,   357,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     374,   374,   374,   375,   376,   377,   377,   378,   378,   379,
     380,   380,   381,   381,   381,   381,   381,   381,   381,   381,
     381,   381,   381,   381,   381,   381,   381,   381,   381,   381,
     381,   382,   382,   383,   384,   384,   385,   385,   385,   386,
     387,   387,   388,   388,   389,   389,   390,   390,   391,   391,
     392,   393,   393,   394,   394,   394,   394,   394,   394,   395,
     396,   396,   396,   396,   396,   397,   397,   398,   398,   399,
     399,   399,   400,   400,   400,   401,   401,   402,   402,   403,
     403,   404,   404,   404,   405,   405,   405,   405,   406,   406,
     406,   406,   406,   407,   408,   409,   409,   409,   409,   409,
     410,   411,   411,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   413,   413,   413,   414,   414,   415,   415,
     416,   416,   417,   418,   418,   419,   419,   420,   420,   421,
     422,   423,   424,   424,   424,   425,   425,   425,   426,   426,
     426,   426,   426,   426,   426,   427,   427,   428,   429,   429,
     429,   430,   430,   431,   432,   432,   432,   432,   432,   433,
     433,   434,   435,   435,   436,   436,   436,   437,   437,   438,
     439,   439,   440,   440,   441,   441,   442,   442,   443,   443,
     444,   445,   445,   446,   446,   447,   448,   448,   449,   450,
     450,   451,   452,   452,   453,   454,   455,   455,   455,   456,
     457,   457,   457,   457,   457,   457,   457,   457,   457,   457,
     457,   457,   458,   459,   459,   459,   460,   460,   460,   460,
     460,   461,   461,   462,   462,   462,   463,   463,   464,   464,
     465,   465,   466,   467,   467,   468,   469,   470,   471,   471,
     471,   472,   473,   473,   473,   474,   475,   475,   475,   476,
     476,   476,   477,   477,   478,   479,   479,   480,   481,   481,
     482,   482,   483,   483,   484,   484,   485,   485,   486,   487,
     488,   489,   490,   491,   491,   492,   492,   493,   494,   494,
     495,   496,   496,   496,   496,   497,   497,   498,   498,   498,
     499,   499,   499,   500,   500,   501,   501,   502,   502,   503,
     504,   504,   505,   505,   506,   507,   507,   507,   507,   507,
     507,   507,   507,   507,   507,   507,   507,   508,   508,   508,
     508,   508,   508,   508,   508,   508,   508,   508,   508,   508,
     508,   508,   509,   509,   509,   509,   509,   509,   510,   510,
     510,   510,   510,   510,   511,   511,   511,   512,   512,   513,
     513,   513,   513,   514,   514,   514,   514,   514,   514,   514,
     514,   514,   514,   514,   514,   514,   514,   514,   514,   514,
     514,   514,   514,   515,   515,   515,   515,   515,   516,   516,
     517,   517,   518,   519,   519,   519,   520,   520,   521,   521,
     522,   522,   522,   523,   523,   523,   524,   524,   525,   525,
     525,   525,   525,   525,   525,   525,   525,   525,   525,   525,
     525,   525,   525,   526,   526,   526,   526,   526,   526,   526,
     527,   527,   528,   528,   528,   528,   529,   529,   530,   530,
     531,   531,   532,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   534,
     535,   535,   535,   536,   537,   537,   537,   538,   539,   539,
     539,   539,   540,   541,   541,   541,   541,   541,   542,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   544,   545,   545,   545,   545,   545,   545,   545,   546,
     547,   547,   547,   547,   547,   547,   547,   547,   547,   548,
     549,   549,   549,   549,   549,   549,   549,   549,   550,   551,
     551,   551,   551,   551,   552,   553,   553,   554,   555,   555,
     555,   556,   557,   557,   557,   557,   558,   559,   559,   559,
     559,   560,   560,   560,   561,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   562,   562,   562,   562,   562,   562,
     562,   562,   562,   562,   562,   562,   563,   563,   563,   563,
     563,   563,   563,   563,   564,   565,   565,   565,   566,   567,
     567,   567,   567,   568,   568,   568,   568,   568,   568,   568,
     568,   569,   570,   570,   571,   572,   572,   572,   572,   573,
     574,   575,   576,   577,   578,   578,   578,   578,   579,   580,
     580,   580,   580,   580,   580,   581,   582,   582,   583,   584,
     584,   584,   584,   584,   585,   586,   586,   586,   586,   586
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
       1,     1,     1,     3,     3,     2,     1,     3,     3,     5,
       1,     2,     1,     3,     1,     2,     2,     2,     1,     2,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     1,
       2,     2,     1,     1,     1,     3,     1,     1,     1,     7,
       6,     3,     1,     1,     0,     1,     1,     0,     3,     5,
       3,     1,     1,     0,     0,     3,     3,     3,     1,     1,
       1,     1,     1,     2,     1,     0,     4,     4,     4,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     1,     1,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     4,     2,     3,     2,     2,     1,     1,     3,     4,
       1,     2,     1,     1,     2,     3,     1,     3,     4,     3,
       5,     3,     1,     3,     1,     1,     1,     1,     2,     1,
       1,     2,     2,     1,     1,     3,     1,     1,     1,     2,
       1,     4,     5,     1,     1,     7,     6,     1,     1,     1,
       2,     2,     6,     8,     1,     2,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     3,     3,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     3,     3,     3,
       3,     5,     1,     2,     1,     1,     2,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     4,     1,
       4,     1,     1,     1,     1,     5,     3,     0,     6,     5,
       1,     2,     2,     3,     5,     3,     3,     1,     1,     1,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     3,     4,     1,     4,     0,     2,
       1,     1,     5,     7,     5,     4,     1,     1,     2,     3,
       1,     1,     1,     2,     3,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       4,     5,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     6,
       1,     1,     1,     2,     1,     1,     1,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     1,     1,
       1,     2,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     2,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
          case 89: /* "string"  */
#line 263 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3652 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 90: /* "quoted string"  */
#line 263 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3658 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 91: /* "string with a trailing asterisk"  */
#line 263 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3664 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 301: /* line  */
#line 511 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3670 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 302: /* base_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3676 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 303: /* add_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3682 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 304: /* replace_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3688 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 305: /* create_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3694 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 306: /* insert_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3700 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 307: /* delete_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3706 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 308: /* get_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3712 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 309: /* list_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3718 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 310: /* reset_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3724 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 311: /* flush_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3730 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 312: /* rename_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3736 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 313: /* import_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3742 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 314: /* export_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3748 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 315: /* monitor_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3754 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 316: /* monitor_event  */
#line 711 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3760 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 320: /* describe_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3766 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 321: /* table_block_alloc  */
#line 526 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 3772 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 324: /* chain_block_alloc  */
#line 528 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 3778 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 326: /* set_block_alloc  */
#line 537 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3784 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 328: /* set_block_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3790 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 331: /* map_block_alloc  */
#line 540 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3796 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* flowtable_block_alloc  */
#line 543 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 3802 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* flowtable_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3808 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* flowtable_list_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3814 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* flowtable_expr_member  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3820 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* data_type_atom_expr  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3826 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* data_type_expr  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3832 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* obj_block_alloc  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 3838 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* type_identifier  */
#line 503 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3844 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* dev_spec  */
#line 523 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3850 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 353: /* identifier  */
#line 503 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3856 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* string  */
#line 503 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3862 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* table_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3868 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 359: /* tableid_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3874 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* chain_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3880 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* chainid_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3886 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 362: /* chain_identifier  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3892 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 363: /* set_spec  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3898 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 364: /* setid_spec  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3904 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 365: /* set_identifier  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3910 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 366: /* flowtable_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3916 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 368: /* obj_spec  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3922 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 369: /* objid_spec  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3928 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 370: /* obj_identifier  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3934 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 371: /* handle_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3940 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 372: /* position_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3946 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* index_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3952 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 374: /* rule_position  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3958 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* ruleid_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3964 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* comment_spec  */
#line 503 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3970 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* ruleset_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3976 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 378: /* rule  */
#line 530 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 3982 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 380: /* stmt_list  */
#line 549 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 3988 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 381: /* stmt  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3994 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 382: /* verdict_stmt  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4000 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* verdict_map_stmt  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4006 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* verdict_map_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4012 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* verdict_map_list_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4018 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* verdict_map_list_member_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4024 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* counter_stmt  */
#line 553 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4030 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* counter_stmt_alloc  */
#line 553 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4036 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* log_stmt  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4042 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* log_stmt_alloc  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4048 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* limit_stmt  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4054 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* quota_unit  */
#line 523 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4060 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* quota_stmt  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4066 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* reject_stmt  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4072 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* reject_stmt_alloc  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4078 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* nat_stmt  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4084 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* nat_stmt_alloc  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4090 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 412: /* primary_stmt_expr  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4096 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* shift_stmt_expr  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4102 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* and_stmt_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4108 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* exclusive_or_stmt_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4114 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* inclusive_or_stmt_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4120 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* basic_stmt_expr  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4126 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* concat_stmt_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4132 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* map_stmt_expr_set  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4138 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* map_stmt_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4144 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* prefix_stmt_expr  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4150 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* range_stmt_expr  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4156 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* wildcard_stmt_expr  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4162 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* multiton_stmt_expr  */
#line 604 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4168 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* stmt_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4174 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* masq_stmt  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4180 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* masq_stmt_alloc  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4186 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* redir_stmt  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4192 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* redir_stmt_alloc  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4198 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* dup_stmt  */
#line 575 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4204 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* fwd_stmt  */
#line 577 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4210 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* queue_stmt  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4216 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* queue_stmt_alloc  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4222 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* set_elem_expr_stmt  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4228 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 444: /* set_elem_expr_stmt_alloc  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4234 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 445: /* set_stmt  */
#line 579 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4240 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 447: /* map_stmt  */
#line 582 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4246 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* meter_stmt  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4252 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 449: /* flow_stmt_legacy_alloc  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4258 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* meter_stmt_alloc  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4264 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 453: /* match_stmt  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4270 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 454: /* variable_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4276 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 455: /* symbol_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4282 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 456: /* integer_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4288 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* primary_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4294 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* fib_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4300 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* shift_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4306 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 463: /* and_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4312 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* exclusive_or_expr  */
#line 591 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4318 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* inclusive_or_expr  */
#line 591 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4324 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* basic_expr  */
#line 593 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4330 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 467: /* concat_expr  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4336 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* prefix_rhs_expr  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4342 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* range_rhs_expr  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4348 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* wildcard_rhs_expr  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4354 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* multiton_rhs_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4360 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* map_expr  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4366 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4372 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* set_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4378 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* set_list_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4384 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* set_list_member_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4390 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* meter_key_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4396 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* meter_key_expr_alloc  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4402 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* set_elem_expr  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4408 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* set_elem_expr_alloc  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4414 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 483: /* set_lhs_expr  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4420 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* set_rhs_expr  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4426 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* initializer_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4432 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 486: /* counter_config  */
#line 715 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).counter)); }
#line 4438 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* counter_obj  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4444 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* quota_config  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).quota)); }
#line 4450 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 489: /* quota_obj  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4456 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 493: /* ct_obj_alloc  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4462 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* limit_config  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).limit)); }
#line 4468 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 495: /* limit_obj  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4474 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 496: /* relational_expr  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4480 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 497: /* list_rhs_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4486 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 498: /* rhs_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4492 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 499: /* shift_rhs_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4498 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* and_rhs_expr  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4504 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* exclusive_or_rhs_expr  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4510 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 502: /* inclusive_or_rhs_expr  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4516 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 503: /* basic_rhs_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4522 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 504: /* concat_rhs_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4528 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* boolean_expr  */
#line 727 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4534 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* keyword_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4540 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 508: /* primary_rhs_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4546 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* verdict_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4552 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 511: /* meta_expr  */
#line 692 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4558 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 515: /* meta_stmt  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4564 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* numgen_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4570 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* hash_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4576 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 521: /* rt_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4582 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* ct_expr  */
#line 702 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4588 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* symbol_stmt_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4594 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* list_stmt_expr  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4600 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* ct_stmt  */
#line 557 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4606 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* payload_stmt  */
#line 555 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4612 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* payload_expr  */
#line 655 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4618 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* payload_raw_expr  */
#line 655 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4624 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* eth_hdr_expr  */
#line 658 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4630 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* vlan_hdr_expr  */
#line 658 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4636 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* arp_hdr_expr  */
#line 661 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4642 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 542: /* ip_hdr_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4648 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 544: /* icmp_hdr_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4654 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 546: /* ip6_hdr_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4660 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 548: /* icmp6_hdr_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4666 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 550: /* auth_hdr_expr  */
#line 670 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4672 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 552: /* esp_hdr_expr  */
#line 670 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4678 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 554: /* comp_hdr_expr  */
#line 670 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4684 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 556: /* udp_hdr_expr  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4690 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 558: /* udplite_hdr_expr  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4696 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 560: /* tcp_hdr_expr  */
#line 722 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4702 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 564: /* dccp_hdr_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4708 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 566: /* sctp_hdr_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4714 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 568: /* exthdr_expr  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4720 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 569: /* hbh_hdr_expr  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4726 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 571: /* rt_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4732 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 573: /* rt0_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4738 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 575: /* rt2_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4744 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 577: /* rt4_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4750 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 579: /* frag_hdr_expr  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4756 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 581: /* dst_hdr_expr  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4762 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 583: /* mh_hdr_expr  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4768 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 585: /* exthdr_exists_expr  */
#line 731 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4774 "parser_bison.c" /* yacc.c:1257  */
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

#line 4891 "parser_bison.c" /* yacc.c:1429  */
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
#line 740 "parser_bison.y" /* yacc.c:1646  */
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
#line 5094 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 8:
#line 766 "parser_bison.y" /* yacc.c:1646  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 9:
#line 774 "parser_bison.y" /* yacc.c:1646  */
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
#line 5124 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 788 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 5135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 11:
#line 795 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 5150 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 806 "parser_bison.y" /* yacc.c:1646  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 5160 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 813 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 5166 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 814 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 5172 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 815 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 5178 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 16:
#line 817 "parser_bison.y" /* yacc.c:1646  */
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
#line 5212 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 848 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5218 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 849 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5224 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 850 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5230 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 851 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5236 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 852 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5242 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 853 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5248 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 854 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5254 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 855 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5260 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 856 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5266 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 857 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5272 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 858 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5278 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 859 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5284 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 860 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5290 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 861 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5296 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 862 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5302 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 866 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5310 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 871 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5320 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 877 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5328 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 882 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5339 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 889 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5347 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 893 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 898 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5365 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 905 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5375 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 911 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5383 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 916 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5393 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 42:
#line 922 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5406 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 931 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5414 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 935 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5422 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 939 "parser_bison.y" /* yacc.c:1646  */
    {

				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5431 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 944 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5439 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 950 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 956 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 961 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5465 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 967 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 972 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5484 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 980 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5494 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 987 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5504 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 993 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5512 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 998 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1004 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5535 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1013 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5543 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1017 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5551 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1021 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1025 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5567 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1031 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5575 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1037 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5583 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1041 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1045 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5599 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1049 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5607 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1053 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5615 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1057 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5623 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1061 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5631 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1065 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5639 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1069 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5647 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1073 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1077 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5663 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1081 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5671 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1085 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5679 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1089 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5687 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1093 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5695 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1097 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5703 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1101 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5711 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1107 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5719 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1113 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5727 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1117 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5735 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1121 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5743 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1125 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5751 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1129 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5759 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1133 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5767 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1137 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5775 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1141 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1145 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5791 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1149 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5799 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1153 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5807 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1157 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5815 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1161 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5823 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1165 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5831 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1169 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5839 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1173 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5847 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1177 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5855 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1181 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5863 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1185 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5871 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1189 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5879 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1193 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5887 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1197 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5895 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1201 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5903 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1205 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5911 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1209 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5919 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1213 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5927 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1219 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5935 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1223 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5943 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1227 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 5951 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1231 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5959 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1235 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5967 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1239 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5975 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1245 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5983 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1249 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5991 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1253 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5999 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1257 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1261 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6015 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1265 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6023 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1269 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6031 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1275 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 6040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1282 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6050 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1288 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6060 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1296 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6070 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1302 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6080 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1310 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 6091 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1318 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1319 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1322 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 6109 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1323 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 6115 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1324 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 6121 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1325 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 6127 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1326 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 6133 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1327 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 6139 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1328 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 6145 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1329 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 6151 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1332 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 6157 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1336 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 6163 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1337 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 6169 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1338 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 6175 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1342 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 6185 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1350 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 6194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1357 "parser_bison.y" /* yacc.c:1646  */
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
#line 6210 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1370 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 6216 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1377 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6229 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1388 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6241 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1398 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6253 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1409 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].flowtable)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].flowtable)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].flowtable)->list, &(yyvsp[-7].table)->flowtables);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6265 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1419 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6278 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1430 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6291 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1439 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 6304 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1450 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6317 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1461 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 6326 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1467 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 6332 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1473 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 6341 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1480 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6349 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1485 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1489 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6364 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1494 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1499 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6382 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1504 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6391 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1509 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6400 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1514 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 6409 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1526 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6417 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1532 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 6423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1533 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 6429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1534 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 6435 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1538 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6443 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1543 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6449 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1547 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6458 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1554 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].expr)->dtype;

				expr_free((yyvsp[-1].expr));
				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6471 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1565 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6482 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1574 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6493 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1583 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6504 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1590 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6513 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1595 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1603 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 6530 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1607 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 6538 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1612 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 6544 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1613 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 6550 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1617 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 6558 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1622 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 6564 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1626 "parser_bison.y" /* yacc.c:1646  */
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
#line 6581 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1639 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 6589 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1645 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6598 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1652 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 6607 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1657 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 6616 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1665 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
			}
#line 6626 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1673 "parser_bison.y" /* yacc.c:1646  */
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
#line 6642 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1688 "parser_bison.y" /* yacc.c:1646  */
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
#line 6663 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1707 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 6671 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1712 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6677 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1716 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->counter = *(yyvsp[0].counter);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6686 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1722 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6692 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1726 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->quota = *(yyvsp[0].quota);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6701 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1732 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6707 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1736 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6715 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1741 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6721 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1745 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->limit = *(yyvsp[0].limit);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6730 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1751 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6736 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1752 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("mark"); }
#line 6742 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1753 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("dscp"); }
#line 6748 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1754 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("ecn"); }
#line 6754 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1755 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("classid"); }
#line 6760 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1759 "parser_bison.y" /* yacc.c:1646  */
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
#line 6790 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1786 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 6796 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1787 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = -(yyvsp[0].val); }
#line 6802 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1790 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6808 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1791 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6814 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1795 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].chain)->policy != -1) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].val);
			}
#line 6827 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1805 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_ACCEPT; }
#line 6833 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1806 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_DROP;   }
#line 6839 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1818 "parser_bison.y" /* yacc.c:1646  */
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
#line 6856 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1832 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6862 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1836 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6868 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1837 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 6874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1838 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_INET; }
#line 6880 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1839 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_ARP; }
#line 6886 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1840 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 6892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1841 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 6898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1845 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table.location = (yylsp[0]);
				(yyval.handle).table.name	= (yyvsp[0].string);
			}
#line 6909 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1854 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yyloc);
			}
#line 6920 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1863 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain.name	= (yyvsp[0].string);
				(yyval.handle).chain.location = (yylsp[0]);
			}
#line 6930 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1871 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 6940 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1879 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain.name		= (yyvsp[0].string);
				(yyval.handle).chain.location	= (yylsp[0]);
			}
#line 6950 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1887 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 6960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1895 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 6970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1903 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set.name	= (yyvsp[0].string);
				(yyval.handle).set.location	= (yylsp[0]);
			}
#line 6980 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1912 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).flowtable	= (yyvsp[0].string);
			}
#line 6989 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1919 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable	= (yyvsp[0].string);
			}
#line 6998 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1926 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj.name	= (yyvsp[0].string);
				(yyval.handle).obj.location	= (yylsp[0]);
			}
#line 7008 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1934 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 7018 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1942 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj.name		= (yyvsp[0].string);
				(yyval.handle).obj.location		= (yylsp[0]);
			}
#line 7028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1950 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 7038 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1958 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 7048 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1966 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).index.location	= (yyloc);
				(yyval.handle).index.id		= (yyvsp[0].val) + 1;
			}
#line 7058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1974 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 7066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1978 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7075 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1983 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].handle).position.location = (yyvsp[0].handle).handle.location;
				(yyvsp[0].handle).position.id = (yyvsp[0].handle).handle.id;
				(yyvsp[0].handle).handle.id = 0;
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7087 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1991 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1998 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7105 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 274:
#line 2005 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strlen((yyvsp[0].string)) > UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed", UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 7118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 275:
#line 2016 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 7127 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 276:
#line 2021 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 7136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 277:
#line 2028 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 7144 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 278:
#line 2032 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 7152 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 279:
#line 2038 "parser_bison.y" /* yacc.c:1646  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 7166 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 280:
#line 2050 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 7176 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 281:
#line 2056 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 7185 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 301:
#line 2084 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7193 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 302:
#line 2088 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 303:
#line 2094 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7209 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2100 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7218 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2105 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7229 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2114 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7238 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2119 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 309:
#line 2127 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 7255 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 312:
#line 2136 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 7263 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 313:
#line 2140 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7273 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 314:
#line 2148 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7281 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 316:
#line 2155 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 7289 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 317:
#line 2159 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 7297 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2169 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 7305 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 321:
#line 2175 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7313 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2182 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 7322 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2187 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 7331 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2192 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 7340 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2197 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 7349 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2202 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 7358 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 328:
#line 2207 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 7366 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 329:
#line 2213 "parser_bison.y" /* yacc.c:1646  */
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
				else {
					erec_queue(error(&(yylsp[0]), "invalid log level"),
						   state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}
				xfree((yyvsp[0].string));
			}
#line 7396 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2241 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 7404 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2245 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 7412 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2249 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 7420 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2253 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 7428 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2257 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 7436 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2263 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7444 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2270 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 7452 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2274 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 7460 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2280 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 7473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2289 "parser_bison.y" /* yacc.c:1646  */
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
#line 7496 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2308 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7506 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2315 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 7512 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2316 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7518 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2317 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7524 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2320 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("bytes"); }
#line 7530 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2321 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7536 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2324 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7542 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 348:
#line 2326 "parser_bison.y" /* yacc.c:1646  */
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
#line 7559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 349:
#line 2341 "parser_bison.y" /* yacc.c:1646  */
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
#line 7579 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 350:
#line 2357 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7589 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2364 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 7595 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 352:
#line 2365 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7601 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 353:
#line 2366 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7607 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 354:
#line 2369 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 355:
#line 2370 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 7619 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 356:
#line 2371 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 7625 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 357:
#line 2373 "parser_bison.y" /* yacc.c:1646  */
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
#line 7642 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 358:
#line 2387 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL; }
#line 7648 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2388 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60; }
#line 7654 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 360:
#line 2389 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 7660 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 361:
#line 2390 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 7666 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2391 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 7672 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 364:
#line 2398 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 7680 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2404 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 7689 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2409 "parser_bison.y" /* yacc.c:1646  */
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
#line 7704 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2420 "parser_bison.y" /* yacc.c:1646  */
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
#line 7719 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2431 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpx_code_type;
				xfree((yyvsp[0].string));
			}
#line 7733 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2441 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 7741 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 371:
#line 2449 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 7747 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 372:
#line 2450 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 7753 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2453 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7759 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2454 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7765 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2455 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7771 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2456 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7777 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2457 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2458 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7789 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2459 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7795 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2460 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7801 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 381:
#line 2461 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7807 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2462 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7813 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2467 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7821 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2471 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7829 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 387:
#line 2478 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7837 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 389:
#line 2485 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7845 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2492 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2502 "parser_bison.y" /* yacc.c:1646  */
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
#line 7874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2525 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7882 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2528 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7888 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2532 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 7896 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2538 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2544 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 7917 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2565 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7925 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2569 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7933 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2573 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7942 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2578 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7951 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2583 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7959 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2587 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7967 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2591 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7975 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2600 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 7981 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2604 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7989 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2608 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7998 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2613 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8006 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2622 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 8012 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2626 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8020 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2630 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 8028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2634 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8036 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2638 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8045 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2643 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 8054 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2650 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 8063 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2655 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 8073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2663 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.to = (yyvsp[0].expr);
			}
#line 8082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2671 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8090 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2676 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 8096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2677 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 8102 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2678 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 8108 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2686 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 8116 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2692 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8124 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2699 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 8133 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2704 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 8141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2711 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8149 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2716 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 8155 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2717 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 8161 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2725 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8169 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2731 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 8180 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2738 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 8191 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2746 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 8197 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2747 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 8203 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 455:
#line 2751 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.map = map_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 8214 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2760 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 8225 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2766 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 8231 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2770 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 8239 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2776 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2783 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 8255 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2789 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.size = 0xffff;
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 8268 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 463:
#line 2798 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-6].string);
				(yyval.stmt)->meter.size = (yyvsp[-4].val);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 8281 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2809 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8289 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2815 "parser_bison.y" /* yacc.c:1646  */
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
#line 8309 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2834 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 8320 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2841 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 8331 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2850 "parser_bison.y" /* yacc.c:1646  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 8344 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2860 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8350 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2861 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8356 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 472:
#line 2862 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8362 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2863 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8368 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2864 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8374 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2865 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8380 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2866 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8386 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2867 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8392 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2868 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8398 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2869 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8404 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2870 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8410 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2871 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 8416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2875 "parser_bison.y" /* yacc.c:1646  */
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
#line 8441 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2897 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 8447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2898 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 8453 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2899 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 8459 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2902 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 8465 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 487:
#line 2903 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 8471 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 488:
#line 2904 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 8477 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 489:
#line 2905 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 8483 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2906 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 8489 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 491:
#line 2910 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8497 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 494:
#line 2918 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8505 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 495:
#line 2922 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8513 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2929 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8521 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 499:
#line 2936 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8529 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2943 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8537 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 504:
#line 2953 "parser_bison.y" /* yacc.c:1646  */
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
#line 8558 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 505:
#line 2972 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 8566 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 506:
#line 2978 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8574 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 507:
#line 2984 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 8587 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 511:
#line 3000 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8595 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 515:
#line 3011 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8604 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 516:
#line 3018 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 517:
#line 3023 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8622 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 519:
#line 3031 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8630 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 520:
#line 3035 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8638 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 521:
#line 3039 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 8646 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 523:
#line 3046 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 524:
#line 3053 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8663 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 527:
#line 3063 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8671 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 528:
#line 3069 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 8679 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 530:
#line 3076 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val);
			}
#line 8687 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 531:
#line 3080 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 8695 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 538:
#line 3098 "parser_bison.y" /* yacc.c:1646  */
    {
				struct counter *counter;

				counter = xzalloc(sizeof(*counter));
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
				(yyval.counter) = counter;
			}
#line 8708 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 539:
#line 3109 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
				(yyval.obj)->counter = *(yyvsp[0].counter);
			}
#line 8718 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 540:
#line 3117 "parser_bison.y" /* yacc.c:1646  */
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
#line 8741 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 541:
#line 3138 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
				(yyval.obj)->quota = *(yyvsp[0].quota);
			}
#line 8751 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 542:
#line 3145 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 8757 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 543:
#line 3148 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_TCP; }
#line 8763 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 544:
#line 3149 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_UDP; }
#line 8769 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 545:
#line 3153 "parser_bison.y" /* yacc.c:1646  */
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
#line 8788 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 546:
#line 3168 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 8796 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 547:
#line 3174 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 8804 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 548:
#line 3180 "parser_bison.y" /* yacc.c:1646  */
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
#line 8819 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 549:
#line 3191 "parser_bison.y" /* yacc.c:1646  */
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
#line 8843 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 550:
#line 3213 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
				(yyval.obj)->limit = *(yyvsp[0].limit);
			}
#line 8853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 551:
#line 3221 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8861 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 552:
#line 3225 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8869 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 553:
#line 3229 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8877 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 554:
#line 3233 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-3]), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[-1].expr));
			}
#line 8885 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 555:
#line 3239 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8895 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 556:
#line 3245 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8905 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 557:
#line 3252 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8911 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 558:
#line 3253 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8917 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 559:
#line 3254 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8923 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 561:
#line 3259 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8931 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 562:
#line 3263 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8939 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 564:
#line 3270 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8947 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 566:
#line 3277 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8955 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 568:
#line 3284 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8963 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 571:
#line 3294 "parser_bison.y" /* yacc.c:1646  */
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
#line 8984 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 572:
#line 3312 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = true; }
#line 8990 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 573:
#line 3313 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = false; }
#line 8996 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 574:
#line 3317 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 1, &(yyvsp[0].val));
			}
#line 9006 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 575:
#line 3324 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 9012 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 576:
#line 3325 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 9018 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 577:
#line 3326 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 9024 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 578:
#line 3327 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 9030 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 579:
#line 3328 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 9036 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 580:
#line 3329 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 9042 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 581:
#line 3330 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 9048 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 582:
#line 3331 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 9054 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 583:
#line 3332 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 9060 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 584:
#line 3333 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 9066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 585:
#line 3334 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 9072 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 586:
#line 3335 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 9078 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 587:
#line 3338 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9084 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 588:
#line 3339 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9090 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 589:
#line 3340 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 590:
#line 3341 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9102 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 591:
#line 3343 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9113 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 592:
#line 3350 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9124 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 593:
#line 3357 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 594:
#line 3364 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9146 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 595:
#line 3371 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9157 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 596:
#line 3378 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9168 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 597:
#line 3385 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9179 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 598:
#line 3392 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9190 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 599:
#line 3399 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 600:
#line 3406 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9212 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 601:
#line 3413 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9223 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 602:
#line 3421 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_EQ; }
#line 9229 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 603:
#line 3422 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_NEQ; }
#line 9235 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 604:
#line 3423 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LT; }
#line 9241 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 605:
#line 3424 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GT; }
#line 9247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 606:
#line 3425 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GTE; }
#line 9253 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 607:
#line 3426 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LTE; }
#line 9259 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 608:
#line 3430 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 9267 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 609:
#line 3434 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 9275 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 610:
#line 3438 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 9283 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 611:
#line 3442 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].string));
			}
#line 9291 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 612:
#line 3446 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].string));
			}
#line 9299 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 613:
#line 3450 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 9307 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 614:
#line 3456 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 9315 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 615:
#line 3460 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 9323 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 616:
#line 3464 "parser_bison.y" /* yacc.c:1646  */
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
#line 9341 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 619:
#line 3483 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_LEN; }
#line 9347 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 620:
#line 3484 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 9353 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 621:
#line 3485 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 9359 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 622:
#line 3486 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 9365 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 623:
#line 3489 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_MARK; }
#line 9371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 624:
#line 3490 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIF; }
#line 9377 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 625:
#line 3491 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 9383 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 626:
#line 3492 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 9389 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 627:
#line 3493 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIF; }
#line 9395 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 628:
#line 3494 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 9401 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 629:
#line 3495 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 9407 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 630:
#line 3496 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKUID; }
#line 9413 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 631:
#line 3497 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKGID; }
#line 9419 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 632:
#line 3498 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 9425 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 633:
#line 3499 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 9431 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 634:
#line 3500 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 9437 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 635:
#line 3501 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 9443 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 636:
#line 3502 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 9449 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 637:
#line 3503 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 9455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 638:
#line 3504 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 9461 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3505 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CPU; }
#line 9467 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 640:
#line 3506 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 9473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 641:
#line 3507 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 9479 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 642:
#line 3508 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 9485 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3512 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 9493 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 644:
#line 3516 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 9501 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 645:
#line 3520 "parser_bison.y" /* yacc.c:1646  */
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
#line 9519 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 646:
#line 3534 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 9527 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 647:
#line 3538 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 9535 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 648:
#line 3543 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 9541 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 649:
#line 3544 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 9547 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 650:
#line 3547 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 9553 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 651:
#line 3548 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 9559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 652:
#line 3552 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 9567 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 653:
#line 3558 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 9576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 654:
#line 3563 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 9585 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 655:
#line 3568 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 9593 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 656:
#line 3573 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 9599 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 657:
#line 3574 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 9605 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 658:
#line 3578 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 9613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 659:
#line 3582 "parser_bison.y" /* yacc.c:1646  */
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
#line 9635 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 660:
#line 3601 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 9641 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 661:
#line 3602 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 9647 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 662:
#line 3603 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 9653 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 663:
#line 3607 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1, NFPROTO_UNSPEC);
			}
#line 9661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 664:
#line 3611 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val), NFPROTO_UNSPEC);
			}
#line 9669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 665:
#line 3615 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 9677 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 666:
#line 3620 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 9683 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 667:
#line 3621 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 9689 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 668:
#line 3624 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9695 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 669:
#line 3625 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9701 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 670:
#line 3626 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_MARK; }
#line 9707 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 671:
#line 3627 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATE; }
#line 9713 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 672:
#line 3628 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 9719 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 673:
#line 3629 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 9725 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 674:
#line 3630 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 9731 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 675:
#line 3631 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 9737 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 676:
#line 3632 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9743 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 677:
#line 3633 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9749 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 678:
#line 3634 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9755 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 679:
#line 3635 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9761 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 680:
#line 3636 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 9767 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 681:
#line 3637 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 9773 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 683:
#line 3641 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9779 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 684:
#line 3642 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9785 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 685:
#line 3643 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9791 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 686:
#line 3644 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9797 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 687:
#line 3645 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9803 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 688:
#line 3646 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9809 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 690:
#line 3650 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9815 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 691:
#line 3651 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9821 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 692:
#line 3654 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 9827 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 693:
#line 3655 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 9833 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 694:
#line 3656 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 9839 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 695:
#line 3657 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 9845 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 698:
#line 3665 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9855 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 699:
#line 3671 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 700:
#line 3679 "parser_bison.y" /* yacc.c:1646  */
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
#line 9882 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 701:
#line 3692 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 9890 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 702:
#line 3698 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].expr)->ops->type == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9901 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 719:
#line 3725 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 9912 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 720:
#line 3733 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 9918 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 721:
#line 3734 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 9924 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 722:
#line 3735 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 9930 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 723:
#line 3739 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 9938 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 724:
#line 3744 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 9944 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 725:
#line 3745 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 9950 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 726:
#line 3746 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 9956 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 727:
#line 3750 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 9964 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 728:
#line 3755 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_VID; }
#line 9970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 729:
#line 3756 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_CFI; }
#line 9976 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 730:
#line 3757 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_PCP; }
#line 9982 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 731:
#line 3758 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 9988 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 732:
#line 3762 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 9996 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 733:
#line 3767 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HRD; }
#line 10002 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 734:
#line 3768 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PRO; }
#line 10008 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 735:
#line 3769 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HLN; }
#line 10014 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 736:
#line 3770 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PLN; }
#line 10020 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 737:
#line 3771 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_OP; }
#line 10026 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 738:
#line 3775 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 10034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 739:
#line 3780 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_VERSION; }
#line 10040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 740:
#line 3781 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 10046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 741:
#line 3782 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DSCP; }
#line 10052 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 742:
#line 3783 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ECN; }
#line 10058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 743:
#line 3784 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 10064 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 744:
#line 3785 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ID; }
#line 10070 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 745:
#line 3786 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 10076 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 746:
#line 3787 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_TTL; }
#line 10082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 747:
#line 3788 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 10088 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 748:
#line 3789 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 10094 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 749:
#line 3790 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_SADDR; }
#line 10100 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 750:
#line 3791 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DADDR; }
#line 10106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 751:
#line 3795 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 10114 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 752:
#line 3800 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 10120 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 753:
#line 3801 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 10126 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 754:
#line 3802 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 10132 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 755:
#line 3803 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_ID; }
#line 10138 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 756:
#line 3804 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 10144 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 757:
#line 3805 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 10150 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 758:
#line 3806 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 10156 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 759:
#line 3810 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 10164 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 760:
#line 3815 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 10170 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 761:
#line 3816 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 10176 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 762:
#line 3817 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_ECN; }
#line 10182 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 763:
#line 3818 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 10188 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 764:
#line 3819 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 10194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 765:
#line 3820 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 10200 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 766:
#line 3821 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 10206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 767:
#line 3822 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 10212 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 768:
#line 3823 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 10218 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 769:
#line 3826 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 10226 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 770:
#line 3831 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 10232 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 771:
#line 3832 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 10238 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 772:
#line 3833 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 10244 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 773:
#line 3834 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 10250 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 774:
#line 3835 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 10256 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 775:
#line 3836 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 10262 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 776:
#line 3837 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 10268 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 777:
#line 3838 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 10274 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 778:
#line 3842 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 10282 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 779:
#line 3847 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 10288 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 780:
#line 3848 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 10294 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 781:
#line 3849 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 10300 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 782:
#line 3850 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SPI; }
#line 10306 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 783:
#line 3851 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 10312 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 784:
#line 3855 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 10320 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 785:
#line 3860 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SPI; }
#line 10326 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 786:
#line 3861 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 10332 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 787:
#line 3865 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 10340 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 788:
#line 3870 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 10346 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 789:
#line 3871 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 10352 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 790:
#line 3872 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_CPI; }
#line 10358 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 791:
#line 3876 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 10366 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 792:
#line 3881 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 10372 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 793:
#line 3882 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 10378 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 794:
#line 3883 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 10384 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 795:
#line 3884 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 10390 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 796:
#line 3888 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 10398 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 797:
#line 3893 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 10404 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 798:
#line 3894 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 10410 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 799:
#line 3895 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 10416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 800:
#line 3896 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 10422 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 801:
#line 3900 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 10430 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 802:
#line 3904 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 10438 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 803:
#line 3908 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 10447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 804:
#line 3914 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 10453 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 805:
#line 3915 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 10459 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 806:
#line 3916 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 10465 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 807:
#line 3917 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 10471 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 808:
#line 3918 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 10477 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 809:
#line 3919 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 10483 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 810:
#line 3920 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 10489 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 811:
#line 3921 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 10495 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 812:
#line 3922 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 10501 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 813:
#line 3923 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 10507 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 814:
#line 3926 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 10513 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 815:
#line 3927 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 10519 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 816:
#line 3928 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 10525 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 817:
#line 3929 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 10531 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 818:
#line 3930 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 10537 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 819:
#line 3931 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 10543 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 820:
#line 3932 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 10549 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 821:
#line 3933 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 10555 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 822:
#line 3934 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 10561 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 823:
#line 3935 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 10567 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 824:
#line 3936 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 10573 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 825:
#line 3937 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 10579 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 826:
#line 3940 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 10585 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 827:
#line 3941 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 10591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 828:
#line 3942 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 10597 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 829:
#line 3943 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 10603 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 830:
#line 3944 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 10609 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 831:
#line 3945 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 10615 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 832:
#line 3946 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 10621 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 833:
#line 3947 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 10627 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 834:
#line 3951 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 10635 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 835:
#line 3956 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 10641 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 836:
#line 3957 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 10647 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 837:
#line 3958 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 10653 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 838:
#line 3962 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 10661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 839:
#line 3967 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 10667 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 840:
#line 3968 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 10673 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 841:
#line 3969 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 10679 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 842:
#line 3970 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 10685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 851:
#line 3984 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 10693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 852:
#line 3989 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 10699 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 853:
#line 3990 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 10705 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 854:
#line 3994 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 10713 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 855:
#line 3999 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 10719 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 856:
#line 4000 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 10725 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 857:
#line 4001 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_TYPE; }
#line 10731 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 858:
#line 4002 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 10737 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 859:
#line 4006 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 10745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 860:
#line 4012 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 10753 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 861:
#line 4018 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 10761 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 862:
#line 4023 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 10767 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 863:
#line 4027 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 10775 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 864:
#line 4032 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 10781 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 865:
#line 4033 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 10787 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 866:
#line 4034 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_TAG; }
#line 10793 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 867:
#line 4036 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 10801 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 868:
#line 4042 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 10809 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 869:
#line 4047 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 10815 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 870:
#line 4048 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 10821 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 871:
#line 4049 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 10827 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 872:
#line 4050 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 10833 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 873:
#line 4051 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 10839 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 874:
#line 4052 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_ID; }
#line 10845 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 875:
#line 4056 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 10853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 876:
#line 4061 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 10859 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 877:
#line 4062 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 10865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 878:
#line 4066 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 10873 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 879:
#line 4071 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 10879 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 880:
#line 4072 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 10885 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 881:
#line 4073 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_TYPE; }
#line 10891 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 882:
#line 4074 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 10897 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 883:
#line 4075 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 10903 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 884:
#line 4079 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 10919 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 885:
#line 4092 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 10925 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 886:
#line 4093 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 10931 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 887:
#line 4094 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 10937 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 888:
#line 4095 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 10943 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 889:
#line 4096 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_MH; }
#line 10949 "parser_bison.c" /* yacc.c:1646  */
    break;


#line 10953 "parser_bison.c" /* yacc.c:1646  */
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
#line 4099 "parser_bison.y" /* yacc.c:1906  */

