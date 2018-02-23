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
    IMPORT = 313,
    EXPORT = 314,
    MONITOR = 315,
    ALL = 316,
    ACCEPT = 317,
    DROP = 318,
    CONTINUE = 319,
    JUMP = 320,
    GOTO = 321,
    RETURN = 322,
    TO = 323,
    CONSTANT = 324,
    INTERVAL = 325,
    AUTOMERGE = 326,
    TIMEOUT = 327,
    GC_INTERVAL = 328,
    ELEMENTS = 329,
    POLICY = 330,
    MEMORY = 331,
    PERFORMANCE = 332,
    SIZE = 333,
    FLOW = 334,
    METER = 335,
    METERS = 336,
    NUM = 337,
    STRING = 338,
    QUOTED_STRING = 339,
    ASTERISK_STRING = 340,
    LL_HDR = 341,
    NETWORK_HDR = 342,
    TRANSPORT_HDR = 343,
    BRIDGE = 344,
    ETHER = 345,
    SADDR = 346,
    DADDR = 347,
    TYPE = 348,
    VLAN = 349,
    ID = 350,
    CFI = 351,
    PCP = 352,
    ARP = 353,
    HTYPE = 354,
    PTYPE = 355,
    HLEN = 356,
    PLEN = 357,
    OPERATION = 358,
    IP = 359,
    HDRVERSION = 360,
    HDRLENGTH = 361,
    DSCP = 362,
    ECN = 363,
    LENGTH = 364,
    FRAG_OFF = 365,
    TTL = 366,
    PROTOCOL = 367,
    CHECKSUM = 368,
    ICMP = 369,
    CODE = 370,
    SEQUENCE = 371,
    GATEWAY = 372,
    MTU = 373,
    OPTIONS = 374,
    IP6 = 375,
    PRIORITY = 376,
    FLOWLABEL = 377,
    NEXTHDR = 378,
    HOPLIMIT = 379,
    ICMP6 = 380,
    PPTR = 381,
    MAXDELAY = 382,
    AH = 383,
    RESERVED = 384,
    SPI = 385,
    ESP = 386,
    COMP = 387,
    FLAGS = 388,
    CPI = 389,
    UDP = 390,
    SPORT = 391,
    DPORT = 392,
    UDPLITE = 393,
    CSUMCOV = 394,
    TCP = 395,
    ACKSEQ = 396,
    DOFF = 397,
    WINDOW = 398,
    URGPTR = 399,
    OPTION = 400,
    ECHO = 401,
    EOL = 402,
    MAXSEG = 403,
    NOOP = 404,
    SACK = 405,
    SACK0 = 406,
    SACK1 = 407,
    SACK2 = 408,
    SACK3 = 409,
    SACK_PERMITTED = 410,
    TIMESTAMP = 411,
    KIND = 412,
    COUNT = 413,
    LEFT = 414,
    RIGHT = 415,
    TSVAL = 416,
    TSECR = 417,
    DCCP = 418,
    SCTP = 419,
    VTAG = 420,
    RT = 421,
    RT0 = 422,
    RT2 = 423,
    SEG_LEFT = 424,
    ADDR = 425,
    HBH = 426,
    FRAG = 427,
    RESERVED2 = 428,
    MORE_FRAGMENTS = 429,
    DST = 430,
    MH = 431,
    META = 432,
    MARK = 433,
    IIF = 434,
    IIFNAME = 435,
    IIFTYPE = 436,
    OIF = 437,
    OIFNAME = 438,
    OIFTYPE = 439,
    SKUID = 440,
    SKGID = 441,
    NFTRACE = 442,
    RTCLASSID = 443,
    IBRIPORT = 444,
    OBRIPORT = 445,
    PKTTYPE = 446,
    CPU = 447,
    IIFGROUP = 448,
    OIFGROUP = 449,
    CGROUP = 450,
    CLASSID = 451,
    NEXTHOP = 452,
    CT = 453,
    L3PROTOCOL = 454,
    PROTO_SRC = 455,
    PROTO_DST = 456,
    ZONE = 457,
    DIRECTION = 458,
    EVENT = 459,
    EXPIRATION = 460,
    HELPER = 461,
    LABEL = 462,
    STATE = 463,
    STATUS = 464,
    ORIGINAL = 465,
    REPLY = 466,
    COUNTER = 467,
    NAME = 468,
    PACKETS = 469,
    BYTES = 470,
    AVGPKT = 471,
    COUNTERS = 472,
    QUOTAS = 473,
    LIMITS = 474,
    HELPERS = 475,
    LOG = 476,
    PREFIX = 477,
    GROUP = 478,
    SNAPLEN = 479,
    QUEUE_THRESHOLD = 480,
    LEVEL = 481,
    LIMIT = 482,
    RATE = 483,
    BURST = 484,
    OVER = 485,
    UNTIL = 486,
    QUOTA = 487,
    USED = 488,
    NANOSECOND = 489,
    MICROSECOND = 490,
    MILLISECOND = 491,
    SECOND = 492,
    MINUTE = 493,
    HOUR = 494,
    DAY = 495,
    WEEK = 496,
    _REJECT = 497,
    WITH = 498,
    ICMPX = 499,
    SNAT = 500,
    DNAT = 501,
    MASQUERADE = 502,
    REDIRECT = 503,
    RANDOM = 504,
    FULLY_RANDOM = 505,
    PERSISTENT = 506,
    QUEUE = 507,
    QUEUENUM = 508,
    BYPASS = 509,
    FANOUT = 510,
    DUP = 511,
    FWD = 512,
    NUMGEN = 513,
    INC = 514,
    MOD = 515,
    OFFSET = 516,
    JHASH = 517,
    SYMHASH = 518,
    SEED = 519,
    POSITION = 520,
    COMMENT = 521,
    XML = 522,
    JSON = 523,
    VM = 524,
    NOTRACK = 525,
    EXISTS = 526,
    MISSING = 527,
    EXTHDR = 528
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
#define IMPORT 313
#define EXPORT 314
#define MONITOR 315
#define ALL 316
#define ACCEPT 317
#define DROP 318
#define CONTINUE 319
#define JUMP 320
#define GOTO 321
#define RETURN 322
#define TO 323
#define CONSTANT 324
#define INTERVAL 325
#define AUTOMERGE 326
#define TIMEOUT 327
#define GC_INTERVAL 328
#define ELEMENTS 329
#define POLICY 330
#define MEMORY 331
#define PERFORMANCE 332
#define SIZE 333
#define FLOW 334
#define METER 335
#define METERS 336
#define NUM 337
#define STRING 338
#define QUOTED_STRING 339
#define ASTERISK_STRING 340
#define LL_HDR 341
#define NETWORK_HDR 342
#define TRANSPORT_HDR 343
#define BRIDGE 344
#define ETHER 345
#define SADDR 346
#define DADDR 347
#define TYPE 348
#define VLAN 349
#define ID 350
#define CFI 351
#define PCP 352
#define ARP 353
#define HTYPE 354
#define PTYPE 355
#define HLEN 356
#define PLEN 357
#define OPERATION 358
#define IP 359
#define HDRVERSION 360
#define HDRLENGTH 361
#define DSCP 362
#define ECN 363
#define LENGTH 364
#define FRAG_OFF 365
#define TTL 366
#define PROTOCOL 367
#define CHECKSUM 368
#define ICMP 369
#define CODE 370
#define SEQUENCE 371
#define GATEWAY 372
#define MTU 373
#define OPTIONS 374
#define IP6 375
#define PRIORITY 376
#define FLOWLABEL 377
#define NEXTHDR 378
#define HOPLIMIT 379
#define ICMP6 380
#define PPTR 381
#define MAXDELAY 382
#define AH 383
#define RESERVED 384
#define SPI 385
#define ESP 386
#define COMP 387
#define FLAGS 388
#define CPI 389
#define UDP 390
#define SPORT 391
#define DPORT 392
#define UDPLITE 393
#define CSUMCOV 394
#define TCP 395
#define ACKSEQ 396
#define DOFF 397
#define WINDOW 398
#define URGPTR 399
#define OPTION 400
#define ECHO 401
#define EOL 402
#define MAXSEG 403
#define NOOP 404
#define SACK 405
#define SACK0 406
#define SACK1 407
#define SACK2 408
#define SACK3 409
#define SACK_PERMITTED 410
#define TIMESTAMP 411
#define KIND 412
#define COUNT 413
#define LEFT 414
#define RIGHT 415
#define TSVAL 416
#define TSECR 417
#define DCCP 418
#define SCTP 419
#define VTAG 420
#define RT 421
#define RT0 422
#define RT2 423
#define SEG_LEFT 424
#define ADDR 425
#define HBH 426
#define FRAG 427
#define RESERVED2 428
#define MORE_FRAGMENTS 429
#define DST 430
#define MH 431
#define META 432
#define MARK 433
#define IIF 434
#define IIFNAME 435
#define IIFTYPE 436
#define OIF 437
#define OIFNAME 438
#define OIFTYPE 439
#define SKUID 440
#define SKGID 441
#define NFTRACE 442
#define RTCLASSID 443
#define IBRIPORT 444
#define OBRIPORT 445
#define PKTTYPE 446
#define CPU 447
#define IIFGROUP 448
#define OIFGROUP 449
#define CGROUP 450
#define CLASSID 451
#define NEXTHOP 452
#define CT 453
#define L3PROTOCOL 454
#define PROTO_SRC 455
#define PROTO_DST 456
#define ZONE 457
#define DIRECTION 458
#define EVENT 459
#define EXPIRATION 460
#define HELPER 461
#define LABEL 462
#define STATE 463
#define STATUS 464
#define ORIGINAL 465
#define REPLY 466
#define COUNTER 467
#define NAME 468
#define PACKETS 469
#define BYTES 470
#define AVGPKT 471
#define COUNTERS 472
#define QUOTAS 473
#define LIMITS 474
#define HELPERS 475
#define LOG 476
#define PREFIX 477
#define GROUP 478
#define SNAPLEN 479
#define QUEUE_THRESHOLD 480
#define LEVEL 481
#define LIMIT 482
#define RATE 483
#define BURST 484
#define OVER 485
#define UNTIL 486
#define QUOTA 487
#define USED 488
#define NANOSECOND 489
#define MICROSECOND 490
#define MILLISECOND 491
#define SECOND 492
#define MINUTE 493
#define HOUR 494
#define DAY 495
#define WEEK 496
#define _REJECT 497
#define WITH 498
#define ICMPX 499
#define SNAT 500
#define DNAT 501
#define MASQUERADE 502
#define REDIRECT 503
#define RANDOM 504
#define FULLY_RANDOM 505
#define PERSISTENT 506
#define QUEUE 507
#define QUEUENUM 508
#define BYPASS 509
#define FANOUT 510
#define DUP 511
#define FWD 512
#define NUMGEN 513
#define INC 514
#define MOD 515
#define OFFSET 516
#define JHASH 517
#define SYMHASH 518
#define SEED 519
#define POSITION 520
#define COMMENT 521
#define XML 522
#define JSON 523
#define VM 524
#define NOTRACK 525
#define EXISTS 526
#define MISSING 527
#define EXTHDR 528

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

#line 787 "parser_bison.c" /* yacc.c:355  */
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

#line 817 "parser_bison.c" /* yacc.c:358  */

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
#define YYLAST   4637

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  283
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  276
/* YYNRULES -- Number of rules.  */
#define YYNRULES  844
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1289

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   528

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   278,     2,     2,     2,
     279,   280,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   274,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   281,     2,   282,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   275,   277,   276,     2,     2,     2,     2,
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
     265,   266,   267,   268,   269,   270,   271,   272,   273
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   716,   716,   717,   735,   736,   739,   740,   743,   751,
     765,   773,   774,   775,   776,   808,   809,   810,   811,   812,
     813,   814,   815,   816,   817,   818,   819,   820,   821,   824,
     828,   835,   839,   847,   851,   855,   862,   869,   873,   882,
     886,   890,   895,   901,   907,   911,   918,   922,   930,   937,
     944,   948,   957,   961,   965,   969,   975,   981,   985,   989,
     993,   997,  1001,  1005,  1009,  1013,  1017,  1023,  1027,  1031,
    1035,  1039,  1043,  1047,  1051,  1055,  1059,  1063,  1067,  1071,
    1075,  1079,  1083,  1087,  1091,  1095,  1099,  1103,  1107,  1111,
    1115,  1119,  1125,  1129,  1133,  1137,  1141,  1145,  1151,  1155,
    1159,  1163,  1167,  1171,  1175,  1181,  1188,  1194,  1200,  1203,
    1209,  1215,  1218,  1227,  1228,  1231,  1232,  1233,  1234,  1235,
    1236,  1237,  1238,  1241,  1242,  1243,  1246,  1247,  1250,  1259,
    1265,  1279,  1280,  1281,  1282,  1283,  1294,  1304,  1314,  1325,
    1336,  1345,  1359,  1365,  1366,  1367,  1368,  1369,  1370,  1378,
    1383,  1384,  1385,  1386,  1391,  1396,  1401,  1406,  1411,  1416,
    1419,  1420,  1423,  1427,  1430,  1431,  1432,  1436,  1441,  1442,
    1443,  1444,  1455,  1464,  1473,  1482,  1487,  1492,  1495,  1499,
    1505,  1506,  1509,  1523,  1524,  1544,  1549,  1550,  1551,  1552,
    1559,  1560,  1561,  1562,  1569,  1570,  1571,  1572,  1578,  1579,
    1580,  1581,  1588,  1589,  1590,  1591,  1592,  1595,  1623,  1624,
    1627,  1628,  1631,  1642,  1643,  1646,  1649,  1650,  1651,  1654,
    1669,  1670,  1673,  1674,  1675,  1676,  1677,  1678,  1681,  1689,
    1696,  1703,  1710,  1717,  1724,  1731,  1739,  1747,  1751,  1758,
    1765,  1777,  1781,  1788,  1792,  1798,  1810,  1816,  1823,  1824,
    1825,  1826,  1827,  1828,  1829,  1830,  1831,  1832,  1833,  1834,
    1835,  1836,  1837,  1838,  1839,  1840,  1843,  1847,  1853,  1859,
    1864,  1873,  1878,  1883,  1886,  1892,  1893,  1895,  1899,  1907,
    1911,  1914,  1918,  1924,  1925,  1928,  1934,  1938,  1941,  1946,
    1951,  1956,  1961,  1966,  1972,  2000,  2004,  2008,  2012,  2016,
    2022,  2026,  2029,  2033,  2039,  2048,  2067,  2075,  2076,  2077,
    2080,  2081,  2084,  2085,  2100,  2116,  2124,  2125,  2126,  2129,
    2130,  2131,  2132,  2147,  2148,  2149,  2150,  2151,  2154,  2157,
    2164,  2168,  2179,  2190,  2200,  2206,  2209,  2214,  2221,  2222,
    2223,  2224,  2225,  2226,  2227,  2228,  2229,  2230,  2233,  2234,
    2238,  2244,  2245,  2251,  2252,  2258,  2259,  2265,  2268,  2269,
    2288,  2289,  2292,  2296,  2299,  2305,  2311,  2322,  2323,  2324,
    2327,  2328,  2329,  2332,  2336,  2340,  2345,  2350,  2354,  2358,
    2364,  2365,  2368,  2371,  2375,  2380,  2386,  2387,  2390,  2393,
    2397,  2401,  2405,  2410,  2417,  2422,  2430,  2437,  2438,  2444,
    2445,  2446,  2449,  2450,  2453,  2459,  2463,  2466,  2471,  2477,
    2478,  2484,  2485,  2488,  2489,  2492,  2498,  2507,  2508,  2511,
    2518,  2521,  2527,  2531,  2534,  2540,  2550,  2556,  2573,  2574,
    2581,  2590,  2601,  2602,  2603,  2604,  2605,  2606,  2607,  2608,
    2609,  2610,  2611,  2612,  2615,  2638,  2639,  2640,  2643,  2644,
    2645,  2646,  2647,  2650,  2654,  2657,  2658,  2662,  2668,  2669,
    2675,  2676,  2682,  2683,  2689,  2692,  2693,  2712,  2718,  2724,
    2735,  2736,  2737,  2740,  2746,  2747,  2748,  2751,  2758,  2763,
    2768,  2771,  2775,  2779,  2785,  2786,  2793,  2799,  2800,  2803,
    2809,  2813,  2816,  2820,  2826,  2827,  2830,  2831,  2834,  2835,
    2838,  2849,  2857,  2878,  2886,  2889,  2890,  2893,  2908,  2915,
    2920,  2931,  2953,  2961,  2965,  2969,  2973,  2979,  2985,  2993,
    2994,  2995,  2998,  2999,  3003,  3009,  3010,  3016,  3017,  3023,
    3024,  3030,  3033,  3034,  3053,  3054,  3057,  3065,  3066,  3067,
    3068,  3069,  3070,  3071,  3072,  3073,  3074,  3075,  3076,  3079,
    3080,  3081,  3082,  3083,  3090,  3097,  3104,  3111,  3118,  3125,
    3132,  3139,  3146,  3153,  3162,  3163,  3164,  3165,  3166,  3167,
    3170,  3174,  3178,  3182,  3186,  3190,  3196,  3200,  3204,  3219,
    3220,  3223,  3224,  3225,  3226,  3229,  3230,  3231,  3232,  3233,
    3234,  3235,  3236,  3237,  3238,  3239,  3240,  3241,  3242,  3243,
    3244,  3245,  3246,  3249,  3253,  3257,  3271,  3277,  3278,  3281,
    3282,  3285,  3291,  3296,  3301,  3307,  3308,  3311,  3315,  3335,
    3336,  3337,  3340,  3344,  3348,  3354,  3355,  3358,  3359,  3360,
    3361,  3362,  3363,  3364,  3365,  3366,  3367,  3368,  3369,  3370,
    3371,  3372,  3375,  3376,  3377,  3378,  3379,  3380,  3381,  3384,
    3385,  3388,  3389,  3392,  3393,  3394,  3395,  3398,  3399,  3402,
    3408,  3416,  3429,  3435,  3444,  3445,  3446,  3447,  3448,  3449,
    3450,  3451,  3452,  3453,  3454,  3455,  3456,  3457,  3458,  3459,
    3462,  3472,  3473,  3474,  3477,  3483,  3484,  3485,  3488,  3494,
    3495,  3496,  3497,  3500,  3506,  3507,  3508,  3509,  3510,  3513,
    3519,  3520,  3521,  3522,  3523,  3524,  3525,  3526,  3527,  3528,
    3529,  3530,  3533,  3539,  3540,  3541,  3542,  3543,  3544,  3545,
    3548,  3554,  3555,  3556,  3557,  3558,  3559,  3560,  3561,  3562,
    3564,  3570,  3571,  3572,  3573,  3574,  3575,  3576,  3577,  3580,
    3586,  3587,  3588,  3589,  3590,  3593,  3599,  3600,  3603,  3609,
    3610,  3611,  3614,  3620,  3621,  3622,  3623,  3626,  3632,  3633,
    3634,  3635,  3638,  3642,  3646,  3653,  3654,  3655,  3656,  3657,
    3658,  3659,  3660,  3661,  3662,  3665,  3666,  3667,  3668,  3669,
    3670,  3671,  3672,  3673,  3674,  3675,  3676,  3679,  3680,  3681,
    3682,  3683,  3684,  3685,  3686,  3689,  3695,  3696,  3697,  3700,
    3706,  3707,  3708,  3709,  3712,  3713,  3714,  3715,  3716,  3717,
    3718,  3721,  3727,  3728,  3731,  3737,  3738,  3739,  3740,  3743,
    3749,  3755,  3761,  3764,  3770,  3771,  3772,  3773,  3774,  3775,
    3778,  3784,  3785,  3788,  3794,  3795,  3796,  3797,  3798,  3801,
    3815,  3816,  3817,  3818,  3819
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
  "\"rename\"", "\"describe\"", "\"import\"", "\"export\"", "\"monitor\"",
  "\"all\"", "\"accept\"", "\"drop\"", "\"continue\"", "\"jump\"",
  "\"goto\"", "\"return\"", "\"to\"", "\"constant\"", "\"interval\"",
  "\"auto-merge\"", "\"timeout\"", "\"gc-interval\"", "\"elements\"",
  "\"policy\"", "\"memory\"", "\"performance\"", "\"size\"", "\"flow\"",
  "\"meter\"", "\"meters\"", "\"number\"", "\"string\"",
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
     525,   526,   527,   528,    61,   123,   125,   124,    36,    40,
      41,    91,    93
};
# endif

