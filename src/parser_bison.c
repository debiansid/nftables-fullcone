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
    LOOKUP = 280,
    INCLUDE = 281,
    DEFINE = 282,
    REDEFINE = 283,
    UNDEFINE = 284,
    FIB = 285,
    HOOK = 286,
    DEVICE = 287,
    DEVICES = 288,
    TABLE = 289,
    TABLES = 290,
    CHAIN = 291,
    CHAINS = 292,
    RULE = 293,
    RULES = 294,
    SETS = 295,
    SET = 296,
    ELEMENT = 297,
    MAP = 298,
    MAPS = 299,
    FLOWTABLE = 300,
    HANDLE = 301,
    RULESET = 302,
    TRACE = 303,
    INET = 304,
    NETDEV = 305,
    ADD = 306,
    UPDATE = 307,
    REPLACE = 308,
    CREATE = 309,
    INSERT = 310,
    DELETE = 311,
    GET = 312,
    LIST = 313,
    RESET = 314,
    FLUSH = 315,
    RENAME = 316,
    DESCRIBE = 317,
    IMPORT = 318,
    EXPORT = 319,
    MONITOR = 320,
    ALL = 321,
    ACCEPT = 322,
    DROP = 323,
    CONTINUE = 324,
    JUMP = 325,
    GOTO = 326,
    RETURN = 327,
    TO = 328,
    CONSTANT = 329,
    INTERVAL = 330,
    AUTOMERGE = 331,
    TIMEOUT = 332,
    GC_INTERVAL = 333,
    ELEMENTS = 334,
    POLICY = 335,
    MEMORY = 336,
    PERFORMANCE = 337,
    SIZE = 338,
    FLOW = 339,
    OFFLOAD = 340,
    METER = 341,
    METERS = 342,
    FLOWTABLES = 343,
    NUM = 344,
    STRING = 345,
    QUOTED_STRING = 346,
    ASTERISK_STRING = 347,
    LL_HDR = 348,
    NETWORK_HDR = 349,
    TRANSPORT_HDR = 350,
    BRIDGE = 351,
    ETHER = 352,
    SADDR = 353,
    DADDR = 354,
    TYPE = 355,
    VLAN = 356,
    ID = 357,
    CFI = 358,
    PCP = 359,
    ARP = 360,
    HTYPE = 361,
    PTYPE = 362,
    HLEN = 363,
    PLEN = 364,
    OPERATION = 365,
    IP = 366,
    HDRVERSION = 367,
    HDRLENGTH = 368,
    DSCP = 369,
    ECN = 370,
    LENGTH = 371,
    FRAG_OFF = 372,
    TTL = 373,
    PROTOCOL = 374,
    CHECKSUM = 375,
    ICMP = 376,
    CODE = 377,
    SEQUENCE = 378,
    GATEWAY = 379,
    MTU = 380,
    OPTIONS = 381,
    IP6 = 382,
    PRIORITY = 383,
    FLOWLABEL = 384,
    NEXTHDR = 385,
    HOPLIMIT = 386,
    ICMP6 = 387,
    PPTR = 388,
    MAXDELAY = 389,
    AH = 390,
    RESERVED = 391,
    SPI = 392,
    ESP = 393,
    COMP = 394,
    FLAGS = 395,
    CPI = 396,
    UDP = 397,
    SPORT = 398,
    DPORT = 399,
    UDPLITE = 400,
    CSUMCOV = 401,
    TCP = 402,
    ACKSEQ = 403,
    DOFF = 404,
    WINDOW = 405,
    URGPTR = 406,
    OPTION = 407,
    ECHO = 408,
    EOL = 409,
    MAXSEG = 410,
    NOOP = 411,
    SACK = 412,
    SACK0 = 413,
    SACK1 = 414,
    SACK2 = 415,
    SACK3 = 416,
    SACK_PERMITTED = 417,
    TIMESTAMP = 418,
    KIND = 419,
    COUNT = 420,
    LEFT = 421,
    RIGHT = 422,
    TSVAL = 423,
    TSECR = 424,
    DCCP = 425,
    SCTP = 426,
    VTAG = 427,
    RT = 428,
    RT0 = 429,
    RT2 = 430,
    RT4 = 431,
    SEG_LEFT = 432,
    ADDR = 433,
    LAST_ENT = 434,
    TAG = 435,
    SID = 436,
    HBH = 437,
    FRAG = 438,
    RESERVED2 = 439,
    MORE_FRAGMENTS = 440,
    DST = 441,
    MH = 442,
    META = 443,
    MARK = 444,
    IIF = 445,
    IIFNAME = 446,
    IIFTYPE = 447,
    OIF = 448,
    OIFNAME = 449,
    OIFTYPE = 450,
    SKUID = 451,
    SKGID = 452,
    NFTRACE = 453,
    RTCLASSID = 454,
    IBRIPORT = 455,
    OBRIPORT = 456,
    IBRIDGENAME = 457,
    OBRIDGENAME = 458,
    PKTTYPE = 459,
    CPU = 460,
    IIFGROUP = 461,
    OIFGROUP = 462,
    CGROUP = 463,
    CLASSID = 464,
    NEXTHOP = 465,
    CT = 466,
    L3PROTOCOL = 467,
    PROTO_SRC = 468,
    PROTO_DST = 469,
    ZONE = 470,
    DIRECTION = 471,
    EVENT = 472,
    EXPIRATION = 473,
    HELPER = 474,
    LABEL = 475,
    STATE = 476,
    STATUS = 477,
    ORIGINAL = 478,
    REPLY = 479,
    COUNTER = 480,
    NAME = 481,
    PACKETS = 482,
    BYTES = 483,
    AVGPKT = 484,
    COUNTERS = 485,
    QUOTAS = 486,
    LIMITS = 487,
    HELPERS = 488,
    LOG = 489,
    PREFIX = 490,
    GROUP = 491,
    SNAPLEN = 492,
    QUEUE_THRESHOLD = 493,
    LEVEL = 494,
    LIMIT = 495,
    RATE = 496,
    BURST = 497,
    OVER = 498,
    UNTIL = 499,
    QUOTA = 500,
    USED = 501,
    NANOSECOND = 502,
    MICROSECOND = 503,
    MILLISECOND = 504,
    SECOND = 505,
    MINUTE = 506,
    HOUR = 507,
    DAY = 508,
    WEEK = 509,
    _REJECT = 510,
    WITH = 511,
    ICMPX = 512,
    SNAT = 513,
    DNAT = 514,
    MASQUERADE = 515,
    REDIRECT = 516,
    RANDOM = 517,
    FULLY_RANDOM = 518,
    PERSISTENT = 519,
    QUEUE = 520,
    QUEUENUM = 521,
    BYPASS = 522,
    FANOUT = 523,
    DUP = 524,
    FWD = 525,
    NUMGEN = 526,
    INC = 527,
    MOD = 528,
    OFFSET = 529,
    JHASH = 530,
    SYMHASH = 531,
    SEED = 532,
    POSITION = 533,
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
#define LOOKUP 280
#define INCLUDE 281
#define DEFINE 282
#define REDEFINE 283
#define UNDEFINE 284
#define FIB 285
#define HOOK 286
#define DEVICE 287
#define DEVICES 288
#define TABLE 289
#define TABLES 290
#define CHAIN 291
#define CHAINS 292
#define RULE 293
#define RULES 294
#define SETS 295
#define SET 296
#define ELEMENT 297
#define MAP 298
#define MAPS 299
#define FLOWTABLE 300
#define HANDLE 301
#define RULESET 302
#define TRACE 303
#define INET 304
#define NETDEV 305
#define ADD 306
#define UPDATE 307
#define REPLACE 308
#define CREATE 309
#define INSERT 310
#define DELETE 311
#define GET 312
#define LIST 313
#define RESET 314
#define FLUSH 315
#define RENAME 316
#define DESCRIBE 317
#define IMPORT 318
#define EXPORT 319
#define MONITOR 320
#define ALL 321
#define ACCEPT 322
#define DROP 323
#define CONTINUE 324
#define JUMP 325
#define GOTO 326
#define RETURN 327
#define TO 328
#define CONSTANT 329
#define INTERVAL 330
#define AUTOMERGE 331
#define TIMEOUT 332
#define GC_INTERVAL 333
#define ELEMENTS 334
#define POLICY 335
#define MEMORY 336
#define PERFORMANCE 337
#define SIZE 338
#define FLOW 339
#define OFFLOAD 340
#define METER 341
#define METERS 342
#define FLOWTABLES 343
#define NUM 344
#define STRING 345
#define QUOTED_STRING 346
#define ASTERISK_STRING 347
#define LL_HDR 348
#define NETWORK_HDR 349
#define TRANSPORT_HDR 350
#define BRIDGE 351
#define ETHER 352
#define SADDR 353
#define DADDR 354
#define TYPE 355
#define VLAN 356
#define ID 357
#define CFI 358
#define PCP 359
#define ARP 360
#define HTYPE 361
#define PTYPE 362
#define HLEN 363
#define PLEN 364
#define OPERATION 365
#define IP 366
#define HDRVERSION 367
#define HDRLENGTH 368
#define DSCP 369
#define ECN 370
#define LENGTH 371
#define FRAG_OFF 372
#define TTL 373
#define PROTOCOL 374
#define CHECKSUM 375
#define ICMP 376
#define CODE 377
#define SEQUENCE 378
#define GATEWAY 379
#define MTU 380
#define OPTIONS 381
#define IP6 382
#define PRIORITY 383
#define FLOWLABEL 384
#define NEXTHDR 385
#define HOPLIMIT 386
#define ICMP6 387
#define PPTR 388
#define MAXDELAY 389
#define AH 390
#define RESERVED 391
#define SPI 392
#define ESP 393
#define COMP 394
#define FLAGS 395
#define CPI 396
#define UDP 397
#define SPORT 398
#define DPORT 399
#define UDPLITE 400
#define CSUMCOV 401
#define TCP 402
#define ACKSEQ 403
#define DOFF 404
#define WINDOW 405
#define URGPTR 406
#define OPTION 407
#define ECHO 408
#define EOL 409
#define MAXSEG 410
#define NOOP 411
#define SACK 412
#define SACK0 413
#define SACK1 414
#define SACK2 415
#define SACK3 416
#define SACK_PERMITTED 417
#define TIMESTAMP 418
#define KIND 419
#define COUNT 420
#define LEFT 421
#define RIGHT 422
#define TSVAL 423
#define TSECR 424
#define DCCP 425
#define SCTP 426
#define VTAG 427
#define RT 428
#define RT0 429
#define RT2 430
#define RT4 431
#define SEG_LEFT 432
#define ADDR 433
#define LAST_ENT 434
#define TAG 435
#define SID 436
#define HBH 437
#define FRAG 438
#define RESERVED2 439
#define MORE_FRAGMENTS 440
#define DST 441
#define MH 442
#define META 443
#define MARK 444
#define IIF 445
#define IIFNAME 446
#define IIFTYPE 447
#define OIF 448
#define OIFNAME 449
#define OIFTYPE 450
#define SKUID 451
#define SKGID 452
#define NFTRACE 453
#define RTCLASSID 454
#define IBRIPORT 455
#define OBRIPORT 456
#define IBRIDGENAME 457
#define OBRIDGENAME 458
#define PKTTYPE 459
#define CPU 460
#define IIFGROUP 461
#define OIFGROUP 462
#define CGROUP 463
#define CLASSID 464
#define NEXTHOP 465
#define CT 466
#define L3PROTOCOL 467
#define PROTO_SRC 468
#define PROTO_DST 469
#define ZONE 470
#define DIRECTION 471
#define EVENT 472
#define EXPIRATION 473
#define HELPER 474
#define LABEL 475
#define STATE 476
#define STATUS 477
#define ORIGINAL 478
#define REPLY 479
#define COUNTER 480
#define NAME 481
#define PACKETS 482
#define BYTES 483
#define AVGPKT 484
#define COUNTERS 485
#define QUOTAS 486
#define LIMITS 487
#define HELPERS 488
#define LOG 489
#define PREFIX 490
#define GROUP 491
#define SNAPLEN 492
#define QUEUE_THRESHOLD 493
#define LEVEL 494
#define LIMIT 495
#define RATE 496
#define BURST 497
#define OVER 498
#define UNTIL 499
#define QUOTA 500
#define USED 501
#define NANOSECOND 502
#define MICROSECOND 503
#define MILLISECOND 504
#define SECOND 505
#define MINUTE 506
#define HOUR 507
#define DAY 508
#define WEEK 509
#define _REJECT 510
#define WITH 511
#define ICMPX 512
#define SNAT 513
#define DNAT 514
#define MASQUERADE 515
#define REDIRECT 516
#define RANDOM 517
#define FULLY_RANDOM 518
#define PERSISTENT 519
#define QUEUE 520
#define QUEUENUM 521
#define BYPASS 522
#define FANOUT 523
#define DUP 524
#define FWD 525
#define NUMGEN 526
#define INC 527
#define MOD 528
#define OFFSET 529
#define JHASH 530
#define SYMHASH 531
#define SEED 532
#define POSITION 533
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
#define YYLAST   4866

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  296
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  290
/* YYNRULES -- Number of rules.  */
#define YYNRULES  885
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1388

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
    1839,  1840,  1841,  1844,  1852,  1861,  1868,  1876,  1883,  1890,
    1898,  1906,  1913,  1920,  1927,  1935,  1942,  1950,  1958,  1962,
    1969,  1976,  1988,  1992,  1999,  2003,  2009,  2021,  2027,  2034,
    2035,  2036,  2037,  2038,  2039,  2040,  2041,  2042,  2043,  2044,
    2045,  2046,  2047,  2048,  2049,  2050,  2051,  2052,  2055,  2059,
    2065,  2071,  2076,  2085,  2090,  2095,  2098,  2104,  2105,  2107,
    2111,  2119,  2123,  2126,  2130,  2136,  2137,  2140,  2146,  2150,
    2153,  2158,  2163,  2168,  2173,  2178,  2184,  2212,  2216,  2220,
    2224,  2228,  2234,  2238,  2241,  2245,  2251,  2260,  2279,  2287,
    2288,  2289,  2292,  2293,  2296,  2297,  2312,  2328,  2336,  2337,
    2338,  2341,  2342,  2343,  2344,  2359,  2360,  2361,  2362,  2363,
    2366,  2369,  2376,  2380,  2391,  2402,  2412,  2418,  2421,  2422,
    2425,  2426,  2427,  2428,  2429,  2430,  2431,  2432,  2433,  2434,
    2437,  2438,  2442,  2448,  2449,  2455,  2456,  2462,  2463,  2469,
    2472,  2473,  2492,  2493,  2496,  2500,  2503,  2509,  2515,  2526,
    2527,  2528,  2531,  2532,  2533,  2536,  2540,  2544,  2549,  2554,
    2558,  2562,  2568,  2569,  2572,  2575,  2579,  2584,  2590,  2591,
    2594,  2597,  2601,  2605,  2609,  2614,  2621,  2626,  2634,  2641,
    2642,  2648,  2649,  2650,  2653,  2654,  2657,  2663,  2667,  2670,
    2675,  2681,  2682,  2688,  2689,  2692,  2693,  2696,  2702,  2709,
    2718,  2719,  2722,  2731,  2738,  2741,  2747,  2751,  2754,  2760,
    2770,  2776,  2794,  2795,  2802,  2811,  2822,  2823,  2824,  2825,
    2826,  2827,  2828,  2829,  2830,  2831,  2832,  2833,  2836,  2859,
    2860,  2861,  2864,  2865,  2866,  2867,  2868,  2871,  2875,  2878,
    2879,  2883,  2889,  2890,  2896,  2897,  2903,  2904,  2910,  2913,
    2914,  2933,  2939,  2945,  2956,  2957,  2958,  2961,  2967,  2968,
    2969,  2972,  2979,  2984,  2989,  2992,  2996,  3000,  3006,  3007,
    3014,  3020,  3021,  3024,  3030,  3034,  3037,  3041,  3047,  3048,
    3051,  3052,  3055,  3056,  3059,  3070,  3078,  3099,  3107,  3110,
    3111,  3114,  3129,  3136,  3141,  3152,  3174,  3182,  3186,  3190,
    3194,  3200,  3206,  3214,  3215,  3216,  3219,  3220,  3224,  3230,
    3231,  3237,  3238,  3244,  3245,  3251,  3254,  3255,  3274,  3275,
    3278,  3286,  3287,  3288,  3289,  3290,  3291,  3292,  3293,  3294,
    3295,  3296,  3297,  3300,  3301,  3302,  3303,  3304,  3311,  3318,
    3325,  3332,  3339,  3346,  3353,  3360,  3367,  3374,  3383,  3384,
    3385,  3386,  3387,  3388,  3391,  3395,  3399,  3403,  3407,  3411,
    3417,  3421,  3425,  3440,  3441,  3444,  3445,  3446,  3447,  3450,
    3451,  3452,  3453,  3454,  3455,  3456,  3457,  3458,  3459,  3460,
    3461,  3462,  3463,  3464,  3465,  3466,  3467,  3468,  3469,  3472,
    3476,  3480,  3494,  3498,  3504,  3505,  3508,  3509,  3512,  3518,
    3523,  3528,  3534,  3535,  3538,  3542,  3562,  3563,  3564,  3567,
    3571,  3575,  3581,  3582,  3585,  3586,  3587,  3588,  3589,  3590,
    3591,  3592,  3593,  3594,  3595,  3596,  3597,  3598,  3599,  3602,
    3603,  3604,  3605,  3606,  3607,  3608,  3611,  3612,  3615,  3616,
    3617,  3618,  3621,  3622,  3625,  3631,  3639,  3652,  3658,  3667,
    3668,  3669,  3670,  3671,  3672,  3673,  3674,  3675,  3676,  3677,
    3678,  3679,  3680,  3681,  3682,  3685,  3694,  3695,  3696,  3699,
    3705,  3706,  3707,  3710,  3716,  3717,  3718,  3719,  3722,  3728,
    3729,  3730,  3731,  3732,  3735,  3741,  3742,  3743,  3744,  3745,
    3746,  3747,  3748,  3749,  3750,  3751,  3752,  3755,  3761,  3762,
    3763,  3764,  3765,  3766,  3767,  3770,  3776,  3777,  3778,  3779,
    3780,  3781,  3782,  3783,  3784,  3786,  3792,  3793,  3794,  3795,
    3796,  3797,  3798,  3799,  3802,  3808,  3809,  3810,  3811,  3812,
    3815,  3821,  3822,  3825,  3831,  3832,  3833,  3836,  3842,  3843,
    3844,  3845,  3848,  3854,  3855,  3856,  3857,  3860,  3864,  3868,
    3875,  3876,  3877,  3878,  3879,  3880,  3881,  3882,  3883,  3884,
    3887,  3888,  3889,  3890,  3891,  3892,  3893,  3894,  3895,  3896,
    3897,  3898,  3901,  3902,  3903,  3904,  3905,  3906,  3907,  3908,
    3911,  3917,  3918,  3919,  3922,  3928,  3929,  3930,  3931,  3934,
    3935,  3936,  3937,  3938,  3939,  3940,  3941,  3944,  3950,  3951,
    3954,  3960,  3961,  3962,  3963,  3966,  3972,  3978,  3984,  3987,
    3993,  3994,  3995,  3996,  4002,  4008,  4009,  4010,  4011,  4012,
    4013,  4016,  4022,  4023,  4026,  4032,  4033,  4034,  4035,  4036,
    4039,  4053,  4054,  4055,  4056,  4057
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
  "\"lookup\"", "\"include\"", "\"define\"", "\"redefine\"",
  "\"undefine\"", "\"fib\"", "\"hook\"", "\"device\"", "\"devices\"",
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
  "\"seed\"", "\"position\"", "\"comment\"", "\"xml\"", "\"json\"",
  "\"vm\"", "\"notrack\"", "\"exists\"", "\"missing\"", "\"exthdr\"",
  "'='", "'{'", "'}'", "'|'", "'$'", "'('", "')'", "'['", "']'", "$accept",
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
  "limit_block", "type_identifier", "hook_spec", "prio_spec", "dev_spec",
  "policy_spec", "chain_policy", "identifier", "string", "time_spec",
  "family_spec", "family_spec_explicit", "table_spec", "tableid_spec",
  "chain_spec", "chainid_spec", "chain_identifier", "set_spec",
  "setid_spec", "set_identifier", "flowtable_spec", "flowtable_identifier",
  "obj_spec", "objid_spec", "obj_identifier", "handle_spec",
  "position_spec", "rule_position", "ruleid_spec", "comment_spec",
  "ruleset_spec", "rule", "rule_alloc", "stmt_list", "stmt",
  "verdict_stmt", "verdict_map_stmt", "verdict_map_expr",
  "verdict_map_list_expr", "verdict_map_list_member_expr", "counter_stmt",
  "counter_stmt_alloc", "counter_args", "counter_arg", "log_stmt",
  "log_stmt_alloc", "log_args", "log_arg", "level_type", "log_flags",
  "log_flags_tcp", "log_flag_tcp", "limit_stmt", "quota_mode",
  "quota_unit", "quota_used", "quota_stmt", "limit_mode", "limit_burst",
  "time_unit", "reject_stmt", "reject_stmt_alloc", "reject_opts",
  "nat_stmt", "nat_stmt_alloc", "primary_stmt_expr", "shift_stmt_expr",
  "and_stmt_expr", "exclusive_or_stmt_expr", "inclusive_or_stmt_expr",
  "basic_stmt_expr", "concat_stmt_expr", "map_stmt_expr_set",
  "map_stmt_expr", "prefix_stmt_expr", "range_stmt_expr",
  "wildcard_stmt_expr", "multiton_stmt_expr", "stmt_expr", "nat_stmt_args",
  "masq_stmt", "masq_stmt_alloc", "masq_stmt_args", "redir_stmt",
  "redir_stmt_alloc", "redir_stmt_arg", "dup_stmt", "fwd_stmt",
  "nf_nat_flags", "nf_nat_flag", "queue_stmt", "queue_stmt_alloc",
  "queue_stmt_args", "queue_stmt_arg", "queue_stmt_flags",
  "queue_stmt_flag", "set_elem_expr_stmt", "set_elem_expr_stmt_alloc",
  "set_stmt", "set_stmt_op", "map_stmt", "meter_stmt",
  "flow_stmt_legacy_alloc", "flow_stmt_opts", "flow_stmt_opt",
  "meter_stmt_alloc", "match_stmt", "variable_expr", "symbol_expr",
  "integer_expr", "primary_expr", "fib_expr", "fib_result", "fib_flag",
  "fib_tuple", "shift_expr", "and_expr", "exclusive_or_expr",
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

