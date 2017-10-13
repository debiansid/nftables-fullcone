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

#line 171 "parser_bison.c" /* yacc.c:339  */

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
    FIB = 283,
    HOOK = 284,
    DEVICE = 285,
    TABLE = 286,
    TABLES = 287,
    CHAIN = 288,
    CHAINS = 289,
    RULE = 290,
    RULES = 291,
    SETS = 292,
    SET = 293,
    ELEMENT = 294,
    MAP = 295,
    MAPS = 296,
    HANDLE = 297,
    RULESET = 298,
    TRACE = 299,
    INET = 300,
    NETDEV = 301,
    ADD = 302,
    UPDATE = 303,
    REPLACE = 304,
    CREATE = 305,
    INSERT = 306,
    DELETE = 307,
    LIST = 308,
    RESET = 309,
    FLUSH = 310,
    RENAME = 311,
    DESCRIBE = 312,
    EXPORT = 313,
    MONITOR = 314,
    ALL = 315,
    ACCEPT = 316,
    DROP = 317,
    CONTINUE = 318,
    JUMP = 319,
    GOTO = 320,
    RETURN = 321,
    TO = 322,
    CONSTANT = 323,
    INTERVAL = 324,
    TIMEOUT = 325,
    GC_INTERVAL = 326,
    ELEMENTS = 327,
    POLICY = 328,
    MEMORY = 329,
    PERFORMANCE = 330,
    SIZE = 331,
    FLOW = 332,
    NUM = 333,
    STRING = 334,
    QUOTED_STRING = 335,
    ASTERISK_STRING = 336,
    LL_HDR = 337,
    NETWORK_HDR = 338,
    TRANSPORT_HDR = 339,
    BRIDGE = 340,
    ETHER = 341,
    SADDR = 342,
    DADDR = 343,
    TYPE = 344,
    VLAN = 345,
    ID = 346,
    CFI = 347,
    PCP = 348,
    ARP = 349,
    HTYPE = 350,
    PTYPE = 351,
    HLEN = 352,
    PLEN = 353,
    OPERATION = 354,
    IP = 355,
    HDRVERSION = 356,
    HDRLENGTH = 357,
    DSCP = 358,
    ECN = 359,
    LENGTH = 360,
    FRAG_OFF = 361,
    TTL = 362,
    PROTOCOL = 363,
    CHECKSUM = 364,
    ICMP = 365,
    CODE = 366,
    SEQUENCE = 367,
    GATEWAY = 368,
    MTU = 369,
    OPTIONS = 370,
    IP6 = 371,
    PRIORITY = 372,
    FLOWLABEL = 373,
    NEXTHDR = 374,
    HOPLIMIT = 375,
    ICMP6 = 376,
    PPTR = 377,
    MAXDELAY = 378,
    AH = 379,
    RESERVED = 380,
    SPI = 381,
    ESP = 382,
    COMP = 383,
    FLAGS = 384,
    CPI = 385,
    UDP = 386,
    SPORT = 387,
    DPORT = 388,
    UDPLITE = 389,
    CSUMCOV = 390,
    TCP = 391,
    ACKSEQ = 392,
    DOFF = 393,
    WINDOW = 394,
    URGPTR = 395,
    OPTION = 396,
    ECHO = 397,
    EOL = 398,
    MAXSEG = 399,
    NOOP = 400,
    SACK = 401,
    SACK0 = 402,
    SACK1 = 403,
    SACK2 = 404,
    SACK3 = 405,
    SACK_PERMITTED = 406,
    TIMESTAMP = 407,
    KIND = 408,
    COUNT = 409,
    LEFT = 410,
    RIGHT = 411,
    TSVAL = 412,
    TSECR = 413,
    DCCP = 414,
    SCTP = 415,
    VTAG = 416,
    RT = 417,
    RT0 = 418,
    RT2 = 419,
    SEG_LEFT = 420,
    ADDR = 421,
    HBH = 422,
    FRAG = 423,
    RESERVED2 = 424,
    MORE_FRAGMENTS = 425,
    DST = 426,
    MH = 427,
    META = 428,
    MARK = 429,
    IIF = 430,
    IIFNAME = 431,
    IIFTYPE = 432,
    OIF = 433,
    OIFNAME = 434,
    OIFTYPE = 435,
    SKUID = 436,
    SKGID = 437,
    NFTRACE = 438,
    RTCLASSID = 439,
    IBRIPORT = 440,
    OBRIPORT = 441,
    PKTTYPE = 442,
    CPU = 443,
    IIFGROUP = 444,
    OIFGROUP = 445,
    CGROUP = 446,
    CLASSID = 447,
    NEXTHOP = 448,
    CT = 449,
    L3PROTOCOL = 450,
    PROTO_SRC = 451,
    PROTO_DST = 452,
    ZONE = 453,
    DIRECTION = 454,
    EVENT = 455,
    EXPIRATION = 456,
    HELPER = 457,
    LABEL = 458,
    STATE = 459,
    STATUS = 460,
    ORIGINAL = 461,
    REPLY = 462,
    COUNTER = 463,
    NAME = 464,
    PACKETS = 465,
    BYTES = 466,
    AVGPKT = 467,
    COUNTERS = 468,
    QUOTAS = 469,
    LIMITS = 470,
    HELPERS = 471,
    LOG = 472,
    PREFIX = 473,
    GROUP = 474,
    SNAPLEN = 475,
    QUEUE_THRESHOLD = 476,
    LEVEL = 477,
    LIMIT = 478,
    RATE = 479,
    BURST = 480,
    OVER = 481,
    UNTIL = 482,
    QUOTA = 483,
    USED = 484,
    NANOSECOND = 485,
    MICROSECOND = 486,
    MILLISECOND = 487,
    SECOND = 488,
    MINUTE = 489,
    HOUR = 490,
    DAY = 491,
    WEEK = 492,
    _REJECT = 493,
    WITH = 494,
    ICMPX = 495,
    SNAT = 496,
    DNAT = 497,
    MASQUERADE = 498,
    REDIRECT = 499,
    RANDOM = 500,
    FULLY_RANDOM = 501,
    PERSISTENT = 502,
    QUEUE = 503,
    QUEUENUM = 504,
    BYPASS = 505,
    FANOUT = 506,
    DUP = 507,
    FWD = 508,
    NUMGEN = 509,
    INC = 510,
    MOD = 511,
    OFFSET = 512,
    JHASH = 513,
    SYMHASH = 514,
    SEED = 515,
    POSITION = 516,
    COMMENT = 517,
    XML = 518,
    JSON = 519,
    NOTRACK = 520,
    EXISTS = 521,
    MISSING = 522,
    EXTHDR = 523
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
#define FIB 283
#define HOOK 284
#define DEVICE 285
#define TABLE 286
#define TABLES 287
#define CHAIN 288
#define CHAINS 289
#define RULE 290
#define RULES 291
#define SETS 292
#define SET 293
#define ELEMENT 294
#define MAP 295
#define MAPS 296
#define HANDLE 297
#define RULESET 298
#define TRACE 299
#define INET 300
#define NETDEV 301
#define ADD 302
#define UPDATE 303
#define REPLACE 304
#define CREATE 305
#define INSERT 306
#define DELETE 307
#define LIST 308
#define RESET 309
#define FLUSH 310
#define RENAME 311
#define DESCRIBE 312
#define EXPORT 313
#define MONITOR 314
#define ALL 315
#define ACCEPT 316
#define DROP 317
#define CONTINUE 318
#define JUMP 319
#define GOTO 320
#define RETURN 321
#define TO 322
#define CONSTANT 323
#define INTERVAL 324
#define TIMEOUT 325
#define GC_INTERVAL 326
#define ELEMENTS 327
#define POLICY 328
#define MEMORY 329
#define PERFORMANCE 330
#define SIZE 331
#define FLOW 332
#define NUM 333
#define STRING 334
#define QUOTED_STRING 335
#define ASTERISK_STRING 336
#define LL_HDR 337
#define NETWORK_HDR 338
#define TRANSPORT_HDR 339
#define BRIDGE 340
#define ETHER 341
#define SADDR 342
#define DADDR 343
#define TYPE 344
#define VLAN 345
#define ID 346
#define CFI 347
#define PCP 348
#define ARP 349
#define HTYPE 350
#define PTYPE 351
#define HLEN 352
#define PLEN 353
#define OPERATION 354
#define IP 355
#define HDRVERSION 356
#define HDRLENGTH 357
#define DSCP 358
#define ECN 359
#define LENGTH 360
#define FRAG_OFF 361
#define TTL 362
#define PROTOCOL 363
#define CHECKSUM 364
#define ICMP 365
#define CODE 366
#define SEQUENCE 367
#define GATEWAY 368
#define MTU 369
#define OPTIONS 370
#define IP6 371
#define PRIORITY 372
#define FLOWLABEL 373
#define NEXTHDR 374
#define HOPLIMIT 375
#define ICMP6 376
#define PPTR 377
#define MAXDELAY 378
#define AH 379
#define RESERVED 380
#define SPI 381
#define ESP 382
#define COMP 383
#define FLAGS 384
#define CPI 385
#define UDP 386
#define SPORT 387
#define DPORT 388
#define UDPLITE 389
#define CSUMCOV 390
#define TCP 391
#define ACKSEQ 392
#define DOFF 393
#define WINDOW 394
#define URGPTR 395
#define OPTION 396
#define ECHO 397
#define EOL 398
#define MAXSEG 399
#define NOOP 400
#define SACK 401
#define SACK0 402
#define SACK1 403
#define SACK2 404
#define SACK3 405
#define SACK_PERMITTED 406
#define TIMESTAMP 407
#define KIND 408
#define COUNT 409
#define LEFT 410
#define RIGHT 411
#define TSVAL 412
#define TSECR 413
#define DCCP 414
#define SCTP 415
#define VTAG 416
#define RT 417
#define RT0 418
#define RT2 419
#define SEG_LEFT 420
#define ADDR 421
#define HBH 422
#define FRAG 423
#define RESERVED2 424
#define MORE_FRAGMENTS 425
#define DST 426
#define MH 427
#define META 428
#define MARK 429
#define IIF 430
#define IIFNAME 431
#define IIFTYPE 432
#define OIF 433
#define OIFNAME 434
#define OIFTYPE 435
#define SKUID 436
#define SKGID 437
#define NFTRACE 438
#define RTCLASSID 439
#define IBRIPORT 440
#define OBRIPORT 441
#define PKTTYPE 442
#define CPU 443
#define IIFGROUP 444
#define OIFGROUP 445
#define CGROUP 446
#define CLASSID 447
#define NEXTHOP 448
#define CT 449
#define L3PROTOCOL 450
#define PROTO_SRC 451
#define PROTO_DST 452
#define ZONE 453
#define DIRECTION 454
#define EVENT 455
#define EXPIRATION 456
#define HELPER 457
#define LABEL 458
#define STATE 459
#define STATUS 460
#define ORIGINAL 461
#define REPLY 462
#define COUNTER 463
#define NAME 464
#define PACKETS 465
#define BYTES 466
#define AVGPKT 467
#define COUNTERS 468
#define QUOTAS 469
#define LIMITS 470
#define HELPERS 471
#define LOG 472
#define PREFIX 473
#define GROUP 474
#define SNAPLEN 475
#define QUEUE_THRESHOLD 476
#define LEVEL 477
#define LIMIT 478
#define RATE 479
#define BURST 480
#define OVER 481
#define UNTIL 482
#define QUOTA 483
#define USED 484
#define NANOSECOND 485
#define MICROSECOND 486
#define MILLISECOND 487
#define SECOND 488
#define MINUTE 489
#define HOUR 490
#define DAY 491
#define WEEK 492
#define _REJECT 493
#define WITH 494
#define ICMPX 495
#define SNAT 496
#define DNAT 497
#define MASQUERADE 498
#define REDIRECT 499
#define RANDOM 500
#define FULLY_RANDOM 501
#define PERSISTENT 502
#define QUEUE 503
#define QUEUENUM 504
#define BYPASS 505
#define FANOUT 506
#define DUP 507
#define FWD 508
#define NUMGEN 509
#define INC 510
#define MOD 511
#define OFFSET 512
#define JHASH 513
#define SYMHASH 514
#define SEED 515
#define POSITION 516
#define COMMENT 517
#define XML 518
#define JSON 519
#define NOTRACK 520
#define EXISTS 521
#define MISSING 522
#define EXTHDR 523

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 130 "parser_bison.y" /* yacc.c:355  */

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

#line 773 "parser_bison.c" /* yacc.c:355  */
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

