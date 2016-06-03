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


#line 162 "parser_bison.c" /* yacc.c:339  */

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
    HOOK = 282,
    DEVICE = 283,
    TABLE = 284,
    TABLES = 285,
    CHAIN = 286,
    CHAINS = 287,
    RULE = 288,
    RULES = 289,
    SETS = 290,
    SET = 291,
    ELEMENT = 292,
    MAP = 293,
    MAPS = 294,
    HANDLE = 295,
    RULESET = 296,
    INET = 297,
    NETDEV = 298,
    ADD = 299,
    UPDATE = 300,
    REPLACE = 301,
    CREATE = 302,
    INSERT = 303,
    DELETE = 304,
    LIST = 305,
    FLUSH = 306,
    RENAME = 307,
    DESCRIBE = 308,
    EXPORT = 309,
    MONITOR = 310,
    ACCEPT = 311,
    DROP = 312,
    CONTINUE = 313,
    JUMP = 314,
    GOTO = 315,
    RETURN = 316,
    TO = 317,
    CONSTANT = 318,
    INTERVAL = 319,
    TIMEOUT = 320,
    GC_INTERVAL = 321,
    ELEMENTS = 322,
    POLICY = 323,
    MEMORY = 324,
    PERFORMANCE = 325,
    SIZE = 326,
    FLOW = 327,
    NUM = 328,
    STRING = 329,
    QUOTED_STRING = 330,
    ASTERISK_STRING = 331,
    LL_HDR = 332,
    NETWORK_HDR = 333,
    TRANSPORT_HDR = 334,
    BRIDGE = 335,
    ETHER = 336,
    SADDR = 337,
    DADDR = 338,
    TYPE = 339,
    VLAN = 340,
    ID = 341,
    CFI = 342,
    PCP = 343,
    ARP = 344,
    HTYPE = 345,
    PTYPE = 346,
    HLEN = 347,
    PLEN = 348,
    OPERATION = 349,
    IP = 350,
    HDRVERSION = 351,
    HDRLENGTH = 352,
    DSCP = 353,
    ECN = 354,
    LENGTH = 355,
    FRAG_OFF = 356,
    TTL = 357,
    PROTOCOL = 358,
    CHECKSUM = 359,
    ICMP = 360,
    CODE = 361,
    SEQUENCE = 362,
    GATEWAY = 363,
    MTU = 364,
    IP6 = 365,
    PRIORITY = 366,
    FLOWLABEL = 367,
    NEXTHDR = 368,
    HOPLIMIT = 369,
    ICMP6 = 370,
    PPTR = 371,
    MAXDELAY = 372,
    AH = 373,
    RESERVED = 374,
    SPI = 375,
    ESP = 376,
    COMP = 377,
    FLAGS = 378,
    CPI = 379,
    UDP = 380,
    SPORT = 381,
    DPORT = 382,
    UDPLITE = 383,
    CSUMCOV = 384,
    TCP = 385,
    ACKSEQ = 386,
    DOFF = 387,
    WINDOW = 388,
    URGPTR = 389,
    DCCP = 390,
    SCTP = 391,
    VTAG = 392,
    RT = 393,
    RT0 = 394,
    RT2 = 395,
    SEG_LEFT = 396,
    ADDR = 397,
    HBH = 398,
    FRAG = 399,
    RESERVED2 = 400,
    MORE_FRAGMENTS = 401,
    DST = 402,
    MH = 403,
    META = 404,
    NFPROTO = 405,
    L4PROTO = 406,
    MARK = 407,
    IIF = 408,
    IIFNAME = 409,
    IIFTYPE = 410,
    OIF = 411,
    OIFNAME = 412,
    OIFTYPE = 413,
    SKUID = 414,
    SKGID = 415,
    NFTRACE = 416,
    RTCLASSID = 417,
    IBRIPORT = 418,
    OBRIPORT = 419,
    PKTTYPE = 420,
    CPU = 421,
    IIFGROUP = 422,
    OIFGROUP = 423,
    CGROUP = 424,
    CT = 425,
    DIRECTION = 426,
    STATE = 427,
    STATUS = 428,
    EXPIRATION = 429,
    HELPER = 430,
    L3PROTOCOL = 431,
    PROTO_SRC = 432,
    PROTO_DST = 433,
    LABEL = 434,
    COUNTER = 435,
    PACKETS = 436,
    BYTES = 437,
    LOG = 438,
    PREFIX = 439,
    GROUP = 440,
    SNAPLEN = 441,
    QUEUE_THRESHOLD = 442,
    LEVEL = 443,
    LEVEL_EMERG = 444,
    LEVEL_ALERT = 445,
    LEVEL_CRIT = 446,
    LEVEL_ERR = 447,
    LEVEL_WARN = 448,
    LEVEL_NOTICE = 449,
    LEVEL_INFO = 450,
    LEVEL_DEBUG = 451,
    LIMIT = 452,
    RATE = 453,
    BURST = 454,
    OVER = 455,
    UNTIL = 456,
    NANOSECOND = 457,
    MICROSECOND = 458,
    MILLISECOND = 459,
    SECOND = 460,
    MINUTE = 461,
    HOUR = 462,
    DAY = 463,
    WEEK = 464,
    _REJECT = 465,
    WITH = 466,
    ICMPX = 467,
    SNAT = 468,
    DNAT = 469,
    MASQUERADE = 470,
    REDIRECT = 471,
    RANDOM = 472,
    FULLY_RANDOM = 473,
    PERSISTENT = 474,
    QUEUE = 475,
    QUEUENUM = 476,
    BYPASS = 477,
    FANOUT = 478,
    DUP = 479,
    FWD = 480,
    POSITION = 481,
    COMMENT = 482,
    XML = 483,
    JSON = 484
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
#define HOOK 282
#define DEVICE 283
#define TABLE 284
#define TABLES 285
#define CHAIN 286
#define CHAINS 287
#define RULE 288
#define RULES 289
#define SETS 290
#define SET 291
#define ELEMENT 292
#define MAP 293
#define MAPS 294
#define HANDLE 295
#define RULESET 296
#define INET 297
#define NETDEV 298
#define ADD 299
#define UPDATE 300
#define REPLACE 301
#define CREATE 302
#define INSERT 303
#define DELETE 304
#define LIST 305
#define FLUSH 306
#define RENAME 307
#define DESCRIBE 308
#define EXPORT 309
#define MONITOR 310
#define ACCEPT 311
#define DROP 312
#define CONTINUE 313
#define JUMP 314
#define GOTO 315
#define RETURN 316
#define TO 317
#define CONSTANT 318
#define INTERVAL 319
#define TIMEOUT 320
#define GC_INTERVAL 321
#define ELEMENTS 322
#define POLICY 323
#define MEMORY 324
#define PERFORMANCE 325
#define SIZE 326
#define FLOW 327
#define NUM 328
#define STRING 329
#define QUOTED_STRING 330
#define ASTERISK_STRING 331
#define LL_HDR 332
#define NETWORK_HDR 333
#define TRANSPORT_HDR 334
#define BRIDGE 335
#define ETHER 336
#define SADDR 337
#define DADDR 338
#define TYPE 339
#define VLAN 340
#define ID 341
#define CFI 342
#define PCP 343
#define ARP 344
#define HTYPE 345
#define PTYPE 346
#define HLEN 347
#define PLEN 348
#define OPERATION 349
#define IP 350
#define HDRVERSION 351
#define HDRLENGTH 352
#define DSCP 353
#define ECN 354
#define LENGTH 355
#define FRAG_OFF 356
#define TTL 357
#define PROTOCOL 358
#define CHECKSUM 359
#define ICMP 360
#define CODE 361
#define SEQUENCE 362
#define GATEWAY 363
#define MTU 364
#define IP6 365
#define PRIORITY 366
#define FLOWLABEL 367
#define NEXTHDR 368
#define HOPLIMIT 369
#define ICMP6 370
#define PPTR 371
#define MAXDELAY 372
#define AH 373
#define RESERVED 374
#define SPI 375
#define ESP 376
#define COMP 377
#define FLAGS 378
#define CPI 379
#define UDP 380
#define SPORT 381
#define DPORT 382
#define UDPLITE 383
#define CSUMCOV 384
#define TCP 385
#define ACKSEQ 386
#define DOFF 387
#define WINDOW 388
#define URGPTR 389
#define DCCP 390
#define SCTP 391
#define VTAG 392
#define RT 393
#define RT0 394
#define RT2 395
#define SEG_LEFT 396
#define ADDR 397
#define HBH 398
#define FRAG 399
#define RESERVED2 400
#define MORE_FRAGMENTS 401
#define DST 402
#define MH 403
#define META 404
#define NFPROTO 405
#define L4PROTO 406
#define MARK 407
#define IIF 408
#define IIFNAME 409
#define IIFTYPE 410
#define OIF 411
#define OIFNAME 412
#define OIFTYPE 413
#define SKUID 414
#define SKGID 415
#define NFTRACE 416
#define RTCLASSID 417
#define IBRIPORT 418
#define OBRIPORT 419
#define PKTTYPE 420
#define CPU 421
#define IIFGROUP 422
#define OIFGROUP 423
#define CGROUP 424
#define CT 425
#define DIRECTION 426
#define STATE 427
#define STATUS 428
#define EXPIRATION 429
#define HELPER 430
#define L3PROTOCOL 431
#define PROTO_SRC 432
#define PROTO_DST 433
#define LABEL 434
#define COUNTER 435
#define PACKETS 436
#define BYTES 437
#define LOG 438
#define PREFIX 439
#define GROUP 440
#define SNAPLEN 441
#define QUEUE_THRESHOLD 442
#define LEVEL 443
#define LEVEL_EMERG 444
#define LEVEL_ALERT 445
#define LEVEL_CRIT 446
#define LEVEL_ERR 447
#define LEVEL_WARN 448
#define LEVEL_NOTICE 449
#define LEVEL_INFO 450
#define LEVEL_DEBUG 451
#define LIMIT 452
#define RATE 453
#define BURST 454
#define OVER 455
#define UNTIL 456
#define NANOSECOND 457
#define MICROSECOND 458
#define MILLISECOND 459
#define SECOND 460
#define MINUTE 461
#define HOUR 462
#define DAY 463
#define WEEK 464
#define _REJECT 465
#define WITH 466
#define ICMPX 467
#define SNAT 468
#define DNAT 469
#define MASQUERADE 470
#define REDIRECT 471
#define RANDOM 472
#define FULLY_RANDOM 473
#define PERSISTENT 474
#define QUEUE 475
#define QUEUENUM 476
#define BYPASS 477
#define FANOUT 478
#define DUP 479
#define FWD 480
#define POSITION 481
#define COMMENT 482
#define XML 483
#define JSON 484

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 122 "parser_bison.y" /* yacc.c:355  */

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

#line 680 "parser_bison.c" /* yacc.c:355  */
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

