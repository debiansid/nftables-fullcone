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

void parser_init(struct mnl_socket *nf_sock, struct nft_cache *cache,
		 struct parser_state *state, struct list_head *msgs,
		 unsigned int debug_mask, struct output_ctx *octx)
{
	memset(state, 0, sizeof(*state));
	init_list_head(&state->cmds);
	init_list_head(&state->top_scope.symbols);
	state->msgs = msgs;
	state->scopes[0] = scope_init(&state->top_scope, NULL);
	state->ectx.cache = cache;
	state->ectx.msgs = msgs;
	state->ectx.nf_sock = nf_sock;
	state->ectx.debug_mask = debug_mask;
	state->ectx.octx = octx;
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

#line 176 "parser_bison.c" /* yacc.c:339  */

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
    HANDLE = 299,
    RULESET = 300,
    TRACE = 301,
    INET = 302,
    NETDEV = 303,
    ADD = 304,
    UPDATE = 305,
    REPLACE = 306,
    CREATE = 307,
    INSERT = 308,
    DELETE = 309,
    LIST = 310,
    RESET = 311,
    FLUSH = 312,
    RENAME = 313,
    DESCRIBE = 314,
    IMPORT = 315,
    EXPORT = 316,
    MONITOR = 317,
    ALL = 318,
    ACCEPT = 319,
    DROP = 320,
    CONTINUE = 321,
    JUMP = 322,
    GOTO = 323,
    RETURN = 324,
    TO = 325,
    CONSTANT = 326,
    INTERVAL = 327,
    AUTOMERGE = 328,
    TIMEOUT = 329,
    GC_INTERVAL = 330,
    ELEMENTS = 331,
    POLICY = 332,
    MEMORY = 333,
    PERFORMANCE = 334,
    SIZE = 335,
    FLOW = 336,
    METER = 337,
    METERS = 338,
    NUM = 339,
    STRING = 340,
    QUOTED_STRING = 341,
    ASTERISK_STRING = 342,
    LL_HDR = 343,
    NETWORK_HDR = 344,
    TRANSPORT_HDR = 345,
    BRIDGE = 346,
    ETHER = 347,
    SADDR = 348,
    DADDR = 349,
    TYPE = 350,
    VLAN = 351,
    ID = 352,
    CFI = 353,
    PCP = 354,
    ARP = 355,
    HTYPE = 356,
    PTYPE = 357,
    HLEN = 358,
    PLEN = 359,
    OPERATION = 360,
    IP = 361,
    HDRVERSION = 362,
    HDRLENGTH = 363,
    DSCP = 364,
    ECN = 365,
    LENGTH = 366,
    FRAG_OFF = 367,
    TTL = 368,
    PROTOCOL = 369,
    CHECKSUM = 370,
    ICMP = 371,
    CODE = 372,
    SEQUENCE = 373,
    GATEWAY = 374,
    MTU = 375,
    OPTIONS = 376,
    IP6 = 377,
    PRIORITY = 378,
    FLOWLABEL = 379,
    NEXTHDR = 380,
    HOPLIMIT = 381,
    ICMP6 = 382,
    PPTR = 383,
    MAXDELAY = 384,
    AH = 385,
    RESERVED = 386,
    SPI = 387,
    ESP = 388,
    COMP = 389,
    FLAGS = 390,
    CPI = 391,
    UDP = 392,
    SPORT = 393,
    DPORT = 394,
    UDPLITE = 395,
    CSUMCOV = 396,
    TCP = 397,
    ACKSEQ = 398,
    DOFF = 399,
    WINDOW = 400,
    URGPTR = 401,
    OPTION = 402,
    ECHO = 403,
    EOL = 404,
    MAXSEG = 405,
    NOOP = 406,
    SACK = 407,
    SACK0 = 408,
    SACK1 = 409,
    SACK2 = 410,
    SACK3 = 411,
    SACK_PERMITTED = 412,
    TIMESTAMP = 413,
    KIND = 414,
    COUNT = 415,
    LEFT = 416,
    RIGHT = 417,
    TSVAL = 418,
    TSECR = 419,
    DCCP = 420,
    SCTP = 421,
    VTAG = 422,
    RT = 423,
    RT0 = 424,
    RT2 = 425,
    SEG_LEFT = 426,
    ADDR = 427,
    HBH = 428,
    FRAG = 429,
    RESERVED2 = 430,
    MORE_FRAGMENTS = 431,
    DST = 432,
    MH = 433,
    META = 434,
    MARK = 435,
    IIF = 436,
    IIFNAME = 437,
    IIFTYPE = 438,
    OIF = 439,
    OIFNAME = 440,
    OIFTYPE = 441,
    SKUID = 442,
    SKGID = 443,
    NFTRACE = 444,
    RTCLASSID = 445,
    IBRIPORT = 446,
    OBRIPORT = 447,
    PKTTYPE = 448,
    CPU = 449,
    IIFGROUP = 450,
    OIFGROUP = 451,
    CGROUP = 452,
    CLASSID = 453,
    NEXTHOP = 454,
    CT = 455,
    L3PROTOCOL = 456,
    PROTO_SRC = 457,
    PROTO_DST = 458,
    ZONE = 459,
    DIRECTION = 460,
    EVENT = 461,
    EXPIRATION = 462,
    HELPER = 463,
    LABEL = 464,
    STATE = 465,
    STATUS = 466,
    ORIGINAL = 467,
    REPLY = 468,
    COUNTER = 469,
    NAME = 470,
    PACKETS = 471,
    BYTES = 472,
    AVGPKT = 473,
    COUNTERS = 474,
    QUOTAS = 475,
    LIMITS = 476,
    HELPERS = 477,
    LOG = 478,
    PREFIX = 479,
    GROUP = 480,
    SNAPLEN = 481,
    QUEUE_THRESHOLD = 482,
    LEVEL = 483,
    LIMIT = 484,
    RATE = 485,
    BURST = 486,
    OVER = 487,
    UNTIL = 488,
    QUOTA = 489,
    USED = 490,
    NANOSECOND = 491,
    MICROSECOND = 492,
    MILLISECOND = 493,
    SECOND = 494,
    MINUTE = 495,
    HOUR = 496,
    DAY = 497,
    WEEK = 498,
    _REJECT = 499,
    WITH = 500,
    ICMPX = 501,
    SNAT = 502,
    DNAT = 503,
    MASQUERADE = 504,
    REDIRECT = 505,
    RANDOM = 506,
    FULLY_RANDOM = 507,
    PERSISTENT = 508,
    QUEUE = 509,
    QUEUENUM = 510,
    BYPASS = 511,
    FANOUT = 512,
    DUP = 513,
    FWD = 514,
    NUMGEN = 515,
    INC = 516,
    MOD = 517,
    OFFSET = 518,
    JHASH = 519,
    SYMHASH = 520,
    SEED = 521,
    POSITION = 522,
    COMMENT = 523,
    XML = 524,
    JSON = 525,
    VM = 526,
    NOTRACK = 527,
    EXISTS = 528,
    MISSING = 529,
    EXTHDR = 530
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
#define HANDLE 299
#define RULESET 300
#define TRACE 301
#define INET 302
#define NETDEV 303
#define ADD 304
#define UPDATE 305
#define REPLACE 306
#define CREATE 307
#define INSERT 308
#define DELETE 309
#define LIST 310
#define RESET 311
#define FLUSH 312
#define RENAME 313
#define DESCRIBE 314
#define IMPORT 315
#define EXPORT 316
#define MONITOR 317
#define ALL 318
#define ACCEPT 319
#define DROP 320
#define CONTINUE 321
#define JUMP 322
#define GOTO 323
#define RETURN 324
#define TO 325
#define CONSTANT 326
#define INTERVAL 327
#define AUTOMERGE 328
#define TIMEOUT 329
#define GC_INTERVAL 330
#define ELEMENTS 331
#define POLICY 332
#define MEMORY 333
#define PERFORMANCE 334
#define SIZE 335
#define FLOW 336
#define METER 337
#define METERS 338
#define NUM 339
#define STRING 340
#define QUOTED_STRING 341
#define ASTERISK_STRING 342
#define LL_HDR 343
#define NETWORK_HDR 344
#define TRANSPORT_HDR 345
#define BRIDGE 346
#define ETHER 347
#define SADDR 348
#define DADDR 349
#define TYPE 350
#define VLAN 351
#define ID 352
#define CFI 353
#define PCP 354
#define ARP 355
#define HTYPE 356
#define PTYPE 357
#define HLEN 358
#define PLEN 359
#define OPERATION 360
#define IP 361
#define HDRVERSION 362
#define HDRLENGTH 363
#define DSCP 364
#define ECN 365
#define LENGTH 366
#define FRAG_OFF 367
#define TTL 368
#define PROTOCOL 369
#define CHECKSUM 370
#define ICMP 371
#define CODE 372
#define SEQUENCE 373
#define GATEWAY 374
#define MTU 375
#define OPTIONS 376
#define IP6 377
#define PRIORITY 378
#define FLOWLABEL 379
#define NEXTHDR 380
#define HOPLIMIT 381
#define ICMP6 382
#define PPTR 383
#define MAXDELAY 384
#define AH 385
#define RESERVED 386
#define SPI 387
#define ESP 388
#define COMP 389
#define FLAGS 390
#define CPI 391
#define UDP 392
#define SPORT 393
#define DPORT 394
#define UDPLITE 395
#define CSUMCOV 396
#define TCP 397
#define ACKSEQ 398
#define DOFF 399
#define WINDOW 400
#define URGPTR 401
#define OPTION 402
#define ECHO 403
#define EOL 404
#define MAXSEG 405
#define NOOP 406
#define SACK 407
#define SACK0 408
#define SACK1 409
#define SACK2 410
#define SACK3 411
#define SACK_PERMITTED 412
#define TIMESTAMP 413
#define KIND 414
#define COUNT 415
#define LEFT 416
#define RIGHT 417
#define TSVAL 418
#define TSECR 419
#define DCCP 420
#define SCTP 421
#define VTAG 422
#define RT 423
#define RT0 424
#define RT2 425
#define SEG_LEFT 426
#define ADDR 427
#define HBH 428
#define FRAG 429
#define RESERVED2 430
#define MORE_FRAGMENTS 431
#define DST 432
#define MH 433
#define META 434
#define MARK 435
#define IIF 436
#define IIFNAME 437
#define IIFTYPE 438
#define OIF 439
#define OIFNAME 440
#define OIFTYPE 441
#define SKUID 442
#define SKGID 443
#define NFTRACE 444
#define RTCLASSID 445
#define IBRIPORT 446
#define OBRIPORT 447
#define PKTTYPE 448
#define CPU 449
#define IIFGROUP 450
#define OIFGROUP 451
#define CGROUP 452
#define CLASSID 453
#define NEXTHOP 454
#define CT 455
#define L3PROTOCOL 456
#define PROTO_SRC 457
#define PROTO_DST 458
#define ZONE 459
#define DIRECTION 460
#define EVENT 461
#define EXPIRATION 462
#define HELPER 463
#define LABEL 464
#define STATE 465
#define STATUS 466
#define ORIGINAL 467
#define REPLY 468
#define COUNTER 469
#define NAME 470
#define PACKETS 471
#define BYTES 472
#define AVGPKT 473
#define COUNTERS 474
#define QUOTAS 475
#define LIMITS 476
#define HELPERS 477
#define LOG 478
#define PREFIX 479
#define GROUP 480
#define SNAPLEN 481
#define QUEUE_THRESHOLD 482
#define LEVEL 483
#define LIMIT 484
#define RATE 485
#define BURST 486
#define OVER 487
#define UNTIL 488
#define QUOTA 489
#define USED 490
#define NANOSECOND 491
#define MICROSECOND 492
#define MILLISECOND 493
#define SECOND 494
#define MINUTE 495
#define HOUR 496
#define DAY 497
#define WEEK 498
#define _REJECT 499
#define WITH 500
#define ICMPX 501
#define SNAT 502
#define DNAT 503
#define MASQUERADE 504
#define REDIRECT 505
#define RANDOM 506
#define FULLY_RANDOM 507
#define PERSISTENT 508
#define QUEUE 509
#define QUEUENUM 510
#define BYPASS 511
#define FANOUT 512
#define DUP 513
#define FWD 514
#define NUMGEN 515
#define INC 516
#define MOD 517
#define OFFSET 518
#define JHASH 519
#define SYMHASH 520
#define SEED 521
#define POSITION 522
#define COMMENT 523
#define XML 524
#define JSON 525
#define VM 526
#define NOTRACK 527
#define EXISTS 528
#define MISSING 529
#define EXTHDR 530

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 135 "parser_bison.y" /* yacc.c:355  */

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
	struct counter		*counter;
	struct quota		*quota;
	struct ct		*ct;
	struct limit		*limit;
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;
	const struct exthdr_desc *exthdr_desc;

#line 792 "parser_bison.c" /* yacc.c:355  */
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

#line 822 "parser_bison.c" /* yacc.c:358  */

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
#define YYLAST   4722

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  285
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  275
/* YYNRULES -- Number of rules.  */
#define YYNRULES  843
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1296

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   530

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   280,     2,     2,     2,
     281,   282,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   276,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   283,     2,   284,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   277,   279,   278,     2,     2,     2,     2,
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
     275
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   721,   721,   722,   740,   741,   744,   745,   748,   756,
     770,   779,   790,   798,   799,   800,   801,   833,   834,   835,
     836,   837,   838,   839,   840,   841,   842,   843,   844,   845,
     846,   849,   853,   860,   864,   872,   876,   880,   887,   894,
     898,   907,   911,   915,   920,   926,   932,   936,   943,   947,
     955,   962,   969,   973,   982,   986,   990,   994,  1000,  1006,
    1010,  1014,  1018,  1022,  1026,  1030,  1034,  1038,  1042,  1048,
    1052,  1056,  1060,  1064,  1068,  1072,  1076,  1080,  1084,  1088,
    1092,  1096,  1100,  1104,  1108,  1112,  1116,  1120,  1124,  1128,
    1132,  1136,  1140,  1144,  1150,  1154,  1158,  1162,  1166,  1170,
    1176,  1180,  1184,  1188,  1192,  1196,  1200,  1206,  1213,  1219,
    1227,  1233,  1241,  1250,  1251,  1254,  1255,  1256,  1257,  1258,
    1259,  1260,  1261,  1264,  1265,  1268,  1269,  1270,  1273,  1282,
    1288,  1302,  1303,  1304,  1305,  1306,  1317,  1327,  1337,  1348,
    1359,  1368,  1382,  1388,  1389,  1390,  1391,  1392,  1393,  1401,
    1406,  1407,  1408,  1409,  1414,  1419,  1424,  1429,  1434,  1439,
    1442,  1443,  1446,  1450,  1453,  1454,  1455,  1459,  1464,  1465,
    1466,  1467,  1472,  1483,  1492,  1501,  1510,  1515,  1520,  1523,
    1527,  1533,  1534,  1537,  1551,  1552,  1572,  1577,  1578,  1579,
    1580,  1587,  1588,  1589,  1590,  1597,  1598,  1599,  1600,  1606,
    1607,  1608,  1609,  1616,  1617,  1618,  1619,  1620,  1623,  1651,
    1652,  1655,  1656,  1659,  1670,  1671,  1674,  1677,  1678,  1679,
    1682,  1697,  1698,  1701,  1702,  1703,  1704,  1705,  1706,  1709,
    1717,  1724,  1731,  1738,  1745,  1752,  1759,  1767,  1775,  1779,
    1786,  1793,  1805,  1809,  1816,  1820,  1826,  1838,  1844,  1851,
    1852,  1853,  1854,  1855,  1856,  1857,  1858,  1859,  1860,  1861,
    1862,  1863,  1864,  1865,  1866,  1867,  1868,  1871,  1875,  1881,
    1887,  1892,  1901,  1906,  1911,  1914,  1920,  1921,  1923,  1927,
    1935,  1939,  1942,  1946,  1952,  1953,  1956,  1962,  1966,  1969,
    1974,  1979,  1984,  1989,  1994,  2000,  2028,  2032,  2036,  2040,
    2044,  2050,  2054,  2057,  2061,  2067,  2076,  2095,  2103,  2104,
    2105,  2108,  2109,  2112,  2113,  2128,  2144,  2152,  2153,  2154,
    2157,  2158,  2159,  2160,  2175,  2176,  2177,  2178,  2179,  2182,
    2185,  2192,  2196,  2207,  2218,  2228,  2234,  2237,  2242,  2249,
    2250,  2251,  2252,  2253,  2254,  2255,  2256,  2257,  2258,  2261,
    2262,  2266,  2272,  2273,  2279,  2280,  2286,  2287,  2293,  2296,
    2297,  2316,  2317,  2320,  2324,  2327,  2333,  2339,  2350,  2351,
    2352,  2355,  2356,  2357,  2360,  2364,  2368,  2373,  2378,  2382,
    2386,  2392,  2393,  2396,  2399,  2403,  2408,  2414,  2415,  2418,
    2421,  2425,  2429,  2433,  2438,  2445,  2450,  2458,  2465,  2466,
    2472,  2473,  2474,  2477,  2478,  2481,  2487,  2491,  2494,  2499,
    2505,  2506,  2512,  2513,  2516,  2517,  2520,  2526,  2535,  2536,
    2539,  2546,  2549,  2555,  2559,  2562,  2568,  2578,  2584,  2601,
    2602,  2609,  2618,  2629,  2630,  2631,  2632,  2633,  2634,  2635,
    2636,  2637,  2638,  2639,  2640,  2643,  2666,  2667,  2668,  2671,
    2672,  2673,  2674,  2675,  2678,  2682,  2685,  2686,  2690,  2696,
    2697,  2703,  2704,  2710,  2711,  2717,  2720,  2721,  2740,  2746,
    2752,  2763,  2764,  2765,  2768,  2774,  2775,  2776,  2779,  2786,
    2791,  2796,  2799,  2803,  2807,  2813,  2814,  2821,  2827,  2828,
    2831,  2837,  2841,  2844,  2848,  2854,  2855,  2858,  2859,  2862,
    2863,  2866,  2877,  2885,  2906,  2914,  2917,  2918,  2921,  2936,
    2943,  2948,  2959,  2981,  2989,  2993,  2997,  3001,  3007,  3013,
    3021,  3022,  3023,  3026,  3027,  3031,  3037,  3038,  3044,  3045,
    3051,  3052,  3058,  3061,  3062,  3081,  3082,  3085,  3093,  3094,
    3095,  3096,  3097,  3098,  3099,  3100,  3101,  3102,  3103,  3104,
    3107,  3108,  3109,  3110,  3111,  3118,  3125,  3132,  3139,  3146,
    3153,  3160,  3167,  3174,  3181,  3190,  3191,  3192,  3193,  3194,
    3195,  3198,  3202,  3206,  3210,  3214,  3218,  3224,  3228,  3232,
    3247,  3248,  3251,  3252,  3253,  3254,  3257,  3258,  3259,  3260,
    3261,  3262,  3263,  3264,  3265,  3266,  3267,  3268,  3269,  3270,
    3271,  3272,  3273,  3274,  3277,  3281,  3285,  3299,  3305,  3306,
    3309,  3310,  3313,  3319,  3324,  3329,  3335,  3336,  3339,  3343,
    3363,  3364,  3365,  3368,  3372,  3376,  3382,  3383,  3386,  3387,
    3388,  3389,  3390,  3391,  3392,  3393,  3394,  3395,  3396,  3397,
    3398,  3399,  3400,  3403,  3404,  3405,  3406,  3407,  3408,  3409,
    3412,  3413,  3416,  3417,  3418,  3419,  3422,  3423,  3426,  3432,
    3440,  3453,  3459,  3468,  3469,  3470,  3471,  3472,  3473,  3474,
    3475,  3476,  3477,  3478,  3479,  3480,  3481,  3482,  3483,  3486,
    3499,  3500,  3501,  3504,  3510,  3511,  3512,  3515,  3521,  3522,
    3523,  3524,  3527,  3533,  3534,  3535,  3536,  3537,  3540,  3546,
    3547,  3548,  3549,  3550,  3551,  3552,  3553,  3554,  3555,  3556,
    3557,  3560,  3566,  3567,  3568,  3569,  3570,  3571,  3572,  3575,
    3581,  3582,  3583,  3584,  3585,  3586,  3587,  3588,  3589,  3591,
    3597,  3598,  3599,  3600,  3601,  3602,  3603,  3604,  3607,  3613,
    3614,  3615,  3616,  3617,  3620,  3626,  3627,  3630,  3636,  3637,
    3638,  3641,  3647,  3648,  3649,  3650,  3653,  3659,  3660,  3661,
    3662,  3665,  3669,  3673,  3680,  3681,  3682,  3683,  3684,  3685,
    3686,  3687,  3688,  3689,  3692,  3693,  3694,  3695,  3696,  3697,
    3698,  3699,  3700,  3701,  3702,  3703,  3706,  3707,  3708,  3709,
    3710,  3711,  3712,  3713,  3716,  3722,  3723,  3724,  3727,  3733,
    3734,  3735,  3736,  3739,  3740,  3741,  3742,  3743,  3744,  3745,
    3748,  3754,  3755,  3758,  3764,  3765,  3766,  3767,  3770,  3776,
    3782,  3788,  3791,  3797,  3798,  3799,  3800,  3801,  3802,  3805,
    3811,  3812,  3815,  3821,  3822,  3823,  3824,  3825,  3828,  3842,
    3843,  3844,  3845,  3846
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
  "\"undefine\"", "\"fib\"", "\"hook\"", "\"device\"", "\"table\"",
  "\"tables\"", "\"chain\"", "\"chains\"", "\"rule\"", "\"rules\"",
  "\"sets\"", "\"set\"", "\"element\"", "\"map\"", "\"maps\"",
  "\"handle\"", "\"ruleset\"", "\"trace\"", "\"inet\"", "\"netdev\"",
  "\"add\"", "\"update\"", "\"replace\"", "\"create\"", "\"insert\"",
  "\"delete\"", "\"list\"", "\"reset\"", "\"flush\"", "\"rename\"",
  "\"describe\"", "\"import\"", "\"export\"", "\"monitor\"", "\"all\"",
  "\"accept\"", "\"drop\"", "\"continue\"", "\"jump\"", "\"goto\"",
  "\"return\"", "\"to\"", "\"constant\"", "\"interval\"", "\"auto-merge\"",
  "\"timeout\"", "\"gc-interval\"", "\"elements\"", "\"policy\"",
  "\"memory\"", "\"performance\"", "\"size\"", "\"flow\"", "\"meter\"",
  "\"meters\"", "\"number\"", "\"string\"", "\"quoted string\"",
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
  "\"seg-left\"", "\"addr\"", "\"hbh\"", "\"frag\"", "\"reserved2\"",
  "\"more-fragments\"", "\"dst\"", "\"mh\"", "\"meta\"", "\"mark\"",
  "\"iif\"", "\"iifname\"", "\"iiftype\"", "\"oif\"", "\"oifname\"",
  "\"oiftype\"", "\"skuid\"", "\"skgid\"", "\"nftrace\"", "\"rtclassid\"",
  "\"ibriport\"", "\"obriport\"", "\"pkttype\"", "\"cpu\"", "\"iifgroup\"",
  "\"oifgroup\"", "\"cgroup\"", "\"classid\"", "\"nexthop\"", "\"ct\"",
  "\"l3proto\"", "\"proto-src\"", "\"proto-dst\"", "\"zone\"",
  "\"direction\"", "\"event\"", "\"expiration\"", "\"helper\"",
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
  "delete_cmd", "list_cmd", "reset_cmd", "flush_cmd", "rename_cmd",
  "import_cmd", "export_cmd", "monitor_cmd", "monitor_event",
  "monitor_object", "monitor_format", "markup_format", "describe_cmd",
  "table_block_alloc", "table_options", "table_block", "chain_block_alloc",
  "chain_block", "set_block_alloc", "set_block", "set_block_expr",
  "set_flag_list", "set_flag", "map_block_alloc", "map_block",
  "set_mechanism", "set_policy_spec", "data_type_atom_expr",
  "data_type_expr", "obj_block_alloc", "counter_block", "quota_block",
  "ct_helper_block", "limit_block", "type_identifier", "hook_spec",
  "prio_spec", "dev_spec", "policy_spec", "chain_policy", "identifier",
  "string", "time_spec", "family_spec", "family_spec_explicit",
  "table_spec", "chain_spec", "chain_identifier", "set_spec",
  "set_identifier", "obj_spec", "obj_identifier", "handle_spec",
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
  "set_stmt", "set_stmt_op", "meter_stmt", "flow_stmt_legacy_alloc",
  "flow_stmt_opts", "flow_stmt_opt", "meter_stmt_alloc", "match_stmt",
  "variable_expr", "symbol_expr", "integer_expr", "primary_expr",
  "fib_expr", "fib_result", "fib_flag", "fib_tuple", "shift_expr",
  "and_expr", "exclusive_or_expr", "inclusive_or_expr", "basic_expr",
  "concat_expr", "prefix_rhs_expr", "range_rhs_expr", "wildcard_rhs_expr",
  "multiton_rhs_expr", "map_expr", "expr", "set_expr", "set_list_expr",
  "set_list_member_expr", "meter_key_expr", "meter_key_expr_alloc",
  "set_elem_expr", "set_elem_expr_alloc", "set_elem_options",
  "set_elem_option", "set_lhs_expr", "set_rhs_expr", "initializer_expr",
  "counter_config", "counter_obj", "quota_config", "quota_obj",
  "ct_obj_type", "ct_l4protoname", "ct_helper_config", "ct_obj_alloc",
  "limit_config", "limit_obj", "relational_expr", "list_rhs_expr",
  "rhs_expr", "shift_rhs_expr", "and_rhs_expr", "exclusive_or_rhs_expr",
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
  "frag_hdr_expr", "frag_hdr_field", "dst_hdr_expr", "dst_hdr_field",
  "mh_hdr_expr", "mh_hdr_field", "exthdr_exists_expr", "exthdr_key", YY_NULLPTR
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
     525,   526,   527,   528,   529,   530,    61,   123,   125,   124,
      36,    40,    41,    91,    93
};
# endif