#define YYPACT_NINF -1049

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1049)))

#define YYTABLE_NINF -659

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1049,  4405, -1049,    82, -1049, -1049,    95,    40,   422,   422,
     422,   422,   422,   422, -1049, -1049,  1719,   117,   800,   177,
     413,  1497,   630,   736,   195,  3783,    38,   134,   150, -1049,
   -1049, -1049, -1049,    35,   422,   422,   422, -1049, -1049, -1049,
     550, -1049,    40, -1049,    40,    17,  3482, -1049,    82, -1049,
      -9,    18,    25,  3482,    40, -1049,  -153, -1049, -1049,   422,
   -1049,   422,   422,   422,   422,   422,   112,   422,   422,   422,
   -1049,   422, -1049,   422,   422,   422,   422,   422,   422,   123,
     422,   422,   422, -1049,   422,   422,   422,   422,   768,   422,
     422,   422,   422,   461,   422,   422,    53,   422,   910,  1004,
    1024,   422,   422, -1049,   422,  1107,  1285,   422, -1049,   422,
     422,   422,   422,   422,   257,   422, -1049,   422, -1049,   506,
     381, -1049, -1049, -1049, -1049,   524,   709,   596,  1510,   867,
    1112,   638,   735,   133,   237,   425,   371,  1338,   142,   204,
     377,   155,   174,    59,   489,    78,   485,  2255, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049,  1755,   141,  3664,    88,
     239,    40,  3783, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049,   109, -1049, -1049,    89, -1049, -1049,   109, -1049,
   -1049, -1049, -1049, -1049,   734,   422,    40,   153,   165,   -56,
   -1049, -1049, -1049, -1049,   322, -1049,   465, -1049, -1049, -1049,
      40,    40, -1049, -1049,    40,  2375,  1755,   185, -1049,    63,
     103, -1049, -1049, -1049, -1049, -1049, -1049,   344,   350, -1049,
     424, -1049,   183,  3482, -1049, -1049, -1049, -1049,   315, -1049,
     292, -1049, -1049, -1049,   222, -1049,  2211, -1049,   104, -1049,
     135, -1049, -1049, -1049,   541, -1049, -1049,   440, -1049, -1049,
   -1049,   528,   459,   468,   219, -1049,   213, -1049,  2808, -1049,
   -1049, -1049,   464, -1049, -1049, -1049,   484, -1049,  3224,   224,
     261, -1049, -1049,   264, -1049, -1049, -1049,   272,   543,  3482,
      18,    25, -1049,  -153, -1049,   422,   153,   165,   -56,  3482,
   -1049, -1049, -1049, -1049,  -153, -1049, -1049,   422, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049,   422, -1049, -1049, -1049,
   -1049, -1049,   422,   422, -1049, -1049,   535,   422, -1049,   422,
   -1049,   422, -1049,   422, -1049, -1049, -1049, -1049,   422, -1049,
     422, -1049, -1049, -1049, -1049, -1049, -1049, -1049,   422, -1049,
      40, -1049, -1049, -1049, -1049,   581, -1049, -1049, -1049, -1049,
   -1049,   588,    68, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049,  1283, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049,   -41, -1049, -1049,   323, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049,  1643, -1049, -1049, -1049, -1049,
     360,    74,   363,   544, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049,   330, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049,   592, -1049, -1049,   546, -1049, -1049,   370, -1049,
   -1049, -1049, -1049,   552, -1049, -1049, -1049, -1049, -1049,  3783,
   -1049, -1049,   364,   603,   636,  1643,   650,  3041,  3041,   370,
    3041,   583,  3041,  3664, -1049,  3224,    33, -1049,   784, -1049,
   -1049,   648,   652,   315, -1049,    11,   784,   727,   728,   748,
     784,   292, -1049,    13, -1049,  3041, -1049, -1049,  2408,   524,
     709,   596,  1510, -1049,  1112,   309, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049,   654,   774,   814,   558,   434,   126,
   -1049, -1049, -1049, -1049, -1049,   813,   627,   827, -1049, -1049,
   -1049,   830, -1049, -1049, -1049, -1049, -1049,   837,   839, -1049,
     844, -1049, -1049, -1049, -1049,   843, -1049,  2605, -1049,   843,
    3041, -1049, -1049,   541, -1049,   845, -1049,    40,    24, -1049,
    3783,  3783,  3783,  3783,  3783,  3783,    23,  3224, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049,    40, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,   849,
   -1049,   662,   853,   855,   594,   316,   871, -1049, -1049, -1049,
    2896,  3041,  3041,    82,   849, -1049, -1049, -1049, -1049, -1049,
     799, -1049, -1049,   607,   611,   614, -1049,   616, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,   422, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049,   810,   381, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049,   557, -1049,   812, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049,   589, -1049,   820,
     824,   646, -1049, -1049, -1049, -1049,   637,   698, -1049, -1049,
     832,   -20,    46,   -19,   914,  3783,  3041,  3041,   885,  3041,
   -1049, -1049,   842, -1049,   -20,   895, -1049, -1049,   424,   686,
     -19, -1049,   533,   871,   424, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049,   815,   278, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049,   838,   846,   878,   850, -1049,  3041,   933,
    3902,  4175,  3902,  3902,  3902,   860,  3902,  3902,   202,  3041,
     843,  1419,  1419,  3041,   627,  3041,   627, -1049, -1049,   448,
   -1049,  3783, -1049, -1049, -1049,   528,   459,   468, -1049,    40,
     424, -1049, -1049,  4175,  4175,  4175,  4175,  4175,  4175,  4175,
     862,  4175,  4175,  3224, -1049, -1049, -1049, -1049,   228,  1608,
     416,   131, -1049, -1049, -1049, -1049, -1049,   673, -1049, -1049,
     944, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049,   672, -1049, -1049, -1049,   646,   200,   875, -1049, -1049,
     876,   108, -1049, -1049,   731, -1049,   882, -1049,   -19, -1049,
     914,  3482,   -19, -1049, -1049,  3041, -1049,   119,   731,  3041,
   -1049,  4087, -1049,   -19,  3224, -1049, -1049, -1049, -1049,   954,
   -1049,   884,   886, -1049,   887, -1049,  3041, -1049, -1049, -1049,
   -1049,   654,   774,   814, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049,   627, -1049,   627,   843, -1049,
    3482, -1049,  3312,    43, -1049, -1049, -1049, -1049,   662,   853,
     855, -1049, -1049, -1049, -1049,   691,    40,    40,    40,   893,
     771,    40,    40,    40, -1049, -1049, -1049,    82,   643,   903,
   -1049, -1049, -1049,    82,    82,    82, -1049,   882,   882,   704,
     651,   906,    60,   579, -1049, -1049, -1049,    82,   715,    60,
     579, -1049, -1049, -1049,    82,  1141,  1810,   497,   288, -1049,
     908, -1049, -1049,   918, -1049, -1049,    70, -1049,   679,   772,
     921, -1049, -1049, -1049, -1049,   729,   -19, -1049,   679,   772,
   -1049, -1049,   424, -1049,   871, -1049,   278, -1049, -1049, -1049,
   -1049,   843,   843,   737,  1002,   424, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049,    40, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049,   986, -1049, -1049, -1049,    82,    82,  -153,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
     623, -1049, -1049, -1049, -1049,   573, -1049, -1049,  -153,   477,
     573, -1049, -1049, -1049, -1049, -1049,   143, -1049,   646,   938,
     422,    82, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
     772,   941, -1049,   -20, -1049,   772, -1049, -1049, -1049, -1049,
     930,  3312, -1049,   750,   751,   758, -1049,   759,   761,   762,
     955, -1049, -1049, -1049,    60, -1049,   579, -1049, -1049,   355,
   -1049,    82, -1049,   929,    82, -1049, -1049,    29, -1049, -1049,
     424, -1049, -1049, -1049,   767, -1049, -1049, -1049,  1013, -1049,
   -1049,    82,    82,    82,   623, -1049,    75, -1049, -1049, -1049,
   -1049, -1049,  2012,   946,   531, -1049,    83,   431,   193,   961,
     924, -1049, -1049, -1049, -1049, -1049, -1049,    82,    82,    82,
      82,   346,    82, -1049, -1049, -1049,    82, -1049, -1049, -1049,
      82, -1049, -1049, -1049, -1049,    91, -1049, -1049, -1049, -1049,
      82, -1049, -1049, -1049,   965, -1049, -1049, -1049, -1049
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,   220,   220,
     220,   220,   220,   220,   224,   227,   220,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   226,
     225,   222,   223,     0,   220,   220,   220,    12,    11,     3,
       0,    15,     0,   221,     0,   237,     0,    10,     0,   215,
       0,    29,    31,     0,     0,   149,     0,   167,    16,   220,
      17,   220,   220,   220,   220,   220,     0,   220,   220,   220,
      18,   220,    19,   220,   220,   220,   220,   220,   220,     0,
     220,   220,   220,    20,   220,   241,   220,   241,   241,   220,
     220,   241,   241,     0,   220,   241,     0,   220,   241,   241,
     241,   220,   220,    21,   220,   241,   241,   220,    22,   220,
     220,   220,   220,   241,     0,   220,    23,   220,    24,     0,
       0,   431,   216,   217,   218,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   585,   586,
     587,   588,   589,   590,   591,   592,   593,   594,   595,   596,
     597,   598,   599,   600,   601,   602,     0,     0,     0,     0,
       0,     0,     0,    28,   429,   428,   432,   433,   128,   442,
     437,   577,   440,   441,   438,   439,   434,   664,   665,   666,
     667,   668,   669,   670,   671,   672,   673,   674,   675,   676,
     677,   678,   679,   435,   804,   805,   806,   807,   808,   809,
     810,   436,     0,   126,   108,     0,    25,   107,     0,   111,
      26,   110,   114,    27,   115,   220,     0,    38,     0,   309,
      14,    13,   228,   229,     0,   238,     0,   570,   571,   572,
       0,     0,   575,   421,     0,     0,     0,   277,   285,     0,
     309,   329,   336,   337,   382,   388,   404,     0,     0,   606,
       7,    34,   243,   245,   246,   248,   267,   251,   275,   254,
     283,   255,   256,   257,   330,   258,     0,   261,   381,   262,
     387,   263,   264,   259,   402,   265,   250,     0,   420,   249,
     455,   458,   460,   462,   464,   465,   474,   476,     0,   475,
     426,   266,   577,   253,   260,   252,   434,     8,     0,     0,
       0,    33,   231,     0,    37,   161,   160,     0,     0,     0,
      44,    46,   149,     0,   167,   220,    51,     0,   309,     0,
      57,    58,    59,    60,     0,    61,   504,   220,    63,    66,
      64,    67,   242,    68,    69,    70,   220,    71,    73,    89,
      88,    83,   220,   241,    87,    86,     0,   220,    76,   220,
      74,   220,    77,   220,    80,    82,    79,    94,   220,    92,
     220,    95,    97,    98,    99,   100,   101,   104,   220,   103,
       0,   681,   682,   683,   430,     0,   448,   449,   450,   451,
     452,   454,     0,   685,   686,   687,   684,   692,   689,   690,
     691,   688,   694,   695,   696,   697,   698,   693,   710,   711,
     705,   700,   701,   702,   703,   704,   706,   707,   708,   709,
     699,   713,   716,   715,   714,   717,   718,   719,   712,   728,
     729,   721,   722,   723,   725,   724,   726,   727,   720,   731,
     736,   733,   732,   737,   735,   734,   738,   730,   741,   744,
     740,   742,   743,   739,   747,   746,   745,   749,   750,   751,
     748,   755,   756,   753,   754,   752,   761,   758,   759,   760,
     757,   773,   767,   770,   771,   765,   766,   768,   769,   772,
     774,     0,   762,   798,   796,   797,   795,   803,   800,   801,
     802,   799,   817,   615,   816,   621,   616,   815,   818,   619,
     620,     0,   617,   814,     0,   819,   822,   821,   813,   812,
     811,   829,   826,   824,   825,   827,   828,   823,   832,   831,
     830,   836,   835,   838,   834,   837,   833,   578,   581,   582,
     583,   584,   576,   579,   580,   635,   636,   628,   629,   627,
     637,   638,   656,   631,   640,   633,   634,   639,   630,   632,
     625,   626,   654,   653,   655,     0,   622,   641,   610,   609,
       0,   474,     0,     0,   841,   840,   842,   843,   844,   839,
     427,     0,   106,   127,   109,   116,   117,   119,   118,   121,
     122,   120,   123,   509,   233,     0,   501,    39,   318,   512,
      42,   307,   308,     0,   503,    40,   236,   417,   418,     0,
     573,   574,     0,   578,   576,     0,   622,     0,     0,   318,
       0,     0,     0,     0,     6,     0,     0,   478,     0,   244,
     247,     0,     0,   276,   279,     0,     0,     0,     0,     0,
       0,   284,   286,     0,   328,     0,   366,   545,     0,   537,
     540,   541,   538,   544,   539,     0,   548,   546,   547,   543,
     542,   534,   535,   348,   351,   353,   355,   357,   358,   363,
     370,   367,   368,   369,   371,   373,   335,   338,   339,   536,
     340,   347,   341,   344,   345,   342,   343,     0,   372,   346,
       0,   399,   400,   401,   380,   385,   397,     0,   386,   391,
       0,   411,   412,   403,   405,   408,   409,     0,     0,   422,
       0,     0,     0,     0,     0,     0,     0,     0,   564,   565,
     566,   567,   568,   569,   469,     0,   537,   540,   541,   538,
     558,   539,   559,   557,   556,   560,   554,   555,   553,   561,
     562,   563,   549,   550,   470,   471,   472,   520,   521,   514,
     513,   525,   527,   529,   531,   532,   519,   551,   552,   522,
       0,     0,     0,     0,   499,   498,   131,   143,   150,   168,
       0,   239,    43,     0,     0,     0,    50,     0,   509,    52,
      55,    53,    56,    62,   509,    72,    85,    84,   220,    90,
      75,    78,    81,    93,    96,   102,   105,     0,     0,   447,
     445,   446,   444,   778,   785,   775,   777,   776,   780,   781,
     782,   783,   784,   779,   786,   764,   618,     0,   642,   643,
     649,   645,   650,   644,   646,   647,   623,     0,   648,     0,
       0,   607,   443,   125,   112,   124,     0,     0,   316,   317,
       0,     0,     0,   413,   415,     0,     0,     0,   648,     0,
     278,   306,     0,   315,     0,   394,   396,   495,     7,     7,
     487,   489,   532,   494,     7,   477,   240,   281,   282,   280,
     299,   298,     0,     0,   297,   293,   288,   289,   290,   291,
     294,   292,   287,     0,     0,     0,     0,   377,     0,   374,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     379,     0,     0,     0,     0,     0,   389,   407,   406,     0,
     424,     0,   423,   456,   457,   459,   461,   463,   466,     0,
       7,   268,   473,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   515,   604,   663,     9,     0,     0,
       0,     0,   235,   131,   143,   150,   168,     0,    65,    91,
       0,   453,   789,   788,   787,   790,   791,   792,   793,   794,
     763,     0,   651,   652,   624,   607,   607,     0,   614,   194,
       0,     0,   311,   310,   312,   416,     0,   493,   414,   490,
     486,     0,   484,   605,   603,     0,   661,     0,   312,     0,
     481,     0,   482,   488,   480,   479,   296,   302,   303,   295,
     301,     0,     0,   334,     0,   378,     0,   349,   338,   347,
     350,   352,   354,   356,   364,   365,   359,   362,   361,   360,
     375,   657,   658,   659,   660,   383,   398,   390,   392,   410,
       0,   270,     0,     0,   271,   518,   523,   524,   526,   528,
     530,   517,   467,   468,   533,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    30,   133,   132,     0,     0,     0,
      32,   145,   144,     0,     0,     0,   158,     0,     0,     0,
       0,     0,     0,     0,    35,   152,   151,     0,     0,     0,
       0,    36,   170,   169,     0,     0,     0,     0,     0,   194,
       0,   820,   611,     0,   613,   608,     0,   500,     0,   319,
       0,   502,   219,   492,   491,     0,   485,   662,     0,   319,
     314,   395,     7,   532,   496,   497,     0,   331,   332,   333,
     376,   384,   393,     0,     0,     7,   269,   516,   230,   142,
     232,   149,   167,   130,     0,   234,   185,   185,   185,   134,
     213,   214,   212,     0,   146,   147,   148,     0,     0,     0,
     181,   180,   178,   179,   202,   204,   205,   203,   206,   183,
       0,   182,   164,   165,   166,     0,   163,   159,     0,     0,
       0,   177,    45,    47,    48,    49,     0,   680,   607,     0,
       0,     0,   196,   195,   197,   323,   324,   325,   326,   327,
     319,     0,   511,     0,   425,   319,   305,   483,   300,   419,
       0,   273,   272,     0,     0,     0,   185,     0,     0,     0,
       0,   155,   156,   157,     0,   153,     0,   154,   176,     0,
     175,     0,   612,     0,     0,    41,   510,     0,   313,   304,
       7,   143,   150,   168,     0,   186,   198,   190,   211,   184,
     162,     0,     0,     0,     0,    54,     0,   508,   322,   320,
     321,   274,     0,     0,     0,   194,     0,     0,     0,     0,
       0,   172,   174,   173,   171,   506,   505,     0,     0,     0,
       0,     0,     0,   188,   187,   189,     0,   200,   199,   201,
       0,   192,   191,   193,   210,     0,   507,   135,   136,   137,
       0,   138,   141,   139,     0,   208,   207,   140,   209
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1049, -1049,    -1,  -789,     5, -1049, -1049,  1040, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049,     4, -1049,   740, -1049,   124,  -308,  -890,  -318,
    -894,  -313,    -8,  -145,  -310,  -888,  -893, -1049,  -141, -1001,
   -1048, -1049, -1049, -1022, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049,   139,  -152,  -321, -1049,   -76,  1281,   466, -1049,    30,
      26,  1343,  -926, -1049, -1049,    65,   992,   806,   555,     3,
   -1049, -1049,  -245, -1049, -1049, -1049, -1049,   -44, -1049, -1049,
   -1049,   449, -1049, -1049, -1049,   444, -1049, -1049, -1049,   -25,
   -1049,   840,  -808,   110, -1049,   478,  -913,    -6, -1049, -1049,
   -1049, -1049, -1049,  -709,   207,   212,   214, -1049,   215, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049,  -448, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049,  -260,   205, -1049, -1049,
   -1049,   411, -1049,   208, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049,   408, -1049, -1049,   -53,   577,   -18,     0, -1049, -1049,
   -1049,   321,   409,   407,   410, -1049,  -140,  -163, -1049, -1049,
   -1049,  -588, -1049,  -134,    22, -1049,   258,   216, -1049,  -964,
   -1049,  -783,  -865, -1049, -1049, -1049,  -130,   792,  -129,   795,
    1029, -1049, -1049,  -528,  -127,   802, -1049,   818,  -291,   211,
     218,   221, -1049,  -246,  -589, -1049,   396,   -94,  -619, -1049,
    -930,     8,   888, -1049,   -45, -1049,  -856, -1049,    20,    39,
   -1049,    45,   629,    58,   894,   897, -1049, -1049, -1049,  -465,
     -91, -1049, -1049, -1049,    80, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049, -1049,
   -1049, -1049, -1049, -1049, -1049, -1049
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,  1051,   615,  1052,    39,    40,    41,    60,    70,
      72,    83,   103,   108,   116,   118,   216,   220,   223,   224,
     582,   824,   217,   173,   309,  1047,   928,   310,   929,   313,
     930,   314,  1155,  1156,   317,   931,  1067,  1142,  1149,  1150,
    1197,  1246,  1248,  1086,  1247,  1151,  1053,  1286,  1250,  1054,
    1132,  1125,   174,  1093,    42,    43,   226,    45,  1119,    55,
    1121,   227,  1126,   761,   235,    46,   319,   967,   343,  1055,
     262,   263,   264,   265,   266,   911,  1023,  1024,   267,   268,
     623,   624,   269,   270,   631,   632,   871,   865,   989,   990,
     271,   593,   964,  1091,   272,   830,  1182,  1180,   273,   274,
     634,   275,   276,   653,   654,   655,   656,   657,   658,   659,
    1007,   660,   661,   662,   663,   664,   665,   666,   277,   278,
     684,   279,   280,   688,   281,   282,   685,   686,   283,   284,
     693,   694,   695,   696,   832,   833,   285,   599,   286,   287,
     698,   699,   288,   289,   175,   176,   668,   290,   179,   792,
     391,   392,   291,   292,   293,   294,   295,   296,   734,   735,
     736,   737,   297,   298,   299,   616,   617,   971,   972,   849,
     850,   968,   969,   851,  1102,   753,   586,   587,   594,   595,
     337,  1257,  1174,   826,   589,   590,   300,   739,   740,   741,
     742,   743,   744,   852,   746,   669,   670,   671,   749,   750,
     301,   672,   532,   533,   181,   303,   958,   560,   673,   674,
     501,   675,   502,   676,   555,   556,   816,   817,   954,   557,
     677,   678,   304,   305,   679,   187,   385,   188,   396,   189,
     401,   190,   407,   191,   420,   192,   428,   193,   438,   194,
     447,   195,   453,   196,   456,   197,   460,   198,   465,   199,
     470,   200,   482,   805,   950,   201,   486,   202,   491,   203,
     204,   510,   205,   503,   206,   505,   207,   507,   208,   517,
     209,   520,   210,   526,   211,   569
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,   302,    47,   315,   765,   561,    38,   177,   302,   342,
     766,   342,   342,   764,   767,   342,   342,   755,   620,   342,
     689,   773,   342,   342,   342,   178,   853,   847,   177,   342,
     342,   221,   571,   180,   562,   177,   978,   342,  1074,   231,
     854,  1077,    56,    57,  1076,   182,   909,   307,  1078,   261,
    1115,  1105,   745,   966,   180,   697,   311,  1166,  1114,   980,
     982,   180,   745,   962,   183,   984,   182,   983,  1159,   715,
     184,     3,   860,   182,     4,    53,     5,   495,   316,  1198,
    1199,   212,   705,   185,     3,   183,     4,     4,     5,     5,
     818,   184,   183,   322,   323,   324,     6,     7,   184,  1082,
    1084,   861,   534,  1094,   185,   186,   333,   334,   335,     6,
       7,   185,  1238,  1284,   707,   862,  1127,  1128,  1094,   348,
     349,  1022,   260,    49,   354,   171,   306,   873,  1088,   122,
     123,   124,     3,   306,   887,     4,   329,     5,   874,  1098,
     838,   375,   376,  1144,     3,   379,    50,     4,  1224,     5,
     177,   863,    59,   875,   177,   499,   500,     6,     7,   840,
     841,   789,   843,  1169,   845,   508,   888,  1145,  1146,     6,
       7,   997,   680,  1285,   591,   592,   180,   218,  1006,    48,
     180,   232,   509,   233,   518,  1074,  1186,   877,   182,  1096,
     879,  1089,   182,   312,     3,   963,   864,     4,  1196,     5,
     534,   519,  1099,   687,   748,  1068,  1060,   183,  1234,  1061,
    1255,   183,    71,   184,   748,  1256,   572,   184,   302,     6,
       7,   705,   574,  1261,  1069,   715,   185,  1114,   117,     3,
     185,  1094,     4,   222,     5,   483,  1169,   706,  1147,   896,
     937,   225,   897,  1239,  1240,   177,   938,   618,   186,   454,
     790,   791,   186,   707,     6,     7,  1148,   876,   384,   336,
    1220,  1036,  1000,   455,  1070,   308,  1037,  1216,  1038,  1170,
     315,   180,  1219,   356,   302,  -309,   608,   342,   484,   485,
     733,   315,   234,   182,   302,   122,   123,   124,   378,     3,
     733,   609,     4,  -129,     5,  1026,  1027,   585,   910,   901,
    -142,   177,   183,   925,   926,   213,   214,   215,   184,   855,
     570,   177,  1212,  1187,     6,     7,   610,   487,   325,  1116,
     738,   185,   762,   919,   171,   504,  1191,   180,  1243,   336,
     738,  1242,   772,   591,   592,  1244,   920,   180,   921,   182,
     488,   489,  1170,   306,   506,   316,  1171,     3,   563,   182,
       4,  1074,     5,   681,   682,   683,   316,   573,   183,  1262,
     457,  1039,  1068,  1060,   184,   584,  1061,   585,   183,   490,
     458,   459,     6,     7,   184,  1218,   213,   185,   215,   600,
     601,  1069,   776,   602,   681,   682,   683,   185,   973,   974,
     558,   976,  1104,   588,   987,   853,   847,   988,   607,   306,
     559,   213,   219,   215,   596,   564,   890,  1071,   785,   306,
     565,   566,   612,   493,   567,   568,   912,     3,   613,  1211,
       4,  1070,     5,   591,   592,   625,  1040,   495,   614,   496,
     995,  1241,     3,   853,   847,     4,   834,     5,  1144,  1169,
    1041,  1010,     6,     7,    73,  1015,    74,  1017,    75,   618,
     561,    76,    77,    78,   885,  1042,   886,     6,     7,   924,
    1043,   957,  1145,  1146,  1083,   633,   856,    14,    15,  1270,
     492,   697,   386,   387,   866,    52,   702,   260,   870,   846,
     171,   493,  1209,   494,   466,  1204,   703,  1056,  1057,  1058,
    1059,  1060,   352,   353,  1061,   495,   704,   496,     3,   756,
     497,     4,   751,     5,  1044,   499,   500,   467,   468,  1062,
     469,    29,   597,   598,   626,   627,   628,   629,   630,   786,
      30,   748,   752,     6,     7,   318,    31,  1097,   321,   621,
     622,  1101,     3,  1147,   461,     4,   757,     5,   462,   758,
     331,   318,    32,   700,   701,  1170,   498,   759,  1110,  1063,
     230,  1148,   344,   920,     4,   921,     5,     6,     7,   388,
     389,   463,   464,   390,  1165,   908,   778,  1231,  1056,  1057,
    1058,  1059,  1060,   499,   500,  1061,   374,     4,   521,     5,
    1206,   177,  1232,   380,   511,   760,   825,  1233,   787,    49,
    1062,   522,   381,   382,   383,   177,   788,   733,   523,   512,
     828,   829,   853,   847,   807,  1068,  1060,   180,   524,  1061,
     822,    79,   513,   748,   525,   393,   394,   395,   514,   182,
     819,   180,  1280,   820,  1069,    80,   821,     4,   827,     5,
    1063,  1204,  1035,   182,   831,   942,  1018,   848,   183,   835,
      81,   836,   345,   347,   184,    82,   350,   351,  1152,  1153,
     355,  1154,   183,   360,   362,   364,   748,   185,   184,   588,
     369,   371,   515,   516,  1070,   844,   943,  1025,   377,   880,
     881,   185,   970,  1031,   837,  1033,  1034,   914,   915,   186,
     952,   953,   177,   177,   177,   177,   177,   177,   839,   733,
     614,   981,  1064,   186,   747,   402,   403,   404,   405,   406,
     903,   904,   691,   692,   747,  1130,  1131,  1266,   180,   180,
     180,   180,   180,   180,   944,   945,   946,   947,   948,   949,
     182,   182,   182,   182,   182,   182,  1095,  1140,  1141,   738,
     857,   439,   733,   440,   858,  1103,  1137,  1138,   970,   183,
     183,   183,   183,   183,   183,   184,   184,   184,   184,   184,
     184,   441,   927,   442,   443,  1111,   444,  1112,   185,   185,
     185,   185,   185,   185,   445,   446,   575,   109,   576,   110,
     577,   578,   738,  1164,   111,  1113,   112,   579,   580,   113,
     186,   186,   186,   186,   186,   186,   999,   748,   999,   999,
     999,   882,   999,   999,   690,   691,   692,  1012,  1012,   346,
    1013,  1014,   397,  1194,   398,   399,   400,  1260,   581,   867,
     868,  1193,  1195,    14,    15,   114,   115,   177,   889,   748,
     748,   748,   748,   748,   748,   748,  1203,   748,   748,   748,
     869,    61,   883,    62,  -657,   884,   900,  -658,    63,    64,
      65,   448,   104,   180,   891,  1208,   892,   105,   106,   893,
     894,   449,   899,   667,   384,   182,   913,    29,   450,   213,
     823,   215,   107,   733,   451,   452,    30,   122,   123,   124,
     916,   918,    31,   917,   183,   732,   681,   682,   683,   922,
     184,   932,   933,   177,   302,   732,   934,   748,    32,   935,
     748,   936,   940,   185,   951,   733,   733,   733,   733,   733,
     733,   733,   955,   733,   733,   733,   956,   957,   777,   180,
    1009,   177,   959,   960,   961,   186,  1175,  1176,  1177,  1178,
    1179,   182,   705,   975,   977,   979,   302,  1045,   748,  1065,
    1072,   991,   993,  1046,   986,  1066,  1073,   180,   996,   992,
     183,   359,  1004,   994,  1032,   738,   184,     3,  1079,   182,
       4,  1080,     5,   177,  1081,    14,    15,  1085,  1087,   185,
     421,  1106,   422,   733,  1090,  1092,   733,  1107,   183,  1108,
    1109,  1117,     6,     7,   184,   302,  1123,  1124,  1139,   180,
     423,   186,   424,   425,   426,   427,  1133,   185,  1143,  1158,
    1167,   182,   237,   238,   239,   240,   241,   242,    66,    29,
    1168,  1181,   177,  1183,   733,  1184,   848,  1190,    30,   306,
     183,   747,    67,  1189,    31,  1200,   184,  1056,  1057,  1058,
    1059,  1060,  1213,  1217,  1061,  1221,  1222,    68,   180,   185,
      32,   302,    69,  1223,  1225,   361,  1226,  1227,  1228,  1062,
     182,  1236,  1245,  1249,  1274,  1275,  1129,  1288,  1021,    14,
      15,   306,  1134,  1135,  1136,   363,    58,  1075,   177,   183,
     763,  1230,  1160,  1229,  1122,   184,  1157,   332,   619,    14,
      15,  1192,   859,  1161,  1045,   872,  1065,  1072,   185,  1063,
    1046,  1188,  1066,  1073,   180,  1172,   315,   842,  1100,  1001,
     611,  1173,  1185,    29,  1214,  1002,   182,   748,  1003,  1016,
     306,  1005,    30,   747,   898,   315,   902,  1019,    31,   941,
     906,   905,   985,    29,   907,   183,  1265,  1020,   769,  1273,
    1269,   184,    30,   771,    32,   357,   754,  1028,    31,   770,
     806,     0,     0,   604,   185,  1029,  1201,  1202,   368,  1030,
     605,     0,     3,   606,    32,     4,   747,     5,     0,  1205,
       0,     0,    14,    15,  1207,     0,   306,     0,     0,  1210,
       0,   316,     0,     0,     0,  1172,     0,     6,     7,     0,
    1215,  1173,     0,   733,  1036,  1118,  1120,  1120,     0,  1037,
     316,  1038,     0,     0,   667,   667,     0,   667,     0,   667,
       0,     0,   732,     0,     0,     0,    29,   302,     0,     0,
       0,     0,     0,   429,   430,    30,     0,     0,     0,     0,
    1235,    31,   667,  1237,     0,   667,     0,   431,     0,   432,
     433,   434,  1259,     0,   177,     0,     0,    32,     0,     0,
    1251,  1252,  1253,  1254,   435,   436,   437,     0,     0,     0,
       0,     0,  1065,  1072,     0,  1263,  1267,  1271,  1066,  1073,
     180,  1264,  1268,  1272,     0,     0,  1276,  1277,  1278,  1279,
    1172,  1281,   182,     0,   667,  1282,  1173,   667,     0,  1283,
       0,     0,     0,     0,  1039,     0,     0,   747,     0,  1287,
       0,   183,    44,     0,   732,     0,     0,   184,     0,    51,
      44,    44,    54,    54,    54,     0,     0,    44,     0,     0,
     185,     0,     0,     0,     0,     0,     0,     0,     0,   747,
     747,   747,   747,   747,   747,   747,   370,   747,   747,   747,
       0,     0,   306,     0,     0,     0,     0,   732,   667,   667,
      14,    15,     0,     0,     0,     0,     0,     0,     0,  1040,
      44,     0,   320,    44,    54,    54,    54,     0,     0,     0,
       0,     0,    44,  1041,   330,    44,    44,    54,    54,    54,
       0,     0,     0,     0,     0,   341,     0,    44,  1042,     0,
      54,    54,     0,  1043,    29,    54,     0,   747,   228,   229,
     747,     0,     0,    30,     0,     0,     0,     0,     0,    31,
     373,    44,    54,    54,     0,     0,    54,     0,    44,     0,
       0,     0,     0,     0,     0,    32,     0,     0,     0,   965,
     326,   327,   328,   667,   667,     0,   667,  1162,   747,     0,
       0,     0,     0,   338,   339,   340,   793,     0,     0,   794,
     795,   796,   797,   798,   799,   800,   801,   802,   803,   804,
     358,     0,   715,     0,   365,   366,     0,   367,     0,     0,
     372,   471,     0,     0,   472,   667,     0,   998,   732,   998,
     998,   998,     0,   998,   998,  1008,   667,   473,  1011,  1011,
     667,   474,   667,   637,   475,   476,     0,     0,     0,   477,
     478,   479,   480,   481,     0,     0,     0,     0,     0,     0,
     732,   732,   732,   732,   732,   732,   732,     0,   732,   732,
     732,     0,   122,   123,   124,     0,     0,     0,     0,   716,
       0,     0,     0,   717,     0,     0,     0,   718,     0,     0,
       0,     0,     0,   719,     0,     0,     0,   643,    84,    85,
      86,    87,     0,     0,    88,    89,     0,    90,    91,   721,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   667,     0,     0,     0,   667,     0,   732,     0,
       0,   732,     0,     0,     0,     0,     0,     0,   583,     0,
       0,     0,     0,   667,     0,     0,    93,    94,    95,     0,
       0,     0,     0,     0,     0,     0,     0,   747,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   732,
       0,   408,   409,     0,     0,   410,     0,     0,     0,     3,
       0,     0,     4,     0,     5,   411,   412,   413,   414,   415,
     416,   417,   418,   419,     0,     0,   646,   775,     0,   647,
     648,   119,     0,    54,     6,     7,   120,     0,     0,     0,
     780,     0,   781,     0,   782,     0,   236,     0,     0,   783,
       0,   784,     0,     0,     0,     0,     0,     0,     0,    54,
       0,     0,     0,     0,   649,   650,     0,     0,   768,     0,
     237,   238,   239,   240,   241,   242,     0,     0,     0,     0,
     774,     0,     0,  1048,     0,     0,     0,   243,   244,     0,
     121,   122,   123,   124,     0,    96,     0,   171,   125,     0,
     779,  1049,   126,     0,     0,     0,   127,     0,     0,    97,
       0,     0,   128,     0,    98,    99,   100,     0,     0,     0,
       0,     0,   129,     0,   101,     0,     0,     0,   130,   102,
       0,     0,     0,   131,   808,   809,   132,     0,     0,   133,
     134,     0,     0,   135,     0,     0,   136,   810,   137,     0,
       8,     0,     9,     0,    10,   811,     0,    11,    12,    13,
       0,     0,     0,   812,    14,    15,     0,     0,   732,     0,
       0,   138,   139,     0,   140,   141,   142,     0,     0,   143,
     144,     0,     0,   145,   146,   245,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,     0,     0,   246,     0,    29,     0,
       0,     3,     0,     0,     4,     0,     5,    30,     0,     0,
     247,     0,     0,    31,     0,     0,     0,     0,     0,   248,
       0,     0,     0,   119,     0,   249,     6,     7,   120,    32,
     250,     0,   813,   814,   815,   542,   535,   536,   236,     0,
     251,     0,     0,   252,   253,   254,   255,   552,   553,   554,
     256,     0,     0,     0,   257,   258,   167,   537,     0,     0,
     168,   169,   237,   238,   239,   240,   241,   242,   259,     0,
       0,   170,     0,   260,  1050,  1048,   171,   172,     0,   243,
     244,     0,   121,   122,   123,   124,     0,     0,     0,     0,
     125,     0,     0,  1049,   126,     0,     0,     0,   127,     0,
       0,     0,     0,     0,   128,     0,     0,    33,     0,     0,
       0,     0,     0,     0,   129,     0,     0,     0,     0,     0,
     130,    34,     0,   538,     0,   131,     0,     0,   132,     0,
       0,   133,   134,     0,     0,   135,    35,     0,   136,     0,
     137,    36,     0,     0,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,     0,     0,   552,
     553,   554,     0,   138,   139,     0,   140,   141,   142,     0,
       0,   143,   144,     0,     0,   145,   146,   245,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,     0,     0,   246,     0,
       0,     0,     0,     3,     0,     0,     4,     0,     5,     0,
       0,     0,   247,     0,     0,     0,     0,     0,     0,     0,
       0,   248,     0,     0,     0,   119,     0,   249,     6,     7,
     120,     0,   250,     0,     0,     0,     0,     0,     0,     0,
     236,     0,   251,     0,     0,   252,   253,   254,   255,   939,
       0,     0,   256,     0,     0,     0,   257,   258,   167,     0,
       0,     0,   168,   169,   237,   238,   239,   240,   241,   242,
     259,     0,     0,   170,     0,   260,  1163,  1048,   171,   172,
       0,   243,   244,     0,   121,   122,   123,   124,     0,     0,
       0,     0,   125,     0,     0,  1049,   126,     0,     0,     0,
     127,     0,     0,     0,     0,     0,   128,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,     0,     0,     0,
       0,     0,   130,     0,     0,     0,     0,   131,     0,     0,
     132,     0,     0,   133,   134,     0,     0,   135,     0,     0,
     136,     0,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,     0,   140,   141,
     142,     0,     0,   143,   144,     0,     0,   145,   146,   245,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,     0,     0,
     246,     0,     0,     0,     0,     0,   635,     0,     0,     0,
       0,     0,     0,     0,   247,     0,     0,     0,     0,     0,
       0,     0,   636,   248,   119,     0,     0,     0,     0,   249,
       0,     0,     0,     0,   250,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   251,     0,     0,   252,   253,   254,
     255,     0,     0,     0,   256,   637,     0,     0,   257,   258,
     167,     0,     0,     0,   168,   169,     0,     0,     0,   638,
       0,     0,   259,     0,     0,   170,     0,   260,  1258,     0,
     171,   172,     0,   121,   122,   123,   124,     0,     0,     0,
       0,   639,     0,     0,     0,   640,     0,     0,     0,   641,
       0,     0,     0,     0,     0,   642,     0,     0,     0,   643,
       0,     0,     0,     0,     0,   129,     0,     0,     0,     0,
       0,   644,     0,     0,     0,     0,   131,     0,   527,   132,
       0,     0,   133,   134,     0,     0,   135,     0,     0,   136,
       0,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   528,     0,     0,   529,     0,     0,
       0,     0,     0,     0,   138,   139,   530,   645,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,     0,     0,   166,
       0,     0,     0,   878,     0,     0,     0,     0,   646,     0,
       0,   647,   648,     0,     0,     0,     0,     0,     0,   636,
       0,   119,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,     0,     0,     0,     0,     0,   649,   650,   603,     0,
       0,     0,   637,     0,     0,     0,     0,     0,     0,   167,
       0,     0,     0,   168,   169,     0,     0,     0,     0,     0,
       0,     0,   651,   652,   528,     0,     0,   529,     0,   171,
     121,   122,   123,   124,     0,     0,   530,     0,   639,     0,
       0,     0,   640,     0,   531,     0,   641,     0,     0,     0,
       0,     0,   642,     0,     0,     0,   643,     0,     0,     0,
       0,     0,   129,     0,     0,     0,     0,     0,   644,     0,
       0,     0,     0,   131,     0,     0,   132,     0,     0,   133,
     134,     0,     0,   135,     0,     0,   136,     0,   137,     0,
       0,     0,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   138,   139,     0,   645,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,     0,     0,   166,     0,     0,     0,
     895,     0,     0,     0,     0,   646,     0,     0,   647,   648,
       0,     0,     0,     0,   531,     0,   636,     0,   119,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   649,   650,     0,     0,     0,     0,   637,
       0,     0,     0,     0,     0,     0,   167,     0,     0,     0,
     168,   169,     0,     0,     0,     0,     0,     0,     0,   651,
     652,     0,     0,     0,     0,     0,   171,   121,   122,   123,
     124,     0,     0,     0,     0,   639,     0,     0,     0,   640,
       0,     0,     0,   641,     0,     0,     0,     0,     0,   642,
       0,     0,     0,   643,     0,     0,     0,     0,     0,   129,
       0,     0,     0,     0,     0,   644,     0,     0,     0,     0,
     131,     0,     0,   132,     0,     0,   133,   134,     0,     0,
     135,     0,     0,   136,     0,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
       0,   645,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,     0,     0,   166,     0,     0,     0,     0,     0,     0,
       0,     0,   646,     0,     0,   647,   648,   708,   709,   710,
     711,   712,   713,     0,     0,     0,     0,     0,     0,   714,
       0,   715,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     649,   650,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   637,   167,     0,     0,     0,   168,   169,     0,
       0,     0,     0,     0,     0,     0,   651,   652,     0,     0,
       0,     0,     0,   171,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,     0,     0,     0,     0,   716,     0,
       0,     0,   717,     0,     0,     0,   718,     0,     0,     0,
       0,     0,   719,     0,     0,     0,   643,   714,     0,   715,
       0,     0,   720,     0,     0,     0,     0,     0,   721,     0,
       0,     0,     0,   722,     0,     0,   723,     0,     0,   724,
     725,     0,     0,   726,     0,     0,   727,     0,   728,     0,
     637,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   729,   730,     0,     0,     0,     0,     0,   121,   122,
     123,   124,     0,     0,     0,     0,   716,     0,     0,     0,
     717,     0,     0,     0,   718,     0,     0,     0,     0,     0,
     719,     0,     0,     0,   643,     0,     0,     0,     0,     0,
     720,     0,     0,     0,     0,   646,   721,     0,   647,   648,
       0,   722,     0,     0,   723,     0,     0,   724,   725,     0,
       0,   726,     0,     0,   727,     0,   728,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   649,   650,     0,   731,     0,     0,   729,
     730,     0,   636,     0,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   651,
     652,     0,     0,   260,     0,     0,   171,     0,     0,     0,
       0,     0,     0,     0,     0,   637,     0,     0,     0,     0,
       0,     0,     0,   646,     0,     0,   647,   648,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,   122,   123,   124,     0,     0,     0,
       0,   639,     0,     0,     0,   640,     0,     0,     0,   641,
       0,   649,   650,     0,   731,   642,     0,     0,     0,   643,
       0,     0,     0,     0,     0,   129,     0,     0,     0,     0,
       0,   644,     0,     0,     0,     0,   131,   651,   652,   132,
       0,   260,   133,   134,   171,   923,   135,     0,     0,   136,
       0,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,     0,   645,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,     0,     0,   166,
       0,     0,     0,     0,     0,   714,     0,   715,   646,     0,
       0,   647,   648,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   637,     0,
       0,     0,     0,     0,     0,     0,   649,   650,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   167,
       0,     0,     0,   168,   169,     0,   121,   122,   123,   124,
       0,     0,   651,   652,   716,     0,     0,     0,   717,   171,
       0,     0,   718,     0,     0,     0,     0,     0,   719,     0,
       0,     0,   643,   714,     0,   715,     0,     0,   720,     0,
       0,     0,     0,     0,   721,     0,     0,     0,     0,   722,
       0,     0,   723,     0,     0,   724,   725,     0,     0,   726,
       0,     0,   727,     0,   728,     0,   637,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   729,   730,     0,
       0,     0,     0,     0,   121,   122,   123,   124,     0,     0,
       0,     0,   716,     0,     0,     0,   717,     0,     0,     0,
     718,     0,     0,     0,     0,     0,   719,     0,     0,     0,
     643,     0,     0,     0,     0,     0,   720,     0,     0,     0,
       0,   646,   721,     0,   647,   648,     0,   722,     0,     0,
     723,     0,     0,   724,   725,     0,     0,   726,     0,     0,
     727,     0,   728,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   649,
     650,     0,   731,     0,     0,   729,   730,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   651,   652,     0,     0,   260,
       0,     0,   171,     0,     0,   119,     0,     0,     0,     0,
     120,     0,     0,     0,     0,     0,     0,     0,     0,   646,
     236,     0,   647,   648,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   237,   238,   239,   240,   241,   242,
       0,     0,     0,     0,     0,     0,     0,   649,   650,     0,
     731,   243,   244,     0,   121,   122,   123,   124,     0,     0,
       0,     0,   125,     0,     0,     0,   126,     0,     0,     0,
     127,     0,     0,   651,   652,     0,   128,     0,     0,     0,
     171,     0,     0,     0,     0,     0,   129,     0,     0,     0,
       0,     0,   130,     0,     0,     0,     0,   131,     0,     0,
     132,     0,     0,   133,   134,     0,     0,   135,     0,     0,
     136,     0,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,     0,   140,   141,
     142,     0,     0,   143,   144,     0,     0,   145,   146,   245,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,     0,     0,
     246,     0,     0,     0,     0,     0,     0,   119,     0,     0,
       0,     0,   120,     0,   247,     0,     0,     0,     0,     0,
       0,     0,     0,   248,     0,     0,     0,     0,     0,   249,
       0,     0,     0,     0,   250,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   251,     0,     0,   252,   253,   254,
     255,     0,     0,     0,   256,     0,     0,     0,   257,   258,
     167,     0,     0,     0,   168,   169,   121,   122,   123,   124,
       0,     0,   259,     0,   125,   170,     0,   260,   126,     0,
     171,   172,   127,     0,     0,     0,     0,     0,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,     0,
       0,     0,     0,     0,   130,     0,     0,     0,     0,   131,
       0,     0,   132,     0,     0,   133,   134,     0,     0,   135,
       0,     0,   136,     0,   137,     0,   119,     0,     0,     0,
       0,   120,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   138,   139,     0,
     140,   141,   142,     0,     0,   143,   144,     0,     0,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
       0,     0,   166,     0,     0,   121,   122,   123,   124,     0,
       0,     0,     0,   125,     0,     0,     0,   126,     0,     0,
       0,   127,     0,     0,     0,     0,     0,   128,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,     0,     0,
       0,     0,     0,   130,     0,     0,     0,     0,   131,     0,
       0,   132,     0,     0,   133,   134,     0,     0,   135,     0,
       0,   136,   167,   137,     0,   119,   168,   169,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   170,     0,   260,
       0,     0,   171,   172,     0,     0,   138,   139,     0,   140,
     141,   142,     0,     0,   143,   144,   637,     0,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,     0,
       0,   166,     0,     0,   121,   122,   123,   124,     0,     0,
       0,     0,   639,     0,     0,     0,   640,     0,     0,     0,
     641,     0,     0,     0,     0,     0,   642,     0,     0,     0,
     643,     0,     0,     0,     0,     0,   129,     0,     0,     0,
       0,     0,   644,     0,     0,     0,     0,   131,     0,     0,
     132,     0,     0,   133,   134,     0,     0,   135,     0,     0,
     136,   167,   137,     0,     0,   168,   169,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   170,     0,     0,     0,
       0,   171,   172,     0,     0,   138,   139,     0,   645,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,     0,     0,
     166,     0,     0,     0,     0,     0,     0,     0,     0,   646,
     715,     0,   647,   648,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   637,     0,     0,     0,     0,     0,   649,   650,   237,
     238,   239,   240,   241,   242,     0,     0,     0,     0,     0,
     167,     0,     0,     0,   168,   169,     0,     0,     0,   121,
     122,   123,   124,   651,   652,     0,     0,   716,     0,     0,
     171,   717,     0,     0,     0,   718,     0,     0,     0,     0,
       0,   719,     0,     0,     0,   643,     0,     0,   715,     0,
       0,   720,     0,     0,     0,     0,     0,   721,     0,     0,
       0,     0,   722,     0,     0,   723,     0,     0,   724,   725,
       0,     0,   726,     0,     0,   727,     0,   728,     0,   637,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     729,   730,     0,     0,     0,     0,     0,   121,   122,   123,
     124,     0,     0,     0,     0,   716,     0,     0,     0,   717,
       0,     0,     0,   718,     0,     0,     0,     0,     0,   719,
       0,     0,     0,   643,     0,     0,     0,     0,     0,   720,
       0,     0,     0,     0,   646,   721,     0,   647,   648,     0,
     722,     0,     0,   723,     0,     0,   724,   725,     0,     0,
     726,     0,     0,   727,     0,   728,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   649,   650,     0,   731,     0,     0,   729,   730,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   651,   652,
       0,     0,     0,     0,     0,   171,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   646,     0,     0,   647,   648,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     3,     0,     0,     4,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
     649,   650,     0,   731,     0,     0,     0,     0,     0,     0,
       0,     6,     7,     0,     0,     0,     8,     0,     9,     0,
      10,     0,     0,    11,    12,    13,   651,   652,     0,     0,
      14,    15,    16,   171,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -220,     0,
       0,     0,     0,     0,    29,     0,     0,     0,     0,     0,
       0,     0,     0,    30,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,     0,     0,     0,     0,    36
};

