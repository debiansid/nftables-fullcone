/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

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

void parser_init(struct parser_state *state, struct list_head *msgs)
{
	memset(state, 0, sizeof(*state));
	init_list_head(&state->cmds);
	init_list_head(&state->top_scope.symbols);
	state->msgs = msgs;
	state->scopes[0] = scope_init(&state->top_scope, NULL);
	state->ectx.msgs = msgs;
}

static void yyerror(struct location *loc, void *scanner,
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


#line 163 "parser_bison.c" /* yacc.c:339  */

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
    INET = 299,
    NETDEV = 300,
    ADD = 301,
    UPDATE = 302,
    REPLACE = 303,
    CREATE = 304,
    INSERT = 305,
    DELETE = 306,
    LIST = 307,
    FLUSH = 308,
    RENAME = 309,
    DESCRIBE = 310,
    EXPORT = 311,
    MONITOR = 312,
    ALL = 313,
    ACCEPT = 314,
    DROP = 315,
    CONTINUE = 316,
    JUMP = 317,
    GOTO = 318,
    RETURN = 319,
    TO = 320,
    CONSTANT = 321,
    INTERVAL = 322,
    TIMEOUT = 323,
    GC_INTERVAL = 324,
    ELEMENTS = 325,
    POLICY = 326,
    MEMORY = 327,
    PERFORMANCE = 328,
    SIZE = 329,
    FLOW = 330,
    NUM = 331,
    STRING = 332,
    QUOTED_STRING = 333,
    ASTERISK_STRING = 334,
    LL_HDR = 335,
    NETWORK_HDR = 336,
    TRANSPORT_HDR = 337,
    BRIDGE = 338,
    ETHER = 339,
    SADDR = 340,
    DADDR = 341,
    TYPE = 342,
    VLAN = 343,
    ID = 344,
    CFI = 345,
    PCP = 346,
    ARP = 347,
    HTYPE = 348,
    PTYPE = 349,
    HLEN = 350,
    PLEN = 351,
    OPERATION = 352,
    IP = 353,
    HDRVERSION = 354,
    HDRLENGTH = 355,
    DSCP = 356,
    ECN = 357,
    LENGTH = 358,
    FRAG_OFF = 359,
    TTL = 360,
    PROTOCOL = 361,
    CHECKSUM = 362,
    ICMP = 363,
    CODE = 364,
    SEQUENCE = 365,
    GATEWAY = 366,
    MTU = 367,
    OPTIONS = 368,
    IP6 = 369,
    PRIORITY = 370,
    FLOWLABEL = 371,
    NEXTHDR = 372,
    HOPLIMIT = 373,
    ICMP6 = 374,
    PPTR = 375,
    MAXDELAY = 376,
    AH = 377,
    RESERVED = 378,
    SPI = 379,
    ESP = 380,
    COMP = 381,
    FLAGS = 382,
    CPI = 383,
    UDP = 384,
    SPORT = 385,
    DPORT = 386,
    UDPLITE = 387,
    CSUMCOV = 388,
    TCP = 389,
    ACKSEQ = 390,
    DOFF = 391,
    WINDOW = 392,
    URGPTR = 393,
    DCCP = 394,
    SCTP = 395,
    VTAG = 396,
    RT = 397,
    RT0 = 398,
    RT2 = 399,
    SEG_LEFT = 400,
    ADDR = 401,
    HBH = 402,
    FRAG = 403,
    RESERVED2 = 404,
    MORE_FRAGMENTS = 405,
    DST = 406,
    MH = 407,
    META = 408,
    MARK = 409,
    IIF = 410,
    IIFNAME = 411,
    IIFTYPE = 412,
    OIF = 413,
    OIFNAME = 414,
    OIFTYPE = 415,
    SKUID = 416,
    SKGID = 417,
    NFTRACE = 418,
    RTCLASSID = 419,
    IBRIPORT = 420,
    OBRIPORT = 421,
    PKTTYPE = 422,
    CPU = 423,
    IIFGROUP = 424,
    OIFGROUP = 425,
    CGROUP = 426,
    CLASSID = 427,
    NEXTHOP = 428,
    CT = 429,
    DIRECTION = 430,
    STATE = 431,
    STATUS = 432,
    EXPIRATION = 433,
    HELPER = 434,
    L3PROTOCOL = 435,
    PROTO_SRC = 436,
    PROTO_DST = 437,
    LABEL = 438,
    COUNTER = 439,
    PACKETS = 440,
    BYTES = 441,
    LOG = 442,
    PREFIX = 443,
    GROUP = 444,
    SNAPLEN = 445,
    QUEUE_THRESHOLD = 446,
    LEVEL = 447,
    LIMIT = 448,
    RATE = 449,
    BURST = 450,
    OVER = 451,
    UNTIL = 452,
    QUOTA = 453,
    NANOSECOND = 454,
    MICROSECOND = 455,
    MILLISECOND = 456,
    SECOND = 457,
    MINUTE = 458,
    HOUR = 459,
    DAY = 460,
    WEEK = 461,
    _REJECT = 462,
    WITH = 463,
    ICMPX = 464,
    SNAT = 465,
    DNAT = 466,
    MASQUERADE = 467,
    REDIRECT = 468,
    RANDOM = 469,
    FULLY_RANDOM = 470,
    PERSISTENT = 471,
    QUEUE = 472,
    QUEUENUM = 473,
    BYPASS = 474,
    FANOUT = 475,
    DUP = 476,
    FWD = 477,
    NUMGEN = 478,
    INC = 479,
    MOD = 480,
    OFFSET = 481,
    JHASH = 482,
    SEED = 483,
    POSITION = 484,
    COMMENT = 485,
    XML = 486,
    JSON = 487,
    NOTRACK = 488
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
#define INET 299
#define NETDEV 300
#define ADD 301
#define UPDATE 302
#define REPLACE 303
#define CREATE 304
#define INSERT 305
#define DELETE 306
#define LIST 307
#define FLUSH 308
#define RENAME 309
#define DESCRIBE 310
#define EXPORT 311
#define MONITOR 312
#define ALL 313
#define ACCEPT 314
#define DROP 315
#define CONTINUE 316
#define JUMP 317
#define GOTO 318
#define RETURN 319
#define TO 320
#define CONSTANT 321
#define INTERVAL 322
#define TIMEOUT 323
#define GC_INTERVAL 324
#define ELEMENTS 325
#define POLICY 326
#define MEMORY 327
#define PERFORMANCE 328
#define SIZE 329
#define FLOW 330
#define NUM 331
#define STRING 332
#define QUOTED_STRING 333
#define ASTERISK_STRING 334
#define LL_HDR 335
#define NETWORK_HDR 336
#define TRANSPORT_HDR 337
#define BRIDGE 338
#define ETHER 339
#define SADDR 340
#define DADDR 341
#define TYPE 342
#define VLAN 343
#define ID 344
#define CFI 345
#define PCP 346
#define ARP 347
#define HTYPE 348
#define PTYPE 349
#define HLEN 350
#define PLEN 351
#define OPERATION 352
#define IP 353
#define HDRVERSION 354
#define HDRLENGTH 355
#define DSCP 356
#define ECN 357
#define LENGTH 358
#define FRAG_OFF 359
#define TTL 360
#define PROTOCOL 361
#define CHECKSUM 362
#define ICMP 363
#define CODE 364
#define SEQUENCE 365
#define GATEWAY 366
#define MTU 367
#define OPTIONS 368
#define IP6 369
#define PRIORITY 370
#define FLOWLABEL 371
#define NEXTHDR 372
#define HOPLIMIT 373
#define ICMP6 374
#define PPTR 375
#define MAXDELAY 376
#define AH 377
#define RESERVED 378
#define SPI 379
#define ESP 380
#define COMP 381
#define FLAGS 382
#define CPI 383
#define UDP 384
#define SPORT 385
#define DPORT 386
#define UDPLITE 387
#define CSUMCOV 388
#define TCP 389
#define ACKSEQ 390
#define DOFF 391
#define WINDOW 392
#define URGPTR 393
#define DCCP 394
#define SCTP 395
#define VTAG 396
#define RT 397
#define RT0 398
#define RT2 399
#define SEG_LEFT 400
#define ADDR 401
#define HBH 402
#define FRAG 403
#define RESERVED2 404
#define MORE_FRAGMENTS 405
#define DST 406
#define MH 407
#define META 408
#define MARK 409
#define IIF 410
#define IIFNAME 411
#define IIFTYPE 412
#define OIF 413
#define OIFNAME 414
#define OIFTYPE 415
#define SKUID 416
#define SKGID 417
#define NFTRACE 418
#define RTCLASSID 419
#define IBRIPORT 420
#define OBRIPORT 421
#define PKTTYPE 422
#define CPU 423
#define IIFGROUP 424
#define OIFGROUP 425
#define CGROUP 426
#define CLASSID 427
#define NEXTHOP 428
#define CT 429
#define DIRECTION 430
#define STATE 431
#define STATUS 432
#define EXPIRATION 433
#define HELPER 434
#define L3PROTOCOL 435
#define PROTO_SRC 436
#define PROTO_DST 437
#define LABEL 438
#define COUNTER 439
#define PACKETS 440
#define BYTES 441
#define LOG 442
#define PREFIX 443
#define GROUP 444
#define SNAPLEN 445
#define QUEUE_THRESHOLD 446
#define LEVEL 447
#define LIMIT 448
#define RATE 449
#define BURST 450
#define OVER 451
#define UNTIL 452
#define QUOTA 453
#define NANOSECOND 454
#define MICROSECOND 455
#define MILLISECOND 456
#define SECOND 457
#define MINUTE 458
#define HOUR 459
#define DAY 460
#define WEEK 461
#define _REJECT 462
#define WITH 463
#define ICMPX 464
#define SNAT 465
#define DNAT 466
#define MASQUERADE 467
#define REDIRECT 468
#define RANDOM 469
#define FULLY_RANDOM 470
#define PERSISTENT 471
#define QUEUE 472
#define QUEUENUM 473
#define BYPASS 474
#define FANOUT 475
#define DUP 476
#define FWD 477
#define NUMGEN 478
#define INC 479
#define MOD 480
#define OFFSET 481
#define JHASH 482
#define SEED 483
#define POSITION 484
#define COMMENT 485
#define XML 486
#define JSON 487
#define NOTRACK 488

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 123 "parser_bison.y" /* yacc.c:355  */

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
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;

#line 689 "parser_bison.c" /* yacc.c:355  */
};
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



int nft_parse (void *scanner, struct parser_state *state);