#define YYPACT_NINF -1038

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1038)))

#define YYTABLE_NINF -658

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1038,  4488, -1038,   357, -1038, -1038,   -47,    13,    13,    13,
    1178,  1178,  1178,  1178,  1178,  1178, -1038, -1038,  1820,    50,
     780,    74,   736,  3147,   410,   453,   157,  3859,    96,   104,
     133, -1038, -1038, -1038, -1038,   -38,  1178,  1178,  1178, -1038,
   -1038, -1038,   328, -1038,    13, -1038,    13,   -21,  3556, -1038,
     357, -1038,    -7,    40,   357,    20,    58,  3556,    13, -1038,
      41, -1038, -1038,  1178, -1038,  1178,  1178,  1178,  1178,  1178,
     141,  1178,  1178,  1178, -1038,  1178, -1038,  1178,  1178,  1178,
    1178,  1178,  1178,   160,  1178,  1178,  1178, -1038,  1178,  1178,
    1178,  1178,   614,  1178,  1178,  1178,  1178,   208,  1178,  1178,
      31,  1178,   821,   943,  1007,  1178,  1178, -1038,  1178,  1073,
    1171,  1178, -1038,  1178,  1178,  1178,  1178,  1178,   337,  1178,
   -1038,  1178, -1038,   538,    43, -1038, -1038, -1038, -1038,   434,
     412,   762,  1456,   620,   541,  1028,   700,   195,   298,   320,
     256,  1564,   124,   170,   355,   204,   213,   103,   446,   126,
     464,  1946, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
    2497,    79,  3738,   131,   500,    13,  3859, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038,   348, -1038, -1038,   132,
   -1038, -1038,   348, -1038, -1038, -1038, -1038,   510,  1178,    13,
     212,   209,   232, -1038, -1038, -1038, -1038,   389, -1038,   455,
   -1038, -1038, -1038,    13,    13, -1038, -1038,    13,  2320,  2497,
     261, -1038,    63,    44, -1038, -1038, -1038, -1038, -1038, -1038,
     411,   463, -1038,   492, -1038,   268,  3556, -1038, -1038, -1038,
   -1038,   302, -1038,   190, -1038, -1038, -1038,   296, -1038,  2279,
   -1038,    91, -1038,   135, -1038, -1038, -1038,   398, -1038, -1038,
     514, -1038, -1038, -1038,   551,   535,   542,   291, -1038,   214,
   -1038,  2878, -1038, -1038, -1038,   534, -1038, -1038, -1038,   545,
   -1038,  3298,  3298, -1038,   299,   310, -1038, -1038,   317, -1038,
   -1038, -1038,   322,   553,  3556,    20,    58, -1038,    41, -1038,
    1178,   212,   209,   232,  3556, -1038, -1038, -1038, -1038,    41,
   -1038, -1038,  1178, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038,  1178, -1038, -1038, -1038, -1038, -1038,  1178,  1178, -1038,
   -1038,   572,  1178, -1038,  1178, -1038,  1178, -1038,  1178, -1038,
   -1038, -1038, -1038,  1178, -1038,  1178, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038,  1178, -1038,    13, -1038, -1038, -1038, -1038,
     608, -1038, -1038, -1038, -1038, -1038,   656,   -16, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038,  1285, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038,   -59, -1038, -1038,   350,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
    1100, -1038, -1038, -1038, -1038,   413,   101,   417,   588, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038,   399, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038,   348, -1038, -1038,
     632, -1038, -1038,   375, -1038, -1038, -1038, -1038,   648, -1038,
   -1038, -1038, -1038, -1038,  3859, -1038, -1038,   484,   701,   719,
    1100,   726,  3115,  3115,   375,  3115,   686,  3115,  3738, -1038,
    3298,    23, -1038,   573, -1038, -1038,   688,   704,   302, -1038,
      67,   573,   714,   717,   728,   573,   190, -1038,   -45, -1038,
    3115, -1038, -1038,  2476,   434,   412,   762,  1456, -1038,   541,
     316, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,   630,
     751,   792,   540,   427,   149, -1038, -1038, -1038, -1038, -1038,
     818,   512,   819, -1038, -1038, -1038,   820, -1038, -1038, -1038,
   -1038, -1038,   823,   826, -1038,   829, -1038, -1038, -1038, -1038,
     828, -1038,  2673, -1038,   828,  3115, -1038, -1038,   398, -1038,
     831, -1038,    13,    11, -1038,  3859,  3859,  3859,  3859,  3859,
    3859,    15,  3298, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
      13, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038,   832, -1038,   684,   811,   830,   557,
     383,   847, -1038, -1038, -1038,  2966,  3115,  3115,   357,   832,
   -1038,   357, -1038, -1038, -1038, -1038,   777, -1038, -1038,   593,
     594,   597, -1038,   598, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038,  1178, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038,   793,    43, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038,   912, -1038,   802, -1038, -1038, -1038, -1038, -1038, -1038,
     625, -1038, -1038,   803,   804,   626, -1038, -1038, -1038,   615,
     674, -1038, -1038,   809,    18,    19,   -28,   893,  3859,  3115,
    3115,   865,  3115, -1038, -1038,   825, -1038,    18,   875, -1038,
   -1038,   492,   776,   -28, -1038,   470,   847,   492, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038,   796,   263, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038,   827,   835,   858,   843,
   -1038,  3115,   913,  4011,  4284,  4011,  4011,  4011,   840,  4011,
    4011,    14,  3115,   828,  1364,  1364,  3115,   512,  3115,   512,
   -1038, -1038,   526, -1038,  3859, -1038, -1038, -1038,   551,   535,
     542, -1038,    13,   492, -1038, -1038,  4284,  4284,  4284,  4284,
    4284,  4284,  4284,   857,  4284,  4284,  3298, -1038, -1038, -1038,
   -1038, -1038,  1002,  1556,   426,   852, -1038, -1038, -1038, -1038,
   -1038,   667, -1038, -1038,   938, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038,   662, -1038, -1038, -1038,   626,
     144,   864, -1038, -1038,   868,    90, -1038, -1038,   720, -1038,
     871, -1038,   -28, -1038,   893,  3556,   -28, -1038, -1038,  3115,
   -1038,    95,   720,  3115, -1038,  4196, -1038,   -28,  3298, -1038,
   -1038, -1038, -1038,   950, -1038,   874,   877, -1038,   879, -1038,
    3115, -1038, -1038, -1038, -1038,   630,   751,   792, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,   512,
   -1038,   512,   828, -1038,  3556, -1038,  3386,    25, -1038, -1038,
   -1038, -1038,   684,   811,   830, -1038, -1038, -1038, -1038,   678,
      13,    13,    13,   882,   760,    13,    13,    13, -1038, -1038,
   -1038,   357,   722,   884, -1038, -1038, -1038,   357,   357,   357,
   -1038,   871,   871,   696,   718,   889,     4,   327, -1038, -1038,
   -1038,   357,   871,   698,     4,   327, -1038, -1038, -1038,   357,
    1309,  1818,   536,  1953, -1038,   891, -1038, -1038,   895, -1038,
   -1038,   118, -1038,   482,   750,   899, -1038, -1038, -1038, -1038,
     706,   -28, -1038,   482,   750, -1038, -1038,   492, -1038,   847,
   -1038,   263, -1038, -1038, -1038, -1038,   828,   828,   707,   981,
     492, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,    13,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,   957, -1038,
   -1038, -1038,   357,   357,    41, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038,   292, -1038, -1038, -1038, -1038,
     577, -1038, -1038,   357,    41,   435,   577, -1038, -1038, -1038,
   -1038, -1038,   456, -1038,   626,   907,  1178,   357, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038,   750,   911, -1038,    18,
   -1038,   750, -1038, -1038, -1038, -1038,  1122,  3386, -1038,   721,
     723,   724, -1038,   734,   735,   738,   914, -1038, -1038, -1038,
       4, -1038,   327, -1038, -1038, -1038,   359, -1038,   357, -1038,
     883,   357, -1038, -1038,   -27, -1038, -1038,   492, -1038, -1038,
   -1038,   739, -1038, -1038, -1038,   973, -1038, -1038,   357,   357,
     357,   292, -1038,   -10, -1038, -1038, -1038, -1038, -1038,  2080,
    1518,  2215, -1038,   254,   244,   159,   932,   896, -1038, -1038,
   -1038, -1038, -1038, -1038,   357,   357,   357,   357,   574,   357,
   -1038, -1038, -1038,   357, -1038, -1038, -1038,   357, -1038, -1038,
   -1038, -1038,    72, -1038, -1038, -1038, -1038,   357, -1038, -1038,
   -1038,   940, -1038, -1038, -1038, -1038
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,     0,     0,
     221,   221,   221,   221,   221,   221,   225,   228,   221,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,   227,   226,   223,   224,     0,   221,   221,   221,    14,
      13,     3,     0,    17,     0,   222,     0,   238,     0,    12,
       0,   216,     0,     0,     0,    31,    33,     0,     0,   149,
       0,   167,    18,   221,    19,   221,   221,   221,   221,   221,
       0,   221,   221,   221,    20,   221,    21,   221,   221,   221,
     221,   221,   221,     0,   221,   221,   221,    22,   221,   242,
     221,   242,   242,   221,   221,   242,   242,     0,   221,   242,
       0,   221,   242,   242,   242,   221,   221,    23,   221,   242,
     242,   221,    24,   221,   221,   221,   221,   242,     0,   221,
      25,   221,    26,     0,     0,   432,   217,   218,   219,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
       0,     0,     0,     0,     0,     0,     0,    30,   430,   429,
     433,   434,   128,   443,   438,   578,   441,   442,   439,   440,
     435,   663,   664,   665,   666,   667,   668,   669,   670,   671,
     672,   673,   674,   675,   676,   677,   678,   436,   803,   804,
     805,   806,   807,   808,   809,   437,     0,   125,   126,     0,
      27,   109,     0,    28,   111,   114,    29,   115,   221,     0,
      40,     0,   310,    16,    15,   229,   230,     0,   239,     0,
     571,   572,   573,     0,     0,   576,   422,     0,     0,     0,
     278,   286,     0,   310,   330,   337,   338,   383,   389,   405,
       0,     0,   607,     7,    36,   244,   246,   247,   249,   268,
     252,   276,   255,   284,   256,   257,   258,   331,   259,     0,
     262,   382,   263,   388,   264,   265,   260,   403,   266,   251,
       0,   421,   250,   456,   459,   461,   463,   465,   466,   475,
     477,     0,   476,   427,   267,   578,   254,   261,   253,   435,
       8,     0,     0,    11,     0,     0,    35,   232,     0,    39,
     161,   160,     0,     0,     0,    46,    48,   149,     0,   167,
     221,    53,     0,   310,     0,    59,    60,    61,    62,     0,
      63,   505,   221,    65,    68,    66,    69,   243,    70,    71,
      72,   221,    73,    75,    91,    90,    85,   221,   242,    89,
      88,     0,   221,    78,   221,    76,   221,    79,   221,    82,
      84,    81,    96,   221,    94,   221,    97,    99,   100,   101,
     102,   103,   106,   221,   105,     0,   680,   681,   682,   431,
       0,   449,   450,   451,   452,   453,   455,     0,   684,   685,
     686,   683,   691,   688,   689,   690,   687,   693,   694,   695,
     696,   697,   692,   709,   710,   704,   699,   700,   701,   702,
     703,   705,   706,   707,   708,   698,   712,   715,   714,   713,
     716,   717,   718,   711,   727,   728,   720,   721,   722,   724,
     723,   725,   726,   719,   730,   735,   732,   731,   736,   734,
     733,   737,   729,   740,   743,   739,   741,   742,   738,   746,
     745,   744,   748,   749,   750,   747,   754,   755,   752,   753,
     751,   760,   757,   758,   759,   756,   772,   766,   769,   770,
     764,   765,   767,   768,   771,   773,     0,   761,   797,   795,
     796,   794,   802,   799,   800,   801,   798,   816,   616,   815,
     622,   617,   814,   817,   620,   621,     0,   618,   813,     0,
     818,   821,   820,   812,   811,   810,   828,   825,   823,   824,
     826,   827,   822,   831,   830,   829,   835,   834,   837,   833,
     836,   832,   579,   582,   583,   584,   585,   577,   580,   581,
     636,   637,   629,   630,   628,   638,   639,   655,   632,   641,
     634,   635,   640,   631,   633,   626,   627,   653,   652,   654,
       0,   623,   642,   611,   610,     0,   475,     0,     0,   840,
     839,   841,   842,   843,   838,   428,     0,   108,   127,   110,
     116,   117,   119,   118,   121,   122,   120,   123,   510,   234,
       0,   502,    41,   319,   513,    44,   308,   309,     0,   504,
      42,   237,   418,   419,     0,   574,   575,     0,   579,   577,
       0,   623,     0,     0,   319,     0,     0,     0,     0,     6,
       0,     0,   479,     0,   245,   248,     0,     0,   277,   280,
       0,     0,     0,     0,     0,     0,   285,   287,     0,   329,
       0,   367,   546,     0,   538,   541,   542,   539,   545,   540,
       0,   549,   547,   548,   544,   543,   535,   536,   349,   352,
     354,   356,   358,   359,   364,   371,   368,   369,   370,   372,
     374,   336,   339,   340,   537,   341,   348,   342,   345,   346,
     343,   344,     0,   373,   347,     0,   400,   401,   402,   381,
     386,   398,     0,   387,   392,     0,   412,   413,   404,   406,
     409,   410,     0,     0,   423,     0,     0,     0,     0,     0,
       0,     0,     0,   565,   566,   567,   568,   569,   570,   470,
       0,   538,   541,   542,   539,   559,   540,   560,   558,   557,
     561,   555,   556,   554,   562,   563,   564,   550,   551,   471,
     472,   473,   521,   522,   515,   514,   526,   528,   530,   532,
     533,   520,   552,   553,   523,     0,     0,     0,     0,   500,
     499,     0,   131,   143,   150,   168,     0,   240,    45,     0,
       0,     0,    52,     0,   510,    54,    57,    55,    58,    64,
     510,    74,    87,    86,   221,    92,    77,    80,    83,    95,
      98,   104,   107,     0,     0,   448,   446,   447,   445,   777,
     784,   774,   776,   775,   779,   780,   781,   782,   783,   778,
     785,   763,   619,     0,   643,   644,   646,   645,   647,   648,
       0,   624,   649,     0,     0,   608,   444,   112,   124,     0,
       0,   317,   318,     0,     0,     0,   414,   416,     0,     0,
       0,   649,     0,   279,   307,     0,   316,     0,   395,   397,
     496,     7,     7,   488,   490,   533,   495,     7,   478,   241,
     282,   283,   281,   300,   299,     0,     0,   298,   294,   289,
     290,   291,   292,   295,   293,   288,     0,     0,     0,     0,
     378,     0,   375,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   380,     0,     0,     0,     0,     0,   390,
     408,   407,     0,   425,     0,   424,   457,   458,   460,   462,
     464,   467,     0,     7,   269,   474,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   516,   605,   662,
       9,    10,     0,     0,     0,     0,   236,   131,   143,   150,
     168,     0,    67,    93,     0,   454,   788,   787,   786,   789,
     790,   791,   792,   793,   762,     0,   650,   651,   625,   608,
     608,     0,   615,   195,     0,     0,   312,   311,   313,   417,
       0,   494,   415,   491,   487,     0,   485,   606,   604,     0,
     660,     0,   313,     0,   482,     0,   483,   489,   481,   480,
     297,   303,   304,   296,   302,     0,     0,   335,     0,   379,
       0,   350,   339,   348,   351,   353,   355,   357,   365,   366,
     360,   363,   362,   361,   376,   656,   657,   658,   659,   384,
     399,   391,   393,   411,     0,   271,     0,     0,   272,   519,
     524,   525,   527,   529,   531,   518,   468,   469,   534,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,   133,
     132,     0,     0,     0,    34,   145,   144,     0,     0,     0,
     158,     0,     0,     0,     0,     0,     0,     0,    37,   152,
     151,     0,     0,     0,     0,     0,    38,   170,   169,     0,
       0,     0,     0,     0,   195,     0,   819,   612,     0,   614,
     609,     0,   501,     0,   320,     0,   503,   220,   493,   492,
       0,   486,   661,     0,   320,   315,   396,     7,   533,   497,
     498,     0,   332,   333,   334,   377,   385,   394,     0,     0,
       7,   270,   517,   231,   142,   233,   149,   167,   130,     0,
     235,   186,   186,   186,   134,   214,   215,   213,     0,   146,
     147,   148,     0,     0,     0,   182,   181,   179,   180,   203,
     205,   206,   204,   207,   184,     0,   183,   164,   165,   166,
       0,   163,   159,     0,     0,     0,     0,   178,    47,    49,
      50,    51,     0,   679,   608,     0,     0,     0,   197,   196,
     198,   324,   325,   326,   327,   328,   320,     0,   512,     0,
     426,   320,   306,   484,   301,   420,     0,   274,   273,     0,
       0,     0,   186,     0,     0,     0,     0,   155,   156,   157,
       0,   153,     0,   154,   171,   177,     0,   176,     0,   613,
       0,     0,    43,   511,     0,   314,   305,     7,   143,   150,
     168,     0,   187,   199,   191,   212,   185,   162,     0,     0,
       0,     0,    56,     0,   509,   323,   321,   322,   275,     0,
       0,     0,   195,     0,     0,     0,     0,     0,   173,   175,
     174,   172,   507,   506,     0,     0,     0,     0,     0,     0,
     189,   188,   190,     0,   201,   200,   202,     0,   193,   192,
     194,   211,     0,   508,   135,   136,   137,     0,   138,   141,
     139,     0,   209,   208,   140,   210
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1038, -1038,    -1,  -761,     5, -1038, -1038,  1004, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038,   -18, -1038,   702, -1038,    88,  -318,  -914,  -324,
    -906,  -327,   -43,  -179,  -320,  -915,  -912, -1038,  -175, -1017,
   -1025, -1038, -1038, -1037, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038,   109,  -459,  -583, -1038,   -29,  1414,   794, -1038,   114,
      -4,   340,  -963, -1038, -1038,    56,   960,   771,   421,     7,
   -1038, -1038,  -262, -1038, -1038, -1038, -1038,   -79, -1038, -1038,
   -1038,   418, -1038, -1038, -1038,   415, -1038, -1038, -1038,   -64,
   -1038,   795,  -825,    70, -1038,   439,  -966,   -42, -1038, -1038,
   -1038, -1038, -1038,  -616,   178,   180,   181, -1038,   188, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038,  -492, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038,  -263,   183, -1038, -1038,
   -1038,   386, -1038,   184, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038,   391, -1038, -1038,   -53,   488,   -22,    -8, -1038, -1038,
   -1038,   295,   385,   387,   388, -1038,  -160,  -162, -1038, -1038,
   -1038,  -606, -1038,  -151,    -6, -1038,   242,   200, -1038,  -981,
   -1038,  -797,  -895, -1038, -1038,   798,  -141,   783,  -140,   784,
    1016, -1038, -1038,  -420,  -136,   800, -1038,   833,  -283,   205,
     207,   215, -1038,  -284,  -605, -1038,   -75,   473,  -560, -1038,
    -949,   -14,   885, -1038,   -17, -1038,  -908, -1038,     2,    21,
    -484,    38,   629,    45,   890,   903, -1038, -1038,  -475,   -91,
   -1038, -1038, -1038,    85, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038, -1038,
   -1038, -1038, -1038, -1038, -1038
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1055,   620,  1056,    41,    42,    43,    64,    74,
      76,    87,   107,   112,   120,   122,   220,   223,   226,   227,
     587,   827,   221,   177,   314,  1051,   932,   315,   933,   318,
     934,   319,  1160,  1161,   322,   935,  1071,  1147,  1154,  1155,
    1203,  1253,  1255,  1091,  1254,  1156,  1057,  1293,  1257,  1058,
    1137,  1130,   178,  1098,    44,    45,   229,    47,  1124,    59,
    1126,   230,  1131,   767,   238,    48,   324,   971,   348,  1059,
     265,   266,   267,   268,   269,   914,  1027,  1028,   270,   271,
     628,   629,   272,   273,   636,   637,   874,   868,   993,   994,
     274,   598,   968,  1096,   275,   833,  1188,  1186,   276,   277,
     639,   278,   279,   658,   659,   660,   661,   662,   663,   664,
    1011,   665,   666,   667,   668,   669,   670,   671,   280,   281,
     689,   282,   283,   693,   284,   285,   690,   691,   286,   287,
     698,   699,   700,   701,   835,   836,   288,   604,   289,   290,
     703,   704,   291,   292,   179,   180,   673,   293,   183,   798,
     396,   397,   294,   295,   296,   297,   298,   299,   739,   740,
     741,   742,   300,   301,   302,   621,   622,   975,   976,   852,
     853,   972,   973,   854,  1107,   758,   591,   592,   599,   600,
     342,  1264,  1180,   829,   594,   595,   303,   759,   760,   746,
     747,   748,   749,   855,   751,   674,   675,   676,   754,   755,
     304,   677,   537,   538,   185,   306,   962,   565,   678,   679,
     506,   680,   507,   681,   560,   561,   821,   958,   562,   682,
     683,   307,   308,   684,   191,   390,   192,   401,   193,   406,
     194,   412,   195,   425,   196,   433,   197,   443,   198,   452,
     199,   458,   200,   461,   201,   465,   202,   470,   203,   475,
     204,   487,   811,   954,   205,   491,   206,   496,   207,   208,
     515,   209,   508,   210,   510,   211,   512,   212,   522,   213,
     525,   214,   531,   215,   574
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,   772,    49,   771,   625,   181,    40,   320,   770,   773,
     566,   224,   779,   184,   850,   856,   576,   750,   745,   182,
     694,   567,   982,  1079,  1081,  1083,   181,   750,   750,   186,
     857,   305,  1120,  1082,   184,   181,  1110,   720,   912,    50,
     305,   234,   720,   184,   702,  1119,   970,  1172,   187,   310,
     186,  1087,  1089,   313,   321,   264,   987,  1165,  1245,   186,
     347,   500,   347,   347,   316,   188,   347,   347,    57,   187,
     347,   876,   189,   347,   347,   347,   820,  1099,   187,   795,
     347,   347,   877,  1132,  1133,   822,   188,    63,   347,  1149,
     984,   986,  1099,   189,  1291,   188,   988,   878,    51,   126,
     127,   128,   189,   966,   126,   127,   128,  1204,  1205,   710,
    1093,    75,   190,  1150,  1151,  1103,    52,    53,    54,     3,
     843,   844,     4,   846,     5,   848,   820,  1262,    60,    61,
     863,   334,  1263,   309,   539,   841,   391,   392,  1192,   504,
     505,   216,   309,   712,     6,     7,     8,     9,   880,   222,
     181,   882,  1026,   235,   181,   236,  1292,   890,   184,   864,
       3,   685,   184,     4,   859,     5,  1202,   317,   796,   797,
     228,  1079,   869,   865,   186,  1094,   873,  1231,   186,  1101,
    1104,   327,   328,   329,  1152,     6,     7,     8,     9,  1246,
    1247,   891,   121,   187,   338,   339,   340,   187,   577,  1241,
     899,   879,  1153,   900,   579,   692,  1099,   353,   354,   866,
     188,   513,   359,  1175,   188,  1268,  1119,   189,   225,   488,
    1223,   189,   710,   393,   394,  1226,   752,   395,   514,   380,
     381,   539,   389,   384,   523,   967,   752,   752,   711,   341,
     623,   357,   358,  -310,   181,     3,   237,  1227,     4,   305,
       5,   524,   184,   361,   867,     3,   712,   190,     4,   615,
       5,   190,   489,   490,   928,   929,  1219,  1001,   186,   311,
       6,     7,     8,     9,  1010,   320,   596,   597,   613,   738,
       6,     7,     8,     9,   575,   492,   320,   187,   904,   738,
     738,   263,   913,   614,   175,   743,     4,  -129,     5,   175,
    1210,   858,   181,  1121,   188,   743,   743,   305,   493,   494,
     184,   189,   181,   459,  1249,  1251,   312,   305,   263,  1176,
     184,   175,   321,  1250,  1004,   630,   186,   460,   233,   347,
     563,   768,     4,   321,     5,  -142,   186,   495,   589,  1079,
     564,   778,   686,   687,   688,   187,  1193,   977,   978,   330,
     980,   309,   605,   606,   941,   187,   607,  1030,  1031,  1197,
     942,     4,   188,     5,  1225,   217,   218,   219,   341,   189,
     383,   471,   188,   217,   218,   219,   509,   231,   232,   189,
    1109,   991,   850,   856,   992,   511,   686,   687,   688,   999,
     922,   596,   597,   568,   472,   473,  1177,   474,  1157,  1158,
    1014,  1159,   578,   923,  1019,   924,  1021,   961,   893,   309,
    1088,   331,   332,   333,   631,   632,   633,   634,   635,   309,
     850,   856,   498,   462,   343,   344,   345,     3,   590,   915,
       4,   466,     5,   463,   464,   467,   500,  1277,   501,   593,
    1216,   363,   837,  1210,  1149,   370,   371,   888,   372,   889,
     497,   377,     6,     7,     8,     9,   566,     3,   468,   469,
       4,   498,     5,   499,   596,   597,  1248,   849,  1150,  1151,
     590,   782,   927,   601,   593,   500,   612,   501,  1142,  1143,
     502,   617,     6,     7,     8,     9,   113,  1102,   114,  1163,
     923,  1106,   924,   115,   792,   116,   619,   791,   117,  1060,
    1061,  1062,  1063,  1064,   602,   603,  1065,   402,  1115,   403,
     404,   405,   350,   352,   504,   505,   355,   356,   626,   627,
     360,  1066,  1273,   365,   367,   369,   503,   398,   399,   400,
     374,   376,  1269,   618,   118,   119,   623,     3,   382,  1152,
       4,   638,     5,   516,   580,   752,   581,   702,   582,   583,
     911,  1175,   707,   504,   505,   584,   585,  1153,   517,   526,
     708,  1067,     6,     7,     8,     9,   705,   706,   588,   828,
     709,   518,   527,  1238,   756,     3,   762,   519,     4,   528,
       5,     4,   181,     5,  1212,   757,   586,   763,  1239,   529,
     184,   850,   856,  1240,   764,   530,   181,   766,   738,   765,
       6,     7,     8,     9,   184,   784,   186,   831,   832,  1060,
    1061,  1062,  1063,  1064,   851,   793,  1065,   217,   218,   219,
     186,   520,   521,    51,   108,   187,   386,   387,   388,   109,
     110,  1066,  1029,   813,   434,   435,  1022,   752,  1035,   187,
    1037,  1038,   188,  1039,   111,   883,   884,   351,   436,   189,
     437,   438,   439,   695,   696,   697,   188,  1176,   126,   127,
     128,    16,    17,   189,   794,   440,   441,   442,   569,  1175,
     774,  1067,   825,   570,   571,   823,   974,   572,   573,   824,
     752,   826,   780,   181,   181,   181,   181,   181,   181,   190,
     738,   184,   184,   184,   184,   184,   184,   906,   907,   917,
     918,  1108,   785,   190,  1068,    31,   743,   186,   186,   186,
     186,   186,   186,  1100,    32,   426,   830,   427,   956,   957,
      33,  1181,  1182,  1183,  1184,  1185,   187,   187,   187,   187,
     187,   187,   834,   738,  1218,   428,    34,   429,   430,   431,
     432,   839,   974,   188,   188,   188,   188,   188,   188,   743,
     189,   189,   189,   189,   189,   189,  1116,   930,  1117,   840,
     931,   838,  1118,   686,   687,   688,   842,   672,   885,    77,
     847,    78,   860,    79,   753,  1176,    80,    81,    82,   783,
     619,   985,   696,   697,   753,   753,  1135,  1136,   861,   737,
     190,   190,   190,   190,   190,   190,  1145,  1146,   870,   737,
     737,   871,  1200,  1017,  1018,    56,  1199,  1201,   453,   752,
     886,   903,   872,    65,  1170,    66,   181,  1209,   454,   887,
      67,    68,    69,   892,   184,   455,  -656,  -657,   919,   389,
     894,   456,   457,   895,   896,   897,   921,  1215,   902,   916,
     186,   752,   752,   752,   752,   752,   752,   752,   920,   752,
     752,   752,  1287,     3,   364,   925,     4,   323,     5,   187,
     326,   936,   738,   407,   408,   409,   410,   411,    16,    17,
     937,   938,   336,   323,   939,   940,   188,   944,     6,     7,
       8,     9,   181,   189,   349,  1013,   955,   959,   960,   961,
     184,   964,   963,   965,   738,   738,   738,   738,   738,   738,
     738,   710,   738,   738,   738,   979,   186,   983,   379,   981,
     752,   181,    31,   752,   997,   385,   305,   990,  1000,   184,
     743,    32,   995,   190,  1008,   187,  1072,    33,  1073,  1064,
     996,  1049,  1065,  1069,  1077,   186,    83,  1050,   998,  1070,
    1078,  1036,   188,    34,  1084,  1085,  1086,  1074,  1090,   189,
      84,   752,  1092,   181,   187,  1095,  1097,  1111,   305,  1112,
    1122,   184,  1113,   738,  1114,    85,   738,  1128,  1129,  1138,
      86,   188,  1144,  1148,  1164,  1173,   366,   186,   189,  1174,
      70,  1187,   851,  1189,  1190,  1195,  1196,  1075,  1206,   190,
      16,    17,   946,  1220,    71,  1224,   187,  1243,  1228,  1235,
    1229,  1230,   181,     3,   738,  1256,     4,   305,     5,    72,
     184,  1232,  1233,   188,    73,  1234,  1252,  1281,   309,  1282,
     189,  1025,    62,   947,  1295,  1080,   186,   769,     6,     7,
       8,     9,  1166,  1237,    31,  1236,   624,  1040,  1127,   337,
     368,  1198,  1041,    32,  1042,   187,   862,  1194,   616,    33,
    1134,   875,  1105,   845,    16,    17,  1139,  1140,  1141,   181,
     309,  1191,   188,  1005,   305,    34,  1006,   184,  1007,   189,
    1162,   948,   949,   950,   951,   952,   953,  1009,  1167,  1049,
    1020,  1069,  1077,   186,   901,  1050,  1023,  1070,  1078,   945,
    1178,   320,   908,   753,   905,   909,  1179,   910,    31,   989,
     672,   672,   187,   672,  1024,   672,   373,    32,   737,   309,
     761,   320,  1272,    33,   775,  1280,   362,   777,  1276,   188,
      16,    17,   752,   444,  1032,   445,   189,  1033,   672,    34,
    1076,   672,   776,   609,   744,   812,  1034,  1043,   321,   610,
       0,  1207,  1208,   446,     0,   447,   448,  1221,   449,  1123,
    1125,  1125,   611,     0,  1211,     0,   450,   451,   321,  1213,
       0,     0,  1214,     0,    31,  1217,   309,     0,     0,     0,
       0,  1178,     0,    32,     0,   738,  1222,  1179,     0,    33,
     672,     0,     0,   672,     0,   753,   240,   241,   242,   243,
     244,   245,     0,   814,   815,    34,     0,     0,     0,     0,
     737,     0,  1044,     0,   375,     0,   498,     0,     0,     0,
       0,     0,     0,     0,   816,     0,  1045,  1242,    16,    17,
    1244,     0,   501,     0,     0,    16,    17,   181,   753,     0,
       0,  1046,   305,     0,     0,   184,  1047,  1258,  1259,  1260,
    1261,     0,     0,   737,   672,   672,     0,     0,     0,  1069,
    1077,   186,  1270,  1274,  1278,  1070,  1078,     0,  1271,  1275,
    1279,     0,    31,  1283,  1284,  1285,  1286,  1178,  1288,    31,
     187,    32,  1289,  1179,     0,     0,  1290,    33,    32,     0,
    1048,     0,     0,     0,    33,     0,  1294,   188,     0,     0,
       0,     0,     0,    34,   189,     0,     0,     0,     0,     0,
      34,   817,   818,   819,   547,     0,     0,     0,     0,     0,
       3,     0,     0,     4,     0,     5,   557,   558,   559,     0,
       0,     0,     0,   969,     0,     0,     0,   672,   672,     0,
     672,     0,     0,     0,   309,     6,     7,     8,     9,     0,
       0,     0,     0,     0,  1040,     0,     0,     0,     0,  1041,
       0,  1042,     0,     0,     0,     0,  1003,   753,  1003,  1003,
    1003,     0,  1003,  1003,     0,     0,     0,  1016,  1016,   672,
       0,  1002,   737,  1002,  1002,  1002,     0,  1002,  1002,  1012,
     672,     0,  1015,  1015,   672,     0,   672,   720,     0,   753,
     753,   753,   753,   753,   753,   753,     0,   753,   753,   753,
       0,     0,     0,     0,   737,   737,   737,   737,   737,   737,
     737,     0,   737,   737,   737,    46,     0,     0,     0,     0,
     642,     0,     0,     0,    55,    46,    46,    58,    58,    58,
     799,     0,    46,   800,   801,   802,   803,   804,   805,   806,
     807,   808,   809,   810,  1043,     0,     0,     0,     0,   126,
     127,   128,     0,     0,     0,     0,   721,     0,   753,     0,
     722,   753,     0,     0,   723,     0,     0,   672,     0,     0,
     724,   672,     0,   737,   648,     0,   737,    46,     0,   325,
      46,    58,    58,    58,     0,     0,   726,     0,   672,    46,
       0,   335,    46,    46,    58,    58,    58,     0,     0,   753,
       0,     0,   346,     0,    46,     0,     0,    58,    58,  1044,
       0,     0,    58,     0,   737,     0,     0,     0,     0,     3,
       0,     0,     4,  1045,     5,     0,     0,   378,    46,    58,
      58,     0,     0,    58,     0,    46,     0,     0,  1046,     0,
       0,     0,     0,  1047,     6,     7,     8,     9,     0,   413,
     414,     0,     0,   415,     0,     0,     0,     3,     0,     0,
       4,     0,     5,   416,   417,   418,   419,   420,   421,   422,
     423,   424,     0,   651,     0,     0,   652,   653,     0,   123,
       0,     0,     6,     7,     8,     9,   124,  1168,     0,     0,
       0,  1060,  1061,  1062,  1063,  1064,   239,     0,  1065,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   654,   655,  1066,     0,     0,     0,     0,     0,     0,
     240,   241,   242,   243,   244,   245,     0,     0,     0,     0,
       0,     0,     0,  1052,     0,     0,     0,   246,   247,     0,
     125,   126,   127,   128,   175,     0,     0,     0,   129,     0,
       0,  1053,   130,  1067,     0,     0,   131,     0,     0,     0,
       0,     0,   132,     0,     0,     0,     0,     0,     0,     0,
     753,     0,   133,     0,     0,     0,     0,     0,   134,   476,
       0,     0,   477,   135,     0,   737,   136,     0,     0,   137,
     138,     0,     0,   139,     0,   478,   140,     0,   141,   479,
       0,     0,   480,   481,     0,     0,     0,   482,   483,   484,
     485,   486,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   142,   143,     0,   144,   145,   146,     0,     0,   147,
     148,     0,     0,   149,   150,   248,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,     0,     0,   249,     0,     0,     0,
       0,     0,     0,     0,     0,   781,     0,     0,     0,     0,
     250,    58,     0,     0,     0,     0,     0,     0,   786,   251,
     787,     0,   788,     0,     0,   252,     0,   789,     0,   790,
     253,     0,     0,     0,     0,     0,  1266,    58,     0,     0,
     254,     0,     0,   255,   256,   257,   258,     0,     0,     0,
     259,     0,     0,     0,   260,   261,   171,     0,     0,     3,
     172,   173,     4,     0,     5,     0,     0,     0,   262,     0,
       0,   174,     0,   263,  1054,     0,   175,   176,     0,     0,
       0,   123,     0,     0,     6,     7,     8,     9,   124,     0,
       0,     0,     0,    10,     0,    11,     0,    12,   239,     0,
      13,    14,    15,     0,     0,     0,     0,    16,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   240,   241,   242,   243,   244,   245,     0,     0,
       0,     0,     0,     0,     0,  1052,     0,     0,     0,   246,
     247,     0,   125,   126,   127,   128,     0,     0,     0,     0,
     129,    31,     0,  1053,   130,     0,     0,     0,   131,     0,
      32,     0,     0,     0,   132,     0,    33,     0,     0,     0,
       0,     0,     0,     0,   133,     0,     0,     0,     0,     0,
     134,     0,    34,     0,     0,   135,     0,     0,   136,     0,
       0,   137,   138,     0,     3,   139,     0,     4,   140,     5,
     141,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       7,     8,     9,   142,   143,     0,   144,   145,   146,     0,
       0,   147,   148,     0,     0,   149,   150,   248,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,     0,     0,   249,     0,
      35,     0,     0,     0,     0,     0,     0,  1072,     0,  1073,
    1064,   532,   250,  1065,    36,     0,     0,     0,     0,     0,
       0,   251,     0,     0,     0,     0,     0,   252,  1074,    37,
       0,     0,   253,     0,    38,     0,     0,   533,     0,     0,
     534,     0,   254,     0,     0,   255,   256,   257,   258,   535,
       0,     0,   259,     0,     0,     0,   260,   261,   171,     0,
       0,     3,   172,   173,     4,     0,     5,     0,  1075,     0,
     262,     0,     0,   174,     0,   263,  1169,     0,   175,   176,
       0,     0,     0,   123,     0,     0,     6,     7,     8,     9,
     124,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     239,     0,     0,     0,     0,     0,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   240,   241,   242,   243,   244,   245,
       0,     0,     0,     0,     0,     0,     0,  1052,     0,     0,
       0,   246,   247,     0,   125,   126,   127,   128,     0,     0,
       0,     0,   129,     0,     0,  1053,   130,     0,     0,     0,
     131,     0,     0,     0,     0,     0,   132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,   536,   943,     0,
       0,     0,   134,     0,     0,     0,     0,   135,     0,     0,
     136,     0,     0,   137,   138,     0,     3,   139,     0,     4,
     140,     5,   141,     0,     0,     0,     0,     0,     0,     0,
       0,  1171,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     7,     8,     9,   142,   143,     0,   144,   145,
     146,     0,     0,   147,   148,     0,     0,   149,   150,   248,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,     0,     0,
     249,     0,     0,     0,   640,     0,     0,     0,     0,  1072,
       0,  1073,  1064,     0,   250,  1065,     0,     0,     0,     0,
     641,     0,   123,   251,     0,     0,     0,     0,     0,   252,
    1074,     0,     0,     0,   253,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   254,     0,     0,   255,   256,   257,
     258,     0,     0,     0,   259,   642,     0,     0,   260,   261,
     171,     0,     0,     0,   172,   173,     0,     0,     0,   643,
    1075,     0,   262,     0,     0,   174,     0,   263,  1265,     0,
     175,   176,     0,   125,   126,   127,   128,     0,     0,     0,
       0,   644,     0,     0,     0,   645,     0,     0,     0,   646,
       0,     0,     0,     0,     0,   647,     0,     0,     0,   648,
       0,     0,     0,     0,     0,   133,     0,     0,     0,     0,
       0,   649,     0,     0,     0,   608,   135,     0,     0,   136,
       0,     0,   137,   138,     0,     0,   139,     0,     0,   140,
       0,   141,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   533,     0,     0,   534,     0,     0,     0,     0,     0,
       0,     0,     0,   535,   142,   143,     0,   650,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,     0,     0,   170,
       0,   881,     0,     0,     0,     0,     0,     0,   651,     0,
       0,   652,   653,  1267,     0,     0,     0,   641,     0,   123,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,     0,     0,
       0,     0,     0,     0,     0,     0,   654,   655,     0,     0,
       0,     0,   642,     0,     0,     0,     0,     0,     0,   171,
       0,     0,     0,   172,   173,     0,     0,     0,     0,     0,
       0,     0,   656,   657,     0,     0,     0,     0,     0,   175,
     125,   126,   127,   128,     0,     0,     0,     0,   644,     0,
       0,   536,   645,     0,     0,     0,   646,     0,     0,     0,
       0,     0,   647,     0,     0,     0,   648,     0,     0,     0,
     540,   541,   133,     0,     0,     0,     0,     0,   649,     0,
       0,     0,     0,   135,     0,     0,   136,     0,     0,   137,
     138,   542,     0,   139,     0,     0,   140,     0,   141,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   142,   143,     0,   650,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,     0,     0,   170,   543,   898,     0,
       0,     0,     0,     0,     0,   651,     0,     0,   652,   653,
       0,     0,     0,     0,   641,     0,   123,     0,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,     0,     0,   557,   558,   559,     0,     0,     0,     0,
       0,     0,     0,   654,   655,     0,     0,     0,     0,   642,
       0,     0,     0,     0,     0,     0,   171,     0,     0,     0,
     172,   173,     0,     0,     0,     0,     0,     0,     0,   656,
     657,     0,     0,     0,     0,     0,   175,   125,   126,   127,
     128,     0,     0,     0,     0,   644,     0,     0,     0,   645,
       0,     0,     0,   646,     0,     0,     0,     0,     0,   647,
       0,     0,     0,   648,     0,     0,     0,     0,     0,   133,
       0,     0,     0,     0,     0,   649,     0,     0,     0,     0,
     135,     0,     0,   136,     0,     0,   137,   138,     0,     0,
     139,     0,     0,   140,     0,   141,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   142,   143,
       0,   650,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,     0,     0,   170,     0,     0,     0,     0,     0,     0,
       0,     0,   651,     0,     0,   652,   653,   713,   714,   715,
     716,   717,   718,     0,     0,     0,     0,     0,     0,   719,
       0,   720,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     654,   655,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   171,   642,     0,     0,   172,   173,     0,
       0,     0,     0,     0,     0,     0,   656,   657,     0,     0,
       0,     0,     0,   175,     0,     0,     0,     0,     0,     0,
       0,     0,   125,   126,   127,   128,     0,     0,     0,     0,
     721,     0,     0,     0,   722,     0,     0,     0,   723,     0,
       0,     0,     0,     0,   724,     0,     0,   719,   648,   720,
       0,     0,     0,     0,   725,     0,     0,     0,     0,     0,
     726,     0,     0,     0,     0,   727,     0,     0,   728,     0,
       0,   729,   730,     0,     0,   731,     0,     0,   732,     0,
     733,     0,   642,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   734,   735,     0,     0,     0,     0,     0,
     125,   126,   127,   128,     0,     0,     0,     0,   721,     0,
       0,     0,   722,     0,     0,     0,   723,     0,     0,     0,
       0,     0,   724,     0,     0,     0,   648,     0,     0,     0,
       0,     0,   725,     0,     0,     0,     0,   651,   726,     0,
     652,   653,     0,   727,     0,     0,   728,     0,     0,   729,
     730,     0,     0,   731,     0,     0,   732,     0,   733,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   654,   655,     0,   736,     0,
       0,   734,   735,     0,     0,     0,   641,     0,   123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   656,   657,     0,     0,   263,     0,     0,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   642,     0,     0,     0,   651,     0,     0,   652,   653,
      88,    89,    90,    91,     0,     0,    92,    93,     0,    94,
      95,     0,    96,     0,     0,     0,     0,     0,     0,   125,
     126,   127,   128,     0,     0,     0,     0,   644,     0,     0,
       0,   645,     0,   654,   655,   646,   736,     0,     0,     0,
       0,   647,     0,     0,     0,   648,     0,     0,    97,    98,
      99,   133,     0,     0,     0,     0,     0,   649,     0,   656,
     657,     0,   135,   263,     0,   136,   175,   926,   137,   138,
       0,     0,   139,     0,     0,   140,     0,   141,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     142,   143,     0,   650,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,     0,     0,   170,     0,     0,     0,   719,
       0,   720,     0,     0,   651,     0,     0,   652,   653,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,     0,     0,
       0,     0,     0,     0,   642,     0,     0,     0,     0,     0,
       0,   101,   654,   655,     0,     0,   102,   103,   104,     0,
       0,     0,     0,     0,     0,   171,   105,     0,     0,   172,
     173,   106,   125,   126,   127,   128,     0,     0,   656,   657,
     721,     0,     0,     0,   722,   175,     0,     0,   723,     0,
       0,     0,     0,     0,   724,     0,     0,   719,   648,   720,
       0,     0,     0,     0,   725,     0,     0,     0,     0,     0,
     726,     0,     0,     0,     0,   727,     0,     0,   728,     0,
       0,   729,   730,     0,     0,   731,     0,     0,   732,     0,
     733,     0,   642,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   734,   735,     0,     0,     0,     0,     0,
     125,   126,   127,   128,     0,     0,     0,     0,   721,     0,
       0,     0,   722,     0,     0,     0,   723,     0,     0,     0,
       0,     0,   724,     0,     0,     0,   648,     0,     0,     0,
       0,     0,   725,     0,     0,     0,     0,   651,   726,     0,
     652,   653,     0,   727,     0,     0,   728,     0,     0,   729,
     730,     0,     0,   731,     0,     0,   732,     0,   733,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   654,   655,     0,   736,     0,
       0,   734,   735,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   656,   657,     0,     0,   263,     0,     0,   175,   123,
       0,     0,     0,     0,     0,     0,   124,     0,     0,     0,
       0,     0,     0,     0,     0,   651,   239,     0,   652,   653,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     240,   241,   242,   243,   244,   245,     0,     0,     0,     0,
       0,     0,     0,   654,   655,     0,   736,   246,   247,     0,
     125,   126,   127,   128,     0,     0,     0,     0,   129,     0,
       0,     0,   130,     0,     0,     0,   131,     0,     0,   656,
     657,     0,   132,     0,     0,     0,   175,     0,     0,     0,
       0,     0,   133,     0,     0,     0,     0,     0,   134,     0,
       0,     0,     0,   135,     0,     0,   136,     0,     0,   137,
     138,     0,     0,   139,     0,     0,   140,     0,   141,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   142,   143,     0,   144,   145,   146,     0,     0,   147,
     148,     0,     0,   149,   150,   248,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,     0,     0,   249,     0,     0,     0,
       0,   123,     0,     0,     0,     0,     0,     0,   124,     0,
     250,     0,     0,     0,     0,     0,     0,     0,     0,   251,
       0,     0,     0,     0,     0,   252,     0,     0,     0,     0,
     253,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     254,     0,     0,   255,   256,   257,   258,     0,     0,     0,
     259,     0,     0,     0,   260,   261,   171,     0,     0,     0,
     172,   173,   125,   126,   127,   128,     0,     0,   262,     0,
     129,   174,     0,   263,   130,     0,   175,   176,   131,     0,
       0,     0,     0,     0,   132,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,     0,     0,     0,     0,     0,
     134,     0,     0,     0,     0,   135,     0,     0,   136,     0,
       0,   137,   138,     0,     0,   139,     0,     0,   140,     0,
     141,     0,   123,     0,     0,     0,     0,     0,     0,   124,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   142,   143,     0,   144,   145,   146,     0,
       0,   147,   148,     0,     0,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,     0,     0,   170,     0,
       0,     0,     0,   125,   126,   127,   128,     0,     0,     0,
       0,   129,     0,     0,     0,   130,     0,     0,     0,   131,
       0,     0,     0,     0,     0,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,     0,     0,     0,     0,
       0,   134,     0,     0,     0,     0,   135,     0,     0,   136,
       0,     0,   137,   138,     0,     0,   139,     0,   171,   140,
       0,   141,   172,   173,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   174,     0,   263,     0,     0,   175,   176,
       0,     0,     0,     0,   142,   143,     0,   144,   145,   146,
       0,     0,   147,   148,   123,     0,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,     0,     0,   170,
       0,     0,     0,     0,     0,     0,     0,   642,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   125,   126,   127,   128,     0,
       0,     0,     0,   644,     0,     0,     0,   645,     0,     0,
       0,   646,     0,     0,     0,     0,     0,   647,     0,   171,
       0,   648,     0,   172,   173,     0,     0,   133,     0,     0,
       0,     0,     0,   649,   174,     0,     0,     0,   135,   175,
     176,   136,     0,     0,   137,   138,     0,     0,   139,     0,
       0,   140,     0,   141,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   142,   143,     0,   650,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,     0,
       0,   170,     0,     0,     0,     0,     0,     0,     0,   720,
     651,     0,     0,   652,   653,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   642,     0,     0,     0,     0,     0,   654,   655,
     240,   241,   242,   243,   244,   245,     0,     0,     0,     0,
       0,   171,     0,     0,     0,   172,   173,     0,     0,     0,
     125,   126,   127,   128,   656,   657,     0,     0,   721,     0,
       0,   175,   722,     0,     0,     0,   723,     0,     0,     0,
       0,     0,   724,     0,     0,     0,   648,   720,     0,     0,
       0,     0,   725,     0,     0,     0,     0,     0,   726,     0,
       0,     0,     0,   727,     0,     0,   728,     0,     0,   729,
     730,     0,     0,   731,     0,     0,   732,     0,   733,     0,
     642,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   734,   735,     0,     0,     0,     0,     0,   125,   126,
     127,   128,     0,     0,     0,     0,   721,     0,     0,     0,
     722,     0,     0,     0,   723,     0,     0,     0,     0,     0,
     724,     0,     0,     0,   648,     0,     0,     0,     0,     0,
     725,     0,     0,     0,     0,   651,   726,     0,   652,   653,
       0,   727,     0,     0,   728,     0,     0,   729,   730,     0,
       0,   731,     0,     0,   732,     0,   733,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   654,   655,     0,   736,     0,     0,   734,
     735,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   656,
     657,     0,     0,     0,     0,     0,   175,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       0,     0,     4,   651,     5,     0,   652,   653,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     7,     8,     9,     0,     0,
       0,    10,     0,    11,     0,    12,     0,     0,    13,    14,
      15,   654,   655,     0,   736,    16,    17,    18,     0,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     0,     0,     0,     0,     0,     0,   656,   657,     0,
       0,     0,     0,     0,   175,     0,     0,     0,     0,     0,
       0,     0,     0,  -221,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,    32,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,     0,    38
};