#line 803 "parser_bison.c" /* yacc.c:358  */

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
#define YYLAST   4608

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  278
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  274
/* YYNRULES -- Number of rules.  */
#define YYNRULES  832
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1269

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   523

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   273,     2,     2,     2,
     274,   275,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   269,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   276,     2,   277,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   270,   272,   271,     2,     2,     2,     2,
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
     265,   266,   267,   268
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   707,   707,   708,   726,   727,   730,   731,   734,   742,
     756,   764,   765,   766,   767,   799,   800,   801,   802,   803,
     804,   805,   806,   807,   808,   809,   810,   811,   814,   818,
     825,   829,   837,   841,   845,   852,   859,   863,   872,   876,
     880,   885,   891,   897,   901,   908,   912,   920,   927,   934,
     938,   947,   951,   955,   959,   965,   971,   975,   979,   983,
     987,   991,   995,   999,  1003,  1007,  1013,  1017,  1021,  1025,
    1029,  1033,  1037,  1041,  1045,  1049,  1053,  1057,  1061,  1065,
    1069,  1073,  1077,  1081,  1085,  1089,  1093,  1097,  1101,  1107,
    1111,  1115,  1119,  1123,  1127,  1133,  1137,  1141,  1145,  1149,
    1153,  1159,  1166,  1172,  1180,  1189,  1190,  1193,  1194,  1195,
    1196,  1197,  1198,  1199,  1200,  1203,  1204,  1207,  1208,  1211,
    1220,  1226,  1240,  1241,  1242,  1243,  1244,  1255,  1265,  1275,
    1286,  1297,  1306,  1320,  1326,  1327,  1328,  1329,  1330,  1331,
    1339,  1344,  1345,  1346,  1347,  1352,  1357,  1362,  1367,  1372,
    1375,  1376,  1379,  1383,  1386,  1387,  1388,  1392,  1397,  1398,
    1399,  1400,  1411,  1420,  1429,  1438,  1443,  1448,  1451,  1455,
    1461,  1462,  1465,  1479,  1480,  1500,  1505,  1506,  1507,  1508,
    1515,  1516,  1517,  1518,  1525,  1526,  1527,  1528,  1534,  1535,
    1536,  1537,  1544,  1545,  1546,  1547,  1550,  1578,  1579,  1582,
    1583,  1586,  1597,  1598,  1601,  1604,  1605,  1606,  1609,  1624,
    1625,  1628,  1629,  1630,  1631,  1632,  1633,  1636,  1644,  1651,
    1658,  1665,  1672,  1679,  1686,  1694,  1702,  1706,  1713,  1720,
    1732,  1736,  1743,  1747,  1753,  1765,  1771,  1778,  1779,  1780,
    1781,  1782,  1783,  1784,  1785,  1786,  1787,  1788,  1789,  1790,
    1791,  1792,  1793,  1794,  1795,  1798,  1802,  1808,  1814,  1819,
    1828,  1833,  1838,  1841,  1847,  1848,  1850,  1854,  1862,  1866,
    1869,  1873,  1879,  1880,  1883,  1889,  1893,  1896,  1901,  1906,
    1911,  1916,  1921,  1927,  1955,  1959,  1963,  1967,  1971,  1977,
    1981,  1984,  1988,  1994,  2003,  2022,  2030,  2031,  2032,  2035,
    2036,  2039,  2040,  2055,  2071,  2079,  2080,  2081,  2084,  2085,
    2086,  2087,  2102,  2103,  2104,  2105,  2106,  2109,  2112,  2119,
    2123,  2134,  2145,  2155,  2161,  2164,  2169,  2176,  2177,  2178,
    2179,  2180,  2181,  2182,  2183,  2184,  2185,  2188,  2189,  2193,
    2199,  2200,  2206,  2207,  2213,  2214,  2220,  2223,  2224,  2243,
    2244,  2247,  2251,  2254,  2260,  2266,  2277,  2278,  2279,  2282,
    2283,  2284,  2287,  2291,  2295,  2300,  2305,  2309,  2313,  2319,
    2320,  2323,  2326,  2330,  2335,  2341,  2342,  2345,  2348,  2352,
    2356,  2360,  2365,  2372,  2377,  2385,  2392,  2393,  2399,  2400,
    2401,  2404,  2405,  2408,  2414,  2418,  2421,  2426,  2432,  2433,
    2439,  2440,  2443,  2444,  2447,  2453,  2462,  2463,  2466,  2473,
    2482,  2488,  2492,  2495,  2501,  2507,  2524,  2525,  2532,  2541,
    2552,  2553,  2554,  2555,  2556,  2557,  2558,  2559,  2560,  2561,
    2562,  2563,  2566,  2589,  2590,  2591,  2594,  2595,  2596,  2597,
    2598,  2601,  2605,  2608,  2609,  2613,  2619,  2620,  2626,  2627,
    2633,  2634,  2640,  2643,  2644,  2663,  2669,  2675,  2686,  2687,
    2688,  2691,  2697,  2698,  2699,  2702,  2709,  2714,  2719,  2722,
    2726,  2730,  2736,  2737,  2744,  2750,  2751,  2754,  2760,  2764,
    2767,  2771,  2777,  2778,  2781,  2782,  2785,  2786,  2789,  2800,
    2808,  2829,  2837,  2840,  2841,  2844,  2859,  2866,  2871,  2882,
    2904,  2912,  2916,  2920,  2924,  2930,  2936,  2944,  2945,  2946,
    2949,  2950,  2954,  2960,  2961,  2967,  2968,  2974,  2975,  2981,
    2984,  2985,  3004,  3005,  3008,  3016,  3017,  3018,  3019,  3020,
    3021,  3022,  3023,  3024,  3025,  3026,  3027,  3030,  3031,  3032,
    3033,  3034,  3041,  3048,  3055,  3062,  3069,  3076,  3083,  3090,
    3097,  3104,  3113,  3114,  3115,  3116,  3117,  3118,  3121,  3125,
    3129,  3133,  3137,  3141,  3147,  3151,  3155,  3170,  3171,  3174,
    3175,  3176,  3177,  3180,  3181,  3182,  3183,  3184,  3185,  3186,
    3187,  3188,  3189,  3190,  3191,  3192,  3193,  3194,  3195,  3196,
    3197,  3200,  3204,  3208,  3222,  3228,  3229,  3232,  3233,  3236,
    3242,  3247,  3252,  3258,  3259,  3262,  3266,  3286,  3287,  3288,
    3291,  3295,  3299,  3305,  3306,  3309,  3310,  3311,  3312,  3313,
    3314,  3315,  3316,  3317,  3318,  3319,  3320,  3321,  3322,  3323,
    3326,  3327,  3328,  3329,  3330,  3331,  3332,  3335,  3336,  3339,
    3340,  3343,  3344,  3345,  3346,  3349,  3350,  3353,  3359,  3367,
    3380,  3386,  3395,  3396,  3397,  3398,  3399,  3400,  3401,  3402,
    3403,  3404,  3405,  3406,  3407,  3408,  3409,  3410,  3413,  3423,
    3424,  3425,  3428,  3434,  3435,  3436,  3439,  3445,  3446,  3447,
    3448,  3451,  3457,  3458,  3459,  3460,  3461,  3464,  3470,  3471,
    3472,  3473,  3474,  3475,  3476,  3477,  3478,  3479,  3480,  3481,
    3484,  3490,  3491,  3492,  3493,  3494,  3495,  3496,  3499,  3505,
    3506,  3507,  3508,  3509,  3510,  3511,  3512,  3513,  3515,  3521,
    3522,  3523,  3524,  3525,  3526,  3527,  3528,  3531,  3537,  3538,
    3539,  3540,  3541,  3544,  3550,  3551,  3554,  3560,  3561,  3562,
    3565,  3571,  3572,  3573,  3574,  3577,  3583,  3584,  3585,  3586,
    3589,  3593,  3597,  3604,  3605,  3606,  3607,  3608,  3609,  3610,
    3611,  3612,  3613,  3616,  3617,  3618,  3619,  3620,  3621,  3622,
    3623,  3624,  3625,  3626,  3627,  3630,  3631,  3632,  3633,  3634,
    3635,  3636,  3637,  3640,  3646,  3647,  3648,  3651,  3657,  3658,
    3659,  3660,  3663,  3664,  3665,  3666,  3667,  3668,  3669,  3672,
    3678,  3679,  3682,  3688,  3689,  3690,  3691,  3694,  3700,  3706,
    3712,  3715,  3721,  3722,  3723,  3724,  3725,  3726,  3729,  3735,
    3736,  3739,  3745,  3746,  3747,  3748,  3749,  3752,  3766,  3767,
    3768,  3769,  3770
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
  "\"lookup\"", "\"include\"", "\"define\"", "\"fib\"", "\"hook\"",
  "\"device\"", "\"table\"", "\"tables\"", "\"chain\"", "\"chains\"",
  "\"rule\"", "\"rules\"", "\"sets\"", "\"set\"", "\"element\"", "\"map\"",
  "\"maps\"", "\"handle\"", "\"ruleset\"", "\"trace\"", "\"inet\"",
  "\"netdev\"", "\"add\"", "\"update\"", "\"replace\"", "\"create\"",
  "\"insert\"", "\"delete\"", "\"list\"", "\"reset\"", "\"flush\"",
  "\"rename\"", "\"describe\"", "\"export\"", "\"monitor\"", "\"all\"",
  "\"accept\"", "\"drop\"", "\"continue\"", "\"jump\"", "\"goto\"",
  "\"return\"", "\"to\"", "\"constant\"", "\"interval\"", "\"timeout\"",
  "\"gc-interval\"", "\"elements\"", "\"policy\"", "\"memory\"",
  "\"performance\"", "\"size\"", "\"flow\"", "\"number\"", "\"string\"",
  "\"quoted string\"", "\"string with a trailing asterisk\"", "\"ll\"",
  "\"nh\"", "\"th\"", "\"bridge\"", "\"ether\"", "\"saddr\"", "\"daddr\"",
  "\"type\"", "\"vlan\"", "\"id\"", "\"cfi\"", "\"pcp\"", "\"arp\"",
  "\"htype\"", "\"ptype\"", "\"hlen\"", "\"plen\"", "\"operation\"",
  "\"ip\"", "\"version\"", "\"hdrlength\"", "\"dscp\"", "\"ecn\"",
  "\"length\"", "\"frag-off\"", "\"ttl\"", "\"protocol\"", "\"checksum\"",
  "\"icmp\"", "\"code\"", "\"seq\"", "\"gateway\"", "\"mtu\"",
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
  "\"notrack\"", "\"exists\"", "\"missing\"", "\"exthdr\"", "'='", "'{'",
  "'}'", "'|'", "'$'", "'('", "')'", "'['", "']'", "$accept", "input",
  "stmt_separator", "opt_newline", "common_block", "line", "base_cmd",
  "add_cmd", "replace_cmd", "create_cmd", "insert_cmd", "delete_cmd",
  "list_cmd", "reset_cmd", "flush_cmd", "rename_cmd", "export_cmd",
  "monitor_cmd", "monitor_event", "monitor_object", "monitor_format",
  "export_format", "describe_cmd", "table_block_alloc", "table_options",
  "table_block", "chain_block_alloc", "chain_block", "set_block_alloc",
  "set_block", "set_block_expr", "set_flag_list", "set_flag",
  "map_block_alloc", "map_block", "set_mechanism", "set_policy_spec",
  "data_type_atom_expr", "data_type_expr", "obj_block_alloc",
  "counter_block", "quota_block", "ct_helper_block", "limit_block",
  "type_identifier", "hook_spec", "prio_spec", "dev_spec", "policy_spec",
  "chain_policy", "identifier", "string", "time_spec", "family_spec",
  "family_spec_explicit", "table_spec", "chain_spec", "chain_identifier",
  "set_spec", "set_identifier", "obj_spec", "obj_identifier",
  "handle_spec", "position_spec", "rule_position", "ruleid_spec",
  "comment_spec", "ruleset_spec", "rule", "rule_alloc", "stmt_list",
  "stmt", "verdict_stmt", "verdict_map_stmt", "verdict_map_expr",
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
  "set_stmt", "set_stmt_op", "flow_stmt", "flow_stmt_alloc",
  "flow_stmt_opts", "flow_stmt_opt", "match_stmt", "variable_expr",
  "symbol_expr", "integer_expr", "primary_expr", "fib_expr", "fib_result",
  "fib_flag", "fib_tuple", "shift_expr", "and_expr", "exclusive_or_expr",
  "inclusive_or_expr", "basic_expr", "concat_expr", "prefix_rhs_expr",
  "range_rhs_expr", "wildcard_rhs_expr", "multiton_rhs_expr", "map_expr",
  "expr", "set_expr", "set_list_expr", "set_list_member_expr",
  "flow_key_expr", "flow_key_expr_alloc", "set_elem_expr",
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
  "numgen_type", "numgen_expr", "hash_expr", "rt_key_proto", "rt_expr",
  "rt_key", "ct_expr", "ct_dir", "ct_key", "ct_key_dir", "ct_key_proto",
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
     515,   516,   517,   518,   519,   520,   521,   522,   523,    61,
     123,   125,   124,    36,    40,    41,    91,    93
};
# endif

#define YYPACT_NINF -1006

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1006)))