#line 708 "parser_bison.c" /* yacc.c:358  */

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
#define YYLAST   2453

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  239
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  210
/* YYNRULES -- Number of rules.  */
#define YYNRULES  605
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  892

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   484

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   233,     2,     2,     2,
     234,   235,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   230,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   237,     2,   238,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   231,   236,   232,     2,     2,     2,     2,
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
     225,   226,   227,   228,   229
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   597,   597,   598,   615,   616,   619,   620,   623,   631,
     644,   652,   653,   654,   655,   684,   685,   686,   687,   688,
     689,   690,   691,   692,   693,   694,   695,   698,   702,   709,
     713,   721,   725,   729,   736,   743,   749,   755,   759,   766,
     770,   780,   786,   790,   794,   798,   802,   806,   812,   816,
     820,   824,   828,   832,   836,   840,   844,   848,   852,   858,
     862,   866,   870,   876,   883,   891,   900,   901,   904,   905,
     906,   907,   908,   909,   912,   913,   916,   917,   920,   929,
     935,   947,   948,   949,   950,   951,   962,   972,   985,   991,
     992,   993,   994,   995,   996,  1004,  1009,  1010,  1011,  1012,
    1017,  1022,  1027,  1032,  1037,  1040,  1044,  1047,  1048,  1049,
    1053,  1059,  1060,  1061,  1062,  1070,  1075,  1080,  1083,  1087,
    1093,  1094,  1097,  1106,  1116,  1128,  1129,  1130,  1131,  1134,
    1160,  1161,  1164,  1165,  1168,  1179,  1180,  1183,  1186,  1187,
    1188,  1191,  1205,  1206,  1209,  1210,  1211,  1212,  1213,  1214,
    1217,  1225,  1232,  1239,  1246,  1254,  1257,  1266,  1269,  1277,
    1285,  1297,  1301,  1308,  1312,  1318,  1330,  1336,  1343,  1344,
    1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1353,  1354,
    1355,  1356,  1357,  1358,  1359,  1362,  1366,  1372,  1378,  1383,
    1392,  1397,  1402,  1405,  1411,  1412,  1414,  1420,  1424,  1427,
    1431,  1437,  1438,  1441,  1447,  1451,  1454,  1459,  1464,  1469,
    1474,  1481,  1482,  1483,  1484,  1485,  1486,  1487,  1488,  1491,
    1500,  1520,  1521,  1522,  1525,  1526,  1527,  1528,  1542,  1543,
    1544,  1545,  1546,  1549,  1552,  1559,  1563,  1573,  1583,  1592,
    1604,  1607,  1612,  1619,  1620,  1639,  1645,  1646,  1647,  1650,
    1654,  1659,  1663,  1669,  1670,  1673,  1676,  1680,  1685,  1691,
    1692,  1695,  1698,  1702,  1706,  1713,  1718,  1726,  1733,  1734,
    1740,  1741,  1742,  1745,  1746,  1749,  1755,  1759,  1762,  1767,
    1773,  1774,  1780,  1781,  1784,  1793,  1794,  1797,  1804,  1813,
    1819,  1823,  1826,  1832,  1838,  1845,  1859,  1868,  1879,  1880,
    1881,  1882,  1883,  1884,  1885,  1888,  1889,  1893,  1899,  1900,
    1906,  1907,  1913,  1914,  1920,  1923,  1924,  1943,  1949,  1955,
    1966,  1967,  1968,  1971,  1977,  1978,  1979,  1982,  1989,  1994,
    1999,  2002,  2006,  2010,  2016,  2017,  2024,  2030,  2031,  2034,
    2040,  2044,  2047,  2051,  2057,  2058,  2061,  2062,  2065,  2066,
    2069,  2073,  2077,  2083,  2089,  2097,  2098,  2099,  2102,  2103,
    2107,  2113,  2114,  2120,  2121,  2127,  2128,  2134,  2137,  2138,
    2157,  2158,  2159,  2165,  2171,  2177,  2183,  2189,  2196,  2203,
    2210,  2217,  2224,  2231,  2238,  2245,  2252,  2259,  2266,  2272,
    2278,  2286,  2287,  2288,  2289,  2290,  2291,  2294,  2298,  2302,
    2306,  2310,  2314,  2320,  2324,  2330,  2331,  2334,  2335,  2336,
    2337,  2338,  2341,  2342,  2343,  2344,  2345,  2346,  2347,  2348,
    2349,  2350,  2351,  2352,  2353,  2354,  2355,  2356,  2357,  2358,
    2361,  2365,  2371,  2375,  2390,  2391,  2392,  2393,  2394,  2395,
    2396,  2397,  2399,  2400,  2401,  2402,  2403,  2404,  2405,  2408,
    2409,  2412,  2418,  2424,  2425,  2426,  2427,  2428,  2429,  2430,
    2431,  2432,  2433,  2434,  2435,  2436,  2437,  2438,  2439,  2442,
    2452,  2453,  2454,  2457,  2463,  2464,  2465,  2468,  2474,  2475,
    2476,  2477,  2480,  2486,  2487,  2488,  2489,  2490,  2493,  2499,
    2500,  2501,  2502,  2503,  2504,  2505,  2506,  2507,  2508,  2509,
    2510,  2513,  2519,  2520,  2521,  2522,  2523,  2524,  2525,  2528,
    2534,  2535,  2536,  2537,  2538,  2539,  2540,  2541,  2542,  2544,
    2550,  2551,  2552,  2553,  2554,  2555,  2556,  2557,  2560,  2566,
    2567,  2568,  2569,  2570,  2573,  2579,  2580,  2583,  2589,  2590,
    2591,  2594,  2600,  2601,  2602,  2603,  2606,  2612,  2613,  2614,
    2615,  2618,  2624,  2625,  2626,  2627,  2628,  2629,  2630,  2631,
    2632,  2633,  2636,  2642,  2643,  2644,  2647,  2653,  2654,  2655,
    2656,  2659,  2660,  2661,  2662,  2663,  2664,  2665,  2668,  2674,
    2675,  2678,  2684,  2685,  2686,  2687,  2690,  2696,  2702,  2708,
    2711,  2717,  2718,  2719,  2720,  2721,  2722,  2725,  2731,  2732,
    2735,  2741,  2742,  2743,  2744,  2745
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
  "\"include\"", "\"define\"", "\"hook\"", "\"device\"", "\"table\"",
  "\"tables\"", "\"chain\"", "\"chains\"", "\"rule\"", "\"rules\"",
  "\"sets\"", "\"set\"", "\"element\"", "\"map\"", "\"maps\"",
  "\"handle\"", "\"ruleset\"", "\"inet\"", "\"netdev\"", "\"add\"",
  "\"update\"", "\"replace\"", "\"create\"", "\"insert\"", "\"delete\"",
  "\"list\"", "\"flush\"", "\"rename\"", "\"describe\"", "\"export\"",
  "\"monitor\"", "\"accept\"", "\"drop\"", "\"continue\"", "\"jump\"",
  "\"goto\"", "\"return\"", "\"to\"", "\"constant\"", "\"interval\"",
  "\"timeout\"", "\"gc-interval\"", "\"elements\"", "\"policy\"",
  "\"memory\"", "\"performance\"", "\"size\"", "\"flow\"", "\"number\"",
  "\"string\"", "QUOTED_STRING", "ASTERISK_STRING", "\"ll\"", "\"nh\"",
  "\"th\"", "\"bridge\"", "\"ether\"", "\"saddr\"", "\"daddr\"",
  "\"type\"", "\"vlan\"", "\"id\"", "\"cfi\"", "\"pcp\"", "\"arp\"",
  "\"htype\"", "\"ptype\"", "\"hlen\"", "\"plen\"", "\"operation\"",
  "\"ip\"", "\"version\"", "\"hdrlength\"", "\"dscp\"", "\"ecn\"",
  "\"length\"", "\"frag-off\"", "\"ttl\"", "\"protocol\"", "\"checksum\"",
  "\"icmp\"", "\"code\"", "\"seq\"", "\"gateway\"", "\"mtu\"", "\"ip6\"",
  "\"priority\"", "\"flowlabel\"", "\"nexthdr\"", "\"hoplimit\"",
  "\"icmpv6\"", "\"param-problem\"", "\"max-delay\"", "\"ah\"",
  "\"reserved\"", "\"spi\"", "\"esp\"", "\"comp\"", "\"flags\"", "\"cpi\"",
  "\"udp\"", "\"sport\"", "\"dport\"", "\"udplite\"", "\"csumcov\"",
  "\"tcp\"", "\"ackseq\"", "\"doff\"", "\"window\"", "\"urgptr\"",
  "\"dccp\"", "\"sctp\"", "\"vtag\"", "\"rt\"", "\"rt0\"", "\"rt2\"",
  "\"seg-left\"", "\"addr\"", "\"hbh\"", "\"frag\"", "\"reserved2\"",
  "\"more-fragments\"", "\"dst\"", "\"mh\"", "\"meta\"", "\"nfproto\"",
  "\"l4proto\"", "\"mark\"", "\"iif\"", "\"iifname\"", "\"iiftype\"",
  "\"oif\"", "\"oifname\"", "\"oiftype\"", "\"skuid\"", "\"skgid\"",
  "\"nftrace\"", "\"rtclassid\"", "\"ibriport\"", "\"obriport\"",
  "\"pkttype\"", "\"cpu\"", "\"iifgroup\"", "\"oifgroup\"", "\"cgroup\"",
  "\"ct\"", "\"direction\"", "\"state\"", "\"status\"", "\"expiration\"",
  "\"helper\"", "\"l3proto\"", "\"proto-src\"", "\"proto-dst\"",
  "\"label\"", "\"counter\"", "\"packets\"", "\"bytes\"", "\"log\"",
  "\"prefix\"", "\"group\"", "\"snaplen\"", "\"queue-threshold\"",
  "\"level\"", "\"emerg\"", "\"alert\"", "\"crit\"", "\"err\"", "\"warn\"",
  "\"notice\"", "\"info\"", "\"debug\"", "\"limit\"", "\"rate\"",
  "\"burst\"", "\"over\"", "\"until\"", "\"nanosecond\"",
  "\"microsecond\"", "\"millisecond\"", "\"second\"", "\"minute\"",
  "\"hour\"", "\"day\"", "\"week\"", "\"reject\"", "\"with\"", "\"icmpx\"",
  "\"snat\"", "\"dnat\"", "\"masquerade\"", "\"redirect\"", "\"random\"",
  "\"fully-random\"", "\"persistent\"", "\"queue\"", "\"num\"",
  "\"bypass\"", "\"fanout\"", "\"dup\"", "\"fwd\"", "\"position\"",
  "\"comment\"", "\"xml\"", "\"json\"", "'='", "'{'", "'}'", "'$'", "'('",
  "')'", "'|'", "'['", "']'", "$accept", "input", "stmt_seperator",
  "opt_newline", "common_block", "line", "base_cmd", "add_cmd",
  "replace_cmd", "create_cmd", "insert_cmd", "delete_cmd", "list_cmd",
  "flush_cmd", "rename_cmd", "export_cmd", "monitor_cmd", "monitor_event",
  "monitor_object", "monitor_format", "export_format", "describe_cmd",
  "table_block_alloc", "table_options", "table_block", "chain_block_alloc",
  "chain_block", "set_block_alloc", "set_block", "set_flag_list",
  "set_flag", "map_block_alloc", "map_block", "set_mechanism",
  "set_policy_spec", "data_type", "type_identifier_list",
  "type_identifier", "hook_spec", "prio_spec", "dev_spec", "policy_spec",
  "chain_policy", "identifier", "string", "time_spec", "family_spec",
  "family_spec_explicit", "table_spec", "chain_spec", "chain_identifier",
  "set_spec", "set_identifier", "handle_spec", "position_spec",
  "ruleid_spec", "comment_spec", "ruleset_spec", "rule", "rule_alloc",
  "stmt_list", "stmt", "verdict_stmt", "verdict_map_stmt",
  "verdict_map_expr", "verdict_map_list_expr",
  "verdict_map_list_member_expr", "counter_stmt", "counter_stmt_alloc",
  "counter_args", "counter_arg", "log_stmt", "log_stmt_alloc", "log_args",
  "log_arg", "level_type", "limit_stmt", "limit_mode", "limit_burst",
  "time_unit", "reject_stmt", "reject_stmt_alloc", "reject_opts",
  "nat_stmt", "nat_stmt_alloc", "concat_stmt_expr", "map_stmt_expr",
  "stmt_expr", "nat_stmt_args", "masq_stmt", "masq_stmt_alloc",
  "masq_stmt_args", "redir_stmt", "redir_stmt_alloc", "redir_stmt_arg",
  "dup_stmt", "fwd_stmt", "nf_nat_flags", "nf_nat_flag", "queue_stmt",
  "queue_stmt_alloc", "queue_stmt_args", "queue_stmt_arg",
  "queue_stmt_flags", "queue_stmt_flag", "set_stmt", "set_stmt_op",
  "flow_stmt", "flow_stmt_alloc", "flow_stmt_opts", "flow_stmt_opt",
  "match_stmt", "symbol_expr", "integer_expr", "primary_expr",
  "shift_expr", "and_expr", "exclusive_or_expr", "inclusive_or_expr",
  "basic_expr", "concat_expr", "prefix_rhs_expr", "range_rhs_expr",
  "wildcard_rhs_expr", "multiton_rhs_expr", "map_expr", "expr", "set_expr",
  "set_list_expr", "set_list_member_expr", "flow_key_expr",
  "flow_key_expr_alloc", "set_elem_expr", "set_elem_expr_alloc",
  "set_elem_options", "set_elem_option", "set_lhs_expr", "set_rhs_expr",
  "initializer_expr", "relational_expr", "list_rhs_expr", "rhs_expr",
  "shift_rhs_expr", "and_rhs_expr", "exclusive_or_rhs_expr",
  "inclusive_or_rhs_expr", "basic_rhs_expr", "concat_rhs_expr",
  "primary_rhs_expr", "relational_op", "verdict_expr", "meta_expr",
  "meta_key", "meta_key_qualified", "meta_key_unqualified", "meta_stmt",
  "ct_expr", "ct_key", "ct_key_dir", "ct_key_counters", "ct_stmt",
  "payload_stmt", "payload_expr", "payload_raw_expr", "payload_base_spec",
  "eth_hdr_expr", "eth_hdr_field", "vlan_hdr_expr", "vlan_hdr_field",
  "arp_hdr_expr", "arp_hdr_field", "ip_hdr_expr", "ip_hdr_field",
  "icmp_hdr_expr", "icmp_hdr_field", "ip6_hdr_expr", "ip6_hdr_field",
  "icmp6_hdr_expr", "icmp6_hdr_field", "auth_hdr_expr", "auth_hdr_field",
  "esp_hdr_expr", "esp_hdr_field", "comp_hdr_expr", "comp_hdr_field",
  "udp_hdr_expr", "udp_hdr_field", "udplite_hdr_expr", "udplite_hdr_field",
  "tcp_hdr_expr", "tcp_hdr_field", "dccp_hdr_expr", "dccp_hdr_field",
  "sctp_hdr_expr", "sctp_hdr_field", "exthdr_expr", "hbh_hdr_expr",
  "hbh_hdr_field", "rt_hdr_expr", "rt_hdr_field", "rt0_hdr_expr",
  "rt0_hdr_field", "rt2_hdr_expr", "rt2_hdr_field", "frag_hdr_expr",
  "frag_hdr_field", "dst_hdr_expr", "dst_hdr_field", "mh_hdr_expr",
  "mh_hdr_field", YY_NULLPTR
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
      61,   123,   125,    36,    40,    41,   124,    91,    93
};
# endif

#define YYPACT_NINF -694

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-694)))