static const yytype_int16 yycheck[] =
{
       1,    46,     3,    56,   322,   168,     1,    25,    53,    85,
     323,    87,    88,   321,   324,    91,    92,   308,   263,    95,
     280,   334,    98,    99,   100,    25,   615,   615,    46,   105,
     106,    27,   172,    25,   168,    53,   844,   113,   931,    40,
       7,   935,    12,    13,   934,    25,    23,    48,   936,    46,
       7,   981,   298,    72,    46,    31,    53,  1079,  1022,   848,
     849,    53,   308,    83,    25,   854,    46,   850,  1069,    23,
      25,     1,    61,    53,     4,    10,     6,   118,    56,  1127,
    1128,    43,     8,    25,     1,    46,     4,     4,     6,     6,
     555,    46,    53,    63,    64,    65,    26,    27,    53,   955,
     956,    90,   147,   968,    46,    25,    76,    77,    78,    26,
      27,    53,    83,    22,    40,   104,  1042,  1043,   983,    89,
      90,   910,   275,    83,    94,   278,    46,   114,    20,    83,
      84,    85,     1,    53,     8,     4,    71,     6,   125,    20,
     605,   111,   112,    83,     1,   115,     7,     4,  1196,     6,
     168,   140,    35,   140,   172,   196,   197,    26,    27,   607,
     608,    93,   610,    93,   612,   106,    40,   107,   108,    26,
      27,   880,    68,    82,   230,   231,   168,    43,   887,    84,
     172,    42,   123,    44,   106,  1078,  1099,   635,   168,   972,
     638,    83,   172,    54,     1,   215,   185,     4,  1124,     6,
     245,   123,    83,    68,   298,    74,    75,   168,  1209,    78,
     135,   172,    35,   168,   308,   140,   212,   172,   263,    26,
      27,     8,   218,  1245,    93,    23,   168,  1191,    33,     1,
     172,  1096,     4,    83,     6,    93,    93,    24,   178,   687,
     768,   206,   690,   214,   215,   263,   774,   266,   168,   116,
     182,   183,   172,    40,    26,    27,   196,   244,   119,   206,
    1190,    33,   881,   130,   133,   274,    38,  1180,    40,   199,
     323,   263,  1185,   220,   319,    82,   213,   353,   136,   137,
     298,   334,   265,   263,   329,    83,    84,    85,    31,     1,
     308,   228,     4,   275,     6,   914,   915,   214,   275,   275,
     275,   319,   263,   751,   752,   267,   268,   269,   263,   276,
     171,   329,  1168,  1102,    26,    27,   213,   113,   206,   276,
     298,   263,   319,     7,   278,   170,  1115,   319,  1222,   206,
     308,  1221,   329,   230,   231,  1223,    20,   329,    22,   319,
     136,   137,   199,   263,   170,   323,   276,     1,   260,   329,
       4,  1244,     6,   249,   250,   251,   334,   268,   319,   276,
     123,   133,    74,    75,   319,   226,    78,   214,   329,   165,
     133,   134,    26,    27,   329,  1183,   267,   319,   269,   240,
     241,    93,   352,   244,   249,   250,   251,   329,   836,   837,
     249,   839,   981,   228,   116,   984,   984,   119,   213,   319,
     259,   267,   268,   269,    82,   166,   666,   276,   378,   329,
     171,   172,    68,   104,   175,   176,   707,     1,    68,   276,
       4,   133,     6,   230,   231,   133,   198,   118,     4,   120,
     878,  1220,     1,  1022,  1022,     4,   599,     6,    83,    93,
     212,   889,    26,    27,    31,   893,    33,   895,    35,   266,
     613,    38,    39,    40,    20,   227,    22,    26,    27,   750,
     232,   261,   107,   108,   264,   243,   618,    45,    46,   276,
      93,    31,    91,    92,   626,     9,    17,   275,   630,   613,
     278,   104,     5,   106,   113,     8,    18,    71,    72,    73,
      74,    75,    31,    32,    78,   118,   277,   120,     1,   275,
     123,     4,    38,     6,   276,   196,   197,   136,   137,    93,
     139,    89,    47,    48,   222,   223,   224,   225,   226,   380,
      98,   615,    38,    26,    27,    59,   104,   975,    62,   214,
     215,   979,     1,   178,   109,     4,   275,     6,   113,   275,
      74,    75,   120,    15,    16,   199,   169,   275,   996,   133,
       0,   196,    86,    20,     4,    22,     6,    26,    27,   178,
     179,   136,   137,   182,   276,   705,    31,   212,    71,    72,
      73,    74,    75,   196,   197,    78,   110,     4,    93,     6,
       7,   599,   227,   117,    95,    42,   582,   232,     7,    83,
      93,   106,    86,    87,    88,   613,     8,   615,   113,   110,
     230,   231,  1191,  1191,   281,    74,    75,   599,   123,    78,
     280,   198,   123,   707,   129,    91,    92,    93,   129,   599,
     260,   613,   276,   260,    93,   212,    82,     4,    82,     6,
     133,     8,   923,   613,    82,    78,   896,   615,   599,   275,
     227,    38,    87,    88,   599,   232,    91,    92,    69,    70,
      95,    72,   613,    98,    99,   100,   750,   599,   613,   228,
     105,   106,   173,   174,   133,    82,   109,   913,   113,    15,
      16,   613,   835,   919,    38,   921,   922,    15,    16,   599,
      91,    92,   700,   701,   702,   703,   704,   705,    38,   707,
       4,     5,   276,   613,   298,    99,   100,   101,   102,   103,
     700,   701,   254,   255,   308,    62,    63,   276,   700,   701,
     702,   703,   704,   705,   157,   158,   159,   160,   161,   162,
     700,   701,   702,   703,   704,   705,   971,    76,    77,   707,
      82,    93,   750,    95,    82,   981,  1057,  1058,   901,   700,
     701,   702,   703,   704,   705,   700,   701,   702,   703,   704,
     705,   113,   753,   115,   116,  1015,   118,  1017,   700,   701,
     702,   703,   704,   705,   126,   127,    32,    31,    34,    33,
      36,    37,   750,   276,    38,  1020,    40,    43,    44,    43,
     700,   701,   702,   703,   704,   705,   880,   881,   882,   883,
     884,    17,   886,   887,   253,   254,   255,   891,   892,    31,
     891,   892,    93,  1121,    95,    96,    97,   276,    74,    82,
      82,  1119,  1122,    45,    46,    79,    80,   835,     5,   913,
     914,   915,   916,   917,   918,   919,  1139,   921,   922,   923,
      82,    31,    18,    33,     7,   277,   697,     7,    38,    39,
      40,   106,   212,   835,     7,  1158,     7,   217,   218,     5,
       7,   116,     7,   276,   715,   835,     7,    89,   123,   267,
     268,   269,   232,   881,   129,   130,    98,    83,    84,    85,
      17,   277,   104,    18,   835,   298,   249,   250,   251,     8,
     835,    82,   275,   901,   929,   308,   275,   981,   120,   275,
     984,   275,    82,   835,    82,   913,   914,   915,   916,   917,
     918,   919,    82,   921,   922,   923,    82,   261,   353,   901,
     888,   929,   275,   215,    82,   835,   237,   238,   239,   240,
     241,   901,     8,    38,    82,    30,   971,   928,  1022,   930,
     931,    93,    54,   928,   119,   930,   931,   929,     5,    93,
     901,    31,    82,    93,    82,   923,   901,     1,   275,   929,
       4,     7,     6,   971,   282,    45,    46,    82,    82,   901,
      93,     7,    95,   981,   233,    83,   984,    83,   929,    83,
      83,   280,    26,    27,   929,  1020,    83,   206,   274,   971,
     113,   901,   115,   116,   117,   118,    83,   929,    82,   274,
      82,   971,    62,    63,    64,    65,    66,    67,   198,    89,
      82,   229,  1020,    82,  1022,   276,   984,     5,    98,   929,
     971,   615,   212,   276,   104,    29,   971,    71,    72,    73,
      74,    75,    84,    82,    78,   275,   275,   227,  1020,   971,
     120,  1076,   232,   275,   275,    31,   275,   275,    83,    93,
    1020,   112,   275,    30,    83,   121,  1047,    82,   909,    45,
      46,   971,  1053,  1054,  1055,    31,    16,   933,  1076,  1020,
     320,  1206,  1070,  1204,  1038,  1020,  1067,    75,   262,    45,
      46,  1115,   623,  1074,  1075,   631,  1077,  1078,  1020,   133,
    1075,  1106,  1077,  1078,  1076,  1086,  1139,   609,   978,   882,
     250,  1086,  1098,    89,  1170,   883,  1076,  1191,   884,   894,
    1020,   886,    98,   707,   693,  1158,   698,   899,   104,   788,
     703,   702,   854,    89,   704,  1076,  1246,   901,   326,  1248,
    1247,  1076,    98,   328,   120,    96,   308,   916,   104,   327,
     501,    -1,    -1,   245,  1076,   917,  1137,  1138,    31,   918,
     246,    -1,     1,   246,   120,     4,   750,     6,    -1,  1150,
      -1,    -1,    45,    46,  1155,    -1,  1076,    -1,    -1,  1160,
      -1,  1139,    -1,    -1,    -1,  1166,    -1,    26,    27,    -1,
    1171,  1166,    -1,  1191,    33,  1036,  1037,  1038,    -1,    38,
    1158,    40,    -1,    -1,   607,   608,    -1,   610,    -1,   612,
      -1,    -1,   615,    -1,    -1,    -1,    89,  1242,    -1,    -1,
      -1,    -1,    -1,    91,    92,    98,    -1,    -1,    -1,    -1,
    1211,   104,   635,  1214,    -1,   638,    -1,   105,    -1,   107,
     108,   109,   276,    -1,  1242,    -1,    -1,   120,    -1,    -1,
    1231,  1232,  1233,  1234,   122,   123,   124,    -1,    -1,    -1,
      -1,    -1,  1243,  1244,    -1,  1246,  1247,  1248,  1243,  1244,
    1242,  1246,  1247,  1248,    -1,    -1,  1257,  1258,  1259,  1260,
    1261,  1262,  1242,    -1,   687,  1266,  1261,   690,    -1,  1270,
      -1,    -1,    -1,    -1,   133,    -1,    -1,   881,    -1,  1280,
      -1,  1242,     1,    -1,   707,    -1,    -1,  1242,    -1,     8,
       9,    10,    11,    12,    13,    -1,    -1,    16,    -1,    -1,
    1242,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   913,
     914,   915,   916,   917,   918,   919,    31,   921,   922,   923,
      -1,    -1,  1242,    -1,    -1,    -1,    -1,   750,   751,   752,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,
      59,    -1,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    71,   212,    73,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    86,   227,    -1,
      89,    90,    -1,   232,    89,    94,    -1,   981,    35,    36,
     984,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,
     109,   110,   111,   112,    -1,    -1,   115,    -1,   117,    -1,
      -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,   832,
      67,    68,    69,   836,   837,    -1,   839,   276,  1022,    -1,
      -1,    -1,    -1,    80,    81,    82,   143,    -1,    -1,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
      97,    -1,    23,    -1,   101,   102,    -1,   104,    -1,    -1,
     107,   113,    -1,    -1,   116,   878,    -1,   880,   881,   882,
     883,   884,    -1,   886,   887,   888,   889,   129,   891,   892,
     893,   133,   895,    54,   136,   137,    -1,    -1,    -1,   141,
     142,   143,   144,   145,    -1,    -1,    -1,    -1,    -1,    -1,
     913,   914,   915,   916,   917,   918,   919,    -1,   921,   922,
     923,    -1,    83,    84,    85,    -1,    -1,    -1,    -1,    90,
      -1,    -1,    -1,    94,    -1,    -1,    -1,    98,    -1,    -1,
      -1,    -1,    -1,   104,    -1,    -1,    -1,   108,    31,    32,
      33,    34,    -1,    -1,    37,    38,    -1,    40,    41,   120,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   975,    -1,    -1,    -1,   979,    -1,   981,    -1,
      -1,   984,    -1,    -1,    -1,    -1,    -1,    -1,   225,    -1,
      -1,    -1,    -1,   996,    -1,    -1,    79,    80,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1191,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1022,
      -1,    91,    92,    -1,    -1,    95,    -1,    -1,    -1,     1,
      -1,    -1,     4,    -1,     6,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    -1,    -1,   207,   346,    -1,   210,
     211,    23,    -1,   352,    26,    27,    28,    -1,    -1,    -1,
     359,    -1,   361,    -1,   363,    -1,    38,    -1,    -1,   368,
      -1,   370,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   378,
      -1,    -1,    -1,    -1,   245,   246,    -1,    -1,   325,    -1,
      62,    63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
     337,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    -1,
      82,    83,    84,    85,    -1,   198,    -1,   278,    90,    -1,
     357,    93,    94,    -1,    -1,    -1,    98,    -1,    -1,   212,
      -1,    -1,   104,    -1,   217,   218,   219,    -1,    -1,    -1,
      -1,    -1,   114,    -1,   227,    -1,    -1,    -1,   120,   232,
      -1,    -1,    -1,   125,    91,    92,   128,    -1,    -1,   131,
     132,    -1,    -1,   135,    -1,    -1,   138,   104,   140,    -1,
      31,    -1,    33,    -1,    35,   112,    -1,    38,    39,    40,
      -1,    -1,    -1,   120,    45,    46,    -1,    -1,  1191,    -1,
      -1,   163,   164,    -1,   166,   167,   168,    -1,    -1,   171,
     172,    -1,    -1,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,    -1,    -1,   198,    -1,    89,    -1,
      -1,     1,    -1,    -1,     4,    -1,     6,    98,    -1,    -1,
     212,    -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,   221,
      -1,    -1,    -1,    23,    -1,   227,    26,    27,    28,   120,
     232,    -1,   199,   200,   201,   202,    91,    92,    38,    -1,
     242,    -1,    -1,   245,   246,   247,   248,   214,   215,   216,
     252,    -1,    -1,    -1,   256,   257,   258,   112,    -1,    -1,
     262,   263,    62,    63,    64,    65,    66,    67,   270,    -1,
      -1,   273,    -1,   275,   276,    75,   278,   279,    -1,    79,
      80,    -1,    82,    83,    84,    85,    -1,    -1,    -1,    -1,
      90,    -1,    -1,    93,    94,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,    -1,   104,    -1,    -1,   198,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,    -1,
     120,   212,    -1,   178,    -1,   125,    -1,    -1,   128,    -1,
      -1,   131,   132,    -1,    -1,   135,   227,    -1,   138,    -1,
     140,   232,    -1,    -1,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,    -1,    -1,   214,
     215,   216,    -1,   163,   164,    -1,   166,   167,   168,    -1,
      -1,   171,   172,    -1,    -1,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,    -1,    -1,   198,    -1,
      -1,    -1,    -1,     1,    -1,    -1,     4,    -1,     6,    -1,
      -1,    -1,   212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   221,    -1,    -1,    -1,    23,    -1,   227,    26,    27,
      28,    -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,   242,    -1,    -1,   245,   246,   247,   248,   778,
      -1,    -1,   252,    -1,    -1,    -1,   256,   257,   258,    -1,
      -1,    -1,   262,   263,    62,    63,    64,    65,    66,    67,
     270,    -1,    -1,   273,    -1,   275,   276,    75,   278,   279,
      -1,    79,    80,    -1,    82,    83,    84,    85,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    93,    94,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,   125,    -1,    -1,
     128,    -1,    -1,   131,   132,    -1,    -1,   135,    -1,    -1,
     138,    -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   163,   164,    -1,   166,   167,
     168,    -1,    -1,   171,   172,    -1,    -1,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,    -1,    -1,
     198,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   212,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,   221,    23,    -1,    -1,    -1,    -1,   227,
      -1,    -1,    -1,    -1,   232,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   242,    -1,    -1,   245,   246,   247,
     248,    -1,    -1,    -1,   252,    54,    -1,    -1,   256,   257,
     258,    -1,    -1,    -1,   262,   263,    -1,    -1,    -1,    68,
      -1,    -1,   270,    -1,    -1,   273,    -1,   275,   276,    -1,
     278,   279,    -1,    82,    83,    84,    85,    -1,    -1,    -1,
      -1,    90,    -1,    -1,    -1,    94,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,   108,
      -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,
      -1,   120,    -1,    -1,    -1,    -1,   125,    -1,    83,   128,
      -1,    -1,   131,   132,    -1,    -1,   135,    -1,    -1,   138,
      -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   109,    -1,    -1,   112,    -1,    -1,
      -1,    -1,    -1,    -1,   163,   164,   121,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,    -1,    -1,   198,
      -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,   207,    -1,
      -1,   210,   211,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    -1,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,    -1,    -1,    -1,    -1,    -1,   245,   246,    83,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,   258,
      -1,    -1,    -1,   262,   263,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   271,   272,   109,    -1,    -1,   112,    -1,   278,
      82,    83,    84,    85,    -1,    -1,   121,    -1,    90,    -1,
      -1,    -1,    94,    -1,   249,    -1,    98,    -1,    -1,    -1,
      -1,    -1,   104,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,   114,    -1,    -1,    -1,    -1,    -1,   120,    -1,
      -1,    -1,    -1,   125,    -1,    -1,   128,    -1,    -1,   131,
     132,    -1,    -1,   135,    -1,    -1,   138,    -1,   140,    -1,
      -1,    -1,    -1,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   163,   164,    -1,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,    -1,    -1,   198,    -1,    -1,    -1,
       5,    -1,    -1,    -1,    -1,   207,    -1,    -1,   210,   211,
      -1,    -1,    -1,    -1,   249,    -1,    21,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   245,   246,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,   258,    -1,    -1,    -1,
     262,   263,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   271,
     272,    -1,    -1,    -1,    -1,    -1,   278,    82,    83,    84,
      85,    -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    94,
      -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,
      -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,   114,
      -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,
     125,    -1,    -1,   128,    -1,    -1,   131,   132,    -1,    -1,
     135,    -1,    -1,   138,    -1,   140,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   163,   164,
      -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,    -1,    -1,   198,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   207,    -1,    -1,   210,   211,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     245,   246,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,   258,    -1,    -1,    -1,   262,   263,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   271,   272,    -1,    -1,
      -1,    -1,    -1,   278,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    83,    84,    85,    -1,    -1,    -1,    -1,    90,    -1,
      -1,    -1,    94,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,   104,    -1,    -1,    -1,   108,    21,    -1,    23,
      -1,    -1,   114,    -1,    -1,    -1,    -1,    -1,   120,    -1,
      -1,    -1,    -1,   125,    -1,    -1,   128,    -1,    -1,   131,
     132,    -1,    -1,   135,    -1,    -1,   138,    -1,   140,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   163,   164,    -1,    -1,    -1,    -1,    -1,    82,    83,
      84,    85,    -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,
      94,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,
     104,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,
     114,    -1,    -1,    -1,    -1,   207,   120,    -1,   210,   211,
      -1,   125,    -1,    -1,   128,    -1,    -1,   131,   132,    -1,
      -1,   135,    -1,    -1,   138,    -1,   140,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   245,   246,    -1,   248,    -1,    -1,   163,
     164,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   271,
     272,    -1,    -1,   275,    -1,    -1,   278,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   207,    -1,    -1,   210,   211,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    83,    84,    85,    -1,    -1,    -1,
      -1,    90,    -1,    -1,    -1,    94,    -1,    -1,    -1,    98,
      -1,   245,   246,    -1,   248,   104,    -1,    -1,    -1,   108,
      -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,
      -1,   120,    -1,    -1,    -1,    -1,   125,   271,   272,   128,
      -1,   275,   131,   132,   278,   279,   135,    -1,    -1,   138,
      -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   163,   164,    -1,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,    -1,    -1,   198,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,   207,    -1,
      -1,   210,   211,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   245,   246,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   258,
      -1,    -1,    -1,   262,   263,    -1,    82,    83,    84,    85,
      -1,    -1,   271,   272,    90,    -1,    -1,    -1,    94,   278,
      -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,    -1,
      -1,    -1,   108,    21,    -1,    23,    -1,    -1,   114,    -1,
      -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,   125,
      -1,    -1,   128,    -1,    -1,   131,   132,    -1,    -1,   135,
      -1,    -1,   138,    -1,   140,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   163,   164,    -1,
      -1,    -1,    -1,    -1,    82,    83,    84,    85,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    -1,    94,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,   207,   120,    -1,   210,   211,    -1,   125,    -1,    -1,
     128,    -1,    -1,   131,   132,    -1,    -1,   135,    -1,    -1,
     138,    -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   245,
     246,    -1,   248,    -1,    -1,   163,   164,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   271,   272,    -1,    -1,   275,
      -1,    -1,   278,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   207,
      38,    -1,   210,   211,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   245,   246,    -1,
     248,    79,    80,    -1,    82,    83,    84,    85,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    -1,    94,    -1,    -1,    -1,
      98,    -1,    -1,   271,   272,    -1,   104,    -1,    -1,    -1,
     278,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,   125,    -1,    -1,
     128,    -1,    -1,   131,   132,    -1,    -1,   135,    -1,    -1,
     138,    -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   163,   164,    -1,   166,   167,
     168,    -1,    -1,   171,   172,    -1,    -1,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,    -1,    -1,
     198,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    28,    -1,   212,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   221,    -1,    -1,    -1,    -1,    -1,   227,
      -1,    -1,    -1,    -1,   232,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   242,    -1,    -1,   245,   246,   247,
     248,    -1,    -1,    -1,   252,    -1,    -1,    -1,   256,   257,
     258,    -1,    -1,    -1,   262,   263,    82,    83,    84,    85,
      -1,    -1,   270,    -1,    90,   273,    -1,   275,    94,    -1,
     278,   279,    98,    -1,    -1,    -1,    -1,    -1,   104,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,
      -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,   125,
      -1,    -1,   128,    -1,    -1,   131,   132,    -1,    -1,   135,
      -1,    -1,   138,    -1,   140,    -1,    23,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   163,   164,    -1,
     166,   167,   168,    -1,    -1,   171,   172,    -1,    -1,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
      -1,    -1,   198,    -1,    -1,    82,    83,    84,    85,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    -1,    94,    -1,    -1,
      -1,    98,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,   125,    -1,
      -1,   128,    -1,    -1,   131,   132,    -1,    -1,   135,    -1,
      -1,   138,   258,   140,    -1,    23,   262,   263,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,   275,
      -1,    -1,   278,   279,    -1,    -1,   163,   164,    -1,   166,
     167,   168,    -1,    -1,   171,   172,    54,    -1,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,    -1,
      -1,   198,    -1,    -1,    82,    83,    84,    85,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    -1,    94,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,   125,    -1,    -1,
     128,    -1,    -1,   131,   132,    -1,    -1,   135,    -1,    -1,
     138,   258,   140,    -1,    -1,   262,   263,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,    -1,
      -1,   278,   279,    -1,    -1,   163,   164,    -1,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,    -1,    -1,
     198,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   207,
      23,    -1,   210,   211,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,   245,   246,    62,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
     258,    -1,    -1,    -1,   262,   263,    -1,    -1,    -1,    82,
      83,    84,    85,   271,   272,    -1,    -1,    90,    -1,    -1,
     278,    94,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,
      -1,   104,    -1,    -1,    -1,   108,    -1,    -1,    23,    -1,
      -1,   114,    -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,
      -1,    -1,   125,    -1,    -1,   128,    -1,    -1,   131,   132,
      -1,    -1,   135,    -1,    -1,   138,    -1,   140,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     163,   164,    -1,    -1,    -1,    -1,    -1,    82,    83,    84,
      85,    -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    94,
      -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,
      -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,   114,
      -1,    -1,    -1,    -1,   207,   120,    -1,   210,   211,    -1,
     125,    -1,    -1,   128,    -1,    -1,   131,   132,    -1,    -1,
     135,    -1,    -1,   138,    -1,   140,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   245,   246,    -1,   248,    -1,    -1,   163,   164,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   271,   272,
      -1,    -1,    -1,    -1,    -1,   278,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   207,    -1,    -1,   210,   211,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     0,     1,    -1,    -1,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     245,   246,    -1,   248,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    -1,    -1,    38,    39,    40,   271,   272,    -1,    -1,
      45,    46,    47,   278,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   198,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   227,    -1,    -1,    -1,    -1,   232
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   284,     0,     1,     4,     6,    26,    27,    31,    33,
      35,    38,    39,    40,    45,    46,    47,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    89,
      98,   104,   120,   198,   212,   227,   232,   285,   287,   288,
     289,   290,   337,   338,   339,   340,   348,   285,    84,    83,
     334,   339,   340,   348,   339,   342,   342,   342,   290,    35,
     291,    31,    33,    38,    39,    40,   198,   212,   227,   232,
     292,    35,   293,    31,    33,    35,    38,    39,    40,   198,
     212,   227,   232,   294,    31,    32,    33,    34,    37,    38,
      40,    41,    43,    79,    80,    81,   198,   212,   217,   218,
     219,   227,   232,   295,   212,   217,   218,   232,   296,    31,
      33,    38,    40,    43,    79,    80,   297,    33,   298,    23,
      28,    82,    83,    84,    85,    90,    94,    98,   104,   114,
     120,   125,   128,   131,   132,   135,   138,   140,   163,   164,
     166,   167,   168,   171,   172,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   198,   258,   262,   263,
     273,   278,   279,   306,   335,   427,   428,   429,   430,   431,
     484,   487,   491,   492,   494,   496,   507,   508,   510,   512,
     514,   516,   518,   520,   522,   524,   526,   528,   530,   532,
     534,   538,   540,   542,   543,   545,   547,   549,   551,   553,
     555,   557,    43,   267,   268,   269,   299,   305,    43,   268,
     300,   305,    83,   301,   302,   206,   339,   344,   344,   344,
       0,   285,   334,   334,   265,   347,    38,    62,    63,    64,
      65,    66,    67,    79,    80,   177,   198,   212,   221,   227,
     232,   242,   245,   246,   247,   248,   252,   256,   257,   270,
     275,   352,   353,   354,   355,   356,   357,   361,   362,   365,
     366,   373,   377,   381,   382,   384,   385,   401,   402,   404,
     405,   407,   408,   411,   412,   419,   421,   422,   425,   426,
     430,   435,   436,   437,   438,   439,   440,   445,   446,   447,
     469,   483,   487,   488,   505,   506,   507,   285,   274,   307,
     310,   352,   334,   312,   314,   427,   447,   317,   340,   349,
     339,   340,   342,   342,   342,   206,   344,   344,   344,   348,
     339,   340,   349,   342,   342,   342,   206,   463,   344,   344,
     344,   339,   338,   351,   340,   351,    31,   351,   342,   342,
     351,   351,    31,    32,   342,   351,   220,   463,   344,    31,
     351,    31,   351,    31,   351,   344,   344,   344,    31,   351,
      31,   351,   344,   339,   340,   342,   342,   351,    31,   342,
     340,    86,    87,    88,   334,   509,    91,    92,   178,   179,
     182,   433,   434,    91,    92,    93,   511,    93,    95,    96,
      97,   513,    99,   100,   101,   102,   103,   515,    91,    92,
      95,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     517,    93,    95,   113,   115,   116,   117,   118,   519,    91,
      92,   105,   107,   108,   109,   122,   123,   124,   521,    93,
      95,   113,   115,   116,   118,   126,   127,   523,   106,   116,
     123,   129,   130,   525,   116,   130,   527,   123,   133,   134,
     529,   109,   113,   136,   137,   531,   113,   136,   137,   139,
     533,   113,   116,   129,   133,   136,   137,   141,   142,   143,
     144,   145,   535,    93,   136,   137,   539,   113,   136,   137,
     165,   541,    93,   104,   106,   118,   120,   123,   169,   196,
     197,   493,   495,   546,   170,   548,   170,   550,   106,   123,
     544,    95,   110,   123,   129,   173,   174,   552,   106,   123,
     554,    93,   106,   113,   123,   129,   556,    83,   109,   112,
     121,   249,   485,   486,   487,    91,    92,   112,   178,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   214,   215,   216,   497,   498,   502,   249,   259,
     490,   440,   446,   260,   166,   171,   172,   175,   176,   558,
     334,   439,   305,   268,   305,    32,    34,    36,    37,    43,
      44,    74,   303,   344,   334,   214,   459,   460,   228,   467,
     468,   230,   231,   374,   461,   462,    82,    47,    48,   420,
     334,   334,   334,    83,   485,   497,   498,   213,   213,   228,
     213,   374,    68,    68,     4,   286,   448,   449,   266,   350,
     355,   214,   215,   363,   364,   133,   222,   223,   224,   225,
     226,   367,   368,   243,   383,     5,    21,    54,    68,    90,
      94,    98,   104,   108,   120,   166,   207,   210,   211,   245,
     246,   271,   272,   386,   387,   388,   389,   390,   391,   392,
     394,   395,   396,   397,   398,   399,   400,   428,   429,   478,
     479,   480,   484,   491,   492,   494,   496,   503,   504,   507,
      68,   249,   250,   251,   403,   409,   410,    68,   406,   409,
     253,   254,   255,   413,   414,   415,   416,    31,   423,   424,
      15,    16,    17,    18,   277,     8,    24,    40,     9,    10,
      11,    12,    13,    14,    21,    23,    90,    94,    98,   104,
     114,   120,   125,   128,   131,   132,   135,   138,   140,   163,
     164,   248,   428,   429,   441,   442,   443,   444,   447,   470,
     471,   472,   473,   474,   475,   476,   477,   479,   480,   481,
     482,    38,    38,   458,   470,   471,   275,   275,   275,   275,
      42,   346,   352,   307,   310,   312,   314,   317,   344,   460,
     468,   462,   352,   314,   344,   339,   342,   351,    31,   344,
     339,   339,   339,   339,   339,   342,   334,     7,     8,    93,
     182,   183,   432,   143,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   536,   495,   281,    91,    92,
     104,   112,   120,   199,   200,   201,   499,   500,   502,   260,
     260,    82,   280,   268,   304,   305,   466,    82,   230,   231,
     378,    82,   417,   418,   440,   275,    38,    38,   502,    38,
     399,   399,   378,   399,    82,   399,   446,   444,   447,   452,
     453,   456,   476,   477,     7,   276,   335,    82,    82,   364,
      61,    90,   104,   140,   185,   370,   335,    82,    82,    82,
     335,   369,   368,   114,   125,   140,   244,   399,     5,   399,
      15,    16,    17,    18,   277,    20,    22,     8,    40,     5,
     409,     7,     7,     5,     7,     5,   399,   399,   414,     7,
     334,   275,   424,   430,   430,   435,   436,   437,   439,    23,
     275,   358,   471,     7,    15,    16,    17,    18,   277,     7,
      20,    22,     8,   279,   471,   399,   399,   285,   309,   311,
     313,   318,    82,   275,   275,   275,   275,   466,   466,   339,
      82,   434,    78,   109,   157,   158,   159,   160,   161,   162,
     537,    82,    91,    92,   501,    82,    82,   261,   489,   275,
     215,    82,    83,   215,   375,   428,    72,   350,   454,   455,
     440,   450,   451,   399,   399,    38,   399,    82,   375,    30,
     286,     5,   286,   454,   286,   449,   119,   116,   119,   371,
     372,    93,    93,    54,    93,   399,     5,   386,   428,   480,
     481,   387,   388,   389,    82,   391,   386,   393,   428,   447,
     399,   428,   480,   503,   503,   399,   410,   399,   409,   416,
     450,   334,   286,   359,   360,   476,   481,   481,   472,   473,
     474,   476,    82,   476,   476,   471,    33,    38,    40,   133,
     198,   212,   227,   232,   276,   285,   287,   308,    75,    93,
     276,   285,   287,   329,   332,   352,    71,    72,    73,    74,
      75,    78,    93,   133,   276,   285,   287,   319,    74,    93,
     133,   276,   285,   287,   319,   309,   311,   313,   318,   275,
       7,   282,   489,   264,   489,    82,   326,    82,    20,    83,
     233,   376,    83,   336,   455,   355,   454,   399,    20,    83,
     376,   399,   457,   476,   477,   483,     7,    83,    83,    83,
     399,   409,   409,   355,   452,     7,   276,   280,   334,   341,
     334,   343,   343,    83,   206,   334,   345,   345,   345,   285,
      62,    63,   333,    83,   285,   285,   285,   336,   336,   274,
      76,    77,   320,    82,    83,   107,   108,   178,   196,   321,
     322,   328,    69,    70,    72,   315,   316,   285,   274,   322,
     315,   285,   276,   276,   276,   276,   326,    82,    82,    93,
     199,   276,   285,   287,   465,   237,   238,   239,   240,   241,
     380,   229,   379,    82,   276,   380,   379,   286,   372,   276,
       5,   286,   360,   310,   312,   317,   345,   323,   323,   323,
      29,   285,   285,   314,     8,   285,     7,   285,   314,     5,
     285,   276,   489,    84,   338,   285,   379,    82,   375,   379,
     483,   275,   275,   275,   323,   275,   275,   275,    83,   321,
     316,   212,   227,   232,   322,   285,   112,   285,    83,   214,
     215,   286,   311,   313,   318,   275,   324,   327,   325,    30,
     331,   285,   285,   285,   285,   135,   140,   464,   276,   276,
     276,   326,   276,   285,   287,   459,   276,   285,   287,   467,
     276,   285,   287,   461,    83,   121,   285,   285,   285,   285,
     276,   285,   285,   285,    22,    82,   330,   285,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   283,   284,   284,   285,   285,   286,   286,   287,   287,
     287,   288,   288,   288,   288,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   291,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   293,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294,   295,   295,   295,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   296,   296,   296,   296,   296,   296,   297,   297,
     297,   297,   297,   297,   297,   298,   299,   299,   299,   300,
     300,   300,   301,   302,   302,   303,   303,   303,   303,   303,
     303,   303,   303,   304,   304,   304,   305,   305,   306,   307,
     308,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   310,   311,   311,   311,   311,   311,   311,   312,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     314,   314,   315,   315,   316,   316,   316,   317,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   319,   319,
     320,   320,   321,   322,   322,   323,   324,   324,   324,   324,
     325,   325,   325,   325,   326,   326,   326,   326,   327,   327,
     327,   327,   328,   328,   328,   328,   328,   329,   330,   330,
     331,   331,   332,   333,   333,   334,   335,   335,   335,   336,
     337,   337,   338,   338,   338,   338,   338,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   348,   349,
     350,   351,   351,   352,   352,   353,   354,   354,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   356,   356,   357,   358,
     358,   359,   359,   359,   360,   361,   361,   362,   362,   363,
     363,   364,   364,   365,   365,   366,   367,   367,   368,   368,
     368,   368,   368,   368,   369,   370,   370,   370,   370,   370,
     371,   371,   372,   372,   373,   373,   373,   374,   374,   374,
     375,   375,   376,   376,   377,   377,   378,   378,   378,   379,
     379,   379,   379,   380,   380,   380,   380,   380,   381,   382,
     383,   383,   383,   383,   383,   384,   385,   385,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   387,   387,
     387,   388,   388,   389,   389,   390,   390,   391,   392,   392,
     393,   393,   394,   394,   395,   396,   397,   398,   398,   398,
     399,   399,   399,   400,   400,   400,   400,   400,   400,   400,
     401,   401,   402,   403,   403,   403,   404,   404,   405,   406,
     406,   406,   406,   406,   407,   407,   408,   409,   409,   410,
     410,   410,   411,   411,   412,   413,   413,   414,   414,   415,
     415,   416,   416,   417,   417,   418,   419,   420,   420,   421,
     421,   422,   423,   423,   424,   425,   426,   427,   428,   428,
     428,   429,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   431,   432,   432,   432,   433,   433,
     433,   433,   433,   434,   434,   435,   435,   435,   436,   436,
     437,   437,   438,   438,   439,   440,   440,   441,   442,   443,
     444,   444,   444,   445,   446,   446,   446,   447,   448,   448,
     448,   449,   449,   449,   450,   450,   451,   452,   452,   453,
     454,   454,   455,   455,   456,   456,   457,   457,   458,   458,
     459,   460,   461,   462,   463,   464,   464,   465,   465,   466,
     467,   467,   468,   469,   469,   469,   469,   470,   470,   471,
     471,   471,   472,   472,   472,   473,   473,   474,   474,   475,
     475,   476,   477,   477,   478,   478,   479,   480,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   480,   480,   481,
     481,   481,   481,   481,   481,   481,   481,   481,   481,   481,
     481,   481,   481,   481,   482,   482,   482,   482,   482,   482,
     483,   483,   483,   483,   483,   483,   484,   484,   484,   485,
     485,   486,   486,   486,   486,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   488,   488,   488,   488,   489,   489,   490,
     490,   491,   492,   492,   492,   493,   493,   494,   494,   495,
     495,   495,   496,   496,   496,   497,   497,   498,   498,   498,
     498,   498,   498,   498,   498,   498,   498,   498,   498,   498,
     498,   498,   499,   499,   499,   499,   499,   499,   499,   500,
     500,   501,   501,   502,   502,   502,   502,   503,   503,   504,
     504,   505,   505,   506,   507,   507,   507,   507,   507,   507,
     507,   507,   507,   507,   507,   507,   507,   507,   507,   507,
     508,   509,   509,   509,   510,   511,   511,   511,   512,   513,
     513,   513,   513,   514,   515,   515,   515,   515,   515,   516,
     517,   517,   517,   517,   517,   517,   517,   517,   517,   517,
     517,   517,   518,   519,   519,   519,   519,   519,   519,   519,
     520,   521,   521,   521,   521,   521,   521,   521,   521,   521,
     522,   523,   523,   523,   523,   523,   523,   523,   523,   524,
     525,   525,   525,   525,   525,   526,   527,   527,   528,   529,
     529,   529,   530,   531,   531,   531,   531,   532,   533,   533,
     533,   533,   534,   534,   534,   535,   535,   535,   535,   535,
     535,   535,   535,   535,   535,   536,   536,   536,   536,   536,
     536,   536,   536,   536,   536,   536,   536,   537,   537,   537,
     537,   537,   537,   537,   537,   538,   539,   539,   539,   540,
     541,   541,   541,   541,   542,   542,   542,   542,   542,   542,
     542,   543,   544,   544,   545,   546,   546,   546,   546,   547,
     548,   549,   550,   551,   552,   552,   552,   552,   552,   552,
     553,   554,   554,   555,   556,   556,   556,   556,   556,   557,
     558,   558,   558,   558,   558
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       2,     1,     1,     2,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       6,     2,     6,     3,     2,     6,     6,     3,     2,     3,
       3,     8,     3,     3,     2,     6,     2,     6,     6,     6,
       3,     2,     3,     3,     8,     3,     3,     2,     2,     2,
       2,     2,     3,     2,     2,     4,     2,     2,     2,     2,
       2,     2,     3,     2,     2,     3,     2,     2,     3,     2,
       2,     3,     2,     2,     3,     3,     2,     2,     2,     2,
       3,     4,     2,     3,     2,     2,     3,     2,     2,     2,
       2,     2,     3,     2,     2,     3,     2,     1,     1,     2,
       1,     1,     3,     0,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     1,     1,     2,     1,     0,
       2,     0,     2,     2,     3,     8,     8,     8,     8,     8,
       9,     8,     0,     0,     2,     2,     3,     3,     3,     0,
       0,     2,     2,     4,     4,     4,     4,     4,     2,     3,
       1,     1,     3,     1,     1,     1,     1,     0,     0,     2,
       2,     6,     6,     6,     6,     4,     4,     3,     2,     2,
       1,     1,     1,     1,     3,     0,     0,     2,     2,     2,
       0,     2,     2,     2,     0,     2,     2,     2,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     7,     1,     2,
       2,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     2,     1,     2,     1,     2,     2,     1,     2,     2,
       2,     0,     1,     1,     2,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       2,     1,     3,     3,     5,     1,     2,     1,     3,     1,
       2,     2,     2,     1,     2,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     1,     2,     2,     1,     1,     1,
       3,     1,     1,     1,     7,     6,     3,     1,     1,     0,
       1,     1,     0,     3,     5,     3,     1,     1,     0,     0,
       3,     3,     3,     1,     1,     1,     1,     1,     2,     1,
       0,     4,     4,     4,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     3,
       1,     1,     3,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     4,     2,     3,     2,
       2,     1,     1,     3,     4,     1,     2,     1,     1,     2,
       3,     1,     3,     4,     3,     5,     3,     1,     3,     1,
       1,     1,     1,     2,     1,     1,     2,     2,     1,     1,
       3,     1,     1,     1,     2,     1,     4,     1,     1,     6,
       1,     1,     1,     2,     2,     6,     1,     2,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     3,     3,     3,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     3,
       3,     3,     3,     5,     1,     2,     1,     1,     2,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     4,     1,     1,     1,     1,     5,     3,     0,
       6,     5,     1,     2,     2,     3,     5,     3,     3,     1,
       1,     1,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     3,     4,     1,     0,     2,     1,
       1,     5,     7,     5,     4,     1,     1,     2,     3,     1,
       1,     1,     2,     3,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     4,     5,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       6,     1,     1,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     2,     1,     1,     2,     1,
       1,     1,     2,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     2,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     2,     1,     1,     1,     1,     2,
       4,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     2,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1
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
          case 83: /* "string"  */
#line 255 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3500 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 84: /* "quoted string"  */
#line 255 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3506 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 85: /* "string with a trailing asterisk"  */
#line 255 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3512 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 288: /* line  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3518 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 289: /* base_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3524 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 290: /* add_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3530 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 291: /* replace_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3536 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 292: /* create_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3542 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 293: /* insert_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3548 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 294: /* delete_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3554 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 295: /* list_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3560 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 296: /* reset_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3566 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 297: /* flush_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3572 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 298: /* rename_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3578 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 299: /* import_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3584 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 300: /* export_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3590 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 301: /* monitor_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3596 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 302: /* monitor_event  */
#line 689 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3602 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 306: /* describe_cmd  */
#line 499 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 3608 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 307: /* table_block_alloc  */
#line 511 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 3614 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 310: /* chain_block_alloc  */
#line 513 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 3620 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 312: /* set_block_alloc  */
#line 522 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3626 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 314: /* set_block_expr  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3632 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 317: /* map_block_alloc  */
#line 525 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3638 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 321: /* data_type_atom_expr  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3644 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 322: /* data_type_expr  */
#line 493 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3650 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 323: /* obj_block_alloc  */
#line 528 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 3656 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 328: /* type_identifier  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3662 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 331: /* dev_spec  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3668 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 334: /* identifier  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3674 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* string  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3680 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* table_spec  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3686 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* chain_spec  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3692 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* chain_identifier  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3698 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 342: /* set_spec  */
#line 504 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3704 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* set_identifier  */
#line 504 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3710 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* obj_spec  */
#line 504 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3716 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 345: /* obj_identifier  */
#line 504 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3722 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* handle_spec  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3728 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* position_spec  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3734 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 348: /* rule_position  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3740 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 349: /* ruleid_spec  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3746 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* comment_spec  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3752 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 351: /* ruleset_spec  */
#line 502 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3758 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 352: /* rule  */
#line 515 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 3764 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* stmt_list  */
#line 531 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 3770 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 355: /* stmt  */
#line 533 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3776 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* verdict_stmt  */
#line 533 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3782 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 357: /* verdict_map_stmt  */
#line 602 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3788 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* verdict_map_expr  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3794 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 359: /* verdict_map_list_expr  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3800 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* verdict_map_list_member_expr  */
#line 605 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3806 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* counter_stmt  */
#line 535 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3812 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 362: /* counter_stmt_alloc  */
#line 535 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3818 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 365: /* log_stmt  */
#line 543 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3824 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 366: /* log_stmt_alloc  */
#line 543 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3830 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* limit_stmt  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3836 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* quota_unit  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3842 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* quota_stmt  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3848 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 381: /* reject_stmt  */
#line 549 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3854 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 382: /* reject_stmt_alloc  */
#line 549 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3860 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* nat_stmt  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3866 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* nat_stmt_alloc  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3872 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* primary_stmt_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3878 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* shift_stmt_expr  */
#line 591 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3884 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* and_stmt_expr  */
#line 593 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3890 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* exclusive_or_stmt_expr  */
#line 593 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3896 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* inclusive_or_stmt_expr  */
#line 593 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3902 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* basic_stmt_expr  */
#line 589 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3908 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 392: /* concat_stmt_expr  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3914 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 393: /* map_stmt_expr_set  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3920 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* map_stmt_expr  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3926 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* prefix_stmt_expr  */
#line 586 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3932 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 396: /* range_stmt_expr  */
#line 586 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3938 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* wildcard_stmt_expr  */
#line 586 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3944 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* multiton_stmt_expr  */
#line 584 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3950 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* stmt_expr  */
#line 581 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3956 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* masq_stmt  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3962 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* masq_stmt_alloc  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3968 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* redir_stmt  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3974 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* redir_stmt_alloc  */
#line 551 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3980 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 407: /* dup_stmt  */
#line 557 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3986 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* fwd_stmt  */
#line 559 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3992 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 411: /* queue_stmt  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3998 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 412: /* queue_stmt_alloc  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4004 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* set_elem_expr_stmt  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4010 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* set_elem_expr_stmt_alloc  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4016 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 419: /* set_stmt  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4022 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 421: /* meter_stmt  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4028 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* flow_stmt_legacy_alloc  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4034 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* meter_stmt_alloc  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4040 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* match_stmt  */
#line 533 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4046 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* variable_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4052 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* symbol_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4058 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* integer_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4064 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* primary_expr  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4070 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* fib_expr  */
#line 684 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4076 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* shift_expr  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4082 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 436: /* and_expr  */
#line 569 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4088 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* exclusive_or_expr  */
#line 571 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4094 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 438: /* inclusive_or_expr  */
#line 571 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4100 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 439: /* basic_expr  */
#line 573 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4106 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 440: /* concat_expr  */
#line 596 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4112 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 441: /* prefix_rhs_expr  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4118 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 442: /* range_rhs_expr  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4124 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* wildcard_rhs_expr  */
#line 578 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4130 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 444: /* multiton_rhs_expr  */
#line 576 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4136 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 445: /* map_expr  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4142 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 446: /* expr  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4148 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 447: /* set_expr  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4154 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 448: /* set_list_expr  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4160 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 449: /* set_list_member_expr  */
#line 608 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4166 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 450: /* meter_key_expr  */
#line 615 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4172 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* meter_key_expr_alloc  */
#line 615 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4178 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 452: /* set_elem_expr  */
#line 610 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4184 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 453: /* set_elem_expr_alloc  */
#line 610 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4190 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 456: /* set_lhs_expr  */
#line 610 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4196 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* set_rhs_expr  */
#line 610 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4202 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 458: /* initializer_expr  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4208 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* counter_config  */
#line 693 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).counter)); }
#line 4214 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* counter_obj  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4220 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 461: /* quota_config  */
#line 695 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).quota)); }
#line 4226 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* quota_obj  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4232 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* ct_obj_alloc  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4238 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 467: /* limit_config  */
#line 697 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).limit)); }
#line 4244 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* limit_obj  */
#line 628 "parser_bison.y" /* yacc.c:1257  */
      { obj_free(((*yyvaluep).obj)); }
#line 4250 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 469: /* relational_expr  */
#line 631 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4256 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* list_rhs_expr  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4262 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 471: /* rhs_expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4268 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* shift_rhs_expr  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4274 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 473: /* and_rhs_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4280 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 474: /* exclusive_or_rhs_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4286 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 475: /* inclusive_or_rhs_expr  */
#line 625 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4292 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 476: /* basic_rhs_expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4298 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 477: /* concat_rhs_expr  */
#line 621 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4304 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 479: /* boolean_expr  */
#line 705 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4310 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 480: /* keyword_expr  */
#line 618 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4316 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 481: /* primary_rhs_expr  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4322 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 483: /* verdict_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4328 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 484: /* meta_expr  */
#line 672 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4334 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 488: /* meta_stmt  */
#line 541 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4340 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 491: /* numgen_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4346 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 492: /* hash_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4352 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 494: /* rt_expr  */
#line 676 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4358 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 496: /* ct_expr  */
#line 680 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4364 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 503: /* symbol_stmt_expr  */
#line 623 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4370 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 504: /* list_stmt_expr  */
#line 591 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4376 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 505: /* ct_stmt  */
#line 539 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4382 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 506: /* payload_stmt  */
#line 537 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 4388 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 507: /* payload_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4394 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 508: /* payload_raw_expr  */
#line 635 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4400 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 510: /* eth_hdr_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4406 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 512: /* vlan_hdr_expr  */
#line 638 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4412 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 514: /* arp_hdr_expr  */
#line 641 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4418 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 516: /* ip_hdr_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4424 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 518: /* icmp_hdr_expr  */
#line 644 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4430 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 520: /* ip6_hdr_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4436 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 522: /* icmp6_hdr_expr  */
#line 647 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4442 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 524: /* auth_hdr_expr  */
#line 650 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4448 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 526: /* esp_hdr_expr  */
#line 650 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4454 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 528: /* comp_hdr_expr  */
#line 650 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4460 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 530: /* udp_hdr_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4466 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 532: /* udplite_hdr_expr  */
#line 653 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4472 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 534: /* tcp_hdr_expr  */
#line 700 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4478 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 538: /* dccp_hdr_expr  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4484 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 540: /* sctp_hdr_expr  */
#line 656 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4490 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 542: /* exthdr_expr  */
#line 660 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4496 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 543: /* hbh_hdr_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4502 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 545: /* rt_hdr_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4508 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 547: /* rt0_hdr_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4514 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 549: /* rt2_hdr_expr  */
#line 665 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4520 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 551: /* frag_hdr_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4526 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 553: /* dst_hdr_expr  */
#line 662 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4532 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 555: /* mh_hdr_expr  */
#line 668 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4538 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 557: /* exthdr_exists_expr  */
#line 709 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 4544 "parser_bison.c" /* yacc.c:1257  */
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

#line 4661 "parser_bison.c" /* yacc.c:1429  */
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
#line 718 "parser_bison.y" /* yacc.c:1646  */
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
#line 4864 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 8:
#line 744 "parser_bison.y" /* yacc.c:1646  */
    {
				if (scanner_include_file(nft, scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 4876 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 9:
#line 752 "parser_bison.y" /* yacc.c:1646  */
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
#line 4894 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 766 "parser_bison.y" /* yacc.c:1646  */
    {
				if (++state->nerrs == nft->parser_max_errors)
					YYABORT;
				yyerrok;
			}
#line 4904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 11:
#line 773 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 4910 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 774 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 4916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 775 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 4922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 777 "parser_bison.y" /* yacc.c:1646  */
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
#line 4956 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 808 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 16:
#line 809 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 810 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4974 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 811 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4980 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 812 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4986 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 813 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4992 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 814 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4998 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 815 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5004 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 816 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5010 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 817 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5016 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 818 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5022 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 819 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 820 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 821 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 5040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 825 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5048 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 830 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 836 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 841 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5077 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 848 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5085 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 852 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5093 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 857 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 864 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5113 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 870 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5121 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 874 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5134 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 883 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5142 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 887 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5150 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 891 "parser_bison.y" /* yacc.c:1646  */
    {

				(yyval.cmd) = cmd_alloc_obj_ct(CMD_ADD, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 42:
#line 896 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5167 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 902 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5175 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 908 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 913 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 5193 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 919 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 924 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 5212 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 932 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5222 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 939 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 5232 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 945 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5240 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 949 "parser_bison.y" /* yacc.c:1646  */
    {
				struct obj *obj;

				obj = obj_alloc(&(yyloc));
				obj->type = NFT_OBJECT_COUNTER;
				handle_merge(&obj->handle, &(yyvsp[0].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), obj);
			}
#line 5253 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 958 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_COUNTER, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5261 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 962 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_QUOTA, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5269 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 966 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_CREATE, NFT_OBJECT_CT_HELPER, &(yyvsp[-5].handle), &(yyloc), (yyvsp[-4].obj));
			}
#line 5277 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 970 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_LIMIT, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5285 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 56:
#line 976 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 5293 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 982 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5301 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 986 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5309 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 990 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5317 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 994 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5325 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 998 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5333 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1002 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 5341 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1006 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5349 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1010 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5357 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1014 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_DELETE, (yyvsp[-2].val), &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].obj));
			}
#line 5365 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1018 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1024 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5381 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1028 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5389 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1032 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1036 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5405 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1040 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5413 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1044 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5421 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1048 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1052 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5437 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1056 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5445 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1060 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_COUNTER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5453 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1064 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5461 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1068 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5469 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1072 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5477 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1076 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5485 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1080 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMITS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5493 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1084 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_LIMIT, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5501 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1088 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5509 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1092 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5517 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1096 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5525 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1100 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5533 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1104 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5541 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1108 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5549 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1112 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5557 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1116 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc_obj_ct(CMD_LIST, (yyvsp[-1].val), &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5565 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1120 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CT_HELPERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5573 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1126 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5581 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1130 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTERS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5589 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1134 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_COUNTER, &(yyvsp[0].handle),&(yyloc), NULL);
			}
#line 5597 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1138 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5605 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1142 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTAS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1146 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RESET, CMD_OBJ_QUOTA, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5621 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1152 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5629 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1156 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5637 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1160 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5645 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1164 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5653 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1168 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1172 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_METER, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1176 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 5677 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1182 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 5686 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1189 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 5696 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1195 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_IMPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 5706 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1200 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 5712 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1204 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 5722 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1210 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct markup *markup = markup_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_MARKUP, &h, &(yyloc), markup);
			}
#line 5732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1215 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 5738 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1219 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 5749 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1227 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 5755 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1228 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 5761 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1231 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 5767 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1232 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 5773 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1233 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 5779 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1234 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 5785 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1235 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 5791 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1236 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 5797 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1237 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULESET; }
#line 5803 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1238 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TRACE; }
#line 5809 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1241 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 5815 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1243 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 5821 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1246 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_XML; }
#line 5827 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1247 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 5833 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1251 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 5843 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1259 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 5852 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1266 "parser_bison.y" /* yacc.c:1646  */
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
#line 5868 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1279 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 5874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1286 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5887 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1297 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5899 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1307 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5911 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1317 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_COUNTER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5924 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1328 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_QUOTA;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5937 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1337 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_CT_HELPER;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-8].table)->objs);
				(yyval.table) = (yyvsp[-8].table);
			}
#line 5950 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1348 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].obj)->location = (yylsp[-5]);
				(yyvsp[-4].obj)->type = NFT_OBJECT_LIMIT;
				handle_merge(&(yyvsp[-4].obj)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].obj)->list, &(yyvsp[-7].table)->objs);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 5963 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1359 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 5972 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1365 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 5978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1371 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 5987 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1378 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 5995 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1383 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6001 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1387 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->key = (yyvsp[-1].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6010 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1392 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6019 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1397 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1402 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6037 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1407 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1412 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->automerge = true;
				(yyval.set) = (yyvsp[-1].set);
			}