#define YYPACT_NINF -1099

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1099)))

#define YYTABLE_NINF -694

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1099,  4621, -1099,   388, -1099, -1099,   151,   160,   160,   160,
     505,   505,   505,   505,   505,   505,   505, -1099, -1099,  3624,
     246,   377,   288,   740,   272,  2462,   454,   659,   305,  3948,
      97,   107,   331, -1099, -1099, -1099, -1099,   206,   505,   505,
     505, -1099, -1099, -1099,   380, -1099,   160, -1099,   160,   165,
    3620, -1099,   388, -1099,   175,   192,   388,   211,   215,  3620,
     160, -1099,   200, -1099,   160, -1099, -1099,   505, -1099,   505,
     505,   505,   505,   505,   505,   310,   505,   505,   505, -1099,
     505, -1099,   505,   505,   505,   505,   505,   505,   505,   341,
     505,   505,   505, -1099,   505, -1099,   505,   505,   505,   505,
     213,   505,   505,   505,   505,   162,   505,   505,   505,    35,
     505,   399,   587,   605,   505,   505, -1099,   505,  1359,  1495,
     505, -1099,   505,   505,   505,   505,   505,   544,   505, -1099,
     505, -1099,   387,   416, -1099, -1099, -1099, -1099,   613,   586,
     702,  1664,   726,  1509,  1393,   404,   152,   263,   136,   469,
    1586,   143,   262,   895,   402,   405,   276,   185,   468,   243,
     432,  1782, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099,  2533,   129,  3825,   299,   462,   160,  3948, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,   512,
   -1099, -1099,   309, -1099, -1099,   512, -1099, -1099, -1099, -1099,
    1059,   505,   160,   360,   366,   209, -1099, -1099, -1099, -1099,
     514, -1099,   498, -1099, -1099, -1099, -1099, -1099,   160,   160,
   -1099,   526,   160,  2075,  2533,   415, -1099,  -127,   122, -1099,
   -1099, -1099, -1099, -1099, -1099,   573,   578, -1099,   653, -1099,
     391,  3620, -1099, -1099, -1099, -1099,   392, -1099,   286, -1099,
   -1099, -1099,   421, -1099,  2594, -1099,   -24, -1099,    67, -1099,
   -1099, -1099,   577, -1099,   119, -1099, -1099,   657, -1099, -1099,
   -1099,   688,   679,   697,   441, -1099,   319, -1099,  3021, -1099,
   -1099, -1099,   701, -1099, -1099, -1099,   703, -1099,  3360,  3360,
   -1099,   459,   478, -1099, -1099,   481, -1099, -1099, -1099,   487,
   -1099,   508,   704,  3620,   211,   215, -1099,   200, -1099, -1099,
     505,   360,   366,   209,  3620,    61, -1099, -1099,   113, -1099,
   -1099, -1099,   132, -1099, -1099,   200, -1099, -1099, -1099,   505,
     137, -1099, -1099, -1099, -1099, -1099, -1099,   200, -1099, -1099,
   -1099, -1099, -1099,   505, -1099, -1099, -1099, -1099, -1099,   505,
     505, -1099, -1099, -1099,   718,   505, -1099,   505, -1099,   505,
   -1099,   505, -1099, -1099, -1099, -1099,   505, -1099,   505, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099,   505, -1099,   160, -1099,
   -1099, -1099, -1099,   792, -1099, -1099, -1099, -1099, -1099,   798,
      -9, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,  1282,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,    25,
   -1099, -1099,   560, -1099, -1099, -1099, -1099, -1099, -1099,   564,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,  1307, -1099,
   -1099, -1099, -1099,   556,   130,   625,   782, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099,   607, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099,   512, -1099, -1099,   813, -1099,
   -1099,   431, -1099, -1099, -1099, -1099,   817, -1099, -1099, -1099,
    3948, -1099, -1099,   886,   622,   870,   872,  1307,   874,  3235,
    3235,   431,  3235,   827,  3235,  3825, -1099,  3360,    49, -1099,
     770, -1099, -1099,   829,   834,   392, -1099,   362,   770,   836,
     848,   856,   770,   286, -1099,   -21, -1099,  3235, -1099, -1099,
    2719,   613,   586,   702,  1664, -1099,  1509,    14, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099,   692,   933,   934,   663,
     378,   221, -1099, -1099, -1099, -1099, -1099,   951,   606,   950,
   -1099, -1099, -1099,   952, -1099, -1099, -1099, -1099, -1099,   954,
     956, -1099,   953, -1099, -1099, -1099, -1099,   960, -1099,  2870,
   -1099,   960,  3235, -1099, -1099,   577, -1099,   962, -1099,   160,
     686,   160,    18, -1099,  3948,  3948,  3948,  3948,  3948,  3948,
      11,  3360, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099,   968, -1099,   724,   967,   959,   706,   572,   990,
   -1099, -1099, -1099,  3084,  3235,  3235,   388,   968, -1099,   388,
   -1099, -1099, -1099, -1099, -1099,   911, -1099, -1099,   713,   714,
     722, -1099,   723,   725, -1099, -1099, -1099, -1099, -1099,   923,
     925,   927, -1099, -1099,   928, -1099, -1099, -1099, -1099,   505,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,   937,   416,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099,   764, -1099,   938,   939,
   -1099, -1099, -1099, -1099, -1099, -1099,   681, -1099, -1099,   946,
     955,   765, -1099, -1099, -1099,   758,   823, -1099, -1099,   963,
       0,   119,   -31,  1045,   770,  3948,  3235,  3235,  1013,  3235,
   -1099, -1099,   971, -1099,     0,  1024, -1099, -1099,   653,   815,
     -31, -1099,   516,   990,   653, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099,   935,   385, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099,   966,   969,  1009,   970, -1099,  3235,  1066,
    4106,  4376,  4106,  4106,  4106,   986,  4106,  4106,    80,  3235,
     960,  1199,  1199,  3235,   606,  3235,   606, -1099, -1099,   598,
    3948, -1099,  3948, -1099, -1099, -1099,   688,   679,   697, -1099,
     160,   653, -1099, -1099,  4376,  4376,  4376,  4376,  4376,  4376,
    4376,   987,  4376,  4376,  3360, -1099, -1099, -1099, -1099, -1099,
    1388,  1823,   796,   547,   306, -1099, -1099, -1099, -1099, -1099,
   -1099,   789, -1099, -1099, -1099, -1099, -1099, -1099,  1071, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,   793,
     794, -1099, -1099, -1099,   765,   242,   995, -1099, -1099,   998,
      77, -1099, -1099,   844, -1099,  1002, -1099,   -31, -1099, -1099,
    1045,  3620,   -31, -1099, -1099,  3235, -1099,   135,   844,  3235,
   -1099,  4304, -1099,   -31,  3360, -1099, -1099, -1099, -1099,  1086,
   -1099,  1005,  1011, -1099,  1012, -1099,  3235, -1099, -1099, -1099,
   -1099,   692,   933,   934, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099,   606, -1099,   606,   960, -1099,
      27,  3620, -1099,  3455,    63, -1099, -1099, -1099, -1099,   724,
     967,   959, -1099, -1099, -1099, -1099,   818,   160,   160,   160,
     160,  1019,   891,   160,   160,   160, -1099, -1099, -1099,   388,
     810,  1023, -1099, -1099, -1099,   388,   388,   388, -1099,  1002,
    1002,   832,   822,  1031,    87,   522, -1099, -1099, -1099,   388,
    1002,   835,    87,   522, -1099, -1099, -1099,   388,  1035,   839,
   -1099, -1099, -1099,  1714,  2116,  1003,   893,   438, -1099,  1032,
   -1099, -1099, -1099,  1038, -1099, -1099,    53, -1099,   632,   887,
    1041, -1099, -1099, -1099, -1099,   842,   -31, -1099,   632,   887,
   -1099, -1099,   653, -1099,   990, -1099,   385, -1099, -1099, -1099,
   -1099,   960,   960,  3948, -1099,   843,  1129,   653, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,   160, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099,  1104, -1099, -1099,
   -1099,   388,   388,   200, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099,   464, -1099, -1099, -1099, -1099,   797,
   -1099, -1099,   388,   200,   551,   797, -1099,  1020,   849, -1099,
   -1099, -1099, -1099, -1099,   457, -1099,   765,  1048,   505,   388,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,   887,  1051,
   -1099,     0, -1099,   887, -1099, -1099, -1099,   852, -1099,   821,
    3455, -1099,   859,   871,   876,   877, -1099,   881,   882,   883,
    1068, -1099, -1099, -1099,    87, -1099,   522, -1099, -1099, -1099,
     528, -1099,    71,  1082,   388,   388, -1099,  1054,   388, -1099,
   -1099,   -22, -1099, -1099, -1099,   653, -1099, -1099, -1099, -1099,
     889, -1099, -1099, -1099,  1147, -1099, -1099,   388,   388,   388,
     464,  1094, -1099,   388, -1099,    66, -1099, -1099, -1099,   -10,
   -1099, -1099, -1099, -1099, -1099,  2389,  1162,  1608,   538, -1099,
     187,  1036,    57,  1095,  1056, -1099, -1099, -1099, -1099, -1099,
   -1099,    85, -1099, -1099, -1099,   388,   388,   388,   388,   388,
    1174,   388, -1099, -1099, -1099,   388, -1099, -1099, -1099,   388,
   -1099, -1099, -1099, -1099,    71, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099,   388, -1099, -1099, -1099, -1099, -1099
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
     245,    14,    13,     3,     0,    17,     0,   246,     0,   268,
       0,    12,     0,   240,     0,     0,     0,    32,    34,     0,
       0,   162,     0,   180,     0,   196,    18,   245,    19,   245,
     245,   245,   245,   245,   245,     0,   245,   245,   245,    20,
     245,    21,   245,   245,   245,   245,   245,   245,   245,     0,
     245,   245,   245,    22,   245,    23,   245,   272,   245,   272,
     272,   245,   245,   272,   272,     0,   245,   272,   272,     0,
     245,   272,   272,   272,   245,   245,    24,   245,   272,   272,
     245,    25,   245,   245,   245,   245,   272,     0,   245,    26,
     245,    27,     0,     0,   465,   241,   242,   243,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   619,   620,   621,   622,   623,   624,   625,   626,
     627,   628,   629,   630,   631,   632,   633,   634,   635,   636,
     637,   638,     0,     0,     0,     0,     0,     0,     0,    31,
     463,   462,   466,   467,   140,   476,   471,   611,   474,   475,
     472,   473,   468,   699,   700,   701,   702,   703,   704,   705,
     706,   707,   708,   709,   710,   711,   712,   713,   714,   469,
     839,   840,   841,   842,   843,   844,   845,   846,   470,     0,
     137,   138,     0,    28,   121,     0,    29,   123,   126,    30,
     127,   245,     0,    42,     0,   341,    16,    15,   253,   255,
       0,   269,     0,   450,   451,   604,   605,   606,     0,     0,
     609,   455,     0,     0,     0,   309,   317,     0,   341,   361,
     368,   369,   414,   420,   436,     0,     0,   642,     7,    37,
     274,   276,   277,   279,   299,   282,   307,   285,   315,   286,
     287,   288,   362,   289,     0,   292,   413,   293,   419,   294,
     295,   290,   434,   296,     0,   297,   281,     0,   454,   280,
     489,   492,   494,   496,   498,   499,   508,   510,     0,   509,
     460,   298,   611,   284,   291,   283,   468,     8,     0,     0,
      11,     0,     0,    36,   258,     0,    40,   174,   173,     0,
     261,     0,     0,     0,    48,    50,   162,     0,   180,   196,
     245,    56,     0,   341,     0,     0,    62,    63,     0,    64,
      65,    66,     0,    67,    68,     0,    69,    71,   538,   245,
       0,    72,    73,    77,    78,    74,    75,     0,    80,   273,
      81,    82,    83,   245,    84,    86,   103,   102,    96,   245,
     272,   100,    99,   101,     0,   245,    89,   245,    87,   245,
      90,   245,    93,    95,    92,   108,   245,   106,   245,   109,
     111,   112,   113,   114,   115,   118,   245,   117,     0,   716,
     717,   718,   464,     0,   482,   483,   484,   485,   486,   488,
       0,   720,   721,   722,   719,   727,   724,   725,   726,   723,
     729,   730,   731,   732,   733,   728,   745,   746,   740,   735,
     736,   737,   738,   739,   741,   742,   743,   744,   734,   748,
     751,   750,   749,   752,   753,   754,   747,   763,   764,   756,
     757,   758,   760,   759,   761,   762,   755,   766,   771,   768,
     767,   772,   770,   769,   773,   765,   776,   779,   775,   777,
     778,   774,   782,   781,   780,   784,   785,   786,   783,   790,
     791,   788,   789,   787,   796,   793,   794,   795,   792,   808,
     802,   805,   806,   800,   801,   803,   804,   807,   809,     0,
     797,   833,   831,   832,   830,   838,   835,   836,   837,   834,
     853,   652,   852,   658,   653,   851,   854,   656,   657,     0,
     654,   850,     0,   855,   858,   857,   861,   860,   862,     0,
     859,   849,   848,   847,   870,   867,   865,   866,   868,   869,
     864,   873,   872,   871,   877,   876,   879,   875,   878,   874,
     612,   615,   616,   617,   618,   610,   613,   614,   672,   673,
     665,   666,   664,   674,   675,   691,   668,   677,   670,   671,
     676,   667,   669,   662,   663,   689,   688,   690,     0,   659,
     678,   647,   646,     0,   508,     0,     0,   882,   881,   883,
     884,   885,   880,   461,     0,   120,   139,   122,   128,   129,
     131,   130,   133,   134,   132,   135,   543,   263,     0,   535,
      43,   350,   546,    46,   339,   340,     0,   537,    44,   267,
       0,   607,   608,     0,     0,   612,   610,     0,   659,     0,
       0,   350,     0,     0,     0,     0,     6,     0,     0,   512,
       0,   275,   278,     0,     0,   308,   311,     0,     0,     0,
       0,     0,     0,   316,   318,     0,   360,     0,   398,   579,
       0,   571,   574,   575,   572,   578,   573,     0,   582,   580,
     581,   577,   576,   568,   569,   380,   383,   385,   387,   389,
     390,   395,   402,   399,   400,   401,   403,   405,   367,   370,
     371,   570,   372,   379,   373,   376,   377,   374,   375,     0,
     404,   378,     0,   431,   432,   433,   412,   417,   429,     0,
     418,   423,     0,   443,   444,   435,   437,   440,   441,     0,
       0,     0,     0,   456,     0,     0,     0,     0,     0,     0,
       0,     0,   598,   599,   600,   601,   602,   603,   503,   571,
     574,   575,   572,   592,   573,   593,   591,   590,   594,   588,
     589,   587,   595,   596,   597,   583,   584,   504,   505,   506,
     554,   555,   548,   547,   559,   561,   563,   565,   566,   553,
     585,   586,   556,     0,     0,     0,     0,   533,   532,     0,
     143,   156,   163,   181,   197,     0,   270,    47,     0,     0,
       0,    54,     0,     0,   543,    57,    60,    58,    61,     0,
       0,     0,    70,   543,     0,    79,    85,    98,    97,   245,
     104,    88,    91,    94,   107,   110,   116,   119,     0,     0,
     481,   479,   480,   478,   813,   820,   810,   812,   811,   815,
     816,   817,   818,   819,   814,   821,   799,   655,     0,     0,
     679,   680,   682,   681,   683,   684,     0,   660,   685,     0,
       0,   644,   477,   124,   136,     0,     0,   348,   349,     0,
       0,     0,   445,   447,     0,     0,     0,     0,   685,     0,
     310,   338,     0,   347,     0,   426,   428,   529,     7,     7,
     521,   523,   566,   528,     7,   511,   271,   313,   314,   312,
     331,   330,     0,     0,   329,   325,   320,   321,   322,   323,
     326,   324,   319,     0,     0,     0,     0,   409,     0,   406,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     411,     0,     0,     0,     0,     0,   421,   439,   438,     0,
       0,   458,     0,   457,   490,   491,   493,   495,   497,   500,
       0,     7,   300,   507,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   549,   640,   698,     9,    10,
       0,     0,     0,     0,     0,   266,   143,   156,   163,   181,
     197,     0,   254,   256,   259,    76,   264,   105,     0,   487,
     824,   823,   822,   825,   826,   827,   828,   829,   798,     0,
       0,   686,   687,   661,   644,   644,     0,   651,   219,     0,
       0,   343,   342,   344,   448,     0,   527,   446,   524,   643,
     520,     0,   518,   641,   639,     0,   696,     0,   344,     0,
     515,     0,   516,   522,   514,   513,   328,   334,   335,   327,
     333,     0,     0,   366,     0,   410,     0,   381,   370,   379,
     382,   384,   386,   388,   396,   397,   391,   394,   393,   392,
     407,   692,   693,   694,   695,   415,   430,   422,   424,   442,
       0,     0,   302,     0,     0,   303,   552,   557,   558,   560,
     562,   564,   551,   501,   502,   567,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    33,   145,   144,     0,
       0,     0,    35,   158,   157,     0,     0,     0,   171,     0,
       0,     0,     0,     0,     0,     0,    38,   165,   164,     0,
       0,     0,     0,     0,    39,   183,   182,     0,     0,     0,
      41,   199,   198,     0,     0,     0,     0,     0,   219,     0,
     856,   863,   648,     0,   650,   645,     0,   534,     0,   351,
       0,   536,   244,   526,   525,     0,   519,   697,     0,   351,
     346,   427,     7,   566,   530,   531,     0,   363,   364,   365,
     408,   416,   425,     0,   449,     0,     0,     7,   301,   550,
     257,   155,   260,   162,   180,   262,   196,   142,     0,   265,
     210,   210,   210,   146,   238,   239,   237,     0,   159,   160,
     161,     0,     0,     0,   195,   194,   192,   193,   227,   229,
     230,   228,   231,   208,     0,   207,   177,   178,   179,     0,
     176,   172,     0,     0,     0,     0,   191,     0,     0,    49,
      51,    52,    53,    55,     0,   715,   644,     0,     0,     0,
     221,   220,   222,   355,   356,   357,   358,   359,   351,     0,
     545,     0,   459,   351,   337,   517,   332,     0,   453,     0,
     305,   304,     0,     0,     0,     0,   210,     0,     0,     0,
       0,   168,   169,   170,     0,   166,     0,   167,   184,   190,
       0,   189,     0,     0,     0,     0,   649,     0,     0,    45,
     544,     0,   345,   336,   452,     7,   156,   163,   181,   197,
       0,   211,   223,   215,   236,   209,   175,     0,     0,     0,
       0,     0,   233,     0,   206,     0,   203,   201,    59,     0,
     542,   354,   352,   353,   306,     0,     0,     0,     0,   219,
       0,     0,     0,     0,     0,   186,   188,   187,   185,   234,
     200,     7,   202,   540,   539,     0,     0,     0,     0,     0,
       0,     0,   213,   212,   214,     0,   225,   224,   226,     0,
     217,   216,   218,   235,     0,   205,   204,   541,   147,   148,
     149,   150,     0,   151,   154,   152,   232,   153
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1099, -1099,    -1,  -851,     6, -1099, -1099,  1168, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099,   -17, -1099,   850, -1099,   210,  -339,  -952,
    -338,  -950,  -346,    64,   -91,  -337,  -947,  -954, -1099,  -340,
    -946, -1099, -1099,  -153,   -80, -1070, -1081, -1099, -1099, -1098,
   -1099, -1099, -1099,  -169, -1099, -1099, -1099,   173,  -503,  -826,
    1124,     5,  1472, -1099,   463, -1099, -1099,    62, -1099,   108,
     302, -1099,   168,   816, -1009, -1099, -1099,    94,  1125,   932,
     394,    15, -1099, -1099,  -260, -1099, -1099, -1099, -1099,    21,
   -1099, -1099, -1099,   549, -1099, -1099, -1099,   542, -1099, -1099,
   -1099,    40, -1099,   949,  -864,   180, -1099,   568, -1097,    52,
   -1099, -1099, -1099, -1099, -1099,  -500,   289,   291,   292, -1099,
     293, -1099, -1099, -1099, -1099, -1099, -1099, -1099,  -305, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,  -270,   283,
   -1099, -1099, -1099,   497, -1099,   284,  -910, -1099, -1099,   983,
   -1099, -1099, -1099, -1099,   494, -1099, -1099,   -52,   730,   -26,
     -16, -1099, -1099, -1099,   407,   501,   502,   503, -1099,  -172,
    -180, -1099, -1099, -1099,  -637, -1099,  -159,   -57, -1099,   350,
     303, -1099, -1019, -1099,  -833,  -949, -1099, -1099,   930,   -84,
     906,   -82,   908,  1154, -1099, -1099,  -406,   -77,   913, -1099,
     948,  -301,   300,   307,   311, -1099,  -292,  -642, -1099,  -306,
     535,  -699, -1099, -1000,    10,  1015, -1099,   -32, -1099,  -927,
   -1099,    16,    42,  -471,    69,   729,    86,  1017,  1018, -1099,
   -1099,  -468,    -7, -1099, -1099, -1099,    93, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099,
   -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099, -1099
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1113,   657,  1114,    43,    44,    45,    68,    79,
      81,    93,    95,   116,   121,   129,   131,   233,   236,   239,
     240,   625,   873,   234,   189,   331,  1109,   980,   332,   981,
     335,   982,   336,  1229,  1230,   339,   983,  1129,  1216,   341,
     984,  1294,  1325,  1326,  1223,  1224,  1277,  1340,  1342,  1156,
    1341,  1225,  1115,  1323,  1344,  1116,  1206,  1199,   190,  1163,
      46,    47,    60,   357,    49,   360,  1191,    61,   364,  1193,
      65,  1196,   243,   372,  1200,   806,   251,    50,   343,  1026,
     380,  1117,   280,   281,   282,   283,   284,   962,  1084,  1085,
     285,   286,   665,   666,   287,   288,   673,   674,   921,   915,
    1049,  1050,   289,   636,  1023,  1161,   290,   879,  1260,  1258,
     291,   292,   676,   293,   294,   695,   696,   697,   698,   699,
     700,   701,  1067,   702,   703,   704,   705,   706,   707,   708,
     295,   296,   726,   297,   298,   730,   299,   300,   727,   728,
     301,   302,   735,   736,   737,   738,   881,   882,   303,   304,
     305,   306,   307,   742,   743,   308,   309,   191,   192,   710,
     310,   195,   843,   429,   430,   311,   312,   313,   314,   315,
     316,   777,   778,   779,   780,   317,   318,   319,   658,   659,
    1031,  1032,   899,   900,  1027,  1028,   901,  1172,   796,   629,
     630,   637,   638,   369,  1355,  1252,   875,   632,   633,   320,
     797,   798,   784,   785,   786,   787,   902,   789,   711,   712,
     713,   792,   793,   321,   714,   575,   576,   197,   323,  1017,
     603,   715,   716,   539,   717,   540,   718,   598,   599,   867,
    1013,   600,   719,   720,   324,   325,   721,   203,   423,   204,
     434,   205,   439,   206,   445,   207,   458,   208,   466,   209,
     476,   210,   485,   211,   491,   212,   494,   213,   498,   214,
     503,   215,   508,   216,   520,   856,  1008,   217,   524,   218,
     529,   219,   220,   553,   221,   541,   222,   543,   223,   545,
     224,   550,   225,   560,   226,   563,   227,   569,   228,   612
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,   811,    51,   193,   604,   338,   809,    42,   810,   813,
     337,   812,   790,   194,   237,   903,   614,   783,   322,   822,
     897,   662,   790,   790,   193,   605,   788,   322,   731,  1137,
    1038,   825,  1183,   193,   960,  1144,   788,   788,  1145,   196,
    1080,  1175,  1146,   247,  1147,   198,  1025,  1040,  1042,   722,
    1244,   327,   741,  1044,     3,   330,   904,     4,     3,     5,
     196,     4,  1234,     5,  1186,   279,   198,  1043,  1331,   196,
    1187,   199,  1264,  1351,   333,   198,    62,    63,  1164,     6,
       7,     8,     9,     6,     7,     8,     9,  1152,  1154,   656,
    1021,   840,   199,  1321,  1164,  1201,  1202,  1158,   200,   650,
     923,   199,   379,   739,   379,   379,    59,   819,   379,   379,
    1083,   924,   379,   379,   651,   201,   379,   379,   379,   200,
    1278,  1279,   202,   379,   379,   531,   925,   866,   200,   577,
     868,   379,  1353,   346,   347,   348,   201,  1354,   749,   533,
     729,   534,   739,   326,   229,   201,  -341,   363,   365,   366,
     533,    53,   326,  1247,   235,  1168,   377,   906,   193,   820,
    1322,  1300,   193,   385,   386,   916,  1303,  1159,   391,   920,
     135,   136,   137,   751,   354,  1324,   866,  1218,   821,   888,
      54,    55,    56,   824,   841,   842,   413,   414,     3,  1276,
     417,     4,  1137,     5,   196,  1310,   389,   390,   196,  1166,
     198,  1219,  1220,    53,   198,  1332,  1333,   244,   245,   135,
     136,   137,   615,     6,     7,     8,     9,  1164,   617,   248,
    1320,   249,    53,   537,   538,  1169,   199,    53,  1022,   937,
     199,   577,  1060,   334,   537,   538,   926,   340,   723,   724,
     725,  1360,    52,   521,   351,   352,   353,   383,   660,   322,
      53,  1186,   499,   200,   368,   193,   500,   200,   371,   373,
     375,   781,    17,    18,   938,  1248,  1087,  1088,   394,  1305,
     201,   781,   781,  1267,   201,   492,  1221,   202,   396,   501,
     502,   202,   403,   404,    67,   405,   522,   523,   410,   493,
     338,   196,   776,  1211,  1212,   337,  1222,   198,   551,   961,
     634,   635,   776,   776,  1232,   422,   952,     3,   338,    33,
       4,   322,     5,   337,    94,   552,  1184,   193,    34,  1296,
     338,  1265,   322,   199,    35,   337,    80,   749,   193,   723,
     724,   725,     6,     7,     8,     9,  1270,  1138,   905,  1139,
      36,   130,  1249,   750,   890,   891,  1369,   893,   652,   895,
     200,   790,  1188,   196,  1335,  1352,   561,  1336,   807,   198,
     613,  1337,   751,  1338,   196,   634,   635,   201,   278,   818,
     198,   187,   927,   562,   326,   929,   349,   230,   231,   232,
     246,  1029,   525,  1137,     4,   199,     5,   230,   231,   232,
     367,   601,     4,   495,     5,   379,   199,  1302,   935,  1174,
     936,   602,   903,   496,   497,   526,   527,   897,   991,   626,
     187,    69,   200,    70,   628,   627,   546,   995,    71,    72,
      73,   238,    74,   200,   946,   241,   667,   947,   910,   201,
    1057,   641,   642,   397,   528,   644,   326,  1066,   940,     3,
     201,   903,     4,   250,     5,   790,   897,   326,    17,    18,
     963,   827,   634,   635,  1334,   547,   548,   549,     3,   911,
     883,     4,   328,     5,     6,     7,     8,     9,     4,  1138,
       5,  1139,  1284,   912,    58,   604,  1361,    53,   836,   329,
     419,   420,   421,     6,     7,     8,     9,   790,   278,   976,
     977,   187,   975,   382,   384,    33,   896,   387,   388,  -141,
    1375,   392,   393,  -155,    34,   398,   400,   402,  1047,   913,
      35,  1048,   407,   409,   424,   425,  1016,   486,   814,  1153,
     415,   668,   669,   670,   671,   672,    36,   487,   248,   350,
     342,   249,   564,   345,   488,   334,   971,   823,   972,     3,
     489,   490,     4,   627,     5,   565,   359,   342,     3,   253,
     254,     4,   566,     5,    17,    18,  1290,  1247,   914,  1284,
     368,   381,   567,   830,     6,     7,     8,     9,   568,  1138,
     554,  1139,   606,     6,     7,     8,     9,   959,   416,   970,
     542,  1033,  1034,   544,  1036,   555,   412,   628,    75,   504,
     616,   837,   971,   418,   972,  1140,  1226,  1227,   556,  1228,
     898,    33,    76,   639,   557,   426,   427,   631,   874,   428,
      34,   643,   505,   506,   193,   507,    35,    77,  1218,   663,
     664,   399,    78,  1055,  1130,   790,  1131,  1122,   903,   193,
    1123,   776,    36,   897,  1070,   607,    17,    18,  1075,   401,
    1077,   649,  1219,  1220,   608,   609,   654,  1132,   610,   611,
     196,   655,   558,   559,    17,    18,   198,   656,   790,   790,
     790,   790,   790,   790,   790,   196,   790,   790,   790,  1248,
     660,   198,  1086,  1096,   877,   878,  1078,   675,  1092,   117,
    1094,  1095,   199,    33,   118,   119,   435,  1133,   436,   437,
     438,   741,    34,   122,   781,   123,   746,   199,    35,   120,
     124,    33,   125,   744,   745,  1030,   126,   930,   931,   200,
      34,   431,   432,   433,    36,   747,    35,  1221,   193,   193,
     193,   193,   193,   193,   200,   776,   201,  1243,   954,   955,
    1167,   748,    36,   202,  1171,   790,   781,  1222,   790,   965,
     966,   201,   794,   127,   795,   128,  1295,   800,   202,  1173,
     805,  1180,   829,  1317,   196,   196,   196,   196,   196,   196,
     198,   198,   198,   198,   198,   198,   801,   776,  1318,   802,
     883,  1165,  1030,  1319,    82,   803,    83,   790,    84,  1011,
    1012,    85,    86,    87,   828,    88,   199,   199,   199,   199,
     199,   199,   230,   231,   232,   978,   804,     3,   979,   838,
       4,     4,     5,     5,  1286,  1181,   839,  1182,   440,   441,
     442,   443,   444,   200,   200,   200,   200,   200,   200,   656,
    1041,  1185,     6,     7,     8,     9,   459,  1359,   460,   869,
     201,   201,   201,   201,   201,   201,  1134,   202,   202,   202,
     202,   202,   202,   732,   733,   734,   461,  1000,   462,   463,
     464,   465,  1272,   791,   858,  1273,  1275,  1274,   859,   193,
     135,   136,   137,   791,   791,   733,   734,  1283,   723,   724,
     725,   871,  1118,  1119,  1120,  1121,  1122,  1204,  1205,  1123,
    1001,  1069,  1253,  1254,  1255,  1256,  1257,  1289,   255,   256,
     257,   258,   259,   260,     3,   196,  1124,     4,   870,     5,
     872,   198,   876,  1214,  1215,   776,   880,   374,   376,   884,
     885,   886,   422,   887,   951,   889,   894,   781,   907,     6,
       7,     8,     9,   908,   193,   917,   193,   199,  1002,  1003,
    1004,  1005,  1006,  1007,  1073,  1074,  1125,   918,   776,   776,
     776,   776,   776,   776,   776,   919,   776,   776,   776,   322,
     932,    89,   933,   934,   200,   193,   939,  -692,   943,  -693,
     196,   941,   196,   942,   790,    90,   198,   944,   198,   949,
    1130,   201,  1131,  1122,   950,   964,  1123,   968,   202,  1107,
      91,  1127,  1135,  1141,   967,    92,  1108,   898,  1128,  1136,
    1142,   196,   199,  1132,   199,   530,   969,   198,   973,   322,
     985,   986,   987,   883,     3,   193,   531,     4,   532,     5,
     988,   989,   992,   990,   993,   776,   994,   996,   776,   200,
     533,   200,   534,   199,   709,   535,   998,  1009,  1010,     6,
       7,     8,     9,  1133,   740,  1014,   201,     3,   201,  1016,
       4,   196,     5,   202,  1015,   202,  1018,   198,   775,   322,
     200,  1019,  1020,   749,  1035,   193,  1039,   776,   775,   775,
    1037,  1046,     6,     7,     8,     9,  1051,   201,  1053,  1052,
    1054,  1056,   536,   199,   326,  1064,  1093,  1148,  1149,  1118,
    1119,  1120,  1121,  1122,  1155,  1126,  1123,  1157,  1150,  1151,
    1160,   196,  1162,  1176,   618,  1177,   619,   198,   620,   621,
     200,  1178,  1179,  1124,   537,   538,   622,   623,  1203,  1197,
    1198,  1189,   322,  1207,  1208,  1209,  1210,   201,   193,  1213,
    1217,  1245,  1233,   199,   326,  1237,  1238,  1246,  1231,  1259,
    1261,  1262,  1268,  1082,  1269,  1280,  1236,  1293,   624,  1297,
    1301,  1304,  1107,  1125,  1127,  1135,  1141,  1306,  1292,  1108,
     200,  1128,  1136,  1142,   196,  1250,   338,   193,  1314,  1307,
     198,   337,  1251,     3,  1308,  1309,     4,   201,     5,  1311,
    1312,  1313,  1324,  1329,   326,     3,   338,  1339,     4,  1343,
       5,   337,  1242,  1349,  1374,  1373,   199,    66,     6,     7,
       8,     9,   791,   196,   808,  1316,  1143,  1235,  1376,   198,
       6,     7,     8,     9,  1315,  1386,   355,  1194,  1271,   361,
    1281,  1282,   661,   200,   909,   922,  1266,   653,  1170,   892,
    1263,  1061,   739,  1285,  1062,   199,  1063,  1076,  1287,  1065,
     201,  1288,   948,  1079,  1291,   640,   953,   326,  1118,  1119,
    1120,  1121,  1122,  1250,   776,  1123,   999,   956,  1299,   957,
    1251,   958,   200,  1298,  1045,  1081,  1364,   815,   679,   799,
    1372,   817,  1124,   395,  1368,   816,   782,  1089,   857,   201,
    1190,  1192,  1192,  1195,  1247,  1090,   202,   631,   646,     0,
    1091,   647,   648,     0,     0,     0,   791,     0,     0,   135,
     136,   137,  1241,  1327,  1328,     0,   759,  1330,     0,     0,
     760,     0,  1125,   322,   761,     0,     0,     0,     0,   193,
     762,     0,     0,     0,   685,     0,  1345,  1346,  1347,  1348,
       0,     0,  1350,     0,     0,  1365,   764,     0,   791,     0,
       0,     0,     0,     0,     0,  1127,  1135,  1141,     0,  1362,
    1366,  1370,  1128,  1136,  1142,   196,  1363,  1367,  1371,     0,
       0,   198,     0,     0,  1377,  1378,  1379,  1380,  1381,  1250,
    1383,     0,     0,     0,  1384,     0,  1251,     0,  1385,     0,
       0,     0,     0,     0,     0,     0,     0,   199,     0,   709,
     709,  1387,   709,     0,   709,     0,  1248,   775,     0,     3,
       0,     0,     4,   406,     5,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   200,   860,   861,   709,    17,    18,
     709,     0,     0,     0,     6,     7,     8,     9,   531,   688,
       0,   201,   689,   690,  1097,     0,   862,     0,   326,  1098,
       0,  1099,   844,  1100,   534,   845,   846,   847,   848,   849,
     850,   851,   852,   853,   854,   855,     0,     0,     0,     0,
       0,  1357,     0,     0,     0,    33,     0,   691,   692,   709,
       0,     0,   709,  1382,    34,  1059,   791,  1059,  1059,  1059,
      35,  1059,  1059,    48,     0,     0,  1072,  1072,     0,     0,
       0,   775,    57,    48,    48,     0,    36,     0,    64,     0,
     187,    48,     0,   477,     0,   478,     0,     0,     0,   791,
     791,   791,   791,   791,   791,   791,     0,   791,   791,   791,
     242,   242,   242,   479,     0,   480,   481,     0,   482,   863,
     864,   865,   585,   775,   709,   709,   483,   484,  1101,   408,
       0,     0,     0,     0,   595,   596,   597,     0,     0,    48,
       0,   344,    48,     0,    17,    18,    64,     0,   242,   242,
     242,     0,    48,     0,   356,   358,    48,   362,     0,     0,
      64,     0,   370,   370,   370,     0,     0,     0,   378,     0,
      48,     0,     0,     0,     0,     0,   791,     0,     0,   791,
       0,     0,   242,     0,     0,     0,   242,   242,     0,   242,
       0,    33,   242,     0,   411,    48,     0,     0,     0,  1102,
      34,     0,    48,     0,     0,     0,    35,   467,   468,     3,
       0,  1024,     4,  1103,     5,     0,   709,   709,   791,   709,
       0,   469,    36,   470,   471,   472,     0,     0,  1104,     0,
       0,     0,     0,  1105,     6,     7,     8,     9,   473,   474,
     475,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   709,     0,
    1058,   775,  1058,  1058,  1058,     0,  1058,  1058,  1068,   709,
       0,  1071,  1071,   709,     0,   709,     0,  1106,     0,     0,
       0,     0,     0,     0,     0,  1130,     0,  1131,  1122,     0,
       0,  1123,     0,     0,   775,   775,   775,   775,   775,   775,
     775,     0,   775,   775,   775,     0,   509,     0,  1132,   510,
       0,     0,     0,   242,     0,     3,     0,     0,     4,     0,
       5,     0,   511,     0,     0,     0,   512,     0,     0,   513,
     514,     0,     0,     0,   515,   516,   517,   518,   519,     0,
       6,     7,     8,     9,     0,     0,     0,     0,  1133,     0,
    1097,     0,     0,     0,     0,  1098,     0,  1099,     0,  1100,
       0,     0,   446,   447,     0,   709,   448,     0,     0,   709,
       0,   775,     0,     0,   775,     0,   449,   450,   451,   452,
     453,   454,   455,   456,   457,     0,   709,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   791,     0,     0,     0,     0,
       0,     0,     0,   775,     0,     0,     0,     0,     0,     0,
       0,     0,   242,     0,     3,     0,     0,     4,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   242,     0,     0,     0,     0,   132,     0,     0,     6,
       7,     8,     9,   133,  1101,   826,     0,     0,     0,     0,
       0,     0,     0,     0,   252,     0,     0,   242,     0,   831,
       0,   832,   570,   833,   253,   254,     0,     0,   834,     0,
     835,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     255,   256,   257,   258,   259,   260,     0,  1358,   571,     0,
       0,   572,     0,  1110,     0,     0,     0,   261,     0,   262,
     573,     0,   134,   135,   136,   137,     0,     0,     0,     0,
     138,     0,     0,  1111,   139,  1102,     0,     0,   140,     0,
       0,     0,     0,     0,   141,     0,     0,     0,     0,  1103,
       0,     0,     0,     0,   142,     0,     0,     0,     0,     0,
     143,     0,     0,     0,  1104,   144,     0,     0,   145,  1105,
       0,   146,   147,     0,     0,   148,     0,     0,   149,     0,
     150,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,     0,     0,   151,   152,     0,   153,   154,   155,   156,
     775,     0,     0,  1239,     0,   157,   158,     0,     0,   159,
     160,   263,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,     0,     0,   264,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   574,     0,     0,     0,   265,     0,
       0,     0,     0,     0,     0,     0,     0,   266,     0,     0,
       0,     0,     0,   267,     0,     0,     0,     0,   268,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   269,     0,
       0,   270,   271,   272,   273,     0,     0,     0,   274,     0,
       0,     0,   275,   276,   183,     0,     0,     0,   184,   185,
       0,     0,     0,     0,     0,     0,   277,     0,     0,   186,
       0,   278,  1112,     0,   187,   188,     0,     3,     0,     0,
       4,     0,     5,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   132,
       0,     0,     6,     7,     8,     9,   133,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   252,     0,     0,
       0,     0,     0,     0,     0,   645,     0,   253,   254,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   255,   256,   257,   258,   259,   260,     0,
       0,   571,     0,     0,   572,     0,  1110,     0,     0,     0,
     261,     0,   262,   573,     0,   134,   135,   136,   137,     0,
       0,     0,     0,   138,     0,     0,  1111,   139,     0,     0,
       0,   140,     0,     0,     0,     0,     0,   141,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   142,     0,     0,
       0,     0,     0,   143,     0,     0,     0,     0,   144,     0,
       0,   145,     0,     0,   146,   147,     0,     0,   148,     0,
       0,   149,     0,   150,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,     0,     0,   151,   152,     0,   153,
     154,   155,   156,     0,     0,     0,     0,     0,   157,   158,
       0,   997,   159,   160,   263,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,     0,     0,   264,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   574,     0,     0,
       0,   265,     0,     0,     0,     0,     0,     0,     0,     0,
     266,     0,     0,     0,     0,     0,   267,     0,     0,     0,
       0,   268,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   269,     0,     0,   270,   271,   272,   273,     0,     0,
       0,   274,     0,     0,     0,   275,   276,   183,     0,     0,
       3,   184,   185,     4,     0,     5,     0,     0,     0,   277,
       0,     0,   186,     0,   278,  1240,     0,   187,   188,     0,
       0,     0,   132,     0,     0,     6,     7,     8,     9,   133,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     252,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     253,   254,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   255,   256,   257,   258,
     259,   260,     0,     0,     0,     0,     0,     0,     0,  1110,
       0,     0,     0,   261,     0,   262,     0,     0,   134,   135,
     136,   137,     0,     0,     0,     0,   138,     0,     0,  1111,
     139,     0,     0,     0,   140,     0,    96,    97,    98,    99,
     141,     0,   100,   101,     0,   102,   103,     0,     0,   104,
     142,     0,     0,     0,     0,     0,   143,     0,     0,     0,
       0,   144,     0,     0,   145,     0,     0,   146,   147,     0,
       0,   148,     0,     0,   149,     0,   150,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,     0,   106,   107,
     108,     0,     0,     0,     0,     0,     0,     0,     0,   151,
     152,     0,   153,   154,   155,   156,     0,     0,     0,     0,
       0,   157,   158,     0,     0,   159,   160,   263,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,     0,   677,
     264,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   265,   678,     0,   132,     0,     0,
       0,     0,     0,   266,     0,     0,     0,     0,     0,   267,
       0,   578,   579,     0,   268,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   269,     0,     0,   270,   271,   272,
     273,     0,   580,   679,   274,     0,     0,     0,   275,   276,
     183,     0,     0,     0,   184,   185,     0,   680,     0,     0,
       0,     0,   277,   109,     0,   186,     0,   278,  1356,     0,
     187,   188,     0,   134,   135,   136,   137,   110,     0,     0,
       0,   681,   111,   112,   113,   682,     0,     0,     0,   683,
       0,     0,   114,     0,     0,   684,     0,   115,     0,   685,
       0,     0,     0,     0,     0,   142,     0,     0,     0,     0,
       0,   686,   581,     0,   928,     0,   144,     0,     0,   145,
       0,     0,   146,   147,     0,     0,   148,     0,     0,   149,
     678,   150,   132,     0,     0,   582,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   592,   593,   594,     0,     0,
     595,   596,   597,     0,   151,   152,     0,   687,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   679,     0,
       0,     0,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,     0,     0,   182,     0,     0,   134,   135,
     136,   137,     0,     0,   688,     0,   681,   689,   690,     0,
     682,     0,     0,     0,   683,     0,     0,     0,     0,     0,
     684,     0,     0,     0,   685,     0,     0,     0,     0,     0,
     142,     0,     0,     0,     0,     0,   686,     0,     0,     0,
       0,   144,   691,   692,   145,     0,     0,   146,   147,     0,
       0,   148,     0,     0,   149,   183,   150,     0,     0,   184,
     185,     0,     0,     0,     0,   945,     0,     0,   693,   694,
       0,     0,     0,     0,     0,   187,     0,     0,     0,   151,
     152,   678,   687,   132,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,     0,   679,
     182,     0,     0,     0,     0,     0,     0,     0,     0,   688,
       0,     0,   689,   690,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   134,
     135,   136,   137,     0,     0,     0,     0,   681,     0,     0,
       0,   682,     0,     0,     0,   683,     0,   691,   692,     0,
       0,   684,     0,     0,     0,   685,     0,     0,     0,     0,
     183,   142,     0,     0,   184,   185,     0,   686,     0,     0,
       0,     0,   144,   693,   694,   145,     0,     0,   146,   147,
     187,     0,   148,     0,     0,   149,     0,   150,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     752,   753,   754,   755,   756,   757,     0,     0,     0,     0,
     151,   152,   758,   687,   739,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,     0,
     679,   182,     0,     0,     0,     0,     0,     0,     0,     0,
     688,     0,     0,   689,   690,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   758,     0,   739,     0,     0,
     134,   135,   136,   137,     0,     0,     0,     0,   759,     0,
       0,     0,   760,     0,     0,     0,   761,     0,   691,   692,
       0,     0,   762,     0,     0,     0,   685,     0,     0,     0,
       0,   183,   763,   679,     0,   184,   185,     0,   764,     0,
       0,     0,     0,   765,   693,   694,   766,     0,     0,   767,
     768,   187,     0,   769,     0,     0,   770,     0,   771,     0,
       0,     0,     0,   134,   135,   136,   137,     0,     0,     0,
       0,   759,     0,     0,     0,   760,     0,     0,     0,   761,
       0,   772,   773,     0,     0,   762,     0,     0,     0,   685,
       0,     0,     0,     0,     0,   763,     0,     0,     0,     0,
       0,   764,     0,     0,     0,     0,   765,     0,     0,   766,
       0,     0,   767,   768,     0,     0,   769,     0,     0,   770,
       0,   771,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   688,     0,     0,   689,   690,     0,     0,     0,     0,
       0,     0,     0,     0,   772,   773,   678,     0,   132,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   691,
     692,     0,   774,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   679,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   688,   693,   694,   689,   690,   278,
       0,     0,   187,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   134,   135,   136,   137,     0,     0,
       0,     0,   681,     0,     0,     0,   682,     0,     0,     0,
     683,     0,   691,   692,     0,   774,   684,     0,     0,     0,
     685,     0,     0,     0,     0,     0,   142,     0,     0,     0,
       0,     0,   686,     0,     0,     0,     0,   144,   693,   694,
     145,     0,   278,   146,   147,   187,   974,   148,     0,     0,
     149,   758,   150,   739,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   151,   152,     0,   687,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   679,
       0,     0,     0,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,     0,     0,   182,     0,     0,   134,
     135,   136,   137,     0,     0,   688,     0,   759,   689,   690,
       0,   760,     0,     0,     0,   761,     0,     0,     0,     0,
       0,   762,     0,     0,     0,   685,   758,     0,   739,     0,
       0,   763,     0,     0,     0,     0,     0,   764,     0,     0,
       0,     0,   765,   691,   692,   766,     0,     0,   767,   768,
       0,     0,   769,     0,     0,   770,   183,   771,     0,     0,
     184,   185,     0,     0,   679,     0,     0,     0,     0,   693,
     694,     0,     0,     0,     0,     0,   187,     0,     0,     0,
     772,   773,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   134,   135,   136,   137,     0,     0,
       0,     0,   759,     0,     0,     0,   760,     0,     0,     0,
     761,     0,     0,     0,     0,     0,   762,     0,     0,     0,
     685,     0,     0,     0,     0,     0,   763,     0,     0,     0,
     688,     0,   764,   689,   690,     0,     0,   765,     0,     0,
     766,     0,     0,   767,   768,     0,     0,   769,     0,     0,
     770,     0,   771,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   691,   692,
       0,   774,     0,     0,     0,   772,   773,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   132,   693,   694,     0,     0,   278,     0,
     133,   187,     0,     0,     0,     0,     0,     0,    10,     0,
      11,   252,    12,     0,     0,    13,    14,    15,     0,    16,
       0,   253,   254,    17,    18,   688,     0,     0,   689,   690,
       0,     0,     0,     0,     0,     0,     0,   255,   256,   257,
     258,   259,   260,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   261,     0,   262,     0,     0,   134,
     135,   136,   137,   691,   692,     0,   774,   138,     0,     0,
      33,   139,     0,     0,     0,   140,     0,     0,     0,    34,
       0,   141,     0,     0,     0,    35,     0,     0,     0,   693,
     694,   142,     0,     0,     0,     0,   187,   143,     0,     0,
       0,    36,   144,     0,     0,   145,     0,     0,   146,   147,
       0,     0,   148,     0,     0,   149,     0,   150,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     151,   152,     0,   153,   154,   155,   156,     0,     0,     0,
       0,     0,   157,   158,     0,     0,   159,   160,   263,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,     0,
       0,   264,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   265,     0,     0,   132,    38,
       0,     0,     0,     0,   266,   133,     0,     0,     0,     0,
     267,     0,     0,     0,    39,   268,     0,     0,     0,    40,
       0,     0,     0,     0,     0,   269,     0,     0,   270,   271,
     272,   273,     0,     0,     0,   274,     0,     0,     0,   275,
     276,   183,     0,     0,     0,   184,   185,     0,     0,     0,
       0,     0,     0,   277,     0,     0,   186,     0,   278,     0,
       0,   187,   188,     0,   134,   135,   136,   137,     0,     0,
       0,     0,   138,     0,     0,     0,   139,     0,     0,     0,
     140,     0,     0,     0,     0,     0,   141,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   142,     0,     0,     0,
       0,     0,   143,     0,     0,     0,     0,   144,     0,     0,
     145,     0,     0,   146,   147,     0,     0,   148,     0,     0,
     149,   132,   150,     0,     0,     0,     0,     0,   133,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   151,   152,     0,   153,   154,
     155,   156,     0,     0,     0,     0,     0,   157,   158,     0,
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,     0,     0,   182,   134,   135,   136,
     137,     0,     0,     0,     0,   138,     0,     0,     0,   139,
       0,     0,     0,   140,     0,     0,     0,     0,     0,   141,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   142,
       0,     0,     0,     0,     0,   143,     0,     0,     0,     0,
     144,     0,     0,   145,     0,     0,   146,   147,     0,     0,
     148,     0,     0,   149,     0,   150,   183,     0,     0,     0,
     184,   185,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   186,     0,   278,     0,     0,   187,   188,   151,   152,
       0,   153,   154,   155,   156,     0,     0,     0,     0,   132,
     157,   158,     0,     0,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,     0,     0,   182,
       0,     0,     0,     0,     0,   679,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   134,   135,   136,   137,     0,
       0,     0,     0,   681,     0,     0,     0,   682,     0,     0,
       0,   683,     0,     0,     0,     0,     0,   684,     0,   183,
       0,   685,     0,   184,   185,     0,     0,   142,     0,     0,
       0,     0,     0,   686,   186,     0,     0,     0,   144,   187,
     188,   145,     0,     0,   146,   147,     0,     0,   148,     0,
       0,   149,     0,   150,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   151,   152,     0,   687,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,     0,     0,   182,     0,     0,
       0,     0,     0,     0,     0,     0,   688,   739,     0,   689,
     690,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   679,   691,   692,     0,     0,     0,     0,
       0,   255,   256,   257,   258,   259,   260,   183,     0,     0,
       0,   184,   185,     0,     0,     0,     0,     0,     0,     0,
     693,   694,     0,   134,   135,   136,   137,   187,     0,   739,
       0,   759,     0,     0,     0,   760,     0,     0,     0,   761,
       0,     0,     0,     0,     0,   762,     0,     0,     0,   685,
       0,     0,     0,     0,     0,   763,     0,     0,     0,     0,
       0,   764,     0,     0,     0,   679,   765,     0,     0,   766,
       0,     0,   767,   768,     0,     0,   769,     0,     0,   770,
       0,   771,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   134,   135,   136,   137,     0,
       0,     0,     0,   759,   772,   773,     0,   760,     0,     0,
       0,   761,     0,     0,     0,     0,     0,   762,     0,     0,
       0,   685,     0,     0,     0,     0,     0,   763,     0,     0,
       0,     0,     0,   764,     0,     0,     0,     0,   765,     0,
       0,   766,     0,     0,   767,   768,     0,     0,   769,     0,
       0,   770,     0,   771,   688,     0,     0,   689,   690,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   772,   773,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   691,   692,     0,   774,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   693,   694,
       0,     0,     0,     0,     0,   187,   688,     0,     0,   689,
     690,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     3,     0,     0,     4,     0,     5,     0,     0,
       0,     0,     0,     0,   691,   692,     0,   774,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     7,     8,
       9,     0,     0,     0,     0,    10,     0,    11,     0,    12,
     693,   694,    13,    14,    15,     0,    16,   187,     0,     0,
      17,    18,    19,     0,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -245,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    39,     0,     0,     0,     0,    40
};