#define YYTABLE_NINF -359

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -694,  2333,  -694,   125,  -694,  -694,   -11,     9,   226,   226,
     226,   226,   226,   226,  -694,  -694,   622,    36,   184,    93,
     601,   514,   210,   103,  2070,  -138,    78,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   399,  -694,     9,  -694,     9,   130,
    1816,  -694,   125,  -694,   -87,   -58,   -48,  1816,     9,  -694,
     -44,  -694,  -694,   226,  -694,   226,   226,  -694,   226,  -694,
     226,   226,   226,   226,   226,   226,  -694,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   227,  -694,   226,   226,
     226,   226,  -694,   226,  -694,   347,  -694,  -694,  -694,  -694,
     228,   394,   403,   920,   562,   644,   508,   441,    28,   135,
     308,   224,   716,   -55,   -41,   234,    51,    55,    65,   417,
      69,   332,   628,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,   219,     9,  2070,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,   353,  -694,  -694,  -694,  -694,   151,    16,
     250,  -694,  -694,  -694,     9,     9,  -694,  -694,   628,   219,
    -694,  -694,    30,  -694,  -694,  -694,  -694,  -694,  -694,   176,
     208,   273,  -694,    71,  1816,  -694,  -694,  -694,  -694,   246,
    -694,   519,  -694,  -694,   106,  -694,  1356,  -694,    84,  -694,
     115,  -694,  -694,  -694,   216,  -694,  -694,    -4,  -694,  -694,
     426,   309,   311,   105,  -694,    35,  -694,  1518,  -694,  -694,
    -694,   307,  -694,  -694,  -694,   310,  -694,   483,   104,   136,
    -694,  -694,   145,  -694,   150,  1816,   -58,   -48,  1816,  -694,
    -694,  -694,  -694,   -44,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,   226,   226,  -694,  -694,  -694,
    -694,     9,  -694,  -694,  -694,  -694,   356,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
     152,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,   241,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   169,  -694,  -694,  -694,  -694,  -694,
    -138,  -694,   337,  -694,  -694,  -694,  1706,  -694,  -694,   432,
     438,   232,  1556,  1970,  -694,   483,    12,  -694,   321,  -694,
    -694,   357,   416,   246,  -694,   321,   428,   435,   439,   529,
     519,  -694,   102,  -694,  1556,  -694,   228,   394,   403,   920,
    -694,   562,   644,   508,   441,    28,   135,   308,   224,   716,
     -55,   -41,  -694,  -694,  -694,    68,  -694,   494,   248,    99,
     109,  -694,  -694,  -694,  -694,  -694,   469,   503,   507,   295,
     318,   269,   534,  -694,  -694,  -694,  -694,   540,  -694,  1556,
    -694,   540,  1556,  -694,  -694,   216,  -694,   544,  -694,     9,
    2070,     2,  -694,  2070,  2070,  2070,  2070,  2070,  2070,    -8,
     483,  -694,  -694,  -694,  -694,  -694,  -694,     9,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,   558,  -694,   174,
     563,  -694,   483,  1970,  1970,   125,   558,  -694,  -694,  -694,
    -694,  -694,  -694,   342,   344,  -694,  -694,  -694,  -694,  -694,
     506,   510,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,    45,    -7,  -694,   318,   563,
    1970,  1970,  -694,  -694,   518,   553,   133,  -694,   273,   523,
     273,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
     511,   512,   525,   516,  -694,  2070,   483,  1556,   540,  2220,
    2220,  2220,  2220,  2220,   530,  2220,  1556,   248,   248,  -694,
    -694,   354,  -694,   579,  1816,    -7,  2070,  -694,  -694,  -694,
     426,   309,   311,  -694,     9,   273,  -694,  -694,  2220,  2220,
    2220,  -694,  -694,  -694,  -694,   138,   828,    88,    56,  -694,
    -694,   595,   368,  -694,   533,  -694,    -7,  -694,  -694,  -694,
       3,  1556,  -694,  2192,  -694,   483,  -694,   535,   536,  -694,
     542,  -694,  -694,  -694,  -694,  -694,   469,   503,   507,  -694,
    -694,   248,  -694,   540,  -694,   388,    -7,  1816,  -694,  1706,
      13,  -694,  -694,  -694,  -694,     9,     9,     9,   547,  -694,
    -694,  -694,   125,   513,   548,  -694,  -694,  -694,   125,   125,
     125,   533,   533,   393,   515,   567,   206,   470,  -694,  -694,
    -694,   125,   396,   206,   470,  -694,  -694,  -694,   125,   348,
    1009,   569,  -694,  -694,  -694,  -694,   545,   437,  -694,   273,
    -694,   563,  -694,  -694,  -694,  -694,   540,  -694,   411,   626,
     273,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,   618,  -694,  -694,  -694,   125,   125,   -44,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,   125,   639,  -694,
    -694,  -694,  -694,   258,  -694,  -694,   -44,   649,   258,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,   437,   584,
    -694,  -694,  -694,   619,  1706,  -694,   430,   431,   436,   589,
    -694,  -694,  -694,  -694,   206,   470,  -694,  -694,   206,  -694,
    -694,   -21,   273,  -694,  -694,  -694,   645,  -694,  -694,   125,
    -694,  -694,  -694,  -694,  1190,   124,   132,   598,   571,  -694,
     125,   125,   125,  -694,    39,  -694,  -694,  -694,   610,  -694,
    -694,  -694
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,   142,   142,
     142,   142,   142,   142,   146,   149,   142,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,   148,   147,   144,
     145,    12,    11,     3,     0,    15,     0,   143,     0,   155,
       0,    10,     0,   137,     0,    27,    29,     0,     0,    95,
       0,   110,    16,   142,    17,   142,   142,    18,   142,    19,
     142,   142,   142,   142,   142,   142,    20,   142,   161,   142,
     161,   161,   142,   142,   161,   161,     0,    21,   142,   142,
     142,   161,    22,   142,    23,     0,   297,   138,   139,   140,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,     0,     0,     0,    26,   294,   298,   299,    78,   302,
     404,   303,   300,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   301,
     571,   572,   573,   574,   575,   576,   577,    76,    77,    24,
      64,    67,    25,    68,    14,    13,   150,   151,     0,   157,
       0,   397,   398,   399,     0,     0,   402,   289,     0,     0,
     196,   203,     0,   234,   241,   242,   255,   261,   275,     0,
       0,     7,    32,   163,   165,   166,   168,   186,   171,   194,
     174,   201,   175,   176,   235,   177,     0,   180,   254,   181,
     260,   182,   183,   178,   273,   184,   170,     0,   169,   305,
     308,   310,   312,   314,   315,   324,   326,     0,   325,   293,
     185,   404,   173,   179,   172,   300,     8,     0,     0,     0,
      31,   153,     0,    35,     0,     0,    37,    39,     0,    42,
      43,    44,    45,     0,    46,    48,   162,    49,    50,    51,
      52,    53,    58,    57,    54,   142,   161,    59,    60,    61,
      62,     0,   470,   471,   472,   296,     0,   474,   475,   476,
     473,   481,   478,   479,   480,   477,   483,   484,   485,   486,
     487,   482,   499,   500,   494,   489,   490,   491,   492,   493,
     495,   496,   497,   498,   488,   502,   505,   504,   503,   506,
     507,   508,   501,   517,   518,   510,   511,   512,   514,   513,
     515,   516,   509,   520,   525,   522,   521,   526,   524,   523,
     527,   519,   530,   533,   529,   531,   532,   528,   536,   535,
     534,   538,   539,   540,   537,   544,   545,   542,   543,   541,
     550,   547,   548,   549,   546,   560,   554,   557,   558,   552,
     553,   555,   556,   559,   561,   551,   565,   563,   564,   562,
     570,   567,   568,   569,   566,   584,   583,   582,   585,   581,
       0,   586,   589,   588,   580,   579,   578,   596,   593,   591,
     592,   594,   595,   590,   599,   598,   597,   603,   602,   605,
     601,   604,   600,   407,   410,   411,   408,   409,   403,   405,
     406,     0,   437,   435,   434,   436,   438,   439,   440,   450,
     449,   432,   441,   295,     0,    69,    70,    72,    71,    73,
      74,   156,     0,   159,   285,   286,     0,   400,   401,   403,
     432,   223,     0,     0,     6,     0,     0,   328,     0,   164,
     167,     0,     0,   195,   197,     0,     0,     0,     0,     0,
     202,   204,     0,   233,     0,   319,   372,   375,   376,   373,
     390,   382,   374,   383,   381,   380,   384,   378,   379,   377,
     385,   386,   388,   389,   387,     0,   246,   249,   240,   370,
     371,   243,   320,   321,   322,   247,   361,   363,   365,   367,
       0,   248,     0,   270,   271,   272,   253,   258,   268,     0,
     259,   263,     0,   282,   283,   274,   276,   279,   280,     0,
       0,     0,   290,     0,     0,     0,     0,     0,     0,     0,
       0,   391,   392,   393,   394,   395,   396,     0,   372,   375,
     376,   373,   382,   374,   383,   381,   380,   384,   378,   379,
     377,   385,   386,   370,   371,   356,   357,   351,   350,   368,
     355,   358,     0,     0,     0,     0,   349,   348,    81,    89,
      96,   111,    36,     0,     0,    41,    47,    56,    55,    63,
       0,     0,   442,   443,   445,   444,   446,   447,   433,   448,
     304,    65,    75,   158,   345,     0,   337,   339,   368,   344,
       0,     0,   221,   222,     0,   265,   324,   267,     7,     7,
       7,   327,   160,   199,   200,   198,   206,   207,   208,   209,
     211,   212,   213,   214,   215,   216,   217,   218,   210,   205,
       0,     0,     0,     0,   251,     0,     0,     0,   252,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   262,   278,
     277,     0,   292,   336,     0,   334,     0,   291,   306,   307,
     309,   311,   313,   316,     0,     7,   187,   323,     0,     0,
       0,   352,   431,   452,     9,     0,     0,     0,     0,    81,
      89,     0,     0,   284,     0,   343,   338,   340,   430,   451,
       0,     0,   331,     0,   332,   330,   329,     0,     0,   239,
       0,   244,   245,   250,   359,   360,   362,   364,   366,   317,
     318,   256,   269,   264,   281,     0,   335,     0,   189,     0,
       0,   190,   354,   353,   369,     0,     0,     0,     0,    28,
      83,    82,     0,     0,     0,    30,    91,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    98,
      97,     0,     0,     0,     0,    34,   113,   112,     0,     0,
       0,     0,   587,   141,   342,   341,     0,   224,   266,     7,
     368,   346,   347,   236,   237,   238,   257,   288,     0,     0,
       7,   188,   152,    88,   154,    95,   110,    80,    84,   135,
     136,   134,     0,    92,    93,    94,     0,     0,     0,   121,
     120,   118,   119,   125,   127,   128,   126,     0,   122,   123,
     107,   108,   109,     0,   106,   104,     0,     0,     0,   117,
      38,    40,   469,   228,   229,   230,   231,   232,   224,     0,
     220,   333,   287,     0,   192,   191,     0,     0,     0,     0,
     101,   102,   103,    99,     0,     0,   100,   116,     0,   115,
     219,     0,     7,    89,    96,   111,   133,   124,   105,     0,
     227,   225,   226,   193,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   132,     0,    85,    86,    87,     0,   130,
     129,   131
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -694,  -694,    -1,  -553,     7,  -694,  -694,   669,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
     253,  -694,   442,  -694,    11,  -252,  -653,  -107,  -156,   -63,
    -146,   -86,  -153,  -667,  -694,  -693,  -694,  -141,  -694,  -694,
    -694,  -694,  -694,     0,  -411,  -162,  -694,   291,    38,   299,
    -694,    15,   -22,  -694,  -694,    46,   526,   131,    -5,  -694,
    -694,  -195,  -694,  -694,  -694,  -694,   -60,  -694,  -694,  -694,
     275,  -694,  -694,  -694,   276,  -694,  -694,  -694,   -93,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -422,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -202,    98,  -694,
    -694,  -694,   236,  -694,   101,  -694,  -694,  -694,  -694,  -694,
     233,  -694,  -203,  -192,   -12,   230,   235,   229,  -694,  -127,
    -344,  -694,  -694,  -694,  -215,  -694,  -338,   -49,  -694,   143,
     107,  -694,  -430,  -694,   110,  -551,  -694,  -694,  -694,  -694,
     522,  -233,   119,   120,   121,  -694,  -163,  -429,  -177,  -694,
    -663,  -694,   611,  -694,   -37,  -694,  -694,   609,  -694,   379,
    -694,  -694,   -36,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   746,   455,   747,    33,    34,    35,    54,    57,
      59,    66,    77,    82,    84,   169,   172,   173,   440,   601,
     170,   134,   248,   742,   685,   249,   686,   252,   687,   823,
     824,   254,   688,   761,   811,   817,   818,   819,   748,   890,
     878,   749,   801,   285,   135,   774,    36,    37,    38,    39,
     793,    49,   795,   179,   443,    40,   695,   267,   750,   203,
     204,   205,   206,   207,   676,   730,   731,   208,   209,   463,
     464,   210,   211,   470,   471,   638,   212,   614,   840,   838,
     213,   214,   473,   215,   216,   495,   496,   497,   498,   217,
     218,   516,   219,   220,   520,   221,   222,   517,   518,   223,
     224,   525,   526,   527,   528,   225,   446,   226,   227,   531,
     532,   228,   136,   137,   229,   230,   231,   232,   233,   234,
     235,   502,   503,   504,   505,   236,   237,   238,   456,   457,
     664,   665,   619,   606,   696,   697,   607,   779,   575,   239,
     567,   568,   506,   507,   508,   509,   510,   570,   571,   572,
     240,   139,   418,   419,   140,   242,   141,   431,   598,   432,
     243,   244,   142,   143,   286,   144,   290,   145,   295,   146,
     301,   147,   314,   148,   322,   149,   332,   150,   341,   151,
     347,   152,   350,   153,   354,   154,   359,   155,   364,   156,
     375,   157,   379,   158,   384,   159,   160,   396,   161,   389,
     162,   391,   163,   393,   164,   403,   165,   406,   166,   412
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      31,   253,    41,   241,   245,   584,   434,    44,    32,   460,
     241,   245,   138,   499,   577,   674,   605,   609,   521,   620,
     790,   768,   565,   776,   500,   529,   609,    50,    51,   376,
     615,   529,   565,   175,   563,   202,   176,   770,   177,   511,
     782,   246,   250,   538,   563,   564,    45,   622,   251,    48,
      48,    48,   644,   870,   626,   564,    47,     3,   694,   539,
       4,   888,     5,   380,    42,   702,   704,   705,   547,    53,
     827,   377,   378,   540,   569,   420,   645,   777,   262,   263,
     264,     6,     7,    43,   569,   381,   382,   271,   272,     3,
     167,   168,     4,   256,     5,   279,   383,   658,   259,   255,
     659,    48,    48,    48,   258,   265,   646,  -298,   261,   616,
      48,    48,   889,     6,     7,   617,   277,  -299,    48,    87,
      88,    89,   729,   762,   754,     3,    58,   755,     4,     4,
       5,     5,   433,     3,    83,   348,     4,  -298,     5,     3,
     763,   538,     4,   247,     5,   775,   512,  -299,   349,     6,
       7,   420,   171,   751,   752,   753,   754,     6,     7,   755,
     871,   872,   394,     6,     7,   869,   404,   241,   245,   735,
     178,   540,   756,   -79,   736,   775,   737,   519,   395,   764,
     862,   679,   405,   -88,   447,   448,   663,   201,   566,   751,
     752,   753,   754,   390,   654,   755,   655,   392,   566,   762,
     754,   269,   270,   755,   501,   273,   274,   640,   756,   768,
     874,   757,   280,    55,   586,    56,   763,   641,   241,   245,
     458,   241,   245,   675,   441,   713,   841,   530,   451,   616,
     616,   604,   642,   666,   721,   682,   683,   844,   452,    78,
     604,    79,   442,   563,   621,   791,    80,   757,   351,   499,
     582,    81,   563,   585,   564,   764,   275,   276,   352,   353,
     500,   738,     4,   564,     5,   855,   616,   616,    14,    15,
     453,   499,   698,   699,   781,   511,   609,   454,   132,   778,
     813,   589,   500,   608,  -358,  -358,  -358,  -358,   765,  -358,
     587,  -358,   608,   421,   444,   445,   648,   511,   458,   789,
     609,   513,   514,   515,   814,   815,    27,   677,    46,   873,
     287,   288,   289,    48,   643,    28,   499,   472,   385,   499,
     758,    29,   663,   592,   593,   565,   535,   500,   360,   536,
     500,   386,   513,   514,   515,   578,    30,   563,   654,   681,
     655,   537,   511,   573,   594,   511,   574,   387,   564,     3,
     361,   362,     4,   363,     5,   257,   881,   565,   816,   266,
     260,   266,   266,   590,   882,   266,   266,   579,   268,   563,
     739,   422,   266,     6,     7,   388,   580,   608,   278,   735,
     564,   581,   281,   435,   736,   436,   737,   437,   438,   591,
     423,   424,   425,   426,   427,    87,    88,    89,   428,   174,
     429,   430,   693,     4,   600,     5,   618,   588,   355,   608,
     603,   673,   356,   712,   789,   609,   407,   595,   596,   597,
     439,    43,   429,   430,   282,   283,   284,   461,   462,   408,
     623,   565,   612,   613,   357,   358,   409,   522,   523,   524,
     501,   533,   534,   563,   499,   410,   563,   563,   563,   563,
     563,   411,   563,   499,   564,   500,   723,   564,   564,   564,
     564,   564,   501,   564,   500,   513,   514,   515,   610,   725,
     511,   738,   714,   715,   611,   563,   563,   563,   291,   511,
     292,   293,   294,   608,   649,   650,   564,   564,   564,   624,
     604,   566,   720,   296,   297,   298,   299,   300,   499,   647,
     563,   627,   563,   397,   475,  -358,   547,   501,   628,   500,
     501,   564,   629,   564,   604,   732,   733,   734,   398,   786,
     651,   668,   669,   566,   511,   652,   563,   454,   703,   662,
     399,   653,   788,   820,   821,   822,   400,   564,   342,   656,
     780,   846,   608,    67,    68,    69,    70,   657,   343,    71,
      72,   661,    73,    74,   344,    75,    86,    87,    88,    89,
     345,   346,   401,   402,   548,   678,   608,   266,   549,   799,
     800,   680,   550,   689,   684,   690,   523,   524,   551,   691,
     830,   701,   480,   692,   809,   810,    76,   538,   552,   806,
     807,   700,   333,   553,   334,   707,   708,   566,   554,   709,
     710,   555,   771,   719,   556,   557,   772,   773,   558,   783,
     784,   559,   335,   560,   336,   337,   785,   338,   561,   562,
     787,   797,   802,   808,   339,   340,   826,   241,   245,   604,
      60,   843,    61,   711,    62,   501,   839,    63,    64,    65,
     812,   563,   832,   842,   501,   849,   315,   854,   316,   241,
     245,     8,   564,     9,   858,    10,   618,   861,    11,    12,
      13,   863,   864,   866,    14,    15,   317,   865,   318,   319,
     320,   321,   883,   877,   728,   181,   182,   183,   184,   185,
     186,   608,   884,   891,   740,    52,   759,   766,   847,   501,
     241,   245,   741,   602,   760,   767,   492,   493,   583,   494,
     769,   828,    27,   465,   466,   467,   468,   469,   875,   868,
     848,    28,   876,   867,   201,   796,   132,    29,   630,   631,
     632,   633,   634,   635,   636,   637,   323,   324,   413,   459,
     845,   414,    30,   241,   245,   792,   794,   794,   625,   415,
     325,   798,   326,   327,   328,   860,   639,   803,   804,   805,
     833,   834,   835,   836,   837,   722,   329,   330,   331,   852,
     825,   660,   724,   706,   667,   670,   672,   829,   740,   576,
     716,   671,   717,   727,   718,   726,   741,   857,   416,   417,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   450,   449,
     599,     0,     0,     0,     0,   850,   851,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   853,     0,     0,     0,
     365,     0,   856,   366,     0,     0,     0,   859,     0,     3,
       0,     0,     4,     0,     5,   367,     0,   241,   245,   368,
       0,     0,   369,   370,     0,     0,     0,   371,   372,   373,
     374,    85,     0,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,     0,     0,     0,   879,     0,
       0,     0,     0,     0,   759,   766,     0,     0,     0,   885,
     886,   887,   760,   767,   181,   182,   183,   184,   185,   186,
       0,     0,     0,     0,     0,     0,   743,     0,     0,     0,
     187,    86,    87,    88,    89,     0,     0,     0,     0,    90,
       0,     0,   744,    91,     0,     0,     0,    92,     0,     0,
       0,     0,     0,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,     0,     0,     0,     0,    95,     0,
       0,     0,     0,    96,     0,     0,    97,     0,     0,    98,
      99,     0,     0,   100,     0,     0,   101,     0,   102,     0,
       0,     0,     0,   103,   104,     0,   105,   106,   107,     0,
       0,   108,   109,     0,     0,   110,   111,   188,     0,     0,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   189,     0,
       0,     0,   302,   303,     0,     0,   304,     0,   190,     0,
       3,   191,     0,     4,     0,     5,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   192,     0,     0,     0,     0,
       0,     0,    85,     0,     6,     7,     0,     0,   193,     0,
       0,   194,   195,   196,   197,   180,     0,     0,   198,     0,
       0,     0,   199,   200,     0,     0,     0,     0,     0,   201,
     745,   132,   133,     0,     0,   181,   182,   183,   184,   185,
     186,     0,     0,     0,     0,     0,     0,   743,     0,     0,
       0,   187,    86,    87,    88,    89,     0,     0,     0,     0,
      90,     0,     0,   744,    91,     0,     0,     0,    92,     0,
       0,     0,     0,     0,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    94,     0,     0,     0,     0,    95,
       0,     0,     0,     0,    96,     0,     0,    97,     0,     0,
      98,    99,     0,     0,   100,     0,     0,   101,     0,   102,
       0,     0,     0,     0,   103,   104,     0,   105,   106,   107,
       0,     0,   108,   109,     0,     0,   110,   111,   188,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   189,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   190,
       0,     3,   191,     0,     4,     0,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,     0,     0,     0,
       0,     0,     0,    85,     0,     6,     7,     0,     0,   193,
       0,     0,   194,   195,   196,   197,   180,     0,     0,   198,
       0,     0,     0,   199,   200,     0,     0,     0,     0,     0,
     201,   831,   132,   133,     0,     0,   181,   182,   183,   184,
     185,   186,     0,     0,     0,     0,     0,     0,   743,     0,
       0,     0,   187,    86,    87,    88,    89,     0,     0,     0,
       0,    90,     0,     0,   744,    91,     0,     0,     0,    92,
       0,     0,     0,     0,     0,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
      95,     0,     0,     0,     0,    96,     0,     0,    97,     0,
       0,    98,    99,     0,     0,   100,     0,     0,   101,     0,
     102,     0,     0,     0,     0,   103,   104,     0,   105,   106,
     107,     0,     0,   108,   109,     0,     0,   110,   111,   188,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     189,   474,     0,     0,     0,     0,     0,     0,     0,     0,
     190,     0,     0,   191,     0,     0,     0,   475,     0,    85,
       0,     0,     0,     0,     0,     0,     0,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     193,     0,     0,   194,   195,   196,   197,     0,     0,     0,
     198,     0,     0,     0,   199,   200,     0,     0,     0,     0,
       0,   201,   880,   132,   133,     0,     0,     0,     0,    86,
      87,    88,    89,     0,     0,     0,     0,   476,     0,     0,
       0,   477,     0,     0,     0,   478,     0,     0,     0,     0,
       0,   479,     0,     0,     0,   480,     0,     0,     0,     0,
       0,   481,     0,     0,     0,     0,   482,     0,     0,     0,
       0,   483,     0,     0,   484,     0,     0,   485,   486,     0,
       0,   487,     0,     0,   488,     0,   489,     0,     0,     0,
       0,   490,   491,     0,   105,   106,   107,     0,     0,   108,
     109,     0,     0,   110,   111,   112,     0,     0,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   541,   542,   543,
     544,   545,   546,     0,     0,     0,     0,     0,     0,   475,
       0,   547,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   492,
     493,     0,   494,     0,     0,     0,     0,   475,     0,    85,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   132,
     133,    86,    87,    88,    89,     0,     0,     0,     0,   548,
       0,     0,     0,   549,     0,     0,     0,   550,     0,     0,
       0,     0,     0,   551,     0,     0,     0,   480,     0,     0,
       0,     0,     0,   552,     0,     0,     0,     0,   553,    86,
      87,    88,    89,   554,     0,     0,   555,   476,     0,   556,
     557,   477,     0,   558,     0,   478,   559,     0,   560,     0,
       0,   479,     0,   561,   562,   480,     0,     0,     0,     0,
       0,   481,     0,     0,     0,     0,   482,     0,     0,     0,
       0,   483,     0,     0,   484,     0,     0,   485,   486,     0,
       0,   487,     0,     0,   488,     0,   489,     0,     0,     0,
       0,   490,   491,     0,   105,   106,   107,     0,     0,   108,
     109,     0,     0,   110,   111,   112,     0,     0,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   475,     0,   547,
       0,   492,   493,     0,   494,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
       0,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   492,
     493,     0,   494,     0,     0,     0,     0,     0,     0,    86,
      87,    88,    89,     0,     0,     0,     0,   548,     0,   132,
     133,   549,     0,     0,     0,   550,     0,     0,     0,     0,
       0,   551,     0,     0,     0,   480,     0,     0,     0,     0,
       0,   552,     0,     0,     0,     0,   553,     0,     0,     0,
       0,   554,     0,     0,   555,     0,     0,   556,   557,     0,
       0,   558,     0,     0,   559,     0,   560,     0,     0,    85,
       0,   561,   562,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   181,   182,   183,   184,   185,   186,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   187,    86,
      87,    88,    89,     0,     0,     0,     0,    90,     0,     0,
       0,    91,     0,     0,     0,    92,     0,     0,     0,     0,
       0,    93,     0,     0,     0,     0,     0,     0,     0,   492,
     493,    94,   494,     0,     0,     0,    95,     0,     0,     0,
       0,    96,     0,     0,    97,     0,     0,    98,    99,   132,
       0,   100,     0,     0,   101,     0,   102,     0,     0,     0,
       0,   103,   104,     0,   105,   106,   107,     0,     0,   108,
     109,     0,     0,   110,   111,   188,     0,     0,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   189,     0,     0,     0,
       0,     0,     0,    85,     0,     0,   190,     0,     0,   191,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   192,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   193,     0,     0,   194,
     195,   196,   197,     0,     0,     0,   198,     0,     0,     0,
     199,   200,     0,    86,    87,    88,    89,   201,     0,   132,
     133,    90,     0,     0,     0,    91,     0,     0,     0,    92,
       0,     0,     0,     0,     0,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
      95,     0,     0,     0,     0,    96,     0,     0,    97,     0,
       0,    98,    99,    85,     0,   100,     0,     0,   101,     0,
     102,     0,     0,     0,     0,   103,   104,     0,   105,   106,
     107,     0,     0,   108,   109,     0,     0,   110,   111,   112,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,     0,     0,    86,    87,    88,    89,     0,     0,     0,
       0,    90,     0,     0,     0,    91,     0,     0,     0,    92,
       0,     0,     0,     0,     0,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
      95,     0,     0,     0,     0,    96,     0,     0,    97,     0,
       0,    98,    99,     0,     0,   100,     0,     0,   101,     0,
     102,   201,     0,   132,   133,   103,   104,     0,   105,   106,
     107,     0,     0,   108,   109,   547,     0,   110,   111,   112,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,     0,     0,   547,     0,     0,     0,     0,   181,   182,
     183,   184,   185,   186,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    86,    87,    88,    89,     0,
       0,     0,     0,   548,     0,     0,     0,   549,     0,     0,
       0,   550,     0,     0,     0,     0,     0,   551,     0,     0,
       0,   480,     0,    86,    87,    88,    89,   552,     0,     0,
       0,   548,   553,   132,   133,   549,     0,   554,     0,   550,
     555,     0,     0,   556,   557,   551,     0,   558,     0,   480,
     559,     0,   560,     0,     0,   552,     0,   561,   562,     0,
     553,     0,     0,     2,     3,   554,     0,     4,   555,     5,
       0,   556,   557,     0,     0,   558,     0,     0,   559,     0,
     560,     0,     0,     0,     0,   561,   562,     0,     6,     7,
       0,     0,     8,     0,     9,     0,    10,     0,     0,    11,
      12,    13,     0,     0,     0,    14,    15,    16,     0,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   492,   493,  -142,   494,     0,
       0,     0,     0,    27,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,     0,   132,     0,     0,    29,     0,
       0,     0,     0,   492,   493,     0,   494,     0,     0,     0,
       0,     0,     0,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   132
};

