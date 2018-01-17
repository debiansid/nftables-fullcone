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
    METER = 333,
    METERS = 334,
    NUM = 335,
    STRING = 336,
    QUOTED_STRING = 337,
    ASTERISK_STRING = 338,
    LL_HDR = 339,
    NETWORK_HDR = 340,
    TRANSPORT_HDR = 341,
    BRIDGE = 342,
    ETHER = 343,
    SADDR = 344,
    DADDR = 345,
    TYPE = 346,
    VLAN = 347,
    ID = 348,
    CFI = 349,
    PCP = 350,
    ARP = 351,
    HTYPE = 352,
    PTYPE = 353,
    HLEN = 354,
    PLEN = 355,
    OPERATION = 356,
    IP = 357,
    HDRVERSION = 358,
    HDRLENGTH = 359,
    DSCP = 360,
    ECN = 361,
    LENGTH = 362,
    FRAG_OFF = 363,
    TTL = 364,
    PROTOCOL = 365,
    CHECKSUM = 366,
    ICMP = 367,
    CODE = 368,
    SEQUENCE = 369,
    GATEWAY = 370,
    MTU = 371,
    OPTIONS = 372,
    IP6 = 373,
    PRIORITY = 374,
    FLOWLABEL = 375,
    NEXTHDR = 376,
    HOPLIMIT = 377,
    ICMP6 = 378,
    PPTR = 379,
    MAXDELAY = 380,
    AH = 381,
    RESERVED = 382,
    SPI = 383,
    ESP = 384,
    COMP = 385,
    FLAGS = 386,
    CPI = 387,
    UDP = 388,
    SPORT = 389,
    DPORT = 390,
    UDPLITE = 391,
    CSUMCOV = 392,
    TCP = 393,
    ACKSEQ = 394,
    DOFF = 395,
    WINDOW = 396,
    URGPTR = 397,
    OPTION = 398,
    ECHO = 399,
    EOL = 400,
    MAXSEG = 401,
    NOOP = 402,
    SACK = 403,
    SACK0 = 404,
    SACK1 = 405,
    SACK2 = 406,
    SACK3 = 407,
    SACK_PERMITTED = 408,
    TIMESTAMP = 409,
    KIND = 410,
    COUNT = 411,
    LEFT = 412,
    RIGHT = 413,
    TSVAL = 414,
    TSECR = 415,
    DCCP = 416,
    SCTP = 417,
    VTAG = 418,
    RT = 419,
    RT0 = 420,
    RT2 = 421,
    SEG_LEFT = 422,
    ADDR = 423,
    HBH = 424,
    FRAG = 425,
    RESERVED2 = 426,
    MORE_FRAGMENTS = 427,
    DST = 428,
    MH = 429,
    META = 430,
    MARK = 431,
    IIF = 432,
    IIFNAME = 433,
    IIFTYPE = 434,
    OIF = 435,
    OIFNAME = 436,
    OIFTYPE = 437,
    SKUID = 438,
    SKGID = 439,
    NFTRACE = 440,
    RTCLASSID = 441,
    IBRIPORT = 442,
    OBRIPORT = 443,
    PKTTYPE = 444,
    CPU = 445,
    IIFGROUP = 446,
    OIFGROUP = 447,
    CGROUP = 448,
    CLASSID = 449,
    NEXTHOP = 450,
    CT = 451,
    L3PROTOCOL = 452,
    PROTO_SRC = 453,
    PROTO_DST = 454,
    ZONE = 455,
    DIRECTION = 456,
    EVENT = 457,
    EXPIRATION = 458,
    HELPER = 459,
    LABEL = 460,
    STATE = 461,
    STATUS = 462,
    ORIGINAL = 463,
    REPLY = 464,
    COUNTER = 465,
    NAME = 466,
    PACKETS = 467,
    BYTES = 468,
    AVGPKT = 469,
    COUNTERS = 470,
    QUOTAS = 471,
    LIMITS = 472,
    HELPERS = 473,
    LOG = 474,
    PREFIX = 475,
    GROUP = 476,
    SNAPLEN = 477,
    QUEUE_THRESHOLD = 478,
    LEVEL = 479,
    LIMIT = 480,
    RATE = 481,
    BURST = 482,
    OVER = 483,
    UNTIL = 484,
    QUOTA = 485,
    USED = 486,
    NANOSECOND = 487,
    MICROSECOND = 488,
    MILLISECOND = 489,
    SECOND = 490,
    MINUTE = 491,
    HOUR = 492,
    DAY = 493,
    WEEK = 494,
    _REJECT = 495,
    WITH = 496,
    ICMPX = 497,
    SNAT = 498,
    DNAT = 499,
    MASQUERADE = 500,
    REDIRECT = 501,
    RANDOM = 502,
    FULLY_RANDOM = 503,
    PERSISTENT = 504,
    QUEUE = 505,
    QUEUENUM = 506,
    BYPASS = 507,
    FANOUT = 508,
    DUP = 509,
    FWD = 510,
    NUMGEN = 511,
    INC = 512,
    MOD = 513,
    OFFSET = 514,
    JHASH = 515,
    SYMHASH = 516,
    SEED = 517,
    POSITION = 518,
    COMMENT = 519,
    XML = 520,
    JSON = 521,
    NOTRACK = 522,
    EXISTS = 523,
    MISSING = 524,
    EXTHDR = 525
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
#define METER 333
#define METERS 334
#define NUM 335
#define STRING 336
#define QUOTED_STRING 337
#define ASTERISK_STRING 338
#define LL_HDR 339
#define NETWORK_HDR 340
#define TRANSPORT_HDR 341
#define BRIDGE 342
#define ETHER 343
#define SADDR 344
#define DADDR 345
#define TYPE 346
#define VLAN 347
#define ID 348
#define CFI 349
#define PCP 350
#define ARP 351
#define HTYPE 352
#define PTYPE 353
#define HLEN 354
#define PLEN 355
#define OPERATION 356
#define IP 357
#define HDRVERSION 358
#define HDRLENGTH 359
#define DSCP 360
#define ECN 361
#define LENGTH 362
#define FRAG_OFF 363
#define TTL 364
#define PROTOCOL 365
#define CHECKSUM 366
#define ICMP 367
#define CODE 368
#define SEQUENCE 369
#define GATEWAY 370
#define MTU 371
#define OPTIONS 372
#define IP6 373
#define PRIORITY 374
#define FLOWLABEL 375
#define NEXTHDR 376
#define HOPLIMIT 377
#define ICMP6 378
#define PPTR 379
#define MAXDELAY 380
#define AH 381
#define RESERVED 382
#define SPI 383
#define ESP 384
#define COMP 385
#define FLAGS 386
#define CPI 387
#define UDP 388
#define SPORT 389
#define DPORT 390
#define UDPLITE 391
#define CSUMCOV 392
#define TCP 393
#define ACKSEQ 394
#define DOFF 395
#define WINDOW 396
#define URGPTR 397
#define OPTION 398
#define ECHO 399
#define EOL 400
#define MAXSEG 401
#define NOOP 402
#define SACK 403
#define SACK0 404
#define SACK1 405
#define SACK2 406
#define SACK3 407
#define SACK_PERMITTED 408
#define TIMESTAMP 409
#define KIND 410
#define COUNT 411
#define LEFT 412
#define RIGHT 413
#define TSVAL 414
#define TSECR 415
#define DCCP 416
#define SCTP 417
#define VTAG 418
#define RT 419
#define RT0 420
#define RT2 421
#define SEG_LEFT 422
#define ADDR 423
#define HBH 424
#define FRAG 425
#define RESERVED2 426
#define MORE_FRAGMENTS 427
#define DST 428
#define MH 429
#define META 430
#define MARK 431
#define IIF 432
#define IIFNAME 433
#define IIFTYPE 434
#define OIF 435
#define OIFNAME 436
#define OIFTYPE 437
#define SKUID 438
#define SKGID 439
#define NFTRACE 440
#define RTCLASSID 441
#define IBRIPORT 442
#define OBRIPORT 443
#define PKTTYPE 444
#define CPU 445
#define IIFGROUP 446
#define OIFGROUP 447
#define CGROUP 448
#define CLASSID 449
#define NEXTHOP 450
#define CT 451
#define L3PROTOCOL 452
#define PROTO_SRC 453
#define PROTO_DST 454
#define ZONE 455
#define DIRECTION 456
#define EVENT 457
#define EXPIRATION 458
#define HELPER 459
#define LABEL 460
#define STATE 461
#define STATUS 462
#define ORIGINAL 463
#define REPLY 464
#define COUNTER 465
#define NAME 466
#define PACKETS 467
#define BYTES 468
#define AVGPKT 469
#define COUNTERS 470
#define QUOTAS 471
#define LIMITS 472
#define HELPERS 473
#define LOG 474
#define PREFIX 475
#define GROUP 476
#define SNAPLEN 477
#define QUEUE_THRESHOLD 478
#define LEVEL 479
#define LIMIT 480
#define RATE 481
#define BURST 482
#define OVER 483
#define UNTIL 484
#define QUOTA 485
#define USED 486
#define NANOSECOND 487
#define MICROSECOND 488
#define MILLISECOND 489
#define SECOND 490
#define MINUTE 491
#define HOUR 492
#define DAY 493
#define WEEK 494
#define _REJECT 495
#define WITH 496
#define ICMPX 497
#define SNAT 498
#define DNAT 499
#define MASQUERADE 500
#define REDIRECT 501
#define RANDOM 502
#define FULLY_RANDOM 503
#define PERSISTENT 504
#define QUEUE 505
#define QUEUENUM 506
#define BYPASS 507
#define FANOUT 508
#define DUP 509
#define FWD 510
#define NUMGEN 511
#define INC 512
#define MOD 513
#define OFFSET 514
#define JHASH 515
#define SYMHASH 516
#define SEED 517
#define POSITION 518
#define COMMENT 519
#define XML 520
#define JSON 521
#define NOTRACK 522
#define EXISTS 523
#define MISSING 524
#define EXTHDR 525

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
	struct counter		*counter;
	struct quota		*quota;
	struct ct		*ct;
	struct limit		*limit;
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;
	const struct exthdr_desc *exthdr_desc;

#line 781 "parser_bison.c" /* yacc.c:355  */
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

#line 811 "parser_bison.c" /* yacc.c:358  */

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
#define YYLAST   4410

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  280
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  275
/* YYNRULES -- Number of rules.  */
#define YYNRULES  837
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1279

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   525

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   275,     2,     2,     2,
     276,   277,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   271,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   278,     2,   279,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   272,   274,   273,     2,     2,     2,     2,
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
     265,   266,   267,   268,   269,   270
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   713,   713,   714,   732,   733,   736,   737,   740,   748,
     762,   770,   771,   772,   773,   805,   806,   807,   808,   809,
     810,   811,   812,   813,   814,   815,   816,   817,   820,   824,
     831,   835,   843,   847,   851,   858,   865,   869,   878,   882,
     886,   891,   897,   903,   907,   914,   918,   926,   933,   940,
     944,   953,   957,   961,   965,   971,   977,   981,   985,   989,
     993,   997,  1001,  1005,  1009,  1013,  1019,  1023,  1027,  1031,
    1035,  1039,  1043,  1047,  1051,  1055,  1059,  1063,  1067,  1071,
    1075,  1079,  1083,  1087,  1091,  1095,  1099,  1103,  1107,  1111,
    1115,  1121,  1125,  1129,  1133,  1137,  1141,  1147,  1151,  1155,
    1159,  1163,  1167,  1171,  1177,  1184,  1190,  1198,  1207,  1208,
    1211,  1212,  1213,  1214,  1215,  1216,  1217,  1218,  1221,  1222,
    1225,  1226,  1229,  1238,  1244,  1258,  1259,  1260,  1261,  1262,
    1273,  1283,  1293,  1304,  1315,  1324,  1338,  1344,  1345,  1346,
    1347,  1348,  1349,  1357,  1362,  1363,  1364,  1365,  1370,  1375,
    1380,  1385,  1390,  1393,  1394,  1397,  1401,  1404,  1405,  1406,
    1410,  1415,  1416,  1417,  1418,  1429,  1438,  1447,  1456,  1461,
    1466,  1469,  1473,  1479,  1480,  1483,  1497,  1498,  1518,  1523,
    1524,  1525,  1526,  1533,  1534,  1535,  1536,  1543,  1544,  1545,
    1546,  1552,  1553,  1554,  1555,  1562,  1563,  1564,  1565,  1566,
    1569,  1597,  1598,  1601,  1602,  1605,  1616,  1617,  1620,  1623,
    1624,  1625,  1628,  1643,  1644,  1647,  1648,  1649,  1650,  1651,
    1652,  1655,  1663,  1670,  1677,  1684,  1691,  1698,  1705,  1713,
    1721,  1725,  1732,  1739,  1751,  1755,  1762,  1766,  1772,  1784,
    1790,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,  1805,
    1806,  1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,  1817,
    1821,  1827,  1833,  1838,  1847,  1852,  1857,  1860,  1866,  1867,
    1869,  1873,  1881,  1885,  1888,  1892,  1898,  1899,  1902,  1908,
    1912,  1915,  1920,  1925,  1930,  1935,  1940,  1946,  1974,  1978,
    1982,  1986,  1990,  1996,  2000,  2003,  2007,  2013,  2022,  2041,
    2049,  2050,  2051,  2054,  2055,  2058,  2059,  2074,  2090,  2098,
    2099,  2100,  2103,  2104,  2105,  2106,  2121,  2122,  2123,  2124,
    2125,  2128,  2131,  2138,  2142,  2153,  2164,  2174,  2180,  2183,
    2188,  2195,  2196,  2197,  2198,  2199,  2200,  2201,  2202,  2203,
    2204,  2207,  2208,  2212,  2218,  2219,  2225,  2226,  2232,  2233,
    2239,  2242,  2243,  2262,  2263,  2266,  2270,  2273,  2279,  2285,
    2296,  2297,  2298,  2301,  2302,  2303,  2306,  2310,  2314,  2319,
    2324,  2328,  2332,  2338,  2339,  2342,  2345,  2349,  2354,  2360,
    2361,  2364,  2367,  2371,  2375,  2379,  2384,  2391,  2396,  2404,
    2411,  2412,  2418,  2419,  2420,  2423,  2424,  2427,  2433,  2437,
    2440,  2445,  2451,  2452,  2458,  2459,  2462,  2463,  2466,  2472,
    2481,  2482,  2485,  2492,  2495,  2501,  2505,  2508,  2514,  2524,
    2530,  2547,  2548,  2555,  2564,  2575,  2576,  2577,  2578,  2579,
    2580,  2581,  2582,  2583,  2584,  2585,  2586,  2589,  2612,  2613,
    2614,  2617,  2618,  2619,  2620,  2621,  2624,  2628,  2631,  2632,
    2636,  2642,  2643,  2649,  2650,  2656,  2657,  2663,  2666,  2667,
    2686,  2692,  2698,  2709,  2710,  2711,  2714,  2720,  2721,  2722,
    2725,  2732,  2737,  2742,  2745,  2749,  2753,  2759,  2760,  2767,
    2773,  2774,  2777,  2783,  2787,  2790,  2794,  2800,  2801,  2804,
    2805,  2808,  2809,  2812,  2823,  2831,  2852,  2860,  2863,  2864,
    2867,  2882,  2889,  2894,  2905,  2927,  2935,  2939,  2943,  2947,
    2953,  2959,  2967,  2968,  2969,  2972,  2973,  2977,  2983,  2984,
    2990,  2991,  2997,  2998,  3004,  3007,  3008,  3027,  3028,  3031,
    3039,  3040,  3041,  3042,  3043,  3044,  3045,  3046,  3047,  3048,
    3049,  3050,  3053,  3054,  3055,  3056,  3057,  3064,  3071,  3078,
    3085,  3092,  3099,  3106,  3113,  3120,  3127,  3136,  3137,  3138,
    3139,  3140,  3141,  3144,  3148,  3152,  3156,  3160,  3164,  3170,
    3174,  3178,  3193,  3194,  3197,  3198,  3199,  3200,  3203,  3204,
    3205,  3206,  3207,  3208,  3209,  3210,  3211,  3212,  3213,  3214,
    3215,  3216,  3217,  3218,  3219,  3220,  3223,  3227,  3231,  3245,
    3251,  3252,  3255,  3256,  3259,  3265,  3270,  3275,  3281,  3282,
    3285,  3289,  3309,  3310,  3311,  3314,  3318,  3322,  3328,  3329,
    3332,  3333,  3334,  3335,  3336,  3337,  3338,  3339,  3340,  3341,
    3342,  3343,  3344,  3345,  3346,  3349,  3350,  3351,  3352,  3353,
    3354,  3355,  3358,  3359,  3362,  3363,  3366,  3367,  3368,  3369,
    3372,  3373,  3376,  3382,  3390,  3403,  3409,  3418,  3419,  3420,
    3421,  3422,  3423,  3424,  3425,  3426,  3427,  3428,  3429,  3430,
    3431,  3432,  3433,  3436,  3446,  3447,  3448,  3451,  3457,  3458,
    3459,  3462,  3468,  3469,  3470,  3471,  3474,  3480,  3481,  3482,
    3483,  3484,  3487,  3493,  3494,  3495,  3496,  3497,  3498,  3499,
    3500,  3501,  3502,  3503,  3504,  3507,  3513,  3514,  3515,  3516,
    3517,  3518,  3519,  3522,  3528,  3529,  3530,  3531,  3532,  3533,
    3534,  3535,  3536,  3538,  3544,  3545,  3546,  3547,  3548,  3549,
    3550,  3551,  3554,  3560,  3561,  3562,  3563,  3564,  3567,  3573,
    3574,  3577,  3583,  3584,  3585,  3588,  3594,  3595,  3596,  3597,
    3600,  3606,  3607,  3608,  3609,  3612,  3616,  3620,  3627,  3628,
    3629,  3630,  3631,  3632,  3633,  3634,  3635,  3636,  3639,  3640,
    3641,  3642,  3643,  3644,  3645,  3646,  3647,  3648,  3649,  3650,
    3653,  3654,  3655,  3656,  3657,  3658,  3659,  3660,  3663,  3669,
    3670,  3671,  3674,  3680,  3681,  3682,  3683,  3686,  3687,  3688,
    3689,  3690,  3691,  3692,  3695,  3701,  3702,  3705,  3711,  3712,
    3713,  3714,  3717,  3723,  3729,  3735,  3738,  3744,  3745,  3746,
    3747,  3748,  3749,  3752,  3758,  3759,  3762,  3768,  3769,  3770,
    3771,  3772,  3775,  3789,  3790,  3791,  3792,  3793
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
  "\"performance\"", "\"size\"", "\"flow\"", "\"meter\"", "\"meters\"",
  "\"number\"", "\"string\"", "\"quoted string\"",
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
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,    61,   123,   125,   124,    36,    40,    41,    91,    93
};
# endif