#endif /* !YY_NFT_PARSER_BISON_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 717 "parser_bison.c" /* yacc.c:358  */

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
#define YYLAST   2998

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  243
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  231
/* YYNRULES -- Number of rules.  */
#define YYNRULES  656
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  985

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   488

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   237,     2,     2,     2,
     238,   239,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   234,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   241,     2,   242,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   235,   240,   236,     2,     2,     2,     2,
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
     225,   226,   227,   228,   229,   230,   231,   232,   233
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   617,   617,   618,   635,   636,   639,   640,   643,   651,
     664,   672,   673,   674,   675,   704,   705,   706,   707,   708,
     709,   710,   711,   712,   713,   714,   715,   718,   722,   729,
     733,   741,   745,   749,   756,   763,   769,   775,   779,   786,
     790,   798,   805,   812,   818,   824,   828,   832,   836,   840,
     844,   850,   854,   858,   862,   866,   870,   874,   878,   882,
     886,   890,   896,   900,   904,   908,   914,   921,   927,   935,
     944,   945,   948,   949,   950,   951,   952,   953,   956,   957,
     960,   961,   964,   973,   979,   991,   992,   993,   994,   995,
    1006,  1016,  1029,  1035,  1036,  1037,  1038,  1039,  1040,  1048,
    1053,  1054,  1055,  1056,  1061,  1066,  1071,  1076,  1081,  1084,
    1085,  1088,  1092,  1095,  1096,  1097,  1101,  1107,  1108,  1109,
    1110,  1118,  1123,  1128,  1131,  1135,  1141,  1142,  1145,  1154,
    1164,  1176,  1177,  1178,  1179,  1182,  1208,  1209,  1212,  1213,
    1216,  1227,  1228,  1231,  1234,  1235,  1236,  1239,  1253,  1254,
    1257,  1258,  1259,  1260,  1261,  1262,  1265,  1273,  1280,  1287,
    1294,  1301,  1309,  1317,  1321,  1328,  1335,  1347,  1351,  1358,
    1362,  1368,  1380,  1386,  1393,  1394,  1395,  1396,  1397,  1398,
    1399,  1400,  1401,  1402,  1403,  1404,  1405,  1406,  1407,  1408,
    1409,  1410,  1413,  1417,  1423,  1429,  1434,  1443,  1448,  1453,
    1456,  1462,  1463,  1465,  1471,  1475,  1478,  1482,  1488,  1489,
    1492,  1498,  1502,  1505,  1510,  1515,  1520,  1525,  1530,  1536,
    1562,  1566,  1570,  1574,  1578,  1584,  1588,  1591,  1595,  1601,
    1610,  1630,  1631,  1632,  1635,  1636,  1639,  1655,  1656,  1657,
    1660,  1661,  1662,  1663,  1677,  1678,  1679,  1680,  1681,  1684,
    1687,  1694,  1698,  1708,  1718,  1727,  1739,  1742,  1747,  1754,
    1755,  1774,  1780,  1781,  1782,  1785,  1789,  1793,  1798,  1803,
    1807,  1811,  1817,  1818,  1821,  1824,  1828,  1833,  1839,  1840,
    1843,  1846,  1850,  1854,  1858,  1863,  1870,  1875,  1883,  1890,
    1891,  1897,  1898,  1899,  1902,  1903,  1906,  1912,  1916,  1919,
    1924,  1930,  1931,  1937,  1938,  1941,  1942,  1945,  1951,  1960,
    1961,  1964,  1971,  1980,  1986,  1990,  1993,  1999,  2005,  2021,
    2022,  2029,  2038,  2049,  2050,  2051,  2052,  2053,  2054,  2055,
    2056,  2057,  2058,  2059,  2062,  2085,  2086,  2087,  2090,  2091,
    2092,  2093,  2094,  2097,  2101,  2104,  2105,  2109,  2115,  2116,
    2122,  2123,  2129,  2130,  2136,  2139,  2140,  2159,  2165,  2171,
    2182,  2183,  2184,  2187,  2193,  2194,  2195,  2198,  2205,  2210,
    2215,  2218,  2222,  2226,  2232,  2233,  2240,  2246,  2247,  2250,
    2256,  2260,  2263,  2267,  2273,  2274,  2277,  2278,  2281,  2282,
    2285,  2289,  2293,  2297,  2303,  2309,  2317,  2318,  2319,  2322,
    2323,  2327,  2333,  2334,  2340,  2341,  2347,  2348,  2354,  2357,
    2358,  2377,  2378,  2379,  2385,  2391,  2397,  2403,  2409,  2416,
    2423,  2430,  2437,  2444,  2451,  2458,  2465,  2472,  2479,  2486,
    2492,  2498,  2506,  2507,  2508,  2509,  2510,  2511,  2514,  2518,
    2522,  2526,  2530,  2534,  2540,  2544,  2548,  2562,  2563,  2566,
    2567,  2568,  2569,  2572,  2573,  2574,  2575,  2576,  2577,  2578,
    2579,  2580,  2581,  2582,  2583,  2584,  2585,  2586,  2587,  2588,
    2589,  2592,  2596,  2600,  2613,  2619,  2620,  2623,  2624,  2627,
    2633,  2638,  2645,  2651,  2652,  2655,  2659,  2672,  2687,  2688,
    2689,  2690,  2692,  2693,  2694,  2695,  2696,  2697,  2698,  2701,
    2702,  2705,  2709,  2724,  2730,  2731,  2732,  2733,  2734,  2735,
    2736,  2737,  2738,  2739,  2740,  2741,  2742,  2743,  2744,  2745,
    2748,  2758,  2759,  2760,  2763,  2769,  2770,  2771,  2774,  2780,
    2781,  2782,  2783,  2786,  2792,  2793,  2794,  2795,  2796,  2799,
    2805,  2806,  2807,  2808,  2809,  2810,  2811,  2812,  2813,  2814,
    2815,  2816,  2819,  2825,  2826,  2827,  2828,  2829,  2830,  2831,
    2834,  2840,  2841,  2842,  2843,  2844,  2845,  2846,  2847,  2848,
    2850,  2856,  2857,  2858,  2859,  2860,  2861,  2862,  2863,  2866,
    2872,  2873,  2874,  2875,  2876,  2879,  2885,  2886,  2889,  2895,
    2896,  2897,  2900,  2906,  2907,  2908,  2909,  2912,  2918,  2919,
    2920,  2921,  2924,  2930,  2931,  2932,  2933,  2934,  2935,  2936,
    2937,  2938,  2939,  2942,  2948,  2949,  2950,  2953,  2959,  2960,
    2961,  2962,  2965,  2966,  2967,  2968,  2969,  2970,  2971,  2974,
    2980,  2981,  2984,  2990,  2991,  2992,  2993,  2996,  3002,  3008,
    3014,  3017,  3023,  3024,  3025,  3026,  3027,  3028,  3031,  3037,
    3038,  3041,  3047,  3048,  3049,  3050,  3051
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
  "\"maps\"", "\"handle\"", "\"ruleset\"", "\"inet\"", "\"netdev\"",
  "\"add\"", "\"update\"", "\"replace\"", "\"create\"", "\"insert\"",
  "\"delete\"", "\"list\"", "\"flush\"", "\"rename\"", "\"describe\"",
  "\"export\"", "\"monitor\"", "\"all\"", "\"accept\"", "\"drop\"",
  "\"continue\"", "\"jump\"", "\"goto\"", "\"return\"", "\"to\"",
  "\"constant\"", "\"interval\"", "\"timeout\"", "\"gc-interval\"",
  "\"elements\"", "\"policy\"", "\"memory\"", "\"performance\"",
  "\"size\"", "\"flow\"", "\"number\"", "\"string\"", "\"quoted string\"",
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
  "\"urgptr\"", "\"dccp\"", "\"sctp\"", "\"vtag\"", "\"rt\"", "\"rt0\"",
  "\"rt2\"", "\"seg-left\"", "\"addr\"", "\"hbh\"", "\"frag\"",
  "\"reserved2\"", "\"more-fragments\"", "\"dst\"", "\"mh\"", "\"meta\"",
  "\"mark\"", "\"iif\"", "\"iifname\"", "\"iiftype\"", "\"oif\"",
  "\"oifname\"", "\"oiftype\"", "\"skuid\"", "\"skgid\"", "\"nftrace\"",
  "\"rtclassid\"", "\"ibriport\"", "\"obriport\"", "\"pkttype\"",
  "\"cpu\"", "\"iifgroup\"", "\"oifgroup\"", "\"cgroup\"", "\"classid\"",
  "\"nexthop\"", "\"ct\"", "\"direction\"", "\"state\"", "\"status\"",
  "\"expiration\"", "\"helper\"", "\"l3proto\"", "\"proto-src\"",
  "\"proto-dst\"", "\"label\"", "\"counter\"", "\"packets\"", "\"bytes\"",
  "\"log\"", "\"prefix\"", "\"group\"", "\"snaplen\"",
  "\"queue-threshold\"", "\"level\"", "\"limit\"", "\"rate\"", "\"burst\"",
  "\"over\"", "\"until\"", "\"quota\"", "\"nanosecond\"",
  "\"microsecond\"", "\"millisecond\"", "\"second\"", "\"minute\"",
  "\"hour\"", "\"day\"", "\"week\"", "\"reject\"", "\"with\"", "\"icmpx\"",
  "\"snat\"", "\"dnat\"", "\"masquerade\"", "\"redirect\"", "\"random\"",
  "\"fully-random\"", "\"persistent\"", "\"queue\"", "\"num\"",
  "\"bypass\"", "\"fanout\"", "\"dup\"", "\"fwd\"", "\"numgen\"",
  "\"inc\"", "\"mod\"", "\"offset\"", "\"jhash\"", "\"seed\"",
  "\"position\"", "\"comment\"", "\"xml\"", "\"json\"", "\"notrack\"",
  "'='", "'{'", "'}'", "'$'", "'('", "')'", "'|'", "'['", "']'", "$accept",
  "input", "stmt_seperator", "opt_newline", "common_block", "line",
  "base_cmd", "add_cmd", "replace_cmd", "create_cmd", "insert_cmd",
  "delete_cmd", "list_cmd", "flush_cmd", "rename_cmd", "export_cmd",
  "monitor_cmd", "monitor_event", "monitor_object", "monitor_format",
  "export_format", "describe_cmd", "table_block_alloc", "table_options",
  "table_block", "chain_block_alloc", "chain_block", "set_block_alloc",
  "set_block", "set_block_expr", "set_flag_list", "set_flag",
  "map_block_alloc", "map_block", "set_mechanism", "set_policy_spec",
  "data_type", "type_identifier_list", "type_identifier", "hook_spec",
  "prio_spec", "dev_spec", "policy_spec", "chain_policy", "identifier",
  "string", "time_spec", "family_spec", "family_spec_explicit",
  "table_spec", "chain_spec", "chain_identifier", "set_spec",
  "set_identifier", "handle_spec", "position_spec", "rule_position",
  "ruleid_spec", "comment_spec", "ruleset_spec", "rule", "rule_alloc",
  "stmt_list", "stmt", "verdict_stmt", "verdict_map_stmt",
  "verdict_map_expr", "verdict_map_list_expr",
  "verdict_map_list_member_expr", "counter_stmt", "counter_stmt_alloc",
  "counter_args", "counter_arg", "log_stmt", "log_stmt_alloc", "log_args",
  "log_arg", "level_type", "log_flags", "log_flags_tcp", "log_flag_tcp",
  "limit_stmt", "quota_mode", "quota_unit", "quota_stmt", "limit_mode",
  "limit_burst", "time_unit", "reject_stmt", "reject_stmt_alloc",
  "reject_opts", "nat_stmt", "nat_stmt_alloc", "concat_stmt_expr",
  "map_stmt_expr", "stmt_expr", "nat_stmt_args", "masq_stmt",
  "masq_stmt_alloc", "masq_stmt_args", "redir_stmt", "redir_stmt_alloc",
  "redir_stmt_arg", "dup_stmt", "fwd_stmt", "nf_nat_flags", "nf_nat_flag",
  "queue_stmt", "queue_stmt_alloc", "queue_stmt_args", "queue_stmt_arg",
  "queue_stmt_flags", "queue_stmt_flag", "set_elem_expr_stmt",
  "set_elem_expr_stmt_alloc", "set_stmt", "set_stmt_op", "flow_stmt",
  "flow_stmt_alloc", "flow_stmt_opts", "flow_stmt_opt", "match_stmt",
  "variable_expr", "symbol_expr", "integer_expr", "primary_expr",
  "fib_expr", "fib_result", "fib_flag", "fib_tuple", "shift_expr",
  "and_expr", "exclusive_or_expr", "inclusive_or_expr", "basic_expr",
  "concat_expr", "prefix_rhs_expr", "range_rhs_expr", "wildcard_rhs_expr",
  "multiton_rhs_expr", "map_expr", "expr", "set_expr", "set_list_expr",
  "set_list_member_expr", "flow_key_expr", "flow_key_expr_alloc",
  "set_elem_expr", "set_elem_expr_alloc", "set_elem_options",
  "set_elem_option", "set_lhs_expr", "set_rhs_expr", "initializer_expr",
  "relational_expr", "list_rhs_expr", "rhs_expr", "shift_rhs_expr",
  "and_rhs_expr", "exclusive_or_rhs_expr", "inclusive_or_rhs_expr",
  "basic_rhs_expr", "concat_rhs_expr", "primary_rhs_expr", "relational_op",
  "verdict_expr", "meta_expr", "meta_key", "meta_key_qualified",
  "meta_key_unqualified", "meta_stmt", "offset_opt", "numgen_type",
  "numgen_expr", "hash_expr", "rt_expr", "rt_key", "ct_expr", "ct_key",
  "ct_key_dir", "ct_key_counters", "ct_stmt", "payload_stmt",
  "payload_expr", "payload_raw_expr", "payload_base_spec", "eth_hdr_expr",
  "eth_hdr_field", "vlan_hdr_expr", "vlan_hdr_field", "arp_hdr_expr",
  "arp_hdr_field", "ip_hdr_expr", "ip_hdr_field", "icmp_hdr_expr",
  "icmp_hdr_field", "ip6_hdr_expr", "ip6_hdr_field", "icmp6_hdr_expr",
  "icmp6_hdr_field", "auth_hdr_expr", "auth_hdr_field", "esp_hdr_expr",
  "esp_hdr_field", "comp_hdr_expr", "comp_hdr_field", "udp_hdr_expr",
  "udp_hdr_field", "udplite_hdr_expr", "udplite_hdr_field", "tcp_hdr_expr",
  "tcp_hdr_field", "dccp_hdr_expr", "dccp_hdr_field", "sctp_hdr_expr",
  "sctp_hdr_field", "exthdr_expr", "hbh_hdr_expr", "hbh_hdr_field",
  "rt_hdr_expr", "rt_hdr_field", "rt0_hdr_expr", "rt0_hdr_field",
  "rt2_hdr_expr", "rt2_hdr_field", "frag_hdr_expr", "frag_hdr_field",
  "dst_hdr_expr", "dst_hdr_field", "mh_hdr_expr", "mh_hdr_field", YY_NULLPTR
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
     485,   486,   487,   488,    61,   123,   125,    36,    40,    41,
     124,    91,    93
};
# endif

#define YYPACT_NINF -771

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-771)))