static const yytype_int16 yycheck[] =
{
       1,    50,     3,    40,    40,   257,   133,     7,     1,   204,
      47,    47,    24,   216,   247,    23,   446,   446,   220,     7,
       7,   688,   237,    20,   216,    29,   455,    12,    13,    84,
     452,    29,   247,    34,   237,    40,    36,   690,    38,   216,
     703,    42,    47,     8,   247,   237,     8,   458,    48,    11,
      12,    13,   474,    74,   465,   247,    10,     1,    65,    24,
       4,    22,     6,   104,    75,   618,   619,   620,    23,    33,
     763,   126,   127,    38,   237,   112,     8,    74,    63,    64,
      65,    25,    26,    74,   247,   126,   127,    72,    73,     1,
     228,   229,     4,    55,     6,    80,   137,   519,    60,    53,
     522,    63,    64,    65,    58,    67,    38,     8,    62,   453,
      72,    73,    73,    25,    26,   453,    78,     8,    80,    74,
      75,    76,   675,    67,    68,     1,    33,    71,     4,     4,
       6,     6,   132,     1,    31,   107,     4,    38,     6,     1,
      84,     8,     4,   230,     6,   696,    62,    38,   120,    25,
      26,   188,    74,    65,    66,    67,    68,    25,    26,    71,
     181,   182,    97,    25,    26,   858,    97,   204,   204,    31,
      40,    38,    84,   231,    36,   726,    38,    62,   113,   123,
     843,     7,   113,   231,   184,   185,   530,   231,   237,    65,
      66,    67,    68,   142,    20,    71,    22,   142,   247,    67,
      68,    70,    71,    71,   216,    74,    75,   105,    84,   876,
     863,   123,    81,    29,   263,    31,    84,   115,   255,   255,
     227,   258,   258,   231,    73,   647,   779,   231,   198,   573,
     574,   446,   130,   231,   656,   573,   574,   790,    62,    29,
     455,    31,   226,   446,   232,   232,    36,   123,   113,   452,
     255,    41,   455,   258,   446,   123,    29,    30,   123,   124,
     452,   123,     4,   455,     6,     7,   610,   611,    42,    43,
      62,   474,   610,   611,   703,   452,   705,     4,   233,   701,
      74,   281,   474,   446,    15,    16,    17,    18,   232,    20,
     275,    22,   455,    74,    44,    45,   498,   474,   227,   729,
     729,   217,   218,   219,    98,    99,    80,   540,     9,   862,
      82,    83,    84,   275,   212,    89,   519,   211,    84,   522,
     232,    95,   666,    82,    83,   540,    17,   519,   104,    18,
     522,    97,   217,   218,   219,   231,   110,   540,    20,   572,
      22,   236,   519,    36,   103,   522,    36,   113,   540,     1,
     126,   127,     4,   129,     6,    56,   232,   572,   152,    68,
      61,    70,    71,     7,   232,    74,    75,   231,    69,   572,
     232,   152,    81,    25,    26,   141,   231,   540,    79,    31,
     572,   231,    83,    30,    36,    32,    38,    34,    35,   237,
     171,   172,   173,   174,   175,    74,    75,    76,   179,     0,
     181,   182,   605,     4,   235,     6,   455,   276,   100,   572,
      73,   538,   104,   646,   844,   844,    84,   176,   177,   178,
      67,    74,   181,   182,    77,    78,    79,   181,   182,    97,
      73,   646,   200,   201,   126,   127,   104,   221,   222,   223,
     452,    15,    16,   646,   647,   113,   649,   650,   651,   652,
     653,   119,   655,   656,   646,   647,   658,   649,   650,   651,
     652,   653,   474,   655,   656,   217,   218,   219,    36,   664,
     647,   123,   649,   650,    36,   678,   679,   680,    84,   656,
      86,    87,    88,   646,    15,    16,   678,   679,   680,    73,
     705,   540,   655,    90,    91,    92,    93,    94,   701,     5,
     703,    73,   705,    86,    21,   236,    23,   519,    73,   701,
     522,   703,    73,   705,   729,   678,   679,   680,   101,   721,
      17,   533,   534,   572,   701,    18,   729,     4,     5,   529,
     113,   236,   727,    63,    64,    65,   119,   729,    97,     5,
     703,   793,   705,    29,    30,    31,    32,     7,   107,    35,
      36,     7,    38,    39,   113,    41,    73,    74,    75,    76,
     119,   120,   145,   146,    81,     7,   729,   276,    85,    56,
      57,     8,    89,   231,   575,   231,   222,   223,    95,    73,
     232,    28,    99,    73,    69,    70,    72,     8,   105,   751,
     752,    73,    84,   110,    86,    84,    84,   646,   115,    74,
      84,   118,     7,    73,   121,   122,   238,    74,   125,    74,
      74,   128,   104,   130,   106,   107,    74,   109,   135,   136,
     232,    74,    74,   230,   116,   117,   230,   664,   664,   844,
      29,     5,    31,   645,    33,   647,   199,    36,    37,    38,
      73,   844,    73,   232,   656,    27,    84,     8,    86,   686,
     686,    29,   844,    31,     5,    33,   705,    73,    36,    37,
      38,   231,   231,    74,    42,    43,   104,   231,   106,   107,
     108,   109,    74,    28,   674,    56,    57,    58,    59,    60,
      61,   844,   111,    73,   685,    16,   687,   688,   795,   701,
     727,   727,   685,   440,   687,   688,   213,   214,   256,   216,
     689,   764,    80,   184,   185,   186,   187,   188,   864,   855,
     796,    89,   865,   854,   231,   737,   233,    95,   189,   190,
     191,   192,   193,   194,   195,   196,    82,    83,   100,   203,
     790,   103,   110,   770,   770,   735,   736,   737,   463,   111,
      96,   742,    98,    99,   100,   838,   470,   748,   749,   750,
     205,   206,   207,   208,   209,   657,   112,   113,   114,   808,
     761,   525,   661,   620,   531,   535,   537,   768,   769,   247,
     651,   536,   652,   666,   653,   665,   769,   826,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   189,   188,
     421,    -1,    -1,    -1,    -1,   806,   807,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   817,    -1,    -1,    -1,
     104,    -1,   823,   107,    -1,    -1,    -1,   828,    -1,     1,
      -1,    -1,     4,    -1,     6,   119,    -1,   874,   874,   123,
      -1,    -1,   126,   127,    -1,    -1,    -1,   131,   132,   133,
     134,    23,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,   869,    -1,
      -1,    -1,    -1,    -1,   875,   876,    -1,    -1,    -1,   880,
     881,   882,   875,   876,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,   110,    -1,
      -1,    -1,    -1,   115,    -1,    -1,   118,    -1,    -1,   121,
     122,    -1,    -1,   125,    -1,    -1,   128,    -1,   130,    -1,
      -1,    -1,    -1,   135,   136,    -1,   138,   139,   140,    -1,
      -1,   143,   144,    -1,    -1,   147,   148,   149,    -1,    -1,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,    -1,
      -1,    -1,    82,    83,    -1,    -1,    86,    -1,   180,    -1,
       1,   183,    -1,     4,    -1,     6,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   197,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    25,    26,    -1,    -1,   210,    -1,
      -1,   213,   214,   215,   216,    36,    -1,    -1,   220,    -1,
      -1,    -1,   224,   225,    -1,    -1,    -1,    -1,    -1,   231,
     232,   233,   234,    -1,    -1,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    84,    85,    -1,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,   115,    -1,    -1,   118,    -1,    -1,
     121,   122,    -1,    -1,   125,    -1,    -1,   128,    -1,   130,
      -1,    -1,    -1,    -1,   135,   136,    -1,   138,   139,   140,
      -1,    -1,   143,   144,    -1,    -1,   147,   148,   149,    -1,
      -1,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   180,
      -1,     1,   183,    -1,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    25,    26,    -1,    -1,   210,
      -1,    -1,   213,   214,   215,   216,    36,    -1,    -1,   220,
      -1,    -1,    -1,   224,   225,    -1,    -1,    -1,    -1,    -1,
     231,   232,   233,   234,    -1,    -1,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    84,    85,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,
     110,    -1,    -1,    -1,    -1,   115,    -1,    -1,   118,    -1,
      -1,   121,   122,    -1,    -1,   125,    -1,    -1,   128,    -1,
     130,    -1,    -1,    -1,    -1,   135,   136,    -1,   138,   139,
     140,    -1,    -1,   143,   144,    -1,    -1,   147,   148,   149,
      -1,    -1,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     180,    -1,    -1,   183,    -1,    -1,    -1,    21,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     210,    -1,    -1,   213,   214,   215,   216,    -1,    -1,    -1,
     220,    -1,    -1,    -1,   224,   225,    -1,    -1,    -1,    -1,
      -1,   231,   232,   233,   234,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,
      -1,   115,    -1,    -1,   118,    -1,    -1,   121,   122,    -1,
      -1,   125,    -1,    -1,   128,    -1,   130,    -1,    -1,    -1,
      -1,   135,   136,    -1,   138,   139,   140,    -1,    -1,   143,
     144,    -1,    -1,   147,   148,   149,    -1,    -1,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   213,
     214,    -1,   216,    -1,    -1,    -1,    -1,    21,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   233,
     234,    73,    74,    75,    76,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,
      -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,   110,    73,
      74,    75,    76,   115,    -1,    -1,   118,    81,    -1,   121,
     122,    85,    -1,   125,    -1,    89,   128,    -1,   130,    -1,
      -1,    95,    -1,   135,   136,    99,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,
      -1,   115,    -1,    -1,   118,    -1,    -1,   121,   122,    -1,
      -1,   125,    -1,    -1,   128,    -1,   130,    -1,    -1,    -1,
      -1,   135,   136,    -1,   138,   139,   140,    -1,    -1,   143,
     144,    -1,    -1,   147,   148,   149,    -1,    -1,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,    21,    -1,    23,
      -1,   213,   214,    -1,   216,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,
      -1,   233,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   213,
     214,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    -1,    -1,    -1,    -1,    81,    -1,   233,
     234,    85,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,
      -1,   115,    -1,    -1,   118,    -1,    -1,   121,   122,    -1,
      -1,   125,    -1,    -1,   128,    -1,   130,    -1,    -1,    23,
      -1,   135,   136,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   213,
     214,   105,   216,    -1,    -1,    -1,   110,    -1,    -1,    -1,
      -1,   115,    -1,    -1,   118,    -1,    -1,   121,   122,   233,
      -1,   125,    -1,    -1,   128,    -1,   130,    -1,    -1,    -1,
      -1,   135,   136,    -1,   138,   139,   140,    -1,    -1,   143,
     144,    -1,    -1,   147,   148,   149,    -1,    -1,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,   180,    -1,    -1,   183,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   197,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   210,    -1,    -1,   213,
     214,   215,   216,    -1,    -1,    -1,   220,    -1,    -1,    -1,
     224,   225,    -1,    73,    74,    75,    76,   231,    -1,   233,
     234,    81,    -1,    -1,    -1,    85,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,
     110,    -1,    -1,    -1,    -1,   115,    -1,    -1,   118,    -1,
      -1,   121,   122,    23,    -1,   125,    -1,    -1,   128,    -1,
     130,    -1,    -1,    -1,    -1,   135,   136,    -1,   138,   139,
     140,    -1,    -1,   143,   144,    -1,    -1,   147,   148,   149,
      -1,    -1,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,    -1,    -1,    73,    74,    75,    76,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,
     110,    -1,    -1,    -1,    -1,   115,    -1,    -1,   118,    -1,
      -1,   121,   122,    -1,    -1,   125,    -1,    -1,   128,    -1,
     130,   231,    -1,   233,   234,   135,   136,    -1,   138,   139,
     140,    -1,    -1,   143,   144,    23,    -1,   147,   148,   149,
      -1,    -1,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,    -1,    -1,    23,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    99,    -1,    73,    74,    75,    76,   105,    -1,    -1,
      -1,    81,   110,   233,   234,    85,    -1,   115,    -1,    89,
     118,    -1,    -1,   121,   122,    95,    -1,   125,    -1,    99,
     128,    -1,   130,    -1,    -1,   105,    -1,   135,   136,    -1,
     110,    -1,    -1,     0,     1,   115,    -1,     4,   118,     6,
      -1,   121,   122,    -1,    -1,   125,    -1,    -1,   128,    -1,
     130,    -1,    -1,    -1,    -1,   135,   136,    -1,    25,    26,
      -1,    -1,    29,    -1,    31,    -1,    33,    -1,    -1,    36,
      37,    38,    -1,    -1,    -1,    42,    43,    44,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   213,   214,    74,   216,    -1,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,   233,    -1,    -1,    95,    -1,
      -1,    -1,    -1,   213,   214,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   233
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   240,     0,     1,     4,     6,    25,    26,    29,    31,
      33,    36,    37,    38,    42,    43,    44,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    80,    89,    95,
     110,   241,   243,   244,   245,   246,   285,   286,   287,   288,
     294,   241,    75,    74,   282,   287,   288,   294,   287,   290,
     290,   290,   246,    33,   247,    29,    31,   248,    33,   249,
      29,    31,    33,    36,    37,    38,   250,    29,    30,    31,
      32,    35,    36,    38,    39,    41,    72,   251,    29,    31,
      36,    41,   252,    31,   253,    23,    73,    74,    75,    76,
      81,    85,    89,    95,   105,   110,   115,   118,   121,   122,
     125,   128,   130,   135,   136,   138,   139,   140,   143,   144,
     147,   148,   149,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   233,   234,   260,   283,   351,   352,   353,   390,
     393,   395,   401,   402,   404,   406,   408,   410,   412,   414,
     416,   418,   420,   422,   424,   426,   428,   430,   432,   434,
     435,   437,   439,   441,   443,   445,   447,   228,   229,   254,
     259,    74,   255,   256,     0,   241,   282,   282,    40,   292,
      36,    56,    57,    58,    59,    60,    61,    72,   149,   170,
     180,   183,   197,   210,   213,   214,   215,   216,   220,   224,
     225,   231,   297,   298,   299,   300,   301,   302,   306,   307,
     310,   311,   315,   319,   320,   322,   323,   328,   329,   331,
     332,   334,   335,   338,   339,   344,   346,   347,   350,   353,
     354,   355,   356,   357,   358,   359,   364,   365,   366,   378,
     389,   393,   394,   399,   400,   401,   241,   230,   261,   264,
     297,   282,   266,   366,   270,   294,   287,   288,   294,   287,
     288,   294,   290,   290,   290,   287,   286,   296,   288,   296,
     296,   290,   290,   296,   296,    29,    30,   287,   288,   290,
     296,   288,    77,    78,    79,   282,   403,    82,    83,    84,
     405,    84,    86,    87,    88,   407,    90,    91,    92,    93,
      94,   409,    82,    83,    86,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   411,    84,    86,   104,   106,   107,
     108,   109,   413,    82,    83,    96,    98,    99,   100,   112,
     113,   114,   415,    84,    86,   104,   106,   107,   109,   116,
     117,   417,    97,   107,   113,   119,   120,   419,   107,   120,
     421,   113,   123,   124,   423,   100,   104,   126,   127,   425,
     104,   126,   127,   129,   427,   104,   107,   119,   123,   126,
     127,   131,   132,   133,   134,   429,    84,   126,   127,   431,
     104,   126,   127,   137,   433,    84,    97,   113,   141,   438,
     142,   440,   142,   442,    97,   113,   436,    86,   101,   113,
     119,   145,   146,   444,    97,   113,   446,    84,    97,   104,
     113,   119,   448,   100,   103,   111,   150,   151,   391,   392,
     393,    74,   152,   171,   172,   173,   174,   175,   179,   181,
     182,   396,   398,   282,   358,    30,    32,    34,    35,    67,
     257,    73,   226,   293,    44,    45,   345,   282,   282,   391,
     396,   198,    62,    62,     4,   242,   367,   368,   227,   295,
     300,   181,   182,   308,   309,   184,   185,   186,   187,   188,
     312,   313,   211,   321,     5,    21,    81,    85,    89,    95,
      99,   105,   110,   115,   118,   121,   122,   125,   128,   130,
     135,   136,   213,   214,   216,   324,   325,   326,   327,   351,
     352,   353,   360,   361,   362,   363,   381,   382,   383,   384,
     385,   387,    62,   217,   218,   219,   330,   336,   337,    62,
     333,   336,   221,   222,   223,   340,   341,   342,   343,    29,
     231,   348,   349,    15,    16,    17,    18,   236,     8,    24,
      38,     9,    10,    11,    12,    13,    14,    23,    81,    85,
      89,    95,   105,   110,   115,   118,   121,   122,   125,   128,
     130,   135,   136,   351,   352,   363,   366,   379,   380,   385,
     386,   387,   388,    36,    36,   377,   379,   380,   231,   231,
     231,   231,   297,   261,   264,   297,   366,   290,   296,   282,
       7,   237,    82,    83,   103,   176,   177,   178,   397,   398,
     235,   258,   259,    73,   363,   371,   372,   375,   385,   386,
      36,    36,   200,   201,   316,   326,   359,   365,   366,   371,
       7,   232,   283,    73,    73,   309,   283,    73,    73,    73,
     189,   190,   191,   192,   193,   194,   195,   196,   314,   313,
     105,   115,   130,   212,   326,     8,    38,     5,   336,    15,
      16,    17,    18,   236,    20,    22,     5,     7,   326,   326,
     341,     7,   282,   359,   369,   370,   231,   349,   353,   353,
     354,   355,   356,   358,    23,   231,   303,   380,     7,     7,
       8,   380,   365,   365,   241,   263,   265,   267,   271,   231,
     231,    73,    73,   351,    65,   295,   373,   374,   365,   365,
      73,    28,   242,     5,   242,   242,   368,    84,    84,    74,
      84,   353,   380,   326,   387,   387,   381,   382,   383,    73,
     385,   326,   337,   336,   343,   300,   373,   369,   282,   242,
     304,   305,   385,   385,   385,    31,    36,    38,   123,   232,
     241,   243,   262,    68,    84,   232,   241,   243,   277,   280,
     297,    65,    66,    67,    68,    71,    84,   123,   232,   241,
     243,   272,    67,    84,   123,   232,   241,   243,   272,   263,
     265,     7,   238,    74,   284,   374,    20,    74,   326,   376,
     385,   386,   389,    74,    74,    74,   336,   232,   300,   371,
       7,   232,   282,   289,   282,   291,   291,    74,   241,    56,
      57,   281,    74,   241,   241,   241,   284,   284,   230,    69,
      70,   273,    73,    74,    98,    99,   152,   274,   275,   276,
      63,    64,    65,   268,   269,   241,   230,   274,   268,   241,
     232,   232,    73,   205,   206,   207,   208,   209,   318,   199,
     317,   242,   232,     5,   242,   305,   264,   266,   270,    27,
     241,   241,   366,   241,     8,     7,   241,   366,     5,   241,
     317,    73,   389,   231,   231,   231,    74,   276,   269,   274,
      74,   181,   182,   242,   265,   267,   271,    28,   279,   241,
     232,   232,   232,    74,   111,   241,   241,   241,    22,    73,
     278,    73
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   239,   240,   240,   241,   241,   242,   242,   243,   243,
     243,   244,   244,   244,   244,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   247,   248,   248,   248,
     248,   249,   250,   250,   250,   250,   250,   250,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   252,
     252,   252,   252,   253,   254,   255,   256,   256,   257,   257,
     257,   257,   257,   257,   258,   258,   259,   259,   260,   261,
     262,   263,   263,   263,   263,   263,   263,   263,   264,   265,
     265,   265,   265,   265,   265,   266,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   268,   268,   269,   269,   269,
     270,   271,   271,   271,   271,   271,   271,   271,   272,   272,
     273,   273,   274,   275,   275,   276,   276,   276,   276,   277,
     278,   278,   279,   279,   280,   281,   281,   282,   283,   283,
     283,   284,   285,   285,   286,   286,   286,   286,   286,   286,
     287,   288,   289,   290,   291,   292,   292,   293,   293,   294,
     295,   296,   296,   297,   297,   298,   299,   299,   300,   300,
     300,   300,   300,   300,   300,   300,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   301,   301,   302,   303,   303,
     304,   304,   304,   305,   306,   306,   307,   308,   308,   309,
     309,   310,   310,   311,   312,   312,   313,   313,   313,   313,
     313,   314,   314,   314,   314,   314,   314,   314,   314,   315,
     315,   316,   316,   316,   317,   317,   317,   317,   318,   318,
     318,   318,   318,   319,   320,   321,   321,   321,   321,   321,
     322,   323,   323,   324,   324,   325,   326,   326,   326,   327,
     327,   327,   327,   328,   328,   329,   330,   330,   330,   331,
     331,   332,   333,   333,   333,   334,   334,   335,   336,   336,
     337,   337,   337,   338,   338,   339,   340,   340,   341,   341,
     342,   342,   343,   343,   344,   345,   345,   346,   346,   347,
     348,   348,   349,   350,   351,   351,   351,   352,   353,   353,
     353,   353,   353,   353,   353,   354,   354,   354,   355,   355,
     356,   356,   357,   357,   358,   359,   359,   360,   361,   362,
     363,   363,   363,   364,   365,   365,   365,   366,   367,   367,
     367,   368,   368,   368,   369,   369,   370,   371,   371,   372,
     373,   373,   374,   374,   375,   375,   376,   376,   377,   377,
     378,   378,   378,   379,   379,   380,   380,   380,   381,   381,
     381,   382,   382,   383,   383,   384,   384,   385,   386,   386,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   388,   388,   388,   388,   388,   388,   389,   389,   389,
     389,   389,   389,   390,   390,   391,   391,   392,   392,   392,
     392,   392,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     394,   394,   395,   395,   396,   396,   396,   396,   396,   396,
     396,   396,   397,   397,   397,   397,   397,   397,   397,   398,
     398,   399,   400,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   402,
     403,   403,   403,   404,   405,   405,   405,   406,   407,   407,
     407,   407,   408,   409,   409,   409,   409,   409,   410,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   412,   413,   413,   413,   413,   413,   413,   413,   414,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   416,
     417,   417,   417,   417,   417,   417,   417,   417,   418,   419,
     419,   419,   419,   419,   420,   421,   421,   422,   423,   423,
     423,   424,   425,   425,   425,   425,   426,   427,   427,   427,
     427,   428,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   430,   431,   431,   431,   432,   433,   433,   433,
     433,   434,   434,   434,   434,   434,   434,   434,   435,   436,
     436,   437,   438,   438,   438,   438,   439,   440,   441,   442,
     443,   444,   444,   444,   444,   444,   444,   445,   446,   446,
     447,   448,   448,   448,   448,   448
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       2,     1,     1,     2,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     6,     2,
       6,     3,     2,     6,     6,     3,     3,     2,     6,     2,
       6,     3,     2,     2,     2,     2,     2,     3,     2,     2,
       2,     2,     2,     2,     2,     3,     3,     2,     2,     2,
       2,     2,     2,     3,     1,     3,     0,     1,     0,     1,
       1,     1,     1,     1,     0,     1,     1,     1,     1,     0,
       2,     0,     2,     2,     3,     8,     8,     8,     0,     0,
       2,     2,     3,     3,     3,     0,     0,     2,     2,     4,
       4,     4,     4,     4,     3,     3,     1,     1,     1,     1,
       0,     0,     2,     2,     6,     4,     4,     3,     2,     2,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     7,
       1,     2,     2,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     2,     1,     0,     2,     0,     2,     3,
       2,     0,     1,     1,     2,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       1,     3,     3,     5,     1,     2,     1,     1,     2,     2,
       2,     1,     2,     1,     1,     2,     2,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     7,
       6,     1,     1,     0,     0,     3,     3,     3,     1,     1,
       1,     1,     1,     2,     1,     0,     4,     4,     4,     3,
       2,     1,     1,     1,     3,     3,     1,     1,     1,     1,
       3,     2,     2,     2,     1,     1,     3,     4,     1,     2,
       1,     1,     2,     1,     3,     3,     5,     3,     1,     3,
       1,     1,     1,     1,     2,     1,     1,     2,     2,     1,
       1,     3,     1,     1,     4,     1,     1,     6,     5,     1,
       1,     2,     2,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     3,     3,     3,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     3,
       3,     3,     3,     5,     1,     2,     1,     1,     2,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     3,     3,     1,     1,     1,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     3,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     6,
       1,     1,     1,     2,     1,     1,     1,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     1,     1,
       1,     2,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     1,     1,     1,     1,     2,     4,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     2,     1,     1,
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
          case 74: /* "string"  */
#line 226 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2715 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 75: /* QUOTED_STRING  */
#line 226 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2721 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 76: /* ASTERISK_STRING  */
#line 226 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2727 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 244: /* line  */
#line 423 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2733 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 245: /* base_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2739 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 246: /* add_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2745 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 247: /* replace_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2751 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 248: /* create_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2757 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 249: /* insert_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2763 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 250: /* delete_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2769 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 251: /* list_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2775 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 252: /* flush_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2781 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 253: /* rename_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2787 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 254: /* export_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2793 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 255: /* monitor_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2799 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 256: /* monitor_event  */
#line 592 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2805 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 260: /* describe_cmd  */
#line 426 "parser_bison.y" /* yacc.c:1257  */
      { cmd_free(((*yyvaluep).cmd)); }
#line 2811 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 261: /* table_block_alloc  */
#line 441 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); table_free(((*yyvaluep).table)); }
#line 2817 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 264: /* chain_block_alloc  */
#line 443 "parser_bison.y" /* yacc.c:1257  */
      { close_scope(state); chain_free(((*yyvaluep).chain)); }
#line 2823 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 266: /* set_block_alloc  */
#line 452 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 2829 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 270: /* map_block_alloc  */
#line 455 "parser_bison.y" /* yacc.c:1257  */
      { set_free(((*yyvaluep).set)); }
#line 2835 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 276: /* type_identifier  */
#line 415 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2841 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 279: /* dev_spec  */
#line 438 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2847 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 282: /* identifier  */
#line 415 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2853 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 283: /* string  */
#line 415 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2859 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 287: /* table_spec  */
#line 429 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 2865 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 288: /* chain_spec  */
#line 429 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 2871 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 289: /* chain_identifier  */
#line 429 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 2877 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 290: /* set_spec  */
#line 431 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 2883 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 291: /* set_identifier  */
#line 431 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 2889 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 294: /* ruleid_spec  */
#line 429 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 2895 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 295: /* comment_spec  */
#line 415 "parser_bison.y" /* yacc.c:1257  */
      { xfree(((*yyvaluep).string)); }
#line 2901 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 296: /* ruleset_spec  */
#line 429 "parser_bison.y" /* yacc.c:1257  */
      { handle_free(&((*yyvaluep).handle)); }
#line 2907 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 297: /* rule  */
#line 445 "parser_bison.y" /* yacc.c:1257  */
      { rule_free(((*yyvaluep).rule)); }
#line 2913 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 299: /* stmt_list  */
#line 458 "parser_bison.y" /* yacc.c:1257  */
      { stmt_list_free(((*yyvaluep).list)); xfree(((*yyvaluep).list)); }
#line 2919 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 300: /* stmt  */
#line 460 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 2925 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 301: /* verdict_stmt  */
#line 460 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 2931 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 302: /* verdict_map_stmt  */
#line 517 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 2937 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 303: /* verdict_map_expr  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 2943 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 304: /* verdict_map_list_expr  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 2949 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 305: /* verdict_map_list_member_expr  */
#line 520 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 2955 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 306: /* counter_stmt  */
#line 462 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 2961 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 307: /* counter_stmt_alloc  */
#line 462 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 2967 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 310: /* log_stmt  */
#line 470 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 2973 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 311: /* log_stmt_alloc  */
#line 470 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 2979 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 315: /* limit_stmt  */
#line 473 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 2985 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 319: /* reject_stmt  */
#line 476 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 2991 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 320: /* reject_stmt_alloc  */
#line 476 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 2997 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 322: /* nat_stmt  */
#line 478 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3003 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 323: /* nat_stmt_alloc  */
#line 478 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3009 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 324: /* concat_stmt_expr  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3015 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 325: /* map_stmt_expr  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3021 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 326: /* stmt_expr  */
#line 508 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3027 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 328: /* masq_stmt  */
#line 478 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3033 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 329: /* masq_stmt_alloc  */
#line 478 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3039 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 331: /* redir_stmt  */
#line 478 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3045 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 332: /* redir_stmt_alloc  */
#line 478 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3051 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 334: /* dup_stmt  */
#line 484 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3057 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 335: /* fwd_stmt  */
#line 486 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3063 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 338: /* queue_stmt  */
#line 481 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3069 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 339: /* queue_stmt_alloc  */
#line 481 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3075 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 344: /* set_stmt  */
#line 488 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3081 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 346: /* flow_stmt  */
#line 491 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3087 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 347: /* flow_stmt_alloc  */
#line 491 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3093 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 350: /* match_stmt  */
#line 460 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3099 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 351: /* symbol_expr  */
#line 494 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3105 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 352: /* integer_expr  */
#line 494 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3111 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 353: /* primary_expr  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3117 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 354: /* shift_expr  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3123 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 355: /* and_expr  */
#line 496 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3129 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 356: /* exclusive_or_expr  */
#line 498 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3135 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 357: /* inclusive_or_expr  */
#line 498 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3141 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 358: /* basic_expr  */
#line 500 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3147 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 359: /* concat_expr  */
#line 511 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3153 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 360: /* prefix_rhs_expr  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3159 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 361: /* range_rhs_expr  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3165 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 362: /* wildcard_rhs_expr  */
#line 505 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3171 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 363: /* multiton_rhs_expr  */
#line 503 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3177 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 364: /* map_expr  */
#line 514 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3183 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 365: /* expr  */
#line 531 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3189 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 366: /* set_expr  */
#line 523 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3195 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 367: /* set_list_expr  */
#line 523 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3201 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 368: /* set_list_member_expr  */
#line 523 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3207 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 369: /* flow_key_expr  */
#line 528 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3213 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 370: /* flow_key_expr_alloc  */
#line 528 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3219 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 371: /* set_elem_expr  */
#line 525 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3225 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 372: /* set_elem_expr_alloc  */
#line 525 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3231 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 375: /* set_lhs_expr  */
#line 525 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3237 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 376: /* set_rhs_expr  */
#line 525 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3243 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 377: /* initializer_expr  */
#line 531 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3249 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 378: /* relational_expr  */
#line 542 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3255 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 379: /* list_rhs_expr  */
#line 536 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3261 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 380: /* rhs_expr  */
#line 534 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3267 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 381: /* shift_rhs_expr  */
#line 536 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3273 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 382: /* and_rhs_expr  */
#line 538 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3279 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 383: /* exclusive_or_rhs_expr  */
#line 538 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3285 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 384: /* inclusive_or_rhs_expr  */
#line 538 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3291 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 385: /* basic_rhs_expr  */
#line 534 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3297 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 386: /* concat_rhs_expr  */
#line 534 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3303 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 387: /* primary_rhs_expr  */
#line 536 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3309 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 389: /* verdict_expr  */
#line 494 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3315 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 390: /* meta_expr  */
#line 583 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3321 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 394: /* meta_stmt  */
#line 468 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3327 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 395: /* ct_expr  */
#line 587 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3333 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 399: /* ct_stmt  */
#line 466 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3339 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 400: /* payload_stmt  */
#line 464 "parser_bison.y" /* yacc.c:1257  */
      { stmt_free(((*yyvaluep).stmt)); }
#line 3345 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 401: /* payload_expr  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3351 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 402: /* payload_raw_expr  */
#line 546 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3357 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 404: /* eth_hdr_expr  */
#line 549 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3363 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 406: /* vlan_hdr_expr  */
#line 549 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3369 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 408: /* arp_hdr_expr  */
#line 552 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3375 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 410: /* ip_hdr_expr  */
#line 555 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3381 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 412: /* icmp_hdr_expr  */
#line 555 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3387 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 414: /* ip6_hdr_expr  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3393 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 416: /* icmp6_hdr_expr  */
#line 558 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3399 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 418: /* auth_hdr_expr  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3405 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 420: /* esp_hdr_expr  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3411 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 422: /* comp_hdr_expr  */
#line 561 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3417 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 424: /* udp_hdr_expr  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3423 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 426: /* udplite_hdr_expr  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3429 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 428: /* tcp_hdr_expr  */
#line 564 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3435 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 430: /* dccp_hdr_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3441 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 432: /* sctp_hdr_expr  */
#line 567 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3447 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 434: /* exthdr_expr  */
#line 571 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3453 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 435: /* hbh_hdr_expr  */
#line 573 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3459 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 437: /* rt_hdr_expr  */
#line 576 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3465 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 439: /* rt0_hdr_expr  */
#line 576 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3471 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 441: /* rt2_hdr_expr  */
#line 576 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3477 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 443: /* frag_hdr_expr  */
#line 573 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3483 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 445: /* dst_hdr_expr  */
#line 573 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3489 "parser_bison.c" /* yacc.c:1257  */
        break;

    case 447: /* mh_hdr_expr  */
#line 579 "parser_bison.y" /* yacc.c:1257  */
      { expr_free(((*yyvaluep).expr)); }
#line 3495 "parser_bison.c" /* yacc.c:1257  */
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
#line 112 "parser_bison.y" /* yacc.c:1429  */
{
	location_init(scanner, state, &yylloc);
#ifdef DEBUG
	if (debug_level & DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (debug_level & DEBUG_PARSER)
		yydebug = 1;
#endif
}

#line 3614 "parser_bison.c" /* yacc.c:1429  */
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
#line 599 "parser_bison.y" /* yacc.c:1646  */
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
#line 3816 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 8:
#line 624 "parser_bison.y" /* yacc.c:1646  */
    {
				if (scanner_include_file(scanner, (yyvsp[-1].string), &(yyloc)) < 0) {
					xfree((yyvsp[-1].string));
					YYERROR;
				}
				xfree((yyvsp[-1].string));
			}
#line 3828 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 9:
#line 632 "parser_bison.y" /* yacc.c:1646  */
    {
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, (yyvsp[-3].string)) != NULL) {
					erec_queue(error(&(yylsp[-3]), "redfinition of symbol '%s'", (yyvsp[-3].string)),
						   state->msgs);
					YYERROR;
				}

				symbol_bind(scope, (yyvsp[-3].string), (yyvsp[-1].expr));
				xfree((yyvsp[-3].string));
			}