#define YYTABLE_NINF -647

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1006,  4380, -1006,   320, -1006, -1006,    79,     3,  1070,  1070,
    1070,  1070,  1070,  1070, -1006, -1006,   915,   145,   897,   152,
     785,  1286,   120,   307,   187,  3732,    17,   172, -1006, -1006,
   -1006, -1006,    68,  1070,  1070,  1070, -1006, -1006, -1006,   488,
   -1006,     3, -1006,     3,    -2,  3418, -1006,   320, -1006,   110,
       4,    83,  3418,     3, -1006,    87, -1006, -1006,  1070, -1006,
    1070,  1070,  1070,  1070,  1070,    85,  1070,  1070,  1070, -1006,
    1070, -1006,  1070,  1070,  1070,  1070,  1070,  1070,   196,  1070,
    1070,  1070, -1006,  1070,  1070,  1070,  1070,   351,  1070,  1070,
    1070,  1070,   304,   -35,  1070,   742,   765,  1083,  1070,  1070,
   -1006,  1070,  1103,  1329,  1070, -1006,  1070,  1070,  1070,  1070,
    1070,   356, -1006,  1070, -1006,   570,   234, -1006, -1006, -1006,
   -1006,    23,   478,   673,  1720,   820,  1434,  1247,   595,   217,
     276,   260,   235,  1527,   136,    76,   415,   223,   247,    84,
     431,   113,   497,  1741, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006,  1943,    47,  3615,   166,   533,     3,  3732, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   232, -1006,
   -1006, -1006, -1006, -1006, -1006,  1148,  1070,     3,   220,   216,
     285, -1006, -1006, -1006, -1006,   366, -1006,   506, -1006, -1006,
   -1006,     3,     3, -1006, -1006,  2235,  1943,   240, -1006,    30,
      35, -1006, -1006, -1006, -1006, -1006, -1006,   393,   402, -1006,
     448, -1006,   225,  3418, -1006, -1006, -1006, -1006,   317, -1006,
     325, -1006, -1006, -1006,   263, -1006,  2195, -1006,   -12, -1006,
      51, -1006, -1006, -1006,   231, -1006, -1006,    12, -1006, -1006,
     574,   489,   496,   248, -1006,   315, -1006,  2774, -1006, -1006,
   -1006,   487, -1006, -1006, -1006,   492, -1006,  3191,   265,   279,
   -1006, -1006,   290, -1006, -1006, -1006,   292,   491,  3418,     4,
      83, -1006,    87, -1006,  1070,   220,   216,   285,  3418, -1006,
   -1006, -1006, -1006,    87, -1006, -1006,  1070, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,  1070, -1006, -1006, -1006, -1006,
   -1006,  1070,  1070,   534,  1070, -1006,  1070, -1006,  1070, -1006,
    1070, -1006, -1006, -1006, -1006,  1070, -1006,  1070, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,  1070,     3, -1006, -1006, -1006,
   -1006,   566, -1006, -1006, -1006, -1006, -1006,   571,   -33, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006,  1828, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006,     6, -1006, -1006,
     308, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006,  1320, -1006, -1006, -1006, -1006,   336,   161,   346,   527,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006,   340, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006,   232, -1006, -1006,   578,
   -1006, -1006,   368, -1006, -1006, -1006, -1006,   580, -1006, -1006,
   -1006, -1006, -1006,  3732, -1006, -1006,   637,   644,  1320,   646,
    3001,  3001,   368,  3001,   618,  3001,  3615, -1006,  3191,    37,
   -1006,   636, -1006, -1006,   625,   628,   317, -1006,    43,   636,
     631,   640,   650,   636,   325, -1006,   -29, -1006,  3001, -1006,
   -1006,  2385,    23,   478,   673,  1720, -1006,  1434,   185, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006,   602,   695,   713,
     461,   403,   206, -1006, -1006, -1006, -1006, -1006,   729,   385,
     730, -1006, -1006, -1006,   738, -1006, -1006, -1006, -1006, -1006,
     748,   756, -1006,   761, -1006, -1006, -1006, -1006,   771, -1006,
    2575, -1006,   771,  3001, -1006, -1006,   231, -1006,   777, -1006,
       3,  3732,    19, -1006,  3732,  3732,  3732,  3732,  3732,  3732,
      18,  3191, -1006, -1006, -1006, -1006, -1006, -1006, -1006,     3,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006,   806, -1006,   620,   798,   764,   549,   435,
     818, -1006, -1006, -1006,  2842,  3001,  3001,   320,   806, -1006,
   -1006, -1006, -1006, -1006,   753, -1006, -1006,   563,   564,   565,
   -1006,   567, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006,  1070, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006,   760,   234, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   456,
   -1006,   762, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006,   554, -1006,   763,   766,   592, -1006, -1006, -1006,   582,
     642, -1006, -1006,   778,    -4,    46,   -19,   847,  3001,  3001,
     823,  3001, -1006, -1006,   792, -1006,    -4,   833, -1006, -1006,
     448,   634,   -19, -1006,   483,   818,   448, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006,   751,   251, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,   783,   796,   835,   804, -1006,
    3001,   882,  3917,  4155,  3917,  3917,  3917,   816,  3917,  3917,
      57,  3001,   771,  1470,  1470,  3001,   385,  3001,   385, -1006,
   -1006,   397, -1006,   847,  3418,   -19,  3732, -1006, -1006, -1006,
     574,   489,   496, -1006,     3,   448, -1006, -1006,  4155,  4155,
    4155,  4155,  4155,  4155,  4155,   817,  4155,  4155,  3191, -1006,
   -1006, -1006, -1006,   779,  1519,   348,   515, -1006, -1006, -1006,
   -1006, -1006,   626, -1006, -1006,   891, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006,   623, -1006, -1006, -1006,
     592,   116,   824, -1006, -1006,   825,    44, -1006, -1006,   672,
   -1006,   826, -1006,   -19, -1006, -1006, -1006,  3001, -1006,    75,
     672,  3001, -1006,  4087, -1006,   -19,  3191, -1006, -1006, -1006,
   -1006,   899, -1006,   828,   831, -1006,   834, -1006,  3001, -1006,
   -1006, -1006, -1006,   602,   695,   713, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006,   385, -1006,   385,
     771, -1006,   648,   -19,  3418, -1006,  3259,    41, -1006, -1006,
   -1006, -1006,   620,   798,   764, -1006, -1006, -1006, -1006,   666,
       3,     3,     3,   838,   721,     3,     3,     3, -1006, -1006,
   -1006,   320,   617,   846, -1006, -1006, -1006,   320,   320,   320,
     826,   826,   674,   624,   866,    10,   739, -1006, -1006, -1006,
     320,   676,    10,   739, -1006, -1006, -1006,   320,  1168,  1775,
     437,   551, -1006,   873, -1006, -1006,   879, -1006, -1006,   156,
   -1006,   923,   734,   886, -1006, -1006, -1006, -1006, -1006,   923,
     734, -1006, -1006,   448, -1006,   818, -1006,   251, -1006, -1006,
   -1006, -1006,   771,   771, -1006,   694,   961,   448, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006,     3, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,   938, -1006, -1006, -1006,   320,
     320,    87, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006,   532, -1006, -1006, -1006, -1006,   466, -1006, -1006,    87,
     399,   466, -1006, -1006, -1006, -1006, -1006,   215, -1006,   592,
     889,  1070,   320, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006,   734,   892, -1006,    -4,   734, -1006, -1006, -1006, -1006,
     959,  3259, -1006,   701,   702,   704, -1006,   705,   706,   708,
     902, -1006, -1006, -1006,    10, -1006,   739, -1006, -1006,   788,
   -1006,   320, -1006,   875,   320, -1006, -1006,    -6, -1006, -1006,
     448, -1006, -1006, -1006,   714, -1006, -1006, -1006,   955, -1006,
   -1006,   320,   320,   320,   532, -1006,   159, -1006, -1006, -1006,
   -1006, -1006,  1998,   775,  1013, -1006,   222,   252,   115,   909,
     874, -1006, -1006, -1006, -1006, -1006, -1006,   320,   320,   320,
     320,   305,   320, -1006, -1006, -1006,   320, -1006, -1006, -1006,
     320, -1006, -1006, -1006, -1006,    69, -1006, -1006, -1006, -1006,
     320, -1006, -1006, -1006,   912, -1006, -1006, -1006, -1006
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,   209,   209,
     209,   209,   209,   209,   213,   216,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,   215,   214,
     211,   212,     0,   209,   209,   209,    12,    11,     3,     0,
      15,     0,   210,     0,   226,     0,    10,     0,   204,     0,
      28,    30,     0,     0,   140,     0,   157,    16,   209,    17,
     209,   209,   209,   209,   209,     0,   209,   209,   209,    18,
     209,    19,   209,   209,   209,   209,   209,   209,     0,   209,
     209,   209,    20,   209,   230,   209,   230,   230,   209,   209,
     230,   230,     0,     0,   209,   230,   230,   230,   209,   209,
      21,   209,   230,   230,   209,    22,   209,   209,   209,   209,
     230,     0,    23,   209,    24,     0,     0,   419,   205,   206,
     207,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   573,   574,   575,   576,   577,   578,
     579,   580,   581,   582,   583,   584,   585,   586,   587,   588,
     589,   590,     0,     0,     0,     0,     0,     0,     0,    27,
     417,   416,   420,   421,   119,   430,   425,   565,   428,   429,
     426,   427,   422,   652,   653,   654,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   664,   665,   666,   667,   423,
     792,   793,   794,   795,   796,   797,   798,   424,     0,   117,
     118,    25,   103,   106,    26,   107,   209,     0,    37,     0,
     298,    14,    13,   217,   218,     0,   227,     0,   558,   559,
     560,     0,     0,   563,   410,     0,     0,   266,   274,     0,
     298,   318,   325,   326,   371,   377,   393,     0,     0,   594,
       7,    33,   232,   234,   235,   237,   256,   240,   264,   243,
     272,   244,   245,   246,   319,   247,     0,   250,   370,   251,
     376,   252,   253,   248,   391,   254,   239,     0,   238,   443,
     446,   448,   450,   452,   453,   462,   464,     0,   463,   414,
     255,   565,   242,   249,   241,   422,     8,     0,     0,     0,
      32,   220,     0,    36,   151,   150,     0,     0,     0,    43,
      45,   140,     0,   157,   209,    50,     0,   298,     0,    56,
      57,    58,    59,     0,    60,   492,   209,    62,    65,    63,
      66,   231,    67,    68,    69,   209,    70,    72,    86,    85,
      82,   209,   230,     0,   209,    75,   209,    73,   209,    76,
     209,    79,    81,    78,    91,   209,    89,   209,    92,    94,
      95,    96,    97,    98,   100,   209,     0,   669,   670,   671,
     418,     0,   436,   437,   438,   439,   440,   442,     0,   673,
     674,   675,   672,   680,   677,   678,   679,   676,   682,   683,
     684,   685,   686,   681,   698,   699,   693,   688,   689,   690,
     691,   692,   694,   695,   696,   697,   687,   701,   704,   703,
     702,   705,   706,   707,   700,   716,   717,   709,   710,   711,
     713,   712,   714,   715,   708,   719,   724,   721,   720,   725,
     723,   722,   726,   718,   729,   732,   728,   730,   731,   727,
     735,   734,   733,   737,   738,   739,   736,   743,   744,   741,
     742,   740,   749,   746,   747,   748,   745,   761,   755,   758,
     759,   753,   754,   756,   757,   760,   762,     0,   750,   786,
     784,   785,   783,   791,   788,   789,   790,   787,   805,   603,
     804,   609,   604,   803,   806,   607,   608,     0,   605,   802,
       0,   807,   810,   809,   801,   800,   799,   817,   814,   812,
     813,   815,   816,   811,   820,   819,   818,   824,   823,   826,
     822,   825,   821,   566,   569,   570,   571,   572,   564,   567,
     568,   623,   624,   616,   617,   615,   625,   626,   644,   619,
     628,   621,   622,   627,   618,   620,   613,   614,   642,   641,
     643,     0,   610,   629,   598,   597,     0,   462,     0,     0,
     829,   828,   830,   831,   832,   827,   415,     0,   102,   108,
     109,   111,   110,   113,   114,   112,   115,   497,   222,     0,
     489,    38,   307,   500,    41,   296,   297,     0,   491,    39,
     225,   406,   407,     0,   561,   562,   566,   564,     0,   610,
       0,     0,   307,     0,     0,     0,     0,     6,     0,     0,
     466,     0,   233,   236,     0,     0,   265,   268,     0,     0,
       0,     0,     0,     0,   273,   275,     0,   317,     0,   355,
     533,     0,   525,   528,   529,   526,   532,   527,     0,   536,
     534,   535,   531,   530,   522,   523,   337,   340,   342,   344,
     346,   347,   352,   359,   356,   357,   358,   360,   362,   324,
     327,   328,   524,   329,   336,   330,   333,   334,   331,   332,
       0,   361,   335,     0,   388,   389,   390,   369,   374,   386,
       0,   375,   380,     0,   400,   401,   392,   394,   397,   398,
       0,     0,     0,   411,     0,     0,     0,     0,     0,     0,
       0,     0,   552,   553,   554,   555,   556,   557,   457,     0,
     525,   528,   529,   526,   546,   527,   547,   545,   544,   548,
     542,   543,   541,   549,   550,   551,   537,   538,   458,   459,
     460,   508,   509,   502,   501,   513,   515,   517,   519,   520,
     507,   539,   540,   510,     0,     0,     0,     0,   487,   486,
     122,   134,   141,   158,     0,   228,    42,     0,     0,     0,
      49,     0,   497,    51,    54,    52,    55,    61,   497,    71,
      84,    83,   209,    87,    74,    77,    80,    90,    93,    99,
     101,     0,     0,   435,   433,   434,   432,   766,   773,   763,
     765,   764,   768,   769,   770,   771,   772,   767,   774,   752,
     606,     0,   630,   631,   637,   633,   638,   632,   634,   635,
     611,     0,   636,     0,     0,   595,   431,   104,   116,     0,
       0,   305,   306,     0,     0,     0,   402,   404,     0,     0,
     636,     0,   267,   295,     0,   304,     0,   383,   385,   483,
       7,     7,   475,   477,   520,   482,     7,   465,   229,   270,
     271,   269,   288,   287,     0,     0,   286,   282,   277,   278,
     279,   280,   283,   281,   276,     0,     0,     0,     0,   366,
       0,   363,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   368,     0,     0,     0,     0,     0,   378,   396,
     395,     0,   413,   474,     0,   472,     0,   412,   444,   445,
     447,   449,   451,   454,     0,     7,   257,   461,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   503,
     592,   651,     9,     0,     0,     0,     0,   224,   122,   134,
     141,   158,     0,    64,    88,     0,   441,   777,   776,   775,
     778,   779,   780,   781,   782,   751,     0,   639,   640,   612,
     595,   595,     0,   602,   184,     0,     0,   300,   299,   301,
     405,     0,   481,   403,   478,   593,   591,     0,   649,     0,
     301,     0,   469,     0,   470,   476,   468,   467,   285,   291,
     292,   284,   290,     0,     0,   323,     0,   367,     0,   338,
     327,   336,   339,   341,   343,   345,   353,   354,   348,   351,
     350,   349,   364,   645,   646,   647,   648,   372,   387,   379,
     381,   399,     0,   473,     0,   259,     0,     0,   260,   506,
     511,   512,   514,   516,   518,   505,   455,   456,   521,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,   124,
     123,     0,     0,     0,    31,   136,   135,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,   143,   142,
       0,     0,     0,     0,    35,   160,   159,     0,     0,     0,
       0,     0,   184,     0,   808,   599,     0,   601,   596,     0,
     488,     0,   308,     0,   490,   208,   480,   479,   650,     0,
     308,   303,   384,     7,   520,   484,   485,     0,   320,   321,
     322,   365,   373,   382,   409,     0,     0,     7,   258,   504,
     219,   133,   221,   140,   157,   121,     0,   223,   175,   175,
     175,   125,   202,   203,   201,     0,   137,   138,   139,     0,
       0,     0,   171,   170,   168,   169,   192,   194,   195,   193,
     173,     0,   172,   154,   155,   156,     0,   153,   149,     0,
       0,     0,   167,    44,    46,    47,    48,     0,   668,   595,
       0,     0,     0,   186,   185,   187,   312,   313,   314,   315,
     316,   308,     0,   499,     0,   308,   294,   471,   289,   408,
       0,   262,   261,     0,     0,     0,   175,     0,     0,     0,
       0,   146,   147,   148,     0,   144,     0,   145,   166,     0,
     165,     0,   600,     0,     0,    40,   498,     0,   302,   293,
       7,   134,   141,   158,     0,   176,   188,   180,   200,   174,
     152,     0,     0,     0,     0,    53,     0,   496,   311,   309,
     310,   263,     0,     0,     0,   184,     0,     0,     0,     0,
       0,   162,   164,   163,   161,   494,   493,     0,     0,     0,
       0,     0,     0,   178,   177,   179,     0,   190,   189,   191,
       0,   182,   181,   183,   199,     0,   495,   126,   127,   128,
       0,   129,   132,   130,     0,   197,   196,   131,   198
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1006, -1006,    -1,  -797,     5, -1006, -1006,   976, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006,  -183, -1006,   685, -1006,    77,  -298,  -888,  -303,  -884,
    -307,   -56,  -188,  -300,  -889,  -887, -1006,  -185,  -999, -1005,
   -1006, -1006,  -995, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
      33,  -151,  -266, -1006,   -25,  1389,   490, -1006,    88,   -21,
     367,  -933, -1006, -1006,    58,   930,   758,   388,    -3, -1006,
   -1006,  -239, -1006, -1006, -1006, -1006,   -92, -1006, -1006, -1006,
     406, -1006, -1006, -1006,   412, -1006, -1006, -1006,   -60, -1006,
     789,  -800,    73, -1006,   436,  -993,   -47, -1006, -1006, -1006,
   -1006, -1006,  -730,   170,   176,   177, -1006,   179, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,  -460, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,  -235,   169, -1006, -1006, -1006,
     372, -1006,   171, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
     369, -1006,   -52,   480,   -24,    -8, -1006, -1006, -1006,   300,
     378,   390,   391, -1006,  -150,  -157, -1006, -1006, -1006,  -575,
   -1006,  -140,   -40, -1006,   244,   197, -1006,  -954, -1006,  -710,
    -869, -1006, -1006, -1006,  -144,   769,  -138,   776,   995, -1006,
   -1006,  -563,  -135,   784, -1006,   797,  -275,   194,   201,   203,
   -1006,  -278,  -578, -1006,  -109,   405,  -708, -1006,  -918,   -15,
     869, -1006,   -41, -1006,  -883, -1006,     2,    38, -1006,    54,
     621,    63,   871,   876, -1006, -1006, -1006,  -432,   -45, -1006,
   -1006, -1006,    72, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1035,   598,  1036,    38,    39,    40,    59,    69,
      71,    82,   100,   105,   112,   114,   211,   214,   215,   566,
     807,   212,   169,   298,  1031,   913,   299,   914,   302,   915,
     303,  1136,  1137,   306,   916,  1050,  1124,  1130,  1131,  1177,
    1226,  1228,  1069,  1227,  1132,  1037,  1266,  1230,  1038,  1114,
    1107,   170,  1076,    41,    42,   217,    44,  1101,    54,  1103,
     218,  1108,   745,   226,    45,   308,   952,   332,  1039,   252,
     253,   254,   255,   256,   896,  1007,  1008,   257,   258,   606,
     607,   259,   260,   614,   615,   853,   847,   971,   972,   261,
     577,   949,  1074,   262,   813,  1163,  1161,   263,   264,   617,
     265,   266,   636,   637,   638,   639,   640,   641,   642,   989,
     643,   644,   645,   646,   647,   648,   649,   267,   268,   667,
     269,   270,   671,   271,   272,   668,   669,   273,   274,   676,
     677,   678,   679,   815,   816,   275,   583,   276,   277,   682,
     683,   278,   171,   172,   651,   279,   175,   776,   377,   378,
     280,   281,   282,   283,   284,   285,   718,   719,   720,   721,
     286,   287,   288,   599,   600,   884,   885,   831,   832,   953,
     954,   833,  1083,   737,   570,   571,   578,   579,   326,  1237,
    1155,   809,   573,   574,   289,   723,   724,   725,   726,   727,
     728,   834,   730,   652,   653,   654,   733,   734,   290,   655,
     518,   519,   177,   292,   943,   546,   656,   657,   487,   658,
     488,   659,   541,   542,   800,   801,   939,   543,   660,   661,
     293,   294,   662,   183,   371,   184,   382,   185,   387,   186,
     393,   187,   406,   188,   414,   189,   424,   190,   433,   191,
     439,   192,   442,   193,   446,   194,   451,   195,   456,   196,
     468,   789,   935,   197,   472,   198,   477,   199,   200,   496,
     201,   489,   202,   491,   203,   493,   204,   503,   205,   506,
     206,   512,   207,   555
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,   173,    46,   304,   291,   750,    37,   547,   749,   729,
     176,   291,   748,   751,   603,   305,   757,   174,   557,   729,
     835,   173,   739,   829,   548,   558,   960,   178,   173,  1057,
     176,  1059,  1061,   962,   964,   672,  1060,   176,   222,   966,
      49,   894,   251,   680,   836,  1086,   296,   178,  1097,   300,
     680,   951,  1096,  1140,   178,   663,   773,  1065,  1067,   331,
     208,   331,   331,   179,  1071,   331,   331,  1147,    52,   699,
     331,   331,   331,  1218,   223,   947,   224,   331,   331,   180,
     699,   855,    48,   179,  1077,   331,   301,  1166,   181,  1126,
     179,  1264,   856,  1109,  1110,  1079,  1077,   182,  1006,   180,
      55,    56,   520,   842,  1178,  1179,   180,   857,   181,   802,
     379,   380,   381,  1127,  1128,   181,     3,   295,   670,     4,
     481,     5,   965,  1072,   295,   118,   119,   120,   318,   843,
     822,   823,   979,   825,  1077,   827,   118,   119,   120,   988,
     173,     6,     7,   844,   173,   774,   775,  1265,   370,   176,
     311,   312,   313,   176,  1080,   982,   820,     3,   859,    47,
       4,   861,     5,   322,   323,   324,   178,   325,  1196,   689,
     178,  1204,  1199,  1176,  1057,  1003,   337,   338,   731,   845,
      58,   343,     6,     7,  1129,   473,   494,    70,   731,   922,
    1214,  1010,  1011,  -298,   520,   923,   362,   363,   485,   486,
     556,   691,   179,   495,  1219,  1220,   179,   948,   474,   475,
     878,   858,   291,   879,   869,   504,     3,  1096,   180,     4,
     113,     5,   180,     3,   846,   469,     4,   181,     5,   173,
    1241,   181,   505,   664,   665,   666,   182,   476,   176,   591,
     182,     6,     7,   601,   593,  1150,   870,   722,     6,     7,
     568,   213,  1200,     3,   592,   178,     4,   722,     5,   225,
     304,   575,   576,   717,   584,   585,  1192,   291,   470,   471,
     216,   304,   305,   717,  -120,   910,   911,   291,     6,     7,
     209,   210,   681,   305,   173,   479,  1167,   314,   895,   886,
    1235,   179,   544,   176,   173,  1236,   664,   665,   666,   481,
    1171,   482,   545,   176,  1150,   746,     3,   180,   837,     4,
     178,     5,  1098,  1222,  1224,   756,   181,   331,  1223,   167,
     178,   372,   373,   689,     4,   295,     5,   250,   101,   440,
     167,     6,     7,   102,   103,   341,   342,  1057,   106,   690,
     107,   575,   576,   441,   452,   108,   179,   109,   104,     3,
     110,  1151,     4,  -133,     5,   691,   179,   250,   955,   956,
     167,   958,   180,   969,  1198,   447,   970,   453,   454,   448,
     455,   181,   180,   942,     6,     7,  1066,   485,   486,   297,
     295,   181,   335,   808,   111,  1085,  1250,   365,   835,   490,
     295,   829,   449,   450,  1150,   443,    14,    15,   325,   770,
     977,   219,   220,  1221,  1189,   444,   445,  1184,   374,   375,
    1151,   992,   376,   492,   872,   997,   897,   999,  1040,  1041,
    1042,  1043,   549,   867,  1044,   868,   817,  1152,   835,   760,
     569,   829,   569,   315,   316,   317,    28,  1045,     3,   547,
     572,     4,   904,     5,   580,    29,   327,   328,   329,   590,
     838,    30,   597,   769,   608,   905,   828,   906,   848,   909,
     595,   345,   852,     6,     7,   352,   353,    31,   354,   596,
       4,   359,     5,  1186,   334,   336,   572,  1046,   339,   340,
     673,   674,   675,   347,   349,   351,  1191,   601,   221,   731,
     356,   358,     4,  1242,     5,   209,   210,  1078,   364,    51,
    1151,  1082,   616,   905,   478,   906,   686,  1040,  1041,  1042,
    1043,   575,   576,  1044,   687,   479,     3,   480,  1091,     4,
     688,     5,   497,  1246,   883,   735,  1045,   604,   605,   481,
     736,   482,   927,   744,   483,   740,     4,   498,     5,   893,
    1184,     6,     7,   609,   610,   611,   612,   613,   307,   741,
     499,   310,     3,   581,   582,     4,   500,     5,   830,   173,
     742,   928,   743,   320,   307,   762,  1046,   383,   176,   384,
     385,   386,   173,   771,   717,   333,  1260,     6,     7,   772,
     484,   176,   731,   567,   791,   178,   507,  1051,  1043,   684,
     685,  1044,   803,   835,   811,   812,   829,   361,   178,   508,
     501,   502,   804,   366,  1052,   805,   509,   485,   486,   929,
     930,   931,   932,   933,   934,   806,   510,   862,   863,  1047,
    1009,   179,   511,  1051,  1043,   731,  1015,  1044,  1017,  1018,
     664,   665,   666,  1019,   179,   899,   900,   180,   597,   963,
    1052,   937,   938,  1000,  1053,  1002,   181,   674,   675,    48,
     180,   722,   367,   368,   369,   182,   810,   173,   814,   181,
     173,   173,   173,   173,   173,   173,   176,   717,   182,   176,
     176,   176,   176,   176,   176,   818,   888,   889,  1112,  1113,
    1053,   752,   819,   178,   821,  1084,   178,   178,   178,   178,
     178,   178,   732,   758,   722,   550,   826,   434,  1122,  1123,
     551,   552,   732,   839,   553,   554,   840,   435,  1145,   849,
     717,   763,   864,   882,   436,   118,   119,   120,   850,   179,
     437,   438,   179,   179,   179,   179,   179,   179,   851,   883,
     761,   865,   370,   866,   871,   180,   912,  -645,   180,   180,
     180,   180,   180,   180,   181,  -646,   650,   181,   181,   181,
     181,   181,   181,   182,   731,   873,   182,   182,   182,   182,
     182,   182,  1092,   874,  1093,  1095,   875,   716,   388,   389,
     390,   391,   392,   346,  1119,  1120,     3,   716,   876,     4,
       3,     5,   902,     4,   881,     5,  1054,    14,    15,   731,
     731,   731,   731,   731,   731,   731,   348,   731,   731,   731,
    1174,     6,     7,  1173,  1175,     6,     7,  1133,  1134,  1135,
      14,    15,  1020,   898,  1183,   901,    72,  1021,    73,  1022,
      74,   903,  1146,    75,    76,    77,   907,    28,   995,   996,
     991,   917,  1188,   918,   919,   920,    29,   921,   925,   717,
     936,   940,    30,   291,   941,  1040,  1041,  1042,  1043,   942,
      28,  1044,   944,   945,   731,   689,   946,   731,    31,    29,
     173,   957,   173,   961,  1045,    30,   968,  1126,   722,   176,
     959,   176,   973,   291,   717,   717,   717,   717,   717,   717,
     717,    31,   717,   717,   717,   974,   178,   978,   178,   975,
     173,  1127,  1128,   976,   986,  1016,  1062,   731,  1063,   176,
    1064,  1073,  1068,  1070,  1046,  1075,  1087,  1088,  1023,   407,
    1089,   408,  1029,  1090,  1048,  1055,   178,  1105,  1030,  1094,
    1049,  1056,   179,  1106,   179,  1115,   830,  1005,    60,   409,
      61,   410,   411,   412,   413,    62,    63,    64,   180,   717,
     180,  1099,   717,  1121,  1125,  1139,     8,   181,     9,   181,
      10,  1148,   179,    11,    12,    13,   295,  1149,   182,  1162,
      14,    15,  1129,   291,  1164,  1169,  1170,  1180,   180,  1193,
    1197,  1201,  1202,  1024,  1203,  1205,  1206,   181,  1207,    78,
     173,  1208,   717,  1216,  1225,  1229,   295,  1025,  1254,   176,
    1268,  1255,    57,    79,   747,  1058,  1211,  1141,  1210,  1209,
      28,  1104,  1026,   732,   321,  1172,   178,  1027,    80,    29,
     602,  1212,   841,    81,     3,    30,  1213,     4,   291,     5,
     228,   229,   230,   231,   232,   233,   854,  1168,   824,   594,
    1111,    31,  1165,  1081,   983,   173,  1116,  1117,  1118,     6,
       7,   984,   179,   985,   176,   998,  1239,   987,   880,  1138,
    1028,   887,  1001,  1100,  1102,  1102,  1142,  1029,   180,  1048,
    1055,   178,   731,  1030,   890,  1049,  1056,   181,  1153,   304,
     650,   650,   926,   650,  1154,   650,   295,   891,   716,   892,
     967,   305,  1245,  1004,   753,  1051,  1043,   304,   344,  1044,
    1253,    65,  1249,   755,   738,  1012,   732,   179,   650,   305,
     754,   650,  1052,  1013,   587,    66,  1014,   588,   790,    32,
       0,     0,   589,   180,   350,    14,    15,     0,  1181,  1182,
      67,     0,   181,    33,     0,    68,  1194,     0,    14,    15,
    1185,   295,     0,     0,   355,  1187,     0,     0,    34,   732,
    1190,     0,  1053,    35,     0,     0,  1153,   717,    14,    15,
     650,  1195,  1154,   650,     0,    28,  1156,  1157,  1158,  1159,
    1160,     0,     0,     0,    29,     0,     0,     0,    28,     3,
      30,   716,     4,     0,     5,     0,     0,    29,     0,     0,
     559,   291,   560,    30,   561,   562,    31,     0,    28,     0,
    1215,   563,   564,  1217,     6,     7,     0,    29,   173,    31,
       0,  1020,     0,    30,     0,     0,  1021,   176,  1022,     0,
    1231,  1232,  1233,  1234,   716,   650,   650,     0,     0,    31,
     565,     0,  1048,  1055,   178,  1243,  1247,  1251,  1049,  1056,
       0,  1244,  1248,  1252,     0,     0,  1256,  1257,  1258,  1259,
    1153,  1261,     0,     0,     0,  1262,  1154,     0,     0,  1263,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1267,
     179,     0,     0,     0,     0,     0,     0,   981,   732,   981,
     981,   981,     0,   981,   981,     0,   180,     0,   994,   994,
       0,     0,     0,     0,  1240,   181,     0,     0,     0,     0,
       0,     0,     0,     0,   295,   950,     0,  1023,   650,   650,
       0,   650,     0,   732,   732,   732,   732,   732,   732,   732,
       0,   732,   732,   732,     0,     0,     0,    83,    84,    85,
      86,     0,     0,    87,    88,     0,    89,    90,     0,    91,
       0,     0,     0,     0,     0,     0,   425,     0,   426,     0,
     650,     0,   980,   716,   980,   980,   980,     0,   980,   980,
     990,   650,     0,   993,   993,   650,   427,   650,   428,   429,
     357,   430,  1024,    92,     0,     0,     0,     0,   732,   431,
     432,   732,     0,     0,    14,    15,  1025,     0,   716,   716,
     716,   716,   716,   716,   716,     0,   716,   716,   716,     0,
      43,  1026,     0,     0,     0,     0,  1027,    50,    43,    43,
      53,    53,    53,     0,     0,    43,     0,   792,   793,     0,
       0,   732,     0,     0,    28,     0,     0,     0,     0,     0,
     794,     0,     0,    29,     0,     0,     0,     0,   795,    30,
       0,     0,     0,     0,     0,     0,   796,   650,     0,  1143,
       0,   650,     0,   716,     0,    31,   716,    43,     0,   309,
      43,    53,    53,    53,     0,     0,     0,     0,   650,    43,
       0,   319,    43,    43,    53,    53,    53,     0,     0,     0,
       0,     0,   330,     0,    43,     0,     0,    53,    53,     0,
      93,     0,     0,     0,     0,     0,   716,     0,     0,     0,
       0,     0,     0,   699,    94,   360,    43,    53,    53,    95,
      96,    97,    43,     0,     0,     0,     0,     0,     0,    98,
       0,     0,     0,     0,    99,   797,   798,   799,   528,     0,
       3,   415,   416,     4,   620,     5,     0,     0,     0,     0,
     538,   539,   540,     0,     0,   417,     0,   418,   419,   420,
       0,     0,   115,     0,     0,     6,     7,   116,     0,   118,
     119,   120,   421,   422,   423,     0,   700,   227,     0,     0,
     701,     0,     0,     0,   702,     0,     0,     0,     0,     0,
     703,     0,     0,     0,   626,     0,   732,     0,     0,     0,
     228,   229,   230,   231,   232,   233,   705,     0,     0,     0,
       0,     0,  1032,     0,     0,     0,   234,   117,   118,   119,
     120,     0,     0,     0,     0,   121,     0,     0,  1033,   122,
       0,     0,     0,   123,     0,     0,     0,     0,     0,   124,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   125,
       0,     0,     0,     0,     0,   126,   457,     0,     0,   458,
     127,     0,     0,   128,     0,     0,   129,   130,     0,     0,
     131,   716,   459,   132,     0,   133,   460,     0,     0,   461,
     462,     0,     0,     0,   463,   464,   465,   466,   467,     0,
       0,     0,     0,   629,     0,     0,   630,   631,   134,   135,
       0,   136,   137,   138,     0,     0,   139,   140,     0,     0,
     141,   142,   235,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   632,   633,   236,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   759,     0,     0,   237,     0,     0,
      53,     0,     0,     0,     0,   764,   238,   765,     0,   766,
       0,     0,   239,   167,   767,     0,   768,   240,     0,     0,
       0,     0,     0,     0,    53,     0,     0,   241,     0,     0,
     242,   243,   244,   245,     0,     0,     0,   246,     0,     0,
       0,   247,   248,   163,     0,     0,     3,   164,   165,     4,
       0,     5,     0,     0,   249,     0,     0,   166,     0,   250,
    1034,     0,   167,   168,     0,     0,     0,     0,   115,     0,
       0,     6,     7,   116,     0,     0,     0,   394,   395,     0,
       0,   396,     0,   227,     0,     0,     0,     0,     0,     0,
     513,   397,   398,   399,   400,   401,   402,   403,   404,   405,
       0,     0,     0,     0,     0,     0,   228,   229,   230,   231,
     232,   233,     0,     0,     0,     0,   514,     0,  1032,   515,
       0,     0,   234,   117,   118,   119,   120,     0,   516,     0,
       0,   121,     0,     0,  1033,   122,     0,     0,     0,   123,
       0,     0,     0,     0,     0,   124,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   125,     0,     0,     0,     0,
       0,   126,     0,     0,     0,     0,   127,     0,     0,   128,
       0,     0,   129,   130,     0,     0,   131,     0,     0,   132,
       0,   133,     0,     0,     0,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,     0,   134,   135,     0,   136,   137,   138,
       0,     0,   139,   140,     0,     0,   141,   142,   235,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   777,     0,   236,
     778,   779,   780,   781,   782,   783,   784,   785,   786,   787,
     788,     0,     0,   237,     0,     0,   517,     0,     0,     0,
       0,     0,   238,     0,     0,     0,     0,     0,   239,     3,
       0,     0,     4,   240,     5,     0,     0,     0,     0,     0,
       0,     0,     0,   241,     0,     0,   242,   243,   244,   245,
       0,   115,     0,   246,     6,     7,   116,   247,   248,   163,
     521,   522,     0,   164,   165,     0,   227,     0,     0,     0,
     249,     0,     0,   166,     0,   250,  1144,     0,   167,   168,
       0,   523,     0,     0,     0,     0,     0,     0,     0,   228,
     229,   230,   231,   232,   233,     0,     0,     0,     0,     0,
       0,  1032,     0,     0,     0,   234,   117,   118,   119,   120,
       0,     0,     0,     0,   121,     0,     0,  1033,   122,     0,
       0,     0,   123,     0,     0,     0,     0,     0,   124,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   125,     0,
       0,     0,     0,     0,   126,     0,     0,   524,     0,   127,
       0,     0,   128,     0,     0,   129,   130,     0,     0,   131,
       0,     0,   132,     0,   133,     0,     0,     0,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   924,     0,   538,   539,   540,     0,   134,   135,     0,
     136,   137,   138,     0,     0,   139,   140,     0,     0,   141,
     142,   235,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
       0,     0,   236,     0,     0,     0,     0,     0,     0,     0,
     618,     0,     0,     0,     0,     0,   237,     0,     0,     0,
       0,     0,     0,     0,     0,   238,   619,     0,   115,     0,
       0,   239,     0,     0,     0,     0,   240,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   241,     0,     0,   242,
     243,   244,   245,     0,     0,     0,   246,     0,     0,   620,
     247,   248,   163,     0,     0,     0,   164,   165,     0,     0,
       0,     0,   621,   249,     0,     0,   166,     0,   250,  1238,
       0,   167,   168,   117,   118,   119,   120,     0,     0,     0,
       0,   622,     0,     0,     0,   623,     0,     0,     0,   624,
       0,     0,     0,     0,     0,   625,     0,     0,     0,   626,
       0,     0,     0,     0,     0,   125,     0,     0,     0,     0,
       0,   627,     0,     0,   586,     0,   127,     0,     0,   128,
       0,     0,   129,   130,     0,     0,   131,     0,     0,   132,
       0,   133,     0,     0,     0,     0,     0,     0,     0,     0,
     514,     0,     0,   515,     0,     0,     0,     0,     0,     0,
       0,     0,   516,     0,   134,   135,     0,   628,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,     0,     0,   162,
     860,     0,     0,     0,     0,     0,     0,     0,   629,     0,
       0,   630,   631,     0,     0,     0,   619,     0,   115,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   632,   633,     0,   620,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   163,
       0,     0,     0,   164,   165,     0,     0,     0,     0,     0,
       0,   634,   635,   117,   118,   119,   120,     0,   167,     0,
       0,   622,     0,     0,     0,   623,     0,     0,     0,   624,
     517,     0,     0,     0,     0,   625,     0,     0,     0,   626,
       0,     0,     0,     0,     0,   125,     0,     0,     0,     0,
       0,   627,     0,     0,     0,     0,   127,     0,     0,   128,
       0,     0,   129,   130,     0,     0,   131,     0,     0,   132,
       0,   133,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   134,   135,     0,   628,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,     0,     0,   162,
     877,     0,     0,     0,     0,     0,     0,     0,   629,     0,
       0,   630,   631,     0,     0,     0,   619,     0,   115,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   632,   633,     0,   620,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   163,
       0,     0,     0,   164,   165,     0,     0,     0,     0,     0,
       0,   634,   635,   117,   118,   119,   120,     0,   167,     0,
       0,   622,     0,     0,     0,   623,     0,     0,     0,   624,
       0,     0,     0,     0,     0,   625,     0,     0,     0,   626,
       0,     0,     0,     0,     0,   125,     0,     0,     0,     0,
       0,   627,     0,     0,     0,     0,   127,     0,     0,   128,
       0,     0,   129,   130,     0,     0,   131,     0,     0,   132,
       0,   133,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   134,   135,     0,   628,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,     0,     0,   162,
       0,     0,     0,     0,     0,     0,     0,     0,   629,     0,
       0,   630,   631,   692,   693,   694,   695,   696,   697,     0,
       0,     0,     0,     0,     0,   698,     0,   699,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   632,   633,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   620,   163,
       0,     0,     0,   164,   165,     0,     0,     0,     0,     0,
       0,   634,   635,     0,     0,     0,     0,     0,   167,     0,
       0,     0,   117,   118,   119,   120,     0,     0,     0,     0,
     700,     0,     0,   698,   701,   699,     0,     0,   702,     0,
       0,     0,     0,     0,   703,     0,     0,     0,   626,     0,
       0,     0,     0,     0,   704,     0,     0,     0,     0,     0,
     705,     0,     0,     0,     0,   706,   620,     0,   707,     0,
       0,   708,   709,     0,     0,   710,     0,     0,   711,     0,
     712,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,   119,   120,     0,     0,     0,     0,   700,     0,
       0,     0,   701,   713,   714,     0,   702,     0,     0,     0,
       0,     0,   703,     0,     0,     0,   626,     0,     0,     0,
       0,     0,   704,     0,     0,     0,     0,     0,   705,     0,
       0,     0,     0,   706,     0,     0,   707,     0,     0,   708,
     709,     0,     0,   710,     0,     0,   711,   629,   712,     0,
     630,   631,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   713,   714,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   632,   633,     0,   715,     0,
       0,     0,   619,     0,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     634,   635,     0,     0,   250,   629,     0,   167,   630,   631,
       0,     0,     0,     0,     0,   620,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   632,   633,     0,   715,   622,     0,     0,
       0,   623,     0,     0,     0,   624,     0,     0,     0,     0,
       0,   625,     0,     0,     0,   626,     0,     0,   634,   635,
       0,   125,   250,     0,     0,   167,   908,   627,     0,     0,
       0,     0,   127,     0,     0,   128,     0,     0,   129,   130,
       0,     0,   131,     0,     0,   132,     0,   133,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     134,   135,     0,   628,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,     0,     0,   162,     0,     0,     0,     0,
       0,     0,     0,     0,   629,     0,     0,   630,   631,     0,
       0,     0,   698,     0,   699,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   632,   633,     0,   620,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   163,     0,     0,     0,   164,
     165,     0,     0,     0,     0,     0,     0,   634,   635,   117,
     118,   119,   120,     0,   167,     0,     0,   700,     0,     0,
     698,   701,   699,     0,     0,   702,     0,     0,     0,     0,
       0,   703,     0,     0,     0,   626,     0,     0,     0,     0,
       0,   704,     0,     0,     0,     0,     0,   705,     0,     0,
       0,     0,   706,   620,     0,   707,     0,     0,   708,   709,
       0,     0,   710,     0,     0,   711,     0,   712,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,   119,
     120,     0,     0,     0,     0,   700,     0,     0,     0,   701,
     713,   714,     0,   702,     0,     0,     0,     0,     0,   703,
       0,     0,     0,   626,     0,     0,     0,     0,     0,   704,
       0,     0,     0,     0,     0,   705,     0,     0,     0,     0,
     706,     0,     0,   707,     0,     0,   708,   709,     0,     0,
     710,     0,     0,   711,   629,   712,     0,   630,   631,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   713,   714,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   632,   633,     0,   715,     0,     0,     0,     0,
       0,   115,     0,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   227,   634,   635,     0,
       0,   250,   629,     0,   167,   630,   631,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   228,
     229,   230,   231,   232,   233,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   234,   117,   118,   119,   120,
     632,   633,     0,   715,   121,     0,     0,     0,   122,     0,
       0,     0,   123,     0,     0,     0,     0,     0,   124,     0,
       0,     0,     0,     0,     0,   634,   635,     0,   125,     0,
       0,     0,   167,     0,   126,     0,     0,     0,     0,   127,
       0,     0,   128,     0,     0,   129,   130,     0,     0,   131,
       0,     0,   132,     0,   133,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   134,   135,     0,
     136,   137,   138,     0,     0,   139,   140,     0,     0,   141,
     142,   235,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
       0,     0,   236,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   237,     0,     0,     0,
       0,     0,     0,     0,     0,   238,     0,     0,   115,     0,
       0,   239,     0,   116,     0,     0,   240,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   241,     0,     0,   242,
     243,   244,   245,     0,     0,     0,   246,     0,     0,     0,
     247,   248,   163,     0,     0,     0,   164,   165,     0,     0,
       0,     0,     0,   249,     0,     0,   166,     0,   250,     0,
       0,   167,   168,   117,   118,   119,   120,     0,     0,     0,
       0,   121,     0,     0,     0,   122,     0,     0,     0,   123,
       0,     0,     0,     0,     0,   124,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   125,     0,     0,     0,     0,
       0,   126,     0,     0,     0,     0,   127,     0,     0,   128,
       0,     0,   129,   130,     0,     0,   131,     0,     0,   132,
       0,   133,     0,     0,     0,   115,     0,     0,     0,     0,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   134,   135,     0,   136,   137,   138,
       0,     0,   139,   140,     0,     0,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,     0,     0,   162,
     117,   118,   119,   120,     0,     0,     0,     0,   121,     0,
       0,     0,   122,     0,     0,     0,   123,     0,     0,     0,
       0,     0,   124,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   125,     0,     0,     0,     0,     0,   126,     0,
       0,     0,     0,   127,     0,     0,   128,     0,     0,   129,
     130,     0,     0,   131,     0,     0,   132,     0,   133,   163,
       0,     0,     0,   164,   165,     0,     0,     0,     0,     0,
       0,     0,     0,   166,     0,   250,     0,     0,   167,   168,
       0,   134,   135,     0,   136,   137,   138,     0,     0,   139,
     140,     0,     0,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,     0,     0,   162,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   620,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   163,     0,     0,     0,
     164,   165,     0,     0,     0,   117,   118,   119,   120,     0,
     166,     0,     0,   622,     0,   167,   168,   623,     0,     0,
       0,   624,     0,     0,     0,     0,     0,   625,     0,     0,
       0,   626,     0,     0,     0,     0,     0,   125,     0,     0,
       0,     0,     0,   627,     0,     0,     0,     0,   127,     0,
       0,   128,     0,     0,   129,   130,     0,     0,   131,     0,
       0,   132,     0,   133,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   134,   135,     0,   628,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,     0,
     699,   162,     0,     0,     0,     0,     0,     0,     0,     0,
     629,     0,     0,   630,   631,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   620,     0,     0,     0,     0,     0,     0,   228,   229,
     230,   231,   232,   233,     0,     0,     0,     0,   632,   633,
       0,     0,     0,     0,     0,   117,   118,   119,   120,     0,
       0,   163,     0,   700,     0,   164,   165,   701,   699,     0,
       0,   702,     0,   634,   635,     0,     0,   703,     0,     0,
     167,   626,     0,     0,     0,     0,     0,   704,     0,     0,
       0,     0,     0,   705,     0,     0,     0,     0,   706,   620,
       0,   707,     0,     0,   708,   709,     0,     0,   710,     0,
       0,   711,     0,   712,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,   119,   120,     0,     0,     0,
       0,   700,     0,     0,     0,   701,   713,   714,     0,   702,
       0,     0,     0,     0,     0,   703,     0,     0,     0,   626,
       0,     0,     0,     0,     0,   704,     0,     0,     0,     0,
       0,   705,     0,     0,     0,     0,   706,     0,     0,   707,
       0,     0,   708,   709,     0,     0,   710,     0,     0,   711,
     629,   712,     0,   630,   631,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   713,   714,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   632,   633,
       0,   715,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   634,   635,     0,     0,     0,   629,     0,
     167,   630,   631,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     3,     0,     0,     4,     0,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   632,   633,     0,   715,
       0,     0,     0,     0,     0,     0,     6,     7,     0,     0,
       0,     8,     0,     9,     0,    10,     0,     0,    11,    12,
      13,   634,   635,     0,     0,    14,    15,    16,   167,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -209,
       0,     0,     0,     0,     0,    28,     0,     0,     0,     0,
       0,     0,     0,     0,    29,     0,     0,     0,     0,     0,
      30,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,     0,     0,     0,     0,    35
};