#define YYTABLE_NINF -400

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -771,   834,  -771,    70,  -771,  -771,    -5,    39,   552,   552,
     552,   552,   552,   552,  -771,  -771,   920,    45,   660,    72,
     706,   864,   472,    90,  2580,    29,    81,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,   416,  -771,    39,  -771,    39,   -64,
    2328,  -771,    70,  -771,    28,   -50,   -10,  2328,    39,  -771,
     137,  -771,  -771,   552,  -771,   552,   552,   552,   552,   552,
    -771,   552,  -771,   552,   552,   552,   552,   552,   552,  -771,
     552,   552,   552,   552,   552,   552,   552,   552,   552,   307,
    -771,   552,   552,   552,   552,  -771,   552,  -771,   512,   247,
    -771,  -771,  -771,  -771,   236,   125,   659,  1792,   565,   699,
     550,   585,   -29,   106,   206,   328,  1079,    75,   268,   212,
      83,    95,     1,   506,     2,   400,  1852,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,   254,   -55,  2480,    39,  2580,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,   198,  -771,
    -771,  -771,  -771,  -771,  -771,   438,  -771,  -771,  -771,  -771,
     191,  -771,   397,  -771,  -771,  -771,    39,    39,  -771,  -771,
    2767,   326,  -771,  -771,    80,   266,  -771,  -771,  -771,  -771,
    -771,  -771,   221,   251,  -771,   320,  -771,    97,  2328,  -771,
    -771,  -771,  -771,   265,  -771,    93,  -771,  -771,  -771,   122,
    -771,  1489,  -771,    -6,  -771,    64,  -771,  -771,  -771,   151,
    -771,  -771,    13,  -771,  -771,   468,   332,   325,   118,  -771,
     149,  -771,  1862,  -771,  -771,  -771,   339,  -771,  -771,  -771,
     355,  -771,  2128,   154,   165,  -771,  -771,   172,  -771,  -771,
    -771,   184,   371,  2328,   -50,   -10,  -771,   137,  -771,  2328,
    -771,  -771,  -771,  -771,   137,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,   552,   552,  -771,  -771,
    -771,  -771,    39,  -771,  -771,  -771,  -771,   414,  -771,  -771,
    -771,  -771,  -771,   418,   -12,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,   192,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,   351,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,   235,    69,   240,  -771,   229,  -771,  -771,  -771,
    -771,  -771,  -771,   198,  -771,  -771,  -771,  2580,  -771,  -771,
     433,   443,   267,   455,   360,  -771,  -771,   440,  1962,  2480,
    -771,  2128,    20,  -771,   447,  -771,  -771,   446,   452,   265,
    -771,   256,   447,   454,   459,   463,   447,    93,  -771,   111,
    -771,  1962,  -771,  1589,   236,   125,   659,  1792,  -771,   565,
     699,   550,   585,   -29,   106,   206,   328,  1079,    75,   268,
    -771,  -771,  -771,    82,  -771,   471,   369,   167,   171,  -771,
    -771,  -771,  -771,  -771,   544,   525,   534,   314,   284,    35,
     559,  -771,  -771,  -771,  -771,   581,  -771,  1696,  -771,   581,
    1962,  -771,  -771,   151,  -771,   592,  -771,    39,  2580,    15,
    -771,  2580,  2580,  2580,  2580,  2580,  2580,     3,  2128,  -771,
    -771,  -771,  -771,  -771,  -771,    39,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,   611,  -771,   250,   558,  -771,
    2062,  2480,  2480,    70,   611,  -771,  -771,  -771,  -771,  -771,
     533,  -771,  -771,   393,   405,   408,  -771,   411,  -771,  -771,
    -771,  -771,  -771,   573,   247,  -771,  -771,  -771,  -771,   582,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,   587,   589,
    -771,  -771,  -771,    71,    -3,   661,  2480,  2480,  2480,  2480,
    -771,  -771,   605,     5,   654,  -771,  -771,   320,   602,    -3,
    -771,   284,   558,   320,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,   576,   153,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,   599,   607,   620,   617,  -771,  1962,   702,  2580,
    2128,  1962,   581,  2761,  2761,  2761,  2761,  2761,   638,  2761,
    1962,   369,  1962,   369,  -771,  -771,   394,  -771,   661,  2328,
      -3,  2580,  -771,  -771,  -771,   468,   332,   325,  -771,    39,
     320,  -771,  -771,  2761,  2761,  2761,  2128,  -771,  -771,  -771,
    -771,   150,   918,    57,   291,  -771,  -771,  -771,  -771,  -771,
     713,  -771,   474,   500,   178,  -771,   650,  -771,    -3,  -771,
    -771,  -771,  -771,  -771,    47,  -771,  -771,  -771,  1962,  -771,
    2702,  -771,    -3,  2128,  -771,  -771,  -771,  -771,   729,  -771,
     670,   672,  -771,   680,  -771,  1962,  -771,  -771,  -771,  -771,
    -771,   544,   525,   534,  -771,  -771,   369,  -771,   369,   581,
    -771,   502,    -3,  2328,  -771,  2228,    23,  -771,  -771,  -771,
    -771,   519,    39,    39,    39,   683,  -771,  -771,  -771,    70,
     557,   684,  -771,  -771,  -771,    70,    70,    70,   650,   650,
     529,   548,   693,    40,   612,  -771,  -771,  -771,    70,   537,
      40,   612,  -771,  -771,  -771,    70,   160,  1120,    65,   340,
     701,  -771,   704,  -771,   707,  -771,  -771,  -771,  -771,   603,
     580,  -771,   320,  -771,   558,  -771,   153,  -771,  -771,  -771,
    -771,   581,   581,  -771,   542,   777,   320,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,   757,
    -771,  -771,  -771,    70,    70,   137,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,    70,   779,  -771,  -771,  -771,  -771,
     245,  -771,  -771,   137,   783,   245,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,   500,  -771,  -771,  -771,  -771,  -771,   580,
     716,  -771,  -771,  -771,  -771,   671,  2228,  -771,   554,   561,
     562,   717,  -771,  -771,  -771,  -771,    40,   612,  -771,  -771,
      40,  -771,  -771,  -771,    16,   320,  -771,  -771,  -771,   763,
    -771,  -771,    70,  -771,  -771,  -771,  -771,  1322,   220,   641,
     722,   688,  -771,    70,    70,    70,  -771,    56,  -771,  -771,
    -771,   743,  -771,  -771,  -771
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,   148,   148,
     148,   148,   148,   148,   152,   155,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    70,   154,   153,   150,
     151,    12,    11,     3,     0,    15,     0,   149,     0,   163,
       0,    10,     0,   143,     0,    27,    29,     0,     0,    99,
       0,   116,    16,   148,    17,   148,   148,   148,   148,   148,
      18,   148,    19,   148,   148,   148,   148,   148,   148,    20,
     148,   167,   148,   167,   167,   148,   148,   167,   167,     0,
      21,   148,   148,   148,   167,    22,   148,    23,     0,     0,
     322,   144,   145,   146,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,     0,     0,     0,     0,     0,
      26,   320,   319,   323,   324,    82,   332,   327,   445,   330,
     331,   328,   329,   325,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     326,   622,   623,   624,   625,   626,   627,   628,     0,    80,
      81,    24,    68,    71,    25,    72,    14,    13,   156,   157,
       0,   164,     0,   438,   439,   440,     0,     0,   443,   313,
       0,     0,   203,   210,     0,   233,   250,   257,   258,   274,
     280,   296,     0,     0,   474,     7,    32,   169,   171,   172,
     174,   193,   177,   201,   180,   208,   181,   182,   183,   251,
     184,     0,   187,   273,   188,   279,   189,   190,   185,   294,
     191,   176,     0,   175,   345,   348,   350,   352,   354,   355,
     364,   366,     0,   365,   317,   192,   445,   179,   186,   178,
     325,     8,     0,     0,     0,    31,   159,     0,    35,   110,
     109,     0,     0,     0,    37,    39,    99,     0,   116,     0,
      45,    46,    47,    48,     0,    49,    51,   168,    52,    53,
      54,    55,    56,    61,    60,    57,   148,   167,    62,    63,
      64,    65,     0,   521,   522,   523,   321,     0,   338,   339,
     340,   341,   342,   344,     0,   525,   526,   527,   524,   532,
     529,   530,   531,   528,   534,   535,   536,   537,   538,   533,
     550,   551,   545,   540,   541,   542,   543,   544,   546,   547,
     548,   549,   539,   553,   556,   555,   554,   557,   558,   559,
     552,   568,   569,   561,   562,   563,   565,   564,   566,   567,
     560,   571,   576,   573,   572,   577,   575,   574,   578,   570,
     581,   584,   580,   582,   583,   579,   587,   586,   585,   589,
     590,   591,   588,   595,   596,   593,   594,   592,   601,   598,
     599,   600,   597,   611,   605,   608,   609,   603,   604,   606,
     607,   610,   612,   602,   616,   614,   615,   613,   621,   618,
     619,   620,   617,   635,   634,   633,   636,   483,   484,   482,
     632,     0,   637,   640,   639,   631,   630,   629,   647,   644,
     642,   643,   645,   646,   641,   650,   649,   648,   654,   653,
     656,   652,   655,   651,   446,   449,   450,   451,   452,   444,
     447,   448,   486,   489,   490,   488,   500,   499,   485,   491,
     478,   477,     0,   364,     0,   318,     0,    67,    73,    74,
      76,    75,    77,    78,   162,   309,   310,     0,   441,   442,
     446,   444,   486,   485,   239,   231,   232,     0,     0,     0,
       6,     0,     0,   368,     0,   170,   173,     0,     0,   202,
     204,     0,     0,     0,     0,     0,     0,   209,   211,     0,
     249,     0,   359,     0,   413,   416,   417,   414,   431,   423,
     415,   424,   422,   421,   425,   419,   420,   418,   426,   427,
     429,   430,   428,     0,   262,   265,   256,   411,   412,   259,
     360,   361,   362,   263,   402,   404,   406,   408,     0,   264,
       0,   291,   292,   293,   272,   277,   289,     0,   278,   283,
       0,   303,   304,   295,   297,   300,   301,     0,     0,     0,
     314,     0,     0,     0,     0,     0,     0,     0,     0,   432,
     433,   434,   435,   436,   437,     0,   413,   416,   417,   414,
     423,   415,   424,   422,   421,   425,   419,   420,   418,   426,
     427,   411,   412,   397,   398,   391,   390,   409,   396,   399,
       0,     0,     0,     0,   389,   388,    85,    93,   100,   117,
       0,   165,    36,     0,     0,     0,    43,     0,    44,    50,
      59,    58,    66,     0,     0,   337,   335,   336,   334,     0,
     492,   493,   495,   494,   496,   497,   487,   498,     0,     0,
     333,    69,    79,     0,   305,   307,     0,     0,     0,     0,
     237,   238,     0,     0,   286,   288,   385,     7,     7,   377,
     379,   409,   384,     7,   367,   166,   206,   207,   205,   224,
     223,     0,     0,   222,   218,   213,   214,   215,   216,   219,
     217,   212,     0,     0,     0,     0,   269,     0,   266,     0,
       0,     0,   271,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   281,   299,   298,     0,   316,   376,     0,
     374,     0,   315,   346,   347,   349,   351,   353,   356,     0,
       7,   194,   363,     0,     0,     0,     0,   392,   472,   503,
       9,     0,     0,     0,     0,   161,    85,    93,   100,   117,
       0,   343,     0,   475,   475,   308,     0,   383,   306,   380,
     473,   471,   502,   501,     0,   235,   234,   236,     0,   371,
       0,   372,   378,   370,   369,   221,   227,   228,   220,   226,
       0,     0,   255,     0,   270,     0,   260,   261,   267,   400,
     401,   403,   405,   407,   357,   358,   275,   290,   282,   284,
     302,     0,   375,     0,   196,     0,     0,   197,   395,   394,
     410,     0,     0,     0,     0,     0,    28,    87,    86,     0,
       0,     0,    30,    95,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,   102,   101,     0,     0,
       0,     0,    34,   119,   118,     0,     0,     0,     0,     0,
       0,   638,     0,   479,     0,   481,   147,   382,   381,     0,
     240,   287,     7,   409,   386,   387,     0,   252,   253,   254,
     268,   276,   285,   312,     0,     0,     7,   195,   393,   158,
      92,   160,    99,   116,    84,    88,   141,   142,   140,     0,
      96,    97,    98,     0,     0,     0,   127,   126,   124,   125,
     131,   133,   134,   132,     0,   128,   129,   113,   114,   115,
       0,   112,   108,     0,     0,     0,   123,    38,    40,    41,
      42,   520,   476,   475,   244,   245,   246,   247,   248,   240,
       0,   230,   373,   225,   311,     0,   199,   198,     0,     0,
       0,     0,   105,   106,   107,   103,     0,     0,   104,   122,
       0,   121,   480,   229,     0,     7,    93,   100,   117,   139,
     130,   111,     0,   243,   241,   242,   200,     0,     0,     0,
       0,     0,   120,     0,     0,     0,   138,     0,    89,    90,
      91,     0,   136,   135,   137
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -771,  -771,    -1,  -645,     7,  -771,  -771,   804,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -158,  -771,   547,  -771,    77,  -269,  -702,  -267,  -688,  -265,
     -19,  -119,  -264,  -687,  -704,  -771,  -770,  -771,  -117,  -771,
    -771,  -771,  -771,  -771,     0,  -114,  -106,  -771,    37,   709,
     359,  -771,    30,    17,  -771,  -771,    76,   765,   615,    94,
     -15,  -771,  -771,  -205,  -771,  -771,  -771,  -771,   -43,  -771,
    -771,  -771,   337,  -771,  -771,  -771,   334,  -771,  -771,  -771,
     -27,  -771,  -771,  -771,  -771,  -771,   -87,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -457,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -217,   132,  -771,  -771,  -771,
     286,  -771,   135,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
     283,  -771,   -45,  -215,  -132,    -9,  -771,  -771,  -771,   223,
     281,   285,   287,  -771,  -122,  -113,  -771,  -771,  -771,  -223,
    -771,   -25,   -49,  -771,   185,   142,  -771,  -741,  -771,  -565,
    -598,  -771,  -771,  -771,  -771,   604,  -227,   166,   164,   168,
    -771,  -109,  -470,  -163,  -771,  -736,  -771,   676,  -771,   -37,
    -771,  -705,  -771,  -771,  -771,  -771,  -771,  -771,   698,  -771,
    -312,  -771,  -771,   -36,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   823,   491,   824,    33,    34,    35,    54,    60,
      62,    69,    80,    85,    87,   181,   184,   185,   473,   651,
     182,   140,   263,   819,   741,   264,   742,   267,   743,   268,
     910,   911,   271,   744,   838,   898,   904,   905,   906,   825,
     983,   971,   826,   888,   306,   141,   857,    36,    37,    48,
      39,   880,    49,   882,   621,   191,    40,   273,   757,   288,
     827,   217,   218,   219,   220,   221,   731,   806,   807,   222,
     223,   499,   500,   224,   225,   507,   508,   690,   684,   778,
     779,   226,   487,   767,   227,   662,   931,   929,   228,   229,
     510,   230,   231,   533,   534,   535,   536,   232,   233,   554,
     234,   235,   558,   236,   237,   555,   556,   238,   239,   563,
     564,   565,   566,   653,   654,   240,   477,   241,   242,   569,
     570,   243,   142,   143,   144,   244,   146,   638,   313,   314,
     245,   246,   247,   248,   249,   250,   540,   541,   542,   543,
     251,   252,   253,   492,   493,   719,   720,   668,   669,   758,
     759,   670,   862,   613,   254,   605,   606,   544,   545,   546,
     547,   548,   608,   609,   610,   255,   147,   449,   450,   148,
     257,   853,   462,   149,   150,   151,   419,   152,   458,   646,
     459,   258,   259,   153,   154,   307,   155,   318,   156,   323,
     157,   329,   158,   342,   159,   350,   160,   360,   161,   369,
     162,   375,   163,   378,   164,   382,   165,   387,   166,   392,
     167,   403,   168,   407,   169,   412,   170,   171,   427,   172,
     420,   173,   422,   174,   424,   175,   434,   176,   437,   177,
     443
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      31,   270,    41,   256,   260,   269,   624,    44,    32,   625,
     256,   260,   626,   496,   627,   145,   537,   466,   559,   629,
     467,   672,   769,   771,   463,   216,   729,   673,   773,   603,
     876,   664,   265,   187,   865,   615,   188,   601,   189,   603,
     845,   261,    50,    51,   567,   847,   567,   601,   266,   855,
    -399,  -399,  -399,  -399,   696,  -399,   698,  -399,     3,   550,
     848,     4,   849,     5,   875,   756,     3,   859,   549,     4,
     914,     5,   178,    42,     4,   635,     5,   576,   981,   451,
      53,   376,   765,     6,     7,   805,    47,   276,   277,   278,
     699,     6,     7,   963,   585,   377,   283,   284,   285,   538,
     713,   425,   435,   714,   772,   292,   293,    61,   287,   578,
     287,   287,   464,   300,   287,   287,    43,   900,   426,   436,
     602,   287,   700,    86,   860,   828,   829,   830,   831,   557,
     602,   832,   982,   828,   829,   830,   831,   279,   465,   832,
     647,   901,   902,   607,   833,   845,   636,   637,    91,    92,
      93,     3,   833,   607,     4,   802,     5,   576,   183,   460,
     858,     3,   404,   451,     4,   190,     5,   290,   291,   461,
     647,   294,   295,   577,   858,  -323,     6,     7,   301,  -324,
     962,   256,   260,   812,   834,   -83,     6,     7,   813,   578,
     814,   766,   834,   812,   903,   875,   478,   479,   813,   955,
     814,   964,   965,   604,   858,   405,   406,  -323,   551,   552,
     553,  -324,   319,   604,   320,   321,   322,   932,   952,   692,
     501,     3,   539,   379,     4,   -92,     5,   494,   270,   421,
     693,   936,   269,   380,   381,   270,   256,   260,   730,   269,
     784,   423,   256,   260,   788,   694,     6,     7,   568,     4,
     721,     5,   947,   796,   967,   798,   674,   734,   622,   877,
     179,   180,   262,   776,   628,   845,   777,   474,   666,   968,
     708,   969,   709,   537,   484,  -399,   601,   815,   551,   552,
     553,   502,   503,   504,   505,   506,   488,   815,   828,   829,
     830,   831,     3,   835,   832,     4,   537,     5,   537,   413,
     864,   919,   632,   672,   708,   658,   709,   833,   138,   383,
     966,   861,   414,   384,   679,   652,   489,     6,     7,   702,
     695,   315,   316,   317,   490,   549,   630,   494,   870,   415,
     509,   452,   308,   309,   287,   672,   385,   386,   296,   297,
     680,     3,   537,   574,     4,   537,     5,   834,   549,   573,
     549,   732,   640,   641,   681,   603,   538,   416,   575,   602,
     453,   839,   831,   601,   655,   832,     6,     7,    46,   560,
     561,   562,   215,   642,   138,   408,   463,   611,   840,   538,
     675,   538,   671,   737,   417,   418,   816,   603,   685,   616,
     682,   631,   689,   612,   549,   601,   917,   549,   409,   410,
     617,   310,   311,   482,   852,   312,   854,   618,   454,   411,
     839,   831,   272,   620,   832,   275,   186,   683,   841,   619,
       4,   633,     5,   281,   272,   538,   634,   840,   538,   179,
     180,   289,   453,   639,   455,   388,   640,   641,   755,   456,
     457,   299,   667,   475,   476,   302,   602,   643,   644,   645,
     497,   498,   456,   457,   728,   718,   974,   642,   389,   390,
     648,   391,   485,   486,   665,   649,   672,   841,   650,   671,
     468,   656,   469,   787,   470,   471,   701,   603,   602,   539,
     454,   657,   537,   571,   572,   601,   537,   438,   601,   601,
     601,   601,   601,   659,   601,   537,   799,   537,   463,   463,
     439,   671,   539,    81,   539,    82,   455,   440,   472,   811,
      83,   456,   457,   603,   801,    84,   663,   441,   601,   601,
     601,   601,   676,   442,    91,    92,    93,   842,   677,   604,
     686,   643,   644,   645,   549,   687,   456,   457,   549,   688,
     789,   790,   705,   463,   463,   463,   463,   549,   539,   549,
     666,   539,   706,   537,   707,   601,   660,   661,   601,   703,
     704,   604,   723,   724,   710,   538,   735,   717,   602,   538,
     537,   602,   602,   602,   602,   602,   920,   602,   538,   871,
     538,   872,   666,   551,   552,   553,   738,   739,   711,    43,
     601,   671,   303,   304,   305,   428,    14,    15,   874,   716,
     795,   602,   602,   602,   602,   549,   490,   770,   718,   745,
     429,   938,   740,   561,   562,   939,   886,   887,   733,   940,
     896,   897,   549,   430,   808,   809,   810,   671,   746,   431,
     944,   760,   761,   762,   763,    27,   538,   361,   602,   362,
     747,   602,     3,   748,    28,     4,   749,     5,   949,   750,
      29,   604,   343,   538,   344,   432,   433,   363,   752,   364,
     365,   863,   366,   753,   671,   754,    30,     6,     7,   576,
     367,   368,   345,   602,   346,   347,   348,   349,   907,   908,
     909,   764,   256,   260,   768,   370,   780,   604,   539,   775,
     786,    55,   539,    56,   781,   371,   671,   782,    57,    58,
      59,   539,   372,   539,   783,   256,   260,   785,   373,   374,
      38,   839,   831,   666,   794,   832,   851,    45,    38,    38,
     850,   601,   893,   894,   667,    38,   852,   856,   840,   804,
     193,   194,   195,   196,   197,   198,   866,    63,   873,    64,
     817,    65,   836,   843,    66,    67,    68,   867,   818,   868,
     837,   844,   324,   325,   326,   327,   328,   869,   878,   539,
     884,   889,    38,   895,   274,    38,   256,   260,   841,   899,
      38,   913,   280,    38,    38,   930,   539,   921,   934,   286,
     922,    38,   935,   923,   351,   352,   941,   946,   950,   956,
     298,    38,   954,   970,   959,    38,   957,   958,   353,   976,
     354,   355,   356,   977,   602,   924,   925,   926,   927,   928,
     256,   260,   879,   881,   881,   357,   358,   359,   885,   984,
      52,   623,   915,   846,   890,   891,   892,   671,   961,   960,
     282,   883,   495,   937,     2,     3,   678,   912,     4,   933,
       5,   691,   953,   797,   916,   817,   270,   836,   843,   715,
     269,   800,   722,   818,   725,   837,   844,   751,   774,   726,
       6,     7,   727,   803,   270,     8,   614,     9,   269,    10,
     792,   791,    11,    12,    13,   793,   481,   975,    14,    15,
      16,     0,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,   942,   943,     0,    70,    71,    72,    73,   483,
       0,    74,    75,   945,    76,    77,     0,    78,     0,   948,
       0,  -148,     0,     0,   951,     0,     0,    27,     0,     3,
       0,     0,     4,     0,     5,     0,    28,     0,     0,     0,
     256,   260,    29,     0,     0,     0,     0,     0,     0,    79,
       0,    88,     0,     0,     6,     7,    89,     0,    30,     0,
       0,     8,     0,     9,     0,    10,   192,     0,    11,    12,
      13,   972,     0,     0,    14,    15,     0,   836,   843,     0,
       0,     0,   978,   979,   980,   837,   844,   193,   194,   195,
     196,   197,   198,     0,     0,     0,     0,     0,     0,   820,
       0,     0,     0,   199,    90,    91,    92,    93,     0,     0,
       0,     0,    94,    27,     0,   821,    95,     0,     0,     0,
      96,     0,    28,     0,     0,     0,    97,     0,    29,     0,
       0,     0,     0,     0,     0,     0,    98,     0,     0,     0,
       0,     0,    99,     0,    30,     0,     0,   100,     0,     0,
     101,     0,     0,   102,   103,     0,     0,   104,     0,     0,
     105,     0,   106,     0,     0,     0,     0,   107,   108,     0,
     109,   110,   111,     0,     0,   112,   113,     0,     0,   114,
     115,   200,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
       0,     0,   201,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   202,     0,     0,   203,     0,     0,     0,     0,
       0,   204,     0,     0,     0,     0,   205,     0,     0,     0,
       0,     3,     0,     0,     4,   206,     5,     0,   207,   208,
     209,   210,     0,     0,     0,   211,     0,     0,     0,   212,
     213,   136,     0,    88,     0,   137,     6,     7,    89,     0,
       0,   214,     0,   215,   822,   138,   139,     0,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   195,   196,   197,   198,     0,   393,     0,     0,   394,
       0,   820,     0,     0,     0,   199,    90,    91,    92,    93,
       0,     0,   395,     0,    94,     0,   396,   821,    95,   397,
     398,     0,    96,     0,   399,   400,   401,   402,    97,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    98,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,   100,
       0,     0,   101,     0,     0,   102,   103,     0,     0,   104,
       0,     0,   105,     0,   106,     0,     0,     0,     0,   107,
     108,     0,   109,   110,   111,     0,     0,   112,   113,     0,
       0,   114,   115,   200,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,     0,     0,   201,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,     0,     0,   203,     0,     0,
       0,     0,     0,   204,     0,     0,     0,     0,   205,     0,
       0,     0,     0,     3,     0,     0,     4,   206,     5,     0,
     207,   208,   209,   210,     0,     0,     0,   211,     0,     0,
       0,   212,   213,   136,     0,    88,     0,   137,     6,     7,
      89,     0,     0,   214,     0,   215,   918,   138,   139,     0,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,     0,     0,   820,     0,     0,     0,   199,    90,    91,
      92,    93,     0,     0,     0,     0,    94,     0,     0,   821,
      95,     0,     0,     0,    96,     0,     0,     0,     0,     0,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      98,     0,     0,     0,     0,     0,    99,     0,     0,     0,
       0,   100,     0,     0,   101,     0,     0,   102,   103,     0,
       0,   104,     0,     0,   105,     0,   106,     0,     0,     0,
       0,   107,   108,     0,   109,   110,   111,     0,     0,   112,
     113,     0,     0,   114,   115,   200,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   511,     0,   201,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   202,     0,     0,   203,
     512,     0,    88,     0,     0,   204,     0,    89,     0,     0,
     205,     0,     0,     0,     0,     0,     0,     0,     0,   206,
       0,     0,   207,   208,   209,   210,     0,     0,     0,   211,
       0,     0,     0,   212,   213,   136,     0,     0,     0,   137,
       0,     0,     0,     0,   513,   214,     0,   215,   973,   138,
     139,     0,     0,     0,     0,    90,    91,    92,    93,     0,
       0,     0,     0,   514,     0,     0,     0,   515,     0,     0,
       0,   516,     0,     0,     0,     0,     0,   517,     0,     0,
       0,   518,     0,     0,   697,     0,     0,   519,     0,     0,
       0,     0,     0,   520,     0,     0,     0,     0,   521,     0,
     512,   522,    88,     0,   523,   524,     0,    89,   525,     0,
       0,   526,     0,   527,     0,     0,     0,     0,   528,   529,
       0,   109,   110,   111,     0,     0,   112,   113,     0,     0,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,     0,     0,   135,     0,    90,    91,    92,    93,     0,
       0,     0,     0,   514,     0,     0,     0,   515,     0,     0,
       0,   516,     0,     0,     0,     0,     0,   517,     0,     0,
       0,   518,     0,     0,     0,     0,     0,   519,     0,   530,
     531,   712,   532,   520,     0,     0,     0,     0,   521,     0,
       0,   522,   136,     0,   523,   524,   137,   512,   525,    88,
       0,   526,     0,   527,    89,     0,   138,   139,   528,   529,
       0,   109,   110,   111,     0,     0,   112,   113,     0,     0,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,     0,     0,   135,     0,     0,     0,     0,     0,     0,
       0,     0,    90,    91,    92,    93,     0,     0,     0,     0,
     514,     0,     0,     0,   515,     0,     0,     0,   516,     0,
       0,     0,     0,     0,   517,     0,     0,     0,   518,   530,
     531,     0,   532,     0,   519,     0,     0,     0,     0,     0,
     520,     0,   136,     0,     0,   521,   137,     0,   522,     0,
       0,   523,   524,     0,     0,   525,   138,   139,   526,     0,
     527,     0,     0,     0,     0,   528,   529,     0,   109,   110,
     111,     0,     0,   112,   113,     0,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,     0,     0,
     135,   579,   580,   581,   582,   583,   584,   330,   331,     0,
       0,   332,     0,   512,     0,   585,     0,     0,     0,     0,
       0,   333,   334,   335,   336,   337,   338,   339,   340,   341,
       0,     0,     0,     0,     0,     0,   530,   531,     0,   532,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   136,
       0,     0,     0,   137,     0,     0,     0,     0,     0,   444,
       0,     0,     0,   138,   139,     0,     0,     0,    90,    91,
      92,    93,     0,     0,     0,     0,   586,     0,     0,     0,
     587,     0,     0,     0,   588,   445,     0,     0,   446,     0,
     589,     0,     0,     0,   518,     0,     0,   447,     0,     0,
     590,     0,     0,     0,     0,     0,   591,     0,     0,     0,
       0,   592,     0,   512,   593,    88,     0,   594,   595,     0,
      89,   596,     0,     0,   597,     0,   598,     0,     0,     0,
       0,   599,   600,     0,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    90,    91,
      92,    93,     0,     0,     0,     0,   514,     0,     0,     0,
     515,     0,     0,     0,   516,     0,     0,     0,     0,     0,
     517,     0,     0,     0,   518,     0,   448,     0,     0,     0,
     519,     0,   530,   531,     0,   532,   520,     0,     0,     0,
       0,   521,     0,   512,   522,   585,     0,   523,   524,     0,
       0,   525,     0,     0,   526,     0,   527,   215,     0,   138,
       0,   528,   529,     0,   109,   110,   111,     0,     0,   112,
     113,     0,     0,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,     0,     0,   135,     0,    90,    91,
      92,    93,     0,     0,     0,     0,   586,     0,     0,   512,
     587,   585,     0,     0,   588,     0,     0,     0,     0,     0,
     589,     0,     0,     0,   518,     0,     0,     0,     0,     0,
     590,     0,   530,   531,     0,   532,   591,     0,     0,     0,
       0,   592,     0,     0,   593,   136,     0,   594,   595,   137,
       0,   596,     0,     0,   597,     0,   598,     0,     0,   138,
     139,   599,   600,     0,    90,    91,    92,    93,     0,     0,
       0,     0,   586,     0,     0,     0,   587,     0,     0,     0,
     588,     0,     0,     0,     0,     0,   589,     0,     0,     0,
     518,     0,     0,     0,     0,     0,   590,     0,     0,     0,
       0,     0,   591,     0,     0,     0,     0,   592,     0,   512,
     593,   585,     0,   594,   595,     0,     0,   596,     0,     0,
     597,     0,   598,     0,     0,     0,     0,   599,   600,     0,
       0,     0,   530,   531,     0,   532,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,     0,   138,
     736,     0,     0,     0,    90,    91,    92,    93,     0,     0,
       0,     0,   586,     0,     0,     0,   587,     0,     0,     0,
     588,     0,     0,     0,     0,     0,   589,     0,     0,     0,
     518,     0,     0,     0,     0,     0,   590,     0,   530,   531,
       0,   532,   591,     0,     0,     0,     0,   592,     0,     0,
     593,    88,     0,   594,   595,     0,    89,   596,     0,     0,
     597,     0,   598,   215,     0,   138,   192,   599,   600,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   193,   194,   195,
     196,   197,   198,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   199,    90,    91,    92,    93,     0,     0,
       0,     0,    94,     0,     0,     0,    95,     0,     0,     0,
      96,     0,     0,     0,     0,     0,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    98,     0,   530,   531,
       0,   532,    99,     0,     0,     0,     0,   100,     0,     0,
     101,     0,     0,   102,   103,     0,     0,   104,     0,     0,
     105,     0,   106,     0,     0,   138,     0,   107,   108,     0,
     109,   110,   111,     0,     0,   112,   113,     0,     0,   114,
     115,   200,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
       0,     0,   201,    88,     0,     0,     0,     0,    89,     0,
       0,     0,   202,     0,     0,   203,     0,     0,     0,     0,
       0,   204,     0,     0,     0,     0,   205,     0,     0,     0,
       0,     0,     0,     0,     0,   206,     0,     0,   207,   208,
     209,   210,     0,     0,     0,   211,     0,     0,     0,   212,
     213,   136,     0,     0,     0,   137,    90,    91,    92,    93,
       0,   214,     0,   215,    94,   138,   139,     0,    95,     0,
       0,     0,    96,     0,     0,     0,     0,     0,    97,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    98,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,   100,
       0,     0,   101,    88,     0,   102,   103,     0,    89,   104,
       0,     0,   105,     0,   106,     0,     0,     0,     0,   107,
     108,     0,   109,   110,   111,     0,     0,   112,   113,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,     0,     0,   135,     0,    90,    91,    92,    93,
       0,     0,     0,     0,    94,     0,     0,     0,    95,     0,
       0,     0,    96,     0,     0,     0,     0,     0,    97,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    98,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,   100,
       0,     0,   101,   136,     0,   102,   103,   137,     0,   104,
       0,     0,   105,     0,   106,   215,     0,   138,   139,   107,
     108,     0,   109,   110,   111,   585,     0,   112,   113,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,     0,     0,   135,     0,     0,     0,     0,     0,
       0,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    90,    91,
      92,    93,     0,     0,   585,     0,   586,     0,     0,     0,
     587,     0,     0,     0,   588,     0,     0,     0,     0,     0,
     589,     0,     0,   136,   518,     0,     0,   137,     0,     0,
     590,     0,     0,     0,     0,     0,   591,   138,   139,     0,
       0,   592,     0,     0,   593,     0,     0,   594,   595,     0,
       0,   596,     0,     0,   597,     0,   598,    90,    91,    92,
      93,   599,   600,     0,   480,   586,     0,     0,     0,   587,
       0,     0,     0,   588,     0,     0,     0,     0,     0,   589,
       0,     0,     0,   518,     0,     0,     0,     0,     0,   590,
     445,     0,     0,   446,     0,   591,     0,     0,     0,     0,
     592,     0,   447,   593,     0,     0,   594,   595,     0,     0,
     596,     0,     0,   597,     0,   598,     0,     0,     0,     0,
     599,   600,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   530,   531,     0,   532,     0,     0,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   530,   531,     0,   532,     0,     0,     0,     0,     0,
       0,   448,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138
};