#define YYPACT_NINF -1009

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1009)))

#define YYTABLE_NINF -652

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1009,  4180, -1009,   343, -1009, -1009,     9,    54,   773,   773,
     773,   773,   773,   773, -1009, -1009,  2414,   119,   583,   139,
     511,  1271,   230,   360,    81,  3548,    19,    97, -1009, -1009,
   -1009, -1009,    11,   773,   773,   773, -1009, -1009, -1009,   368,
   -1009,    54, -1009,    54,   -39,  3233, -1009,   343, -1009,    61,
     -21,    68,  3233,    54, -1009,   -68, -1009, -1009,   773, -1009,
     773,   773,   773,   773,   773,   185,   773,   773,   773, -1009,
     773, -1009,   773,   773,   773,   773,   773,   773,   188,   773,
     773,   773, -1009,   773,   773,   773,   773,  1054,   773,   773,
     773,   773,    78,   773,   773,   142,   773,  1071,  1088,  1092,
     773,   773, -1009,   773,  1199,  1362,   773, -1009,   773,   773,
     773,   773,   773,   381,   773, -1009,   773, -1009,   569,   425,
   -1009, -1009, -1009, -1009,   378,   615,   585,  1417,   852,  1000,
    1323,   745,   186,    49,   223,   345,  1621,    33,   128,   930,
     302,   306,   143,   437,   162,   295,  1718, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,  2121,    -2,  3431,   218,   471,
      54,  3548, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009,   131, -1009, -1009, -1009, -1009, -1009, -1009,   918,   773,
      54,   276,   237,    65, -1009, -1009, -1009, -1009,   421, -1009,
     361, -1009, -1009, -1009,    54,    54, -1009, -1009,    54,  1943,
    2121,   330, -1009,    79,   126, -1009, -1009, -1009, -1009, -1009,
   -1009,   457,   476, -1009,   549, -1009,   304,  3233, -1009, -1009,
   -1009, -1009,   236, -1009,   205, -1009, -1009, -1009,   332, -1009,
    2175, -1009,     1, -1009,    64, -1009, -1009, -1009,   380, -1009,
   -1009,   540, -1009, -1009, -1009,   427,   559,   570,   316, -1009,
     109, -1009,  2691, -1009, -1009, -1009,   560, -1009, -1009, -1009,
     568, -1009,  3037,   324,   346, -1009, -1009,   348, -1009, -1009,
   -1009,   379,   621,  3233,   -21,    68, -1009,   -68, -1009,   773,
     276,   237,    65,  3233, -1009, -1009, -1009, -1009,   -68, -1009,
   -1009,   773, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     773, -1009, -1009, -1009, -1009, -1009,   773,   773, -1009, -1009,
     636,   773, -1009,   773, -1009,   773, -1009,   773, -1009, -1009,
   -1009, -1009,   773, -1009,   773, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009,   773, -1009,    54, -1009, -1009, -1009, -1009,   667,
   -1009, -1009, -1009, -1009, -1009,   690,    17, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,  1392, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,    37, -1009, -1009,   419, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   305,
   -1009, -1009, -1009, -1009,   462,   108,   464,   631, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,   449, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009,   131, -1009, -1009,   645, -1009, -1009,
     281, -1009, -1009, -1009, -1009,   648, -1009, -1009, -1009, -1009,
   -1009,  3548, -1009, -1009,   465,   691,   700,   305,   702,  2918,
    2918,   281,  2918,   663,  2918,  3431, -1009,  3037,    25, -1009,
     755, -1009, -1009,   666,   670,   236, -1009,    70,   755,   672,
     674,   676,   755,   205, -1009,   -25, -1009,  2918, -1009, -1009,
    2294,   378,   615,   585,  1417, -1009,  1000,   454, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009,   513,   730,   740,   490,
     398,   152, -1009, -1009, -1009, -1009, -1009,   761,   614,   760,
   -1009, -1009, -1009,   763, -1009, -1009, -1009, -1009, -1009,   765,
     766, -1009,   770, -1009, -1009, -1009, -1009,   774, -1009,  2490,
   -1009,   774,  2918, -1009, -1009,   380, -1009,   777, -1009,    54,
      10, -1009,  3548,  3548,  3548,  3548,  3548,  3548,    34,  3037,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009,    54, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009,   781, -1009,   520,   775,   759,   516,   251,   788, -1009,
   -1009, -1009,  2759,  2918,  2918,   343,   781, -1009, -1009, -1009,
   -1009, -1009,   718, -1009, -1009,   527,   529,   531, -1009,   534,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     773, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   729,
     425, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009,   698, -1009,   734,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   470,
   -1009,   735,   737,   561, -1009, -1009, -1009,   550,   610, -1009,
   -1009,   747,    24,   113,   -18,   820,  3548,  2918,  2918,   792,
    2918, -1009, -1009,   752, -1009,    24,   803, -1009, -1009,   549,
     558,   -18, -1009,   501,   788,   549, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009,   722,   225, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009,   776,   779,   796,   780, -1009,  2918,
     869,  3665,  3904,  3665,  3665,  3665,   797,  3665,  3665,   103,
    2918,   774,  3966,  3966,  2918,   614,  2918,   614, -1009, -1009,
     313, -1009,  3548, -1009, -1009, -1009,   427,   559,   570, -1009,
      54,   549, -1009, -1009,  3904,  3904,  3904,  3904,  3904,  3904,
    3904,   798,  3904,  3904,  3037, -1009, -1009, -1009, -1009,   234,
    1528,   521,   138, -1009, -1009, -1009, -1009, -1009,   620, -1009,
   -1009,   887, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009,   616, -1009, -1009, -1009,   561,   104,   819, -1009,
   -1009,   822,    53, -1009, -1009,   677, -1009,   824, -1009,   -18,
   -1009,   820,  3233,   -18, -1009, -1009,  2918, -1009,    69,   677,
    2918, -1009,  3836, -1009,   -18,  3037, -1009, -1009, -1009, -1009,
     896, -1009,   826,   829, -1009,   832, -1009,  2918, -1009, -1009,
   -1009, -1009,   513,   730,   740, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009,   614, -1009,   614,   774,
   -1009,  3233, -1009,  3114,    28, -1009, -1009, -1009, -1009,   520,
     775,   759, -1009, -1009, -1009, -1009,   640,    54,    54,    54,
     838,   719,    54,    54,    54, -1009, -1009, -1009,   343,   542,
     841, -1009, -1009, -1009,   343,   343,   343,   824,   824,   654,
     552,   849,    40,   903, -1009, -1009, -1009,   343,   665,    40,
     903, -1009, -1009, -1009,   343,   344,  1753,  1383,   825, -1009,
     854, -1009, -1009,   857, -1009, -1009,   253, -1009,   789,   712,
     861, -1009, -1009, -1009, -1009,   669,   -18, -1009,   789,   712,
   -1009, -1009,   549, -1009,   788, -1009,   225, -1009, -1009, -1009,
   -1009,   774,   774,   671,   942,   549, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009,    54, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009,   920, -1009, -1009, -1009,   343,   343,   -68,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     576, -1009, -1009, -1009, -1009,   448, -1009, -1009,   -68,   375,
     448, -1009, -1009, -1009, -1009, -1009,   551, -1009,   561,   877,
     773,   343, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     712,   880, -1009,    24, -1009,   712, -1009, -1009, -1009, -1009,
    1030,  3114, -1009,   692,   697,   704, -1009,   707,   708,   711,
     904, -1009, -1009, -1009,    40, -1009,   903, -1009, -1009,   385,
   -1009,   343, -1009,   876,   343, -1009, -1009,     7, -1009, -1009,
     549, -1009, -1009, -1009,   716, -1009, -1009, -1009,   961, -1009,
   -1009,   343,   343,   343,   576, -1009,   171, -1009, -1009, -1009,
   -1009, -1009,  1978,  1400,   905, -1009,   114,    96,   785,   912,
     873, -1009, -1009, -1009, -1009, -1009, -1009,   343,   343,   343,
     343,   756,   343, -1009, -1009, -1009,   343, -1009, -1009, -1009,
     343, -1009, -1009, -1009, -1009,    47, -1009, -1009, -1009, -1009,
     343, -1009, -1009, -1009,   914, -1009, -1009, -1009, -1009
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,   213,   213,
     213,   213,   213,   213,   217,   220,   213,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   219,   218,
     215,   216,     0,   213,   213,   213,    12,    11,     3,     0,
      15,     0,   214,     0,   230,     0,    10,     0,   208,     0,
      28,    30,     0,     0,   143,     0,   160,    16,   213,    17,
     213,   213,   213,   213,   213,     0,   213,   213,   213,    18,
     213,    19,   213,   213,   213,   213,   213,   213,     0,   213,
     213,   213,    20,   213,   234,   213,   234,   234,   213,   213,
     234,   234,     0,   213,   234,     0,   213,   234,   234,   234,
     213,   213,    21,   213,   234,   234,   213,    22,   213,   213,
     213,   213,   234,     0,   213,    23,   213,    24,     0,     0,
     424,   209,   210,   211,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,     0,     0,     0,     0,     0,
       0,     0,    27,   422,   421,   425,   426,   122,   435,   430,
     570,   433,   434,   431,   432,   427,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   670,
     671,   672,   428,   797,   798,   799,   800,   801,   802,   803,
     429,     0,   120,   121,    25,   106,   109,    26,   110,   213,
       0,    37,     0,   302,    14,    13,   221,   222,     0,   231,
       0,   563,   564,   565,     0,     0,   568,   414,     0,     0,
       0,   270,   278,     0,   302,   322,   329,   330,   375,   381,
     397,     0,     0,   599,     7,    33,   236,   238,   239,   241,
     260,   244,   268,   247,   276,   248,   249,   250,   323,   251,
       0,   254,   374,   255,   380,   256,   257,   252,   395,   258,
     243,     0,   413,   242,   448,   451,   453,   455,   457,   458,
     467,   469,     0,   468,   419,   259,   570,   246,   253,   245,
     427,     8,     0,     0,     0,    32,   224,     0,    36,   154,
     153,     0,     0,     0,    43,    45,   143,     0,   160,   213,
      50,     0,   302,     0,    56,    57,    58,    59,     0,    60,
     497,   213,    62,    65,    63,    66,   235,    67,    68,    69,
     213,    70,    72,    88,    87,    82,   213,   234,    86,    85,
       0,   213,    75,   213,    73,   213,    76,   213,    79,    81,
      78,    93,   213,    91,   213,    94,    96,    97,    98,    99,
     100,   103,   213,   102,     0,   674,   675,   676,   423,     0,
     441,   442,   443,   444,   445,   447,     0,   678,   679,   680,
     677,   685,   682,   683,   684,   681,   687,   688,   689,   690,
     691,   686,   703,   704,   698,   693,   694,   695,   696,   697,
     699,   700,   701,   702,   692,   706,   709,   708,   707,   710,
     711,   712,   705,   721,   722,   714,   715,   716,   718,   717,
     719,   720,   713,   724,   729,   726,   725,   730,   728,   727,
     731,   723,   734,   737,   733,   735,   736,   732,   740,   739,
     738,   742,   743,   744,   741,   748,   749,   746,   747,   745,
     754,   751,   752,   753,   750,   766,   760,   763,   764,   758,
     759,   761,   762,   765,   767,     0,   755,   791,   789,   790,
     788,   796,   793,   794,   795,   792,   810,   608,   809,   614,
     609,   808,   811,   612,   613,     0,   610,   807,     0,   812,
     815,   814,   806,   805,   804,   822,   819,   817,   818,   820,
     821,   816,   825,   824,   823,   829,   828,   831,   827,   830,
     826,   571,   574,   575,   576,   577,   569,   572,   573,   628,
     629,   621,   622,   620,   630,   631,   649,   624,   633,   626,
     627,   632,   623,   625,   618,   619,   647,   646,   648,     0,
     615,   634,   603,   602,     0,   467,     0,     0,   834,   833,
     835,   836,   837,   832,   420,     0,   105,   111,   112,   114,
     113,   116,   117,   115,   118,   502,   226,     0,   494,    38,
     311,   505,    41,   300,   301,     0,   496,    39,   229,   410,
     411,     0,   566,   567,     0,   571,   569,     0,   615,     0,
       0,   311,     0,     0,     0,     0,     6,     0,     0,   471,
       0,   237,   240,     0,     0,   269,   272,     0,     0,     0,
       0,     0,     0,   277,   279,     0,   321,     0,   359,   538,
       0,   530,   533,   534,   531,   537,   532,     0,   541,   539,
     540,   536,   535,   527,   528,   341,   344,   346,   348,   350,
     351,   356,   363,   360,   361,   362,   364,   366,   328,   331,
     332,   529,   333,   340,   334,   337,   338,   335,   336,     0,
     365,   339,     0,   392,   393,   394,   373,   378,   390,     0,
     379,   384,     0,   404,   405,   396,   398,   401,   402,     0,
       0,   415,     0,     0,     0,     0,     0,     0,     0,     0,
     557,   558,   559,   560,   561,   562,   462,     0,   530,   533,
     534,   531,   551,   532,   552,   550,   549,   553,   547,   548,
     546,   554,   555,   556,   542,   543,   463,   464,   465,   513,
     514,   507,   506,   518,   520,   522,   524,   525,   512,   544,
     545,   515,     0,     0,     0,     0,   492,   491,   125,   137,
     144,   161,     0,   232,    42,     0,     0,     0,    49,     0,
     502,    51,    54,    52,    55,    61,   502,    71,    84,    83,
     213,    89,    74,    77,    80,    92,    95,   101,   104,     0,
       0,   440,   438,   439,   437,   771,   778,   768,   770,   769,
     773,   774,   775,   776,   777,   772,   779,   757,   611,     0,
     635,   636,   642,   638,   643,   637,   639,   640,   616,     0,
     641,     0,     0,   600,   436,   107,   119,     0,     0,   309,
     310,     0,     0,     0,   406,   408,     0,     0,     0,   641,
       0,   271,   299,     0,   308,     0,   387,   389,   488,     7,
       7,   480,   482,   525,   487,     7,   470,   233,   274,   275,
     273,   292,   291,     0,     0,   290,   286,   281,   282,   283,
     284,   287,   285,   280,     0,     0,     0,     0,   370,     0,
     367,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   372,     0,     0,     0,     0,     0,   382,   400,   399,
       0,   417,     0,   416,   449,   450,   452,   454,   456,   459,
       0,     7,   261,   466,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   508,   597,   656,     9,     0,
       0,     0,     0,   228,   125,   137,   144,   161,     0,    64,
      90,     0,   446,   782,   781,   780,   783,   784,   785,   786,
     787,   756,     0,   644,   645,   617,   600,   600,     0,   607,
     187,     0,     0,   304,   303,   305,   409,     0,   486,   407,
     483,   479,     0,   477,   598,   596,     0,   654,     0,   305,
       0,   474,     0,   475,   481,   473,   472,   289,   295,   296,
     288,   294,     0,     0,   327,     0,   371,     0,   342,   331,
     340,   343,   345,   347,   349,   357,   358,   352,   355,   354,
     353,   368,   650,   651,   652,   653,   376,   391,   383,   385,
     403,     0,   263,     0,     0,   264,   511,   516,   517,   519,
     521,   523,   510,   460,   461,   526,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,   127,   126,     0,     0,
       0,    31,   139,   138,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,   146,   145,     0,     0,     0,
       0,    35,   163,   162,     0,     0,     0,     0,     0,   187,
       0,   813,   604,     0,   606,   601,     0,   493,     0,   312,
       0,   495,   212,   485,   484,     0,   478,   655,     0,   312,
     307,   388,     7,   525,   489,   490,     0,   324,   325,   326,
     369,   377,   386,     0,     0,     7,   262,   509,   223,   136,
     225,   143,   160,   124,     0,   227,   178,   178,   178,   128,
     206,   207,   205,     0,   140,   141,   142,     0,     0,     0,
     174,   173,   171,   172,   195,   197,   198,   196,   199,   176,
       0,   175,   157,   158,   159,     0,   156,   152,     0,     0,
       0,   170,    44,    46,    47,    48,     0,   673,   600,     0,
       0,     0,   189,   188,   190,   316,   317,   318,   319,   320,
     312,     0,   504,     0,   418,   312,   298,   476,   293,   412,
       0,   266,   265,     0,     0,     0,   178,     0,     0,     0,
       0,   149,   150,   151,     0,   147,     0,   148,   169,     0,
     168,     0,   605,     0,     0,    40,   503,     0,   306,   297,
       7,   137,   144,   161,     0,   179,   191,   183,   204,   177,
     155,     0,     0,     0,     0,    53,     0,   501,   315,   313,
     314,   267,     0,     0,     0,   187,     0,     0,     0,     0,
       0,   165,   167,   166,   164,   499,   498,     0,     0,     0,
       0,     0,     0,   181,   180,   182,     0,   193,   192,   194,
       0,   185,   184,   186,   203,     0,   500,   129,   130,   131,
       0,   132,   135,   133,     0,   201,   200,   134,   202
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1009, -1009,    -1,  -789,     5, -1009, -1009,   983, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009,  -189, -1009,   693, -1009,    80,  -312,  -888,  -311,  -887,
    -313,   -57,  -185,  -308,  -884,  -899, -1009,  -182, -1000,  -980,
   -1009, -1009, -1008, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     118,  -208,  -409, -1009,   -20,   423,   404, -1009,    18,   -12,
     122,  -790, -1009, -1009,    93,   946,   782,   911,    -3, -1009,
   -1009,  -243, -1009, -1009, -1009, -1009,   -83, -1009, -1009, -1009,
     415, -1009, -1009, -1009,   410, -1009, -1009, -1009,   -61, -1009,
     810,  -811,    72, -1009,   446,  -993,   -29, -1009, -1009, -1009,
   -1009, -1009,  -695,   189,   191,   194, -1009,   200, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,   689, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,  -257,   193, -1009, -1009, -1009,
     386, -1009,   197, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     389, -1009, -1009,   -47,   453,   -24,     2, -1009, -1009, -1009,
     308,   390,   413,   416, -1009,  -159,  -133, -1009, -1009, -1009,
    -594, -1009,  -148,     0, -1009,   264,   219, -1009,  -955, -1009,
    -742,  -873, -1009, -1009, -1009,  -123,   794,  -120,   793,  1033,
   -1009, -1009,  -393,  -107,   815, -1009,   840,  -295,   224,   235,
     242, -1009,  -276,  -596, -1009,  -248,   469,  -630, -1009,  -924,
     -16,   915, -1009,   -27, -1009,  -871, -1009,    -5,     8, -1009,
      20,   658,    38,   922,   923, -1009, -1009, -1009,  -445,  -236,
   -1009, -1009, -1009,   148, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1042,   607,  1043,    38,    39,    40,    59,    69,
      71,    82,   102,   107,   115,   117,   214,   217,   218,   574,
     815,   215,   172,   303,  1038,   919,   304,   920,   307,   921,
     308,  1145,  1146,   311,   922,  1057,  1132,  1139,  1140,  1187,
    1236,  1238,  1076,  1237,  1141,  1044,  1276,  1240,  1045,  1122,
    1115,   173,  1083,    41,    42,   220,    44,  1109,    54,  1111,
     221,  1116,   753,   229,    45,   313,   958,   337,  1046,   256,
     257,   258,   259,   260,   902,  1014,  1015,   261,   262,   615,
     616,   263,   264,   623,   624,   862,   856,   980,   981,   265,
     585,   955,  1081,   266,   821,  1172,  1170,   267,   268,   626,
     269,   270,   645,   646,   647,   648,   649,   650,   651,   998,
     652,   653,   654,   655,   656,   657,   658,   271,   272,   676,
     273,   274,   680,   275,   276,   677,   678,   277,   278,   685,
     686,   687,   688,   823,   824,   279,   591,   280,   281,   690,
     691,   282,   283,   174,   175,   660,   284,   178,   784,   385,
     386,   285,   286,   287,   288,   289,   290,   726,   727,   728,
     729,   291,   292,   293,   608,   609,   962,   963,   840,   841,
     959,   960,   842,  1092,   745,   578,   579,   586,   587,   331,
    1247,  1164,   817,   581,   582,   294,   731,   732,   733,   734,
     735,   736,   843,   738,   661,   662,   663,   741,   742,   295,
     664,   526,   527,   180,   297,   949,   554,   665,   666,   495,
     667,   496,   668,   549,   550,   808,   809,   945,   551,   669,
     670,   298,   299,   671,   186,   379,   187,   390,   188,   395,
     189,   401,   190,   414,   191,   422,   192,   432,   193,   441,
     194,   447,   195,   450,   196,   454,   197,   459,   198,   464,
     199,   476,   797,   941,   200,   480,   201,   485,   202,   203,
     504,   204,   497,   205,   499,   206,   501,   207,   511,   208,
     514,   209,   520,   210,   563
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,   176,    46,   756,   758,   757,    37,   747,   309,   179,
     759,   844,   565,   838,   612,   765,   737,   681,   296,   556,
     181,   176,   566,  1064,   969,   296,   737,   177,   176,   179,
      55,    56,   845,   182,   555,  1105,   179,  1066,   225,  1067,
     181,   689,   255,  1068,   739,   183,   301,   181,  1095,   305,
     971,   973,   957,   182,   739,   310,   975,   900,  1104,  1149,
     182,  1156,   211,   184,   336,   183,   336,   336,   672,  1274,
     336,   336,   183,  1078,   336,  1072,  1074,   336,   336,   336,
     316,   317,   318,   184,   336,   336,  1084,   864,  1228,  1088,
     184,    47,   336,   327,   328,   329,  1176,     3,   865,   974,
       4,  1084,     5,    52,   810,   953,   342,   343,   781,   346,
     347,   348,  1013,   866,   116,     3,   697,   697,     4,   528,
       5,  1134,     6,     7,   477,    49,   707,  1275,   369,   370,
     851,   679,   373,   698,  1079,    48,   707,  1188,  1189,     3,
       6,     7,     4,   176,     5,  1135,  1136,   176,   699,   699,
    1089,   179,   829,   489,    58,   179,   222,   223,   852,   226,
     878,   227,   181,   323,     6,     7,   181,   478,   479,  1064,
     451,   306,   853,   185,    70,   182,   988,  1206,   216,   182,
     452,   453,  1209,   997,   121,   122,   123,   183,   320,   321,
     322,   183,   879,   300,   121,   122,   123,   782,   783,  1224,
     300,   332,   333,   334,   254,   184,  1214,   170,   854,   184,
    1058,  1050,   528,  1084,  1051,   219,  1137,   867,   352,  1229,
    1230,  1086,   359,   360,   228,   361,  1104,  1251,   366,  1059,
     296,   493,   494,   176,  1138,     3,   378,   954,     4,   481,
       5,   179,   991,  1117,  1118,   552,   610,   502,   673,   674,
     675,  -123,   181,   855,     3,   553,  1210,     4,   910,     5,
       6,     7,   482,   483,   503,   182,   512,  1027,   725,  1060,
     309,   911,  1028,   912,  1029,  1017,  1018,   183,   725,     6,
       7,   309,   892,   513,   212,   213,   296,  1202,   564,   176,
     600,   484,   730,   583,   584,   184,   296,   179,   846,   176,
     448,  1106,   730,  1177,  1245,   601,   901,   179,   181,  1246,
     754,   673,   674,   675,   449,   185,  1181,   310,   181,   185,
     764,   182,   580,  1232,  1186,  1233,   577,   336,   310,  1234,
     455,   182,   302,   183,   456,  1064,   617,   602,   576,   978,
    -136,   575,   979,   183,  1159,     3,   330,     4,     4,     5,
       5,   184,   592,   593,   583,   584,   594,   457,   458,   739,
     350,   184,  1208,   948,   768,  1030,  1073,   928,   224,  1256,
       6,     7,     4,   929,     5,   254,  1094,  1027,   170,   844,
    1199,   838,  1028,  1194,  1029,   816,   515,  1252,   170,   319,
     777,   108,   330,   109,   800,   801,   212,   213,   110,   516,
     111,   881,   847,   112,   903,   300,   517,   802,   589,   590,
     857,  1061,   372,    51,   861,   803,   518,   844,   876,   838,
     877,  1231,   519,   804,    43,   618,   619,   620,   621,   622,
    1031,    50,    43,    43,    53,    53,    53,   113,   114,    43,
     103,   760,   692,   693,  1032,   104,   105,   915,   613,   614,
    1160,   739,     4,   766,     5,  1196,   460,   837,   825,  1033,
     106,   300,   312,   580,  1034,   315,  1134,   387,   388,   389,
     498,   300,   555,   771,   500,  1030,   557,   325,   312,   461,
     462,    43,   463,   314,    43,    53,    53,    53,   577,   338,
    1135,  1136,   778,    43,   739,   324,    43,    43,    53,    53,
      53,   588,   805,   806,   807,   536,   335,  1035,    43,   819,
     820,    53,    53,   368,   380,   381,    53,   546,   547,   548,
     374,   911,     3,   912,   604,     4,  1161,     5,   871,   872,
     505,   367,    43,    53,    53,   905,   906,    53,   899,    43,
    1031,   599,    72,   605,    73,   506,    74,     6,     7,    75,
      76,    77,     3,   606,  1032,     4,   487,     5,   507,   943,
     944,  1137,   606,   972,   508,   683,   684,   176,   610,  1033,
     489,   689,   490,   625,  1034,   179,   694,     6,     7,  1138,
       4,   176,     5,   725,  1194,   844,   181,   838,   695,   179,
     696,  1047,  1048,  1049,  1050,  1221,   748,  1051,   743,   182,
     181,   382,   383,  1120,  1121,   384,   744,   839,   509,   510,
    1222,   183,  1052,   182,    60,  1223,    61,  1152,   749,  1026,
     750,    62,    63,    64,   739,   183,  1130,  1131,  1016,   184,
    1009,   682,   683,   684,  1022,   558,  1024,  1025,  1127,  1128,
     559,   560,  1159,   184,   561,   562,  1004,  1005,   493,   494,
      48,   751,  1053,   375,   376,   377,   739,   739,   739,   739,
     739,   739,   739,   752,   739,   739,   739,   770,   176,   176,
     176,   176,   176,   176,   779,   725,   179,   179,   179,   179,
     179,   179,   396,   397,   398,   399,   400,   181,   181,   181,
     181,   181,   181,   961,   894,   895,  1093,   799,   780,   730,
     182,   182,   182,   182,   182,   182,   391,    78,   392,   393,
     394,   813,   183,   183,   183,   183,   183,   183,   725,  1085,
     811,    79,   812,   659,   739,   818,   814,   739,   822,   827,
     184,   184,   184,   184,   184,   184,    80,   826,   828,   185,
     830,    81,   730,   835,   918,   724,   848,   873,  1160,  1101,
     849,  1102,   858,   185,   859,   724,   860,     3,   874,   961,
       4,   740,     5,   767,   875,   739,   880,  -650,  1103,    53,
    -651,   740,   882,   883,   933,   884,   772,   908,   773,    65,
     774,   885,     6,     7,   890,   775,     3,   776,   904,     4,
     909,     5,   907,    66,  1054,    53,   913,  1183,   923,   924,
    1184,   925,   176,   926,  1185,   934,   927,   891,    67,   931,
     179,     6,     7,    68,   942,   946,  1193,   947,    14,    15,
     948,   181,   950,   951,  1201,   378,     3,   952,   697,     4,
     966,     5,   968,   970,   182,  1198,   121,   122,   123,   977,
     185,   185,   185,   185,   185,   185,   183,  1159,   725,   442,
     984,     6,     7,   935,   936,   937,   938,   939,   940,   443,
      28,   673,   674,   675,   184,  -302,   444,   982,   176,    29,
     983,   985,   445,   446,   987,    30,   179,   995,  1023,  1000,
     725,   725,   725,   725,   725,   725,   725,   181,   725,   725,
     725,    31,  1069,   296,  1070,  1071,   176,  1058,  1050,  1075,
     182,  1051,  1077,  1096,   179,  1082,     3,  1097,  1080,     4,
    1098,     5,   183,  1099,   730,   181,  1059,  1107,  1036,  1113,
    1055,  1062,  1123,  1114,  1037,  1129,  1056,  1063,   182,  1133,
     184,     6,     7,   739,  1157,   296,  1148,  1158,   176,  1171,
     183,  1173,  1174,   415,  1179,   416,   179,  1180,   725,  1190,
     567,   725,   568,  1160,   569,   570,  1060,   181,   184,  1203,
    1207,   571,   572,   417,  1211,   418,   419,   420,   421,  1212,
     182,  1142,  1143,  1144,   185,   839,  1213,  1058,  1050,  1215,
    1216,  1051,   183,  1217,   296,  1218,  1226,   176,  1235,   725,
     573,  1239,  1265,  1264,  1278,   179,  1059,   339,   341,    57,
     184,   344,   345,  1150,  1065,   349,   181,   755,   354,   356,
     358,  1220,  1219,   583,   584,   363,   365,  1112,  1012,   182,
     326,   486,  1182,   371,  1165,  1166,  1167,  1168,  1169,  1270,
     850,   183,   487,   863,   488,  1178,  1060,  1119,   611,   296,
     185,  1090,   176,  1124,  1125,  1126,   489,   833,   490,   184,
     179,   491,   659,   659,   603,   659,  1147,   659,  1260,  1175,
     724,   181,   992,  1151,  1036,   993,  1055,  1062,   300,   994,
    1037,   889,  1056,  1063,   182,  1162,   740,   996,  1007,   893,
     659,  1163,   309,   659,   896,   340,   183,  1010,   932,   423,
     424,   231,   232,   233,   234,   235,   236,   492,  1155,    14,
      15,   309,   353,   425,   184,   426,   427,   428,   897,   976,
     300,  1011,   898,  1255,   761,   763,    14,    15,  1263,   355,
     429,   430,   431,   357,   493,   494,  1191,  1192,   351,   310,
    1259,  1019,   659,    14,    15,   659,   762,    14,    15,  1195,
    1204,    28,   746,  1020,  1197,  1108,  1110,  1110,   310,  1200,
      29,  1021,   724,   798,   596,  1162,    30,   725,    28,   300,
    1205,  1163,   597,   598,     0,     0,     0,    29,   740,     0,
       0,     0,    31,    30,     0,    28,     0,     0,  1250,    28,
       0,     0,     0,     0,    29,     0,     0,     0,    29,    31,
      30,     0,     0,   930,    30,   724,   659,   659,     0,     0,
    1225,     0,     0,  1227,     0,   296,    31,     0,   176,     0,
      31,   740,     0,     0,   300,     0,   179,     0,     0,     0,
    1241,  1242,  1243,  1244,     0,     0,     0,   181,     0,     0,
     362,     0,  1055,  1062,     0,  1253,  1257,  1261,  1056,  1063,
     182,  1254,  1258,  1262,    14,    15,  1266,  1267,  1268,  1269,
    1162,  1271,   183,     0,     0,  1272,  1163,     0,   769,  1273,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1277,
     184,     0,     0,     0,     0,     0,   956,     0,     0,     0,
     659,   659,     0,   659,     0,     0,    28,     0,   831,   832,
       0,   834,     0,   836,     0,    29,     0,     0,     0,     0,
       0,    30,    83,    84,    85,    86,     0,     0,    87,    88,
       0,    89,    90,     0,    91,     0,   868,    31,     0,   870,
       0,     0,   659,     0,   989,   724,   989,   989,   989,     0,
     989,   989,   999,   659,     0,  1002,  1002,   659,     0,   659,
     990,   740,   990,   990,   990,     0,   990,   990,    92,    93,
      94,  1003,  1003,     0,     0,     0,     0,   724,   724,   724,
     724,   724,   724,   724,     0,   724,   724,   724,   887,     0,
       0,   888,     0,   740,   740,   740,   740,   740,   740,   740,
     300,   740,   740,   740,     3,     0,     0,     4,     0,     5,
       0,     0,     0,   364,     0,     0,     0,     0,     0,     0,
       0,     3,     0,     0,     4,     0,     5,    14,    15,     6,
       7,     0,     0,     0,   433,     0,   434,     0,     0,   659,
       0,     0,     0,   659,     0,   724,     6,     7,   724,     0,
       0,     0,   916,   917,   435,     0,   436,   437,     0,   438,
     659,   740,     0,     0,   740,     0,     0,   439,   440,    28,
       0,     0,     0,  1047,  1048,  1049,  1050,     0,    29,  1051,
       0,     0,     0,     0,    30,     0,   724,    95,     0,     0,
    1047,  1048,  1049,  1050,  1052,     0,  1051,     0,     0,     0,
      31,    96,   740,     0,     0,     0,    97,    98,    99,     0,
       0,  1052,     0,     0,     0,     0,   100,     0,     0,     0,
       0,   101,     0,     0,     0,     0,   402,   403,     0,     0,
     404,     0,     0,     0,  1053,     0,   964,   965,     0,   967,
     405,   406,   407,   408,   409,   410,   411,   412,   413,     3,
       0,  1053,     4,   785,     5,     0,   786,   787,   788,   789,
     790,   791,   792,   793,   794,   795,   796,     0,     0,     0,
       0,   118,     0,     0,     6,     7,   119,     0,   986,     0,
       0,     0,     0,     0,     0,     0,   230,     0,     0,  1001,
       0,     0,     0,  1006,     0,  1008,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   231,
     232,   233,   234,   235,   236,     0,     0,     0,     0,     0,
       0,  1039,     0,     0,     0,   237,   238,     0,   120,   121,
     122,   123,     0,     0,     0,     0,   124,     0,     0,  1040,
     125,     0,     0,     0,   126,     0,     0,     0,     0,     0,
     127,     0,     0,     0,   724,     0,     0,     0,     0,     0,
     128,     0,     0,     0,     0,     0,   129,     0,     0,     0,
     740,   130,     0,     0,   131,  1087,  1154,   132,   133,  1091,
       0,   134,     0,     0,   135,     0,   136,     0,     0,     0,
       0,     0,     0,  1249,     0,     0,  1100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
     138,     0,   139,   140,   141,     0,     0,   142,   143,     0,
       0,   144,   145,   239,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,     0,     0,   240,     0,     0,     0,     0,     0,
       0,     0,   465,     0,     0,   466,     0,     0,   241,     0,
       0,     0,     0,     0,     0,     0,     0,   242,   467,     0,
       0,     0,   468,   243,     3,   469,   470,     4,   244,     5,
     471,   472,   473,   474,   475,     0,     0,     0,   245,     0,
       0,   246,   247,   248,   249,     0,   118,     0,   250,     6,
       7,   119,   251,   252,   166,     0,     0,     0,   167,   168,
       0,   230,     0,     0,     0,   253,     0,     0,   169,   521,
     254,  1041,     0,   170,   171,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   231,   232,   233,   234,   235,   236,
       0,     0,     0,     0,     0,   522,  1039,     0,   523,     0,
     237,   238,     0,   120,   121,   122,   123,   524,     0,     0,
       0,   124,     0,     0,  1040,   125,     0,     0,     0,   126,
       0,     0,     0,     0,     0,   127,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,     0,     0,     0,     0,
       0,   129,     0,     0,     0,     0,   130,     0,     0,   131,
       0,     0,   132,   133,     0,     0,   134,     0,     0,   135,
       0,   136,     0,     0,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,     0,     0,   137,   138,     0,   139,   140,   141,
       0,     0,   142,   143,     0,     0,   144,   145,   239,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,     0,     0,   240,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   241,     0,   525,     0,     0,     0,     0,
       0,     0,   242,     0,     0,     0,     0,     0,   243,     3,
       0,     0,     4,   244,     5,     0,     0,     0,     0,     0,
       0,     0,     0,   245,     0,     0,   246,   247,   248,   249,
       0,   118,     0,   250,     6,     7,   119,   251,   252,   166,
       0,     0,     0,   167,   168,     0,   230,     0,     0,     0,
     253,     0,     0,   169,   595,   254,  1153,     0,   170,   171,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   231,
     232,   233,   234,   235,   236,     0,     0,     0,     0,     0,
     522,  1039,     0,   523,     0,   237,   238,     0,   120,   121,
     122,   123,   524,     0,     0,     0,   124,     0,     0,  1040,
     125,     0,     0,     0,   126,     0,     0,     0,     0,     0,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     128,     0,     0,     0,     0,     0,   129,     0,     0,     0,
       0,   130,     0,     0,   131,     0,     0,   132,   133,     0,
       0,   134,     0,     0,   135,     0,   136,     0,     0,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,     0,     0,   137,
     138,     0,   139,   140,   141,     0,     0,   142,   143,     0,
       0,   144,   145,   239,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,     0,     0,   240,     0,     0,     0,     0,     0,
     627,     0,     0,     0,     0,     0,     0,     0,   241,     0,
     525,     0,     0,     0,     0,     0,   628,   242,   118,     0,
       0,     0,     0,   243,     0,     0,     0,     0,   244,     0,
     529,   530,     0,     0,     0,     0,     0,     0,   245,     0,
       0,   246,   247,   248,   249,     0,     0,     0,   250,   629,
       0,   531,   251,   252,   166,     0,     0,     0,   167,   168,
       0,     0,   630,     0,     0,   253,     0,     0,   169,     0,
     254,  1248,     0,   170,   171,   120,   121,   122,   123,     0,
       0,     0,     0,   631,     0,     0,     0,   632,     0,     0,
       0,   633,     0,     0,     0,     0,     0,   634,     0,     0,
       0,   635,     0,     0,     0,     0,     0,   128,     0,     0,
       0,     0,     0,   636,     0,     0,     0,   532,   130,   869,
       0,   131,     0,     0,   132,   133,     0,     0,   134,     0,
       0,   135,     0,   136,     0,   628,     0,   118,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,     0,     0,   546,   547,   548,   137,   138,     0,   637,
       0,     0,     0,     0,     0,     0,     0,     0,   629,     0,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,     0,
       0,   165,     0,     0,   120,   121,   122,   123,     0,     0,
     638,     0,   631,   639,   640,     0,   632,     0,     0,     0,
     633,     0,     0,     0,     0,     0,   634,     0,     0,     0,
     635,     0,     0,     0,     0,     0,   128,     0,     0,     0,
       0,     0,   636,     0,     0,     0,     0,   130,   641,   642,
     131,     0,     0,   132,   133,     0,     0,   134,     0,     0,
     135,   166,   136,     0,     0,   167,   168,     0,     0,     0,
       0,     0,     0,   643,   644,     8,     0,     9,     0,    10,
     170,     0,    11,    12,    13,   137,   138,     0,   637,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,     0,     0,
     165,     0,     0,     0,     0,   886,     0,     0,     0,   638,
       0,    28,   639,   640,     0,     0,     0,     0,     0,     0,
      29,   628,     0,   118,     0,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,   641,   642,     0,
       0,     0,     0,     0,   629,     0,     0,     0,     0,     0,
     166,     0,     0,     0,   167,   168,     0,     0,     0,     0,
       0,     0,   643,   644,     0,     0,     0,     0,     0,   170,
     120,   121,   122,   123,     0,     0,     0,     0,   631,     0,
       0,     0,   632,     0,     0,     0,   633,     0,     0,     0,
       0,     0,   634,     0,     0,     0,   635,     0,     0,     0,
       0,     0,   128,     0,     0,     0,     0,     0,   636,     0,
      32,     0,     0,   130,     0,     0,   131,     0,     0,   132,
     133,     0,     0,   134,    33,     0,   135,     0,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
       0,     0,     0,     0,    35,     0,     0,     0,     0,     0,
       0,   137,   138,     0,   637,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,     0,     0,   165,     0,     0,     0,
       0,     0,     0,     0,     0,   638,     0,     0,   639,   640,
     700,   701,   702,   703,   704,   705,     0,     0,     0,     0,
       0,     0,   706,     0,   707,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   641,   642,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   629,   166,     0,     0,     0,
     167,   168,     0,     0,     0,     0,     0,     0,   643,   644,
       0,     0,     0,     0,     0,   170,     0,     0,     0,     0,
       0,   120,   121,   122,   123,     0,     0,     0,     0,   708,
     706,     0,   707,   709,     0,     0,     0,   710,     0,     0,
       0,     0,     0,   711,     0,     0,     0,   635,     0,     0,
       0,     0,     0,   712,     0,     0,     0,     0,     0,   713,
       0,     0,     0,   629,   714,     0,     0,   715,     0,     0,
     716,   717,     0,     0,   718,     0,     0,   719,     0,   720,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   120,
     121,   122,   123,     0,     0,     0,     0,   708,     0,     0,
       0,   709,   721,   722,     0,   710,     0,     0,     0,     0,
       0,   711,     0,     0,     0,   635,     0,     0,     0,     0,
       0,   712,     0,     0,     0,     0,     0,   713,     0,     0,
       0,     0,   714,     0,     0,   715,     0,     0,   716,   717,
       0,     0,   718,     0,     0,   719,   638,   720,     0,   639,
     640,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     721,   722,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   641,   642,     0,   723,     0,   628,
       0,   118,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   643,
     644,     0,     0,   254,   638,     0,   170,   639,   640,     0,
       0,     0,   629,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   120,   121,
     122,   123,   641,   642,     0,   723,   631,     0,     0,     0,
     632,     0,     0,     0,   633,     0,     0,     0,     0,     0,
     634,     0,     0,     0,   635,     0,     0,   643,   644,     0,
     128,   254,     0,     0,   170,   914,   636,     0,     0,     0,
       0,   130,     0,     0,   131,     0,     0,   132,   133,     0,
       0,   134,     0,     0,   135,     0,   136,     0,   706,     0,
     707,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
     138,     0,   637,     0,     0,     0,     0,     0,     0,     0,
       0,   629,     0,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,     0,     0,   165,     0,     0,   120,   121,   122,
     123,     0,     0,   638,     0,   708,   639,   640,     0,   709,
       0,     0,     0,   710,     0,   706,     0,   707,     0,   711,
       0,     0,     0,   635,     0,     0,     0,     0,     0,   712,
       0,     0,     0,     0,     0,   713,     0,     0,     0,     0,
     714,   641,   642,   715,     0,     0,   716,   717,   629,     0,
     718,     0,     0,   719,   166,   720,     0,     0,   167,   168,
       0,     0,     0,     0,     0,     0,   643,   644,     0,     0,
       0,     0,     0,   170,   120,   121,   122,   123,   721,   722,
       0,     0,   708,     0,     0,     0,   709,     0,     0,     0,
     710,     0,     0,     0,     0,     0,   711,     0,     0,     0,
     635,     0,     0,     0,     0,     0,   712,     0,     0,     0,
       0,     0,   713,     0,     0,     0,     0,   714,     0,     0,
     715,     0,   638,   716,   717,   639,   640,   718,     0,     0,
     719,     0,   720,     0,     0,     0,   118,     0,     0,     0,
       0,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   230,     0,     0,     0,   721,   722,     0,     0,     0,
     641,   642,     0,   723,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   231,   232,   233,   234,   235,   236,
       0,     0,     0,     0,     0,   643,   644,     0,     0,   254,
     237,   238,   170,   120,   121,   122,   123,     0,     0,   638,
       0,   124,   639,   640,     0,   125,     0,     0,     0,   126,
       0,     0,     0,     0,     0,   127,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,     0,     0,     0,     0,
       0,   129,     0,     0,     0,     0,   130,   641,   642,   131,
     723,     0,   132,   133,     0,     0,   134,     0,     0,   135,
       0,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   643,   644,     0,     0,     0,     0,     0,   170,
       0,     0,     0,     0,   137,   138,     0,   139,   140,   141,
       0,     0,   142,   143,     0,     0,   144,   145,   239,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,     0,     0,   240,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   241,     0,     0,     0,     0,     0,     0,
       0,     0,   242,     0,   118,     0,     0,     0,   243,   119,
       0,     0,     0,   244,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   245,     0,     0,   246,   247,   248,   249,
       0,     0,     0,   250,     0,     0,     0,   251,   252,   166,
       0,     0,     0,   167,   168,     0,     0,     0,     0,     0,
     253,     0,     0,   169,     0,   254,     0,     0,   170,   171,
       0,   120,   121,   122,   123,     0,     0,     0,     0,   124,
       0,     0,     0,   125,     0,     0,     0,   126,     0,     0,
       0,     0,     0,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   128,     0,     0,     0,     0,     0,   129,
       0,     0,     0,     0,   130,     0,     0,   131,     0,     0,
     132,   133,     0,     0,   134,     0,     0,   135,     0,   136,
       0,   118,     0,     0,     0,     0,   119,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   137,   138,     0,   139,   140,   141,     0,     0,
     142,   143,     0,     0,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,     0,     0,   165,   120,   121,
     122,   123,     0,     0,     0,     0,   124,     0,     0,     0,
     125,     0,     0,     0,   126,     0,     0,     0,     0,     0,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     128,     0,     0,     0,     0,     0,   129,     0,     0,     0,
       0,   130,     0,     0,   131,     0,     0,   132,   133,     0,
       0,   134,     0,     0,   135,     0,   136,   166,   118,     0,
       0,   167,   168,     0,     0,     0,     0,     0,     0,     0,
       0,   169,     0,   254,     0,     0,   170,   171,     0,   137,
     138,     0,   139,   140,   141,     0,     0,   142,   143,   629,
       0,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,     0,     0,   165,   120,   121,   122,   123,     0,
       0,     0,     0,   631,     0,     0,     0,   632,     0,     0,
       0,   633,     0,     0,     0,     0,     0,   634,     0,     0,
       0,   635,     0,     0,     0,     0,     0,   128,     0,     0,
       0,     0,     0,   636,     0,     0,     0,     0,   130,     0,
       0,   131,     0,     0,   132,   133,     0,     0,   134,     0,
       0,   135,     0,   136,   166,     0,     0,     0,   167,   168,
       0,     0,     0,     0,     0,     0,     0,     0,   169,     0,
       0,     0,     0,   170,   171,     0,   137,   138,     0,   637,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   707,
       0,   165,     0,     0,     0,     0,     0,     0,     0,     0,
     638,     0,     0,   639,   640,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     629,     0,     0,     0,     0,     0,     0,   231,   232,   233,
     234,   235,   236,     0,     0,     0,     0,     0,   641,   642,
       0,     0,     0,     0,     0,     0,   120,   121,   122,   123,
       0,   166,     0,     0,   708,   167,   168,   707,   709,     0,
       0,     0,   710,   643,   644,     0,     0,     0,   711,     0,
     170,     0,   635,     0,     0,     0,     0,     0,   712,     0,
       0,     0,     0,     0,   713,     0,     0,     0,   629,   714,
       0,     0,   715,     0,     0,   716,   717,     0,     0,   718,
       0,     0,   719,     0,   720,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   120,   121,   122,   123,     0,   707,
       0,     0,   708,     0,     0,     0,   709,   721,   722,     0,
     710,     0,     0,     0,     0,     0,   711,     0,     0,     0,
     635,     0,     0,     0,     0,     0,   712,     0,     0,     0,
     629,     0,   713,     0,     0,     0,     0,   714,     0,     0,
     715,     0,     0,   716,   717,     0,     0,   718,     0,     0,
     719,   638,   720,     0,   639,   640,     0,   121,   122,   123,
       0,     0,     0,     0,   708,     0,     0,     0,   709,     0,
       0,     0,   710,     0,     0,   721,   722,     0,   711,     0,
       0,     0,   635,     0,     0,     0,     0,     0,     0,   641,
     642,     0,   723,     0,   713,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   643,   644,     0,     0,     0,   638,
       0,   170,   639,   640,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   641,   642,     0,
     723,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   638,   643,   644,   639,   640,     0,     0,     0,   170,
       2,     3,     0,     0,     4,     0,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     7,     0,   641,
     642,     8,     0,     9,     0,    10,     0,     0,    11,    12,
      13,     0,     0,     0,     0,    14,    15,    16,     0,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
       0,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -213,     0,     0,     0,     0,     0,    28,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,     0,     0,
       0,     0,    30,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,     0,     0,     0,
      35
};