static const yytype_int16 yycheck[] =
{
       1,    25,     3,    55,    45,   312,     1,   164,   311,   287,
      25,    52,   310,   313,   253,    55,   323,    25,   168,   297,
     598,    45,   297,   598,   164,   208,   826,    25,    52,   916,
      45,   919,   921,   830,   831,   270,   920,    52,    39,   836,
       7,    23,    45,    31,     7,   963,    47,    45,     7,    52,
      31,    70,  1006,  1052,    52,    67,    89,   940,   941,    84,
      43,    86,    87,    25,    20,    90,    91,  1062,    10,    23,
      95,    96,    97,    79,    41,    79,    43,   102,   103,    25,
      23,   110,    79,    45,   953,   110,    53,  1080,    25,    79,
      52,    22,   121,  1026,  1027,    20,   965,    25,   895,    45,
      12,    13,   143,    60,  1109,  1110,    52,   136,    45,   541,
      87,    88,    89,   103,   104,    52,     1,    45,    67,     4,
     114,     6,   832,    79,    52,    79,    80,    81,    70,    86,
     590,   591,   862,   593,  1003,   595,    79,    80,    81,   869,
     164,    26,    27,   100,   168,   178,   179,    78,   115,   164,
      62,    63,    64,   168,    79,   863,   588,     1,   618,    80,
       4,   621,     6,    75,    76,    77,   164,   202,  1161,     8,
     168,  1176,  1165,  1106,  1061,   885,    88,    89,   287,   136,
      35,   216,    26,    27,   174,   109,   102,    35,   297,   752,
    1189,   899,   900,    78,   235,   758,   108,   109,   192,   193,
     167,    40,   164,   119,   210,   211,   168,   211,   132,   133,
     670,   240,   253,   673,     8,   102,     1,  1171,   164,     4,
      33,     6,   168,     1,   181,    89,     4,   164,     6,   253,
    1225,   168,   119,   245,   246,   247,   164,   161,   253,   209,
     168,    26,    27,   262,   209,    89,    40,   287,    26,    27,
     217,    79,  1170,     1,   224,   253,     4,   297,     6,   261,
     312,   226,   227,   287,   231,   232,  1149,   308,   132,   133,
     202,   323,   312,   297,   270,   735,   736,   318,    26,    27,
     263,   264,   270,   323,   308,   100,  1083,   202,   270,   270,
     131,   253,   245,   308,   318,   136,   245,   246,   247,   114,
    1097,   116,   255,   318,    89,   308,     1,   253,   271,     4,
     308,     6,   271,  1201,  1203,   318,   253,   342,  1202,   273,
     318,    87,    88,     8,     4,   253,     6,   270,   208,   112,
     273,    26,    27,   213,   214,    31,    32,  1224,    31,    24,
      33,   226,   227,   126,   109,    38,   308,    40,   228,     1,
      43,   195,     4,   270,     6,    40,   318,   270,   818,   819,
     273,   821,   308,   112,  1164,   105,   115,   132,   133,   109,
     135,   308,   318,   257,    26,    27,   260,   192,   193,   269,
     308,   318,    31,   566,    77,   963,   271,    31,   966,   166,
     318,   966,   132,   133,    89,   119,    45,    46,   202,   366,
     860,    34,    35,  1200,     5,   129,   130,     8,   174,   175,
     195,   871,   178,   166,   649,   875,   691,   877,    70,    71,
      72,    73,   256,    20,    76,    22,   583,   271,  1006,   341,
     210,  1006,   210,    66,    67,    68,    85,    89,     1,   596,
     224,     4,     7,     6,    78,    94,    79,    80,    81,   209,
     601,   100,     4,   365,   129,    20,   596,    22,   609,   734,
      67,    94,   613,    26,    27,    98,    99,   116,   101,    67,
       4,   104,     6,     7,    86,    87,   224,   129,    90,    91,
     249,   250,   251,    95,    96,    97,   271,   262,     0,   598,
     102,   103,     4,   271,     6,   263,   264,   957,   110,     9,
     195,   961,   239,    20,    89,    22,    17,    70,    71,    72,
      73,   226,   227,    76,    18,   100,     1,   102,   978,     4,
     272,     6,    91,   271,   681,    38,    89,   210,   211,   114,
      38,   116,    76,    42,   119,   270,     4,   106,     6,   689,
       8,    26,    27,   218,   219,   220,   221,   222,    58,   270,
     119,    61,     1,    47,    48,     4,   125,     6,   598,   583,
     270,   105,   270,    73,    74,    31,   129,    89,   583,    91,
      92,    93,   596,     7,   598,    85,   271,    26,    27,     8,
     165,   596,   691,   216,   276,   583,    89,    72,    73,    15,
      16,    76,   256,  1171,   226,   227,  1171,   107,   596,   102,
     169,   170,   256,   113,    89,    78,   109,   192,   193,   153,
     154,   155,   156,   157,   158,   275,   119,    15,    16,   271,
     898,   583,   125,    72,    73,   734,   904,    76,   906,   907,
     245,   246,   247,   908,   596,    15,    16,   583,     4,     5,
      89,    87,    88,   878,   129,   884,   583,   250,   251,    79,
     596,   691,    82,    83,    84,   583,    78,   681,    78,   596,
     684,   685,   686,   687,   688,   689,   681,   691,   596,   684,
     685,   686,   687,   688,   689,    38,   684,   685,    61,    62,
     129,   314,    38,   681,    38,   963,   684,   685,   686,   687,
     688,   689,   287,   326,   734,   162,    78,   102,    74,    75,
     167,   168,   297,    78,   171,   172,    78,   112,   271,    78,
     734,   344,    17,   680,   119,    79,    80,    81,    78,   681,
     125,   126,   684,   685,   686,   687,   688,   689,    78,   886,
     342,    18,   699,   272,     5,   681,   737,     7,   684,   685,
     686,   687,   688,   689,   681,     7,   266,   684,   685,   686,
     687,   688,   689,   681,   863,     7,   684,   685,   686,   687,
     688,   689,   997,     7,   999,  1004,     5,   287,    95,    96,
      97,    98,    99,    31,  1040,  1041,     1,   297,     7,     4,
       1,     6,    18,     4,     7,     6,   271,    45,    46,   898,
     899,   900,   901,   902,   903,   904,    31,   906,   907,   908,
    1103,    26,    27,  1101,  1104,    26,    27,    68,    69,    70,
      45,    46,    33,     7,  1121,    17,    31,    38,    33,    40,
      35,   272,   271,    38,    39,    40,     8,    85,   873,   874,
     870,    78,  1139,   270,   270,   270,    94,   270,    78,   863,
      78,    78,   100,   884,    78,    70,    71,    72,    73,   257,
      85,    76,   270,   211,   963,     8,    78,   966,   116,    94,
     884,    38,   886,    30,    89,   100,   115,    79,   908,   884,
      78,   886,    89,   914,   898,   899,   900,   901,   902,   903,
     904,   116,   906,   907,   908,    89,   884,     5,   886,    54,
     914,   103,   104,    89,    78,    78,   270,  1006,     7,   914,
     277,   229,    78,    78,   129,    79,     7,    79,   129,    89,
      79,    91,   913,    79,   915,   916,   914,    79,   913,   271,
     915,   916,   884,   202,   886,    79,   966,   894,    31,   109,
      33,   111,   112,   113,   114,    38,    39,    40,   884,   963,
     886,   275,   966,   269,    78,   269,    31,   884,    33,   886,
      35,    78,   914,    38,    39,    40,   884,    78,   886,   225,
      45,    46,   174,  1004,    78,   271,     5,    29,   914,    80,
      78,   270,   270,   194,   270,   270,   270,   914,   270,   194,
    1004,    79,  1006,   108,   270,    30,   914,   208,    79,  1004,
      78,   117,    16,   208,   309,   918,   208,  1053,  1186,  1184,
      85,  1022,   223,   598,    74,  1097,  1004,   228,   223,    94,
     252,   223,   606,   228,     1,   100,   228,     4,  1059,     6,
      61,    62,    63,    64,    65,    66,   614,  1087,   592,   240,
    1031,   116,  1079,   960,   864,  1059,  1037,  1038,  1039,    26,
      27,   865,  1004,   866,  1059,   876,   271,   868,   676,  1050,
     271,   682,   881,  1020,  1021,  1022,  1057,  1058,  1004,  1060,
    1061,  1059,  1171,  1058,   686,  1060,  1061,  1004,  1069,  1121,
     590,   591,   772,   593,  1069,   595,  1004,   687,   598,   688,
     836,  1121,  1226,   886,   315,    72,    73,  1139,    93,    76,
    1228,   194,  1227,   317,   297,   901,   691,  1059,   618,  1139,
     316,   621,    89,   902,   235,   208,   903,   236,   487,   194,
      -1,    -1,   236,  1059,    31,    45,    46,    -1,  1119,  1120,
     223,    -1,  1059,   208,    -1,   228,  1151,    -1,    45,    46,
    1131,  1059,    -1,    -1,    31,  1136,    -1,    -1,   223,   734,
    1141,    -1,   129,   228,    -1,    -1,  1147,  1171,    45,    46,
     670,  1152,  1147,   673,    -1,    85,   233,   234,   235,   236,
     237,    -1,    -1,    -1,    94,    -1,    -1,    -1,    85,     1,
     100,   691,     4,    -1,     6,    -1,    -1,    94,    -1,    -1,
      32,  1222,    34,   100,    36,    37,   116,    -1,    85,    -1,
    1191,    43,    44,  1194,    26,    27,    -1,    94,  1222,   116,
      -1,    33,    -1,   100,    -1,    -1,    38,  1222,    40,    -1,
    1211,  1212,  1213,  1214,   734,   735,   736,    -1,    -1,   116,
      72,    -1,  1223,  1224,  1222,  1226,  1227,  1228,  1223,  1224,
      -1,  1226,  1227,  1228,    -1,    -1,  1237,  1238,  1239,  1240,
    1241,  1242,    -1,    -1,    -1,  1246,  1241,    -1,    -1,  1250,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1260,
    1222,    -1,    -1,    -1,    -1,    -1,    -1,   862,   863,   864,
     865,   866,    -1,   868,   869,    -1,  1222,    -1,   873,   874,
      -1,    -1,    -1,    -1,   271,  1222,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1222,   815,    -1,   129,   818,   819,
      -1,   821,    -1,   898,   899,   900,   901,   902,   903,   904,
      -1,   906,   907,   908,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,    37,    38,    -1,    40,    41,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    91,    -1,
     860,    -1,   862,   863,   864,   865,   866,    -1,   868,   869,
     870,   871,    -1,   873,   874,   875,   109,   877,   111,   112,
      31,   114,   194,    77,    -1,    -1,    -1,    -1,   963,   122,
     123,   966,    -1,    -1,    45,    46,   208,    -1,   898,   899,
     900,   901,   902,   903,   904,    -1,   906,   907,   908,    -1,
       1,   223,    -1,    -1,    -1,    -1,   228,     8,     9,    10,
      11,    12,    13,    -1,    -1,    16,    -1,    87,    88,    -1,
      -1,  1006,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,
     100,    -1,    -1,    94,    -1,    -1,    -1,    -1,   108,   100,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   957,    -1,   271,
      -1,   961,    -1,   963,    -1,   116,   966,    58,    -1,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,   978,    70,
      -1,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    83,    -1,    85,    -1,    -1,    88,    89,    -1,
     194,    -1,    -1,    -1,    -1,    -1,  1006,    -1,    -1,    -1,
      -1,    -1,    -1,    23,   208,   106,   107,   108,   109,   213,
     214,   215,   113,    -1,    -1,    -1,    -1,    -1,    -1,   223,
      -1,    -1,    -1,    -1,   228,   195,   196,   197,   198,    -1,
       1,    87,    88,     4,    54,     6,    -1,    -1,    -1,    -1,
     210,   211,   212,    -1,    -1,   101,    -1,   103,   104,   105,
      -1,    -1,    23,    -1,    -1,    26,    27,    28,    -1,    79,
      80,    81,   118,   119,   120,    -1,    86,    38,    -1,    -1,
      90,    -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,
     100,    -1,    -1,    -1,   104,    -1,  1171,    -1,    -1,    -1,
      61,    62,    63,    64,    65,    66,   116,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    -1,    -1,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,
      -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,   116,   109,    -1,    -1,   112,
     121,    -1,    -1,   124,    -1,    -1,   127,   128,    -1,    -1,
     131,  1171,   125,   134,    -1,   136,   129,    -1,    -1,   132,
     133,    -1,    -1,    -1,   137,   138,   139,   140,   141,    -1,
      -1,    -1,    -1,   203,    -1,    -1,   206,   207,   159,   160,
      -1,   162,   163,   164,    -1,    -1,   167,   168,    -1,    -1,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   241,   242,   194,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   335,    -1,    -1,   208,    -1,    -1,
     341,    -1,    -1,    -1,    -1,   346,   217,   348,    -1,   350,
      -1,    -1,   223,   273,   355,    -1,   357,   228,    -1,    -1,
      -1,    -1,    -1,    -1,   365,    -1,    -1,   238,    -1,    -1,
     241,   242,   243,   244,    -1,    -1,    -1,   248,    -1,    -1,
      -1,   252,   253,   254,    -1,    -1,     1,   258,   259,     4,
      -1,     6,    -1,    -1,   265,    -1,    -1,   268,    -1,   270,
     271,    -1,   273,   274,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    26,    27,    28,    -1,    -1,    -1,    87,    88,    -1,
      -1,    91,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      79,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,   105,    -1,    73,   108,
      -1,    -1,    77,    78,    79,    80,    81,    -1,   117,    -1,
      -1,    86,    -1,    -1,    89,    90,    -1,    -1,    -1,    94,
      -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,    -1,    -1,   121,    -1,    -1,   124,
      -1,    -1,   127,   128,    -1,    -1,   131,    -1,    -1,   134,
      -1,   136,    -1,    -1,    -1,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,    -1,   159,   160,    -1,   162,   163,   164,
      -1,    -1,   167,   168,    -1,    -1,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   139,    -1,   194,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,    -1,    -1,   208,    -1,    -1,   245,    -1,    -1,    -1,
      -1,    -1,   217,    -1,    -1,    -1,    -1,    -1,   223,     1,
      -1,    -1,     4,   228,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   238,    -1,    -1,   241,   242,   243,   244,
      -1,    23,    -1,   248,    26,    27,    28,   252,   253,   254,
      87,    88,    -1,   258,   259,    -1,    38,    -1,    -1,    -1,
     265,    -1,    -1,   268,    -1,   270,   271,    -1,   273,   274,
      -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,   174,    -1,   121,
      -1,    -1,   124,    -1,    -1,   127,   128,    -1,    -1,   131,
      -1,    -1,   134,    -1,   136,    -1,    -1,    -1,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   762,    -1,   210,   211,   212,    -1,   159,   160,    -1,
     162,   163,   164,    -1,    -1,   167,   168,    -1,    -1,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
      -1,    -1,   194,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,    -1,    -1,    -1,    -1,    -1,   208,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   217,    21,    -1,    23,    -1,
      -1,   223,    -1,    -1,    -1,    -1,   228,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   238,    -1,    -1,   241,
     242,   243,   244,    -1,    -1,    -1,   248,    -1,    -1,    54,
     252,   253,   254,    -1,    -1,    -1,   258,   259,    -1,    -1,
      -1,    -1,    67,   265,    -1,    -1,   268,    -1,   270,   271,
      -1,   273,   274,    78,    79,    80,    81,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    -1,    90,    -1,    -1,    -1,    94,
      -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,   104,
      -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,    79,    -1,   121,    -1,    -1,   124,
      -1,    -1,   127,   128,    -1,    -1,   131,    -1,    -1,   134,
      -1,   136,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,    -1,   159,   160,    -1,   162,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,    -1,    -1,   194,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   203,    -1,
      -1,   206,   207,    -1,    -1,    -1,    21,    -1,    23,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   241,   242,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   254,
      -1,    -1,    -1,   258,   259,    -1,    -1,    -1,    -1,    -1,
      -1,   266,   267,    78,    79,    80,    81,    -1,   273,    -1,
      -1,    86,    -1,    -1,    -1,    90,    -1,    -1,    -1,    94,
     245,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,   104,
      -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,    -1,    -1,   121,    -1,    -1,   124,
      -1,    -1,   127,   128,    -1,    -1,   131,    -1,    -1,   134,
      -1,   136,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   159,   160,    -1,   162,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,    -1,    -1,   194,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   203,    -1,
      -1,   206,   207,    -1,    -1,    -1,    21,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   241,   242,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   254,
      -1,    -1,    -1,   258,   259,    -1,    -1,    -1,    -1,    -1,
      -1,   266,   267,    78,    79,    80,    81,    -1,   273,    -1,
      -1,    86,    -1,    -1,    -1,    90,    -1,    -1,    -1,    94,
      -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,   104,
      -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,    -1,    -1,   121,    -1,    -1,   124,
      -1,    -1,   127,   128,    -1,    -1,   131,    -1,    -1,   134,
      -1,   136,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   159,   160,    -1,   162,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,    -1,    -1,   194,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   203,    -1,
      -1,   206,   207,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   241,   242,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,   254,
      -1,    -1,    -1,   258,   259,    -1,    -1,    -1,    -1,    -1,
      -1,   266,   267,    -1,    -1,    -1,    -1,    -1,   273,    -1,
      -1,    -1,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    21,    90,    23,    -1,    -1,    94,    -1,
      -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,   104,    -1,
      -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,
     116,    -1,    -1,    -1,    -1,   121,    54,    -1,   124,    -1,
      -1,   127,   128,    -1,    -1,   131,    -1,    -1,   134,    -1,
     136,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    -1,    90,   159,   160,    -1,    94,    -1,    -1,    -1,
      -1,    -1,   100,    -1,    -1,    -1,   104,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,   116,    -1,
      -1,    -1,    -1,   121,    -1,    -1,   124,    -1,    -1,   127,
     128,    -1,    -1,   131,    -1,    -1,   134,   203,   136,    -1,
     206,   207,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   159,   160,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   241,   242,    -1,   244,    -1,
      -1,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     266,   267,    -1,    -1,   270,   203,    -1,   273,   206,   207,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    80,    81,   241,   242,    -1,   244,    86,    -1,    -1,
      -1,    90,    -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,
      -1,   100,    -1,    -1,    -1,   104,    -1,    -1,   266,   267,
      -1,   110,   270,    -1,    -1,   273,   274,   116,    -1,    -1,
      -1,    -1,   121,    -1,    -1,   124,    -1,    -1,   127,   128,
      -1,    -1,   131,    -1,    -1,   134,    -1,   136,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     159,   160,    -1,   162,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,    -1,    -1,   194,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   203,    -1,    -1,   206,   207,    -1,
      -1,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   241,   242,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   254,    -1,    -1,    -1,   258,
     259,    -1,    -1,    -1,    -1,    -1,    -1,   266,   267,    78,
      79,    80,    81,    -1,   273,    -1,    -1,    86,    -1,    -1,
      21,    90,    23,    -1,    -1,    94,    -1,    -1,    -1,    -1,
      -1,   100,    -1,    -1,    -1,   104,    -1,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,
      -1,    -1,   121,    54,    -1,   124,    -1,    -1,   127,   128,
      -1,    -1,   131,    -1,    -1,   134,    -1,   136,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    86,    -1,    -1,    -1,    90,
     159,   160,    -1,    94,    -1,    -1,    -1,    -1,    -1,   100,
      -1,    -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
     121,    -1,    -1,   124,    -1,    -1,   127,   128,    -1,    -1,
     131,    -1,    -1,   134,   203,   136,    -1,   206,   207,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   159,   160,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   241,   242,    -1,   244,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,   266,   267,    -1,
      -1,   270,   203,    -1,   273,   206,   207,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,
     241,   242,    -1,   244,    86,    -1,    -1,    -1,    90,    -1,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,   266,   267,    -1,   110,    -1,
      -1,    -1,   273,    -1,   116,    -1,    -1,    -1,    -1,   121,
      -1,    -1,   124,    -1,    -1,   127,   128,    -1,    -1,   131,
      -1,    -1,   134,    -1,   136,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   159,   160,    -1,
     162,   163,   164,    -1,    -1,   167,   168,    -1,    -1,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
      -1,    -1,   194,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   208,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   217,    -1,    -1,    23,    -1,
      -1,   223,    -1,    28,    -1,    -1,   228,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   238,    -1,    -1,   241,
     242,   243,   244,    -1,    -1,    -1,   248,    -1,    -1,    -1,
     252,   253,   254,    -1,    -1,    -1,   258,   259,    -1,    -1,
      -1,    -1,    -1,   265,    -1,    -1,   268,    -1,   270,    -1,
      -1,   273,   274,    78,    79,    80,    81,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    -1,    90,    -1,    -1,    -1,    94,
      -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,    -1,    -1,   121,    -1,    -1,   124,
      -1,    -1,   127,   128,    -1,    -1,   131,    -1,    -1,   134,
      -1,   136,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   159,   160,    -1,   162,   163,   164,
      -1,    -1,   167,   168,    -1,    -1,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,    -1,    -1,   194,
      78,    79,    80,    81,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    -1,    90,    -1,    -1,    -1,    94,    -1,    -1,    -1,
      -1,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,   116,    -1,
      -1,    -1,    -1,   121,    -1,    -1,   124,    -1,    -1,   127,
     128,    -1,    -1,   131,    -1,    -1,   134,    -1,   136,   254,
      -1,    -1,    -1,   258,   259,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   268,    -1,   270,    -1,    -1,   273,   274,
      -1,   159,   160,    -1,   162,   163,   164,    -1,    -1,   167,
     168,    -1,    -1,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,    -1,    -1,   194,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   254,    -1,    -1,    -1,
     258,   259,    -1,    -1,    -1,    78,    79,    80,    81,    -1,
     268,    -1,    -1,    86,    -1,   273,   274,    90,    -1,    -1,
      -1,    94,    -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,
      -1,   104,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,   121,    -1,
      -1,   124,    -1,    -1,   127,   128,    -1,    -1,   131,    -1,
      -1,   134,    -1,   136,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   159,   160,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,    -1,
      23,   194,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     203,    -1,    -1,   206,   207,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,   241,   242,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,    -1,
      -1,   254,    -1,    86,    -1,   258,   259,    90,    23,    -1,
      -1,    94,    -1,   266,   267,    -1,    -1,   100,    -1,    -1,
     273,   104,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,   121,    54,
      -1,   124,    -1,    -1,   127,   128,    -1,    -1,   131,    -1,
      -1,   134,    -1,   136,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79,    80,    81,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    -1,    90,   159,   160,    -1,    94,
      -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,   104,
      -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,    -1,    -1,   121,    -1,    -1,   124,
      -1,    -1,   127,   128,    -1,    -1,   131,    -1,    -1,   134,
     203,   136,    -1,   206,   207,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   159,   160,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   241,   242,
      -1,   244,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   266,   267,    -1,    -1,    -1,   203,    -1,
     273,   206,   207,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       0,     1,    -1,    -1,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   241,   242,    -1,   244,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,
      -1,    31,    -1,    33,    -1,    35,    -1,    -1,    38,    39,
      40,   266,   267,    -1,    -1,    45,    46,    47,   273,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   194,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   223,    -1,    -1,    -1,    -1,   228
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   279,     0,     1,     4,     6,    26,    27,    31,    33,
      35,    38,    39,    40,    45,    46,    47,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    85,    94,
     100,   116,   194,   208,   223,   228,   280,   282,   283,   284,
     285,   331,   332,   333,   334,   342,   280,    80,    79,   328,
     333,   334,   342,   333,   336,   336,   336,   285,    35,   286,
      31,    33,    38,    39,    40,   194,   208,   223,   228,   287,
      35,   288,    31,    33,    35,    38,    39,    40,   194,   208,
     223,   228,   289,    31,    32,    33,    34,    37,    38,    40,
      41,    43,    77,   194,   208,   213,   214,   215,   223,   228,
     290,   208,   213,   214,   228,   291,    31,    33,    38,    40,
      43,    77,   292,    33,   293,    23,    28,    78,    79,    80,
      81,    86,    90,    94,   100,   110,   116,   121,   124,   127,
     128,   131,   134,   136,   159,   160,   162,   163,   164,   167,
     168,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   194,   254,   258,   259,   268,   273,   274,   300,
     329,   420,   421,   422,   423,   424,   477,   480,   484,   485,
     487,   489,   500,   501,   503,   505,   507,   509,   511,   513,
     515,   517,   519,   521,   523,   525,   527,   531,   533,   535,
     536,   538,   540,   542,   544,   546,   548,   550,    43,   263,
     264,   294,   299,    79,   295,   296,   202,   333,   338,   338,
     338,     0,   280,   328,   328,   261,   341,    38,    61,    62,
      63,    64,    65,    66,    77,   173,   194,   208,   217,   223,
     228,   238,   241,   242,   243,   244,   248,   252,   253,   265,
     270,   346,   347,   348,   349,   350,   351,   355,   356,   359,
     360,   367,   371,   375,   376,   378,   379,   395,   396,   398,
     399,   401,   402,   405,   406,   413,   415,   416,   419,   423,
     428,   429,   430,   431,   432,   433,   438,   439,   440,   462,
     476,   480,   481,   498,   499,   500,   280,   269,   301,   304,
     346,   328,   306,   308,   420,   440,   311,   334,   343,   333,
     334,   336,   336,   336,   202,   338,   338,   338,   342,   333,
     334,   343,   336,   336,   336,   202,   456,   338,   338,   338,
     333,   332,   345,   334,   345,    31,   345,   336,   336,   345,
     345,    31,    32,   216,   456,   338,    31,   345,    31,   345,
      31,   345,   338,   338,   338,    31,   345,    31,   345,   338,
     333,   334,   336,   336,   345,    31,   334,    82,    83,    84,
     328,   502,    87,    88,   174,   175,   178,   426,   427,    87,
      88,    89,   504,    89,    91,    92,    93,   506,    95,    96,
      97,    98,    99,   508,    87,    88,    91,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   510,    89,    91,   109,
     111,   112,   113,   114,   512,    87,    88,   101,   103,   104,
     105,   118,   119,   120,   514,    89,    91,   109,   111,   112,
     114,   122,   123,   516,   102,   112,   119,   125,   126,   518,
     112,   126,   520,   119,   129,   130,   522,   105,   109,   132,
     133,   524,   109,   132,   133,   135,   526,   109,   112,   125,
     129,   132,   133,   137,   138,   139,   140,   141,   528,    89,
     132,   133,   532,   109,   132,   133,   161,   534,    89,   100,
     102,   114,   116,   119,   165,   192,   193,   486,   488,   539,
     166,   541,   166,   543,   102,   119,   537,    91,   106,   119,
     125,   169,   170,   545,   102,   119,   547,    89,   102,   109,
     119,   125,   549,    79,   105,   108,   117,   245,   478,   479,
     480,    87,    88,   108,   174,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   210,   211,
     212,   490,   491,   495,   245,   255,   483,   433,   439,   256,
     162,   167,   168,   171,   172,   551,   328,   432,   299,    32,
      34,    36,    37,    43,    44,    72,   297,   338,   328,   210,
     452,   453,   224,   460,   461,   226,   227,   368,   454,   455,
      78,    47,    48,   414,   328,   328,    79,   478,   490,   491,
     209,   209,   224,   209,   368,    67,    67,     4,   281,   441,
     442,   262,   344,   349,   210,   211,   357,   358,   129,   218,
     219,   220,   221,   222,   361,   362,   239,   377,     5,    21,
      54,    67,    86,    90,    94,   100,   104,   116,   162,   203,
     206,   207,   241,   242,   266,   267,   380,   381,   382,   383,
     384,   385,   386,   388,   389,   390,   391,   392,   393,   394,
     421,   422,   471,   472,   473,   477,   484,   485,   487,   489,
     496,   497,   500,    67,   245,   246,   247,   397,   403,   404,
      67,   400,   403,   249,   250,   251,   407,   408,   409,   410,
      31,   270,   417,   418,    15,    16,    17,    18,   272,     8,
      24,    40,     9,    10,    11,    12,    13,    14,    21,    23,
      86,    90,    94,   100,   110,   116,   121,   124,   127,   128,
     131,   134,   136,   159,   160,   244,   421,   422,   434,   435,
     436,   437,   440,   463,   464,   465,   466,   467,   468,   469,
     470,   472,   473,   474,   475,    38,    38,   451,   463,   464,
     270,   270,   270,   270,    42,   340,   346,   301,   304,   306,
     308,   311,   338,   453,   461,   455,   346,   308,   338,   333,
     336,   345,    31,   338,   333,   333,   333,   333,   333,   336,
     328,     7,     8,    89,   178,   179,   425,   139,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   529,
     488,   276,    87,    88,   100,   108,   116,   195,   196,   197,
     492,   493,   495,   256,   256,    78,   275,   298,   299,   459,
      78,   226,   227,   372,    78,   411,   412,   433,    38,    38,
     495,    38,   393,   393,   372,   393,    78,   393,   439,   437,
     440,   445,   446,   449,   469,   470,     7,   271,   329,    78,
      78,   358,    60,    86,   100,   136,   181,   364,   329,    78,
      78,    78,   329,   363,   362,   110,   121,   136,   240,   393,
       5,   393,    15,    16,    17,    18,   272,    20,    22,     8,
      40,     5,   403,     7,     7,     5,     7,     5,   393,   393,
     408,     7,   328,   433,   443,   444,   270,   418,   423,   423,
     428,   429,   430,   432,    23,   270,   352,   464,     7,    15,
      16,    17,    18,   272,     7,    20,    22,     8,   274,   464,
     393,   393,   280,   303,   305,   307,   312,    78,   270,   270,
     270,   270,   459,   459,   333,    78,   427,    76,   105,   153,
     154,   155,   156,   157,   158,   530,    78,    87,    88,   494,
      78,    78,   257,   482,   270,   211,    78,    79,   211,   369,
     421,    70,   344,   447,   448,   393,   393,    38,   393,    78,
     369,    30,   281,     5,   281,   447,   281,   442,   115,   112,
     115,   365,   366,    89,    89,    54,    89,   393,     5,   380,
     421,   473,   474,   381,   382,   383,    78,   385,   380,   387,
     421,   440,   393,   421,   473,   496,   496,   393,   404,   393,
     403,   410,   349,   447,   443,   328,   281,   353,   354,   469,
     474,   474,   465,   466,   467,   469,    78,   469,   469,   464,
      33,    38,    40,   129,   194,   208,   223,   228,   271,   280,
     282,   302,    73,    89,   271,   280,   282,   323,   326,   346,
      70,    71,    72,    73,    76,    89,   129,   271,   280,   282,
     313,    72,    89,   129,   271,   280,   282,   313,   303,   305,
     307,   312,   270,     7,   277,   482,   260,   482,    78,   320,
      78,    20,    79,   229,   370,    79,   330,   448,   393,    20,
      79,   370,   393,   450,   469,   470,   476,     7,    79,    79,
      79,   393,   403,   403,   271,   349,   445,     7,   271,   275,
     328,   335,   328,   337,   337,    79,   202,   328,   339,   339,
     339,   280,    61,    62,   327,    79,   280,   280,   280,   330,
     330,   269,    74,    75,   314,    78,    79,   103,   104,   174,
     315,   316,   322,    68,    69,    70,   309,   310,   280,   269,
     316,   309,   280,   271,   271,   271,   271,   320,    78,    78,
      89,   195,   271,   280,   282,   458,   233,   234,   235,   236,
     237,   374,   225,   373,    78,   374,   373,   281,   366,   271,
       5,   281,   354,   304,   306,   311,   339,   317,   317,   317,
      29,   280,   280,   308,     8,   280,     7,   280,   308,     5,
     280,   271,   482,    80,   332,   280,   373,    78,   369,   373,
     476,   270,   270,   270,   317,   270,   270,   270,    79,   315,
     310,   208,   223,   228,   316,   280,   108,   280,    79,   210,
     211,   281,   305,   307,   312,   270,   318,   321,   319,    30,
     325,   280,   280,   280,   280,   131,   136,   457,   271,   271,
     271,   320,   271,   280,   282,   452,   271,   280,   282,   460,
     271,   280,   282,   454,    79,   117,   280,   280,   280,   280,
     271,   280,   280,   280,    22,    78,   324,   280,    78
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   278,   279,   279,   280,   280,   281,   281,   282,   282,
     282,   283,   283,   283,   283,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   286,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   288,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   291,
     291,   291,   291,   291,   291,   292,   292,   292,   292,   292,
     292,   293,   294,   294,   295,   296,   296,   297,   297,   297,
     297,   297,   297,   297,   297,   298,   298,   299,   299,   300,
     301,   302,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   304,   305,   305,   305,   305,   305,   305,
     306,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     308,   308,   309,   309,   310,   310,   310,   311,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   313,   313,
     314,   314,   315,   316,   316,   317,   318,   318,   318,   318,
     319,   319,   319,   319,   320,   320,   320,   320,   321,   321,
     321,   321,   322,   322,   322,   322,   323,   324,   324,   325,
     325,   326,   327,   327,   328,   329,   329,   329,   330,   331,
     331,   332,   332,   332,   332,   332,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   342,   343,   344,
     345,   345,   346,   346,   347,   348,   348,   349,   349,   349,
     349,   349,   349,   349,   349,   349,   349,   349,   349,   349,
     349,   349,   349,   349,   349,   350,   350,   351,   352,   352,
     353,   353,   353,   354,   355,   355,   356,   356,   357,   357,
     358,   358,   359,   359,   360,   361,   361,   362,   362,   362,
     362,   362,   362,   363,   364,   364,   364,   364,   364,   365,
     365,   366,   366,   367,   367,   367,   368,   368,   368,   369,
     369,   370,   370,   371,   371,   372,   372,   372,   373,   373,
     373,   373,   374,   374,   374,   374,   374,   375,   376,   377,
     377,   377,   377,   377,   378,   379,   379,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   381,   381,   381,
     382,   382,   383,   383,   384,   384,   385,   386,   386,   387,
     387,   388,   388,   389,   390,   391,   392,   392,   392,   393,
     393,   393,   394,   394,   394,   394,   394,   394,   394,   395,
     395,   396,   397,   397,   397,   398,   398,   399,   400,   400,
     400,   400,   400,   401,   401,   402,   403,   403,   404,   404,
     404,   405,   405,   406,   407,   407,   408,   408,   409,   409,
     410,   410,   411,   411,   412,   413,   414,   414,   415,   415,
     416,   417,   417,   418,   419,   420,   421,   421,   421,   422,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   424,   425,   425,   425,   426,   426,   426,   426,
     426,   427,   427,   428,   428,   428,   429,   429,   430,   430,
     431,   431,   432,   433,   433,   434,   435,   436,   437,   437,
     437,   438,   439,   439,   439,   440,   441,   441,   441,   442,
     442,   442,   443,   443,   444,   445,   445,   446,   447,   447,
     448,   448,   449,   449,   450,   450,   451,   451,   452,   453,
     454,   455,   456,   457,   457,   458,   458,   459,   460,   460,
     461,   462,   462,   462,   462,   463,   463,   464,   464,   464,
     465,   465,   465,   466,   466,   467,   467,   468,   468,   469,
     470,   470,   471,   471,   472,   473,   473,   473,   473,   473,
     473,   473,   473,   473,   473,   473,   473,   474,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   474,   475,   475,   475,   475,   475,   475,   476,   476,
     476,   476,   476,   476,   477,   477,   477,   478,   478,   479,
     479,   479,   479,   480,   480,   480,   480,   480,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   480,   480,   480,
     480,   481,   481,   481,   481,   482,   482,   483,   483,   484,
     485,   485,   485,   486,   486,   487,   487,   488,   488,   488,
     489,   489,   489,   490,   490,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     492,   492,   492,   492,   492,   492,   492,   493,   493,   494,
     494,   495,   495,   495,   495,   496,   496,   497,   497,   498,
     498,   499,   500,   500,   500,   500,   500,   500,   500,   500,
     500,   500,   500,   500,   500,   500,   500,   500,   501,   502,
     502,   502,   503,   504,   504,   504,   505,   506,   506,   506,
     506,   507,   508,   508,   508,   508,   508,   509,   510,   510,
     510,   510,   510,   510,   510,   510,   510,   510,   510,   510,
     511,   512,   512,   512,   512,   512,   512,   512,   513,   514,
     514,   514,   514,   514,   514,   514,   514,   514,   515,   516,
     516,   516,   516,   516,   516,   516,   516,   517,   518,   518,
     518,   518,   518,   519,   520,   520,   521,   522,   522,   522,
     523,   524,   524,   524,   524,   525,   526,   526,   526,   526,
     527,   527,   527,   528,   528,   528,   528,   528,   528,   528,
     528,   528,   528,   529,   529,   529,   529,   529,   529,   529,
     529,   529,   529,   529,   529,   530,   530,   530,   530,   530,
     530,   530,   530,   531,   532,   532,   532,   533,   534,   534,
     534,   534,   535,   535,   535,   535,   535,   535,   535,   536,
     537,   537,   538,   539,   539,   539,   539,   540,   541,   542,
     543,   544,   545,   545,   545,   545,   545,   545,   546,   547,
     547,   548,   549,   549,   549,   549,   549,   550,   551,   551,
     551,   551,   551
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       2,     1,     1,     2,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     6,
       2,     6,     3,     2,     6,     6,     3,     2,     3,     3,
       8,     3,     3,     2,     6,     2,     6,     6,     6,     3,
       2,     3,     3,     8,     3,     3,     2,     2,     2,     2,
       2,     3,     2,     2,     4,     2,     2,     2,     2,     2,
       2,     3,     2,     2,     3,     2,     2,     3,     2,     2,
       3,     2,     2,     3,     3,     2,     2,     3,     4,     2,
       3,     2,     2,     3,     2,     2,     2,     2,     2,     3,
       2,     3,     2,     1,     3,     0,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     1,
       0,     2,     0,     2,     2,     3,     8,     8,     8,     8,
       8,     9,     8,     0,     0,     2,     2,     3,     3,     3,
       0,     0,     2,     2,     4,     4,     4,     4,     4,     3,
       1,     1,     3,     1,     1,     1,     1,     0,     0,     2,
       2,     6,     6,     6,     6,     4,     4,     3,     2,     2,
       1,     1,     1,     1,     3,     0,     0,     2,     2,     2,
       0,     2,     2,     2,     0,     2,     2,     2,     0,     2,
       2,     2,     1,     1,     1,     1,     7,     1,     2,     2,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       2,     1,     2,     1,     2,     2,     1,     2,     2,     2,
       0,     1,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       1,     3,     3,     5,     1,     2,     1,     3,     1,     2,
       2,     2,     1,     2,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     1,     2,     2,     1,     1,     1,     3,
       1,     1,     1,     7,     6,     3,     1,     1,     0,     1,
       1,     0,     3,     5,     3,     1,     1,     0,     0,     3,
       3,     3,     1,     1,     1,     1,     1,     2,     1,     0,
       4,     4,     4,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     1,     3,     1,
       1,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     4,     2,     3,     2,     2,
       1,     1,     3,     4,     1,     2,     1,     1,     2,     3,
       1,     3,     4,     3,     5,     3,     1,     3,     1,     1,
       1,     1,     2,     1,     1,     2,     2,     1,     1,     3,
       1,     1,     1,     2,     1,     4,     1,     1,     6,     5,
       1,     1,     2,     2,     1,     2,     1,     1,     2,     1,
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
       1,     4,     3,     4,     1,     0,     2,     1,     1,     5,
       7,     5,     4,     1,     1,     2,     3,     1,     1,     1,
       2,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     4,
       5,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     6,     1,
       1,     1,     2,     1,     1,     1,     2,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     1,     1,     1,
       2,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       2,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     1,     1,     1,     1,     2,     4,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1
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
          case 79: /* "string"  */
#line 247 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3468 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 80: /* "quoted string"  */
#line 247 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3474 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 81: /* "string with a trailing asterisk"  */
#line 247 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3480 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 283: /* line  */
#line 487 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3486 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 284: /* base_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3492 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 285: /* add_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3498 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 286: /* replace_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3504 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 287: /* create_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3510 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 288: /* insert_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3516 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 289: /* delete_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3522 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 290: /* list_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3528 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 291: /* reset_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3534 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 292: /* flush_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3540 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 293: /* rename_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3546 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 294: /* export_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3552 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 295: /* monitor_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3558 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 296: /* monitor_event  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3564 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 300: /* describe_cmd  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3570 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 301: /* table_block_alloc  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 3576 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 304: /* chain_block_alloc  */
#line 504 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 3582 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 306: /* set_block_alloc  */
#line 513 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3588 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 308: /* set_block_expr  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3594 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 311: /* map_block_alloc  */
#line 516 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3600 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 315: /* data_type_atom_expr  */
#line 484 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3606 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 316: /* data_type_expr  */
#line 484 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3612 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 317: /* obj_block_alloc  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 3618 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 322: /* type_identifier  */
#line 479 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3624 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 325: /* dev_spec  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3630 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 328: /* identifier  */
#line 479 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3636 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 329: /* string  */
#line 479 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3642 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 333: /* table_spec  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3648 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 334: /* chain_spec  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3654 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* chain_identifier  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3660 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 336: /* set_spec  */
#line 495 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3666 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* set_identifier  */
#line 495 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3672 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* obj_spec  */
#line 495 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3678 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* obj_identifier  */
#line 495 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3684 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* handle_spec  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3690 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* position_spec  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3696 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* rule_position  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3702 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* ruleid_spec  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3708 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* comment_spec  */
#line 479 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3714 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 345: /* ruleset_spec  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3720 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* rule  */
#line 506 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 3726 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 348: /* stmt_list  */
#line 522 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 3732 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 349: /* stmt  */
#line 524 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3738 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* verdict_stmt  */
#line 524 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3744 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 351: /* verdict_map_stmt  */
#line 593 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3750 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 352: /* verdict_map_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3756 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 353: /* verdict_map_list_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3762 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* verdict_map_list_member_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3768 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 355: /* counter_stmt  */
#line 526 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3774 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* counter_stmt_alloc  */
#line 526 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3780 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 359: /* log_stmt  */
#line 534 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3786 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* log_stmt_alloc  */
#line 534 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3792 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 367: /* limit_stmt  */
#line 537 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3798 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 369: /* quota_unit  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3804 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 371: /* quota_stmt  */
#line 537 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3810 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* reject_stmt  */
#line 540 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3816 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* reject_stmt_alloc  */
#line 540 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3822 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 378: /* nat_stmt  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3828 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 379: /* nat_stmt_alloc  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3834 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 380: /* primary_stmt_expr  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3840 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 381: /* shift_stmt_expr  */
#line 582 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3846 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 382: /* and_stmt_expr  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3852 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* exclusive_or_stmt_expr  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3858 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* inclusive_or_stmt_expr  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3864 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* basic_stmt_expr  */
#line 580 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3870 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* concat_stmt_expr  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3876 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* map_stmt_expr_set  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3882 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* map_stmt_expr  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3888 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* prefix_stmt_expr  */
#line 577 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3894 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* range_stmt_expr  */
#line 577 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3900 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* wildcard_stmt_expr  */
#line 577 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3906 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* multiton_stmt_expr  */
#line 575 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3912 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 393: /* stmt_expr  */
#line 572 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3918 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* masq_stmt  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3924 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 396: /* masq_stmt_alloc  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3930 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* redir_stmt  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3936 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* redir_stmt_alloc  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3942 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* dup_stmt  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3948 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* fwd_stmt  */
#line 550 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3954 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* queue_stmt  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3960 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* queue_stmt_alloc  */
#line 545 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3966 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* set_elem_expr_stmt  */
#line 603 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3972 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 412: /* set_elem_expr_stmt_alloc  */
#line 603 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3978 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* set_stmt  */
#line 552 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3984 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* flow_stmt  */
#line 555 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3990 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* flow_stmt_alloc  */
#line 555 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3996 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* match_stmt  */
#line 524 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4002 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* variable_expr  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4008 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* symbol_expr  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4014 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* integer_expr  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4020 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* primary_expr  */
#line 560 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4026 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* fib_expr  */
#line 675 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4032 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* shift_expr  */
#line 560 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4038 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* and_expr  */
#line 560 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4044 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* exclusive_or_expr  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4050 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* inclusive_or_expr  */
#line 562 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4056 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 432: /* basic_expr  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4062 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* concat_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4068 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* prefix_rhs_expr  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4074 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* range_rhs_expr  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4080 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 436: /* wildcard_rhs_expr  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4086 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* multiton_rhs_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4092 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* map_expr  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4098 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 439: /* expr  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4104 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 440: /* set_expr  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4110 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 441: /* set_list_expr  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4116 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* set_list_member_expr  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4122 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* flow_key_expr  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4128 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 444: /* flow_key_expr_alloc  */
#line 606 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4134 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 445: /* set_elem_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4140 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 446: /* set_elem_expr_alloc  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4146 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 449: /* set_lhs_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4152 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 450: /* set_rhs_expr  */
#line 601 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4158 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* initializer_expr  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4164 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* counter_config  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).counter)); }
#line 4170 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 453: /* counter_obj  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4176 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 454: /* quota_config  */
#line 686 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).quota)); }
#line 4182 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 455: /* quota_obj  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4188 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* ct_obj_alloc  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4194 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* limit_config  */
#line 688 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).limit)); }
#line 4200 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* limit_obj  */
#line 619 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4206 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* relational_expr  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4212 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 463: /* list_rhs_expr  */
#line 614 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4218 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* rhs_expr  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4224 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* shift_rhs_expr  */
#line 614 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4230 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* and_rhs_expr  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4236 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 467: /* exclusive_or_rhs_expr  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4242 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* inclusive_or_rhs_expr  */
#line 616 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4248 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* basic_rhs_expr  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4254 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* concat_rhs_expr  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4260 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* boolean_expr  */
#line 696 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4266 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* keyword_expr  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4272 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* primary_rhs_expr  */
#line 614 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4278 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* verdict_expr  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4284 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* meta_expr  */
#line 663 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4290 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* meta_stmt  */
#line 532 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4296 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* numgen_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4302 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 485: /* hash_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4308 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* rt_expr  */
#line 667 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4314 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 489: /* ct_expr  */
#line 671 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4320 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 496: /* symbol_stmt_expr  */
#line 614 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4326 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 497: /* list_stmt_expr  */
#line 582 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4332 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 498: /* ct_stmt  */
#line 530 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4338 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 499: /* payload_stmt  */
#line 528 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4344 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* payload_expr  */
#line 626 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4350 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* payload_raw_expr  */
#line 626 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4356 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 503: /* eth_hdr_expr  */
#line 629 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4362 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* vlan_hdr_expr  */
#line 629 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4368 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* arp_hdr_expr  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4374 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 509: /* ip_hdr_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4380 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 511: /* icmp_hdr_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4386 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 513: /* ip6_hdr_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4392 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 515: /* icmp6_hdr_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4398 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 517: /* auth_hdr_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4404 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 519: /* esp_hdr_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4410 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 521: /* comp_hdr_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4416 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 523: /* udp_hdr_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4422 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 525: /* udplite_hdr_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4428 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 527: /* tcp_hdr_expr  */
#line 691 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4434 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 531: /* dccp_hdr_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4440 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 533: /* sctp_hdr_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4446 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 535: /* exthdr_expr  */
#line 651 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4452 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* hbh_hdr_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4458 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* rt_hdr_expr  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4464 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* rt0_hdr_expr  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4470 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 542: /* rt2_hdr_expr  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4476 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 544: /* frag_hdr_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4482 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 546: /* dst_hdr_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4488 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 548: /* mh_hdr_expr  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4494 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 550: /* exthdr_exists_expr  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4500 "parser_bison.c" /* yacc.c:1257  */
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
#line 122 "parser_bison.y" /* yacc.c:1429  */
{
	location_init(scanner, state, &yylloc);
	if (nft->debug_mask & DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (nft->debug_mask & DEBUG_PARSER)
		yydebug = 1;
}

#line 4617 "parser_bison.c" /* yacc.c:1429  */
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
#line 709 "parser_bison.y" /* yacc.c:1646  */
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
#line 4820 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 8:
#line 735 "parser_bison.y" /* yacc.c:1646  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 4832 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 9:
#line 743 "parser_bison.y" /* yacc.c:1646  */
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
#line 4850 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 757 "parser_bison.y" /* yacc.c:1646  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 4860 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 11:
#line 764 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 4866 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 765 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 4872 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 766 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 4878 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 768 "parser_bison.y" /* yacc.c:1646  */
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
#line 4912 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 799 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4918 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 16:
#line 800 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4924 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 801 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4930 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 802 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4936 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 803 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4942 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 804 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4948 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 805 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 806 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 807 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4966 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 808 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4972 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 809 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 810 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4984 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 811 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4990 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 815 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4998 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 820 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5008 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 826 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5016 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 831 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5027 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 838 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5035 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 842 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5043 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 847 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 854 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5063 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 860 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5071 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 864 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5084 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 873 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5092 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 877 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5100 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 881 "parser_bison.y" /* yacc.c:1646  */
    {

				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5109 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 886 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5117 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 42:
#line 892 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5125 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 898 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5133 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 903 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5143 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 909 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5151 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 914 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5162 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 922 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5172 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 929 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5182 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 935 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5190 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 939 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5203 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 948 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5211 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 952 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5219 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 956 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5227 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 960 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5235 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 966 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5243 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 56:
#line 972 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5251 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 976 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5259 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 980 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5267 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 984 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5275 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 988 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5283 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 992 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5291 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 996 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5299 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1000 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5307 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1004 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5315 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1008 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5323 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1014 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5331 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1018 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5339 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1022 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5347 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1026 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1030 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5363 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1034 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1038 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1042 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5387 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1046 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5395 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1050 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5403 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1054 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5411 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1058 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5419 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1062 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5427 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1066 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5435 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1070 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5443 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1074 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5451 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1078 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5459 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1082 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5467 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1086 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5475 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1090 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5483 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1094 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5491 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1098 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5499 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1102 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5507 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1108 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5515 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1112 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5523 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1116 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 5531 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1120 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5539 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1124 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5547 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1128 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5555 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1134 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5563 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1138 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5571 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1142 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5579 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1146 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5587 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1150 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5595 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1154 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5603 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1160 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 5612 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1167 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct export *export = export_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_EXPORT, &h, &(yyloc), export);
			}
#line 5622 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1173 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct export *export = export_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_EXPORT, &h, &(yyloc), export);
			}
#line 5632 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1181 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 5643 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1189 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 5649 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1190 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 5655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1193 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 5661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1194 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 5667 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1195 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 5673 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1196 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 5679 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1197 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 5685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1198 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 5691 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1199 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 5697 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1200 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 5703 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1203 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 5709 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1207 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_XML; }
#line 5715 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1208 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 5721 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1212 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 5731 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1220 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 5740 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1227 "parser_bison.y" /* yacc.c:1646  */
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
#line 5756 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1240 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 5762 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1247 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5775 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1258 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5787 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1268 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5799 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1278 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5812 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1289 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5825 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1298 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 5838 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1309 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5851 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1320 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 5860 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1326 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 5866 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1332 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 5875 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1339 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 5883 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1344 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 5889 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1348 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 5898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1353 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 5907 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1358 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 5916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1363 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 5925 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1368 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 5934 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1380 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 5942 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1386 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 5948 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1387 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 5954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1388 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 5960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1392 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 5968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1397 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 5974 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1403 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].expr)->dtype;

				expr_free((yyvsp[-1].expr));
				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 5987 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1414 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 5998 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1423 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6009 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1432 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6020 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1439 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6029 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1444 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6038 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1452 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 6046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1456 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 6054 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1461 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 6060 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1462 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 6066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1466 "parser_bison.y" /* yacc.c:1646  */
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
#line 6082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1481 "parser_bison.y" /* yacc.c:1646  */
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
#line 6103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1500 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 6111 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1505 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6117 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1509 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->counter = *(yyvsp[0].counter);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6126 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1515 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6132 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1519 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->quota = *(yyvsp[0].quota);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1525 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6147 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1529 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6155 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1534 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6161 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1538 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->limit = *(yyvsp[0].limit);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6170 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1544 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6176 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1545 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("mark"); }
#line 6182 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1546 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("dscp"); }
#line 6188 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1547 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("ecn"); }
#line 6194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1551 "parser_bison.y" /* yacc.c:1646  */
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
#line 6224 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1578 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 6230 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1579 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = -(yyvsp[0].val); }
#line 6236 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1582 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6242 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1583 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6248 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1587 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].chain)->policy != -1) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].val);
			}