static const yytype_int16 yycheck[] =
{
       1,   347,     3,    29,   184,    62,   345,     1,   346,   349,
      62,   348,   318,    29,    31,   657,   188,   318,    50,   365,
     657,   281,   328,   329,    50,   184,   318,    59,   298,   983,
     894,   377,     5,    59,    23,   987,   328,   329,   988,    29,
     950,  1041,   989,    44,   990,    29,    77,   898,   899,    73,
    1148,    52,    34,   904,     1,    56,     7,     4,     1,     6,
      50,     4,  1132,     6,  1083,    50,    50,   900,    90,    59,
       7,    29,  1169,     7,    59,    59,    14,    15,  1027,    26,
      27,    28,    29,    26,    27,    28,    29,  1014,  1015,     4,
      90,   100,    50,    22,  1043,  1104,  1105,    20,    29,   226,
     121,    59,    97,    23,    99,   100,    12,    46,   103,   104,
     961,   132,   107,   108,   241,    29,   111,   112,   113,    50,
    1201,  1202,    29,   118,   119,   111,   147,   598,    59,   161,
     598,   126,   142,    71,    72,    73,    50,   147,     8,   125,
      73,   127,    23,    50,    47,    59,    89,    85,    86,    87,
     125,    90,    59,   100,    47,    20,    94,   660,   184,    46,
      89,  1258,   188,   101,   102,   668,  1263,    90,   106,   672,
      90,    91,    92,    43,    80,    90,   647,    90,    46,   647,
       7,     8,     9,    46,   193,   194,   124,   125,     1,  1198,
     128,     4,  1146,     6,   184,  1276,    34,    35,   188,  1032,
     184,   114,   115,    90,   188,   227,   228,    39,    40,    90,
      91,    92,   229,    26,    27,    28,    29,  1166,   235,    46,
    1290,    48,    90,   209,   210,    90,   184,    90,   228,     8,
     188,   263,   931,    60,   209,   210,   257,    64,   262,   263,
     264,  1339,    91,   100,    76,    77,    78,    34,   279,   281,
      90,  1270,   116,   184,   219,   281,   120,   188,    90,    91,
      92,   318,    49,    50,    43,   212,   965,   966,   233,  1269,
     184,   328,   329,  1183,   188,   123,   189,   184,   110,   143,
     144,   188,   114,   115,    38,   117,   143,   144,   120,   137,
     347,   281,   318,  1119,  1120,   347,   209,   281,   113,   288,
     243,   244,   328,   329,  1130,   132,   288,     1,   365,    96,
       4,   343,     6,   365,    42,   130,   289,   343,   105,  1246,
     377,  1172,   354,   281,   111,   377,    38,     8,   354,   262,
     263,   264,    26,    27,    28,    29,  1187,    31,   289,    33,
     127,    36,   289,    24,   649,   650,   289,   652,   226,   654,
     281,   657,   289,   343,  1306,   289,   113,  1307,   343,   343,
     187,  1308,    43,  1309,   354,   243,   244,   281,   288,   354,
     354,   291,   677,   130,   281,   680,    74,   280,   281,   282,
       0,   884,   120,  1337,     4,   343,     6,   280,   281,   282,
      88,   262,     4,   130,     6,   390,   354,  1261,    20,  1041,
      22,   272,  1044,   140,   141,   143,   144,  1044,   814,   241,
     291,    34,   343,    36,   227,   242,   140,   823,    41,    42,
      43,    90,    45,   354,   729,   219,   140,   732,    66,   343,
     930,   258,   259,    34,   172,   262,   343,   937,   708,     1,
     354,  1083,     4,   278,     6,   751,  1083,   354,    49,    50,
     751,   389,   243,   244,  1305,   179,   180,   181,     1,    97,
     640,     4,   287,     6,    26,    27,    28,    29,     4,    31,
       6,    33,     8,   111,    11,   655,   289,    90,   416,   287,
      93,    94,    95,    26,    27,    28,    29,   793,   288,   794,
     795,   291,   793,    99,   100,    96,   655,   103,   104,   288,
    1351,   107,   108,   288,   105,   111,   112,   113,   123,   147,
     111,   126,   118,   119,    98,    99,   274,   113,   350,   277,
     126,   235,   236,   237,   238,   239,   127,   123,   355,   219,
      67,   358,   100,    70,   130,   362,    20,   369,    22,     1,
     136,   137,     4,   370,     6,   113,    83,    84,     1,    51,
      52,     4,   120,     6,    49,    50,     5,   100,   196,     8,
     219,    98,   130,   395,    26,    27,    28,    29,   136,    31,
     102,    33,   273,    26,    27,    28,    29,   749,    34,     7,
     178,   886,   887,   178,   889,   117,   123,   227,   211,   120,
     281,   418,    20,   130,    22,   289,    74,    75,   130,    77,
     657,    96,   225,    89,   136,   189,   190,   241,   625,   193,
     105,    85,   143,   144,   640,   146,   111,   240,    90,   227,
     228,    34,   245,   928,    77,   931,    79,    80,  1270,   655,
      83,   657,   127,  1270,   939,   173,    49,    50,   943,    34,
     945,   226,   114,   115,   182,   183,    73,   100,   186,   187,
     640,    73,   184,   185,    49,    50,   640,     4,   964,   965,
     966,   967,   968,   969,   970,   655,   972,   973,   974,   212,
     279,   655,   964,   974,   243,   244,   946,   256,   970,   225,
     972,   973,   640,    96,   230,   231,   100,   140,   102,   103,
     104,    34,   105,    34,   751,    36,    17,   655,   111,   245,
      41,    96,    43,    15,    16,   885,    47,    15,    16,   640,
     105,    98,    99,   100,   127,    18,   111,   189,   744,   745,
     746,   747,   748,   749,   655,   751,   640,   289,   744,   745,
    1035,   290,   127,   640,  1039,  1041,   793,   209,  1044,    15,
      16,   655,    41,    84,    41,    86,   289,   288,   655,  1041,
      46,  1056,    34,   225,   744,   745,   746,   747,   748,   749,
     744,   745,   746,   747,   748,   749,   288,   793,   240,   288,
     950,  1031,   952,   245,    34,   288,    36,  1083,    38,    98,
      99,    41,    42,    43,   390,    45,   744,   745,   746,   747,
     748,   749,   280,   281,   282,   796,   288,     1,   799,     7,
       4,     4,     6,     6,     7,  1075,     8,  1077,   106,   107,
     108,   109,   110,   744,   745,   746,   747,   748,   749,     4,
       5,  1081,    26,    27,    28,    29,   100,   289,   102,   273,
     744,   745,   746,   747,   748,   749,   289,   744,   745,   746,
     747,   748,   749,   266,   267,   268,   120,    83,   122,   123,
     124,   125,  1191,   318,   294,  1193,  1196,  1194,   294,   885,
      90,    91,    92,   328,   329,   267,   268,  1213,   262,   263,
     264,    89,    76,    77,    78,    79,    80,    67,    68,    83,
     116,   938,   250,   251,   252,   253,   254,  1233,    67,    68,
      69,    70,    71,    72,     1,   885,   100,     4,   273,     6,
     293,   885,    89,    81,    82,   931,    89,    91,    92,    23,
     288,    41,   739,    41,   741,    41,    89,   974,    89,    26,
      27,    28,    29,    89,   950,    89,   952,   885,   164,   165,
     166,   167,   168,   169,   941,   942,   140,    89,   964,   965,
     966,   967,   968,   969,   970,    89,   972,   973,   974,   981,
      17,   211,    18,   290,   885,   981,     5,     7,     5,     7,
     950,     7,   952,     7,  1270,   225,   950,     7,   952,     7,
      77,   885,    79,    80,   288,     7,    83,    18,   885,   980,
     240,   982,   983,   984,    17,   245,   980,  1044,   982,   983,
     984,   981,   950,   100,   952,   100,   290,   981,     8,  1031,
      89,   288,   288,  1183,     1,  1031,   111,     4,   113,     6,
     288,   288,    89,   288,    89,  1041,    89,    89,  1044,   950,
     125,   952,   127,   981,   294,   130,    89,    89,    89,    26,
      27,    28,    29,   140,   304,    89,   950,     1,   952,   274,
       4,  1031,     6,   950,    89,   952,   288,  1031,   318,  1081,
     981,   228,    89,     8,    41,  1081,    32,  1083,   328,   329,
      89,   126,    26,    27,    28,    29,   100,   981,    59,   100,
     100,     5,   177,  1031,   981,    89,    89,   288,     7,    76,
      77,    78,    79,    80,    89,   289,    83,    89,   295,   295,
     246,  1081,    90,     7,    35,    90,    37,  1081,    39,    40,
    1031,    90,    90,   100,   209,   210,    47,    48,  1109,    90,
     219,   293,  1144,    90,  1115,  1116,  1117,  1031,  1144,   287,
      89,    89,   287,  1081,  1031,    90,   287,    89,  1129,   242,
      89,   289,   289,   960,     5,    31,  1137,   288,    79,    91,
      89,   289,  1143,   140,  1145,  1146,  1147,   288,   128,  1143,
    1081,  1145,  1146,  1147,  1144,  1156,  1213,  1183,    90,   288,
    1144,  1213,  1156,     1,   288,   288,     4,  1081,     6,   288,
     288,   288,    90,   119,  1081,     1,  1233,   288,     4,    32,
       6,  1233,   289,    89,   128,    90,  1144,    19,    26,    27,
      28,    29,   657,  1183,   344,  1286,   986,  1133,  1351,  1183,
      26,    27,    28,    29,  1284,  1374,    82,  1099,  1187,    84,
    1211,  1212,   280,  1144,   665,   673,  1176,   268,  1038,   651,
    1168,   932,    23,  1224,   933,  1183,   934,   944,  1229,   936,
    1144,  1232,   735,   949,  1235,   252,   742,  1144,    76,    77,
      78,    79,    80,  1244,  1270,    83,   839,   746,  1249,   747,
    1244,   748,  1183,  1248,   904,   952,  1340,   351,    59,   329,
    1342,   353,   100,   109,  1341,   352,   318,   967,   539,  1183,
    1097,  1098,  1099,  1100,   100,   968,  1183,   241,   263,    -1,
     969,   264,   264,    -1,    -1,    -1,   751,    -1,    -1,    90,
      91,    92,   289,  1294,  1295,    -1,    97,  1298,    -1,    -1,
     101,    -1,   140,  1335,   105,    -1,    -1,    -1,    -1,  1335,
     111,    -1,    -1,    -1,   115,    -1,  1317,  1318,  1319,  1320,
      -1,    -1,  1323,    -1,    -1,   289,   127,    -1,   793,    -1,
      -1,    -1,    -1,    -1,    -1,  1336,  1337,  1338,    -1,  1340,
    1341,  1342,  1336,  1337,  1338,  1335,  1340,  1341,  1342,    -1,
      -1,  1335,    -1,    -1,  1355,  1356,  1357,  1358,  1359,  1360,
    1361,    -1,    -1,    -1,  1365,    -1,  1360,    -1,  1369,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1335,    -1,   649,
     650,  1382,   652,    -1,   654,    -1,   212,   657,    -1,     1,
      -1,    -1,     4,    34,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1335,    98,    99,   677,    49,    50,
     680,    -1,    -1,    -1,    26,    27,    28,    29,   111,   220,
      -1,  1335,   223,   224,    36,    -1,   119,    -1,  1335,    41,
      -1,    43,   150,    45,   127,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,    -1,    -1,    -1,    -1,
      -1,   289,    -1,    -1,    -1,    96,    -1,   258,   259,   729,
      -1,    -1,   732,   289,   105,   930,   931,   932,   933,   934,
     111,   936,   937,     1,    -1,    -1,   941,   942,    -1,    -1,
      -1,   751,    10,    11,    12,    -1,   127,    -1,    16,    -1,
     291,    19,    -1,   100,    -1,   102,    -1,    -1,    -1,   964,
     965,   966,   967,   968,   969,   970,    -1,   972,   973,   974,
      38,    39,    40,   120,    -1,   122,   123,    -1,   125,   212,
     213,   214,   215,   793,   794,   795,   133,   134,   140,    34,
      -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,    67,
      -1,    69,    70,    -1,    49,    50,    74,    -1,    76,    77,
      78,    -1,    80,    -1,    82,    83,    84,    85,    -1,    -1,
      88,    -1,    90,    91,    92,    -1,    -1,    -1,    96,    -1,
      98,    -1,    -1,    -1,    -1,    -1,  1041,    -1,    -1,  1044,
      -1,    -1,   110,    -1,    -1,    -1,   114,   115,    -1,   117,
      -1,    96,   120,    -1,   122,   123,    -1,    -1,    -1,   211,
     105,    -1,   130,    -1,    -1,    -1,   111,    98,    99,     1,
      -1,   881,     4,   225,     6,    -1,   886,   887,  1083,   889,
      -1,   112,   127,   114,   115,   116,    -1,    -1,   240,    -1,
      -1,    -1,    -1,   245,    26,    27,    28,    29,   129,   130,
     131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   928,    -1,
     930,   931,   932,   933,   934,    -1,   936,   937,   938,   939,
      -1,   941,   942,   943,    -1,   945,    -1,   289,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    79,    80,    -1,
      -1,    83,    -1,    -1,   964,   965,   966,   967,   968,   969,
     970,    -1,   972,   973,   974,    -1,   120,    -1,   100,   123,
      -1,    -1,    -1,   241,    -1,     1,    -1,    -1,     4,    -1,
       6,    -1,   136,    -1,    -1,    -1,   140,    -1,    -1,   143,
     144,    -1,    -1,    -1,   148,   149,   150,   151,   152,    -1,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,   140,    -1,
      36,    -1,    -1,    -1,    -1,    41,    -1,    43,    -1,    45,
      -1,    -1,    98,    99,    -1,  1035,   102,    -1,    -1,  1039,
      -1,  1041,    -1,    -1,  1044,    -1,   112,   113,   114,   115,
     116,   117,   118,   119,   120,    -1,  1056,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1270,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1083,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   350,    -1,     1,    -1,    -1,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   369,    -1,    -1,    -1,    -1,    23,    -1,    -1,    26,
      27,    28,    29,    30,   140,   383,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    -1,   395,    -1,   397,
      -1,   399,    90,   401,    51,    52,    -1,    -1,   406,    -1,
     408,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    -1,   289,   116,    -1,
      -1,   119,    -1,    80,    -1,    -1,    -1,    84,    -1,    86,
     128,    -1,    89,    90,    91,    92,    -1,    -1,    -1,    -1,
      97,    -1,    -1,   100,   101,   211,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,    -1,   225,
      -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,
     127,    -1,    -1,    -1,   240,   132,    -1,    -1,   135,   245,
      -1,   138,   139,    -1,    -1,   142,    -1,    -1,   145,    -1,
     147,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,    -1,    -1,   170,   171,    -1,   173,   174,   175,   176,
    1270,    -1,    -1,   289,    -1,   182,   183,    -1,    -1,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,    -1,    -1,   211,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   262,    -1,    -1,    -1,   225,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   234,    -1,    -1,
      -1,    -1,    -1,   240,    -1,    -1,    -1,    -1,   245,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   255,    -1,
      -1,   258,   259,   260,   261,    -1,    -1,    -1,   265,    -1,
      -1,    -1,   269,   270,   271,    -1,    -1,    -1,   275,   276,
      -1,    -1,    -1,    -1,    -1,    -1,   283,    -1,    -1,   286,
      -1,   288,   289,    -1,   291,   292,    -1,     1,    -1,    -1,
       4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,   116,    -1,    -1,   119,    -1,    80,    -1,    -1,    -1,
      84,    -1,    86,   128,    -1,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    97,    -1,    -1,   100,   101,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,
      -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,   132,    -1,
      -1,   135,    -1,    -1,   138,   139,    -1,    -1,   142,    -1,
      -1,   145,    -1,   147,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,    -1,    -1,   170,   171,    -1,   173,
     174,   175,   176,    -1,    -1,    -1,    -1,    -1,   182,   183,
      -1,   829,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,    -1,    -1,   211,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   262,    -1,    -1,
      -1,   225,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     234,    -1,    -1,    -1,    -1,    -1,   240,    -1,    -1,    -1,
      -1,   245,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   255,    -1,    -1,   258,   259,   260,   261,    -1,    -1,
      -1,   265,    -1,    -1,    -1,   269,   270,   271,    -1,    -1,
       1,   275,   276,     4,    -1,     6,    -1,    -1,    -1,   283,
      -1,    -1,   286,    -1,   288,   289,    -1,   291,   292,    -1,
      -1,    -1,    23,    -1,    -1,    26,    27,    28,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    84,    -1,    86,    -1,    -1,    89,    90,
      91,    92,    -1,    -1,    -1,    -1,    97,    -1,    -1,   100,
     101,    -1,    -1,    -1,   105,    -1,    34,    35,    36,    37,
     111,    -1,    40,    41,    -1,    43,    44,    -1,    -1,    47,
     121,    -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,    -1,
      -1,   132,    -1,    -1,   135,    -1,    -1,   138,   139,    -1,
      -1,   142,    -1,    -1,   145,    -1,   147,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,
     171,    -1,   173,   174,   175,   176,    -1,    -1,    -1,    -1,
      -1,   182,   183,    -1,    -1,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,    -1,     5,
     211,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   225,    21,    -1,    23,    -1,    -1,
      -1,    -1,    -1,   234,    -1,    -1,    -1,    -1,    -1,   240,
      -1,    98,    99,    -1,   245,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   255,    -1,    -1,   258,   259,   260,
     261,    -1,   119,    59,   265,    -1,    -1,    -1,   269,   270,
     271,    -1,    -1,    -1,   275,   276,    -1,    73,    -1,    -1,
      -1,    -1,   283,   211,    -1,   286,    -1,   288,   289,    -1,
     291,   292,    -1,    89,    90,    91,    92,   225,    -1,    -1,
      -1,    97,   230,   231,   232,   101,    -1,    -1,    -1,   105,
      -1,    -1,   240,    -1,    -1,   111,    -1,   245,    -1,   115,
      -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,
      -1,   127,   189,    -1,     5,    -1,   132,    -1,    -1,   135,
      -1,    -1,   138,   139,    -1,    -1,   142,    -1,    -1,   145,
      21,   147,    23,    -1,    -1,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,    -1,    -1,
     227,   228,   229,    -1,   170,   171,    -1,   173,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      -1,    -1,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,    -1,    -1,   211,    -1,    -1,    89,    90,
      91,    92,    -1,    -1,   220,    -1,    97,   223,   224,    -1,
     101,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,
     111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,    -1,
     121,    -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,    -1,
      -1,   132,   258,   259,   135,    -1,    -1,   138,   139,    -1,
      -1,   142,    -1,    -1,   145,   271,   147,    -1,    -1,   275,
     276,    -1,    -1,    -1,    -1,     5,    -1,    -1,   284,   285,
      -1,    -1,    -1,    -1,    -1,   291,    -1,    -1,    -1,   170,
     171,    21,   173,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,    -1,    59,
     211,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   220,
      -1,    -1,   223,   224,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      90,    91,    92,    -1,    -1,    -1,    -1,    97,    -1,    -1,
      -1,   101,    -1,    -1,    -1,   105,    -1,   258,   259,    -1,
      -1,   111,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,
     271,   121,    -1,    -1,   275,   276,    -1,   127,    -1,    -1,
      -1,    -1,   132,   284,   285,   135,    -1,    -1,   138,   139,
     291,    -1,   142,    -1,    -1,   145,    -1,   147,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
     170,   171,    21,   173,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,    -1,
      59,   211,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     220,    -1,    -1,   223,   224,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    -1,    -1,
      89,    90,    91,    92,    -1,    -1,    -1,    -1,    97,    -1,
      -1,    -1,   101,    -1,    -1,    -1,   105,    -1,   258,   259,
      -1,    -1,   111,    -1,    -1,    -1,   115,    -1,    -1,    -1,
      -1,   271,   121,    59,    -1,   275,   276,    -1,   127,    -1,
      -1,    -1,    -1,   132,   284,   285,   135,    -1,    -1,   138,
     139,   291,    -1,   142,    -1,    -1,   145,    -1,   147,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    -1,    -1,    -1,
      -1,    97,    -1,    -1,    -1,   101,    -1,    -1,    -1,   105,
      -1,   170,   171,    -1,    -1,   111,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,
      -1,   127,    -1,    -1,    -1,    -1,   132,    -1,    -1,   135,
      -1,    -1,   138,   139,    -1,    -1,   142,    -1,    -1,   145,
      -1,   147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   220,    -1,    -1,   223,   224,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   170,   171,    21,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   258,
     259,    -1,   261,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   220,   284,   285,   223,   224,   288,
      -1,    -1,   291,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    90,    91,    92,    -1,    -1,
      -1,    -1,    97,    -1,    -1,    -1,   101,    -1,    -1,    -1,
     105,    -1,   258,   259,    -1,   261,   111,    -1,    -1,    -1,
     115,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,
      -1,    -1,   127,    -1,    -1,    -1,    -1,   132,   284,   285,
     135,    -1,   288,   138,   139,   291,   292,   142,    -1,    -1,
     145,    21,   147,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   170,   171,    -1,   173,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      -1,    -1,    -1,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,    -1,    -1,   211,    -1,    -1,    89,
      90,    91,    92,    -1,    -1,   220,    -1,    97,   223,   224,
      -1,   101,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,
      -1,   111,    -1,    -1,    -1,   115,    21,    -1,    23,    -1,
      -1,   121,    -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,
      -1,    -1,   132,   258,   259,   135,    -1,    -1,   138,   139,
      -1,    -1,   142,    -1,    -1,   145,   271,   147,    -1,    -1,
     275,   276,    -1,    -1,    59,    -1,    -1,    -1,    -1,   284,
     285,    -1,    -1,    -1,    -1,    -1,   291,    -1,    -1,    -1,
     170,   171,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    90,    91,    92,    -1,    -1,
      -1,    -1,    97,    -1,    -1,    -1,   101,    -1,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,
     115,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,
     220,    -1,   127,   223,   224,    -1,    -1,   132,    -1,    -1,
     135,    -1,    -1,   138,   139,    -1,    -1,   142,    -1,    -1,
     145,    -1,   147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   258,   259,
      -1,   261,    -1,    -1,    -1,   170,   171,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,   284,   285,    -1,    -1,   288,    -1,
      30,   291,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      36,    41,    38,    -1,    -1,    41,    42,    43,    -1,    45,
      -1,    51,    52,    49,    50,   220,    -1,    -1,   223,   224,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    86,    -1,    -1,    89,
      90,    91,    92,   258,   259,    -1,   261,    97,    -1,    -1,
      96,   101,    -1,    -1,    -1,   105,    -1,    -1,    -1,   105,
      -1,   111,    -1,    -1,    -1,   111,    -1,    -1,    -1,   284,
     285,   121,    -1,    -1,    -1,    -1,   291,   127,    -1,    -1,
      -1,   127,   132,    -1,    -1,   135,    -1,    -1,   138,   139,
      -1,    -1,   142,    -1,    -1,   145,    -1,   147,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     170,   171,    -1,   173,   174,   175,   176,    -1,    -1,    -1,
      -1,    -1,   182,   183,    -1,    -1,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,    -1,
      -1,   211,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,    -1,    -1,    23,   225,
      -1,    -1,    -1,    -1,   234,    30,    -1,    -1,    -1,    -1,
     240,    -1,    -1,    -1,   240,   245,    -1,    -1,    -1,   245,
      -1,    -1,    -1,    -1,    -1,   255,    -1,    -1,   258,   259,
     260,   261,    -1,    -1,    -1,   265,    -1,    -1,    -1,   269,
     270,   271,    -1,    -1,    -1,   275,   276,    -1,    -1,    -1,
      -1,    -1,    -1,   283,    -1,    -1,   286,    -1,   288,    -1,
      -1,   291,   292,    -1,    89,    90,    91,    92,    -1,    -1,
      -1,    -1,    97,    -1,    -1,    -1,   101,    -1,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,
      -1,    -1,   127,    -1,    -1,    -1,    -1,   132,    -1,    -1,
     135,    -1,    -1,   138,   139,    -1,    -1,   142,    -1,    -1,
     145,    23,   147,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   170,   171,    -1,   173,   174,
     175,   176,    -1,    -1,    -1,    -1,    -1,   182,   183,    -1,
      -1,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,    -1,    -1,   211,    89,    90,    91,
      92,    -1,    -1,    -1,    -1,    97,    -1,    -1,    -1,   101,
      -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,   111,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,
      -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,
     132,    -1,    -1,   135,    -1,    -1,   138,   139,    -1,    -1,
     142,    -1,    -1,   145,    -1,   147,   271,    -1,    -1,    -1,
     275,   276,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   286,    -1,   288,    -1,    -1,   291,   292,   170,   171,
      -1,   173,   174,   175,   176,    -1,    -1,    -1,    -1,    23,
     182,   183,    -1,    -1,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,    -1,    -1,   211,
      -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    97,    -1,    -1,    -1,   101,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,   111,    -1,   271,
      -1,   115,    -1,   275,   276,    -1,    -1,   121,    -1,    -1,
      -1,    -1,    -1,   127,   286,    -1,    -1,    -1,   132,   291,
     292,   135,    -1,    -1,   138,   139,    -1,    -1,   142,    -1,
      -1,   145,    -1,   147,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   170,   171,    -1,   173,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,    -1,    -1,   211,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   220,    23,    -1,   223,
     224,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,   258,   259,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,   271,    -1,    -1,
      -1,   275,   276,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     284,   285,    -1,    89,    90,    91,    92,   291,    -1,    23,
      -1,    97,    -1,    -1,    -1,   101,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,
      -1,   127,    -1,    -1,    -1,    59,   132,    -1,    -1,   135,
      -1,    -1,   138,   139,    -1,    -1,   142,    -1,    -1,   145,
      -1,   147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    97,   170,   171,    -1,   101,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,
      -1,   115,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,
      -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,   132,    -1,
      -1,   135,    -1,    -1,   138,   139,    -1,    -1,   142,    -1,
      -1,   145,    -1,   147,   220,    -1,    -1,   223,   224,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   170,   171,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   258,   259,    -1,   261,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   284,   285,
      -1,    -1,    -1,    -1,    -1,   291,   220,    -1,    -1,   223,
     224,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     0,     1,    -1,    -1,     4,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,   258,   259,    -1,   261,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,    -1,    -1,    34,    -1,    36,    -1,    38,
     284,   285,    41,    42,    43,    -1,    45,   291,    -1,    -1,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,
      -1,    -1,   111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   211,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   240,    -1,    -1,    -1,    -1,   245
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   297,     0,     1,     4,     6,    26,    27,    28,    29,
      34,    36,    38,    41,    42,    43,    45,    49,    50,    51,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    96,   105,   111,   127,   211,   225,   240,
     245,   298,   300,   301,   302,   303,   356,   357,   358,   360,
     373,   298,    91,    90,   353,   353,   353,   358,   360,   373,
     358,   363,   363,   363,   358,   366,   303,    38,   304,    34,
      36,    41,    42,    43,    45,   211,   225,   240,   245,   305,
      38,   306,    34,    36,    38,    41,    42,    43,    45,   211,
     225,   240,   245,   307,    42,   308,    34,    35,    36,    37,
      40,    41,    43,    44,    47,    84,    86,    87,    88,   211,
     225,   230,   231,   232,   240,   245,   309,   225,   230,   231,
     245,   310,    34,    36,    41,    43,    47,    84,    86,   311,
      36,   312,    23,    30,    89,    90,    91,    92,    97,   101,
     105,   111,   121,   127,   132,   135,   138,   139,   142,   145,
     147,   170,   171,   173,   174,   175,   176,   182,   183,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   211,   271,   275,   276,   286,   291,   292,   320,
     354,   453,   454,   455,   456,   457,   510,   513,   517,   518,
     520,   522,   532,   533,   535,   537,   539,   541,   543,   545,
     547,   549,   551,   553,   555,   557,   559,   563,   565,   567,
     568,   570,   572,   574,   576,   578,   580,   582,   584,    47,
     280,   281,   282,   313,   319,    47,   314,   319,    90,   315,
     316,   219,   358,   368,   368,   368,     0,   298,   353,   353,
     278,   372,    41,    51,    52,    67,    68,    69,    70,    71,
      72,    84,    86,   188,   211,   225,   234,   240,   245,   255,
     258,   259,   260,   261,   265,   269,   270,   283,   288,   377,
     378,   379,   380,   381,   382,   386,   387,   390,   391,   398,
     402,   406,   407,   409,   410,   426,   427,   429,   430,   432,
     433,   436,   437,   444,   445,   446,   447,   448,   451,   452,
     456,   461,   462,   463,   464,   465,   466,   471,   472,   473,
     495,   509,   513,   514,   530,   531,   532,   298,   287,   287,
     298,   321,   324,   377,   353,   326,   328,   453,   473,   331,
     353,   335,   360,   374,   358,   360,   363,   363,   363,   366,
     219,   368,   368,   368,   373,   356,   358,   359,   358,   360,
     361,   374,   358,   363,   364,   363,   363,   366,   219,   489,
     358,   368,   369,   368,   369,   368,   369,   363,   358,   357,
     376,   360,   376,    34,   376,   363,   363,   376,   376,    34,
      35,   363,   376,   376,   233,   489,   368,    34,   376,    34,
     376,    34,   376,   368,   368,   368,    34,   376,    34,   376,
     368,   358,   360,   363,   363,   376,    34,   363,   360,    93,
      94,    95,   353,   534,    98,    99,   189,   190,   193,   459,
     460,    98,    99,   100,   536,   100,   102,   103,   104,   538,
     106,   107,   108,   109,   110,   540,    98,    99,   102,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   542,   100,
     102,   120,   122,   123,   124,   125,   544,    98,    99,   112,
     114,   115,   116,   129,   130,   131,   546,   100,   102,   120,
     122,   123,   125,   133,   134,   548,   113,   123,   130,   136,
     137,   550,   123,   137,   552,   130,   140,   141,   554,   116,
     120,   143,   144,   556,   120,   143,   144,   146,   558,   120,
     123,   136,   140,   143,   144,   148,   149,   150,   151,   152,
     560,   100,   143,   144,   564,   120,   143,   144,   172,   566,
     100,   111,   113,   125,   127,   130,   177,   209,   210,   519,
     521,   571,   178,   573,   178,   575,   140,   179,   180,   181,
     577,   113,   130,   569,   102,   117,   130,   136,   184,   185,
     579,   113,   130,   581,   100,   113,   120,   130,   136,   583,
      90,   116,   119,   128,   262,   511,   512,   513,    98,    99,
     119,   189,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   227,   228,   229,   523,   524,
     527,   262,   272,   516,   466,   472,   273,   173,   182,   183,
     186,   187,   585,   353,   465,   319,   281,   319,    35,    37,
      39,    40,    47,    48,    79,   317,   368,   353,   227,   485,
     486,   241,   493,   494,   243,   244,   399,   487,   488,    89,
     445,   353,   353,    85,   353,    90,   511,   523,   524,   226,
     226,   241,   226,   399,    73,    73,     4,   299,   474,   475,
     279,   375,   380,   227,   228,   388,   389,   140,   235,   236,
     237,   238,   239,   392,   393,   256,   408,     5,    21,    59,
      73,    97,   101,   105,   111,   115,   127,   173,   220,   223,
     224,   258,   259,   284,   285,   411,   412,   413,   414,   415,
     416,   417,   419,   420,   421,   422,   423,   424,   425,   454,
     455,   504,   505,   506,   510,   517,   518,   520,   522,   528,
     529,   532,    73,   262,   263,   264,   428,   434,   435,    73,
     431,   434,   266,   267,   268,   438,   439,   440,   441,    23,
     454,    34,   449,   450,    15,    16,    17,    18,   290,     8,
      24,    43,     9,    10,    11,    12,    13,    14,    21,    97,
     101,   105,   111,   121,   127,   132,   135,   138,   139,   142,
     145,   147,   170,   171,   261,   454,   455,   467,   468,   469,
     470,   473,   496,   497,   498,   499,   500,   501,   502,   503,
     505,   506,   507,   508,    41,    41,   484,   496,   497,   484,
     288,   288,   288,   288,   288,    46,   371,   377,   321,   324,
     326,   328,   331,   335,   368,   486,   494,   488,   377,    46,
      46,    46,   328,   368,    46,   328,   358,   363,   376,    34,
     368,   358,   358,   358,   358,   358,   363,   353,     7,     8,
     100,   193,   194,   458,   150,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   561,   521,   294,   294,
      98,    99,   119,   212,   213,   214,   519,   525,   527,   273,
     273,    89,   293,   318,   319,   492,    89,   243,   244,   403,
      89,   442,   443,   466,    23,   288,    41,    41,   527,    41,
     424,   424,   403,   424,    89,   424,   472,   470,   473,   478,
     479,   482,   502,   503,     7,   289,   354,    89,    89,   389,
      66,    97,   111,   147,   196,   395,   354,    89,    89,    89,
     354,   394,   393,   121,   132,   147,   257,   424,     5,   424,
      15,    16,    17,    18,   290,    20,    22,     8,    43,     5,
     434,     7,     7,     5,     7,     5,   424,   424,   439,     7,
     288,   353,   288,   450,   456,   456,   461,   462,   463,   465,
      23,   288,   383,   497,     7,    15,    16,    17,    18,   290,
       7,    20,    22,     8,   292,   497,   424,   424,   298,   298,
     323,   325,   327,   332,   336,    89,   288,   288,   288,   288,
     288,   492,    89,    89,    89,   492,    89,   358,    89,   460,
      83,   116,   164,   165,   166,   167,   168,   169,   562,    89,
      89,    98,    99,   526,    89,    89,   274,   515,   288,   228,
      89,    90,   228,   400,   454,    77,   375,   480,   481,   354,
     466,   476,   477,   424,   424,    41,   424,    89,   400,    32,
     299,     5,   299,   480,   299,   475,   126,   123,   126,   396,
     397,   100,   100,    59,   100,   424,     5,   411,   454,   506,
     507,   412,   413,   414,    89,   416,   411,   418,   454,   473,
     424,   454,   506,   528,   528,   424,   435,   424,   434,   441,
     442,   476,   353,   299,   384,   385,   502,   507,   507,   498,
     499,   500,   502,    89,   502,   502,   497,    36,    41,    43,
      45,   140,   211,   225,   240,   245,   289,   298,   300,   322,
      80,   100,   289,   298,   300,   348,   351,   377,    76,    77,
      78,    79,    80,    83,   100,   140,   289,   298,   300,   333,
      77,    79,   100,   140,   289,   298,   300,   333,    31,    33,
     289,   298,   300,   323,   325,   327,   332,   336,   288,     7,
     295,   295,   515,   277,   515,    89,   345,    89,    20,    90,
     246,   401,    90,   355,   481,   380,   480,   424,    20,    90,
     401,   424,   483,   502,   503,   509,     7,    90,    90,    90,
     424,   434,   434,     5,   289,   380,   478,     7,   289,   293,
     353,   362,   353,   365,   365,   353,   367,    90,   219,   353,
     370,   370,   370,   298,    67,    68,   352,    90,   298,   298,
     298,   355,   355,   287,    81,    82,   334,    89,    90,   114,
     115,   189,   209,   340,   341,   347,    74,    75,    77,   329,
     330,   298,   355,   287,   341,   329,   298,    90,   287,   289,
     289,   289,   289,   289,   345,    89,    89,   100,   212,   289,
     298,   300,   491,   250,   251,   252,   253,   254,   405,   242,
     404,    89,   289,   405,   404,   299,   397,   442,   289,     5,
     299,   385,   324,   326,   331,   335,   370,   342,   342,   342,
      31,   298,   298,   328,     8,   298,     7,   298,   298,   328,
       5,   298,   128,   288,   337,   289,   515,    91,   357,   298,
     404,    89,   400,   404,   289,   509,   288,   288,   288,   288,
     342,   288,   288,   288,    90,   340,   330,   225,   240,   245,
     341,    22,    89,   349,    90,   338,   339,   298,   298,   119,
     298,    90,   227,   228,   299,   325,   327,   332,   336,   288,
     343,   346,   344,    32,   350,   298,   298,   298,   298,    89,
     298,     7,   289,   142,   147,   490,   289,   289,   289,   289,
     345,   289,   298,   300,   485,   289,   298,   300,   493,   289,
     298,   300,   487,    90,   128,   299,   339,   298,   298,   298,
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
     365,   366,   367,   368,   369,   370,   371,   372,   373,   373,
     374,   375,   376,   376,   377,   377,   378,   379,   379,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   381,   381,
     382,   383,   383,   384,   384,   384,   385,   386,   386,   387,
     387,   388,   388,   389,   389,   390,   390,   391,   392,   392,
     393,   393,   393,   393,   393,   393,   394,   395,   395,   395,
     395,   395,   396,   396,   397,   397,   398,   398,   398,   399,
     399,   399,   400,   400,   401,   401,   402,   402,   403,   403,
     403,   404,   404,   404,   404,   405,   405,   405,   405,   405,
     406,   407,   408,   408,   408,   408,   408,   409,   410,   410,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     412,   412,   412,   413,   413,   414,   414,   415,   415,   416,
     417,   417,   418,   418,   419,   419,   420,   421,   422,   423,
     423,   423,   424,   424,   424,   425,   425,   425,   425,   425,
     425,   425,   426,   426,   427,   428,   428,   428,   429,   429,
     430,   431,   431,   431,   431,   431,   432,   432,   433,   434,
     434,   435,   435,   435,   436,   436,   437,   438,   438,   439,
     439,   440,   440,   441,   441,   442,   442,   443,   444,   444,
     445,   445,   446,   447,   447,   448,   449,   449,   450,   451,
     452,   453,   454,   454,   454,   455,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   457,   458,
     458,   458,   459,   459,   459,   459,   459,   460,   460,   461,
     461,   461,   462,   462,   463,   463,   464,   464,   465,   466,
     466,   467,   468,   469,   470,   470,   470,   471,   472,   472,
     472,   473,   474,   474,   474,   475,   475,   475,   476,   476,
     477,   478,   478,   479,   480,   480,   481,   481,   482,   482,
     483,   483,   484,   484,   485,   486,   487,   488,   489,   490,
     490,   491,   491,   492,   493,   493,   494,   495,   495,   495,
     495,   496,   496,   497,   497,   497,   498,   498,   498,   499,
     499,   500,   500,   501,   501,   502,   503,   503,   504,   504,
     505,   506,   506,   506,   506,   506,   506,   506,   506,   506,
     506,   506,   506,   507,   507,   507,   507,   507,   507,   507,
     507,   507,   507,   507,   507,   507,   507,   507,   508,   508,
     508,   508,   508,   508,   509,   509,   509,   509,   509,   509,
     510,   510,   510,   511,   511,   512,   512,   512,   512,   513,
     513,   513,   513,   513,   513,   513,   513,   513,   513,   513,
     513,   513,   513,   513,   513,   513,   513,   513,   513,   514,
     514,   514,   514,   514,   515,   515,   516,   516,   517,   518,
     518,   518,   519,   519,   520,   520,   521,   521,   521,   522,
     522,   522,   523,   523,   524,   524,   524,   524,   524,   524,
     524,   524,   524,   524,   524,   524,   524,   524,   524,   525,
     525,   525,   525,   525,   525,   525,   526,   526,   527,   527,
     527,   527,   528,   528,   529,   529,   530,   530,   531,   532,
     532,   532,   532,   532,   532,   532,   532,   532,   532,   532,
     532,   532,   532,   532,   532,   533,   534,   534,   534,   535,
     536,   536,   536,   537,   538,   538,   538,   538,   539,   540,
     540,   540,   540,   540,   541,   542,   542,   542,   542,   542,
     542,   542,   542,   542,   542,   542,   542,   543,   544,   544,
     544,   544,   544,   544,   544,   545,   546,   546,   546,   546,
     546,   546,   546,   546,   546,   547,   548,   548,   548,   548,
     548,   548,   548,   548,   549,   550,   550,   550,   550,   550,
     551,   552,   552,   553,   554,   554,   554,   555,   556,   556,
     556,   556,   557,   558,   558,   558,   558,   559,   559,   559,
     560,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     561,   561,   562,   562,   562,   562,   562,   562,   562,   562,
     563,   564,   564,   564,   565,   566,   566,   566,   566,   567,
     567,   567,   567,   567,   567,   567,   567,   568,   569,   569,
     570,   571,   571,   571,   571,   572,   573,   574,   575,   576,
     577,   577,   577,   577,   578,   579,   579,   579,   579,   579,
     579,   580,   581,   581,   582,   583,   583,   583,   583,   583,
     584,   585,   585,   585,   585,   585
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
       1,     2,     1,     2,     3,     1,     2,     2,     1,     2,
       2,     2,     0,     1,     1,     2,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     2,     1,     3,     3,     5,     1,     2,     1,
       3,     1,     2,     2,     2,     1,     2,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     1,
       1,     1,     3,     1,     1,     1,     7,     6,     3,     1,
       1,     0,     1,     1,     0,     3,     5,     3,     1,     1,
       0,     0,     3,     3,     3,     1,     1,     1,     1,     1,
       2,     1,     0,     4,     4,     4,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       1,     3,     1,     1,     3,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     4,     2,
       3,     2,     2,     1,     1,     3,     4,     1,     2,     1,
       1,     2,     3,     1,     3,     4,     3,     5,     3,     1,
       3,     1,     1,     1,     1,     2,     1,     1,     2,     2,
       1,     1,     3,     1,     1,     1,     2,     1,     4,     5,
       1,     1,     7,     6,     1,     1,     1,     2,     2,     6,
       1,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     1,
       3,     3,     3,     1,     1,     1,     1,     3,     1,     1,
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
       3,     4,     1,     4,     0,     2,     1,     1,     5,     7,
       5,     4,     1,     1,     2,     3,     1,     1,     1,     2,
       3,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     4,     5,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     6,     1,     1,     1,     2,
       1,     1,     1,     2,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
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
          case 90: /* "string"  */
#line 264 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3628 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 91: /* "quoted string"  */
#line 264 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3634 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 92: /* "string with a trailing asterisk"  */
#line 264 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3640 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 301: /* line  */
#line 511 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3646 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 302: /* base_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3652 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 303: /* add_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3658 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 304: /* replace_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3664 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 305: /* create_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3670 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 306: /* insert_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3676 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 307: /* delete_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3682 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 308: /* get_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3688 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 309: /* list_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3694 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 310: /* reset_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3700 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 311: /* flush_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3706 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 312: /* rename_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3712 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 313: /* import_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3718 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 314: /* export_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3724 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 315: /* monitor_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3730 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 316: /* monitor_event  */
#line 711 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3736 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 320: /* describe_cmd  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3742 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 321: /* table_block_alloc  */
#line 526 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 3748 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 324: /* chain_block_alloc  */
#line 528 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 3754 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 326: /* set_block_alloc  */
#line 537 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3760 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 328: /* set_block_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3766 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 331: /* map_block_alloc  */
#line 540 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3772 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* flowtable_block_alloc  */
#line 543 "parser_bison.y" /* yacc.c:1257  */
      { flowtable_free(((*yyvaluep).flowtable)); }
#line 3778 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* flowtable_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3784 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* flowtable_list_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3790 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* flowtable_expr_member  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3796 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* data_type_atom_expr  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3802 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* data_type_expr  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3808 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* obj_block_alloc  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 3814 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* type_identifier  */
#line 503 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3820 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* dev_spec  */
#line 523 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3826 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 353: /* identifier  */
#line 503 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3832 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* string  */
#line 503 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3838 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* table_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3844 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 359: /* tableid_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3850 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* chain_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3856 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* chainid_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3862 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 362: /* chain_identifier  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3868 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 363: /* set_spec  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3874 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 364: /* setid_spec  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3880 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 365: /* set_identifier  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3886 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 366: /* flowtable_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3892 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 368: /* obj_spec  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3898 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 369: /* objid_spec  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3904 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 370: /* obj_identifier  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3910 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 371: /* handle_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3916 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 372: /* position_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3922 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* rule_position  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3928 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 374: /* ruleid_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3934 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* comment_spec  */
#line 503 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3940 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* ruleset_spec  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3946 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* rule  */
#line 530 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 3952 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 379: /* stmt_list  */
#line 549 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 3958 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 380: /* stmt  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3964 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 381: /* verdict_stmt  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3970 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 382: /* verdict_map_stmt  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3976 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* verdict_map_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3982 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* verdict_map_list_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3988 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* verdict_map_list_member_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3994 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* counter_stmt  */
#line 553 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4000 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* counter_stmt_alloc  */
#line 553 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4006 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* log_stmt  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4012 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* log_stmt_alloc  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4018 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* limit_stmt  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4024 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* quota_unit  */
#line 523 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 4030 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* quota_stmt  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4036 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* reject_stmt  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4042 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* reject_stmt_alloc  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4048 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* nat_stmt  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4054 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* nat_stmt_alloc  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4060 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* primary_stmt_expr  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4066 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 412: /* shift_stmt_expr  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4072 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* and_stmt_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4078 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* exclusive_or_stmt_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4084 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* inclusive_or_stmt_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4090 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* basic_stmt_expr  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4096 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* concat_stmt_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4102 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* map_stmt_expr_set  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4108 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* map_stmt_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4114 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* prefix_stmt_expr  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4120 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* range_stmt_expr  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4126 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* wildcard_stmt_expr  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4132 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* multiton_stmt_expr  */
#line 604 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4138 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* stmt_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4144 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* masq_stmt  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4150 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* masq_stmt_alloc  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4156 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* redir_stmt  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4162 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* redir_stmt_alloc  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4168 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 432: /* dup_stmt  */
#line 575 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4174 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* fwd_stmt  */
#line 577 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4180 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 436: /* queue_stmt  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4186 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* queue_stmt_alloc  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4192 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* set_elem_expr_stmt  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4198 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* set_elem_expr_stmt_alloc  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4204 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 444: /* set_stmt  */
#line 579 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4210 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 446: /* map_stmt  */
#line 582 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4216 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 447: /* meter_stmt  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4222 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* flow_stmt_legacy_alloc  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4228 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* meter_stmt_alloc  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4234 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* match_stmt  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4240 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 453: /* variable_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4246 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 454: /* symbol_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4252 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 455: /* integer_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4258 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 456: /* primary_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4264 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* fib_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4270 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* shift_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4276 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* and_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4282 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 463: /* exclusive_or_expr  */
#line 591 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4288 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* inclusive_or_expr  */
#line 591 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4294 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* basic_expr  */
#line 593 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4300 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* concat_expr  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4306 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 467: /* prefix_rhs_expr  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4312 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* range_rhs_expr  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4318 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* wildcard_rhs_expr  */
#line 598 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4324 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* multiton_rhs_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4330 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* map_expr  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4336 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4342 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* set_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4348 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* set_list_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4354 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* set_list_member_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4360 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* meter_key_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4366 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* meter_key_expr_alloc  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4372 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* set_elem_expr  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4378 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* set_elem_expr_alloc  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4384 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* set_lhs_expr  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4390 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 483: /* set_rhs_expr  */
#line 630 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4396 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* initializer_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4402 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* counter_config  */
#line 715 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).counter)); }
#line 4408 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 486: /* counter_obj  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4414 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* quota_config  */
#line 717 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).quota)); }
#line 4420 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* quota_obj  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4426 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 492: /* ct_obj_alloc  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4432 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 493: /* limit_config  */
#line 719 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).limit)); }
#line 4438 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* limit_obj  */
#line 648 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4444 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 495: /* relational_expr  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4450 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 496: /* list_rhs_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4456 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 497: /* rhs_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4462 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 498: /* shift_rhs_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4468 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 499: /* and_rhs_expr  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4474 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* exclusive_or_rhs_expr  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4480 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* inclusive_or_rhs_expr  */
#line 645 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4486 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 502: /* basic_rhs_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4492 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 503: /* concat_rhs_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4498 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* boolean_expr  */
#line 727 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4504 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* keyword_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4510 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* primary_rhs_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4516 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 509: /* verdict_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4522 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* meta_expr  */
#line 692 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4528 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 514: /* meta_stmt  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4534 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* numgen_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4540 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* hash_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4546 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 520: /* rt_expr  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4552 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 522: /* ct_expr  */
#line 702 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4558 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* symbol_stmt_expr  */
#line 643 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4564 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* list_stmt_expr  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4570 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* ct_stmt  */
#line 557 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4576 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* payload_stmt  */
#line 555 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4582 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* payload_expr  */
#line 655 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4588 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* payload_raw_expr  */
#line 655 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4594 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* eth_hdr_expr  */
#line 658 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4600 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 537: /* vlan_hdr_expr  */
#line 658 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4606 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* arp_hdr_expr  */
#line 661 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4612 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* ip_hdr_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4618 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* icmp_hdr_expr  */
#line 664 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4624 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 545: /* ip6_hdr_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4630 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* icmp6_hdr_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4636 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 549: /* auth_hdr_expr  */
#line 670 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4642 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* esp_hdr_expr  */
#line 670 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4648 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 553: /* comp_hdr_expr  */
#line 670 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4654 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 555: /* udp_hdr_expr  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4660 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 557: /* udplite_hdr_expr  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4666 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 559: /* tcp_hdr_expr  */
#line 722 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4672 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 563: /* dccp_hdr_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4678 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 565: /* sctp_hdr_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4684 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 567: /* exthdr_expr  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4690 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 568: /* hbh_hdr_expr  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4696 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 570: /* rt_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4702 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 572: /* rt0_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4708 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 574: /* rt2_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4714 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 576: /* rt4_hdr_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4720 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 578: /* frag_hdr_expr  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4726 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 580: /* dst_hdr_expr  */
#line 682 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4732 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 582: /* mh_hdr_expr  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4738 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 584: /* exthdr_exists_expr  */
#line 731 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4744 "parser_bison.c" /* yacc.c:1257  */
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

#line 4861 "parser_bison.c" /* yacc.c:1429  */
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
#line 5064 "parser_bison.c" /* yacc.c:1646  */
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
#line 5076 "parser_bison.c" /* yacc.c:1646  */
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
#line 5094 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 788 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 5105 "parser_bison.c" /* yacc.c:1646  */
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
#line 5120 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 806 "parser_bison.y" /* yacc.c:1646  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 5130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 813 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 5136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 814 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 5142 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 815 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 5148 "parser_bison.c" /* yacc.c:1646  */
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
#line 5182 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 848 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5188 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 849 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 850 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5200 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 851 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 852 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5212 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 853 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5218 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 854 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5224 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 855 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5230 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 856 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5236 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 857 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5242 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 858 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5248 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 859 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5254 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 860 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5260 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 861 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5266 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 862 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5272 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 866 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5280 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 871 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5290 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 877 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5298 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 882 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5309 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 889 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5317 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 893 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5325 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 898 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5335 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 905 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5345 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 911 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5353 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 916 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5363 "parser_bison.c" /* yacc.c:1646  */
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
#line 5376 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 931 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5384 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 935 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5392 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 939 "parser_bison.y" /* yacc.c:1646  */
    {

				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5401 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 944 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5409 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 950 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5417 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 956 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5425 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 961 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5435 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 967 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5443 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 972 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5454 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 980 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5464 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 987 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5474 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 993 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5482 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 998 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].flowtable)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].flowtable)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_FLOWTABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].flowtable));
			}