static const yytype_int16 yycheck[] =
{
       1,   328,     3,   327,   266,    27,     1,    60,   326,   329,
     172,    29,   339,    27,   620,   620,   176,   301,   301,    27,
     283,   172,   847,   935,   938,   940,    48,   311,   312,    27,
       7,    48,     7,   939,    48,    57,   985,    23,    23,    86,
      57,    42,    23,    57,    33,  1026,    74,  1084,    27,    50,
      48,   959,   960,    54,    60,    48,   853,  1074,    85,    57,
      89,   120,    91,    92,    57,    27,    95,    96,    12,    48,
      99,   116,    27,   102,   103,   104,   560,   972,    57,    95,
     109,   110,   127,  1046,  1047,   560,    48,    37,   117,    85,
     851,   852,   987,    48,    22,    57,   857,   142,    85,    85,
      86,    87,    57,    85,    85,    86,    87,  1132,  1133,     8,
      20,    37,    27,   109,   110,    20,     7,     8,     9,     1,
     612,   613,     4,   615,     6,   617,   610,   137,    14,    15,
      63,    75,   142,    48,   151,   610,    93,    94,  1104,   198,
     199,    45,    57,    42,    26,    27,    28,    29,   640,    45,
     172,   643,   913,    44,   176,    46,    84,     8,   172,    92,
       1,    70,   176,     4,   623,     6,  1129,    58,   184,   185,
     208,  1083,   631,   106,   172,    85,   635,  1202,   176,   976,
      85,    67,    68,    69,   180,    26,    27,    28,    29,   216,
     217,    42,    35,   172,    80,    81,    82,   176,   216,  1216,
     692,   246,   198,   695,   222,    70,  1101,    93,    94,   142,
     172,   108,    98,    95,   176,  1252,  1197,   172,    85,    95,
    1186,   176,     8,   180,   181,  1191,   301,   184,   125,   115,
     116,   248,   123,   119,   108,   217,   311,   312,    24,   208,
     268,    33,    34,    84,   266,     1,   267,  1196,     4,   266,
       6,   125,   266,   222,   187,     1,    42,   172,     4,   215,
       6,   176,   138,   139,   756,   757,  1174,   883,   266,   276,
      26,    27,    28,    29,   890,   328,   232,   233,   215,   301,
      26,    27,    28,    29,   175,   115,   339,   266,   277,   311,
     312,   277,   277,   230,   280,   301,     4,   277,     6,   280,
       8,   278,   324,   278,   266,   311,   312,   324,   138,   139,
     324,   266,   334,   118,  1228,  1230,   276,   334,   277,   201,
     334,   280,   328,  1229,   884,   135,   324,   132,     0,   358,
     251,   324,     4,   339,     6,   277,   334,   167,   229,  1251,
     261,   334,   251,   252,   253,   324,  1107,   839,   840,   208,
     842,   266,   243,   244,   774,   334,   247,   917,   918,  1120,
     780,     4,   324,     6,  1189,   269,   270,   271,   208,   324,
      33,   115,   334,   269,   270,   271,   172,    37,    38,   334,
     985,   118,   988,   988,   121,   172,   251,   252,   253,   881,
       7,   232,   233,   262,   138,   139,   278,   141,    71,    72,
     892,    74,   270,    20,   896,    22,   898,   263,   671,   324,
     266,    71,    72,    73,   224,   225,   226,   227,   228,   334,
    1026,  1026,   106,   125,    84,    85,    86,     1,   216,   712,
       4,   111,     6,   135,   136,   115,   120,   278,   122,   230,
       5,   101,   604,     8,    85,   105,   106,    20,   108,    22,
      95,   111,    26,    27,    28,    29,   618,     1,   138,   139,
       4,   106,     6,   108,   232,   233,  1227,   618,   109,   110,
     216,   357,   755,    84,   230,   120,   215,   122,  1061,  1062,
     125,    70,    26,    27,    28,    29,    33,   979,    35,  1072,
      20,   983,    22,    40,   385,    42,     4,   383,    45,    73,
      74,    75,    76,    77,    49,    50,    80,    95,  1000,    97,
      98,    99,    91,    92,   198,   199,    95,    96,   216,   217,
      99,    95,   278,   102,   103,   104,   171,    93,    94,    95,
     109,   110,   278,    70,    81,    82,   268,     1,   117,   180,
       4,   245,     6,    97,    34,   620,    36,    33,    38,    39,
     710,    95,    17,   198,   199,    45,    46,   198,   112,    95,
      18,   135,    26,    27,    28,    29,    15,    16,   228,   587,
     279,   125,   108,   214,    40,     1,   277,   131,     4,   115,
       6,     4,   604,     6,     7,    40,    76,   277,   229,   125,
     604,  1197,  1197,   234,   277,   131,   618,    44,   620,   277,
      26,    27,    28,    29,   618,    33,   604,   232,   233,    73,
      74,    75,    76,    77,   620,     7,    80,   269,   270,   271,
     618,   175,   176,    85,   214,   604,    88,    89,    90,   219,
     220,    95,   916,   283,    93,    94,   899,   712,   922,   618,
     924,   925,   604,   926,   234,    15,    16,    33,   107,   604,
     109,   110,   111,   255,   256,   257,   618,   201,    85,    86,
      87,    47,    48,   618,     8,   124,   125,   126,   168,    95,
     330,   135,    84,   173,   174,   262,   838,   177,   178,   262,
     755,   282,   342,   705,   706,   707,   708,   709,   710,   604,
     712,   705,   706,   707,   708,   709,   710,   705,   706,    15,
      16,   985,   362,   618,   278,    91,   712,   705,   706,   707,
     708,   709,   710,   975,   100,    95,    84,    97,    93,    94,
     106,   239,   240,   241,   242,   243,   705,   706,   707,   708,
     709,   710,    84,   755,   278,   115,   122,   117,   118,   119,
     120,    40,   904,   705,   706,   707,   708,   709,   710,   755,
     705,   706,   707,   708,   709,   710,  1019,   758,  1021,    40,
     761,   277,  1024,   251,   252,   253,    40,   279,    17,    33,
      84,    35,    84,    37,   301,   201,    40,    41,    42,   358,
       4,     5,   256,   257,   311,   312,    64,    65,    84,   301,
     705,   706,   707,   708,   709,   710,    78,    79,    84,   311,
     312,    84,  1126,   894,   895,    11,  1124,  1127,   108,   884,
      18,   702,    84,    33,   278,    35,   838,  1144,   118,   279,
      40,    41,    42,     5,   838,   125,     7,     7,    17,   720,
       7,   131,   132,     7,     5,     7,   279,  1164,     7,     7,
     838,   916,   917,   918,   919,   920,   921,   922,    18,   924,
     925,   926,   278,     1,    33,     8,     4,    63,     6,   838,
      66,    84,   884,   101,   102,   103,   104,   105,    47,    48,
     277,   277,    78,    79,   277,   277,   838,    84,    26,    27,
      28,    29,   904,   838,    90,   891,    84,    84,    84,   263,
     904,   217,   277,    84,   916,   917,   918,   919,   920,   921,
     922,     8,   924,   925,   926,    40,   904,    32,   114,    84,
     985,   933,    91,   988,    56,   121,   933,   121,     5,   933,
     926,   100,    95,   838,    84,   904,    74,   106,    76,    77,
      95,   932,    80,   934,   935,   933,   200,   932,    95,   934,
     935,    84,   904,   122,   277,     7,   284,    95,    84,   904,
     214,  1026,    84,   975,   933,   235,    85,     7,   975,    85,
     282,   975,    85,   985,    85,   229,   988,    85,   208,    85,
     234,   933,   276,    84,   276,    84,    33,   975,   933,    84,
     200,   231,   988,    84,   278,   278,     5,   135,    31,   904,
      47,    48,    80,    86,   214,    84,   975,   114,   277,    85,
     277,   277,  1024,     1,  1026,    32,     4,  1024,     6,   229,
    1024,   277,   277,   975,   234,   277,   277,    85,   933,   123,
     975,   912,    18,   111,    84,   937,  1024,   325,    26,    27,
      28,    29,  1075,  1212,    91,  1210,   265,    35,  1042,    79,
      33,  1120,    40,   100,    42,  1024,   628,  1111,   253,   106,
    1051,   636,   982,   614,    47,    48,  1057,  1058,  1059,  1081,
     975,  1103,  1024,   885,  1081,   122,   886,  1081,   887,  1024,
    1071,   159,   160,   161,   162,   163,   164,   889,  1079,  1080,
     897,  1082,  1083,  1081,   698,  1080,   902,  1082,  1083,   794,
    1091,  1144,   707,   620,   703,   708,  1091,   709,    91,   857,
     612,   613,  1081,   615,   904,   617,    33,   100,   620,  1024,
     312,  1164,  1253,   106,   331,  1255,   100,   333,  1254,  1081,
      47,    48,  1197,    95,   919,    97,  1081,   920,   640,   122,
     278,   643,   332,   248,   301,   506,   921,   135,  1144,   249,
      -1,  1142,  1143,   115,    -1,   117,   118,  1176,   120,  1040,
    1041,  1042,   249,    -1,  1155,    -1,   128,   129,  1164,  1160,
      -1,    -1,  1163,    -1,    91,  1166,  1081,    -1,    -1,    -1,
      -1,  1172,    -1,   100,    -1,  1197,  1177,  1172,    -1,   106,
     692,    -1,    -1,   695,    -1,   712,    64,    65,    66,    67,
      68,    69,    -1,    93,    94,   122,    -1,    -1,    -1,    -1,
     712,    -1,   200,    -1,    33,    -1,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,   214,  1218,    47,    48,
    1221,    -1,   122,    -1,    -1,    47,    48,  1249,   755,    -1,
      -1,   229,  1249,    -1,    -1,  1249,   234,  1238,  1239,  1240,
    1241,    -1,    -1,   755,   756,   757,    -1,    -1,    -1,  1250,
    1251,  1249,  1253,  1254,  1255,  1250,  1251,    -1,  1253,  1254,
    1255,    -1,    91,  1264,  1265,  1266,  1267,  1268,  1269,    91,
    1249,   100,  1273,  1268,    -1,    -1,  1277,   106,   100,    -1,
     278,    -1,    -1,    -1,   106,    -1,  1287,  1249,    -1,    -1,
      -1,    -1,    -1,   122,  1249,    -1,    -1,    -1,    -1,    -1,
     122,   201,   202,   203,   204,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    -1,     4,    -1,     6,   216,   217,   218,    -1,
      -1,    -1,    -1,   835,    -1,    -1,    -1,   839,   840,    -1,
     842,    -1,    -1,    -1,  1249,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    40,
      -1,    42,    -1,    -1,    -1,    -1,   883,   884,   885,   886,
     887,    -1,   889,   890,    -1,    -1,    -1,   894,   895,   881,
      -1,   883,   884,   885,   886,   887,    -1,   889,   890,   891,
     892,    -1,   894,   895,   896,    -1,   898,    23,    -1,   916,
     917,   918,   919,   920,   921,   922,    -1,   924,   925,   926,
      -1,    -1,    -1,    -1,   916,   917,   918,   919,   920,   921,
     922,    -1,   924,   925,   926,     1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    10,    11,    12,    13,    14,    15,
     145,    -1,    18,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   135,    -1,    -1,    -1,    -1,    85,
      86,    87,    -1,    -1,    -1,    -1,    92,    -1,   985,    -1,
      96,   988,    -1,    -1,   100,    -1,    -1,   979,    -1,    -1,
     106,   983,    -1,   985,   110,    -1,   988,    63,    -1,    65,
      66,    67,    68,    69,    -1,    -1,   122,    -1,  1000,    75,
      -1,    77,    78,    79,    80,    81,    82,    -1,    -1,  1026,
      -1,    -1,    88,    -1,    90,    -1,    -1,    93,    94,   200,
      -1,    -1,    98,    -1,  1026,    -1,    -1,    -1,    -1,     1,
      -1,    -1,     4,   214,     6,    -1,    -1,   113,   114,   115,
     116,    -1,    -1,   119,    -1,   121,    -1,    -1,   229,    -1,
      -1,    -1,    -1,   234,    26,    27,    28,    29,    -1,    93,
      94,    -1,    -1,    97,    -1,    -1,    -1,     1,    -1,    -1,
       4,    -1,     6,   107,   108,   109,   110,   111,   112,   113,
     114,   115,    -1,   209,    -1,    -1,   212,   213,    -1,    23,
      -1,    -1,    26,    27,    28,    29,    30,   278,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    40,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   247,   248,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    82,    -1,
      84,    85,    86,    87,   280,    -1,    -1,    -1,    92,    -1,
      -1,    95,    96,   135,    -1,    -1,   100,    -1,    -1,    -1,
      -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1197,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,   115,
      -1,    -1,   118,   127,    -1,  1197,   130,    -1,    -1,   133,
     134,    -1,    -1,   137,    -1,   131,   140,    -1,   142,   135,
      -1,    -1,   138,   139,    -1,    -1,    -1,   143,   144,   145,
     146,   147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   165,   166,    -1,   168,   169,   170,    -1,    -1,   173,
     174,    -1,    -1,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,    -1,    -1,   200,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   351,    -1,    -1,    -1,    -1,
     214,   357,    -1,    -1,    -1,    -1,    -1,    -1,   364,   223,
     366,    -1,   368,    -1,    -1,   229,    -1,   373,    -1,   375,
     234,    -1,    -1,    -1,    -1,    -1,   278,   383,    -1,    -1,
     244,    -1,    -1,   247,   248,   249,   250,    -1,    -1,    -1,
     254,    -1,    -1,    -1,   258,   259,   260,    -1,    -1,     1,
     264,   265,     4,    -1,     6,    -1,    -1,    -1,   272,    -1,
      -1,   275,    -1,   277,   278,    -1,   280,   281,    -1,    -1,
      -1,    23,    -1,    -1,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,    33,    -1,    35,    -1,    37,    40,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,
      82,    -1,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      92,    91,    -1,    95,    96,    -1,    -1,    -1,   100,    -1,
     100,    -1,    -1,    -1,   106,    -1,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,
     122,    -1,   122,    -1,    -1,   127,    -1,    -1,   130,    -1,
      -1,   133,   134,    -1,     1,   137,    -1,     4,   140,     6,
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,   165,   166,    -1,   168,   169,   170,    -1,
      -1,   173,   174,    -1,    -1,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,    -1,    -1,   200,    -1,
     200,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    76,
      77,    85,   214,    80,   214,    -1,    -1,    -1,    -1,    -1,
      -1,   223,    -1,    -1,    -1,    -1,    -1,   229,    95,   229,
      -1,    -1,   234,    -1,   234,    -1,    -1,   111,    -1,    -1,
     114,    -1,   244,    -1,    -1,   247,   248,   249,   250,   123,
      -1,    -1,   254,    -1,    -1,    -1,   258,   259,   260,    -1,
      -1,     1,   264,   265,     4,    -1,     6,    -1,   135,    -1,
     272,    -1,    -1,   275,    -1,   277,   278,    -1,   280,   281,
      -1,    -1,    -1,    23,    -1,    -1,    26,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    81,    82,    -1,    84,    85,    86,    87,    -1,    -1,
      -1,    -1,    92,    -1,    -1,    95,    96,    -1,    -1,    -1,
     100,    -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   251,   784,    -1,
      -1,    -1,   122,    -1,    -1,    -1,    -1,   127,    -1,    -1,
     130,    -1,    -1,   133,   134,    -1,     1,   137,    -1,     4,
     140,     6,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   278,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,   165,   166,    -1,   168,   169,
     170,    -1,    -1,   173,   174,    -1,    -1,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,    -1,    -1,
     200,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    74,
      -1,    76,    77,    -1,   214,    80,    -1,    -1,    -1,    -1,
      21,    -1,    23,   223,    -1,    -1,    -1,    -1,    -1,   229,
      95,    -1,    -1,    -1,   234,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   244,    -1,    -1,   247,   248,   249,
     250,    -1,    -1,    -1,   254,    56,    -1,    -1,   258,   259,
     260,    -1,    -1,    -1,   264,   265,    -1,    -1,    -1,    70,
     135,    -1,   272,    -1,    -1,   275,    -1,   277,   278,    -1,
     280,   281,    -1,    84,    85,    86,    87,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    96,    -1,    -1,    -1,   100,
      -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,    -1,    85,   127,    -1,    -1,   130,
      -1,    -1,   133,   134,    -1,    -1,   137,    -1,    -1,   140,
      -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   111,    -1,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   123,   165,   166,    -1,   168,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,    -1,    -1,   200,
      -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,   209,    -1,
      -1,   212,   213,   278,    -1,    -1,    -1,    21,    -1,    23,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   247,   248,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,   260,
      -1,    -1,    -1,   264,   265,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   273,   274,    -1,    -1,    -1,    -1,    -1,   280,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    92,    -1,
      -1,   251,    96,    -1,    -1,    -1,   100,    -1,    -1,    -1,
      -1,    -1,   106,    -1,    -1,    -1,   110,    -1,    -1,    -1,
      93,    94,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,    -1,    -1,   127,    -1,    -1,   130,    -1,    -1,   133,
     134,   114,    -1,   137,    -1,    -1,   140,    -1,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   165,   166,    -1,   168,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,    -1,    -1,   200,   180,     5,    -1,
      -1,    -1,    -1,    -1,    -1,   209,    -1,    -1,   212,   213,
      -1,    -1,    -1,    -1,    21,    -1,    23,    -1,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,    -1,    -1,   216,   217,   218,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   247,   248,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,   260,    -1,    -1,    -1,
     264,   265,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   273,
     274,    -1,    -1,    -1,    -1,    -1,   280,    84,    85,    86,
      87,    -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,    96,
      -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,    -1,   106,
      -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,   116,
      -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,    -1,
     127,    -1,    -1,   130,    -1,    -1,   133,   134,    -1,    -1,
     137,    -1,    -1,   140,    -1,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   165,   166,
      -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,    -1,    -1,   200,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   209,    -1,    -1,   212,   213,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,   248,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   260,    56,    -1,    -1,   264,   265,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   273,   274,    -1,    -1,
      -1,    -1,    -1,   280,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    -1,    96,    -1,    -1,    -1,   100,    -1,
      -1,    -1,    -1,    -1,   106,    -1,    -1,    21,   110,    23,
      -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,    -1,    -1,   127,    -1,    -1,   130,    -1,
      -1,   133,   134,    -1,    -1,   137,    -1,    -1,   140,    -1,
     142,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   165,   166,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    96,    -1,    -1,    -1,   100,    -1,    -1,    -1,
      -1,    -1,   106,    -1,    -1,    -1,   110,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,    -1,    -1,   209,   122,    -1,
     212,   213,    -1,   127,    -1,    -1,   130,    -1,    -1,   133,
     134,    -1,    -1,   137,    -1,    -1,   140,    -1,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   247,   248,    -1,   250,    -1,
      -1,   165,   166,    -1,    -1,    -1,    21,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   273,   274,    -1,    -1,   277,    -1,    -1,   280,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,   209,    -1,    -1,   212,   213,
      33,    34,    35,    36,    -1,    -1,    39,    40,    -1,    42,
      43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    86,    87,    -1,    -1,    -1,    -1,    92,    -1,    -1,
      -1,    96,    -1,   247,   248,   100,   250,    -1,    -1,    -1,
      -1,   106,    -1,    -1,    -1,   110,    -1,    -1,    81,    82,
      83,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,   273,
     274,    -1,   127,   277,    -1,   130,   280,   281,   133,   134,
      -1,    -1,   137,    -1,    -1,   140,    -1,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     165,   166,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,    -1,    -1,   200,    -1,    -1,    -1,    21,
      -1,    23,    -1,    -1,   209,    -1,    -1,   212,   213,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,   214,   247,   248,    -1,    -1,   219,   220,   221,    -1,
      -1,    -1,    -1,    -1,    -1,   260,   229,    -1,    -1,   264,
     265,   234,    84,    85,    86,    87,    -1,    -1,   273,   274,
      92,    -1,    -1,    -1,    96,   280,    -1,    -1,   100,    -1,
      -1,    -1,    -1,    -1,   106,    -1,    -1,    21,   110,    23,
      -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,    -1,    -1,   127,    -1,    -1,   130,    -1,
      -1,   133,   134,    -1,    -1,   137,    -1,    -1,   140,    -1,
     142,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   165,   166,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    96,    -1,    -1,    -1,   100,    -1,    -1,    -1,
      -1,    -1,   106,    -1,    -1,    -1,   110,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,    -1,    -1,   209,   122,    -1,
     212,   213,    -1,   127,    -1,    -1,   130,    -1,    -1,   133,
     134,    -1,    -1,   137,    -1,    -1,   140,    -1,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   247,   248,    -1,   250,    -1,
      -1,   165,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   273,   274,    -1,    -1,   277,    -1,    -1,   280,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   209,    40,    -1,   212,   213,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   247,   248,    -1,   250,    81,    82,    -1,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    96,    -1,    -1,    -1,   100,    -1,    -1,   273,
     274,    -1,   106,    -1,    -1,    -1,   280,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,    -1,    -1,   127,    -1,    -1,   130,    -1,    -1,   133,
     134,    -1,    -1,   137,    -1,    -1,   140,    -1,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   165,   166,    -1,   168,   169,   170,    -1,    -1,   173,
     174,    -1,    -1,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,    -1,    -1,   200,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
     214,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   223,
      -1,    -1,    -1,    -1,    -1,   229,    -1,    -1,    -1,    -1,
     234,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     244,    -1,    -1,   247,   248,   249,   250,    -1,    -1,    -1,
     254,    -1,    -1,    -1,   258,   259,   260,    -1,    -1,    -1,
     264,   265,    84,    85,    86,    87,    -1,    -1,   272,    -1,
      92,   275,    -1,   277,    96,    -1,   280,   281,   100,    -1,
      -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,    -1,    -1,   127,    -1,    -1,   130,    -1,
      -1,   133,   134,    -1,    -1,   137,    -1,    -1,   140,    -1,
     142,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   165,   166,    -1,   168,   169,   170,    -1,
      -1,   173,   174,    -1,    -1,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,    -1,    -1,   200,    -1,
      -1,    -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    96,    -1,    -1,    -1,   100,
      -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,    -1,    -1,   127,    -1,    -1,   130,
      -1,    -1,   133,   134,    -1,    -1,   137,    -1,   260,   140,
      -1,   142,   264,   265,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   275,    -1,   277,    -1,    -1,   280,   281,
      -1,    -1,    -1,    -1,   165,   166,    -1,   168,   169,   170,
      -1,    -1,   173,   174,    23,    -1,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,    -1,    -1,   200,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    -1,    96,    -1,    -1,
      -1,   100,    -1,    -1,    -1,    -1,    -1,   106,    -1,   260,
      -1,   110,    -1,   264,   265,    -1,    -1,   116,    -1,    -1,
      -1,    -1,    -1,   122,   275,    -1,    -1,    -1,   127,   280,
     281,   130,    -1,    -1,   133,   134,    -1,    -1,   137,    -1,
      -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   165,   166,    -1,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,    -1,
      -1,   200,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
     209,    -1,    -1,   212,   213,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,   247,   248,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,   260,    -1,    -1,    -1,   264,   265,    -1,    -1,    -1,
      84,    85,    86,    87,   273,   274,    -1,    -1,    92,    -1,
      -1,   280,    96,    -1,    -1,    -1,   100,    -1,    -1,    -1,
      -1,    -1,   106,    -1,    -1,    -1,   110,    23,    -1,    -1,
      -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,    -1,    -1,   127,    -1,    -1,   130,    -1,    -1,   133,
     134,    -1,    -1,   137,    -1,    -1,   140,    -1,   142,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   165,   166,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,
      96,    -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,
     116,    -1,    -1,    -1,    -1,   209,   122,    -1,   212,   213,
      -1,   127,    -1,    -1,   130,    -1,    -1,   133,   134,    -1,
      -1,   137,    -1,    -1,   140,    -1,   142,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   247,   248,    -1,   250,    -1,    -1,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   273,
     274,    -1,    -1,    -1,    -1,    -1,   280,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,     1,
      -1,    -1,     4,   209,     6,    -1,   212,   213,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    29,    -1,    -1,
      -1,    33,    -1,    35,    -1,    37,    -1,    -1,    40,    41,
      42,   247,   248,    -1,   250,    47,    48,    49,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    -1,    -1,    -1,    -1,    -1,   273,   274,    -1,
      -1,    -1,    -1,    -1,   280,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,    -1,
      -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   214,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   229,    -1,    -1,
      -1,    -1,   234
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   286,     0,     1,     4,     6,    26,    27,    28,    29,
      33,    35,    37,    40,    41,    42,    47,    48,    49,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    91,   100,   106,   122,   200,   214,   229,   234,   287,
     289,   290,   291,   292,   339,   340,   341,   342,   350,   287,
      86,    85,   336,   336,   336,   341,   342,   350,   341,   344,
     344,   344,   292,    37,   293,    33,    35,    40,    41,    42,
     200,   214,   229,   234,   294,    37,   295,    33,    35,    37,
      40,    41,    42,   200,   214,   229,   234,   296,    33,    34,
      35,    36,    39,    40,    42,    43,    45,    81,    82,    83,
     200,   214,   219,   220,   221,   229,   234,   297,   214,   219,
     220,   234,   298,    33,    35,    40,    42,    45,    81,    82,
     299,    35,   300,    23,    30,    84,    85,    86,    87,    92,
      96,   100,   106,   116,   122,   127,   130,   133,   134,   137,
     140,   142,   165,   166,   168,   169,   170,   173,   174,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     200,   260,   264,   265,   275,   280,   281,   308,   337,   429,
     430,   431,   432,   433,   486,   489,   493,   494,   496,   498,
     508,   509,   511,   513,   515,   517,   519,   521,   523,   525,
     527,   529,   531,   533,   535,   539,   541,   543,   544,   546,
     548,   550,   552,   554,   556,   558,    45,   269,   270,   271,
     301,   307,    45,   302,   307,    85,   303,   304,   208,   341,
     346,   346,   346,     0,   287,   336,   336,   267,   349,    40,
      64,    65,    66,    67,    68,    69,    81,    82,   179,   200,
     214,   223,   229,   234,   244,   247,   248,   249,   250,   254,
     258,   259,   272,   277,   354,   355,   356,   357,   358,   359,
     363,   364,   367,   368,   375,   379,   383,   384,   386,   387,
     403,   404,   406,   407,   409,   410,   413,   414,   421,   423,
     424,   427,   428,   432,   437,   438,   439,   440,   441,   442,
     447,   448,   449,   471,   485,   489,   490,   506,   507,   508,
     287,   276,   276,   287,   309,   312,   354,   336,   314,   316,
     429,   449,   319,   342,   351,   341,   342,   344,   344,   344,
     208,   346,   346,   346,   350,   341,   342,   351,   344,   344,
     344,   208,   465,   346,   346,   346,   341,   340,   353,   342,
     353,    33,   353,   344,   344,   353,   353,    33,    34,   344,
     353,   222,   465,   346,    33,   353,    33,   353,    33,   353,
     346,   346,   346,    33,   353,    33,   353,   346,   341,   342,
     344,   344,   353,    33,   344,   342,    88,    89,    90,   336,
     510,    93,    94,   180,   181,   184,   435,   436,    93,    94,
      95,   512,    95,    97,    98,    99,   514,   101,   102,   103,
     104,   105,   516,    93,    94,    97,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   518,    95,    97,   115,   117,
     118,   119,   120,   520,    93,    94,   107,   109,   110,   111,
     124,   125,   126,   522,    95,    97,   115,   117,   118,   120,
     128,   129,   524,   108,   118,   125,   131,   132,   526,   118,
     132,   528,   125,   135,   136,   530,   111,   115,   138,   139,
     532,   115,   138,   139,   141,   534,   115,   118,   131,   135,
     138,   139,   143,   144,   145,   146,   147,   536,    95,   138,
     139,   540,   115,   138,   139,   167,   542,    95,   106,   108,
     120,   122,   125,   171,   198,   199,   495,   497,   547,   172,
     549,   172,   551,   108,   125,   545,    97,   112,   125,   131,
     175,   176,   553,   108,   125,   555,    95,   108,   115,   125,
     131,   557,    85,   111,   114,   123,   251,   487,   488,   489,
      93,    94,   114,   180,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   216,   217,   218,
     499,   500,   503,   251,   261,   492,   442,   448,   262,   168,
     173,   174,   177,   178,   559,   336,   441,   307,   270,   307,
      34,    36,    38,    39,    45,    46,    76,   305,   346,   336,
     216,   461,   462,   230,   469,   470,   232,   233,   376,   463,
     464,    84,    49,    50,   422,   336,   336,   336,    85,   487,
     499,   500,   215,   215,   230,   215,   376,    70,    70,     4,
     288,   450,   451,   268,   352,   357,   216,   217,   365,   366,
     135,   224,   225,   226,   227,   228,   369,   370,   245,   385,
       5,    21,    56,    70,    92,    96,   100,   106,   110,   122,
     168,   209,   212,   213,   247,   248,   273,   274,   388,   389,
     390,   391,   392,   393,   394,   396,   397,   398,   399,   400,
     401,   402,   430,   431,   480,   481,   482,   486,   493,   494,
     496,   498,   504,   505,   508,    70,   251,   252,   253,   405,
     411,   412,    70,   408,   411,   255,   256,   257,   415,   416,
     417,   418,    33,   425,   426,    15,    16,    17,    18,   279,
       8,    24,    42,     9,    10,    11,    12,    13,    14,    21,
      23,    92,    96,   100,   106,   116,   122,   127,   130,   133,
     134,   137,   140,   142,   165,   166,   250,   430,   431,   443,
     444,   445,   446,   449,   472,   473,   474,   475,   476,   477,
     478,   479,   481,   482,   483,   484,    40,    40,   460,   472,
     473,   460,   277,   277,   277,   277,    44,   348,   354,   309,
     312,   314,   316,   319,   346,   462,   470,   464,   354,   316,
     346,   341,   344,   353,    33,   346,   341,   341,   341,   341,
     341,   344,   336,     7,     8,    95,   184,   185,   434,   145,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   537,   497,   283,    93,    94,   114,   201,   202,   203,
     495,   501,   503,   262,   262,    84,   282,   306,   307,   468,
      84,   232,   233,   380,    84,   419,   420,   442,   277,    40,
      40,   503,    40,   401,   401,   380,   401,    84,   401,   448,
     446,   449,   454,   455,   458,   478,   479,     7,   278,   337,
      84,    84,   366,    63,    92,   106,   142,   187,   372,   337,
      84,    84,    84,   337,   371,   370,   116,   127,   142,   246,
     401,     5,   401,    15,    16,    17,    18,   279,    20,    22,
       8,    42,     5,   411,     7,     7,     5,     7,     5,   401,
     401,   416,     7,   336,   277,   426,   432,   432,   437,   438,
     439,   441,    23,   277,   360,   473,     7,    15,    16,    17,
      18,   279,     7,    20,    22,     8,   281,   473,   401,   401,
     287,   287,   311,   313,   315,   320,    84,   277,   277,   277,
     277,   468,   468,   341,    84,   436,    80,   111,   159,   160,
     161,   162,   163,   164,   538,    84,    93,    94,   502,    84,
      84,   263,   491,   277,   217,    84,    85,   217,   377,   430,
      74,   352,   456,   457,   442,   452,   453,   401,   401,    40,
     401,    84,   377,    32,   288,     5,   288,   456,   288,   451,
     121,   118,   121,   373,   374,    95,    95,    56,    95,   401,
       5,   388,   430,   482,   483,   389,   390,   391,    84,   393,
     388,   395,   430,   449,   401,   430,   482,   504,   504,   401,
     412,   401,   411,   418,   452,   336,   288,   361,   362,   478,
     483,   483,   474,   475,   476,   478,    84,   478,   478,   473,
      35,    40,    42,   135,   200,   214,   229,   234,   278,   287,
     289,   310,    77,    95,   278,   287,   289,   331,   334,   354,
      73,    74,    75,    76,    77,    80,    95,   135,   278,   287,
     289,   321,    74,    76,    95,   135,   278,   287,   289,   321,
     311,   313,   315,   320,   277,     7,   284,   491,   266,   491,
      84,   328,    84,    20,    85,   235,   378,    85,   338,   457,
     357,   456,   401,    20,    85,   378,   401,   459,   478,   479,
     485,     7,    85,    85,    85,   401,   411,   411,   357,   454,
       7,   278,   282,   336,   343,   336,   345,   345,    85,   208,
     336,   347,   347,   347,   287,    64,    65,   335,    85,   287,
     287,   287,   338,   338,   276,    78,    79,   322,    84,    85,
     109,   110,   180,   198,   323,   324,   330,    71,    72,    74,
     317,   318,   287,   338,   276,   324,   317,   287,   278,   278,
     278,   278,   328,    84,    84,    95,   201,   278,   287,   289,
     467,   239,   240,   241,   242,   243,   382,   231,   381,    84,
     278,   382,   381,   288,   374,   278,     5,   288,   362,   312,
     314,   319,   347,   325,   325,   325,    31,   287,   287,   316,
       8,   287,     7,   287,   287,   316,     5,   287,   278,   491,
      86,   340,   287,   381,    84,   377,   381,   485,   277,   277,
     277,   325,   277,   277,   277,    85,   323,   318,   214,   229,
     234,   324,   287,   114,   287,    85,   216,   217,   288,   313,
     315,   320,   277,   326,   329,   327,    32,   333,   287,   287,
     287,   287,   137,   142,   466,   278,   278,   278,   328,   278,
     287,   289,   461,   278,   287,   289,   469,   278,   287,   289,
     463,    85,   123,   287,   287,   287,   287,   278,   287,   287,
     287,    22,    84,   332,   287,    84
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   285,   286,   286,   287,   287,   288,   288,   289,   289,
     289,   289,   289,   290,   290,   290,   290,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   291,
     291,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   293,   294,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294,   294,   295,   296,
     296,   296,   296,   296,   296,   296,   296,   296,   296,   297,
     297,   297,   297,   297,   297,   297,   297,   297,   297,   297,
     297,   297,   297,   297,   297,   297,   297,   297,   297,   297,
     297,   297,   297,   297,   298,   298,   298,   298,   298,   298,
     299,   299,   299,   299,   299,   299,   299,   300,   301,   301,
     302,   302,   303,   304,   304,   305,   305,   305,   305,   305,
     305,   305,   305,   306,   306,   307,   307,   307,   308,   309,
     310,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   312,   313,   313,   313,   313,   313,   313,   314,
     315,   315,   315,   315,   315,   315,   315,   315,   315,   315,
     316,   316,   317,   317,   318,   318,   318,   319,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   321,
     321,   322,   322,   323,   324,   324,   325,   326,   326,   326,
     326,   327,   327,   327,   327,   328,   328,   328,   328,   329,
     329,   329,   329,   330,   330,   330,   330,   330,   331,   332,
     332,   333,   333,   334,   335,   335,   336,   337,   337,   337,
     338,   339,   339,   340,   340,   340,   340,   340,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   350,
     351,   352,   353,   353,   354,   354,   355,   356,   356,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   358,   358,   359,
     360,   360,   361,   361,   361,   362,   363,   363,   364,   364,
     365,   365,   366,   366,   367,   367,   368,   369,   369,   370,
     370,   370,   370,   370,   370,   371,   372,   372,   372,   372,
     372,   373,   373,   374,   374,   375,   375,   375,   376,   376,
     376,   377,   377,   378,   378,   379,   379,   380,   380,   380,
     381,   381,   381,   381,   382,   382,   382,   382,   382,   383,
     384,   385,   385,   385,   385,   385,   386,   387,   387,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   388,   389,
     389,   389,   390,   390,   391,   391,   392,   392,   393,   394,
     394,   395,   395,   396,   396,   397,   398,   399,   400,   400,
     400,   401,   401,   401,   402,   402,   402,   402,   402,   402,
     402,   403,   403,   404,   405,   405,   405,   406,   406,   407,
     408,   408,   408,   408,   408,   409,   409,   410,   411,   411,
     412,   412,   412,   413,   413,   414,   415,   415,   416,   416,
     417,   417,   418,   418,   419,   419,   420,   421,   422,   422,
     423,   423,   424,   425,   425,   426,   427,   428,   429,   430,
     430,   430,   431,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   433,   434,   434,   434,   435,
     435,   435,   435,   435,   436,   436,   437,   437,   437,   438,
     438,   439,   439,   440,   440,   441,   442,   442,   443,   444,
     445,   446,   446,   446,   447,   448,   448,   448,   449,   450,
     450,   450,   451,   451,   451,   452,   452,   453,   454,   454,
     455,   456,   456,   457,   457,   458,   458,   459,   459,   460,
     460,   461,   462,   463,   464,   465,   466,   466,   467,   467,
     468,   469,   469,   470,   471,   471,   471,   471,   472,   472,
     473,   473,   473,   474,   474,   474,   475,   475,   476,   476,
     477,   477,   478,   479,   479,   480,   480,   481,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   482,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   484,   484,   484,   484,   484,
     484,   485,   485,   485,   485,   485,   485,   486,   486,   486,
     487,   487,   488,   488,   488,   488,   489,   489,   489,   489,
     489,   489,   489,   489,   489,   489,   489,   489,   489,   489,
     489,   489,   489,   489,   490,   490,   490,   490,   491,   491,
     492,   492,   493,   494,   494,   494,   495,   495,   496,   496,
     497,   497,   497,   498,   498,   498,   499,   499,   500,   500,
     500,   500,   500,   500,   500,   500,   500,   500,   500,   500,
     500,   500,   500,   501,   501,   501,   501,   501,   501,   501,
     502,   502,   503,   503,   503,   503,   504,   504,   505,   505,
     506,   506,   507,   508,   508,   508,   508,   508,   508,   508,
     508,   508,   508,   508,   508,   508,   508,   508,   508,   509,
     510,   510,   510,   511,   512,   512,   512,   513,   514,   514,
     514,   514,   515,   516,   516,   516,   516,   516,   517,   518,
     518,   518,   518,   518,   518,   518,   518,   518,   518,   518,
     518,   519,   520,   520,   520,   520,   520,   520,   520,   521,
     522,   522,   522,   522,   522,   522,   522,   522,   522,   523,
     524,   524,   524,   524,   524,   524,   524,   524,   525,   526,
     526,   526,   526,   526,   527,   528,   528,   529,   530,   530,
     530,   531,   532,   532,   532,   532,   533,   534,   534,   534,
     534,   535,   535,   535,   536,   536,   536,   536,   536,   536,
     536,   536,   536,   536,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   538,   538,   538,   538,
     538,   538,   538,   538,   539,   540,   540,   540,   541,   542,
     542,   542,   542,   543,   543,   543,   543,   543,   543,   543,
     544,   545,   545,   546,   547,   547,   547,   547,   548,   549,
     550,   551,   552,   553,   553,   553,   553,   553,   553,   554,
     555,   555,   556,   557,   557,   557,   557,   557,   558,   559,
     559,   559,   559,   559
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       5,     3,     2,     1,     1,     2,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     6,     2,     6,     3,     2,     6,     6,     3,
       2,     3,     3,     8,     3,     3,     2,     6,     2,     6,
       6,     6,     3,     2,     3,     3,     8,     3,     3,     2,
       2,     2,     2,     2,     3,     2,     2,     4,     2,     2,
       2,     2,     2,     2,     3,     2,     2,     3,     2,     2,
       3,     2,     2,     3,     2,     2,     3,     3,     2,     2,
       2,     2,     3,     4,     2,     3,     2,     2,     3,     2,
       2,     2,     2,     2,     3,     2,     2,     3,     2,     1,
       2,     1,     3,     0,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     1,     1,     2,     1,     0,
       2,     0,     2,     2,     3,     8,     8,     8,     8,     8,
       9,     8,     0,     0,     2,     2,     3,     3,     3,     0,
       0,     2,     2,     4,     4,     4,     4,     4,     2,     3,
       1,     1,     3,     1,     1,     1,     1,     0,     0,     2,
       2,     4,     6,     6,     6,     6,     4,     4,     3,     2,
       2,     1,     1,     1,     1,     3,     0,     0,     2,     2,
       2,     0,     2,     2,     2,     0,     2,     2,     2,     0,
       2,     2,     2,     1,     1,     1,     1,     1,     7,     1,
       2,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     2,     1,     2,     1,     2,     2,     1,     2,
       2,     2,     0,     1,     1,     2,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     2,     1,     3,     3,     5,     1,     2,     1,     3,
       1,     2,     2,     2,     1,     2,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     1,     2,     2,     1,     1,
       1,     3,     1,     1,     1,     7,     6,     3,     1,     1,
       0,     1,     1,     0,     3,     5,     3,     1,     1,     0,
       0,     3,     3,     3,     1,     1,     1,     1,     1,     2,
       1,     0,     4,     4,     4,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     1,
       3,     1,     1,     3,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     4,     2,     3,
       2,     2,     1,     1,     3,     4,     1,     2,     1,     1,
       2,     3,     1,     3,     4,     3,     5,     3,     1,     3,
       1,     1,     1,     1,     2,     1,     1,     2,     2,     1,
       1,     3,     1,     1,     1,     2,     1,     4,     1,     1,
       6,     1,     1,     1,     2,     2,     6,     1,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     3,     3,     3,
       1,     1,     1,     1,     3,     1,     1,     1,     3,     1,
       3,     3,     3,     3,     5,     1,     2,     1,     1,     2,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     4,     1,     1,     1,     1,     5,     3,
       0,     6,     5,     1,     2,     2,     3,     5,     3,     3,
       1,     1,     1,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     4,     1,     0,     2,
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
       2,     1,     1,     2,     1,     1,     1,     1,     2,     4,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1
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
          case 85: /* "string"  */
#line 258 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3528 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 86: /* "quoted string"  */
#line 258 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3534 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 87: /* "string with a trailing asterisk"  */
#line 258 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3540 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 290: /* line  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3546 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 291: /* base_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3552 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 292: /* add_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3558 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 293: /* replace_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3564 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 294: /* create_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3570 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 295: /* insert_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3576 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 296: /* delete_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3582 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 297: /* list_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3588 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 298: /* reset_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3594 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 299: /* flush_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3600 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 300: /* rename_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3606 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 301: /* import_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3612 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 302: /* export_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3618 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 303: /* monitor_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3624 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 304: /* monitor_event  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3630 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 308: /* describe_cmd  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3636 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 309: /* table_block_alloc  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 3642 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 312: /* chain_block_alloc  */
#line 516 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 3648 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 314: /* set_block_alloc  */
#line 525 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3654 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 316: /* set_block_expr  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3660 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 319: /* map_block_alloc  */
#line 528 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3666 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 323: /* data_type_atom_expr  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3672 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 324: /* data_type_expr  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3678 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 325: /* obj_block_alloc  */
#line 531 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 3684 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 330: /* type_identifier  */
#line 491 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3690 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 333: /* dev_spec  */
#line 511 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3696 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 336: /* identifier  */
#line 491 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3702 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* string  */
#line 491 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3708 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* table_spec  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3714 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* chain_spec  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3720 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* chain_identifier  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3726 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* set_spec  */
#line 507 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3732 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 345: /* set_identifier  */
#line 507 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3738 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* obj_spec  */
#line 507 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3744 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* obj_identifier  */
#line 507 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3750 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 348: /* handle_spec  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3756 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 349: /* position_spec  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3762 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* rule_position  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3768 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 351: /* ruleid_spec  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3774 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 352: /* comment_spec  */
#line 491 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3780 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 353: /* ruleset_spec  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3786 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* rule  */
#line 518 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 3792 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* stmt_list  */
#line 534 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 3798 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 357: /* stmt  */
#line 536 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3804 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* verdict_stmt  */
#line 536 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3810 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 359: /* verdict_map_stmt  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3816 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* verdict_map_expr  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3822 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* verdict_map_list_expr  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3828 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 362: /* verdict_map_list_member_expr  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3834 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 363: /* counter_stmt  */
#line 538 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3840 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 364: /* counter_stmt_alloc  */
#line 538 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3846 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 367: /* log_stmt  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3852 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 368: /* log_stmt_alloc  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3858 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* limit_stmt  */
#line 549 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3864 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* quota_unit  */
#line 511 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3870 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 379: /* quota_stmt  */
#line 549 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3876 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* reject_stmt  */
#line 552 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3882 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* reject_stmt_alloc  */
#line 552 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3888 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* nat_stmt  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3894 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* nat_stmt_alloc  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3900 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* primary_stmt_expr  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3906 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* shift_stmt_expr  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3912 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* and_stmt_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3918 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* exclusive_or_stmt_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3924 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* inclusive_or_stmt_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3930 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 393: /* basic_stmt_expr  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3936 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* concat_stmt_expr  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3942 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* map_stmt_expr_set  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3948 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 396: /* map_stmt_expr  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3954 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* prefix_stmt_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3960 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* range_stmt_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3966 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* wildcard_stmt_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3972 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* multiton_stmt_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3978 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* stmt_expr  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3984 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* masq_stmt  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3990 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* masq_stmt_alloc  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3996 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* redir_stmt  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4002 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* redir_stmt_alloc  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4008 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* dup_stmt  */
#line 560 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4014 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* fwd_stmt  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4020 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* queue_stmt  */
#line 557 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4026 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* queue_stmt_alloc  */
#line 557 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4032 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* set_elem_expr_stmt  */
#line 615 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4038 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* set_elem_expr_stmt_alloc  */
#line 615 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4044 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* set_stmt  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4050 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* meter_stmt  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4056 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* flow_stmt_legacy_alloc  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4062 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* meter_stmt_alloc  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4068 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* match_stmt  */
#line 536 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4074 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* variable_expr  */
#line 570 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4080 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* symbol_expr  */
#line 570 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4086 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* integer_expr  */
#line 570 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4092 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 432: /* primary_expr  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4098 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* fib_expr  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4104 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* shift_expr  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4110 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* and_expr  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4116 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 439: /* exclusive_or_expr  */
#line 574 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4122 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 440: /* inclusive_or_expr  */
#line 574 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4128 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 441: /* basic_expr  */
#line 576 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4134 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* concat_expr  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4140 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* prefix_rhs_expr  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4146 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 444: /* range_rhs_expr  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4152 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 445: /* wildcard_rhs_expr  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4158 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 446: /* multiton_rhs_expr  */
#line 579 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4164 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 447: /* map_expr  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4170 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4176 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 449: /* set_expr  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4182 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 450: /* set_list_expr  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4188 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* set_list_member_expr  */
#line 611 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4194 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* meter_key_expr  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4200 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 453: /* meter_key_expr_alloc  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4206 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 454: /* set_elem_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4212 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 455: /* set_elem_expr_alloc  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4218 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* set_lhs_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4224 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* set_rhs_expr  */
#line 613 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4230 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* initializer_expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4236 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* counter_config  */
#line 698 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).counter)); }
#line 4242 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* counter_obj  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4248 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 463: /* quota_config  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).quota)); }
#line 4254 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* quota_obj  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4260 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* ct_obj_alloc  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4266 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* limit_config  */
#line 702 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).limit)); }
#line 4272 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* limit_obj  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4278 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* relational_expr  */
#line 634 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4284 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* list_rhs_expr  */
#line 626 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4290 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* rhs_expr  */
#line 624 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4296 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* shift_rhs_expr  */
#line 626 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4302 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* and_rhs_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4308 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* exclusive_or_rhs_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4314 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* inclusive_or_rhs_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4320 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 478: /* basic_rhs_expr  */
#line 624 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4326 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* concat_rhs_expr  */
#line 624 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4332 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* boolean_expr  */
#line 710 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4338 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 482: /* keyword_expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4344 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 483: /* primary_rhs_expr  */
#line 626 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4350 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* verdict_expr  */
#line 570 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4356 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 486: /* meta_expr  */
#line 675 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4362 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 490: /* meta_stmt  */
#line 544 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4368 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 493: /* numgen_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4374 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* hash_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4380 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 496: /* rt_expr  */
#line 681 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4386 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 498: /* ct_expr  */
#line 685 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4392 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 504: /* symbol_stmt_expr  */
#line 626 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4398 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* list_stmt_expr  */
#line 594 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4404 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* ct_stmt  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4410 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* payload_stmt  */
#line 540 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4416 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 508: /* payload_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4422 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 509: /* payload_raw_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4428 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 511: /* eth_hdr_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4434 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* vlan_hdr_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4440 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 515: /* arp_hdr_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4446 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* ip_hdr_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4452 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* icmp_hdr_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4458 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 521: /* ip6_hdr_expr  */
#line 650 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4464 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* icmp6_hdr_expr  */
#line 650 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4470 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 525: /* auth_hdr_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4476 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 527: /* esp_hdr_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4482 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 529: /* comp_hdr_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4488 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* udp_hdr_expr  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4494 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* udplite_hdr_expr  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4500 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* tcp_hdr_expr  */
#line 705 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4506 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* dccp_hdr_expr  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4512 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* sctp_hdr_expr  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4518 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* exthdr_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4524 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 544: /* hbh_hdr_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4530 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 546: /* rt_hdr_expr  */
#line 668 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4536 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 548: /* rt0_hdr_expr  */
#line 668 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4542 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 550: /* rt2_hdr_expr  */
#line 668 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4548 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 552: /* frag_hdr_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4554 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 554: /* dst_hdr_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4560 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 556: /* mh_hdr_expr  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4566 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 558: /* exthdr_exists_expr  */
#line 714 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4572 "parser_bison.c" /* yacc.c:1257  */
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
#line 127 "parser_bison.y" /* yacc.c:1429  */
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & NFT_DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & NFT_DEBUG_PARSER)
		yydebug = 1;
}