#line 6055 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1424 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6063 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1430 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_CONSTANT; }
#line 6069 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1431 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_INTERVAL; }
#line 6075 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1432 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_TIMEOUT; }
#line 6081 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1436 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 6089 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1441 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 6095 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1447 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].expr)->dtype;

				expr_free((yyvsp[-1].expr));
				(yyvsp[-5].set)->flags |= NFT_SET_MAP;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6108 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1458 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_COUNTER;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6119 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1467 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_QUOTA;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1476 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->key = (yyvsp[-3].expr);
				(yyvsp[-5].set)->objtype = NFT_OBJECT_LIMIT;
				(yyvsp[-5].set)->flags  |= NFT_SET_OBJECT;
				(yyval.set) = (yyvsp[-5].set);
			}
#line 6141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1483 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6150 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1488 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 6159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1496 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 6167 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1500 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 6175 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1505 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 6181 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1506 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 6187 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1510 "parser_bison.y" /* yacc.c:1646  */
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
#line 6203 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1525 "parser_bison.y" /* yacc.c:1646  */
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
#line 6224 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1544 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(NULL);
			}
#line 6232 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1549 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6238 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1553 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->counter = *(yyvsp[0].counter);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1559 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6253 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1563 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->quota = *(yyvsp[0].quota);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6262 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1569 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6268 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1573 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1578 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[(-1) - (0)].obj); }
#line 6282 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1582 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].obj)->limit = *(yyvsp[0].limit);
				(yyval.obj) = (yyvsp[-1].obj);
			}