#line 5492 "parser_bison.c" /* yacc.c:1646  */
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
#line 5505 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1013 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5513 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1017 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5521 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1021 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5529 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1025 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5537 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1031 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5545 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1037 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5553 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1041 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5561 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1045 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5569 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1049 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5577 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1053 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5585 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1057 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5593 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1061 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5601 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1065 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5609 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1069 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5617 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1073 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5625 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1077 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5633 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1081 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5641 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1085 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5649 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1089 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5657 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1093 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5665 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1097 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5673 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1101 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5681 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1107 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_GET, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5689 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1113 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5697 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1117 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5705 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1121 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5713 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1125 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5721 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1129 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5729 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1133 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5737 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1137 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1141 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5753 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1145 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5761 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1149 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5769 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1153 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5777 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1157 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5785 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1161 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5793 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1165 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5801 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1169 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5809 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1173 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5817 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1177 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5825 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1181 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5833 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1185 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5841 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1189 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5849 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1193 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5857 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1197 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1201 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5873 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1205 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5881 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1209 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5889 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1213 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5897 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1219 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5905 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1223 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5913 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1227 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 5921 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1231 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5929 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1235 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5937 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1239 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5945 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1245 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5953 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1249 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5961 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1253 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5969 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1257 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5977 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1261 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5985 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1265 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5993 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1269 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 6001 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1275 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 6010 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1282 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6020 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1288 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6030 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1296 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1302 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 6050 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1310 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 6061 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1318 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6067 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1319 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1322 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 6079 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1323 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 6085 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1324 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 6091 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1325 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 6097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1326 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 6103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1327 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 6109 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1328 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 6115 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1329 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 6121 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1332 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 6127 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1336 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 6133 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1337 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 6139 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1338 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 6145 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1342 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 6155 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1350 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 6164 "parser_bison.c" /* yacc.c:1646  */
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
#line 6180 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1370 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 6186 "parser_bison.c" /* yacc.c:1646  */
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
#line 6199 "parser_bison.c" /* yacc.c:1646  */
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
#line 6211 "parser_bison.c" /* yacc.c:1646  */
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
#line 6223 "parser_bison.c" /* yacc.c:1646  */
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
#line 6235 "parser_bison.c" /* yacc.c:1646  */
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
#line 6248 "parser_bison.c" /* yacc.c:1646  */
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
#line 6261 "parser_bison.c" /* yacc.c:1646  */
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
#line 6274 "parser_bison.c" /* yacc.c:1646  */
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
#line 6287 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1461 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 6296 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1467 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 6302 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1473 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 6311 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1480 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6319 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1485 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6325 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1489 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6334 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1494 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6343 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1499 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6352 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1504 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6361 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1509 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6370 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1514 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 6379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1526 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6387 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1532 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 6393 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1533 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 6399 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1534 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 6405 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1538 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6413 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1543 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6419 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1547 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6428 "parser_bison.c" /* yacc.c:1646  */
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
#line 6441 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1565 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6452 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1574 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6463 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1583 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6474 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1590 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6483 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1595 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6492 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1603 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 6500 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1607 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 6508 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1612 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 6514 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1613 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 6520 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1617 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.flowtable) = flowtable_alloc(NULL);
			}