static const yytype_int16 yycheck[] =
{
       1,    50,     3,    40,    40,    50,   275,     7,     1,   276,
      47,    47,   277,   218,   278,    24,   231,   139,   235,   284,
     178,   491,   667,   668,   137,    40,    23,     7,   673,   252,
       7,   488,    47,    34,   770,   262,    36,   252,    38,   262,
     744,    42,    12,    13,    31,   747,    31,   262,    48,   754,
      15,    16,    17,    18,   511,    20,   513,    22,     1,    65,
     748,     4,   749,     6,   805,    68,     1,    20,   231,     4,
     840,     6,    43,    78,     4,    87,     6,     8,    22,   116,
      35,   110,    77,    26,    27,   730,    10,    57,    58,    59,
       8,    26,    27,    77,    23,   124,    66,    67,    68,   231,
     557,   100,   100,   560,   669,    75,    76,    35,    71,    40,
      73,    74,   137,    83,    77,    78,    77,    77,   117,   117,
     252,    84,    40,    33,    77,    68,    69,    70,    71,    65,
     262,    74,    76,    68,    69,    70,    71,    61,   138,    74,
     452,   101,   102,   252,    87,   849,   158,   159,    77,    78,
      79,     1,    87,   262,     4,   720,     6,     8,    77,   214,
     758,     1,    87,   200,     4,   229,     6,    73,    74,   224,
     482,    77,    78,    24,   772,     8,    26,    27,    84,     8,
     950,   218,   218,    33,   127,   235,    26,    27,    38,    40,
      40,   186,   127,    33,   154,   936,   196,   197,    38,   935,
      40,   185,   186,   252,   802,   130,   131,    40,   214,   215,
     216,    40,    87,   262,    89,    90,    91,   862,   923,   108,
     127,     1,   231,   117,     4,   235,     6,   230,   277,   146,
     119,   876,   277,   127,   128,   284,   273,   273,   235,   284,
     697,   146,   279,   279,   701,   134,    26,    27,   235,     4,
     235,     6,     7,   710,   956,   712,   236,     7,   273,   236,
     231,   232,   234,   110,   279,   969,   113,    76,   491,   957,
      20,   958,    22,   488,   194,   240,   491,   127,   214,   215,
     216,   188,   189,   190,   191,   192,    65,   127,    68,    69,
      70,    71,     1,   236,    74,     4,   511,     6,   513,    87,
     770,   236,   302,   773,    20,    38,    22,    87,   237,   103,
     955,   768,   100,   107,    58,   473,    65,    26,    27,   536,
     209,    85,    86,    87,     4,   488,   296,   230,   785,   117,
     208,    77,    85,    86,   297,   805,   130,   131,    31,    32,
      84,     1,   557,    18,     4,   560,     6,   127,   511,    17,
     513,   578,    85,    86,    98,   578,   488,   145,   240,   491,
     106,    70,    71,   578,   477,    74,    26,    27,     9,   218,
     219,   220,   235,   106,   237,   107,   489,    38,    87,   511,
     494,   513,   491,   610,   172,   173,   236,   610,   502,   235,
     134,   297,   506,    38,   557,   610,   236,   560,   130,   131,
     235,   154,   155,    77,   226,   158,   228,   235,   154,   141,
      70,    71,    53,    42,    74,    56,     0,   161,   127,   235,
       4,     7,     6,    64,    65,   557,     8,    87,   560,   231,
     232,    72,   106,   241,   180,   107,    85,    86,   653,   185,
     186,    82,   491,    46,    47,    86,   578,   180,   181,   182,
     185,   186,   185,   186,   576,   568,   236,   106,   130,   131,
     225,   133,   196,   197,   489,   225,   936,   127,   239,   578,
      32,    38,    34,   700,    36,    37,     5,   700,   610,   488,
     154,    38,   697,    15,    16,   700,   701,    87,   703,   704,
     705,   706,   707,    38,   709,   710,   713,   712,   611,   612,
     100,   610,   511,    31,   513,    33,   180,   107,    70,   736,
      38,   185,   186,   736,   719,    43,    76,   117,   733,   734,
     735,   736,    76,   123,    77,    78,    79,   236,    76,   578,
      76,   180,   181,   182,   697,    76,   185,   186,   701,    76,
     703,   704,    17,   656,   657,   658,   659,   710,   557,   712,
     773,   560,    18,   768,   240,   770,   196,   197,   773,    15,
      16,   610,   571,   572,     5,   697,     8,   567,   700,   701,
     785,   703,   704,   705,   706,   707,   236,   709,   710,   796,
     712,   798,   805,   214,   215,   216,   611,   612,     7,    77,
     805,   700,    80,    81,    82,    89,    44,    45,   803,     7,
     709,   733,   734,   735,   736,   768,     4,     5,   721,    76,
     104,   880,   613,   219,   220,   882,    59,    60,     7,   883,
      72,    73,   785,   117,   733,   734,   735,   736,   235,   123,
     895,   656,   657,   658,   659,    83,   768,    87,   770,    89,
     235,   773,     1,   235,    92,     4,   235,     6,   913,    76,
      98,   700,    87,   785,    89,   149,   150,   107,    76,   109,
     110,   770,   112,    76,   773,    76,   114,    26,    27,     8,
     120,   121,   107,   805,   109,   110,   111,   112,    66,    67,
      68,    76,   719,   719,    30,   100,    87,   736,   697,   113,
     699,    31,   701,    33,    87,   110,   805,    77,    38,    39,
      40,   710,   117,   712,    87,   742,   742,     5,   123,   124,
       1,    70,    71,   936,    76,    74,   242,     8,     9,    10,
       7,   936,   828,   829,   773,    16,   226,    77,    87,   729,
      59,    60,    61,    62,    63,    64,     7,    31,   236,    33,
     741,    35,   743,   744,    38,    39,    40,    77,   741,    77,
     743,   744,    93,    94,    95,    96,    97,    77,   239,   768,
      77,    77,    53,   234,    55,    56,   803,   803,   127,    76,
      61,   234,    63,    64,    65,   195,   785,    76,   236,    70,
      76,    72,     5,    76,    85,    86,    29,     8,     5,   235,
      81,    82,    76,    30,    77,    86,   235,   235,    99,    77,
     101,   102,   103,   115,   936,   202,   203,   204,   205,   206,
     847,   847,   812,   813,   814,   116,   117,   118,   819,    76,
      16,   274,   841,   746,   825,   826,   827,   936,   947,   946,
      65,   814,   217,   876,     0,     1,   499,   838,     4,   866,
       6,   507,   929,   711,   845,   846,   895,   848,   849,   563,
     895,   716,   569,   846,   573,   848,   849,   634,   673,   574,
      26,    27,   575,   721,   913,    31,   262,    33,   913,    35,
     706,   705,    38,    39,    40,   707,   200,   236,    44,    45,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,   893,   894,    -1,    31,    32,    33,    34,   201,
      -1,    37,    38,   904,    40,    41,    -1,    43,    -1,   910,
      -1,    77,    -1,    -1,   915,    -1,    -1,    83,    -1,     1,
      -1,    -1,     4,    -1,     6,    -1,    92,    -1,    -1,    -1,
     967,   967,    98,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      -1,    23,    -1,    -1,    26,    27,    28,    -1,   114,    -1,
      -1,    31,    -1,    33,    -1,    35,    38,    -1,    38,    39,
      40,   962,    -1,    -1,    44,    45,    -1,   968,   969,    -1,
      -1,    -1,   973,   974,   975,   968,   969,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    -1,    -1,
      -1,    -1,    84,    83,    -1,    87,    88,    -1,    -1,    -1,
      92,    -1,    92,    -1,    -1,    -1,    98,    -1,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,   114,    -1,   114,    -1,    -1,   119,    -1,    -1,
     122,    -1,    -1,   125,   126,    -1,    -1,   129,    -1,    -1,
     132,    -1,   134,    -1,    -1,    -1,    -1,   139,   140,    -1,
     142,   143,   144,    -1,    -1,   147,   148,    -1,    -1,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
      -1,    -1,   174,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   184,    -1,    -1,   187,    -1,    -1,    -1,    -1,
      -1,   193,    -1,    -1,    -1,    -1,   198,    -1,    -1,    -1,
      -1,     1,    -1,    -1,     4,   207,     6,    -1,   210,   211,
     212,   213,    -1,    -1,    -1,   217,    -1,    -1,    -1,   221,
     222,   223,    -1,    23,    -1,   227,    26,    27,    28,    -1,
      -1,   233,    -1,   235,   236,   237,   238,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,   107,    -1,    -1,   110,
      -1,    71,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      -1,    -1,   123,    -1,    84,    -1,   127,    87,    88,   130,
     131,    -1,    92,    -1,   135,   136,   137,   138,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,   119,
      -1,    -1,   122,    -1,    -1,   125,   126,    -1,    -1,   129,
      -1,    -1,   132,    -1,   134,    -1,    -1,    -1,    -1,   139,
     140,    -1,   142,   143,   144,    -1,    -1,   147,   148,    -1,
      -1,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,    -1,    -1,   174,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   184,    -1,    -1,   187,    -1,    -1,
      -1,    -1,    -1,   193,    -1,    -1,    -1,    -1,   198,    -1,
      -1,    -1,    -1,     1,    -1,    -1,     4,   207,     6,    -1,
     210,   211,   212,   213,    -1,    -1,    -1,   217,    -1,    -1,
      -1,   221,   222,   223,    -1,    23,    -1,   227,    26,    27,
      28,    -1,    -1,   233,    -1,   235,   236,   237,   238,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,
      88,    -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,   119,    -1,    -1,   122,    -1,    -1,   125,   126,    -1,
      -1,   129,    -1,    -1,   132,    -1,   134,    -1,    -1,    -1,
      -1,   139,   140,    -1,   142,   143,   144,    -1,    -1,   147,
     148,    -1,    -1,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,     5,    -1,   174,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,   187,
      21,    -1,    23,    -1,    -1,   193,    -1,    28,    -1,    -1,
     198,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   207,
      -1,    -1,   210,   211,   212,   213,    -1,    -1,    -1,   217,
      -1,    -1,    -1,   221,   222,   223,    -1,    -1,    -1,   227,
      -1,    -1,    -1,    -1,    65,   233,    -1,   235,   236,   237,
     238,    -1,    -1,    -1,    -1,    76,    77,    78,    79,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,   102,    -1,    -1,     5,    -1,    -1,   108,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,   119,    -1,
      21,   122,    23,    -1,   125,   126,    -1,    28,   129,    -1,
      -1,   132,    -1,   134,    -1,    -1,    -1,    -1,   139,   140,
      -1,   142,   143,   144,    -1,    -1,   147,   148,    -1,    -1,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,    -1,    -1,   174,    -1,    76,    77,    78,    79,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,   102,    -1,    -1,    -1,    -1,    -1,   108,    -1,   210,
     211,     5,   213,   114,    -1,    -1,    -1,    -1,   119,    -1,
      -1,   122,   223,    -1,   125,   126,   227,    21,   129,    23,
      -1,   132,    -1,   134,    28,    -1,   237,   238,   139,   140,
      -1,   142,   143,   144,    -1,    -1,   147,   148,    -1,    -1,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,    -1,    -1,   174,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,   102,   210,
     211,    -1,   213,    -1,   108,    -1,    -1,    -1,    -1,    -1,
     114,    -1,   223,    -1,    -1,   119,   227,    -1,   122,    -1,
      -1,   125,   126,    -1,    -1,   129,   237,   238,   132,    -1,
     134,    -1,    -1,    -1,    -1,   139,   140,    -1,   142,   143,
     144,    -1,    -1,   147,   148,    -1,    -1,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,    -1,    -1,
     174,     9,    10,    11,    12,    13,    14,    85,    86,    -1,
      -1,    89,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    99,   100,   101,   102,   103,   104,   105,   106,   107,
      -1,    -1,    -1,    -1,    -1,    -1,   210,   211,    -1,   213,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   223,
      -1,    -1,    -1,   227,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,   237,   238,    -1,    -1,    -1,    76,    77,
      78,    79,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      88,    -1,    -1,    -1,    92,   103,    -1,    -1,   106,    -1,
      98,    -1,    -1,    -1,   102,    -1,    -1,   115,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,   119,    -1,    21,   122,    23,    -1,   125,   126,    -1,
      28,   129,    -1,    -1,   132,    -1,   134,    -1,    -1,    -1,
      -1,   139,   140,    -1,    -1,    -1,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      88,    -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,   102,    -1,   214,    -1,    -1,    -1,
     108,    -1,   210,   211,    -1,   213,   114,    -1,    -1,    -1,
      -1,   119,    -1,    21,   122,    23,    -1,   125,   126,    -1,
      -1,   129,    -1,    -1,   132,    -1,   134,   235,    -1,   237,
      -1,   139,   140,    -1,   142,   143,   144,    -1,    -1,   147,
     148,    -1,    -1,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,    -1,    -1,   174,    -1,    76,    77,
      78,    79,    -1,    -1,    -1,    -1,    84,    -1,    -1,    21,
      88,    23,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,
     108,    -1,   210,   211,    -1,   213,   114,    -1,    -1,    -1,
      -1,   119,    -1,    -1,   122,   223,    -1,   125,   126,   227,
      -1,   129,    -1,    -1,   132,    -1,   134,    -1,    -1,   237,
     238,   139,   140,    -1,    76,    77,    78,    79,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
     102,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,   114,    -1,    -1,    -1,    -1,   119,    -1,    21,
     122,    23,    -1,   125,   126,    -1,    -1,   129,    -1,    -1,
     132,    -1,   134,    -1,    -1,    -1,    -1,   139,   140,    -1,
      -1,    -1,   210,   211,    -1,   213,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   235,    -1,   237,
     238,    -1,    -1,    -1,    76,    77,    78,    79,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
     102,    -1,    -1,    -1,    -1,    -1,   108,    -1,   210,   211,
      -1,   213,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,
     122,    23,    -1,   125,   126,    -1,    28,   129,    -1,    -1,
     132,    -1,   134,   235,    -1,   237,    38,   139,   140,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,   210,   211,
      -1,   213,   114,    -1,    -1,    -1,    -1,   119,    -1,    -1,
     122,    -1,    -1,   125,   126,    -1,    -1,   129,    -1,    -1,
     132,    -1,   134,    -1,    -1,   237,    -1,   139,   140,    -1,
     142,   143,   144,    -1,    -1,   147,   148,    -1,    -1,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
      -1,    -1,   174,    23,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,   184,    -1,    -1,   187,    -1,    -1,    -1,    -1,
      -1,   193,    -1,    -1,    -1,    -1,   198,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   207,    -1,    -1,   210,   211,
     212,   213,    -1,    -1,    -1,   217,    -1,    -1,    -1,   221,
     222,   223,    -1,    -1,    -1,   227,    76,    77,    78,    79,
      -1,   233,    -1,   235,    84,   237,   238,    -1,    88,    -1,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,   119,
      -1,    -1,   122,    23,    -1,   125,   126,    -1,    28,   129,
      -1,    -1,   132,    -1,   134,    -1,    -1,    -1,    -1,   139,
     140,    -1,   142,   143,   144,    -1,    -1,   147,   148,    -1,
      -1,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,    -1,    -1,   174,    -1,    76,    77,    78,    79,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,   119,
      -1,    -1,   122,   223,    -1,   125,   126,   227,    -1,   129,
      -1,    -1,   132,    -1,   134,   235,    -1,   237,   238,   139,
     140,    -1,   142,   143,   144,    23,    -1,   147,   148,    -1,
      -1,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,    -1,    -1,   174,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    -1,    -1,    23,    -1,    84,    -1,    -1,    -1,
      88,    -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,   223,   102,    -1,    -1,   227,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,   114,   237,   238,    -1,
      -1,   119,    -1,    -1,   122,    -1,    -1,   125,   126,    -1,
      -1,   129,    -1,    -1,   132,    -1,   134,    76,    77,    78,
      79,   139,   140,    -1,    77,    84,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,   108,
     103,    -1,    -1,   106,    -1,   114,    -1,    -1,    -1,    -1,
     119,    -1,   115,   122,    -1,    -1,   125,   126,    -1,    -1,
     129,    -1,    -1,   132,    -1,   134,    -1,    -1,    -1,    -1,
     139,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   210,   211,    -1,   213,    -1,    -1,    -1,    -1,
      -1,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   237,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   210,   211,    -1,   213,    -1,    -1,    -1,    -1,    -1,
      -1,   214,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   237
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   244,     0,     1,     4,     6,    26,    27,    31,    33,
      35,    38,    39,    40,    44,    45,    46,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    83,    92,    98,
     114,   245,   247,   248,   249,   250,   290,   291,   292,   293,
     299,   245,    78,    77,   287,   292,   293,   299,   292,   295,
     295,   295,   250,    35,   251,    31,    33,    38,    39,    40,
     252,    35,   253,    31,    33,    35,    38,    39,    40,   254,
      31,    32,    33,    34,    37,    38,    40,    41,    43,    75,
     255,    31,    33,    38,    43,   256,    33,   257,    23,    28,
      76,    77,    78,    79,    84,    88,    92,    98,   108,   114,
     119,   122,   125,   126,   129,   132,   134,   139,   140,   142,
     143,   144,   147,   148,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   174,   223,   227,   237,   238,
     264,   288,   365,   366,   367,   368,   369,   409,   412,   416,
     417,   418,   420,   426,   427,   429,   431,   433,   435,   437,
     439,   441,   443,   445,   447,   449,   451,   453,   455,   457,
     459,   460,   462,   464,   466,   468,   470,   472,    43,   231,
     232,   258,   263,    77,   259,   260,     0,   245,   287,   287,
     229,   298,    38,    59,    60,    61,    62,    63,    64,    75,
     153,   174,   184,   187,   193,   198,   207,   210,   211,   212,
     213,   217,   221,   222,   233,   235,   303,   304,   305,   306,
     307,   308,   312,   313,   316,   317,   324,   327,   331,   332,
     334,   335,   340,   341,   343,   344,   346,   347,   350,   351,
     358,   360,   361,   364,   368,   373,   374,   375,   376,   377,
     378,   383,   384,   385,   397,   408,   412,   413,   424,   425,
     426,   245,   234,   265,   268,   303,   287,   270,   272,   365,
     385,   275,   293,   300,   292,   293,   295,   295,   295,   299,
     292,   293,   300,   295,   295,   295,   292,   291,   302,   293,
     302,   302,   295,   295,   302,   302,    31,    32,   292,   293,
     295,   302,   293,    80,    81,    82,   287,   428,    85,    86,
     154,   155,   158,   371,   372,    85,    86,    87,   430,    87,
      89,    90,    91,   432,    93,    94,    95,    96,    97,   434,
      85,    86,    89,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   436,    87,    89,   107,   109,   110,   111,   112,
     438,    85,    86,    99,   101,   102,   103,   116,   117,   118,
     440,    87,    89,   107,   109,   110,   112,   120,   121,   442,
     100,   110,   117,   123,   124,   444,   110,   124,   446,   117,
     127,   128,   448,   103,   107,   130,   131,   450,   107,   130,
     131,   133,   452,   107,   110,   123,   127,   130,   131,   135,
     136,   137,   138,   454,    87,   130,   131,   456,   107,   130,
     131,   141,   458,    87,   100,   117,   145,   172,   173,   419,
     463,   146,   465,   146,   467,   100,   117,   461,    89,   104,
     117,   123,   149,   150,   469,   100,   117,   471,    87,   100,
     107,   117,   123,   473,    77,   103,   106,   115,   214,   410,
     411,   412,    77,   106,   154,   180,   185,   186,   421,   423,
     214,   224,   415,   378,   384,   287,   377,   263,    32,    34,
      36,    37,    70,   261,    76,    46,    47,   359,   287,   287,
      77,   410,    77,   421,   194,   196,   197,   325,    65,    65,
       4,   246,   386,   387,   230,   301,   306,   185,   186,   314,
     315,   127,   188,   189,   190,   191,   192,   318,   319,   208,
     333,     5,    21,    65,    84,    88,    92,    98,   102,   108,
     114,   119,   122,   125,   126,   129,   132,   134,   139,   140,
     210,   211,   213,   336,   337,   338,   339,   366,   367,   368,
     379,   380,   381,   382,   400,   401,   402,   403,   404,   406,
      65,   214,   215,   216,   342,   348,   349,    65,   345,   348,
     218,   219,   220,   352,   353,   354,   355,    31,   235,   362,
     363,    15,    16,    17,    18,   240,     8,    24,    40,     9,
      10,    11,    12,    13,    14,    23,    84,    88,    92,    98,
     108,   114,   119,   122,   125,   126,   129,   132,   134,   139,
     140,   366,   367,   382,   385,   398,   399,   404,   405,   406,
     407,    38,    38,   396,   398,   399,   235,   235,   235,   235,
      42,   297,   303,   265,   268,   270,   272,   275,   303,   272,
     295,   302,   287,     7,     8,    87,   158,   159,   370,   241,
      85,    86,   106,   180,   181,   182,   422,   423,   225,   225,
     239,   262,   263,   356,   357,   378,    38,    38,    38,    38,
     196,   197,   328,    76,   338,   384,   382,   385,   390,   391,
     394,   404,   405,     7,   236,   288,    76,    76,   315,    58,
      84,    98,   134,   161,   321,   288,    76,    76,    76,   288,
     320,   319,   108,   119,   134,   209,   338,     5,   338,     8,
      40,     5,   348,    15,    16,    17,    18,   240,    20,    22,
       5,     7,     5,   338,   338,   353,     7,   287,   378,   388,
     389,   235,   363,   368,   368,   373,   374,   375,   377,    23,
     235,   309,   399,     7,     7,     8,   238,   399,   384,   384,
     245,   267,   269,   271,   276,    76,   235,   235,   235,   235,
      76,   372,    76,    76,    76,   366,    68,   301,   392,   393,
     384,   384,   384,   384,    76,    77,   186,   326,    30,   246,
       5,   246,   392,   246,   387,   113,   110,   113,   322,   323,
      87,    87,    77,    87,   338,     5,   368,   399,   338,   406,
     406,   400,   401,   402,    76,   404,   338,   349,   338,   348,
     355,   306,   392,   388,   287,   246,   310,   311,   404,   404,
     404,   399,    33,    38,    40,   127,   236,   245,   247,   266,
      71,    87,   236,   245,   247,   282,   285,   303,    68,    69,
      70,    71,    74,    87,   127,   236,   245,   247,   277,    70,
      87,   127,   236,   245,   247,   277,   267,   269,   271,   276,
       7,   242,   226,   414,   228,   414,    77,   289,   393,    20,
      77,   338,   395,   404,   405,   408,     7,    77,    77,    77,
     338,   348,   348,   236,   306,   390,     7,   236,   239,   287,
     294,   287,   296,   296,    77,   245,    59,    60,   286,    77,
     245,   245,   245,   289,   289,   234,    72,    73,   278,    76,
      77,   101,   102,   154,   279,   280,   281,    66,    67,    68,
     273,   274,   245,   234,   279,   273,   245,   236,   236,   236,
     236,    76,    76,    76,   202,   203,   204,   205,   206,   330,
     195,   329,   246,   323,   236,     5,   246,   311,   268,   270,
     275,    29,   245,   245,   272,   245,     8,     7,   245,   272,
       5,   245,   414,   329,    76,   408,   235,   235,   235,    77,
     281,   274,   279,    77,   185,   186,   246,   269,   271,   276,
      30,   284,   245,   236,   236,   236,    77,   115,   245,   245,
     245,    22,    76,   283,    76
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   243,   244,   244,   245,   245,   246,   246,   247,   247,
     247,   248,   248,   248,   248,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   251,   252,   252,   252,
     252,   252,   252,   252,   253,   254,   254,   254,   254,   254,
     254,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   256,   256,   256,   256,   257,   258,   258,   259,
     260,   260,   261,   261,   261,   261,   261,   261,   262,   262,
     263,   263,   264,   265,   266,   267,   267,   267,   267,   267,
     267,   267,   268,   269,   269,   269,   269,   269,   269,   270,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   272,
     272,   273,   273,   274,   274,   274,   275,   276,   276,   276,
     276,   276,   276,   276,   277,   277,   278,   278,   279,   280,
     280,   281,   281,   281,   281,   282,   283,   283,   284,   284,
     285,   286,   286,   287,   288,   288,   288,   289,   290,   290,
     291,   291,   291,   291,   291,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   299,   300,   301,   302,   302,   303,
     303,   304,   305,   305,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   307,   307,   308,   309,   309,   310,   310,   310,
     311,   312,   312,   313,   314,   314,   315,   315,   316,   316,
     317,   318,   318,   319,   319,   319,   319,   319,   319,   320,
     321,   321,   321,   321,   321,   322,   322,   323,   323,   324,
     324,   325,   325,   325,   326,   326,   327,   328,   328,   328,
     329,   329,   329,   329,   330,   330,   330,   330,   330,   331,
     332,   333,   333,   333,   333,   333,   334,   335,   335,   336,
     336,   337,   338,   338,   338,   339,   339,   339,   339,   339,
     339,   339,   340,   340,   341,   342,   342,   342,   343,   343,
     344,   345,   345,   345,   345,   345,   346,   346,   347,   348,
     348,   349,   349,   349,   350,   350,   351,   352,   352,   353,
     353,   354,   354,   355,   355,   356,   356,   357,   358,   359,
     359,   360,   360,   361,   362,   362,   363,   364,   365,   366,
     366,   366,   367,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   368,   369,   370,   370,   370,   371,   371,
     371,   371,   371,   372,   372,   373,   373,   373,   374,   374,
     375,   375,   376,   376,   377,   378,   378,   379,   380,   381,
     382,   382,   382,   383,   384,   384,   384,   385,   386,   386,
     386,   387,   387,   387,   388,   388,   389,   390,   390,   391,
     392,   392,   393,   393,   394,   394,   395,   395,   396,   396,
     397,   397,   397,   397,   398,   398,   399,   399,   399,   400,
     400,   400,   401,   401,   402,   402,   403,   403,   404,   405,
     405,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   407,   407,   407,   407,   407,   407,   408,   408,
     408,   408,   408,   408,   409,   409,   409,   410,   410,   411,
     411,   411,   411,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   412,   412,   412,
     412,   413,   413,   413,   413,   414,   414,   415,   415,   416,
     417,   417,   418,   419,   419,   420,   420,   420,   421,   421,
     421,   421,   422,   422,   422,   422,   422,   422,   422,   423,
     423,   424,   424,   425,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     427,   428,   428,   428,   429,   430,   430,   430,   431,   432,
     432,   432,   432,   433,   434,   434,   434,   434,   434,   435,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   437,   438,   438,   438,   438,   438,   438,   438,
     439,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     441,   442,   442,   442,   442,   442,   442,   442,   442,   443,
     444,   444,   444,   444,   444,   445,   446,   446,   447,   448,
     448,   448,   449,   450,   450,   450,   450,   451,   452,   452,
     452,   452,   453,   454,   454,   454,   454,   454,   454,   454,
     454,   454,   454,   455,   456,   456,   456,   457,   458,   458,
     458,   458,   459,   459,   459,   459,   459,   459,   459,   460,
     461,   461,   462,   463,   463,   463,   463,   464,   465,   466,
     467,   468,   469,   469,   469,   469,   469,   469,   470,   471,
     471,   472,   473,   473,   473,   473,   473
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       2,     1,     1,     2,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     6,     2,
       6,     3,     2,     6,     6,     3,     3,     2,     6,     2,
       6,     6,     6,     3,     3,     2,     2,     2,     2,     2,
       3,     2,     2,     2,     2,     2,     2,     2,     3,     3,
       2,     2,     2,     2,     2,     2,     3,     2,     1,     3,
       0,     1,     0,     1,     1,     1,     1,     1,     0,     1,
       1,     1,     1,     0,     2,     0,     2,     2,     3,     8,
       8,     8,     0,     0,     2,     2,     3,     3,     3,     0,
       0,     2,     2,     4,     4,     4,     4,     4,     3,     1,
       1,     3,     1,     1,     1,     1,     0,     0,     2,     2,
       6,     4,     4,     3,     2,     2,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     7,     1,     2,     2,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     2,
       1,     2,     2,     1,     2,     2,     2,     0,     1,     1,
       2,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     2,     1,     3,     3,
       5,     1,     2,     1,     1,     2,     2,     2,     1,     2,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     1,
       2,     2,     1,     1,     1,     3,     1,     1,     1,     7,
       6,     1,     1,     0,     1,     1,     4,     1,     1,     0,
       0,     3,     3,     3,     1,     1,     1,     1,     1,     2,
       1,     0,     4,     4,     4,     3,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     2,     3,     4,     2,
       3,     2,     2,     1,     1,     3,     4,     1,     2,     1,
       1,     2,     3,     1,     3,     4,     3,     5,     3,     1,
       3,     1,     1,     1,     1,     2,     1,     1,     2,     2,
       1,     1,     3,     1,     1,     1,     2,     1,     4,     1,
       1,     6,     5,     1,     1,     2,     2,     1,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     3,     3,     3,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     3,
       3,     3,     3,     5,     1,     2,     1,     1,     2,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     5,     3,     3,     1,     1,     1,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     3,     4,     1,     0,     2,     1,     1,     5,
       7,     5,     2,     1,     1,     2,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       6,     1,     1,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     2,     1,     1,     2,     1,
       1,     1,     2,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     1,     1,     1,     1,     2,     4,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     1,     1,     1,     1,     1
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
      yyerror (&yylloc, scanner, state, YY_("syntax error: cannot back up")); \
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
                  Type, Value, Location, scanner, state); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct parser_state *state)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct parser_state *state)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, state);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, void *scanner, struct parser_state *state)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , scanner, state);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, state); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void *scanner, struct parser_state *state)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (state);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 77: /* "string"  */