#line 4689 "parser_bison.c" /* yacc.c:1429  */
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
#line 723 "parser_bison.y" /* yacc.c:1646  */
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
						list_splice_tail(&list, &state->cmds);
				}
			}
#line 4892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 8:
#line 749 "parser_bison.y" /* yacc.c:1646  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 4904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 9:
#line 757 "parser_bison.y" /* yacc.c:1646  */
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
#line 4922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 771 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				/* ignore missing identifier */
				symbol_unbind(scope, (yyvsp[-3].string));
				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 4935 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 11:
#line 780 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_unbind(scope, (yyvsp[-1].string)) < 0) {
					erec_queue(error(&(yylsp[-1]), "undefined symbol '%s'", (yyvsp[-1].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 4950 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 791 "parser_bison.y" /* yacc.c:1646  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 4960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 798 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 4966 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 799 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 4972 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 800 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 4978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 16:
#line 802 "parser_bison.y" /* yacc.c:1646  */
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
						list_splice_tail(&list, &state->cmds);
				}
				if (state->nerrs)
					YYABORT;
				(yyval.cmd) = NULL;

				YYACCEPT;
			}
#line 5012 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 833 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5018 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 834 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5024 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 835 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5030 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 836 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5036 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 837 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5042 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 838 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5048 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 839 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5054 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 840 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5060 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 841 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 842 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5072 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 843 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5078 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 844 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5084 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 845 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5090 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 846 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 850 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5104 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 855 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5114 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 861 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5122 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 866 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5133 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 873 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 877 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5149 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 882 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 889 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5169 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 895 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5177 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 899 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5190 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 908 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5198 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 42:
#line 912 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 916 "parser_bison.y" /* yacc.c:1646  */
    {

				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5215 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 921 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5223 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 927 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5231 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 933 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5239 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 938 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5249 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 944 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5257 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 949 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5268 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 957 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5278 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 964 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5288 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 970 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5296 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 974 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5309 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 983 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5317 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 987 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5325 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 56:
#line 991 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5333 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 995 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5341 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1001 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5349 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1007 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5357 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1011 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5365 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1015 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1019 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5381 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1023 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5389 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1027 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1031 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5405 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1035 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5413 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1039 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5421 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1043 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1049 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5437 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1053 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5445 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1057 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5453 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1061 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5461 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1065 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5469 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1069 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5477 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1073 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5485 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1077 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5493 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1081 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5501 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1085 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5509 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1089 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5517 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1093 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5525 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1097 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5533 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1101 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5541 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1105 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5549 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1109 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5557 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1113 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5565 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1117 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5573 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1121 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5581 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1125 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5589 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1129 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5597 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1133 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5605 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1137 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1141 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5621 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1145 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5629 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1151 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5637 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1155 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5645 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1159 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 5653 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1163 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1167 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1171 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5677 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1177 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1181 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1185 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5701 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1189 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5709 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1193 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5717 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1197 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5725 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1201 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5733 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1207 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 5742 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1214 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 5752 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1220 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 5762 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1228 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 5772 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1234 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 5782 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1242 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 5793 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1250 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 5799 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1251 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 5805 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1254 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 5811 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1255 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 5817 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1256 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 5823 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1257 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 5829 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1258 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 5835 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1259 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 5841 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1260 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 5847 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1261 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 5853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1264 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 5859 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1268 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 5865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1269 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = __NFT_OUTPUT_NOTSUPP; }
#line 5871 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1270 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 5877 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1274 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 5887 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1282 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 5896 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1289 "parser_bison.y" /* yacc.c:1646  */
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
#line 5912 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1302 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 5918 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1309 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5931 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1320 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5943 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1330 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5955 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1340 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1351 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5981 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1360 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 5994 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1371 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 6007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1382 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 6016 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1388 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 6022 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1394 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 6031 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1401 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6039 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1406 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6045 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1410 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6054 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1415 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6063 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1420 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6072 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1425 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6081 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1430 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6090 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1435 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 6099 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1447 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6107 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1453 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 6113 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1454 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 6119 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1455 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 6125 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1459 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6133 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1464 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6139 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1468 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6148 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1475 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].expr)->dtype;

				expr_free((yyvsp[-1].expr));
				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6161 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1486 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6172 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1495 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1504 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1511 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6203 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1516 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6212 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1524 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 6220 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1528 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 6228 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1533 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 6234 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1534 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 6240 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1538 "parser_bison.y" /* yacc.c:1646  */
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
#line 6256 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1553 "parser_bison.y" /* yacc.c:1646  */
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
#line 6277 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1572 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 6285 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1577 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6291 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1581 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->counter = *(yyvsp[0].counter);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6300 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1587 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6306 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1591 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->quota = *(yyvsp[0].quota);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6315 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1597 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6321 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1601 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6329 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1606 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6335 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1610 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->limit = *(yyvsp[0].limit);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6344 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1616 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6350 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1617 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("mark"); }
#line 6356 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1618 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("dscp"); }
#line 6362 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1619 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("ecn"); }
#line 6368 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1620 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("classid"); }
#line 6374 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1624 "parser_bison.y" /* yacc.c:1646  */
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
#line 6404 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1651 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 6410 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1652 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = -(yyvsp[0].val); }
#line 6416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1655 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6422 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1656 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6428 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1660 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].chain)->policy != -1) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].val);
			}
#line 6441 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1670 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_ACCEPT; }
#line 6447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1671 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_DROP;   }
#line 6453 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1683 "parser_bison.y" /* yacc.c:1646  */
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
#line 6470 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1697 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6476 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1701 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6482 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1702 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 6488 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1703 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_INET; }
#line 6494 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1704 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_ARP; }
#line 6500 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1705 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 6506 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1706 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 6512 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1710 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table	= (yyvsp[0].string);
			}