#line 6528 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1622 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.flowtable) = (yyvsp[(-1) - (0)].flowtable); }
#line 6534 "parser_bison.c" /* yacc.c:1646  */
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
#line 6551 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1639 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.flowtable)->dev_expr = (yyvsp[-1].expr);
			}
#line 6559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1645 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6568 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1652 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = compound_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 6577 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1657 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 6586 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1665 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
			}
#line 6596 "parser_bison.c" /* yacc.c:1646  */
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
#line 6612 "parser_bison.c" /* yacc.c:1646  */
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
#line 6633 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1707 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 6641 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1712 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6647 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1716 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->counter = *(yyvsp[0].counter);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6656 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1722 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6662 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1726 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->quota = *(yyvsp[0].quota);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6671 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1732 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6677 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1736 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1741 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6691 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1745 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->limit = *(yyvsp[0].limit);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6700 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1751 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6706 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1752 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("mark"); }
#line 6712 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1753 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("dscp"); }
#line 6718 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1754 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("ecn"); }
#line 6724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1755 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("classid"); }
#line 6730 "parser_bison.c" /* yacc.c:1646  */
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
#line 6760 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1786 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 6766 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1787 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = -(yyvsp[0].val); }
#line 6772 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1790 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6778 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1791 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6784 "parser_bison.c" /* yacc.c:1646  */
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
#line 6797 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1805 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_ACCEPT; }
#line 6803 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1806 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_DROP;   }
#line 6809 "parser_bison.c" /* yacc.c:1646  */
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
#line 6826 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1832 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6832 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1836 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6838 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1837 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 6844 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1838 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_INET; }
#line 6850 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1839 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_ARP; }
#line 6856 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1840 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 6862 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1841 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 6868 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1845 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table	= (yyvsp[0].string);
			}