#line 6261 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1597 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_ACCEPT; }
#line 6267 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1598 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_DROP;   }
#line 6273 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1610 "parser_bison.y" /* yacc.c:1646  */
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
#line 6290 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1624 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6296 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1628 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6302 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1629 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 6308 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1630 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_INET; }
#line 6314 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1631 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_ARP; }
#line 6320 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1632 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 6326 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1633 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 6332 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1637 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table	= (yyvsp[0].string);
			}
#line 6342 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1645 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 6351 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1652 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 6360 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1659 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 6369 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1666 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 6378 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1673 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj		= (yyvsp[0].string);
			}
#line 6387 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1680 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj		= (yyvsp[0].string);
			}
#line 6396 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1687 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 6406 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1695 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 6416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1703 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 6424 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1707 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 6433 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1714 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 6442 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1721 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strlen((yyvsp[0].string)) > UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed", UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 6455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1732 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 6464 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1737 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 6473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1744 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 6481 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1748 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 6489 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1754 "parser_bison.y" /* yacc.c:1646  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 6503 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1766 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 6513 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1772 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 6522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1799 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 6530 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1803 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 6538 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1809 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6546 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1815 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6555 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1820 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 6566 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1829 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 6575 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1834 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 6584 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1842 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 6592 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1851 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 6600 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1855 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 6610 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1863 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 6618 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1870 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 6626 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1874 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 6634 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1884 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 6642 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1890 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 6650 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1897 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 6659 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1902 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 6668 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1907 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 6677 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1912 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 6686 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1917 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 6695 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1922 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 6703 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1928 "parser_bison.y" /* yacc.c:1646  */
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
#line 6733 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1956 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 6741 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1960 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 6749 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1964 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 6757 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1968 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 6765 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1972 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 6773 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1978 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6781 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1985 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 6789 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1989 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 6797 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1995 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 6810 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 294:
#line 2004 "parser_bison.y" /* yacc.c:1646  */
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
#line 6833 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 295:
#line 2023 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 6843 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 296:
#line 2030 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 6849 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 297:
#line 2031 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6855 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 298:
#line 2032 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6861 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 299:
#line 2035 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("bytes"); }
#line 6867 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 300:
#line 2036 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6873 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 301:
#line 2039 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6879 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 302:
#line 2041 "parser_bison.y" /* yacc.c:1646  */
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
#line 6896 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 303:
#line 2056 "parser_bison.y" /* yacc.c:1646  */
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
#line 6916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2072 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 6926 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2079 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 6932 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2080 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6938 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2081 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6944 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 308:
#line 2084 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6950 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 309:
#line 2085 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 6956 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 310:
#line 2086 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 6962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 311:
#line 2088 "parser_bison.y" /* yacc.c:1646  */
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
#line 6979 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 312:
#line 2102 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL; }
#line 6985 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 313:
#line 2103 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60; }
#line 6991 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 314:
#line 2104 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 6997 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 315:
#line 2105 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 7003 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 316:
#line 2106 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 7009 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 318:
#line 2113 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 7017 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 319:
#line 2119 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 7026 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2124 "parser_bison.y" /* yacc.c:1646  */
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
#line 7041 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 321:
#line 2135 "parser_bison.y" /* yacc.c:1646  */
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
#line 7056 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 322:
#line 2146 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpx_code_type;
				xfree((yyvsp[0].string));
			}