#line 3845 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 645 "parser_bison.y" /* yacc.c:1646  */
    {
				if (++state->nerrs == max_errors)
					YYABORT;
				yyerrok;
			}
#line 3855 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 11:
#line 652 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 3861 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 653 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = NULL; }
#line 3867 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 654 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[-1].cmd); }
#line 3873 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 656 "parser_bison.y" /* yacc.c:1646  */
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
#line 3904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 684 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3910 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 16:
#line 685 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 686 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 687 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3928 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 688 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3934 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 689 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3940 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 690 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3946 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 691 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3952 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 692 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3958 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 693 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3964 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 694 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 695 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.cmd) = (yyvsp[0].cmd); }
#line 3976 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 699 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 3984 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 704 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 3994 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 710 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4002 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 715 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 4013 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 722 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 4021 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 726 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 4029 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 731 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 4039 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 738 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].set)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].set)->handle, &(yyvsp[-4].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].set));
			}
#line 4049 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 744 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 4057 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 750 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_REPLACE, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 4065 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 756 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4073 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 761 "parser_bison.y" /* yacc.c:1646  */
    {
				handle_merge(&(yyvsp[-3].table)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].table));
			}
#line 4083 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 767 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4091 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 772 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].chain)->location = (yylsp[-1]);
				handle_merge(&(yyvsp[-3].chain)->handle, &(yyvsp[-4].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[-4].handle), &(yyloc), (yyvsp[-1].chain));
			}