#line 6522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1718 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 6531 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1725 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 6540 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1732 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 6549 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1739 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 6558 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1746 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj		= (yyvsp[0].string);
			}
#line 6567 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1753 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj		= (yyvsp[0].string);
			}
#line 6576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1760 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 6586 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1768 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 6596 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1776 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 6604 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1780 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 6613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1787 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 6622 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1794 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strlen((yyvsp[0].string)) > UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed", UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 6635 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1805 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 6644 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1810 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 6653 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1817 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 6661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1821 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 6669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1827 "parser_bison.y" /* yacc.c:1646  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 6683 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1839 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 6693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1845 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 6702 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1872 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 6710 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1876 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 6718 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1882 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6726 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1888 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6735 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1893 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 6746 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1902 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 6755 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1907 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 6764 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1915 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 6772 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1924 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 6780 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1928 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 6790 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1936 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 6798 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1943 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 6806 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1947 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 6814 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1957 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 6822 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1963 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 6830 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1970 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 6839 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1975 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 6848 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1980 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 6857 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1985 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 6866 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1990 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 6875 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1995 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 6883 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 295:
#line 2001 "parser_bison.y" /* yacc.c:1646  */
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
#line 6913 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 296:
#line 2029 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 6921 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 297:
#line 2033 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 6929 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 298:
#line 2037 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 6937 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 299:
#line 2041 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 6945 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 300:
#line 2045 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 6953 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 301:
#line 2051 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6961 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 303:
#line 2058 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 6969 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2062 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 6977 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2068 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 6990 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2077 "parser_bison.y" /* yacc.c:1646  */
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
#line 7013 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2096 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7023 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 308:
#line 2103 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 7029 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 309:
#line 2104 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7035 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 310:
#line 2105 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7041 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 311:
#line 2108 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("bytes"); }
#line 7047 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 312:
#line 2109 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 313:
#line 2112 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7059 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 314:
#line 2114 "parser_bison.y" /* yacc.c:1646  */
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
#line 7076 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 315:
#line 2129 "parser_bison.y" /* yacc.c:1646  */
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
#line 7096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 316:
#line 2145 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 317:
#line 2152 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 7112 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 318:
#line 2153 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 319:
#line 2154 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7124 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2157 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 321:
#line 2158 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 7136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 322:
#line 2159 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 7142 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2161 "parser_bison.y" /* yacc.c:1646  */
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
#line 7159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2175 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL; }
#line 7165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2176 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60; }
#line 7171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2177 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 7177 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2178 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 7183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 328:
#line 2179 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 7189 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2186 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 7197 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2192 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 7206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2197 "parser_bison.y" /* yacc.c:1646  */
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
#line 7221 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2208 "parser_bison.y" /* yacc.c:1646  */
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
#line 7236 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2219 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpx_code_type;
				xfree((yyvsp[0].string));
			}