#line 232 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2886 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 78: /* "quoted string"  */
#line 232 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2892 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 79: /* "string with a trailing asterisk"  */
#line 232 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2898 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 248: /* line  */
#line 436 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2904 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 249: /* base_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2910 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 250: /* add_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2916 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 251: /* replace_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2922 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 252: /* create_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2928 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 253: /* insert_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2934 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 254: /* delete_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2940 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 255: /* list_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2946 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 256: /* flush_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2952 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 257: /* rename_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2958 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 258: /* export_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2964 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 259: /* monitor_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2970 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 260: /* monitor_event  */
#line 612 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2976 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 264: /* describe_cmd  */
#line 439 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2982 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 265: /* table_block_alloc  */
#line 451 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 2988 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 268: /* chain_block_alloc  */
#line 453 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 2994 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 270: /* set_block_alloc  */
#line 462 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3000 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 272: /* set_block_expr  */
#line 533 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3006 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 275: /* map_block_alloc  */
#line 465 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 3012 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 281: /* type_identifier  */
#line 428 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3018 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 284: /* dev_spec  */
#line 448 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3024 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 287: /* identifier  */
#line 428 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3030 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 288: /* string  */
#line 428 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3036 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 292: /* table_spec  */
#line 442 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3042 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 293: /* chain_spec  */
#line 442 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3048 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 294: /* chain_identifier  */
#line 442 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3054 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 295: /* set_spec  */
#line 444 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3060 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 296: /* set_identifier  */
#line 444 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3066 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 297: /* handle_spec  */
#line 442 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3072 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 298: /* position_spec  */
#line 442 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3078 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 299: /* rule_position  */
#line 442 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3084 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 300: /* ruleid_spec  */
#line 442 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3090 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 301: /* comment_spec  */
#line 428 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3096 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 302: /* ruleset_spec  */
#line 442 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 3102 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 303: /* rule  */
#line 455 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 3108 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 305: /* stmt_list  */
#line 468 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 3114 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 306: /* stmt  */
#line 470 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3120 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 307: /* verdict_stmt  */
#line 470 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3126 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 308: /* verdict_map_stmt  */
#line 527 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3132 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 309: /* verdict_map_expr  */
#line 530 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3138 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 310: /* verdict_map_list_expr  */
#line 530 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3144 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 311: /* verdict_map_list_member_expr  */
#line 530 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3150 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 312: /* counter_stmt  */
#line 472 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3156 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 313: /* counter_stmt_alloc  */
#line 472 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3162 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 316: /* log_stmt  */
#line 480 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3168 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 317: /* log_stmt_alloc  */
#line 480 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3174 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 324: /* limit_stmt  */
#line 483 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3180 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 326: /* quota_unit  */
#line 448 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 3186 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 327: /* quota_stmt  */
#line 483 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3192 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 331: /* reject_stmt  */
#line 486 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3198 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 332: /* reject_stmt_alloc  */
#line 486 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3204 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 334: /* nat_stmt  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3210 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* nat_stmt_alloc  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3216 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 336: /* concat_stmt_expr  */
#line 518 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3222 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 337: /* map_stmt_expr  */
#line 518 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3228 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* stmt_expr  */
#line 518 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3234 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 340: /* masq_stmt  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3240 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 341: /* masq_stmt_alloc  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3246 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 343: /* redir_stmt  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3252 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* redir_stmt_alloc  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3258 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* dup_stmt  */
#line 494 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3264 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* fwd_stmt  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3270 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* queue_stmt  */
#line 491 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3276 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 351: /* queue_stmt_alloc  */
#line 491 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3282 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* set_elem_expr_stmt  */
#line 537 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3288 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 357: /* set_elem_expr_stmt_alloc  */
#line 537 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3294 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* set_stmt  */
#line 498 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3300 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* flow_stmt  */
#line 501 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3306 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* flow_stmt_alloc  */
#line 501 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3312 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 364: /* match_stmt  */
#line 470 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3318 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 365: /* variable_expr  */
#line 504 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3324 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 366: /* symbol_expr  */
#line 504 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3330 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 367: /* integer_expr  */
#line 504 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3336 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 368: /* primary_expr  */
#line 506 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3342 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 369: /* fib_expr  */
#line 607 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3348 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 373: /* shift_expr  */
#line 506 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3354 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 374: /* and_expr  */
#line 506 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3360 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* exclusive_or_expr  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3366 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* inclusive_or_expr  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3372 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* basic_expr  */
#line 510 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3378 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 378: /* concat_expr  */
#line 521 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3384 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 379: /* prefix_rhs_expr  */
#line 515 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3390 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 380: /* range_rhs_expr  */
#line 515 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3396 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 381: /* wildcard_rhs_expr  */
#line 515 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3402 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 382: /* multiton_rhs_expr  */
#line 513 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3408 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* map_expr  */
#line 524 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3414 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* expr  */
#line 543 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3420 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* set_expr  */
#line 533 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3426 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* set_list_expr  */
#line 533 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3432 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* set_list_member_expr  */
#line 533 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3438 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 388: /* flow_key_expr  */
#line 540 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3444 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* flow_key_expr_alloc  */
#line 540 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3450 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* set_elem_expr  */
#line 535 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3456 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 391: /* set_elem_expr_alloc  */
#line 535 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3462 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* set_lhs_expr  */
#line 535 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3468 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* set_rhs_expr  */
#line 535 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3474 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 396: /* initializer_expr  */
#line 543 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3480 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 397: /* relational_expr  */
#line 554 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3486 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 398: /* list_rhs_expr  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3492 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* rhs_expr  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3498 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* shift_rhs_expr  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3504 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* and_rhs_expr  */
#line 550 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3510 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* exclusive_or_rhs_expr  */
#line 550 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3516 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 403: /* inclusive_or_rhs_expr  */
#line 550 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3522 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* basic_rhs_expr  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3528 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 405: /* concat_rhs_expr  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3534 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* primary_rhs_expr  */
#line 548 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3540 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* verdict_expr  */
#line 504 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3546 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 409: /* meta_expr  */
#line 595 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3552 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 413: /* meta_stmt  */
#line 478 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3558 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* numgen_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3564 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 417: /* hash_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3570 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* rt_expr  */
#line 599 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3576 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* ct_expr  */
#line 603 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3582 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* ct_stmt  */
#line 476 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3588 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 425: /* payload_stmt  */
#line 474 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3594 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* payload_expr  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3600 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 427: /* payload_raw_expr  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3606 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 429: /* eth_hdr_expr  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3612 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 431: /* vlan_hdr_expr  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3618 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 433: /* arp_hdr_expr  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3624 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* ip_hdr_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3630 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* icmp_hdr_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3636 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 439: /* ip6_hdr_expr  */
#line 570 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3642 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 441: /* icmp6_hdr_expr  */
#line 570 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3648 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* auth_hdr_expr  */
#line 573 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3654 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 445: /* esp_hdr_expr  */
#line 573 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3660 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 447: /* comp_hdr_expr  */
#line 573 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3666 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 449: /* udp_hdr_expr  */
#line 576 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3672 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 451: /* udplite_hdr_expr  */
#line 576 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3678 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 453: /* tcp_hdr_expr  */
#line 576 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3684 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 455: /* dccp_hdr_expr  */
#line 579 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3690 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 457: /* sctp_hdr_expr  */
#line 579 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3696 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 459: /* exthdr_expr  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3702 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 460: /* hbh_hdr_expr  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3708 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 462: /* rt_hdr_expr  */
#line 588 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3714 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 464: /* rt0_hdr_expr  */
#line 588 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3720 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 466: /* rt2_hdr_expr  */
#line 588 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3726 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 468: /* frag_hdr_expr  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3732 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 470: /* dst_hdr_expr  */
#line 585 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3738 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 472: /* mh_hdr_expr  */
#line 591 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3744 "parser_bison.c" /* yacc.c:1257  */
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
yyparse (void *scanner, struct parser_state *state)
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
#line 113 "parser_bison.y" /* yacc.c:1429  */
{
	location_init(scanner, state, &yylloc);
#ifdef DEBUG
	if (debug_level & DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (debug_level & DEBUG_PARSER)
		yydebug = 1;
#endif
}

#line 3863 "parser_bison.c" /* yacc.c:1429  */
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
#line 619 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[0].cmd) != NULL) {
					LIST_HEAD(list);

					(yyvsp[0].cmd)->location = (yylsp[0]);

					list_add_tail(&(yyvsp[0].cmd)->list, &list);
					if (cmd_evaluate(&state->ectx, (yyvsp[0].cmd)) < 0) {
						if (++state->nerrs == max_errors)
							YYABORT;
					} else
						list_splice_tail(&list, &state->cmds);
				}
			}