static const yytype_int16 yycheck[] =
{
       1,    25,     3,   315,   317,   316,     1,   302,    55,    25,
     318,   607,   171,   607,   257,   328,   292,   274,    45,   167,
      25,    45,   211,   922,   835,    52,   302,    25,    52,    45,
      12,    13,     7,    25,   167,     7,    52,   925,    39,   926,
      45,    31,    45,   927,   292,    25,    47,    52,   972,    52,
     839,   840,    70,    45,   302,    55,   845,    23,  1013,  1059,
      52,  1069,    43,    25,    84,    45,    86,    87,    67,    22,
      90,    91,    52,    20,    94,   946,   947,    97,    98,    99,
      62,    63,    64,    45,   104,   105,   959,   112,    81,    20,
      52,    82,   112,    75,    76,    77,  1089,     1,   123,   841,
       4,   974,     6,    10,   549,    81,    88,    89,    91,    31,
      32,    93,   901,   138,    33,     1,     8,     8,     4,   146,
       6,    81,    26,    27,    91,     7,    23,    80,   110,   111,
      60,    67,   114,    24,    81,    81,    23,  1117,  1118,     1,
      26,    27,     4,   167,     6,   105,   106,   171,    40,    40,
      81,   167,   597,   116,    35,   171,    34,    35,    88,    41,
       8,    43,   167,    70,    26,    27,   171,   134,   135,  1068,
     121,    53,   102,    25,    35,   167,   871,  1170,    81,   171,
     131,   132,  1175,   878,    81,    82,    83,   167,    66,    67,
      68,   171,    40,    45,    81,    82,    83,   180,   181,  1199,
      52,    79,    80,    81,   272,   167,  1186,   275,   138,   171,
      72,    73,   239,  1086,    76,   204,   176,   242,    96,   212,
     213,   963,   100,   101,   263,   103,  1181,  1235,   106,    91,
     257,   194,   195,   257,   194,     1,   118,   213,     4,   111,
       6,   257,   872,  1033,  1034,   247,   264,   104,   247,   248,
     249,   272,   257,   183,     1,   257,  1180,     4,     7,     6,
      26,    27,   134,   135,   121,   257,   104,    33,   292,   131,
     317,    20,    38,    22,    40,   905,   906,   257,   302,    26,
      27,   328,   272,   121,   265,   266,   313,  1158,   170,   313,
     211,   163,   292,   228,   229,   257,   323,   313,   273,   323,
     114,   273,   302,  1092,   133,   226,   272,   323,   313,   138,
     313,   247,   248,   249,   128,   167,  1105,   317,   323,   171,
     323,   313,   226,  1211,  1114,  1212,   212,   347,   328,  1213,
     107,   323,   271,   313,   111,  1234,   131,   211,   220,   114,
     272,   219,   117,   323,    91,     1,   204,     4,     4,     6,
       6,   313,   234,   235,   228,   229,   238,   134,   135,   607,
     218,   323,  1173,   259,   346,   131,   262,   760,     0,   273,
      26,    27,     4,   766,     6,   272,   972,    33,   275,   975,
       5,   975,    38,     8,    40,   574,    91,   273,   275,   204,
     372,    31,   204,    33,    89,    90,   265,   266,    38,   104,
      40,   658,   610,    43,   699,   257,   111,   102,    47,    48,
     618,   273,    31,     9,   622,   110,   121,  1013,    20,  1013,
      22,  1210,   127,   118,     1,   220,   221,   222,   223,   224,
     196,     8,     9,    10,    11,    12,    13,    77,    78,    16,
     210,   319,    15,    16,   210,   215,   216,   742,   212,   213,
     197,   699,     4,   331,     6,     7,   111,   605,   591,   225,
     230,   313,    58,   226,   230,    61,    81,    89,    90,    91,
     168,   323,   605,   351,   168,   131,   258,    73,    74,   134,
     135,    58,   137,    60,    61,    62,    63,    64,   212,    85,
     105,   106,   374,    70,   742,    72,    73,    74,    75,    76,
      77,    80,   197,   198,   199,   200,    83,   273,    85,   228,
     229,    88,    89,   109,    89,    90,    93,   212,   213,   214,
     116,    20,     1,    22,    67,     4,   273,     6,    15,    16,
      93,   108,   109,   110,   111,    15,    16,   114,   697,   116,
     196,   211,    31,    67,    33,   108,    35,    26,    27,    38,
      39,    40,     1,     4,   210,     4,   102,     6,   121,    89,
      90,   176,     4,     5,   127,   252,   253,   591,   264,   225,
     116,    31,   118,   241,   230,   591,    17,    26,    27,   194,
       4,   605,     6,   607,     8,  1181,   591,  1181,    18,   605,
     274,    70,    71,    72,    73,   210,   272,    76,    38,   591,
     605,   176,   177,    61,    62,   180,    38,   607,   171,   172,
     225,   591,    91,   605,    31,   230,    33,   273,   272,   914,
     272,    38,    39,    40,   872,   605,    74,    75,   904,   591,
     887,   251,   252,   253,   910,   164,   912,   913,  1047,  1048,
     169,   170,    91,   605,   173,   174,   882,   883,   194,   195,
      81,   272,   131,    84,    85,    86,   904,   905,   906,   907,
     908,   909,   910,    42,   912,   913,   914,    31,   692,   693,
     694,   695,   696,   697,     7,   699,   692,   693,   694,   695,
     696,   697,    97,    98,    99,   100,   101,   692,   693,   694,
     695,   696,   697,   826,   692,   693,   972,   278,     8,   699,
     692,   693,   694,   695,   696,   697,    91,   196,    93,    94,
      95,    80,   692,   693,   694,   695,   696,   697,   742,   962,
     258,   210,   258,   270,   972,    80,   277,   975,    80,    38,
     692,   693,   694,   695,   696,   697,   225,   272,    38,   591,
      38,   230,   742,    80,   745,   292,    80,    17,   197,  1006,
      80,  1008,    80,   605,    80,   302,    80,     1,    18,   892,
       4,   292,     6,   340,   274,  1013,     5,     7,  1011,   346,
       7,   302,     7,     7,    76,     5,   353,    18,   355,   196,
     357,     7,    26,    27,     7,   362,     1,   364,     7,     4,
     274,     6,    17,   210,   273,   372,     8,  1109,    80,   272,
    1111,   272,   826,   272,  1112,   107,   272,   689,   225,    80,
     826,    26,    27,   230,    80,    80,  1129,    80,    45,    46,
     259,   826,   272,   213,   273,   707,     1,    80,     8,     4,
      38,     6,    80,    30,   826,  1148,    81,    82,    83,   117,
     692,   693,   694,   695,   696,   697,   826,    91,   872,   104,
      54,    26,    27,   155,   156,   157,   158,   159,   160,   114,
      87,   247,   248,   249,   826,    80,   121,    91,   892,    96,
      91,    91,   127,   128,     5,   102,   892,    80,    80,   879,
     904,   905,   906,   907,   908,   909,   910,   892,   912,   913,
     914,   118,   272,   920,     7,   279,   920,    72,    73,    80,
     892,    76,    80,     7,   920,    81,     1,    81,   231,     4,
      81,     6,   892,    81,   914,   920,    91,   277,   919,    81,
     921,   922,    81,   204,   919,   271,   921,   922,   920,    80,
     892,    26,    27,  1181,    80,   962,   271,    80,   962,   227,
     920,    80,   273,    91,   273,    93,   962,     5,   972,    29,
      32,   975,    34,   197,    36,    37,   131,   962,   920,    82,
      80,    43,    44,   111,   272,   113,   114,   115,   116,   272,
     962,    68,    69,    70,   826,   975,   272,    72,    73,   272,
     272,    76,   962,   272,  1011,    81,   110,  1011,   272,  1013,
      72,    30,   119,    81,    80,  1011,    91,    86,    87,    16,
     962,    90,    91,  1060,   924,    94,  1011,   314,    97,    98,
      99,  1196,  1194,   228,   229,   104,   105,  1029,   900,  1011,
      74,    91,  1105,   112,   235,   236,   237,   238,   239,   273,
     615,  1011,   102,   623,   104,  1096,   131,  1038,   256,  1066,
     892,   969,  1066,  1044,  1045,  1046,   116,   601,   118,  1011,
    1066,   121,   599,   600,   244,   602,  1057,   604,   273,  1088,
     607,  1066,   873,  1064,  1065,   874,  1067,  1068,   920,   875,
    1065,   685,  1067,  1068,  1066,  1076,   607,   877,   885,   690,
     627,  1076,  1129,   630,   694,    31,  1066,   890,   780,    89,
      90,    61,    62,    63,    64,    65,    66,   167,   273,    45,
      46,  1148,    31,   103,  1066,   105,   106,   107,   695,   845,
     962,   892,   696,  1236,   320,   322,    45,    46,  1238,    31,
     120,   121,   122,    31,   194,   195,  1127,  1128,    95,  1129,
    1237,   907,   679,    45,    46,   682,   321,    45,    46,  1140,
    1160,    87,   302,   908,  1145,  1027,  1028,  1029,  1148,  1150,
      96,   909,   699,   495,   239,  1156,   102,  1181,    87,  1011,
    1161,  1156,   240,   240,    -1,    -1,    -1,    96,   699,    -1,
      -1,    -1,   118,   102,    -1,    87,    -1,    -1,   273,    87,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    96,   118,
     102,    -1,    -1,   770,   102,   742,   743,   744,    -1,    -1,
    1201,    -1,    -1,  1204,    -1,  1232,   118,    -1,  1232,    -1,
     118,   742,    -1,    -1,  1066,    -1,  1232,    -1,    -1,    -1,
    1221,  1222,  1223,  1224,    -1,    -1,    -1,  1232,    -1,    -1,
      31,    -1,  1233,  1234,    -1,  1236,  1237,  1238,  1233,  1234,
    1232,  1236,  1237,  1238,    45,    46,  1247,  1248,  1249,  1250,
    1251,  1252,  1232,    -1,    -1,  1256,  1251,    -1,   347,  1260,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1270,
    1232,    -1,    -1,    -1,    -1,    -1,   823,    -1,    -1,    -1,
     827,   828,    -1,   830,    -1,    -1,    87,    -1,   599,   600,
      -1,   602,    -1,   604,    -1,    96,    -1,    -1,    -1,    -1,
      -1,   102,    31,    32,    33,    34,    -1,    -1,    37,    38,
      -1,    40,    41,    -1,    43,    -1,   627,   118,    -1,   630,
      -1,    -1,   869,    -1,   871,   872,   873,   874,   875,    -1,
     877,   878,   879,   880,    -1,   882,   883,   884,    -1,   886,
     871,   872,   873,   874,   875,    -1,   877,   878,    77,    78,
      79,   882,   883,    -1,    -1,    -1,    -1,   904,   905,   906,
     907,   908,   909,   910,    -1,   912,   913,   914,   679,    -1,
      -1,   682,    -1,   904,   905,   906,   907,   908,   909,   910,
    1232,   912,   913,   914,     1,    -1,    -1,     4,    -1,     6,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,     4,    -1,     6,    45,    46,    26,
      27,    -1,    -1,    -1,    91,    -1,    93,    -1,    -1,   966,
      -1,    -1,    -1,   970,    -1,   972,    26,    27,   975,    -1,
      -1,    -1,   743,   744,   111,    -1,   113,   114,    -1,   116,
     987,   972,    -1,    -1,   975,    -1,    -1,   124,   125,    87,
      -1,    -1,    -1,    70,    71,    72,    73,    -1,    96,    76,
      -1,    -1,    -1,    -1,   102,    -1,  1013,   196,    -1,    -1,
      70,    71,    72,    73,    91,    -1,    76,    -1,    -1,    -1,
     118,   210,  1013,    -1,    -1,    -1,   215,   216,   217,    -1,
      -1,    91,    -1,    -1,    -1,    -1,   225,    -1,    -1,    -1,
      -1,   230,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,
      93,    -1,    -1,    -1,   131,    -1,   827,   828,    -1,   830,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     1,
      -1,   131,     4,   141,     6,    -1,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    26,    27,    28,    -1,   869,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,   880,
      -1,    -1,    -1,   884,    -1,   886,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    -1,    -1,    -1,    77,    78,    -1,    80,    81,
      82,    83,    -1,    -1,    -1,    -1,    88,    -1,    -1,    91,
      92,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    -1,    -1,  1181,    -1,    -1,    -1,    -1,    -1,
     112,    -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,
    1181,   123,    -1,    -1,   126,   966,   273,   129,   130,   970,
      -1,   133,    -1,    -1,   136,    -1,   138,    -1,    -1,    -1,
      -1,    -1,    -1,   273,    -1,    -1,   987,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   161,
     162,    -1,   164,   165,   166,    -1,    -1,   169,   170,    -1,
      -1,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,    -1,    -1,   196,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   111,    -1,    -1,   114,    -1,    -1,   210,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   219,   127,    -1,
      -1,    -1,   131,   225,     1,   134,   135,     4,   230,     6,
     139,   140,   141,   142,   143,    -1,    -1,    -1,   240,    -1,
      -1,   243,   244,   245,   246,    -1,    23,    -1,   250,    26,
      27,    28,   254,   255,   256,    -1,    -1,    -1,   260,   261,
      -1,    38,    -1,    -1,    -1,   267,    -1,    -1,   270,    81,
     272,   273,    -1,   275,   276,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,   107,    73,    -1,   110,    -1,
      77,    78,    -1,    80,    81,    82,    83,   119,    -1,    -1,
      -1,    88,    -1,    -1,    91,    92,    -1,    -1,    -1,    96,
      -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,
      -1,   118,    -1,    -1,    -1,    -1,   123,    -1,    -1,   126,
      -1,    -1,   129,   130,    -1,    -1,   133,    -1,    -1,   136,
      -1,   138,    -1,    -1,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,    -1,    -1,   161,   162,    -1,   164,   165,   166,
      -1,    -1,   169,   170,    -1,    -1,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,    -1,    -1,   196,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   210,    -1,   247,    -1,    -1,    -1,    -1,
      -1,    -1,   219,    -1,    -1,    -1,    -1,    -1,   225,     1,
      -1,    -1,     4,   230,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   240,    -1,    -1,   243,   244,   245,   246,
      -1,    23,    -1,   250,    26,    27,    28,   254,   255,   256,
      -1,    -1,    -1,   260,   261,    -1,    38,    -1,    -1,    -1,
     267,    -1,    -1,   270,    81,   272,   273,    -1,   275,   276,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
     107,    73,    -1,   110,    -1,    77,    78,    -1,    80,    81,
      82,    83,   119,    -1,    -1,    -1,    88,    -1,    -1,    91,
      92,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,
      -1,   123,    -1,    -1,   126,    -1,    -1,   129,   130,    -1,
      -1,   133,    -1,    -1,   136,    -1,   138,    -1,    -1,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,    -1,    -1,   161,
     162,    -1,   164,   165,   166,    -1,    -1,   169,   170,    -1,
      -1,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,    -1,    -1,   196,    -1,    -1,    -1,    -1,    -1,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   210,    -1,
     247,    -1,    -1,    -1,    -1,    -1,    21,   219,    23,    -1,
      -1,    -1,    -1,   225,    -1,    -1,    -1,    -1,   230,    -1,
      89,    90,    -1,    -1,    -1,    -1,    -1,    -1,   240,    -1,
      -1,   243,   244,   245,   246,    -1,    -1,    -1,   250,    54,
      -1,   110,   254,   255,   256,    -1,    -1,    -1,   260,   261,
      -1,    -1,    67,    -1,    -1,   267,    -1,    -1,   270,    -1,
     272,   273,    -1,   275,   276,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,
      -1,   106,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,
      -1,    -1,    -1,   118,    -1,    -1,    -1,   176,   123,     5,
      -1,   126,    -1,    -1,   129,   130,    -1,    -1,   133,    -1,
      -1,   136,    -1,   138,    -1,    21,    -1,    23,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,    -1,    -1,   212,   213,   214,   161,   162,    -1,   164,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,    -1,
      -1,   196,    -1,    -1,    80,    81,    82,    83,    -1,    -1,
     205,    -1,    88,   208,   209,    -1,    92,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,
      -1,    -1,   118,    -1,    -1,    -1,    -1,   123,   243,   244,
     126,    -1,    -1,   129,   130,    -1,    -1,   133,    -1,    -1,
     136,   256,   138,    -1,    -1,   260,   261,    -1,    -1,    -1,
      -1,    -1,    -1,   268,   269,    31,    -1,    33,    -1,    35,
     275,    -1,    38,    39,    40,   161,   162,    -1,   164,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,    -1,    -1,
     196,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,   205,
      -1,    87,   208,   209,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    21,    -1,    23,    -1,    -1,   102,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118,    -1,    -1,    -1,    -1,   243,   244,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
     256,    -1,    -1,    -1,   260,   261,    -1,    -1,    -1,    -1,
      -1,    -1,   268,   269,    -1,    -1,    -1,    -1,    -1,   275,
      80,    81,    82,    83,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    92,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,    -1,   102,    -1,    -1,    -1,   106,    -1,    -1,    -1,
      -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,   118,    -1,
     196,    -1,    -1,   123,    -1,    -1,   126,    -1,    -1,   129,
     130,    -1,    -1,   133,   210,    -1,   136,    -1,   138,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,
      -1,    -1,    -1,    -1,   230,    -1,    -1,    -1,    -1,    -1,
      -1,   161,   162,    -1,   164,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,    -1,    -1,   196,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   205,    -1,    -1,   208,   209,
       9,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   243,   244,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,   256,    -1,    -1,    -1,
     260,   261,    -1,    -1,    -1,    -1,    -1,    -1,   268,   269,
      -1,    -1,    -1,    -1,    -1,   275,    -1,    -1,    -1,    -1,
      -1,    80,    81,    82,    83,    -1,    -1,    -1,    -1,    88,
      21,    -1,    23,    92,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,    -1,   102,    -1,    -1,    -1,   106,    -1,    -1,
      -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,   118,
      -1,    -1,    -1,    54,   123,    -1,    -1,   126,    -1,    -1,
     129,   130,    -1,    -1,   133,    -1,    -1,   136,    -1,   138,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      81,    82,    83,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    92,   161,   162,    -1,    96,    -1,    -1,    -1,    -1,
      -1,   102,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,
      -1,   112,    -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,
      -1,    -1,   123,    -1,    -1,   126,    -1,    -1,   129,   130,
      -1,    -1,   133,    -1,    -1,   136,   205,   138,    -1,   208,
     209,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     161,   162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   243,   244,    -1,   246,    -1,    21,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   268,
     269,    -1,    -1,   272,   205,    -1,   275,   208,   209,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,
      82,    83,   243,   244,    -1,   246,    88,    -1,    -1,    -1,
      92,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    -1,    -1,   106,    -1,    -1,   268,   269,    -1,
     112,   272,    -1,    -1,   275,   276,   118,    -1,    -1,    -1,
      -1,   123,    -1,    -1,   126,    -1,    -1,   129,   130,    -1,
      -1,   133,    -1,    -1,   136,    -1,   138,    -1,    21,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   161,
     162,    -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,    -1,    -1,   196,    -1,    -1,    80,    81,    82,
      83,    -1,    -1,   205,    -1,    88,   208,   209,    -1,    92,
      -1,    -1,    -1,    96,    -1,    21,    -1,    23,    -1,   102,
      -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,   112,
      -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,
     123,   243,   244,   126,    -1,    -1,   129,   130,    54,    -1,
     133,    -1,    -1,   136,   256,   138,    -1,    -1,   260,   261,
      -1,    -1,    -1,    -1,    -1,    -1,   268,   269,    -1,    -1,
      -1,    -1,    -1,   275,    80,    81,    82,    83,   161,   162,
      -1,    -1,    88,    -1,    -1,    -1,    92,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,
      -1,    -1,   118,    -1,    -1,    -1,    -1,   123,    -1,    -1,
     126,    -1,   205,   129,   130,   208,   209,   133,    -1,    -1,
     136,    -1,   138,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    -1,   161,   162,    -1,    -1,    -1,
     243,   244,    -1,   246,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,   268,   269,    -1,    -1,   272,
      77,    78,   275,    80,    81,    82,    83,    -1,    -1,   205,
      -1,    88,   208,   209,    -1,    92,    -1,    -1,    -1,    96,
      -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,
      -1,   118,    -1,    -1,    -1,    -1,   123,   243,   244,   126,
     246,    -1,   129,   130,    -1,    -1,   133,    -1,    -1,   136,
      -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   268,   269,    -1,    -1,    -1,    -1,    -1,   275,
      -1,    -1,    -1,    -1,   161,   162,    -1,   164,   165,   166,
      -1,    -1,   169,   170,    -1,    -1,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,    -1,    -1,   196,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   210,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   219,    -1,    23,    -1,    -1,    -1,   225,    28,
      -1,    -1,    -1,   230,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   240,    -1,    -1,   243,   244,   245,   246,
      -1,    -1,    -1,   250,    -1,    -1,    -1,   254,   255,   256,
      -1,    -1,    -1,   260,   261,    -1,    -1,    -1,    -1,    -1,
     267,    -1,    -1,   270,    -1,   272,    -1,    -1,   275,   276,
      -1,    80,    81,    82,    83,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    92,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,   118,
      -1,    -1,    -1,    -1,   123,    -1,    -1,   126,    -1,    -1,
     129,   130,    -1,    -1,   133,    -1,    -1,   136,    -1,   138,
      -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   161,   162,    -1,   164,   165,   166,    -1,    -1,
     169,   170,    -1,    -1,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,    -1,    -1,   196,    80,    81,
      82,    83,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      92,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,
      -1,   123,    -1,    -1,   126,    -1,    -1,   129,   130,    -1,
      -1,   133,    -1,    -1,   136,    -1,   138,   256,    23,    -1,
      -1,   260,   261,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   270,    -1,   272,    -1,    -1,   275,   276,    -1,   161,
     162,    -1,   164,   165,   166,    -1,    -1,   169,   170,    54,
      -1,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,    -1,    -1,   196,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,
      -1,   106,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,
      -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,   123,    -1,
      -1,   126,    -1,    -1,   129,   130,    -1,    -1,   133,    -1,
      -1,   136,    -1,   138,   256,    -1,    -1,    -1,   260,   261,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   270,    -1,
      -1,    -1,    -1,   275,   276,    -1,   161,   162,    -1,   164,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,    23,
      -1,   196,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     205,    -1,    -1,   208,   209,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,   243,   244,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    82,    83,
      -1,   256,    -1,    -1,    88,   260,   261,    23,    92,    -1,
      -1,    -1,    96,   268,   269,    -1,    -1,    -1,   102,    -1,
     275,    -1,   106,    -1,    -1,    -1,    -1,    -1,   112,    -1,
      -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,    54,   123,
      -1,    -1,   126,    -1,    -1,   129,   130,    -1,    -1,   133,
      -1,    -1,   136,    -1,   138,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    81,    82,    83,    -1,    23,
      -1,    -1,    88,    -1,    -1,    -1,    92,   161,   162,    -1,
      96,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,
      54,    -1,   118,    -1,    -1,    -1,    -1,   123,    -1,    -1,
     126,    -1,    -1,   129,   130,    -1,    -1,   133,    -1,    -1,
     136,   205,   138,    -1,   208,   209,    -1,    81,    82,    83,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    96,    -1,    -1,   161,   162,    -1,   102,    -1,
      -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,   243,
     244,    -1,   246,    -1,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   268,   269,    -1,    -1,    -1,   205,
      -1,   275,   208,   209,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   243,   244,    -1,
     246,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   205,   268,   269,   208,   209,    -1,    -1,    -1,   275,
       0,     1,    -1,    -1,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    -1,   243,
     244,    31,    -1,    33,    -1,    35,    -1,    -1,    38,    39,
      40,    -1,    -1,    -1,    -1,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,   275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     210,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,    -1,    -1,    -1,    -1,
     230
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   281,     0,     1,     4,     6,    26,    27,    31,    33,
      35,    38,    39,    40,    45,    46,    47,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    87,    96,
     102,   118,   196,   210,   225,   230,   282,   284,   285,   286,
     287,   333,   334,   335,   336,   344,   282,    82,    81,   330,
     335,   336,   344,   335,   338,   338,   338,   287,    35,   288,
      31,    33,    38,    39,    40,   196,   210,   225,   230,   289,
      35,   290,    31,    33,    35,    38,    39,    40,   196,   210,
     225,   230,   291,    31,    32,    33,    34,    37,    38,    40,
      41,    43,    77,    78,    79,   196,   210,   215,   216,   217,
     225,   230,   292,   210,   215,   216,   230,   293,    31,    33,
      38,    40,    43,    77,    78,   294,    33,   295,    23,    28,
      80,    81,    82,    83,    88,    92,    96,   102,   112,   118,
     123,   126,   129,   130,   133,   136,   138,   161,   162,   164,
     165,   166,   169,   170,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   196,   256,   260,   261,   270,
     275,   276,   302,   331,   423,   424,   425,   426,   427,   480,
     483,   487,   488,   490,   492,   503,   504,   506,   508,   510,
     512,   514,   516,   518,   520,   522,   524,   526,   528,   530,
     534,   536,   538,   539,   541,   543,   545,   547,   549,   551,
     553,    43,   265,   266,   296,   301,    81,   297,   298,   204,
     335,   340,   340,   340,     0,   282,   330,   330,   263,   343,
      38,    61,    62,    63,    64,    65,    66,    77,    78,   175,
     196,   210,   219,   225,   230,   240,   243,   244,   245,   246,
     250,   254,   255,   267,   272,   348,   349,   350,   351,   352,
     353,   357,   358,   361,   362,   369,   373,   377,   378,   380,
     381,   397,   398,   400,   401,   403,   404,   407,   408,   415,
     417,   418,   421,   422,   426,   431,   432,   433,   434,   435,
     436,   441,   442,   443,   465,   479,   483,   484,   501,   502,
     503,   282,   271,   303,   306,   348,   330,   308,   310,   423,
     443,   313,   336,   345,   335,   336,   338,   338,   338,   204,
     340,   340,   340,   344,   335,   336,   345,   338,   338,   338,
     204,   459,   340,   340,   340,   335,   334,   347,   336,   347,
      31,   347,   338,   338,   347,   347,    31,    32,   338,   347,
     218,   459,   340,    31,   347,    31,   347,    31,   347,   340,
     340,   340,    31,   347,    31,   347,   340,   335,   336,   338,
     338,   347,    31,   338,   336,    84,    85,    86,   330,   505,
      89,    90,   176,   177,   180,   429,   430,    89,    90,    91,
     507,    91,    93,    94,    95,   509,    97,    98,    99,   100,
     101,   511,    89,    90,    93,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   513,    91,    93,   111,   113,   114,
     115,   116,   515,    89,    90,   103,   105,   106,   107,   120,
     121,   122,   517,    91,    93,   111,   113,   114,   116,   124,
     125,   519,   104,   114,   121,   127,   128,   521,   114,   128,
     523,   121,   131,   132,   525,   107,   111,   134,   135,   527,
     111,   134,   135,   137,   529,   111,   114,   127,   131,   134,
     135,   139,   140,   141,   142,   143,   531,    91,   134,   135,
     535,   111,   134,   135,   163,   537,    91,   102,   104,   116,
     118,   121,   167,   194,   195,   489,   491,   542,   168,   544,
     168,   546,   104,   121,   540,    93,   108,   121,   127,   171,
     172,   548,   104,   121,   550,    91,   104,   111,   121,   127,
     552,    81,   107,   110,   119,   247,   481,   482,   483,    89,
      90,   110,   176,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   212,   213,   214,   493,
     494,   498,   247,   257,   486,   436,   442,   258,   164,   169,
     170,   173,   174,   554,   330,   435,   301,    32,    34,    36,
      37,    43,    44,    72,   299,   340,   330,   212,   455,   456,
     226,   463,   464,   228,   229,   370,   457,   458,    80,    47,
      48,   416,   330,   330,   330,    81,   481,   493,   494,   211,
     211,   226,   211,   370,    67,    67,     4,   283,   444,   445,
     264,   346,   351,   212,   213,   359,   360,   131,   220,   221,
     222,   223,   224,   363,   364,   241,   379,     5,    21,    54,
      67,    88,    92,    96,   102,   106,   118,   164,   205,   208,
     209,   243,   244,   268,   269,   382,   383,   384,   385,   386,
     387,   388,   390,   391,   392,   393,   394,   395,   396,   424,
     425,   474,   475,   476,   480,   487,   488,   490,   492,   499,
     500,   503,    67,   247,   248,   249,   399,   405,   406,    67,
     402,   405,   251,   252,   253,   409,   410,   411,   412,    31,
     419,   420,    15,    16,    17,    18,   274,     8,    24,    40,
       9,    10,    11,    12,    13,    14,    21,    23,    88,    92,
      96,   102,   112,   118,   123,   126,   129,   130,   133,   136,
     138,   161,   162,   246,   424,   425,   437,   438,   439,   440,
     443,   466,   467,   468,   469,   470,   471,   472,   473,   475,
     476,   477,   478,    38,    38,   454,   466,   467,   272,   272,
     272,   272,    42,   342,   348,   303,   306,   308,   310,   313,
     340,   456,   464,   458,   348,   310,   340,   335,   338,   347,
      31,   340,   335,   335,   335,   335,   335,   338,   330,     7,
       8,    91,   180,   181,   428,   141,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   532,   491,   278,
      89,    90,   102,   110,   118,   197,   198,   199,   495,   496,
     498,   258,   258,    80,   277,   300,   301,   462,    80,   228,
     229,   374,    80,   413,   414,   436,   272,    38,    38,   498,
      38,   395,   395,   374,   395,    80,   395,   442,   440,   443,
     448,   449,   452,   472,   473,     7,   273,   331,    80,    80,
     360,    60,    88,   102,   138,   183,   366,   331,    80,    80,
      80,   331,   365,   364,   112,   123,   138,   242,   395,     5,
     395,    15,    16,    17,    18,   274,    20,    22,     8,    40,
       5,   405,     7,     7,     5,     7,     5,   395,   395,   410,
       7,   330,   272,   420,   426,   426,   431,   432,   433,   435,
      23,   272,   354,   467,     7,    15,    16,    17,    18,   274,
       7,    20,    22,     8,   276,   467,   395,   395,   282,   305,
     307,   309,   314,    80,   272,   272,   272,   272,   462,   462,
     335,    80,   430,    76,   107,   155,   156,   157,   158,   159,
     160,   533,    80,    89,    90,   497,    80,    80,   259,   485,
     272,   213,    80,    81,   213,   371,   424,    70,   346,   450,
     451,   436,   446,   447,   395,   395,    38,   395,    80,   371,
      30,   283,     5,   283,   450,   283,   445,   117,   114,   117,
     367,   368,    91,    91,    54,    91,   395,     5,   382,   424,
     476,   477,   383,   384,   385,    80,   387,   382,   389,   424,
     443,   395,   424,   476,   499,   499,   395,   406,   395,   405,
     412,   446,   330,   283,   355,   356,   472,   477,   477,   468,
     469,   470,   472,    80,   472,   472,   467,    33,    38,    40,
     131,   196,   210,   225,   230,   273,   282,   284,   304,    73,
      91,   273,   282,   284,   325,   328,   348,    70,    71,    72,
      73,    76,    91,   131,   273,   282,   284,   315,    72,    91,
     131,   273,   282,   284,   315,   305,   307,   309,   314,   272,
       7,   279,   485,   262,   485,    80,   322,    80,    20,    81,
     231,   372,    81,   332,   451,   351,   450,   395,    20,    81,
     372,   395,   453,   472,   473,   479,     7,    81,    81,    81,
     395,   405,   405,   351,   448,     7,   273,   277,   330,   337,
     330,   339,   339,    81,   204,   330,   341,   341,   341,   282,
      61,    62,   329,    81,   282,   282,   282,   332,   332,   271,
      74,    75,   316,    80,    81,   105,   106,   176,   194,   317,
     318,   324,    68,    69,    70,   311,   312,   282,   271,   318,
     311,   282,   273,   273,   273,   273,   322,    80,    80,    91,
     197,   273,   282,   284,   461,   235,   236,   237,   238,   239,
     376,   227,   375,    80,   273,   376,   375,   283,   368,   273,
       5,   283,   356,   306,   308,   313,   341,   319,   319,   319,
      29,   282,   282,   310,     8,   282,     7,   282,   310,     5,
     282,   273,   485,    82,   334,   282,   375,    80,   371,   375,
     479,   272,   272,   272,   319,   272,   272,   272,    81,   317,
     312,   210,   225,   230,   318,   282,   110,   282,    81,   212,
     213,   283,   307,   309,   314,   272,   320,   323,   321,    30,
     327,   282,   282,   282,   282,   133,   138,   460,   273,   273,
     273,   322,   273,   282,   284,   455,   273,   282,   284,   463,
     273,   282,   284,   457,    81,   119,   282,   282,   282,   282,
     273,   282,   282,   282,    22,    80,   326,   282,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   280,   281,   281,   282,   282,   283,   283,   284,   284,
     284,   285,   285,   285,   285,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   288,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   290,   291,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   293,   293,   293,   293,   293,   293,   294,   294,   294,
     294,   294,   294,   294,   295,   296,   296,   297,   298,   298,
     299,   299,   299,   299,   299,   299,   299,   299,   300,   300,
     301,   301,   302,   303,   304,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   306,   307,   307,   307,
     307,   307,   307,   308,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   310,   310,   311,   311,   312,   312,   312,
     313,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   315,   315,   316,   316,   317,   318,   318,   319,   320,
     320,   320,   320,   321,   321,   321,   321,   322,   322,   322,
     322,   323,   323,   323,   323,   324,   324,   324,   324,   324,
     325,   326,   326,   327,   327,   328,   329,   329,   330,   331,
     331,   331,   332,   333,   333,   334,   334,   334,   334,   334,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   344,   345,   346,   347,   347,   348,   348,   349,   350,
     350,   351,   351,   351,   351,   351,   351,   351,   351,   351,
     351,   351,   351,   351,   351,   351,   351,   351,   351,   352,
     352,   353,   354,   354,   355,   355,   355,   356,   357,   357,
     358,   358,   359,   359,   360,   360,   361,   361,   362,   363,
     363,   364,   364,   364,   364,   364,   364,   365,   366,   366,
     366,   366,   366,   367,   367,   368,   368,   369,   369,   369,
     370,   370,   370,   371,   371,   372,   372,   373,   373,   374,
     374,   374,   375,   375,   375,   375,   376,   376,   376,   376,
     376,   377,   378,   379,   379,   379,   379,   379,   380,   381,
     381,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     382,   383,   383,   383,   384,   384,   385,   385,   386,   386,
     387,   388,   388,   389,   389,   390,   390,   391,   392,   393,
     394,   394,   394,   395,   395,   395,   396,   396,   396,   396,
     396,   396,   396,   397,   397,   398,   399,   399,   399,   400,
     400,   401,   402,   402,   402,   402,   402,   403,   403,   404,
     405,   405,   406,   406,   406,   407,   407,   408,   409,   409,
     410,   410,   411,   411,   412,   412,   413,   413,   414,   415,
     416,   416,   417,   417,   418,   419,   419,   420,   421,   422,
     423,   424,   424,   424,   425,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   427,   428,   428,
     428,   429,   429,   429,   429,   429,   430,   430,   431,   431,
     431,   432,   432,   433,   433,   434,   434,   435,   436,   436,
     437,   438,   439,   440,   440,   440,   441,   442,   442,   442,
     443,   444,   444,   444,   445,   445,   445,   446,   446,   447,
     448,   448,   449,   450,   450,   451,   451,   452,   452,   453,
     453,   454,   454,   455,   456,   457,   458,   459,   460,   460,
     461,   461,   462,   463,   463,   464,   465,   465,   465,   465,
     466,   466,   467,   467,   467,   468,   468,   468,   469,   469,
     470,   470,   471,   471,   472,   473,   473,   474,   474,   475,
     476,   476,   476,   476,   476,   476,   476,   476,   476,   476,
     476,   476,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   478,   478,   478,
     478,   478,   478,   479,   479,   479,   479,   479,   479,   480,
     480,   480,   481,   481,   482,   482,   482,   482,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   484,   484,   484,   484,
     485,   485,   486,   486,   487,   488,   488,   488,   489,   489,
     490,   490,   491,   491,   491,   492,   492,   492,   493,   493,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   494,   494,   495,   495,   495,   495,   495,
     495,   495,   496,   496,   497,   497,   498,   498,   498,   498,
     499,   499,   500,   500,   501,   501,   502,   503,   503,   503,
     503,   503,   503,   503,   503,   503,   503,   503,   503,   503,
     503,   503,   503,   504,   505,   505,   505,   506,   507,   507,
     507,   508,   509,   509,   509,   509,   510,   511,   511,   511,
     511,   511,   512,   513,   513,   513,   513,   513,   513,   513,
     513,   513,   513,   513,   513,   514,   515,   515,   515,   515,
     515,   515,   515,   516,   517,   517,   517,   517,   517,   517,
     517,   517,   517,   518,   519,   519,   519,   519,   519,   519,
     519,   519,   520,   521,   521,   521,   521,   521,   522,   523,
     523,   524,   525,   525,   525,   526,   527,   527,   527,   527,
     528,   529,   529,   529,   529,   530,   530,   530,   531,   531,
     531,   531,   531,   531,   531,   531,   531,   531,   532,   532,
     532,   532,   532,   532,   532,   532,   532,   532,   532,   532,
     533,   533,   533,   533,   533,   533,   533,   533,   534,   535,
     535,   535,   536,   537,   537,   537,   537,   538,   538,   538,
     538,   538,   538,   538,   539,   540,   540,   541,   542,   542,
     542,   542,   543,   544,   545,   546,   547,   548,   548,   548,
     548,   548,   548,   549,   550,   550,   551,   552,   552,   552,
     552,   552,   553,   554,   554,   554,   554,   554
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
       3,     2,     2,     3,     3,     2,     2,     2,     2,     3,
       4,     2,     3,     2,     2,     3,     2,     2,     2,     2,
       2,     3,     2,     2,     3,     2,     1,     3,     0,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     1,     1,     0,     2,     0,     2,     2,     3,     8,
       8,     8,     8,     8,     9,     8,     0,     0,     2,     2,
       3,     3,     3,     0,     0,     2,     2,     4,     4,     4,
       4,     4,     3,     1,     1,     3,     1,     1,     1,     1,
       0,     0,     2,     2,     6,     6,     6,     6,     4,     4,
       3,     2,     2,     1,     1,     1,     1,     3,     0,     0,
       2,     2,     2,     0,     2,     2,     2,     0,     2,     2,
       2,     0,     2,     2,     2,     1,     1,     1,     1,     1,
       7,     1,     2,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     2,     1,     2,     1,     2,     2,
       1,     2,     2,     2,     0,     1,     1,     2,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     1,     3,     3,     5,     1,     2,
       1,     3,     1,     2,     2,     2,     1,     2,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     1,     2,     2,
       1,     1,     1,     3,     1,     1,     1,     7,     6,     3,
       1,     1,     0,     1,     1,     0,     3,     5,     3,     1,
       1,     0,     0,     3,     3,     3,     1,     1,     1,     1,
       1,     2,     1,     0,     4,     4,     4,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     1,     3,     1,     1,     3,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     4,
       2,     3,     2,     2,     1,     1,     3,     4,     1,     2,
       1,     1,     2,     3,     1,     3,     4,     3,     5,     3,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     2,
       2,     1,     1,     3,     1,     1,     1,     2,     1,     4,
       1,     1,     6,     1,     1,     1,     2,     2,     6,     1,
       2,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     3,
       3,     3,     1,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     3,     3,     3,     3,     5,     1,     2,     1,
       1,     2,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     4,     1,     4,     1,     1,     1,     1,
       5,     3,     0,     6,     5,     1,     2,     2,     3,     5,
       3,     3,     1,     1,     1,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     3,     4,     1,
       0,     2,     1,     1,     5,     7,     5,     4,     1,     1,
       2,     3,     1,     1,     1,     2,     3,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     4,     5,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     1,     1,     1,     2,     1,     1,
       1,     2,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     2,     4,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     1,     1,
       1,     1,     2,     4,     2,     1,     2,     1,     1,     1,
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
          case 81: /* "string"  */
#line 253 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3442 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 82: /* "quoted string"  */
#line 253 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3448 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 83: /* "string with a trailing asterisk"  */
#line 253 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3454 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 285: /* line  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3460 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 286: /* base_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3466 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 287: /* add_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3472 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 288: /* replace_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3478 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 289: /* create_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3484 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 290: /* insert_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3490 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 291: /* delete_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3496 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 292: /* list_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3502 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 293: /* reset_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3508 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 294: /* flush_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3514 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 295: /* rename_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3520 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 296: /* export_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3526 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 297: /* monitor_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3532 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 298: /* monitor_event  */
#line 686 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3538 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 302: /* describe_cmd  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3544 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 303: /* table_block_alloc  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 3550 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 306: /* chain_block_alloc  */
#line 510 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 3556 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 308: /* set_block_alloc  */
#line 519 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3562 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 310: /* set_block_expr  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3568 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 313: /* map_block_alloc  */
#line 522 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3574 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 317: /* data_type_atom_expr  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3580 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 318: /* data_type_expr  */
#line 490 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3586 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 319: /* obj_block_alloc  */
#line 525 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 3592 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 324: /* type_identifier  */
#line 485 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3598 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 327: /* dev_spec  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3604 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 330: /* identifier  */
#line 485 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3610 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 331: /* string  */
#line 485 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3616 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* table_spec  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3622 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 336: /* chain_spec  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3628 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* chain_identifier  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3634 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* set_spec  */
#line 501 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3640 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* set_identifier  */
#line 501 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3646 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* obj_spec  */
#line 501 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3652 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* obj_identifier  */
#line 501 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3658 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* handle_spec  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3664 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* position_spec  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3670 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* rule_position  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3676 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 345: /* ruleid_spec  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3682 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* comment_spec  */
#line 485 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3688 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* ruleset_spec  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3694 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 348: /* rule  */
#line 512 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 3700 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* stmt_list  */
#line 528 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 3706 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 351: /* stmt  */
#line 530 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3712 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 352: /* verdict_stmt  */
#line 530 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3718 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 353: /* verdict_map_stmt  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3724 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* verdict_map_expr  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3730 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 355: /* verdict_map_list_expr  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3736 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* verdict_map_list_member_expr  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3742 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 357: /* counter_stmt  */
#line 532 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3748 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* counter_stmt_alloc  */
#line 532 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3754 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* log_stmt  */
#line 540 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3760 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 362: /* log_stmt_alloc  */
#line 540 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3766 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 369: /* limit_stmt  */
#line 543 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3772 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 371: /* quota_unit  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3778 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* quota_stmt  */
#line 543 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3784 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* reject_stmt  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3790 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 378: /* reject_stmt_alloc  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3796 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 380: /* nat_stmt  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3802 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 381: /* nat_stmt_alloc  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3808 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 382: /* primary_stmt_expr  */
#line 586 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3814 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* shift_stmt_expr  */
#line 588 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3820 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* and_stmt_expr  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3826 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* exclusive_or_stmt_expr  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3832 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* inclusive_or_stmt_expr  */
#line 590 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3838 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* basic_stmt_expr  */
#line 586 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3844 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* concat_stmt_expr  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3850 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* map_stmt_expr_set  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3856 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* map_stmt_expr  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3862 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* prefix_stmt_expr  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3868 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* range_stmt_expr  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3874 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 393: /* wildcard_stmt_expr  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3880 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* multiton_stmt_expr  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3886 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* stmt_expr  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3892 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* masq_stmt  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3898 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* masq_stmt_alloc  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3904 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* redir_stmt  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3910 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* redir_stmt_alloc  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3916 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* dup_stmt  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3922 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* fwd_stmt  */
#line 556 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3928 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* queue_stmt  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3934 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* queue_stmt_alloc  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3940 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* set_elem_expr_stmt  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3946 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* set_elem_expr_stmt_alloc  */
#line 609 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3952 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 415: /* set_stmt  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3958 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* meter_stmt  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3964 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* flow_stmt_legacy_alloc  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3970 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* meter_stmt_alloc  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3976 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* match_stmt  */
#line 530 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3982 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 423: /* variable_expr  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3988 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* symbol_expr  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3994 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* integer_expr  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4000 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* primary_expr  */
#line 566 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4006 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* fib_expr  */
#line 681 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4012 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* shift_expr  */
#line 566 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4018 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 432: /* and_expr  */
#line 566 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4024 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* exclusive_or_expr  */
#line 568 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4030 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* inclusive_or_expr  */
#line 568 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4036 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* basic_expr  */
#line 570 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4042 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 436: /* concat_expr  */
#line 593 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4048 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* prefix_rhs_expr  */
#line 575 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4054 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* range_rhs_expr  */
#line 575 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4060 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 439: /* wildcard_rhs_expr  */
#line 575 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4066 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 440: /* multiton_rhs_expr  */
#line 573 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4072 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 441: /* map_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4078 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* expr  */
#line 615 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4084 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* set_expr  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4090 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 444: /* set_list_expr  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4096 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 445: /* set_list_member_expr  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4102 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 446: /* meter_key_expr  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4108 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 447: /* meter_key_expr_alloc  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4114 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* set_elem_expr  */
#line 607 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4120 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 449: /* set_elem_expr_alloc  */
#line 607 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4126 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* set_lhs_expr  */
#line 607 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4132 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 453: /* set_rhs_expr  */
#line 607 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4138 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 454: /* initializer_expr  */
#line 615 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4144 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 455: /* counter_config  */
#line 690 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).counter)); }
#line 4150 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 456: /* counter_obj  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4156 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* quota_config  */
#line 692 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).quota)); }
#line 4162 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* quota_obj  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4168 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* ct_obj_alloc  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4174 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 463: /* limit_config  */
#line 694 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).limit)); }
#line 4180 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* limit_obj  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4186 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 465: /* relational_expr  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4192 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* list_rhs_expr  */
#line 620 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4198 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 467: /* rhs_expr  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4204 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* shift_rhs_expr  */
#line 620 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4210 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* and_rhs_expr  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4216 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* exclusive_or_rhs_expr  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4222 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* inclusive_or_rhs_expr  */
#line 622 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4228 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* basic_rhs_expr  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4234 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* concat_rhs_expr  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4240 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* boolean_expr  */
#line 702 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4246 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* keyword_expr  */
#line 615 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4252 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* primary_rhs_expr  */
#line 620 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4258 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* verdict_expr  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4264 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* meta_expr  */
#line 669 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4270 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* meta_stmt  */
#line 538 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4276 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 487: /* numgen_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4282 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* hash_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4288 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 490: /* rt_expr  */
#line 673 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4294 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 492: /* ct_expr  */
#line 677 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4300 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 499: /* symbol_stmt_expr  */
#line 620 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4306 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 500: /* list_stmt_expr  */
#line 588 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4312 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 501: /* ct_stmt  */
#line 536 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4318 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 502: /* payload_stmt  */
#line 534 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4324 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 503: /* payload_expr  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4330 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 504: /* payload_raw_expr  */
#line 632 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4336 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* eth_hdr_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4342 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 508: /* vlan_hdr_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4348 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* arp_hdr_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4354 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 512: /* ip_hdr_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4360 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 514: /* icmp_hdr_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4366 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 516: /* ip6_hdr_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4372 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* icmp6_hdr_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4378 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 520: /* auth_hdr_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4384 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 522: /* esp_hdr_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4390 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 524: /* comp_hdr_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4396 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 526: /* udp_hdr_expr  */
#line 650 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4402 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* udplite_hdr_expr  */
#line 650 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4408 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* tcp_hdr_expr  */
#line 697 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4414 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* dccp_hdr_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4420 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 536: /* sctp_hdr_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4426 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* exthdr_expr  */
#line 657 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4432 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 539: /* hbh_hdr_expr  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4438 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 541: /* rt_hdr_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4444 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* rt0_hdr_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4450 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 545: /* rt2_hdr_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4456 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* frag_hdr_expr  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4462 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 549: /* dst_hdr_expr  */
#line 659 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4468 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* mh_hdr_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4474 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 553: /* exthdr_exists_expr  */
#line 706 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4480 "parser_bison.c" /* yacc.c:1257  */
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

#line 4597 "parser_bison.c" /* yacc.c:1429  */
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
#line 715 "parser_bison.y" /* yacc.c:1646  */
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
#line 4800 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 8:
#line 741 "parser_bison.y" /* yacc.c:1646  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 4812 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 9:
#line 749 "parser_bison.y" /* yacc.c:1646  */
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
#line 4830 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 763 "parser_bison.y" /* yacc.c:1646  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 4840 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 11:
#line 770 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 4846 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 771 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 4852 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 772 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 4858 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 774 "parser_bison.y" /* yacc.c:1646  */
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
#line 4892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 805 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 16:
#line 806 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 807 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4910 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 808 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 809 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 810 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4928 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 811 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4934 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 812 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4940 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 813 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4946 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 814 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4952 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 815 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4958 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 816 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4964 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 817 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 821 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 826 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 4988 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 832 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4996 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 837 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 844 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5015 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 848 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5023 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 853 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5033 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 860 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5043 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 866 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5051 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 870 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5064 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 879 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5072 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 883 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5080 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 887 "parser_bison.y" /* yacc.c:1646  */
    {

				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5089 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 892 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 42:
#line 898 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5105 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 904 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5113 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 909 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5123 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 915 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5131 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 920 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5142 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 928 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5152 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 935 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5162 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 941 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5170 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 945 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 954 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5191 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 958 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5199 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 962 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 966 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5215 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 972 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5223 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 56:
#line 978 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5231 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 982 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5239 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 986 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 990 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5255 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 994 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5263 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 998 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5271 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1002 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5279 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1006 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5287 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1010 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5295 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1014 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5303 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1020 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5311 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1024 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5319 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1028 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5327 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1032 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5335 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1036 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5343 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1040 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5351 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1044 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5359 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1048 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5367 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1052 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5375 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1056 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5383 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1060 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5391 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1064 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5399 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1068 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5407 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1072 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5415 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1076 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1080 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5431 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1084 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5439 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1088 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1092 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1096 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5463 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1100 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5471 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1104 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5479 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1108 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5487 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1112 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5495 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1116 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5503 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1122 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5511 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1126 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5519 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1130 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 5527 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1134 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5535 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1138 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5543 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1142 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5551 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1148 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1152 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5567 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1156 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5575 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1160 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5583 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1164 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1168 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5599 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1172 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5607 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1178 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 5616 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1185 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct export *export = export_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_EXPORT, &h, &(yyloc), export);
			}
#line 5626 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1191 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct export *export = export_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_EXPORT, &h, &(yyloc), export);
			}