#line 6291 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1588 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6297 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1589 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("mark"); }
#line 6303 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1590 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("dscp"); }
#line 6309 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1591 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("ecn"); }
#line 6315 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1592 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("classid"); }
#line 6321 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1596 "parser_bison.y" /* yacc.c:1646  */
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
#line 6351 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1623 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 6357 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1624 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = -(yyvsp[0].val); }
#line 6363 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1627 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6369 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1628 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 6375 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1632 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].chain)->policy != -1) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].val);
			}
#line 6388 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1642 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_ACCEPT; }
#line 6394 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1643 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_DROP;   }
#line 6400 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1655 "parser_bison.y" /* yacc.c:1646  */
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
#line 6417 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1669 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1673 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 6429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1674 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 6435 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1675 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_INET; }
#line 6441 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1676 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_ARP; }
#line 6447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1677 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 6453 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1678 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 6459 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1682 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table	= (yyvsp[0].string);
			}
#line 6469 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1690 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 6478 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1697 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 6487 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1704 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 6496 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1711 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 6505 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1718 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).obj		= (yyvsp[0].string);
			}
#line 6514 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1725 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).obj		= (yyvsp[0].string);
			}
#line 6523 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1732 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 6533 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1740 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 6543 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1748 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 6551 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1752 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 6560 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1759 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 6569 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1766 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strlen((yyvsp[0].string)) > UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed", UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 6582 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1777 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 6591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1782 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 6600 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1789 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 6608 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1793 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 6616 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1799 "parser_bison.y" /* yacc.c:1646  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 6630 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1811 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 6640 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1817 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 6649 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1844 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 6657 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1848 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 6665 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1854 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6673 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1860 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6682 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1865 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 6693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1874 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 6702 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1879 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 6711 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1887 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 6719 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1896 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 6727 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1900 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_COUNTER;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 6737 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1908 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 6745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1915 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 6753 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1919 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 6761 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1929 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 6769 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1935 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 6777 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1942 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 6786 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1947 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 6795 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1952 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 6804 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1957 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 6813 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1962 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 6822 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1967 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 6830 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1973 "parser_bison.y" /* yacc.c:1646  */
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
#line 6860 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 295:
#line 2001 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 6868 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 296:
#line 2005 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 6876 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 297:
#line 2009 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 6884 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 298:
#line 2013 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 6892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 299:
#line 2017 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 6900 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 300:
#line 2023 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6908 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 302:
#line 2030 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 6916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 303:
#line 2034 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 6924 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2040 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 6937 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2049 "parser_bison.y" /* yacc.c:1646  */
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
#line 6960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2068 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_LIMIT;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 6970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2075 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 6976 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 308:
#line 2076 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6982 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 309:
#line 2077 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 6988 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 310:
#line 2080 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("bytes"); }
#line 6994 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 311:
#line 2081 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 7000 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 312:
#line 2084 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7006 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 313:
#line 2086 "parser_bison.y" /* yacc.c:1646  */
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
#line 7023 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 314:
#line 2101 "parser_bison.y" /* yacc.c:1646  */
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
#line 7043 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 315:
#line 2117 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = objref_stmt_alloc(&(yyloc));
				(yyval.stmt)->objref.type = NFT_OBJECT_QUOTA;
				(yyval.stmt)->objref.expr = (yyvsp[0].expr);
			}