#line 7250 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2229 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 7258 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2238 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_SNAT;
			}
#line 7267 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2243 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_DNAT;
			}
#line 7276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2249 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7282 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2250 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7288 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2251 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7294 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2252 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7300 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2253 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7306 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2254 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7312 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2255 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7318 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2256 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7324 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2257 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7330 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 348:
#line 2258 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7336 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 350:
#line 2263 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7344 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2267 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7352 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 353:
#line 2274 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7360 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 355:
#line 2281 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7368 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 357:
#line 2288 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7376 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 360:
#line 2298 "parser_bison.y" /* yacc.c:1646  */
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
#line 7397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 363:
#line 2321 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7405 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 364:
#line 2324 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7411 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2328 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 7419 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2334 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7427 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2340 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 7440 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2361 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7448 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2365 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7456 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2369 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7465 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2374 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7474 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2379 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7482 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2383 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7490 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2387 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7498 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2396 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = masq_stmt_alloc(&(yyloc)); }
#line 7504 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2400 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->masq.proto = (yyvsp[0].expr);
			}
#line 7512 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2404 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->masq.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 7521 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 386:
#line 2409 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 7529 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 389:
#line 2418 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = redir_stmt_alloc(&(yyloc)); }
#line 7535 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 390:
#line 2422 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 7543 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2426 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 7551 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 392:
#line 2430 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 393:
#line 2434 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7568 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2439 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7577 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2446 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 7586 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2451 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 7596 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2459 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.to = (yyvsp[0].expr);
			}