#line 5636 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1199 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 5647 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1207 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 5653 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1208 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 5659 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1211 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 5665 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1212 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 5671 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1213 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 5677 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1214 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 5683 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1215 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 5689 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1216 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 5695 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1217 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 5701 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1218 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 5707 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1221 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 5713 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1225 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_XML; }
#line 5719 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1226 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 5725 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1230 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 5735 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1238 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 5744 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1245 "parser_bison.y" /* yacc.c:1646  */
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
#line 5760 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1258 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 5766 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1265 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5779 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1276 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5791 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1286 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5803 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1296 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5816 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1307 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5829 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1316 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 5842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1327 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5855 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1338 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 5864 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1344 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 5870 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1350 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 5879 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1357 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 5887 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1362 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 5893 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1366 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 5902 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1371 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 5911 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1376 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 5920 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1381 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 5929 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1386 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 5938 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1398 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 5946 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1404 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 5952 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1405 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 5958 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1406 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 5964 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1410 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 5972 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1415 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 5978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1421 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].expr)->dtype;

				expr_free((yyvsp[-1].expr));
				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 5991 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1432 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6002 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1441 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6013 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1450 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6024 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1457 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6033 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1462 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6042 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1470 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 6050 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1474 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 6058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1479 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 6064 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1480 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 6070 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1484 "parser_bison.y" /* yacc.c:1646  */
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
#line 6086 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1499 "parser_bison.y" /* yacc.c:1646  */
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
#line 6107 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1518 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 6115 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1523 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6121 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1527 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->counter = *(yyvsp[0].counter);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1533 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1537 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->quota = *(yyvsp[0].quota);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6145 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1543 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6151 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1547 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1552 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1556 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->limit = *(yyvsp[0].limit);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6174 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1562 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6180 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1563 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("mark"); }
#line 6186 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1564 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("dscp"); }
#line 6192 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1565 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("ecn"); }
#line 6198 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1566 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("classid"); }
#line 6204 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1570 "parser_bison.y" /* yacc.c:1646  */
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
#line 6234 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1597 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 6240 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1598 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = -(yyvsp[0].val); }
#line 6246 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1601 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6252 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1602 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6258 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1606 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].chain)->policy != -1) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].val);
			}