#line 7053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 316:
#line 2124 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 7059 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 317:
#line 2125 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7065 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 318:
#line 2126 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7071 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 319:
#line 2129 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7077 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2130 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 7083 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 321:
#line 2131 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 7089 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 322:
#line 2133 "parser_bison.y" /* yacc.c:1646  */
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
#line 7106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2147 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL; }
#line 7112 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2148 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60; }
#line 7118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2149 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 7124 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2150 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 7130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2151 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 7136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 329:
#line 2158 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 7144 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2164 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 7153 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2169 "parser_bison.y" /* yacc.c:1646  */
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
#line 7168 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2180 "parser_bison.y" /* yacc.c:1646  */
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
#line 7183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2191 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpx_code_type;
				xfree((yyvsp[0].string));
			}
#line 7197 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2201 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
#line 7205 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2210 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_SNAT;
			}
#line 7214 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2215 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_DNAT;
			}
#line 7223 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2221 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7229 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2222 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7235 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2223 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7241 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2224 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7247 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2225 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7253 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2226 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7259 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2227 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7265 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2228 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7271 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2229 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7277 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2230 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7283 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 349:
#line 2235 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7291 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 350:
#line 2239 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7299 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 352:
#line 2246 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7307 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 354:
#line 2253 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7315 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 356:
#line 2260 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7323 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2270 "parser_bison.y" /* yacc.c:1646  */
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
#line 7344 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2293 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7352 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 363:
#line 2296 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7358 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 364:
#line 2300 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 7366 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2306 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7374 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2312 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 7387 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2333 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7395 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2337 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 7403 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2341 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7412 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2346 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7421 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2351 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2355 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 7437 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2359 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 7445 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2368 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = masq_stmt_alloc(&(yyloc)); }
#line 7451 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2372 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->masq.proto = (yyvsp[0].expr);
			}