#line 7070 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2156 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 7078 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2165 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_SNAT;
			}
#line 7087 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2170 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_DNAT;
			}
#line 7096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2176 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7102 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 328:
#line 2177 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7108 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 329:
#line 2178 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7114 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2179 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7120 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2180 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7126 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2181 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7132 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2182 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7138 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2183 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7144 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2184 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7150 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2185 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7156 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2190 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7164 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2194 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7172 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2201 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7180 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2208 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7188 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2215 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7196 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 348:
#line 2225 "parser_bison.y" /* yacc.c:1646  */
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
#line 7217 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2248 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7225 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 352:
#line 2251 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7231 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 353:
#line 2255 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 7239 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 354:
#line 2261 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 355:
#line 2267 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 7260 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2288 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7268 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 363:
#line 2292 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 364:
#line 2296 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7285 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2301 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7294 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2306 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7302 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2310 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7310 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2314 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7318 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 371:
#line 2323 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = masq_stmt_alloc(&(yyloc)); }
#line 7324 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 372:
#line 2327 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->masq.proto = (yyvsp[0].expr);
			}
#line 7332 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2331 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->masq.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 7341 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2336 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 7349 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2345 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = redir_stmt_alloc(&(yyloc)); }
#line 7355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2349 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 7363 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2353 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 7371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2357 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 381:
#line 2361 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7388 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2366 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2373 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 7406 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2378 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 7416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2386 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.to = (yyvsp[0].expr);
			}