#line 6271 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1616 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_ACCEPT; }
#line 6277 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1617 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_DROP;   }
#line 6283 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1629 "parser_bison.y" /* yacc.c:1646  */
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
#line 6300 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1643 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6306 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1647 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6312 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1648 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 6318 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1649 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_INET; }
#line 6324 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1650 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_ARP; }
#line 6330 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1651 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 6336 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1652 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 6342 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1656 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table	= (yyvsp[0].string);
			}
#line 6352 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1664 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 6361 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1671 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 6370 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1678 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 6379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1685 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 6388 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1692 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj		= (yyvsp[0].string);
			}
#line 6397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1699 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj		= (yyvsp[0].string);
			}
#line 6406 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1706 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 6416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1714 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 6426 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1722 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 6434 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1726 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 6443 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1733 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 6452 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1740 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strlen((yyvsp[0].string)) > UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed", UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 6465 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1751 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 6474 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1756 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 6483 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1763 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 6491 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1767 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 6499 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1773 "parser_bison.y" /* yacc.c:1646  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 6513 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1785 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 6523 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1791 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 6532 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1818 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 6540 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1822 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 6548 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1828 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6556 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1834 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6565 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1839 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 6576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1848 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 6585 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1853 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 6594 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1861 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 6602 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1870 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 6610 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1874 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 6620 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1882 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 6628 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1889 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 6636 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1893 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 6644 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1903 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 6652 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1909 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 6660 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1916 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 6669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1921 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 6678 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1926 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 6687 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1931 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 6696 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1936 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 6705 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1941 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 6713 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1947 "parser_bison.y" /* yacc.c:1646  */
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
#line 6743 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1975 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 6751 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1979 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 6759 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1983 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 6767 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1987 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 6775 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1991 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 6783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1997 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6791 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 295:
#line 2004 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 6799 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 296:
#line 2008 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 6807 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 297:
#line 2014 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 6820 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 298:
#line 2023 "parser_bison.y" /* yacc.c:1646  */
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
#line 6843 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 299:
#line 2042 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 6853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 300:
#line 2049 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 6859 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 301:
#line 2050 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 302:
#line 2051 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6871 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 303:
#line 2054 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("bytes"); }
#line 6877 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2055 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6883 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2058 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6889 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2060 "parser_bison.y" /* yacc.c:1646  */
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
#line 6906 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2075 "parser_bison.y" /* yacc.c:1646  */
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
#line 6926 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 308:
#line 2091 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 6936 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 309:
#line 2098 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 6942 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 310:
#line 2099 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6948 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 311:
#line 2100 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 312:
#line 2103 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 313:
#line 2104 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 6966 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 314:
#line 2105 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 6972 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 315:
#line 2107 "parser_bison.y" /* yacc.c:1646  */
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
#line 6989 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 316:
#line 2121 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL; }
#line 6995 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 317:
#line 2122 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60; }
#line 7001 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 318:
#line 2123 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 7007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 319:
#line 2124 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 7013 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2125 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 7019 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 322:
#line 2132 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 7027 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2138 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 7036 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2143 "parser_bison.y" /* yacc.c:1646  */
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
#line 7051 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2154 "parser_bison.y" /* yacc.c:1646  */
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
#line 7066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2165 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpx_code_type;
				xfree((yyvsp[0].string));
			}