#line 7605 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2467 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2472 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 7619 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2473 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 7625 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 402:
#line 2474 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 7631 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 405:
#line 2482 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 7639 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 406:
#line 2488 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7647 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2495 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 7656 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2500 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 7664 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2507 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7672 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2512 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 7678 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2513 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 7684 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2521 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 7692 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2527 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 7703 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2535 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 7709 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2536 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 7715 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2540 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 7726 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2546 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 7732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2550 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 7740 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2556 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7748 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2563 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 7756 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2569 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 7768 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2579 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7776 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2585 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, (yyvsp[0].string)) == NULL) {
					erec_queue(error(&(yylsp[0]), "unknown identifier '%s'", (yyvsp[0].string)),
						   state->msgs);
					xfree((yyvsp[0].string));
					YYERROR;
				}

				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_DEFINE,
						       scope, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7795 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2603 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7806 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2610 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7817 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2619 "parser_bison.y" /* yacc.c:1646  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 7830 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2629 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7836 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2630 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2631 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7848 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2632 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7854 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2633 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7860 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2634 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7866 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2635 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7872 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2636 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7878 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2637 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7884 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2638 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7890 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2639 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7896 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2640 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 7902 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2644 "parser_bison.y" /* yacc.c:1646  */
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
#line 7927 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2666 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 7933 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2667 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 7939 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 448:
#line 2668 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 7945 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2671 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 7951 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2672 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 7957 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2673 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 7963 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2674 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 7969 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2675 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 7975 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2679 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7983 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2687 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7991 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2691 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7999 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 460:
#line 2698 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2705 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8015 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2712 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8023 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2722 "parser_bison.y" /* yacc.c:1646  */
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
#line 8044 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2741 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 8052 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2747 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8060 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2753 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 8073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2769 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8081 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2780 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8090 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2787 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8099 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2792 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8108 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2800 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8116 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2804 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8124 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2808 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 8132 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2815 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 487:
#line 2822 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8149 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2832 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8157 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 491:
#line 2838 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 8165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2845 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val) * 1000;
			}