#line 4065 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 8:
#line 644 "parser_bison.y" /* yacc.c:1646  */
    {
				if (scanner_include_file(scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 4077 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 9:
#line 652 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, (yyvsp[-3].string)) != NULL) {
					erec_queue(error(&(yylsp[-3]), "redefinition of symbol '%s'", (yyvsp[-3].string)),
						   state->msgs);
					YYERROR;
				}

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 4094 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 665 "parser_bison.y" /* yacc.c:1646  */
    {
				if (++state->nerrs == max_errors)
					YYABORT;
				yyerrok;
			}
#line 4104 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 11:
#line 672 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 4110 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 673 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 4116 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 674 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 4122 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 676 "parser_bison.y" /* yacc.c:1646  */
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
						if (++state->nerrs == max_errors)
							YYABORT;
					} else
						list_splice_tail(&list, &state->cmds);
				}
				(yyval.cmd) = NULL;

				YYACCEPT;
			}
#line 4153 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 704 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4159 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 16:
#line 705 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4165 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 706 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 707 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4177 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 708 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4183 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 709 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4189 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 710 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4195 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 711 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 712 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 713 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4213 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 714 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4219 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 715 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 4225 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 719 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4233 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 724 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 4243 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 730 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4251 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 735 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 4262 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 742 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 4270 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 746 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 4278 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 751 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 4288 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 758 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 4298 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 764 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 4306 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 770 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 4314 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 776 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4322 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 781 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 4332 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 787 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4340 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 792 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 4351 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 800 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 4361 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 42:
#line 807 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 4371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 813 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 4379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 819 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 4387 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 825 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4395 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 829 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4403 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 833 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4411 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 837 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4419 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 841 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4427 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 845 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 4435 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 851 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4443 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 855 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4451 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 859 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4459 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 863 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4467 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 867 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4475 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 56:
#line 871 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4483 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 875 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4491 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 879 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4499 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 883 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4507 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 887 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4515 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 891 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4523 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 897 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4531 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 901 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4539 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 905 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4547 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 909 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4555 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 915 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 4564 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 922 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct export *export = export_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_EXPORT, &h, &(yyloc), export);
			}