#line 6878 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1853 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family 		= (yyvsp[-2].val);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
				(yyval.handle).handle.location	= (yyloc);
			}
#line 6889 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1862 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 6898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1869 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 6908 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1877 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 6917 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1884 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 6926 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1891 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location 	= (yyloc);
				(yyval.handle).handle.id 		= (yyvsp[0].val);
			}
#line 6936 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1899 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 6945 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1907 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).flowtable	= (yyvsp[0].string);
			}
#line 6954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1914 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).flowtable	= (yyvsp[0].string);
			}
#line 6963 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1921 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj		= (yyvsp[0].string);
			}
#line 6972 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1928 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) 			= (yyvsp[-2].handle);
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 6982 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1936 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj		= (yyvsp[0].string);
			}
#line 6991 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1943 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 7001 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1951 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 7011 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1959 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 7019 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1963 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1970 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 7037 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1977 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strlen((yyvsp[0].string)) > UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed", UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 7050 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1988 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 7059 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1993 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 7068 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 274:
#line 2000 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 7076 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 275:
#line 2004 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 7084 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 276:
#line 2010 "parser_bison.y" /* yacc.c:1646  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 7098 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 277:
#line 2022 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 7108 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 278:
#line 2028 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 7117 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 298:
#line 2056 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7125 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 299:
#line 2060 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7133 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 300:
#line 2066 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 301:
#line 2072 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7150 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 302:
#line 2077 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7161 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 303:
#line 2086 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7170 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2091 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7179 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2099 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 7187 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 309:
#line 2108 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 7195 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 310:
#line 2112 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7205 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 311:
#line 2120 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7213 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 313:
#line 2127 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 7221 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 314:
#line 2131 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 7229 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 317:
#line 2141 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 7237 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 318:
#line 2147 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7245 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2154 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 7254 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 321:
#line 2159 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 7263 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 322:
#line 2164 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 7272 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2169 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 7281 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2174 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 7290 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2179 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 7298 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2185 "parser_bison.y" /* yacc.c:1646  */
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
#line 7328 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2213 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 7336 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 328:
#line 2217 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 7344 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 329:
#line 2221 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 7352 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2225 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 7360 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2229 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 7368 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2235 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7376 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2242 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 7384 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2246 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 7392 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2252 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 7405 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2261 "parser_bison.y" /* yacc.c:1646  */
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
#line 7428 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2280 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7438 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2287 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 7444 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2288 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7450 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2289 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7456 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2292 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("bytes"); }
#line 7462 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2293 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7468 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2296 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7474 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2298 "parser_bison.y" /* yacc.c:1646  */
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
#line 7491 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2313 "parser_bison.y" /* yacc.c:1646  */
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
#line 7511 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2329 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7521 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 348:
#line 2336 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 7527 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 349:
#line 2337 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7533 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 350:
#line 2338 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7539 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2341 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7545 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 352:
#line 2342 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 7551 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 353:
#line 2343 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 7557 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 354:
#line 2345 "parser_bison.y" /* yacc.c:1646  */
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
#line 7574 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 355:
#line 2359 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL; }
#line 7580 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 356:
#line 2360 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60; }
#line 7586 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 357:
#line 2361 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 7592 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 358:
#line 2362 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 7598 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2363 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 7604 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 361:
#line 2370 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 7612 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2376 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 7621 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 363:
#line 2381 "parser_bison.y" /* yacc.c:1646  */
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
#line 7636 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 364:
#line 2392 "parser_bison.y" /* yacc.c:1646  */
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
#line 7651 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2403 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpx_code_type;
				xfree((yyvsp[0].string));
			}