#line 7425 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 387:
#line 2394 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7433 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2399 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 7439 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 389:
#line 2400 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 7445 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 390:
#line 2401 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 7451 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 393:
#line 2409 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 7459 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2415 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7467 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2422 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 7476 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2427 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 7484 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2434 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7492 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2439 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 7498 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2440 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 7504 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 404:
#line 2448 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 7512 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 405:
#line 2454 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 7523 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 406:
#line 2462 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 7529 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 407:
#line 2463 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 7535 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2467 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->flow.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->flow.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 7546 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2474 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->flow.key  = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->flow.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-4].stmt);
			}
#line 7557 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2483 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = flow_stmt_alloc(&(yyloc));
			}
#line 7565 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2489 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7573 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2496 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->flow.table = (yyvsp[0].string);
			}
#line 7581 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2502 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7589 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2508 "parser_bison.y" /* yacc.c:1646  */
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
#line 7608 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2526 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7619 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2533 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7630 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2542 "parser_bison.y" /* yacc.c:1646  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 7643 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2552 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7649 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2553 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2554 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2555 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7667 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2556 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7673 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2557 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7679 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2558 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2559 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7691 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2560 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7697 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2561 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7703 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2562 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7709 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2563 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 7715 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2567 "parser_bison.y" /* yacc.c:1646  */
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
#line 7740 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2589 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 7746 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2590 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 7752 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2591 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 7758 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2594 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 7764 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2595 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 7770 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2596 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 7776 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2597 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 7782 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2598 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 7788 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2602 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7796 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2610 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7804 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2614 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7812 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2621 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7820 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2628 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7828 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2635 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7836 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2645 "parser_bison.y" /* yacc.c:1646  */
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
#line 7857 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 455:
#line 2664 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 7865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2670 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7873 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2676 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 7886 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2692 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7894 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2703 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7903 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 466:
#line 2710 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7912 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2715 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7921 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2723 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7929 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2727 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7937 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2731 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 7945 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2738 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2745 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 7962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2755 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 7970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2761 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 7978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2768 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val) * 1000;
			}