#line 8173 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 494:
#line 2849 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 8181 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2867 "parser_bison.y" /* yacc.c:1646  */
    {
				struct counter *counter;

				counter = xzalloc(sizeof(*counter));
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
				(yyval.counter) = counter;
			}
#line 8194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2878 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
				(yyval.obj)->counter = *(yyvsp[0].counter);
			}
#line 8204 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 503:
#line 2886 "parser_bison.y" /* yacc.c:1646  */
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
#line 8227 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 504:
#line 2907 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
				(yyval.obj)->quota = *(yyvsp[0].quota);
			}
#line 8237 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 505:
#line 2914 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 8243 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 506:
#line 2917 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_TCP; }
#line 8249 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 507:
#line 2918 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_UDP; }
#line 8255 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 508:
#line 2922 "parser_bison.y" /* yacc.c:1646  */
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
#line 8274 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 509:
#line 2937 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 8282 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 510:
#line 2943 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 8290 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 511:
#line 2949 "parser_bison.y" /* yacc.c:1646  */
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
#line 8305 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 512:
#line 2960 "parser_bison.y" /* yacc.c:1646  */
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
#line 8329 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 513:
#line 2982 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
				(yyval.obj)->limit = *(yyvsp[0].limit);
			}
#line 8339 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 514:
#line 2990 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8347 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 515:
#line 2994 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_FLAGCMP, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 516:
#line 2998 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8363 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 517:
#line 3002 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-3]), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[-1].expr));
			}
#line 8371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 518:
#line 3008 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8381 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 519:
#line 3014 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8391 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 520:
#line 3021 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 521:
#line 3022 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8403 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 522:
#line 3023 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8409 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 524:
#line 3028 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8417 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 525:
#line 3032 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8425 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 527:
#line 3039 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8433 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 529:
#line 3046 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8441 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 531:
#line 3053 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8449 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 534:
#line 3063 "parser_bison.y" /* yacc.c:1646  */
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
#line 8470 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 535:
#line 3081 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = true; }
#line 8476 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 536:
#line 3082 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = false; }
#line 8482 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 537:
#line 3086 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 1, &(yyvsp[0].val));
			}
#line 8492 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 538:
#line 3093 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 8498 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 539:
#line 3094 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 8504 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 540:
#line 3095 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 8510 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 541:
#line 3096 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 8516 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 542:
#line 3097 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 8522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 543:
#line 3098 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 8528 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 544:
#line 3099 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 8534 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 545:
#line 3100 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 8540 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 546:
#line 3101 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 8546 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 547:
#line 3102 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 8552 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 548:
#line 3103 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 8558 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 549:
#line 3104 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 8564 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 550:
#line 3107 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8570 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 551:
#line 3108 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 552:
#line 3109 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8582 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 553:
#line 3110 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8588 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 554:
#line 3112 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8599 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 555:
#line 3119 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8610 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 556:
#line 3126 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8621 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 557:
#line 3133 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8632 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 558:
#line 3140 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8643 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 559:
#line 3147 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8654 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 560:
#line 3154 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8665 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 561:
#line 3161 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8676 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 562:
#line 3168 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8687 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 563:
#line 3175 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8698 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 564:
#line 3182 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8709 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 565:
#line 3190 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_EQ; }
#line 8715 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 566:
#line 3191 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_NEQ; }
#line 8721 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 567:
#line 3192 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LT; }
#line 8727 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 568:
#line 3193 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GT; }
#line 8733 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 569:
#line 3194 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GTE; }
#line 8739 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 570:
#line 3195 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LTE; }
#line 8745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 571:
#line 3199 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 8753 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 572:
#line 3203 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 8761 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 573:
#line 3207 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 8769 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 574:
#line 3211 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].string));
			}
#line 8777 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 575:
#line 3215 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].string));
			}
#line 8785 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 576:
#line 3219 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 8793 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 577:
#line 3225 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 8801 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 578:
#line 3229 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 8809 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 579:
#line 3233 "parser_bison.y" /* yacc.c:1646  */
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
#line 8827 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 582:
#line 3251 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_LEN; }
#line 8833 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 583:
#line 3252 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 8839 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 584:
#line 3253 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 8845 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 585:
#line 3254 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 8851 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 586:
#line 3257 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_MARK; }
#line 8857 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 587:
#line 3258 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIF; }
#line 8863 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 588:
#line 3259 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 8869 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 589:
#line 3260 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 8875 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 590:
#line 3261 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIF; }
#line 8881 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 591:
#line 3262 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 8887 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 592:
#line 3263 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 8893 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 593:
#line 3264 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKUID; }
#line 8899 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 594:
#line 3265 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKGID; }
#line 8905 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 595:
#line 3266 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 8911 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 596:
#line 3267 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 8917 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 597:
#line 3268 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 8923 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 598:
#line 3269 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 8929 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 599:
#line 3270 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 8935 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 600:
#line 3271 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CPU; }
#line 8941 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 601:
#line 3272 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 8947 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 602:
#line 3273 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 8953 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 603:
#line 3274 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 8959 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 604:
#line 3278 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 8967 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 605:
#line 3282 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 8975 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 606:
#line 3286 "parser_bison.y" /* yacc.c:1646  */
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
#line 8993 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 607:
#line 3300 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 9001 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 608:
#line 3305 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 9007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 609:
#line 3306 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 9013 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 610:
#line 3309 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 9019 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 611:
#line 3310 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 9025 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 612:
#line 3314 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 9033 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 613:
#line 3320 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 9042 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 614:
#line 3325 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 9051 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 615:
#line 3330 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 9059 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 616:
#line 3335 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 9065 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 617:
#line 3336 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 9071 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 618:
#line 3340 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 9079 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 619:
#line 3344 "parser_bison.y" /* yacc.c:1646  */
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
#line 9101 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 620:
#line 3363 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 9107 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 621:
#line 3364 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 9113 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 622:
#line 3365 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 9119 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 623:
#line 3369 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1, NFPROTO_UNSPEC);
			}
#line 9127 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 624:
#line 3373 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val), NFPROTO_UNSPEC);
			}
#line 9135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 625:
#line 3377 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 9143 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 626:
#line 3382 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 9149 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 627:
#line 3383 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 9155 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 628:
#line 3386 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9161 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 629:
#line 3387 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9167 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 630:
#line 3388 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_MARK; }
#line 9173 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 631:
#line 3389 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATE; }
#line 9179 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 632:
#line 3390 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 9185 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 633:
#line 3391 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 9191 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 634:
#line 3392 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 9197 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 635:
#line 3393 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 9203 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 636:
#line 3394 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9209 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 637:
#line 3395 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9215 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 638:
#line 3396 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9221 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3397 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9227 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 640:
#line 3398 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 9233 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 641:
#line 3399 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 9239 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3403 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9245 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 644:
#line 3404 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9251 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 645:
#line 3405 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9257 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 646:
#line 3406 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9263 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 647:
#line 3407 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9269 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 648:
#line 3408 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9275 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 650:
#line 3412 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9281 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 651:
#line 3413 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9287 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 652:
#line 3416 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 9293 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 653:
#line 3417 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 9299 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 654:
#line 3418 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 9305 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 655:
#line 3419 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 9311 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 658:
#line 3427 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9321 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 659:
#line 3433 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9331 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 660:
#line 3441 "parser_bison.y" /* yacc.c:1646  */
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
#line 9348 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 661:
#line 3454 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 9356 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 662:
#line 3460 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].expr)->ops->type == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9367 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 679:
#line 3487 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				(yyval.expr)->payload.base	= (yyvsp[-4].val);
				(yyval.expr)->payload.offset	= (yyvsp[-2].val);
				(yyval.expr)->len			= (yyvsp[0].val);
				(yyval.expr)->dtype		= &integer_type;
				(yyval.expr)->byteorder		= BYTEORDER_BIG_ENDIAN;
				(yyval.expr)->payload.is_raw	= true;
				(yyval.expr)->flags		= 0;
			}
#line 9382 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 680:
#line 3499 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 9388 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 681:
#line 3500 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 9394 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 682:
#line 3501 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 9400 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 683:
#line 3505 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 9408 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 684:
#line 3510 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 9414 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 685:
#line 3511 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 9420 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 686:
#line 3512 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 9426 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 687:
#line 3516 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 9434 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 688:
#line 3521 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_VID; }
#line 9440 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 689:
#line 3522 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_CFI; }
#line 9446 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 690:
#line 3523 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_PCP; }
#line 9452 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 691:
#line 3524 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 9458 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 692:
#line 3528 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 9466 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 693:
#line 3533 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HRD; }
#line 9472 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 694:
#line 3534 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PRO; }
#line 9478 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 695:
#line 3535 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HLN; }
#line 9484 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 696:
#line 3536 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PLN; }
#line 9490 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 697:
#line 3537 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_OP; }
#line 9496 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 698:
#line 3541 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 9504 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 699:
#line 3546 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_VERSION; }
#line 9510 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 700:
#line 3547 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 9516 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 701:
#line 3548 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DSCP; }
#line 9522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 702:
#line 3549 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ECN; }
#line 9528 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 703:
#line 3550 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 9534 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 704:
#line 3551 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ID; }
#line 9540 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 705:
#line 3552 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 9546 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 706:
#line 3553 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_TTL; }
#line 9552 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 707:
#line 3554 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 9558 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 708:
#line 3555 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 9564 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 709:
#line 3556 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_SADDR; }
#line 9570 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 710:
#line 3557 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DADDR; }
#line 9576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 711:
#line 3561 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 9584 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 712:
#line 3566 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 9590 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 713:
#line 3567 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 9596 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 714:
#line 3568 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 9602 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 715:
#line 3569 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_ID; }
#line 9608 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 716:
#line 3570 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 9614 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 717:
#line 3571 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 9620 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 718:
#line 3572 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 9626 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 719:
#line 3576 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 9634 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 720:
#line 3581 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 9640 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 721:
#line 3582 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 9646 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 722:
#line 3583 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_ECN; }
#line 9652 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 723:
#line 3584 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 9658 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 724:
#line 3585 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 9664 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 725:
#line 3586 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 9670 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 726:
#line 3587 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 9676 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 727:
#line 3588 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 9682 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 728:
#line 3589 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 9688 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 729:
#line 3592 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 9696 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 730:
#line 3597 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 9702 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 731:
#line 3598 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 9708 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 732:
#line 3599 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 9714 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 733:
#line 3600 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 9720 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 734:
#line 3601 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 9726 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 735:
#line 3602 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 9732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 736:
#line 3603 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 9738 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 737:
#line 3604 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 9744 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 738:
#line 3608 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 9752 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 739:
#line 3613 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 9758 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 740:
#line 3614 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 9764 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 741:
#line 3615 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 9770 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 742:
#line 3616 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SPI; }
#line 9776 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 743:
#line 3617 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 9782 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 744:
#line 3621 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 9790 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 745:
#line 3626 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SPI; }
#line 9796 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 746:
#line 3627 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 9802 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 747:
#line 3631 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 9810 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 748:
#line 3636 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 9816 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 749:
#line 3637 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 9822 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 750:
#line 3638 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_CPI; }
#line 9828 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 751:
#line 3642 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 9836 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 752:
#line 3647 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 9842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 753:
#line 3648 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 9848 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 754:
#line 3649 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 9854 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 755:
#line 3650 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 9860 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 756:
#line 3654 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 9868 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 757:
#line 3659 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 9874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 758:
#line 3660 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 9880 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 759:
#line 3661 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 9886 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 760:
#line 3662 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 9892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 761:
#line 3666 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 9900 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 762:
#line 3670 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 9908 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 763:
#line 3674 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 9917 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 764:
#line 3680 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 9923 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 765:
#line 3681 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 9929 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 766:
#line 3682 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 9935 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 767:
#line 3683 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 9941 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 768:
#line 3684 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 9947 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 769:
#line 3685 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 9953 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 770:
#line 3686 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 9959 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 771:
#line 3687 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 9965 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 772:
#line 3688 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 9971 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 773:
#line 3689 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 9977 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 774:
#line 3692 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 9983 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 775:
#line 3693 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 9989 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 776:
#line 3694 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 9995 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 777:
#line 3695 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 10001 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 778:
#line 3696 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 10007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 779:
#line 3697 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 10013 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 780:
#line 3698 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 10019 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 781:
#line 3699 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 10025 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 782:
#line 3700 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 10031 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 783:
#line 3701 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 10037 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 784:
#line 3702 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 10043 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 785:
#line 3703 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 10049 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 786:
#line 3706 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 10055 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 787:
#line 3707 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 10061 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 788:
#line 3708 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 10067 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 789:
#line 3709 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 10073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 790:
#line 3710 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 10079 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 791:
#line 3711 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 10085 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 792:
#line 3712 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 10091 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 793:
#line 3713 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 10097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 794:
#line 3717 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 10105 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 795:
#line 3722 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 10111 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 796:
#line 3723 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 10117 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 797:
#line 3724 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 10123 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 798:
#line 3728 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 10131 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 799:
#line 3733 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 10137 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 800:
#line 3734 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 10143 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 801:
#line 3735 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 10149 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 802:
#line 3736 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 10155 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 810:
#line 3749 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 10163 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 811:
#line 3754 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 10169 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 812:
#line 3755 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 10175 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 813:
#line 3759 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 10183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 814:
#line 3764 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 10189 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 815:
#line 3765 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 10195 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 816:
#line 3766 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_TYPE; }
#line 10201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 817:
#line 3767 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 10207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 818:
#line 3771 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 10215 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 819:
#line 3777 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 10223 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 820:
#line 3783 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 10231 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 821:
#line 3788 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 10237 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 822:
#line 3792 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 10245 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 823:
#line 3797 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 10251 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 824:
#line 3798 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 10257 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 825:
#line 3799 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 10263 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 826:
#line 3800 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 10269 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 827:
#line 3801 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 10275 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 828:
#line 3802 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_ID; }
#line 10281 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 829:
#line 3806 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 10289 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 830:
#line 3811 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 10295 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 831:
#line 3812 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 10301 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 832:
#line 3816 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 10309 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 833:
#line 3821 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 10315 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 834:
#line 3822 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 10321 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 835:
#line 3823 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_TYPE; }
#line 10327 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 836:
#line 3824 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 10333 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 837:
#line 3825 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 10339 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 838:
#line 3829 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 10355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 839:
#line 3842 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 10361 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 840:
#line 3843 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 10367 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 841:
#line 3844 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 10373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 842:
#line 3845 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 10379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 843:
#line 3846 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_MH; }
#line 10385 "parser_bison.c" /* yacc.c:1646  */
    break;


#line 10389 "parser_bison.c" /* yacc.c:1646  */
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
#line 3849 "parser_bison.y" /* yacc.c:1906  */