#line 7665 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2413 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 7673 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2421 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_SNAT); }
#line 7679 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2422 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_DNAT); }
#line 7685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 370:
#line 2425 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7691 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 371:
#line 2426 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7697 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 372:
#line 2427 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7703 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2428 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7709 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2429 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7715 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2430 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7721 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2431 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7727 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2432 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7733 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2433 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7739 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2434 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 381:
#line 2439 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7753 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2443 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7761 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2450 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7769 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 386:
#line 2457 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7777 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2464 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7785 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2474 "parser_bison.y" /* yacc.c:1646  */
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
#line 7806 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2497 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7814 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2500 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7820 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2504 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 7828 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2510 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7836 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2516 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 7849 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 405:
#line 2537 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7857 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 406:
#line 2541 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 407:
#line 2545 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2550 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7883 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2555 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7891 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2559 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7899 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2563 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7907 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2572 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_MASQ); }
#line 7913 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2576 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7921 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2580 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7930 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2585 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7938 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2594 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = nat_stmt_alloc(&(yyloc), NFT_NAT_REDIR); }
#line 7944 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2598 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7952 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2602 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2606 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2610 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7977 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2615 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7986 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2622 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 7995 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2627 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 8005 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2635 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.to = (yyvsp[0].expr);
			}
#line 8014 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2643 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8022 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2648 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 8028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2649 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 8034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2650 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 8040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2658 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 8048 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2664 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8056 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2671 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 8065 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2676 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 8073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2683 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8081 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2688 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 8087 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2689 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 8093 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2697 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8101 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 448:
#line 2703 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 8112 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2710 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-4].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[-3].expr);
			}