#line 4102 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 781 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].rule));
			}
#line 4110 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 42:
#line 787 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 791 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4126 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 795 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4134 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 799 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4142 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 803 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4150 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 807 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[-1].handle), &(yyloc), (yyvsp[0].expr));
			}
#line 4158 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 813 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4166 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 817 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4174 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 821 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4182 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 825 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAINS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4190 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 829 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4198 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 833 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 837 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4214 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 841 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLES, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4222 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 56:
#line 845 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_FLOWTABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4230 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 849 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAPS, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4238 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 853 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_MAP, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4246 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 859 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4254 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 863 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4262 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 867 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4270 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 871 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[0].handle), &(yyloc), NULL);
			}
#line 4278 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 877 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[-1].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[0].string);
			}
#line 4287 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 884 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct export *export = export_alloc((yyvsp[0].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_EXPORT, &h, &(yyloc), export);
			}
#line 4297 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 892 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[0].val), (yyvsp[-1].val), (yyvsp[-2].string));
				m->location = (yylsp[-2]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
#line 4308 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 900 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 4314 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 901 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 4320 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 904 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
#line 4326 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 905 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
#line 4332 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 906 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
#line 4338 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 907 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
#line 4344 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 908 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
#line 4350 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 909 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
#line 4356 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 912 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
#line 4362 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 916 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_XML; }
#line 4368 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 917 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
#line 4374 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 921 "parser_bison.y" /* yacc.c:1646  */
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[0].expr);
			}