#line 4574 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 928 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct export *export = export_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_EXPORT, &h, &(yyloc), export);
			}
#line 4584 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 936 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 4595 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 944 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 4601 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 945 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 4607 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 948 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 4613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 949 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 4619 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 950 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 4625 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 75:
#line 951 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 4631 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 952 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 4637 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 953 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 4643 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 956 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 4649 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 960 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_XML; }
#line 4655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 961 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 4661 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 82:
#line 965 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 4671 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 83:
#line 973 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 4680 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 84:
#line 980 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strcmp((yyvsp[0].string), "dormant") == 0) {
					(yyvsp[-2].table)->flags = TABLE_F_DORMANT;
				} else {
					erec_queue(error(&(yylsp[0]), "unknown table option %s", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}
			}
#line 4694 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 991 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 4700 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 998 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 4713 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1009 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 4725 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1019 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 4737 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1029 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 4746 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1035 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 4752 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1041 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 4761 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1048 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 4769 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1053 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 4775 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1057 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->keytype = (yyvsp[-1].datatype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4784 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1062 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4793 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1067 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4802 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1072 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4811 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1077 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4820 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1089 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 4828 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1095 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SET_F_CONSTANT; }
#line 4834 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1096 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SET_F_INTERVAL; }
#line 4840 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1097 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SET_F_TIMEOUT; }
#line 4846 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1101 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
				(yyval.set)->flags |= NFT_SET_MAP;
			}
#line 4855 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1107 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 4861 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1113 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->keytype  = (yyvsp[-3].datatype);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].datatype);
				(yyval.set) = (yyvsp[-5].set);
			}
#line 4871 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1119 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags |= (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4880 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1124 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4889 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1132 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 4897 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1136 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 4905 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1141 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 4911 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1142 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 4917 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1146 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[0].val) & ~TYPE_MASK)
					(yyval.datatype) = concat_type_alloc((yyvsp[0].val));
				else
					(yyval.datatype) = datatype_lookup((yyvsp[0].val));
			}
#line 4928 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1155 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct datatype *dtype = datatype_lookup_byname((yyvsp[0].string));
				if (dtype == NULL) {
					erec_queue(error(&(yylsp[0]), "unknown datatype %s", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}
				(yyval.val) = dtype->type;
			}
#line 4942 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1165 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct datatype *dtype = datatype_lookup_byname((yyvsp[0].string));
				if (dtype == NULL) {
					erec_queue(error(&(yylsp[0]), "unknown datatype %s", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}
				(yyval.val) = concat_subtype_add((yyval.val), dtype->type);
			}
#line 4956 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1176 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 4962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1177 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("mark"); }
#line 4968 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1178 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("dscp"); }
#line 4974 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1179 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("ecn"); }
#line 4980 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1183 "parser_bison.y" /* yacc.c:1646  */
    {
				const char *chain_type = chain_type_name_lookup((yyvsp[-5].string));

				if (chain_type == NULL) {
					erec_queue(error(&(yylsp[-5]), "unknown chain type %s", (yyvsp[-5].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[-7].chain)->type		= xstrdup(chain_type);
				xfree((yyvsp[-5].string));

				(yyvsp[-7].chain)->hookstr	= chain_hookname_lookup((yyvsp[-3].string));
				if ((yyvsp[-7].chain)->hookstr == NULL) {
					erec_queue(error(&(yylsp[-3]), "unknown chain hook %s", (yyvsp[-3].string)),
						   state->msgs);
					YYERROR;
				}
				xfree((yyvsp[-3].string));

				(yyvsp[-7].chain)->dev		= (yyvsp[-2].string);
				(yyvsp[-7].chain)->priority	= (yyvsp[0].val);
				(yyvsp[-7].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
#line 5008 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1208 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 5014 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1209 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = -(yyvsp[0].val); }
#line 5020 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1212 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 5026 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1213 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 5032 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1217 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].chain)->policy != -1) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].val);
			}
#line 5045 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1227 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_ACCEPT; }
#line 5051 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1228 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_DROP;   }
#line 5057 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1240 "parser_bison.y" /* yacc.c:1646  */
    {
				struct error_record *erec;
				uint64_t res;

				erec = time_parse(&(yylsp[0]), (yyvsp[0].string), &res);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.val) = res;
			}
#line 5073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1253 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 5079 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1257 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 5085 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1258 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 5091 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1259 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_INET; }
#line 5097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1260 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_ARP; }
#line 5103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1261 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 5109 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1262 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 5115 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1266 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table	= (yyvsp[0].string);
			}
#line 5125 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1274 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 5134 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1281 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 5143 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1288 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 5152 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1295 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 5161 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1302 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).handle.location	= (yyloc);
				(yyval.handle).handle.id		= (yyvsp[0].val);
			}
#line 5171 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1310 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).position.location	= (yyloc);
				(yyval.handle).position.id		= (yyvsp[0].val);
			}
#line 5181 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1318 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle) = (yyvsp[0].handle);
			}
#line 5189 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1322 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 5198 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1329 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-1].handle), &(yyvsp[0].handle));
				(yyval.handle) = (yyvsp[-1].handle);
			}
#line 5207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1336 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strlen((yyvsp[0].string)) > UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed", UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 5220 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1347 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 5229 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1352 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 5238 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1359 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 5246 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1363 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 5254 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1369 "parser_bison.y" /* yacc.c:1646  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 5268 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1381 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 5278 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1387 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 5287 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1414 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 5295 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1418 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 5303 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1424 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5311 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1430 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 5320 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1435 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 5331 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1444 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 5340 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1449 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 5349 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1457 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 5357 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1466 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 5365 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1472 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 5373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1479 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 5381 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1483 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 5389 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1493 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 5397 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1499 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 5405 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1506 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 5414 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1511 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 5423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1516 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 5432 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1521 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 5441 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1526 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 5450 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1531 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.logflags	|= (yyvsp[0].val);
			}
#line 5458 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1537 "parser_bison.y" /* yacc.c:1646  */
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
					erec_queue(error(&(yylsp[0]), "invalid log level", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}
			}
#line 5486 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1563 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[0].val);
			}
#line 5494 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1567 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_IPOPT;
			}
#line 5502 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1571 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_UID;
			}
#line 5510 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1575 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MACDECODE;
			}
#line 5518 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1579 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_MASK;
			}
#line 5526 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1585 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 5534 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1592 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPSEQ;
			}
#line 5542 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1596 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = NF_LOG_TCPOPT;
			}
#line 5550 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1602 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 5563 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1611 "parser_bison.y" /* yacc.c:1646  */
    {
				struct error_record *erec;
				uint64_t rate, unit;

				erec = rate_parse(&(yyloc), (yyvsp[-1].string), &rate, &unit);
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
#line 5585 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1630 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUOTA_F_INV; }
#line 5591 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1631 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 5597 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1632 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 5603 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1635 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("bytes"); }
#line 5609 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1636 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 5615 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1640 "parser_bison.y" /* yacc.c:1646  */
    {
				struct error_record *erec;
				uint64_t rate;

				erec = data_unit_parse(&(yyloc), (yyvsp[0].string), &rate);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.stmt) = quota_stmt_alloc(&(yyloc));
				(yyval.stmt)->quota.bytes	= (yyvsp[-1].val) * rate;
				(yyval.stmt)->quota.flags	= (yyvsp[-2].val);
			}
#line 5633 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1655 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 5639 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1656 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 5645 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1657 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 5651 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1660 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 5657 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1661 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 5663 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1662 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 5669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1664 "parser_bison.y" /* yacc.c:1646  */
    {
				struct error_record *erec;
				uint64_t rate;

				erec = data_unit_parse(&(yyloc), (yyvsp[0].string), &rate);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.val) = (yyvsp[-1].val) * rate;
			}