#line 7080 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2175 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 7088 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 329:
#line 2184 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_SNAT;
			}
#line 7097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2189 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_DNAT;
			}
#line 7106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2195 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7112 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2196 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2197 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7124 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2198 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2199 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2200 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7142 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2201 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7148 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2202 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7154 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2203 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7160 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2204 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7166 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2209 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7174 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2213 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7182 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2220 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7190 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2227 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7198 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 349:
#line 2234 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 352:
#line 2244 "parser_bison.y" /* yacc.c:1646  */
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
#line 7227 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 355:
#line 2267 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7235 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 356:
#line 2270 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7241 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 357:
#line 2274 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 7249 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 358:
#line 2280 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7257 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2286 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 7270 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2307 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7278 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2311 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7286 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2315 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7295 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2320 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7304 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 370:
#line 2325 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7312 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 371:
#line 2329 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7320 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 372:
#line 2333 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7328 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2342 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = masq_stmt_alloc(&(yyloc)); }
#line 7334 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2346 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->masq.proto = (yyvsp[0].expr);
			}
#line 7342 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2350 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->masq.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 7351 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2355 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 7359 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 381:
#line 2364 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = redir_stmt_alloc(&(yyloc)); }
#line 7365 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2368 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 7373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2372 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 7381 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2376 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7389 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2380 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7398 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 386:
#line 2385 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7407 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 387:
#line 2392 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 7416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2397 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 7426 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 389:
#line 2405 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.to = (yyvsp[0].expr);
			}