#line 7459 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2376 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->masq.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 7468 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2381 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 7476 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2390 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = redir_stmt_alloc(&(yyloc)); }
#line 7482 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 389:
#line 2394 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 7490 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 390:
#line 2398 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 7498 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2402 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7506 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 392:
#line 2406 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7515 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 393:
#line 2411 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 7524 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2418 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 7533 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2423 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 7543 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2431 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.to = (yyvsp[0].expr);
			}
#line 7552 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2439 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7560 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2444 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 7566 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2445 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 7572 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2446 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 7578 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 404:
#line 2454 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 7586 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 405:
#line 2460 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7594 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 407:
#line 2467 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 7603 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2472 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 7611 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2479 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7619 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2484 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 7625 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2485 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 7631 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2493 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 7639 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2499 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 7650 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2507 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 7656 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2508 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 7662 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2512 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->meter.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 7673 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2518 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 7679 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2522 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
			}
#line 7687 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2528 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 7695 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2535 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->meter.name = (yyvsp[0].string);
			}
#line 7703 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2541 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meter_stmt_alloc(&(yyloc));
				(yyval.stmt)->meter.name = (yyvsp[-4].string);
				(yyval.stmt)->meter.key  = (yyvsp[-2].expr);
				(yyval.stmt)->meter.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
			}