#line 5685 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1677 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL; }
#line 5691 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1678 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60; }
#line 5697 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1679 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 5703 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1680 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 5709 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1681 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 5715 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1688 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 5723 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1694 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 5732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1699 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmp_code_type;
			}
#line 5746 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1709 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpv6_code_type;
			}
#line 5760 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1719 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpx_code_type;
			}
#line 5773 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1728 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strcmp((yyvsp[0].string), "reset") == 0) {
					(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
				} else {
					erec_queue(error(&(yylsp[-1]), "unsupported reject type", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}
			}
#line 5787 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1743 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_SNAT;
			}
#line 5796 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1748 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_DNAT;
			}
#line 5805 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1756 "parser_bison.y" /* yacc.c:1646  */
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
#line 5826 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1775 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5834 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1786 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 5842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1790 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 5850 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1794 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 5859 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1799 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 5868 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1804 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 5876 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1808 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 5884 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1812 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 5892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1821 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = masq_stmt_alloc(&(yyloc)); }
#line 5898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1825 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->masq.proto = (yyvsp[0].expr);
			}
#line 5906 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1829 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->masq.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 5915 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1834 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 5923 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1843 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = redir_stmt_alloc(&(yyloc)); }
#line 5929 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1847 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 5937 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1851 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 5945 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1855 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 5953 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1859 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 5962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1864 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 5971 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1871 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 5980 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1876 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 5990 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1884 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.to = (yyvsp[0].expr);
			}
#line 5999 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1892 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6007 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1897 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 6013 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1898 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 6019 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1899 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 6025 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1907 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 6033 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1913 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 6041 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1920 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 6050 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1925 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 6058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1932 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1937 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 6072 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1938 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 6078 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1946 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 6086 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1952 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 6097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1960 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 6103 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1961 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 6109 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1965 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->flow.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->flow.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 6120 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1972 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->flow.key  = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->flow.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-4].stmt);
			}
#line 6131 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1981 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = flow_stmt_alloc(&(yyloc));
			}
#line 6139 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1987 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 6147 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1994 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->flow.table = (yyvsp[0].string);
			}
#line 6155 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 317:
#line 2000 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 6163 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 318:
#line 2006 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, (yyvsp[0].string)) == NULL) {
					erec_queue(error(&(yylsp[0]), "unknown identifier '%s'", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}

				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_DEFINE,
						       scope, (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 6181 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2023 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 6192 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 321:
#line 2030 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 6203 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 322:
#line 2039 "parser_bison.y" /* yacc.c:1646  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 6216 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2049 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6222 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2050 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6228 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2051 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6234 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2052 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6240 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2053 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6246 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 328:
#line 2054 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6252 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 329:
#line 2055 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6258 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2056 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6264 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2057 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6270 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2058 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2059 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 6282 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2063 "parser_bison.y" /* yacc.c:1646  */
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
#line 6307 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2085 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIF; }
#line 6313 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2086 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_OIFNAME; }
#line 6319 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2087 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) =NFT_FIB_RESULT_ADDRTYPE; }
#line 6325 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2090 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_SADDR; }
#line 6331 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2091 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_DADDR; }
#line 6337 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2092 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_MARK; }
#line 6343 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2093 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_IIF; }
#line 6349 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2094 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTA_FIB_F_OIF; }
#line 6355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2098 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 6363 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2106 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6371 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2110 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 349:
#line 2117 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6387 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2124 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6395 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 353:
#line 2131 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6403 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 356:
#line 2141 "parser_bison.y" /* yacc.c:1646  */
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
#line 6424 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 357:
#line 2160 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 6432 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 358:
#line 2166 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6440 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2172 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 6453 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 363:
#line 2188 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6461 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2199 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6470 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2206 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 6479 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2211 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 6488 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 371:
#line 2219 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6496 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 372:
#line 2223 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6504 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2227 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 6512 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2234 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 6521 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2241 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 6529 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2251 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 6537 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2257 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 6545 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2264 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val) * 1000;
			}
#line 6553 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2268 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 6561 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 390:
#line 2286 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 6569 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2290 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_FLAGCMP, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 6577 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 392:
#line 2294 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6585 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 393:
#line 2298 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-3]), (yyvsp[-3].val), (yyvsp[-4].expr), (yyvsp[-1].expr));
			}
#line 6593 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2304 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 6603 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2310 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 6613 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2317 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6619 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2318 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6625 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2319 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6631 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2324 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6639 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2328 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6647 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 403:
#line 2335 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 405:
#line 2342 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6663 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 407:
#line 2349 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6671 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2359 "parser_bison.y" /* yacc.c:1646  */
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
#line 6692 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2377 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6698 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2378 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6704 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2380 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ether");
			}
#line 6714 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2386 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ip");
			}
#line 6724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2392 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ip6");
			}
#line 6734 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2398 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "vlan");
			}
#line 6744 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2404 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "arp");
			}
#line 6754 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2410 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6765 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2417 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6776 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2424 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6787 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2431 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6798 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2438 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6809 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2445 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6820 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2452 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6831 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2459 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2466 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2473 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6864 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2480 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6875 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2487 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "snat");
			}
#line 6885 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2493 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "dnat");
			}
#line 6895 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2499 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ecn");
			}
#line 6905 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2506 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_EQ; }
#line 6911 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2507 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_NEQ; }
#line 6917 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2508 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LT; }
#line 6923 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2509 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GT; }
#line 6929 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2510 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GTE; }
#line 6935 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2511 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LTE; }
#line 6941 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2515 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 6949 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2519 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 6957 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2523 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 6965 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2527 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].string));
			}
#line 6973 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2531 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].string));
			}
#line 6981 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2535 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 6989 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2541 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 6997 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2545 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 7005 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2549 "parser_bison.y" /* yacc.c:1646  */
    {
				struct error_record *erec;
				unsigned int key;

				erec = meta_key_parse(&(yyloc), (yyvsp[0].string), &key);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.expr) = meta_expr_alloc(&(yyloc), key);
			}
#line 7022 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2566 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_LEN; }
#line 7028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2567 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 7034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2568 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 7040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2569 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRANDOM; }
#line 7046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2572 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_MARK; }
#line 7052 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2573 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIF; }
#line 7058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 455:
#line 2574 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 7064 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2575 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 7070 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2576 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIF; }
#line 7076 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2577 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 7082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2578 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 7088 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 460:
#line 2579 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKUID; }
#line 7094 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2580 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKGID; }
#line 7100 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2581 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 7106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 463:
#line 2582 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 7112 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2583 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 7118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2584 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 7124 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 466:
#line 2585 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 7130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2586 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CPU; }
#line 7136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2587 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 7142 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2588 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 7148 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2589 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 7154 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2593 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 7162 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 472:
#line 2597 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 7170 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2601 "parser_bison.y" /* yacc.c:1646  */
    {
				struct error_record *erec;
				unsigned int key;

				erec = meta_key_parse(&(yyloc), (yyvsp[-2].string), &key);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.stmt) = meta_stmt_alloc(&(yyloc), key, (yyvsp[0].expr));
			}
#line 7187 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2614 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = notrack_stmt_alloc(&(yyloc));
			}
#line 7195 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2619 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 7201 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2620 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 7207 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2623 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_INCREMENTAL; }
#line 7213 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2624 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_NG_RANDOM; }
#line 7219 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2628 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = numgen_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
			}
#line 7227 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2634 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val));
				(yyval.expr)->hash.expr = (yyvsp[-5].expr);
			}
#line 7236 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2639 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = hash_expr_alloc(&(yyloc), (yyvsp[-1].val), 0, (yyvsp[0].val));
				(yyval.expr)->hash.expr = (yyvsp[-3].expr);
			}
#line 7245 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2646 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = rt_expr_alloc(&(yyloc), (yyvsp[0].val), true);
			}
#line 7253 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2651 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_CLASSID; }
#line 7259 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2652 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_RT_NEXTHOP4; }
#line 7265 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2656 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1);
			}
#line 7273 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2660 "parser_bison.y" /* yacc.c:1646  */
    {
				struct error_record *erec;
				unsigned int key;

				erec = ct_key_parse(&(yyloc), (yyvsp[0].string), &key);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.expr) = ct_expr_alloc(&(yyloc), key, -1);
			}
#line 7290 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 487:
#line 2673 "parser_bison.y" /* yacc.c:1646  */
    {
				struct error_record *erec;
				int8_t direction;

				erec = ct_dir_parse(&(yyloc), (yyvsp[-1].string), &direction);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), direction);
			}
#line 7307 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 488:
#line 2687 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 7313 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 489:
#line 2688 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 7319 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2689 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_MARK; }
#line 7325 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 492:
#line 2692 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 7331 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2693 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 7337 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 494:
#line 2694 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 7343 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 495:
#line 2695 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 7349 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 496:
#line 2696 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 7355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2697 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 7361 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 499:
#line 2701 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 7367 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 500:
#line 2702 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 7373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2706 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 7381 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2710 "parser_bison.y" /* yacc.c:1646  */
    {
				struct error_record *erec;
				unsigned int key;

				erec = ct_key_parse(&(yyloc), (yyvsp[-2].string), &key);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}

				(yyval.stmt) = ct_stmt_alloc(&(yyloc), key, (yyvsp[0].expr));
			}
#line 7398 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 503:
#line 2725 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 7406 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 520:
#line 2749 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				(yyval.expr)->payload.base	= (yyvsp[-4].val);
				(yyval.expr)->payload.offset	= (yyvsp[-2].val);
				(yyval.expr)->len			= (yyvsp[0].val);
				(yyval.expr)->dtype		= &integer_type;
			}
#line 7418 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 521:
#line 2758 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 7424 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 522:
#line 2759 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 7430 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 523:
#line 2760 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 7436 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 524:
#line 2764 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 7444 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 525:
#line 2769 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 7450 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 526:
#line 2770 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 7456 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 527:
#line 2771 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 7462 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 528:
#line 2775 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 7470 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 529:
#line 2780 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_VID; }
#line 7476 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 530:
#line 2781 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_CFI; }
#line 7482 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 531:
#line 2782 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_PCP; }
#line 7488 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 532:
#line 2783 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 7494 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 533:
#line 2787 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 7502 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 534:
#line 2792 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HRD; }
#line 7508 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 535:
#line 2793 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PRO; }
#line 7514 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 536:
#line 2794 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HLN; }
#line 7520 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 537:
#line 2795 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PLN; }
#line 7526 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 538:
#line 2796 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_OP; }
#line 7532 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 539:
#line 2800 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 7540 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 540:
#line 2805 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_VERSION; }
#line 7546 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 541:
#line 2806 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 7552 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 542:
#line 2807 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DSCP; }
#line 7558 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 543:
#line 2808 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ECN; }
#line 7564 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 544:
#line 2809 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 7570 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 545:
#line 2810 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ID; }
#line 7576 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 546:
#line 2811 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 7582 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 547:
#line 2812 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_TTL; }
#line 7588 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 548:
#line 2813 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 7594 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 549:
#line 2814 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 7600 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 550:
#line 2815 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_SADDR; }
#line 7606 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 551:
#line 2816 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DADDR; }
#line 7612 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 552:
#line 2820 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 7620 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 553:
#line 2825 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 7626 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 554:
#line 2826 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 7632 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 555:
#line 2827 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 7638 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 556:
#line 2828 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_ID; }
#line 7644 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 557:
#line 2829 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 7650 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 558:
#line 2830 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 7656 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 559:
#line 2831 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 7662 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 560:
#line 2835 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 7670 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 561:
#line 2840 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 7676 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 562:
#line 2841 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 7682 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 563:
#line 2842 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_ECN; }
#line 7688 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 564:
#line 2843 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 7694 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 565:
#line 2844 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 7700 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 566:
#line 2845 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 7706 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 567:
#line 2846 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 7712 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 568:
#line 2847 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 7718 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 569:
#line 2848 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 7724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 570:
#line 2851 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 7732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 571:
#line 2856 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 7738 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 572:
#line 2857 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 7744 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 573:
#line 2858 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 7750 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 574:
#line 2859 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 7756 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 575:
#line 2860 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 7762 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 576:
#line 2861 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 7768 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 577:
#line 2862 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 7774 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 578:
#line 2863 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 7780 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 579:
#line 2867 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 7788 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 580:
#line 2872 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 7794 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 581:
#line 2873 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 7800 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 582:
#line 2874 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 7806 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 583:
#line 2875 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SPI; }
#line 7812 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 584:
#line 2876 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 7818 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 585:
#line 2880 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 7826 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 586:
#line 2885 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SPI; }
#line 7832 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 587:
#line 2886 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 7838 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 588:
#line 2890 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 7846 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 589:
#line 2895 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 7852 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 590:
#line 2896 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 7858 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 591:
#line 2897 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_CPI; }
#line 7864 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 592:
#line 2901 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 7872 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 593:
#line 2906 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 7878 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 594:
#line 2907 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 7884 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 595:
#line 2908 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 7890 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 596:
#line 2909 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 7896 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 597:
#line 2913 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 7904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 598:
#line 2918 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 7910 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 599:
#line 2919 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 7916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 600:
#line 2920 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 7922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 601:
#line 2921 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 7928 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 602:
#line 2925 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 7936 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 603:
#line 2930 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 7942 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 604:
#line 2931 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 7948 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 605:
#line 2932 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 7954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 606:
#line 2933 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 7960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 607:
#line 2934 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 7966 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 608:
#line 2935 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 7972 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 609:
#line 2936 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 7978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 610:
#line 2937 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 7984 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 611:
#line 2938 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 7990 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 612:
#line 2939 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 7996 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 613:
#line 2943 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 8004 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 614:
#line 2948 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 8010 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 615:
#line 2949 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 8016 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 616:
#line 2950 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 8022 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 617:
#line 2954 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 8030 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 618:
#line 2959 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 8036 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 619:
#line 2960 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 8042 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 620:
#line 2961 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 8048 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 621:
#line 2962 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 8054 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 629:
#line 2975 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 8062 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 630:
#line 2980 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 8068 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 631:
#line 2981 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 8074 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 632:
#line 2985 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 8082 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 633:
#line 2990 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 8088 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 634:
#line 2991 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 8094 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 635:
#line 2992 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_TYPE; }
#line 8100 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 636:
#line 2993 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 8106 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 637:
#line 2997 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 8114 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 638:
#line 3003 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 8122 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3009 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 8130 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 640:
#line 3014 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 8136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 641:
#line 3018 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 8144 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 642:
#line 3023 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 8150 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3024 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 8156 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 644:
#line 3025 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 8162 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 645:
#line 3026 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 8168 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 646:
#line 3027 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 8174 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 647:
#line 3028 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_ID; }
#line 8180 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 648:
#line 3032 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 8188 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 649:
#line 3037 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 8194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 650:
#line 3038 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 8200 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 651:
#line 3042 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 8208 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 652:
#line 3047 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 8214 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 653:
#line 3048 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 8220 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 654:
#line 3049 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_TYPE; }
#line 8226 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 655:
#line 3050 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 8232 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 656:
#line 3051 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 8238 "parser_bison.c" /* yacc.c:1646  */
    break;


#line 8242 "parser_bison.c" /* yacc.c:1646  */
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
      yyerror (&yylloc, scanner, state, YY_("syntax error"));
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
        yyerror (&yylloc, scanner, state, yymsgp);
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
                      yytoken, &yylval, &yylloc, scanner, state);
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
                  yystos[yystate], yyvsp, yylsp, scanner, state);
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
  yyerror (&yylloc, scanner, state, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, scanner, state);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, scanner, state);
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
#line 3054 "parser_bison.y" /* yacc.c:1906  */