#line 7435 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2413 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7443 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 392:
#line 2418 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 7449 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 393:
#line 2419 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 7455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2420 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 7461 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2428 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 7469 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2434 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7477 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2441 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 7486 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2446 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 7494 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 403:
#line 2453 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7502 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 404:
#line 2458 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 7508 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 405:
#line 2459 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 7514 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2467 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 7522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2473 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 7533 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2481 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 7539 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2482 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 7545 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2486 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 7556 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2492 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 7562 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2496 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 7570 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2502 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7578 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2509 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 7586 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2515 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 7598 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2525 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7606 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2531 "parser_bison.y" /* yacc.c:1646  */
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
#line 7625 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2549 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7636 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2556 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7647 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2565 "parser_bison.y" /* yacc.c:1646  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 7660 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2575 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7666 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2576 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7672 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2577 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7678 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2578 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7684 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2579 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7690 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2580 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7696 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2581 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7702 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2582 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7708 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2583 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7714 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2584 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7720 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2585 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7726 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2586 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 7732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2590 "parser_bison.y" /* yacc.c:1646  */
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
#line 7757 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2612 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 7763 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2613 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 7769 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2614 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 7775 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2617 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 7781 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2618 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 7787 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2619 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 7793 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2620 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 7799 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2621 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 7805 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2625 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7813 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2633 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7821 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2637 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7829 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2644 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7837 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2651 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7845 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2658 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2668 "parser_bison.y" /* yacc.c:1646  */
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

  case 460:
#line 2687 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 7882 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2693 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7890 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2699 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 7903 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 466:
#line 2715 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7911 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2726 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7920 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2733 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 7929 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 472:
#line 2738 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 7938 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2746 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7946 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2750 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2754 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 7962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2761 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 7971 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2768 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 7979 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2778 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 7987 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2784 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 7995 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2791 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val) * 1000;
			}
#line 8003 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2795 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 8011 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2813 "parser_bison.y" /* yacc.c:1646  */
    {
				struct counter *counter;

				counter = xzalloc(sizeof(*counter));
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
				(yyval.counter) = counter;
			}
#line 8024 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 494:
#line 2824 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
				(yyval.obj)->counter = *(yyvsp[0].counter);
			}
#line 8034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 495:
#line 2832 "parser_bison.y" /* yacc.c:1646  */
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
#line 8057 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 496:
#line 2853 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
				(yyval.obj)->quota = *(yyvsp[0].quota);
			}
#line 8067 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2860 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 8073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 498:
#line 2863 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_TCP; }
#line 8079 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 499:
#line 2864 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_UDP; }
#line 8085 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 500:
#line 2868 "parser_bison.y" /* yacc.c:1646  */
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
#line 8104 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2883 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 8112 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2889 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 8120 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 503:
#line 2895 "parser_bison.y" /* yacc.c:1646  */
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
#line 8135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 504:
#line 2906 "parser_bison.y" /* yacc.c:1646  */
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
#line 8159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 505:
#line 2928 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
				(yyval.obj)->limit = *(yyvsp[0].limit);
			}
#line 8169 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 506:
#line 2936 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8177 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 507:
#line 2940 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_FLAGCMP, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8185 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 508:
#line 2944 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8193 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 509:
#line 2948 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-3]), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[-1].expr));
			}
#line 8201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 510:
#line 2954 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8211 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 511:
#line 2960 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8221 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 512:
#line 2967 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8227 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 513:
#line 2968 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8233 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 514:
#line 2969 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8239 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 516:
#line 2974 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 517:
#line 2978 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8255 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 519:
#line 2985 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8263 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 521:
#line 2992 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8271 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 523:
#line 2999 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8279 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 526:
#line 3009 "parser_bison.y" /* yacc.c:1646  */
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
#line 8300 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 527:
#line 3027 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = true; }
#line 8306 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 528:
#line 3028 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = false; }
#line 8312 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 529:
#line 3032 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 1, &(yyvsp[0].val));
			}
#line 8322 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 530:
#line 3039 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 8328 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 531:
#line 3040 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 8334 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 532:
#line 3041 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 8340 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 533:
#line 3042 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 8346 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 534:
#line 3043 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 8352 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 535:
#line 3044 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 8358 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 536:
#line 3045 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 8364 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 537:
#line 3046 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 8370 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 538:
#line 3047 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 8376 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 539:
#line 3048 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 8382 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 540:
#line 3049 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 8388 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 541:
#line 3050 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 8394 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 542:
#line 3053 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8400 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 543:
#line 3054 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8406 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 544:
#line 3055 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8412 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 545:
#line 3056 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8418 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 546:
#line 3058 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 547:
#line 3065 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8440 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 548:
#line 3072 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8451 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 549:
#line 3079 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8462 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 550:
#line 3086 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 551:
#line 3093 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8484 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 552:
#line 3100 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8495 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 553:
#line 3107 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8506 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 554:
#line 3114 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8517 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 555:
#line 3121 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8528 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 556:
#line 3128 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8539 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 557:
#line 3136 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_EQ; }
#line 8545 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 558:
#line 3137 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_NEQ; }
#line 8551 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 559:
#line 3138 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LT; }
#line 8557 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 560:
#line 3139 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GT; }
#line 8563 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 561:
#line 3140 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GTE; }
#line 8569 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 562:
#line 3141 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LTE; }
#line 8575 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 563:
#line 3145 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 8583 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 564:
#line 3149 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 8591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 565:
#line 3153 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 8599 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 566:
#line 3157 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].string));
			}
#line 8607 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 567:
#line 3161 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].string));
			}
#line 8615 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 568:
#line 3165 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 8623 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 569:
#line 3171 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 8631 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 570:
#line 3175 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 8639 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 571:
#line 3179 "parser_bison.y" /* yacc.c:1646  */
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
#line 8657 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 574:
#line 3197 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_LEN; }
#line 8663 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 575:
#line 3198 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 8669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 576:
#line 3199 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 8675 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 577:
#line 3200 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 8681 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 578:
#line 3203 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_MARK; }
#line 8687 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 579:
#line 3204 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIF; }
#line 8693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 580:
#line 3205 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 8699 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 581:
#line 3206 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 8705 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 582:
#line 3207 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIF; }
#line 8711 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 583:
#line 3208 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 8717 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 584:
#line 3209 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 8723 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 585:
#line 3210 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKUID; }
#line 8729 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 586:
#line 3211 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKGID; }
#line 8735 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 587:
#line 3212 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 8741 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 588:
#line 3213 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 8747 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 589:
#line 3214 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 8753 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 590:
#line 3215 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 8759 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 591:
#line 3216 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 8765 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 592:
#line 3217 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CPU; }
#line 8771 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 593:
#line 3218 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 8777 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 594:
#line 3219 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 8783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 595:
#line 3220 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 8789 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 596:
#line 3224 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 8797 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 597:
#line 3228 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 8805 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 598:
#line 3232 "parser_bison.y" /* yacc.c:1646  */
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
#line 8823 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 599:
#line 3246 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 8831 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 600:
#line 3251 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 8837 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 601:
#line 3252 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 8843 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 602:
#line 3255 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 8849 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 603:
#line 3256 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 8855 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 604:
#line 3260 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 8863 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 605:
#line 3266 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 8872 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 606:
#line 3271 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 8881 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 607:
#line 3276 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 8889 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 608:
#line 3281 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 8895 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 609:
#line 3282 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 8901 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 610:
#line 3286 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 8909 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 611:
#line 3290 "parser_bison.y" /* yacc.c:1646  */
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
#line 8931 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 612:
#line 3309 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 8937 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 613:
#line 3310 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 8943 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 614:
#line 3311 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 8949 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 615:
#line 3315 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1, NFPROTO_UNSPEC);
			}
#line 8957 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 616:
#line 3319 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val), NFPROTO_UNSPEC);
			}
#line 8965 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 617:
#line 3323 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 8973 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 618:
#line 3328 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 8979 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 619:
#line 3329 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 8985 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 620:
#line 3332 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 8991 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 621:
#line 3333 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 8997 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 622:
#line 3334 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_MARK; }
#line 9003 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 623:
#line 3335 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATE; }
#line 9009 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 624:
#line 3336 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 9015 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 625:
#line 3337 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 9021 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 626:
#line 3338 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 9027 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 627:
#line 3339 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 9033 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 628:
#line 3340 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9039 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 629:
#line 3341 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9045 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 630:
#line 3342 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9051 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 631:
#line 3343 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9057 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 632:
#line 3344 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 9063 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 633:
#line 3345 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 9069 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 635:
#line 3349 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9075 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 636:
#line 3350 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9081 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 637:
#line 3351 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9087 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 638:
#line 3352 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9093 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3353 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9099 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 640:
#line 3354 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9105 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 642:
#line 3358 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 9111 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3359 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 9117 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 644:
#line 3362 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9123 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 645:
#line 3363 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9129 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 646:
#line 3366 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 9135 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 647:
#line 3367 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 9141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 648:
#line 3368 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 9147 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 649:
#line 3369 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 9153 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 652:
#line 3377 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9163 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 653:
#line 3383 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9173 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 654:
#line 3391 "parser_bison.y" /* yacc.c:1646  */
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
#line 9190 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 655:
#line 3404 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 9198 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 656:
#line 3410 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].expr)->ops->type == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9209 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 673:
#line 3437 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				(yyval.expr)->payload.base	= (yyvsp[-4].val);
				(yyval.expr)->payload.offset	= (yyvsp[-2].val);
				(yyval.expr)->len			= (yyvsp[0].val);
				(yyval.expr)->dtype		= &integer_type;
			}
#line 9221 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 674:
#line 3446 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 9227 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 675:
#line 3447 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 9233 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 676:
#line 3448 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 9239 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 677:
#line 3452 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 9247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 678:
#line 3457 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 9253 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 679:
#line 3458 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 9259 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 680:
#line 3459 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 9265 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 681:
#line 3463 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 9273 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 682:
#line 3468 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_VID; }
#line 9279 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 683:
#line 3469 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_CFI; }
#line 9285 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 684:
#line 3470 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_PCP; }
#line 9291 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 685:
#line 3471 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 9297 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 686:
#line 3475 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 9305 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 687:
#line 3480 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HRD; }
#line 9311 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 688:
#line 3481 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PRO; }
#line 9317 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 689:
#line 3482 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HLN; }
#line 9323 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 690:
#line 3483 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PLN; }
#line 9329 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 691:
#line 3484 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_OP; }
#line 9335 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 692:
#line 3488 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 9343 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 693:
#line 3493 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_VERSION; }
#line 9349 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 694:
#line 3494 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 9355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 695:
#line 3495 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DSCP; }
#line 9361 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 696:
#line 3496 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ECN; }
#line 9367 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 697:
#line 3497 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 9373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 698:
#line 3498 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ID; }
#line 9379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 699:
#line 3499 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 9385 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 700:
#line 3500 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_TTL; }
#line 9391 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 701:
#line 3501 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 9397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 702:
#line 3502 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 9403 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 703:
#line 3503 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_SADDR; }
#line 9409 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 704:
#line 3504 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DADDR; }
#line 9415 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 705:
#line 3508 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 9423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 706:
#line 3513 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 9429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 707:
#line 3514 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 9435 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 708:
#line 3515 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 9441 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 709:
#line 3516 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_ID; }
#line 9447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 710:
#line 3517 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 9453 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 711:
#line 3518 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 9459 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 712:
#line 3519 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 9465 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 713:
#line 3523 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 9473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 714:
#line 3528 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 9479 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 715:
#line 3529 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 9485 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 716:
#line 3530 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_ECN; }
#line 9491 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 717:
#line 3531 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 9497 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 718:
#line 3532 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 9503 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 719:
#line 3533 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 9509 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 720:
#line 3534 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 9515 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 721:
#line 3535 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 9521 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 722:
#line 3536 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 9527 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 723:
#line 3539 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 9535 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 724:
#line 3544 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 9541 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 725:
#line 3545 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 9547 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 726:
#line 3546 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 9553 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 727:
#line 3547 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 9559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 728:
#line 3548 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 9565 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 729:
#line 3549 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 9571 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 730:
#line 3550 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 9577 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 731:
#line 3551 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 9583 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 732:
#line 3555 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 9591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 733:
#line 3560 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 9597 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 734:
#line 3561 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 9603 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 735:
#line 3562 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 9609 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 736:
#line 3563 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SPI; }
#line 9615 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 737:
#line 3564 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 9621 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 738:
#line 3568 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 9629 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 739:
#line 3573 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SPI; }
#line 9635 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 740:
#line 3574 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 9641 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 741:
#line 3578 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 9649 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 742:
#line 3583 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 9655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 743:
#line 3584 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 9661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 744:
#line 3585 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_CPI; }
#line 9667 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 745:
#line 3589 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 9675 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 746:
#line 3594 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 9681 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 747:
#line 3595 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 9687 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 748:
#line 3596 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 9693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 749:
#line 3597 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 9699 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 750:
#line 3601 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 9707 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 751:
#line 3606 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 9713 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 752:
#line 3607 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 9719 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 753:
#line 3608 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 9725 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 754:
#line 3609 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 9731 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 755:
#line 3613 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 9739 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 756:
#line 3617 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 9747 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 757:
#line 3621 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 9756 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 758:
#line 3627 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 9762 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 759:
#line 3628 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 9768 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 760:
#line 3629 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 9774 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 761:
#line 3630 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 9780 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 762:
#line 3631 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 9786 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 763:
#line 3632 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 9792 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 764:
#line 3633 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 9798 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 765:
#line 3634 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 9804 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 766:
#line 3635 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 9810 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 767:
#line 3636 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 9816 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 768:
#line 3639 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 9822 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 769:
#line 3640 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 9828 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 770:
#line 3641 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 9834 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 771:
#line 3642 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 9840 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 772:
#line 3643 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 9846 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 773:
#line 3644 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 9852 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 774:
#line 3645 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 9858 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 775:
#line 3646 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 9864 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 776:
#line 3647 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 9870 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 777:
#line 3648 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 9876 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 778:
#line 3649 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 9882 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 779:
#line 3650 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 9888 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 780:
#line 3653 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 9894 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 781:
#line 3654 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 9900 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 782:
#line 3655 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 9906 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 783:
#line 3656 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 9912 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 784:
#line 3657 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 9918 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 785:
#line 3658 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 9924 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 786:
#line 3659 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 9930 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 787:
#line 3660 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 9936 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 788:
#line 3664 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 9944 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 789:
#line 3669 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 9950 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 790:
#line 3670 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 9956 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 791:
#line 3671 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 9962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 792:
#line 3675 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 9970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 793:
#line 3680 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 9976 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 794:
#line 3681 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 9982 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 795:
#line 3682 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 9988 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 796:
#line 3683 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 9994 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 804:
#line 3696 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 10002 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 805:
#line 3701 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 10008 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 806:
#line 3702 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 10014 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 807:
#line 3706 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 10022 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 808:
#line 3711 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 10028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 809:
#line 3712 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 10034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 810:
#line 3713 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_TYPE; }
#line 10040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 811:
#line 3714 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 10046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 812:
#line 3718 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 10054 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 813:
#line 3724 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 10062 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 814:
#line 3730 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 10070 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 815:
#line 3735 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 10076 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 816:
#line 3739 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 10084 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 817:
#line 3744 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 10090 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 818:
#line 3745 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 10096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 819:
#line 3746 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 10102 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 820:
#line 3747 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 10108 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 821:
#line 3748 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 10114 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 822:
#line 3749 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_ID; }
#line 10120 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 823:
#line 3753 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 10128 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 824:
#line 3758 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 10134 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 825:
#line 3759 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 10140 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 826:
#line 3763 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 10148 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 827:
#line 3768 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 10154 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 828:
#line 3769 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 10160 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 829:
#line 3770 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_TYPE; }
#line 10166 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 830:
#line 3771 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 10172 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 831:
#line 3772 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 10178 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 832:
#line 3776 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 10194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 833:
#line 3789 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 10200 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 834:
#line 3790 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 10206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 835:
#line 3791 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 10212 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 836:
#line 3792 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 10218 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 837:
#line 3793 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_MH; }
#line 10224 "parser_bison.c" /* yacc.c:1646  */
    break;


#line 10228 "parser_bison.c" /* yacc.c:1646  */
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
#line 3796 "parser_bison.y" /* yacc.c:1906  */