#line 7715 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2551 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 7723 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2557 "parser_bison.y" /* yacc.c:1646  */
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
#line 7742 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2575 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7753 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2582 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 7764 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2591 "parser_bison.y" /* yacc.c:1646  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 7777 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2601 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7783 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2602 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7789 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2603 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7795 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2604 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7801 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2605 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7807 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2606 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7813 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2607 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7819 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2608 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7825 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2609 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7831 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2610 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7837 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2611 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 7843 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2612 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 7849 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2616 "parser_bison.y" /* yacc.c:1646  */
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
#line 7874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2638 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 7880 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2639 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 7886 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2640 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 7892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 448:
#line 2643 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 7898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2644 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 7904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2645 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 7910 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2646 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 7916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2647 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 7922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2651 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 7930 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2659 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7938 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2663 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7946 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2670 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2677 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 463:
#line 2684 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 466:
#line 2694 "parser_bison.y" /* yacc.c:1646  */
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
#line 7991 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2713 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 7999 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2719 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2725 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 8020 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2741 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2752 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8037 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2759 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc), NULL);
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2764 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8055 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2772 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8063 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2776 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8071 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2780 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 8079 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2787 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 8088 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2794 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 489:
#line 2804 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 8104 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2810 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 8112 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 492:
#line 2817 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val) * 1000;
			}
#line 8120 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2821 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 8128 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 500:
#line 2839 "parser_bison.y" /* yacc.c:1646  */
    {
				struct counter *counter;

				counter = xzalloc(sizeof(*counter));
				counter->packets = (yyvsp[-2].val);
				counter->bytes = (yyvsp[0].val);
				(yyval.counter) = counter;
			}
#line 8141 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2850 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_COUNTER;
				(yyval.obj)->counter = *(yyvsp[0].counter);
			}
#line 8151 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2858 "parser_bison.y" /* yacc.c:1646  */
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
#line 8174 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 503:
#line 2879 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_QUOTA;
				(yyval.obj)->quota = *(yyvsp[0].quota);
			}
#line 8184 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 504:
#line 2886 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_OBJECT_CT_HELPER; }
#line 8190 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 505:
#line 2889 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_TCP; }
#line 8196 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 506:
#line 2890 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_UDP; }
#line 8202 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 507:
#line 2894 "parser_bison.y" /* yacc.c:1646  */
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
#line 8221 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 508:
#line 2909 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].obj)->ct_helper.l3proto = (yyvsp[-1].val);
			}
#line 8229 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 509:
#line 2915 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
			}
#line 8237 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 510:
#line 2921 "parser_bison.y" /* yacc.c:1646  */
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
#line 8252 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 511:
#line 2932 "parser_bison.y" /* yacc.c:1646  */
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
#line 8276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 512:
#line 2954 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.obj) = obj_alloc(&(yyloc));
				(yyval.obj)->type = NFT_OBJECT_LIMIT;
				(yyval.obj)->limit = *(yyvsp[0].limit);
			}
#line 8286 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 513:
#line 2962 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8294 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 514:
#line 2966 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_FLAGCMP, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 8302 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 515:
#line 2970 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8310 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 516:
#line 2974 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-3]), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[-1].expr));
			}
#line 8318 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 517:
#line 2980 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 8328 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 518:
#line 2986 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 8338 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 519:
#line 2993 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8344 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 520:
#line 2994 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8350 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 521:
#line 2995 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8356 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 523:
#line 3000 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8364 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 524:
#line 3004 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8372 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 526:
#line 3011 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8380 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 528:
#line 3018 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8388 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 530:
#line 3025 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 8396 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 533:
#line 3035 "parser_bison.y" /* yacc.c:1646  */
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
#line 8417 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 534:
#line 3053 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = true; }
#line 8423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 535:
#line 3054 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = false; }
#line 8429 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 536:
#line 3058 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = constant_expr_alloc(&(yyloc), &boolean_type,
							 BYTEORDER_HOST_ENDIAN,
							 1, &(yyvsp[0].val));
			}
#line 8439 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 537:
#line 3065 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ether"); }
#line 8445 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 538:
#line 3066 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip"); }
#line 8451 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 539:
#line 3067 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ip6"); }
#line 8457 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 540:
#line 3068 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "vlan"); }
#line 8463 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 541:
#line 3069 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "arp"); }
#line 8469 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 542:
#line 3070 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "dnat"); }
#line 8475 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 543:
#line 3071 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "snat"); }
#line 8481 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 544:
#line 3072 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "ecn"); }
#line 8487 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 545:
#line 3073 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reset"); }
#line 8493 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 546:
#line 3074 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "original"); }
#line 8499 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 547:
#line 3075 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "reply"); }
#line 8505 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 548:
#line 3076 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = symbol_value(&(yyloc), "label"); }
#line 8511 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 549:
#line 3079 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8517 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 550:
#line 3080 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8523 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 551:
#line 3081 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8529 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 552:
#line 3082 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 8535 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 553:
#line 3084 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8546 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 554:
#line 3091 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8557 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 555:
#line 3098 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8568 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 556:
#line 3105 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8579 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 557:
#line 3112 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8590 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 558:
#line 3119 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8601 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 559:
#line 3126 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8612 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 560:
#line 3133 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8623 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 561:
#line 3140 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8634 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 562:
#line 3147 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8645 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 563:
#line 3154 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 8656 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 564:
#line 3162 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_EQ; }
#line 8662 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 565:
#line 3163 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_NEQ; }
#line 8668 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 566:
#line 3164 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LT; }
#line 8674 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 567:
#line 3165 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GT; }
#line 8680 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 568:
#line 3166 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GTE; }
#line 8686 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 569:
#line 3167 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LTE; }
#line 8692 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 570:
#line 3171 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 8700 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 571:
#line 3175 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 8708 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 572:
#line 3179 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 8716 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 573:
#line 3183 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].string));
			}
#line 8724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 574:
#line 3187 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].string));
			}
#line 8732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 575:
#line 3191 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 8740 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 576:
#line 3197 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 8748 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 577:
#line 3201 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 8756 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 578:
#line 3205 "parser_bison.y" /* yacc.c:1646  */
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
#line 8774 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 581:
#line 3223 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_LEN; }
#line 8780 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 582:
#line 3224 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 8786 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 583:
#line 3225 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 8792 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 584:
#line 3226 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 8798 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 585:
#line 3229 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_MARK; }
#line 8804 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 586:
#line 3230 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIF; }
#line 8810 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 587:
#line 3231 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 8816 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 588:
#line 3232 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 8822 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 589:
#line 3233 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIF; }
#line 8828 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 590:
#line 3234 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 8834 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 591:
#line 3235 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 8840 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 592:
#line 3236 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKUID; }
#line 8846 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 593:
#line 3237 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKGID; }
#line 8852 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 594:
#line 3238 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 8858 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 595:
#line 3239 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 8864 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 596:
#line 3240 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 8870 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 597:
#line 3241 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 8876 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 598:
#line 3242 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 8882 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 599:
#line 3243 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CPU; }
#line 8888 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 600:
#line 3244 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 8894 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 601:
#line 3245 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 8900 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 602:
#line 3246 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 8906 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 603:
#line 3250 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 8914 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 604:
#line 3254 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 8922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 605:
#line 3258 "parser_bison.y" /* yacc.c:1646  */
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
#line 8940 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 606:
#line 3272 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 8948 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 607:
#line 3277 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 8954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 608:
#line 3278 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 8960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 609:
#line 3281 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 8966 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 610:
#line 3282 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 8972 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 611:
#line 3286 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 8980 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 612:
#line 3292 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), true, (yyvsp[-1].val), (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 8989 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 613:
#line 3297 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_JENKINS);
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 8998 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 614:
#line 3302 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), false, 0, (yyvsp[0].val), NFT_HASH_SYM);
			}
#line 9006 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 615:
#line 3307 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 9012 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 616:
#line 3308 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 9018 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 617:
#line 3312 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 9026 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 618:
#line 3316 "parser_bison.y" /* yacc.c:1646  */
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
#line 9048 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 619:
#line 3335 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 9054 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 620:
#line 3336 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 9060 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 621:
#line 3337 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_TCPMSS; }
#line 9066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 622:
#line 3341 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1, NFPROTO_UNSPEC);
			}
#line 9074 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 623:
#line 3345 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-1].val), NFPROTO_UNSPEC);
			}
#line 9082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 624:
#line 3349 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), (yyvsp[-2].val), (yyvsp[-1].val));
			}
#line 9090 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 625:
#line 3354 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_ORIGINAL; }
#line 9096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 626:
#line 3355 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP_CT_DIR_REPLY; }
#line 9102 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 627:
#line 3358 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9108 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 628:
#line 3359 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9114 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 629:
#line 3360 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_MARK; }
#line 9120 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 630:
#line 3361 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATE; }
#line 9126 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 631:
#line 3362 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 9132 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 632:
#line 3363 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 9138 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 633:
#line 3364 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 9144 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 634:
#line 3365 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 9150 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 635:
#line 3366 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9156 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 636:
#line 3367 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9162 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 637:
#line 3368 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9168 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 638:
#line 3369 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9174 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3370 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 9180 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 640:
#line 3371 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EVENTMASK; }
#line 9186 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 642:
#line 3375 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9192 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3376 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9198 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 644:
#line 3377 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 9204 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 645:
#line 3378 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 9210 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 646:
#line 3379 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 9216 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 647:
#line 3380 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 9222 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 649:
#line 3384 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 9228 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 650:
#line 3385 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 9234 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 651:
#line 3388 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 9240 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 652:
#line 3389 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 9246 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 653:
#line 3392 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 9252 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 654:
#line 3393 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 9258 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 655:
#line 3394 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_AVGPKT; }
#line 9264 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 656:
#line 3395 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_ZONE; }
#line 9270 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 659:
#line 3403 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 9280 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 660:
#line 3409 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 9290 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 661:
#line 3417 "parser_bison.y" /* yacc.c:1646  */
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
#line 9307 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 662:
#line 3430 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[0].expr));
			}
#line 9315 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 663:
#line 3436 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].expr)->ops->type == EXPR_EXTHDR)
					(yyval.stmt) = exthdr_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
				else
					(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 9326 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 680:
#line 3463 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				(yyval.expr)->payload.base	= (yyvsp[-4].val);
				(yyval.expr)->payload.offset	= (yyvsp[-2].val);
				(yyval.expr)->len			= (yyvsp[0].val);
				(yyval.expr)->dtype		= &integer_type;
			}
#line 9338 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 681:
#line 3472 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 9344 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 682:
#line 3473 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 9350 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 683:
#line 3474 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 9356 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 684:
#line 3478 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 9364 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 685:
#line 3483 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 9370 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 686:
#line 3484 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 9376 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 687:
#line 3485 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 9382 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 688:
#line 3489 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 9390 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 689:
#line 3494 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_VID; }
#line 9396 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 690:
#line 3495 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_CFI; }
#line 9402 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 691:
#line 3496 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_PCP; }
#line 9408 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 692:
#line 3497 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 9414 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 693:
#line 3501 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 9422 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 694:
#line 3506 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HRD; }
#line 9428 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 695:
#line 3507 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PRO; }
#line 9434 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 696:
#line 3508 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HLN; }
#line 9440 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 697:
#line 3509 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PLN; }
#line 9446 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 698:
#line 3510 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_OP; }
#line 9452 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 699:
#line 3514 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 9460 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 700:
#line 3519 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_VERSION; }
#line 9466 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 701:
#line 3520 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 9472 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 702:
#line 3521 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DSCP; }
#line 9478 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 703:
#line 3522 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ECN; }
#line 9484 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 704:
#line 3523 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 9490 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 705:
#line 3524 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ID; }
#line 9496 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 706:
#line 3525 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 9502 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 707:
#line 3526 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_TTL; }
#line 9508 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 708:
#line 3527 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 9514 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 709:
#line 3528 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 9520 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 710:
#line 3529 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_SADDR; }
#line 9526 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 711:
#line 3530 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DADDR; }
#line 9532 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 712:
#line 3534 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 9540 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 713:
#line 3539 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 9546 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 714:
#line 3540 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 9552 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 715:
#line 3541 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 9558 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 716:
#line 3542 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_ID; }
#line 9564 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 717:
#line 3543 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 9570 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 718:
#line 3544 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 9576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 719:
#line 3545 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 9582 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 720:
#line 3549 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 9590 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 721:
#line 3554 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 9596 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 722:
#line 3555 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 9602 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 723:
#line 3556 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_ECN; }
#line 9608 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 724:
#line 3557 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 9614 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 725:
#line 3558 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 9620 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 726:
#line 3559 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 9626 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 727:
#line 3560 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 9632 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 728:
#line 3561 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 9638 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 729:
#line 3562 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 9644 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 730:
#line 3565 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 9652 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 731:
#line 3570 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 9658 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 732:
#line 3571 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 9664 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 733:
#line 3572 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 9670 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 734:
#line 3573 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 9676 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 735:
#line 3574 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 9682 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 736:
#line 3575 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 9688 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 737:
#line 3576 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 9694 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 738:
#line 3577 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 9700 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 739:
#line 3581 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 9708 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 740:
#line 3586 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 9714 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 741:
#line 3587 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 9720 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 742:
#line 3588 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 9726 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 743:
#line 3589 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SPI; }
#line 9732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 744:
#line 3590 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 9738 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 745:
#line 3594 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 9746 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 746:
#line 3599 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SPI; }
#line 9752 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 747:
#line 3600 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 9758 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 748:
#line 3604 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 9766 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 749:
#line 3609 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 9772 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 750:
#line 3610 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 9778 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 751:
#line 3611 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_CPI; }
#line 9784 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 752:
#line 3615 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 9792 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 753:
#line 3620 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 9798 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 754:
#line 3621 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 9804 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 755:
#line 3622 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 9810 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 756:
#line 3623 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 9816 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 757:
#line 3627 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 9824 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 758:
#line 3632 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 9830 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 759:
#line 3633 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 9836 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 760:
#line 3634 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 9842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 761:
#line 3635 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 9848 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 762:
#line 3639 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 9856 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 763:
#line 3643 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 9864 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 764:
#line 3647 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = tcpopt_expr_alloc(&(yyloc), (yyvsp[0].val), TCPOPTHDR_FIELD_KIND);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 9873 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 765:
#line 3653 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 9879 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 766:
#line 3654 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 9885 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 767:
#line 3655 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 9891 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 768:
#line 3656 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 9897 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 769:
#line 3657 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 9903 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 770:
#line 3658 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 9909 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 771:
#line 3659 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 9915 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 772:
#line 3660 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 9921 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 773:
#line 3661 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 9927 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 774:
#line 3662 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 9933 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 775:
#line 3665 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_EOL; }
#line 9939 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 776:
#line 3666 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_NOOP; }
#line 9945 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 777:
#line 3667 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_MAXSEG; }
#line 9951 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 778:
#line 3668 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_WINDOW; }
#line 9957 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 779:
#line 3669 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK_PERMITTED; }
#line 9963 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 780:
#line 3670 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 9969 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 781:
#line 3671 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK0; }
#line 9975 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 782:
#line 3672 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK1; }
#line 9981 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 783:
#line 3673 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK2; }
#line 9987 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 784:
#line 3674 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_SACK3; }
#line 9993 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 785:
#line 3675 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_ECHO; }
#line 9999 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 786:
#line 3676 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_TIMESTAMP; }
#line 10005 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 787:
#line 3679 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_KIND; }
#line 10011 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 788:
#line 3680 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LENGTH; }
#line 10017 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 789:
#line 3681 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_SIZE; }
#line 10023 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 790:
#line 3682 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_COUNT; }
#line 10029 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 791:
#line 3683 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_LEFT; }
#line 10035 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 792:
#line 3684 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_RIGHT; }
#line 10041 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 793:
#line 3685 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSVAL; }
#line 10047 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 794:
#line 3686 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPOPTHDR_FIELD_TSECR; }
#line 10053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 795:
#line 3690 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 10061 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 796:
#line 3695 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 10067 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 797:
#line 3696 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 10073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 798:
#line 3697 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 10079 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 799:
#line 3701 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 10087 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 800:
#line 3706 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 10093 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 801:
#line 3707 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 10099 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 802:
#line 3708 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 10105 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 803:
#line 3709 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 10111 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 811:
#line 3722 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 10119 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 812:
#line 3727 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 10125 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 813:
#line 3728 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 10131 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 814:
#line 3732 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 10139 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 815:
#line 3737 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 10145 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 816:
#line 3738 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 10151 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 817:
#line 3739 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_TYPE; }
#line 10157 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 818:
#line 3740 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 10163 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 819:
#line 3744 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 10171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 820:
#line 3750 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 10179 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 821:
#line 3756 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 10187 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 822:
#line 3761 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 10193 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 823:
#line 3765 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 10201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 824:
#line 3770 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 10207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 825:
#line 3771 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 10213 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 826:
#line 3772 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 10219 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 827:
#line 3773 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 10225 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 828:
#line 3774 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 10231 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 829:
#line 3775 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_ID; }
#line 10237 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 830:
#line 3779 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 10245 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 831:
#line 3784 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 10251 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 832:
#line 3785 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 10257 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 833:
#line 3789 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 10265 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 834:
#line 3794 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 10271 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 835:
#line 3795 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 10277 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 836:
#line 3796 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_TYPE; }
#line 10283 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 837:
#line 3797 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 10289 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 838:
#line 3798 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 10295 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 839:
#line 3802 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct exthdr_desc *desc;

				desc = exthdr_find_proto((yyvsp[0].val));

				/* Assume that NEXTHDR template is always
				 * the fist one in list of templates.
				 */
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), desc, 1);
				(yyval.expr)->exthdr.flags = NFT_EXTHDR_F_PRESENT;
			}
#line 10311 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 840:
#line 3815 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_HOPOPTS; }
#line 10317 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 841:
#line 3816 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_ROUTING; }
#line 10323 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 842:
#line 3817 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_FRAGMENT; }
#line 10329 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 843:
#line 3818 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_DSTOPTS; }
#line 10335 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 844:
#line 3819 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPPROTO_MH; }
#line 10341 "parser_bison.c" /* yacc.c:1646  */
    break;


#line 10345 "parser_bison.c" /* yacc.c:1646  */
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
#line 3822 "parser_bison.y" /* yacc.c:1906  */