#line 8123 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2718 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 8129 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2719 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 8135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2723 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = map_stmt_alloc(&(yyloc));
				(yyval.stmt)->map.op  = (yyvsp[-6].val);
				(yyval.stmt)->map.map = map_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
				(yyval.stmt)->map.set = (yyvsp[-5].expr);
			}
#line 8146 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2732 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 8157 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2738 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 8163 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 455:
#line 2742 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 8171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2748 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 8179 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2755 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 8187 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2761 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 8199 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 460:
#line 2771 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 8207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2777 "parser_bison.y" /* yacc.c:1646  */
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
#line 8227 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 463:
#line 2796 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 8238 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2803 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 8249 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2812 "parser_bison.y" /* yacc.c:1646  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 8262 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 466:
#line 2822 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8268 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2823 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8274 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2824 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8280 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2825 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8286 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2826 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8292 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2827 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8298 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 472:
#line 2828 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8304 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2829 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8310 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2830 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8316 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2831 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8322 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2832 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8328 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2833 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 8334 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2837 "parser_bison.y" /* yacc.c:1646  */
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
#line 8359 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2859 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 8365 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2860 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 8371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2861 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 8377 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2864 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 8383 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2865 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 8389 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2866 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 8395 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2867 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 8401 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2868 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 8407 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 487:
#line 2872 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 8415 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2880 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 491:
#line 2884 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8431 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2891 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8439 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 495:
#line 2898 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2905 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 500:
#line 2915 "parser_bison.y" /* yacc.c:1646  */
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
#line 8476 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2934 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 8484 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2940 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8492 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 503:
#line 2946 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 8505 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 507:
#line 2962 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8513 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 511:
#line 2973 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 512:
#line 2980 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8531 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 513:
#line 2985 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8540 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 515:
#line 2993 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8548 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 516:
#line 2997 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8556 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 517:
#line 3001 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 8564 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 519:
#line 3008 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8573 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 520:
#line 3015 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8581 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 523:
#line 3025 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8589 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 524:
#line 3031 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 8597 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 526:
#line 3038 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val) * 1000;
			}
#line 8605 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 527:
#line 3042 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 8613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 534:
#line 3060 "parser_bison.y" /* yacc.c:1646  */
    {
				struct counter *counter;

				counter = xzalloc(sizeof(*counter));
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
				(yyval.counter) = counter;
			}
#line 8626 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 535:
#line 3071 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
				(yyval.obj)->counter = *(yyvsp[0].counter);
			}
#line 8636 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 536:
#line 3079 "parser_bison.y" /* yacc.c:1646  */
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
#line 8659 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 537:
#line 3100 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
				(yyval.obj)->quota = *(yyvsp[0].quota);
			}
#line 8669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 538:
#line 3107 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 8675 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 539:
#line 3110 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_TCP; }
#line 8681 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 540:
#line 3111 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_UDP; }
#line 8687 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 541:
#line 3115 "parser_bison.y" /* yacc.c:1646  */
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
#line 8706 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 542:
#line 3130 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 8714 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 543:
#line 3136 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 8722 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 544:
#line 3142 "parser_bison.y" /* yacc.c:1646  */
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
#line 8737 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 545:
#line 3153 "parser_bison.y" /* yacc.c:1646  */
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
#line 8761 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 546:
#line 3175 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
				(yyval.obj)->limit = *(yyvsp[0].limit);
			}
#line 8771 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 547:
#line 3183 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8779 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 548:
#line 3187 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8787 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 549:
#line 3191 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8795 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 550:
#line 3195 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-3]), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[-1].expr));
			}
#line 8803 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 551:
#line 3201 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8813 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 552:
#line 3207 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8823 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 553:
#line 3214 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8829 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 554:
#line 3215 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8835 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 555:
#line 3216 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8841 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 557:
#line 3221 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8849 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 558:
#line 3225 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8857 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 560:
#line 3232 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 562:
#line 3239 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8873 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 564:
#line 3246 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8881 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 567:
#line 3256 "parser_bison.y" /* yacc.c:1646  */
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
#line 8902 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 568:
#line 3274 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = true; }
#line 8908 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 569:
#line 3275 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = false; }
#line 8914 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 570:
#line 3279 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 1, &(yyvsp[0].val));
			}
#line 8924 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 571:
#line 3286 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 8930 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 572:
#line 3287 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 8936 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 573:
#line 3288 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 8942 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 574:
#line 3289 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 8948 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 575:
#line 3290 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 8954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 576:
#line 3291 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 8960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 577:
#line 3292 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 8966 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 578:
#line 3293 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 8972 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 579:
#line 3294 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 8978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 580:
#line 3295 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 8984 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 581:
#line 3296 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 8990 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 582:
#line 3297 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 8996 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 583:
#line 3300 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9002 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 584:
#line 3301 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9008 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 585:
#line 3302 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9014 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 586:
#line 3303 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 9020 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 587:
#line 3305 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9031 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 588:
#line 3312 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9042 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 589:
#line 3319 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 590:
#line 3326 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9064 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 591:
#line 3333 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9075 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 592:
#line 3340 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9086 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 593:
#line 3347 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 594:
#line 3354 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9108 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 595:
#line 3361 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9119 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 596:
#line 3368 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 597:
#line 3375 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 9141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 598:
#line 3383 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_EQ; }
#line 9147 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 599:
#line 3384 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_NEQ; }
#line 9153 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 600:
#line 3385 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LT; }
#line 9159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 601:
#line 3386 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GT; }
#line 9165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 602:
#line 3387 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GTE; }
#line 9171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 603:
#line 3388 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LTE; }
#line 9177 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 604:
#line 3392 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 9185 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 605:
#line 3396 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 9193 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 606:
#line 3400 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 9201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 607:
#line 3404 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].string));
			}
#line 9209 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 608:
#line 3408 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].string));
			}
#line 9217 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 609:
#line 3412 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 9225 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 610:
#line 3418 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 9233 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 611:
#line 3422 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 9241 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 612:
#line 3426 "parser_bison.y" /* yacc.c:1646  */
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
#line 9259 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 615:
#line 3444 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_LEN; }
#line 9265 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 616:
#line 3445 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 9271 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 617:
#line 3446 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 9277 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 618:
#line 3447 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 9283 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 619:
#line 3450 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_MARK; }
#line 9289 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 620:
#line 3451 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIF; }
#line 9295 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 621:
#line 3452 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 9301 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 622:
#line 3453 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 9307 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 623:
#line 3454 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIF; }
#line 9313 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 624:
#line 3455 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 9319 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 625:
#line 3456 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 9325 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 626:
#line 3457 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKUID; }
#line 9331 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 627:
#line 3458 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKGID; }
#line 9337 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 628:
#line 3459 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 9343 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 629:
#line 3460 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 9349 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 630:
#line 3461 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 9355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 631:
#line 3462 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 9361 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 632:
#line 3463 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 9367 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 633:
#line 3464 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 9373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 634:
#line 3465 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 9379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 635:
#line 3466 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CPU; }
#line 9385 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 636:
#line 3467 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 9391 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 637:
#line 3468 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 9397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 638:
#line 3469 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 9403 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3473 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 9411 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 640:
#line 3477 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 9419 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 641:
#line 3481 "parser_bison.y" /* yacc.c:1646  */
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
#line 9437 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 642:
#line 3495 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 9445 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3499 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = flow_offload_stmt_alloc(&(yyloc), (yyvsp[0].string));
			}
#line 9453 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 644:
#line 3504 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 9459 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 645:
#line 3505 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 9465 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 646:
#line 3508 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 9471 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 647:
#line 3509 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 9477 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 648:
#line 3513 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 9485 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 649:
#line 3519 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 9494 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 650:
#line 3524 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 9503 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 651:
#line 3529 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 9511 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 652:
#line 3534 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 9517 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 653:
#line 3535 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 9523 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 654:
#line 3539 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 9531 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 655:
#line 3543 "parser_bison.y" /* yacc.c:1646  */
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
#line 9553 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 656:
#line 3562 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 9559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 657:
#line 3563 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 9565 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 658:
#line 3564 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 9571 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 659:
#line 3568 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1, NFPROTO_UNSPEC);
			}
#line 9579 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 660:
#line 3572 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val), NFPROTO_UNSPEC);
			}
#line 9587 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 661:
#line 3576 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 9595 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 662:
#line 3581 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 9601 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 663:
#line 3582 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 9607 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 664:
#line 3585 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 665:
#line 3586 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9619 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 666:
#line 3587 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_MARK; }
#line 9625 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 667:
#line 3588 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATE; }
#line 9631 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 668:
#line 3589 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 9637 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 669:
#line 3590 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 9643 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 670:
#line 3591 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 9649 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 671:
#line 3592 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 9655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 672:
#line 3593 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 673:
#line 3594 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9667 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 674:
#line 3595 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9673 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 675:
#line 3596 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9679 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 676:
#line 3597 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 9685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 677:
#line 3598 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 9691 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 679:
#line 3602 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9697 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 680:
#line 3603 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9703 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 681:
#line 3604 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9709 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 682:
#line 3605 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9715 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 683:
#line 3606 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9721 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 684:
#line 3607 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9727 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 686:
#line 3611 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9733 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 687:
#line 3612 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9739 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 688:
#line 3615 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 9745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 689:
#line 3616 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 9751 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 690:
#line 3617 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 9757 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 691:
#line 3618 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 9763 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 694:
#line 3626 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9773 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 695:
#line 3632 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 696:
#line 3640 "parser_bison.y" /* yacc.c:1646  */
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
#line 9800 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 697:
#line 3653 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 9808 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 698:
#line 3659 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].expr)->ops->type == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9819 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 715:
#line 3686 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				payload_init_raw((yyval.expr), (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[0].val));
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
			}
#line 9830 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 716:
#line 3694 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 9836 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 717:
#line 3695 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 9842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 718:
#line 3696 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 9848 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 719:
#line 3700 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 9856 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 720:
#line 3705 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 9862 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 721:
#line 3706 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 9868 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 722:
#line 3707 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 9874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 723:
#line 3711 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 9882 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 724:
#line 3716 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_VID; }
#line 9888 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 725:
#line 3717 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_CFI; }
#line 9894 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 726:
#line 3718 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_PCP; }
#line 9900 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 727:
#line 3719 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 9906 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 728:
#line 3723 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 9914 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 729:
#line 3728 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HRD; }
#line 9920 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 730:
#line 3729 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PRO; }
#line 9926 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 731:
#line 3730 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HLN; }
#line 9932 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 732:
#line 3731 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PLN; }
#line 9938 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 733:
#line 3732 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_OP; }
#line 9944 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 734:
#line 3736 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 9952 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 735:
#line 3741 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_VERSION; }
#line 9958 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 736:
#line 3742 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 9964 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 737:
#line 3743 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DSCP; }
#line 9970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 738:
#line 3744 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ECN; }
#line 9976 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 739:
#line 3745 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 9982 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 740:
#line 3746 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ID; }
#line 9988 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 741:
#line 3747 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 9994 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 742:
#line 3748 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_TTL; }
#line 10000 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 743:
#line 3749 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 10006 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 744:
#line 3750 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 10012 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 745:
#line 3751 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_SADDR; }
#line 10018 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 746:
#line 3752 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DADDR; }
#line 10024 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 747:
#line 3756 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 10032 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 748:
#line 3761 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 10038 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 749:
#line 3762 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 10044 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 750:
#line 3763 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 10050 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 751:
#line 3764 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_ID; }
#line 10056 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 752:
#line 3765 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 10062 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 753:
#line 3766 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 10068 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 754:
#line 3767 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 10074 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 755:
#line 3771 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 10082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 756:
#line 3776 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 10088 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 757:
#line 3777 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 10094 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 758:
#line 3778 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_ECN; }
#line 10100 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 759:
#line 3779 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 10106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 760:
#line 3780 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 10112 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 761:
#line 3781 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 10118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 762:
#line 3782 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 10124 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 763:
#line 3783 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 10130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 764:
#line 3784 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 10136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 765:
#line 3787 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 10144 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 766:
#line 3792 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 10150 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 767:
#line 3793 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 10156 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 768:
#line 3794 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 10162 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 769:
#line 3795 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 10168 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 770:
#line 3796 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 10174 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 771:
#line 3797 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 10180 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 772:
#line 3798 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 10186 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 773:
#line 3799 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 10192 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 774:
#line 3803 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 10200 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 775:
#line 3808 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 10206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 776:
#line 3809 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 10212 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 777:
#line 3810 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 10218 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 778:
#line 3811 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SPI; }
#line 10224 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 779:
#line 3812 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 10230 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 780:
#line 3816 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 10238 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 781:
#line 3821 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SPI; }
#line 10244 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 782:
#line 3822 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 10250 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 783:
#line 3826 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 10258 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 784:
#line 3831 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 10264 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 785:
#line 3832 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 10270 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 786:
#line 3833 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_CPI; }
#line 10276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 787:
#line 3837 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 10284 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 788:
#line 3842 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 10290 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 789:
#line 3843 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 10296 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 790:
#line 3844 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 10302 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 791:
#line 3845 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 10308 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 792:
#line 3849 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 10316 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 793:
#line 3854 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 10322 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 794:
#line 3855 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 10328 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 795:
#line 3856 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 10334 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 796:
#line 3857 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 10340 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 797:
#line 3861 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 10348 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 798:
#line 3865 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 10356 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 799:
#line 3869 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 10365 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 800:
#line 3875 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 10371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 801:
#line 3876 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 10377 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 802:
#line 3877 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 10383 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 803:
#line 3878 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 10389 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 804:
#line 3879 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 10395 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 805:
#line 3880 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 10401 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 806:
#line 3881 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 10407 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 807:
#line 3882 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 10413 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 808:
#line 3883 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 10419 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 809:
#line 3884 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 10425 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 810:
#line 3887 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 10431 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 811:
#line 3888 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 10437 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 812:
#line 3889 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 10443 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 813:
#line 3890 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 10449 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 814:
#line 3891 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 10455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 815:
#line 3892 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 10461 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 816:
#line 3893 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 10467 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 817:
#line 3894 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 10473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 818:
#line 3895 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 10479 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 819:
#line 3896 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 10485 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 820:
#line 3897 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 10491 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 821:
#line 3898 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 10497 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 822:
#line 3901 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 10503 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 823:
#line 3902 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 10509 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 824:
#line 3903 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 10515 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 825:
#line 3904 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 10521 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 826:
#line 3905 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 10527 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 827:
#line 3906 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 10533 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 828:
#line 3907 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 10539 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 829:
#line 3908 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 10545 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 830:
#line 3912 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 10553 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 831:
#line 3917 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 10559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 832:
#line 3918 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 10565 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 833:
#line 3919 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 10571 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 834:
#line 3923 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 10579 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 835:
#line 3928 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 10585 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 836:
#line 3929 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 10591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 837:
#line 3930 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 10597 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 838:
#line 3931 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 10603 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 847:
#line 3945 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 10611 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 848:
#line 3950 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 10617 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 849:
#line 3951 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 10623 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 850:
#line 3955 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 10631 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 851:
#line 3960 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 10637 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 852:
#line 3961 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 10643 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 853:
#line 3962 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_TYPE; }
#line 10649 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 854:
#line 3963 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 10655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 855:
#line 3967 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 10663 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 856:
#line 3973 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 10671 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 857:
#line 3979 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 10679 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 858:
#line 3984 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 10685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 859:
#line 3988 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt4, (yyvsp[0].val));
			}
#line 10693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 860:
#line 3993 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_LASTENT; }
#line 10699 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 861:
#line 3994 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_FLAGS; }
#line 10705 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 862:
#line 3995 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT4HDR_TAG; }
#line 10711 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 863:
#line 3997 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT4HDR_SID_1 + (yyvsp[-1].val) - 1;
			}
#line 10719 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 864:
#line 4003 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 10727 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 865:
#line 4008 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 10733 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 866:
#line 4009 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 10739 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 867:
#line 4010 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 10745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 868:
#line 4011 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 10751 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 869:
#line 4012 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 10757 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 870:
#line 4013 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_ID; }
#line 10763 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 871:
#line 4017 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 10771 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 872:
#line 4022 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 10777 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 873:
#line 4023 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 10783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 874:
#line 4027 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 10791 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 875:
#line 4032 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 10797 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 876:
#line 4033 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 10803 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 877:
#line 4034 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_TYPE; }
#line 10809 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 878:
#line 4035 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 10815 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 879:
#line 4036 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 10821 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 880:
#line 4040 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 10837 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 881:
#line 4053 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 10843 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 882:
#line 4054 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 10849 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 883:
#line 4055 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 10855 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 884:
#line 4056 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 10861 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 885:
#line 4057 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_MH; }
#line 10867 "parser_bison.c" /* yacc.c:1646  */
    break;


#line 10871 "parser_bison.c" /* yacc.c:1646  */
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
#line 4060 "parser_bison.y" /* yacc.c:1906  */