#line 4384 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 79:
#line 929 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
#line 4393 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 936 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strcmp((yyvsp[0].string), "dormant") == 0) {
					(yyvsp[-2].table)->flags = TABLE_F_DORMANT;
				} else {
					erec_queue(error(&(yylsp[0]), "unknown table option %s", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}
			}
#line 4407 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 947 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
#line 4413 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 954 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].chain)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].chain)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[-4].chain)->list, &(yyvsp[-7].table)->chains);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 4426 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 86:
#line 965 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 4438 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 87:
#line 975 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].set)->location = (yylsp[-5]);
				handle_merge(&(yyvsp[-4].set)->handle, &(yyvsp[-5].handle));
				handle_free(&(yyvsp[-5].handle));
				list_add_tail(&(yyvsp[-4].set)->list, &(yyvsp[-7].table)->sets);
				(yyval.table) = (yyvsp[-7].table);
			}
#line 4450 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 88:
#line 985 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
#line 4459 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 991 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
#line 4465 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 94:
#line 997 "parser_bison.y" /* yacc.c:1646  */
    {
				list_add_tail(&(yyvsp[-1].rule)->list, &(yyvsp[-2].chain)->rules);
				(yyval.chain) = (yyvsp[-2].chain);
			}
#line 4474 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1004 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
			}
#line 4482 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1009 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 4488 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1013 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->keytype = (yyvsp[-1].datatype);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4497 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1018 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4506 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1023 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->timeout = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4515 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1028 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->gc_int = (yyvsp[-1].val) * 1000;
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4524 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1033 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4533 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1041 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 4541 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1047 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SET_F_CONSTANT; }
#line 4547 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1048 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SET_F_INTERVAL; }
#line 4553 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1049 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SET_F_TIMEOUT; }
#line 4559 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1053 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.set) = set_alloc(NULL);
				(yyval.set)->flags |= NFT_SET_MAP;
			}
#line 4568 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1059 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
#line 4574 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1065 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].set)->keytype  = (yyvsp[-3].datatype);
				(yyvsp[-5].set)->datatype = (yyvsp[-1].datatype);
				(yyval.set) = (yyvsp[-5].set);
			}
#line 4584 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1071 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->flags = (yyvsp[-1].val);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4593 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1076 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].set)->init = (yyvsp[0].expr);
				(yyval.set) = (yyvsp[-3].set);
			}
#line 4602 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1084 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->policy = (yyvsp[0].val);
			}
#line 4610 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1088 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].set)->desc.size = (yyvsp[0].val);
			}
#line 4618 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1093 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
#line 4624 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1094 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_SET_POL_MEMORY; }
#line 4630 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1098 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[0].val) & ~TYPE_MASK)
					(yyval.datatype) = concat_type_alloc((yyvsp[0].val));
				else
					(yyval.datatype) = datatype_lookup((yyvsp[0].val));
			}
#line 4641 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1107 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct datatype *dtype = datatype_lookup_byname((yyvsp[0].string));
				if (dtype == NULL) {
					erec_queue(error(&(yylsp[0]), "unknown datatype %s", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}
				(yyval.val) = dtype->type;
			}
#line 4655 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1117 "parser_bison.y" /* yacc.c:1646  */
    {
				const struct datatype *dtype = datatype_lookup_byname((yyvsp[0].string));
				if (dtype == NULL) {
					erec_queue(error(&(yylsp[0]), "unknown datatype %s", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}
				(yyval.val) = concat_subtype_add((yyval.val), dtype->type);
			}
#line 4669 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1128 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 4675 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1129 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("mark"); }
#line 4681 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1130 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("dscp"); }
#line 4687 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1131 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = xstrdup("ecn"); }
#line 4693 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1135 "parser_bison.y" /* yacc.c:1646  */
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
#line 4721 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1160 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 4727 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1161 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = -(yyvsp[0].val); }
#line 4733 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1164 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 4739 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1165 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 4745 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1169 "parser_bison.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].chain)->policy != -1) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[-2].chain)->policy	= (yyvsp[0].val);
			}
#line 4758 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1179 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_ACCEPT; }
#line 4764 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1180 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_DROP;   }
#line 4770 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1192 "parser_bison.y" /* yacc.c:1646  */
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
#line 4786 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1205 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 4792 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1209 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV4; }
#line 4798 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1210 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_IPV6; }
#line 4804 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1211 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_INET; }
#line 4810 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1212 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_ARP; }
#line 4816 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1213 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_BRIDGE; }
#line 4822 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1214 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFPROTO_NETDEV; }
#line 4828 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1218 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[-1].val);
				(yyval.handle).table	= (yyvsp[0].string);
			}
#line 4838 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1226 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 4847 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1233 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain	= (yyvsp[0].string);
			}
#line 4856 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1240 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-1].handle);
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 4865 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1247 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set		= (yyvsp[0].string);
			}
#line 4874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1254 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle_spec), 0, sizeof((yyval.handle_spec)));
			}
#line 4882 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1258 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle_spec), 0, sizeof((yyval.handle_spec)));
				(yyval.handle_spec).location	= (yyloc);
				(yyval.handle_spec).id		= (yyvsp[0].val);
			}
#line 4892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1266 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.position_spec), 0, sizeof((yyval.position_spec)));
			}
#line 4900 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1270 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.position_spec), 0, sizeof((yyval.position_spec)));
				(yyval.position_spec).location	= (yyloc);
				(yyval.position_spec).id		= (yyvsp[0].val);
			}
#line 4910 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1278 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.handle)		= (yyvsp[-2].handle);
				(yyval.handle).handle	= (yyvsp[-1].handle_spec);
				(yyval.handle).position	= (yyvsp[0].position_spec);
			}
#line 4920 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1286 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strlen((yyvsp[0].string)) > UDATA_COMMENT_MAXLEN) {
					erec_queue(error(&(yylsp[0]), "comment too long, %d characters maximum allowed", UDATA_COMMENT_MAXLEN),
						   state->msgs);
					YYERROR;
				}
				(yyval.string) = (yyvsp[0].string);
			}
#line 4933 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1297 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
#line 4942 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1302 "parser_bison.y" /* yacc.c:1646  */
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[0].val);
			}
#line 4951 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1309 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = NULL;
			}
#line 4959 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1313 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.rule)->comment = (yyvsp[0].string);
			}
#line 4967 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1319 "parser_bison.y" /* yacc.c:1646  */
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				list_for_each_entry(i, (yyvsp[0].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[0].list), &(yyval.rule)->stmts);
				xfree((yyvsp[0].list));
			}
#line 4981 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1331 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[0].stmt)->list, (yyval.list));
			}
#line 4991 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1337 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.list) = (yyvsp[-1].list);
				list_add_tail(&(yyvsp[0].stmt)->list, (yyvsp[-1].list));
			}
#line 5000 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1363 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 5008 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1367 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 5016 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1373 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5024 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1379 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 5033 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1384 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 5044 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1393 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 5053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1398 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 5062 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1406 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 5070 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1415 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
#line 5078 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1421 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 5086 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1428 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.packets = (yyvsp[0].val);
			}
#line 5094 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1432 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->counter.bytes	 = (yyvsp[0].val);
			}
#line 5102 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1442 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
#line 5110 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1448 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 5118 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1455 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.prefix	 = (yyvsp[0].string);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
#line 5127 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1460 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.group	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
#line 5136 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1465 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.snaplen	 = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
#line 5145 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1470 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.qthreshold = (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
#line 5154 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1475 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->log.level	= (yyvsp[0].val);
				(yyvsp[-2].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
#line 5163 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1481 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = LOG_EMERG; }
#line 5169 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1482 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = LOG_ALERT; }
#line 5175 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1483 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = LOG_CRIT; }
#line 5181 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1484 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = LOG_ERR; }
#line 5187 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1485 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = LOG_WARNING; }
#line 5193 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1486 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = LOG_NOTICE; }
#line 5199 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1487 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = LOG_INFO; }
#line 5205 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1488 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = LOG_DEBUG; }
#line 5211 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1492 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[-3].val);
				(yyval.stmt)->limit.unit	= (yyvsp[-1].val);
				(yyval.stmt)->limit.burst	= (yyvsp[0].val);
				(yyval.stmt)->limit.type	= NFT_LIMIT_PKTS;
				(yyval.stmt)->limit.flags = (yyvsp[-4].val);
			}
#line 5224 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1501 "parser_bison.y" /* yacc.c:1646  */
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
#line 5246 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1520 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_LIMIT_F_INV; }
#line 5252 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1521 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 5258 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1522 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 5264 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1525 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 5270 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1526 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 5276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1527 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 5282 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1529 "parser_bison.y" /* yacc.c:1646  */
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
#line 5298 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1542 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL; }
#line 5304 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1543 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60; }
#line 5310 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1544 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60; }
#line 5316 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1545 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
#line 5322 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1546 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
#line 5328 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1553 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
#line 5336 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1559 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[0].stmt)->reject.type = -1;
				(yyvsp[0].stmt)->reject.icmp_code = -1;
			}
#line 5345 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1564 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmp_code_type;
			}
#line 5359 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1574 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpv6_code_type;
			}
#line 5373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1584 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[-4].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[0].string));
				(yyvsp[-4].stmt)->reject.expr->dtype = &icmpx_code_type;
			}
#line 5386 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1593 "parser_bison.y" /* yacc.c:1646  */
    {
				if (strcmp((yyvsp[0].string), "reset") == 0) {
					(yyvsp[-3].stmt)->reject.type = NFT_REJECT_TCP_RST;
				} else {
					erec_queue(error(&(yylsp[-1]), "unsupported reject type", (yyvsp[0].string)),
						   state->msgs);
					YYERROR;
				}
			}
#line 5400 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1608 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_SNAT;
			}
#line 5409 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1613 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_DNAT;
			}
#line 5418 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1621 "parser_bison.y" /* yacc.c:1646  */
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
#line 5439 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1640 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1651 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->nat.addr = (yyvsp[0].expr);
			}
#line 5455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1655 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->nat.addr = (yyvsp[-2].expr);
				(yyvsp[-3].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 5464 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1660 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.proto = (yyvsp[0].expr);
			}
#line 5472 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1664 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->nat.flags = (yyvsp[0].val);
			}
#line 5480 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1673 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = masq_stmt_alloc(&(yyloc)); }
#line 5486 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1677 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->masq.proto = (yyvsp[0].expr);
			}
#line 5494 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1681 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->masq.proto = (yyvsp[-1].expr);
				(yyvsp[-4].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 5503 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1686 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->masq.flags = (yyvsp[0].val);
			}
#line 5511 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1695 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.stmt) = redir_stmt_alloc(&(yyloc)); }
#line 5517 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1699 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->redir.proto = (yyvsp[0].expr);
			}
#line 5525 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1703 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 5533 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1707 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].stmt)->redir.proto = (yyvsp[-1].expr);
				(yyvsp[-3].stmt)->redir.flags = (yyvsp[0].val);
			}
#line 5542 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1714 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[0].expr);
			}
#line 5551 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1719 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = dup_stmt_alloc(&(yyloc));
				(yyval.stmt)->dup.to = (yyvsp[-2].expr);
				(yyval.stmt)->dup.dev = (yyvsp[0].expr);
			}
#line 5561 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1727 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = fwd_stmt_alloc(&(yyloc));
				(yyval.stmt)->fwd.to = (yyvsp[0].expr);
			}
#line 5570 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1735 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 5578 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1740 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
#line 5584 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1741 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
#line 5590 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1742 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
#line 5596 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1750 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
#line 5604 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1756 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 5612 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1763 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->queue.queue = (yyvsp[0].expr);
				(yyvsp[-2].stmt)->queue.queue->location = (yyloc);
			}
#line 5621 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1768 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].stmt)->queue.flags |= (yyvsp[0].val);
			}
#line 5629 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1775 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = (yyvsp[-2].val) | (yyvsp[0].val);
			}
#line 5637 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1780 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
#line 5643 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1781 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
#line 5649 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1785 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[-2].val);
				(yyval.stmt)->set.key = (yyvsp[-1].expr);
				(yyval.stmt)->set.set = (yyvsp[0].expr);
			}
#line 5660 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1793 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
#line 5666 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1794 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
#line 5672 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1798 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-5].stmt)->flow.key  = (yyvsp[-2].expr);
				(yyvsp[-5].stmt)->flow.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-5].stmt);
			}
#line 5683 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1805 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-4].stmt)->flow.key  = (yyvsp[-2].expr);
				(yyvsp[-4].stmt)->flow.stmt = (yyvsp[-1].stmt);
				(yyval.stmt)->location  = (yyloc);
				(yyval.stmt) = (yyvsp[-4].stmt);
			}
#line 5694 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1814 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = flow_stmt_alloc(&(yyloc));
			}
#line 5702 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1820 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt)	= (yyvsp[-1].stmt);
			}
#line 5710 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1827 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].stmt)->flow.table = (yyvsp[0].string);
			}