#line 7986 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2772 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 7994 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 488:
#line 2790 "parser_bison.y" /* yacc.c:1646  */
    {
				struct counter *counter;

				counter = xzalloc(sizeof(*counter));
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
				(yyval.counter) = counter;
			}
#line 8007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 489:
#line 2801 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
				(yyval.obj)->counter = *(yyvsp[0].counter);
			}
#line 8017 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2809 "parser_bison.y" /* yacc.c:1646  */
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
#line 8040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 491:
#line 2830 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
				(yyval.obj)->quota = *(yyvsp[0].quota);
			}
#line 8050 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 492:
#line 2837 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 8056 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2840 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_TCP; }
#line 8062 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 494:
#line 2841 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_UDP; }
#line 8068 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 495:
#line 2845 "parser_bison.y" /* yacc.c:1646  */
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
#line 8087 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 496:
#line 2860 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 8095 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2866 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 8103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 498:
#line 2872 "parser_bison.y" /* yacc.c:1646  */
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
#line 8118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 499:
#line 2883 "parser_bison.y" /* yacc.c:1646  */
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
#line 8142 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 500:
#line 2905 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
				(yyval.obj)->limit = *(yyvsp[0].limit);
			}
#line 8152 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2913 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8160 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2917 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_FLAGCMP, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8168 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 503:
#line 2921 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8176 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 504:
#line 2925 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-3]), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[-1].expr));
			}
#line 8184 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 505:
#line 2931 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 506:
#line 2937 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8204 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 507:
#line 2944 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8210 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 508:
#line 2945 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8216 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 509:
#line 2946 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8222 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 511:
#line 2951 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8230 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 512:
#line 2955 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8238 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 514:
#line 2962 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8246 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 516:
#line 2969 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8254 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 518:
#line 2976 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8262 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 521:
#line 2986 "parser_bison.y" /* yacc.c:1646  */
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
#line 8283 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 522:
#line 3004 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = true; }
#line 8289 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 523:
#line 3005 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = false; }
#line 8295 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 524:
#line 3009 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 1, &(yyvsp[0].val));
			}
#line 8305 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 525:
#line 3016 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 8311 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 526:
#line 3017 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 8317 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 527:
#line 3018 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 8323 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 528:
#line 3019 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 8329 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 529:
#line 3020 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 8335 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 530:
#line 3021 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 8341 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 531:
#line 3022 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 8347 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 532:
#line 3023 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 8353 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 533:
#line 3024 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 8359 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 534:
#line 3025 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 8365 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 535:
#line 3026 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 8371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 536:
#line 3027 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 8377 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 537:
#line 3030 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8383 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 538:
#line 3031 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8389 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 539:
#line 3032 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8395 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 540:
#line 3033 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8401 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 541:
#line 3035 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8412 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 542:
#line 3042 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 543:
#line 3049 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8434 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 544:
#line 3056 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8445 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 545:
#line 3063 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8456 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 546:
#line 3070 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8467 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 547:
#line 3077 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8478 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 548:
#line 3084 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8489 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 549:
#line 3091 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8500 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 550:
#line 3098 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8511 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 551:
#line 3105 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 552:
#line 3113 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_EQ; }
#line 8528 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 553:
#line 3114 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_NEQ; }
#line 8534 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 554:
#line 3115 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LT; }
#line 8540 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 555:
#line 3116 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GT; }
#line 8546 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 556:
#line 3117 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GTE; }
#line 8552 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 557:
#line 3118 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LTE; }
#line 8558 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 558:
#line 3122 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 8566 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 559:
#line 3126 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 8574 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 560:
#line 3130 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 8582 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 561:
#line 3134 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].string));
			}
#line 8590 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 562:
#line 3138 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].string));
			}
#line 8598 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 563:
#line 3142 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 8606 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 564:
#line 3148 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 8614 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 565:
#line 3152 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 8622 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 566:
#line 3156 "parser_bison.y" /* yacc.c:1646  */
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
#line 8640 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 569:
#line 3174 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_LEN; }
#line 8646 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 570:
#line 3175 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 8652 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 571:
#line 3176 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 8658 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 572:
#line 3177 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 8664 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 573:
#line 3180 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_MARK; }
#line 8670 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 574:
#line 3181 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIF; }
#line 8676 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 575:
#line 3182 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 8682 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 576:
#line 3183 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 8688 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 577:
#line 3184 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIF; }
#line 8694 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 578:
#line 3185 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 8700 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 579:
#line 3186 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 8706 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 580:
#line 3187 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKUID; }
#line 8712 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 581:
#line 3188 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKGID; }
#line 8718 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 582:
#line 3189 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 8724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 583:
#line 3190 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 8730 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 584:
#line 3191 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 8736 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 585:
#line 3192 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 8742 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 586:
#line 3193 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 8748 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 587:
#line 3194 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CPU; }
#line 8754 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 588:
#line 3195 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 8760 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 589:
#line 3196 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 8766 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 590:
#line 3197 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 8772 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 591:
#line 3201 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 8780 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 592:
#line 3205 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 8788 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 593:
#line 3209 "parser_bison.y" /* yacc.c:1646  */
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
#line 8806 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 594:
#line 3223 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 8814 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 595:
#line 3228 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 8820 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 596:
#line 3229 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 8826 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 597:
#line 3232 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 8832 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 598:
#line 3233 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 8838 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 599:
#line 3237 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 8846 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 600:
#line 3243 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 8855 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 601:
#line 3248 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 8864 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 602:
#line 3253 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 8872 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 603:
#line 3258 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8878 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 604:
#line 3259 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 8884 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 605:
#line 3263 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 8892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 606:
#line 3267 "parser_bison.y" /* yacc.c:1646  */
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
#line 8914 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 607:
#line 3286 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 8920 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 608:
#line 3287 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 8926 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 609:
#line 3288 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 8932 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 610:
#line 3292 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1, NFPROTO_UNSPEC);
			}
#line 8940 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 611:
#line 3296 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val), NFPROTO_UNSPEC);
			}
#line 8948 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 612:
#line 3300 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 8956 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 613:
#line 3305 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 8962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 614:
#line 3306 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 8968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 615:
#line 3309 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 8974 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 616:
#line 3310 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 8980 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 617:
#line 3311 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_MARK; }
#line 8986 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 618:
#line 3312 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATE; }
#line 8992 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 619:
#line 3313 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 8998 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 620:
#line 3314 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 9004 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 621:
#line 3315 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 9010 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 622:
#line 3316 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 9016 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 623:
#line 3317 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9022 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 624:
#line 3318 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 625:
#line 3319 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 626:
#line 3320 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 627:
#line 3321 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 9046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 628:
#line 3322 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 9052 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 630:
#line 3326 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 631:
#line 3327 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9064 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 632:
#line 3328 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9070 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 633:
#line 3329 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9076 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 634:
#line 3330 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 635:
#line 3331 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9088 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 637:
#line 3335 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 9094 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 638:
#line 3336 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 9100 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3339 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 640:
#line 3340 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9112 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 641:
#line 3343 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 9118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 642:
#line 3344 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 9124 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3345 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 9130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 644:
#line 3346 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 9136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 647:
#line 3354 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9146 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 648:
#line 3360 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9156 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 649:
#line 3368 "parser_bison.y" /* yacc.c:1646  */
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
#line 9173 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 650:
#line 3381 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 9181 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 651:
#line 3387 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].expr)->ops->type == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9192 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 668:
#line 3414 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				(yyval.expr)->payload.base	= (yyvsp[-4].val);
				(yyval.expr)->payload.offset	= (yyvsp[-2].val);
				(yyval.expr)->len			= (yyvsp[0].val);
				(yyval.expr)->dtype		= &integer_type;
			}
#line 9204 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 669:
#line 3423 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 9210 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 670:
#line 3424 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 9216 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 671:
#line 3425 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 9222 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 672:
#line 3429 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 9230 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 673:
#line 3434 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 9236 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 674:
#line 3435 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 9242 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 675:
#line 3436 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 9248 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 676:
#line 3440 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 9256 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 677:
#line 3445 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_VID; }
#line 9262 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 678:
#line 3446 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_CFI; }
#line 9268 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 679:
#line 3447 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_PCP; }
#line 9274 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 680:
#line 3448 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 9280 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 681:
#line 3452 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 9288 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 682:
#line 3457 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HRD; }
#line 9294 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 683:
#line 3458 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PRO; }
#line 9300 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 684:
#line 3459 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HLN; }
#line 9306 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 685:
#line 3460 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PLN; }
#line 9312 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 686:
#line 3461 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_OP; }
#line 9318 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 687:
#line 3465 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 9326 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 688:
#line 3470 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_VERSION; }
#line 9332 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 689:
#line 3471 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 9338 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 690:
#line 3472 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DSCP; }
#line 9344 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 691:
#line 3473 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ECN; }
#line 9350 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 692:
#line 3474 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 9356 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 693:
#line 3475 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ID; }
#line 9362 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 694:
#line 3476 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 9368 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 695:
#line 3477 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_TTL; }
#line 9374 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 696:
#line 3478 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 9380 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 697:
#line 3479 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 9386 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 698:
#line 3480 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_SADDR; }
#line 9392 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 699:
#line 3481 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DADDR; }
#line 9398 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 700:
#line 3485 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 9406 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 701:
#line 3490 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 9412 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 702:
#line 3491 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 9418 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 703:
#line 3492 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 9424 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 704:
#line 3493 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_ID; }
#line 9430 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 705:
#line 3494 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 9436 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 706:
#line 3495 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 9442 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 707:
#line 3496 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 9448 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 708:
#line 3500 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 9456 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 709:
#line 3505 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 9462 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 710:
#line 3506 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 9468 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 711:
#line 3507 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_ECN; }
#line 9474 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 712:
#line 3508 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 9480 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 713:
#line 3509 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 9486 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 714:
#line 3510 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 9492 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 715:
#line 3511 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 9498 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 716:
#line 3512 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 9504 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 717:
#line 3513 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 9510 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 718:
#line 3516 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 9518 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 719:
#line 3521 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 9524 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 720:
#line 3522 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 9530 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 721:
#line 3523 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 9536 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 722:
#line 3524 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 9542 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 723:
#line 3525 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 9548 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 724:
#line 3526 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 9554 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 725:
#line 3527 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 9560 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 726:
#line 3528 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 9566 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 727:
#line 3532 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 9574 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 728:
#line 3537 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 9580 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 729:
#line 3538 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 9586 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 730:
#line 3539 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 9592 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 731:
#line 3540 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SPI; }
#line 9598 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 732:
#line 3541 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 9604 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 733:
#line 3545 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 9612 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 734:
#line 3550 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SPI; }
#line 9618 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 735:
#line 3551 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 9624 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 736:
#line 3555 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 9632 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 737:
#line 3560 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 9638 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 738:
#line 3561 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 9644 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 739:
#line 3562 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_CPI; }
#line 9650 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 740:
#line 3566 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 9658 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 741:
#line 3571 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 9664 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 742:
#line 3572 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 9670 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 743:
#line 3573 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 9676 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 744:
#line 3574 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 9682 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 745:
#line 3578 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 9690 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 746:
#line 3583 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 9696 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 747:
#line 3584 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 9702 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 748:
#line 3585 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 9708 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 749:
#line 3586 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 9714 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 750:
#line 3590 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 9722 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 751:
#line 3594 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 9730 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 752:
#line 3598 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 9739 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 753:
#line 3604 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 9745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 754:
#line 3605 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 9751 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 755:
#line 3606 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 9757 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 756:
#line 3607 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 9763 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 757:
#line 3608 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 9769 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 758:
#line 3609 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 9775 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 759:
#line 3610 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 9781 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 760:
#line 3611 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 9787 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 761:
#line 3612 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 9793 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 762:
#line 3613 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 9799 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 763:
#line 3616 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 9805 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 764:
#line 3617 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 9811 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 765:
#line 3618 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 9817 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 766:
#line 3619 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 9823 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 767:
#line 3620 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 9829 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 768:
#line 3621 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 9835 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 769:
#line 3622 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 9841 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 770:
#line 3623 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 9847 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 771:
#line 3624 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 9853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 772:
#line 3625 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 9859 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 773:
#line 3626 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 9865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 774:
#line 3627 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 9871 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 775:
#line 3630 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 9877 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 776:
#line 3631 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 9883 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 777:
#line 3632 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 9889 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 778:
#line 3633 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 9895 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 779:
#line 3634 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 9901 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 780:
#line 3635 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 9907 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 781:
#line 3636 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 9913 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 782:
#line 3637 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 9919 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 783:
#line 3641 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 9927 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 784:
#line 3646 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 9933 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 785:
#line 3647 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 9939 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 786:
#line 3648 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 9945 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 787:
#line 3652 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 9953 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 788:
#line 3657 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 9959 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 789:
#line 3658 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 9965 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 790:
#line 3659 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 9971 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 791:
#line 3660 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 9977 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 799:
#line 3673 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 9985 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 800:
#line 3678 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 9991 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 801:
#line 3679 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 9997 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 802:
#line 3683 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 10005 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 803:
#line 3688 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 10011 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 804:
#line 3689 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 10017 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 805:
#line 3690 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_TYPE; }
#line 10023 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 806:
#line 3691 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 10029 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 807:
#line 3695 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 10037 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 808:
#line 3701 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 10045 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 809:
#line 3707 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 10053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 810:
#line 3712 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 10059 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 811:
#line 3716 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 10067 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 812:
#line 3721 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 10073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 813:
#line 3722 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 10079 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 814:
#line 3723 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 10085 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 815:
#line 3724 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 10091 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 816:
#line 3725 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 10097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 817:
#line 3726 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_ID; }
#line 10103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 818:
#line 3730 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 10111 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 819:
#line 3735 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 10117 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 820:
#line 3736 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 10123 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 821:
#line 3740 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 10131 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 822:
#line 3745 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 10137 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 823:
#line 3746 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 10143 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 824:
#line 3747 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_TYPE; }
#line 10149 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 825:
#line 3748 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 10155 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 826:
#line 3749 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 10161 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 827:
#line 3753 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 10177 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 828:
#line 3766 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 10183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 829:
#line 3767 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 10189 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 830:
#line 3768 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 10195 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 831:
#line 3769 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 10201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 832:
#line 3770 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_MH; }
#line 10207 "parser_bison.c" /* yacc.c:1646  */
    break;


#line 10211 "parser_bison.c" /* yacc.c:1646  */
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
#line 3773 "parser_bison.y" /* yacc.c:1906  */