#line 5718 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1833 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[0].expr));
			}
#line 5726 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1839 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 5737 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1846 "parser_bison.y" /* yacc.c:1646  */
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
#line 5755 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1860 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[0].string));
				xfree((yyvsp[0].string));
			}
#line 5766 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1869 "parser_bison.y" /* yacc.c:1646  */
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[0].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
#line 5779 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1879 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 5785 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1880 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 5791 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1881 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 5797 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1882 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 5803 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1883 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 5809 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1884 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 5815 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1885 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 5821 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1890 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5829 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1894 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5837 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1901 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5845 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1908 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5853 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1915 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5861 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1925 "parser_bison.y" /* yacc.c:1646  */
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
#line 5882 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1944 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].val));
			}
#line 5890 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1950 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1956 "parser_bison.y" /* yacc.c:1646  */
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
#line 5911 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1972 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 5919 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1983 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 5928 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1990 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 5937 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 329:
#line 1995 "parser_bison.y" /* yacc.c:1646  */
    {
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 5946 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2003 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 5954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2007 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 5962 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2011 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[-3].expr), (yyvsp[-1].expr));
			}
#line 5970 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2018 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[-1].expr);
			}
#line 5979 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2025 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 5987 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2035 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[0]), (yyvsp[0].expr));
			}
#line 5995 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2041 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr)	= (yyvsp[-1].expr);
			}
#line 6003 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2048 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->timeout = (yyvsp[0].val) * 1000;
			}
#line 6011 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2052 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].expr)->comment = (yyvsp[0].string);
			}
#line 6019 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 350:
#line 2070 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 6027 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2074 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_FLAGCMP, (yyvsp[-1].expr), (yyvsp[0].expr));
			}
#line 6035 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 352:
#line 2078 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[-1]), (yyvsp[-1].val), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6043 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 353:
#line 2084 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[-2].expr));
				compound_expr_add((yyval.expr), (yyvsp[0].expr));
			}
#line 6053 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 354:
#line 2090 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyvsp[-2].expr)->location = (yyloc);
				compound_expr_add((yyvsp[-2].expr), (yyvsp[0].expr));
				(yyval.expr) = (yyvsp[-2].expr);
			}
#line 6063 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 355:
#line 2097 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6069 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 356:
#line 2098 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6075 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 357:
#line 2099 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6081 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2104 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6089 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 360:
#line 2108 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6097 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2115 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6105 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 364:
#line 2122 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6113 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2129 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6121 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2139 "parser_bison.y" /* yacc.c:1646  */
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
#line 6142 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 370:
#line 2157 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6148 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 371:
#line 2158 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 6154 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 372:
#line 2160 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ether");
			}
#line 6164 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2166 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ip");
			}
#line 6174 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2172 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ip6");
			}
#line 6184 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2178 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "vlan");
			}
#line 6194 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2184 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "arp");
			}
#line 6204 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2190 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6215 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2197 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6226 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2204 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6237 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2211 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6248 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 381:
#line 2218 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6259 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2225 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6270 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2232 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6281 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2239 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6292 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2246 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6303 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 386:
#line 2253 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6314 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 387:
#line 2260 "parser_bison.y" /* yacc.c:1646  */
    {
				uint8_t data = ICMP_REDIRECT;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &icmp_type_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
#line 6325 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2267 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "snat");
			}
#line 6335 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 389:
#line 2273 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "dnat");
			}
#line 6345 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 390:
#line 2279 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ecn");
			}
#line 6355 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2286 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_EQ; }
#line 6361 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 392:
#line 2287 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_NEQ; }
#line 6367 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 393:
#line 2288 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LT; }
#line 6373 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2289 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GT; }
#line 6379 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2290 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_GTE; }
#line 6385 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2291 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = OP_LTE; }
#line 6391 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2295 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
#line 6399 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2299 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
#line 6407 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2303 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
#line 6415 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2307 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[0].string));
			}
#line 6423 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2311 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[0].string));
			}
#line 6431 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 402:
#line 2315 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
#line 6439 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 403:
#line 2321 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 6447 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 404:
#line 2325 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[0].val));
			}
#line 6455 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 407:
#line 2334 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_LEN; }
#line 6461 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2335 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFPROTO; }
#line 6467 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2336 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_L4PROTO; }
#line 6473 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2337 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PROTOCOL; }
#line 6479 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2338 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PRIORITY; }
#line 6485 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2341 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_MARK; }
#line 6491 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2342 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIF; }
#line 6497 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2343 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFNAME; }
#line 6503 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2344 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFTYPE; }
#line 6509 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2345 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIF; }
#line 6515 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2346 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFNAME; }
#line 6521 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2347 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFTYPE; }
#line 6527 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2348 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKUID; }
#line 6533 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2349 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_SKGID; }
#line 6539 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2350 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_NFTRACE; }
#line 6545 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2351 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_RTCLASSID; }
#line 6551 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2352 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
#line 6557 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2353 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
#line 6563 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2354 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_PKTTYPE; }
#line 6569 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2355 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CPU; }
#line 6575 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2356 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_IIFGROUP; }
#line 6581 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2357 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_OIFGROUP; }
#line 6587 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2358 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_META_CGROUP; }
#line 6593 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2362 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 6601 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2366 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 6609 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2372 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[0].val), -1);
			}
#line 6617 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2376 "parser_bison.y" /* yacc.c:1646  */
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
#line 6634 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2390 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATE; }
#line 6640 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2391 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DIRECTION; }
#line 6646 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2392 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_STATUS; }
#line 6652 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2393 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_MARK; }
#line 6658 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2394 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_EXPIRATION; }
#line 6664 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2395 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_HELPER; }
#line 6670 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2396 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_LABELS; }
#line 6676 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2399 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_SRC; }
#line 6682 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2400 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_DST; }
#line 6688 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2401 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
#line 6694 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2402 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTOCOL; }
#line 6700 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2403 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_SRC; }
#line 6706 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2404 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PROTO_DST; }
#line 6712 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2408 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_BYTES; }
#line 6718 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2409 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = NFT_CT_PKTS; }
#line 6724 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2413 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[-2].val), (yyvsp[0].expr));
			}
#line 6732 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2419 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.stmt) = payload_stmt_alloc(&(yyloc), (yyvsp[-2].expr), (yyvsp[0].expr));
			}
#line 6740 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2443 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				(yyval.expr)->payload.base	= (yyvsp[-4].val);
				(yyval.expr)->payload.offset	= (yyvsp[-2].val);
				(yyval.expr)->len			= (yyvsp[0].val);
				(yyval.expr)->dtype		= &integer_type;
			}
#line 6752 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2452 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_LL_HDR; }
#line 6758 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2453 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
#line 6764 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 472:
#line 2454 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
#line 6770 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2458 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[0].val));
			}
#line 6778 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2463 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_SADDR; }
#line 6784 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2464 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_DADDR; }
#line 6790 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2465 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ETHHDR_TYPE; }
#line 6796 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2469 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[0].val));
			}
#line 6804 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2474 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_VID; }
#line 6810 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2475 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_CFI; }
#line 6816 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2476 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_PCP; }
#line 6822 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2477 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = VLANHDR_TYPE; }
#line 6828 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2481 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[0].val));
			}
#line 6836 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2486 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HRD; }
#line 6842 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2487 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PRO; }
#line 6848 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2488 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_HLN; }
#line 6854 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2489 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_PLN; }
#line 6860 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 487:
#line 2490 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ARPHDR_OP; }
#line 6866 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 488:
#line 2494 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[0].val));
			}
#line 6874 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 489:
#line 2499 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_VERSION; }
#line 6880 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2500 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_HDRLENGTH; }
#line 6886 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 491:
#line 2501 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DSCP; }
#line 6892 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 492:
#line 2502 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ECN; }
#line 6898 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2503 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_LENGTH; }
#line 6904 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 494:
#line 2504 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_ID; }
#line 6910 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 495:
#line 2505 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_FRAG_OFF; }
#line 6916 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 496:
#line 2506 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_TTL; }
#line 6922 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2507 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_PROTOCOL; }
#line 6928 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 498:
#line 2508 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_CHECKSUM; }
#line 6934 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 499:
#line 2509 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_SADDR; }
#line 6940 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 500:
#line 2510 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IPHDR_DADDR; }
#line 6946 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2514 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[0].val));
			}
#line 6954 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2519 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_TYPE; }
#line 6960 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 503:
#line 2520 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CODE; }
#line 6966 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 504:
#line 2521 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_CHECKSUM; }
#line 6972 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 505:
#line 2522 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_ID; }
#line 6978 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 506:
#line 2523 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_SEQ; }
#line 6984 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 507:
#line 2524 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_GATEWAY; }
#line 6990 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 508:
#line 2525 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMPHDR_MTU; }
#line 6996 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 509:
#line 2529 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[0].val));
			}
#line 7004 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 510:
#line 2534 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_VERSION; }
#line 7010 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 511:
#line 2535 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DSCP; }
#line 7016 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 512:
#line 2536 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_ECN; }
#line 7022 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 513:
#line 2537 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_FLOWLABEL; }
#line 7028 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 514:
#line 2538 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_LENGTH; }
#line 7034 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 515:
#line 2539 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_NEXTHDR; }
#line 7040 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 516:
#line 2540 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_HOPLIMIT; }
#line 7046 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 517:
#line 2541 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_SADDR; }
#line 7052 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 518:
#line 2542 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = IP6HDR_DADDR; }
#line 7058 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 519:
#line 2545 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[0].val));
			}
#line 7066 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 520:
#line 2550 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_TYPE; }
#line 7072 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 521:
#line 2551 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CODE; }
#line 7078 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 522:
#line 2552 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
#line 7084 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 523:
#line 2553 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_PPTR; }
#line 7090 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 524:
#line 2554 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MTU; }
#line 7096 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 525:
#line 2555 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_ID; }
#line 7102 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 526:
#line 2556 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_SEQ; }
#line 7108 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 527:
#line 2557 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
#line 7114 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 528:
#line 2561 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[0].val));
			}
#line 7122 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 529:
#line 2566 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_NEXTHDR; }
#line 7128 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 530:
#line 2567 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_HDRLENGTH; }
#line 7134 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 531:
#line 2568 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_RESERVED; }
#line 7140 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 532:
#line 2569 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SPI; }
#line 7146 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 533:
#line 2570 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = AHHDR_SEQUENCE; }
#line 7152 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 534:
#line 2574 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[0].val));
			}
#line 7160 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 535:
#line 2579 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SPI; }
#line 7166 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 536:
#line 2580 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = ESPHDR_SEQUENCE; }
#line 7172 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 537:
#line 2584 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[0].val));
			}
#line 7180 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 538:
#line 2589 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_NEXTHDR; }
#line 7186 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 539:
#line 2590 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_FLAGS; }
#line 7192 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 540:
#line 2591 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = COMPHDR_CPI; }
#line 7198 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 541:
#line 2595 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[0].val));
			}
#line 7206 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 542:
#line 2600 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 7212 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 543:
#line 2601 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 7218 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 544:
#line 2602 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 7224 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 545:
#line 2603 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 7230 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 546:
#line 2607 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[0].val));
			}
#line 7238 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 547:
#line 2612 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_SPORT; }
#line 7244 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 548:
#line 2613 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_DPORT; }
#line 7250 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 549:
#line 2614 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_LENGTH; }
#line 7256 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 550:
#line 2615 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = UDPHDR_CHECKSUM; }
#line 7262 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 551:
#line 2619 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[0].val));
			}
#line 7270 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 552:
#line 2624 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SPORT; }
#line 7276 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 553:
#line 2625 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DPORT; }
#line 7282 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 554:
#line 2626 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_SEQ; }
#line 7288 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 555:
#line 2627 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_ACKSEQ; }
#line 7294 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 556:
#line 2628 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_DOFF; }
#line 7300 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 557:
#line 2629 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_RESERVED; }
#line 7306 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 558:
#line 2630 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_FLAGS; }
#line 7312 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 559:
#line 2631 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_WINDOW; }
#line 7318 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 560:
#line 2632 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_CHECKSUM; }
#line 7324 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 561:
#line 2633 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = TCPHDR_URGPTR; }
#line 7330 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 562:
#line 2637 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[0].val));
			}
#line 7338 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 563:
#line 2642 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_SPORT; }
#line 7344 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 564:
#line 2643 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_DPORT; }
#line 7350 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 565:
#line 2644 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DCCPHDR_TYPE; }
#line 7356 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 566:
#line 2648 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[0].val));
			}
#line 7364 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 567:
#line 2653 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_SPORT; }
#line 7370 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 568:
#line 2654 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_DPORT; }
#line 7376 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 569:
#line 2655 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_VTAG; }
#line 7382 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 570:
#line 2656 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = SCTPHDR_CHECKSUM; }
#line 7388 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 578:
#line 2669 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[0].val));
			}
#line 7396 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 579:
#line 2674 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_NEXTHDR; }
#line 7402 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 580:
#line 2675 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = HBHHDR_HDRLENGTH; }
#line 7408 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 581:
#line 2679 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[0].val));
			}
#line 7416 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 582:
#line 2684 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_NEXTHDR; }
#line 7422 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 583:
#line 2685 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_HDRLENGTH; }
#line 7428 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 584:
#line 2686 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_TYPE; }
#line 7434 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 585:
#line 2687 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RTHDR_SEG_LEFT; }
#line 7440 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 586:
#line 2691 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[0].val));
			}
#line 7448 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 587:
#line 2697 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[-1].val) - 1;
			}
#line 7456 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 588:
#line 2703 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[0].val));
			}
#line 7464 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 589:
#line 2708 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = RT2HDR_ADDR; }
#line 7470 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 590:
#line 2712 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[0].val));
			}
#line 7478 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 591:
#line 2717 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_NEXTHDR; }
#line 7484 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 592:
#line 2718 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED; }
#line 7490 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 593:
#line 2719 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
#line 7496 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 594:
#line 2720 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_RESERVED2; }
#line 7502 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 595:
#line 2721 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_MFRAGS; }
#line 7508 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 596:
#line 2722 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = FRAGHDR_ID; }
#line 7514 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 597:
#line 2726 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[0].val));
			}
#line 7522 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 598:
#line 2731 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_NEXTHDR; }
#line 7528 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 599:
#line 2732 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = DSTHDR_HDRLENGTH; }
#line 7534 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 600:
#line 2736 "parser_bison.y" /* yacc.c:1646  */
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[0].val));
			}
#line 7542 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 601:
#line 2741 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_NEXTHDR; }
#line 7548 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 602:
#line 2742 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_HDRLENGTH; }
#line 7554 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 603:
#line 2743 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_TYPE; }
#line 7560 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 604:
#line 2744 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_RESERVED; }
#line 7566 "parser_bison.c" /* yacc.c:1646  */
    break;

  case 605:
#line 2745 "parser_bison.y" /* yacc.c:1646  */
    { (yyval.val) = MHHDR_CHECKSUM; }
#line 7572 "parser_bison.c" /* yacc.c:1646  */
    break;


#line 7576 "parser_bison.c" /* yacc.c:1646  */
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
#line 2748 "parser_bison.y" /* yacc.c:1906  */

